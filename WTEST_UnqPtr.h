void testUnqPtr() {

    {
        UnqPtr<int> uptr(new int(5));
        assert(*(uptr.get()) == 5);
    }


    {
        UnqPtr<int> uptr1(new int(10));
        UnqPtr<int> uptr2(std::move(uptr1));
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 10);
    }


    {
        UnqPtr<int> uptr1(new int(20));
        UnqPtr<int> uptr2;
        uptr2 = std::move(uptr1);
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 20);
    }

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