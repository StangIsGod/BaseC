#include <cell/cell_fs.h>
#include <spu_printf.h>
#include <sys/process.h>

#include <cell/cell_fs.h>
#include <sys/ss_get_open_psid.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>
#include <netex\libnetctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <json\json.h>
//#include <sys/ccapi.h>
//
//#include <math.h>
#pragma comment(lib, "net_stub")
#pragma comment(lib, "netctl_stub")

#include "math.h"
//*/
#include "ui.h"
#include <stdio.h>
#include "Tool.h"
#include "stdafx.h"
//#include "liblv2.h"
#include "network.h"
#include "nativeCaller.h"
#include "natives.h"
#include "opds.h"
#include "enums.h"
#include "Float.h"
#include "int.h"
#include "Bool.h"
#include "char.h"
#include "ByteWriter.h"
#include "MenuStrings.h"
#include "Functions.h"
#include "AddOptions.h"
#include "Xml.h"
#include "Injector.h"
//#include "xmlreader.h"
//#include "XmlR.h"

SYS_MODULE_INFO( Memories, 0, 1, 0);
SYS_MODULE_START( _Memories_prx_entry );

#define NOP 0x4E800020
#define R_NOP 0x7C0802A6


void Hook();
int waitTimeMain;
bool MainBoolImage = true;
//bool _true = true;
namespace Hooking
{
	void MainTheread(NativeArg_s* pArg)
	{
		int bOnline;
		bOnline = is_player_online_orig();
		pArg->SetRet(bOnline);

		//if (_true)
		//{
		//	int _PartA = PS3::ReadUInt32(AllEntity_A);

		//	if (_PartA > 0x20000000)
		//	{
		//		entitiesPoolPart1 = PS3::ReadUInt32(_PartA);
		//		entitiesPoolPart2 = PS3::ReadUInt32((_PartA)+4);
		//		printf("0x%X\n0x%X\n0x%X\n", _PartA, entitiesPoolPart1, entitiesPoolPart2);
		//		_true = false;
		//	}
		//}

		char *script = SCRIPT::GET_THIS_SCRIPT_NAME();
		if (!strcmp(script, "ingamehud"))
		{
			if (GAMEPLAY::GET_GAME_TIMER() > waitTimeMain)
			{
				much4uLoop();
				waitTimeMain = GAMEPLAY::GET_GAME_TIMER() + 10;
			}

			Hook();
			otherLoop();
		}
		
		//BOTTOMTEXT = GRAPHICS::REQUEST_SCALEFORM_MOVIE("text_input_box");
		BOTTOMTEXT = GRAPHICS::REQUEST_SCALEFORM_MOVIE("TEXTFIELD");
		Functions();

		//PS3::WriteString(0x1820630, "");//"**Invalid**" => "-"
	}
	void does_entity_exist(NativeArg_s* pArg)
	{
		Vector3 bGetEntityR;
		uint32_t Entity = pArg->GetArg<uint32_t>(0);
		int bGetEntityA = does_entity_exist_orig(Entity);
		pArg->SetRet(bGetEntityA);
		monitorButtons();
	}
	void get_max_wanted_level(NativeArg_s* pArg)
	{
		int bWanted;
		bWanted = GET_MAX_WANTED_LEVEL_orig();
		pArg->SetRet(bWanted);
	}
}
float _841000f = 0.866000f;

void Hook()
{
	if (submenu != Closed)
	{
		
		DrawingMenus::normalMenuActions();
		if (MenuInfoTimer < GAMEPLAY::GET_GAME_TIMER())
		{
#pragma region Menu本体
			// base background
			GRAPHICS::DRAW_RECT(0.825000f, 0.517500f - plusY, 0.225000f, 0.765000f, 20, 20, 25, menualpha);
			GRAPHICS::DRAW_RECT(posX, posY - plusY, scaleX, scaleY, 20, 20, 20, menualpha);
			DrawSprite("timerbars", "lhs_bg", 0.825000f, 0.511497f - plusY, 0.225000f, 0.788993f, 90, 138, 138, 138, 86); // fade effect ( hide some of our memes ight? )																											//background (top)
			GRAPHICS::DRAW_RECT(0.825000f, 0.517500f - plusY, 0.211000f, 0.733999f, 20, 20, 20, menualpha);
			GRAPHICS::DRAW_RECT(0.825000f, 0.862499f - plusY, 0.210000f, 0.001000f, 255, 255, 255, menualpha); // bottom white line
			GRAPHICS::DRAW_RECT(0.825000f, 0.273500f - plusY, 0.210000f, 0.001000f, 255, 255, 255, menualpha); // banner white line																			   //==== banner
			GRAPHICS::DRAW_RECT(0.823000f, 0.209500f - plusY, 0.129000f, 0.045000f, 45, 126, 255, 19); // blue BG under text... 


			drawText("GTA V ONLINE BLJM MOD MENU", 4, subtitleX, 0.239500f - plusY, 0.083000f, 0.311000f, 255, 255, 255, 255, false); // subtitle (underneath the title)

			/*drawText("~italic~Ver.1.0", 4, 0.724002f, 0.861492f - plusY, 0.085000f, 0.371999f, 255, 255, 255, 255, false); // Version*/
			drawText("~italic~Twitter : @stngsan", 4, _841000f, 0.860492f - plusY, 0.085000f, 0.370999f, 244, 244, 244, 255, false); // Team

			char buf[30];
			snprintf(buf, sizeof(buf), "Item : ~b~%i~w~/~b~%i", currentOption, optionCount);
			drawText2(buf, 6, 0.924999f, 0.246500f - plusY, 0.085000f - 0.03f, 0.357999f - 0.03f, 255, 255, 255, 255, 0, true);
			//==== banner

			if (optionCount > /* 16 */ maxOptions)
			{
				if (currentOption > /* 16 */ maxOptions)
				{
					//==== new scroller
					//GRAPHICS::DRAW_RECT(0.825000f, ((16 * 0.035f) + 0.273501f) - plusY, 0.193000f, 0.037000f, 45, 126, 255, 19); // Main

					GRAPHICS::DRAW_RECT(0.726002f, ((16 * 0.035f) + 0.262500f) - plusY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Left Corner
					GRAPHICS::DRAW_RECT(0.734001f, ((16 * 0.035f) + 0.250500f) - plusY, 0.016000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Left Corner

					GRAPHICS::DRAW_RECT(0.914999f, ((16 * 0.035f) + 0.294499f) - plusY - ScrollerY, 0.015000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
					GRAPHICS::DRAW_RECT(0.922999f, ((16 * 0.035f) + 0.281499f) - plusY - ScrollerY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
																																   //==== new scroller
				}
				else
				{
					//==== new scroller
					//GRAPHICS::DRAW_RECT(0.825000f, ((currentOption * 0.035f) + 0.273501f) - plusY, 0.193000f, 0.037000f, 45, 126, 255, 19); // Main

					GRAPHICS::DRAW_RECT(0.726002f, ((currentOption * 0.035f) + 0.262500f) - plusY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Left Corner
					GRAPHICS::DRAW_RECT(0.734001f, ((currentOption * 0.035f) + 0.250500f) - plusY, 0.016000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Left Corner

					GRAPHICS::DRAW_RECT(0.914999f, ((currentOption * 0.035f) + 0.294499f) - plusY - ScrollerY, 0.015000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
					GRAPHICS::DRAW_RECT(0.922999f, ((currentOption * 0.035f) + 0.281499f) - plusY - ScrollerY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
																																			  //==== new scroller
				}
			}
			else
			{
				//==== new scroller
				//GRAPHICS::DRAW_RECT(0.825000f, ((currentOption * 0.035f) + 0.273501f) - plusY, 0.193000f, 0.037000f, 45, 126, 255, 19); // Main

				GRAPHICS::DRAW_RECT(0.726002f, ((currentOption * 0.035f) + 0.262500f) - plusY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Left Corner
				GRAPHICS::DRAW_RECT(0.734001f, ((currentOption * 0.035f) + 0.250500f) - plusY, 0.016000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Left Corner

				GRAPHICS::DRAW_RECT(0.914999f, ((currentOption * 0.035f) + 0.294499f) - plusY - ScrollerY, 0.015000f, 0.003000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
				GRAPHICS::DRAW_RECT(0.922999f, ((currentOption * 0.035f) + 0.281499f) - plusY - ScrollerY, 0.002000f, 0.025000f, 0xFF, 0x69, 0xb4, 255); // Right Corner
																																		  //==== new scroller
			}
#pragma endregion
			MenuInfoTimer = GAMEPLAY::GET_GAME_TIMER() + 15;
		}
#pragma region infobox
		if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
		{
			drawText("説明", 0, infoTextXY.x, infoTextXY.y, infoTextSize, infoTextSize, 45, 255, 126, 255, true, false);
			GRAPHICS::DRAW_RECT(infoLineX - 0.001f, infoLineY, infoLineSizeX, infoLineSizeY, 20, 20, 20, 180); //Info Box line
			GRAPHICS::DRAW_RECT(infoTextLi.x, infoTextLi.y, infoTextLi.w, infoTextLi.z, 45, 126, 255, 19); //Info Box line
			GRAPHICS::DRAW_RECT(infoBox1.x, infoBox1.y, 0.001000f, 0.025000f, 255, 255, 255, 255); // Left Corner
			GRAPHICS::DRAW_RECT(infoBox2.x, infoBox2.y, 0.016000f, 0.002000f, 255, 255, 255, 255); // Left Corner

			GRAPHICS::DRAW_RECT(infoBox3.x, infoBox3.y, 0.015000f, 0.002000f, 255, 255, 255, 255); // Right Corner
			GRAPHICS::DRAW_RECT(infoBox4.x, infoBox4.y, 0.001000f, 0.025000f, 255, 255, 255, 255); // Right Corner

			GRAPHICS::_0x76C641E4(-0.0755f, -0.0755f, 0.0f, 0.0f);
			GRAPHICS::DRAW_SCALEFORM_MOVIE(BOTTOMTEXT, infoBoxX, infoBoxY, infoBoxSizeX /*0.224f*/, infoBoxSizeY, 255, 255, 255, 255, 0); // Info Box
			
			GRAPHICS::_0x3FE33BD6();
			GRAPHICS::_0x215ABBE8(BOTTOMTEXT, "SET_TEXT");
			set_text_component(infoText);
			GRAPHICS::_0x02DBF2D7();


		}
#pragma endregion
	}

#pragma region Tutorial
	Hash Hash = GAMEPLAY::GET_HASH_KEY("MPPLY_NO_MORE_TUTORIALS");
	bool _Value;
	STATS::STAT_GET_BOOL(Hash, &_Value, 1);
	if (!_Value || NETWORK::NETWORK_IS_IN_TUTORIAL_SESSION())
	{
		//STAT_SET_BOOL("MPPLY_NO_MORE_TUTORIALS", 1, 1);
		STATS::STAT_SET_BOOL(0xC9DAB8F, true, 1); //MP0_FM_TRIGTUT_DONE
		STATS::STAT_SET_BOOL((0x7B91ECE), true, 1); //MP0_FM_HOLDTUT_DONE
		STATS::STAT_SET_BOOL((0x58862927), true, 1);//MP0_FM_RACETUT_DONE
		STATS::STAT_SET_BOOL((0x93B408C4), true, 1);//MP0_FM_CMODTUT_DONE
		STATS::STAT_SET_BOOL((0x825CDA0C), true, 1);//MP0_NO_TUT_SPAWN
		STATS::STAT_SET_BOOL((0xD5680B05), true, 1);//MP0_FRONT_END_JIP_UNLOCKED
		STATS::STAT_SET_BOOL((0xE1DBECCF), true, 1);//MP0_FM_NOTUT_DONE
		STATS::STAT_SET_BOOL((0x791E04FA), true, 1);//MP0_FM_INTRO_CUT_DONE
		STATS::STAT_SET_BOOL((0xB19ABF2), true, 1); //MP0_FM_INTRO_MISS_DONE
		STATS::STAT_SET_BOOL((0xE077B8C5), true, 1);//MP1_FM_TRIGTUT_DONE
		STATS::STAT_SET_BOOL((0x5D2A52CF), true, 1);//MP1_FM_HOLDTUT_DONE
		STATS::STAT_SET_BOOL((0xE346B631), true, 1);//MP1_FM_RACETUT_DONE
		STATS::STAT_SET_BOOL((0xFC86A5C9), true, 1);//MP1_FM_CMODTUT_DONE
		STATS::STAT_SET_BOOL((0x5A283B59), true, 1);//MP1_NO_TUT_SPAWN
		STATS::STAT_SET_BOOL((0x16D62EE0), true, 1);//MP1_FRONT_END_JIP_UNLOCKED
		STATS::STAT_SET_BOOL((0xC7F1F5EC), true, 1);//MP1_FM_NOTUT_DONE
		STATS::STAT_SET_BOOL((0x91C5D62F), true, 1);//MP1_FM_INTRO_CUT_DONE
		STATS::STAT_SET_BOOL((0xA7B3D64C), true, 1);//MP1_FM_INTRO_MISS_DONE
		STATS::STAT_SET_BOOL((0xD07EE8D), true, 1); //MPPLY_FM_INTRO_CUT_DONE
		STATS::STAT_SET_BOOL((0x4EE04218), true, 1);//MPPLY_NO_MORE_TUTORIALS
	}
#pragma endregion

	/*ボタン表示*/

	optionCount = 0;
	SkipLoading();
	if (EnableAccountBool)
		EnableAccountLoop();

	if (!testBool)
	{
		if (PS3::ReadUInt32(0x3F8B10) != 0x60000000)
			PS3::WriteUInt32(0x3F8B10, 0x60000000);

		if (PS3::ReadUInt32(0x11355C8) != 0x2C05022B)
			PS3::WriteUInt32(0x11355C8, 0x2C05022B);

		if (PS3::ReadUInt32(0x11355C8) != 0x2C04022B)
			PS3::WriteUInt32(0x11355C8, 0x2C04022B);

		if (PS3::ReadUInt32(0x179F70) != 0x60000000)
			PS3::WriteUInt32(0x179F70, 0x60000000);
		if ((PS3::ReadUInt32(0x3F8B10) == 0x60000000) && (PS3::ReadUInt32(0x11355C8) == 0x2C05022B) && (PS3::ReadUInt32(0x11355C8) == 0x2C04022B) && (PS3::ReadUInt32(0x179F70) == 0x60000000))
			testBool = true;
	}
	//PS3::WriteUInt32(0x11355C8, 0x2C05022B);
	//PS3::WriteUInt32(0x11B26D8, 0x2C04022B);
	//PS3::WriteUInt32(0x179F70, 0x60000000); //Animal Freeze

	*(int*)(0x01C6C7E0) = *(int*)((int)&CHECK_EBOOT_SIZE);
	*(int*)((0x01C6C7E0 + 0x4)) = *(int*)((int)&CHECK_EBOOT_SIZE + 0x4);

	//runOnAllEntities1();
	if (isOnline())
	{
		if (!DeleteMenuID)
			PS3::Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 178 + 45, 0x5000);

		PS3::SetTunable(0x49, 0x3B9ACA00); //放置キック
		PS3::SetTunable(0x4A, 0x3B9ACA00); //放置キック
		PS3::SetTunable(0x4B, 0x3B9ACA00); //放置キック
		PS3::SetTunable(0x4C, 0x3B9ACA00); //放置キック

		PS3::SetGlobal(0x40001 + 0x69, 999999999, 0); //アンチタイムアウト
		PS3::SetGlobal(0x40001 + 0x6A, 999999999, 0); //アンチタイムアウト
		PS3::SetGlobal(0x40001 + 0x11F7, 999999999, 0); //アンチタイムアウト
	}

	if (PS3::ReadInt32(0x1CF74E4) != 0xEB3970)
		PS3::WriteInt32(0x1CF74E4, 0xEB3970);


	for (int i = 0; i < 18; i++)
	{
		Playername[i] = PLAYER::GET_PLAYER_NAME(i);
		if (i != PLAYER::PLAYER_ID())
		{
			if (ChatBypass)
			{
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(i, 1);
					NETWORK::_NETWORK_OVERRIDE_SEND_RESTRICTIONS(i, 1);
					NETWORK::NETWORK_OVERRIDE_CHAT_RESTRICTIONS(i, 1);
				}
				else
				{
					NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(i, 0);
					NETWORK::_NETWORK_OVERRIDE_SEND_RESTRICTIONS(i, 0);
					NETWORK::NETWORK_OVERRIDE_CHAT_RESTRICTIONS(i, 0);
				}
			}
		}
	}
	
	//*(int*)(0x1C4F5A0) = *(int*)((int)&_DROP_KICK_EVENT);
	//*(int*)((0x1C4F5A0 + 0x4)) = *(int*)((int)&_DROP_KICK_EVENT + 0x4);
	switch (submenu)
	{
#pragma region Closed
	case Closed:
		if (!DontViewOpenMenu)
		{
			drawText("~b~Re:Hyper Dx", bannerTextFont, 0.85, 0.08f + 0.2f, 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			drawText("Open Menu □ + Right", bannerTextFont, 0.85, 0.1f + 0.2f, 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(0.85, 0.1f + 0.2f, 0.14f, 0.08, 0, 0, 0, 160);
		}
		break;
#pragma endregion

#pragma region Main Menu
	case Main_Menu:
		/*
		char testtt[30];
		sprintf(testtt, "0x%X", errornum);
		drawText(testtt, 0, 0.5, 0.5, 0.4f, 0.4f, 255, 255, 255, 255, true);*/

		//DrawSprite("social_club2", "tour_image", 0.5, 0.5, MenuWidth, 0.083f, 0, 255, 255, 255, 255);
		ObjectUI = false;

		addTitle("メインメニュー");
		addSubmenuOption("セルフチート", Self_Options, "プレイヤー自身向けのチートです。\nSelf Option");
		addSubmenuOption("オンライン", OnlineMenu, "オンラインのプレイヤー向けのチートです。\nOnline Option");
		//addSubmenuOption("スポーン", Spawn_Menus, "車とかオブジェクトを出します。\nSpawner");
		addSubmenuOption("車 スポーン", VehicleSpawn, "車を出現させます。\nSpawn Vehicle");
		addSubmenuOption("車のチート", VehicleMenu, "車向けのチートです。\nVehicle Option");
		addSubmenuOption("テレポート", TeleportMenu, "様々なところへ移動するチートです。\nTeleport Option");
		addSubmenuOption("オブジェクト スポーン", ObjectSpawn, "物を出現させます\nSpawn Object");
		addSubmenuOption("マップ MOD", MapMods, "様々な地点にオブジェクトを生成します。");
		addSubmenuOption("武器", WeaponMenu, "武器に関するチートです。\nWeapon Option");
		addSubmenuOption("モデルチェンジ", ModelChanger, "姿を変更します。\nModel Option");
		addSubmenuOption("ファンメニュー", FunMenu, "チートを駆使した楽しいモードです。\nFun Option");
		addSubmenuOption("アニメーション", AnimatioNMenu, "アニメーション変更向けのチートです。\nAnimation Option");
		
		addSubmenuOption("プロテクション + 軽量化", ProtectionMenu__, "チーターからの様々な攻撃を無効化します。\nProtection Option");
		addSubmenuOption("リカバリー", RecoveryMenu, "アカウント代行向けのチートです。\nRecovery Option");
		addSubmenuOption("その他", MiscMenu, "FPS表示等の細かな設定です。\nMisc");
		addSubmenuOption("メニューの設定", Settings, "メニューを使いやすくするための設定です。\nSettings");
		if (isOnline() && _chat)
			addKeyboardOption("チャット送信", 6, "", 60, "みんなでチャットしよう！");

		switch (getOption())
		{
			
		}
		break;
#pragma endregion	

#pragma region _RCE
	case _RCE:
		addTitle("RCE");
		addOption("Step 1");
		addOption("Step 2");
		addOption("Step 3");
		switch (getOption())
		{
		case 1:
			
			//PS3::WriteUInt32(0x10054E00, 0x7c0802a6);
			//PS3::WriteUInt32(0x10054E04, 0x48268a3c);

			//7c 08 02 a6
			PS3::WriteUInt32(0x10054F00, 0x7c0802a6);
			PS3::WriteUInt32(0x10054F04, 0x38a000ff);
			PS3::WriteUInt32(0x10054F08, 0x3cc01005);
			PS3::WriteUInt32(0x10054F0C, 0x60c64300);
			PS3::WriteUInt32(0x10054F10, 0x98a60000);
			PS3::WriteUInt32(0x10054F14, 0x4e800020);
			break;

		case 2:

			break;

		case 3:
			PLAYER::GET_MAX_WANTED_LEVEL();
			break;
		}
		break;
#pragma endregion

#pragma region MapMods
	case MapMods:
		addTitle("マップ MOD");
		//addOption("チリアド グルグル", "by Eilish");
		addOption("空港", "by Eilish");
		addOption("LSC近く", "by Eilish");
		switch (getOption())
		{
		//case 1:MountainRace = true; break;
		case 1:AirRace = true; break;
		case 2:LSCRace = true; break;
		//case 2:MountainRace2 = true;
		//	mountain2_index = 0;
		//	break;
		}
		break;
#pragma endregion

#pragma region Spawn_Menus
	case Spawn_Menus:
		addTitle("スポーン");

		break;
#pragma endregion

#pragma region SelfOption
	case Self_Options:
		addTitle("セルフチート");
		addCheckOption("[無敵]検知される v1", NoRagdoll, "Detected Godmode v1");
		addCheckOption("[無敵]検知されにくい v2", GodMode, "Undetected Godmode v2");

		//addCheckOption("無敵", GodMode, "検知される無敵です。\nGodMode");
		addCheckOption("透明", Invisible, "プレイヤー自身が透明になります。\nInvisible");
		addCheckOption("手配度無効", Nocops, "手配度が上昇しなくなります。\nNo Cops");
		//test
		addCheckOption("スーパージャンプ", SuperJump, "跳躍力が上がります。\nSuperJump");
		//addCheckOption(test, SuperJump, "ジャンプ力が上昇します。\nSuper Jump");
		addCheckFloat("スーパーラン", SuperRun, &SuperRun_, 1.0f, 10.0f, 0.2f, "走る速度が上昇します。\nSuper Run");
		addCheckOption("ウルトララン", UltraRun, "スーパーランより早い");
		addCheckOption("ウルトラパンチ", UltraPunch, "殴った対象を吹っ飛ばします。\nUltra Punch(Address)");

		addCheckOption("爆発パンチ", ExplosionMelee, "殴った対象が爆発します。\nExplosion Melee");

		addCheckOption("レーダーにプレイヤーを表示", RevealPeople, "ゲーム内でレスターが使用している物です。\nRevealPeople");
		addCheckOption("レーダーから自身を消す", OffRader, "ゲーム内でレスターが使用する物です。\nOffRader");
		addCheckOption("警察が黙視", CopsTurnBlindEye, "手配度が上昇しません。\nCopsTurnBlindEye");
		addOption("ブルシャーク", "ブルシャーsクを拾った判定にします。\nBull Shark");
		addCheckOption("浮遊", Noclip[0], "L3スティックを前に倒すとカメラの方向へ進みます。\nNo Clip");
		addOption("ネームチェンジャー", "", "→→→");
		switch (getOption())

		{

		case 1:
			NoRagdoll = !NoRagdoll;
			if (!NoRagdoll)
			{
				ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 0, 0);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 0);
			}
			break;
		case 2:GodMode = !GodMode;
			if (GodMode)
			{
				addMessageShow("~y~*無敵*~w~を~g~有効化~w~しました。");
			}
			else
			{
				ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 0, 0);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 0);
				*(int*)0x10060000 = PLAYER::PLAYER_ID();
				uint uVar1 = Script_Inject::_PlayerIndexToPlayerAddress(*(int*)0x10060000);
				if (0x10000 < (uVar1 & 0xffffffff)) {
					*(uint*)(uVar1 + 0x170) = 328;
					*(uint*)(uVar1 + 0x174) = 328;
				}
				addMessageShow("~y~*無敵*~w~を~r~無効化~w~しました。");
			}
			break;
		case 3:Invisible = !Invisible;
			if (Invisible)
				addMessageShow("~y~*透明*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*透明*~w~を~r~無効化~w~しました。");
			break;

		case 4:Nocops = !Nocops;
			if (Nocops)
				addMessageShow("~y~*手配度*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*手配度*~w~を~r~無効化~w~しました。");
			break;

		case 5:SuperJump = !SuperJump;
			if (SuperJump)
				addMessageShow("~y~*スーパージャンプ*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*スーパージャンプ*~w~を~r~無効化~w~しました。");
			break;

		case 6:SuperRun = !SuperRun;
			if (!SuperRun)
			Script_Inject::SET_PLAYER_SPEED_MODIFIER(1.0f, PLAYER::PLAYER_ID());

			//if (!SuperRun)
			//	PS3::WriteFloat(0x411433DC, 1.00f);

			if (SuperRun)
				addMessageShow("~y~*スーパーラン*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*スーパーラン*~w~を~r~無効化~w~しました。");
			break;
		case 7:UltraRun = !UltraRun;
			if (UltraRun)
			{
				addMessageShow("~y~*ウルトララン*~w~を~g~有効化~w~しました。");
			}
			else
			{
				addMessageShow("~y~*ウルトララン*~w~を~r~無効化~w~しました。");
			}

			break;
		case 8: UltraPunch = !UltraPunch;
			UltraPuncher(UltraPunch);
			if (UltraPunch)
				addMessageShow("~y~*ウルトラパンチ*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*ウルトラパンチ*~w~を~r~無効化~w~しました。");
			break;

		case 9: ExplosionMelee = !ExplosionMelee;
			if (ExplosionMelee)
				addMessageShow("~y~*爆発パンチ*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*爆発パンチ*~w~を~r~無効化~w~しました。");
			break;


		case 10: RevealPeople = !RevealPeople;
			RevealPeople2(RevealPeople);
			if (RevealPeople)
				addMessageShow("~y~*レーダーにプレイヤーを表示*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*レーダーにプレイヤーを表示*~w~を~r~無効化~w~しました。");
			break;

		case 11: OffRader = !OffRader; OFF_Rader(OffRader);
			if (OffRader)
				addMessageShow("~y~*レーダーから自身を消す*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*レーダーから自身を消す*~w~を~r~無効化~w~しました。");
			break;

		case 12: CopsTurnBlindEye = !CopsTurnBlindEye; CopsturnBlindEye(CopsTurnBlindEye);
			if (CopsTurnBlindEye)
				addMessageShow("~y~*警察が黙視*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*警察が黙視*~w~を~r~無効化~w~しました。");
			break;

		case 13: PS3::WriteInt32(PS3::ReadInt32(0x1E70394) + 0x24C18, 5);
			addMessageShow("~y~ブルシャーク~w~を適応しました。");
			break;

		case 14: Noclip[0] = !Noclip[0]; NoClipSetup(Noclip[0]);
			if (Noclip[0])
				addMessageShow("~y~*浮遊*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*浮遊*~w~を~r~無効化~w~しました。");
			break;
		case 15:
			changeSubmenu(NameChager);
			break;
		}
		break;
#pragma endregion

#pragma region NameChager
	case NameChager:
		addTitle("ネームチェンジャー");
		addKeyboardOption("ネームチェンジャー 入力", CUSTOM_NAME, "~r~Re HyperDx", 17, "", "", 1);
		if (_AdminFlag)
		{
			addOption("~p~S~b~T~y~A~g~N~r~G~w~");
		}
		for (int i = 0; i < 20; i++)
		{
			if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(Load_NameChanger::Loaded_String[i]))
				addNameOption(Load_NameChanger::Loaded_String[i], "読み込まれた文字列です。", "");
		}
		switch (getOption())
		{
			if (_AdminFlag)
			{
		case 2:
			do_NameChange("~p~S~b~T~y~A~g~N~r~G~w~");
			addMessageShow("変更完了!セッションを移動してください！");
			break;
			}
		}
		break;
#pragma endregion

#pragma region Online
	case OnlineMenu:
		PlayerUI = false;
		addTitle("オンライン");
		addSubmenuOption("プレイヤーリスト", PlayerList, "プレイヤー1人ずつ選択します。\nPlayer List");
		addSubmenuOption("全てのプレイヤー", AllPlayer, "全てのプレイヤーに影響を与えます。\nAll Player");
		addCheckOption("スクリプトホスト取得", _GetHost, "よくフリーズします\nCapture ScriptHost");
		addCheckOption("ゴーストモード", GhostMode, "セッション一覧に表示されなくなります。\nGhost Mode");
		addCheckInt("ランク偽装", _SpoofRank, &_SpoofRankVar, -99999, 99999, 1, "オンにしてる間は他の人に見えます");
		addOption("セッション退出");
		switch (getOption())
		{
		case 3:
			if (PLAYER::PLAYER_ID() != NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) && isOnline())
				_GetHost = !_GetHost;
			else
			{
				if (_GetHost)
					_GetHost = false;
				else
					addMessageShow("[S-H]でないときに使用してください。");
			}
			break;
		case 4:GhostMode = !GhostMode;
			if (GhostMode)
			{
				PS3::WriteUInt32(0x12F324C, 0x60000000);
				PS3::WriteUInt32(0x12F32F0, 0x60000000);
			}
			else
			{
				PS3::WriteUInt32(0x12F324C, 0x4B70EB19);
				PS3::WriteUInt32(0x12F32F0, 0x63A30000);
			}
			break;
		case 5:_SpoofRank = !_SpoofRank; break;
		case 6:

			PS3::SetGlobal(0x14064F, 1, 0);
			//PS3::SetGlobal(0x14064F, 1, 0);
			break;
		}
		break;
#pragma endregion

#pragma region VehicleMenu_Color
	case VehicleMenu_Color:
		addTitle("カラー変更");
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.1300f, 0.1000f, VehicleColor.R, VehicleColor.G, VehicleColor.B, 255);
		drawText("<カラーレビュー>", 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);
		addIntOption("赤", &VehicleColor.R, 0, 255, 3, "RED");
		addIntOption("緑", &VehicleColor.G, 0, 255, 3, "GREEN");
		addIntOption("青", &VehicleColor.B, 0, 255, 3, "BLUE");
		addCheckOption("メイン色", VehicleColor_Bool[0], "");
		addCheckOption("サブ色", VehicleColor_Bool[1], "");
		addCheckOption("スモーク色", VehicleColor_Bool[2], "");
		addCharSwap("プリセット", COLOR_ESP, &VehicleColorVar, 0, 5, "");
		addOption("クローム ~g~ON", "");
		addOption("クローム ~r~OFF", "");

		switch (getOption())
		{
		case 4:VehicleColor_Bool[0] = !VehicleColor_Bool[0]; break;
		case 5:VehicleColor_Bool[1] = !VehicleColor_Bool[1]; break;
		case 6:VehicleColor_Bool[2] = !VehicleColor_Bool[2]; break;
		case 8:
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
			VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 120, 120); break;
		case 9:
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
			VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, 0); break;
		}
		if (currentOption == 7)
		{
			switch (VehicleColorVar)
			{
			case 0:VehicleColor.R = 255; VehicleColor.G = 0; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 1:VehicleColor.R = 0; VehicleColor.G = 255; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 2:VehicleColor.R = 0; VehicleColor.G = 0; VehicleColor.B = 255; VehicleColor.A = 255; break;
			case 3:VehicleColor.R = 255; VehicleColor.G = 255; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 4:VehicleColor.R = 180; VehicleColor.G = 0; VehicleColor.B = 255; VehicleColor.A = 255; break;
			case 5:VehicleColor.R = 0; VehicleColor.G = 0; VehicleColor.B = 150; VehicleColor.A = 255; break;
			}
		}

		break;
#pragma endregion
//
//#pragma region VehicleMenu_Custom_Test_Spoiler
//	case VehicleMenu_Custom_Test_Custom:
//		addTitle(UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(selectedVehicle, LSCIndex, 0)));
//		int num = VEHICLE::GET_NUM_VEHICLE_MODS(selectedVehicle, LSCIndex);
//		for (int i = 0; i < num; i++)
//		{
//			addOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(selectedVehicle, LSCIndex, i)));
//		}
//		if (optionPress)
//		{
//			VEHICLE::SET_VEHICLE_MOD(selectedVehicle, LSCIndex, currentOption - 1, false);
//		}
//		break;
//#pragma endregion
//
//#pragma region VehicleMenu_Custom_Test
//	case VehicleMenu_Custom_Test:
//		addTitle("LSC");
//		for (int i = 0; i < 24; i++)
//		{
//			//UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(selectedVehicle, i, 0))
//			addOption("");
//		}
//		if (optionPress && !(VEHICLE::GET_NUM_VEHICLE_MODS(selectedVehicle, 0) <= -1))
//		{
//			ReadyLSCMenu(currentOption - 1);
//		}
//
//		break;
//#pragma endregion

#pragma region VehicleMenu_Custom
	case VehicleMenu_Custom:
		addTitle("カスタム");
		addKeyboardOption("ナンバープレート 入力", CUSTOM_NUMBERPLATE, "ST4NG", 9, "キーボード", "", 1);
		addOption("フルカス");
		addOption("3色 スモーク");
		//if (_AdminFlag)
		//	addOption("テスト", "", "+");
		switch (getOption())
		{
		case 2:MaxUp(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)); break;
		case 3:
			VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 20, 1);
			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, 0, 0);
			break;
		//case 2:
		//	selectedVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		//	VEHICLE::SET_VEHICLE_MOD_KIT(selectedVehicle, 0);
		//	if (selectedVehicle != 0)
		//		changeSubmenu(VehicleMenu_Custom_Test);
		//	else
		//		addMessageShow("乗車してから実行してください。");
		//	break;
		}
		break;
#pragma endregion

#pragma region VehicleOption
	case VehicleMenu:
		addTitle("車のチート");
		addOption("カラー変更", "色変えます", "+");
		addOption("カスタム", "", "+");
		addCheckOption("車無敵", VehicleGodmode, "");

		addCheckOption("ジェットパック", VehicleJetpack, "車が浮きます。\nVehicle Jetpack");
		addCheckOption("壁走り", DriveOnWall, "壁を走ります。\nDrive On Wall");
		addOption("乗ってる車を削除");
		//addOption("フルアップグレード");
		addCheckOption("海の上を走る", DriveOnWater, "UFOは気にしないで");
		addCheckFloat("車のスピードを変更する", DriveSpeedModifier, &DriveSpeedModifier_float, 0, 1000, 1.0f, "限界スピードを変更します");
		addCheckFloat("ブレーキの効きやすさを変更する", StopSpeedModifier, &StopSpeedModifier_float, 0, 300, 1.0f, "");
		addCheckOption("車がすり抜ける", CollisionCar, "壁と床がすり抜けます");
		addOption("車修復", "");
		addCheckOption("車修復 十字ボタンの右", DpadLeftCarFix, "");
		addCheckOption("ドリフト R1", DriftL1, "");
		addCheckOption("L3ブースト R3ストップ", L3Boost_R3Stop, "");
		addCheckFloat("ジャンプ R1", R1Jumping, &hydro, 0, 10, 0.5, "飛びます");
		addCheckChar("タイヤ痕 カラー変更", taiyakonColor, Tire_Color_, &ColorVarTaiyakon, 0, 6, "軽量化入れてると見えません");
		addOption("どこでも水しぶき", "軽量化入れてると見えません");
		addOption("ライト カラー変更", "", "+");

		if (currentOption == 14 && isDpadPress_2())
		{
			RGBA _RGBA;
			switch (ColorVarTaiyakon)
			{
			case 0:_RGBA = RED;	break;
			case 1:_RGBA = GREEN; break;
			case 2:_RGBA = BLUE; break;
			case 3:_RGBA = YELLOW; break;
			case 4:_RGBA = PURPLE; break;
			case 5:_RGBA = LBLUE; break;
			case 6:TireRainbow = true; break;
			}
			if (ColorVarTaiyakon != 6)
			{
				for (int i = 0; i < VEHFX_INDEX; i++)
				{
					int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
					PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)_RGBA.R);
					PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)_RGBA.G);
					PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)_RGBA.B);
				}
			}
		}
		else if (currentOption == 16 && isDpadPress_2())
		{
			RGBA _RGBA;
			switch (ColorVarTaiyakon)
			{
			case 0:_RGBA = RED;	break;
			case 1:_RGBA = GREEN; break;
			case 2:_RGBA = BLUE; break;
			case 3:_RGBA = YELLOW; break;
			case 4:_RGBA = PURPLE; break;
			case 5:_RGBA = LBLUE; break;
			case 6:TireRainbow2 = true; break;
			}
			if (ColorVarTaiyakon != 6)
			{
				for (int i = 0; i < VEHFX_INDEX; i++)
				{
					int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
					PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)_RGBA.R);
					PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)_RGBA.G);
					PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)_RGBA.B);
				}
			}
		}
		switch (getOption())
		{
		case 1:
			changeSubmenu(VehicleMenu_Color);
			break;
		case 2:
			changeSubmenu(VehicleMenu_Custom);
			break;
		case 3:
			VehicleGodmode = !VehicleGodmode;
			if (!VehicleGodmode)
				_VehicleGodmode(PLAYER::PLAYER_PED_ID(), false);
			break;
			//case 3:MaxUp(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)); break;
		case 4:
			if (ENTITY::DOES_ENTITY_EXIST(JetPackOB))
			{
				ENTITY::DETACH_ENTITY(JetPackOB, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(JetPackOB, 1, 1);
				ENTITY::DELETE_ENTITY1(&JetPackOB);
				JetPackOB = 0;
			}
			Hover_ON = false;
			VehJetpack_ON = false;
			VehicleJetpack = !VehicleJetpack; break;

		case 5:
			DriveOnWall = !DriveOnWall; break;

		case 6:DeleteEntity(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)); break;

		case 7:DriveOnWater = !DriveOnWater;
			DeleteEntity(DriveOnWaterOBJ);
			//FloatZ_DriveOnWater = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).z - 18;
			break;
		case 8:
			DriveSpeedModifier = !DriveSpeedModifier; break;
		case 9:StopSpeedModifier = !StopSpeedModifier; break;
		case 10:
			CollisionCar = !CollisionCar; 
			if (!CollisionCar)
				Collision(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true);
			
			break;
		case 11:
			CARFIX();
			break;
		case 12:
			DpadLeftCarFix = !DpadLeftCarFix;
			break;
		case 13:DriftL1 = !DriftL1; break;
		case 14:L3Boost_R3Stop = !L3Boost_R3Stop; break;
		case 15:R1Jumping = !R1Jumping; break;
		case 16: taiyakonColor = !taiyakonColor;

			RGBA _RGBA;
			switch (ColorVarTaiyakon)
			{
			case 0:_RGBA = RED;	break;
			case 1:_RGBA = GREEN; break;
			case 2:_RGBA = BLUE; break;
			case 3:_RGBA = YELLOW; break;
			case 4:_RGBA = PURPLE; break;
			case 5:_RGBA = LBLUE; break;
			case 6:TireRainbow = true; break;
			}

			tirekoncolor(taiyakonColor, _RGBA);
			break;
		case 17:
			for (int i = 0; i < VEHFX_INDEX; i++)
			{
				int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
				PS3::WriteBytes(_ADDRESS, Tire_Water_byte, 116);
			}
			break;
		case 18:
			changeSubmenu(LightEditor);
			break;

		}
		break;
