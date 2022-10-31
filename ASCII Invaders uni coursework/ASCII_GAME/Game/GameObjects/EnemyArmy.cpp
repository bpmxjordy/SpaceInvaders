#include "EnemyArmy.h"
#include "../Game.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>
#include <thread>
#include <cmath>
#include <limits> // 'std::numeric_limits'

float deltaTime = 1.0f / 30.0f;


const int ENEMY_SPACING_X = 4;
const int ENEMY_SPACING_Y = 4;

EnemyArmy::EnemyArmy()
:m_UpdateTimer(0.0f)
,m_pGame(NULL)
,m_ScoreEarned(0)
{

}

EnemyArmy::~EnemyArmy()
{

}


void EnemyArmy::Initialise(Game* pGame)
{
	srand(time(NULL));

	m_pGame = pGame;
	deltaTime = 1.0f / 10.0f;

	m_MovingRight = true;

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)						//This will initialise all of the enemy ships in a random position withing 500 pixels past the right side of the screen
	{

		int randomWidth = rand() % 500 + SCREEN_WIDTH;					//creating random co-ordinates
		int randomHeight = rand() % 75 + 30;

		Vector2 enemyShipSpawnPos(randomWidth, SCREEN_WIDTH);		//setting a vector2 to the random values i made
		//m_EnemyShip[i][j].Initialise(Vector2(4 + j * 7, 2 + i * 4), 5/*, (i+1.0f) * 0.3f*/ );
		//m_EnemyShip[i][j].Initialise(Vector2(iSecret, SCREEN_WIDTH), 10, i, 10, (i + 1.0f) * 0.3f);
		//m_EnemyShip[i][j].Initialise(Vector2(iSecret, SCREEN_WIDTH), 10, i, 10, (i + 1.0f) * 0.3f);
		m_EnemyShip[i].Initialise(Vector2(randomWidth, (rand() % 75 + 20)), 5, i, 20, (i + 1.0f) * 0.3f);		//initialising the enemy ships in this random position with a firerate of 5 and a score value of 20
	}
}

void EnemyArmy::Update()
{
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{
		if (m_EnemyShip[i].GetAnimationFrame() > 2)				//if the enemy ship and completed the explode animation then respawn them in another random postion
		{
			srand(time(NULL));

			int randomWidth = rand() % 500 + SCREEN_WIDTH;
			int randomHeight = rand() % 75 + 30;
			Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
			m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
		}
	}
	//update enemy movement
	m_UpdateTimer += deltaTime;

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		m_EnemyShip[i].MoveLeft();								//make the enemies move left
	}




	//update enemy animations
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		if (m_EnemyShip[i].Update(deltaTime))					
		{
			Missile* pMissile = new Missile();					//Creating a new missile every time an enemy shoots
			pMissile->Initialise(Vector2(m_EnemyShip[i].GetPosition().x + (m_EnemyShip[i].GetSize().x / 2.0f), m_EnemyShip[i].GetPosition().y + 1), Vector2(0, MISSILE_SPEED));
			m_pGame->AddEnemyMissile(pMissile);					//Add a new missile
		}

	}



		}

			
int EnemyArmy::CheckCollision() // AABB - AABB collision
{

	return true;
}

bool EnemyArmy::HasLanded()
{

	for ( int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{
		//check the right most ship in this row
		if (m_EnemyShip[i].Active())
		{
			if (m_EnemyShip[i].GetPosition().x > 0 && m_EnemyShip[i].GetPosition().x < 10)
			{
				int randomWidth = rand() % 500 + SCREEN_WIDTH;
				int randomHeight = rand() % (SCREEN_HEIGHT - 2) + 2;

				Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
				m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
					return true;
				

			}
			
		}
	}

	return false;
}

void EnemyArmy::Render(ASCIIRenderer* pRenderer)
{
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

			m_EnemyShip[i].Render(pRenderer);
		}
	
}


bool EnemyArmy::Collides(Sprite& otherSprite)															//This function checks if the player missile collides with the enemy ship
{
	bool collision = false;

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)														//loops through each invader
	{

		if (m_EnemyShip[i].Active() && otherSprite.Collides(m_EnemyShip[i].GetCurrentSprite()))
		{
			collision = true;
			m_ScoreEarned += m_EnemyShip[i].GetScoreValue();
			m_EnemyShip[i].Explode();
				if (m_EnemyShip[i].GetAnimationFrame() > 2)												//Setting them back to a random spawn point
				{

					int randomWidth = rand() % 500 + SCREEN_WIDTH;
					int randomHeight = rand() % 75 + 30;

					Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
					m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
					
				}

			}
			
		}


	

	

	return collision;
}

int EnemyArmy::GetNumActiveEnemies()
{
	int activeEnemies = 0;
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

			if (m_EnemyShip[i].Active())
			{
				activeEnemies++;
			}
		
	}

	return activeEnemies;
}
