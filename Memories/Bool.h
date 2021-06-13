bool _Test;
bool _AdminFlag;
bool fastInstruction;
bool lrInstruction;
bool xInstruction;
bool squareInstruction;
bool instructions = true;
bool instructionsSetupThisFrame;
bool optionPress = false;                //オプションが押されたかの判定。押されたらtrue
bool rightPress = false;                //十字の右が押されたかの判定
bool leftPress = false;                //十字の左が押されたかの判定
bool fastRightPress = false;                //十字の右が押されているかの判定
bool fastLeftPress = false;                //十字の右が押されているかの判定
bool squarePress = false;                //□ボタンが押されたかの判定
bool keyboardActive = false;                //キーボードを表示するフラグ
bool udInstruction;
bool checkPoolOffset = true;
bool OffLineFlag;
bool TitleGCMODE;
bool CreatorMode;
bool mensacar;
bool RCE_ChangeRank;
int RCE_ChangeRankVar = 5;
int RCE_ChangeRankIndex;
bool _playerwantedbool;
bool _setwantedbool;
bool TimeStopper;
bool MinecraftMode_2;
bool _unknownCar;
bool _playeruiIPADDRESS = true;

bool SpoofKasuAll[2] = { false, false };
int SpoofKasuIndex[2];
int SpoofKasuTimer[2];
bool taiyakonColor;
bool TireRainbow;
RGBA TireRainbow_ = {5, 180, 200};

/*Menu*/
bool hasBeenUsed;
bool rightpressing;
bool leftpressing;

/*Self Option*/
bool GodMode;
bool Invisible;
bool Nocops;
bool SuperJump;
bool SuperRun;
bool UltraPunch;
bool ExplosionMelee;
bool FireAmmo;
bool ExplosionAmmo;
bool RevealPeople;
bool OffRader;
bool CopsTurnBlindEye;
bool Noclip[2];
bool UltraRun;

/*Weapon Menu*/
bool DeleteGun;
bool InfAmmo0;
bool InfAmmo1;
bool MagnetGun;
bool VehicleGun;
bool VehicleGun_ShotFlag;
bool MoneyGunMe;
bool TeleportGunMe;

/*Online*/
bool GhostMode;
bool _SpoofRank;

/*Player_List*/
bool ESP_BOOL_[16];

/*Player_Option*/
bool PlayerUI;
bool IUI;
bool _GetHost;
bool Spectatormode;
bool MoneyFlag[16];
bool ParachuteFlag[16];
bool DropSnackFlag[16];
bool ModdedWeapon_var[16];
bool Message_Color_Bool;
bool Message_Spoof_Bool;
bool ExplosionName;
bool DriveOnWater;
bool Freezing_V1;
bool Freezing_V1_Time;

bool Freezing_V2;
bool Freezing_V2_Time;

bool Freezing_V3;
bool Freezing_V3_Time;
bool do_Fence;

/*Player_Option_Attach*/
bool _PlayerAttach;

bool kasamod;
int KASA;

bool Psychokinetic_v2;

bool ripley2;
int ripley2_moto;
int ripley2_int[2];
int ripley2_index;

/*Allplayer*/
bool ALL_PLAYER_40K;
bool ALL_ESP;
bool ALL_ANIMATION_KILL;
bool RemoveAllPlayerWanted;

/*Particle*/
bool ParticleMan;
bool Fly_ON;
bool effectp[20];

bool NoRagdoll;
bool PenginCar;
bool PenginCar2;

/*Object*/
bool ObjectUI;
bool _Is_Collision = true;
bool _HashGun;
bool Create_Map;
bool Create_Map_int;
bool _Is_FreezePosition;
bool Shot_to_add;
bool L3Boost_R3Stop;
bool R1Jumping;

/*Teleport*/
bool WaypointTeleport;
bool VehicleTP = true;
bool AnimTP = false;
bool TeleportPTFX;
bool Teleanim;
bool move1 = 0;
float PosX, PosY, PosZ;
bool TeleportCameraSelf;
bool TeleportEffect;
bool TPEffectBool;

