#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "xml_ser.h"

using namespace std;
void test_arithmetic_type_xml_ser(void);
void test_arithmetic_type_xml_ser2(void);
void test_string_type_xml_ser(void);
void test_pair_type_xml_ser(void);
void test_vector_type_xml_ser(void);
void test_vector_type_xml_ser2(void);
void test_vector_type_xml_ser3(void);
void test_list_type_xml_ser(void);
void test_list_type_xml_ser2(void);
void test_list_type_xml_ser3(void);
void test_set_type_xml_ser(void);
void test_set_type_xml_ser2(void);
void test_set_type_xml_ser3(void);
void test_map_type_xml_ser(void);
void test_map_type_xml_ser2(void);
void test_map_type_xml_ser3(void);
void test_map_type_xml_ser4(void);
void test_complicated_xml(void);


int main() {

	

	//we second test single arithmetic types in XML serialization
	std::cout << "\n" << std::endl; //this \n is here for output format control
	test_arithmetic_type_xml_ser();
	test_arithmetic_type_xml_ser2();
	std::cout << "\n" << std::endl;

	// we then test  C++ string types
	std::cout << "\n" << std::endl;
	test_string_type_xml_ser();
	std::cout << "\n" << std::endl;


	//we then test C++  STL types
	//1.std::pair
	std::cout << "\n" << std::endl;
	test_pair_type_xml_ser();
	std::cout << "\n" << std::endl;

	//2.std::vector
	std::cout << "\n" << std::endl;
	test_vector_type_xml_ser();
	test_vector_type_xml_ser2();
	test_vector_type_xml_ser3();
	std::cout << "\n" << std::endl;

	//3.std::list
	std::cout << "\n" << std::endl;
	test_list_type_xml_ser();
	test_list_type_xml_ser2();
	test_list_type_xml_ser3();
	std::cout << "\n" << std::endl;

	//4.std::set
	std::cout << "\n" << std::endl;
	test_set_type_xml_ser();
	test_set_type_xml_ser2();
	test_set_type_xml_ser3();
	std::cout << "\n" << std::endl;

	//3.std::map
	std::cout << "\n" << std::endl;
	test_map_type_xml_ser();
	test_map_type_xml_ser2();
	test_map_type_xml_ser3();
	test_map_type_xml_ser4();
	std::cout << "\n" << std::endl;

	//complicated
	//the method we construct would support container loop 
	//we test vector<map<string,string>> 
	test_complicated_xml();

	//lastly we test the user_define variables
	struct UserDefineType
	{
		int idx;
		std::string name;
		std::vector<double> data;
	};
	struct UserDefineType u0, u1;
	u0 = { 1,"KKK",{1.2,1.4} };

	
	std :: cout << "Begin test User define type in XML Serialization" << endl;
	xml_ser::serialize_xml(u0.idx,"user_define_type","u0idx.xml");
	xml_ser::serialize_xml(u0.name, "user_define_type", "u0name.xml");
	xml_ser::serialize_xml(u0.data, "user_define_type", "u0data.xml");

	//reconstruct object n1 from the content of n.data
	xml_ser::deserialize_xml(u1.idx,"user_define_type","u0idx.xml");
	xml_ser::deserialize_xml(u1.name, "user_define_type", "u0name.xml");
	xml_ser::deserialize_xml(u1.data, "user_define_type", "u0data.xml");

	std::cout << "u0 = " << "{" << u0.idx << "," << u0.name << "," << "[" << u0.data[0] << "," << u0.data[1]<< "]" << "}" << endl;
	std::cout << "u1 = " << "{" << u1.idx << "," << u1.name << "," << "[" << u1.data[0] << "," << u1.data[1]<<"]" << "}" << endl;
	if (u0.data == u1.data && u0.idx == u0.idx && u0.name == u1.name)
		std::cout << "user define type test success in XML Serialization" << endl;
	else
		std::cout << "user define type test went wrong in XML Serialization" << endl;
	







	std::system("pause");
	return 0;
}


