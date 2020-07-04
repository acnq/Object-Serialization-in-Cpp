#include <iostream>
#include <vector>
#include <string>
#include <any>
#include "serialization.h"
using namespace std;
//g++ testor.cpp serialization.cpp -std=c++17
SERIALIZATION_ENABLE

class test
{
public:
	int a;
	double b;

	CLASS_REGISTER(test)

		MEMBER_REGISTER(public, int, a, test)
		MEMBER_REGISTER(public, double, b, test)

		CLASS_ENABLE(test)
};


template <typename T>
void printFirstMemberInfo(T objIn, string typeName);

int main()
{
	test a = test();
	a.a = 1;

	//在其他文件使用需要添加如下语句：
	//extern Serialization::Registers __All_Classes__;
	printFirstMemberInfo(a, "test");
}

template <typename T>
void printFirstMemberInfo(T objIn, string typeName)
{
	Serialization::MemberInfoTriad info = __All_Classes__.searchClass(typeName).members[0];
	//a case struct,omitted
	int t = 0;
	info.get(&objIn, t);
	cout << info.member_name << " " << info.class_name << " " << t << endl;
}