#pragma endregion

#pragma region LightEditor
	case LightEditor:
		addTitle("ライト カラー変更");
		addOption("ヘッドライト", "", "+");
		addOption("テールランプ", "", "+");
		addOption("ミドルランプ", "", "+");
		addOption("バックライト", "", "+");
		switch (getOption())
		{
		case 1:
			//HeadLightReady();
			LightEditorReady(0xEC, 0x108, false, "ヘッドライト");
			break;
		case 2:
			LightEditorReady(0x78, 0x94, false, "テールランプ");
			//TailReady();
			break;
		case 3:
			LightEditorReady(0x00, 0xC0, true, "ミドルランプ");
			break;

		case 4:
			LightEditorReady(0x134, 0x150, false, "バックライト");
			break;
		}

		break;
#pragma endregion

#pragma region LightEditor_head
	case LightEditor_head:
		addTitle(Editor.name);
		if (!Editor.is_sub)
		{
			addByteOption("ライト ~r~赤", &Editor.lightvalue._red, 0, 255, 2, "");
			addByteOption("ライト ~g~緑", &Editor.lightvalue._green, 0, 255, 2, "");
			addByteOption("ライト ~b~青", &Editor.lightvalue._blue, 0, 255, 2, "");

			addFloatOption("ライト 光の強さ", &Editor.lightvalue._Intensity, 0, 10000, 1, "");
			addFloatOption("ライト 照らす距離", &Editor.lightvalue._fallofMax, 0, 2505, 1, "");
			addFloatOption("ライト 照らす距離2", &Editor.lightvalue._falloffExponent, 0, 10000, 1, "");
			addFloatOption("ライト 薄さ", &Editor.lightvalue._innerConeAngle, 0, 47, 1, "");
			addFloatOption("ライト 照らす範囲", &Editor.lightvalue._outerConeAngle, 0, 85, 1, "");
		}
		addByteOption("光輪 ~r~赤", &Editor.coronavalue._red, 0, 255, true, "");
		addByteOption("光輪 ~g~緑", &Editor.coronavalue._green, 0, 255, true, "");
		addByteOption("光輪 ~b~青", &Editor.coronavalue._blue, 0, 255, true, "");
		
		addFloatOption("光輪 サイズ", &Editor.coronavalue._intensity, 0, 10000, true, "");
		addFloatOption("光輪 サイズ2", &Editor.coronavalue._size, 0, 10000, true, "");
		addFloatOption("光輪 薄さ", &Editor.coronavalue._size_far, 0, 10000, true, "");
		addFloatOption("光輪 薄さ2", &Editor.coronavalue.intensity_far, 0, 10000, true, "");
		addFloatOption("光輪 回転 x", &Editor.coronavalue.xRotation, 0, 359, true, "");
		addFloatOption("光輪 回転 y", &Editor.coronavalue.yRotation, 0, 359, true, "");
		addFloatOption("光輪 回転 z", &Editor.coronavalue.zRotation, 0, 359, true, "");

		if (isDpadPress_2())
		{
			int lightIndex = PS3::ReadInt32(0x1CE4E38);
			int lightAddress = PS3::ReadInt32(lightIndex + 0x1C);
			
			for (int i = 0; i < 0x5D; i++)
			{
				if (!Editor.is_sub && Editor.lightIndex != 0x00)
					*(Light_*)(lightAddress + (i * 0x180) + Editor.lightIndex) = Editor.lightvalue;

				*(LightCorona_*)(lightAddress + (i * 0x180) + Editor.coronaIndex) = Editor.coronavalue;
			}
		}
		switch (getOption())
		{

		}
		break;
#pragma endregion

#pragma region PTFXMenu
	case PTFXMenu:
		addTitle("パーティクル");
		addCheckOption("電気", effectp[0], "電気ビリビリ");
		addCheckOption("血しぶき", effectp[1], "血ぶっしゃーん");
		addCheckOption("ピンクのもやもや", effectp[2], "もやもや");
		//addCheckOption("aaa", effectp[3], "");
		//addCheckOption("パーティクルマン", ParticleMan, "飛べたりします\nParticle Man");
		switch (getOption())
		{
		case 1: effectp[0] = !effectp[0]; break;
		case 2: effectp[1] = !effectp[1]; break;
		case 3: effectp[2] = !effectp[2]; break;
		//case 4:effectp[3] = !effectp[3]; break;
			//case 1:ParticleMan = !ParticleMan; break;
		}
		break;
#pragma endregion

#pragma region ObjectSpawn
	case ObjectSpawn:
		addTitle("オブジェクト");
		
		addSubmenuOption("スポーンした物", Spawned_Object, "オブジェクトもでます");
		if (ViewPropName)
		{ 
			addObjectCharSwap("マップMod用 オブジェ", UnusedObj1, UnusedObj1, &ObjectIndexes[0], 0, 12);
			addObjectCharSwap("マップMod用 オブジェ2", UnusedObj1, UnusedObj1, &ObjectIndexes[1], 0, 4);
			addObjectCharSwap("車アタッチ用 オブジェ1", ForVehAttach1, ForVehAttach1, &ObjectIndexes[2], 0, 8);
			addObjectCharSwap("車アタッチ用 オブジェ2", objectspawner13, objectspawner13, &ObjectIndexes[11], 0, 32);
			addObjectCharSwap("ジャンプ台", RampModelsOBJ, RampModelsOBJ, &ObjectIndexes[7], 0, 3);
			addObjectCharSwap("スケートオブジェクト", skateobjectlist, skateobjectlist, &ObjectIndexes[3], 0, 6);
			addObjectCharSwap("ローポリマップ", LowPolygonlist, LowPolygonlist, &ObjectIndexes[4], 0, 13);
			addObjectCharSwap("アパート / 家", ApartMentAndHouse, ApartMentAndHouse, &ObjectIndexes[5], 0, 10);
			addObjectCharSwap("オブジェクト3", MapObjectsList, MapObjectsList, &ObjectIndexes[6], 0, 10);
			addObjectCharSwap("ライト", LightingObj, LightingObj, &ObjectIndexes[8], 0, 2);
			addObjectCharSwap("スクラップ", ScrapList, ScrapList, &ObjectIndexes[9], 0, 2);
			addObjectCharSwap("適当オブジェ", ObjectTekitou2, ObjectTekitou2, &ObjectIndexes[10], 0, 24);
			addObjectCharSwap("適当オブジェ2", ObjectTekitou3, ObjectTekitou3, &ObjectIndexes[12], 0, 15);
			addObjectCharSwap("適当オブジェ3", ObjectTekitou4, ObjectTekitou4, &ObjectIndexes[13], 0, 24);
			addObjectCharSwap("適当オブジェ4", ObjectTekitou5, ObjectTekitou5, &ObjectIndexes[14], 0, 45, "prop_flag系はアタッチすると見えます");
			addObjectCharSwap("適当オブジェ5", BiribiriObj, BiribiriObj, &ObjectIndexes[15], 0, 77, "");
			addObjectCharSwap("適当オブジェ6", TekitouObj2, TekitouObj2, &ObjectIndexes[16], 0, 9, "");
		}
		else
		{
			addObjectCharSwap("マップMod用 オブジェ", UnusedObj1, UnusedObjJp1, &ObjectIndexes[0], 0, 12);
			addObjectCharSwap("マップMod用 オブジェ2", ForMapModObj1, ForMapModObjJp1, &ObjectIndexes[1], 0, 4);
			addObjectCharSwap("車アタッチ用 オブジェ1", ForVehAttach1, VehAttJapanse1, &ObjectIndexes[2], 0, 8);
			addObjectCharSwap("車アタッチ用 オブジェ2", objectspawner13, objectspawner13japanese, &ObjectIndexes[11], 0, 32);
			addObjectCharSwap("ジャンプ台", RampModelsOBJ, RampModelsOBJJP, &ObjectIndexes[7], 0, 3);
			addObjectCharSwap("スケートオブジェクト", skateobjectlist, skateJapanese1, &ObjectIndexes[3], 0, 6);
			addObjectCharSwap("ローポリマップ", LowPolygonlist, LowPolyJplist, &ObjectIndexes[4], 0, 13);
			addObjectCharSwap("アパート / 家", ApartMentAndHouse, ApartMentHouseJpn, &ObjectIndexes[5], 0, 10);
			addObjectCharSwap("オブジェクト3", MapObjectsList, MapObjJapanese, &ObjectIndexes[6], 0, 10);
			addObjectCharSwap("ライト", LightingObj, LightingObjJP, &ObjectIndexes[8], 0, 2);
			addObjectCharSwap("スクラップ", ScrapList, ScrapListJP, &ObjectIndexes[9], 0, 2);
			addObjectCharSwap("適当オブジェ", ObjectTekitou2, ObjectTekitou2JP, &ObjectIndexes[10], 0, 24);
			addObjectCharSwap("適当オブジェ2", ObjectTekitou3, ObjectTekitou3JP, &ObjectIndexes[12], 0, 15);
			addObjectCharSwap("適当オブジェ3", ObjectTekitou4, ObjectTekitou4JP, &ObjectIndexes[13], 0, 24);
			addObjectCharSwap("適当オブジェ4", ObjectTekitou5, ObjectTekitou5JP, &ObjectIndexes[14], 0, 45, "prop_flag系はアタッチすると見えます");
			addObjectCharSwap("適当", BiribiriObj, BiribiriObjJPN, &ObjectIndexes[15], 0, 77, "");
			addObjectCharSwap("適当オブジェ6", TekitouObj2, TekitouObj2, &ObjectIndexes[16], 0, 9, "");
			//add_LoadedObjectCharSwap("適当3", &ObjectIndexes[16], 0, 60, 0x10060000, "");
		}

		
		//if (_AdminFlag)
		//	addIntOption("適当", &TekitouOBJVar, 0, 40, 1, "");
		addKeyboardOption("オブジェクト名 入力", CUSTOM_OBJECT, "", 100, "", "", 0);
		SpawnObjOption("水", "cs3_lod_water_slod3_03", "cs3_lod_water_slod3_03");
		SpawnObjOption("溶岩", "root_scroll_anim_skel", "root_scroll_anim_skel");
		
		switch (getOption())
		{
		//case 12:
		//	char AAAA[40];
		//	snprintf(AAAA, 40, "0x%X", tekitouOBJ[TekitouOBJVar]);
		//	Create_Hash_int = tekitouOBJ[TekitouOBJVar];
		//	Create_Map_string = AAAA;
		//	Create_Map_int = true;
		//	break;

		}
		break;
#pragma endregion

#pragma region ObjectSpawn_Manager_Location
	case ObjectSpawn_Manager_Location:
		addTitle("移動");
		
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(SpawnedSelectedEntity);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(SpawnedSelectedEntity, 0, 0);
		addFloatOption("移動速度", &Movement, 0.1, 3, 0.05);

		addFloatOption("左右 (X)", &ObjectSpawn_Manager_Location_Loc.x, -9999.0f, 9999.0f, Movement, "");
		addFloatOption("奥行き (Y)", &ObjectSpawn_Manager_Location_Loc.y, -9999.0f, 9999.0f, Movement, "");
		addFloatOption("上下 (Z)", &ObjectSpawn_Manager_Location_Loc.z, -9999.0f, 9999.0f, Movement, "");

		addFloatOption("向き : 横 (X)", &ObjectSpawn_Manager_Location_Rot.x, 0.0f, 360.0f, Movement, "");
		addFloatOption("向き : 縦 (Y)", &ObjectSpawn_Manager_Location_Rot.y, 0.0f, 360.0f, Movement, "");
		addFloatOption("向き : 傾き (Z)", &ObjectSpawn_Manager_Location_Rot.z, 0.0f, 360.0f, Movement, "");

		if (isDpadPress_2())
		{
			switch (currentOption)
			{
			case 2:
			case 3:
			case 4: 
				ENTITY::SET_ENTITY_COORDS(SpawnedSelectedEntity, ObjectSpawn_Manager_Location_Loc.x, ObjectSpawn_Manager_Location_Loc.y, ObjectSpawn_Manager_Location_Loc.z, 0, 0, 0, 1);
				break;
			case 5:
			case 6:
			case 7:
				ENTITY::SET_ENTITY_ROTATION(SpawnedSelectedEntity, ObjectSpawn_Manager_Location_Rot.x, ObjectSpawn_Manager_Location_Rot.y, ObjectSpawn_Manager_Location_Rot.z, 2, 1);
				break;
			}
		}

		/*addFloatCoord("左右 (X)", SpawnedSelectedEntity, X, Movement, false, "< >");
		addFloatCoord("奥行き (Y)", SpawnedSelectedEntity, Y, Movement, false, "< >");
		addFloatCoord("上下 (Z)", SpawnedSelectedEntity, Z, Movement, false, "< >");
		addFloatRotation("向き : 横 (X)", SpawnedSelectedEntity, X, Movement, "< >");
		addFloatRotation("向き : 縦 (Y)", SpawnedSelectedEntity, Y, Movement, "< >");
		addFloatRotation("向き : 傾き (Z)", SpawnedSelectedEntity, Z, Movement, "< >");*/
		addOption("リセット", "");
		switch (getOption())
		{
		case 8:
			//ObjectSpawn_Manager_Location_Loc = { 0, 0, 0 };
			ObjectSpawn_Manager_Location_Rot.x = 0;
			ObjectSpawn_Manager_Location_Rot.y = 0;
			ObjectSpawn_Manager_Location_Rot.z = 0;
			ENTITY::SET_ENTITY_ROTATION(SpawnedSelectedEntity, 0, 0, 0, 1, 1); 
			break;
		}
		break;
