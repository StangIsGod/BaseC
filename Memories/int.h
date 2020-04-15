uint64_t HeadlightSearchByte[] = { 0x000000003EC00000, 0x4020000041000000, 0x41F0000042A00000, 0xFFFF800000000000 ,0x0000000000000000, 0x0000000000000000 };
int HeadLightColor[] = { 0xFF, 0xFF, 0, 0 };
int HeadlightInts[5] = {1, 35, 16, 0, 60};
int LightSelectedVar;
int LightSelectedEditVar;
int instructCount;
int frameCache_time, frameCache_old, frameCache_new;
int Get_Ped_Prop_Index[3];
int Get_Ped_Prop_Texture_Index[3];
int GET_PED_DRAWABLE_VARIATION[12];
int GET_PED_TEXTURE_VARIATION[12];
int GET_PED_PALETTE_VARIATION[12];
float RainbowEffectInt[] = { 0.0f, 0.5f, 0.3f };
int intensity[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int falloffMax[] = { 3, 3,3,3,3,3,3,3,3,3 };
int falloffExponent[] = { 8,8,8,8,8,8,8,8,8,8 };
int innerConeAngle[] = {30,30,30,30, 30,30, 30,30, 30,30 };
int outerConeAngle[] = {80,80,80,80 ,80,80 ,80,80 ,80,80 };
int Indexed = 1;
int RedColor[] = {0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
int GreenColor[10];
int BlueColor[10];

int Corona_size[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int Corona_size_far[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int intensity_far[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int numCoronas[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int distBetweenCoronas[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int distBetweenCoronas_far[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int zBias[10];
int _xRotation[10];
int _yRotation[10];
int _zRotation[10];

int Tire_UNKO[3];

int HeadlightIndex;
int HeadlightAddress;
int BackupModel;
int WaterOpacityAll;
int QuadPointer = 0x21C8C48;
int IronmanV2EffectTimer;
int mov;
int bannerTextRed = 255;
int bannerTextGreen = 255;
int bannerTextBlue = 255;
int bannerTextOpacity = 255;
int bannerTextFont = 1;
int bannerRectRed = 16;
int bannerRectGreen = 0;
int bannerRectBlue = 0;
int bannerRectOpacity = 150;
int backgroundRed = 16;
int backgroundGreen = 0;
int backgroundBlue = 0;
int backgroundOpacity = 150;
int backgroundOpacity1 = 180;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 0;
int scrollerRed = 255;
int scrollerGreen = 255;
int scrollerBlue = 255;
int scrollerOpacity = 50;
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;
int OptionPlusIndex = 25;
int gGlareHandle;                           //地球描画関係
int AnimationTimerCount;
int optionCount = 0;                    //項目のオプション数を格納する場所
int submenu = 0;                    //現在開いているメニューが何なのか保存する場所
int currentOption = 0;                    //選択中のオプションを保存
int maxOptions = 18;                   //1ページに表示できるオプション数

int keyboardAction = 0;                    //キーボードのアクションを指定
int *keyboardIntVar = 0;                    //キーボードの結果(int型)を保存
int lastSubmenu[20];                    //最後のサブメニューを保存
int lastOption[20];                    //最後のオプションを保存
int submenuLevel = 0;                    //サブメニュー
int selectedPlayer;


int MoneyTimer[16];

int ParachuteTimer[16];

int DropSnackTimer[16];

int DropWeaponTimer[16];

int ESPVar = 1;	
int WeaponIndex, IronManTimer, DriftIndex;
int ColorMessageVar;
int AnimaType, AnimaTypeA, AnimaTypeS, AnimaTypeSI, AnimaTypeN, AnimaTypeM, AnimaTypeO;

int PlusRPVar;
int PlusRPVar_;
int GetPedBoneIndex;
int SelectedObject;
int BONSINTS[] = { 0x796e, 0x9995,   0xb987,  0x60f0,          0xfcd9,           0x29d2,      0x49d9,       0xe5f2,          0xb1c5,           0x9d4d,      0xb3fe,       0x3fcf,      0x3779,       0xcc4d };

int RPList_[] = { -1000,-5000,-10000,-50000,-100000,-200000,-500000,-1000000 };

int RPList[] = { 1000,5000,10000,50000,100000,200000,500000,1000000 };

int NetHandleBuffer = 0x10070200;
int WeatherAddress1 = 0x003D3E48;
int WeatherAddress2 = 0x01095304;
int WeatherAddress3 = 0x01095358;

int FreezePedID;
int CHANGEType, RPListVar;
int DeleteSpawnedPedFreezeDelay = 0;
bool PUBGMode, PlayerForgeGun; Vector6 PUBGSelect = { 0.075f, -0.15f, -0.02f, 0.0, 165.0f, 0.0f }; Hash UNKO, b2, Backup; bool IsPUBGWEapon; int PUBGWeaponEntity;
Entity Target;
int RapidFireDelay;
int RapidFireDelay1;

int SelectedShotVehicleVar;
Hash WepArray[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B,
0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x5FC3C11, 0xC472FE2,
0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0xA0973D5E, 0x24B17070, 0x60EC506, 0x34A67B97, 0x23C9F95C,
0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xD205520E, 0xBFD21232, 0x92A27487, 0x83839C4, 0xA89CB99E, 0xC0A3098D, 0x7F229F94, 0x7F7497E5, 0x787F0BB, 0xAB564B93,
0x63AB0442, 0x47757124, 0xA3D4D34, 0x3AABBBAA, 0xC734385A, 0xA3D4D34, 0xDC4DB296 };
int SelectedWeaponID;
int SelectedWeaponHash;
int SelectedWeaponOffset;
int SelectedWeaponOffset2;
int SelectedWeaponAmmoOffset;
int SelectedWeaponAimingOffset;
int ApartSelected;
int ModelChangerMenuHash, ModelChangerMenuModel;
int SelectedHash, SelectedCompAddress, SelectedModel;
int CompModelChangeVar;
int MainLightRange, MainLightFalloffExponent, MainLightInnerAngle, MainLightOuterAngle, MainLightCoronaIntensity, MainLightCoronaSize, MainLightVolumeIntensity, MainLightVolumeSize;
int MainLightVolumeExponent, MainLightShadowFadeDistance, MainLightSpecularFadeDistance;
int SecondaryLightIntensity, SecondaryLightRange, SecondaryLightFalloffExponent, SecondaryLightInnerAngle, SecondaryLightOuterAngle, SecondaryLightVolumeIntensity, SecondaryLightVolumeSize, SecondaryLightVolumeExponent, SecondaryLightFadeDistance, fTargetDistalongAimCamera;
int SecondaryColor1Comp[4];
int SecondaryLightVolumeOuterColor1Comp[4];
int Color1Comp[4];
int Color1CompSecond[4];
int SelectedModelID;
int SuperCarVar;
int sportVar;
int VehicleHandle;
int classicVar;
int MuscleVar;
int SedanVar;
int CoupeVar;
int CompactVar;
int SuvVar;
int TrackVar;
int PlaneVar;
int BoatVar; int TrailersVar;
int HelicopterVar;	int BikeVar;	int MilitaryVar;	int ServiceVar; int EmergencyVar; int VanVar;
int BicycleVar;
int CommercialVar;
int SelectedVehicle;
int SpawnedVehicleCode[20];
int ColorR, ColorG, ColorB, ColorA;
int SpawnedIndex;
int AttachSpawnPlayer;
int IEEEHash[] = { 0x00000000 , 0x3f800000 , 0x41200000 , 0x41a00000 ,0x41f00000 ,0x42200000 , 0x42480000 ,0x42c80000,0x43480000,0x43C80000,0x44480000,0x447A0000 };
int EQMODTimer;
int isplayerme;
int Carneon2 = 0;
int Redneon, Greenneon, Blueneon;
int MyCarAddress;
int AddressHandling = 0;
int MycaraddressTarget;

int menu_h_r = 5;
int menu_h_g = 213;
int menu_h_b = 237;
int menu_h_r1 = 5;
int menu_h_g1 = 213;
int menu_h_b1 = 237;
int Extra1 = 157;
int Extra2 = 11;
int Menu_X = 1000;

int VehicleMetaHandling;
int WaterQuad;
int WaterIndex;
int PedList[10];
int PedIndex;
int PedSelectedIndex;
int WaterOpacity;
int SelectedWaterQuad;
int EGG;
int WaterQuadLength = 0x332;

int Camera = 0, Cam_OB, Cam_OB2, PreCamera = 0, PreCamera2 = 0, PreCamera3 = 0, PreCamera4 = 0, PreCamera5 = 0, PreCamera6 = 0, FakeMissileOb, PreMissile, PreMissile2, IronManTimeout,
RaderColorVar, SpeedometerPointerSpeed, IronManSpeed = 2,
WaterCount, WaterEditMaxValue, TimeoutHulk;
int RideonAnimalsPedID;	int UCAVTimer;
int clipDistance = 10;
int ObjectListIndex;
int LightNingObj;
int InfamousSwitch;
int infamousTimer;

int PropAttachTimer;
int VehicleFreezeProtectionDelay;
int Bone;
int BoneIndex;
int ProtectionBypassTimer;
int DRAWABLE_VAR[12];
int TEXTURE_VAR[12];
int PALETTE_VAR[12];
int SWITCH_DRAWABLE_VAR[12];
int SWITCH_TEXTURE_VAR[12];
int SWITCH_PALETTE_VAR[12];
Entity ObjectList[16];
int index = 0;
int T20Offset[4] = { 0x54323000, 0x00000000, 0x00000000, 0x50524F47 };
char QuadBytes[] = { 0xF0, 0x60 , 0xF0 , 0x60 , 0xF2 , 0x54 , 0xF2 , 0x54 , 0x1A , 0x1A , 0x1A , 0x1A , 0x00 , 0x00 , 0x00 , 0x00 };
int ObjectIndexes[30];
int ObjectSelectedIndex;
int HAKUCHOU[4] = { 0x5A454E54,0x4F524E4F,0x00000000, 0x50524F47 };
int SearchOffset[4];	int BackupOffset;
char T20bytes[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05 };
int StartAddress = 0x33000000;

Hash Props[133] = {
	0xB467C540, /*p_spinning_anus_s*/
	0xC2BC19CD, /*p_cs_mp_jet_01_s*/
	0xC42C019A, /*prop_ld_ferris_wheel*/
	0xFB631122, /*prop_bumper_car_01*/
	0x745F3383, /*prop_windmill_01*/
	0xBF8918DE, /*prop_jetski_ramp_01*/
	0xB157C9E4, /*prop_mp_ramp_01*/
	0xF4F1511E, /*prop_mp_ramp_02*/
	0x93948E5E, /*prop_mp_ramp_03*/
	0x6DB9599A, /*prop_bskball_01*/
	0x2E28CA22, /*p_tram_crash_s*/
	0xC079B265, /*prop_beach_fire*/
	0xE8032E4, /*prop_weed_pallet*/
	0x8973A868, /*prop_air_bigradar*/
	0x8E8C7A5B, /*prop_crashed_heli*/
	0xBD8AE007, /*prop_space_pistol*/
	0x6F9939C7, /*prop_ld_toilet_01*/
	0x4B3D240F, /*prop_wheelchair_01*/
	0x961CCC04, /*prop_cs_trolley_01*/
	0xE3BA450, /*Xmas Tree*/
	0x7121AC4, /*Large Xmas Tree*/
	0xB7C30A72,/*prop_tv_06*/
	0xF0A61994, /*prop_bong_01*/
	0xED2E79F0, /*prop_cs_ice_locker*/
	0x37FDC243, /*prop_mp_cone_01*/
	0x35AE1F39, /*prop_air_stair_03*/
	0xF7FCF988, /*prop_bank_vaultdoor*/
	0xE0264F5D,/*prop_roadcone01a*/
	0x6B795EBC, /*prop_alien_egg_01*/
	0x1405669B, /*prop_boxing_glove_01*/
	0x671C5C38, /*prop_boombox_01*/
	0xE6CB661E, /*prop_cs_dildo_01*/
	0xE2BA016F, /*prop_cs_katana_01*/
	0xEE95F258, /*prop_wheel_01*/
	0x52660DBB, /*prop_car_seat*/
	0xC89630B8, /*prop_minigun_01*/
	0xD733DF, /*root_scroll_anim_skel*/
	0xFA686C0E, /*prop_bin_04a*/
	0xF830B63E, /*prop_swiss_ball_01*/
	0xF3565180,/*prop_cs_meth_pipe*/
	0xF15FB3DD,/*prop_beggers_sign_01*/
	0xF046EA37,/*prop_gold_bar*/
	0xEFC4165A, /*prop_food_van_01*/
	0xEDA96F47,/*prop_distantcar_night*/
	0xEB7D0265,/*prop_golf_bag_01b*/
	0xE92E717E,/*prop_carwash_roller_vert*/
	0xE8E8AADA,/*prop_skip_01a*/
	0xE44D5CEC,/*prop_cash_crate_01*/
	0xE3CE09E2, /*prop_dummy_plane*/
	0xE1C17F6F,/*prop_kayak_01*/
	0xD541462D, /*p_ld_soc_ball_01*/
	0xD44295DD, /*p_cablecar_s*/
	0xCB74FE41,/*prop_roller_car_02*/
	0xCB290EE2,/*prop_fbibombplant*/
	0xC79A987E,/*prop_beach_volball01*/
	0xC54C0CD2,/*prop_huge_display_01*/
	0xC381B3E6,/*prop_lifeblurb_02*/
	0xC2451209,/*prop_air_lights_02a*/
	0xC20633F4,/*prop_cup_saucer_01*/
	0xBE862050, /*prop_portacabin01*/
	0xBB314853,/*prop_player_gasmask*/
	0xB60A04EC,/*prop_water_corpse_01*/
	0xB58BE281,/*prop_byard_rowboat1*/
	0xB58259BD,/*prop_security_case_01*/
	0xB39B99E2,/*prop_jet_bloodsplat_01*/
	0xB321DD82,/*prop_cs_leg_chain_01*/
	0xB21C3926,/*prop_hose_2*/
	0xB20E5785, /*prop_sculpt_fix*/
	0xB155FD87,/*prop_entityxf_covered*/
	0xB155B61D,/*prop_drop_armscrate_01*/
	0xA9BD0D16, /*prop_coke_block_01*/
	0xA67C935F,/*prop_bowling_pin*/
	0xA50DDDD0, /*prop_bball_arcade_01*/
	0xA22CEA2,/*prop_cs_bowie_knife*/
	0x9C762726, /*prop_lev_des_barge_02*/
	0x98752042,/*prop_ld_fan_01_old*/
	0x97A58869,/*prop_inflatearch_01*/
	0x927A5723, /*prop_fan_01*/
	0x922C2A43, /*prop_big_shit_01*/
	0x8E146BFF,/*prop_ld_monitor_01*/
	0x8DA1C0E, /*Orange Ball?*/
	0x8AF58425, /*prop_lev_des_barge_01*/
	0x8A451C5C,/*prop_ferris_car_01*/
	0x84898EFE,/*prop_big_shit_02*/
	0x7FFBC1E2, /*prop_dummy_01*/
	0x7F2B2371,/*prop_ld_fireaxe*/
	0x72F54E90,/*prop_jb700_covered*/
	0x72C8A3FB,/*prop_ld_shovel*/
	0x6F204E3A,/*prop_sprink_golf_01*/
	0x6B5FFA1D,/*prop_gravetomb_01a*/
	0x6AD326C2, /*prop_space_rifle*/
	0x699C8FC0,/*prop_ld_bomb_anim*/
	0x678FC2DB, /*prop_wheelchair_01_s*/
	0x60F90AD4,/*prop_cs_heist_bag_02*/
	0x5C1D75A6,/*prop_chair_05*/
	0x5B5C4263, /*prop_chip_fryer*/
	0x5A6DF96A,/*prop_hockey_bag_01*/
	0x58D3B4EA, /*prop_micro_01*/
	0x5869A8F8, /*prop_large_gold*/
	0x5571173D, /*prop_beer_neon_01*/
	0x5411322E,/*prop_ld_haybail*/
	0x532B1DD1, /*prop_rub_trolley01a*/
	0x50A607D0,/*prop_buck_spade_08*/
	0x4DA19524,/*prop_cs_cardbox_01*/
	0x4AF9D1D9,/*prop_shamal_crash*/
	0x478A8882,/*prop_rad_waste_barrel_01*/
	0x456AA864, /*prop_dj_deck_01*/
	0x434BFB7C,/*prop_burgerstand_01*/
	0x40F52369, /*p_v_43_safe_s*/
	0x3DC31836, /*prop_tv_flat_01*/
	0x3C3B89F0,/*prop_cs_bin_01_skinned*/
	0x39885BB5, /*prop_chickencoop_a*/
	0x392D62AA, /*prop_gold_cont_01*/
	0x37D80B0E,/*prop_cheetah_covered*/
	0x369D8410,/*prop_el_guitar_02*/
	0x34D5D3FD, /*prop_golf_bag_01*/
	0x2BE688E0,/*prop_dock_bouy_2*/
	0x2AE13DFA, /*prop_armchair_01*/
	0x29E362FF,/*prop_bucket_01a*/
	0x29CB0F3C, /*prop_armour_pickup*/
	0x240D3E4B,/*prop_pizza_box_01*/
	0x1F811CE1,/*prop_drug_package*/
	0x1F550C17, /*prop_chair_01a*/
	0x1D8A4162,/*prop_hotel_clock_01*/
	0x1AFA6A0A, /*prop_weed_01*/
	0x1AB39621,/*prop_lawnmower_01*/
	0x16A39A90, /*prop_dog_cage_01*/
	0x14E3D6EB, /*prop_inflategate_01*/
	0x113FD533,/*prop_money_bag_01*/
	0x0E8032E4, /*prop_weed_pallet*/
	0x0E3BA450, /*prop_xmas_tree_int*/
	0x07121AC4, /*prop_xmas_ext*/
	0x9F984011,
};
Entity infamousTarget, EffectTimer;
Entity DummyInfamous;
Entity DummyIronman;
Hash ModelHash = 0;
RGBA Carneon = { 255, 0, 0 };

Entity DragonFireCamera, FireAutoTarget, Core, Body, RedLamp, Stick, Stick2, Stick3, Stick4, Propeller, Propeller2, Propeller3,
Propeller4, minigun01, PedClone, Hoverboard, VehicleBackup, HulkEgg, Target2, Target3;
Entity AnimOB;
bool TeleAni;
bool TeleAni2;
bool TeleAni3;
Entity CAMERAAnim;
Vector3Int CustomTelep;
