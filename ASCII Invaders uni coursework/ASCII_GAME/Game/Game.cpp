#include "Game.h"
#include <windows.h>
#include <iostream>
#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"
#include <fstream>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 96;

#define VK_UP		0x26
#define VK_DOWN		0x28
#define VK_SPACE	0x20    

#define VK_1		0x31
#define VK_2		0x32
#define VK_3		0x33
#define VK_4		0x34




char* GameTitleSprite = "                                                                                                                                                                            dddddddd                                                                        AAA                 SSSSSSSSSSSSSSS         CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIII                                                                 d::::::d                                                                       A:::A              SS:::::::::::::::S     CCC::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                      A:::::A            S:::::SSSSSS::::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                     A:::::::A           S:::::S     SSSSSSS  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::II                                                                 d:::::d                                                                     A:::::::::A          S:::::S             C:::::C       CCCCCC  I::::I    I::::I         I::::Innnn  nnnnnnnn vvvvvvv           vvvvvvvaaaaaaaaaaaaa      ddddddddd:::::d     eeeeeeeeeeee    rrrrr   rrrrrrrrr       ssssssssss             A:::::A:::::A         S:::::S            C:::::C                I::::I    I::::I         I::::In:::nn::::::::nnv:::::v         v:::::v a::::::::::::a   dd::::::::::::::d   ee::::::::::::ee  r::::rrr:::::::::r    ss::::::::::s           A:::::A A:::::A         S::::SSSS         C:::::C                I::::I    I::::I         I::::In::::::::::::::nnv:::::v       v:::::v  aaaaaaaaa:::::a d::::::::::::::::d  e::::::eeeee:::::eer:::::::::::::::::r ss:::::::::::::s         A:::::A   A:::::A         SS::::::SSSSS    C:::::C                I::::I    I::::I         I::::Inn:::::::::::::::nv:::::v     v:::::v            a::::ad:::::::ddddd:::::d e::::::e     e:::::err::::::rrrrr::::::rs::::::ssss:::::s       A:::::A     A:::::A          SSS::::::::SS  C:::::C                I::::I    I::::I         I::::I  n:::::nnnn:::::n v:::::v   v:::::v      aaaaaaa:::::ad::::::d    d:::::d e:::::::eeeee::::::e r:::::r     r:::::r s:::::s  ssssss       A:::::AAAAAAAAA:::::A            SSSSSS::::S C:::::C                I::::I    I::::I         I::::I  n::::n    n::::n  v:::::v v:::::v     aa::::::::::::ad:::::d     d:::::d e:::::::::::::::::e  r:::::r     rrrrrrr   s::::::s           A:::::::::::::::::::::A                S:::::SC:::::C                I::::I    I::::I         I::::I  n::::n    n::::n   v:::::v:::::v     a::::aaaa::::::ad:::::d     d:::::d e::::::eeeeeeeeeee   r:::::r                  s::::::s       A:::::AAAAAAAAAAAAA:::::A               S:::::S C:::::C       CCCCCC  I::::I    I::::I         I::::I  n::::n    n::::n    v:::::::::v     a::::a    a:::::ad:::::d     d:::::d e:::::::e            r:::::r            ssssss   s:::::s    A:::::A             A:::::A  SSSSSSS     S:::::S  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::IIn::::n    n::::n     v:::::::v      a::::a    a:::::ad::::::ddddd::::::dde::::::::e           r:::::r            s:::::ssss::::::s  A:::::A               A:::::A S::::::SSSSSS:::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n      v:::::v       a:::::aaaa::::::a d:::::::::::::::::d e::::::::eeeeeeee   r:::::r            s::::::::::::::s  A:::::A                 A:::::AS:::::::::::::::SS      CCC::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n       v:::v         a::::::::::aa:::a d:::::::::ddd::::d  ee:::::::::::::e   r:::::r             s:::::::::::ss  AAAAAAA                   AAAAAAASSSSSSSSSSSSSSS           CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIIInnnnnn    nnnnnn        vvv           aaaaaaaaaa  aaaa  ddddddddd   ddddd    eeeeeeeeeeeeee   rrrrrrr              sssssssssss    ";
char* GameOverSprite = "Y88b   d88P                   888                                   888     Y88b d88P                    888                                   888      Y88o88P                     888                                   888       Y888P  .d88b.  888  888    888      .d88b.  .d8888b   .d88b.     888        888  d88''88b 888  888    888     d88''88b 88K      d8P  Y8b    888        888  888  888 888  888    888     888  888 'Y8888b. 88888888    Y8P        888  Y88..88P Y88b 888    888     Y88..88P      X88 Y8b.         '         888   'Y88P'   'Y88888    88888888 'Y88P'   88888P'  'Y8888     888   ";
/*
Y88b   d88P                   888                                   888   
 Y88b d88P                    888                                   888   
  Y88o88P                     888                                   888   
   Y888P  .d88b.  888  888    888      .d88b.  .d8888b   .d88b.     888   
    888  d88""88b 888  888    888     d88""88b 88K      d8P  Y8b    888   
    888  888  888 888  888    888     888  888 "Y8888b. 88888888    Y8P   
    888  Y88..88P Y88b 888    888     Y88..88P      X88 Y8b.         "    
    888   "Y88P"   "Y88888    88888888 "Y88P"   88888P'  "Y8888     888   
                                                                                                                                            
 */

