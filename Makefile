NAME			=	libasm.so
NAME_TEST		=	unit_tests

ASM 			= 	nasm
ASMFLAGS 		=	-f elf64 -Iinclude/

CC				=	ld
CLINK 			=	-I/lib64/ld-linux-x86-64.so.2 -lc -s
CFLAGS			=	-fPIC  -shared
LDFLAGS 		=	-shared -Bsymbolic -Bsymbolic-functions
CFLAGS_TEST		=	--coverage -lcriterion -ldl

SRC				= src/strlen.asm		\
				  src/memset.asm		\
				  src/strcmp.asm		\
				  src/strncmp.asm		\
				  src/strstr.asm		\
				  src/strpbrk.asm		\
				  src/strcspn.asm		\
				  src/memcpy.asm 		\
				  src/strcasecmp.asm	\
				  src/memmove.asm		\
				  src/index.asm			\
				  src/rindex.asm		\
				  src/ffs.asm			\
				  src/memfrob.asm		\

SRC_TEST 		= test/test.c

OBJS			=	$(SRC:.asm=.o)
OBJ_TEST		=	$(SRC_TEST:.c=.o)

all 	: 	$(NAME)

$(NAME) :	$(OBJS)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.asm
		$(ASM) $(ASMFLAGS) $< -o $@

clean :
		rm -f $(OBJS)
		rm -f *.o
		rm -f $(NAME)

fclean 	: 	clean
		rm -f $(NAME)

re 	: 	fclean all

unit_tests:
	@rm -f test/unit_tests
	@(make -C test/) > /dev/null

gcovr:
	@rm -f test/unit_tests
	@(make gcovr -C test/)