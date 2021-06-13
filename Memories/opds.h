#pragma once
#define ADDR(x) {x,TOC};
uint32_t TOC = 0x1C85330;

#pragma region OPD_s
int GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS = 0x3AC394;
int GET_PED_LAST_WEAPON_IMPACT_COORD = 0x468ED0;
OPD_s is_player_online_OPD_s;
OPD_s does_entity_exist_OPD_s;
OPD_s get_entity_coords_OPD_s;
OPD_s get_entity_rotation_OPD_s;
OPD_s GET_GAMEPLAY_CAM_ROT_OPD_s;
OPD_s START_NEW_SCRIPT_OPD_s;

OPD_s GET_GAMEPLAY_CAM_COORD_OPD_s;
OPD_s IS_PS3_VERSION_OPD_s;
OPD_s IS_PC_VERSION_OPD_s;
OPD_s IS_XBOX360_VERSION_OPD_s;
OPD_s NETWORK_IS_IN_SESSION_OPD_s;
OPD_s GET_ENTITY_FORWARD_VECTOR_OPD_s;
OPD_s GET_ENTITY_SPEED_VECTOR_OPD_s;
OPD_s IS_BIT_SET_OPD_s;
OPD_s IS_AN_ENTITY_OPD_s;
OPD_s IS_MODEL_VALID_OPD_s;
OPD_s IS_TENNIS_MODE_OPD_s;
OPD_s GET_CAM_ROT_OPD_s;
OPD_s GET_CAM_COORD_OPD_s;
OPD_s GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_OPD_s;
OPD_s GET_PED_LAST_WEAPON_IMPACT_COORD_OPD_s;
OPD_s GET_PED_BONE_COORDS_OPD_s;
OPD_s GET_PED_LAST_WEAPON_IMPACT_COORD_s;
OPD_s GET_PED_BONE_COORDS_s;
OPD_s GET_SHAPE_TEST_RESULT_s;
OPD_s GET_MAX_WANTED_LEVEL_t;
OPD_s GET_SHAPE_TEST_RESULT_t = { 0x429A38, 0x1C85330 }; //0x9B87A0
OPD_s _START_SHAPE_TEST_RAY_s;
OPD_s _START_SHAPE_TEST_RAY_t = { 0x428E80, 0x1C85330 }; //0x9B87A0
OPD_s HAS_ACHIEVEMENT_BEEN_PASSED_s = { 0x4245BC ,0x1C85330 };
OPD_s GIVE_ACHIEVEMENT_TO_PLAYER_s = { 0x424590 ,0x1C85330 };
OPD_s shoot_single_bullet_between_coords_t;
OPD_s get_offset_from_entity_in_world_coords_t = { GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS , 0x0 };
OPD_s get_ped_last_weapon_impact_coord_t = ADDR(GET_PED_LAST_WEAPON_IMPACT_COORD);

OPD_s GET_PED_LAST_WEAPON_IMPACT_COORD_t = { 0x468ED0, 0x1C85330 }; //0x9B87A0
OPD_s set_input_exlcusive_t;//
OPD_s ATTACH_CAM_TO_ENTITY_t = { 0x3A4134 , 0x0 };
OPD_s IS_ENTITY_IN_WATER_t = { 0x3AE138 ,0x0 };
OPD_s HAS_ENTITY_COLLIDED_WITH_ANYTHING_t = { 0x3AAC7C ,0x0 };
OPD_s GET_BLIP_COORDS_t = { 0x0,0x0 };
OPD_s GET_GROUND_Z_FOR_3D_COORD_t = { 0x3D4620,0x0 };
#pragma endregion

#pragma region Functions
Vector3(*get_offset_from_entity_in_world_coords2)(int VehID, float* coords) = (Vector3(*)(int, float* coords))&get_offset_from_entity_in_world_coords_t;
Vector3(*get_entity_coords_orig)(uint32_t, uint32_t) = (Vector3(*)(uint32_t, uint32_t))&get_entity_coords_OPD_s;
Vector3(*get_entity_rotation_orig)(uint32_t, int) = (Vector3(*)(uint32_t, int))&get_entity_rotation_OPD_s;
Vector3(*GET_GAMEPLAY_CAM_ROT_orig)(uint32_t) = (Vector3(*)(uint32_t))&GET_GAMEPLAY_CAM_ROT_OPD_s;
Vector3(*GET_GAMEPLAY_CAM_COORD_orig)() = (Vector3(*)())&GET_GAMEPLAY_CAM_COORD_OPD_s;
Vector3(*GET_ENTITY_FORWARD_VECTOR_orig)(uint64_t) = (Vector3(*)(uint64_t))&GET_ENTITY_FORWARD_VECTOR_OPD_s;
Vector3(*GET_ENTITY_SPEED_VECTOR_orig)(uint64_t, uint64_t) = (Vector3(*)(uint64_t, uint64_t))&GET_ENTITY_SPEED_VECTOR_OPD_s;
Vector3(*GET_CAM_ROT_orig)(uint64_t, uint64_t) = (Vector3(*)(uint64_t, uint64_t))&GET_CAM_ROT_OPD_s;
Vector3(*GET_CAM_COORD_orig)(uint64_t) = (Vector3(*)(uint64_t))&GET_CAM_COORD_OPD_s;
Vector3(*GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_orig)(uint64_t, float*) = (Vector3(*)(uint64_t, float*))&GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_OPD_s;
Vector3(*GET_PED_BONE_COORDS_orig)(uint32_t, uint32_t, int, int, int) = (Vector3(*)(uint32_t, uint32_t, int, int, int))&GET_PED_BONE_COORDS_OPD_s;
Vector3(*GET_BLIP_COORDS_orig)(uint32_t) = (Vector3(*)(uint32_t))&GET_BLIP_COORDS_t;
Vector3(*GET_PED_BONE_COORDS)(Ped, int, float, float, float) = (Vector3(*)(Ped, int, float, float, float))&GET_PED_BONE_COORDS_s;

