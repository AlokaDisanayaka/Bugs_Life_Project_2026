//
// Created by Aloka on 03/05/2026.
//

#ifndef BUGS_LIFE_PROJECT_2026_CRAWLER_H
#define BUGS_LIFE_PROJECT_2026_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug
{
public:
    // Constructor
    Crawler(int id, int x, int y, int direction, int health);

    // Override move function
    void move();

    // Return type of bug
    string getType() const;
};

#endif //BUGS_LIFE_PROJECT_2026_CRAWLER_H