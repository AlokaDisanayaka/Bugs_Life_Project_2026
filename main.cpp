#include <iostream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include <vector>
using namespace std;

int main()
{
    // int choice = 0;
    //
    // do
    // {
    //     cout << "===========================================" << endl;
    //     cout << "\n============= BUG'S LIFE MENU ===========" << endl;
    //     cout << "1. Initialize Bug Board" << endl;
    //     cout << "2. Display all Bugs" << endl;
    //     cout << "3. Find a Bug" << endl;
    //     cout << "4. Tap the Bug Board" << endl;
    //     cout << "5. Display Life History of all Bugs" << endl;
    //     cout << "6. Display all Cells" << endl;
    //     cout << "7. Run Simulation" << endl;
    //     cout << "8. Exit" << endl;
    //     cout << "==========================================" << endl;
    //     cout << "Enter choice: ";
    //     cin >> choice;
    //
    //     if (choice == 1)
    //     {
    //         cout << "Initialize Bug Board selected." << endl;
    //     }
    //     else if (choice == 2)
    //     {
    //         cout << "Display all Bugs selected." << endl;
    //     }
    //     else if (choice == 3)
    //     {
    //         cout << "Find a Bug selected." << endl;
    //     }
    //     else if (choice == 4)
    //     {
    //         cout << "Tap Bug Board selected." << endl;
    //     }
    //     else if (choice == 5)
    //     {
    //         cout << "Display Life History selected." << endl;
    //     }
    //     else if (choice == 6)
    //     {
    //         cout << "Display all Cells selected." << endl;
    //     }
    //     else if (choice == 7)
    //     {
    //         cout << "Run Simulation selected." << endl;
    //     }
    //     else if (choice == 8)
    //     {
    //         cout << "Exiting program..." << endl;
    //     }
    //     else
    //     {
    //         cout << "Invalid choice. Try again." << endl;
    //     }
    //
    // } while (choice != 8);


    //hopper tests
    vector<Bug*> bugs;

    Bug* b1 = new Crawler(101, 0, 0, 2, 10);
    Bug* b2 = new Hopper(102, 5, 5, 1, 10, 3);

    bugs.push_back(b1);
    bugs.push_back(b2);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < bugs.size(); j++)
        {
            bugs[j]->move();
        }
    }

    cout << "Crawler Path: ";
    bugs[0]->displayPath();

    cout << "\nHopper Path: ";
    bugs[1]->displayPath();

    // free memory
    for (int i = 0; i < bugs.size(); i++)
    {
        delete bugs[i];
    }



    return 0;
}