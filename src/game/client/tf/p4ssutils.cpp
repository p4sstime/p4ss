#include "cbase.h"
#include <algorithm>
#include <cstdio>
#include <memory>
#include "p4ssutils.h"
#include "dbg.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
using namespace vgui;

namespace P4ss
{
	// this will parse through the text to find the color codes
	// 
	// returns a string with the color codes removed
	// and the color changes in order
	//
	// colorChanges is an outParam which will be filled in with the color changes
	// because for some reason it's not move constructible
	//
	// IF ANYTHING FAILS IN THIS FUNCTION, the returned string will have a $ at
	// the position of parse failure, and the color changes MAY be inaccurately positioned.
	std::wstring GetColorChanges(const wchar_t *text, const int team, CUtlVector<ColorChange>& colorChanges)
	{
		Msg("Analyzing text: %ls\n", text);
		Color primaryColor;
		Color secondaryColor;
		if ( team == TF_TEAM_BLUE )
		{
			primaryColor = P4SS_BLUE;
			secondaryColor = P4SS_RED;
		}
		else if ( team == TF_TEAM_RED ) 
		{
			primaryColor = P4SS_RED;
			secondaryColor = P4SS_BLUE;
		}
		else {
			primaryColor = COLOR_TF_SPECTATOR;
			secondaryColor = P4SS_RED;
		}
		// create a malleable pointer
		const wchar_t *txt = text;
		std::wstring result;
		// OUTER LOOP OVER ALL TEXT
		outer: while (txt && *txt)
		{
			// found a color code?
			if ( *txt == L'#') {
				// move forward
				txt++;
				// is this a color code or just an escaped #?
				// (if two #s are in a row, and it's not following a color code, it means a single #)
				if (*txt == L'#')
				{
					// just a #, don't change color
					result.push_back(*txt);
					txt++;
					// loop again
					goto outer;
				}
				// check if it's a special case
				if (*txt == L'S')
				{
					// advance
					txt += 1;
					
					// handle special cases here
					switch (*txt)
					{
						case '\0': // end of string
							Warning("P4ss::GetColorChanges: reached end of string expecting special case\n");
							goto outer;
							break;
						case L'p': // primary team
							colorChanges.AddToTail(ColorChange { primaryColor, result.length() });
							break;
						case L's': // secondary team
							colorChanges.AddToTail(ColorChange { secondaryColor, result.length() });
							break;
						case L'r': // reset
							colorChanges.AddToTail(ColorChange { Color(255, 255, 255, 0), result.length() });
							break;
					}
					// done handling special case

					txt++;
					// optional ending # for localizers sake
					if (*txt == L'#') {
						txt++;
					}
					goto outer;
				}
				// this is a color code
				CUtlVector<long> colorFragments;
				// find the hex codes (two letters/digits)
				color_loop: for (int i = 0; i < 3; i++) {
					// are we at the end of the string?
					if (*txt == '\0') {
						// loop again, exiting since it's nul. 
						// it's fine to leave the string technically 
						// uncompleted with its malformed color code
						// because I feel like handling it will be more
						// effort than it's worth

						// we'll use the $ as a sign of malformed input
						Warning("P4ss::GetColorChanges: reached end of string expecting color code on color %d\n", i);
						result.push_back(L'$');
						goto outer;
					}
					// loop again if it's not a valid hex digit
					if (!iswxdigit(*txt)) {
						Warning("P4ss::GetColorChanges: reached non hex digit expecting color code on color %d\n", i);
						result.push_back(L'$');
						goto outer;
					}
					wchar_t char_one = *txt;

					txt++;
					// check again (holy wet code)

					// are we at the end of the string?
					if (*txt == '\0') {
						Warning("P4ss::GetColorChanges: reached end of string expecting color code on color %d\n", i);
						result.push_back(L'$');
						goto outer;
					}
					// loop again if it's not a valid hex digit
					if (!iswxdigit(*txt)) {
						Warning("P4ss::GetColorChanges: reached non hex digit expecting color code on color %d\n", i);
						result.push_back(L'$');
						goto outer;
					}

					wchar_t str[3] = { 0 };
					str[0] = char_one;
					str[1] = *txt;
					str[2] = L'\0';
					long color = std::wcstol(str, nullptr, 16);

					// successful, loop and add the color
					colorFragments.AddToTail(color);
					txt++;
				}

				// optional ending # for localizers sake
				if (*txt == L'#') {
					txt++;
				}
				// if all goes well, we should have 3 color fragments

				Assert(colorFragments.Count() == 3);
				
				Color outColor = Color(colorFragments[0], colorFragments[1], colorFragments[2], 255);
				colorChanges.AddToTail(ColorChange{ outColor, result.length() });
				goto outer;
			}

			// not a color code
			// add this text to the resulting string
			result.push_back(*txt);
			txt++;
		}

		return result;
	}
	std::wstring GetColorChangesShadow(const wchar_t *text, const int team, CUtlVector<ColorChange>& colorChanges)
	{
		auto result = GetColorChanges(text, team, colorChanges);

		// darken each color by 50%
		FOR_EACH_VEC(colorChanges, i) {
			ColorChange colorChange = colorChanges[i];
			// is this the special value to reset?
			if (colorChange.color == Color(255, 255, 255, 0)) {
				continue;
			}
			colorChange.color[0] = std::max(0, colorChange.color[0] - 128);
			colorChange.color[1] = std::max(0, colorChange.color[1] - 128);
			colorChange.color[2] = std::max(0, colorChange.color[2] - 128);
			colorChanges[i] = colorChange;
		}
		return result;
	}
		
