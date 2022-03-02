#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*strpbrk_sym)(const char *, const char *) = NULL;

// Open lib and get calloc
static void get_strpbrk(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strpbrk_sym = (char *(*)(const char *, const char *))dlsym(handle, "strpbrk");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strpbrk, simple_test, .init=get_strpbrk, .fini=close_lib)
{
    if (strpbrk_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strpbrk(str, "salut"), strpbrk_sym(str, "salut"));
}

Test(strpbrk, medium_test, .init=get_strpbrk, .fini=close_lib)
{
    if (strpbrk_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strpbrk(str, "bcld"), strpbrk_sym(str, "bcld"));
}

Test(strpbrk, simple_test_false, .init=get_strpbrk, .fini=close_lib)
{
    if (strpbrk_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut tout le monde";
    cr_assert_eq(strpbrk(str, "frik"), strpbrk_sym(str, "frik"));
}

Test(strpbrk, simple_test_empty, .init=get_strpbrk, .fini=close_lib)
{
    if (strpbrk_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "";
    cr_assert_eq(strpbrk(str, "bonjour"), strpbrk_sym(str, "bonjour"));
}