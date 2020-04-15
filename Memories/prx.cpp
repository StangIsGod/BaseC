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
//#include <math.h>
#pragma comment(lib, "net_stub")
#pragma comment(lib, "netctl_stub")

//*/
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
#include "Functions.h"
#include "AddOptions.h"


SYS_MODULE_INFO( Memories, 0, 1, 0);
SYS_MODULE_START( _Memories_prx_entry );


sys_ppu_thread_t threadId;
void Hook();
int waitTimeMain;


namespace Hooking
{

	void MainTheread(NativeArg_s* pArg)
	{
		if (!strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud"))
		{
			if (GAMEPLAY::GET_GAME_TIMER() > waitTimeMain)
			{
				much4uLoop();
				waitTimeMain = GAMEPLAY::GET_GAME_TIMER() + 10;
			}
		}
		int bOnline;
		bOnline = is_player_online_orig();
		pArg->SetRet(bOnline);
		char *script = SCRIPT::GET_THIS_SCRIPT_NAME();
		if (!strcmp(script, "ingamehud"))
		{
			Hook();                   
			otherLoop();
		}
		Functions();
		if (Loading_Vehicle)
		{
			if (Create_Vehicle(Vehicle_String) == 1)
			{
				Vehicle_String = "";
				Loading_Vehicle = false;
			}
		}
		if (CreateMap)
		{
			if (Create_Map(MapObjectName) == 1)
			{
				MapObjectName = "";
				CreateMap = false;
			}
		}
		if (xMovieFix == 0.0f && yMovieFix == 0.0f && submenu == Closed)
		{
			if (PS3::SetGlobal(2394218 + 550 + 6, NULL, 1) == 0)
			{
				xMovieFix = 0.0218f;
				yMovieFix = 0.0186f;
			}
		}

		PS3::SetGlobal(262145 + 105, 999999999, 0);
		PS3::SetGlobal(262145 + 106, 999999999, 0);
		PS3::SetGlobal(262145 + 4599, 999999999, 0);

		PS3::WriteString(0x1820630, "No Player");//"**Invalid**" => "-"
	}


	void does_entity_exist(NativeArg_s* pArg)
	{
		Vector3 bGetEntityR;
		uint32_t Entity = pArg->GetArg<uint32_t>(0);
		int bGetEntityA = does_entity_exist_orig(Entity);
		pArg->SetRet(bGetEntityA);
		monitorButtons();

           if(NETWORK::NETWORK_IS_IN_SESSION())		
		   {
			if (!IsGettingProtec && ProtectionBypassTimer < GAMEPLAY::GET_GAME_TIMER() + 3000)
			{
				SessionChangeApply(false);
				IsGettingProtec = true;
			}
		}
		else
		{
			if (IsGettingProtec)
			{
				SessionChangeApply(true);
				ProtectionBypassTimer = GAMEPLAY::GET_GAME_TIMER();
				ProtectionAllApply(false);
				IsGettingProtec = false;
			}
		}
	}
}

void Hook()
{
	if (FlagIndexes == AdminFlag)
	{
		MenuID = true;
	}
	else
	{
		MenuID2 = true;
	}
	if (submenu != Closed)
	{
		DrawingMenus::normalMenuActions();
	}
	optionCount = 0;
	HelpIndex = 0;
	switch (submenu)
	{
		#pragma region Main Menu
		
	case Main_Menu:
		if (FlagIndexes == AdminFlag)
		{
			addTitle("~p~Phantom ~r~Admin");
			DropKickDetected = true;
		}
		else
		{
			addTitle("~p~Phantom");
		}
		addSubmenuOption("セルフオプション", Self_Options);
		addSubmenuOption("プレイヤーリスト", Select_Players_List);
		addSubmenuOption("オールプレイヤー", AllPlayer);
		addSubmenuOption("武器オプション", WeaponEditor);
		addSubmenuOption("車両スポーン", VehicleSpawner);
		addSubmenuOption("車両オプション", VehicleCheat);
		addSubmenuOption("テレポート一覧", Teleporter);
		addSubmenuOption("ファン機能", FunMenu);
		addSubmenuOption("アニメーション", Animations);	
		addSubmenuOption("スポーンした車", SpawnedVehicleList);
		addSubmenuOption("ペッドスポーン", PedMenu);
		addSubmenuOption("モデル変更", ModelChanger);
		addSubmenuOption("天候 / 時間", WeatherOptions);
		addSubmenuOption("オブジェクト", ObjectMenu);
		addSubmenuOption("メモリエディター", memoryeditor);
		if (FlagIndexes == AdminFlag)
		{
			addSubmenuOption("フライングカー", Freezecar);
		}
		addSubmenuOption("プロテクション", Protections);
		//addSubmenuOption("オプション一括有効化", AllActiveButtons);
		addSubmenuOption("設定", Settings, "メニューの構造を設定します。");
		FreezeNormal(1076751048);
		FreezeNormal(1076625000);
		switch (getOption())
		{

		}
		break;
#pragma endregion
#pragma region EffectCoolorMenu
	case EffectCoolorMenu:
		addTitle("エフェクトエディター");
		addOption("エフェクト削除");
		addOption("元に戻す");
		addFloatOption("赤", &EffectColorFloat[0], 0, 1, true, 0.05f, "");
		addFloatOption("緑", &EffectColorFloat[1], 0, 1, true, 0.05f, "");
		addFloatOption("青", &EffectColorFloat[2], 0, 1, true, 0.05f, "");
		addFloatOption("透明度", &EffectColorFloat[3], 0, 1, true, 0.05f, "");
		//addCheckBool("レインボー", Rainbow_Effect);
		if (rightPress || leftPress || fastLeftPress || fastRightPress)
		{
			switch (currentOption)
			{
			case 3:
				PS3::WriteFloat(0x1E60FF0, EffectColorFloat[0]);
				break;

			case 4:
				PS3::WriteFloat(0x1E60FF4, EffectColorFloat[1]);
				break;

			case 5:
				PS3::WriteFloat(0x1E60FF8, EffectColorFloat[2]);
				break;

			case 6:
				PS3::WriteFloat(0x1E60FFC, EffectColorFloat[3]);
				break;
			}
		}

		switch (getOption())
		{
		case 1:
			PS3::WriteFloat(0x1E60FFC, 0.0f);
			EffectColorFloat[3] = 0;
			break;

		case 2:
			EffectColorFloat[0] = 1.0f;
			EffectColorFloat[1] = 1.0f;
			EffectColorFloat[2] = 1.0f;
			EffectColorFloat[3] = 1.0f;
			PS3::WriteFloat(0x1E60FF0, 1.0f);
			PS3::WriteFloat(0x1E60FF4, 1.0f);
			PS3::WriteFloat(0x1E60FF8, 1.0f);
			PS3::WriteFloat(0x1E60FFC, 1.0f);
			break;
		//case 7:
		//	Rainbow_Effect = !Rainbow_Effect;
		//	break;
		}
		break;
#pragma endregion
#pragma region CurrentWaterEdit
	case CurrentWaterEdit:
		Vector2 ReturnXY = ReturnWaterXY(SelectedWaterQuad);
		addTitle(quadFormatStr(SelectedWaterQuad));
		DrawViewName(SelectedWaterQuad);
		DrawBoxWater(SelectedWaterQuad);
		WaterQuadInfo(SelectedWaterQuad);
		addIntOption("透明度", &WaterOpacity, 0, 0xFF, true, "", true);
		addOption("Quadへテレポート");
		switch (getOption())
		{
		case 1:
			PS3::WriteByte(WaterQuad + SelectedWaterQuad * 0x1C + 0x08, (char)WaterOpacity);
			PS3::WriteByte(WaterQuad + SelectedWaterQuad * 0x1C + 0x09, (char)WaterOpacity);
			PS3::WriteByte(WaterQuad + SelectedWaterQuad * 0x1C + 0x0A, (char)WaterOpacity);
			PS3::WriteByte(WaterQuad + SelectedWaterQuad * 0x1C + 0x0B, (char)WaterOpacity);
			break;

		case 2:
			MyConsoleTeleport(PLAYER::PLAYER_PED_ID(), ReturnXY.x, ReturnXY.y, CurrentWaterQuad.height + 1.0f);
			break;
		}
		break;
#pragma endregion

#pragma region QuadList
	case QuadList:
		addTitle("Quad List");
		WaterQuad = PS3::ReadInt32(QuadPointer);
		for (int i = 0; i < WaterQuadLength; i++)
		{
			addOption(quadFormatStr(i), "", "+");
		}

		if (isPressed(Button_R1))
		{
			if (WaterQuadLength > currentOption + 10)
			{
				currentOption += 10;
			}
		}
		if (isPressed(Button_L1))
		{
			if (currentOption > 10)
			{
				currentOption -= 10;
			}
		}
		DrawViewName(currentOption - 1);
		DrawBoxWater(currentOption - 1);
		WaterQuadInfo(currentOption - 1);
		if (optionPress)
		{
			SelectedWaterQuad = currentOption - 1;
			GetWaterQuadData(SelectedWaterQuad);
			changeSubmenu(CurrentWaterEdit);
		}
		break;
#pragma endregion

#pragma region WaterColorEditors
	case WaterColorEditors:
		addTitle("リアルタイム海色エディター");
		addOption("取得");
		addFloatOption("速度", &WaterMovement, 0, 1, true, 0.0001f, "", false, 0.0001f);
		addFloatOption("海面のなんか", &RippleScale, 0, 10000.0f, true, WaterMovement, "", true, 0.0001f);
		addFloatOption("上の泡のきめ細かさ", &OceanFoamScale, 0, 10000.0f, true, WaterMovement, "", true, 0.0001f);
		addFloatOption("海面の光沢", &SpecularIntensity, 0, 10000.0f, true, WaterMovement, "", true, 0.0001f);
		addFloatOption("海面の光沢の減少率", &SpecularFalloff, 0, 10000.0f, true, WaterMovement, "", true, 0.0001f);
		addFloatOption("海面の光沢 2", &FogPierceIntensity, 0, 10000.0f, true, WaterMovement, "", true, 0.0001f);
		addOption("デフォルトに戻す");

		if (rightPress || leftPress || fastLeftPress || fastRightPress)
		{
			switch (currentOption)
			{
			case 3:
				PS3::WriteFloat(0x21C62A4, RippleScale);
				break;
			case 4:
				PS3::WriteFloat(0x21C62A8, OceanFoamScale);
				break;
			case 5:
				PS3::WriteFloat(0x21C62AC, SpecularIntensity);
				break;
			case 6:
				PS3::WriteFloat(0x21C62B0, SpecularFalloff);
				break;
			case 7:
				PS3::WriteFloat(0x21C62B4, FogPierceIntensity);
				break;
			}
		}
		switch (getOption())
		{
			case 1:
				RippleScale = *(float*)(0x21C62A4);
				OceanFoamScale = *(float*)(0x21C62A8);
				SpecularIntensity = *(float*)(0x21C62AC);
				SpecularFalloff = *(float*)(0x21C62B0);
				FogPierceIntensity = *(float*)(0x21C62B4);
				break;
			case 8:

				PS3::WriteFloat(0x21C62A4, 0.040000);
				PS3::WriteFloat(0x21C62A8, 0.050000);
				PS3::WriteFloat(0x21C62AC, 1.750000);
				PS3::WriteFloat(0x21C62B0, 1118.000000);
				PS3::WriteFloat(0x21C62B4, 0.7500000);
				RippleScale = *(float*)(0x21C62A4);
				OceanFoamScale = *(float*)(0x21C62A8);
				SpecularIntensity = *(float*)(0x21C62AC);
				SpecularFalloff = *(float*)(0x21C62B0);
				FogPierceIntensity = *(float*)(0x21C62B4);
				break;
		}

		break;
#pragma endregion

#pragma region WaterQuadEditors
	case WaterQuadEditors:
		addTitle("リアルタイム海エディター");
		addSubmenuOption("海リスト", QuadList, "");
		addIntOption("海全体の透明度", &WaterOpacityAll, 0, 0xFF, true, "", true);

		if (rightPress || leftPress || fastLeftPress || fastRightPress)
		{
			switch (currentOption)
			{
			case 2:	WaterOpacityEdit(WaterOpacityAll);
				break;
			}
		}
		break;
#pragma endregion

#pragma region WaterAddressEditor
	case WaterAddressEditor:
		addTitle("ウォーターアドレス");
		addSubmenuOption("リアルタイム海エディター", WaterQuadEditors);
		addOption("リアルタイム海色エディター", "", ">>");
		switch (getOption())
		{
		case 2:
			RippleScale = *(float*)(0x21C62A4);
			OceanFoamScale = *(float*)(0x21C62A8);
			SpecularIntensity = *(float*)(0x21C62AC);
			SpecularFalloff = *(float*)(0x21C62B0);
			FogPierceIntensity = *(float*)(0x21C62B4);
			changeSubmenu(WaterColorEditors);
			break;
		}
		break;
#pragma endregion

#pragma region CompModelChangerMenu
	case CompModelChangerMenu:
		addTitle(CompModelName);
		addCharSwap("モデルチェンジ", WEAPONCOMPMODELJAPANESE, &CompModelChangeVar, 0, 19, "");
		//addOption("元に戻す"); //ModelChangerMenuModel
		switch (getOption())
		{
		case 1:
			SelectedCompAddress = WeaponCompReturn(ModelChangerMenuHash);
			PS3::WriteInt32(SelectedCompAddress + 0x0C, GAMEPLAY::GET_HASH_KEY(WEAPONCOMPMODELHASH[CompModelChangeVar]));
			break;

		case 2:
			SelectedCompAddress = WeaponCompReturn(ModelChangerMenuHash);
			PS3::WriteInt32(SelectedCompAddress + 0x0C, ModelChangerMenuModel);
			break;
		}

		break;
#pragma endregion

#pragma region COMPONENTATPIFLSH
	case COMPONENTATPIFLSH:
		addTitle("ピストル ライト");
		addCharSwap("モデルチェンジ", WEAPONCOMPMODELJAPANESE, &CompModelChangeVar, 0, 19, "モデルチェンジするとライトが消えます。");
		addOption("モデルをもとに戻す");
		addOption("取得");
		addIntOption("メインライト 光の強さ", &MainLightIntensity, 0, 1000, true, "");

		//	addIntOption("Color 1", &Color1Comp[0], 0, 0xFF, true, "");
		addIntOption("メインライト ~r~赤", &Color1Comp[1], 0, 0xFF, true, "");
		addIntOption("メインライト ~g~緑", &Color1Comp[2], 0, 0xFF, true, "");
		addIntOption("メインライト ~b~青", &Color1Comp[3], 0, 0xFF, true, "");

		addIntOption("ライト 射程距離", &MainLightRange, 0, 1000, true, "");
		addIntOption("ライト 薄さ", &MainLightFalloffExponent, 0, 1000, true, "");
		addIntOption("ライト 薄さ2", &MainLightInnerAngle, 0, 1000, true, "");
		addIntOption("ライト 光の細さ", &MainLightOuterAngle, 0, 1000, true, "");

		addIntOption("ライト コロナの強さ (不明)", &MainLightCoronaIntensity, 0, 1000, true, "不明");
		addIntOption("ライト コロナ サイズ(不明)", &MainLightCoronaSize, 0, 1000, true, "不明");
		addIntOption("ライト 全体 濃さ", &MainLightVolumeIntensity, 0, 1000, true, "");
		addIntOption("ライト 全体 濃さ2", &MainLightVolumeSize, 0, 1000, true, "");

		addIntOption("主光量指数 (不明)", &MainLightVolumeExponent, 0, 1000, true, "不明");

		addIntOption("メインアウターカラー1 (不明)", &Color1CompSecond[0], 0, 0xFF, true, "不明");
		addIntOption("メインアウターカラー2 (不明)", &Color1CompSecond[1], 0, 0xFF, true, "不明");
		addIntOption("メインアウターカラー3 (不明)", &Color1CompSecond[2], 0, 0xFF, true, "不明");
		addIntOption("メインアウターカラー4 (不明)", &Color1CompSecond[3], 0, 0xFF, true, "不明");

		addIntOption("ライト 影 強さ", &MainLightShadowFadeDistance, 0, 1000, true, "");
		addIntOption("ライト 影 強さ2", &MainLightSpecularFadeDistance, 0, 7, true, "");

		addIntOption("サブライト 光の強さ", &SecondaryLightIntensity, 0, 1000, true, "");

		//addIntOption("ライト サブカラー 赤", &SecondaryColor1Comp[0], 0, 0xFF, true, "");
		addIntOption("ライト サブカラー ~r~赤", &SecondaryColor1Comp[1], 0, 0xFF, true, "");
		addIntOption("ライト サブカラー ~g~緑", &SecondaryColor1Comp[2], 0, 0xFF, true, "");
		addIntOption("ライト サブカラー ~b~青", &SecondaryColor1Comp[3], 0, 0xFF, true, "");
		addIntOption("サブライト 射程距離", &SecondaryLightRange, 0, 1000, true, "");
		addIntOption("サブライト 薄さ", &SecondaryLightFalloffExponent, 0, 1000, true, "");


		addIntOption("サブライト 薄さ2", &SecondaryLightInnerAngle, 0, 1000, true, "");
		addIntOption("サブライト 光の細さ", &SecondaryLightOuterAngle, 0, 1000, true, "");
		//addIntOption("サブライト 光の細さ", &SecondaryLightVolumeIntensity, 0, 1000, true, "");
		/*addIntOption("SecondaryLightVolumeSize", &SecondaryLightVolumeSize, 0, 1000, true, "");
		addIntOption("SecondaryLightVolumeExponent", &SecondaryLightVolumeExponent, 0, 1000, true, "");
		addIntOption("SecondaryLightVolumeOuterColor1", &SecondaryLightVolumeOuterColor1Comp[0], 0, 0xFF, true, "");
		addIntOption("SecondaryLightVolumeOuterColor2", &SecondaryLightVolumeOuterColor1Comp[1], 0, 0xFF, true, "");
		addIntOption("SecondaryLightVolumeOuterColor3", &SecondaryLightVolumeOuterColor1Comp[2], 0, 0xFF, true, "");
		addIntOption("SecondaryLightVolumeOuterColor4", &SecondaryLightVolumeOuterColor1Comp[3], 0, 0xFF, true, "");
		addIntOption("SecondaryLightFadeDistance", &SecondaryLightFadeDistance, 0, 1000, true, "");
		addIntOption("fTargetDistalongAimCamera", &fTargetDistalongAimCamera, 0, 1000, true, "");*/
		if (leftPress || rightPress || fastLeftPress || fastRightPress)
		{
			switch (currentOption)
			{
			case 4:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightIntensity, SYSTEM::TO_FLOAT(MainLightIntensity));
				break;

				/*case 5:
				PS3::WriteByte(SelectedCompAddress + F_MainLightColor1, Color1Comp[0]);
				break;*/

			case 5:
				PS3::WriteByte(SelectedCompAddress + F_MainLightColor2, Color1Comp[1]);
				break;

			case 6:
				PS3::WriteByte(SelectedCompAddress + F_MainLightColor3, Color1Comp[2]);
				break;

			case 7:
				PS3::WriteByte(SelectedCompAddress + F_MainLightColor4, Color1Comp[3]);
				break;

			case 8:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightRange, SYSTEM::TO_FLOAT(MainLightRange));
				break;

			case 9:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightFalloffExponent, SYSTEM::TO_FLOAT(MainLightFalloffExponent));
				break;

			case 10:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightInnerAngle, SYSTEM::TO_FLOAT(MainLightInnerAngle));
				break;

			case 11:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightOuterAngle, SYSTEM::TO_FLOAT(MainLightOuterAngle));
				break;

			case 12:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightCoronaIntensity, SYSTEM::TO_FLOAT(MainLightCoronaIntensity));
				break;

			case 13:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightCoronaSize, SYSTEM::TO_FLOAT(MainLightCoronaSize));
				break;

			case 14:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightVolumeIntensity, SYSTEM::TO_FLOAT(MainLightVolumeIntensity));
				break;

			case 15:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightVolumeSize, SYSTEM::TO_FLOAT(MainLightVolumeSize));
				break;

			case 16:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightVolumeExponent, SYSTEM::TO_FLOAT(MainLightVolumeExponent));
				break;

			case 17:
				PS3::WriteByte(SelectedCompAddress + F_MainLightVolumeOuterColor1, Color1CompSecond[0]);
				break;

			case 18:
				PS3::WriteByte(SelectedCompAddress + F_MainLightVolumeOuterColor2, Color1CompSecond[1]);
				break;

			case 19:
				PS3::WriteByte(SelectedCompAddress + F_MainLightVolumeOuterColor3, Color1CompSecond[2]);
				break;

			case 20:
				PS3::WriteByte(SelectedCompAddress + F_MainLightVolumeOuterColor4, Color1CompSecond[3]);
				break;

			case 21:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightShadowFadeDistance, SYSTEM::TO_FLOAT(MainLightShadowFadeDistance));
				break;

			case 22:
				PS3::WriteFloat(SelectedCompAddress + F_MainLightSpecularFadeDistance, SYSTEM::TO_FLOAT(MainLightSpecularFadeDistance));
				break;

			case 23:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightIntensity, SYSTEM::TO_FLOAT(SecondaryLightIntensity));
				break;

				/*case 24:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightColor1, SecondaryColor1Comp[0]);
				break;*/

			case 24:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightColor2, SecondaryColor1Comp[1]);
				break;

			case 25:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightColor3, SecondaryColor1Comp[2]);
				break;

			case 26:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightColor4, SecondaryColor1Comp[3]);
				break;

			case 27:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightRange, SYSTEM::TO_FLOAT(SecondaryLightRange));
				break;

			case 28:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightFalloffExponent, SYSTEM::TO_FLOAT(SecondaryLightFalloffExponent));
				break;


			case 29:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightInnerAngle, SYSTEM::TO_FLOAT(SecondaryLightInnerAngle));
				break;

			case 30:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightOuterAngle, SYSTEM::TO_FLOAT(SecondaryLightOuterAngle));
				break;

				/*case 31:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightVolumeIntensity, SYSTEM::TO_FLOAT(SecondaryLightVolumeIntensity));
				break;

				case 32:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightVolumeSize, SYSTEM::TO_FLOAT(SecondaryLightVolumeSize));
				break;

				case 33:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightVolumeExponent, SYSTEM::TO_FLOAT(SecondaryLightVolumeExponent));
				break;

				case 34:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor1, SecondaryLightVolumeOuterColor1Comp[0]);
				break;

				case 35:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor2, SecondaryLightVolumeOuterColor1Comp[1]);
				break;

				case 36:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor3, SecondaryLightVolumeOuterColor1Comp[2]);
				break;

				case 37:
				PS3::WriteByte(SelectedCompAddress + F_SecondaryLightVolumeOuterColor4, SecondaryLightVolumeOuterColor1Comp[3]);
				break;

				case 38:
				PS3::WriteFloat(SelectedCompAddress + F_SecondaryLightFadeDistance, SYSTEM::TO_FLOAT(SecondaryLightFadeDistance));
				break;

				case 39:
				PS3::WriteFloat(SelectedCompAddress + F_fTargetDistalongAimCamera, SYSTEM::TO_FLOAT(fTargetDistalongAimCamera));
				break;*/


			}

		}

		switch (getOption())
		{
		case 1:
			SelectedHash = 0x359B7AAE;
			SelectedModel = 0x43685959;
			SelectedCompAddress = WeaponCompReturn(SelectedHash);
			PS3::WriteInt32(SelectedCompAddress + 0x0C, GAMEPLAY::GET_HASH_KEY(WEAPONCOMPMODELHASH[CompModelChangeVar]));
			break;

		case 2:
			PS3::WriteInt32(SelectedCompAddress + 0x0C, 0x43685959);
			break;

		case 3:
			SelectedCompAddress = WeaponCompReturn(0x43685959);
			ReloadWeaponFlashComp();
			MainLightFalloffExponent = PS3::ReadFloat(SelectedCompAddress + 0x38);
			break;
		}

		break;
