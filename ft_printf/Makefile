# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 23:20:02 by cmauley           #+#    #+#              #
#    Updated: 2026/03/02 17:51:28 by cmauley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# nom de la librairie
NAME = libftprintf.a

# compilateur
CC = cc

# flags
CFLAGS = -Wall -Wextra -Werror

# fichiers sources .c
SRC =	src/ft_printf.c src/ft_putstr.c src/ft_putchar.c src/ft_putnbr.c \
		src/ft_putunbr.c src/ft_putptr.c src/ft_puthex.c

# Liste des fichiers objets (.o) générés à partir des .c
# (remplace l’extension .c par .o automatiquement)
OBJ =	$(SRC:.c=.o)

# La cible "all" est lancée par défaut (quand on tape juste "make")
# Elle dépend de $(NAME), donc construit si besoin
all :$(NAME)

# créer libftprintf.a :
# - "ar rcs" crée une archive (librairie statique)
#   r = remplace / ajoute les fichiers
#   c = crée l’archive si elle n’existe pas
#   s = crée un index interne
$(NAME):	$(OBJ)
		ar rcs $(NAME) $(OBJ)

# Pour chaque fichier .o,compile le .c correspondant
# $< = nom du fichier source
# -o $@ = nom du fichier de sortie
%.o:	%.c
		$(CC) $(CFLAGS) -I include -c $< -o $@

# Supprime tous les fichiers objets (.o)
clean:
		rm -f $(OBJ)

# Supprime les objets + la librairie finale
fclean: clean
		rm -f $(NAME)

# Recompile tout depuis zéro
re : fclean all

# Empêche make de confondre ces noms avec des fichiers
.PHONY: all clean fclean re