BOOL(*is_ps3_version_orig)() = (BOOL(*)())&IS_PS3_VERSION_OPD_s;
BOOL(*is_pc_version_orig)() = (BOOL(*)())&IS_PC_VERSION_OPD_s;
BOOL(*is_xbox360_version_orig)() = (BOOL(*)())&IS_XBOX360_VERSION_OPD_s;
BOOL(*NETWORK_IS_IN_SESSION_orig)() = (BOOL(*)())&NETWORK_IS_IN_SESSION_OPD_s;
BOOL(*is_bit_set_orig)(uint64_t, uint64_t) = (BOOL(*)(uint64_t, uint64_t))&IS_BIT_SET_OPD_s;
BOOL(*is_an_entity_orig)(uint64_t) = (BOOL(*)(uint64_t))&IS_AN_ENTITY_OPD_s;
BOOL(*is_model_valid_orig)(Hash) = (BOOL(*)(Hash))&IS_MODEL_VALID_OPD_s;
BOOL(*is_tennis_mode_orig)(uint64_t) = (BOOL(*)(uint64_t))&IS_MODEL_VALID_OPD_s;

bool(*get_ped_last_weapon_impact_coord)(int ped, Vector3* out) = (bool(*)(int, Vector3*))&get_ped_last_weapon_impact_coord_t;
bool(*__GET_PED_LAST_WEAPON_IMPACT_COORD)(int ped, Vector3* Co) = (bool(*)(int, Vector3*))&GET_PED_LAST_WEAPON_IMPACT_COORD_t;
bool(*HAS_ACHIEVEMENT_BEEN_PASSED_orig)(int i) = (bool(*)(int i))&HAS_ACHIEVEMENT_BEEN_PASSED_s;
bool(*HAS_ENTITY_COLLIDED_WITH_ANYTHING)(int entity) = (bool(*)(int))&HAS_ENTITY_COLLIDED_WITH_ANYTHING_t;// 0x8BAD02F0368D9E14 0x662A2F41
bool(*is_entity_in_water)(int entity) = (bool(*)(int))&IS_ENTITY_IN_WATER_t;
bool(*GET_GROUND_Z_FOR_3D_COORD_orig)(float, float, float, float*) = (bool(*)(float, float, float, float*))&GET_GROUND_Z_FOR_3D_COORD_t;


void(*set_input_exlcusive)(int p1, int p2) = (void(*)(int, int))&set_input_exlcusive_t;
void(*ATTACH_CAM_TO_ENTITY)(int cam, int entity, float xOffset, float yOffset, float zOffset, bool p5) = (void(*)(int, int, float, float, float, bool))&ATTACH_CAM_TO_ENTITY_t;// 0xFEDB7D269E8C60E3 0xAD7C45F6
void(*shoot_single_bullet_between_coords2)(float* start, float* end, int _999, int zero, int hashweapon, int PedAttacker, int one, int _one, float speed) = (void(*)(float* start, float* end, int, int, int, int, int, int, float))&shoot_single_bullet_between_coords_t;

int(*GIVE_ACHIEVEMENT_TO_PLAYER_orig)(int i) = (int(*)(int i))&GIVE_ACHIEVEMENT_TO_PLAYER_s;
int(*is_player_online_orig)() = (int(*)())&is_player_online_OPD_s;
int(*does_entity_exist_orig)(uint32_t) = (int(*)(uint32_t))&does_entity_exist_OPD_s;
int(*_START_SHAPE_TEST_RAY_orig)(float, float, float, float,float, float, int, Entity, int) = (int(*)(float, float, float, float, float, float, int, Entity, int))&_START_SHAPE_TEST_RAY_s;
int(*GET_SHAPE_TEST_RESULT_orig)(int, BOOL *, Vector3 *,Vector3 *,Entity *) = (int(*)(int, BOOL *, Vector3 *, Vector3 *, Entity *))&GET_SHAPE_TEST_RESULT_s;

int(*GET_MAX_WANTED_LEVEL_orig)() = (int(*)())&GET_MAX_WANTED_LEVEL_t;
#pragma endregion









