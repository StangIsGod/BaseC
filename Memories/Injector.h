//
//#pragma region ZeroMemories
//namespace DragonFire {
//	bool DragonFire;
//	bool CreateDragonFire;
//	bool DeleteDragonFire;
//	Entity BaseDragonFire;
//	Entity DragonFire1, DragonFire2, DragonFire3, DragonFire4, DragonFire5, DragonFire6, DragonFire7, DragonFire8, DragonFire9, DragonFire10, DragonFire11, DragonFire12, DragonFireMinigun_1;
//	
//	
//	
//	//bool CamChange_ON;
//	//bool DragonFire_FlyMode;
//
//	void ATTACH_ENTITY_TO_ENTITY2(int entity1, int entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool p9, bool isRelative, bool collision, bool allowRotation, int vertexIndex, bool fixedRot)// 0x6B9BBD38AB0796DF 0xEC024237
//	{
//		ENTITY::ATTACH_ENTITY_TO_ENTITY(entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, isRelative, collision, allowRotation, vertexIndex, fixedRot);
//	}
//
//	
//	
//}
//
//void Functions2()
//{
//	if (DragonFire::CreateDragonFire)
//	{
//		Vector3 PlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
//		int Basehash = GAMEPLAY::GET_HASH_KEY("prop_ld_test_01");
//		int hash = GAMEPLAY::GET_HASH_KEY("prop_cartwheel_01");
//		int hash2 = GAMEPLAY::GET_HASH_KEY("prop_telescope");
//		int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_05");
//		int hash4 = GAMEPLAY::GET_HASH_KEY("p_cctv_s");
//		int hash5 = GAMEPLAY::GET_HASH_KEY("hei_prop_wall_alarm_on");
//		int hash6 = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
//		REQUEST_MODEL(Basehash);
//		REQUEST_MODEL(hash);
//		REQUEST_MODEL(hash2);
//		REQUEST_MODEL(hash3);
//		REQUEST_MODEL(hash4);
//		REQUEST_MODEL(hash5);
//		REQUEST_MODEL(hash6);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire1))
//			DragonFire::DragonFire1 = OBJECT::CREATE_OBJECT(hash, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire2))
//			DragonFire::DragonFire2 = OBJECT::CREATE_OBJECT(hash, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire3))
//			DragonFire::DragonFire3 = OBJECT::CREATE_OBJECT(hash, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire4))
//			DragonFire::DragonFire4 = OBJECT::CREATE_OBJECT(hash, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire5))
//			DragonFire::DragonFire5 = OBJECT::CREATE_OBJECT(hash2, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire6))
//			DragonFire::DragonFire6 = OBJECT::CREATE_OBJECT(hash2, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire7))
//			DragonFire::DragonFire7 = OBJECT::CREATE_OBJECT(hash2, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire8))
//			DragonFire::DragonFire8 = OBJECT::CREATE_OBJECT(hash2, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire9))
//			DragonFire::DragonFire9 = OBJECT::CREATE_OBJECT(hash3, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire10))
//			DragonFire::DragonFire10 = OBJECT::CREATE_OBJECT(hash3, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire11))
//			DragonFire::DragonFire11 = OBJECT::CREATE_OBJECT(hash4, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire12))
//			DragonFire::DragonFire12 = OBJECT::CREATE_OBJECT(hash5, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFireMinigun_1))
//			DragonFire::DragonFireMinigun_1 = OBJECT::CREATE_OBJECT(hash6, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		if (!ENTITY::DOES_ENTITY_EXIST(DragonFire::BaseDragonFire))
//			DragonFire::BaseDragonFire = OBJECT::CREATE_OBJECT(Basehash, PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, true, true, false);
//
//		int bone = PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 24818);
//
//		if (ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire1) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire2) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire3) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire4) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire5) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire6) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire7) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire8) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire9) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire10) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire11) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFire12) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::DragonFireMinigun_1) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire::BaseDragonFire)
//			)
//		{
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire1, DragonFire::BaseDragonFire, bone, -1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire2, DragonFire::BaseDragonFire, bone, 1.0, 1.0, 0.3, 0.0, 0.0, 0.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire3, DragonFire::BaseDragonFire, bone, -1.0, -1.0, 0.3, 0.0, 0.0, 0.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire4, DragonFire::BaseDragonFire, bone, 1.0, -1.0, 0.3, 0.0, 0.0, 0.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire5, DragonFire::BaseDragonFire, bone, 0.1, 0.1, -0.3, -70.0, 0.0, 50.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire6, DragonFire::BaseDragonFire, bone, -0.1, 0.1, -0.3, -70.0, 0.0, -50.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire7, BaseDragonFire, bone, 0.1, -0.1, -0.3, -70.0, 0.0, 130.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire8, BaseDragonFire, bone, -0.1, -0.1, -0.3, -70.0, 0.0, -130.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire9, BaseDragonFire, bone, 0.0, 0.3, -0.55, 0.0, 0.0, 90.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire10, BaseDragonFire, bone, 0.0, -0.3, -0.55, 0.0, 0.0, 90.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire11, BaseDragonFire, bone, 0.0, 0.7, -0.2, 0.0, 0.0, 180.0, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFire12, BaseDragonFire, bone, 0.0, -0.65, -0.25, 0.0, 0.0, 180, 1, 0, 0, 0, 2, 1);
//			DragonFire::ATTACH_ENTITY_TO_ENTITY2(DragonFire::DragonFireMinigun_1, BaseDragonFire, bone, 0.0, 1.0, -0.5, 0.0, 0.0, 90.0, 1, 0, 0, 0, 2, 1);
//		}
//
//		DragonFire::CreateDragonFire = false;
//	}
//
//	if (DragonFire::DeleteDragonFire)
//	{
//		if (ENTITY::DOES_ENTITY_EXIST(DragonFire1) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire2) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire3) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire4) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire5) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire6) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire7) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire8) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire9) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire10) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire11) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFire12) &&
//			ENTITY::DOES_ENTITY_EXIST(DragonFireMinigun_1) &&
//			ENTITY::DOES_ENTITY_EXIST(BaseDragonFire)
//			)
//		{
//			ENTITY::DETACH_ENTITY(DragonFire1, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire2, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire3, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire4, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire5, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire6, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire7, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire8, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire9, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire10, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire11, false, false);
//			ENTITY::DETACH_ENTITY(DragonFire12, false, false);
//			ENTITY::DETACH_ENTITY(DragonFireMinigun_1, false, false);
//			ENTITY::DELETE_ENTITY(&DragonFire1);
//			ENTITY::DELETE_ENTITY(&DragonFire2);
//			ENTITY::DELETE_ENTITY(&DragonFire3);
//			ENTITY::DELETE_ENTITY(&DragonFire4);
//			ENTITY::DELETE_ENTITY(&DragonFire5);
//			ENTITY::DELETE_ENTITY(&DragonFire6);
//			ENTITY::DELETE_ENTITY(&DragonFire7);
//			ENTITY::DELETE_ENTITY(&DragonFire8);
//			ENTITY::DELETE_ENTITY(&DragonFire9);
//			ENTITY::DELETE_ENTITY(&DragonFire10);
//			ENTITY::DELETE_ENTITY(&DragonFire11);
//			ENTITY::DELETE_ENTITY(&DragonFire12);
//			ENTITY::DELETE_ENTITY(&DragonFireMinigun_1);
//			ENTITY::DELETE_ENTITY(&BaseDragonFire);
//			UI::REMOVE_BLIP(DragonFire_Blip);
//		}
//	}
//}
//#pragma endregion
//
//namespace NetworkObj
//{
//	OPD_s entityToIndex_t = { 0x474054, TOC };
//	int(*entityToIndex)(int r3) = (int(*)(int))&entityToIndex_t;
//	int g_SpamManager[3][6];
//	int g_ForceControlEntity = 0; //dont need bc need hook but idk what addr is to hook
//
//	void NetworkPools() {
//		if (NETWORK::NETWORK_IS_IN_SESSION()) {
//			CNetGenericPool* networkObjectPool = (CNetGenericPool*)(*(int*)(0x1CF7640)); //
//			CNetGenericPool* networkPickupPool = (CNetGenericPool*)(*(int*)(0x1CF76A4)); //
//			CNetGenericPool* networkPedPool = (CNetGenericPool*)(*(int*)(0x1CF7654)); //
//			CNetGenericPool* networkVehiclePool = (CNetGenericPool*)(*(int*)(0x1CF7674)); //
//
//			if ((int)networkObjectPool != 0) {
//				if (networkObjectPool->m_PoolStart != 0) {
//					for (int i = 0; i < networkObjectPool->m_MaxItems; i++) {
//						if (*(int*)((networkObjectPool->m_PoolStart + (i * networkObjectPool->m_ItemSize))) == 0x1934EF0 && *(int*)((networkObjectPool->m_PoolStart + (i * networkObjectPool->m_ItemSize)) + 0x2C) != 0) {
//							CObject* objectStruct = (CObject*)(*(int*)((networkObjectPool->m_PoolStart + (i * networkObjectPool->m_ItemSize)) + 0x2C));
//							int objectScriptIndex = entityToIndex(*(int*)((networkObjectPool->m_PoolStart + (i * networkObjectPool->m_ItemSize)) + 0x2C));
//
//							if (ENTITY::DOES_ENTITY_EXIST(objectScriptIndex)) {
//								if (objectStruct->m_ModelInfo->m_ModelHash == 0xa50dddd0) {
//									if (g_SpamManager[0][0] == 5) {
//										for (int j = 1; j < 6; j++) {
//											//g_ForceControlEntity = g_SpamManager[0][i];
//											if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(g_SpamManager[0][i])) {
//												ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectScriptIndex, true, true);
//												ENTITY::DELETE_ENTITY(&g_SpamManager[0][i]);
//												//g_ForceControlEntity = 0;
//											}
//										}
//										PrintNotification(ENFORCER_ALERT, "Someone tried to crash you with basketballs.");
//										g_SpamManager[0][0] = 0;
//									}
//									else
//										g_SpamManager[0][g_SpamManager[0][0]++] = objectScriptIndex;
//								}
//								if (objectStruct->m_ModelInfo->m_ModelHash == 0x6b795ebc) {
//									if (g_SpamManager[1][0] == 5) {
//										for (int j = 1; j < 6; j++) {
//											//g_ForceControlEntity = g_SpamManager[1][i];
//											if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(g_SpamManager[1][i])) {
//												ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectScriptIndex, true, true);
//												ENTITY::DELETE_ENTITY(&g_SpamManager[1][i]);
//												//g_ForceControlEntity = 0;
//											}
//										}
//										PrintNotification(ENFORCER_ALERT, "Someone tried to crash you with alien eggs.");
//										g_SpamManager[1][0] = 0;
//									}
//									else
//										g_SpamManager[1][g_SpamManager[1][0]++] = objectScriptIndex;
//								}
//
//
//								if (objectStruct->m_ModelInfo->m_ModelHash == 0xa50dddd0 /*BASKETBALL HASH*/) { // INDIVIDUAL HASH CHECK
//																												//g_ForceControlEntity = objectScriptIndex;
//									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(objectScriptIndex)) {
//										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectScriptIndex, true, true);
//										ENTITY::DELETE_ENTITY(&objectScriptIndex);
//										//g_ForceControlEntity = 0;
//										PrintNotification(ENFORCER_ALERT, "Someone tried to spawn a freeze object.");
//									}
//								}
//
//								if (STREAMING::IS_MODEL_A_VEHICLE(objectStruct->m_ModelInfo->m_ModelHash)) { // VEHICLE HASH CHECK
//																											 //g_ForceControlEntity = objectScriptIndex;
//									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(objectScriptIndex)) {
//										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectScriptIndex, true, true);
//										ENTITY::DELETE_ENTITY(&objectScriptIndex);
//										//g_ForceControlEntity = 0;
//										PrintNotification(ENFORCER_ALERT, "Someone tried to spawn a vehicle freeze object.");
//									}
//
//								}
//
//								if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(PLAYER::PLAYER_PED_ID(), objectScriptIndex)) { // OBJECT REATTACH
//																														//g_ForceControlEntity = objectScriptIndex;
//									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(objectScriptIndex)) {
//										ENTITY::DETACH_ENTITY(objectScriptIndex, false, false);
//										//g_ForceControlEntity = 0;
//										PrintNotification(ENFORCER_ALERT, "Someone tried to attach an object to your player.");
//									}
//								}
//							}
//						}
//					}
//					g_SpamManager[0][0] = 0; // RESET SPAM MANAGER COUNTS HERE
//					g_SpamManager[1][0] = 0; // RESET SPAM MANAGER COUNTS HERE
//				}
//			}
//			if ((int)networkPickupPool != 0) {
//				if (networkPickupPool->m_PoolStart != 0) {
//					for (int i = 0; i < networkPickupPool->m_MaxItems; i++) {
//						if (*(int*)((networkPickupPool->m_PoolStart + (i * networkPickupPool->m_ItemSize))) == 0x19382E0 && *(int*)((networkPickupPool->m_PoolStart + (i * networkPickupPool->m_ItemSize)) + 0x2C) != 0) {
//							CPickup* pickupStruct = (CPickup*)(*(int*)((networkPickupPool->m_PoolStart + (i * networkPickupPool->m_ItemSize)) + 0x2C));
//							int pickupScriptIndex = entityToIndex(*(int*)((networkPickupPool->m_PoolStart + (i * networkPickupPool->m_ItemSize)) + 0x2C));
//							if (pickupStruct->m_PickupData->m_NameHash == 0xCE6FDD6B) {
//								//g_ForceControlEntity = pickupScriptIndex;
//								if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(pickupScriptIndex)) {
//									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pickupScriptIndex, true, true);
//									OBJECT::DELETE_OBJECT(&pickupScriptIndex);
//									//g_ForceControlEntity = 0;
//									PrintNotification(ENFORCER_ALERT, "Someone tried to spawn a freeze pickup.");
//								}
//							}
//						}
//					}
//				}
//			}
//			if ((int)networkPedPool != 0) {
//				if (networkPedPool->m_PoolStart != 0) {
//					for (int i = 0; i < networkPedPool->m_MaxItems; i++) {
//						if (*(int*)((networkPedPool->m_PoolStart + (i * networkPedPool->m_ItemSize))) == 0x1938EB0 && *(int*)((networkPedPool->m_PoolStart + (i * networkPedPool->m_ItemSize)) + 0x2C) != 0) {
//							CPed* pedStruct = (CPed*)(*(int*)((networkPedPool->m_PoolStart + (i * networkPedPool->m_ItemSize)) + 0x2C));
//							int pedScriptIndex = entityToIndex(*(int*)((networkPedPool->m_PoolStart + (i * networkPedPool->m_ItemSize)) + 0x2C));
//							if (ENTITY::DOES_ENTITY_EXIST(pedScriptIndex)) {
//								if (WEAPON::GET_SELECTED_PED_WEAPON(pedScriptIndex) == 0x2be6766b) { // WEAPON HASH CHECK
//																									 //g_ForceControlEntity = pedScriptIndex;
//									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(pedScriptIndex)) {
//										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pedScriptIndex, true, true);
//										ENTITY::DELETE_ENTITY(&pedScriptIndex);
//										//g_ForceControlEntity = 0;
//										PrintNotification(ENFORCER_ALERT, "Someone tried to spawn a ped holding a freeze SMG.");
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//			if ((int)networkVehiclePool != 0) {
//				if (networkVehiclePool->m_PoolStart != 0) {
//					for (int i = 0; i < networkVehiclePool->m_MaxItems; i++) {
//						if (*(int*)((networkVehiclePool->m_PoolStart + (i * networkVehiclePool->m_ItemSize))) == 0x1935F38 && *(int*)((networkVehiclePool->m_PoolStart + (i * networkVehiclePool->m_ItemSize)) + 0x2C) != 0) {
//							CVehicle* vehicleStruct = (CVehicle*)(*(int*)((networkVehiclePool->m_PoolStart + (i * networkVehiclePool->m_ItemSize)) + 0x2C));
//							int vehicleScriptIndex = entityToIndex(*(int*)((networkVehiclePool->m_PoolStart + (i * networkVehiclePool->m_ItemSize)) + 0x2C));
//							if (ENTITY::DOES_ENTITY_EXIST(vehicleScriptIndex)) {
//								if (vehicleStruct->m_ModelInfo->m_ModelHash == 0xb779a091) {
//									if (g_SpamManager[2][0] == 5) {
//										PrintNotification(ENFORCER_ALERT, "Someone tried to crash you with adders.");
//										for (int j = 1; j < 6; j++) {
//											//g_ForceControlEntity = g_SpamManager[2][i];
//											if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(g_SpamManager[2][i])) {
//												ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_SpamManager[2][i], true, true);
//												ENTITY::DELETE_ENTITY(&g_SpamManager[2][i]);
//												//g_ForceControlEntity = 0;
//											}
//										}
//										g_SpamManager[2][0] = 0;
//									}
//									else
//										g_SpamManager[2][g_SpamManager[2][0]++] = vehicleScriptIndex;
//								}
//
//								if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(PLAYER::PLAYER_PED_ID(), vehicleScriptIndex)) { // OBJECT REATTACH
//																														 //g_ForceControlEntity = vehicleScriptIndex; //
//									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicleScriptIndex)) {
//										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicleScriptIndex, true, true);
//										ENTITY::DELETE_ENTITY(&vehicleScriptIndex);
//										//g_ForceControlEntity = 0;
//										PrintNotification(ENFORCER_ALERT, "Someone tried to attach a vehicle to your player.");
//									}
//								}
//							}
//						}
//					}
//					g_SpamManager[2][0] = 0; // RESET SPAM MANAGER COUNTS HERE
//				}
//			}
//		}
//	}
//
//	/*
//	opd_s HasControlOfEntity_t = { 0xA0D1B4, TOC };
//	bool(*HasControlOfEntity)(int r3) = (bool(*)(int))&HasControlOfEntity_t;
//	bool HasControlOfEntity_Hook(int r3) { //this need hook in some addr with branch_link
//	if (g_ForceControlEntity != 0 && *(int*)(r3 + 0x2C) != 0)
//	{
//	if (entityToIndex(*(int*)(r3 + 0x2C)) == g_ForceControlEntity)
//	{
//	*(char*)(r3 + 0x27) = 0;
//	return 0;
//	}
//	}
//	return HasControlOfEntity(r3);
//	}*/
//}