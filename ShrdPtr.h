#ifndef SHRD_PTR_H
#define SHRD_PTR_H

template <typename T>
class ShrdPtr {
private:
    T* ptr;
    size_t* referenceCount;

public:
    ShrdPtr(T* p = nullptr) : ptr(p), referenceCount(new size_t(1)) {}

    // Конструктор копирования
    ShrdPtr(const ShrdPtr& other) : ptr(other.ptr), referenceCount(other.referenceCount) {
        ++(*referenceCount);
    }

    // Конструктор из UnqPtr
    ShrdPtr(UnqPtr<T>&& uptr) : ptr(uptr.release()), referenceCount(new size_t(1)) {}

    ~ShrdPtr() {
        if (--(*referenceCount) == 0) {
            delete ptr;
            delete referenceCount;
        }
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};



#endif // SHRD_PTR_H