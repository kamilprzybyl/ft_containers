#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
	//	Member types
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

private:
	Iterator _current;

public:
	// constructors
	reverse_iterator()
		: _current()
	{
	}
	explicit reverse_iterator ( Iterator const & it)
		: _current(it)
	{
	}
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it)
		: _current(rev_it.base())
	{
	}

	~reverse_iterator()
	{
	}

	// base
	Iterator base() const
		{ return this->_current; }

	reference operator*() const
		{ Iterator tmp = this->_current; return *--tmp; }
	pointer  operator->() const
		{ return &(operator*()); }
	reverse_iterator& operator++()
		{ --this->_current; return *this; }
	reverse_iterator  operator++(int)
		{ reverse_iterator tmp(*this); --this->_current; return tmp; }
	reverse_iterator  operator--(int)
		{ reverse_iterator tmp(*this); ++this->_current; return tmp; }
	reverse_iterator& operator--()
		{ ++this->_current; return *this; }
	reverse_iterator operator+ (difference_type n) const
		{ return reverse_iterator(this->_current - n); }
	reverse_iterator& operator+=(difference_type n)
		{ this->_current -= n; return *this; }
	reverse_iterator  operator- (difference_type n) const
		{ return reverse_iterator(this->_current + n); }
	reverse_iterator& operator-=(difference_type n)
		{ this->_current += n; return *this; }
	reference         operator[](difference_type n) const
		{ return *(*this + n); }
};


template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs,
				 const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+ (
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& rev_it)
{
	return rev_it + n;
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
{
	return rhs - lhs;
}



} // ft

#endif
