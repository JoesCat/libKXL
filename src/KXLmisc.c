#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>
#include <sys/time.h>
#include "KXL.h"
#include "KXL-config.h"

#if defined(_LP64) || defined(__LP64__)
#define _FILE_OFFSET_BITS 64 // Enable 64-bit offsets for large file support
#endif

Bool KXL_TimerFlag;

// 360 degree data, 360度データ
static Sint16 sin360[] = {
    0,
    4,    8,   13,   17,   22,   26,   31,   35,   40,   44,
   48,   53,   57,   61,   66,   70,   74,   79,   83,   87,
   91,   95,  100,  104,  108,  112,  116,  120,  124,  127,
  131,  135,  139,  143,  146,  150,  154,  157,  161,  164,
  167,  171,  174,  177,  181,  184,  187,  190,  193,  196,
  198,  201,  204,  207,  209,  212,  214,  217,  219,  221,
  223,  226,  228,  230,  232,  233,  235,  237,  238,  240,
  242,  243,  244,  246,  247,  248,  249,  250,  251,  252,
  252,  253,  254,  254,  255,  255,  255,  255,  255,  256,
  255,  255,  255,  255,  255,  254,  254,  253,  252,  252,
  251,  250,  249,  248,  247,  246,  244,  243,  242,  240,
  238,  237,  235,  233,  232,  230,  228,  226,  223,  221,
  219,  217,  214,  212,  209,  207,  204,  201,  198,  196,
  193,  190,  187,  184,  181,  177,  174,  171,  167,  164,
  161,  157,  154,  150,  146,  143,  139,  135,  131,  127,
  124,  120,  116,  112,  108,  104,  100,   95,   91,   87,
   83,   79,   74,   70,   66,   61,   57,   53,   48,   44,
   40,   35,   31,   26,   22,   17,   13,    8,    4,    0,
   -4,   -8,  -13,  -17,  -22,  -26,  -31,  -35,  -40,  -44,
  -48,  -53,  -57,  -61,  -66,  -70,  -74,  -79,  -83,  -87,
  -91,  -95, -100, -104, -108, -112, -116, -120, -124, -127,
 -131, -135, -139, -143, -146, -150, -154, -157, -161, -164,
 -167, -171, -174, -177, -181, -184, -187, -190, -193, -196,
 -198, -201, -204, -207, -209, -212, -214, -217, -219, -221,
 -223, -226, -228, -230, -232, -233, -235, -237, -238, -240,
 -242, -243, -244, -246, -247, -248, -249, -250, -251, -252,
 -252, -253, -254, -254, -255, -255, -255, -255, -255, -256,
 -255, -255, -255, -255, -255, -254, -254, -253, -252, -252,
 -251, -250, -249, -248, -247, -246, -244, -243, -242, -240,
 -238, -237, -235, -233, -232, -230, -228, -226, -223, -221,
 -219, -217, -214, -212, -209, -207, -204, -201, -198, -196,
 -193, -190, -187, -184, -181, -177, -174, -171, -167, -164,
 -161, -157, -154, -150, -146, -143, -139, -135, -131, -128,
 -124, -120, -116, -112, -108, -104, -100,  -95,  -91,  -87,
  -83,  -79,  -74,  -70,  -66,  -61,  -57,  -53,  -48,  -44,
  -40,  -35,  -31,  -26,  -22,  -17,  -13,   -8,   -4,    0,
};

//==============================================================
// Get timer flag, タイマーフラグ取得
//==============================================================
Bool KXL_GetTimer(void)
{
  return KXL_TimerFlag;
}

//==============================================================
// timer flag reset, タイマーフラグリセット
//==============================================================
void KXL_ResetTimer(void)
{
  KXL_TimerFlag = False;
}

//==============================================================
// timer callback, タイマーコールバック
//==============================================================
void KXL_TimerCallBack(int dummy)
{
  KXL_TimerFlag = True;
}

//==============================================================
// timer settings, タイマー設定
// Number of frames: 引き数：フレーム数
//==============================================================
void KXL_Timer(Uint16 time)
{
  struct itimerval val={
    {0, 1000000 / time},
    {0, 1000000 / time},
  };
  signal(SIGALRM, KXL_TimerCallBack);
  setitimer(ITIMER_REAL, &val, NULL);
  KXL_TimerFlag = False;
}

//==============================================================
// Memory reservation, メモリ確保
// Arguments: Memory size, 引き数：メモリサイズ
// Return value: A pointer to allocated memory, 戻り値：確保したメモリのポインタ
//==============================================================
void *KXL_Malloc(Uint32 size)
{
  void *new;

  new = malloc(size);
  if (new == NULL) {
    fprintf(stderr, "KXL error message\nOut Of memory!!\n");
    exit(1);
  }
  return new;
}

