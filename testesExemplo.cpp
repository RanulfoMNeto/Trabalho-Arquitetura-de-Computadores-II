#include <iostream>
#include "Test.cpp"
#include <bitset>
#include "Processador.cpp"

using namespace std;

int main() {

    Test<int> test;
    test.assertEqual(5-3, 2); // ID: 0
    test.assertEqual(5-3, 3); // ID: 1
    test.assertTrue(5>2); // ID: 2
    test.assertFalse(5<3); // ID: 3
    test.assertEqual((double)3/2, (double)1.5); // ID: 4

    Test<int> test2;
    Processador proc = Processador("codigo.txt");
    test2.assertEqual(proc.dados->getRegistrador(bitset<16>(10)).to_ulong(), 30);
    
    return 0;
}
