#include <iostream>
#include "Test.cpp"

using namespace std;

int main() {

    Test<int> test;
    test.assertEqual(5-3, 2); // ID: 0
    test.assertEqual(5-3, 3); // ID: 1
    test.assertTrue(5>2); // ID: 2
    test.assertFalse(5<3); // ID: 3
    test.assertEqual((double)3/2, (double)1.5); // ID: 4
    
    return 0;
}
