#include <stdlib.h>
#include <check.h>

#include "KXL.h"
#include "KXL-config.h"

extern KXL_Window *KXL_Root;
extern Bool KXL_SoundOk;

START_TEST (test_CreateWindow)
{
    KXL_CreateWindow(100, 100, "CreateWindow test",
                   KXL_EVENT_EXPOSURE_MASK |
                   KXL_EVENT_KEY_PRESS_MASK);

    ck_assert( KXL_Root->Display != NULL );
    KXL_DeleteWindow();
}
END_TEST

// Test creating a window with invalid $DISPLAY value.
// This test should always fail.
START_TEST (test_CreateWindow2)
{
    KXL_DisplayName("abcdefghijklmnopqrstuvwxyz");
    KXL_CreateWindow(100, 100, "CreateWindow test",
                   KXL_EVENT_EXPOSURE_MASK |
                   KXL_EVENT_KEY_PRESS_MASK);
    ck_assert(!KXL_Root->Display);
}
END_TEST

START_TEST(test_LoadBitmap)
{
    KXL_CreateWindow(100, 100, "CreateWindow test",
                   KXL_EVENT_EXPOSURE_MASK |
                   KXL_EVENT_KEY_PRESS_MASK);

    KXL_Image *bmp = KXL_LoadBitmap("../docs/sample.bmp", 0);
    ck_assert(bmp != NULL);
    KXL_DeleteImage(bmp);

    // Load AFL++ generated bmp which used to cause old KXL versions to go into an infinite loop
    bmp = KXL_LoadBitmap("test_bmp_PXIpZM", 0);
    ck_assert(!bmp);
    KXL_DeleteWindow();
}
END_TEST

#ifdef USE_PIPEWIREAUDIO
START_TEST(test_InitSound)
{
    char *snames[] = {"sound1", ""};
    KXL_InitSound("../docs/", snames);
    ck_assert(KXL_SoundOk);
    KXL_EndSound();
    char *notexist[] = {"non-existent", ""};
    KXL_InitSound("/dev/random/foo", notexist);
    ck_assert(!KXL_SoundOk);
    KXL_EndSound();
}
END_TEST
#else
#ifdef USE_PULSEAUDIO
START_TEST(test_InitSound)
{
    char *snames[] = {"sound1", ""};
    KXL_InitSound("../docs/", snames);
    ck_assert(KXL_SoundOk);
    KXL_EndSound();
    char *notexist[] = {"non-existent", ""};
    KXL_InitSound("/dev/random/foo", notexist);
    ck_assert(!KXL_SoundOk);
    KXL_EndSound();
}
END_TEST
#endif
#endif

Suite * KXL_suite(void)
{
    Suite *s;
    TCase *KXL_core;

    s = suite_create("KXL tests");
    KXL_core = tcase_create("Core tests");

    tcase_add_test(KXL_core, test_CreateWindow);
    tcase_add_exit_test(KXL_core, test_CreateWindow2, 1);
    tcase_add_test(KXL_core, test_LoadBitmap);
#ifdef USE_PIPEWIREAUDIO
    tcase_add_test(KXL_core, test_InitSound);
#else
#ifdef USE_PULSEAUDIO
    tcase_add_test(KXL_core, test_InitSound);
#endif
#endif
    suite_add_tcase(s, KXL_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = KXL_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
