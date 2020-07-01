#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>
#include "ObjSertemplate.hpp"
using namespace std;
void test_arithmetic_type_binary_ser(void);
void test_string_type_binary_ser(void);
void test_pair_type_binary_ser(void);
void test_vector_type_binary_ser(void);
void test_list_type_binary_ser(void);
void test_set_type_binary_ser(void);
void test_map_type_binary_ser(void);

void test_arithmetic_type_XML_ser(void);
void test_string_type_XML_ser(void);
void test_pair_type_XML_ser(void);
void test_vector_type_XML_ser(void);
void test_list_type_XML_ser(void);
void test_set_type_XML_ser(void);
void test_map_type_XML_ser(void);

int main(){

    //we first test single arithmetic types in binary serialization
    std :: cout << "now begin a binary serialization test" << endl; //give instruct for the tester;
    cout << "\n" << endl;//this line for format control in terminal;
    test_arithmetic_type_binary_ser();//actuall work run here;
    cout << "\n" << endl;//this line also for format control in terminal;
    
    // we then test  C++ string types
    cout << "\n" << endl;//this line for format control in termianl;
    test_string_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;
    


    //we then test C++  STL types
    //1.std::pair
    cout << "\n" << endl;//this line for format control;
    test_pair_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;

    //2.std::vector
    cout << "\n" << endl;//this line for format control;
    test_vector_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;
    
    //3.std::list
    cout << "\n" << endl;//this line for format control;
    test_list_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;

    //4.std::set
    cout << "\n" << endl;//this line for format control;
    test_set_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;

    //3.std::map
    cout << "\n" << endl;//this line for format control;
    test_map_type_binary_ser();//actual work run here;
    cout << "\n" << endl;//this line for format control;

    std::cout << "end a binary serialization test" << endl;

    std :: cout << "now begin a XML serialization test" << endl;
    cout << "\n" << endl;//this line for format control;

    /*//we second test single arithmetic types in XML serialization
    test_arithmetic_type_XML_ser();
    
    // we then test  C++ string types
    test_string_type_XML_ser();
    


    //we then test C++  STL types
    //1.std::pair
    test_pair_type_XML_ser();

    //2.std::vector
    test_vector_type_XML_ser();
    
    //3.std::list
    test_list_type_XML_ser();

    //4.std::set
    test_set_type_XML_ser();

    //3.std::map
    test_map_type_XML_ser();
    */
    //lastly we test the user_define variables
    std::cout << "Begin test User define type in Binary Serialization" << endl;
    struct UserDefineType
    {
        int idx;
        std::string name;
        std::vector<double> data;
    };
    struct UserDefineType u0,u1;
    u0 = {1,"KKK",{1.2,1.4}};

    //since the mememory do not align in this variable
    //we do not support a serialize(u0,"u.data") mechanism
    //we will support a mechanism of distributive serialize 
    
    //serialize object n0 to a binary file n.data   
    serialize(u0.idx,"u_i.data");
    serialize(u0.name,"u_n.data");
    serialize(u0.data,"u_d.data");

    //reconstruct object n1 from the content of n.data
    deserialize(u1.idx,"u.data");
    deserialize(u1.name,"u_n.data");
    deserialize(u1.data,"u_d.data");

    std::cout << "u0 = " << "{" << u0.idx << "," << u0.name << "," << "[" << u0.data[0] << "," << u0.data[1]<< "]" << "}" << endl;
    std::cout << "u1 = " << "{" << u1.idx << "," << u1.name << "," << "[" << u1.data[0] << "," << u1.data[1]<<"]" << "}" << endl;
    if (u0.data == u1.data && u0.idx == u0.idx && u0.name == u1.name)
        std::cout << "user define type test success in Binary Serialization" << endl;
    else
        std::cout << "user define type test went wrong in Binary Serialization" << endl;

    /*std :: cout << "Begin test User define type in XML Serialization" << endl;
    serialize_xml(u0,"user_define_type","n.data");

    //reconstruct object n1 from the content of n.data
    deserialize_xml(u1,"user_define_type","n.data");

    std::cout << "u0 = " << "{" << u0.idx << "," << u0.name << "," << "[" << u0.data[0] << "," << u0.data[2]<< "]" << "}" << endl;
    std::cout << "u1 = " << "{" << u1.idx << "," << u1.name << "," << "[" << u1.data[0] << "," << u1.data[2]<<"]" << "}" << endl;
    if (u0.data == u1.data && u0.idx == u0.idx && u0.name == u1.name)
        std::cout << "user define type test success in XML Serialization" << endl;
    else
        std::cout << "user define type test went wrong in XML Serialization" << endl;
    */
    
    
    
    
    


    std::system("pause");
    return 0;
}

