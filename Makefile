CC		=	clang++
CFLAGS	=	-Wextra -Wall -Werror -std=c++98
OUT		=	ft_containers
SRC		=	main.cpp
INC		=	vector/vector.hpp \
			utils/copy.hpp \
			utils/distance.hpp \
			utils/equal.hpp \
			utils/fill.hpp \
			utils/iterator_traits.hpp \
			utils/lexicographical_compare.hpp
OBJ		=	$(SRC:.cpp=.o)

all: $(OUT)

# %.o : %.cpp
# 	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) -o $@ -D FT

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(OUT)

re: fclean all
