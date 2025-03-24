# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 13:23:14 by nponchon          #+#    #+#              #
#    Updated: 2025/03/24 14:53:34 by nponchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME 		= PmergeMe

# -=-=-=-=-    FLAG -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			= c++
CFLAGS		= -Werror -Wall -Wextra -std=c++98
DFLAGS		= -Wshadow -pedantic -g -Wconversion -fsanitize=address -fsanitize=leak

RM			= rm -fr

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC 		= 	main.cpp	\
				PmergeMe.cpp

HEADERS		=	PmergeMe.hpp

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME)

small: all
	./$(NAME) `shuf -i 1-100000 -n 10000 | tr '\n' ' '`

big: all
	./$(NAME) `shuf -i 1-1000000 -n 100000 | tr '\n' ' '`

example: all
	./$(NAME) 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7

leak:
	valgrind --leak-check=full ./$(NAME)

$(OBJDIR)/%.o: %.cpp Makefile $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(SRC) -o $(NAME)

clean: 
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re leak example small big