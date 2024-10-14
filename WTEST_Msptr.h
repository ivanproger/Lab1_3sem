void testMsPtr() {
    MemorySpan span(5);
    span.addElement('A');
    span.addElement('B');
    span.addElement('C');


    MsPtr ptr(span, 1);

// Test operator*
    assert(*ptr == 'B');

// Test operator++
    ++ptr;
    assert(*ptr == 'C');

// Test Locate()
    assert(ptr.Locate() == 2);
    std::cout << "Msptr OK" << std::endl; // Если все тесты прошли успешно
}