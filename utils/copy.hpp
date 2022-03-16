#ifndef COPY_HPP
#define COPY_HPP

#include "distance.hpp"

namespace ft
{


template<class InputIterator, class OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator result)
{
	while (first != last)
	{
		*result = *first;
		++result;
		++first;
	}
	return result;
}

template<typename iterator, typename InputIterator>
iterator
copy_backward(InputIterator first, InputIterator last, iterator position)
{
	first--;
	last--;
	size_t n = ft::distance(first, last);
	position = position + n - 1;
	while (last != first)
	{
		*position = *last;
		last--;
		position--;
	}
	return position + n;
}


} // ft

#endif
