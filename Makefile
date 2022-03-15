CC		=	clang++
CFLAGS	=	-Wextra -Wall -Werror -std=c++98
OUT		=	ft_containers
SRC		=	main.cpp
INC		=	utils/copy.hpp \
			utils/distance.hpp \
			utils/fill.hpp \
			utils/equal.hpp \
			utils/iterator_traits.hpp \
			utils/lexicographical_compare.hpp
OBJ		=	$(SRC:.cpp=.o)

all: $(OUT)

# %.o : %.cpp

$(OUT): $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) -o $@
# $(OUT): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(OUT)

re: fclean all