#pragma endregion

#pragma region PistolCompo
	case PistolCompo:
		addTitle("ピストル");
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_01", 0xFED0FD71, 0x8ECC910A);
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_02", 0xED265A1C, 0xA11B35A7);
		addCompChangeModelSubmenuOption("COMPONENT_AT_PI_SUPP", 0xC304849A, 0xC2E47B1E);
		addOption("COMPONENT_AT_PI_FLSH", "", ">>");
		switch (getOption())
		{
		case 4:
			SelectedCompAddress = WeaponCompReturn(0x43685959);
			ReloadWeaponFlashComp();
			fTargetDistalongAimCamera = WCFloat(F_fTargetDistalongAimCamera);
			changeSubmenu(COMPONENTATPIFLSH);
			break;
		}
		break;
#pragma endregion

#pragma region CombatPistol
	case CombatPistol:
		addTitle("コンバットピストル");
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_01", 0x0721B079, 0x418C9D74);
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_02", 0xD67B4F2D, 0x4ADEB018);
		addCompChangeModelSubmenuOption("COMPONENT_AT_PI_SUPP", 0xC304849A, 0xC2E47B1E);
		addOption("COMPONENT_AT_PI_FLSH", "", ">>");
		switch (getOption())
		{
		case 4:
			SelectedCompAddress = WeaponCompReturn(0x43685959);
			ReloadWeaponFlashComp();
			fTargetDistalongAimCamera = WCFloat(F_fTargetDistalongAimCamera);
			changeSubmenu(COMPONENTATPIFLSH);
			break;
		}
		break;
#pragma endregion

#pragma region APPistol_
	case APPistol_:
		addTitle("APピストル");
		addCompChangeModelSubmenuOption("COMPONENT_APPISTOL_CLIP_01", 0x31C4B22A, 0x6AA519BA);
		addCompChangeModelSubmenuOption("COMPONENT_APPISTOL_CLIP_02", 0x249A17D5, 0x9C6EFD4D);
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_01", 0x0721B079, 0x418C9D74);
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_02", 0xD67B4F2D, 0x4ADEB018);
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_01", 0xFED0FD71, 0x8ECC910A);
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_02", 0xED265A1C, 0xA11B35A7);
		addCompChangeModelSubmenuOption("COMPONENT_AT_PI_SUPP", 0xC304849A, 0xC2E47B1E);
		addCompChangeModelSubmenuOption("COMPONENT_AT_AR_AFGRIP", 0xC164F53, 0xDF3AE7C5);
		addCompChangeModelSubmenuOption("COMPONENT_AT_AR_AFGRIP", 0xC164F53, 0xDF3AE7C5);
		addOption("COMPONENT_AT_PI_FLSH", "", ">>");
		addOption("COMPONENT_AT_AR_FLSH", "", ">>");
		switch (getOption())
		{
		case 10:
			SelectedCompAddress = WeaponCompReturn(0x43685959);
			ReloadWeaponFlashComp();
			fTargetDistalongAimCamera = WCFloat(F_fTargetDistalongAimCamera);
			changeSubmenu(COMPONENTATPIFLSH);
			break;

		case 11:
			SelectedCompAddress = WeaponCompReturn(0x7BC4CDDC);
			ReloadWeaponFlashComp();
			
			changeSubmenu(COMPONENTATPIFLSH);
			break;
		}
		break;
#pragma endregion

#pragma region GunEditor
	case GunEditor:
		addTitle("アタッチメントエディター");
		/*addSubmenuOption("ピストル", PistolCompo, "");
		addSubmenuOption("コンバットピストル", CombatPistol, "");
		addSubmenuOption("AP ピストル", APPistol_, "");*/
	/*addCompChangeModelSubmenuOption("COMPONENT_APPISTOL_CLIP_01", 0x31C4B22A, 0x6AA519BA);
		addCompChangeModelSubmenuOption("COMPONENT_APPISTOL_CLIP_02", 0x249A17D5, 0x9C6EFD4D);
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_01", 0x0721B079, 0x418C9D74);
		addCompChangeModelSubmenuOption("COMPONENT_COMBATPISTOL_CLIP_02", 0xD67B4F2D, 0x4ADEB018);
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_01", 0xFED0FD71, 0x8ECC910A);
		addCompChangeModelSubmenuOption("COMPONENT_PISTOL_CLIP_02", 0xED265A1C, 0xA11B35A7);
		addCompChangeModelSubmenuOption("COMPONENT_AT_PI_SUPP", 0xC304849A, 0xC2E47B1E);
		addCompChangeModelSubmenuOption("COMPONENT_AT_AR_AFGRIP", 0xC164F53, 0xDF3AE7C5);
		addCompChangeModelSubmenuOption("POLICE_TORCH_FLASHLIGHT", 0xC164F53, 0xDF3AE7C5);*/
		for (int i = 0; i < 45; i++)
		{
			addOption2(WEAPONCOMPONENT2[i], WEAPONCOMPONENT[i], "", ">>");
		}
		
		addOption("COMPONENT_AT_PI_FLSH", "", ">>");
		addOption("COMPONENT_AT_AR_FLSH", "", ">>");
		addOption("POLICE_TORCH_FLASHLIGHT", "", ">>");
		if (optionPress)
		{
			switch (currentOption)
			{
			case 46:
				SelectedCompAddress = WeaponCompReturn(0x43685959);
				if (SelectedCompAddress != 0)
				{
					ReloadWeaponFlashComp();

					changeSubmenu(COMPONENTATPIFLSH);
				}
				else
				{
					NotifyDown("エラー");
				}
				break;

			case 47:
				SelectedCompAddress = WeaponCompReturn(0x7BC4CDDC);
				if (SelectedCompAddress != 0)
				{
					ReloadWeaponFlashComp();

					changeSubmenu(COMPONENTATPIFLSH);
				}
				else
				{
					NotifyDown("エラー");
				}
				break;

			case 48:
				SelectedCompAddress = WeaponCompReturn(0xC5A30FED);
				if (SelectedCompAddress != 0)
				{
					ReloadWeaponFlashComp();

					changeSubmenu(COMPONENTATPIFLSH);
				}
				else
				{
					NotifyDown("エラー");
				}
				break;
			
			default:

				CompModelName = WEAPONCOMPONENT2[currentOption - 1];
				ModelChangerMenuHash = GAMEPLAY::GET_HASH_KEY(WEAPONCOMPONENT[currentOption - 1]);
				SelectedCompAddress = WeaponCompReturn(ModelChangerMenuHash);
				if (SelectedCompAddress != 0)
				{
					changeSubmenu(CompModelChangerMenu);
				}
				else
				{
					NotifyDown("エラー");
				}
				break;
			}

		}
		

		
		break;
#pragma endregion
#pragma region SkyEditor
	case SkyEditor:
		addTitle("スカイエディター");
		addOption("おかしい空");
		addOption("ピンクブルー");
		addOption("水色");
		addOption("お茶色");
		addOption("あおむらさき");
		addOption("ももいろ");
		addOption("ネオンブルー");
		addOption("黄色");
		addOption("オレンジ");
		addOption("パープル");
		addOption("空無し");
		switch (getOption())
		{
		case 1:
			SkyColor::WTFSky();
			break;

		case 2:
			SkyColor::PinkBlueSky();
			break;

		case 3:
			SkyColor::LightningBlueSky();
			break;

		case 4:
			SkyColor::TeaSky();
			break;

		case 5:
			SkyColor::BlurpleSky();
			break;

		case 6:
			SkyColor::PeachSky();
			break;

		case 7:
			SkyColor::NeonBlueSky();
			break;

		case 8:
			SkyColor::YellowSky(); 
			break;

		case 9:
			SkyColor::OrangeSky();
			break;

		case 10:
			SkyColor::PurpleSky();
			break;

		case 11:
			SkyColor::NoSky();
			break;
		}
		break;
#pragma endregion

#pragma region WeatherEditor
	/*case WeatherEditor:
		addTitle("天候エディター");
		addSubmenuOption("BLIZZARD", RealTime_Blizzard);
		addSubmenuOption("RAINSTORM", RealTime_Rainstorm);
		addSubmenuOption("SNOWHEAVY", RealTime_Snowheavy);
		addSubmenuOption("SNOWLIGHT", RealTime_Snowlight);
		addSubmenuOption("THUNDER", RealTime_Thunder);
		//addSubmenuOption("UNDERWATER", RealTime_Underwater);
		break;
	case RealTime_Thunder:
		addTitle("THUNDER");
		addOption("THUNDER_RENDER_DROP");
		addOption("THUNDER_RENDER_GROUND");
		addOption("THUNDER_RENDER_MIST");
		switch (getOption())
		{
		case 1:
			SelectedRenderAddress = THUNDER_RENDER_DROP;
			SelectedRender = Render_Read(THUNDER_RENDER_DROP);
			changeSubmenu(RenderEditor____);
			break;
		case 2:
			SelectedRenderAddress = THUNDER_RENDER_GROUND;
			SelectedRender = Render_Read(THUNDER_RENDER_GROUND);
			changeSubmenu(RenderEditor____);
			break;
		case 3:
			SelectedRenderAddress = THUNDER_RENDER_MIST;
			SelectedRender = Render_Read(THUNDER_RENDER_MIST);
			changeSubmenu(RenderEditor____);
			break;
		}
		break;
	case RealTime_Snowlight:
		addTitle("SNOWLIGHT");
		addOption("SNOWLIGHT_RENDER_MIST");
		switch (getOption())
		{
		case 1:
			SelectedRenderAddress = SNOWLIGHT_RENDER_MIST;
			SelectedRender = Render_Read(SNOWLIGHT_RENDER_MIST);
			changeSubmenu(RenderEditor____);
			break;
		}

		break;
	case RealTime_Snowheavy:
		addTitle("SNOWHEAVY");
		addOption("SNOWHEAVY_RENDER_DROP");
		addOption("SNOWHEAVY_RENDER_GROUND");
		addOption("SNOWHEAVY_RENDER_MIST");
		switch (getOption())
		{
		case 1:
			SelectedRenderAddress = SNOWHEAVY_RENDER_DROP;
			SelectedRender = Render_Read(SNOWHEAVY_RENDER_DROP);
			changeSubmenu(RenderEditor____);
			break;
		case 2:
			SelectedRenderAddress = SNOWHEAVY_RENDER_GROUND;
			SelectedRender = Render_Read(SNOWHEAVY_RENDER_GROUND);
			changeSubmenu(RenderEditor____);
			break;
		case 3:
			SelectedRenderAddress = SNOWHEAVY_RENDER_MIST;
			SelectedRender = Render_Read(SNOWHEAVY_RENDER_MIST);
			changeSubmenu(RenderEditor____);
			break;
		}
		break;
	case RealTime_Rainstorm:
		addTitle("RAINSTORM");
		addOption("RAINSTORM_RENDER_DROP");
		addOption("RAINSTORM_RENDER_GROUND");
		addOption("RAINSTORM_RENDER_MIST");
		switch (getOption())
		{
		case 1:
			SelectedRenderAddress = RAINSTORM_RENDER_DROP;
			SelectedRender = Render_Read(RAINSTORM_RENDER_DROP);
			changeSubmenu(RenderEditor____);
			break;
		case 2:
			SelectedRenderAddress = RAINSTORM_RENDER_GROUND;
			SelectedRender = Render_Read(RAINSTORM_RENDER_GROUND);
			changeSubmenu(RenderEditor____);
			break;
		case 3:
			SelectedRenderAddress = RAINSTORM_RENDER_MIST;
			SelectedRender = Render_Read(RAINSTORM_RENDER_MIST);
			changeSubmenu(RenderEditor____);
			break;
		}
		break;

	case RealTime_Blizzard:
		addTitle("BLIZZARD");
		addOption("BLIZZARD_RENDER_DROP");
		addOption("BLIZZARD_RENDER_GROUND");
		switch (getOption())
		{
		case 1:
			SelectedRenderAddress = BLIZZARD_RENDER_DROP;
			SelectedRender = Render_Read(BLIZZARD_RENDER_DROP);
			changeSubmenu(RenderEditor____);
			break;
		case 2:
			SelectedRenderAddress = BLIZZARD_RENDER_GROUND;
			SelectedRender = Render_Read(BLIZZARD_RENDER_GROUND);
			changeSubmenu(RenderEditor____);
			break;
		}
		break;

	case RenderEditor____:
		if (isDpadPress())
		{
			WriteAllRender(SelectedRenderAddress, SelectedRender);
		}
		addTitle("Render");
		addFloatOption("textureRowsColsAnim.x", &SelectedRender.textureRowsColsAnim[0], 0, 50, true, 0.1f, "");
		addFloatOption("textureRowsColsAnim.y", &SelectedRender.textureRowsColsAnim[1], 0, 50, true, 0.1f, "");
		addFloatOption("textureRowsColsAnim.z", &SelectedRender.textureRowsColsAnim[2], 0, 50, true, 0.1f, "");
		addFloatOption("sizeMinMax.x", &SelectedRender.sizeMinMax[0], 0, 50, true, 0.1f, "");
		addFloatOption("sizeMinMax.y", &SelectedRender.sizeMinMax[1], 0, 50, true, 0.1f, "");
		addFloatOption("sizeMinMax.z", &SelectedRender.sizeMinMax[2], 0, 50, true, 0.1f, "");
		addFloatOption("sizeMinMax.w", &SelectedRender.sizeMinMax[3], 0, 50, true, 0.1f, "");
		addFloatOption("colour.R", &SelectedRender.colour[0], 0, 50, true, 0.1f, "");
		addFloatOption("colour.G", &SelectedRender.colour[1], 0, 50, true, 0.1f, "");
		addFloatOption("colour.B", &SelectedRender.colour[2], 0, 50, true, 0.1f, "");
		addFloatOption("colour.A", &SelectedRender.colour[3], 0, 50, true, 0.1f, "");
		addFloatOption("fadeInOut.x", &SelectedRender.fadeInOut[0], 0, 50, true, 0.1f, "");
		addFloatOption("fadeInOut.y", &SelectedRender.fadeInOut[1], 0, 50, true, 0.1f, "");
		addFloatOption("fadeNearFar.x", &SelectedRender.fadeNearFar[0], 0, 50, true, 0.1f, "");
		addFloatOption("fadeNearFar.y", &SelectedRender.fadeNearFar[1], 0, 50, true, 0.1f, "");

		addFloatOption("fadeZ", &SelectedRender.fadeZ, 0, 50, true, 0.1f, "");
		addFloatOption("directionalZOffsetMinMax.x", &SelectedRender.directionalZOffsetMinMax[0], 0, 50, true, 0.1f, "");
		addFloatOption("directionalZOffsetMinMax.y", &SelectedRender.directionalZOffsetMinMax[1], 0, 50, true, 0.1f, "");
		addFloatOption("directionalZOffsetMinMax.z", &SelectedRender.directionalZOffsetMinMax[2], 0, 50, true, 0.1f, "");
		addFloatOption("dirVelAddCamSpeedMinMaxMult.x", &SelectedRender.dirVelAddCamSpeedMinMaxMult[0], 0, 50, true, 0.1f, "");
		addFloatOption("dirVelAddCamSpeedMinMaxMult.y", &SelectedRender.dirVelAddCamSpeedMinMaxMult[1], 0, 50, true, 0.1f, "");
		addFloatOption("dirVelAddCamSpeedMinMaxMult.z", &SelectedRender.dirVelAddCamSpeedMinMaxMult[2], 0, 50, true, 0.1f, "");
		addFloatOption("edgeSoftness", &SelectedRender.edgeSoftness, 0, 50, true, 0.1f, "");
		break;
#pragma endregion

#pragma region WeatherEditor
	/*case WeatherEditor:
		addSubmenuOption("BLIZZARD", RealTime_Blizzard);
		switch (getOption())
		{
		case 1: break;
		}
		break;*/
#pragma endregion

#pragma region メモリエディター
	case memoryeditor:
		addTitle("メモリエディター");
		addSubmenuOption("ウォーターアドレス", WaterAddressEditor);
		addSubmenuOption("アタッチメントエディター", GunEditor);
		addSubmenuOption("スカイエディター", SkyEditor);
		addSubmenuOption("エフェクト", EffectCoolorMenu);
		addSubmenuOption("車両ライト変更", AddressSearch);
		//addSubmenuOption("天候エディター", WeatherEditor);
		addSubmenuOption("タイヤ痕エディター", TireUNKOEditor);
		switch (getOption())
		{
		

		}
		break;
#pragma endregion

#pragma region TireUNKOEditor
	case TireUNKOEditor:
		addTitle("タイヤ痕エディター");
		addOption("ノーマル化");
		addIntOption("赤", &Tire_UNKO[0], 0, 0xFF, true, "", true);
		addIntOption("緑", &Tire_UNKO[1], 0, 0xFF, true, "", true);
		addIntOption("青", &Tire_UNKO[2], 0, 0xFF, true, "", true);
		if (isDpadPress())
		{
			switch (currentOption)
			{
			case 1:break;
			default:
				PS3::WriteBytes(0x213A5C0 + 0x04, Tire_Write_Byte, 20);
				PS3::WriteByte(0x213A5C0 + 0x24, (char)Tire_UNKO[0]);
				PS3::WriteByte(0x213A5C0 + 0x25, (char)Tire_UNKO[1]);
				PS3::WriteByte(0x213A5C0 + 0x26, (char)Tire_UNKO[2]);
				PS3::WriteBytes(0x213A634 + 0x04, Tire_Write_Byte, 20);
				PS3::WriteByte(0x213A634 + 0x24, (char)Tire_UNKO[0]);
				PS3::WriteByte(0x213A634 + 0x25, (char)Tire_UNKO[1]);
				PS3::WriteByte(0x213A634 + 0x26, (char)Tire_UNKO[2]);
				PS3::WriteBytes(0x213A6A8 + 0x04, Tire_Write_Byte, 20);
				PS3::WriteByte(0x213A6A8 + 0x24, (char)Tire_UNKO[0]);
				PS3::WriteByte(0x213A6A8 + 0x25, (char)Tire_UNKO[1]);
				PS3::WriteByte(0x213A6A8 + 0x26, (char)Tire_UNKO[2]);
				break;
			}
		}
		switch (getOption())
		{
		case 1:
			PS3::WriteBytes(0x213A5C0, Tire_UNko_Byte, 0x28);
			PS3::WriteBytes(0x213A634, Tire_UNko_Byte, 0x28);
			PS3::WriteBytes(0x213A6A8, Tire_UNko_Byte, 0x28);
			break;
		}
		break;
#pragma endregion

		#pragma region Freezecar
	case Freezecar:
		addTitle("フライグゥ～");
		addOption("T20 サーチ & セット");
		addOption("T20 元に戻す"); //00 00 00 00 00 00 00 05 
		addOption("ゼントーノ サーチ & セット");
		addOption("ゼントーノ 元に戻す");
		uint aaa;
		snprintf(KKKK, 40, "Address : 0x%8X", index);
		drawText(KKKK, 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);

		snprintf(KKSS, 40, "Address : 0x%8X", AddressHandling);
		drawText(KKSS, 0, 0.5, 0.525, 0.4, 0.4, 255, 255, 255, 255, true);

		switch (getOption())
		{
		case 1:
			SearchOffset[0] = T20Offset[0];
			SearchOffset[1] = T20Offset[1];
			SearchOffset[2] = T20Offset[2];
			SearchOffset[3] = T20Offset[3];
			index = 0; SettingFlying = true; Getting = true; break;

		case 2:
			SearchOffset[0] = T20Offset[0];
			SearchOffset[1] = T20Offset[1];
			SearchOffset[2] = T20Offset[2];
			SearchOffset[3] = T20Offset[3];
			index = 0; ComeBackFlying = true; Getting = true; break;

		case 3:
			SearchOffset[0] = HAKUCHOU[0];
			SearchOffset[1] = HAKUCHOU[1];
			SearchOffset[2] = HAKUCHOU[2];
			SearchOffset[3] = HAKUCHOU[3];
			index = 0; SettingFlying = true; Getting = true; break;

		case 4:
			SearchOffset[0] = HAKUCHOU[0];
			SearchOffset[1] = HAKUCHOU[1];
			SearchOffset[2] = HAKUCHOU[2];
			SearchOffset[3] = HAKUCHOU[3];
			index = 0; ComeBackFlying = true; Getting = true; break;
		}
		break;
