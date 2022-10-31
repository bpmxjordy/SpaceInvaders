#ifndef _ENEMY_ARMY_H_
#define _ENEMY_ARMY_H_

#include "EnemyShip.h"

class ASCIIRenderer;
class Game;

const int NUM_INVADERS_PER_ROW = 5;
const int TOP_OF_PLAY_SCREEN = 15;

class EnemyArmy
{
public:
	EnemyArmy();
	~EnemyArmy();

	void Initialise(Game* pGame);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	bool Collides(Sprite& otherSprite);

	int CheckCollision();

	int GetScore() { int retVal = m_ScoreEarned; m_ScoreEarned = 0; return retVal; }
	int GetNumActiveEnemies();

	bool HasLanded();
	int bossLives = 3;
private:

	bool ShouldChangeDirection();

	bool m_MovingRight;

	EnemyShip m_EnemyShip[NUM_INVADERS_PER_ROW];

	float m_UpdateTimer;

	Game* m_pGame;

	int m_ScoreEarned;

	int m_PlayerLives = 3;

	

};

#endif
