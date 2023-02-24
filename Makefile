##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile for every projects
##

#################ALL SRC##################

SRC			=	src/server/initialyze_server.c \
				src/server/server_connection.c \
				src/server/server_handling.c \
				src/client/initialyze_client.c \
				src/client/client_connection.c \
				src/client/client_handling.c \
				src/client_commands/commands_engine.c \
				src/client_commands/data_mode_commands.c \
				src/client_commands/data_transfer_commands.c \
				src/client_commands/directory_handling_commands.c \
				src/client_commands/user_login_commands.c \
				src/client_commands/other_commands.c \

MAIN 		=	src/main.c

TESTS_SRC 	=	tests/test.c \

#################ALL OBJ##################

OBJ			=	$(SRC:%.c=%.o)

OBJ_MAIN	=	$(MAIN:%.c=%.o)

OBJT		=	$(TESTS_SRC:%.c=%.o)

#################ALL NAMES##################

NAME		=	myftp

TEST_NAME	=	unit_test

#################ALL FLAGS##################

CC			=	gcc

CFLAGS 		= 	 -I./include #-fprofile-arcs -ftest-coverage

TESTS_FLAGS = 	--coverage -lcriterion

#################ALL##################

all:	$(NAME)

$(NAME): 		$(OBJ) $(OBJ_MAIN)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(OBJ_MAIN)

#################CLEAN##################

clean:
	find . -name "*~" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	find . -name "unit_test" -delete
	find . -name "#*#" -delete
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

#################TESTS##################

tests_run: fclean $(OBJT) $(OBJ)
	$(CC) -o $(TEST_NAME) $(OBJT) $(OBJ) $(CFLAGS) $(TESTS_FLAGS)
	./$(TEST_NAME)

coverage:
	gcovr --exclude tests

branch_coverage:
	gcovr -b --exclude tests

#################PUSH##################

push:
	make fclean
	git add -A
	@read -p "Give a commit message " TAG \
    && git commit -m "$${TAG}"
	git push

#################RE##################

re: fclean all

.PHONY: clean fclean re all tests_run coverage
