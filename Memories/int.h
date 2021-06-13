#pragma region Menu Color
int bannerTextRed = 255;
int bannerTextGreen = 255;
int bannerTextBlue = 255;
int bannerTextOpacity = 255;
int bannerTextFont = 7;
RGBA bannerRect = { 50, 100, 255, 120 };
RGBA bannerRect1 = { 255, 0, 255, 120 };
int bannerRectRed = 50;
int bannerRectGreen = 100;
int _playerwanted = 5;
int UIIndex;
RGBA _UIGETRGBA[224];
int SpectatormodePlayer;
int _SetPlayerWantedVar;
int _SetUIcolorvar[10];
int _SetMaxPlayerWantedVar;
int _GiveMoneyVar = 10000000;
int _GiveMoneyVar2 = 10000000;
int _SetPlayerWantedIndex;
int _SetPlayerWantedTimer;
int _ChatTimer;
int _UnknownCarIndex;
int _UnknownCar_car[15];
int bannerRectBlue = 255;
int bannerRectRed1 = 255;
int bannerRectGreen1 = 0;
int bannerRectBlue1 = 255;
int backgroundRed = 16;
int backgroundGreen = 16;
int backgroundBlue = 16;
int backgroundOpacity = 110;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 0;
int scrollerRed = 46;
int scrollerGreen = 186;
int scrollerBlue = 255;
int scrollerOpacity = 100;
int indicatorRed = 255;
int indicatorGreen = 44;
int indicatorBlue = 55;
int indicatorOpacity = 255;
#pragma endregion

int PlayerListIndexes[18];

int CargoBobInt;

RGBA ESP_COLOR = { 6, 200, 5, 255 };
/*Hash*/
Hash WepArray[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B,
0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x5FC3C11, 0xC472FE2,
0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0xA0973D5E, 0x24B17070, 0x60EC506, 0x34A67B97, 0x23C9F95C,
0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xD205520E, 0xBFD21232, 0x92A27487, 0x83839C4, 0xA89CB99E, 0xC0A3098D, 0x7F229F94, 0x7F7497E5, 0x787F0BB, 0xAB564B93,
0x63AB0442, 0x47757124, 0xA3D4D34, 0x3AABBBAA, 0xC734385A, 0xA3D4D34, 0xDC4DB296 };

/*地球描画関係*/
int mov;
int gGlareHandle;
int vctalkerindex;
int vctalkertimer2;

/*項目のオプション数を格納する場所*/
int optionCount = 0;

int godmodebackup[2];

int AirRaceIndex;
int AirRaceInt[100];

/*LSC Race*/
int LSCRaceIndex;
int LSCRaceInt[100];

int moddedmule_moto;
int moddedmule_index;
int moddedmule[5];

/*Pengin*/
int PenginIndex;
int Pengin_moto;
int Pengin_Spawned[10];

int PenginIndex_;
int Pengin_moto_;
int Pengin_Spawned_[10];

/*メニュー*/
int submenu = 0;
int currentOption = 0;
int maxOptions = 16;
int lastSubmenu[20];
int lastOption[20];
int submenuLevel = 0;
int instructCount;
int BOTTOMTEXT;
int MISSIONCOMP;
int controlJustPressedTimeout = 0;
int PlayerInfoTimer;
int MenuInfoTimer;
int __PlayerList[18];
int COLORED_ESP_VAR;


/*キーボード*/
int keyboardAction = 0;
int *keyboardIntVar = 0;
float *keybordFloatVar = 0;

/*プレイヤー*/
int selectedPlayer;
int ESize;
int AutoHost;

/*全てノプレイヤー*/
int TimerDelay[16];
int ESPVar = 1;
int WeatherVar;
int TimerVar;

/*Vehicle Option*/
int JetPackOB;
int VehJetpackHoverToggle;
int VehJetpackToggle;
int VehJetpackPTFXTimer;
int SpawnedEntityList[40];
int SpawnedEntityIndex;
int DriveOnWaterOBJ;
int SpawnedSelectedEntity;
int __INNOVATION;
int __AAA;
int __Fire;
int __EMP;
int RideonSpeed;
int SpeedometerPreviousSpeed;
int RideonAnimalsPedID;
float ACC;
int SpeedometerPreviousGameTime;
int ColorVarTaiyakon;
RGBA RED = { 255, 0, 0, 255 };
RGBA GREEN = { 0, 255, 0, 255 };
RGBA BLUE = { 0, 0, 255, 255 };
RGBA YELLOW = { 255, 255, 0, 255 };
RGBA PURPLE = { 180, 0, 255, 255 };
RGBA LBLUE = { 0x9D, 0xCC, 0xE0, 255 };
int Create_Tank_int[2];
int Create_Tank_int_2[3];
Cam FarCamera;
int Galaxhip_index;
int Galaxhip_int[100];
int Galaxhip_moto;

