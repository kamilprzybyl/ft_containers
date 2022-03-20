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

}

#endif