#pragma endregion


		#pragma region オブジェクト
	case ObjectMenu:
		addTitle("オブジェクト");
		addOption("オブジェクトマネージャー +");
		addOption("オブジェクト 銃選択オプション");
		addOption("オブジェクトバイパス", "使用できるオブジェクトが増えます。");
		addObjectCharSwap("マップMod用 オブジェ", UnusedObj1, UnusedObjJp1, &ObjectIndexes[0], 0, 9);
		addObjectCharSwap("マップMod用 オブジェ2", ForMapModObj1, ForMapModObjJp1, &ObjectIndexes[1], 0, 4);
		addObjectCharSwap("車アタッチ用 オブジェ1", ForVehAttach1, VehAttJapanse1, &ObjectIndexes[2], 0, 8);
		addObjectCharSwap("車アタッチ用 オブジェ2", objectspawner13, objectspawner13japanese, &ObjectIndexes[11], 0, 32);
		if (objectbypass)
		{
			addObjectCharSwap("スケートオブジェクト", skateobjectlist, skateJapanese1, &ObjectIndexes[3], 0, 6);
			addObjectCharSwap("ローポリマップ", LowPolygonlist, LowPolyJplist, &ObjectIndexes[4], 0, 13);
			addObjectCharSwap("アパート / 家", ApartMentAndHouse, ApartMentHouseJpn, &ObjectIndexes[5], 0, 10);
			addObjectCharSwap("オブジェクト3", MapObjectsList, MapObjJapanese, &ObjectIndexes[6], 0, 10);
		}
		addKeyboardOption("入力", 1, "", 100, "");
		SpawnObjOption("水", "cs3_lod_water_slod3_03", "cs3_lod_water_slod3_03");
		SpawnObjOption("溶岩", "root_scroll_anim_skel", "root_scroll_anim_skel");
		switch (getOption())
		{
		case 1:changeSubmenu(ObjectManager); break;
		case 2: changeSubmenu(ObjectAttachment2); break;
		case 3:ObjectBypass = true; break;
		}
		break;

	case ObjectManager:
		addTitle("オブジェクトマネージャー");
		for (int i = 0; i < 16; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(ObjectList[i]))
			{
				addOption(objectnamearray[i]);
			}
			else
			{
				addOption("オブジェクトが存在しません。");
			}
		}
		ObjectInfo(currentOption - 1); 
		ObjectInfoBool = false;
		if (optionPress)
		{  
			if (ENTITY::DOES_ENTITY_EXIST(ObjectList[currentOption - 1]))
			{
				ObjectSelectedIndex = currentOption - 1;
				changeSubmenu(ObjectManagement);
			}
		}
		break;

	case ObjectManagement:
		addTitle(objectnamearray[ObjectSelectedIndex]);
		addOption("オブジェクトの移動", "", "+");;
		addOption("オブジェクトをアタッチ", "", "+");
		addOption("位置固定化", "フリーズ化");
		addOption("位置固定化解除", "フリーズ解除します。");
		addOption("判定有効化");
		addOption("判定無効化");
		addOption("削除");
		addOption("アドレス表示");
		addFloatOption("サイズ変更", &ObjectSizeVv, 0, 10, true, 0.01, "");
		addCheckBool("サイズ変更 スイッチ", ObjectSizeBool);
		ObjectAttachFlag22 = false;
		ObjectInfoBool = true;
		switch (getOption())
		{
		case 1:changeSubmenu(ObjectMovement); break;
		case 2:changeSubmenu(ObjectAttachment); break;
		case 3:ToggleFreezeEntity(ObjectList[ObjectSelectedIndex], 1); break;
		case 4:ToggleFreezeEntity(ObjectList[ObjectSelectedIndex], 0); break;
		case 5:ToggleCollisionEntity(ObjectList[ObjectSelectedIndex], true); break;
		case 6:ToggleCollisionEntity(ObjectList[ObjectSelectedIndex], false); break;
		case 7:DeleteEntity(ObjectList[ObjectSelectedIndex]); ObjectList[ObjectListIndex] = 0; objectnamearray[ObjectSelectedIndex] = ""; break;
		case 8:NotifyDown(ItoS(GetEntityAddress(ObjectList[ObjectSelectedIndex]), true), 1000); break;
		case 10: ObjectSizeBool = !ObjectSizeBool; break;
		}
		break;

	case ObjectMovement:
		addTitle(objectnamearray[ObjectSelectedIndex]);
		addFloatOption("移動速度", &Movement, 0.1, 3, true, 0.1, "オブジェクトが移動する速度を設定します。");
		addFloatCoord("座標<X軸>", ObjectList[ObjectSelectedIndex], X, Movement);
		addFloatCoord("座標<Y軸>", ObjectList[ObjectSelectedIndex], Y, Movement);
		addFloatCoord("座標<Z軸>", ObjectList[ObjectSelectedIndex], Z, Movement);
		addFloatRotation("回転<X軸>", ObjectList[ObjectSelectedIndex], X, Movement);
		addFloatRotation("回転<Y軸>", ObjectList[ObjectSelectedIndex], Y, Movement);
		addFloatRotation("回転<Z軸>", ObjectList[ObjectSelectedIndex], Z, Movement);
		addOption("回転リセット", "回転<>で動かしたオブジェクトを初期化");
		switch (getOption())
		{
		case 8:ENTITY::SET_ENTITY_ROTATION(ObjectList[ObjectSelectedIndex], 0, 0, 0, 0, 0); break;
		}
		break;
	
	case ObjectAttachment:
		addTitle(objectnamearray[ObjectSelectedIndex]);
		addFloatOption("移動速度", &Movement, 0.1, 3, true, 0.1, "オブジェクトが移動する速度を設定します。");
		addCheckBool("オブジェクトを銃で選択", ShotToEntity, "オフの場合は乗っている車にアタッチされます。");
		addFloatOption("座標X軸", &AttachLoc.x, -10, 10, true, Movement);
		addFloatOption("座標Y軸", &AttachLoc.y, -10, 10, true, Movement);
		addFloatOption("座標Z軸", &AttachLoc.z, -10, 10, true, Movement);
		addFloatOption("回転X軸", &AttachRot.x, 0, 360, true, Movement);
		addFloatOption("回転Y軸", &AttachRot.y, 0, 360, true, Movement);
		addFloatOption("回転Z軸", &AttachRot.z, 0, 360, true, Movement);
		addOption("アタッチ", "選択物にアタッチ");
		addCheckBool("アタッチ(ループ)", ObjectAttachFlag22);
		addCharSwap("アタッチ先", BoneList, &BoneIndex, 0, 6);
		addCheckBool("当たり判定", JudgeMent);
		addCheckBool("透明", JudgeMent_1);
		addOption("リセット");
		switch (getOption())
		{
		case 2:ShotToEntity = !ShotToEntity; break;
		case 9:
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
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ObjectList[ObjectSelectedIndex], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
			}break;
		case 10:ObjectAttachFlag22 = !ObjectAttachFlag22; break;
		case 12: JudgeMent = !JudgeMent; 
			if (JudgeMent)
			{
				Collision(ObjectList[ObjectSelectedIndex], 0);
			}
			else
			{
				Collision(ObjectList[ObjectSelectedIndex], 1);
			}

			break;
		case 13: JudgeMent_1 = !JudgeMent_1;
			  if (JudgeMent_1)
			  {
				  Collision_1(ObjectList[ObjectSelectedIndex], 0);
			  }
			  else
			  {
				  Collision_1(ObjectList[ObjectSelectedIndex], 1);
			  }break;
		case 14: AttachLoc.x = 0; AttachLoc.y = 0; AttachLoc.z = 0; AttachRot.x = 0; AttachRot.y = 0; AttachRot.z = 0; break;
		} break;


	case ObjectAttachment2:
		addTitle("オブジェクト");
		addFloatOption("移動速度", &Movement, 0.1, 3, true, 0.1, "オブジェクトが移動する速度を設定します。");
		addCheckBool("撃った物選択", entityselectedgun);//JudgeMent_1
		addFloatOption("座標X軸", &AttachLoc.x, -10, 10, true, Movement);
		addFloatOption("座標Y軸", &AttachLoc.y, -10, 10, true, Movement);
		addFloatOption("座標Z軸", &AttachLoc.z, -10, 10, true, Movement);
		addFloatOption("回転X軸", &AttachRot.x, 0, 360, true, Movement);
		addFloatOption("回転Y軸", &AttachRot.y, 0, 360, true, Movement);
		addFloatOption("回転Z軸", &AttachRot.z, 0, 360, true, Movement);
		addCheckBool("アタッチ(ループ)", ObjectAttachFlag222);
		addCharSwap("アタッチ先", BoneList, &BoneIndex, 0, 6);
		addCheckBool("当たり判定", JudgeMent);
		addCheckBool("透明", JudgeMent_1);
		addOption("リセット");

		switch (getOption())
		{
		case 2:entityselectedgun = !entityselectedgun; break;
		case 9:ObjectAttachFlag222 = !ObjectAttachFlag222; break;
		case 11: JudgeMent = !JudgeMent;
			if (JudgeMent)
			{
				Collision(selected ,0);
			}
			else
			{
				Collision(selected, 1);
			}

			break;
		case 12: JudgeMent_1 = !JudgeMent_1;
			if (JudgeMent_1)
			{
				Collision_1(selected, 0);
			}
			else
			{
				Collision_1(selected, 1);
			}break;
		case 13: AttachLoc.x = 0; AttachLoc.y = 0; AttachLoc.z = 0; AttachRot.x = 0; AttachRot.y = 0; AttachRot.z = 0; break;

		} break;
#pragma endregion

		#pragma region te
	case WeatherOptions:
		addTitle("天候 / 時間");
		addOption("晴れ", "CLEAR");
		addOption("大雪", "BLIZZARD");
		addOption("クリア", "CLEARING");
		addOption("曇り", "CLOUDS");
		addOption("快晴", "EXTRASUNNY");
		addOption("もや", "FOGGY");
		addOption("異世界", "NEUTRAL");
		addOption("曇り改", "OVERCAST");
		addOption("雨", "RAIN");
		addOption("スモッグ", "SMOG");
		addOption("雪", "SNOW");
		addOption("雪 + 快晴", "SNOWLIGHT");
		addOption("雷雨", "THUNDER");
		addOption("昼", "Time : 12");
		addOption("夜", "Time : 0");
		addOption("夜");
		switch (getOption())
		{
		case 1: CHANGE_WEATHER("CLEAR"); break;
		case 2: CHANGE_WEATHER("BLIZZARD"); break;
		case 3: CHANGE_WEATHER("CLEARING"); break;
		case 4: CHANGE_WEATHER("CLOUDS"); break;
		case 5: CHANGE_WEATHER("EXTRASUNNY"); break;
		case 6: CHANGE_WEATHER("FOGGY"); break;
		case 7: CHANGE_WEATHER("NEUTRAL"); break;
		case 8: CHANGE_WEATHER("OVERCAST"); break;
		case 9: CHANGE_WEATHER("RAIN"); break;
		case 10: CHANGE_WEATHER("SMOG"); break;
		case 11: CHANGE_WEATHER("SNOW"); break;
		case 12: CHANGE_WEATHER("SNOWLIGHT"); break;
		case 13: CHANGE_WEATHER("THUNDER"); break;
		case 14: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, 12, 12); break;
		case 15: NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, 0, 0); break;
		case 16: lobbyTime(0, 0, 0); break;
		}
		break;
#pragma endregion

		#pragma region ModelChanger
	case ModelChanger:
		addTitle("モデルチェンジャー");
		addOption("初期モデル 女");
		addOption("初期モデル 男");
		addOption("ゾンビ");
		addOption("サル");
		addOption("ピエロ");
		addOption("ハッカー");
		addOption("ポゴ");
		addOption("ムキムキ");
		addOption("警官");
		addOption("ビッチガール");
		addOption("ビーチガール");
		addOption("エイリアン");
		addOption("モデルを黒化");
		switch (getOption())
		{
		case 1:ChangeModelHash = true; ModelHash = 0x9C9EFFD8; break;
		case 2:ChangeModelHash = true; ModelHash = 0x705E61F2; break;
		case 3: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("u_m_y_zombie_01");  break;
		case 4: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("A_C_Chimp"); break;
		case 5: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("S_M_Y_Clown_01"); break;
		case 6: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("S_M_Y_Dealer_01"); break;
		case 7: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("U_M_Y_pogo_01"); break;
		case 8: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("S_M_Y_Marine_02"); break;
		case 9: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("S_F_Y_Cop_01"); break;
		case 10: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("A_F_Y_Juggalo_01"); break;
		case 11: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("a_f_y_beach_01"); break;
		case 12: ChangeModelHash = true; ModelHash = GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01"); break;
		case 13:
			for (int i = 0; i < 14; i++)
			{
				Modelo(Family[i], 0, 40, 0);
			} break;
		}
		break;
#pragma endregion

		#pragma region PedMenu
	case PedMenu:
		addTitle("ペッドメニュー");
		addSubmenuOption("ペッドマネージャー", PedManager);
		addSubmenuOption("スポーン時の設定", PedMenuSetting);
		addOptionP("ゾンビ", "u_m_y_zombie_01");
		addOptionP("エイリアン", "s_m_m_movalien_01");
		addOptionP("コマンダー", "u_m_y_rsranger_01");
		addOptionP("下半身露出", "u_m_y_justin");
		addOptionP("モンキー", "A_C_Chimp");
		addOptionP("モンキー", "A_C_Chimp");
		addKeyboardOption("入力", 2, "", 30, "");
		break;

	case PedManager:
		addTitle("ペッドメニュー");
		for (int i = 0; i < 10; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PedList[i]))
			{
				addOption(PedNameList[i]);
			}
			else
			{
				addOption("ペッドが存在しません。");
			}
		}

		if (optionPress)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PedList[currentOption - 1]))
			{
				PedSelectedIndex = currentOption - 1;
				changeSubmenu(PedManagement);
			}
		}
		break;

	case PedManagement:
		addOption("ペッドの移動 +");
		addOption("ペッドをアタッチ +");
		addOption("位置固定化", "フリーズ化");
		addOption("位置固定化解除", "フリーズ解除します。");
		addOption("判定有効化");
		addOption("判定無効化");
		addOption("削除");
		addTitle(PedNameList[PedSelectedIndex]);
		switch (getOption())
		{
		case 1:changeSubmenu(PedMovement); break;
		case 2:changeSubmenu(PedAttachment); break;
		case 3:ToggleFreezeEntity(PedList[PedSelectedIndex], 1); break;
		case 4:ToggleFreezeEntity(PedList[PedSelectedIndex], 0); break;
		case 5:ToggleCollisionEntity(PedList[PedSelectedIndex], true); break;
		case 6:ToggleCollisionEntity(PedList[PedSelectedIndex], false); break;
		case 7:DeleteEntity(PedList[PedSelectedIndex]); PedList[PedSelectedIndex] = 0; break;
		}
		break;

	case PedMenuSetting:
		addTitle("スポーン時の設定");
		addCheckBool("無敵化", IsPedInvincible);
		addCheckBool("ボディーガード化", IsPedBodyguard);
		addCheckBool("ホミラン所持(弾無限)", IsPedHaveWeapon);	
		switch (getOption())
		{
		case 1:IsPedInvincible = !IsPedInvincible; break;
		case 2:IsPedBodyguard = !IsPedBodyguard; break;
		case 3:IsPedHaveWeapon = !IsPedHaveWeapon; break;
		}
		break;
		
	case PedMovement:
		addTitle(PedNameList[PedSelectedIndex]);
		addFloatOption("移動速度", &Movement, 0.1, 10, true, 0.01, "オブジェクトが移動する速度を設定します。");
		addFloatCoord("座標<X軸>", PedList[PedSelectedIndex], X, Movement, true);
		addFloatCoord("座標<Y軸>", PedList[PedSelectedIndex], Y, Movement, true);
		addFloatCoord("座標<Z軸>", PedList[PedSelectedIndex], Z, Movement, true);
		addFloatRotation("回転<X軸>", PedList[PedSelectedIndex], X, Movement, true);
		addFloatRotation("回転<Y軸>", PedList[PedSelectedIndex], Y, Movement, true);
		addFloatRotation("回転<Z軸>", PedList[PedSelectedIndex], Z, Movement, true);
		addOption("回転リセット", "回転<>で動かしたオブジェクトを初期化");

		switch (getOption())
		{
		case 8:ENTITY::SET_ENTITY_ROTATION(PedList[PedSelectedIndex], 0, 0, 0, 0, 0); break;
		}
		break;

	case PedAttachment:
		addTitle(PedNameList[PedSelectedIndex]);
		addFloatOption("移動速度", &Movement, 0.1, 10, true, 0.1, "オブジェクトが移動する速度を設定します。");
		addCheckBool("オブジェクトを銃で選択", ShotToEntity, "オフの場合は乗っている車にアタッチされます。");
		addFloatOption("座標X軸", &AttachLoc.x, 0, 360, true, Movement);
		addFloatOption("座標Y軸", &AttachLoc.y, 0, 360, true, Movement);
		addFloatOption("座標Z軸", &AttachLoc.z, 0, 360, true, Movement);
		addFloatOption("回転X軸", &AttachRot.x, 0, 360, true, Movement);
		addFloatOption("回転Y軸", &AttachRot.y, 0, 360, true, Movement);
		addFloatOption("回転Z軸", &AttachRot.z, 0, 360, true, Movement);
		addOption("アタッチ", "選択物にアタッチ");
		addCheckBool("アタッチ(ループ)", LoopAttach2);
		addCharSwap("アタッチ先", BoneStringList, &BoneIndex, 0, 6);

		switch (getOption())
		{
		case 2:ShotToEntity = !ShotToEntity; break;
		case 9:
			if (ShotToEntity)
			{
				if (PedList[PedSelectedIndex] != Selected)
				{
					Bone = ENTITY::_GET_ENTITY_BONE_INDEX(Selected, BoneList[BoneIndex]);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(PedList[PedSelectedIndex], Selected, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
				}
				else
				{
					NotifyDown("エラーが発生したため、アタッチ出来ませんでした。", 1000);
				}
			}
			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(PedList[PedSelectedIndex], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
			}break;
		case 10:LoopAttach2 = !LoopAttach2; break;
		}
		break;

#pragma endregion

		#pragma region SpawnedVehicleList
	case SpawnedVehicleList:
		addTitle("スポーンした車のリスト");
		for (int i = 0; i < 20; i++)
		{
			addOption(UI::_0x95C4B5AD(SpawnedVehicleName[i]));
		}
		if (optionPress)
		{
			SelectedVehicle = currentOption - 1;
			changeSubmenu(EditVehicle);
		}
		break;

	case EditVehicle:
		addTitle(UI::_0x95C4B5AD(SpawnedVehicleName[SelectedVehicle]));
		addSubmenuOption("カラー変更", EditVehicle_Color);
		addSubmenuOption("移動 / 回転", EditVehicle_Move);
		addSubmenuOption("アタッチ", EditVehicle_Attach);
		addOption("位置固定");
		addOption("位置固定解除");
		addOption("判定有効化");
		addOption("判定無効化");
		addOption("削除");
		switch (getOption())
		{
		case 4:ToggleFreezeEntity(SpawnedVehicleCode[SelectedVehicle], 1); break;
		case 5:ToggleFreezeEntity(SpawnedVehicleCode[SelectedVehicle], 0); break;
		case 6:ToggleCollisionEntity(SpawnedVehicleCode[SelectedVehicle], true); break;
		case 7:ToggleCollisionEntity(SpawnedVehicleCode[SelectedVehicle], false); break;
		case 8:DeleteEntity(SpawnedVehicleCode[SelectedVehicle]); SpawnedVehicleCode[SelectedVehicle] = 0; break;
		}
		break;

	case EditVehicle_Color:
		addTitle("カラー変更");
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.1300f, 0.1000f, ColorR, ColorG, ColorB, 255);
		drawText("<カラーレビュー>", 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true, false);
		addTitle("車のカラー");
		addIntOption("<赤>", &ColorR, 0, 255, false, NULL, true);
		addIntOption("<緑>", &ColorG, 0, 255, false, NULL, true);
		addIntOption("<青>", &ColorB, 0, 255, false, NULL, true);
		addOption("赤色");
		addOption("緑色");
		addOption("青色");
		addOption("水色");
		addOption("黄色");
		addOption("ピンク色");
		addCheckBool("メインカラー(Loop)", EditVehicle_Main_[SelectedVehicle]);
		addCheckBool("サブカラー(Loop)", EditVehicle_Sub_[SelectedVehicle]);
		addCheckBool("スモークカラー(Loop)", EditVehicle_Smoke_[SelectedVehicle]);
		addOption("クローム化");
		addOption("クローム解除");
		switch (getOption())
		{
		case 10:EditVehicle_Main_[SelectedVehicle] = !EditVehicle_Main_[SelectedVehicle]; break;
		case 11:EditVehicle_Sub_[SelectedVehicle] = !EditVehicle_Sub_[SelectedVehicle]; break;
		case 12:EditVehicle_Smoke_[SelectedVehicle] = !EditVehicle_Smoke_[SelectedVehicle]; break;
		case 13:chromevehicle(SpawnedVehicleCode[SelectedVehicle], true); break;
		case 14:chromevehicle(SpawnedVehicleCode[SelectedVehicle], false); break;
		}
		break;

	case EditVehicle_Move:
		addTitle("移動 / 回転");
		addFloatOption("移動速度", &Movement, 0.1, 10, true, 0.01, "オブジェクトが移動する速度を設定します。");
		addFloatCoord("座標<X軸>", SpawnedVehicleCode[SelectedVehicle], X, Movement, true);
		addFloatCoord("座標<Y軸>", SpawnedVehicleCode[SelectedVehicle], Y, Movement, true);
		addFloatCoord("座標<Z軸>", SpawnedVehicleCode[SelectedVehicle], Z, Movement, true);
		addFloatRotation("回転<X軸>", SpawnedVehicleCode[SelectedVehicle], X, Movement, true);
		addFloatRotation("回転<Y軸>", SpawnedVehicleCode[SelectedVehicle], Y, Movement, true);
		addFloatRotation("回転<Z軸>", SpawnedVehicleCode[SelectedVehicle], Z, Movement, true);
		addOption("回転リセット", "回転<>で動かしたオブジェクトを初期化");

		switch (getOption())
		{
		case 8:ENTITY::SET_ENTITY_ROTATION(SpawnedVehicleCode[SelectedVehicle], 0, 0, 0, 0, 0); break;
		}
		break;

	case EditVehicle_Attach:
		addTitle("アタッチ");
		addFloatOption("移動速度", &Movement, 0.1, 10, true, 0.1, "オブジェクトが移動する速度を設定します。");
		addFloatOption("座標X軸", &AttachLoc.x, -10, 10, true, Movement);
		addFloatOption("座標Y軸", &AttachLoc.y, -10, 10, true, Movement);
		addFloatOption("座標Z軸", &AttachLoc.z, -10, 10, true, Movement);
		addFloatOption("回転X軸", &AttachRot.x, 0, 360, true, Movement);
		addFloatOption("回転Y軸", &AttachRot.y, 0, 360, true, Movement);
		addFloatOption("回転Z軸", &AttachRot.z, 0, 360, true, Movement);
		addOption("アタッチ", "自分が乗っている車にアタッチ");
		addCheckBool("アタッチ(ループ)", AttachFlag[SelectedVehicle]);
		addCharSwap("アタッチ先", BoneList, &BoneIndex, 0, 6);
		switch (getOption())
		{
		case 8:
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			RequestNetworkControl(vehicle);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
			Bone = ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, BoneList[BoneIndex]);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedVehicleCode[SelectedVehicle], vehicle, Bone, AttachLoc.x, AttachLoc.y, AttachLoc.z, AttachRot.x, AttachRot.y, AttachRot.z, true, true, true, true, true, true);
			break;
		case 9:
			AttachFlag[SelectedVehicle] = !AttachFlag[SelectedVehicle];
			//LoopAttach3 = !LoopAttach3; 
			break;
		}
		break;
