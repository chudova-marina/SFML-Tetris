#pragma once
#include <memory>
#include "GameModel.h"
#include "GameView.h"

class GameControl
{
public:
	GameControl(RenderWindow& window)
	{
		m_oView = std::make_unique<GameView>(window);
		m_oModel = std::make_unique<GameModel>();
	};

	void setTextureTile(const std::string& textureFilename);
	void setTextureBackground(const std::string& textureFilename);
	void setTextureFrame(const std::string& textureFilename);
	void setMainFont(const std::string& fontFilename);
	void setMusic(const std::string& musicFilename);
	void showMenu();
	void drawBackground();
	void drawFront();
	void playPauseMusic();
	void setNextBlock();
	void processTetris();
	void onKeyLeft();
	void onKeyRight();
	void onKeyDown();
	void onKeyUp();
	void onKeySpace();
	void onKeyEnter();
	void onKeyEscape();
	void onMouseLeft();
	void tickTock();
	void moveDownIfTimesUp();
	void checkIfGameOver();

private:
	std::unique_ptr<GameView> m_oView;
	std::unique_ptr<GameModel> m_oModel;

	void _outputCurrBlock();
	void _outputFixedTiles();
	void _outputScore();
};