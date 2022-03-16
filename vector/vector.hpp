#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "../utils/copy.hpp"
#include "../utils/distance.hpp"
#include "../utils/fill.hpp"
#include "../utils/equal.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
	//	Member types
	typedef T											value_type;
    typedef Allocator									allocator_type;
    typedef typename allocator_type::reference			reference;
    typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
    typedef typename allocator_type::pointer         	pointer;
    typedef typename allocator_type::const_pointer   	const_pointer;
    typedef pointer										iterator;
    typedef const_pointer								const_iterator;
	// typedef ft::reverse_iterator<iterator>          	reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;

private:
	size_type		_capacity;
	pointer			_begin;
	pointer			_end;
	allocator_type	_a;

public:
	//	Constructors
	explicit vector (const allocator_type& alloc = allocator_type())
		:	_capacity(),
			_begin(nullptr),
			_end(nullptr),
			_a(alloc)
	{
	}
	explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
		:	_capacity(n),
			_begin(nullptr),
			_end(nullptr),
			_a(alloc)
	{
		this->_begin = this->_a.allocate(n);
		this->_end = this->_begin;
		for (size_t i = 0; i < n ; i++)
		{
			this->_a.construct(this->_end, val);
			this->_end++;
		}
	}
	// template <class InputIterator>
    // vector (InputIterator first, InputIterator last,
	// 		const allocator_type& alloc = allocator_type())
	// 	:	_capacity(),
	// 		_begin(nullptr),
	// 		_end(nullptr),
	// 		_a(alloc)
	// {
	// 	// typename iterator_traits<InputIterator>::difference_type  n = ft::distance(first, last);
	// 	size_t  n = ft::distance(first, last);
	// 	reserve(n);
	// 	ft::copy(first, last, (iterator)this->_begin);
	// }
	vector (const vector& x)
		:	_capacity(x._capacity),
			_begin(nullptr),
			_end(nullptr),
			_a(x._a)
	{
		this->_begin = this->_a.allocate(this->_capacity);
		this->_end = this->_begin;
		for (size_t i = 0; i < x.size() ; i++)
		{
			this->_a.construct(this->_end, x[i]);
			this->_end++;
		}
	}

	vector& operator=(const vector& x);

	//	Destructor
	~vector()
	{
		clear();
		this->_a.deallocate(this->_begin, this->_capacity);
	}

	// 	Iterators
	iterator 				begin()
		{ return  iterator(this->_begin); }
	const_iterator 			begin() const
		{ return  const_iterator(this->_begin); }
	iterator 				end()
		{ return  iterator(this->_end); }
	const_iterator 			end() const
		{ return  const_iterator(this->_end); }

	// reverse_iterator 		rbegin()
	// 	{ return  reverse_iterator(this->_begin); }
	// const_reverse_iterator 	rbegin() const
	// 	{ return  const_reverse_iterator(this->_begin); }
	// reverse_iterator 		rend()
	// 	{ return  reverse_iterator(this->_end); }
	// const_reverse_iterator 	rend() const
	// 	{ return  const_reverse_iterator(this->_end); }

	//	Capacity
	size_type 	size() const
		{ return this->_end - this->_begin; }
	size_type 	max_size() const
		{ return this->_a.max_size(); }

	size_type 	capacity() const
		{ return this->_capacity; }
	bool 		empty() const
		{ return this->_begin == this->_end; }
	void 		reserve (size_type n);

	void 		resize (size_type n, value_type val = value_type());

	//	Element access
	reference 		operator[]( size_type n )
		{ return this->_begin[n]; }
	const_reference operator[] (size_type n) const
		{ return this->_begin[n]; }
	reference		at( size_type n );
	const_reference at (size_type n) const;

	reference 		front()			{ return reference(this->_begin); }
	const_reference front() const	{ return const_reference(this->_begin); }
	reference 		back()			{ return reference(*(this->_end - 1)); }
	const_reference back() const	{ return const_reference(*(this->_end - 1)); }

	//	Modifiers
	template <class InputIterator>
	void 		assign (InputIterator first, InputIterator last);
	void 		assign (size_type n, const value_type& val);

	void 		push_back (const value_type& val);
	void 		pop_back();

	iterator 	insert (iterator position, const value_type& val);
	void 		insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void 		insert (iterator position, InputIterator first, InputIterator last,
						typename std::enable_if<!std::is_integral<InputIterator>::value, bool>::type = true);

	iterator 	erase (iterator position);
	iterator 	erase (iterator first, iterator last);

	void 		swap (vector& x);

	void 		clear();

	//	Allocator
	allocator_type get_allocator() const
		{ return this->_a; }

};	//vector