char* YouWinSprite = "Y88b   d88P                   888       888 d8b             888   Y88b d88P                    888   o   888 Y8P             888    Y88o88P                     888  d8b  888                 888     Y888P  .d88b.  888  888    888 d888b 888 888 88888b.     888      888  d88''88b 888  888    888d88888b888 888 888 '88b    888      888  888  888 888  888    88888P Y88888 888 888  888    Y8P      888  Y88..88P Y88b 888    8888P   Y8888 888 888  888     '       888   'Y88P'   'Y88888    888P     Y888 888 888  888    888  ";
/*
Y88b   d88P                   888       888 d8b             888 
 Y88b d88P                    888   o   888 Y8P             888 
  Y88o88P                     888  d8b  888                 888 
   Y888P  .d88b.  888  888    888 d888b 888 888 88888b.     888 
    888  d88''88b 888  888    888d88888b888 888 888 '88b    888 
    888  888  888 888  888    88888P Y88888 888 888  888    Y8P 
    888  Y88..88P Y88b 888    8888P   Y8888 888 888  888     '  
    888   'Y88P'   "Y88888    888P     Y888 888 888  888    888 
*/

char* StartGameSprite = "         __             __       _____/ /_____ ______/ /_     / ___/ __/ __ `/ ___/ __/    /__  / /_/ /_/ / /  / /_     _____/\\__/\\__,_/_/   \\\__/  ";


//         __             __ 
//   _____/ /_____ ______/ /_
//  / ___/ __/ __ `/ ___/ __/
// (__  ) /_/ /_/ / /  / /_  
///____/\__/\__,_/_/   \__/  
                           

                           
char* DiffGameSprite = "       ___ _________            ____                ____/ (_) __/ __(_)______  __/ / /___  __        / __  / / /_/ /_/ / ___/ / / / / __/ / / /       / /_/ / / __/ __/ / /__/ /_/ / / /_/ /_/ /        \\__,_/_/_/ /_/ /_/\\___/\\__,_/_/\\__/\\__, /                                           /____/   ";
   
//       ___ _________            ____       
//  ____/ (_) __/ __(_)______  __/ / /___  __
// / __  / / /_/ /_/ / ___/ / / / / __/ / / /
/// /_/ / / __/ __/ / /__/ /_/ / / /_/ /_/ / 
//\__,_/_/_/ /_/ /_/\___/\__,_/_/\__/\__, /  
//                                  /____/   


char* SizeSprite = "    __    _       __                                 / /_  (_)___ _/ /_  ______________  ________     / __ \\/ / __ `/ __ \\/ ___/ ___/ __ \\/ ___/ _ \\   / / / / / /_/ / / / (__  ) /__/ /_/ / /  /  __/  /_/ /_/_/\\__, /_/ /_/____/\\___/\\____/_/   \\___/           /____/                                  ";
	  

/*
    __    _       __                            
   / /_  (_)___ _/ /_  ______________  ________ 
  / __ \/ / __ `/ __ \/ ___/ ___/ __ \/ ___/ _ \
 / / / / / /_/ / / / (__  ) /__/ /_/ / /  /  __/
/_/ /_/_/\__, /_/ /_/____/\___/\____/_/   \___/ 
        /____/                                  
*/
                                                      

                                               
                                               

char* ExitGameSprite = "             _ __     ___  _  __(_) /_   / _ \\| |/_/ / __/  /  __/>  </ / /_    \\___/_/|_/_/\\__/  ";
									 
//             _ __ 
//  ___  _  __(_) /_
// / _ \| |/_/ / __/
///  __/>  </ / /_  
//\___/_/|_/_/\__/  


char* FirstDiffSprite = "    ______                       / ____/___ ________  __      / __/ / __ `/ ___/ / / /     / /___/ /_/ (__  ) /_/ /     /_____/\\__,_/____/\\__, /                       /____/		";


//    ______                
//   / ____/___ ________  __
//  / __/ / __ `/ ___/ / / /
// / /___/ /_/ (__  ) /_/ / 
///_____/\__,_/____/\__, /  
//                 /____/		


char* SecondDiffSprite = "    __  ___         ___                    /  |/  /__  ____/ (_)_  ______ ___     / /|_/ / _ \\/ __  / / / / / __ `__ \\   / /  / /  __/ /_/ / / /_/ / / / / / /  /_/  /_/\\___/\\__,_/_/\\__,_/_/ /_/ /_/ ";


//    __  ___         ___               
//   /  |/  /__  ____/ (_)_  ______ ___ 
//  / /|_/ / _ \/ __  / / / / / __ `__ \
// / /  / /  __/ /_/ / / /_/ / / / / / /
///_/  /_/\___/\__,_/_/\__,_/_/ /_/ /_/ 
                                      

char* ThirdDiffSprite = "    ______          ____                   / ____/___  ____/ / /__  __________    / __/ / __ \\/ __  / / _ \\/ ___/ ___/   / /___/ / / / /_/ / /  __(__  |__  )   /_____/_/ /_/\\__,_/_/\\___/____/____/";


