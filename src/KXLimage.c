#include <stdio.h>
#include <stdlib.h> // for exit
#include <sys/stat.h>
#include <sys/types.h>
#include "KXL.h"

#if defined(_LP64) || defined(__LP64__)
#define _FILE_OFFSET_BITS 64 // Enable 64-bit offsets for large file support
#endif

extern KXL_Window *KXL_Root;

//==============================================================
// Convert an 8bpp BMP to 16bpp, 8bppのＢＭＰを16bpp化する
//  引き数：8bpsデータ
//        ：16bpsXイメージ
//        ：パレット
//==============================================================
void KXL_CreateBitmap8to16(Uint8 *from, XImage *to, KXL_RGBE *rgb, Uint8 blend)
{
  Uint32 x, y, offset, no;

  for (y = 0; y < to->height; y ++) {
    for (x = 0; x < to->width; x ++) {
      // Offset calculation, オフセット計算
      offset = (y * to->bytes_per_line) + (x << 1);
      no = from[y * to->width + x];
      if (no == blend) { // Make the specified pallet number black., 指定パレット番号を黒にする
        to->data[offset ++] = 0x00;
        to->data[offset ++] = 0x00;
      } else {
        // 000rrrrr, 000ggggg, 000bbbbb
        //            |
        // gg0bbbbb, rrrrrggg
        if (!(rgb[no].r | rgb[no].g | rgb[no].b)) { // Eliminate complete black, 完全な黒を無くす
          to->data[offset++] = 0x41;
          to->data[offset++] = 0x08;
        } else {
          to->data[offset++] = rgb[no].b | (rgb[no].g << 6);
          to->data[offset++] = (rgb[no].r << 3) | (rgb[no].g >> 2);
        }
      }
    }
  }
}

//==============================================================
// Convert an 8bpp BMP to 16bpp, 8bppのＢＭＰを24bpp化する
//  引き数：8bpsデータ
//        ：24bpsXイメージ
//        ：パレット
//==============================================================
void KXL_CreateBitmap8to24(Uint8 *from, XImage *to, KXL_RGBE *rgb, Uint8 blend)
{
  Uint32 x, y, offset, no;

  for (y = 0; y < to->height; y ++) {
    for (x = 0; x < to->width; x ++) {
      // オフセット計算
      offset = (y * to->bytes_per_line) + ((x * to->bits_per_pixel) >> 3);
      no = from[y * to->width + x];
      if (no == blend) { // Make the specified pallet number black., 指定パレット番号を黒にする
        to->data[offset ++] = 0x00;
        to->data[offset ++] = 0x00;
        to->data[offset ++] = 0x00;
      } else {
        if (!(rgb[no].r | rgb[no].g | rgb[no].b)) { // Eliminate complete black, 完全な黒を無くす
          to->data[offset ++] = 0x01;
          to->data[offset ++] = 0x01;
          to->data[offset ++] = 0x01;
        } else {
          to->data[offset ++] = rgb[no].b;
          to->data[offset ++] = rgb[no].g;
          to->data[offset ++] = rgb[no].r;
        }
      }
    }
  }
}

//==============================================================
// Converting an 8bpp BMP to 1bpp, 8bppのＢＭＰを1bpp化する
//  引き数：8bpsデータ
//        ：1bpsXイメージ
//==============================================================
void KXL_CreateBitmap8to1(Uint8 *from, XImage *to, Uint8 blend)
{
  Uint16 x, y, offset, no;

  for (y = 0; y < to->height; y ++) {
    for (x = 0; x < to->width; x ++) {
      // オフセット計算
      offset = (y * to->bytes_per_line) + (x >> 3);
      no = from[y * to->width + x];
      if (no != blend)
        to->data[offset] |= 1 << (x & 7);
      else
        to->data[offset] &= ~(1 << (x & 7));
    }
  }
}