#pragma endregion

		#pragma region AllActiveButtons
	case AllActiveButtons:
		addTitle("一括有効化");
		addOption("プロテクション有効化", "全部ONにします。");
		addOption("プロテクション無効化", "全部OFFにします。");
		addOption("セルフオプション有効化", "全部ONにします。");
		addOption("セルフオプション無効化", "全部OFFにします。");
		switch (getOption())
		{
		
		case 1:ProtectionAllApply(true); break;
		case 2:ProtectionAllApply(false); break;
		case 3:SelfOptionAllApply(true); break;
		case 4:SelfOptionAllApply(true); break;
		
		}
		break;
#pragma endregion

		#pragma region Protections
	case Protections:
		addTitle("プロテクション");
		addCheckBool("~r~エフェクト ~b~保護", PTFX);
		addCheckBool("~r~テレポート/アニメーション ~b~保護", TaskP);
		addCheckBool("~r~クリアタスク ~b~保護", Ctask);
		addCheckBool("車両操作 ~b~保護", VehiP);
		addCheckBool("武器 |没収 配布| ~b~保護", Remvp);
		addCheckBool("クリアエリア ~b~軽量化", ClearAreaAll);
		addCheckBool("車両アタッチ ~b~保護", VehicleAttachProtect);
		addCheckBool("~r~スクリプト ~b~保護", RPprotection);
		addCheckBool("スクリプト ~b~感知", ScriptDetect);
		addCheckBool("~r~ステータス変更 ~b~保護", ChangeStatsProtection);
		addCheckBool("~r~アドミンキック ~b~保護", admink);
		addCheckBool("投票キック ~b~保護", Kickvote);
		addCheckBool("ホストキック ~b~保護", hostkick);
		addCheckBool("天候変更 ~b~保護", wetherChangepro);
		addOption("~b~個別~w~プロテクション");
		//addCheckBool("apartmentdelete", apartmentdelete);
		switch (getOption())
		{
		case 1:PTFX = !PTFX; PTFXs(PTFX); break;
		case 2:TaskP = !TaskP; Tasks(TaskP); break;
		case 3:Ctask = !Ctask; CTask(Ctask); break;
		case 4:VehiP = !VehiP; Vehip(VehiP); break;
		case 5:Remvp = !Remvp; RemvP(Remvp); break;
		case 6:ClearAreaAll = !ClearAreaAll; break;
		case 7:VehicleAttachProtect = !VehicleAttachProtect; break;
		case 8:RPprotection = !RPprotection; RPprotection2(RPprotection, true); break;
		case 9:ScriptDetect = !ScriptDetect; break;
		case 10:ChangeStatsProtection = !ChangeStatsProtection;
			if (ChangeStatsProtection)
			{
				PS3::WriteBytes(NETWORK_INCREMENT_STAT_EVENT, ON, 4);
			}
			else
			{
				PS3::WriteBytes(NETWORK_INCREMENT_STAT_EVENT, OFF, 4);
			}
			break;
		case 11:admink = !admink;  Adminvoid1(admink); break;
		case 12: Kickvote = !Kickvote; KickVote(Kickvote); break;
		case 13: hostkick = !hostkick; HostKick(hostkick); break;
		case 14: wetherChangepro = !wetherChangepro; WeatherPro(wetherChangepro); break;
		case 15: changeSubmenu(kobetuprotections); break;
		//case 14: apartmentdelete = !apartmentdelete; break;
		}break;

		case kobetuprotections:
			addTitle("~b~個別~w~プロテクション");
			addCheckBool("~b~オール ~r~保護", EntiBlock);
			addCheckBool("~b~エンティティ ~r~保護", Blockallentities1);
			addCheckBool("~b~ピックアップ ~r~保護", PickupsBlock1);
			addCheckBool("~b~飛行機 ~r~保護", PlanesBlock1);
			addCheckBool("~b~オブジェクト ~r~保護", ObjectBlock1);
			addCheckBool("~b~バイク ~r~保護", BikesBlock1);
			addCheckBool("~b~車両 ~r~保護", CarsBlock1);
			addCheckBool("~b~ヘリ ~r~保護", HelicoptersBlock1);
			addCheckBool("~b~ペッド ~r~保護", CloneBlock1);
			addCheckBool("~b~ボート ~r~保護", BoatBlock1);
			addCheckBool("~b~トレイラー ~r~保護", TralerBlock1);
			addCheckBool("~b~ヘリ ~r~完全削除", HeliP, "ヘリフライングカーを防ぎます");
			addCheckBool("~b~飛行機 ~r~完全削除", FrezP, "ヘリフライングカーを防ぎます");
			addCheckBool("~b~全車両モデル ~r~完全削除", AllP, "ヘリフライングカーを防ぎます");
			addCheckBool("~b~パラダイス ~r~ブロック", ParadiseProtect);
			addCheckBool("~b~情報取得 ~w~& ~r~SAVE", PSIDsaveloop,"悪質プレイヤーを保存");
			//addCheckBool("All EVENT", ALLEVENT);
			/*addCheckBool("オールテスト", AllTest);
			addCheckBool("アパート削除", apartmentdelete);
			addCheckBool("POLICEdelete", POLICEdelete);*/
			//addCheckBool("フライングカー感知", FryingCarKANTI);
			switch (getOption())// AnimationName
			{
			case 1: EntiBlock = !EntiBlock; entityBlocker(EntiBlock); PlanesBlock1 = false;  Blockallentities1 = false; 
				PickupsBlock1 = false;  ObjectBlock1 = false;  BikesBlock1 = false;  CarsBlock1 = false;  
				HelicoptersBlock1 = false;  CloneBlock1 = false; BoatBlock1 = false;  TralerBlock1 = false; break;
			case 2:if (!EntiBlock)
			{
				Blockallentities1 = !Blockallentities1; Blockallentities(Blockallentities1);
			}break;
			case 3:if (!EntiBlock)
			{
				PickupsBlock1 = !PickupsBlock1; PickupsBlock(PickupsBlock1);
			}break;
			case 4:if (!EntiBlock) { PlanesBlock1 = !PlanesBlock1; PlanesBlock(PlanesBlock1); } break;
			case 5:if (!EntiBlock) { ObjectBlock1 = !ObjectBlock1; ObjectBlock(ObjectBlock1); } break;
			case 6:if (!EntiBlock) { BikesBlock1 = !BikesBlock1; BikesBlock(BikesBlock1); } break;
			case 7:if (!EntiBlock) { CarsBlock1 = !CarsBlock1; CarsBlock(CarsBlock1); } break;
			case 8:if (!EntiBlock) { HelicoptersBlock1 = !HelicoptersBlock1; HelicoptersBlock(HelicoptersBlock1); } break;
			case 9: if (!EntiBlock) { CloneBlock1 = !CloneBlock1; CloneBlock(CloneBlock1); } break;
			case 10:if (!EntiBlock) { BoatBlock1 = !BoatBlock1; BoatBlock(BoatBlock1); } break;
			case 11: if (!EntiBlock) { TralerBlock1 = !TralerBlock1; TralerBlock(TralerBlock1); } break;
			case 12: HeliP = !HeliP; Helipaaa(HeliP); break;
			case 13:FrezP = !FrezP; Frezpaaa(FrezP); break;
			case 14: AllP = !AllP; Allpaaa(AllP); break;
			case 15: ParadiseProtect = !ParadiseProtect; break;
			case 16: PSIDsaveloop = !PSIDsaveloop; break;
			//case 15: ALLEVENT = !ALLEVENT; AllEvent(ALLEVENT); break;
			/*case 15: AllTest = !AllTest; break;
			case 16: apartmentdelete = !apartmentdelete; break;
			case 17: POLICEdelete = !POLICEdelete; break;*/
			//case 15: FryingCarKANTI = !FryingCarKANTI; break;
			}
			break;
#pragma endregion

		#pragma region Animations
	case Animations:
		addTitle("アニメーション");
		addOption("アニメーション停止");
		addIntOption("ダンス系", &AnimaType, 0, 4, true, "", false);
		addIntOption("動物系", &AnimaTypeA, 0, 4, true, "", false);
		addIntOption("スポーツ系", &AnimaTypeS, 0, 4, true, "", false);
		addIntOption("Sex系", &AnimaTypeN, 0, 4, true, "", false);
		addIntOption("その他1", &AnimaTypeM, 0, 4, true, "", false);
		addIntOption("その他2", &AnimaTypeO, 0, 19, true, "", false);
		addCheckBool("上半身アニメーション", isUpperAnim, "上半身のみアニメーション");
		switch (getOption())// AnimationName
		{
		case 1:Freeze(PLAYER::PLAYER_PED_ID()); break;
		case 2:Animations2[0] = AnimaMenu2[AnimaType]; Animations2[1] = Animahsh[AnimaType]; SetPlayerAnimationForMe = true; break;
		case 3:Animations2[0] = AnimaMenu2A[AnimaTypeA]; Animations2[1] = AnimahshA[AnimaTypeA]; SetPlayerAnimationForMe = true; break;
		case 4:Animations2[0] = AnimaMenu2S[AnimaTypeS]; Animations2[1] = AnimahshS[AnimaTypeS]; SetPlayerAnimationForMe = true; break;
		case 5:Animations2[0] = AnimaMenu2N[AnimaTypeN]; Animations2[1] = AnimahshN[AnimaTypeN]; SetPlayerAnimationForMe = true; break;
		case 6:Animations2[0] = AnimaMenu2M[AnimaTypeM]; Animations2[1] = AnimahshM[AnimaTypeM]; SetPlayerAnimationForMe = true; break;
		case 7:Animations2[0] = AnimaMenu2O[AnimaTypeO]; Animations2[1] = AnimahshO[AnimaTypeO]; SetPlayerAnimationForMe = true; break;
		case 8:isUpperAnim = !isUpperAnim; break;
		}
		break;
#pragma endregion

		#pragma region FunMenu
	case FunMenu:
		addCheckBool("アイアンマンMOD", Psychokinetic_anim, "アイアンマン");
		addCheckBool("アイアンマンMOD ESP", testESP);
		addCheckBool("ハルクMOD", HulkMod);
		addCheckBool("ドラゴンファイア", DragonFireTrue);
		addCheckBool("UCAV Mod", UCAV);
		addCheckBool("パラシュートMOD", ParachuteMOD);
		addCheckBool("マインクラフト", MinecraftMode);	
		//addCheckBool("インファマス MOD", infamousMOD, "");
		addCheckBool("海水無効", WaterisntHere, "Ver 1.8より使えるようになりました");
		addCheckBool("スピードメーター", SpeedMeter);
		addCheckBool("ほふく前進 (テスト)", ProneMod, "");
		//addCheckBool("Psychokinetic MOD", IronmanV2, "");
		addOption("ホミラン パラシュート");
		addCheckBool("車両ぴょん飛び", BAIKUKUU);
		addCheckBool("エンティティ表示", EntityEPS);
		switch (getOption())
		{
		case 1:
			if (ENTITY::IS_ENTITY_ATTACHED(PLAYER::PLAYER_PED_ID()))
			{
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), 0, 0);
			}
			EGG = 0; Psychokinetic_anim = !Psychokinetic_anim; 
			if (!Psychokinetic_anim)
			{
				Entity unko = EGG;
				Freeze(PLAYER::PLAYER_PED_ID());
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), 0, 0);
				ENTITY::DELETE_ENTITY(&unko);
				Psychokinetic = false;
			}
			break;
		case 2:testESP = !testESP; break;
		case 3:HulkMod = !HulkMod; break;
		case 4:DragonFireTrue = !DragonFireTrue; DeleteAllDragonFire();/*DragonFireEnable = true;*/ break;
		case 5:
			if (UCAV)
			{
				NotifyDown("UCAV Off", 1000);
				DeleteCam();
				DeleteCam2();
				DeleteIMissile();
				Predator_ON2 = false;
				UCAV = false;
			}
			else
			{
				PreMissile2 = 0;
				FakeMissileOb = 0;
				PreCamera = 0;
				PreCamera2 = 0;
				DeleteCam();
				DeleteCam2();
				NotifyDown("UCAV On", 1000);
				UCAV = true;
			}
			break;
		case 6:ParachuteMOD = !ParachuteMOD; ChangeAmmo(); break;
		case 7:MinecraftMode = !MinecraftMode; break;
		//case 8:infamousMOD = !infamousMOD; break;
		case 8:
			WaterisntHere = !WaterisntHere;
			WaterEditer();
			break;
		case 9:SpeedMeter = !SpeedMeter; break;
		case 10:ProneMod = !ProneMod; SneakMode(ProneMod); break;
	/*	case 12: 
			IronmanV2 = !IronmanV2; 
			Ironman::isFlying = false;
			Ironman::MovementFlag = WalkingIronman;
			Ironman::AttackFlag = NoneIronman;
			break;*/
		case 11:
			SetWeaponFlag(GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_HOMINGLAUNCHER")));
			break;
		case 12: BAIKUKUU = !BAIKUKUU; break;
		case 13: EntityEPS = !EntityEPS; break;
		}
		break;
#pragma endregion

		#pragma region Teleporter
	case Teleporter:
		Entity ent = PLAYER::PLAYER_PED_ID();
		addTitle("テレポート");
		addSubmenuOption("お気に入りスポット", FavoriteSpot);
		addSubmenuOption("お買い物", StoreSpot);
		addSubmenuOption("適当スポット", TekitouSpot);
		addOption("マーカーテレポート");
		addIntOption("カスタムテレポート : X座標", &CustomTelep.x, -5000, 5000, true, "", true);
		addIntOption("カスタムテレポート : Y座標", &CustomTelep.y, -5000, 5000, true, "", true);
		addIntOption("カスタムテレポート : Z座標", &CustomTelep.z, -5000, 5000, true, "", true);
		addOption("カスタムテレポート");
		addCheckBool("カメラアクション", Teleanim);
			//addOption("マーカーテレポートv2");
		switch (getOption())
		{
		case 4: TeleportWPLoop = true; break;
		case 5:MyConsoleTeleport(PLAYER::PLAYER_PED_ID(), CustomTelep.x, CustomTelep.y, CustomTelep.z); break;
		case 6:MyConsoleTeleport(PLAYER::PLAYER_PED_ID(), CustomTelep.x, CustomTelep.y, CustomTelep.z); break;
		case 7:MyConsoleTeleport(PLAYER::PLAYER_PED_ID(), CustomTelep.x, CustomTelep.y, CustomTelep.z); break;
		case 8:MyConsoleTeleport(PLAYER::PLAYER_PED_ID(), CustomTelep.x, CustomTelep.y, CustomTelep.z); break;
		case 9: Teleanim = !Teleanim; break;

		}
		break;

	case FavoriteSpot:
		addTitle("お気に入り");
		addOption("空港");
		addOption("40万アパート屋根");
		addOption("40Kアパートの近く");
		addOption("40Kガレージ前");
		addOption("FIBビル 上");
		addOption("FIBビル 中");
		addOption("チリアド山");
		addOption("メイズバンク");
		addOption("海の中のUFO");
		switch (getOption())
		{
		case 1:addteleportoption( -1102.2910, -2894.5160, 13.9467, ent); break;
		case 2:addteleportoption( -769.8004, 331.2076, 234.2694,ent); break;
		case 3:addteleportoption( -775.0500, 312.3200, 85.7000, ent); break;
		case 4:addteleportoption( -796, 300, 85, ent); break;
		case 5:addteleportoption( 137, -749, 257, ent); break;
		case 6:addteleportoption( 115, -745, 242, ent); break;
		case 7:addteleportoption( 495, 5586, 794, ent); break;
		case 8:addteleportoption( -75, -818, 326, ent); break;
		case 9:addteleportoption( 762, 7388, -110, ent); break;
		}
		break;

	case StoreSpot:
		addTitle("お買い物");
		addOption("服屋1");
		addOption("服屋2");
		addOption("服屋3");
		addOption("ロスカス");
		addOption("武器屋");
		addOption("マスク屋");
		switch (getOption())
		{
		case 1:addteleportoption( -723, -162, 36, ent); break;
		case 2:addteleportoption( -4, 6520, 30, ent); break;
		case 3:addteleportoption( -154, -306, 38, ent); break;
		case 4:addteleportoption( -375, -129, 38, ent); break;
		case 5:addteleportoption( 250, -48, 69, ent); break;
		case 6:addteleportoption( -1339, -1278, 4, ent); break;
		}
		break;

	case TekitouSpot:
		addTitle("適当スポット");
		addOption("ヒューメイン1");
		addOption("ヒューメイン2");
		addOption("トレバー空港");
		addOption("美容室");
		addOption("コンテナ ドリフト用");
		addOption("軍事基地");
		addOption("クレーンの上");
		addOption("工事ビルの上");
		switch (getOption())
		{
		case 1:addteleportoption( 3615, 3738, 28, ent); break;
		case 2:addteleportoption( 3525, 3709, 20, ent); break;
		case 3:addteleportoption( 1792, 3247, 42, ent); break;
		case 4:addteleportoption( -27, -138, 56, ent); break;
		case 5:addteleportoption( 978, -3061, 5, ent); break;
		case 6:addteleportoption( -2264, 3200, 32, ent); break;
		case 7:addteleportoption( -102, -967, 296, ent); break;
		case 8:addteleportoption( -146, -963, 269, ent); break;
		}
		break;
#pragma endregion

		#pragma region Self
	case Self_Options:
		addTitle("セルフオプション");
		addOption("歩行スタイル", "", ">>");
		addOption("ネームチェンジャー", "", ">>");
		addCheckBool("無敵", gmode);
		addCheckBool("透明", Invisible);
		addCheckBool("手配度無効", nocops);
		addCheckBool("スーパージャンプ", SuperJump);
		addCheckBool("スーパーラン", SuperRun);
		addCheckBool("ウルトラパンチ (Address)", superpunch, "");
		addCheckBool("爆発パンチ", Exmelee);
		addCheckBool("炎の弾", fireammo);
		addCheckBool("爆発する弾", Exammo);
		addCheckBool("レーダーにプレイヤーを表示", revealPeople);
		addCheckBool("レーダーから自身を消す", offradar);
		addCheckBool("警察が黙認", Copsturnblindeye);
		addOption("ブルシャーク");
		addFloatOption("プレイヤーのサイズ 調整", &PlayerHeightSize, 0, 10, true, 0.01f, "");
		addCheckBool("浮遊", NoClip);
	/*	addCheckBool("クラシックカメラ", GTA2CamTEST);
		addFloatOption("クラシックカメラ 高さ",&CAMHIGH, 0, 1000000,true,0.1f);
*/
		/*addCheckBool("GTA2 TEST", GTA2CamTEST);
		addFloatOption("GTA2 Float", &GTA2CamUNKO, 0, 100, true, 1, "");*/

		switch (getOption())
		{
		case 1: changeSubmenu(walkedit); break;
		case 2:changeSubmenu(NameChangerMenu); break;
	    case 3:gmode = !gmode; break; break;

		case 4:Invisible = !Invisible;  break;
		case 5:nocops = !nocops;
			if (!nocops)
			{
				NoCops(nocops);
			}break;
		case 6:SuperJump = !SuperJump; break;
		case 7:SuperRun = !SuperRun; 
			if (SuperRun) { 
				PLAYER::SuperRun(PLAYER::PLAYER_ID(), 1.49); 
			}
			else 
			{ 
				PLAYER::SuperRun(PLAYER::PLAYER_ID(), 1); 
			} break;
		case 8: superpunch = !superpunch; Super_Puch(superpunch);  break;
		case 9:Exmelee = !Exmelee; break;
		case 10:fireammo = !fireammo; break;
		case 11:Exammo = !Exammo; break;
		case 12:revealPeople = !revealPeople; RevealPeople(revealPeople); break;
		case 13:offradar = !offradar; OffRadar(offradar); break;
		case 14:Copsturnblindeye = !Copsturnblindeye; CopsturnBlindEye(Copsturnblindeye); break;
		case 15:PS3::WriteInt32(PS3::ReadInt32(0x1E70394) + 0x24C18, 5); break;
		case 16:PlayerHeightBool = !PlayerHeightBool; break;
		case 17: NoClip = !NoClip; NoClipSetup(NoClip); break;
		//case 18: GTA2CamTEST = !GTA2CamTEST; break;

		}
		break;
#pragma endregion

		#pragma region Name Changer
	case NameChangerMenu:
		addTitle("あとで追加します");
		addNameOption("Phantom");
		addNameOption("Rockstar DEV");
		addNameOption("SPRX");
		addKeyboardOption("名前変更", 3, "", 100);
		addKeyboardOption("クルータグ変更", 4, "", 100);
		switch (getOption())
		{
		}
		break;
#pragma endregion

		#pragma region AllPlayer
	case AllPlayer:
		addTitle("オールプレイヤー");
		addCheckBool("40Kドロップ", allplayer40k);
		addOption("アニメーション削除");
		addOption("全員を自分の元へ");
		addCheckBool("全員の手配度削除(Loop)", DeleteAllWantedLevels, "オンの間セッション全員の手配度を永遠に消し続けます");
		//addOption("全員を自分へアタッチ");
		addCharSwap("全員の天候変更", CHANGEMenu, &CHANGEType, 0, 12, "");
		addCharSwap("ランクアップ", RPListChar, &RPListVar, 0, 7);
		addCharSwap("ランクダウン", RPListChar_, &RPListVar, 0, 7);
		addOption("全員爆発");
		addCheckBool("オールESP", AllESP);

		switch (getOption())
		{
		case 1:allplayer40k = !allplayer40k; break;
		case 2:
			for (int i = 0; i < 16; i++)
			{
				Freeze(PLAYER::GET_PLAYER_PED(i));
			}break;
		case 3:AllTeleportToMe(); break;
		case 4:DeleteAllWantedLevels = !DeleteAllWantedLevels; break;
		case 5:ChangeAllPlayerChange(); break;
		case 6:
			for (int i = 0; i < 16; i++)
			{
				if (i != PLAYER::PLAYER_ID())
				{
					GiveRP(i, RPList[RPListVar] * -1);
				}
			}break;
		case 7:
			for (int i = 0; i < 16; i++)
			{
				if (i != PLAYER::PLAYER_ID())
				{
					GiveRP(i, RPList_[RPListVar] * -1);
				}
			}break;
		case 8: for (int i = 0; i < 16; i++)
		{
			if (i != PLAYER::PLAYER_ID())
			{
				Vector3 Pos1 = get_entity_coords_orig(i, true);
				FIRE::ADD_EXPLOSION(Pos1.x, Pos1.y, Pos1.z, 29, 0.5f, true, false, 5.0f);
			}
		}break;
			//case 4:AttachAllToMe = true; break;
		case 9:AllESP = !AllESP;
			break;
		}
		break;
