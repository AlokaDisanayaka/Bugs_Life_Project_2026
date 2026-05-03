//
// Created by Aloka on 03/05/2026.
//

#include "Bug.h"

Bug::Bug(int id, int x, int y, int direction, int health)
{
    this->id = id;
    this->position.first = x;
    this->position.second = y;
    this->direction = direction;
    this->health = health;
    this->alive = true;

    // Store the starting position in the bug's life history
    addPositionToPath();
}

Bug::~Bug()
{
    // Virtual destructor needed because we will delete derived objects
    // through Bug pointers later.
}

int Bug::getId() const
{
    return id;
}

pair<int, int> Bug::getPosition() const
{
    return position;
}

int Bug::getDirection() const
{
    return direction;
}

int Bug::getHealth() const
{
    return health;
}

bool Bug::isAlive() const
{
    return alive;
}

void Bug::setDirection(int newDirection)
{
    direction = newDirection;
}

void Bug::setHealth(int newHealth)
{
    health = newHealth;

    if (health <= 0)
    {
        health = 0;
        alive = false;
    }
}

void Bug::setAlive(bool status)
{
    alive = status;
}

string Bug::getDirectionAsString() const
{
    if (direction == 1)
    {
        return "North";
    }
    else if (direction == 2)
    {
        return "East";
    }
    else if (direction == 3)
    {
        return "South";
    }
    else if (direction == 4)
    {
        return "West";
    }
    else
    {
        return "Unknown";
    }
}

string Bug::getStatusAsString() const
{
    if (alive == true)
    {
        return "Alive";
    }
    else
    {
        return "Dead";
    }
}

void Bug::addPositionToPath()
{
    path.push_back(position);
}

void Bug::displayPath() const
{
    list<pair<int, int> >::const_iterator it;

    for (it = path.begin(); it != path.end(); it++)
    {
        cout << "(" << it->first << "," << it->second << ")";

        list<pair<int, int> >::const_iterator nextIt = it;
        nextIt++;

        if (nextIt != path.end())
        {
            cout << ", ";
        }
    }
}

bool Bug::isWayBlocked() const
{
    int x = position.first;
    int y = position.second;

    if (direction == 1 && y == 0)
    {
        return true;
    }
    else if (direction == 2 && x == 9)
    {
        return true;
    }
    else if (direction == 3 && y == 9)
    {
        return true;
    }
    else if (direction == 4 && x == 0)
    {
        return true;
    }

    return false;
}

int Bug::getHopLength() const
{
    // Crawlers do not have hop length.
    return 0;
}