void test_arithmetic_type_binary_ser(void){
    std::cout << "Begin test arithmetic type\n" << endl;
    int n0 = 256,n1;

    //serialize object n0 to a binary file n.data   
    serialize<int>(n0,"n.data");

    //reconstruct object n1 from the content of n.data
    deserialize<int>(n1,"n.data");

    // the line below run a output of n0 and n1, for the tester to check every element
    std::cout << "n0 = " << n0 << " " << "n1 = "<< n1  << " " << (bool) (n0 == n1) <<endl; 

    //the 4 lines below run a computer check of whether n0 == n1;
    if (n0 == n1)
        std::cout << "\narithmetic type testing succeess" << endl;
    else
        std::cout << "\narithmetic type testing went wrong" << endl;
     //now n0 == n1 should be true.
    return;
}
void test_arithmetic_type_XML_ser(void){
    std::cout << "Begin test arithmetic type" << endl;
    int n0 = 256,n1;

    //serialize object n0 to a binary file n.xml   
    serialize_xml(n0,"int","n.xml");

    //reconstruct object n1 from the content of n.xml
    deserialize_xml(n1,"int","n.xml");

    // the line below run a output of n0 and n1, for the tester to check every element
    std::cout << "n0 = " << n0 << " " << "n1 = "<< n1  << " " << (bool) (n0 == n1) <<endl; 
    if (n0 == n1)
        std::cout << "arithmetic type testing succeess" << endl;
    else
        std::cout << "arithmetic type testing went wrong" << endl;
     //now n0 == n1 should be true.
    return;
}
//the function below is very similar as test_arithmetic_type_XML_ser(void), we do not comment them so.
//...unless necessary;
void test_string_type_binary_ser(void){
    std::cout << "Begin test cpp String type\n" << endl;

    string s0 = "HelloWorld",s1;
    serialize<string>(s0,"s.data");
    deserialize<string>(s1,"s.data");
    std::cout << "s0 = " << s0 << " " << "s1 = "<< s1  << " " << (bool) (s0 == s1) <<endl;

    if (s0 == s1)
        std::cout << "\nstring type testing succeess" << endl;
    else
        std::cout << "\nstring type testing went wrong" << endl;
}
void test_string_type_XML_ser(void){
    std::cout << "Begin test cpp String type" << endl;

    string s0 = "HelloWorld",s1;
    serialize_xml(s0,"string","s.xml");
    deserialize_xml(s1,"strring","s.xml");
    std::cout << "s0 = " << s0 << " " << "s1 = "<< s1  << " " << (bool) (s0 == s1) <<endl;

    if (s0 == s1)
        std::cout << "string type testing succeess" << endl;
    else
        std::cout << "string type testing went wrong" << endl;
}
void test_pair_type_binary_ser(void){
    std::cout << "Begin test cpp stl:pair type\n" << endl;

    std::pair<int,double> p0 = {2,4.0},p1;
    serialize<std::pair<int,double>>(p0,"p.data");
    deserialize<std::pair<int,double>>(p1,"p.data");
    std::cout << "p0 = " << " <" << p0.first  << "," << p0.second << ">" 
        << " " << "p1 = "<< " <" << p1.first  << "," << p1.second << ">" 
        << " "  << (bool) (p0 == p1) <<endl;
    if (p0 == p1)

        std::cout << "\npair type testing succeess" << endl;
    else
        std::cout << "\npair type testing went wrong" << endl;

}
void test_pair_type_XML_ser(void){
    std::cout << "Begin test cpp stl:pair type" << endl;

    std::pair<int,double> p0 = {2,4.0},p1;
    serialize_xml(p0,"std_pair","p.xml");
    deserialize_xml(p1,"std_pair","p.xml");
    std::cout << "p0 = " << " <" << p0.first  << "," << p0.second << ">" 
        << " " << "p1 = "<< " <" << p1.first  << "," << p1.second << ">" 
        << " "  << (bool) (p0 == p1) <<endl;
    if (p0 == p1)

        std::cout << "pair type testing succeess" << endl;
    else
        std::cout << "pair type testing went wrong" << endl;

}
void test_vector_type_binary_ser(void){
    std::cout << "Begin test cpp stl:vector type\n" << endl;

    std::vector<int> v0 = {2,4,6},v1 = {0,0,0};
    serialize(v0,"v.data");
    deserialize(v1,"v.data");
    //we use index to output every element in the vector,3 lines below output the element in vector for tester to check
    std::cout << "v0 = " << " [" << v0[0]  << "," << v0[1]  << "," << v0[2] << "]" 
        << " " << "v1 = " << " [" << v1[0]  << "," << v1[1]  << "," << v1[2] << "]" 
        << " " << (bool) (v0 == v1) <<endl;
    
    // a computer check below is in the 4 lines below
    if (v0 == v1)
        std::cout << "\nvector type testing succeess" << endl;
    else
        std::cout << "\nvector type testing went wrong" << endl;
}
void test_vector_type_XML_ser(void){
    std::cout << "Begin test cpp stl:vector type" << endl;

    std::vector<int> v0 = {2,4,6},v1;
    serialize_xml(v0,"std_vector","v.xml");
    deserialize_xml(v1,"std_vector","v.xml");
    std::cout << "v0 = " << " [" << v0[0]  << "," << v0[1]  << "," << v0[2] << "]" 
        << " " << "v1 = " << " [" << v1[0]  << "," << v1[1]  << "," << v1[2] << "]" 
        << " " << (bool) (v0 == v1) <<endl;
    if (v0 == v1)
        std::cout << "vector type testing succeess" << endl;
    else
        std::cout << "vector type testing went wrong" << endl;
}

