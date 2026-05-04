//
// Created by Aloka on 03/05/2026.
//

#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "DiagonalBug.h"
#include <fstream>
#include <sstream>
#include <cstdlib> // for rand()
#include <thread>
#include <chrono>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iostream>


Board::Board()
{
}

//LOAD FILE
void Board::loadFromFile(string filename)
{
    ifstream file(filename);

    if (!file)
    {
        file.open("../" + filename);
    }

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string type;
        string temp;

        getline(ss, type, ';');

        // Read common fields
        getline(ss, temp, ';');
        int id = stoi(temp);

        getline(ss, temp, ';');
        int x = stoi(temp);

        getline(ss, temp, ';');
        int y = stoi(temp);

        getline(ss, temp, ';');
        int direction = stoi(temp);

        getline(ss, temp, ';');
        int health = stoi(temp);

        //CREATE OBJECT BASED ON TYPE
        if (type == "C")
        {
            Bug* bug = new Crawler(id, x, y, direction, health);
            bugs.push_back(bug);
        }
        else if (type == "H")
        {
            getline(ss, temp, ';');
            int hopLength = stoi(temp);

            Bug* bug = new Hopper(id, x, y, direction, health, hopLength);
            bugs.push_back(bug);
        }
        else if (type == "D")
        {
            Bug* bug = new DiagonalBug(id, x, y, direction, health);
            bugs.push_back(bug);
        }
    }

    file.close();

    cout << "Bugs loaded successfully!" << endl;
}

//DISPLAY FUNCTION
void Board::displayAllBugs() const
{
    if (bugs.empty())
    {
        cout << "No bugs loaded. Choose option 1 first." << endl;
        return;
    }

    for (int i = 0; i < bugs.size(); i++)
    {
        Bug* b = bugs[i];

        pair<int,int> pos = b->getPosition();

        cout << b->getId() << " "
             << b->getType() << " ("
             << pos.first << "," << pos.second << ") "
             << b->getHealth() << " "
             << b->getDirectionAsString() << " ";

        // Hopper shows hop length
        if (b->getType() == "Hopper")
        {
            cout << b->getHopLength() << " ";
        }

        cout << b->getStatusAsString() << endl;
    }
}

Board::~Board()
{
    for (int i = 0; i < bugs.size(); i++)
    {
        delete bugs[i]; // free memory
    }
}
void Board::findBugById(int id) const
{
    for (int i = 0; i < bugs.size(); i++)
    {
        if (bugs[i]->getId() == id)
        {
            Bug* b = bugs[i];
            pair<int,int> pos = b->getPosition();

            cout << b->getId() << " "
                 << b->getType() << " ("
                 << pos.first << "," << pos.second << ") "
                 << b->getHealth() << " "
                 << b->getDirectionAsString() << " ";

            if (b->getType() == "Hopper")
            {
                cout << b->getHopLength() << " ";
            }

            cout << b->getStatusAsString() << endl;

            return;
        }
    }

    cout << "Bug " << id << " not found." << endl;
}

void Board::tapBoard()
{
    if (bugs.size() == 0)
    {
        cout << "No bugs on board!" << endl;
        return;
    }

    int frozenIndex = rand() % bugs.size();

    cout << "Frozen Bug ID: " << bugs[frozenIndex]->getId() << endl;

    for (int i = 0; i < bugs.size(); i++)
    {
        if (i == frozenIndex)
        {
            continue;
        }

        bugs[i]->move();
    }

    // after movement go FIGHT
    fightBugs();

    cout << "Tap complete!" << endl;
}

void Board::displayLifeHistory() const
{
    for (int i = 0; i < bugs.size(); i++)
    {
        Bug* b = bugs[i];

        cout << b->getId() << " "
             << b->getType() << " Path: ";

        b->displayPath();

        if (b->isAlive())
        {
            cout << " Alive!";
        }
        else
        {
            cout << " Dead";
        }

        cout << endl;
    }
}

void Board::displayAllCells() const
{
    // Loop through all grid cells
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            cout << "(" << x << "," << y << "): ";

            bool found = false;

            // Check all bugs
            for (int i = 0; i < bugs.size(); i++)
            {
                Bug* b = bugs[i];

                // Only show alive bugs
                if (!b->isAlive())
                {
                    continue;
                }

                pair<int,int> pos = b->getPosition();

                if (pos.first == x && pos.second == y)
                {
                    cout << b->getType() << " " << b->getId() << ", ";
                    found = true;
                }
            }

            if (!found)
            {
                cout << "empty";
            }

            cout << endl;
        }
    }
}

