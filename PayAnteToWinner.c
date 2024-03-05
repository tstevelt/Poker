/*----------------------------------------------------------------------------
	Program : PayAnteToWinner.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Pay all ante to the winner.
				If all opponents fold, then you had to fold but you 
				get the pot.
				If you folded then find the best hand (with stack and 
				not folded) and he gets the pot.
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

void PayAnteToWinner ()
{
	int		xp;
	int		EverybodyFolded = 1;
	
	/*----------------------------------------------------------
		assume everybody else folded
	----------------------------------------------------------*/
	for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( xp == YOUR_INDEX || sm.Players[xp].Stack <= 0 )
		{
			continue;
		}
		
		if ( sm.Players[xp].Folded == 0  )
		{
			/*----------------------------------------------------------
				somebody did NOT fold
			----------------------------------------------------------*/
			EverybodyFolded = 0;
			break;
		}
	}

	if ( EverybodyFolded )
	{
		/*----------------------------------------------------------
			everybody folded, you get the kitty
		----------------------------------------------------------*/
		sm.Players[YOUR_INDEX].Stack += AnteAmount;
	}
	else
	{
		xp = FindBestHand( 1 );
		if ( xp != YOUR_INDEX )
		{
			sm.Players[xp].Stack += AnteAmount;
		}
		else
		{
			int SecondBestValue = 99999;
			int SecondBestPlayer = -1;
			for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
			{
				if ( xp == YOUR_INDEX )
				{
					continue;
				}
				if ( sm.Players[xp].Stack <= 0 )
				{
					continue;
				}
				if ( SecondBestValue > sm.Players[xp].Value )
				{
					SecondBestValue = sm.Players[xp].Value;
					SecondBestPlayer = xp;
				}
			}

			if ( SecondBestPlayer == -1 )
			{
				printf ( "IMPOSSIBLE!<br>\n" );
			}
			else
			{
				sm.Players[SecondBestPlayer].Stack += AnteAmount;
			}
		}
	}
}
