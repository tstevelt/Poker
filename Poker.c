/*----------------------------------------------------------------------------
	Program : Poker.c
	Author  : Tom Stevelt
	Date    : Oct 2022
	Synopsis: 5 card stud
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		11/01/2022	Automatic sizing.  Clean up code.
	tms		11/03/2022	Fix Ante bug. Cleanup buttons.  Add Game Stats.

----------------------------------------------------------------------------*/
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

#define		MAIN
#include	"Poker.h"

int main ( int argc, char *argv[] )
{
	int		DoSave = 0;
	int		ShowResults = 0;
	int		BetResult;

	seed_random_with_usec ();

	GlobalDebug = 0;
	if ( GlobalDebug )
	{
		gfp = fopen ( DEBUGFILE, "a" );
		fprintf ( gfp, "---------\n" );
	}

	PaintTop ( 1 );
	GetInput ();
	if ( RunMode == MODE_START || nsStrlen ( SessionID ) == 0 )
	{
		RunMode = MODE_START;
	}
	else
	{
		LoadSession ();
	}

	PaintTop ( 2 );
	
	if (( RunMode == MODE_OKAY ) && 
		( sm.Players[YOUR_INDEX].Stack <= 0 || sm.Players[YOUR_INDEX].Stack == sm.TotalMoney) )
	{
		RunMode = MODE_NEW_GAME;
	}

	switch ( RunMode )
	{
		case MODE_BET_FIXED:
		case MODE_BET_TEN_PERCENT:
		case MODE_BET_FIFTY_PERCENT:
		case MODE_ALL_IN:
			LoadGame ();
			BetResult = EvalBet ( RunMode );
			SaveGame ();
			DoSave = 1;
			ShowResults = 1;
			break;

		case MODE_NEW_GAME:
			for ( int xp = 0; xp < sm.NumberOfPlayers; xp++ )
			{
				if ( sm.Type == TYPE_MILLIONAIRE && xp == 0 )
				{
					sm.Players[xp].Stack = 1000000;
				}
				else
				{
					sm.Players[xp].Stack = BUY_IN_AMOUNT;
				}
				sm.Players[xp].Folded = 0;
			}
			sm.Rounds = 0;
			sm.Winner = -1;
			InitGame ();
			SaveGame ();
			/* FALL-THROUGH */
		case MODE_FOLD:
			LoadGame ();
			if ( RunMode == MODE_FOLD )
			{
				GameRecord.FoldCount++;
				SaveGame ();
				PayAnteToWinner ();
			}
			/* FALL-THROUGH */
		case MODE_OKAY:
			InitDeck ();
			Shuffle ();
			/*----------------------------------------------------------
				do cactus kev stuff
			----------------------------------------------------------*/
			init_deck ( sm.deck );
			sm.Rounds++;
			Deal ( 1 );
			if ( sm.HoleCards == 2 )
			{
				AutoFoldTwoHole ();
			}
			else
			{
				AutoFoldOneHole ();
			}
			DoSave = 1;
			ShowResults = 0;
			BetResult = 0;
			break;
	}

	if ( RunMode == MODE_START )
	{
		PaintStartup ();
	}
	else if ( RunMode == MODE_STATS )
	{
		PaintStats ();
	}
	else
	{
		PaintScreen ( ShowResults, BetResult );
		if ( ShowResults )
		{
			ClearFolded ();
		}
	}

	PaintBottom ( RunMode );

	if ( DoSave )
	{
		SaveSession ();
	}

	return ( 0 );
}
