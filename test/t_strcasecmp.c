#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static int (*strcasecmp_sym)(char *, char *) = NULL;

// Open lib and get calloc
static void get_strcasecmp(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strcasecmp_sym = (int (*)(char *, char *))dlsym(handle, "strcasecmp");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strcasecmp, simple_test_eq, .init=get_strcasecmp, .fini=close_lib)
{
    if (strcasecmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "BONJOUR";
    char str2[] = "salut";
    cr_assert(strcasecmp_sym(str, str2) < 0 , "reel : %d my : %d\n", strcasecmp(str, str2), strcasecmp_sym(str, str2));
}

Test(strcasecmp, simple_test_gr, .init=get_strcasecmp, .fini=close_lib)
{
    if (strcasecmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    char str2[] = "sAlUa";
    cr_assert_eq(strcasecmp(str, str2), strcasecmp_sym(str, str2));
}

Test(strcasecmp, simple_test_sm, .init=get_strcasecmp, .fini=close_lib)
{
    if (strcasecmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "SALU";
    char str2[] = "salua";
    cr_assert_eq(strcasecmp(str, str2), strcasecmp_sym(str, str2));
}

Test(strcasecmp, medium_test, .init=get_strcasecmp, .fini=close_lib)
{
    if (strcasecmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "bonjour2";
    char str2[] = "bonJouR";
    cr_assert_eq(strcasecmp(str, str2), strcasecmp_sym(str, str2));
}

Test(strcasecmp, medium_test_o, .init=get_strcasecmp, .fini=close_lib)
{
    if (strcasecmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "M";
    char str2[] = "O";
    cr_assert(strcasecmp(str, str2) == strcasecmp_sym(str, str2), "reel : %d my : %d\n", strcasecmp(str, str2), strcasecmp_sym(str, str2));
}