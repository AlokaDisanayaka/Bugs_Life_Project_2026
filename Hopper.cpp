//
// Created by Aloka on 03/05/2026.
//

#include "Hopper.h"
#include <cstdlib>

// Constructor
Hopper::Hopper(int id, int x, int y, int direction, int health, int hopLength)
    : Bug(id, x, y, direction, health)
{
    this->hopLength = hopLength;
}

// Return type
string Hopper::getType() const
{
    return "Hopper";
}

// getter
int Hopper::getHopLength() const
{
    return hopLength;
}

// Move function
void Hopper::move()
{
    // If dead → do nothing
    if (!alive)
    {
        return;
    }

    // If blocked → change direction until valid
    while (isWayBlocked())
    {
        direction = (rand() % 4) + 1;
    }

    // Move step-by-step
    for (int i = 0; i < hopLength; i++)
    {
        // Check if next step is blocked
        if (isWayBlocked())
        {
            break; // stop at edge
        }

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
    }

    int actualHop = hopLength;

    if (evolved)
    {
        actualHop += 1;
    }
    // Save final position
    addPositionToPath();
}