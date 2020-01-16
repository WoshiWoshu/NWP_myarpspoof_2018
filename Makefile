##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for mychap
##

SRC	=	main.c\
		src/myarp.c\
		src/error.c\
		src/useful_functions.c\
		src/useful_functions_two.c\
		src/useful_functions_three.c\
		src/init.c\
		src/init_two.c\
		src/display_broadcast.c

INC	=	-I include

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	$(INC)

NAME	=	myARPspoof

all:	$(NAME)	clean

$(NAME):
	gcc -o $(NAME) $(SRC) -g3 $(CFLAGS) $(INC)

clean:
	rm -f *~ *.gcda *.gcno *.o
	rm -rf .vscode/

fclean:	clean
	rm -f $(NAME)

re:	fclean all
