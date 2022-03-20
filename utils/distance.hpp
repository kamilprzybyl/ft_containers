#ifndef EQUAL_HPP
#define EQUAL_HPP

#include "iterator_traits.hpp"

namespace ft
{

template<class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	typename ft::iterator_traits<InputIterator>::difference_type	i;

	i = 0;
	while (first != last)
	{
		i++;
		first++;
	}
	return i;
}


} // ft

#endif
