#include <stdlib.h>

#include "KXL.h"
#include "KXL-config.h"

extern KXL_Window *KXL_Root;
extern Bool KXL_SoundOk;

int main(int argc, char** argv)
{
  char *snames[] = {"sound1", "sound2", "sound3", ""};
  char *notexist[] = {"non-existent", ""};

  // Test #1 InitSound(), should fail
  // TODO: need to test with a PC that has '/dev/dsp' available if
  // testing './configure --disable-pipewire --disable--pulseaudio'
  fprintf(stdout, "run test 1, KXL_InitSound(../docs/) and no *.wav files\n");
  KXL_InitSound("../docs/", notexist);
  if (KXL_SoundOk) {
    fprintf(stderr, "  test 1 failed\n");
    return -1;
  }
  fprintf(stdout, "  test 1 passed\n");

  // Test #3 EndSound(), empty *.wav file list, but should pass
  // TODO: need to test with a PC that has '/dev/dsp' available if
  // testing './configure --disable-pipewire --disable--pulseaudio'
  fprintf(stdout, "run test 2, KXL_EndSound() and no *.wav files\n");
  KXL_EndSound();
  fprintf(stdout, "  test 2 passed\n");

  // Test #3 InitSound(), should pass
  // TODO: need to test with a PC that has '/dev/dsp' available if
  // testing './configure --disable-pipewire --disable--pulseaudio'
  fprintf(stdout, "run test 3, KXL_InitSound(../docs/) and 3 sound*.wav files\n");
  KXL_InitSound("../docs/", snames);
  if (!KXL_SoundOk) {
    fprintf(stderr, "  test 3 failed\n");
    return -3;
  }
  fprintf(stdout, "  test 3 passed\n");

  // Test #4 EndSound(), we do have a *.wav file list, should pass
  // TODO: need to test with a PC that has '/dev/dsp' available if
  // testing './configure --disable-pipewire --disable--pulseaudio'
  fprintf(stdout, "run test 4, KXL_EndSound() and 3 sound*.wav file\n");
  KXL_EndSound();
  fprintf(stdout, "  test 4 passed\n");

  fprintf(stdout, "run test 5, KXL_PlaySound(../docs/sound1.wav)\n");
  KXL_InitSound("../docs/", snames);
  KXL_PlaySound(0, KXL_SOUND_PLAY);
  fprintf(stdout, "  test 5 passed\n");
  KXL_EndSound();

  fprintf(stdout, "done test_02\n");
  return 0;
}