void test_list_type_binary_ser(void){
    std::cout << "Begin test cpp stl:list type\n" << endl;

    std::list<int> l0 ,l1;
    l0.push_front(1);
    l0.push_front(2);
    l0.push_front(3);

    l1.push_front(0);
    l1.push_front(0);
    l1.push_front(0);

    serialize(l0,"l.data");
    deserialize(l1,"l.data");
    list<int> ::iterator li = l0.begin();
    list<int> :: iterator lj = l1.begin();
    std::cout << "l0 = " << " [" << *li  << "," << *(li++)  << "," << *(li++) << "]" 
        << " " << "l1 = " << " [" << *lj  << "," << *(lj++)  << "," << *(lj++) << "]" 
        << " " << (bool) (l0 == l1) <<endl;
    if (l0 == l1)
        std::cout << "\nlist type testing succeess" << endl;
    else
        std::cout << "\nlist type testing went wrong" << endl;
}

void test_list_type_XML_ser(void){
    std::cout << "Begin test cpp stl:list type" << endl;

    std::list<int> l0 = {2,4,6},l1;
    serialize_xml(l0,"std_list","v.xml");
    deserialize_xml(l1,"std_list","v.xml");
    list<int> ::iterator li = l0.begin();
    list<int> :: iterator lj = l1.begin();
    std::cout << "l0 = " << " [" << *li  << "," << *(++li)  << "," << *(++li) << "]" 
        << " " << "l1 = " << " [" << *lj  << "," << *(++lj)  << "," << *(++lj) << "]" 
        << " " << (bool) (l0 == l1) <<endl;
    if (l0 == l1)
        std::cout << "list type testing succeess" << endl;
    else
        std::cout << "list type testing went wrong" << endl;
}