/*Particle*/
int ParticlemanToggle;
int ParitcleManOB;
RGBA VehicleColor = {100, 0, 100};
int VehicleColorVar;
int ModdedSkyLift_Int[16];
Cam cameraHandle;
int timerdesu5;
int selectedVehicle;
int TeleID = 0, TeleID2 = 115, RenderTime2 = 3500, AlturaTeleport = 400, RenderTime = 3500;
int TooBigDump_int[100];
int TooBigDump_moto;
int TooBigDump_index;

/*Map*/
int LSCTroll_Int[6];
int Mountain_int[100];
int mountain2_int[100];
int mountain2_index;

/*Weapon MEnu*/
Entity Target;
int RapidFireDelay;
int Shot_To_Add_Timer;
int SelectedShotVehicleVar;
int VehicleGun_int;

/*Player Option*/
int PSNvar;
int Kicktypevar;
int CHANGEType;
int WeatherIndexes[] = { 0x1, 0xB, 0x0, 0x2, 0x8, 0x3, 0x9, 0x5, 0x6, 0x4, 0xA, 0xC, 0x7, -0x1 };
int ModdedWPvar;
int ColorMessageVar;
int selectedNamedPlayer;
int KillValue = 10000;
int DeathValue = 10000;
int RankUpValue = 100000;
int RankDownValue = 100000;
int CrewRankValue = 90000;
int ExplositonAttackVar;
int ExplosionAttackON[] = { EXPLOSION_BLIMP, EXPLOSION_CAR, EXPLOSION_STICKYBOMB, EXPLOSION_DIR_WATER_HYDRANT, EXPLOSION_DIR_FLAME, EXPLOSION_DIR_STEAM, EXPLOSION_MOLOTOV };
int PlayerExplosionVar;
int Freezing_V1_Timer;
int Freezing_V2_Timer;
int Freezing_V3_Timer;
int FreezingVehicle;
int RankVar = 120;
int _SpoofRankVar = 120;
int GodModeVar;
int _16BMX_Main[16];
int _16BMX_Index;
int _SquadPilotFly_int[6];
int _WoodedBoatInt_[3];
int LightningPanto_int[4];
int yanki_bike_int[3];
int senpuukicar_int[10];
Entity incer_e, tower_e, tower_e2, apart_e;
int IPADDRESS_TIMEOUT;
int SmallBigVar;
int do_Fence_Int[12];
int do_Fence_index;

/*Object*/
int AttachSelectvar;
int AttachBone_;
int PedBone_var;
int spawnedindex__;
Hash Create_Hash, Create_Hash_int;
int Create_Obj_Spawned;
int ObjectIndexes[30];
int TekitouOBJVar;

/*PlayerTEleport*/
int TPtoMevar;
int TPtoMePlayer;

/*Teleport*/
int WayIndex;
int WayTimer;
int VehicleTPTimer;
int VehicleTPEntity;
int VehicleTPIndex;

/*Model Change*/
int OnlineModelvar;
int ModelChangerHash;
int StoryModelVar;
int HumanModelVar;
int UniqueModelVar;
int BirdsModelVar;
int FishModelVar;
int DogModelVar;
int AnimalModelVar;

/*Entity*/
int MyCar;

/*Vehicle Spawn*/
int SpawnedVehicle[25];
int _SpawnedVehicle;
int SpawnVehMethod_Hash;
int PenisDeamon_int[2];
int PenisDeamon_moto;
int PenisDeamon_index;

/*Protection*/
int VehicleFreezeProtectionDelay;
int ClearAreaVehicleDelay;
int PARADISE_P_SUBTIMER;
int KICK_P_SUBTIMER;
int SCRIPT_P_SUBTIMER;
int KEIRYOU_P_SUBTIMER;

/*msginfobox*/
int msgindex;
int MsgOpa = 0x6A;
int MsgTimer;
int MsgOpacity;

/*Misc*/
int CServerTimer;
int ScrollTimer = 90;
int ScrollSpeedModifier = 1;

/*FunMenu*/
int FireTimer;
int timeoutMinecraft;
int distanceMinecraft = 6;
int DragonFire_Int[14];
int DragonFire_Blip;
int DragonFire_TargetEntity;
int DragonFire_ONToggle;
int ComeDragonFire_ON;
int DragonFireCameraResetToggle;
int DragonFire_Timer;

/* Particle */
int ParticleTimer[20];

/*Minecraft*/
int M_Hash;
int M_Spawned;
int M_DeletingTimer;
Entity M_obj;

/*Settings*/
int PlayerUIVar;
int LightningLoop_Timer;

/*Animation Menu*/
int WalktypeVar;
int AnimaType, AnimaTypeA, AnimaTypeS, AnimaTypeSI, AnimaTypeN, AnimaTypeM, AnimaTypeO;

/*Fps*/
int frameCache_time, frameCache_old, frameCache_new;

/*Recovery*/
int CharacterVar_;
int _1000KLoop_time;
int _FullHack_time;

/*Protection*/
int Low_TextureVar;
int ProtectionTimer = 1000;

int BearBearBearMoto;
int BearBearbear_int[100];
int BearBearBear_index;