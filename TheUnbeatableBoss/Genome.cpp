#include"pch.h"
#include "Genome.h"
template<typename T>
 function<void(T)> Genome<T>::UpdateFunction;
 template<>
 function<void(Dir)> Genome<Dir>::UpdateFunction;

template<typename T>
vector<T> Genome<T>::list;
template<>
vector<float> Genome<float>::list;
template<>
vector<Dir> Genome<Dir>::list;

