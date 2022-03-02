#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char * (*memset_sym)(char *, int, size_t) = NULL;

// Open lib and get calloc
static void get_memset(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    memset_sym = (char *(*)(char *, int, size_t))dlsym(handle, "memset");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(memset, simple_test, .init=get_memset, .fini=close_lib)
{
    if (memset_sym == NULL) {
        cr_skip_test();
    }
    char	*str = malloc(10);

	cr_assert(memset(str, '1', 10) == memset_sym(str, '1', 10));
	free(str);
}

Test(memset, simple_test_letter, .init=get_memset, .fini=close_lib)
{
    if (memset_sym == NULL) {
        cr_skip_test();
    }
    char	*str = malloc(1000);

	str = memset_sym(str, 'X', 1000);
    for (size_t i = 0; i < 1000; i++)
		cr_assert(str[i] == 'X'); 
	free(str);
}

Test(memset, size_zero, .init=get_memset, .fini=close_lib)
{
    if (memset_sym == NULL) {
        cr_skip_test();
    }
    char	*str = malloc(100);

	cr_assert(memset(str, '1', 0) == memset_sym(str, '1', 0));
	free(str);
}