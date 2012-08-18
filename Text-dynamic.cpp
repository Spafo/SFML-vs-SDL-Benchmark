
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iomanip>
#include <iostream>
#include <sstream>

const int NbLines = 20;


////////////////////////////////////////////////////////////
// SDL 20 lines of dynamic text
////////////////////////////////////////////////////////////
int TextDynamicSDL()
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
            // Use different styles
            switch (i % 5)
            {
                case 0 : TTF_SetFontStyle(Font, TTF_STYLE_NORMAL);    break;
                case 1 : TTF_SetFontStyle(Font, TTF_STYLE_BOLD);      break;
                case 2 : TTF_SetFontStyle(Font, TTF_STYLE_ITALIC);    break;
                case 3 : TTF_SetFontStyle(Font, TTF_STYLE_UNDERLINE); break;
                case 4 : TTF_SetFontStyle(Font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE); break;
            }

            // Define the dynamic text
            std::ostringstream oss;
            oss << "Hi, I'm the line number " << i << " and the time elapsed is " << std::setprecision(2) << ((SDL_GetTicks() - Time) / 1000.f) << " sec";

            // Render the text to a surface
            SDL_Color TextColor = {0, 128, 128};
            SDL_Surface* Text = TTF_RenderText_Blended(Font, oss.str().c_str(), TextColor);

            // Define the text rectangle
            SDL_Rect Rect;
            Rect.x = 0;
            Rect.y = i * 30;
            Rect.w = Text->w;
            Rect.h = Text->h;

            // Blit the text surface
            SDL_BlitSurface(Text, NULL, App, &Rect);

            // Free the surface
            SDL_FreeSurface(Text);
        }

        // Finally, display rendered frame on screen
        SDL_Flip(App);
        NbFrames++;
    }

    // Close the font
    TTF_CloseFont(Font);

    // Exit SDL_ttf
    TTF_Quit();

    // Exit SDL
    SDL_Quit();

    return NbFrames;
}


////////////////////////////////////////////////////////////
// SFML 20 lines of dynamic text
////////////////////////////////////////////////////////////
int TextDynamicSFML()
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
            // Use different styles
            switch (i % 5)
            {
                case 0 : Text.setStyle(sf::Text::Regular);    break;
                case 1 : Text.setStyle(sf::Text::Bold);       break;
                case 2 : Text.setStyle(sf::Text::Italic);     break;
                case 3 : Text.setStyle(sf::Text::Underlined); break;
                case 4 : Text.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined); break;
            }

            // Define the dynamic text
            std::ostringstream oss;
			oss << "Hi, I'm the line number " << i << " and the time elapsed is " << std::setprecision(2) << Clock.getElapsedTime().asSeconds() << " sec";
            Text.setString(oss.str());

            // Draw the string
			Text.setPosition(Text.getPosition().x, i * 30.f);
            App.draw(Text);
        }

        // Finally, display rendered frame on screen
        App.display();
        NbFrames++;
    }

    return NbFrames;
}
