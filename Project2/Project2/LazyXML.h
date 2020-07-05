/*
Bryan B.
byebyebryan@gmail.com

simple & stupid c++ auto xml serialization based on tinyxml2
*/

#ifndef _LAZY_XML_H
#define _LAZY_XML_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <functional>
#include <assert.h>
#include "tinyxml2.h"

#define LAZY_XML_VAR(var_type, var_name) \
	private: template <typename T0> class LazyXML_##var_name { \
	public: \
		std::string name_; \
		var_type value_; \
		LazyXML_##var_name () : name_(#var_name) { \
			value_ = var_type(); \
			T0::reading_funcs()[#var_name] = std::bind(&T0::VarType<var_type>::reader, std::placeholders::_1, &value_); \
			T0::writing_funcs()[#var_name] = std::bind(&T0::VarType<var_type>::writer, std::placeholders::_1, #var_name, std::cref(value_)); \
		} \
	}; \
	private: LazyXML_##var_name<LayzXMLClass> var_name##_; \
	public: var_type var_name() {return var_name##_.value_;} \
	public: void set_##var_name(const var_type & value) {var_name##_.value_ = value;}

namespace lazyxml {
	using namespace tinyxml2;

	template<typename T>
	class LazyXMLBase {
	public:
		//singleton implementation
		static T* GetInstance() {
			static T* instance = new T();
			return instance;
		}

		typedef T LayzXMLClass;

		//stream in from xml
		void ReadFromFile(const std::string & file_name) {
			std::ifstream fileStream(file_name);
			std::stringstream stringBuffer;
			stringBuffer << fileStream.rdbuf();
			ReadFromBuffer(stringBuffer.str());
		}
		void ReadFromBuffer(const std::string & buffer) {
			XMLDocument * xmlDoc = new XMLDocument();
			xmlDoc->Parse(buffer.c_str());
			XMLElement * xmlNode = xmlDoc->RootElement()->FirstChildElement();
			while (xmlNode)
			{
				auto it = reading_funcs().find(xmlNode->Name());
				if (it != reading_funcs().end())
				{
					it->second(xmlNode);
				}
				xmlNode = xmlNode->NextSiblingElement();
			}
			delete xmlDoc;
		}

		//stream out to xml
		void WriteToBuffer(std::string & buffer) {
			XMLDocument * xmlDoc = new XMLDocument();
			XMLDeclaration * xmlDecl = xmlDoc->NewDeclaration();
			xmlDoc->InsertFirstChild(xmlDecl);
			XMLElement * rootElement = xmlDoc->NewElement("root");
			xmlDoc->InsertEndChild(rootElement);

			for (auto & it : writing_funcs())
			{
				it.second(rootElement);
			}

			XMLPrinter xmlPrinter;
			xmlDoc->Print(&xmlPrinter);
			buffer = std::string(xmlPrinter.CStr());
		}
		void WriteToFile(const std::string & file_name) {
			std::string buffer;
			WriteToBuffer(buffer);
			std::ofstream fileStream(file_name);
			fileStream << buffer;
		}

	protected:
		// container struct to provide read/write function for generic type T
		//  -default implementation block execution
		//  -specialize T to override
		template<typename T>
		struct VarType
		{
			static void reader(tinyxml2::XMLElement * xmlElement, T & value)
			{
				std::cerr << "missing XML reading function for value type : " << typeid(T).name() << std::endl;
				assert(false);
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const T & value)
			{
				std::cerr << "missing XML writing function for value type : " << typeid(T).name() << std::endl;
				assert(false);
			}
		};

		// partially specialized read/write for container type std::vector<T>
		//  -calls fully specialized read/write for type T
		template<typename T>
		struct VarType < std::vector<T> >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, std::vector<T> * value)
			{
				tinyxml2::XMLElement * childElement = xmlElement->FirstChildElement();
				while (childElement)
				{
					T childValue;
					VarType<T>::reader(childElement, &childValue);
					value->push_back(childValue);
					childElement = childElement->NextSiblingElement();
				}
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const std::vector<T> & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				for (auto & item : value)
				{
					VarType<T>::writer(newElement, "item", item);
				}
				xmlElement->InsertEndChild(newElement);
			}
		};

		// fully specialized read/write for bool
		template<>
		struct VarType < bool >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, bool * value)
			{
				xmlElement->QueryBoolText(value);
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const bool & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				newElement->SetText(value);
				xmlElement->InsertEndChild(newElement);
			}
		};

		// fully specialized read/write for int
		template<>
		struct VarType < int >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, int * value)
			{
				xmlElement->QueryIntText(value);
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const int & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				newElement->SetText(value);
				xmlElement->InsertEndChild(newElement);
			}
		};

		// fully specialized read/write for float
		template<>
		struct VarType < float >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, float * value)
			{
				xmlElement->QueryFloatText(value);
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const float & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				newElement->SetText(value);
				xmlElement->InsertEndChild(newElement);
			}
		};

		// fully specialized read/write for double
		template<>
		struct VarType < double >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, double * value)
			{
				xmlElement->QueryDoubleText(value);
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const double & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				newElement->SetText(value);
				xmlElement->InsertEndChild(newElement);
			}
		};

		// fully specialized read/write for std::string
		template<>
		struct VarType < std::string >
		{
			static void reader(tinyxml2::XMLElement * xmlElement, std::string * value)
			{
				*value = xmlElement->GetText();
			}

			static void writer(tinyxml2::XMLElement * xmlElement, const std::string & name, const std::string & value)
			{
				tinyxml2::XMLElement * newElement = xmlElement->GetDocument()->NewElement(name.c_str());
				newElement->SetText(value.c_str());
				xmlElement->InsertEndChild(newElement);
			}
		};

		//reading/writing function maps
		static std::unordered_map<std::string, std::function<void(tinyxml2::XMLElement *)>> & reading_funcs() {
			static std::unordered_map<std::string, std::function<void(tinyxml2::XMLElement *)>> funcs;
			return funcs;
		};
		static std::unordered_map<std::string, std::function<void(tinyxml2::XMLElement *)>> & writing_funcs() {
			static std::unordered_map<std::string, std::function<void(tinyxml2::XMLElement *)>> funcs;
			return funcs;
		}
	};
}

#endif // _LAZY_XML_H