#include <SFML/Graphics.hpp>
#include "CHIP-8.hpp"
#include <iostream>
int main(int argc, char **argv)
{
    sf::Texture texture;
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    }
    int videoScale = std::stoi(argv[1]);
    int cycleDelay = std::stoi(argv[2]);
    char const *romFilename = argv[3];
    // create the window
    sf::RenderWindow window(sf::VideoMode(VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale), "CHIP-8 Emulator");
    texture.create(VIDEO_WIDTH,VIDEO_HEIGHT);
    sf::Sprite sprite(texture);    
    Chip8 chip8;
    chip8.LoadROM(romFilename);
    std::cout << "Done\n";
    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::X:
                    chip8.keypad[0] = 1;
                    break;
                case sf::Keyboard::Num1:
                    chip8.keypad[1] = 1;
                    break;
                case sf::Keyboard::Num2:
                    chip8.keypad[2] = 1;
                    break;
                case sf::Keyboard::Num3:
                    chip8.keypad[3] = 1;
                    break;
                case sf::Keyboard::Q:
                    chip8.keypad[4] = 1;
                    break;
                case sf::Keyboard::W:
                    chip8.keypad[5] = 1;
                    break;
                case sf::Keyboard::E:
                    chip8.keypad[6] = 1;
                    break;
                case sf::Keyboard::A:
                    chip8.keypad[7] = 1;
                    break;
                case sf::Keyboard::S:
                    chip8.keypad[8] = 1;
                    break;
                case sf::Keyboard::D:
                    chip8.keypad[9] = 1;
                    break;
                case sf::Keyboard::Z:
                    chip8.keypad[10] = 1;
                    break;
                case sf::Keyboard::C:
                    chip8.keypad[11] = 1;
                    break;
                case sf::Keyboard::Num4:
                    chip8.keypad[12] = 1;
                    break;
                case sf::Keyboard::R:
                    chip8.keypad[13] = 1;
                    break;
                case sf::Keyboard::F:
                    chip8.keypad[14] = 1;
                    break;
                case sf::Keyboard::V:
                    chip8.keypad[15] = 1;
                    break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::X:
                    chip8.keypad[0] = 0;
                    break;
                case sf::Keyboard::Num1:
                    chip8.keypad[1] = 0;
                    break;
                case sf::Keyboard::Num2:
                    chip8.keypad[2] = 0;
                    break;
                case sf::Keyboard::Num3:
                    chip8.keypad[3] = 0;
                    break;
                case sf::Keyboard::Q:
                    chip8.keypad[4] = 0;
                    break;
                case sf::Keyboard::W:
                    chip8.keypad[5] = 0;
                    break;
                case sf::Keyboard::E:
                    chip8.keypad[6] = 0;
                    break;
                case sf::Keyboard::A:
                    chip8.keypad[7] = 0;
                    break;
                case sf::Keyboard::S:
                    chip8.keypad[8] = 0;
                    break;
                case sf::Keyboard::D:
                    chip8.keypad[9] = 0;
                    break;
                case sf::Keyboard::Z:
                    chip8.keypad[10] = 0;
                    break;
                case sf::Keyboard::C:
                    chip8.keypad[11] = 0;
                    break;
                case sf::Keyboard::Num4:
                    chip8.keypad[12] = 0;
                    break;
                case sf::Keyboard::R:
                    chip8.keypad[13] = 0;
                    break;
                case sf::Keyboard::F:
                    chip8.keypad[14] = 0;
                    break;
                case sf::Keyboard::V:
                    chip8.keypad[15] = 0;
                    break;
                }
                break;
            default:
                break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;
            chip8.Cycle();
            texture.update(chip8.screen);
            sprite.setScale(sf::Vector2f(videoScale,videoScale));
            window.draw(sprite);
            sprite.setScale(sf::Vector2f(1.0f,1.0f));
            for (int i = 0 ; i < 16 ; i++) {
                if (chip8.keypad[i]) {
                    std::cout << "Key :" << i << "\n";
                }
            } 
        }
        window.display();
    }

    return 0;
}