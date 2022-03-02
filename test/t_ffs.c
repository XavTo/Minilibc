#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static int (*ffs_sym)(int) = NULL;

// Open lib and get calloc
static void get_ffs(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    ffs_sym = (int(*)(int))dlsym(handle, "ffs");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(ffs, simple_test, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(1), ffs_sym(1));
}

Test(ffs, simple_test_2, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(2), ffs_sym(2));
}

Test(ffs, simple_test_3, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(3), ffs_sym(3));
}

Test(ffs, simple_test_4, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(4), ffs_sym(4));
}

Test(ffs, simple_test_5, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(128), ffs_sym(128));
}

Test(ffs, simple_test_6, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(2147483647), ffs_sym(2147483647));
}

Test(ffs, simple_test_null, .init=get_ffs, .fini=close_lib)
{
    if (ffs_sym == NULL) {
        cr_skip_test();
    }
    cr_assert_eq(ffs(0), ffs_sym(0));
}