#pragma endregion

#pragma region ObjectSpawn_Manager_Attach
	case ObjectSpawn_Manager_Attach:
		addTitle(_SelectedEntity);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(SpawnedSelectedEntity);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(SpawnedSelectedEntity, 0, 0);
		addFloatOption("移動速度", &Movement, 0, 10, 0.05, "移動するスピード\nMovement");
		addFloatOption("左右 (X)", &AttachVector3[SpawnedEntityIndex].x, -100, 100, Movement, "");
		
		addFloatOption("奥行き (Y)", &AttachVector3[SpawnedEntityIndex].y, -100, 100, Movement, "");
		addFloatOption("上下 (Z)", &AttachVector3[SpawnedEntityIndex].z, -100, 100, Movement, "");
		addFloatOption("向き : 横 (X)", &AttachRot[SpawnedEntityIndex].x, 0, 360, Movement, "");
		addFloatOption("向き : 縦 (Y)", &AttachRot[SpawnedEntityIndex].y, 0, 360, Movement, "");
		addFloatOption("向き : 傾き (Z)", &AttachRot[SpawnedEntityIndex].z, 0, 360, Movement, "");
		addCharSwap("アタッチするボーン", BoneStringList, &AttachBone_, 0, 13, "");
		addOption("アタッチ", "選択した値でアタッチします");
		addCharSwap("アタッチ先", _Attach_Char, &AttachSelectvar, 0, 0, "");
		addOption("値をリセット");
		addOption("コピー");
		addOption("当たり判定無しで アタッチ", "押すだけです");
		addOption("向き : 横 (X) +90", "", "");
		addOption("向き : 縦 (Y) +90", "", "");
		addOption("向き : 傾き (Z) +90", "", "");
		if (currentOption > 1 && currentOption < 10)
		{
			if (rightPress || (isPress(Dpad_Right) && isPress(Button_X)) || (leftPress || (isPress(Dpad_Left) && isPress(Button_X))))
			{
				int TO_ATTACH = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
				if (TO_ATTACH != SpawnedSelectedEntity && TO_ATTACH != 0)
				{
					Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH, BoneList[AttachBone_]);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, true, true, true, true);
				}
				else
				{
					addMessageShow("エラーが発生したため、アタッチ出来ませんでした。");
				}
			}
		}
		switch (getOption())
		{
		case 10:
			int TO_ATTACH = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
			if (TO_ATTACH != SpawnedSelectedEntity && TO_ATTACH != 0)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH, BoneList[AttachBone_]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, true, true, true, true);
			}
			else
			{
				addMessageShow("エラーが発生したため、アタッチ出来ませんでした。");
			}
			break;
		case 11:
			AttachVector3[SpawnedEntityIndex].x = 0;
			AttachVector3[SpawnedEntityIndex].y = 0;
			AttachVector3[SpawnedEntityIndex].z = 0;
			AttachRot[SpawnedEntityIndex].x = 0;
			AttachRot[SpawnedEntityIndex].y = 0;
			AttachRot[SpawnedEntityIndex].z = 0;
			break;
		case 12:
			int _hash = ENTITY::GET_ENTITY_MODEL(SpawnedSelectedEntity);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(_hash) && STREAMING::IS_MODEL_VALID(_hash))
			{
				if (ENTITY::IS_ENTITY_A_VEHICLE(SpawnedSelectedEntity))
				{
					SpawnVehMethod_Hash = _hash;
					VehSpawnMethod = true;
				}
				else if (ENTITY::IS_ENTITY_AN_OBJECT(SpawnedSelectedEntity))
				{
					Create_Hash = _hash;
					Create_Map = true;
				}
			}
			else
				addMessageShow("モデルが読み込めませんでした。");
			break;

		case 13:
			int TO_ATTACH2 = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
			if (TO_ATTACH2 != SpawnedSelectedEntity && TO_ATTACH2 != 0)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH2, BoneList[AttachBone_]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH2, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, false, true, true, true);

			}
			break;
		case 14:
			AttachRot[SpawnedEntityIndex].x += 90;
			TO_ATTACH = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
			if (TO_ATTACH != SpawnedSelectedEntity && TO_ATTACH != 0)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH, BoneList[AttachBone_]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, true, true, true, true);
			}
			else
			{
				addMessageShow("エラーが発生したため、アタッチ出来ませんでした。");
			}
			break;
		case 15:
			AttachRot[SpawnedEntityIndex].y += 90;
			TO_ATTACH = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
			if (TO_ATTACH != SpawnedSelectedEntity && TO_ATTACH != 0)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH, BoneList[AttachBone_]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, true, true, true, true);
			}
			else
			{
				addMessageShow("エラーが発生したため、アタッチ出来ませんでした。");
			}
			break;
		case 16:
			AttachRot[SpawnedEntityIndex].z += 90;
			TO_ATTACH = AttachSelectvar == 0 ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
			if (TO_ATTACH != SpawnedSelectedEntity && TO_ATTACH != 0)
			{
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(TO_ATTACH, BoneList[AttachBone_]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, TO_ATTACH, Bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, true, true, true, true);
			}
			else
			{
				addMessageShow("エラーが発生したため、アタッチ出来ませんでした。");
			}
			break;
		}
		break;
#pragma endregion

#pragma region ObjectSpawn_Manager_AttachToPlayer
		case ObjectSpawn_Manager_AttachToPlayer:
			addTitle(_SelectedEntity);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(SpawnedSelectedEntity);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PLAYER::GET_PLAYER_PED(selectedNamedPlayer));
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(SpawnedSelectedEntity, 0, 0);
			addFloatOption("移動速度", &Movement, 0, 10, 0.1, "移動するスピード\nMovement");
			addFloatOption("左右 (X)", &AttachVector3[SpawnedEntityIndex].x, -100, 100, Movement, "動かすだけで自動でくっつきます");

			addFloatOption("奥行き (Y)", &AttachVector3[SpawnedEntityIndex].y, -100, 100, Movement, "動かすだけで自動でくっつきます");
			addFloatOption("上下 (Z)", &AttachVector3[SpawnedEntityIndex].z, -100, 100, Movement, "動かすだけで自動でくっつきます");
			addFloatOption("向き : 横 (X)", &AttachRot[SpawnedEntityIndex].x, 0, 360, Movement, "動かすだけで自動でくっつきます");
			addFloatOption("向き : 縦 (Y)", &AttachRot[SpawnedEntityIndex].y, 0, 360, Movement, "動かすだけで自動でくっつきます");
			addFloatOption("向き : 傾き (Z)", &AttachRot[SpawnedEntityIndex].z, 0, 360, Movement, "動かすだけで自動でくっつきます");
			addCharSwap("アタッチするボーン", PedBoneList, &PedBone_var, 0, 6, "");

			addCharSwap("アタッチ先", Playername, &selectedNamedPlayer, 0, 15, "");
			addOption("アタッチ", "選択した値でアタッチします");

			addOption("値をリセット");
			addOption("コピー");
			addOption("当たり判定無しで アタッチ", "押すだけです");
			addOption("向き : 横 (X) +90", "", "");
			addOption("向き : 縦 (Y) +90", "", "");
			addOption("向き : 傾き (Z) +90", "", "");
			int bone = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), PedBoneHash[PedBone_var]);

			if (currentOption > 1 && currentOption < 9)
			{
				if (rightPress || (isPress(Dpad_Right) && isPress(Button_X)) || (leftPress || (isPress(Dpad_Left) && isPress(Button_X))))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, PLAYER::GET_PLAYER_PED(selectedNamedPlayer), bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, _Is_Collision, true, true, true);
				}
			}

			switch (getOption())
			{
			case 11:
				//AttachVector3[SpawnedEntityIndex].x = 0;
				//AttachVector3[SpawnedEntityIndex].y = 0;
				//AttachVector3[SpawnedEntityIndex].z = 0;
				AttachRot[SpawnedEntityIndex].x = 0;
				AttachRot[SpawnedEntityIndex].y = 0;
				AttachRot[SpawnedEntityIndex].z = 0;
				break;
			case 12:
				int _hash = ENTITY::GET_ENTITY_MODEL(SpawnedSelectedEntity);
				if (STREAMING::IS_MODEL_IN_CDIMAGE(_hash) && STREAMING::IS_MODEL_VALID(_hash))
				{
					if (ENTITY::IS_ENTITY_A_VEHICLE(SpawnedSelectedEntity))
					{
						SpawnVehMethod_Hash = _hash;
						VehSpawnMethod = true;
					}
					else if (ENTITY::IS_ENTITY_AN_OBJECT(SpawnedSelectedEntity))
					{
						Create_Hash = _hash;
						Create_Map = true;
					}
				}
				else
					addMessageShow("モデルが読み込めませんでした。");
				break;

			case 13:
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, PLAYER::GET_PLAYER_PED(selectedNamedPlayer), bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, false, true, true, true);

				break;
			case 14:
				AttachRot[SpawnedEntityIndex].x += 90;
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, PLAYER::GET_PLAYER_PED(selectedNamedPlayer), bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, _Is_Collision, true, true, true);
				break;
			case 15:
				AttachRot[SpawnedEntityIndex].y += 90;
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, PLAYER::GET_PLAYER_PED(selectedNamedPlayer), bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, _Is_Collision, true, true, true);
				break;
			case 16:
				AttachRot[SpawnedEntityIndex].z += 90;
				ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedSelectedEntity, PLAYER::GET_PLAYER_PED(selectedNamedPlayer), bone, AttachVector3[SpawnedEntityIndex].x, AttachVector3[SpawnedEntityIndex].y, AttachVector3[SpawnedEntityIndex].z, AttachRot[SpawnedEntityIndex].x, AttachRot[SpawnedEntityIndex].y, AttachRot[SpawnedEntityIndex].z, true, true, _Is_Collision, true, true, true);
				break;
			}
			break;
#pragma endregion

#pragma region ObjectSpawn_Manager
	case ObjectSpawn_Manager:
		addTitle(_SelectedEntity);
		//ChangeEntityOwner(SpawnedSelectedEntity, PLAYER::PLAYER_ID());
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(SpawnedSelectedEntity);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(SpawnedSelectedEntity, 0, 0);
		addSubmenuOption("アタッチ (自分の車へ)", ObjectSpawn_Manager_Attach, "選択したオブジェクトを他のオブジェクトへ\nAttach");
		addSubmenuOption("アタッチ (プレイヤー)", ObjectSpawn_Manager_AttachToPlayer, "選択したオブジェクトを他のプレイヤーへ");
		addOption("移動", "選択したオブジェクトの座標を移動します。\nLocation", "+");
		
		addCheckOption("当たり判定", _Is_Collision, "");
		addCheckOption("フリーズポジション", _Is_FreezePosition, "");
		addOption("削除");
		addOption("おまじない");
		switch (getOption())
		{
		case 2:
			selectedNamedPlayer = PLAYER::PLAYER_ID();
			break;
		case 3:
			ObjectSpawn_Manager_Location_Loc = ENTITY::GET_ENTITY_COORDS(SpawnedSelectedEntity, true);
			ObjectSpawn_Manager_Location_Rot = ENTITY::GET_ENTITY_ROTATION(SpawnedSelectedEntity, 2);
			changeSubmenu(ObjectSpawn_Manager_Location);
			break;
		case 4:_Is_Collision = !_Is_Collision; 		
			if (_Is_Collision)
			{
				Collision(SpawnedSelectedEntity, 0);
			}
			else
			{
				Collision(SpawnedSelectedEntity, 1);
			}
			break;
		case 5:_Is_FreezePosition = !_Is_FreezePosition;
			if (_Is_FreezePosition)
				ToggleFreezeEntity(SpawnedSelectedEntity, true);
			else
				ToggleFreezeEntity(SpawnedSelectedEntity, false);
			break;
		case 6:
			DeleteEntity(SpawnedSelectedEntity);
			submenu = lastSubmenu[submenuLevel - 1];
			currentOption = lastOption[submenuLevel - 1];
			submenuLevel--;
			playSound("Back");
			break;
		case 7:
			ChangeEntityOwner(SpawnedSelectedEntity, PLAYER::PLAYER_ID());
			break;
		}
		//SpawnedSelectedEntity;
		break;
#pragma endregion

#pragma region Spawned_Object_s
	case Spawned_Object:
		ObjectUI = false;
		addTitle("スポーンした物");
		addSubmenuOption("リスト", Spawned_Object_s, "");
		addOption("~r~全て削除");
		addCheckOption("撃ったオブジェクトをリストに追加", Shot_to_add, "");
		switch (getOption())
		{
		case 2:
			for (int i = 0; i < 40; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(SpawnedEntityList[i]))
				{
					DeleteEntity(SpawnedEntityList[i]);
				}
			}
			break;

		case 3:
			Shot_to_add = !Shot_to_add;
			break;

		}
		break;
#pragma endregion

#pragma region Spawned_Object
	case Spawned_Object_s:
		ObjectUI = true;
		addTitle("スポーンしたエンティティ");

		for (int i = 0; i < 40; i++)
		{
			if (SpawnedEntityList[i] != 0)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(SpawnedEntityList[i]);
				addOption(SpawnedEntityNames[i], SpawnedEntityName[i]);
			}
			else
			{
				addOption("~r~ 存在しません");
			}
		}


		if ((optionPress && ENTITY::DOES_ENTITY_EXIST(SpawnedEntityList[currentOption - 1])))
		{
			SpawnedEntityIndex = currentOption - 1;
			SpawnedSelectedEntity = SpawnedEntityList[SpawnedEntityIndex];
			_SelectedEntity = SpawnedEntityName[SpawnedEntityIndex];
			changeSubmenu(ObjectSpawn_Manager);
		}

		break;
#pragma endregion

#pragma region VehicleSpawn_ColorChange
	case VehicleSpawn_ColorChange:
		addTitle("スポーン時のカラー設定");
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.1300f, 0.1000f, VehicleColor.R, VehicleColor.G, VehicleColor.B, 255);
		drawText("<カラーレビュー>", 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);
		addIntOption("赤", &VehicleColor.R, 0, 255, 3, "RED");
		addIntOption("緑", &VehicleColor.G, 0, 255, 3, "GREEN");
		addIntOption("青", &VehicleColor.B, 0, 255, 3, "BLUE");
		addCheckOption("メイン色", VehicleSpawnBool[0], "");
		addCheckOption("サブ色", VehicleSpawnBool[1], "");
		addCheckOption("スモーク色", VehicleSpawnBool[2], "");
		addCharSwap("プリセット", COLOR_ESP, &VehicleColorVar, 0, 5, "");
		addCheckOption("クローム化", VehicleSpawnBool[3], "");
		switch (getOption())
		{
		case 4:VehicleSpawnBool[0] = !VehicleSpawnBool[0]; break;
		case 5:VehicleSpawnBool[1] = !VehicleSpawnBool[1]; break;
		case 6:VehicleSpawnBool[2] = !VehicleSpawnBool[2]; break;
		case 8:

			VehicleSpawnBool[3] = !VehicleSpawnBool[3]; break;
		}
		if (currentOption == 7)
		{
			switch (VehicleColorVar)
			{
			case 0:VehicleColor.R = 255; VehicleColor.G = 0; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 1:VehicleColor.R = 0; VehicleColor.G = 255; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 2:VehicleColor.R = 0; VehicleColor.G = 0; VehicleColor.B = 255; VehicleColor.A = 255; break;
			case 3:VehicleColor.R = 255; VehicleColor.G = 255; VehicleColor.B = 0; VehicleColor.A = 255; break;
			case 4:VehicleColor.R = 180; VehicleColor.G = 0; VehicleColor.B = 255; VehicleColor.A = 255; break;
			case 5:VehicleColor.R = 0; VehicleColor.G = 0; VehicleColor.B = 150; VehicleColor.A = 255; break;
			}
		}

		break;
#pragma endregion

#pragma region VehicleSpawn_Setting
	case VehicleSpawn_Setting:
		addTitle("スポーン時の設定");
		addCheckOption("フルカス", MaxUpgrades, "スポーン時にフルカスで出現します。\nMax Upgrades");
		addCheckOption("乗車", TeleAutomIncar, "スポーン時に乗車します。\nAuto in Car");
		addOption("スポーン時のカラー設定", "スポーン時にカラーをつけてスポーンします。", "+");
		switch (getOption())
		{
		case 1:
			MaxUpgrades = !MaxUpgrades; break;
			break;

		case 2:
			TeleAutomIncar = !TeleAutomIncar;
			break;
		case 3:changeSubmenu(VehicleSpawn_ColorChange);
		}
		break;
#pragma endregion

#pragma region Vehicle

#pragma region Veh Spawn
	case VehicleSpawn:
		addTitle("車スポーン");
		ObjectUI = false;
		addSubmenuOption("スポーン時の設定", VehicleSpawn_Setting, "乗車時に乗る。など");
		addSubmenuOption("スポーンした物", Spawned_Object, "オブジェクトもでます");
		addSubmenuOption("Modded Car", VehicleSpawn_ModdedCar, "ModdedVehicle");
		addSubmenuOption(_RetCarClass(7), VehicleSpawn_Sport, "Super Sport");
		addSubmenuOption(_RetCarClass(6), VehicleSpawn_Spor2, "Sport");
		addSubmenuOption(_RetCarClass(5), VehicleSpawn_Classic, "Classic");
		addSubmenuOption(_RetCarClass(15), VehicleSpawn_Helicopter, "Helicopter");
		addSubmenuOption(_RetCarClass(16), VehicleSpawn_Plane, "Plane");
		addSubmenuOption(_RetCarClass(14), VehicleSpawn_Boat, "Boat");
		addSubmenuOption(_RetCarClass(8), VehicleSpawn_Bike, "Motorcyclse");
		addSubmenuOption("自転車", VehicleSpawn_Bicycle, "Bicycle");


		addSubmenuOption(_RetCarClass(4), VehicleSpawn_Muscle, "Muscle");
		addSubmenuOption(_RetCarClass(1), VehicleSpawn_Sedan, "Sedan");
		addSubmenuOption(_RetCarClass(3), VehicleSpawn_Coupes, "Coupes");
		addSubmenuOption(_RetCarClass(0), VehicleSpawn_Compact, "Compact");
		addSubmenuOption(_RetCarClass(2), VehicleSpawn_SUV, "SUV");
		addSubmenuOption(_RetCarClass(9), VehicleSpawn_Truck, "Truck");
		addSubmenuOption(_RetCarClass(12), VehicleSpawn_Vans, "Van");
		addSubmenuOption(_RetCarClass(18), VehicleSpawn_Emergency, "Emergency");
		addSubmenuOption(_RetCarClass(17), VehicleSpawn_Service, "Service");
		addSubmenuOption(_RetCarClass(19), VehicleSpawn_Military, "Military");
		addSubmenuOption(_RetCarClass(20), VehicleSpawn_Commercial, "Commercial");
		addSubmenuOption(_RetCarClass(21), VehicleSpawn_Trailer, "Trailer");

		break;
#pragma endregion

#pragma region VehicleSpawn_ModdedCar
	case VehicleSpawn_ModdedCar:
		addTitle("Modded Car");
		addOption("ゴーストライダー", "by Nyan");
		addOption("16連BMX", "by Stang");
		addOption("スカイリフト(いっぱい乗れる)", "by Eilish");
		if (_AdminFlag)
			addOption("変態飛行", "by Eilishすけべ");
		else
			addOption("編隊飛行", "by Eilish");
		addOption("木のボート", "by Eilish");
		addOption("~y~ビリビリ ~w~パント", "by Eilish");
		addOption("族車", "by imomushi45451919");
		addOption("扇風機", "by akadamaru_REDX");
		if (_AdminFlag)
			addOption("タワークレーンメンサ", "by Eilish");
		else
			addOption("タワークレーンインサージェント", "by Eilish");
		addOption("クレーン戦車", "by Eilish");
		addOption("クレーン戦車 (2)", "by Eilish");
		addOption("ギャラクシークルーザー", "by Eilish");

		addOption("なんかよくわかんないやつ", "by Eilish");
		addOption("マグネットカーゴボブ", "by Stang");
		addOption("おさかな", "by Eilish");
		addOption("宣伝車両", "by Eilish");
		addOption("?", "by Eilish");
		switch (getOption())
		{
		case 1: 
			__INNOVATION = 0;
			GhostRiderSpawn = true; 
			
			break;
		case 2:
			for (int i = 0; i < 16; i++)
			{
				_16BMX_Main[i] = 0;
			}
			_16BMX_Index = 0;
			_16BMX = true;
			break;
		case 3:
			ModdedSkyLift = true;
			break;

		case 4:
			SquadPilotFly = true;
			break;
		case 5:
			WoodedBoat = true;
			break;
		case 6:LightningPanto = true; break;
		case 7:
			yanki_bike = true;
			break;
		case 8:

			senpuukicar = true;
			break;
		case 9:mensacar = true; break;
		case 10:cranetank = true; break;
		case 11:
			cranetank2 = true;
			break;
		case 12:
			Galaxhip_index = 0;
			Galaxhip = true;
			break;

		case 13:
			_unknownCar = true;
			break;
		case 14:
			MagnetCargo = true;
			break;
		case 15:
			PenginCar = true;
			break;
		case 16:
			moddedmule_ = true;
			break;
		case 17:
			ripley2 = true;
			break;
		}
		break;
#pragma endregion

#pragma region VehicleSpawn_Sport
	case VehicleSpawn_Sport:
		addTitle(_RetCarClass(7));
		addVehicleOption("adder", "Truffade Adder");
		addVehicleOption("entityxf", "Overflod Entity XF");
		addVehicleOption("cheetah", "Grotti Cheetah");
		addVehicleOption("infernus", "Pegassi Infernus");
		addVehicleOption("vacca", "Pegassi Vacca");
		addVehicleOption("bullet", "Vapid Bullet");
		addVehicleOption("voltic", "Coil Voltic");
		addVehicleOption("zentorno", "Pegassi Zentorno");
		addVehicleOption("turismor", "Grotti Turismo R");
		addVehicleOption("osiris", "Pegassi Osiris");
		addVehicleOption("t20", "Progen T20");
		break;
#pragma endregion

#pragma region VehicleSpawn_Spor2
	case VehicleSpawn_Spor2:
		addTitle(_RetCarClass(6));
		addVehicleOption("elegy2", "Annis Elegy RH8");
		addVehicleOption("khamelion", "Hijak Khamelion");
		addVehicleOption("carbonizzare", "Grotti Carbonizzare ");
		addVehicleOption("feltzer2", "Benefactor Feltzer 1");
		addVehicleOption("feltzer3", "Benefactor Feltzer 2 ");
		addVehicleOption("rapidgt", "Dewbauchee Rapid GT 1 ");
		addVehicleOption("rapidgt2", "Dewbauchee Rapid GT 2");
		addVehicleOption("coquette", "Inverto Coquette 1");
		addVehicleOption("ninef", "Obey 9F Cabrio ");
		addVehicleOption("ninef2", "Obey 9F");
		addVehicleOption("surano", "Benefactor Surano");
		addVehicleOption("banshee", "Bravado Banshee");
		addVehicleOption("comet", "Pfister Comet");
		addVehicleOption("schwarzer", "Benefactor Schwartzer");
		addVehicleOption("fusilade", "Schyster Fusilade");
		addVehicleOption("buffalo", "Bravado Buffalo");
		addVehicleOption("buffalo2", "Bravado Buffalo 2");
		addVehicleOption("penumbra", "Maibatsu Penumbra");
		addVehicleOption("sultan", "Karin Sultan");
		addVehicleOption("futo", "Karin Futo");
		addVehicleOption("furoregt", "Lampadati Furore GT");
		addVehicleOption("massacro", "Dewbauchee Massacro 1");
		addVehicleOption("massacro2", "Dewbauchee Massacro 2");
		addVehicleOption("jester", "Dinka Jester 1");
		addVehicleOption("jester2", "Dinka Jester 2");
		addVehicleOption("windsor", "Enus Windsor");
		addVehicleOption("alpha", "Albany Alpha");
		addVehicleOption("kuruma", "Karin Kuruma 1");
		addVehicleOption("kuruma2", "Karin Kuruma 2");
		break;
#pragma endregion

#pragma region VehicleSpawn_Classic
	case VehicleSpawn_Classic:
		addTitle(_RetCarClass(5));
		addVehicleOption("coquette2", "Inverto Coquette 2");
		addVehicleOption("coquette3", "Inverto Coquette 3");
		addVehicleOption("ztype", "Truffade Z-Type");
		addVehicleOption("stingergt", "Grotti Stinger GT");
		addVehicleOption("stinger", "Grotti Stinger");
		addVehicleOption("monroe", "Pegassi Monroe");
		addVehicleOption("jb700", "Dewbauchee JB 700");
		addVehicleOption("tornado", "Declasse Tornado 1");
		addVehicleOption("tornado2", "Declasse Tornado 2");
		addVehicleOption("tornado3", "Declasse Tornado 3");
		addVehicleOption("tornado4", "Declasse Tornado 4");
		addVehicleOption("peyote", "Vapid Peyote");
		addVehicleOption("manana", "Albany Manana");
		addVehicleOption("virgo", "Albany Virgo");
		addVehicleOption("btype", "Albany Roosevelt");
		addVehicleOption("blade", "Vapid Blade");
		addVehicleOption("glendale", "Benefactor Glendale");
		addVehicleOption("pigalle", "Lampadati Pigalle");
		addVehicleOption("casco", "Lampadati Casco");
		addVehicleOption("chino", "Vapid Chino");
		break;
#pragma endregion

#pragma region VehicleSpawn_Muscle
	case VehicleSpawn_Muscle:
		addTitle(_RetCarClass(4));
		addVehicleOption("hotknife", "Vapid Hotknife");
		addVehicleOption("gauntlet", "Bravado Gauntlet");
		addVehicleOption("vigero", "Declasse Vigero");
		addVehicleOption("dominator", "Vapid Dominator");
		addVehicleOption("buccaneer", "Albany Buccaneer");
		addVehicleOption("phoenix", "Imponte Phoenix");
		addVehicleOption("sabregt", "Declasse Sabre Turbo");
		addVehicleOption("ruiner", "Imponte Ruiner");
		addVehicleOption("voodoo2", "Declasse Voodoo");
		addVehicleOption("picador", "Cheval Picador");
		addVehicleOption("ratloader", "Rat Loader 1");
		addVehicleOption("ratloader2", "Rat Loader 2");
		break;
#pragma endregion

