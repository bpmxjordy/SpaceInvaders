#include "PlayerShip.h"
#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include <Windows.h>

const int MOVEMENT_SPEED = 2;

CHAR_INFO ShipSprite[] =				//The sprite for the player ship
{
	{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_BRIGHT_RED			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_BRIGHT_RED			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },{ 0 ,BACKGROUND_WHITE			 },
	{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_BRIGHT_RED },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
};

PlayerShip::PlayerShip()
	:m_UpKey(0)
	, m_DownKey(0)
	, m_bInitialised(false)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Initialise(Vector2& position, int upKey, int downKey)				//This is initialising the player ship, the sprite and the keys that the player can use
{
	m_UpKey = upKey;
	m_DownKey = downKey;

	Sprite::Initialise(ShipSprite, Vector2(12, 6));

	Vector2 startPosition(0, SCREEN_HEIGHT / 2);
	SetPosition(startPosition);

	m_bInitialised = true;
}

void PlayerShip::Update()
{
	if (!m_bInitialised)
		return;

	if (UpKeyPressed())
	{
		MoveUp();
	}
	if (DownKeyPressed())
	{
		MoveDown();
	}


}

void PlayerShip::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	Sprite::Render(pRenderer);
}

void PlayerShip::MoveUp()												//This is used to move the ship up when the player presses the up key
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y - MOVEMENT_SPEED));

	if (GetPosition().y < 0)											//If the player reaches the top of the screen then the ship will stop
	{
		MoveDown();
	}
}

void PlayerShip::MoveDown()												//This is used to move the player ship downwards when the player presses the down key
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y + MOVEMENT_SPEED));

	if (GetPosition().y + GetSize().y > SCREEN_HEIGHT)					//Tells the ship to stop when it reaches the bottom of the screen
	{
		MoveUp();
	}
}

bool PlayerShip::UpKeyPressed()											//Setting the keystate to the corrisponding key when pressed
{
	return (GetKeyState(m_UpKey) < 0);
}

bool PlayerShip::DownKeyPressed()
{
	return (GetKeyState(m_DownKey) < 0);
}