void test_set_type_binary_ser(void){
    std::cout << "Begin test cpp stl:set type\n" << endl;

    std::set<int> st0 ,st1;
    st0.insert(1);
    st0.insert(2);
    st0.insert(3);

    st1.insert(0);
    st1.insert(-1);
    st1.insert(-2);

    
    serialize(st0,"st.data");
    deserialize(st1,"st.data");
    set<int> ::iterator sti = st0.begin();
    set<int> :: iterator stj = st1.begin();
    //std::cout << *sti << endl;
    std::cout << "st0 = " << " [" << *sti  << "," << *(sti++)  << "," << *(sti++) << "]" 
        << " " << "st1 = " << " [" << *stj  << "," << *(stj++)  << "," << *(stj++) << "]" 
        << " " << (bool) (st0 == st1) <<endl;
    if (st0 == st1)
        std::cout << "\nset type testing succeess" << endl;
    else
        std::cout << "\nset type testing went wrong" << endl;
}
void test_set_type_XML_ser(void){
    std::cout << "Begin test cpp stl:set type" << endl;

    std::set<int> st0 = {2,4,6},st1;
    serialize_xml(st0,"std_xml","v.xml");
    deserialize_xml(st1,"std_xml","v.xml");
    set<int> ::iterator sti = st0.begin();
    set<int> :: iterator stj = st1.begin();
    std::cout << "l0 = " << " [" << *sti  << "," << *(++sti)  << "," << *(++sti) << "]" 
        << " " << "l1 = " << " [" << *stj  << "," << *(++stj)  << "," << *(++stj) << "]" 
        << " " << (bool) (st0 == st1) <<endl;
    if (st0 == st1)
        std::cout << "set type testing succeess" << endl;
    else
        std::cout << "set type testing went wrong" << endl;
}

void test_map_type_binary_ser(void){
    std::cout << "Begin test cpp stl:map type\n" << endl;

    std::map<int,double> m0,m1;
    m0.insert(pair<int,double>(0,0.1));
    m0.insert(pair<int,double>(1,1.1));
    m0.insert(pair<int,double>(2,1.2));

    m1.insert(pair<int,double>(0,-0.1));
    m1.insert(pair<int,double>(-1,-0.2));
    m1.insert(pair<int,double>(-2,-0.3));



    serialize(m0,"m.data");
    deserialize(m1,"m.data");
    map<int,double> ::iterator mi = m0.begin();
    map<int,double> ::iterator mj = m1.begin();

    std::cout << "m0 = " << " {" <<endl;
    for ( ; mi != m0.end(); mi++)
    {
        std::cout << "<"<<mi->first << ", " << mi->second << ">" << endl;
    }
    std::cout << "}" << endl;

    std::cout << "m0 = " << " {" <<endl;
    for ( ; mj != m1.end(); mj++)
    {
        std::cout << "<"<<mj->first << ", " << mj->second << ">" << endl;
    }
    std::cout << "}" << endl;
    
    if (m0 == m1)
        std::cout << "\nmap type testing succeess" << endl;
    else
        std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_XML_ser(void){
    std::cout << "Begin test cpp stl:map type" << endl;

    std::map<int,string> m0,m1;
    m0.insert(pair<int,string>(0,"m0"));
    m0.insert(pair<int,string>(1,"m1"));
    m0.insert(pair<int,string>(2,"m2"));

    serialize_xml(m0,"std_map","v.xml");
    deserialize_xml(m1,"std_map","v.xml");
    map<int,string> ::iterator mi = m0.begin();
    map<int,string> ::iterator mj = m1.begin();

    std::cout << "m0 = " << " {" <<endl;
    for ( ; mi != m0.end(); mi++)
    {
        std::cout << "<"<<mi->first << mi->second << endl;
    }
    std::cout << "}" << endl;

    std::cout << "m0 = " << " {" <<endl;
    for ( ; mj != m0.end(); mj++)
    {
        std::cout << "<"<<mi->first << mi->second << endl;
    }
    std::cout << "}" << endl;
    
    if (m0 == m1)
        std::cout << "map type testing succeess" << endl;
    else
        std::cout << "map type testing went wrong" << endl;
}