/*----------------------------------------------------------------------------
	Program : SessionFuncs.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Game is stateless, store game state in server-side session file.
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

void InitSession ()
{
	char	*cp;

	memset ( sm.Address, '\0', sizeof(sm.Address) );
	if (( cp = getenv ( "REMOTE_ADDR" )) == NULL )
	{
		snprintf ( sm.Address, sizeof(sm.Address), "unknown" );
	}
	else
	{
		snprintf ( sm.Address, sizeof(sm.Address), cp );
	}

	for ( int xp = 0; xp < sm.NumberOfPlayers; xp++ )
	{	
		if ( xp != YOUR_INDEX )
		{
			sm.Players[xp].StrongBluff = d_random_range ( 0.01, 0.08 );
			sm.Players[xp].WeakBluff   = d_random_range ( 0.01, 0.08 );
		}
	}

	switch ( sm.Type )
	{
		case TYPE_NORMAL:
			sm.TotalMoney = sm.NumberOfPlayers * BUY_IN_AMOUNT; 
			break;
		case TYPE_MILLIONAIRE:
			sm.TotalMoney = BUY_IN_AMOUNT + 1000000;
			break;
	}

	WriteLogEntry ( "Start new session" );
}

int LoadSession ()
{
	char	Filename[128];
	FILE	*fp;
	
	sprintf ( Filename, "%s/%s.dat", SESSION_DIR, SessionID );

	if (( fp = fopen ( Filename, "r" )) == NULL )
	{
		// printf ( "Cannot open session file %s<br>\n", Filename );
		return ( -1 );
	}

	if (  fread ( &sm, sizeof(sm), 1, fp ) != 1 )
	{
		printf ( "Session file read error %s<br>\n", Filename );
	}

	fclose ( fp );
	return ( 0 );
}

void SaveSession ()
{
	char	Filename[128];
	FILE	*fp;
	
	sprintf ( Filename, "%s/%s.dat", SESSION_DIR, SessionID );

	if (( fp = fopen ( Filename, "w" )) == NULL )
	{
		printf ( "Cannot create session file %s<br>\n", Filename );
		memset ( &sm, '\0', sizeof(sm) );
		return;
	}

	if ( fwrite ( &sm, sizeof(sm), 1, fp ) != 1 )
	{
		printf ( "Session file read error %s<br>\n", Filename );
	}

	fclose ( fp );
}