#pragma endregion

#pragma region rearIndicatorCoronaEditor
	/*case rearIndicatorCoronaEditor:
		addTitle("rearIndicatorCoronaEditor");
		Indexed = 2;
		addIntOption("Red", &RedColor[Indexed], 0, 255, true, "", true);
		addIntOption("Green", &GreenColor[Indexed], 0, 255, true, "", true);
		addIntOption("Blue", &BlueColor[Indexed], 0, 255, true, "", true);

		addIntOption("rearIndicatorCorona_size", &intensity[Indexed], 0, 10000, true, "", true);
		addIntOption("rearIndicatorCorona_size_far", &Corona_size[Indexed], 0, 10000, true, "", true);
		addIntOption("rearIndicatorCorona_intensity", &Corona_size_far[Indexed], 0, 10000, true, "", true);
		addIntOption("rearIndicatorCorona_intensity_far", &intensity_far[Indexed], 0, 10000, true, "", true);	
		addIntOption("rearIndicatorCorona_zBias", &zBias[Indexed], 0, 10000, true, "", true);
		addIntOption("rearIndicatorCorona_xRotation", &_xRotation[Indexed], 0, 359, true, "", true);
		addIntOption("rearIndicatorCorona_yRotation", &_yRotation[Indexed], 0, 359, true, "", true);
		addIntOption("rearIndicatorCorona_zRotation", &_zRotation[Indexed], 0, 359, true, "", true);

		WriteByteLight(rearIndicatorCorona_Red, (char)RedColor[Indexed]);
		WriteByteLight(rearIndicatorCorona_Green, (char)GreenColor[Indexed]);
		WriteByteLight(rearIndicatorCorona_Blue, (char)BlueColor[Indexed]);

		WriteFloatLight(rearIndicatorCorona_size, intensity[Indexed]);
		WriteFloatLight(rearIndicatorCorona_size_far, Corona_size[Indexed]);
		WriteFloatLight(rearIndicatorCorona_intensity, Corona_size_far[Indexed]);
		WriteFloatLight(rearIndicatorCorona_intensity_far, intensity_far[Indexed]);
		WriteFloatLight(rearIndicatorCorona_zBias, zBias[Indexed]);
		WriteFloatLight(rearIndicatorCorona_xRotation, _xRotation[Indexed]);
		WriteFloatLight(rearIndicatorCorona_yRotation, _yRotation[Indexed]);
		WriteFloatLight(rearIndicatorCorona_zRotation, _zRotation[Indexed]);

		break;*/
#pragma endregion
		
#pragma region tailLightEditor
//	case tailLightEditor:
//		addTitle("テールランプ~r~変更");
//		Indexed = 4;
//		addIntOption("テールランプ ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("テールランプ ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("テールランプ ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("テールランプ 光の強さ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("テールランプ 照らす距離", &falloffMax[Indexed], 0, 10000, true, "", true);
//		addIntOption("テールランプ 照らす距離2", &falloffExponent[Indexed], 0, 10000, true, "", true);
//		addIntOption("テールランプ 薄さ", &innerConeAngle[Indexed], 0, 10000, true, "", true);
//		addIntOption("テールランプ 照らす範囲", &outerConeAngle[Indexed], 0, 10000, true, "", true);
//
//		WriteFloatLight(tailLight_intensity, SYSTEM::TO_FLOAT(intensity[Indexed]));
//		WriteFloatLight(tailLight_falloffMax, SYSTEM::TO_FLOAT(falloffMax[Indexed]));
//		WriteFloatLight(tailLight_falloffExponent, SYSTEM::TO_FLOAT(falloffExponent[Indexed]));
//		WriteFloatLight(tailLight_innerConeAngle, SYSTEM::TO_FLOAT(innerConeAngle[Indexed]));
//		WriteFloatLight(tailLight_outerConeAngle, SYSTEM::TO_FLOAT(outerConeAngle[Indexed]));
//
//		WriteByteLight(tailLight_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(tailLight_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(tailLight_colorvalueBlue, (char)BlueColor[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region reversingLightCoronaEditor
//	case reversingLightCoronaEditor:
//		addTitle("バックライト~b~光輪");
//		Indexed = 9;
//		addIntOption("光輪 ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("光輪 サイズ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 サイズ2", &Corona_size[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ", &Corona_size_far[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ2", &intensity_far[Indexed], 0, 10000, true, "", true);
//		//addIntOption("光輪 薄さ", &zBias[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 回転 x", &_xRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 y", &_yRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 z", &_zRotation[Indexed], 0, 359, true, "", true);
//
//
//		WriteByteLight(reversingLightCorona_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(reversingLightCorona_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(reversingLightCorona_colorvalueBlue, (char)BlueColor[Indexed]);
//
//		WriteFloatLight(frontIndicatorCorona_size, intensity[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_size_far, Corona_size[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_intensity, Corona_size_far[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_intensity_far, intensity_far[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_zBias, zBias[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_xRotation, _xRotation[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_yRotation, _yRotation[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_zRotation, _zRotation[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region frontIndicatorCoronaEditor
//	/*case frontIndicatorCoronaEditor:
//		addTitle("frontIndicatorCoronaEditor");
//		Indexed = 3;
//		addIntOption("Red", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("Green", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("Blue", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("frontIndicatorCorona_size", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("frontIndicatorCorona_size_far", &Corona_size[Indexed], 0, 10000, true, "", true);
//		addIntOption("frontIndicatorCorona_intensity", &Corona_size_far[Indexed], 0, 10000, true, "", true);
//		addIntOption("frontIndicatorCorona_intensity_far", &intensity_far[Indexed], 0, 10000, true, "", true);	
//		addIntOption("frontIndicatorCorona_zBias", &zBias[Indexed], 0, 10000, true, "", true);
//		addIntOption("frontIndicatorCorona_xRotation", &_xRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("frontIndicatorCorona_yRotation", &_yRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("frontIndicatorCorona_zRotation", &_zRotation[Indexed], 0, 359, true, "", true);
//
//		WriteByteLight(frontIndicatorCorona_Red, (char)RedColor[Indexed]);
//		WriteByteLight(frontIndicatorCorona_Green, (char)GreenColor[Indexed]);
//		WriteByteLight(frontIndicatorCorona_Blue, (char)BlueColor[Indexed]);
//
//		WriteFloatLight(frontIndicatorCorona_size, intensity[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_size_far, Corona_size[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_intensity, Corona_size_far[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_intensity_far, intensity_far[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_zBias, zBias[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_xRotation, _xRotation[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_yRotation, _yRotation[Indexed]);
//		WriteFloatLight(frontIndicatorCorona_zRotation, _zRotation[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region indicatorEditor
//	case indicatorEditor:
//		Indexed = 1;
//		addTitle("indicatorEditor");
//		addIntOption("Red", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("Green", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("Blue", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("indicator_intensity", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("indicator_falloffMax", &falloffMax[Indexed], 0, 10000, true, "", true);
//		addIntOption("indicator_falloffExponent", &falloffExponent[Indexed], 0, 10000, true, "", true);
//		addIntOption("indicator_innerConeAngle", &innerConeAngle[Indexed], 0, 10000, true, "", true);
//		addIntOption("indicator_outerConeAngle", &outerConeAngle[Indexed], 0, 10000, true, "", true);
//
//		WriteFloatLight(indicator_intensity, SYSTEM::TO_FLOAT(intensity[Indexed]));
//		WriteFloatLight(indicator_falloffMax, SYSTEM::TO_FLOAT(falloffMax[Indexed]));
//		WriteFloatLight(indicator_falloffExponent, SYSTEM::TO_FLOAT(falloffExponent[Indexed]));
//		WriteFloatLight(indicator_innerConeAngle, SYSTEM::TO_FLOAT(innerConeAngle[Indexed]));
//		WriteFloatLight(indicator_outerConeAngle, SYSTEM::TO_FLOAT(outerConeAngle[Indexed]));
//
//		WriteByteLight(indicator_colorRed, (char)RedColor[Indexed]);
//		WriteByteLight(indicator_colorGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(indicator_colorBlue, (char)BlueColor[Indexed]);
//		break;
//#pragma endregion*/
//
//#pragma region reversingLightEditor
//	case reversingLightEditor:
//		addTitle("バックライト~r~変更");
//		Indexed = 8;
//
//		addIntOption("バックライト ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("バックライト ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("バックライト ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("バックライト 光の強さ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("バックライト 照らす距離", &falloffMax[Indexed], 0, 10000, true, "", true);
//		addIntOption("バックライト 照らす距離2", &falloffExponent[Indexed], 0, 10000, true, "", true);
//		addIntOption("バックライト 薄さ", &innerConeAngle[Indexed], 0, 10000, true, "", true);
//		addIntOption("バックライト 照らす範囲", &outerConeAngle[Indexed], 0, 10000, true, "", true);
//
//		WriteFloatLight(reversingLight_intensity, SYSTEM::TO_FLOAT(intensity[Indexed]));
//		WriteFloatLight(reversingLight_falloffMax, SYSTEM::TO_FLOAT(falloffMax[Indexed]));
//		WriteFloatLight(reversingLight_falloffExponent, SYSTEM::TO_FLOAT(falloffExponent[Indexed]));
//		WriteFloatLight(reversingLight_innerConeAngle, SYSTEM::TO_FLOAT(innerConeAngle[Indexed]));
//		WriteFloatLight(reversingLight_outerConeAngle, SYSTEM::TO_FLOAT(outerConeAngle[Indexed]));
//
//		WriteByteLight(reversingLight_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(reversingLight_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(reversingLight_colorvalueBlue, (char)BlueColor[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region headLightEditor
//	case headLightEditor:
//		addTitle("ヘッドライト~r~変更");
//		Indexed = 0;
//		
//		addIntOption("ヘッドライト ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("ヘッドライト ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("ヘッドライト ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("ヘッドライト 光の強さ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("ヘッドライト 照らす距離", &falloffMax[Indexed], 0, 2505, true, "", true);
//		addIntOption("ヘッドライト 照らす距離2", &falloffExponent[Indexed], 0, 10000, true, "", true);
//		addIntOption("ヘッドライト 薄さ", &innerConeAngle[Indexed], 0, 47, true, "", true);
//		addIntOption("ヘッドライト 照らす範囲", &outerConeAngle[Indexed], 0, 85, true, "", true);
//
//		WriteFloatLight(headLight_intensity, SYSTEM::TO_FLOAT(intensity[Indexed]));
//		WriteFloatLight(headLight_falloffMax, SYSTEM::TO_FLOAT(falloffMax[Indexed]));
//		WriteFloatLight(headLight_falloffExponent, SYSTEM::TO_FLOAT(falloffExponent[Indexed]));
//		WriteFloatLight(headLight_innerConeAngle, SYSTEM::TO_FLOAT(innerConeAngle[Indexed]));
//		WriteFloatLight(headLight_outerConeAngle, SYSTEM::TO_FLOAT(outerConeAngle[Indexed]));
//
//		WriteByteLight(headLight_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(headLight_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(headLight_colorvalueBlue, (char)BlueColor[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region headLightCoronaEditor
//	case headLightCoronaEditor:
//		addTitle("ヘッドライト~b~光輪");
//		Indexed = 7;
//		addIntOption("光輪 ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("光輪 サイズ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 サイズ2", &Corona_size[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ", &Corona_size_far[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ2", &intensity_far[Indexed], 0, 10000, true, "", true);
//		//addIntOption("headLightCorona_zBias", &zBias[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 回転 x", &_xRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 y", &_yRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 z", &_zRotation[Indexed], 0, 359, true, "", true);
//
//		WriteByteLight(headLightCorona_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(headLightCorona_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(headLightCorona_colorvalueBlue, (char)BlueColor[Indexed]);
//
//		WriteFloatLight(headLightCorona_size, intensity[Indexed]);
//		WriteFloatLight(headLightCorona_size_far, Corona_size[Indexed]);
//		WriteFloatLight(headLightCorona_intensity, Corona_size_far[Indexed]);
//		WriteFloatLight(headLightCorona_intensity_far, intensity_far[Indexed]);
//		WriteFloatLight(headLightCorona_zBias, zBias[Indexed]);
//		WriteFloatLight(headLightCorona_xRotation, _xRotation[Indexed]);
//		WriteFloatLight(headLightCorona_yRotation, _yRotation[Indexed]);
//		WriteFloatLight(headLightCorona_zRotation, _zRotation[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region tailLightMiddleCoronaEditor
//	case tailLightMiddleCoronaEditor:
//		addTitle("テールランプ~b~サブ光輪");
//		Indexed = 6;
//		addIntOption("光輪 ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("光輪 サイズ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 サイズ2", &Corona_size[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ", &Corona_size_far[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ2", &intensity_far[Indexed], 0, 10000, true, "", true);
//		//addIntOption("tailLightMiddleCorona_zBias", &zBias[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 回転 x", &_xRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 y", &_yRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 z", &_zRotation[Indexed], 0, 359, true, "", true);
//
//		WriteByteLight(tailLightMiddleCorona_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(tailLightMiddleCorona_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(tailLightMiddleCorona_colorvalueBlue, (char)BlueColor[Indexed]);
//
//		WriteFloatLight(tailLightCorona_size, intensity[Indexed]);
//		WriteFloatLight(tailLightCorona_size_far, Corona_size[Indexed]);
//		WriteFloatLight(tailLightCorona_intensity, Corona_size_far[Indexed]);
//		WriteFloatLight(tailLightCorona_intensity_far, intensity_far[Indexed]);
//		WriteFloatLight(tailLightCorona_zBias, zBias[Indexed]);
//		WriteFloatLight(tailLightCorona_xRotation, _xRotation[Indexed]);
//		WriteFloatLight(tailLightCorona_yRotation, _yRotation[Indexed]);
//		WriteFloatLight(tailLightCorona_zRotation, _zRotation[Indexed]);
//		break;
//#pragma endregion
//
//#pragma region tailLightCoronaEditor
//	case tailLightCoronaEditor:
//		addTitle("テールランプ~b~光輪");
//		Indexed = 5;
//		addIntOption("光輪 ~r~赤", &RedColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~g~緑", &GreenColor[Indexed], 0, 255, true, "", true);
//		addIntOption("光輪 ~b~青", &BlueColor[Indexed], 0, 255, true, "", true);
//
//		addIntOption("光輪 サイズ", &intensity[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 サイズ2", &Corona_size[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ", &Corona_size_far[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 薄さ2", &intensity_far[Indexed], 0, 10000, true, "", true);
//		//addIntOption("tailLightCorona_zBias", &zBias[Indexed], 0, 10000, true, "", true);
//		addIntOption("光輪 回転 x", &_xRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 y", &_yRotation[Indexed], 0, 359, true, "", true);
//		addIntOption("光輪 回転 z", &_zRotation[Indexed], 0, 359, true, "", true);
//
//		WriteByteLight(tailLightCorona_colorvalueRed, (char)RedColor[Indexed]);
//		WriteByteLight(tailLightCorona_colorvalueGreen, (char)GreenColor[Indexed]);
//		WriteByteLight(tailLightCorona_colorvalueBlue, (char)BlueColor[Indexed]);
//
//		WriteFloatLight(tailLightCorona_size, intensity[Indexed]);
//		WriteFloatLight(tailLightCorona_size_far, Corona_size[Indexed]);
//		WriteFloatLight(tailLightCorona_intensity, Corona_size_far[Indexed]);
//		WriteFloatLight(tailLightCorona_intensity_far, intensity_far[Indexed]);
//		WriteFloatLight(tailLightCorona_zBias, zBias[Indexed]);
//		WriteFloatLight(tailLightCorona_xRotation, _xRotation[Indexed]);
//		WriteFloatLight(tailLightCorona_yRotation, _yRotation[Indexed]);
//		WriteFloatLight(tailLightCorona_zRotation, _zRotation[Indexed]);
//		break;
//#pragma endregion
//
//		#pragma region AddressSearch
//	/*case AddressSearch:
//		addTitle("ゼノムウンコ");
//		addOption("Water Quad Address");
//		if (WaterQuad != 0)
//		{
//			addOption("Water Quad List", "", "+");
//			addOption("初期化");
//			addIntOption("All Opacity", &WaterOpacity, 0, 0xFF, true, "", true);
//			addFloatOption("WaterHeightVar", &WaterHeightVar, -20, 20, true, 0.1, "");
//			addCheckBool("AllQuadView", AllQuadView, "");
//		}
//		switch (getOption())
//		{
//		case 1:
//			if (!WaterQuadAddress)
//			{
//				WaterQuadAddress = true;
//			}
//			else
//			{
//				NotifyDown("処理中です", 1000);
//			}
//			break;
//
//		case 2:
//			changeSubmenu(AddressSearchList);
//			break;
//
//		case 3:
//			WaterQuad = 0;
//			WaterIndex = 0;
//			break;
//
//		case 4:
//			for (int i = 0; i < WaterQuadLength; i++)
//			{
//				PS3::WriteByte(WaterQuad + i * 0x1C + 0x08, (char)WaterOpacity);
//				PS3::WriteByte(WaterQuad + i * 0x1C + 0x09, (char)WaterOpacity);
//				PS3::WriteByte(WaterQuad + i * 0x1C + 0x0A, (char)WaterOpacity);
//				PS3::WriteByte(WaterQuad + i * 0x1C + 0x0B, (char)WaterOpacity);
//			}
//			break;
//
//		case 5:
//			for (int i = 0; i < WaterQuadLength; i++)
//			{
//				*(float*)(WaterQuad + i * 0x1C + 0x0014) = WaterHeightVar;
//				PS3::WriteByte(WaterQuad + i * 0x1C + 0x0015, 0xA0);
//			}
//			break;
//
//		case 6:
//			AllQuadView = !AllQuadView; break;
//		}
//		break;*/
//	case AddressSearch:
//		addTitle("HeadLight");
//		//addSubmenuOption("indicator", indicatorEditor, "");
//		addSubmenuOption("ヘッドライト~r~変更", headLightEditor, "");
//		addSubmenuOption("ヘッドライト~b~光輪", headLightCoronaEditor, "");
//		addSubmenuOption("テールランプ~r~変更", tailLightEditor, "");
//		addSubmenuOption("テールランプ~b~光輪", tailLightCoronaEditor, "");
//		addSubmenuOption("テールランプ~b~サブ光輪", tailLightMiddleCoronaEditor, "");
//		//addSubmenuOption("rearIndicatorCorona", rearIndicatorCoronaEditor, "");
//		addSubmenuOption("バックライト~r~変更", reversingLightEditor, "");
//		addSubmenuOption("バックライト~b~光輪", reversingLightCoronaEditor, "");
//		//addSubmenuOption("frontIndicatorCorona", frontIndicatorCoronaEditor, "");
//		
//		
//		switch (getOption())
//		{
//		
//		}
//		break;
#pragma endregion

	/*	#pragma region AddressSearchList
	case AddressSearchList:
		addTitle("ゼノムウンコ");
		for (int i = 0; i < WaterQuadLength; i++)
		{
			addOption(quadFormatStr(i), "", "+");
		}

		if (isPressed(Button_R1))
		{
			if (WaterQuadLength > currentOption + 10)
			{
				currentOption += 10;
			}
		}
		if (isPressed(Button_L1))
		{
			if (currentOption > 10)
			{
				currentOption -= 10;
			}
		}
		DrawViewName(currentOption - 1);
		DrawBoxWater(currentOption - 1);
		WaterQuadInfo(currentOption - 1);
		if (optionPress)
		{
			SelectedWaterQuad = currentOption - 1;
			GetWaterQuadData(SelectedWaterQuad);
			changeSubmenu(CurrentWaterEdit);
		}
		break;*/
#pragma endregion



		#pragma region VehicleSpawner
	case VehicleSpawner:
		addTitle("車をスポーン");
		addSubmenuOption("出す時の設定", VehicleSpawnOptions);
		addCarCharSwap("スーパー", SuperCar, &SuperCarVar, 0, 10);
		addCarCharSwap("スポーツ", sport, &sportVar, 0, 28);
		addCarCharSwap("クラシック", classic, &classicVar, 0, 19);
		addCarCharSwap("クラシックスポーツ", Muscle, &MuscleVar, 0, 11);
		addCarCharSwap("セダン", Sedan, &SedanVar, 0, 22);
		addCarCharSwap("クーペ", Coupes, &CoupeVar, 0, 9);
		addCarCharSwap("コンパクト", Compact, &CompactVar, 0, 7);
		addCarCharSwap("SUV", Suv, &SuvVar, 0, 27);
		//追加 Page2
		addCarCharSwap("トラック", Tracks, &TrackVar, 0, 18);
		addCarCharSwap("バン", Van, &VanVar, 0, 30);
		addCarCharSwap("警察車両", Emergency, &EmergencyVar, 0, 17);
		addCarCharSwap("サービス", Service, &ServiceVar, 0, 5);
		addCarCharSwap("ミリタリー", Military, &MilitaryVar, 0, 6);
		addCarCharSwap("バイク", Bike, &BikeVar, 0, 20);
		addCarCharSwap("自転車", Bicycle, &BicycleVar, 0, 6);
		addCarCharSwap("宣伝用", Commercial, &CommercialVar, 0, 38);
		addCarCharSwap("ヘリ", Helicopter, &HelicopterVar, 0, 13);
		addCarCharSwap("プレーン", Plane, &PlaneVar, 0, 18);
		addCarCharSwap("ボート", Boat, &BoatVar, 0, 13);
		addCarCharSwap("トレーラー", Trailers, &TrailersVar, 0, 26, false, true);
		//addSubmenuOption("MODDED車両", Funnys_vehicles);
		break;
