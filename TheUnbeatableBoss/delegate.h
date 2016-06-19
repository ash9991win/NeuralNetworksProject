#include<vector>
#include<functional>
#include<cstddef>
#include<iostream>
/*!
\class delegate
\brief The generic delegate that can bind to any function
*/
using namespace std;
template<typename returnType,typename...Args>
class delegate
{
private:

	typename std::vector<std::function<returnType(Args...)>> mListOfFunctions;
	const int ArgSize = sizeof...(Args);
	template<int N, typename T, typename U> struct Params { static void Push(T t, U* u,delegate& del) {}; };
	template<typename T,typename U>
	struct Params<0,T,U> {
		static void Push(T t, U* u,delegate& del) {
		
		using namespace std::placeholders;
		auto fn = std::bind(t, u);
		del.mListOfFunctions.push_back(fn);
		return;
	}
	};
	template<typename T, typename U>
	struct Params<1, T, U> {
		static void Push(T t, U* u, delegate& del) {
			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};
	template<typename T, typename U>
	struct Params<2, T, U> {
		static void Push(T t, U* u, delegate& del) {

			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1,_2);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};
	template<typename T, typename U>
	struct Params<3, T, U> {
		static void Push(T t, U* u, delegate& del) {

			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1,_2,_3);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};
	template<typename T, typename U>
	struct Params<4, T, U> {
		static void Push(T t, U* u, delegate& del) {

			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1,_2,_3,_4);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};
	template<typename T, typename U>
	struct Params<5, T, U> {
		static void Push(T t, U* u, delegate& del) {

			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1,_2,_3,_4,_5);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};
	template<typename T, typename U>
	struct Params<6, T, U> {
		static void Push(T t, U* u, delegate& del) {

			using namespace std::placeholders;
			auto fn = std::bind(t, u,_1,_2,_3,_4,_5,_6);
			del.mListOfFunctions.push_back(fn);
			return;
		}
	};

public:
	/*!
	\fn Bind(T t,U* u)
	\brief Binds a given function pointer with a given object 
	\param The function pointer to bind
	\param The object to bind to ( mostly this pointer)
	*/
	template<typename T,typename U>
	void Bind(T t, U* u)
	{
		Params<sizeof...(Args), T, U>::Push(t, u,*this);
	}
	/*!
	\fn Bind((std::function<returnType(Args...)>)
	\brief Binds a given lambda
	\param The lambda function  to bind
	*/
	void Bind(std::function<returnType(Args...)> lamba)
	{
		mListOfFunctions.push_back(lamba);
	}
	/*!
	\fn Invoke(TArgs&&...arg)
	\brief Invokes the delegate
	\param The arguments to be passed onto the bound functions
	*/
	template<typename...TArgs>
	void Invoke(TArgs&&...arg)
	{
		for (auto f : mListOfFunctions)
		{
			f(std::forward<TArgs>(arg)...);
		}
	}
};


