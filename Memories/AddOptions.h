#pragma region addOption

void addTitle(char *title)
{
	drawText(title, bannerTextFont, menuXCoord, TitleTextY, TitleSize, TitleSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	//GRAPHICS::DRAW_RECT(menuXCoord, Title01175f, Option019f, Title0083f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
	drawGlare();
}

void addOption(char *option, char *info = NULL, char* mark = "")
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	

	if (FlagIndexes == AdminFlag)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			if (currentOption == optionCount)
			{
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
			}
			else
			{
				drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * optionCount) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			}
			drawText(mark, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			if (currentOption == optionCount)
			{
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR1, PerpleG1, PerpleB1, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
			}
			else
			{
				drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			}
			drawText(mark, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		}
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			if (currentOption == optionCount)
			{
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
			}
			else
			{
				drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * optionCount) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			}
			drawText(mark, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			if (currentOption == optionCount)
			{
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
				drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
			}
			else
			{
				drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			}
			drawText(mark, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		}
	}
}

bool ButtonChange1 = true;
bool ButtonChange2 = false;
bool ButtonChange3 = false;
bool ButtonChange4 = false;
bool ButtonChange5 = false;
bool ButtonChange6 = false;

void addChangeControlOption(char*option, bool b00l, int Button_1, int Button_2)
{
	
	addOption(option);
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	if (currentOption == optionCount && optionPress)
	{
		Button1 = Button_1;
		Button2 = Button_2;
	}
}

void addOption2(char *option, char *option2, char *info = NULL, char* mark = "")
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (currentOption == optionCount)
		{
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * currentOption) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
		}
		else
		{
			drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * optionCount) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		}
		drawText(mark, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (currentOption == optionCount)
		{
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 + 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75 - 1) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X + 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X - 1) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, PerpleR, PerpleG, PerpleB, 255, false, false, false);
			drawText(option, bannerTextFont, PixelX(Menu_X) - PixelX(130) + FixOptionCurrentX + PlusAllX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, TextSize04f, TextSize04f, 240, 240, 240, 240, false, false, false);
		}
		else
		{
			drawText(option, optionsFont, PixelX(Menu_X) - PixelX(130) + PlusAllX + FixOptionCurrentX, PixelY(75) + PixelY(OptionPlusIndex * (optionCount - (currentOption - maxOptions))) + FixOptionCurrentY, 0.4, 0.4, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		}
		drawText(mark, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
}

void addBoolOption(char *option, bool b00l, char *info = NULL)
{
	if (b00l)
	{
		addOption(option, info, "~g~[ON]");
	}
	else
	{
		addOption(option, info, "~r~[OFF]");
	}
	
	//DrawSprite("mprankbadge", "globe", textXCoord, (optionCount * MenuFloat035 + MenuFloat0125), 0.03, 0.04, 0, optionsRed, optionsGreen, optionsBlue, optionsOpacity);
	/*if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", CheckBox.LocX, (optionCount * MenuFloat035 + MenuFloat0125) + pluccheckbox + BodyDownFloat, CheckBox.SizeX, CheckBox.SizeY, 0, 100, 71, 148, optionsOpacity);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", CheckBox.LocX, (optionCount * MenuFloat035 + MenuFloat0125) + pluccheckbox + BodyDownFloat, CheckBox.SizeX, CheckBox.SizeY, 0, 171, 36, 35, optionsOpacity);
		}
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", CheckBox.LocX, ((optionCount - (currentOption - maxOptions)) * MenuFloat035 + MenuFloat0125) + pluccheckbox + BodyDownFloat, CheckBox.SizeX, CheckBox.SizeY, 0, 100, 71, 148, optionsOpacity);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", CheckBox.LocX, ((optionCount - (currentOption - maxOptions)) * MenuFloat035 + MenuFloat0125) + pluccheckbox + BodyDownFloat, CheckBox.SizeX, CheckBox.SizeY, 0, 171, 36, 35, optionsOpacity);
		}
	}*/


}

void addCheckBool(char *option, bool b00l, char *info = NULL)
{
	addOption(option);
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (b00l)
		{
			
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{			
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
}

void addCharBoolOption(char *option, bool b00l, char** right, int *var, int min, int max, char *info = NULL)
{
	char buf[60];
	snprintf(buf,60, "%s ~m~[%i/%i]", right[*var], *var, max);
	addOption(option);
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (b00l)
		{

			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	if (currentOption == optionCount)
	{
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}

	}
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(buf, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(buf, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
}


void addIntOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL, bool fastPress = true)
	{
		char buf[30];
		strcpy(buf, "< ");
		strcat(buf, ItoS(*var));
		strcat(buf, " / ");
		strcat(buf, ItoS(max));
		strcat(buf, " >");
		addOption(option, info, buf);
		if (currentOption == optionCount)
		{
			lrInstruction = true;
			if (fastPress)
			{
				if (fastRightPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var >= max)
						*var = min;
					else
						*var = *var + 1;
				}
				else if (fastLeftPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var <= min)
						*var = max;
					else
						*var = *var - 1;
				}
			}
			else
			{
				if (rightPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var >= max)
						*var = min;
					else
						*var = *var + 1;
				}
				else if (leftPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var <= min)
						*var = max;
					else
						*var = *var - 1;
				}
			}
			if (keyboard)
			{
				squareInstruction = true;
				if (squarePress)
				{
					startKeyboard(0, "", (strlen(ItoS(max)) + 1));
					keyboardIntVar = var;
				}
			}
		}
	}

