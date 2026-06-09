#include <stdlib.h>

#include "KXL.h"
#include "KXL-config.h" // included here for internal testing use only

extern KXL_Window *KXL_Root;

int main(int argc, char** argv)
{
  KXL_Image *bmp1, *bmp2;

  // Test #1 CreateWindow()
  fprintf(stdout, "run test 1, CreateWindow()\n");
  KXL_DisplayName("\0"); // startup default is empty
  KXL_CreateWindow(100,100, "CreateWindow test", \
                   KXL_EVENT_EXPOSURE_MASK |     \
                   KXL_EVENT_KEY_PRESS_MASK);

  if (KXL_Root->Display == NULL) {
    fprintf(stderr, "  failed test 1\n");
    return -1;
  }
  KXL_DeleteWindow();
  fprintf(stdout, "  test 1 passed\n");

  // Test #2 DisplayName()
  // Test creating a window with invalid $DISPLAY value.
  // This test should always fail.
  fprintf(stdout, "run test 2, DisplayName()\n");
  KXL_DisplayName("abcdefghijklmnopqrstuvwxyz");
  fprintf(stdout, "  ..run test 2\n");
  if ((KXL_CreateWindow0(100,100, "CreateWindow test", \
                         KXL_EVENT_EXPOSURE_MASK |     \
                         KXL_EVENT_KEY_PRESS_MASK)) == 0) {
    // we did not want it to pass, so it failed!
    KXL_DeleteWindow();
    fprintf(stderr, "  failed test 2\n");
    return -2;
  }
  // failed, so this went as planned! so it is a pass!
  fprintf(stdout, "  test 2 passed\n");

  // Test #3 DisplayName()
  // Test creating a window with a valid $DISPLAY value.
  // This test should always pass.
  fprintf(stdout, "run test 3, DisplayName()\n");
  KXL_DisplayName(":0"); // default_monitor=':0', first_monitor=':1'
  fprintf(stdout, "  ..run test 3\n");
  if ((KXL_CreateWindow0(100,100, "CreateWindow test", \
                         KXL_EVENT_EXPOSURE_MASK |     \
                         KXL_EVENT_KEY_PRESS_MASK))) {
    fprintf(stderr, "  failed test 3\n");
    return -3;
  }
  fprintf(stdout, "  test 3 passed\n");

  // Test #4 LoadBitmap()
  fprintf(stdout, "run test 4, LoadBitmap(../docs/sample.bmp)\n");
  // NOTE: you need to be in tests directory before running ./test_01
  bmp1 = KXL_LoadBitmap("../docs/sample.bmp", 0);

  fprintf(stdout, "  ..run test 4\n");
  if (bmp1 == NULL) {
    KXL_DeleteWindow();
    fprintf(stderr, "  failed test 4\n");
    return -4;
  }
  fprintf(stdout, "  test 4 passed\n");

  // Test #5 LoadBitmap()
  // Load AFL++ generated bmp which caused old KXL versions to go into an infinite loop
  // This test should always fail.
  fprintf(stdout, "run test 5, LoadBitmap(test_bmp_PXIpZM)\n");
  // NOTE: you need to be in tests directory before running ./test_01
  bmp2 = KXL_LoadBitmap("test_bmp_PXIpZM", 0);

  fprintf(stdout, "  ..run test 5\n");
  if (bmp2 != NULL) {
    KXL_DeleteImage(bmp1);
    KXL_DeleteWindow();
    fprintf(stderr, "  test 5 failed\n");
    return -5;
  }
  fprintf(stdout, "  test 5 passed\n");

  KXL_DeleteImage(bmp1);

  fprintf(stdout, "run test 6, KXL_DeleteImage(bmp2)\n");
  KXL_DeleteImage(bmp2); // try delete NULL! (crash now fixed)
  fprintf(stdout, "  test 6 passed\n");

  KXL_DeleteWindow();

  fprintf(stdout, "done test_01\n");
  return 0;
}
