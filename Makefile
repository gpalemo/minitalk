# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 18:37:18 by cmauley           #+#    #+#              #
#    Updated: 2026/03/23 18:37:42 by cmauley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==================== VARIABLES ==================== #

CC					= cc
CFLAGS				= -Wall -Wextra -Werror
INCLUDES			= -I include/ -I libft/ -I ft_printf/include/

# Exécutables
SERVER				= server
CLIENT				= client
NAME				= $(SERVER) $(CLIENT)

# Répertoires et fichiers
SRC_DIR				= src/
SRC_CLIENT			= $(SRC_DIR)client.c
SRC_SERVER			= $(SRC_DIR)server.c

OBJ_DIR				= obj/
OBJ_CLIENT			= $(OBJ_DIR)client.o
OBJ_SERVER			= $(OBJ_DIR)server.o

# Librairies
LIBFT_DIR			= libft/
LIBFT				= $(LIBFT_DIR)libft.a

FT_PRINTF_DIR		= ft_printf/
FT_PRINTF			= $(FT_PRINTF_DIR)libftprintf.a

LIBS				= $(LIBFT) $(FT_PRINTF)
LIB_FLAGS			= -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf

# ==================== RULES ==================== #

.PHONY: all clean fclean re

all: $(LIBFT) $(FT_PRINTF) $(SERVER) $(CLIENT)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER): $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) -o $@ $(LIB_FLAGS)
	@echo " $(SERVER) compiled"

$(CLIENT): $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $@ $(LIB_FLAGS)
	@echo " $(CLIENT) compiled"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@echo " Object files cleaned"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo " All cleaned"

re: fclean all
