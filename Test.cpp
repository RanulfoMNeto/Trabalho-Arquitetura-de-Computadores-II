#include <exception>
#include <string>

using namespace std;

class AssertException : public exception {
    private:
        string message;

    public:
        AssertException(string msg) : message("AssertException: " + msg) {}
        const char* what () {
            return message.c_str();
        }
};

string to_string(bitset<32> b) {
    return to_string(b.to_ulong());
}

template<typename Auto>
class Test {
    private:
        int id = 0;
        void Assert(Auto result, Auto expected) {
            id++;
            if(!(result == expected)) {
                throw AssertException(to_string(result) + " != " + to_string(expected));
            }
        }
    public:
        void assertEqual(Auto result, Auto expected) {
            cout << "Test ID: " << id << endl;
            try {
                Assert(result, expected);
                cout << " | Test Completed!" << endl;
            } catch (AssertException ae) {
                cout << " | Test Failed! ";
                cout << ae.what() << endl;
            }
        }
        void assertTrue(Auto condition) {
            assertEqual(condition, true);
        }
        void assertFalse(Auto condition) {
            assertEqual(condition, false);
        }
        int getId() {
            return id;
        }
};