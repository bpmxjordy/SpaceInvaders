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

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		int randomWidth = rand() % 500 + SCREEN_WIDTH;
		int randomHeight = rand() % 80 - 20;

		Vector2 enemyShipSpawnPos(randomWidth, SCREEN_WIDTH);
		//m_EnemyShip[i][j].Initialise(Vector2(4 + j * 7, 2 + i * 4), 5/*, (i+1.0f) * 0.3f*/ );
		//m_EnemyShip[i][j].Initialise(Vector2(iSecret, SCREEN_WIDTH), 10, i, 10, (i + 1.0f) * 0.3f);
		//m_EnemyShip[i][j].Initialise(Vector2(iSecret, SCREEN_WIDTH), 10, i, 10, (i + 1.0f) * 0.3f);
		m_EnemyShip[i].Initialise(Vector2(randomWidth, (rand() % 85 + 10)), 5, i, 50, (i + 1.0f) * 0.3f);
	}
}

void EnemyArmy::Update()
{
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{
		if (m_EnemyShip[i].GetAnimationFrame() == 3)
		{
			srand(time(NULL));
			int randomWidth = rand() % 500 + SCREEN_WIDTH;
			int randomHeight = rand() % 80 + 10;

			int randomDirection = rand() % -5 + 5;
			Missile* pMissile = new Missile();
			pMissile->Initialise(Vector2(m_EnemyShip[i].GetPosition().x - (m_EnemyShip[i].GetSize().x / 2.0f), m_EnemyShip[i].GetPosition().y + 1), Vector2(0, -2));
			m_pGame->AddEnemyMissile(pMissile);

			int randomDirection2 = rand() % 5 + -5;
			Missile* pMissile2 = new Missile();
			pMissile2->Initialise(Vector2(m_EnemyShip[i].GetPosition().x - (m_EnemyShip[i].GetSize().x / 2.0f), m_EnemyShip[i].GetPosition().y + 1), Vector2(randomDirection2, -2));
			m_pGame->AddEnemyMissile(pMissile2);

			int randomDirection3 = rand() % 5 + -5;
			Missile* pMissile3 = new Missile();
			pMissile3->Initialise(Vector2(m_EnemyShip[i].GetPosition().x - (m_EnemyShip[i].GetSize().x / 2.0f), m_EnemyShip[i].GetPosition().y + 1), Vector2(randomDirection3, MISSILE_SPEED));
			m_pGame->AddEnemyMissile(pMissile3);
			

			Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
			m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
		}
	}
	//update enemy movement
	m_UpdateTimer += deltaTime;

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		m_EnemyShip[i].MoveLeft();
	}




	//update enemy animations
	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		if (m_EnemyShip[i].Update(deltaTime))
		{
			Missile* pMissile = new Missile();
			pMissile->Initialise(Vector2(m_EnemyShip[i].GetPosition().x + (m_EnemyShip[i].GetSize().x / 2.0f), m_EnemyShip[i].GetPosition().y + 1), Vector2(0, MISSILE_SPEED));
			m_pGame->AddEnemyMissile(pMissile);
		}

	}



	


			/*for (int i = 0; i < NUM_INVADERS_PER_ROW; i++) {
				for (int j = 0; j < NUM_INVADERS_PER_ROW; j++)
				{

					int enemyship1_x = m_EnemyShip[i].GetPosition().x;
					int enemyship1_y = m_EnemyShip[i].GetPosition().y;

					int enemyship2_x = m_EnemyShip[j].GetPosition().x;
					int enemyship2_y = m_EnemyShip[j].GetPosition().y;
					int enemyship2_size_x = m_EnemyShip[j].GetSize().x;
					int enemyship2_size_y = m_EnemyShip[j].GetSize().y;

					int enemyShipLower_x = enemyship2_x - 5;
					int enemyShipHigher_x = enemyship2_x + 5;

					int enemyShipLower_y = enemyship2_y - 5;
					int enemyShipHigher_y = enemyship2_y + 5;

					bool inside = false;

					//if(m_EnemyShip[i].Active() && m_EnemyShip[i].Collides(m_EnemyShip[j].GetCurrentSprite()))



					if ( enemyship1_x > enemyShipLower_x && enemyShipHigher_x > enemyship1_x)
					{
						if (enemyShipLower_y < enemyship1_y && enemyship1_y < enemyShipHigher_y)
						{
							int randomWidth = rand() % SCREEN_WIDTH + 40;
							int randomHeight = rand() % (SCREEN_HEIGHT - 2) + 2;

							Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
							m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
						}
					}

					*/

					/*if (enemyship1_x >((enemyship2_x - enemyship2_size_x) - 5) && enemyship1_x < ((enemyship2_x + enemyship2_size_x) + 5))
					{
						if (enemyship1_y > ((enemyship2_y - enemyship2_size_y) -5) && enemyship1_y < ((enemyship2_y + enemyship2_size_y) + 5))
						{
							int randomWidth = rand() % 500 + (500 + SCREEN_WIDTH);
							int randomHeight = rand() % (SCREEN_HEIGHT - 2) + 2;

							Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
							m_EnemyShip[i].SetPosition(enemyShipSpawnPos);
						}
					}
					*/
					
	/*for (int i = 0; i < NUM_INVADERS_PER_ROW; i++) {
		for (int j = 1; j < NUM_INVADERS_PER_ROW; j++)
		{
			// collision x-axis?
			bool collisionX = m_EnemyShip[i].GetPosition().x + m_EnemyShip[i].GetSize().x >= m_EnemyShip[j].GetPosition().x &&
				m_EnemyShip[j].GetPosition().x + m_EnemyShip[j].GetSize().x >= m_EnemyShip[i].GetPosition().x;
			// collision y-axis?
			bool collisionY = m_EnemyShip[i].GetPosition().y + m_EnemyShip[i].GetSize().y >= m_EnemyShip[j].GetPosition().y &&
				m_EnemyShip[j].GetPosition().y + m_EnemyShip[j].GetSize().y >= m_EnemyShip[j].GetPosition().y;
			// collision only if on both axes
			if (collisionY && collisionX)
			{
				int randomWidth = rand() % SCREEN_WIDTH + 40;
				int randomHeight = rand() % (SCREEN_HEIGHT - 2) + 2;

				Vector2 enemyShipSpawnPos(randomWidth, randomHeight);
				m_EnemyShip[j].SetPosition(enemyShipSpawnPos);
			}
		}
	}*/
					
	



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


bool EnemyArmy::Collides(Sprite& otherSprite)
{
	bool collision = false;

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		if (m_EnemyShip[i].Active() && otherSprite.Collides(m_EnemyShip[i].GetCurrentSprite()))
		{
			collision = true;

		}
	}

	for (int i = 0; i < NUM_INVADERS_PER_ROW; i++)
	{

		if (m_EnemyShip[i].Active() && otherSprite.Collides(m_EnemyShip[i].GetCurrentSprite()))
		{
			collision = true;
			
			m_EnemyShip[i].Explode();


				if (m_EnemyShip[i].GetAnimationFrame() == 3)
				{
					m_ScoreEarned += m_EnemyShip[i].GetScoreValue();
					int randomWidth = rand() % 500 + SCREEN_WIDTH;
					int randomHeight = rand() % 92 + 10;

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
