
#include <iostream>
using namespace std;

class Print {
public:
    void display(int i) {
        cout << "Integer: " << i << endl;
    }

    void display(double f) {
        cout << "Float: " << f << endl;
    }

    void display(string s) {
        cout << "String: " << s << endl;
    }
};

int main() {
    Print obj;
    obj.display((int)5.00);
    obj.display((int)3.14);
    obj.display(0.4);
    return 0;
}
