#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <assert.h>
#include <set>
#include <map>
#include <string>
using namespace std;

class FileOp
{//this is a class of file operation
public:
//it implement the  basic function of write and read
    virtual std::ostream& write(std::ostream& ostr) = 0;
    virtual std::istream& read(std::istream& istr) = 0;
};


//the 2 function below is the 1st version testing, not play a 
//necessary role in the whole process, could be delete if the whole 
//process wrong perfect in your computer environment;
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

//this function is here for a test of alignment
//whether your computer use little endian, or big endian in your computer's memory system
static inline bool LE(){
    //we assume all variable are stored in the same endian
    //so we need only test the storage of variable integer "1";
    const static int n = 1;
    const static bool le = (*(char*)&n == 1);//test whether a little endian 
    return le;
}

static inline ostream& write_internal(ostream& outfile,const char* p,uint32_t size){
    //this function write data in the outfile via a char pointer p
    if(!LE()){
        //if big endian. we write it as little endian
        for (int i = size - 1; i >= 0; --i)
        {
            outfile.write(p+i,1);//we use write function in ostream.tcc
        }    
    }
    else
    {   //use pointer to write content;
        outfile.write(p,size);//we use write function in ostream.tcc
    }
    return outfile;   
}

//below we show all the write functions, for fundamental type and cpp STL container pair、 vector、list、set、map
//-------------------------------------------

template<typename T>
static inline ostream& write(ostream& outfile, T& t){
    //this function write a Type t variable to the output file
    //we now just implememt fundamental type;
    
    if(std::is_fundamental<T>::value){
        //we construct a pointer, and use write_internal funct to write every element to the outputfile
        return write_internal(outfile,(const char*)& t, sizeof(t));
    }else
    {
        //if want a implememtation of user_define type just add code here
        cout << "sorry, we do not support non_fundamental STL container type\n"<<endl;
        cout << "if continue , there may be bugs\n" << endl;
        return write_internal(outfile,(const char*)& t, sizeof(t));
    }    
}

//vector//////////////////////////////////////////////////
template <class T>
static inline ostream& write(ostream& outfile,vector<T>& container){
    //this function implement a writing to outfile of vector type
    uint32_t size = container.size();

    //we first write the size info of this vector via write(outfile T t);
    write(outfile,size);

    //then we do a loop to write every element in the vector;
    for (auto& ite: container)
    {
        write(outfile,ite);
    }
    return outfile;
}
//list//////////////////////////////////////////////////////
template <class T>
static inline ostream& write(ostream& outfile, list<T>& container){
    //this function implement a writing to outfile of list type
    uint32_t size = container.size();

    //we first write the size info of this list via write(outfile T t);
    write(outfile,size);

    //then we do a loop to write every element in the list;
    for (auto& ite : container)
    {
        write(outfile,ite);
    }
    return outfile;
    
}
//set/////////////////////////////////////////////////
template <class T>
static inline ostream& write(ostream& outfile, set<T>& container){
    //this function implement a writing to outfile of set type
    uint32_t size = container.size();

    //we first write the size info of this set via write(outfile T t);
    write(outfile,size);

    //then we do a loop to write every element in the set;
    for (auto& ite : container)
    {
        write(outfile,ite);
    }
    return outfile;
    
}
//map//////////////////////////////////////////////////
template<class K, class V>
static inline ostream& write(ostream& outfile, map<K,V>& container){
//this function implement a writing to outfile of map type
    uint32_t size = container.size();
    
    //we first write the size info of this set via write(outfile T t);
    write(outfile,size);

    //then we do a loop to write every element in the set;
    for (auto& p : container)
    {
        write(outfile,p.first);
        write(outfile, p.second);
    }
    return outfile;
}


//-------------------------------------------------------
//end showing write function



