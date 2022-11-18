#include <iostream>
#include <string>
#include <chrono>
#include <set>

std::multiset<std::string> names;
std::string nameFromIDX(int IdX) {};

/*
*  @brief Alternative overloads for universal links:
*  @details
*	1.Overload rejection:
*		In our case, overloading the logAndAdd method can
*		be divided into two methods.
*	2. Transfer const T&:
*		It's disadvantage is that this design is not
*		as effective as we would like it to be,
*		as we would like it to be.
*	3. Transmission by value:
*		An approach that often achieves performance without increasing
*		complexity is to replace parameter passing by reference with passing by value,
*		no matter how unnatural it may sound.
*		This design should be used when it is known that the object
*		is passed by value, when it is known that they will be exactly copied.
*	4. Descriptor dispatch:
*		Conceptually, logAndAdd passes a boolean value to the logAndAddimpl function indicating
*		whether an integer type is passed to the logAndAdd function, but the values true and false are
*		runtime values, and we need overload permission to select the correct version of logAndAddimpl
*		need to allow overloading, i.e., the compile-time phenomenon. This means that
*		we need a type corresponding to the value true, and another type corresponding to the value
*		false. This need is such a common occurrence that the standard
*		library provides what we need under the names std::true_ture
*		and std::false_type.
*	5. Limitations of templates that receive universal references:
*		For situations like this, where an overloaded function accepting a universal
*		reference turns out to be more "greedy" than you wanted, but not greedy enough
*		to act as a single dispatch function, the method of dispatching
*		of descriptors isn't what's needed. You need a different technology, and that technology
*		- std::enable_if.
*		std::enable_if gives you the ability to make compilers behave
*		as if a certain pattern didn't exist. These patterns are called disconnected
*		(disable). By default, all templates are enabled, but the one using
*		std::enable_if, is enabled only if the condition defined by
*		std::enable_if.
*/

/*
* @details
*	In short, rvalue-refss, when they are passed to other functions, must be unconditionally
*	to rvalue (with std::move), because they are always associated with rvalue,
*	and universal references should be conditionally reduced to rvalue when they are
*	passed (with std::forward), since they are only sometimes linked to rvalue.
*		(see widget constructor and setter of Widget(setName))
*/
class Widget
{
public:
	Widget() = default;

	template<typename TType, bool B,
		typename = typename std::enable_if<B>::type>
	explicit Widget(TType&& rhs)
	{
	}

	Widget(Widget&& rhs) noexcept	// rhs has rvalue-ref
		:widgetStr(std::move(rhs.widgetStr)), widgetName(std::string())
	{
		++moveCtorCalls;
	}

	template<typename TType>
	void setName(TType&& newName)	// newName has xvalue-ref
	{
		widgetName = std::forward<TType>(newName);
	}

	/// Overloading for universal references almost always causes this
	/// overloading is called more often than you expect.
	template<typename TType>
	void logAndAdd(TType&& name)
	{
		std::cout << "Overloading for universal links of LogAndAdd" << std::endl;
		names.emplace(std::forward<TType>(name));
	}

	void logAndAdd(int IdX)
	{
		std::cout << "LogAndAdd overload" << std::endl;
		names.emplace(nameFromIDX(IdX));
	}

	template<typename TType>
	void logAndAdd(TType&& name, volatile int countOfLog)
	{
		logAndAddImpl(std::forward<TType>(name),
			std::is_integral<TType>());
		++countOfLog;
	}

	/// The argument passed to logAndAddimpl by the function logAndAdd,
	/// is a type object inherited from std::true_type if T is an integer
	/// type, and from std::false_type if T is not.The end result is
	///	is that this logAndAddimpl overload is a real candidate for calling
	///	to logAndAdd only if T is not an integer type.
	template<typename TType>
	void logAndAddImpl(TType&& name, std::false_type)
	{
		std::cout << "Descriptor dispatch LogAndAdd overload"
			<< std::endl;
		names.emplace(std::forward<TType>(name));
	}

	/*
	* @details
	*	RVO - Return Value Optimization
	*	But RVO is just an optimization.
	*	Compilers are not obliged to eliminate operations
	*	copy and move operations, even when they are allowed to do so.
	*/
	Widget makeWidget()
	{
		///	In this case, applying std::move to a local object is still a bad
		///	idea.The part of the standard permitting RVO application further states that if the conditions
		///	for applying RVO are met, but compilers choose not to perform
		///	copy removal, then the returned object must be treated as rvalue.
		///	By in essence, the standard requires that when RVO optimization is allowed, the returned local
		/// object either apply copy removal or implicitly apply the std::move function.
		Widget w;

		return w; // Copying does not work 
		//return std::move(w) - second version of RVO
	}
private:
	static std::size_t moveCtorCalls;
	std::string widgetStr;
	std::string widgetName;
};

void proccess(const Widget& lvalue) {};
void proccess(Widget&& rvalue) {};

/*
* @details
*	param, like all function parameters, is lvalue. Each call to process
*	within logAndProcess will thus call the process overload for lvalue. To
*	to prevent this behavior, we need a mechanism to cast param to rvalue
*	if and only if the argument with which param is initialized is the argument passed to
*	logAndProcess, was rvalue. This is exactly what std::forward does. Here's
*	why std::forward is a conditional conversion: this function performs
*	conversion to rvalue only when its argument is initialized with rvalue.
*/
template<typename TType>
void logAndProccess(TType&& param)
{
	auto now = std::chrono::system_clock::now();
	proccess(std::forward<TType>(param));
}

/*
* @brief Reference Collapsing
* @details 
*	We are forbidden to declare a reference to a reference, 
*	but compilers can create them in certain contexts, 
*	among which is template instantiation.
*	When compilers generate a reference to a reference, 
*	reference collapsing determines what happens next.
* @details
*  There are two kinds of references (lvalue and rvalue), 
*	so there are four possible
*	Ñombinations "link to link" (lvalue to lvalue, lvalue to rvalue, 
*	rvalue to lvalue and rvalue on rvalue). 
*	If a reference occurs in a context where it is allowed (for example,
*	during template instantiation), the references are collapsed into 
*	a single reference according to the following rule:
*	If any of the references are lvalue references, the result is a
*	lvalue link. Otherwise (when both references are lvalue references)
*	the result is a value-link.
*/
template<typename TType>
void someFunc(TType&& fParam)
{
	foo(std::forward<TType>(fParam));

	/*
	* @details 
	*	Link collapsing takes place in the most common
	*	- Instantiation of templates. 
	*	The second is generating types for variables auto. 
	*	The details are essentially the same as for templates, 
	*	because the type output for autovariables,
	*	is essentially the same as the output of types for templates.
	*/
	Widget widgetOfCollapsing; // lvalue
	auto&& widgetTemplate = widgetOfCollapsing; // lvalue

	Widget widgetFactory(); // rvalue
	auto&& secondWidgetTemplate = widgetFactory(); // rvalue

	/// A universal reference is not a new kind of reference, in fact
	/// it is an rvalue reference in a context in which two conditions are met:
	/// 1. The type output distinguishes lvalue from rvalue.
	///	A lvalue of type TType is rendered as having type TType&,
	/// where as an rvalue of type TType is rendered as having type TType .
	/// 2. The collapsing of references takes place.
	
	/// Universal references are rvalue references in contexts where
	// type output distinguishes lvalue from rvalueand collapses the references.
}

void foo(Widget&& param) {}	// rvalue-ref

int main()
{
	Widget&& varFirst = Widget();	// rvalue-ref
	auto&& varSecond = varFirst;	// xvalue-ref

	logAndProccess(varFirst);
}
