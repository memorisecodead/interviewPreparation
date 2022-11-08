#include "worker.h"

const int countOfWorkers = 5;

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	
	Worker* workers[countOfWorkers]{};
	int totalCount = 0;

	for (totalCount = 0; totalCount < countOfWorkers; totalCount++)
	{
		char choiceOfCategory = '\0';
		cout << "Enter the employee category:\n"
			<< "w: waiter's singer "
			<< "t: singing waiter q:quit\n";
		cin >> choiceOfCategory;
		while (std::strchr("wstq", choiceOfCategory) == nullptr)
		{
			cout << "Please enter a w, s, t, or q: ";
			cin >> choiceOfCategory;
		}
		if (choiceOfCategory == 'q')
			break;
		switch (choiceOfCategory)
		{
		case 'w': workers[totalCount] = new Waiter;
			break;
		case 's': workers[totalCount] = new Singer;
			break;
		case 't': workers[totalCount] = new SingingWaiter;
			break;
		}
		cin.get();
		workers[totalCount]->setWorkerData();
	}
	std::cout << "\nHere is your staff:\n";

	int countOfStaff = 0;
	for (countOfStaff = 0; countOfStaff < totalCount; countOfStaff++)
	{
		cout << endl;
		workers[countOfStaff]->showInfo();
	}
	for (countOfStaff = 0; countOfStaff < totalCount; countOfStaff++)
	{
		delete workers[countOfStaff];
	}

	cout << "Example of multiple inheritance.\n";
	return 0;
}