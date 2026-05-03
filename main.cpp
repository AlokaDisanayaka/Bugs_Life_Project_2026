#include <iostream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"
#include <vector>
using namespace std;

int main()
{
    int choice = 0;
    Board board;

    do
    {
        cout << "===========================================" << endl;
        cout << "\n============= BUG'S LIFE MENU ===========" << endl;
        cout << "1. Initialize Bug Board" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug" << endl;
        cout << "4. Tap the Bug Board" << endl;
        cout << "5. Display Life History of all Bugs" << endl;
        cout << "6. Display all Cells" << endl;
        cout << "7. Run Simulation" << endl;
        cout << "8. Exit" << endl;
        cout << "==========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            board.loadFromFile("Bugs.txt");
        }
        else if (choice == 2)
        {
            board.displayAllBugs();
        }
        else if (choice == 3)
        {
            cout << "Find a Bug selected." << endl;
        }
        else if (choice == 4)
        {
            cout << "Tap Bug Board selected." << endl;
        }
        else if (choice == 5)
        {
            cout << "Display Life History selected." << endl;
        }
        else if (choice == 6)
        {
            cout << "Display all Cells selected." << endl;
        }
        else if (choice == 7)
        {
            cout << "Run Simulation selected." << endl;
        }
        else if (choice == 8)
        {
            cout << "Exiting program..." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 8);



    return 0;
}