#pragma region VehicleSpawn_Sedan
	case VehicleSpawn_Sedan:
		addTitle(_RetCarClass(1));
		addVehicleOption("superd", "Enus Super Diamond");
		addVehicleOption("oracle", "Ubermacht Oracle I");
		addVehicleOption("oracle2", "Ubermacht Oracle II");
		addVehicleOption("stretch", "Dundreary Stretch");
		addVehicleOption("fugitive", "Cheval Fugitive");
		addVehicleOption("surge", "Cheval Surge");
		addVehicleOption("schafter2", "Benefactor Schafter");
		addVehicleOption("asterope", "Karin Asterope");
		addVehicleOption("intruder", "Karin Intruder");
		addVehicleOption("washington", "Albany Washington");
		addVehicleOption("stanier", "Vapid Stanier");
		addVehicleOption("ingot", "Vulcan Ingot");
		addVehicleOption("emperor", "Albany Emperor I");
		addVehicleOption("emperor2", "Albany Emperor II");
		addVehicleOption("emperor3", "Albany Emperor III");
		addVehicleOption("primo", "Albany Primo");
		addVehicleOption("regina", "Dundreary Regina");
		addVehicleOption("romero", "Chariot Romero Hearse");
		addVehicleOption("tailgater", "Obey Tailgater");
		addVehicleOption("premier", "Declasse Premier");
		addVehicleOption("stratum", "Zirconium Stratum");
		addVehicleOption("asea", "Declasse Asea I");
		addVehicleOption("asea2", "Declasse Asea II");
		break;
#pragma endregion

#pragma region VehicleSpawn_Coupes
	case VehicleSpawn_Coupes:
		addTitle(_RetCarClass(3));
		addVehicleOption("exemplar", "Dewbauchee Exemplar");
		addVehicleOption("cogcabrio", "Enus Cognoscenti Cabrio");
		addVehicleOption("felon2", "Lampadati Felon GT");
		addVehicleOption("felon", "Lampadati Felon,");
		addVehicleOption("zion", "Ubermacht Zion Cabri");
		addVehicleOption("zion2", "Ubermacht Zion");
		addVehicleOption("sentinel", "Ubermacht Sentinel XS");
		addVehicleOption("sentinel2", "Ubermacht Sentinel");
		addVehicleOption("f620", "Ocelot F620");
		addVehicleOption("jackal", "Ocelot Jackal");
		break;
#pragma endregion

#pragma region VehicleSpawn_Compact
	case VehicleSpawn_Compact:
		addTitle(_RetCarClass(0));
		addVehicleOption("dilettante", "Karin Dilettante I");
		addVehicleOption("dilettante2", "Karin Dilettante II");
		addVehicleOption("issi2", "Weeny Issi");
		addVehicleOption("prairie", "Bollokan Prairie");
		addVehicleOption("rhapsody", "Declasse Rhapsody");
		addVehicleOption("warrener", "Vulcar Warrener");
		addVehicleOption("panto", "Benefactor Panto");
		break;
#pragma endregion
		
#pragma region VehicleSpawn_SUV
	case VehicleSpawn_SUV:
		addTitle(_RetCarClass(2));
		addVehicleOption("baller", "Gallivanter Baller 1");
		addVehicleOption("baller2", "Gallivanter Baller 2");
		addVehicleOption("rocoto", "Obey Rocoto");
		addVehicleOption("cavalcade", "Albany Cavalcade 1");
		addVehicleOption("cavalcade2", "Albany Cavalcade 2");
		addVehicleOption("dubsta", "Benefactor Dubsta 1");
		addVehicleOption("dubsta2", "Benefactor Dubsta 2");
		addVehicleOption("dubsta3", "Benefactor Dubsta 3");
		addVehicleOption("serrano", "Benefactor Serrano");
		addVehicleOption("landstalker", "Dundreary Landstalker");
		addVehicleOption("fq2", "Fathom FQ 2");
		addVehicleOption("patriot", "Mammoth Patriot");
		addVehicleOption("habanero", "Emperor Habanero");
		addVehicleOption("radi", "Vapid Radius");
		addVehicleOption("granger", "Declasse Granger");
		addVehicleOption("mesa", "Canis Mesa 1");
		addVehicleOption("mesa2", "Canis Mesa 2");
		addVehicleOption("seminole", "Canis Seminole");
		addVehicleOption("kalahari", "Canis Kalahari");
		addVehicleOption("gresley", "Bravado Gresley");
		addVehicleOption("bjxl", "Karin BeeJay XL");
		addVehicleOption("huntley", "Enus Huntley");
		addVehicleOption("sadler", "Sadler 1");
		addVehicleOption("sadler2", "Sadler 2");
		addVehicleOption("guardian", "Vapid Guardian");
		addVehicleOption("insurgent2", "HVY Insurgent 1");
		addVehicleOption("insurgent", "HVY Insurgent 2");
		addVehicleOption("technical", "Karin Technical");
		break;
#pragma endregion

#pragma region VehicleSpawn_Truck
	case VehicleSpawn_Truck:
		addTitle(_RetCarClass(11));
		addVehicleOption("monster", "Monster Truck");
		addVehicleOption("sandking", "Vapid Sandking XL");
		addVehicleOption("dune", "BF Dune Buggy");
		addVehicleOption("dune2", "BF Dune 2 (Space Docker)");
		addVehicleOption("bfinjection", "BF Injection");
		addVehicleOption("bifta", "BF Bifta");
		addVehicleOption("blazer", "Nagasaki Blazer 1");
		addVehicleOption("blazer3", "Nagasaki Blazer 2 (Trevors)");
		addVehicleOption("mesa3", "Canis Mesa (Merryweather");
		addVehicleOption("sandking2", "Vapid Sandking SWB");
		addVehicleOption("dloader", "Bravado Duneloader");
		addVehicleOption("bodhi2", "Canis Bodhi");
		addVehicleOption("rancherxl", "Declasse Rancher XL 1");
		addVehicleOption("rancherxl2", "Declasse Rancher XL 2");
		addVehicleOption("rebel", "Karin Rebel 1");
		addVehicleOption("rebel2", "Karin Rebel 2");
		addVehicleOption("blazer2", "Nagasaki Blazer Lifeguard");
		addVehicleOption("brawler", "Coil Brawler");
		addVehicleOption("enduro", "Dinka Enduro");
		break;
#pragma endregion

#pragma region VehicleSpawn_Vans
	case VehicleSpawn_Vans:
		addTitle(_RetCarClass(12));
		addVehicleOption("bison", "Bravado Bison 1");
		addVehicleOption("bison2", "Bravado Bison 2");
		addVehicleOption("bison3", "Bravado Bison 3");
		addVehicleOption("paradise", "Bravado Paradise");
		addVehicleOption("journey", "Zirconium Journey");
		addVehicleOption("minivan", "Vapid Minivan");
		addVehicleOption("bobcatxl", "Vapid Bobcat XL");
		addVehicleOption("rumpo", "Bravado Rumpo 1");
		addVehicleOption("rumpo2", "Bravado Rumpo 2");
		addVehicleOption("pony", "Brute Pony 1");
		addVehicleOption("pony2", "Brute Pony 2");
		addVehicleOption("burrito", "Declasse Burrito 1");
		addVehicleOption("burrito2", "Declasse Burrito 2");
		addVehicleOption("burrito3", "Declasse Burrito 3");
		addVehicleOption("burrito4", "Declasse Burrito 4");
		addVehicleOption("burrito5", "Declasse Burrito 5");
		addVehicleOption("burrito6", "Declasse Burrito 6");
		addVehicleOption("burrito7", "Declasse Burrito 7");
		addVehicleOption("speedo", "Vapid Speedo 1");
		addVehicleOption("speedo2", "Vapid Speedo 2");
		addVehicleOption("youga", "Bravado Youga");
		addVehicleOption("boxville", "Boxville 1");
		addVehicleOption("boxville2", "Boxville 2");
		addVehicleOption("boxville3", "Boxville 3");
		addVehicleOption("boxville4", "Boxville 4");
		addVehicleOption("camper", "Brute Camper");
		addVehicleOption("taco", "Taco Van");
		addVehicleOption("surfer", "BF Surfer");
		addVehicleOption("surfer2", "BF Surfer (Rusted)");
		addVehicleOption("slamvan", "Vapid Slamvan 1");
		addVehicleOption("slamvan2", "Vapid Slamvan 2");
		break;
#pragma endregion

#pragma region VehicleSpawn_Emergency
	case VehicleSpawn_Emergency:
		addTitle(_RetCarClass(18));
		addVehicleOption("fbi", "FIB");
		addVehicleOption("fbi2", "FIB SUV");
		addVehicleOption("firetruk", "Firetruck");
		addVehicleOption("ambulance", "Ambulance");
		addVehicleOption("police", "Police 1");
		addVehicleOption("police2", "Police 2");
		addVehicleOption("police3", "Police 3");
		addVehicleOption("police4", "Police 4");
		addVehicleOption("policeb", "Police Bike");
		addVehicleOption("policeold1", "Police Old 1");
		addVehicleOption("policeold2", "Police Old 2");
		addVehicleOption("policet", "Police Van");
		addVehicleOption("riot", "Swat Truck");
		addVehicleOption("sheriff", "Sheriff 1");
		addVehicleOption("sheriff2", "Sheriff 2");
		addVehicleOption("pbus", "Prison Bus");
		addVehicleOption("pranger", "Park Ranger");
		addVehicleOption("lguard", "Life Guard SUV");
		break;
#pragma endregion

#pragma region VehicleSpawn_Service
	case VehicleSpawn_Service:
		addTitle(_RetCarClass(17));
		addVehicleOption("airbus", "Airport Bu");
		addVehicleOption("coach", "Dashhound");
		addVehicleOption("bus", "Bus");
		addVehicleOption("rentalbus", "Rental Shuttle Bus");
		addVehicleOption("tourbus", "Tour Bus");
		addVehicleOption("taxi", "Taxi");
		break;
#pragma endregion
		
#pragma region VehicleSpawn_Military
	case VehicleSpawn_Military:
		addTitle(_RetCarClass(19));
		addVehicleOption("rhino", "Rhino Tank");
		addVehicleOption("barracks", "Barracks 1");
		addVehicleOption("barracks2", "Barracks 2");
		addVehicleOption("barracks3", "Barracks 3 ");
		addVehicleOption("crusader", "Canis Crusader");
		addVehicleOption("tanker", "Tanker 1");
		addVehicleOption("tanker2", "Tanker 2");
		break;
#pragma endregion

#pragma region VehicleSpawn_Bike
	case VehicleSpawn_Bike:
		addTitle(_RetCarClass(8));
		addVehicleOption("carbonrs", "Nagasaki Carbon RS");

		addVehicleOption("bati", "Pegassi Bati 801");
		addVehicleOption("hexer", "LCC Hexer");
		addVehicleOption("innovation", "LCC Innovation");
		addVehicleOption("double", "Dinka Double-T");
		addVehicleOption("thrust", "Dinka Thrust");
		addVehicleOption("vindicator", "Dinka Vindicator");
		addVehicleOption("ruffian", "Pegassi Ruffian");
		addVehicleOption("vader", "Shitzu Vader");
		addVehicleOption("pcj", "Shitzu PCJ 600");
		addVehicleOption("hakuchou", "Shitzu Hakuchou");
		addVehicleOption("akuma", "Dinka Akuma");
		addVehicleOption("sanchez", "Maibatsu Sanchez (Decal)");
		addVehicleOption("sanchez2", "Maibatsu Sanchez");
		addVehicleOption("faggio2", "Pegassi Faggio");
		addVehicleOption("daemon", "Western Daemon");
		addVehicleOption("bagger", "Western Bagger");
		addVehicleOption("nemesis", "Principe Nemesis");
		addVehicleOption("sovereign", "Sovereign");
		addVehicleOption("lectro", "Principe Lectro");
		break;
#pragma endregion

#pragma region VehicleSpawn_Bicycle
	case VehicleSpawn_Bicycle:
		addTitle("自転車");
		addVehicleOption("tribike", "Whippet Race Bike");
		addVehicleOption("tribike3", "Tri-Cycles Race Bike");
		addVehicleOption("scorcher", "Scorcher");
		addVehicleOption("tribike2", "Endurex Race Bike");
		addVehicleOption("cruiser", "Cruiser");
		addVehicleOption("bmx", "BMX");
		addVehicleOption("fixter", "Fixter");
		break;
#pragma endregion

#pragma region VehicleSpawn_Commercial
	case VehicleSpawn_Commercial:
		addTitle(_RetCarClass(20));
		addVehicleOption("mule", "Maibatsu Mule 1");
		addVehicleOption("mule2", "Maibatsu Mule 2");
		addVehicleOption("mule3", "Maibatsu Mule 3");
		addVehicleOption("phantom", "JoBuilt Phantom");
		addVehicleOption("benson", "Vapid Benson");
		addVehicleOption("packer", "MTL Packer");
		addVehicleOption("pounder", "MTL Pounder");
		addVehicleOption("hauler", "JoBuilt Hauler");
		addVehicleOption("stockade", "Brute Stockade 1");
		addVehicleOption("stockade3", "Brute Stockade 2");
		addVehicleOption("biff", "HVY Biff");
		addVehicleOption("dump", "HVY Dump");
		addVehicleOption("bulldozer", "HVY Dozer");
		addVehicleOption("forklift", "HVY Forklift");
		addVehicleOption("handler", "HVY Handler");
		addVehicleOption("cutter", "HVY Cutter");
		addVehicleOption("utillitruck", "Utility Truck 1");
		addVehicleOption("utillitruck2", "Utility Truck 2");
		addVehicleOption("utillitruck3", "Utility Truck 3");
		addVehicleOption("trash", "Trashmaster 1");
		addVehicleOption("trash2", "Trashmaster 2");
		addVehicleOption("towtruck", "Towtruck 1");
		addVehicleOption("towtruck2", "Towtruck 2");
		addVehicleOption("tiptruck", "TipTruck 1");
		addVehicleOption("tiptruck2", "TipTruck 2");
		addVehicleOption("mixer", "Mixer 1");
		addVehicleOption("mixer2", "Mixer 2");
		addVehicleOption("flatbed", "Flatbed Truck");
		addVehicleOption("ripley", "Airport Ripley");
		addVehicleOption("rubble", "Rubble");
		addVehicleOption("scrap", "Vapid Scrap Truck");
		addVehicleOption("mower", "Lawnmower");
		addVehicleOption("docktug", "Dock Tug");
		addVehicleOption("airtug", "Airport Tug");
		addVehicleOption("tractor", "Tractor 1");
		addVehicleOption("tractor2", "Tractor 2");
		addVehicleOption("tractor3", "Tractor 3");
		addVehicleOption("caddy", "Caddy 1");
		addVehicleOption("caddy2", "Caddy 2");
		break;
#pragma endregion

#pragma region VehicleSpawn_Helicopter
	case VehicleSpawn_Helicopter:
		addTitle(_RetCarClass(15));
		addVehicleOption("annihilator", "Annihilator");
		addVehicleOption("buzzard", "Buzzard Attack Chopper 1");
		addVehicleOption("buzzard2", "Buzzard Attack Chopper 2");
		addVehicleOption("frogger", "Frogger 1");
		addVehicleOption("frogger2", "Frogger 2");
		addVehicleOption("maverick", "Maverick");
		addVehicleOption("cargobob", "Cargobob 1");
		addVehicleOption("cargobob2", "Cargobob 2");
		addVehicleOption("cargobob3", "Cargobob 3");
		addVehicleOption("polmav", "Police Maverick");
		addVehicleOption("swift", "Swift 1");
		addVehicleOption("swift2", "Swift 2");
		addVehicleOption("valkyrie", "Buckingham Valkyrie");
		addVehicleOption("savage", "Savage");
		addVehicleOption("skylift", "Skylift");
		break;
#pragma endregion
		
#pragma region VehicleSpawn_Plane
	case VehicleSpawn_Plane:
		addTitle(_RetCarClass(16));
		addVehicleOption("titan", "Titan");
		addVehicleOption("luxor", "Buckingham Luxor 1");
		addVehicleOption("luxor2", "Buckingham Luxor 2");
		addVehicleOption("shamal", "Buckingham Shamal");
		addVehicleOption("vestra", "Buckingham Vestra");
		addVehicleOption("miljet", "Buckingham Miljet");
		addVehicleOption("velum", "Velum 1");
		addVehicleOption("velum2", "Velum 2");
		addVehicleOption("mammatus", "Mammatus");
		addVehicleOption("duster", "Duster");
		addVehicleOption("stunt", "Mallard");
		addVehicleOption("cuban800", "Cuban 800");
		addVehicleOption("cargoplane", "Cargo Plane");
		addVehicleOption("blimp", "Blimp");
		addVehicleOption("lazer", "P-996 Lazer");

		addVehicleOption("jet", "Jet");
		addVehicleOption("besra", "Bersa");
		addVehicleOption("hydra", "Mammoth Hydra");
		break;
#pragma endregion

#pragma region VehicleSpawn_Boat
	case VehicleSpawn_Boat:
		addTitle(_RetCarClass(14));
		addVehicleOption("marquis", "Dinka Marqui");
		addVehicleOption("jetmax", "Shitzu Jetmax");
		addVehicleOption("squalo", "Shitzu Squalo, ");
		addVehicleOption("suntrap", "Shitzu Suntrap");
		addVehicleOption("tropic", "Shitzu Tropic");
		addVehicleOption("seashark", "Speedophile Seashark 1");
		addVehicleOption("seashark2", "Speedophile Seashark 2");
		addVehicleOption("predator", "Police Predator");
		addVehicleOption("submersible", "Submarine");
		addVehicleOption("speeder", "Pegassi Speeder");
		addVehicleOption("dinghy", "Nagasaki Dinghy 1");
		addVehicleOption("dinghy2", "Nagasaki Dinghy 2");
		addVehicleOption("dinghy3", "Nagasaki Dinghy 3");
		addVehicleOption("toro", "Lampadati Toro");
		break;
#pragma endregion

#pragma region VehicleSpawn_Trailer
	case VehicleSpawn_Trailer:
		addTitle(_RetCarClass(21));
		addVehicleOption("armytanker", "Army Tanker");
		addVehicleOption("armytrailer", "Army Tanker 1");
		addVehicleOption("armytrailer2", "Army Tanker 2");
		addVehicleOption("baletrailer", "Bale Trailer");
		addVehicleOption("boattrailer", "Boat Trailer");
		addVehicleOption("cablecar", "Cablecar");
		addVehicleOption("docktrailer", "Dock Trailer");
		addVehicleOption("freight", "Freight Car 1");
		addVehicleOption("freightcar", "Freight Car 2");
		addVehicleOption("freightcont1", "Freight Container 1");
		addVehicleOption("freightcont2", "Freight Container 2");
		addVehicleOption("freightgrain", "Freight Train Boxcar");
		addVehicleOption("graintrailer", "Grain Trailer");
		addVehicleOption("metrotrain", "Metro Train");
		addVehicleOption("proptrailer", "Mobile Home Trailer");
		addVehicleOption("raketrailer", "Rake Trailer");
		addVehicleOption("tankercar", "Train Fuel Tank Car");
		addVehicleOption("tr2", "Car Carrier Trailer");
		addVehicleOption("tr3", "Marquis Trailer");
		addVehicleOption("tr4", "Super Car Carrier Trailer");
		addVehicleOption("trailerlogs", "Trailer Logs");
		addVehicleOption("trailers", "Trailers 1");
		addVehicleOption("trailers2", "Trailers 2");
		addVehicleOption("trailers3", "Trailers 3");
		addVehicleOption("trailersmall", "Trailer Small");
		addVehicleOption("trflat", "Trailer Flat");
		addVehicleOption("tvtrailer", "Tv Trailer");
		break;
#pragma endregion

#pragma endregion

#pragma region AllPlayer
	case AllPlayer:
		addTitle("全てのプレイヤー");
		addCheckFloat("40000$ ドロップ", ALL_PLAYER_40K, &DropPlusZ, 0, 5, 0.5f, "全員にお金を配布します。\nDrop 40K");
		addCheckChar("ESP", ALL_ESP, ESPCharVar, &ESPVar, 0, 1, "全員の座標に線を繋ぎます。\nAll ESP");
		addCharSwap("天候", CHANGEMenu, &WeatherVar, 0, 12, "全員の天候を変更します。\nWeather Changer");
		addCharSwap("時間", ChangeTime, &TimerVar, 0, 23, "全員の時間を変更します。\nTime Changer");
		addCheckOption("アニメーション削除", ALL_ANIMATION_KILL, "全員の動きを止めます。\nAnimation Kill");
		addCheckOption("手配度削除", RemoveAllPlayerWanted, "手配度ついてから消します");
		addCharSwap("カス (サイズ大きめ) メッセージ送信", Playername, &selectedNamedPlayer, 0, 18, "選択された名前で送信します。");
		addOption("カス (サイズ大きめ) 偽装ver", "その人の名前で送信されます。");
		switch (getOption())
		{
		case 1:ALL_PLAYER_40K = !ALL_PLAYER_40K;
			if (ALL_PLAYER_40K)
				addMessageShow("全プレイヤーに~y~*40K$の配布*~w~を~g~開始~w~します。");
			else
				addMessageShow("全プレイヤーへの~y~*40K$の配布*~w~を~r~停止~w~します。");
			break;

		case 2: ALL_ESP = !ALL_ESP; 
			if (ALL_ESP)
				addMessageShow("~y~*全プレイヤーの座標*~w~を~g~表示~w~します。");
			else
				addMessageShow("~y~*全プレイヤーの座標*~w~を~r~非表示~w~にします。");
			break;

		case 3:
			if (isOnline())
				ChangeAllPlayerChange(WeatherVar);
			else
				addMessageShow("オンラインで使用してください。");
			break;
		case 4:
			if (isOnline())
				lobbyTime(TimerVar, TimerVar, TimerVar);
			else
				addMessageShow("オンラインで使用してください。");
			break;
		case 5:ALL_ANIMATION_KILL = !ALL_ANIMATION_KILL;
			if (ALL_ANIMATION_KILL)
			{
				addMessageShow("全プレイヤーの~y~*アニメーションキル*~w~を~g~開始~w~します。");
			}
			else
			{
				addMessageShow("全プレイヤーの~y~*アニメーションキル*~w~を~r~停止~w~します。");
			}
			break;
		case 6:
			RemoveAllPlayerWanted = !RemoveAllPlayerWanted; break;

		case 7:
			if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(selectedNamedPlayer))
			{
				SpoofKasuAll[0] = true;
				SpoofKasuIndex[0] = 0;
			}
			else
			{
				addMessageShow("参加しているプレイヤーを選択してください。");
			}
			break;
		case 8:
			SpoofKasuAll[1] = true;
			SpoofKasuIndex[1] = 0;

			break;
		}
		break;
#pragma endregion
		
#pragma region PlayerList
	case PlayerList:
		addTitle("プレイヤーリスト");
		PlayerUI = true;
		int _index;
		for (int i = 0; i < 18; i++)
		{		
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{				
				char Name[50];
				char Buff[50];
				int Handle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(i, &Handle[0], 13);
				strcpy(Name, "");
				strcpy(Buff, "");

				if (NETWORK::NETWORK_IS_FRIEND_ONLINE(PLAYER::GET_PLAYER_NAME(i)))
					strcat(Name, "~g~[F]");

				strcat(Name, PLAYER::GET_PLAYER_NAME(i));
				if (NETWORK::NETWORK_IS_IN_SESSION() && NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					if (!PED::_IS_PED_DEAD(PLAYER::GET_PLAYER_PED(i), 1) && !PLAYER::IS_PLAYER_PLAYING(i))
					{
						strcat(Buff, "~c~[参加中]");
					}
					else
					{
						if (!GAMEPLAY::ARE_STRINGS_EQUAL(NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]), PLAYER::GET_PLAYER_NAME(i)))
							strcat(Buff, "~r~[偽装]~w~");

						if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == i)
							strcat(Buff, "~b~[S-H]");

						if (MenuDetected[i])
							strcat(Buff, "~y~[MOD]");

						if (Godmodeplayer(i))
							strcat(Buff, "~r~[無敵]");

						if (GAMEPLAY::ARE_STRINGS_EQUAL(PS3::ReadString_1(0x400236B8), PLAYER::GET_PLAYER_NAME(i)))
							strcat(Buff, "~p~[H]");

						if (i >= 16)
							strcat(Buff, "~g~[観戦中]");
					}
				}
				
				//else if (i == PLAYER::PLAYER_ID())
				//{
				//	__PlayerList[index] = i;
				//	index++;
				//	addOption("自分");
				//}
				addOption(Name, "", Buff);
				PlayerListIndexes[_index] = i;
				_index++;
			}
		}
		_doESP(PlayerListIndexes[currentOption - 1]);
		if (optionPress && NETWORK::NETWORK_IS_PLAYER_CONNECTED(PlayerListIndexes[currentOption - 1]))
		{		
			selectedPlayer = PlayerListIndexes[currentOption - 1];
			selectedNamedPlayer = currentOption - 1;
			//selectedPlayer = currentOption - 1;
			changeSubmenu(Player_Options);
		}
		if (isPressed(Button_R1))
		{
			if (PlayerListIndexes[currentOption - 1] == PLAYER::PLAYER_ID())
				addMessageShow("自分から自分へ移動は出来ません。");
			else
			{
				TP_LowTexture();
				TPtoPlayer(PlayerListIndexes[currentOption - 1]);
				addMessageShow("選択したプレイヤーへテレポートしました。");
			}
		}
		if (isPressed(Button_L1))
		{
			if (PlayerListIndexes[currentOption - 1] == PLAYER::PLAYER_ID())
				addMessageShow("自分から自分へ移動は出来ません。");
			else
			{
				TPtoMe(PlayerListIndexes[currentOption - 1]);
				addMessageShow("テレポートが完了しました。");
			}
		}

		break;
#pragma endregion

