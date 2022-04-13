#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include "../utils/tree.hpp"
#include "../utils/utility.hpp"

namespace ft
{

template < class Key, class T, class Compare = std::less<Key>,
           class Allocator = std::allocator<ft::pair<const Key,T> > >
class map
{
public:
	//	Member types
	class value_compare;

	typedef	Key																					key_type;
	typedef	T																					mapped_type;
	typedef	ft::pair<const key_type, mapped_type>												value_type;
	typedef	Compare																				key_compare;
	typedef	Allocator																			allocator_type;
	typedef	typename allocator_type::reference													reference;
	typedef	typename allocator_type::const_reference											const_reference;
	typedef	typename allocator_type::pointer													pointer;
	typedef	typename allocator_type::const_pointer												const_pointer;
	typedef	typename allocator_type::size_type													size_type;
	typedef	typename allocator_type::difference_type											difference_type;

	typedef typename tree<value_type, value_compare, allocator_type>::iterator					iterator;
	typedef typename tree<value_type, value_compare, allocator_type>::const_iterator			const_iterator;
	typedef typename tree<value_type, value_compare, allocator_type>::reverse_iterator			reverse_iterator;
	typedef typename tree<value_type, value_compare, allocator_type>::const_reverse_iterator	const_reverse_iterator;

private:
	typedef	tree<value_type, value_compare, allocator_type>	_base;

	_base _tree;

public:
	//	Constructors
	explicit map (const key_compare& comp = key_compare(),
				  const allocator_type& alloc = allocator_type())
		: _tree(value_compare(comp), alloc) {}

	template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
			: _tree(value_compare(comp), alloc)
		{
			insert(first, last);
		}

	map (const map& x)
		: _tree(x._tree)
	{
		insert(x.begin(), x.end());
	}

	map& operator= (const map& x)
	{
		if (this != &x)
		{
			_tree.clear();
			// stuff
		}
		return *this;
	}

	//	Destructor
	~map() {}

	// test
	void print_tree()
	{_tree.prettyPrint();}

	// 	Iterators
	iterator 				begin() {return _tree.begin();}
	const_iterator 			begin() const {return _tree.begin();}
	iterator 				end() {return _tree.end();}
	const_iterator 			end() const {return _tree.end();}

	reverse_iterator 		rbegin() {return reverse_iterator(end());}
	const_reverse_iterator 	rbegin() const {return const_reverse_iterator(end());}
	reverse_iterator 		rend() {return reverse_iterator(begin());}
	const_reverse_iterator 	rend() const {return const_reverse_iterator(begin());}

	//	Capacity
	bool 		empty() const {return _tree.size() == 0;}
	size_type 	size() const {return _tree.size();}
	size_type 	max_size() const {return _tree.max_size();}

	//	Element access
	reference 		operator[]( size_type pos );
	const_reference operator[] (size_type n) const;

	//	Modifiers
	pair<iterator, bool> insert (const value_type& val)
		{return _tree.insert(val);}

	iterator 			insert (iterator position, const value_type& val)
		{return _tree.insert(val).first; (void)position;}

	template <class InputIterator>
		void 	insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				++first;
			}
		}

	void 		erase (iterator position) {return _tree.erase(position);}
	size_type 	erase (const key_type& k)
		{return _tree.erase(ft::make_pair(k, mapped_type()));}
	void 		erase (iterator first, iterator last)
		{_tree.erase(first, last);}

	void 		swap (map& x)
		{_tree.swap(x._tree);}
	void 		clear() {_tree.clear();}

	//	Observers
	key_compare key_comp() const
		{return _tree.value_comp().key_comp();}
	value_compare value_comp() const
		{return value_compare(_tree.value_comp().key_comp());}

	//	Allocator
	allocator_type get_allocator() const
		{return _tree.get_allocator();}

	//	Operations
	iterator 		find (const key_type& k)
		{return _tree.find(ft::make_pair(k, mapped_type()));}
	const_iterator 	find (const key_type& k) const
		{return _tree.find(ft::make_pair(k, mapped_type()));}

	size_type count (const key_type& k) const
		{return _tree.count(ft::make_pair(k, mapped_type()));}

	iterator 		lower_bound (const key_type& k)
		{return _tree.lower_bound(ft::make_pair(k, mapped_type()));}
	const_iterator 	lower_bound (const key_type& k) const
		{return _tree.lower_bound(ft::make_pair(k, mapped_type()));}

	iterator 		upper_bound (const key_type& k)
		{return _tree.upper_bound(ft::make_pair(k, mapped_type()));}
	const_iterator 	upper_bound (const key_type& k) const
		{return _tree.upper_bound(ft::make_pair(k, mapped_type()));}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{return _tree.equal_range(ft::make_pair(k, mapped_type()));}
	pair<iterator,iterator>             equal_range (const key_type& k)
		{return _tree.equal_range(ft::make_pair(k, mapped_type()));}
};


template <class Key, class T, class Compare, typename Allocator>
class map<Key, T, Compare, Allocator>::value_compare
{
	friend class map;

protected:
	key_compare comp;

	value_compare(key_compare c) : comp(c) {}
public:
	bool operator()(const value_type& x, const value_type& y) const
	{return comp(x.first, y.first);}
};


}   // ft

#endif	// MAP_HPP