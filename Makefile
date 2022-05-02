CC		=	c++
CFLAGS	=	#-Wextra -Wall -Werror -std=c++98
OUT		=	ft_containers
SRC		=	main.cpp
OBJ		=	$(SRC:.cpp=.o)

all: $(OUT)

$(OUT): $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(OUT)

re: fclean all
