float menuXCoord3 = 0.915f; 
float titleScale = 0.75f;
float titleX = 0.820f;
float subtitleX = 0.782f;
//0.825000f, 0.511497f, 0.225000f, 0.788993f
float plusY = 0.014f;
float ScrollerY = 0.0090f;
float posX = 0.825000f, posY = 0.516497f, scaleX = 0.225000f, scaleY = 0.763993f;
int menualpha = 120;
float titleY = 0.014f;
float rightText_ = 0.9190f;
void addTitle(char* subtitle)//
{
	drawText("~italic~Re:Hyper Dx", 4, titleX, 0.182500f - plusY, 0.105000f, 0.789000f, 45, 255, 126, 255, true); // title
	drawText(subtitle, 6, 0.723002f, 0.248500f - plusY, 0.085000f, 0.343999f, 255, 255, 255, 255, false); // subtitle

	GRAPHICS::DRAW_RECT(0.752001f, 0.182500f - plusY, 0.001000f, 0.023000f, 228, 228, 228, 255); // corner left
	GRAPHICS::DRAW_RECT(0.760001f, 0.171500f - plusY, 0.016000f, 0.001250f, 228, 228, 228, 255); // corner left

	GRAPHICS::DRAW_RECT(0.887999f, 0.243501f - plusY, 0.015000f, 0.001000f, 228, 228, 228, 255); // corner right
	GRAPHICS::DRAW_RECT(0.894999f, 0.228500f - plusY, 0.001000f, 0.028000f, 228, 228, 228, 255); // corner right

	GRAPHICS::DRAW_RECT(0.823000f, 0.239500f - plusY, 0.081000f, 0.001250f, 255, 255, 255, 255); // white line under GTA V Engine
}
static void DRAW_SPRITE(char* texture, char * name, float X, float Y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture, 0);
	GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture);
	GRAPHICS::DRAW_SPRITE(texture, name, X, Y, width, height, rotation, r, g, b, a);
}
void addOption(char *option, char *info = NULL, char*buf = NULL, float plus = 0.0f)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;

	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{																	 /*0.085000f*//*0.555000*/
		drawText(option, 1, 0.731000f, (optionCount * 0.035f + 0.25400f) - plusY, 0.33f, 0.33f, 255, 255, 255, 255, false);
		if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(buf))
			drawText2(buf, 1, rightText_ - plus, (optionCount * 0.035f + 0.25400f) - plusY, 0.33f, 0.33f, 255, 255, 255, 255, false, true);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{																	 /*0.085000f*//*0.555000*/
		drawText(option, 1, 0.731000f, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.25400f) - plusY, 0.33f, 0.33f, 255, 255, 255, 255, false);
		if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(buf))
			drawText2(buf, 1, rightText_ - plus, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.25400f) - plusY, 0.33f, 0.33f, 255, 255, 255, 255, false, true);
	}
}

void addNameOption(char *option, char *info = NULL, char*buf = NULL)
{
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		if (optionPress)
			do_NameChange(option);
	}
}

void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	addOption(option, info, "→→→");
	if (currentOption == optionCount)
	{
		if (optionPress)
			changeSubmenu(newSubmenu);
	}	
	//if (currentOption <= maxOptions && optionCount <= maxOptions)
	//{
	//	GRAPHICS::DRAW_RECT(SubmenuThingX1, (optionCount * _0_035f + 0.210f) - _0_035f, 0.004f, _0_035f, bannerRectRed, bannerRectGreen, bannerRectBlue, 100);
	//}
	//else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	//{
	//	GRAPHICS::DRAW_RECT(SubmenuThingX1, ((optionCount - (currentOption - maxOptions)) * _0_035f + 0.210f) - _0_035f, 0.004f, _0_035f, bannerRectRed, bannerRectGreen, bannerRectBlue, 100);
	//}
}
void addFloatOption(char *option, float *var, float min, float max, float movement = 0.01f, char *info = NULL)
{
	char buf[80];
	strcpy(buf, "[");
	strcat(buf, FtoS(*var, 1 / 0.0001f));
	strcat(buf, " / ");
	strcat(buf, FtoS(max, 1 / 0.0001f));
	strcat(buf, "]");

	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		fastInstruction = true;
		lrInstruction = true;
		//squareInstruction = true;
		if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + movement;
		}
		else if (leftPress || (isPress(Dpad_Left) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - movement;
		}

		//if (squarePress)
		//{
		//	startKeyboard(0, "", (strlen(ItoS(max)) + 1));
		//	keybordFloatVar = var;
		//}
	}
}
void addByteOption(char *option, char *var, int min, int max, int movement = 0.01f, char *info = NULL, char* en = NULL)
{
	char buf[30];
	strcat(buf, "");
	strcpy(buf, "< ");
	strcat(buf, ItoS((int)*var, false));
	strcat(buf, " / ");
	strcat(buf, ItoS(max, false));
	strcat(buf, "> ");
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		fastInstruction = true;
		lrInstruction = true;
		//squareInstruction = true;
		if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + movement;
		}
		else if (leftPress || (isPress(Dpad_Left) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - movement;
		}

		//if (squarePress)
		//{
		//	startKeyboard(0, "", (strlen(ItoS(max)) + 1));
		//	(char*)keyboardIntVar = var;
		//}
	}
}

