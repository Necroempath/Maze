#pragma once
#include <iostream>
#include <initializer_list>
#define ascending_factor 1.5f
#define descending_factor .7f

template <typename T>
class Vector
{
private:
	T* _data;
	size_t _size;
	size_t _capacity;

	static constexpr size_t CAPACITY = 10;

	Vector concat(const Vector& vector) const
	{
		Vector result(_size + vector._size);

		for (size_t i = 0; i < _size; i++)
		{
			result[i] = _data[i];
		}
		for (size_t i = _size, j = 0; i < result._size; i++, j++)
		{
			result[i] = vector._data[j];
		}

		return result;
	}

	void ResizeArray(const float factor)
	{
		_capacity *= factor;
		T* temp = new T[_capacity]();

		for (size_t i = 0; i < _size; i++)
		{
			temp[i] = _data[i];
		}

		delete[] _data;
		_data = temp;
	}

public:
	Vector() : _data(nullptr), _size(0), _capacity(CAPACITY) {}

	Vector(size_t size) : _size(size), _capacity(size* ascending_factor + 1)
	{
		_data = new T[_capacity]{};
	}

	Vector(const Vector& other) : _size(other._size), _capacity(other._capacity)
	{
		_data = new T[_capacity];

		for (size_t i = 0; i < _size; i++)
		{
			_data[i] = other._data[i];
		}
	}

	Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity)
	{
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	Vector(std::initializer_list<T> init_list) : _size(init_list.size()), _capacity(init_list.size()* ascending_factor)
	{
		_data = new T[_capacity];
		size_t index = 0;

		for (auto value : init_list)
		{
			_data[index++] = value;
		}
	}

	inline size_t Size() const
	{
		return _size;
	}

	T& operator[](size_t index)
	{
		if (index >= 0 && index < _size)
			return _data[index];
	}

	const T operator[](size_t index) const
	{
		if (index >= 0 && index < _size)
			return _data[index];
	}

	Vector& operator=(const Vector& vector)
	{
		if (&vector == this) return *this;

		_size = vector._size;
		_capacity = vector._capacity;
		_data = new T[_capacity];

		for (size_t i = 0; i < _size; i++)
		{
			_data[i] = vector._data[i];
		}

		return *this;
	}

	Vector& operator=(Vector&& vector) noexcept
	{
		if (&vector == this) return *this;

		_size = vector._size;
		_capacity = vector._capacity;
		_data = vector._data;

		vector._size = 0;
		vector._capacity = 0;
		vector._data = nullptr;

		return *this;
	}

	Vector operator+(const Vector& other) const
	{
		return concat(other);
	}

	Vector& operator+=(const Vector& other)
	{
		*this = concat(other);
		return *this;
	}

	void PushBack(T value)
	{
		if (!_data) return;

		if (_size == _capacity) ResizeArray(ascending_factor);

		_data[_size++] = value;
	}

	bool Insert(size_t index, T value)
	{
		if (index < 0 || index > _size) return 0;

		if (!_data) return 0;

		if (_size == _capacity) ResizeArray(ascending_factor);

		for (size_t i = _size; i > index; i--)
		{
			_data[i] = _data[i - 1];
		}

		_data[index] = value;

		_size++;
		return 1;
	}

	bool Pop()
	{
		if (!_data || _size == 0) return 0;

		if (--_size <= _capacity * 0.7f) ResizeArray(descending_factor);
		return 1;
	}

	bool Remove(size_t index)
	{
		if (!_data || _size == 0) return 0;

		if (index < 0 || index >= _size) return 0;

		for (size_t i = index; i < _size - 1; i++)
		{
			_data[i] = _data[i + 1];
		}

		return Pop();
	}

	~Vector()
	{
		delete[] _data;
	}
};