//below we show all the ser functions, including elementType and STL_container(vector、list、set、map)
//-------------------------------------------------------------
template<class ElementType>
void serialize(ElementType a,std::string fileName)
{//this function do a ser of fundamental type of cpp;

    std::fstream str;
    str.open(fileName, std::ios::out | std::ios::binary);

    //just a simple fstream.write will work, for int, string and pair;
    str.write((char*)(&a),sizeof(a));
    ///str.write(reinterpret_cast<ElementType*>(&a), std::aligned_storage<sizeof(ElementType),std::alignment_of<ElementType>::value>::type);
    str.close();
}
//vector///////////////////////////////////////////////
template<class T>
void serialize(vector<T>& container,std::string fileName){
    //this function do a ser of vector of T type(now fundamental T only)
    std::ofstream str;
    str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

    //we must use a different kind of write to implement the write-out method.
    write(str,container);
    str.flush();
    str.close();
}
//list////////////////////////////////////////////////
template<class T>
void serialize(list<T>& container,std::string fileName){
    //this function do a ser of list of T type(now fundamental T only)
    std::ofstream str;
    str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc );

    //we use a very similar read function as vector do  to implememte a write-out
    write(str,container);
    str.flush();
    str.close();
}
//set//////////////////////////////////////////
template<class T>
void serialize(set<T>& container, std::string fileName){
    //this function do a ser of set of T type(now fundamental T only)
    std::ofstream str;
    str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc );

    //we use a very similar read function as vector do  to implememte a write-out
    write(str,container);
    str.flush();
    str.close();
}
//map/////////////////////////////////////////
template<class K,class V>
void serialize(map<K,V>& container, std::string fileName){
    //this function do a ser of set of T type(now fundamental T only)
    std::ofstream str;
    str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc );

    //we use a very similar read function as vector do  to implememte a write-out
    write(str,container);
    str.flush();
    str.close();
}

//-------------------------------------------------------------
//end showing ser functions


static inline istream& read_internal(istream& infile, char* p, uint32_t size){
    //this function read data in the outfile via a char pointer p
    //very similar as write_internal function as above; we do not comment it  then
    if(!LE()){
        for (int i = size - 1; i >= 0; --i)
        {
            infile.read(p+i,1);
        }    
    }
    else
        {
            infile.read(p,size);
        }
    return infile;
}


//below we show all the read functions, for fundamental type and cpp STL container pair、 vector、list、set、map
//------------------------------------------------------------------------------

template<class T>
static inline istream& read(istream& infile, T& t){
//this function read a Type t variable from the input file
//we now just implememt fundamental type;
    if(std::is_fundamental<T>::value){
        return read_internal(infile,(char*)& t, sizeof(t));
    }else
    {
        //if want a implememtation of user_define type just add code here
        cout << "Sorry we do not support non_fundamental_type STL_container " << endl;
    }
    return infile;
}

//vector////////////////////////////////////////////////////
template<class T>
static inline istream& read(istream& infile,vector<T>& container){
    //this function implement a read from input file(infile) of a vector type container
    if(!infile.good() || infile.eof()){
        //we do not read a dirty file or empty file;
        return infile;
    }
    int size;
    container.clear();//we first clear the buff in the container
    read(infile,size);//then we use read(istream, Ttype) to read in size
    for (int i = 0; i < size; ++i)
    {//we then read every element use read(istream Ttype) and a vector push_back;
       T t;
       read(infile,t);
       container.push_back(t);
    }

    //check whether we have read successfully
    assert(infile.good());

    return infile;  
}
//list////////////////////////////////////////////////
template<class T>
static inline istream& read(istream& infile, list<T>& container){
    //this function implement a read from input file(infile) of a vector type container
    if(!infile.good() || infile.eof()){
        //we do not read a dirty file or empty file;
        return infile;
    }
    int size;
    container.clear();//we first clear the buff in the container
    read(infile,size);//then we use read(istream, Ttype) to read in size
    for (int i = 0; i < size; ++i)
    {//we then read every element use read(istream Ttype) and a vector push_back;
       T t;
       read(infile,t);
       container.push_back(t);
    }

    //check whether we have read successfully
    assert(infile.good());

    return infile;
}
//set//////////////////////////////////////////////////
template<class T>
static inline istream& read(istream& infile,set<T>& container){
    //this function implement a read from input file(infile) of a vector type container
    if(!infile.good() || infile.eof()){
        //we do not read a dirty file or empty file;
        return infile;
    }
    int size;
    container.clear();//we first clear the buff in the container
    read(infile,size);//then we use read(istream, Ttype) to read in size

    for (int i = 0; i < size; ++i)
    {//we then read every element use read(istream Ttype) and a vector push_back;
       T t;
       read(infile,t);
       container.insert(t);
    }

    //check whether we have read successfully
    assert(infile.good());

    return infile;
}
//map//////////////////////////////////////////////////
template<class K, class V>
static inline istream& read(istream& infile, map<K,V>& container){
    //this function implement a read from input file(infile) of a vector type container
    if(!infile.good() || infile.eof()){
        //we do not read a dirty file or empty file;
        return infile;
    }
    int size;
    container.clear();//we first clear the buff in the container
    read(infile,size);//then we use read(istream, Ttype) to read in size

    for (int i = 0; i < size; ++i)
    {//we then read every element use read(istream Ttype) and a vector push_back;
       
       K key;
       V value;

       read(infile,key);
       read(infile,value);

       container[key] = value;
    }

    //check whether we have read successfully
    assert(infile.good());

    return infile;
}

