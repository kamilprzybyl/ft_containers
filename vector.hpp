#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

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
		std::cout << "hi from default constructor" << std::endl;
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
		std::cout << "hi from fill constructor" << std::endl;
	}
	// template <class InputIterator>
    // vector (InputIterator first, InputIterator last,
	// 		const allocator_type& alloc = allocator_type())
	// 	:	_capacity(),
	// 		_begin(nullptr),
	// 		_end(nullptr),
	// 		_a(alloc)
	// {
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
		std::cout << "hi from copy constructor" << std::endl;
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
	// template <class InputIterator>
	// void 		assign (InputIterator first, InputIterator last);
	// void 		assign (size_type n, const value_type& val);

	void 		push_back (const value_type& val);
	void 		pop_back();

	iterator 	insert (iterator position, const value_type& val);
	void 		insert (iterator position, size_type n, const value_type& val);
	// template <class InputIterator>
	// void 		insert (iterator position, InputIterator first, InputIterator last);

	iterator 	erase (iterator position);
	iterator 	erase (iterator first, iterator last);

	void 		swap (vector& x);

	void 		clear();

	//	Allocator
	allocator_type get_allocator() const
		{ return this->_a; }

};	//vector

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
	if (n > capacity()
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
swap (vector<T,Allocator>& x, vector<T,Allocator>& y)
{
	vector<T, Allocator> temp = x;
	x = y;
	y = temp;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::push_back( const value_type& val )
{
	if (size() == capacity())
		reserve(size() + 1);
	// this->_a.construct(this->_end, val);
	this->_end++;
	back() = val;
	// this->_end++;
}

template <typename T, typename Allocator>
void
vector<T, Allocator>::pop_back()
{
	this->_a.destroy(this->_end - 1);
	this->_end--;
}

template <typename T, typename Allocator>
iterator
vector<T, Allocator>::insert (iterator position, const value_type& val)
{
	size_type n = position - this->_begin();
	insert(position, 1, val);
	return iterator(this->begin + n);
}

template <typename T, typename Allocator>
iterator
vector<T, Allocator>::insert (iterator position, size_type n, const value_type& val)
{

}

template <typename T, typename Allocator>
iterator
vector<T, Allocator>::erase (iterator position)
{
	return erase(position, position + 1);
}

template <typename T, typename Allocator>
iterator
vector<T, Allocator>::erase (iterator first, iterator last)
{
	iterator it = ft::copy(last, end(), first);
	pointer  tmp = this->_begin + (it - this->_begin);
	while (tmp != this->_end)
	{
		this->a.destroy(tmp);
		tmp++;
	}
	this->_end = last - first;
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
// template <class T, class Alloc>
// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// template <class T, class Alloc>
// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// template <class T, class Alloc>
// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// template <class T, class Alloc>
// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// template <class T, class Alloc>
// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// template <class T, class Alloc>
// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


}   // ft

#endif	// VECTOR_HPP