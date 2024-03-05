/*----------------------------------------------------------------------------
	Program : InitDeck.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Initialize and shuffle the deck.
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

void InitDeck ()
{
	int		ndx = 0;

	for	( int suit = SUIT_SPADES; suit <= SUIT_DIAMONDS; suit++ )
	{
		for ( int card = 1; card <= 13; card++ )
		{
			sm.Deck[ndx].Card.Suit = suit;
			sm.Deck[ndx].Card.Rank = card;
			sm.Deck[ndx].Sort  = d_random();
			ndx++;
		}
	}

	long usec = random_range ( 100, 250000 );
	usleep ( usec );

	for ( int xd = 0; xd < 52; xd++ )
	{
		sm.Deck[ndx].Sort += d_random();
	}

	usec = random_range ( 100, 250000 );
	usleep ( usec );

	for ( int xd = 0; xd < 52; xd++ )
	{
		sm.Deck[ndx].Sort += d_random();
	}
}
