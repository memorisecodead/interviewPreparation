#include <iostream>
#include <string>
#include <chrono>
#include <set>

template<typename TType> // xvalue-ref 
TType f(TType&& type)
{
	return std::move(type);
}

/*
* In short, rvalue-refss, when they are passed to other functions, must be unconditionally
* to rvalue (with std::move), because they are always associated with rvalue,
* and universal references should be conditionally reduced to rvalue when they are
* passed (with std::forward), since they are only sometimes linked to rvalue.
*	(see function logAndAdd in Annotation class)
*/
class Annotation
{
public:
	/* 
	*	The only thing, that distinguishes this code from the ideal realization 
	*	of your intentions is that text is not moved to value, but copied.
	*	Of course, text is brought to rvalue by std::move, but text is declared
	*	as const std::string, so that before the conversion text was a lvalue 
	*	of type const std::string, so that the result of the conversion is rvalue of type
	*	const std::string, and throughout all these actions the constancy is preserved.
	*/
	explicit Annotation(const std::string text)
		: value(std::move(text))
	{
	}

	template<typename TType>
	void proccess(const TType&& param) {}

	template<typename TType>
	void proccess(TType&& param) {}

	/// std::forward is a conditional conversion:
	/// this function performs to rvalue only when its argument 
	/// is initialized by rvalue.
	template<typename TType>
	void logAndAdd(TType&& param)
	{
		proccess(std::forward<TType>(param)); 
	}

private:
	std::string value;
};
