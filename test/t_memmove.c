#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>

static void *handle;
static char *(*memmove_sym)(char *, char *, size_t) = NULL;

// Open lib and get calloc
static void get_memmove(void)
{
    if (handle != NULL) {
        return;
    }
    handle = dlopen("../libasm.so", RTLD_LAZY);
    if (handle == NULL) {
        cr_log_warn("Cannot open lib");
        return;
    }
    memmove_sym = (char *(*)(char *, char *, size_t))dlsym(handle, "memmove");
}
// Close lib
static void close_lib(void)
{
    if (handle == NULL) {
        return;
    }
    dlclose(handle);
}

Test(memmove, empty_string, .init=get_memmove, .fini=close_lib)
{
	char	*test = strdup("empty string");
	char	*test2 = strdup("");

	cr_assert_str_eq(memmove_sym(test, test2, 10), memmove(test, test2, 10));
}

Test(memmove, empty_string2, .init=get_memmove, .fini=close_lib)
{
	char	*test = strdup("");
	char	*test2 = strdup("empty string");

	cr_assert_str_eq(memmove_sym(test, test2, 10), memmove(test, test2, 10));
}

Test(memmove, full_null, .init=get_memmove, .fini=close_lib)
{
	char	*test = strdup("");
	char	*test2 = strdup("");

	cr_assert_str_eq(memmove_sym(test, test2, 1), memmove(test, test2, 1));
}

Test(memmove, return_value, .init=get_memmove, .fini=close_lib)
{
	char	*test = strdup("test");
	char	*test2 = strdup("bonj");

	cr_assert_str_eq(memmove(test, test2, 4), memmove_sym(test, test2, 4));
}

Test(memmove, return_value_2, .init=get_memmove, .fini=close_lib)
{
	char *test = strdup("ezae ezadazd sqd ze aezaeza dzaaedsqd q dqdsq d q dqz");

	cr_assert_str_eq(memmove(test + 15, test + 20, 11), memmove_sym(test + 15, test + 20, 11));
}

Test(memmove, med_test, .init=get_memmove, .fini=close_lib)
{
	char dest[] = "Hello World!";
    char my_dest[] = "Hello World!";
    char *src = dest + 2;
    char *my_src = my_dest + 2;

    cr_assert_str_eq(memmove(dest, src, 12), memmove_sym(my_dest, my_src, 12));
}