void addintbooloption(char*option, int *var, int min, int max, bool keyboard, bool b00l , bool fastPress = true)
{
	char buf[30];
	sprintf(buf, "%s: < %i >", option, *var);
	addOption(buf);
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, (optionCount * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		if (b00l)
		{
			DrawSprite("commonmenu", "shop_box_tick", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
		else
		{
			DrawSprite("commonmenu", "shop_box_blank", Checkboxz, ((optionCount - (currentOption - maxOptions)) * CheckBoxPlus2) + CheckBoxPlus, 0.03, 0.05, 0, 255, 255, 255, 255);
		}
	}

	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (fastPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1;
			}
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardIntVar = var;
			}
		}
	}
}


void addFloatOption(char *option, float *var, float min, float max, bool holdPress, float movement = 0.01f, char *info = NULL, bool CustomPointer = false, float FloatPointer = 0.01f)
{
	float XXXXPointer = CustomPointer ? FloatPointer : (1 / movement);
	char buf[30];
	strcpy(buf, "< ");
	strcat(buf, FtoS(*var, 1 / 0.0001f));
	strcat(buf, " / ");
	strcat(buf, FtoS(max, 1 / 0.0001f));
	strcat(buf, " >");
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + movement;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - movement;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + movement;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - movement;
			}
		}
	}
}

void addFloatCheckOption(char *option, bool b00l, float *var, float min, float max, bool holdPress, float movement = 0.01f, char *info = NULL, bool CustomPointer = false, float FloatPointer = 0.01f)
{
	char buf[30];
	if (b00l)
	{
		float XXXXPointer = CustomPointer ? FloatPointer : (1 / movement);

		strcpy(buf, "< ");
		strcat(buf, FtoS(*var, 1 / 0.0001f));
		strcat(buf, " / ");
		strcat(buf, FtoS(max, 1 / 0.0001f));
		strcat(buf, " >");
		addOption(option, info, buf);

		if (currentOption == optionCount)
		{
			lrInstruction = true;
			if (holdPress)
			{
				if (fastRightPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var >= max)
						*var = min;
					else
						*var = *var + movement;
				}
				else if (fastLeftPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var <= min)
						*var = max;
					else
						*var = *var - movement;
				}
			}
			else
			{
				if (rightPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var >= max)
						*var = min;
					else
						*var = *var + movement;
				}
				else if (leftPress)
				{
					playSound("NAV_UP_DOWN");
					if (*var <= min)
						*var = max;
					else
						*var = *var - movement;
				}
			}
		}
	}
	else
	{
		strcpy(buf, "< OFF >");
		addOption(option, info, buf);
	}

}


