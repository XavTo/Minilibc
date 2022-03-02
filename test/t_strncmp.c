#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static int (*strncmp_sym)(char *, char *, size_t) = NULL;

// Open lib and get calloc
static void get_strncmp(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strncmp_sym = (int (*)(char *, char *, size_t))dlsym(handle, "strncmp");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strncmp, simple_test_eq, .init=get_strncmp, .fini=close_lib)
{
    if (strncmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    char str2[] = "salut";
    cr_assert_eq(strncmp(str, str2, 3), strncmp_sym(str, str2, 3));
}

Test(strncmp, simple_test_gr, .init=get_strncmp, .fini=close_lib)
{
    if (strncmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    char str2[] = "salua";
    cr_assert_eq(strncmp(str, str2, 9), strncmp_sym(str, str2, 9));
}

Test(strncmp, simple_test_sm, .init=get_strncmp, .fini=close_lib)
{
    if (strncmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salu";
    char str2[] = "salua";
    cr_assert_eq(strncmp(str, str2, 5), strncmp_sym(str, str2, 5));
}