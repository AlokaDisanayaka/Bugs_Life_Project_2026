//
// Created by Aloka on 03/05/2026.
//

#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <fstream>
#include <sstream>

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
