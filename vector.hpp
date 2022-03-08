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
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type());
	template <class InputIterator>
    vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());
		:	_capacity(),
			_begin(nullptr),
			_end(nullptr),
			_a(alloc)
	{
	}
	vector (const vector& x);
		:	_capacity(),
			_begin(nullptr),
			_end(nullptr),
			_a(alloc)
	{
	}

	vector& operator= (const vector& x)

	//	Destructor
	~vector();

	// 	Iterators
	iterator 				begin();
	const_iterator 			begin() const;
	iterator 				end();
	const_iterator 			end() const;

	// reverse_iterator 		rbegin();
	// const_reverse_iterator 	rbegin() const;
	// reverse_iterator 		rend();
	// const_reverse_iterator 	rend() const;

	//	Capacity
	size_type 	size() const;
	size_type 	max_size() const;

	size_type 	capacity() const;
	bool 		empty() const;
	void 		reserve (size_type n);

	void 		resize (size_type n, value_type val = value_type());

	//	Element access
	reference 		operator[]( size_type pos );
	const_reference operator[] (size_type n) const;
	reference		at( size_type pos );
	const_reference at (size_type n) const;

	reference 		front();
	const_reference front() const;
	reference 		back();
	const_reference back() const;

	//	Modifiers
	template <class InputIterator>
	void 		assign (InputIterator first, InputIterator last);
	void 		assign (size_type n, const value_type& val);

	void 		push_back (const value_type& val);
	void 		pop_back();

	iterator 	insert (iterator position, const value_type& val);
	void 		insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void 		insert (iterator position, InputIterator first, InputIterator last);

	iterator 	erase (iterator position);
	iterator 	erase (iterator first, iterator last);

	void 		swap (vector& x);

	void 		clear();

	//	Allocator
	allocator_type get_allocator() const;

	//	Non-member function overloads
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
};


template <typename T, typename Allocator>
vector<T, Allocator>::vector(const allocator_type& alloc = allocator_type())
	:	_capacity(),
		_begin(nullptr),
		_end(nullptr),
		_a(alloc)
{
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	:	_capacity(),
		_begin(nullptr),
		_end(nullptr),
		_a(alloc)
{
}

// template <typename T, typename Allocator>
// vector<T, Allocator>::vector(InputIterator first, InputIterator last,
// 			const allocator_type& alloc = allocator_type()))
// 	:	_capacity(),
// 		_begin(),
// 		_end(),
// 		_a(alloc)
// {
// }

// template <typename T, typename Allocator>
// vector<T, Allocator>::vector(const vector& x)
// 	:	_capacity(),
// 		_begin(),
// 		_end(),
// 		_a(alloc)
// {
// }



}   // ft

#endif	// VECTOR_HPP