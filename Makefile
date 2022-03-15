CC		=	clang++
CFLAGS	=	-Wextra -Wall -Werror -std=c++98
OUT		=	ft_containers
SRC		=	main.cpp
<<<<<<< HEAD
INC		=	vector/vector.hpp \
			utils/copy.hpp \
			utils/distance.hpp \
			utils/equal.hpp \
			utils/fill.hpp \
=======
INC		=	utils/copy.hpp \
			utils/distance.hpp \
			utils/fill.hpp \
			utils/equal.hpp \
>>>>>>> 4582d3dbab5dda581914a6a7aec55f9f3128595f
			utils/iterator_traits.hpp \
			utils/lexicographical_compare.hpp
OBJ		=	$(SRC:.cpp=.o)

all: $(OUT)

# %.o : %.cpp
# 	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(SRC) $(INC)
<<<<<<< HEAD
	$(CC) $(CFLAGS) $(SRC) -o $@ -D FT
=======
	$(CC) $(CFLAGS) $(SRC) -o $@
# $(OUT): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $@
>>>>>>> 4582d3dbab5dda581914a6a7aec55f9f3128595f

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(OUT)

re: fclean all
