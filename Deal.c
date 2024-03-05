/*----------------------------------------------------------------------------
	Program : Deal.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Deal all the cards to all the players
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

#include    "Poker.h"

void Deal ( int PrintAnteAmount )
{
	int		xp, xc, ndx;
	int		rv, KevRank, KevSuit, KevHand[5];
	char	Message[128];
	
	if ( sm.Rounds ==  1 )
	{
		if ( sm.Type == TYPE_MILLIONAIRE )
		{
			sprintf ( Message, "Start Beat the Millionaire" );
		}
		else
		{
			sprintf ( Message, "Start %d player game", sm.NumberOfPlayers );
		}
		WriteLogEntry ( Message );
	}

	/*----------------------------------------------------------
		go around the table just like a real game
		important to not deal to broke players, so those
		cards wind up in remainder stack.
	----------------------------------------------------------*/
	ndx = 0;
	for ( xc = 0; xc < FIVE_CARDS; xc++ )
	{
		for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
		{
			if ( sm.Players[xp].Stack > 0 )
			{
				sm.Players[xp].Cards[xc].Suit = sm.Deck[ndx].Card.Suit;
				sm.Players[xp].Cards[xc].Rank = sm.Deck[ndx].Card.Rank;
				ndx++;
			}
			else
			{
				sm.Players[xp].Cards[xc].Suit = 0;
				sm.Players[xp].Cards[xc].Rank = 0;
			}
		}
	}

	/*----------------------------------------------------------
		now for each hand, calculate its value
		while we're at it, calculate AnteAmount
	----------------------------------------------------------*/
	AnteAmount = 0;
	for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( sm.Players[xp].Stack > 0 )
		{
			sm.Players[xp].Stack -= ANTE_AMOUNT;
			AnteAmount           += ANTE_AMOUNT;
		}

		for ( xc = 0; xc < 5; xc++ )
		{
			switch ( sm.Players[xp].Cards[xc].Suit )
			{
				case SUIT_SPADES:
					KevSuit = SPADE;
					break;
				case SUIT_HEARTS:
					KevSuit = HEART;
					break;
				case SUIT_CLUBS:
					KevSuit = CLUB;
					break;
				case SUIT_DIAMONDS:
					KevSuit = DIAMOND;
					break;
			}

			KevRank = sm.Players[xp].Cards[xc].Rank-1;

			rv = find_card ( KevRank, KevSuit, sm.deck );

			KevHand[xc] = sm.deck[rv];
		}
		sm.Players[xp].Value = eval_5hand ( KevHand );
	}
	if ( PrintAnteAmount )
	{
		printf ( "<input type='hidden' name='AnteAmount' value='%d'>\n", AnteAmount );
	}
}
