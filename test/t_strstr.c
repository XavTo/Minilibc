#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*strstr_sym)(const char *, const char *) = NULL;

// Open lib and get calloc
static void get_strstr(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strstr_sym = (char *(*)(const char *, const char *))dlsym(handle, "strstr");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strstr, simple_test, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strstr(str, "salut"), strstr_sym(str, "salut"));
}

Test(strstr, medium_test, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut tout le monde";
    cr_assert_eq(strstr(str, "tout"), strstr_sym(str, "tout"));
}

Test(strstr, simple_test_false, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut tout le monde";
    cr_assert_eq(strstr(str, "bonjour"), strstr_sym(str, "bonjour"));
}

Test(strstr, simple_test_empty, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "";
    cr_assert_eq(strstr(str, "bonjour"), strstr_sym(str, "bonjour"));
}

Test(strstr, medium_test_mul, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "bonbonjour";
    cr_assert_eq(strstr(str, "bonjour"), strstr_sym(str, "bonjour"));
}

Test(strstr, medium_test_empty, .init=get_strstr, .fini=close_lib)
{
    if (strstr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strstr(str, ""), strstr_sym(str, ""));
}