//
// Created by Aloka on 03/05/2026.
//

#ifndef BUGS_LIFE_PROJECT_2026_BOARD_H
#define BUGS_LIFE_PROJECT_2026_BOARD_H
#include <vector>
#include <string>
#include "Bug.h"

using namespace std;

class Board
{
private:
    vector<Bug*> bugs; // vector of pointers

public:
    Board();

    // Load bugs from file
    void loadFromFile(string filename);

    // Display all bugs
    void displayAllBugs() const;

    // Give read-only access to the bugs for the SFML display
    const vector<Bug*>& getBugs() const;

    // Destructor to free memory
    ~Board();

    //Find a bug by ID
    void findBugById(int id) const;

    //Tap the board
    void tapBoard();

    //Display lifehistory
    void displayLifeHistory() const;

    //Dispaly all the cells of the board
    void displayAllCells() const;

    //Fight
    void fightBugs();
    void fightPair(Bug* b1, Bug* b2);

    //count alive bugs
    int countAliveBugs() const;

    //run simulation
    void runSimulation();

    //function to write bug state
    void writeStateToFile(string filename) const;

    //write life history to a file
    void writeLifeHistoryToFile();

    //EXTRA FEATURES-----------------

    //display visual board = console grid
    void displayBoard() const;

    //Step-by-Step Simulation
    void runStepByStep();

    //display leaderboard
    void displayLeaderboard() const;

    //replay mode
    void replaySimulation();
};

#endif //BUGS_LIFE_PROJECT_2026_BOARD_H
