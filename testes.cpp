#include <iostream>
#include "Test.cpp"
#include <bitset>
#include "Processador.cpp"

using namespace std;

int main() {

    Test<bitset<32> > test2;
    Processador proc = Processador("codigo.txt");
    test2.assertEqual(proc.dados->getRegistrador(bitset<16>(10)), bitset<32>(20));
    
    return 0;
}
