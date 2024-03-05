/*----------------------------------------------------------------------------
	Program : PaintTop.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Start HTML screen
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

#define		CSS_VERSION		"20221101"

void PaintTop ( int Stage )
{
	WEBPARMS	*ptrWebParms = webInitParms();
	char		*ScriptFilename = getenv ( "SCRIPT_FILENAME" );
	char		*Basename = basename ( ScriptFilename );

	if ( Stage == 1 )
	{
		webContentHtml ();

		ptrWebParms->WP_Title = "Poker";
		webStartHead ( ptrWebParms );

		printf ( "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n" );

		printf ( "<link rel='stylesheet' href='Poker.css?version=%s'>\n", CSS_VERSION );
		printf ( "<script src='Poker.js'></script>\n" );
	}
	else if ( Stage == 2 )
	{
		printf ( "</head>\n" );

		printf ( "<body class='%s' onLoad='javascript:Loaded();'>\n", RunMode == MODE_START ? "start" : "game" );
		printf ( "<div id='PokerDiv' class='game'>\n" );

		ptrWebParms->WP_FormName   = "Poker";
		ptrWebParms->WP_FormAction = Basename;
		ptrWebParms->WP_FormMethod = "POST";
		ptrWebParms->WP_FormOther  = (char *)0;
		webStartForm ( ptrWebParms );

		webFreeParms ( ptrWebParms );

		if ( nsStrlen ( SessionID ) > 0 )
		{
			printf ( "<input type='hidden' name='SessionID' value='%s'>\n", SessionID );
		}
	}
}