/*Veh spawn*/
bool VehSpawnMethod;
bool MaxUpgrades;
bool TeleAutomIncar;
bool GhostRiderSpawn;
bool _16BMX;
bool _16BMX_2[16];
bool ModdedSkyLift;
bool VehicleSpawnBool[4];
bool WoodedBoat;
bool LightningPanto, yanki_bike;
bool senpuukicar;
bool cranetank;
bool cranetank2;
bool CameraFar;
bool Galaxhip;
bool TooBigDump;
bool PenisDeamon;

/*Vehicle Option*/
bool VehicleJetpack;
bool Hover_ON, VehJetpack_ON;
bool DriveOnWall;
int EffectsONOFF = 1;
bool ParticleFlying;
bool VehJetpackStop;
bool VehicleGodmode;
bool VehicleColor_Bool[3];
bool DriftL1;
bool DpadLeftCarFix;
bool SpawnedChrome;
bool SquadPilotFly;
bool taiyakonColor2;
bool TireRainbow2;

/*Model Change*/
bool ChangeModel;
bool _ChangeModel[2];

/*Protection Menu*/
bool PTFX_P;
bool TPANIM_P;
bool CTASK_P;
bool VEHCON_P;
bool WEAPON_P;
bool CLEARAREA_ALL;
bool VEHATTACH_P;
bool SCRIPT_P;
bool STATUS_P;
bool WEATHER_P;
bool KICK_P;
bool DETECTION_P;
bool PARADISE_P;
bool DETECTMENU_P;
bool PARADISE_P_SUB[2];
bool SCRIPT_P_SUB[2];
bool KICK_P_SUB[2];
bool PEDATTACH_P;
bool CLEARVEH_ALL;
bool Low_Tecture;
bool Low_TextureWater;
bool RCE_P;
bool MapDelete_;
bool AutoClearArea;
bool OBJECT_P;

/*Map*/
bool LSCTroll;
bool MountainRace;
bool MountainRace2;
bool AirRace;

/*Weapon Menu*/
bool _OneShot;
bool IsInAutoApply;
bool RapidFire;

/*Animation*/
bool WalkingChanger;
bool isUpperAnim;
bool SetPlayerAnimationForMe;
bool AnimFreezeMe;
bool SetPlayerAnimation;

/*Funmenu*/
bool breathfire;
bool CreateSoccer;
bool CreatorFlag[133];
bool FirstCreateFlag;
bool MinecraftMode;
bool MinecraftMode_Spawn;
bool M_Deleting;
bool RideonAnimal;
bool MoveAnimal;
bool ParachuteMod;
//bool DragonFire;
bool DragonFire_ON, CamChange_ON, DragonFire_Flymode;
bool SpawnDragonFireCam;
bool doAnimation;
bool SpawnedFlag_DragonFire;
bool DeleteDragonFireCam;
bool Attach_ON;

bool LSCRace;
bool moddedmule_;

bool ChatBypass;

/*Misc*/
bool View_FPS = true;
bool View_Session = true;
bool ninjam;
bool CServer;
bool BlackOut;
bool checkeWater;
bool DeleteWaterC;
bool isHDD;
bool OpacityWater;
bool _LoadIPL;
bool EnableAccountBool;
bool DeleteParachute;
bool LightningLoop;
bool testBool;
bool DeleteMenuID;
bool ChangeUIColor;
bool _UIGET;
/*Recovery*/
bool FullHack;
bool _1000KLoop;

/*Setting*/
bool msgindexflag = true;
bool _PlayerUI = true;
bool NAME_ESP;
bool DontViewLog;
bool VCTalker = true;
bool HackerView = true;
bool COLORED_ESP;
bool DontViewOpenMenu;
bool ViewPropName;

bool BearBearBear;
bool DriveSpeedModifier;
bool StopSpeedModifier;
bool CollisionCar;

bool MagnetCargo;