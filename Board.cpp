//
// Created by Aloka on 03/05/2026.
//

#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <fstream>
#include <sstream>
#include <cstdlib> // for rand()

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

    //Choose one bug to freeze
    int frozenIndex = rand() % bugs.size();

    cout << "Frozen Bug ID: " << bugs[frozenIndex]->getId() << endl;

    for (int i = 0; i < bugs.size(); i++)
    {
        // Skip frozen bug
        if (i == frozenIndex)
        {
            continue;
        }

        // Move all other bugs
        bugs[i]->move();
    }

    cout << "All bugs moved!" << endl;
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