void test_arithmetic_type_xml_ser(void) {
	std::cout << "Begin test arithmetic type" << endl;
	int n0 = 256, n1;

	//serialize object n0 to a xml file n.xml   
	xml_ser::serialize_xml(n0, "int", "n.xml");

	//reconstruct object n1 from the content of n.xml
	xml_ser::deserialize_xml(n1, "int", "n.xml");

	// the line below run a output of n0 and n1, for the tester to check every element
	std::cout << "n0 = " << n0 << " " << "n1 = " << n1 << " " << (bool)(n0 == n1) << endl;
	if (n0 == n1)
		std::cout << "arithmetic type testing succeess" << endl;
	else
		std::cout << "arithmetic type testing went wrong" << endl;
	//now n0 == n1 should be true.
	return;
}
void test_arithmetic_type_xml_ser2(void) {
	std::cout << "Begin test arithmetic type" << endl;
	double d0 = 0.256, d1;

	//serialize object n0 to a xml file n.xml   
	xml_ser::serialize_xml(d0, "double", "dbl.xml");

	//reconstruct object n1 from the content of n.xml
	xml_ser::deserialize_xml(d1, "double", "dbl.xml");

	// the line below run a output of n0 and n1, for the tester to check every element
	std::cout << "n0 = " << d0 << " " << "n1 = " << d1 << " " << (bool)(d0 == d1) << endl;
	if (d0 == d1)
		std::cout << "arithmetic type testing succeess" << endl;
	else
		std::cout << "arithmetic type testing went wrong" << endl;
	//now n0 == n1 should be true.
	return;
}

void test_string_type_xml_ser(void) {
	std::cout << "Begin test cpp String type" << endl;

	string s0 = "HelloWorld", s1;
	xml_ser::serialize_xml(s0, "string", "s.xml");
	xml_ser::deserialize_xml(s1, "strring", "s.xml");
	std::cout << "s0 = " << s0 << " " << "s1 = " << s1 << " " << (bool)(s0 == s1) << endl;

	if (s0 == s1)
		std::cout << "string type testing succeess" << endl;
	else
		std::cout << "string type testing went wrong" << endl;
}

void test_pair_type_xml_ser(void) {
	std::cout << "Begin test cpp stl:pair type" << endl;

	std::pair<int, double> p0 = { 2,0.4 }, p1;
	xml_ser::serialize_xml(p0, "std_pair", "p.xml");
	xml_ser::deserialize_xml(p1, "std_pair", "p.xml");
	std::cout << "p0 = " << " <" << p0.first << "," << p0.second << ">"
		<< " " << "p1 = " << " <" << p1.first << "," << p1.second << ">"
		<< " " << (bool)(p0 == p1) << endl;
	if (p0 == p1)

		std::cout << "pair type testing succeess" << endl;
	else
		std::cout << "pair type testing went wrong" << endl;

}


void test_vector_type_xml_ser(void) {
	std::cout << "Begin test cpp stl:vector type" << endl;

	std::vector<int> v0 = { 2,4,6 }, v1;
	xml_ser::serialize_xml(v0, "std_vector", "v.xml");
	xml_ser::deserialize_xml(v1, "std_vector", "v.xml");
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "," << v0[2] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "," << v1[2] << "]"
		<< " " << (bool)(v0 == v1) << endl;
	if (v0 == v1)
		std::cout << "vector type testing succeess" << endl;
	else
		std::cout << "vector type testing went wrong" << endl;
}
void test_vector_type_xml_ser2(void) {//test vector<string>
	std::cout << "Begin test cpp stl:vector<string> type\n" << endl;

	std::vector<std::string> v0 = { "Hello","World" }, v1 = { "Foo","Bar" };
	xml_ser::serialize_xml(v0, "std_vector","v2.xml");
	xml_ser::deserialize_xml(v1, "std_vector","v2.xml");
	//we use index to output every element in the vector,3 lines below output the element in vector for tester to check
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "]"
		<< " " << (bool)(v0 == v1) << endl;

	// a computer check below is in the 4 lines below
	if (v0 == v1)
		std::cout << "\nvector string type testing succeess" << endl;
	else
		std::cout << "\nvector  string type testing went wrong" << endl;
}
void test_vector_type_xml_ser3(void) {//test vector<double>
	std::cout << "Begin test cpp stl:vector<double> type\n" << endl;

	std::vector<double> v0 = { 2.2,4.4,6.6 }, v1 = { 0.0,0.0,0.0 };
	xml_ser::serialize_xml(v0,"stl_vector", "v3.xml");
	xml_ser::deserialize_xml(v1,"stl_vector", "v3.xml");
	//we use index to output every element in the vector,3 lines below output the element in vector for tester to check
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "," << v0[2] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "," << v1[2] << "]"
		<< " " << (bool)(v0 == v1) << endl;

	// a computer check below is in the 4 lines below
	if (v0 == v1)
		std::cout << "\nvector type double testing succeess" << endl;
	else
		std::cout << "\nvector type double testing went wrong" << endl;
}

