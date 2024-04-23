#include "GameModel.h"

GameModel::GameModel()
	: m_arrBlocks({
		 1, 3, 5, 7, // I
		 2, 4, 5, 7, // S
		 3, 5, 4, 6, // Z
		 3, 5, 4, 7, // T
		 2, 3, 5, 7, // L
		 3, 5, 7, 6, // J
		 2, 3, 4, 5, // O 
		})
{
	for (int i = 0; i < m_cNumVisibleNextBlocks; i++)
		_addNewNextBlock();
}

const GameModel::OneBlock* GameModel::getCurrBlock()
{
	return &m_currBlock;
}

const GameModel::blocks_t* GameModel::getNextBlocks()
{
	return &m_arrNextBlocks;
}

const GameModel::field_t* GameModel::getFieldWithTiles()
{
	return &m_arrField;
}

const int GameModel::getScore()
{
	return m_nPoints;
}

void GameModel::_fixBlockOnTheField()
{
	if (isGameOver())
		return;

	for (auto& tile : m_currBlock.coord)
	{
		if (tile.y < 0)
		{
			m_bGameOver = true;
			return;
		}
		m_arrField[tile.y][tile.x].exists = true;
		m_arrField[tile.y][tile.x].color  = m_currBlock.color;

		if (m_nLastNonEmptyRow > tile.y)
			m_nLastNonEmptyRow = tile.y;
	}

	_destroyLines();
}

void GameModel::_destroyLines()
{
	int nDestroyedLines{ 0 };

	for (int y = m_arrField.size() - 1; y >= m_nLastNonEmptyRow; y--)
	{
		auto arrLine = m_arrField.at(y);
		bool bLineIsFull{ true };
		for (int x = 0; x < arrLine.size(); x++)
		{
			auto arrTile = arrLine.at(x);
			if (arrTile.exists == false)
			{
				bLineIsFull = false;
				break;
			}
		}

		if (bLineIsFull == true)
		{
			int nFirstEmptyRow = m_nLastNonEmptyRow - 1;
			for (int yCurr = y; yCurr > nFirstEmptyRow; yCurr--)
				if (yCurr == 0)
					m_arrField.at(yCurr) = {};
				else
					m_arrField.at(yCurr) = m_arrField.at(yCurr - 1);

			m_nLastNonEmptyRow++;
			y++;
			nDestroyedLines++;
		}
	}
	
	switch (nDestroyedLines)
	{
	case 1:
		m_nPoints += 100;
		break;
	case 2:
		m_nPoints += 300;
		break;
	case 3:
		m_nPoints += 700;
		break;
	case 4:
		m_nPoints += 1500;
		break;
	default:
		break;
	}

	if ((m_nPoints - m_nOldPoints) > 1500)
	{
		m_nOldPoints = m_nPoints;
		m_Delay -= 0.05;
	}
}

void GameModel::setNextBlockAsCurr()
{
	if (isGameOver())
		return;

	m_currBlock = m_arrNextBlocks.front();
	m_arrNextBlocks.pop_front();
	_addNewNextBlock();
}

void GameModel::moveBlockLeft()
{
	if (isGameOver())
		return;

	for (auto& tile : m_currBlock.coord)
		if (tile.x <= 0 or (tile.y > 0 and m_arrField[tile.y][tile.x - 1].exists == true))
			return;

	for (auto& tile : m_currBlock.coord)
		--tile.x;

	m_currBlock.centerRotation = m_currBlock.coord[1];
}

void GameModel::moveBlockRight()
{
	if (isGameOver())
		return;

	for (auto& tile : m_currBlock.coord)
		if (tile.x >= m_cFieldWidth - 1 or (tile.y > 0 and m_arrField[tile.y][tile.x + 1].exists == true))
			return;

	for (auto& tile : m_currBlock.coord)
		++tile.x;

	m_currBlock.centerRotation = m_currBlock.coord[1];
}

void GameModel::moveBlockDown()
{
	if (isGameOver() or _isCurrBlockOnBottom())
		return;

	for (auto& tile : m_currBlock.coord)
		++tile.y;

	m_currBlock.centerRotation = m_currBlock.coord[1];
}

