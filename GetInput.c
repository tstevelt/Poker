/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Get user input for game config to play and game actions.
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

int GetInput ()
{
	int		xa;
	int		rv = 0;
	int		DoInitSession = 0;

	if ( webGetInput () != 0 )
	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}
	
	RunMode = MODE_NEW_GAME;

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

		// printf ( "GetInput: %s = %s<br>\n", webNames[xa], webValues[xa] );

		if ( strcmp (webNames[xa], "SessionID" ) == 0 )
		{
			sprintf ( SessionID, "%s", webValues[xa] );
		}

		else if ( strcmp ( webNames[xa], "submitFold" ) == 0 )
		{
			RunMode = MODE_FOLD;
		}
		else if ( strcmp ( webNames[xa], "submitOkay" ) == 0 )
		{
			RunMode = MODE_OKAY;
		}
		else if ( strcmp ( webNames[xa], "submitBetFixed" ) == 0 )
		{
			RunMode = MODE_BET_FIXED;
		}
		else if ( strcmp ( webNames[xa], "submitBetTenPercent" ) == 0 )
		{
			RunMode = MODE_BET_TEN_PERCENT;
		}
		else if ( strcmp ( webNames[xa], "submitBetFiftyPercent" ) == 0 )
		{
			RunMode = MODE_BET_FIFTY_PERCENT;
		}
		else if ( strcmp ( webNames[xa], "submitAllIn" ) == 0 )
		{
			RunMode = MODE_ALL_IN;
		}
		else if ( strcmp ( webNames[xa], "submitNewGame" ) == 0 )
		{
			RunMode = MODE_NEW_GAME;
		}
		else if ( strcmp ( webNames[xa], "submitQuit" ) == 0 )
		{
			RunMode = MODE_START;
		}

		else if ( strcmp ( webNames[xa], "GameType" ) == 0 )
		{
			switch ( webValues[xa][0] )
			{
				case '2':
				case '3':
				case '4':
				case '5':
					sm.NumberOfPlayers = nsAtoi ( webValues[xa] );
					sm.Type = TYPE_NORMAL;
					break;

				case 'M':
					sm.NumberOfPlayers = 2;
					sm.Type = TYPE_MILLIONAIRE;
					break;
			}
		}
		else if ( strcmp ( webNames[xa], "HoleCards" ) == 0 )
		{
			switch ( webValues[xa][0] )
			{
				case '1':
				case '2':
					sm.HoleCards = nsAtoi ( webValues[xa] );
					break;
			}
		}
		else if ( strcmp ( webNames[xa], "submitStartup" ) == 0 )
		{
			DoInitSession = 1;
		}
		else if ( strcmp ( webNames[xa], "submitStats" ) == 0 )
		{
			RunMode = MODE_STATS;
		}

		else if ( strcmp (webNames[xa], "Players" ) == 0 )
		{
			sm.NumberOfPlayers = atoi ( webValues[xa] );
			if ( sm.NumberOfPlayers < 2 || sm.NumberOfPlayers > 5 )
			{
				printf ( "Number of players should be two through five" );
				sm.NumberOfPlayers = 3;
			}
			RunMode = MODE_NEW_GAME;
		}
		else if ( strcmp (webNames[xa], "Millionaire" ) == 0 )
		{
			sm.Type = TYPE_MILLIONAIRE;
			sm.NumberOfPlayers = 2;
			RunMode = MODE_NEW_GAME;
		}

		else if ( strcmp (webNames[xa], "AspectRatio" ) == 0 )
		{
			sm.AspectRatio = nsAtof ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "WindowWidth" ) == 0 )
		{
			sm.WindowWidth = nsAtoi ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "WindowHeight" ) == 0 )
		{
			sm.WindowHeight = nsAtoi ( webValues[xa] );
		}

		else if ( strcmp (webNames[xa], "AnteAmount" ) == 0 )
		{
			AnteAmount = nsAtoi ( webValues[xa] );
		}

		else
		{
			printf ( "Unknown name value pair %s = %s<br>\n", webNames[xa], webValues[xa] );
		}
	}

	if ( DoInitSession )
	{
		MakeSessionID ( SessionID, SESSION_LENGTH, 0 );
		InitSession ();
	}

	return ( rv );
}