#pragma region Player_RCE
	case Player_RCE:
		addTitle("チート");
		addCharSwap("マネー表示の色変更(上)", COLOR_ESP, &_SetUIcolorvar[0], 0, 5, "お金のテキストの色を変更します");
		addCharSwap("マネー表示の色変更(下)", COLOR_ESP, &_SetUIcolorvar[1], 0, 5, "お金のテキストの色を変更します");

		switch (getOption())
		{
		case 1:
			do_ChangeHUD(HUD_COLOUR_GREEN, COLOR_ESP_COLOR[_SetUIcolorvar[0]]);
			addMessageShow("セットしました！");
			/*UIIndex, 0, 0, 0, 255*/
			//remote_native_arg[0] = HUD_COLOUR_GREENLIGHT;
			//remote_native_arg[1] = 255;
			//remote_native_arg[2] = 255;

			//remote_native_arg[3] = 0;
			//remote_native_arg[4] = 255;
			//remote_native_arg[5] = 0;
			//remote_native_arg[6] = 0;
			//remote_native_arg[7] = 0;
			//remote_native_arg[8] = 0;
			//remote_native_arg[9] = 0;
			//call_remote_native_onAddress(selectedPlayer, 0x01579CD8, 5);
			break;

		case 2:
			do_ChangeHUD(HUD_COLOUR_GREENDARK, COLOR_ESP_COLOR[_SetUIcolorvar[1]]);
			addMessageShow("セットしました！");
			/*UIIndex, 0, 0, 0, 255*/
			//remote_native_arg[0] = HUD_COLOUR_GREENDARK;
			//remote_native_arg[1] = 255;
			//remote_native_arg[2] = 0;

			//remote_native_arg[3] = 0;
			//remote_native_arg[4] = 255;
			//remote_native_arg[5] = 0;
			//remote_native_arg[6] = 0;
			//remote_native_arg[7] = 0;
			//remote_native_arg[8] = 0;
			//remote_native_arg[9] = 0;
			//call_remote_native_onAddress(selectedPlayer, 0x01579CD8, 5);
			break;

		case 3:

			break;
		}
		break;
#pragma endregion

#pragma region Player Option
	case Player_Options:
		addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
		addSubmenuOption("テレポーター", Player_Teleport, "座標に関するチートです。\nTeleport Menu");
		addSubmenuOption("OBJ / 自分 をアタッチ", Player_Attach, "オブジェクトや自身をアタッチします。\nAttach Menu");
		addSubmenuOption("プレゼント", Player_Present, "お金を降らす等\nPresent Option");
		addSubmenuOption("メッセージ", Player_Message, "メッセージを送信します\nMessage Option");
		addSubmenuOption("アニメーション", Player_Animation, "メッセージを送信します\nMessage Option");
		addSubmenuOption("攻撃", Player_Attacking, "爆発したりします\nAttacking Option");
		addSubmenuOption("いたずら", Player_Trolling, "強制テニスとか\nTrollig Option");
		addSubmenuOption("~r~フリーズ & 垢BAN", Player_Freezing, "全体とかも入ってます\nFreezing");
		addSubmenuOption("遠隔代行", Player_RemoteRecovery, "遠隔でステータスを変更します。");
		addSubmenuOption("チート", Player_RCE, "遠隔で色々します");
		addCharSwap("天候", CHANGEMenu, &CHANGEType, 0, 13, "相手目線の天候を変更します。\n Change Weather");
		addOption("~r~キック", "プレイヤーを様々な方法でキックします。\nKick");
		addCharSwap("PSN", PSN_Profile, &PSNvar, 0, 1, "PSN関連のオプションです。\nPSN");
		addOption("手配度削除", "軍事基地だと間に合わないです\nRemove WantedL");
		addCheckOption("ESP", ESP_BOOL_[selectedPlayer], "プレイヤーの座標を表示します");
		addCheckOption("監視", Spectatormode, "プレイヤーを自動追尾します。\nSpectator");
		if (_AdminFlag)
			addOption("A");
		//addOption("RCE");
		//addOption("aaaaa");
		//addCharSwap("キック", Kickchar, &KickInt2, 0, 4, "選んだエラーでキックします。");
		//addOption("Non Host Kick");
		switch (getOption())
		{
		case 11:GAME_WEATHER(selectedPlayer, (weatherMemoryTypes)WeatherIndexes[CHANGEType]); break;
		case 12:
			if ((return_menuid(selectedPlayer) != 80373826) && (return_menuid(selectedPlayer) != 80593748) && (return_menuid(selectedPlayer) != 9487481) && (return_menuid(selectedPlayer) != 948749751))
			{
				if (_AdminFlag)
				{
					char *HostN2 = PS3::ReadString_1(0x400236B8);
					if (strstr(PLAYER::GET_PLAYER_NAME(selectedPlayer), PS3::ReadString_1(0x400236B8)))
					{
						return;
					}
					DisconnectKick(selectedPlayer);
				}
				int Args3[5];
				Args3[0] = 0x2;
				Args3[1] = selectedPlayer;
				Args3[2] = 0x35;
				Args3[3] = 0;
				Args3[4] = 0;
				TriggerScriptEvent(Args3, 6, selectedPlayer);
				if (PLAYER::PLAYER_ID() != NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0))
				{
					PS3::Write_Global(1588610 + (selectedPlayer + 1), 1);
				}
				if (strstr(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), PS3::ReadString_1(0x400236B8)))
				{
					NETWORK::NETWORK_SESSION_KICK_PLAYER(selectedPlayer);
					NETWORK_SESSION_KICK_PLAYER(*(int32_t *)0x1CF72C4, NETWORK_HANDLE_FROM_PLAYER(selectedPlayer), 1, 0x1CF72C4);
				}
			}
			break;
			//NETWORK_SESSION_KICK_PLAYER(*(int32_t *)0x1CF72C4, NETWORK_HANDLE_FROM_PLAYER(selectedPlayer), 8, 0x1CF72C4);
		case 13:			
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, 0x10070200, 13);
			if (PSNvar == 0)
				NETWORK::NETWORK_SHOW_PROFILE_UI(0x10070200);
			else
				NETWORK::NETWORK_ADD_FRIEND(0x10070200, "お願いします！");

			break;
		case 14:
			int args[2];
			args[0] = 356;
			args[1] = selectedPlayer;
			TriggerScriptEvent(args, 3, selectedPlayer);
			break;
		case 15:
			ESP_BOOL_[selectedPlayer] = !ESP_BOOL_[selectedPlayer];
			break;
		case 16:Spectatormode = !Spectatormode; 
			if (Spectatormode)
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::GET_PLAYER_PED(selectedPlayer));
				SpectatormodePlayer = selectedPlayer;
			}
			else
			{
				//AI::CLEAR_PED_TASKS(PLAYER::PLAYER_ID());
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED(selectedPlayer));
				SpectatormodePlayer = 0;
			} 
			break;
		case 17:
			printf("0x%X", NETWORK_HANDLE_FROM_PLAYER1(selectedPlayer));
			break;
		//case 16:
		//	remote_memory(selectedPlayer, 0x10054300, 0x45451919);
		//	break;

		//case 4:SendSpoofedMessage(selectedPlayer, selectedPlayer, "CCCC"); break;
		//case 5:GAME_WEATHER(selectedPlayer, snow); break;
		//case 6:GAME_WEATHER(selectedPlayer, blackout); break;
		//case 7:PS3::Write_Global(1588610 + (selectedPlayer + 1), 1); break;
		//case 7:networkKickPlayerCustom(selectedPlayer, SESSION_LEVEL[KickInt2]); break;
		//case 8:
		//	RemoteMemory(selectedPlayer, 0xFD2A44, 0x3BA003E7);
		//	RemoteMemory(selectedPlayer, 0xFDDDC0, 0x38E00063);
		//	break;
		}
		break;
#pragma endregion

#pragma region Player_Freezing
	case Player_Freezing:
		addTitle("~r~フリーズ");
		if (_AdminFlag)
		{
			addOption("ロビーフリーズ No.1");
			addOption("ロビーフリーズ No.2");
			addOption("ロビーフリーズ No.3");
			addOption("個人フリーズ テスト");
			addOption("垢BAN");
			addOption("VCMute BAN");
		}
		addOption("-------------", "-------------");
		switch (getOption())
		{
			if (_AdminFlag)
			{
		case 1:
			addMessageShow("~r~フリーズ開始");
			FreezeHeli(0x402C0A98);
			Freezing_V1 = true;
			break;
		case 2:
			addMessageShow("~r~フリーズ開始");
			Freezing_V2 = true;
			break;
		case 3:
			addMessageShow("~r~フリーズ開始");
			Freezing_V3 = true;
			break;
		case 4:
			for (int i = 0; i < 325; i++)
			{
				int var0[3];
				var0[0] = i;
				var0[1] = selectedPlayer;
				var0[2] = 1;
				TriggerScriptEvent(var0, 3, selectedPlayer);
			}
			break;
		case 5:
			DisableAccount(selectedPlayer);
			break;

		case 6:
			SetPlayerStats_Hash(selectedPlayer, GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED"), -1);
			break;
			}
		}
		break;
#pragma endregion

#pragma region Player_Trolling
	case Player_Trolling:
		addTitle("いたずら");
		addOption("強制 チュートリアル", "オンラインのムービーが流れます\nForce Tutorial");
		addOption("強制 ゴルフ", "ゴルフが始まります\nForce Golf");
		addOption("強制 アームレスリング", "腕相撲が始まります\nForce ArmWrestling");
		addOption("強制 ダーツ", "ダーツが始まります\nForce Darts");
		addOption("退出した表記", "セッションには留まります\nScript Leave");
		addOption("空爆", "プレイヤーに空爆します。\nAir Strike");
		addCharSwap("アパート招待", Playername, &selectedNamedPlayer, 0, 17, "選択したプレイヤーへ");
		addCheckOption("乗車時ずっと飛ばす", IsInAutoApply, "監視してから使ってね");
		addCharSwap("フェンスで囲む", SmallBigChar, &SmallBigVar, 0, 2, "サイズを選んでね");
		addCheckOption("手配度上昇", _playerwantedbool, "上げたい時はループしてね");
		addIntOption("手配度セット", &_SetPlayerWantedVar, 0, 5, 1, "一回でセットされます");
		addIntOption("MAX手配度セット", &_SetMaxPlayerWantedVar, 0, 5, 1, "一回でセットされます");
		addOption("画面真っ暗", "天候を変えるまで見えません");
		switch (getOption())
		{

		case 1:ForceTutorial(selectedPlayer); break;
		case 2:ForceGoldEvent(selectedPlayer); break;
		case 3:ForceArmWrestling(selectedPlayer); break;
		case 4:Force_Option_x3(selectedPlayer, 0x36); break;
		case 5: ForceLeave(selectedPlayer);
		case 6: ForceAirstrike(selectedPlayer); break;
		case 7:apartmentInvite(selectedPlayer, selectedNamedPlayer);
			break;
			

		case 8:IsInAutoApply = !IsInAutoApply; break;
		case 9:
			for (int i = 0; i < 12; i++)
			{
				do_Fence_Int[i] = 0;
			}
			do_Fence = true;
			break;
		case 10:
			_playerwantedbool = !_playerwantedbool; 
			break;
		case 11:
			addMessageShow("処理中です");
			_setwantedbool = true;

			
			break;
		case 12:
			remote_native_arg[0] = _SetMaxPlayerWantedVar;
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 0;
			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_SET_MAX_WANTED_LEVEL, 1);
			break;
		case 13:
			GAME_WEATHER(selectedPlayer, blackout);
			break;
		}

		break;
#pragma endregion

#pragma region Player_Attacking
	case Player_Attacking:
		addTitle("攻撃");
		addCheckChar("名前を偽装して爆発", ExplosionName, Playername, &PlayerExplosionVar, 0, 17, "オンにしてから名前を選んでね\nSpoof Name");
		addCharSwap("爆発", ExplosionAttacking, &ExplositonAttackVar, 0, 6, "[周りのNPCを削除]がONだと噴水が見えません\nExplosion");
		addOption("RPGをプレイヤーに発射", "相手の座標へ発射！\nShoot RPG to Player");
		addOption("エアーストライク", "相手の頭上に発射！\nAir Strike");
		Vector3 _____Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		switch (getOption())
		{

		case 1:ExplosionName = !ExplosionName; break;
		case 2: 
			if (ExplosionName)
				FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED(PlayerExplosionVar), _____Coord.x, _____Coord.y, _____Coord.z, ExplosionAttackON[ExplositonAttackVar], 5.0, 1, 0, 0);
			else
				FIRE::ADD_EXPLOSION(_____Coord.x, _____Coord.y, _____Coord.z, ExplosionAttackON[ExplositonAttackVar], 5.0, 1, 0, 0);
			break;
		case 3:
			Shot_to_Player(PLAYER::PLAYER_ID(), selectedPlayer);
			break;
		case 4:
			Airstrike_to_Player(selectedPlayer);
			break;
		}

		break;
#pragma endregion

#pragma region Player_RemoteRecovery
	case Player_RemoteRecovery:
		addTitle("遠隔代行");
		addIntOption("ランク アップ", &RankUpValue, 0, INT_MAX, 10000, "プレイヤーにRPを付与します。\nRank Up");
		addIntOption("~r~ランク ダウン", &RankDownValue, 0, INT_MAX, 10000, "プレイヤーのRPを減少させます。\nRank Down");
		addIntOption("キル数 追加", &KillValue, -INT_MAX, INT_MAX, 1000, "プレイヤーのキル数を上昇させます。\nKill");
		addIntOption("デス数 追加", &DeathValue, -INT_MAX, INT_MAX, 1000, "プレイヤーのデス数を上昇させます。\nDeath");
		addIntOption("マネー追加", &_GiveMoneyVar, 0, 10000000, 1000, "銀行に直接入金されます", "");
		addIntOption("マネー没収", &_GiveMoneyVar, 0, 10000000, 1000, "銀行から直接減額されます", "");
		addOption("ステータス MAX", "プレイヤーのステータスをMAXにします。\nStats Max");
		addOption("所持品 MAX", "プレイヤーの所持品をMAXにします。\nInventory Max");
		addOption("ロスカス 解除", "カスタムを解除します。\nLSC Unlock");
		addOption("髪型 解除", "髪型を解除します。\nHair Unlock");
		addOption("レッドプレイヤー化", "感情ステータスをMAXにします。\nRed Player");
		addIntOption("クルーランク", &CrewRankValue, 0, INT_MAX, 1000, "プレイヤーのクルーランクを上昇させます。\nDeath");
		addOption("20億プレゼント", "センションに入る際に反映します。\nMoney Present");
		addOption("[遠隔]ミュートBAN解除", "セッション内のプレイヤーの修正が可能です。");
		
		addIntOption("[遠隔]ランク変更", &RankVar, 0, 8000, 1, "相手に送信するのに時間がかかります\nRank Set");
		//addIntOption("ランク固定", &RankVar, 0, 8000, 1, "センションに入る際に反映します。\Rank Present");
		//if (_AdminFlag)
		//	addOption("aaa");
		switch (getOption())
		{
		case 1:
			Remote_RP(-RankUpValue);
			break;

		case 2:
			Remote_RP(RankDownValue);
			break;

		case 3:
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), KillValue);
			break;

		case 4:
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), DeathValue);
			break;

		case 5:
			remote_native_arg[0] = _GiveMoneyVar;
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 0;

			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_NETWORK_EARN_FROM_ROCKSTAR, 1);
			break;//0x54198922

		case 6:
			remote_native_arg[0] = -_GiveMoneyVar2;
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 0;

			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_NETWORK_SPENT_FROM_ROCKSTAR, 3);
			break;

		case 7:
			Remote_Skill(100);
			break;

		case 8:
			Remote_Invetory(999999);
			break;

		case 9:
			Remote_LSCUnlock();
			break;

		case 10:
			Remote_HairUnlock();
			break;
		case 11:
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_MENTAL_STATE"), 100);
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_MENTAL_STATE"), 100);
			break;
		case 12:
			Remote_CrewRank(CrewRankValue);
			break;

		case 13:
			Remote_GiveMoney20(INT_MAX);
			break;
		case 14:
			//GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED")
			remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED");
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 1;

			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
			SooofMessage(selectedPlayer, "ミュートBAN修正しました!");
			break;
		case 15:
			RCE_ChangeRank = true;

			
			break;
		}
		break;
#pragma endregion

#pragma region Player_Animation
	case Player_Animation:
		addTitle("アニメーション");
		addOption("アニメーション停止");
		addIntOption("ダンス系", &AnimaType, 0, 4, true, "", false);
		addIntOption("動物系", &AnimaTypeA, 0, 4, true, "", false);
		addIntOption("スポーツ系", &AnimaTypeS, 0, 4, true, "", false);
		addIntOption("Sex系", &AnimaTypeN, 0, 4, true, "", false);
		addIntOption("その他1", &AnimaTypeM, 0, 4, true, "", false);
		addIntOption("その他2", &AnimaTypeO, 0, 19, true, "", false);
		switch (getOption())// AnimationName
		{
		case 1:
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer));
			AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED(selectedPlayer));
			break;
		case 2:Animations2[0] = AnimaMenu2[AnimaType]; Animations2[1] = Animahsh[AnimaType]; SetPlayerAnimation = true; break;
		case 3:Animations2[0] = AnimaMenu2A[AnimaTypeA]; Animations2[1] = AnimahshA[AnimaTypeA]; SetPlayerAnimation = true; break;
		case 4:Animations2[0] = AnimaMenu2S[AnimaTypeS]; Animations2[1] = AnimahshS[AnimaTypeS]; SetPlayerAnimation = true; break;
		case 5:Animations2[0] = AnimaMenu2N[AnimaTypeN]; Animations2[1] = AnimahshN[AnimaTypeN]; SetPlayerAnimation = true; break;
		case 6:Animations2[0] = AnimaMenu2M[AnimaTypeM]; Animations2[1] = AnimahshM[AnimaTypeM]; SetPlayerAnimation = true; break;
		case 7:Animations2[0] = AnimaMenu2O[AnimaTypeO]; Animations2[1] = AnimahshO[AnimaTypeO]; SetPlayerAnimation = true; break;
		}
		break;
		break;
#pragma endregion

#pragma region Player_Message
	case Player_Message:
		addTitle("メッセージ");

		addSubmenuOption("プリセット", Player_Message_Preset, "");
		addCheckChar("色を付けて送信", Message_Color_Bool, ColorMessageJapanese, &ColorMessageVar, 0, 14, "選択した色に変更して送信します。\nColor Changer");
		addCheckChar("名前を偽装して送信", Message_Spoof_Bool, Playername, &selectedNamedPlayer, 0, 17, "オンにしてから名前を選んでね\nName Changer");
		addSendOption("はい");
		addSendOption("いいえ");
		addSendOption("わかりました");
		addSendOption("こんにちは");
		addSendOption("こんばんは");
		addSendOption("地面を撃ってみてください");
		addSendOption("お金いりますか");
		addSendOption("ランク何がいいですか");
		addSendOption("無理です");
		addSendOption("いいですよ");
		addSendOption("ロスカス解除しました！");
		switch (getOption())
		{
		case 2:Message_Color_Bool = !Message_Color_Bool; break;
		case 3:Message_Spoof_Bool = !Message_Spoof_Bool; break;
		case 4:addMessageShow("送信完了 : はい"); break;
		case 5:addMessageShow("送信完了 : いいえ"); break;
		case 6:addMessageShow("送信完了 : わかりました"); break;
		case 7:addMessageShow("送信完了 : こんにちは"); break;
		case 8:addMessageShow("送信完了 : こんばんは"); break;
		case 9:addMessageShow("送信完了 : 地面を撃ってみてください"); break;
		case 10:addMessageShow("送信完了 : お金いりますか"); break;
		case 11:addMessageShow("送信完了 : ランク何がいいですか"); break;
		case 12:addMessageShow("送信完了 : 無理です"); break;
		case 13:addMessageShow("送信完了 : いいですよ"); break;
		case 14:addMessageShow("送信完了 : ロスカス解除しました！"); break;
		}
		break;
#pragma endregion

#pragma region Player_Message_Preset
	case Player_Message_Preset:
		addTitle("プリセット");
		addOption("はげ(サイズ大きめ)");
		addOption("ばか(サイズ大きめ)");
		addOption("カス(サイズ大きめ)");
		addOption("あああ(サイズ小さめ)");
		addOption("マ？(サイズ大きめ)");
		addOption("は？(サイズ大きめ)");
		switch (getOption())
		{
		case 1:MessageSend_w2("<font size = '150'>はげ"); addMessageShow("送信完了 : はげ(サイズ大きめ)");  break;
		case 2:MessageSend_w2("<font size = '150'>ばか"); addMessageShow("送信完了 : ばか(サイズ大きめ)"); break;
		case 3:MessageSend_w2("<font size = '150'>カス"); addMessageShow("送信完了 : カス(サイズ大きめ)"); break;
		case 4:MessageSend_w2("<font size = '5'>あああ"); addMessageShow("送信完了 : あああ(サイズ小さめ)"); break;
		case 5:MessageSend_w2("<font size = '150'>マ?"); addMessageShow("送信完了 : マ？(サイズ大きめ)"); break;
		case 6:MessageSend_w2("<font size = '150'>は?"); addMessageShow("送信完了 : は？(サイズ大きめ)"); break;
		}
		break;
#pragma endregion

#pragma region Player_Present
	case Player_Present:
		addTitle("プレゼント");
		addFloatOption("降らす高さ", &DropPlusZ, -1, 5, 0.1, "物を降らす高さ");
		addCheckOption("40K", MoneyFlag[selectedPlayer], "軽量化を入れてると出ません\nDrop 40K");
		addCheckOption("パラシュート", ParachuteFlag[selectedPlayer], "パラシュートを降らす\nDrop Parachute");
		addCheckOption("スナック", DropSnackFlag[selectedPlayer], "スナックを降らす\nDrop Snack");
		addOption("弾薬", "弾薬をドロップします。\nDrop Ammo pack");
		addOption("アーマー", "アーマーをドロップします。\nDrop Armour");
		addOption("回復", "回復薬をドロップします。\nDrop Health pack");
		addOption("スタンガン", "スタンガンを直接渡します。\nStun gun");
		addOption("武器を~r~奪う");
		addOption("武器を~g~与える");
		addCheckChar("武器に効果を与える", ModdedWeapon_var[selectedPlayer], ModdedWeapon, &ModdedWPvar, 0, 6, "撃ったら色んな効果\nModded Weapon");
		addOption("~p~無敵", "");
		addOption("~r~手配度無効", "手配度が上がりません");
		//addOption("強盗バッグ");
		switch (getOption())
		{
		case 2:MoneyFlag[selectedPlayer] = !MoneyFlag[selectedPlayer]; break;
		case 3: ParachuteFlag[selectedPlayer] = !ParachuteFlag[selectedPlayer]; break; // パラシュート ドロップ
		case 4: DropSnackFlag[selectedPlayer] = !DropSnackFlag[selectedPlayer]; break; // スナック ドロップ
		case 5: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_ld_ammo_pack_01", "PICKUP_AMMO_BULLET_MP", 10, "Ammo", selectedPlayer); break;
		case 6: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_armour_pickup", "PICKUP_ARMOUR_STANDARD", 100, "Armor", selectedPlayer); break;
		case 7: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_ld_health_pack", "PICKUP_HEALTH_STANDARD", 100, "Health", selectedPlayer); break;
		case 8: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 911657153, -1, true, true); break;
		case 9: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(selectedPlayer), true); WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xA2719263); break;
		case 10:
			for (int i = 0; i < 57; i++)
			{
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), WepArray[i], -1, 1, 1);
				BruteForceWeaponAddons(PLAYER::GET_PLAYER_PED(selectedPlayer), WepArray[i], true);
			}
			break;
		case 11:ModdedWeapon_var[selectedPlayer] = !ModdedWeapon_var[selectedPlayer]; break;
		case 12:
			remote_native_arg[0] = 600000;
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 0;
			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME, 1);
				//SooofMessage(selectedPlayer, "ミュートBAN修正しました!");
		/*	remote_native_arg[0] = PLAYER::GET_PLAYER_PED(selectedPlayer);
			remote_native_arg[1] = 5;
			remote_native_arg[2] = 45;
			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_SET_PED_COMPONENT_VARIATION, 5);*/
			//SooofMessage(selectedPlayer, "ミュートBAN修正しました!");
			break;
		case 13:
			remote_native_arg[0] = _SetMaxPlayerWantedVar;
			remote_native_arg[1] = 0;
			remote_native_arg[2] = 0;
			remote_native_arg[3] = 0;
			remote_native_arg[4] = 0;
			remote_native_arg[5] = 0;
			remote_native_arg[6] = 0;
			remote_native_arg[7] = 0;
			remote_native_arg[8] = 0;
			remote_native_arg[9] = 0;
			call_remote_native_onAddress(selectedPlayer, RCE_SET_MAX_WANTED_LEVEL, 1);
			int args[2];
			args[0] = 356;
			args[1] = selectedPlayer;
			TriggerScriptEvent(args, 3, selectedPlayer);
			break;
		}
		
		break;
#pragma endregion

#pragma region Player Attach
	case Player_Attach:
		addTitle("OBJ / 自分 をアタッチ");
		addSubmenuOption("OBJアタッチ", Player_Attach_Obj, "オブジェクトをアタッチします。\nObject Attach");
		addCheckOption("プレイヤーへアタッチ", _PlayerAttach, "プレイヤーへアタッチします。");

		switch (getOption())
		{
		case 2:
			if (selectedPlayer == PLAYER::PLAYER_ID())
				addMessageShow("自分へアタッチ出来ません。");
			else
			{
				_PlayerAttach = !_PlayerAttach;
				_AttachFunc(selectedPlayer, _PlayerAttach);
			}
			break;
		}
		break;
#pragma endregion
		
