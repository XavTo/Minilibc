#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static size_t (*strlen_sym)(char *) = NULL;

// Open lib and get calloc
static void get_strlen(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strlen_sym = (size_t(*)(char *))dlsym(handle, "strlen");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strlen, test_size, .init=get_strlen, .fini=close_lib)
{
    if (strlen_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "test";
    cr_assert_eq(strlen(str), strlen_sym(str));
}

Test(strlen, test_size_empty, .init=get_strlen, .fini=close_lib)
{
    if (strlen_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "";
    cr_assert_eq(strlen(str), strlen_sym(str));
}

Test(strlen, test_size_byte, .init=get_strlen, .fini=close_lib)
{
    if (strlen_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "test\0salut";
    cr_assert_eq(strlen(str), strlen_sym(str));
    close_lib();
}