name = cub3d

all : 
	cc -Wall -Werror -Wextra libft/src/*.c -I libft/includes *.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -o cub3d