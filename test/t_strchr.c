#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*strchr_sym)(char *, int) = NULL;

// Open lib and get calloc
static void get_strchr(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strchr_sym = (char *(*)(char *, int))dlsym(handle, "strchr");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strchr, simple_test, .init=get_strchr, .fini=close_lib)
{
    if (strchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strchr(str, 'a'), strchr_sym(str, 'a'));
}

Test(strchr, simple_test_false, .init=get_strchr, .fini=close_lib)
{
    if (strchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(strchr(str, 'b'), strchr_sym(str, 'b'));
}

Test(strchr, simple_test_o, .init=get_strchr, .fini=close_lib)
{
    if (strchr_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut\0";
    cr_assert_eq(strchr(str, '\0'), strchr_sym(str, '\0'));
}