template <typename T, typename Allocator>
vector<T, Allocator> &
vector<T, Allocator>::operator=(const vector<T, Allocator> & x)
{
    if (this != &x)
    {
		reserve(x.size());
		ft::copy(x.begin(), x.end(), begin()); // not sure if i need it
		this->_end = this->_begin + x.size();
    }
    return *this;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::reserve(size_type n)
{
	// if (n < max_size())
	// 	throw std::length_error("vector");
	if (n > capacity())
	{
		pointer tmp = this->_a.allocate(n);
		ft::copy(iterator(this->_begin), iterator(this->_end), tmp);
		clear();
		this->_a.deallocate(this->_begin, size()); // size or capacity?
		this->_begin = tmp;
		this->_end = tmp + n;
		this->_capacity = n;
	}
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::resize(size_type n, value_type val)
{
	// if (n > max_size())
	// 	throw std::length_error("vector");
	if (n < size())
	{
		pointer	tmp = this->_begin + n;
		while (tmp != this->_end)
		{
			this->_a.destroy(tmp);
			tmp++;
		}
		this->_end = this->_begin + n;
	}
	else if (n > size())
	{
		if (n > this->_capacity)
		{
			if (n <= this->_capacity * 2)
				reserve(this->_capacity * 2);
			else
				reserve(n);
		}
		for (size_t i = size(); i < n; i++)
		{
			this->_a.construct(this->_end, val);
			this->_end++;
		}
	}
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::at( size_type n )
{
	if (n >= size() || n < 0)
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at( size_type n ) const
{
	if (n >= size() || n < 0)
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template <typename T, typename Allocator>
void
swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
{
	vector<T, Allocator> temp = x;
	x = y;
	y = temp;
}

template <typename T, typename Allocator>
template <class InputIterator>
void
vector<T, Allocator>::assign(InputIterator first, InputIterator last)
{
	clear();
	insert(begin(), first, last);
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::assign(size_type n, const value_type& val)
{
	clear();
	insert(begin(), n, val);
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::push_back( const value_type& val )
{
	if (size() == capacity())
		reserve(size() + 1);
	back() = val;
	this->_end++;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::pop_back()
{
	this->_a.destroy(this->_end - 1);
	this->_end--;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert (iterator position, const value_type& val)
{
	insert(position, 1, val);
	return position;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::insert (iterator position, size_type n, const value_type& val)
{
	std::cout << "lol " << std::endl;
	if (n > max_size() || n + size() > max_size())
		throw std::length_error("Length error: vector::insert");
	size_type start = ft::distance(begin(), position);
	reserve(size() + n);
	ft::copy_backward(begin() + start, begin() + size() - n, begin() + start + n);
	ft::fill(begin() + start, begin() + start + n, val);
}

template <typename T, typename Allocator>
template <class InputIterator>
void
vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last,
							 typename std::enable_if<!std::is_integral<InputIterator>::value, bool>::type)
{
	// std::cout << "sucks" << std::endl;
	size_type n = ft::distance(first, last);
	if (n > max_size() || n + size() > max_size())
		throw std::length_error("Length error: vector::insert");
	size_type start = ft::distance(position, begin());
	size_type old_end = size();
	reserve(size() + n);
	std::cout << "size = " << size() << std::endl;
	ft::copy_backward(begin() + start, begin() + old_end, begin() + start + n);
	// for (int i = 0; i < 28; i++)
	// 	std::cout << *(position + i) << std::endl;
	for (size_t i = 0; i < n; i++)
	{
		std::cout << ": " << *first << std::endl;
		*(this->_begin + start + i) = *first;
		first++;
	}
	// ft::fill(begin() + start, begin() + start + n, first);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase (iterator position)
{
	return erase(position, position + 1);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase (iterator first, iterator last)
{
	pointer  tmp = last;
	ft::copy(last, end(), first);
	while (tmp != this->_end)
	{
		this->_a.destroy(tmp);
		tmp++;
	}
	this->_end -= ft::distance(first, last);
	return first;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::swap (vector& x)
{
	vector<T, Allocator> temp = *this;
	*this = x;
	x = temp;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::clear()
{
	pointer	tmp = this->_begin;	
	while (tmp != this->_end)
	{
		this->_a.destroy(tmp);
		tmp++;
	}
	this->_end = this->_begin;
}

//	Non-member function overloads
template <class T, class Alloc>
bool
operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool
operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool
operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool
operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool
operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template <class T, class Alloc>
bool
operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(rhs > lhs);
}


}   // ft

#endif	// VECTOR_HPP