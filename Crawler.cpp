//
// Created by Aloka on 03/05/2026.
//

#include "Crawler.h"
#include <cstdlib> // for rand()

// Constructor
Crawler::Crawler(int id, int x, int y, int direction, int health)
    : Bug(id, x, y, direction, health)
{
}

// Return bug type
string Crawler::getType() const
{
    return "Crawler";
}

// Move function
void Crawler::move()
{
    // If dead -> do nothing
    if (!alive)
    {
        return;
    }

    // If blocked -> pick new direction until valid
    while (isWayBlocked())
    {
        direction = (rand() % 4) + 1; // random 1–4
    }

    // Move 1 step based on direction
    if (direction == 1) // North
    {
        position.second--;
    }
    else if (direction == 2) // East
    {
        position.first++;
    }
    else if (direction == 3) // South
    {
        position.second++;
    }
    else if (direction == 4) // West
    {
        position.first--;
    }

    if (evolved && rand() % 2 == 0)
    {
        // extra move
        if (!isWayBlocked())
        {
            if (direction == 1) position.second--;
            else if (direction == 2) position.first++;
            else if (direction == 3) position.second++;
            else if (direction == 4) position.first--;
        }
    }
    // Save new position in path history
    addPositionToPath();
}