void test_list_type_xml_ser(void) {
	std::cout << "Begin test cpp stl:list type" << endl;

	std::list<int> l0 = { 2,4,6 }, l1;
	xml_ser::serialize_xml(l0, "std_list", "lst.xml");
	xml_ser::deserialize_xml(l1, "std_list", "lst.xml");
	list<int> ::iterator li = l0.begin();
	list<int> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(++li) << "," << *(++li) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(++lj) << "," << *(++lj) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "list type testing succeess" << endl;
	else
		std::cout << "list type testing went wrong" << endl;
}
void test_list_type_xml_ser2(void) {//test set<double>
	std::cout << "Begin test cpp stl:list<double> type\n" << endl;

	std::list<double> l0, l1;
	l0.push_front(1.1);
	l0.push_front(2.1);
	l0.push_front(3.1);

	l1.push_front(0.0);
	l1.push_front(0.0);
	l1.push_front(0.0);

	xml_ser::serialize_xml(l0,"stl_list", "l1.xml");
	xml_ser::deserialize_xml(l1,"stl_list", "l1.xml");
	list<double> ::iterator li = l0.begin();
	list<double> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(li++) << "," << *(li++) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(lj++) << "," << *(lj++) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "\nlist type testing succeess" << endl;
	else
		std::cout << "\nlist type testing went wrong" << endl;
}
void test_list_type_xml_ser3(void) {//test set<string>
	std::cout << "Begin test cpp stl:list<string> type\n" << endl;

	std::list<std::string> l0, l1;
	l0.push_front("Hello");
	l0.push_front("World");


	l1.push_front("Foo");
	l1.push_front("Bar");


	xml_ser::serialize_xml(l0,"stl_list", "l2.xml");
	xml_ser::deserialize_xml(l1,"stl_list", "l2.xml");
	list<std::string> ::iterator li = l0.begin();
	list<std::string> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(li++) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(lj++) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "\nlist type testing succeess" << endl;
	else
		std::cout << "\nlist type testing went wrong" << endl;
}

