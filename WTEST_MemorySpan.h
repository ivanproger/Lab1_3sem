void testMemorySpan() {
    MemorySpan memorySpan(5);

    // Проверка добавления элементов
    memorySpan.addElement('A');
    memorySpan.addElement('B');
    memorySpan.addElement('C');

    assert(memorySpan.getElement(0) == 'A');
    assert(memorySpan.getElement(1) == 'B');
    assert(memorySpan.getElement(2) == 'C');

    // Проверка счетчиков
    assert(memorySpan.getCounter(0) == 1);
    assert(memorySpan.getCounter(1) == 1);
    assert(memorySpan.getCounter(2) == 1);

    // Создание указателей
    Pointer p1 = memorySpan.createPointer(0);
    Pointer p2 = memorySpan.createPointer(1);
    Pointer p3 = memorySpan.createPointer(2);

    assert(p1.getValue() == 'A');
    assert(p2.getValue() == 'B');
    assert(p3.getValue() == 'C');

    // Проверка счетчиков после создания указателей
    assert(memorySpan.getCounter(0) == 2);
    assert(memorySpan.getCounter(1) == 2);
    assert(memorySpan.getCounter(2) == 2);

    // Удаление указателей
    p1.~Pointer();
    p2.~Pointer();
    p3.~Pointer();

    // Проверка счетчиков после удаления указателей
    assert(memorySpan.getCounter(0) == 1);
    assert(memorySpan.getCounter(1) == 1);
    assert(memorySpan.getCounter(2) == 1);

    // Удаление элементов
    memorySpan.deletePointer(0);
    memorySpan.deletePointer(1);
    memorySpan.deletePointer(2);

    // Проверка состояния массива после удаления
    assert(memorySpan.getCounter(0) == 0);
    assert(memorySpan.getCounter(1) == 0);
    assert(memorySpan.getCounter(2) == 0);

    std::cout << "MemorySpan OK" << std::endl; // Если все тесты прошли успешно
}