#pragma endregion

	
		#pragma region VehicleSpawnOptions
	case VehicleSpawnOptions:
		addTitle("スポーン時の設定");
		addCheckBool("フルアップグレード", MaxUpgrades);
		addCheckBool("スポーン時に乗る", TeleAutomIncar);
		addCheckBool("無敵", spawnGodmode);
		addCheckBool("クローム", ChromeSpawn);
		addCheckBool("透明化", isinvisible);
		addCheckBool("スポーンアタッチ", isattach);
		addOption("スポーン or アタッチリスト +");
		addCheckBool("プレイヤーへスポーン", spawnplayer);
		addOption("車のカラー");
		addCheckBool("3色スモーク", threecolorsmoke);
		addCheckBool("スモークカラー(車のカラーと同じ)", smokecolortrue);
		addCheckBool("フェードイン", isFadeinSpawn, "");
		addCheckBool("無傷", CarGodCanBeDmg);
		switch (getOption())
		{
		case 1:
			MaxUpgrades = !MaxUpgrades;
			break;
		case 2:
			TeleAutomIncar = !TeleAutomIncar;
			break;
		case 3:
			spawnGodmode = !spawnGodmode;

			break;
		case 4:
			ChromeSpawn = !ChromeSpawn;
			break;
		case 5:isinvisible = !isinvisible; break;
		case 6:isattach = !isattach; spawnplayer = false; break;
		case 7:changeSubmenu(spawnattachlist); break;
		case 8:spawnplayer = !spawnplayer; isattach = false; break;
		case 9:changeSubmenu(VehicleSpawnColor); break;
		case 10:threecolorsmoke = !threecolorsmoke; smokecolortrue = false; break;
		case 11:smokecolortrue = !smokecolortrue; threecolorsmoke = false; break;
		case 12:isFadeinSpawn = !isFadeinSpawn; break;
		case 13:CarGodCanBeDmg = !CarGodCanBeDmg; break;
		}
		break;
#pragma endregion

#pragma region RocketShoot
	case RocketShoot:
		addTitle("ロケット発射");
		addCheckBool("緑レーザー(爆発)", Rocket_Player_Shoot[0]);
		addCheckBool("赤レーザー(爆発)", Rocket_Player_Shoot[1]);
		addCheckBool("戦車", Rocket_Player_Shoot[2]);
		addCheckBool("RPG", Rocket_Player_Shoot[3]);
		switch (getOption())
		{
		case 1:
			Rocket_Player_Shoot[0] = !Rocket_Player_Shoot[0];
			break;
		case 2:
			Rocket_Player_Shoot[1] = !Rocket_Player_Shoot[1];
			break;
		case 3:
			Rocket_Player_Shoot[2] = !Rocket_Player_Shoot[2];
			break;
		case 4:
			Rocket_Player_Shoot[3] = !Rocket_Player_Shoot[3];
			break;
		}
		break;
#pragma endregion

		#pragma region VehicleCheat
	case VehicleCheat:

		addTitle("改造 / チート");
		addOption("車のカラー改造", "", ">>");
		//addOption("ハンドリングエディター", "", ">>");
		addOption("ネオンメニュー", "", ">>");
		addOption("ロケット発射", "", ">>");
		addCheckBool("車無敵", IsGodModeVehicle);
		addCheckBool("レインボーカー", Slow_Rainbow_Loop);
		addCheckBool("レインボーカー(ばらばら)", RandomColorLoop);
		addCheckBool("車浮遊", vehflymode);
		addOption("車修復");
		addOption("MAXアップグレード");
		addCheckBool("ハイドロジャンプ", isHydroJump);
		addCheckBool("着地なしハイドロジャンプ", isHydroJump2);
		addFloatOption("ジャンプ力", &hydro, 1, 10, true, 0.1, "ハイドロジャンプのジャンプ力");
		addCheckBool("ドリフト", DRIFT);
		addCheckBool("L3 ブースト R3ストップ", VehicleBoostStop);
		addOption("(ヘリの)サーチライト~g~オン");
		addOption("(ヘリの)サーチライト~r~オフ");
		addCheckBool("壁走り", DriveONwall);
		
		addFloatOption("サスペ", &WheelSizePTR, -10, 10, true, 0.05, "");
		addFloatOption("ホイール", &WheelSizePTRWheel, -10, 10, true, 0.05, "");
		//addCheckBool("イコライザー MOD", EQMOD, "");
		addCheckBool("ネオン(白)", neonmodcar);
		addCheckBool("ネオン(青)", neonmodcar1);
		if (rightPress || leftPress || fastLeftPress || fastRightPress)
		{
			switch (currentOption)
			{
			case 18:
				setsuspensionheight(WheelSizePTR * -1);
				break;
			case 19 :
				setWheelSize(WheelSizePTRWheel);

				break;
			}
		}
		//	addOption("カーゴボブに磁石をつける", "");
		//VEHICLE::_SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		switch (getOption())
		{
		case 1:
			if (PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
			{
				isplayerme = PLAYER::PLAYER_PED_ID();
				changeSubmenu(VehicleColorCustomize);
			}
			break;
	/*	case 2:
			changeSubmenu(VehicleHandlingEditor);
			break;*/
		case 2: changeSubmenu(NeonMenu); break;
		case 3: changeSubmenu(RocketShoot); break;
		case 4:
			IsGodModeVehicle = !IsGodModeVehicle;
			for (int i = 0; i < 5; i++)
			{
				VehicleGodmode(true);
			}break;


		case 5:Slow_Rainbow_Loop = !Slow_Rainbow_Loop; break;
		case 6:RandomColorLoop = !RandomColorLoop; break;
		case 7:vehflymode = !vehflymode; break;
		case 8:CARFIX(); break;
		case 9:MaxUpgrade(); break;
		case 10:isHydroJump = !isHydroJump; isHydroJump2 = false; break;
		case 11:isHydroJump2 = !isHydroJump2; isHydroJump = false; break;
		case 13:DRIFT = !DRIFT;  break;
		case 14:VehicleBoostStop = !VehicleBoostStop; break;
		case 15:SearchLight(true); break;
		case 16:SearchLight(false); break;
		case 17:DriveONwall = !DriveONwall; break;

		//case 22:EQMOD = !EQMOD; break;
		case 20: neonmodcar = !neonmodcar;

			if (neonmodcar)
			{
				Start = true;
				END = false;

			}
			else
			{
				if (!END)
				{
					Start = false;
					RequestNetworkControl(NeonWhitelightCreat);
					RequestNetworkControl(NeonWhitelightCreat2);
					DeleteEntity(NeonWhitelightCreat2);
					DeleteEntity(NeonWhitelightCreat);
					Start2 = false;
					END = true;
				}
			}

			break;
		case 21: neonmodcar1 = !neonmodcar1;

			if (neonmodcar1)
			{
				Start1 = true;
				END1 = false;

			}
			else
			{
				if (!END1)
				{
					Start1 = false;
					RequestNetworkControl(NeonWhitelightCreat1);
					RequestNetworkControl(NeonWhitelightCreat3);
					RequestNetworkControl(NeonWhitelightCreat4);
					DeleteEntity(NeonWhitelightCreat4);
					DeleteEntity(NeonWhitelightCreat3);
					DeleteEntity(NeonWhitelightCreat1);
					Start3 = false;
					END1 = true;
				}
			}

			break;
		}
		break;

#pragma endregion

		#pragma region NeonMenu
	case NeonMenu:
		addTitle("ネオンメニュー");


		addCheckBool("ネオン 緑", Neongreen1);
		addCheckBool("ネオン 紫", Purple1);
		addCheckBool("ネオン 青", Blue1);
		addCheckBool("ネオン ピンク", Pink1);
		addCheckBool("ネオン 赤", Red1);
		addCheckBool("ネオン オレンジ", Orange1);
		addCheckBool("ネオン 黄色", Yallow1);
		addCheckBool("ネオン ランダム", rainbowneon);
		addCheckBool("ネオン~b~色~w~カスタム", neoncustum);
		addIntOption("ネオン : 赤", &Redneon, 0, 255, true, "", true);
		addIntOption("ネオン : 緑", &Greenneon, 0, 255, true, "", true);
		addIntOption("ネオン : 青", &Blueneon, 0, 255, true, "", true);
		switch (getOption())
		{
		case 1: Neongreen1 = !Neongreen1; Purple1 = false; Blue1 = false; Pink1 = false; Red1 = false; Orange1 = false; Yallow1 = false; rainbowneon = false; neoncustum = false; break;
		case 2: Purple1 = !Purple1; Neongreen1 = false; Blue1 = false; Pink1 = false; Red1 = false; break;
		case 3:	Blue1 = !Blue1; Neongreen1 = false; Purple1 = false; Pink1 = false; Pink1 = false; Red1 = false; Orange1 = false; Yallow1 = false; rainbowneon = false; neoncustum = false; break;
		case 4:	Pink1 = !Pink1; Neongreen1 = false; Purple1 = false; Blue1 = false; Red1 = false; Orange1 = false; Yallow1 = false; rainbowneon = false; neoncustum = false; break;
		case 5: Red1 = !Red1; Neongreen1 = false; Purple1 = false; Blue1 = false; Pink1 = false; Orange1 = false; Yallow1 = false; rainbowneon = false; neoncustum = false; break;
		case 6: Orange1 = !Orange1; Neongreen1 = false; Purple1 = false; Blue1 = false; Pink1 = false; Red1 = false; Yallow1 = false; rainbowneon = false; neoncustum = false; break;
		case 7:	Yallow1 = !Yallow1; Neongreen1 = false; Purple1 = false; Blue1 = false; Pink1 = false; Red1 = false; Orange1 = false; rainbowneon = false; neoncustum = false; break;
		case 8: rainbowneon = !rainbowneon; Neongreen1 = false; Purple1 = false; Blue1 = false; Pink1 = false; Red1 = false; Orange1 = false; Yallow1 = false; break;
		case 9: neoncustum = !neoncustum; Purple1 = false; Blue1 = false; Pink1 = false; Red1 = false; Orange1 = false; Yallow1 = false; Neongreen1 = false; break;
		}
		break;
#pragma endregion

		#pragma region Vehicle Handling Editor
	//case VehicleHandlingEditor:
	//	addTitle("ハンドリング");
	//	addOption(GettingQue);
	//	addOption("実行");
	//	addOption("今の車を表示");
	//	addOption("今の車をサーチ");
	//	addOption("ドリフト化");
	//	addFloatOption("サスペンション", &Suspension__, -30, 30, true, 0.05, "");
	//	addFloatOption("スピード変更", &Speed__, -30, 30, true, 0.05, "");
	//	addFloatOption("重量変更", &HeavyPer__, -1000000, 1000000, true, 10, "");
	//	addOption("ハンドリングv2", "", "+");
	//	if (isPressed(Dpad_Right) || isPressed(Dpad_Left))
	//	{
	//		if (MyCarAddress != 0)
	//		{
	//			switch (currentOption)
	//			{
	//			case 6:PS3::WriteFloat(MyCarAddress + 188u, Suspension__); break;
	//			case 7:PS3::WriteFloat(MyCarAddress + 116u, Speed__); break;
	//			case 8:PS3::WriteFloat(MyCarAddress + 4u, Speed__); break;
	//			}
	//		}
	//	}

	//	snprintf(KuronekoIsgomi, 40, "Address : 0x%8X", AddressHandling);
	//	drawText(KuronekoIsgomi, 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);

	//	snprintf(KuronekoIsgomi2, 40, "Address : 0x%8X", MyCarAddress);
	//	drawText(KuronekoIsgomi2, 0, 0.5, 0.6, 0.4, 0.4, 255, 255, 255, 255, true);
	//	switch (getOption())
	//	{
	//	case 2:IsGetFlag = true; break;
	//	case 3:
	//		char UNKOKuroneko[30];
	//		snprintf(UNKOKuroneko, 30, "0x%8X", ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())));
	//		NotifyDown(UNKOKuroneko);
	//		break;
	//	case 4:
	//		MycaraddressTarget = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
	//		Getter = true;
	//		break;

	//	case 5:
	//		PS3::WriteBytes(MyCarAddress + 4u, buffer, 100);
	//		break;

	//	case 9:
	//		changeSubmenu(VehicleHandlingEditorV2);
	//		break;
	//	}
	//	break;
#pragma endregion

		#pragma region VehicleHandlingEditorV2
	/*case VehicleHandlingEditorV2:
		addTitle("あああ");
		addOption(GettingQue2);
		addOption("実行");

		snprintf(KuronekoIsgomi, 40, "Address : 0x%8X", VehicleMetaHandling);
		drawText(KuronekoIsgomi, 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);

		snprintf(KuronekoIsgomi2, 40, "Car : %s", VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()))));
		drawText(KuronekoIsgomi2, 0, 0.5, 0.6, 0.4, 0.4, 255, 255, 255, 255, true);

		switch (getOption())
		{
		case 1: IsGetFlag2 = true; break;
		case 2: IsGetFlag2 = true; break;
		}
		break;*/
#pragma endregion

		#pragma region VehicleColorCustomize
	case VehicleColorCustomize:
		addTitle("カラー変更");
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.1300f, 0.1000f, ColorR, ColorG, ColorB, 255);
		drawText("<カラーレビュー>", 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);
		addIntOption("<赤>", &ColorR, 0, 255, false, NULL, true);
		addIntOption("<緑>", &ColorG, 0, 255, false, NULL, true);
		addIntOption("<青>", &ColorB, 0, 255, false, NULL, true);
		addOption("赤色");
		addOption("緑色");
		addOption("青色");
		addOption("水色");
		addOption("黄色");
		addOption("ピンク色");
		addCheckBool("メインカラーセット(Loop)", maincolor);
		addCheckBool("サブカラーセット(Loop)", subcolor);
		addCheckBool("スモークカラーセット(Loop)", smokecolor);
		addOption("クローム色~g~オン");
		addOption("クローム色~r~オフ");
		addOption("次世代型カラー選択");
		switch (getOption())
		{
		case 4:ColorR = 255; ColorG = 0; ColorB = 0;  break;
		case 5:ColorR = 0; ColorG = 255; ColorB = 0; break;
		case 6:ColorR = 0; ColorG = 0; ColorB = 255; break;
		case 7:ColorR = 46; ColorG = 254; ColorB = 247; break;
		case 8:ColorR = 255; ColorG = 255; ColorB = 0; break;
		case 9:ColorR = 254; ColorG = 46; ColorB = 200; break;
		case 10:maincolor = !maincolor; break;
		case 11:subcolor = !subcolor; break;
		case 12:smokecolor = !smokecolor; break;
		case 13:Chrome(true); break;
		case 14:Chrome(false); break;
		case 15:HyperDxColorSelect = true; break;
		}
		break;
#pragma endregion

		#pragma region spawnattachlist
		addTitle("選択してください。");
		for (int i = 0; i < 16; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			AttachSpawnPlayer = currentOption - 1;
			NotifyDown("選択しました。");
		}
#pragma endregion

		#pragma region VehicleSpawnColor
	case VehicleSpawnColor:
		addTitle("スポーン時の車のカラー");
		GRAPHICS::DRAW_RECT(0.5, 0.5, 0.1300f, 0.1000f, ColorR, ColorG, ColorB, 255);
		drawText("<カラーレビュー>", 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true, false);
		addIntOption("<赤>", &ColorR, 0, 255, false, NULL, true);
		addIntOption("<緑>", &ColorG, 0, 255, false, NULL, true);
		addIntOption("<青>", &ColorB, 0, 255, false, NULL, true);
		addOption("赤色");
		addOption("緑色");
		addOption("青色");
		addOption("水色");
		addOption("黄色");
		addOption("ピンク色");
		switch (getOption())
		{
		case 4:ColorR = 255; ColorG = 0; ColorB = 0;  break;
		case 5:ColorR = 0; ColorG = 255; ColorB = 0; break;
		case 6:ColorR = 0; ColorG = 0; ColorB = 255; break;
		case 7:ColorR = 46; ColorG = 254; ColorB = 247; break;
		case 8:ColorR = 255; ColorG = 255; ColorB = 0; break;
		case 9:ColorR = 254; ColorG = 46; ColorB = 200; break;
		}
		break;
#pragma endregion

		#pragma region WeaponEditor
	case WeaponEditor:
		addTitle("武器エディタ v2");
		addOption("全ての武器リスト", "GTA5内の武器の性能を変更", ">>");
		addOption("自分に武器を~g~与える");
		addOption("自分から武器を~r~奪う");
		//addCheckBool("テレポートガン", TeleporterGun, "");
		addCheckBool("デリートガン", DeleteGun, "");
		addCheckBool("弾無限(リロード有り)", infiniteammo);
		addCheckBool("弾無限(リロード無し)", UnlimitedAmmo1);
		addCheckBool("マネーガン", MoneygunPlayerFlag[PLAYER::PLAYER_ID()]);
		addCheckBool("テレポートガン", TeleportGunFlag[PLAYER::PLAYER_ID()], "");

		addCheckBool("車ショット", ShootVehicle);
		addCharSwap("車ショットの車", ShootVehicleChar, &SelectedShotVehicleVar, 0, 6, "", true);
		addCheckBool("ラピッドファイア", RapidFire);
		addCheckBool("武器を背中にやるやつ", PUBGMode);
		if (PUBGMode)
		{
			addFloatOption("座標調整 <X>", &PUBGSelect.Lx, -5, 5, true, 0.01, "");
			addFloatOption("座標調整 <Y>", &PUBGSelect.Ly, -5, 5, true, 0.01, "");
			addFloatOption("座標調整 <Z>", &PUBGSelect.Lz, -5, 5, true, 0.01, "");
			addFloatOption("向き調整 <X>", &PUBGSelect.Rx, 0, 360, true, 2, "");
			addFloatOption("向き調整 <Y>", &PUBGSelect.Ry, 0, 360, true, 2, "");
			addFloatOption("向き調整 <Z>", &PUBGSelect.Rz, 0, 360, true, 2, "");
		}
		switch (getOption())
		{
		case 1:changeSubmenu(AllWeaponList); break;
		case 2:
			for (int i = 0; i < 57; i++)
			{
				GiveWeaponPed(PLAYER::PLAYER_PED_ID(), WepArray[i], 528);
				BruteForceWeaponAddons(PLAYER::PLAYER_PED_ID(), WepArray[i], true);
			}
			break;
		case 3:
			WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), true);
			break;
			//case 1:TeleporterGun = !TeleporterGun; break;
		case 4:DeleteGun = !DeleteGun; break;
		case 5:infiniteammo = !infiniteammo; UnlimitedAmmo(); break;
		case 6:UnlimitedAmmo1 = !UnlimitedAmmo1; break;
		case 7:MoneygunPlayerFlag[PLAYER::PLAYER_ID()] = !MoneygunPlayerFlag[PLAYER::PLAYER_ID()]; break;
		case 8:TeleportGunFlag[PLAYER::PLAYER_ID()] = !TeleportGunFlag[PLAYER::PLAYER_ID()]; break;

		case 9:ShootVehicle = !ShootVehicle; break;
		case 11:RapidFire = !RapidFire; break;
		case 12:PUBGMode = !PUBGMode; break;
		}
		break;
#pragma endregion

		#pragma region AllWeaponList
	case AllWeaponList:
		addTitle("全ての武器リスト");
		for (int i = 0; i < 56; i++)
		{
			addOption(WEAPONJAPANESE[i]);
		}
		if (optionPress)
		{
			SelectedWeaponID = currentOption - 1;
			SelectedWeaponHash = GAMEPLAY::GET_HASH_KEY(WEAPONMENU[SelectedWeaponID]);
			SelectedWeaponOffset2 = GET_WEAPONS(SelectedWeaponHash);
			SelectedWeaponAmmoOffset = PS3::ReadInt32(SelectedWeaponOffset2 + AmmoInfo);
			SelectedWeaponAimingOffset = PS3::ReadInt32(SelectedWeaponOffset2 + AimingInfo);
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), SelectedWeaponHash, -1, true, true);
			SetWeaponFlag(SelectedWeaponOffset2);
			changeSubmenu(SelectedWeaponEditMenu);
		}
		break;
#pragma endregion

		#pragma region SelectedWeaponEditMenu
	case SelectedWeaponEditMenu:
		addTitle(WEAPONJAPANESE[SelectedWeaponID]);
		addOption("性能エディット", "", ">>");
		addOption("高速化");
		addOption("スナイパーカメラセット");
		addOption("モデルセット", "", ">>");
		addOption("武器の弾を変更", "", ">>");
		switch (getOption())
		{
		case 1:changeSubmenu(WeaponStatEditor); break;
		case 2:HighSpeedStungun(SelectedWeaponOffset2); break;
		case 3:SniperCameraSet(SelectedWeaponOffset2); break;
		case 4:changeSubmenu(WeaponModelEditor); break;
		case 5:changeSubmenu(WeaponStatAmmoEditor); break;
		}
		break;
#pragma endregion

		#pragma region WeaponStatEditor
	case WeaponStatEditor:
		addTitle("性能エディット");
		/*addFloatOption("ダメージ", &*(float*)(AllWeaponLists::SelectedWeaponOffset2 + Force), 0, 10000000, true, 100, "");
		addFloatOption("発射スピード", &*(float*)(AllWeaponLists::SelectedWeaponOffset2 + LaunchSpeed), 0, 10000000, true, 100, "");
		addFloatOption("ロックオン", &*(float*)(AllWeaponLists::SelectedWeaponOffset2 + LockOnRange), 0, 10000000, true, 100, "");
		addFloatOption("射程", &*(float*)(AllWeaponLists::SelectedWeaponOffset2 + WeaponRange), 0, 10000000, true, 100, "");
		addFloatOption("ノックバック", &*(float*)(AllWeaponLists::SelectedWeaponOffset2 + ForceHitVehicle), 0, 10000000, true, 100, "");*/
		addIntOption("ダメージ", &Damage2, 0, 10000000, true);
		addIntOption("発射スピード", &Launch, 0, 10000000, true);
		addIntOption("ノックバック", &Diffusion, 0, 10000000, true);
		if (rightPress || leftPress || fastLeftPress || fastRightPress)
		{
			SelectedWeaponHash = GAMEPLAY::GET_HASH_KEY(WEAPONMENU[SelectedWeaponID]);
			SelectedWeaponOffset2 = GET_WEAPONS(SelectedWeaponHash);
			SelectedWeaponAmmoOffset = PS3::ReadInt32(SelectedWeaponOffset2 + AmmoInfo);
			switch (currentOption)
			{
			case 1:
				PS3::WriteFloat(SelectedWeaponOffset2 + Damage, Damage2); 
				break;
			case 2:
				PS3::WriteFloat(SelectedWeaponAmmoOffset + LaunchSpeed, Launch); 
				break;
			case 3:
				PS3::WriteFloat(SelectedWeaponOffset2 + Force, Diffusion); 
				PS3::WriteFloat(SelectedWeaponOffset2 + ForceHitFlyingHeli, Diffusion);
				PS3::WriteFloat(SelectedWeaponOffset2 + ForceHitPed, Diffusion);
				PS3::WriteFloat(SelectedWeaponOffset2 + ForceHitVehicle, Diffusion);
				break;
			default:; break;
			}
		}
		switch (getOption())
		{
		}
		break;
