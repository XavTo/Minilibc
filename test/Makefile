NAME_TEST		=	unit_tests

CFLAGS_TEST		=	--coverage -lcriterion -ldl

SRC_TEST 		= 	t_strlen.c		\
					t_strchr.c 		\
					t_strrchr.c		\
					t_memset.c		\
					t_strcmp.c 		\
					t_strncmp.c		\
					t_strstr.c		\
					t_strpbrk.c     \
					t_strcspn.c		\
					t_memcpy.c 		\
					t_strcasecmp.c	\
					t_memmove.c		\
					t_index.c		\
					t_rindex.c		\
					t_ffs.c 		\

OBJ_TEST		=	$(SRC_TEST:.c=.o)

all 	: 	$(NAME_TEST)

$(NAME_TEST) :	$(OBJ_TEST)
	@gcc -o $(NAME_TEST) $(OBJ_TEST) $(SRC) $(CFLAGS_TEST) $(CFLAGS)
	@./$(NAME_TEST)

clean :
		rm -f $(OBJS)
		rm -f *.o
		rm -f $(NAME)

fclean 	: 	clean
		rm -f $(NAME)

re 	: 	fclean all

tests_run:	clean unit_tests

gcovr:	tests_run
	@gcovr --exclude tests
	@gcovr --exclude tests --branch

gen_html:	unit_tests
	@(mkdir -p tests/coverage) > /dev/null
	@(lcov -c -d . --output-file tests/coverage/lcov) > /dev/null
	@(genhtml tests/coverage/lcov --output-directory tests/coverage) > /dev/null

html_run:	gen_html
	@(firefox tests/coverage/index.html) > /dev/null