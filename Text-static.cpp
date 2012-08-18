
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

const int NbLines = 20;


////////////////////////////////////////////////////////////
// SDL 20 lines of static text
////////////////////////////////////////////////////////////
int TextStaticSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    // Create the main window
    SDL_Surface* App = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (App == NULL)
        return 1;

    // Initialize SDL_ttf
    if (TTF_Init() < 0)
        return 1;

    // Load the font
    TTF_Font* Font = TTF_OpenFont("cheeseburger.ttf", 30);
    if (!Font)
        return 1;

    // Render the text to a surface
    const char* String = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789";
    SDL_Color TextColor = {0, 128, 128};
    SDL_Surface* Text = TTF_RenderText_Blended(Font, String, TextColor);
    if (!Text)
        return 1;

    // Define the text rectangle
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = Text->w;
    Rect.h = Text->h;

    // Start the timer
    Uint32 Time = SDL_GetTicks();
    int NbFrames = 0;

    // Start game loop
    while (SDL_GetTicks() < Time + 5000)
    {
        // Clear the screen
        SDL_FillRect(App, NULL, SDL_MapRGB(App->format, 0, 0, 0));

        // Draw the text
        for (int i = 0; i < NbLines; ++i)
        {
            Rect.y = i * 30;
            SDL_BlitSurface(Text, NULL, App, &Rect);
        }

        // Finally, display rendered frame on screen
        SDL_Flip(App);
        NbFrames++;
    }

    // Free the surface
    SDL_FreeSurface(Text);

    // Close the font
    TTF_CloseFont(Font);

    // Exit SDL_ttf
    TTF_Quit();

    // Exit SDL
    SDL_Quit();

    return NbFrames;
}


////////////////////////////////////////////////////////////
// SFML 20 lines of static text
////////////////////////////////////////////////////////////
int TextStaticSFML()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML_App");

    // Load the font
    sf::Font TextFont;
    if (!TextFont.loadFromFile("cheeseburger.ttf"))
        return 1;

    // Create the string
    const char* String = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789";
    sf::Text Text(String, TextFont, 30.f);
    Text.setColor(sf::Color(0, 128, 128));

    // Start the timer
    sf::Clock Clock;
    int NbFrames = 0;

    // Start game loop
	while (Clock.getElapsedTime().asSeconds() < 5.f)
    {
        // Clear the screen
        App.clear();

        // Draw the text
        for (int i = 0; i < NbLines; ++i)
        {
			Text.setPosition(Text.getPosition().x, i * 30.f);
            App.draw(Text);
        }

        // Finally, display rendered frame on screen
        App.display();
        NbFrames++;
    }

    return NbFrames;
}
