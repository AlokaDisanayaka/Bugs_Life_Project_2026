//
// Created by Aloka on 03/05/2026.
//

#ifndef BUGS_LIFE_PROJECT_2026_BUG_H
#define BUGS_LIFE_PROJECT_2026_BUG_H

#include <iostream>
#include <utility>
#include <list>
#include <string>
#include <fstream>

using namespace std;

class Bug
{
protected:
    int id;
    pair<int, int> position;
    int direction;
    int health;
    bool alive;
    list<pair<int, int> > path;
    bool evolved; // new feature When a bug wins a fight, it evolves:
                     //+3 health
                     //If Hopper → +1 hop length
                     //If Crawler → moves twice occasionally
public:
    Bug(int id, int x, int y, int direction, int health,bool evolved);

    virtual ~Bug();

    int getId() const;
    pair<int, int> getPosition() const;
    int getDirection() const;
    int getHealth() const;
    bool isAlive() const;

    void setDirection(int newDirection);
    void setHealth(int newHealth);
    void setAlive(bool status);

    //string getDirectionAsString() const;
    virtual string getDirectionAsString() const;
    string getStatusAsString() const;

    void addPositionToPath();
    void displayPath() const;
    void writePathToFile(ofstream& out) const;

    bool isWayBlocked() const;

    virtual void move() = 0;
    virtual string getType() const = 0;
    virtual int getHopLength() const;

    //helper functions for relplay mode
    int getPathSize() const;
    bool getPathAt(int index, pair<int,int>& pos) const;

    //evolve functions
    void evolve();
    bool isEvolved() const;
};


#endif //BUGS_LIFE_PROJECT_2026_BUG_H