#pragma endregion

		#pragma region WeaponModelEditor
	case WeaponModelEditor:
		addTitle("モデルセット");
		for (int i = 0; i < 56; i++)
		{
			addOption(WEAPONJAPANESE[i]);
		}
		if (optionPress)
		{
			SelectedModelID = currentOption - 1;
			int Offset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY(WEAPONMENU[SelectedModelID]));
			int Offset2 = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY(WEAPONMENU[SelectedWeaponID]));
			int model = PS3::ReadInt32(Offset + Model);
			PS3::WriteInt32(Offset2 + Model, model);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), 0xA2719263, true);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY(WEAPONMENU[SelectedWeaponID]), true);
			NotifyDown("モデルセット完了!", 500);
		}
		break;
#pragma endregion

		#pragma region WeaponStatAmmoEditor
	case WeaponStatAmmoEditor:
		addTitle("弾変更");
		addOption("緑レーザー(~y~爆発~w~)");
		addOption("赤レーザー(~y~爆発~w~)");
		addOption("緑レーザー(~b~噴水~w~)");
		addOption("赤レーザー(~b~噴水~w~)");
		addOption("緑レーザー(~r~火柱~w~)");
		addOption("赤レーザー(~r~火柱~w~)");
		addOption("緑レーザー(~g~花火~w~)");
		addOption("赤レーザー(~g~花火~w~)");
		addOption("弾無限固定化");
		addOption("ロケット");
		addOption("花火");
		switch (getOption())
		{
		case 1:AmmoSet(GreenLaser); break;
		case 2:AmmoSet(RedLaser); break;
		case 3:AmmoSet(GreenLaser, 13); break;
		case 4:AmmoSet(RedLaser, 13); break;
		case 5:AmmoSet(GreenLaser, 12); break;
		case 6:AmmoSet(RedLaser, 12); break;
		case 7:AmmoSet(GreenLaser, 35); break;
		case 8:AmmoSet(RedLaser, 35); break;
		case 9:InfiniteAmmoManzi(); break;
		case 10:AmmoSet(Rocket, 4); break;
		case 11:
			int address = SelectedWeaponOffset2;
			int AddAmmo = SelectedWeaponAmmoOffset;
			int Firework = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_FIREWORK"));
			int FireAmmo = PS3::ReadInt32(Firework + AmmoInfo);
			PS3::WriteInt32(FireAmmo + Explosion_Default, 35);
			PS3::WriteInt32(FireAmmo + ProjectileFlags, 4);
			PS3::WriteInt32(address + FireType, 4);
			PS3::WriteInt32(address + AmmoInfo, FireAmmo);
			WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_FIREWORK"), -1);
			break;
		}
		break;
#pragma endregion

		#pragma region Walk Edit
	case walkedit:
		addTitle("歩行スタイル");
		addOption("男歩き");
		addOption("女歩き");
		addOption("泥酔");
		addOption("登山家");
		addOption("ランニング");
		addOption("怪我人");
		addOption("筋トレ");

		switch (getOption())
		{
		case 1:
			ChangeWalkingType("move_m@generic");
			break;
		case 2:
			ChangeWalkingType("move_f@generic");
			break;
		case 3:
			ChangeWalkingType("move_m@drunk@verydrunk");
			break;
		case 4:
			ChangeWalkingType("move_m@hiking");
			break;
		case 5:
			ChangeWalkingType("move_f@film_reel");
			break;
		case 6:
			ChangeWalkingType("move_m@injured");
			break;
		case 7:
			ChangeWalkingType("move_m@business@a");
			break;
		}
		break;
#pragma endregion
	
#pragma endregion
	
		#pragma region Select Player List
	case Select_Players_List:
		addTitle("プレイヤーリスト選択");
		addSubmenuOption("プレイヤー操作", Players_List);
		/*addSubmenuOption("マネー配布プレイヤー", Money_List);
		addFloatOption("マネー配布の高さ", &PlusMoneyZ, -1, 5, true, 0.1);*/
		addSubmenuOption("ESP 個人リスト", ESP_List);
		addSubmenuOption("ESP 設定", ESP_List_Settings);
		//addSubmenuOption("手配度削除 個人", RWanted_List);
		//addSubmenuOption("マネーガン 個人", GiveMoneyGun_List);
		//addSubmenuOption("アパート招待リスト", Players_List_Apart, "選択中 → リストの中のプレイヤーへ");
		break;
#pragma endregion

		#pragma region Money_List
	/*case Money_List:
		addTitle("マネー配布 プレイヤーリスト");
		for (int i = 0; i < 16; i++)
		{
			RGBA BoolColour;
			BoolColour.R = MoneyFlag[i] ? 255 : 0;
			BoolColour.G = MoneyFlag[i] ? 0 : 0;
			BoolColour.B = MoneyFlag[i] ? 0 : 255;
			MarkerESP(currentOption - 1, BoolColour);
		}
		if (optionPress)
		{
			MoneyFlag[currentOption - 1] = !MoneyFlag[currentOption - 1];
		}
		break;*/
#pragma endregion

		#pragma region ESP_List
	case ESP_List:
		addTitle("個人ESPプレイヤーリスト");
		for (int i = 0; i < 16; i++)
		{
			addCheckBool(PlayerNameReturn(i), ESPFlag[i]);
			RGBA BoolColour;
			BoolColour.R = MoneyFlag[i] ? 255 : 0;
			BoolColour.G = MoneyFlag[i] ? 0 : 0;
			BoolColour.B = MoneyFlag[i] ? 0 : 255;
			MarkerESP(currentOption - 1, BoolColour);
		}
		if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_A))
		{
			ESPFlag[currentOption - 1] = !ESPFlag[currentOption - 1];
		}
		break;
#pragma endregion

		#pragma region ESP_List_Settings
	case ESP_List_Settings:
		addTitle("個人ESPリスト設定");
		addCheckBool("名前 相手 距離表示", NameESPFlag, "");
		addCharSwap("線の色", ESPColor, &ESPVar, 0, 2, "");
		switch (getOption())
		{
		case 1: NameESPFlag = !NameESPFlag; break;
		}
		break;
#pragma endregion

		#pragma region RWanted_List
	/*case RWanted_List:
		addTitle("手配度削除リスト");
		for (int i = 0; i < 16; i++)
		{
			addCheckBool(PlayerNameReturn(i), WantedFlag[i]);
			RGBA BoolColour;
			BoolColour.R = MoneyFlag[i] ? 255 : 0;
			BoolColour.G = MoneyFlag[i] ? 0 : 0;
			BoolColour.B = MoneyFlag[i] ? 0 : 255;
			MarkerESP(currentOption - 1, BoolColour);
		}
		if (optionPress)
		{
			WantedFlag[currentOption - 1] = !WantedFlag[currentOption - 1];
		}
		break;*/
#pragma endregion

		/*#pragma region GiveMoneyGun_List
		addTitle("マネーガンリスト");
		for (int i = 0; i < 16; i++)
		{
			addCheckBool(PlayerNameReturn(i), MoneygunPlayerFlag[i]);
			RGBA BoolColour;
			BoolColour.R = MoneyFlag[i] ? 255 : 0;
			BoolColour.G = MoneyFlag[i] ? 0 : 0;
			BoolColour.B = MoneyFlag[i] ? 0 : 255;
			MarkerESP(currentOption - 1, BoolColour);
		}
		if (optionPress)
		{
			MoneygunPlayerFlag[currentOption - 1] = !MoneygunPlayerFlag[currentOption - 1];
		}*/
#pragma endregion

		#pragma region Players_List_Apart
	/*case Players_List_Apart:
		addTitle("アパート招待リスト");
		for (int i = 0; i < 16; i++)
		{
			char AAA[500];
			strcpy(AAA, PlayerNameReturn(i));
			addOption(AAA);
		}
		RGBA AAA2 = { 0, 255, 0 };
		MarkerESP(currentOption - 1, AAA2);
		if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			ApartSelected = currentOption - 1;
			apartmentInvite(selectedPlayer, ApartSelected);
		}
		break;*/
#pragma endregion

		#pragma region Player List
	case Players_List:
		addTitle("通常プレイヤーリスト");
		for (int i = 0; i < 18; i++)
		{

			int Handle[13];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(i, &Handle[0], 13);
			char *RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
			char* nameOfPlayer = PLAYER::GET_PLAYER_NAME(i);
			char AAA[100];

			char *Player = PLAYER::GET_PLAYER_NAME(i);
			strcpy(AAA, PlayerNameReturn(i));
			if (GodModeCheck(i) && !IsPlayerInvisible(i) && !NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(i) && !PLAYER::IS_PLAYER_DEAD(i) && !ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(i) && (getPlayerStat(i, 238) == 0) && !NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(i) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::GET_PLAYER_PED(i)))
			{
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					strcat(AAA, " ~w~[~r~無敵~w~]");
				}
			}

			if (PLAYER::IS_PLAYER_PLAYING(i) && NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{
				if (PS3::Read_Global(1581767 + (i * 306) + 205) == 987)
					strcat(AAA, " ~w~[~p~Phantom ~r~A~w~]");
				else if (PS3::Read_Global(1581767 + (i * 306) + 205) == 986)
					strcat(AAA, " ~w~[~p~Phantom~w~]");
				else if (PS3::Read_Global(1581767 + (i * 306) + 205) == 914)
					strcat(AAA, " ~w~[~g~ZEDD~w~]");
				else if (PS3::Read_Global(1581767 + (i * 306) + 205) == 911)
					strcat(AAA, " ~w~[~g~ZEDD ~r~A~w~]");
				else if (PS3::Read_Global(1581767 + (i * 306) + 205) == 888)
					strcat(AAA, " ~w~[~y~PLS ~r~A~w~]");
				else if (PS3::Read_Global(1581767 + (i * 306) + 205) == 889)
					strcat(AAA, " ~w~[~g~PLS~w~]");
			}
		
			if (NETWORK::NETWORK_IS_FRIEND_ONLINE(Player))
				strcat(AAA, "~g~[F]");
			if (strcmp(RealName, nameOfPlayer))
			{
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					strcat(AAA, " ~o~[名前偽装]");
				}
			}
			if (ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::GET_PLAYER_PED(i)) == 4095)
			{
				strcat(AAA, " ~w~[~r~Paradise~w~]");
			}
			else if (PLAYER::GET_PLAYER_MAX_ARMOUR(i) > 100)
			{
				strcat(AAA, " ~w~[~r~SPRX~w~]");
			}

			addOption(AAA);
		}
		RGBA AAA = { 0, 255, 0 };
		MarkerESP(currentOption - 1, AAA);
		PlayerUIInfo = false;
			if (optionPress && NETWORK::NETWORK_IS_PLAYER_CONNECTED(currentOption - 1))
			{
				selectedPlayer = currentOption - 1;
				changeSubmenu(Player_Options);
			}
		break;
#pragma endregion

		#pragma region Player Option
	case Player_Options:
		addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
		addSubmenuOption("テレポート", TeleportMenu, "TP to Me, Tp to Player等");
		addSubmenuOption("~r~管理~w~オプション", adminoption);
		addSubmenuOption("ドロップ系", MoneyDropper, "お金等を降らす");
		addSubmenuOption("武器MOD", GiveModMenu, "Teleport Gun等");
		addSubmenuOption("車両操作", Player_Vehicle_Options);
		addSubmenuOption("アニメーション", AnimationSub);
		addSubmenuOption("~b~遠隔 ~g~リカバリー", StatsEditor);
		addSubmenuOption("攻撃", Shoot_Bullet_At_Player);
		addSubmenuOption("アタッチ系", Object_Attach);
		addSubmenuOption("~r~スクリプト~w~&~b~悪質", Player_OptionPt2);
		//addSubmenuOption("天候変更", tenkouhenkou);
		addSubmenuOption("メッセージ送信", MessageSend, "");
		addOption("~b~プロフィールを開く");
		addOption("~y~フレンド追加");
		addCheckBool("~r~監視モード", spectatemode);
		/*addOption("保存");
		addOption("test");
		addOption("AAA");
		addOption("強制キック");
		addOption("TEST表示");
		addOption("アドレス表示");
		addIntOption("アドレス入力", &addressInt, 1, 10000000, true);
		addOption("アドレス表示");*/

		PlayerUIInfo = true;
	/*	
			addOption("アドミンキル");
			addCheckBool("Freeze Console ~b~V1", DoFreezeConsole);
			addOption("Freeze Console ~r~V2");
		*/
		//addCheckBool("~r~プレイヤー操作モード", AttachingToMe, "");

		switch (getOption())
		{
		case 12:
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
			NETWORK::NETWORK_SHOW_PROFILE_UI(NetHandleBuffer);
			break;


		case 13:
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
			NETWORK::NETWORK_ADD_FRIEND(NetHandleBuffer, "Phantom からフレンド申請!");
			break;

		case 14:
			spectatemode = !spectatemode;
			if (spectatemode)
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::GET_PLAYER_PED(selectedPlayer));
			}
			else
			{
				//AI::CLEAR_PED_TASKS(PLAYER::PLAYER_ID());
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED(selectedPlayer));
			} break;



		//case 16:
		//	int BBB2, CCC2, Ptr;
		//	Ptr = *(int*)((0x1E70374 - 0x04) + ((((1581767 + (selectedPlayer * 306) + 180) / 0x40000) & 0x3F) * 4));
		//	if (Ptr != 0)
		//	{
		//		//PRINT(ItoS(Ptr), 2000);
		//		BBB2 = Ptr + (((1581767 + (selectedPlayer * 306) + 180) % 0x40000) * 4);
		//		NotifyDown(ItoS(BBB2));
		//	}
		//	break;
		//	
		//case 17: 
		//	PSIDsave(selectedPlayer); break;
		//case 18: AdminMessage(selectedPlayer, "死ね"); break;
		//case 19: PS3::Write_Global(1588610 + (selectedPlayer + 1), 1); break;
		//case 20:

		//	int BBBB, Ptr1;
		//	Ptr1 = *(int*)((0x1E70374 - 0x04) + (((2399048 + 2415 + 232 / 0x40000) & 0x3F) * 4));
		//	if (Ptr1 != 0)
		//	{
		//		//PRINT(ItoS(Ptr), 2000);
		//		BBBB = Ptr1 + ((1588610 + 2399048 + 2415 + 232 % 0x40000) * 4);
		//		NotifyDown(ItoS(BBBB));

		//	}
		//	break;
		//case 21: PS3::Read_Global_Printf(addressInt); break;
		}

		break;
#pragma endregion

#pragma region adminoption
	case adminoption:
		addTitle("~r~管理~w~オプション");
		addOption("~r~強制~g~キック");
		addOption("~r~無敵キル");
		addOption("~r~H ~b~ホストキック");
		addOption("~r~アカウント ~b~無効化");
		addOption("~r~VC ~b~無効化");
		addCheckBool("~r~個人 ~y~フリーズ", directfreezeconsole);
		addOption("Freeze ~r~V1");
		addOption("Freeze ~b~V2");
		if (FlagIndexes == AdminFlag)
		{
			addOption("Phantom kick");
			addOption("Phantom Freeze");
			addOption("IP SAVE");
			/*addKeyboardOption("入力", 5, "", 100, "");
			addKeyboardOption("入力", 6, "", 100, "");
			addKeyboardOption("入力", 7, "", 100, "");
			addKeyboardOption("入力", 8, "", 100, "");*/
			addCharSwap("キックType :", KickChar, &KickInt, 0, 2, false);

		}
		switch (getOption())
		{
		case 1:ForceKickByNonHost(selectedPlayer); break;
		case 2: TeleportInScene(PLAYER::GET_PLAYER_PED(selectedPlayer), "mini@strip_club@private_dance@part3", "priv_dance_p3", 10000, 10000, -10);break;
		case 3: NETWORK::NETWORK_SESSION_KICK_PLAYER(selectedPlayer); break;
		case 4: DisableAccount(selectedPlayer); break;
		case 5: muteBanPlayer(selectedPlayer); break;
		case 6: directfreezeconsole = !directfreezeconsole; break;
		case 7:
			Vehicle_Hash = GAMEPLAY::GET_HASH_KEY("akuma");
			Vehicle_Atach = true; break;
		case 8:
			Vehicle_Hash = GAMEPLAY::GET_HASH_KEY("akuma");
			Vehicle_Atach2 = true; break;
		case 9: PhantomError(selectedPlayer); break;
		case 10: PhantomFreeze(selectedPlayer); break;
		case 11: PSIDsave(selectedPlayer); break;
		case 12: DoKickPlayer(selectedPlayer); break;
		}
		break;


	case Shoot_Bullet_At_Player:
		addTitle("攻撃");
		addBoolOption("ループ", ShootBulletAPlayerLoop);
		addOption("赤レーザー (爆発)");
		addOption("緑レーザー (爆発)");
		addOption("ハンター");
		addOption("スタンガン");
		addOption("花火");
		addOption("戦車");
		addCharSwap("爆発", EXPLOSION_TYPES, &EXPLOSIONVAR, 0, 35, "");
		switch (getOption()) {
		case 1: ShootBulletAPlayerLoop = !ShootBulletAPlayerLoop; break;
		case 2:
			BulletAtPlayerString = "VEHICLE_WEAPON_ENEMY_LASER";
			WeaponAmmoChange(BulletAtPlayerString);
			ShootBulletAPlayer = true;
			break;
		case 3:
			BulletAtPlayerString = "VEHICLE_WEAPON_PLAYER_LASER";
			WeaponAmmoChange(BulletAtPlayerString);
			ShootBulletAPlayer = true;
			break;
		case 4:
			BulletAtPlayerString = "VEHICLE_WEAPON_PLAYER_HUNTER";
			ShootBulletAPlayer = true;
			break;

		case 5:
			BulletAtPlayerString = "WEAPON_STUNGUN";
			ShootBulletAPlayer = true;
			break;

		case 6:
			BulletAtPlayerString = "WEAPON_FIREWORK";
			ShootBulletAPlayer = true;
			break;

		case 7:
			BulletAtPlayerString = "VEHICLE_WEAPON_TANK";
			ShootBulletAPlayer = true;
			break;
		case 8:
			Vector3 handleCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
			FIRE::ADD_EXPLOSION(handleCoords.x, handleCoords.y, handleCoords.z, EXPLOSIONVAR, 0.5f, true, false, 0.0f);
			break;
		}break;
#pragma endregion

		#pragma region Money Dropper
	case MoneyDropper:
		addTitle("ドロップ");
		addFloatOption("降らす高さ", &PlusMoneyZ, -1, 5, true, 0.1, "物を降らす高さ");
		addCheckBool("40K ドロップ", MoneyFlag[selectedPlayer], "4万ドルを降らす。");
		addCheckBool("パラシュート ドロップ", ParachuteFlag[selectedPlayer], "パラシュートを降らす");
		addCheckBool("スナック ドロップ", DropSnackFlag[selectedPlayer], "スナックを降らす");
		addOption("弾薬");
		addOption("アーマードロップ");
		addOption("回復");
		addOption("アーマー");
		addOption("スタンガン");
		//addOption("Give無敵");
		switch (getOption())
		{
		case 2: MoneyFlag[selectedPlayer] = !MoneyFlag[selectedPlayer]; break; //40K ドロップ
		case 3: ParachuteFlag[selectedPlayer] = !ParachuteFlag[selectedPlayer]; break; // パラシュート ドロップ
		case 4: DropSnackFlag[selectedPlayer] = !DropSnackFlag[selectedPlayer]; break; // スナック ドロップ
		case 5: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_ld_ammo_pack_01", "PICKUP_AMMO_BULLET_MP", 10, "Ammo", selectedPlayer); break;
		case 6: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_armour_pickup", "PICKUP_ARMOUR_STANDARD", 100, "Armor", selectedPlayer); break;
		case 7: dropPickup(get_entity_coords_orig(PLAYER::GET_PLAYER_PED(selectedPlayer), 1), "prop_ld_health_pack", "PICKUP_HEALTH_STANDARD", 100, "Health", selectedPlayer); break;
		case 8: GiveArmour(selectedPlayer); break;
		case 9: WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 911657153, -1, true, true); break;
		case 10:CREATE_AND_ATTACH(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x8DA1C0E, 0, 0.1, -0.1, 0, 500); break;
		}
		break;
#pragma endregion

		#pragma region GiveModMenu
	case GiveModMenu:
		addTitle("武器に効果を追加");
		addCheckBool("~y~瞬間移動弾", TeleportGunFlag[selectedPlayer], "撃ったらテレポートします");
		addCheckBool("~r~爆発弾", ExplosionGunFlag[selectedPlayer], "撃ったところが爆発します");
		addCheckBool("~r~炎弾", FireGunFlag[selectedPlayer], "撃ったところから炎が出ます");
		addCheckBool("~b~放水弾", SteamGunFlag[selectedPlayer], "撃ったところから噴水が出ます");
		addCheckBool("~y~金弾", MoneygunPlayerFlag[selectedPlayer], "撃ったところにマネー出現");
		addCheckBool("~r~フレアガン", FreaGun[selectedPlayer]);
		addCheckBool("~p~花火", FireWorkGun[selectedPlayer]);
		switch (getOption())
		{
		case 1:TeleportGunFlag[selectedPlayer] = !TeleportGunFlag[selectedPlayer]; break;
		case 2: ExplosionGunFlag[selectedPlayer] = !ExplosionGunFlag[selectedPlayer]; break;
		case 3: FireGunFlag[selectedPlayer] = !FireGunFlag[selectedPlayer]; SteamGunFlag[selectedPlayer] = false; break;
		case 4: SteamGunFlag[selectedPlayer] = !SteamGunFlag[selectedPlayer]; FireGunFlag[selectedPlayer] = false; break;
		case 5: MoneygunPlayerFlag[selectedPlayer] = !MoneygunPlayerFlag[selectedPlayer]; break;
		case 6: FreaGun[selectedPlayer] = !FreaGun[selectedPlayer]; break;
		case 7: FireWorkGun[selectedPlayer] = !FireWorkGun[selectedPlayer]; break;
		}
		break;
