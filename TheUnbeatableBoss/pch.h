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

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;
const int NO_OF_ROWS = (WINDOW_HEIGHT / TILE_HEIGHT) + 1;
const int NO_OF_COLS = (WINDOW_WIDTH / TILE_WIDTH) + 1;

const float FLOOR_X = 0;
const float FLOOR_Y = WINDOW_HEIGHT;
const float LEARNING_RATE = 0.5f;
const float ERROR_RATE = 0.0025f;
const float MOMENTUM = 0.9f;
const int COMBO_LENGTH = 4;
const int LengthOfChromosome = 2;

const double CROSSOVER_RATE = 0.7;
const double MUTATION_RATE = 0.001;
const int POP_SIZE = 50;
const int CHROMO_LENGTH = 10;
const int GENE_LENGTH = 2;
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
inline int RandInt(int x, int y) { return rand() % (y - x + 1) + x; }
inline double RandFloat() { return (rand()) / (RAND_MAX + 1.0); }
inline bool   RandBool()
{
	if (RandInt(0, 1)) return true;

	else return false;
}
