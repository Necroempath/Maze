#pragma once
template <typename T>
class SharedPtr
{
private:
    T* _ptr;
    size_t* _use_count;

    bool decrease_count()
    {
        if (_use_count && --(*_use_count) == 0)
        {
            delete _ptr;
            delete _use_count;
            return true;
        }
        return false;
    }

public:
    SharedPtr() : _ptr(nullptr), _use_count(new size_t(0)) {}
 
    SharedPtr(T&& obj) : _ptr(new T(std::move(obj))), _use_count(new size_t(1)) {}

    SharedPtr(T* obj) : _ptr(obj), _use_count(new size_t(1)) {}

    SharedPtr(const SharedPtr& other) : _ptr(other._ptr), _use_count(other._use_count)
    {
        if (_use_count) (*_use_count)++;
    }

    SharedPtr(SharedPtr&& other) noexcept : _ptr(other._ptr), _use_count(other._use_count)
    {
        other._ptr = nullptr;
        other._use_count = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            if (decrease_count()) {
                _ptr = nullptr;
                _use_count = nullptr;
            }

            _ptr = other._ptr;
            _use_count = other._use_count;
            if (_use_count) (*_use_count)++;
        }

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            if (decrease_count()) {
                _ptr = nullptr;
                _use_count = nullptr;
            }

            _ptr = other._ptr;
            _use_count = other._use_count;

            other._ptr = nullptr;
            other._use_count = nullptr;
        }

        return *this;
    }

    T* operator->() { return get(); }
    T& operator*() { return *_ptr; }

    explicit operator bool() const { return _ptr != nullptr; }

    T* get() const { return _ptr; }

    size_t use_count() const { return _use_count ? *_use_count : 0; }

    void swap(SharedPtr& other)
    {
        std::swap(_ptr, other._ptr);
        std::swap(_use_count, other._use_count);
    }

    bool unique() const { return use_count() == 1; }

    T* release()
    {
        T* temp = _ptr;
        if (decrease_count()) {
            _ptr = nullptr;
        }
        return temp;
    }

    ~SharedPtr()
    {
        if (decrease_count())
        {
            delete _ptr;
            delete _use_count;
        }
    }
};
