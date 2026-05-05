#include "sfml_view.h"

#ifdef HAVE_SFML

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct BugDrawInfo
{
    int x;
    int y;
    string type;
};

vector<BugDrawInfo> getBugsForDrawing(Board& board)
{
    vector<BugDrawInfo> bugsToDraw;

    stringstream capturedText;
    streambuf* oldCout = cout.rdbuf(capturedText.rdbuf());

    board.displayAllCells();

    cout.rdbuf(oldCout);

    string line;

    while (getline(capturedText, line))
    {
        if (line.find("empty") != string::npos)
        {
            continue;
        }

        int commaPosition = line.find(",");
        int closingBracketPosition = line.find(")");
        int colonPosition = line.find(":");

        if (commaPosition == string::npos ||
            closingBracketPosition == string::npos ||
            colonPosition == string::npos)
        {
            continue;
        }

        int x = stoi(line.substr(1, commaPosition - 1));
        int y = stoi(line.substr(commaPosition + 1,
                                 closingBracketPosition - commaPosition - 1));

        string bugText = line.substr(colonPosition + 2);

        if (bugText.find("Crawler") != string::npos)
        {
            bugsToDraw.push_back({x, y, "Crawler"});
        }
        else if (bugText.find("Hopper") != string::npos)
        {
            bugsToDraw.push_back({x, y, "Hopper"});
        }
        else if (bugText.find("DiagonalBug") != string::npos ||
                 bugText.find("SkitterBug") != string::npos)
        {
            bugsToDraw.push_back({x, y, "DiagonalBug"});
        }
    }

    return bugsToDraw;
}

sf::Color getBugColor(string bugType)
{
    if (bugType == "Crawler")
    {
        return sf::Color::Green;
    }
    else if (bugType == "Hopper")
    {
        return sf::Color::Yellow;
    }
    else if (bugType == "DiagonalBug")
    {
        return sf::Color::Cyan;
    }

    return sf::Color::Red;
}

string getBugLetter(string bugType)
{
    if (bugType == "Crawler")
    {
        return "C";
    }
    else if (bugType == "Hopper")
    {
        return "H";
    }
    else if (bugType == "DiagonalBug")
    {
        return "D";
    }

    return "?";
}

void launchSFML(Board& board)
{
    const int cellSize = 60;
    const int boardSize = 10;
    const int windowSize = cellSize * boardSize;

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize),
                            "Bug Board Visualizer");

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Space)
            {
                board.tapBoard();
            }
        }

        window.clear(sf::Color::White);

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

        vector<BugDrawInfo> bugsToDraw = getBugsForDrawing(board);

        for (int i = 0; i < bugsToDraw.size(); i++)
        {
            sf::CircleShape bugShape;
            bugShape.setRadius(18);
            bugShape.setFillColor(getBugColor(bugsToDraw[i].type));
            bugShape.setPosition((bugsToDraw[i].x * cellSize) + 12,
                                 (bugsToDraw[i].y * cellSize) + 12);

            window.draw(bugShape);

            sf::Text letter;
            letter.setFont(font);
            letter.setString(getBugLetter(bugsToDraw[i].type));
            letter.setCharacterSize(24);
            letter.setFillColor(sf::Color::Black);
            letter.setStyle(sf::Text::Bold);
            letter.setPosition((bugsToDraw[i].x * cellSize) + 22,
                               (bugsToDraw[i].y * cellSize) + 16);

            window.draw(letter);
        }

        window.display();
    }
}

#else

#include <iostream>

using namespace std;

void launchSFML(Board& board)
{
    cout << "SFML is not installed or CMake cannot find it yet." << endl;
    cout << "Install SFML, reload CMake, then try this option again." << endl;
}

#endif
