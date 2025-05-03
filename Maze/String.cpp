#include "string.h"
#define ascending_factor 1.5f
#define descending_factor .7f

String::String() { Default(); }

String::String(const char* str)
{
	if (!str)
	{
		Default();
		return;
	}

	copy(*this, str);
}

String::String(const size_t len) : _len(len), _capacity(_len* ascending_factor + 1)
{
	_string = new char[_capacity];
}

String::String(const String& other)
{
	if (!other._string)
	{
		Default();
		return;
	}

	copy(*this, other._string);
}

String::String(String&& other) noexcept { Init(other); other._string = nullptr; }

String& String::operator=(const String& other)
{
	copy(*this, other._string);
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this == &other || !other._string) return *this;

	Init(other);

	other._string = nullptr;
	return *this;
}

String& String::operator=(const char* str)
{
	copy(*this, str);
	return *this;
}

String String::operator+(const String& str) const
{
	String temp(*this);
	concat(temp, str._string);

	return temp;
}

String String::operator+(const char* str) const
{
	String temp(*this);
	concat(temp, str);

	return temp;
}

String& String::operator+=(const String& str)
{
	*this = *this + str;
	return *this;
}

String& String::operator+=(const char* str)
{
	*this = *this + str;
	return *this;
}

String String::operator*(const size_t count) const
{
	String temp(*this);
	repeat(temp, _string, count);
	return temp;
}

String& String::operator*=(const size_t count)
{
	repeat(*this, _string, count);
	return *this;
}

bool String::operator==(const String& str) const
{
	return compare(str._string);
}

bool String::operator==(const char* str) const
{
	return compare(str);
}

const char String::operator[](const size_t index) const
{
	if (index >= 0 && index < _len)	return _string[index];
}

char& String::operator[](size_t index)
{
	if (index >= 0 && index < _len)	return _string[index];
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str._string;
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buffer[100];
	is >> buffer;
	str = String(buffer);
	return is;
}

void String::Default()
{
	_string = new char[1] {'\0'};
	_len = 0;
	_capacity = CAPACITY;
}

void String::Init(const String& str)
{
	_string = str._string;
	_len = str._len;
	_capacity = str._capacity;
}

size_t String::length(const char* str) const
{
	size_t size = 0;

	while (str[size]) size++;

	return size;
}

void String::copy(String& dest, const char* source) const
{
	if (_string == source || !source) return;

	dest._len = length(source);
	dest._capacity = _len * ascending_factor;
	dest._string = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		dest._string[i] = source[i];
	}

	dest._string[_len] = '\0';
}

void String::concat(String& dest, const char* source) const
{
	size_t source_len = dest._len + length(source);
	dest._len += source_len;
	dest._capacity = dest._len * ascending_factor;

	dest._string = new char[dest._capacity];

	for (size_t i = 0; i < dest._len; i++)
	{
		dest._string[i] = dest._string[i];
	}

	for (size_t i = dest._len, j = 0; i < source_len; i++, j++)
	{
		dest._string[i] = source[j];
	}
	dest._string[source_len] = '\0';
}

void String::repeat(String& dest, const char* source, const short count) const
{
	if (count < 0) return;
	if (count == 0) { dest.Default(); return; }

	size_t source_len = length(source);

	dest._len = source_len * count;
	dest._capacity = _len * ascending_factor;
	dest._string = new char[dest._capacity];

	for (size_t i = 0; i < dest._len; i++)
	{
		dest._string[i] = source[i % source_len];
	}

	dest._string[dest._len] = '\0';
}

bool String::compare(const char* str) const
{
	if (_len != length(str)) return 0;

	for (size_t i = 0; i < _len; i++)
	{
		if (_string[i] != str[i]) return 0;
	}
	return 1;
}

long String::find(const char* str) const
{
	size_t str_len = length(str);

	for (size_t i = 0, j = 0; i < _len - (str_len - j - 1); i++)
	{
		if (_string[i] == str[j])
		{
			if (++j == str_len) return i - j + 1;
		}
		else if (j > 0) { j = 0; i--; }
	}

	return -1;
}

void String::remove(const size_t index, const size_t len)
{
	for (size_t i = index; i < _len - len; i++)
	{
		_string[i] = _string[i + len];
	}
	_len -= len;
	_string[_len] = '\0';

	if (_capacity * descending_factor >= _len) ResizeString(descending_factor);
}

void String::ResizeString(const float factor)
{
	_capacity *= factor;

	char* temp = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		temp[i] = _string[i];
	}
	temp[_len] = '\0';

	delete[] _string;
	_string = temp;
}

size_t String::GetLen() { return _len; }

long String::Find(const char value) const
{
	for (size_t i = 0; i < _len; i++)
	{
		if (_string[i] == value) return i;
	}

	return -1;
}

long String::Find(const char* str) const
{
	return (find(str));
}

long String::Find(const String& str) const
{
	return (find(str._string));
}

bool String::Remove(const char value)
{
	size_t index = Find(value);
	if (index < 0) return 0;

	remove(index, 1);
	return 1;
}

bool String::Remove(const char* str)
{
	size_t index = Find(str);

	if (index < 0) return 0;

	remove(index, length(str));
	return 1;
}

bool String::Remove(const String& str)
{
	size_t index = Find(str);

	if (index < 0) return 0;

	remove(index, str._len);
	return 1;
}

const char* String::c_str() const { return _string; }

String::~String()
{
	delete[] _string;
}