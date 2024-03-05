/*----------------------------------------------------------------------------
	Program : GameFuncs.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Initiallize game, save game to file, load game from file
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

#define		SESSION_DIR		"/var/local/webstate/Poker"

void InitGame ()
{
	memset ( &GameRecord, '\0', sizeof(GameRecord) );
	time ( &GameRecord.StartTime );
}

int LoadGame ()
{
	char	Filename[128];
	FILE	*fp;
	
	sprintf ( Filename, "%s/%s.game", SESSION_DIR, SessionID );

	if (( fp = fopen ( Filename, "r" )) == NULL )
	{
		// printf ( "Cannot open game file %s<br>\n", Filename );
		return ( -1 );
	}

	if (  fread ( &GameRecord, sizeof(GameRecord), 1, fp ) != 1 )
	{
		printf ( "Game file read error %s<br>\n", Filename );
	}

	fclose ( fp );
	return ( 0 );
}

void SaveGame ()
{
	char	Filename[128];
	FILE	*fp;
	
	sprintf ( Filename, "%s/%s.game", SESSION_DIR, SessionID );

	if (( fp = fopen ( Filename, "w" )) == NULL )
	{
		printf ( "Cannot create game file %s<br>\n", Filename );
		memset ( &GameRecord, '\0', sizeof(GameRecord) );
		return;
	}

	if ( fwrite ( &GameRecord, sizeof(GameRecord), 1, fp ) != 1 )
	{
		printf ( "Game file read error %s<br>\n", Filename );
	}

	fclose ( fp );
}