void test_set_type_xml_ser(void) {
	std::cout << "Begin test cpp stl:set type" << endl;

	std::set<int> st0 = { 2,4,6 }, st1;
	xml_ser::serialize_xml(st0, "std_xml", "st.xml");
	xml_ser::deserialize_xml(st1, "std_xml", "st.xml");
	set<int> ::iterator sti = st0.begin();
	set<int> ::iterator stj = st1.begin();
	std::cout << "l0 = " << " [" << *sti << "," << *(++sti) << "," << *(++sti) << "]"
		<< " " << "l1 = " << " [" << *stj << "," << *(++stj) << "," << *(++stj) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "set type testing succeess" << endl;
	else
		std::cout << "set type testing went wrong" << endl;
}
void test_set_type_xml_ser2(void) {//test set<double>
	std::cout << "Begin test cpp stl:set<double> type\n" << endl;

	std::set<double> st0, st1;
	st0.insert(1.1);
	st0.insert(2.1);
	st0.insert(3.1);

	st1.insert(0.0);
	st1.insert(-1.1);
	st1.insert(-2.1);


	xml_ser::serialize_xml(st0,"stl_set", "st2.xml");
	xml_ser::deserialize_xml(st1,"stl_set", "st2.xml");
	set<double> ::iterator sti = st0.begin();
	set<double> ::iterator stj = st1.begin();
	//std::cout << *sti << endl;
	std::cout << "st0 = " << " [" << *sti << "," << *(sti++) << "," << *(sti++) << "]"
		<< " " << "st1 = " << " [" << *stj << "," << *(stj++) << "," << *(stj++) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "\nset type testing succeess" << endl;
	else
		std::cout << "\nset type testing went wrong" << endl;
}
void test_set_type_xml_ser3(void) {//test set<string>
	std::cout << "Begin test cpp stl:set<string> type\n" << endl;

	std::set<std::string> st0, st1;
	st0.insert("Hello");
	st0.insert("World");
	st0.insert("Set");

	st1.insert("Set");
	st1.insert("Set");
	st1.insert("Set");


	xml_ser::serialize_xml(st0,"set", "st3.xml");
	xml_ser::deserialize_xml(st1,"set", "st3.xml");
	set<std::string> ::iterator sti = st0.begin();
	set<std::string> ::iterator stj = st1.begin();
	//std::cout << *sti << endl;
	std::cout << "st0 = " << " [" << *sti << "," << *(sti++) << "," << *(sti++) << "]"
		<< " " << "st1 = " << " [" << *stj << "," << *(stj++) << "," << *(stj++) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "\nset type testing succeess" << endl;
	else
		std::cout << "\nset type testing went wrong" << endl;
}