#pragma endregion

		#pragma region Teleporter
	case TeleportMenu:
		Vector3 My;
		addTitle("テレポート系");
		addOption("相手の元へテレポート");
		addCheckBool("テレポート時の硬直", TPFreeze, "自分の元への際の硬直");
		addOption("自分の元へテレポート(体のみ)");
		addOption("自分の元へテレポート(車ごと)");
		addOption("相手の車へ乗車");
		addOption("全員をその人へ");
		addOption("~r~深海へテレポート");
		switch (getOption())
		{
		case 1:
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			My = ENTITY::GET_ENTITY_COORDS(Player, 1);
			TeleportToCoords(PLAYER::PLAYER_PED_ID(), My.x, My.y, My.z);
			char AAAA[100];
			strcpy(AAAA, PLAYER::GET_PLAYER_NAME(selectedPlayer));
			strcat(AAAA, "の元へテレポートしました。");
			NotifyDown(AAAA, 1000);
			break;
		case 2: TPFreeze = !TPFreeze; break;
		case 3:
			My = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			TeleportInScene(PLAYER::GET_PLAYER_PED(selectedPlayer), "mini@strip_club@private_dance@part3", "priv_dance_p3", My.x, My.y, My.z);
			NotifyDown("テレポートさせました。");
			break;
		case 4:
			My = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			TeleportCar(PLAYER::GET_PLAYER_PED(selectedPlayer), My.x, My.y, My.z);
			NotifyDown("テレポートさせました。");
			break;
		

		case 5:
			TeleportToClientCar(PLAYER::GET_PLAYER_PED(selectedPlayer));
			break;

		case 6:
			AllTeleportToMe(selectedPlayer);
			break;

		case 7:
			TeleportInScene(PLAYER::GET_PLAYER_PED(selectedPlayer),"mini@strip_club@private_dance@part3", "priv_dance_p3",10000, 10000, -10);
			break;
		}
		break;
#pragma endregion

		#pragma region MessageSend
	case MessageSend:
		addTitle("メッセージ送信");
		addCharSwap("カラー変更", ColorMessageJapanese, &ColorMessageVar, 0, 15, "");
		addSendOption("はい");
		addSendOption("いいえ");
		addSendOption("わかりました");
		addSendOption("こんにちは");
		addSendOption("Phantomです");
		addSendOption("地面を撃ってみてください");
		addSendOption("お金いりますか");
		addSendOption("ランク何がいいですか");
		addSendOption("何のSPRX使ってますか?");
		addSendOption("無理です");
		addSendOption("いいですよ");
		addSendOption("いいですね");
		addSendOption("荒らして楽しいですか?");
		addSendOption("すごいですね!");
		switch (getOption())
		{
		}

		break;
#pragma endregion

		#pragma region 車体操作
	case Player_Vehicle_Options:
		addTitle("車体操作");
		addOption("ジャンプ");
		addOption("ブースト");
		addOption("ストップ");
		addCheckBool("乗車時ずっと飛ばす", soratobu);

		switch (getOption())
		{
		case 1:SlingShot = true; break;
		case 2: boost = true; break;
		case 3: carstop = true; break;
		case 4: soratobu = !soratobu; break;

		}
		break;
#pragma endregion

		#pragma region アニメーション
	case AnimationSub:
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
		case 1:Freeze(PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		case 2:Animations2[0] = AnimaMenu2[AnimaType]; Animations2[1] = Animahsh[AnimaType]; SetPlayerAnimation = true; break;
		case 3:Animations2[0] = AnimaMenu2A[AnimaTypeA]; Animations2[1] = AnimahshA[AnimaTypeA]; SetPlayerAnimation = true; break;
		case 4:Animations2[0] = AnimaMenu2S[AnimaTypeS]; Animations2[1] = AnimahshS[AnimaTypeS]; SetPlayerAnimation = true; break;
		case 5:Animations2[0] = AnimaMenu2N[AnimaTypeN]; Animations2[1] = AnimahshN[AnimaTypeN]; SetPlayerAnimation = true; break;
		case 6:Animations2[0] = AnimaMenu2M[AnimaTypeM]; Animations2[1] = AnimahshM[AnimaTypeM]; SetPlayerAnimation = true; break;
		case 7:Animations2[0] = AnimaMenu2O[AnimaTypeO]; Animations2[1] = AnimahshO[AnimaTypeO]; SetPlayerAnimation = true; break;
		}
		break;
#pragma endregion
		
		#pragma region Stat Editor
	case StatsEditor:
		addTitle("ステータス");
		addOption("ステータスMAX", "");
		addOption("強制負け犬解除", "");
		addOption("足早~g~有効化", "");
		addOption("足早~r~無効化", "");
		addOption("無限ローリング化", "");
		addOption("無限ローリング解除", "");
		addOption("所持品全てMAX", "");
		addOption("クルーランクアップ");
		addOption("大金代行");
		addOption("ロスカス解除");
		addOption("髪型解除");
		addOption("キル数を上げる");
		addOption("デス数を上げる");
		addOption("レッドプレイヤーにする");
		addCharSwap("ランクアップ", RPListChar, &PlusRPVar, 0, 7);
		addCharSwap("ランクダウン", RPListChar_, &PlusRPVar_, 0, 7);
		//addCharSwap("ランクアップ", RPListChar_, &PlusRPVar_, 0, 7);
		switch (getOption())
		{
		case 1:
			Skill();
			break;
		case 2:
			addBatSports(false);
			break;

		case 3:
			WalkSPeed(true);
			break;

		case 4:
			WalkSPeed(false);
			break;

		case 5:
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 1000);
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SHOOTING_ABILITY"), 1000);
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SHOOTING_ABILITY"), 1000);
			break;

		case 6:
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 0);
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SHOOTING_ABILITY"), 0);
			setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SHOOTING_ABILITY"), 0);
			break;

		case 7:
			InventoryMax();
			break;
		case 8: CrewRank(); break;
		case 9: CashGiftplayer(); break;
		case 10: LSC(); break;
		case 11: CLTHSplayer; break;
		case 12: killsplayer(); break;
		case 13: deathsplayer(); break;
		case 14: RedesignPromtplayer(selectedPlayer); break;

		case 15:
			GiveRP(selectedPlayer, -1 * RPList[PlusRPVar]); break;

		case 16:
			GiveRP(selectedPlayer, -1 * RPList_[PlusRPVar_]); break;
			break;
		}
		break;
#pragma endregion

		#pragma region Object_Attach
	case Object_Attach:
		addCharSwap("アタッチ場所", BONSCH, &GetPedBoneIndex, 0, 13, "アタッチ先を選択");
		addCharSwap("オブジェクト", UnusedObj1, &SelectedObject, 0, 21, "アタッチするオブジェクトを選択");
		addCheckBool("車の上にアタッチ", AttachtoVehicleTop);
		addCheckBool("プレイヤーへアタッチ", PlayerAttached);
		addFloatOption("アタッチ<X座標>", &One1.x, -3, 3, true, 0.05);
		addFloatOption("アタッチ<Y座標>", &One1.y, -3, 3, true, 0.05);
		addFloatOption("アタッチ<Z座標>", &One1.z, -3, 3, true, 0.05);
		addFloatOption("回転<X座標>", &Two1.x, 0, 360, true, 10);
		addFloatOption("回転<Y座標>", &Two1.y, 0, 360, true, 10);
		addFloatOption("回転<Z座標>", &Two1.z, 0, 360, true, 10);
		switch (currentOption)
		{
		case 1:; break;
		case 2:; break;
		case 3:; break;
		case 4:; break;
		default:
			if (fastRightPress || fastLeftPress || rightPress || leftPress)
			{
				if (PlayerAttached)
				{
					PlayerAttached = false; toggleAttach(selectedPlayer);
				}
			}break;
		}
		switch (getOption())
		{
		case 2:
			ObjectAttach = true;
			AttachObjectID = UnusedObj1[SelectedObject];
			break;
		case 3:AttachtoVehicleTop = !AttachtoVehicleTop; break;
		case 4:toggleAttach(selectedPlayer);

			break;

		}

		break;
#pragma endregion

		#pragma region tenkouhenkou
	//case tenkouhenkou:
	//	addTitle("天候変更");
	//	addOption("雨");
	//	addOption("晴れ");
	//	addOption("ブリザード");
	//	switch (getOption())
	//	{
	//	case 1: changePlayerWeather(0x1871A0C); break;
	//	case 2: changePlayerWeather(0x1813D78); break;
	//	case 3: changePlayerWeather(0x2504684); break;
	//	
	//	}
	//	break;
#pragma endregion

		#pragma region Player_OptionPt2
	case Player_OptionPt2:
		addTitle("~r~悪質");
		addOption("強制キック");
		addOption("手配度削除");
		addOption("コスチュームを盗む");
		addOption("~r~武器を奪う");
		addOption("~g~武器を与える");
		//addCheckBool("コンソールフリーズ", DoFreezeConsole);//1
		addOption("強制チュートリアル");
		addOption("強制ゴルフ");//5
		addOption("強制レスリング");//6
		addOption("強制ダーツ");//7
		addOption("フェイク退出");//8
		addOption("HUD破壊");//9
		addOption("強制テニス");//10
		addOption("Give空爆");//11
		addOption("ヘリを呼ぶ");//12
		addOption("Give透明");
		switch (getOption())
		{
		case 1:ForceKickByNonHost(selectedPlayer); break;
		case 2:removePlayerWantedLevel(selectedPlayer); break;
		case 3:StealClothes = true; break;
		case 4: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(selectedPlayer), true); break;
		case 5:
			for (int i = 0; i < 57; i++)
			{
				GiveWeaponPed(PLAYER::GET_PLAYER_PED(selectedPlayer), WepArray[i], -1);
				BruteForceWeaponAddons(PLAYER::GET_PLAYER_PED(selectedPlayer), WepArray[i], true);
			}
			break;
		/*case 6: if (DoFreezeConsole == false) { DoFreezeConsole = true; }
				else if (DoFreezeConsole == true) { DoFreezeConsole = false; }
				NotifyDown("~y~10 sec Player Freeze"); break;*/
		case 6: ForceTutorial(selectedPlayer); break;
		case 7: teleportPlayerIntoGolfEvent(selectedPlayer);  break;
		case 8: teleportPlayerIntoArmWrestlingEvent(selectedPlayer);  break;
		case 9: teleportPlayerIntoDartsEvent(selectedPlayer);  break;
		case 10: makePlayerFakeLeave(selectedPlayer);  break; //playSound
		case 11: sendCash2(selectedPlayer); break;
		case 12: givePlayerMoney(selectedPlayer); break;
		case 13: givePlayerMoney_8(selectedPlayer); break;
		case 14: givePlayerMoney_12(selectedPlayer); break;
		case 15: PlayerRace(selectedPlayer); break;
		}
		break;
#pragma endregion

		#pragma region Settings
	case Settings:
		addTitle("設定");
		addCheckBool("FPS表示", ViewFPS, "30FPSがMAXです。");
		addCheckBool("効果音を近未来にする", SoundChange);
		addCheckBool("セッションの情報を表示", isserverhost);
		addOption("放置キック無効");
		addCheckBool("VC表示",ShowTalking1);
		addCheckBool("VC表示2", VChyouji);
		addCheckBool("雪の地面", SnowTEST);
		addOption("~b~軽量化 ~g~オプション");
		addOption("MENU オープン設定");
		addOption("~r~フリーズロビー");
		addintbooloption("ランク偽装", &RankPPP, -9999999, 9999999, 1, Rankkotei, 1);
		addCheckBool("IP ブラックリスト", IPLoop);
		addOption("Mute 解除");
		addCheckBool("テスト 軽量化", LiteMOD);
		//addOption("PSNspoof");
		//addOption("ホスト確認");
		//addCheckBool("ghostbool", ghostbool);
		/*addOption("AAA");
		addOption("戦闘機");*/
		switch (getOption())
		{
		case 1:ViewFPS = !ViewFPS; KEIRYOUKA = false; break;
		case 2:SoundChange = !SoundChange; break;
		case 3:isserverhost = !isserverhost; break;
		case 4:
			PS3::SetTunable(73, 0x3B9ACA00);
			PS3::SetTunable(74, 0x3B9ACA00);
			PS3::SetTunable(75, 0x3B9ACA00);
			PS3::SetTunable(76, 0x3B9ACA00);
			NotifyDown("Idle Kick ~r~Disabled", 1000);
			break;
		case 5: ShowTalking1 = !ShowTalking1; break;
		case 6: VChyouji = !VChyouji; break;
		case 7: SnowTEST = !SnowTEST; PS3::SetTunable(4715, SnowTEST ? 0x00000001 : 0x00000000); break;
		case 8: changeSubmenu(Keiryoukaoption); break;
		/*case 10: FreezeTrailer(1076615640); break;
		case 11:FreezeHeli(1076736072); break;
		case 12: spoofRank(555); break;*/
		case 9: changeSubmenu(MenuHenkou); break;
		case 10: lobbyf = true; break;
		case 11: Rankkotei = !Rankkotei;break;
		case 12: IPLoop = !IPLoop; break;
		//case 14: broadCastHostMod(); break;
		case 13: NinetyPer(); break;
		//case 12: PSNspoof = true; break;
		//case 13: ghostbool = !ghostbool; Ghost(ghostbool); break;
		case 14: LiteMOD = !LiteMOD; break;
			 break;
		}
		break;

	case Keiryoukaoption:
		addTitle("~b~軽量化 ~g~オプション");
		addCheckBool("軽量化", KEIRYOUKA); //1
		addOption("LOWテクスチャー (~g~安定型~w~)"); //2
		addOption("LOWテクスチャー ~g~小");//6
		addOption("LOWテクスチャー ~g~中");//7
		addOption("LOWテクスチャー ~g~中 ~b~V2");//8
		addOption("LOWテクスチャー ~r~強");//4
		addOption("LOWテクスチャー ~g~強 ~b~V2");//9
		addOption("描写距離 減少"); //3
		addOption("描写速度を落とす");//5
		addOption("~g~鮮明化 ~w~+ ~b~海中クリア");//10
		addOption("通常テクスチャー");//11
		switch (getOption())
		{
		case 1:KEIRYOUKA = !KEIRYOUKA; ViewFPS = false; break;
		case 2:GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema_001");break;
		case 3:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_HD_orphan_reduce"); break;
		case 4:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_LOD_reduce"); break;
		case 5:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_SLOD1_reduce"); break;
		case 6:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_global_reduce_NOHD"); break;
		case 7:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_SLOD2_reduce"); break;
		case 8:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_SLOD3_reduce"); break;
		case 9:GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_HD_orphan_LOD_reduce"); break;
		case 10:GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema"); break;
		case 11:GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");break;
		}
		break;

	case MenuHenkou:
		addTitle("MENU オープン設定");
		addChangeControlOption("通常 四角 + 右", ButtonChange1, Button_X, Dpad_Left);
		addChangeControlOption("X + 左", ButtonChange2, Button_A, Dpad_Left);
		addChangeControlOption("R1 + L1", ButtonChange3, Button_R1, Button_L1);
		addChangeControlOption("R1 + 四角", ButtonChange4, Button_R1, Button_X);
		addChangeControlOption("R3 + 右", ButtonChange5, Dpad_Right, Button_R3);
		addChangeControlOption("R2 + L2", ButtonChange6, Button_L2, Button_R2);
		switch (getOption())
		{
		case 1: ButtonChange1 = true; ButtonChange2 = false, ButtonChange3 = false, ButtonChange4 = false, ButtonChange6 = false, ButtonChange5 = false; break;
		case 2: ButtonChange1 = false; ButtonChange2 = true, ButtonChange3 = false, ButtonChange4 = false, ButtonChange6 = false, ButtonChange5 = false; break;
		case 3: ButtonChange1 = false; ButtonChange2 = false, ButtonChange3 = true, ButtonChange4 = false, ButtonChange6 = false, ButtonChange5 = false; break;
		case 4: ButtonChange1 = false; ButtonChange2 = false, ButtonChange3 = false, ButtonChange4 = true, ButtonChange6 = false, ButtonChange5 = false; break;
		case 5: ButtonChange1 = false; ButtonChange2 = false, ButtonChange3 = false, ButtonChange4 = false, ButtonChange6 = false, ButtonChange5 = true; break;
		case 6: ButtonChange1 = false; ButtonChange2 = false, ButtonChange3 = false, ButtonChange4 = false, ButtonChange6 = true, ButtonChange5 = false; break;
		}
		break;
#pragma endregion
	}
	
	resetVars();
}

int sleep(int msec)
{
	return sys_timer_usleep(msec * 1000);
}
char TmpLisenceReturn[30]; char MainLisenceReturn[30]; char LooLisence[30];
uint64_t swl2[10];
int RequestID = 0;
void Engine_Thread(uint64_t)
{


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

	strcpy(MacAddress300, getMacAddress());
	if (!IsMacTMP)
	{
		if (cellFsOpen("/dev_hdd0/tmp/Phantom.config", CELL_FS_O_CREAT, &LisenceTmpDDA3, NULL, 0) == CELL_FS_SUCCEEDED)
		{
			cellFsOpen("/dev_hdd0/tmp/Phantom.config", CELL_FS_O_WRONLY, &LisenceTmpDDA2, NULL, 0);
			PS3::Write(LisenceTmpDDA2, MacAddress300, swl2[2]);
			FlagIndexes = PlzRebuildPS3;
		}
		else
		{
			FlagIndexes = MacCreateError;
		}
	}
	else
	{
		if (!(strstr(MacAddress300, IsMacReturn) != NULL))
		{
			FlagIndexes = MacAddressInvalid;
		}
	}

	if (MainFlagIndex == 0)
	{
		switch (FlagIndexes)
		{
		case NormalFlag:
			Dialog::ShowText("!!! Phantom SPRX Loading now !!!");
			Dialog::SetProgressText("購入ありがとうございます。\nBy Zenom\n協力者\nZEDD\n開発者 Stang");
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::Close();
			break;

		case AdminFlag:
			Dialog::ShowText("Phantom SPRX Loading now !!!\n\nMENU OPEN  + ");
			Dialog::SetProgressText("Admin");
			//Dialog::SetProgressText(MacAddress);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::SetProgressInc(20);
			sleep(1000);
			Dialog::Close();
			break;

		case BannedFlag:
			Dialog::ShowText("Error Code : 0xF8004000");
			Dialog::SetProgressText("");
			break;

		case CantLogin:
			Dialog::ShowText("Error Code : 0xF8000003");
			Dialog::SetProgressText("");
			break;

		case UsedLicense:
			Dialog::ShowText("Error Code : 0xF8000002");
			Dialog::SetProgressText("");
			break;

		case InvilidLicenseError:
			Dialog::ShowText("Error Code : 0xF8000001");
			Dialog::SetProgressText("");
			break;

		case NetworkError:
			Dialog::ShowText("Error Code : 0xF8000010"); // ネトエラ
			Dialog::SetProgressText("");
			break;

		case LicenseLoadError:
			Dialog::ShowText("Error Code : 0xF80000FF"); // ライセンスロードエラー
			Dialog::SetProgressText("");
			break;

		case PlzRebuildPS3:
			Dialog::ShowText("GTA5を再起動してください。"); // MACアドレス保存
			Dialog::SetProgressText("");
			break;

		case MacCreateError:
			Dialog::ShowText("Error Code : 0xF80010FF"); // MACアドレス保存失敗
			Dialog::SetProgressText("");
			break;

		case MacAddressInvalid:
			Dialog::ShowText("Error Code : 0xF80020FF"); // MACアドレス偽装
			Dialog::SetProgressText("");
			break;
		}
	}
	else
	{
		Dialog::ShowText("メンテナンス中です。");
		Dialog::SetProgressText("Server is maintenance now.....");
	}

	sys_ppu_thread_exit(0);

	//printf("よ！フック接続完了だぜ！\n");
}

extern "C" int _Memories_prx_entry(void)
{
	//PS3::WriteString(0x1826824, "/dev_hdd0/tmp/ZeNomWater/water.xml");

	char PhantomCodeApply[60]; // /dev_hdd0/tmp/PhantomCode.txt
	char* PhantomCodeText[] = { "/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","e","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","v","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","_","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","0","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","p","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","/","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","P","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","h","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","a","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","n","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","m","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","C","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","o","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","d","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","e","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼",".","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","x","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼","t","똥별똥별β똥별㌼똥별♥똥별α똥별똥별β똥별㌼" };
	sprintf(PhantomCodeApply, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", PhantomCodeText[0], PhantomCodeText[2], PhantomCodeText[4], PhantomCodeText[6], PhantomCodeText[8], PhantomCodeText[10], PhantomCodeText[12], PhantomCodeText[14], PhantomCodeText[16], PhantomCodeText[18], PhantomCodeText[20], PhantomCodeText[22], PhantomCodeText[24], PhantomCodeText[26], PhantomCodeText[28], PhantomCodeText[30], PhantomCodeText[32], PhantomCodeText[34], PhantomCodeText[36], PhantomCodeText[38], PhantomCodeText[40], PhantomCodeText[42], PhantomCodeText[44], PhantomCodeText[46], PhantomCodeText[48], PhantomCodeText[50], PhantomCodeText[52], PhantomCodeText[54], PhantomCodeText[56]);

	int LisenceTmpDDA;
	//wm_config.bins
	bool IsLisenceTMP = cellFsOpen(PhantomCodeApply, CELL_FS_O_RDONLY, &LisenceTmpDDA, NULL, 0) == CELL_FS_SUCCEEDED;
	IsMacTMP = cellFsOpen("/dev_hdd0/tmp/Phantom.config", CELL_FS_O_RDONLY, &LisenceTmpDDA2, NULL, 0) == CELL_FS_SUCCEEDED;
	if (IsLisenceTMP)
	{
		cellFsRead(LisenceTmpDDA, LooLisence, 30, &swl2[0]);
		cellFsClose(LisenceTmpDDA);
		cellFsRead(LisenceTmpDDA2, IsMacRet, 30, &swl2[1]);
		cellFsClose(LisenceTmpDDA2);
		strcpy(TmpLisenceReturn, LooLisence);
		strcpy(IsMacReturn, IsMacRet);
		if (IsMacTMP)
		{
			ChangeFlagFromReturnValue(SendToPHP(TmpLisenceReturn));
			IsMenteFlag(SendToMente());
		}
	}
	else
	{
		FlagIndexes = LicenseLoadError;
	}

	sys_ppu_thread_create(&threadId, Engine_Thread, 0, 10, 0x10, 0, "");
	return SYS_PRX_RESIDENT;
}

