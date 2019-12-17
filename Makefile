# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 14:36:51 by tmelvin           #+#    #+#              #
#    Updated: 2019/12/17 20:48:44 by tmelvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
SRCDIR := ./
LIBDIR := libft
SRC := ft_printf convert_alpha convert_numeric buffer get_info handle_width handle_flags tools
CC := gcc
CFLAGS := -Wall -Wextra -Werror
OPTIONS := -c
CFILES := $(patsubst %, $(SRCDIR)%.c, $(SRC))
OBJECTS := $(patsubst %, $(SRCDIR)%.o, $(SRC))

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(OPTIONS) -o $@ $<
$(NAME) : $(OBJECTS)
	$(MAKE) -C $(LIBDIR) all
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
clean :
	rm -f $(OBJECTS) $(BONUS_OBJECTS)
	$(MAKE) -C $(LIBDIR) clean
fclean : clean
	rm -f $(NAME)
	rm -f $(LIBDIR)/libft.a
re : fclean all

bonus : all 

.PHONY : all clean fclean re bonus