/*
    ______          ____              
   / ____/___  ____/ / /__  __________
  / __/ / __ \/ __  / / _ \/ ___/ ___/
 / /___/ / / / /_/ / /  __(__  |__  ) 
/_____/_/ /_/\__,_/_/\___/____/____/  
 */                                     

                           

char* MainMenuLogo = "      :::::::::  :::::::::  ::::::::::: :::::::::: ::::::::::: ::::::::::: ::::    :::  ::::::::        +:+    +:+ +:+    +:+     +:+     +:+            +:+         +:+     :+:+:+  +:+ +:+                +:+    +:+ +:+    +:+     +:+     +:+            +:+         +:+     :+:+:+  +:+ +:+               +#+    +:+ +#++:++#:      +#+     :#::+::#       +#+         +#+     +#+ +:+ +#+ :#:               +#+    +#+ +#+    +#+     +#+     +#+            +#+         +#+     +#+  +#+#+# +#+   +#+#        #+#    #+# #+#    #+#     #+#     #+#            #+#         #+#     #+#   #+#+# #+#    #+#        #########  ###    ### ########### ###            ###     ########### ###    ####  ########                         ::::::::::: :::    ::: :::::::::   ::::::::  :::    :::  ::::::::  :::    :::                          :+:     :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+:                         +#+     +#++:++#++ +#++:++#:  +#+    +:+ +#+    +:+ :#:        +#++:++#++                           +#+     +#++:++#++ +#++:++#:  +#+    +:+ +#+    +:+ :#:        +#++:++#++                          +#+     +#+    +#+ +#+    +#+ +#+    +#+ +#+    +#+ +#+   +#+# +#+    +#+                          #+#     #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+#                          ###     ###    ### ###    ###  ########   ########   ########  ###    ###                                      :::   :::       ::: ::::::::::: ::::::::::: :::::::::: :::::::::                                  :+:+: :+:+:    :+: :+:   :+:         :+:     :+:        :+:    :+:                                +:+ +:+:+ +:+  +:+   +:+  +:+         +:+     +:+        +:+    +:+                                +#+  +:+  +#+ +#++:++#++: +#+         +#+     +#++:++#   +#++:++#:                                 +#+       +#+ +#+     +#+ +#+         +#+     +#+        +#+    +#+                                #+#       #+# #+#     #+# #+#         #+#     #+#        #+#    #+#                                ###       ### ###     ### ###         ###     ########## ###    ###        ";




/*
      :::::::::  :::::::::  ::::::::::: :::::::::: ::::::::::: ::::::::::: ::::    :::  ::::::::  
     :+:    :+: :+:    :+:     :+:     :+:            :+:         :+:     :+:+:   :+: :+:    :+:  
    +:+    +:+ +:+    +:+     +:+     +:+            +:+         +:+     :+:+:+  +:+ +:+          
   +#+    +:+ +#++:++#:      +#+     :#::+::#       +#+         +#+     +#+ +:+ +#+ :#:           
  +#+    +#+ +#+    +#+     +#+     +#+            +#+         +#+     +#+  +#+#+# +#+   +#+#     
 #+#    #+# #+#    #+#     #+#     #+#            #+#         #+#     #+#   #+#+# #+#    #+#      
#########  ###    ### ########### ###            ###     ########### ###    ####  ########        
               ::::::::::: :::    ::: :::::::::   ::::::::  :::    :::  ::::::::  :::    :::      
                  :+:     :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+:       
                 +:+     +:+    +:+ +:+    +:+ +:+    +:+ +:+    +:+ +:+        +:+    +:+        
                +#+     +#++:++#++ +#++:++#:  +#+    +:+ +#+    +:+ :#:        +#++:++#++         
               +#+     +#+    +#+ +#+    +#+ +#+    +#+ +#+    +#+ +#+   +#+# +#+    +#+          
              #+#     #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+#           
             ###     ###    ### ###    ###  ########   ########   ########  ###    ###            
                                 :::   :::       ::: ::::::::::: ::::::::::: :::::::::: ::::::::: 
                               :+:+: :+:+:    :+: :+:   :+:         :+:     :+:        :+:    :+: 
                             +:+ +:+:+ +:+  +:+   +:+  +:+         +:+     +:+        +:+    +:+  
                            +#+  +:+  +#+ +#++:++#++: +#+         +#+     +#++:++#   +#++:++#:    
                           +#+       +#+ +#+     +#+ +#+         +#+     +#+        +#+    +#+    
                          #+#       #+# #+#     #+# #+#         #+#     #+#        #+#    #+#     
                         ###       ### ###     ### ###         ###     ########## ###    ###      
    
                                                         */



char* OneLivesSprite = "██   ██    ██ ██      ███      ██ ██    ██   ██   ";

char* TwoLivesSprite = "██   ██    ██ ██      ███      ██ ██    ██   ██   ";

char* ThreeLivesSprite = "██   ██    ██ ██      ███      ██ ██    ██   ██   ";



//██   ██
// ██ ██  
//  ███   
// ██ ██  
//██   ██
        
        

                           
                           

                  
                  



