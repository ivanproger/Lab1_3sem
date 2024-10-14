#include <iostream>
#include <vector>
#include <stdexcept>

#ifndef MEMORYSPAN_H
#define MEMORYSPAN_H

class Pointer; // Предварительное объявление класса Pointer

class MemorySpan {
private:
    std::vector<char> elem;          // Массив элементов
    std::vector<size_t> counter;     // Счетчики указателей
    std::vector<size_t> next_elem;   // Индексы следующих свободных элементов
    size_t Nexter;                   // Индекс следующего свободного элемента
    size_t size_;                    // Размер массива

public:
    MemorySpan(size_t size) : Nexter(0), size_(size) { // Инициализация size_
        elem.resize(size, '\0');
        counter.resize(size, 0);
        next_elem.resize(size);
        for (size_t i = 0; i < size - 1; ++i) {
            next_elem[i] = i + 1; // Инициализация свободных индексов
        }
        next_elem[size - 1] = size; // Конец списка свободных индексов
    }

    ~MemorySpan() {
        // Освобождение памяти не требуется, так как elem теперь просто массив
    }

    void addElement(char newObj) {
        if (Nexter >= elem.size()) {
            std::cout << "No free space for a new element." << std::endl;
            return;
        }

        size_t index = Nexter; // Индекс для нового объекта
        elem[index] = newObj;  // Сохранение объекта в массиве
        counter[index] = 1;    // Установка счетчика на 1
        Nexter = next_elem[Nexter]; // Обновление Nexter


    }

    char getElement(size_t index) const {
        if (index < elem.size()) {
            return elem[index];
        }
        throw std::out_of_range("Index out of range");
    }

    Pointer createPointer(size_t index); // Объявление метода создания указателя

    void deletePointer(size_t index) {
        if (index >= elem.size() || elem[index] == '\0') {
            return;
        }

        // Уменьшение счетчика и проверка, достиг ли он нуля
        if (--counter[index] == 0) {
            elem[index] = '\0'; // Освобождение места
            next_elem[index] = Nexter; // Возврат индекса в список свободных
            Nexter = index; // Обновление Nexter
        }
    }

    void showPointers() const {
        for (size_t i = 0; i < elem.size(); ++i) {
            if (elem[i] != '\0') {
                std::cout << "elem[" << i << "] = " << elem[i] << ", counter = " << counter[i] << std::endl;
            }
        }
    }

    size_t getSize() const {
        return size_;
    }

    size_t getCounter(size_t index) const {
        if (index < counter.size()) {
            return counter[index];
        }
        return 0; // Возвращаем 0, если индекс вне диапазона
    }
};
class Pointer {
private:
    MemorySpan& span_; // Ссылка на MemorySpan
    size_t index_;     // Индекс текущего элемента

public:
    Pointer(MemorySpan& span, size_t index) : span_(span), index_(index) {
        if (index_ >= span.getSize() || span.getCounter(index_) == 0) {
            throw std::out_of_range("Index out of range or element does not exist");
        }
    }

    ~Pointer() {
        span_.deletePointer(index_); // Уменьшаем счетчик указателей при уничтожении
    }

    char getValue() const {
        return span_.getElement(index_);
    }
};

// Реализация метода createPointer
Pointer MemorySpan::createPointer(size_t index) {
    if (index >= elem.size() || elem[index] == '\0') {
        throw std::out_of_range("Element does not exist for the pointer.");
    }
    counter[index]++; // Увеличение счетчика
    return Pointer(*this, index); // Возвращаем новый указатель
}

#endif // MEMORYSPAN_H
