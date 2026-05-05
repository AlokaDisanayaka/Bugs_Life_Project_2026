//
// Created by Aloka on 03/05/2026.
//

#include "DiagonalBug.h"
#include "Bug.h"
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
    // If bug is dead → do nothing
    if (!alive)
    {
        return;
    }

    // 1:Ensure direction is valid (not blocked)

    bool blocked = true;

    while (blocked)
    {
        int x = position.first;
        int y = position.second;

        blocked = false;

        // Check if movement in current direction hits board edge
        if (direction == 1 && (x == 9 || y == 0)) // North-East
        {
            blocked = true;
        }
        else if (direction == 2 && (x == 9 || y == 9)) // South-East
        {
            blocked = true;
        }
        else if (direction == 3 && (x == 0 || y == 9)) // South-West
        {
            blocked = true;
        }
        else if (direction == 4 && (x == 0 || y == 0)) // North-West
        {
            blocked = true;
        }

        // If blocked -> pick a new random direction
        if (blocked)
        {
            direction = (rand() % 4) + 1;
        }
    }

    // 2:Determine number of moves

    int moveSteps = 1; // normal behaviour

    if (evolved)
    {
        moveSteps = 2; // evolved bug moves twice
    }

    // 3: Move step-by-step
    for (int i = 0; i < moveSteps; i++)
    {
        int x = position.first;
        int y = position.second;

        bool edgeBlocked = false;

        // Check again before each step
        if (direction == 1 && (x == 9 || y == 0))
        {
            edgeBlocked = true;
        }
        else if (direction == 2 && (x == 9 || y == 9))
        {
            edgeBlocked = true;
        }
        else if (direction == 3 && (x == 0 || y == 9))
        {
            edgeBlocked = true;
        }
        else if (direction == 4 && (x == 0 || y == 0))
        {
            edgeBlocked = true;
        }

        // If next step hits edge → stop moving further
        if (edgeBlocked)
        {
            break;
        }

        // Perform diagonal movement
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
    }

    // 4: Record new position

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