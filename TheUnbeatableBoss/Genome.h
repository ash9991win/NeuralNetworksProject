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
		MAXNUMBEROFVALUES++;
		DecodingTable[MAXNUMBEROFVALUES] = value;
		if (text != "")
		{
			StringDecoder[MAXNUMBEROFVALUES] = text;
		}
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
