/*----------------------------------------------------------------------------
	Program : PaintStats.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Game over, show statistics.
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

void PaintStats ()
{
	int		xp;
	int		TableWidth = CalcTableWidth();
	DATETIMEVAL		dtVal;

	if ( TableWidth == 100 )
	{
		printf ( "<table id='PokerTable' width='100%%'" );
		printf ( " style='border: 1px solid; border-collapse: collapse; border-color: yellow;'" );
		printf ( " align='center'>\n" );
	}
	else
	{
		printf ( "<table id='PokerTable' width='%d'", TableWidth );
		printf ( " style='border: 1px solid; border-collapse: collapse; border-color: yellow;'" );
		printf ( " align='center'>\n" );
	}

	LoadGame ();

	for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		printf ( "<tr>\n" );

		printf ( "<td class='poker' width='16%%'>\n" );
		printf ( "<img src='%s/%s' alt='%s'>\n", CARD_DIRECTORY, "CardBack.png", "CardBack.png" );
		printf ( "</td>\n" );

		if ( xp == 0 )
		{
			printf ( "<td class='poker' width='80%%' colspan='5' rowspan='%d'>\n", sm.NumberOfPlayers );
			printf ( "<div id='GameResults'>\n" );

			printf ( "<h2>Game Summary</h2>\n" );
			printf ( "Players: %d<br>\n", sm.NumberOfPlayers );
			switch ( sm.Type )
			{
				case TYPE_NORMAL:
					printf ( "Game   : Normal - %s Hole Card<br>\n", sm.HoleCards == 2 ? "2" : "1" );
					break;
				case TYPE_MILLIONAIRE:
					printf ( "Game   : Beat the Millionaire - %s Hole Card<br>\n", sm.HoleCards == 2 ? "2" : "1" );
					break;
			}
			//  - %s Hole Card\n", sm.HoleCards == 2 ? "2" : "1" );
			printf ( "Total: $%d<br>\n", sm.TotalMoney );
			printf ( "Winner:  %s<br>\n", sm.Winner == YOUR_INDEX ? "You won!" : "Opponent won" );
			printf ( "Rounds : %d<br>\n", sm.Rounds );
			printf ( "Won       :  %3d<br>\n", GameRecord.WonCount );
			printf ( "Lost      :  %3d<br>\n", GameRecord.LostCount );
			printf ( "Fold      :  %3d<br>\n", GameRecord.FoldCount );
			printf ( "Best Win  : $%3d", GameRecord.BestWin );
			if ( GameRecord.BestWin > 0 )
			{
				printf ( "  on hand: " );
				for ( int xc = 0; xc < 5; xc++ )
				{
					PrintCard ( stdout, &GameRecord.BestHand[xc] );
				}
			}
			printf ( "<br>\n" );

			printf ( "Worst Loss: $%3d", GameRecord.WorstLoss );
			if ( GameRecord.WorstLoss > 0 )
			{
				printf ( "  on hand: " );
				for ( int xc = 0; xc < 5; xc++ )
				{
					PrintCard ( stdout, &GameRecord.WorstHand[xc] );
				}
			}
			printf ( "<br>\n" );

			/*---------------------------------------------------------------------------
			printf ( "Game Time : %ld %ld = %ld seconds", 
					GameRecord.StartTime, GameRecord.EndTime, GameRecord.EndTime - GameRecord.StartTime );
			---------------------------------------------------------------------------*/

//	void ConvertSecondsToDateTimeVal ( time_t Seconds, DATETIMEVAL *dtValue )

			ConvertSecondsToDateTimeVal ( (time_t) (GameRecord.EndTime - GameRecord.StartTime), &dtVal );
			
			if ( dtVal.hour > 0 )
			{
				printf ( "Game Time : %d hours, %d minutes, %d seconds", dtVal.hour, dtVal.minute, dtVal.second );
			}
			else
			{
				printf ( "Game Time : %d minutes, %d seconds", dtVal.minute, dtVal.second );
			}

			printf ( "<p>\n" );
			
			printf ( "<span style='font-size: smaller;'>IP addr: %s</span><br>\n", 
						sm.Address );
			printf ( "<span style='font-size: smaller;'>Window : %dx%d %.3f</span><br>\n", 
						sm.WindowWidth, sm.WindowHeight, sm.AspectRatio );

			printf ( "</div>\n" );
			printf ( "</td>\n" );
		}

		printf ( "</tr>\n" );
	}

	PaintButtons ( 0 );

	printf ( "</tr>\n" );
	printf ( "</table>\n" );
}
