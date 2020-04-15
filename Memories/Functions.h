
#pragma region License Func



bool IsMacTMP;
char IsMacRet[30];
char IsMacReturn[30];
char MacAddress300[30];
int LisenceTmpDDA2, LisenceTmpDDA3;
int PlayerIP;
char* getMacAddress()
{
	CellNetCtlInfo netInfo1;
	cellNetCtlGetInfo(CELL_NET_CTL_INFO_ETHER_ADDR, &netInfo1);
	const char * Mac = (const char *)netInfo1.ether_addr.data;
	char MacAddress3[30];
	sprintf(MacAddress3, "%02X%02X%02X%02X%02X%02X", Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF);
	return MacAddress3;
}

char *SendToPHP(char *Lisence)
{
	char* PhantomURL[] = { "h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",":","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","s","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","r","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","x","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","7","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","1","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","s","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","9","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","x","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","a","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","i","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","n","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","j","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","P","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","a","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","n","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼" };
	char NetReqURLBuf[200];
	sprintf(NetReqURLBuf, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", PhantomURL[0], PhantomURL[2], PhantomURL[4], PhantomURL[6], PhantomURL[8], PhantomURL[10], PhantomURL[12], PhantomURL[14], PhantomURL[16], PhantomURL[18], PhantomURL[20], PhantomURL[22], PhantomURL[24], PhantomURL[26], PhantomURL[28], PhantomURL[30], PhantomURL[32], PhantomURL[34], PhantomURL[36], PhantomURL[38], PhantomURL[40], PhantomURL[42], PhantomURL[44], PhantomURL[46], PhantomURL[48], PhantomURL[50], PhantomURL[52], PhantomURL[54], PhantomURL[56], PhantomURL[58], PhantomURL[60], PhantomURL[62], PhantomURL[64], PhantomURL[66], PhantomURL[68], PhantomURL[70], PhantomURL[72], PhantomURL[74], PhantomURL[76]);
	char URLKakunou[300];
	char URLKakunou2[300];
	char MacAddress[30];
	strcpy(URLKakunou, NetReqURLBuf);
	strcat(URLKakunou, "Phantom.php");
	strcat(URLKakunou, "?License=");
	strcat(URLKakunou, Lisence);
	strcat(URLKakunou, "&MAC=");
	strcat(URLKakunou, IsMacReturn);
	network::sendRequest(URLKakunou);

	sleep(1000);

	strcpy(URLKakunou2, NetReqURLBuf);
	strcat(URLKakunou2, "AccountData/");
	strcat(URLKakunou2, Lisence);
	strcat(URLKakunou2, ".txt");
	network::sendRequest(URLKakunou2);
	return network::getResponse();
}

char *SendToMente()
{
	char* PhantomURL[] = { "h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",":","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","s","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","r","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","x","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","7","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","1","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","s","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","9","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","x","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","a","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","i","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","n","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","j","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","P","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","a","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","n","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼" };
	char NetReqURLBuf[200];
	sprintf(NetReqURLBuf, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", PhantomURL[0], PhantomURL[2], PhantomURL[4], PhantomURL[6], PhantomURL[8], PhantomURL[10], PhantomURL[12], PhantomURL[14], PhantomURL[16], PhantomURL[18], PhantomURL[20], PhantomURL[22], PhantomURL[24], PhantomURL[26], PhantomURL[28], PhantomURL[30], PhantomURL[32], PhantomURL[34], PhantomURL[36], PhantomURL[38], PhantomURL[40], PhantomURL[42], PhantomURL[44], PhantomURL[46], PhantomURL[48], PhantomURL[50], PhantomURL[52], PhantomURL[54], PhantomURL[56], PhantomURL[58], PhantomURL[60], PhantomURL[62], PhantomURL[64], PhantomURL[66], PhantomURL[68], PhantomURL[70], PhantomURL[72], PhantomURL[74], PhantomURL[76]);
	char URLKakunou[300];
	strcpy(URLKakunou, NetReqURLBuf);
	strcat(URLKakunou, "Command.txt");
	network::sendRequest(URLKakunou);
	return network::getResponse();
}


int FlagIndexes = 0;
int MainFlagIndex;
bool DropKickDetected;
int IsMenteFlag(char *Value)
{
	if (strstr(Value, "0x7F000000") != NULL)
	{
		MainFlagIndex = 0;
	}
	else if (strstr(Value, "0x7F000001") != NULL)
	{
		MainFlagIndex = 1;
	}
	else
	{
		MainFlagIndex = 2;
	}
}
int ChangeFlagFromReturnValue(char *Value)
{
	if (strstr(Value, "0xB8003000") != NULL)
	{
		FlagIndexes = AdminFlag;
	}
	else if (strstr(Value, "0xB8001000") != NULL)
	{
		FlagIndexes = NormalFlag;
	}
	else if (strstr(Value, "0xF8004000") != NULL)
	{
		FlagIndexes = BannedFlag;
	}
	else if (strstr(Value, "0xF8000003") != NULL)
	{
		FlagIndexes = CantLogin;
	}
	else if (strstr(Value, "0xF8000002") != NULL)
	{
		FlagIndexes = UsedLicense;
	}
	else if (strstr(Value, "0xF8000001") != NULL)
	{
		FlagIndexes = InvilidLicenseError;
	}
	else
	{
		FlagIndexes = NetworkError;
	}
}
#pragma endregion
#pragma region Effect
int EffectColor[4];
float EffectColorFloat[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
#pragma endregion
void drawGlare(float PositionX = Glare.LocX, float PositionY = Glare.LocY, float width = Glare.SizeX, float height = Glare.SizeY, int r = 255, int g = 255, int b = 255)
{
	gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(gGlareHandle, "SET_DATA_SLOT");
	//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(-GlareParam);
	GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();

	GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, (PositionX - xMovieFix) + PlusAllX, PositionY - yMovieFix, width, height, r, g, b, 255, 0);
	GRAPHICS::_0x3FE33BD6();
}

#pragma region メニューの描画メソッド
void drawText(char *text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool Right = false, bool Outline = true)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_CENTRE(center);
	//UI::SET_TEXT_RIGHT_JUSTIFY(Right);
	if (Right)
	{
		UI::_0x68CDFA60(2);
		if (PlusAllX != 0.0f)
		{
			UI::SET_TEXT_WRAP(OOO, LLL + PlusAllX);
		}
		else
		{
			UI::SET_TEXT_WRAP(OOO, LLL);
		}
		//UI::SET_TEXT_RIGHT_JUSTIFY(Right);
	}
	else
	{
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
	}

	if (Outline)
	{
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
	}
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x + PlusAllX, y);
}

void DrawSprite(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture));
	GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}

void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(mov, "CLEAR_ALL");
	GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	GRAPHICS::_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_0x716777CB(200);
	GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount = 0;
}

void instructionsClose()
{
	GRAPHICS::_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	GRAPHICS::_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(80);
	GRAPHICS::POP_SCALEFORM_MOVIE_FUNCTION_VOID();
}

float PixelX(int Input)
{
	return (float)Input / (float)1280;
}

float PixelY(int Input)
{
	return (float)Input / (float)720;
}

namespace DrawingMenus
{
	void ViewAllOptionText()
	{
		sprintf(ViewAllOption, "%i / %i", currentOption, optionCount);
		drawText(ViewAllOption, 1, RightJusty, SubTitleTextLocY, OptionTextSize, OptionTextSize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
	}

	void normalMenuActions()
	{
#pragma region ボタン操作無効
		UI::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);
#pragma endregion
		GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, FreedomYCoord, Option019f, FreedomYSize, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity1); //Background
		if (optionCount > maxOptions)
		{
			if (currentOption > maxOptions)
			{
				GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, ((maxOptions * Option0035f) + Option01415f) + ScrollBarPlus, Option019f, Option0035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			}
			else
			{
				GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, ((currentOption * Option0035f) + Option01415f) + ScrollBarPlus, Option019f, Option0035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			}
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, ((currentOption * Option0035f) + Option01415f) + ScrollBarPlus, Option019f, Option0035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
		}
		if (FlagIndexes == AdminFlag)
		{
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine1Coord, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // X Line
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine2Coord, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // X Line 2
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine3Coord, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Title Line
			GRAPHICS::DRAW_RECT(YLine1Coord + PlusAllX, FreedomYCoord, LineSize2, FreedomYSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Y Line
			GRAPHICS::DRAW_RECT(YLine2Coord + PlusAllX, FreedomYCoord, LineSize2, FreedomYSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Y Line 2
			if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
			{
				drawText(infoText, optionsFont, menuXCoord, FreedomInfoText, OptionTextSize, OptionTextSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
				GRAPHICS::DRAW_RECT(menuXCoord, FreedomInfobox, Option019f + 0.0075f, Option0035f, PerpleR1, PerpleG1, PerpleB1, bannerRectOpacity); //Info Box	
			}
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine1Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine2Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line 2
			GRAPHICS::DRAW_RECT(menuXCoord + PlusAllX, XLine3Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Title Line
			GRAPHICS::DRAW_RECT(YLine1Coord + PlusAllX, FreedomYCoord, LineSize2, FreedomYSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line
			GRAPHICS::DRAW_RECT(YLine2Coord + PlusAllX, FreedomYCoord, LineSize2, FreedomYSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line 2
			if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
			{
				drawText(infoText, optionsFont, menuXCoord, FreedomInfoText, OptionTextSize, OptionTextSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
				GRAPHICS::DRAW_RECT(menuXCoord, FreedomInfobox, Option019f + 0.0075f, Option0035f, PerpleR, PerpleG, PerpleB, bannerRectOpacity); //Info Box	
			}
		}
		
	}
}
int EXPLOSIONVAR;
char *EXPLOSION_TYPES[] = {
	"EXPLOSION_GRENADE", //0
	"EXPLOSION_GRENADELAUNCHER",//1
	"EXPLOSION_STICKYBOMB",//2
	"EXPLOSION_MOLOTOV",//3
	"EXPLOSION_ROCKET",//4
	"EXPLOSION_TANKSHELL",//5
	"EXPLOSION_HI_OCTANE",//6
	"EXPLOSION_CAR",//7
	"EXPLOSION_PLANE",//8
	"EXPLOSION_PETROL_PUMP",//9
	"EXPLOSION_BIKE",//10
	"EXPLOSION_DIR_STEAM",//11
	"EXPLOSION_DIR_FLAME",//12
	"EXPLOSION_DIR_WATER_HYDRANT",//13
	"EXPLOSION_DIR_GAS_CANISTER",//14
	"EXPLOSION_BOAT",//15
	"EXPLOSION_SHIP_DESTROY",//16
	"EXPLOSION_TRUCK",//17
	"EXPLOSION_BULLET",//18
	"EXPLOSION_SMOKEGRENADELAUNCHER",//19
	"EXPLOSION_SMOKEGRENADE",//20
	"EXPLOSION_BZGAS",
	"EXPLOSION_FLARE",
	"EXPLOSION_GAS_CANISTER",
	"EXPLOSION_EXTINGUISHER",
	"EXPLOSION_PROGRAMMABLEAR",
	"EXPLOSION_TRAIN",
	"EXPLOSION_BARREL",
	"EXPLOSION_PROPANE",
	"EXPLOSION_BLIMP",
	"EXPLOSION_DIR_FLAME_EXPLODE",
	"EXPLOSION_TANKER",
	"EXPLOSION_PLANE_ROCKET",
	"EXPLOSION_VEHICLE_BULLET",
	"EXPLOSION_GAS_TANK",
	"EXPLOSION_BIRD_CRAP"
};
namespace Timers
{
	bool newTimerTick = true, newTimerTick2 = true;	
	int maxTimerCount, maxTimerCount2;

	void SetupTimer(int tickTime)
	{
		if (newTimerTick) {
			maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
			newTimerTick = false;
		}
	}

	bool IsTimerReady()
	{
		return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
	}

	void ResetTimer()
	{
		newTimerTick = true;
	}

	void SetupTimer2(int tickTime)
	{
		if (newTimerTick2) {
			maxTimerCount2 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
			newTimerTick2 = false;
		}
	}

	bool IsTimerReady2()
	{
		return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount2;
	}

	void ResetTimer2()
	{
		newTimerTick2 = true;
	}
}
#pragma endregion

#pragma region Math
#define PI (3.14159265359)
float Factorial(int Value)
{
	int Ret = 1;
	for (int i = Value; i > 0; i--)
		Ret = Ret * i;
	return Ret;
}

float myPow(float Value, int Pow)
{
	float Ret = 1;
	for (int i = 0; i < Pow; i++)
		Ret = Ret * Value;
	return Ret;
}
float mySin(float AnglesRad, int Accuracy)
{
	float i = AnglesRad; float Ret = 0;
	bool Minus = false;
	for (int j = 1; j <= Accuracy; j += 2)
	{
		if (!Minus)
			Ret += myPow(i, j) / Factorial(j);
		else
			Ret -= myPow(i, j) / Factorial(j);
		Minus = !Minus;
	}
	return Ret;
}

float myCos(float AnglesRad, int Accuracy)
{
	float Rad = (PI / 2) - AnglesRad;
	return mySin(Rad, Accuracy);
}

float myTan(float AnglesRad, int Accuracy)
{
	float sinus = mySin(AnglesRad, Accuracy);
	float cosinus = myCos(AnglesRad, Accuracy);
	return sinus / cosinus;
}
#pragma endregion

#pragma region メニューの構成部分 (メソッド)
void NotifyDown(char*msg, int timer = 2000)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(timer, 1);
}

void NotifyLeft(char* msg)
{
	UI::_0x574EE85C("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_SET_NOTIFICATION_MESSAGE("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", true, 4, "PHANTOM", "");
	UI::_DRAW_NOTIFICATION(false, true);
}

//CHAR_DEFAULT
int HelpIndex;
void HelpTextDraw(char *msg)
{
	char *script = SCRIPT::GET_THIS_SCRIPT_NAME();
	if (!strcmp(script, "ingamehud"))
	{
		drawText(msg, 0, 0.15f, (HelpIndex * 0.025) + 0.05, 0.4, 0.4, 255, 255, 255, 255, true);
		HelpIndex++;
	}
}

int getOption()
{
	if (optionPress)
		return currentOption;
	else return 0;
}

void resetVars()
{

	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	squarePress = false;
}

void GlobalHack(int AAA, int BBB)
{
	switch (BBB)
	{
	case 0:
		PS3::Write_Global(AAA + (selectedPlayer), 1); break;
	case 1: 
		PS3::Write_Global(AAA + (selectedPlayer + 1), 1); break;
	case 2: 	
		PS3::Write_Global(AAA + (selectedPlayer), 9999); break;
	case 3:
		PS3::Write_Global(AAA + (selectedPlayer + 1), 9999); break;


	}
}


void ChangeName(char* EditedName, int action) {
	switch (action)
	{
	case 0: //Current name
		PS3::WriteString(0x41143344, EditedName);
		PS3::WriteString(0x1FF248C, EditedName);
		PS3::WriteString(0x200255C, EditedName);
		/*PS3::WriteString2(PS3::PlayerNameActual - 0x2C, EditedName);
		PS3::WriteString2(PS3::PlayerNameActual - 0x74, EditedName);*/
		break;

	case 1://crew tag 
		PS3::WriteString(0x205C27F, EditedName);
		PS3::WriteString(0x205C27F, EditedName);
		PS3::WriteString(0x205C337, EditedName);
		PS3::WriteString(0x205C337, EditedName);
		PS3::WriteString(0x205C3EF, EditedName);
		PS3::WriteString(0x205C3EF, EditedName);
		PS3::WriteString(0x205C4A7, EditedName);
		PS3::WriteString(0x205C4A7, EditedName);
		PS3::WriteString(0x205C55F, EditedName);
		PS3::WriteString(0x205C55F, EditedName);
		break;
	}
}

void startKeyboard(int action, char *defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}

void playSound(char* sound, char *soundgroup = "HUD_FRONTEND_DEFAULT_SOUNDSET")
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound, soundgroup);
}
namespace SkyColor
{
	void WTFSky()
	{
		char noz[] = { 0x00, 0x00, 0x00, 0x00, 0xF4, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8 }; //<3
		PS3::WriteBytes(0x493754, noz, 13);
		
	}

	void PinkBlueSky()
	{
		char noz[] = { 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noz, 13);
	}

	void LightningBlueSky()
	{
		char noz[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noz, 13);
	}
	void TeaSky()
	{
		char no9[] = { 0x00, 0x00, 0x00, 0x00, 0xF4, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, no9, 13);
	}
	void BlurpleSky()
	{
		char nod[] = { 0x00, 0x05, 0x06, 0x07, 0xF4, 0x09, 0x0A, 0x0B, 0x00, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, nod, 13);
	}
	void PeachSky()
	{
		char noh[] = { 0xF4, 0x05, 0x06, 0x07, 0xF4, 0x09, 0x0A, 0x0B, 0xF4, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noh, 13);
	}
	void NeonBlueSky()
	{
		char noj[] = { 0xF4, 0x05, 0x06, 0x07, 0x00, 0x09, 0x0A, 0x0B, 0x00, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noj, 13);
	}
	void YellowSky()
	{
		char noj[] = { 0x04, 0x05, 0x06, 0x07, 0xF4, 0x09, 0x0A, 0x0B, 0x18, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noj, 13);
	}
	void OrangeSky()
	{
		char noj[] = { 0x04, 0xF4, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x18, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noj, 13);
	}
	void PurpleSky()
	{
		char noj[] = { 0xF4, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x18, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noj, 13);
	}
	void NoSky()
	{
		char noj[] = { 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x18, 0x19, 0x1A, 0x1B, 0xF8 }; //<3

		PS3::WriteBytes(0x493754, noj, 13);
	}
}
void DpadUpFUnc()
{
	TextSize04f = 0.6f;
	AnimationMinusFlag = false;
	AnimationPlusFlag = true;
	currentOption--;
	if (currentOption < 1)
	{
		currentOption = optionCount;
		//ScrollBarPlus = (PixelY(30) * currentOption) * -1;
	}
	else if (currentOption < maxOptions)
	{
		ScrollBarPlus += PixelY(OptionPlusIndex);
	}
	if (SoundChange)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_CENTRED", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
	}
	else
	{
		playSound("NAV_UP_DOWN");
	}
	

}

void DownFunc()
{
	TextSize04f = 0.6f;
	AnimationMinusFlag = false;
	AnimationPlusFlag = true;
	currentOption++;
	if (currentOption > optionCount)
	{
		currentOption = 1;
		//ScrollBarPlus = PixelY(30) * currentOption;
	}
	else if (currentOption < maxOptions)
	{
		ScrollBarPlus += (PixelY(OptionPlusIndex) * -1);
	}
	if (SoundChange)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_CENTRED", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
	}
	else
	{
		playSound("NAV_UP_DOWN");
	}
}
int Button1 = Dpad_Right;
int Button2 = Button_X;
void monitorButtons()
{
	Timers::SetupTimer(20);
	if (submenu == Closed)
	{
		if (Timers::IsTimerReady())
		{
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button1) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button2))
			{
				PlusAllX = 1.2f;
				submenu = Main_Menu;
				submenuLevel = 0;
				currentOption = 1;
				if (SoundChange)
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "HACK_SUCCESS", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
				}
				else
				{
					playSound("YES");
				}
			}
			Timers::ResetTimer();
		}
	}
	else {
		if (Timers::IsTimerReady())
		{
			if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_B))
			{
				ScrollBarPlus = 0;
				if (submenu == Main_Menu)
				{
					submenu = Closed;
				}
				else {
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}


				if (SoundChange)
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "HACK_FAILED", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
				}
				else
				{
					playSound("Back");
				}



				//playSound("Back");
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_A))
			{
				optionPress = true;

				if (SoundChange)
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_GOOD", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
				}
				else
				{
					playSound("SELECT");
				}

				//playSound("SELECT");
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Dpad_Up))
			{
				/*TextSize04f = 0.6f;
				AnimationMinusFlag = false;
				AnimationPlusFlag = true;
				currentOption--;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}

				playSound("NAV_UP_DOWN");*/
				DpadUpFUnc();
				//playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Dpad_Down))
			{
				/*TextSize04f = 0.6f;
				AnimationMinusFlag = false;
				AnimationPlusFlag = true;
				currentOption++;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}

				playSound("NAV_UP_DOWN");*/
				DownFunc();

			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Dpad_Right))
			{
				rightPress = true;
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Dpad_Left))
			{
				leftPress = true;
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Dpad_Right))
			{
				fastRightPress = true;
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Dpad_Left))
			{
				fastLeftPress = true;
			}
			else if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_X))
			{
				squarePress = true;
			}
			Timers::ResetTimer();
		}
	}
}



void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}

#pragma endregion

char IPADDR1[4][50];



void PSIDsave(int PPP)
{

	
	char PSID[200];
	char PSID_2[500];
	char output[100];
	char *LIST = PLAYER::GET_PLAYER_NAME(PPP);

	unsigned char ip = *(unsigned char*)((0xC89A2AF0 + (PPP * 0x78) + 4));
	unsigned char ip1 = *(unsigned char*)((0xC89A2AF0 + (PPP * 0x78) + 5));
	unsigned char ip2 = *(unsigned char*)((0xC89A2AF0 + (PPP * 0x78) + 6));
	unsigned char ip3 = *(unsigned char*)((0xC89A2AF0 + (PPP * 0x78) + 7));
	long long XUID = *(long long*)(0xC89A2AF0 + (0x78 * PPP) + 0x38);

	sprintf(output, "%i.%i.%i.%i | %i", ip, ip1, ip2, ip3, XUID);
	for (int i = 0; i < 34; i++)
	{
			int Handle[13];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER2(PPP, &Handle[0], 13);
			char *RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
			char *ipName = PS3::ReadBytes(0x40025C80 + (i * 136), 100);
			if (!strcmp(RealName, ipName))
			{
				int ip = *(int *)(0x40025CC8 + (i * 0x88));
				int p1 = (ip & 0xff000000) >> 24;
				int p2 = (ip & 0x00ff0000) >> 16;
				int p3 = (ip & 0x0000ff00) >> 8;
				int p4 = (ip & 0x000000ff) >> 0;

				int internal_ip = *(int *)(0x40025CA8 + (i * 0x88));
				int p5 = (internal_ip & 0xff000000) >> 24;
				int p6 = (internal_ip & 0x00ff0000) >> 16;
				int p7 = (internal_ip & 0x0000ff00) >> 8;
				int p8 = (internal_ip & 0x000000ff) >> 0;

				char *Region = PS3::ReadBytes(0x40025c96 + (i * 0x88), 100);

				int port = *(int*)(0x40025ccd + (i * 0x88));
				int p9 = (port & 0xff000000) >> 24;
				int p10 = (port & 0x00ff0000) >> 16;
				int portToShow = (p9 << 8) | p10;

				sprintf(IPADDR1[0], "%i.%i.%i.%i", p1, p2, p3, p4);
				sprintf(IPADDR1[1], "%i.%i.%i.%i", p5, p6, p7, p8);
				sprintf(IPADDR1[2], "%s", Region);
				sprintf(IPADDR1[3], "%i", portToShow);
				//if (strstr(IPADDR1[0], "255.255.255.255") == NULL && strstr(IPADDR1[0], "0.0.0.0") == NULL)
				//{
				//	/*DRAW_INFO_TEXT(IPADDR1[0], 0, 0.4390, 0.3875f, 0.35f, 0.35f, 255, 255, 255, true, false);
				//	DRAW_INFO_TEXT(IPADDR1[3], 0, 0.4390, 0.418f, 0.35f, 0.35f, 255, 255, 255, true, false);*/
				//}
				//else
				//{
				///*	DRAW_INFO_TEXT("-", 0, 0.4390, 0.3875f, 0.35f, 0.35f, 255, 255, 255, true, false);
				//	DRAW_INFO_TEXT("-", 0, 0.4390, 0.418f, 0.35f, 0.35f, 255, 255, 255, true, false);*/
			 //   }
				sprintf(PSID, "/dev_hdd0/tmp/ID_IP_SAVE/%s.txt", RealName);//URL
				sprintf(PSID_2, "Playstation ID: %s \r\nClient IP: %s \r\nIP: %s \r\n PS3 Local IP: %s \r\n PORT: %s \r\n 国: %s", RealName, output, IPADDR1[0], IPADDR1[1], IPADDR1[3], Region, Region);//プレイヤー情報
				PS3::WriteFile(PSID_2, PSID);
		}
	}
	
}



#pragma region Buttons
int Analog(int Value)
{
	// Left Analog X-Axis (188 = INPUT_SCRIPT_LEFT_AXIS_X)
	// 0 = Fully left
	// 127 = Centered
	// 254 = Fully right

	// Left Analog Y-Axis (189 = INPUT_SCRIPT_LEFT_AXIS_Y)
	// 0 = Fully up
	// 127 = Centered
	// 254 = Fully down

	// Right Analog X-Axis (190 = INPUT_SCRIPT_RIGHT_AXIS_X)
	// 0 = Fully left
	// 127 = Centered
	// 254 = Fully right

	// Right Analog Y-Axis (191 = INPUT_SCRIPT_RIGHT_AXIS_Y)
	// 0 = Fully up
	// 127 = Centered
	// 254 = Fully down

	return CONTROLS::GET_CONTROL_VALUE(0, Value);
}

bool isDpadPress()
{
	return (leftPress || rightPress || fastLeftPress || fastRightPress);
}

bool isPress(int ButtonID, bool disabled = false)
{
	return disabled ? CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ButtonID) : CONTROLS::IS_CONTROL_PRESSED(0, ButtonID);
}

bool isPressed(int ButtonID)
{
	return CONTROLS::IS_CONTROL_JUST_PRESSED(0, ButtonID);
}

void ButtonDisable(int ButtonID)
{
	CONTROLS::DISABLE_CONTROL_ACTION(0, ButtonID);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, ButtonID);
}
#pragma endregion

#pragma region Animation
void Freeze(Ped selectedPed)
{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
	AI::CLEAR_PED_SECONDARY_TASK(selectedPed);
}

void ChangeWalkingType(char *WalkType)
{
	STREAMING::REQUEST_ANIM_SET(WalkType);
	if (STREAMING::HAS_ANIM_SET_LOADED(WalkType))
	{
		PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), WalkType, 1048576000);
	}
}

bool TASK_PLAY_ANIM_1(Ped Ped, char* AnimDict, char* Anim, int index = 8, float speed = 8.0f, float playback = 8.0f)
{
	STREAMING::REQUEST_ANIM_DICT(AnimDict);
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		AI::TASK_PLAY_ANIM(Ped, AnimDict, Anim, speed, speed, -1, index, playback, 0, 0, 0);
}

void SetAnimSpeed(char *dict, char *anim, float p1, int ped = PLAYER::PLAYER_PED_ID())
{
	ENTITY::SET_ENTITY_ANIM_SPEED(ped, dict, anim, p1);
}

void TASK_PLAY_ANIM(Ped Ped, char* AnimDict, char* Anim, int LoopUpper = 8, float Speed = 8)
{
	AI::TASK_PLAY_ANIM(Ped, AnimDict, Anim, Speed, Speed, -1, LoopUpper, Speed, 0, 0, 0);
}
#pragma endregion

#pragma region Player List
int ReturnMenuID(int player)
{
	return PLAYER::GET_PLAYER_MAX_ARMOUR(player);
}



char *ReturnMenuS(int player)
{
	char MenuName[40];
	switch (ReturnMenuID(player))
	{
	case 83:sprintf(MenuName, "~y~[危険]"); break;
	case 505:sprintf(MenuName, "~r~[HGNE]"); break;
	case 3000: sprintf(MenuName, "~m~[GNX]"); break;
	case 2002:sprintf(MenuName, "~m~[GNX2]"); break;
	case 2001: sprintf(MenuName, "~r~[PE]"); break;
	case 2777:sprintf(MenuName, "~o~[XENO]"); break;
	case 2870: sprintf(MenuName, "~p~[GC]"); break;
	case 2871:sprintf(MenuName, "~p~[GCP]"); break;
	case 2872: sprintf(MenuName, "~p~[GCA]"); break;
	case 2900: sprintf(MenuName, "~r~[HDC]"); break;
	case 2901: sprintf(MenuName, "~b~[HG]"); break;
	case 2902: sprintf(MenuName, "~b~[HGP]"); break;
	case 2903:sprintf(MenuName, "~b~[HGA]"); break;
	case 2904:sprintf(MenuName, "~b~[HGN]"); break;
	case 2905:sprintf(MenuName, "~b~[HGPN]"); break;
	case 2906:sprintf(MenuName, "~b~[HGMN]"); break;
	case 2055:sprintf(MenuName, "~y~[NMRS]"); break;
	case 1109: sprintf(MenuName, "~c~[TKMN]"); break;
	case 2585:sprintf(MenuName, "~m~[ZEDD]"); break;
	case 1256:sprintf(MenuName, "~p~[PAIX]"); break;
	case 564:sprintf(MenuName, "~p~[EMPR]"); break;
	case 3024:sprintf(MenuName, "~p~[PAIX]"); break;
	case 3025:sprintf(MenuName, "~p~[PAIX]"); break;
	case 50: sprintf(MenuName, ""); break;
	case 0: sprintf(MenuName, ""); break;
	case 100: sprintf(MenuName, "[改造機]"); break;
		//通常版
	case 2717:sprintf(MenuName, "~b~[v1.7]"); break;
	case 2718:sprintf(MenuName, "~b~[v1.8]"); break;
	case 2719:sprintf(MenuName, "~b~[v1.9]"); break;
	case 2720:sprintf(MenuName, "~b~[v2.0]"); break;
	case 2721:sprintf(MenuName, "~b~[v2.1]"); break;
	case 2722:sprintf(MenuName, "~b~[v2.2]"); break;
	case 2723:sprintf(MenuName, "~b~[v2.3]"); break;
	case 2724:sprintf(MenuName, "~b~[v2.4]"); break;
	case 2725:sprintf(MenuName, "~b~[v2.5]"); break;
	case 2726:sprintf(MenuName, "~b~[v2.6]"); break;
	case 2727:sprintf(MenuName, "~b~[v2.7]"); break;
	case 2728:sprintf(MenuName, "~b~[v2.8]"); break;
	case 2729:sprintf(MenuName, "~b~[v2.9]"); break;
	case 2730:sprintf(MenuName, "~b~[v3.0]"); break;
	case 2731:sprintf(MenuName, "~b~[v3.1]"); break;
	case 2732:sprintf(MenuName, "~b~[v3.2]"); break;
	case 2733:sprintf(MenuName, "~b~[v3.3]"); break;
	case 2734:sprintf(MenuName, "~b~[v3.4]"); break;
	case 2735:sprintf(MenuName, "~b~[v3.5]"); break;
	case 2736:sprintf(MenuName, "~b~[v3.6]"); break;
	case 2737:sprintf(MenuName, "~b~[v3.7]"); break;
	case 2738:sprintf(MenuName, "~b~[v3.8]"); break;
	case 2739:sprintf(MenuName, "~b~[v3.9]"); break;
	case 2740:sprintf(MenuName, "~b~[v4.0]"); break;
	case 2741:sprintf(MenuName, "~b~[v4.1]"); break;
	case 2742:sprintf(MenuName, "~b~[v4.2]"); break;
	case 2743:sprintf(MenuName, "~b~[v4.3]"); break;
	case 2744:sprintf(MenuName, "~b~[v4.4]"); break;
	case 2745:sprintf(MenuName, "~b~[v4.5]"); break;
	case 2746:sprintf(MenuName, "~b~[v4.6]"); break;
		//Pro
	case 2817:sprintf(MenuName, "~b~[Pv1.7]"); break;
	case 2818:sprintf(MenuName, "~b~[Pv1.8]"); break;
	case 2819:sprintf(MenuName, "~b~[Pv1.9]"); break;
	case 2820:sprintf(MenuName, "~b~[Pv2.0]"); break;
	case 2821:sprintf(MenuName, "~b~[Pv2.1]"); break;
	case 2822:sprintf(MenuName, "~b~[Pv2.2]"); break;
	case 2823:sprintf(MenuName, "~b~[Pv2.3]"); break;
	case 2824:sprintf(MenuName, "~b~[Pv2.4]"); break;
	case 2825:sprintf(MenuName, "~b~[Pv2.5]"); break;
	case 2826:sprintf(MenuName, "~b~[Pv2.6]"); break;
	case 2827:sprintf(MenuName, "~b~[Pv2.7]"); break;
	case 2828:sprintf(MenuName, "~b~[Pv2.8]"); break;
	case 2829:sprintf(MenuName, "~b~[Pv2.9]"); break;
	case 2830:sprintf(MenuName, "~b~[Pv3.0]"); break;
	case 2831:sprintf(MenuName, "~b~[Pv3.1]"); break;
	case 2832:sprintf(MenuName, "~b~[Pv3.2]"); break;
	case 2833:sprintf(MenuName, "~b~[Pv3.3]"); break;
	case 2834:sprintf(MenuName, "~b~[Pv3.4]"); break;
	case 2835:sprintf(MenuName, "~b~[Pv3.5]"); break;
	case 2836:sprintf(MenuName, "~b~[Pv3.6]"); break;
	case 2837:sprintf(MenuName, "~b~[Pv3.7]"); break;
	case 2838:sprintf(MenuName, "~b~[Pv3.8]"); break;
	case 2839:sprintf(MenuName, "~b~[Pv3.9]"); break;
	case 2840:sprintf(MenuName, "~b~[Pv4.0]"); break;
	case 2841:sprintf(MenuName, "~b~[Pv4.1]"); break;
	case 2842:sprintf(MenuName, "~b~[Pv4.2]"); break;
	case 2843:sprintf(MenuName, "~b~[Pv4.3]"); break;
	case 2844:sprintf(MenuName, "~b~[Pv4.4]"); break;
	case 2845:sprintf(MenuName, "~b~[Pv4.5]"); break;
	case 2846:sprintf(MenuName, "~b~[Pv4.6]"); break;
		//Admin
	case 2917:sprintf(MenuName, "~b~[Av1.7]"); break;
	case 2918:sprintf(MenuName, "~b~[Av1.8]"); break;
	case 2919:sprintf(MenuName, "~b~[Av1.9]"); break;
	case 2920:sprintf(MenuName, "~b~[Av2.0]"); break;
	case 2921:sprintf(MenuName, "~b~[Av2.1]"); break;
	case 2922:sprintf(MenuName, "~b~[Av2.2]"); break;
	case 2923:sprintf(MenuName, "~b~[Av2.3]"); break;
	case 2924:sprintf(MenuName, "~b~[Av2.4]"); break;
	case 2925:sprintf(MenuName, "~b~[Av2.5]"); break;
	case 2926:sprintf(MenuName, "~b~[Av2.6]"); break;
	case 2927:sprintf(MenuName, "~b~[Av2.7]"); break;
	case 2928:sprintf(MenuName, "~b~[Av2.8]"); break;
	case 2929:sprintf(MenuName, "~b~[Av2.9]"); break;
	case 2930:sprintf(MenuName, "~b~[Av3.0]"); break;
	case 2931:sprintf(MenuName, "~b~[Av3.1]"); break;
	case 2932:sprintf(MenuName, "~b~[Av3.2]"); break;
	case 2933:sprintf(MenuName, "~b~[Av3.3]"); break;
	case 2934:sprintf(MenuName, "~b~[Av3.4]"); break;
	case 2935:sprintf(MenuName, "~b~[Av3.5]"); break;
	case 2936:sprintf(MenuName, "~b~[Av3.6]"); break;
	case 2937:sprintf(MenuName, "~b~[Av3.7]"); break;
	case 2938:sprintf(MenuName, "~b~[Av3.8]"); break;
	case 2939:sprintf(MenuName, "~b~[Av3.9]"); break;
	case 2940:sprintf(MenuName, "~b~[Av4.0]"); break;
	case 2941:sprintf(MenuName, "~b~[Av4.1]"); break;
	case 2942:sprintf(MenuName, "~b~[Av4.2]"); break;
	case 2943:sprintf(MenuName, "~b~[Av4.3]"); break;
	case 2944:sprintf(MenuName, "~b~[Av4.4]"); break;
	case 2945:sprintf(MenuName, "~b~[Av4.5]"); break;
	case 2946:sprintf(MenuName, "~b~[Av4.6]"); break;
	}

	return MenuName;
}

char* GetGodmodeStatus(int i)
{
	unsigned char flag = 0;
	if (PLAYER::GET_PLAYER_MAX_ARMOUR(i) > 100)
	{
		return "~y~Hacker!!";
	}
	else if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(i)))
	{
		flag = *(unsigned char*)(GetEntityAddress(PLAYER::GET_PLAYER_PED(i)) + 0xB5);
	}
	if (flag == 128 || flag == 129)
	{
		return "~y~Hacker!!";

	}
	else
	{
		return "~g~No";
	}

}

char *PlayerNameReturn(int i)
{
	char PlayerName[100];
	if (cstrcmp(PLAYER::GET_PLAYER_NAME(i), "**Invalid**"))
	{
		strcpy(PlayerName, "---");
	}
	else
	{
		//PLAYER::GET_PLAYER_NAME(i) ReturnMenuS
		char *Player = PLAYER::GET_PLAYER_NAME(i);
		strcpy(PlayerName, ReturnMenuS(i));
		/*if (i == PLAYER::PLAYER_ID())
		{
			strcat(PlayerName, "~p~[Me]");
		}
		else if (NETWORK::NETWORK_IS_FRIEND_ONLINE(Player))
		{
			strcat(PlayerName, "~g~[F]");
		}*/
		int HostNumber = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
		if (HostNumber == i)
		{
			if (!cstrcmp(PLAYER::GET_PLAYER_NAME(HostNumber), "**Invalid**"))
			{
				strcat(PlayerName, "~f~[S-H]");
			}
		}
		if (!strstr("", PS3::ReadString_1(0x400236B8)))
		{
			if (strstr(PLAYER::GET_PLAYER_NAME(i), PS3::ReadString_1(0x400236B8)))
			{
				strcat(PlayerName, " ~w~[~r~H~w~]");
			}
		}

		if (i >= 16)
		{
			strcat(PlayerName, "~r~[観戦中]");
		}
		strcat(PlayerName, "~w~");
		strcat(PlayerName, Player);
	}
	return PlayerName;
}
#pragma endregion

#pragma region Vector3
float DistanceBetweenVectors(Vector3 v1, Vector3 v2)
{
	float ret = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, true);
	return ret;
}
#pragma endregion

#pragma region Teleport
void TeleportInScene(int playerid, char* anim, char* animid, float X, float Y, float Z)
{
	if (UNKO222)
	{
		TPFreeze = true;
	}

	if (TPFreeze)
	{
		Animations2[0] = anim;
		Animations2[1] = animid;
		MyCoordsForTPtoMe.x = X;
		MyCoordsForTPtoMe.y = Y;
		MyCoordsForTPtoMe.z = Z;
		Teleporting = true;
		SetPlayerAnimation = true;
	}
	else
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(playerid);
		int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(X, Y, Z, 0.0, 0.0, ENTITY::GET_ENTITY_HEADING(playerid), 9, 0, 0, 0, 0, 0);
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(playerid, scene2, anim, animid, 8.0f, -8.0, 5, 0, 30, 0);
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
	}
}
#pragma endregion

#pragma region Teleport
void TeleportPedGun(Ped ped)
{
	if (ped == PLAYER::PLAYER_PED_ID())
	{
		if (PED::IS_PED_SHOOTING(ped))
		{
			if (__GET_PED_LAST_WEAPON_IMPACT_COORD(ped, (Vector3*)0x10031000))
			{
				if (((Vector3*)0x10031000)->x != 0.0f)
				{
					Vector3 Unti = get_entity_rotation_orig(0, 0);
					Unti.z = ENTITY::GET_ENTITY_HEADING(ped);
					ENTITY::SET_ENTITY_COORDS(ped, ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 0, 0, 0, true);
					ENTITY::SET_ENTITY_ROTATION(ped, Unti.x, Unti.y, Unti.z, 0, 0);
				}
			}
			else
			{
				NotifyDown("座標が取得出来ませんでした。", 500);
			}
		}
	}
}

void TeleportCar(Ped ped, float x, float y, float z)
{
	if (ped != PLAYER::PLAYER_PED_ID())
	{
		Vehicle GetVeh = PED::GET_VEHICLE_PED_IS_USING(ped);
		if (GetVeh != 0)
		{
			for (int i = 0; i < 5; i++)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(GetVeh);
				ENTITY::SET_ENTITY_COORDS(GetVeh, x, y, z, 0, 0, 0, true);
			}
		}
		else
		{
			NotifyDown("車に乗っていません。");
		}
	}
	else
	{
		NotifyDown("自分はテレポート出来ません");
	}
}

void TeleportToCoords(Ped from, float x, float y, float z)
{
	Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(from);
	if (Veh == 0)
	{
		ENTITY::SET_ENTITY_COORDS(from, x, y, z, 0, 0, 0, 1);
	}
	else
	{
		ENTITY::SET_ENTITY_COORDS(Veh, x, y, z, 0, 0, 0, 1);
	}
}

void TeleportToClientCar(int Client)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(Client, true))
	{
		for (int i = 0; i < 16; i++)
		{
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_USING(Client), i))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_USING(Client), i);
				NotifyDown("プレイヤーの車へ乗車しました。");
			}
		}
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
		{
			NotifyDown("プレイヤーの車の空きを取得出来ませんでした。", 1000);
		}
	}
	else
	{
		NotifyDown("~r~プレイヤーが車に乗っていません。");
	}
}
void RequestControlOfEnt(int entity)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 12)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
}
void AllTeleportToMe(int CoordPed = PLAYER::PLAYER_ID())
{
	Vector3 AAA = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(CoordPed), 1);
	int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(AAA.x, AAA.y, AAA.z, 0.0, 0.0, 0.0, 9, 0, 0, 0, 0, 0);
	for (int i = 0; i < 16; i++)
	{
		if (i != CoordPed)
		{
			Freeze(PLAYER::GET_PLAYER_PED(i));
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(PLAYER::GET_PLAYER_PED(i), scene2, "mini@strip_club@private_dance@part3", "priv_dance_p3", 8.0f, -8.0, 5, 0, 30, 0);
		}
	}
	NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
}

float PosX, PosY, PosZ;
bool move1 = 0;
bool TeleportCameraSelf;
bool ParadiseProtect;
bool LiteMOD;
int Entities;
Cam cameraHandle;
int TeleID = 0, TeleID2 = 115, RenderTime2 = 3500, AlturaTeleport = 400, RenderTime = 3500;
void _CreateTeleport(Cam *Cam)
{
	*Cam = CAM::CREATE_CAMERA(26379945, false);
	CAM::SET_CAM_ACTIVE(*Cam, true);
	CAM::SET_CAM_COORD(*Cam, PosX, PosY, PosZ + AlturaTeleport);
}

int Teleanim;

void addteleportoption(float x, float y, float z, Entity entity, int flag = 2)
{
	if (optionPress)
	{
		if (Teleanim == 1)
		{
			RequestControlOfEnt(entity);
			switch (flag)
			{
			case 0:  break;
			case 1: if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), 0)); break;
			case 2: move1 = true; break;
			case 3:  break;
			case 4: break;
			}
			if (move1)
			{
				PosX = x; PosY = y; PosZ = z;
				STREAMING::LOAD_ALL_OBJECTS_NOW();
				move1 = true;
			}
			else
			{
				Ped ped = PLAYER::PLAYER_PED_ID(); Entity entityToTele = ped;
				if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
				Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				ENTITY::SET_ENTITY_COORDS(entityToTele, x, y, z, false, false, false, true);
				STREAMING::LOAD_ALL_OBJECTS_NOW();
			}
		}
		else
		{
			Ped ped = PLAYER::PLAYER_PED_ID(); Entity entityToTele = ped;
			if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
			Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_COORDS(entityToTele, x, y, z, false, false, false, true);
			STREAMING::LOAD_ALL_OBJECTS_NOW();
		}
	}
}

void MyConsoleTeleport(int ped, float x, float y, float z)
{
	int aaa = PED::GET_VEHICLE_PED_IS_USING(ped);
	if (aaa == 0)
	{
		aaa = ped;
	}
	Vector3 flo = { x, y, z };
	Vector3 Unti = get_entity_rotation_orig(0, 0);
	Unti.z = ENTITY::GET_ENTITY_HEADING(aaa);
	ENTITY::SET_ENTITY_COORDS(aaa, flo.x, flo.y, flo.z, 0, 0, 0, true);
	ENTITY::SET_ENTITY_ROTATION(aaa, Unti.x, Unti.y, Unti.z, 0, 0);

	/*move1 = true;

	if (move1)
	{
		PosX = x; PosY = y; PosZ = z; 
		STREAMING::LOAD_ALL_OBJECTS_NOW();
		move1 = true;
	}
	else
	{
		Ped ped = PLAYER::PLAYER_PED_ID(); Entity entityToTele = ped;
		if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		ENTITY::SET_ENTITY_COORDS(entityToTele, x, y, z, false, false, false, true);
		STREAMING::LOAD_ALL_OBJECTS_NOW();
	}*/
}
#pragma endregion

#pragma region Pickup
void GiveArmour(int PedHandle)
{
	PED::SET_PED_ARMOUR(PLAYER::GET_PLAYER_PED(PedHandle), 9999999);
}

void dropPickup(Vector3 Location, char* PickupModel, char* PickupBehavior, int PickupAmount, char* DisplayName, int Client)
{
	int Model = GAMEPLAY::GET_HASH_KEY(PickupModel);
	int Behavior = GAMEPLAY::GET_HASH_KEY(PickupBehavior); //"PICKUP_MONEY_CASE"
	STREAMING::REQUEST_MODEL(Model);
	if (STREAMING::HAS_MODEL_LOADED(Model))
	{
		OBJECT::CREATE_AMBIENT_PICKUP(Behavior, Location.x, Location.y, Location.z, 0, PickupAmount, Model, 0, 2);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
	}
}

#pragma endregion

#pragma region Object
void ATTACH_ENTITY_TO_ENTITY_T(Entity Ent1, Entity Ent2, float X = 0, float Y = 0, float Z = 0, float Pitch = 0, float Roll = 0, float Yaw = 0, bool HasPhysics = false)
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(Ent1, Ent2, 0, X, Y, Z, Pitch, Roll, Yaw, 1, 0, 0, 1, 2, 1);
	if (HasPhysics)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(Ent1, true);
		ENTITY::SET_ENTITY_COLLISION(Ent1, true, false);
		ENTITY::SET_ENTITY_VISIBLE(Ent1, 0);
	}
}

void CREATE_AND_ATTACH(Entity Entity, Hash ObjectHash, float Offset_X = 0, float Offset_Y = 0, float Offset_Z = 0, float Pitch = 0, float Roll = 0, float Yaw = 0, bool HasPhysics = false, bool Invisible = true)
{
	Hash hash = ObjectHash;
	Vector3 MyPos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
	Object Handle = OBJECT::CREATE_OBJECT(hash, MyPos.x, MyPos.y, MyPos.z, true, true, false);
	if (Handle == 0)
	{
		STREAMING::REQUEST_MODEL(hash);//Load model into memory
		STREAMING::REQUEST_MODEL(hash);
		STREAMING::REQUEST_MODEL(hash);
		STREAMING::REQUEST_MODEL(hash);
		STREAMING::REQUEST_MODEL(hash);
		Object Handle = OBJECT::CREATE_OBJECT(hash, MyPos.x, MyPos.y, MyPos.z, true, true, false);
	}
	if (Invisible)
		ENTITY::SET_ENTITY_VISIBLE(Handle, true);
	ATTACH_ENTITY_TO_ENTITY_T(Handle, Entity, Offset_X, Offset_Y, Offset_Z, Pitch, Roll, Yaw, HasPhysics);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	ENTITY::SET_ENTITY_VISIBLE(Entity, 0);
}

bool RequestNetworkControl(uint vehID)
{
	int Tries = 0;
	bool
		hasControl = false,
		giveUp = false;
	do
	{
		hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
		Tries++;
		if (Tries > 300)
			giveUp = true;
	} while (!hasControl && !giveUp);

	if (giveUp)
		return false;
	else return true;
}

int Create_Map_int(char* MapObjectName, Hash aaa = 0, bool visible = false, bool position = false, bool MyCodSpawn = false)
{
	Hash ObjectHash;

	if (aaa == 0)
	{
		ObjectHash = GAMEPLAY::GET_HASH_KEY(MapObjectName);
	}
	else
	{
		ObjectHash = aaa;
	}

	STREAMING::REQUEST_MODEL(ObjectHash);
	Vector3 coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
	if (STREAMING::HAS_MODEL_LOADED(ObjectHash))
	{
		int GetMemory = MyCodSpawn ? OBJECT::CREATE_OBJECT(ObjectHash, coords.x + 0, coords.y + 0, coords.z + 3, 1, 1, 1) : OBJECT::CREATE_OBJECT(ObjectHash, coords.x + 0, coords.y + 0, coords.z + 0, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(GetMemory))
		{
			ENTITY::FREEZE_ENTITY_POSITION(GetMemory, position);
			ENTITY::SET_ENTITY_VISIBLE(GetMemory, visible);
			ENTITY::SET_ENTITY_COORDS(GetMemory, coords.x + 3, coords.y + 3, coords.z + 3, false, false, false, false);
			return GetMemory;
		}
		return 0;
	}
	return 0;
}

void ToggleFreezeEntity(Entity obj, bool flag)
{
	ENTITY::FREEZE_ENTITY_POSITION(obj, flag);
}

void ToggleCollisionEntity(Entity obj, bool flag)
{
	ENTITY::SET_ENTITY_COLLISION(obj, flag, 1);
}



#pragma endregion

#pragma region vehicle
int GetRFromI(int i)
{
	i *= 10;
	if (i <= 255)
		return 255;
	else if (i <= 510)
		return 255 - (i - 255);
	else if (i <= 765)
		return 0;
	else if (i <= 1020)
		return 0;
	else if (i <= 1275)
		return i - 1020;
	else if (i <= 1530)
		return 255;
	else
		return 255;
}

int GetGFromI(int i)
{
	i *= 10;
	if (i <= 255)
		return 0;
	else if (i <= 510)
		return 0;
	else if (i <= 765)
		return i - 510;
	else if (i <= 1020)
		return 255;
	else if (i <= 1275)
		return 255;
	else if (i <= 1530)
		return 255 - (i - 1275);
	else
		return 255;
}

int GetBFromI(int i)
{
	i *= 10;
	if (i <= 255)
		return i;
	else if (i <= 510)
		return 255;
	else if (i <= 765)
		return 255;
	else if (i <= 1020)
		return 255 - (i - 765);
	else if (i <= 1275)
		return 0;
	else if (i <= 1530)
		return 0;
	else
		return 255;
}

int Create_Vehicle_int(char* FahrzeugName, Vector3 coords, float speed, Vector3 Rot)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
	{
		if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
		{
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(FahrzeugName));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
			{
				int Spawned_Vehicle = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(FahrzeugName), coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Spawned_Vehicle))
				{
					RequestNetworkControl(Spawned_Vehicle);
					ENTITY::SET_ENTITY_ROTATION(Spawned_Vehicle, Rot.x, Rot.y, Rot.z, 0, 0);
					if (speed != 0.0f)
					{
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(Spawned_Vehicle, speed);
					}
					return Spawned_Vehicle;
				}
			}
			else return 0;
		}
	}
}

bool Create_Vehicle(char* FahrzeugName, bool isBusAttack = false)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
	{
		if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
		{
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(FahrzeugName));
			Vector3 coords;

			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(FahrzeugName)))
			{
				if (!isBusAttack)
				{
					if (spawnplayer)
					{
						coords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(AttachSpawnPlayer), 1);
					}
					else
					{
						coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
					}
					int Spawned_Vehicle = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(FahrzeugName), coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);

					if (ENTITY::DOES_ENTITY_EXIST(Spawned_Vehicle))
					{
						if (isFadeinSpawn)
						{
							NETWORK::NETWORK_FADE_IN_ENTITY(Spawned_Vehicle, 0);
						}
						if (isattach)
						{
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Spawned_Vehicle, PLAYER::GET_PLAYER_PED(AttachSpawnPlayer), 0x0, 0, 0, 0, 0, 0, 0, false, false, false, false, 2, true);
						}
						VEHICLE::SET_VEHICLE_MOD_KIT(Spawned_Vehicle, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Spawned_Vehicle, ColorR, ColorG, ColorB);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Spawned_Vehicle, ColorR, ColorG, ColorB);
						if (TeleAutomIncar)
						{
							bool AAAn;
							float Speed;
							Vector3 Rotation;
							int PedHandle = PLAYER::PLAYER_PED_ID();
							Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Spawned_Vehicle, -1);
							VEHICLE::SET_VEHICLE_ENGINE_ON(Spawned_Vehicle, true, true);
							if (PED::IS_PED_IN_ANY_VEHICLE(PedHandle, 0))
							{
								AAAn = true;
								Speed = ENTITY::GET_ENTITY_SPEED(veh);
								VEHICLE::DELETE_VEHICLE(&veh);
								VEHICLE::SET_VEHICLE_FORWARD_SPEED(Spawned_Vehicle, Speed);
							}

						}
						if (MaxUpgrades)
						{

							VEHICLE::SET_VEHICLE_FIXED(Spawned_Vehicle);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Spawned_Vehicle);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(Spawned_Vehicle, 0);
							VEHICLE::SET_VEHICLE_MOD_KIT(Spawned_Vehicle, 0);
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 0, 1, 0);//Soiler
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 1, 1, 0);//Frontstoﾟstange
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 2, 1, 0);//Heckstoﾟstange
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 3, 1, 0);//Body
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 4, 2, 0);//Auspuff
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 5, 1, 0);//Ueberrollkaeffig
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 6, 1, 0);//Grill
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 7, 1, 0);//Motorhaube
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 8, 2, 0);//Schhuerze
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 9, 2, 0);//Rechte Schuerze
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 10, 1, 0);//Dach
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 11, 3, 0);//Motor9
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 12, 2, 0);//Bremsen
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 13, 2, 0);//Getriebe
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 14, 24, 0);//Hupe
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 15, 2, 0);//Federung
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 16, 4, 0);//Panzerung
							VEHICLE::TOGGLE_VEHICLE_MOD(Spawned_Vehicle, 18, 1);//Turbo
							VEHICLE::TOGGLE_VEHICLE_MOD(Spawned_Vehicle, 22, 1);//Xenon 
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(Spawned_Vehicle, 7);//Reifen Typ
							VEHICLE::SET_VEHICLE_MOD(Spawned_Vehicle, 23, 18, 0);//Reifen
							VEHICLE::SET_VEHICLE_WINDOW_TINT(Spawned_Vehicle, 5);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Spawned_Vehicle, "Phantom");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Spawned_Vehicle, 3);
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(Spawned_Vehicle, false);
							//char buf[100];
							//sprintf(buf, "アップグレードしました。: ~b~%s~HUD_COLOUR_WHITE~!", UI::_0x95C4B5AD(FahrzeugName));
							//NotifyDown(buf);
						}
						if (threecolorsmoke)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 20, 1);
							VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, 0, 0);
						}
						else if (smokecolortrue)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 20, 1);
							VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), ColorR, ColorG, ColorB);
						}
						if (ChromeSpawn)
							VEHICLE::SET_VEHICLE_COLOURS(Spawned_Vehicle, 120, 120);
						if (spawnGodmode)
						{
							ENTITY::SET_ENTITY_PROOFS(Spawned_Vehicle, true, true, true, true, true, true, true, true);

						}
						
						if (isinvisible)
						{
							ENTITY::SET_ENTITY_VISIBLE(Spawned_Vehicle, false);
						}
						char buf[100];
						sprintf(buf, "スポーンしました : ~b~%s~HUD_COLOUR_WHITE~!", UI::_0x95C4B5AD(FahrzeugName));
						NotifyDown(buf, 1000);
						SpawnedVehicleCode[SpawnedIndex] = Spawned_Vehicle;
						SpawnedVehicleName[SpawnedIndex] = FahrzeugName;
						if (SpawnedIndex >= 19)
						{
							SpawnedIndex = 0;
						}
						else
						{
							SpawnedIndex++;
						}
						return true;
					}
				}
			}
			else return false;
		}
	}
}

void setWheelSize(float dir)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		*(float*)((*(int*)((*(int*)(GetEntityAddress(veh) + 0x28)) + 0x130)) + 0x04) = dir;
		char UNKOAAAA[300];
		//sprintf(UNKOAAAA, "veh 0x%X \n", veh);
		//NotifyDown(UNKOAAAA, 1000);

		int veh_addr = GetEntityAddress(veh);
		//sprintf(UNKOAAAA, "veh_addr = 0x%X \n", veh_addr);
		//NotifyDown(UNKOAAAA, 1000);

		int veh_comps_ptr = *(int*)(veh_addr + 0x28);
		//sprintf(UNKOAAAA, "veh_comps_ptr = 0x%X \n", veh_comps_ptr);
		//NotifyDown(UNKOAAAA, 1000);

		int wheel_ptr = *(int*)(veh_comps_ptr + 0x130);
		//sprintf(UNKOAAAA, "wheel ptr = 0x%X \n", wheel_ptr);
		//NotifyDown(UNKOAAAA, 1000);

		*(float*)(wheel_ptr + 0x4) = dir;
		if (VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)))
		{
			//*(float*)(*(int*)(wheel_ptr + 0x08)) = dir;
			*(float*)(wheel_ptr + 0x8) = dir;
		}
	}
}

void setsuspensionheight(float dir)
{
	int address = GetEntityAddress(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
	*(float*)(address + 0xCEC) = dir;
}
WeatherEditor_Render SelectedRender;
int SelectedRenderAddress;
WeatherEditor_Render Render_Read(int address)
{
	WeatherEditor_Render aaa;
	aaa.textureRowsColsAnim[0] = PS3::ReadFloat(address);
	aaa.textureRowsColsAnim[1] = PS3::ReadFloat(address + 0x04);
	aaa.textureRowsColsAnim[2] = PS3::ReadFloat(address + 0x08);
	aaa.Dummy = PS3::ReadInt32(address + Dummy);
	aaa.sizeMinMax[0] = PS3::ReadFloat(address + sizeMinMax);
	aaa.sizeMinMax[1] = PS3::ReadFloat(address + sizeMinMax + 0x04);
	aaa.sizeMinMax[2] = PS3::ReadFloat(address + sizeMinMax + 0x08);
	aaa.sizeMinMax[3] = PS3::ReadFloat(address + sizeMinMax + 0x0C);
	aaa.colour[0] = PS3::ReadFloat(address + colour + 0x00);
	aaa.colour[1] = PS3::ReadFloat(address + colour + 0x04);
	aaa.colour[2] = PS3::ReadFloat(address + colour + 0x08);
	aaa.colour[3] = PS3::ReadFloat(address + colour + 0x0C);
	aaa.fadeInOut[0] = PS3::ReadFloat(address + fadeInOut + 0x00);
	aaa.fadeInOut[1] = PS3::ReadFloat(address + fadeInOut + 0x04);
	aaa.fadeNearFar[0] = PS3::ReadFloat(address + fadeNearFar + 0x00);
	aaa.fadeNearFar[1] = PS3::ReadFloat(address + fadeNearFar + 0x04);
	aaa.fadeZ = PS3::ReadFloat(address + fadeZ + 0x00);
	
	aaa.rotSpeedMinMax[0] = PS3::ReadFloat(address + rotSpeedMinMax + 0x00);
	aaa.rotSpeedMinMax[1] = PS3::ReadFloat(address + rotSpeedMinMax + 0x04);
	aaa.Dummy2 = PS3::ReadFloat(address + Dummy2);
	aaa.directionalZOffsetMinMax[0] = PS3::ReadFloat(address + directionalZOffsetMinMax + 0x00);
	aaa.directionalZOffsetMinMax[1] = PS3::ReadFloat(address + directionalZOffsetMinMax + 0x04);
	aaa.directionalZOffsetMinMax[2] = PS3::ReadFloat(address + directionalZOffsetMinMax + 0x08);
	aaa.Dummy3 = PS3::ReadFloat(address + Dummy3);
	aaa.dirVelAddCamSpeedMinMaxMult[0] = PS3::ReadFloat(address + dirVelAddCamSpeedMinMaxMult + 0x00);
	aaa.dirVelAddCamSpeedMinMaxMult[1] = PS3::ReadFloat(address + dirVelAddCamSpeedMinMaxMult + 0x04);
	aaa.dirVelAddCamSpeedMinMaxMult[2] = PS3::ReadFloat(address + dirVelAddCamSpeedMinMaxMult + 0x08);
	aaa.Dummy4 = PS3::ReadFloat(address + Dummy4 + 0x00);
	aaa.edgeSoftness = PS3::ReadFloat(address + edgeSoftness);
	return aaa;
}

void WriteAllRender(int Address, WeatherEditor_Render aaa)
{
	PS3::WriteFloat(Address + 0x00, aaa.textureRowsColsAnim[0]);
	PS3::WriteFloat(Address + 0x04, aaa.textureRowsColsAnim[1]);
	PS3::WriteFloat(Address + 0x08, aaa.textureRowsColsAnim[2]);

	PS3::WriteFloat(Address + 0x00 + sizeMinMax, aaa.sizeMinMax[0]);
	PS3::WriteFloat(Address + 0x04 + sizeMinMax, aaa.sizeMinMax[1]);
	PS3::WriteFloat(Address + 0x08 + sizeMinMax, aaa.sizeMinMax[2]);
	PS3::WriteFloat(Address + 0x0C + sizeMinMax, aaa.sizeMinMax[3]);

	PS3::WriteFloat(Address + 0x00 + colour, aaa.colour[0]);
	PS3::WriteFloat(Address + 0x04 + colour, aaa.colour[1]);
	PS3::WriteFloat(Address + 0x08 + colour, aaa.colour[2]);
	PS3::WriteFloat(Address + 0x0C + colour, aaa.colour[3]);

	PS3::WriteFloat(Address + 0x00 + fadeInOut, aaa.fadeInOut[0]);
	PS3::WriteFloat(Address + 0x04 + fadeInOut, aaa.fadeInOut[1]);

	PS3::WriteFloat(Address + 0x00 + fadeNearFar, aaa.fadeNearFar[0]);
	PS3::WriteFloat(Address + 0x04 + fadeNearFar, aaa.fadeNearFar[1]);

	PS3::WriteFloat(Address + 0x00 + fadeZ, aaa.fadeZ);

	PS3::WriteFloat(Address + 0x00 + rotSpeedMinMax, aaa.rotSpeedMinMax[0]);
	PS3::WriteFloat(Address + 0x04 + rotSpeedMinMax, aaa.rotSpeedMinMax[1]);

	PS3::WriteFloat(Address + 0x00 + directionalZOffsetMinMax, aaa.directionalZOffsetMinMax[0]);
	PS3::WriteFloat(Address + 0x04 + directionalZOffsetMinMax, aaa.directionalZOffsetMinMax[1]);
	PS3::WriteFloat(Address + 0x08 + directionalZOffsetMinMax, aaa.directionalZOffsetMinMax[2]);

	PS3::WriteFloat(Address + 0x00 + dirVelAddCamSpeedMinMaxMult, aaa.dirVelAddCamSpeedMinMaxMult[0]);
	PS3::WriteFloat(Address + 0x04 + dirVelAddCamSpeedMinMaxMult, aaa.dirVelAddCamSpeedMinMaxMult[1]);
	PS3::WriteFloat(Address + 0x08 + dirVelAddCamSpeedMinMaxMult, aaa.dirVelAddCamSpeedMinMaxMult[2]);
	PS3::WriteFloat(Address + 0x00 + edgeSoftness, aaa.edgeSoftness);
}

void VehicleGodmode(bool flag)
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	if (flag == true)
	{
		RequestNetworkControl(Vehicle);
		ENTITY::SET_ENTITY_INVINCIBLE(Vehicle, true);
		ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Vehicle, true);
		ENTITY::SET_ENTITY_PROOFS(Vehicle, 0, 0, 0, 0, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEALTH(Vehicle, 99999999);
		VEHICLE::_0x920C2517(Vehicle, 1000000000.0f);
	}
	else
	{

	}
}

void CARFIX(int player = PLAYER::PLAYER_ID())
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
	RequestNetworkControl(Vehicle);
	VEHICLE::SET_VEHICLE_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 1);
	WEAPON::CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Vehicle);
}



void MaxUpgrade(int player = PLAYER::PLAYER_ID())
{
	Entity Vehicle1 = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
	RequestNetworkControl(Vehicle1);
	VEHICLE::SET_VEHICLE_FIXED(Vehicle1);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle1);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle1, 0);
	VEHICLE::SET_VEHICLE_MOD_KIT(Vehicle1, 0);
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 0, 1, 0);//Soiler
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 1, 1, 0);//Frontstoﾟstange
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 2, 1, 0);//Heckstoﾟstange
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 3, 1, 0);//Body
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 4, 2, 0);//Auspuff
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 5, 1, 0);//Ueberrollkaeffig
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 6, 1, 0);//Grill
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 7, 1, 0);//Motorhaube
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 8, 2, 0);//Schhuerze
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 9, 2, 0);//Rechte Schuerze
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 10, 1, 0);//Dach
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 11, 3, 0);//Motor9
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 12, 2, 0);//Bremsen
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 13, 2, 0);//Getriebe
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 14, 24, 0);//Hupe
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 15, 2, 0);//Federung
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 16, 4, 0);//Panzerung
	VEHICLE::TOGGLE_VEHICLE_MOD(Vehicle1, 18, 1);//Turbo
	VEHICLE::TOGGLE_VEHICLE_MOD(Vehicle1, 22, 1);//Xenon 
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(Vehicle1, 7);//Reifen Typ
	VEHICLE::SET_VEHICLE_MOD(Vehicle1, 23, 18, 0);//Reifen
	VEHICLE::SET_VEHICLE_WINDOW_TINT(Vehicle1, 5);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle1, "STANG");
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle1, 3);
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(Vehicle1, false);
}

void SearchLight(bool aa = true)
{
	if (aa)
	{
		VEHICLE::SET_VEHICLE_SEARCHLIGHT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, false);
	}
	else
	{
		VEHICLE::SET_VEHICLE_SEARCHLIGHT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false, false);
	}
}

void DrawNeons(int R, int G, int B)
{
	int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	Vector3 Coords = get_entity_coords_orig(VehicleID, true);
	GRAPHICS::DRAW_LIGHT_WITH_RANGE(Coords.x, Coords.y, Coords.z, R, G, B, 4.0f, 2.0f);
}

void VehicleCustom(bool a = false, bool b = false, bool c = false, int Client = isplayerme)
{
	if (a)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(Client, true))
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(Client), ColorR, ColorG, ColorB);
		}
	}
	if (b)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(Client, true))
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(Client), ColorR, ColorG, ColorB);
		}
	}
	if (c)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(Client, true))
		{
			VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(Client, false), 20, 1);
			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(Client, false), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_USING(Client), ColorR, ColorG, ColorB);
		}
	}
}

void ShowAddressEntity()
{
	int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	char UNKOAAAA[300];
	sprintf(UNKOAAAA, "veh 0x%X \n", veh);
	NotifyLeft(UNKOAAAA);

	int veh_addr = GetEntityAddress(veh);
	sprintf(UNKOAAAA, "veh_addr = 0x%X \n", veh_addr);
	NotifyLeft(UNKOAAAA);

	int veh_addr2 = GetEntityAddress(veh) + 0xCEC;
	sprintf(UNKOAAAA, "サスペ = 0x%X \n", veh_addr2);
	NotifyLeft(UNKOAAAA);

	int veh_comps_ptr = *(int*)(veh_addr + 0x28);
	sprintf(UNKOAAAA, "veh_comps_ptr = 0x%X \n", veh_comps_ptr);
	NotifyLeft(UNKOAAAA);

	int wheel_ptr = *(int*)(veh_comps_ptr + 0x130);
	sprintf(UNKOAAAA, "wheel ptr = 0x%X \n", wheel_ptr);
	NotifyLeft(UNKOAAAA);

}

void Chrome(bool flag)
{
	if (flag == true)
	{
		RequestNetworkControl(PED::GET_VEHICLE_PED_IS_USING(isplayerme));
		VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_USING(isplayerme), 120, 120);

	}
	else
	{
		RequestNetworkControl(PED::GET_VEHICLE_PED_IS_USING(isplayerme));
		VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_USING(isplayerme), 0, 0);
	}
}


void RandomColor(int VehicleHandle)
{
	int col1 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int col2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int col3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int col4 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int col5 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int col6 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int c1 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 160);
	int c2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 160);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleHandle, 0.0f);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehicleHandle, col1, col2, col5);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(VehicleHandle, col3, col4);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehicleHandle, col3, col4, col6);
	VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
	VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, c1, c2);
}
#pragma endregion

#pragma region Water
waterQuad CurrentWaterQuad;
char QuadVire[100];
float QuadScreenX, QuadScreenY;
char* quadFormatStr(int val)
{
	sprintf(hex2buf, "Quad #%i", val);
	return hex2buf;
}

void GetWaterQuadData(int num)
{
	CurrentWaterQuad.minX = *(int16_t*)(WaterQuad + (num * 0x1C) + 0x00);
	CurrentWaterQuad.minY = *(int16_t*)(WaterQuad + (num * 0x1C) + 0x02);
	CurrentWaterQuad.maxX = *(int16_t*)(WaterQuad + (num * 0x1C) + 0x04);
	CurrentWaterQuad.maxY = *(int16_t*)(WaterQuad + (num * 0x1C) + 0x06);

	CurrentWaterQuad.a1 = *(BYTE*)(WaterQuad + (num * 0x1C) + 0x08);
	CurrentWaterQuad.a2 = *(BYTE*)(WaterQuad + (num * 0x1C) + 0x09);
	CurrentWaterQuad.a3 = *(BYTE*)(WaterQuad + (num * 0x1C) + 0x0A);
	CurrentWaterQuad.a4 = *(BYTE*)(WaterQuad + (num * 0x1C) + 0x0B);

	CurrentWaterQuad._0x000C[0] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x0C);
	CurrentWaterQuad._0x000C[1] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x0D);
	CurrentWaterQuad._0x000C[2] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x0E);
	CurrentWaterQuad._0x000C[3] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x0F);
	CurrentWaterQuad._0x000C[4] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x10);
	CurrentWaterQuad._0x000C[5] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x11);
	CurrentWaterQuad._0x000C[6] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x12);
	CurrentWaterQuad._0x000C[7] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x13);

	CurrentWaterQuad.height = *(float*)(WaterQuad + (num * 0x1C) + 0x14);

	CurrentWaterQuad._0x0018[0] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x18);
	CurrentWaterQuad._0x0018[1] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x19);
	CurrentWaterQuad._0x0018[2] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x1A);
	CurrentWaterQuad._0x0018[3] = PS3::ReadByte(WaterQuad + (num * 0x1C) + 0x1B);

	//CurrentWaterQuad = *(waterQuad*)(*(DWORD*)WaterQuad + (SelectedWaterQuad * 0x1C));
}

void DrawBoxWater(int current)
{
	GetWaterQuadData(current);
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
	int midX = ((int)CurrentWaterQuad.minX + (int)CurrentWaterQuad.maxX) / 2;
	int midY = ((int)CurrentWaterQuad.minY + (int)CurrentWaterQuad.maxY) / 2;
	GRAPHICS::DRAW_LINE(coords.x, coords.y, coords.z, (float)midX, (float)midY, CurrentWaterQuad.height + 1.0f, 255, 0, 0, 255);
	GRAPHICS::DRAW_LINE((float)((int)CurrentWaterQuad.minX), (float)((int)CurrentWaterQuad.minY), CurrentWaterQuad.height, (float)((int)CurrentWaterQuad.minX), (float)((int)CurrentWaterQuad.maxY), CurrentWaterQuad.height, 255, 0, 0, 255);
	GRAPHICS::DRAW_LINE((float)((int)CurrentWaterQuad.minX), (float)((int)CurrentWaterQuad.maxY), CurrentWaterQuad.height, (float)((int)CurrentWaterQuad.maxX), (float)((int)CurrentWaterQuad.maxY), CurrentWaterQuad.height, 255, 0, 0, 255);
	GRAPHICS::DRAW_LINE((float)((int)CurrentWaterQuad.maxX), (float)((int)CurrentWaterQuad.maxY), CurrentWaterQuad.height, (float)((int)CurrentWaterQuad.maxX), (float)((int)CurrentWaterQuad.minY), CurrentWaterQuad.height, 255, 0, 0, 255);
	GRAPHICS::DRAW_LINE((float)((int)CurrentWaterQuad.maxX), (float)((int)CurrentWaterQuad.minY), CurrentWaterQuad.height, (float)((int)CurrentWaterQuad.minX), (float)((int)CurrentWaterQuad.minY), CurrentWaterQuad.height, 255, 0, 0, 255);
}

Vector2 ReturnWaterXY(int i)
{
	float minX = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x00);
	float minY = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x02);
	float maxX = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x04);
	float maxY = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x06);
	int midX = ((int)minX + (int)maxX) / 2;
	int midY = ((int)minY + (int)maxY) / 2;
	Vector2 A = { midX , midY };
	return A;
}

float ReturnWaterHeight(int i)
{
	return *(float*)(WaterQuad + (i * 0x1C) + 0x14);
}

void DrawViewName(int i)
{
	
	waterQuad UNKO;
	UNKO.minX = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x00);
	UNKO.minY = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x02);
	UNKO.maxX = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x04);
	UNKO.maxY = *(int16_t*)(WaterQuad + (i * 0x1C) + 0x06);

	UNKO.a1 = *(BYTE*)(WaterQuad + (i * 0x1C) + 0x08);
	UNKO.a2 = *(BYTE*)(WaterQuad + (i * 0x1C) + 0x09);
	UNKO.a3 = *(BYTE*)(WaterQuad + (i * 0x1C) + 0x0A);
	UNKO.a4 = *(BYTE*)(WaterQuad + (i * 0x1C) + 0x0B);

	UNKO.height = *(float*)(WaterQuad + (i * 0x1C) + 0x14);

	Vector3 WaterQuadCoords = { ((int)UNKO.minX + (int)UNKO.maxX) / 2 , ((int)UNKO.minY + (int)UNKO.maxY) / 2 , UNKO.height };
	Vector3 MyC = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
	if (!UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(WaterQuadCoords.x, WaterQuadCoords.y, WaterQuadCoords.z, &QuadScreenX, &QuadScreenY))
	{
		drawText(quadFormatStr(i), 0, QuadScreenX, QuadScreenY, 0.5, 0.5, 0, 255, 0, 255, true);
	}
}
#pragma endregion

#pragma region Weapon
uint GET_WEAPONS(uint weaponHash)
{
	uint Hash, Zero, r7, r9, r10;
	ulong r8;
	int r6, r4;

	Hash = weaponHash;
	Zero = 0;
	if (Hash == 0)
	{
		Hash = Zero;
		goto End;
	}
	r4 = 0x21478E8;
	r6 = PS3::ReadInt16(r4 + 0x24);
	r6--;
	if (r6 < 0)
	{
		Hash = Zero;
		goto End;
	}
	else
	{
		r7 = Zero;
		r4 = PS3::ReadInt32(r4 + 0x20);

	start:;
		r10 = r6 + r7;
		r10 = r10 >> 1;
		r8 = r10 << 2;
		r8 = r4 + r8;
		r9 = (uint)(r8 & 0xFFFFFFFF);
		r9 = PS3::ReadUInt32(r9);
		r8 = PS3::ReadUInt32(r9 + 8);
		if (Hash != r8)
		{
			if (Hash >= r8)
			{
				r7 = r10 + 1;
			}
			else
			{
				r6 = r10 - 1;
			}

			if (r6 >= r7)
			{
				goto start;
			}
			else
			{
				Hash = Zero;
				goto End;
			}
		}
		else
		{
			if (r9 != 0)
			{
				Hash = r9;
				goto End;
			}
			else
			{
				Hash = Zero;
				goto End;
			}
		}
	}

End:;
	return Hash;
}

void GiveWeaponPed(int Ped, int WeaponHash, int ammo = -1)
{
	WEAPON::GIVE_WEAPON_TO_PED(Ped, WeaponHash, ammo, 1, 1);
}

Hash weaponAddons[] = { COMPONENT_AT_SCOPE_MACRO, COMPONENT_AT_SCOPE_MACRO_02, COMPONENT_AT_SCOPE_SMALL, COMPONENT_AT_SCOPE_SMALL_02, COMPONENT_AT_SCOPE_MEDIUM, COMPONENT_AT_SCOPE_LARGE, COMPONENT_AT_SCOPE_MAX, COMPONENT_AT_RAILCOVER_01, COMPONENT_AT_AR_AFGRIP, COMPONENT_AT_PI_FLSH, COMPONENT_AT_AR_FLSH, COMPONENT_PISTOL_CLIP_02, COMPONENT_COMBATPISTOL_CLIP_02, COMPONENT_APPISTOL_CLIP_02, COMPONENT_MICROSMG_CLIP_02, COMPONENT_SMG_CLIP_02, COMPONENT_ASSAULTRIFLE_CLIP_02, COMPONENT_CARBINERIFLE_CLIP_02, COMPONENT_ADVANCEDRIFLE_CLIP_02, COMPONENT_MG_CLIP_02, COMPONENT_COMBATMG_CLIP_02, COMPONENT_ASSAULTSHOTGUN_CLIP_02, COMPONENT_PISTOL50_CLIP_02, COMPONENT_ASSAULTSMG_CLIP_02, COMPONENT_SNSPISTOL_CLIP_02, COMPONENT_COMBATPDW_CLIP_02, COMPONENT_HEAVYPISTOL_CLIP_02, COMPONENT_SPECIALCARBINE_CLIP_02, COMPONENT_BULLPUPRIFLE_CLIP_02, COMPONENT_VINTAGEPISTOL_CLIP_02, COMPONENT_MARKSMANRIFLE_CLIP_02, COMPONENT_HEAVYSHOTGUN_CLIP_02, COMPONENT_GUSENBERG_CLIP_02 };
void BruteForceWeaponAddons(Ped ped, Hash weaponHash, bool bSilencer)
{
	static Hash weaponAddons[] = { COMPONENT_AT_SCOPE_MACRO, COMPONENT_AT_SCOPE_MACRO_02, COMPONENT_AT_SCOPE_SMALL, COMPONENT_AT_SCOPE_SMALL_02, COMPONENT_AT_SCOPE_MEDIUM, COMPONENT_AT_SCOPE_LARGE, COMPONENT_AT_SCOPE_MAX, COMPONENT_AT_RAILCOVER_01, COMPONENT_AT_AR_AFGRIP, COMPONENT_AT_PI_FLSH, COMPONENT_AT_AR_FLSH, COMPONENT_PISTOL_CLIP_02, COMPONENT_COMBATPISTOL_CLIP_02, COMPONENT_APPISTOL_CLIP_02, COMPONENT_MICROSMG_CLIP_02, COMPONENT_SMG_CLIP_02, COMPONENT_ASSAULTRIFLE_CLIP_02, COMPONENT_CARBINERIFLE_CLIP_02, COMPONENT_ADVANCEDRIFLE_CLIP_02, COMPONENT_MG_CLIP_02, COMPONENT_COMBATMG_CLIP_02, COMPONENT_ASSAULTSHOTGUN_CLIP_02, COMPONENT_PISTOL50_CLIP_02, COMPONENT_ASSAULTSMG_CLIP_02, COMPONENT_SNSPISTOL_CLIP_02, COMPONENT_COMBATPDW_CLIP_02, COMPONENT_HEAVYPISTOL_CLIP_02, COMPONENT_SPECIALCARBINE_CLIP_02, COMPONENT_BULLPUPRIFLE_CLIP_02, COMPONENT_VINTAGEPISTOL_CLIP_02, COMPONENT_MARKSMANRIFLE_CLIP_02, COMPONENT_HEAVYSHOTGUN_CLIP_02, COMPONENT_GUSENBERG_CLIP_02 };
	for (int i = 0; i < 33; i++)
	{
		if (WEAPON::_0xB1817BAA(weaponHash, weaponAddons[i]))
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, weaponAddons[i]);
	}
	if (bSilencer)
	{
		static Hash silencers[] = { COMPONENT_AT_PI_SUPP, COMPONENT_AT_PI_SUPP_02, COMPONENT_AT_AR_SUPP, COMPONENT_AT_SR_SUPP, COMPONENT_AT_AR_SUPP_02 };
		for (int i = 0; i < 5; i++)
		{
			if (WEAPON::_0xB1817BAA(weaponHash, silencers[i])) {
				if (weaponHash != WEAPON_ADVANCEDRIFLE && WEAPON::GET_WEAPONTYPE_GROUP(weaponHash) != WEAPON_TYPE_GROUP_SHOTGUN)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, silencers[i]);
			}
		}
		if (weaponHash == WEAPON_SNIPERRIFLE || weaponHash == WEAPON_MICROSMG)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, COMPONENT_AT_AR_SUPP_02);
	}
}

void UnlimitedAmmo()
{
	if (infiniteammo)
	{
		char AAA[] = { 59, 160, 3, 231 };
		char BBB[] = { 56, 224, 0, 99 };
		PS3::WriteBytes(0xFD2A44, AAA, 4);
		PS3::WriteBytes(0xFDDDC0, BBB, 4);
	}
	else
	{
		char CCC[] = { 99,253,0,0 };
		char DDD[] = { 96,135,0,0 };
		PS3::WriteBytes(0xFD2A44, CCC, 4);
		PS3::WriteBytes(0xFDDDC0, DDD, 4);
	}
}

void SniperCameraSet(int Offset)
{
	if (Offset != 0)
	{
		int HeavySniper = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"));
		int Camera = PS3::ReadInt32(HeavySniper + DefaultCameraHash);
		PS3::WriteInt32(Offset + DefaultCameraHash, Camera);
	}
	else
	{
		NotifyDown("オフセットサーチが失敗しています。", 1000);
	}
}

void HighSpeedStungun(int Offset)
{
	int MinusOne = 0xBF800000;
	PS3::WriteInt32(Offset + TimeBetweenShots, MinusOne);
}

void SetWeaponFlag(uint Offset)
{
	int APWP = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_APPISTOL"));
	if (Offset != 0)
	{
		int Weapon1 = PS3::ReadInt32(APWP + WeaponFlags1);
		int Weapon2 = PS3::ReadInt32(APWP + WeaponFlags2);
		int Weapon3 = PS3::ReadInt32(APWP + WeaponFlags3);
		int Weapon4 = PS3::ReadInt32(APWP + Group);
		PS3::WriteInt32(Offset + WeaponFlags1, Weapon1);
		PS3::WriteInt32(Offset + WeaponFlags2, Weapon2);
		PS3::WriteInt32(Offset + WeaponFlags3, Weapon3);
		PS3::WriteInt32(Offset + Group, Weapon4);
		NotifyDown("セット完了");
	}
	else
	{
		NotifyDown("オフセット検索が失敗しています。");
	}
}

bool RequestBullet(int BulletHash)
{
	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(BulletHash))
	{
		WEAPON::REQUEST_WEAPON_ASSET(BulletHash, 31, 0);
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(BulletHash));
	}
}

void InfiniteAmmoManzi()
{
	int AmmoOffset[] = { 59, 128, 30, 97, 179, 153, 0, 80, 179, 153, 0, 82, 127, 151, 227, 120, 127, 155, 227, 120 };
	//0xF6C68
	for (int i = 0; i < 20; i++)
	{
		*(char*)(0xF6C68 + (i)) = AmmoOffset[i];
	}
}

void AmmoSet(int AmmoWord, int ExplosionType = 5)
{
	uint Offset;
	int Hash;
	switch (AmmoWord)
	{
	case GreenLaser:
		Hash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LASER");
		Offset = GET_WEAPONS(Hash);
		break;
	case RedLaser:
		Hash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER");
		Offset = GET_WEAPONS(Hash);
		break;

	case Rocket:
		Hash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET");
		Offset = GET_WEAPONS(Hash);
		break;

	}
	RequestBullet(Hash);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, -1, true, true);
	WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), Hash, -1);
	int AmmoOffset = PS3::ReadInt32(Offset + AmmoInfo);
	int NoobOffset = PS3::ReadInt32(SelectedWeaponOffset2 + AmmoInfo);
	int HeavyOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"));
	int APOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_APPISTOL"));
	int APRange = PS3::ReadInt32(APOffset + WeaponRange);
	PS3::WriteUInt32(AmmoOffset + Explosion_Default, ExplosionType);
	PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
	PS3::WriteUInt32(Offset + FireType, 4);
	PS3::WriteUInt32(SelectedWeaponOffset2 + FireType, 4);
	PS3::WriteUInt32(SelectedWeaponOffset2 + AmmoInfo, AmmoOffset);
	PS3::WriteUInt32(SelectedWeaponOffset2 + WeaponRange, APRange);
	PS3::WriteInt32(SelectedWeaponOffset2 + DamageType, 0x40A00000);
	if (NoobOffset != 0)
	{
		PS3::WriteUInt32(NoobOffset + Explosion_Default, ExplosionType);
		PS3::WriteUInt32(NoobOffset + ProjectileFlags, 4);
	}
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), SelectedWeaponHash, -1, true, true);
}

#pragma endregion

#pragma region Script

union ScriptArg
{
	unsigned int ui; float f; int i; char *str;
};
namespace SCRIPT
{
	static void TRIGGER_SCRIPT_EVENT(int always1, ScriptArg *argsStruct, int argsStructCount, int playerbitset) { invoke<Void>(0x54763B35, always1, argsStruct, argsStructCount, playerbitset); }
};
namespace PlayerMods
{
	namespace eventCreator
	{
		void callScriptEvent(ScriptArg *args, int argsCount, unsigned int playerBits) { SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, argsCount, playerBits); }
	};
};

void removePlayerWantedLevel(int player)
{
	int args[2];
	args[0] = 356;
	args[1] = player;
	TriggerScriptEvent(args, 3, player);
}

void GiveRP(int player = PLAYER::PLAYER_ID(), int RP = 0)
{
	int Args2[5];
	Args2[0] = 0xD8;
	Args2[1] = player;
	Args2[2] = RP;
	Args2[3] = 0;
	Args2[4] = 0;
	TriggerScriptEvent(Args2, 5, player);
}

void changePlayerWeather(int Address)
{

	int Args2[22];
	Args2[0] = 16;
	Args2[1] = selectedPlayer;
	//strcpy((char*)&args[2].i,weather);
	//printf("\n%s\n",(char*)&args[2].i);
	Args2[2] = Address;
	TriggerScriptEvent(Args2, 22, selectedPlayer);
}

void ForceKickByNonHost(int player = PLAYER::PLAYER_ID())
{
	int Args3[5];
	Args3[0] = 0x2;
	Args3[1] = player;
	Args3[2] = 0x35;
	Args3[3] = 0;
	Args3[4] = 0;
	TriggerScriptEvent(Args3, 6, player);
}

void kickPlayerNonHost(int player) 
{
	PLAYER::GET_PLAYER_PED(player);
	unsigned int playerBit = (1 << player);
	ScriptArg args[3] = { 0x2,player,0x35 };
	SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, playerBit);
}

void hostforce(int player)
{
	int Var0[15];
	Var0[0] = 181;
	Var0[1] = player;
	Var0[2] = PS3::Read_Global(1838493);
	Var0[3] = PS3::Read_Global(1838493 + 1);
	Var0[4] = 0;
	Var0[5] = PS3::Read_Global(1838493 + 2);
	Var0[8] = PS3::Read_Global(1838493 + 5);
	Var0[14] = PS3::Read_Global(2399048 + 1 + 1481 + 13);
	TriggerScriptEvent(Var0, 15, player);
}

void PhantomError(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int playerBit = (1 << player);
	ScriptArg args[3] = { 0x2,player,0x456 };
	SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, playerBit);
}
void PhantomFreeze(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int playerBit = (1 << player);
	ScriptArg args[3] = { 0x2,player,0x789 };
	SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, playerBit);
}
void ForceTutorial(int player) {
	PLAYER::GET_PLAYER_PED(player);
	int args[3] = { 0x3 ,player ,0x14 };
	TriggerScriptEvent(args, 3, player);
}

void teleportPlayerIntoGolfEvent(int player) {
	PLAYER::GET_PLAYER_PED(player);
	int args[3] = { 0x3 ,player ,0x37 };
	TriggerScriptEvent(args, 3, player);
}

void teleportPlayerIntoArmWrestlingEvent(int player) {
	PLAYER::GET_PLAYER_PED(player);
	int args[3] = { 0x3 ,player ,0x35 };

	TriggerScriptEvent(args, 3, player);
}

void sendCash2(int player) {
	PLAYER::GET_PLAYER_PED(player);

	int args[3];
	args[0] = 0x3;//0xDB
	args[1] = player;//player...   I think you set to 40 to make it work post-patch. I haven't tested
	args[2] = 0x40;

	TriggerScriptEvent(args, 4, player);
}

void givePlayerMoney_12(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x25 };
	TriggerScriptEvent(args, 3, player);
}

void teleportPlayerIntoDartsEvent(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x3,player , 0x36 };

	TriggerScriptEvent(args, 3, player);
}

void makePlayerFakeLeave(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x2 ,player,0x34 };
	TriggerScriptEvent(args, 3, player);
}

void givePlayerMoney(int player) {//refunds to themself. max 20k
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x39 };
	TriggerScriptEvent(args, 3, player);
}

void givePlayerMoney1(int player, int amount) {//refunds to themself. max 20k
	for (int i = 16; i < amount / 20000 + 16; i++) {
		ScriptArg args[4];
		args[0].i = 219;//0xDA = 218;
		args[1].i = i;//player;//cash giver (them cuz they refund themself)
		args[2].i = 20000;//46
		args[3].i = 1;
		unsigned int bits = (1 << player);//0xFFFFFFFF;
		PlayerMods::eventCreator::callScriptEvent(args, 4, bits);
	}
}

void PlayerRace(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x41 };
	TriggerScriptEvent(args, 3, player);
}

void givePlayerMoney_8(int player) {
	PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x1B };
	TriggerScriptEvent(args, 3, player);
}

void apartmentInvite(int sender, int reciever)
{//I think it just sends it to the whole lobby
	int args[2];
	args[0] = 32;
	args[1] = sender;
	TriggerScriptEvent(args, 2, reciever);
}

#pragma endregion

#pragma region Player Option
void SetSnowOnGround(bool unko)
{
	if (unko == false)
	{
		PS3::SetTunable(4715, 0);
	}
	else if (unko == true)
	{
		PS3::SetTunable(4715, 1);
	}
}



void ChangeAllPlayerChange()
{
	if (PS3::ReadInt32(WeatherAddress1) != 0x60000000 || PS3::ReadInt32(WeatherAddress2) != 0x60000000 || PS3::ReadInt32(WeatherAddress3) != 0x60000000)
	{
		PS3::WriteBytes(WeatherAddress1, NotWrite, 4);
		PS3::WriteBytes(WeatherAddress2, NotWrite, 4);
		PS3::WriteBytes(WeatherAddress3, NotWrite, 4);
	}
	switch (CHANGEType)
	{
	case 0:SetSnowOnGround(false); break;
	case 1:SetSnowOnGround(true); break;
	case 2:SetSnowOnGround(false); break;
	case 3:SetSnowOnGround(false); break;
	case 4:SetSnowOnGround(false); break;
	case 5:SetSnowOnGround(false); break;
	case 6:SetSnowOnGround(false); break;
	case 7:SetSnowOnGround(false); break;
	case 8:SetSnowOnGround(false); break;
	case 9:SetSnowOnGround(false); break;
	case 10:SetSnowOnGround(true); break;
	case 11:SetSnowOnGround(true); break;
	case 12:SetSnowOnGround(false); break;
	}
	GAMEPLAY::SET_WEATHER_TYPE_NOW(CHANGEhsh[CHANGEType]);
	GAMEPLAY::SET_OVERRIDE_WEATHER(CHANGEhsh[CHANGEType]);
	GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(CHANGEhsh[CHANGEType], 0);
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(CHANGEhsh[CHANGEType]);
}
#pragma endregion

#pragma region ESP
RGBA MenuColour = { 255,0,0 };
void MarkerESP(int client, RGBA MenuColour)
{
	Vector3 playerPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(PLAYER::GET_PLAYER_PED(client), 0, 0, 0.0);
	playerPosition.z += 1.5;
	GRAPHICS::DRAW_MARKER(1, playerPosition.x, playerPosition.y, playerPosition.z - 1, 0, 0, 0, 0, 0, 0, .1, .1, .45, MenuColour.R, MenuColour.B, MenuColour.B, 255, 0, 0, 2, 0, 0, 0, 0);
	GRAPHICS::DRAW_MARKER(25, playerPosition.x, playerPosition.y, playerPosition.z - 2.5, 0, 0, 0, 0, 0, 0, 1.0, 1.0, 45, MenuColour.R, MenuColour.B, MenuColour.B, 255, 1, 0, 2, 0, 0, 0, 0);
	GRAPHICS::DRAW_MARKER(21, playerPosition.x, playerPosition.y, playerPosition.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, MenuColour.R, MenuColour.B, MenuColour.B, 255, true, false, 2, true, false, false, false);
}

void Kiste(Vector3 Cords, RGBA Colour)
{
	float XXX = 1.0;
	float ZZZ = .7;
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y + XXX, Cords.z + ZZZ, Cords.x + XXX, Cords.y - XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y - XXX, Cords.z + ZZZ, Cords.x - XXX, Cords.y - XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y - XXX, Cords.z + ZZZ, Cords.x - XXX, Cords.y + XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y + XXX, Cords.z + ZZZ, Cords.x + XXX, Cords.y + XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y + XXX, Cords.z - ZZZ, Cords.x + XXX, Cords.y - XXX, Cords.z - ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y - XXX, Cords.z - ZZZ, Cords.x - XXX, Cords.y - XXX, Cords.z - ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y - XXX, Cords.z - ZZZ, Cords.x - XXX, Cords.y + XXX, Cords.z - ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y + XXX, Cords.z - ZZZ, Cords.x + XXX, Cords.y + XXX, Cords.z - ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y + XXX, Cords.z - ZZZ, Cords.x + XXX, Cords.y + XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x + XXX, Cords.y - XXX, Cords.z - ZZZ, Cords.x + XXX, Cords.y - XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y - XXX, Cords.z - ZZZ, Cords.x - XXX, Cords.y - XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
	GRAPHICS::DRAW_LINE(Cords.x - XXX, Cords.y + XXX, Cords.z - ZZZ, Cords.x - XXX, Cords.y + XXX, Cords.z + ZZZ, Colour.R, Colour.G, Colour.B, 255);
}
#pragma endregion

#pragma region ステータスエディター

void addBatSports(bool toggle)
{
	int Player_Index = selectedPlayer;
	if (toggle)
	{
		int Player_Index = selectedPlayer;
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_WAS_I_BAD_SPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OVERALL_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_CHAR_IS_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_BECAME_BADSPORT_NUM"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DESTROYED_PVEHICLES"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_WAS_I_BAD_SPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OVERALL_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_CHAR_IS_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_BECAME_BADSPORT_NUM"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_DESTROYED_PVEHICLES"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("BAD_SPORT_BITSET"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_WAS_I_BAD_SPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), 100);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 100);
	}
	else
	{
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_WAS_I_BAD_SPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_OVERALL_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_CHAR_IS_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DESTROYED_PVEHICLES"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_BAD_SPORT_BITSET"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_WAS_I_BAD_SPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_OVERALL_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_CHAR_IS_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_BECAME_BADSPORT_NUM"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_DESTROYED_PVEHICLES"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("BAD_SPORT_BITSET"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_WAS_I_BAD_SPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), 0);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 0);
	}
}

void WalkSPeed(bool toggle)
{
	int Player_Index = selectedPlayer;
	if (toggle)
	{
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1);

		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_1_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_2_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_3_UNLCK"), -1);

		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_1_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_2_UNLCK"), -1);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_3_UNLCK"), -1);
	}
	else
	{
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), 600);

		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_1_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_2_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_ABILITY_3_UNLCK"), 600);

		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_1_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_2_UNLCK"), 600);
		setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_FM_ABILITY_3_UNLCK"), 600);
	}
}

void InventoryMax()
{
	int Player_Index = selectedPlayer;

	//アーマー
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_1_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_2_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_3_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_4_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_5_COUNT"), 9999);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_1_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_2_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_3_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_4_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_5_COUNT"), 9999);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_1_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_2_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_3_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_4_COUNT"), 9999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_5_COUNT"), 9999);

	//スナック
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), INT_MAX);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), INT_MAX);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_YUM_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_HEALTH_SNACKS"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_EPIC_SNACKS"), INT_MAX);

	//花火
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 999999);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), 999999);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_BLUE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_WHITE"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_RED"), 999999);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_BLUE"), 999999);

	//スモーク
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), INT_MAX);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CIGARETTES_BOUGHT"), INT_MAX);

}

void Skill()
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), 100);
}

void CrewRank()//クルーランク
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_0"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_1"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_2"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_3"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_4"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_0"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_1"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_2"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_3"), 900000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_4"), 900000);
}

void CashGiftplayer()//10億
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_NEW"), 1000000000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CASH_GIFT_NEW"), 1000000000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CASH_GIFT_NEW"), 1000000000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CASH_GIFT_NEW"), 1000000000);
}

void MaxSkillplayer()//スキルマックス
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), 100);
}

void MaxSnackplayer()//スナック
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_YUM_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_HEALTH_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_EPIC_SNACKS"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_NUMBER_OF_ORANGE_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CIGARETTES_BOUGHT"), 12345678);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_WHITE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_RED"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), 9999999);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_BLUE"), 9999999);
}

void Modderroll()
{
	setPlayerStat(selectedPlayer, STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_1_COUNT "), 9999999, 0), 1);
	setPlayerStat(selectedPlayer, STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_2_COUNT "), 9999999, 0), 1);
	setPlayerStat(selectedPlayer, STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_3_COUNT "), 9999999, 0), 1);
	setPlayerStat(selectedPlayer, STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_4_COUNT "), 9999999, 0), 1);
	setPlayerStat(selectedPlayer, STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP_CHAR_ARMOUR_5_COUNT"), 9999999, 0), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("SHOOTING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STAMINA"), 150);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STRENGTH"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("LUNG_CAPACITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("WHEELIE_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("FLYING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STEALTH_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_STAMINA"), 150);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_STRENGTH"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_LUNG_CAPACITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_WHEELIE_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FLYING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_STEALTH_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SHOOTING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_STAMINA"), 150);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_STRENGTH"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_LUNG_CAPACITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_WHEELIE_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FLYING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_STEALTH_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("SHOOTING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STAMINA"), 150);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STRENGTH"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("LUNG_CAPACITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("WHEELIE_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("FLYING_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("STEALTH_ABILITY"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CHAR_ABILITY_1_UNLCK"), 200);
}

void DisableAccount(int player)
{
	SetPlayerStats_Hash(player, 0xF1AD9B2B, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x3EB3FA6, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x4D3AD244, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x724BAE22, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x7D15C3B6, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x279D18C6, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x3977BC7B, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x436AD061, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x5600758C, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xDFBF8908, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xF26E2E65, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xFD3743F7, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x9A45179F, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x4840E8F, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x83079483, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x671634FD, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x87CD697F, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xA4C198D9, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x6881E6B9, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xB7D704EB, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xACF9F1C2, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xB7869E, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xBE09FD96, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x98BA126, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x4DAA973A, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x25FD26C4, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x3C4E73A1, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xE155A3CA, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xA5E699CB, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0xD0CD234, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x34868FD3, 0x7FFFFFFF);
	SetPlayerStats_Hash(player, 0x9CD69DC4, 0x7FFFFFFF);
}


void muteBanPlayer(int a_uiRecevPlayerIndex)
{
	SetPlayerStats_Hash(a_uiRecevPlayerIndex, GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED"), -1);
}
int CharacterVar;

enum CharacterNumber
{
	CharacterOne = 0,
	CharacterSec = 1,
};

void STAT_SET_INT(char* objectkey, int A, int B)
{
	if (strstr(objectkey, "MPPLY_") != NULL)
	{
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(objectkey), A, B);
	}
	else
	{
		char ObjectKey[30];
		char *CharacterSet;
		switch (CharacterVar)
		{
		case CharacterOne:
			CharacterSet = "MP0_";
			break;
		case CharacterSec:
			CharacterSet = "MP1_";
			break;
		}
		strcpy(ObjectKey, CharacterSet);
		strcat(ObjectKey, objectkey);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(ObjectKey), A, B);
	}
}

// bool型
void STAT_SET_BOOL(char* objectkey, int A, int B)
{
	if (strstr(objectkey, "MPPLY_") != NULL)
	{
		STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(objectkey), A, B);
	}
	else
	{
		char ObjectKey[30];
		char *CharacterSet;
		switch (CharacterVar)
		{
		case CharacterOne:
			CharacterSet = "MP0_";
			break;
		case CharacterSec:
			CharacterSet = "MP1_";
			break;
		}
		strcpy(ObjectKey, CharacterSet);
		strcat(ObjectKey, objectkey);
		STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(ObjectKey), A, B);
	}
}

// float型
void STAT_SET_FLOAT(char* objectkey, float A, int B)
{
	if (strstr(objectkey, "MPPLY_") != NULL)
	{
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(objectkey), A, B);
	}
	else
	{
		char ObjectKey[30];
		char *CharacterSet;
		switch (CharacterVar)
		{
		case CharacterOne:
			CharacterSet = "MP0_";
			break;
		case CharacterSec:
			CharacterSet = "MP1_";
			break;
		}
		strcpy(ObjectKey, CharacterSet);
		strcat(ObjectKey, objectkey);
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(ObjectKey), A, B);
	}
}

void NinetyPer()
{
	STAT_SET_INT("MPPLY_COMMEND_STRENGTH", 100, 1);
	STAT_SET_INT("MPPLY_FRIENDLY", 300, 1);
	STAT_SET_INT("MPPLY_HELPFUL", 100, 1);
	STAT_SET_INT("MPPLY_GRIEFING", 0, 0);
	STAT_SET_INT("MPPLY_VC_HATE", 0, 0);
	STAT_SET_INT("MPPLY_VC_ANNOYINGME", 0, 0);
	STAT_SET_INT("MPPLY_OFFENSIVE_LANGUAGE", 0, 0);
	STAT_SET_INT("MPPLY_OFFENSIVE_TAGPLATE", 0, 0);
	STAT_SET_INT("MPPLY_OFFENSIVE_UGC", 0, 0);
	STAT_SET_INT("MPPLY_BAD_CREW_MOTTO", 0, 0);
	STAT_SET_INT("MPPLY_BAD_CREW_STATUS", 0, 0);
	STAT_SET_INT("MPPLY_BAD_CREW_EMBLEM", 0, 0);
	STAT_SET_INT("MPPLY_GAME_EXPLOITS", 0, 0);
	STAT_SET_INT("MPPLY_EXPLOITS", 0, 0);
	STAT_SET_INT("MPPLY_ISPUNISHED", 0, 0);
	STAT_SET_FLOAT("MPPLY_OVERALL_BADSPORT", 0.0f, 1);
	STAT_SET_FLOAT("TIMES_CHEATED", 0.0f, 1);
	STAT_SET_FLOAT("PLAYER_MENTAL_STATE", 0.0f, 1);
	STAT_SET_BOOL("MPPLY_IS_CHEATER", 0, 1);
	STAT_SET_BOOL("MPPLY_CHAR_IS_BADSPORT", 0, 1);
	STAT_SET_BOOL("MPPLY_ISPUNISHED", 0, 1);
	STAT_SET_BOOL("MPPLY_IS_HIGH_EARNER", 0, 1);
	STAT_SET_INT("MPPLY_IS_CHEATER_TIME", 0, 1);
	STAT_SET_INT("MP1_CHEAT_BITSET", 0, 1);
	STAT_SET_INT("MP1_BAD_SPORT_BITSET", 0, 1);
	STAT_SET_INT("MPPLY_BECAME_BADSPORT_NUM", 0, 1);
	STAT_SET_INT("MPPLY_BECAME_CHEATER_NUM", 0, 1);
	STAT_SET_INT("MPPLY_REPORT_STRENGTH", 32, 1);
	STAT_SET_INT("MPPLY_COMMEND_STRENGTH", 100, 1);
	STAT_SET_INT("MPPLY_FRIENDLY", 100, 1);
	STAT_SET_INT("MPPLY_HELPFUL", 100, 1);
	STAT_SET_INT("MPPLY_GRIEFING", 0, 1);
	STAT_SET_INT("MPPLY_OFFENSIVE_LANGUAGE", 0, 1);
	STAT_SET_INT("MPPLY_OFFENSIVE_UGC", 0, 1);
	STAT_SET_INT("MPPLY_VC_HATE", 0, 1);
	STAT_SET_INT("MPPLY_GAME_EXPLOITS", 0, 1);
	STAT_SET_INT("PLAYER_MUTED", 0, 1);

	
}

void Fireworksplayer()
{
	if (selectedPlayer != PLAYER::PLAYER_ID()) {
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_WHITE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_RED"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_BLUE"), 9999999);
	}
}

void MaxArmorplayer()
{
	if (selectedPlayer != PLAYER::PLAYER_ID()) {
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_1_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_2_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_3_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_4_COUNT"), 9999999);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MP_CHAR_ARMOUR_5_COUNT"), 9999999);
	}
}

void ChromeRimsplayer()
{
	if (selectedPlayer != PLAYER::PLAYER_ID()) {
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS"), 1);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 25);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_NIGHTVISION_KILLS"), 1);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_CAPTURES"), 25);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_DROPOFF_CAP_PACKAGES"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_CARRIER_CAPTURE"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEISTS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEIST_SETUP_JOB"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_NIGHTVISION_KILLS"), 1);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);

	}
}

void RedesignPromtplayer(int selectedPlayer)
{
	if (selectedPlayer != PLAYER::PLAYER_ID()) {
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_MENTAL_STATE"), 100);
		setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_MENTAL_STATE"), 100);
	}
}

void CLTHSplayer()//髪型解除
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_1"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_2"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_3"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_4"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_5"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_6"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_CLTHS_AVAILABLE_HAIR_7"), -1);
}

void killsplayer()//キル数
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), 500);

}

void deathsplayer()//デス数
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), 500);

}

void LSC()
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_NIGHTVISION_KILLS"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_CAPTURES"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_NIGHTVISION_KILLS"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
}
#pragma endregion

#pragma region Self Option


void NoCops(bool toggle)
{
	if (toggle)
	{
		Vector3 KuronekoGamesDDR = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
		GAMEPLAY::CLEAR_AREA_OF_COPS(KuronekoGamesDDR.x, KuronekoGamesDDR.y, KuronekoGamesDDR.z, 100000, 0);
		PLAYER::SET_MAX_WANTED_LEVEL(0);
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	}
	else
	{
		PLAYER::SET_MAX_WANTED_LEVEL(5);
	}
}

void Super_Puch(bool toggle)
{
	unsigned int Result = PS3::ReadUInt32((int)PS3::ReadUInt32(0x1CFB0A0) + 0x28) + 0xC;
	if (toggle)
	{
		for (int i = 0; i < 21; i++)
		{
			PS3::WriteFloat(Result + (i * 0x20), 10000000000);
			PS3:: WriteFloat(Result + (i * 0x20) + 4, 10000000000);
		}
	}
	else
	{
		for (int i = 0; i < 21; i++)
		{
			PS3::WriteFloat(Result + (i * 0x20), 25);
			PS3::WriteFloat(Result + (i * 0x20) + 4, 25);
		}
	}
}

void RevealPeople(bool flag)
{
	if (flag)
	{
		PS3::Write_Global(2394218 + 56, 2147483647);
		PS3::Write_Global(2390201 + PLAYER::PLAYER_ID() * 223 + 172, 1);
	}
	else
	{
		PS3::Write_Global(2390201 + PLAYER::PLAYER_ID() * 223 + 172, 0);
	}
}

void OffRadar(bool flag)
{
	if (flag)
	{
		PS3::WriteInt32(PS3::ReadInt32(0x1E70394) + 0x22284, 2147483647);
		PS3::Write_Global(2390201 + PLAYER::PLAYER_ID() * 223 + 170, 1);
		PS3::Write_Global(2394218 + 55, 2147483647);
	}
	else
	{
		PS3::WriteInt32(PS3::ReadInt32(0x1E70394) + 0x22284, 0);
	}
}

void CopsturnBlindEye(bool flag)
{
	if (flag)
	{
		PS3::Write_Global(2410912 + 4141, 5);
		PS3::Write_Global(2410912 + 4144, 2147483647);
	}
	else
	{
		PS3::Write_Global(2410912 + 4141, 0);
	}
}
#pragma endregion

#pragma region Ped
int CREATE_PED_NORMAL(Hash Name, Vector3 Location)
{
	Hash Hash = (Name);
	int Ped = 0;
	STREAMING::REQUEST_MODEL(Hash);
	if (STREAMING::HAS_MODEL_LOADED(Hash))
	{
		Ped = PED::CREATE_PED(21, Hash, Location.x, Location.y, Location.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Hash);
	}
	return Ped;
}

bool PedSpawnMethod(char* pedname)
{
	Hash Unko = GAMEPLAY::GET_HASH_KEY(pedname);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(Unko))
	{
		if (STREAMING::IS_MODEL_VALID(Unko))
		{
			STREAMING::REQUEST_MODEL(Unko);
			Vector3 coords;

			if (STREAMING::HAS_MODEL_LOADED(Unko))
			{
				coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
				PedList[PedIndex] = PED::CREATE_PED(21, Unko, coords.x, coords.y, coords.z, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(PedList[PedIndex]))
				{
					PedNameList[PedIndex] = PedName2;
					int Blip = UI::ADD_BLIP_FOR_ENTITY(PedList[PedIndex]);
					//BlipList[PedIndex] = UI::ADD_BLIP_FOR_ENTITY(PedList[PedIndex]);
					UI::SET_BLIP_SPRITE(Blip, 84);
					UI::SET_BLIP_SCALE(Blip, 1.2);
					UI::SET_BLIP_COLOUR(Blip, 3);
					if (IsPedBodyguard)
					{
						int Ped = PedList[PedIndex];
						int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
						PED::SET_PED_AS_GROUP_LEADER(PLAYER::PLAYER_PED_ID(), my_group);
						PED::SET_PED_AS_GROUP_MEMBER(Ped, my_group);
						PED::SET_PED_COMBAT_ABILITY(Ped, 100);
						PED::SET_PED_CAN_SWITCH_WEAPON(Ped, false);
					}
					if (IsPedHaveWeapon)
					{
						GiveWeaponPed(PedList[PedIndex], GAMEPLAY::GET_HASH_KEY("WEAPON_HOMINGLAUNCHER"));
					}
					if (IsPedInvincible)
					{
						bool flag = IsPedInvincible;
						PLAYER::SET_PLAYER_INVINCIBLE(PedList[PedIndex], flag);
						ENTITY::SET_ENTITY_INVINCIBLE(PedList[PedIndex], flag);
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PedList[PedIndex], flag);
						PED::SET_PED_CAN_RAGDOLL(PedList[PedIndex], !flag);
						PED::SET_PED_CAN_RAGDOLL(PedList[PedIndex], !flag);
						PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PedList[PedIndex], !flag);
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PedList[PedIndex], !flag);
						PED::SET_PED_RAGDOLL_ON_COLLISION(PedList[PedIndex], flag);
					}
					PedIndex++;
					if (PedIndex >= 10)
					{
						PedIndex = 0;
					}
					return true;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool SET_PLAYER_MODEL(Hash ModelHash)
{
	Vehicle CurrentVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	STREAMING::REQUEST_MODEL(ModelHash);
	if (STREAMING::HAS_MODEL_LOADED(ModelHash))
	{

		Hash WEAPONINFO_Current;
		bool WEAPONINFO_GotWeapon[58];
		int WEAPONINFO_Ammo[58];
		PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ModelHash);
		PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 200);
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == ModelHash)
		{
			for (int i = 0; i < 58; i++)
			{
				if (WEAPONINFO_GotWeapon[i])
				{
					WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WepArray[i], -1, false, true);
				}
			}
			
			if (ModelHash == 0xB881AEE)//hc_gunman
			{
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 3, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 1, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 1, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 1, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 1, 0, 0);
			}
			else if (ModelHash == 0xD86B5A95)//a_c_deer
				ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
			else if (ModelHash == 0x1250D7BA)//a_c_mtlion
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), false);
			if (ModelHash == 0x705E61F2 ||
				ModelHash == 0x1615AD62 ||
				ModelHash == 0x9C9EFFD8 ||
				ModelHash == 0xD174E983)//mp_m_freemode_01 mp_m_freemode_02 mp_f_freemode_01 mp_f_freemode_02
			{
				if (OtherCostume)
				{
					for (int i = 0; i < 12; i++)
						PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, SWITCH_DRAWABLE_VAR[i], SWITCH_TEXTURE_VAR[i], SWITCH_PALETTE_VAR[i]);
					OtherCostume = false;
				}
				else
				{
					for (int i = 0; i < 12; i++)
						PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, DRAWABLE_VAR[i], TEXTURE_VAR[i], PALETTE_VAR[i]);
				}
			}

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash);
			if (CurrentVeh != 0)
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), CurrentVeh, -1);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
#pragma endregion

#pragma region 天気
void CHANGE_WEATHER(char* WeatherName)
{
	GAMEPLAY::SET_WEATHER_TYPE_PERSIST(WeatherName);
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(WeatherName);
	GAMEPLAY::SET_WEATHER_TYPE_NOW(WeatherName);
	GAMEPLAY::SET_OVERRIDE_WEATHER(WeatherName);
}
#pragma endregion

#pragma region Object


void DeleteEntity(Entity Entity)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Entity, 1, 1);
	ENTITY::DELETE_ENTITY(&Entity);
}
void DeleteEntH4X(Entity Handle)
{
	RequestNetworkControl(Handle);
	RequestControlOfEnt(Handle);
	ENTITY::FREEZE_ENTITY_POSITION(Handle, false);
	ENTITY::DETACH_ENTITY(Handle, 1, 1);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Handle, 0, 1);
	ENTITY::DELETE_ENTITY(&Handle);
}


void ApplyForce(Entity ped_id, float x, float y, float z, float rx = 0, float ry = 0, float rz = 0)
{
	ENTITY::APPLY_FORCE_TO_ENTITY(ped_id, 1, x, y, z, rx, ry, rz, 0, 1, 1, 1, 0, 1);
}

void ATTACH_ENTITY_TO_ENTITY(Entity Kuttukuyatu, Entity Kuttukareruyatu, int boneIndex = 0x0, float x = 0, float y = 0, float z = 0, float maehoukou = 0, float yokohoukou = 0, float muki = 0)
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(Kuttukuyatu, Kuttukareruyatu, boneIndex, x, y, z, maehoukou, yokohoukou, muki, true, true, true, true, true, true);
}

bool Create_Map(char* MapObjectName)
{
	Hash ObjectHash = GAMEPLAY::GET_HASH_KEY(MapObjectName);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(ObjectHash))
	{
		if (STREAMING::IS_MODEL_VALID(ObjectHash))
		{
			STREAMING::REQUEST_MODEL(ObjectHash);
			Vector3 coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
			if (STREAMING::HAS_MODEL_LOADED(ObjectHash))
			{
				ObjectList[ObjectListIndex] = OBJECT::CREATE_OBJECT(ObjectHash, coords.x, coords.y, coords.z, 1, 1, 1);
				objectnamearray[ObjectListIndex] = MapObjectName;
				if (ENTITY::DOES_ENTITY_EXIST(ObjectList[ObjectListIndex]))
				{
					ENTITY::FREEZE_ENTITY_POSITION(ObjectList[ObjectListIndex], true);
					ObjectListIndex++;

					char buf[100];
					sprintf(buf, "Spawned: ~b~%s~HUD_COLOUR_WHITE~!", MapObjectName);
					NotifyDown(buf);
					if (ObjectListIndex >= 16)
					{
						ObjectListIndex = 0;
					}
					return true;
				}
				return false;
			}
			return false;
		}
	}
}
#pragma endregion

#pragma region Camera
bool isLockOnEntity(float ScreenX, float ScreenY)
{
	return (!(ScreenX <= 0.2 | ScreenX >= 0.8 | ScreenY <= 0.2 | ScreenY >= 0.8) && (ScreenX >= 0.3f && ScreenX <= 0.7f) && (ScreenY >= 0.3f && ScreenY <= 0.7f));
}

Vector3 GetCoordsInfrontOfCam(float distance)
{
	Vector3 Rot = GET_GAMEPLAY_CAM_ROT_orig(2);
	Vector3 Coord = GET_GAMEPLAY_CAM_COORD_orig();
	Rot.y = distance * SYSTEM::COS(Rot.x);
	Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);
	return Coord;
}

Vector3 get_coords_from_cam(float distance)
{
	Vector3 Rot = GET_GAMEPLAY_CAM_ROT_orig(2);
	Vector3 Coord = GET_GAMEPLAY_CAM_COORD_orig();

	Rot.y = distance * SYSTEM::COS(Rot.x);
	Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);

	return Coord;
}

Vector3 get_coords_from_entity_cam(float distance)
{
	Vector3 Coord;
	if (MoveAnimal)
	{
		Vector3 Rot = GET_CAM_ROT_orig(RideonAnimalsPedID, 2);
		Coord = GET_CAM_COORD_orig(RideonAnimalsPedID);

		Rot.y = distance * SYSTEM::COS(Rot.x);
		Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
		Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
		Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);

	}
	else
	{
		Vector3 Rot = GET_CAM_ROT_orig(DragonFireCamera, 2);
		Coord = GET_CAM_COORD_orig(DragonFireCamera);

		Rot.y = distance * SYSTEM::COS(Rot.x);
		Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
		Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
		Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);
	}
	return Coord;
}

Vector3 get_coords_from_entity(Entity entity, float distance, bool Minecraft = false)
{
	Vector3 Rot;
	if (Minecraft)
	{
		Rot = GET_GAMEPLAY_CAM_ROT_orig(2);
	}
	else
	{
		Rot = get_entity_rotation_orig(entity, 2);
	}
	Vector3 Coord = get_entity_coords_orig(entity, 1);

	Rot.y = distance * SYSTEM::COS(Rot.x);
	Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);

	return Coord;
}

Vector3 GET_COORDS_INFRONT(float Distance)
{
	float Tan = Distance * myTan(GET_GAMEPLAY_CAM_ROT_orig(2).y, 20);
	float UNKO[] = { 0, Distance, Distance * Tan };
	Vector3 Coords = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_orig(PLAYER::PLAYER_PED_ID(), UNKO);
	return Coords;
}
#pragma endregion

#pragma region Rocket
void VehicleWeaponsFunctionN(int Hash)
{
	Vector3 rot = GET_GAMEPLAY_CAM_ROT_orig(2);
	int launchDistance = 250;
	float launchSpeed = 500.0f;
	Vector3 spawnPosition = get_coords_from_cam(5.0);
	Vector3 endPosition = get_coords_from_cam(50.0);

	ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), rot.x, rot.y, rot.z, 2, true);

	float Start[] = { spawnPosition.x, spawnPosition.y, spawnPosition.z };
	float End[] = { endPosition.x, endPosition.y, endPosition.z };

	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R2))
	{
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start[0], Start[1], Start[2], End[0], End[1], End[2], launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
	}
}
#pragma endregion

#pragma region Attach
void toggleAttach(int Player)
{
	int att, player, bone;
	if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(Player), PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()))))
	{
		if (!PlayerAttached)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				att = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			}
			else
			{
				att = PLAYER::PLAYER_PED_ID();
			}

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(Player), 0))
			{
				player = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(Player), 0);
			}
			else
			{
				player = PLAYER::GET_PLAYER_PED(Player);
			}

			if (AttachtoVehicleTop)
			{
				bone = ENTITY::_GET_ENTITY_BONE_INDEX(player, "roof");
			}
			else
			{
				bone = PED::GET_PED_BONE_INDEX(player, BONSINTS[GetPedBoneIndex]);
			}
			ENTITY::ATTACH_ENTITY_TO_ENTITY(att, player, bone, One1.x, One1.y, One1.z, Two1.x, Two1.y, Two1.z, 0, 1, 0, 0, 2, 1);
			ENTITY::SET_ENTITY_COLLISION(att, 0, 0);
			PlayerAttached = true;
		}
		else
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				att = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			}
			else
			{
				att = PLAYER::PLAYER_PED_ID();
			}

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(Player), 0))
			{
				player = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(Player), 0);
			}
			else
			{
				player = PLAYER::GET_PLAYER_PED(Player);
			}

			ENTITY::DETACH_ENTITY(att, player, 1);
			ENTITY::SET_ENTITY_COLLISION(att, 1, 1);
			PlayerAttached = false;
		}
	}
}
#pragma endregion

#pragma region Outfit
void Modelo(char* family, int model, int texture, int palette)
{
	int fam;
	if (strstr(family, "HATS") != NULL || strstr(family, "GLASSES") != NULL || strstr(family, "EARS") != NULL)
	{
		if (strstr(family, "HATS") != NULL)
			fam = 0;
		else if (strstr(family, "GLASSES") != NULL)
			fam = 1;
		else if (strstr(family, "EARS") != NULL)
			fam = 2;
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model, texture, palette);
	}
	else
	{
		if (strstr(family, "FACE") != NULL)
			fam = 0;
		else if (strstr(family, "MASK") != NULL)
			fam = 1;
		else if (strstr(family, "HAIR") != NULL)
			fam = 2;
		else if (strstr(family, "TORSO") != NULL)
			fam = 3;
		else if (strstr(family, "LEGS") != NULL)
			fam = 4;
		else if (strstr(family, "HANDS") != NULL)
			fam = 5;
		else if (strstr(family, "SHOES") != NULL)
			fam = 6;
		else if (strstr(family, "SPECIAL1") != NULL)
			fam = 7;
		else if (strstr(family, "SPECIAL2") != NULL)
			fam = 8;
		else if (strstr(family, "SPECIAL3") != NULL)
			fam = 9;
		else if (strstr(family, "TEXTURE") != NULL)
			fam = 10;
		else if (strstr(family, "TORSO2") != NULL)
			fam = 11;
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, palette);
	}
}

void ReturnModelo(char* family, int model, int texture, int palette)
{
	int fam;
	if (strstr(family, "HATS") != NULL || strstr(family, "GLASSES") != NULL || strstr(family, "EARS") != NULL)
	{
		if (strstr(family, "HATS") != NULL)
			fam = 0;
		else if (strstr(family, "GLASSES") != NULL)
			fam = 1;
		else if (strstr(family, "EARS") != NULL)
			fam = 2;
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model, texture, palette);
	}
	else
	{
		if (strstr(family, "FACE") != NULL)
			fam = 0;
		else if (strstr(family, "MASK") != NULL)
			fam = 1;
		else if (strstr(family, "HAIR") != NULL)
			fam = 2;
		else if (strstr(family, "TORSO") != NULL)
			fam = 3;
		else if (strstr(family, "LEGS") != NULL)
			fam = 4;
		else if (strstr(family, "HANDS") != NULL)
			fam = 5;
		else if (strstr(family, "SHOES") != NULL)
			fam = 6;
		else if (strstr(family, "SPECIAL1") != NULL)
			fam = 7;
		else if (strstr(family, "SPECIAL2") != NULL)
			fam = 8;
		else if (strstr(family, "SPECIAL3") != NULL)
			fam = 9;
		else if (strstr(family, "TEXTURE") != NULL)
			fam = 10;
		else if (strstr(family, "TORSO2") != NULL)
			fam = 11;
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, palette);
	}
}

void DriftNotMod()
{
	if (!drift)
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 0);
	}
	else
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 1);
	}
}

void CopyingOutfit()
{
	Modelo("HATS", PED::GET_PED_PROP_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 0),
		PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 0), 0);

	Modelo("GALLSSES", PED::GET_PED_PROP_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 1),
		PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), 0);

	Modelo("EARS", PED::GET_PED_PROP_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 2),
		PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), 2), 0);

	Modelo("FACE", PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 0),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 0),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 0));

	Modelo("MASK", PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 1),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 1),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 1));

	Modelo("HAIR",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 2),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 2),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 2));

	Modelo("TORSO",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 3),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 3),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 3));

	Modelo("LEGS",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 4),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 4),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 4));

	Modelo("HANDS",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 5),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 5),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 5));

	Modelo("SHOES",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 6),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 6),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 6));

	Modelo("SPECIAL1",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 7),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 7),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 7));

	Modelo("SPECIAL2",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 8),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 8),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 8));

	Modelo("SPECIAL3",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 9),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 9),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 9));

	Modelo("TEXTURE",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 10),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 10),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 10));

	Modelo("TORSO2",
		PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 11),
		PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 11),
		PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED(selectedPlayer), 11));

}
#pragma endregion

#pragma region Funmenu

bool PartcleFX_Bone(char *FXType, char *FXName, float X, float Y, float Z, float xRot, float yRot, float zRot, int index, float scale)
{
	STREAMING::_REQUEST_DLC_PTFX_ASSET(FXType);
	GRAPHICS::_0x9C720B61(FXType);
	if (STREAMING::_HAS_DLC_PTFX_LOADED(FXType))
	{
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(FXName, PLAYER::PLAYER_PED_ID(), X, Y, Z, xRot, yRot, zRot, index, scale, 0, 0, 0);
		return true;
	}
	return false;
}

void DeleteAllDragonFire()
{
	if (DragonFireTrue)
	{
		DragonFireSpawn = true;
	}
	else
	{
		BodyFlag = false;
		RedLampFlag = false;
		StickFlag = false;
		Stick2Flag = false;
		Stick3Flag = false;
		Stick4Flag = false;
		PropellerFlag = false;
		Propeller2Flag = false;
		Propeller3Flag = false;
		Propeller4Flag = false;
		RequestNetworkControl(Core);
		RequestNetworkControl(Body);
		RequestNetworkControl(RedLamp);
		RequestNetworkControl(Stick);
		RequestNetworkControl(Stick2);
		RequestNetworkControl(Stick3);
		RequestNetworkControl(Stick4);
		RequestNetworkControl(Propeller);
		RequestNetworkControl(Propeller2);
		RequestNetworkControl(Propeller3);
		RequestNetworkControl(Propeller4);
		RequestNetworkControl(minigun01);
		ENTITY::DELETE_ENTITY(&Body);
		ENTITY::DELETE_ENTITY(&RedLamp);
		ENTITY::DELETE_ENTITY(&Stick);
		ENTITY::DELETE_ENTITY(&Stick2);
		ENTITY::DELETE_ENTITY(&Stick3);
		ENTITY::DELETE_ENTITY(&Stick4);
		ENTITY::DELETE_ENTITY(&Propeller);
		ENTITY::DELETE_ENTITY(&Propeller2);
		ENTITY::DELETE_ENTITY(&Propeller3);
		ENTITY::DELETE_ENTITY(&Propeller4);
		ENTITY::DELETE_ENTITY(&minigun01);
		DragonFireEnable = false;
		DragonFireMovement = false;
		DragonFireSpawn = false;
		DragonFireFirstPerson = false;
	}
}

bool DeleteIMissile()
{
	if (ENTITY::DOES_ENTITY_EXIST(PreMissile2))
	{
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PreMissile2, true, true);
		DeleteEntity(PreMissile2);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(FakeMissileOb, true, true);
		DeleteEntity(FakeMissileOb);
	}
	else return true;
	return false;
}





void DeleteCam()
{
	CAM::SET_CAM_ACTIVE1(PreCamera, false);
	CAM::DESTROY_CAM1(PreCamera, false);
	CAM::RENDER_SCRIPT_CAMS1(false, false, 3000, true, false);
	PreCamera = 0;
}

void DeleteCam2()
{
	CAM::SET_CAM_ACTIVE1(PreCamera2, false);
	CAM::DESTROY_CAM1(PreCamera2, false);
	CAM::RENDER_SCRIPT_CAMS1(false, false, 3000, true, false);
	PreCamera2 = 0;
}

void VehicleWeaponsFunctionN2(int Hash)
{
	int launchDistance = 250;
	float launchSpeed = 500.0f;
	Vector3 spawnPosition = get_coords_from_entity_cam(5.0);
	Vector3 endPosition = get_coords_from_entity_cam(100.0);

	float Start[] = { spawnPosition.x, spawnPosition.y, spawnPosition.z };
	float End[] = { endPosition.x, endPosition.y, endPosition.z };

	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start[0], Start[1], Start[2], End[0], End[1], End[2], launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
}

void VehicleWeaponsFunctionN3(Entity entiy, int Hash)
{
	int launchDistance = 250;
	float launchSpeed = 500.0f;
	Vector3 spawnPosition = get_coords_from_entity(entiy, 5.0);
	Vector3 endPosition = get_coords_from_entity(entiy, 100.0);

	float Start[] = { spawnPosition.x, spawnPosition.y, spawnPosition.z };
	float End[] = { endPosition.x, endPosition.y, endPosition.z };

	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start[0], Start[1], Start[2], End[0], End[1], End[2], launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
}

void VehicleWeaponsFunctionN4(int Hash)
{
	Vector3 rot = GET_GAMEPLAY_CAM_ROT_orig(2);
	int launchDistance = 250;
	float launchSpeed = 500.0f;
	Vector3 spawnPosition = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), SKEL_R_Hand, 0, 0, 0);/*ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.1, 4, 0.5)*/;
	Vector3 endPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.1, 100, 0.5);

	float Start[] = { spawnPosition.x, spawnPosition.y, spawnPosition.z };
	float End[] = { endPosition.x, endPosition.y, endPosition.z };
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start[0], Start[1], Start[2], End[0], End[1], End[2], launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
	InfamousSwitch = WaitingButton;
}

bool SpawnMissile()
{
	Vector3 vec = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
	vec.y += 5.0f;
	vec.z += 5.0f;
	Vector3 a; a.x = 0, a.y = 0, a.z = 0;
	Vector3 b; b.x = 0, b.y = 2, b.z = 0;
	Vector3 Force = { 0, 5.0f, 0.0f }, Position = { 0, 0, 0 };
	PreMissile2 = Create_Map_int("prop_dummy_plane");
	FakeMissileOb = Create_Map_int("prop_ld_test_01");
	if (ENTITY::DOES_ENTITY_EXIST(PreMissile2) && ENTITY::DOES_ENTITY_EXIST(FakeMissileOb))
	{
		Vector3 One, Two;
		One.x = 0.0f;
		One.y = 2.0f;
		One.z = 0.0f;
		Two.x = 0.0f;
		Two.y = 0.0f;
		Two.z = 180.0f;
		ENTITY::SET_ENTITY_HEADING(FakeMissileOb, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
		Vector3 untiiii = GET_GAMEPLAY_CAM_ROT_orig(2);
		ENTITY::SET_ENTITY_ROTATION(FakeMissileOb, untiiii.x, untiiii.y, untiiii.z, 2, 1);
		ApplyForce(FakeMissileOb, Force.x, Force.y, Force.z, Position.x, Position.y, Position.z);
		ATTACH_ENTITY_TO_ENTITY(PreMissile2, FakeMissileOb, 0, One.x, One.y, One.z, Two.x, Two.y, Two.z);
		return true;
	}
	else
	{
		return false;
	}
}

void ChangeAmmo()
{
	int Hash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LASER");
	int Hash2 = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER");
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, -1, true, true);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash2, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash2, -1, true, true);
	int Offset = GET_WEAPONS(Hash);
	int Offset2 = GET_WEAPONS(Hash2);
	int AmmoOffset = PS3::ReadInt32(Offset + AmmoInfo);
	int AmmoOffset2 = PS3::ReadInt32(Offset2 + AmmoInfo);
	PS3::WriteUInt32(AmmoOffset + Explosion_Default, EXPLOSION_GRENADE);
	PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
	PS3::WriteUInt32(AmmoOffset2 + Explosion_Default, EXPLOSION_GRENADE);
	PS3::WriteUInt32(AmmoOffset2 + ProjectileFlags, 4);
}
RGBA Red = { 255,0,0,255 };
void drawLine(Vector3 p1, Vector3 p2, RGBA RGBAs = Red)
{
	GRAPHICS::DRAW_LINE(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, RGBAs.R, RGBAs.G, RGBAs.B, RGBAs.A);
}

bool PartcleFX_Entity(char *FXType, char *FXName, int Entity, float X, float Y, float Z, float xRot, float yRot, float zRot, float scale)
{
	STREAMING::_REQUEST_DLC_PTFX_ASSET(FXType);
	GRAPHICS::_0x9C720B61(FXType);
	if (STREAMING::_HAS_DLC_PTFX_LOADED(FXType))
	{
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(FXName, Entity, X, Y, Z, xRot, yRot, zRot, scale, 0, 0, 0);
		//StartParticleFXEntity(FXName, Entity, X, Y, Z, xRot, yRot, zRot, scale);
		return true;
	}
	return false;
}

void WaterEditer()
{
	NotifyDown("Thread Start", 1000);
	if (WaterisntHere)
	{
		if (!WaterEditFlagTrue && !WaterEditFlagFalse)
		{
			WaterCount = 0;
			WaterEditMaxValue = 0;
			WaterEditFlagTrue = true;
		}
		else
		{
			NotifyDown("処理を実行出来ません", 1000);
		}
	}
	else
	{
		if (!WaterEditFlagFalse && !WaterEditFlagTrue)
		{
			WaterCount = 0;
			WaterEditMaxValue = 0;
			WaterEditFlagFalse = true;
		}
		else
		{
			NotifyDown("処理を実行出来ません", 1000);
		}
	}
}

void SneakMode(bool toggle)
{
	if (!toggle)
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}
}
#pragma endregion

#pragma region Protections
char ON[] = { 78,128,0,32 }; //4E800020 
char OFF[] = { 124,8,2,166 };//7C0802A6
char ONN[] = { 0x41,0x82,0x00,0x94 }; //41820094
char OF[] = { 0x40,0x82,0x00,0x68 };
char bytes130[209]; char bytes131[209]; char bytes132[209]; char bytes133[209]; char bytes134[209]; char bytes135[209]; char bytes136[209]; char bytes137[209];
uint FlyingCar[] = { 1076750960, 1076574992, 1076576240, 1076709776, 1076571872, 1076569376, 1076711024, 1076692304, 1076578736, 1076579360, 1076580608, 1076577488, 1076578112, 1076711648, 1076712272, 1076581232, 1076582480, 1076584976, 1076579984, 1076583104, 1076583728, 1076584352, 1076593088, 1076568752, 1076708528, 1076570624, 1076588720, 1076589344, 1076586848, 1076590592, 1076591216, 1076592464, 1076593712, 1076571248, 1076718512, 1076719136, 1076599328, 1076599952, 1076601200, 1076719760, 1076602448, 1076574368, 1076603072, 1076604320, 1076707904, 1076637392, 1076725376, 1076604944, 1076713520, 1076732864, 1076609312, 1076742224, 1076612432, 1076714144, 1076609936, 1076611184, 1076607440, 1076608064, 1076726000, 1076616800, 1076613680, 1076615552, 1076616176, 1076617424, 1076618048, 1076618672, 1076619296, 1076619920, 1076621168, 1076707280, 1076621792, 1076623040, 1076573744, 1076724128, 1076624288, 1076623664, 1076624912, 1076626160, 1076598704, 1076625536, 1076605568, 1076626784, 1076628032, 1076627408, 1076717264, 1076608688, 1076628656, 1076629280, 1076629904, 1076630528, 1076631152, 1076632400, 1076727872, 1076734112, 1076631776, 1076730368, 1076634272, 1076729120, 1076727248, 1076634896, 1076732240, 1076722880, 1076635520, 1076638016, 1076638640, 1076639264, 1076639888, 1076640512, 1076641136, 1076723504, 1076567504, 1076568128, 1076642384, 1076642384, 1076643632, 1076644256, 1076644880, 1076714768, 1076645504, 1076646128, 1076646752, 1076647376, 1076648000, 1076598080, 1076650496, 1076649872, 1076709152, 1076598080, 1076722256, 1076652992, 1076648624, 1076654240, 1076654864, 1076734736, 1076655488, 1076656112, 1076659856, 1076658608, 1076661104, 1076662352, 1076661728, 1076665472, 1076666096, 1076666720, 1076667968, 1076611808, 1076712896, 1076663600, 1076664224, 1076668592, 1076669216, 1076703536, 1076704160, 1076670464, 1076704784, 1076672960, 1076735984, 1076673584, 1076674208, 1076674832, 1076676704, 1076728496, 1076677328, 1076677952, 1076721632, 1076678576, 1076679200, 1076731616, 1076679824, 1076680448, 1076681696, 1076682944, 1076701664, 1076726624, 1076683568, 1076752832, 1076684192, 1076684816, 1076685440, 1076686064, 1076686688, 1076687312, 1076688560, 1076692928, 1076693552, 1076729744, 1076694176, 1076694800, 1076695424, 1076696672, 1076697296, 1076689808, 1076690432, 1076744096, 1076744096, 1076689184, 1076705408, 1076706032, 1076706656, 1076735360, 1076752208, 1076715392, 1076750336, 1076716016, 1076751584, 1076702288, 1076675456, 1076676080, 1076702912 };
char bytes10[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04 };
char bytes[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04 };
char bytes1ff[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 };
char FreezeHelibyte[] = { 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04 };

void AdminKickP(bool flag)
{
	PS3::WriteInt32(ADMIN_KICK_PROTECTION1, flag ? 0x60000000 : ADMIN_KICK_PROTECTION1);
	PS3::WriteInt32(ADMIN_KICK_PROTECTION2, flag ? 0x60000000 : ADMIN_KICK_PROTECTION2);
}

void PTFXs(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12D4FF8, ON, 4);
		PS3::WriteBytes(0x12C6950, ON, 4);//Lazer
		PS3::WriteBytes(0x12C49A4, ON, 4);//Explosion
		PS3::WriteBytes(0x12C5598, ON, 4);//Fire
		NotifyDown("エフェクト: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12D4FF8, OFF, 4);
		PS3::WriteBytes(0x12C6950, OFF, 4);//Lazer
		PS3::WriteBytes(0x12C49A4, OFF, 4);
		PS3::WriteBytes(0x12C5598, OFF, 4);
		NotifyDown("エフェクト: ~r~オフ");
	}
}

bool hostkick;
void HostKick(bool flag)
{
	if (flag)
	{
		
		PS3::WriteBytes(0x1358AFC, ON, 4);
	}
	else
	{
		PS3::WriteBytes(0x1358AFC, OFF, 4);
	}
}
bool wetherChangepro;
void WeatherPro(bool On)
{
	if (On)
	{
		
			PS3::WriteBytes(0x12C2D8C, ON, 4);

	}
	else
	{
		PS3::WriteBytes(0x12C2D8C, OFF, 4);
	}
}

bool ALLEVENT;
//void AllEvent(bool flag)
//{
//	if (flag)
//	{
//		PS3::WriteBytes(0x12C783C, ON, 4); //不明
//		PS3::WriteBytes(0xA046B8, ON, 4);  //不明
//		PS3::WriteBytes(0x12D2944, ON, 4); //不明
//		PS3::WriteBytes(0x12D6918, ON, 4);  //不明
//		PS3::WriteBytes(0x12C7CD4, ON, 4); //不明
//		PS3::WriteBytes(0x12CADC8, ON, 4); //不明
//		PS3::WriteBytes(0x12C9F5C, ON, 4); //不明
//		PS3::WriteBytes(0x12C88B0, ON, 4); //不明
//		PS3::WriteBytes(0x12C5598, ON, 4); //爆発の発生Event これを消せば爆発が発生しない。
//		PS3::WriteBytes(0x12C49A4, ON, 4); //炎の発生Event これを消せば炎が発生しない。
//		PS3::WriteBytes(0x12C28E8, ON, 4); //恐らくゲームの時間が進むイベント。
//		PS3::WriteBytes(0x12C2D8C, ON, 4); //恐らくゲームの天候が変わるイベント。
//		PS3::WriteBytes(0x12BDF2C, ON, 4); //不明
//		PS3::WriteBytes(0x12CBD94, ON, 4); //不明
//		PS3::WriteBytes(0x12CC1EC, ON, 4); //不明
//		PS3::WriteBytes(0x12D2064, ON, 4); //不明
//		PS3::WriteBytes(0x12C374C, ON, 4); //武器がチート等で渡される時のイベント。これを消せば渡されない。
//		PS3::WriteBytes(0x12CA70C, ON, 4); //不明
//		PS3::WriteBytes(0x12D5F18, ON, 4); //不明
//		PS3::WriteBytes(0x12D1D88, ON, 4); //投票で追い出されるイベント。これを消せば追い出されない。
//		PS3::WriteBytes(0x12C9948, ON, 4); //不明
//		PS3::WriteBytes(0x12D04E4, ON, 4); //不明
//		PS3::WriteBytes(0x12D4B98, ON, 4); //不明
//		PS3::WriteBytes(0x12D48D0, ON, 4); //不明
//		PS3::WriteBytes(0x12CC8B8, ON, 4); //強制クリアタスクイベント。これを消せばクリアタスクを無効化できる。
//		PS3::WriteBytes(0x12D2460, ON, 4); //不明
//		PS3::WriteBytes(0x12CD4C8, ON, 4); //不明
//		PS3::WriteBytes(0x12CDAB4, ON, 4); //不明
//		PS3::WriteBytes(0x12D12DC, ON, 4); //不明
//		PS3::WriteBytes(0x12D585C, ON, 4); //不明
//		PS3::WriteBytes(0x12CFD48, ON, 4); //不明
//		PS3::WriteBytes(0x12D4FF8, ON, 4); //ParticleFXを表示するイベント。(ネットワーク内で)同じく消せば表示されない。
//		PS3::WriteBytes(0x12CB0F8, ON, 4); //強制テレポートや強制アニメーションに関係する物。これと同じ説明の物を全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0x12D3500, ON, 4); //不明
//		PS3::WriteBytes(0x12CCEA4, ON, 4); //相手のクラクションを鳴らすのを防ぐ。自分目線のみ。
//		PS3::WriteBytes(0x12CCC00, ON, 4); //不明
//		PS3::WriteBytes(0x12CCD70, ON, 4); //不明
//		PS3::WriteBytes(0x12CB4BC, ON, 4);
//		PS3::WriteBytes(0x12D01A8, ON, 4); //不明
//		PS3::WriteBytes(0x12CB66C, ON, 4); //強制テレポートや強制アニメーションに関係する全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0x12D10AC, ON, 4); //不明
//		PS3::WriteBytes(0x12D0D6C, ON, 4); //不明
//		PS3::WriteBytes(0x12CB890, ON, 4); //強制テレポートや強制アニメーションに関係する物。これと同じ説明のを全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0xA03A98, ON, 4);  //不明
//		PS3::WriteBytes(0xA04090, ON, 4);  //不明
//		PS3::WriteBytes(0x12CDF04, ON, 4); //不明
//		PS3::WriteBytes(0x12D6434, ON, 4); //不明
//		PS3::WriteBytes(0x12D41DC, ON, 4); //不明
//		PS3::WriteBytes(0x12C870C, ON, 4); //不明
//		PS3::WriteBytes(0x12C8330, ON, 4);//不明
//		PS3::WriteBytes(0x12C7F48, ON, 4); //不明
//		PS3::WriteBytes(0x12C918C, ON, 4); //不明
//		PS3::WriteBytes(0x12C9614, ON, 4); //不明
//		PS3::WriteBytes(0x12C3BD4, ON, 4); //武器を消すイベント。これを消せばチート等で武器を消されるのが防げる。
//		PS3::WriteBytes(0x12D6DB0, ON, 4); //不明
//		PS3::WriteBytes(0x12D5C14, ON, 4); //不明
//		PS3::WriteBytes(0x12C3A2C, ON, 4); //武器を消すイベント。これを消せばチート等で武器を消されるのが防げる。
//		PS3::WriteBytes(0x12D72AC, ON, 4); //不明
//		PS3::WriteBytes(0x12BD2CC, ON, 4); //車をコントロールされるイベント。これを消せばSling Shot等の車操作系を防げる。
//		PS3::WriteBytes(0x12D19B0, ON, 4); //不明
//		PS3::WriteBytes(0x12D0934, ON, 4); //不明
//		PS3::WriteBytes(0x12C2274, ON, 4); //不明
//		PS3::WriteBytes(0x12D1740, ON, 4); //不明
//		PS3::WriteBytes(0x12C1A54, ON, 4); //不明
//		PS3::WriteBytes(0x12C310C, ON, 4); //不明
//		PS3::WriteBytes(0x12C8CC0, ON, 4); //不明
//		PS3::WriteBytes(0x12BCE60, ON, 4); //不明
//		PS3::WriteBytes(0x12CE66C, ON, 4); //不明
//		PS3::WriteBytes(0x12CA3E4, ON, 4); //不明
//		PS3::WriteBytes(0x12C6950, ON, 4); //不明
//		PS3::WriteBytes(0x12D45C0, ON, 4); //不明
//		PS3::WriteBytes(0x12C409C, ON, 4); //車を改造されるチート等のイベント。恐らくこれを消せば勝手にクロームなどに改造されたりしない。
//		PS3::WriteBytes(0x12CD1A4, ON, 4); //不明
//		PS3::WriteBytes(0x12C0088, ON, 4); //不明
//		NotifyDown("All: ~g~オン");
//	}
//	else
//	{
//		PS3::WriteBytes(0x12C783C, OFF, 4); //不明
//		PS3::WriteBytes(0xA046B8, OFF, 4);  //不明
//		PS3::WriteBytes(0x12D2944, OFF, 4); //不明
//		PS3::WriteBytes(0x12D6918, OFF, 4);  //不明
//		PS3::WriteBytes(0x12C7CD4, OFF, 4); //不明
//		PS3::WriteBytes(0x12CADC8, OFF, 4); //不明
//		PS3::WriteBytes(0x12C9F5C, OFF, 4); //不明
//		PS3::WriteBytes(0x12C88B0, OFF, 4); //不明
//		PS3::WriteBytes(0x12C5598, OFF, 4); //爆発の発生Event これを消せば爆発が発生しない。
//		PS3::WriteBytes(0x12C49A4, OFF, 4); //炎の発生Event これを消せば炎が発生しない。
//		PS3::WriteBytes(0x12C28E8, OFF, 4); //恐らくゲームの時間が進むイベント。
//		PS3::WriteBytes(0x12C2D8C, OFF, 4); //恐らくゲームの天候が変わるイベント。
//		PS3::WriteBytes(0x12BDF2C, OFF, 4); //不明
//		PS3::WriteBytes(0x12CBD94, OFF, 4); //不明
//		PS3::WriteBytes(0x12CC1EC, OFF, 4); //不明
//		PS3::WriteBytes(0x12D2064, OFF, 4); //不明
//		PS3::WriteBytes(0x12C374C, OFF, 4); //武器がチート等で渡される時のイベント。これを消せば渡されない。
//		PS3::WriteBytes(0x12CA70C, OFF, 4); //不明
//		PS3::WriteBytes(0x12D5F18, OFF, 4); //不明
//		PS3::WriteBytes(0x12D1D88, OFF, 4); //投票で追い出されるイベント。これを消せば追い出されない。
//		PS3::WriteBytes(0x12C9948, OFF, 4); //不明
//		PS3::WriteBytes(0x12D04E4, OFF, 4); //不明
//		PS3::WriteBytes(0x12D4B98, OFF, 4); //不明
//		PS3::WriteBytes(0x12D48D0, OFF, 4); //不明
//		PS3::WriteBytes(0x12CC8B8, OFF, 4); //強制クリアタスクイベント。これを消せばクリアタスクを無効化できる。
//		PS3::WriteBytes(0x12D2460, OFF, 4); //不明
//		PS3::WriteBytes(0x12CD4C8, OFF, 4); //不明
//		PS3::WriteBytes(0x12CDAB4, OFF, 4); //不明
//		PS3::WriteBytes(0x12D12DC, OFF, 4); //不明
//		PS3::WriteBytes(0x12D585C, OFF, 4); //不明
//		PS3::WriteBytes(0x12CFD48, OFF, 4); //不明
//		PS3::WriteBytes(0x12D4FF8, OFF, 4); //ParticleFXを表示するイベント。(ネットワーク内で)同じく消せば表示されない。
//		PS3::WriteBytes(0x12CB0F8, OFF, 4); //強制テレポートや強制アニメーションに関係する物。これと同じ説明の物を全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0x12D3500, OFF, 4); //不明
//		PS3::WriteBytes(0x12CCEA4, OFF, 4); //相手のクラクションを鳴らすのを防ぐ。自分目線のみ。
//		PS3::WriteBytes(0x12CCC00, OFF, 4); //不明
//		PS3::WriteBytes(0x12CCD70, OFF, 4); //不明
//		PS3::WriteBytes(0x12CB4BC, OFF, 4);
//		PS3::WriteBytes(0x12D01A8, OFF, 4); //不明
//		PS3::WriteBytes(0x12CB66C, OFF, 4); //強制テレポートや強制アニメーションに関係する全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0x12D10AC, OFF, 4); //不明
//		PS3::WriteBytes(0x12D0D6C, OFF, 4); //不明
//		PS3::WriteBytes(0x12CB890, OFF, 4); //強制テレポートや強制アニメーションに関係する物。これと同じ説明のを全て消せばテレポートやアニメーションが適用されない。
//		PS3::WriteBytes(0xA03A98, OFF, 4);  //不明
//		PS3::WriteBytes(0xA04090, OFF, 4);  //不明
//		PS3::WriteBytes(0x12CDF04, OFF, 4); //不明
//		PS3::WriteBytes(0x12D6434, OFF, 4); //不明
//		PS3::WriteBytes(0x12D41DC, OFF, 4); //不明
//		PS3::WriteBytes(0x12C870C, OFF, 4); //不明
//		PS3::WriteBytes(0x12C8330, OFF, 4);//不明
//		PS3::WriteBytes(0x12C7F48, OFF, 4); //不明
//		PS3::WriteBytes(0x12C918C, OFF, 4); //不明
//		PS3::WriteBytes(0x12C9614, OFF, 4); //不明
//		PS3::WriteBytes(0x12C3BD4, OFF, 4); //武器を消すイベント。これを消せばチート等で武器を消されるのが防げる。
//		PS3::WriteBytes(0x12D6DB0, OFF, 4); //不明
//		PS3::WriteBytes(0x12D5C14, OFF, 4); //不明
//		PS3::WriteBytes(0x12C3A2C, OFF, 4); //武器を消すイベント。これを消せばチート等で武器を消されるのが防げる。
//		PS3::WriteBytes(0x12D72AC, OFF, 4); //不明
//		PS3::WriteBytes(0x12BD2CC, OFF, 4); //車をコントロールされるイベント。これを消せばSling Shot等の車操作系を防げる。
//		PS3::WriteBytes(0x12D19B0, OFF, 4); //不明
//		PS3::WriteBytes(0x12D0934, OFF, 4); //不明
//		PS3::WriteBytes(0x12C2274, OFF, 4); //不明
//		PS3::WriteBytes(0x12D1740, OFF, 4); //不明
//		PS3::WriteBytes(0x12C1A54, OFF, 4); //不明
//		PS3::WriteBytes(0x12C310C, OFF, 4); //不明
//		PS3::WriteBytes(0x12C8CC0, OFF, 4); //不明
//		PS3::WriteBytes(0x12BCE60, OFF, 4); //不明
//		PS3::WriteBytes(0x12CE66C, OFF, 4); //不明
//		PS3::WriteBytes(0x12CA3E4, OFF, 4); //不明
//		PS3::WriteBytes(0x12C6950, OFF, 4); //不明
//		PS3::WriteBytes(0x12D45C0, OFF, 4); //不明
//		PS3::WriteBytes(0x12C409C, OFF, 4); //車を改造されるチート等のイベント。恐らくこれを消せば勝手にクロームなどに改造されたりしない。
//		PS3::WriteBytes(0x12CD1A4, OFF, 4); //不明
//		PS3::WriteBytes(0x12C0088, OFF, 4); //不明
//		NotifyDown("エフェクト: ~r~オフ");
//	}
//}

void Tasks(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12CB0F8, ON, 4);
		PS3::WriteBytes(0x12CB4BC, ON, 4);
		PS3::WriteBytes(0x12CB66C, ON, 4);
		PS3::WriteBytes(0x12CB890, ON, 4);
		NotifyDown("アニメ / テレポ: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12CB0F8, OFF, 4);
		PS3::WriteBytes(0x12CB4BC, OFF, 4);
		PS3::WriteBytes(0x12CB66C, OFF, 4);
		PS3::WriteBytes(0x12CB890, OFF, 4);
		NotifyDown("アニメ / テレポ: ~r~Deleted");
	}
}



void CTask(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12CC8B8, ON, 4);
		NotifyDown("クリアタスク: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12CC8B8, OFF, 4);
		NotifyDown("クリアタスク: ~r~オフ");
	}
}

void Vehip(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12BD2CC, ON, 4);
		NotifyDown("車両操作: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12BD2CC, OFF, 4);
		NotifyDown("車両操作: ~r~オフ");
	}
}

void RemvP(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12C3BD4, ON, 4);
		PS3::WriteBytes(0x12C3A2C, ON, 4);
		NotifyDown("武器没収: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12C3BD4, OFF, 4);
		PS3::WriteBytes(0x12C3A2C, OFF, 4);
		NotifyDown("武器没収: ~r~オフ");
	}
}



bool Kickvote;

void KickVote(bool flag)
{
	if (flag)
	{
		PS3::WriteBytes(0x12D1D88, ON, 4);
		PS3::Write_Global(1582015 + (306 * PLAYER::PLAYER_ID()), 5461328);
		NotifyDown("キック投票: ~g~オン");
	}
	else
	{
		PS3::WriteBytes(0x12D1D88, OFF, 4);
		NotifyDown("クック投票: ~r~オフ");
	}
}

void FreezeCarImport()
{
	if (PS3::ReadInt32(0x13BF850) != 0x4E800020)
	{
		PS3::WriteBytes(0x13BF850, ON, 4);
	}
}

void FreezeCarDefault()
{
	if (PS3::ReadInt32(0x13BF850) != 0x7C0802A6)
	{
		PS3::WriteBytes(0x13BF850, OFF, 4);
	}
}

void Frezp(bool flag)
{
	if (flag)
	{
		FreezeCarImport();
	}
	else
	{
		FreezeCarDefault();
	}
}
//
//void AllPro(bool On)
//{
//	if (PS3::ReadInt32(0x223F0C0) == 0x01000000 && (PS3::ReadInt32(0x223F0C4) == 0x01000000) && On)
//	{
//		AutoProtection = true;
//	}
//	else
//	{
//		AutoProtection = false;
//		PTFX = false;
//		TaskP = false;
//		hostkick = false;
//		Kickvote = false;
//		ChangeStatsProtection = false;
//		ScriptDetect = false;
//		RPprotection = false;
//		Blockallentities1 = false;
//		TralerBlock1 = false;
//		ObjectBlock1 = false;
//		HelicoptersBlock1 = false;
//		PlanesBlock1 = false;
//		ParadiseProtection(false);
//		ObjectBlock(ObjectBlock1);
//		HelicoptersBlock(HelicoptersBlock1);
//		TralerBlock(TralerBlock1);
//		PlanesBlock(PlanesBlock1);
//		Blockallentities(Blockallentities1);
//		KickVote(Kickvote);
//		RPprotection2(RPprotection);
//		HostKick(hostkick);
//		Tasks(TaskP);
//		PTFXs(PTFX);
//	}
//}
//


bool ghostbool;
char Enable[] = { 0x60, 0x00, 0x00, 0x00 };

void GhostOn()
{
	if (PS3::ReadInt32(0x12F324C) != 0x60000000 && PS3::ReadInt32(0x12F32F0) != 0x60000000)
	{
		PS3::WriteBytes(0x12F324C, Enable, 4);
		PS3::WriteBytes(0x12F32F0, Enable, 4);
	}
}
char d2[] = { 0x4B, 0x70, 0xEB, 0x19 }; //4B 70 EB 19
char d3[] = { 0x63, 0xA3, 0x00, 0x00 };
void GhostOff()
{
	if (PS3::ReadInt32(0x12F324C) != 0x4B70EB19 && PS3::ReadInt32(0x12F32F0) != 0x4BE24689)
	{
		PS3::WriteBytes(0x12F324C, d2, 4);
		PS3::WriteBytes(0x12F32F0, d3, 4);
	}
}
void Ghost(bool flag)
{
	if (flag)
	{
		GhostOn();
	}
	else
	{
		GhostOff();
	}
}


void Frezpaaa(bool toggle)
{
	if (toggle)
	{
		FreezeCarImport();
		NotifyDown("飛行機完全削除 : ~g~オン", 1000);
	}
	else
	{
		FreezeCarDefault();
		NotifyDown("飛行機完全削除 : ~r~オフ", 1000);
	}
}

bool admink;

char NOP_ENABLE[] = { 0x60, 0x00, 0x00, 0x00 };
char adminKickOriginal[] = { 0x90, 0x7E, 0x00, 0x04 };



bool CarFreeze;


void Adminvoid()//AdminKick
{
	if (PS3::ReadInt32(0x01357D44) != 0x60000000 || PS3::ReadInt32(0x01370334) != 0x60000000)
	{
		PS3::WriteBytes(0x01357D44, NOP_ENABLE, 4);
		PS3::WriteBytes(0x01370334, NOP_ENABLE, 4);
	}
}
void AdminvoidDefault()//AdminKick
{
	if (PS3::ReadInt32(0x01357D44) != 0x907E0004 || PS3::ReadInt32(0x01370334) != 0x907E0004)
	{
		PS3::WriteBytes(0x01357D44, adminKickOriginal, 4);
		PS3::WriteBytes(0x01370334, adminKickOriginal, 4);
	}
}
void Adminvoid1(bool toggle)
{
	if (toggle)
	{
		Adminvoid();
	}
	else
	{
		AdminvoidDefault();
	}

}




bool HeliP;

void HeliImport()
{
	if (PS3::ReadInt32(0x13BBF78) != 0x4E800020)
	{
		PS3::WriteBytes(0x13BBF78, ON, 4);
	}
}

void HeliDefault()
{
	if (PS3::ReadInt32(0x13BBF78) != 0x7C0802A6)
	{
		PS3::WriteBytes(0x13BBF78, OFF, 4);
	}
}

void Helipaaa(bool toggle)
{
	if (toggle)
	{
		HeliImport();
		NotifyDown("ヘリ完全削除 : ~g~オン", 1000);
	}
	else
	{
		HeliDefault();
		NotifyDown("ヘリ完全削除 : ~r~オフ", 1000);
	}
}


bool AllP;


void AllImport()
{
	if (PS3::ReadInt32(0x13AE688) != 0x4E800020)
	{
		PS3::WriteBytes(0x13AE688, ON, 4);
	}
}

void AllDefault()
{
	if (PS3::ReadInt32(0x13AE688) != 0x7C0802A6)
	{
		PS3::WriteBytes(0x13AE688, OFF, 4);
	}
}

void Allpaaa(bool toggle)
{
	if (toggle)
	{
		AllImport();
		NotifyDown("全車両完全削除 : ~g~オン", 1000);
	}
	else
	{
		AllDefault();
		NotifyDown("全車両完全削除 : ~r~オフ", 1000);
	}
}



char* getPlayerName(int playerIndex) {
	return PLAYER::GET_PLAYER_NAME(playerIndex);
}
int returnPlayerPed(char* nameIndex) {
	for (int i = 0; i < 18; i++)
	{
		if (i != PLAYER::PLAYER_ID())
		{
			if (strstr(getPlayerName(i), nameIndex) != NULL)
			{
				return i;
			}
		}
	}
}

void dropkickplayer(int player)
{
	PS3::Write_Global(1588610 + (player + 1), 1);
}
void messeji(char *Message , int selectedPlayer)
{
	int NetHandleBuffer = 0x10070200; /*0x223C250*/
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
	NETWORK::NETWORK_SEND_TEXT_MESSAGE(Message, NetHandleBuffer);
}

bool PSIDsaveloop;
;

bool ProtectionON = false;
char scriptEventDialogText[100];
unsigned int scriptEventDetour(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9)
{

	int addressOfArgs = r3 + 10 * 0x4;
	char *senderName = (char*)(*(int*)(senderData + 0x78) + 0x10);
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x35)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~をキックしてます!!", senderName);
		NotifyDown(scriptEventDialogText);

		if (PSIDsaveloop)
		{
			PSIDsave(returnPlayerPed(senderName));
		}
		//kickPlayerNonHost(returnPlayerPed(senderName));
		dropkickplayer(returnPlayerPed(senderName));
		*(int*)addressOfArgs = 0;
	}

	if (FlagIndexes == NormalFlag)
	{
		if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x456)
		{
			NETWORK::NETWORK_SESSION_END(1, 1);
			*(int*)addressOfArgs = 0;
		}
		if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x789)
		{
			char *buffer1 = PS3::ReadBytes(0x402D6BC0, 144);
			PS3::WriteBytes(11111 + 0x10, buffer1, 144);
			buffer1 = NULL;
			char buffer[4] = { 71,195,79,128 };
			PS3::WriteBytes(0x4120CC24 + 0x04, buffer, 4);
			*buffer = NULL;		*(int*)addressOfArgs = 0;
		}
	}
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x34)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~を偽装キックしようとしてます!", senderName);
		NotifyDown(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x2e)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~を偽装キック[リセット]しようとしてます!", senderName);
		NotifyDown(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0xD8)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~のランク操作を行ってます! %i RP!", senderName, *(int*)(addressOfArgs + 0x8));
		NotifyDown(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x16C)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~をアパートに強制招待されてます!", senderName);
		NotifyDown(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x3)
	{
		if (*(int*)(addressOfArgs + 0x8) == 0x37 || *(int*)(addressOfArgs + 0x8) == 0x36 || *(int*)(addressOfArgs + 0x8) == 0x35)
		{
			snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s  ~w~が貴方を強制ゲームに招待してます!", senderName);
			NotifyDown(scriptEventDialogText);
			*(int*)addressOfArgs = 0;
		}
	}
	return _0x12C8CC0(r3, senderData, recieverData, r6, r7, r8, r9);
}

	//if (strstr(entityType, "PED") || strstr(entityType, "SCRIPT_PED"))
	//{
	//	if (*(int*)addressOfArgs == 0x1DC17987 || *(int*)addressOfArgs == 0x1E727BFF)
	//	{
	//		snprintf(EventDialogText, sizeof(EventDialogText), "~r~!警告!\n~y~%s~w~が~b~FreezePED~w~を出した。", NameOfSender);
	//		print2(EventDialogText, 2000);
	//		drawNotification2(EventDialogText);
	//		*(int*)addressOfArgs = 0;
	//	}
	//	if (*(int*)addressOfArgs == 0x1CFC0E72/*slod_human*/ || *(int*)addressOfArgs == 0x1E15B3EC/*slod_large_quadped*/ || *(int*)addressOfArgs == 0x1CB5C0C3/*slod_small_quadped*/) {
	//		snprintf(EventDialogText, sizeof(EventDialogText), "~r~!警告!\n~y~%s~w~が~b~FreezePED~w~を出した。", NameOfSender);
	//		print2(EventDialogText, 2000);
	//		drawNotification2(EventDialogText);

OPD_s weather_1t = { 0x12C2D8C,0x1C85330 };
unsigned int(*weather_1)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&weather_1t;
unsigned int WeatherEventProtection(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s  ~w~が天候変更しました!", senderName);
	NotifyDown(scriptEventDialogText);
	return weather_1(r3, r4, r5, r6, r7, r8);
}

OPD_s Anim_1t = { 0x12CB4BC,0x1C85330 };
unsigned int(*anim_1)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&Anim_1t;
unsigned int AnimproProtection(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s  ~w~がアニメーションをかけてきた!", senderName);
	NotifyDown(scriptEventDialogText);
	return anim_1(r3, r4, r5, r6, r7, r8);
}

OPD_s STATEVENTt = { 0x12D12DC,0x1C85330 };
unsigned int(*STATEVENT)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&STATEVENTt;
unsigned int NETWORKINCREMENTSTATEVENT(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s  ~w~が遠隔リカバリーを使用してきた!", senderName);
	NotifyDown(scriptEventDialogText);
	return STATEVENT(r3, r4, r5, r6, r7, r8);
}

OPD_s KICKVOTESEVENTzt = { 0x12D1D88,0x1C85330 };
unsigned int(*KICKVOTESEVENTz)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&KICKVOTESEVENTzt;
unsigned int KICKVOTESEVENT(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s  ~w~が除外投票してきた!", senderName);
	NotifyDown(scriptEventDialogText);
	return KICKVOTESEVENTz(r3, r4, r5, r6, r7, r8);
}

//OPD_s _NETWORK_START_SYNCED_SCENE_EVENT_t = { NETWORK_START_SYNCED_SCENE_EVENT, 0x1C85330 };
//unsigned int(*_NETWORK_START_SYNCED_SCENE_EVENT)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&_NETWORK_START_SYNCED_SCENE_EVENT_t;
//
//char AnimText[100];
//int AnimPro(int r3, int r4, int r5, int r6, int r7, int r8)
//{
//	int addressOfArgs = r3 + 10 * 0x4;
//	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
//	char *recieverName = (char*)(*(int*)(r4 + 0x78) + 0x10);
//	
//		snprintf(AnimText, sizeof(AnimText), "~r~警告!!  ~y~%s が ~g~貴方~w~をキックしてます!!", senderName);
//		NotifyDown(AnimText);
//		*(int*)addressOfArgs = 0;
//		return _NETWORK_START_SYNCED_SCENE_EVENT(r3, r4, r5, r6, r7);
//}

//void AnimationProtection(int r3, int r4, int r5, int r6, int r7, int r8) {
//	int addressOfArgs = r3 + 10 * 0x4;
//	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
//
//	char BufNoob[100];
//	snprintf(BufNoob, sizeof(BufNoob), "~r~警告!!  ~y~%s  ~w~が貴方を強制ゲームに招待してます!", senderName);
//	NotifyDown(BufNoob);
//	*(int*)addressOfArgs = 0;
//	return _NETWORK_START_SYNCED_SCENE_EVENT(r3, r4, r5, r6, r7);
//}


void RPprotection2(bool flag, bool toggle = false)
{
	char NOP_ENABLE[] = { 0x60, 0x00, 0x00, 0x00 };
	char adminKickOriginal[] = { 0x90, 0x7E, 0x00, 0x04 };
	if (flag)
	{
		if (PS3::ReadInt32(0x12CBD94) != 0x4E800020)
		{
			PS3::WriteBytes(0x12CBD94, ON, 4);
			PS3::WriteBytes(0x12D1D88, ON, 4);
			PS3::WriteBytes(0x172D78C, ONN, 4);
			if (toggle)
				NotifyDown("SCRIPT Protection ~g~ADDED", 1000);
		}
		if (PS3::ReadInt32(0x1358F9C) != 0x4E800020)
		{
			char Enable[] = { 0x60, 0x00, 0x00, 0x00 };
			PS3::WriteBytes(0x1358F9C, Enable, 4);
			PS3::WriteBytes(0x1358F08, NOP_ENABLE, 4);
		}
	}
	else
	{
		if (PS3::ReadInt32(0x12CBD94) != 0x7C0802A6)
		{
			PS3::WriteBytes(0x12CBD94, OFF, 4);
			PS3::WriteBytes(0x12D1D88, OFF, 4);
			PS3::WriteBytes(0x172D78C, OF, 4);
			if (toggle)
				NotifyDown("SCRIPT Protection ~r~DELETED", 1000);
		}
		if (PS3::ReadInt32(0x1358F9C) != 0x38A00006)
		{
			char UNKO[] = { 0x38 ,0xA0 ,0x00 ,0x06 };
			char AAAA[] = { 0x38 ,0x60 ,0x00 ,0x01 };
			PS3::WriteBytes(0x1358F9C, UNKO, 4);
			PS3::WriteBytes(0x1358F08, adminKickOriginal, 4);
		}
	}
}

bool EntiBlock;
bool ParadiseProtectionLOOP;
char dBytes1[] = { 0x4B, 0xA5, 0x26, 0x15 }; //block entity off
char dBytes2[] = { 0x8B, 0xD7, 0x00, 0x29 }; //Off
char dBytes3[] = { 0x62, 0xC3, 0x00, 0x00 }; //clone off
char eBytes1[] = { 0x48, 0x00, 0x00, 0x44 };
char eBytes2[] = { 0x48, 0x00, 0x00, 0x18 };
char eBytes3[] = { 0x60, 0x00, 0x00, 0x00 };




bool freezetest;
void FreezeTester(bool On)
{
	char Offbyte[] = { 0x62 , 0x83 , 0x00,0x00 };
	char Offbyte2[] = { 0x48 , 0x08 , 0xFE,0xDD };
	char Offbyte3[] = { 0x7C , 0x17 , 0x18,0x00 };
	char Offbyte4[] = { 0x40 , 0x82 , 0xFD,0xB0 };
	char Offbyte5[] = { 0x7F , 0xE1 , 0x08,0x08 };
	char Offbyte6[] = { 0x4B , 0xFF , 0xFD,0xA8 };

	char dropOn[] = { 0x65, 0x60, 0xFD, 0xCF };
	char dropOff[] = { 0x4B, 0xFF, 0xF8, 0xA1 };

	char FakeOn[] = { 0x64, 0x60, 0xFD, 0xCF };
	char FakeOff[] = { 0x2C, 0x03, 0x00, 0x00 };



	if (On)
	{
		//PS3::WriteBytes(0x9FBB48, eBytes3, 4);
		//PS3::WriteBytes(0x9FBB4C, eBytes3, 4);
		//PS3::WriteBytes(0x9FBB50, eBytes3, 4);
		PS3::WriteBytes(0x9FB990, eBytes3, 4); /////////
		PS3::WriteBytes(0x9FBB58, eBytes3, 4); //Freeze V3
		PS3::WriteBytes(0x9FBB5C, eBytes3, 4); /////////

		PS3::WriteBytes(0x9FFF0C, dropOn, 4);

		PS3::WriteBytes(0x9FBA5C, FakeOn, 4);
	}
	else
	{
	/*	PS3::WriteBytes(0x9FBB48, Offbyte, 4);
		PS3::WriteBytes(0x9FBB4C, Offbyte2, 4);
		PS3::WriteBytes(0x9FBB50, Offbyte3, 4);*/
		PS3::WriteBytes(0x9FB990, Offbyte5, 4); ////////
		PS3::WriteBytes(0x9FBB58, Offbyte5, 4); //Freeze V3 Off
		PS3::WriteBytes(0x9FBB5C, Offbyte6, 4); ////////


		PS3::WriteBytes(0x9FFF0C, dropOff, 4);

		PS3::WriteBytes(0x9FBA5C, FakeOff, 4);
		
	}
}


int qwertyyuiop(int asdfghjkl, int zxcvbnm)
{
	return asdfghjkl + zxcvbnm;
}

bool Paradisepro;


void HeliBlocker(bool toggle)
{
	char On[] = { 0x48, 0x00, 0x00, 0x44 };
	char Off[] = { 0x8B, 0xD7, 0x00, 0x29 };
	PS3::WriteBytes(0x133CD84, toggle ? On : Off, 4);
}

void entityBlocker(bool toggle)
{
	char dBytes1[] = { 0x4B, 0xA5, 0x26, 0x15 }; //block entity off
	char dBytes2[] = { 0x8B, 0xD7, 0x00, 0x29 }; //Off
	char dBytes3[] = { 0x62, 0xC3, 0x00, 0x00 }; //clone off
	char eBytes1[] = { 0x48, 0x00, 0x00, 0x44 };
	char eBytes2[] = { 0x48, 0x00, 0x00, 0x18 };
	char eBytes3[] = { 0x60, 0x00, 0x00, 0x00 };

	char Offbyte[] = { 0x62 , 0x83 , 0x00,0x00 };
	char Offbyte2[] = { 0x48 , 0x08 , 0xFE,0xDD };
	char Offbyte3[] = { 0x7C , 0x17 , 0x18,0x00 };
	char Offbyte4[] = { 0x40 , 0x82 , 0xFD,0xB0 };
	char Offbyte5[] = { 0x7F , 0xE1 , 0x08,0x08 };
	char Offbyte6[] = { 0x4B , 0xFF , 0xFD,0xA8 };


	if (toggle)
	{
		PS3::WriteBytes(0x1093188, eBytes3, 4);//Block all entities
		PS3::WriteBytes(0x133CB64, eBytes1, 4);//Pickups
		PS3::WriteBytes(0x133CE5C, eBytes1, 4);//Planes
		PS3::WriteBytes(0x133CAF4, eBytes1, 4);//Object 133CAF4
		PS3::WriteBytes(0x133CC40, eBytes1, 4);//Bikes
		PS3::WriteBytes(0x133CA84, eBytes1, 4);//Cars
		PS3::WriteBytes(0x133CD84, eBytes1, 4);//Helicopters
		PS3::WriteBytes(0x133CA44, eBytes2, 4);//Clone
		PS3::WriteBytes(0x133CDF0, eBytes1, 4);//Boat
		PS3::WriteBytes(0x133CCAC, eBytes1, 4);//Traler

		PS3::WriteBytes(0x133CBD4, eBytes1, 4);//??
		PS3::WriteBytes(0x133CD18, eBytes1, 4);//??
		PS3::WriteBytes(0x133CE5C, eBytes1, 4);//??
		PS3::WriteBytes(0x133CEC8, eBytes1, 4);//??
		PS3::WriteBytes(0x133CF38, eBytes1, 4);//??

		//PS3::WriteBytes(0x133CA00, eBytes2, 4);//Clone

		//
		//
		//
		//
	}
	else
	{
		PS3::WriteBytes(0x1093188, dBytes1, 4);//Block all entities
		PS3::WriteBytes(0x133CB64, dBytes2, 4);//Pickups
		PS3::WriteBytes(0x133CE5C, dBytes2, 4);//Planes
		PS3::WriteBytes(0x133CAF4, dBytes2, 4);//Object 133CAF4
		PS3::WriteBytes(0x133CC40, dBytes2, 4);//Bikes
		PS3::WriteBytes(0x133CA84, dBytes2, 4);//Cars
		PS3::WriteBytes(0x133CD84, dBytes2, 4);//Helicopters
		PS3::WriteBytes(0x133CA44, dBytes3, 4);//Clone
		PS3::WriteBytes(0x133CDF0, dBytes2, 4);//Boat
		PS3::WriteBytes(0x133CCAC, dBytes2, 4);//Traler

		PS3::WriteBytes(0x133CBD4, dBytes2, 4);//??
		PS3::WriteBytes(0x133CD18, dBytes2, 4);//??
		PS3::WriteBytes(0x133CE5C, dBytes2, 4);//??
		PS3::WriteBytes(0x133CEC8, dBytes2, 4);//??
		PS3::WriteBytes(0x133CF38, dBytes2, 4);//??

		//PS3::WriteBytes(0x133CA00, dBytes3, 4);//??
	}
}

//int write_process(void* destination, const void* source, size_t size)
//{
//	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
//	return_to_user_prog(int);
//}




bool TralerBlock1;
void TralerBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CCAC, eBytes1, 4);//Traler

	}
	else
	{
		PS3::WriteBytes(0x133CCAC, dBytes2, 4);//Traler

	}
}

bool BoatBlock1;
void BoatBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CDF0, eBytes1, 4);//Boat

	}
	else
	{
		PS3::WriteBytes(0x133CDF0, dBytes2, 4);//Boat

	}
}


bool CloneBlock1;
void CloneBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CA44, eBytes2, 4);//Clone

	}
	else
	{
		PS3::WriteBytes(0x133CA44, dBytes3, 4);//Clone

	}
}

bool HelicoptersBlock1;
void HelicoptersBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CD84, eBytes1, 4);//Helicopters

	}
	else
	{
		PS3::WriteBytes(0x133CD84, dBytes2, 4);//Helicopters

	}
}


bool CarsBlock1;
void CarsBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CA84, eBytes1, 4);//Cars

	}
	else
	{
		PS3::WriteBytes(0x133CA84, dBytes2, 4);//Cars

	}
}

bool BikesBlock1;
void BikesBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CC40, eBytes1, 4);//Bikes

	}
	else
	{
		PS3::WriteBytes(0x133CC40, dBytes2, 4);//Bikes
	}
}

bool ObjectBlock1;
void ObjectBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CAF4, eBytes1, 4);//Object 133CAF4

	}
	else
	{
		PS3::WriteBytes(0x133CAF4, dBytes2, 4);//Object 133CAF4

	}
}

bool PlanesBlock1;
void PlanesBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CE5C, eBytes1, 4);//Planes

	}
	else
	{
		PS3::WriteBytes(0x133CE5C, dBytes2, 4);//Planes

	}
}

bool ONsaisoku;
bool nnnn;
bool ParadiseBlocker;


//bool freezetest;
//void FreezeTester(bool On)
//{
//	char Offbyte[] = { 0x62 , 0x83 , 0x00,0x00 };
//	char Offbyte2[] = { 0x48 , 0x08 , 0xFE,0xDD };
//	char Offbyte3[] = { 0x7C , 0x17 , 0x18,0x00 };
//	char Offbyte4[] = { 0x40 , 0x82 , 0xFD,0xB0 };
//	char Offbyte5[] = { 0x7F , 0xE1 , 0x08,0x08 };
//	char Offbyte6[] = { 0x4B , 0xFF , 0xFD,0xA8 };
//
//	char dropOn[] = { 0x65, 0x60, 0xFD, 0xCF };
//	char dropOff[] = { 0x4B, 0xFF, 0xF8, 0xA1 };
//
//	char FakeOn[] = { 0x64, 0x60, 0xFD, 0xCF };
//	char FakeOff[] = { 0x2C, 0x03, 0x00, 0x00 };
//
//
//
//	if (On)
//	{
//		//PS3::WriteBytes(0x9FBB48, eBytes3, 4);
//		//PS3::WriteBytes(0x9FBB4C, eBytes3, 4);
//		//PS3::WriteBytes(0x9FBB50, eBytes3, 4);
//		PS3::WriteBytes(0x9FB990, eBytes3, 4); /////////
//		PS3::WriteBytes(0x9FBB58, eBytes3, 4); //Freeze V3
//		PS3::WriteBytes(0x9FBB5C, eBytes3, 4); /////////
//
//		PS3::WriteBytes(0x9FFF0C, dropOn, 4);
//
//		PS3::WriteBytes(0x9FBA5C, FakeOn, 4);
//	}
//	else
//	{
//		/*	PS3::WriteBytes(0x9FBB48, Offbyte, 4);
//		PS3::WriteBytes(0x9FBB4C, Offbyte2, 4);
//		PS3::WriteBytes(0x9FBB50, Offbyte3, 4);*/
//		PS3::WriteBytes(0x9FB990, Offbyte5, 4); ////////
//		PS3::WriteBytes(0x9FBB58, Offbyte5, 4); //Freeze V3 Off
//		PS3::WriteBytes(0x9FBB5C, Offbyte6, 4); ////////
//
//
//		PS3::WriteBytes(0x9FFF0C, dropOff, 4);
//
//		PS3::WriteBytes(0x9FBA5C, FakeOff, 4);
//
//	}
//}

bool PickupsBlock1;
void PickupsBlock(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x133CB64, eBytes1, 4);//Pickups

	}
	else
	{
		PS3::WriteBytes(0x133CB64, dBytes2, 4);//Pickups

	}
}

bool Blockallentities1;
void Blockallentities(bool toggle)
{
	if (toggle)
	{
		PS3::WriteBytes(0x1093188, eBytes3, 4);//Block all entities
	
	}
	else
	{
		PS3::WriteBytes(0x1093188, dBytes1, 4);//Block all entities

	}
}



float float_MiscOptions[50];

void ChangeCoords(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) {
		ENTITY::SET_ENTITY_COORDS1(PED::GET_VEHICLE_PED_IS_IN(Handle, 0), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS1(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}
void teleairport()
{
	CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(100.0, float_MiscOptions[0]);
	Vector3 Coords; Coords.x = -1208.71f; Coords.y = -3026.39f; Coords.z = 13.94f; ChangeCoords(Coords);
}

void SelfOptionAllApply(bool trueflag)
{
	//Invisible = trueflag;
	nocops = trueflag; NoCops(nocops);
	SuperJump = trueflag;
	SuperRun = !trueflag; if (SuperRun) { PLAYER::SuperRun(PLAYER::PLAYER_ID(), 1.49); }
}

void Collision_1(Entity entity, bool state)
{
	ENTITY::SET_ENTITY_VISIBLE2(entity, state, 0);
}

void Collision(Entity entity, bool state)
{
	ENTITY::SET_ENTITY_COLLISION(entity, state, 0);
}

bool Save;
void ProtectionAllApply(bool trueflag)
{
	PTFX = trueflag; PTFXs(PTFX);
	TaskP = trueflag; Tasks(TaskP);
	Ctask = trueflag; CTask(Ctask);
	VehiP = trueflag; Vehip(VehiP);
	Remvp = trueflag; RemvP(Remvp);
	FrezP = trueflag;
	ClearAreaAll = trueflag;
	VehicleAttachProtect = trueflag;
	Pedattach = trueflag;
	FreezeConsoleBAN = trueflag;
	RPprotection = trueflag; RPprotection2(RPprotection);
	//ScriptDetect = trueflag;
}

bool Flags[15];
void SessionChangeApply(bool toggle)
{
	if (toggle) //Saving
	{
		Flags[0] = PTFX;
		Flags[1] = TaskP;
		Flags[2] = Ctask;
		Flags[3] = VehiP;
		Flags[4] = Remvp;
		Flags[5] = FrezP;
		Flags[6] = ClearAreaAll;
		Flags[7] = VehicleAttachProtect;
		Flags[8] = Pedattach;
		Flags[9] = FreezeConsoleBAN;
		Flags[10] = RPprotection;
	}
	else		//Apply
	{
		PTFX = Flags[0]; PTFXs(PTFX);
		TaskP = Flags[1]; Tasks(TaskP);
		Ctask = Flags[2]; CTask(Ctask);
		VehiP = Flags[3]; Vehip(VehiP);
		Remvp = Flags[4]; RemvP(Remvp);
		FrezP = Flags[5];
		ClearAreaAll = Flags[6];
		VehicleAttachProtect = Flags[7];
		Pedattach = Flags[8];
		FreezeConsoleBAN = Flags[9];
		RPprotection = Flags[10]; RPprotection2(RPprotection);
	}
}

void chromevehicle(int vehicle, bool chrome)
{
	if (chrome)
	{
		RequestNetworkControl(vehicle);
		VEHICLE::SET_VEHICLE_COLOURS(vehicle, 120, 120);
	}
	else
	{
		RequestNetworkControl(vehicle);
		VEHICLE::SET_VEHICLE_COLOURS(vehicle, 0, 0);
	}
}
#pragma endregion

#pragma region Settings


bool IsRevealPeople(int selectedPlayer)
{
	return PS3::Read_Global(2390201 + selectedPlayer * 223 + 172) == 1;
}

bool isOffRadar(bool selectedPlayer)
{
	return PS3::Read_Global(2390201 + selectedPlayer * 223 + 170) == 1;
}
#pragma endregion

#pragma region Laser
void drawLaser()
{
	int VehHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	float Offset1[] = { 0.6f, 0.6707f, 0.3711f };
	float Offset2[] = { -0.6f, 0.6707f, 0.3711f };
	float Offset3[] = { 0.6f, 25.0707f, 0.3711f };
	float Offset4[] = { -0.6f, 25.0707f, 0.3711f };
	Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(VehHandle, Offset1[0], Offset1[1], Offset1[2]);
	Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(VehHandle, Offset2[0], Offset2[1], Offset2[2]);
	Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(VehHandle, Offset3[0], Offset3[1], Offset3[2]);
	Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(VehHandle, Offset4[0], Offset4[1], Offset4[2]);
	Vector3 StartCoords1 = { getcoords1.x, getcoords1.y, getcoords1.z };
	Vector3 StartCoords2 = { getcoords2.x, getcoords2.y, getcoords2.z };
	Vector3 EndCoords1 = { getcoords3.x, getcoords3.y, getcoords3.z };
	Vector3 EndCoords2 = { getcoords4.x, getcoords4.y, getcoords4.z };
	drawLine(StartCoords1, EndCoords1);
	drawLine(StartCoords2, EndCoords2);
}

void WeaponAmmoChange(char* hash, int ExplosionType = EXPLOSION_GRENADE)
{
	int Hash = GAMEPLAY::GET_HASH_KEY(hash);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Hash, -1, true, true);
	int Offset = GET_WEAPONS(Hash);
	int AmmoOffset = PS3::ReadInt32(Offset + AmmoInfo);
	PS3::WriteUInt32(AmmoOffset + Explosion_Default, ExplosionType);
	PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
}

void ShootVehicleRocket(char *Bullet)
{
	int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	int launchDistance = 250;
	int weaponHash = GAMEPLAY::GET_HASH_KEY(Bullet);
	float launchSpeed = 1500.0f;
	float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
	Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
	float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
	Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
	float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
	Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
	float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
	Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
	float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
	float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
	float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
	float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
}
#pragma endregion

#pragma region Compo
uint WeaponCompReturn(uint Hash)
{
	uint Offset = 0x2147FAC;
	uint indexLength = 0x11C;
	uint returnA = 0;
	for (uint i = 0; i < indexLength; i += 4)
	{
		uint Address = Offset + i;
		if (Address != 0 && Hash != 0)
		{
			returnA = PS3::ReadUInt32(Address);
			uint number1 = PS3::ReadUInt32(returnA + 0x08);
			uint number2 = PS3::ReadUInt32(returnA + 0x0C);
			if (number1 == Hash || number2 == Hash)
			{
				break;
			}
		}
	}
	return returnA;
}
#pragma endregion

#pragma region Session Func
int getHost()
{
	return NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
}

int getNumPlayers()
{
	int Amount = 0;
	for (int i = 0; i < 16; i++)
	{
		if (!(strstr(PLAYER::GET_PLAYER_NAME(i), "**Invalid**")))
			Amount++;
	}
	return Amount;
}

void NetworkSessionHostSinglePlayer(int SelectedPlayer)
{
	NETWORK::NETWORK_SESSION_HOST_SINGLE_PLAYER(SelectedPlayer);
}
int testNumPlayers()
{
	return NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
}

char* get_player_name(int id)
{
	char* Name = PLAYER::GET_PLAYER_NAME(id);
	if (PLAYER::IS_PLAYER_PLAYING(id))
	{
		if (PED::_IS_PED_DEAD(PLAYER::GET_PLAYER_PED(id), true))
		{
			char DeadPed[100];
			sprintf(DeadPed, "~r~死亡中 : %s", Name);
			return DeadPed;
		}
		else
		{
			return Name;
		}
	}
	else
	{
		return "プレイヤーが存在しません。";
	}
}

int getFreeSpots()
{
	return (16 - testNumPlayers());
}

char* getHostName()
{
	return get_player_name(getHost());
}
#pragma endregion

#pragma region Functions

bool FabOptionONN;

int scriptsetModel = -1;


bool GodModeCheck(int player) {
	//unsigned char flag;
	unsigned int flag2;
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player)))
	{
		//flag = *(unsigned char*)(GetEntityAddress(GET_PLAYER_PED(player)) + 0xB5);
		flag2 = PS3::ReadInt16(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB4);
	}
	if (flag2 != 0x3000)
		return true;
	return false;
}

bool GodModeDetected(int player)
{
	unsigned int addressValue;
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player))){	addressValue = PS3::ReadInt16(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB4);}
	if (addressValue != 0x3000)
		return true;
	return false;
}

bool IsPlayerInvisible(int player)
{
	if (player != PLAYER::PLAYER_ID())
	{
		unsigned char flag[1];
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player)))
		{
			flag[0] = *(unsigned char*)(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB7);
		}
		if (flag[0] == 0x00)
			return true;
		return false;
	}
}

int getFPS;

//////////////////////////////////////////////////////////
bool WorldOptions_Bool = true;
int contadoreljackson = 0;
char FPStext[60];

float LastFrameTime;

void AllImport1()
{
	if (PS3::ReadInt32(0x13AE688) != 0x4E800020)
	{
		PS3::WriteBytes(0x13AE688, ON, 4);
	}
}

void AllDefault1()
{
	if (PS3::ReadInt32(0x13AE688) != 0x7C0802A6)
	{
		PS3::WriteBytes(0x13AE688, OFF, 4);
	}
}
void Allpaaa1(bool toggle)
{
	if (toggle)
	{
		AllImport1();
		NotifyDown("軽量化", 2000);

		Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 100000000, true, 0, 0, 0);
		GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 100000000, 0, 0, 0, 0, 0);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
	}
	else
	{
		AllDefault1();
	}
}

bool KEIRYOU;
bool KEIRYOU2;

bool KEIRYOUKA;
void ReadTunable(int index, int value)
{
	int address = (*(int*)0x1E70374) + 4;
	{
		if (address != 0)
		{
			int temp = address;
			temp += (index * 4);
			//*(int*)temp = value;
			NotifyDown(ItoS(address));

		}
	}
}

void ReadTunable1(int index, int value)
{
	int address = (*(int*)0x1E70374) + 4;
	{
		if (address != 0)
		{
			int temp = address;
			temp += (index * 4);
			//*(int*)temp = value;
			NotifyDown(ItoS(temp));

		}
	}
}
bool SnowTEST;

int FPSCheckDelay;
int count_1;
bool directfreezeconsole;

//int g_uiSuperCars[] = { 0xB779A091, 0xB2FE5CF9, 0xB1D95DA0, 0x18F25AC7, 0x142E0DC3, 0x9AE6DDA1, 0x9F4B77BE, 0xAC5DF515, 0x185484E1, 0x767164D6, 0x6322B39A };
//
//void freezeCarDetection()
//{
//	char buffer[0x100];
//	char buffer1[0x100];
//
//	for (int i = 0; i < 18; i++)
//	{
//		int Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(i));
//
//		if (PED::IS_PED_IN_ANY_HELI(PLAYER::GET_PLAYER_PED(i)))
//		{
//			if (PED::IS_PED_IN_VEHICLE(i,Vehicle,1))
//			{
//				snprintf(buffer, 0x100, "~r~感知 ~w~%s が~g~フリーズカー(ヘリ)~w~を出した ", PLAYER::GET_PLAYER_NAME(i));
//				NotifyDown(buffer);
//			}
//		}
//	}
//}
//
//char bytes1_on[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x1B, 0xFA, 0xE0, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x1B, 0xFA, 0xC0, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x4C, 0xE7, 0x04, 0x3D, 0xF0, 0xD8, 0x45, 0x3E, 0x4C, 0xE7, 0x04, 0x3D, 0xF0, 0xD8, 0x45, 0x44, 0x7A, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xA0, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC7 };
//char bytes2_on[] = { 0x47, 0xC3, 0x4F, 0x80 };
//char bytes3_on[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//char bytes4_on[] = { 0x0C, 0x00, 0x00, 0x00 };
//void spoofvehicle()//semjases freeze vehickle
//{
//	PS3::WriteBytes(0x402DEA80, bytes1_on, 144); PS3::WriteBytes(0x4120CF88, bytes2_on, 4);
//	PS3::WriteBytes(0x4120D060, bytes3_on, 16);  PS3::WriteBytes(0x4120D08C, bytes4_on, 4);
//}

void FreezeHeli(int address)
{
	char bytes31[] = { 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04 };
	PS3::WriteBytes(address, bytes31, 8);
}

void FreezeHiko(int address)
{
	char bytes13[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04 };
	PS3::WriteBytes(address, bytes13, 8);
	//drawNotification("全車両飛行機化セット!!");

}


void FreezeNormal(int address)
{
	char bytes14[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05 };
	PS3::WriteBytes(address, bytes14, 8);
	//drawNotification("全車両ノーマル化!!");
}

bool Lobbyf()
{
	char *FuncByteshelicopterA = PS3::ReadBytes3(0x402D77F0, 0x90);//helicopter
	PS3::WriteBytes2((int)0x402DEA80, FuncByteshelicopterA, 0x90);//ADDER = 0x402DEA80
	char cmd1A[] = { 0x47, 0xF0, 0x4F, 0x80 };
	char cmd2A[0x10] = {};
	PS3::WriteBytes2((int)0x4120CC28, cmd1A, 4);
	PS3::WriteBytes2((int)0x4120CD00, cmd2A, 0x10);

	NotifyDown("~r~フリーズロビー");
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 c = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	int hash = GAMEPLAY::GET_HASH_KEY("adder");
	STREAMING::REQUEST_MODEL(hash);
	if (STREAMING::HAS_MODEL_LOADED(hash))
	{
		int Vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
		if (ENTITY::DOES_ENTITY_EXIST(Vehicle)) 
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			return true;
		}
		return false;
	}
	return false;
}



void NoClipCont()
{

	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

	int Vehiclee = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), ent = Vehiclee == 0 ? PLAYER::PLAYER_PED_ID() : Vehiclee;

	ENTITY::SET_ENTITY_COLLISION(ent, true, 1); Vector3 camvt = get_coords_from_cam(10.0f);
	ENTITY::FREEZE_ENTITY_POSITION(ent, true);

	if (ent == Vehiclee)
		if (ent == PLAYER::PLAYER_PED_ID())
		{
			ENTITY::SET_ENTITY_COLLISION(ent, false, 0);
		}
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, camvt.x, camvt.y, camvt.z, 0, 0, 0);
}
void UpdateNoCliploop()
{


	

	if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 205), CONTROLS::IS_CONTROL_JUST_PRESSED(2, 205))

		

	if (CONTROLS::IS_CONTROL_PRESSED(2, 199))
	{

		NoClipCont();
	}
	if (Analog(189) > 127)
	{
		NoClipCont();
	}

	if (Analog(189) < 127)
	{
		NoClipCont();
	}

	if (Analog(188) > 127)
	{
		NoClipCont();
	}

	if (Analog(188) < 127)
	{
		NoClipCont();
	}
}
void ForcekickLoop(int player)
{
		PS3::Write_Global(1588610 + (player + 1), 1);
}
//void ForcekickLoop1(int player)
//{
//	PS3::Write_Global(1588610 + (player + 1), 0);
//}
bool lobbyf;

int returnPlayerStats()
{
	return (PLAYER::PLAYER_ID() * 306);
}
bool Rankkotei;
int RankPPP;
bool ParadiseProtectionAuto[2];
int ParadiseTimer;
void spoofRank(int rank)
{
	PS3::Write_Global(1581952 + returnPlayerStats(), rank);
}
/*
PS3::WriteBytes(0x9FB990, eBytes3, 4); /////////
PS3::WriteBytes(0x9FBB58, eBytes3, 4); //Freeze V3
PS3::WriteBytes(0x9FBB5C, eBytes3, 4); /////////

PS3::WriteBytes(0x9FFF0C, dropOn, 4); //drop kick

PS3::WriteBytes(0x9FBA5C, FakeOn, 4); //fake leave v2
*/

void IDSearch(int PLAY)
{
	char GoMim[100];
	sprintf(GoMim, "0x%x", GetEntityAddress(PLAYER::GET_PLAYER_PED(selectedPlayer)));;
	NotifyDown(GoMim, 5000);
}
void Functions()
{
	//PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 0);

	if (Rankkotei)
	{
		spoofRank(RankPPP);
	}
	if (lobbyf)
	{
		if (Lobbyf())
		{
			lobbyf = false;
		}
	}

	if (directfreezeconsole)
	{
		static int delay = 0;
		count_1 += 10;
		if (PLAYER::IS_PLAYER_PLAYING(selectedPlayer))
		{
			static int delay = 0;
			if (delay < GAMEPLAY::GET_GAME_TIMER())
			{
				givePlayerMoney1(selectedPlayer, 100000000/*0x7FFFFFFF*/);
				delay = GAMEPLAY::GET_GAME_TIMER() + 250;
			}
		}

		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::GET_PLAYER_PED(selectedPlayer));

		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
		{
			Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
			mycoords.z = mycoords.z + 2.5;
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, mycoords.x, mycoords.y, mycoords.z, 0, 40000, 0x113FD533, 0, 1);
		}
		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED)
		{
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED(selectedPlayer));
			directfreezeconsole = false;
			NotifyDown("完了しました。");

		}
		if (count_1 > 48000)
		{
			NotifyDown("完了しました。");
			count_1 = 0;
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED(selectedPlayer));
			directfreezeconsole = false;
		}
		drawText("~y~個人フリーズをかけています...", 0, 0.425, 0.82, 0.29, 0.45, 255, 255, 255, 255, true);
	}
	//if (gmode)
	//{
	//	PLAYER::SET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_PED_ID(),50);
	//	PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), 50);
	//	//ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
	//	ENTITY::SET_ENTITY_CAN_BE_DAMAGED(PLAYER::PLAYER_PED_ID(), 0);
	//	ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 1, 1, 1, 1, 1, 1, 1, 1);
	//	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 0);
	//	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 0);
	//	PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
	//	PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID());
	//	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
	//}
	//else
	//{
	//	//ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
	//	ENTITY::SET_ENTITY_CAN_BE_DAMAGED(PLAYER::PLAYER_PED_ID(), 1);
	//	ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 0, 0);
	//	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 1);
	//	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 1);
	//	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
	//}
	if (gmode) {//Undetected Godmode
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 1, 1, 1, 1, 1, 0, 0, 0);
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 0);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 0);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
	}
	else
	{
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 0, 0);
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 1);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 1);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
	}
	
	if (ObjectSizeBool)
	{
		RequestNetworkControl(ObjectList[ObjectSelectedIndex]);
		*(float*)(*(int*)(GetEntityAddress(ObjectList[ObjectSelectedIndex]) + 48) + 0x28) = ObjectSizeVv;
		*(float*)(*(int*)(GetEntityAddress(ObjectList[ObjectSelectedIndex]) + 48) + 0x14) = ObjectSizeVv;
		*(float*)(*(int*)(GetEntityAddress(ObjectList[ObjectSelectedIndex]) + 48) + 0x0) = ObjectSizeVv;
	}

	
	

	/*if (entitiesPoolPart1 < 0x40000000)
	{
		
	}
	else if (entitiesPoolPart2 < 0x40000000)
	{
		
	}
	else
	{
		int* entities = (int*)0x10020000;
		int count = worldGetAllEntities(entities);
		for (int i = 0; i < count; i++)
		{
			if (entities[i] != NULL && ENTITY::DOES_ENTITY_EXIST(entities[i]) && entities[i] != PLAYER::PLAYER_PED_ID() && !ENTITY::IS_ENTITY_DEAD(entities[i]))
			{
				Vector3 coordsPly = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				Vector3 coordsEntity = ENTITY::GET_ENTITY_COORDS(entities[i], true);
				drawLine(coordsPly, coordsEntity, Red);
			}
		}
	}*/

	if (FabOptionONN)
	{
		

	}
	if (Rocket_Player_Shoot[0]) //緑レーザー
	{

		HelpTextDraw("L3 : Shoot Rocket");
		drawLaser();
		ChangeAmmo();
		if (isPressed(Button_L3))
			ShootVehicleRocket("VEHICLE_WEAPON_PLAYER_LASER");
	}

	if (Rocket_Player_Shoot[1]) //赤レーザー 
	{

		HelpTextDraw("L3 : Shoot Rocket");
		drawLaser();
		ChangeAmmo();
		if (isPressed(Button_L3))
			ShootVehicleRocket("VEHICLE_WEAPON_ENEMY_LASER");
	}

	if (Rocket_Player_Shoot[2]) //戦車
	{
		HelpTextDraw("L3 : Shoot Rocket");
		drawLaser();
		if (isPressed(Button_L3))
			ShootVehicleRocket("VEHICLE_WEAPON_TANK");
	}

	if (Rocket_Player_Shoot[3]) //RPG
	{
		HelpTextDraw("L3 : Shoot Rocket");
		drawLaser();
		if (isPressed(Button_L3))
			ShootVehicleRocket("VEHICLE_WEAPON_SPACE_ROCKET");
	}
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !Invisible);

	

	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			switch (keyboardAction)
			{
			case 0: //addIntOption
				*keyboardIntVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				keyboardActive = false;
				break;
			case 1:
				keyboardVar = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				MapObjectName = keyboardVar;
				CreateMap = true;
				keyboardActive = false;
				break;
			case 2:
				PedName2 = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				PedName = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				PedSpawn = true;
				break;
			case 3: ChangeName(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT(), 0); break;
			case 4: ChangeName(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT(), 1); break;
			case 5: GlobalHack(StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()), 0); break;
			case 6: GlobalHack(StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()), 1); break;
			case 7: GlobalHack(StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()), 2); break;
			case 8: GlobalHack(StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()), 3); break;
			 break;
			}
			

		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}

	if (LoopAttach2)
	{
		if (ShotToEntity)
		{
			Bone = ENTITY::_GET_ENTITY_BONE_INDEX(Selected, BoneList[BoneIndex]);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PedList[PedSelectedIndex], Selected, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
		}
		else
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PedList[PedSelectedIndex], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
		}
	}

	if (ShotToEntity)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Target))
			{
				if (ENTITY::IS_ENTITY_A_VEHICLE(Target))
				{
					Selected = Target;
					NotifyDown("Entity(Vehicle) Selected!", 1000);
				}
				else if (ENTITY::IS_ENTITY_AN_OBJECT(Target))
				{
					Selected = Target;
					NotifyDown("Entity(Object) Selected!", 1000);
				}
				else
				{
					Selected = Target;
					NotifyDown("Entity Selected!", 1000);
				}
			}
		}
	}

	if (nocops)
	{
		NoCops(nocops);
	}

	if (SuperJump)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	//unsigned int Result = PS3::ReadUInt32((int)PS3::ReadUInt32(0x1CFB0A0) + 0x28) + 0xC;
	//if (superpunch)
	//{
	//	for (int i = 0; i < 21; i++)
	//	{
	//		PS3::WriteFloat(Result + (i * 0x20), 10000000000);
	//		PS3::WriteFloat(Result + (i * 0x20) + 4, 10000000000);
	//	}
	//}

	if (Exmelee)
	{
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	if (fireammo)
	{
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	if (Exammo)
	{
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	}

	for (int i = 0; i < 16; i++)
	{
		if (i != PLAYER::PLAYER_ID()) // 他人用
		{
			if (MoneyFlag[i])
			{
				if (MoneyTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					STREAMING::REQUEST_MODEL(0x113FD533);
					Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
					mycoords.z = mycoords.z + PlusMoneyZ;
					OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, mycoords.x, mycoords.y, mycoords.z, 0, 40000, 0x113FD533, 0, 1);
					MoneyTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;

				}
			}
			else if (allplayer40k)
			{
				if (MoneyTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					STREAMING::REQUEST_MODEL(0x113FD533);
					if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + PlusMoneyZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, mycoords.x, mycoords.y, mycoords.z, 0, 40000, 0x113FD533, 0, 1);
						MoneyTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
					}
				}
			}
			if (ParachuteFlag[i])
			{
				if (ParachuteTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
					mycoords.z = mycoords.z + PlusMoneyZ;
					OBJECT::CREATE_AMBIENT_PICKUP(0x6773257D, mycoords.x, mycoords.y, mycoords.z, 0, 0, 1, 0, 1);
					ParachuteTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
				}
			}
			if (DropSnackFlag[i])
			{

			}
			if (TeleportGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						TeleportInScene(PLAYER::GET_PLAYER_PED(i), "mini@strip_club@private_dance@part3", "priv_dance_p3", ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z);
					}
				}
			}
			if (KickLoop[i])
			{
				/*if (KickLoop[i] && !KICKtimer && !TNT > 100)
				{
					PS3::Write_Global(1588610 + (selectedPlayer + 1), 0);
					forceSessionUpdate(selectedPlayer); 
					playerIsHost(PLAYER::PLAYER_ID());
					TimerGAME = GAMEPLAY::GET_GAME_TIMER() + 500;
					KICKtimer = true;
				}
				else if (KICKtimer && TimerGAME < GAMEPLAY::GET_GAME_TIMER())
				{
					PS3::Write_Global(1588610 + (selectedPlayer + 1), 1);
					forceSessionUpdate(selectedPlayer);
					playerIsHost(PLAYER::PLAYER_ID());
					KICKtimer = false;
					TNT++;
				}
				if (TNT)
				{
					KickLoop = false;
					NotifyDown("Ok");
					TNT = 0;
				}*/

			}
			if (ExplosionGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 29, 0.5f, true, false, 0);
					}
				}
			}
			if (FireGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_DIR_FLAME, 5.0, 1, 0, 0);
					}
				}
			}
			if (SteamGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 13, 5.0, 1, 0, 0);
					}
				}
			}
			if (FreaGun[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 22, 5.0, 1, 0, 0);
					}
				}
			}if (FireWorkGun[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 35, 5.0, 1, 0, 0);
					}
				}
			}
			if (MoneygunPlayerFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						STREAMING::REQUEST_MODEL(0x113FD533);
						if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
						{
							OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 0, 40000, 0x113FD533, 0, 1);
						}
					}
					else
					{
						Vector3 AAX = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
						{
							OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, AAX.x, AAX.y, AAX.z + 2, 0, 40000, 0x113FD533, 0, 1);
						}
					}
				}
			}
			if (ESPFlag[i] || AllESP)
			{
				RGBA Markers = { 255, 0, 0, 255 };
				int playerHandle = PLAYER::GET_PLAYER_PED(i);
				//bool bPlayerOnlineExists = ENTITY::DOES_ENTITY_EXIST(playerHandle);
				Vector3 playerOnlineCoords = get_entity_coords_orig(playerHandle, false);
				Vector3 playerCoords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
				char* name = PLAYER::GET_PLAYER_NAME(i);
				float distance = DistanceBetweenVectors(playerCoords, playerOnlineCoords);
				//int armor = PED::GET_PED_ARMOUR(playerHandle);
				char text[100];

				float xa;
				float ya;
				bool screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, &xa, &ya);

				switch (ESPVar)
				{
				case 0:Markers.R = 255; Markers.G = 0; Markers.B = 0; break;
				case 1:Markers.R = 0; Markers.G = 255; Markers.B = 0; break;
				case 2:Markers.R = 0; Markers.G = 0; Markers.B = 255; break;
				}

				//255, 0, 0, 255
				if (NameESPFlag)
				{
					sprintf(text, "%s\n %i", name, (int)distance);
					drawText(text, 0, xa, ya, 0.4f, 0.4f, Markers.R, Markers.G, Markers.B, Markers.A, true, false);
				}

				GRAPHICS::DRAW_LINE(playerCoords.x, playerCoords.y, playerCoords.z, playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, Markers.R, Markers.G, Markers.B, Markers.A);
				Kiste(playerOnlineCoords, Markers);
			}
			if (WantedFlag[i])
			{
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(i) != 0)
				{
					removePlayerWantedLevel(i);
				}
			}
		}
		else                          // 自分用
		{
			if (MoneyFlag[i])
			{
				if (MoneyTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					STREAMING::REQUEST_MODEL(0x113FD533);
					if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + PlusMoneyZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, mycoords.x, mycoords.y, mycoords.z, 0, 40000, 0x113FD533, 0, 1);
						MoneyTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
					}
				}
			}
			else if (allplayer40k)
			{
				if (MoneyTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					STREAMING::REQUEST_MODEL(0x113FD533);
					if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + PlusMoneyZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, mycoords.x, mycoords.y, mycoords.z, 0, 40000, 0x113FD533, 0, 1);
						MoneyTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
					}
				}
			}
			if (ParachuteFlag[i])
			{
				if (ParachuteTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
					mycoords.z = mycoords.z + PlusMoneyZ;
					OBJECT::CREATE_AMBIENT_PICKUP(0x6773257D, mycoords.x, mycoords.y, mycoords.z, 0, 0, 1, 0, 1);
					ParachuteTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
				}
			}
			if (DropSnackFlag[i])
			{
				if (DropSnackTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
					mycoords.z = mycoords.z + PlusMoneyZ;
					OBJECT::CREATE_AMBIENT_PICKUP(0x1CD2CF66, mycoords.x, mycoords.y, mycoords.z, 0, 0, 1, 0, 1);
					DropSnackTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
				}
			}
			if (DropWeaponFlag[i])
			{
				if (DropSnackTimer[i] < GAMEPLAY::GET_GAME_TIMER())
				{
					if (!(WeaponIndex > 57))
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + PlusMoneyZ;
						int Hash = GAMEPLAY::GET_HASH_KEY(WEAPONMENU[WeaponIndex]);
						OBJECT::CREATE_AMBIENT_PICKUP(Hash, mycoords.x, mycoords.y, mycoords.z, 0, 0, 1, 0, 1);
						WeaponIndex++;
						DropSnackTimer[i] = GAMEPLAY::GET_GAME_TIMER() + 50;
					}
					else
					{
						WeaponIndex = 0;
					}
				}
			}
			if (TeleportGunFlag[i])
			{
				TeleportPedGun(PLAYER::PLAYER_PED_ID());
			}
			if (ExplosionGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 29, 0.5f, true, false, 0);
					}
				}
			}
			if (FireGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_DIR_FLAME, 5.0, 1, 0, 0);
					}
				}
			}
			if (SteamGunFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 13, 5.0, 1, 0, 0);
					}
				}
			}
			if (MoneygunPlayerFlag[i])
			{
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
				{
					if (__GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000))
					{
						STREAMING::REQUEST_MODEL(0x113FD533);
						if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
						{
							OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 0, 40000, 0x113FD533, 0, 1);
						}
					}
					else
					{
						Vector3 AAX = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						if (STREAMING::HAS_MODEL_LOADED(0x113FD533) == 1)
						{
							OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, AAX.x, AAX.y, AAX.z + 2, 0, 40000, 0x113FD533, 0, 1);
						}
					}
				}
			}
			if (ESPFlag[i])
			{
				if (!ESPFlag[i])
				{
					RGBA Markers = { 255, 0, 0, 255 };
					int playerHandle = PLAYER::GET_PLAYER_PED(i);
					//bool bPlayerOnlineExists = ENTITY::DOES_ENTITY_EXIST(playerHandle);
					Vector3 playerOnlineCoords = get_entity_coords_orig(playerHandle, false);
					Vector3 playerCoords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
					char* name = PLAYER::GET_PLAYER_NAME(i);
					float distance = DistanceBetweenVectors(playerCoords, playerOnlineCoords);
					//int armor = PED::GET_PED_ARMOUR(playerHandle);
					char text[100];

					float xa;
					float ya;
					bool screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, &xa, &ya);

					switch (ESPVar)
					{
					case 0:Markers.R = 255; Markers.G = 0; Markers.B = 0; break;
					case 1:Markers.R = 0; Markers.G = 255; Markers.B = 0; break;
					case 2:Markers.R = 0; Markers.G = 0; Markers.B = 255; break;
					}

					//255, 0, 0, 255
					if (NameESPFlag)
					{
						sprintf(text, "%s\n %i", name, (int)distance);
						drawText(text, 0, xa, ya, 0.2f, 0.2f, Markers.R, Markers.G, Markers.B, Markers.A, true, false);
					}

					GRAPHICS::DRAW_LINE(playerCoords.x, playerCoords.y, playerCoords.z, playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, Markers.R, Markers.G, Markers.B, Markers.A);
					Kiste(playerOnlineCoords, Markers);
				}
			}
			if (WantedFlag[i])
			{
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(i) != 0)
				{
					removePlayerWantedLevel(i);
				}
			}
		}
	}
	
	if (SetPlayerAnimation)
	{
		STREAMING::REQUEST_ANIM_DICT(Animations2[0]);
		if (STREAMING::HAS_ANIM_DICT_LOADED(Animations2[0]))
		{
			Vector3 MyCoordsForTPtoMe2222;
			if (UNKO222)
			{
				MyCoordsForTPtoMe2222 = MyCoordsForTPtoMe;
			}
			else
			{
				if (Teleporting)
				{
					MyCoordsForTPtoMe2222 = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 1);

				}
				else
				{
					MyCoordsForTPtoMe2222 = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
				}
			}
			int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(MyCoordsForTPtoMe2222.x, MyCoordsForTPtoMe2222.y, MyCoordsForTPtoMe2222.z, 0, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(selectedPlayer)), 2, 0, 1, 1.0f, 0.0f, 1.0f);
			PED::SET_SYNCHRONIZED_SCENE_RATE(scene2, 1000.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_4(PLAYER::GET_PLAYER_PED(selectedPlayer), scene2, Animations2[0], Animations2[1], 8.0f, -8.0, 5, 0, 30, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
			SetPlayerAnimation = false;
			Teleporting = false;
		}
	}

	if (SlingShot)
	{
		for (int i = 0; i < 3; i++)
		{
			int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
			RequestNetworkControl(veh);
			ApplyForce(veh, 0, 0, 10, 0, 0, 0);
		}
		SlingShot = false;
	}

	if (boost)
	{
		for (int i = 0; i < 3; i++)
		{
			int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
			RequestNetworkControl(veh);
			float Speed222 = ENTITY::GET_ENTITY_SPEED(veh) + 100.0f;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, Speed222);
		}
		boost = false;
	}

	if (carstop)
	{
		for (int i = 0; i < 3; i++)
		{
			int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0);
		}
		carstop = false;
	}


	if (soratobu)
	{
		RequestNetworkControl(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true));
		if (RequestNetworkControl(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true)));
		{
			ApplyForce(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true), 0, 100, 0, 0, 0, 0);
		}
	}

	if (ObjectAttach)
	{
		int GetMe = Create_Map_int(AttachObjectID);
		if (GetMe != 0)
		{
			ATTACH_ENTITY_TO_ENTITY(GetMe, PLAYER::GET_PLAYER_PED(selectedPlayer), PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), BONSINTS[GetPedBoneIndex]), One1.x, One1.y, One1.z, Two1.x, Two1.y, Two1.z);
			ToggleCollisionEntity(GetMe, false);
			ENTITY::SET_ENTITY_VISIBLE(GetMe, true);
			ObjectAttach = false;
			GetMe = 0;
		}
	}

	if (StealClothes)
	{
		CopyingOutfit();
		StealClothes = false;
	}


	/*if (DoFreezeConsole && !DeleteSpawnedPedFreeze)
	{
		Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		Vector3 TheirCoordss = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
		float Distance = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(MyPos.x, MyPos.y, MyPos.z, TheirCoordss.x, TheirCoordss.y, TheirCoordss.z, false);
		if (Distance < 150) NotifyDown("~y~distance from the player to freezer");
		else
		{
			FreezePedID = CREATE_PED_NORMAL(0x856CFB02, TheirCoordss);
			if (FreezePedID != 0)
			{
				ATTACH_ENTITY_TO_ENTITY_T(FreezePedID, PLAYER::GET_PLAYER_PED(selectedPlayer));
				DeleteSpawnedPedFreezeDelay = GAMEPLAY::GET_GAME_TIMER() + 10000;
				DeleteSpawnedPedFreeze = true;
				NotifyDown("~r~Freezing Player");
			}
		}
	}
	else if (DeleteSpawnedPedFreeze && DeleteSpawnedPedFreezeDelay < GAMEPLAY::GET_GAME_TIMER())
	{
		PED::DELETE_PED1(&FreezePedID);
		NotifyDown("~y~Player Freeze Sucess!");
		DeleteSpawnedPedFreeze = false;
		DoFreezeConsole = false;
	}*/

	//if (GTA2CamTEST)
	//{
	//	if (CAM::DOES_CAM_EXIST(GTA2Cam)) CAM::SET_CAM_ACTIVE(GTA2Cam, 1);
	//	else
	//	{
	//		GTA2Cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
	//		CAM::ATTACH_CAM_TO_ENTITY(GTA2Cam, PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, CAMHIGH, 1);
	//		Vector3 TINPO = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//		CAM::POINT_CAM_AT_COORD(GTA2Cam, TINPO.x - 90, TINPO.y, -1000000000);
	//		CAM::SET_CAM_ACTIVE(GTA2Cam, 1);
	//	}
	//	CAM::RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0);
	//}
	//else if (CAM::DOES_CAM_EXIST(GTA2Cam))
	//{
	//	CAM::DESTROY_CAM(GTA2Cam, 0);
	//	CAM::RENDER_SCRIPT_CAMS(0, 0, 3000, 1, 0);
	//	GTA2Cam = 0;
	//	//CAM::SET_CAM_ACTIVE(GTA2Cam, 0);
	//}

	if (DeleteAllWantedLevels)
	{
		for (int i = 0; i < 16; i++)
		{
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(i) != 0)
			{
				removePlayerWantedLevel(i);
			}
		}
	}

	if (ShootBulletAPlayer) {
		Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Vector3 pcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		int hash;
		hash = GAMEPLAY::GET_HASH_KEY(BulletAtPlayerString);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(mycoords.x, mycoords.y, mycoords.z, pcoords.x, pcoords.y, pcoords.z, 0, 0, hash, PLAYER::PLAYER_PED_ID(), 0, 0, 500);
		if (!ShootBulletAPlayerLoop) {
			ShootBulletAPlayer = false;
		}
	}

	if (DeleteGun)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			RequestNetworkControl(Target);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
			if (ENTITY::IS_ENTITY_A_PED(Target))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Target, false))
				{
					Target = PED::GET_VEHICLE_PED_IS_IN(Target, false);
					int NumSeats = VEHICLE::_GET_VEHICLE_MODEL_MAX_NUMBER_OF_PASSENGERS(ENTITY::GET_ENTITY_MODEL(Target));
					for (int i = -1; i < NumSeats - 1; i++)
					{
						if (!VEHICLE::IS_VEHICLE_SEAT_FREE(Target, i))
						{
							Entity PedID = VEHICLE::GET_PED_IN_VEHICLE_SEAT(Target, i);
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PedID);
							Freeze(PedID);
							PED::DELETE_PED(&PedID);
						}
					}
					RequestNetworkControl(Target);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
					VEHICLE::DELETE_VEHICLE(&Target);
					ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
				}
				else
				{
					PED::DELETE_PED(&Target);
					ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
				}
			}
			else if (ENTITY::IS_ENTITY_A_VEHICLE(Target))
			{
				VEHICLE::DELETE_VEHICLE(&Target);
				ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
			}
			else if (ENTITY::IS_ENTITY_AN_OBJECT(Target))
			{
				RequestNetworkControl(Target);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
				ENTITY::DETACH_ENTITY(Target, 1, 1);
				ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
				ENTITY::DELETE_ENTITY(&Target);
			}
			else
			{
				ENTITY::DELETE_ENTITY(&Target);
				ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
			}
		}
	}

	if (UnlimitedAmmo1)
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 1);
	}
	else
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 0);
	}

	if (ShootVehicle)
	{
		if (!IsShootingVehicle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				GetShotVehicle = ShootVehicleChar[SelectedShotVehicleVar];
				IsShootingVehicle = true;
			}
		}
		else
		{
			float AAA[] = { 0.0f, 3.0f, 2.0f };
			Vector3 UNKO = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_orig(PLAYER::PLAYER_PED_ID(), AAA);
			Vector3 TINKO = GET_GAMEPLAY_CAM_ROT_orig(2);
			if (Create_Vehicle_int(GetShotVehicle, UNKO, 80.0f, TINKO) != 0)
			{
				IsShootingVehicle = false;
			}
		}
	}

	if (RapidFire)
	{
		if (GAMEPLAY::GET_GAME_TIMER() > RapidFireDelay)
		{
			int Handle = PLAYER::PLAYER_PED_ID();
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(Handle, &weaponHash, 0);
			if (PED::IS_PED_ON_FOOT(Handle) && CONTROLS::IS_CONTROL_PRESSED(0, Button_R2))
			{
				float qqq[] = { 0 , 1 , 0 };
				Vector3 FromCoord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS3(Handle, qqq[0], qqq[1], qqq[2]);
				Vector3 ToCoord = GetCoordsInfrontOfCam(75);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoord.x, FromCoord.y, FromCoord.z, ToCoord.x, ToCoord.y, ToCoord.z, 250, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 0, 750);//250
				RapidFireDelay = GAMEPLAY::GET_GAME_TIMER() + 50;
			}
		}
	}

	if (PUBGMode)
	{
		if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &b2, true))
		{
			UNKO = ENTITY::GET_ENTITY_MODEL(WEAPON::_0x5D73CD20(PLAYER::PLAYER_PED_ID()));
			IsPUBGWEapon = true;
		}
		else
		{
			IsPUBGWEapon = false;
		}
		if (IsPUBGWEapon)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(PUBGWeaponEntity))
			{
				Backup = UNKO;
				PUBGWeaponEntity = Create_Map_int("", UNKO, true);
			}
			else
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(PUBGWeaponEntity, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 24818), PUBGSelect.Lx, PUBGSelect.Ly, PUBGSelect.Lz, PUBGSelect.Rx, PUBGSelect.Ry, PUBGSelect.Rz, 1, 1, 0, 1, 2, 1);
			}
			if (ENTITY::IS_ENTITY_ATTACHED(PUBGWeaponEntity))
			{
				if (Backup != UNKO)
				{
					DeleteEntity(PUBGWeaponEntity);
				}
			}
		}
		else
		{
			if (ENTITY::DOES_ENTITY_EXIST(PUBGWeaponEntity))
			{
				DeleteEntity(PUBGWeaponEntity);
			}
		}
	}
	else
	{
		if (ENTITY::DOES_ENTITY_EXIST(PUBGWeaponEntity))
		{
			DeleteEntity(PUBGWeaponEntity);
		}
	}

	if (HyperDxColorSelect)
	{
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.5, 0.05, 0, 0, 0, 200);
		int NumberOfStates = 153;
		float Width = 0.495 / NumberOfStates;
		for (int i = 0; i < NumberOfStates; i++)
			GRAPHICS::DRAW_RECT(0.255 + (Width * i), 0.5, Width, 0.04, GetRFromI(i), GetGFromI(i), GetBFromI(i), 200);

		GRAPHICS::DRAW_RECT(0.255 + (Width * RGB_Left), 0.5, 0.01, 0.07, 0, 0, 0, 200);
		GRAPHICS::DRAW_RECT(0.255 + (Width * RGB_Left), 0.5, 0.005, 0.065, GetRFromI((int)RGB_Left), GetGFromI((int)RGB_Left), GetBFromI((int)RGB_Left), 200);

		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Dpad_Left))
		{
			RGB_Left -= 0.5;
			if (RGB_Left < 0)
				RGB_Left = 153;
		}
		else if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Dpad_Right))
		{
			RGB_Left += 0.5;
			if (RGB_Left > 153)
				RGB_Left = 0;
		}
		ColorR = GetRFromI((int)RGB_Left);
		ColorG = GetGFromI((int)RGB_Left);
		ColorB = GetBFromI((int)RGB_Left);
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_X))
		{
			HyperDxColorSelect = false;
		}
	}

	if (Slow_Rainbow_Loop) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			if (menu_h_r == 5) {
				if (menu_h_g > 5)
					menu_h_g -= 1;
				if (menu_h_b < 255)
					menu_h_b += 1;
			}
			if (menu_h_g == 5) {
				if (menu_h_b > 5)
					menu_h_b -= 1;
				if (menu_h_r < 255)
					menu_h_r += 1;
			}
			if (menu_h_b == 5) {
				if (menu_h_r > 5)
					menu_h_r -= 1;
				if (menu_h_g < 255)
					menu_h_g += 1;
			}
			if (menu_h_r1 == 5) {
				if (menu_h_g1 > 5)
					menu_h_g1 -= 1;
				if (menu_h_b1 < 255)
					menu_h_b1 += 1;
			}
			if (menu_h_g1 == 5) {
				if (menu_h_b1 > 1)
					menu_h_b1 -= 5;
				if (menu_h_r1 < 255)
					menu_h_r1 += 1;
			}
			if (menu_h_b1 == 5) {
				if (menu_h_r1 > 5)
					menu_h_r1 -= 1;
				if (menu_h_g1 < 255)
					menu_h_g1 += 1;
			}
			if (Extra1 == 5) {
				if (Extra2 > 1)
					Extra2 -= 1;
				if (Extra1 < 145)
					Extra1 += 1;
			}
			if (Extra2 == 5) {
				if (Extra1 > 1)
					Extra1 -= 1;
				if (Extra2 < 145)
					Extra2 += 1;
			}
			RequestNetworkControl(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), menu_h_r, menu_h_g, menu_h_b);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), menu_h_r1, menu_h_g1, menu_h_b1);
			//VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), Extra1, Extra2);
		}
	}

	if (RandomColorLoop) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			RandomColor(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
		}
	}

	if (vehflymode)
	{
		int PedHandle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(PedHandle, 0))
		{
			if (vehflymode1)
			{
				char SpeedText[40];
				strcpy(SpeedText, "Speed ~b~");
				strcat(SpeedText, FtoS(vehflymodeSpeed, 100));
				//sprintf(SpeedText, "Speed ~b~%s", FtoS(vehflymodeSpeed,100));
				drawText("~b~L3 ~w~Rotation", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
				drawText("~b~R1 ~w~Up", 0, 0.3, 0.125, 0.4, 0.4, 255, 128, 255, 255, false, false);
				drawText("~b~R2 ~w~Go", 0, 0.3, 0.150, 0.4, 0.4, 255, 128, 255, 255, false, false);
				drawText("~b~R3 ~w~Stop Noclip", 0, 0.3, 0.175, 0.4, 0.4, 255, 128, 255, 255, false, false);
				drawText("~b~L1 ~w~Down", 0, 0.3, 0.200, 0.4, 0.4, 255, 128, 255, 255, false, false);
				drawText(SpeedText, 0, 0.3, 0.225, 0.4, 0.4, 255, 128, 255, 255, false, false);

				if (isPress(Dpad_Right))
				{
					if (vehflymodeSpeed > 10.0f)
					{
						vehflymodeSpeed = 0;
					}
					else
					{
						vehflymodeSpeed += 0.02f;
					}
				}
				if (isPress(Dpad_Left))
				{
					if (vehflymodeSpeed < 0.0f)
					{
						vehflymodeSpeed = 10.0f;
					}
					else
					{
						vehflymodeSpeed -= 0.02f;
					}
				}
				int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true);

				if (isPress(Button_R2))
				{
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);
					ApplyForce(vehicle, 0, 1.2 * vehflymodeSpeed, 0.2, 0, 0, 0);
				}

				if (isPress(Button_L1))
				{
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);
					ApplyForce(vehicle, 0, 0, -0.5 * vehflymodeSpeed, 0, 0, 0);
				}

				if (isPress(Button_R1))
				{
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);
					ApplyForce(vehicle, 0, 0, 0.5 * vehflymodeSpeed, 0, 0, 0);

				}

				if (Analog(LeftAnalogX) > Centered) //right
				{
					Heading = ENTITY::GET_ENTITY_HEADING(vehicle);
					ENTITY::SET_ENTITY_HEADING(vehicle, Heading - 3.0f);
				}
				else if (Analog(LeftAnalogX) < Centered) //left
				{
					Heading = ENTITY::GET_ENTITY_HEADING(vehicle);
					ENTITY::SET_ENTITY_HEADING(vehicle, Heading + 3.0f);
				}
				else if (!isPress(Button_R2) && !isPress(Button_L1) && !isPress(Button_R1))
				{
					Heading = ENTITY::GET_ENTITY_HEADING(vehicle);
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, true);
					ENTITY::SET_ENTITY_HEADING(vehicle, Heading);
				}
				else if (Analog(LeftAnalogX) == Centered)
				{
					ENTITY::SET_ENTITY_HEADING(vehicle, Heading);
				}

				if (isPressed(Button_R3))
				{
					ToggleCollisionEntity(vehicle, true);
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);
					VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true);
					vehflymode1 = false;
				}
			}
			else
			{
				drawText("~b~L3   ~w~Start Noclip", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, true, false);
				if (isPressed(Button_L3))
				{
					int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
					ToggleCollisionEntity(vehicle, false);
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, true);
					vehflymode1 = true;
				}
			}
		}
		else
		{
			drawText("Please drive the vehicle.", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, true, false);
		}
	}

	/*if (EQMOD)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
		{
			if (EQMODTimer < GAMEPLAY::GET_GAME_TIMER())
			{
				Random11 = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0, EQBGBLK.SizeX - 0.05f);
				Random2 = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0, EQBGBLK.SizeX - 0.05f);
				EQMODTimer = GAMEPLAY::GET_GAME_TIMER() + 100;
			}

			GRAPHICS::DRAW_RECT(EQBGBLK.Lx, EQBGBLK.Ly, EQBGBLK.SizeX, EQBGBLK.SizeY, 0, 0, 0, 255);
			GRAPHICS::DRAW_RECT(EQMain1.Lx, EQMain1.Ly, EQMain1.SizeX, EQMain1.SizeY, 220, 220, 220, 180);
			GRAPHICS::DRAW_RECT(EQMain1.Lx, EQMain1.Ly + PlusEQMain2, EQMain1.SizeX, EQMain1.SizeY, 220, 220, 220, 180);

			GRAPHICS::DRAW_RECT(0.351f + (Random11 / 2.0f), EQMain1.Ly, Random11, EQMain1.SizeY, 0, 191, 255, 180);
			GRAPHICS::DRAW_RECT(0.351f + (Random2 / 2.0f), EQMain1.Ly + PlusEQMain2, Random2, EQMain1.SizeY, 0, 191, 255, 180);

			drawText("L", 0, PixelX(Menu_X + 1) - PlusLRTextX, PixelY(0) + PlusLRTextY, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("L", 0, PixelX(Menu_X - 1) - PlusLRTextX, PixelY(0) + PlusLRTextY, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("L", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0 + 1) + PlusLRTextY, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("L", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0 - 1) + PlusLRTextY, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("L", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0) + PlusLRTextY, TextSizeLR, TextSizeLR, 240, 240, 240, 255, true, false, false);

			drawText("R", 0, PixelX(Menu_X + 1) - PlusLRTextX, PixelY(0) + PlusLRTextY2, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("R", 0, PixelX(Menu_X - 1) - PlusLRTextX, PixelY(0) + PlusLRTextY2, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("R", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0 + 1) + PlusLRTextY2, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("R", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0 - 1) + PlusLRTextY2, TextSizeLR, TextSizeLR, 0, 191, 255, 180, true, false, false);
			drawText("R", 0, PixelX(Menu_X) - PlusLRTextX, PixelY(0) + PlusLRTextY2, TextSizeLR, TextSizeLR, 240, 240, 240, 255, true, false, false);
		}
	}
*/
	if (isHydroJump)
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		drawText("~b~R1 ~w~Jump", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
		if (isPressed(Button_R1))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
			{
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle))
				{
					ApplyForce(vehicle, 0, 0.3, hydro, 0, 0, 0);
				}
			}
		}
	}
	if (isHydroJump2)
	{
		drawText("~b~R1 ~w~Jump", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
		int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

		if (isPressed(Button_R1))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
			{
				ApplyForce(vehicle, 0, 0.3, hydro, 0, 0, 0);
			}
		}
	}
	if (BAIKUKUU)
	{
		strcpy(ParachuteText, "Speed : ");
		strcat(ParachuteText, FtoS(CarJUMP, 100));
		drawText(ParachuteText, 1, 0.3, 0.150, 0.4, 0.4, 255, 255, 0, 255, true, false);

		int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		HelpTextDraw("~b~R1 ~w~飛ぶ");
		HelpTextDraw("~b~右 ~w~上げる");
		HelpTextDraw("~b~左 ~w~下げる");

		if (isPress(Button_R1))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
			{
					ApplyForce(vehicle, 0, 0, CarJUMP, 0, 0, 0);
			}
		}
		if (PED::GET_VEHICLE_PED_IS_IN)
		{
			ButtonDisable(Dpad_Left);
			ButtonDisable(Dpad_Right);
			if (isPress(Dpad_Right, true))
			{
				if (CarJUMP > 10.0f)
				{
					CarJUMP = 0.0f;
				}
				else
				{
					CarJUMP += 0.1f;
				}
			}

			if (isPress(Dpad_Left, true))
			{
				if (CarJUMP < 0.0f)
				{
					CarJUMP = 10.0f;
				}
				else
				{
					CarJUMP -= 0.1f;
				}
			}
		}
	}
	if (VehicleBoostStop)
	{
		drawText("~b~L3 ~w~Boost", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
		drawText("~b~R3 ~w~Stop", 0, 0.3, 0.125, 0.4, 0.4, 255, 128, 255, 255, false, false);
		int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		if (isPressed(Button_L3))
		{
			float Speed222 = ENTITY::GET_ENTITY_SPEED(veh) + 100.0f;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, Speed222);
		}
		if (isPressed(Button_R3))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0);
		}
	}

	if (Neongreen1)
	{
		DrawNeons(123, 255, 0);

	}
	if (Purple1)
	{
		DrawNeons(159, 19, 214);

	}
	if (Blue1)
	{
		DrawNeons(19, 123, 214);

	}
	if (Pink1)
	{
		DrawNeons(214, 19, 100);

	}
	if (Red1)
	{
		DrawNeons(214, 19, 19);

	}
	if (Orange1)
	{
		DrawNeons(214, 117, 19);

	}
	if (Yallow1)
	{
		DrawNeons(228, 250, 32);
	}
	if (Random1)
	{
		DrawNeons(228, 250, 32);
		DrawNeons(214, 117, 19);
		DrawNeons(214, 19, 19);
		DrawNeons(214, 19, 100);
		DrawNeons(19, 123, 214);
		DrawNeons(159, 19, 214);
		DrawNeons(123, 255, 0);
	}
	if (rainbowneon)
	{
		if (Carneon2 == 0)
		{
			Carneon.B++;
			if (Carneon.B == 255)
				Carneon2 = 1;
		}
		else if (Carneon2 == 1)
		{
			Carneon.R--;
			if (Carneon.R == 0)
				Carneon2 = 2;
		}
		else if (Carneon2 == 2)
		{
			Carneon.G++;
			if (Carneon.G == 255)
				Carneon2 = 3;
		}
		else if (Carneon2 == 3)
		{
			Carneon.B--;
			if (Carneon.B == 0)
				Carneon2 = 4;
		}
		else if (Carneon2 == 4)
		{
			Carneon.R++;
			if (Carneon.R == 255)
				Carneon2 = 5;
		}
		else if (Carneon2 == 5)
		{
			Carneon.G--;
			if (Carneon.G == 0)
				Carneon2 = 0;
		}

		Redneon = Carneon.R;
		Greenneon = Carneon.G;
		Blueneon = Carneon.B;
	}

	if (neoncustum)
	{
		DrawNeons(Redneon, Greenneon, Blueneon);
	}

	if (DriveONwall)
	{
		drawText("~b~X  ~w~Stop", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
		drawText("~b~R2 ~w~Boost", 0, 0.3, 0.125, 0.4, 0.4, 255, 128, 255, 255, false, false);
		drawText("~b~L2 ~w~Back", 0, 0.3, 0.150, 0.4, 0.4, 255, 128, 255, 255, false, false);

		drawText("~b~R1 ~w~Change to WallMode", 0, 0.3, 0.175, 0.4, 0.4, 255, 128, 255, 255, false, false);
		int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		Vector3 WallDrive = { DriveOnWallx, DriveOnWallxy, DriveOnWallxz };
		Vector3 Wallrot = { DriveOnWallxrotx, DriveOnWallxroty, DriveOnWallxrotz };
		if (isPress(Button_X))
		{
			DriveOnWallxz = 0.0f;
			ENTITY::FREEZE_ENTITY_POSITION(veh, true);
		}

		if (isPress(Button_R2))
		{
			DriveOnWallxy = 0.15f;
			ENTITY::FREEZE_ENTITY_POSITION(veh, false);
		}
		else if (isPress(Button_L2))
		{
			DriveOnWallxy = -0.15f;
			DriveOnWallxz = 0.0f;
			ENTITY::FREEZE_ENTITY_POSITION(veh, false);
		}
		else
		{

			DriveOnWallxy = 0.0f;
		}

		if (isPress(Button_R1))
		{
			if (!isPress(Button_X))
			{
				DriveOnWallxz = 0.5f;
			}
			DriveOnWallxroty = 0.5f;
		}
		else
		{
			if (!isPress(Button_X))
			{
				DriveOnWallxz = -0.5f;
			}
			DriveOnWallxroty = 0.0f;
		}
		ApplyForce(veh, WallDrive.x, WallDrive.y, WallDrive.z, Wallrot.x, Wallrot.y, Wallrot.z);
	}

	if (neonmodcar)
	{
		if (Start)
		{
			int NeonWhitelight = GAMEPLAY::GET_HASH_KEY("prop_wall_light_05a");

			if (!STREAMING::HAS_MODEL_LOADED(NeonWhitelight))
				STREAMING::REQUEST_MODEL(NeonWhitelight);

			Vector3 Pos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
			int NeonSelectedCar = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

			if (NeonSelectedCar == 0)
				neonmodcar = false;
			if (!Start2)
			{
				if (!ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat))
					NeonWhitelightCreat = OBJECT::CREATE_OBJECT(NeonWhitelight, Pos.x, Pos.y, Pos.z, true, true, true);

				if (!ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat2))
					NeonWhitelightCreat2 = OBJECT::CREATE_OBJECT(NeonWhitelight, Pos.x, Pos.y, Pos.z, true, true, true);

				if (ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat) && ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat2))
				{
					NotifyDown("存在");
					ENTITY::ATTACH_ENTITY_TO_ENTITY(NeonWhitelightCreat, NeonSelectedCar, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(NeonWhitelightCreat2, NeonSelectedCar, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1);
					if (ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(NeonWhitelightCreat) && ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(NeonWhitelightCreat2))
						Start2 = true;
				}

			}
		}

	}

	if (neonmodcar1)
	{
		if (Start1)
		{
			int NeonWhitelight1 = GAMEPLAY::GET_HASH_KEY("prop_air_lights_05a");

			if (!STREAMING::HAS_MODEL_LOADED(NeonWhitelight1))
				STREAMING::REQUEST_MODEL(NeonWhitelight1);

			Vector3 Pos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
			int NeonSelectedCar = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

			if (NeonSelectedCar == 0)
				neonmodcar1 = false;
			if (!Start3)
			{
				if (!ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat1))
					NeonWhitelightCreat1 = OBJECT::CREATE_OBJECT(NeonWhitelight1, Pos.x, Pos.y, Pos.z, true, true, true);

				if (!ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat3))
					NeonWhitelightCreat3 = OBJECT::CREATE_OBJECT(NeonWhitelight1, Pos.x, Pos.y, Pos.z, true, true, true);

				if (!ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat4))
					NeonWhitelightCreat4 = OBJECT::CREATE_OBJECT(NeonWhitelight1, Pos.x, Pos.y, Pos.z, true, true, true);

				if (ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat1) && ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat3) && ENTITY::DOES_ENTITY_EXIST(NeonWhitelightCreat4))
				{
					NotifyDown("存在");
					ENTITY::ATTACH_ENTITY_TO_ENTITY(NeonWhitelightCreat1, NeonSelectedCar, 0, 0, 0, 0.6000, 90.0000, 0, 0, 1, 0, 0, 0, 2, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(NeonWhitelightCreat3, NeonSelectedCar, 0, 0, 0, 0.6000, 90.0000, 0, 0, 1, 0, 0, 0, 2, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(NeonWhitelightCreat4, NeonSelectedCar, 0, 0, 0, 0.6000, 90.0000, 0, 0, 1, 0, 0, 0, 2, 1);

					if (ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(NeonWhitelightCreat1) && ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(NeonWhitelightCreat3) && ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(NeonWhitelightCreat4))
						Start3 = true;
				}

			}
		}

	}

	if (maincolor)
	{
		VehicleCustom(true);
	}

	if (subcolor)
	{
		VehicleCustom(false, true);
	}

	if (smokecolor)
	{
		VehicleCustom(false, false, true);
	}

	if (IsGetFlag)
	{
		for (int i = 0; i < 0x13000; i++)
		{
			if (PS3::ReadInt32(0x411ED000 + (4 * i)) == 0x5D0AAC8F)
			{
				AddressHandling = 0x411ED000 + (4 * i);
				GettingQue = "取得できたよ！";
				IsGetFlag = false;
				break;
			}
			else
			{
				GettingQue = "取得できなかったよ！";
			}
		}
		IsGetFlag = false;
	}

	if (Getter)
	{
		for (int i = 0; i < 0x13000; i++)
		{
			if (PS3::ReadInt32(AddressHandling + (4 * i)) == MycaraddressTarget)
			{
				MyCarAddress = AddressHandling + (4 * i);
				GettingQue = "取得できたよ！ v2";
				Getter = false;
				break;
			}
			else
			{
				GettingQue = "取得できなかったよ！ v2";
			}
		}
		Getter = false;
	}

	//if (IsGetFlag2)
	//{
	//	VehicleMetaHandling = FindPattern(0x402B0000, 0x10000, (BYTE*)NinefByte, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	//	//}
	//	//VehicleCheats::VehicleMetaHandling = AddressZ;
	//	if (VehicleMetaHandling == 0)
	//	{
	//		GettingQue2 = "取得できなかったよ！";
	//	}
	//	else
	//	{
	//		GettingQue2 = "取得できたよ！";
	//	}

	//	IsGetFlag2 = false;
	//}

	if (testESP)
	{
		float ScreenX;
		float ScreenY;
		Ped Closest;
		const int numElements = 50;
		const int arrSize = numElements * 2 + 2;
		int veh[arrSize];
		veh[0] = numElements;
		int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, 0);
		if (veh != NULL)
		{
			for (int i = 0; i < count; i++)
			{
				Vector3 handleCoords = get_entity_coords_orig(veh[i], 1);
				UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &ScreenX, &ScreenY);
				if (!(ScreenX <= 0.2 | ScreenX >= 0.8 | ScreenY <= 0.2 | ScreenY >= 0.8))
				{
					DrawSprite("ironhud", "grime7", ScreenX, ScreenY, 0.7, 0.7, 0, 255, 255, 255, 255);
				}
			}
		}
	}

	if (SpeedMeter)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) // if you'r in a Car or ... Speedometer shows up!
		{
			float speed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) * 3.3;// this transfers the speed to Float rotate
			speed = speed + 1;
			if (speed > 260)
			{
				speed = 260;
			}
			DrawSprite("speedometers", "off_road_race_icon", METER1, METER2, METER3, METER4, 0, 255, 255, 255, 255);//speedometer background
			DrawSprite("speedometers", "last_team_standing_icon", METER1, METER2, METER3, METER4, speed, 255, 255, 255, 255);//Speedometer needle 
		}
	}

	if (HulkMod)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(HulkEgg))
		{
			HulkEgg = Create_Map_int("prop_ld_test_01");
			ENTITY::SET_ENTITY_VISIBLE(HulkEgg, false);
		}
		if (isHulk)
		{
			Vector3 vector = GET_GAMEPLAY_CAM_ROT_orig(2);
			drawText("HulkJump : R1", 1, 0.5, 0.05, 0.4, 0.4, 255, 255, 255, 255, true, false);
			drawText("GetObject : L2", 1, 0.5, 0.075, 0.4, 0.4, 255, 255, 255, 255, true, false);
			drawText("ObjectShot : R2", 1, 0.5, 0.1, 0.4, 0.4, 255, 255, 255, 255, true, false);
			drawText("EndHulkMod : R3", 1, 0.5, 0.125, 0.4, 0.4, 255, 255, 255, 255, true, false);
			if (!IsGet)
			{
				if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2))
				{
					if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target2))
					{
						for (int i = 0; i < 16; i++)
						{
							HulkL2Flag = true;
							if (Target2 == PLAYER::GET_PLAYER_PED(i))
							{
								HulkL2Flag = false;
							}
						}

					}

				}
				if (HulkL2Flag)
				{

					RequestNetworkControl(Target2);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target2, 1, 1);
					if (ENTITY::IS_ENTITY_A_PED(Target2))
					{
						if (!ENTITY::IS_ENTITY_ATTACHED(Target2))
						{
							if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "anim@heists@narcotics@trash", "walk", 3))
							{
								TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "anim@heists@narcotics@trash", "walk", 49);
							}
							else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "anim@heists@narcotics@trash", "walk", 3))
							{
								ENTITY::SET_ENTITY_ALPHA(Target2, 100, true);
								ATTACH_ENTITY_TO_ENTITY(Target2, PLAYER::PLAYER_PED_ID(), 0xdead, 0.5, 0, -0.7, 0, 0, 0);
								//ENTITY::SET_ENTITY_HEALTH(Target2, 0);
								TASK_PLAY_ANIM(Target2, "amb@code_human_cower_stand@male@base", "base", 49);
								isPed = true;
								IsGet = true;
								HulkL2Flag = false;
							}
						}
					}
					else if (ENTITY::IS_ENTITY_A_VEHICLE(Target2))
					{
						RequestNetworkControl(Target2);
						if (!ENTITY::IS_ENTITY_ATTACHED(Target2))
						{
							if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3))
							{
								TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 49);
							}
							else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3))
							{
								RequestNetworkControl(Target2);
								ENTITY::SET_ENTITY_ALPHA(Target2, 100, true);
								ATTACH_ENTITY_TO_ENTITY(Target2, PLAYER::PLAYER_PED_ID(), 0x0, 0, 0, 1.7, 0, 0, 0);
								IsGet = true;
								HulkL2Flag = false;
							}
						}
					}
				}
				if (HulkR1Flag)
				{
					if (!ENTITY::DOES_ENTITY_EXIST(HulkEgg))
					{
					}
					else
					{
						if (!ENTITY::IS_ENTITY_ATTACHED(PLAYER::PLAYER_PED_ID()))
						{
							ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), HulkEgg, 0, 0, 0, 1.5);
						}
						else
						{
							ENTITY::FREEZE_ENTITY_POSITION(HulkEgg, false);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(HulkEgg, 1, 1);
							RequestNetworkControl(HulkEgg);
							ApplyForce(HulkEgg, 0, 5, 20);
							ApplyForce(HulkEgg, 0, 5, 20);
							HulkR1Flag = false;
						}
					}
				}
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R1))//R1
				{
					HulkR1Flag = true;
				}
				if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
				{
					if (vector.x < 0)
					{
						ApplyForce(HulkEgg, 0, 0, -2);
					}
					else
					{
						ApplyForce(HulkEgg, 0, 0, 5);
					}
					ENTITY::SET_ENTITY_ROTATION(HulkEgg, 0, vector.y, vector.z, 2, true);
					AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), 1.0, 0, 0);
					ENTITY::APPLY_FORCE_TO_ENTITY(HulkEgg, true, 0, 3, 0, 0, 0, 0, false, true, true, true, false, true);
					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "dead@fall", "dead_fall_up", 3))
					{
						TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "dead@fall", "dead_fall_up", 1.0f);
					}
				}
				else
				{
					if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "dead@fall", "dead_fall_up", 3))
					{
						Freeze(PLAYER::PLAYER_PED_ID());
					}
					if (ENTITY::DOES_ENTITY_EXIST(HulkEgg))
					{
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(HulkEgg, 1, 1);
						RequestNetworkControl(HulkEgg);
						DeleteEntity(HulkEgg);
					}
				}
			}
			else
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), 0xA2719263);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), 0xA2719263, false);
				if (!IsShooting && !IsDrop)
				{
					if (isPed)
					{
						if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R2))
						{
							TimeoutHulk = GAMEPLAY::GET_GAME_TIMER() + 1600;
							IsShooting = true;
						}
					}
					else
					{
						if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R2))
						{
							TimeoutHulk = GAMEPLAY::GET_GAME_TIMER() + 1600;
							IsShooting = true;
						}
					}
				}
				else if (IsShooting)
				{
					if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3) || ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "anim@heists@narcotics@trash", "walk", 3))
					{
						Freeze(PLAYER::PLAYER_PED_ID());
					}
					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "weapons@projectile@", "throw_m_fb_stand", 3))
					{
						AI::SET_ANIM_RATE(PLAYER::PLAYER_PED_ID(), 2.0, 0, 0);
						TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "weapons@projectile@", "throw_m_fb_stand", 49);
					}
					else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "weapons@projectile@", "throw_m_fb_stand", 3))
					{
						ENTITY::DETACH_ENTITY(Target2, 0, 0);
						ENTITY::SET_ENTITY_ALPHA(Target2, 255, true);
						RequestNetworkControl(Target2);
						if (isPed)
						{
							Freeze(Target2);//TEST
							ApplyForce(Target2, 0, 10, 0);
							//	ApplyForce(Target2, 0, 0.5, 0);
						}
						else
						{
							ApplyForce(Target2, 0, 10 * -1, 0);
							//	ApplyForce(Target2, 0, 0.5 * -1, 0);
						}

						//ApplyForce(Target2, 0, ApplySpeed * -1, 0);
						//ApplyForce(Target2, 0, ApplySpeed * -1, 0);
						if (TimeoutHulk < GAMEPLAY::GET_GAME_TIMER())
						{
							Freeze(PLAYER::PLAYER_PED_ID());
							Target2 = 0;
							isPed = false;
							IsGet = false;
							IsShooting = false;
						}
					}
				}
			}
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R3))
			{
				IsDrop = false;
				IsGet = false;
				isHulk = false;
				IsShooting = false;
			}
		}
		else
		{
			drawText("HulkMod : L3", 1, 0.5, 0.05, 0.4, 0.4, 255, 255, 255, 255, true, false);
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L3))
			{
				IsGet = false;
				isHulk = true;
			}
		}
	}

	if (DragonFireSpawn)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(Core))
		{
			Core = Create_Map_int("prop_ld_test_01");
		}
		else
		{
			if (ENTITY::IS_ENTITY_VISIBLE(Core))
			{
				ENTITY::SET_ENTITY_VISIBLE(Core, false);
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Body))
		{
			Body = Create_Map_int("prop_tool_box_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Body))
			{
				//BodyFlag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Body, Core, 0x0, 0, 0, 0.60, 180, 0, 90);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Body, Core, 0x0, 0.0000, 0.0000, 1.0000, -180.0000, 0.0000, 90.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Body, true);
			}
			else
			{
				BodyFlag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(RedLamp))
		{
			RedLamp = Create_Map_int("hei_prop_heist_thermite_flash");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(RedLamp))
			{
				//RedLampFlag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(RedLamp, Core, 0x0, 0.1f, 0.44f, 0.81f, 0.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(RedLamp, Core, 0x0, 0.0000, -0.3500, 0.8500, 0.0000, -90.0000, 90.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(RedLamp, true);
			}
			else
			{
				RedLampFlag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Stick))
		{
			Stick = Create_Map_int("prop_cs_bar");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Stick))
			{
				//StickFlag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Stick, Core, 0x0, -0.66f, -0.80f, 1.4f, 150.0f, 20.50f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Stick, Core, 0x0, 0.4300, -0.4700, 1.1660, 45.0000, 51.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Stick, true);
			}
			else
			{
				StickFlag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Stick2))
		{
			Stick2 = Create_Map_int("prop_cs_bar");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Stick2))
			{
				//Stick2Flag = false;
				//	ATTACH_ENTITY_TO_ENTITY_1(Stick2, Core, 0x0, -0.66f, 0.79f, 1.4f, 150.0f, 349.5f, 80.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Stick2, Core, 0x0, -0.4300, -0.4700, 1.1660, 45.0000, -51.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Stick2, true);
			}
			else
			{
				Stick2Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Stick3))
		{
			Stick3 = Create_Map_int("prop_cs_bar");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Stick3))
			{
				//Stick3Flag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Stick3, Core, 0x0, 0.66f, 0.79f, 1.4f, 150.0f, 349.50f, 320.25f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Stick3, Core, 0x0, -0.4300, 0.4700, 1.1660, -45.0000, -51.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Stick3, true);
			}
			else
			{
				Stick3Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Stick4))
		{
			Stick4 = Create_Map_int("prop_cs_bar");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Stick4))
			{
				//Stick4Flag = false;
				//	ATTACH_ENTITY_TO_ENTITY_1(Stick4, Core, 0x0, 0.69f, -0.81f, 1.4f, 150.0f, 20.50f, 251.40f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Stick4, Core, 0x0, 0.4300, 0.4700, 1.1660, -45.0000, 51.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Stick4, true);
			}
			else
			{
				Stick4Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Propeller))
		{
			Propeller = Create_Map_int("prop_cartwheel_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Propeller))
			{
				//PropellerFlag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Propeller, Core, 0x0, -0.60f, 0.80f, 1.16f, 180.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Propeller, Core, 0x0, -0.8000, 0.6000, 1.3000, 0.0000, 0.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Propeller, true);
			}
			else
			{
				PropellerFlag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Propeller2))
		{
			Propeller2 = Create_Map_int("prop_cartwheel_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Propeller2))
			{
				//Propeller2Flag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Propeller2, Core, 0x0, 0.66f, 0.80f, 1.16f, 180.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Propeller2, Core, 0x0, -0.8000, -0.7000, 1.3000, 0.0000, 0.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Propeller2, true);
			}
			else
			{
				Propeller2Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Propeller3))
		{
			Propeller3 = Create_Map_int("prop_cartwheel_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Propeller3))
			{
				//Propeller3Flag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Propeller3, Core, 0x0, 0.66f, -0.80f, 1.16f, 180.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Propeller3, Core, 0x0, 0.8000, -0.7000, 1.3000, 0.0000, 0.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Propeller3, true);
			}
			else
			{
				Propeller3Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(Propeller4))
		{
			Propeller4 = Create_Map_int("prop_cartwheel_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(Propeller4))
			{
				//Propeller4Flag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Propeller4, Core, 0x0, -0.66f, -0.80f, 1.16f, 180.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Propeller4, Core, 0x0, 0.8000, 0.7000, 1.3000, 0.0000, 0.0000, 0.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(Propeller4, true);
			}
			else
			{
				Propeller4Flag = true;
			}
		}

		if (!ENTITY::DOES_ENTITY_EXIST(minigun01))
		{
			minigun01 = Create_Map_int("prop_minigun_01");
		}
		else
		{
			if (!ENTITY::IS_ENTITY_ATTACHED(minigun01))
			{
				//Propeller4Flag = false;
				//ATTACH_ENTITY_TO_ENTITY_1(Propeller4, Core, 0x0, -0.66f, -0.80f, 1.16f, 180.0f, 0.0f, 90.0f);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(minigun01, Core, 0x0, 0.0000, 0.7000, 0.9000, 0.0000, 0.0000, 90.0000, 1, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE(minigun01, true);
			}
			else
			{
				minigun01flag = true;
			}
		}
		if (BodyFlag && RedLampFlag && StickFlag && Stick2Flag && Stick3Flag && Stick4Flag && PropellerFlag && Propeller2Flag && Propeller3Flag && Propeller4Flag && minigun01flag)
		{
			NotifyDown("Start DragonFire!");
			DragonFireEnable = true;
			DragonFireMovement = true;
			DragonFireSpawn = false;
		}

	}

	if (DragonFireEnable)
	{
		RequestNetworkControl(Core);
		RequestNetworkControl(Body);
		RequestNetworkControl(RedLamp);
		RequestNetworkControl(Stick);
		RequestNetworkControl(Stick2);
		RequestNetworkControl(Stick3);
		RequestNetworkControl(Stick4);
		RequestNetworkControl(Propeller);
		RequestNetworkControl(Propeller2);
		RequestNetworkControl(Propeller3);
		RequestNetworkControl(Propeller4);
		//Propeller
		HEADING2 = HEADING2 + 2;
		//ENTITY::SET_ENTITY_HEADING(Propeller, HEADING);
		//ENTITY::SET_ENTITY_HEADING(Propeller2, HEADING);
		//ENTITY::SET_ENTITY_HEADING(Propeller3, HEADING);
		//ENTITY::SET_ENTITY_HEADING(Propeller4, HEADING);
		//ENTITY::SET_ENTITY_ROTATION(Propeller, 0, 0, Rotation.z, 0, 0);
		//ENTITY::SET_ENTITY_ROTATION(Propeller2, 0, 0, Rotation.z, 0, 0);
		//ENTITY::SET_ENTITY_ROTATION(Propeller3, 0, 0, Rotation.z, 0, 0);
		//ENTITY::SET_ENTITY_ROTATION(Propeller4, 0, 0, Rotation.z, 0, 0);
		ATTACH_ENTITY_TO_ENTITY(Propeller, Core, 0x0, -0.8000, 0.6000, 1.3000, 0.0000, 0.0000, HEADING2);
		//ENTITY::SET_ENTITY_VISIBLE(Propeller, true);
		ATTACH_ENTITY_TO_ENTITY(Propeller2, Core, 0x0, -0.8000, -0.7000, 1.3000, 0.0000, 0.0000, HEADING2);
		//ENTITY::SET_ENTITY_VISIBLE(Propeller2, true);
		ATTACH_ENTITY_TO_ENTITY(Propeller3, Core, 0x0, 0.8000, -0.7000, 1.3000, 0.0000, 0.0000, HEADING2);
		//ENTITY::SET_ENTITY_VISIBLE(Propeller3, true);
		ATTACH_ENTITY_TO_ENTITY(Propeller4, Core, 0x0, 0.8000, 0.7000, 1.3000, 0.0000, 0.0000, HEADING2);
		//ENTITY::SET_ENTITY_VISIBLE(Propeller4, true);
		ENTITY::FREEZE_ENTITY_POSITION(Core, true);

	}

	if (DragonFireMovement)
	{
		drawText("~b~Dpad Up    ~w~Call DragonFire", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);
		drawText("~b~Dpad Right ~w~Change to MoveMode", 0, 0.3, 0.125, 0.4, 0.4, 255, 128, 255, 255, false, false);

		if (isPressed(Dpad_Up))
		{
			CamCoord = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_COORDS(Core, CamCoord.x, CamCoord.y, CamCoord.z, 0, 0, 0, true);
		}

		if (isPressed(Dpad_Right))
		{
			if (!DragonFireCamera > 0)
			{
				DragonFireCamera = CAM::CREATE_CAMERA1(GAMEPLAY::GET_HASH_KEY("DEFAULT_SCRIPTED_CAMERA"), false);
				//CAM::ATTACH_CAM_TO_PED_BONE1(DragonFireCamera, Core, 0x0, 0.3, 0, 0.5, false);	
				CamCoord = get_entity_coords_orig(Core, true);

				CAM::SET_CAM_COORD(DragonFireCamera, CamCoord.x, CamCoord.y, CamCoord.z + 1.3);
				CAM::SET_CAM_ACTIVE1(DragonFireCamera, true);
				CAM::RENDER_SCRIPT_CAMS1(1, 0, 3000, 1, 0);

			}
			SelectedTarget = false;
			TargetAttach = false;
			DragonFireFirstPerson = true;
			DragonFireAuto = false;
		}

		if (isPressed(Dpad_Left))
		{
			CAM::DESTROY_CAM1(DragonFireCamera, 0);
			CAM::RENDER_SCRIPT_CAMS1(0, 0, 3000, 1, 0);
			DragonFireCamera = 0;
			DragonFireFirstPerson = false;
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
			DragonFireAuto = false;
			SelectedTarget = false;
			TargetAttach = false;
		}

		if (isPressed(Button_L2))
		{
			DragonFireAuto = true;
			SelectedTarget = false;
			TargetAttach = false;
		}
		VVVV = get_entity_coords_orig(Core, 2);
		CCCC = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 2);
		GRAPHICS::DRAW_LINE(VVVV.x, VVVV.y, VVVV.z, CCCC.x, CCCC.y, CCCC.z, 255, 0, 0, 255);
	}

	if (DragonFireFirstPerson)
	{
		GetCamRot = GET_GAMEPLAY_CAM_ROT_orig(2);
		CamRot = get_entity_rotation_orig(Core, true);
		CamCoord = get_entity_coords_orig(Core, true);
		RequestNetworkControl(Core);
		RequestNetworkControl(Body);
		RequestNetworkControl(RedLamp);
		RequestNetworkControl(Stick);
		RequestNetworkControl(Stick2);
		RequestNetworkControl(Stick3);
		RequestNetworkControl(Stick4);
		RequestNetworkControl(Propeller);
		RequestNetworkControl(Propeller2);
		RequestNetworkControl(Propeller3);
		RequestNetworkControl(Propeller4);

		if (Analog(189) > 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 0, 5 * -1, 0);
		}

		if (Analog(189) < 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 0, 5, 0);
		}

		if (Analog(188) > 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 5, 0, 0);
		}

		if (Analog(188) < 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 5 * -1, 0, 0);
		}

		if (Analog(190) > 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			GetCamRot.z = GetCamRot.z - 5;
			if (GetCamRot.z > 360)
			{
				GetCamRot.z = 0;
			}
			if (GetCamRot.z < -360)
			{
				GetCamRot.z = 0;
			}
		}
		if (Analog(190) < 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			GetCamRot.z = GetCamRot.z + 5;
			if (GetCamRot.z > 360)
			{
				GetCamRot.z = 0;
			}
			if (GetCamRot.z < -360)
			{
				GetCamRot.z = 0;
			}
		}
		if (Analog(191) > 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			GetCamRot.x = GetCamRot.x - 5;
			if (GetCamRot.x > 90)
			{
				GetCamRot.x = 90;
			}
			if (GetCamRot.x < -90)
			{
				GetCamRot.x = -90;
			}
		}
		if (Analog(191) < 127)
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			GetCamRot.x = GetCamRot.x + 5;
			if (GetCamRot.x > 90)
			{
				GetCamRot.x = 90;
			}
			if (GetCamRot.x < -90)
			{
				GetCamRot.x = -90;
			}
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 0, 0, 5);
		}
		else if (CONTROLS::IS_CONTROL_PRESSED(0, Button_B))
		{
			ENTITY::FREEZE_ENTITY_POSITION(Core, false);
			ApplyForce(Core, 0, 0, -5);
		}

		if (isPress(Button_L2))
		{
			ENTITY::ATTACH_ENTITY_TO_ENTITY(minigun01, Core, 0x0, 0.0000, 0.7000, 0.9000, HEADING2, 0.0000, 90.0000, 1, 0, 0, 0, 2, 1);
			VehicleWeaponsFunctionN2(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_BUZZARD"));
		}
		else if (isPress(Button_R2))
		{
			ENTITY::ATTACH_ENTITY_TO_ENTITY(minigun01, Core, 0x0, 0.0000, 0.7000, 0.9000, HEADING2, 0.0000, 90.0000, 1, 0, 0, 0, 2, 1);
			if (IronManTimer < GAMEPLAY::GET_GAME_TIMER())
			{
				VehicleWeaponsFunctionN2(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"));
				IronManTimer = GAMEPLAY::GET_GAME_TIMER() + 400;
			}
		}

		CAM::SET_CAM_ROT1(DragonFireCamera, GetCamRot.x, 0, GetCamRot.z, 2);
		CAM::SET_CAM_COORD(DragonFireCamera, CamCoord.x, CamCoord.y, CamCoord.z + 1.3);
		ENTITY::SET_ENTITY_ROTATION(Core, GetCamRot.x, 0, GetCamRot.z, 0, 0);
		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
		//ENTITY::FREEZE_ENTITY_POSITION(Core, true);
	}

	/*if (AntiFreezeObject)
	{
		Vector3 Loc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
		int obj = OBJECT::_GET_CLOSEST_OBJECT_OF_TYPE(Loc.x, Loc.y, Loc.z, 50.0f, -1268267712, false, false, true);

		char* playernamefromentity = PLAYER::GET_PLAYER_NAME(NETWORK::NETWORK_GET_ENTITY_FROM_NETWORK_ID(obj));


		if (ENTITY::DOES_ENTITY_EXIST(obj))
		{
				char buf[512];
				snprintf(buf, 512, "感知: %s がUFOをつけてきた", playernamefromentity);
				NotifyDown(buf);
				DeleteEntH4X(obj);
		}
	}*/


	if (DragonFireAuto)
	{
		if (!SelectedTarget)
		{
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &FireAutoTarget))
			{
				if (ENTITY::DOES_ENTITY_EXIST(FireAutoTarget))
				{
					if (!ENTITY::IS_ENTITY_ATTACHED(FireAutoTarget))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(FireAutoTarget))
						{
							ATTACH_ENTITY_TO_ENTITY(Core, FireAutoTarget, 0x0, 2, 2, 1.5, -40, 0, 120);
							DragonFireAttacking = true;
						}
						else
						{
							Vector3 MyCod = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
							ENTITY::SET_ENTITY_COORDS(Core, MyCod.x, MyCod.y, MyCod.z + 2, 0, 0, 0, 1);
							TargetCoords = get_entity_coords_orig(FireAutoTarget, 1);
							//DragonFireCoords = get_entity_coords_orig(Core, 1);
							MyHeading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
							//if (MyHeading != 0)
							//{
							//Vector3 Direction = TurrentTrig(DragonFireCoords, TargetCoords);
							ENTITY::SET_ENTITY_ROTATION(Core, 0, 0, MyHeading, 0, 0);
							NotifyDown("Targeting Object");
							SelectedTarget = true;
							TargetAttach = true;
							//}
						}
					}
				}
			}
			else
			{
				DragonFireAuto = false;
			}
		}
		else
		{
			if (TargetAttach)
			{
				TargetCoords = get_entity_coords_orig(FireAutoTarget, 1);
				DragonFireCoords = get_entity_coords_orig(Core, 1);
				//Vector3 HEADING5 = get_entity_rotation_orig(Core,2);

				//float HEADING4 = GetHeadingFromCoords(DragonFireCoords, TargetCoords) + 270;
				//ENTITY::SET_ENTITY_ROTATION(Core, 0, 0, HEADING4, 0, 0);
				float Distance = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(DragonFireCoords.x, DragonFireCoords.y, DragonFireCoords.z, TargetCoords.x, TargetCoords.y, TargetCoords.z, false);
				if (Distance > 4)
				{
					MyHeading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
					ENTITY::SET_ENTITY_ROTATION(Core, 0, 0, MyHeading, 0, 0);
					ENTITY::FREEZE_ENTITY_POSITION(Core, false);
					ApplyForce(Core, 0, 6, 0.5);
				}
				else
				{
					RequestNetworkControl(FireAutoTarget);
					ATTACH_ENTITY_TO_ENTITY(Core, FireAutoTarget, 0x0, 2, 2, 2.5, -20, 0, 120);
					ENTITY::FREEZE_ENTITY_POSITION(Core, true);
					NotifyDown("Targeted!");
					TargetAttach = false;
					DragonFireAttachedAAA = true;
					DragonFireAttacking = true;
				}
			}
			else if (DragonFireAttacking)
			{
				if (IronManTimeout < GAMEPLAY::GET_GAME_TIMER())
				{
					VehicleWeaponsFunctionN3(Core, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"));
					IronManTimeout = GAMEPLAY::GET_GAME_TIMER() + 400;
				}
			}
		}
	}
	else
	{
		FireAutoTarget = 0;
	}


	if (ShowTalking1)
	{
		int Height = 1;
		for (int i = 0; i < 16; i++)
		{
			if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i))
				Height++;
		}
		if (Height <= 1)
			Height = 0;
		float BoxHeight = PixelY(30 * Height);
		if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
		{
			if (timerdesu5 < GAMEPLAY::GET_GAME_TIMER())
			{
				timerdesu5 = GAMEPLAY::GET_GAME_TIMER() + 1;
				GRAPHICS::DRAW_RECT(PixelX(25 + 125), PixelY(45) + (BoxHeight / 2), PixelX(250), BoxHeight, 0, 0, 0, 100);//Background
			}
		}
		if (Height != 0)
			drawText("VC装着者", 0, PixelX(45), PixelY(50) + (PixelY(30) * 0), 0.5, 0.5, 255, 255, 255, 255, false);
		int Current = 1;
		for (int i = 0; i < 16; i++)
		{
			if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i))
			{
				char* Icon = "leaderboard_audio_inactive";
				drawText(PLAYER::GET_PLAYER_NAME(i), 0, PixelX(60), PixelY(50) + (PixelY(30) * Current), 0.4, 0.4, 240, 240, 240, 255, false);
				if (NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(i))
					Icon = "leaderboard_audio_mute";
				else if (NETWORK::NETWORK_IS_PLAYER_TALKING(i))
					Icon = "leaderboard_audio_3";
				DrawSprite("mpleaderboard", Icon, PixelX(45), PixelY(60) + (PixelY(30) * Current), 0.03, 0.05, 0, 255, 255, 255, 255);
				Current++;
			}
		}
	}

	if (VChyouji)
	{
		float xc = .1;
		float p = .05;
		float TextScale2 = 0.5;
		for (int i = 0; i < 16; i++)
		{
			if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i) && NETWORK::NETWORK_IS_PLAYER_TALKING(i))
			{
				char Buffer[100];
				snprintf(Buffer,100, "~y~トーク: ~b~%s", PLAYER::GET_PLAYER_NAME(i));
				drawText(Buffer, 0, .1, (p += .02), TextScale2, TextScale2, 255, 255, 255, 255, 0);
			}
			else if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i) && !NETWORK::NETWORK_IS_PLAYER_TALKING(i))
			{
				char Buffer[100];
				snprintf(Buffer, 100, "VC装着: ~g~%s", PLAYER:: GET_PLAYER_NAME(i));
				drawText(Buffer, 0, .1, (p += .02), TextScale2, TextScale2, 255, 255, 255, 255, 0);
			}
		}
	}

	if (UCAV)
	{
		drawText("~b~R2 ~w~Start UCAV(with Shoot)", 0, 0.3, 0.100, 0.4, 0.4, 255, 128, 255, 255, false, false);

		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			if (!Predator_ON2) { UCAVTimer = GAMEPLAY::GET_GAME_TIMER() + 100000; isSpawned = true; }
		}
		if (isSpawned)
		{
			if (SpawnMissile())
			{
				while (!CAM::DOES_CAM_EXIST(PreCamera2))
				{
					PreCamera2 = CAM::CREATE_CAMERA1(26379945, false);
				}
				ENTITY::SET_ENTITY_VISIBLE(PreMissile2, true);
				CAM::ATTACH_CAM_TO_ENTITY(PreCamera2, PreMissile2, 0, -1, 0.5, 1);
				CAM::SET_CAM_ACTIVE1(PreCamera2, true);
				CAM::RENDER_SCRIPT_CAMS1(true, false, 3000, true, false);
				NotifyDown("Start Script.", 500);
				Predator_ON2 = true;
				isSpawned = false;
			}
		}
		if (Predator_ON2)
		{
			CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_L1);
			CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R2);
			CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R1);
			CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R1);
			CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R2);
			CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);

			if (ENTITY::DOES_ENTITY_EXIST(FakeMissileOb))
			{
				DrawSprite("securitycam", "securitycam_box", 0.5000, 0.5000, 0.5000, 0.5600, 0, 255, 255, 255, 255);
				DrawSprite("securitycam", "securitycam_scanlines", 0.5000, 0.5000, 1.0000, 1.0000, 0, 255, 255, 255, 255);

				Vector3 CamRot = GET_GAMEPLAY_CAM_ROT_orig(0);
				Vector3 vector3 = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
				Vector3 vector2 = get_entity_coords_orig(FakeMissileOb, false);

				if (UCAVTimer < GAMEPLAY::GET_GAME_TIMER())
				{
					NotifyDown("End Script.", 500);
					Vector3 vector2 = get_entity_coords_orig(FakeMissileOb, true);
					DeleteEntity(FakeMissileOb);
					DeleteEntity(PreMissile2);
					DeleteCam2();
					FIRE::ADD_EXPLOSION(vector2.x, vector2.y, vector2.z, 4, 1.0f, true, false, 0.0f);
					DeleteIMissile();
					PreCamera2 = 0;
					FakeMissileOb = 0;
					PreMissile2 = 0;
					Predator_ON2 = false;
				}
				else if (!ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(FakeMissileOb) && !ENTITY::IS_ENTITY_IN_WATER(FakeMissileOb))
				{
					Vector3 Force = { 0.0f, 5.0f, 0.0f };
					ApplyForce(FakeMissileOb, Force.x, Force.y, Force.z);
					CAM::SET_CAM_ROT1(PreCamera2, CamRot.x, CamRot.y, CamRot.z, 0);
					ENTITY::SET_ENTITY_ROTATION(FakeMissileOb, CamRot.x, CamRot.y, CamRot.z, 2, 1);
				}
				else if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(FakeMissileOb) || ENTITY::IS_ENTITY_IN_WATER(FakeMissileOb))
				{
					NotifyDown("End Script.", 500);
					DeleteEntity(FakeMissileOb);
					DeleteEntity(PreMissile2);
					DeleteCam2();
					FIRE::ADD_EXPLOSION(vector2.x, vector2.y, vector2.z, 4, 1.0f, true, false, 0.0f);
					DeleteIMissile();
					PreCamera2 = 0;
					FakeMissileOb = 0;
					PreMissile2 = 0;
					Predator_ON2 = false;
				}
			}
			else
			{
				Vector3 vector2 = get_entity_coords_orig(FakeMissileOb, false);
				NotifyDown("End Script.", 500);
				DeleteEntity(FakeMissileOb);
				DeleteEntity(PreMissile2);
				DeleteCam2();
				FIRE::ADD_EXPLOSION(vector2.x, vector2.y, vector2.z, 4, 1.0f, true, false, 0.0f);
				DeleteIMissile();
				PreCamera2 = 0;
				FakeMissileOb = 0;
				PreMissile2 = 0;
				Predator_ON2 = false;
			}

		}
	}

	if (CarGodCanBeDmg)
	{
		int vehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicleID,0);
		//VEHICLE::SET_VEHICLE_FIXED(vehicleID);
		VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(vehicleID, true);
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicleID, false);
	}

	/*if (MinecraftMode)
	{

		if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
		{
#pragma region To Invilid Button
			CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L1);
			CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R1);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_R1);
#pragma endregion
			Vector3 tmp = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
			Vector3 c = GET_COORDS_INFRONT(clipDistance);

			float coeff = (1.0f / 1.5f);
			float x = SYSTEM::ROUND(get_coords_from_entity(PLAYER::PLAYER_PED_ID(), clipDistance, true).x * coeff) / coeff;
			float y = SYSTEM::ROUND(get_coords_from_entity(PLAYER::PLAYER_PED_ID(), clipDistance, true).y * coeff) / coeff;
			float z = SYSTEM::ROUND(get_coords_from_entity(PLAYER::PLAYER_PED_ID(), clipDistance, true).z * coeff) / coeff;

			GRAPHICS::DRAW_LINE(tmp.x, tmp.y, tmp.z, x, y, z, 255, 0, 0, 255);

			Vector3 c1 = { x + 0.75f,y + 0.75f,z + 0.1f }; Vector3 c11 = { x + 0.75f,y + 0.75f,z - 1.5f + 0.1f };
			Vector3 c2 = { x + 0.75f,y - 0.75f,z + 0.1f }; Vector3 c22 = { x + 0.75f,y - 0.75f,z - 1.5f + 0.1f };
			Vector3 c3 = { x - 0.75f,y - 0.75f,z + 0.1f }; Vector3 c33 = { x - 0.75f,y - 0.75f,z - 1.5f + 0.1f };
			Vector3 c4 = { x - 0.75f,y + 0.75f,z + 0.1f }; Vector3 c44 = { x - 0.75f,y + 0.75f,z - 1.5f + 0.1f };

			drawLine(c1, c2);
			drawLine(c2, c3);
			drawLine(c3, c4);
			drawLine(c1, c4);

			drawLine(c11, c22);
			drawLine(c22, c33);
			drawLine(c33, c44);
			drawLine(c11, c44);

			drawLine(c1, c11);
			drawLine(c2, c22);
			drawLine(c3, c33);
			drawLine(c4, c44);

			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L1))
			{
				AAA.Lx = x; AAA.Ly = y; AAA.Lz = z;
				AAA.Rx = 0; AAA.Ry = 180; AAA.Rz = 0;
				AAA.objectname = "prop_mb_sandblock_01";
				AAA.Hash = GAMEPLAY::GET_HASH_KEY(AAA.objectname);
				ObjectSpawn = true;

			}

			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R1))
			{
				Entity obj;
				PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &obj);
				DeleteEntity(obj);
			}
		}
	}

	if (ObjectSpawn)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(AAA.Hash))
		{
			if (STREAMING::IS_MODEL_VALID(AAA.Hash))
			{
				STREAMING::REQUEST_MODEL(AAA.Hash);
				if (STREAMING::HAS_MODEL_LOADED(AAA.Hash))
				{
					ObjectListIndex = OBJECT::CREATE_OBJECT(AAA.Hash, AAA.Lx, AAA.Ly, AAA.Lz, 1, 1, 1);
					if (ENTITY::DOES_ENTITY_EXIST(ObjectListIndex))
					{
						ENTITY::SET_ENTITY_ROTATION(ObjectListIndex, AAA.Rx, AAA.Ry, AAA.Rz, 2, true);
						ENTITY::FREEZE_ENTITY_POSITION(ObjectListIndex, true);
						ObjectSpawn = false;
					}
				}
			}
		}
	}*/

//	if (infamousMOD)
//	{
//		Vector3 CamRotOrig = GET_GAMEPLAY_CAM_ROT_orig(2);
//		WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"), true);
//
//		switch (InfamousSwitch)
//		{
//		case Cancel: //"melee@unarmed@streamed_core", "shove"
//			if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "melee@unarmed@streamed_core", "shove", 3))
//			{
//				Freeze(PLAYER::PLAYER_PED_ID());
//			}
//			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2))
//			{
//				if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &infamousTarget))
//				{
//					InfamousSwitch = ENTITY::IS_ENTITY_A_VEHICLE(infamousTarget) ? GettingL2Obj : Cancel;
//				}
//			}
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_L1))
//			{
//				InfamousSwitch = WaitingButton;
//			}
//			if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_R1))
//			{
//				InfamousSwitch = CMD_ReadyForFly;
//			}
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_X))
//			{
//				infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//				InfamousSwitch = CMD_TeleportEffect;
//			}
//			break;
//
//		case GettingL2Obj:
//			if (!ENTITY::DOES_ENTITY_EXIST(infamousTarget))
//			{
//				InfamousSwitch = Cancel;
//				infamousTarget = 0;
//			}
//			RequestNetworkControl(infamousTarget);
//			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(infamousTarget, 1, 1);
//			InfamousDict = "rcmcollect_paperleadinout@";
//			InfamousAnim = "meditiate_idle";
//			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 3))
//			{
//				TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 49);
//			}
//			else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 3))
//			{
//				infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//				//ENTITY::SET_ENTITY_ALPHA(infamousTarget, 30, true);
//				InfamousSwitch = GettingisGet;
//			}
//			break;
//
//		case GettingisGet:
//			if (!ENTITY::DOES_ENTITY_EXIST(infamousTarget))
//			{
//				InfamousSwitch = Cancel;
//				infamousTarget = 0;
//			}
//			if (EffectTimer + 700 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Hand, 0.2f, 0, 0, 0);
//				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Hand, 0.2f, 0, 0, 0);
//				EffectTimer = GAMEPLAY::GET_GAME_TIMER();
//			}
//			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2))
//			{
//				ATTACH_ENTITY_TO_ENTITY(infamousTarget, PLAYER::PLAYER_PED_ID(), SKEL_ROOT, 0, 3, 0.2f, 0, 0, 0);		
//			}
//			else
//			{
//				InfamousSwitch = GettingThraw;
//			}
//			break;
//		case GettingThraw:
//
//			InfamousDict = "melee@unarmed@streamed_core";
//			InfamousAnim = "shove";
//			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 3))
//			{
//				AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "rcmcollect_paperleadinout@", "meditiate_idle", 3);
//				TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 48);
//			}
//			else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 3))
//			{
//				ENTITY::DETACH_ENTITY(infamousTarget, 0, 0);
//				if (!ENTITY::IS_ENTITY_ATTACHED(infamousTarget))
//				{
//					VEHICLE::SET_VEHICLE_FORWARD_SPEED(infamousTarget, 120.0f);
//					infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//					InfamousSwitch = GettingAnimationStop;
//					infamousTarget = 0;
//				}
//			}
//
//			break;
//		case GettingAnimationStop:
//			ENTITY::SET_ENTITY_ANIM_CURRENT_TIME(PLAYER::PLAYER_PED_ID(), InfamousDict, InfamousAnim, 0.18);
//			if (infamousTimer + 1000 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				infamousTimer = 0;
//				Freeze(PLAYER::PLAYER_PED_ID());
//				InfamousSwitch = Cancel;
//				infamousTarget = 0;
//			}
//			break;
//
//		case WaitingButton:
//
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_L1))
//			{
//				if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3) && !CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_R2))
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 49);
//				}
//
//				if (infamousTimer + 400 < GAMEPLAY::GET_GAME_TIMER())
//				{
//					if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_R1))
//					{
//						InfamousSwitch = ShootLaser;
//					}
//
//					if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_R2))
//					{
//						InfamousSwitch = CMD_Shockwave;
//					}
//
//					if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_X))
//					{
//						InfamousSwitch = CMD_LightningShot;
//					}
//				}
//			}
//			else
//			{
//				Freeze(PLAYER::PLAYER_PED_ID());
//				InfamousSwitch = Cancel;
//			}
//
//			break;
//
//		case ShootLaser:
//			if (infamousTimer + 400 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				int hash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER");
//				int Offset = GET_WEAPONS(hash);
//				int AmmoOffset = PS3::ReadInt32(Offset + AmmoInfo);
//				PS3::WriteUInt32(AmmoOffset + Explosion_Default, EXPLOSION_STICKYBOMB);
//				PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
//				VehicleWeaponsFunctionN4(hash);
//				infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//
//			}
//
//			break;
//
//		case CMD_Shockwave:
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_L1))
//			{
//				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_R2))
//				{
//					if (EffectTimer + 700 < GAMEPLAY::GET_GAME_TIMER())
//					{
//						STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//						GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//						GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Hand, 0.2f, 0, 0, 0);
//						EffectTimer = GAMEPLAY::GET_GAME_TIMER();
//					}
//
//					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "melee@unarmed@streamed_core", "shove", 3))
//					{
//						AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3);
//						TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "melee@unarmed@streamed_core", "shove", 49);
//					}
//					else if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "melee@unarmed@streamed_core", "shove", 3))
//					{
//						ENTITY::SET_ENTITY_ANIM_CURRENT_TIME(PLAYER::PLAYER_PED_ID(), "melee@unarmed@streamed_core", "shove", 0.18);
//						VehicleWeaponsFunctionN4(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_HUNTER"));
//					}
//				}
//				else
//				{
//					Freeze(PLAYER::PLAYER_PED_ID());
//					InfamousSwitch = WaitingButton;
//				}
//			}
//			else
//			{
//				InfamousSwitch = Cancel;
//			}
//			break;
//
//		case CMD_FireBreath://没
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_X))
//			{
//				if (infamousTimer + 6000 < GAMEPLAY::GET_GAME_TIMER())
//				{
//					int FirePlayerCoords = PLAYER::PLAYER_PED_ID();
//					float XPos1 = -0.02, YPos1 = 0.2, ZPos1 = 0.0, XOff1 = 90.0, YOff1 = 100.0, ZOff1 = 90.0;
//					STREAMING::REQUEST_NAMED_PTFX_ASSET("ent_liquid_cont");//scr_carsteal5_car_muzzle_flash
//					GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("ent_liquid_cont");
//					GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("ent_sht_flame", FirePlayerCoords, XPos1, YPos1, ZPos1, XOff1, YOff1, ZOff1, SKEL_Head, 0.8, 0, 0, 0);
//					infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//				}
//			}
//			else
//			{
//				InfamousSwitch = Cancel;
//			}
//			break;
//
//		case CMD_ReadyForFly:
//			if (ENTITY::DOES_ENTITY_EXIST(DummyInfamous))
//			{
//				ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), DummyInfamous, 0x0, 0, 0, 0, 360 - 50, 0, 0);
//				if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 3) || !ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3))
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 9);
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 49);
//				}
//				else
//				{
//					ApplyForce(DummyInfamous, 0, 0, 25, 0, 0, 0);
//					infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//					InfamousSwitch = CMD_Jumping;
//				}
//
//			}
//			else
//			{
//				DummyInfamous = Create_Map_int(TestOBJ, 0, false, false, true);
//			}
//			break;
//
//		case CMD_Jumping:
//
//			ENTITY::SET_ENTITY_ROTATION(DummyInfamous, 0, 0, CamRotOrig.z, 2, 1);
//			if (infamousTimer + 1500 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				InfamousSwitch = CMD_FlyMode;
//				AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 3);
//
//			}
//			break;
//
//		case CMD_FlyMode:
//			//ENTITY::SET_ENTITY_HAS_GRAVITY(DummyInfamous, false);
//
//			ENTITY::SET_ENTITY_ROTATION(DummyInfamous, 0, 0, CamRotOrig.z, 2, 1);
//			if (ENTITY::IS_ENTITY_ATTACHED(PLAYER::PLAYER_PED_ID()) && ENTITY::DOES_ENTITY_EXIST(DummyInfamous))
//			{
//				if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "amb@world_human_seat_steps@male@elbows_on_knees_skinny@idle_a", "idle_a_skinny", 3))
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "amb@world_human_seat_steps@male@elbows_on_knees_skinny@idle_a", "idle_a_skinny", 9);
//				}
//				if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 3))
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 49);
//				}
//
//				if (EffectTimer + 700 < GAMEPLAY::GET_GAME_TIMER())
//				{
//					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//					GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//					GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Hand, 0.5f, 0, 0, 0);
//					STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//					GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//					GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Hand, 0.5f, 0, 0, 0);
//					EffectTimer = GAMEPLAY::GET_GAME_TIMER();
//				}
//				ApplyForce(DummyInfamous, 0, 1, 0, 0, 0, 0);
//
//				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(DummyInfamous))
//				{
//					ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), 0, 0);
//					Freeze(PLAYER::PLAYER_PED_ID());
//					DeleteEntity(DummyInfamous);
//					InfamousSwitch = Cancel;
//				}
//			}
//			else
//			{
//				InfamousSwitch = Cancel;
//			}
//			break;
//
//		case CMD_LightningShot:
//			Hash ObjectHash = GAMEPLAY::GET_HASH_KEY("prop_ld_test_01");
//			if (!ENTITY::DOES_ENTITY_EXIST(LightNingObj))
//			{
//				Vector3 MYC = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
//				if (STREAMING::IS_MODEL_IN_CDIMAGE(ObjectHash))
//				{
//					if (STREAMING::IS_MODEL_VALID(ObjectHash))
//					{
//						STREAMING::REQUEST_MODEL(ObjectHash);
//						if (STREAMING::HAS_MODEL_LOADED(ObjectHash))
//						{
//							LightNingObj = OBJECT::CREATE_OBJECT(ObjectHash, MYC.x, MYC.y, MYC.z + 2, 1, 1, 1);
//						}
//					}
//				}
//			}
//			else
//			{
//
//				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ObjectHash);
//				if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(LightNingObj, PLAYER::PLAYER_PED_ID()))
//				{
//					ENTITY::DETACH_ENTITY(LightNingObj, 0, 0);
//					ApplyForce(LightNingObj, 0, 2, 0, 0, 0, 0);
//					InfamousSwitch = CMD_LightningMove;
//				}
//				else
//				{
//					ATTACH_ENTITY_TO_ENTITY(LightNingObj, PLAYER::PLAYER_PED_ID(), SKEL_R_Hand, 0, 3, 0, 0, 0, 0);
//				}
//			}
//			break;
//		case CMD_LightningMove:
//			if (infamousTimer + 300 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				PartcleFX_Entity("scr_trevor1", "scr_trev1_trailer_boosh", LightNingObj, 0, 0, 0, 0, 0, 0, 0.3f);
//				infamousTimer = GAMEPLAY::GET_GAME_TIMER();
//			}
//			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(LightNingObj))
//			{
//				Vector3 vector2 = get_entity_coords_orig(LightNingObj, 1);
//				FIRE::ADD_OWNED_EXPLOSION(PLAYER::PLAYER_PED_ID(), vector2.x, vector2.y, vector2.z, EXPLOSION_ROCKET, 1.0f, true, false, 0.0f);
//				DeleteEntity(LightNingObj);
//				LightNingObj = 0;
//				InfamousSwitch = WaitingButton;
//			}
//			break;
//
//		case CMD_TeleportEffect:
//			char bytes9[] = { 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0xFF };
//			PS3::WriteBytes(0x1E60FF0, bytes9, 9);
//			if (infamousTimer + 100 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				Vector3 OffsetCoord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 3, -1);
//				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), OffsetCoord.x, OffsetCoord.y, OffsetCoord.z, 1, 1, 1, 1);
//				PartcleFX_Entity("scr_rcbarry2", "scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 0.8f);
//				EffectTimer = GAMEPLAY::GET_GAME_TIMER();
//				InfamousSwitch = CMD_EffectReturn;
//			}
//			//GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR();
//			break;
//
//		case CMD_EffectReturn:
//			if (EffectTimer + 1000 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				char bytes3[] = { 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F };
//				PS3::WriteBytes(0x1E60FF0, bytes3, 9);
//				InfamousSwitch = Cancel;
//			}
//			break;
//		}
//#pragma region Disable Buttons
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_L1);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R1);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R1);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R2);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R2);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_X);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_X);
//#pragma endregion
//	}

	if (WaterEditFlagTrue)
	{
		WaterCount++;
		for (int i = 0; i < 100 * WaterCount; i++)
		{
			*(char*)(0x21C62AC + WaterEditMaxValue) = 0x00;
			WaterEditMaxValue++;
			if (WaterEditMaxValue >= 6492)
			{
				NotifyDown("処理終了", 1000);
				WaterEditFlagTrue = false;
				break;
			}
		}
	}

	if (WaterEditFlagFalse)
	{
		WaterCount++;
		for (int i = 0; i < 100 * WaterCount; i++)
		{
			*(char*)(0x21C62AC + WaterEditMaxValue) = WaterAddressMap[WaterEditMaxValue];
			WaterEditMaxValue++;
			if (WaterEditMaxValue >= 6492)
			{
				NotifyDown("処理終了", 1000);
				WaterEditFlagFalse = false;
				break;
			}
		}
	}

	if (SetPlayerAnimationForMe)
	{
		STREAMING::REQUEST_ANIM_DICT(Animations2[0]);
		if (STREAMING::HAS_ANIM_DICT_LOADED(Animations2[0]))
		{
			//   8 ループしない 
			//   9 ループ有
			// +40 上半身
			int Upper = isUpperAnim ? 49 : 9;
			TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), Animations2[0], Animations2[1], Upper);
			SetPlayerAnimationForMe = false;
		}
	}

	if (ClearAreaAll)
	{
		Vector3 MyPos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
		GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 1000000, true, 0, 0, 0);
		GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 1000000, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 1000000, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 1000000, 0, 0, 0, 0, 0);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 1000000, 0);
		GAMEPLAY::CLEAR_AREA_OF_PROJECTILES(MyPos.x, MyPos.y, MyPos.z, 1000000, 0);
	}

	if (Vehicle_Atach)
	{
		STREAMING::REQUEST_MODEL(Vehicle_Hash);
		FreezeHeli(1076625000);
		if (STREAMING::HAS_MODEL_LOADED(Vehicle_Hash));
		{
			Vector3 Coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
			int Handle = VEHICLE::CREATE_VEHICLE(Vehicle_Hash, Coords.x, Coords.y, Coords.z, 0, true, false);
			ENTITY::SET_ENTITY_VISIBLE(Handle, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Handle))
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Handle, PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1);
				Vehicle_Atach = false;
			}
		}

	}

	if (Vehicle_Atach2)
	{
		STREAMING::REQUEST_MODEL(Vehicle_Hash);
		FreezeHiko(1076625000);
		if (STREAMING::HAS_MODEL_LOADED(Vehicle_Hash));
		{
			Vector3 Coords = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
			int Handle = VEHICLE::CREATE_VEHICLE(Vehicle_Hash, Coords.x, Coords.y, Coords.z, 0, true, false);
			ENTITY::SET_ENTITY_VISIBLE(Handle, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Handle))
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Handle, PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1);
				Vehicle_Atach2 = false;
			}
		}

	}
	if (entityselectedgun)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Target))
			{
				if (ENTITY::IS_ENTITY_A_VEHICLE(Target))
				{
					selected = Target;
				}
				else if (ENTITY::IS_ENTITY_AN_OBJECT(Target))
				{
					if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Target))
					{
						selected = Target;
					}
				}
				else
				{
					selected = Target;
				}
			}
		}
	}


	if (VehicleAttachProtect)
	{
		if (VehicleFreezeProtectionDelay < GAMEPLAY::GET_GAME_TIMER())
		{
			Vector3 Myc = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
			const int numElements = 10;
			const int arrSize = numElements + 1;  //Start at index 2, and the odd elements are padding
			uint32_t vehs[arrSize];
			vehs[0] = numElements;
			int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);
			for (int i = 0; i < count; ++i)
			{
				int offsettedID = i + 1;
				if (ENTITY::DOES_ENTITY_EXIST(vehs[offsettedID]))
				{
					if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehs[offsettedID]))
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehs[offsettedID], 0, 1);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
						ENTITY::DELETE_ENTITY(&vehs[offsettedID]);
						NotifyDown("~b~ Vehicle removed.", 1000);
					}
				}
			}
			VehicleFreezeProtectionDelay = GAMEPLAY::GET_GAME_TIMER() + 500;
		}
	}

	if (ScriptDetect)
	{
		*(int*)(0x1C6BD80) = *(int*)((int)&scriptEventDetour);
		*(int*)((0x1C6BD80 + 0x4)) = *(int*)((int)&scriptEventDetour + 0x4);

		*(int*)(0x1C6BAA8) = *(int*)((int)&WeatherEventProtection);
		*(int*)((0x1C6BAA8 + 0x4)) = *(int*)((int)&WeatherEventProtection + 0x4);

		*(int*)(0x1C6BF80) = *(int*)((int)&AnimproProtection);
		*(int*)((0x1C6BF80+ 0x4)) = *(int*)((int)&AnimproProtection + 0x4);

		*(int*)(0x1C6C530) = *(int*)((int)&NETWORKINCREMENTSTATEVENT);
		*(int*)((0x1C6C530 + 0x4)) = *(int*)((int)&NETWORKINCREMENTSTATEVENT + 0x4);

		*(int*)(0x1C6C5C8) = *(int*)((int)&KICKVOTESEVENT);
		*(int*)((0x1C6C5C8 + 0x4)) = *(int*)((int)&KICKVOTESEVENT + 0x4);
		/**(int*)(0x1C6BD80) = *(int*)((int)&AnimPro);
		*(int*)((0x1C6BD80 + 0x4)) = *(int*)((int)&AnimPro + 0x4);*/
		//branch_link(*(int*)((int)&_0x12D4AFC), 0xA028FC);

	}
	
	if (FreezeConsoleBAN)
	{
		Ped Closest;
		Vector3 MyPos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
		if (PED::GET_CLOSEST_PED(MyPos.x, MyPos.y, MyPos.z, 10000, true, true, &Closest, false, true, -1))
		{
			int Model = ENTITY::GET_ENTITY_MODEL(Closest);
			RequestNetworkControl(Closest);
			PED::DELETE_PED(&Closest);
			if (Model == 0x3F039CBA) //slod_human
				NotifyDown("フリーズモデルを削除しました。", 1000);
		}
		//0x3F039CBA
	}

	for (int i = 0; i < 20; i++)
	{
		if (ENTITY::DOES_ENTITY_EXIST(SpawnedVehicleCode[i]))
		{
			if (AttachFlag[i])
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				if (vehicle != SpawnedVehicleCode[i])
				{
					RequestNetworkControl(vehicle);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
					Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedVehicleCode[i], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
				}
				else
				{
					NotifyDown("エラー。選択中の車両と乗っている車両が同一です。", 1500);
					AttachFlag[i] = false;
				}
			}
			if (EditVehicle_Main_[i])
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(SpawnedVehicleCode[i], ColorR, ColorG, ColorB);
			}
			if (EditVehicle_Sub_[i])
			{
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(SpawnedVehicleCode[i], ColorR, ColorG, ColorB);
			}
			if (EditVehicle_Smoke_[i])
			{
				VEHICLE::TOGGLE_VEHICLE_MOD(SpawnedVehicleCode[i], 20, 1);
				VEHICLE::SET_VEHICLE_MOD_KIT(SpawnedVehicleCode[i], 0);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(SpawnedVehicleCode[i], ColorR, ColorG, ColorB);
			}
		}
		else
		{
			AttachFlag[i] = false;
			EditVehicle_Main_[i] = false;
			EditVehicle_Sub_[i] = false;
			EditVehicle_Smoke_[i] = false;
		}
	}

	if (PedSpawn)
	{
		if (PedSpawnMethod(PedName) == 1)
		{
			PedName = "";
			PedSpawn = false;
		}
	}

	if (ChangeModelHash)
	{
		ChangeModelHash = !SET_PLAYER_MODEL(ModelHash);
	}

	if (ObjectBypass)
	{
		char Objectnop[] = { 0x60,0x00,0x00,0x00 };
		PS3::WriteBytes(0x3F8B10, Objectnop, 4); //ObjectBypass	
		//PS3::WriteBytes(0x3F8B84, Objectnop, 4); //ObjectBypass2 ??? from AnotherMenu
		NotifyDown("Object Bypass:~g~Added");
		objectbypass = true;
		ObjectBypass = false;
	}

	if (Getting)
	{
		for (int i = index; i < 0x10000 + index; i += 4)
		{
			if (PS3::ReadInt32(StartAddress + i) == SearchOffset[0])
			{
				if (SearchOffset[1] == 0)
				{
					IsGodddd = true;
				}
				else
				{
					if (PS3::ReadInt32(StartAddress + i + 0x04) == SearchOffset[1])
					{
						if (SearchOffset[2] == 0)
						{
							IsGodddd = true;
						}
						else
						{
							if (PS3::ReadInt32(StartAddress + i + 0x08) == SearchOffset[2])
							{
								if (SearchOffset[3] == 0)
								{
									IsGodddd = true;
								}
								else
								{
									if (PS3::ReadInt32(StartAddress + i + 0x0C) == SearchOffset[3])
									{
										IsGodddd = true;
									}
								}
							}
						}

					}
				}
			}
			else
			{
				IsGodddd = false;
			}

			if (IsGodddd)
			{
				AddressHandling = StartAddress + i;
				NotifyDown("取得したぞ！", 3000);
				Getting = false;
				IsgetQuestion = true;
				if (SettingFlying)
				{
					PS3::WriteBytes(AddressHandling + 88u, FreezeHelibyte, 8);
					SettingFlying = false;
				}
				else if (ComeBackFlying)
				{
					PS3::WriteBytes(AddressHandling + 88u, T20bytes, 8);
					ComeBackFlying = false;
				}
				break;
			}

			if (index >= 0x10000000)
			{
				Getting = false;
				NotifyDown("取得できなかった！！", 3000);
				break;
			}
		}
		index += 0x10000;
	}
	if (PlusAllX > 0.0f)
	{
		PlusAllX -= 0.1f;
	}
	else if (PlusAllX <= 0.0f)
	{
		PlusAllX = 0.0f;
	}

	if (AnimationTimerCount < GAMEPLAY::GET_GAME_TIMER())
	{
		if (!AnimationMinusFlag)
		{
			if (TextSize04f > 0.4f)
			{
				TextSize04f -= 0.025f;
			}
			else if (TextSize04f <= 0.4f)
			{
				TextSize04f = 0.4f;
				AnimationMinusFlag = true;
				AnimationPlusFlag = false;
			}
		}
		if (!AnimationPlusFlag)
		{
			if (TextSize04f < 0.6f)
			{
				TextSize04f += 0.025f;
			}
			else if (TextSize04f >= 0.6f)
			{
				TextSize04f = 0.6f;
				AnimationPlusFlag = true;
			}
		}
		if (ScrollBarPlus != 0)
		{
			if (ScrollBarPlus < 0)
			{
				ScrollBarPlus += 0.01f;
			}

			if (ScrollBarPlus > 0)
			{
				ScrollBarPlus -= 0.01f;
			}
		}

		AnimationTimerCount = GAMEPLAY::GET_GAME_TIMER() + 5;
	}
	//PlusAllX

	if (SpeedMeter)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) // if you'r in a Car or ... Speedometer shows up!
		{
			float speed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) * 3.3;// this transfers the speed to Float rotate
			speed = speed + 1;
			if (speed > 260)
			{
				speed = 260;
			}
			DrawSprite("speedometers", "off_road_race_icon", METER1, METER2, METER3, METER4, 0, 255, 255, 255, 255);//speedometer background
			DrawSprite("speedometers", "last_team_standing_icon", METER1, METER2, METER3, METER4, speed, 255, 255, 255, 255);//Speedometer needle 
		}
	}

	if (WaterQuadAddress)
	{
		WaterQuad = FindPattern(0x32000000 + (0x10000 * WaterIndex), 0x30000, (BYTE*)QuadBytes, "xxxxxxxxxxxxxxxx");
		if (WaterQuad != 0)
		{
			NotifyDown(ItoS(WaterQuad, true), 1000);
			WaterQuadAddress = false;
		}
		else
		{
			if (WaterIndex != 1000)
			{
				WaterIndex++;
			}
			else
			{
				NotifyDown("検索しっぱい", 1000);
				WaterQuadAddress = false;
				WaterIndex = 0;
			}
		}

	}

	

	if (ObjectAttachFlag22)
	{
		if (ShotToEntity)
		{
			if (ObjectList[ObjectSelectedIndex] != Selected)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(Selected, BoneList[BoneIndex]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ObjectList[ObjectSelectedIndex], Selected, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
			}
			else
			{
				NotifyDown("エラーが発生したため、アタッチ出来ませんでした。", 1000);
			}
		}
		else
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(ObjectList[ObjectSelectedIndex], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
		}

	}

	if (ObjectAttachFlag222)
	{
		if (ShotToEntity)
		{
			if (selected != Selected)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(Selected, BoneList[BoneIndex]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(selected, Selected, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
			}
			else
			{
				NotifyDown("エラーが発生したため、アタッチ出来ませんでした。", 1000);
			}
		}
		else
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(selected, vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
		}

	}

	

	if (AllQuadView)
	{
		for (int i = 0; i < WaterQuadLength; i++)
		{
			DrawViewName(i);
		}
	}

//	if (IronmanV2)
//	{
//		Vector3 CamRotOrig = GET_GAMEPLAY_CAM_ROT_orig(2);
//		switch (Ironman::MovementFlag)
//		{
//		case WalkingIronman:
//			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, Button_L1))
//			{
//				if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "mini@strip_club@idles@bouncer@stop", "stop", 3) && (ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(PLAYER::PLAYER_PED_ID(), "mini@strip_club@idles@bouncer@stop", "stop") >= 0.34f))
//				{
//					ENTITY::SET_ENTITY_ANIM_CURRENT_TIME(PLAYER::PLAYER_PED_ID(), "mini@strip_club@idles@bouncer@stop", "stop", 0.34);
//				}
//				else
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@idles@bouncer@stop", "stop", 48);
//				}//0.34
//				float ScreenX, ScreenY;
//				#pragma region ESP & Lock Explosion Vehicle
//				const int numElements = 10;
//				const int arrSize = numElements + 1;
//				uint32_t vehs[arrSize];
//				vehs[0] = numElements;
//				int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);
//				for (int i = 0; i < count; ++i)
//				{
//					int offsettedID = i + 1;
//					Entity Target = vehs[offsettedID];
//					Vector3 handleCoords = get_entity_coords_orig(Target, 1);
//					UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &ScreenX, &ScreenY);
//					if (isLockOnEntity(ScreenX, ScreenY))
//					{
//						HelpTextDraw("R1 : Explosion");
//						HelpTextDraw("R2 : Force Up");
//						HelpTextDraw("Up : Rocket");
//						RequestNetworkControl(Target);
//						GRAPHICS::DRAW_MARKER(MarkerTypeChevronUpx1, handleCoords.x, handleCoords.y, handleCoords.z + 1.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, false, false, false);
//						if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_R1))
//						{
//							VEHICLE::SET_VEHICLE_FORWARD_SPEED(Target, 0);
//							ToggleFreezeEntity(Target, true);
//							FIRE::ADD_EXPLOSION(handleCoords.x, handleCoords.y, handleCoords.z, EXPLOSION_GRENADE, 0.5f, true, false, 0.0f);
//							ToggleFreezeEntity(Target, false);
//						}
//
//						if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_R2))
//						{
//							ApplyForce(Target, 0, 3, 5.6, 60, 60, 60);
//							//VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehs[offsettedID], 60.0f);
//						}
//
//						if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Dpad_Up))
//						{
//							//FIRE::ADD_EXPLOSION(handleCoords.x, handleCoords.y, handleCoords.z, EXPLOSION_FLARE, 10, 1, 0, 0);
//							VEHICLE::SET_VEHICLE_FORWARD_SPEED(Target, 0);
//							GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(handleCoords.x, handleCoords.y, handleCoords.z += 55, handleCoords.x, handleCoords.y, handleCoords.z, 100, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 150);
//						}
//					}
//				}
//#pragma endregion
//
//				#pragma region ESP & Lockon PeD
//				Ped Closest;
//				int veh[arrSize];
//				veh[0] = numElements;
//				int count2 = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, 0);
//				if (veh != NULL)
//				{
//					for (int i = 0; i < count2; i++)
//					{
//						int Target = veh[i];
//						Vector3 handleCoords = get_entity_coords_orig(Target, 1);
//						UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &ScreenX, &ScreenY);
//						if (isLockOnEntity(ScreenX, ScreenY))
//						{
//							GRAPHICS::DRAW_MARKER(MarkerTypeChevronUpx1, handleCoords.x, handleCoords.y, handleCoords.z + 1.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, false, false, false);
//							if (IronmanV2EffectTimer + 700 < GAMEPLAY::GET_GAME_TIMER())
//							{
//								STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
//								GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
//								GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", Target, 0, 0, 0, 0, 0, 0, PED::GET_PED_BONE_INDEX(Target, SKEL_ROOT) , 0.5f, 0, 0, 0);
//								IronmanV2EffectTimer = GAMEPLAY::GET_GAME_TIMER();
//							}
//						}
//					}
//				}
//#pragma endregion	
//			}
//			else
//			{
//				if (ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "mini@strip_club@idles@bouncer@stop", "stop", 3))
//				{
//					Freeze(PLAYER::PLAYER_PED_ID());
//				}
//			}
//
//			if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_L3))
//			{
//				Ironman::MovementFlag = ReadyFlyingIronman;
//			}
//			break;
//
//		case ReadyFlyingIronman:
//			if (ENTITY::DOES_ENTITY_EXIST(DummyIronman))
//			{
//				ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), DummyIronman, 0x0, 0, 0, 0, 360 - 50, 0, 0);
//				if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 3) || !ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3))
//				{
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 9);
//					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 49);
//				}
//				else
//				{
//					ApplyForce(DummyIronman, 0, 0, 25, 0, 0, 0);
//					Ironman::IronmanTimer = GAMEPLAY::GET_GAME_TIMER();
//					Ironman::MovementFlag = JumpingIronman;
//				}
//
//			}
//			else
//			{
//				DummyIronman = Create_Map_int(TestOBJ, 0, false, false, true);
//			}
//			break;
//			
//		case JumpingIronman:
//
//			ENTITY::SET_ENTITY_ROTATION(DummyIronman, 0, 0, CamRotOrig.z, 2, 1);
//			if (Ironman::IronmanTimer + 1500 < GAMEPLAY::GET_GAME_TIMER())
//			{
//				Ironman::MovementFlag = FlyingIronman;
//				AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "missfam5_yoga", "f_yogapose_c", 3);
//			}
//			break;
//
//		case FlyingIronman:
//			#pragma region Effect
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", -0.0, -0.145f, -0.1, 0, 0, 180, 24818, 0.35f);
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", -0.0, -0.145f, 0.1, 0, 0, 180, 24818, 0.35f);
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", 0.1, 0, 0.015, 0, -20, 0, 18905, 0.3);
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", 0.1, 0, -0.015, 0, 20, 0, 57005, 0.3);
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", 0, 0, 0, 0, 90, 0, 57717, 0.5);
//			PartcleFX_Bone("scr_carsteal4", "scr_carsteal5_car_muzzle_flash", 0, 0, 0, 0, 90, 0, 24806, 0.5);
//#pragma endregion
//			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "move_m@coward", "idle", 3) || !ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 3))
//			{
//				TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "move_m@coward", "idle", 49);
//				TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "skydive@parachute@", "chute_idle", 9);
//			}
//			break;
//		}
//		switch (Ironman::AttackFlag)
//		{
//		case NoneIronman:
//			
//			break;
//		}
//
//#pragma region Disable Buttons
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_L1);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R1);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R1);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_L2);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L2);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R2);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R2);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_L3);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L3);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_R3);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R3);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Button_X);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Button_X);
//		CONTROLS::SET_INPUT_EXCLUSIVE(0, Dpad_Up);
//		CONTROLS::DISABLE_CONTROL_ACTION(0, Dpad_Up);
//#pragma endregion
//	}
	if (TestUIOption)
	{

	}
	if (PlayerHeightSize != 1.0f)
	{
		*(float*)(*(int*)(GetEntityAddress(PLAYER::PLAYER_PED_ID()) + 0x30) + 0x28) = PlayerHeightSize;
	}
	
	/*if (Rainbow_Effect)
	{
		if (RainbowEffectInt[0] == 0.0f) {
			if (RainbowEffectInt[1] > 0.0f)
				RainbowEffectInt[1] -= 0.1f;
			if (RainbowEffectInt[2] < 1.0f)
				RainbowEffectInt[2] += 0.1f;
		}
		if (RainbowEffectInt[1] == 0.0f) {
			if (RainbowEffectInt[2] > 0.0f)
				RainbowEffectInt[2] -= 0.1f;
			if (RainbowEffectInt[0] < 1.0f)
				RainbowEffectInt[0] += 0.1f;
		}
		if (RainbowEffectInt[2] == 0.0f) {
			if (RainbowEffectInt[0] > 0.0f)
				RainbowEffectInt[0] -= 0.1f;
			if (RainbowEffectInt[1] < 1.0f)
				RainbowEffectInt[1] += 0.1f;
		}

		PS3::WriteFloat(0x1E60FF0, RainbowEffectInt[0]);
		PS3::WriteFloat(0x1E60FF4, RainbowEffectInt[1]);
		PS3::WriteFloat(0x1E60FF8, RainbowEffectInt[2]);
	}*/
	if (SearchingHeadlight)
	{

		
	}
}
	
#pragma endregion

#pragma region Player Infomation
int getCash(int player)
{
	return PS3::Read_Global(1581949 + player * 306);
}




int getPlayerStat(int player, int stat)
{
	return PS3::Read_Global(1581767 + (player * 306) + stat);
}

int getPlayerhost(int player)
{
	return PS3::Read_Global(1315372 + (player));
}

//1315372 //iVar0 - 1

int getPlayerRP(int player)
{
	return getPlayerStat(player, 180);
}
int getPlayerRank(int player)
{
	return getPlayerStat(player, 185);
}

int getIDTEST(int player)
{
	return PS3::Read_Global(1582015 + (306 * player));

}


void MenuIDset(int rank)
{
	PS3::Write_Global(19349 + returnPlayerStats(), rank);
}

int getIDspoof(int player)
{
	return getPlayerStat(player, 205);
}


void spoofID(int ID)
{
	PS3::Write_Global(1581972 + returnPlayerStats(), ID);
}


int getIDTEST2(int player)
{
	return PS3::Read_Global(1587565 + (306 * player));
}



//////////////

//////////////

void PlayerInfo(int Index)
{
	#pragma region Rect & Glare
	if (FlagIndexes == AdminFlag)
	{
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusY2, Option019f, PlayerUIMinusY, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine1Coord, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // X Line
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine2Coord, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // X Line 2
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusX, Option019f, LineSize, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Title Line
		GRAPHICS::DRAW_RECT((YLine1Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Y Line
		GRAPHICS::DRAW_RECT((YLine2Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR1, PerpleG1, PerpleB1, backgroundOpacity); // Y Line 2
		drawGlare(GlareUI.LocX);
	}
	else
	{
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusY2, Option019f, PlayerUIMinusY, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine1Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine2Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line 2
		GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusX, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Title Line
		GRAPHICS::DRAW_RECT((YLine1Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line
		GRAPHICS::DRAW_RECT((YLine2Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line 2
		drawGlare(GlareUI.LocX);
	}
#pragma endregion

	int PlayerIndex = PLAYER::GET_PLAYER_PED(Index);
	int pedArmour = PED::GET_PED_ARMOUR(PLAYER::GET_PLAYER_PED(Index));
	int maxArmour = PLAYER::GET_PLAYER_MAX_ARMOUR(Index);
	char RealName[200];
	int p0[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(Index, &p0[0], 13);
	char *RealNaming = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&p0[0]);
	char *OldName = PLAYER::GET_PLAYER_NAME(Index);
	snprintf(RealName, 200, "偽装前ネーム : %s%s", strstr(OldName, RealNaming) != NULL ? "~w~" : "~r~", RealNaming);

	char ModelHash[500];
	snprintf(ModelHash, 500, "モデルハッシュ : 0x%8X", ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED(Index)));

	char VCSet[500];
	snprintf(VCSet, 500, "VC : %s", NETWORK::NETWORK_PLAYER_HAS_HEADSET(Index) ? NETWORK::NETWORK_IS_PLAYER_TALKING(Index) ? "~g~会話中" : "~b~VC装着" : "~r~VC無し");

	char WantedLevel[60];
	snprintf(WantedLevel, 60, "手配度 : %i", PLAYER::GET_PLAYER_WANTED_LEVEL(Index));

	char RankLevel[500];
	snprintf(RankLevel, 500, "ランク : %i", getPlayerRank(Index));

	char Hostid[500];
	snprintf(Hostid, 500, "判定 : %i", getPlayerhost(Index));

	//char invincible[60];
	//snprintf(invincible, 60, "無敵 : %s", PLAYER::GET_PLAYER_INVINCIBLE(PlayerIndex) ? "~r~Yes" : "~b~No");

	//snprintf(invincible, 60, "無敵 : %s", ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(PlayerIndex)) ? "~r~Yes" : "~b~No");


	char ArmourText[500];
	snprintf(ArmourText,500, "アーマー : %i / %i", pedArmour, maxArmour);

	char HealthText[100];
	snprintf(HealthText,100, "体力 : %i / %i", ENTITY::GET_ENTITY_HEALTH(PlayerIndex), ENTITY::GET_ENTITY_MAX_HEALTH(PlayerIndex));

	char MoneyText[100];
	snprintf(MoneyText,100, "所持金 : %i $", (int)getCash(Index));

	

	Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PlayerIndex, true);

	char _X[200], _Y[200], _Z[200];

	snprintf(_X, 200, "X : ~b~[ ~w~%i ~b~]", (int)playerpos.x);
	snprintf(_Y, 200, "Y : ~b~[ ~w~%i ~b~]", (int)playerpos.y);
	snprintf(_Z, 200, "Z : ~b~[ ~w~%i ~b~]", (int)playerpos.z);

	char VehicleText[35];
	char *VehicleName = UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PlayerIndex, 0))));
	sprintf(VehicleText, "車両 %s", (strstr(VehicleName, "NULL") != NULL) ? "歩行中" : VehicleName);



	drawText(OldName, bannerTextFont, menuXCoord - 0.25f, TitleTextY, TitleSize, TitleSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);


	drawText(RealName, 1, TestX, 0.160, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(HealthText, 1, TestX, 0.185, 0.4, 0.4, 255, 255, 255, 255, false);
	drawText(ArmourText, 1, TestX, 0.210, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(MoneyText, 1, TestX, 0.235, 0.4, 0.4, 255, 255, 255, 255, false);
	drawText(VehicleText, 1, TestX, 0.260, 0.4, 0.4, 255, 255, 255, 255, false, false);


	drawText(ModelHash, 1, TestX, 0.285, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(VCSet, 1, TestX, 0.310, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(WantedLevel, 1, TestX, 0.335, 0.4, 0.4, 255, 255, 255, 255, false, false);
	//drawText(invincible, 1, TestX, 0.260, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(RankLevel, 1, TestX, 0.360, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(_X, 1, TestX, 0.385, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(_Y, 1, TestX, 0.410, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(_Z, 1, TestX, 0.435, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(Hostid, 1, TestX, 0.460, 0.4, 0.4, 255, 255, 255, 255, false, false);







}
#pragma endregion




#pragma region Object
void ObjectInfo(int Index)
{
	#pragma region Rect & Glare
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusY2, Option019f, PlayerUIMinusY, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine1Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine2Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line 2
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusX, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Title Line
	GRAPHICS::DRAW_RECT((YLine1Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line
	GRAPHICS::DRAW_RECT((YLine2Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line 2
	drawGlare(GlareUI.LocX);
#pragma endregion

	Vector3 XYZCoord = ENTITY::GET_ENTITY_COORDS(ObjectList[Index], 1);
	Vector3 XYZROtat = ENTITY::GET_ENTITY_ROTATION(ObjectList[Index], 1);

	char XYZ[60];
	snprintf(XYZ, 60, "X:%i Y:%i Z:%i", (int)(XYZCoord.x), (int)(XYZCoord.y), (int)(XYZCoord.z));

	char ModelHash[30];
	snprintf(ModelHash, 30, "モデルハッシュ : 0x%8X", ENTITY::GET_ENTITY_MODEL(ObjectList[Index]));

	char RotationX[60];
	snprintf(RotationX, 60, "Rotation X : %i", (int)(XYZROtat.x));

	char RotationY[60];
	snprintf(RotationY, 60, "Rotation Y : %i", (int)(XYZROtat.x));

	char RotationZ[60];
	snprintf(RotationZ, 60, "Rotation Z : %i", (int)(XYZROtat.x));
	
	drawText(objectnamearray[Index], bannerTextFont, menuXCoord - 0.25f, TitleTextY, TitleSize, TitleSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	
	drawText(XYZ, 1, TestX, 0.160, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(ModelHash, 1, TestX, 0.185, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(RotationX, 1, TestX, 0.210, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(RotationY, 1, TestX, 0.235, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(RotationZ, 1, TestX, 0.260, 0.4, 0.4, 255, 255, 255, 255, false, false);
	//drawText("テスト表示5", 1, TestX, 0.260, 0.4, 0.4, 255, 255, 255, 255, false, false);


}
#pragma endregion

#pragma region Water Opacity
void WaterQuadInfo(int Index)
{
	int QuadIndex = WaterQuad + Index * 0x1C;
	int Opacity1 = (int)PS3::ReadByte(QuadIndex + 0x08),
		Opacity2 = (int)PS3::ReadByte(QuadIndex + 0x09),
		Opacity3 = (int)PS3::ReadByte(QuadIndex + 0x0A),
		Opacity4 = (int)PS3::ReadByte(QuadIndex + 0x0B);

	float XCoord = ReturnWaterXY(Index).x;
	float YCoord = ReturnWaterXY(Index).y;

	float Height = *(float*)(WaterQuad + (Index * 0x1C) + 0x14);
	int Number	 = Index;

	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusY2, Option019f, PlayerUIMinusY, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine1Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, XLine2Coord, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // X Line 2
	GRAPHICS::DRAW_RECT((menuXCoord + PlusAllX) - 0.25f, PlayerUIMinusX, Option019f, LineSize, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Title Line
	GRAPHICS::DRAW_RECT((YLine1Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line
	GRAPHICS::DRAW_RECT((YLine2Coord + PlusAllX) - 0.25f, PlayerUIMinusY2, LineSize2, PlayerUIMinusY, PerpleR, PerpleG, PerpleB, backgroundOpacity); // Y Line 2

	char XCoords[30];
	snprintf(XCoords, 30, "X座標 : %i", (int)XCoord);

	char YCoords[30];
	snprintf(YCoords, 30, "Y座標 : %i", (int)YCoord);

	char Heights[30];
	snprintf(Heights, 30, "高さ  : %i", (int)Height);

	char Opacitys[50];
	snprintf(Opacitys, 50, "透明度 : 0x%2X 0x%2X 0x%2X 0x%2X", Opacity1, Opacity2, Opacity3, Opacity4);

	drawText(XCoords, 1, TestX, 0.160, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(YCoords, 1, TestX, 0.185, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(Heights, 1, TestX, 0.210, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(Opacitys, 1, TestX, 0.235, 0.4, 0.4, 255, 255, 255, 255, false, false);
	//drawText("テスト表示5", 1, TestX, 0.260, 0.4, 0.4, 255, 255, 255, 255, false, false);
	drawText(quadFormatStr(Number), bannerTextFont, menuXCoord - 0.25f, TitleTextY, TitleSize, TitleSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	drawGlare(GlareUI.LocX);
}

void WaterOpacityEdit(int opacity)
{
	int WaterQuad = PS3::ReadInt32(QuadPointer);
	for (int i = 0; i < WaterQuadLength; i++)
	{
		PS3::WriteByte(WaterQuad + i * 0x1C + 0x08, (char)opacity);
		PS3::WriteByte(WaterQuad + i * 0x1C + 0x09, (char)opacity);
		PS3::WriteByte(WaterQuad + i * 0x1C + 0x0A, (char)opacity);
		PS3::WriteByte(WaterQuad + i * 0x1C + 0x0B, (char)opacity);
	}
}
#pragma endregion

#pragma region WeaponComp

float WCFloat(int index)
{
	return PS3::ReadFloat(SelectedCompAddress + index);
}

enum FlashCompEnum
{
	F_MainLightIntensity = 0x2C,
	F_MainLightColor1 = 0x30,
	F_MainLightColor2 = 0x31,
	F_MainLightColor3 = 0x32,
	F_MainLightColor4 = 0x33,
	F_MainLightRange = 0x34,
	F_MainLightFalloffExponent = 0x38,
	F_MainLightInnerAngle = 0x3C,
	F_MainLightOuterAngle = 0x40,
	F_MainLightCoronaIntensity = 0x44,
	F_MainLightCoronaSize = 0x48,
	F_MainLightVolumeIntensity = 0x4C,
	F_MainLightVolumeSize = 0x50,
	F_MainLightVolumeExponent = 0x54,
	F_MainLightVolumeOuterColor1 = 0x58,
	F_MainLightVolumeOuterColor2 = 0x59,
	F_MainLightVolumeOuterColor3 = 0x5A,
	F_MainLightVolumeOuterColor4 = 0x5B,
	F_MainLightShadowFadeDistance = 0x5C,
	F_MainLightSpecularFadeDistance = 0x60, //10.0f 0x41200000

	F_SecondaryLightIntensity = 0x64,
	F_SecondaryLightColor1 = 0x68,
	F_SecondaryLightColor2 = 0x69,
	F_SecondaryLightColor3 = 0x6A,
	F_SecondaryLightColor4 = 0x6B,
	F_SecondaryLightRange = 0x6C,
	F_SecondaryLightFalloffExponent = 0x70,
	F_SecondaryLightInnerAngle = 0x74,
	F_SecondaryLightOuterAngle = 0x78,
	F_SecondaryLightVolumeIntensity = 0x7C,
	F_SecondaryLightVolumeSize = 0x80,
	F_SecondaryLightVolumeExponent = 0x84,
	F_SecondaryLightVolumeOuterColor1 = 0x88,
	F_SecondaryLightVolumeOuterColor2 = 0x89,
	F_SecondaryLightVolumeOuterColor3 = 0x8A,
	F_SecondaryLightVolumeOuterColor4 = 0x8B,
	F_SecondaryLightFadeDistance = 0x8C,
	F_fTargetDistalongAimCamera = 0x90,

};

//void WriteFloatLight(int index, float input)
//{
//	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
//	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
//	for (int i = 0; i < 0x5D; i++)
//	{
//		PS3::WriteFloat(HeadlightAddress + (i * 0x180) + index, input);
//	}
//}

//void WriteByteLight(int index, char input)
//{
//	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
//	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
//	for (int i = 0; i < 0x5D; i++)
//	{
//		PS3::WriteByte(HeadlightAddress + (i * 0x180) + index, input);
//	}
//}

void ReloadWeaponFlashComp()
{
	MainLightIntensity = WCFloat(0x2C);
	Color1Comp[0] = PS3::ReadByte(SelectedCompAddress + 0x30);
	Color1Comp[1] = PS3::ReadByte(SelectedCompAddress + 0x31);
	Color1Comp[2] = PS3::ReadByte(SelectedCompAddress + 0x32);
	Color1Comp[3] = PS3::ReadByte(SelectedCompAddress + 0x33);
	MainLightRange = WCFloat(0x34);
	MainLightFalloffExponent = WCFloat(F_MainLightFalloffExponent);
	MainLightInnerAngle = WCFloat(F_MainLightInnerAngle);
	MainLightOuterAngle = WCFloat(F_MainLightOuterAngle);
	MainLightCoronaIntensity = WCFloat(F_MainLightCoronaIntensity);
	MainLightCoronaSize = WCFloat(F_MainLightCoronaSize);
	MainLightVolumeIntensity = WCFloat(F_MainLightVolumeIntensity);
	MainLightVolumeSize = WCFloat(F_MainLightVolumeSize);
	MainLightVolumeExponent = WCFloat(F_MainLightVolumeExponent);
	Color1CompSecond[0] = PS3::ReadByte(SelectedCompAddress + F_MainLightVolumeOuterColor1);
	Color1CompSecond[1] = PS3::ReadByte(SelectedCompAddress + F_MainLightVolumeOuterColor2);
	Color1CompSecond[2] = PS3::ReadByte(SelectedCompAddress + F_MainLightVolumeOuterColor3);
	Color1CompSecond[3] = PS3::ReadByte(SelectedCompAddress + F_MainLightVolumeOuterColor4);
	MainLightShadowFadeDistance = WCFloat(F_MainLightShadowFadeDistance);
	MainLightSpecularFadeDistance = WCFloat(F_MainLightSpecularFadeDistance);
	SecondaryLightIntensity = WCFloat(F_SecondaryLightIntensity);
	SecondaryColor1Comp[0] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightColor1);
	SecondaryColor1Comp[1] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightColor2);
	SecondaryColor1Comp[2] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightColor3);
	SecondaryColor1Comp[3] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightColor4);
	SecondaryLightRange = WCFloat(F_SecondaryLightRange);
	SecondaryLightFalloffExponent = WCFloat(F_SecondaryLightFalloffExponent);
	SecondaryLightInnerAngle = WCFloat(F_SecondaryLightInnerAngle);
	SecondaryLightOuterAngle = WCFloat(F_SecondaryLightOuterAngle);
	SecondaryLightVolumeIntensity = WCFloat(F_SecondaryLightVolumeIntensity);
	SecondaryLightVolumeSize = WCFloat(F_SecondaryLightVolumeSize);
	SecondaryLightVolumeExponent = WCFloat(F_SecondaryLightVolumeExponent);
	SecondaryLightVolumeOuterColor1Comp[0] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor1);
	SecondaryLightVolumeOuterColor1Comp[1] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor2);
	SecondaryLightVolumeOuterColor1Comp[2] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor3);
	SecondaryLightVolumeOuterColor1Comp[3] = PS3::ReadByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor4);
	SecondaryLightFadeDistance = WCFloat(F_SecondaryLightFadeDistance);
	fTargetDistalongAimCamera = WCFloat(F_fTargetDistalongAimCamera);
}

Hash g_uiAllCar[] = { 0x898ECCEA ,0xF21B33BE,0x07405E08 ,0xAFBB2CA4, 0xC9E8FF76,0x98171BD3,0x353B561D,0x437CF2A0,0x6FD95F68 ,0x97FA4F36, 0xC1CE1183, 0x33581161, 0x17DF5EC2, 0xEF2295C9, 0x1149422F, 0xC2974024, 0xDB4388E4, 0xE2E7D4AB, 0x2DFF622F, 0x0DC60D2B, 0x3D961290, 0x107F392C, 0x3FD5AA2F, 0x761E2AD3, 0x250B0C5E, 0xB79F589E, 0xB79C1BF5, 0x4FF77E37, 0x09D80F93, 0x9C429B6A, 0x403820E8, 0x97E55D11, 0x39D6779E, 0x81794C70, 0xD9927FE3, 0x15F27762, 0xF7004C86, 0xB39B0AE6, 0x3E48BF23, 0x3F119114, 0x6CBD1D6D, 0x39D6E83F, 0x31F0B376, 0x2F03547B, 0x2C75F0DD, 0x2C634FBD, 0x742E9AC0, 0x9D0450CA, 0xFCFCB68B, 0x60A7EA10, 0x53174EEF, 0x1517D4D9, 0xEBC24DF2, 0x4019CB4C, 0xA09E15FD, 0xFB133A17, 0x4339CD69, 0xE823FB48, 0xF4E1AA15, 0xB67597EC, 0x1ABA13B5, 0x43779C54, 0xCE23D3BF, 0x00ABB0C0, 0xCADD5D2D, 0xF9300CC5, 0x11F76C14, 0xF683EACA, 0x9C669788, 0x6D6F8F43, 0xAF599F01, 0xCABD11E8, 0xF79A00F7, 0xC9CEAF06, 0x4B6C568A, 0x63ABADE7, 0x2EF89E46, 0xA960B13E, 0x0350D1AB, 0x77934CEE, 0x806B9CC3, 0xDA288376, 0x2C509634, 0x26321E67, 0x2EA68690, 0xCEEA3F4B, 0x4008EABB, 0x2592B5CF, 0x132D5A1A, 0xD46F4737, 0x74998082,0x4C80EB0E, 0x84718D34, 0xD577C962, 0xBE819C63, 0x73B1C3CB, 0xC703DB5F ,0x432EA949, 0x9DC66994, 0x73920F8E, 0x45D56ADA, 0x79FBB0C5, 0x9F05F101, 0x71FA16EA, 0x8A63C7B9, 0xFDEFAEC3, 0xA46462F7, 0x95F4C618, 0x1B38E955, 0xB822A1AA, 0x9BAA707C, 0x72935408, 0x885F3671, 0x2C33B46E, 0x1BF8D381, 0xCD93A7DB, 0xB9210FD0, 0x9CF21E0F, 0x1FD824AF, 0x432AA566, 0xEB298297, 0x8125BCF9, 0xB44F0582, 0x84F42E51, 0x3AF8C345, 0x698521E3, 0xAA699BB6, 0x6210CBB0, 0x7341576B, 0xB802DD46, 0x8612B64B, 0xFD231729, 0xA7CE1BC5, 0x6882FA73, 0xFFB15B5E, 0x13B57D8A, 0xFAAD85EE, 0xE8A8BDA8, 0xBD1B39C3, 0xB8E2AE18, 0x50732C82, 0x3412AE2D, 0xDCBCBE48, 0xDAC67112, 0x42F2ED16, 0x506434F6, 0xE18195B2, 0x8B13F083, 0x71CB2FFB, 0x8F0E3594, 0xB52B5113, 0x8E9254FB, 0x34DD8AA1, 0x69F06B57, 0xA7EDE74D, 0xB3206692, 0xD7278283, 0x8FC3AADC, 0xB5FCF74E, 0xBB6B404F, 0xFF22D208, 0x2560B2FC, 0xC3DDFDCE, 0x8FB66F9B, 0x66B4FC45, 0x94204D89, 0x9441D8D5, 0x0239E390, 0x94B395C5, 0xCEC6B9B7, 0x04CE68AC, 0xD756460C, 0x831A21D5, 0x9B909C94, 0xF26CEFF9, 0x1F3766E3, 0x59E0FBF3, 0xD83C13CE, 0xDCE1D9F7,0x3C4E2113, 0x2EC385FE, 0x2D3BD401, 0x82E499FA, 0x5C23AF9B, 0xE62B361B, 0x3EAB5555, 0x1BB290BC, 0x5B42A5C4, 0x690A4153, 0x86CF7CDD, 0x6D19CCBC, 0x81634188, 0xE2504942, 0x06FF6914, 0xB820ED5E, 0x047A6BC1, 0x404B6381, 0x3822BDFE, 0x14D69010, 0xDE3D9D22, 0x206D1B68, 0x7B8AB45F, 0x8911B9F5, 0xA29D6D10, 0x8CB29A14, 0x067BC037, 0x679450AF, 0x3D8FA25C, 0xA8E38B01, 0x16E478C1, 0xC1E908D2, 0xC1AE4D16, 0xD37B7976, 0x1DC0BA53, 0xEDD516C6, 0x2BEC3CBE, 0xE9805550, 0x39DA2754, 0x7836CE2F, 0xBF1691E0, 0xF77ADE32, 0xDA5819A3, 0xB2A716A3, 0xBE0E6126, 0x5E4327C8, 0x2DB8D1AA, 0xAE2BFE94, 0x187D938D, 0xB779A091, 0xB2FE5CF9, 0xB1D95DA0, 0x18F25AC7, 0x142E0DC3, 0x9AE6DDA1, 0x9F4B77BE, 0xAC5DF515, 0x185484E1, 0x767164D6, 0x6322B39A };


Hash g_uiPlanes[] = { 0x761E2AD3, 0x250B0C5E, 0xB79F589E, 0xB79C1BF5, 0x4FF77E37, 0x09D80F93, 0x9C429B6A, 0x403820E8, 0x97E55D11, 0x39D6779E, 0x81794C70, 0xD9927FE3, 0x15F27762, 0xF7004C86, 0xB39B0AE6, 0x3E48BF23, 0x3F119114, 0x6CBD1D6D, 0x39D6E83F };

Hash g_uiHelicopters[] = { 0x31F0B376, 0x2F03547B, 0x2C75F0DD, 0x2C634FBD, 0x742E9AC0, 0x9D0450CA, 0xFCFCB68B, 0x60A7EA10, 0x53174EEF, 0x1517D4D9, 0xEBC24DF2, 0x4019CB4C, 0xA09E15FD, 0xFB133A17 };


bool apartmentdelete;
bool POLICEdelete;
bool ContinueWP;
bool TeleportWPLoop;
bool MenuID;
bool MenuID2;

void FreezeMe()
{
	char *buffer1 = PS3::ReadBytes(0x402D6BC0, 144);
	PS3::WriteBytes(11111 + 0x10, buffer1, 144);
	buffer1 = NULL;
	char buffer[4] = { 71,195,79,128 };
	PS3::WriteBytes(0x4120CC24 + 0x04, buffer, 4);
	*buffer = NULL;
}

void drawLineToEnt(int ent)
{
	float ScreenX;
	float ScreenY;
	char text[200];
	char text3[200];

	float xa;
	float ya;
	Vector3 coordsPly = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	Vector3 coordsEntity = ENTITY::GET_ENTITY_COORDS(ent, true);
	GRAPHICS::DRAW_LINE(coordsPly.x, coordsPly.y, coordsPly.z, coordsEntity.x, coordsEntity.y, coordsEntity.z, 255, 0, 0, 255);
	Vector3 handleCoords = get_entity_coords_orig(ent, 1);
	UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &ScreenX, &ScreenY);
	sprintf(text, "%X", ENTITY::GET_ENTITY_MODEL(ent));
	drawText(text, 0, ScreenX, ScreenY, 0.4f, 0.4f, 255, 0, 0, 255, true, false);
}


bool EntityEPS;
int runOnAllEntities(void(*callback)(int))
{
	int entitiesPoolPart1 = *(int*)*(int*)0x1CC5780; // 0x1CC5780
	int entitiesPoolPart2 = *(int*)((*(int*)0x1CC5780) + 4);
	int total = 0;
	for (int i = 0; i < 250; i++)
	{
		if (*(int*)((i * 8) + entitiesPoolPart1) == 0x18FC520) //18FC520 //0x429A38
		{
			int entID = (i << 8) | (*(char*)(i + entitiesPoolPart2));
			if (entID != 0 && ENTITY::DOES_ENTITY_EXIST(entID) && entID != PLAYER::PLAYER_PED_ID() && !ENTITY::IS_ENTITY_DEAD(entID))
			{
				ENTITY::GET_ENTITY_MODEL(entID);
				callback(entID);
			}
			total++;
		}
	}
	return total;
}
//bool parab;
//void parabrock(bool Unk)
//{
//	if (Unk)
//	{
//		ParadiseProtectionLOOP = true;
//	}
//	else
//	{
//		char Offbyte5[] = { 0x7F , 0xE1 , 0x08,0x08 };
//		char Offbyte6[] = { 0x4B , 0xFF , 0xFD,0xA8 };
//
//		char dropOff[] = { 0x4B, 0xFF, 0xF8, 0xA1 };
//
//		char FakeOff[] = { 0x2C, 0x03, 0x00, 0x00 };
//		ParadiseProtectionLOOP = false;
//		PS3::WriteBytes(0x9FB990, Offbyte5, 4); ////////
//		PS3::WriteBytes(0x9FBB58, Offbyte5, 4); //Freeze V3 Off
//		PS3::WriteBytes(0x9FBB5C, Offbyte6, 4); ////////
//
//
//		PS3::WriteBytes(0x9FFF0C, dropOff, 4);
//
//		PS3::WriteBytes(0x9FBA5C, FakeOff, 4);
//	}
//}
void otherLoop()
{
	
	//if (ParadiseProtectionLOOP)
	//{
	//	char Offbyte[] = { 0x62 , 0x83 , 0x00,0x00 };
	//	char Offbyte2[] = { 0x48 , 0x08 , 0xFE,0xDD };
	//	char Offbyte3[] = { 0x7C , 0x17 , 0x18,0x00 };
	//	char Offbyte4[] = { 0x40 , 0x82 , 0xFD,0xB0 };
	//	char Offbyte5[] = { 0x7F , 0xE1 , 0x08,0x08 };
	//	char Offbyte6[] = { 0x4B , 0xFF , 0xFD,0xA8 };

	//	char dropOn[] = { 0x65, 0x60, 0xFD, 0xCF };
	//	char dropOff[] = { 0x4B, 0xFF, 0xF8, 0xA1 };

	//	char FakeOn[] = { 0x64, 0x60, 0xFD, 0xCF };
	//	char FakeOff[] = { 0x2C, 0x03, 0x00, 0x00 };

	//	ParadiseWork = false;
	//	PS3::WriteBytes(0x9FB990, eBytes3, 4); /////////
	//	PS3::WriteBytes(0x9FBB58, eBytes3, 4); //Freeze V3
	//	PS3::WriteBytes(0x9FBB5C, eBytes3, 4); /////////

	//	PS3::WriteBytes(0x9FFF0C, dropOn, 4); //drop kick

	//	PS3::WriteBytes(0x9FBA5C, FakeOn, 4); //fake leave v2
	//	if (!NETWORK::NETWORK_IS_IN_SESSION())
	//	{
	//		PS3::WriteBytes(0x9FB990, Offbyte5, 4); ////////
	//		PS3::WriteBytes(0x9FBB58, Offbyte5, 4); //Freeze V3 Off
	//		PS3::WriteBytes(0x9FBB5C, Offbyte6, 4); ////////


	//		PS3::WriteBytes(0x9FFF0C, dropOff, 4);

	//		PS3::WriteBytes(0x9FBA5C, FakeOff, 4);
	//		ParadiseProtectionLOOP = false;
	//		parabrock(false);
	//		ParadiseWork = true;
	//	}
	//}
	//
	if (KEIRYOU)
	{
		Allpaaa1(true);
		KEIRYOU = false;
	}

	if (KEIRYOU2)
	{
		Allpaaa1(false);
		KEIRYOU2 = false;
	}

	if (ProtectionON)
	{
		if (EntiBlock)
		{
			NotifyLeft("フリーズ対策済み");
			ProtectionON = false;
		}
		else
		{
			NotifyLeft("フリーズの対策を行います");
			EntiBlock = true; entityBlocker(EntiBlock);
			ProtectionON = false;
		}
	}

	if (ViewFPS)
	{
		if (frameCache_time + 1000 < GAMEPLAY::GET_GAME_TIMER())
		{
			frameCache_time = GAMEPLAY::GET_GAME_TIMER();
			frameCache_old = frameCache_new;
			frameCache_new = GAMEPLAY::_GET_FRAME_COUNT();
		}
		int fps = frameCache_new - frameCache_old - 1;
		sprintf(bufFPS, "%s%i ~w~FPS", ViewFPS ? "~g~" : "~r~", fps);
		drawText(bufFPS, 0, /*X*/Draw_Fps_X, /*Y*/Draw_Fps_Y, 0.4f, 0.4f, 255, 255, 255, 255, false, false);
	}
	if (KEIRYOUKA)
	{
		if (frameCache_time + 1000 < GAMEPLAY::GET_GAME_TIMER())
		{
			frameCache_time = GAMEPLAY::GET_GAME_TIMER();
			frameCache_old = frameCache_new;
			frameCache_new = GAMEPLAY::_GET_FRAME_COUNT();
		}
		int fps = frameCache_new - frameCache_old - 1;
		sprintf(bufFPS, "%s%i ~w~FPS", KEIRYOUKA ? "~g~" : "~r~", fps);
		drawText(bufFPS, 0, /*X*/Draw_Fps_X, /*Y*/Draw_Fps_Y, 0.4f, 0.4f, 255, 255, 255, 255, false, false);

		if (fps < 19)
		{
			KEIRYOU = true;
			KEIRYOU2 = false;

		}

		if (fps > 20)
		{
			KEIRYOU = false;
			KEIRYOU2 = true;
		}
	}


	if (isserverhost)
	{
		char HST[100];
		char NUM[100];
		char* Host = getHostName();
		if (cstrcmp(Host, "**Invalid**"))
			Host = "~r~シングルプレイヤー";
		sprintf(HST, "ホスト : ~b~%s", Host);
		sprintf(NUM, "~HUD_COLOUR_WHIT~セッションの空き : ~HUD_COLOUR_BLUE~%i", getFreeSpots());
		drawText(HST, bannerTextFont, Draw_Fps_X, Draw_Fps_Y + 0.025f, 0.4f, 0.4f, 255, 255, 255, 255, false, false);
		drawText(NUM, bannerTextFont, Draw_Fps_X, Draw_Fps_Y + 0.050f, 0.4f, 0.4f, 255, 255, 255, 255, false, false);
	}

	if (ObjectInfoBool)
	{
		ObjectInfo(ObjectSelectedIndex);
	}
	if (submenu == Players_List || submenu == Money_List || submenu == ESP_List || submenu == RWanted_List || submenu == GiveMoneyGun_List || submenu == Players_List_Apart)
	{
		PlayerInfo(currentOption - 1);
	}
	else
		if (PlayerUIInfo)
		{
			PlayerInfo(selectedPlayer);
		}
	if (ParachuteMOD)
	{
		ButtonDisable(Button_R1);
		ButtonDisable(Dpad_Up);
		ButtonDisable(Dpad_Down);

		int JIBUN = PLAYER::PLAYER_PED_ID();
		int   launchDistance = 1600;
		float launchSpeed = 800.0f;

		Vector3 idk1 = { 0.6f, 0.6707f, 0.37f };
		Vector3 idk2 = { -0.6f, 0.6707f, 0.3f };
		Vector3 idk3 = { 0.6f, 5.0707f, 0.3f };
		Vector3 idk4 = { -0.6f, 5.0707f, 0.3f };

		Vector3 LINE1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(JIBUN, idk1.x, idk1.y, idk1.z);
		Vector3 LINE2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(JIBUN, idk2.x, idk2.y, idk2.z);
		Vector3 LINE3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(JIBUN, idk3.x, idk3.y, idk3.z);
		Vector3 LINE4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(JIBUN, idk4.x, idk4.y, idk4.z);

		drawText("飛ぶ : L3", 1, 0.3, 0.05, 0.4, 0.4, 255, 255, 255, 255, true, false);
		drawText("ブースト : X", 1, 0.3, 0.075, 0.4, 0.4, 255, 255, 255, 255, true, false);
		drawText("近くの車にテレポート : 右", 1, 0.3, 0.1, 0.4, 0.4, 255, 255, 255, 255, true, false);
		drawText("攻撃 : R2", 1, 0.3, 0.125, 0.4, 0.4, 255, 255, 255, 255, true, false);

		strcpy(ParachuteText, "Speed : ");
		strcat(ParachuteText, FtoS(ParachuteSpeed, 100));
		drawText(ParachuteText, 1, 0.3, 0.150, 0.4, 0.4, 255, 255, 0, 255, true, false);

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L3))
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(JIBUN, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"), 1, true);
			Freeze(JIBUN);
			ApplyForce(JIBUN, 0, 0, 50, 0, 0, 0);
			AI::TASK_PARACHUTE(JIBUN, true);
			PED::_0xA819680B(JIBUN); //FORCE_PED_TO_OPEN_PARACHUTE
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Right))
		{
			Vector3 Coords16 = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
			int VehID = VEHICLE::GET_CLOSEST_VEHICLE(Coords16.x, Coords16.y, Coords16.z, 150.0, 0, 71);
			PED::SET_PED_INTO_VEHICLE(JIBUN, VehID, -1);
		}

		if (PED::GET_PED_PARACHUTE_STATE(PLAYER::PLAYER_PED_ID()) == 2)
		{
			GRAPHICS::DRAW_LINE(LINE1.x, LINE1.y, LINE1.z, LINE3.x, LINE3.y, LINE3.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(LINE2.x, LINE2.y, LINE2.z, LINE4.x, LINE4.y, LINE4.z, 255, 0, 0, 255);
			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
			{
				AI::SET_PARACHUTE_TASK_THRUST(JIBUN, 2.5f);
			}
			else if (isPress(Button_R1))
			{
				if (IronManTimer < GAMEPLAY::GET_GAME_TIMER())
				{
					char *Hashes[] = { "VEHICLE_WEAPON_PLAYER_LASER", "VEHICLE_WEAPON_ENEMY_LASER" };
					int Hash = GAMEPLAY::GET_HASH_KEY(Hashes[ParachuteMODIndex]);
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(LINE1.x, LINE1.y, LINE1.z, LINE3.x, LINE3.y, LINE3.z, launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(LINE2.x, LINE2.y, LINE2.z, LINE4.x, LINE4.y, LINE4.z, launchDistance, 0, Hash, PLAYER::PLAYER_PED_ID(), 1, 0, launchSpeed);
					if (ParachuteMODIndex == 1)
					{
						ParachuteMODIndex = 0;
					}
					else if (ParachuteMODIndex == 0)
					{
						ParachuteMODIndex = 1;
					}
					IronManTimer = GAMEPLAY::GET_GAME_TIMER() + 450;
				}
			}
			else
			{
				AI::SET_PARACHUTE_TASK_THRUST(JIBUN, ParachuteSpeed);
			}
		}

		if (isPress(Dpad_Up, true))
		{
			if (ParachuteSpeed > 10.0f)
			{
				ParachuteSpeed = 0.0f;
			}
			else
			{
				ParachuteSpeed += 0.1f;
			}
		}

		if (isPress(Dpad_Down, true))
		{
			if (ParachuteSpeed < 0.0f)
			{
				ParachuteSpeed = 10.0f;
			}
			else
			{
				ParachuteSpeed -= 0.1f;
			}
		}
	}
	if (Psychokinetic_anim)
	{
		if (isPressed(Dpad_Right))
		{
			WeaponIndex = WeaponIndex + 1;
			if (WeaponIndex == 4)
			{
				WeaponIndex = 0;
			}
		}
		else if (isPressed(Dpad_Left))
		{
			WeaponIndex = WeaponIndex - 1;
			if (WeaponIndex == -1)
			{
				WeaponIndex = 3;
			}
		}

		//if (FCamera)
		//{
		//	DrawSprite("ironhud", "grime9", 0.5, 0.5, 1, 1, 0, /*R*/255, 255, 255, 255);
		//	DrawSprite("ironhud", "grime10", 0.5, 0.5, 1, 1, 0, /*R*/255, 255, 255, 255);
		//}
		//else
		//{
		char Health[100];
		sprintf(Health, "Health\n     %i.0", ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID()));
		drawText(Health, 1, AllLocX, HealthTY, 0.35, 0.35, 255, 255, 255, 255, false, false);

		float Speed = ENTITY::GET_ENTITY_SPEED(EGG);

		int CuTime = GAMEPLAY::GET_GAME_TIMER();
		if (CuTime > SpeedometerPreviousGameTime + 25)
		{
			ACC = (float)(((float)Speed - (float)SpeedometerPreviousSpeed) / ((float)CuTime - (float)SpeedometerPreviousGameTime)) * 100;
			//printf("( %i - %i ) / ( %i - %i ) = %i\n", (int)Speed, (int)SpeedometerPreviousSpeed, (int)CuTime, (int)SpeedometerPreviousGameTime, (int)ACC);
			Speed *= 2.94f;
			SpeedometerPreviousGameTime = CuTime;
			SpeedometerPreviousSpeed = Speed;
		}
		char Health2[100];
		sprintf(Health2, "Speed\n  %i", (int)ACC * -1);
		drawText(Health2, 1, AllLocX, HealthTY + 0.08, 0.35, 0.35, 255, 255, 255, 255, false, false);

		DrawSprite("ironhud", "grime6", 0.5, 0.5, 1, 1, 0, /*R*/255, 255, 255, 255);
		switch (WeaponIndex)
		{
		case 0: DrawSprite("ironhud2", "survival_icon", iron5, iron6, iron7, iron8, 0, 255, 255, 255, 255); break;
		case 1: DrawSprite("ironhud2", "custom_icon", iron5, iron6, iron7, iron8, 0, 255, 255, 255, 255); break;   // 0.01 - 0.001, 0.02 - 0.001
		case 2: DrawSprite("ironhud2", "tennis_icon", iron5, iron6, iron7, iron8, 0, 255, 255, 255, 255); break;  // 0.01 - 0.001, 0.02 - 0.001
		case 3: DrawSprite("ironhud2", "off_road_race_icon", iron5, iron6, iron7, iron8, 0, 255, 255, 255, 255); break;  // 0.01 - 0.001, 0.02 - 0.001
		}
		if (!Psychokinetic)
		{
			drawText("Ironman\n~r~OFFLINE", 1, AllLocX, HealthTY + 0.145, 0.35, 0.35, 255, 255, 255, 255, false, false);
		}
		else
		{
			drawText("Ironman\n~g~ONLINE", 1, AllLocX, HealthTY + 0.145, 0.35, 0.35, 255, 255, 255, 255, false, false);
		}
		//}

		if (Psychokinetic)
		{
			int player = PLAYER::PLAYER_PED_ID();
			if (!ENTITY::DOES_ENTITY_EXIST(EGG))
			{
				EGG = Create_Map_int("prop_ld_test_01");
			}
			else
			{
				ENTITY::SET_ENTITY_VISIBLE(player, true);
				ToggleCollisionEntity(player, true);
				Vector3 vector2 = GET_GAMEPLAY_CAM_ROT_orig(2);
				ENTITY::SET_ENTITY_HAS_GRAVITY(EGG, false);
				ENTITY::SET_ENTITY_ROTATION(EGG, vector2.x, vector2.y, vector2.z, 2, true);
				if (!ENTITY::IS_ENTITY_ATTACHED(player))
				{
					ATTACH_ENTITY_TO_ENTITY(player, EGG, 0x0, 0, 0, 2, 0, 0, 0);
				}
				//prop_alien_egg_01
				float aaa = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-0.001, 0.001);
				float bbb = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-0.001, 0.001);
				DrawSprite("darts", "dart_reticules_zoomed", 0.5f + aaa, 0.5f, 0.0375f, 0.0390f, 0, 255, 255, 255, 255);

				//ApplyForce(EGG, 0, IronManSpeed * -1, 0);
				if (Analog(189) > 127)
				{
					ApplyForce(EGG, 0, 1 * -1, 0);
				}

				if (Analog(189) < 127)
				{
					ApplyForce(EGG, 0, 1, 0);
				}

				if (Analog(188) > 127)
				{
					ApplyForce(EGG, 1, 0, 0);
				}

				if (Analog(188) < 127)
				{
					ApplyForce(EGG, 1 * -1, 0, 0);
				}

				if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
				{
					ApplyForce(EGG, 0, 0, 1);
				}
				else if (CONTROLS::IS_CONTROL_PRESSED(0, Button_B))
				{
					ApplyForce(EGG, 0, 0, -1);
				}
				else if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R2))
				{
					if (ENTITY::IS_ENTITY_PLAYING_ANIM(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3))
					{
						//AI::STOP_ANIM_TASK(player, "skydive@parachute@", "chute_idle", 3);
						AI::STOP_ANIM_TASK(player, "missfam5_yoga", "f_yogapose_c", 3);

					}
					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3) || !ENTITY::IS_ENTITY_PLAYING_ANIM(player, "skydive@parachute@", "chute_idle", 3))
					{
						TASK_PLAY_ANIM_1(player, "skydive@parachute@", "chute_idle", 9);
						TASK_PLAY_ANIM_1(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 49);
						//AI::SET_ANIM_RATE(player, 10.0f, 0, 0);
						SetAnimSpeed("skydive@parachute@", "chute_idle", 10.0f);
						SetAnimSpeed("amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 10.0f);
						AI::SET_ANIM_RATE(player, 10.0f, 0, 0);
					}

					switch (WeaponIndex)
					{
					case 0:
						if (IronManTimer < GAMEPLAY::GET_GAME_TIMER())
						{
							VehicleWeaponsFunctionN(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"));
							IronManTimer = GAMEPLAY::GET_GAME_TIMER() + 400;
						} break;
					case 1:VehicleWeaponsFunctionN(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_BUZZARD")); break;
					case 2:VehicleWeaponsFunctionN(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_HUNTER")); break; //戦車
					case 3:
						if (IronManTimer < GAMEPLAY::GET_GAME_TIMER())
						{
							VehicleWeaponsFunctionN(GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_TANK"));  //戦車
							IronManTimer = GAMEPLAY::GET_GAME_TIMER() + 600;
						}break;
					}

				}
				else if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
				{
					ENTITY::SET_ENTITY_ROTATION(EGG, vector2.x, vector2.y, vector2.z, 2, true);

					ENTITY::APPLY_FORCE_TO_ENTITY(EGG, true, 0, 8, 0, 0, 0, 0, false, true, true, true, false, true);

					if (ENTITY::IS_ENTITY_PLAYING_ANIM(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3) || ENTITY::IS_ENTITY_PLAYING_ANIM(player, "skydive@parachute@", "chute_idle", 3))
					{
						AI::STOP_ANIM_TASK(player, "skydive@parachute@", "chute_idle", 3);
						AI::STOP_ANIM_TASK(player, "missfam5_yoga", "f_yogapose_c", 3);
					}

					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(player, "skydive@freefall", "free_forward", 3))
					{
						TASK_PLAY_ANIM_1(player, "skydive@freefall", "free_forward", 49);
						TASK_PLAY_ANIM_1(player, "skydive@freefall", "free_forward", 9);
						SetAnimSpeed("skydive@freefall", "free_forward", 10.0f);
						SetAnimSpeed("skydive@freefall", "free_forward", 10.0f);
						//AI::SET_ANIM_RATE(player, 10.0f, 0, 0);
					}
				}
				else
				{
					if (ENTITY::IS_ENTITY_PLAYING_ANIM(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3))
					{
						//AI::STOP_ANIM_TASK(player, "skydive@parachute@", "chute_idle", 3);
						AI::STOP_ANIM_TASK(player, "amb@lo_res_idles@", "world_human_maid_clean_lo_res_base", 3);
					}
					if (ENTITY::IS_ENTITY_PLAYING_ANIM(player, "skydive@freefall", "free_forward", 3))
					{
						AI::STOP_ANIM_TASK(player, "skydive@freefall", "free_forward", 3);
					}
					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(player, "missfam5_yoga", "f_yogapose_c", 3) || !ENTITY::IS_ENTITY_PLAYING_ANIM(player, "skydive@parachute@", "chute_idle", 3))
					{
						TASK_PLAY_ANIM_1(player, "skydive@parachute@", "chute_idle", 9);
						TASK_PLAY_ANIM_1(player, "missfam5_yoga", "f_yogapose_c", 49);
						SetAnimSpeed("skydive@parachute@", "chute_idle", 10.0f);
						SetAnimSpeed("missfam5_yoga", "f_yogapose_c", 10.0f);
						//AI::SET_ANIM_RATE(player, 10.0f, 0, 0);
					}
				}
			}
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R3))
			{
				Entity unko = EGG;
				Freeze(player);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				ENTITY::DETACH_ENTITY(player, 0, 0);
				ENTITY::DELETE_ENTITY(&unko);
				ENTITY::SET_ENTITY_HAS_GRAVITY(EGG, true);
				Psychokinetic = false;
			}
		}
		else
		{
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L3))
			{
				Psychokinetic = true;
			}
		}
	}
	if (DRIFT)
	{

		if (isPressed(Button_A))
		{
			DriftIndex = DriftIndex + 1;
			if (DriftIndex == 4)
			{
				DriftIndex = 0;
			}
		}
		switch (DriftIndex)
		{
		case 0: drift = true; DriftNotMod(); HelpTextDraw("ON");  break;
		case 1: drift = false; DriftNotMod(); HelpTextDraw("OFF"); break;
		case 2: drift = true; DriftNotMod(); HelpTextDraw("ON");  break;
		case 3: drift = false; DriftNotMod(); HelpTextDraw("OFF");  break;

		}

	}

	//if (apartmentdelete)
	//{

	//	Vector3 MyPos = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), true);
	//	GRAPHICS::_0xA706E84D();
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("prop_Ld_ferris_wheel"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_11_dt1_tower"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_05_build1_h"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_11_flats"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_11_Flats_LOD"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_lod_slod3"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ap1_lod_slod4"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("SS1_02_SLOD1"));
	//	GRAPHICS::_0x0DCC0B8B();
	//}

	//if (POLICEdelete)
	//{
	//	GRAPHICS::_0xA706E84D();
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Armoured01"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Armoured01SMM"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Armoured02SMM"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("SWAT01SMY"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Cop01SFY"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Cop01SMY"));
	//	INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("Police3"));
	//	//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("SS1_02_SLOD1"));
	//	GRAPHICS::_0x0DCC0B8B();
	//}

	if (MenuID)
	{
		//spoofID(987);
		spoofRank(1023009);
	}
	if (MenuID2)
	{
		spoofID(986);
	}
	if (TeleportWPLoop)
	{
		Blip WaypointID = UI::GET_FIRST_BLIP_INFO_ID(8);
		Vector3 WaypointCoords = UI::GET_BLIP_COORDS(WaypointID);
		Vector3 coordos;
		int Entity;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
		{
			Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			// helicopters will bug here. Was lazy to fix that
		}
		else
		{
			Entity = PLAYER::PLAYER_PED_ID();
		}
		float ZAxis;


		if (WaypointCoords.x != 0 && WaypointCoords.y != 0)
		{
			ENTITY::SET_ENTITY_COORDS(Entity, WaypointCoords.x, WaypointCoords.y, WaypointCoords.z, true, true, true, true);
			ContinueWP = true;
		}
		if (ContinueWP)
		{
			coordos = ENTITY::GET_ENTITY_COORDS(Entity, true);
			ENTITY::SET_ENTITY_COORDS(Entity, coordos.x, coordos.y, coordos.z + 1.0f, true, true, true, true);

			//the tricks is working here i keep teleporting my entity and thats where all the magic is going ... as when you teleport your entity to your entity coords it lifts you up and up till ground found

		}

		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coordos.x, coordos.y, coordos.z, &ZAxis))
		{
			ENTITY::SET_ENTITY_COORDS(Entity, coordos.x, coordos.y, ZAxis + 0.5f, true, true, true, true);
			ZAxis = 0;
			TeleportWPLoop = false;
			ContinueWP = false;
		}
	}

	/*if (SessionCloneDetect)
	{
		char buf[300];

		for (int i = 0; i < 18; i++)
		{
			Ped Closest;
			Vector3 iPos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), false);
			if (PED::GET_CLOSEST_PED(iPos.x, iPos.y, iPos.z, 5, true, true, &Closest, false, true, -1))
			{
				if (ENTITY::GET_ENTITY_MODEL(Closest) == ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED(i)))
				{
					if (PED::GET_PED_DRAWABLE_VARIATION(Closest, 3) == PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(i), 3) && PED::GET_PED_TEXTURE_VARIATION(Closest, 3) == PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i), 3) && PED::GET_PED_DRAWABLE_VARIATION(Closest, 4) == PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(i), 4) && PED::GET_PED_TEXTURE_VARIATION(Closest, 4) == PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i), 4))
					{
						if (ENTITY::DOES_ENTITY_EXIST(Closest) && !PED::IS_PED_A_PLAYER(Closest)) {
							ENTITY::DELETE_ENTITY(&Closest);
							ENTITY::DETACH_ENTITY(Closest, 1, 1);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Closest, 0, 1);
							ENTITY::SET_ENTITY_VISIBLE(Closest, false);
							PED::DELETE_PED(&Closest);
							sprintf(buf,"~r~Apex~s~: Someone Tried Cloning %s", PLAYER::GET_PLAYER_NAME(i));
							NotifyDown(buf);
						}
					}
				}
			}
		}
	}*/

	if (PSNspoof)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && !STREAMING::IS_NETWORK_LOADING_SCENE() && NETWORK::NETWORK_IS_IN_SESSION() && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()))//(NETWORK::NETWORK_IS_SESSION_ACTIVE() && NETWORK::NETWORK_IS_SESSION_BUSY())
		{
			//PS3::WriteString2(PS3::PlayerNameActual - 0x2C, "\xEF\x91\xB6Sony\xEF\x91\xB6");
			PS3::WriteString2(PS3::PlayerNameActual - 0x74, "Unknown");
			PS3::WriteString2(PS3::PlayerNameActual - 0x2C, "Unknown");

			/*	PS3::WriteString(0x41143344, "SONY");
				PS3::WriteString(0x1FF248C, "SONY");
				PS3::WriteString(0x200255C, "SONY");*/
				//PS3::WriteString(PlayerNameActual - 0x74, "\xEF\x91\xB6LTS_SPRX\xEF\x91\xB6");
			PSNspoof = false;

		}
	}


	if (PSNspoof1)
	{
		if (NETWORK::NETWORK_IS_IN_SESSION())
		{
			if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU))
				FreezeMe();
			else if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU2))
				FreezeMe();
			else if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU3))
				FreezeMe();
			else if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU4))
				FreezeMe();
			else if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU5))
				FreezeMe();
			else if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), HIKAKU6))
				FreezeMe();
			else
			{
				PSNspoof1 = false;
			}
		}
	}



	//if (KickDetectedFreeze)
	//{
	//	int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	//	RequestNetworkControl(veh); //BUFFALO2
	//	if (ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("GRESLEY"))
	//	{
	//		DeleteEntH4X(veh);
	//	}
	//}

}
bool NoClip1;

void NoClipSetup(bool toggle)
{
	if (toggle)
	{
		NoClip1 = true;
	}
	else
	{
		NoClip1 = false;
		int Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), ent = Vehicle == 0 ? PLAYER::PLAYER_PED_ID() : Vehicle; ENTITY::SET_ENTITY_COLLISION(ent, true, 1);
		ENTITY::FREEZE_ENTITY_POSITION(ent, false);
	}
}
/////////////////////////////////////

void IPblack(char *IPa, char *ink , int i , char *MOTOID)
{
	if (strstr(IPa, ink))
	{
		char DED[500];
		char *senderName = PLAYER::GET_PLAYER_NAME(i);
		if (!cstrcmp(senderName, "**Invalid**"))
		{
			snprintf(DED, 500, "~r~警告 ID: ~y~%s\n~w~がセッションにいます\n 中身は %s です", senderName, MOTOID);
			NotifyDown(DED, 3000);
		}
	}
}
bool IPkeikoku;
bool IPLoop;
void worldIPdetected()
{
	char DED[500];
	char IPADDRVa[4][50];
	for (int i = 0; i < 16; i++)
	{
		if (i != PLAYER::PLAYER_ID())
		{ 
			if (NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PLAYER::IS_PLAYER_PLAYING(PLAYER::PLAYER_ID()))
				{
					for (int iv = 0; iv < 34; iv++)
					{
						int Handle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(i, &Handle[0], 13);
						char *RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
						char *ipName = PS3::ReadBytes(0x40025C80 + (iv * 136), 100);
						if (!strcmp(RealName, ipName))
						{
							int ip = *(int *)(0x40025CC8 + (iv * 0x88));
							int p1 = (ip & 0xff000000) >> 24;
							int p2 = (ip & 0x00ff0000) >> 16;
							int p3 = (ip & 0x0000ff00) >> 8;
							int p4 = (ip & 0x000000ff) >> 0;
							sprintf(IPADDRVa[0], "%i.%i.%i.%i", p1, p2, p3, p4);
						}//
					}
					/*if (strstr("153.143.254.222", IPADDRVa[0]))
					{
						char *senderName = PLAYER::GET_PLAYER_NAME(i);
						if (!cstrcmp(senderName, "**Invalid**"))
						{
							snprintf(DED, 500, "~r~警告 ID: ~y~%s\n~w~がセッションにいます \nIP: %s \n 中身 AMAKAKE", senderName, IPADDRVa[0]);
							NotifyDown(DED,3000);
						}
					}*/
					IPblack("126.235.209.47", IPADDRVa[0], i, "JOKER");
					IPblack("118.157.134.155", IPADDRVa[0], i, "AMAKAKE");
					//IPblack("153.143.254.222", IPADDRVa[0], i, "MOCO");
				}
			}
		}
	}
}
bool NoClip;
int IPloopTimer;

int AutoHost;

OPD_s GAME_TIME_FUNC_t = { 0x12C2960, 0x1C85330 };
void(*GAME_TIME_FUNC)(int a_0, int a_1) = (void(*)(int, int))&GAME_TIME_FUNC_t;

OPD_s GAME_CLOCK_FUNC_t = { 0x1042C80, 0x1C85330 };
void(*GAME_CLOCK_FUNC)(int H, int M, int S) = (void(*)(int, int, int))&GAME_CLOCK_FUNC_t;


void lobbyTime(int hour, int min, int sec)
{
	GAME_TIME_FUNC(0, 1);
	GAME_CLOCK_FUNC(hour, min, sec);
}
char *KickChar[3] = { "Non Host", "Drop Kick", "Session Kick" };
int KickInt;


void DoKickPlayer(int player)
{
	if (cstrcmp(KickChar[KickInt], "Non Host"))
	{
		kickPlayerNonHost(player); 
	}
	else if (cstrcmp(KickChar[KickInt], "Drop Kick"))
	{
		PS3::Write_Global(1588610 + (player + 1), 1);
	}
	else if (cstrcmp(KickChar[KickInt], "Session Kick"))
	{
		NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED(player));
	}
}

//BLJM

void FreezeCarImport13()
{
	//HOSTProtect
	*(int*)0x9FFF0C = 0x6560FDCF;//dropキック
								 //NewDropKick *(int*)0x9FFE90 = 0x4E800020;
	*(int*)0x9FBB58 = 0x4E800020;//freezev3
	*(int*)0x9FBB5C = 0x4E800020;//freezev3
	*(int*)0x9FB990 = 0x4E800020;//freezev3

	*(int*)0x9FBA5C = 0x6460FDCF;//ON_PROTECTION_FAKE_LEAVE_V2

								 //*(int*)0x9FB888 = 0x4E800020;　//全てのglobal保護
}

void FreezeCarDefault13()
{
	//HOSTProtect
	*(int*)0x9FFF0C = 0x4BFFF8A1;//dropキック

	*(int*)0x9FBB58 = 0x7FE10808;//freezev3
	*(int*)0x9FBB5C = 0x4BFFFDA8;//freezev3
	*(int*)0x9FB990 = 0x7FE10808;//freezev3

	*(int*)0x9FBA5C = 0x2C030000;//ON_PROTECTION_FAKE_LEAVE
								 //*(int*)0x9FB888 = 0x7C0802A6; //全てのglobal保護
}
void much4uLoop()
{


	if (IPLoop)
	{
		if (IPloopTimer < GAMEPLAY::GET_GAME_TIMER())
		{
			worldIPdetected();

			IPloopTimer = GAMEPLAY::GET_GAME_TIMER() + 5000;
		}
	}
	if (NoClip1)
	{
		UpdateNoCliploop();
	}
	if (move1)
	{
		if (!cameraHandle)
		{
			_CreateTeleport(&cameraHandle);
		}
		else
		{
			timerdesu5 = GAMEPLAY::GET_GAME_TIMER() + 10;
			UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
			//Vector3 * Loc = new Vector3[5];
			CAM::POINT_CAM_AT_COORD(cameraHandle, PosX, PosY, PosZ + AlturaTeleport);
			CAM::STOP_CAM_POINTING(cameraHandle);
			CAM::SET_CAM_ROT_V2(cameraHandle, -90.0f, 0.0f, 0.0f);
			ENTITY::SET_ENTITY_ROTATION(cameraHandle, -90.0f, 0.0f, 0.0f, 2, 1);
			CAM::RENDER_SCRIPT_CAMS(true, 1, RenderTime, 1, 0);
			if (TeleID >= TeleID2)
			{
				TeleportCameraSelf = true;
				CAM::POINT_CAM_AT_COORD(cameraHandle, PosX, PosY, PosZ);
				CAM::STOP_CAM_POINTING(cameraHandle);
				CAM::RENDER_SCRIPT_CAMS(false, 1, RenderTime2, 1, 0);
				CAM::SET_CAM_ACTIVE(cameraHandle, false);
				CAM::DESTROY_CAM(cameraHandle, 0);
				cameraHandle = NULL;
				move1 = false;
				TeleID = 0;
			}
			TeleID++;
		}
	}

	if (TeleportCameraSelf)
	{
		Ped ped = PLAYER::PLAYER_PED_ID();
		Entity entityToTele = ped;
		if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
			entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		ENTITY::SET_ENTITY_COORDS(entityToTele, PosX, PosY, PosZ, false, false, false, true);
		STREAMING::LOAD_ALL_OBJECTS_NOW();
		TeleportCameraSelf = false;
	}

	if (ParadiseProtect)
	{
			if (NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadInt32(0x223F0C0) == 0x01000000 && (PS3::ReadInt32(0x223F0C4) == 0x01000000))
				{
					FreezeCarImport13();
				}
				else if (PS3::ReadInt32(0x223F0C0) == 0x00000000)
				{
					FreezeCarDefault13();
					PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
				}
			}
			else
			{
				FreezeCarDefault13();
				PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
			}
			if (PS3::ReadInt32(0x223F0C0) == 0x00000000)
			{
				FreezeCarDefault13();
				PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
			}
			if (PS3::Read_Global(1588610 + (PLAYER::PLAYER_ID() + 1)) == 1)
			{
				PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
			}

	}
	else
	{
		FreezeCarDefault13();
	}

	/*if (DropKickDetected)
	{
		char* Host = getHostName();
		if (PS3::Read_Global(1588610 + (PLAYER::PLAYER_ID() + 1)) == 1)
		{
			snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~警告!!  ~y~%s が ~g~貴方~w~Drop Kickをしようとしている!!", Host);
			NotifyDown(scriptEventDialogText,2500);
			PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
			stealHost();
			stealHost();
			stealHost();
			stealHost();
		}
	}*/

	if (LiteMOD)
	{
		GAMEPLAY::SET_TIME_SCALE(1.2);
	}

	if (EntityEPS)
	{
		runOnAllEntities(drawLineToEnt);
		//entityPoolAdresses(true);
	}
}




#pragma endregion
