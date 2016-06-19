#pragma once
#include"delegate.h"
#include<memory>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#define RTTI_DECLARATION(Type,Parent)\
		public:			\
		static std::string ObjectName() { return std::string(#Type);}												\
		virtual bool Is(std::string name) const 																\
	{																												\
		if (name == ObjectName())																					\
			return true;																							\
		else																										\
																													\
		{																											\
			return (Parent::Is(name));																				\
		}																											\
	}																												\
virtual bool Is(std::uint64_t id) const                                                  \
			{                                                                                                \
				if (id == sRunTimeTypeId)                                                                    \
					{ return true; }                                                                         \
				else                                                                                         \
					{ return Parent::Is(id); }                                                               \
			}  \
template<typename T>   \
T* As()                \
{                      \
	if (T::TypeIdClass())    \
	{                        \
		return new T();      \
	}                        \
	return nullptr;         \
}                           \
	static std::uint64_t TypeIdClass() { return sRunTimeTypeId; }                                    \
	private:                                                                                         \
				static std::uint64_t sRunTimeTypeId;

#define RTTI_DEFINITION(Type) std::uint64_t Type::sRunTimeTypeId = reinterpret_cast<std::uint64_t>(&Type::sRunTimeTypeId);

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