void addIntOption(char *option, int *var, int min, int max, int movement = 0.01f, char *info = NULL, char* en = NULL)
{
	char buf[100];
	strcpy(buf, "< ");
	strcat(buf, ItoS(*var, false));
	strcat(buf, " / ");
	strcat(buf, ItoS(max, false));
	strcat(buf, "> ");
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		fastInstruction = true;
		lrInstruction = true;
		squareInstruction = true;
		if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + movement;
		}
		else if (leftPress || (isPress(Dpad_Left) && isPress(Button_L1)))
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - movement;
		}

		if (squarePress)
		{
			startKeyboard(0, "", (strlen(ItoS(max)) + 1));
			keyboardIntVar = var;
		}
	}
}
float booloption1 = 0.025000f, booloption2 = 0.361999f, booloption3 = 0.020000f, booloption4 = 0.369999f;

void addCheckOption(char *option, bool var, char *info = NULL)
{
	addOption(option, info, "");
	if (var)
	{	
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			//GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			//drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			//GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);

		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, ((optionCount - (currentOption - maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
	}
}
float checkplusfloat_ = 0.0470f;
void addCheckFloat(char *option, bool var, float *var2, float min, float max, float movement = 0.1f, char* info = NULL)
{
	char FloatO[100];
	strcpy(FloatO, "[");
	strcat(FloatO, FtoS(*var2));
	strcat(FloatO, "]");

	addOption(option, info, FloatO, checkplusfloat_);
	if (var)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			//GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			//drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			//GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}

		if (currentOption == optionCount)
		{
			if (var)
			{
				fastInstruction = true;
				lrInstruction = true;
			}
			if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				if (*var2 >= max)
					*var2 = min;
				else
					*var2 = *var2 + movement;
			}
			else if (leftPress || (isPress(Dpad_Left) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				if (*var2 <= min)
					*var2 = max;
				else
					*var2 = *var2 - movement;
			}
		}
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);

		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, ((optionCount - (currentOption - maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
	}
}
void addCheckInt(char *option, bool var, int *var2, int min, int max, int movement = 1, char* info = NULL)
{
	char FloatO[30];
	if (var)
	{
		sprintf(FloatO, "[%i]%s", *var2, "");
	}
	else
	{
		strcpy(FloatO, "");
	}
	addOption(option, info, FloatO, checkplusfloat_);
	if (var)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			//GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			//drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			//GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}

		if (currentOption == optionCount)
		{

			if (var)
			{
				squareInstruction = true;
				fastInstruction = true;
				lrInstruction = true;
			}
			if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				if (*var2 >= max)
					*var2 = min;
				else
					*var2 = *var2 + movement;
			}
			else if (leftPress || (isPress(Dpad_Left) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				if (*var2 <= min)
					*var2 = max;
				else
					*var2 = *var2 - movement;
			}

			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardIntVar = var2;
			}
		}
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);

		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, ((optionCount - (currentOption - maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
	}
}
void addCharSwap(char *option, char** stringg, int *var, int min, int max, char* info = NULL)
{
	char buf[100];
	strcpy(buf, "[");
	strcat(buf, stringg[*var]);
	strcat(buf, "]");
	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		strcat(buf, "← →");
		udInstruction = true;
		lrInstruction = true;
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

void addCheckChar(char *option, bool var, char** stringg, int *varI, int min, int max, char* info = NULL)
{
	char Char[100];
	strcpy(Char, "[");
	strcat(Char, stringg[*varI]);
	strcat(Char, "]");
	addOption(option, info, Char, checkplusfloat_);
	if (var)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			//GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			//drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			//GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~On", 7, 0.878000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption2, 45, 255, 126, 166, false);
			GRAPHICS::DRAW_RECT(0.909000f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
		if (currentOption == optionCount)
		{
			lrInstruction = true;
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*varI >= max)
					*varI = min;
				else
					*varI = *varI + 1;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*varI <= min)
					*varI = max;
				else
					*varI = *varI - 1;
			}
		}
	}
	else
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			GRAPHICS::DRAW_RECT(0.896999f, (optionCount * 0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, (optionCount * 0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, (optionCount * 0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);

		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			GRAPHICS::DRAW_RECT(0.896999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.273499f /* 0.503500f */) - plusY, 0.049000f, booloption1, 29, 29, 29, 255);
			drawText("~italic~Off", 7, 0.897999f, ((optionCount - (currentOption - /* 16 */ maxOptions)) *0.035f + 0.261499f) - plusY, 0.085000f, booloption4, 107, 107, 107, 87, false);
			GRAPHICS::DRAW_RECT(0.885000f, ((optionCount - (currentOption - maxOptions)) *0.035f + 0.273500f /* 0.503500f */) - plusY, 0.022000f, booloption3, 60, 60, 60, 255);
		}
	}
}

void addSendOption(char *option, char *info = NULL, char *mark = NULL)
{
	addOption(option, info, mark);
	if (currentOption == optionCount)
	{
		if (optionPress)
		{
			MessageSend(option);
		}
	}
}
void addAttachObject(char *option, Hash hash, Entity _Entity, Vector3 _Loc, Vector3 _Rot, int _Bone, bool _Collision, char* info = NULL)
{
	addOption(option, info);
	if (optionPress && currentOption == optionCount)
	{
		Obj._Hash = hash;
		Obj._Entity = _Entity;
		Obj._Loc = _Loc;
		Obj._Rot = _Rot;
		Obj._Bone = _Bone;
		Obj.Collision = _Collision;
		Obj._Spawned = 0;
		Obj.flag = true;
	}
}

void addVehicleOption(char *hashname, char *info = NULL)
{
	char *VehicleName = UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(hashname)));
	if (strstr(VehicleName, "NULL"))
	{
		VehicleName = hashname;
	}
	addOption(VehicleName, info);

	if (optionPress && optionCount == currentOption)
	{	
		SpawnVehMethod_Hash = GAMEPLAY::GET_HASH_KEY(hashname);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(SpawnVehMethod_Hash) && STREAMING::IS_MODEL_VALID(SpawnVehMethod_Hash))
			VehSpawnMethod = true;
		else
			addMessageShow("モデルが読み込めませんでした。");
	}
}