void RealTimeFloatWrite(char *option, float *var, int Address, float min, float max, float movement = 0.01f, char* info = NULL, bool CustomPointer = false, float FloatPointer = 0.01f)
{
	float XXXXPointer = CustomPointer ? FloatPointer : 1 / movement;
	char buf[30];
	strcpy(buf, "< ");
	strcat(buf, FtoS(*var, XXXXPointer));
	strcat(buf, " / ");
	strcat(buf, FtoS(max, XXXXPointer));
	strcat(buf, " >");
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (fastRightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + movement;

			PS3::WriteFloat(Address, *var);
		}
		else if (fastLeftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - movement;

			PS3::WriteFloat(Address, *var);
		}
		else if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + movement;

			PS3::WriteFloat(Address, *var);
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - movement;

			PS3::WriteFloat(Address, *var);
		}
	}
}
float var = 0;
void addFloatCoord(char *option, Entity obj, int Flag, float movement, bool human = false)
{
	addOption(option, "");
	if (currentOption == optionCount)
	{
		RequestNetworkControl(obj);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, true, true);
		Vector3 cor = ENTITY::GET_ENTITY_COORDS(obj, 1);
		if (human)
		{
			cor.z = cor.z - 1;
		}

		switch (Flag)
		{
		case X:
			var = cor.x;

			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, var, cor.y, cor.z, 0, 0, 0, 0);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, var, cor.y, cor.z, 0, 0, 0, 0);
			}
			break;
		case Y:
			var = cor.y;

			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, var, cor.z, 0, 0, 0, 0);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, var, cor.z, 0, 0, 0, 0);
			}
			break;
		case Z:
			var = cor.z;

			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, cor.y, var, 0, 0, 0, 0);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, cor.y, var, 0, 0, 0, 0);
			}
			break;
		}
	}
}

void addFloatRotation(char *option, Entity obj, int Flag, float movement, bool reset = false, char* info = NULL)
{
	addOption(option, info);
	RequestNetworkControl(obj);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, true, true);
	if (currentOption == optionCount)
	{
		Vector3 Rotation = ENTITY::GET_ENTITY_ROTATION(obj, true);

		switch (Flag)
		{
		case X:

			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.x = Rotation.x + movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.x = Rotation.x - movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			break;
		case Y:
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.y = Rotation.y + movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.y = Rotation.y - movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			break;
		case Z:
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.z = Rotation.z + movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				Rotation.z = Rotation.z - movement;

				ENTITY::SET_ENTITY_ROTATION(obj, Rotation.x, Rotation.y, Rotation.z, 0, true);
			}
			break;
		}
	}
}

void addKeyboardOption(char *option, int action, char *defaultText, int maxLength, char *info = NULL)
	{
		addOption(option, info);
		if (currentOption == optionCount)
		{
			xInstruction = true;
			if (optionPress)
				startKeyboard(action, defaultText, maxLength);
		}
	}

