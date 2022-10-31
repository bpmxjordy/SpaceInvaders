#ifndef _GAME_H_
#define _GAME_H

#include "GameStates.h"
#include "GameObjects\PlayerShip.h"
#include "GameObjects\EnemyArmy.h"
#include "GameObjects\Missile.h"
#include "../Core/Renderer/Sprite.h"
#include "GameObjects\ScoreDisplay.h"
#include <vector>
#include<fstream>
#include <string>



class ASCIIRenderer;



class Game
{
	

public:
	int difficultyFireRate = 5;
	Game();
	~Game();

	void Initialise();

	void Run();

	void AddEnemyMissile(Missile* pMissile);

private:

	void InitialiseRenderer();
	void Update();
	void Render();
	void UpdateScoreDisplay();

	void InitialiseMainMenu();
	void InitialiseGame();
	void InitialiseEndScreens();

	void UpdateMainMenu();
	void InitialiseDiffScreen();
	void UpdateDiff();
	void UpdateScreenSize();
	void InitialiseScreenScreen();
	void UpdateGame();

	void UpdatePlayerMissiles();
	void UpdateEnemyMissiles();

	void CheckWinConditions();

	void FireMissile();

	void UpdateEndGameScreens();

	void RenderMainMenu();
	void RenderDiff();
	void RenderScreenSize();
	void RenderGame();
	void RenderWinScreen();
	void RenderLoseScreen();

	void RenderEnemyMissiles();
	void RenderScore();
	void RenderLives();

	ASCIIRenderer* m_pRenderer;

	E_GAME_STATE m_GameState;

	bool m_bInitialised;
	bool m_bExitApp;

	int m_Score;
	int m_HighScoreInt;
	std::string m_HighScore;

	int difficultyScore = 999;

	int lives = 3;

	int enemiesRemaining = 50;

	int menuCounter = 0;
	int SizeMenuCounter = 0;

	PlayerShip m_PlayerShip;
	EnemyArmy m_EnemyArmy;

	Missile m_Missile; //player missile
	std::vector<Missile*> m_EnemyMissiles;

	ScoreDisplay m_ScoreDigit[5];

	ScoreDisplay m_LivesDigit[1];

	ScoreDisplay m_EnemiesDigit[3];

	bool missileActive = false;

	Sprite m_GameTitle;
	Sprite m_StartGameTitle;
	Sprite m_LogoTitle;
	Sprite m_DiffGameTitle;
	Sprite m_HighScoreTitle;

	Sprite m_FirstDiffMenuSize;
	Sprite m_SecondDiffMenuSize;
	Sprite m_ThirdDiffMenuSize;
	Sprite m_ExitGameTitle;
	int m_MainMenuCounter;

	Sprite m_GameOverTitle;
	int m_EndScreenCounter;

	Sprite m_YouWinTitle;

	char menuState;
	bool canPress = false;

};


#endif
