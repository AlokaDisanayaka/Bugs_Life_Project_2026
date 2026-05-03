//
// Created by Aloka on 03/05/2026.
//

#include "DiagonalBug.h"
#include <cstdlib>

// Constructor
DiagonalBug::DiagonalBug(int id, int x, int y, int direction, int health)
    : Bug(id, x, y, direction, health)
{
}

// Return bug type
string DiagonalBug::getType() const
{
    return "DiagonalBug";
}

// Move diagonally=?
// 1 = North-East
// 2 = South-East
// 3 = South-West
// 4 = North-West
void DiagonalBug::move()
{
    if (!alive)
    {
        return;
    }

    bool blocked = true;

    while (blocked)
    {
        int x = position.first;
        int y = position.second;

        blocked = false;

        if (direction == 1 && (x == 9 || y == 0))
        {
            blocked = true;
        }
        else if (direction == 2 && (x == 9 || y == 9))
        {
            blocked = true;
        }
        else if (direction == 3 && (x == 0 || y == 9))
        {
            blocked = true;
        }
        else if (direction == 4 && (x == 0 || y == 0))
        {
            blocked = true;
        }

        if (blocked)
        {
            direction = (rand() % 4) + 1;
        }
    }

    if (direction == 1)       // North-East
    {
        position.first++;
        position.second--;
    }
    else if (direction == 2)  // South-East
    {
        position.first++;
        position.second++;
    }
    else if (direction == 3)  // South-West
    {
        position.first--;
        position.second++;
    }
    else if (direction == 4)  // North-West
    {
        position.first--;
        position.second--;
    }

    addPositionToPath();
}

string DiagonalBug::getDirectionAsString() const
{
    if (direction == 1)
    {
        return "North-East";
    }
    else if (direction == 2)
    {
        return "South-East";
    }
    else if (direction == 3)
    {
        return "South-West";
    }
    else if (direction == 4)
    {
        return "North-West";
    }
    else
    {
        return "Unknown";
    }
}