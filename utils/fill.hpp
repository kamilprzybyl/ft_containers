#ifndef FILL_HPP
#define FILL_HPP

#include "iterator_traits.hpp"

namespace ft
{


template <class ForwardIterator, class T>
void
fill(ForwardIterator first, ForwardIterator last, const T& val)
{
	while (first != last)
	{
		*first = val;
		++first;
	}
}

template<typename iterator, typename InputIterator>
void
fill(InputIterator first1, InputIterator last1, InputIterator first2)
{
	while (first1 != last1)
	{
		*first1 = *first2;
		++first1;
		++first2;
	}
}


} // ft

#endif
