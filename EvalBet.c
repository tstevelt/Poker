/*----------------------------------------------------------------------------
	Program : EvalBet.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Hands have already been scored, evaluate outcome

	Regarding all in bets: https://www.mypokercoaching.com/all-in-poker/
		For example, if you have $200 in front of you in a cash game and 
		someone with $1,000 in chips announces they're all in, you don't 
		need to add an extra $800 to match their bet.

		If you make the call, the maximum you can lose is the $200 you 
		have in your stack. Of course, you can only win $200 as well, 
		and if you're the only caller, the excess money will be returned 
		to the player with the bigger stack.
---------------------------------------------------------------------------*/
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

int EvalBet ( int BetType )
{
	int		rv;
	int		BetAmount;
	int		WinAmount;
	int		xp;
	int		BestPlayer;
	char	Message[128];

	if ( sm.Players[YOUR_INDEX].Stack <= 0 )
	{
		printf ( "YOU ARE BROKE<br>\n" );
		return ( 0 );
	}

	WinAmount = 0;
	switch ( BetType )
	{
		case MODE_BET_FIXED:
		case MODE_BET_TEN_PERCENT:
		case MODE_BET_FIFTY_PERCENT:
			if ( BetType == MODE_BET_FIXED )
			{
				BetAmount = BET_AMOUNT;
			}
			else
			{
				BetAmount = CalcPercentageBet ( BetType );
			}
			if ( BetAmount > sm.Players[YOUR_INDEX].Stack )
			{
				BetAmount = sm.Players[YOUR_INDEX].Stack;
			}
			break;
		case MODE_ALL_IN:
			BetAmount = sm.Players[YOUR_INDEX].Stack;
			break;
		default:
			printf ( "INVALID BET TYPE<br>\n" );
			return ( INVALID_BET );
	}

	/*----------------------------------------------------------
		find best hand
	----------------------------------------------------------*/
	BestPlayer = FindBestHand ( 1 );

	if ( BestPlayer == YOUR_INDEX )
	{
		WinAmount = 0;

		/*----------------------------------------------------------
			deduct from losers who did not fold
		----------------------------------------------------------*/
		for ( xp = 0; xp < sm.NumberOfPlayers; xp++ )
		{
			if ( sm.Players[xp].Folded || xp == YOUR_INDEX )
			{
				continue;
			}

			if ( sm.Players[xp].Stack >  BetAmount )
			{
				sm.Players[xp].Stack -= BetAmount;
				WinAmount += BetAmount;
			}
			else
			{
				WinAmount += sm.Players[xp].Stack;
				sm.Players[xp].Stack = 0;
			}
		}

		/*----------------------------------------------------------
			winner
		----------------------------------------------------------*/
		sm.Players[YOUR_INDEX].Stack += (WinAmount + AnteAmount);
		
		/*----------------------------------------------------------
			now we can see if game is over
		----------------------------------------------------------*/
		if ( sm.TotalMoney == sm.Players[YOUR_INDEX].Stack )
		{
			sm.Winner = YOUR_INDEX;

			sprintf ( Message, "Player WON $%d after %d rounds", sm.Players[YOUR_INDEX].Stack,  sm.Rounds );
			WriteLogEntry ( Message );
		}

		rv = WINNER_BET;

		GameRecord.WonCount++;
		if ( GameRecord.BestWin < (WinAmount + AnteAmount) )
		{
			GameRecord.BestWin = (WinAmount + AnteAmount);
			memcpy ( GameRecord.BestHand, sm.Players[YOUR_INDEX].Cards, sizeof(GameRecord.BestHand) );
		}
	}
	else
	{
		int MaxLoss = CalcMaxStack ( 1 );
		if ( BetAmount > MaxLoss )
		{
			BetAmount = MaxLoss;
		}

		/*----------------------------------------------------------
			loser
		----------------------------------------------------------*/
		sm.Players[YOUR_INDEX].Stack -= BetAmount;
		sm.Players[BestPlayer].Stack += (BetAmount + AnteAmount);

		if ( sm.Players[YOUR_INDEX].Stack == 0 )
		{
			/*----------------------------------------------------------
				this sets the game winner to the opponent with the
				highest stack.  in games with three or more players,
				the remaining players do not keep on playing, so this
				is an assumption about who might win if they did.
			----------------------------------------------------------*/
			sm.Winner = FindMaxStack ();

			sprintf ( Message, "Player LOST after %d rounds", sm.Rounds );
			WriteLogEntry ( Message );
		}

		rv = LOSER_BET;

		GameRecord.LostCount++;
		if ( GameRecord.WorstLoss < BetAmount )
		{
			GameRecord.WorstLoss = BetAmount;
			memcpy ( GameRecord.WorstHand, sm.Players[YOUR_INDEX].Cards, sizeof(GameRecord.WorstHand) );
		}
	}

	/*----------------------------------------------------------
		clear all folded flags for the next deal
		fixit this may be too early
	ClearFolded ();
	----------------------------------------------------------*/

	return ( rv );
}