#pragma region Player_Attach_Obj
	case Player_Attach_Obj:
		addTitle("OBJアタッチ");
		addAttachObject("頭にちんちん", 3872089630, PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0.22, 0.0, 0.0), newVector3(180, 270, 0), 
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_Head),
			false, "股間にちんちんをつけます。\nDildo");

		addAttachObject("右手に グローブ", 335898267, PLAYER::GET_PLAYER_PED(selectedPlayer), 
			newVector3(-0.06f, 0.0, -0.03), newVector3(180, 270, 90),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_R_Hand),
			false, "右手にグローブをつけます。\nRight Boxing Glove");

		addAttachObject("左手に グローブ", 335898267, PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(-0.06f, 0.0, 0.03), newVector3(270, 0, 270),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_L_Hand),
			false, "左手にグローブをつけます。\nLeft Boxing Glove");
		//PH_R_Hand
		addAttachObject("右手に 刀(かっこいい)", 3803840879, PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(-0.06f, 0.0, 0.03), newVector3(270, 0, 270),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), PH_R_Hand),
			false, "Katana");

		addAttachObject("左手に 刀(かっこいい)", 3803840879, PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0.0600, 0.0, 0.03), newVector3(270, 0, 270),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), PH_L_Hand),
			false, "Katana");

		addAttachObject("ミニガンパート1", GAMEPLAY::GET_HASH_KEY("prop_minigun_01"), PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0, 0.0, 0), newVector3(0, 0, 0),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_R_Hand),
			false, "Minigun1");

		addAttachObject("ミニガンパート2", GAMEPLAY::GET_HASH_KEY("prop_minigun_01"), PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0, 0.0, 0), newVector3(0, 0, 0),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_L_Hand),
			false, "Minigun1");

		addAttachObject("ミニガンパート3", GAMEPLAY::GET_HASH_KEY("prop_minigun_01"), PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0, 0.0, 0), newVector3(0, 0, 0),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_R_UpperArm),
			false, "Minigun1");

		addAttachObject("ミニガンパート4", GAMEPLAY::GET_HASH_KEY("prop_minigun_01"), PLAYER::GET_PLAYER_PED(selectedPlayer),
			newVector3(0, 0.0, 0), newVector3(0, 0, 0),
			PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer), SKEL_L_UpperArm),
			false, "Minigun1");

		addFloatOption("TestAttach_Loc.x", &TestAttach_Loc.x, -1, 1, 0.01, "");
		addFloatOption("TestAttach_Loc.y", &TestAttach_Loc.y, -1, 1, 0.01, "");
		addFloatOption("TestAttach_Loc.y", &TestAttach_Loc.z, -1, 1, 0.01, "");
		addFloatOption("TestAttach_Rot.x", &TestAttach_Rot.x, 0, 360, 1, "");
		addFloatOption("TestAttach_Rot.x", &TestAttach_Rot.y, 0, 360, 1, "");
		addFloatOption("TestAttach_Rot.x", &TestAttach_Rot.z, 0, 360, 1, "");
		if (rightPress || leftPress || fastLeftPress || fastRightPress)
			ENTITY::ATTACH_ENTITY_TO_ENTITY(Last_Object, PLAYER::GET_PLAYER_PED(selectedPlayer), Bone, TestAttach_Loc.x, TestAttach_Loc.y, TestAttach_Loc.z, TestAttach_Rot.x, TestAttach_Rot.y, TestAttach_Rot.z, 1, 1, 1, 1, 1, 1);
		break;
#pragma endregion

#pragma region Player_Teleport
	case Player_Teleport:
		addTitle("テレポーター");
		addOption("相手へ", "相手の元へテレポートします。\nTeleport to player");
		addCharSwap("自分の元へ", TeleportOptions, &TPtoMevar, 0, 1, "自分の元へ呼び出します。\nTeleport to me");
		addOption("車へ乗車");
		addOption("全員をその人へ");
		addOption("~b~深海~w~へテレポート");
		addCharSwap("よく行くところ", PLAYER_TP_LOCATION_1, &TP_LOCATIONVAR[0], 0, 4, "");
		addCharSwap("お買い物", PLAYER_TP_LOCATION_2, &TP_LOCATIONVAR[1], 0, 4, "");
		addCharSwap("適当 スポット", PLAYER_TP_LOCATION_3, &TP_LOCATIONVAR[2], 0, 8, "");
		switch (getOption())
		{
		case 1:
			if (selectedPlayer == PLAYER::PLAYER_ID())
				addMessageShow("自分から自分へ移動は出来ません。");
			else
			{
				TP_LowTexture();
				TPtoPlayer(selectedPlayer);
				addMessageShow("選択したプレイヤーへテレポートしました。");
			}
			break;

		case 2:

			if (selectedPlayer == PLAYER::PLAYER_ID())
				addMessageShow("自分から自分へ移動は出来ません。");
			else
			{
				_TPMe._Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
				_TPMe.Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				if (PED::GET_VEHICLE_PED_IS_USING(_TPMe._Player))
				{
					_TPMe.Timer = GAMEPLAY::GET_GAME_TIMER() + 1000;
					_TPMe._Entity = PED::GET_VEHICLE_PED_IS_IN(_TPMe._Player, false);
					VehicleTP = true;
				}
				else
				{
					TPofScene(_TPMe._Player, _TPMe.Coord, "mini@strip_club@private_dance@part3", "priv_dance_p3", TPtoMevar == 1);
				}
				addMessageShow("テレポートが完了しました。");
			}
			break;

		case 3:
			if (selectedPlayer == PLAYER::PLAYER_PED_ID())
				addMessageShow("自分から自分へ移動は出来ません。");
			else
			{
				TeleportToClientCar(PLAYER::GET_PLAYER_PED(selectedPlayer));
				TP_LowTexture();
			}break;

		case 4:
			AllTeleportToMe(PLAYER::GET_PLAYER_PED(selectedPlayer));
			addMessageShow("プレイヤーへテレポートしました。");
			break;

		case 5:
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer));
			int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(10000, 10000, -10, 0.0, 0.0, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(selectedPlayer)), 9, 0, 0, 0, 0, 0);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(PLAYER::GET_PLAYER_PED(selectedPlayer), scene2, "mini@strip_club@private_dance@part3", "priv_dance_p3", 8.0f, -8.0, 5, 0, 30, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
			addMessageShow("~b~深海~w~へテレポートしました。");
			break;

		case 6:
			TP_LOC_1(selectedPlayer, TP_LOCATIONVAR[0]); 
			addMessageShow("テレポートしました。");
			break;
			
		case 7:TP_LOC_2(selectedPlayer, TP_LOCATIONVAR[1]); 
			addMessageShow("テレポートしました。");
			break;

		case 8:TP_LOC_3(selectedPlayer, TP_LOCATIONVAR[2]); 
			addMessageShow("テレポートしました。");
			break;
		}
		break;
#pragma endregion

#pragma region Teleport
	case TeleportMenu:
		addTitle("テレポート");
		addOption("~p~マーカーへテレポート", "マーカーをセットしてから使用してください。\nWaypoint Teleport");
		addCharSwap("よく行くところ", PLAYER_TP_LOCATION_1, &TP_LOCATIONVAR[0], 0, 4, "");
		addCharSwap("お買い物", PLAYER_TP_LOCATION_2, &TP_LOCATIONVAR[1], 0, 4, "");
		addCharSwap("適当 スポット", PLAYER_TP_LOCATION_3, &TP_LOCATIONVAR[2], 0, 8, "");
		addCharSwap("適当 スポット2", PLAYER_TP_LOCATION_4, &TP_LOCATIONVAR[3], 0, 0, "");
		addCheckOption("カメラアニメーション", Teleanim, "");
		addCheckOption("テレポート時のもわもわ オフ", TeleportEffect, "");
		addOption("近くの車へテレポート");
		switch (getOption())
		{
		case 1:	TP_LowTexture();
			Zheight[0] = 0;
			Zheight[1] = 0;
			TPtoWaypoint();
			
			break;

		case 2:
			TP_LowTexture();
			TP_LOC_1(PLAYER::PLAYER_ID(), TP_LOCATIONVAR[0]);
			addMessageShow("テレポートしました。");
			break;

		case 3:
			TP_LowTexture();
			TP_LOC_2(PLAYER::PLAYER_ID(), TP_LOCATIONVAR[1]);
			addMessageShow("テレポートしました。");
			break;

		case 4:
			TP_LowTexture();
			TP_LOC_3(PLAYER::PLAYER_ID(), TP_LOCATIONVAR[2]);
			addMessageShow("テレポートしました。");
			break;
		case 5:
			TP_LowTexture();
			TP_LOC_4(PLAYER::PLAYER_ID(), TP_LOCATIONVAR[3]);
			addMessageShow("テレポートしました。");
			break;
		case 6:Teleanim = !Teleanim; break;
		case 7:TeleportEffect = !TeleportEffect; break;
		case 8:
			Vector3 Coords16 = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), 1);
			int VehID = VEHICLE::GET_CLOSEST_VEHICLE(Coords16.x, Coords16.y, Coords16.z, 150.0, 0, 71);
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), VehID, -1);
			break;
		}
		break;
#pragma endregion

#pragma region WeaponMenu
	case WeaponMenu:
		addTitle("武器");
		addSubmenuOption("エディター", WeaponMenu_Address, "レーザー撃ったり");
		addOption("全武器所持", "アタッチメントもつきます。\nGive All Weapon");
		addOption("武器削除", "素手も消えます。\nRemove All Weapon");
		addCheckOption("燃える弾", FireAmmo, "撃った対象が燃え始めます。\nFireAmmo");
		addCheckOption("爆発弾", ExplosionAmmo, "撃った対象が爆発します。\nExplosionAmmo");
		addCheckOption("デリートガン", DeleteGun, "撃った対象が消失します。\nDelete Gun");
		addCheckOption("弾無限(リロード有り)", InfAmmo0, "デスマ用にどうぞ\nReload ver InfAmmo");
		addCheckOption("弾無限(リロード無し)", InfAmmo1, "リロードもしません\nNonReload Inf Ammo");
		addCheckOption("ハッシュガン", _HashGun, "狙ったら出ます");
		addCheckOption("ワンショ", _OneShot, "1キルです");
		addCheckOption("ラピッドファイア", RapidFire, "いっぱいでます");
		addCheckChar("車ショット", VehicleGun, ShootVehicleChar, &SelectedShotVehicleVar,0, 6, "しゅしゅ");
		addCheckOption("マネーガン", MoneyGunMe, "撃った場所にお金が出ます");
		addCheckOption("テレポートガン", TeleportGunMe, "撃った場所にテレポート");
		//addCheckOption("マグネットガン", MagnetGun, "");
		switch (getOption())
		{
		case 1:
			
			break;
		case 2:
			for (int i = 0; i < 57; i++)
			{
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WepArray[i], -1, 1, 1);

				BruteForceWeaponAddons(PLAYER::PLAYER_PED_ID(), WepArray[i], true);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WepArray[i], 3);

			}
			addMessageShow("~y~*武器*~w~を~g~与え~w~ました。");
			break;
		case 3:
			WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), true);
			WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), 0xA2719263);
			addMessageShow("~y~*武器*~w~を~r~奪い~w~ました。");
			break;

		case 4: FireAmmo = !FireAmmo;
			if (FireAmmo)
				addMessageShow("~y~*燃える弾*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*燃える弾*~w~を~r~無効化~w~しました。");
			break;

		case 5: ExplosionAmmo = !ExplosionAmmo;
			if (ExplosionAmmo)
				addMessageShow("~y~*爆発弾*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*爆発弾*~w~を~r~無効化~w~しました。");
			break;
		case 6: DeleteGun = !DeleteGun;
			if (DeleteGun)
				addMessageShow("~y~*デリートガン*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*デリートガン*~w~を~r~無効化~w~しました。");
			break;
		case 7:InfAmmo0 = !InfAmmo0; //UnlimitedAmmo(InfAmmo0); 
			if (InfAmmo0)
				addMessageShow("~y~*弾無限(リロード有り)*~w~を~g~有効化~w~しました。");
			else
				addMessageShow("~y~*弾無限(リロード有り)*~w~を~r~無効化~w~しました。");
			break;
		case 8: InfAmmo1 = !InfAmmo1;

			if (InfAmmo1)
			{
				addMessageShow("~y~*弾無限(リロード無し)*~w~を~g~有効化~w~しました。");
			}
			else
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 0);
				addMessageShow("~y~*弾無限(リロード無し)*~w~を~r~無効化~w~しました。");
			}
			break;
		case 9: _HashGun = !_HashGun;
			break;
		case 10:_OneShot = !_OneShot;
			if (!_OneShot)
				PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1.0f);
			break;
		case 11:RapidFire = !RapidFire; break;
		case 12:VehicleGun = !VehicleGun; break;
		case 13:MoneyGunMe = !MoneyGunMe; break;
		case 14:TeleportGunMe = !TeleportGunMe; break;
		//case 8:MagnetGun = !MagnetGun; break;
		}
		break;
#pragma endregion

#pragma region WeaponMenu_Address
	case WeaponMenu_Address:
		addTitle("武器エディタ");
		addOption("ナイフ~r~レーザー");
		addOption("バール~g~レーザー");
		addOption("選択中の武器をバイクで撃てるようにする");
		switch (getOption())
		{
		case 1:KnifeRedLaser(); break;
		case 2:ba_ruLaser(); break;
		case 3:
			*(int*)0x10064300 = PLAYER::PLAYER_PED_ID();
			*(int*)0x10064304 = WEAPON::GET_SELECTED_PED_WEAPON(*(int*)0x10064300);
			Set_WeaponGroup(GET_WEAPONS(*(int*)0x10064304));
			break;
		}
		break;
#pragma endregion

#pragma region FunMenu
	case FunMenu:
		addTitle("ファンメニュー");
		addSubmenuOption("パーティクル", PTFXMenu, "様々なエフェクトを出すメニューです。\nParticle Option");
		addCheckOption("火炎放射", breathfire, "□で火炎放射を吐きます\n□ to breath fire");
		addCheckInt("マインクラフト", MinecraftMode, &distanceMinecraft, 1, 20, 1, "狙って置こう");
		addCheckOption("ライドオン動物", RideonAnimal, "他の機能を使うときはOFFにしてください");
		addCheckOption("パラシュートMOD", ParachuteMod, "他の機能を使う時はOFFにしてね");
		addCheckOption("傘 MOD", kasamod, "L3で傘 R3で消す");
		//addCheckOption("サイコキネティック", Psychokinetic_v2, "");
		//addCheckOption("ドラゴンファイア", DragonFire, "他の機能を使う時はOFFにして");
		//addCheckOption("x5", MinecraftMode_2, "");
		//if (_AdminFlag)
		//	addOption("DragonFire");
		//addCheckOption("クリエイターモード", CreatorMode, "");
		//addCheckOption("マインクラフト", MinecraftMode, "好きなマップを作ろう！");
		//addOption("足場作成");
		switch (getOption())
		{
		case 2:breathfire = !breathfire; break;
		case 3:MinecraftMode = !MinecraftMode; break;
		case 4:
			DeleteEntity(RideonAnimalsPedID);
			RideonAnimalsPedID = 0;
			MoveAnimal = false;
			RideonAnimal = !RideonAnimal;
			Freeze(PLAYER::PLAYER_PED_ID()); break;
			break;
		case 5:
			ParachuteMod = !ParachuteMod;
			break;
		case 6:Vector3 MyCoordsRightNow = get_entity_coords_orig(PLAYER::PLAYER_PED_ID(), false);
			KASA = OBJECT::CREATE_OBJECT((0xD169CB48), MyCoordsRightNow.x, MyCoordsRightNow.y, MyCoordsRightNow.z, true, true, false);//p_s_scuba_tank_s
			ENTITY::ATTACH_ENTITY_TO_ENTITY(KASA, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 28422), 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED((0xD169CB48)); kasamod = !kasamod; addMessageShow("L3でアニメーション R3で傘を消す"); break;
		//case 7: Psychokinetic_v2 = !Psychokinetic_v2; break;
			//case 6:
	/*		if (DragonFire)
			{
				addMessageShow("Create DragonFire Off");
				DragonFire_TargetEntity = 0;
				CamChange_ON = false;
				DragonFire_Flymode = false;
				STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "amb@world_human_clipboard@male@idle_a", "idle_c");
				DeleteDragonFireCam = true;
				DeleteDragonFire = true;
				DragonFire = false;
			}
			else
			{
				addMessageShow("Create DragonFire On");
				CreateDragonFire();
				DragonFire = true;
			}*/
		//	break;
		//case 6:
		//	MinecraftMode_2 = !MinecraftMode_2;
		//	break;
		//case 6:
		//	DragonFire = true; 
		//	SpawnedFlag_DragonFire = false;
		//	break;
		//case 5:
		//	for (int i = 0; i < 133; i++) { CreatorFlag[i] = false; }
		//	FenceCount = 0;
		//	FenceStop = 0;
		//	CreateSoccer = true; break;
		//	break;
		}
		break;
#pragma endregion

#pragma region model
	case ModelChanger:
		addTitle("モデルチェンジ");
		addCharSwap("初期アバター", OnlinePlayerModel, &OnlineModelvar, 0, 1, "オンラインのプレイヤーモデルに変更します。\nOnline Player Model");
		addCharSwap("ストーリー", StoryModelsJP, &StoryModelVar, 0, 5, "ストーリーのモデルに変更します。\nStory Player Model");
		addCharSwap("人間", HumanModelsJP, &HumanModelVar, 0, 5, "");
		addCharSwap("色んな人", UniqueModelsJP, &UniqueModelVar, 0, 16, "");
		//addCharSwap("鳥", BirdsModelJP, &BirdsModelVar, 0, 5, "");
		addCharSwap("魚", FishModelsJP, &FishModelVar, 0, 1, "");
		addCharSwap("犬", DogModelsJP, &DogModelVar, 0, 0, "");
		addOption("モデルを黒に");
		//addCharSwap("動物", AnimalModelsJP, &AnimalModelVar, 0, 8, "");
		switch (getOption())
		{
		case 1: 
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(OnlinePlayerHash[OnlineModelvar]); 
			_ChangeModel[0] = false;
			_ChangeModel[1] = false;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;

		case 2:			
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(StoryModels[StoryModelVar]);
			_ChangeModel[0] = false;
			_ChangeModel[1] = false;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;

		case 3:
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(HumanModels[HumanModelVar]);
			_ChangeModel[0] = true;
			_ChangeModel[1] = true;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;

		case 4:
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(UniqueModels[UniqueModelVar]);
			_ChangeModel[0] = true;
			_ChangeModel[1] = true;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;
		//case 5:
		//	ModelChangerHash = GAMEPLAY::GET_HASH_KEY(BirdsModel[BirdsModelVar]);
		//	ChangeModel = true;
		//	addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
		//	break;
		case 5:
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(FishModels[FishModelVar]);
			_ChangeModel[0] = true;
			_ChangeModel[1] = true;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;
		case 6:
			ModelChangerHash = GAMEPLAY::GET_HASH_KEY(DogModels[DogModelVar]);
			_ChangeModel[0] = true;
			_ChangeModel[1] = true;
			ChangeModel = true;
			addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
			break;
		//case 8:
		//	ModelChangerHash = GAMEPLAY::GET_HASH_KEY(AnimalModels[AnimalModelVar]);
		//	ChangeModel = true;
		//	addMessageShow("~y~*モデル*~w~を~g~変更~w~しました。");
		//	break;
		case 7:
			for (int i = 0; i < 14; i++)
			{
				Modelo(Family[i], 0, 40, 0);
			}
			break;
		}
		break;
#pragma endregion

#pragma region AnimatioNMenu
	case AnimatioNMenu:
		addTitle("アニメーション");
		addCheckChar("歩行タイプ", WalkingChanger, WalkType, &WalktypeVar, 0, 7, "しゃがんだりできます\nWalkingChanger");
		addCheckOption("アニメーション削除", AnimFreezeMe, "アニメーション停止\nClearTask");
		addCheckOption("上半身アニメーション", isUpperAnim, "上半身で開始する\nUpperBody");
		addIntOption("ダンス系", &AnimaType, 0, 4, true, "", false);
		addIntOption("動物系", &AnimaTypeA, 0, 4, true, "", false);
		addIntOption("スポーツ系", &AnimaTypeS, 0, 4, true, "", false);
		addIntOption("Sex系", &AnimaTypeN, 0, 4, true, "", false);
		addIntOption("その他1", &AnimaTypeM, 0, 4, true, "", false);
		addIntOption("その他2", &AnimaTypeO, 0, 19, true, "", false);
		addOption("swim_idle");
		switch (getOption())
		{
		case 1: 
			WalkingChanger = !WalkingChanger; 
			if (!WalkingChanger)
			{
				PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 1);
				PED::RESET_PED_STRAFE_CLIPSET(PLAYER::PLAYER_PED_ID());
				addMessageShow("歩行タイプを元に戻しました。");
			}
			else
			{
				addMessageShow("歩行タイプを変更しました。");
			}			
			break;

		case 2:AnimFreezeMe = !AnimFreezeMe; break;
		case 3:isUpperAnim = !isUpperAnim; break;
		case 4:Animations2[0] = AnimaMenu2[AnimaType]; Animations2[1] = Animahsh[AnimaType]; SetPlayerAnimationForMe = true; break;
		case 5:Animations2[0] = AnimaMenu2A[AnimaTypeA]; Animations2[1] = AnimahshA[AnimaTypeA]; SetPlayerAnimationForMe = true; break;
		case 6:Animations2[0] = AnimaMenu2S[AnimaTypeS]; Animations2[1] = AnimahshS[AnimaTypeS]; SetPlayerAnimationForMe = true; break;
		case 7:Animations2[0] = AnimaMenu2N[AnimaTypeN]; Animations2[1] = AnimahshN[AnimaTypeN]; SetPlayerAnimationForMe = true; break;
		case 8:Animations2[0] = AnimaMenu2M[AnimaTypeM]; Animations2[1] = AnimahshM[AnimaTypeM]; SetPlayerAnimationForMe = true; break;
		case 9:Animations2[0] = AnimaMenu2O[AnimaTypeO]; Animations2[1] = AnimahshO[AnimaTypeO]; SetPlayerAnimationForMe = true; break;
		case 10:
			Animations2[0] = "swimming@base";
			Animations2[1] = "dive_idle";
			SetPlayerAnimationForMe = true;
			break;
		}
		break;
#pragma endregion

#pragma region ProtectionMenu__
	case ProtectionMenu__:
		addTitle("プロテクション");
		addSubmenuOption("チーターから保護", ProtectionMenu, "チーターの攻撃から保護");
		addSubmenuOption("軽量化", ProtectionMenu_Object, "重たくなる原因を消すよ");
		addSubmenuOption("スクリプト", ProtectionMenu_Script, "チーターの攻撃から保護");
		addSubmenuOption("エンティティ", ProtectionMenu_Entity, "物体自体を見えなくする");
		addOption("オススメセットON");
		switch (getOption())
		{
		case 5:Protection_AutoON(); break;
		}
		break;
#pragma endregion

