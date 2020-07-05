#include <iostream>
#include "serialization.h"

extern Serialization::Registers __All_Classes__;

namespace Serialization
{

	MemberInfoTriad::MemberInfoTriad(std::string type_name, std::string member_name, uint32_t offset)
	{
		class_name = type_name;
		this->member_name = member_name;
		this->offset = offset;
	}

	MemberInfoTriad::MemberInfoTriad(const MemberInfoTriad &fr)
	{
		this->offset = fr.offset;
		this->class_name = fr.class_name;
		this->member_name = fr.member_name;
	}
	//这两个函数如果放在h文件里就能成功编译，如果放在这里就会出现链接器错误
	//undefined reference to `void Serialization::MemberInfoTriad::get<test, int>(test*, int&)'
	//还不知道原因，但我不想管了
	/*
	template <typename Obj_ty, typename Value_ty>
	void MemberInfoTriad::get(Obj_ty *obj, Value_ty &value)
	{
		value = *((Value_ty *)((uint32_t *)obj + offset));
	}

	template <typename Obj_ty, typename Value_ty>
	void MemberInfoTriad::set(Obj_ty *obj, Value_ty &value)
	{
		*((Value_ty *)((uint32_t *)obj + offset)) = value;
	}
*/
	bool MemberInfoTriad::operator==(const MemberInfoTriad &s)
	{
		return (this->member_name == s.member_name);
	}
	bool MemberInfoTriad::operator>=(const MemberInfoTriad &s)
	{
		return (this->member_name >= s.member_name);
	}
	bool MemberInfoTriad::operator<=(const MemberInfoTriad &s)
	{
		return (this->member_name <= s.member_name);
	}
	bool MemberInfoTriad::operator<(const MemberInfoTriad &s)
	{
		return (this->member_name < s.member_name);
	}
	bool MemberInfoTriad::operator>(const MemberInfoTriad &s)
	{
		return (this->member_name > s.member_name);
	}

	ClassInfo::ClassInfo(std::string type_name)
	{
		this->class_name = type_name;
		members = std::vector<MemberInfoTriad>();
	}

	std::vector<MemberInfoTriad> ClassInfo::get_members()
	{
		return this->members;
	}

	MemberInfoTriad ClassInfo::get_member(std::string name)
	{
		std::vector<MemberInfoTriad>::iterator tar = find(members.begin(), members.end(), MemberInfoTriad(std::string(""), name, 0));
		if (tar == members.end())
		{
			std::cout << "throw exception:not found" << std::endl;
		}
		return *tar;
	}

	void ClassInfo::registerMember(const MemberInfoTriad &member)
	{
		members.push_back(member);
	}

	bool ClassInfo::operator==(const ClassInfo &s)
	{
		return this->class_name == s.class_name;
	}

	bool ClassInfo::operator>(const ClassInfo &s)
	{
		return this->class_name > s.class_name;
	}

	bool ClassInfo::operator<(const ClassInfo &s)
	{
		return this->class_name < s.class_name;
	}

	bool ClassInfo::operator<=(const ClassInfo &s)
	{
		return this->class_name <= s.class_name;
	}

	bool ClassInfo::operator>=(const ClassInfo &s)
	{
		return this->class_name >= s.class_name;
	}

	ClassRegister::ClassRegister(ClassInfo *cl)
	{
		__All_Classes__.registerClass(cl);
	}

	ClassInfo Registers::searchClass(std::string cla_name)
	{
		ClassInfo tar = ClassInfo(cla_name);
		std::vector<ClassInfo>::iterator iter = find(classes.begin(), classes.end(), tar);
		if (iter == classes.end())
		{
			std::cout << "throw exception:not found" << std::endl;
		}
		return *iter;
	}

	void Registers::registerClass(ClassInfo *cla)
	{
		classes.push_back(*cla);
	}

} // namespace Serialization
  //Serialization::Registers __All_Classes__ = Serialization::Registers();