/*----------------------------------------------------------------------------
	Program : Functions.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Various utility functions
				void PrintCard ( FILE *fp , CARD_RECORD *Card );
				void WriteLogEntry ( char *Message );
				int FindMaxStack ( void );
				int CalcMaxStack ( int SkipYou );
				int CalcTotalStack ( void );
				int CalcPercentageBet ( int Mode );
				int CalcTableWidth ( void );
				int FindBestHand ( int IncludeYourself );
				void ClearFolded ( void );
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

void PrintCard ( FILE *fp, CARD_RECORD *Card )
{
	switch ( Card->Rank )
	{
		case 9: 
			fprintf ( fp, " T" );
			break;
		case 10: 
			fprintf ( fp, " J" );
			break;
		case 11: 
			fprintf ( fp, " Q" );
			break;
		case 12: 
			fprintf ( fp, " K" );
			break;
		case 13: 
			fprintf ( fp, " A" );
			break;
		default:
			fprintf ( fp, " %d", Card->Rank+1 );
			break;
	}
	switch ( Card->Suit )
	{
		case SUIT_SPADES:
			fprintf ( fp, "s" );
			break;
		case SUIT_HEARTS:
			fprintf ( fp, "h" );
			break;
		case SUIT_CLUBS:
			fprintf ( fp, "c" );
			break;
		case SUIT_DIAMONDS:
			fprintf ( fp, "d" );
			break;
	}
}

void WriteLogEntry ( char *Message )
{
	FILE		*fp;
	DATETIMEVAL	Now;
	char		*UserAgent;
	char        *ScriptFilename = getenv ( "SCRIPT_FILENAME" );
	char        *Basename = basename ( ScriptFilename );
	
	/*---------------------------------------------------------------------------
		inconsistant, not enough info
		HTTP_USER_AGENT : Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:106.0) Gecko/20100101 Firefox/106.0
	---------------------------------------------------------------------------*/
	if (( UserAgent = getenv ( "HTTP_USER_AGENT" )) == NULL )
	{
		UserAgent = "null";
	}

	if (( fp = fopen ( LOGFILE, "a" )) == NULL )
	{
		printf ( "Cannot open %s for append<br>\n", LOGFILE );
		return;
	}

	if ( nsStrcmp ( Basename, "PokerDev.cgi" ) == 0 )
	{
		fprintf ( fp, "DEVELOPER" );
	}
	else
	{
		fprintf ( fp, "%s", sm.Address );
	}

	CurrentDateTime ( &Now );
	fprintf ( fp, "|%4d-%02d-%02d %02d:%02d",
		Now.year4, Now.month, Now.day, Now.hour, Now.minute);

	fprintf ( fp, "|%s", Message );

	if ( nsStrcasestr ( UserAgent, "iPhone" ) != NULL )
	{
		fprintf ( fp, "|iPhone" );
	}
	else if ( nsStrcasestr ( UserAgent, "Macintosh" ) != NULL )
	{
		fprintf ( fp, "|Macintosh" );
	}
	else if ( nsStrcasestr ( UserAgent, "Windows" ) != NULL )
	{
		fprintf ( fp, "|Windows" );
	}
	else if ( nsStrcasestr ( UserAgent, "Android" ) != NULL )
	{
		fprintf ( fp, "|Android" );
	}
	else if ( nsStrcasestr ( UserAgent, "null" ) != NULL )
	{
		fprintf ( fp, "|null" );
	}
	else
	{
		fprintf ( fp, "|UserAgent" );
	}

	if ( nsStrcmp ( Message, "Start new session" ) == 0 )
	{
		if ( sm.AspectRatio > 0.01 )
		{
			fprintf ( fp, " %dx%d %.3f", sm.WindowWidth, sm.WindowHeight, sm.AspectRatio );
		}
	}

	/*----------------------------------------------------------
		NOW write the F'n NEWLINE!!
	----------------------------------------------------------*/
	fprintf ( fp, "\n" );

	fclose ( fp );
}

int FindMaxStack ()
{
	int		xp, rv, max;

	for ( xp = 0, rv = 0, max = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( max < sm.Players[xp].Stack )
		{
			max = sm.Players[xp].Stack;
			rv = xp;
		}
	}
	return ( rv );
}

int CalcMaxStack ( int SkipYou )
{
	int		xp, max;

	for ( xp = 0, max = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( sm.Players[xp].Folded )
		{
			continue;
		}
		if ( SkipYou && xp == YOUR_INDEX )
		{
			continue;
		}
		if ( max < sm.Players[xp].Stack )
		{
			max = sm.Players[xp].Stack;
		}
	}
	
	return ( max );
}

int CalcTotalStack ()
{
	int		xp, rv;

	for ( xp = 0, rv = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		rv += sm.Players[xp].Stack;
	}
	return ( rv );
}

int CalcPercentageBet ( int Mode )
{
	int rv;
	
	switch ( Mode )
	{
		case MODE_BET_TEN_PERCENT:
			rv = 0.1 * sm.Players[YOUR_INDEX].Stack;
			break;

		case MODE_BET_FIFTY_PERCENT:
			rv = 0.5 * sm.Players[YOUR_INDEX].Stack;
			break;

		default:
			rv = 10;
			break;
	}
	return ( rv );
}

int CalcTableWidth ()
{
	int		rv = 100;

	switch ( sm.NumberOfPlayers )
	{
		case 2:
			rv = 1.6 * sm.WindowHeight;
			break;
		case 3:
			rv = 1.2 * sm.WindowHeight;
			break;
		case 4:
			rv = 0.925 * sm.WindowHeight;
			break;
		case 5:
			rv = 0.7 * sm.WindowHeight;
			break;
	}

	if ( rv > sm.WindowWidth )
	{
		rv =  sm.WindowWidth - 15;
	}

	return ( rv );
}

int FindBestHand ( int IncludeYourself )
{
	int	BestValue = 999999;
	int	BestPlayer = -1;

	for ( int xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( sm.Players[xp].Stack <= 0 || sm.Players[xp].Folded )
		{
			continue;
		}
		if ( IncludeYourself == 0 && xp == YOUR_INDEX )
		{
			continue;
		}

		if (  BestValue > sm.Players[xp].Value )
		{
			BestValue = sm.Players[xp].Value;
			BestPlayer = xp;
		}
	}

	return ( BestPlayer );
}

void ClearFolded ()
{
	for ( int xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{
		if ( sm.Players[xp].Folded )
		{
			sm.Players[xp].Folded = 0;
		}
	}
}