Game::Game()
:m_pRenderer(NULL)
, m_GameState(E_GAME_STATE_MAIN_MENU)
, m_bInitialised(false)
, m_bExitApp(false)
, m_Score(0)
, m_MainMenuCounter(0)
, m_EndScreenCounter(0)
{
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise()														//For initialising all the functions in the game
{
	InitialiseRenderer();

	InitialiseMainMenu();

	InitialiseGame();

	InitialiseEndScreens();

	m_bInitialised = true;

	std::ifstream HighScoreFile("HighScore.txt");					//opens the text file for the highscore

	HighScoreFile >> m_HighScore;											//Reads the high score and inserts the value into the "m_HighScore" variable"

	HighScoreFile.close();			

	m_HighScoreInt = std::stoi(m_HighScore);								//Converts the highscore into a integer so its ready to be used in game
}

void Game::InitialiseRenderer()												//Starts the window renderer
{
	m_pRenderer = new ASCIIRenderer();

	m_pRenderer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);


	
}

void Game::InitialiseMainMenu()																			//The function that will initialise the different items in the menu
{
	Vector2 LogoTitleSize(100, 21);																//Setting the vector2 values to how big i want the sprite to be(Characters, lines)
	m_LogoTitle.Initialise(MainMenuLogo, FOREGROUND_BRIGHT_RED, LogoTitleSize);				//This will initialise the ASCII sprite, in the vector2 size, in the colour BRIGHT RED

	Vector2 LogoPosition(80, 25);																	//Setting this vector2 to the position i want the sprite to appear
	m_LogoTitle.SetPosition(LogoPosition);															//Setting the sprites position to the vector2 co-ordinates 
	
	Vector2 StartGameTitleSize(30, 5);
	m_StartGameTitle.Initialise(StartGameSprite, FOREGROUND_BLUE, StartGameTitleSize);

	Vector2 StartGamePosition(115, 57);
	m_StartGameTitle.SetPosition(StartGamePosition);

	Vector2 DiffGameTitleSize(50, 6);
	m_DiffGameTitle.Initialise(DiffGameSprite, FOREGROUND_BLUE, DiffGameTitleSize);

	Vector2 DiffGamePosition(107, 64);
	m_DiffGameTitle.SetPosition(DiffGamePosition);

	Vector2 HighScoreTitleSize(50, 6);
	m_HighScoreTitle.Initialise(SizeSprite, FOREGROUND_BLUE, HighScoreTitleSize);

	Vector2 HighScoreTitlePosition(102, 71);
	m_HighScoreTitle.SetPosition(HighScoreTitlePosition);

	Vector2 ExitGameTitleSize(20, 5);
	m_ExitGameTitle.Initialise(ExitGameSprite, FOREGROUND_BLUE, ExitGameTitleSize);

	Vector2 ExitGameTitlePosition(118, 78);
	m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
}

void Game::InitialiseGame()																						//This is used to initialise all the parts of the actual game(Player ship, score digits and the missile initialisation)
{

	Vector2 ExitGameTitleSize(20, 5);
	m_ExitGameTitle.Initialise(ExitGameSprite, FOREGROUND_BRIGHT_RED, ExitGameTitleSize);

	Vector2 ExitGameTitlePosition(118, 78);
	m_ExitGameTitle.SetPosition(ExitGameTitlePosition);

	//Game
	m_PlayerShip.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8), VK_UP, VK_DOWN);

	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Initialise(Vector2(120 + (i * 10), 10));
	}

	m_EnemyArmy.Initialise(this);

	m_Missile.Initialise(Vector2(m_PlayerShip.GetPosition().x + (m_PlayerShip.GetSize().x * 0.5f), m_PlayerShip.GetPosition().y - 2), Vector2(0, -MISSILE_SPEED));
	m_Missile.SetActive(false);


	
}

void Game::InitialiseEndScreens()																			//This is used to initialise the end screen sprites
{
	//End Game Screen
	Vector2 gameOverTitleSize(75, 8);
	m_GameOverTitle.Initialise(GameOverSprite, FOREGROUND_SKYPINK, gameOverTitleSize);

	Vector2 gameOverPosition(93, 40);
	m_GameOverTitle.SetPosition(gameOverPosition);


	Vector2 youWinTitleSize(65, 8);
	m_YouWinTitle.Initialise(YouWinSprite, FOREGROUND_SKYPINK, youWinTitleSize);

	Vector2 youWinPosition(98, 40);
	m_YouWinTitle.SetPosition(youWinPosition);
}

void Game::Run()																							//This is used to call the update and render functions
{
	while (!m_bExitApp)
	{
		Update();

		Render();

		Sleep(30);
	}
}

