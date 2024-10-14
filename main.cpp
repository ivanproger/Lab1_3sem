#include <iostream>
#include <cassert>
#include <chrono> //измерение времени операции
#include <memory> //библиотека со стандартными умными указателями STL
#include <vector> //стандартный контейнер, динамический массив
//#include "../LR1/matplotlib-cpp-master/matplotlibcpp.h" // Подключаем библиотеку для построения графиков
//
#include "../LR1/SmtrPtr.h"
#include "../LR1/UnqPtr.h"
#include "../LR1/ShrdPtr.h"
#include "../LR1/MsPtr.h"
#include "../LR1/MemorySpan.h"
#include "../LR1/SmtrPtr.h"//защита от повторного включения реализовать
#include "../LR1/WTEST_ShrdPtr.h"
#include "../LR1/WTEST_UnqPtr.h"
#include "../LR1/WTEST_MemorySpan.h"
#include "../LR1/WTEST_Msptr.h"
//namespace plt = matplotlibcpp;
using namespace std;
//tests
// Тесты

    int main() {


        size_t capacity;
        std::cout << "Enter the size of the array: ";
        std::cin >> capacity;

        MemorySpan memorySpan(capacity);

        for (size_t i = 0; i < capacity; ++i) {
            char newObj;
            std::cout << "Enter value for elem[" << i << "]: ";
            std::cin >> newObj;
            memorySpan.addElement(newObj);
        }

        size_t indexToCreate;
        std::cout << "Enter index of the element to create a pointer (0-" << capacity - 1 << "): ";
        std::cin >> indexToCreate;
        Pointer p1 = memorySpan.createPointer(indexToCreate);
        std::cout << "Pointer created for element with index " << indexToCreate << " with value: " << p1.getValue() << std::endl;

        std::cin >> indexToCreate;
        Pointer p2 = memorySpan.createPointer(indexToCreate);
        std::cout << "Pointer created for element with index " << indexToCreate << " with value: " << p2.getValue() << std::endl;

        std::cin >> indexToCreate;
        Pointer p3 = memorySpan.createPointer(indexToCreate);
        std::cout << "Pointer created for element with index " << indexToCreate << " with value: " << p3.getValue() << std::endl;

        size_t indexToDelete;
        std::cout << "Enter index of the element to delete the pointer (0-" << capacity - 1 << "): ";
        std::cin >> indexToDelete;
        memorySpan.deletePointer(indexToDelete);

        std::cout << "Enter index of the element to delete the pointer (0-" << capacity - 1 << "): ";
        std::cin >> indexToDelete;
        memorySpan.deletePointer(indexToDelete);

        std::cout << "\nState of the arrays after operations:" << std::endl;
        memorySpan.showPointers();
        testMemorySpan();
        testMsPtr();
        testShrdPtr();
        testUnqPtr();

        loadTestShrdPtr(1000);
        loadTestShrdPtr(100000);

        loadTestStdSharedPtr(1000);
        loadTestStdSharedPtr(100000);


        loadTestUnqPtr(1000);
        loadTestStdUniquePtr(1000);

        loadTestUnqPtr(1000000);
        loadTestStdUniquePtr(1000000);
        return 0;
    }


    //TODO:1)всё плохо сделалось после Msptr нужно разобраться с ним написать соместные тесты для него и MemorySpan
   // 2)написать тесты для других функций
   // 3)сделать пользовательский интерейс для пойнтеров
   // 4)сделать сравнение эффективности реализации