//==============================================================
// Memory reallocation, メモリ再確保
// Argument: Pointer to memory, 引き数：メモリのポインタ
//         : memory size, メモリサイズ
// Return value: Pointer to reallocated memory, 戻り値：再確保したメモリのポインタ
//==============================================================
void *KXL_Realloc(void *src, Uint32 size)
{
  void *new;

  new = realloc(src, size);
  if (new == NULL) {
    fprintf(stderr, "KXL error message\nOut Of memory!!\n");
    free(src);
    exit(1);
  }
  return new;
}

//==============================================================
// Free memory, メモリ解放
// Argument: Pointer to memory, 引き数：メモリのポインタ
//==============================================================
void KXL_Free(void *src)
{
  free(src);
  src = NULL;
}

//==============================================================
// Get direction, 方角取得
// Arguments: Your rectangle, 引き数：自分の矩形
//          : opponent's rectangle, 相手の矩形
//==============================================================
Uint16 KXL_GetDirection(KXL_Rect src, KXL_Rect target) {
  Uint16 k, x, y;
  Uint16 mx, my, yx, yy;

  mx = src.Left + (src.Width >> 1);
  my = src.Top + (src.Height >> 1);
  yx = target.Left + (target.Width >> 1);
  yy = target.Top + (target.Height >> 1);

  x = abs(yx - mx);
  y = abs(yy - my);
  if (yx == mx)
    k = (yy > my) ? 0 : 180;
  else if (yy == my)
    k = (yx > mx) ? 90 : 270;
  else if (yx > mx)
    if (yy > my)
      k = 90 * x / (x + y);
    else
      k = 180 - (90 * x / (x + y));
  else
    if (yy > my)
      k = 360 - (90 * x / (x + y));
    else
      k = (90 * x / (x + y)) + 180;
  return k;
}

//==============================================================
// Setting the added value based on angle, 角度による加算値設定
// Number of draws
//        : angle, 引き数：角度
//        : Horizontal Addition Right Pointer, 水平加算値のポインタ
//        : Vertical Addition Value Pointer, 垂直加算値のポインタ
//==============================================================
void KXL_GetDirectionAdd(Sint16 dir, Sint16 *x, Sint16 *y) {
  Sint16 dir2 = dir + 90;

  while (dir < 0) dir += 360;
  while (dir > 360) dir -= 360;
  *x = sin360[dir];

  while (dir2 < 0) dir2 += 360;
  while (dir2 > 360) dir2 -= 360;
  *y = sin360[dir2];
}

//==============================================================
// 8-bit file reading, with file error check
// Arguments: File pointer, errno, value
// Return value: errno, 8-bit value
//==============================================================
int KXLread8(FILE *fp, int *fe, uint8_t *p)
{
  int e;

  if ((e = fread(p, 1, 1, fp)) == 1) {
    *fe = 0;
    return 0;
  }
  *fe = e;
  return -1;
}

//==============================================================
// 16-bit little-endian reading, １６リトルビットエンディアン読み込み
// Arguments: File pointer, errno, value
// Return value: errno, 16-bit value
//==============================================================
int KXLread16(FILE *fp, int *fe, uint16_t *p)
{
  int e;
  uint8_t c[2];

  if ((e = fread(c, 1, 2, fp)) == 2) {
    *p = (uint16_t)(c[1]<<8 | c[0]);
    *fe = 0;
    return 0;
  }
  *p = 0;
  *fe = e;
  return -1;
}

// Deprecated, kept for backwards compatibility with older code
// Arguments: File pointer, 引き数：ファイルポインタ
// Return value: 16-bit value, 戻り値：１６ビット値
Uint16 KXL_ReadU16(FILE *fp)
{
  uint8_t c[2];

  fread(c, 1, 2, fp);
  return (Uint16)(c[0] +  c[1] * 0x100);
}

//==============================================================
// 32-bit little-endian read, ３２ビットリトルエンディアン読み込み
// Arguments: File pointer, errno, value
// Return value: errno, 32-bit value
//==============================================================
int KXLread32(FILE *fp, int *fe, uint32_t *p)
{
  int e;
  uint8_t c[4];

  if ((e = fread(c, 1, 4, fp)) == 4) {
    *p = (uint32_t)(c[3]<<24 | c[2]<<16 |c[1]<<8 | c[0]);
    *fe = 0;
    return 0;
  }
  *p = 0;
  *fe = e;
  return -1;
}

// Deprecated, kept for backwards compatibility with older code
// Arguments: File pointer, 引き数：ファイルポインタ
// Return value: 32-bit value, 戻り値：３２ビット値
Uint32 KXL_ReadU32(FILE *fp)
{
  uint8_t c[4];

  fread(c, 1, 4, fp);
  return (Uint32)(c[0] + c[1] * 0x100L + c[2] * 0x10000L + c[3] * 0x1000000L);
}
