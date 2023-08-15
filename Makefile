# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 11:32:45 by arepsa            #+#    #+#              #
#    Updated: 2023/08/15 12:45:19 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INCLUDES	=	includes
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRCS			=	pipex.c \
					pipex_path.c \
					pipex_utils.c
BONUS_SRCS		=	pipex_bonus.c \
					pipex_bonus_path.c \
					pipex_bonus_heredoc.c \
					pipex_bonus_utils.c

CC			= cc
LIBFLAGS	= ar -rcs
RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -g 

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	echo "Done compiling $(NAME)!"

bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	echo "Done compiling $(NAME) bonus!"

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
	$(RM) $(NAME) $(LIBFT)
	echo "Deleted $(NAME) files and $(LIBFT)"
	
re: fclean all

.PHONY: all clean fclean re
.SILENT:
