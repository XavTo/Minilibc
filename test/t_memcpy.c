#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char *(*memcpy_sym)(char *, char *, size_t) = NULL;

// Open lib and get calloc
static void get_memcpy(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    memcpy_sym = (char *(*)(char *, char *, size_t))dlsym(handle, "memcpy");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(memcpy, empty_string, .init=get_memcpy, .fini=close_lib)
{
	char	*test = strdup("empty string");
	char	*test2 = strdup("");

	cr_assert(memcpy_sym(test, test2, 10) == test);
}

Test(memcpy, empty_string2, .init=get_memcpy, .fini=close_lib)
{
	char	*test = strdup("");
	char	*test2 = strdup("empty string");

	cr_assert(memcpy_sym(test, test2, 10) == test);
}

Test(memcpy, full_null, .init=get_memcpy, .fini=close_lib)
{
	char	*test = strdup("");
	char	*test2 = strdup("");

	cr_assert(memcpy_sym(test, test2, 1) == test);
}

Test(memcpy, return_value, .init=get_memcpy, .fini=close_lib)
{
	char	*test = strdup("test");
	char	*test2 = strdup("care");

	cr_assert(memcpy(test, test2, 4) == memcpy_sym(test, test2, 4));
}