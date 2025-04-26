#pragma once

template <typename T>
class UniquePtr {
    T* _ptr;

public:
    UniquePtr() : _ptr(nullptr) {}

    UniquePtr(const UniquePtr&) = delete;
    
    UniquePtr(T&& obj) : _ptr(new T(std::move(obj))) {}

    UniquePtr(T* ptr) : _ptr(ptr) {}

    UniquePtr(UniquePtr&& other) noexcept : _ptr(other._ptr) {
        other._ptr = nullptr;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this == &other) return *this;

        reset();
        _ptr = other._ptr;
        other._ptr = nullptr;

        return *this;
    }

    T* operator->() {
        if (!_ptr) throw std::runtime_error("Dereferencing a null pointer");
        return _ptr;
    }

    T& operator*() {
        if (!_ptr) throw std::runtime_error("Dereferencing a null pointer");
        return *_ptr;
    }

    explicit operator bool() const { return _ptr != nullptr; }

    T* get() const { return _ptr; }

    void swap(UniquePtr& other) {
        T* temp = _ptr;
        _ptr = other._ptr;
        other._ptr = temp;
    }

    inline void reset(T* ptr = nullptr) {
        if (_ptr) delete _ptr;
        _ptr = ptr;
    }

    inline T* release() {
        T* temp = _ptr;
        _ptr = nullptr;
        return temp;
    }

    ~UniquePtr() {
        if (_ptr) delete _ptr;
    }
};
