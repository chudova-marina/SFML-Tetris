#include <SFML/Graphics.hpp>
#include "GameControl.h"
#include <memory> 

int main()
{
	const int windowWidthPx{ 600 }, windowHeightPx{ 850 };
	RenderWindow window(VideoMode(windowWidthPx, windowHeightPx), "The Game!");
	auto posWindow = window.getPosition();
	posWindow.y -= 20;
	window.setPosition(posWindow);
	window.setMouseCursorVisible(true);

	GameControl oGame(window);
	oGame.setTextureTile("Files\\tiles2.png");
	oGame.setTextureBackground("Files\\bkg2.png");
	oGame.setTextureFrame("Files\\Frame.png");
	oGame.setMainFont("Files\\Roboto\\Roboto-Regular.ttf");
	oGame.setMusic("Files\\oji-flore.flac");
	oGame.showMenu();
	oGame.setNextBlock();
	oGame.playPauseMusic();

	while (window.isOpen())
	{
		oGame.tickTock();

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				switch (event.key.code)
				{ 
				case Keyboard::Left:
					oGame.onKeyLeft();
					break;
				case Keyboard::Right:
					oGame.onKeyRight();
					break;
				case Keyboard::Down:
					oGame.onKeyDown();
					break;
				case Keyboard::Up:
					oGame.onKeyUp();
					break;
				case Keyboard::Space:
					oGame.onKeySpace();
					break;
				case Keyboard::Enter:
					oGame.onKeyEnter();
					break;
				case Keyboard::Escape:
					oGame.onKeyEscape();
					break;
				default:
					break;
				}
			case Event::MouseButtonReleased:
				switch (event.key.code)
				{
				case Mouse::Left:
					oGame.onMouseLeft();
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		window.clear(Color::White);
		oGame.drawBackground();
		oGame.moveDownIfTimesUp();
		oGame.processTetris();
		oGame.drawFront();
		oGame.checkIfGameOver();
		window.display();
	}

	return 0;
}