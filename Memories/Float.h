float menuXCoord = 0.845f, textXCoord = 0.743f, optioncountx = 0.940f, GlareX = 1.151f, SubTitleXCoord = 0.743f,
OnOffX = 0.941f, charText = 0.9460f, charText1 = 0.950f, SubmenuThingX1 = 0.948f, SubmenuThingX2 = 0.940f,
LeftFade = 0.9625f, RightFade = 0.727f, charArrows = 0.939f, SideBoxLine = 0.736f, SideBox = 0.630f,
MiddleLines = 0.628f, LeftInfoText = 0.526f, LeftInfoResult = 0.624f, RightInfoText = 0.630f, MenuWidth = 0.21f, RightInfoResult = 0.729f;
float InfoBoxYMax = 0.702f;
float InfoBoxY = 0.666f;
float InfoBoxLineYMax = 0.1986f;
float InfoBoxLineY = 0.164f;
float FadeY = 0.1185f;
float GlareY = 0.482f;
float Glarewidth = 0.90f;
float Glareheight = 0.90f;
float checky = 0.173f;
float OOO = 0.000f;                         //右寄り設定時のWrap設定
float LLL = 0.9770f;                        //右寄り設定時のWrap設定
float SuperRun_ = 1.2f;
float RightJusty = 0.8000f;                 //右寄り
float msgXcoord = 0.2260f;
float msgYcoord = 0.630f;
float msgWindow[4] = {0.3700, 0.7799, 0.2999, 0.3100};
float textYCoord = 0.160f;
float Draw_Fps_X = 0.2260f, Draw_Fps_Y = 0.6058f;
float DropPlusZ = 1.0f;
float PlayerCoord[3] = { 2215.608f, -3734.883f, 5 };
float Floor[3] = { 2215.608f, -3734.883f, 2.84708f };
float Fence[3] = { 2218.263f, -3734.883f, 4.007766f };
float ESPX = 0.4300f, ESPY = 0.9400f;
float x = 0.0, y = 0.0, z = 0.0, heading = 0.0;
float rotx = 0.0, roty = 0.0, rotz = 0.0;
float FireRot = 0.0, FireZCoords = 0.0, FireSize = 0.0;
float gGlareDir;
float ___A, ___B, ___C;
float distanceFromCam = 3.0; 
float FloatZ_DriveOnWater = 14;
float Movement = 1;
float VCTalkerX = 0.025;

float FlashRun_Z;

float SuperRunSpeed;
float hydro = 3.0;
Vector3 AttachVector3[40];
Vector3 AttachRot[40];
float ZoomVar = 100.0f;
Vector3 ObjectSpawn_Manager_Location_Loc;
Vector3 ObjectSpawn_Manager_Location_Rot;
float conv360(float base, float min, float max)
{
	float fVar0;
	if (min == max) return min;
	fVar0 = max - min;
	base -= round(base - min / fVar0) * fVar0;
	if (base < min) base += fVar0;
	return base;
}

Vector3 PlusVector, PlusVector2, PlusVector3, PlusVector4;
Vector3 MinusVector, MinusVector2, MinusVector3, MinusVector4;
Vector3 FIRE_BREATH = { 0, 0.2380, 0.0 };
Vector3 M_Coord;
Vector3 M_Rot;
Vector3 _Attach_Loc;
Vector3 _Attach_Rot;
float ParachuteSpeed;
float DriveSpeedModifier_float = 20;
float StopSpeedModifier_float = 20;