	void SetColors(vgui::TextImage *textImage, CUtlVector<ColorChange>& colorChanges, Color defaultColor) {
		textImage->ClearColorChangeStream();
		FOR_EACH_VEC(colorChanges, i) {
			ColorChange colorChange = colorChanges[i];
			// is this the special value to reset?
			if (colorChange.color == Color(255, 255, 255, 0)) {
				textImage->AddColorChange(defaultColor, colorChange.idx);
				continue;
			}
			textImage->AddColorChange(colorChange.color, colorChange.idx);
		}
	};
	void ColorTextP4ss(vgui::TextImage *textImage, const wchar_t *text,  const int team)
	{
		textImage->ClearColorChangeStream();
		Color color;
		Color secondaryColor;
		if ( team == TF_TEAM_BLUE )
		{
			color = P4SS_BLUE;
			secondaryColor = P4SS_RED;
		}
		else if ( team == TF_TEAM_RED ) 
		{
			color = P4SS_RED;
			secondaryColor = P4SS_BLUE;
		}
		else {
			color = COLOR_TF_SPECTATOR;
			secondaryColor = P4SS_RED;
		}
		// We change the title's text color to match the colors of the matching
		// model panel backgrounds
		const wchar_t *txt = text;
		int iWChars = 0;
		while ( txt && *txt )
		{
			switch ( *txt )
			{
			case 0x06: // Assists
				textImage->AddColorChange( Color( 59, 196, 143, 255 ), iWChars );
				break;
			case 0x07: // Saves
				textImage->AddColorChange( Color( 255, 255, 0, 255 ), iWChars );
				break;
			case 0x08: // Intercepts
				textImage->AddColorChange( Color( 255, 0, 255, 255 ), iWChars );
				break;
			case 0x15: // Deathbomb
				textImage->AddColorChange( Color( 151, 224, 67, 255 ), iWChars );
				break;
			case 0x17: // Winstrat & Panacea
				textImage->AddColorChange( Color(77, 247, 4, 255), iWChars );
				break;
			case 0x14: // Steals
				textImage->AddColorChange( Color( 255, 128, 0, 255 ), iWChars );
				break;
			case 0x0F: // Splashes
				textImage->AddColorChange( Color( 91, 212, 180, 255 ), iWChars );
				break;
			case 0x13: // PRIMARY team color
				textImage->AddColorChange( color, iWChars );
				break;
			case 0x11: // SECONDARY team color
				textImage->AddColorChange( secondaryColor, iWChars );
				break;
			case 0x12: // Goals
				textImage->AddColorChange( Color( 59, 196, 59, 255 ), iWChars );
				break;
			case 0x01:
				textImage->AddColorChange( Color( 224, 217, 197, 255), iWChars );
				break;
			default:
				break;
			}

			txt++;
			iWChars++;
		}
	}
}