//==============================================================
// Bitmap header information loading, ビットマップヘッダ情報読み込み
// Argument: file name, 引き数：ファイル名
//         :Header information pointer, ヘッダ情報のポインタ
//  If the image data is NULL, that means the function has failed.
//==============================================================
int KXL_ReadBitmapHeader0(const char *filename, KXL_BitmapHeader *hed)
{
  FILE *fp;
  struct stat st;
  Bool stat_ok = 0;
  int fd, data;
  Uint16 i, j;
//  uint8_t data;

  // Open file in read-only mode, ファイルを読み込み専用で開く
  if ((fp = fopen(filename,"rb")) == NULL) {
    fprintf(stderr, "KXL error message\n'%s' open error\n", filename);
    goto error_KXL_ReadBitmapHeader0;
  }
  // Get underlying File Descriptor (fd) and File Stats (st)
  if ((fd = fileno(fp)) >= 0)
    stat_ok = !(fstat(fd, &st));

  // Read header, ヘッダ読み込み
  if (fread(hed->magic, 1, 2, fp) != 2) {
    fprintf(stderr, "KXL error message\n'%s' cannot read header\n", filename);
    goto error_KXL_ReadBitmapHeader1;
  }
  if (hed->magic[0] != 'B' || hed->magic[1] != 'M') {
    fprintf(stderr, "KXL error message\n'%s' is not a bitmap file\n", filename);
    goto error_KXL_ReadBitmapHeader1;
  }
  if (KXLread32(fp, &hed->file_size)  || \
      KXLread16(fp, &hed->reserved1)  || \
      KXLread16(fp, &hed->reserved2)  || \
      KXLread32(fp, &hed->offset)     || \
      KXLread32(fp, &hed->hed_size)   || \
      KXLread32(fp, &hed->width)      || \
      KXLread32(fp, &hed->height)     || \
      KXLread16(fp, &hed->plane)      || \
      KXLread16(fp, &hed->depth)      || \
      KXLread32(fp, &hed->lzd)        || \
      KXLread32(fp, &hed->image_size) || \
      KXLread32(fp, &hed->x_pixels)   || \
      KXLread32(fp, &hed->y_pixels)   || \
      KXLread32(fp, &hed->pals)       || \
      KXLread32(fp, &hed->pals2)) {
    fprintf(stderr, "KXL error message\n'%s' cannot read bitmap file header\n", filename);
    goto error_KXL_ReadBitmapHeader1;
  }
  // Not supported, bad image, not usable here
  if (hed->width  == 0 || hed->width  > 0xffff || \
      hed->height == 0 || hed->height > 0xffff) {
    fprintf(stderr, "KXL error message\n'%s' [width=%d, height=%d] not supported\n",
            filename, hed->width, hed->height);
    goto error_KXL_ReadBitmapHeader1;
  }
  // Not supported except for 4 or 8bpp, 以外はサポート外
  if (hed->depth < 4 || hed->depth > 8) {
    fprintf(stderr, "KXL error message\n'%s' %dbps is not supported\n",
            filename, hed->depth);
    goto error_KXL_ReadBitmapHeader1;
  }
  // Exit if there is no image size, イメージサイズがなければ終了
  if (hed->image_size == 0) {
    fprintf(stderr, "KXL error message\n'%s image size not found\n",
            filename);
    goto error_KXL_ReadBitmapHeader1;
  }
  // Setting the number of pallets used, 使用パレット数設定
  hed->pals = hed->pals ? hed->pals : (1 << hed->depth);
  // Check if there is space for the palette.
  if (stat_ok) {
#if defined(_LP64) || defined(__LP64__)
    off_t pos = ftello(fp);
    if ((pos + 4 * (off_t)hed->pals) > st.st_size) {
#else
    long pos = ftell(fp);
    if ((pos + 4 * (long)hed->pals) > st.st_size) {
#endif
      fprintf(stderr, "KXL error message\n'%s' not found palette or truncated\n", filename);
      goto error_KXL_ReadBitmapHeader1;
    }
  }
  // Get color map, カラーマップ取得
  // Not supported, bad image, not usable here
  if (hed->pals == 0 || hed->pals > 0xffff) {
    fprintf(stderr, "KXL error message\n'%s' [pals=%d] palette size not supported\n",
            filename, hed->pals, hed->height);
    goto error_KXL_ReadBitmapHeader1;
  }
  hed->rgb = (KXL_RGBE *)malloc(sizeof(KXL_RGBE) * hed->pals);
  if (hed->rgb == NULL) {
    fprintf(stderr, "KXL error message\n'%s' bitmap RGB, out of memory!!\n", filename);
    goto error_KXL_ReadBitmapHeader1;
  }
  for (i = 0; i < hed->pals; i ++) {
    if (KXLread8(fp, &hed->rgb[i].b) || \
        KXLread8(fp, &hed->rgb[i].g) || \
        KXLread8(fp, &hed->rgb[i].r) || \
        KXLread8(fp, &hed->rgb[i].e)) {
      fprintf(stderr, "KXL error message\n'%s' bitmap RGB missing or truncated\n", filename);
      goto error_KXL_ReadBitmapHeader2;

    }
    // Xが16bppなら補正しておく
    if (KXL_Root->Depth == 16) {
      hed->rgb[i].b /= 8;
      hed->rgb[i].g /= 8;
      hed->rgb[i].r /= 8;
    }
  }
  // Adjust the width to a multiple of 4, 横幅を4の倍数で補正する
  hed->w = ((hed->width + 3) / 4) * 4;
  // Check if there is space for the palette.
  if (stat_ok) {
#if defined(_LP64) || defined(__LP64__)
    off_t pos = ftello(fp);
    if ((pos + (off_t)hed->image_size) > st.st_size) {
#else
    long pos = ftell(fp);
    if ((pos + (long)hed->image_size) > st.st_size) {
#endif
      fprintf(stderr, "KXL error message\n'%s' not found image data or truncated\n", filename);
      goto error_KXL_ReadBitmapHeader2;
    }
  }
  // Secure data area, データ領域確保
  if (hed->depth == 8)
    hed->data = (Uint8 *)malloc(hed->image_size);
  else
    hed->data = (Uint8 *)malloc(hed->image_size * 2);
  if (hed->data == NULL) {
    fprintf(stderr, "KXL error message\n'%s' bitmap image, out of memory!!\n", filename);
    goto error_KXL_ReadBitmapHeader2;
  }
  // get data, データを取得する
  if (hed->depth == 8) {
    // Read and store an 8bpp BMP image, 8bppのbmpを読み込み格納する
    for (i = 0; i < hed->height; i++) {
      // Load from the last line, 最終ラインから読み込む
#if defined(_LP64) || defined(__LP64__)
      if ((fseeko(fp, (off_t)(hed->offset + (hed->height - i - 1) * hed->w), 0) < 0) ||
#else
      if ((fseek(fp, (hed->offset + (hed->height - i - 1) * hed->w), 0) < 0) ||
#endif
          (fread(&(hed->data[i * hed->w]), hed->w, 1, fp) != 1)) {
        fprintf(stderr, "KXL error message\n'%s' bitmap image read error\n", filename);
        goto error_KXL_ReadBitmapHeader3;
      }
    }
  } else {
    Uint32 w = (((hed->width / 2) + 3) / 4) * 4;
    // Read and store a 4bpp BMP image, 4bppのbmpを読み込み格納する
    for (i = 0; i < hed->height; i++) {
      // Load from the last line, 最終ラインから読み込む
      fseek(fp, hed->offset + (hed->height - i - 1) * w, 0);
      for (j = 0; j < w; j ++) {
        data = fgetc(fp);
        hed->data[i * hed->w + j * 2 + 0] = data >> 4;
        hed->data[i * hed->w + j * 2 + 1] = data & 0x0f;
      }
    }
  }
  hed->depth = 8;
  fclose(fp);
  return 0;

error_KXL_ReadBitmapHeader3:
  free(hed->data);
error_KXL_ReadBitmapHeader2:
  free(hed->rgb);
error_KXL_ReadBitmapHeader1:
  fclose(fp);
error_KXL_ReadBitmapHeader0:
  hed->magic[0] = hed->magic[1] = 0;
  hed->file_size = 0;
  hed->reserved1 = hed->reserved2 = 0;
  hed->offset = hed->hed_size = hed->width = hed->height = 0;
  hed->plane = hed->depth = 0;
  hed->lzd = hed->image_size = hed->x_pixels = hed->y_pixels = hed->pals = hed->pals2 = 0;
  hed->data = NULL;
  hed->rgb = NULL;
  return -1;
}

// Deprecated, kept for backwards compatibility with older code
void KXL_ReadBitmapHeader(const char *filename, KXL_BitmapHeader *hed)
{
  int i;

  if (KXL_ReadBitmapHeader0(filename, hed)) {
    // error, cleanup hed and then return
    if (hed->data)
      KXL_Free(hed->data);
    if (hed->rgb)
      KXL_Free(hed->rgb);
  }
  return;
}
