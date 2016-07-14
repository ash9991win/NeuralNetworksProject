#pragma once
template<typename T>
class Genome
{
public:
	double mFitness;
	vector<int> mBits;
	static int MAXNUMBEROFVALUES;
	static vector<T> Types;
	static map<int, T> DecodingTable;
	static map<int, string> StringDecoder;
	static function<double(vector<T>)> FitnessFunction;
	static void AddPossibleValue(const T& value,string text = "")
	{
		Types.push_back(value);
		if (text != "")
		{
			StringDecoder[MAXNUMBEROFVALUES] = text;
		}
		MAXNUMBEROFVALUES++;
		DecodingTable[MAXNUMBEROFVALUES] = value;
		
	}
	const vector<int>& GetBits() const
	{
		return mBits;
	}
	Genome() = default;
	Genome(int numberOfBits)
	{
		for (int i = 0; i < numberOfBits; i++)
		{
			mBits.push_back(RandInt(0, MAXNUMBEROFVALUES));
		}
	}
};
#define DECLARE_GENOME(Type)      \
 template<>                       \
 int Genome<Type>::MAXNUMBEROFVALUES;   \
 template<>                            \
 vector<Type> Genome<Type>::Types;       \
 template<>                            \
 map<int, Type> Genome<Type>::DecodingTable;  \
 template<>                                 \
 function<double(vector<Type>)> Genome<Type>::FitnessFunction;    \
 template<>                                                     \
 map<int, string> Genome<Type>::StringDecoder;                   