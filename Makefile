NAME = libasm.a
TEST = test
CC = cc
NASM = nasm
AR = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
NASMFLAGS = -f elf64 -g

SRCS_ASM = ft_strlen.s \
           ft_strcmp.s \
           ft_strdup.s \
           ft_strcpy.s \
           ft_read.s \
           ft_write.s

OBJS_ASM = $(SRCS_ASM:.s=.o)

all: $(NAME)

$(NAME): $(OBJS_ASM)
	$(AR) $(NAME) $(OBJS_ASM)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

$(TEST): $(NAME) main.o
	$(CC) $(CFLAGS) main.o -L. -lasm -o $(TEST)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_ASM) main.o

fclean: clean
	$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test