#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*rindex_sym)(char *, int) = NULL;

// Open lib and get calloc
static void get_rindex(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    rindex_sym = (char *(*)(char *, int))dlsym(handle, "rindex");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(rindex, simple_test, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(rindex(str, 'a'), rindex_sym(str, 'a'));
}

Test(rindex, simple_test_false, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    cr_assert_eq(rindex(str, 'b'), rindex_sym(str, 'b'));
}

Test(rindex, medium_test, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "Ceci est une très longue phrase avec plusieurs occurence la lettre a trouver.";
    cr_assert_eq(rindex(str, 'e'), rindex_sym(str, 'e'));
}

Test(rindex, medium_test_o, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "sssss";
    cr_assert_eq(rindex(str, 's'), rindex_sym(str, 's'));
}

Test(rindex, simple_test_o, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut\0";
    cr_assert_eq(rindex(str, '\0'), rindex_sym(str, '\0'));
}

Test(rindex, simple_test_c, .init=get_rindex, .fini=close_lib)
{
    if (rindex_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "";
    cr_assert_eq(rindex(str, '\0'), rindex_sym(str, '\0'));
}