#include <iostream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"
#include "sfml_view.h"
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
            cout << "\n=====================================\n";
            cout << "        BUG'S LIFE SIMULATOR\n";
            cout << "=====================================\n\n";

            cout << "[1] Initialize Bug Board\n";
            cout << "[2] Display All Bugs\n";
            cout << "[3] Find a Bug\n";
            cout << "[4] Tap the Board\n";
            cout << "[5] Display Life History\n";
            cout << "[6] Display All Cells\n";
            cout << "[7] Run Simulation\n";
            cout << "[8] Display Visual Board\n";
            cout << "[9] Step-by-Step Simulation\n";
            cout << "[10] Leaderboard\n";
            cout << "[11] Replay Simulation\n";
            cout << "[12] Launch SFML Visualizer\n";
            cout << "[13] Exit\n";

            cout << "\n-------------------------------------\n";
            cout << "Enter your choice: ";

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
            board.displayBoard();
        }
        else if (choice == 9)
        {
            cin.ignore();
            board.runStepByStep();
        }
        else if (choice == 10)
        {
            board.displayLeaderboard();
        }
        else if (choice == 11)
        {
            board.replaySimulation();
        }
        else if (choice == 12)
        {
            launchSFML(board);
        }
        else if (choice == 13)
        {
            board.writeLifeHistoryToFile();
            cout << "Exiting program... Goodbye...." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 13);


    return 0;
}
