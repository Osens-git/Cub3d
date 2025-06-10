# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 13:22:33 by vluo              #+#    #+#              #
#    Updated: 2025/06/10 16:05:01 by vluo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	cub3d
BONUS_NAME		=	cub3d_bonus

SRC_DIR			=	src/
SRC_BONUS_DIR	=	bonus/src/

OBJ_DIR			=	obj/
OBJ_BONUS_DIR	=	bonus/obj/

INC				=	includes/
INC_BONUS		=	bonus/includes

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

MINILIBFLAGS	=	-Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

RED				=	\e[31m

BLUE			=	\e[34m

RESET			=	\e[0m

SRC				=	$(SRC_DIR)drawline.c $(SRC_DIR)drawrays.c	\
					$(SRC_DIR)drawmap.c							\
					$(SRC_DIR)get_min_ray.c						\
					$(SRC_DIR)utils.c $(SRC_DIR)utils2.c		\
					$(SRC_DIR)utils3.c							\
					$(SRC_DIR)handle_input.c $(SRC_DIR)cub3d.c	\

SRC_BONUS		=	$(SRC_BONUS_DIR)drawline.c $(SRC_BONUS_DIR)drawrays.c	\
					$(SRC_BONUS_DIR)draw_minimap.c							\
					$(SRC_BONUS_DIR)get_min_ray.c							\
					$(SRC_BONUS_DIR)utils.c $(SRC_BONUS_DIR)utils2.c		\
					$(SRC_BONUS_DIR)utils3.c								\
					$(SRC_BONUS_DIR)handle_input.c $(SRC_BONUS_DIR)cub3d_bonus.c	\

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
OBJ_BONUS		=	$(patsubst $(SRC_BONUS_DIR)%.c,$(OBJ_BONUS_DIR)%.o,$(SRC_BONUS))


LIBFT			=	libft/libft.a

all				:	$(NAME) $(BONUS_NAME)

$(LIBFT)		:
					$(MAKE) -C libft --no-print-directory

$(NAME)			:	$(LIBFT) $(OBJ_DIR) $(OBJ)
					@$(CC) $(CFLAGS) -I $(INC) $(OBJ) $(LIBFT) -o $(NAME) $(MINILIBFLAGS)
					@clear
					@echo "Compilation Done"
					@echo ""
					@echo "........                                                                         ........"
					@echo ""
					@echo ""
					@echo ""
					@echo "........                                  mcauchy-                               ........"
					@echo "........                                   vluo                                  ........"
					@echo ""

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
					@echo "$(BLUE)cub3d $(RESET): \e[92mCompiling\e[m $(notdir $<)...\n"

clean			:
					@$(MAKE) clean -C libft --no-print-directory
					@rm -rf $(OBJ_DIR)
					@rm -rf $(OBJ_BONUS_DIR)
					@echo "$(RED)- Objects deleted !$(RESET)"

fclean			:	clean
					@$(MAKE) fclean -C libft --no-print-directory
					@rm -rf $(NAME)
					@rm -rf $(BONUS_NAME)
					@echo "$(RED)- Executable deleted !$(RESET)"

re				:	fclean
					@make all --no-print-directory

bonus			:	$(BONUS_NAME)

$(BONUS_NAME)	:	$(LIBFT) $(OBJ_BONUS_DIR) $(OBJ_BONUS)
					@$(CC) $(CFLAGS) -I $(INC) $(OBJ_BONUS) $(LIBFT) -o $(BONUS_NAME) $(MINILIBFLAGS)
					@clear
					@echo "Bonus Compilation Done"

$(OBJ_BONUS_DIR)	:
					mkdir -p $(OBJ_BONUS_DIR)

$(OBJ_BONUS_DIR)%.o	:	$(SRC_BONUS_DIR)%.c
					@$(CC) $(CFLAGS) -I $(INC_BONUS) -c $< -o $@
					@echo "$(BLUE)cub3d_bonus $(RESET): \e[92mCompiling\e[m $(notdir $<)...\n"

.PHONY			:	all clean fclean re