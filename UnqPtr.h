// UnqPtr.h
#ifndef UNQPTR_H
#define UNQPTR_H

// Код для UnqPtr



template <typename T>
class UnqPtr {
private:
    T* ptr;

public:


    T* get() const {
        return ptr;
    }

    UnqPtr(T* p = nullptr) : ptr(p) {}


    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }


    ~UnqPtr() {
        delete ptr;
    }

    // Запрещаем копирование
    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // Разрешаем перемещение
    UnqPtr(UnqPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr; // Освобождаем указатель
    }

    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};
#endif // UNQPTR_H
