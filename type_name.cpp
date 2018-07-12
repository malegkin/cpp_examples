#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <iostream>

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

template <typename T>
void func1(T param) {
 std::cout << "decltype(i) is " << type_name<decltype(param)>() << '\n';
}
template <typename T>
void func2(T& param) {
 std::cout << "decltype(i) is " << type_name<decltype(param)>() << '\n';
}
template <typename T>
void func3(T* param) {
 std::cout << "decltype(i) is " << type_name<decltype(param)>() << '\n';
}
template <typename T>
void func4(T&& param) {
 std::cout << "decltype(i) is " << type_name<decltype(param)>() << '\n';
}


int main() {
    const int ci = 15;
    const int &cir = ci;

    auto aci = ci;
    auto acir = cir;    
    
    func2(ci); // 2.2. param type ?
    func2(cir); // 2.3. param type ?

    func2(aci); // 2.2. param type ?
    func2(acir); // 2.3. param type ?

    
    
    
    
    
    return 0;
}
