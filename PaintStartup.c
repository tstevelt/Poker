/*----------------------------------------------------------------------------
	Program : PaintStartup.c
	Author  : Tom Stevelt
	Date    : 2022-2024
	Synopsis: Startup screen for game setup. Javascript CalcAspectRatio()
				sets the screen sizing fields, used for subsequent dispalay.
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

void PaintStartup ()
{
	printf ( "<div class='startup'>\n" );

	nsStrcpy ( OnLoadFunction, "CalcAspectRatio" );
	printf ( "<input type='hidden' id='AspectRatio' name='AspectRatio'>\n" );
	printf ( "<input type='hidden' id='WindowWidth' name='WindowWidth'>\n" );
	printf ( "<input type='hidden' id='WindowHeight' name='WindowHeight'>\n" );

	printf ( "<div class='story'>\n" );
	printf ( "<h2>Five Card Stud Poker</h2>\n" );
	printf ( "<p>\n" );
	printf ( "Five Card Stud Poker with two to five players.  Everyone starts with $100.<br>\n" );
	printf ( "Beat the Millionaire is a two-player game. The Millionaire starts with $1,000,000 and you start with $100.<br>\n" );
	printf ( "Opponents <b>not so naive anymore</b>. They considers all your possible hole cards. And may fold or even bluff!<br>\n" );

	printf ( "<p>\n" );
	printf ( "<select id='GameType' name='GameType' onChange='javascript:OnSelectChange();'>\n" );
	printf ( "<option value='?'>-- select --</option>\n" );
	printf ( "<option value='2'>2 players</option>\n" );
	printf ( "<option value='3'>3 players</option>\n" );
	printf ( "<option value='4'>4 players</option>\n" );
	printf ( "<option value='5'>5 players</option>\n" );
	printf ( "<option value='M'>Beat the Millionaire</option>\n" );
	printf ( "</select>\n" );

	printf ( "<p>\n" );
	printf ( "<select id='HoleCards' name='HoleCards'>\n" );
	printf ( "<option value='1'>Standard 1 card face down</option>\n" );
	printf ( "<option value='2'>Two Hole 2 cards face down</option>\n" );
	printf ( "</select>\n" );

	printf ( "<P>\n" );
	printf ( "<input type='submit' id='submitStartup' name='submitStartup' value='Start Game' autofocus" );
	printf ( " onFocus='javascript:OnSelectChange();'>\n" );

	printf ( "</div>\n" );
	printf ( "</div>\n" );

}
