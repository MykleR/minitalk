# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 18:27:35 by mrouves           #+#    #+#              #
#    Updated: 2024/12/15 20:03:22 by mrouves          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources/pretty_compile.mk
include sources/sources_server.mk
include sources/sources_client.mk
NAME_CLIENT 	:= client
NAME_SERVER		:= server

DIR_HEADERS		:= headers
DIR_SOURCES		:= sources
DIR_OBJS		:= .objs
DIR_LIB			:= lib

DIR_LIBFT		:= $(DIR_LIB)/libft
LIBFT_HEADERS	:= $(DIR_LIBFT)/headers
LIBFT			:= $(DIR_LIBFT)/libft.a

OBJS_SERVER		:= $(addprefix $(DIR_OBJS)/, $(SOURCES_SERVER:%.c=%.o))
OBJS_CLIENT		:= $(addprefix $(DIR_OBJS)/, $(SOURCES_CLIENT:%.c=%.o))

CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -g
IFLAGS			:= -I $(DIR_HEADERS) -I $(LIBFT_HEADERS)
DIR_DUP			= mkdir -p $(@D)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@
	@printf "$(BOLD)$@$(NO_COLOR) compiled $(OK_COLOR)successfully$(NO_COLOR)\n"

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@
	@printf "$(BOLD)$@$(NO_COLOR) compiled $(OK_COLOR)successfully$(NO_COLOR)\n"

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory -j

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.c
	@$(DIR_DUP)
	@$(call run_and_test,$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@)

clean:
	@rm -rf $(DIR_OBJS)
	@printf "Cleaned $(BOLD)$(DIR_OBJS)$(NO_COLOR)\n"

fclean: clean
	@rm -f $(NAME_CLIENT)
	@rm -f $(NAME_SERVER)
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory fclean
	@printf "Cleaned $(BOLD)$(NAME_CLIENT)$(NO_COLOR)\n"
	@printf "Cleaned $(BOLD)$(NAME_SERVER)$(NO_COLOR)\n"

re: fclean all

.PHONY: clean fclean re all
