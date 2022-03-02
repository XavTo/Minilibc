#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*strcspn_sym)(const char *, const char *) = NULL;

// Open lib and get calloc
static void get_strcspn(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strcspn_sym = (char *(*)(const char *, const char *))dlsym(handle, "strcspn");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strcspn, simple_test, .init=get_strcspn, .fini=close_lib)
{
    if (strcspn_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strcspn(str, "pkhyg"), strcspn_sym(str, "pkhyg"));
}

Test(strcspn, medium_test, .init=get_strcspn, .fini=close_lib)
{
    if (strcspn_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strcspn(str, "bcdspam"), strcspn_sym(str, "bcdspam"));
}

Test(strcspn, simple_test_false, .init=get_strcspn, .fini=close_lib)
{
    if (strcspn_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut tout le monde";
    cr_assert_eq(strcspn(str, "tulsa "), strcspn_sym(str, "tulsa "));
}

Test(strcspn, simple_test_empty, .init=get_strcspn, .fini=close_lib)
{
    if (strcspn_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "";
    cr_assert_eq(strcspn(str, "bonjour"), strcspn_sym(str, "bonjour"));
}