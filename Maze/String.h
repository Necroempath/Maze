#pragma once
#include <iostream>
class String
{
	char* _string;
	size_t _len;
	size_t _capacity;

	static constexpr size_t CAPACITY = 10;

	void Default();
	void Init(const String& str);
	size_t length(const char* str) const;
	void copy(String& dest, const char* source) const;
	void concat(String& dest, const char* source) const;
	void repeat(String& dest, const char* source, const short count) const;
	bool compare(const char* str) const;
	long find(const char* str) const;
	void remove(const size_t index, const size_t len);
	void ResizeString(const float factor);

public:
	String();

	String(const char* str);

	explicit String(const size_t len);

	String(const String& other);

	String(String&& other) noexcept;

	String& operator=(const String& other);

	String& operator=(String&& other) noexcept;

	String& operator=(const char* str);

	String operator+(const String& str) const;

	String operator+(const char* str) const;

	String& operator+=(const String& str);

	String& operator+=(const char* str);

	bool operator==(const String& str) const;

	bool operator==(const char* str) const;

	String operator*(const size_t count) const;

	String& operator*=(const size_t count);

	const char operator[](const size_t index) const;

	char& operator[](size_t index);

	friend std::ostream& operator<<(std::ostream& os, const String& str);

	friend std::istream& operator>>(std::istream& is, String& str);

	size_t GetLen();

	long Find(const char value) const;

	long Find(const char* str) const;

	long Find(const String& str) const;

	bool Remove(const char value);

	bool Remove(const char* str);

	bool Remove(const String& str);

	const char* c_str() const;

	~String();
};
