/*
* An SFML application - Matthew Devine 18/10/21
* SFML Documentation https://www.sfml-dev.org/documentation/2.5.1/
* SFML Shapes Tutorials https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php
* SGML Graphics tutorial https://gamefromscratch.com/sfml-c-tutorial-basic-graphics/
*/
#include <iostream>                                                     // std namespace
#include <SFML/Graphics.hpp>                                            // sf namespace 
#include "graphPoints.h"

int main()
{
#pragma region Window Creation
    // give choice of colours that work with color scheme 
    int num;
    std::cout << "Hello, please select a colour for the graph!\n"; //output colour choices
    std::cout << "1: Dark Green\n";
    std::cout << "2: Brown\n";
    std::cout << "3: Blue\n";
    std::cout << "Enter number\n";
    std::cin >> num;   //input colour choice

    while (!(num == 1 || num == 2 || num == 3)) { //check user input
        std::cout << "\nEnter a number from 1-3";
        std::cout << "Enter number";
        std::cin >> num;

    }
    



    sf::RenderWindow window(sf::VideoMode(1200, 800), "Plot Points!", sf::Style::Default, sf::ContextSettings(24));   // render a Window
    window.setVerticalSyncEnabled(true);
    sf::Vector2u winSize = window.getSize();

    sf::Font font;

    if (!font.loadFromFile(".\\fonts\\omegle.ttf"))
        return EXIT_FAILURE;

    sf::Text graphTitle("Heart Rate Over Time", font, 22); // title and font

    graphTitle.setFillColor(sf::Color::Cyan); //colour for title
    graphTitle.setPosition(winSize.x / 2, 6);

    sf::Text yAxisLabel("Heart Rate", font, 18);
    yAxisLabel.setFillColor(sf::Color::Cyan);
    yAxisLabel.setPosition(5, 200);



    sf::Text xAxisLabel("Time in seconds)", font, 18); // x axis title and font size
    xAxisLabel.setFillColor(sf::Color::Cyan);
    xAxisLabel.setPosition(winSize.x / 2, winSize.y - 24);





#pragma endregion
    graphPoints graphPts;                                               // create an instance of my point plotting class
    graphPts.loadPoints("HeartRate.csv", window);
    while (window.isOpen())                                             // This is the Windows application loop - infinite loop until closed
    {
        window.clear(sf::Color(40, 50, 45));  // Clear graphics buffer


#pragma region Check for Exit
        sf::Event event;                                                // Windows is event driven - so check for events
        while (window.pollEvent(event))
        {
           
            if (event.type == sf::Event::Closed)                        // if event closed close window
                window.close();    

            }
        
#pragma endregion
        
        // Set up x and y axis lines - this could be modified to look better. Further lines can be drawn in the same way. 
        // Lines can also be draw more efficiently with vertices. https://en.sfml-dev.org/forums/index.php?topic=11121.0
        // A function for this code would be better.
        sf::RectangleShape horizLine; sf::RectangleShape vertLine; sf::RectangleShape horizAxisLine; sf::RectangleShape vertAxisLine;
        switch (num) {
        case 1: if (num == 1) {
            window.clear(sf::Color(40, 50, 45));
        }
        case 2: if (num == 2) {
        window.clear(sf::Color(100, 52, 300));
        }
        case 3: if (num == 3) {
        window.clear(sf::Color(55, 25, 255));
            }
        }

        horizAxisLine.setFillColor(sf::Color(0,0,0)); horizAxisLine.setSize(sf::Vector2f(900, 2)); horizAxisLine.setPosition(100, winSize.y - 60); horizAxisLine.setRotation(0);
        vertAxisLine.setFillColor(sf::Color(0, 0, 0)); vertAxisLine.setSize(sf::Vector2f(700, 2));  vertAxisLine.setPosition(100, winSize.y - 60); vertAxisLine.setRotation(-90); // anticlockwise

        for (int i = 0; i <= vertAxisLine.getLocalBounds().width; i += vertAxisLine.getLocalBounds().width / 10)
        {
            horizLine.setFillColor(sf::Color(0, 0, 0)); horizLine.setSize(sf::Vector2f(900, 1)); horizLine.setPosition(100, winSize.y - (60 +i)); horizLine.setRotation(0);
            window.draw(horizLine);

            sf::Text yAxisValue(std::to_string(i/7), font, 20);
            yAxisValue.setFillColor(sf::Color::Black);
            yAxisValue.setPosition(100, winSize.y - (60 + i));
            yAxisValue.setOrigin(yAxisValue.getLocalBounds().width+5, yAxisValue.getLocalBounds().height/2);
            window.draw(yAxisValue);
        }

        for (int i = 0; i <= horizAxisLine.getLocalBounds().width; i += horizAxisLine.getLocalBounds().width/6)
        {
            vertLine.setFillColor(sf::Color(0, 0, 0)); vertLine.setSize(sf::Vector2f(700, 1)); vertLine.setPosition(100+i, winSize.y - 60 ); vertLine.setRotation(-90);
            window.draw(vertLine);

            sf::Text xAxisValue(std::to_string(i/3), font, 20);
            xAxisValue.setFillColor(sf::Color::Black);
            xAxisValue.setPosition(100 + i, winSize.y - 60);
            xAxisValue.setOrigin(xAxisValue.getLocalBounds().width/2, xAxisValue.getLocalBounds().height - 14);
            window.draw(xAxisValue);
        }

        



        window.draw(horizAxisLine);                                         // Draw x and y axis lines 
        window.draw(vertAxisLine);

        window.draw(graphTitle);                                        // draw title
        window.draw(yAxisLabel);                                        // draw y axis
        window.draw(xAxisLabel);                                        // draw x axis

        graphPts.drawPoints(window);                                    // Call draw function in my class

        window.display();                                               // Display the graphics from the buffer to the display
    }

    return 0;
}