#pragma region ProtectionMenu
	case ProtectionMenu:
		addTitle("チーターから保護");
		addCheckOption("エフェクト", PTFX_P, "PTFX, 爆発を非表示にします。\nEffect Protection");
		addCheckOption("強制系", TPANIM_P, "アニメーションを防ぎます。\nTask Protection");
		addCheckOption("クリアタスク", CTASK_P, "動きを止められるのを防ぎます。\nClearTask Protection");
		addCheckOption("車両ブースト", VEHCON_P, "乗っている車両が飛ばされるのを防ぎます。\nVehicle Control Protection");
		addCheckOption("武器", WEAPON_P, "武器が配布、没収されるのを防ぎます。\nWeapon Protection");
		addCheckOption("キック", KICK_P, "セッションの中でのみ使用してください。\n Kick Protection");
		addCheckOption("検知", DETECTION_P, "チーターからの攻撃を検知し、表示します。\nDetection");
		addCheckOption("パラダイス", PARADISE_P, "ParadiseSPRXが使用するフリーズを防ぎます。\nDrop & Paradise Protection");
		addCheckOption("RCE", RCE_P, "遠隔チートを防ぎます。\nRCE Protection");
		addCheckOption("オブジェクト 操作 / 削除", OBJECT_P, "車の運転も不可能");
		//addOption("軽量化", "FPSが低下する可能性がある物を削除します。\nObject Remover", "+");
		//addOption("スクリプト & 天候", "フリーズする可能性がある物を防ぎます。\nEnglish Script Protect & Detect", "+");
		//addOption("エンティティ", "個別でエンティティを非表示にします。\nEntity Protection", "+");
		
		switch (getOption())
		{
		case 1: PTFX_P = !PTFX_P;
			if (PTFX_P)
			{
				PS3::WriteInt32(0x12D4FF8, 0x4E800020);
				PS3::WriteInt32(0x12C6950, 0x4E800020);//Lazer
				PS3::WriteInt32(0x12C49A4, 0x4E800020);//Explosion
				PS3::WriteInt32(0x12C5598, 0x4E800020);//Fire
				addMessageShow("~y~*エフェクト*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteInt32(0x12D4FF8, 0x7C0802A6);
				PS3::WriteInt32(0x12C6950, 0x7C0802A6);//Lazer
				PS3::WriteInt32(0x12C49A4, 0x7C0802A6);//Explosion
				PS3::WriteInt32(0x12C5598, 0x7C0802A6);//Fire
				addMessageShow("~y~*エフェクト*~w~を~g~有効化~w~しました。");
			}
			break;
		case 2:TPANIM_P = !TPANIM_P;
			if (TPANIM_P)
			{
				PS3::WriteInt32(0x12CB0F8, 0x4E800020);
				PS3::WriteInt32(0x12CB4BC, 0x4E800020);
				PS3::WriteInt32(0x12CB66C, 0x4E800020);
				PS3::WriteInt32(0x12CB890, 0x4E800020);
				addMessageShow("~y~*強制系*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteInt32(0x12CB0F8, 0x7C0802A6);
				PS3::WriteInt32(0x12CB4BC, 0x7C0802A6);
				PS3::WriteInt32(0x12CB66C, 0x7C0802A6);
				PS3::WriteInt32(0x12CB890, 0x7C0802A6);
				addMessageShow("~y~*エフェクト*~w~を~g~有効化~w~しました。");
			}
			break;
		case 3:CTASK_P = !CTASK_P;
			if (CTASK_P)
			{
				PS3::WriteInt32(0x12CC8B8, 0x4E800020);
				addMessageShow("~y~*クリアタスク*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteInt32(0x12CC8B8, 0x7C0802A6);
				addMessageShow("~y~*クリアタスク*~w~を~g~有効化~w~しました。");
			}
			break;
		case 4:VEHCON_P = !VEHCON_P;
			if (VEHCON_P)
			{
				PS3::WriteInt32(0x12BD2CC, 0x4E800020);
				addMessageShow("~y~*車両ブースト*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteInt32(0x12BD2CC, 0x7C0802A6);
				addMessageShow("~y~*車両ブースト*~w~を~g~有効化~w~しました。");
			}
			break;
		case 5:WEAPON_P = !WEAPON_P;
			if (WEAPON_P)
			{
				PS3::WriteUInt32(0x12C3BD4, 0x4E800020);
				PS3::WriteUInt32(0x12C3A2C, 0x4E800020);
				addMessageShow("~y~*没収、配布*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteUInt32(0x12C3BD4, 0x7C0802A6);
				PS3::WriteUInt32(0x12C3A2C, 0x7C0802A6);
				addMessageShow("~y~*没収、配布*~w~を~g~無効化~w~しました。");
			}
			break;
		case 6:KICK_P = !KICK_P;
			//if (isOnline())
			//{
			if (KICK_P)
			{
				//if (PS3::ReadUInt32(0x1357D44) != 0x60000000) //ON
				//	PS3::WriteUInt32(0x1357D44, 0x60000000);

				//if (PS3::ReadUInt32(0x1370334) != 0x60000000) //ON
				//	PS3::WriteUInt32(0x1370334, 0x60000000);

				//if (PS3::ReadUInt32(0x12D1D88) != 0x4E800020) //ON
				//	PS3::WriteUInt32(0x12D1D88, 0x4E800020);

				//if (PS3::ReadUInt32(0x1358AFC) != 0x4E800020) //ON
				//	PS3::WriteUInt32(0x1358AFC, 0x4E800020);
				addMessageShow("~y~*キック*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteUInt32(0x1357D44, 0x907E0004);
				PS3::WriteUInt32(0x1370334, 0x907E0004);
				PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);
				PS3::WriteUInt32(0x1358AFC, 0x7C0802A6);
				addMessageShow("~y~*キック*~w~を~g~有効化~w~しました。");
			}
			//}
			//else
			//{
			//	addMessageShow("オンラインに入ってから使用してください。");
			//}
			break;
		case 7:DETECTION_P = !DETECTION_P;

			if (DETECTION_P)
			{
				addMessageShow("~y~*検知*~w~を~g~表示~w~します。");
			}
			else
			{
				//48 46 01 0D
				PS3::WriteUInt32(0x12D2160, 0x4846010D);
				PS3::WriteUInt32(0x139B61C, 0x4BFFE3F1);

				PS3::WriteUInt32(0x1C6BD80, 0x12C8CC0);
				PS3::WriteUInt32(0x1C6BD84, 0x01C85330);

				PS3::WriteUInt32(0x1C6BAA8, 0x12C2D8C);
				PS3::WriteUInt32(0x1C6BAAC, 0x01C85330);

				PS3::WriteUInt32(0x1C6BF80, 0x12CB4BC);
				PS3::WriteUInt32(0x1C6BF84, 0x01C85330);

				//PS3::WriteUInt32(0x1C6C5F8, 0x12D2064);
				//PS3::WriteUInt32(0x1C6C5FC, 0x01C85330);

				PS3::WriteUInt32(0x1C6C530, 0x12D12DC);
				PS3::WriteUInt32(0x1C6C534, 0x01C85330);

				PS3::WriteUInt32(0x1C707E0, 0x133C480);
				PS3::WriteUInt32(0x1C707E4, 0x01C85330);
				addMessageShow("~y~*検知*~w~を~r~非表示~w~にしました。");
			}
			break;
		case 8:PARADISE_P = !PARADISE_P;
			if (PARADISE_P)
			{
				//if (PS3::ReadUInt32(0x9FBB58) != 0x4E800020) //ON
				//	PS3::WriteUInt32(0x9FBB58, 0x4E800020);

				//if (PS3::ReadUInt32(0x9FBB5C) != 0x4E800020)
				//	PS3::WriteUInt32(0x9FBB5C, 0x4E800020);

				//if (PS3::ReadUInt32(0x9FB990) != 0x4E800020)
				//	PS3::WriteUInt32(0x9FB990, 0x4E800020);

				//if (PS3::ReadUInt32(0x9FFE90) != NOP) //ON
				//	PS3::WriteUInt32(0x9FFE90, NOP); //Drop Kick

				//if (PS3::ReadUInt32(0x9FFF0C) != 0x6560FDCF) //ON
					//PS3::WriteUInt32(0x9FFF0C, 0x6560FDCF); //Drop Kick

				addMessageShow("~y~*パラダイス*~w~を~r~無効化~w~しました。");
			}
			else
			{
				if (PS3::ReadUInt32(0x9FBB58) != 0x7FE10808) //OFF
					PS3::WriteUInt32(0x9FBB58, 0x7FE10808);

				if (PS3::ReadUInt32(0x9FBB5C) != 0x4BFFFDA8)
					PS3::WriteUInt32(0x9FBB5C, 0x4BFFFDA8);

				if (PS3::ReadUInt32(0x9FB990) != 0x7FE10808)
					PS3::WriteUInt32(0x9FB990, 0x7FE10808);

				if (PS3::ReadUInt32(0x9FFE90) != R_NOP) //ON	
					PS3::WriteUInt32(0x9FFE90, R_NOP); //Drop Kick
				addMessageShow("~y~*パラダイス*~w~を~g~有効化~w~しました。");
			}
			break;

		case 9:RCE_P = !RCE_P;
			if (RCE_P)
			{
				//if (PS3::ReadUInt32(GIVE_PICKUP_REWARDS_EVENT) != NOP) //ON
				//	PS3::WriteUInt32(GIVE_PICKUP_REWARDS_EVENT, NOP);

				addMessageShow("~y~*RCE*~w~を~r~無効化~w~しました。");
			}
			else
			{
				if (PS3::ReadUInt32(GIVE_PICKUP_REWARDS_EVENT) != R_NOP) //ON
					PS3::WriteUInt32(GIVE_PICKUP_REWARDS_EVENT, R_NOP);

				addMessageShow("~y~*RCE*~w~を~g~有効化~w~しました。");
			}
			break;
		case 10:
			OBJECT_P = !OBJECT_P; 

			if (!OBJECT_P)
			{
				PS3::WriteUInt32(0x1C6B918, 0x12BDF2C);
				PS3::WriteUInt32(0x1C6B91C, 0x01C85330);
			}
			break;
			//case 10:changeSubmenu(ProtectionMenu_Object); break;
			//case 11:changeSubmenu(ProtectionMenu_Script); break;
			//case 12:changeSubmenu(ProtectionMenu_Entity); break;
			//case 13:DETECTMENU_P = !DETECTMENU_P;
			//	if (DETECTMENU_P)
			//	{
			//		PS3::WriteUInt32(0x12D4A5C, 0x4E800020);
			//		PS3::WriteUInt32(0x13C57B4, 0x4E800020);
			//		addMessageShow("~y~*他プレイヤーからのチート感知*~w~を~r~無効化~w~しました。");
			//	}
			//	else
			//	{
			//		PS3::WriteUInt32(0x12D4A5C, 0x7C0802A6);
			//		PS3::WriteUInt32(0x13C57B4, 0x7C0802A6);
			//		addMessageShow("~y~*他プレイヤーからのチート感知*~w~を~g~有効化~w~しました。");
			//	}
			//	break;
			//}
		}

		break;
#pragma endregion

#pragma region ProtectionMenu_Object
	case ProtectionMenu_Object:
		addTitle("軽量化");
		addCheckOption("周りのNPCを削除", CLEARAREA_ALL, "周りのNPC車、警察等を見えなくします。\nClear Area");
		addCheckOption("周りの車両を削除", CLEARVEH_ALL, "周りのNPC含む車両を削除します。\nClear Vehicle All");
		addCheckOption("アタッチされた車両を削除", VEHATTACH_P, "自身にアタッチされた車両を削除します。\nVehicle Attach Protection");
		addCheckOption("アタッチされたペッドを削除", PEDATTACH_P, "自身にアタッチされたペッドを削除します。\nPed Attach Protection");
		addCheckChar("読み込むマップを抑制", Low_Tecture, Low_Tecture_String, &Low_TextureVar, 0, 4, "Low Texture");
		addCheckOption("一部マップを消す", MapDelete_, "40Kアパートとか消えます");
		addOption("アタッチされたオブジェクトの削除");
		addOption("自分がスポーンした全てのオブジェクトを削除");
		switch (getOption())
		{
		case 1:CLEARAREA_ALL = !CLEARAREA_ALL;
			if (CLEARAREA_ALL)
				addMessageShow("~y~*周辺の軽量化*~w~を開始します。");
			else
				addMessageShow("~y~*周辺の軽量化*~w~を中止します。");
			break;
		case 2:CLEARVEH_ALL = !CLEARVEH_ALL;
			if (CLEARVEH_ALL)
				addMessageShow("~y~*周辺の軽量化(車)*~w~を開始します。");
			else
				addMessageShow("~y~*周辺の軽量化(車)*~w~を中止します。");
			break;

		case 3:VEHATTACH_P = !VEHATTACH_P; 
			if (VEHATTACH_P)
				addMessageShow("~y~*アタッチされた車両の削除*~w~を開始します。");
			else
				addMessageShow("~y~*アタッチされた車両の削除*~w~を終了します。");
			break;
		case 4: PEDATTACH_P = !PEDATTACH_P;
			if (PEDATTACH_P)
				addMessageShow("~y~*アタッチされたペッドの削除*~w~を開始します。");
			else
				addMessageShow("~y~*アタッチされたペッドの削除*~w~を終了します。");
			break;
		case 5:
			Low_Tecture = !Low_Tecture;
			if (Low_Tecture)
			{
				addMessageShow("読み込むマップを抑制を開始します。");
			}
			else if (Low_TextureWater)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema");
				addMessageShow("鮮明化しました。");
			}
			else
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
				addMessageShow("通常に戻しました。");
			}
			break;
		case 6:MapDelete_ = !MapDelete_; 
			if (MapDelete_)
			{
				addMessageShow("消去しました。");
			}
			else
			{
				addMessageShow("復元しました。");
			}

			break;
		case 7:
			AllObjectRemove();
			break;
		//case 8:AutoClearArea = !AutoClearArea;
		//	if (AutoClearArea)
		//		addMessageShow("軽量化を有効化しました");
		//	else
		//		addMessageShow("軽量化を無効化しました。");
		//	break;
		case 8:
			_AllObjectRemove();
			break;
		}
		break;
#pragma endregion

#pragma region ProtectionMenu_Script
	case ProtectionMenu_Script:
		addTitle("スクリプト & 天候");
		addCheckOption("スクリプト", SCRIPT_P, "ノンホスキック、強制チュートリアル等を防ぎます\nScript Protection");
		addCheckOption("ステータス変更", STATUS_P, "チーターからのステータス変更を防ぎます。\nChange Stats Protection");
		addCheckOption("天候変更", WEATHER_P, "チーターからの天候変更を防ぎます。\nWeather Protection");
		switch (getOption())
		{
		case 1: SCRIPT_P = !SCRIPT_P; 
			if (!SCRIPT_P)
			{
				PS3::WriteUInt32(0x12CBD94, 0x7C0802A6);
				PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);
				PS3::WriteUInt32(0x172D78C, 0x40820068);
				PS3::WriteUInt32(0x1358F9C, 0x38600001);
				PS3::WriteUInt32(0x1358F08, 0x907E0004);
				addMessageShow("~y~*スクリプト*~w~を~g~有効化~w~しました。");
			}
			else
			{

				addMessageShow("~y~*スクリプト*~w~を~r~無効化~w~しました。");
			}
			break;
			
		case 2:STATUS_P = !STATUS_P; 
			if (STATUS_P)
			{
				PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, 0x4E800020);
				addMessageShow("~y~*ステータス変更*~w~を~r~無効化~w~しました。");
			}
			else
			{
				PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, 0x7C0802A6);
				addMessageShow("~y~*ステータス変更*~w~を~g~有効化~w~しました。");
			}
			break;

		case 3:
				WEATHER_P = !WEATHER_P;
				if (WEATHER_P)
				{
					//PS3::WriteUInt32(GAME_CLOCK_EVENT, 0x4E800020);
					//PS3::WriteUInt32(GAME_WEATHER_EVENT, 0x4E800020);
					addMessageShow("~y~*天候変更*~w~を~r~無効化~w~しました。");
				}
				else
				{
					PS3::WriteUInt32(GAME_CLOCK_EVENT, 0x7C0802A6);
					PS3::WriteUInt32(GAME_WEATHER_EVENT, 0x7C0802A6);
					addMessageShow("~y~*天候変更*~w~を~g~有効化~w~しました。");
				}
			break;

		}
		break;
#pragma endregion

#pragma region ProtectionMenu_Entity
	case ProtectionMenu_Entity:
		addTitle("エンティティ");
		addCheckOption("エンティティ", (PS3::ReadUInt32(0x1093188) == 0x60000000), "他プレイヤーが出すエンティティを非表示します。\nBlock All Entities");
		addCheckOption("ピックアップ", (PS3::ReadUInt32(0x133CB64) == 0x48000044), "他プレイヤーが出すピックアップ(お金、パラシュート、弾薬)等を非表示にします。\nBlock Pickup");
		addCheckOption("戦闘機", (PS3::ReadUInt32(0x133CE5C) == 0x48000044), "他プレイヤーが出す戦闘機を非表示にします。\nBlock Plane");
		addCheckOption("ヘリコプター", (PS3::ReadUInt32(0x133CD84) == 0x48000044), "他プレイヤーが出すヘリコプターを非表示にします。\nBlock Helicopter");
		addCheckOption("オブジェクト", (PS3::ReadUInt32(0x133CAF4) == 0x48000044), "他プレイヤーが出すオブジェクトを非表示にします。\nBlock Object");
		addCheckOption("バイク", (PS3::ReadUInt32(0x133CC40) == 0x48000044), "他プレイヤーが出すバイクを非表示にします。\nBlock Bike");
		addCheckOption("車両", (PS3::ReadUInt32(0x133CA84) == 0x48000044), "他プレイヤーが出す車両を非表示にします。\nBlock Vehicle");
		addCheckOption("ボート", (PS3::ReadUInt32(0x133CDF0) == 0x48000044), "他プレイヤーが出すボートを非表示にします。\nBlock Boat");
		addCheckOption("トレーラー", (PS3::ReadUInt32(0x133CCAC) == 0x48000044), "他プレイヤーが出すトレーラーを非表示にします。\nBlock Traler");
		addCheckOption("クローン", (PS3::ReadUInt32(0x133CA44) == 0x48000018), "他プレイヤーが出すクローンを非表示にします。\nBlock Clone");
		addCheckOption("不明",
			((PS3::ReadUInt32(0x133CBD4) == 0x48000044) &&
			(PS3::ReadUInt32(0x133CD18) == 0x48000044) &&
			(PS3::ReadUInt32(0x133CEC8) == 0x48000044) &&
			(PS3::ReadUInt32(0x133CF38) == 0x48000044)), "不明です。 なにかを非表示化?\nUnknown"
			);
		switch (getOption())
		{
		case 1:
			if (PS3::ReadUInt32(0x1093188) != 0x60000000) //ON
			{
				PS3::WriteUInt32(0x1093188, 0x60000000);
				addMessageShow("~y~*エンティティ*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x1093188, 0x4BA52615);
				addMessageShow("~y~*エンティティ*~w~を~g~表示~w~します。");
			}
			break;

		case 2:
			if (PS3::ReadUInt32(0x133CB64) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CB64, 0x48000044);
				addMessageShow("~y~*ピックアップ*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CB64, 0x8BD70029);
				addMessageShow("~y~*ピックアップ*~w~を~g~表示~w~します。");
			}
				break;

		case 3:
			if (PS3::ReadUInt32(0x133CE5C) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CE5C, 0x48000044);
				addMessageShow("~y~*戦闘機*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CE5C, 0x8BD70029);
				addMessageShow("~y~*戦闘機*~w~を~g~表示~w~します。");
			}
				break;
			
		case 4:
			if (PS3::ReadUInt32(0x133CD84) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CD84, 0x48000044);
				addMessageShow("~y~*ヘリコプター*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CD84, 0x8BD70029);
				addMessageShow("~y~*ヘリコプター*~w~を~g~表示~w~します。");
			}
				break;
			
		case 5:
			if (PS3::ReadUInt32(0x133CAF4) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CAF4, 0x48000044);
				addMessageShow("~y~*オブジェクト*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CAF4, 0x8BD70029);
				addMessageShow("~y~*オブジェクト*~w~を~g~表示~w~します。");
			}
				break;

		case 6:
			if (PS3::ReadUInt32(0x133CC40) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CC40, 0x48000044);

				addMessageShow("~y~*バイク*~w~を~r~非表示~w~にしました。");
			}
			else {
				PS3::WriteUInt32(0x133CC40, 0x8BD70029);
				addMessageShow("~y~*バイク*~w~を~g~表示~w~します。");
			}
				break;

		case 7:
			if (PS3::ReadUInt32(0x133CA84) != 0x48000044)
			{

				PS3::WriteUInt32(0x133CA84, 0x48000044);
				addMessageShow("~y~*車両*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CA84, 0x8BD70029);
				addMessageShow("~y~*車両*~w~を~g~表示~w~します。");
			}
				break;

		case 8:
			if (PS3::ReadUInt32(0x133CDF0) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CDF0, 0x48000044);
				addMessageShow("~y~*ボート*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CDF0, 0x8BD70029);
				addMessageShow("~y~*ボート*~w~を~g~表示~w~します。");
			}
			break;
		case 9:
			if (PS3::ReadUInt32(0x133CCAC) != 0x48000044)
			{
				PS3::WriteUInt32(0x133CCAC, 0x48000044);
				addMessageShow("~y~*トレーラー*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CCAC, 0x8BD70029);
				addMessageShow("~y~*トレーラー*~w~を~g~表示~w~します。");
			}
				break;

		case 10:
			if (PS3::ReadUInt32(0x133CA44) != 0x48000018)
			{
				PS3::WriteUInt32(0x133CA44, 0x48000018);
				addMessageShow("~y~*クローン*~w~を~r~非表示~w~にしました。");
			}
			else {
				PS3::WriteUInt32(0x133CA44, 0x60000000);
				addMessageShow("~y~*クローン*~w~を~g~表示~w~します。");
			}
				break;

		case 11:
			if (((PS3::ReadUInt32(0x133CBD4) != 0x48000044) ||
				(PS3::ReadUInt32(0x133CD18) != 0x48000044) || 
				(PS3::ReadUInt32(0x133CEC8) != 0x48000044) || 
				(PS3::ReadUInt32(0x133CF38) != 0x48000044)))
			{
				PS3::WriteUInt32(0x133CBD4, 0x48000044);
				PS3::WriteUInt32(0x133CD18, 0x48000044);
				PS3::WriteUInt32(0x133CEC8, 0x48000044);
				PS3::WriteUInt32(0x133CF38, 0x48000044);
				addMessageShow("~y~*???*~w~を~r~非表示~w~にしました。");
			}
			else
			{
				PS3::WriteUInt32(0x133CBD4, 0x8BD70029);
				PS3::WriteUInt32(0x133CD18, 0x8BD70029);
				PS3::WriteUInt32(0x133CEC8, 0x8BD70029);
				PS3::WriteUInt32(0x133CF38, 0x8BD70029);
				addMessageShow("~y~*???*~w~を~g~表示~w~します。");
			}
			break;
		}

		break;
#pragma endregion

#pragma region RecoveryMenu
	case RecoveryMenu:
		addTitle("リカバリー");
		addCharSwap("キャラクター", CharacterSwap, &CharacterVar_, 0, 1, "使用中のキャラを選択してください。\nCharacter");
		addOption("VC Mute BAN 解除", "チーターによってミュートにされたアカウントを修正します。\nMute BAN Exploit");
		addCheckOption("アカウント無効 解除 Loop", EnableAccountBool, "オンラインに参加した後オフラインに戻ってください");

		addOption("フルハック (キャラクター 1)", "一回押すだけでいいです");
		addOption("フルハック (キャラクター 2)", "そのキャラクターを使用中に押してください。");
		addOption("フルハックのヘルプを表示", "説明がログに出ます");
		addCheckOption("10000000$追加 Loop", _1000KLoop, "");
		addIntOption("ランク変更", &RankVar, 0, 8000, 1, "センションに入る際に反映します。\Rank Present");
		switch (getOption())
		{
		case 2:NinetyPer(); break;
		case 3:EnableAccountBool = !EnableAccountBool;
			if (EnableAccountBool)
			{
				addMessageShow("[アカウント無効 解除]Step 1.アカウント無効 解除をオンのままにする");
				addMessageShow("[アカウント無効 解除]Step 2.オンラインに参加する");
				addMessageShow("[アカウント無効 解除]Step 3.セッションに入る");
				addMessageShow("[アカウント無効 解除]Step 4.オフラインに戻る");
			}
			break;
		case 4:
			if ((getProperty(PLAYER::PLAYER_ID(), 0xEB) != 0x00) && (getProperty(PLAYER::PLAYER_ID(), 0xEC) != 0x00) && (getProperty(PLAYER::PLAYER_ID(), 0xED) != 0x00))
			{
				
				_FullHack_time = -1;
				FullHack = true;
			}
			else
				addMessageShow("ガレージを3つ購入してから実行してください。");
			break;
		case 5:
			CharacterVar_ = 0;
			addMessageShow("[フルハック]Step.1 ガレージへ入る");
			addMessageShow("[フルハック]Step.2 ガレージ奥の青い円で全ての車をシャッフルする");
			addMessageShow("[フルハック]Step.3 Step.2を3つのガレージで行う");
			addMessageShow("[フルハック]Step.4 セッションを変更する(ランクが変更される)");
			addMessageShow("[フルハック]Step.5 オフラインへ行く (完了)");
			MsgTimer = GAMEPLAY::GET_GAME_TIMER() + 8000;
			break;
		case 6:
			CharacterVar_ = 1;
			addMessageShow("[フルハック]Step.1 ガレージへ入る");
			addMessageShow("[フルハック]Step.2 ガレージ奥の青い円で全ての車をシャッフルする");
			addMessageShow("[フルハック]Step.3 Step.2を3つのガレージで行う");
			addMessageShow("[フルハック]Step.4 セッションを変更する(ランクが変更される)");
			addMessageShow("[フルハック]Step.5 オフラインへ行く (完了)");
			MsgTimer = GAMEPLAY::GET_GAME_TIMER() + 8000;
			break;
		case 7:
			_1000KLoop = !_1000KLoop; 
			break;
		case 8:

			STAT_SET_INT("SET_RP_GIFT_ADMIN", Ranks[RankVar], 1);
			STAT_SET_INT("CHAR_SET_RP_GIFT_ADMIN", Ranks[RankVar], 1);
			STAT_SET_INT("MPPLY_IS_HIGH_EARNER", 0, 0);
			break;
		}
		break;
#pragma endregion

#pragma region MiscMenu
	case MiscMenu:// レーダー透明 0xFC 0xF5真っ黒
		addTitle("その他");
		addOption("オススメチート + 保護 ON");
		addOption("オススメチート + 保護 OFF");
		addCheckOption("FPS", View_FPS, "平均FPSを表示します。\nView FPS");
		addCheckOption("セッションの情報", View_Session, "セッションホスト、人数を表示します。\nServer Information");
		addCheckOption("消灯", BlackOut, "街の明かりが全て消えます。\nBlackOut");
		addCharSwap("レーダーの色", raderjapanese, &RaderIndex, 0, 9, "レーダーの色を変更します。\nRader Color");
		addCheckOption("水中鮮明化", Low_TextureWater, "水中がきれいに見えます。");
		addCheckOption("海水無効化", DeleteWaterC, "海岸近くの海水が消えます。\nDelete Water");
		addCheckOption("海水半透明化", OpacityWater, "海が半透明になります。\nWater Opaciy Editor");
		addCheckOption("オフラインマップ読み込み", _LoadIPL, "オフラインで使用したマップを読み込みます。");
		addCheckFloat("VC表示", VCTalker, &VCTalkerX, 0, 1.0, 0.025f, "マイクつけてるだけの人もでます");
		addCheckFloat("チーター感知", HackerView, &VCTalkerX, 0, 1.0, 0.025f, "SPRX入れてる人だけ");
		addCharSwap("天候", CHANGEMenu, &WeatherVar, 0, 12, "自分目線の天候を変更します。\nWeather Changer");
		addCharSwap("時間", ChangeTime, &TimerVar, 0, 23, "自分目線の時間を変更します。\nTime Changer");
		addCheckFloat("カメラを遠ざける", CameraFar, &ZoomVar,0, 400,3,"遠くから眺めるカメラになります。");
		addCheckOption("パラシュートを永久的に削除", DeleteParachute, "再度起動するまで");
		addCheckOption("雷を発生させる", LightningLoop, "ONにして数秒後発生します。");
		addCheckOption("朝・晴天 固定", TimeStopper, "");
		addCheckOption("VCをフレ限でも聞こえるようにする", ChatBypass, "");
		
		switch (getOption())
		{
		case 1:
			SelfOptionAutoON();
			break;
		case 2:
			SelfOptionAutoOff();
			break;
		case 3: View_FPS = !View_FPS;
			if (View_FPS)
				addMessageShow("~y~FPS~w~を表示します。");
			else
				addMessageShow("~y~FPS~w~を非表示にします。");
			break;
		case 4: View_Session = !View_Session;
			if (View_Session)
				addMessageShow("~y~*セッションの情報*~w~を~g~表示~w~します。");
			else
				addMessageShow("~y~*セッションの情報*~w~を~r~非表示~w~にします。");
			break;

		case 5:
			BlackOut = !BlackOut; 
			GRAPHICS::_SET_BLACKOUT(BlackOut);
			if (BlackOut)
				addMessageShow("消灯しました。");
			else
				addMessageShow("明かりをつけました。");
			break;

		case 6:PS3::WriteByte(0x01D6B357, radercolor1[RaderIndex]);
			addMessageShow("レーダーの色を変更しました。");
			break;

		case 7:Low_TextureWater = !Low_TextureWater; 
			if (Low_TextureWater)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema");
				addMessageShow("鮮明化しました。");
			}
			else if (Low_Tecture)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER(Low_Tecture_String[Low_TextureVar]);
				addMessageShow("読み込むマップを抑制しました。");
			}
			else
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
				addMessageShow("通常に戻しました。");
			}
			break;

		case 8:
			DeleteWaterC = !DeleteWaterC;
			DeleteWaterChecker();
			if (DeleteWaterC)
			{
				for (unsigned int i = 0; i < 0x5994; i++)
					*(char*)(*(unsigned int*)0x21C8C48 + i) = 0;
				addMessageShow("海水を削除しました。");
			}
			else
			{
				for (int i = 0; i < 0x5994; i++)
					*(char*)(*(int*)0x21C8C48 + i) = bytesForResetWater[i];

				addMessageShow("海水を復元しました。");
			}
			break;
		case 9:
			OpacityWater = !OpacityWater; 
			WaterOpacityEdit(OpacityWater ? 0x02020202 : 0x15151515);

			if (OpacityWater)
				addMessageShow("海水を半透明化しました。");
			else
				addMessageShow("海水の透明度を元に戻しました。");
			break;

		case 10:_LoadIPL = !_LoadIPL;
			LoadIPL(_LoadIPL);
			break;
		case 11:VCTalker = !VCTalker; break;
		case 12:HackerView = !HackerView; break;
		case 13:
			GAMEPLAY::SET_OVERRIDE_WEATHER(CHANGEhsh[WeatherVar]);
			GAMEPLAY::SET_WEATHER_TYPE_NOW(CHANGEhsh[WeatherVar]);

			break;
		case 14:
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TimerVar, 0, 0);
			TIME::SET_CLOCK_TIME(TimerVar, 0, 0);
			break;
		case 15:
			CameraFar = !CameraFar;
			//if (!CameraFar)
			//{
			//	CAM::RENDER_SCRIPT_CAMS(false, 1, 10, 1, 0);
			//	CAM::SET_CAM_ACTIVE(FarCamera, false);
			//	CAM::DESTROY_CAM1(FarCamera, false);
			//	FarCamera = 0;
			//}
			//else
			//{
			//	//CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(300.0f, 1000.0f);
			//}
			break;
		case 16:DeleteParachute = !DeleteParachute; break;
		case 17:LightningLoop = !LightningLoop; break;
		case 18:TimeStopper = !TimeStopper; 
			if (TimeStopper)
			{
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(7, 0, 0);
				TIME::SET_CLOCK_TIME(7, 0, 0);
				TIME::PAUSE_CLOCK(true);
			}
			else
			{
				TIME::PAUSE_CLOCK(false);
			}
			break;
		case 19:
			ChatBypass = !ChatBypass;
			break;

		//case 19:
		//	ChangeUIColor = !ChangeUIColor; 
		//	

		//	break;
		//case 20:
		//	//char message[50];
		//	UI::_SET_HUD_COLOR(UIIndex, 0, 0, 0, 255);
		//	addMessageShow("[UI]変更しました!");
		//	addMessageShow(UILabel[UIIndex]);
		//	break;
		}
		break;
