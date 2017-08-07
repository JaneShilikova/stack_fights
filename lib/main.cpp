#include <iostream>

using namespace std;

#include "IUnit.hpp"
#include "InfantryUnit.hpp"
#include "ArmoredUnit.hpp"
#include "Army.hpp"
#include "Engine.hpp"

int main()
{
    cout << "Menu:\n"
         << "1 - create armies\n"
         << "2 - show armies\n"
         << "3 - next turn\n"
         << "4 - undo\n"
         << "5 - redo\n"
         << "6 - turns to win\n"
		 << "7 - choose strategy\n"
		 << "8 - quit\n"
		 << endl;
	auto& engine = Engine::getInst();
	int x = 1;
	while (x != 8)
	{
        cout << "Choose a number:" << endl;
		cin >> x;
		switch (x)
		{
		case 1:
		{
            engine.createArmies(300);
			break; 
		}
		case 2:
            engine.showArmies();
			break;
		case 3:
			engine.nextTurn();
			break;
		case 4:
			engine.undo();
			break;
		case 5:
			engine.redo();
			break;
		case 6:
            while (!engine.finished())
                engine.nextTurn();
			break;
		case 7:
			int variant;
			cout << "Choose a strategy:" << endl;
			cout << "1 - Line" << endl;
			cout << "2 - Column" << endl;
			cout << "3 - Rank" << endl;
			cin >> variant;
			if (variant != 1 &&
				variant != 2 &&
				variant != 3)
			{
				cout << "Incorrect number\n" << endl;
				break;
			}
			engine.chooseStrategy(variant);
			break;
		case 8:
			break;
		default:
            cout << "Incorrect number\n" << endl;
			break;
		}
	}
	return 0;
}
