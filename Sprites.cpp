////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SDL.h>
#include <iostream>
#include <ctime>

const int NbSprites = 2000;


////////////////////////////////////////////////////////////
// SDL displaying 1000 sprites
////////////////////////////////////////////////////////////
int SpritesSDL()
{
    // Initialize the random numbers generator
    srand(static_cast<unsigned int>(time(NULL)));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    // Create the main window
    SDL_Surface* App = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (App == NULL)
        return 1;

    // Load five images
    SDL_Surface* Images[5];
    Images[0] = SDL_DisplayFormat(SDL_LoadBMP("image1.bmp"));
    Images[1] = SDL_DisplayFormat(SDL_LoadBMP("image2.bmp"));
    Images[2] = SDL_DisplayFormat(SDL_LoadBMP("image3.bmp"));
    Images[3] = SDL_DisplayFormat(SDL_LoadBMP("image4.bmp"));
    Images[4] = SDL_DisplayFormat(SDL_LoadBMP("image5.bmp"));
    if (!Images[0] || !Images[1] || !Images[2] || !Images[3] || !Images[4])
    {
        return 1;
    }

    // Create a lot of sprites
    struct Sprite
    {
        SDL_Rect Rect;
        SDL_Surface* Image;
    };
    Sprite Sprites[NbSprites];
    for (int i = 0; i < NbSprites; ++i)
    {
        Sprites[i].Image  = Images[rand() % 5];
        Sprites[i].Rect.x = rand() % 700;
        Sprites[i].Rect.y = rand() % 500;
        Sprites[i].Rect.w = Sprites[i].Image->w;
        Sprites[i].Rect.h = Sprites[i].Image->h;
    }

    // Start the timer
    Uint32 Time = SDL_GetTicks();
    int NbFrames = 0;

    // Start game loop
    while (SDL_GetTicks() < Time + 5000)
    {
        // Clear the screen
        SDL_FillRect(App, NULL, SDL_MapRGB(App->format, 0, 0, 0));

        // Draw the sprites
        for (int i = 0; i < NbSprites; ++i)
            SDL_BlitSurface(Sprites[i].Image, NULL, App, &Sprites[i].Rect);

        // Finally, display rendered frame on screen
        SDL_Flip(App);
        NbFrames++;
    }

    // Exit SDL
    SDL_Quit();

    return NbFrames;
}


////////////////////////////////////////////////////////////
// SFML displaying 1000 sprites
////////////////////////////////////////////////////////////
int SpritesSFML()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML_App");

    // Load five images
    sf::Texture Textures[5];
    if (!Textures[0].loadFromFile("image1.bmp") || !Textures[1].loadFromFile("image2.bmp") ||
        !Textures[2].loadFromFile("image3.bmp") || !Textures[3].loadFromFile("image4.bmp") ||
        !Textures[4].loadFromFile("image5.bmp"))
    {
        return 1;
    }

    // Create a lot of sprites
    sf::Sprite Sprites[NbSprites];
    for (int i = 0; i < NbSprites; ++i)
    {
        Sprites[i].setTexture(Textures[rand() % 5]);
		Sprites[i].setPosition(rand() % 700, rand() % 500);
    }

    // Start the timer
    sf::Clock Clock;
    int NbFrames = 0;

    // Start game loop
	while (Clock.getElapsedTime().asSeconds() < 5.f)
    {
        // Clear the screen
        App.clear();

        // Draw the sprites
        for (int i = 0; i < NbSprites; ++i)
            App.draw(Sprites[i]);

        // Finally, display rendered frame on screen
        App.display();
        NbFrames++;
    }

    return NbFrames;
}