void Board::fightPair(Bug* b1, Bug* b2)
{
    cout << "Fight: " << b1->getId() << " vs " << b2->getId() << endl;

    // 3 rounds max
    for (int round = 1; round <= 3; round++)
    {
        if (!b1->isAlive() || !b2->isAlive())
        {
            break;
        }

        int damage1 = rand() % 6; // 0–5
        int damage2 = rand() % 6;

        b1->setHealth(b1->getHealth() - damage2);
        b2->setHealth(b2->getHealth() - damage1);

        cout << "Round " << round << ": "
             << b1->getId() << " HP=" << b1->getHealth() << ", "
             << b2->getId() << " HP=" << b2->getHealth() << endl;
    }

    // Determine result
    if (!b1->isAlive() && !b2->isAlive())
    {
        cout << "Both bugs died!" << endl;
    }
    else if (!b1->isAlive())
    {
        cout << b2->getId() << " wins!" << endl;
    }
    else if (!b2->isAlive())
    {
        cout << b1->getId() << " wins!" << endl;
    }
    else
    {
        cout << "Both survived!" << endl;
    }
}
void Board::fightBugs()
{
    // Check each cell
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            vector<Bug*> cellBugs;

            // Collect bugs in this cell
            for (int i = 0; i < bugs.size(); i++)
            {
                Bug* b = bugs[i];

                if (!b->isAlive())
                {
                    continue;
                }

                pair<int,int> pos = b->getPosition();

                if (pos.first == x && pos.second == y)
                {
                    cellBugs.push_back(b);
                }
            }

            // If more than 1 ->fight
            while (cellBugs.size() > 1)
            {
                Bug* b1 = cellBugs[0];
                Bug* b2 = cellBugs[1];

                fightPair(b1, b2);

                // Remove dead bugs from list
                if (!b1->isAlive())
                {
                    cellBugs.erase(cellBugs.begin());
                }

                if (!b2->isAlive())
                {
                    cellBugs.erase(cellBugs.begin());
                }
            }
        }
    }
}
int Board::countAliveBugs() const
{
    int count = 0;

    for (int i = 0; i < bugs.size(); i++)
    {
        if (bugs[i]->isAlive())
        {
            count++;
        }
    }

    return count;
}
//Generate date time filename
string getDateTimeFilename()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;

    ss << "bugs_life_history_"
       << (1900 + ltm->tm_year)
       << "_"
       << (1 + ltm->tm_mon)
       << "_"
       << ltm->tm_mday
       << "_"
       << ltm->tm_hour
       << "_"
       << ltm->tm_min
       << "_"
       << ltm->tm_sec
       << ".out";

    return ss.str();
}
void Board::runSimulation()
{
    if (bugs.size() == 0)
    {
        cout << "No bugs loaded!" << endl;
        return;
    }

    // Create dynamic filename
    string filename = getDateTimeFilename();

    cout << "Saving results to: " << filename << endl;

    //RESET FILE (overwrite)
    ofstream clearFile(filename);
    if (clearFile)
    {
        clearFile << "Simulation Start\n";
        clearFile.close();
    }
    else
    {
        cout << "Error creating file!" << endl;
        return;
    }

    int step = 1;

    while (countAliveBugs() > 1)
    {
        cout << "\n--- Step " << step << " ---" << endl;

        // Write step header
        ofstream out(filename, ios::app);
        if (out)
        {
            out << "\n--- Step " << step << " ---\n";
            out.close();
        }

        tapBoard();

        displayAllBugs();

        // Write bug state
        writeStateToFile(filename);

        step++;

        //wait for one second
        this_thread::sleep_for(chrono::seconds(1));
        //https://www.geeksforgeeks.org/cpp/how-to-add-timed-delay-in-cpp/
    }

    cout << "\nSimulation complete!" << endl;

    //write winner
    ofstream out(filename, ios::app);
    if (out)
    {
        out << "\nSimulation complete!\n";

        for (int i = 0; i < bugs.size(); i++)
        {
            if (bugs[i]->isAlive())
            {
                cout << "🏆Winner: Bug "
                     << bugs[i]->getId() << endl;

                out << "🏆Winner: Bug "
                    << bugs[i]->getId()
                    << " (" << bugs[i]->getType() << ")\n";
            }
        }

        out.close();
    }
}

