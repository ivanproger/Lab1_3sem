void testShrdPtr() {

    ShrdPtr<int> p1(new int(5));
    assert(*p1 == 5);


    ShrdPtr<int> p2 = p1;
    assert(*p2 == 5);
    assert(p1.operator->() == p2.operator->());


    {
        ShrdPtr<int> p3 = p2;
        assert(*p3 == 5);
        assert(p2.operator->() == p3.operator->());
    }


    assert(*p1 == 5);
    assert(*p2 == 5);


    UnqPtr<int> uptr(new int(10));
    ShrdPtr<int> p4(std::move(uptr));
    assert(*p4 == 10);

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