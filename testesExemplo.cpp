#include <iostream>
#include "Test.cpp"
#include <bitset>
#include "Processador.cpp"

using namespace std;

int main() {

    Processador proc = Processador("programa2.txt");
    Test<bitset<32> > test;
    test.assertEqual(proc.rb->getRegistrador(bitset<8>(3)), bitset<32>(20));
    test.assertEqual(proc.rb->getRegistrador(bitset<8>(4)), bitset<32>(20));

    Processador proc2 = Processador("programa3.txt");
    test.assertEqual(proc2.rb->getRegistrador(bitset<8>(1)), bitset<32>(2));
    test.assertEqual(proc2.rb->getRegistrador(bitset<8>(2)), bitset<32>(10));
    test.assertEqual(proc2.rb->getRegistrador(bitset<8>(3)), bitset<32>(20));
    test.assertEqual(proc2.rb->getRegistrador(bitset<8>(4)), bitset<32>(20));

    EXMEM exmem = EXMEM();
    unsigned short n = 10;

    exmem.executar(bitset<32>(INT_MAX), bitset<32>(INT_MAX), bitset<16>(2), bitset<5>("00001"), false, false, false, n, false, false, NULL);
    test.assertEqual(exmem.result, bitset<32>(-2));

    exmem.executar(bitset<32>(INT_MAX), bitset<32>(INT_MAX), bitset<16>(2), bitset<5>("11001"), false, false, false, n, false, false, NULL);
    test.assertEqual(exmem.result, bitset<32>(10));
    
    return 0;
}
