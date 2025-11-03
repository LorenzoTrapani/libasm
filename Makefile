NAME = libasm
CC = cc
NASM = nasm
CFLAGS = -Wall -Wextra -Werror -g
NASMFLAGS = -f elf64 -g

SRCS_C = main.c
SRCS_ASM = ft_strlen.s \
           ft_strcmp.s \
           ft_strdup.s \
           ft_strcpy.s \
           ft_read.s \
           ft_write.s

OBJS_C = $(SRCS_C:.c=.o)
OBJS_ASM = $(SRCS_ASM:.s=.o)
OBJS = $(OBJS_C) $(OBJS_ASM)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re