void Board::writeStateToFile(string filename) const
{
    ofstream out(filename, ios::app);

    if (out)
    {
        for (int i = 0; i < bugs.size(); i++)
        {
            Bug* b = bugs[i];
            pair<int,int> pos = b->getPosition();

            out << b->getId() << " "
                << b->getType() << " ("
                << pos.first << "," << pos.second << ") "
                << b->getHealth() << " "
                << b->getDirectionAsString() << " ";

            if (b->getType() == "Hopper")
            {
                out << b->getHopLength() << " ";
            }

            out << b->getStatusAsString() << endl;
        }

        out.close();
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}
void Bug::writePathToFile(ofstream& out) const
{
    list<pair<int,int> >::const_iterator it;

    for (it = path.begin(); it != path.end(); it++)
    {
        out << "(" << it->first << "," << it->second << ")";

        list<pair<int,int> >::const_iterator nextIt = it;
        nextIt++;

        if (nextIt != path.end())
        {
            out << ",";
        }
    }
}

void Board::writeLifeHistoryToFile()
{
    // ceate filename
    string filename = getDateTimeFilename();

    cout << "Saving life history to: " << filename << endl;

    ofstream out(filename); // overwrite file

    if (out)
    {
        out << "-------🐞BUG LIFE HISTORY🐞-------------\n\n";

        for (int i = 0; i < bugs.size(); i++)
        {
            Bug* b = bugs[i];

            out << b->getId() << " "
                << b->getType() << " Path: ";

            // write path
            list<pair<int,int> >::iterator it;

            list<pair<int,int> > pathCopy;

            // a copy is needed because path is protected
            // reusing displayPath()

            list<pair<int,int> >::const_iterator p;

            out << b->getId() << " "
            << b->getType() << " Path: ";

            b->writePathToFile(out);

            if (b->isAlive())
            {
                out << " Alive";
            }
            else
            {
                out << " Dead";
            }

            out << endl;
        }

        out.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

void Board::displayBoard() const
{
    // Print column numbers
    cout << "   ";
    for (int x = 0; x < 10; x++)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "  ---------------------" << endl;

    // Loop rows
    for (int y = 0; y < 10; y++)
    {
        cout << y << " | ";

        for (int x = 0; x < 10; x++)
        {
            int count = 0;
            char symbol = '.';

            // Check all bugs
            for (int i = 0; i < bugs.size(); i++)
            {
                Bug* b = bugs[i];

                if (!b->isAlive())
                    continue;

                pair<int,int> pos = b->getPosition();

                if (pos.first == x && pos.second == y)
                {
                    count++;

                    // Assign symbol based on type
                    if (b->getType() == "Crawler")
                        symbol = 'C';
                    else if (b->getType() == "Hopper")
                        symbol = 'H';
                    else if (b->getType() == "DiagonalBug")
                        symbol = 'D';
                }
            }

            if (count > 1)
            {
                cout << "* ";
            }
            else
            {
                cout << symbol << " ";
            }
        }

        cout << endl;
    }

    cout << "  ---------------------" << endl;
}

void Board::runStepByStep()
{
    if (bugs.size() == 0)
    {
        cout << "No bugs loaded!" << endl;
        return;
    }

    cout << "\nStep-by-Step Simulation Started!" << endl;

    int step = 1;

    while (countAliveBugs() > 1)
    {
        cout << "\nPress ENTER to run next step...";
        cin.ignore();  // clear leftover input
        cin.get();     // wait for enter

        cout << "\n--- Step " << step << " ---" << endl;

        tapBoard();

        displayBoard(); // show visual board

        step++;
    }

    cout << "\nSimulation complete!" << endl;

    // Show winner
    for (int i = 0; i < bugs.size(); i++)
    {
        if (bugs[i]->isAlive())
        {
            cout << "🏆Winner: Bug "
                 << bugs[i]->getId()
                 << " (" << bugs[i]->getType() << ")" << endl;
        }
    }
}

void Board::displayLeaderboard() const
{
    int aliveCount = 0;
    int deadCount = 0;

    Bug* winner = NULL;
    Bug* strongest = NULL;

    for (int i = 0; i < bugs.size(); i++)
    {
        Bug* b = bugs[i];

        if (b->isAlive())
        {
            aliveCount++;
            winner = b;
        }
        else
        {
            deadCount++;
        }

        // Track strongest bug with highest health
        if (strongest == NULL || b->getHealth() > strongest->getHealth())
        {
            strongest = b;
        }
    }

    cout << "\n===== LEADERBOARD =====" << endl;

    if (winner != NULL)
    {
        cout << "Winner: Bug "
             << winner->getId()
             << " (" << winner->getType() << ")" << endl;
    }
    else
    {
        cout << "No winner yet." << endl;
    }

    cout << "Alive Bugs: " << aliveCount << endl;
    cout << "Dead Bugs: " << deadCount << endl;

    if (strongest != NULL)
    {
        cout << "Strongest Bug: "
             << strongest->getId()
             << " (Health: " << strongest->getHealth() << ")" << endl;
    }

    cout << "========================" << endl;
}