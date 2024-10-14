#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "../LR1/MemorySpan.h"

#ifndef MSPTR_H
#define MSPTR_H

class MsPtr {
private:
    MemorySpan& span_; // Ссылка на MemorySpan
    size_t index_;     // Индекс текущего элемента

public:
    // Конструктор
    MsPtr(MemorySpan& span, size_t index) : span_(span), index_(index) {
        if (index_ >= span.getSize()) { // Проверка на допустимый индекс
            throw std::out_of_range("Индекс вне диапазона");
        }
    }

    // Оператор разыменования
    char operator*() {
        if (index_ >= span_.getSize()) { // Проверка на допустимый индекс
            throw std::out_of_range("Индекс вне диапазона");
        }
        return span_.getElement(index_);
    }

    // Оператор инкремента
    MsPtr& operator++() {
        if (index_ + 1 >= span_.getSize()) { // Проверка на допустимый индекс
            throw std::out_of_range("Индекс вне диапазона");
        }
        ++index_;
        return *this;
    }

    // Метод для получения текущего индекса
    size_t Locate() const {
        return index_;
    }
};
#endif