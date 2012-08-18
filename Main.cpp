////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>

int SpritesSDL();
int SpritesSFML();

int SpritesAlphaSDL();
int SpritesAlphaSFML();

int SpritesRotatingSDL();
int SpritesRotatingSFML();

int TextStaticSDL();
int TextStaticSFML();

int TextDynamicSDL();
int TextDynamicSFML();


void Test(int (*SDLFunc)(), int (*SFMLFunc)())
{
    int SDL  = SDLFunc();
    int SFML = SFMLFunc();
    float Factor = static_cast<float>(SFML) / SDL;

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "SDL  displayed " << SDL  << " frames" << std::endl;
    std::cout << "SFML displayed " << SFML << " frames" << std::endl;
    std::cout << "--> SFML is " << Factor << "x as fast as SDL"  << std::endl;
    std::cout << std::endl;
}


int main(int argc, char *argv[])
{
    std::cout << "1/ Test : sprites" << std::endl;
    Test(&SpritesSDL, &SpritesSFML);

    std::cout << "2/ Test : alpha-blended sprites" << std::endl;
    Test(&SpritesAlphaSDL, &SpritesAlphaSFML);

    std::cout << "3/ Test : rotating sprites" << std::endl;
    Test(&SpritesRotatingSDL, &SpritesRotatingSFML);

    std::cout << "4/ Test : static text" << std::endl;
    Test(&TextStaticSDL, &TextStaticSFML);

    std::cout << "5/ Test : dynamic text" << std::endl;
    Test(&TextDynamicSDL, &TextDynamicSFML);

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