#pragma endregion

#pragma region Settingsss
	case Settings:
		addTitle("メニューの設定");  // 0
		addCheckOption("プレイヤー UI", _PlayerUI, "プレイヤーUIのON / OFF切り替え\nPlayer Information"); // 1
		addCheckOption("ESPに名前を追加する", NAME_ESP, "名前、相手との距離を表示\nNameESP"); // 2
		addCheckChar("ESPのカラー固定", COLORED_ESP, COLOR_ESP, &COLORED_ESP_VAR, 0, 5, "ESPの色を固定します\nColored ESP"); // 3
		addCheckOption("HDD用テレポート", isHDD, "テレポートする際に軽量化します。\nIs your ps3 hdd"); // 4
		addCharSwap("スクロール速度", ScrollSpeedVar, &ScrollSpeedModifier, 0, 2, "長押しした際のスクロール速度を変更します。\nScroll Speed"); // 5
	
		addCheckOption("ログを表示しない", DontViewLog, "左の下のログがでなくなります"); // 6
		addCheckOption("タイトルの色変更", TitleGCMODE, "テスト1");
		addCheckOption("Open Menuを表示しない", DontViewOpenMenu, "右のが出なくなります");
		addCheckOption("オブジェクトをPropIDで表示する", ViewPropName, "オブジェクトスポーンの名前です");
		addCheckOption("IPを表示", _playeruiIPADDRESS, "PlayerUIに入ります");
		addCheckOption("Zedd & Dx Chat", _chat, "メニュー購入者同士でチャット出来ます。");
		if (_AdminFlag)
		{
			addCheckOption("メニュー表示削除", DeleteMenuID, "見えなくなります");
		}
		if (currentOption == 5  && (rightPress || leftPress || fastLeftPress || fastRightPress))
			ScrollTimer = ScrollSpeed[ScrollSpeedModifier];
		
		switch (getOption())
		{
		case 1: _PlayerUI = !_PlayerUI; break;
		case 2: NAME_ESP = !NAME_ESP; break;
		case 3:COLORED_ESP = !COLORED_ESP; break;
		case 4: isHDD = !isHDD; break;
		case 6:DontViewLog = !DontViewLog; break;
		case 7:
			TitleGCMODE = !TitleGCMODE;
			if (TitleGCMODE)
			{
				bannerRect.R = 0xFF;
				bannerRect.G = 0x14;
				bannerRect.B = 0x93;
				bannerRect.A = 120;
				bannerRect1.R = 0xFF;
				bannerRect1.G = 0xC0;
				bannerRect1.B = 0xCB;
				bannerRect1.A = 120;
			}
			else
			{
				bannerRect.R = 50;
				bannerRect.G = 100;
				bannerRect.B = 255;
				bannerRect.A = 120;
				bannerRect1.R = 255;
				bannerRect1.G = 0;
				bannerRect1.B = 255;
				bannerRect1.A = 120;
			}

			break;
		case 8:DontViewOpenMenu = !DontViewOpenMenu; break;
		case 9:ViewPropName = !ViewPropName; break;
			if (_AdminFlag)
			{
		case 10:
			_playeruiIPADDRESS = !_playeruiIPADDRESS;
			break;
		case 11:
			_chat = !_chat; 
			break;
		case 12:
			DeleteMenuID = !DeleteMenuID; 
			break;
			}
		}
		break;
#pragma endregion
	}

	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		if (submenu == Main_Menu)
		{
			if (!isPress(Button_L2))
			{
				ButtonDisable(Button_B);
				ButtonDisable(Button_A);
			}
			addInstruction(BUTTON_B, "選択");
			addInstruction(BUTTON_A, "閉じる");
		}
		else if (submenu != Closed)
		{
			if (!isPress(Button_L2))
			{
				ButtonDisable(Button_B);
				ButtonDisable(Button_A);
			}
			addInstruction(BUTTON_B, "選択");
			addInstruction(BUTTON_A, "戻る");

			if (submenu == PlayerList)
			{
				ButtonDisable(Button_R1);
				ButtonDisable(Button_L1);
				addInstruction(BUTTON_RB, "相手へテレポート");
				addInstruction(BUTTON_LB, "自分へテレポート");
			}
		}
		else 
		if (squareInstruction)
			addInstruction(BUTTON_X, "キーボード入力");
		if (udInstruction)
			addInstruction(BUTTON_DPAD_UP_DOWN, "移動");
		if (lrInstruction)
			addInstruction(BUTTON_DPAD_LEFT_RIGHT, "移動");
		if (fastInstruction)
		{
			ButtonDisable(Button_L1);
			addInstruction(BUTTON_LB, "早く動かす");
		}

		/*ボタン表示*/
		if (VehicleJetpack)
		{
			if (Hover_ON)
			{
				addInstruction(BUTTON_RT, "進む");
				addInstruction(BUTTON_LT, "戻る");
				addInstruction(BUTTON_X, "止まる");
				addInstruction(BUTTON_LSTICK_UP_DOWN, "上昇と下降");
				if (!VehJetpack_ON)
				{
					addInstruction(BUTTON_LSTICK_ROTATE, "回る");
					addInstruction(BUTTON_RSTICK, "ブーストモード起動");
				}
				else
				{
					addInstruction(BUTTON_LSTICK_ROTATE, "回る");
					addInstruction(BUTTON_RSTICK_ROTATE, "進む方向");
				}
			}
			else
			{
				addInstruction(BUTTON_LSTICK, "ホバーモード起動");
			}
		}

		if (DriveOnWall)
		{
			addInstruction(BUTTON_RB, "壁の近くでジャンプ");
			addInstruction(BUTTON_X, "ストップ！");
		}

		if (breathfire)
		{
			addInstruction(BUTTON_X, "火を吐く");
		}

		if (MinecraftMode)
		{
			addInstruction(BUTTON_LT, "置く場所表示");
			if (isPress(Button_L2))
			{
				addInstruction(BUTTON_RB, "置く");
			}
		}

		if (UltraRun)
		{
			addInstruction(BUTTON_B, "早く走る");
		}

		if (Noclip[0])
		{
			addInstruction(BUTTON_LSTICK_UP, "移動");
		}

		if (DriftL1)
		{
			addInstruction(BUTTON_RB, "ドリフト");
		}

		if (DpadLeftCarFix)
		{
			addInstruction(BUTTON_DPAD_RIGHT, "車修復");
		}

		if (L3Boost_R3Stop)
		{
			addInstruction(BUTTON_LSTICK, "ブースト");
			addInstruction(BUTTON_RSTICK, "ストップ");
		}

		if (R1Jumping)
		{
			addInstruction(BUTTON_RB, "ジャンプ");
		}

		if (ParachuteMod)
		{
			addInstruction(BUTTON_LSTICK, "ジャンプ");
			//addInstruction(BUTTON_DPAD_RIGHT, "近くの車へテレポート");
			addInstruction(BUTTON_DPAD_UP, "スピード上昇");
			addInstruction(BUTTON_DPAD_DOWN, "スピードダウン");
		}

		if (instructions)
		{
			instructionsClose();
		}
	}

	resetVars();
}

int sleep(int msec)
{
	return sys_timer_usleep(msec * 1000);
}
uint64_t swl2[10];
int RequestID = 0;

#pragma region Bufs

#pragma endregion
//static CcxCall CCAPIEnableSysCall(uint64_t num);

char* getMacAddress()
{
	CellNetCtlInfo netInfo1;
	cellNetCtlGetInfo(CELL_NET_CTL_INFO_ETHER_ADDR, &netInfo1);
	const char * Mac = (const char *)netInfo1.ether_addr.data;
	char MacAddress3[30];
	sprintf(MacAddress3, "%02X%02X%02X%02X%02X%02X", Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF);
	return MacAddress3;
}
bool LisenceBool;
char lisencepath[50];
char* getLisence()
{
	int fd;
	char bufs[30];
	bool IsLisenceTMP = cellFsOpen(lisencepath, CELL_FS_O_RDONLY, &fd, NULL, 0) == CELL_FS_OK;
	if (IsLisenceTMP)
	{
		cellFsRead(fd, bufs, 30, &swl2[0]);
		cellFsClose(fd);

		if (strlen(bufs) != 30)
			return "Error_B";

		LisenceBool = true;
		return bufs;
	}
	return "Error_A";
}

#define NOT_CONNECTED "0xFFFFFFFF"
#define NORMAL_LISENCE "0xB8001000"
#define ADMIN_LISENCE "0xB8003000"
#define BANNED_LISENCE "0xF8000000"
#define CANTLOGIN "0xF8000003"
#define USEDLISENCE "0xF8000002"
#define NULLORINVALID "0xF8000001"
#define ON_UPDATE "0xC0000001"
#define OFF_UPDATE "0xC0000000"
#define DIRECTERROR "0xC000000F"

char devhdd0_tmp[50];

char MacAddress300[30];
char LisenceBuf[30];

uint64_t IDPS[2] = { 0, 0 };
int g_tSysTime;
int g_ulKeyValue;
void Thread_2(uint64_t a)
{
	sleep(10000);
	cellFsMkdir("/dev_hdd0/tmp/Re_HyperDx", 0);
	SetLabelText("PM_NAME_CHALL", "文字を入力してください。");
	SetLabelText("LOADING_SPLAYER_L", "Re:Hyper Dxをロード中");
	SetLabelText("HUD_LBD_FMC", "Re:Hyper Dx (クルー ~1~人)");
	SetLabelText("HUD_LBD_FMF", "Re:Hyper Dx (フレンド ~1~人)");
	SetLabelText("HUD_LBD_FMI", "Re:Hyper Dx (招待 ~1~人)");
	SetLabelText("HUD_LBD_FMP", "Re:Hyper Dx (公開 ~1~人)");
	SetLabelText("HUD_LBD_FMS", "Re:Hyper Dx (ソロ ~1~人)");
	char GET_INIFILE[40];
	strcpy(GET_INIFILE, LoadText(redirect_redxphpque_cmd_get_inifile, 33));
	DownloadFile_Ini(redxserver, GET_INIFILE, "/dev_hdd0/tmp/Auto_Setting.txt");
	printf("Inifile Downloaded\n");
	AutoOn::Load_String();
	printf("String Loaded\n");
	printf("Thread Ended *2\n");
	BypassAddress();
	PS3::WriteInt32(0x10050200, 0x94994114); PS3::WriteInt32(0x10060200, 0x57115570); PS3::WriteInt32(0x10060208, 0xFFFFFF14);
	char *p5 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=5");
	memcpy((void*)0x10050400, p5, 100);
	sleep(1000);
	char *p4 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=4");
	memcpy((void*)0x10050520, p4, 100);
	sleep(1000);
	char *p3 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=3");
	memcpy((void*)0x10050640, p3, 100);
	sleep(1000);
	char *p2 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=2");
	memcpy((void*)0x10050760, p2, 100);
	sleep(1000);
	char *p1 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=1");
	memcpy((void*)0x10050860, p1, 100);
	sleep(1000);

	printf("Started Load XML\n");
	//do_ReadXML("/dev_hdd0/tmp/Objects.resource");
	//ReadObjects();

	sleep(100);
	printf("thread ended *2\n");
	sys_ppu_thread_exit(a);
}

void Engine_Thread(uint64_t a)
{
	g_tSysTime = sys_time_get_system_time();
	g_ulKeyValue = (unsigned long)(g_tSysTime & 0xFFFF);
	*(unsigned long long*)0x1CCB160 = (unsigned long long)(g_ulKeyValue);
	*(unsigned int*)0xD25E4C = 0x3C600000 | ((unsigned long)(&g_ulKeyValue) >> 16 & 0xFFFF);
	*(unsigned int*)0xD25E54 = 0x80630000 | ((unsigned long)(&g_ulKeyValue) & 0xFFFF);
	//sleep(3000);

#pragma region Native Search
	TOC = (*(OPD_s**)0x1001C)->toc;
	NativeTable = GetNativeTable();
	while (*(uint32_t*)NativeTable == 0) sleep(1000);
	is_player_online_OPD_s.sub = GetBls(GetNative(0x9FAB6729))[1];
	is_player_online_OPD_s.toc = TOC;
	HookNative(GetNative(0x9FAB6729), Hooking::MainTheread);

	does_entity_exist_OPD_s.sub = GetBls(GetNative(0x3AC90869))[1];
	does_entity_exist_OPD_s.toc = TOC;
	HookNative(GetNative(0x3AC90869), Hooking::does_entity_exist);

	//GET_MAX_WANTED_LEVEL_t.sub = GetBls(GetNative(0x457F1E44))[1];
	//GET_MAX_WANTED_LEVEL_t.toc = TOC;
	//HookNative(GetNative(0x3AC90869), Hooking::does_entity_exist);

	GET_GAMEPLAY_CAM_ROT_OPD_s.sub = GetBls(GetNative(0x13A010B5))[1];
	GET_GAMEPLAY_CAM_ROT_OPD_s.toc = TOC;

	get_entity_coords_OPD_s.sub = GetBls(GetNative(0x1647F1CB))[1];
	get_entity_coords_OPD_s.toc = TOC;

	GET_PED_BONE_COORDS_OPD_s.sub = GetBls(GetNative(0x4579CAB1))[1];
	GET_PED_BONE_COORDS_OPD_s.toc = TOC;
	get_entity_rotation_OPD_s.sub = GetBls(GetNative(0x8FF45B04))[1];
	get_entity_rotation_OPD_s.toc = TOC;
	GET_GAMEPLAY_CAM_ROT_OPD_s.sub = GetBls(GetNative(0x13A010B5))[1];
	GET_GAMEPLAY_CAM_ROT_OPD_s.toc = TOC;
	GET_GAMEPLAY_CAM_COORD_OPD_s.sub = GetBls(GetNative(0x9388CF79))[1];
	GET_GAMEPLAY_CAM_COORD_OPD_s.toc = TOC;

	GET_ENTITY_FORWARD_VECTOR_OPD_s.sub = GetBls(GetNative(0x84DCECBF))[1];
	GET_ENTITY_FORWARD_VECTOR_OPD_s.toc = TOC;
	GET_BLIP_COORDS_t.sub = GetBls(GetNative(0xEF6FF47B))[1];
	GET_BLIP_COORDS_t.toc = TOC;
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_OPD_s.sub = 0x3AC394;
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_OPD_s.toc = TOC;
	ATTACH_CAM_TO_ENTITY_t.toc = TOC;
	get_offset_from_entity_in_world_coords_t.toc = TOC;
	shoot_single_bullet_between_coords_t.sub = GetBls(GetNative(0xCB7415AC))[1];
	shoot_single_bullet_between_coords_t.toc = TOC;
	GET_ENTITY_SPEED_VECTOR_OPD_s.sub = GetBls(GetNative(0x3ED2B997))[1];
	GET_ENTITY_SPEED_VECTOR_OPD_s.toc = TOC;
	IS_PS3_VERSION_OPD_s.sub = GetBls(GetNative(0x4C0D5303))[1];
	IS_PS3_VERSION_OPD_s.toc = TOC;
	IS_PC_VERSION_OPD_s.sub = GetBls(GetNative(0x4D5D9EE3))[1];
	IS_PC_VERSION_OPD_s.toc = TOC;
	get_ped_last_weapon_impact_coord_t.toc = TOC;
	SuperRun_t.sub = GetBls(GetNative(0x825423C2))[1];
	SuperRun_t.toc = TOC;
	IS_BIT_SET_OPD_s.sub = GetBls(GetNative(0x902E26AC))[1];
	IS_BIT_SET_OPD_s.toc = TOC;
	GET_CAM_COORD_OPD_s.sub = GetBls(GetNative(0x7C40F09C))[1];
	GET_CAM_COORD_OPD_s.toc = TOC;
	GET_CAM_ROT_OPD_s.sub = GetBls(GetNative(0xDAC84C9F))[1];
	GET_CAM_ROT_OPD_s.toc = TOC;
	GET_PED_BONE_COORDS_s.sub = GetBls(GetNative(0x4579CAB1))[1];
	GET_PED_BONE_COORDS_s.toc = TOC;
	GET_GROUND_Z_FOR_3D_COORD_t.toc = TOC;
	IS_ENTITY_IN_WATER_t.toc = TOC;
	HAS_ENTITY_COLLIDED_WITH_ANYTHING_t.toc = TOC;
	HAS_ACHIEVEMENT_BEEN_PASSED_s.sub = GetBls(GetNative(0x136A5BE9))[1];
	HAS_ACHIEVEMENT_BEEN_PASSED_s.toc = TOC;
	GIVE_ACHIEVEMENT_TO_PLAYER_s.sub = GetBls(GetNative(0x822BC992))[1];
	GIVE_ACHIEVEMENT_TO_PLAYER_s.toc = TOC;
#pragma endregion

#pragma region Lisence

	strcpy(MacAddress300, getMacAddress()); //MAC取得
	strcpy(LisenceBuf, getLisence());

	//memcpy((void*)0x10053FD0, getMacAddress(), 30);

	Dialog::ShowText("サーバー接続中....");
	Dialog::SetProgressText("接続が有効であるか確認しています。");

	/*aaa*/

	bool ConnectError;
	bool D_FREEZE;
	char SendBuf[200];

	bool AdminFlag;

	sleep(1000);

	//char redxserver[50];
	
	
	memcpy(redxserver, LoadText(redxserver_php_xdomain, 25), 50);// redxserver.php.xdomain.jp
	//memcpy((void*)0x1005EC0, LoadText(redxserver_php_xdomain, 25), 50);// redxserver.php.xdomain.jp
															 //char redirect_redx[50]; // "Redirect_REDX.php"
	char redirect_redx[50];	
	strcpy(redirect_redx, LoadText(redirect_redx_php, 17));

	char redirect_version[50]; // "Redirect_REDX.php?VER="
	strcpy(redirect_version, redirect_redx);
	strcat(redirect_version, LoadText(q_ver_equal, 5));

	char redirect_sprxdownload[50]; // "Redirect_REDX.php?DIR=SPRX_DOWNLOAD"
	strcpy(redirect_sprxdownload, redirect_redx);
	strcat(redirect_sprxdownload, LoadText(q_dir_equal_sprx_download, 18));

	char re_hyper_dx_sprx[50]; // /dev_hdd0/tmp/Re_HyperDx.sprx
	strcpy(re_hyper_dx_sprx, devhdd0_tmp);
	strcat(re_hyper_dx_sprx, LoadText(re_hyper_dx_sprx_a, 15));

	char q_lisence_eq[50];  // ?Lisence=
	strcpy(q_lisence_eq, LoadText(q_lisence_eq_, 9));

	char a_mac_eq[50];  // &MAC=
	strcpy(a_mac_eq, LoadText(a_mac_eq_, 5));

	//printf(GET_INIFILE);
	//printf("\n");

	char InifileBuf[50];
	strcpy(InifileBuf, LoadText(tmp_rehyperdx_inifile, 41));
	/*	printf(InifileBuf);
	printf("\n");*/

	char InifileDir[30];
	strcpy(InifileDir, LoadText(tmp_rehyperdx, 24));


	//printf(InifileDir);
	//printf("\n");

	if (LisenceBool)
	{
		Dialog::SetProgressInc(30);
		Dialog::SetProgressText("アップデートが存在するか確認をします。");
		char restart_buf[100];
		int _Index = Redirect(redxserver, redirect_version, MenuVersion);
		if (strstr(get_cmd_2, ON_UPDATE) && _Index == 0) //
		{
			Dialog::SetProgressInc(36);
			Dialog::SetProgressText("アップデートを開始します。");
			sleep(200);
			Dialog::Close();
			DownloadFile_(redxserver, redirect_sprxdownload, re_hyper_dx_sprx, "");
			strcpy(get_cmd, "[Re:Hyper Dx] アップデート完了しました！\n[Re:Hyper Dx] GTA5を再起動してください！");
			strcpy(_get_cmd, "");
			//cellFsUnlink("/dev_hdd0/tmp/Auto_Setting.txt");
			D_FREEZE = true;
		}
		else if (strstr(get_cmd_2, OFF_UPDATE) && _Index == 0)
		{
			Dialog::SetProgressInc(36);
			Dialog::SetProgressText("ライセンスが有効であるかの確認します。");
			strcpy(get_cmd_2, "\0");
			sprintf(SendBuf, "%s%s%s%s", q_lisence_eq, LisenceBuf, a_mac_eq, MacAddress300);
			//printf(SendBuf);
			//strcat(SendBuf, "\0");
			//printf(SendBuf);
			int _Index_ = Redirect(redxserver, redirect_redx, SendBuf);
			if (_Index_ == 0)
			{
				if (strstr(get_cmd_2, USEDLISENCE))
				{
					strcpy(get_cmd, "Error Code : 0xF8000002");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, NOT_CONNECTED))
				{
					strcpy(get_cmd, "Error Code : 0xFFFFFFFF");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, DIRECTERROR))
				{
					strcpy(get_cmd, "Error Code : 0xC000000F");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, NULLORINVALID))
				{
					strcpy(get_cmd, "Error Code : 0xF8000001");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, CANTLOGIN))
				{
					strcpy(get_cmd, "Error Code : 0xF8000003");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, BANNED_LISENCE))
				{
					strcpy(get_cmd, "Error Code : 0xF8000000");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
				else if (strstr(get_cmd_2, ADMIN_LISENCE))
				{
					strcpy(get_cmd, "\nOpen Menu □ + →");
					strcpy(_get_cmd, "    A    D    M            I     N");
					_AdminFlag = true;
				}
				else if (strstr(get_cmd_2, NORMAL_LISENCE))
				{
					strcpy(get_cmd, "[Re:Hyper Dx]\nこの度は購入ありがとうございます！\nOpen Menu □ + →");
					strcpy(_get_cmd, "by すたんぐ");
					_AdminFlag = false;
				}
				else
				{
					strcpy(get_cmd, "ネットワークに接続されていないか、接続が不安定です。\nネットワーク設定を確認した後に起動してください。");
					strcpy(_get_cmd, "10秒後再起動します。");
					D_FREEZE = true;
				}
			}
			else
			{
				strcpy(get_cmd, "ネットワークに接続されていないか、接続が不安定です。\nネットワーク設定を確認した後に起動してください。");
				strcpy(_get_cmd, "10秒後再起動します。");
				D_FREEZE = true;
			}
		}
		else
		{
			strcpy(get_cmd, "ネットワークに接続されていないか、接続が不安定です。\nネットワーク設定を確認した後に起動してください。");
			strcpy(_get_cmd, "10秒後再起動します。");
			D_FREEZE = true;
		}
	}
	else
	{
		printf(LisenceBuf);
		printf("\n");
		strcpy(get_cmd, "ライセンスが読み込めませんでした。\n同封されているファイルを[/dev_hdd0/tmp/]に入れてください。");
		strcpy(_get_cmd, "10秒後再起動します。");
		D_FREEZE = true;
	}

	Dialog::SetProgressInc(34);
	sleep(1000);

	Dialog::Close();
#pragma endregion
	
	if (D_FREEZE)
	{
		Dialog::ShowText(get_cmd);
		Dialog::SetProgressText(_get_cmd);

		sleep(10000);
		Redirect("localhost", "restart.ps3", "");
	}
	else
	{

		//int fd;

		Dialog::ShowText(get_cmd);
		Dialog::SetProgressText(_get_cmd);

		for (int i = 0; i < 100; i++)
		{
			Dialog::SetProgressInc(1);
			sleep(50);
		}
		Dialog::Close();
	}
	printf("g_tSysTime = 0x%X\ng_ulKeyValue = 0x%X\n", g_tSysTime, g_ulKeyValue);
	printf("Thread Ended *1\n");
	sys_ppu_thread_exit(a);
}

extern "C" int _Memories_prx_entry(void)
{
	//system_call_2(867, 0x19003, (uint64_t)IDPS);
	strcpy(devhdd0_tmp, LoadText(dev_hdd0_tmp, 14));
	strcpy(lisencepath, devhdd0_tmp);
	strcat(lisencepath, LoadText(re_hyper_dx_key, 14));

	sys_ppu_thread_create(&threadId[0], Engine_Thread, 0, 10, 0x10, 0, "Hyper Dx");
	create_threadchat(Thread_2, 0x5aa, 0x2000, "Chat");


	//sys_ppu_thread_create(&threadId[1], Thread2, 0, 0x5aa, 0x2000, 0, "[Hyper Dx]Chat Thread");

	return SYS_PRX_RESIDENT;
}