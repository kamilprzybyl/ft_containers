#ifndef COPY_HPP
#define COPY_HPP


namespace ft
{


template<typename iterator, typename InputIterator>
iterator
copy(InputIterator first, InputIterator last, iterator position)
{
	while (first != last)
	{
		*position = *first;
		first++;
		position++;
	}
	return position;
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
    // while (first != last)
	// {
    //     *(--position) = *(--last);
    // }
    // return position;
}


} // ft

#endif
