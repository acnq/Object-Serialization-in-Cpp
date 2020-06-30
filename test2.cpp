#include <iostream>
#include <fstream>

template<typename ElementType>
void ser(ElementType a,std::string fileName)
{
    std::fstream str;
    str.open(fileName, std::ios::out | std::ios::binary);
    str.write((char*)(&a), sizeof(a));
    str.close();
}

template<typename ElementType>
ElementType deser(std::string fileName)
{
    ElementType a = ElementType();
    std::fstream str;
    str.open(fileName, std::ios::in | std::ios::binary);
    str.read((char*)(&a), sizeof(a));
    str.close();
    return a;
}

class test {
public:
    int a;
    double b;
    std::string c;
    int d;
};
#define varName(x) #x
int main()
{
    int a;
    std::cout << (varName(a));
    test tt = test();
    tt.a = 256;
    tt.b = 2.3;
    tt.c = "abc";
    tt.d = 4;
    ser<test>(tt,"a.test");

    test t = deser<test>("a.test");
    std::cout << "\n-------------------\n";
    std::cout << sizeof(test) << "\n";
    std::cout << t.a << " | ";
    std::cout << t.b << " | ";
    std::cout << t.c << " | ";
    std::cout << t.d;

    std::cout << "\n-------------------\n";
    ser<int>(256,"b.data");
    int e = deser<int>("b.data");
    std::cout << e;
    return 0;
}