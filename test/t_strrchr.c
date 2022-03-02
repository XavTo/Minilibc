#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*strrchr_sym)(char *, int) = NULL;

// Open lib and get calloc
static void get_strrchr(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strrchr_sym = (char *(*)(char *, int))dlsym(handle, "strrchr");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strrchr, simple_test, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strrchr(str, 'a'), strrchr_sym(str, 'a'));
}

Test(strrchr, simple_test_false, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strrchr(str, 'b'), strrchr_sym(str, 'b'));
}

Test(strrchr, medium_test, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "Ceci est une très longue phrase avec plusieurs occurence la lettre a trouver.";
    cr_assert_eq(strrchr(str, 'e'), strrchr_sym(str, 'e'));
}

Test(strrchr, medium_test_o, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "sssss";
    cr_assert_eq(strrchr(str, 's'), strrchr_sym(str, 's'));
}

Test(strrchr, simple_test_o, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut\0";
    cr_assert_eq(strrchr(str, '\0'), strrchr_sym(str, '\0'));
}

Test(strrchr, simple_test_m, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut\0pa";
    cr_assert_eq(strrchr(str, 'p'), strrchr_sym(str, 'p'));
}

Test(strrchr, simple_test_l, .init=get_strrchr, .fini=close_lib)
{
    if (strrchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "\0";
    cr_assert_eq(strrchr(str, '\0'), strrchr_sym(str, '\0'));
}