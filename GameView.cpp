#include "GameView.h"

void GameView::drawTile(const int nTile, const int xPos, const int yPos, float coefScale)
{
	m_arrTiles[nTile].setPosition(xPos * m_cPxTile * coefScale, yPos * m_cPxTile * coefScale);
	if (coefScale == 1)
		m_arrTiles[nTile].move(10, 10); // offset
	m_arrTiles[nTile].setScale(Vector2f(coefScale, coefScale));
	m_rwWindow.draw(m_arrTiles[nTile]);
}

void GameView::drawBackground()
{
	m_rwWindow.draw(m_sprBackground);
}

void GameView::drawFrame()
{
	m_rwWindow.draw(m_sprFrame);
}

void GameView::drawNextBlocksWindow()
{
	RectangleShape rect(Vector2f(160, 370));
	rect.setPosition(350, 10);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Black);
	m_rwWindow.draw(rect);

	Text sText("Next Blocks:", m_mainFont, 20);
	sText.setStyle(Text::Bold | Text::Underlined);
	sText.setFillColor(Color::Black);
	sText.setPosition(370, 15);
	m_rwWindow.draw(sText);
}

void GameView::drawScoreWindow(int nPoints)
{
	RectangleShape rect(Vector2f(160, 100));
	rect.setPosition(350, 390);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Black);
	m_rwWindow.draw(rect);

	Text sText("Your Score:", m_mainFont, 20);
	sText.setStyle(Text::Bold | Text::Underlined);
	sText.setFillColor(Color::Black);
	sText.setPosition(370, 395);
	m_rwWindow.draw(sText);
	Text sTextScore(std::to_string(nPoints), m_mainFont, 30);
	sTextScore.setStyle(Text::Bold);
	sTextScore.setFillColor(Color::Black);
	sTextScore.setPosition(370, 425);
	m_rwWindow.draw(sTextScore);
}

void GameView::drawPlayPause()
{
	if (m_music.getStatus() == m_music.Paused)
	{
		CircleShape playButton(30, 3);
		playButton.rotate(90);
		playButton.setFillColor(Color::Black);
		playButton.setPosition(580, 10);
		m_rwWindow.draw(playButton);
	}
	else if (m_music.getStatus() == m_music.Playing)
	{
		RectangleShape Pause1(Vector2f(15, 52));
		RectangleShape Pause2(Vector2f(15, 52));
		Pause1.setFillColor(Color::Black);
		Pause2.setFillColor(Color::Black);
		Pause1.setPosition(535, 14);
		Pause2.setPosition(565, 14);
		m_rwWindow.draw(Pause1);
		m_rwWindow.draw(Pause2);
	}

	Text stext("MUSIC", m_mainFont, 20);
	stext.setFillColor(Color::Black);
	stext.setPosition(528, 70);
	m_rwWindow.draw(stext);
}

void GameView::closeWindow()
{
	m_rwWindow.close();
}

void GameView::printCenteredText(std::string text)
{
	const float widthGap{ 15 }, heightGap{ 10 };
	Text stext(text, m_mainFont, 30);
	stext.setStyle(Text::Bold | Text::Underlined);
	stext.setFillColor(Color::Black);
	auto nSize = stext.getLocalBounds();

	float rectWidth = nSize.width + (widthGap * 2.5);
	float rectHeight = nSize.height + (heightGap * 4);
	float rectX = (m_rwWindow.getSize().x - rectWidth) / 2;
	float rectY = (m_rwWindow.getSize().y - rectHeight) / 2;
	float textX = rectX + widthGap;
	float textY = rectY + heightGap;

	RectangleShape rect(Vector2f(rectWidth, rectHeight));
	rect.setOutlineThickness(5);
	rect.setOutlineColor(Color::Black);
	rect.setPosition(rectX, rectY);
	m_rwWindow.draw(rect);

	stext.setPosition(textX, textY);
	m_rwWindow.draw(stext);
}

void GameView::setTile(const std::string& textureFilename)
{
	m_txrTiles.loadFromFile(textureFilename);
	m_txrTiles.setSmooth(true);
	auto sizeTexture = m_txrTiles.getSize();
	int numTiles = sizeTexture.x / m_cPxTile;
	m_arrTiles.resize(numTiles);

	for (int i = 0; i < numTiles; i++)
		m_arrTiles[i] = Sprite(m_txrTiles, IntRect(m_cPxTile * i, 0, m_cPxTile, m_cPxTile));
}

void GameView::setBackground(const std::string& textureFilename)
{
	m_txrBackground.loadFromFile(textureFilename);
	m_txrBackground.setSmooth(true);
	m_sprBackground = Sprite(m_txrBackground);
	m_sprBackground.rotate(90);
	m_sprBackground.setPosition(Vector2f(600, 0));
	m_sprBackground.setScale(Vector2f(1.1, 1.1));
}

void GameView::setFrame(const std::string& textureFilename)
{
	m_txrFrame.loadFromFile(textureFilename);
	m_txrFrame.setSmooth(true);
	m_sprFrame = Sprite(m_txrFrame);
	m_sprFrame.setScale(Vector2f(0.9014, 0.9091));
}

void GameView::setMainFont(const std::string& fontFilename)
{
	m_mainFont.loadFromFile(fontFilename);
}

void GameView::setMusic(const std::string& musicFilename)
{
	m_music.openFromFile(musicFilename);
}

const Vector2i GameView::getMousePosition()
{
	return Mouse::getPosition(m_rwWindow);
}

void GameView::playPauseMusic()
{
	if (m_music.getStatus() == m_music.Playing)
		m_music.pause();
	else
	{
		m_music.setLoop(true);
		m_music.play();
	}
}