void Game::Update()																							//This is the function that updates the game as we play and call different functions when needed
{
	if (GetKeyState(VK_ESCAPE) < 0)																			//If the escape key is pressed the game will close
	{
		m_bExitApp = true;
		return;
	}
		
	switch (m_GameState)																					//This calls functions based on the "m_GameState" status. Makes the game swap between menu, in-game and end screens
	{
		case E_GAME_STATE_MAIN_MENU:
		{
			UpdateMainMenu();
		}
		break;

		case E_GAME_STATE_DIFF_MENU:
		{
			UpdateDiff();
		}
		break;

		case E_GAME_STATE_SSIZE_MENU:
		{
			UpdateScreenSize();
		}
		break;

		case E_GAME_STATE_IN_GAME:
		{
			UpdateGame();				
		}
		break;

		case E_GAME_STATE_WIN_GAME: //fall through
		case E_GAME_STATE_LOSE_GAME:
		{
			UpdateEndGameScreens();
		}
		break;

		default:
		{
		}
	}
}

void Game::UpdateMainMenu()																							//This function is what allows the user to select different menu items and move through the menu screens
{
	Vector2 StartGameTitleSize(30, 5);
	m_StartGameTitle.Initialise(StartGameSprite, FOREGROUND_SKYPINK, StartGameTitleSize);

	Vector2 StartGamePosition(115, 57);
	m_StartGameTitle.SetPosition(StartGamePosition);
		if (GetAsyncKeyState(VK_1))																					//These detect what button the user is pressing down and then performs the relevant task
		{
			
			menuCounter = 1;
		}
	
		if (GetAsyncKeyState(VK_2))
		{
			
			menuCounter = 2;
		}

		if (GetAsyncKeyState(VK_3))
		{
			
			menuCounter = 3;
		}

		if (GetAsyncKeyState(VK_4))
		{
			
			menuCounter = 4;
		}

		
		if (menuCounter == 1) {																		//This performs all the following tasks when the user has pressed number 1

			if (GetKeyState(VK_SPACE)) {
				m_GameState = E_GAME_STATE_IN_GAME;
			}

			Vector2 StartGamePosition(120, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);

			Vector2 DiffGamePosition(107, 64);
			m_DiffGameTitle.SetPosition(DiffGamePosition);

			Vector2 HighScoreTitlePosition(102, 71);
			m_HighScoreTitle.SetPosition(HighScoreTitlePosition);

			Vector2 ExitGameTitlePosition(118, 78);
			m_ExitGameTitle.SetPosition(ExitGameTitlePosition);

		}

		if (menuCounter == 2) {
			
			if (GetKeyState(VK_SPACE)) {
				m_GameState = E_GAME_STATE_DIFF_MENU;
			}
			Vector2 StartGamePosition(115, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);

			Vector2 DiffGamePosition(112, 64);
			m_DiffGameTitle.SetPosition(DiffGamePosition);

			Vector2 HighScoreTitlePosition(102, 71);
			m_HighScoreTitle.SetPosition(HighScoreTitlePosition);

			Vector2 ExitGameTitlePosition(118, 78);
			m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
		}

		if (menuCounter == 3) {
			
			Vector2 StartGamePosition(115, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);

			Vector2 DiffGamePosition(107, 64);
			m_DiffGameTitle.SetPosition(DiffGamePosition);

			Vector2 HighScoreTitlePosition(106, 71);
			m_HighScoreTitle.SetPosition(HighScoreTitlePosition);

			Vector2 ExitGameTitlePosition(118, 78);
			m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
				if (GetKeyState(VK_SPACE)) {
					m_GameState = E_GAME_STATE_SSIZE_MENU;
					canPress == false;
					SizeMenuCounter = 1;
					menuCounter = 07;

					Vector2 FirstDiffMenuPosition(300, 56);
					m_FirstDiffMenuSize.SetPosition(FirstDiffMenuPosition);
					m_SecondDiffMenuSize.SetPosition(FirstDiffMenuPosition);
					m_ThirdDiffMenuSize.SetPosition(FirstDiffMenuPosition);
				}
			
			
			
		}

		if (menuCounter == 4) {
			
			Vector2 StartGamePosition(115, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);

			Vector2 DiffGamePosition(107, 64);
			m_DiffGameTitle.SetPosition(DiffGamePosition);

			Vector2 HighScoreTitlePosition(102, 71);
			m_HighScoreTitle.SetPosition(HighScoreTitlePosition);

			Vector2 ExitGameTitlePosition(123, 78);
			m_ExitGameTitle.SetPosition(ExitGameTitlePosition);

			if (GetKeyState(VK_SPACE)) {
				m_bExitApp = true;
			}
		}
	
}

