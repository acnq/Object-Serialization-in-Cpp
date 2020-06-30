#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

template<typename elet>
void ser(elet a)
{
    std::fstream str;
    str.open("a.txt", ios::out | ios::binary);
    str.write((char*)(&a), sizeof(a));
    str.close();
}

template<typename elet>
elet deser()
{
    elet a = elet();
    std::fstream str;
    str.open("a.txt", ios::in | ios::binary);
    str.read((char*)(&a), sizeof(a));
    str.close();
    return a;
}



template<class ElementType>
void serialize(ElementType a,std::string fileName)
{
    std::fstream str;
    str.open(fileName, std::ios::out | std::ios::binary);
    str.write((char*)(&a),sizeof(a));
    //str.write(reinterpret_cast<ElementType*>(&a), std::aligned_storage<sizeof(ElementType),std::alignment_of<ElementType>::value>::type);
    str.close();
}


template<class ElementType>
ElementType deserialize(ElementType &a,std::string fileName)
{
    a = ElementType();
    std::fstream str;
    str.open(fileName, std::ios::in | std::ios::binary);
    str.read((char*)(&a), sizeof(a));
    //str.write(reinterpret_cast<ElementType*>(&a), std::aligned_storage<sizeof(ElementType),std::alignment_of<ElementType>::value>::type);
    str.close();
    return a;
}

template<class ElementType>
void serialize_xml(ElementType a,std::string stltype,std::string fileName){

}

template<class ElementType>
void deserialize_xml(ElementType a,std::string stltype,std::string fileName){

}
