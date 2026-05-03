//
// Created by Aloka on 03/05/2026.
//

#ifndef BUGS_LIFE_PROJECT_2026_DIAGONALBUG_H
#define BUGS_LIFE_PROJECT_2026_DIAGONALBUG_H
#include "Bug.h"

class DiagonalBug : public Bug
{
public:
    DiagonalBug(int id, int x, int y, int direction, int health);

    void move();

    string getType() const;

    string getDirectionAsString() const;
};
#endif //BUGS_LIFE_PROJECT_2026_DIAGONALBUG_H