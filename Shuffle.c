/*----------------------------------------------------------------------------
	Program : Shuffle.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Sort card according to random values asssigned in InitDeck()
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

static int cmprec ( DECK_RECORD *a, DECK_RECORD *b )
{
	if ( a->Sort < b->Sort )
	{
		return ( -1 );
	}
	if ( a->Sort > b->Sort )
	{
		return ( 1 );
	}
	return ( 0 );
}

void Shuffle ()
{
	qsort ( sm.Deck, 52, sizeof(DECK_RECORD), (int(*)()) cmprec );
}
