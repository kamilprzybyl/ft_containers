#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include "vector/vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))
// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {

// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout;
// << " "cout << "---" << std::endl;
// 	return (0);
// }

int main()
{


	try
	{
		// constructors (size, capacity)
		// ft::vector<int> v1;
		// for (int i = 0; i < 20; i++)
		// 	v1.push_back(i);
		// for (int i = 0; i < 20; i++)
		// 	std::cout << v1[i] << std::endl;
		// ft::vector<int> v2(20, 5);
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// v2.insert(v2.begin(), v1.begin() + 6, v1.begin() + 12);
		// std::cout << std::endl;
		// for (int i = 0; i < 20; i++)
		// 	std::cout << v2[i] << std::endl;
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// ft::vector<int> v3(v2.begin(), v2.begin() + 10);
		// std::cout << std::endl;
		// for (int i = 0; i < 10; i++)
		// 	std::cout << v3[i] << std::endl;
		// ft::vector<int> v4(v3);
		// std::cout << std::endl;
		// for (int i = 0; i < 10; i++)
		// 	std::cout << v4[i] << std::endl;
		// ft::vector<int> v5;
		// v5 = v4;
		// std::cout << std::endl;
		// for (int i = 0; i < 10; i++)
		// 	std::cout << v5[i] << std::endl;
		

		// assign (size, capacity)
		// ft::vector<int> v1;
		// std::cout << "---v1---" << std::endl;
		// std::cout << "size: " << v1.size() << std::endl;
		// std::cout << "capacity: " << v1.capacity() << std::endl;
		// v1.assign(30, -7);
		// ft::vector<int>::iterator it = v1.begin();
		// while (it != v1.end())
		// 	std::cout << *(it)++;
		// std::cout << std::endl;
		// std::cout << "size: " << v1.size() << std::endl;
		// std::cout << "capacity: " << v1.capacity() << std::endl;
		// std::cout << std::endl;
		// ft::vector<int> v2;
		// std::cout << "---v2---" << std::endl;
		// std::cout << "size: " << v2.size() << std::endl;
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// v2.assign(v1.begin(), v1.begin() + 10);
		// ft::vector<int>::iterator it2 = v2.begin();
		// while (it2 != v2.end())
		// 	std::cout << *(it2)++;
		// std::cout << std::endl;
		// std::cout << "size: " << v2.size() << std::endl;
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// std::cout << std::endl;
		// ft::vector<int> v3;
		// std::cout << "---v3---" << std::endl;
		// std::cout << "size: " << v3.size() << std::endl;
		// std::cout << "capacity: " << v3.capacity() << std::endl;
		// v3.assign(v1.begin(), v1.begin());
		// ft::vector<int>::iterator it3 = v3.begin();
		// while (it3 != v3.end())
		// 	std::cout << *(it3)++;
		// std::cout << std::endl;
		// std::cout << "size: " << v3.size() << std::endl;
		// std::cout << "capacity: " << v3.capacity() << std::endl;
		// std::cout << std::endl;

		// erase
		// ft::vector<int> v1;
		// std::cout << "---v1---" << std::endl;
		// std::cout << "size: " << v1.size() << std::endl;
		// std::cout << "capacity: " << v1.capacity() << std::endl;
		// v1.assign(30, -7);
		// ft::vector<int>::iterator it = v1.begin();
		// while (it != v1.end())
		// 	std::cout << *(it)++;
		// v1.erase(v1.begin() + 10, v1.begin() + 20);
		// std::cout << std::endl;
		// std::cout << "size: " << v1.size() << std::endl;
		// std::cout << "capacity: " << v1.capacity() << std::endl;
		// std::cout << std::endl;
		// ft::vector<int> v2;
		// std::cout << "---v2---" << std::endl;
		// std::cout << "size: " << v2.size() << std::endl;
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// v2.assign(v1.begin(), v1.begin() + 10);
		// // v2.erase(v2.begin() + 10, v2.begin() + 20); // should sef fault and it does
		// v2.erase(v2.begin(), v2.begin() + 10);
		// ft::vector<int>::iterator it2 = v2.begin();
		// while (it2 != v2.end())
		// 	std::cout << *(it2)++;
		// std::cout << std::endl;
		// std::cout << "size: " << v2.size() << std::endl;
		// std::cout << "capacity: " << v2.capacity() << std::endl;
		// std::cout << std::endl;
		// ft::vector<int> v3;
		// std::cout << "---v3---" << std::endl;
		// std::cout << "size: " << v3.size() << std::endl;
		// std::cout << "capacity: " << v3.capacity() << std::endl;
		// v3.assign(1, -999);
		// ft::vector<int>::iterator it3 = v3.begin();
		// while (it3 != v3.end())
		// 	std::cout << *(it3)++;
		// std::cout << std::endl;
		// std::cout << "size: " << v3.size() << std::endl;
		// std::cout << "capacity: " << v3.capacity() << std::endl;
		// std::cout << std::endl;

		// reverse_iterator
		ft::vector<int> v1;
		std::cout << "---v1---" << std::endl;
		std::cout << "size: " << v1.size() << std::endl;
		std::cout << "capacity: " << v1.capacity() << std::endl;
		v1.assign(30, -7);
		ft::vector<int>::iterator it = v1.begin();
		while (it != v1.end())
			std::cout << *(it)++;
		std::cout << std::endl;
		std::cout << "size: " << v1.size() << std::endl;
		std::cout << "capacity: " << v1.capacity() << std::endl;
		std::cout << std::endl;
		ft::vector<int> v2;
		std::cout << "---v2---" << std::endl;
		std::cout << "size: " << v2.size() << std::endl;
		std::cout << "capacity: " << v2.capacity() << std::endl;
		v2.assign(v1.begin(), v1.begin() + 10);
		ft::vector<int>::iterator it2 = v2.begin();
		while (it2 != v2.end())
			std::cout << *(it2)++;
		std::cout << std::endl;
		std::cout << "size: " << v2.size() << std::endl;
		std::cout << "capacity: " << v2.capacity() << std::endl;
		std::cout << std::endl;
		ft::vector<int> v3(16, 83);
		std::cout << "---v3---" << std::endl;
		std::cout << "size: " << v3.size() << std::endl;
		std::cout << "capacity: " << v3.capacity() << std::endl;
		v3.insert(v3.begin(), v1.begin(), v1.begin() + 5);
		ft::vector<int>::iterator it3 = v3.begin();
		while (it3 != v3.end())
			std::cout << *(it3)++;
		std::cout << std::endl;
		for (ft::vector<int>::reverse_iterator i = v3.rbegin(); i != v3.rend(); ++i )
		{
			std::cout << *(i);
		}
		std::cout << std::endl;
		std::cout << "size: " << v3.size() << std::endl;
		std::cout << "capacity: " << v3.capacity() << std::endl;
		std::cout << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
