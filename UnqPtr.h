// UnqPtr.h
#ifndef UNQPTR_H
#define UNQPTR_H

// Код для UnqPtr


//Децентрализованное хранение объектов: UnqPtr и ShrdPtr
template <typename T>
class UnqPtr {
private:
    T* ptr;

public:

    // Метод для получения указателя
    T* get() const {
        return ptr;
    }

    UnqPtr(T* p = nullptr) : ptr(p) {}

    // Метод для получения указателя и освобождения
    T* release() {
        T* temp = ptr;
        ptr = nullptr; // Освобождаем указатель
        return temp;
    }

    // Освобождение ресурса
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
            delete ptr; // Освобождаем текущий указатель
            ptr = other.ptr;
            other.ptr = nullptr; // Освобождаем указатель
        }
        return *this;
    }
};
#endif // UNQPTR_H
