void testUnqPtr() {
    // Тест 1: Создание UnqPtr
    {
        UnqPtr<int> uptr(new int(5));
        assert(*(uptr.get()) == 5); // Проверяем, что значение равно 5
    } // uptr выходит из области видимости и освобождает память

    // Тест 2: Перемещение UnqPtr
    {
        UnqPtr<int> uptr1(new int(10));
        UnqPtr<int> uptr2(std::move(uptr1)); // Перемещаем uptr1 в uptr2
        assert(uptr1.get() == nullptr); // uptr1 теперь должен быть nullptr
        assert(*(uptr2.get()) == 10); // Проверяем, что значение в uptr2 равно 10
    } // uptr2 выходит из области видимости и освобождает память

    // Тест 3: Перемещение с присваиванием
    {
        UnqPtr<int> uptr1(new int(20));
        UnqPtr<int> uptr2;
        uptr2 = std::move(uptr1); // Перемещаем uptr1 в uptr2
        assert(uptr1.get() == nullptr); // uptr1 теперь должен быть nullptr
        assert(*(uptr2.get()) == 20); // Проверяем, что значение в uptr2 равно 20
    } // uptr2 выходит из области видимости и освобождает память

    std::cout << "Uniq OK" << std::endl; // Если все тесты прошли успешно
}


// Функция для нагрузочных тестов UnqPtr
void loadTestUnqPtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<UnqPtr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(new int(i)); // Создаем новый объект
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects UnqPtr for " << duration.count() << " seconds." << std::endl;
}

// Функция для нагрузочных тестов std::unique_ptr
void loadTestStdUniquePtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::unique_ptr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(std::make_unique<int>(i)); // Создаем новый объект
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects std::unique_ptr for " << duration.count() << " seconds." << std::endl;
}