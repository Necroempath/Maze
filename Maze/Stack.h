#pragma once
#include <iostream>
#include "Vector.h"

template <typename T>
class Stack;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack);

template <typename T>
class Stack
{
	Vector<T> _data;
	friend std::ostream& operator<< <>(std::ostream& os, const Stack<T>& stack);
public:
	const T& Top() const
	{
		if (_data.Size() < 1) throw std::runtime_error("No items in stack");
		return _data[_data.Size() - 1];
	}

	void Pop()
	{
		if (_data.Size() < 1) throw std::runtime_error("No items in stack");
		_data.Pop();
	}

	void Push(const T& value)
	{
		_data.PushBack(value);
	}

	size_t Size() const
	{
		return _data.Size();
	}

	bool Empty() const
	{
		return !_data.Size();
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack)
{
	for (size_t i = 0; i < stack.Size(); i++)
	{
		os << stack._data[i];
	}

	return os;
}