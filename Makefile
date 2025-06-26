NAME    := cub3d
CFLAGS  := -fsanitize=address -Wextra -Wall -Werror
LIBFT   := ./libft
MLX     := ./MLX42
BUILD   := $(MLX)/build

INCS    := -I./incs -I$(LIBFT)/incs -I$(MLX)/include
LIBS    := $(LIBFT)/libft.a $(BUILD)/libmlx42.a -ldl -lglfw -lm -pthread
SRCS    := $(shell find ./srcs -name "*.c")
OBJS    := ${SRCS:.c=.o}

all: $(BUILD)/libmlx42.a libft $(NAME)

$(BUILD)/libmlx42.a:
	@cmake -B $(BUILD) -S $(MLX) -DGLFW_USE_WAYLAND=OFF
	@cmake --build $(BUILD)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@rm -rf $(BUILD)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft
