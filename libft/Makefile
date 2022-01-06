# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 10:07:13 by pgueugno          #+#    #+#              #
#    Updated: 2021/06/08 14:36:28 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#							Filename output								      #
###############################################################################

NAME		=	../libs/libft.a

###############################################################################
#						Sources and objects directories					      #
###############################################################################

HEADERS_DIR	=	../header
SRCS_DIR	=	srcs
OBJS_DIR	=	../objs
LIBS_DIR	=	../libs

###############################################################################
#							Sources filenames							      #
###############################################################################

SRCS		=	ft_atoi.c ft_lst_append.c ft_lstsize.c ft_putchar_fd.c\
				ft_strjoin.c ft_strtrim.c ft_bzero.c ft_lstadd_back.c\
				ft_memccpy.c ft_putendl_fd.c ft_strlcat.c ft_substr.c\
				ft_calloc.c ft_lstadd_front.c ft_memchr.c ft_putnbr.c\
				ft_strlcpy.c ft_tolower.c ft_isalnum.c ft_lstclear.c\
				ft_memcmp.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c\
				ft_isalpha.c ft_lstdelone.c ft_memcpy.c ft_putstr.c\
				ft_strmapi.c get_next_line.c ft_isascii.c ft_lstiter.c\
				ft_memmove.c ft_putstr_fd.c ft_strncmp.c ft_isdigit.c\
				ft_lstlast.c ft_memset.c ft_split.c ft_strnstr.c ft_isprint.c\
				ft_lstmap.c ft_numlen.c ft_strchr.c ft_strrchr.c ft_itoa.c\
				ft_lstnew.c ft_putchar.c ft_strdup.c ft_strstr.c ft_atol.c\
				ft_memdel.c ft_strncpy.c dlstend.c dlstnew.c dlstadd_back.c\
				dlstadd_front.c dlstclear.c dlstdelone.c dlstsize.c\
				dlstfind_node.c dlstinsert_node.c ft_strndup.c

###############################################################################
#							Commands and arguments						      #
###############################################################################

CC		=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -I$(HEADERS_DIR) -g
BUFSIZE		=	-D BUFFER_SIZE=32
RM		=	@rm -f
AR		=	@ar -rcs

###############################################################################
#								Defining colors							      #
###############################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m

###############################################################################
#									Compiling							      #
###############################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:	init $(NAME)

init:
	@ if test -f ../libs/libft.a;\
	then echo "$(_CYAN)[libft.a already created]";\
	else echo "$(_YELLOW)[Initialize libft]";\
	fi
	@ $(shell mkdir -p $(OBJS_DIR))
	@ $(shell mkdir -p $(LIBS_DIR))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				$(CC) $(CFLAGS) $(BUFSIZE) -c $< -o $@

$(NAME): $(OBJS)
		@ echo "\t$(_YELLOW)[Creating library...]"
		$(AR) $(NAME) $(OBJS)
		@ echo "$(_GREEN)[libft.a created]"

clean:
		@ echo "\t$(_RED)[cleaning libft objects files]"
		$(RM) $(OBJS)

fclean: clean
		@ echo "\t$(_RED)[cleaning libft objects and library files]"
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
