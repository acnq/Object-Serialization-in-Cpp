#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
//魔法:
#define TO_OFFSET(Obj_ty, member_name) ((uint32_t)(&((Obj_ty *)0)->member_name))

#define CLASS_REGISTER(Obj_ty)                                                      \
public:                                                                             \
    static Serialization::ClassInfo *get_class_ptr()                                \
    {                                                                               \
        static Serialization::ClassInfo __class_##Obj_ty##__(std::string(#Obj_ty)); \
        return &__class_##Obj_ty##__;                                               \
    }

#define MEMBER_REGISTER(Access, Member_ty, Member_name, Obj_ty)     \
private:                                                            \
    class __member_register_##Member_name##__                       \
    {                                                               \
    public:                                                         \
        __member_register_##Member_name##__()                       \
        {                                                           \
            static Serialization::MemberRegister reg_##Member_name( \
                Obj_ty::get_class_ptr(),                            \
                TO_OFFSET(Obj_ty, Member_name),                     \
                std::string(#Member_name),                          \
                std::string(#Member_ty));                           \
        }                                                           \
    } Member_name##_register;

#define CLASS_ENABLE(Obj_ty)                                  \
private:                                                      \
    class __class_register_##Obj_ty##__                       \
    {                                                         \
    public:                                                   \
        __class_register_##Obj_ty##__()                       \
        {                                                     \
            static Serialization::ClassRegister reg_##Obj_ty( \
                Obj_ty::get_class_ptr());                     \
        }                                                     \
    } Obj_ty##_register;

#define SERIALIZATION_ENABLE \
    Serialization::Registers __All_Classes__ = Serialization::Registers();

namespace Serialization
{
	//包含如下信息的三元组：成员类型(字符串)，成员名称(字符串)，偏移量指针
	class MemberInfoTriad
	{
	public:
		std::string class_name;
		std::string member_name;
		uint32_t offset;

	public:
		MemberInfoTriad(std::string type_name, std::string member_name, uint32_t offset);
		MemberInfoTriad(const MemberInfoTriad &fri);
		~MemberInfoTriad() {}
		bool operator==(const MemberInfoTriad &s);
		bool operator<=(const MemberInfoTriad &s);
		bool operator>=(const MemberInfoTriad &s);
		bool operator>(const MemberInfoTriad &s);
		bool operator<(const MemberInfoTriad &s);
		template <typename Obj_ty, typename Value_ty>
		void get(Obj_ty *obj, Value_ty &value)
		{
			value = *((Value_ty *)((uint32_t *)obj + offset));
		}
		template <typename Obj_ty, typename Value_ty>
		void set(Obj_ty *obj, Value_ty &value)
		{
			*((Value_ty *)((uint32_t *)obj + offset)) = value;
		}
	};

	//用于储存类的信息
	class ClassInfo
	{
	public:
		std::vector<MemberInfoTriad> members;
		std::string class_name;

	public:
		ClassInfo(std::string type_name);
		~ClassInfo() {};
		std::vector<MemberInfoTriad> get_members();

		MemberInfoTriad get_member(std::string name);

		void registerMember(const MemberInfoTriad &member);

		bool operator==(const ClassInfo &s);
		bool operator>(const ClassInfo &s);
		bool operator<(const ClassInfo &s);
		bool operator<=(const ClassInfo &s);
		bool operator>=(const ClassInfo &s);
	};

	class MemberRegister
	{
	public:
		MemberRegister(ClassInfo *class_ptr, uint32_t offset, std::string memberName, std::string memberType)
		{
			MemberInfoTriad mem = MemberInfoTriad(memberType, memberName, offset);
			class_ptr->registerMember(mem);
		}
	};

	class ClassRegister
	{
	public:
		ClassRegister(ClassInfo *cl);
	};

	class Registers
	{
	private:
		std::vector<ClassInfo> classes;

	public:
		ClassInfo searchClass(std::string cla_name);
		void registerClass(ClassInfo *cla);
	};

} // namespace Serialization

#endif