void addFloatCoord(char *option, Entity obj, int Flag, float movement, bool human = false, char *info = NULL)
{
	char XYZ[40];
	Vector3 XYZ__ = ENTITY::GET_ENTITY_COORDS(obj, 1);
	if (Flag == X)
		snprintf(XYZ, 40, " [%s]%s", FtoS(XYZ__.x), "");
	else if (Flag == Y)
		snprintf(XYZ, 40, " [%s]%s", FtoS(XYZ__.y), "");
	else if (Flag == Z)
		snprintf(XYZ, 40, "[%s]%s", FtoS(XYZ__.z), "");
	float var;
	ENTITY::FREEZE_ENTITY_POSITION(obj, true);
	addOption(option, info, XYZ);
	if (currentOption == optionCount)
	{
		fastInstruction = true;
		lrInstruction = true;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(obj);
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
			if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, var, cor.y, cor.z, 1, 1, 1, 1);
			}
			else if ((leftPress || (isPress(Dpad_Left)) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, var, cor.y, cor.z, 0, 0, 1, 1);
			}
			break;
		case Y:
			var = cor.y;

			if (rightPress || (fastRightPress && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, var, cor.z, 0, 0, 1, 1);
			}
			else if (leftPress || (fastLeftPress && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, var, cor.z, 0, 0, 1,1);
			}
			break;
		case Z:
			var = cor.z;

			if (rightPress || (fastRightPress && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				var = var + movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, cor.y, var, 0, 0, 1, 1);
			}
			else if (leftPress || (fastLeftPress && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				var = var - movement;
				ENTITY::SET_ENTITY_COORDS(obj, cor.x, cor.y, var, 0, 0, 1, 1);
			}
			break;
		}
	}
}

