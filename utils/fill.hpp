#ifndef FILL_HPP
#define FILL_HPP

#include <iterator_traits.hpp>

namespace ft
{


template<typename iterator, typename InputIterator>
void
fill(InputIterator first, InputIterator last, typename ft::iterator_traits<Iterator>::value_type val)
{
	while (first != last)
		*first = val;
}

template<typename iterator, typename InputIterator>
void
fill(InputIterator first1, InputIterator last1, InputIterator first2)
{
	size_t i = 0;
	while (i != n)
		*first1 = *first2;
}


} // ft

#endif
