#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
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
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }

int main()
{


	try
	{
		// ft::vector<int> v;

		// ft::vector<int> v2(v);

		// ft::vector<int> v3(20, 1);

		// v.get_allocator();
		// ft::vector<int>::size_type size = v.size();
		// std::cout << "size: " << size << std::endl;
		// ft::vector<int>::size_type max_size = v.max_size();
		// std::cout << "max_size: " << max_size << std::endl;
		// ft::vector<int>::size_type capacity = v.capacity();
		// std::cout << "capacity: " << capacity << std::endl;
		// ft::vector<int>::size_type empty = v.empty();
		// std::cout << "empty: " << empty << std::endl;
		// ft::vector<int>::iterator begin = v.begin();
		// std::cout << "begin: " << begin << std::endl;
		// std::cout << "operator[]: " << v[0] << std::endl;
		// ft::vector<int>::reference front = v.front();
		// std::cout << "front: " << front << std::endl;
		// ft::vector<int>::const_reference const_front = v.front();
		// std::cout << "const_front: " << const_front << std::endl;
		// ft::vector<int>::reference back = v.back();
		// std::cout << "back: " << back << std::endl;	// seg fault no clue if it's ok
		// std::cout << "[] operator: " << v3[19] << std::endl;
		// v3.pop_back();
		// std::cout << "[] operator after pop: " << v3[19] << std::endl;
		// v3.pop_back();
		// std::cout << "[] operator after pop: " << v3[19] << std::endl;
		// // std::cout << "push_back: " << v[0] << std::endl;	//should sef fault
		// v.push_back(24);
		// std::cout << "push_back: " << v[0] << std::endl;
		// v.push_back(19);
		// std::cout << "push_back: " << v[1] << std::endl;
		// v.push_back(-12);
		// std::cout << "push_back: " << v[2] << std::endl;
		// v.pop_back();
		// v.push_back(555);
		// std::cout << "pop and push: " << v[2] << std::endl;

		// ft::vector<int>	v4(v);

		// std::cout << "operator= " << v4[1] << std::endl;


		// int i = v.at(1);
		// std::cout << "at: " << i << std::endl;

		// ft::vector<int> v5;

		// v5.insert(v5.begin(), 10, 42);
		// std::cout << "insert: " << v5[0] << std::endl;
		// v5.insert(v5.begin() + 4, 123);
		// std::cout << "insert: " << v5[0] << std::endl;
		// std::cout << "insert: " << v5[4] << std::endl;
		// std::cout << "insert: " << v5[1] << std::endl;
		// v5.erase(v5.begin() + 3);
		// std::cout << "insert: " << v5[3] << std::endl;
		// v5.erase(v5.begin() + 2, v5.begin() + 7);
		// std::cout << "insert: " << v5[8] << std::endl;
		ft::vector<int> v6;
		for (int i = 0; i < 20; i++)
			v6.push_back(i);
		for (int i = 0; i < 20; i++)
			std::cout << v6[i] << std::endl;
		ft::vector<int> v7(20, 5);
		for (int i = 0; i < 20; i++)
			std::cout << v6[i] << std::endl;
		std::cout << "ooooo = " << v6[8] << std::endl;
		// v7.insert(v7.begin(), v6.begin() + 6, v6.begin() + 12);
		// std::cout << std::endl;
		// for (int i = 0; i < 20; i++)
		// 	std::cout << v7[i] << std::endl;
		
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
