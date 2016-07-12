#pragma once
#include"delegate.h"
#include<memory>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#define TRAIN_WITH_DATA 1
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

const float WINDOW_WIDTH = 900;
const float WINDOW_HEIGHT = 900;
const float FLOOR_X = 0;
const float FLOOR_Y = WINDOW_HEIGHT;
const float LEARNING_RATE = 0.5f;
const float ERROR_RATE = 0.0025f;
const float MOMENTUM = 0.9f;
const int COMBO_LENGTH = 6;
const int LengthOfChromosome = 2;
const int POPULATIONSIZE = 3;
class ActivationFunctions
{
public:
	static double Sigmoid(double input)
	{
		return (1 / (1 + exp(-input / 1.0f)));
	}
};
enum class Dir
{
	UP, DOWN, LEFT, RIGHT
};
