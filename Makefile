# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 10:56:34 by arepsa            #+#    #+#              #
#    Updated: 2023/08/07 16:06:20 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
BONUS_NAME	=	pipex_bonus
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INCLUDES	=	includes
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRCS			=	pipex.c
BONUS_SRCS		=	pipex_bonus.c

CC			= cc
LIBFLAGS	= ar -rcs
RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -g 

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	echo "Done compiling $(NAME)!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	echo "Done compiling $(BONUS_NAME)!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	echo "Creating .o files..."
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "Making libft..."
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR)
	echo "Deleted $(NAME) $(OBJS_DIR)"
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME) $(LIBFT)
	echo "Deleted $(NAME) files and $(LIBFT)"
	
re: fclean all

.PHONY: all clean fclean re bonus
#.SILENT:
