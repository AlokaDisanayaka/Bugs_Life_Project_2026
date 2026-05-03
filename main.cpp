#include <iostream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int choice = 0;
    Board board;
    srand(time(0)); // random seed

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
            int id;
            cout << "Enter Bug ID: ";
            cin >> id;

            board.findBugById(id);
        }
        else if (choice == 4)
        {
            board.tapBoard();
        }
        else if (choice == 5)
        {
            board.displayLifeHistory();
        }
        else if (choice == 6)
        {
            board.displayAllCells();
        }
        else if (choice == 7)
        {
            board.runSimulation();
        }
        else if (choice == 8)
        {
            cout << "Exiting program... Goodbye...." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 8);



    return 0;
}
