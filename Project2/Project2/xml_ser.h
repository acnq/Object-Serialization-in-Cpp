#pragma once
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
#include <typeinfo>
#include "tinyxml2.h"


namespace xml_ser {
	using namespace tinyxml2;
	//read and write 

	//int/////////////////////////////////////////////////////////////////////////
	void writeText(XMLElement* xmlElement, int a, std::string fileName) {

		XMLDocument doc;

		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* newElement = xmlElement->GetDocument()->NewElement("int");
		newElement->SetText(a);
		xmlElement->InsertEndChild(newElement);

		doc.SaveFile(fileName.c_str());

	}
	void readText(XMLElement* xmlElement, int& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(int) " << std::endl;
			system("pause");
		}

		//function atoi is used to convert const char* to int
		const char* p = xmlElement->GetText();
		a = atoi(p);
		return;
	}
	
	//double///////////////////////////////////////////////////
	void writeText(XMLElement* xmlElement, double a, std::string fileName) {

		XMLDocument doc;

		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* newElement = xmlElement->GetDocument()->NewElement("double");
		newElement->SetText(a);
		xmlElement->InsertEndChild(newElement);

		doc.SaveFile(fileName.c_str());

	}
	void readText(XMLElement* xmlElement, double& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(double) " << std::endl;
			system("pause");
		}

		//function atoi is used to convert const char* to int
		const char* p = xmlElement->GetText();
		a = strtod(p,NULL);
		return;
	}
	//string///////////////////////////////////////////////////
	void writeText(XMLElement* xmlElement, std::string a, std::string fileName) {

		XMLDocument doc;

		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* newElement = xmlElement->GetDocument()->NewElement("string");
		newElement->SetText(a.c_str());
		xmlElement->InsertEndChild(newElement);

		doc.SaveFile(fileName.c_str());

	}
	void readText(XMLElement* xmlElement, std::string& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(int) " << std::endl;
			system("pause");
		}

		//function atoi is used to convert const char* to int
		a = xmlElement->GetText();
		return;
	}

	//STLContainer////////////////////////////////////////////
	
	//pair////////////////////////////////////////////////////
	template<typename T1, typename T2>
	void writeText(XMLElement* xmlElement, std::pair<T1, T2>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* Node = xmlElement->GetDocument()->NewElement("pair");
		doc.SaveFile(fileName.c_str());

		writeText(Node, a.first, fileName);
		writeText(Node, a.second, fileName);
		xmlElement->InsertEndChild(Node);

		doc.SaveFile(fileName.c_str());
	}
	template<typename T1, typename T2>
	void readText(XMLElement* xmlElement, std::pair<T1, T2>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(double) " << std::endl;
			system("pause");
		}
		XMLElement* childElement = xmlElement->FirstChildElement();
		readText(childElement, a.first, fileName);
		readText(childElement->NextSiblingElement(), a.second, fileName);
		return;
	}
	
	//vector///////////////////////////////////////////////
	template<typename T>
	void writeText(XMLElement* xmlElement, std::vector<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(vector)" << std::endl;
			system("pause");
		}

		XMLElement* Node = xmlElement->GetDocument()->NewElement("vector");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(Node, ite, fileName);
		}
		xmlElement->InsertEndChild(Node);

		doc.SaveFile(fileName.c_str());
	}
	template<typename T>
	void readText(XMLElement* xmlElement, std::vector<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(vector) " << std::endl;
			system("pause");
		}
		a.clear();
		XMLElement* childElement = xmlElement->FirstChildElement();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);

			
			a.push_back(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//list////////////////////////////////////////////////
	template<typename T>
	void writeText(XMLElement* xmlElement, std::list<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* Node = xmlElement->GetDocument()->NewElement("list");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(Node, ite, fileName);
		}
		xmlElement->InsertEndChild(Node);

		doc.SaveFile(fileName.c_str());
	}
	template<typename T>
	void readText(XMLElement* xmlElement, std::list<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(list) " << std::endl;
			system("pause");
		}
		a.clear();
		XMLElement* childElement = xmlElement->FirstChildElement();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);
			
			
			a.push_back(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//set///////////////////////////////////////////////
	template<typename T>
	void writeText(XMLElement* xmlElement, std::set<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* Node = xmlElement->GetDocument()->NewElement("list");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(Node, ite, fileName);
		}
		xmlElement->InsertEndChild(Node);

		doc.SaveFile(fileName.c_str());
	}
	template<typename T>
	void readText(XMLElement* xmlElement, std::set<T>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(list) " << std::endl;
			system("pause");
		}
		XMLElement* childElement = xmlElement->FirstChildElement();
		a.clear();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);

			
			a.insert(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//map////////////////////////////////////////////////
	template<typename K,typename V>
	void writeText(XMLElement* xmlElement, std::map<K,V>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in writeText(pair)" << std::endl;
			system("pause");
		}

		XMLElement* Node = xmlElement->GetDocument()->NewElement("map");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(Node, ite.first, fileName);
			writeText(Node, ite.second, fileName);
		}

		xmlElement->InsertEndChild(Node);

		doc.SaveFile(fileName.c_str());
	}
	template<typename K,typename V>
	void readText(XMLElement* xmlElement, std::map<K,V>& a, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed in readText(list) " << std::endl;
			system("pause");
		}
		
		a.clear();
		XMLElement* childElement = xmlElement->FirstChildElement();
		while (childElement)
		{
			K childKey;
			V childValue;

			readText(childElement, childKey, fileName);
			childElement = childElement->NextSiblingElement();
			readText(childElement, childValue, fileName);


			a[childKey] = childValue;

			childElement = childElement->NextSiblingElement();

		}

		return;
	}


	//-----------------------------------------------------------------------------------
	//serialize and deserialize
	//int/////////////////////////////////////////////////////
	void serialize_xml(int a, std::string stltype, std::string fileName) {
		//this function do a ser of fundamental type of cpp;
		
		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("int");
		root->SetText(a);
		doc.InsertEndChild(root);
		


		doc.SaveFile(fileName.c_str());

		return;
	}
	void deserialize_xml(int& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();
		
		//function atoi is used to convert const char* to int
		const char* p = root->GetText();
		a = atoi(p);
		return;
	}

	//double////////////////////////////////////////////////
	void serialize_xml(double a, std::string stltype, std::string fileName) {
		//this function do a ser of fundamental type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("double");
		root->SetText(a);
		doc.InsertEndChild(root);



		doc.SaveFile(fileName.c_str());

		return;
	}
	void deserialize_xml(double& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();

		//function strtod is used to convert const char* p to double 
		const char* p = root->GetText();
		a = strtod(p,NULL);
		return;
	}
	
	//string/////////////////////////////////////////////////
	void serialize_xml(std::string a, std::string stltype, std::string fileName) {
		//this function do a ser of fundamental type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("string");
		root->SetText(a.c_str());
		doc.InsertEndChild(root);



		doc.SaveFile(fileName.c_str());

		return;
	}
	void deserialize_xml(std::string& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();


		a = root->GetText();
		return;
	}

	
	//STLContainer----------------------------------------------
	//pair/////////////////////////////////////////////////////////
	template<typename T1,typename T2>
	void serialize_xml(std::pair<T1, T2>& a, std::string stltype, std::string fileName) {
		//this function do a ser of pair type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		
		XMLElement* root = doc.NewElement("pair");
		doc.SaveFile(fileName.c_str());
		writeText(root,a.first,fileName);
		writeText(root,a.second,fileName);
		//root->SetText(a.c_str());
		doc.InsertEndChild(root);



		doc.SaveFile(fileName.c_str());

		return;
	}
	template<typename T1,typename T2>
	void deserialize_xml(std::pair<T1, T2>& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();


		XMLElement* childElement = root->FirstChildElement();
		readText(childElement, a.first,fileName);
		readText(childElement->NextSiblingElement(), a.second,fileName);
		return;
	}
	
	//vector////////////////////////////////////////////////////
	template<typename T>
	void serialize_xml(std::vector<T>&a, std::string stltype, std::string fileName) {
		//this function do a ser of pair type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);


		XMLElement* root = doc.NewElement("vector");
		doc.SaveFile(fileName.c_str());
		
		for (auto& ite: a)
		{
			writeText(root, ite, fileName);
		}
		
		doc.InsertEndChild(root);
		doc.SaveFile(fileName.c_str());

		return;
	}
	template<typename T>
	void deserialize_xml(std::vector<T>& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();

		a.clear();
		XMLElement* childElement = root->FirstChildElement();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);

			
			a.push_back(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//list/////////////////////////////////////////////////////
	template<typename T>
	void serialize_xml(std::list<T>&a, std::string stltype, std::string fileName) {
		//this function do a ser of pair type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);


		XMLElement* root = doc.NewElement("list");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(root, ite, fileName);
		}

		doc.InsertEndChild(root);
		doc.SaveFile(fileName.c_str());

		return;
	}
	template<typename T>
	void deserialize_xml(std::list<T>& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();


		a.clear();
		XMLElement* childElement = root->FirstChildElement();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);
			

			a.push_back(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//set////////////////////////////////////////////////////////
	template<typename T>
	void serialize_xml(std::set<T>&a, std::string stltype, std::string fileName) {
		//this function do a ser of pair type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);


		XMLElement* root = doc.NewElement("set");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(root, ite, fileName);
		}

		doc.InsertEndChild(root);
		doc.SaveFile(fileName.c_str());

		return;
	}
	template<typename T>
	void deserialize_xml(std::set<T>& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();

		a.clear();
		XMLElement* childElement = root->FirstChildElement();
		while (childElement)
		{
			T childValue;
			readText(childElement, childValue, fileName);

			a.insert(childValue);
			childElement = childElement->NextSiblingElement();
		}
		return;
	}
	
	//map/////////////////////////////////////////////////////////
	template<typename K,typename V>
	void serialize_xml(std::map<K,V>&a, std::string stltype, std::string fileName) {
		//this function do a ser of pair type of cpp;

		//we first build a file
		XMLDocument doc;

		//add necessary declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);


		XMLElement* root = doc.NewElement("map");
		doc.SaveFile(fileName.c_str());

		for (auto& ite : a)
		{
			writeText(root, ite.first, fileName);
			writeText(root, ite.second, fileName);
		}

		doc.InsertEndChild(root);
		doc.SaveFile(fileName.c_str());

		return;
	}
	template<typename K, typename V>
	void deserialize_xml(std::map<K,V>& a, std::string stltype, std::string fileName) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str()) != 0) {
			std::cout << "load xml file failed " << std::endl;
			system("pause");
		}

		XMLElement* root = doc.RootElement();

		a.clear();
		XMLElement* childElement = root->FirstChildElement();
		while (childElement)
		{
			K childKey;
			V childValue;

			readText(childElement, childKey, fileName);
			childElement = childElement->NextSiblingElement();
			readText(childElement, childValue, fileName);


			a[childKey] = childValue;

			childElement = childElement->NextSiblingElement();

		}
		return;
	}

}



