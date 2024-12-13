# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    title.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 16:32:18 by mrouves           #+#    #+#              #
#    Updated: 2024/12/13 17:08:54 by mrouves          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
define TITLE

┌────────────────────────────────┐
│░█▄█░▀█▀░█▀█░▀█▀░▀█▀░█▀█░█░░░█░█│
│░█░█░░█░░█░█░░█░░░█░░█▀█░█░░░█▀▄│
│░▀░▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀▀▀░▀░▀│
└────────────────────────────────┘

endef
export TITLE
text-style 		= $(shell tput $1)$2$(shell tput sgr0)
PRINT_TITLE		:= $(shell $(info $(call text-style,setaf 6, $(TITLE))))