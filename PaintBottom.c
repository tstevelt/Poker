/*----------------------------------------------------------------------------
	Program : PaintBottom.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: End HTML screen
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

void PaintBottom ( int RunMode )
{
	webEndForm ();

	if ( RunMode == MODE_START )
	{
		printf ( "</div>\n" );
		printf ( "<div class='footer'>\n" );
		printf ( "<a target='_self' href='http://www.silverhammersoftware.com'>Copyright 2022 Silver Hammer Software LLC</a>\n" );
		printf ( "</div>\n" );
	}

	/*----------------------------------------------------------
		Loaded may call OnLoadFunction
	----------------------------------------------------------*/
	printf ( "<script>\n" );
	printf ( "function Loaded ()\n" );
	printf ( "{\n" );
	if ( nsStrlen ( OnLoadFunction ) > 0 )
	{
		printf ( "\t%s();\n", OnLoadFunction );
	}
	else
	{
		printf ( "\twindow.focus();\n" );
	}
	printf ( "}\n" );
	printf ( "</script>\n" );
	
	webEndPage ();
}