void GameModel::moveBlockBottom()
{
	while (_isCurrBlockOnBottom() == false)
		moveBlockDown();
}

int GameModel::getLastNonEmptyRow()
{
	return m_nLastNonEmptyRow;
}

GameModel::BlockType GameModel::_getRandomBlockType()
{
	return static_cast<BlockType>(m_mersenne() % BlockType::MAX_TYPES);
}

GameModel::ColorTile GameModel::_getRandomColor()
{
	return static_cast<ColorTile>(m_mersenne() % ColorTile::MAX_COLORS);
}

void GameModel::_addNewNextBlock()
{
	if (isGameOver())
		return;

	OneBlock block{};
	block.type = _getRandomBlockType();
	for (int i = 0; i < m_cNumTilesBlock; i++)
	{
		block.coord.at(i).x = (m_arrBlocks[block.type][i] % 2) + ((m_cFieldWidth - 1) / 2);
		block.coord.at(i).y = (m_arrBlocks[block.type][i] / 2) - 3;
	}
	block.color = _getRandomColor();
	block.centerRotation = block.coord[1];
	m_arrNextBlocks.push_back(block);
}

void GameModel::newGame()
{
	m_arrNextBlocks.clear();
	m_arrField = {};
	m_nPoints = 0;
	m_bGameOver = false;


	for (int i = 0; i < m_cNumVisibleNextBlocks; i++)
		_addNewNextBlock();
	setNextBlockAsCurr();
}

void GameModel::rotateBlock()
{
	if (isGameOver() or m_currBlock.type == BlockType::O)
		return;

	oneBlockXY_t newCoord{};
	for (int i = 0; i < m_cNumTilesBlock; i++)
	{
		int diffX{ m_currBlock.coord.at(i).x - m_currBlock.centerRotation.x };
		int diffY{ m_currBlock.coord.at(i).y - m_currBlock.centerRotation.y };
		newCoord.at(i).x = m_currBlock.centerRotation.x - diffY;
		newCoord.at(i).y = m_currBlock.centerRotation.y + diffX;

		if (newCoord.at(i).y > 0 and newCoord.at(i).y < m_cFieldHeight
			and newCoord.at(i).x > 0 and newCoord.at(i).x < m_cFieldWidth
			and m_arrField[newCoord.at(i).y][newCoord.at(i).x].exists == true)
			return;
	}

	// When the block is out of the left or right border
	m_currBlock.coord = newCoord;
	
	char offset{ '0' };
	do
	{
		if (offset != '0')
		{
			for (auto& tile : m_currBlock.coord)
				switch (offset)
				{
				case '-':
					++tile.x;
					break;
				case '+':
					--tile.x;
					break;
				default:
					break;
				}

			m_currBlock.centerRotation = m_currBlock.coord[1];
		}

		for (auto& tile : m_currBlock.coord)
			if (tile.x < 0)
			{
				offset = '-';
				break;
			}
			else if (tile.x >= m_cFieldWidth)
			{
				offset = '+';
				break;
			}
			else
				offset = '0';
	} while (offset != '0');
}

bool GameModel::_isCurrBlockOnBottom()
{
	for (auto& tile : m_currBlock.coord)
	{
		if (tile.y >= m_cFieldHeight - 1 or (tile.y > 0 and m_arrField[tile.y + 1][tile.x].exists == true))
			return true;
	}
	return false;
}

void GameModel::tickTock()
{
	auto time = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();
	m_timer += time;
}

void GameModel::MoveDownIfTimesUp()
{
	if (_isCurrBlockOnBottom())
	{
		if (m_timerBottom >= m_cDelayBottom)
		{
			m_timer = 0;
			m_timerBottom = 0;
			_fixBlockOnTheField();
			setNextBlockAsCurr();
		}
		else
		{
			auto time = m_clock.getElapsedTime().asSeconds();
			m_clock.restart();
			m_timerBottom += time;
		}
		return;
	}

	if (m_timer >= m_Delay)
	{
		for (auto& tile : m_currBlock.coord)
			++tile.y;
		m_currBlock.centerRotation = m_currBlock.coord[1];
		m_timer = 0;
	}
}

bool GameModel::isGameOver()
{
	return m_bGameOver;
}