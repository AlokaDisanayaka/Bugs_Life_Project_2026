//
// Created by Aloka on 05/05/2026.
//

#include "sfml_display.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

sf::Color getBugColor(string bugType)
{
    if (bugType == "Crawler")
    {
        return sf::Color::Blue;
    }
    else if (bugType == "Hopper")
    {
        return sf::Color::Green;
    }
    else if (bugType == "DiagonalBug")
    {
        return sf::Color::Magenta;
    }

    return sf::Color::Red;
}

void displaySFMLBoard(const Board& board)
{
    const int cellSize = 50;
    const int boardSize = 10;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Bug Board");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Draw the grid
        for (int y = 0; y < boardSize; y++)
        {
            for (int x = 0; x < boardSize; x++)
            {
                sf::RectangleShape cell;
                cell.setSize(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::White);
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }

        // Draw the living bugs
        const vector<Bug*>& bugs = board.getBugs();

        for (int i = 0; i < bugs.size(); i++)
        {
            Bug* bug = bugs[i];

            if (!bug->isAlive())
            {
                continue;
            }

            pair<int, int> position = bug->getPosition();

            sf::CircleShape bugShape;
            bugShape.setRadius(15);
            bugShape.setFillColor(getBugColor(bug->getType()));
            bugShape.setPosition((position.first * cellSize) + 10,
                                 (position.second * cellSize) + 10);

            window.draw(bugShape);
        }

        window.display();
    }
}
