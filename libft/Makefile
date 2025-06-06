NAME    := libft.a
CC      := cc
CFLAGS  := -g -Wextra -Wall -Werror

INCS    := -I./incs
SRCS    := $(shell find ./srcs -name "*.c")
OBJS    := ${SRCS:.c=.o}
AR      := ar
ARFLAGS := rcs
RANLIB  := ranlib

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCS) && printf "Compiling: %s\n" "$(notdir $<)"

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re