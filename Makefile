C_FLAGS =  -I
NAME = asm
SRCS = main.c parse.c clear_file.c getters.c work_with_str.c work_w_lable_instrct.c setters.c argums.c checker.c writer.c
##-Wall -Werror -Wextra
OBJECTS = $(SRCS:.c=.o)
LIBFT = ft_printf/
HEADER = ft_printf/includes/printf.h
LIB = ft_printf/libftprintf.a


all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(LIBFT)
	clang -o $(NAME) $(OBJECTS) $(LIB) -g

$(OBJECTS):	%.o: %.c
	clang $(C_FLAGS) $(HEADER) -o $@ -c $<

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
