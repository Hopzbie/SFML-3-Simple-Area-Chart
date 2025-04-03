// library
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>


// main program
int main()
{
    // data
    int data[]   = {2, 4, 3, 6, 7, 5};
    int data_n   = sizeof(data) / sizeof(data[0]);
    int data_max = *std::max_element(data, data + data_n);

    // create window
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title", sf::State::Windowed, settings);

    // dot
    sf::CircleShape dot;
    dot.setFillColor(sf::Color(0, 170, 255));

    // line
    sf::RectangleShape line;
    line.setFillColor(sf::Color(0, 170, 255));

    // area
    sf::ConvexShape area;
    area.setPointCount(4);
    area.setFillColor(sf::Color(0, 127, 191));


    // while window is still open
    while (window.isOpen())
    {
        // handle events
        while (std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }
            // when window is resized
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
            }
        }

        // window size
        float window_w   = window.getView().getSize().x;
        float window_h   = window.getView().getSize().y;
        float window_min = std::min(window_w, window_h);

        // parameters
        float space  = window_w / (data_n - 1);
        float scale  = 0.9f * window_h / data_max;
        float radius = 0.02f * window_min;
        float width  = radius * 2;

        // fill window with color
        window.clear(sf::Color(64, 64, 64));

        // draw
        dot .setRadius(radius);
        dot .setOrigin({radius, radius});
        line.setOrigin({0.f, width/2});
        float x_old;
        float y_old;
        for (int i = 0;  i < data_n;  i++)
        {
            // position
            float x = i * space;
            float y = window_h - (data[i] * scale);

            // skip first
            if (i > 0)
            {
                // area
                area.setPoint(0, {x_old, window_h});
                area.setPoint(1, {x_old, y_old});
                area.setPoint(2, {x, y});
                area.setPoint(3, {x, window_h});
                window.draw(area);
            }

            // store old values
            x_old = x;
            y_old = y;
        }
        for (int i = 0;  i < data_n;  i++)
        {
            // dot
            float x = i * space;
            float y = window_h - (data[i] * scale);
            dot.setPosition({x, y});
            window.draw(dot);

            // skip first
            if (i > 0)
            {
                // line
                float dx     = x_old - x;
                float dy     = y_old - y;
                float angle  = std::atan2(dy, dx);
                float length = std::sqrt(dx*dx + dy*dy);
                line.setSize({length, width});
                line.setRotation(sf::radians(angle));
                line.setPosition({x, y});
                window.draw(line);
            }

            // store old values
            x_old = x;
            y_old = y;
        }
        
        // display
        window.display();
    }

    
    // program end successfully
    return 0;
}