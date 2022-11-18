#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using insertIterator	 = typename std::insert_iterator<std::vector<std::string>>;
using ostreamIterator	 = typename std::ostream_iterator<int, char>;
using backInsertIterator = typename std::back_insert_iterator<std::vector<std::string>>;

void outputStr(const std::string& lStr) { std::cout << lStr << " "; }

void main()
{
	int castsOfDice[10]{ 6,7,2,9,4,11,8,7,10,5 };
	std::vector<int> dice(10);
	
	std::copy(castsOfDice, castsOfDice + 10, dice.begin());
	std::cout << "Let the dice be cast!\n";

	ostreamIterator outIter(std::cout, " ");

	std::copy(dice.begin(), dice.end(), outIter);
	std::cout << std::endl;

	std::cout << "Implicit use of reverse iterator.\n";
	std::copy(dice.rbegin(), dice.rend(), outIter);
	std::cout << std::endl;

	std::cout << "Explicit use of reverse iterator.\n";
	std::vector<int>::reverse_iterator reverseIter;

	for (reverseIter = dice.rbegin(); reverseIter != dice.rend(); reverseIter++)
	{
		std::cout << *reverseIter << " ";
	}
	std::cout << std::endl << std::endl;

	std::string strFirst[]{"bullet", "proof", "fashion","fate"};
	std::string strSecond[]{"busy", "bats"};
	std::string strThird[]{"silly", "songers"};

	std::vector<std::string> words(4);
	std::copy(strFirst, strFirst + 4, words.begin());

	std::for_each(words.begin(), words.end(), outputStr);
	std::cout << std::endl;

	std::copy(strSecond, strSecond + 2, backInsertIterator(words));

	std::for_each(words.begin(), words.end(), outputStr);
	std::cout << std::endl;

	std::copy(strThird, strThird + 2, insertIterator(words,words.begin()));

	std::for_each(words.begin(), words.end(), outputStr);
	std::cout << std::endl;
}