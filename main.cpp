#include "stdafx.h"
#include "LorenzAttractor.h"
#include <SFML/Graphics.hpp>

int main() {
    /// Create a window

    bool isFullscreen = false;
    sf::RenderWindow window;
    window.create(sf::VideoMode(1980, 1080), "Coding Projects", (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default), sf::ContextSettings());
    window.setPosition(sf::Vector2i(0, 0));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // sf::View view;
    // window.setView(view);

    // while (window.isOpen())
    // {
    //     sf::CircleShape circle;
    //     circle.setPosition(5.0f, 10.f);
    //     window.draw(circle);
    // }
    // float g_screenWidth = 200;
    // float g_screenHeight = 200;
    // window.setView(sf::View(sf::Vector2f(static_cast<float>(g_screenWidth / 2), static_cast<float>(g_screenHeight / 2)), sf::Vector2f(static_cast<float>(g_screenWidth), static_cast<float>(g_screenHeight))));


    /// Important part is here

    LorenzAttractor LA;
    LA.attractor(5);
    LA.run(window);
}