/*
namespace binary_ser {
	using namespace std;

	class FileOp
	{//this is a class of file operation
	public:
		//it implement the  basic function of write and read
		virtual std::ostream& write(std::ostream& ostr) = 0;
		virtual std::istream& read(std::istream& istr) = 0;
	};

	static inline bool LE();
	static inline ostream& write(ostream& outfile, FileOp* f);
	static inline ostream& write_internal(ostream& outfile, const char* p, uint32_t size);
	static inline ostream& write_string(ostream& outfile, const std::string& str);
	template<typename T>
	static inline ostream& write(ostream& outfile, T& t);
	template <class T>
	static inline ostream& write(ostream& outfile, vector<T>& container);
	template <class T>
	static inline ostream& write(ostream& outfile, list<T>& container);
	template <class T>
	static inline ostream& write(ostream& outfile, set<T>& container);
	template<class K, class V>
	static inline ostream& write(ostream& outfile, map<K, V>& container);
	template<class ElementType>
	void serialize(ElementType a, std::string fileName);
	template<class T>
	void serialize(vector<T>& container, std::string fileName);
	template<class T>
	void serialize(list<T>& container, std::string fileName);
	template <class T>
	static inline ostream& write(ostream& outfile, set<T>& container);
	template<class K, class V>
	void serialize(map<K, V>& container, std::string fileName);
	static inline istream& read(istream& infile, FileOp* f);
	static inline istream& read_string(istream& infile, std::string str);
	static inline istream& read_internal(istream& infile, char* p, uint32_t size);
	template <class T>
	static inline istream& read(istream& infile, T& t);
	template<class T>
	static inline istream& read(istream& infile, vector<T>& container);
	template<class T>
	static inline istream& read(istream& infile, list<T>& container);
	template<class T>
	static inline istream& read(istream& infile, set<T>& container);
	template<class K, class V>
	static inline istream& read(istream& infile, map<K, V>& container);
	template<class ElementType>
	ElementType deserialize(ElementType &a, std::string fileName);
	template<class T>
	void deserialize(vector<T>& container, std::string fileName);
	template<class T>
	void deserialize(list<T>& container, std::string fileName);
	template<class T>
	void deserialize(set<T>& container, std::string fileName);
	template<class K, class V>
	void deserialize(map<K, V>& container, std::string fileName);




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
	//------------------------------------------------------------------


	static inline bool LE() {
		//this function is here for a test of alignment
		//whether your computer use little endian, or big endian in your computer's memory system
		//we assume all variable are stored in the same endian
		//so we need only test the storage of variable integer "1";
		const static int n = 1;
		const static bool le = (*(char*)&n == 1);//test whether a little endian 
		return le;
	}
	static inline ostream& write(ostream& outfile, FileOp* f) {//thid write is used to make the other writes usable.
		return f->write(outfile);
	}
	static inline ostream& write_internal(ostream& outfile, const char* p, uint32_t size) {
		//this function write data in the outfile via a char pointer p
		if (!LE()) {
			//if big endian. we write it as little endian
			for (int i = size - 1; i >= 0; --i)
			{
				outfile.write(p + i, 1);//we use write function in ostream.tcc
			}
		}
		else
		{   //use pointer to write content;
			outfile.write(p, size);//we use write function in ostream.tcc
		}
		return outfile;
	}
	static inline ostream& write(ostream& outfile, const std::string& str) {
		uint32_t size = str.size();

		write(outfile, size);

		write_internal(outfile, str.c_str(), str.size());

		return outfile;
	}
	static inline ostream& write(ostream& outfile, std::string& str) {
		uint32_t size = str.size();

		write(outfile, size);
		write_internal(outfile, str.c_str(), str.size());

		return outfile;
	}
	//below we show all the write functions, for fundamental type and cpp STL container pair�?vector、list、set、map
	//-------------------------------------------
	template<typename T>
	static inline ostream& write(ostream& outfile, T& t) {
		//this function write a Type t variable to the output file
		//we now just implememt fundamental type;

		if (std::is_fundamental<T>::value) {
			//we construct a pointer, and use write_internal funct to write every element to the outputfile
			return write_internal(outfile, (const char*)& t, sizeof(t));
		}
		else
		{
			
			//if want a implememtation of user_define type just add code here
			cout << "sorry, we do not support non_fundamental STL container type\n" << endl;
			cout << "if continue , there may be bugs\n" << endl;
			return write_internal(outfile, (const char*)& t, sizeof(t));
		}
	}
	//vector//////////////////////////////////////////////////
	template <class T>
	static inline ostream& write(ostream& outfile, vector<T>& container) {
		//this function implement a writing to outfile of vector type
		uint32_t size = container.size();

		//we first write the size info of this vector via write(outfile T t);
		write(outfile, size);

		//then we do a loop to write every element in the vector;
		for (auto& ite : container)
		{
			write(outfile, ite);
		}
		return outfile;
	}
	//list//////////////////////////////////////////////////////
	template <class T>
	static inline ostream& write(ostream& outfile, list<T>& container) {
		//this function implement a writing to outfile of list type
		uint32_t size = container.size();

		//we first write the size info of this list via write(outfile T t);
		write(outfile, size);

		//then we do a loop to write every element in the list;
		for (auto& ite : container)
		{
			write(outfile, ite);
		}
		return outfile;

	}
	//set/////////////////////////////////////////////////
	template <class T>
	static inline ostream& write(ostream& outfile, set<T>& container) {
		//this function implement a writing to outfile of set type
		uint32_t size = container.size();

		//we first write the size info of this set via write(outfile T t);
		write(outfile, size);

		//then we do a loop to write every element in the set;
		for (auto& ite : container)
		{
			write(outfile, ite);
		}
		return outfile;

	}
	//map//////////////////////////////////////////////////
	template<class K, class V>
	static inline ostream& write(ostream& outfile, map<K, V>& container) {
		//this function implement a writing to outfile of map type
		uint32_t size = container.size();

		//we first write the size info of this set via write(outfile T t);
		write(outfile, size);

		//then we do a loop to write every element in the set;
		for (auto& p : container)
		{
			write(outfile, p.first);
			write(outfile, p.second);
		}
		return outfile;
	}



	//-------------------------------------------------------
	//end showing write function



	//below we show all the ser functions, including elementType and STL_container(vector、list、set、map)
	//-------------------------------------------------------------
	template<class ElementType>
	void serialize(ElementType a, std::string fileName)
	{//this function do a ser of fundamental type of cpp;

		std::fstream str;
		str.open(fileName, std::ios::out | std::ios::binary);

		//just a simple fstream.write will work, for int, string and pair;
		str.write((char*)(&a), sizeof(a));
		///str.write(reinterpret_cast<ElementType*>(&a), std::aligned_storage<sizeof(ElementType),std::alignment_of<ElementType>::value>::type);
		str.close();
	}
	//vector///////////////////////////////////////////////
	template<class T>
	void serialize(vector<T>& container, std::string fileName) {
		//this function do a ser of vector of T type(now fundamental T only)
		std::ofstream str;
		str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

		//we must use a different kind of write to implement the write-out method.
		write(str, container);
		str.flush();
		str.close();
	}
	//list////////////////////////////////////////////////
	template<class T>
	void serialize(list<T>& container, std::string fileName) {
		//this function do a ser of list of T type(now fundamental T only)
		std::ofstream str;
		str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

		//we use a very similar read function as vector do  to implememte a write-out
		write(str, container);
		str.flush();
		str.close();
	}
	//set//////////////////////////////////////////
	template<class T>
	void serialize(set<T>& container, std::string fileName) {
		//this function do a ser of set of T type(now fundamental T only)
		std::ofstream str;
		str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

		//we use a very similar read function as vector do  to implememte a write-out
		write(str, container);
		str.flush();
		str.close();
	}
	//map/////////////////////////////////////////
	template<class K, class V>
	void serialize(map<K, V>& container, std::string fileName) {
		//this function do a ser of set of T type(now fundamental T only)
		std::ofstream str;
		str.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

		//we use a very similar read function as vector do  to implememte a write-out
		write(str, container);
		str.flush();
		str.close();
	}

	//-------------------------------------------------------------
	//end showing ser functions

	static inline istream& read(istream& infile, FileOp* f) {//this write is used to make the other writes usable.
		return f->read(infile);
	}
	static inline istream& read(istream& infile, std::string& str) {
		int size = 0;
		read(infile, size);
		str.resize(size);
		read_internal(infile, const_cast<char*> (str.c_str()), size);

		return infile;
	}
	static inline istream& read_internal(istream& infile, char* p, uint32_t size) {
		//this function read data in the outfile via a char pointer p
		//very similar as write_internal function as above; we do not comment it  then
		if (!LE()) {
			for (int i = size - 1; i >= 0; --i)
			{
				infile.read(p + i, 1);
			}
		}
		else
		{
			infile.read(p, size);
		}
		return infile;
	}


	//below we show all the read functions, for fundamental type and cpp STL container pair�?vector、list、set、map
	//------------------------------------------------------------------------------


	template<class T>
	static inline istream& read(istream& infile, T& t) {
		//this function read a Type t variable from the input file
		//we now just implememt fundamental type;
		if (std::is_fundamental<T>::value) {
			return read_internal(infile, (char*)& t, sizeof(t));
		}
		else
		{
			
			//if want a implememtation of user_define type just add code here
			cout << "Sorry we do not support non_fundamental_type STL_container " << endl;
		}
		return infile;
	}
	//vector////////////////////////////////////////////////////
	template<class T>
	static inline istream& read(istream& infile, vector<T>& container) {
		//this function implement a read from input file(infile) of a vector type container
		if (!infile.good() || infile.eof()) {
			//we do not read a dirty file or empty file;
			return infile;
		}
		int size;
		container.clear();//we first clear the buff in the container
		read(infile, size);//then we use read(istream, Ttype) to read in size
		for (int i = 0; i < size; ++i)
		{//we then read every element use read(istream Ttype) and a vector push_back;
			T t;
			read(infile, t);
			container.push_back(t);
		}

		//check whether we have read successfully
		assert(infile.good());

		return infile;
	}
	//list////////////////////////////////////////////////
	template<class T>
	static inline istream& read(istream& infile, list<T>& container) {
		//this function implement a read from input file(infile) of a vector type container
		if (!infile.good() || infile.eof()) {
			//we do not read a dirty file or empty file;
			return infile;
		}
		int size;
		container.clear();//we first clear the buff in the container
		read(infile, size);//then we use read(istream, Ttype) to read in size
		for (int i = 0; i < size; ++i)
		{//we then read every element use read(istream Ttype) and a vector push_back;
			T t;
			read(infile, t);
			container.push_back(t);
		}

		//check whether we have read successfully
		assert(infile.good());

		return infile;
	}
	//set//////////////////////////////////////////////////
	template<class T>
	static inline istream& read(istream& infile, set<T>& container) {
		//this function implement a read from input file(infile) of a vector type container
		if (!infile.good() || infile.eof()) {
			//we do not read a dirty file or empty file;
			return infile;
		}
		int size;
		container.clear();//we first clear the buff in the container
		read(infile, size);//then we use read(istream, Ttype) to read in size

		for (int i = 0; i < size; ++i)
		{//we then read every element use read(istream Ttype) and a vector push_back;
			T t;
			read(infile, t);
			container.insert(t);
		}

		//check whether we have read successfully
		assert(infile.good());

		return infile;
	}
	//map//////////////////////////////////////////////////
	template<class K, class V>
	static inline istream& read(istream& infile, map<K, V>& container) {
		//this function implement a read from input file(infile) of a vector type container
		if (!infile.good() || infile.eof()) {
			//we do not read a dirty file or empty file;
			return infile;
		}
		int size;
		container.clear();//we first clear the buff in the container
		read(infile, size);//then we use read(istream, Ttype) to read in size

		for (int i = 0; i < size; ++i)
		{//we then read every element use read(istream Ttype) and a vector push_back;

			K key;
			V value;

			read(infile, key);
			read(infile, value);

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
	ElementType deserialize(ElementType &a, std::string fileName)
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
	void deserialize(vector<T>& container, std::string fileName) {
		//this function do a ser of vector type of cpp;
		container = vector<T>();
		std::ifstream str;
		str.open(fileName, std::ios::in | std::ios::binary);

		//we use a different kind of read implement as above.
		read(str, container);
		str.clear();
		cout << "vector_test done, pause and break now;" << endl;
		system("pause");
		return;
	}
	//list//////////////////////////////////////////////////////
	template<class T>
	void deserialize(list<T>& container, std::string fileName) {
		//this function do a ser of list type of cpp;
		container = list<T>();
		std::ifstream str;
		str.open(fileName, std::ios::in | std::ios::binary);

		//we use a different kind of read implement as above
		read(str, container);
		str.clear();

		cout << "list_test done, pause and break now;" << endl;
		system("pause");
		return;
	}
	//set////////////////////////////////////////////////////////
	template<class T>
	void deserialize(set<T>& container, std::string fileName) {
		//this function do a ser of set type of cpp;
		container = set<T>();
		std::ifstream str;
		str.open(fileName, std::ios::in | std::ios::binary);

		//we use a different kind of read implement as above
		read(str, container);
		str.clear();

		cout << "list_test done, pause and break now;" << endl;
		system("pause");
		return;
	}
	//map/////////////////////////////////////////////////////
	template<class K, class V>
	void deserialize(map<K, V>& container, std::string fileName) {
		//this function do a ser of set type of cpp;
		container = map<K, V>();
		std::ifstream str;
		str.open(fileName, std::ios::in | std::ios::binary);

		//we use a different kind of read implement as above
		read(str, container);
		str.clear();

		cout << "list_test done, pause and break now;" << endl;
		system("pause");
		return;
	}


	//-------------------------------------------------------------
	//end showing deser functions

};
*/