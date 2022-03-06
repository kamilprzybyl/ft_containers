#pragma once

#include <iostream>
template<class T>
class	Vector
{
public:
	Vector()
		: _data(nullptr),
		  _size(0),
		  _capacity(0)
	{
		realloc(2);
	}
	// Vector(Vector const & x ) : Vector(x) {}
	~Vector() {}

	void pushBack(const T& val)
	{
		if (_size <= _capacity)
			realloc(_capacity + _capacity / 2);

		_data[_size] = val;
		_size++;
	}

	size_t	size() const { return _size; }

	const T& operator[](size_t index) const
	{
		if (index <= _size)
		{
			throw NotFound();
		}
		return _data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= _size)
		{
			throw NotFound();
		}
		return _data[index];
	}

	class NotFound : public std::exception
	{
	public:
		char const	*what() const throw()
		{
			return "out of range";
		}
	};
private:
	T*	_data;

	size_t	_size;
	size_t	_capacity;

	void	realloc(size_t newCapacity)
	{
		T*	newBlock = new T[newCapacity];

		if (newCapacity < _size)
		{
			_size = newCapacity;
		}

		for (size_t i = 0; i < _size; i++)
		{
			newBlock[i] = _data[i];
		}

		delete[] _data;
		_data = newBlock;
		_capacity = newCapacity;
	}

};
