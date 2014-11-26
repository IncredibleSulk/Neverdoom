#include "includes.hpp"


struct ProgressCircle {

    private:
        double Radius;
        double Angle;
        double progressDegrees;
        int Seperation;

        sf::Vector2f Position;
        sf::VertexArray ProgressBar;

    public:
        ProgressCircle () {
            ProgressBar.setPrimitiveType(sf::PrimitiveType::TrianglesFan);
    //        ProgressBar.setPrimitiveType(sf::PrimitiveType::LinesStrip);
            Radius = 50;
            Angle = 0;
            Seperation = 0;
            progressDegrees = 0;
            }

        void draw (sf::RenderWindow &Window) {
            Window.draw(ProgressBar);
            }

        void setSize (float pRadius) { Radius = pRadius;}

        void setSeparation (int Sep) {Seperation = Sep;}

        void setPosition (sf::Vector2f Pos) { Position = Pos;}

        sf::Vector2f getPosition () { return Position;}

        float getPercent () {
            return (progressDegrees / 360) * 100;
            }

        void setPercent (float percentage) {
            progressDegrees = (percentage/100) * 360;
            }

        void handle () {
            ProgressBar.clear();
            Angle = 0;

            ProgressBar.append(sf::Vertex (sf::Vector2f(Position.x, Position.y), sf::Color::Green));
            while (Angle <= progressDegrees) {

                float pAngle = Angle - 180;
                pAngle *= (3.14 / 180.0);
                double x = Position.x + (Radius * sin(pAngle));
                double y = Position.y + (Radius * cos(pAngle));
                pAngle *= (180.0 / 3.14);

    //            if ((int)Angle % (int)(sqrt(Radius)) == 0) ProgressBar.append(sf::Vertex (sf::Vector2f(x, y), sf::Color::Black));

                if (Seperation > 0) {
                    if ((int)Angle % Seperation == 0) ProgressBar.append(sf::Vertex (sf::Vector2f(x, y), sf::Color::Black));
                    else ProgressBar.append(sf::Vertex (sf::Vector2f(x, y), sf::Color::Green));
                    Angle += 0.1;
                    } else ProgressBar.append(sf::Vertex (sf::Vector2f(x, y), sf::Color::Green));
                }
            }
    };