void test_map_type_xml_ser(void) {
	std::cout << "Begin test cpp stl:map type" << endl;

	std::map<int, string> m0, m1;
	m0.insert(pair<int, string>(0, "m0"));
	m0.insert(pair<int, string>(1, "m1"));
	m0.insert(pair<int, string>(2, "m2"));

	xml_ser::serialize_xml(m0, "std_map", "mp.xml");
	xml_ser::deserialize_xml(m1, "std_map", "mp.xml");
	map<int, string> ::iterator mi = m0.begin();
	map<int, string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first <<"," << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << "," << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "map type testing succeess" << endl;
	else
		std::cout << "map type testing went wrong" << endl;
}
void test_map_type_xml_ser2(void) {//test map<double,string>
	std::cout << "Begin test cpp stl:map<double,string> type\n" << endl;

	std::map<double, std::string> m0, m1;
	m0.insert(pair<double, std::string>(0.1, "m01"));
	m0.insert(pair<double, std::string>(0.2, "m02"));
	m0.insert(pair<double, std::string>(0.3, "m03"));

	m1.insert(pair<double, std::string>(0.0, "m00"));
	m1.insert(pair<double, std::string>(-0.1, "m10"));
	m1.insert(pair<double, std::string>(-0.2, "m20"));



	xml_ser::serialize_xml(m0,"std_map", "mp2.xml");
	xml_ser::deserialize_xml(m1,"std_map", "mp2.xml");
	map<double, std::string> ::iterator mi = m0.begin();
	map<double, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_xml_ser3(void) {//test map<int,string>
	std::cout << "Begin test cpp stl:map<int,string> type\n" << endl;

	std::map<int, std::string> m0, m1;
	m0.insert(pair<int, std::string>(1, "m01"));
	m0.insert(pair<int, std::string>(2, "m02"));
	m0.insert(pair<int, std::string>(3, "m03"));

	m1.insert(pair<int, std::string>(0, "n00"));
	m1.insert(pair<int, std::string>(-1, "n10"));
	m1.insert(pair<int, std::string>(-2, "n20"));



	xml_ser::serialize_xml(m0,"stl_map", "m3.xml");
	xml_ser::deserialize_xml(m1,"stl_map", "m3.xml");
	map<int, std::string> ::iterator mi = m0.begin();
	map<int, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_xml_ser4(void) {//test map<string,string>
	std::cout << "Begin test cpp stl:map<string,string> type\n" << endl;

	std::map<std::string, std::string> m0, m1;
	m0.insert(pair<std::string, std::string>("M01", "m01"));
	m0.insert(pair<std::string, std::string>("M02", "m02"));
	m0.insert(pair<std::string, std::string>("M03", "m03"));

	m1.insert(pair<std::string, std::string>("N00", "n00"));
	m1.insert(pair<std::string, std::string>("N10", "n10"));
	m1.insert(pair<std::string, std::string>("N20", "n20"));



	xml_ser::serialize_xml(m0,"stl_map", "m4.xml");
	xml_ser::deserialize_xml(m1,"stl_map", "m4.xml");
	map<std::string, std::string> ::iterator mi = m0.begin();
	map<std::string, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}

void test_complicated_xml(void) {//test vector<map<string,string>>
	std::cout << "Begin test complicated stl vector<map<string,string>>: type\n" << endl;

	std::vector<map<string, string>> c0, c1;
	std::map<string, string> m0, m1;
	m0.insert(pair<std::string, std::string>("M02", "m02"));
	m1.insert(pair<std::string, std::string>("N01", "n02"));
	c0.push_back(m0);
	c1.push_back(m1);


	xml_ser::serialize_xml(c0,"stl_vector", "c.xml");
	xml_ser::deserialize_xml(c1,"stl_vector ","c.xml");


	cout << "c0[0] = {" << (c0[0].begin())->first << "," << (c0[0].begin())->second << "}\n" << std::endl;
	cout << "c1[0] = {" << (c1[0].begin())->first << "," << (c1[0].begin())->second << "}\n" << std::endl;
	if (c0 == c1) {
		cout << "complicated test succeceed" << endl;
	}
	else
	{
		cout << "complicated test went wrong" << endl;
	}


}

/*
void test_arithmetic_type_binary_ser(void) {
	std::cout << "Begin test arithmetic type\n" << endl;
	int n0 = 256, n1;

	//serialize object n0 to a binary file n.xml   
	binary_ser::serialize<int>(n0, "n.data");

	//reconstruct object n1 from the content of n.data
	binary_ser::deserialize<int>(n1, "n.data");

	// the line below run a output of n0 and n1, for the tester to check every element
	std::cout << "n0 = " << n0 << " " << "n1 = " << n1 << " " << (bool)(n0 == n1) << endl;

	//the 4 lines below run a computer check of whether n0 == n1;
	if (n0 == n1)
		std::cout << "\narithmetic type testing succeess" << endl;
	else
		std::cout << "\narithmetic type testing went wrong" << endl;
	//now n0 == n1 should be true.
	return;
}
//the function below is very similar as test_arithmetic_type_XML_ser(void), we do not comment them so.
//...unless necessary;
void test_string_type_binary_ser(void) {
	std::cout << "Begin test cpp String type\n" << endl;

	string s0 = "HelloWorld", s1;
	binary_ser::serialize<string>(s0, "s.data");
	binary_ser::deserialize<string>(s1, "s.data");
	std::cout << "s0 = " << s0 << " " << "s1 = " << s1 << " " << (bool)(s0 == s1) << endl;

	if (s0 == s1)
		std::cout << "\nstring type testing succeess" << endl;
	else
		std::cout << "\nstring type testing went wrong" << endl;
}

void test_pair_type_binary_ser(void) {
	std::cout << "Begin test cpp stl:pair<int,double> type\n" << endl;

	std::pair<int, double> p0 = { 2,4.0 }, p1;
	binary_ser::serialize<std::pair<int, double>>(p0, "p.data");
	binary_ser::deserialize<std::pair<int, double>>(p1, "p.data");
	std::cout << "p0 = " << " <" << p0.first << "," << p0.second << ">"
		<< " " << "p1 = " << " <" << p1.first << "," << p1.second << ">"
		<< " " << (bool)(p0 == p1) << endl;
	if (p0 == p1)

		std::cout << "\npair type testing succeess" << endl;
	else
		std::cout << "\npair type testing went wrong" << endl;

}

void test_vector_type_binary_ser1(void) {//test vector<int>
	std::cout << "Begin test cpp stl:vector<int> type\n" << endl;

	std::vector<int> v0 = { 2,4,6 }, v1 = { 0,0,0 };
	binary_ser::serialize(v0, "v.data");
	binary_ser::deserialize(v1, "v.data");
	//we use index to output every element in the vector,3 lines below output the element in vector for tester to check
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "," << v0[2] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "," << v1[2] << "]"
		<< " " << (bool)(v0 == v1) << endl;

	// a computer check below is in the 4 lines below
	if (v0 == v1)
		std::cout << "\nvector int  type  testing succeess" << endl;
	else
		std::cout << "\nvector int  type testing went wrong" << endl;
}
void test_vector_type_binary_ser2(void) {//test vector<string>
	std::cout << "Begin test cpp stl:vector<string> type\n" << endl;

	std::vector<std::string> v0 = { "Hello","World" }, v1 = { "Foo","Bar" };
	binary_ser::serialize(v0, "v2.data");
	binary_ser::deserialize(v1, "v2.data");
	//we use index to output every element in the vector,3 lines below output the element in vector for tester to check
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "]"
		<< " " << (bool)(v0 == v1) << endl;

	// a computer check below is in the 4 lines below
	if (v0 == v1)
		std::cout << "\nvector string type testing succeess" << endl;
	else
		std::cout << "\nvector  string type testing went wrong" << endl;
}
void test_vector_type_binary_ser3(void) {//test vector<double>
	std::cout << "Begin test cpp stl:vector<double> type\n" << endl;

	std::vector<double> v0 = { 2.2,4.4,6.6 }, v1 = { 0.0,0.0,0.0 };
	binary_ser::serialize(v0, "v3.data");
	binary_ser::deserialize(v1, "v3.data");
	//we use index to output every element in the vector,3 lines below output the element in vector for tester to check
	std::cout << "v0 = " << " [" << v0[0] << "," << v0[1] << "," << v0[2] << "]"
		<< " " << "v1 = " << " [" << v1[0] << "," << v1[1] << "," << v1[2] << "]"
		<< " " << (bool)(v0 == v1) << endl;

	// a computer check below is in the 4 lines below
	if (v0 == v1)
		std::cout << "\nvector type double testing succeess" << endl;
	else
		std::cout << "\nvector type double testing went wrong" << endl;
}


void test_list_type_binary_ser(void) {//test set<int>
	std::cout << "Begin test cpp stl:list<int> type\n" << endl;

	std::list<int> l0, l1;
	l0.push_front(1);
	l0.push_front(2);
	l0.push_front(3);

	l1.push_front(0);
	l1.push_front(0);
	l1.push_front(0);

	binary_ser::serialize(l0, "l.data");
	binary_ser::deserialize(l1, "l.data");
	list<int> ::iterator li = l0.begin();
	list<int> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(li++) << "," << *(li++) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(lj++) << "," << *(lj++) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "\nlist type testing succeess" << endl;
	else
		std::cout << "\nlist type testing went wrong" << endl;
}
void test_list_type_binary_ser2(void) {//test set<double>
	std::cout << "Begin test cpp stl:list<double> type\n" << endl;

	std::list<double> l0, l1;
	l0.push_front(1.1);
	l0.push_front(2.1);
	l0.push_front(3.1);

	l1.push_front(0.0);
	l1.push_front(0.0);
	l1.push_front(0.0);

	binary_ser::serialize(l0, "l1.data");
	binary_ser::deserialize(l1, "l1.data");
	list<double> ::iterator li = l0.begin();
	list<double> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(li++) << "," << *(li++) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(lj++) << "," << *(lj++) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "\nlist type testing succeess" << endl;
	else
		std::cout << "\nlist type testing went wrong" << endl;
}
void test_list_type_binary_ser3(void) {//test set<string>
	std::cout << "Begin test cpp stl:list<string> type\n" << endl;

	std::list<std::string> l0, l1;
	l0.push_front("Hello");
	l0.push_front("World");


	l1.push_front("Foo");
	l1.push_front("Bar");


	binary_ser::serialize(l0, "l2.data");
	binary_ser::deserialize(l1, "l2.data");
	list<std::string> ::iterator li = l0.begin();
	list<std::string> ::iterator lj = l1.begin();
	std::cout << "l0 = " << " [" << *li << "," << *(li++) << "]"
		<< " " << "l1 = " << " [" << *lj << "," << *(lj++) << "]"
		<< " " << (bool)(l0 == l1) << endl;
	if (l0 == l1)
		std::cout << "\nlist type testing succeess" << endl;
	else
		std::cout << "\nlist type testing went wrong" << endl;
}


void test_set_type_binary_ser(void) {//test set<int>
	std::cout << "Begin test cpp stl:set<int> type\n" << endl;

	std::set<int> st0, st1;
	st0.insert(1);
	st0.insert(2);
	st0.insert(3);

	st1.insert(0);
	st1.insert(-1);
	st1.insert(-2);


	binary_ser::serialize(st0, "st.data");
	binary_ser::deserialize(st1, "st.data");
	set<int> ::iterator sti = st0.begin();
	set<int> ::iterator stj = st1.begin();
	//std::cout << *sti << endl;
	std::cout << "st0 = " << " [" << *sti << "," << *(sti++) << "," << *(sti++) << "]"
		<< " " << "st1 = " << " [" << *stj << "," << *(stj++) << "," << *(stj++) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "\nset type testing succeess" << endl;
	else
		std::cout << "\nset type testing went wrong" << endl;
}
void test_set_type_binary_ser2(void) {//test set<double>
	std::cout << "Begin test cpp stl:set<double> type\n" << endl;

	std::set<double> st0, st1;
	st0.insert(1.1);
	st0.insert(2.1);
	st0.insert(3.1);

	st1.insert(0.0);
	st1.insert(-1.1);
	st1.insert(-2.1);


	binary_ser::serialize(st0, "st2.data");
	binary_ser::deserialize(st1, "st2.data");
	set<double> ::iterator sti = st0.begin();
	set<double> ::iterator stj = st1.begin();
	//std::cout << *sti << endl;
	std::cout << "st0 = " << " [" << *sti << "," << *(sti++) << "," << *(sti++) << "]"
		<< " " << "st1 = " << " [" << *stj << "," << *(stj++) << "," << *(stj++) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "\nset type testing succeess" << endl;
	else
		std::cout << "\nset type testing went wrong" << endl;
}
void test_set_type_binary_ser3(void) {//test set<string>
	std::cout << "Begin test cpp stl:set<string> type\n" << endl;

	std::set<std::string> st0, st1;
	st0.insert("Hello");
	st0.insert("World");
	st0.insert("Set");

	st1.insert("Set");
	st1.insert("Set");
	st1.insert("Set");


	binary_ser::serialize(st0, "st3.data");
	binary_ser::deserialize(st1, "st3.data");
	set<std::string> ::iterator sti = st0.begin();
	set<std::string> ::iterator stj = st1.begin();
	//std::cout << *sti << endl;
	std::cout << "st0 = " << " [" << *sti << "," << *(sti++) << "," << *(sti++) << "]"
		<< " " << "st1 = " << " [" << *stj << "," << *(stj++) << "," << *(stj++) << "]"
		<< " " << (bool)(st0 == st1) << endl;
	if (st0 == st1)
		std::cout << "\nset type testing succeess" << endl;
	else
		std::cout << "\nset type testing went wrong" << endl;
}



void test_map_type_binary_ser(void) {//test map<double int>
	std::cout << "Begin test cpp stl:map<double,int> type\n" << endl;

	std::map<int, double> m0, m1;
	m0.insert(pair<int, double>(0, 0.1));
	m0.insert(pair<int, double>(1, 1.1));
	m0.insert(pair<int, double>(2, 1.2));

	m1.insert(pair<int, double>(0, -0.1));
	m1.insert(pair<int, double>(-1, -0.2));
	m1.insert(pair<int, double>(-2, -0.3));



	binary_ser::serialize(m0, "m1.data");
	binary_ser::deserialize(m1, "m1.data");
	map<int, double> ::iterator mi = m0.begin();
	map<int, double> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_binary_ser2(void) {//test map<double,string>
	std::cout << "Begin test cpp stl:map<double,string> type\n" << endl;

	std::map<double, std::string> m0, m1;
	m0.insert(pair<double, std::string>(0.1, "m01"));
	m0.insert(pair<double, std::string>(0.2, "m02"));
	m0.insert(pair<double, std::string>(0.3, "m03"));

	m1.insert(pair<double, std::string>(0.0, "m00"));
	m1.insert(pair<double, std::string>(-0.1, "m10"));
	m1.insert(pair<double, std::string>(-0.2, "m20"));



	binary_ser::serialize(m0, "m2.data");
	binary_ser::deserialize(m1, "m2.data");
	map<double, std::string> ::iterator mi = m0.begin();
	map<double, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_binary_ser3(void) {//test map<int,string>
	std::cout << "Begin test cpp stl:map<int,string> type\n" << endl;

	std::map<int, std::string> m0, m1;
	m0.insert(pair<int, std::string>(1, "m01"));
	m0.insert(pair<int, std::string>(2, "m02"));
	m0.insert(pair<int, std::string>(3, "m03"));

	m1.insert(pair<int, std::string>(0, "n00"));
	m1.insert(pair<int, std::string>(-1, "n10"));
	m1.insert(pair<int, std::string>(-2, "n20"));



	binary_ser::serialize(m0, "m3.data");
	binary_ser::deserialize(m1, "m3.data");
	map<int, std::string> ::iterator mi = m0.begin();
	map<int, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_map_type_binary_ser4(void) {//test map<string,string>
	std::cout << "Begin test cpp stl:map<string,string> type\n" << endl;

	std::map<std::string, std::string> m0, m1;
	m0.insert(pair<std::string, std::string>("M01", "m01"));
	m0.insert(pair<std::string, std::string>("M02", "m02"));
	m0.insert(pair<std::string, std::string>("M03", "m03"));

	m1.insert(pair<std::string, std::string>("N00", "n00"));
	m1.insert(pair<std::string, std::string>("N10", "n10"));
	m1.insert(pair<std::string, std::string>("N20", "n20"));



	binary_ser::serialize(m0, "m4.data");
	binary_ser::deserialize(m1, "m4.data");
	map<std::string, std::string> ::iterator mi = m0.begin();
	map<std::string, std::string> ::iterator mj = m1.begin();

	std::cout << "m0 = " << " {" << endl;
	for (; mi != m0.end(); mi++)
	{
		std::cout << "<" << mi->first << ", " << mi->second << ">" << endl;
	}
	std::cout << "}" << endl;

	std::cout << "m0 = " << " {" << endl;
	for (; mj != m1.end(); mj++)
	{
		std::cout << "<" << mj->first << ", " << mj->second << ">" << endl;
	}
	std::cout << "}" << endl;

	if (m0 == m1)
		std::cout << "\nmap type testing succeess" << endl;
	else
		std::cout << "\nmap type testing went wrong" << endl;
}
void test_complicated(void) {//test vector<map<string,string>>
	std::cout << "Begin test complicated stl vector<map<string,string>>: type\n" << endl;

	std::vector<map<string, string>> c0, c1;
	std::map<string, string> m0, m1;
	m0.insert(pair<std::string, std::string>("M02", "m02"));
	m1.insert(pair<std::string, std::string>("N01", "n02"));
	c0.push_back(m0);
	c1.push_back(m1);


	binary_ser::serialize(c0, "c.data");
	binary_ser::deserialize(c1, "c.data");


	cout << "c0[0] = {" << (c0[0].begin())->first << "," << (c0[0].begin())->second << "}\n" << std::endl;
	cout << "c1[0] = {" << (c1[0].begin())->first << "," << (c1[0].begin())->second << "}\n" << std::endl;
	if (c0 == c1) {
		cout << "complicated test succeceed" << endl;
	}
	else
	{
		cout << "complicated test went wrong" << endl;
	}


}
*/