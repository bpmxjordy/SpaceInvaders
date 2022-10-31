#include "Missile.h"
#include "../../Core/Renderer/ConsoleColours.h"


CHAR_INFO MissileSprite[] =				//These two are the sprites for the missiles
{
	{ ' ' , BACKGROUND_BRIGHT_RED },
	{ ' ', BACKGROUND_BRIGHT_RED },
	{ ' ', BACKGROUND_BRIGHT_RED },
};

CHAR_INFO EnemyMissileSprite[] =
{
	{ ' ', BACKGROUND_BLUE },
	{ ' ', BACKGROUND_BLUE },
	{ ' ', BACKGROUND_BLUE },
};

Missile::Missile()
:m_bInitialised(false)
, m_Active(true)
{

}

Missile::~Missile()
{

}

void Missile::Initialise(Vector2& position, Vector2& velocity)		//initialising the missiles with their position and and given velocity
{
	m_Velocity = velocity;

	Sprite::Initialise(m_Velocity.y < 0.0f ? MissileSprite : EnemyMissileSprite, Vector2(4, 1));

	Vector2 startPosition(position.x - 1, position.y - 1);
	SetPosition(startPosition);

	m_bInitialised = true;
}

void Missile::Update()												//This updates the missile and makes it move
{
	if (!m_bInitialised || !m_Active)
		return;

	SetPosition(Vector2(GetPosition().x - m_Velocity.y, GetPosition().y + m_Velocity.x));

}

void Missile::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised || !m_Active)
		return;

	Sprite::Render(pRenderer);
}

void Missile::Explode()
{
	m_Active = false;
}