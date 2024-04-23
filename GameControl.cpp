#include "GameControl.h"

void GameControl::setTextureTile(const std::string& textureFilename)
{
	m_oView.get()->setTile(textureFilename);
}

void GameControl::setTextureBackground(const std::string& textureFilename)
{
	m_oView.get()->setBackground(textureFilename);
}

void GameControl::setTextureFrame(const std::string& textureFilename)
{
	m_oView.get()->setFrame(textureFilename);
}

void GameControl::setMainFont(const std::string& fontFilename)
{
	m_oView.get()->setMainFont(fontFilename);
}

void GameControl::setMusic(const std::string& musicFilename)
{
	m_oView.get()->setMusic(musicFilename);
}

void GameControl::showMenu()
{
	m_oView.get()->drawBackground();
}

void GameControl::drawBackground()
{
	m_oView.get()->drawBackground();
}

void GameControl::drawFront()
{
	m_oView.get()->drawNextBlocksWindow();

	auto nextBlocks = m_oModel.get()->getNextBlocks();
	
	int offsetY{};
	for (int i = 0; i < nextBlocks->size(); i++)
	{
		offsetY += 5;
		for (const auto& tile : nextBlocks->at(i).coord)
			m_oView.get()->drawTile(nextBlocks->at(i).color, tile.x + 14, tile.y + offsetY, 0.7);
	}

	m_oView.get()->drawFrame();
}

void GameControl::playPauseMusic()
{
	m_oView.get()->playPauseMusic();
}

void GameControl::setNextBlock()
{
	m_oModel.get()->setNextBlockAsCurr();
}

void GameControl::processTetris()
{
	_outputCurrBlock();
	_outputFixedTiles();
	_outputScore();
	m_oView.get()->drawPlayPause();
}

void GameControl::onKeyLeft()
{
	m_oModel.get()->moveBlockLeft();
}

void GameControl::onKeyRight()
{
	m_oModel.get()->moveBlockRight();
}

void GameControl::onKeyDown()
{
	m_oModel.get()->moveBlockDown();
}

void GameControl::onKeyUp()
{
	m_oModel.get()->rotateBlock();
}

void GameControl::onKeySpace()
{
	m_oModel.get()->moveBlockBottom();
}

void GameControl::onKeyEnter()
{
	if (m_oModel.get()->isGameOver())
		m_oModel.get()->newGame();
}

void GameControl::onKeyEscape()
{
	if (m_oModel.get()->isGameOver())
		m_oView.get()->closeWindow();
}

void GameControl::onMouseLeft()
{
	auto mousePos = m_oView.get()->getMousePosition();
	if (535 < mousePos.x and mousePos.x < 580 and 14 < mousePos.y and mousePos.y < 66)
		playPauseMusic();
}

void GameControl::tickTock()
{
	m_oModel.get()->tickTock();
}

void GameControl::moveDownIfTimesUp()
{
	m_oModel.get()->MoveDownIfTimesUp();
}

void GameControl::checkIfGameOver()
{
	if (m_oModel.get()->isGameOver())
		m_oView.get()->printCenteredText("Game Over!");
}

void GameControl::_outputCurrBlock()
{
	auto currBlock = m_oModel.get()->getCurrBlock();
	for (const auto& tile : currBlock->coord)
		m_oView.get()->drawTile(currBlock->color, tile.x, tile.y, 1);
}

void GameControl::_outputFixedTiles()
{
	auto arrField = m_oModel.get()->getFieldWithTiles();
	for (int y = arrField->size() - 1; y >= m_oModel.get()->getLastNonEmptyRow(); y--)
	{
		auto arrLine = arrField->at(y);
		for (int x = 0; x < arrLine.size(); x++)
		{
			auto arrTile = arrLine.at(x);
			if (arrTile.exists == true)
				m_oView.get()->drawTile(arrTile.color, x, y, 1);
		}
	}
}

void GameControl::_outputScore()
{
	auto nPoints = m_oModel.get()->getScore();
	m_oView.get()->drawScoreWindow(nPoints);
}