void Game::UpdateDiff()
{
	Vector2 FirstDiffMenuSize(30, 6);
	m_SecondDiffMenuSize.Initialise(FirstDiffSprite, FOREGROUND_SKYPINK, FirstDiffMenuSize);

	Vector2 FirstDiffMenuPosition(118, 56);
	m_SecondDiffMenuSize.SetPosition(FirstDiffMenuPosition);

	Vector2 SecondDiffMenuSize(40, 5);
	m_FirstDiffMenuSize.Initialise(SecondDiffSprite, FOREGROUND_SKYPINK, SecondDiffMenuSize);

	Vector2 SecondDiffMenuPosition(110, 63);
	m_FirstDiffMenuSize.SetPosition(SecondDiffMenuPosition);

	Vector2 ThirdDiffSize(40, 5);
	m_ThirdDiffMenuSize.Initialise(ThirdDiffSprite, FOREGROUND_SKYPINK, ThirdDiffSize);

	Vector2 ThirdDiffMenuPosition(110, 70);;
	m_ThirdDiffMenuSize.SetPosition(ThirdDiffMenuPosition);

	

	if (GetAsyncKeyState(VK_1))
	{
		SizeMenuCounter = 1;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_2))
	{
		SizeMenuCounter = 2;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_3))
	{
		SizeMenuCounter = 3;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_4))
	{
		SizeMenuCounter = 4;
		canPress = true;
	}

	if (SizeMenuCounter == 1) {

		if (GetAsyncKeyState(VK_SPACE)) {
			difficultyScore = 999;																		//Setting the difficulty score to the corresponding difficulty
		}

		Vector2 FirstDiffMenuPosition(122, 56);
		m_SecondDiffMenuSize.SetPosition(FirstDiffMenuPosition);

		Vector2 SecondDiffMenuPosition(110, 63);
		m_FirstDiffMenuSize.SetPosition(SecondDiffMenuPosition);

		Vector2 ThirdDiffMenuPosition(110, 70);
		m_ThirdDiffMenuSize.SetPosition(ThirdDiffMenuPosition);

		Vector2 ExitGameTitlePosition(118, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);

		

	}

	if (SizeMenuCounter == 2) {

		if (GetAsyncKeyState(VK_SPACE)) {
			difficultyScore = 4999;
			enemiesRemaining = 250;																//Setting the enemies remaining to the corresponding difficulty
		}
		Vector2 FirstDiffMenuPosition(118, 56);
		m_SecondDiffMenuSize.SetPosition(FirstDiffMenuPosition);

		Vector2 SecondDiffMenuPosition(114, 63);
		m_FirstDiffMenuSize.SetPosition(SecondDiffMenuPosition);

		Vector2 ThirdDiffMenuPosition(110, 70);
		m_ThirdDiffMenuSize.SetPosition(ThirdDiffMenuPosition);

		Vector2 ExitGameTitlePosition(118, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
	}

	if (SizeMenuCounter == 3) {

		if (GetAsyncKeyState(VK_SPACE)) {
			difficultyScore = 9999999;
		}

		Vector2 FirstDiffMenuPosition(118, 56);
		m_SecondDiffMenuSize.SetPosition(FirstDiffMenuPosition);

		Vector2 SecondDiffMenuPosition(110, 63);
		m_FirstDiffMenuSize.SetPosition(SecondDiffMenuPosition);

		Vector2 ThirdDiffMenuPosition(114, 70);
		m_ThirdDiffMenuSize.SetPosition(ThirdDiffMenuPosition);

		Vector2 ExitGameTitlePosition(118, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
	}

	if (SizeMenuCounter == 4) {

		Vector2 ExitGameTitlePosition(123, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);

		if (GetAsyncKeyState(VK_SPACE)) {
			Vector2 StartGameTitleSize(30, 5);
			m_StartGameTitle.Initialise(StartGameSprite, FOREGROUND_SKYPINK, StartGameTitleSize);

			Vector2 StartGamePosition(115, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);
			m_GameState = E_GAME_STATE_MAIN_MENU;

			canPress == false;
			SizeMenuCounter = 1;
			menuCounter = 07;

			Vector2 FirstSizeMenuSize(500, 57);
			m_FirstDiffMenuSize.SetPosition(FirstSizeMenuSize);

		}



	}
}

void Game::UpdateScreenSize()
{
	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Initialise(Vector2(115 + (i * 10), 10));											//This is used to initialise all the score digit displays
	}

	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Update(0.0f);																			//This is used to update the score digits
	}

	int ScoreValues[4];

	ScoreValues[3] = m_HighScoreInt > 9999 ? 9 : m_HighScoreInt % 10;													//This is separating each individual digit and assigning it to the array
	ScoreValues[2] = m_HighScoreInt > 9999 ? 9 : m_HighScoreInt / 10 % 10;
	ScoreValues[1] = m_HighScoreInt > 9999 ? 9 : m_HighScoreInt / 100 % 10;
	ScoreValues[0] = m_HighScoreInt > 9999 ? 9 : m_HighScoreInt / 1000 % 10;

	m_ScoreDigit[0].SetDigitValue(ScoreValues[0]);																		//Setting the score digits display to the individual numbers in the array
	m_ScoreDigit[1].SetDigitValue(ScoreValues[1]);
	m_ScoreDigit[2].SetDigitValue(ScoreValues[2]);
	m_ScoreDigit[3].SetDigitValue(ScoreValues[3]);

	Vector2 ExitGameTitlePosition(118, 78);
	m_ExitGameTitle.SetPosition(ExitGameTitlePosition);


	if (GetAsyncKeyState(VK_1))
	{
		SizeMenuCounter = 1;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_2))
	{
		SizeMenuCounter = 2;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_3))
	{
		SizeMenuCounter = 3;
		canPress = true;
	}

	if (GetAsyncKeyState(VK_4))
	{
		SizeMenuCounter = 4;
		canPress = true;
	}


	if (SizeMenuCounter == 1) {

		if (GetAsyncKeyState(VK_SPACE)) {
			//----------------------------- change difficulty --------------------------------------//
		}

		

		Vector2 ExitGameTitlePosition(118, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);



	}

	if (SizeMenuCounter == 2) {

		if (GetAsyncKeyState(VK_SPACE)) {
			Vector2 StartGameTitleSize(30, 5);
			m_StartGameTitle.Initialise(StartGameSprite, FOREGROUND_SKYPINK, StartGameTitleSize);

			Vector2 StartGamePosition(115, 57);
			m_StartGameTitle.SetPosition(StartGamePosition);
			m_GameState = E_GAME_STATE_MAIN_MENU;
			SizeMenuCounter = 1;

			Vector2 FirstSizeMenuSize(500, 57);
			m_FirstDiffMenuSize.SetPosition(FirstSizeMenuSize);
		}

		Vector2 ExitGameTitlePosition(122, 78);
		m_ExitGameTitle.SetPosition(ExitGameTitlePosition);
	}
}

