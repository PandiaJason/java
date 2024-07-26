
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() {
        cout << "Eating..." << endl;
    }
};

class Mammal : public Animal {
public:
    void breathe() {
        cout << "Breathing..." << endl;
    }
};

class Dog : public Mammal {
public:
    void bark() {
        cout << "Barking..." << endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat();    // Inherited from Animal
    myDog.breathe(); // Inherited from Mammal
    myDog.bark();    // Specific to Dog
    return 0;
}