//-------------------------------------------------------------
//end showing read functions

//below we show all the deser functions, including elementType and STL_container(vector、list、set、map)
//-------------------------------------------------------------
template<class ElementType>
ElementType deserialize(ElementType &a,std::string fileName)
{//this function do a ser of fundamental type of cpp;
    a = ElementType();
    std::fstream str;
    str.open(fileName, std::ios::in | std::ios::binary);
    //could be done simply via istream.read in istream.tcc
    str.read((char*)(&a), sizeof(a));
    ///str.write(reinterpret_cast<ElementType*>(&a), std::aligned_storage<sizeof(ElementType),std::alignment_of<ElementType>::value>::type);
    str.close();
    return a;
}
//vector/////////////////////////////////////////////////////
template<class T>
void deserialize(vector<T>& container,std::string fileName){
//this function do a ser of vector type of cpp;
    container =  vector<T>();
    std::ifstream str;
    str.open(fileName, std::ios::in | std::ios::binary);

    //we use a different kind of read implement as above.
    read(str,container);
    str.clear();
    cout << "vector_test done, pause and break now;"<< endl;
    system("pause");
    return ;
}
//list//////////////////////////////////////////////////////
template<class T>
void deserialize(list<T>& container, std::string fileName){
//this function do a ser of list type of cpp;
    container = list<T>();
    std::ifstream str;
    str.open(fileName, std::ios::in | std::ios::binary);

    //we use a different kind of read implement as above
    read(str, container);
    str.clear();

    cout << "list_test done, pause and break now;" <<endl;
    system("pause");
    return ;
}
//set////////////////////////////////////////////////////////
template<class T>
void deserialize(set<T>& container, std::string fileName){
    //this function do a ser of set type of cpp;
    container = set<T>();
    std::ifstream str;
    str.open(fileName, std::ios::in | std::ios::binary);

    //we use a different kind of read implement as above
    read(str, container);
    str.clear();

    cout << "list_test done, pause and break now;" <<endl;
    system("pause");
    return ;
}
//map/////////////////////////////////////////////////////
template<class K, class V>
void deserialize(map<K,V>& container, std::string fileName){
    //this function do a ser of set type of cpp;
    container = map<K,V>();
    std::ifstream str;
    str.open(fileName, std::ios::in | std::ios::binary);

    //we use a different kind of read implement as above
    read(str, container);
    str.clear();

    cout << "list_test done, pause and break now;" <<endl;
    system("pause");
    return ;
}


//-------------------------------------------------------------
//end showing deser functions






template<class ElementType>
void serialize_xml(ElementType a,std::string stltype,std::string fileName){

}

template<class ElementType>
void deserialize_xml(ElementType a,std::string stltype,std::string fileName){

}