void Game::UpdateGame()														//This is used to call all the functions when the updateGame function is called
{
	if (GetKeyState(VK_SPACE) < 0)
	{
		if (missileActive == false)
		{
			FireMissile();													//if there arent any missiles active this will allow the player to fire another missile
		}
	}
	m_PlayerShip.Update();
	m_EnemyArmy.Update();
	UpdatePlayerMissiles();
	UpdateEnemyMissiles();
	UpdateScoreDisplay();
	CheckWinConditions();
}

void Game::FireMissile()
{
	m_Missile.SetPosition(m_PlayerShip.GetPosition().x, m_PlayerShip.GetPosition().y + (m_PlayerShip.GetSize().y - 5));		//This is setting the missiles position to the player and assigning it a velocity
	m_Missile.SetActive();
	missileActive = true;													//Setting this bool to active so the player cant fire another missile
}

void Game::UpdatePlayerMissiles()
{
	m_Missile.Update();

	if (m_Missile.GetPosition().x < 0 || m_Missile.GetPosition().x > SCREEN_WIDTH)				//Checking if the missile has reached the edge of the screen
	{
		m_Missile.Explode();																	//if the missile has reached the end of the screen then the missile will explode and be set to inactive
		missileActive = false;
	}

	if (m_Missile.Active() && m_EnemyArmy.Collides(m_Missile))								//Checking if the missile has collided with any enemy ships
	{
		m_Missile.Explode();
		missileActive = false;
		enemiesRemaining--;																		//if they have collided then the enemiesRemaining counter gets reduced
		m_Score += m_EnemyArmy.GetScore();														//The score of the enemy gets added to the score
																	//the missile gets set to inactive as its exploded
	}
	

}
 
void Game::UpdateEnemyMissiles()
{
	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		m_EnemyMissiles[i]->Update();															//updates the enemy missile
	}
  
	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		if (m_EnemyMissiles[i]->Active() && m_EnemyMissiles[i]->Collides(m_PlayerShip))		//checking if the enemy missile collides with the players ship 
		{
			//hit the player
			m_EnemyMissiles[i]->Explode();														//explodes and deactivates the enemy missile
			m_GameState = E_GAME_STATE_LOSE_GAME;												//takes the player to the lose screen 

			//Updating the highscore
			if(m_Score > m_HighScoreInt)														//Checking if the players score is higher than the highest score
			{
				std::ofstream ofs;
				ofs.open("HighScore.txt", std::ofstream::out | std::ofstream::trunc);		//opens the text file for writing and wipes the file clear

				ofs << m_Score;																			//Inputs the new highscore into the file
				ofs.close();
			}
		}
		if (m_EnemyMissiles[i]->Active() && m_EnemyMissiles[i]->GetPosition().y > SCREEN_HEIGHT)		//checking if the enemy missile reaches the edge of the screen
		{
			m_EnemyMissiles[i]->Explode();																// explodes it if it does
		}
	}
}

void Game::CheckWinConditions()	
{
	if (m_Score > difficultyScore)																		//checks if the player has reached the target score for the difficulty setting
	{

		if (m_Score > m_HighScoreInt)
		{
			std::ofstream ofs;
			ofs.open("HighScore.txt", std::ofstream::out | std::ofstream::trunc);

			ofs << m_Score;
			ofs.close();
		}
																										//player wins if the score is above 999
		m_GameState = E_GAME_STATE_WIN_GAME;


	}
	else if (m_EnemyArmy.HasLanded())																	//checking if the enemy ship has reached the players side
	{
		
		lives--;																						//takes away one life
		if (lives == 0) {																				//checking if the player has 0 lives left

			if (m_Score > m_HighScoreInt)																
			{
				std::ofstream ofs;
				ofs.open("HighScore.txt", std::ofstream::out | std::ofstream::trunc);

				ofs << m_Score;
				ofs.close();
			}

																										//player loses if 3 enemies have reached the left side
			m_GameState = E_GAME_STATE_LOSE_GAME;
		}
		
	}
}

void Game::UpdateEndGameScreens()
{
	m_EndScreenCounter++;

	if (m_EndScreenCounter > 90)																		//displays the end screen and then quits after a set amount of time
	{
		m_EndScreenCounter = 0;
		
		m_bExitApp = true;																				
	}
}

