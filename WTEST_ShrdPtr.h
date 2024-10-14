void testShrdPtr() {
    // Тест 1: Создание ShrdPtr
    ShrdPtr<int> p1(new int(5));
    assert(*p1 == 5); // Проверяем, что значение равно 5

    // Тест 2: Конструктор копирования
    ShrdPtr<int> p2 = p1; // Копируем p1 в p2
    assert(*p2 == 5); // Проверяем, что значение в p2 равно 5
    assert(p1.operator->() == p2.operator->()); // Убедимся, что оба указателя указывают на один и тот же адрес

    // Тест 3: Уменьшение счетчика ссылок
    {
        ShrdPtr<int> p3 = p2; // Копируем p2 в p3
        assert(*p3 == 5); // Проверяем значение
        assert(p2.operator->() == p3.operator->()); // Убедимся, что оба указателя указывают на один и тот же адрес
    } // p3 выходит из области видимости, счетчик ссылок должен уменьшиться

    // Тест 4: Проверка, что p1 и p2 все еще валидны
    assert(*p1 == 5);
    assert(*p2 == 5);

    // Тест 5: Перемещение из UnqPtr
    UnqPtr<int> uptr(new int(10));
    ShrdPtr<int> p4(std::move(uptr)); // Перемещаем uptr в p4
    assert(*p4 == 10); // Проверяем значение

    std::cout << "shred OK" << std::endl; // Если все тесты прошли успешно
}


// Функция для нагрузочных тестов ShrdPtr
void loadTestShrdPtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<ShrdPtr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(new int(i)); // Создаем новый объект
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects ShrdPtr for " << duration.count() << " seconds." << std::endl;
}

// Функция для нагрузочных тестов std::shared_ptr
void loadTestStdSharedPtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::shared_ptr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(std::make_shared<int>(i)); // Создаем новый объект
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects std::shared_ptr for " << duration.count() << " seconds." << std::endl;
}