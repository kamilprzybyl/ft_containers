#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template <class Iterator>
class reverse_iterator
{
private:
	iterator _iter;

public:
	// constructors
	reverse_iterator()
		: _iter()
	{
	}
	explicit reverse_iterator (iterator_type it)
		: _iter(it)
	{
	}
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it)
		: _iter(rev_it.base())
	{
	}

	~reverse_iterator()
	{
	}

	// base
	iterator_type base() const;
		{ return this->_iter; }

	reference operator*() const
		{ return this->_iter; }
};

} // ft

#endif