void Game::Render()																						//Used to call all the render functions based on the game state
{
	m_pRenderer->ClearScreen();	

	switch (m_GameState)
	{
		case E_GAME_STATE_MAIN_MENU:
		{
			RenderMainMenu();
		}
		break;

		case E_GAME_STATE_DIFF_MENU:
		{
			RenderDiff();
		}
		break;

		case E_GAME_STATE_SSIZE_MENU:
		{
			RenderScreenSize();
		}
		break;

		case E_GAME_STATE_IN_GAME:
		{
			RenderGame();
		}
		break;

		case E_GAME_STATE_WIN_GAME:
		{
			RenderWinScreen();
		}
		break;

		case E_GAME_STATE_LOSE_GAME:
		{
			RenderLoseScreen();
		}
		break;

		default:
		{
		}
	}

	//call this last
	m_pRenderer->Render();
}

void Game::RenderMainMenu()																		//These functions are all used to render different items and sprites
{
	m_StartGameTitle.Render(m_pRenderer);
	m_LogoTitle.Render(m_pRenderer);
	m_DiffGameTitle.Render(m_pRenderer);
	m_HighScoreTitle.Render(m_pRenderer);
	m_ExitGameTitle.Render(m_pRenderer);
	m_FirstDiffMenuSize.Render(m_pRenderer);
}

void Game::RenderDiff()
{
	m_FirstDiffMenuSize.Render(m_pRenderer);
	m_SecondDiffMenuSize.Render(m_pRenderer);
	m_ThirdDiffMenuSize.Render(m_pRenderer);
	m_ExitGameTitle.Render(m_pRenderer);
}

void Game::RenderScreenSize()
{
	m_pRenderer->ClearScreen();
	m_FirstDiffMenuSize.Render(m_pRenderer);
	m_SecondDiffMenuSize.Render(m_pRenderer);
	m_ThirdDiffMenuSize.Render(m_pRenderer);
	RenderScore();
	m_ExitGameTitle.Render(m_pRenderer);
}

void Game::RenderGame()
{
	m_PlayerShip.Render(m_pRenderer);
	m_EnemyArmy.Render(m_pRenderer);

	m_Missile.Render(m_pRenderer);

	RenderEnemyMissiles();

	RenderScore();
}

void Game::RenderEnemyMissiles()
{
	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		m_EnemyMissiles[i]->Render(m_pRenderer);
	}
}

void Game::RenderScore()
{
	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Render(m_pRenderer);
	}

	for (int i = 0; i < 3; i++)
	{
		m_EnemiesDigit[i].Render(m_pRenderer);
	}

	m_LivesDigit[0].Render(m_pRenderer);
}

void Game::RenderWinScreen()
{
	m_YouWinTitle.Render(m_pRenderer);
}

void Game::RenderLoseScreen()
{
	m_GameOverTitle.Render(m_pRenderer);
}

void Game::AddEnemyMissile(Missile* pMissile)
{
	m_EnemyMissiles.push_back(pMissile);
}

void Game::UpdateScoreDisplay()
{

	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Initialise(Vector2(120 + (i * 10), 10));
	}

	for (int i = 0; i < 3; i++)
	{
		m_EnemiesDigit[i].Initialise(Vector2(20 + (i * 10), 10));
	}

	for (int i = 0; i < 1; i++)
	{
		m_LivesDigit[i].Initialise(Vector2(240 + (i * 10), 10));
	}

	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Update(0.0f);
	}

	for (int i = 0; i < 1; i++)
	{
		m_LivesDigit[i].Update(0.0f);
	}

	int ScoreValues[4];
	int EnemiesValues[4];

	ScoreValues[3] = m_Score > 9999 ? 9 : m_Score % 10;
	ScoreValues[2] = m_Score > 9999 ? 9 : m_Score / 10 % 10;								//Making the digits show the score, lives and enemies remaining in game
	ScoreValues[1] = m_Score > 9999 ? 9 : m_Score / 100 % 10;
	ScoreValues[0] = m_Score > 9999 ? 9 : m_Score / 1000 % 10;

	EnemiesValues[2] = enemiesRemaining > 9999 ? 9 : enemiesRemaining % 10;
	EnemiesValues[1] = enemiesRemaining > 9999 ? 9 : enemiesRemaining / 10 % 10;
	EnemiesValues[0] = enemiesRemaining > 9999 ? 9 : enemiesRemaining / 100 % 10;

	m_ScoreDigit[0].SetDigitValue(ScoreValues[0]);
	m_ScoreDigit[1].SetDigitValue(ScoreValues[1]);
	m_ScoreDigit[2].SetDigitValue(ScoreValues[2]);
	m_ScoreDigit[3].SetDigitValue(ScoreValues[3]);

	m_EnemiesDigit[0].SetDigitValue(EnemiesValues[0]);
	m_EnemiesDigit[1].SetDigitValue(EnemiesValues[1]);
	m_EnemiesDigit[2].SetDigitValue(EnemiesValues[2]);

	m_LivesDigit[0].SetDigitValue(lives);
}
