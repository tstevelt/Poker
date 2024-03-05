/*----------------------------------------------------------------------------
	Program : PaintButtons.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Paint buttons below tableau.  Display and disable according
				to player and game states.
	Return  : 
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

#include	"Poker.h"

void PaintButtons ( int ShowResults )
{
	int		GameOver = 1;
	int		EverybodyFolded = 1;

	/*----------------------------------------------------------
		analyze ...
	----------------------------------------------------------*/
	for ( int xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( xp == YOUR_INDEX )
		{
			if ( sm.Players[YOUR_INDEX].Stack == 0 )
			{
				GameOver = 1;
			}
		}
		else
		{
			if ( sm.Players[xp].Folded == 0 && sm.Players[xp].Stack > 0 )
			{
				EverybodyFolded = 0;
			}
			if ( sm.Players[xp].Stack > 0 )
			{
				GameOver = 0;
			}
		}
	}

	if ( GameOver == 1 && GameRecord.EndTime == 0 )
	{
		time ( &GameRecord.EndTime );
		SaveGame ();
	}

	printf ( "<td class='poker' colspan='5'>\n" );

	/*----------------------------------------------------------
		after deal, show bet buttons [Fold] [10] [>10] [AllIn]
		if everyone folded, then [Deal]
	----------------------------------------------------------*/
	if ( GameOver == 0 && ShowResults == 0 )
	{
		if ( EverybodyFolded )
		{
			printf ( "<input type='submit' name='submitFold' value='Deal'>\n" );
		}
		else
		{
			printf ( "<input type='submit' name='submitFold' value='Fold'>\n" );
			printf ( "&emsp;<input type='submit' name='submitBetFixed' value='$10'>\n" );
			int CheckAmount = CalcPercentageBet ( MODE_BET_TEN_PERCENT );
			if ( CheckAmount > 10 )
			{
				printf ( "&emsp;<input type='submit' name='submitBetTenPercent' value='$%d'>\n", CheckAmount );
			}
			CheckAmount = CalcPercentageBet ( MODE_BET_FIFTY_PERCENT );
			if ( CheckAmount > 10 )
			{
				printf ( "&emsp;<input type='submit' name='submitBetFiftyPercent' value='$%d'>\n", CheckAmount );
			}
			printf ( "&emsp;<input type='submit' name='submitAllIn' value='All In'>\n" );
		}
	}

	/*----------------------------------------------------------
		after bet/showing results  [Deal]
	----------------------------------------------------------*/
	if ( GameOver == 0 && ShowResults == 1 )
	{
		printf ( "<input type='submit' name='submitOkay' value='Deal'>\n" );
	}

	/*----------------------------------------------------------
		game over [Play Again] [Quit]
	----------------------------------------------------------*/
	if ( GameOver == 1 )
	{
		if ( RunMode != MODE_STATS )
		{
			printf ( "&emsp;<input type='submit' name='submitStats' value='Game Stats'>\n" );
		}
		printf ( "&emsp;<input type='submit' name='submitNewGame' value='Play Again'>\n" );
		printf ( "&emsp;<input type='submit' name='submitQuit' value='Quit'>\n" );
	}

	if ( ShowResults == 0 )
	{
		printf ( "<td class='poker' width='16%%'>\n" );
		printf ( "<div class='cell6'>\n" );
		if ( AnteAmount > 0 )
		{
			printf ( "$%d\n", AnteAmount );
		}
		else
		{
			printf ( " \n" );
		}
		printf ( "</div></td>\n" );
	}
}
