//
// Created by Aloka on 03/05/2026.
//

#ifndef BUGS_LIFE_PROJECT_2026_HOPPER_H
#define BUGS_LIFE_PROJECT_2026_HOPPER_H

#include "Bug.h"

class Hopper : public Bug
{
private:
    int hopLength;

public:
    // Constructor
    Hopper(int id, int x, int y, int direction, int health, int hopLength);

    // Override move
    void move();

    // Return type
    string getType() const;

    // Getter for hop length
    int getHopLength() const;
};


#endif //BUGS_LIFE_PROJECT_2026_HOPPER_H