//     Online poker solitaire
// 
//     Copyright (C)  2022-2024 Tom Stevelt
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.
// 
//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<stdint.h>
#include	<errno.h>
#include	<libgen.h>		// for basename()
#include	"shslib.h"
#include	"weblib.h"

#ifdef MAIN
#define	TYPE	/* */
#else
#define	TYPE	extern
#endif

/*----------------------------------------------------------
	stuff for Cactus Kev evaluator
----------------------------------------------------------*/
#include	"poker.h"

/*----------------------------------------------------------
	game defines and typedefs
----------------------------------------------------------*/
#define		CARD_DIRECTORY	"PixGame/CARDS"
#define		SESSION_DIR		"/var/local/webstate/Poker"
#define		LOGFILE			"/var/local/webstate/Poker/Poker.log"
#define		DEBUGFILE		"/var/local/webstate/Poker/Debug.txt"

#define		FIVE_CARDS		5
#define		BUY_IN_AMOUNT	100
#define     BET_AMOUNT      10
#define     ANTE_AMOUNT     1

#define		SUIT_SPADES		1
#define		SUIT_HEARTS		2
#define		SUIT_CLUBS		3
#define		SUIT_DIAMONDS	4

typedef struct
{
	int		Suit;
	int		Rank;
} CARD_RECORD;

typedef struct
{
	CARD_RECORD	Card;
	double	Sort;
} DECK_RECORD;

typedef struct
{
	CARD_RECORD			Cards[5];
	unsigned short	Value;
	int				Stack;
	int				Folded;
	double			StrongBluff;
	double			WeakBluff;
} PLAYER_RECORD;

#define		MAXPLAYERS			5
#define		SESSION_LENGTH		10

#define		MODE_START				1
#define		MODE_NEW_GAME			2
#define		MODE_FOLD				3
#define		MODE_BET_FIXED			4
#define		MODE_BET_TEN_PERCENT	5
#define		MODE_BET_FIFTY_PERCENT	6
#define		MODE_ALL_IN				7
#define		MODE_OKAY				8
#define		MODE_STATS				9

#define		WINNER_BET			11
#define		LOSER_BET			12
#define		INVALID_BET			13

#define		TYPE_NORMAL			20
#define		TYPE_MILLIONAIRE	21

#define		YOUR_INDEX		(sm.NumberOfPlayers-1)

typedef struct
{
	int		Rounds;
	int		WonCount;
	int		LostCount;
	int		FoldCount;
	int		BestWin;
	CARD_RECORD	BestHand[5];
	int		WorstLoss;
	CARD_RECORD	WorstHand[5];
	time_t		StartTime;
	time_t		EndTime;
} GAME_RECORD;

/*----------------------------------------------------------
	game variables
----------------------------------------------------------*/
TYPE	char	SessionID[SESSION_LENGTH+1];
TYPE	int		RunMode;
TYPE	char	OnLoadFunction[24];
TYPE	int		AnteAmount;
TYPE	GAME_RECORD		GameRecord;
TYPE	int		GlobalDebug;
TYPE	FILE	*gfp;

/*----------------------------------------------------------
	session structure is saved/loaded from disk
----------------------------------------------------------*/
typedef struct
{
	char			Address[16];
	int				deck[52];
	DECK_RECORD		Deck[52];
	PLAYER_RECORD	Players[MAXPLAYERS];
	int				NumberOfPlayers;
	int				Type;
	int				HoleCards;
	int				TotalMoney;
	int				Winner;
	int				Rounds;
	double			AspectRatio;
	int				WindowWidth;
	int				WindowHeight;
} SESSION_RECORD;

TYPE	SESSION_RECORD		sm;


#ifdef EXTRA
/* GetArgs.c */
void GetArgs ( int argc , char *argv []);

/* PokerAUTO.c */
int main ( int argc , char *argv []);

/* PokerCLI.c */
int main ( int argc , char *argv []);

/* PokerSpy.c */
int main ( int argc , char *argv []);

/* Print.c */
void Print ( void );
#endif

/*----------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------*/

/* AutoFoldOneHole.c */
void AutoFoldOneHole ( void );

/* AutoFoldTwoHole.c */
void AutoFoldTwoHole ( void );

/* Deal.c */
void Deal ( int PrintAnteAmount );

/* EvalBet.c */
int EvalBet ( int BetType );

/* FindImage.c */
char *FindImage ( int Card , int Suit );

/* Functions.c */
void PrintCard ( FILE *fp , CARD_RECORD *Card );
void WriteLogEntry ( char *Message );
int FindMaxStack ( void );
int CalcMaxStack ( int SkipYou );
int CalcTotalStack ( void );
int CalcPercentageBet ( int Mode );
int CalcTableWidth ( void );
int FindBestHand ( int IncludeYourself );
void ClearFolded ( void );

/* GameFuncs.c */
void InitGame ( void );
int LoadGame ( void );
void SaveGame ( void );

/* GetInput.c */
int GetInput ( void );

/* InitDeck.c */
void InitDeck ( void );

/* PaintBottom.c */
void PaintBottom ( int RunMode );

/* PaintButtons.c */
void PaintButtons ( int ShowResults );

/* PaintScreen.c */
void PaintScreen ( int ShowResults , int BetResult );

/* PaintStartup.c */
void PaintStartup ( void );

/* PaintStats.c */
void PaintStats ( void );

/* PaintTop.c */
void PaintTop ( int Stage );

/* PayAnteToWinner.c */
void PayAnteToWinner ( void );

/* Poker.c */
int main ( int argc , char *argv []);

/* SessionFuncs.c */
void InitSession ( void );
int LoadSession ( void );
void SaveSession ( void );

/* Shuffle.c */
void Shuffle ( void );
