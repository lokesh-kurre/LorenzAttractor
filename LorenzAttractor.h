#pragma once
#include "vectormath.h"
#include <random>
#include <string>
#include <SFML/Graphics.hpp>

class LorenzAttractor
{
private:
    sf::Event event;
    sf::Clock clock;

    double input_timer = 0;
    double timestep;

    float g_screenWidth = 1920;
    float g_screenHeight = 1080;

    bool isFullScreen = true;
    bool endSubProgram = false;

    sf::View view;

    //camera values
    sf::Vector3f cam_position = { 0, 0, -50 };
    std::vector<float> cam_angle = { 0, 0, 0 };
    sf::Vector3f display_position = { 0, 0, 100 };

    std::vector<sf::Vector3f> point;
    sf::Vector2f projected_point;

    //attractor parameter
    unsigned u = 0;
    std::vector<std::vector<float>> params;

    //rotation matrices
    Matrix3d<float> rotMatrixX;
    Matrix3d<float> rotMatrixY;
    Matrix3d<float> rotMatrixZ;

    //visual assets
    std::vector<std::vector<sf::Vector3f>> trail;
    std::vector<unsigned> j;
    sf::VertexArray line;
    std::vector<sf::CircleShape> circle;
    std::vector<sf::Color> colours;
    std::vector<std::vector<float>> trail_colours_params;


    //visual parameter
    unsigned num_points = 2;
    unsigned trail_length = 50;
    float speed = 0.1f;

    //constants
    float pi = 3.141f;

    //names per attractor
    sf::Text text;
    sf::Font font;
    std::vector<std::string> names = {
       "Lorenz Attractor",
        "3-Cells CNN Attractor",
        "Aizawa Attractor",
        "Bouali Attractor",
        "Chen-Lee Attractor",
        "Halvorsen Attractor",
        "Finance Attractor",
        "Newton-Leipnik Attractor",
        "Nose-Hoover Attractor",
        "Thomas Attractor"
    };

public:
    LorenzAttractor();

    sf::Uint8 clamp(float x) {
        if (x <= 0)
            return 0;
        else if (x >= 255)
            return 255;
        else return static_cast<sf::Uint8>(x);
    }

    float getRandomNumber(float MIN, float MAX) {
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_real_distribution<float> distribution(MIN, MAX);
        return distribution(generator);
    }

    int getRandomNumber(int MIN, int MAX) {
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_int_distribution<int> distribution(MIN, MAX);
        return distribution(generator);
    }

    void input(sf::RenderWindow& window);

    void update();
    void attractor(int newattractor) {
        assert(newattractor > 0 && newattractor < 10);
        u = newattractor;
    }
    void draw(sf::RenderWindow& window);

    void run(sf::RenderWindow& window);

    ~LorenzAttractor();

};