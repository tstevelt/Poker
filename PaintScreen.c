/*----------------------------------------------------------------------------
	Program : PaintScreen.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Paint all the hands, with info in right hand column.
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

void PaintScreen ( int ShowResults, int BetResult )
{
	int		xp, xc, WinnerPlayer;
	char	*cp;
	int		TableWidth = CalcTableWidth();

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

	if ( ShowResults )
	{
		if ( BetResult == LOSER_BET )
		{
			WinnerPlayer = FindBestHand ( 0 );
		}
		else
		{
			WinnerPlayer = YOUR_INDEX;
		}
	}
	else
	{
		WinnerPlayer = -1;
	}

	for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		printf ( "<tr>\n" );
		if ( sm.Players[xp].Stack <= 0 && xp != YOUR_INDEX )
		{
			printf ( "<td class='poker' width='16%%'>\n" );
			printf ( "<img src='%s/%s' alt='%s'>\n", CARD_DIRECTORY, "GreenCard.png", "GreenCard.png" );
			printf ( "</td>\n" );
			printf ( "<td class='poker' width='64%%' colspan='4'>&nbsp;</td>\n" );
			printf ( "<td class='poker' width='16%%'>\n" );
			// out
				printf ( "<div class='cell6'>\n" );
				printf ( "Out\n" );
				printf ( "</div>\n" );
			printf ( "</td>\n" );
			printf ( "</tr>\n" );
			continue;
		}

		if ( ShowResults ==  1 &&  sm.Players[xp].Folded )
		{
			for ( xc = 0; xc < sm.HoleCards; xc++ )
			{
				printf ( "<td class='poker' width='16%%'>\n" );
				printf ( "<img src='%s/%s' alt='%s'>\n", CARD_DIRECTORY, "CardBack.png", "CardBack.png" );
				printf ( "</td>\n" );
			}
			printf ( "<td class='poker' colspan='%d'>&nbsp;</td>\n", 5 - sm.HoleCards );
			printf ( "<td class='poker' width='16%%'>\n" );
			printf ( "<div class='cell6'>\n" );
			printf ( "$%d\n", sm.Players[xp].Stack );
			printf ( "</div></td></tr>\n" );
			continue;
		}

		for ( xc = 0; xc < FIVE_CARDS; xc++ )
		{
			printf ( "<td class='poker' width='16%%'>\n" );
			if ( ShowResults == 0 && xc < sm.HoleCards && xp != YOUR_INDEX )
			{
				printf ( "<img src='%s/%s' alt='%s'>\n", CARD_DIRECTORY, "CardBack.png", "CardBack.png" );
			}
			else 
			{
				cp = FindImage ( sm.Players[xp].Cards[xc].Rank, sm.Players[xp].Cards[xc].Suit );
				printf ( "<img src='%s/%s' alt='%s'>\n", CARD_DIRECTORY, cp, cp );
			}
			printf ( "</td>\n" );
		}

		/*----------------------------------------------------------
			right hand cell.
			if not showresults show stack for everyone
				and if auto-folded write Folded
			else
				show stack for others
				and status and stack for player.
			tms 11/11/2022 show Winner for whoever won
		----------------------------------------------------------*/
		printf ( "<td class='poker' width='16%%'>\n" );
		printf ( "<div class='cell6'>\n" );

#ifdef OLD_LOGIC
		if ( ShowResults == 0 || xp != YOUR_INDEX )
		{
			printf ( "$%d", sm.Players[xp].Stack );
			if ( sm.Players[xp].Folded )
			{
				printf ( "<br />Folded\n" );
			}
		}
		else 
		{
			printf ( "%s\n", BetResult == WINNER_BET ? "Winner!" : "Loser" );
			printf ( "<br />$%d\n", sm.Players[xp].Stack );
		}
#endif
		if ( ShowResults == 0 )
		{
			printf ( "$%d", sm.Players[xp].Stack );
			if ( sm.Players[xp].Folded )
			{
				printf ( "<br />Folded\n" );
			}
		}
		else if ( xp == YOUR_INDEX )
		{
			printf ( "%s\n", BetResult == WINNER_BET ? "Winner!" : "Loser" );
			printf ( "<br />$%d\n", sm.Players[xp].Stack );
		}
		else
		{
			if ( xp == WinnerPlayer )
			{
				printf ( "Winner\n" );
			}
			printf ( "<br />$%d\n", sm.Players[xp].Stack );
		}



		printf ( "</div>\n" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );
	}

	PaintButtons ( ShowResults );

	printf ( "</tr>\n" );
	printf ( "</table>\n" );
}
