#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*index_sym)(char *, int) = NULL;

// Open lib and get calloc
static void get_index(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    index_sym = (char *(*)(char *, int))dlsym(handle, "index");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(index, simple_test, .init=get_index, .fini=close_lib)
{
    if (index_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(index(str, 'a'), index_sym(str, 'a'));
}

Test(index, simple_test_false, .init=get_index, .fini=close_lib)
{
    if (index_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(index(str, 'b'), index_sym(str, 'b'));
}

Test(index, simple_test_o, .init=get_index, .fini=close_lib)
{
    if (index_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut\0";
    cr_assert_eq(index(str, '\0'), index_sym(str, '\0'));
}