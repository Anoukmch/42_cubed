NAME 		= cub3D
CC			= cc
CFLAGS		= -Wall -Werror -Wextra #-fsanitize=address
MLX			= $(LIBS_NAME) ./includes/libs/libmlx/libmlx42.a ./includes/libs/libmlx/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit
M_SRC		= main.c \
				init.c \
				movement.c \
				check_extension.c \
				colors.c \
				error_exit.c \
				parsing/get_map.c \
				parsing/check_map.c \
				parsing/read_map.c \
				parsing/parsing.c \
				DDA.c \
				event_handling.c \
				textures.c \
				utils/utils_free.c \
				utils/utils_parser.c \
				draw_textures.c \
				event_handling.c

M_SRCS		= $(addprefix ./sources/, $(M_SRC))

M_OBJS		= $(M_SRCS:.c=.o)

#INCLUDES = ./includes/cub3d.h

LIBS_NAME = ./includes/libs/libs.a

MLX_NAME = includes/libs/libmlx/libmlx42.a

#RULES
all: $(NAME)
#bonus ?

$(NAME): $(M_OBJS) $(LIBS_NAME) $(MLX_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(M_OBJS) $(MLX)

$(LIBS_NAME):
	make -sC includes/libs/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_NAME):
	$(MAKE) -C includes/libs/libmlx/

clean:
	make clean -C includes/libs/
	make fclean -C includes/libs/libmlx/
	@rm -f $(M_OBJS)

fclean: clean
	make fclean -C includes/libs/
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
