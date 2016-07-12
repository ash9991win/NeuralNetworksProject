#include"pch.h"
#include "Chromosome.h"
template<typename T>
 std::function<double(Chromosome<T>&)> Chromosome<T>::FitnessFunction;

 template<>
 std::function<double(Chromosome<Dir>&)> Chromosome<Dir>::FitnessFunction;