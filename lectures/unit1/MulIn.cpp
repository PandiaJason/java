
#include <iostream>
using namespace std;

class Base1 {
public:
    void display() {
        cout << "Base1 display" << endl;
    }
};

class Base2 {
public:
    void show() {
        cout << "Base2 show" << endl;
    }
};

class Derived : public Base1, public Base2 {
};

int main() {
    Derived obj;
    obj.display(); // From Base1
    obj.show();    // From Base2
    return 0;
}
