/*----------------------------------------------------------------------------
	Program : AutoFoldOneHole.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: eval cards showing in other hands and fold if you can't win.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		Nov 2022	add bluffing
						without bluffing the following happened:
						turns out that you now know every other player
						has at least pair. so boring.
----------------------------------------------------------*/
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

void AutoFoldOneHole ()
{
	int				AutoFoldDebug = 0;
	int				xp, xc, xv, xd, xr, xf;
	FILE			*fp;
	CARD_RECORD		VisibleCards[52];
	int				VisibleCount;
	CARD_RECORD		HoleCard;
	CARD_RECORD		RemainCards[52];
	int				RemainCount;
	CARD_RECORD		PlayerHand[5];
	int				BeatCount, MinValue, MaxValue, Value, rv, KevRank, KevSuit, KevHand[5];

	if ( AutoFoldDebug )
	{
		fp = fopen ( DEBUGFILE, "w" );
		// fprintf ( fp, "----\n" );
	}

	VisibleCount = 0;
	for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		for ( xc = 1; xc < 5; xc++ )
		{
			VisibleCards[VisibleCount].Suit = sm.Players[xp].Cards[xc].Suit;
			VisibleCards[VisibleCount].Rank = sm.Players[xp].Cards[xc].Rank;
			VisibleCount++;
		}
	}

	RemainCount = 0;
	for ( xd = 0; xd < 52; xd++ )
	{
		for ( xv = 0, xf = 0; xv < VisibleCount && xf == 0; xv++ )
		{
			if (( VisibleCards[xv].Suit == sm.Deck[xd].Card.Suit ) &&
				( VisibleCards[xv].Rank == sm.Deck[xd].Card.Rank ))
			{
				xf = 1;
			}
		}
		
		/*----------------------------------------------------------
			if not found in visible, add to remaining.
			note that this will include all the hole cards
		----------------------------------------------------------*/
		if ( xf == 0 )
		{
			RemainCards[RemainCount].Suit = sm.Deck[xd].Card.Suit;
			RemainCards[RemainCount].Rank = sm.Deck[xd].Card.Rank;
			RemainCount++;
		}		
	}

	if ( AutoFoldDebug )
	{
		fprintf ( fp, "visible %d: ", VisibleCount );
		for ( xv = 0; xv < VisibleCount; xv++ )
		{
			PrintCard ( fp, &VisibleCards[xv] );
		}
		fprintf ( fp, "\n" );

		fprintf ( fp, "remain %d: ", RemainCount );
		for ( xr = 0; xr < RemainCount; xr++ )
		{
			PrintCard ( fp, &RemainCards[xr] );
		}
		fprintf ( fp, "\n" );
	}

	for ( xc = 1; xc < 5; xc++ )
	{
		PlayerHand[xc].Suit = sm.Players[YOUR_INDEX].Cards[xc].Suit;
		PlayerHand[xc].Rank = sm.Players[YOUR_INDEX].Cards[xc].Rank;
	}

	for ( xp = 0; xp < sm.NumberOfPlayers && xp != YOUR_INDEX; xp++ )
	{
		HoleCard.Suit = sm.Players[xp].Cards[0].Suit;
		HoleCard.Rank = sm.Players[xp].Cards[0].Rank;
		if ( AutoFoldDebug )
		{
			fprintf ( fp, "%d hole card", xp+1 );
			PrintCard ( fp, &HoleCard );
			fprintf ( fp, " my cards value %d\n", sm.Players[xp].Value );
		}

		/*----------------------------------------------------------
			for remaining combinations of your hand, find the
			minimum and maximum value you might have.
		----------------------------------------------------------*/
		MinValue = 99999;
		MaxValue = 0;
		BeatCount = 0;
		for ( xr = 0; xr < RemainCount; xr++ )
		{
			if (( RemainCards[xr].Suit == HoleCard.Suit ) &&
				( RemainCards[xr].Rank == HoleCard.Rank ))
			{
				continue;
			}
			PlayerHand[0].Suit = RemainCards[xr].Suit;
			PlayerHand[0].Rank = RemainCards[xr].Rank;

			for ( xc = 0; xc < 5; xc++ )
			{
				switch ( PlayerHand[xc].Suit )
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

				KevRank = PlayerHand[xc].Rank-1;

				rv = find_card ( KevRank, KevSuit, sm.deck );

				KevHand[xc] = sm.deck[rv];
			}

			Value = eval_5hand ( KevHand );
			if ( MinValue > Value )
			{
				MinValue = Value;
			}
			if ( MaxValue < Value )
			{
				MaxValue = Value;
			}
			if ( Value > sm.Players[xp].Value )
			{
				BeatCount++;
			}
			if ( AutoFoldDebug > 1 )
			{
				fprintf ( fp, "min/max: " );
				for ( xc = 0; xc < 5; xc++ )
				{
					PrintCard ( fp, &PlayerHand[xc] );
				}
				fprintf ( fp, " %d\n", Value );
			}
		}

		sm.Players[xp].Folded = 0;

		if ( AutoFoldDebug )
		{
			fprintf ( fp, "%d Value %d  MinValue %d  MaxValue %d: ", xp+1, sm.Players[xp].Value, MinValue, MaxValue );
		}

		if ( sm.Players[xp].Value > MaxValue )
		{
			// gauranteed loss
			if ( flip(sm.Players[xp].WeakBluff) == 0 )
			{
				sm.Players[xp].Folded = 1;
				if ( AutoFoldDebug )
				{
					fprintf ( fp, "Guaranteed loss %d folded\n", xp+1 );
				}
			}
			else
			{
				if ( AutoFoldDebug )
				{
					fprintf ( fp, "Guaranteed loss %d bluffed\n", xp+1 );
				}
			}
		}
		else if ( sm.Players[xp].Value < MinValue )
		{
			// gauranteed winner
			if ( flip(sm.Players[xp].StrongBluff) == 0 )
			{
				if ( AutoFoldDebug )
				{
					fprintf ( fp, "Guaranteed winner %d left standing\n", xp+1 );
				}
			}
			else
			{
				sm.Players[xp].Folded = 1;
				if ( AutoFoldDebug )
				{
					fprintf ( fp, "Guaranteed winner %d folded, a bluff\n", xp+1 );
				}
			}
		}
		else
		{
			double Percent = (double) BeatCount / (double) (RemainCount+1);
			if ( AutoFoldDebug )
			{
				fprintf ( fp, "Depends %d, beat count %d, %.2f%%", xp+1, BeatCount, 100.0 * Percent );
			}
			if ( Percent < 0.5 )
			{
				sm.Players[xp].Folded = 1;
				if ( AutoFoldDebug )
				{
					fprintf ( fp, "FOLDED" );
				}
			}
			if ( AutoFoldDebug )
			{
				fprintf ( fp, "\n" );
			}
		}

		if ( AutoFoldDebug )
		{
			fprintf ( fp, "\n" );
		}
	}

	if ( AutoFoldDebug )
	{
		fclose ( fp );
	}
}
