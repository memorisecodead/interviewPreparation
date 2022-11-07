#include "worker.h"

void Worker::data() const
{
	std::cout << "Name: " << mFullName << std::endl;
	std::cout << "Employee ID: " << mID << std::endl;
}

void Worker::getWorkerData()
{
	getline(std::cin, mFullName);
	std::cout << "Enter worker's ID: ";
	std::cin >> mID;
	while (std::cin.get() != '\n')
		continue;
}

void Waiter::data() const
{
	std::cout << "Panache rating: " << mPanache 
		<< std::endl;
}

void Waiter::getWorkerData()
{
	std::cout << "Enter waiter's panache rating: \n";
	std::cin >> mPanache;
	while (std::cin.get()!='\n')
		continue;
}

void Waiter::setWorkerData()
{
	std::cout << "Enter waiter's name: " << std::endl;
	Worker::getWorkerData();
	getWorkerData();
}

void Waiter::showInfo() const
{
	std::cout << "Catergory: waiter\n";
	Worker::data();
	data();
}

void Singer::data() const
{
	std::cout << "Vocal range: " << mVoiceType[mVoice]
		<< std::endl;
}

void Singer::getWorkerData()
{
	std::cout << "Enter number for singer's vocal range:\n";

	int countOfVocal = 0;
	for (size_t i = 0; i < Vtypes; ++i)
	{
		std::cout << i << ": " << mVoiceType << " ";
		if (i % 4 == 3)
		{
			std::cout << std::endl;
		}
	}
	if (countOfVocal % 4 != 0)
	{
		std::cout << '\n';
	}
	std::cin >> mVoice;
	while (std::cin.get() != '\n')
		continue;
}

void Singer::setWorkerData()
{
	std::cout << "Enter singer's name:\n";
	Worker::getWorkerData();
	getWorkerData();
}

void Singer::showInfo() const
{
	std::cout << "Category: singer\n";
	Worker::data();
	data();
}

void SingingWaiter::data() const
{
	Singer::data();
	Waiter::data();
}

void SingingWaiter::getWorkerData()
{
	Waiter::getWorkerData();
	Singer::getWorkerData();
}

void SingingWaiter::setWorkerData()
{
	std::cout << "Enter singing waiter's name:\n";
	Worker::getWorkerData();
	getWorkerData();
}

void SingingWaiter::showInfo() const
{
	std::cout << "Category: singing waiter\n";
	Worker::data();
	data();
}