void addKeyboardOption(char *option, int action, char *defaultText, int maxLength, char *info = NULL, char *buf = NULL, int language = 1)
{

	addOption(option, info, buf);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			startKeyboard(action, defaultText, maxLength, language);
	}
}

void addFloatRotation(char *option, Entity obj, int Flag, float movement, char* info = NULL)
{
	char XYZ[40];
	Vector3 XYZ__ = ENTITY::GET_ENTITY_ROTATION(obj, 2);
	if (Flag == X)
		snprintf(XYZ, 40, "[%s]%s", FtoS(XYZ__.x), "");
	else if (Flag == Y)
		snprintf(XYZ, 40, "[%s]%s", FtoS(XYZ__.y), "");
	else if (Flag == Z)
		snprintf(XYZ, 40, "[%s]%s", FtoS(ENTITY::GET_ENTITY_HEADING(obj)), "");
	addOption(option, info, XYZ);
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(obj);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, true, true);
	ENTITY::FREEZE_ENTITY_POSITION(obj, true);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		fastInstruction = true;

		switch (Flag)
		{
		case X:

			if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
			{
				Vector3 XYZ__ = ENTITY::GET_ENTITY_ROTATION(obj, 1);
				playSound("NAV_UP_DOWN");
				XYZ__.x = XYZ__.x + movement;

				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 1, true);
			}
			else if ((leftPress || (isPress(Dpad_Left)) && isPress(Button_L1)))
			{
				Vector3 XYZ__ = ENTITY::GET_ENTITY_ROTATION(obj, 1);
				playSound("NAV_UP_DOWN");
				XYZ__.x = ENTITY::GET_ENTITY_COORDS(obj, 1).x - movement;

				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 1, true);
			}
			break;
		case Y:
			if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
			{
				playSound("NAV_UP_DOWN");
				XYZ__.y = XYZ__.y + movement;

				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 2, true);
			}
			else if ((leftPress || (isPress(Dpad_Left)) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				XYZ__.y = XYZ__.y - movement;

				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 2, true);
				
			}
			break;
		case Z:
			if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
			{
				playSound("NAV_UP_DOWN");
				XYZ__.z = ENTITY::GET_ENTITY_HEADING(obj) + movement;
				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 2, true);
			}
			else if ((leftPress || (isPress(Dpad_Left)) && isPress(Button_L1)))
			{
				playSound("NAV_UP_DOWN");
				XYZ__.z = ENTITY::GET_ENTITY_HEADING(obj) - movement;
				ENTITY::SET_ENTITY_ROTATION(obj, XYZ__.x, XYZ__.y, XYZ__.z, 2, true);
			}
			break;
		}
	}
}

void addObjectCharSwap(char *option, char **From, char **From2, int*var, int min, int max, char *info = "")
{
	char bug[200];
	sprintf(bug, "%s [%i/%i]%s", From2[*var], *var + 1, max + 1, "");
	addOption(option, info, bug);
	if (currentOption == optionCount)
	{
		if (currentOption == optionCount && optionPress)
		{
			Create_Hash = GAMEPLAY::GET_HASH_KEY(From[*var]);
			Create_Map_string = From[*var];
			Create_Map_strings = From2[*var];
			Create_Map = true;
		}

		if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress || fastRightPress && isPress(Button_L1))
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}

void add_LoadedObjectCharSwap(char *option, int*var, int min, int max, int address, char *info = "")
{
	char bug[200];
	char* hash = PS3::ReadString_1(address + (0x50 * *var));
	char* name = PS3::ReadString_1(address + 0x10000 + (0x50 * *var));
	sprintf(bug, "%s [%i/%i]%s", name, *var + 1, max + 1, "");
	addOption(option, info, bug);
	if (currentOption == optionCount)
	{
	
		if (currentOption == optionCount && optionPress)
		{
			Create_Hash = GAMEPLAY::GET_HASH_KEY(hash);
			Create_Map_string = hash;
			Create_Map = true;
		}

		if (rightPress || isPress(Dpad_Right) && isPress(Button_L1))
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress || fastRightPress && isPress(Button_L1))
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}

void SpawnObjOption(char *option, char *obj, char *aa, char *info = "")
{
	addOption(option, info, aa);
	if (currentOption == optionCount && optionPress)
	{
		Create_Hash = GAMEPLAY::GET_HASH_KEY(obj);
		Create_Map_string = option;
		Create_Map = true;
	}
}
