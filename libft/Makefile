NAME	:= libft.a
CFLAGS	:= -g -Wextra -Wall -Werror

INCS	:= -I./incs
SRCS	:= $(shell find ./srcs -name "*.c")
OBJS	:= ${SRCS:.c=.o}
AR      := ar
ARFLAGS := rcs
RANLIB  = ranlib

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re