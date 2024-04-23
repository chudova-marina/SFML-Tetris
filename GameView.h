#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <vector>

using namespace sf;

class GameView
{
public:
	GameView(RenderWindow& window) : m_rwWindow(window) {};

	void printCenteredText(std::string text);

	void setTile(const std::string& textureFilename);    
	void setBackground(const std::string& textureFilename);
	void setFrame(const std::string& textureFilename);
	void setMainFont(const std::string& fontFilename);
	void setMusic(const std::string& musicFilename);


	const Vector2i getMousePosition();
	void playPauseMusic();

	void drawTile(const int nTile, const int xPos, const int yPos, float coefScale);
	void drawBackground();
	void drawFrame();
	void drawNextBlocksWindow();
	void drawScoreWindow(int nPoints);
	void drawPlayPause();

	void closeWindow();

private:
	const int m_cPxTile = 32; // A tile side in pixels

	std::vector<Sprite> m_arrTiles{};
	Texture m_txrTiles{};

	Texture m_txrBackground{};
	Sprite  m_sprBackground;

	Texture m_txrFrame{};
	Sprite m_sprFrame{};

	RenderWindow& m_rwWindow;
	Font m_mainFont;

	Music m_music;
};