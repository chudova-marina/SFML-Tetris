#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include <queue>

class GameModel
{
public:
	const enum BlockType
	{
		I,
		S,
		Z,
		T,
		L,
		J,
		O,
		MAX_TYPES,
	};

	const enum ColorTile
	{
		YELLOW,
		RED,
		GREEN,
		PINK,
		ORANGE,
		BLUE,
		DARKBLUE,
		MAX_COLORS,
	};

	static const int m_cNumTilesBlock = 4;

private:
	static const int m_cNumVisibleNextBlocks = 3;
	static const int m_cFieldHeight = 20;
	static const int m_cFieldWidth = 10;

	std::random_device m_rd;
	std::mt19937 m_mersenne{m_rd()};

	struct BlockPoint
	{
		int x, y;
	};

	using oneBlockXY_t = std::array<BlockPoint, m_cNumTilesBlock>;

	struct OneBlock
	{
		BlockType type;
		oneBlockXY_t coord;
		ColorTile color;
		BlockPoint centerRotation;
	};

	using blocks_t = std::deque<OneBlock>;

	const std::array<std::array<int, m_cNumTilesBlock>, BlockType::MAX_TYPES> m_arrBlocks;

	OneBlock m_currBlock{};
	blocks_t m_arrNextBlocks{};

	struct TileOnField
	{
		bool exists;
		ColorTile color;
	};

	using field_t = std::array<std::array<TileOnField, m_cFieldWidth>, m_cFieldHeight>;
	field_t m_arrField{};
	int m_nLastNonEmptyRow{ m_cFieldHeight };

	float m_Delay{ 0.3 };
	float m_timer{ 0 };
	const float m_cDelayBottom{ 0.015 }; // My favorite "bug" in this game
	float m_timerBottom{ 0 };
	sf::Clock m_clock;

	bool m_bGameOver{};

	int m_nPoints{}, m_nOldPoints{};

public:
	GameModel();

	const OneBlock* getCurrBlock();
	const blocks_t* getNextBlocks();
	const field_t* getFieldWithTiles();
	const int getScore();
	void setNextBlockAsCurr();
	void moveBlockLeft();
	void moveBlockRight();
	void moveBlockDown();
	void moveBlockBottom();
	void rotateBlock();
	void tickTock();
	void MoveDownIfTimesUp();
	bool isGameOver();
	int getLastNonEmptyRow();
	void newGame();

private:
	BlockType _getRandomBlockType();
	ColorTile _getRandomColor();
	void _addNewNextBlock();
	bool _isCurrBlockOnBottom();
	void _fixBlockOnTheField();
	void _destroyLines();
};