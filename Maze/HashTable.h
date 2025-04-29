#pragma once
#define ascendingFactor 2.0f
#define descendingFactor .75f
template <typename K, typename V>
struct Bucket
{
	K _key;
	V _value;

	bool _isVacant{ true };
};

template <typename K, typename V>
class HashTable
{
	Bucket<K, V>* _bucket;
	K _key;
	V _value;

	size_t _size;
	size_t _capacity;

	static constexpr size_t CAPACITY = 13;

	void Default()
	{
		_bucket = nullptr;
		_key = {};
		_value = {};
		_size = 0;
		_capacity = 0;
	}

	void Clear()
	{
		if (_bucket)
		{
			delete[] _bucket;
			_bucket = nullptr;
		}

		_key = {};
		_value = {};
		_size = 0;
		_capacity = 0;
	}

	void CopyFrom(const HashTable& other)
	{
		_key = other._key;
		_value = other._value;
		_size = other._size;
		_capacity = other._capacity;

		_bucket = new Bucket[_capacity];

		for (size_t i = 0; i < _size; i++)
		{
			_bucket[i] = other._bucket[i];
		}
	}

	bool isPrime(size_t num)
	{
		if (num <= 1) return false;
		if (num == 2) return true;

		double _sqrt = num / 2.0;


		for (int i = 0; i < 5; ++i)
			_sqrt = 0.5 * (_sqrt + num / _sqrt);

		size_t limit = static_cast<size_t>(_sqrt);

		for (size_t i = 2; i <= limit; i++)
		{
			if (num % i == 0)
				return 0;
		}

		return 1;
	}

	/// <summary>
	///	Identifies the nearest prime number to the given param.
	/// The second param determines whether the nearest prime is greater or smaller.
	/// </summary>
	size_t Prime(size_t num, bool greater = true)
	{
		size_t i = num;

		do { greater ? i++ : i--; } while (!isPrime(i));//check

		return i;
	}

	long Find(const K& key)
	{
		size_t index;

		for (size_t i = 0; ; i++)
		{
			index = (Hash(key) + i * Hash2(key)) % _capacity;

			if (_bucket[index]._key == key) return index;
			else if (_bucket[index]._isVacant) return -1;
		}
	}

	Bucket<K, V>* GetAllBuckets(size_t& size)
	{
		size = 0;

		auto temp = new Bucket<K, V>[_capacity];

		for (size_t i = 0; i < _capacity; i++)
		{
			if (!_bucket[i]._isVacant) temp[size++] = _bucket[i];
		}

		return temp;
	}

	void Resize(const float factor)
	{
		size_t size;
		auto arr_buckets = GetAllBuckets(size);

		_capacity = Prime(_capacity * factor, factor > 1);

		auto temp = new Bucket<K, V>[_capacity];

		delete[] _bucket;

		_bucket = temp;

		for (size_t i = 0; i < size; i++)
		{
			Add(arr_buckets[i]._key, arr_buckets[i]._value);
		}

	}

	size_t Hash(const K key)
	{
		return std::hash<K>{}(key);
	}

	size_t Hash2(const K& key)
	{
		return 1 + (Hash(key) % (_capacity - 1));
	}

public:
	HashTable() :_bucket(new Bucket<K, V>[CAPACITY]), _key{}, _value{}, _size(0), _capacity(CAPACITY) {};

	HashTable(const HashTable& other)
	{
		CopyFrom(other);
	};

	HashTable(HashTable&& other) noexcept : _bucket(other._bucket), _key(other._key), _value(other._value), _size(other._size), _capacity(other._capacity)
	{
		other.Default();
	};

	HashTable& operator=(const HashTable& other)
	{
		if (this == &other) return *this;

		CopyFrom(other);

		return *this;
	}

	HashTable& operator=(HashTable&& other) noexcept
	{
		if (this == &other) return *this;

		_key = other._key;
		_value = other._value;
		_size = other._size;
		_capacity = other._capacity;

		if (_bucket) delete[] _bucket;

		_bucket = other._bucket;

		other.Default();

		return *this;
	}

	V& operator()(K key, V value)
	{
		return Add(key, value);
	}

	V& Add(K key, V value)
	{
		size_t index;
		bool newItem = true;

		for (size_t i = 0; ; i++)
		{
			index = (Hash(key) + i * Hash2(key)) % _capacity;

			if (_bucket[index]._isVacant) break;
			if (key == _bucket[index]._key) { newItem = false; break; }
		}

		_bucket[index] = { key, value, false };

		_size = newItem ? _size + 1 : _size;

		if (_size >= _capacity * .4) Resize(ascendingFactor);

		return value;
	}

	V GetValue(const K& key)
	{

		if (!_size) throw std::runtime_error("Hash table is empty");

		long index = Find(key);

		if (index < 0) throw std::invalid_argument("Data by given key not found");

		return _bucket[index]._value;
	}

	void Remove(const K& key)
	{
		if (_size <= 0) return;

		long index = Find(key);

		if (index < 0) return; //object by given key doesn't exist

		_bucket[index] = { K{}, V{}, true };

		if (--_size < _capacity * .5 && _capacity > CAPACITY) Resize(descendingFactor);
	}

	float GetLoadFactor()
	{
		return (float)_size / _capacity;
	}

	~HashTable()
	{
		if (_bucket)
			delete[] _bucket;
	}
};
