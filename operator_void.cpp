#include <iostream>
#include <cstdlib>

struct A
{
    operator void()
    {
        std::cout << "I can!";
    }
};

int main()
{
    auto a = new(A);
    a->operator void();
    
    A a2;
    a2.operator void();
}
