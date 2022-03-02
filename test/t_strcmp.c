#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static int (*strcmp_sym)(char *, char *) = NULL;

// Open lib and get calloc
static void get_strcmp(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    strcmp_sym = (int (*)(char *, char *))dlsym(handle, "strcmp");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(strcmp, simple_test_eq, .init=get_strcmp, .fini=close_lib)
{
    if (strcmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    char str2[] = "salut";
    cr_assert_eq(strcmp(str, str2), strcmp_sym(str, str2));
}

Test(strcmp, simple_test_gr, .init=get_strcmp, .fini=close_lib)
{
    if (strcmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salut";
    char str2[] = "salua";
    cr_assert_eq(strcmp(str, str2), strcmp_sym(str, str2));
}

Test(strcmp, simple_test_sm, .init=get_strcmp, .fini=close_lib)
{
    if (strcmp_sym == NULL) {
        cr_skip_test();
    }
    char str[] = "salu";
    char str2[] = "salua";
    cr_assert_eq(strcmp(str, str2), strcmp_sym(str, str2));
}