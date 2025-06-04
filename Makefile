# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 13:22:33 by vluo              #+#    #+#              #
#    Updated: 2025/06/04 18:46:29 by vluo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	cub3d

SRC_DIR			=	src/

OBJ_DIR			=	obj/

INC				=	includes/

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

MINILIBFLAGS	=	-Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

RED				=	\e[31m

BLUE			=	\e[34m

RESET			=	\e[0m

SRC				=	$(SRC_DIR)drawline.c						\
					$(SRC_DIR)drawmap.c	$(SRC_DIR)drawrays.c	\
					$(SRC_DIR)utils.c	$(SRC_DIR)cub3d.c		\

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

LIBFT			=	libft/libft.a

all				:	$(NAME)

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
					@echo "$(BLUE)minishell $(RESET): \e[92mCompiling\e[m $(notdir $<)...\n"

clean			:
					@$(MAKE) clean -C libft --no-print-directory
					@rm -rf $(OBJ_DIR)
					@echo "$(RED)- Objects deleted !$(RESET)"

fclean			:	clean
					@$(MAKE) fclean -C libft --no-print-directory
					@rm -rf $(NAME)
					@echo "$(RED)- Executable deleted !$(RESET)"

re				:	fclean
					@make all --no-print-directory

.PHONY			:	all clean fclean re