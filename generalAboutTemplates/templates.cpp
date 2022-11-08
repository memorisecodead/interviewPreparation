#include <iostream>
#include <vector>

/*
* @brief Templated entity.
* @details A templated entity(or, in some sources, "temploid") 
*	is any entity that is defined(or , for a lambda - expression, created) within a template definition.
*/
template<typename TTemploid>
struct Temploid
{
	void f(){}
};

template<typename TType, typename UType>
void f(TType xValue, UType yValue)
{
	std::cout << 1 << '\n';
}

template<typename TType>
void f(TType xValue, TType yValue)
{
	std::cout << 2 << '\n';
}

void f(int xValue, int yValue)
{
	std::cout << 3 << '\n';
}

template<typename TType>
void g(TType xValue)
{
	std::cout << 1 << '\n';
}

template<typename TType>
void g(const TType& xValue)
{
	std::cout << 2 << '\n';
}

template<typename TType, typename UType = int>
void h(TType xValue)
{
	UType yValue = 666;
	std::cout << yValue << '\n';
}

/*
* It is not allowed, because when you call the copy constructor,
*	the first constructor will be called, because you can substitute 
*	anything in it and get any correspondence,
*	while the second one gets only constant correspondences.
* P.S. (There is a way to fix this through std::enable_if)
*/
template<typename TType>
struct STemplate
{
	STemplate() = default;

	template<typename UType>
	STemplate(UType& xValue)
	{
		std::cout << 1 << '\n';
	}

	STemplate(const STemplate<TType>&)
	{
		std::cout << 2 << '\n';
	}
};

template<typename TType>
void ff(const std::vector<TType>&)
{
	std::cout << 1 << '\n';
}

namespace tempSpecialization
{
	template<typename TType>
	struct SSpec
	{
		TType xValue = 0;
	};

	template<>
	struct SSpec<int>
	{
		int yValue = 1;
	};

	template<typename TType>
	struct Hash;

	template<>
	struct Hash<int>
	{
		size_t operator()(int xValue)
		{
			return xValue * 10;
		}
	};

	struct MyType {};

	template<>
	struct Hash<MyType>
	{
	};

	template<typename TType>
	void fS(TType xValue)
	{
		std::cout << 1 << '\n';
	}

	template<>
	void fS(int xValue)
	{
		std::cout << 2 << '\n';
	}

	void fS(int xValue)
	{
		std::cout << 3 << '\n';
	}

	template<typename TType,typename UType>
	void fSS(TType xValue, UType yValue)
	{
		std::cout << 1 << '\n';
	}

	template<>
	void fSS(int xValue, int yValue)
	{
		std::cout << 2 << '\n';
	}

	/// The specialization is shaved after the main version is selected. 
	/// The compiler looks to see which one fits better: 1 or 3. 
	/// If you swap 3 and 2, the specialization gets selected. This is very funny :)
	template<typename TType>
	void fSS(TType xValue, TType yValue)
	{
		std::cout << 3 << '\n';
	}
	
	template<typename TType, typename UType>
	struct MyStruct
	{
		void f()
		{
			std::cout << 1 << '\n';
		}
	};

	/// Example of partial specialization.
	template<typename TType>
	struct MyStruct<TType, TType>
	{
		void f()
		{
			std::cout << 2 << '\n';
		}
	};

	/// Another one example of partial specialization for refference types.
	template<typename TType, typename UType>
	struct MyStruct<TType&,UType&>
	{
		void f()
		{
			std::cout << 3 << '\n';
		}
	};

	/// Template as parameters
	template <template <typename TType> class MyType>
	class MyFeather {};
}

void main()
{	
	STemplate<int> s;
	STemplate<int> ss = s;

	/// If you substitute the expression {1,2,3}, \
	/// the compiler will not understand which data type you are using
	std::vector<int> v{ 1,2,3 }; 
	ff(v);

	tempSpecialization::fS(0);
	tempSpecialization::fSS(0, 0);

	/// Example of partial specialization.
	tempSpecialization::MyStruct<int, double> partSpec;
	partSpec.f();

	tempSpecialization::MyStruct<int&, double&> partSpec_1;
	partSpec_1.f();

	tempSpecialization::MyStruct<int, int> partSpec_2;
	partSpec_2.f();
}