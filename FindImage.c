/*----------------------------------------------------------------------------
	Program : FindImage.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Given card and suit, find image for display
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

// CARD_DIRECTORY  "/var/www/vhosts/silverhammersoftware/html/PixGame/CARDS"
typedef struct
{
	int	Suit;
	int	Card;
	char	*ImageFile;
} IMAGE_RECORD;

static	IMAGE_RECORD	ImageArray[] = 
{
	{ SUIT_SPADES, 1, "2_of_spades.png" },
	{ SUIT_SPADES, 2, "3_of_spades.png" },
	{ SUIT_SPADES, 3, "4_of_spades.png" },
	{ SUIT_SPADES, 4, "5_of_spades.png" },
	{ SUIT_SPADES, 5, "6_of_spades.png" },
	{ SUIT_SPADES, 6, "7_of_spades.png" },
	{ SUIT_SPADES, 7, "8_of_spades.png" },
	{ SUIT_SPADES, 8, "9_of_spades.png" },
	{ SUIT_SPADES, 9, "10_of_spades.png" },
	{ SUIT_SPADES, 10, "jack_of_spades2.png" },
	{ SUIT_SPADES, 11, "queen_of_spades2.png" },
	{ SUIT_SPADES, 12, "king_of_spades2.png" },
	{ SUIT_SPADES, 13, "ace_of_spades2.png" },
	{ SUIT_HEARTS, 1, "2_of_hearts.png" },
	{ SUIT_HEARTS, 2, "3_of_hearts.png" },
	{ SUIT_HEARTS, 3, "4_of_hearts.png" },
	{ SUIT_HEARTS, 4, "5_of_hearts.png" },
	{ SUIT_HEARTS, 5, "6_of_hearts.png" },
	{ SUIT_HEARTS, 6, "7_of_hearts.png" },
	{ SUIT_HEARTS, 7, "8_of_hearts.png" },
	{ SUIT_HEARTS, 8, "9_of_hearts.png" },
	{ SUIT_HEARTS, 9, "10_of_hearts.png" },
	{ SUIT_HEARTS, 10, "jack_of_hearts2.png" },
	{ SUIT_HEARTS, 11, "queen_of_hearts2.png" },
	{ SUIT_HEARTS, 12, "king_of_hearts2.png" },
	{ SUIT_HEARTS, 13, "ace_of_hearts.png" },
	{ SUIT_CLUBS, 1, "2_of_clubs.png" },
	{ SUIT_CLUBS, 2, "3_of_clubs.png" },
	{ SUIT_CLUBS, 3, "4_of_clubs.png" },
	{ SUIT_CLUBS, 4, "5_of_clubs.png" },
	{ SUIT_CLUBS, 5, "6_of_clubs.png" },
	{ SUIT_CLUBS, 6, "7_of_clubs.png" },
	{ SUIT_CLUBS, 7, "8_of_clubs.png" },
	{ SUIT_CLUBS, 8, "9_of_clubs.png" },
	{ SUIT_CLUBS, 9, "10_of_clubs.png" },
	{ SUIT_CLUBS, 10, "jack_of_clubs2.png" },
	{ SUIT_CLUBS, 11, "queen_of_clubs2.png" },
	{ SUIT_CLUBS, 12, "king_of_clubs2.png" },
	{ SUIT_CLUBS, 13, "ace_of_clubs.png" },
	{ SUIT_DIAMONDS, 1, "2_of_diamonds.png" },
	{ SUIT_DIAMONDS, 2, "3_of_diamonds.png" },
	{ SUIT_DIAMONDS, 3, "4_of_diamonds.png" },
	{ SUIT_DIAMONDS, 4, "5_of_diamonds.png" },
	{ SUIT_DIAMONDS, 5, "6_of_diamonds.png" },
	{ SUIT_DIAMONDS, 6, "7_of_diamonds.png" },
	{ SUIT_DIAMONDS, 7, "8_of_diamonds.png" },
	{ SUIT_DIAMONDS, 8, "9_of_diamonds.png" },
	{ SUIT_DIAMONDS, 9, "10_of_diamonds.png" },
	{ SUIT_DIAMONDS, 10, "jack_of_diamonds2.png" },
	{ SUIT_DIAMONDS, 11, "queen_of_diamonds2.png" },
	{ SUIT_DIAMONDS, 12, "king_of_diamonds2.png" },
	{ SUIT_DIAMONDS, 13, "ace_of_diamonds.png" },
	{ SUIT_SPADES,   -1,   "black_joker.png" },
	{ SUIT_DIAMONDS, -1,   "red_joker.png" },
};

static	int				ImageCount = sizeof(ImageArray)/sizeof(IMAGE_RECORD);

char *FindImage ( int Card, int Suit )
{
	for ( int ndx = 0; ndx < ImageCount; ndx++ )
	{
		if ( ImageArray[ndx].Card == Card && ImageArray[ndx].Suit == Suit )
		{
			return ( ImageArray[ndx].ImageFile );
		}
	}
	return ( NULL );
}