void addInstruction(int button, char *text)
	{
		if (!instructionsSetupThisFrame)
		{
			instructionsSetup();
			instructionsSetupThisFrame = true;
		}
		GRAPHICS::_0x215ABBE8(mov, "SET_DATA_SLOT");
		GRAPHICS::_0x716777CB(instructCount);
		GRAPHICS::_0x716777CB(button);
		GRAPHICS::_0x3AC9CB55("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		GRAPHICS::_0x386CE0B8();
		GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		instructCount++;
	}

void addCharSwap(char *option, char **From, int*var, int min, int max, char *info = NULL, bool Japanese = false)
{
	char IamGod[50];
	addOption(option, info);
	if (currentOption == optionCount)
	{
		if (Japanese)
		{
			sprintf(IamGod, "~w~%s ~t~[%i/%i] ~d~← →", UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(From[*var]))), *var + 1, max + 1);
		}
		else
		{
			sprintf(IamGod, "~w~%s ~t~[%i/%i] ~d~← →", From[*var], *var + 1, max + 1);
		}
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
	else
	{
		if (Japanese)
		{
			sprintf(IamGod, "~w~%s ~t~[%i/%i]", UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(From[*var]))), *var + 1, max + 1);
		}
		else
		{
			sprintf(IamGod, "~w~%s ~t~[%i/%i]", From[*var], *var + 1, max + 1);
		}
	}

	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(IamGod, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(IamGod, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}

}

void SpawnObjOption(char *option, char *obj, char *aa)
{
	addOption(option, "", aa);
	if (currentOption == optionCount && optionPress)
	{
		MapObjectName = obj;
		CreateMap = true;
	}
}

void addObjectCharSwap(char *option, char **From, char **From2, int*var, int min, int max)
{
	char bug[30];
	sprintf(bug, "~w~%s ~t~[%i/%i]", From2[*var], *var + 1, max + 1);
	addOption(option, "", bug);
	if (currentOption == optionCount)
	{
		if (currentOption == optionCount && optionPress)
		{
			MapObjectName = From[*var];
			CreateMap = true;
		}

		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}

void addCarCharSwap(char *option, char **From, int*var, int min, int max, char *info = NULL, bool Japanese = false)
{
	char IamGod[50];
	addOption(option, info);
	if (currentOption == optionCount)
	{
		sprintf(IamGod, "~w~%s ~t~[%i/%i] ~d~← →", UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(From[*var]))), *var + 1, max + 1);
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}

		if (optionPress)
		{
			Vehicle_String = From[*var];
			Loading_Vehicle = true;
		}
	}
	else
	{
		sprintf(IamGod, "~w~%s ~t~[%i/%i] ~d~← →", UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(From[*var]))), *var + 1, max + 1);
	}

	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(IamGod, optionsFont, 0.9490f + PlusAllX, (optionCount * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(IamGod, optionsFont, 0.9490f + PlusAllX, ((optionCount - (currentOption - maxOptions)) * Option0035f + Option0125f), OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}

}

void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	addOption(option, info, ">>");
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			changeSubmenu(newSubmenu);
	}
}

void addCompChangeModelSubmenuOption(char *option, int Hash, int ModelHash, char *info = NULL)
{
	CompModelName = option;
	addOption(option, info, ">>");
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			changeSubmenu(CompModelChangerMenu);
	}
}

void addSendOption(char *option, char *info = NULL, char *mark = NULL)
{
	addOption(option, info, mark);
	if (currentOption == optionCount)
	{
		if (optionPress)
		{
			char Message[100];
			strcpy(Message, ColorMessageList[ColorMessageVar]);
			strcat(Message, option);
			int NetHandleBuffer = 0x10070200;
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
			NETWORK::NETWORK_SEND_TEXT_MESSAGE(Message, NetHandleBuffer);
		}
	}
}

void addOptionP(char *option, char* pedname = NULL, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		if (optionPress)
		{
			PedName2 = option;
			PedName = pedname;
			PedSpawn = true;
		}
	}
}

void addNameOption(char* name, char* info = NULL)
{
	addOption(name, info, "名前");
	if (currentOption == optionCount)
	{
		if (optionPress)
		{
			PS3::WriteString(0x41143344, name);
			PS3::WriteString(0x1FF248C, name);
			PS3::WriteString(0x200255C, name);
			NotifyDown("変更完了!\nセッションを移動してください！", 1000);
		}
	}
}
#pragma endregion