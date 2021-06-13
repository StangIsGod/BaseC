char *MenuVersion = "180";
char *RealVersion = "1.1";	

using namespace std;

bool StringCompare(char* _char1, char* _char2)
{
	if (strcmp(_char1, _char2) == 0)
		return true;
}

bool isAlphaOrNum(char _a, bool special = false)
{
	if ((_a >= 'a'&& _a <= 'z') || (_a >= 'A' && _a <= 'Z'))
		return true;
	else if (_a >= '0'&& _a <= '9')
		return true;
	else if (((_a == '>') || (_a == '<')) && special)
		return true;
	else
		return false;
}

#pragma region ObjectXMLReader
char *replace(char *str, const char *what, const char *with)
{
	if (!*what) { return str; }
	char *what_pos = strstr(str, what);
	if (!what_pos) { return str; }
	const size_t what_len = strlen(what), with_len = strlen(with);
	const char *remain = what_pos + what_len;
	memmove(what_pos + with_len, remain, strlen(remain) + 1);
	memcpy(what_pos, with, with_len);
	return str;
}

int fileSize(char *file) {
	int fd; int ret; uint64_t pos; uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		CellFsStat sb;
		ret = cellFsFstat(fd, &sb);
		if (!ret)
		{
			return sb.st_size;
		}
	}
	return -1;
}

void ObjectXML(char *LoadedLine)
{
	char *p = strtok(LoadedLine, ", ");
	printf("読み取った単語 1:");
	printf(p);
	printf("  :  ");
	p = strtok(NULL, ", ");
	printf("読み取った単語 2 : %s", p);
	printf("\n");
}

void do_ReadXML(char *path)
{
//#define FREE_MEM_XML 0x10055550;
//#define FREE_MEM_XML2 0x1005F660;
	uint64_t pos, unk;
	int _fd;

	int size = fileSize(path);
	if (size != -1)
	{
		cellFsOpen(path, 0, &_fd, NULL, 0);
		printf("Got a filesize [%ibyte]\n", size);
		cellFsLseek(_fd, 0, CELL_FS_SEEK_SET, &pos);
		if (cellFsRead(_fd, (char*)0x10055550, size, &unk) != CELL_FS_SUCCEEDED)
			return;
		else
			printf("Writed Filedata to 0x%X [%ibyte]", 0x10055550, size);
		cellFsClose(_fd);

		int LineNumber;
		char LoadedLine[200];
		char buf[200];
		strcpy(LoadedLine, "");
		int _index;

		int XMLIndex = -1;
		printf("LoopStart\n");

		for (int i = 0; i < size; i++)
		{
			char thisChar = *(char*)(0x10055550 + i);
			char nextChar = *(char*)(0x10055550 + i + 1);

			if ((thisChar == '\r' && nextChar == '\n'))
			{
				if (strlen(LoadedLine) >= 5)
				{
					strcpy(buf, LoadedLine);
					replace(buf, "\r", "");
					replace(buf, "\n", "");
					replace(buf, "<", "");
					replace(buf, ">", "");
					printf("%s : strlen:%i\n", buf, strlen(LoadedLine));
					ObjectXML(buf);
					i += 1;
				}
				strcpy(buf, "");
				strcpy(LoadedLine, "");
			}
			else
			{
				if (thisChar != '	')
				{
					PS3::WriteByte(0x10054320, thisChar);
					strcat(LoadedLine, PS3::ReadString_1(0x10054320));
					PS3::WriteByte(0x10054320, '\0');
				}
			}
		}
	}

}

bool ObjectNotFounds;
void memFree(char* ptr, int len) { for (int i = 0; i < len; i++) { *(char*)(ptr + i) = 0x00; } }
void ReadObjects()
{
	int fd;
	uint32_t count;
	CellFsDirectoryEntry entry;

	CellFsErrno Res = cellFsOpendir("/dev_hdd0/tmp/Re_HyperDx", &fd);
	if (Res != CELL_FS_SUCCEEDED)
	{
		ObjectNotFounds = true;
		printf("Folder not found\n");
	}
	else
	{
		memset(&entry, 0, sizeof(CellFsDirectoryEntry));
		int Counter = 0;
		do
		{
			CellFsErrno er = cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &count);
			if (er == CELL_FS_SUCCEEDED && entry.entry_name.d_type == CELL_FS_TYPE_REGULAR)
			{
				if (Counter < 100)
				{
					do_ReadXML(entry.entry_name.d_name);
					Counter++;
				}
			}
		} while (count);

		if (Counter == 0)
		{
			ObjectNotFounds = true;
			printf("xml not found\n");
		}
	}
	cellFsClosedir(fd);
}
#pragma endregion

namespace ZeddFileLoader
{
	float ReadXMLObjectCarSavefloat[50];
	int ReadXMLObjectCarSaveInt[50];
	int ReadXMLObjectCarSaveBone[50];
	bool ReadXMLObjectCarSaveIntBOOL[50];
	
	int ReadXMLObjectCarSaveCount;
	int ReadXMLObjectCarSaveCountLoop;

	void StringDelete(char *s1, char *s2)
	{
		char *p = s1;
		p = strstr(s1, s2);
		if (p != NULL) {
			strcpy(p, p + strlen(s2));
			StringDelete(p + 1, s2);
		}
	}

	//void ReadXMLObjectCar(char* patch, char* DownloadName = NULL)
	//{
	//	memset(ReadXMLObjectCarSavefloat, 0, 50);
	//	memset(ReadXMLObjectCarSaveInt, 0, 50);
	//	memset(ReadXMLObjectCarSaveBone, 0, 50);
	//	memset(ReadXMLObjectCarSaveIntBOOL, 0, 50);
	//	ReadXMLObjectCarSaveCount = 0; ReadXMLObjectCarSaveCountLoop = 0;
	//	char* PoolMemory = (char*)0x10020000;
	//	int fd;
	//	uint64_t unk;
	//	if (cellFsOpen(patch, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
	//		return;

	//	cellFsRead(fd, (char*)0x10020000, 20000, &unk);
	//	cellFsClose(fd);
	//	char line[1000];
	//	for (int i = 0; i < 20000; i++)
	//	{
	//		if (PoolMemory[i] == 0x00)
	//			break;

	//		if (PoolMemory[i] == '\n' || PoolMemory[i] == '\r')
	//		{
	//			if (strstr(line, "<start>"))
	//			{
	//				addMessageShow("スタート");
	//			}
	//			if (strstr(line, "<vehicle>"))
	//			{
	//				StringDelete(line, "<vehicle>");
	//				hash_veh = GET_HASH_KEY(line);
	//				SpawnVehicle = true;
	//			}
	//			if (strstr(line, "<objectHash>"))
	//			{
	//				StringDelete(line, "<objectHash>");
	//				ReadXMLObjectCarSaveInt[ReadXMLObjectCarSaveCount] = StringToInt(line);
	//				ReadXMLObjectCarSaveIntBOOL[ReadXMLObjectCarSaveCount] = true;
	//			}
	//			else if (strstr(line, "<ATTACHvehicle>"))
	//			{
	//				StringDelete(line, "<ATTACHvehicle>");
	//				ReadXMLObjectCarSaveInt[ReadXMLObjectCarSaveCount] = GET_HASH_KEY(line);
	//				ReadXMLObjectCarSaveIntBOOL[ReadXMLObjectCarSaveCount] = false;
	//			}
	//			if (strstr(line, "<bone>"))
	//			{
	//				StringDelete(line, "<bone>");
	//				sprintf(ReadXMLObjectCarSaveBone[ReadXMLObjectCarSaveCount], line);
	//			}
	//			if (strstr(line, "<x>"))
	//			{
	//				StringDelete(line, "<x>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Lx = StringToFloat(line);
	//			}
	//			if (strstr(line, "<y>"))
	//			{
	//				StringDelete(line, "<y>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Ly = StringToFloat(line);
	//			}
	//			if (strstr(line, "<z>"))
	//			{
	//				StringDelete(line, "<z>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Lz = StringToFloat(line);
	//			}
	//			if (strstr(line, "<rx>"))
	//			{
	//				StringDelete(line, "<rx>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Rx = StringToFloat(line);
	//			}
	//			if (strstr(line, "<ry>"))
	//			{
	//				StringDelete(line, "<ry>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Ry = StringToFloat(line);
	//			}
	//			if (strstr(line, "<rz>"))
	//			{
	//				StringDelete(line, "<rz>");
	//				ReadXMLObjectCarSavefloat[ReadXMLObjectCarSaveCount].Rz = StringToFloat(line);
	//			}
	//			if (strstr(line, "</next>"))
	//			{
	//				ReadXMLObjectCarSaveCount++;
	//			}
	//			if (strstr(line, "<END>")) {}
	//			memset(line, 0, 1000);
	//		}
	//		else
	//		{
	//			if (PoolMemory[i] != '\n')
	//			{
	//				sprintf(line, "%s%c", line, PoolMemory[i]);
	//			}
	//		}
	//	}
	//	ReadXMLObjectCarSaveLoop = true;
	//	memset((char*)0x10020000, 0, 20000);
	//}
}

#pragma region ScripInjector
//bne 40820000

void branch_bne(uint32_t branchTo, uint32_t branchFrom)
{
	uint32_t branch;
	
	if (branchTo > branchFrom)
	{
		branch = 0x40820000 + (branchTo - branchFrom);
	}
	else
	{
		branch = 0x4082FFFF - (branchFrom - branchTo);
	}

	memcpy((void*)branchFrom, &branch, 4);
}

void branch_link(uint32_t branchTo, uint32_t branchFrom, bool linked = true)
{
	uint32_t branch;
	if (linked)
	{
		if (branchTo > branchFrom)
		{
			branch = 0x48000001 + (branchTo - branchFrom);
		}
		else
		{
			branch = 0x4C000001 - (branchFrom - branchTo);
		}
	}
	else
	{
		if (branchTo > branchFrom)
		{
			branch = 0x48000000 + (branchTo - branchFrom);
		}
		else
		{
			branch = 0x4C000000 - (branchFrom - branchTo);
		}
	}
	memcpy((void*)branchFrom, &branch, 4);
}

void branch_ctr(uint32_t branchFrom, uint32_t branchTo, bool isLinked = true)
{
	uint32_t branch;
	if (isLinked)
		branch = 0x4E800421 + (branchTo - branchFrom); /*bctrl*/
	else
		branch = 0x4E800420 + (branchTo - branchFrom);/*bctr*/
													  //PS3::WriteInt32(branchFrom, branch);
	memcpy((void*)branchFrom, &branch, 4);
	//
}



namespace Script_Inject
{
	OPD_s _0xA88A04_t = { 0xA88A04, 0x1C85330 };
	int(*_0xA88A04)(uint, char*) = (int(*)(uint, char*))&_0xA88A04_t;
	//int test_1(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10)
	//{
	//	printf("0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n", r3, r4, r5, r6, r7, r8);
	//	return _0xA88A04(r3, r4, r5, r6, r7, r8, r9, r10);
	//}

	unsigned int test_44(unsigned int r3, void* r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10)
	{
		printf("0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n", r3, r4, r5, r6, r7, r8);
		//return _0x1523638(r3, (uint*)0xd0040320, r5, r6, r7, r8, r9, r10);
	}

	//OPD_s _0x150aadc_t = { 0x150aadc };
	//int(*_0x150aadc)(void) = (int(*)(void))0x150aadc;

	OPD_s _0x9B806C_t = { 0x9B806C, 0x1C85330 };
	int(*GetAddressFromScriptIndex)(uint scriptindex) = (int(*)(uint))&_0x9B806C_t;

	OPD_s _0x9B83F0_t = { 0x9B83F0, 0x1C85330 };
	int(*loc_0x9B83F0)(int **param_1, uint param_2) = (int(*)(int **, uint))&_0x9B83F0_t;

	OPD_s _0xAE579C_t = { 0xAE579C, 0x1C85330 };
	int(*sub_0xAE579C)(int*, uint) = (int(*)(int*, uint))&_0xAE579C_t;

	OPD_s _0xa88a04_t = { 0xa88a04, 0x1C85330 };
	void(*sub_a88a04)(uint, char*) = (void(*)(uint, char*))&_0xa88a04_t;

	OPD_s _0xa88780 = { 0xa88780, 0x1C85330 };
	void(*sub_0xA88780)(uint *param_1, uint param_2, char* param_3) = (void(*)(uint*, uint, char*))&_0xa88780;

	int test_1(uint r3)
	{
		int value = GetAddressFromScriptIndex(r3);
		printf("script index : 0x%X  |  address : 0x%X\n", r3, value);
		return value;
	}

	void test_2(uint *param_1, uint param_2, char* param_3)
	{
		printf("Pointer:0x%X | Hash:0x%X | Arg:%s\n", *param_1, param_2, param_3);
		sub_0xA88780(param_1, param_2, param_3);
	}

	OPD_s _0x439428 = { 0x439428, 0x1C85330 };
	void(*sub_439428)(char*) = (void(*)(char*))&_0x439428;

	void test_3(char* param_1)
	{
		printf("test_3 : %s\n", param_1);
		sub_439428(param_1);
	}

	OPD_s _0xa88cd4 = { 0xa88cd4, 0x1C85330 };
	void(*sub_A88cd4)(uint, char*) = (void(*)(uint, char*))&_0xa88cd4;
	void test_4(uint param_1, char* param_2)
	{
		int pointer = *(int*)0x01ee881c;
		printf("[test_4]Pointer:0x%X | Hash:0x%X | Arg:%s\n", pointer, param_1, param_2);
		sub_A88cd4(param_1, param_2);
	}
	//uint auStack48[4];
	//ulonglong test_5(int param_1, uint *param_2)
	//{
	//	ulonglong value = sub_1523638(param_1, param_2);
	//	printf("p1 : 0x%X | p2[0] : 0x%X | p2[1] : 0x%X\n | p2[2] : 0x%X | p2[3] : 0x%X", value, param_1, param_2[0], param_2[1], param_2[2], param_2[3]);
	//	return value;
	//}


	OPD_s _0x475294 = { 0x475294, 0x1C85330 };
	void(*sub_475294)(unknown1, int) = (void(*)(unknown1, int))&_0x475294;
	void test_6(unknown1 _a, int _b)
	{
		printf("[Re:Hyper Dx]Throw\n");
		sub_475294(_a, _b);
	}

	void SetBreakPoint(uint32_t address)
	{
		uint32_t branch = 0x7FE00008;
		memcpy((void*)address, &branch, 4);
	}

	OPD_s _0xae579c = { 0xae579c,0x1C85330 };
	uint(*_0xAE579C)(char*, uint) = (uint(*)(char*, uint))&_0xae579c;

	uint(*_GET_HASH_FUNC)(char*, uint zero) = (uint(*)(char*, uint))&_0xae579c;

	//OPD_s _0x1523638 = { 0x1523638, 0x0 };
	//uint(*sub_1523638)(int, int) = (uint(*)(int, int))&_0x1523638;

	ulonglong FUN_0150ccd4(int param_1, int param_2)

	{
		uint uVar1;

		uVar1 = (uint)*(char*)(*(int *)(param_1 + 0x28) + param_2) & 0x80;
		if (((*(int *)(param_1 + 0x40) != 0) && (*(int *)(param_1 + 0x44) <= param_2)) &&
			(param_2 < *(int *)(param_1 + 0x2c))) {
			return (ulonglong)*(uint *)(*(int *)(param_1 + 0x40) + (param_2 - *(int *)(param_1 + 0x44)) * 4);
		}
		return (ulonglong)*(uint *)(param_1 + 0x24) +
			(longlong)param_2 * (longlong)*(int *)(param_1 + 0x30) &
			~(ulonglong)(uint)((int)(uVar1 | -uVar1) >> 0x1f) & 0xffffffff;
	}
	


	/*void UndefinedFunction_0047529c(uint *param_1, int param_2)
	{
		*(char *)(param_1 + 1) = 0x16;
		param_1[2] = 0;
		param_1[3] = 0xffffffff;
		param_1[4] = 0;
		param_1[5] = 0;
		*param_1 = 0x18b90c0;
		if (param_2 != -1) {
			FUN_009c61a4(*(int*)0x01e70d88, (ulonglong)(uint)(*(int*)0x01de8ea0 + param_2), 0x14);
			param_1[3] = param_2;
		}
		return;
	}

	ulonglong UndefinedFunction_01523640(int param_1, uint *param_2)
	{
		unsigned short uVar1;
		uint uVar2;
		int iVar3;
		ulonglong uVar4;
		uint *puVar6;
		ulonglong uVar5;
		printf("Throw");
		uVar2 = *param_2;
		uVar1 = *(short*)
			(*(int *)(param_1 + 100) +
			(uVar2 - (uVar2 / *(unsigned short*)(param_1 + 0x68)) * (uint)*(unsigned short *)(param_1 + 0x68)) * 2);
		if (uVar1 != 0xffff) {
			printf("Throw2");
			do {
				puVar6 = (uint *)(*(int *)(param_1 + 0x60) + (uint)uVar1 * 8);
				if (*puVar6 == uVar2) {
					uVar5 = (ulonglong)*(unsigned short*)(puVar6 + 1);
					goto LAB_015236b4;
				}
				uVar1 = *(unsigned short*)((int)puVar6 + 6);
			} while (uVar1 != 0xffff);
		}
		uVar5 = 0xffffffffffffffff;

	LAB_015236b4:
		uVar4 = 0xffffffffffffffff;
		if (((int)uVar5 != -1) && (iVar3 = FUN_0150ccd4(param_1, uVar5), iVar3 != 0)) {
			uVar4 = uVar5;
		}
		return uVar4;
	}

	void do_RequestScript(char* param1)
	{
		int  piVar1;
		uint uVar2;
		uint auStack48[4];
		int auStack44[44];
		uVar2 = 0;
		if ((int)param1 != 0) {
			uVar2 = _0xAE579C(param1, 0);
			printf("p1 : 0x%X\np2 : %s\n", uVar2, param1);
		}
		sub_a88a04(uVar2, param1);
		int _0x1de8e9c = *(int*)0x01de8e9c;
		printf("_0x1de8e9c = 0x%X\n", _0x1de8e9c);
		uVar2 = UndefinedFunction_01523640(_0x1de8e9c, auStack48);
		printf("Throw\n");
		printf("uVar2 = 0x%X\n", uVar2);

		if ((int)uVar2 != -1) {
			FUN_00475294(auStack44, uVar2);
			piVar1 = (int *)FUN_0047ac6c();
			(***(code ***)(*piVar1 + 0x34))(piVar1, auStack44, 0);
			FUN_00473350(auStack44);
		}
		return;
	}*/

	OPD_s _0x9c61a4 = { 0x9c61a4, 0x1C85330 };

	uint(*FUN_009c61a4)(uint, ulonglong, char) = (uint(*)(uint, ulonglong, char))&_0x9c61a4;

	uint test_inf(uint p1, ulonglong p2, char p3)
	{
		uint value = FUN_009c61a4(p1, p2, p3);
		printf("p1 : 0x%X \np2 : 0x%X \np3 : 0x%X \n", p1, p2, p3);
		return value;
	}

	OPD_s _0x47ac6c = { 0x47ac6c, 0x1C85330 };
	uint(*sub_0x47ac6c)(void) = (uint(*)(void))&_0x47ac6c;


	ulonglong UndefinedFunction_01523640(int param_1, uint *param_2)
	{
		ushort uVar1;
		uint uVar2 = 0;
		int iVar3;
		uint uVar4;
		uint *puVar6;
		uint uVar5;
		uint auStack32[32];
		uVar2 = *param_2;
		uVar1 = *(ushort *)
			(*(int *)(param_1 + 100) +
			(uVar2 - (uVar2 / *(ushort *)(param_1 + 0x68)) * (uint)*(ushort *)(param_1 + 0x68)) * 2);
		printf("Step2.1\n0x%X\n0x%X\n0x%X\n", uVar2, uVar1, param_1);
		if (uVar1 != 0xffff) {
			do {
				puVar6 = (uint *)(*(int *)(param_1 + 0x60) + (uint)uVar1 * 8);
				printf("A : 0x%X\n", *puVar6);
				if (*puVar6 == uVar2) {
					uVar5 = (uint)*(ushort *)(puVar6 + 1);
					goto LAB_015236b4;
				}
				uVar1 = *(ushort *)((int)puVar6 + 6);
				printf("B : 0x%X\n", uVar1);

				if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, Button_L2))
				{
					break;
				}
			} while (uVar1 != 0xffff);
		}
		printf("Step2.5 0x%X\n", uVar1);
		uVar5 = -1;
	LAB_015236b4:
		uVar4 = -1;
		if (((int)uVar5 != -1) && (iVar3 = FUN_0150ccd4(param_1, uVar5), iVar3 != 0)) {
			uVar4 = uVar5;
		}
		return uVar4;
	}

	uint UndefinedFunction_00439560(char* param_1)

	{
		int iVar2;
		uint uVar1;
		uint uVar3;
		uint auStack32[4];

		int DAT_01de8e9c = *(int*)0x01de8e9c;

		uVar3 = 0;
		if ((int)param_1 != 0) {
			uVar3 = _0xAE579C(param_1, 0);
		}
		printf("Step1");
		_0xA88A04(uVar3, param_1);
		printf("Step2");
		iVar2 = UndefinedFunction_01523640(DAT_01de8e9c, auStack32);
		printf("Step3");
		if (iVar2 == -1) {
			uVar1 = 0;
		}
		else {

			uVar1 = (ulonglong)(*(uint *)(*(int*)0x01e70d88 + (*(int*)0x01de8ea0 + iVar2) * 8 + 4) >> 0x1e == 1);
		}
		return iVar2;
		//return uVar1;
	}

	OPD_s _0x01523638 = { 0x01523638, 0x1C85330 };
	int(*sub_1523638)(int, unsigned int*) = (int(*)(int, unsigned int*))&_0x01523638;

	OPD_s _0x9b806c = { 0x9b806c, 0x1C85330 };
	uint(*sub_9b806c)(int) = (uint(*)(int))&_0x9b806c;

	void UndefinedFunction_009b8364(int **param_1, uint param_2)
	{
		int iVar1;
		uint in_r13;
		int iVar2;
		int iVar3;

		if ((int)param_2 == 0) {
			iVar3 = *(int *)((int)in_r13 + -0x6fa0);
			if (iVar3 != 0) {
				*(uint*)(iVar3 + 0xc) = 1;
			}
		}
		else {
			iVar3 = *(int *)((int)in_r13 + -0x6fa0);
			**param_1 = (int)param_2;
			if (iVar3 != 0) {
				iVar2 = 0;
				*(ushort *)(iVar3 + 0xc) = 0;
				iVar3 = 0;
				do {
					iVar1 = sub_9b806c(param_2);
					if (*(int *)(iVar1 + iVar3 + 0x30) == 0) {
						iVar1 = sub_9b806c(param_2);
						*(ushort *)(iVar1 + iVar3 + 0x30) =
							*(ushort *)(*(int *)((int)in_r13 + -0x6fa0) + iVar3 + 0x30);
					}
					iVar2 = iVar2 + 1;
					iVar3 = iVar3 + 4;
				} while (iVar2 < 4);
			}
		}
		return;
	}

	OPD_s _0x47df30 = { 0x47df30, 0x1C85330 };
	uint(*PlayerIndexToPlayerAddress)(uint) = (uint(*)(uint))&_0x47df30;

	OPD_s _0x12f70e8 = { 0x12f70e8, 0x1C85330 };
	uint(*sub_12f70e8)(uint) = (uint(*)(uint))&_0x12f70e8;

	OPD_s _0x1336938 = { 0x1336938, 0x1C85330 };
	uint(*sub_1336938)(uint) = (uint(*)(uint))&_0x1336938;

	uint GET_STAT_PLAYERADDRESS(int param_1)
	{
		uint uVar1;

		uVar1 = 0;
		if (*(int *)(param_1 + 0x78) != 0) {
			uVar1 = *(uint *)(*(int *)(param_1 + 0x78) + 0x160);
		}
		return uVar1;
	}

	uint playerAddress(Player player) //sub_12f70e8
	{
		uint uVar1;
		uint maxPlayer = 18;
		uVar1 = 0;
		if (player < maxPlayer) {
			uVar1 = *(uint *)(*(int*)0x1cf72bc + (uint)player * 0x04 + 0xdc);
		}
		return uVar1;
	}

	enum PlayerAddreses {
		Player_Speed = 0x11c,
		Player_Wanted = 0x94,
		Player_Isdead = 0x154,
		Player_SuperJump = 0x178,
		Player_Health = 0x170,
		Player_MaxHealth = 0x174,
	};

	OPD_s _0x1512b90 = { 0x1512b90, 0x1C85330 };
	uint(*sub_1512b90)(uint) = (uint(*)(uint))&_0x1512b90;

	int GET_WEAPON_CLIP_SIZE(ulonglong param_1)
	{
		int iVar1;
		int uVar2;

		iVar1 = sub_1512b90(param_1 & 0xffffffff);
		if (iVar1 == 0) {
			uVar2 = 0;
		}
		else {
			uVar2 = *(int*)(iVar1 + 0x48);
		}
		return uVar2;
	}

	OPD_s _0x473350_t = { 0x473350, 0x1C85330 };
	uint(*sub_473350)(uint*) = (uint(*)(uint*))&_0x473350_t;

	void UndefinedFunction_00439430(char* param_1)
	{
		int *piVar1;
		uint uVar2;
		uint auStack48[4]; //(uint*)0x10050060
		uint auStack44[44]; //(uint*)0x10051060

		uVar2 = 0;
		if ((int)param_1 != 0) {
			uVar2 = _GET_HASH_FUNC(param_1, 0);
		}
		printf("aaaaaa___aaaa\n");
		_0xA88A04(uVar2, param_1);
		printf("aaaaaa___aaaa\n");
		int uVar10 = *(int*)0x1de8e9c;
		printf("aaaaaa___aaaa\n");
		uVar2 = sub_1523638(uVar10, auStack44);
		printf("aaaaaa___aaaa\n");
		if ((int)uVar2 != -1) {
			printf("aaaaaa___aaaa\n");
			sub_475294((uint*)0x10051060, uVar2);
			printf("aaaaaa___aaaa\n");
			piVar1 = (int*)sub_0x47ac6c();
			printf("0x%X", *piVar1 + 0x34);
			//(***(code ***)(*piVar1 + 0x34))(piVar1, auStack44, 0);
			//sub_473350(auStack44);
		}
		return;
	}

	//void SET_WEAPON_CLIP_SIZE(ulonglong param_1, uint param_2)
	//{
	//	int iVar1;
	//	int uVar2;

	//	iVar1 = sub_1512b90(param_1 & 0xffffffff);
	//	if (iVar1 == 0) {
	//		uVar2 = 0;
	//	}
	//	else {
	//		*(int*)(iVar1 + 0x48) = param_2;
	//	}
	//}

	int countLeadingZeros(uint bits)
	{
		return __builtin_clz(bits);
	}

	uint _PlayerIndexToPlayerAddress(uint param_1) //sub_47df30
	{

		int iVar1;
		uint uVar2;
		bool isOnline = *(int*)0x223f0c0 > 0;
		int maxPlayer = 18;
		if (isOnline) {
			if (0 <= param_1 && param_1 < maxPlayer) {
				iVar1 = playerAddress(param_1);
				if (iVar1 != 0) {
					uVar2 = GET_STAT_PLAYERADDRESS(iVar1);
				}
			}
		}
		else {
			if (param_1 == 0) {
				uVar2 = (uint)*(uint *)(*(int*)0x1cefce8 + 4);
			}
		}

		return uVar2;
	}

	OPD_s _0x9d97c0 = { 0x9d97c0, 0x1C85330 };
	uint(*sub_9d97c0)(uint, uint*) = (uint(*)(uint, uint*))&_0x9d97c0;

	uint IS_VEHICLE_MODEL_A_CAR(uint param_1) /*Get Flying Car Address*/

	{
		int iVar1;
		uint uVar2;
		uint auStack16[16];

		uVar2 = 0;
		iVar1 = sub_9d97c0(param_1 & 0xffffffff, auStack16);
		int iVar2 = iVar1 + 0x6b;
		int iVar3 = iVar1 + 0x1b8;
		printf("iVar1 = 0x%X | iVar2 = 0x%X | iVar3 = 0x%X", iVar1, iVar2, iVar3);

		if (((iVar1 != 0) && (*(char*)(iVar2) >> 3 == 5)) && (*(int *)(iVar1 + 0x1b8) == 0)) {
			uVar2 = 1;
		}
		return uVar2;
	}

	void SuperJumper(uint param_1)
	{
		int iVar1;

		iVar1 = _PlayerIndexToPlayerAddress(param_1);
		if (iVar1 != 0) {
			*(uint *)(*(int *)(iVar1 + 0xbd0) + 0x178) = *(uint *)(*(int *)(iVar1 + 0xbd0) + 0x178) | 0x4000;
		}
		return;
	}

	uint IS_PLAYER_DEAD_(uint param_1)
	{
		int iVar2;
		uint uVar1;

		iVar2 = _PlayerIndexToPlayerAddress(param_1);
		if (iVar2 == 0) {
			uVar1 = 0;
		}
		else {
			return *(int *)(*(int *)(iVar2 + 0xbd0) + Player_Isdead);
		}
	}

	void SET_PLAYER_SPEED_MODIFIER(float param_1, Player param_2) //sub_424CF8
	{
		int PlayerAddress = _PlayerIndexToPlayerAddress(param_2);
		if (((PlayerAddress != 0) /*&& (1.00000000 <= param_1)) && (param_1 < 1.50000000)*/)) {
			*(float *)(*(int *)(PlayerAddress + 0xbd0) + Player_Speed) = (float)param_1;
		}
		return;
	}

	void SET_PLAYER_WANTED_LEVEL_Func(int wantedLevel = 5) //sub_422A10
	{
		int returnvalue = 0;

		int PlayerAddress = _PlayerIndexToPlayerAddress(PLAYER::PLAYER_ID());
		int PlayerStats;

		if (PlayerAddress != 0 && (wantedLevel >= 0) && (wantedLevel <= 5))
		{
			if (PS3::ReadUInt32(PlayerAddress + 0xbd0) != 0)
			{
				PlayerStats = PS3::ReadUInt32(PlayerAddress + 0xbd0) + 0x550;
				*(int*)(PlayerStats + Player_Wanted) = wantedLevel;
			}
		}
	}

	int GET_PLAYER_WANTED_LEVEL_Func(Player param_1) //sub_422A10
	{
		int returnvalue = 0;

		int PlayerAddress = _PlayerIndexToPlayerAddress(param_1);
		int PlayerStats;

		if (PlayerAddress != 0) 
		{
			if (PS3::ReadUInt32(PlayerAddress + 0xbd0) != 0)
			{
				PlayerStats = PS3::ReadUInt32(PlayerAddress + 0xbd0) + 0x550;
				return *(int*)(PlayerStats + Player_Wanted);
			}
		}
		return 0;
	}
	
	OPD_s _0x47deb8 = { 0x47deb8, 0x1C85330 };
	uint(*sub_0x47deb8)(uint, uint) = (uint(*)(uint, uint))&_0x47deb8;

	OPD_s _0x9b826c = { 0x9b826c, 0x1C85330 };
	uint(*sub_9b826c)(void) = (uint(*)(void))&_0x9b826c;

	void UndefinedFunction_004248a0(Player param_1, uint param_2)
	{
		uint uVar1;
		int iVar3;
		uint uVar4;
		Player uVar2;

		iVar3 = sub_0x47deb8(param_1, 1);
		uVar1 = *(int*)0x1c9755c;
		uVar4 = sub_9b826c();
		uVar2 = countLeadingZeros(uVar4);
		uVar1 = uVar1 | (uint)uVar2 >> 5 & 1;
		if (iVar3 != 0) {
			*(uint *)(iVar3 + 0xb4) = (param_2 & 1) << 0x17 | *(uint *)(iVar3 + 0xb4) & 0xff7fffff;
		}
		return;
	}

	void FUN_009b8364(int **param_1, uint param_2)
	{
		int iVar1;
		uint in_r13;
		int iVar2;
		int iVar3;

		if ((int)param_2 == 0) {
			iVar3 = *(int *)((int)in_r13 + -0x6fa0);
			if (iVar3 != 0) {
				*(uint*)(iVar3 + 0xc) = 1;
			}
		}
		else {
			iVar3 = *(int *)((int)in_r13 + -0x6fa0);
			**param_1 = (int)param_2;
			if (iVar3 != 0) {
				iVar2 = 0;
				*(uint *)(iVar3 + 0xc) = 0;
				iVar3 = 0;
				do {
					iVar1 = sub_9b806c(param_2);
					if (*(int *)(iVar1 + iVar3 + 0x30) == 0) {
						iVar1 = sub_9b806c(param_2);
						*(uint *)(iVar1 + iVar3 + 0x30) =
							*(uint *)(*(int *)((int)in_r13 + -0x6fa0) + iVar3 + 0x30);
					}
					iVar2 = iVar2 + 1;
					iVar3 = iVar3 + 4;
				} while (iVar2 < 4);
			}
		}
		return;
	}

	//uint UndefinedFunction_0047dec0(uint param_1)
	//{
	//	uint uVar1;
	//	int iVar2;
	//	ulonglong uVar3;
	//	bool isOnline = *(int*)0x223f0c0 > 0;
	//	uVar3 = 0;
	//	if (!isOnline) {
	//		if (param_1 == 0) {
	//			uVar3 = (uint)*(uint *)(*(int*)0x1cefce8 + 4);
	//		}
	//	}
	//	else {
	//		uVar1 = FUN_012f70e8((uint)(param_1 & 0xff));
	//		if (((int)uVar1 != 0) && (iVar2 = FUN_009fe7c8(uVar1), iVar2 != 0)) {
	//			uVar3 = FUN_01336938(uVar1);
	//		}
	//	}
	//	return uVar3;
	//}

	//0x480178

	int test_AA(uint r3, uint r4, uint r5, uint r6, uint r7)
	{
		printf("r3 = 0x%X | r4 = 0x%X | r5 = 0x%X | r6 = 0x%X | r7 = 0x%X", r3, r4, r5, r6, r7);
	}

	void GET_SCRIPT_ADDRESS()
	{
		
		//branch_link(*(int*)((int)&test_44), 0x439474);
		//branch_link(*(int*)((int)&testfunc), 0x43964c);
		
		//0x15b9034
		
		//SetBreakPoint(0x439478);
		//0x43948c
		/*branch_link(*(int*)((int)&test_6), 0x43948c);*/

		//0x439474
		//branch_link(*(int*)((int)&test_5), 0x439474);

		///branch_link(*(int*)((int)&test_1), 0x9B83B4); //Convert ScriptIndex to Address
		///branch_link(*(int*)((int)&test_2), 0xa88a30); //Register Hash and string of script
		//branch_link(*(int*)((int)&test_4), 0x480178);										//Unknown Maybe Register Hash and string of script
		///branch_link(*(int*)((int)&test_3), 0x159cc28); //START_NEW_SCRIPT Hook
		
		//branch_link(*(int*)((int)&test_inf), 0x475300);
		//0x159cc28

		//0xa88a30
		//branch_link(*(int*)((int)&test_2), 0x439460);
		//branch_link(*(int*)((int)&test_3), 0x439450);
		//branch_bne(*(int*)((int)&test_2), 0x9B83C8);
		//9B83B4

		//1C4E100
		
		//0x439474
		
		//branch_link(*(int*)((int)&test_1), 0x439474);
	}
}
#pragma endregion
//0x1C85330
#pragma region Practice Reverse
namespace Practice {

	//ADdress

	OPD_s _0x150ccd4 = { 0x150ccd4, 0x1C85330 };
	//(int param_1,int param_2)
	int(*sub_150ccd4)(int, int) = (int(*)(int, int))&_0x150ccd4;

	int _retvalue_150ccd4(int r3, int r4)
	{
		int value = sub_150ccd4(r3, r4);
		printf("0x%X, 0x%X\n", r3, r4);
		return value;
	}

	int FUN_00467610(uint param_1)
	{
		int iVar1;
		int uVar2;
		int uVar3;
		int lVar4;
		int lVar5;

		int _0x214790c = *(int*)0x214790c;
		int _0x2147908 = *(int*)0x2147908;
		printf("0x%X\n", _0x214790c);
		printf("0x%X\n", _0x2147908);
		printf("\n");
		if ((param_1 != 0) && (lVar4 = _0x214790c - 1)) {
			lVar5 = 0;
			do {
				printf("1 : 0x%X\n", uVar3);
				printf("2 : 0x%X\n", lVar4);
				printf("3 : 0x%X\n", lVar5 >> 1);
				printf("4 : 0x%X\n", iVar1);
				uVar3 = lVar4 + lVar5 >> 1;
				printf("5 : 0x%X\n", uVar3);
				iVar1 = *(int*)(_0x2147908 + uVar3 * 0x4);
				printf("6 : 0x%X\n", iVar1);
				uVar2 = *(int*)(iVar1 + 8);
				printf("7 : 0x%X\n", uVar2);
			
				//printf("7 : 0x%X\n", lVar5);
			

				if (param_1 == uVar2) {
					if (iVar1 == 0) {
						return 0;
					}
					return 1;
				}
				if (param_1 < uVar2) {
					lVar4 = uVar3 - 1;
				}
				else {
					lVar5 = uVar3 + 1;
				}
			} while ((int)lVar5 <= (int)lVar4);
		}
		return 0;
	}

	void UndefinedFunction_015b5a08(void)
	{
		uint *puVar1;
		uint uVar2;

		//puVar1 = (uint*)*(int*)0x018037c4;
		//uVar2 = FUN_00467610(*(uint*)puVar1[2]);
		//*(uint*)*puVar1 = uVar2;
		return;
	}

	void Practice_Address() {
		
	}
}
#pragma endregion

int return_menuid(int index)
{
	return PS3::Read_Global(1581767 + (index * 306) + 178 + 45);
}
void addMessageShow(char* message) {
	//msgindexflag
	if (!DontViewLog)
	{
		for (int i = 0; i < 9; i++)
		{
			MsgInfoBuf[i] = MsgInfoBuf[i + 1];
		}

		MsgInfoBuf[9] = message;
		MsgOpacity = 255;
		MsgTimer = GAMEPLAY::GET_GAME_TIMER() + 5000;
		msgindexflag = true;
		/*if (!(msgindex >= 10))
		msgindex++;
		else
		msgindex = 0;
		*/
		//msgindexflag = true;
	}
}

void TriggerScriptEvent(int* Args, int ArgCount, Player BitsetPlayer)
{
	if ((return_menuid(BitsetPlayer) == 80373826 || return_menuid(BitsetPlayer) == 80593748 || return_menuid(BitsetPlayer) == 9487481 || return_menuid(BitsetPlayer) == 948749751) && !_AdminFlag)
	{
		addMessageShow("[Script]JP SPRX使用者には攻撃不可能です。");
	}
	else
	{
		unsigned int bits = (1 << BitsetPlayer);
		PLAYER::TRIGGER_SCRIPT_EVENT(1, Args, ArgCount, bits);
	}
}

void NotifyDown(char*msg, int timer = 2000)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(timer, 1);
}

#pragma region 暗号化

int Index;
char EncryptBuffer[0x50];
char* LoadText(char* String, int index)
{
	strcpy(EncryptBuffer, "");
	for (int i = 0; i < index; i++)
	{
		if (i % 2) //奇数
		{
			//strcat(EncryptBuffer, (String + i) + 1);
			*(EncryptBuffer + i) = *(String + i) + 1;
		}
		else //偶数
		{
			//strcat(EncryptBuffer, (String + i) + 1);
			*(EncryptBuffer + i) = *(String + i) - 1;
		}
	}
	//strcat(EncryptBuffer, '\0');
	*(EncryptBuffer + index) = '\0';
	return EncryptBuffer;
}
//char* LoadText(char* String, int leng)
//{
//	char EncryptBuffer[0x50];
//	strcpy(EncryptBuffer, "");
//	for (int i = 0; i < leng; i++)
//	{
//		if (i % 2) //奇数
//		{
//			strcat(EncryptBuffer, ctocp(String[i] + 1));
//			//PS3::WriteByte(0x10024545 + i, String[i] + 1);
//			//EncryptBuffer[i] = ;
//		}
//		else //偶数
//		{
//			strcat(EncryptBuffer, ctocp(String[i] - 1));
//			//PS3::WriteByte(0x10024545 + i, String[i] - 1);
//			//EncryptBuffer[i] = String[i] - 1;
//		}
//	}
//	strcat(EncryptBuffer, '\0');
//	//PS3::WriteByte(0x10024545 + leng, '\0');
//	//EncryptBuffer[leng] = 0x00;
//	//return PS3::ReadString(0x10024545);
//	return EncryptBuffer;
//}

//redxserver.php.xdomain.jp
char redxserver_php_xdomain[] = { 0x73, 0x64, 0x65, 0x77, 0x74, 0x64, 0x73, 0x75, 0x66, 0x71, 0x2f, 0x6f, 0x69, 0x6f, 0x2f, 0x77, 0x65, 0x6e, 0x6e, 0x60, 0x6a, 0x6d, 0x2f, 0x69, 0x71 };

//Redirect_REDX.php?CMD=GET_INIFILE
char redirect_redxphpque_cmd_get_inifile[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x4a, 0x4d, 0x4a, 0x45, 0x4a, 0x4b, 0x46 };

// /dev_hdd0/tmp/Re_HyperDx/Auto_Setting.ini
char tmp_rehyperdx_inifile[] = { 0x30, 0x63, 0x66, 0x75, 0x60, 0x67, 0x65, 0x63, 0x31, 0x2e, 0x75, 0x6c, 0x71, 0x2e, 0x53, 0x64, 0x60, 0x47, 0x7a, 0x6f, 0x66, 0x71, 0x45, 0x77, 0x30, 0x40, 0x76, 0x73, 0x70, 0x5e, 0x54, 0x64, 0x75, 0x73, 0x6a, 0x6d, 0x68, 0x2d, 0x6a, 0x6d, 0x6a };

// /dev_hdd0/tmp/Re_HyperDx
char tmp_rehyperdx[] = { 0x30, 0x63, 0x66, 0x75, 0x60, 0x67, 0x65, 0x63, 0x31, 0x2e, 0x75, 0x6c, 0x71, 0x2e, 0x53, 0x64, 0x60, 0x47, 0x7a, 0x6f, 0x66, 0x71, 0x45, 0x77 };

//Redirect_REDX.php
char redirect_redx_php[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71 };

// /dev_hdd0/tmp/
char dev_hdd0_tmp[] = { 0x30, 0x63, 0x66, 0x75, 0x60, 0x67, 0x65, 0x63, 0x31, 0x2e, 0x75, 0x6c, 0x71, 0x2e };

// ?VER=
char q_ver_equal[] = { 0x40, 0x55, 0x46, 0x51, 0x3e };

// ?DIR=SPRX_DOWNLOAD
char q_dir_equal_sprx_download[] = { 0x40, 0x43, 0x4a, 0x51, 0x3e, 0x52, 0x51, 0x51, 0x59, 0x5e, 0x45, 0x4e, 0x58, 0x4d, 0x4d, 0x4e, 0x42, 0x43 };

// Re_HyperDx.key
char re_hyper_dx_key[] = { 0x53, 0x64, 0x60, 0x47, 0x7a, 0x6f, 0x66, 0x71, 0x45, 0x77, 0x2f, 0x6a, 0x66, 0x78 };

// Redirect_REDX.php?CMD=GET_CHAT&VAR2=5
char redirect_redx_php_que_cmd_get_chat_var2_5[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x44, 0x47, 0x42, 0x53, 0x27, 0x55, 0x42, 0x51, 0x33, 0x3c, 0x36 };

// Redirect_REDX.php?CMD=GET_CHAT&VAR2=4
char redirect_redx_php_que_cmd_get_chat_var2_4[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x44, 0x47, 0x42, 0x53, 0x27, 0x55, 0x42, 0x51, 0x33, 0x3c, 0x35 };

// Redirect_REDX.php?CMD=GET_CHAT&VAR2=3
char redirect_redx_php_que_cmd_get_chat_var2_3[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x44, 0x47, 0x42, 0x53, 0x27, 0x55, 0x42, 0x51, 0x33, 0x3c, 0x34 };

// Redirect_REDX.php?CMD=GET_CHAT&VAR2=2
char redirect_redx_php_que_cmd_get_chat_var2_2[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x44, 0x47, 0x42, 0x53, 0x27, 0x55, 0x42, 0x51, 0x33, 0x3c, 0x33 };

// Redirect_REDX.php?CMD=GET_CHAT&VAR2=1
char redirect_redx_php_que_cmd_get_chat_var2_1[] = { 0x53, 0x64, 0x65, 0x68, 0x73, 0x64, 0x64, 0x73, 0x60, 0x51, 0x46, 0x43, 0x59, 0x2d, 0x71, 0x67, 0x71, 0x3e, 0x44, 0x4c, 0x45, 0x3c, 0x48, 0x44, 0x55, 0x5e, 0x44, 0x47, 0x42, 0x53, 0x27, 0x55, 0x42, 0x51, 0x33, 0x3c, 0x32 };

// Re_HyperDx SPRXs
char re_hyper_dx_sprx_a[] = { 0x53, 0x64, 0x60, 0x47, 0x7a, 0x6f, 0x66, 0x71, 0x45, 0x77, 0x2f, 0x72, 0x71, 0x71, 0x79 };

// ?Lisence=%s&MAC=%s
char lisence_and_mac[] = { 0x40, 0x4b, 0x6a, 0x72, 0x66, 0x6d, 0x64, 0x64, 0x3e, 0x24, 0x74, 0x25, 0x4e, 0x40, 0x44, 0x3c, 0x26, 0x72 };

// ?Lisence=
char q_lisence_eq_[] = { 0x40, 0x4b, 0x6a, 0x72, 0x66, 0x6d, 0x64, 0x64, 0x3e };

// &MAC=
char a_mac_eq_[] = { 0x27, 0x4c, 0x42, 0x42, 0x3e };

char *stringplus(char* _a1, char* _a2)
{
	char BUF[0x30];
	strcpy(BUF, _a1);
	strcat(BUF, _a2);
	return BUF;
}
#pragma endregion

#pragma region Math
#define PI (3.14159265359)
int _round(float f) {
	int i = (int)f;
	float tiny = f - i;
	if (tiny < 0.5f) {
		return i;
	}
	else {
		return i + 1;
	}
}

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

Vector3 RotationToDirection(Vector3 rotation)
{
	float retz = rotation.z * 0.0174532924F; // Degree to radian
	float retx = rotation.x * 0.0174532924F;
	float absx = abs(SYSTEM::COS(retx));
	return newVector3(-SYSTEM::SIN(retz) * absx, SYSTEM::COS(retz) * absx, SYSTEM::SIN(retx));
}
#pragma endregion

namespace CAM2 {
	Vector3 GET_COORDS_FROM_CAM(float distance)
	{
		Vector3 Rot = GET_GAMEPLAY_CAM_ROT_orig(2);
		Vector3 Coord = GET_GAMEPLAY_CAM_COORD_orig();

		Rot.y = distance * SYSTEM::COS(Rot.x);
		Coord.x = Coord.x + Rot.y * SYSTEM::SIN(Rot.z * -1.0f);
		Coord.y = Coord.y + Rot.y * SYSTEM::COS(Rot.z * -1.0f);
		Coord.z = Coord.z + distance * SYSTEM::SIN(Rot.x);

		return Coord;
	}

	Vector3 _GET_COORDS_INFRONT(float d)
	{
		Vector3 ro = GET_GAMEPLAY_CAM_ROT_orig(2);
		Vector3 rot;
		float x = ro.z + 90;
		while (x < 0) x = x + 360;
		while (x > 360)
		{
			x = x - 360;
		}
		bool fix = false;
		if (x > 180)
		{
			fix = true;
		}
		rot.x = x;
		rot.z = ro.x;
		float cosrotz = SYSTEM::COS(rot.z);
		float x1 = 0;
		float y1 = 0;
		float z1 = d*SYSTEM::SIN(rot.z);
		if (fix == true)
		{
			rot.x = (rot.x - 180);
			x1 = -d*SYSTEM::COS(rot.x)*cosrotz;
			y1 = -d*SYSTEM::SIN(rot.x)*cosrotz;
		}
		else
		{
			x1 = d*SYSTEM::COS(rot.x)*cosrotz;
			y1 = d*SYSTEM::SIN(rot.x)*cosrotz;
		}
		Vector3 Coords = { x1, y1, z1 };
		return Coords;
	}

	Vector3 GET_COORDS_INFRONT(float Distance)
	{
		float Tan = Distance * myTan(GET_GAMEPLAY_CAM_ROT_orig(2).y, 20);
		Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, Distance, Distance * Tan);
		return Coords;
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
		return Coord;
	}
}

#pragma region Converter
bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI(char *str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0;
		res = res * 10 + str[i] - '0';
	}
	return sign*res;
}
char *ItoS(int num, bool isX = true)
{
	char buf[50];
	snprintf(buf, 50, isX ? "0x%X" : "%i", num);
	return buf;
}
float ItoF(int input)
{
	float Output = *(float *)&input;
	return Output;
}

float StoF(char* str)
{
	unsigned char abc;
	float ret = 0, fac = 1;
	for (abc = 9; abc & 1; str++) {
		abc = *str == '-' ?
			(abc & 6 ? abc & 14 : (abc & 47) | 36)
			: *str == '+' ?
			(abc & 6 ? abc & 14 : (abc & 15) | 4)
			: *str > 47 && *str < 58 ?
			abc | 18
			: (abc & 8) && *str == '.' ?
			(abc & 39) | 2
			: !(abc & 2) && (*str == ' ' || *str == '\t') ?
			(abc & 47) | 1
			:
			abc & 46;
		if (abc & 16) {
			ret = abc & 8 ? *str - 48 + ret * 10 : (*str - 48) / (fac *= 10) + ret;
		}
	}
	return abc & 32 ? -ret : ret;
}

char* FtoS(float input = 0.0f, float X = 100)
{
	//float Backup = input;
	char returnvalue[64];
	//int wholenumber = (int)input;
	//input -= wholenumber;
	//input *= X;
	//if (Backup < 0)
	//{
	//	//input *= -1; 
	//	//wholenumber *= -1;
	//	input *= -1;
	//}
	//sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	//return returnvalue;
	snprintf___(returnvalue, 64, "%3.4f", input);
	return returnvalue;
}

#pragma endregion

#pragma region PTFX
bool isPTFXCalled(char* aset)
{
	STREAMING::REQUEST_NAMED_PTFX_ASSET(aset);
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(aset);
	if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(aset))
		return true;
}

bool PartcleFX_Entity(char *FXType, char *FXName, int Entity, float X, float Y, float Z, float xRot, float yRot, float zRot, float scale)
{
	if (isPTFXCalled(FXType))
	{
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(FXName, Entity, X, Y, Z, xRot, yRot, zRot, scale, 0, 0, 0);
		//0x110752B2
		//GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(FXName, Entity, X, Y, Z, xRot, xRot, zRot, scale, 1, 1, 1);
		return true;
	}
	return false;
}

bool PartcleFX_Coord(char* FXType, char* FXName, float X = 0, float Y = 0, float Z = 0, float Pitch = 0, float Roll = 0, float Yaw = 0, float scale = 1)
{
	TPEffectBool = true;
	//if (isPTFXCalled(FXType))
	//{
	//	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(FXName, X, Y, Z, Pitch, Roll, Yaw, scale, 1, 1, 1);
	//	return true;
	//}
	//return false;
}

bool PartcleFX_Ped(char *FXType, char*FXName,Ped _Ped, Vector3 Loc, Vector3 Rot, int Bone = -1, float Scale = 1.0f)
{
	if (isPTFXCalled(FXType))
	{

		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_4(FXName, _Ped, Loc.x, Loc.y, Loc.z, Rot.x, Rot.y, Rot.z, Bone, Scale, 0, 0, 0);
		return true;
	}
}
#pragma endregion

#pragma region Teleport
int TeleportDeray;
TPtoMe2 _TPMe;
Entity EntityID;
float Zheight[2];
Vector3 _TP_Coord;
Vector3 CoordBlip;
bool TP_LowBool;
int TP_Low_Delay;
void TP_LowTexture()
{

	if (!Low_Tecture) {
		GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_SLOD2_reduce");
		addMessageShow("テレポートに伴いマップの読み込みを抑制します。");
		TP_Low_Delay = GAMEPLAY::GET_GAME_TIMER() + (isHDD ? 3500 : 1500);
		TP_LowBool = true;
	}
}

void Teleport(int PedHandle, Vector3 Coord)
{
	int handle = PedHandle;
	if (PED::IS_PED_IN_ANY_VEHICLE(handle, 0))
		handle = PED::GET_VEHICLE_PED_IS_IN(handle, 0);
	ENTITY::SET_ENTITY_COORDS(handle, Coord.x, Coord.y, Coord.z, 0, 0, 0, 1);
	if (!TeleportEffect)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
	}
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", Coord.x, Coord.y, Coord.z, 0, 0, 0, 1); //TeleportEffect
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);
	
	//GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_ROOT, 1.2, 0, 0, 0);
}

void TP(Entity _Entity, Vector3 Coord)
{
	ENTITY::SET_ENTITY_COORDS(_Entity, Coord.x, Coord.y, Coord.z, 1, 0, 0, 1);
	if (!TeleportEffect)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
	}
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", Coord.x, Coord.y, Coord.z, 0, 0, 0, 1);
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

void TPofScene(Entity _Entity, Vector3 Coord, char* anim1 = "", char *anim2 = "", bool Animt = false)
{
	if (Animt)
	{
		_TP_Coord = Coord;
		TPtoMePlayer = _Entity;
		SceneTP___[0] = anim1;
		SceneTP___[1] = anim2;
		AnimTP = true;
	}
	else
	{
		STREAMING::REMOVE_ANIM_DICT(anim1);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(_Entity);
		int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(Coord.x, Coord.y, Coord.z, 0.0, 0.0, ENTITY::GET_ENTITY_HEADING(_Entity), 9, 0, 0, 0, 0, 0);
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(_Entity, scene2, anim1, anim2, 8.0f, -8.0, 5, 0, 30, 0);
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
	}
	if (!TeleportEffect)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", _Entity, 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
	}
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", Coord.x, Coord.y, Coord.z, 0, 0, 0, 1);
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

void TPtoWaypoint()
{
	int Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0) : PLAYER::PLAYER_PED_ID();
	EntityID = Entity;

	if (UI::IS_WAYPOINT_ACTIVE())
	{
		CoordBlip = UI::GET_BLIP_INFO_ID_COORD(UI::GET_FIRST_BLIP_INFO_ID(UI::_GET_BLIP_INFO_ID_ITERATOR()));
		ENTITY::SET_ENTITY_COORDS(EntityID, CoordBlip.x, CoordBlip.y, 10, 1, 0, 0, 1);
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(CoordBlip.x, CoordBlip.y, 5000, &Zheight[0]);

		WaypointTeleport = true;
		TeleportDeray = GAMEPLAY::GET_GAME_TIMER() + 3000;
	}
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(EntityID, true);


}

void TPtoPlayer(int index)
{
	Entity Player = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
	Vector3 PlayerC = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(index), true);
	TP(Player, PlayerC);
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	if (!TeleportEffect)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
	}
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", MyCoords.x, MyCoords.y, MyCoords.z, 0, 0, 0, 1);
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

void TPtoMe(int index)
{
	_TPMe._Player = PLAYER::GET_PLAYER_PED(index);
	_TPMe.Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	if (PED::GET_VEHICLE_PED_IS_USING(_TPMe._Player))
	{
		_TPMe.Timer = GAMEPLAY::GET_GAME_TIMER() + 1000;
		_TPMe._Entity = PED::GET_VEHICLE_PED_IS_IN(_TPMe._Player, false);
		VehicleTP = true;
	}
	else
	{
		TPofScene(_TPMe._Player, _TPMe.Coord, "mini@strip_club@private_dance@part3", "priv_dance_p3");
	}
	//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", _TPMe.Coord.x, _TPMe.Coord.y, _TPMe.Coord.z, 0, 0, 0, 1);
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

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
				addMessageShow("プレイヤーの車へ乗車しました。");
			}
		}
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
		{
			addMessageShow("プレイヤーの車の空席を取得出来ませんでした。");
		}
	}
	else
	{
		addMessageShow("~r~プレイヤーが車に乗車していません。");
	}
	if (!TeleportEffect)
	{
		//Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", MyCoords.x, MyCoords.y, MyCoords.z, 0, 0, 0, 1);
	}
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

void AllTeleportToMe(int CoordPed = PLAYER::PLAYER_ID())
{
	Vector3 AAA = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(CoordPed), 1);
	int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(AAA.x, AAA.y, AAA.z, 0.0, 0.0, 0.0, 9, 0, 0, 0, 0, 0);
	for (int i = 0; i < 16; i++)
	{
		if (i != CoordPed)
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(CoordPed);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(PLAYER::GET_PLAYER_PED(i), scene2, "mini@strip_club@private_dance@part3", "priv_dance_p3", 8.0f, -8.0, 5, 0, 30, 0);
		}
	}
	NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
	if (!TeleportEffect)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, -0.5, 0, 0, 0, 31086, 1.5f, 0, 0, 0);
		}
		//Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		//PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", MyCoords.x, MyCoords.y, MyCoords.z, 0, 0, 0, 1);
	}
	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

int TP_LOCATIONVAR[10];
char *PLAYER_TP_LOCATION_1[] = { "空港", "40Kガレージ", "チリアド山", "メイズバンク", "UFO" };

char *PLAYER_TP_LOCATION_2[] = { "服屋", "ロスカス", "武器屋", "マスク", "美容室" };
char *PLAYER_TP_LOCATION_3[] = { "ヒューメイン", "ヒューメイン2", "FIB 上", "FIB オフィス", "トレバー空港", "コンテナ", "軍基地", "クレーンの上", "工事中のビルの上" };
char *PLAYER_TP_LOCATION_4[] = { "ビーチ" };
void TP_LOC(int player, Vector3 _TP)
{
	if (player != PLAYER::PLAYER_ID())
	{
		_TPMe._Player = PLAYER::GET_PLAYER_PED(player);
		_TPMe.Coord = _TP;
		if (PED::GET_VEHICLE_PED_IS_USING(_TPMe._Player))
		{
			_TPMe.Timer = GAMEPLAY::GET_GAME_TIMER() + 1000;
			_TPMe._Entity = PED::GET_VEHICLE_PED_IS_IN(_TPMe._Player, false);
			VehicleTP = true;
		}
		else
		{
			TPofScene(_TPMe._Player, _TPMe.Coord, "mini@strip_club@private_dance@part3", "priv_dance_p3");
		}
	}
	else
	{
		if (!Teleanim)
		{
			Teleport(PLAYER::GET_PLAYER_PED(player), _TP);
		}
		else
		{
			PosX = _TP.x; PosY = _TP.y; PosZ = _TP.z;
			STREAMING::LOAD_ALL_OBJECTS_NOW();
			move1 = true;
		}
	}

	//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
	//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

}

void TP_LOC_1(int player, int index)
{
	Vector3 _TP_Coord;
	switch (index)
	{
	case 0:_TP_Coord.x = -1102.2910; _TP_Coord.y = -2894.5160; _TP_Coord.z = 13.9467; break;
	case 1:_TP_Coord.x = -796; _TP_Coord.y = 300; _TP_Coord.z = 85; break;
	case 2:_TP_Coord.x = 495; _TP_Coord.y = 5586; _TP_Coord.z = 794; break;
	case 3:_TP_Coord.x = -75; _TP_Coord.y = -818; _TP_Coord.z = 326; break;
	case 4:_TP_Coord.x = 762; _TP_Coord.y = 7388; _TP_Coord.z = -110; break;
	}
	TP_LOC(player, _TP_Coord);

}

void TP_LOC_2(int player, int index)
{
	Vector3 _TP_Coord;
	switch (index)
	{
	case 0:_TP_Coord.x = -723; _TP_Coord.y = -162; _TP_Coord.z = 36; break;
	case 1:_TP_Coord.x = -375; _TP_Coord.y = -129; _TP_Coord.z = 38; break;
	case 2:_TP_Coord.x = 250; _TP_Coord.y = -48; _TP_Coord.z = 69; break;
	case 3:_TP_Coord.x = -1339; _TP_Coord.y = -1278; _TP_Coord.z = 4; break;
	case 4:_TP_Coord.x = -27; _TP_Coord.y = -138; _TP_Coord.z = 56; break;
	}
	TP_LOC(player, _TP_Coord);
}

void TP_LOC_3(int player, int index)
{
	Vector3 _TP_Coord;
	switch (index)
	{
	case 0:_TP_Coord.x = 3615; _TP_Coord.y = 3738; _TP_Coord.z = 28; break;
	case 1:_TP_Coord.x = 3525; _TP_Coord.y = 3709; _TP_Coord.z = 20; break;

	case 2:_TP_Coord.x = 137; _TP_Coord.y = -749; _TP_Coord.z = 257; break;
	case 3:_TP_Coord.x = 115; _TP_Coord.y = -745; _TP_Coord.z = 242; break;
	case 4:_TP_Coord.x = 1792; _TP_Coord.y = 3247; _TP_Coord.z = 42; break;
	case 5:_TP_Coord.x = 978; _TP_Coord.y = -3061; _TP_Coord.z = 5; break;
	case 6:_TP_Coord.x = -2264; _TP_Coord.y = 3200; _TP_Coord.z = 32; break;
	case 7:_TP_Coord.x = -102; _TP_Coord.y = -967; _TP_Coord.z = 296; break;
	case 8:_TP_Coord.x = -146; _TP_Coord.y = -963; _TP_Coord.z = 269; break;
	}
	TP_LOC(player, _TP_Coord);
}
void TP_LOC_4(int player, int index)
{
	Vector3 _TP_Coord;
	switch (index)
	{
	case 0:_TP_Coord.x = -1420; _TP_Coord.y = -1548; _TP_Coord.z = 4; break;

	}
	TP_LOC(player, _TP_Coord);
}

void _CreateTeleport(Cam *Cam)
{
	*Cam = CAM::CREATE_CAMERA(26379945, false);
	CAM::SET_CAM_ACTIVE(*Cam, true);
	CAM::SET_CAM_COORD(*Cam, PosX, PosY, PosZ + AlturaTeleport);
}

#pragma endregion

#pragma region Object_
bool REQUEST_MODEL(char *strings)
{
	Hash _Hash = GAMEPLAY::GET_HASH_KEY(strings);
	if (STREAMING::HAS_MODEL_LOADED(_Hash))
		true;
	else
	{
		STREAMING::REQUEST_MODEL(_Hash);
	}
}

bool REQUEST_MODEL(Hash hashs)
{
	Hash _Hash = hashs;
	if (STREAMING::HAS_MODEL_LOADED(_Hash))
		true;
	else
	{
		STREAMING::REQUEST_MODEL(_Hash);
	}
}

bool SET_MODEL_AS_NO_LONGER_NEEDED(char *strings)
{
	Hash _hash = GAMEPLAY::GET_HASH_KEY(strings);
	if (!STREAMING::HAS_MODEL_LOADED(_hash))
		true;
	else
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_hash);
}

bool SET_MODEL_AS_NO_LONGER_NEEDED(Hash _hashs)
{
	Hash _hash = _hashs;
	if (!STREAMING::HAS_MODEL_LOADED(_hash))
		true;
	else
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_hash);
}

void ApplyForce(int entity, Vector3 xyz, Vector3 rot)
{
	ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, xyz.x, xyz.y, xyz.z, rot.x, rot.y, rot.z, 0, 1, 1, 1, 0, 1);
}
void Freeze(Ped selectedPed)
{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
	AI::CLEAR_PED_SECONDARY_TASK(selectedPed);
}
void ATTACH_ENTITY_TO_ENTITY(int Entity, int Entity2, int BoneIndex, Vector3 xyz, Vector3 pry, int Zero = true, float Solid = true, float Dirty = false, int _Zero = false, int Two = 2, int One = 1)
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(Entity, Entity2, BoneIndex, xyz.x, xyz.y, xyz.z, pry.x, pry.y, pry.z, Zero, Solid, Dirty, _Zero, Two, One);
}

void ATTACH_ENTITY_TO_ENTITY_1(Entity entity1, Entity entity2, int boneIndex = 0x0, float x = 0, float y = 0, float z = 0, float rot_x = 0, float rot_y = 0, float rot_z = 0)
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(entity1, entity2, boneIndex, x, y, z, rot_x, rot_y, rot_z, true, true, true, true, true, true);
}

void SetCollision(Entity _Entity, bool Collision)// trueすり抜け
{
	ENTITY::SET_ENTITY_COLLISION(_Entity, Collision, 1);
}

void freeze_entity_position(Entity _Entity, bool freeze)
{
	ENTITY::FREEZE_ENTITY_POSITION(_Entity, freeze);
}

void DeleteEntity(Entity _Entity)
{
	if (ENTITY::DOES_ENTITY_EXIST(_Entity))
	{
		ENTITY::DETACH_ENTITY(_Entity, 1, 1);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(_Entity, 1, 1);
		ENTITY::DELETE_ENTITY(&_Entity);
	}
}

int GetClosestVehicle(Vector3 Coords, float Distance)
{
	int Flag;
	Flag = 64;
	Flag |= 65536;
	Flag |= 2048;
	Flag |= 1;
	Flag |= 2;
	Flag |= 4;
	Flag |= 32;
	Flag |= 16;
	Flag |= 8;
	return VEHICLE::GET_CLOSEST_VEHICLE(Coords.x, Coords.y, Coords.z, Distance, 0, Flag);
}

void Oscillate(Entity _Entity, Vector3 position, float angleFreq, float dampRatio)
{
	Vector3 EntityPos = ENTITY::GET_ENTITY_COORDS(_Entity, true);
	Vector3 Velocity = ENTITY::GET_ENTITY_VELOCITY(_Entity);

	Vector3 ApplyPOS;
	ApplyPOS.x = ((position.x - EntityPos.x) * (angleFreq * angleFreq)) - (2.0f * angleFreq * dampRatio * Velocity.x);
	ApplyPOS.y = ((position.y - EntityPos.y) * (angleFreq * angleFreq)) - (2.0f * angleFreq * dampRatio * Velocity.y);
	ApplyPOS.z = ((position.z - EntityPos.z) * (angleFreq * angleFreq)) - (2.0f * angleFreq * dampRatio * Velocity.z) + 0.1f;
	//Zorg93 - bring entity to position without lerp function using applyforce
	ENTITY::APPLY_FORCE_TO_ENTITY(_Entity, 1, ApplyPOS.x, ApplyPOS.y, ApplyPOS.z, 0, 0, 0, false, false, true, true, false, true);
}

void dropPickup(Vector3 Location, char* PickupModel, char* PickupBehavior, int PickupAmount, char* DisplayName, int Client)
{
	int Model = GAMEPLAY::GET_HASH_KEY(PickupModel);
	int Behavior = GAMEPLAY::GET_HASH_KEY(PickupBehavior); //"PICKUP_MONEY_CASE"
	REQUEST_MODEL(Model);
	if (STREAMING::HAS_MODEL_LOADED(Model))
	{
		OBJECT::CREATE_AMBIENT_PICKUP(Behavior, Location.x, Location.y, Location.z, 0, PickupAmount, Model, 0, 2);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
	}
}

void makePropNotUnspawn(int prop) { ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop, 1, 1); }

void ToggleFreezeEntity(Entity obj, bool flag)
{
	ENTITY::FREEZE_ENTITY_POSITION(obj, flag);
}

void ToggleCollisionEntity(Entity obj, bool flag)
{
	ENTITY::SET_ENTITY_COLLISION(obj, flag, 1);
}
int entitiesPoolPart1, entitiesPoolPart2, AllEntity_A = 0x1CC5780;
int entitiesPoolPart3, entitiesPoolPart4;
int worldGetAllEntities(int entitiesArr)
{
	int j;
	for (int i = 0; i < 500; i++)
	{
	
		if (*(int*)((i * 8) + entitiesPoolPart1) == 0x18FC520)
		{
			*(int*)(entitiesArr + (4 * i)) = (i << 8) | (*(char*)(i + entitiesPoolPart2));		
			j++;
		}
	}
	return j;
}

void do_NetGetAllEntities()
{	
	for (int i = 0; i < 500; i++)
	{
		char _entity = *(char*)(i + 0x400C5020);
		if (_entity != 0x81)
		{
			*(int*)(0x10030000 + (0x04 * i)) = (i << 8) | _entity;
		}
	}
	
}


int count;
OPD_s GetEntityFromScriptIndex_t = { 0xA55270 ,TOC };
OPD_s GetNetGamePlayerFromPhysicalIndex_t = { 0x12F70E8 ,TOC };
OPD_s ChangeNetObjOwner_t = { 0xA117B8 ,TOC };
unsigned long(*GetEntityFromScriptIndex)(int scriptIndex) = (unsigned long(*)(int))&GetEntityFromScriptIndex_t;
unsigned long(*GetNetGamePlayerFromPhysicalIndex)(char physicalIndex) = (unsigned long(*)(char))&GetNetGamePlayerFromPhysicalIndex_t;
void(*ChangeNetObjOwner)(unsigned long networkObjectMgr, unsigned long netObj, unsigned long netGamePlayer, unsigned long a4) = (void(*)(unsigned long, unsigned long, unsigned long, unsigned long))&ChangeNetObjOwner_t;
void ChangeEntityOwner(int scriptIndex, int _playerid)
{
	unsigned long networkObjectMgr = *(unsigned long*)(0x1CF72AC);
	if (networkObjectMgr)
	{
		unsigned long netGamePlayer = GetNetGamePlayerFromPhysicalIndex(_playerid);
		if (netGamePlayer)
		{
			unsigned long entityStruct = GetEntityFromScriptIndex(scriptIndex);
			if (entityStruct)
			{
				unsigned long netObj = *(unsigned long*)(entityStruct + 0x4C);
				if (netObj)
				{
					ChangeNetObjOwner(networkObjectMgr, netObj, netGamePlayer, 0xFFFFFFFF);
				}
			}
		}
	}
}
void NetObjectRemove()
{
	//do_NetGetAllEntities();
	for (int i = 0; i < 0xF0; i++)
	{
		int _entity = *(char*)(i + 0x400C5020);
		if ( !(_entity > 0x80) && _entity != 0x00)
		{
			Entity _Entity = (i << 8) | _entity;
			printf("Detected : 0x%X, 0x%X", _Entity, _entity);
			if (_Entity != NULL && ENTITY::DOES_ENTITY_EXIST(_Entity) && _Entity != PLAYER::PLAYER_PED_ID() && !ENTITY::IS_ENTITY_A_PED(_Entity))
			{
				ChangeEntityOwner(_Entity, PLAYER::PLAYER_ID());
				//NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_Entity);
				//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(_Entity, 1, 1);
				ENTITY::DELETE_ENTITY(&_Entity);
			}
		}

	}
}
void AllObjectRemove()
{

	int _PartA = PS3::ReadUInt32(0x1CC5780);
	//int _PartB = PS3::ReadUInt32(0x1CC37D0);
	if (_PartA > 0x20000000)
	{
		entitiesPoolPart1 = PS3::ReadUInt32(_PartA);
		entitiesPoolPart2 = PS3::ReadUInt32((_PartA)+4);
		//entitiesPoolPart3 = PS3::ReadUInt32(_PartB);
		//entitiesPoolPart4 = PS3::ReadUInt32(_PartB + 4);
		if (entitiesPoolPart1 > 0x20000000)
		{
			int count = worldGetAllEntities(0x10020000);
			if (count != 0)
			{
				for (int i = 0; i < 1000; i++)
				{
					Entity _Entity = PS3::ReadUInt32(0x10020000 + (0x04 * i));
					if (_Entity != NULL && ENTITY::DOES_ENTITY_EXIST(_Entity) && _Entity != PLAYER::PLAYER_PED_ID() && ENTITY::IS_ENTITY_ATTACHED(_Entity) && !ENTITY::IS_ENTITY_A_PED(_Entity))
					{
						printf("Detected");
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_Entity);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(_Entity, 1, 1);
						ENTITY::DELETE_ENTITY(&_Entity);
					}

				}
			}
		}
	}
}

void _AllObjectRemove()
{

	int _PartA = PS3::ReadUInt32(0x1CC5780);
	//int _PartB = PS3::ReadUInt32(0x1CC37D0);
	if (_PartA > 0x20000000)
	{
		entitiesPoolPart1 = PS3::ReadUInt32(_PartA);
		entitiesPoolPart2 = PS3::ReadUInt32((_PartA)+4);
		//entitiesPoolPart3 = PS3::ReadUInt32(_PartB);
		//entitiesPoolPart4 = PS3::ReadUInt32(_PartB + 4);
		if (entitiesPoolPart1 > 0x20000000)
		{
			int count = worldGetAllEntities(0x10020000);
			if (count != 0)
			{
				for (int i = 0; i < 1000; i++)
				{
					Entity _Entity = PS3::ReadUInt32(0x10020000 + (0x04 * i));
					if (_Entity != NULL && ENTITY::DOES_ENTITY_EXIST(_Entity) && _Entity != PLAYER::PLAYER_PED_ID() && !ENTITY::IS_ENTITY_A_PED(_Entity))
					{
						printf("Detected");
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_Entity);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(_Entity, 1, 1);
						ENTITY::DELETE_ENTITY(&_Entity);
					}

				}
			}
		}
	}
}
#pragma endregion

#pragma region RCE
struct sync_data_writer_s {
	char pad[0xC];
	int sync_data;
};
OPD_s write_sync_data_i32_f = { 0x16547D4, TOC };
bool(*write_sync_data_i32_t)(sync_data_writer_s*, int*, int) = (bool(*)(sync_data_writer_s*, int*, int))&write_sync_data_i32_f;

OPD_s send_give_pickup_rewards_event_f = { 0x12D20DC, TOC };
void(*send_give_pickup_rewards_event_t)(int, int) = (void(*)(int, int))&send_give_pickup_rewards_event_f;

bool remote_memory_sent_payload = false;
int remote_memory_p_index = 0;
int remote_memory_address = 0;
int remote_memory_value = 0;
int remote_memory_payload[] = {
	/*0*/0xDEADC0DE,
	/*1*/0xDEADC0DE,
	/*2*/0xDEADC0DE,
	/*3*/0xDEADC0DE,
	/*4*/0xDEADC0DE,
	/*5*/0xFFFFFFFF, // Iter
	/*6*/0xFFFFFFFF, // Set r25
	/*7*/0xFFFFFFFF,
	/*8*/0xDEADC0DE, // Set r26
	/*9*/0xDEADC0DE, // "
	/*10*/0xDEADC0DE, // Set r27
	/*11*/0xDEADC0DE, // "
	/*12*/0xDEADC0DE, // Set r28
	/*13*/0xDEADC0DE, // "
	/*14*/0xFFFFFFFF, // Set r29
	/*15*/0xFFFFFFFF, // "
	/*16*/0xDEADC0DE, // Set r30
	/*17*/0xDEADC0DE, // "
	/*18*/0xDEADC0DE, // Set r31
	/*19*/0xDEADC0DE, // "
	/*20*/0xDEADC0DE,
	/*21*/0xDEADC0DE,
	/*22*/0xDEADC0DE,
	/*23*/0xDEADC0DE,
	/*24*/0x00000000,
	/*25*/0x01046990
};
bool remote_memory_recipient_targetter(void* net_game_event, char* net_game_player) {
	return (int)(net_game_player[0x29]) == remote_memory_p_index;
}
void remote_memory_payload_manipulator(void* net_game_event, int sync_data) {
	sync_data_writer_s writer;
	writer.sync_data = sync_data;
	int original_iter = 0x00000007;
	write_sync_data_i32_t(&writer, &original_iter, 0x00000003);
	write_sync_data_i32_t(&writer, &remote_memory_payload[0], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[1], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[2], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[3], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[4], 0x00000020);
	remote_memory_payload[5] = 26;//sizeof(remote_memory_payload) / sizeof(int);
	write_sync_data_i32_t(&writer, &remote_memory_payload[5], 0x00000020);
	remote_memory_payload[6] = 0;
	remote_memory_payload[7] = remote_memory_value;
	write_sync_data_i32_t(&writer, &remote_memory_payload[6], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[7], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[8], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[9], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[10], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[11], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[12], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[13], 0x00000020);
	remote_memory_payload[14] = 0;
	remote_memory_payload[15] = remote_memory_address;
	write_sync_data_i32_t(&writer, &remote_memory_payload[14], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[15], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[16], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[17], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[18], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[19], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[20], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[21], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[22], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[23], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[24], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_memory_payload[25], 0x00000020);
	remote_memory_sent_payload = true;
}
void remote_memory(int p_index, int address, int value) {
	remote_memory_p_index = p_index;
	if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(remote_memory_p_index))
	{
		return;
	}
	remote_memory_address = address;
	remote_memory_value = value;
	*(int*)(0x1C6C600) = *(int*)((int)&remote_memory_payload_manipulator);
	*(int*)(0x1C6C604) = *(int*)((int)&remote_memory_payload_manipulator + 0x4);
	*(int*)(0x1C6C620) = *(int*)((int)&remote_memory_recipient_targetter);
	*(int*)(0x1C6C624) = *(int*)((int)&remote_memory_recipient_targetter + 0x4);
	send_give_pickup_rewards_event_t(remote_memory_p_index << 1, 0x1337);
}

bool remote_native_sent_p = false;
int remote_native_p_index = 0;
OPD_s remote_native_opd_str = { 0, 0 };
int remote_native_arg[10] = { 0 };
int remote_native_arg_cnt = 0;

int remote_native_payload[] = { // dnt remove comments, they there just in case we lose it
	/*0*/0x10050000, // Return Values Pointer
	/*1*/0xFFFFFFFF, // Argument Count
	/*2*/0xD003DE48, // Native Arguments Pointer
	/*3*/0x00000000, // Data Count
	/*4*/0x10060000, // Vector Data Pointer
					 // 0xD003DE44 - Set New Loop Iteration
					 /*5*/0xFFFFFFFF, // Iter
									  // 0xD003DE48 - Native Arguments
									  /*6*/0xFFFFFFFF, // Set r25
									  /*7*/0xFFFFFFFF,
									  /*8*/0xFFFFFFFF, // Set r26
									  /*9*/0xFFFFFFFF, // "
									  /*10*/0xFFFFFFFF, // Set r27
									  /*11*/0xFFFFFFFF, // "
									  /*12*/0xFFFFFFFF, // Set r28
									  /*13*/0xFFFFFFFF, // "
									  /*14*/0xFFFFFFFF, // Set r29
									  /*15*/0xFFFFFFFF, // "
														// 0xD003DE70 - Set Ptr To Native Context
														/*16*/0x00000000, // Set r30
														/*17*/0xD003DE30, // "
																		  // 0xD003DE78 - Pointer To Native Address
																		  /*18*/0x00000000, // Set r31
																		  /*19*/0xD003DE80, // "
																							// 0xD003DE80 - Native Address
																							/*20*/0xFFFFFFFF, // Set r5
																											  // 0xD003DE84 - Hextic Hacks String
																											  /*21*/0x68657874,
																											  /*22*/0x69636861,
																											  /*23*/0x636B7321,
																											  // 0xD003DE90 - Link Register
																											  /*24*/0x00000000,
																											  /*25*/0x009F4A44,
};

void remote_native_payload_manipu(void* net_game_event, int sync_data) {
	sync_data_writer_s writer;
	writer.sync_data = sync_data;
	int original_iter = 0x00000007;
	write_sync_data_i32_t(&writer, &original_iter, 0x00000003);
	write_sync_data_i32_t(&writer, &remote_native_payload[0], 0x00000020);
	remote_native_payload[1] = remote_native_arg_cnt;
	write_sync_data_i32_t(&writer, &remote_native_payload[1], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[2], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[3], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[4], 0x00000020);
	remote_native_payload[5] = sizeof(remote_native_payload) / sizeof(int);
	write_sync_data_i32_t(&writer, &remote_native_payload[5], 0x00000020);
	remote_native_payload[6] = remote_native_arg[0];
	remote_native_payload[7] = remote_native_arg[1];
	remote_native_payload[8] = remote_native_arg[2];
	remote_native_payload[9] = remote_native_arg[3];
	remote_native_payload[10] = remote_native_arg[4];
	remote_native_payload[11] = remote_native_arg[5];
	remote_native_payload[12] = remote_native_arg[6];
	remote_native_payload[13] = remote_native_arg[7];
	remote_native_payload[14] = remote_native_arg[8];
	remote_native_payload[15] = remote_native_arg[9];
	write_sync_data_i32_t(&writer, &remote_native_payload[6], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[7], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[8], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[9], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[10], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[11], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[12], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[13], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[14], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[15], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[16], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[17], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[18], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[19], 0x00000020);
	remote_native_payload[20] = remote_native_opd_str.sub;
	write_sync_data_i32_t(&writer, &remote_native_payload[20], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[21], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[22], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[23], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[24], 0x00000020);
	write_sync_data_i32_t(&writer, &remote_native_payload[25], 0x00000020);
	remote_native_sent_p = true;
}

bool remote_native_payload_tester(void* net_game_event, char* net_game_player) {
	return (int)(net_game_player[0x29]) == remote_native_p_index;
}

void call_remote_native(int p_index, int native_hash, int arg_cnt) {
	remote_native_p_index = p_index;
	if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(remote_native_p_index)) {
		return;
	}
	int remote_native_address = GetBls(GetNative(native_hash))[1];
	if (remote_native_address == NULL) {
		return;
	}
	remote_native_opd_str = *(OPD_s*)(remote_native_address);
	remote_native_opd_str.toc = 0x1C85330;
	if (remote_native_opd_str.sub == NULL || remote_native_opd_str.toc == NULL) {
		return;
	}
	remote_native_arg_cnt = arg_cnt;
	if (remote_native_arg_cnt > 10) {

		return;
	}
	*(int*)(0x1C6C600) = *(int*)((int)&remote_native_payload_manipu);
	*(int*)(0x1C6C604) = *(int*)((int)&remote_native_payload_manipu + 0x4);
	*(int*)(0x1C6C620) = *(int*)((int)&remote_native_payload_tester);
	*(int*)(0x1C6C624) = *(int*)((int)&remote_native_payload_tester + 0x4);
	send_give_pickup_rewards_event_t(remote_native_p_index << 1, 0x1337);
}

void call_remote_native_onAddress(int p_index, int address, int arg_cnt) {
	remote_native_p_index = p_index;
	if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(remote_native_p_index)) {
		return;
	}
	int remote_native_address = address;
	if (remote_native_address == NULL) {
		return;
	}
	//0x42BD9C
	OPD_s _a = { address, 0x1C85330 };
	remote_native_opd_str = _a;
	//remote_native_opd_str = *(OPD_s*)(remote_native_address);
	//remote_native_opd_str.toc = 0x1C85330;
	if (remote_native_opd_str.sub == NULL || remote_native_opd_str.toc == NULL) {
		return;
	}
	remote_native_arg_cnt = arg_cnt;
	if (remote_native_arg_cnt > 10) {

		return;
	}
	printf("Rced\n");
	*(int*)(0x1C6C600) = *(int*)((int)&remote_native_payload_manipu);
	*(int*)(0x1C6C604) = *(int*)((int)&remote_native_payload_manipu + 0x4);
	*(int*)(0x1C6C620) = *(int*)((int)&remote_native_payload_tester);
	*(int*)(0x1C6C624) = *(int*)((int)&remote_native_payload_tester + 0x4);
	send_give_pickup_rewards_event_t(remote_native_p_index << 1, 0x1337);

}
#pragma endregion

#pragma region ReadUint32on RCE
void *Memcpy(void *dst0, const void *src0, size_t len0)
{
	char *dst = (char *)dst0;
	char *src = (char *)src0;
	void *save = dst0;
	while (len0--)
		*dst++ = *src++;
	return save;
}

int32_t write_process(uint64_t ea, const void * data, uint32_t size)
{
	memcpy((void*)ea, data, size);
}

void do_WriteFreeAddress(int address, int value)
{

	//printf("-----------------------");

	//int freeMem = 0x10054300;
	//int frees[] = { 0x10054300, 0x10054301, 0x10054302,0x10054303,0x10054304, 0x10054305 };
	//char bytes[] = { 0xFF, 0xBB, 0xF2, 0xCC, 0x55, 0x00 };
	*(char*)0x10054300 = 0xFF;
	//*(char*)0x10054301 = 0xBB;
	//*(char*)0x10054302 = 0xF2;
	//*(char*)0x10054303 = 0xCC;
	//*(char*)0x10054304 = 0x55;
	//*(char*)0x10054305 = 0x00;
	//write_process(freeMem, bytes, 6);

	//int freeMem = 0x10054300;
	//*(int*)(freeMem + 0x00) = 0xFF11FFBB;
	//*(int*)(freeMem + 0x04) = *(int*)freeMem;
	//*(int*)(freeMem + 0x08) = 0xFFFFCFFF;
	//PS3::WriteUInt32(freeMem + 0x0C, PS3::ReadUInt32(freeMem + 0x04));
	//*(int*)(freeMem + 0x0C) = 0xFFFF3FBB;

	//printf("-----------------------");
}
#pragma endregion

#pragma region FileDownloader

void myf(char *s1, char *s2)
{
	char *p = s1;

	p = strstr(s1, s2);
	if (p != NULL) {
		strcpy(p, p + strlen(s2));
		myf(p + 1, s2);
	}

}
char* remove_headers(char* request)
{
	char* output = strstr(request, "\r\n\r\n");
	if (output == NULL) {
		return NULL;
	}
	output += 2;
	return output;
}

char get_cmd[0x100];
char _get_cmd[0x100];
int DownloadFile(char* ip = "", char *location = "", const char* fileName = "") {
	struct sockaddr_in sockaddr;
	struct hostent *host;
	unsigned int temp;

	CellFsErrno check_status;
	int fd = -1;
	//printf("\n\nTest\n\n");
	char RequestBuf[300];
	check_status = cellFsOpen(fileName, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_APPEND, &fd, NULL, 0);
	if (check_status != CELL_OK) {
		//printf("\n\n[DownloadFile] failed with cellFsOpen() 0x%x\n\n\n", fd);
		return -1;
	}
	else
	{
		//printf("\n\n[DownloadFile] Created 0x%x\n\n\n", fd);
	}
	bool connected = false;
	int sock;
	int offset = 0;
	int total = 0;
	if ((unsigned int)-1 != (temp = inet_addr(ip))) {
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = temp;
		//printf("\n\n[DownloadFile] Host : [TEMP]0x%x\n\n\n", temp);

	}
	else {
		if (NULL == (host = gethostbyname(ip))) {
			return 0;
		}
		//printf("\n\n[DownloadFile] Host : [HOST]0x%x\n\n\n", *((unsigned long*)host->h_addr));
		sockaddr.sin_family = host->h_addrtype;
		memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);
	}
	//host = gethostbyname(ip);
	
	//printf("\n\n[DownloadFile] Host : 0x%x\n\n\n", *((unsigned long*)host->h_addr));
	
	char responseBuffer[0xE4];
	sockaddr.sin_port = htons(80); //Choose any port you want (needs to be opened on your server)
	//sockaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	sock = socket(sockaddr.sin_family, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
		//printf("\n\n[DownloadFile] failed connecting with socket\n\n\n");
		return -1;
	}
	else
	{
		//printf("\n\n[DownloadFile] Connected with socket\n\n\n");
	}

	strcpy(RequestBuf, "GET /");// GET /line/
	strcat(RequestBuf, location);
	strcat(RequestBuf, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuf, ip);
	//strcat(RequestBuf, "/");
	//strcat(RequestBuf, location);
	strcat(RequestBuf, "\r\n\r\n");
	send(sock, RequestBuf, strlen(RequestBuf), 0);
	//printf("\n\n[DownloadFile]\n %s, 0x%X\n\n", RequestBuf, strlen(RequestBuf));

	char output[100];
	int r, size = 632120; //size needs to be hardcoded OR you need to request the filesize from the socket server beforehand

	int lastPercent = 0;
	int progress = 0;
	int delta;

	//cellMsgDialogOpen2(
	//	CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE | CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE,
	//	"アプデ完了 _ 2",
	//	NULL,
	//	NULL,
	//	NULL
	//);
	while ((r = recv(sock, responseBuffer, sizeof(responseBuffer), 0)) > 0) {
		//printf(responseBuffer);
		total += r;
		delta = total * 100 / size - progress;
		progress += delta;
		//cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, delta);
		//if (offset == 0)
		//{
			//cellFsWrite(fd, responseBuffer, r, NULL);
			//char* z = remove_headers(responseBuffer);
			//cellFsWrite(fd, z, strlen(z), NULL);
		//}
		//else
		if (offset != 0)
			cellFsWrite(fd, responseBuffer, r, NULL);
		offset++;
	}
	
	//cellMsgDialogClose(0);

	if (total == 0) {
		//printf("[DownloadFile] No data was received\n");
		return -1;
	}

	//printf("[DownloadFile] Done reading %d bytes\n", total);
	return 0;
}

char get_cmd_2[0x100];
char* Chat_Download(char* ip = "", char *location = "") {
	char get_cmd_2[0x100];
	strcpy(get_cmd_2, "");
	struct sockaddr_in sockaddr;
	struct hostent *host;
	unsigned int temp;
	char RequestBuf[300];
	CellFsErrno check_status;
	int fd = -1;
	bool connected = false;
	int sock;
	int offset = 0;
	int total = 0;


	sleep(2000);
	host = gethostbyname(ip);
	if ((unsigned int)-1 != (temp = inet_addr(ip))) {
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = temp;
	}
	else {
		if (host == NULL) {
			return "<Network Error>";

		}
		sockaddr.sin_family = host->h_addrtype;
		memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);
	}
	char responseBuffer[0x83];
	sockaddr.sin_port = htons(80); //Choose any port you want (needs to be opened on your server)
								   //sockaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	sock = socket(sockaddr.sin_family, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
		return "<Network Error>";
	}

	strcpy(RequestBuf, "GET /");// GET /line/
	strcat(RequestBuf, location);
	//strcat(RequestBuf, GET_);
	strcat(RequestBuf, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuf, ip);
	strcat(RequestBuf, "\r\n\r\n");
	send(sock, RequestBuf, strlen(RequestBuf), 0);
	int r; //size needs to be hardcoded OR you need to request the filesize from the socket server beforehand
	while ((r = recv(sock, responseBuffer, sizeof(responseBuffer), 0)) > 0) {
		total += r;
		strcpy(get_cmd_2, responseBuffer);
	}
	socketclose(sock);
	if (total != 0)
		return get_cmd_2;
}

int _Index;
int Redirect(char* ip = "", char *location = "", char* GET_ = "") {
	strcpy(get_cmd_2, "");
	struct sockaddr_in sockaddr;
	struct hostent *host;
	unsigned int temp;
	char RequestBuf[300];
	CellFsErrno check_status;
	int fd = -1;
	bool connected = false;
	int sock;
	int offset = 0;
	int total = 0;


	sleep(2000);
	host = gethostbyname(ip);
	if ((unsigned int)-1 != (temp = inet_addr(ip))) {
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = temp;
	}
	else {
		if (host == NULL) {
			return 2;
		}
		sockaddr.sin_family = host->h_addrtype;
		memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);
	}
	char responseBuffer[0x83];
	sockaddr.sin_port = htons(80); //Choose any port you want (needs to be opened on your server)
								   //sockaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	sock = socket(sockaddr.sin_family, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
		return 1;
	}

	strcpy(RequestBuf, "GET /");// GET /line/
	strcat(RequestBuf, location);
	strcat(RequestBuf, GET_);
	strcat(RequestBuf, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuf, ip);
	strcat(RequestBuf, "\r\n\r\n");
	send(sock, RequestBuf, strlen(RequestBuf), 0);
	int r; //size needs to be hardcoded OR you need to request the filesize from the socket server beforehand
	while ((r = recv(sock, responseBuffer, sizeof(responseBuffer), 0)) > 0) {
		total += r;
		strcpy(get_cmd_2, responseBuffer);
	}
	socketclose(sock);
	if (total != 0)
		return 0;	
}

#define SERVER_PORT htons(80)
int Socket_1;
struct hostent *Host2;
char bufferReturn[2000];
char RequestBufferV2[2000];
char saveBuf[256];
struct sockaddr_in SocketAddress;
char* GetResponseBody(char* responseBuffer) {
	char* output = strstr(responseBuffer, "\r\n\r\n");
	if (output == NULL) {
		return NULL;
	}
	output += 4;
	return output;
}
char* SocketRequest(char* URL, char* request)
{
	memset(bufferReturn, 0, 2000);
	memset(saveBuf, 0, 256);
	Host2 = gethostbyname(URL);
	SocketAddress.sin_addr.s_addr = *((unsigned long*)Host2->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket_1 = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Socket_1, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0)
	{
		printf("CONNECTION ERROR\n");
	}
	else
	{
		strcpy(RequestBufferV2, "GET /"); //exemple = GET /request HTTP/1.0\r\nHOST: website.com\r\n\r\n
		strcat(RequestBufferV2, request);
		strcat(RequestBufferV2, " HTTP/1.0\r\nHOST: "); //HTTP 1.0 or HTTP 1.1 (depend website)
		strcat(RequestBufferV2, URL);
		strcat(RequestBufferV2, "\r\n\r\n");
		send(Socket_1, RequestBufferV2, strlen(RequestBufferV2), 0);
		while (recv(Socket_1, bufferReturn, 10000, 0) > 0)
		{
			sprintf(saveBuf, "%s", GetResponseBody(bufferReturn));
			return saveBuf;
		}
		socketclose(Socket_1);
	}
}
int DownloadFile_(char* ip = "", char *location = "", const char* fileName = "", char* GET_ = "") {
	struct sockaddr_in sockaddr;
	struct hostent *host;
	unsigned int temp;

	CellFsErrno check_status;
	int fd = -1;
	//printf("\n\nTest\n\n");
	char RequestBuf[300];
	check_status = cellFsOpen(fileName, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_APPEND, &fd, NULL, 0);
	if (check_status != CELL_OK) {
		//printf("\n\n[DownloadFile] failed with cellFsOpen() 0x%x\n\n\n", fd);
		return -1;
	}
	else
	{
		//printf("\n\n[DownloadFile] Created 0x%x\n\n\n", fd);
	}
	bool connected = false;
	int sock;
	int offset = 0;
	int total = 0;
	if ((unsigned int)-1 != (temp = inet_addr(ip))) {
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.s_addr = temp;
		//printf("\n\n[DownloadFile] Host : [TEMP]0x%x\n\n\n", temp);

	}
	else {
		if (NULL == (host = gethostbyname(ip))) {
			return 0;
		}
		//printf("\n\n[DownloadFile] Host : [HOST]0x%x\n\n\n", *((unsigned long*)host->h_addr));
		sockaddr.sin_family = host->h_addrtype;
		memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);
	}
	//host = gethostbyname(ip);

	//printf("\n\n[DownloadFile] Host : 0x%x\n\n\n", *((unsigned long*)host->h_addr));

	char responseBuffer[0x83];
	sockaddr.sin_port = htons(80); //Choose any port you want (needs to be opened on your server)
								   //sockaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	sock = socket(sockaddr.sin_family, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
		//printf("\n\n[DownloadFile] failed connecting with socket\n\n\n");
		return -1;
	}
	else
	{
		//printf("\n\n[DownloadFile] Connected with socket\n\n\n");
	}

	strcpy(RequestBuf, "GET /");// GET /line/
	strcat(RequestBuf, location);
	strcat(RequestBuf, GET_);
	strcat(RequestBuf, " HTTP/1.0\r\nHOST: ");
	
	strcat(RequestBuf, ip);
	//strcat(RequestBuf, "/");
	//strcat(RequestBuf, location);
	strcat(RequestBuf, "\r\n\r\n");
	send(sock, RequestBuf, strlen(RequestBuf), 0);
	//printf("\n\n[DownloadFile]\n %s, 0x%X\n\n", RequestBuf, strlen(RequestBuf));

	char output[100];
	int r, size = 700000; //size needs to be hardcoded OR you need to request the filesize from the socket server beforehand

	int lastPercent = 0;
	int progress = 0;
	int delta;
	Dialog::ShowText("最新版SPRXをダウンロード中");
	Dialog::SetProgressText("");
	//cellMsgDialogOpen2(
	//	CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE | CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE,
	//	"アプデ完了 _ 2",
	//	NULL,
	//	NULL,
	//	NULL
	//);
	while ((r = recv(sock, responseBuffer, sizeof(responseBuffer), 0)) > 0) {
		//printf(responseBuffer);
		total += r;
		delta = total * 100 / size - progress;
		progress += delta;
		cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, delta);
		//if (offset == 0)
		//{
		//cellFsWrite(fd, responseBuffer, r, NULL);
		//char* z = remove_headers(responseBuffer);
		//cellFsWrite(fd, z, strlen(z), NULL);
		//}
		//else
		if (offset != 0)
			cellFsWrite(fd, responseBuffer, r, NULL);
		offset++;
	}
	
	cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 100 - progress);
	socketclose(sock);

	//cellMsgDialogClose(0);

	if (total == 0) {
		//printf("[DownloadFile] No data was received\n");
		return -1;
	}

	//printf("[DownloadFile] Done reading %d bytes\n", total);
	return 0;
}

#pragma endregion

#pragma region Obj
bool SecondFenceFlag;
int FloorCount, FloorStop;
float FenceBase = -3734.883f;
int FenceCount = 0;
int FenceStop = 0;
float FloorBase;

int Last_Object;
Vector3 TestAttach_Loc;
Vector3 TestAttach_Rot;
int Bone;
bool SecondFlag[14];

bool Create_Map_SelectedCoord(char* MapObjectName, float* ObjectFloat, float* CreatorCoord, bool CreatorTeleport)
{
	int ObjectID;
	Hash ObjectHash = GAMEPLAY::GET_HASH_KEY(MapObjectName);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(ObjectHash))
	{
		if (STREAMING::IS_MODEL_VALID(ObjectHash))
		{
			REQUEST_MODEL(ObjectHash);
			Vector3 coords;
			coords.x = ObjectFloat[0];
			coords.y = ObjectFloat[1];
			coords.z = ObjectFloat[2];
			if (STREAMING::HAS_MODEL_LOADED(ObjectHash))
			{
				ObjectID = OBJECT::CREATE_OBJECT(ObjectHash, coords.x, coords.y, coords.z, 1, 1, 1);
				if (ENTITY::DOES_ENTITY_EXIST(ObjectID))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ObjectID);
					ENTITY::FREEZE_ENTITY_POSITION(ObjectID, true);
					if (CreatorTeleport)
					{
						TP(PLAYER::PLAYER_PED_ID(), coords);

					}
					return true;
				}
				return false;
			}
			return false;
		}
	}
}

bool obj_spawn_flag;
bool Create_obj(Hash _hash, Vector3 Coords, bool collision, int* _spawned)
{
	Vector3 _Player = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(_hash))
	{
		if (!STREAMING::HAS_MODEL_LOADED(_hash))
			REQUEST_MODEL(_hash);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(*_spawned))
				*_spawned = OBJECT::CREATE_OBJECT(_hash, Coords.x, Coords.y, Coords.z - 1.0f, true, true, true);
			else
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(*_spawned);
				ENTITY::SET_ENTITY_COLLISION(*_spawned, collision, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_hash);
				return true;
			}
		}
	}
	else
	{
		addMessageShow("モデルの読み込みに失敗しました。");
	}

}
#pragma endregion

#pragma region Animation
void TASK_PLAY_ANIM(Ped Ped, char* AnimDict, char* Anim, int LoopUpper = 8, float Speed = 8)
{
	AI::TASK_PLAY_ANIM(Ped, AnimDict, Anim, Speed, Speed, -1, LoopUpper, Speed, 0, 0, 0);
}

void STOP_ANIM_TASK(Ped ped, char* AnimDict, char*Anim)
{
	AI::STOP_ANIM_TASK(ped, AnimDict, Anim, 2.0);
}
bool TASK_PLAY_ANIM_1(Ped Ped, char* AnimDict, char* Anim, int index = 8)
{
	AI::TASK_PLAY_ANIM(Ped, AnimDict, Anim, 1.0f, 0.0f, -1, index, 8, 0, 0, 0);
}
bool Set_PlayPedAnimCustom(int ped, char *AnimDict, char *AnimID, int speed = 8.0, int flag = 9, bool bDisableLegIK = false)
{
	PED::SET_PED_KEEP_TASK(ped, true);
	STREAMING::REQUEST_ANIM_DICT(AnimDict);
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
	{
		TASK_PLAY_ANIM(ped, AnimDict, AnimID, flag, flag);
		return true;
	}
}

#pragma endregion

#pragma region Buttons
enum AnalogStick
{
	INPUT_SCRIPT_LEFT_AXIS_X = 188,
	INPUT_SCRIPT_LEFT_AXIS_Y = 189,
	INPUT_SCRIPT_RIGHT_AXIS_X = 190,
	INPUT_SCRIPT_RIGHT_AXIS_Y = 191,
};
/*
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
*/
int Analog(int Value)
{
	return CONTROLS::GET_CONTROL_VALUE(0, Value);
}
bool isPress(int ButtonID, bool disabled = true)
{
	return disabled ? CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ButtonID) : CONTROLS::IS_CONTROL_PRESSED(0, ButtonID);
}

bool isPressed(int ButtonID, bool disabled = true)
{
	return disabled ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, ButtonID) : CONTROLS::IS_CONTROL_JUST_PRESSED(0, ButtonID);
}

bool isDpadPress()
{
	return (leftPress || rightPress || fastLeftPress || fastRightPress);
}

bool isDpadPress_2()
{
	return (isPress(Dpad_Left) || isPress(Dpad_Right) || isPressed(Dpad_Left) || isPressed(Dpad_Right));
}



void ButtonDisable(int ButtonID)
{
	CONTROLS::DISABLE_CONTROL_ACTION(0, ButtonID);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, ButtonID);
}
#pragma endregion

#pragma region セルフオプション
void NoCops(bool t)
{
	if (t) {
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		GAMEPLAY::CLEAR_AREA_OF_COPS(MyCoord.x, MyCoord.y, MyCoord.z, 100000, 0);
		PLAYER::SET_MAX_WANTED_LEVEL(0);
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	}
	else {
		PLAYER::SET_MAX_WANTED_LEVEL(5);
	}
}

void UltraPuncher(bool toggle)
{
	unsigned int Result = PS3::ReadUInt32((int)PS3::ReadUInt32(0x1CFB0A0) + 0x28) + 0xC;
	if (toggle)
	{
		for (int i = 0; i < 21; i++)
		{
			PS3::WriteFloat(Result + (i * 0x20), 10000000000);
			PS3::WriteFloat(Result + (i * 0x20) + 4, 10000000000);
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

void RevealPeople2(bool flag)
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

void OFF_Rader(bool flag)
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

void CopsturnBlindEye(bool t)
{
	if (t)
	{
		PS3::Write_Global(2410912 + 4141, 5);
		PS3::Write_Global(2410912 + 4144, 2147483647);
	}
	else
	{
		PS3::Write_Global(2410912 + 4141, 0);
	}
}

void NoClipSetup(bool toggle)
{
	if (toggle)
	{
		Noclip[1] = true;
	}
	else
	{
		Noclip[1] = false;
		int Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), ent = Vehicle == 0 ? PLAYER::PLAYER_PED_ID() : Vehicle; 
		ENTITY::SET_ENTITY_COLLISION(ent, true, 1);
		ENTITY::FREEZE_ENTITY_POSITION(ent, false);
	}
}
#pragma endregion

#pragma region 文字描画
void drawText(char *text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool Right = false, bool Outline = true, float plus = 0.0f)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_CENTRE(center);
	//UI::SET_TEXT_RIGHT_JUSTIFY(Right);
	if (Right)
	{
		UI::_0x68CDFA60(2);
		UI::SET_TEXT_WRAP(OOO, charText + plus);

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
	UI::_DRAW_TEXT(x, y);
}

void drawText2(char *text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool Right = false, bool Outline = true)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_CENTRE(center);
	//UI::SET_TEXT_RIGHT_JUSTIFY(Right);
	if (Right)
	{
		UI::_0x68CDFA60(2);
		UI::SET_TEXT_WRAP(0.0f, x);

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
	UI::_DRAW_TEXT(x, y);
}

void DrawSprite(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture));
			GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}
void set_text_component(char *text)
{
	GRAPHICS::_0x3AC9CB55("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_0x386CE0B8();
}
void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(mov, "CLEAR_ALL");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_0x716777CB(200);
	GRAPHICS::_0x02DBF2D7();
	instructCount = 0;
}
void addInstruction(int button, char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_0x215ABBE8(mov, "SET_DATA_SLOT");
	GRAPHICS::_0x716777CB(instructCount);
	GRAPHICS::_0x716777CB(button);
	set_text_component(text);
	GRAPHICS::_0x02DBF2D7();
	instructCount++;
}
void instructionsClose()
{
	GRAPHICS::_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(80);
	GRAPHICS::_0x02DBF2D7();
}

namespace DrawingMenus
{
	void normalMenuActions()
	{
#pragma region ボタン
		if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
		{
			if (instructions)
			{		
				
			}
		}

#pragma endregion

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

	}
}

bool newTimerTick = true, newTimerTick2 = true;
bool DdownTimerTick = true;
int maxTimerCount, maxTimerCount2;
int DdownTimerCount, DdownMaxTimerCount2;

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
	
	if (hasBeenUsed && !isPress(Dpad_Down) && !isPress(Dpad_Up))
		controlJustPressedTimeout = 0;
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


#pragma endregion

#pragma region NameChanger


namespace Load_NameChanger {
	int _fd;
	int index;
	char Loaded_String[16][20];
	char *locationToRead = "/dev_hdd0/tmp/Name_Changer.txt";

		char *replace(char *str, const char *what, const char *with)
		{
			if (!*what) { return str; }
			char *what_pos = strstr(str, what);
			if (!what_pos) { return str; }
			const size_t what_len = strlen(what), with_len = strlen(with);
			const char *remain = what_pos + what_len;
			memmove(what_pos + with_len, remain, strlen(remain) + 1);
			memcpy(what_pos, with, with_len);
			return str;
		}

	void do_LoadText(char *string) {
		//if (strlen(string) <= 16)
		//{
			if (index < 19)
			{
				strcpy(Loaded_String[index], string);
				//Loaded_String[index] = string;
				printf(Loaded_String[index]);
				index++;
			}
			else
				index = 0;
		//}
	}

	void Load_String()
	{
		uint64_t pos;
		uint64_t unk;
	
		int size = fileSize(locationToRead);
		//printf("Got a FileSize! : %ibyte\n", size);
		char ReadBuffer[size];
		if (cellFsOpen(locationToRead, CELL_FS_O_RDWR | CELL_FS_O_CREAT , &_fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;
	//	else
			//printf("Read a file\n");

		cellFsLseek(_fd, 0, CELL_FS_SEEK_SET, &pos);
		if (cellFsRead(_fd, ReadBuffer, size, &unk) != CELL_FS_SUCCEEDED)
			return;

		//cellFsClose(_fd);

		int LineNumber;
		char LoadedLine[100];
		char buf[100];
		strcpy(LoadedLine, "");
		int index;

		printf("LoopStart\n");

		for (int i = 0; i < size; i++)
		{
			char *TestString = "";
			if (ReadBuffer[i] == '\r' && ReadBuffer[i + 1] == '\n')
			{
				strcpy(buf, LoadedLine);
				replace(buf, "\n", "");
				//TestString = buf;
				do_LoadText(buf);
				PS3::WriteByte(0x10054320, '\0');
				strcpy(LoadedLine, "");
				printf(buf);
				i += 1;
			}
			else
			{
				PS3::WriteByte(0x10054320, ReadBuffer[i]);
				strcat(LoadedLine, PS3::ReadString_1(0x10054320));
				PS3::WriteByte(0x10054320, '\0');
			}
			printf("loop : %i\n", i);
		}
	}
}

void do_NameChange(char* name)
{
	PS3::WriteString(0x41143344, name);
	PS3::WriteString(0x1FF248C, name);
	PS3::WriteString(0x200255C, name);


	int size = fileSize("/dev_hdd0/tmp/Name_Changer.txt");
	//char _buf[size + 20];
	//char _2uf[size];
	//char _3uf[size];

	//int fd;
	//if (cellFsOpen("/dev_hdd0/tmp/Name_Changer.txt", CELL_FS_O_WRONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
	//	return;
	//else
	//	printf("Loaded\n");

	///cellFsRead(fd, _2uf, size, NULL);
	//strcpy(_3uf, _2uf);
	//strcat(_3uf, "\0");
	//snprintf(_buf, size + 20, "%s\n%s%c", _3uf, name, '\0');
	//snprintf(_buf, sizeof(_buf), "%s\n%s", name);

	cellFsWrite(Load_NameChanger::_fd, name, strlen(name), NULL);
	cellFsWrite(Load_NameChanger::_fd, "\n", strlen("\n"), NULL);
	//cellFsClose(fd);

	strcpy(Load_NameChanger::Loaded_String[Load_NameChanger::index], name);
	//Loaded_String[index] = string;
	printf(Load_NameChanger::Loaded_String[Load_NameChanger::index]);
	Load_NameChanger::index++;
	//strcpy(_buf, "\0");
	//strcpy(_2uf, "\0");
}

void do_ClanTagChange(char *Clan)
{
	PS3::WriteString(0x205C27F, Clan);
	PS3::WriteString(0x205C337, Clan);
	PS3::WriteString(0x205C3EF, Clan);
	PS3::WriteString(0x205C4A7, Clan);
	PS3::WriteString(0x205C55F, Clan);
}
#pragma endregion

#pragma region Detection
int _0x139B5CC() {
	return 0;
}



int write_process2(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	return_to_user_prog(int);
}


unsigned int Paradise_NewFreezePRO(unsigned int r3, unsigned int r4)
{
	addMessageShow("ParadiseSPRXからのフリーズを検知しました。");
	*(int*)0x1755794 = 0x4bfffc91;
	//4b ff fc 91
}
char scriptEventDialogText[100];
unsigned int scriptEventDetour(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9)
{

	int addressOfArgs = r3 + 10 * 0x4;
	char *senderName = (char*)(*(int*)(senderData + 0x78) + 0x10);
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x35)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が貴方をキックしました。", senderName);
		addMessageShow(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x10 && *(int*)(addressOfArgs + 0x8) == 0x4)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が貴方をフリーズさせました。", senderName);
		addMessageShow(scriptEventDialogText);
		branch_link(*(int*)((int)&Paradise_NewFreezePRO), 0x1755794);
		//drawNotification(scriptEventDialogText);
		//EVENTMes(senderName, 8);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x34)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が貴方を偽装キックしました。", senderName);
		addMessageShow(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x2 && *(int*)(addressOfArgs + 0x8) == 0x2e)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が貴方を偽装キック[リセット]しました。", senderName);
		addMessageShow(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0xD8)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が%iRP与えています。", senderName, *(int*)(addressOfArgs + 0x8));
		addMessageShow(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x16C)
	{
		snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sがアパート招待しました。", senderName);
		addMessageShow(scriptEventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x3)
	{
		if (*(int*)(addressOfArgs + 0x8) == 0x37 || *(int*)(addressOfArgs + 0x8) == 0x36 || *(int*)(addressOfArgs + 0x8) == 0x35)
		{
			snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sがゲーム招待してます。", senderName);
			addMessageShow(scriptEventDialogText);
			*(int*)addressOfArgs = 0;
		}
	}
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	_0x12C8CC0(r3, senderData, recieverData, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s weather_1t = { 0x12C2D8C, 0x1C85330 };
unsigned int(*weather_1)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&weather_1t;
unsigned int WeatherEventProtection(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sが天候変更しました", senderName);
	//PS3::WriteUInt32(0xA0284C, 0x60000000);
	//addMessageShow(scriptEventDialogText);
	weather_1(r3, r4, r5, r6, r7, r8);
	//return weather_1(r3, r4, r5, r6, r7, r8);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s give_pickup_reward_t = { 0x12D2064, 0x1C85330 };
unsigned int(*give_pickup_)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&give_pickup_reward_t;
unsigned int Givepickuprewardprotection(int r3, int r4, int r5, int r6, int r7, int r8)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sがメモリ変更しました", senderName);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	addMessageShow(scriptEventDialogText);
	return give_pickup_(r3, r4, r5, r6, r7, r8);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}


OPD_s Anim_1t = { 0x12CB4BC, 0x1C85330 };
unsigned int(*anim_1)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&Anim_1t;
unsigned int AnimproProtection(int r3, int r4, int r5, int r6, int r7, int r8)
{
	//char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);

	//char *recieverName = (char*)(*(int*)(r5 + 0x78) + 0x10);
	//snprintf___(scriptEventDialogText, 100, "%sが強制アニメーションを使用しました。", senderName);
	//printf("r4 = 0x%X | r5 = 0x%X | Me = 0x%X", r4, r5, NETWORK_HANDLE_FROM_PLAYER1(PLAYER::PLAYER_ID()));
	//addMessageShow(scriptEventDialogText);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	anim_1(r3, r4, r5, r6, r7, r8);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s STATEVENTt = { 0x12D12DC,0x1C85330 };
unsigned int(*STATEVENT)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&STATEVENTt;
unsigned int NETWORKINCREMENTSTATEVENT(int r3, int r4, int r5, int r6, int r7, int r8)
{
	int addressOfArgs = r3 + 0x24;
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	int senderIndex = *(int*)((*(int*)r4) + 0x98);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sが[~b~0x%X~w~]を[~b~0x%X~w~]にしようとしています。", senderName, *(int*)addressOfArgs, *(int*)(addressOfArgs + 0x4));
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	addMessageShow(scriptEventDialogText);
	STATEVENT(r3, r4, r5, r6, r7, r8);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s ClearTaskt = { NETWORK_CLEAR_PED_TASKS_EVENT , 0x1C85330 };
unsigned int(*NETWORK_CLEAR_PED_TASKS_EVENT_FUNC)(unsigned int r3, unsigned int senderData, unsigned int receiverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&ClearTaskt;
unsigned int _NETWORK_CLEAR_PED_TASKS_EVENT(unsigned int r3, unsigned int senderData, unsigned int receiverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9)
{
	char *NameOfSender = (char*)(*(int*)(senderData + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sがアニメーションをリセットしようとしています。", NameOfSender);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	//addMessageShow(scriptEventDialogText);
	NETWORK_CLEAR_PED_TASKS_EVENT_FUNC(r3, senderData, receiverData, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
	
}

OPD_s ClockTimet = { GAME_CLOCK_EVENT, 0x1C85330 };
unsigned int(*GAME_CLOCK_EVENT_FUNC)(unsigned int r3, unsigned int senderData, unsigned int receiverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&ClockTimet;
unsigned int _GAME_CLOCK_EVENT(unsigned int r3, unsigned int senderData, unsigned int receiverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9)
{
	char *NameOfSender = (char*)(*(int*)(senderData + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%s時間を変更しようとしています。", NameOfSender);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	//addMessageShow(scriptEventDialogText);
	GAME_CLOCK_EVENT_FUNC(r3, senderData, receiverData, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

int returnKicked()
{
	//char hostKickDetection[50];
	//char *senderName = (char*)((*(int*)0x1CF72C4) + 0x10);
	//int senderIP = *(int*)((*(int*)0x1CF72C4) + 0x12D40);
	//int senderPort = *(int*)((*(int*)0x1CF72C4) + 0x12D44);
//	snprintf(hostKickDetection, sizeof(hostKickDetection), "[~r~%s]からの切断を感知しました。", senderName);
	//addMessageShow(hostKickDetection);
	return 0;
}

unsigned int sub_173226C_S(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9, unsigned int a10)
{
	//int addressOfArgs = a1 + 10 * 0x4;
	
	//int r3 = a1;
	//int addressOfArgs = r3 + 10 * 0x4;
	//int r4 = a2;
	//int addressOfArgs2 = r4 + 10 * 0x4;
	//int rZ = a9;
	//int addressOfArgs3 = rZ + 10 * 0x4;
	//printf("r3->0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n", (int)(addressOfArgs + 0x4 * 0), (int)(addressOfArgs + 0x4 * 1), (int)(addressOfArgs + 0x4 * 2), (int)(addressOfArgs + 0x4 * 3), (int)(addressOfArgs + 0x4 * 4), (int)(addressOfArgs + 0x4 * 5), (int)(addressOfArgs + 0x4 * 6), (int)(addressOfArgs + 0x4 * 7), (int)(addressOfArgs + 0x4 * 8), (int)(addressOfArgs + 0x4 * 9), (int)(addressOfArgs + 0x4 * 10));
	//printf("r4->0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n", (int)(addressOfArgs2 + 0x4 * 0), (int)(addressOfArgs2 + 0x4 * 1), (int)(addressOfArgs2 + 0x4 * 2), (int)(addressOfArgs2 + 0x4 * 3), (int)(addressOfArgs2 + 0x4 * 4), (int)(addressOfArgs2 + 0x4 * 5), (int)(addressOfArgs2 + 0x4 * 6), (int)(addressOfArgs2 + 0x4 * 7), (int)(addressOfArgs2 + 0x4 * 8), (int)(addressOfArgs2 + 0x4 * 9), (int)(addressOfArgs2 + 0x4 * 10));
	//printf("rZ->0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n", (int)(addressOfArgs3 + 0x4 * 0), (int)(addressOfArgs3 + 0x4 * 1), (int)(addressOfArgs3 + 0x4 * 2), (int)(addressOfArgs3 + 0x4 * 3), (int)(addressOfArgs3 + 0x4 * 4), (int)(addressOfArgs3 + 0x4 * 5), (int)(addressOfArgs3 + 0x4 * 6), (int)(addressOfArgs3 + 0x4 * 7), (int)(addressOfArgs3 + 0x4 * 8), (int)(addressOfArgs3 + 0x4 * 9), (int)(addressOfArgs3 + 0x4 * 10));
	//printf("a1 : 0x%X\n", a1);
	//printf("a2 : 0x%X\n", a2);
	//printf("a3 : 0x%X\n", a3);
	//printf("a4 : 0x%X\n", a4);
	//printf("a5 : 0x%X\n", a5);
	//printf("a6 : 0x%X\n", a6);
	//printf("a7 : 0x%X\n", a7);
	//printf("a8 : 0x%X\n", a8);
	//printf("a9 : 0x%X\n", a9);
	//printf("a10 : 0x%X\n", a10);
	char *senderName = (char*)(*(int*)(a3 + 0x78) + 0x10);
	snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "~r~%s~w~が~b~メモリ操作~w~を実行しました。", senderName);
	addMessageShow(scriptEventDialogText);

	//drawNotification(scriptEventDialogText);
}
//1C6C608 
//12D2154

OPD_s SyncData_t = { 0x12D2154, 0x1C85330 };
unsigned int(*SyncFata_event)(unsigned int r3, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&SyncData_t;
unsigned int SyncData_EventHook(unsigned int r3, unsigned int r4, uint r5, uint r6, uint r7, uint r8)
{
	printf("0x%X\n", r3);
	printf("0x%X\n", r4);
	printf("0x%X\n", r5);
	printf("0x%X\n", r6);
	printf("0x%X\n", r7);
	printf("0x%X\n", r8);
	int addressOfArgs = r3;
	printf("r3->0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n 0x%X\n", (int)(addressOfArgs + 0x4 * 0), (int)(addressOfArgs + 0x4 * 1), (int)(addressOfArgs + 0x4 * 2), (int)(addressOfArgs + 0x4 * 3), (int)(addressOfArgs + 0x4 * 4), (int)(addressOfArgs + 0x4 * 5), (int)(addressOfArgs + 0x4 * 6), (int)(addressOfArgs + 0x4 * 7), (int)(addressOfArgs + 0x4 * 8), (int)(addressOfArgs + 0x4 * 9), (int)(addressOfArgs + 0x4 * 10));

	SyncFata_event(r3, r4);
}


OPD_s Parserz = { 0x133C480, 0x1C85330 };
unsigned int(*NETWORK_ENTITIES_EVENT_FUNC)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10, unsigned int r11, unsigned int r12, unsigned int r13, unsigned int r14, unsigned int r15, unsigned int r16, unsigned int r17, unsigned int r18, unsigned int r19, unsigned int r20, unsigned int r21) = 
(unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&Parserz;
OPD_s Parser2 = { 0x132B258, 0x1C85330 };
char*(*MEM_GET_ENTITY_TYPE)(unsigned int r3, bool r4) = (char*(*)(unsigned int, bool))&Parser2;

char EventDialogText[200];
unsigned int _NETWORK_ENTITIES_EVENT(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10, unsigned int r11, unsigned int r12, unsigned int r13, unsigned int r14, unsigned int r15, unsigned int r16, unsigned int r17, unsigned int r18, unsigned int r19, unsigned int r20, unsigned int r21)
{
	char *NameOfSender = (char*)(*(int*)(r4 + 0x78) + 0x10);
	int addressOfArgs = r9 + 0x20;
	bool unkBool = r9 & 4 || r9 & 0x20;
	char *entityType = MEM_GET_ENTITY_TYPE(r6, unkBool);
	//_sys_sprintf("PSID: %s   |   アドレス: 0x%X   |   タイプ: %s  |  アドレス 0x%X  アドレスv2  0x%X", NameOfSender, *(int*)addressOfArgs, entityType,ENTITY::GET_ENTITY_MODEL(*(int*)addressOfArgs), GetEntityAddress(ENTITY::GET_ENTITY_MODEL(*(int*)addressOfArgs)));
	//if (entityType == "PLAYER") {} //if detect is a player, not show anything
	if (strstr(entityType, "HELI") || strstr(entityType, "SCRIPT_HELI"))
	{
		if (*(int*)addressOfArgs == 0x3E48BF23 || *(int*)addressOfArgs == 0xF7004C86 || *(int*)addressOfArgs == 0x31F0B376 || *(int*)addressOfArgs == 0x2F03547B || *(int*)addressOfArgs == 0x9D0450CA || *(int*)addressOfArgs == 0x2C75F0DD || *(int*)addressOfArgs == 0x2C634FBD || *(int*)addressOfArgs == 0x742E9AC0 || *(int*)addressOfArgs == 0xFCFCB68B || *(int*)addressOfArgs == 0x60A7EA10 || *(int*)addressOfArgs == 0x53174EEF || *(int*)addressOfArgs == 0x1517D4D9 || *(int*)addressOfArgs == 0xEBC24DF2 || *(int*)addressOfArgs == 0x4019CB4C || *(int*)addressOfArgs == 0xA09E15FD || *(int*)addressOfArgs == 0xFB133A17)
		{

		}
		else
		{
			snprintf(EventDialogText, sizeof(EventDialogText), "%sがフリーズコンソールを実行しました。", NameOfSender);
			addMessageShow(EventDialogText);
			*(int*)addressOfArgs = 0x3E48BF23;
		}
	}
	if (strstr(entityType, "PLANE") || strstr(entityType, "SCRIPT_PLANE"))
	{
		if (*(int*)addressOfArgs == 0x15F27762 || *(int*)addressOfArgs == 0x39D6E83F || *(int*)addressOfArgs == 0x6CBD1D6D || *(int*)addressOfArgs == 0x3F119114 || *(int*)addressOfArgs == 0xB39B0AE6 || *(int*)addressOfArgs == 0xD9927FE3 || *(int*)addressOfArgs == 0xD9927FE3 || *(int*)addressOfArgs == 0x81794C70 || *(int*)addressOfArgs == 0x39D6779E || *(int*)addressOfArgs == 0x97E55D11 || *(int*)addressOfArgs == 0x403820E8 || *(int*)addressOfArgs == 0x9C429B6A || *(int*)addressOfArgs == 0x9D80F93 || *(int*)addressOfArgs == 0x4FF77E37 || *(int*)addressOfArgs == 0xB79C1BF5 || *(int*)addressOfArgs == 0xB79F589E || *(int*)addressOfArgs == 0x250B0C5E || *(int*)addressOfArgs == 0x761E2AD3)
		{

		}
		else
		{
			snprintf(EventDialogText, sizeof(EventDialogText), "%sがフリーズコンソールを実行しました。", NameOfSender);
			addMessageShow(EventDialogText);
			*(int*)addressOfArgs = 0x15F27762;
		}
	}
	if (strstr(entityType, "OBJECT") || strstr(entityType, "SCRIPT_OBJECT"))
	{

		//_sys_printf("PSID: %s   |   アドレス: 0x%X   |   タイプ: %s  |  アドレス 0x%X  アドレスv2  0x%X アドレス v3 0x%X アドレス v4 0x%X", NameOfSender, *(int*)addressOfArgs, entityType, ENTITY::GET_ENTITY_MODEL(*(int*)addressOfArgs), GetEntityAddress(*(int*)addressOfArgs), ENTITY::GET_ENTITY_MODEL(GetEntityAddress(*(int*)addressOfArgs)), GetEntityAddress(ENTITY::GET_ENTITY_MODEL(*(int*)addressOfArgs)));
		if (*(int*)addressOfArgs == 0x267751FA)
		{
			snprintf(EventDialogText, sizeof(EventDialogText), "%sがフリーズコンソールを実行しました。", NameOfSender);
			addMessageShow(EventDialogText);
			*(int*)addressOfArgs = 0;
		}
	}
	return NETWORK_ENTITIES_EVENT_FUNC(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
}

unsigned int __NETWORK_ENTITIES_EVENT(unsigned int r3, unsigned int l_uiSenderData, unsigned int r5, unsigned int l_uiEntityTypeId, unsigned int r7, unsigned int r8, unsigned int l_uiDataOfArgs, unsigned int r10, unsigned int r11, unsigned int r12, unsigned int r13, unsigned int r14, unsigned int r15, unsigned int r16, unsigned int r17, unsigned int r18, unsigned int r19, unsigned int r20, unsigned int r21)
{
	char *NameOfSender = (char*)(*(int*)(l_uiSenderData + 0x78) + 0x10);
	int addressOfArgs = l_uiDataOfArgs + 0x20; //hash can be +0x29
	//printf("Name: %s    Address: 0x%X\n", NameOfSender, l_uiEntityTypeId);
	char *entityType = MEM_GET_ENTITY_TYPE(l_uiEntityTypeId, true);
	//printf("\tRECEIVED_CLONE_CREATE\t%s_%d\r\n", entityType, r7);

	if (*(int*)addressOfArgs == 0x1DC17987 || *(int*)addressOfArgs == 0x1E727BFF)
	{
		snprintf(EventDialogText, sizeof(EventDialogText), "%sがクローンを生成しました。", NameOfSender);
		addMessageShow(EventDialogText);
		*(int*)addressOfArgs = 0;
	}
	if (*(int*)addressOfArgs == 0x1C71420 || *(int*)addressOfArgs == 0x1C7129C || *(int*)addressOfArgs == 0x1C71424 || *(int*)addressOfArgs == 0x1C71298 ||
		*(int*)addressOfArgs == 0x1CFC0E72/*slod_human*/ || *(int*)addressOfArgs == 0x1E15B3EC/*slod_large_quadped*/ || *(int*)addressOfArgs == 0x1CB5C0C3/*slod_small_quadped*/ ||
		*(int*)addressOfArgs == 0x267751FA || *(int*)addressOfArgs == 0x212C95AE || *(int*)addressOfArgs == 0x24E790F0 || *(int*)addressOfArgs == 0x260E708C || *(int*)addressOfArgs == 0x266C9D3E ||
		*(int*)addressOfArgs == 0x1D96E4C1 || *(int*)addressOfArgs == 0x1FBF96BF || *(int*)addressOfArgs == 0x1EF6ED24 || *(int*)addressOfArgs == 0x1D87531D || *(int*)addressOfArgs == 0x1EB4D03D || *(int*)addressOfArgs == 0x1EF401AB || *(int*)addressOfArgs == 0x1DE25B6A || *(int*)addressOfArgs == 0x1C91ABC8 || *(int*)addressOfArgs == 0x1FAD4765 || *(int*)addressOfArgs == 0x1EA1A0DC || *(int*)addressOfArgs == 0x1C53B05F || *(int*)addressOfArgs == 0x1C49435E || *(int*)addressOfArgs == 0x1E558C88 ||
		*(int*)addressOfArgs == 0x15F27762 || *(int*)addressOfArgs == 0x761E2AD3 || *(int*)addressOfArgs == 0x3F119114 || *(int*)addressOfArgs == 0x9D80F93)
	{
		snprintf(EventDialogText, sizeof(EventDialogText), "%sがフリーズコンソールを実行しました。", NameOfSender);
		addMessageShow(EventDialogText);
		*(int*)addressOfArgs = 0;
	}

	return NETWORK_ENTITIES_EVENT_FUNC(r3, l_uiSenderData, r5, l_uiEntityTypeId, r7, r8, l_uiDataOfArgs, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
}


unsigned int(*DROP_KICK_EVENT_FUNC)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10, unsigned int r11, unsigned int r12, unsigned int r13) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&RTA(0x9FB888);
uint _DROP_KICK_EVENT(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, unsigned int r10, unsigned int r11, unsigned int r12, unsigned int r13)
{
	int32_t v1 = (int32_t)r3;
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	if (r6 != 132 && r6 != 140 && r6 != 144 && r6 != 142 && r6 != 143 && r6 != 138)
	{
		//sprintf(scriptEventDialogText, "%sがドロップキックしました。", senderName);
		//addMessageShow(scriptEventDialogText);
	}

	*(int32_t *)(v1 + 12) = 0;
	*(int32_t *)(v1 + 16) = 0;
	*(int32_t *)(v1 + 20) = 0;
	return DROP_KICK_EVENT_FUNC(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13);
}

OPD_s KICKVOTESEVENTzt = { 0x12D1D88,0x1C85330 };
unsigned int(*KICKVOTESEVENTz)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, uint r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, uint))&KICKVOTESEVENTzt;
unsigned int KICKVOTESEVENT(int r3, int r4, int r5, int r6, int r7, int r8, int r9)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sが投票しました。", senderName);
	//addMessageShow(scriptEventDialogText);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	return KICKVOTESEVENTz(r3, r4, r5, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s request_control_event_t = { REQUEST_CONTROL_EVENT, 0x1C85330 };
unsigned int(*request_control)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&request_control_event_t;
unsigned int request_control_events(int r3, int r4, int r5, int r6, int r7, int r8, int r9)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sが投票しました。", senderName);
	//addMessageShow(scriptEventDialogText);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	request_control(r3, r4, r5, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

OPD_s give_control_event_t = { GIVE_CONTROL_EVENT, 0x1C85330 };
unsigned int(*give_control)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&give_control_event_t;
unsigned int give_control_events(int r3, int r4, int r5, int r6, int r7, int r8, int r9)
{
	char *senderName = (char*)(*(int*)(r4 + 0x78) + 0x10);
	//snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sが投票しました。", senderName);
	//addMessageShow(scriptEventDialogText);
	PS3::WriteUInt32(0xA0284C, 0x60000000);
	give_control(r3, r4, r5, r6, r7, r8, r9);
	PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}

int32_t dropKickDetection(int32_t a1, int32_t a2, int32_t * a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10)
{
	int32_t v1 = (int32_t)a3;
	int v2 = *(int*)((*(int*)a2) + 0x98);
	char *v3 = (char*)((*(int*)a2) + 0x10);
	if (a4 != 132)
	{
		if (a4 != 140)
		{
			if (a4 != 144)
			{
				if (a4 != 142)
				{
					if (a4 != 143)
					{
						if (a4 != 138)
						{
							//sprintf(MsgProtection, "%sがドロップキックしました。");
							//addMessageShow(MsgProtection);
						}
					}
				}
			}
		}
	}
	*(int32_t *)(v1 + 12) = 0;
	*(int32_t *)(v1 + 16) = 0;
	*(int32_t *)(v1 + 20) = 0;
	return 1;
}

struct structDetectMenus {
	bool isModder;
	char *menuDetected;
	int r3;
};

OPD_s EBOOT_t = { 0x12D4A5C, 0x1C85330 };
unsigned int(*CHECK_EBOOT_SIZE_FUNC)(unsigned int r3, unsigned int r4, unsigned int r5) = 
(unsigned int(*)(unsigned int, unsigned int, unsigned int))&EBOOT_t;

structDetectMenus detectedMenus[16];
bool MenuDetected[16];
//int r3_1[16];
//int r4_1[16];
//int r5_1[16];
//int SIZE_1[16];
unsigned int CHECK_EBOOT_SIZE(unsigned int r3, unsigned int r4, unsigned int r5) {
	int32_t sizeID = *(int32_t *)(r3 + 0x24);
	int32_t idOfPlayer = *(int32_t *)(r4 + 0x98);
	//r3_1[idOfPlayer] = r3;
	//r4_1[idOfPlayer] = r4;
	//r5_1[idOfPlayer] = r5;
	//SIZE_1[idOfPlayer] = sizeID;

	switch (sizeID)
	{
	case 0x1CFCCAC: 
		MenuDetected[idOfPlayer] = true;
		break;

	case 0x1CFCCEC:
		MenuDetected[idOfPlayer] = true;
		break;

	case 0xEB3970:
		MenuDetected[idOfPlayer] = false;
		break;
	/*;
	case 0xEB3970:
		MenuDetected[idOfPlayer] = false;
		break;

*/
	case 0x0:
		MenuDetected[idOfPlayer] = false;
		break;
		
	default:
		MenuDetected[idOfPlayer] = true;

		break;
	}
}

OPD_s model_changer_t = { 0x136BF54, 0x1C85330 };
unsigned int(*MODEL_CHANGER_EVENT_FUNC)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7) =
(unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&model_changer_t;
unsigned int _MODEL_CHANGER_EVENT(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7)
{
	char *NameOfSender = (char*)(*(int*)(r4 + 0x78) + 0x10);
	int addressOfArgs = r3 + 0x254;
	//if freeze i think need check if is model and if the model is valid
	if (*(int*)addressOfArgs != 0x705E61F2 || *(int*)addressOfArgs != 0x9C9EFFD8)
	{
		if (NameOfSender != "")
		{
			PS3::WriteUInt32(0xA0284C, 0x60000000);
			snprintf(scriptEventDialogText, sizeof(scriptEventDialogText), "%sがモデルチェンジしました。", NameOfSender);
			addMessageShow(scriptEventDialogText);
			//*(int*)addressOfArgs = 0x705E61F2;
		}
		//*(int*)addressOfArgs = 0x705E61F2;
	}
	return MODEL_CHANGER_EVENT_FUNC(r3, r4, r5, r6, r7);
	//PS3::WriteUInt32(0xA0284C, 0x4E9E0421);
}



#pragma endregion

#pragma region Fun Menu
void drawLine(Vector3 p1, Vector3 p2) {
	GRAPHICS::DRAW_LINE(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, 255, 0, 0, 255);
}
#pragma endregion

#pragma region Misc
void ninjaMode(bool ninja) {
	//block networking locations, spoof your location, so modder cant get your location
	if (ninja)
	{
		PS3::WriteUInt32(0xA01D64, 0x4E800020);
		PS3::WriteUInt32(0x11178D8, 0x4E800020);
	}
	else
	{
		PS3::WriteUInt32(0xA01D64, 0x7C0802A6);
		PS3::WriteUInt32(0x11178D8, 0x7C0802A6);
	}
}

void WaterOpacityEdit(int opacity = 0x02020202)
{
	int WaterQuad = PS3::ReadInt32(0x21C8C48);
	for (int i = 0; i < 0x332; i++)
	{
		PS3::WriteUInt32(WaterQuad + (i * 0x1C) + 0x08, opacity);
	}
}
#pragma endregion

#pragma region Vehspawn
char *_RetCarClass(int index)
{
	char buffer[128];
	snprintf(buffer, 128, "VEH_CLASS_%i", index);
	return UI::_GET_LABEL_TEXT(buffer);
}

void MaxUp(int handle)
{
	VEHICLE::SET_VEHICLE_FIXED(handle);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(handle);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(handle, 0);
	VEHICLE::SET_VEHICLE_MOD_KIT(handle, 0);
	VEHICLE::SET_VEHICLE_MOD(handle, 0, 1, 0);//Soiler
	VEHICLE::SET_VEHICLE_MOD(handle, 1, 1, 0);//Frontstoﾟstange
	VEHICLE::SET_VEHICLE_MOD(handle, 2, 1, 0);//Heckstoﾟstange
	VEHICLE::SET_VEHICLE_MOD(handle, 3, 1, 0);//Body
	VEHICLE::SET_VEHICLE_MOD(handle, 4, 2, 0);//Auspuff
	VEHICLE::SET_VEHICLE_MOD(handle, 5, 1, 0);//Ueberrollkaeffig
	VEHICLE::SET_VEHICLE_MOD(handle, 6, 1, 0);//Grill
	VEHICLE::SET_VEHICLE_MOD(handle, 7, 1, 0);//Motorhaube
	VEHICLE::SET_VEHICLE_MOD(handle, 8, 2, 0);//Schhuerze
	VEHICLE::SET_VEHICLE_MOD(handle, 9, 2, 0);//Rechte Schuerze
	VEHICLE::SET_VEHICLE_MOD(handle, 10, 1, 0);//Dach
	VEHICLE::SET_VEHICLE_MOD(handle, 11, 3, 0);//Motor9
	VEHICLE::SET_VEHICLE_MOD(handle, 12, 2, 0);//Bremsen
	VEHICLE::SET_VEHICLE_MOD(handle, 13, 2, 0);//Getriebe
	VEHICLE::SET_VEHICLE_MOD(handle, 14, 24, 0);//Hupe
	VEHICLE::SET_VEHICLE_MOD(handle, 15, 2, 0);//Federung
	VEHICLE::SET_VEHICLE_MOD(handle, 16, 4, 0);//Panzerung
	VEHICLE::TOGGLE_VEHICLE_MOD(handle, 18, 1);//Turbo
	VEHICLE::TOGGLE_VEHICLE_MOD(handle, 22, 1);//Xenon 
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(handle, 7);//Reifen Typ
	VEHICLE::SET_VEHICLE_MOD(handle, 23, 18, 0);//Reifen
	VEHICLE::SET_VEHICLE_WINDOW_TINT(handle, 5);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(handle, "Hyper Dx");
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(handle, 3);
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(handle, false);
	VEHICLE::TOGGLE_VEHICLE_MOD(handle, 20, 1);
	VEHICLE::SET_VEHICLE_MOD_KIT(handle, 0);
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(handle, 0, 0, 0);
}

void Collision(Entity entity, bool state)
{
	ENTITY::SET_ENTITY_COLLISION(entity, state, 0);
}

bool Create_Vehicle(Hash _Hash)
{
	REQUEST_MODEL(_Hash);
	if (STREAMING::HAS_MODEL_LOADED(_Hash))
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int SpawnVehBuf = VEHICLE::CREATE_VEHICLE(_Hash, MyCoord.x, MyCoord.y, MyCoord.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + (TeleAutomIncar ? 0 : 90), 1, 0);
		if (ENTITY::DOES_ENTITY_EXIST(SpawnVehBuf))
		{
			Entity veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			float Speed = ENTITY::GET_ENTITY_SPEED(veh);

			Vector3 CoordsFront;
			if (TeleAutomIncar)
				CoordsFront = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			else
				CoordsFront = CAM2::GET_COORDS_INFRONT(6);
			
			ENTITY::SET_ENTITY_COORDS(SpawnVehBuf, CoordsFront.x, CoordsFront.y, CoordsFront.z, 0, 0, 90, 0);
			if (!TeleAutomIncar)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(SpawnVehBuf, 0, 0, false);


			if (TeleAutomIncar)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), SpawnVehBuf, -1);
				VEHICLE::SET_VEHICLE_ENGINE_ON(SpawnVehBuf, true, true);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(SpawnVehBuf, Speed);
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
				{
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(SpawnVehBuf, Speed);
				}
			}

			if (VehicleSpawnBool[0])
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(SpawnVehBuf, VehicleColor.R, VehicleColor.G, VehicleColor.B);
			if (VehicleSpawnBool[1])
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(SpawnVehBuf, VehicleColor.R, VehicleColor.G, VehicleColor.B);
			if (VehicleSpawnBool[2])
			{
				VEHICLE::TOGGLE_VEHICLE_MOD(SpawnVehBuf, 20, 1);
				VEHICLE::SET_VEHICLE_MOD_KIT(SpawnVehBuf, 0);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(SpawnVehBuf, VehicleColor.R, VehicleColor.G, VehicleColor.B);
			}
			if (VehicleSpawnBool[3])
			{
				VEHICLE::SET_VEHICLE_COLOURS(SpawnVehBuf, 120, 120);
			}

			if (MaxUpgrades)
				MaxUp(SpawnVehBuf);

			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(SpawnVehBuf, "ReDX");
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(SpawnVehBuf, 3);

			SpawnedEntityList[spawnedindex__] = SpawnVehBuf;
			SpawnedEntityName[spawnedindex__] = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(SpawnVehBuf));
			SpawnedEntityNames[spawnedindex__] = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(SpawnVehBuf));
			if (spawnedindex__ >= 40)
				spawnedindex__ = 0;
			else
				spawnedindex__++;

			addMessageShow("スポーンしました。");
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_Hash);
			return true;
		}
	}
}

int PedSpawnMethod_int(char* pedname)
{
	int PedID;
	Hash Unko = GAMEPLAY::GET_HASH_KEY(pedname);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(Unko))
	{
		if (STREAMING::IS_MODEL_VALID(Unko))
		{
			REQUEST_MODEL(Unko);
			if (STREAMING::HAS_MODEL_LOADED(Unko))
			{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				PedID = PED::CREATE_PED(21, Unko, coords.x, coords.y, coords.z, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(PedID))
				{
					return PedID;
				}
			}
		}
	}
}
#pragma endregion

#pragma region Recovery

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
		switch (CharacterVar_)
		{
		case 0:
			CharacterSet = "MP0_";
			break;
		case 1:
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
		switch (CharacterVar_)
		{
		case 0:
			CharacterSet = "MP0_";
			break;
		case 1:
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
		switch (CharacterVar_)
		{
		case 0:
			CharacterSet = "MP0_";
			break;
		case 1:
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
	STAT_SET_INT("CHEAT_BITSET", 0, 1);
	STAT_SET_INT("BAD_SPORT_BITSET", 0, 1);
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
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED"), 0, 1);


}
#pragma endregion

#pragma region RemoteRecovery

enum kickType { _normalKick = 0x00, _connectionLost = 0x01, _fakeKick = 0x02, _adminKick = 0x04 };
void setCustomKickType(kickType r3) {
	*(unsigned int*)(0x3E4167) = r3;
}
int Ranks[] = { 0, 800, 2100, 3800, 6100, 9500, 12500, 16000, 19800, 24000, 28500, 33400, 38700, 44200, 50200, 56400, 63000, 69900, 77100, 84700, 92500, 100700, 109200, 118000, 127100, 136500, 146200, 156200, 166500, 177100, 188000, 199200, 210700, 222400, 234500, 246800, 259400, 272300, 285500, 299000, 312700, 326800, 341000, 355600, 370500, 385600, 401000, 416600, 432600, 448800, 465200, 482000, 499000, 516300, 533800, 551600, 569600, 588000, 606500, 625400, 644500, 663800, 683400, 703300, 723400, 743800, 764500, 785400, 806500, 827900, 849600, 871500, 893600, 916000, 938700, 961600, 984700, 1008100, 1031800, 1055700, 1079800, 1104200, 1128800, 1153700, 1178800, 1204200, 1229800, 1255600, 1281700, 1308100, 1334600, 1361400, 1388500, 1415800, 1443300, 1471100, 1499100, 1527300, 1555800, 1584350, 1612950, 1641600, 1670300, 1699050, 1727850, 1756700, 1785600, 1814550, 1843550, 1872600, 1901700, 1930850, 1960050, 1989300, 2018600, 2047950, 2077350, 2106800, 2136300, 2165850, 2195450, 2225100, 2254800, 2284550, 2314350, 2344200, 2374100, 2404050, 2434050, 2464100, 2494200, 2524350, 2554550, 2584800, 2615100, 2645450, 2675850, 2706300, 2736800, 2767350, 2797950, 2828600, 2859300, 2890050, 2920850, 2951700, 2982600, 3013550, 3044550, 3075600, 3106700, 3137850, 3169050, 3200300, 3231600, 3262950, 3294350, 3325800, 3357300, 3388850, 3420450, 3452100, 3483800, 3515550, 3547350, 3579200, 3611100, 3643050, 3675050, 3707100, 3739200, 3771350, 3803550, 3835800, 3868100, 3900450, 3932850, 3965300, 3997800, 4030350, 4062950, 4095600, 4128300, 4161050, 4193850, 4226700, 4259600, 4292550, 4325550, 4358600, 4391700, 4424850, 4458050, 4491300, 4524600, 4557950, 4591350, 4624800, 4658300, 4691850, 4725450, 4759100, 4792800, 4826550, 4860350, 4894200, 4928100, 4962050, 4996050, 5030100, 5064200, 5098350, 5132550, 5166800, 5201100, 5235450, 5269850, 5304300, 5338800, 5373350, 5407950, 5442600, 5477300, 5512050, 5546850, 5581700, 5616600, 5651550, 5686550, 5721600, 5756700, 5791850, 5827050, 5862300, 5897600, 5932950, 5968350, 6003800, 6039300, 6074850, 6110450, 6146100, 6181800, 6217550, 6253350, 6289200, 6325100, 6361050, 6397050, 6433100, 6469200, 6505350, 6541550, 6577800, 6614100, 6650450, 6686850, 6723300, 6759800, 6796350, 6832950, 6869600, 6906300, 6943050, 6979850, 7016700, 7053600, 7090550, 7127550, 7164600, 7201700, 7238850, 7276050, 7313300, 7350600, 7387950, 7425350, 7462800, 7500300, 7537850, 7575450, 7613100, 7650800, 7688550, 7726350, 7764200, 7802100, 7840050, 7878050, 7916100, 7954200, 7992350, 8030550, 8068800, 8107100, 8145450, 8183850, 8222300, 8260800, 8299350, 8337950, 8376600, 8415300, 8454050, 8492850, 8531700, 8570600, 8609550, 8648550, 8687600, 8726700, 8765850, 8805050, 8844300, 8883600, 8922950, 8962350, 9001800, 9041300, 9080850, 9120450, 9160100, 9199800, 9239550, 9279350, 9319200, 9359100, 9399050, 9439050, 9479100, 9519200, 9559350, 9599550, 9639800, 9680100, 9720450, 9760850, 9801300, 9841800, 9882350, 9922950, 9963600, 10004300, 10045050, 10085850, 10126700, 10167600, 10208550, 10249550, 10290600, 10331700, 10372850, 10414050, 10455300, 10496600, 10537950, 10579350, 10620800, 10662300, 10703850, 10745450, 10787100, 10828800, 10870550, 10912350, 10954200, 10996100, 11038050, 11080050, 11122100, 11164200, 11206350, 11248550, 11290800, 11333100, 11375450, 11417850, 11460300, 11502800, 11545350, 11587950, 11630600, 11673300, 11716050, 11758850, 11801700, 11844600, 11887550, 11930550, 11973600, 12016700, 12059850, 12103050, 12146300, 12189600, 12232950, 12276350, 12319800, 12363300, 12406850, 12450450, 12494100, 12537800, 12581550, 12625350, 12669200, 12713100, 12757050, 12801050, 12845100, 12889200, 12933350, 12977550, 13021800, 13066100, 13110450, 13154850, 13199300, 13243800, 13288350, 13332950, 13377600, 13422300, 13467050, 13511850, 13556700, 13601600, 13646550, 13691550, 13736600, 13781700, 13826850, 13872050, 13917300, 13962600, 14007950, 14053350, 14098800, 14144300, 14189850, 14235450, 14281100, 14326800, 14372550, 14418350, 14464200, 14510100, 14556050, 14602050, 14648100, 14694200, 14740350, 14786550, 14832800, 14879100, 14925450, 14971850, 15018300, 15064800, 15111350, 15157950, 15204600, 15251300, 15298050, 15344850, 15391700, 15438600, 15485550, 15532550, 15579600, 15626700, 15673850, 15721050, 15768300, 15815600, 15862950, 15910350, 15957800, 16005300, 16052850, 16100450, 16148100, 16195800, 16243550, 16291350, 16339200, 16387100, 16435050, 16483050, 16531100, 16579200, 16627350, 16675550, 16723800, 16772100, 16820450, 16868850, 16917300, 16965800, 17014350, 17062950, 17111600, 17160300, 17209050, 17257850, 17306700, 17355600, 17404550, 17453550, 17502600, 17551700, 17600850, 17650050, 17699300, 17748600, 17797950, 17847350, 17896800, 17946300, 17995850, 18045450, 18095100, 18144800, 18194550, 18244350, 18294200, 18344100, 18394050, 18444050, 18494100, 18544200, 18594350, 18644550, 18694800, 18745100, 18795450, 18845850, 18896300, 18946800, 18997350, 19047950, 19098600, 19149300, 19200050, 19250850, 19301700, 19352600, 19403550, 19454550, 19505600, 19556700, 19607850, 19659050, 19710300, 19761600, 19812950, 19864350, 19915800, 19967300, 20018850, 20070450, 20122100, 20173800, 20225550, 20277350, 20329200, 20381100, 20433050, 20485050, 20537100, 20589200, 20641350, 20693550, 20745800, 20798100, 20850450, 20902850, 20955300, 21007800, 21060350, 21112950, 21165600, 21218300, 21271050, 21323850, 21376700, 21429600, 21482550, 21535550, 21588600, 21641700, 21694850, 21748050, 21801300, 21854600, 21907950, 21961350, 22014800, 22068300, 22121850, 22175450, 22229100, 22282800, 22336550, 22390350, 22444200, 22498100, 22552050, 22606050, 22660100, 22714200, 22768350, 22822550, 22876800, 22931100, 22985450, 23039850, 23094300, 23148800, 23203350, 23257950, 23312600, 23367300, 23422050, 23476850, 23531700, 23586600, 23641550, 23696550, 23751600, 23806700, 23861850, 23917050, 23972300, 24027600, 24082950, 24138350, 24193800, 24249300, 24304850, 24360450, 24416100, 24471800, 24527550, 24583350, 24639200, 24695100, 24751050, 24807050, 24863100, 24919200, 24975350, 25031550, 25087800, 25144100, 25200450, 25256850, 25313300, 25369800, 25426350, 25482950, 25539600, 25596300, 25653050, 25709850, 25766700, 25823600, 25880550, 25937550, 25994600, 26051700, 26108850, 26166050, 26223300, 26280600, 26337950, 26395350, 26452800, 26510300, 26567850, 26625450, 26683100, 26740800, 26798550, 26856350, 26914200, 26972100, 27030050, 27088050, 27146100, 27204200, 27262350, 27320550, 27378800, 27437100, 27495450, 27553850, 27612300, 27670800, 27729350, 27787950, 27846600, 27905300, 27964050, 28022850, 28081700, 28140600, 28199550, 28258550, 28317600, 28376700, 28435850, 28495050, 28554300, 28613600, 28672950, 28732350, 28791800, 28851300, 28910850, 28970450, 29030100, 29089800, 29149550, 29209350, 29269200, 29329100, 29389050, 29449050, 29509100, 29569200, 29629350, 29689550, 29749800, 29810100, 29870450, 29930850, 29991300, 30051800, 30112350, 30172950, 30233600, 30294300, 30355050, 30415850, 30476700, 30537600, 30598550, 30659550, 30720600, 30781700, 30842850, 30904050, 30965300, 31026600, 31087950, 31149350, 31210800, 31272300, 31333850, 31395450, 31457100, 31518800, 31580550, 31642350, 31704200, 31766100, 31828050, 31890050, 31952100, 32014200, 32076350, 32138550, 32200800, 32263100, 32325450, 32387850, 32450300, 32512800, 32575350, 32637950, 32700600, 32763300, 32826050, 32888850, 32951700, 33014600, 33077550, 33140550, 33203600, 33266700, 33329850, 33393050, 33456300, 33519600, 33582950, 33646350, 33709800, 33773300, 33836850, 33900450, 33964100, 34027800, 34091550, 34155350, 34219200, 34283100, 34347050, 34411050, 34475100, 34539200, 34603350, 34667550, 34731800, 34796100, 34860450, 34924850, 34989300, 35053800, 35118350, 35182950, 35247600, 35312300, 35377050, 35441850, 35506700, 35571600, 35636550, 35701550, 35766600, 35831700, 35896850, 35962050, 36027300, 36092600, 36157950, 36223350, 36288800, 36354300, 36419850, 36485450, 36551100, 36616800, 36682550, 36748350, 36814200, 36880100, 36946050, 37012050, 37078100, 37144200, 37210350, 37276550, 37342800, 37409100, 37475450, 37541850, 37608300, 37674800, 37741350, 37807950, 37874600, 37941300, 38008050, 38074850, 38141700, 38208600, 38275550, 38342550, 38409600, 38476700, 38543850, 38611050, 38678300, 38745600, 38812950, 38880350, 38947800, 39015300, 39082850, 39150450, 39218100, 39285800, 39353550, 39421350, 39489200, 39557100, 39625050, 39693050, 39761100, 39829200, 39897350, 39965550, 40033800, 40102100, 40170450, 40238850, 40307300, 40375800, 40444350, 40512950, 40581600, 40650300, 40719050, 40787850, 40856700, 40925600, 40994550, 41063550, 41132600, 41201700, 41270850, 41340050, 41409300, 41478600, 41547950, 41617350, 41686800, 41756300, 41825850, 41895450, 41965100, 42034800, 42104550, 42174350, 42244200, 42314100, 42384050, 42454050, 42524100, 42594200, 42664350, 42734550, 42804800, 42875100, 42945450, 43015850, 43086300, 43156800, 43227350, 43297950, 43368600, 43439300, 43510050, 43580850, 43651700, 43722600, 43793550, 43864550, 43935600, 44006700, 44077850, 44149050, 44220300, 44291600, 44362950, 44434350, 44505800, 44577300, 44648850, 44720450, 44792100, 44863800, 44935550, 45007350, 45079200, 45151100, 45223050, 45295050, 45367100, 45439200, 45511350, 45583550, 45655800, 45728100, 45800450, 45872850, 45945300, 46017800, 46090350, 46162950, 46235600, 46308300, 46381050, 46453850, 46526700, 46599600, 46672550, 46745550, 46818600, 46891700, 46964850, 47038050, 47111300, 47184600, 47257950, 47331350, 47404800, 47478300, 47551850, 47625450, 47699100, 47772800, 47846550, 47920350, 47994200, 48068100, 48142050, 48216050, 48290100, 48364200, 48438350, 48512550, 48586800, 48661100, 48735450, 48809850, 48884300, 48958800, 49033350, 49107950, 49182600, 49257300, 49332050, 49406850, 49481700, 49556600, 49631550, 49706550, 49781600, 49856700, 49931850, 50007050, 50082300, 50157600, 50232950, 50308350, 50383800, 50459300, 50534850, 50610450, 50686100, 50761800, 50837550, 50913350, 50989200, 51065100, 51141050, 51217050, 51293100, 51369200, 51445350, 51521550, 51597800, 51674100, 51750450, 51826850, 51903300, 51979800, 52056350, 52132950, 52209600, 52286300, 52363050, 52439850, 52516700, 52593600, 52670550, 52747550, 52824600, 52901700, 52978850, 53056050, 53133300, 53210600, 53287950, 53365350, 53442800, 53520300, 53597850, 53675450, 53753100, 53830800, 53908550, 53986350, 54064200, 54142100, 54220050, 54298050, 54376100, 54454200, 54532350, 54610550, 54688800, 54767100, 54845450, 54923850, 55002300, 55080800, 55159350, 55237950, 55316600, 55395300, 55474050, 55552850, 55631700, 55710600, 55789550, 55868550, 55947600, 56026700, 56105850, 56185050, 56264300, 56343600, 56422950, 56502350, 56581800, 56661300, 56740850, 56820450, 56900100, 56979800, 57059550, 57139350, 57219200, 57299100, 57379050, 57459050, 57539100, 57619200, 57699350, 57779550, 57859800, 57940100, 58020450, 58100850, 58181300, 58261800, 58342350, 58422950, 58503600, 58584300, 58665050, 58745850, 58826700, 58907600, 58988550, 59069550, 59150600, 59231700, 59312850, 59394050, 59475300, 59556600, 59637950, 59719350, 59800800, 59882300, 59963850, 60045450, 60127100, 60208800, 60290550, 60372350, 60454200, 60536100, 60618050, 60700050, 60782100, 60864200, 60946350, 61028550, 61110800, 61193100, 61275450, 61357850, 61440300, 61522800, 61605350, 61687950, 61770600, 61853300, 61936050, 62018850, 62101700, 62184600, 62267550, 62350550, 62433600, 62516700, 62599850, 62683050, 62766300, 62849600, 62932950, 63016350, 63099800, 63183300, 63266850, 63350450, 63434100, 63517800, 63601550, 63685350, 63769200, 63853100, 63937050, 64021050, 64105100, 64189200, 64273350, 64357550, 64441800, 64526100, 64610450, 64694850, 64779300, 64863800, 64948350, 65032950, 65117600, 65202300, 65287050, 65371850, 65456700, 65541600, 65626550, 65711550, 65796600, 65881700, 65966850, 66052050, 66137300, 66222600, 66307950, 66393350, 66478800, 66564300, 66649850, 66735450, 66821100, 66906800, 66992550, 67078350, 67164200, 67250100, 67336050, 67422050, 67508100, 67594200, 67680350, 67766550, 67852800, 67939100, 68025450, 68111850, 68198300, 68284800, 68371350, 68457950, 68544600, 68631300, 68718050, 68804850, 68891700, 68978600, 69065550, 69152550, 69239600, 69326700, 69413850, 69501050, 69588300, 69675600, 69762950, 69850350, 69937800, 70025300, 70112850, 70200450, 70288100, 70375800, 70463550, 70551350, 70639200, 70727100, 70815050, 70903050, 70991100, 71079200, 71167350, 71255550, 71343800, 71432100, 71520450, 71608850, 71697300, 71785800, 71874350, 71962950, 72051600, 72140300, 72229050, 72317850, 72406700, 72495600, 72584550, 72673550, 72762600, 72851700, 72940850, 73030050, 73119300, 73208600, 73297950, 73387350, 73476800, 73566300, 73655850, 73745450, 73835100, 73924800, 74014550, 74104350, 74194200, 74284100, 74374050, 74464050, 74554100, 74644200, 74734350, 74824550, 74914800, 75005100, 75095450, 75185850, 75276300, 75366800, 75457350, 75547950, 75638600, 75729300, 75820050, 75910850, 76001700, 76092600, 76183550, 76274550, 76365600, 76456700, 76547850, 76639050, 76730300, 76821600, 76912950, 77004350, 77095800, 77187300, 77278850, 77370450, 77462100, 77553800, 77645550, 77737350, 77829200, 77921100, 78013050, 78105050, 78197100, 78289200, 78381350, 78473550, 78565800, 78658100, 78750450, 78842850, 78935300, 79027800, 79120350, 79212950, 79305600, 79398300, 79491050, 79583850, 79676700, 79769600, 79862550, 79955550, 80048600, 80141700, 80234850, 80328050, 80421300, 80514600, 80607950, 80701350, 80794800, 80888300, 80981850, 81075450, 81169100, 81262800, 81356550, 81450350, 81544200, 81638100, 81732050, 81826050, 81920100, 82014200, 82108350, 82202550, 82296800, 82391100, 82485450, 82579850, 82674300, 82768800, 82863350, 82957950, 83052600, 83147300, 83242050, 83336850, 83431700, 83526600, 83621550, 83716550, 83811600, 83906700, 84001850, 84097050, 84192300, 84287600, 84382950, 84478350, 84573800, 84669300, 84764850, 84860450, 84956100, 85051800, 85147550, 85243350, 85339200, 85435100, 85531050, 85627050, 85723100, 85819200, 85915350, 86011550, 86107800, 86204100, 86300450, 86396850, 86493300, 86589800, 86686350, 86782950, 86879600, 86976300, 87073050, 87169850, 87266700, 87363600, 87460550, 87557550, 87654600, 87751700, 87848850, 87946050, 88043300, 88140600, 88237950, 88335350, 88432800, 88530300, 88627850, 88725450, 88823100, 88920800, 89018550, 89116350, 89214200, 89312100, 89410050, 89508050, 89606100, 89704200, 89802350, 89900550, 89998800, 90097100, 90195450, 90293850, 90392300, 90490800, 90589350, 90687950, 90786600, 90885300, 90984050, 91082850, 91181700, 91280600, 91379550, 91478550, 91577600, 91676700, 91775850, 91875050, 91974300, 92073600, 92172950, 92272350, 92371800, 92471300, 92570850, 92670450, 92770100, 92869800, 92969550, 93069350, 93169200, 93269100, 93369050, 93469050, 93569100, 93669200, 93769350, 93869550, 93969800, 94070100, 94170450, 94270850, 94371300, 94471800, 94572350, 94672950, 94773600, 94874300, 94975050, 95075850, 95176700, 95277600, 95378550, 95479550, 95580600, 95681700, 95782850, 95884050, 95985300, 96086600, 96187950, 96289350, 96390800, 96492300, 96593850, 96695450, 96797100, 96898800, 97000550, 97102350, 97204200, 97306100, 97408050, 97510050, 97612100, 97714200, 97816350, 97918550, 98020800, 98123100, 98225450, 98327850, 98430300, 98532800, 98635350, 98737950, 98840600, 98943300, 99046050, 99148850, 99251700, 99354600, 99457550, 99560550, 99663600, 99766700, 99869850, 99973050, 100076300, 100179600, 100282950, 100386350, 100489800, 100593300, 100696850, 100800450, 100904100, 101007800, 101111550, 101215350, 101319200, 101423100, 101527050, 101631050, 101735100, 101839200, 101943350, 102047550, 102151800, 102256100, 102360450, 102464850, 102569300, 102673800, 102778350, 102882950, 102987600, 103092300, 103197050, 103301850, 103406700, 103511600, 103616550, 103721550, 103826600, 103931700, 104036850, 104142050, 104247300, 104352600, 104457950, 104563350, 104668800, 104774300, 104879850, 104985450, 105091100, 105196800, 105302550, 105408350, 105514200, 105620100, 105726050, 105832050, 105938100, 106044200, 106150350, 106256550, 106362800, 106469100, 106575450, 106681850, 106788300, 106894800, 107001350, 107107950, 107214600, 107321300, 107428050, 107534850, 107641700, 107748600, 107855550, 107962550, 108069600, 108176700, 108283850, 108391050, 108498300, 108605600, 108712950, 108820350, 108927800, 109035300, 109142850, 109250450, 109358100, 109465800, 109573550, 109681350, 109789200, 109897100, 110005050, 110113050, 110221100, 110329200, 110437350, 110545550, 110653800, 110762100, 110870450, 110978850, 111087300, 111195800, 111304350, 111412950, 111521600, 111630300, 111739050, 111847850, 111956700, 112065600, 112174550, 112283550, 112392600, 112501700, 112610850, 112720050, 112829300, 112938600, 113047950, 113157350, 113266800, 113376300, 113485850, 113595450, 113705100, 113814800, 113924550, 114034350, 114144200, 114254100, 114364050, 114474050, 114584100, 114694200, 114804350, 114914550, 115024800, 115135100, 115245450, 115355850, 115466300, 115576800, 115687350, 115797950, 115908600, 116019300, 116130050, 116240850, 116351700, 116462600, 116573550, 116684550, 116795600, 116906700, 117017850, 117129050, 117240300, 117351600, 117462950, 117574350, 117685800, 117797300, 117908850, 118020450, 118132100, 118243800, 118355550, 118467350, 118579200, 118691100, 118803050, 118915050, 119027100, 119139200, 119251350, 119363550, 119475800, 119588100, 119700450, 119812850, 119925300, 120037800, 120150350, 120262950, 120375600, 120488300, 120601050, 120713850, 120826700, 120939600, 121052550, 121165550, 121278600, 121391700, 121504850, 121618050, 121731300, 121844600, 121957950, 122071350, 122184800, 122298300, 122411850, 122525450, 122639100, 122752800, 122866550, 122980350, 123094200, 123208100, 123322050, 123436050, 123550100, 123664200, 123778350, 123892550, 124006800, 124121100, 124235450, 124349850, 124464300, 124578800, 124693350, 124807950, 124922600, 125037300, 125152050, 125266850, 125381700, 125496600, 125611550, 125726550, 125841600, 125956700, 126071850, 126187050, 126302300, 126417600, 126532950, 126648350, 126763800, 126879300, 126994850, 127110450, 127226100, 127341800, 127457550, 127573350, 127689200, 127805100, 127921050, 128037050, 128153100, 128269200, 128385350, 128501550, 128617800, 128734100, 128850450, 128966850, 129083300, 129199800, 129316350, 129432950, 129549600, 129666300, 129783050, 129899850, 130016700, 130133600, 130250550, 130367550, 130484600, 130601700, 130718850, 130836050, 130953300, 131070600, 131187950, 131305350, 131422800, 131540300, 131657850, 131775450, 131893100, 132010800, 132128550, 132246350, 132364200, 132482100, 132600050, 132718050, 132836100, 132954200, 133072350, 133190550, 133308800, 133427100, 133545450, 133663850, 133782300, 133900800, 134019350, 134137950, 134256600, 134375300, 134494050, 134612850, 134731700, 134850600, 134969550, 135088550, 135207600, 135326700, 135445850, 135565050, 135684300, 135803600, 135922950, 136042350, 136161800, 136281300, 136400850, 136520450, 136640100, 136759800, 136879550, 136999350, 137119200, 137239100, 137359050, 137479050, 137599100, 137719200, 137839350, 137959550, 138079800, 138200100, 138320450, 138440850, 138561300, 138681800, 138802350, 138922950, 139043600, 139164300, 139285050, 139405850, 139526700, 139647600, 139768550, 139889550, 140010600, 140131700, 140252850, 140374050, 140495300, 140616600, 140737950, 140859350, 140980800, 141102300, 141223850, 141345450, 141467100, 141588800, 141710550, 141832350, 141954200, 142076100, 142198050, 142320050, 142442100, 142564200, 142686350, 142808550, 142930800, 143053100, 143175450, 143297850, 143420300, 143542800, 143665350, 143787950, 143910600, 144033300, 144156050, 144278850, 144401700, 144524600, 144647550, 144770550, 144893600, 145016700, 145139850, 145263050, 145386300, 145509600, 145632950, 145756350, 145879800, 146003300, 146126850, 146250450, 146374100, 146497800, 146621550, 146745350, 146869200, 146993100, 147117050, 147241050, 147365100, 147489200, 147613350, 147737550, 147861800, 147986100, 148110450, 148234850, 148359300, 148483800, 148608350, 148732950, 148857600, 148982300, 149107050, 149231850, 149356700, 149481600, 149606550, 149731550, 149856600, 149981700, 150106850, 150232050, 150357300, 150482600, 150607950, 150733350, 150858800, 150984300, 151109850, 151235450, 151361100, 151486800, 151612550, 151738350, 151864200, 151990100, 152116050, 152242050, 152368100, 152494200, 152620350, 152746550, 152872800, 152999100, 153125450, 153251850, 153378300, 153504800, 153631350, 153757950, 153884600, 154011300, 154138050, 154264850, 154391700, 154518600, 154645550, 154772550, 154899600, 155026700, 155153850, 155281050, 155408300, 155535600, 155662950, 155790350, 155917800, 156045300, 156172850, 156300450, 156428100, 156555800, 156683550, 156811350, 156939200, 157067100, 157195050, 157323050, 157451100, 157579200, 157707350, 157835550, 157963800, 158092100, 158220450, 158348850, 158477300, 158605800, 158734350, 158862950, 158991600, 159120300, 159249050, 159377850, 159506700, 159635600, 159764550, 159893550, 160022600, 160151700, 160280850, 160410050, 160539300, 160668600, 160797950, 160927350, 161056800, 161186300, 161315850, 161445450, 161575100, 161704800, 161834550, 161964350, 162094200, 162224100, 162354050, 162484050, 162614100, 162744200, 162874350, 163004550, 163134800, 163265100, 163395450, 163525850, 163656300, 163786800, 163917350, 164047950, 164178600, 164309300, 164440050, 164570850, 164701700, 164832600, 164963550, 165094550, 165225600, 165356700, 165487850, 165619050, 165750300, 165881600, 166012950, 166144350, 166275800, 166407300, 166538850, 166670450, 166802100, 166933800, 167065550, 167197350, 167329200, 167461100, 167593050, 167725050, 167857100, 167989200, 168121350, 168253550, 168385800, 168518100, 168650450, 168782850, 168915300, 169047800, 169180350, 169312950, 169445600, 169578300, 169711050, 169843850, 169976700, 170109600, 170242550, 170375550, 170508600, 170641700, 170774850, 170908050, 171041300, 171174600, 171307950, 171441350, 171574800, 171708300, 171841850, 171975450, 172109100, 172242800, 172376550, 172510350, 172644200, 172778100, 172912050, 173046050, 173180100, 173314200, 173448350, 173582550, 173716800, 173851100, 173985450, 174119850, 174254300, 174388800, 174523350, 174657950, 174792600, 174927300, 175062050, 175196850, 175331700, 175466600, 175601550, 175736550, 175871600, 176006700, 176141850, 176277050, 176412300, 176547600, 176682950, 176818350, 176953800, 177089300, 177224850, 177360450, 177496100, 177631800, 177767550, 177903350, 178039200, 178175100, 178311050, 178447050, 178583100, 178719200, 178855350, 178991550, 179127800, 179264100, 179400450, 179536850, 179673300, 179809800, 179946350, 180082950, 180219600, 180356300, 180493050, 180629850, 180766700, 180903600, 181040550, 181177550, 181314600, 181451700, 181588850, 181726050, 181863300, 182000600, 182137950, 182275350, 182412800, 182550300, 182687850, 182825450, 182963100, 183100800, 183238550, 183376350, 183514200, 183652100, 183790050, 183928050, 184066100, 184204200, 184342350, 184480550, 184618800, 184757100, 184895450, 185033850, 185172300, 185310800, 185449350, 185587950, 185726600, 185865300, 186004050, 186142850, 186281700, 186420600, 186559550, 186698550, 186837600, 186976700, 187115850, 187255050, 187394300, 187533600, 187672950, 187812350, 187951800, 188091300, 188230850, 188370450, 188510100, 188649800, 188789550, 188929350, 189069200, 189209100, 189349050, 189489050, 189629100, 189769200, 189909350, 190049550, 190189800, 190330100, 190470450, 190610850, 190751300, 190891800, 191032350, 191172950, 191313600, 191454300, 191595050, 191735850, 191876700, 192017600, 192158550, 192299550, 192440600, 192581700, 192722850, 192864050, 193005300, 193146600, 193287950, 193429350, 193570800, 193712300, 193853850, 193995450, 194137100, 194278800, 194420550, 194562350, 194704200, 194846100, 194988050, 195130050, 195272100, 195414200, 195556350, 195698550, 195840800, 195983100, 196125450, 196267850, 196410300, 196552800, 196695350, 196837950, 196980600, 197123300, 197266050, 197408850, 197551700, 197694600, 197837550, 197980550, 198123600, 198266700, 198409850, 198553050, 198696300, 198839600, 198982950, 199126350, 199269800, 199413300, 199556850, 199700450, 199844100, 199987800, 200131550, 200275350, 200419200, 200563100, 200707050, 200851050, 200995100, 201139200, 201283350, 201427550, 201571800, 201716100, 201860450, 202004850, 202149300, 202293800, 202438350, 202582950, 202727600, 202872300, 203017050, 203161850, 203306700, 203451600, 203596550, 203741550, 203886600, 204031700, 204176850, 204322050, 204467300, 204612600, 204757950, 204903350, 205048800, 205194300, 205339850, 205485450, 205631100, 205776800, 205922550, 206068350, 206214200, 206360100, 206506050, 206652050, 206798100, 206944200, 207090350, 207236550, 207382800, 207529100, 207675450, 207821850, 207968300, 208114800, 208261350, 208407950, 208554600, 208701300, 208848050, 208994850, 209141700, 209288600, 209435550, 209582550, 209729600, 209876700, 210023850, 210171050, 210318300, 210465600, 210612950, 210760350, 210907800, 211055300, 211202850, 211350450, 211498100, 211645800, 211793550, 211941350, 212089200, 212237100, 212385050, 212533050, 212681100, 212829200, 212977350, 213125550, 213273800, 213422100, 213570450, 213718850, 213867300, 214015800, 214164350, 214312950, 214461600, 214610300, 214759050, 214907850, 215056700, 215205600, 215354550, 215503550, 215652600, 215801700, 215950850, 216100050, 216249300, 216398600, 216547950, 216697350, 216846800, 216996300, 217145850, 217295450, 217445100, 217594800, 217744550, 217894350, 218044200, 218194100, 218344050, 218494050, 218644100, 218794200, 218944350, 219094550, 219244800, 219395100, 219545450, 219695850, 219846300, 219996800, 220147350, 220297950, 220448600, 220599300, 220750050, 220900850, 221051700, 221202600, 221353550, 221504550, 221655600, 221806700, 221957850, 222109050, 222260300, 222411600, 222562950, 222714350, 222865800, 223017300, 223168850, 223320450, 223472100, 223623800, 223775550, 223927350, 224079200, 224231100, 224383050, 224535050, 224687100, 224839200, 224991350, 225143550, 225295800, 225448100, 225600450, 225752850, 225905300, 226057800, 226210350, 226362950, 226515600, 226668300, 226821050, 226973850, 227126700, 227279600, 227432550, 227585550, 227738600, 227891700, 228044850, 228198050, 228351300, 228504600, 228657950, 228811350, 228964800, 229118300, 229271850, 229425450, 229579100, 229732800, 229886550, 230040350, 230194200, 230348100, 230502050, 230656050, 230810100, 230964200, 231118350, 231272550, 231426800, 231581100, 231735450, 231889850, 232044300, 232198800, 232353350, 232507950, 232662600, 232817300, 232972050, 233126850, 233281700, 233436600, 233591550, 233746550, 233901600, 234056700, 234211850, 234367050, 234522300, 234677600, 234832950, 234988350, 235143800, 235299300, 235454850, 235610450, 235766100, 235921800, 236077550, 236233350, 236389200, 236545100, 236701050, 236857050, 237013100, 237169200, 237325350, 237481550, 237637800, 237794100, 237950450, 238106850, 238263300, 238419800, 238576350, 238732950, 238889600, 239046300, 239203050, 239359850, 239516700, 239673600, 239830550, 239987550, 240144600, 240301700, 240458850, 240616050, 240773300, 240930600, 241087950, 241245350, 241402800, 241560300, 241717850, 241875450, 242033100, 242190800, 242348550, 242506350, 242664200, 242822100, 242980050, 243138050, 243296100, 243454200, 243612350, 243770550, 243928800, 244087100, 244245450, 244403850, 244562300, 244720800, 244879350, 245037950, 245196600, 245355300, 245514050, 245672850, 245831700, 245990600, 246149550, 246308550, 246467600, 246626700, 246785850, 246945050, 247104300, 247263600, 247422950, 247582350, 247741800, 247901300, 248060850, 248220450, 248380100, 248539800, 248699550, 248859350, 249019200, 249179100, 249339050, 249499050, 249659100, 249819200, 249979350, 250139550, 250299800, 250460100, 250620450, 250780850, 250941300, 251101800, 251262350, 251422950, 251583600, 251744300, 251905050, 252065850, 252226700, 252387600, 252548550, 252709550, 252870600, 253031700, 253192850, 253354050, 253515300, 253676600, 253837950, 253999350, 254160800, 254322300, 254483850, 254645450, 254807100, 254968800, 255130550, 255292350, 255454200, 255616100, 255778050, 255940050, 256102100, 256264200, 256426350, 256588550, 256750800, 256913100, 257075450, 257237850, 257400300, 257562800, 257725350, 257887950, 258050600, 258213300, 258376050, 258538850, 258701700, 258864600, 259027550, 259190550, 259353600, 259516700, 259679850, 259843050, 260006300, 260169600, 260332950, 260496350, 260659800, 260823300, 260986850, 261150450, 261314100, 261477800, 261641550, 261805350, 261969200, 262133100, 262297050, 262461050, 262625100, 262789200, 262953350, 263117550, 263281800, 263446100, 263610450, 263774850, 263939300, 264103800, 264268350, 264432950, 264597600, 264762300, 264927050, 265091850, 265256700, 265421600, 265586550, 265751550, 265916600, 266081700, 266246850, 266412050, 266577300, 266742600, 266907950, 267073350, 267238800, 267404300, 267569850, 267735450, 267901100, 268066800, 268232550, 268398350, 268564200, 268730100, 268896050, 269062050, 269228100, 269394200, 269560350, 269726550, 269892800, 270059100, 270225450, 270391850, 270558300, 270724800, 270891350, 271057950, 271224600, 271391300, 271558050, 271724850, 271891700, 272058600, 272225550, 272392550, 272559600, 272726700, 272893850, 273061050, 273228300, 273395600, 273562950, 273730350, 273897800, 274065300, 274232850, 274400450, 274568100, 274735800, 274903550, 275071350, 275239200, 275407100, 275575050, 275743050, 275911100, 276079200, 276247350, 276415550, 276583800, 276752100, 276920450, 277088850, 277257300, 277425800, 277594350, 277762950, 277931600, 278100300, 278269050, 278437850, 278606700, 278775600, 278944550, 279113550, 279282600, 279451700, 279620850, 279790050, 279959300, 280128600, 280297950, 280467350, 280636800, 280806300, 280975850, 281145450, 281315100, 281484800, 281654550, 281824350, 281994200, 282164100, 282334050, 282504050, 282674100, 282844200, 283014350, 283184550, 283354800, 283525100, 283695450, 283865850, 284036300, 284206800, 284377350, 284547950, 284718600, 284889300, 285060050, 285230850, 285401700, 285572600, 285743550, 285914550, 286085600, 286256700, 286427850, 286599050, 286770300, 286941600, 287112950, 287284350, 287455800, 287627300, 287798850, 287970450, 288142100, 288313800, 288485550, 288657350, 288829200, 289001100, 289173050, 289345050, 289517100, 289689200, 289861350, 290033550, 290205800, 290378100, 290550450, 290722850, 290895300, 291067800, 291240350, 291412950, 291585600, 291758300, 291931050, 292103850, 292276700, 292449600, 292622550, 292795550, 292968600, 293141700, 293314850, 293488050, 293661300, 293834600, 294007950, 294181350, 294354800, 294528300, 294701850, 294875450, 295049100, 295222800, 295396550, 295570350, 295744200, 295918100, 296092050, 296266050, 296440100, 296614200, 296788350, 296962550, 297136800, 297311100, 297485450, 297659850, 297834300, 298008800, 298183350, 298357950, 298532600, 298707300, 298882050, 299056850, 299231700, 299406600, 299581550, 299756550, 299931600, 300106700, 300281850, 300457050, 300632300, 300807600, 300982950, 301158350, 301333800, 301509300, 301684850, 301860450, 302036100, 302211800, 302387550, 302563350, 302739200, 302915100, 303091050, 303267050, 303443100, 303619200, 303795350, 303971550, 304147800, 304324100, 304500450, 304676850, 304853300, 305029800, 305206350, 305382950, 305559600, 305736300, 305913050, 306089850, 306266700, 306443600, 306620550, 306797550, 306974600, 307151700, 307328850, 307506050, 307683300, 307860600, 308037950, 308215350, 308392800, 308570300, 308747850, 308925450, 309103100, 309280800, 309458550, 309636350, 309814200, 309992100, 310170050, 310348050, 310526100, 310704200, 310882350, 311060550, 311238800, 311417100, 311595450, 311773850, 311952300, 312130800, 312309350, 312487950, 312666600, 312845300, 313024050, 313202850, 313381700, 313560600, 313739550, 313918550, 314097600, 314276700, 314455850, 314635050, 314814300, 314993600, 315172950, 315352350, 315531800, 315711300, 315890850, 316070450, 316250100, 316429800, 316609550, 316789350, 316969200, 317149100, 317329050, 317509050, 317689100, 317869200, 318049350, 318229550, 318409800, 318590100, 318770450, 318950850, 319131300, 319311800, 319492350, 319672950, 319853600, 320034300, 320215050, 320395850, 320576700, 320757600, 320938550, 321119550, 321300600, 321481700, 321662850, 321844050, 322025300, 322206600, 322387950, 322569350, 322750800, 322932300, 323113850, 323295450, 323477100, 323658800, 323840550, 324022350, 324204200, 324386100, 324568050, 324750050, 324932100, 325114200, 325296350, 325478550, 325660800, 325843100, 326025450, 326207850, 326390300, 326572800, 326755350, 326937950, 327120600, 327303300, 327486050, 327668850, 327851700, 328034600, 328217550, 328400550, 328583600, 328766700, 328949850, 329133050, 329316300, 329499600, 329682950, 329866350, 330049800, 330233300, 330416850, 330600450, 330784100, 330967800, 331151550, 331335350, 331519200, 331703100, 331887050, 332071050, 332255100, 332439200, 332623350, 332807550, 332991800, 333176100, 333360450, 333544850, 333729300, 333913800, 334098350, 334282950, 334467600, 334652300, 334837050, 335021850, 335206700, 335391600, 335576550, 335761550, 335946600, 336131700, 336316850, 336502050, 336687300, 336872600, 337057950, 337243350, 337428800, 337614300, 337799850, 337985450, 338171100, 338356800, 338542550, 338728350, 338914200, 339100100, 339286050, 339472050, 339658100, 339844200, 340030350, 340216550, 340402800, 340589100, 340775450, 340961850, 341148300, 341334800, 341521350, 341707950, 341894600, 342081300, 342268050, 342454850, 342641700, 342828600, 343015550, 343202550, 343389600, 343576700, 343763850, 343951050, 344138300, 344325600, 344512950, 344700350, 344887800, 345075300, 345262850, 345450450, 345638100, 345825800, 346013550, 346201350, 346389200, 346577100, 346765050, 346953050, 347141100, 347329200, 347517350, 347705550, 347893800, 348082100, 348270450, 348458850, 348647300, 348835800, 349024350, 349212950, 349401600, 349590300, 349779050, 349967850, 350156700, 350345600, 350534550, 350723550, 350912600, 351101700, 351290850, 351480050, 351669300, 351858600, 352047950, 352237350, 352426800, 352616300, 352805850, 352995450, 353185100, 353374800, 353564550, 353754350, 353944200, 354134100, 354324050, 354514050, 354704100, 354894200, 355084350, 355274550, 355464800, 355655100, 355845450, 356035850, 356226300, 356416800, 356607350, 356797950, 356988600, 357179300, 357370050, 357560850, 357751700, 357942600, 358133550, 358324550, 358515600, 358706700, 358897850, 359089050, 359280300, 359471600, 359662950, 359854350, 360045800, 360237300, 360428850, 360620450, 360812100, 361003800, 361195550, 361387350, 361579200, 361771100, 361963050, 362155050, 362347100, 362539200, 362731350, 362923550, 363115800, 363308100, 363500450, 363692850, 363885300, 364077800, 364270350, 364462950, 364655600, 364848300, 365041050, 365233850, 365426700, 365619600, 365812550, 366005550, 366198600, 366391700, 366584850, 366778050, 366971300, 367164600, 367357950, 367551350, 367744800, 367938300, 368131850, 368325450, 368519100, 368712800, 368906550, 369100350, 369294200, 369488100, 369682050, 369876050, 370070100, 370264200, 370458350, 370652550, 370846800, 371041100, 371235450, 371429850, 371624300, 371818800, 372013350, 372207950, 372402600, 372597300, 372792050, 372986850, 373181700, 373376600, 373571550, 373766550, 373961600, 374156700, 374351850, 374547050, 374742300, 374937600, 375132950, 375328350, 375523800, 375719300, 375914850, 376110450, 376306100, 376501800, 376697550, 376893350, 377089200, 377285100, 377481050, 377677050, 377873100, 378069200, 378265350, 378461550, 378657800, 378854100, 379050450, 379246850, 379443300, 379639800, 379836350, 380032950, 380229600, 380426300, 380623050, 380819850, 381016700, 381213600, 381410550, 381607550, 381804600, 382001700, 382198850, 382396050, 382593300, 382790600, 382987950, 383185350, 383382800, 383580300, 383777850, 383975450, 384173100, 384370800, 384568550, 384766350, 384964200, 385162100, 385360050, 385558050, 385756100, 385954200, 386152350, 386350550, 386548800, 386747100, 386945450, 387143850, 387342300, 387540800, 387739350, 387937950, 388136600, 388335300, 388534050, 388732850, 388931700, 389130600, 389329550, 389528550, 389727600, 389926700, 390125850, 390325050, 390524300, 390723600, 390922950, 391122350, 391321800, 391521300, 391720850, 391920450, 392120100, 392319800, 392519550, 392719350, 392919200, 393119100, 393319050, 393519050, 393719100, 393919200, 394119350, 394319550, 394519800, 394720100, 394920450, 395120850, 395321300, 395521800, 395722350, 395922950, 396123600, 396324300, 396525050, 396725850, 396926700, 397127600, 397328550, 397529550, 397730600, 397931700, 398132850, 398334050, 398535300, 398736600, 398937950, 399139350, 399340800, 399542300, 399743850, 399945450, 400147100, 400348800, 400550550, 400752350, 400954200, 401156100, 401358050, 401560050, 401762100, 401964200, 402166350, 402368550, 402570800, 402773100, 402975450, 403177850, 403380300, 403582800, 403785350, 403987950, 404190600, 404393300, 404596050, 404798850, 405001700, 405204600, 405407550, 405610550, 405813600, 406016700, 406219850, 406423050, 406626300, 406829600, 407032950, 407236350, 407439800, 407643300, 407846850, 408050450, 408254100, 408457800, 408661550, 408865350, 409069200, 409273100, 409477050, 409681050, 409885100, 410089200, 410293350, 410497550, 410701800, 410906100, 411110450, 411314850, 411519300, 411723800, 411928350, 412132950, 412337600, 412542300, 412747050, 412951850, 413156700, 413361600, 413566550, 413771550, 413976600, 414181700, 414386850, 414592050, 414797300, 415002600, 415207950, 415413350, 415618800, 415824300, 416029850, 416235450, 416441100, 416646800, 416852550, 417058350, 417264200, 417470100, 417676050, 417882050, 418088100, 418294200, 418500350, 418706550, 418912800, 419119100, 419325450, 419531850, 419738300, 419944800, 420151350, 420357950, 420564600, 420771300, 420978050, 421184850, 421391700, 421598600, 421805550, 422012550, 422219600, 422426700, 422633850, 422841050, 423048300, 423255600, 423462950, 423670350, 423877800, 424085300, 424292850, 424500450, 424708100, 424915800, 425123550, 425331350, 425539200, 425747100, 425955050, 426163050, 426371100, 426579200, 426787350, 426995550, 427203800, 427412100, 427620450, 427828850, 428037300, 428245800, 428454350, 428662950, 428871600, 429080300, 429289050, 429497850, 429706700, 429915600, 430124550, 430333550, 430542600, 430751700, 430960850, 431170050, 431379300, 431588600, 431797950, 432007350, 432216800, 432426300, 432635850, 432845450, 433055100, 433264800, 433474550, 433684350, 433894200, 434104100, 434314050, 434524050, 434734100, 434944200, 435154350, 435364550, 435574800, 435785100, 435995450, 436205850, 436416300, 436626800, 436837350, 437047950, 437258600, 437469300, 437680050, 437890850, 438101700, 438312600, 438523550, 438734550, 438945600, 439156700, 439367850, 439579050, 439790300, 440001600, 440212950, 440424350, 440635800, 440847300, 441058850, 441270450, 441482100, 441693800, 441905550, 442117350, 442329200, 442541100, 442753050, 442965050, 443177100, 443389200, 443601350, 443813550, 444025800, 444238100, 444450450, 444662850, 444875300, 445087800, 445300350, 445512950, 445725600, 445938300, 446151050, 446363850, 446576700, 446789600, 447002550, 447215550, 447428600, 447641700, 447854850, 448068050, 448281300, 448494600, 448707950, 448921350, 449134800, 449348300, 449561850, 449775450, 449989100, 450202800, 450416550, 450630350, 450844200, 451058100, 451272050, 451486050, 451700100, 451914200, 452128350, 452342550, 452556800, 452771100, 452985450, 453199850, 453414300, 453628800, 453843350, 454057950, 454272600, 454487300, 454702050, 454916850, 455131700, 455346600, 455561550, 455776550, 455991600, 456206700, 456421850, 456637050, 456852300, 457067600, 457282950, 457498350, 457713800, 457929300, 458144850, 458360450, 458576100, 458791800, 459007550, 459223350, 459439200, 459655100, 459871050, 460087050, 460303100, 460519200, 460735350, 460951550, 461167800, 461384100, 461600450, 461816850, 462033300, 462249800, 462466350, 462682950, 462899600, 463116300, 463333050, 463549850, 463766700, 463983600, 464200550, 464417550, 464634600, 464851700, 465068850, 465286050, 465503300, 465720600, 465937950, 466155350, 466372800, 466590300, 466807850, 467025450, 467243100, 467460800, 467678550, 467896350, 468114200, 468332100, 468550050, 468768050, 468986100, 469204200, 469422350, 469640550, 469858800, 470077100, 470295450, 470513850, 470732300, 470950800, 471169350, 471387950, 471606600, 471825300, 472044050, 472262850, 472481700, 472700600, 472919550, 473138550, 473357600, 473576700, 473795850, 474015050, 474234300, 474453600, 474672950, 474892350, 475111800, 475331300, 475550850, 475770450, 475990100, 476209800, 476429550, 476649350, 476869200, 477089100, 477309050, 477529050, 477749100, 477969200, 478189350, 478409550, 478629800, 478850100, 479070450, 479290850, 479511300, 479731800, 479952350, 480172950, 480393600, 480614300, 480835050, 481055850, 481276700, 481497600, 481718550, 481939550, 482160600, 482381700, 482602850, 482824050, 483045300, 483266600, 483487950, 483709350, 483930800, 484152300, 484373850, 484595450, 484817100, 485038800, 485260550, 485482350, 485704200, 485926100, 486148050, 486370050, 486592100, 486814200, 487036350, 487258550, 487480800, 487703100, 487925450, 488147850, 488370300, 488592800, 488815350, 489037950, 489260600, 489483300, 489706050, 489928850, 490151700, 490374600, 490597550, 490820550, 491043600, 491266700, 491489850, 491713050, 491936300, 492159600, 492382950, 492606350, 492829800, 493053300, 493276850, 493500450, 493724100, 493947800, 494171550, 494395350, 494619200, 494843100, 495067050, 495291050, 495515100, 495739200, 495963350, 496187550, 496411800, 496636100, 496860450, 497084850, 497309300, 497533800, 497758350, 497982950, 498207600, 498432300, 498657050, 498881850, 499106700, 499331600, 499556550, 499781550, 500006600, 500231700, 500456850, 500682050, 500907300, 501132600, 501357950, 501583350, 501808800, 502034300, 502259850, 502485450, 502711100, 502936800, 503162550, 503388350, 503614200, 503840100, 504066050, 504292050, 504518100, 504744200, 504970350, 505196550, 505422800, 505649100, 505875450, 506101850, 506328300, 506554800, 506781350, 507007950, 507234600, 507461300, 507688050, 507914850, 508141700, 508368600, 508595550, 508822550, 509049600, 509276700, 509503850, 509731050, 509958300, 510185600, 510412950, 510640350, 510867800, 511095300, 511322850, 511550450, 511778100, 512005800, 512233550, 512461350, 512689200, 512917100, 513145050, 513373050, 513601100, 513829200, 514057350, 514285550, 514513800, 514742100, 514970450, 515198850, 515427300, 515655800, 515884350, 516112950, 516341600, 516570300, 516799050, 517027850, 517256700, 517485600, 517714550, 517943550, 518172600, 518401700, 518630850, 518860050, 519089300, 519318600, 519547950, 519777350, 520006800, 520236300, 520465850, 520695450, 520925100, 521154800, 521384550, 521614350, 521844200, 522074100, 522304050, 522534050, 522764100, 522994200, 523224350, 523454550, 523684800, 523915100, 524145450, 524375850, 524606300, 524836800, 525067350, 525297950, 525528600, 525759300, 525990050, 526220850, 526451700, 526682600, 526913550, 527144550, 527375600, 527606700, 527837850, 528069050, 528300300, 528531600, 528762950, 528994350, 529225800, 529457300, 529688850, 529920450, 530152100, 530383800, 530615550, 530847350, 531079200, 531311100, 531543050, 531775050, 532007100, 532239200, 532471350, 532703550, 532935800, 533168100, 533400450, 533632850, 533865300, 534097800, 534330350, 534562950, 534795600, 535028300, 535261050, 535493850, 535726700, 535959600, 536192550, 536425550, 536658600, 536891700, 537124850, 537358050, 537591300, 537824600, 538057950, 538291350, 538524800, 538758300, 538991850, 539225450, 539459100, 539692800, 539926550, 540160350, 540394200, 540628100, 540862050, 541096050, 541330100, 541564200, 541798350, 542032550, 542266800, 542501100, 542735450, 542969850, 543204300, 543438800, 543673350, 543907950, 544142600, 544377300, 544612050, 544846850, 545081700, 545316600, 545551550, 545786550, 546021600, 546256700, 546491850, 546727050, 546962300, 547197600, 547432950, 547668350, 547903800, 548139300, 548374850, 548610450, 548846100, 549081800, 549317550, 549553350, 549789200, 550025100, 550261050, 550497050, 550733100, 550969200, 551205350, 551441550, 551677800, 551914100, 552150450, 552386850, 552623300, 552859800, 553096350, 553332950, 553569600, 553806300, 554043050, 554279850, 554516700, 554753600, 554990550, 555227550, 555464600, 555701700, 555938850, 556176050, 556413300, 556650600, 556887950, 557125350, 557362800, 557600300, 557837850, 558075450, 558313100, 558550800, 558788550, 559026350, 559264200, 559502100, 559740050, 559978050, 560216100, 560454200, 560692350, 560930550, 561168800, 561407100, 561645450, 561883850, 562122300, 562360800, 562599350, 562837950, 563076600, 563315300, 563554050, 563792850, 564031700, 564270600, 564509550, 564748550, 564987600, 565226700, 565465850, 565705050, 565944300, 566183600, 566422950, 566662350, 566901800, 567141300, 567380850, 567620450, 567860100, 568099800, 568339550, 568579350, 568819200, 569059100, 569299050, 569539050, 569779100, 570019200, 570259350, 570499550, 570739800, 570980100, 571220450, 571460850, 571701300, 571941800, 572182350, 572422950, 572663600, 572904300, 573145050, 573385850, 573626700, 573867600, 574108550, 574349550, 574590600, 574831700, 575072850, 575314050, 575555300, 575796600, 576037950, 576279350, 576520800, 576762300, 577003850, 577245450, 577487100, 577728800, 577970550, 578212350, 578454200, 578696100, 578938050, 579180050, 579422100, 579664200, 579906350, 580148550, 580390800, 580633100, 580875450, 581117850, 581360300, 581602800, 581845350, 582087950, 582330600, 582573300, 582816050, 583058850, 583301700, 583544600, 583787550, 584030550, 584273600, 584516700, 584759850, 585003050, 585246300, 585489600, 585732950, 585976350, 586219800, 586463300, 586706850, 586950450, 587194100, 587437800, 587681550, 587925350, 588169200, 588413100, 588657050, 588901050, 589145100, 589389200, 589633350, 589877550, 590121800, 590366100, 590610450, 590854850, 591099300, 591343800, 591588350, 591832950, 592077600, 592322300, 592567050, 592811850, 593056700, 593301600, 593546550, 593791550, 594036600, 594281700, 594526850, 594772050, 595017300, 595262600, 595507950, 595753350, 595998800, 596244300, 596489850, 596735450, 596981100, 597226800, 597472550, 597718350, 597964200, 598210100, 598456050, 598702050, 598948100, 599194200, 599440350, 599686550, 599932800, 600179100, 600425450, 600671850, 600918300, 601164800, 601411350, 601657950, 601904600, 602151300, 602398050, 602644850, 602891700, 603138600, 603385550, 603632550, 603879600, 604126700, 604373850, 604621050, 604868300, 605115600, 605362950, 605610350, 605857800, 606105300, 606352850, 606600450, 606848100, 607095800, 607343550, 607591350, 607839200, 608087100, 608335050, 608583050, 608831100, 609079200, 609327350, 609575550, 609823800, 610072100, 610320450, 610568850, 610817300, 611065800, 611314350, 611562950, 611811600, 612060300, 612309050, 612557850, 612806700, 613055600, 613304550, 613553550, 613802600, 614051700, 614300850, 614550050, 614799300, 615048600, 615297950, 615547350, 615796800, 616046300, 616295850, 616545450, 616795100, 617044800, 617294550, 617544350, 617794200, 618044100, 618294050, 618544050, 618794100, 619044200, 619294350, 619544550, 619794800, 620045100, 620295450, 620545850, 620796300, 621046800, 621297350, 621547950, 621798600, 622049300, 622300050, 622550850, 622801700, 623052600, 623303550, 623554550, 623805600, 624056700, 624307850, 624559050, 624810300, 625061600, 625312950, 625564350, 625815800, 626067300, 626318850, 626570450, 626822100, 627073800, 627325550, 627577350, 627829200, 628081100, 628333050, 628585050, 628837100, 629089200, 629341350, 629593550, 629845800, 630098100, 630350450, 630602850, 630855300, 631107800, 631360350, 631612950, 631865600, 632118300, 632371050, 632623850, 632876700, 633129600, 633382550, 633635550, 633888600, 634141700, 634394850, 634648050, 634901300, 635154600, 635407950, 635661350, 635914800, 636168300, 636421850, 636675450, 636929100, 637182800, 637436550, 637690350, 637944200, 638198100, 638452050, 638706050, 638960100, 639214200, 639468350, 639722550, 639976800, 640231100, 640485450, 640739850, 640994300, 641248800, 641503350, 641757950, 642012600, 642267300, 642522050, 642776850, 643031700, 643286600, 643541550, 643796550, 644051600, 644306700, 644561850, 644817050, 645072300, 645327600, 645582950, 645838350, 646093800, 646349300, 646604850, 646860450, 647116100, 647371800, 647627550, 647883350, 648139200, 648395100, 648651050, 648907050, 649163100, 649419200, 649675350, 649931550, 650187800, 650444100, 650700450, 650956850, 651213300, 651469800, 651726350, 651982950, 652239600, 652496300, 652753050, 653009850, 653266700, 653523600, 653780550, 654037550, 654294600, 654551700, 654808850, 655066050, 655323300, 655580600, 655837950, 656095350, 656352800, 656610300, 656867850, 657125450, 657383100, 657640800, 657898550, 658156350, 658414200, 658672100, 658930050, 659188050, 659446100, 659704200, 659962350, 660220550, 660478800, 660737100, 660995450, 661253850, 661512300, 661770800, 662029350, 662287950, 662546600, 662805300, 663064050, 663322850, 663581700, 663840600, 664099550, 664358550, 664617600, 664876700, 665135850, 665395050, 665654300, 665913600, 666172950, 666432350, 666691800, 666951300, 667210850, 667470450, 667730100, 667989800, 668249550, 668509350, 668769200, 669029100, 669289050, 669549050, 669809100, 670069200, 670329350, 670589550, 670849800, 671110100, 671370450, 671630850, 671891300, 672151800, 672412350, 672672950, 672933600, 673194300, 673455050, 673715850, 673976700, 674237600, 674498550, 674759550, 675020600, 675281700, 675542850, 675804050, 676065300, 676326600, 676587950, 676849350, 677110800, 677372300, 677633850, 677895450, 678157100, 678418800, 678680550, 678942350, 679204200, 679466100, 679728050, 679990050, 680252100, 680514200, 680776350, 681038550, 681300800, 681563100, 681825450, 682087850, 682350300, 682612800, 682875350, 683137950, 683400600, 683663300, 683926050, 684188850, 684451700, 684714600, 684977550, 685240550, 685503600, 685766700, 686029850, 686293050, 686556300, 686819600, 687082950, 687346350, 687609800, 687873300, 688136850, 688400450, 688664100, 688927800, 689191550, 689455350, 689719200, 689983100, 690247050, 690511050, 690775100, 691039200, 691303350, 691567550, 691831800, 692096100, 692360450, 692624850, 692889300, 693153800, 693418350, 693682950, 693947600, 694212300, 694477050, 694741850, 695006700, 695271600, 695536550, 695801550, 696066600, 696331700, 696596850, 696862050, 697127300, 697392600, 697657950, 697923350, 698188800, 698454300, 698719850, 698985450, 699251100, 699516800, 699782550, 700048350, 700314200, 700580100, 700846050, 701112050, 701378100, 701644200, 701910350, 702176550, 702442800, 702709100, 702975450, 703241850, 703508300, 703774800, 704041350, 704307950, 704574600, 704841300, 705108050, 705374850, 705641700, 705908600, 706175550, 706442550, 706709600, 706976700, 707243850, 707511050, 707778300, 708045600, 708312950, 708580350, 708847800, 709115300, 709382850, 709650450, 709918100, 710185800, 710453550, 710721350, 710989200, 711257100, 711525050, 711793050, 712061100, 712329200, 712597350, 712865550, 713133800, 713402100, 713670450, 713938850, 714207300, 714475800, 714744350, 715012950, 715281600, 715550300, 715819050, 716087850, 716356700, 716625600, 716894550, 717163550, 717432600, 717701700, 717970850, 718240050, 718509300, 718778600, 719047950, 719317350, 719586800, 719856300, 720125850, 720395450, 720665100, 720934800, 721204550, 721474350, 721744200, 722014100, 722284050, 722554050, 722824100, 723094200, 723364350, 723634550, 723904800, 724175100, 724445450, 724715850, 724986300, 725256800, 725527350, 725797950, 726068600, 726339300, 726610050, 726880850, 727151700, 727422600, 727693550, 727964550, 728235600, 728506700, 728777850, 729049050, 729320300, 729591600, 729862950, 730134350, 730405800, 730677300, 730948850, 731220450, 731492100, 731763800, 732035550, 732307350, 732579200, 732851100, 733123050, 733395050, 733667100, 733939200, 734211350, 734483550, 734755800, 735028100, 735300450, 735572850, 735845300, 736117800, 736390350, 736662950, 736935600, 737208300, 737481050, 737753850, 738026700, 738299600, 738572550, 738845550, 739118600, 739391700, 739664850, 739938050, 740211300, 740484600, 740757950, 741031350, 741304800, 741578300, 741851850, 742125450, 742399100, 742672800, 742946550, 743220350, 743494200, 743768100, 744042050, 744316050, 744590100, 744864200, 745138350, 745412550, 745686800, 745961100, 746235450, 746509850, 746784300, 747058800, 747333350, 747607950, 747882600, 748157300, 748432050, 748706850, 748981700, 749256600, 749531550, 749806550, 750081600, 750356700, 750631850, 750907050, 751182300, 751457600, 751732950, 752008350, 752283800, 752559300, 752834850, 753110450, 753386100, 753661800, 753937550, 754213350, 754489200, 754765100, 755041050, 755317050, 755593100, 755869200, 756145350, 756421550, 756697800, 756974100, 757250450, 757526850, 757803300, 758079800, 758356350, 758632950, 758909600, 759186300, 759463050, 759739850, 760016700, 760293600, 760570550, 760847550, 761124600, 761401700, 761678850, 761956050, 762233300, 762510600, 762787950, 763065350, 763342800, 763620300, 763897850, 764175450, 764453100, 764730800, 765008550, 765286350, 765564200, 765842100, 766120050, 766398050, 766676100, 766954200, 767232350, 767510550, 767788800, 768067100, 768345450, 768623850, 768902300, 769180800, 769459350, 769737950, 770016600, 770295300, 770574050, 770852850, 771131700, 771410600, 771689550, 771968550, 772247600, 772526700, 772805850, 773085050, 773364300, 773643600, 773922950, 774202350, 774481800, 774761300, 775040850, 775320450, 775600100, 775879800, 776159550, 776439350, 776719200, 776999100, 777279050, 777559050, 777839100, 778119200, 778399350, 778679550, 778959800, 779240100, 779520450, 779800850, 780081300, 780361800, 780642350, 780922950, 781203600, 781484300, 781765050, 782045850, 782326700, 782607600, 782888550, 783169550, 783450600, 783731700, 784012850, 784294050, 784575300, 784856600, 785137950, 785419350, 785700800, 785982300, 786263850, 786545450, 786827100, 787108800, 787390550, 787672350, 787954200, 788236100, 788518050, 788800050, 789082100, 789364200, 789646350, 789928550, 790210800, 790493100, 790775450, 791057850, 791340300, 791622800, 791905350, 792187950, 792470600, 792753300, 793036050, 793318850, 793601700, 793884600, 794167550, 794450550, 794733600, 795016700, 795299850, 795583050, 795866300, 796149600, 796432950, 796716350, 796999800, 797283300, 797566850, 797850450, 798134100, 798417800, 798701550, 798985350, 799269200, 799553100, 799837050, 800121050, 800405100, 800689200, 800973350, 801257550, 801541800, 801826100, 802110450, 802394850, 802679300, 802963800, 803248350, 803532950, 803817600, 804102300, 804387050, 804671850, 804956700, 805241600, 805526550, 805811550, 806096600, 806381700, 806666850, 806952050, 807237300, 807522600, 807807950, 808093350, 808378800, 808664300, 808949850, 809235450, 809521100, 809806800, 810092550, 810378350, 810664200, 810950100, 811236050, 811522050, 811808100, 812094200, 812380350, 812666550, 812952800, 813239100, 813525450, 813811850, 814098300, 814384800, 814671350, 814957950, 815244600, 815531300, 815818050, 816104850, 816391700, 816678600, 816965550, 817252550, 817539600, 817826700, 818113850, 818401050, 818688300, 818975600, 819262950, 819550350, 819837800, 820125300, 820412850, 820700450, 820988100, 821275800, 821563550, 821851350, 822139200, 822427100, 822715050, 823003050, 823291100, 823579200, 823867350, 824155550, 824443800, 824732100, 825020450, 825308850, 825597300, 825885800, 826174350, 826462950, 826751600, 827040300, 827329050, 827617850, 827906700, 828195600, 828484550, 828773550, 829062600, 829351700, 829640850, 829930050, 830219300, 830508600, 830797950, 831087350, 831376800, 831666300, 831955850, 832245450, 832535100, 832824800, 833114550, 833404350, 833694200, 833984100, 834274050, 834564050, 834854100, 835144200, 835434350, 835724550, 836014800, 836305100, 836595450, 836885850, 837176300, 837466800, 837757350, 838047950, 838338600, 838629300, 838920050, 839210850, 839501700, 839792600, 840083550, 840374550, 840665600, 840956700, 841247850, 841539050, 841830300, 842121600, 842412950, 842704350, 842995800, 843287300, 843578850, 843870450, 844162100, 844453800, 844745550, 845037350, 845329200, 845621100, 845913050, 846205050, 846497100, 846789200, 847081350, 847373550, 847665800, 847958100, 848250450, 848542850, 848835300, 849127800, 849420350, 849712950, 850005600, 850298300, 850591050, 850883850, 851176700, 851469600, 851762550, 852055550, 852348600, 852641700, 852934850, 853228050, 853521300, 853814600, 854107950, 854401350, 854694800, 854988300, 855281850, 855575450, 855869100, 856162800, 856456550, 856750350, 857044200, 857338100, 857632050, 857926050, 858220100, 858514200, 858808350, 859102550, 859396800, 859691100, 859985450, 860279850, 860574300, 860868800, 861163350, 861457950, 861752600, 862047300, 862342050, 862636850, 862931700, 863226600, 863521550, 863816550, 864111600, 864406700, 864701850, 864997050, 865292300, 865587600, 865882950, 866178350, 866473800, 866769300, 867064850, 867360450, 867656100, 867951800, 868247550, 868543350, 868839200, 869135100, 869431050, 869727050, 870023100, 870319200, 870615350, 870911550, 871207800, 871504100, 871800450, 872096850, 872393300, 872689800, 872986350, 873282950, 873579600, 873876300, 874173050, 874469850, 874766700, 875063600, 875360550, 875657550, 875954600, 876251700, 876548850, 876846050, 877143300, 877440600, 877737950, 878035350, 878332800, 878630300, 878927850, 879225450, 879523100, 879820800, 880118550, 880416350, 880714200, 881012100, 881310050, 881608050, 881906100, 882204200, 882502350, 882800550, 883098800, 883397100, 883695450, 883993850, 884292300, 884590800, 884889350, 885187950, 885486600, 885785300, 886084050, 886382850, 886681700, 886980600, 887279550, 887578550, 887877600, 888176700, 888475850, 888775050, 889074300, 889373600, 889672950, 889972350, 890271800, 890571300, 890870850, 891170450, 891470100, 891769800, 892069550, 892369350, 892669200, 892969100, 893269050, 893569050, 893869100, 894169200, 894469350, 894769550, 895069800, 895370100, 895670450, 895970850, 896271300, 896571800, 896872350, 897172950, 897473600, 897774300, 898075050, 898375850, 898676700, 898977600, 899278550, 899579550, 899880600, 900181700, 900482850, 900784050, 901085300, 901386600, 901687950, 901989350, 902290800, 902592300, 902893850, 903195450, 903497100, 903798800, 904100550, 904402350, 904704200, 905006100, 905308050, 905610050, 905912100, 906214200, 906516350, 906818550, 907120800, 907423100, 907725450, 908027850, 908330300, 908632800, 908935350, 909237950, 909540600, 909843300, 910146050, 910448850, 910751700, 911054600, 911357550, 911660550, 911963600, 912266700, 912569850, 912873050, 913176300, 913479600, 913782950, 914086350, 914389800, 914693300, 914996850, 915300450, 915604100, 915907800, 916211550, 916515350, 916819200, 917123100, 917427050, 917731050, 918035100, 918339200, 918643350, 918947550, 919251800, 919556100, 919860450, 920164850, 920469300, 920773800, 921078350, 921382950, 921687600, 921992300, 922297050, 922601850, 922906700, 923211600, 923516550, 923821550, 924126600, 924431700, 924736850, 925042050, 925347300, 925652600, 925957950, 926263350, 926568800, 926874300, 927179850, 927485450, 927791100, 928096800, 928402550, 928708350, 929014200, 929320100, 929626050, 929932050, 930238100, 930544200, 930850350, 931156550, 931462800, 931769100, 932075450, 932381850, 932688300, 932994800, 933301350, 933607950, 933914600, 934221300, 934528050, 934834850, 935141700, 935448600, 935755550, 936062550, 936369600, 936676700, 936983850, 937291050, 937598300, 937905600, 938212950, 938520350, 938827800, 939135300, 939442850, 939750450, 940058100, 940365800, 940673550, 940981350, 941289200, 941597100, 941905050, 942213050, 942521100, 942829200, 943137350, 943445550, 943753800, 944062100, 944370450, 944678850, 944987300, 945295800, 945604350, 945912950, 946221600, 946530300, 946839050, 947147850, 947456700, 947765600, 948074550, 948383550, 948692600, 949001700, 949310850, 949620050, 949929300, 950238600, 950547950, 950857350, 951166800, 951476300, 951785850, 952095450, 952405100, 952714800, 953024550, 953334350, 953644200, 953954100, 954264050, 954574050, 954884100, 955194200, 955504350, 955814550, 956124800, 956435100, 956745450, 957055850, 957366300, 957676800, 957987350, 958297950, 958608600, 958919300, 959230050, 959540850, 959851700, 960162600, 960473550, 960784550, 961095600, 961406700, 961717850, 962029050, 962340300, 962651600, 962962950, 963274350, 963585800, 963897300, 964208850, 964520450, 964832100, 965143800, 965455550, 965767350, 966079200, 966391100, 966703050, 967015050, 967327100, 967639200, 967951350, 968263550, 968575800, 968888100, 969200450, 969512850, 969825300, 970137800, 970450350, 970762950, 971075600, 971388300, 971701050, 972013850, 972326700, 972639600, 972952550, 973265550, 973578600, 973891700, 974204850, 974518050, 974831300, 975144600, 975457950, 975771350, 976084800, 976398300, 976711850, 977025450, 977339100, 977652800, 977966550, 978280350, 978594200, 978908100, 979222050, 979536050, 979850100, 980164200, 980478350, 980792550, 981106800, 981421100, 981735450, 982049850, 982364300, 982678800, 982993350, 983307950, 983622600, 983937300, 984252050, 984566850, 984881700, 985196600, 985511550, 985826550, 986141600, 986456700, 986771850, 987087050, 987402300, 987717600, 988032950, 988348350, 988663800, 988979300, 989294850, 989610450, 989926100, 990241800, 990557550, 990873350, 991189200, 991505100, 991821050, 992137050, 992453100, 992769200, 993085350, 993401550, 993717800, 994034100, 994350450, 994666850, 994983300, 995299800, 995616350, 995932950, 996249600, 996566300, 996883050, 997199850, 997516700, 997833600, 998150550, 998467550, 998784600, 999101700, 999418850, 999736050, 1000053300, 1000370600, 1000687950, 1001005350, 1001322800, 1001640300, 1001957850, 1002275450, 1002593100, 1002910800, 1003228550, 1003546350, 1003864200, 1004182100, 1004500050, 1004818050, 1005136100, 1005454200, 1005772350, 1006090550, 1006408800, 1006727100, 1007045450, 1007363850, 1007682300, 1008000800, 1008319350, 1008637950, 1008956600, 1009275300, 1009594050, 1009912850, 1010231700, 1010550600, 1010869550, 1011188550, 1011507600, 1011826700, 1012145850, 1012465050, 1012784300, 1013103600, 1013422950, 1013742350, 1014061800, 1014381300, 1014700850, 1015020450, 1015340100, 1015659800, 1015979550, 1016299350, 1016619200, 1016939100, 1017259050, 1017579050, 1017899100, 1018219200, 1018539350, 1018859550, 1019179800, 1019500100, 1019820450, 1020140850, 1020461300, 1020781800, 1021102350, 1021422950, 1021743600, 1022064300, 1022385050, 1022705850, 1023026700, 1023347600, 1023668550, 1023989550, 1024310600, 1024631700, 1024952850, 1025274050, 1025595300, 1025916600, 1026237950, 1026559350, 1026880800, 1027202300, 1027523850, 1027845450, 1028167100, 1028488800, 1028810550, 1029132350, 1029454200, 1029776100, 1030098050, 1030420050, 1030742100, 1031064200, 1031386350, 1031708550, 1032030800, 1032353100, 1032675450, 1032997850, 1033320300, 1033642800, 1033965350, 1034287950, 1034610600, 1034933300, 1035256050, 1035578850, 1035901700, 1036224600, 1036547550, 1036870550, 1037193600, 1037516700, 1037839850, 1038163050, 1038486300, 1038809600, 1039132950, 1039456350, 1039779800, 1040103300, 1040426850, 1040750450, 1041074100, 1041397800, 1041721550, 1042045350, 1042369200, 1042693100, 1043017050, 1043341050, 1043665100, 1043989200, 1044313350, 1044637550, 1044961800, 1045286100, 1045610450, 1045934850, 1046259300, 1046583800, 1046908350, 1047232950, 1047557600, 1047882300, 1048207050, 1048531850, 1048856700, 1049181600, 1049506550, 1049831550, 1050156600, 1050481700, 1050806850, 1051132050, 1051457300, 1051782600, 1052107950, 1052433350, 1052758800, 1053084300, 1053409850, 1053735450, 1054061100, 1054386800, 1054712550, 1055038350, 1055364200, 1055690100, 1056016050, 1056342050, 1056668100, 1056994200, 1057320350, 1057646550, 1057972800, 1058299100, 1058625450, 1058951850, 1059278300, 1059604800, 1059931350, 1060257950, 1060584600, 1060911300, 1061238050, 1061564850, 1061891700, 1062218600, 1062545550, 1062872550, 1063199600, 1063526700, 1063853850, 1064181050, 1064508300, 1064835600, 1065162950, 1065490350, 1065817800, 1066145300, 1066472850, 1066800450, 1067128100, 1067455800, 1067783550, 1068111350, 1068439200, 1068767100, 1069095050, 1069423050, 1069751100, 1070079200, 1070407350, 1070735550, 1071063800, 1071392100, 1071720450, 1072048850, 1072377300, 1072705800, 1073034350, 1073362950, 1073691600, 1074020300, 1074349050, 1074677850, 1075006700, 1075335600, 1075664550, 1075993550, 1076322600, 1076651700, 1076980850, 1077310050, 1077639300, 1077968600, 1078297950, 1078627350, 1078956800, 1079286300, 1079615850, 1079945450, 1080275100, 1080604800, 1080934550, 1081264350, 1081594200, 1081924100, 1082254050, 1082584050, 1082914100, 1083244200, 1083574350, 1083904550, 1084234800, 1084565100, 1084895450, 1085225850, 1085556300, 1085886800, 1086217350, 1086547950, 1086878600, 1087209300, 1087540050, 1087870850, 1088201700, 1088532600, 1088863550, 1089194550, 1089525600, 1089856700, 1090187850, 1090519050, 1090850300, 1091181600, 1091512950, 1091844350, 1092175800, 1092507300, 1092838850, 1093170450, 1093502100, 1093833800, 1094165550, 1094497350, 1094829200, 1095161100, 1095493050, 1095825050, 1096157100, 1096489200, 1096821350, 1097153550, 1097485800, 1097818100, 1098150450, 1098482850, 1098815300, 1099147800, 1099480350, 1099812950, 1100145600, 1100478300, 1100811050, 1101143850, 1101476700, 1101809600, 1102142550, 1102475550, 1102808600, 1103141700, 1103474850, 1103808050, 1104141300, 1104474600, 1104807950, 1105141350, 1105474800, 1105808300, 1106141850, 1106475450, 1106809100, 1107142800, 1107476550, 1107810350, 1108144200, 1108478100, 1108812050, 1109146050, 1109480100, 1109814200, 1110148350, 1110482550, 1110816800, 1111151100, 1111485450, 1111819850, 1112154300, 1112488800, 1112823350, 1113157950, 1113492600, 1113827300, 1114162050, 1114496850, 1114831700, 1115166600, 1115501550, 1115836550, 1116171600, 1116506700, 1116841850, 1117177050, 1117512300, 1117847600, 1118182950, 1118518350, 1118853800, 1119189300, 1119524850, 1119860450, 1120196100, 1120531800, 1120867550, 1121203350, 1121539200, 1121875100, 1122211050, 1122547050, 1122883100, 1123219200, 1123555350, 1123891550, 1124227800, 1124564100, 1124900450, 1125236850, 1125573300, 1125909800, 1126246350, 1126582950, 1126919600, 1127256300, 1127593050, 1127929850, 1128266700, 1128603600, 1128940550, 1129277550, 1129614600, 1129951700, 1130288850, 1130626050, 1130963300, 1131300600, 1131637950, 1131975350, 1132312800, 1132650300, 1132987850, 1133325450, 1133663100, 1134000800, 1134338550, 1134676350, 1135014200, 1135352100, 1135690050, 1136028050, 1136366100, 1136704200, 1137042350, 1137380550, 1137718800, 1138057100, 1138395450, 1138733850, 1139072300, 1139410800, 1139749350, 1140087950, 1140426600, 1140765300, 1141104050, 1141442850, 1141781700, 1142120600, 1142459550, 1142798550, 1143137600, 1143476700, 1143815850, 1144155050, 1144494300, 1144833600, 1145172950, 1145512350, 1145851800, 1146191300, 1146530850, 1146870450, 1147210100, 1147549800, 1147889550, 1148229350, 1148569200, 1148909100, 1149249050, 1149589050, 1149929100, 1150269200, 1150609350, 1150949550, 1151289800, 1151630100, 1151970450, 1152310850, 1152651300, 1152991800, 1153332350, 1153672950, 1154013600, 1154354300, 1154695050, 1155035850, 1155376700, 1155717600, 1156058550, 1156399550, 1156740600, 1157081700, 1157422850, 1157764050, 1158105300, 1158446600, 1158787950, 1159129350, 1159470800, 1159812300, 1160153850, 1160495450, 1160837100, 1161178800, 1161520550, 1161862350, 1162204200, 1162546100, 1162888050, 1163230050, 1163572100, 1163914200, 1164256350, 1164598550, 1164940800, 1165283100, 1165625450, 1165967850, 1166310300, 1166652800, 1166995350, 1167337950, 1167680600, 1168023300, 1168366050, 1168708850, 1169051700, 1169394600, 1169737550, 1170080550, 1170423600, 1170766700, 1171109850, 1171453050, 1171796300, 1172139600, 1172482950, 1172826350, 1173169800, 1173513300, 1173856850, 1174200450, 1174544100, 1174887800, 1175231550, 1175575350, 1175919200, 1176263100, 1176607050, 1176951050, 1177295100, 1177639200, 1177983350, 1178327550, 1178671800, 1179016100, 1179360450, 1179704850, 1180049300, 1180393800, 1180738350, 1181082950, 1181427600, 1181772300, 1182117050, 1182461850, 1182806700, 1183151600, 1183496550, 1183841550, 1184186600, 1184531700, 1184876850, 1185222050, 1185567300, 1185912600, 1186257950, 1186603350, 1186948800, 1187294300, 1187639850, 1187985450, 1188331100, 1188676800, 1189022550, 1189368350, 1189714200, 1190060100, 1190406050, 1190752050, 1191098100, 1191444200, 1191790350, 1192136550, 1192482800, 1192829100, 1193175450, 1193521850, 1193868300, 1194214800, 1194561350, 1194907950, 1195254600, 1195601300, 1195948050, 1196294850, 1196641700, 1196988600, 1197335550, 1197682550, 1198029600, 1198376700, 1198723850, 1199071050, 1199418300, 1199765600, 1200112950, 1200460350, 1200807800, 1201155300, 1201502850, 1201850450, 1202198100, 1202545800, 1202893550, 1203241350, 1203589200, 1203937100, 1204285050, 1204633050, 1204981100, 1205329200, 1205677350, 1206025550, 1206373800, 1206722100, 1207070450, 1207418850, 1207767300, 1208115800, 1208464350, 1208812950, 1209161600, 1209510300, 1209859050, 1210207850, 1210556700, 1210905600, 1211254550, 1211603550, 1211952600, 1212301700, 1212650850, 1213000050, 1213349300, 1213698600, 1214047950, 1214397350, 1214746800, 1215096300, 1215445850, 1215795450, 1216145100, 1216494800, 1216844550, 1217194350, 1217544200, 1217894100, 1218244050, 1218594050, 1218944100, 1219294200, 1219644350, 1219994550, 1220344800, 1220695100, 1221045450, 1221395850, 1221746300, 1222096800, 1222447350, 1222797950, 1223148600, 1223499300, 1223850050, 1224200850, 1224551700, 1224902600, 1225253550, 1225604550, 1225955600, 1226306700, 1226657850, 1227009050, 1227360300, 1227711600, 1228062950, 1228414350, 1228765800, 1229117300, 1229468850, 1229820450, 1230172100, 1230523800, 1230875550, 1231227350, 1231579200, 1231931100, 1232283050, 1232635050, 1232987100, 1233339200, 1233691350, 1234043550, 1234395800, 1234748100, 1235100450, 1235452850, 1235805300, 1236157800, 1236510350, 1236862950, 1237215600, 1237568300, 1237921050, 1238273850, 1238626700, 1238979600, 1239332550, 1239685550, 1240038600, 1240391700, 1240744850, 1241098050, 1241451300, 1241804600, 1242157950, 1242511350, 1242864800, 1243218300, 1243571850, 1243925450, 1244279100, 1244632800, 1244986550, 1245340350, 1245694200, 1246048100, 1246402050, 1246756050, 1247110100, 1247464200, 1247818350, 1248172550, 1248526800, 1248881100, 1249235450, 1249589850, 1249944300, 1250298800, 1250653350, 1251007950, 1251362600, 1251717300, 1252072050, 1252426850, 1252781700, 1253136600, 1253491550, 1253846550, 1254201600, 1254556700, 1254911850, 1255267050, 1255622300, 1255977600, 1256332950, 1256688350, 1257043800, 1257399300, 1257754850, 1258110450, 1258466100, 1258821800, 1259177550, 1259533350, 1259889200, 1260245100, 1260601050, 1260957050, 1261313100, 1261669200, 1262025350, 1262381550, 1262737800, 1263094100, 1263450450, 1263806850, 1264163300, 1264519800, 1264876350, 1265232950, 1265589600, 1265946300, 1266303050, 1266659850, 1267016700, 1267373600, 1267730550, 1268087550, 1268444600, 1268801700, 1269158850, 1269516050, 1269873300, 1270230600, 1270587950, 1270945350, 1271302800, 1271660300, 1272017850, 1272375450, 1272733100, 1273090800, 1273448550, 1273806350, 1274164200, 1274522100, 1274880050, 1275238050, 1275596100, 1275954200, 1276312350, 1276670550, 1277028800, 1277387100, 1277745450, 1278103850, 1278462300, 1278820800, 1279179350, 1279537950, 1279896600, 1280255300, 1280614050, 1280972850, 1281331700, 1281690600, 1282049550, 1282408550, 1282767600, 1283126700, 1283485850, 1283845050, 1284204300, 1284563600, 1284922950, 1285282350, 1285641800, 1286001300, 1286360850, 1286720450, 1287080100, 1287439800, 1287799550, 1288159350, 1288519200, 1288879100, 1289239050, 1289599050, 1289959100, 1290319200, 1290679350, 1291039550, 1291399800, 1291760100, 1292120450, 1292480850, 1292841300, 1293201800, 1293562350, 1293922950, 1294283600, 1294644300, 1295005050, 1295365850, 1295726700, 1296087600, 1296448550, 1296809550, 1297170600, 1297531700, 1297892850, 1298254050, 1298615300, 1298976600, 1299337950, 1299699350, 1300060800, 1300422300, 1300783850, 1301145450, 1301507100, 1301868800, 1302230550, 1302592350, 1302954200, 1303316100, 1303678050, 1304040050, 1304402100, 1304764200, 1305126350, 1305488550, 1305850800, 1306213100, 1306575450, 1306937850, 1307300300, 1307662800, 1308025350, 1308387950, 1308750600, 1309113300, 1309476050, 1309838850, 1310201700, 1310564600, 1310927550, 1311290550, 1311653600, 1312016700, 1312379850, 1312743050, 1313106300, 1313469600, 1313832950, 1314196350, 1314559800, 1314923300, 1315286850, 1315650450, 1316014100, 1316377800, 1316741550, 1317105350, 1317469200, 1317833100, 1318197050, 1318561050, 1318925100, 1319289200, 1319653350, 1320017550, 1320381800, 1320746100, 1321110450, 1321474850, 1321839300, 1322203800, 1322568350, 1322932950, 1323297600, 1323662300, 1324027050, 1324391850, 1324756700, 1325121600, 1325486550, 1325851550, 1326216600, 1326581700, 1326946850, 1327312050, 1327677300, 1328042600, 1328407950, 1328773350, 1329138800, 1329504300, 1329869850, 1330235450, 1330601100, 1330966800, 1331332550, 1331698350, 1332064200, 1332430100, 1332796050, 1333162050, 1333528100, 1333894200, 1334260350, 1334626550, 1334992800, 1335359100, 1335725450, 1336091850, 1336458300, 1336824800, 1337191350, 1337557950, 1337924600, 1338291300, 1338658050, 1339024850, 1339391700, 1339758600, 1340125550, 1340492550, 1340859600, 1341226700, 1341593850, 1341961050, 1342328300, 1342695600, 1343062950, 1343430350, 1343797800, 1344165300, 1344532850, 1344900450, 1345268100, 1345635800, 1346003550, 1346371350, 1346739200, 1347107100, 1347475050, 1347843050, 1348211100, 1348579200, 1348947350, 1349315550, 1349683800, 1350052100, 1350420450, 1350788850, 1351157300, 1351525800, 1351894350, 1352262950, 1352631600, 1353000300, 1353369050, 1353737850, 1354106700, 1354475600, 1354844550, 1355213550, 1355582600, 1355951700, 1356320850, 1356690050, 1357059300, 1357428600, 1357797950, 1358167350, 1358536800, 1358906300, 1359275850, 1359645450, 1360015100, 1360384800, 1360754550, 1361124350, 1361494200, 1361864100, 1362234050, 1362604050, 1362974100, 1363344200, 1363714350, 1364084550, 1364454800, 1364825100, 1365195450, 1365565850, 1365936300, 1366306800, 1366677350, 1367047950, 1367418600, 1367789300, 1368160050, 1368530850, 1368901700, 1369272600, 1369643550, 1370014550, 1370385600, 1370756700, 1371127850, 1371499050, 1371870300, 1372241600, 1372612950, 1372984350, 1373355800, 1373727300, 1374098850, 1374470450, 1374842100, 1375213800, 1375585550, 1375957350, 1376329200, 1376701100, 1377073050, 1377445050, 1377817100, 1378189200, 1378561350, 1378933550, 1379305800, 1379678100, 1380050450, 1380422850, 1380795300, 1381167800, 1381540350, 1381912950, 1382285600, 1382658300, 1383031050, 1383403850, 1383776700, 1384149600, 1384522550, 1384895550, 1385268600, 1385641700, 1386014850, 1386388050, 1386761300, 1387134600, 1387507950, 1387881350, 1388254800, 1388628300, 1389001850, 1389375450, 1389749100, 1390122800, 1390496550, 1390870350, 1391244200, 1391618100, 1391992050, 1392366050, 1392740100, 1393114200, 1393488350, 1393862550, 1394236800, 1394611100, 1394985450, 1395359850, 1395734300, 1396108800, 1396483350, 1396857950, 1397232600, 1397607300, 1397982050, 1398356850, 1398731700, 1399106600, 1399481550, 1399856550, 1400231600, 1400606700, 1400981850, 1401357050, 1401732300, 1402107600, 1402482950, 1402858350, 1403233800, 1403609300, 1403984850, 1404360450, 1404736100, 1405111800, 1405487550, 1405863350, 1406239200, 1406615100, 1406991050, 1407367050, 1407743100, 1408119200, 1408495350, 1408871550, 1409247800, 1409624100, 1410000450, 1410376850, 1410753300, 1411129800, 1411506350, 1411882950, 1412259600, 1412636300, 1413013050, 1413389850, 1413766700, 1414143600, 1414520550, 1414897550, 1415274600, 1415651700, 1416028850, 1416406050, 1416783300, 1417160600, 1417537950, 1417915350, 1418292800, 1418670300, 1419047850, 1419425450, 1419803100, 1420180800, 1420558550, 1420936350, 1421314200, 1421692100, 1422070050, 1422448050, 1422826100, 1423204200, 1423582350, 1423960550, 1424338800, 1424717100, 1425095450, 1425473850, 1425852300, 1426230800, 1426609350, 1426987950, 1427366600, 1427745300, 1428124050, 1428502850, 1428881700, 1429260600, 1429639550, 1430018550, 1430397600, 1430776700, 1431155850, 1431535050, 1431914300, 1432293600, 1432672950, 1433052350, 1433431800, 1433811300, 1434190850, 1434570450, 1434950100, 1435329800, 1435709550, 1436089350, 1436469200, 1436849100, 1437229050, 1437609050, 1437989100, 1438369200, 1438749350, 1439129550, 1439509800, 1439890100, 1440270450, 1440650850, 1441031300, 1441411800, 1441792350, 1442172950, 1442553600, 1442934300, 1443315050, 1443695850, 1444076700, 1444457600, 1444838550, 1445219550, 1445600600, 1445981700, 1446362850, 1446744050, 1447125300, 1447506600, 1447887950, 1448269350, 1448650800, 1449032300, 1449413850, 1449795450, 1450177100, 1450558800, 1450940550, 1451322350, 1451704200, 1452086100, 1452468050, 1452850050, 1453232100, 1453614200, 1453996350, 1454378550, 1454760800, 1455143100, 1455525450, 1455907850, 1456290300, 1456672800, 1457055350, 1457437950, 1457820600, 1458203300, 1458586050, 1458968850, 1459351700, 1459734600, 1460117550, 1460500550, 1460883600, 1461266700, 1461649850, 1462033050, 1462416300, 1462799600, 1463182950, 1463566350, 1463949800, 1464333300, 1464716850, 1465100450, 1465484100, 1465867800, 1466251550, 1466635350, 1467019200, 1467403100, 1467787050, 1468171050, 1468555100, 1468939200, 1469323350, 1469707550, 1470091800, 1470476100, 1470860450, 1471244850, 1471629300, 1472013800, 1472398350, 1472782950, 1473167600, 1473552300, 1473937050, 1474321850, 1474706700, 1475091600, 1475476550, 1475861550, 1476246600, 1476631700, 1477016850, 1477402050, 1477787300, 1478172600, 1478557950, 1478943350, 1479328800, 1479714300, 1480099850, 1480485450, 1480871100, 1481256800, 1481642550, 1482028350, 1482414200, 1482800100, 1483186050, 1483572050, 1483958100, 1484344200, 1484730350, 1485116550, 1485502800, 1485889100, 1486275450, 1486661850, 1487048300, 1487434800, 1487821350, 1488207950, 1488594600, 1488981300, 1489368050, 1489754850, 1490141700, 1490528600, 1490915550, 1491302550, 1491689600, 1492076700, 1492463850, 1492851050, 1493238300, 1493625600, 1494012950, 1494400350, 1494787800, 1495175300, 1495562850, 1495950450, 1496338100, 1496725800, 1497113550, 1497501350, 1497889200, 1498277100, 1498665050, 1499053050, 1499441100, 1499829200, 1500217350, 1500605550, 1500993800, 1501382100, 1501770450, 1502158850, 1502547300, 1502935800, 1503324350, 1503712950, 1504101600, 1504490300, 1504879050, 1505267850, 1505656700, 1506045600, 1506434550, 1506823550, 1507212600, 1507601700, 1507990850, 1508380050, 1508769300, 1509158600, 1509547950, 1509937350, 1510326800, 1510716300, 1511105850, 1511495450, 1511885100, 1512274800, 1512664550, 1513054350, 1513444200, 1513834100, 1514224050, 1514614050, 1515004100, 1515394200, 1515784350, 1516174550, 1516564800, 1516955100, 1517345450, 1517735850, 1518126300, 1518516800, 1518907350, 1519297950, 1519688600, 1520079300, 1520470050, 1520860850, 1521251700, 1521642600, 1522033550, 1522424550, 1522815600, 1523206700, 1523597850, 1523989050, 1524380300, 1524771600, 1525162950, 1525554350, 1525945800, 1526337300, 1526728850, 1527120450, 1527512100, 1527903800, 1528295550, 1528687350, 1529079200, 1529471100, 1529863050, 1530255050, 1530647100, 1531039200, 1531431350, 1531823550, 1532215800, 1532608100, 1533000450, 1533392850, 1533785300, 1534177800, 1534570350, 1534962950, 1535355600, 1535748300, 1536141050, 1536533850, 1536926700, 1537319600, 1537712550, 1538105550, 1538498600, 1538891700, 1539284850, 1539678050, 1540071300, 1540464600, 1540857950, 1541251350, 1541644800, 1542038300, 1542431850, 1542825450, 1543219100, 1543612800, 1544006550, 1544400350, 1544794200, 1545188100, 1545582050, 1545976050, 1546370100, 1546764200, 1547158350, 1547552550, 1547946800, 1548341100, 1548735450, 1549129850, 1549524300, 1549918800, 1550313350, 1550707950, 1551102600, 1551497300, 1551892050, 1552286850, 1552681700, 1553076600, 1553471550, 1553866550, 1554261600, 1554656700, 1555051850, 1555447050, 1555842300, 1556237600, 1556632950, 1557028350, 1557423800, 1557819300, 1558214850, 1558610450, 1559006100, 1559401800, 1559797550, 1560193350, 1560589200, 1560985100, 1561381050, 1561777050, 1562173100, 1562569200, 1562965350, 1563361550, 1563757800, 1564154100, 1564550450, 1564946850, 1565343300, 1565739800, 1566136350, 1566532950, 1566929600, 1567326300, 1567723050, 1568119850, 1568516700, 1568913600, 1569310550, 1569707550, 1570104600, 1570501700, 1570898850, 1571296050, 1571693300, 1572090600, 1572487950, 1572885350, 1573282800, 1573680300, 1574077850, 1574475450, 1574873100, 1575270800, 1575668550, 1576066350, 1576464200, 1576862100, 1577260050, 1577658050, 1578056100, 1578454200, 1578852350, 1579250550, 1579648800, 1580047100, 1580445450, 1580843850, 1581242300, 1581640800, 1582039350, 1582437950, 1582836600, 1583235300, 1583634050, 1584032850, 1584431700, 1584830600, 1585229550, 1585628550, 1586027600, 1586426700, 1586825850, 1587225050, 1587624300, 1588023600, 1588422950, 1588822350, 1589221800, 1589621300, 1590020850, 1590420450, 1590820100, 1591219800, 1591619550, 1592019350, 1592419200, 1592819100, 1593219050, 1593619050, 1594019100, 1594419200, 1594819350, 1595219550, 1595619800, 1596020100, 1596420450, 1596820850, 1597221300, 1597621800, 1598022350, 1598422950, 1598823600, 1599224300, 1599625050, 1600025850, 1600426700, 1600827600, 1601228550, 1601629550, 1602030600, 1602431700, 1602832850, 1603234050, 1603635300, 1604036600, 1604437950, 1604839350, 1605240800, 1605642300, 1606043850, 1606445450, 1606847100, 1607248800, 1607650550, 1608052350, 1608454200, 1608856100, 1609258050, 1609660050, 1610062100, 1610464200, 1610866350, 1611268550, 1611670800, 1612073100, 1612475450, 1612877850, 1613280300, 1613682800, 1614085350, 1614487950, 1614890600, 1615293300, 1615696050, 1616098850, 1616501700, 1616904600, 1617307550, 1617710550, 1618113600, 1618516700, 1618919850, 1619323050, 1619726300, 1620129600, 1620532950, 1620936350, 1621339800, 1621743300, 1622146850, 1622550450, 1622954100, 1623357800, 1623761550, 1624165350, 1624569200, 1624973100, 1625377050, 1625781050, 1626185100, 1626589200, 1626993350, 1627397550, 1627801800, 1628206100, 1628610450, 1629014850, 1629419300, 1629823800, 1630228350, 1630632950, 1631037600, 1631442300, 1631847050, 1632251850, 1632656700, 1633061600, 1633466550, 1633871550, 1634276600, 1634681700, 1635086850, 1635492050, 1635897300, 1636302600, 1636707950, 1637113350, 1637518800, 1637924300, 1638329850, 1638735450, 1639141100, 1639546800, 1639952550, 1640358350, 1640764200, 1641170100, 1641576050, 1641982050, 1642388100, 1642794200, 1643200350, 1643606550, 1644012800, 1644419100, 1644825450, 1645231850, 1645638300, 1646044800, 1646451350, 1646857950, 1647264600, 1647671300, 1648078050, 1648484850, 1648891700, 1649298600, 1649705550, 1650112550, 1650519600, 1650926700, 1651333850, 1651741050, 1652148300, 1652555600, 1652962950, 1653370350, 1653777800, 1654185300, 1654592850, 1655000450, 1655408100, 1655815800, 1656223550, 1656631350, 1657039200, 1657447100, 1657855050, 1658263050, 1658671100, 1659079200, 1659487350, 1659895550, 1660303800, 1660712100, 1661120450, 1661528850, 1661937300, 1662345800, 1662754350, 1663162950, 1663571600, 1663980300, 1664389050, 1664797850, 1665206700, 1665615600, 1666024550, 1666433550, 1666842600, 1667251700, 1667660850, 1668070050, 1668479300, 1668888600, 1669297950, 1669707350, 1670116800, 1670526300, 1670935850, 1671345450, 1671755100, 1672164800, 1672574550, 1672984350, 1673394200, 1673804100, 1674214050, 1674624050, 1675034100, 1675444200, 1675854350, 1676264550, 1676674800, 1677085100, 1677495450, 1677905850, 1678316300, 1678726800, 1679137350, 1679547950, 1679958600, 1680369300, 1680780050, 1681190850, 1681601700, 1682012600, 1682423550, 1682834550, 1683245600, 1683656700, 1684067850, 1684479050, 1684890300, 1685301600, 1685712950, 1686124350, 1686535800, 1686947300, 1687358850, 1687770450, 1688182100, 1688593800, 1689005550, 1689417350, 1689829200, 1690241100, 1690653050, 1691065050, 1691477100, 1691889200, 1692301350, 1692713550, 1693125800, 1693538100, 1693950450, 1694362850, 1694775300, 1695187800, 1695600350, 1696012950, 1696425600, 1696838300, 1697251050, 1697663850, 1698076700, 1698489600, 1698902550, 1699315550, 1699728600, 1700141700, 1700554850, 1700968050, 1701381300, 1701794600, 1702207950, 1702621350, 1703034800, 1703448300, 1703861850, 1704275450, 1704689100, 1705102800, 1705516550, 1705930350, 1706344200, 1706758100, 1707172050, 1707586050, 1708000100, 1708414200, 1708828350, 1709242550, 1709656800, 1710071100, 1710485450, 1710899850, 1711314300, 1711728800, 1712143350, 1712557950, 1712972600, 1713387300, 1713802050, 1714216850, 1714631700, 1715046600, 1715461550, 1715876550, 1716291600, 1716706700, 1717121850, 1717537050, 1717952300, 1718367600, 1718782950, 1719198350, 1719613800, 1720029300, 1720444850, 1720860450, 1721276100, 1721691800, 1722107550, 1722523350, 1722939200, 1723355100, 1723771050, 1724187050, 1724603100, 1725019200, 1725435350, 1725851550, 1726267800, 1726684100, 1727100450, 1727516850, 1727933300, 1728349800, 1728766350, 1729182950, 1729599600, 1730016300, 1730433050, 1730849850, 1731266700, 1731683600, 1732100550, 1732517550, 1732934600, 1733351700, 1733768850, 1734186050, 1734603300, 1735020600, 1735437950, 1735855350, 1736272800, 1736690300, 1737107850, 1737525450, 1737943100, 1738360800, 1738778550, 1739196350, 1739614200, 1740032100, 1740450050, 1740868050, 1741286100, 1741704200, 1742122350, 1742540550, 1742958800, 1743377100, 1743795450, 1744213850, 1744632300, 1745050800, 1745469350, 1745887950, 1746306600, 1746725300, 1747144050, 1747562850, 1747981700, 1748400600, 1748819550, 1749238550, 1749657600, 1750076700, 1750495850, 1750915050, 1751334300, 1751753600, 1752172950, 1752592350, 1753011800, 1753431300, 1753850850, 1754270450, 1754690100, 1755109800, 1755529550, 1755949350, 1756369200, 1756789100, 1757209050, 1757629050, 1758049100, 1758469200, 1758889350, 1759309550, 1759729800, 1760150100, 1760570450, 1760990850, 1761411300, 1761831800, 1762252350, 1762672950, 1763093600, 1763514300, 1763935050, 1764355850, 1764776700, 1765197600, 1765618550, 1766039550, 1766460600, 1766881700, 1767302850, 1767724050, 1768145300, 1768566600, 1768987950, 1769409350, 1769830800, 1770252300, 1770673850, 1771095450, 1771517100, 1771938800, 1772360550, 1772782350, 1773204200, 1773626100, 1774048050, 1774470050, 1774892100, 1775314200, 1775736350, 1776158550, 1776580800, 1777003100, 1777425450, 1777847850, 1778270300, 1778692800, 1779115350, 1779537950, 1779960600, 1780383300, 1780806050, 1781228850, 1781651700, 1782074600, 1782497550, 1782920550, 1783343600, 1783766700, 1784189850, 1784613050, 1785036300, 1785459600, 1785882950, 1786306350, 1786729800, 1787153300, 1787576850 };



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
void ENABLEACC()
{
	STATS::STAT_SET_INT(0x1A830CB5, 0, 1);
	STATS::STAT_SET_INT(0x283CA828, 0, 1);
	STATS::STAT_SET_INT(0x8CD7713C, 0, 1);
	STATS::STAT_SET_INT(0x7E99D4C1, 0, 1);
	STATS::STAT_SET_INT(0x308A3897, 0, 1);
	STATS::STAT_SET_INT(0x1DC4130B, 0, 1);
	STATS::STAT_SET_INT(0xC46F606B, 0, 1);
	STATS::STAT_SET_INT(0x876E1810, 0, 1);
	STATS::STAT_SET_INT(0x99ABBC8B, 0, 1);
	STATS::STAT_SET_INT(0x9CECC30D, 0, 1);
	STATS::STAT_SET_INT(0xAF5F67F2, 0, 1);
	STATS::STAT_SET_INT(0x434A8FC6, 0, 1);
	STATS::STAT_SET_INT(0x647CD22A, 0, 1);
	STATS::STAT_SET_INT(0x76D376D7, 0, 1);
	STATS::STAT_SET_INT(0x88746179, 0, 1);
	STATS::STAT_SET_INT(0x9B3406FC, 0, 1);
	STATS::STAT_SET_INT(0xB3CE3830, 0, 1);
	STATS::STAT_SET_INT(0xC688DDA5, 0, 1);
	STATS::STAT_SET_INT(0xD34DF72F, 0, 1);
	STATS::STAT_SET_INT(0xE21B94CA, 0, 1);
	STATS::STAT_SET_INT(0xDED58E42, 0, 1);
	STATS::STAT_SET_INT(0x1AAA649B, 0, 1);
	STATS::STAT_SET_INT(0xB5629A1D, 0, 1);
	STATS::STAT_SET_INT(0xC7D33EFE, 0, 1);
	STATS::STAT_SET_INT(0x62EB8C5A, 0, 1);
	STATS::STAT_SET_INT(0xE7072CD, 0, 1);
}

void FixAccount(Hash _hash)
{
	int GetValue;
	STATS::STAT_GET_INT(_hash, &GetValue, -1);
	if (GetValue != 0)
		STATS::STAT_SET_INT(_hash, 0, 1);
}

void EnableAccountLoop()
{
	FixAccount(GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED"));
	FixAccount(0xF1AD9B2B);
	FixAccount(0x3EB3FA6);
	FixAccount(0x4D3AD244);
	FixAccount(0x724BAE22);
	FixAccount(0x7D15C3B6);
	FixAccount(0x279D18C6);
	FixAccount(0x3977BC7B);
	FixAccount(0x436AD061);
	FixAccount(0x5600758C);
	FixAccount(0xDFBF8908);
	FixAccount(0xF26E2E65);
	FixAccount(0xFD3743F7);
	FixAccount(0x9A45179F);
	FixAccount(0x4840E8F);
	FixAccount(0x83079483);
	FixAccount(0x671634FD);
	FixAccount(0x87CD697F);
	FixAccount(0xA4C198D9);
	FixAccount(0x6881E6B9);
	FixAccount(0xB7D704EB);
	FixAccount(0xACF9F1C2);
	FixAccount(0xB7869E);
	FixAccount(0xBE09FD96);
	FixAccount(0x98BA126);
	FixAccount(0x4DAA973A);
	FixAccount(0x25FD26C4);
	FixAccount(0x3C4E73A1);
	FixAccount(0xE155A3CA);
	FixAccount(0xA5E699CB);
	FixAccount(0xD0CD234);
	FixAccount(0x34868FD3);
	FixAccount(0x9CD69DC4);
	FixAccount(0x1A830CB5);
	FixAccount(0x283CA828);
	FixAccount(0x8CD7713C);
	FixAccount(0x7E99D4C1);
	FixAccount(0x308A3897);
	FixAccount(0x1DC4130B);
	FixAccount(0xC46F606B);
	FixAccount(0x876E1810);
	FixAccount(0x99ABBC8B);
	FixAccount(0x9CECC30D);
	FixAccount(0xAF5F67F2);
	FixAccount(0x434A8FC6);
	FixAccount(0x647CD22A);
	FixAccount(0x76D376D7);
	FixAccount(0x88746179);
	FixAccount(0x9B3406FC);
	FixAccount(0xB3CE3830);
	FixAccount(0xC688DDA5);
	FixAccount(0xD34DF72F);
	FixAccount(0xE21B94CA);
	FixAccount(0xDED58E42);
	FixAccount(0x1AAA649B);
	FixAccount(0xB5629A1D);
	FixAccount(0xC7D33EFE);
	FixAccount(0x62EB8C5A);
	FixAccount(0xE7072CD);
	FixAccount(0x9AAA476E);
	FixAccount(0x6362D8E4);
	FixAccount(0x952CBC73);
	FixAccount(0x3B5E88DC);
	FixAccount(0x6D506CBF);
	FixAccount(0x19F9C613);
	FixAccount(0x4EC18EB8);
	FixAccount(0x1A830CB5);
	FixAccount(0x283CA828);
	FixAccount(0x8CD7713C);
	FixAccount(0x7E99D4C1);
	FixAccount(0x308A3897);
	FixAccount(0x1DC4130B);
	FixAccount(0xC46F606B);
	FixAccount(0x876E1810);
	FixAccount(0x99ABBC8B);
	FixAccount(0x9CECC30D);
	FixAccount(0xAF5F67F2);
	FixAccount(0x434A8FC6);
	FixAccount(0x647CD22A);
	FixAccount(0x76D376D7);
	FixAccount(0x88746179);
	FixAccount(0x9B3406FC);
	FixAccount(0xB3CE3830);
	FixAccount(0xC688DDA5);
	FixAccount(0xD34DF72F);
	FixAccount(0xE21B94CA);
	FixAccount(0xDED58E42);
	FixAccount(0x1AAA649B);
	FixAccount(0xB5629A1D);
	FixAccount(0xC7D33EFE);
	FixAccount(0xD201535A);
	FixAccount(0xEC71883A);
	FixAccount(0xFEA02C97);
	FixAccount(0x8D74105);
	FixAccount(0xD0366B72);
	FixAccount(0x95C5DBD);
	FixAccount(0xAB81A209);
	FixAccount(0xE4D094A6);
	FixAccount(0x16FFF904);
	FixAccount(0x5033EB6F);
	FixAccount(0x4EC18EB8);
	FixAccount(0x5D92CBD7);
	FixAccount(0x62EB8C5A);
}

void EnableAccount()
{
	int GetValue[100];

	STATS::STAT_GET_INT(0x1A830CB5, &GetValue[0], -1);
	if (GetValue[0] != 0)
		STATS::STAT_SET_INT(0x1A830CB5, 0, 1);

	STATS::STAT_GET_INT(0x283CA828, &GetValue[1], -1);
	if (GetValue[1] != 0)
		STATS::STAT_SET_INT(0x283CA828, 0, 1);

	STATS::STAT_GET_INT(0x8CD7713C, &GetValue[2], -1);
	if (GetValue[2] != 0)
		STATS::STAT_SET_INT(0x8CD7713C, 0, 1);

	STATS::STAT_GET_INT(0x7E99D4C1, &GetValue[3], -1);
	if (GetValue[3] != 0)
		STATS::STAT_SET_INT(0x7E99D4C1, 0, 1);

	STATS::STAT_GET_INT(0x308A3897, &GetValue[4], -1);
	if (GetValue[4] != 0)
		STATS::STAT_SET_INT(0x308A3897, 0, 1);

	STATS::STAT_GET_INT(0x1DC4130B, &GetValue[5], -1);
	if (GetValue[5] != 0)
		STATS::STAT_SET_INT(0x1DC4130B, 0, 1);

	STATS::STAT_GET_INT(0xC46F606B, &GetValue[6], -1);
	if (GetValue[6] != 0)
		STATS::STAT_SET_INT(0xC46F606B, 0, 1);

	STATS::STAT_GET_INT(0x876E1810, &GetValue[7], -1);
	if (GetValue[7] != 0)
		STATS::STAT_SET_INT(0x876E1810, 0, 1);

	STATS::STAT_GET_INT(0x99ABBC8B, &GetValue[8], -1);
	if (GetValue[8] != 0)
		STATS::STAT_SET_INT(0x99ABBC8B, 0, 1);

	STATS::STAT_GET_INT(0x9CECC30D, &GetValue[9], -1);
	if (GetValue[9] != 0)
		STATS::STAT_SET_INT(0x9CECC30D, 0, 1);

	STATS::STAT_GET_INT(0xAF5F67F2, &GetValue[10], -1);
	if (GetValue[10] != 0)
		STATS::STAT_SET_INT(0xAF5F67F2, 0, 1);

	STATS::STAT_GET_INT(0x434A8FC6, &GetValue[11], -1);
	if (GetValue[11] != 0)
		STATS::STAT_SET_INT(0x434A8FC6, 0, 1);

	STATS::STAT_GET_INT(0x647CD22A, &GetValue[12], -1);
	if (GetValue[12] != 0)
		STATS::STAT_SET_INT(0x647CD22A, 0, 1);

	STATS::STAT_GET_INT(0x76D376D7, &GetValue[13], -1);
	if (GetValue[13] != 0)
		STATS::STAT_SET_INT(0x76D376D7, 0, 1);

	STATS::STAT_GET_INT(0x88746179, &GetValue[14], -1);
	if (GetValue[14] != 0)
		STATS::STAT_SET_INT(0x88746179, 0, 1);

	STATS::STAT_GET_INT(0x9B3406FC, &GetValue[15], -1);
	if (GetValue[15] != 0)
		STATS::STAT_SET_INT(0x9B3406FC, 0, 1);

	STATS::STAT_GET_INT(0xB3CE3830, &GetValue[16], -1);
	if (GetValue[16] != 0)
		STATS::STAT_SET_INT(0xB3CE3830, 0, 1);

	STATS::STAT_GET_INT(0xC688DDA5, &GetValue[17], -1);
	if (GetValue[17] != 0)
		STATS::STAT_SET_INT(0xC688DDA5, 0, 1);
	
	STATS::STAT_GET_INT(0xD34DF72F, &GetValue[18], -1);
	if (GetValue[18] != 0)
		STATS::STAT_SET_INT(0xD34DF72F, 0, 1);

	STATS::STAT_GET_INT(0xE21B94CA, &GetValue[19], -1);
	if (GetValue[19] != 0)
		STATS::STAT_SET_INT(0xE21B94CA, 0, 1);

	STATS::STAT_GET_INT(0xE21B94CA, &GetValue[20], -1);
	if (GetValue[20] != 0)
		STATS::STAT_SET_INT(0xE21B94CA, 0, 1);

	STATS::STAT_GET_INT(0x1AAA649B, &GetValue[21], -1);
	if (GetValue[21] != 0)
		STATS::STAT_SET_INT(0x1AAA649B, 0, 1);

	STATS::STAT_GET_INT(0xB5629A1D, &GetValue[22], -1);
	if (GetValue[22] != 0)
		STATS::STAT_SET_INT(0xB5629A1D, 0, 1);

	STATS::STAT_GET_INT(0xC7D33EFE, &GetValue[23], -1);
	if (GetValue[23] != 0)
		STATS::STAT_SET_INT(0xC7D33EFE, 0, 1);

	STATS::STAT_GET_INT(0x62EB8C5A, &GetValue[24], -1);
	if (GetValue[24] != 0)
		STATS::STAT_SET_INT(0x62EB8C5A, 0, 1);

	STATS::STAT_GET_INT(0xE7072CD, &GetValue[25], -1);
	if (GetValue[25] != 0)
		STATS::STAT_SET_INT(0xE7072CD, 0, 1);
}

void SendSpoofedMessage(int a_iPlayer, int a_iPlayer2, char* a_cMessage)
{
	if (NETWORK::NETWORK_IS_IN_SESSION() && a_iPlayer2 != PLAYER::PLAYER_ID() && NETWORK::NETWORK_IS_PLAYER_CONNECTED(a_iPlayer2))
	{
		CPlayerInfo cPlayerInfo;
		memset((void *)0x10050020, 0, sizeof(cPlayerInfo));
		cPlayerInfo.unk0 = 0x00000002;
		strcpy(cPlayerInfo.unk2, PLAYER::GET_PLAYER_NAME(a_iPlayer));
		cPlayerInfo.unk7 = 0x02000000;
		*(CPlayerInfo*)(0x10050020) = cPlayerInfo;
		int *cPlayerStruct = (int*)(NETWORK_HANDLE_FROM_PLAYER1(a_iPlayer2) + 0xC);
		memset((void *)0x10050118, 0, 0x18);
		int *_0x10050118 = (int*)0x10050118;
		_0x10050118[0] = cPlayerStruct[0];
		_0x10050118[1] = cPlayerStruct[1];
		_0x10050118[2] = cPlayerStruct[2];
		_0x10050118[3] = cPlayerStruct[3];
		_0x10050118[4] = cPlayerStruct[4];
		_0x10050118[5] = cPlayerStruct[5];
		NETWORK_SEND_TEXT_MESSAGE(*(int32_t*)0x1CF72D4, a_cMessage, 0x10050020, 0x10050118);
		if (SpoofKasuAll[0])
			SpoofKasuIndex[0]++;
		if (SpoofKasuAll[1])
			SpoofKasuIndex[1]++;
	}
}


void SooofMessage(int player, char *_aaa)
{
	SendSpoofedMessage(player, player, _aaa);
}
void Remote_Skill(int value)
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), value);
	SooofMessage(selectedPlayer, "スキルアップしました!");
}

void Remote_Invetory(int value = INT_MAX)
{
	int Player_Index = selectedPlayer;

	//アーマー
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_1_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_2_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_3_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_4_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ARMOUR_5_COUNT"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_1_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_2_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_3_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_4_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_ARMOUR_5_COUNT"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_1_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_2_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_3_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_4_COUNT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CHAR_ARMOUR_5_COUNT"), value);

	//スナック
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_YUM_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_HEALTH_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NO_BOUGHT_EPIC_SNACKS"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_NUMBER_OF_ORANGE_BOUGHT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CIGARETTES_BOUGHT"), value);

	//花火
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), value);

	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_1_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_2_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_3_BLUE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_WHITE"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_RED"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_FIREWORK_TYPE_4_BLUE"), value);

	//スモーク
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), value);
	setPlayerStat(Player_Index, GAMEPLAY::GET_HASH_KEY("MP2_CIGARETTES_BOUGHT"), value);

	SooofMessage(selectedPlayer, "スナック増やしました!");
}

void Remote_LSCUnlock()
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_NIGHTVISION_KILLS"), 100);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_RACES_WON"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_RACES_WON"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_1_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_2_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_3_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_4_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_6_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_FM_CARMOD_7_UNLCK"), -1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRALLYWONNAV"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRALLYWONNAV"), 1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 1);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 50);

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 100);

	/*setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600);
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

	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_USJS_FOUND"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_CAPTURES"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_NIGHTVISION_KILLS"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP1_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);*/
	SooofMessage(selectedPlayer, "LSC解除しました!");
	
/*
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_ENEMYDRIVEBYKILLS"), 600);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_USJS_COMPLETED"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_USJS_FOUND"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_DB_PLAYER_KILLS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_KILLS_PLAYERS"), 1000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMHORDWAVESSURVIVE"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_TDM_MVP"), 60);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_HOLD_UP_SHOPS"), 20);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_NO_ARMWRESTLING_WINS"), 21);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FMBBETWIN"), 50000);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_DM_WINS"), 51);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_DM_TOTALKILLS"), 500);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_DM_TOTAL_DEATHS"), 412);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_PLAYER_HEADSHOTS"), 623);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_DM_WINS"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_TDM_WINS"), 13);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_GTA_RACES_WON"), 12);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_GOLF_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_TG_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_RT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_CT_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FM_TENNIS_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TENNIS_MATCHES_WON"), 2);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TOTAL_RACES_WON"), 101);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_MPPLY_TOTAL_RACES_LOST"), 36);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_25_KILLS_STICKYBOMBS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_50_KILLS_GRENADES"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_GRENADE_ENEMY_KILLS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_20_KILLS_MELEE"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_CAPTURES"), 25);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_DROPOFF_CAP_PACKAGES"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_KILL_CARRIER_CAPTURE"), 100);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEISTS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_FINISH_HEIST_SETUP_JOB"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_NIGHTVISION_KILLS"), 1);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_WIN_LAST_TEAM_STANDINGS"), 50);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MP2_AWD_ONLY_PLAYER_ALIVE_LTS"), 50);*/
}

void Remote_HairUnlock()
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
	SooofMessage(selectedPlayer, "髪型解除しました!");
}

void Remote_RP(int value)
{
	int Args2[5];
	Args2[0] = 0xD8;
	Args2[1] = selectedPlayer;
	Args2[2] = value;
	Args2[3] = 0;
	Args2[4] = 0;
	TriggerScriptEvent(Args2, 5, selectedPlayer);
	SooofMessage(selectedPlayer, "RP変更しました!");
}

void Remote_CrewRank(int value)
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_0"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_1"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_2"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_3"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_LOCAL_XP_4"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_0"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_1"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_2"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_3"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("MPPLY_CREW_GLOBAL_XP_4"), value);
	SooofMessage(selectedPlayer, "クルーランク変更しました!");
}

void Remote_GiveMoney20(int value)
{
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_NEW "), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_CREDITED"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_DEBITED "), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_LEAVE_REMAINDER"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_GIFT_MIN_BALANCE"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_EVC_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_PVC_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_USDE_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_PXR_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_FIX_PVC_WB_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("CASH_FIX_EVC_CORRECTION"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("TOTAL_CASH"), value);
	setPlayerStat(selectedPlayer, GAMEPLAY::GET_HASH_KEY("BANK_BALANCE"), value);
	SooofMessage(selectedPlayer, "20億プレゼントしました!");
}

int getPlayerStat(int player, int stat)
{
	return PS3::Read_Global(1581767 + (player * 306) + stat);
}

void GiveRP(int RP, int player)
{


	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP0_SET_RP_GIFT_ADMIN"), RP);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP1_SET_RP_GIFT_ADMIN"), RP);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), RP);
	SetPlayerStats_Hash_int(player, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_SET_RP_GIFT_ADMIN"), RP);
	SetPlayerStats_Hash_int(player, GAMEPLAY::GET_HASH_KEY("MPPLY_IS_HIGH_EARNER"), 0);
	SooofMessage(selectedPlayer, "ランク変更しました!");
}

void giveranks(int index, int player) {
	int RankPoint = Ranks[index] - getPlayerStat(player, 180);

	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP0_SET_RP_GIFT_ADMIN"), RankPoint);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP1_SET_RP_GIFT_ADMIN"), RankPoint);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), RankPoint);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MP1_CHAR_SET_RP_GIFT_ADMIN"), RankPoint);
	SetPlayerStats_Hash(player, GAMEPLAY::GET_HASH_KEY("MPPLY_IS_HIGH_EARNER"), 0);
	SooofMessage(selectedPlayer, "ランク変更しました!");
}
#pragma endregion

#pragma region GarageEditor
namespace Color{
	RGB RED = { 255, 0, 0 };
	RGB GREEN = { 0, 255, 0 };
	RGB BLUE = { 0, 0, 255 };
	RGB LIGHTBLUE = { 0, 255, 255 };
	RGB DEEPGREEN = { 0, 0xCC, 0x00 };
	RGB LIGHTPINK = { 255, 0, 255 };
	RGB YELLOW = { 0xFF, 0xFF, 0x0 };

}

namespace GarageEditor {
	enum GarageEditorOffSet
	{
		All_Size = 0x190,
		Car_Hash = 0xB0,

		Car_Chrome_1 = 0x1F,
		Car_Chrome_2 = 0x23,
		Car_Chrome_3 = 0xC7,
		Car_Chrome_4 = 0xCB,
		Car_Chrome_5 = 0xCF,
		Car_Chrome_6 = 0x18B,
		Car_Chrome_7 = 0x18F,

		Car_VehicleRED = 0xC4,
		Car_VehicleGREEN = 0xC8,
		Car_VehicleBLUE = 0xCC,
		Car_VehicleColorFlag = 0xD0,

		Car_SmokeRed = 0xA0,
		Car_SmokeGreen = 0xA4,
		Car_SmokeBlue = 0xA8,
		Car_SmokeFlag = 0x83,
	};

	enum GarageSubColor
	{
	

	};

	void All_Delete(int pointer, int index)
	{
		char _null[All_Size];
		PS3::WriteBytes(pointer + (index * All_Size), _null, All_Size);
	}

	void ChangeAddress(int pointer, int index, int address, char num)
	{
		PS3::WriteByte(pointer + address + (index * All_Size), num);
	}

	void Set_PatriotSmoke(int pointer, int index)
	{
		PS3::WriteUInt32(pointer + Car_SmokeRed + (index * All_Size), 0);
		PS3::WriteUInt32(pointer + Car_SmokeGreen + (index * All_Size), 0);
		PS3::WriteUInt32(pointer + Car_SmokeBlue + (index * All_Size), 0);
		ChangeAddress(pointer, index, Car_SmokeFlag, 1);
	}

	void Set_Car(int pointer, int index, Hash hash)
	{
		PS3::WriteUInt32(pointer + (index * GarageEditor::All_Size) + GarageEditor::Car_Hash, hash);
	}

	void Set_Chrome(int pointer, int index)
	{
		char Numbers[] = { 0x78 };
		PS3::WriteBytes(pointer + Car_Chrome_1 + index * All_Size, Numbers, 1);
		PS3::WriteBytes(pointer + Car_Chrome_2 + index * All_Size, Numbers, 1);
		char Numbers2[] = { 0x00 };
		PS3::WriteBytes(pointer + Car_Chrome_3 + index * All_Size, Numbers2, 1);
		PS3::WriteBytes(pointer + Car_Chrome_4 + index * All_Size, Numbers2, 1);
		PS3::WriteBytes(pointer + Car_Chrome_5 + index * All_Size, Numbers2, 1);
		char Numbers3[] = { 0x04 };
		char Numbers4[] = { 0x04 };
		PS3::WriteBytes(pointer + Car_Chrome_6 + index * All_Size, Numbers3, 1);
		PS3::WriteBytes(pointer + Car_Chrome_7 + index * All_Size, Numbers4, 1);
	}

	void Set_Color(int pointer, int index, int R, int G, int B)
	{
		PS3::WriteUInt32(pointer + Car_VehicleRED + index * All_Size, R);
		PS3::WriteUInt32(pointer + Car_VehicleGREEN + index * All_Size, G);
		PS3::WriteUInt32(pointer + Car_VehicleBLUE + index * All_Size, B);
		PS3::WriteUInt32(pointer + Car_VehicleColorFlag + index * All_Size, 0x00003000);
		//PS3::WriteUInt32(pointer + 0xD4 + index * All_Size, subColor);
	}

	char *GarageCars[]{
		"sovereign",
		"romero",
		"bagger",
		"bmx",
		"dune",
		"daemon",
		"tornado4",
		"btype",
		"panto",
		"buffalo",

		"bmx",
		"bmx",


		"voodoo2",
		"bodhi2",
		"ratloader",
		"bfinjection",
		"elegy2",
		"kuruma2",
		"insurgent2",
		"adder",
		"entityxf",
		"cheetah",

		"bmx",
		"bmx",


		"vacca",
		"bullet",
		"infernus",
		"voltic",
		"zentorno",
		"turismor",
		"osiris",
		"t20",
		"phoenix",
		"peyote",

		"voodoo2",
		"bmx"
	};
}


#pragma endregion

#pragma region Allplayer
float DistanceBetweenVectors(Vector3 v1, Vector3 v2, bool flag = true)
{
	float ret = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, flag);
	return ret;
}
void SetSnowOnGround(bool unko)
{
	PS3::SetTunable(4715, unko ? 1 : 0);
}

int WeatherAddress1 = 0x003D3E48;
int WeatherAddress2 = 0x01095304;
int WeatherAddress3 = 0x01095358;
void ChangeAllPlayerChange(int index)
{
	if (PS3::ReadInt32(WeatherAddress1) != 0x60000000 || PS3::ReadInt32(WeatherAddress2) != 0x60000000 || PS3::ReadInt32(WeatherAddress3) != 0x60000000)
	{
		PS3::WriteBytes(WeatherAddress1, NotWrite, 4);
		PS3::WriteBytes(WeatherAddress2, NotWrite, 4);
		PS3::WriteBytes(WeatherAddress3, NotWrite, 4);
	}
	switch (index)
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
	GAMEPLAY::SET_WEATHER_TYPE_NOW(CHANGEhsh[index]);
	GAMEPLAY::SET_OVERRIDE_WEATHER(CHANGEhsh[index]);
	GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(CHANGEhsh[index], 0);
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(CHANGEhsh[index]);
}

OPD_s Parser3 = { 0x12C2E2C, 0x1C85330 };
void(*GAME_WEATHER_FUNC)(int r3, int r4, int r5, int r6) = (void(*)(int, int, int, int))&Parser3;
enum weatherMemoryTypes {
	extrasunny = 0x0,
	clear = 0x1,
	clouds = 0x2,
	smog = 0x3,
	foggy = 0x4,
	overcast = 0x5,
	rain = 0x6,
	thunder = 0x7,
	clearing = 0x8,
	neutral = 0x9,
	snow = 0xA,
	blizzard = 0xB,
	snowlight = 0xC,
	xmas = 0xD,
	reset = 0x0,
	freeze = 0xE,
	blackout = -0x1

}; 
void GAME_WEATHER(int a_iPlayer, weatherMemoryTypes a_wType) //GAME_WEATHER(selectedPlayer, freeze_WT);
{
	GAME_WEATHER_FUNC(a_wType == reset ? 0 : 1, a_wType, a_wType == freeze ? 0x9D : 0x4E, NETWORK_HANDLE_FROM_PLAYER(a_iPlayer));
}

void lobbyTime(int hour, int min, int sec)
{
	setlobbytimeNoHOST(hour, min, sec);
}

unsigned long getPlayerIPInfo(int player) {
	int playerPed = PLAYER::GET_PLAYER_PED(player);
	if (ENTITY::DOES_ENTITY_EXIST(playerPed)) {
		unsigned long pedAddress = GetEntityAddress(playerPed); //possible CPed
		if (pedAddress != NULL) {
			unsigned long CPlayerInfoStruct = *(unsigned long*)(pedAddress + 0xBD0); //CPlayerInfo
			if (CPlayerInfoStruct != NULL) {
				return *(unsigned long*)(CPlayerInfoStruct + 0x4);
			}
		}
	}
	return NULL;
}


bool Invisible_C(int player)
{
	if (player != PLAYER::PLAYER_ID())
	{
		unsigned char flag;
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player)))
		{
			if (PS3::ReadUInt32(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB7) == 0x00)
				return true;
		}
	}
}

bool GodMode_C(int player)
{
	//unsigned char flag;
	unsigned int flag2;
	unsigned int flag3;

	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player)))
	{
		flag2 = PS3::ReadInt16(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB4);
		flag3 = PS3::ReadInt16(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB6);
	}

	if (flag2 == 0x3080) //detected v1 ON
	{
		if (flag3 == 0x0802)
		{
			if (!PLAYER::IS_PLAYER_DEAD(player))
				return true;
		}
	}

	if (flag2 == 0x3080) //detected v1 ON
	{
		if (flag3 == 0x0800)
		{
			if (!PLAYER::IS_PLAYER_DEAD(player))
				return true;
		}
	}

	return false;
}

bool GodMode_Check(int player)
{
	if (GodMode_C(player) &&
		!Invisible_C(player) &&
		!NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player) && 
		!PLAYER::IS_PLAYER_DEAD(player) &&
		!ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(player) &&
		(PS3::Read_Global(1581767 + (player * 306) + 238) == 0) &&
		!NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player) &&
		!ENTITY::IS_ENTITY_IN_WATER(PLAYER::GET_PLAYER_PED(player)))
		return true;
}

#pragma endregion

#pragma region Protection
void Protection_AutoON()
{
	DETECTION_P = true;
	//isHDD = true;
	//KICK_P = true;
	//DETECTION_P = true;
	////PARADISE_P = true;
	//RCE_P = true;
	//SCRIPT_P = true;
	//STATUS_P = true;
	//WEATHER_P = true;

	//PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, 0x4E800020);
	//PS3::WriteUInt32(0x12C2D8C, 0x4E800020);

	addMessageShow("パッチしました！");
}
#define NOP 0x4E800020
#define R_NOP 0x7C0802A6
void Protection_AutoOFf()
{

	//isHDD = false;
	//KICK_P = false;
	//DETECTION_P = false;
	////PARADISE_P = false;
	//RCE_P = false;
	//SCRIPT_P = false;
	//STATUS_P = false;
	//WEATHER_P = false;

	//PS3::WriteUInt32(0x1357D44, 0x907E0004);
	//PS3::WriteUInt32(0x1370334, 0x907E0004);
	//PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);
	//PS3::WriteUInt32(0x1358AFC, 0x7C0802A6);

	//PS3::WriteUInt32(0x1C6BD80, 0x12C8CC0);
	//PS3::WriteUInt32(0x1C6BD84, 0x01C85330);

	//PS3::WriteUInt32(0x1C6BAA8, 0x12C2D8C);
	//PS3::WriteUInt32(0x1C6BAAC, 0x01C85330);

	//PS3::WriteUInt32(0x1C6BF80, 0x12CB4BC);
	//PS3::WriteUInt32(0x1C6BF84, 0x01C85330);

	//PS3::WriteUInt32(0x1C6C5F8, 0x12D2064);
	//PS3::WriteUInt32(0x1C6C5FC, 0x01C85330);

	//PS3::WriteUInt32(0x1C6C530, 0x12D12DC);
	//PS3::WriteUInt32(0x1C6C534, 0x01C85330);

	//PS3::WriteUInt32(0x1C707E0, 0x133C480);
	//PS3::WriteUInt32(0x1C707E4, 0x01C85330);

	////if (PS3::ReadUInt32(0x9FBB58) != 0x7FE10808) //OFF
	////	PS3::WriteUInt32(0x9FBB58, 0x7FE10808);

	////if (PS3::ReadUInt32(0x9FBB5C) != 0x4BFFFDA8)
	////	PS3::WriteUInt32(0x9FBB5C, 0x4BFFFDA8);

	////if (PS3::ReadUInt32(0x9FB990) != 0x4E800020)
	////	PS3::WriteUInt32(0x9FB990, 0x7FE10808);

	////if (PS3::ReadUInt32(0x9FFE90) != R_NOP) //ON	
	////	PS3::WriteUInt32(0x9FFE90, R_NOP); //Drop Kick

	//if (PS3::ReadUInt32(GIVE_PICKUP_REWARDS_EVENT) != R_NOP) //ON
	//	PS3::WriteUInt32(GIVE_PICKUP_REWARDS_EVENT, R_NOP);

	//PS3::WriteUInt32(0x12CBD94, 0x7C0802A6);
	//PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);
	//PS3::WriteUInt32(0x172D78C, 0x40820068);
	//PS3::WriteUInt32(0x1358F9C, 0x38600001);
	//PS3::WriteUInt32(0x1358F08, 0x907E0004);

	//PS3::WriteUInt32(GAME_CLOCK_EVENT, 0x7C0802A6);
	//PS3::WriteUInt32(GAME_WEATHER_EVENT, 0x7C0802A6);

	//PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, R_NOP);
	//PS3::WriteUInt32(0x12C2D8C, R_NOP);
	DETECTION_P = false;
	addMessageShow("オフにしました！");
}

bool isPlayerPlayingNProgress()
{
	if (PS3::ReadByte(0x1D65D91) == 0)
	{
		if (NETWORK::NETWORK_IS_GAME_IN_PROGRESS() == true)
		{
			return true;
		}
	}
	return false;
}

char HOST_SCRIPT[100];
unsigned int HOST_SCRIPT_FUNC(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7)
{
	char *NameOfSender = (char*)(*(int*)(r4 + 0x78) + 0x10);
	int addressOfArgs = r5 + 0x10;

	if (PS3::ReadInt32(0x223F0C0) == 0x01000000 && (PS3::ReadInt32(0x223F0C4) == 0x01000000))
	{
		if (isPlayerPlayingNProgress())
		{
			for (int i = 0; i < 16; i++)
			{
				if (MenuDetected[i])
				{
					if (GAMEPLAY::ARE_STRINGS_EQUAL(PLAYER::GET_PLAYER_NAME(i), NameOfSender))
					{
						//_sys_printf("NameOfSender %s || r6: 0x%X || addressOfArgs: 0x%X || r5: 0x%X || r7: 0x%X\n", NameOfSender, r6, *(int*)addressOfArgs, r5, r7);
						if (r6 > 0x0)
						{
							if (*(int*)addressOfArgs > 0x0)
							{
								r6 = 0; r7 = 0;
								*(int*)addressOfArgs = 0;
								//printf("0x%X", PS3::ReadUInt32(addressOfArgs));
								//snprintf(HOST_SCRIPT, 100, "%sがドロップキックしました。", NameOfSender);

								//if (!GAMEPLAY::ARE_STRINGS_EQUAL(MsgInfoBuf[9], HOST_SCRIPT))						
									//addMessageShow(HOST_SCRIPT);
							}
						}
					}
				}
			}
		}
	}
	return HOST_SCRIPT_FUNCS(r3, r4, r5, r6, r7);
}

void ParadiseBlockIn()
{

}

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


void ParadiseBlockOut()
{
	PS3::WriteUInt32(0x9FBB58, 0x7FE10808);
	PS3::WriteUInt32(0x9FBB5C, 0x4BFFFDA8);
	PS3::WriteUInt32(0x9FB990, 0x7FE10808);
}
#pragma endregion

#pragma region DrawMarker
void DrawMarker(int type, Vector3 pos, Vector3 dir, Vector3 rot, Vector3 scale, RGBA rgba, BOOL bobUpAndDown = 0, BOOL faceCamera = 0, int p19 = 2, BOOL rotate = 1, char* textureDict = 0, char* textureName = 0, BOOL drawOnEnts = 0)
{
	GRAPHICS::DRAW_MARKER(type, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, rot.x, rot.y, rot.z, scale.x, scale.y, scale.z, rgba.R, rgba.G, rgba.B, rgba.A, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts);
}

void DrawMarker1(int type, Vector3 pos, Vector3 dir, Vector3 rot, Vector3 scale, RGBA rgba)
{
	GRAPHICS::DRAW_MARKER(type, pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, rot.x, rot.y, rot.z, scale.x, scale.y, scale.z, rgba.R, rgba.G, rgba.B, rgba.A, true, false, 2, true, false, false, false);
}
#pragma endregion

#pragma region FunMenu
int Cam_OB, Cam_OB2;
int DragonFireCam, DragonFireCam2;
OPD_s _START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2_t = { 0x0157645C, 0x1C85330 };
bool(*_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2)(char *effectName, int entity, float x, float y, float z, float rotX, float rotY, float rotZ, float scale, bool p9, bool p10, bool p11) = (bool(*)(char *, int, float, float, float, float, float, float, float, bool, bool, bool))&_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2;

void ENTITY_P(char* asset, char* effect, int entity, float X, float Y, float Z, float xRot, float yRot, float zRot, float scale)
{
	STREAMING::REQUEST_NAMED_PTFX_ASSET(asset);
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(asset);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(effect, entity, X, Y, Z, xRot, yRot, zRot, scale, 0, 0, 0);
}

void ResetCamera()
{
	DragonFireCameraResetToggle = 10;
}

void doAnimation2(char *AnimDict, char *AnimID)
{
	doAnimation_Animdict = AnimDict;
	doAnimation_AnimID = AnimID;
	doAnimation = true;
}
#pragma endregion

#pragma region 画像変更
int errornum, pictureindex, pictureindex2;
int Picture_Address;
char PicBuf[0x4080];
int TEXTURE_ADDRESS;
int ADDRESS;
int get_dds_memory_address(char* dict, char* name)
{
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
	{
		TEXTURE_ADDRESS = GET_TEXTURE_ADDRESS(dict, name);
		ADDRESS = PS3::ReadUInt32(TEXTURE_ADDRESS + 0x20);

		return ADDRESS;
	}
	return 0;
}



void readDDSFile2(char *file, char buf[])
{
	int fd;    int ret;    uint64_t pos;    uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, 0x4080, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}

void readDDSFile(char *file, char buf[], int size)
{
	int fd;    int ret;    uint64_t pos;    uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}
int ByteLength;

uint _Texture;
uint _Address;

void TextureAddressGet(char* ar1, char* ar2)
{
	while (true)
	{
		if (TEXTURE_ADDRESS != 0)
			break;

		TEXTURE_ADDRESS = GET_TEXTURE_ADDRESS(ar1, ar2);
	}


	unsigned int ADDRESS = *(unsigned int*)(TEXTURE_ADDRESS + 0x20);

	printf("Loaded !\nTEXTURE_ADDRESS : 0x%X\nADDRESS : 0x%X\n", TEXTURE_ADDRESS, ADDRESS);
}

void imageInject(char *file, char* ar1, char*ar2, unsigned int MALLOC)
{
	unsigned int TEXTURE_ADDRESS;
	//unsigned int loc;
	//while (loc == 0)
	//{
	//	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("social_club2", 0);
	//	loc = get_dds_memory_address(ar1, ar2) - 0x4;
	//}
	
	while (true)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(ar1))
			break;

		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(ar1, 0);
	}

	while (true)
	{
		if (TEXTURE_ADDRESS != 0)
			break;

		TEXTURE_ADDRESS = GET_TEXTURE_ADDRESS(ar1, ar2);
	}

	
	unsigned int ADDRESS = *(unsigned int*)(TEXTURE_ADDRESS + 0x20);

	printf("Loaded !\nTEXTURE_ADDRESS : 0x%X\nADDRESS : 0x%X\n", TEXTURE_ADDRESS, ADDRESS);

	ByteLength = fileSize(file);
	if (ByteLength != -1)
	{
		printf("writing dds!\n");
		readDDSFile(file, (char*)ADDRESS, MALLOC);
		printf("writed dds!\n");
	}
	else
	{
		printf("error when load image on game!\n");
	}
}
void ddsH4x()
{
	imageInject("/dev_hdd0/tmp/Title.dds", "social_club2", "tour_image", 0x4080);
}
#pragma endregion

#pragma region 無敵感知
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



bool Godmodeplayer(int player) {
	if (PED::GET_PED_MAX_HEALTH(player) > 400 || ENTITY::GET_ENTITY_HEALTH(player) > 400)
	{
		return true;
	}

	if (GodModeCheck(player) && !IsPlayerInvisible(player) && !NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player) && !PLAYER::IS_PLAYER_DEAD(player) && !ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(player) && (getPlayerStat(player, 238) == 0) && !NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::GET_PLAYER_PED(player)))
	{
		return true;
	}
}

#pragma endregion

#pragma region Settings

char *RE_MODMENU(int index)
{
	int Zedd = 9900;
	int PoliceA = 0;
	int Polize = 8900;
	int value = PS3::Read_Global(1581767 + (index * 306) + 205);
	int value2 = PS3::Read_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 178 + 45);
	int maxaromour = PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::GET_PLAYER_PED(index));
	char *str = "";
	//if (PS3::Read_Global(1581767 + (index * 306) + 205) == 987)
	//	return " ~w~~p~Phantom ~r~A~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 986)
	//	return " ~w~~p~Phantom~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 914)
	//	return " ~w~~g~ZEDD~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 911)
	//	return " ~w~~g~ZEDD ~r~A~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 888)
	//	return " ~w~~y~PLS ~r~A~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 889)
	//	return " ~w~~g~PLS~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 9900)
	//	return " ~w~~g~ZEDD~w~";
	//else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 8900)
	//	return " ~w~~g~PLS~w~";
	//else
	//	return "N/A";
	bool _checkFlag;
	switch (value)
	{
	case 987:
		str = "~w~~p~Phantom ~r~A~w~";
		break;

	case 986:
		str = "~w~~p~Phantom~w~";
		break;

	default:
		str = "N/A";
		_checkFlag = true;
		break;
	}

	if (_checkFlag)
	{
		switch (value2)
		{
		case 80373826:
			str = "~g~PLS ~r~A";
			break;

		case 80593748:
			str = "~g~PLS";
			break;

		case 9487481:
			str = "~y~Zedd ~r~A";
			break;
			
		case 948749751:
			str = "~y~Zedd";
			break;

		case 0x5000:
			str = "~p~Re:Hyper Dx";
			break;
		}
	}

	switch (maxaromour)
	{
	case 2870:str = "~o~Genesis Cube";break;
	case 2871:str = "~o~Genesis Cube Pro"; break;

	}
	return str;
}

char* getProperty_i(int player, int propertyID)
{
	char getLabel[0x100];
	int globalHash = getPlayerStat(player, propertyID);
	//snprintf(getLabel, 0x100, "MP_PROP_%i", globalHash);
	snprintf(getLabel, 0x100, "MP_PROP_%i, 0x%X ", globalHash, PS3::Read_Global_Address(1581767 + (player * 306) + propertyID));
	//char* ap = UI::_GET_LABEL_TEXT(getLabel);
	//if (strstr(ap, "NULL"))
	//{
		//return "購入していません。";
	//}
	//else
	//{
		return getLabel;
		//return ap;
	//}
}

char* getProperty(int player, int propertyID)
{
	char getLabel[0x100];
	int globalHash = getPlayerStat(player, propertyID);
	if (globalHash >= 53)
		globalHash += 6;
	snprintf(getLabel, 0x100, "MP_PROP_%i", globalHash);
	//snprintf(getLabel, 0x100, "MP_PROP_%i, 0x%X ", globalHash, PS3::Read_Global_Address(1581767 + (player * 306) + propertyID));
	char* ap = UI::_GET_LABEL_TEXT(getLabel);
	if (strstr(ap, "NULL"))
	{
		return "購入していません。";
	}
	else
	{
		//return getLabel;
		return ap;
	}
}
int ApartTestVar = 0xEC;


int VEH_FREE_SPACE(int handle)
{
	int index = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(handle) - VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(handle);
	
	return index;
}
char* getPlayerIP(int playerIndex) {
	char ret[100];
	int port = *(int*)(0x40025ccd + (playerIndex * 0x88));
	int p9 = (port & 0xff000000) >> 24;
	int p10 = (port & 0x00ff0000) >> 16;
	int portToShow = (p9 << 8) | p10;
	int ip = getPlayerIPInfo(playerIndex);
	int p1 = (ip & 0xff000000) >> 24;
	int p2 = (ip & 0x00ff0000) >> 16;
	int p3 = (ip & 0x0000ff00) >> 8;
	int p4 = (ip & 0x000000ff) >> 0;
	snprintf(ret, 100, "%i.%i.%i.%i:", p1, p2, p3, p4, portToShow);
	return ret;
}			

char* getPlayerIP_Internal(int playerIndex) {
	char ret[100];
	char *Region = PS3::ReadBytes(0x40025c96 + (playerIndex * 0x88), 100);
	int ip = *(int *)(0x40025CA8 + (playerIndex * 0x88));
	int p1 = (ip & 0xff000000) >> 24;
	int p2 = (ip & 0x00ff0000) >> 16;
	int p3 = (ip & 0x0000ff00) >> 8;
	int p4 = (ip & 0x000000ff) >> 0;
	snprintf(ret, 100, "%i.%i.%i.%i:", p1, p2, p3, p4, Region);
	return ret;
}
char GBIP[50];
char I_IP[50];


Vector2 infoBox1 = { 0.4990, 0.1390 };
Vector2 infoBox2 = { 0.5070, 0.1260 };
Vector2 infoBox3 = { 0.6510, 0.1560 };
Vector2 infoBox4 = { 0.6580, 0.1430 };
float infoBoxX = 0.5891f;
float infoBoxY = 0.7520f;
float infoBoxSizeX = 0.2830f;
float infoBoxSizeY = 1.1790f;

float infoLineX = 0.5800f;
float infoLineY = 0.1406;
float infoLineSizeX = 0.2659f;
float infoLineSizeY = 0.04;

Vector4 infoTextLi = { 0.5790, 0.1400, 0.03, 0.1450 };

float infoTextSize = 0.4860;
float infomationUIY = 0.2660f;
float PlayerUIMinusX = 0.2700;
float InformationUI_ = 0.2930f;
Vector2 infoTextXY = { 0.5750, 0.1280 };
Vector2 infoBox_Plus = { -0.001f, 0.1320f };
float InforTextCo = 0.7170f;
float PlayerUIMinusX_ = 0.2350;
//PlayerUIMinusX
void PlayerInformationUI(int player)
{
	
	Entity PLAYER_PED_ = PLAYER::GET_PLAYER_PED(player);
	Vector3 P_Coord =  ENTITY::GET_ENTITY_COORDS(PLAYER_PED_, true);
	P_Coord.z += 1.5f;
	float textXCoord = InforTextCo;
	float Fontsize = 0.31;
	float PLY = 0.030f;
	float textYCoord = infomationUIY;
	DrawMarker1(21, P_Coord, newVector3(0, 0, 0), newVector3(180.0f, 0.0f, 0.0f), newVector3(0.9f, 0.9f, 0.9f), ESP_COLOR);
	Entity ENTITY___;
	bool IS_USING_CAR = PED::GET_VEHICLE_PED_IS_USING(PLAYER_PED_);
	if (IS_USING_CAR)
	{
		ENTITY___ = PED::GET_VEHICLE_PED_IS_IN(PLAYER_PED_, false);
	}
#pragma region STRINGS

	/*Real Name*/
	char RName[44];
	int Handle[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(player, &Handle[0], 13);
	char *RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(RealName))
		snprintf(RName, 44, "%s", RealName);
	else
		snprintf(RName, 44, "取得出来ませんでした。");
	/*HP*/
	char HP__[30];
	snprintf(HP__, 30, "%i / %i", ENTITY::GET_ENTITY_HEALTH(PLAYER_PED_), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER_PED_));

	/*Armour*/
	char AM__[30];
	snprintf(AM__, 30, "%i / %i", PED::GET_PED_ARMOUR(PLAYER_PED_), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::GET_PLAYER_PED(player)));

	/*Wanted*/
	char WT__[10];
	snprintf(WT__, 30, "%i / %i", PLAYER::GET_PLAYER_WANTED_LEVEL(player), 5);

	/*Rank*/
	char RK__[50];
	snprintf(RK__, 50, "RP: ~b~%i~w~, Rank : ~b~%i", getPlayerStat(player, 180), getPlayerStat(player, 185));

	/*Cash*/
	char CSH_[30];
	snprintf(CSH_, 30, "~b~%i ~w~$", getPlayerStat(player, 182));

	/*XYZ*/
	char XYZ_[200];
	snprintf___(XYZ_, 200, "X:[~b~%2.3f~w~] Y:[~b~%2.3f~w~] Z:[~b~%2.3f~w~]", P_Coord.x, P_Coord.y, P_Coord.z);

	/*Map, Street*/
	Hash retstreetname, Zonecrossingroad;
	PATHFIND::GET_STREET_NAME_AT_COORD(P_Coord.x, P_Coord.y, P_Coord.z, &retstreetname, &Zonecrossingroad);
	
	//Zone
	char ZONE[60];
	snprintf(ZONE, 60, "%s", UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(P_Coord.x, P_Coord.y, P_Coord.z)));

	//Street
	char STRT[70];
	snprintf(STRT, 70, "%s", UI::GET_STREET_NAME_FROM_HASH_KEY(retstreetname));

	//Speed
	char CAR_[70];
	if (IS_USING_CAR)
	{
		int indexes = VEH_FREE_SPACE(ENTITY___);
		snprintf(CAR_, 70, "~b~%s~w~ (空席 : ~b~%i~w~, ~b~%i~w~ KMPH)", UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(ENTITY___))), indexes, (int)ENTITY::GET_ENTITY_SPEED(ENTITY___));
	}
	else
		snprintf(CAR_, 70, "乗車していません。");

	//MODMENU
	int value = PS3::Read_Global(1581767 + (player * 306) + 205);
	int value2 = PS3::Read_Global(1581767 + (player * 306) + 178 + 45);
	int maxaromour = PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::GET_PLAYER_PED(player));
	char MODM[50];
	char *str_;

	if (value == 987)
		str_ = "~p~Phantom ~r~Admin";
	else if (value == 986)
		str_ = "~p~Phantom";
	else if (value2 == 80373826)
		str_ = "~g~POL!CE ~r~Admin";
	else if (value2 == 80593748)
		str_ = "~g~POL!CE";
	else if (value2 == 9487481)
		str_ = "~y~Zedd ~r~Admin";
	else if (value2 == 948749751)
		str_ = "~y~Zedd";
	else if (value2 == 0x5000)
		str_ = "~p~Re:Hyper Dx";
	else if (maxaromour == 2870)
		str_ = "~o~Genesis Cube";
	else if (maxaromour == 2871)
		str_ = "~o~Genesis Cube Pro";
	else
		str_ = "N/A";


	snprintf(MODM, 50, "%s", str_);
	char VCSet[70];
	snprintf(VCSet, 70, "VC : %s", NETWORK::NETWORK_PLAYER_HAS_HEADSET(player) ? NETWORK::NETWORK_IS_PLAYER_TALKING(player) ? "~g~会話中" : "~b~VC装着" : "~r~VC無し");

	//Model Hash
	char MDHS[50];
	snprintf(MDHS, 50, "0x%X", ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED(player)));

	//Handle
	//uint _a = NETWORK_HANDLE_FROM_PLAYER(player);
	//char HNDL[50];
	//snprintf___(HNDL, 50, "0x%X", _a);

	//GlobalAddress
	//char GBAL[50];
	//snprintf___(GBAL, 50, "0x%X", PS3::Read_Global_Address(1581767 + (player * 306)));




	if (IPADDRESS_TIMEOUT == 0 && _playeruiIPADDRESS)
	{
		if (player != PLAYER::PLAYER_ID())
		{
			for (int i = 0; i < 34; i++)
			{
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

					snprintf(GBIP, 50, "%i.%i.%i.%i:%i", p1, p2, p3, p4, portToShow);
					snprintf(I_IP, 50, "%i.%i.%i.%i:%s", p5, p6, p7, p8, Region);
					IPADDRESS_TIMEOUT = 5;

				}
			}
		}
		else
		{
			snprintf(GBIP, 50, "自分のPS3です。");
			snprintf(I_IP, 50, "自分のPS3です。");
		}
	}
	else if (IPADDRESS_TIMEOUT > 0)
	{
		//strcpy(GBIP, "取得できませんでした");
		//strcpy(I_IP, "取得できませんでした");
		IPADDRESS_TIMEOUT--;
	}
	
	//IP
	/*EBOOT*/
	char EBBT[40];
	snprintf(EBBT, 40, "%s", MenuDetected[player] ? "チーターサイズ" : "サイズ無し");

	//Crew Name
	//char CRNM[40];
	//char *CrewName = PS3::Read_Global_Char(1581767 + (player * 306) + 186); //0xF0FFC
	//snprintf___(CRNM, 40, "%s", CrewName);

	/*Apart 1*/
	char AP1_[40];
	snprintf(AP1_, 40, "%s", getProperty(player, 0xEB));

	/*Apart 2*/
	char AP2_[40];
	snprintf(AP2_, 40, "%s", getProperty(player, 0xEC));

	/*Apart 3*/
	char AP3_[40];
	snprintf(AP3_, 40, "%s", getProperty(player, 0xED));

	/*Apart 3*/
	char GD__[40];
	snprintf(GD__, 40, "%s", Godmodeplayer(player) ? "~b~無敵" : "~r~無敵なし");
	//Godmodeplayer(i)
	//snprintf___(AP1_, 0x100, "MP_PROP_%i, 0x%X ", globalHash, PS3::Read_Global_Address(1581767 + (player * 306) + 0xEB));
	//snprintf___(AP2_, 0x100, "MP_PROP_%i, 0x%X ", globalHash2, PS3::Read_Global_Address(1581767 + (player * 306) + 0xEC));
	//snprintf___(AP3_, 0x100, "MP_PROP_%i, 0x%X ", globalHash3, PS3::Read_Global_Address(1581767 + (player * 306) + 0xED));
#pragma endregion

	/*UI*/
	//GRAPHICS::DRAW_RECT(0.845f - PlayerUIMinusX, 0.1176f, MenuWidth, 0.083f, 255, 255, 255, 120); //white background
	//DrawSprite("timerbars", "all_white_bg", 0.9625f - PlayerUIMinusX, 0.1185f, 0.45f, 0.083f, 180, bannerRectRed, bannerRectGreen, bannerRectBlue, 120);
	//DrawSprite("timerbars", "all_white_bg", 0.727f - PlayerUIMinusX, 0.1185f, 0.45f, 0.083f, 0, bannerRectRed1, bannerRectGreen1, bannerRectBlue1, 120);
	//drawText("情報", 7, 0.845f - PlayerUIMinusX, 0.090f, 1.0f, 1.0f, 255, 255, 255, 255, true, false, true); // Main Title
	//drawText(PLAYER::GET_PLAYER_NAME(player), 0, 0.743f - PlayerUIMinusX, 0.160f, 0.37f, 0.37f, 255, 255, 255, 255, false, false, true); // SubTitle
	//GRAPHICS::DRAW_RECT(0.845f - PlayerUIMinusX, 0.176f, 0.21f, 0.035f, 0, 0, 0, 180); // top box
	float _inforY = 0;
	if (GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		_inforY = 0.1320f;
	}
	drawText(PLAYER::GET_PLAYER_NAME(player), 0, infoTextXY.x + infoBox_Plus.x, infoTextXY.y + infoBox_Plus.y - _inforY, infoTextSize, infoTextSize, 45, 255, 126, 255, true, false);
	GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, infoLineY + infoBox_Plus.y - _inforY, infoLineSizeX, infoLineSizeY, 20, 20, 20, 180); //Info Box line
	GRAPHICS::DRAW_RECT(infoTextLi.x + infoBox_Plus.x, infoTextLi.y + infoBox_Plus.y - _inforY, infoTextLi.w, infoTextLi.z, 45, 126, 255, 19); //Info Box line
	GRAPHICS::DRAW_RECT(infoBox1.x + infoBox_Plus.x, infoBox1.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Left Corner
	GRAPHICS::DRAW_RECT(infoBox2.x + infoBox_Plus.x, infoBox2.y + infoBox_Plus.y - _inforY, 0.016000f, 0.002000f, 255, 255, 255, 255); // Left Corner

	GRAPHICS::DRAW_RECT(infoBox3.x + infoBox_Plus.x, infoBox3.y + infoBox_Plus.y - _inforY, 0.015000f, 0.002000f, 255, 255, 255, 255); // Right Corner
	GRAPHICS::DRAW_RECT(infoBox4.x + infoBox_Plus.x, infoBox4.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Right Corner

	GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, (((18 * 0.035f) / 2) + InformationUI_) - _inforY, infoLineSizeX, (18 * 0.035f), 16, 16, 16, 120); //background

	if (*(int*)0x223F0C0 > 0)
	{
#pragma region TEXT
		

		//リアルネーム
		drawText("PSN_ID", optionsFont, textXCoord - PlayerUIMinusX, (1 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(RName, optionsFont, textXCoord - PlayerUIMinusX, (1 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//体力
		drawText("体力", optionsFont, textXCoord - PlayerUIMinusX, (2 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(HP__, optionsFont, textXCoord - PlayerUIMinusX, (2 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//アーマー
		drawText("アーマー", optionsFont, textXCoord - PlayerUIMinusX, (3 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(AM__, optionsFont, textXCoord - PlayerUIMinusX, (3 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//手配度
		drawText("手配度", optionsFont, textXCoord - PlayerUIMinusX, (4 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(WT__, optionsFont, textXCoord - PlayerUIMinusX, (4 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//手配度
		drawText("ランク", optionsFont, textXCoord - PlayerUIMinusX, (5 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(RK__, optionsFont, textXCoord - PlayerUIMinusX, (5 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//お金
		drawText("所持金", optionsFont, textXCoord - PlayerUIMinusX, (6 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(CSH_, optionsFont, textXCoord - PlayerUIMinusX, (6 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//XYZ
		drawText("座標", optionsFont, textXCoord - PlayerUIMinusX, (7 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(XYZ_, optionsFont, textXCoord - PlayerUIMinusX, (7 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//XYZ
		drawText("ゾーン", optionsFont, textXCoord - PlayerUIMinusX, (8 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(ZONE, optionsFont, textXCoord - PlayerUIMinusX, (8 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//XYZ
		drawText("地名", optionsFont, textXCoord - PlayerUIMinusX, (9 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(STRT, optionsFont, textXCoord - PlayerUIMinusX, (9 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//XYZ
		drawText("車", optionsFont, textXCoord - PlayerUIMinusX, (10 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(CAR_, optionsFont, textXCoord - PlayerUIMinusX, (10 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//MODMENU
		drawText("SPRX", optionsFont, textXCoord - PlayerUIMinusX, (11 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(MODM, optionsFont, textXCoord - PlayerUIMinusX, (11 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//HANDLE
		drawText("VC", optionsFont, textXCoord - PlayerUIMinusX, (12 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(VCSet, optionsFont, textXCoord - PlayerUIMinusX, (12 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//R3_1
		drawText("プレイヤーモデル", optionsFont, textXCoord - PlayerUIMinusX, (13 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(MDHS, optionsFont, textXCoord - PlayerUIMinusX, (13 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);


		//Crew Name
		//drawText("クルーネーム", optionsFont, textXCoord - PlayerUIMinusX, (14 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		//drawText(CRNM, optionsFont, textXCoord - PlayerUIMinusX, (14 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);
		//GD__

		//アパート3
		drawText("無敵", optionsFont, textXCoord - PlayerUIMinusX, (14 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(GD__, optionsFont, textXCoord - PlayerUIMinusX, (14 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		if (_playeruiIPADDRESS)
		{
			//アパート3
			drawText("グローバル IP", optionsFont, textXCoord - PlayerUIMinusX, (15 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText(GBIP, optionsFont, textXCoord - PlayerUIMinusX, (15 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

			//アパート3
			drawText("PS3内 IP", optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText(I_IP, optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);
		}
		else
		{
			//アパート3
			drawText("グローバル IP", optionsFont, textXCoord - PlayerUIMinusX, (15 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText("IP表示がOFFになっています。", optionsFont, textXCoord - PlayerUIMinusX, (15 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

			//アパート3
			drawText("PS3内 IP", optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText("IP表示がOFFになっています。", optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		}

		//アパート3
		drawText("EBOOT", optionsFont, textXCoord - PlayerUIMinusX, (17 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(EBBT, optionsFont, textXCoord - PlayerUIMinusX, (17 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);


		//HANDLE
		//drawText("Handle", optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		//drawText(HNDL, optionsFont, textXCoord - PlayerUIMinusX, (16 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);

		//SIZE
		//drawText("Global Address", optionsFont, textXCoord - PlayerUIMinusX, (17 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		//drawText(GBAL, optionsFont, textXCoord - PlayerUIMinusX, (17 * PLY + textYCoord), Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);

		//アパート1
		drawText("アパート 1", optionsFont, textXCoord - PlayerUIMinusX, (18 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(AP1_, optionsFont, textXCoord - PlayerUIMinusX, (18 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//アパート2
		drawText("アパート 2", optionsFont, textXCoord - PlayerUIMinusX, (19 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(AP2_, optionsFont, textXCoord - PlayerUIMinusX, (19 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);

		//アパート3
		drawText("アパート 3", optionsFont, textXCoord - PlayerUIMinusX, (20 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(AP3_, optionsFont, textXCoord - PlayerUIMinusX, (20 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX_);


#pragma endregion
	}
	else
	{
		drawText("セッションに参加してください。", optionsFont, textXCoord - PlayerUIMinusX, (1 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}

}

void ObjectInformationUI(Entity _Entity, char* name, int index)
{
	float textXCoord = InforTextCo;
	float Fontsize = 0.31;
	float PLY = 0.030f;
	float textYCoord = infomationUIY;
	float _inforY = 0;
	if (ENTITY::DOES_ENTITY_EXIST(_Entity))
	{
		
		if (GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
		{
			_inforY = 0.1320f;
		}
		drawText(name, 0, infoTextXY.x + infoBox_Plus.x, infoTextXY.y + infoBox_Plus.y - _inforY, infoTextSize, infoTextSize, 45, 255, 126, 255, true, false);
		GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, infoLineY + infoBox_Plus.y - _inforY, infoLineSizeX, infoLineSizeY, 20, 20, 20, 180); //Info Box line
		GRAPHICS::DRAW_RECT(infoTextLi.x + infoBox_Plus.x, infoTextLi.y + infoBox_Plus.y - _inforY, infoTextLi.w, infoTextLi.z, 45, 126, 255, 19); //Info Box line
		GRAPHICS::DRAW_RECT(infoBox1.x + infoBox_Plus.x, infoBox1.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Left Corner
		GRAPHICS::DRAW_RECT(infoBox2.x + infoBox_Plus.x, infoBox2.y + infoBox_Plus.y - _inforY, 0.016000f, 0.002000f, 255, 255, 255, 255); // Left Corner

		GRAPHICS::DRAW_RECT(infoBox3.x + infoBox_Plus.x, infoBox3.y + infoBox_Plus.y - _inforY, 0.015000f, 0.002000f, 255, 255, 255, 255); // Right Corner
		GRAPHICS::DRAW_RECT(infoBox4.x + infoBox_Plus.x, infoBox4.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Right Corner

		GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, (((10 * 0.035f) / 2) + InformationUI_) - _inforY, infoLineSizeX, (10 * 0.035f), 16, 16, 16, 120); //background

		//Vector3 rightVector;
		//Vector3 forwardVector;
		//Vector3 upVector;
		//Vector3 position;

		//ENTITY::GET_ENTITY_MATRIX(_Entity, &rightVector, &forwardVector, &upVector, &position);

		Vector3 P_Coord = ENTITY::GET_ENTITY_COORDS(_Entity, true);
		Vector3 P_Rot = ENTITY::GET_ENTITY_ROTATION(_Entity, 2);


		char XYZ_[200];
		snprintf___(XYZ_, 200, "X [%3.4f] Y [%3.4f] Z [%3.4f]", P_Coord.x, P_Coord.y, P_Coord.z);
		//strcpy(XYZ_, "X [");
		//strcat(XYZ_, FtoS(P_Coord.x));
		//strcat(XYZ_, "] Y [");
		//strcat(XYZ_, FtoS(P_Coord.y));
		//strcat(XYZ_, "] Z [");
		//strcat(XYZ_, FtoS(P_Coord.z));
		//strcat(XYZ_, "]");

		char RXYZ[80];
		snprintf___(RXYZ, 200, "X [%3.4f] Y [%3.4f] Z [%3.4f]", P_Rot.x, P_Rot.y, P_Rot.z);
		/*strcpy(RXYZ, "X [");
		strcat(RXYZ, FtoS(P_Rot.x));
		strcat(RXYZ, "] Y [");
		strcat(RXYZ, FtoS(P_Rot.y));
		strcat(RXYZ, "] Z [");
		strcat(RXYZ, FtoS(P_Rot.z));
		strcat(RXYZ, "]");*/

		//char RXYZ[80];
		//snprintf(RXYZ, 30, "X [%i] Y [%i] Z[%i]", (int)P_Rot.x, (int)P_Rot.y, (int)P_Rot.z);

		char MODL[60];
		snprintf(MODL, 30, "0x%X", ENTITY::GET_ENTITY_MODEL(_Entity));

		char ATTC[60];
		snprintf(ATTC, 40, "%s", ENTITY::IS_ENTITY_ATTACHED(_Entity) ? "アタッチ中" : "アタッチしていません");

		char RIGHT[40];
		char FORWARD[40];
		char UP[40];
		char POSITION[40];

		//snprintf(RIGHT, 40, "X [%s] Y [%s] Z [%s]", FtoS(rightVector.x), FtoS(rightVector.y), FtoS(rightVector.z));

		P_Coord.z += 1.5f;
		DrawMarker1(21, P_Coord, newVector3(0, 0, 0), newVector3(180.0f, 0.0f, 0.0f), newVector3(0.9f, 0.9f, 0.9f), ESP_COLOR);

		//座標
		drawText("座標", optionsFont, textXCoord - PlayerUIMinusX, (1 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(XYZ_, optionsFont, textXCoord - PlayerUIMinusX, (1 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);
	
		//回転
		drawText("回転", optionsFont, textXCoord - PlayerUIMinusX, (2 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(RXYZ, optionsFont, textXCoord - PlayerUIMinusX, (2 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);
		
		//ハッシュ
		drawText("ハッシュ", optionsFont, textXCoord - PlayerUIMinusX, (3 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(MODL, optionsFont, textXCoord - PlayerUIMinusX, (3 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);

		//アタッチ
		drawText("アタッチ", optionsFont, textXCoord - PlayerUIMinusX, (4 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
		drawText(ATTC, optionsFont, textXCoord - PlayerUIMinusX, (4 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);
		
		if (ENTITY::IS_ENTITY_ATTACHED(_Entity))
		{
			char AttachLocz[100];
			char AttachRotz[100];
			//アタッチ		
			snprintf___(AttachLocz, 100, "X [~b~%3.4f~w~] Y [~b~%3.4f~w~] Z [~b~%3.4f~w~]", AttachVector3[index].x, AttachVector3[index].y, AttachVector3[index].z);
			snprintf___(AttachRotz, 100, "X [~b~%3.4f~w~] Y [~b~%3.4f~w~] Z [~b~%3.4f~w~]", AttachRot[index].x, AttachRot[index].y, AttachRot[index].z);

			drawText("アタッチ 座標", optionsFont, textXCoord - PlayerUIMinusX, (5 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText(AttachLocz, optionsFont, textXCoord - PlayerUIMinusX, (5 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);

			drawText("アタッチ 回転", optionsFont, textXCoord - PlayerUIMinusX, (6 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
			drawText(AttachRotz, optionsFont, textXCoord - PlayerUIMinusX, (6 * PLY + textYCoord) - _inforY, Fontsize, Fontsize, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true, true, -PlayerUIMinusX);

		}
	}
	else
	{
		if (GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
		{
			_inforY = 0.1320f;
		}
		drawText("~r~存在していません", 0, infoTextXY.x + infoBox_Plus.x, infoTextXY.y + infoBox_Plus.y - _inforY, infoTextSize, infoTextSize, 45, 255, 126, 255, true, false);
		GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, infoLineY + infoBox_Plus.y - _inforY, infoLineSizeX, infoLineSizeY, 20, 20, 20, 180); //Info Box line
		GRAPHICS::DRAW_RECT(infoTextLi.x + infoBox_Plus.x, infoTextLi.y + infoBox_Plus.y - _inforY, infoTextLi.w, infoTextLi.z, 45, 126, 255, 19); //Info Box line
		GRAPHICS::DRAW_RECT(infoBox1.x + infoBox_Plus.x, infoBox1.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Left Corner
		GRAPHICS::DRAW_RECT(infoBox2.x + infoBox_Plus.x, infoBox2.y + infoBox_Plus.y - _inforY, 0.016000f, 0.002000f, 255, 255, 255, 255); // Left Corner

		GRAPHICS::DRAW_RECT(infoBox3.x + infoBox_Plus.x, infoBox3.y + infoBox_Plus.y - _inforY, 0.015000f, 0.002000f, 255, 255, 255, 255); // Right Corner
		GRAPHICS::DRAW_RECT(infoBox4.x + infoBox_Plus.x, infoBox4.y + infoBox_Plus.y - _inforY, 0.001000f, 0.025000f, 255, 255, 255, 255); // Right Corner

		GRAPHICS::DRAW_RECT(infoLineX + infoBox_Plus.x, (((18 * 0.035f) / 2) + InformationUI_) - _inforY, infoLineSizeX, (18 * 0.035f), 16, 16, 16, 120); //background
	}
}

char TLK[100];
#pragma endregion

#pragma region VehicleOption
RGBA TireColor[] = { RED, GREEN, BLUE, YELLOW, PURPLE, LBLUE };
char *tireBackup[VEHFX_INDEX];
int Tirecons = 0x14;
void tirekoncolor(bool toggle, RGBA _RGBA)
{
	if (toggle)
	{
		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
			PS3::WriteBytes(_ADDRESS + 0x08, Tire_Write_Byte, 20);
			PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)_RGBA.R);
			PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)_RGBA.G);
			PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)_RGBA.B);
		}

		//PS3::WriteBytes(0x213A5C0 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A5C0 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A5C0 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A5C0 + 0x26, (char)_RGBA.B);
		//PS3::WriteBytes(0x213A634 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A634 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A634 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A634 + 0x26, (char)_RGBA.B);
		//PS3::WriteBytes(0x213A6A8 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A6A8 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A6A8 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A6A8 + 0x26, (char)_RGBA.B);
	}
	else
	{
		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			PS3::WriteBytes(VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE) + 0x04, Tire_UNko_Byte, 40);
		}
		
	}
}

void tirekoncolor2(bool toggle, RGBA _RGBA)
{
	if (toggle)
	{
		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
			PS3::WriteBytes(_ADDRESS, Tire_Water_byte, 116);
			PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)_RGBA.R);
			PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)_RGBA.G);
			PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)_RGBA.B);
		}

		//PS3::WriteBytes(0x213A5C0 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A5C0 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A5C0 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A5C0 + 0x26, (char)_RGBA.B);
		//PS3::WriteBytes(0x213A634 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A634 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A634 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A634 + 0x26, (char)_RGBA.B);
		//PS3::WriteBytes(0x213A6A8 + 0x04, Tire_Write_Byte, 20);
		//PS3::WriteByte(0x213A6A8 + 0x24, (char)_RGBA.R);
		//PS3::WriteByte(0x213A6A8 + 0x25, (char)_RGBA.G);
		//PS3::WriteByte(0x213A6A8 + 0x26, (char)_RGBA.B);
	}
	else
	{
		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			PS3::WriteBytes(VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE) + 0x04, Tire_UNko_Byte, 40);
		}

	}
}
#pragma endregion

#pragma region Player Option

void Force_Option_x3(int player, int value)
{
	int args[3] = { 0x3 ,player ,value };
	TriggerScriptEvent(args, 3, player);
}

void ForceTutorial(int player)
{
	Force_Option_x3(player, 0x14);
}

void ForceGoldEvent(int player)
{
	Force_Option_x3(player, 0x37);
}

void ForceArmWrestling(int player)
{
	Force_Option_x3(player, 0x35);
}

void ForceLeave(int player)
{
	unsigned int bits = (1 << player);
	int args[3] = { 0x2 ,player,0x34 };
	TriggerScriptEvent(args, 3, player);
}

void ForceAirstrike(int player)
{
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x1B };
	TriggerScriptEvent(args, 3, player);
}

void ForceHelicopter(int player)
{
	unsigned int bits = (1 << player);
	int args[3] = { 0x3 ,player ,0x25 };
	TriggerScriptEvent(args, 3, player);
}

void apartmentInvite(int sender, int reciever)
{//I think it just sends it to the whole lobby
	int args[3];
	args[0] = 0x16c;
	args[1] = sender;
	args[2] = reciever;
	TriggerScriptEvent(args, 3, reciever);
}


void MessageSend(char *option)
{
	char Message[100];
	strcpy(Message, "");
	if (Message_Color_Bool)
		strcpy(Message, ColorMessageList[ColorMessageVar]);
	strcat(Message, option);

	if (Message_Spoof_Bool)
		SendSpoofedMessage(selectedNamedPlayer, selectedPlayer, Message);
	else
	{
		int NetHandleBuffer = 0x10070200;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
		NETWORK::NETWORK_SEND_TEXT_MESSAGE(Message, NetHandleBuffer);
	}
}

void MessageSend_w2(char *option)
{
	char Message[100];
	strcpy(Message, "");
	strcat(Message, option);

	if (Message_Spoof_Bool)
		SendSpoofedMessage(selectedNamedPlayer, selectedPlayer, Message);
	else
	{
		int NetHandleBuffer = 0x10070200;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, NetHandleBuffer, 13);
		NETWORK::NETWORK_SEND_TEXT_MESSAGE(Message, NetHandleBuffer);
	}
}

OPD_s _0xA5660C_t = { 0xA5659C, 0x1C85330 };
OPD_s _0xA57F28_t = { 0xA57EB8, 0x1C85330 };

int(*_0xA5660C)(int r3) = (int(*)(int))&_0xA5660C_t;
int(*_0xA57F28)(int r3, int r4) = (int(*)(int, int))&_0xA57F28_t;

void getHostOfThisScript()
{
	int netScrPoolStruc = *(int*)0x1C97568;
	if (netScrPoolStruc)
	{
		int netScripts = *(int*)netScrPoolStruc;
		int netScrCount = *(int*)(netScrPoolStruc + 8);
		int thrStrLength = *(int*)(netScrPoolStruc + 0xC);
		bool found = false;
		for (int i = 0; i < netScrCount; i++)
		{
			if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == PLAYER::PLAYER_ID())
				break;

			int lowerStruc = *(int*)(netScripts + 4 + (i * thrStrLength));
			if (lowerStruc)
			{
				if ((*(int*)(lowerStruc + 0x3C)) == 0xC875557D)
				{
					netScripts = (netScripts + (i * thrStrLength));
					found = true;
					break;
				}
			}
		}
		if (found)
		{
			*(int*)0xA566BC = 0x60000000;
			_0xA5660C(netScripts);
			int local = *(int*)0x1CC4A24;
			if (local)
			{
				local = *(int*)(local + 0x8C);
				_0xA57F28(netScripts, local);
			}
		}
	}
}


void _SendSpoofedMessage(char *name, int a_iPlayer2, char* a_cMessage)
{
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
		CPlayerInfo cPlayerInfo;
		memset((void *)0x10050020, 0, sizeof(cPlayerInfo));
		cPlayerInfo.unk0 = 0x00000002;
		strcpy(cPlayerInfo.unk2, name);
		cPlayerInfo.unk7 = 0x02000000;
		*(CPlayerInfo*)(0x10050020) = cPlayerInfo;
		int *cPlayerStruct = (int*)(NETWORK_HANDLE_FROM_PLAYER1(a_iPlayer2) + 0xC);
		memset((void *)0x10050118, 0, 0x18);
		int *_0x10050118 = (int*)0x10050118;
		_0x10050118[0] = cPlayerStruct[0];
		_0x10050118[1] = cPlayerStruct[1];
		_0x10050118[2] = cPlayerStruct[2];
		_0x10050118[3] = cPlayerStruct[3];
		_0x10050118[4] = cPlayerStruct[4];
		_0x10050118[5] = cPlayerStruct[5];
		NETWORK_SEND_TEXT_MESSAGE(*(int32_t*)0x1CF72D4, a_cMessage, 0x10050020, 0x10050118);
	}
}


void broadCastHostMod(int aiClientIndex, int a_iGlobalIndex, int a_iValueIndex, char* a_cMessage)
{
	if (isOnline())
	{
		if (PLAYER::PLAYER_ID() == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", -1, 0))
		{
			PS3::Write_Global(a_iGlobalIndex + aiClientIndex, a_iValueIndex);
			//s(aiClientIndex, aiClientIndex, a_cMessage);
		}
		else
		{
			if (PLAYER::PLAYER_ID() == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", -1, 0))
			{
				PS3::Write_Global(a_iGlobalIndex + aiClientIndex, a_iValueIndex);
				//SendSpoofedMessage(aiClientIndex, aiClientIndex, a_cMessage);
			}

		}
	}
	else
		addMessageShow("オンラインに入ってから使用してください。");
}

void _AttachFunc(int player, bool g)
{
	Entity _Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) : PLAYER::PLAYER_PED_ID();
	Entity TO_Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player)) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(player), false) : PLAYER::GET_PLAYER_PED(player);
	if (g)
	{
		int Bone = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player)) ? ENTITY::_GET_ENTITY_BONE_INDEX(TO_Entity, "roof") : PED::GET_PED_BONE_INDEX(TO_Entity, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(_Entity, TO_Entity, Bone, 0, 0, 2/*Loc_Z*/, 0, 0, 0/*Rot_Z*/, 0, 1, 0, 0, 2, 1);
		addMessageShow("アタッチしました。");
	
	}
	else
	{
		if (ENTITY::IS_ENTITY_ATTACHED(_Entity))
		{
			ENTITY::DETACH_ENTITY(_Entity, TO_Entity, 1);
			ENTITY::SET_ENTITY_COLLISION(_Entity, 1, 1);
			addMessageShow("アタッチを解除しました。");
		}
	}
}

OPD_s NETWORK_SESSION_KICK_PLAYER_t = { 0x1358BD0, 0x1C85330 };
void(*NETWORK_SESSION_KICK_PLAYER)(unsigned int a_uiHostPointer, unsigned int a_uiRecevPlayerIndex, unsigned int a_uiValueIndex, unsigned int a_ui0x1CF72C4) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&NETWORK_SESSION_KICK_PLAYER_t;
int SESSION_LEVEL[] = { 0, 1, 2, 4, 8 };
int KickInt2;
char *Kickchar[5] = { "セッション追放", "ネットワークエラー", "プレイヤーが去りました","管理者から削除されました","プレイヤーに蹴られました" };
void networkKickPlayerCustom(unsigned int a_uiRecevPlayerIndex, unsigned int a_uiValueIndex)
{
	NETWORK_SESSION_KICK_PLAYER(*(int32_t *)0x1CF72C4, NETWORK_HANDLE_FROM_PLAYER(a_uiRecevPlayerIndex), a_uiValueIndex, 0x1CF72C4);
}

void Shot_to_Player(int player, int player2, char* weapon_rpg = "weapon_rpg")
{
	int myped = PLAYER::GET_PLAYER_PED(player);
	int myped2 = PLAYER::GET_PLAYER_PED(player2);
	Vector3 start = ENTITY::GET_ENTITY_COORDS(myped, true);
	Vector3 end = ENTITY::GET_ENTITY_COORDS(myped2, true);
	Hash _hash = GAMEPLAY::GET_HASH_KEY(weapon_rpg);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(myped, _hash, 9999, 0);
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start.x, start.y, start.z, end.x, end.y, end.z, 5, true, _hash, myped, true, false, 1500.0f);
}

void Airstrike_to_Player(int player2, char* weapon_rpg = "weapon_rpg")
{
	int myped2 = PLAYER::GET_PLAYER_PED(player2);
	Vector3 end = ENTITY::GET_ENTITY_COORDS(myped2, true);
	Hash _hash = GAMEPLAY::GET_HASH_KEY(weapon_rpg);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _hash, 9999, 0);
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(end.x, end.y, end.z + 5, end.x, end.y, end.z, 5, true, _hash, PLAYER::PLAYER_PED_ID(), true, false, 1500.0f);
}

void _doESP(int player)
{
	char ESP_N[30];

	if (COLORED_ESP)
	{
		switch (COLORED_ESP_VAR)
		{
		case 0:ESP_COLOR.R = 255; ESP_COLOR.G = 0; ESP_COLOR.B = 0; ESP_COLOR.A = 255; break;
		case 1:ESP_COLOR.R = 0; ESP_COLOR.G = 255; ESP_COLOR.B = 0; ESP_COLOR.A = 255; break;
		case 2:ESP_COLOR.R = 0; ESP_COLOR.G = 0; ESP_COLOR.B = 255; ESP_COLOR.A = 255; break;
		case 3:ESP_COLOR.R = 255; ESP_COLOR.G = 255; ESP_COLOR.B = 0; ESP_COLOR.A = 255; break;
		case 4:ESP_COLOR.R = 180; ESP_COLOR.G = 0; ESP_COLOR.B = 255; ESP_COLOR.A = 255; break;
		case 5:ESP_COLOR.R = 0; ESP_COLOR.G = 0; ESP_COLOR.B = 150; ESP_COLOR.A = 255; break;
		}
	}
	else
	{
		if (ESP_COLOR.R == 5) {
			if (ESP_COLOR.G > 5)
				ESP_COLOR.G -= 1;
			if (ESP_COLOR.B < 255)
				ESP_COLOR.B += 1;
		}
		if (ESP_COLOR.G == 5) {
			if (ESP_COLOR.B > 5)
				ESP_COLOR.B -= 1;
			if (ESP_COLOR.R < 255)
				ESP_COLOR.R += 1;
		}
		if (ESP_COLOR.B == 5) {
			if (ESP_COLOR.R > 5)
				ESP_COLOR.R -= 1;
			if (ESP_COLOR.G < 255)
				ESP_COLOR.G += 1;
		}
	}
	Vector3 ggg = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player), true);
	Vector3 aaa = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

	float xa;
	float ya;
	GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ggg.x, ggg.y, ggg.z, &xa, &ya);
	GRAPHICS::DRAW_LINE(aaa.x, aaa.y, aaa.z, ggg.x, ggg.y, ggg.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
	//DrawMarker1(21, ggg, newVector3(0, 0, 0), newVector3(180.0f, 0.0f, 0.0f), newVector3(0.9f, 0.9f, 0.9f), ESP_COLOR);
	switch (ESPVar)
	{
	case 0:
		PlusVector = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, 0, ESPY);
		PlusVector2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, 0, ESPY);
		MinusVector = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, 0, -ESPY);
		MinusVector2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, 0, -ESPY);

		GRAPHICS::DRAW_LINE(PlusVector.x, PlusVector.y, PlusVector.z, PlusVector2.x, PlusVector2.y, PlusVector2.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(PlusVector.x, PlusVector.y, PlusVector.z, MinusVector.x, MinusVector.y, MinusVector.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);

		GRAPHICS::DRAW_LINE(MinusVector2.x, MinusVector2.y, MinusVector2.z, PlusVector2.x, PlusVector2.y, PlusVector2.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(MinusVector2.x, MinusVector2.y, MinusVector2.z, MinusVector.x, MinusVector.y, MinusVector.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		break;
	case 1:
		PlusVector = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, 0.2, ESPY);
		PlusVector2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, 0.2, ESPY);
		MinusVector = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, 0.2, -ESPY);
		MinusVector2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, 0.2, -ESPY);

		GRAPHICS::DRAW_LINE(PlusVector.x, PlusVector.y, PlusVector.z, PlusVector2.x, PlusVector2.y, PlusVector2.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(PlusVector.x, PlusVector.y, PlusVector.z, MinusVector.x, MinusVector.y, MinusVector.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);

		GRAPHICS::DRAW_LINE(MinusVector2.x, MinusVector2.y, MinusVector2.z, PlusVector2.x, PlusVector2.y, PlusVector2.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(MinusVector2.x, MinusVector2.y, MinusVector2.z, MinusVector.x, MinusVector.y, MinusVector.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);

		PlusVector3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, -0.2, ESPY);
		PlusVector4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, -0.2, ESPY);
		MinusVector3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), ESPX, -0.2, -ESPY);
		MinusVector4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(player), -ESPX, -0.2, -ESPY);

		GRAPHICS::DRAW_LINE(PlusVector3.x, PlusVector3.y, PlusVector3.z, PlusVector4.x, PlusVector4.y, PlusVector4.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(PlusVector3.x, PlusVector3.y, PlusVector3.z, MinusVector3.x, MinusVector3.y, MinusVector3.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);

		GRAPHICS::DRAW_LINE(MinusVector4.x, MinusVector4.y, MinusVector4.z, PlusVector4.x, PlusVector4.y, PlusVector4.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(MinusVector4.x, MinusVector4.y, MinusVector4.z, MinusVector3.x, MinusVector3.y, MinusVector3.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);


		GRAPHICS::DRAW_LINE(PlusVector.x, PlusVector.y, PlusVector.z, PlusVector3.x, PlusVector3.y, PlusVector3.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(PlusVector2.x, PlusVector2.y, PlusVector2.z, PlusVector4.x, PlusVector4.y, PlusVector4.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);

		GRAPHICS::DRAW_LINE(MinusVector.x, MinusVector.y, MinusVector.z, MinusVector3.x, MinusVector3.y, MinusVector3.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		GRAPHICS::DRAW_LINE(MinusVector2.x, MinusVector2.y, MinusVector2.z, MinusVector4.x, MinusVector4.y, MinusVector4.z, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, ESP_COLOR.A);
		break;
	}

	if (NAME_ESP)
	{
		float distance = DistanceBetweenVectors(aaa, ggg);
		snprintf(ESP_N, 30, "%s\n距離 : %i", PLAYER::GET_PLAYER_NAME(player), (int)distance);
		drawText(ESP_N, 0, xa, ya, 0.3f, 0.3f, ESP_COLOR.R, ESP_COLOR.G, ESP_COLOR.B, 255, true);
	}
}
#pragma endregion

#pragma region Disconetkick
OPD_s sub_0x9F81F8_t = { 0x9F81F8, 0x1C85330 };
int(*sub_0x9F81F8)(int r3) = (int(*)(int))&sub_0x9F81F8_t;
OPD_s sub_0x9F8870_t = { 0x9F8870, 0x1C85330 };
uint32_t(*sub_0x9F8870)(int r3) = (uint32_t(*)(int))&sub_0x9F8870_t;
OPD_s sub_0x13409B4_t = { 0x13409B4, 0x1C85330 };
void(*sub_0x13409B4)(int r3, int r4) = (void(*)(int, int))&sub_0x13409B4_t;
int DisconnectKickTIME;
OPD_s Parser5 = { 0x12F3CB0, 0x1C85330 };
OPD_s Parser6 = { 0x47DF9C, 0x1C85330 };
uint32_t(*sub_012f3d50)(uint32_t r3) = (uint32_t(*)(uint32_t))&Parser5;
int(*handle_cnet)(int r3, int r4) = (int(*)(int, int))&Parser6;

void DisconnectKick(int P)
{
	if (GAMEPLAY::GET_GAME_TIMER() > DisconnectKickTIME)
	{
		sub_0x9F81F8(P);
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(P)))
		{
			int KICK = sub_0x9F8870(P);
			sub_012f3d50(handle_cnet(P, 1));
			sub_0x13409B4(0x222D970, KICK);
		}
		DisconnectKickTIME = GAMEPLAY::GET_GAME_TIMER() + 10000;
	}
	else
	{
		addMessageShow("[キック]数秒後に再度お試しください。");
	}
}
#pragma endregion

#pragma region WeaponMenu
void UnlimitedAmmo(bool toggle)
{
	if (toggle)
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

void Set_WeaponGroup(uint address, uint group = 0x18D5FA97)
{
	if (address != 0)
	{
		PS3::WriteUInt32(address + Group, group);
		addMessageShow("セット完了");
	}
	else
	{
		addMessageShow("オフセット検索が失敗しています。");
	}
}

void KnifeRedLaser(char* LASER = "VEHICLE_WEAPON_ENEMY_LASER", int ExplosionType = 5)
{
	int APOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_APPISTOL"));
	int Weapon1 = PS3::ReadInt32(APOffset + WeaponFlags1);
	int Weapon2 = PS3::ReadInt32(APOffset + WeaponFlags2);
	int Weapon3 = PS3::ReadInt32(APOffset + WeaponFlags3);
	int Weapon4 = PS3::ReadInt32(APOffset + Group);
	int APRange = PS3::ReadInt32(APOffset + WeaponRange);
	//printf("Step1\n");

	Hash _hash = GAMEPLAY::GET_HASH_KEY(LASER);
	uint _hashoffset = GET_WEAPONS(_hash);
	//printf("Step2\n");
	Hash _Knife = GAMEPLAY::GET_HASH_KEY("WEAPON_KNIFE");
	uint _KnifeOffset = GET_WEAPONS(_Knife);
	//printf("Step3\n");
	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(_hash))
	{
		WEAPON::REQUEST_WEAPON_ASSET(_hash, 31, 0);
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(_hash));
	}
	//printf("Step4\n");
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _hash, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _hash, -1, true, true);
	WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), _hash, -1);
	//printf("Step5\n");
	int AmmoOffset = PS3::ReadInt32(_hashoffset + AmmoInfo);
	int NoobOffset = PS3::ReadInt32(_KnifeOffset + AmmoInfo);

	int HeavyOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"));
	
	//printf("Step6\n");


	PS3::WriteInt32(_KnifeOffset + WeaponFlags1, Weapon1);
	PS3::WriteInt32(_KnifeOffset + WeaponFlags2, Weapon2);
	PS3::WriteInt32(_KnifeOffset + WeaponFlags3, Weapon3);
	PS3::WriteInt32(_KnifeOffset + Group, Weapon4);
	PS3::WriteUInt32(AmmoOffset + Explosion_Default, ExplosionType);
	PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
	PS3::WriteUInt32(_hashoffset + FireType, 4);
	PS3::WriteUInt32(_KnifeOffset + FireType, 4);
	PS3::WriteUInt32(_KnifeOffset + AmmoInfo, AmmoOffset);
	PS3::WriteUInt32(_KnifeOffset + WeaponRange, APRange);
	PS3::WriteInt32(_KnifeOffset + DamageType, 0x40A00000);
	if (NoobOffset != 0)
	{
		PS3::WriteUInt32(NoobOffset + Explosion_Default, ExplosionType);
		PS3::WriteUInt32(NoobOffset + ProjectileFlags, 4);
	}
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _Knife, -1, true, true);
	//printf("Step7\n");
}

void ba_ruLaser(char* LASER = "VEHICLE_WEAPON_PLAYER_LASER", int ExplosionType = 5)
{
	int APOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_APPISTOL"));
	int Weapon1 = PS3::ReadInt32(APOffset + WeaponFlags1);
	int Weapon2 = PS3::ReadInt32(APOffset + WeaponFlags2);
	int Weapon3 = PS3::ReadInt32(APOffset + WeaponFlags3);
	int Weapon4 = PS3::ReadInt32(APOffset + Group);
	Hash _hash = GAMEPLAY::GET_HASH_KEY(LASER);
	uint _hashoffset = GET_WEAPONS(_hash);

	Hash _Knife = GAMEPLAY::GET_HASH_KEY("WEAPON_CROWBAR");
	uint _KnifeOffset = GET_WEAPONS(_Knife);

	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(_hash))
	{
		WEAPON::REQUEST_WEAPON_ASSET(_hash, 31, 0);
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(_hash));
	}

	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _hash, 0, false);
	WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), _hash, -1, true, true);
	WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), _hash, -1);

	int AmmoOffset = PS3::ReadInt32(_hashoffset + AmmoInfo);
	int NoobOffset = PS3::ReadInt32(_KnifeOffset + AmmoInfo);

	int HeavyOffset = GET_WEAPONS(GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"));

	int APRange = PS3::ReadInt32(APOffset + WeaponRange);

	PS3::WriteInt32(_KnifeOffset + WeaponFlags1, Weapon1);
	PS3::WriteInt32(_KnifeOffset + WeaponFlags2, Weapon2);
	PS3::WriteInt32(_KnifeOffset + WeaponFlags3, Weapon3);
	PS3::WriteInt32(_KnifeOffset + Group, Weapon4);
	PS3::WriteUInt32(AmmoOffset + Explosion_Default, ExplosionType);
	PS3::WriteUInt32(AmmoOffset + ProjectileFlags, 4);
	PS3::WriteUInt32(_hashoffset + FireType, 4);
	PS3::WriteUInt32(_KnifeOffset + FireType, 4);
	PS3::WriteUInt32(_KnifeOffset + AmmoInfo, AmmoOffset);
	PS3::WriteUInt32(_KnifeOffset + WeaponRange, APRange);
	PS3::WriteInt32(_KnifeOffset + DamageType, 0x40A00000);
	if (NoobOffset != 0)
	{
		PS3::WriteUInt32(NoobOffset + Explosion_Default, ExplosionType);
		PS3::WriteUInt32(NoobOffset + ProjectileFlags, 4);
	}
}

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

bool RequestBullet(int BulletHash)
{
	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(BulletHash))
	{
		WEAPON::REQUEST_WEAPON_ASSET(BulletHash, 31, 0);
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(BulletHash));
	}
}
#pragma endregion

#pragma region フライングカー
int Backup;
int Backup2; //0x402C0A98 handler
void FreezeHeli(int address)
{
	if (Backup == 0x00 && Backup2 == 0x00)
	{
		Backup = PS3::ReadUInt32(address);
		Backup2 = PS3::ReadUInt32(address + 0x04);
	}
	char bytes31[] = { 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04 };
	PS3::WriteBytes(address, bytes31, 8);
}

void FreezeHiko(int address)
{
	char bytes13[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04 };
	PS3::WriteBytes(address, bytes13, 8);
	//drawNotification("全車両飛行機化セット!!");

}
#pragma endregion

#pragma region UI
void do_ChangeHUD(int hud_id, RGBA _rgba)
{
	remote_native_arg[0] = hud_id;
	remote_native_arg[1] = _rgba.R;
	remote_native_arg[2] = _rgba.G;
	remote_native_arg[3] = _rgba.B;
	remote_native_arg[4] = _rgba.A;
	remote_native_arg[5] = 0;
	remote_native_arg[6] = 0;
	remote_native_arg[7] = 0;
	remote_native_arg[8] = 0;
	remote_native_arg[9] = 0;
	call_remote_native_onAddress(selectedPlayer, 0x01579CD8, 5);
}
#pragma endregion

#pragma region VehicleMenu
void _VehicleGodmode(int playerPed, bool GodmodeOn)
{
	int vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	ENTITY::SET_ENTITY_INVINCIBLE(vehicle, GodmodeOn); //That should do the trick.
	ENTITY::SET_ENTITY_PROOFS(vehicle, GodmodeOn, GodmodeOn, GodmodeOn, GodmodeOn, GodmodeOn, GodmodeOn, GodmodeOn, GodmodeOn);
	VEHICLE::SET_VEHICLE_STRONG(vehicle, GodmodeOn); //2stronk
	VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, !GodmodeOn); //I don't think this really works, but fuck it. Call it anyway.
	VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, !GodmodeOn); //Hopefully this fixes the car blowing up after getting hit by a train...
	VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, !GodmodeOn);
}

void CARFIX(int player = PLAYER::PLAYER_ID())
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
	VEHICLE::SET_VEHICLE_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 1);
	WEAPON::CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Vehicle);
}
#pragma endregion

void Engine_Thread2(uint64_t)
{
	printf("Thread Started!\n");

	printf("Thread Closed\n");
}

void much4uLoop()
{
	//Invisible
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !Invisible);


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

		if (TeleportCameraSelf)
		{
			Ped ped = PLAYER::PLAYER_PED_ID();
			Entity entityToTele = ped;
			if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
				entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
			ENTITY::SET_ENTITY_COORDS(entityToTele, PosX, PosY, PosZ, false, false, false, true);
			STREAMING::LOAD_ALL_OBJECTS_NOW();
			TeleportCameraSelf = false;
		}
	}
}

void otherLoop()
{
	
#pragma region Player_Option
	if (PlayerInfoTimer < GAMEPLAY::GET_GAME_TIMER())
	{
		if (_PlayerUI && PlayerUI)
		{
			if (submenu == PlayerList)
			{
				PlayerInformationUI(PlayerListIndexes[currentOption - 1]);
			}
			else if (submenu == Closed)
			{

			}
			else
			{
				PlayerInformationUI(selectedPlayer);
			}
		}

		if (ObjectUI)
		{
			if (submenu == Spawned_Object_s)
			{
				if (currentOption < 40)
				{
					ObjectInformationUI(SpawnedEntityList[currentOption -1 ], SpawnedEntityName[currentOption - 1], currentOption - 1);
				}
			}
			else if (submenu == Closed)
			{

			}
			else
			{
				ObjectInformationUI(SpawnedSelectedEntity, _SelectedEntity, SpawnedEntityIndex);
			}
		}
		PlayerInfoTimer = GAMEPLAY::GET_GAME_TIMER() + 15;

		if (msgindexflag)
		{
			if (MsgTimer < GAMEPLAY::GET_GAME_TIMER())
			{
				MsgOpacity = 0;
				msgindexflag = false;
			}
			else
			{
				//GRAPHICS::DRAW_RECT(msgWindow[0], msgWindow[1], msgWindow[2], msgWindow[3], 30, 30, 30, MsgOpa);
				drawText(MsgInfoBuf[0], 0, msgXcoord, msgYcoord + 0.00f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[1], 0, msgXcoord, msgYcoord + 0.03f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[2], 0, msgXcoord, msgYcoord + 0.06f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[3], 0, msgXcoord, msgYcoord + 0.09f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[4], 0, msgXcoord, msgYcoord + 0.12f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[5], 0, msgXcoord, msgYcoord + 0.15f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[6], 0, msgXcoord, msgYcoord + 0.18f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[7], 0, msgXcoord, msgYcoord + 0.21f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[8], 0, msgXcoord, msgYcoord + 0.24f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
				drawText(MsgInfoBuf[9], 0, msgXcoord, msgYcoord + 0.27f, 0.35, 0.35, 255, 255, 255, MsgOpacity, false, false, true);
			}
		}
	}
#pragma endregion
}
#define NOP 0x4E800020
#define R_NOP 0x7C0802A6
#pragma region AAA
ObjAttach Obj;

void SelfOptionAutoON()
{
	GodMode = true;
	Nocops = true;
	SuperJump = true;
	SuperRun = true;
	InfAmmo1 = true;
	Protection_AutoON();
	addMessageShow("オンにしました！");
}

void SelfOptionAutoOff()
{
	GodMode = false;
	Nocops = false;
	SuperJump = false;
	SuperRun = false;
	InfAmmo1 = false;
	WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 0);
	Protection_AutoOFf();
	addMessageShow("オフにしました！");
}
#pragma endregion

#pragma region Rank偽装
void SpoofRank(int Rank)
{
	PS3::Write_Global(1581952 + (PLAYER::PLAYER_ID() * 306), Rank);
}
#pragma endregion
char redxserver[50];
sys_ppu_thread_t threadId[2];
bool _chat = true;
bool _chat_send;
int Chat_ThreadTIME;
char Chat_Buf[100][5];
bool TASK_PLAY_ANIM_PAIX(Ped Ped, char *AnimDict, char *Anim)
{
	STREAMING::REQUEST_ANIM_DICT(AnimDict);
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
	{
		AI::TASK_PLAY_ANIM(Ped, AnimDict, Anim, 8.0f, 4.0f, -1, 49, 0.0f, false, false, false);
		return true;
	}
	else
		return false;
}
sys_ppu_thread_t create_threadchat(void(*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{
	sys_ppu_thread_t idchat;
	if (sys_ppu_thread_create(&idchat, entry, 0, priority, stacksize, 0, threadname) != CELL_OK)
	{
		//printf("チャットスレッド作成エラー\n");
	}
	else
	{
		//printf("チャットスレッド作成\n");
	}
	return idchat;
}
bool _threadFlag = true;
bool sendFlag;
void Thread2(uint64_t a)
{
	if (_chat_send)
	{
		SocketRequest(redxserver, (char*)0x1005CCD0);
		_chat_send = false;
		sleep(250);
	}

	if (_chat)
	{
		char *p1 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=1");
		if (!strstr((char*)0x10050860, p1))
		{
			memcpy((void*)0x10050400, (char*)0x10050520, 100);
			memcpy((void*)0x10050520, (char*)0x10050640, 100);
			memcpy((void*)0x10050640, (char*)0x10050760, 100);
			memcpy((void*)0x10050760, (char*)0x10050860, 100);
			memcpy((void*)0x10050860, p1, 100);
		}
		/*char *p5 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=5");
		memcpy((void*)0x10050400, p5, 100);
		sleep(25);
		char *p4 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=4");
		memcpy((void*)0x10050520, p4, 100);
		sleep(25);
		char *p3 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=3");
		memcpy((void*)0x10050640, p3, 100);
		sleep(25);
		char *p2 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=2");
		memcpy((void*)0x10050760, p2, 100);
		sleep(25);
		char *p1 = SocketRequest(redxserver, "Redirect_REDX.php?CMD=GET_CHAT&VAR2=1");
		memcpy((void*)0x10050860, p1, 100);*/
	}
	sys_ppu_thread_exit(a);
}

float chatX = 0.3300, chatY = 0.0530;

void Functions()
{
	if (_chat && isOnline())
	{
		if (GAMEPLAY::GET_GAME_TIMER() > Chat_ThreadTIME) {	
			create_threadchat(Thread2, 10, 0x10, "[Zedd Dx]Chat Thread");
			Chat_ThreadTIME = GAMEPLAY::GET_GAME_TIMER() + 10000;
			sendFlag = false;
		}
		drawText2("< Zedd & Dx Chat > (ベータ)", 0, chatX, chatY - 0.03, 0.4, 0.4, 222, 0, 222, 255, false, true, true);
		drawText2((char*)0x10050400, 0, chatX, chatY + (0.03 * 0), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		drawText2((char*)0x10050520, 0, chatX, chatY + (0.03 * 1), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		drawText2((char*)0x10050640, 0, chatX, chatY + (0.03 * 2), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		drawText2((char*)0x10050760, 0, chatX, chatY + (0.03 * 3), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		drawText2((char*)0x10050860, 0, chatX, chatY + (0.03 * 4), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		if (sendFlag) {
			char buf[100];
			snprintf(buf, 100, "チャット更新まで : %ims", Chat_ThreadTIME - GAMEPLAY::GET_GAME_TIMER());
			drawText2(buf, 0, chatX, chatY + (0.03 * 5), 0.4, 0.4, 255, 255, 255, 255, false, true, true);
		}
	}

	if (_UIGET)
	{
		for (int i = 0; i < 224; i++)
		{
			UI::GET_HUD_COLOUR(i, &_UIGETRGBA[i].R, &_UIGETRGBA[i].G, &_UIGETRGBA[i].B, &_UIGETRGBA[i].A);
		}
		_UIGET = false;
	}
	//DragonFire::Functions2();
	//DragonFire::Functions();

	//Super_Run(SuperRun);

	if (kasamod)
	{
		if (isPressed(Button_L3))
		{
			TASK_PLAY_ANIM_PAIX(PLAYER::PLAYER_PED_ID(), "amb@code_human_wander_drinking@male@base", "base");
		}
		if (isPressed(Button_R3))
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			ENTITY::DETACH_ENTITY(KASA, false, false);
			ENTITY::DELETE_ENTITY1(&KASA);
			kasamod = false;
		}
	}

	if (Spectatormode)
	{
		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(SpectatormodePlayer))
		{
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, PLAYER::GET_PLAYER_PED(SpectatormodePlayer));
			SpectatormodePlayer = 0;
			Spectatormode = false;
		}
	}

	if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");

	if (InfAmmo0)
	{
		//*(int*)0x10064300 = 0; // Weapon Hash
		//*(int*)0x10064304 = 0; // Current Ammo
		//*(int*)0x1006430C = 0; // Player Ped id
		//*(int*)0x10064308 = 0; // Max Ammo
		//*(int*)0x10064310 = 0;

		//*(int*)0x1006430C = PLAYER::PLAYER_PED_ID();
		//*(int*)0x10064300 = WEAPON::GET_SELECTED_PED_WEAPON(*(int*)0x1006430C);
		//*(int*)0x10064308 = WEAPON::GET_MAX_AMMO(*(int*)0x1006430C, *(int*)0x10064300, (int*)0x10064310);

		*(int*)0x10064300 = PLAYER::PLAYER_PED_ID();
		*(int*)0x10064304 = WEAPON::GET_SELECTED_PED_WEAPON(*(int*)0x10064300);
		*(int*)0x10064308 = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(*(int*)0x10064300, *(int*)0x10064304);
		int maxammo;
		WEAPON::SET_PED_AMMO_BY_TYPE(PLAYER::PLAYER_PED_ID(), *(int*)0x10064308, 9999);
		//WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), &maxammo);
		//WEAPON::SET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), maxammo);
	}

	if (_SpoofRank)
		SpoofRank(_SpoofRankVar);

	if (SuperRun)
		Script_Inject::SET_PLAYER_SPEED_MODIFIER(SuperRun_, PLAYER::PLAYER_ID());
	//if (SuperRun)
	//	PS3::WriteFloat(0x411433DC, 1.50f);

#pragma region その他
	/*PS3::WriteUInt32(NETWORK_CRC_HASH_CHECK_EVENT, 0x4E800020);
	PS3::WriteUInt32(PICKUP_DESTROYED_EVENT, 0x4E800020);
	PS3::WriteUInt32(UPDATE_PLAYER_SCARS_EVENT, 0x4E800020);
	PS3::WriteUInt32(NETWORK_CHECK_EXE_SIZE_EVENT, 0x4E800020);
	PS3::WriteUInt32(NETWORK_CHECK_CODE_CRCS_EVENT, 0x4E800020);
	PS3::WriteUInt32(REPORT_CASH_SPAWN_EVENT, 0x4E800020);*/

	/*FPS*/
	if (frameCache_time + 1000 < GAMEPLAY::GET_GAME_TIMER())
	{
		frameCache_time = GAMEPLAY::GET_GAME_TIMER();
		frameCache_old = frameCache_new;
		frameCache_new = GAMEPLAY::_GET_FRAME_COUNT();
	}
	int fps = frameCache_new - frameCache_old - 1;

	for (int i = 0; i < 16; i++)
	{
		if (i != PLAYER::PLAYER_ID())
		{
			if (TimerDelay[i] < GAMEPLAY::GET_GAME_TIMER())
			{
				if (ALL_PLAYER_40K || MoneyFlag[i])
				{
					REQUEST_MODEL(0x113FD533);
					if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
					{
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true);
						coords.z = coords.z + DropPlusZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z, 0, 40000, 0x113FD533, 0, 1);
					}
				}

				if (ParachuteFlag[i])
				{
					REQUEST_MODEL(0x6773257D);
					if (STREAMING::HAS_MODEL_LOADED(0x6773257D))
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + DropPlusZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0x6773257D, mycoords.x, mycoords.y, mycoords.z, 0, 0, 1, 0, 1);
					}
				}
				
				if (DropSnackFlag[i])
				{
					REQUEST_MODEL(0x6773257D);
					if (STREAMING::HAS_MODEL_LOADED(0x6773257D))
					{
						Vector3 mycoords = get_entity_coords_orig(PLAYER::GET_PLAYER_PED(i), true);
						mycoords.z = mycoords.z + DropPlusZ;
						OBJECT::CREATE_AMBIENT_PICKUP(0x6773257D, mycoords.x, mycoords.y, mycoords.z, 0, GAMEPLAY::GET_HASH_KEY("prop_ld_snack_01"), 15, 0, 1);
					}
				}

				if (ModdedWeapon_var[i])
				{
					Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					bool isCoord = __GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000);
					if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)))
					{
						switch (ModdedWPvar)
						{
						case 0:
							if (isCoord)
								TPofScene(PLAYER::GET_PLAYER_PED(i), *(Vector3*)0x10031000, "mini@strip_club@private_dance@part3", "priv_dance_p3", false);
							break;
						case 1:
							if (isCoord)
								FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 29, 0.5f, true, false, 0);
							
							break;
						case 2:
							if (isCoord)
								FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_DIR_FLAME, 5.0, 1, 0, 0);
							break;
						case 3:
							if (isCoord)
								FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_DIR_WATER_HYDRANT, 5.0, 1, 0, 0);
							break;
						case 4:
							if (isCoord)
							{						
								REQUEST_MODEL(0x113FD533);
								if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
								{
									OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 0, 40000, 0x113FD533, 0, 1);
								}
								
							}
							else
							{
								Vector3 AAX = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(i), 0, 1, 0);
								OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, AAX.x, AAX.y, AAX.z, 0, 40000, 0x113FD533, 0, 1);
							}
							break;
						case 5:
							if (isCoord)
								FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_FLARE, 5.0, 1, 0, 0);
							break;
						case 6:
							if (isCoord)
								FIRE::ADD_EXPLOSION(((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, EXPLOSION_BIRD_CRAP, 5.0, 1, 0, 0);
							break;

						}
					}
				}

				TimerDelay[i] + 100;
			}

			if (ALL_ANIMATION_KILL)
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
				AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED(i));
			}
		}
		else
		{
			if (TimerDelay[i] < GAMEPLAY::GET_GAME_TIMER())
			{
				if (MoneyGunMe)
				{
					bool isCoord = __GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000);
					if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)) && isCoord)
					{
						REQUEST_MODEL(0x113FD533);
						if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
						{
							OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ((Vector3*)0x10031000)->x, ((Vector3*)0x10031000)->y, ((Vector3*)0x10031000)->z, 0, 40000, 0x113FD533, 0, 1);
						}
					}
				}

				if (TeleportGunMe)
				{
					bool isCoord = __GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), (Vector3*)0x10031000);
					if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i)) && isCoord)
					{
						TP(PLAYER::PLAYER_PED_ID(), *(Vector3*)0x10031000);
					}
				}
			}
		}


		if (ESP_BOOL_[i] && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			ESP_BOOL_[i] = false;
			

		if (ALL_ESP || ESP_BOOL_[i])
		{
			if (!(submenu == PlayerList && (currentOption - 1) == i))
				_doESP(i);
		}

		if (RemoveAllPlayerWanted)
		{
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(i) != 0)
			{
				int args[2];
				args[0] = 356;
				args[1] = i;
				TriggerScriptEvent(args, 3, i);
			}
		}
		//ESP_BOOL_[i] = false;
	}

#pragma endregion

#pragma region SelfOption Func
	//GodMode
	if (GodMode) {
		*(int*)0x10060000 = PLAYER::PLAYER_ID();
		uint uVar1 = Script_Inject::_PlayerIndexToPlayerAddress(*(int*)0x10060000);
		if (0x10000 < (uVar1 & 0xffffffff)) {
			*(uint*)(uVar1 + 0x170) = 0x7f7fffff;
			*(uint*)(uVar1 + 0x174) = 0x7f7fffff;
		}

		*(int*)0x10060004 = PLAYER::PLAYER_PED_ID();
		PED::SET_PED_CAN_RAGDOLL(*(int*)0x10060004, 0);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(*(int*)0x10060004, 0);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(*(int*)0x10060004, 1);
		ENTITY::SET_ENTITY_PROOFS(*(int*)0x10060004, 1, 1, 1, 1, 1, 0, 0, 0);
		ENTITY::SET_ENTITY_INVINCIBLE(*(int*)0x10060004, 1);
		//ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 1, 1, 1, 1, 1, 0, 0, 0);
		//ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
	}

	if (NoRagdoll)
	{
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), 1, 1, 1, 1, 1, 0, 0, 0);
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), 0);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), 0);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), 1);
	}

	//手配度無効
	if (Nocops) {
		NoCops(Nocops);
	}

	//スーパージャンプ
	if (SuperJump)
	{
		//Script_Inject::SuperJumper(PLAYER::PLAYER_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	//スーパーラン

	if (UltraRun)
	{
		if (isPressed(Button_A))
		{
			ApplyForce(PLAYER::PLAYER_PED_ID(), newVector3(0, 10, 0), newVector3(0, 0, 0));
		}
	}
	//爆発パンチ
	if (ExplosionMelee)
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());

	//浮遊
	if (Noclip[1]) {
		if (Analog(189) > 127 || Analog(189) < 127 || Analog(188) > 127 || Analog(188) < 127)
		{
			Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

			int Vehiclee = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0),
				ent = Vehiclee == 0 ? PLAYER::PLAYER_PED_ID() : Vehiclee;

			ENTITY::SET_ENTITY_COLLISION(ent, true, 1); 
			Vector3 camvt = CAM2::GET_COORDS_FROM_CAM(10.0f);
			ENTITY::FREEZE_ENTITY_POSITION(ent, true);

			if (ent == Vehiclee)
				if (ent == PLAYER::PLAYER_PED_ID())
				{
					ENTITY::SET_ENTITY_COLLISION(ent, false, 0);
				}
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, camvt.x, camvt.y, camvt.z, 0, 0, 0);
		}
	}
#pragma endregion

#pragma region Player_Option
	if (_GetHost)
	{
		if (NETWORK::NETWORK_IS_IN_SESSION() && NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) != PLAYER::PLAYER_ID())
		{
			if (AutoHost < GAMEPLAY::GET_GAME_TIMER())
			{
				getHostOfThisScript();
				AutoHost = GAMEPLAY::GET_GAME_TIMER() + 5000;
			}
		}
	}

	if (Obj.flag)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Obj._Hash))
		{
			if (!STREAMING::HAS_MODEL_LOADED(Obj._Hash))
				REQUEST_MODEL(Obj._Hash);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(Obj._Spawned))
					Obj._Spawned = OBJECT::CREATE_OBJECT(Obj._Hash, Obj._Loc.x, Obj._Loc.y, Obj._Loc.z + 20, true, true, false);
				else
				{
					if (!ENTITY::IS_ENTITY_ATTACHED(Obj._Spawned))
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Obj._Spawned, Obj._Entity, Obj._Bone, Obj._Loc.x, Obj._Loc.y, Obj._Loc.z, Obj._Rot.x, Obj._Rot.y, Obj._Rot.z, 1, 1, Obj.Collision, 1, 1, 1);
					else
					{
						Last_Object = Obj._Spawned;
						TestAttach_Loc = Obj._Loc;
						TestAttach_Rot = Obj._Rot;
						Bone = Obj._Bone;
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Obj._Hash);
						addMessageShow("アタッチが完了しました。");
						Obj.flag = false;
					}
				}
			}
		}
		else
		{
			addMessageShow("モデルの読み込みに失敗しました。");
			Obj.flag = false;
		}
	}

	if (Freezing_V1)
	{
		if (!Freezing_V1_Time)
		{
			uint Handle = PLAYER::PLAYER_PED_ID();
			Vector3 c = ENTITY::GET_ENTITY_COORDS(Handle, 1);
			int hash = GAMEPLAY::GET_HASH_KEY("handler");
			REQUEST_MODEL(hash);
			if (STREAMING::HAS_MODEL_LOADED(hash))
			{
				FreezingVehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z + 100, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(FreezingVehicle))
				{
					VEHICLE::SET_VEHICLE_ENGINE_ON(FreezingVehicle, true, 1);
					//PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
					Freezing_V1_Time = true;
					Freezing_V1_Timer = GAMEPLAY::GET_GAME_TIMER() + 6000;
					Freezing_V1 = false;
				}
			}
		}
		else
		{
			if (Freezing_V1_Timer < GAMEPLAY::GET_GAME_TIMER())
			{
				DeleteEntity(FreezingVehicle);
				FreezingVehicle = 0;
				addMessageShow("~b~フリーズ完了");
				Freezing_V1_Time = false;
				Freezing_V1 = false;
			}
		}
	}

	if (Freezing_V2)
	{
		if (!Freezing_V2_Time)
		{
			*(int*)0x9FB2E8 = 0x60000000;
			Freezing_V2_Timer = GAMEPLAY::GET_GAME_TIMER() + 6000;
			Freezing_V2_Time = true;
		}
		else
		{
			if (Freezing_V2_Timer < GAMEPLAY::GET_GAME_TIMER())
			{
				*(int*)0x9FB2E8 = 0x4E9E0421;
				Freezing_V2_Time = false;
				Freezing_V2 = false;
				addMessageShow("~b~フリーズ完了");
			}
		}
	}

	if (Freezing_V3)
	{
		if (!Freezing_V3_Time)
		{
			*(int*)0xA8C2B8 = 0x4E800020;
			Freezing_V3_Timer = GAMEPLAY::GET_GAME_TIMER() + 1000;
			Freezing_V3_Time = true;
		}
		else
		{
			if (Freezing_V3_Timer < GAMEPLAY::GET_GAME_TIMER())
			{
				*(int*)0xA8C2B8 = 0x7C0802A6;
				Freezing_V3_Time = false;
				addMessageShow("~b~フリーズ完了");
			}
		}
	}

	if (IsInAutoApply)
	{
		int _vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
		if (_vehicle != 0)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_vehicle);
			ApplyForce(_vehicle, newVector3(0, 100, 0), newVector3(100, 0, 0));
		}
	}

	if (SpoofKasuAll[0])
	{
		if (SpoofKasuIndex[0] >= 16)
			SpoofKasuAll[0] = false;

		if (SpoofKasuTimer[0] < GAMEPLAY::GET_GAME_TIMER())
		{
			SendSpoofedMessage(selectedNamedPlayer, SpoofKasuIndex[0], "<font size = '150'>カス");
			SpoofKasuTimer[0] = GAMEPLAY::GET_GAME_TIMER() + 150;
		}


	}

	if (SpoofKasuAll[1])
	{
		if (SpoofKasuIndex[1] >= 16)
			SpoofKasuAll[1] = false;

		if (SpoofKasuTimer[1] < GAMEPLAY::GET_GAME_TIMER())
		{
			
			SendSpoofedMessage(SpoofKasuIndex[1], SpoofKasuIndex[1], "<font size = '150'>カス");
			SpoofKasuTimer[1] = GAMEPLAY::GET_GAME_TIMER() + 150;
		}


	}

	if (do_Fence)
	{
		Vector6 small_vector[] = { { -1.7,-0.5,-0.5,0,0,0 }, { 0.7,-1.7,-0.5,0,0,90 }, { 1.8,0.7,-0.5,0,0,180 },{ -0.7,1.7,-0.5,0,0,270 } };
		Vector6 middle_vector[] = { { -1.7,-1.7,-0.5,0,0,0 }, { 1.7,-1.7,-0.5,0,0,90 }, { 1.7,1.7,-0.5,0,0,180 }, { -1.7,1.7,-0.5,0,0,270 } };
		Vector6 big_vector[] = { { -3.5,-3.7,-0.5,0,0,0 }, { 0,-3.7,-0.5,0,0,0 }, { 3.4,-3.7,-0.5,0,0,90 }, { 3.4,-0.2,-0.5,0,0,90 }, { 3.4,3.2,-0.5,0,0,180 }, { -0.1,3.2,-0.5,0,0,180 }, { -3.5,-0.3,-0.5,0,0,270 }, { -3.5,3.2,-0.5,0,0,270 } };

		//Vector3 P_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		Hash prop_fnclink_05b = GAMEPLAY::GET_HASH_KEY("prop_fnclink_05b");
		REQUEST_MODEL(prop_fnclink_05b);
		switch (SmallBigVar)
		{
		case 0:
			if (!ENTITY::DOES_ENTITY_EXIST(do_Fence_Int[do_Fence_index]))
			{
				Vector3 P_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
				P_Coord.x += small_vector[do_Fence_index].Lx;
				P_Coord.y += small_vector[do_Fence_index].Ly;
				P_Coord.z += small_vector[do_Fence_index].Lz;
				//Vector3 P_Coord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), small_vector[do_Fence_index].Lx, small_vector[do_Fence_index].Ly, small_vector[do_Fence_index].Lz);
				do_Fence_Int[do_Fence_index] = OBJECT::CREATE_OBJECT(prop_fnclink_05b, P_Coord.x, P_Coord.y, P_Coord.z, true, true, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(do_Fence_Int[do_Fence_index], 1, 1);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(do_Fence_Int[do_Fence_index]);
				freeze_entity_position(do_Fence_Int[do_Fence_index], true);
			}
			else
			{
				ENTITY::SET_ENTITY_ROTATION(do_Fence_Int[do_Fence_index], small_vector[do_Fence_index].Rx, small_vector[do_Fence_index].Ry, small_vector[do_Fence_index].Rz, 2, 1);
				do_Fence_index++;
			}

			if (do_Fence_index > 3)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_fnclink_05b);
				do_Fence_index = 0;
				do_Fence = false;
			}
			break;

		case 1:
			if (!ENTITY::DOES_ENTITY_EXIST(do_Fence_Int[do_Fence_index]))
			{
				Vector3 P_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
				P_Coord.x += middle_vector[do_Fence_index].Lx;
				P_Coord.y += middle_vector[do_Fence_index].Ly;
				P_Coord.z += middle_vector[do_Fence_index].Lz;
				//Vector3 P_Coord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), middle_vector[do_Fence_index].Lx, middle_vector[do_Fence_index].Ly, middle_vector[do_Fence_index].Lz);
				do_Fence_Int[do_Fence_index] = OBJECT::CREATE_OBJECT(prop_fnclink_05b, P_Coord.x, P_Coord.y, P_Coord.z, true, true, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(do_Fence_Int[do_Fence_index], 1, 1);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(do_Fence_Int[do_Fence_index]);
				freeze_entity_position(do_Fence_Int[do_Fence_index], true);
			}
			else
			{
				ENTITY::SET_ENTITY_ROTATION(do_Fence_Int[do_Fence_index], middle_vector[do_Fence_index].Rx, middle_vector[do_Fence_index].Ry, middle_vector[do_Fence_index].Rz, 2, 1);
				do_Fence_index++;
			}

			if (do_Fence_index > 3)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_fnclink_05b);
				do_Fence_index = 0;
				do_Fence = false;
			}

			break;

		case 2:
			if (!ENTITY::DOES_ENTITY_EXIST(do_Fence_Int[do_Fence_index]))
			{
				Vector3 P_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
				P_Coord.x += big_vector[do_Fence_index].Lx;
				P_Coord.y += big_vector[do_Fence_index].Ly;
				P_Coord.z += big_vector[do_Fence_index].Lz;
				//Vector3 P_Coord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), big_vector[do_Fence_index].Lx, big_vector[do_Fence_index].Ly, big_vector[do_Fence_index].Lz);
				do_Fence_Int[do_Fence_index] = OBJECT::CREATE_OBJECT(prop_fnclink_05b, P_Coord.x, P_Coord.y, P_Coord.z, true, true, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(do_Fence_Int[do_Fence_index], 1, 1);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(do_Fence_Int[do_Fence_index]);
				freeze_entity_position(do_Fence_Int[do_Fence_index], true);
			}
			else
			{
				ENTITY::SET_ENTITY_ROTATION(do_Fence_Int[do_Fence_index], big_vector[do_Fence_index].Rx, big_vector[do_Fence_index].Ry, big_vector[do_Fence_index].Rz, 2, 1);
				do_Fence_index++;
			}

			if (do_Fence_index > 7)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_fnclink_05b);
				do_Fence_index = 0;
				do_Fence = false;
			}

			break;
		}
	}

	if (RCE_ChangeRank)
	{
		if (RCE_ChangeRankVar == 0)
		{
			switch (RCE_ChangeRankIndex)
			{
			case 0:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MP0_SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar - 1];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				RCE_ChangeRankIndex++;
				break;

			case 1:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar - 1];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				RCE_ChangeRankIndex++;
				break;

			case 2:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MP1_SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar - 1];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				RCE_ChangeRankIndex++;
				break;

			case 3:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MP1_CHAR_SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar - 1];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				RCE_ChangeRankIndex++;
				break;

			case 4:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MPPLY_IS_HIGH_EARNER");
				remote_native_arg[1] = 0;
				remote_native_arg[2] = 0;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				RCE_ChangeRankIndex++;
				break;

			case 5:
				RCE_ChangeRankIndex = 0;
				RCE_ChangeRankVar = 0;
				RCE_ChangeRank = false;
				SooofMessage(selectedPlayer, "ランク変更しました!");
				addMessageShow("ランクセットしました！");
				break;
			}	
			RCE_ChangeRankVar = 25;
		}
		else
		{
			RCE_ChangeRankVar--;
		}


		/*if (RCE_ChangeRankVar == 0)
		{
			switch (RCE_ChangeRankIndex)
			{
			case 0:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				break;
			case 1:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("CHAR_SET_RP_GIFT_ADMIN");
				remote_native_arg[1] = Ranks[RankVar];
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				break;
			case 2:
				remote_native_arg[0] = GAMEPLAY::GET_HASH_KEY("MPPLY_IS_HIGH_EARNER");
				remote_native_arg[1] = 0;
				remote_native_arg[2] = 0;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_STAT_SET_INT, 3);
				break;

			case 3:
				RCE_ChangeRankIndex = 0;
				RCE_ChangeRankVar = 0;
				RCE_ChangeRank = false;
				SooofMessage(selectedPlayer, "ランク変更しました!");
				break;
			}
			RCE_ChangeRankIndex++;
			RCE_ChangeRankVar = 250;
		}
		else
			RCE_ChangeRankVar--;*/
	}

	if (_playerwantedbool)
	{
		PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(selectedPlayer, true);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(selectedPlayer, true);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NO_DROP(selectedPlayer, true, 5);
		PLAYER::SET_PLAYER_WANTED_LEVEL(selectedPlayer, 5, true);
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(5);
		PLAYER::SET_WANTED_LEVEL_DIFFICULTY(selectedPlayer, 5);
		PLAYER::REPORT_CRIME(selectedPlayer, 36, PLAYER::GET_WANTED_LEVEL_THRESHOLD(5));
	}

	if (_setwantedbool)
	{
		if (_SetPlayerWantedTimer == 0)
		{
			switch (_SetPlayerWantedIndex)
			{
			case 0:
				remote_native_arg[0] = 5;
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

				_SetPlayerWantedIndex++;
				break;

			case 1:
				remote_native_arg[0] = selectedPlayer;
				remote_native_arg[1] = _SetPlayerWantedVar;
				remote_native_arg[2] = 1;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_SET_PLAYER_WANTED_LEVEL, 3);

				_SetPlayerWantedIndex++;
				break;

			case 2:
				remote_native_arg[0] = selectedPlayer;
				remote_native_arg[1] = _SetPlayerWantedVar;
				remote_native_arg[2] = 0;
				remote_native_arg[3] = 0;
				remote_native_arg[4] = 0;
				remote_native_arg[5] = 0;
				remote_native_arg[6] = 0;
				remote_native_arg[7] = 0;
				remote_native_arg[8] = 0;
				remote_native_arg[9] = 0;
				call_remote_native_onAddress(selectedPlayer, RCE_SET_PLAYER_WANTED_LEVEL_NOW, 2);
				_SetPlayerWantedIndex++;
				break;

			case 3:
				_SetPlayerWantedIndex = 0;
				_SetPlayerWantedTimer = 0;
				_setwantedbool = false;
				addMessageShow("セットしました！");
				break;
			}
			_SetPlayerWantedTimer = 10;
		}
		else
			_SetPlayerWantedTimer--;
	}
	
#pragma endregion

#pragma region Teleport
	if (WaypointTeleport)
	{
		if (TeleportDeray >= GAMEPLAY::GET_GAME_TIMER())
		{
			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(CoordBlip.x, CoordBlip.y, Zheight[1], &Zheight[0]))
			{
				ENTITY::SET_ENTITY_COORDS(EntityID, CoordBlip.x, CoordBlip.y, Zheight[0], 1, 0, 0, 1);
				PartcleFX_Coord("scr_rcbarry2", "scr_clown_appears", CoordBlip.x, CoordBlip.y, Zheight[0], 0, 0, 0, 1);
				//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
				//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

				addMessageShow("座標を取得しました。");
				WaypointTeleport = false;
			}
			ENTITY::SET_ENTITY_COORDS(EntityID, CoordBlip.x, CoordBlip.y, Zheight[1], 1, 0, 0, 1);
			Zheight[1] += 10.0f;
		}
		else
		{
			Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(EntityID, true);
			ENTITY::SET_ENTITY_COORDS(EntityID, MyCoord.x, MyCoord.y, 400, 1, 0, 0, 1);
			addMessageShow("座標を取得出来ませんでした。");
			WaypointTeleport = false;
		}
	}

	if (VehicleTP)
	{
		if (PED::GET_VEHICLE_PED_IS_USING(_TPMe._Player))
		{
			if (_TPMe.Timer > GAMEPLAY::GET_GAME_TIMER())
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_TPMe._Entity);
				ENTITY::SET_ENTITY_COORDS(_TPMe._Entity, _TPMe.Coord.x, _TPMe.Coord.y, _TPMe.Coord.z, 0, 0, 0, true);
			}
		}
		else
		{
			TPofScene(_TPMe._Player, _TPMe.Coord, "", "");
			VehicleTP = false;
		}
	}

	if (AnimTP)
	{
		if (!STREAMING::HAS_ANIM_DICT_LOADED(SceneTP___[0]))
			STREAMING::REQUEST_ANIM_DICT(SceneTP___[0]);
		else
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(TPtoMePlayer);
			int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(_TP_Coord.x, _TP_Coord.y, _TP_Coord.z, 0.0, 0.0, ENTITY::GET_ENTITY_HEADING(TPtoMePlayer), 9, 0, 0, 0, 0, 0);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_3(TPtoMePlayer, scene2, SceneTP___[0], SceneTP___[1], 8.0f, -8.0, 5, 0, 30, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
			STREAMING::REMOVE_ANIM_DICT(SceneTP___[0]);
			AnimTP = false;
		}
	}

	if (TP_LowBool)
	{
		if (GAMEPLAY::GET_GAME_TIMER() > TP_Low_Delay)
		{
			GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
			addMessageShow("テレポートが完了したのでもとに戻します。");
			TP_LowBool = false;
			TP_Low_Delay = 0;
		}
	}

	if (TeleportPTFX)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			Vector3 PTFX_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			//int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(PLAYER::PLAYER_PED_ID(), "roof");
			//PartcleFX_Ped("scr_rcbarry2", "scr_clown_appears", PLAYER::PLAYER_PED_ID(), newVector3(0, 0, 0), newVector3(0, 0, 0), Bone, 1.0);

			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PTFX_Coord.x, PTFX_Coord.y, PTFX_Coord.z, 0, 0, 0, 1, 0, 0, 0);
			TeleportPTFX = false;
		}
	}

	if (TPEffectBool)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			Vector3 PTFX_Coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PTFX_Coord.x, PTFX_Coord.y, PTFX_Coord.z, 1, 1, 1, 1, 1, 1, 1);
			GRAPHICS::_START_FWPARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PTFX_Coord.x, PTFX_Coord.y, PTFX_Coord.z, 1, 1, 1, 1, 1, 1, 1);
			TPEffectBool = false;
		}
	}

#pragma endregion

#pragma region PenisDeamon
	if (PenisDeamon)
	{
		Vector3 _TP_Coord;
		_TP_Coord.x = -1102.2910; _TP_Coord.y = -2894.5160; _TP_Coord.z = 13.9467;
		TP_LOC(PLAYER::PLAYER_PED_ID(), _TP_Coord);
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		int deamon = GAMEPLAY::GET_HASH_KEY("daemon");
		int v_ret_gc_bullet = GAMEPLAY::GET_HASH_KEY("v_ret_gc_bullet");
		int prop_mr_raspberry_01 = GAMEPLAY::GET_HASH_KEY("prop_mr_raspberry_01");
		REQUEST_MODEL(deamon);
		REQUEST_MODEL(v_ret_gc_bullet);
		REQUEST_MODEL(prop_mr_raspberry_01);
		Hash prop []= { v_ret_gc_bullet , prop_mr_raspberry_01 };
		Vector6 propC[] = { { 0, 0.8, 0.6, 310, 0, 0 }, { 0, 0.5, 0.6, 0, 0, 180 } };
		if (!ENTITY::DOES_ENTITY_EXIST(PenisDeamon_moto))
			PenisDeamon_moto = VEHICLE::CREATE_VEHICLE(deamon, MyCoord.x, MyCoord.y, MyCoord.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(PenisDeamon_int[0]))
			{
				PenisDeamon_int[0] = OBJECT::CREATE_OBJECT(prop[0], MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
			}
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(PenisDeamon_int[1]))
				{
					PenisDeamon_int[1] = OBJECT::CREATE_OBJECT(prop[1], MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
				}
				else
				{
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PenisDeamon_int[0], 0, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(PenisDeamon_int[0], PenisDeamon_moto, -1, propC[0].Lx, propC[0].Ly, propC[0].Lz, propC[0].Rx, propC[0].Ry, propC[0].Rz, 1, 1, 0, 1, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PenisDeamon_int[1], 0, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(PenisDeamon_int[1], PenisDeamon_moto, -1, propC[1].Lx, propC[1].Ly, propC[1].Lz, propC[1].Rx, propC[1].Ry, propC[1].Rz, 1, 1, 0, 1, 1, 1);

					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PenisDeamon_moto, -1);
					ENTITY::SET_ENTITY_PROOFS(PenisDeamon_moto, true, true, true, true, true, true, true, true);
					SET_MODEL_AS_NO_LONGER_NEEDED(deamon);
					SET_MODEL_AS_NO_LONGER_NEEDED(v_ret_gc_bullet);
					SET_MODEL_AS_NO_LONGER_NEEDED(prop_mr_raspberry_01);
					PenisDeamon_moto = 0;
					PenisDeamon_int[0] = 0;
					PenisDeamon_int[1] = 0;
					PenisDeamon_index = 0;
					PenisDeamon = false;
				}
			}

		}
	}
#pragma endregion

#pragma region GhostRiderSpawn
	if (GhostRiderSpawn)
	{
		int __hash = GAMEPLAY::GET_HASH_KEY("innovation");
		int __fire_h = GAMEPLAY::GET_HASH_KEY("prop_beach_fire");
		int __emp_h = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
		REQUEST_MODEL(__fire_h);
		REQUEST_MODEL(__hash);
		REQUEST_MODEL(__emp_h);

		if (STREAMING::HAS_MODEL_LOADED(__hash) && STREAMING::HAS_MODEL_LOADED(__fire_h) && STREAMING::HAS_MODEL_LOADED(__emp_h))
		{
			Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			MyCoord.z += 20;
			if (!ENTITY::DOES_ENTITY_EXIST(__Fire))
			{
				__Fire = OBJECT::CREATE_OBJECT(__fire_h, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
				//ENTITY::SET_ENTITY_PROOFS(__Fire, 1, 1, 1, 1, 1, 1, 1, 1);
			}
			if (!ENTITY::DOES_ENTITY_EXIST(__INNOVATION))
			{
				__INNOVATION = VEHICLE::CREATE_VEHICLE(__hash, MyCoord.x, MyCoord.y, MyCoord.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + (TeleAutomIncar ? 0 : 90), 1, 0);
				//ENTITY::SET_ENTITY_PROOFS(__INNOVATION, 1, 1, 1, 1, 1, 1, 1, 1);
			}
			if (!ENTITY::DOES_ENTITY_EXIST(__EMP))
			{
				__EMP = OBJECT::CREATE_OBJECT(__emp_h, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
				//ENTITY::SET_ENTITY_PROOFS(__EMP, 1, 1, 1, 1, 1, 1, 1, 1);
			}
			//wheel_rr
			if (ENTITY::DOES_ENTITY_EXIST(__Fire) && ENTITY::DOES_ENTITY_EXIST(__INNOVATION) && ENTITY::DOES_ENTITY_EXIST(__EMP))
			{
				int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(__INNOVATION, "wheel_lr");

				if (ENTITY::IS_ENTITY_ATTACHED(__EMP))
				{
					ENTITY::SET_ENTITY_COORDS(__INNOVATION, MyCoord.x, MyCoord.y, MyCoord.z - 20.0f, 0, 0, 0, 1);
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), __INNOVATION, -1);
					VEHICLE::SET_VEHICLE_ENGINE_ON(__INNOVATION, true, true);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(__emp_h);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(__hash);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(__fire_h);
					__INNOVATION = 0;
					__Fire = 0;
					__EMP = 0;
					ENTITY::SET_ENTITY_PROOFS(__INNOVATION, true, true, true, true, true, true, true, true);
					GhostRiderSpawn = false;
				}
				else
				{
					ToggleCollisionEntity(__Fire, false);
					ToggleCollisionEntity(__EMP, false);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(__Fire, __INNOVATION, Bone, 0, 0, 0, 0, 0, 90, 1, 1, 0, 1, 1, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(__EMP, __INNOVATION, Bone, 0, 0, 0, 0, 0, 90, 1, 1, 0, 1, 1, 1);

				}
			}
		}
	}
	
	if (RideonAnimal)
	{
		char UANS[100];
		snprintf___(UANS, 100, "Speed : %f\nNow   : %f", RideonSpeed, SpeedometerPreviousSpeed);
		drawText(UANS, 1, 0.2, 0.3, 0.4, 0.4, 0, 255, 255, 255, true);
		if (!MoveAnimal)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(RideonAnimalsPedID))
			{
				RideonAnimalsPedID = PedSpawnMethod_int("a_c_deer");
			}
			else
			{
				ENTITY::SET_ENTITY_INVINCIBLE(RideonAnimalsPedID, true);
				PED::SET_PED_CAN_BE_TARGETTED(RideonAnimalsPedID, false);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(RideonAnimalsPedID, false);
				PED::SET_PED_CAN_RAGDOLL(RideonAnimalsPedID, false);
				PED::SET_PED_CAN_RAGDOLL(RideonAnimalsPedID, false);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(RideonAnimalsPedID, false);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(RideonAnimalsPedID, false);
				PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(RideonAnimalsPedID, false);
				PED::SET_PED_RAGDOLL_ON_COLLISION(RideonAnimalsPedID, true);
				ATTACH_ENTITY_TO_ENTITY_1(PLAYER::PLAYER_PED_ID(), RideonAnimalsPedID, 0, 0.3000f, 0, 0.1000f, 0.0f, 90.00f, 270.00f);
				//RideonAnimals = false;
				MoveAnimal = true;
			}
		}
		else
		{
			if (ENTITY::DOES_ENTITY_EXIST(RideonAnimalsPedID))
			{
				STREAMING::REQUEST_ANIM_DICT("missfam2_tracy_jetski");
				if (STREAMING::HAS_ANIM_DICT_LOADED("missfam2_tracy_jetski"))
				{
					TASK_PLAY_ANIM_1(PLAYER::PLAYER_PED_ID(), "missfam2_tracy_jetski", "tracy_jetski_a", 9);
				}
				Vector3 MyRot = GET_GAMEPLAY_CAM_ROT_orig(2);
				Vector3 MyCod = CAM2::get_coords_from_entity_cam(5);
				AI::TASK_LOOK_AT_COORD(RideonAnimalsPedID, MyCod.x, MyCod.y, MyCod.z, 8.0f, 0, 2);
				AI::TASK_GO_STRAIGHT_TO_COORD(RideonAnimalsPedID, MyCod.x, MyCod.y, MyCod.z, 8.0f, 20000, MyRot.z, 4.0f);
				ENTITY::SET_ENTITY_ROTATION(RideonAnimalsPedID, 0, 0, MyRot.z, 0, 0);
				//if (isPress(Button_R2))
				//{
				if (isPress(Dpad_Right))
				{
					if (RideonSpeed > 3.0f)
					{
						RideonSpeed = 0.1f;
					}
					else
					{
						RideonSpeed += 0.1f;
					}
				}
				if (isPress(Dpad_Left))
				{
					if (RideonSpeed < 0.1f)
					{
						RideonSpeed = 3.0f;
					}
					else
					{
						RideonSpeed -= 0.1f;
					}
				}
				int CuTime = GAMEPLAY::GET_GAME_TIMER();
				if (CuTime > SpeedometerPreviousGameTime + 25)
				{
					float Speed = ENTITY::GET_ENTITY_SPEED(RideonAnimalsPedID);
					ACC = (float)(((float)Speed - (float)SpeedometerPreviousSpeed) / ((float)CuTime - (float)SpeedometerPreviousGameTime)) * 100;
					Speed *= 2.94f;
					SpeedometerPreviousGameTime = CuTime;
					SpeedometerPreviousSpeed = Speed;
				}

				if (SpeedometerPreviousSpeed < 25)
				{
					ApplyForce(RideonAnimalsPedID, newVector3(0, RideonSpeed, 0), newVector3(0, 0, 0));
				}
				//}
			}
			else
			{
				Freeze(PLAYER::PLAYER_PED_ID());
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), 0, 0);
				MoveAnimal = false;
			}
		}
	}
#pragma endregion

#pragma region Vehicle Option
	if (VehicleJetpack)
	{
		x = 0.0, y = 0.0, z = 0.0;
		heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(JetPackOB, true);
		

		MyCoords.z += 1.0;

		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		//float speed = ENTITY::GET_ENTITY_SPEED(JetPackOB);
		//float avod = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(JetPackOB);

		if (ENTITY::DOES_ENTITY_EXIST(vehicle))
		{
			if (isPressed(Button_L3) && VehJetpackHoverToggle == 0 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				if (!Hover_ON)
				{
					Hover_ON = true;
					addMessageShow("~y~*ホバーモード*~w~ ~g~ON");
				}
				else
				{
					if (ENTITY::DOES_ENTITY_EXIST(JetPackOB))
					{
						ENTITY::DETACH_ENTITY(JetPackOB, 1, 1);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(JetPackOB, 1, 1);
						ENTITY::DELETE_ENTITY1(&JetPackOB);
					}
					ENTITY::SET_ENTITY_ROTATION(JetPackOB, 0, 0, heading, 2, 1);
					VehJetpack_ON = false;
					Hover_ON = false;
					addMessageShow("~y~*ホバーモード*~w~ ~r~OFF");
				}

				VehJetpackHoverToggle = 20;
			}
		}
		else
		{
			JetPackOB = 0;
			Hover_ON = false;
			VehJetpack_ON = false;
		}

		if (VehJetpackHoverToggle != 0) VehJetpackHoverToggle--;

		if (Hover_ON)
		{
			if (VehJetpackStop)
			{
				freeze_entity_position(JetPackOB, false);
				VehJetpackStop = false;
			}

			if (isPress(Button_X))
			{
				freeze_entity_position(JetPackOB, true);
				VehJetpackStop = true;
			}
			SetCollision(JetPackOB, false);
			int L3_X = Analog(188);
			int L3_Y = Analog(189);

			if (L3_X < 127)
			{
				heading += 2.7f;
				if (heading >= 359) heading = 0.0;
			}
			if (L3_X > 127)
			{
				heading -= 2.7f;
				if (heading < 0) heading = 359;
			}

			if (L3_Y < 127) { z = 1.0; }
			if (L3_Y > 127) { z = -1.0; }

			if (isPress(Button_R2)) { y = 1.0; }
			if (isPress(Button_L2)) { y = -1.0; }

			if (isPressed(Button_R3) && VehJetpackToggle == 0)
			{
				if (!VehJetpack_ON)
				{
					VehJetpack_ON = true;
					addMessageShow("~y~*フライモード* ~g~ON");
				}
				else
				{
					VehJetpack_ON = false;
					addMessageShow("~y~*フライモード* ~r~OFF");
				}

				VehJetpackToggle = 20;
			}

			if (VehJetpackToggle != 0) VehJetpackToggle--;

			if (!ENTITY::DOES_ENTITY_EXIST(JetPackOB))
				Create_obj(GAMEPLAY::GET_HASH_KEY("prop_ld_test_01"), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), true, &JetPackOB);
			else
			{
				if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(vehicle, JetPackOB))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(JetPackOB);
					ENTITY::SET_ENTITY_HAS_GRAVITY(JetPackOB, false);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("prop_ld_test_01"));
					ATTACH_ENTITY_TO_ENTITY(vehicle, JetPackOB, 0, newVector3(0.0f, 0.0f, 0.7f), newVector3(0.0, 0.0, 0.0), true, true, false, false, 2, true);
				}
				else
				{
					if (VehJetpack_ON)
					{
						Vector3 CamRot = GET_GAMEPLAY_CAM_ROT_orig(0);
						ENTITY::SET_ENTITY_ROTATION(JetPackOB, CamRot.x, CamRot.y, CamRot.z, 2, 1);
						if (isPress(Button_R2))x *= 8.0f, y *= 8.0f, z *= 8.0f;
						FireZCoords = -0.5;
						FireSize = 2.0;
					}
					else
					{
						Vector3 Rot = { 0, 0, heading };
						ENTITY::SET_ENTITY_ROTATION(JetPackOB, Rot.x, Rot.y, Rot.z, 2, 1);
						FireZCoords = -0.4;
						FireSize = 1.5;
					}

					Vector3 Force = { x, y, z };
					Vector3 ForceRot = { 0.0f, 0.0f, 0.0f };
					ApplyForce(JetPackOB, Force, ForceRot);
				}
			}
		}
		//Create_obj(GAMEPLAY::GET_HASH_KEY("prop_ld_test_01"), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), false, &JetPackOB);
	}

	if (DriveOnWall)
	{
		int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		Vector3 WallDrive = { x, y, z };
		Vector3 Wallrot = { rotx, roty, rotz };
		x = 0.0, y = 0.0, z = -0.5;
		rotx = 0.0, roty = 0.0, rotz = 0.0;
		if (ENTITY::DOES_ENTITY_EXIST(veh))
		{
			if (isPress(Button_X))
			{
				freeze_entity_position(veh, true);
			}
			if (isPress(Button_R2))
			{
				y = 0.3f;
				freeze_entity_position(veh, false);
			}
			if (isPress(Button_L2))
			{
				y = -0.3f;
				freeze_entity_position(veh, false);
			}
			if (isPress(Button_R1))
			{
				z = 0.5;
				roty = 0.4f;
			}
			ApplyForce(veh, WallDrive, Wallrot);
		}
	}

	if (VehicleGodmode)
	{
		_VehicleGodmode(PLAYER::PLAYER_PED_ID(), true);
	}

	if (DriftL1)
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		if (isPress(Button_R1))
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 1);
		else
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 0);
		ButtonDisable(Button_R1);
	}

	if (DpadLeftCarFix)
	{
		if (isPressed(Dpad_Right))
		{
			CARFIX();
		}
	}

	if (L3Boost_R3Stop)
	{
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

	if (R1Jumping)
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		
		if (isPressed(Button_R1))
		{
			if (!VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(vehicle)) || !VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(vehicle)))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					ApplyForce(vehicle, newVector3(0, 0.3, hydro), newVector3(0, 0, 0));
				}
			}
			else
			{
				addMessageShow("ヘリ, 飛行機では使用できません。");
			}
		}
	}

	if (TireRainbow)
	{
		if (!taiyakonColor || ColorVarTaiyakon != 6)
		{
			TireRainbow = false;
		}

		if (TireRainbow_.R == 5) {
			if (TireRainbow_.G > 5)
				TireRainbow_.G -= 1;
			if (TireRainbow_.B < 255)
				TireRainbow_.B += 1;
		}
		if (TireRainbow_.G == 5) {
			if (TireRainbow_.B > 5)
				TireRainbow_.B -= 1;
			if (TireRainbow_.R < 255)
				TireRainbow_.R += 1;
		}
		if (TireRainbow_.B == 5) {
			if (TireRainbow_.R > 5)
				TireRainbow_.R -= 1;
			if (TireRainbow_.G < 255)
				TireRainbow_.G += 1;
		}

		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
			PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)TireRainbow_.R);
			PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)TireRainbow_.G);
			PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)TireRainbow_.B);
		}
	}

	if (TireRainbow2)
	{
		if (!taiyakonColor || ColorVarTaiyakon != 6)
		{
			TireRainbow = false;
		}

		if (TireRainbow_.R == 5) {
			if (TireRainbow_.G > 5)
				TireRainbow_.G -= 1;
			if (TireRainbow_.B < 255)
				TireRainbow_.B += 1;
		}
		if (TireRainbow_.G == 5) {
			if (TireRainbow_.B > 5)
				TireRainbow_.B -= 1;
			if (TireRainbow_.R < 255)
				TireRainbow_.R += 1;
		}
		if (TireRainbow_.B == 5) {
			if (TireRainbow_.R > 5)
				TireRainbow_.R -= 1;
			if (TireRainbow_.G < 255)
				TireRainbow_.G += 1;
		}

		for (int i = 0; i < VEHFX_INDEX; i++)
		{
			int _ADDRESS = VEHFX_ADDRESS + VEHFX_INFO_START_VOID + (i * VEHFX_SIZE);
			PS3::WriteByte(_ADDRESS + VEHFX_RED, (char)TireRainbow_.R);
			PS3::WriteByte(_ADDRESS + VEHFX_GREEN, (char)TireRainbow_.G);
			PS3::WriteByte(_ADDRESS + VEHFX_BLUE, (char)TireRainbow_.B);
		}
	}
	//CollisionCar
	if (DriveSpeedModifier)
	{
		if (isPress(Button_R2) && PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))
			ApplyForce(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), newVector3(0, (DriveSpeedModifier_float / 100), 0), newVector3(0, 0, 0));
	}

	if (StopSpeedModifier)
	{
		if (isPress(Button_L2) && PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))
		{
			if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) > 0.5f)
				ApplyForce(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), newVector3(0, (StopSpeedModifier_float / 100) * (-1), 0), newVector3(0, 0, 0));
			else
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);
		}
			
	}

	if (CollisionCar)
	{
		Collision(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
	}
#pragma endregion

#pragma region aa
	if (LSCRace)
	{
		Hash prop_ind_barge_01 = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_01");
		Hash prop_helipad_02 = GAMEPLAY::GET_HASH_KEY("prop_helipad_02");
		REQUEST_MODEL(prop_ind_barge_01);
		Hash props[] = { prop_ind_barge_01, prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01 ,prop_ind_barge_01,prop_helipad_02,prop_helipad_02,prop_helipad_02,prop_helipad_02 };
		Vector6 vecs[] = { { -227.6013,-211.4689,47.5324,0,192,6 }, { -240.5011,-213.5683,50.3438,1.45,192.15,12}, { -250.6817,-216.6063,52.6639,2.6,192.6,17.55 }, { -263.0307,-221.5447,55.6647,4.25,193.1001,24 }, { -273.8909,-226.9779,58.8245,7.05,194.7002,36.6501 }, { -285.357,-234.2717,63.0878,7.95,198.5502,40.2 }, { -294.304,-243.4786,67.4437,10.25,198.9999,47.6 }, { -290.1392,-249.9649,69.1432,19.7501,207,84 }, { -287.3026,-261.2772,74.3534,26.25,210.6996,94.5 }, { -282.9771,-269.9594,79.2473,33.05,212.75,105 }, { -275.6901,-277.4409,84.152,40.2,209.7,121.6499 }, { -265.6228,-284.0466,89.4109,315.8998,149.7,312 }, { -254.4565,-287.2058,93.737,309.2499,152.2,333.3516 }, { -244.2487,-286.0292,97.5675,304.8,163.3498,7.8 }, { -233.4595,-278.4027,99.8191,303,156,24 }, { -226.2459,-268.0284,104.1927,300,156,48 }, { -223.6288,-256.2286,107.4872,297.15,170.85,81 }, { -226.2961,-245.1515,108.6042,297.4036,160.2504,91.1501 }, { -234.2629,-235.0951,110.1223,63.9,201.25,300 } , { -229.7274,-239.3629,110.2131,246,339,291 }, { -237.7029,-282.333,98.4209,302.4987,173.0999,31.3 },{ -94.8501,-818.9779,325.1085,0,0,0 }, { -75.1787,-838.423,325.1085,0,0,90 }, { 55.7853,-818.9779,325.1085,0,0,180 } , { -75.1582,-779.5519,325.1085,0,0,270 } };
		if (!ENTITY::DOES_ENTITY_EXIST(LSCRaceInt[LSCRaceIndex]))
		{
			LSCRaceInt[LSCRaceIndex] = OBJECT::CREATE_OBJECT(props[LSCRaceIndex], 0, 0, 0, true, true, false);
			ENTITY::SET_ENTITY_COORDS(LSCRaceInt[LSCRaceIndex], vecs[LSCRaceIndex].Lx, vecs[LSCRaceIndex].Ly, vecs[LSCRaceIndex].Lz, 0, 0, 0, true);
			ENTITY::SET_ENTITY_ROTATION(LSCRaceInt[LSCRaceIndex], vecs[LSCRaceIndex].Rx, vecs[LSCRaceIndex].Ry, vecs[LSCRaceIndex].Rz, 2, 1);
			ToggleFreezeEntity(LSCRaceInt[LSCRaceIndex], true);
		}
		else
		{
			ENTITY::SET_ENTITY_COORDS(LSCRaceInt[LSCRaceIndex], vecs[LSCRaceIndex].Lx, vecs[LSCRaceIndex].Ly, vecs[LSCRaceIndex].Lz, 0, 0, 0, true);
			ENTITY::SET_ENTITY_ROTATION(LSCRaceInt[LSCRaceIndex], vecs[LSCRaceIndex].Rx, vecs[LSCRaceIndex].Ry, vecs[LSCRaceIndex].Rz, 2, 1);
			ToggleFreezeEntity(LSCRaceInt[LSCRaceIndex], true);
			LSCRaceIndex++;
		}
		
		if (LSCRaceIndex >= 25)
		{
			int Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0) : PLAYER::PLAYER_PED_ID();
			TP(Entity, newVector3(-227.6013, -211.4689, 50.5324));

			for (int i = 0; i < 21; i++)
			{
				LSCRaceInt[i] = 0;
			}
			SET_MODEL_AS_NO_LONGER_NEEDED(prop_ind_barge_01);
			LSCRace = false;
			LSCRaceIndex = 0;
		}
	}

	if (AirRace)
	{
		Hash prop_ind_barge_01 = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_01");
		Hash prop_ind_barge_02 = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_02");
		Hash prop_container_ld2 = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
		REQUEST_MODEL(prop_ind_barge_01);
		Hash props[] = { prop_ind_barge_02 ,prop_ind_barge_02 ,prop_ind_barge_02 ,prop_ind_barge_02 ,prop_ind_barge_02,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_01,prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_container_ld2 };
		Vector6 vecs[] = { { -995.2849,-3143.771,114.4329,0,180,60 }, { -1117.369,-3073.2019,114.4966,0,180,60 }, { -1086.2577,-3091.1528,114.4966,0,180,60 }, { -1055.7219,-3108.7595,114.4966,0,180,60 }, { -1024.6168,-3126.7483,114.4966,0,180,60 }, { -1151.9353,-3053.0613,115.2488,0,180,330 }, { -1139.2252,-3060.4189,115.2488,0,180,330 }, { -1214.2642,-3019.387,13.0598,0,197,330 }, { -1225.7535,-3012.7708,17.1172,0,197,330 }, { -1237.9131,-3005.7427,21.922,0,200.8,330 }, { -1249.6442,-2998.979,27.911,0,207,330 }, { -1258.7563,-2993.7114,34.417,0,214.8,330 }, { -1268.0232,-2988.3621,42.9263,0,222,330 }, { -1275.2325,-2984.1909,52.2374,0,237,330 }, { -1279.8501,-2981.5234,61.6508,0,246,330 }, { -1282.5013,-2979.9968,70.6854,0,255,330 },{ -1283.7822,-2979.2581,78.7657,0,270,330 } , { -1283.0493,-2979.6897,91.5856,0,279,330 },{ -1282.376,-2980.0664,96.5772,0,282,330 }, { -1280.2208,-2981.2715,102.616,0,306,330 }, { -1273.7502,-2984.9775,111.1663,0,321,330 }, { -1189.6078,-3031.2896,115.2488,0,180,330 },{ -1176.7344,-3038.731,115.2488,0,180,330 }, { -1163.8478,-3046.1812,115.2488,0,180,330}, { -972.5259,-3156.8081,115.2479,0,180,330 }, { -959.5876,-3164.2998,116.0143,0,174,330 }, { -946.8026,-3171.6785,118.7112,0,165,330 }, { -934.4281,-3178.8254,123.766,0,156,330 }, { -923.2156,-3185.2944,130.8037,0,147,330 }, { -913.9182,-3190.6604,138.9526,0,139,330 }, { -906.9495,-3194.6714,146.7565,0,130,330 }, { -901.796,-3197.635,154.9485,0,120,330 }, { -899.62,-3198.8962,159.4967,0,111,330 }, { -897.8545,-3199.9070,166.7682,0,99,330 } ,{ -894.0693,-3200.3594,173.8192,0,90,330 }, { -897.2013,-3200.2981,180.9263,0,81,330 },{ -898.6884,-3199.4504,188.4051,0,66,330 }, { -905.3043,-3195.634,199.3792,0,45,330 }, { -952.1303,-3165.3735,215.057,0,180,330 }, { -964.0133,-3158.5149,215.0735,0,180,330 },{ -976.869,-3151.0938,215.0901,0,180,330 } ,{ -989.5522,-3143.7471,215.1064,0,180,330 }, { -1002.3624,-3136.3479,215.1227,0,180,330 }, { -1139.3616,-3060.324,115.2141,0,180,330 },{ -1014.3372,-3129.4229,215.0892,0,180,330 }, { -1026.9078,-3122.1633,215.1052,0,180,330 }, { -1039.684,-3114.804,215.1218,0,180,330 }, { -1052.6023,-3107.342,215.1385,0,180,330 }, { -1065.4657,-3099.8987,215.1547,0,180,330 }, { -1078.3811,-3092.4502,215.1707,0,180,330 }, { -1091.3174,-3084.9666,215.1871,0,180,330 }, { -1104.2341,-3077.5127,215.2036,0,180,330 }, { -1117.1769,-3070.0356,215.2203,0,180,330 }, { -1130.1404,-3062.5525,215.2368,0,180,330 }, { -1142.8424,-3055.2058,215.6032,0,183,330 }, { -1147.2726,-3052.6533,216.2252,0,186,330 }, { -1152.3365,-3049.7385,217.1866,0,189,330 }, { -1158.9497,-3045.9038,218.7735,0,192,330 }, { -1162.959,-3043.5764,220.1035,0,195,330 }, { -1168.2522,-3040.532,222.1402,0,198,330 }, { -1172.7333,-3037.957,224.2041,0,201,330 }, { -1175.7546,-3036.1577,225.9677,0,204,330 }, { -1176.9785,-3035.4602,227.016,0,207,330 }, { -1181.6373,-3032.7542,230.1462,0,210,330 }, { -1184.424,-3031.1519,232.2783,0,213,330 }, { 1188.7931,-3028.6274,235.918,0,216,330 }, { -1191.8,-3026.8994,238.489,0,219,330 }, { -1198.5752,-3022.9849,245.0566,0,222,330 }, { -1204.1702,-3019.7483,251.0324,0,225,330 }, { 1207.3312,-3017.928,254.6476,0,228,330 } , { 1212.7394,-3014.8232,261.8192,0,231,330 }, { -1215.233,-3013.3877,265.4833,0,234,330 }, { -1218.7532,-3011.3457,271.4355,0,237,330 }, { -1222.6613,-3009.0742,278.7675,0,240,330 }, { -1225.078,-3007.6528,284.1312,0,244,330}, { -1228.2894,-3005.7815,291.9537,0,247,330 } , { -1229.6824,-3004.9705,295.3357,0,250,330 }, { -1231.7347,-3003.7839,301.9774,0,255,330 }, { -1234.1077,-3002.4409,315.065,0,261,330 }, { -1235.1761,-3001.8254,323.6075,0,264,330 } , { 1235.5376,-3001.6187,330.0284,0,270,330 }, { -1235.1642,-3001.8323,340.1884,0,276,330 }, { -1233.5874,-3002.7527,352.3916,0,282,330 }, { -1231.9979,-3003.6792,359.9013,0,285,330 }, { -1167.5654,-3041.3267,387.5515,0,180,330 }, { -1155.1423,-3048.498,387.5678,0,180,330 }, { -1182.1886,-3033.1792,368.5254,0,180,330 }, { -1169.5394,-3040.4927,368.542,0,180,330 }, { 1142.4612,-3055.8333,387.5876,0,180,330 } , { 1142.4612,-3055.8333,387.5876,0,180,330 }, { -1086.2987,-3082.489,387.5913,0,180,330 } , { -1091.386,-3091.1531,387.5894,0,180,330 }, { -1148.9491,-3052.3315,367.7668,0,180,60 } , { -1134.8768, -3060.4604,369.4431,348,180,60 } , { -1128.3652,-3064.2175,366.6168,327,180,60 } ,{ -1119.7733,-3069.0818,370.3415,309,180,60 },{ -1104.9763,-3064.8572,386.826,0,180,60 }, { -1115.8917,-3083.8206,386.823,0,180,60 }, { -1094.7238,-3083.5371,385.653,354,180,60 }, { -1095.0975,-3083.5557,386.7092,0,327,330 } };
		if (!ENTITY::DOES_ENTITY_EXIST(AirRaceInt[AirRaceIndex]))
		{
			AirRaceInt[AirRaceIndex] = OBJECT::CREATE_OBJECT(props[AirRaceIndex], 0, 0, 0, true, true, false);
			//NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(AirRaceInt[AirRaceIndex]);
			//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(AirRaceInt[AirRaceIndex], 0, 1);

			ENTITY::SET_ENTITY_COORDS(AirRaceInt[AirRaceIndex], vecs[AirRaceIndex].Lx, vecs[AirRaceIndex].Ly, vecs[AirRaceIndex].Lz, 0, 0, 0, true);
			ENTITY::SET_ENTITY_ROTATION(AirRaceInt[AirRaceIndex], vecs[AirRaceIndex].Rx, vecs[AirRaceIndex].Ry, vecs[AirRaceIndex].Rz, 2, 1);
			ToggleFreezeEntity(AirRaceInt[AirRaceIndex], true);
		}
		else
		{
			//NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(AirRaceInt[AirRaceIndex]);
			//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(AirRaceInt[AirRaceIndex], 0, 1);
			ToggleFreezeEntity(AirRaceInt[AirRaceIndex], true);
			ENTITY::SET_ENTITY_COORDS(AirRaceInt[AirRaceIndex], vecs[AirRaceIndex].Lx, vecs[AirRaceIndex].Ly, vecs[AirRaceIndex].Lz, 0, 0, 0, true);
			ENTITY::SET_ENTITY_ROTATION(AirRaceInt[AirRaceIndex], vecs[AirRaceIndex].Rx, vecs[AirRaceIndex].Ry, vecs[AirRaceIndex].Rz, 2, 1);		
			ToggleFreezeEntity(AirRaceInt[AirRaceIndex], true);
			AirRaceIndex++;
		}

		if (AirRaceIndex >= 100)
		{
			int Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0) : PLAYER::PLAYER_PED_ID();
			TP(Entity, newVector3(-1214.2642, -3019.387, 20.0598));
			for (int i = 0; i < 44; i++)
			{
				AirRaceInt[i] = 0;
			}
			SET_MODEL_AS_NO_LONGER_NEEDED(prop_ind_barge_01);
			AirRace = false;
			AirRaceIndex = 0;
		}
	}

	//if (MountainRace)
	//{
	//	Hash _prop_container_03b_Hash = GAMEPLAY::GET_HASH_KEY("prop_container_03b");
	//	Hash _prop_ind_barge_Hash = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_02");
	//	REQUEST_MODEL(_prop_container_03b_Hash);


	//	Vector6 _prop_container_03b_0 = { 426.8,5572.99,811.52,0,-53.99,0 };
	//	Vector6 _prop_container_03b_1 = { 279.53,5573.34,701.5,0,14.99,0 };
	//	Vector6 _prop_container_03b_2 = { 272.62,5572.78,706.16,0,-41.99,0 };
	//	Vector6 _prop_container_03b_3 = { 267.44,5572.45,713.86,0,-23.99,0 };
	//	//Vector6 _prop_container_03b_4 = { 236.95,5568.9,725.6,0,0,0 };
	//	//Vector6 _prop_container_03b_5 = { 265.77,5536.61,734.71,0,27,0 };
	//	Vector6 _prop_container_03b_6 = { 274.99,5560.47,724.94,0,-23.99,0 };
	//	Vector6 _prop_container_03b_7 = { 284.69,5557.67,745.5,0,5.99,0 };
	//	Vector6 _prop_container_03b_8 = { 293.8,5554.73,745.2,0,8.99,0 };
	//	Vector6 _prop_container_03b_9 = { 300.25,5550.26,741.91,0,32.99,0 };
	//	Vector6 _prop_container_03b_10 = { 307.73,5546.48,735.13,0,53.99,0 };
	//	Vector6 _prop_container_03b_11 = { 313.76,5543.85,725.35,0,-14.99,0 };
	//	Vector6 _prop_container_03b_12 = { 314.79,5540.5,715.13,0,0,0 };
	//	Vector6 _prop_container_03b_13 = { 291.96,5573.41,700.16,0,-5.99,0 };
	//	Vector6 _prop_container_03b_14 = { 327.2,5573.19,712.66,0,-22.99,0 };
	//	REQUEST_MODEL(_prop_ind_barge_Hash);
	//	Vector6 _prop_ind_barge_02_15 = { 427,5571.95,809.81,0.2,114.64,0.2 };
	//	Vector6 _prop_ind_barge_02_16 = { 444.50,5572.78,816.87,-17.99,0,90.18 };
	//	Vector6 _prop_ind_barge_02_17 = { 412.79,5573.3,794.11,-52.79, 180, 90.31 };
	//	Vector6 _prop_ind_barge_02_18 = { 392.64,5573.14,770.99,-46.63,180,90.18 };
	//	Vector6 _prop_ind_barge_02_19 = { 368.86,5573.61,747.44,-42.85,179,90.9 };
	//	Vector6 _prop_ind_barge_02_20 = { 340.35,5573.67,724.15,-36.64,-180,90.15 };
	//	Vector6 _prop_ind_barge_02_21 = { 309.41,5573.8,705.96,-18.4, 180,90 };
	//	Vector6 _prop_ind_barge_02_22 = { 286.1,5586.16,700.56,0.26,-174,359.97 };
	//	Vector6 _prop_ind_barge_02_23 = { 275.36,5586.59,703.25,0.59,152.99,180.6 };
	//	Vector6 _prop_ind_barge_02_24 = { 263.64,5583.38,720.10,0.6,104.99,180 };
	//	Vector6 _prop_ind_barge_02_25 = { 263.27,5575.61,731.15,-1.72,74.99,178.33 };
	//	Vector6 _prop_ind_barge_02_26 = { 269.17,5567.34,741.62,0,-44.99 };
	//	Vector6 _prop_ind_barge_02_27 = { 278.85,5559.90,746.87,0,-11.99,0 };
	//	Vector6 _prop_ind_barge_02_28 = { 287.16,5551.45,748.5,0,0,0 };
	//	Vector6 _prop_ind_barge_02_29 = { 296.7,5544.12,747.12,0,23.99,0 };
	//	Vector6 _prop_ind_barge_02_30 = { 305.93,5540.89,740.91,0,36,0 };
	//	Vector6 _prop_ind_barge_02_31 = { 312.4,5541.18,732.62,0,62.99,0 };
	//	Vector6 _prop_ind_barge_02_32 = { 315.89,5540.84,721.35,0,83.99,0 };
	//	Vector6 _prop_ind_barge_02_33 = { 313.47,5541.52,710.31,0,119.99,0 };
	//	Vector6 _prop_ind_barge_02_34 = { 304.7,5541.59,702.6,0,161.99,0 };
	//	Vector6 _prop_ind_barge_02_35 = { 293.8,5541.72,698.93,0,158.99,0 };
	//	//Vector6 _prop_ind_barge_02_36 = { 303,5520.82,711.22,-22.34,-92.99,266.16 };
	//	Vector6 _prop_ind_barge_02_37 = { 283.51,5542.28,696.6,0.31,-176.99,178.2 };
	//	Vector6 _prop_ind_barge_02_38 = { 274.11,5541.47,698.34,0.1,-150, 0.1 };
	//	
	//	Vector6 _prop_ind_barge_02_39 = {267.30, 5585.6, 711.55, 0.0, -104.99, 0.0};
	//	Vector6 _prop_ind_barge_02_40 = { 264.78, 5583.85, 719.28, 0, -110.99, 0 };
	//	if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[0]))
	//	{
	//		Mountain_int[0] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//		ENTITY::SET_ENTITY_COORDS(Mountain_int[0], _prop_container_03b_0.Lx, _prop_container_03b_0.Ly, _prop_container_03b_0.Lz, 0, 0, 0, true);
	//		ENTITY::SET_ENTITY_ROTATION(Mountain_int[0], _prop_container_03b_0.Rx, _prop_container_03b_0.Ry, _prop_container_03b_0.Rz, 2, 1);
	//		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[0], 0, 1);
	//		ToggleFreezeEntity(Mountain_int[0], true);
	//	}
	//	else
	//	{
	//		if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[1]))
	//		{
	//			Mountain_int[1] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//			ENTITY::SET_ENTITY_COORDS(Mountain_int[1], _prop_container_03b_1.Lx, _prop_container_03b_1.Ly, _prop_container_03b_1.Lz, 0, 0, 0, true);
	//			ENTITY::SET_ENTITY_ROTATION(Mountain_int[1], _prop_container_03b_1.Rx, _prop_container_03b_1.Ry, _prop_container_03b_1.Rz, 2, 1);
	//			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[1], 0, 1);
	//			ToggleFreezeEntity(Mountain_int[1], true);
	//		}
	//		else
	//		{
	//			if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[2]))
	//			{
	//				Mountain_int[2] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//				ENTITY::SET_ENTITY_COORDS(Mountain_int[2], _prop_container_03b_2.Lx, _prop_container_03b_2.Ly, _prop_container_03b_2.Lz, 0, 0, 0, true);
	//				ENTITY::SET_ENTITY_ROTATION(Mountain_int[2], _prop_container_03b_2.Rx, _prop_container_03b_2.Ry, _prop_container_03b_2.Rz, 2, 1);
	//				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[2], 0, 1);
	//				ToggleFreezeEntity(Mountain_int[2], true);
	//			}
	//			else
	//			{
	//				if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[3]))
	//				{
	//					Mountain_int[3] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//					ENTITY::SET_ENTITY_COORDS(Mountain_int[3], _prop_container_03b_3.Lx, _prop_container_03b_3.Ly, _prop_container_03b_3.Lz, 0, 0, 0, true);
	//					ENTITY::SET_ENTITY_ROTATION(Mountain_int[3], _prop_container_03b_3.Rx, _prop_container_03b_3.Ry, _prop_container_03b_3.Rz, 2, 1);
	//					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[3], 0, 1);
	//					ToggleFreezeEntity(Mountain_int[3], true);
	//				}
	//				else
	//				{
	//					//if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[4]))
	//					//{
	//					//	Mountain_int[4] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//					//	ENTITY::SET_ENTITY_COORDS(Mountain_int[4], _prop_container_03b_4.Lx, _prop_container_03b_4.Ly, _prop_container_03b_4.Lz, 0, 0, 0, true);
	//					//	ENTITY::SET_ENTITY_ROTATION(Mountain_int[4], _prop_container_03b_4.Rx, _prop_container_03b_4.Ry, _prop_container_03b_4.Rz, 2, 1);
	//					//	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[4], 0, 1);
	//					//	ToggleFreezeEntity(Mountain_int[4], true);
	//					//}
	//					//else
	//					//{
	//						//if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[5]))
	//						//{
	//						//	Mountain_int[5] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//						//	ENTITY::SET_ENTITY_COORDS(Mountain_int[5], _prop_container_03b_5.Lx, _prop_container_03b_5.Ly, _prop_container_03b_5.Lz, 0, 0, 0, true);
	//						//	ENTITY::SET_ENTITY_ROTATION(Mountain_int[5], _prop_container_03b_5.Rx, _prop_container_03b_5.Ry, _prop_container_03b_5.Rz, 2, 1);
	//						//	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[5], 0, 1);
	//						//	ToggleFreezeEntity(Mountain_int[5], true);
	//						//}
	//						//else
	//						//{
	//							//if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[5]))
	//							//{
	//							//	Mountain_int[5] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//							//	ENTITY::SET_ENTITY_COORDS(Mountain_int[5], _prop_container_03b_5.Lx, _prop_container_03b_5.Ly, _prop_container_03b_5.Lz, 0, 0, 0, true);
	//							//	ENTITY::SET_ENTITY_ROTATION(Mountain_int[5], _prop_container_03b_5.Rx, _prop_container_03b_5.Ry, _prop_container_03b_5.Rz, 2, 1);
	//							//	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[5], 0, 1);
	//							//	ToggleFreezeEntity(Mountain_int[5], true);
	//							//}
	//							//else
	//							//{
	//								if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[6]))
	//								{
	//									Mountain_int[6] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//									ENTITY::SET_ENTITY_COORDS(Mountain_int[6], _prop_container_03b_6.Lx, _prop_container_03b_6.Ly, _prop_container_03b_6.Lz, 0, 0, 0, true);
	//									ENTITY::SET_ENTITY_ROTATION(Mountain_int[6], _prop_container_03b_6.Rx, _prop_container_03b_6.Ry, _prop_container_03b_6.Rz, 2, 1);
	//									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[6], 0, 1);
	//									ToggleFreezeEntity(Mountain_int[6], true);
	//								}
	//								else
	//								{
	//									if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[7]))
	//									{
	//										Mountain_int[7] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//										ENTITY::SET_ENTITY_COORDS(Mountain_int[7], _prop_container_03b_7.Lx, _prop_container_03b_7.Ly, _prop_container_03b_7.Lz, 0, 0, 0, true);
	//										ENTITY::SET_ENTITY_ROTATION(Mountain_int[7], _prop_container_03b_7.Rx, _prop_container_03b_7.Ry, _prop_container_03b_7.Rz, 2, 1);
	//										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[7], 0, 1);
	//										ToggleFreezeEntity(Mountain_int[7], true);
	//									}
	//									else
	//									{
	//										if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[8]))
	//										{
	//											Mountain_int[8] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//											ENTITY::SET_ENTITY_COORDS(Mountain_int[8], _prop_container_03b_8.Lx, _prop_container_03b_8.Ly, _prop_container_03b_8.Lz, 0, 0, 0, true);
	//											ENTITY::SET_ENTITY_ROTATION(Mountain_int[8], _prop_container_03b_8.Rx, _prop_container_03b_8.Ry, _prop_container_03b_8.Rz, 2, 1);
	//											ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[8], 0, 1);
	//											ToggleFreezeEntity(Mountain_int[8], true);
	//										}
	//										else
	//										{
	//											if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[9]))
	//											{
	//												Mountain_int[9] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//												ENTITY::SET_ENTITY_COORDS(Mountain_int[9], _prop_container_03b_9.Lx, _prop_container_03b_9.Ly, _prop_container_03b_9.Lz, 0, 0, 0, true);
	//												ENTITY::SET_ENTITY_ROTATION(Mountain_int[9], _prop_container_03b_9.Rx, _prop_container_03b_9.Ry, _prop_container_03b_9.Rz, 2, 1);
	//												ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[9], 0, 1);
	//												ToggleFreezeEntity(Mountain_int[9], true);
	//											}
	//											else
	//											{
	//												if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[10]))
	//												{
	//													Mountain_int[10] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//													ENTITY::SET_ENTITY_COORDS(Mountain_int[10], _prop_container_03b_10.Lx, _prop_container_03b_10.Ly, _prop_container_03b_10.Lz, 0, 0, 0, true);
	//													ENTITY::SET_ENTITY_ROTATION(Mountain_int[10], _prop_container_03b_10.Rx, _prop_container_03b_10.Ry, _prop_container_03b_10.Rz, 2, 1);
	//													ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[10], 0, 1);
	//													ToggleFreezeEntity(Mountain_int[10], true);
	//												}
	//												else
	//												{
	//													if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[11]))
	//													{
	//														Mountain_int[11] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//														ENTITY::SET_ENTITY_COORDS(Mountain_int[11], _prop_container_03b_11.Lx, _prop_container_03b_11.Ly, _prop_container_03b_11.Lz, 0, 0, 0, true);
	//														ENTITY::SET_ENTITY_ROTATION(Mountain_int[11], _prop_container_03b_11.Rx, _prop_container_03b_11.Ry, _prop_container_03b_11.Rz, 2, 1);
	//														ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[11], 0, 1);
	//														ToggleFreezeEntity(Mountain_int[11], true);
	//													}
	//													else
	//													{
	//														if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[12]))
	//														{
	//															Mountain_int[12] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//															ENTITY::SET_ENTITY_COORDS(Mountain_int[12], _prop_container_03b_12.Lx, _prop_container_03b_12.Ly, _prop_container_03b_12.Lz, 0, 0, 0, true);
	//															ENTITY::SET_ENTITY_ROTATION(Mountain_int[12], _prop_container_03b_12.Rx, _prop_container_03b_12.Ry, _prop_container_03b_12.Rz, 2, 1);
	//															ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[12], 0, 1);
	//															ToggleFreezeEntity(Mountain_int[12], true);
	//														}
	//														else
	//														{
	//															if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[13]))
	//															{
	//																Mountain_int[13] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//																ENTITY::SET_ENTITY_COORDS(Mountain_int[13], _prop_container_03b_13.Lx, _prop_container_03b_13.Ly, _prop_container_03b_13.Lz, 0, 0, 0, true);
	//																ENTITY::SET_ENTITY_ROTATION(Mountain_int[13], _prop_container_03b_13.Rx, _prop_container_03b_13.Ry, _prop_container_03b_13.Rz, 2, 1);
	//																ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[13], 0, 1);
	//																ToggleFreezeEntity(Mountain_int[13], true);
	//															}
	//															else
	//															{
	//																if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[14]))
	//																{
	//																	Mountain_int[14] = OBJECT::CREATE_OBJECT(_prop_container_03b_Hash, 0, 0, 0, true, true, false);
	//																	ENTITY::SET_ENTITY_COORDS(Mountain_int[14], _prop_container_03b_14.Lx, _prop_container_03b_14.Ly, _prop_container_03b_14.Lz, 0, 0, 0, true);
	//																	ENTITY::SET_ENTITY_ROTATION(Mountain_int[14], _prop_container_03b_14.Rx, _prop_container_03b_14.Ry, _prop_container_03b_14.Rz, 2, 1);
	//																	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[14], 0, 1);
	//																	ToggleFreezeEntity(Mountain_int[14], true);
	//																}
	//																else
	//																{

	//																	if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[15]))
	//																	{
	//																		Mountain_int[15] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																		ENTITY::SET_ENTITY_COORDS(Mountain_int[15], _prop_ind_barge_02_15.Lx, _prop_ind_barge_02_15.Ly, _prop_ind_barge_02_15.Lz, 0, 0, 0, true);
	//																		ENTITY::SET_ENTITY_ROTATION(Mountain_int[14], _prop_ind_barge_02_15.Rx, _prop_ind_barge_02_15.Ry, _prop_ind_barge_02_15.Rz, 2, 1);
	//																		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[15], 0, 1);
	//																		ToggleFreezeEntity(Mountain_int[15], true);
	//																	}
	//																	else
	//																	{
	//																		if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[16]))
	//																		{
	//																			Mountain_int[16] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																			ENTITY::SET_ENTITY_COORDS(Mountain_int[16], _prop_ind_barge_02_16.Lx, _prop_ind_barge_02_16.Ly, _prop_ind_barge_02_16.Lz, 0, 0, 0, true);
	//																			ENTITY::SET_ENTITY_ROTATION(Mountain_int[16], _prop_ind_barge_02_16.Rx, _prop_ind_barge_02_16.Ry, _prop_ind_barge_02_16.Rz, 2, 1);
	//																			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[16], 0, 1);
	//																			ToggleFreezeEntity(Mountain_int[16], true);
	//																		}
	//																		else
	//																		{
	//																			if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[17]))
	//																			{
	//																				Mountain_int[17] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																				ENTITY::SET_ENTITY_COORDS(Mountain_int[17], _prop_ind_barge_02_17.Lx, _prop_ind_barge_02_17.Ly, _prop_ind_barge_02_17.Lz, 0, 0, 0, true);
	//																				ENTITY::SET_ENTITY_ROTATION(Mountain_int[17], _prop_ind_barge_02_17.Rx, _prop_ind_barge_02_17.Ry, _prop_ind_barge_02_17.Rz, 2, 1);
	//																				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[17], 0, 1);
	//																				ToggleFreezeEntity(Mountain_int[17], true);
	//																			}
	//																			else
	//																			{
	//																				if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[18]))
	//																				{
	//																					Mountain_int[18] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																					ENTITY::SET_ENTITY_COORDS(Mountain_int[18], _prop_ind_barge_02_18.Lx, _prop_ind_barge_02_18.Ly, _prop_ind_barge_02_18.Lz, 0, 0, 0, true);
	//																					ENTITY::SET_ENTITY_ROTATION(Mountain_int[18], _prop_ind_barge_02_18.Rx, _prop_ind_barge_02_18.Ry, _prop_ind_barge_02_18.Rz, 2, 1);
	//																					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[18], 0, 1);
	//																					ToggleFreezeEntity(Mountain_int[18], true);
	//																				}
	//																				else
	//																				{
	//																					if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[19]))
	//																					{
	//																						Mountain_int[19] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																						ENTITY::SET_ENTITY_COORDS(Mountain_int[19], _prop_ind_barge_02_19.Lx, _prop_ind_barge_02_19.Ly, _prop_ind_barge_02_19.Lz, 0, 0, 0, true);
	//																						ENTITY::SET_ENTITY_ROTATION(Mountain_int[19], _prop_ind_barge_02_19.Rx, _prop_ind_barge_02_19.Ry, _prop_ind_barge_02_19.Rz, 2, 1);
	//																						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[19], 0, 1);
	//																						ToggleFreezeEntity(Mountain_int[19], true);
	//																					}
	//																					else
	//																					{
	//																						if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[20]))
	//																						{
	//																							Mountain_int[20] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																							ENTITY::SET_ENTITY_COORDS(Mountain_int[20], _prop_ind_barge_02_20.Lx, _prop_ind_barge_02_20.Ly, _prop_ind_barge_02_20.Lz, 0, 0, 0, true);
	//																							ENTITY::SET_ENTITY_ROTATION(Mountain_int[20], _prop_ind_barge_02_20.Rx, _prop_ind_barge_02_20.Ry, _prop_ind_barge_02_20.Rz, 2, 1);
	//																							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[20], 0, 1);
	//																							ToggleFreezeEntity(Mountain_int[20], true);
	//																						}
	//																						else
	//																						{
	//																							if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[21]))
	//																							{
	//																								Mountain_int[21] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																								ENTITY::SET_ENTITY_COORDS(Mountain_int[21], _prop_ind_barge_02_21.Lx, _prop_ind_barge_02_21.Ly, _prop_ind_barge_02_21.Lz, 0, 0, 0, true);
	//																								ENTITY::SET_ENTITY_ROTATION(Mountain_int[21], _prop_ind_barge_02_21.Rx, _prop_ind_barge_02_21.Ry, _prop_ind_barge_02_21.Rz, 2, 1);
	//																								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[21], 0, 1);
	//																								ToggleFreezeEntity(Mountain_int[21], true);
	//																							}
	//																							else
	//																							{
	//																								if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[22]))
	//																								{
	//																									Mountain_int[22] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																									ENTITY::SET_ENTITY_COORDS(Mountain_int[22], _prop_ind_barge_02_22.Lx, _prop_ind_barge_02_22.Ly, _prop_ind_barge_02_22.Lz, 0, 0, 0, true);
	//																									ENTITY::SET_ENTITY_ROTATION(Mountain_int[22], _prop_ind_barge_02_22.Rx, _prop_ind_barge_02_22.Ry, _prop_ind_barge_02_22.Rz, 2, 1);
	//																									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[22], 0, 1);
	//																									ToggleFreezeEntity(Mountain_int[22], true);
	//																								}
	//																								else
	//																								{
	//																									if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[23]))
	//																									{
	//																										Mountain_int[23] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																										ENTITY::SET_ENTITY_COORDS(Mountain_int[23], _prop_ind_barge_02_23.Lx, _prop_ind_barge_02_23.Ly, _prop_ind_barge_02_23.Lz, 0, 0, 0, true);
	//																										ENTITY::SET_ENTITY_ROTATION(Mountain_int[23], _prop_ind_barge_02_23.Rx, _prop_ind_barge_02_23.Ry, _prop_ind_barge_02_23.Rz, 2, 1);
	//																										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[23], 0, 1);
	//																										ToggleFreezeEntity(Mountain_int[23], true);
	//																									}
	//																									else
	//																									{
	//																										if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[24]))
	//																										{
	//																											Mountain_int[24] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																											ENTITY::SET_ENTITY_COORDS(Mountain_int[24], _prop_ind_barge_02_23.Lx, _prop_ind_barge_02_23.Ly, _prop_ind_barge_02_23.Lz, 0, 0, 0, true);
	//																											ENTITY::SET_ENTITY_ROTATION(Mountain_int[24], _prop_ind_barge_02_23.Rx, _prop_ind_barge_02_23.Ry, _prop_ind_barge_02_23.Rz, 2, 1);
	//																											ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[24], 0, 1);
	//																											ToggleFreezeEntity(Mountain_int[24], true);
	//																										}
	//																										else
	//																										{
	//																											if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[25]))
	//																											{
	//																												Mountain_int[25] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																												ENTITY::SET_ENTITY_COORDS(Mountain_int[25], _prop_ind_barge_02_25.Lx, _prop_ind_barge_02_25.Ly, _prop_ind_barge_02_25.Lz, 0, 0, 0, true);
	//																												ENTITY::SET_ENTITY_ROTATION(Mountain_int[25], _prop_ind_barge_02_25.Rx, _prop_ind_barge_02_25.Ry, _prop_ind_barge_02_25.Rz, 2, 1);
	//																												ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[25], 0, 1);
	//																												ToggleFreezeEntity(Mountain_int[25], true);
	//																											}
	//																											else
	//																											{
	//																												if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[26]))
	//																												{
	//																													Mountain_int[26] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																													ENTITY::SET_ENTITY_COORDS(Mountain_int[26], _prop_ind_barge_02_26.Lx, _prop_ind_barge_02_26.Ly, _prop_ind_barge_02_26.Lz, 0, 0, 0, true);
	//																													ENTITY::SET_ENTITY_ROTATION(Mountain_int[26], _prop_ind_barge_02_26.Rx, _prop_ind_barge_02_26.Ry, _prop_ind_barge_02_26.Rz, 2, 1);
	//																													ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[26], 0, 1);
	//																													ToggleFreezeEntity(Mountain_int[26], true);
	//																												}
	//																												else
	//																												{
	//																													if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[27]))
	//																													{
	//																														Mountain_int[27] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																														ENTITY::SET_ENTITY_COORDS(Mountain_int[27], _prop_ind_barge_02_27.Lx, _prop_ind_barge_02_27.Ly, _prop_ind_barge_02_27.Lz, 0, 0, 0, true);
	//																														ENTITY::SET_ENTITY_ROTATION(Mountain_int[27], _prop_ind_barge_02_27.Rx, _prop_ind_barge_02_27.Ry, _prop_ind_barge_02_27.Rz, 2, 1);
	//																														ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[27], 0, 1);
	//																														ToggleFreezeEntity(Mountain_int[27], true);
	//																													}
	//																													else
	//																													{
	//																														if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[28]))
	//																														{
	//																															Mountain_int[28] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																															ENTITY::SET_ENTITY_COORDS(Mountain_int[28], _prop_ind_barge_02_28.Lx, _prop_ind_barge_02_28.Ly, _prop_ind_barge_02_28.Lz, 0, 0, 0, true);
	//																															ENTITY::SET_ENTITY_ROTATION(Mountain_int[28], _prop_ind_barge_02_28.Rx, _prop_ind_barge_02_28.Ry, _prop_ind_barge_02_28.Rz, 2, 1);
	//																															ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[28], 0, 1);
	//																															ToggleFreezeEntity(Mountain_int[28], true);
	//																														}
	//																														else
	//																														{
	//																															if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[29]))
	//																															{
	//																																Mountain_int[29] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																ENTITY::SET_ENTITY_COORDS(Mountain_int[29], _prop_ind_barge_02_29.Lx, _prop_ind_barge_02_29.Ly, _prop_ind_barge_02_29.Lz, 0, 0, 0, true);
	//																																ENTITY::SET_ENTITY_ROTATION(Mountain_int[29], _prop_ind_barge_02_29.Rx, _prop_ind_barge_02_29.Ry, _prop_ind_barge_02_29.Rz, 2, 1);
	//																																ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[29], 0, 1);
	//																																ToggleFreezeEntity(Mountain_int[29], true);
	//																															}
	//																															else
	//																															{
	//																																if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[30]))
	//																																{
	//																																	Mountain_int[30] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																	ENTITY::SET_ENTITY_COORDS(Mountain_int[30], _prop_ind_barge_02_30.Lx, _prop_ind_barge_02_30.Ly, _prop_ind_barge_02_30.Lz, 0, 0, 0, true);
	//																																	ENTITY::SET_ENTITY_ROTATION(Mountain_int[30], _prop_ind_barge_02_30.Rx, _prop_ind_barge_02_30.Ry, _prop_ind_barge_02_30.Rz, 2, 1);
	//																																	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[30], 0, 1);
	//																																	ToggleFreezeEntity(Mountain_int[30], true);
	//																																}
	//																																else
	//																																{
	//																																	if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[31]))
	//																																	{
	//																																		Mountain_int[31] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																		ENTITY::SET_ENTITY_COORDS(Mountain_int[31], _prop_ind_barge_02_31.Lx, _prop_ind_barge_02_31.Ly, _prop_ind_barge_02_31.Lz, 0, 0, 0, true);
	//																																		ENTITY::SET_ENTITY_ROTATION(Mountain_int[31], _prop_ind_barge_02_31.Rx, _prop_ind_barge_02_31.Ry, _prop_ind_barge_02_31.Rz, 2, 1);
	//																																		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[31], 0, 1);
	//																																		ToggleFreezeEntity(Mountain_int[31], true);
	//																																	}
	//																																	else
	//																																	{
	//																																		if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[32]))
	//																																		{
	//																																			Mountain_int[32] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																			ENTITY::SET_ENTITY_COORDS(Mountain_int[32], _prop_ind_barge_02_32.Lx, _prop_ind_barge_02_32.Ly, _prop_ind_barge_02_32.Lz, 0, 0, 0, true);
	//																																			ENTITY::SET_ENTITY_ROTATION(Mountain_int[32], _prop_ind_barge_02_32.Rx, _prop_ind_barge_02_32.Ry, _prop_ind_barge_02_32.Rz, 2, 1);
	//																																			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[32], 0, 1);
	//																																			ToggleFreezeEntity(Mountain_int[32], true);
	//																																		}
	//																																		else
	//																																		{
	//																																			if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[33]))
	//																																			{
	//																																				Mountain_int[33] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																				ENTITY::SET_ENTITY_COORDS(Mountain_int[33], _prop_ind_barge_02_33.Lx, _prop_ind_barge_02_33.Ly, _prop_ind_barge_02_33.Lz, 0, 0, 0, true);
	//																																				ENTITY::SET_ENTITY_ROTATION(Mountain_int[33], _prop_ind_barge_02_33.Rx, _prop_ind_barge_02_33.Ry, _prop_ind_barge_02_33.Rz, 2, 1);
	//																																				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[33], 0, 1);
	//																																				ToggleFreezeEntity(Mountain_int[33], true);
	//																																			}
	//																																			else
	//																																			{
	//																																				if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[34]))
	//																																				{
	//																																					Mountain_int[34] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																					ENTITY::SET_ENTITY_COORDS(Mountain_int[34], _prop_ind_barge_02_34.Lx, _prop_ind_barge_02_34.Ly, _prop_ind_barge_02_34.Lz, 0, 0, 0, true);
	//																																					ENTITY::SET_ENTITY_ROTATION(Mountain_int[34], _prop_ind_barge_02_34.Rx, _prop_ind_barge_02_34.Ry, _prop_ind_barge_02_34.Rz, 2, 1);
	//																																					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[34], 0, 1);
	//																																					ToggleFreezeEntity(Mountain_int[34], true);
	//																																				}
	//																																				else
	//																																				{
	//																																					if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[35]))
	//																																					{
	//																																						Mountain_int[35] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																						ENTITY::SET_ENTITY_COORDS(Mountain_int[35], _prop_ind_barge_02_35.Lx, _prop_ind_barge_02_35.Ly, _prop_ind_barge_02_35.Lz, 0, 0, 0, true);
	//																																						ENTITY::SET_ENTITY_ROTATION(Mountain_int[35], _prop_ind_barge_02_35.Rx, _prop_ind_barge_02_35.Ry, _prop_ind_barge_02_35.Rz, 2, 1);
	//																																						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[35], 0, 1);
	//																																						ToggleFreezeEntity(Mountain_int[35], true);
	//																																					}
	//																																					else
	//																																					{
	//	/*																																					if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[36]))
	//																																						{
	//																																							Mountain_int[36] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																							ENTITY::SET_ENTITY_COORDS(Mountain_int[36], _prop_ind_barge_02_36.Lx, _prop_ind_barge_02_36.Ly, _prop_ind_barge_02_36.Lz, 0, 0, 0, true);
	//																																							ENTITY::SET_ENTITY_ROTATION(Mountain_int[36], _prop_ind_barge_02_36.Rx, _prop_ind_barge_02_36.Ry, _prop_ind_barge_02_36.Rz, 2, 1);
	//																																							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[36], 0, 1);
	//																																							ToggleFreezeEntity(Mountain_int[36], true);
	//																																						}
	//																																						else
	//																																						{*/
	//																																							if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[37]))
	//																																							{
	//																																								Mountain_int[37] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																								ENTITY::SET_ENTITY_COORDS(Mountain_int[37], _prop_ind_barge_02_37.Lx, _prop_ind_barge_02_37.Ly, _prop_ind_barge_02_37.Lz, 0, 0, 0, true);
	//																																								ENTITY::SET_ENTITY_ROTATION(Mountain_int[37], _prop_ind_barge_02_37.Rx, _prop_ind_barge_02_37.Ry, _prop_ind_barge_02_37.Rz, 2, 1);
	//																																								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[37], 0, 1);
	//																																								ToggleFreezeEntity(Mountain_int[37], true);
	//																																							}
	//																																							else
	//																																							{
	//																																								if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[39]))
	//																																								{
	//																																									Mountain_int[39] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																									ENTITY::SET_ENTITY_COORDS(Mountain_int[39], _prop_ind_barge_02_39.Lx, _prop_ind_barge_02_39.Ly, _prop_ind_barge_02_39.Lz, 0, 0, 0, true);
	//																																									ENTITY::SET_ENTITY_ROTATION(Mountain_int[39], _prop_ind_barge_02_39.Rx, _prop_ind_barge_02_39.Ry, _prop_ind_barge_02_39.Rz, 2, 1);
	//																																									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[39], 0, 1);
	//																																									ToggleFreezeEntity(Mountain_int[39], true);
	//																																								}
	//																																								else
	//																																								{
	//																																									if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[40]))
	//																																									{
	//																																										Mountain_int[40] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																										ENTITY::SET_ENTITY_COORDS(Mountain_int[40], _prop_ind_barge_02_40.Lx, _prop_ind_barge_02_40.Ly, _prop_ind_barge_02_40.Lz, 0, 0, 0, true);
	//																																										ENTITY::SET_ENTITY_ROTATION(Mountain_int[40], _prop_ind_barge_02_40.Rx, _prop_ind_barge_02_40.Ry, _prop_ind_barge_02_40.Rz, 2, 1);
	//																																										ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[40], 0, 1);
	//																																										ToggleFreezeEntity(Mountain_int[40], true);
	//																																									}
	//																																									else
	//																																									{
	//																																										if (!ENTITY::DOES_ENTITY_EXIST(Mountain_int[38]))
	//																																										{
	//																																											Mountain_int[38] = OBJECT::CREATE_OBJECT(_prop_ind_barge_Hash, 0, 0, 0, true, true, false);
	//																																											ENTITY::SET_ENTITY_COORDS(Mountain_int[38], _prop_ind_barge_02_38.Lx, _prop_ind_barge_02_38.Ly, _prop_ind_barge_02_38.Lz, 0, 0, 0, true);
	//																																											ENTITY::SET_ENTITY_ROTATION(Mountain_int[38], _prop_ind_barge_02_38.Rx, _prop_ind_barge_02_38.Ry, _prop_ind_barge_02_38.Rz, 2, 1);
	//																																											ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Mountain_int[38], 0, 1);
	//																																											ToggleFreezeEntity(Mountain_int[38], true);
	//																																										}
	//																																										else
	//																																										{
	//																																											for (int i = 0; i < 39; i++)
	//																																											{
	//																																												Mountain_int[i] = 0;
	//																																											}
	//																																											SET_MODEL_AS_NO_LONGER_NEEDED(_prop_container_03b_Hash);
	//																																											SET_MODEL_AS_NO_LONGER_NEEDED(_prop_ind_barge_Hash);
	//																																											int Entity = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) ? PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0) : PLAYER::PLAYER_PED_ID();
	//																																											TP(Entity, newVector3(447, 5574, 828));
	//																																											MountainRace = false;
	//																																										}
	//																																									}
	//																																								}
	//																																							//}
	//																																						//}
	//																																					}
	//																																				}
	//																																			}
	//																																		}
	//																																	}
	//																																}
	//																																
	//																															}
	//																														//}
	//																													//}
	//																												}
	//																											}
	//																										}
	//																									}
	//																								}
	//																							}
	//																						}
	//																					}
	//																				}
	//																			}
	//																		}
	//																	}
	//																}


	//															}
	//														}
	//													}
	//												}
	//											}
	//										}
	//									}
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//if (MountainRace2)
	//{
	//	int hash = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_02");
	//	Vector6 _prop_ind_barge_02[] = { { 438.32,5569.89,870.43,0,-179.99,0 }, { 438.32,5569.89,870.43,0,-179.99,0 }, { 415.8,5569.89,870.43,0,-179.99,0 }, { 404.72,5569.89,869.81,0,173.99,0 }, { 393.9,5569.89,871.6,0,167.98,0 }, { 383.32,5569.89,865.25,0,162,0 }, { 373.16,5569.89,861.35,0,156,0 }, { 363.2,5569.89,856.21,0,149.99,0 }, { 354.6,5569.89,850.27,0,143.99,0 }, { 354.6,5569.89,850.27,0,143.99,0 }, { 337.15,5569.89,835.88,0,131.99,0 }, { 330.8,5569.89,827.13,0,125.99,0 }, { 323.4,5569.89,817.93,0,128.99,0 }, { 316.9,5569.89,809.34,0,132,0 }, { 309.29,5569.89,800.95,0,128.99,0 }, { 302.3,5569.89,794.91,0,128.89,0 }, { 294.82,5569.89,783.13,0,128.99,0 }, { 287.75,5569.89,774.4,0,128.99,0 }, { 280.75,5569.89,765.75,0,128.99,0 }, { 273.66,5569.89,756.98,0,128.99,0 }, { 266.49,5569.89,748.13,0,128.99,0 }, { 259.42,5569.89,739.37,0,128.99,0 }, { 252.48,5569.89,730.78,0,128.99,0 }, { 245.25,5569.89,721.85,0,128.99,0 }, { 238,5569.89,712.88,0,128.99,0 }, { 230.98,5569.89,707.8,0,128.99,0 }, { 223.92,5569.89,695.48,0,128.99,0 }, {345.40, 5570.25, 846.54, 0.0, 143.99, 0.0}, {426.88, 5569.87, 873.31, 0.0, 180, 0.0} };
	//	bool _bool = true;
	//	
	//	if (!ENTITY::DOES_ENTITY_EXIST(mountain2_int[mountain2_index]))
	//	{
	//		mountain2_int[mountain2_index] = OBJECT::CREATE_OBJECT(hash, 0, 0, 0, true, true, false);
	//		ToggleFreezeEntity(mountain2_int[mountain2_index], true);
	//		ENTITY::SET_ENTITY_COORDS(mountain2_int[mountain2_index], _prop_ind_barge_02[mountain2_index].Lx, _prop_ind_barge_02[mountain2_index].Ly, _prop_ind_barge_02[mountain2_index].Lz, 0, 0, 0, true);
	//		ENTITY::SET_ENTITY_ROTATION(mountain2_int[mountain2_index], _prop_ind_barge_02[mountain2_index].Rx, _prop_ind_barge_02[mountain2_index].Ry, _prop_ind_barge_02[mountain2_index].Rz, 2, 1);
	//		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(mountain2_int[mountain2_index], 0, 1);

	//	}
	//	else
	//	{
	//		mountain2_index++;
	//	}

	//	if (mountain2_index > 28)
	//	{
	//		for (int i = 0; i < 29; i++)
	//		{
	//			mountain2_int[i] = 0;
	//		}
	//		SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	//		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 447, 5574, 828, 0, 0, 0, 1);
	//		MountainRace2 = false;
	//	}
	//}
#pragma endregion

#pragma region BMX
	if (_16BMX)
	{
		bool _is_attached;
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int __Hash = GAMEPLAY::GET_HASH_KEY("bmx");
		REQUEST_MODEL(__Hash);
		if (STREAMING::HAS_MODEL_LOADED(__Hash))
		{
			if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[15]))
			{
				// VEHICLE::CREATE_VEHICLE(_Hash, MyCoord.x, MyCoord.y, MyCoord.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + (TeleAutomIncar ? 0 : 90), 1, 0);
				_16BMX_Main[15] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _16BMX_Main[15], -1);
				ENTITY::SET_ENTITY_PROOFS(_16BMX_Main[15], 1, 1, 1, 1, 1, 1, 1, 1);
			}
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[0]))
				{
					_16BMX_Main[0] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
				}
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[1]))
					{
						_16BMX_Main[1] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
					}
					else
					{
						if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[2]))
						{
							_16BMX_Main[2] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
						}
						else
						{
							if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[3]))
							{
								_16BMX_Main[3] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
							}
							else
							{
								if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[4]))
								{
									_16BMX_Main[4] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
								}
								else
								{
									if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[5]))
									{
										_16BMX_Main[5] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
									}
									else
									{
										if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[6]))
										{
											_16BMX_Main[6] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
										}
										else
										{
											if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[7]))
											{
												_16BMX_Main[7] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
											}
											else
											{
												if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[8]))
												{
													_16BMX_Main[8] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
												}
												else
												{
													if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[9]))
													{
														_16BMX_Main[9] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
													}
													else
													{
														if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[10]))
														{
															_16BMX_Main[10] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
														}
														else
														{
															if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[11]))
															{
																_16BMX_Main[11] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
															}
															else
															{
																if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[12]))
																{
																	_16BMX_Main[12] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
																}
																else
																{
																	if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[13]))
																	{
																		_16BMX_Main[13] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
																	}
																	else
																	{
																		if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[14]))
																		{
																			_16BMX_Main[14] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
																		}
																		else
																		{
																			for (int i = 0; i < 15; i++)
																			{
																				int index;
																				if (!ENTITY::IS_ENTITY_ATTACHED(_16BMX_Main[i]))
																				{
																					ENTITY::SET_ENTITY_PROOFS(_16BMX_Main[i], 1, 1, 1, 1, 1, 1, 1, 1);
																					ENTITY::ATTACH_ENTITY_TO_ENTITY(_16BMX_Main[i], _16BMX_Main[15], -1, 0, (-1.5 * (1 + i)), 0, 0, 0, 0, 1, 1, 1, 1, 1, 1);
																				
}
																				else
																				{
																					index++;
																					if (index >= 15)
																					{
																						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _16BMX_Main[15], -1);
																						_16BMX = false;
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}

				//for (int i = 0; i < 15; i++)
				//{
				//	if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[i]))
				//		_16BMX_Main[i] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
				//}
				/*for (int i = 0; i < 15; i++)
				{
					int index;
					if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[i]))
					{
						_16BMX_Main[i] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
					}
					else
					{
						if (!ENTITY::IS_ENTITY_ATTACHED(_16BMX_Main[i]))
						{
							ENTITY::ATTACH_ENTITY_TO_ENTITY(_16BMX_Main[i], _16BMX_Main[15], -1, 0, (-1.5 * (1 + i)), 0, 0, 0, 0, 1, 1, 1, 1, 1, 1);
						}
						else
							index++;
					}

					if (index == 15)
					{
						_is_attached = true;
					}*/
			}

			//if (_is_attached)
			//{
			//	//ENTITY::SET_ENTITY_COORDS(_16BMX_Main[15], MyCoord.x, MyCoord.y, MyCoord.z, 0, 0, 0, 1);
			//	//PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _16BMX_Main[15], -1);
			//	//VEHICLE::SET_VEHICLE_ENGINE_ON(_16BMX_Main[15], true, true);
			//	addMessageShow("スポーンしました！");
			//	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(__Hash);
			//	_is_attached = false;
			//	_16BMX = false;
			//}
		}
		//	int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(_16BMX_Main[15], "SKEL_ROOT");
		//	if (_16BMX_Index < 15)
		//	{
		//		for (int i = 0; i < 15; i++)
		//		{
		//			if (!_16BMX_2[i])
		//			{
		//				if (!ENTITY::DOES_ENTITY_EXIST(_16BMX_Main[i]))
		//				{
		//					_16BMX_Main[i] = VEHICLE::CREATE_VEHICLE(__Hash, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
		//					ATTACH_ENTITY_TO_ANTITY_B(_16BMX_Main[15], _16BMX_Main[i], Bone, newVector3(0, -1.5 * (1 + i), 0), newVector3(0, 0, 0), 0);
		//				}
		//				else
		//				{
		//					if (!ENTITY::IS_ENTITY_ATTACHED(_16BMX_Main[i]))
		//					{
		//						ATTACH_ENTITY_TO_ANTITY_B(_16BMX_Main[15], _16BMX_Main[i], Bone, newVector3(0, -1.5 * (1 + i), 0), newVector3(0, 0, 0), 0);
		//						_16BMX_2[i] = true;
		//						_16BMX_Index++;
		//					}
		//				}
		//			}
		//		}
		//	}
		//	else
		//	{
		//		ENTITY::SET_ENTITY_COORDS(_16BMX_Main[15], MyCoord.x, MyCoord.y, MyCoord.z, 0, 0, 0, 1);
		//		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _16BMX_Main[15], -1);
		//		VEHICLE::SET_VEHICLE_ENGINE_ON(_16BMX_Main[15], true, true);
		//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(__Hash);
		//		_16BMX = false;
		//	}
		//}

	}
#pragma endregion

#pragma region ModdedSkyLift
	if (ModdedSkyLift)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _skylift = GAMEPLAY::GET_HASH_KEY("skylift");
		int _tourbus = GAMEPLAY::GET_HASH_KEY("tourbus");
		int _bmx = GAMEPLAY::GET_HASH_KEY("bmx");
		int _emp = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
		int _ferris = GAMEPLAY::GET_HASH_KEY("prop_ferris_car_01");
		int _caddy = GAMEPLAY::GET_HASH_KEY("caddy");
		int _ferriswheel = GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel");
		REQUEST_MODEL(_skylift);
		REQUEST_MODEL(_tourbus);
		REQUEST_MODEL(_bmx);
		REQUEST_MODEL(_emp);
		REQUEST_MODEL(_ferris);
		REQUEST_MODEL(_caddy);
		REQUEST_MODEL(_ferriswheel);

		//ModdedSkyLift_Int[0]
		if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[0]))
			ModdedSkyLift_Int[0] = VEHICLE::CREATE_VEHICLE(_skylift, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[1]))
				ModdedSkyLift_Int[1] = VEHICLE::CREATE_VEHICLE(_tourbus, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[2]))
					ModdedSkyLift_Int[2] = VEHICLE::CREATE_VEHICLE(_bmx, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[11]))
						ModdedSkyLift_Int[11] = VEHICLE::CREATE_VEHICLE(_bmx, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
					else
					{
						if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[3]))
							ModdedSkyLift_Int[3] = VEHICLE::CREATE_VEHICLE(_caddy, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
						else
						{
							if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[4]))
								ModdedSkyLift_Int[4] = OBJECT::CREATE_OBJECT(_emp, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
							else
							{

								if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[6]))
									ModdedSkyLift_Int[6] = OBJECT::CREATE_OBJECT(_emp, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
								else
								{
									if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[7]))
										ModdedSkyLift_Int[7] = OBJECT::CREATE_OBJECT(_emp, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
									else
									{
										if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[8]))
											ModdedSkyLift_Int[8] = OBJECT::CREATE_OBJECT(_emp, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
										else
										{
											if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[9]))
												ModdedSkyLift_Int[9] = OBJECT::CREATE_OBJECT(_ferris, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
											else
											{
												if (!ENTITY::DOES_ENTITY_EXIST(ModdedSkyLift_Int[10]))
													ModdedSkyLift_Int[10] = OBJECT::CREATE_OBJECT(_ferriswheel, MyCoord.x, MyCoord.y, MyCoord.z, true, true, false);
												else
												{
													//rotor_main
													int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(ModdedSkyLift_Int[0], "chassis");

													//_tourbus
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[1], ModdedSkyLift_Int[0], Bone2, 0.0, -3.0, -2.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
													//_bmx
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[2], ModdedSkyLift_Int[0], Bone2, -4.2, -4.5, -2.4, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
													//_bmx
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[11], ModdedSkyLift_Int[0], Bone2, 0, -12.3, -2.3, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
													//_caddy
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[3], ModdedSkyLift_Int[0], Bone2, 0, -16.2, -2.4, 0, 0, 0, 1, 1, 1, 1, 1, 1);
													//_emp
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[4], ModdedSkyLift_Int[0], Bone2, 1.5, -5.7, 1.5, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//_emp
													//ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[5], ModdedSkyLift_Int[0], Bone2, 1.5, -5.7, 1.5, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//_emp
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[6], ModdedSkyLift_Int[0], Bone2, -1.5, -5.7, 1.5, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//_emp
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[7], ModdedSkyLift_Int[0], Bone2, 0.3, -16.8, -2.4, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//_emp
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[8], ModdedSkyLift_Int[0], Bone2, -0.3, -16.8, -2.4, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//_ferris
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[9], ModdedSkyLift_Int[0], Bone2, 0, -12.6, 0.3, 0, 0, 0, 1, 1, false, 1, 1, 1);
													//rotor_main
													int Bone = ENTITY::_GET_ENTITY_BONE_INDEX(ModdedSkyLift_Int[0], "rotor_main");
													//_ferriswheel
													ENTITY::ATTACH_ENTITY_TO_ENTITY(ModdedSkyLift_Int[10], ModdedSkyLift_Int[0], Bone, 0.0, 0.0, -10.0, 0.0, 90.0, 0.0, 1, 1, true, 1, 1, 1);


													PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), ModdedSkyLift_Int[0], -1);
													for (int i = 0; i < 11; i++)
													{
														ENTITY::SET_ENTITY_PROOFS(ModdedSkyLift_Int[i], 1, 1, 1, 1, 1, 1, 1, 1);
														ModdedSkyLift_Int[i] = 0;

													}
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_skylift);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_tourbus);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_bmx);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_emp);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_ferris);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_caddy);
													STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_ferriswheel);

													ModdedSkyLift = false;
												}
											}
										}
									}

								}
							}
						}
					}
				}
			}
		}
	}
	
#pragma endregion

#pragma region Galaxhip
	if (Galaxhip)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int marquis = GAMEPLAY::GET_HASH_KEY("marquis");
		int prop_ind_barge_02 = GAMEPLAY::GET_HASH_KEY("prop_ind_barge_02");
		int prop_container_ld2 = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
		int prop_dock_crane_04 = GAMEPLAY::GET_HASH_KEY("prop_dock_crane_04");
		int	prop_crashed_heli = GAMEPLAY::GET_HASH_KEY("prop_crashed_heli");
		int prop_container_03b = GAMEPLAY::GET_HASH_KEY("prop_container_03b");
		int RHINO = GAMEPLAY::GET_HASH_KEY("rhino");
		int INSURGENT = GAMEPLAY::GET_HASH_KEY("insurgent");

		REQUEST_MODEL(marquis);
		REQUEST_MODEL(prop_ind_barge_02);
		REQUEST_MODEL(prop_container_ld2);

		REQUEST_MODEL(prop_dock_crane_04);
		REQUEST_MODEL(prop_crashed_heli);
		REQUEST_MODEL(RHINO);
		REQUEST_MODEL(INSURGENT);
		Vector6 Galaxhip_[] = { { -4,-18.9,1.2,0,246,0 }, { -3.9,14,1.2,0,246,0, }, { 3.9,-18,1.2,0,115,0 }, { 4,14,1.1,0,115,0}, { 0,-19,5.7,0,0,0 }, { 0,15.4,5.7,0,0,0 }, { 3,37.1,4,0,27.5,27.5 }, { -3,37.1,4,0,333.5,333.5 }, { -1.7,36.9,1.5,0,333.5,333.5 }, { 1.7,36.9,1.5,0,27.5,27.5 }, { -1,35.5,-1.5,0,333.5,333.5 }, { 1,35.5,-1.5,0,27.5,27.5 }, { 0,43,4.5,44,0,0 }, { 0,-9.5,10,0,0,0 }, { 2.5,6.5,16,0,180,180 }, { -2.5,4.5,16,0,180,0 }, { -1.5,2.5,12.5,80,180,0 }, { 1,2.5,12.5,80,180,0 }, { 1,0,12,100.5,0,0 }, { -1.5,0,12,100.5,0,0 }, { 0.5,1,14.5,94,356,7 }, { 0,31,8.5,0,0,90 }, { 0,23,8.5,0,0,270 }, { 0,13.0,8.2,20,0,0 }, { 0,-32.5,8,0,0,180 }, { 0,-23.5,11.5,0,0,180 }, { 0,-6,12,0,0,270 }, { 0,-11.5,12,0,0,90 }, { 0,38,2.5,0,0,0 }, { -3,-17,11.5,0,0,90 }, { 3,-17,11.5,0,0,270 } };
		Hash Galaxhip_hash[] = { prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02, prop_ind_barge_02,prop_ind_barge_02,prop_ind_barge_02,prop_container_ld2,prop_container_ld2, prop_container_ld2,prop_container_ld2,prop_container_ld2,prop_container_ld2,prop_container_ld2,prop_ind_barge_02,prop_dock_crane_04, prop_dock_crane_04,prop_container_ld2, prop_container_ld2,prop_container_ld2,prop_container_ld2, prop_crashed_heli,RHINO, RHINO, RHINO, RHINO, RHINO, RHINO, RHINO, prop_container_03b,INSURGENT, INSURGENT };
		if (!ENTITY::DOES_ENTITY_EXIST(Galaxhip_moto))
		{
			Galaxhip_moto = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("marquis"), MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
			ENTITY::SET_ENTITY_PROOFS(Galaxhip_moto, 1, 1, 1, 1, 1, 1, 1, 1);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Galaxhip_moto, 0, 1);
		}
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Galaxhip_int[Galaxhip_index]))
			{
				if (Galaxhip_hash[Galaxhip_index] != RHINO && Galaxhip_hash[Galaxhip_index] != INSURGENT)
				{
					Galaxhip_int[Galaxhip_index] = OBJECT::CREATE_OBJECT(Galaxhip_hash[Galaxhip_index], 0, 0, 0, 1, 1, 0);
				}
				else
				{
					Galaxhip_int[Galaxhip_index] = VEHICLE::CREATE_VEHICLE(Galaxhip_hash[Galaxhip_index], 0, 0, 0, 0, 1, 0);
				}
			}
			else
			{
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Galaxhip_int[Galaxhip_index], 0, 1);
				ENTITY::SET_ENTITY_PROOFS(Galaxhip_int[Galaxhip_index], 1, 1, 1, 1, 1, 1, 1, 1);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Galaxhip_int[Galaxhip_index], Galaxhip_moto, -1, Galaxhip_[Galaxhip_index].Lx, Galaxhip_[Galaxhip_index].Ly, Galaxhip_[Galaxhip_index].Lz, Galaxhip_[Galaxhip_index].Rx, Galaxhip_[Galaxhip_index].Ry, Galaxhip_[Galaxhip_index].Rz, 1, 1, 1, 1, 1, 1);
				
				Galaxhip_index++;
			}

			if (Galaxhip_index >= 31)
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(marquis);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_ind_barge_02);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_container_ld2);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_dock_crane_04);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_crashed_heli);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_container_03b);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(RHINO);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(INSURGENT);
				ENTITY::SET_ENTITY_COORDS(Galaxhip_moto, MyCoord.x, MyCoord.y, MyCoord.z, 0, 0, 0, 1);
				for (int i = 0; i < 31; i++)
				{
					Galaxhip_int[i] = 0;
				}
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Galaxhip_moto, -1);
				Galaxhip_moto = 0;
				Galaxhip_index = 0;
				Galaxhip = false;

			}
		}
	}
#pragma endregion

#pragma region SquadPilotFly
	if (SquadPilotFly)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _lazer = GAMEPLAY::GET_HASH_KEY("lazer");
		REQUEST_MODEL(_lazer);
		if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[0]))
			_SquadPilotFly_int[0] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[1]))
				_SquadPilotFly_int[1] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 30, 0, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[2]))
					_SquadPilotFly_int[2] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 40, 0, 1, 0);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[3]))
						_SquadPilotFly_int[3] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 50, 0, 1, 0);
					else
					{
						if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[4]))
							_SquadPilotFly_int[4] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 60, 0, 1, 0);
						else
						{
							if (!ENTITY::DOES_ENTITY_EXIST(_SquadPilotFly_int[5]))
								_SquadPilotFly_int[5] = VEHICLE::CREATE_VEHICLE(_lazer, MyCoord.x, MyCoord.y, MyCoord.z + 70, 0, 1, 0);
							else
							{
								//rotor_main
								int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(_SquadPilotFly_int[0], "chassis");

								//_tourbus
								ENTITY::ATTACH_ENTITY_TO_ENTITY(_SquadPilotFly_int[1], _SquadPilotFly_int[0], Bone2, 8.0, 0, 2.7, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
								//_bmx
								ENTITY::ATTACH_ENTITY_TO_ENTITY(_SquadPilotFly_int[2], _SquadPilotFly_int[0], Bone2, -8.0, 0, 2.7, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
								//_bmx
								ENTITY::ATTACH_ENTITY_TO_ENTITY(_SquadPilotFly_int[3], _SquadPilotFly_int[0], Bone2, 15.0, 0, 0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 1, 1);
								//_caddy
								ENTITY::ATTACH_ENTITY_TO_ENTITY(_SquadPilotFly_int[4], _SquadPilotFly_int[0], Bone2, -15.0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1);
								//_emp
								ENTITY::ATTACH_ENTITY_TO_ENTITY(_SquadPilotFly_int[5], _SquadPilotFly_int[0], Bone2, -0, 0, 5.5, 0, 0, 0, 1, 1, 1, 1, 1, 1);



								PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _SquadPilotFly_int[0], -1);
								for (int i = 0; i < 6; i++)
								{
									ENTITY::SET_ENTITY_PROOFS(_SquadPilotFly_int[i], 1, 1, 1, 1, 1, 1, 1, 1);
									_SquadPilotFly_int[i] = 0;

								}
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_lazer);
								ENTITY::SET_ENTITY_ROTATION(_SquadPilotFly_int[0], 0, 0, ENTITY::GET_ENTITY_HEADING(_SquadPilotFly_int[0]), 0, 0);
								SquadPilotFly = false;
							}
						}
					}
				}
			}
		}
	}
#pragma endregion

#pragma region WoodedBoat
	if (WoodedBoat)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _seashark = GAMEPLAY::GET_HASH_KEY("seashark");
		int _rowboat1 = GAMEPLAY::GET_HASH_KEY("prop_byard_rowboat1");
		int _lamp = GAMEPLAY::GET_HASH_KEY("prop_construcionlamp_01");
		REQUEST_MODEL(_seashark);
		REQUEST_MODEL(_rowboat1);
		REQUEST_MODEL(_lamp);
		if (!ENTITY::DOES_ENTITY_EXIST(_WoodedBoatInt_[0]))
			_WoodedBoatInt_[0] = VEHICLE::CREATE_VEHICLE(_seashark, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(_WoodedBoatInt_[1]))
				_WoodedBoatInt_[1] = OBJECT::CREATE_OBJECT(_rowboat1, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(_WoodedBoatInt_[2]))
					_WoodedBoatInt_[2] = OBJECT::CREATE_OBJECT(_lamp, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{
					int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(_WoodedBoatInt_[0], "chassis");

					ENTITY::ATTACH_ENTITY_TO_ENTITY(_WoodedBoatInt_[1], _WoodedBoatInt_[0], Bone2, -0, 0.8, 0.4, 0, 0, 180, 1, 1, 1, 1, 1, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(_WoodedBoatInt_[2], _WoodedBoatInt_[0], Bone2, -0, 3.6, 0.7, 0, 0, 0, 1, 1, 1, 1, 1, 1);
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _WoodedBoatInt_[0], -1);
					ENTITY::SET_ENTITY_COORDS(_WoodedBoatInt_[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
					for (int i = 0; i < 3; i++)
					{
						ENTITY::SET_ENTITY_PROOFS(_WoodedBoatInt_[i], 1, 1, 1, 1, 1, 1, 1, 1);
						_WoodedBoatInt_[i] = 0;

					}

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_lamp);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_rowboat1);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_seashark);
					WoodedBoat = false;
				}
			}
		}
	}
#pragma endregion

#pragma region mensacar
	if (mensacar)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		Vector6 prop_towercrane_01a_1 = { 0.0,-3.7000,-4.7000,0,0,0 };
		Vector6 prop_towercrane_01a_2 = { 0.0,16.2000,36.7000,0,0,0 };
		Vector6 db_apart01 = { 9.2000,15.6000,28.4000,0.0,0.0,0.0 };
		char* incer = "insurgent2";
		char* tower = "prop_towercrane_01a";
		char* apart = "db_apart_01_";
		Hash _incer = GAMEPLAY::GET_HASH_KEY(incer);
		Hash _tower = GAMEPLAY::GET_HASH_KEY(tower);
		Hash _apart = GAMEPLAY::GET_HASH_KEY(apart);
		REQUEST_MODEL(incer);
		REQUEST_MODEL(tower);
		REQUEST_MODEL(apart);

		if (!ENTITY::DOES_ENTITY_EXIST(incer_e))
		{
			incer_e = VEHICLE::CREATE_VEHICLE(_incer, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
			
		}
		else
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), incer_e, -1);
			if (!ENTITY::DOES_ENTITY_EXIST(tower_e2))
				tower_e2 = OBJECT::CREATE_OBJECT(_tower, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(tower_e))
					tower_e = OBJECT::CREATE_OBJECT(_tower, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(apart_e))
						apart_e = OBJECT::CREATE_OBJECT(_apart, MyCoord.x, MyCoord.y, MyCoord.z + 0, 1, 1, 0);
					else
					{


						int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(incer_e, "chassis");

						ENTITY::ATTACH_ENTITY_TO_ENTITY(tower_e2, incer_e, Bone2, prop_towercrane_01a_1.Lx, prop_towercrane_01a_1.Ly, prop_towercrane_01a_1.Lz, prop_towercrane_01a_1.Rx, prop_towercrane_01a_1.Ry, prop_towercrane_01a_1.Rz, 1, 1, 1, 1, 1, 1);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(tower_e, incer_e, Bone2, prop_towercrane_01a_2.Lx, prop_towercrane_01a_2.Ly, prop_towercrane_01a_2.Lz, prop_towercrane_01a_2.Rx, prop_towercrane_01a_2.Ry, prop_towercrane_01a_2.Rz, 1, 1, 1, 1, 1, 1);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(apart_e, incer_e, Bone2, db_apart01.Lx, db_apart01.Ly, db_apart01.Lz, db_apart01.Rx, db_apart01.Ry, db_apart01.Rz, 1, 1, 1, 1, 1, 1);
						ENTITY::SET_ENTITY_PROOFS(incer_e, 1, 1, 1, 1, 1, 1, 1, 1);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), incer_e, -1);
						ENTITY::SET_ENTITY_COORDS(incer_e, MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
						tower_e2 = 0;
						tower_e = 0;
						apart_e = 0;
						incer_e = 0;
						SET_MODEL_AS_NO_LONGER_NEEDED(_tower);
						SET_MODEL_AS_NO_LONGER_NEEDED(_apart);
						SET_MODEL_AS_NO_LONGER_NEEDED(_incer);
						mensacar = false;
					}
				}
			}
		}
	}
	
#pragma endregion

#pragma region cranetank
	if (cranetank)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		Vector6 prop_dock_crane_04_ = { 0.0,0.0,-1.0,0.0,0.0,180.0 };
		Hash _rhino = GAMEPLAY::GET_HASH_KEY("rhino");
		Hash _dock = GAMEPLAY::GET_HASH_KEY("prop_dock_crane_04");
		REQUEST_MODEL(_rhino);
		REQUEST_MODEL(_dock);
		if (!ENTITY::DOES_ENTITY_EXIST(Create_Tank_int[0]))
			Create_Tank_int[0] = OBJECT::CREATE_OBJECT(_dock, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Create_Tank_int[1]))
				Create_Tank_int[1] = VEHICLE::CREATE_VEHICLE(_rhino, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
			else
			{
				int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(Create_Tank_int[1], "turret_1base");
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Create_Tank_int[0], Create_Tank_int[1], Bone2, prop_dock_crane_04_.Lx, prop_dock_crane_04_.Ly, prop_dock_crane_04_.Lz, prop_dock_crane_04_.Rx, prop_dock_crane_04_.Ry, prop_dock_crane_04_.Rz, 1, 1, 1, 1, 1, 1);
				ENTITY::SET_ENTITY_PROOFS(Create_Tank_int[1], 1, 1, 1, 1, 1, 1, 1, 1);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Create_Tank_int[1], -1);
				ENTITY::SET_ENTITY_COORDS(Create_Tank_int[1], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
				Create_Tank_int[0] = 0;
				Create_Tank_int[1] = 0;
				SET_MODEL_AS_NO_LONGER_NEEDED(_rhino);
				SET_MODEL_AS_NO_LONGER_NEEDED(_dock);
				cranetank = false;
			}
		}
	}
#pragma endregion

#pragma region cranetank2
	if (cranetank2)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		Vector6 prop_dock_crane_04 = { 0.0,0.0,-1.0,0.0,0.0,180.0 };
		Vector6 prop_rub_buswreck_06 = { 0.3000,14.6000,9.2000,0.0,0.0,90.0 };
		Hash _crane = GAMEPLAY::GET_HASH_KEY("prop_dock_crane_04");
		Hash _buswreck = GAMEPLAY::GET_HASH_KEY("prop_rub_buswreck_06");
		Hash _rhino = GAMEPLAY::GET_HASH_KEY("rhino");
		REQUEST_MODEL(_crane);
		REQUEST_MODEL(_buswreck);
		REQUEST_MODEL(_rhino);
		if (!ENTITY::DOES_ENTITY_EXIST(Create_Tank_int_2[0]))
			Create_Tank_int_2[0] = VEHICLE::CREATE_VEHICLE(_rhino, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Create_Tank_int_2[1]))
				Create_Tank_int_2[1] = OBJECT::CREATE_OBJECT(_crane, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(Create_Tank_int_2[2]))
					Create_Tank_int_2[2] = OBJECT::CREATE_OBJECT(_buswreck, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{

					int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(Create_Tank_int_2[0], "turret_1base");

					ENTITY::ATTACH_ENTITY_TO_ENTITY(Create_Tank_int_2[1], Create_Tank_int_2[0], Bone2, prop_dock_crane_04.Lx, prop_dock_crane_04.Ly, prop_dock_crane_04.Lz, prop_dock_crane_04.Rx, prop_dock_crane_04.Ry, prop_dock_crane_04.Rz, 1, 1, 1, 1, 1, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Create_Tank_int_2[2], Create_Tank_int_2[0], Bone2, prop_rub_buswreck_06.Lx, prop_rub_buswreck_06.Ly, prop_rub_buswreck_06.Lz, prop_rub_buswreck_06.Rx, prop_rub_buswreck_06.Ry, prop_rub_buswreck_06.Rz, 1, 1, 1, 1, 1, 1);
					ENTITY::SET_ENTITY_PROOFS(Create_Tank_int_2[0], 1, 1, 1, 1, 1, 1, 1, 1);
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Create_Tank_int_2[0], -1);
					ENTITY::SET_ENTITY_COORDS(Create_Tank_int_2[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
					SET_MODEL_AS_NO_LONGER_NEEDED(_rhino);
					SET_MODEL_AS_NO_LONGER_NEEDED(_crane);
					SET_MODEL_AS_NO_LONGER_NEEDED(_buswreck);
					cranetank2 = false;
				}
			}
		}
	}
#pragma endregion

#pragma region PenginCar
	if (PenginCar)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Hash carbon = GAMEPLAY::GET_HASH_KEY("carbonrs");
		Hash prop_byard_rowboat4 = GAMEPLAY::GET_HASH_KEY("prop_byard_rowboat4");
		Hash prop_air_lights_05a = GAMEPLAY::GET_HASH_KEY("prop_air_lights_05a");
		Hash prop_parasol_04 = GAMEPLAY::GET_HASH_KEY("prop_parasol_04");
		Hash prop_dummy_plane = GAMEPLAY::GET_HASH_KEY("prop_dummy_plane");
		REQUEST_MODEL(carbon);
		REQUEST_MODEL(prop_byard_rowboat4);
		REQUEST_MODEL(prop_air_lights_05a);
		REQUEST_MODEL(prop_parasol_04);
		REQUEST_MODEL(prop_dummy_plane);
		Hash _hash[] = { prop_byard_rowboat4, prop_byard_rowboat4 ,prop_air_lights_05a, prop_air_lights_05a,  prop_parasol_04 , prop_dummy_plane };
		Vector6 _coord[] = { { 0,0,-0.45,0,0,0 },{ 0,0,1.05,355,180,0 }, { 0.4,1.6,0.4,0,0,180 } ,{ -0.4,1.6,0.4,0,0,180 }, { 0,0,-0.3,0,0,0 },{ 0,-0.8,0.5,350,0,180 } };
		if (!ENTITY::DOES_ENTITY_EXIST(Pengin_moto))
		{
			Pengin_moto = VEHICLE::CREATE_VEHICLE(carbon, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		}
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Pengin_Spawned[PenginIndex]))
			{
				Pengin_Spawned[PenginIndex] = OBJECT::CREATE_OBJECT(_hash[PenginIndex], MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				ENTITY::SET_ENTITY_PROOFS(Pengin_moto, 1, 1, 1, 1, 1, 1, 1, 1);
			}
			else
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Pengin_Spawned[PenginIndex], Pengin_moto, -1, _coord[PenginIndex].Lx, _coord[PenginIndex].Ly, _coord[PenginIndex].Lz, _coord[PenginIndex].Rx, _coord[PenginIndex].Ry, _coord[PenginIndex].Rz, 1, 1, 0, 1, 1, 1);
				PenginIndex++;
			}

			if (PenginIndex >= 6)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(carbon);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_byard_rowboat4);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_air_lights_05a);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_parasol_04);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_dummy_plane);
				ENTITY::SET_ENTITY_COORDS(Pengin_moto, MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
				for (int i = 0; i < 6; i++)
				{
					Pengin_Spawned[i] = 0;
				}
				PenginIndex = 0;
				Pengin_moto = 0;
				PenginCar = false;
			}
		}
	}
#pragma endregion

#pragma region PenginCar2
	if (PenginCar2)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Hash carbon = GAMEPLAY::GET_HASH_KEY("carbonrs");
		Hash prop_byard_rowboat1 = GAMEPLAY::GET_HASH_KEY("prop_byard_rowboat1");
		Hash prop_air_lights_05a = GAMEPLAY::GET_HASH_KEY("prop_air_lights_05a");
		Hash prop_parasol_04 = GAMEPLAY::GET_HASH_KEY("prop_parasol_04");
		Hash prop_dummy_plane = GAMEPLAY::GET_HASH_KEY("prop_dummy_plane");
		REQUEST_MODEL(carbon);
		REQUEST_MODEL(prop_byard_rowboat1);
		REQUEST_MODEL(prop_air_lights_05a);
		REQUEST_MODEL(prop_parasol_04);
		REQUEST_MODEL(prop_dummy_plane);
		Hash _hash[] = { prop_byard_rowboat1, prop_byard_rowboat1 ,prop_air_lights_05a, prop_air_lights_05a,  prop_parasol_04 , prop_dummy_plane };
		Vector6 _coord[] = { { 0,0.4,-0.15,0,0,180}, { 0,0.4,0.8,0,180,180 }, { 0.45,2.3,0.4,0,0,180 }, { -0.45,2.3,0.4,0,0,180 }, { 0,-0.45,0.65,0,0,180 }, { 0,0.5,0.05,0,0,0 } };
		if (!ENTITY::DOES_ENTITY_EXIST(Pengin_moto_))
		{
			Pengin_moto_ = VEHICLE::CREATE_VEHICLE(carbon, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		}
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Pengin_Spawned_[PenginIndex_]))
			{
				Pengin_Spawned_[PenginIndex_] = OBJECT::CREATE_OBJECT(_hash[PenginIndex_], MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				ENTITY::SET_ENTITY_PROOFS(Pengin_moto_, 1, 1, 1, 1, 1, 1, 1, 1);
			}
			else
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Pengin_Spawned_[PenginIndex_], Pengin_moto_, -1, _coord[PenginIndex_].Lx, _coord[PenginIndex_].Ly, _coord[PenginIndex_].Lz, _coord[PenginIndex_].Rx, _coord[PenginIndex_].Ry, _coord[PenginIndex_].Rz, 1, 1, 0, 1, 1, 1);
				PenginIndex_++;
			}

			if (PenginIndex_ >= 6)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(carbon);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_byard_rowboat1);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_air_lights_05a);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_parasol_04);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_dummy_plane);
				ENTITY::SET_ENTITY_COORDS(Pengin_moto_, MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
				for (int i = 0; i < 6; i++)
				{
					Pengin_Spawned_[i] = 0;
				}
				PenginIndex_ = 0;
				Pengin_moto_ = 0;
				PenginCar = false;
			}
		}
	}
#pragma endregion

	if (ripley2)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Hash RIPLEY = GAMEPLAY::GET_HASH_KEY("RIPLEY");
		Hash LAZER = GAMEPLAY::GET_HASH_KEY("LAZER");
		REQUEST_MODEL(RIPLEY);
		REQUEST_MODEL(LAZER);
		Vector6 _vecs = { 0,-0.5,0.65,50,0,0 };
		if (!ENTITY::DOES_ENTITY_EXIST(ripley2_moto))
		{
			ripley2_moto = VEHICLE::CREATE_VEHICLE(RIPLEY, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
			ENTITY::SET_ENTITY_PROOFS(ripley2_moto, 1, 1, 1, 1, 1, 1, 1, 1);
		}
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(ripley2_int[ripley2_index]))
			{
				ripley2_int[ripley2_index] = VEHICLE::CREATE_VEHICLE(LAZER, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
				ENTITY::SET_ENTITY_PROOFS(ripley2_int[ripley2_index], 1, 1, 1, 1, 1, 1, 1, 1);
			}
			else
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ripley2_int[ripley2_index], ripley2_moto, -1, _vecs.Lx, _vecs.Ly, _vecs.Lz, _vecs.Rx, _vecs.Ry, _vecs.Rz, 1, 1, 1, 1, 1, 1);
				ripley2_index++;
			}

			if (ripley2_index >= 1)
			{
				ripley2_moto = 0;
				ripley2_index = 0;
				ripley2_int[0] = 0;
				SET_MODEL_AS_NO_LONGER_NEEDED(RIPLEY);
				SET_MODEL_AS_NO_LONGER_NEEDED(LAZER);
				ripley2 = false;
			}
		}
	}

#pragma region LightningPanto
	if (LightningPanto)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _panto = GAMEPLAY::GET_HASH_KEY("panto");
		int _trans = GAMEPLAY::GET_HASH_KEY("prop_sub_trans_02a");
		REQUEST_MODEL(_panto);
		REQUEST_MODEL(_trans);
		if (!ENTITY::DOES_ENTITY_EXIST(LightningPanto_int[0]))
			LightningPanto_int[0] = VEHICLE::CREATE_VEHICLE(_panto, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(LightningPanto_int[1]))
				LightningPanto_int[1] = OBJECT::CREATE_OBJECT(_trans, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(LightningPanto_int[2]))
					LightningPanto_int[2] = OBJECT::CREATE_OBJECT(_trans, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(LightningPanto_int[3]))
						LightningPanto_int[3] = OBJECT::CREATE_OBJECT(_trans, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
					else
					{
						int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(LightningPanto_int[0], "chassis");

						ENTITY::ATTACH_ENTITY_TO_ENTITY(LightningPanto_int[1], LightningPanto_int[0], Bone2, 0.1, -1.1, 0.2, 270, 0, 0, 1, 1, 1, 1, 1, 1);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(LightningPanto_int[2], LightningPanto_int[0], Bone2, 0.1, -1, 0.2, 270, 0.0, 350, 1, 1, 1, 1, 1, 1);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(LightningPanto_int[3], LightningPanto_int[0], Bone2, 0, -1.2, 0.2, 270, 0, 10, 1, 1, 1, 1, 1, 1);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), LightningPanto_int[0], -1);
						MaxUp(LightningPanto_int[0]);
						ENTITY::SET_ENTITY_COORDS(LightningPanto_int[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
						for (int i = 0; i < 4; i++)
						{
							ENTITY::SET_ENTITY_PROOFS(LightningPanto_int[i], 1, 1, 1, 1, 1, 1, 1, 1);
							LightningPanto_int[i] = 0;

						}
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_panto);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_trans);
						LightningPanto = false;
					}
				}
			}
		}

	}

	if (yanki_bike)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _innovation = GAMEPLAY::GET_HASH_KEY("innovation");
		int _prop_carjack = GAMEPLAY::GET_HASH_KEY("prop_carjack");
		int _prop_flag_japan_s = GAMEPLAY::GET_HASH_KEY("prop_flag_japan_s");
		REQUEST_MODEL(_innovation);
		REQUEST_MODEL(_prop_carjack);
		REQUEST_MODEL(_prop_flag_japan_s);
		if (!ENTITY::DOES_ENTITY_EXIST(yanki_bike_int[0]))
			yanki_bike_int[0] = VEHICLE::CREATE_VEHICLE(_innovation, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(yanki_bike_int[1]))
				yanki_bike_int[1] = OBJECT::CREATE_OBJECT(_prop_carjack, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(yanki_bike_int[2]))
					yanki_bike_int[2] = OBJECT::CREATE_OBJECT(_prop_flag_japan_s, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{
					int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(yanki_bike_int[0], "chassis");

					ENTITY::ATTACH_ENTITY_TO_ENTITY(yanki_bike_int[1], yanki_bike_int[0], Bone2, 0, -0.9299, 0.0, 20, 0, 180, 1, 1, 1, 1, 1, 1);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(yanki_bike_int[2], yanki_bike_int[0], Bone2, -0, -1.2, 0.9, 0, 0, 0, 1, 1, 1, 1, 1, 1);
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), yanki_bike_int[0], -1);
					ENTITY::SET_ENTITY_COORDS(yanki_bike_int[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
					
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(yanki_bike_int[0], 0, 0, 120);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(yanki_bike_int[0], 0, 0, 120);
					VEHICLE::TOGGLE_VEHICLE_MOD(yanki_bike_int[0], 20, 1);
					VEHICLE::SET_VEHICLE_MOD_KIT(yanki_bike_int[0], 0);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(yanki_bike_int[0], 0, 0, 0);
					for (int i = 0; i < 3; i++)
					{
						ENTITY::SET_ENTITY_PROOFS(yanki_bike_int[i], 1, 1, 1, 1, 1, 1, 1, 1);
						yanki_bike_int[i] = 0;

					}
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_innovation);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_flag_japan_s);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_carjack);
					yanki_bike = false;
				}
			}
		}
	}

	if (senpuukicar)
	{
		//monster
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int _monster = GAMEPLAY::GET_HASH_KEY("monster");
		int _prop_windmill_01 = GAMEPLAY::GET_HASH_KEY("prop_windmill_01");
		int _hei_prop_heist_emp = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
		int _prop_wall_light_05a = GAMEPLAY::GET_HASH_KEY("prop_wall_light_05a");
		int _prop_mb_ordnance_02 = GAMEPLAY::GET_HASH_KEY("prop_mb_ordnance_02");
		int _prop_juicestand = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
		REQUEST_MODEL(_monster);
		REQUEST_MODEL(_prop_windmill_01);
		REQUEST_MODEL(_hei_prop_heist_emp);
		REQUEST_MODEL(_prop_wall_light_05a);
		REQUEST_MODEL(_prop_mb_ordnance_02);
		REQUEST_MODEL(_prop_juicestand);
		if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[0]))
			senpuukicar_int[0] = VEHICLE::CREATE_VEHICLE(_monster, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[1]))
				senpuukicar_int[1] = OBJECT::CREATE_OBJECT(_prop_windmill_01, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[2]))
					senpuukicar_int[2] = OBJECT::CREATE_OBJECT(_prop_windmill_01, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[3]))
						senpuukicar_int[3] = OBJECT::CREATE_OBJECT(_hei_prop_heist_emp, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
					else
					{
						if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[4]))
							senpuukicar_int[4] = OBJECT::CREATE_OBJECT(_prop_wall_light_05a, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
						else
						{
							if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[5]))
								senpuukicar_int[5] = OBJECT::CREATE_OBJECT(_prop_mb_ordnance_02, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
							else
							{
								if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[6]))
									senpuukicar_int[6] = OBJECT::CREATE_OBJECT(_prop_juicestand, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
								else
								{
									if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[7]))
										senpuukicar_int[7] = OBJECT::CREATE_OBJECT(_prop_juicestand, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
									else
									{
										if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[8]))
											senpuukicar_int[8] = OBJECT::CREATE_OBJECT(_prop_juicestand, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
										else
										{
											if (!ENTITY::DOES_ENTITY_EXIST(senpuukicar_int[9]))
												senpuukicar_int[9] = OBJECT::CREATE_OBJECT(_prop_juicestand, MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
											else
											{
												int Bone1 = ENTITY::_GET_ENTITY_BONE_INDEX(senpuukicar_int[0], "chassis");
												int Bone2 = ENTITY::_GET_ENTITY_BONE_INDEX(senpuukicar_int[0], "wheel_lf");
												int Bone3 = ENTITY::_GET_ENTITY_BONE_INDEX(senpuukicar_int[0], "wheel_rf");
												int Bone4 = ENTITY::_GET_ENTITY_BONE_INDEX(senpuukicar_int[0], "wheel_rr");
												int Bone5 = ENTITY::_GET_ENTITY_BONE_INDEX(senpuukicar_int[0], "wheel_lr");

												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[1], senpuukicar_int[0], Bone1, -0.3, 1.0, -36.8000,0, 0, 180, 1, 1, 1, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[2], senpuukicar_int[0], Bone1, -0.3, 1.0, -36.8000, 0, 0, 180, 1, 1, 1, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[3], senpuukicar_int[0], Bone1, 0.0, -2.3000, 1.8, 0, 0, 0, 1, 1, 1, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[4], senpuukicar_int[0], Bone1, 0.0, 0.6f, 1.8f, 0, 0, 0, 1, 1, 1, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[5], senpuukicar_int[0], Bone1, 0.0, 0.6, 1.2, 0, 0, 270, 1, 1, 1, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[6], senpuukicar_int[0], Bone2, 0.3, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[7], senpuukicar_int[0], Bone3, 0.3, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[8], senpuukicar_int[0], Bone4, 0.3, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(senpuukicar_int[9], senpuukicar_int[0], Bone5, 0.3, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1);

												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), senpuukicar_int[0], -1);
												ENTITY::SET_ENTITY_COORDS(senpuukicar_int[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
												for (int i = 0; i < 10; i++)
												{
													ENTITY::SET_ENTITY_PROOFS(senpuukicar_int[i], 1, 1, 1, 1, 1, 1, 1, 1);
													senpuukicar_int[i] = 0;

												}
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_monster);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_windmill_01);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_hei_prop_heist_emp);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_wall_light_05a);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_mb_ordnance_02);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_prop_juicestand);

												senpuukicar = false;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

	}
#pragma endregion

#pragma region moddedmule
	if (moddedmule_)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Hash MULE = GAMEPLAY::GET_HASH_KEY("mule");
		Hash prop_lifelurb_02 = GAMEPLAY::GET_HASH_KEY("prop_lifelurb_02");
		Hash prop_lifelurb_01 = GAMEPLAY::GET_HASH_KEY("prop_lifelurb_01");
		Hash prop_lifelurb_02b = GAMEPLAY::GET_HASH_KEY("prop_lifelurb_02b");
		
		Hash props[] = { MULE,prop_lifelurb_02,prop_lifelurb_02,prop_lifelurb_01,prop_lifelurb_02b };
		Vector6 vecs[] = { { 0,-2,0,0,0,0 }, { -1.2,-1.55,1.05,0,0,270 }, { 1.2,-2.5,1.05,0,0,90 }, { 0,-5.65,1.2,0,0,0 }, { 0,-1.55,2.4,0,90,270 } };
		if (!ENTITY::DOES_ENTITY_EXIST(moddedmule_moto))
		{
			moddedmule_moto = VEHICLE::CREATE_VEHICLE(MULE, MyCoord.x, MyCoord.y, MyCoord.z, 0, 1, 0);
			ENTITY::SET_ENTITY_PROOFS(moddedmule_moto, 1, 1, 1, 1, 1, 1, 1, 1);
		}
		else
		{
			if (!ENTITY::DOES_ENTITY_EXIST(moddedmule[moddedmule_index]))
			{
				REQUEST_MODEL(props[moddedmule_index]);
				if (props[moddedmule_index] == MULE)
				{
					moddedmule_moto = VEHICLE::CREATE_VEHICLE(MULE, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
				}
				else
				{
					moddedmule_moto = OBJECT::CREATE_OBJECT(props[moddedmule_index], MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);;
				}
			}
			else
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(props[moddedmule_index]);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(moddedmule[moddedmule_index], moddedmule_moto, -1, vecs[moddedmule_index].Lx, vecs[moddedmule_index].Ly, vecs[moddedmule_index].Lz, vecs[moddedmule_index].Rx, vecs[moddedmule_index].Ry, vecs[moddedmule_index].Rz, 1, 1, 1, 1, 1, 1);
				ENTITY::SET_ENTITY_PROOFS(moddedmule[moddedmule_index], 1, 1, 1, 1, 1, 1, 1, 1);
				moddedmule_index++;
			}
		}

		if (moddedmule_index >= 5)
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), moddedmule_moto, -1);
			ENTITY::SET_ENTITY_COORDS(moddedmule_moto, MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
			for (int i = 0; i < 5; i++)
			{
				moddedmule[i] = 0;
			}
			moddedmule_index = 0;
			moddedmule_moto = 0;
		}
	}
#pragma endregion

#pragma region Unknown
	if (_unknownCar)
	{
		Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Hash FIRETRUK = GAMEPLAY::GET_HASH_KEY("FIRETRUK");
		Hash SEASHARK = GAMEPLAY::GET_HASH_KEY("SEASHARK");
		Hash prop_juicestand = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
		Hash prop_parasol_04 = GAMEPLAY::GET_HASH_KEY("prop_parasol_04");
		Vector6 vecs[] = { { 0,-0.45,-0.1,0,0,0 }, { 0,-0.45,1,0,180,0 },{ -0.55,-0.45,0.45,0,90,0 }, {0.55,-0.45,0.45,0,270,0 },{ -0.4,-0.45,0.05,0,45,0 }, { -0.4,-0.45,0.85,0,135,0 }, { 0.4,-0.45,0.85,0,225,0 }, { 0.4,-0.45,0.05,0,315,0 }, { -1.75,-1.5,-0.8,0,0,0 } ,{ 1.75,-1.5,-0.85,0,0,0 }, { 0,0.05,0.15,90,0,0 } };
		Hash props[] = { SEASHARK,SEASHARK, SEASHARK,SEASHARK,SEASHARK,SEASHARK,SEASHARK,SEASHARK,prop_juicestand, prop_juicestand, prop_parasol_04 };
		REQUEST_MODEL(FIRETRUK);
		REQUEST_MODEL(SEASHARK);
		REQUEST_MODEL(prop_juicestand);
		REQUEST_MODEL(prop_parasol_04);
		if (!ENTITY::DOES_ENTITY_EXIST(_UnknownCar_car[0]))
		{
			_UnknownCar_car[0] = VEHICLE::CREATE_VEHICLE(FIRETRUK, MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
		}
		else
		{
			if (_UnknownCarIndex >= 11)
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(FIRETRUK);
				SET_MODEL_AS_NO_LONGER_NEEDED(SEASHARK);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_juicestand);
				SET_MODEL_AS_NO_LONGER_NEEDED(prop_parasol_04);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _UnknownCar_car[0], -1);
				ENTITY::SET_ENTITY_COORDS(_UnknownCar_car[0], MyCoord.x, MyCoord.y, MyCoord.z, 1, 1, 1, 1);
				for (int i = 0; i < 15; i++)
				{
					ENTITY::SET_ENTITY_PROOFS(_UnknownCar_car[i], 1, 1, 1, 1, 1, 1, 1, 1);
					_UnknownCar_car[i] = 0;
					
				}
				_unknownCar = false;
			}
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(_UnknownCar_car[1 + _UnknownCarIndex]))
				{
					if (props[_UnknownCarIndex] == SEASHARK)
					{
						_UnknownCar_car[_UnknownCarIndex + 1] = VEHICLE::CREATE_VEHICLE(props[_UnknownCarIndex], MyCoord.x, MyCoord.y, MyCoord.z + 20, 0, 1, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(_UnknownCar_car[_UnknownCarIndex + 1], 180, 0, 225);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(_UnknownCar_car[_UnknownCarIndex + 1], 180, 0, 225);
					}
					else
					{
						_UnknownCar_car[_UnknownCarIndex + 1] = OBJECT::CREATE_OBJECT(props[_UnknownCarIndex], MyCoord.x, MyCoord.y, MyCoord.z + 20, 1, 1, 0);
					}
				}
				else
				{
					int Bone5 = ENTITY::_GET_ENTITY_BONE_INDEX(_UnknownCar_car[0], "turret_1base");
					ENTITY::ATTACH_ENTITY_TO_ENTITY(_UnknownCar_car[_UnknownCarIndex + 1], _UnknownCar_car[0], Bone5, vecs[_UnknownCarIndex].Lx, vecs[_UnknownCarIndex].Ly, vecs[_UnknownCarIndex].Lz, vecs[_UnknownCarIndex].Rx, vecs[_UnknownCarIndex].Ry, vecs[_UnknownCarIndex].Rz, 1, 1, 0, 1, 1, 1);
					_UnknownCarIndex++;
				}
			}
		}
	}
#pragma endregion

#pragma region MagnetCargo
	if (MagnetCargo)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(CargoBobInt))
		{
			Hash _Hash1 = GAMEPLAY::GET_HASH_KEY("CARGOBOB");
			Hash _Hash2 = GAMEPLAY::GET_HASH_KEY("CARGOBOB2");
			Hash _Hash3 = GAMEPLAY::GET_HASH_KEY("CARGOBOB3");
			Hash _Hash4 = GAMEPLAY::GET_HASH_KEY("CARGOBOB4");
			REQUEST_MODEL(_Hash1);
			REQUEST_MODEL(_Hash2);
			REQUEST_MODEL(_Hash3);
			REQUEST_MODEL(_Hash4);
			Vector3 _vector3 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			CargoBobInt = VEHICLE::CREATE_VEHICLE(_Hash1, _vector3.x, _vector3.y, _vector3.z + 3, 0, 1, 0);
		}
		else
		{
			if (!VEHICLE::DOES_CARGOBOB_HAVE_PICKUP_MAGNET(CargoBobInt))
			{
				VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(CargoBobInt, 1);
			}
			else
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), CargoBobInt, -1);
				ENTITY::SET_ENTITY_PROOFS(CargoBobInt, 1, 1, 1, 1, 1, 1, 1, 1);
				CargoBobInt = 0;
				MagnetCargo = false;
			}
			//VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB()
			//VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB()
		}
	}
#pragma endregion

#pragma region Particle
	if (effectp[0])
	{
		if (ParticleTimer[0] < GAMEPLAY::GET_GAME_TIMER())
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 18905, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");

			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 57005, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_Spine_Root, 0.1f, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(72, 236, 232);
			ParticleTimer[0] = GAMEPLAY::GET_GAME_TIMER() + 1000;
		}
	}

	if (effectp[1])
	{
		if (ParticleTimer[1] <= GAMEPLAY::GET_GAME_TIMER())
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 18905, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 57005, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_michael2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_michael2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_abattoir_ped_sliced", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_Spine_Root, 0.1f, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(72, 236, 232);
			ParticleTimer[1] = GAMEPLAY::GET_GAME_TIMER() + 2000;
		}
	}

	if (effectp[2])
	{
		if (ParticleTimer[2] <= GAMEPLAY::GET_GAME_TIMER())
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 18905, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 57005, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_R_Foot, 0.1f, 0, 0, 0);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_Spine_Root, 0.1f, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(72, 236, 232);
			ParticleTimer[2] = GAMEPLAY::GET_GAME_TIMER() + 1000;
		}
	}

	if (effectp[3])
	{
		if (ParticleTimer[3] <= GAMEPLAY::GET_GAME_TIMER())
		{
			//char *pt1 = "ent_liquid_cont";
			//char *pt2 = "ent_sht_flame";
			//float Size = 6.0f;
			////STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			////GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			////GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, Size, 0, 0, 0);
			////STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			////GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			////GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 18905, Size, 0, 0, 0);
			////STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			////GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			////GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 57005, Size, 0, 0, 0);
			////STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			////GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			////GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_L_Foot, Size, 0, 0, 0);
			//STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			//GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			//GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 3, 90, 0, 0, SKEL_R_Foot, Size, 0, 0, 0);
			////STREAMING::REQUEST_NAMED_PTFX_ASSET(pt1);
			////GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(pt1);
			////GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(pt2, PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, SKEL_Spine_Root, Size, 0, 0, 0);
			//GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(72, 236, 232);
			//ParticleTimer[3] = GAMEPLAY::GET_GAME_TIMER() + 1000;
		}
	}
#pragma endregion

#pragma region Veh
	if (VehSpawnMethod)
	{
		// VEHICLE::CREATE_VEHICLE(_Hash, MyCoord.x, MyCoord.y, MyCoord.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + (TeleAutomIncar ? 0 : 90), 1, 0);
		if (Create_Vehicle(SpawnVehMethod_Hash))
			VehSpawnMethod = false;
	}

	if (DriveOnWater)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(DriveOnWaterOBJ))
			Create_obj(GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::PLAYER_PED_ID(), 0, 0, -20.0f), true, &DriveOnWaterOBJ);
		else
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(DriveOnWaterOBJ);
			int pveh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			Vector3 pcoord;
			if (pveh != 0)
				pcoord = ENTITY::GET_ENTITY_COORDS(pveh, true);
			else
				pcoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Vector3 prot = GET_GAMEPLAY_CAM_ROT_orig(2);
			ENTITY::SET_ENTITY_COORDS(DriveOnWaterOBJ, pcoord.x, pcoord.y, -FloatZ_DriveOnWater, 0, 0, 0, 1);
			ENTITY::SET_ENTITY_ROTATION(DriveOnWaterOBJ, prot.x, prot.y, prot.z, 2, 1);
			ENTITY::SET_ENTITY_HEADING(DriveOnWaterOBJ, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
			ENTITY::FREEZE_ENTITY_POSITION(DriveOnWaterOBJ, true);
		}
	}

	int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

	if (VehicleColor_Bool[0])
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, VehicleColor.R, VehicleColor.G, VehicleColor.B);

	if (VehicleColor_Bool[1])
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, VehicleColor.R, VehicleColor.G, VehicleColor.B);

	if (VehicleColor_Bool[2])
	{
		VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, VehicleColor.R, VehicleColor.G, VehicleColor.B);
	}
#pragma endregion

#pragma region Object
	if (_HashGun)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target))
		{
			if (Target != 0)
			{
				char buffer[200];
				snprintf(buffer, 200, "Object Hash: 0x%X", ENTITY::GET_ENTITY_MODEL(Target));
				//DRAW_TEXT(buffer, 0.5, 0.05, 0.6, 0.6, 0, true, false, true, false, SelectColour.R, SelectColour.G, SelectColour.B, 255);
				NotifyDown(buffer, 1);
			}
		}
	}

	if (Create_Map)
	{
		Vector3 Coord = CAM2::GET_COORDS_INFRONT(7);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Create_Hash))
		{
			if (!STREAMING::HAS_MODEL_LOADED(Create_Hash))
				REQUEST_MODEL(Create_Hash);
			else
			{
				if (!ENTITY::DOES_ENTITY_EXIST(Create_Obj_Spawned))
					Create_Obj_Spawned = OBJECT::CREATE_OBJECT(Create_Hash, Coord.x, Coord.y, Coord.z, true, true, false);
				else
				{
					ENTITY::FREEZE_ENTITY_POSITION(Create_Obj_Spawned, true);
					SpawnedEntityList[spawnedindex__] = Create_Obj_Spawned;
					SpawnedEntityName[spawnedindex__] = Create_Map_string;
					SpawnedEntityNames[spawnedindex__] = Create_Map_strings;
					if (spawnedindex__ >= 40)
						spawnedindex__ = 0;
					else
						spawnedindex__++;

					Last_Object = Create_Obj_Spawned;
					Create_Obj_Spawned = 0;
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Create_Hash);
					addMessageShow("スポーンが完了しました。");
					Create_Map = false;
				}
			}
		}
		else
		{
			addMessageShow("モデルの読み込みに失敗しました。");
			Create_Map = false;
		}
	}
#pragma endregion

#pragma region CameraFar
	if (CameraFar)
	{
		CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(ZoomVar, ZoomVar);
		//Vector3 _aaa = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		//if (FarCamera == 0)
		//{
		//	//FarCamera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
		//	FarCamera = CAM::CREATE_CAMERA(26379945, false);
		//	CAM::SET_CAM_COORD(FarCamera, _aaa.x, _aaa.y, _aaa.z);
		//	CAM::SET_CAM_ACTIVE(FarCamera, true);
		//	CAM::RENDER_SCRIPT_CAMS(true, 1, 10, 1, 0);
		//	CAM::ATTACH_CAM_TO_PED_BONE1(FarCamera, PLAYER::PLAYER_PED_ID(), -1, 0, -10, 10, CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING());
		//	ENTITY::ATTACH_ENTITY_TO_ENTITY(FarCamera, PLAYER::PLAYER_PED_ID(), -1, 0, -10, 10, 0, 0, 1, 1, 1, 1, 1, 1, 1);
		//}
		//else
		//{
		//	//Vector3 rot_2 = GET_GAMEPLAY_CAM_ROT_orig(2);
		//	//Vector3 _222 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 2);
		//	//Vector3 loc_2 = CAM::GET_GAMEPLAY_CAM_COORD();
		//	//ENTITY::ATTACH_ENTITY_TO_ENTITY(FarCamera, PLAYER::PLAYER_PED_ID(), -1, 0, -10, 10, rot_2.x, rot_2.y, rot_2.z, 1, 1, 1, 1, 1, 1);
		//	//CAM::SET_CAM_ROT_V2(FarCamera, _222.y, _222.y, _222.z);
		//	//CAM::SET_CAM_COORD(FarCamera, loc_2.x, loc_2.y, loc_2.z);
		//}
		//else
		//{
	
		//	CAM::ATTACH_CAM_TO_PED_BONE1(FarCamera, PLAYER::PLAYER_PED_ID(), -1, 0, -10, 0, true);
		//	//CAM::SET_CAM_FAR_CLIP(FarCamera, 100);
		//	addMessageShow("パッチしました！");
		//	CameraFar = false;
		//}
	}
#pragma endregion

#pragma region ModelChange
	if (ChangeModel)
	{
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) != ModelChangerHash)
		{
			Vehicle CurrentVeh;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
				CurrentVeh = MyCar;
			REQUEST_MODEL(ModelChangerHash);
			if (STREAMING::HAS_MODEL_LOADED(ModelChangerHash))
			{
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ModelChangerHash);
				for (int i = 0; i < 57; i++)
				{
					WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), WepArray[i], -1, 1, 1);
					BruteForceWeaponAddons(PLAYER::PLAYER_PED_ID(), WepArray[i], true);
				}
				if (_ChangeModel[0])
					PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());

				if (_ChangeModel[1])
					PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), false);
				if (ModelChangerHash == 0xB881AEE)//hc_gunman
				{
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 3, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, 0, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 1, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 1, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 1, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 1, 0, 0);
				}
				else if (ModelChangerHash == 0xD86B5A95)//a_c_deer
					ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
				else if (ModelChangerHash == 0x1250D7BA)//a_c_mtlion
					PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), false);
				/*if (ModelChangerHash == 0x705E61F2 ||
					ModelChangerHash == 0x1615AD62 ||
					ModelChangerHash == 0x9C9EFFD8 ||
					ModelChangerHash == 0xD174E983)//mp_m_freemode_01 mp_m_freemode_02 mp_f_freemode_01 mp_f_freemode_02
				{
				}*/
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ModelChangerHash);
				ChangeModel = false;
			}
		}
		else
			ChangeModel = false;
	}
#pragma endregion

#pragma region WeaponMenu

	//燃える弾
	if (FireAmmo)
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());

	//爆発する弾
	if (ExplosionAmmo)
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());

	//デリートガン
	if (DeleteGun)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			if (ENTITY::DOES_ENTITY_EXIST(Target))
			{
				for (int i = 0; i < 16; i++)
				{
					if (PLAYER::IS_PLAYER_TARGETTING_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(i))) {
						return;
					}
				}
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target);
			//	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
				
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
								//ChangeEntityOwner(PedID, PLAYER::PLAYER_ID());
								NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PedID);
								AI::CLEAR_PED_TASKS_IMMEDIATELY(PedID);
								AI::CLEAR_PED_SECONDARY_TASK(PedID);
								ENTITY::DELETE_ENTITY(&Target);
							}
						}
						//ChangeEntityOwner(Target, PLAYER::PLAYER_ID());
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
						ENTITY::DELETE_ENTITY(&Target);
						ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
					}
					else
					{
						ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
						ENTITY::DELETE_ENTITY(&Target);
						//PED::DELETE_PED(&Target);
						
					}
				}
				else if (ENTITY::IS_ENTITY_A_VEHICLE(Target))
				{
					ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
					ENTITY::DELETE_ENTITY(&Target);
					//VEHICLE::DELETE_VEHICLE(&Target);
					
				}
				else if (ENTITY::IS_ENTITY_AN_OBJECT(Target))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);
					ENTITY::DETACH_ENTITY(Target, 1, 1);
					ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
					ENTITY::DELETE_ENTITY(&Target);
				}
				else
				{
					ENTITY::SET_ENTITY_COORDS(Target, 6000.0, 6000.0, 6000.0, true, false, false, true);
					ENTITY::DELETE_ENTITY(&Target);
				
				}
			}
		}
	}

	if (InfAmmo1)
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 1);
	}

	if (_OneShot)
	{
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 999999.0f);
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
				Vector3 ToCoord = CAM2::GET_COORDS_FROM_CAM(75);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoord.x, FromCoord.y, FromCoord.z, ToCoord.x, ToCoord.y, ToCoord.z, 250, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 0, 750);//250
				RapidFireDelay = GAMEPLAY::GET_GAME_TIMER() + 50;
			}
		}
	}

	if (Shot_to_add)
	{
		if (Shot_To_Add_Timer < GAMEPLAY::GET_GAME_TIMER())
		{
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Target) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				if (ENTITY::IS_ENTITY_AN_OBJECT(Target) || ENTITY::IS_ENTITY_A_VEHICLE(Target))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Target);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 0, 1);

					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Target))
					{

						SpawnedEntityList[spawnedindex__] = Target;
						SpawnedEntityName[spawnedindex__] = "追加したオブジェクト";

						if (spawnedindex__ >= 40)
							spawnedindex__ = 0;
						else
							spawnedindex__++;

						addMessageShow("追加しました！");
					}
					else
					{
						addMessageShow("追加リクエストに失敗しました。再度撃ってください");
					}
				}
			}
			Shot_To_Add_Timer = GAMEPLAY::GET_GAME_TIMER() + 200;
		}
	}

	if (VehicleGun)
	{
		if (!VehicleGun_ShotFlag)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				VehicleGun_int = 0;
				VehicleGun_ShotFlag = true;
			}
		}
		else
		{
			int _hash = GAMEPLAY::GET_HASH_KEY(ShootVehicleChar[SelectedShotVehicleVar]);
			REQUEST_MODEL(_hash);
			float AAA[] = { 0.0f, 3.0f, 2.0f };
			Vector3 UNKO = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS_orig(PLAYER::PLAYER_PED_ID(), AAA);
			float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			if (!ENTITY::DOES_ENTITY_EXIST(VehicleGun_int))
			{
				VehicleGun_int = VEHICLE::CREATE_VEHICLE(_hash, UNKO.x, UNKO.y, UNKO.z, heading, 1, 0);
			}
			else
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(_hash);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(VehicleGun_int, 90.0);
				VehicleGun_ShotFlag = false;
			}
		}
	}
	/* //マグネットガン
	//if (MagnetGun)
	//{
	//	if (isPress(Button_L2))
	//	{
	//		//int UpDown = Analog(INPUT_SCRIPT_RIGHT_AXIS_Y);
	//		/*Vector3 targetPos = GET_GAMEPLAY_CAM_COORD_orig();
	//		Vector3 Direction = RotationToDirection(GET_GAMEPLAY_CAM_ROT_orig(2));
	//		Direction.x *= distanceFromCam;
	//		Direction.y *= distanceFromCam;
	//		Direction.z *= distanceFromCam;

	//		targetPos.x += Direction.x;
	//		targetPos.y += Direction.y;
	//		targetPos.z += Direction.z;

	//		drawText(FtoS(targetPos.x, 10), 0, 0.5, 0.5, 0.3, 0.3, 255, 255, 255, 255, true);
	//		drawText(FtoS(targetPos.y, 10), 0, 0.5, 0.5 + 0.25, 0.3, 0.3, 255, 255, 255, 255, true);
	//		drawText(FtoS(targetPos.z, 10), 0, 0.5, 0.5 + 0.25 + 0.25, 0.3, 0.3, 255, 255, 255, 255, true);

	//		Vector3 targetPos = CAM2::GET_COORDS_FROM_CAM(4);

	//		///*( * distanceFromCam);*/
	/*//		//DrawMarker(DebugSphere, targetPos, newVector3(0, 0, 0), newVector3(0, 0, 0), newVector3(0.5f, 0.5f, 0.5f), newRGBA(255, 0, 0, 150));
	//		//Vehicle _Vehicle = GetClosestVehicle(targetPos, 18.7);
	//		uint32_t vehs[11];
	//		int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

	//		for (int i = 1; i < count + 1; i++)
	//		{
	//			//if (ENTITY::IS_ENTITY_AT_COORD(vehs[i], targetPos.x, targetPos.y, targetPos.z, 18.7, 18.7, 18.7, 0, 0, 0))
	//			//{
	//				if (vehs[i] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
	//				{
	//					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[i]);
	//					ENTITY::FREEZE_ENTITY_POSITION(vehs[i], false);
	//					Oscillate(vehs[i], targetPos, 4, 4);
	//				}
	//			//}
	//		}
	//	}
	//} */
#pragma endregion

#pragma region Animation
	if (WalkingChanger)
	{
		if (WalktypeVar == 0)
		{
			STREAMING::REQUEST_ANIM_SET("move_ped_crouched");
			if (STREAMING::HAS_ANIM_SET_LOADED("move_ped_crouched"))
			{
				PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_ped_crouched", 1.0f);
				PED::SET_PED_STRAFE_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_ped_crouched_strafing");
			}
		}
		else
		{
			STREAMING::REQUEST_ANIM_SET(_WalkType[WalktypeVar - 1]);
			if (STREAMING::HAS_ANIM_SET_LOADED(_WalkType[WalktypeVar - 1]))
			{
				PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), _WalkType[WalktypeVar - 1], 1048576000);
			}
		}
	}

	if (AnimFreezeMe)
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
		AI::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
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

	if (SetPlayerAnimation)
	{
		STREAMING::REQUEST_ANIM_DICT(Animations2[0]);
		if (STREAMING::HAS_ANIM_DICT_LOADED(Animations2[0]))
		{
			Vector3 MyCoordsForTPtoMe2222 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
			int scene2 = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE_3(MyCoordsForTPtoMe2222.x, MyCoordsForTPtoMe2222.y, MyCoordsForTPtoMe2222.z, 0, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(selectedPlayer)), 2, 0, 1, 1.0f, 0.0f, 1.0f);
			PED::SET_SYNCHRONIZED_SCENE_RATE(scene2, 1000.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_4(PLAYER::GET_PLAYER_PED(selectedPlayer), scene2, Animations2[0], Animations2[1], 8.0f, -8.0, 5, 0, 30, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(scene2);
			SetPlayerAnimation = false;
		}
	}
#pragma endregion

#pragma region Protections
	if (OffLineFlag == false && isOnline() && NETWORK::NETWORK_IS_IN_SESSION() && ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && !GAMEPLAY::IS_STRING_NULL_OR_EMPTY(PS3::ReadString_1(0x400236B8)))
	{
		printf("\n\n\nProtected");
		ProtectionTimer = GAMEPLAY::GET_GAME_TIMER() + 6000;
		OffLineFlag = true;
	}

	if ((!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION()) && (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER()) && !GAMEPLAY::IS_STRING_NULL_OR_EMPTY(PS3::ReadString_1(0x400236B8)))
		ProtectionTimer = GAMEPLAY::GET_GAME_TIMER() + 10000;

	if (OffLineFlag)
	{
		if (KICK_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(0x1357D44) != 0x907E0004)
					PS3::WriteUInt32(0x1357D44, 0x907E0004);

				if (PS3::ReadUInt32(0x1370334) != 0x907E0004)
					PS3::WriteUInt32(0x1370334, 0x907E0004);

				if (PS3::ReadUInt32(0x12D1D88) != 0x7C0802A6)
					PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);

				if (PS3::ReadUInt32(0x1358AFC) != 0x7C0802A6)
					PS3::WriteUInt32(0x1358AFC, 0x7C0802A6);
			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER())
				{
					if (PS3::ReadUInt32(0x1357D44) != 0x60000000) //ON
						PS3::WriteUInt32(0x1357D44, 0x60000000);

					if (PS3::ReadUInt32(0x1370334) != 0x60000000) //ON
						PS3::WriteUInt32(0x1370334, 0x60000000);

					if (PS3::ReadUInt32(0x12D1D88) != 0x4E800020) //ON
						PS3::WriteUInt32(0x12D1D88, 0x4E800020);

					if (PS3::ReadUInt32(0x1358AFC) != 0x4E800020) //ON
						PS3::WriteUInt32(0x1358AFC, 0x4E800020);
				}
			}
		}

		if (PARADISE_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(0x9FFE90) != R_NOP) //ON
					PS3::WriteUInt32(0x9FFE90, R_NOP); //Drop Kick

				if (PS3::ReadUInt32(0x9FBB58) != 0x7FE10808) //OFF
					PS3::WriteUInt32(0x9FBB58, 0x7FE10808);

				if (PS3::ReadUInt32(0x9FBB5C) != 0x4BFFFDA8)
					PS3::WriteUInt32(0x9FBB5C, 0x4BFFFDA8);

				if (PS3::ReadUInt32(0x9FB990) != 0x7FE10808)
					PS3::WriteUInt32(0x9FB990, 0x7FE10808);
			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER() && !isPlayerPlayingNProgress())
				{
					if (PS3::ReadUInt32(0x9FFE90) != NOP) //ON
						PS3::WriteUInt32(0x9FFE90, NOP); //Drop Kick

					if (PS3::ReadUInt32(0x9FBB58) != 0x4E800020) //ON
						PS3::WriteUInt32(0x9FBB58, 0x4E800020);

					if (PS3::ReadUInt32(0x9FBB5C) != 0x4E800020)
						PS3::WriteUInt32(0x9FBB5C, 0x4E800020);

					if (PS3::ReadUInt32(0x9FB990) != 0x4E800020)
						PS3::WriteUInt32(0x9FB990, 0x4E800020);

					PS3::Write_Global(1588610 + (PLAYER::PLAYER_ID() + 1), 19);
				}
			}
		}

		if (RCE_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(GIVE_PICKUP_REWARDS_EVENT) != R_NOP) //ON
					PS3::WriteUInt32(GIVE_PICKUP_REWARDS_EVENT, R_NOP);

			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER() && PS3::ReadUInt32(GIVE_PICKUP_REWARDS_EVENT) != NOP) //ON
					PS3::WriteUInt32(GIVE_PICKUP_REWARDS_EVENT, NOP);
			}
		}

		if (CLEARAREA_ALL)
		{
			Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			GAMEPLAY::CLEAR_AREA(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, true, 0, 0, 0);
			GAMEPLAY::CLEAR_AREA_OF_COPS(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, 0);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, 0);
			GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, 0, 0, 0, 0, 0);
			GAMEPLAY::CLEAR_AREA_OF_PEDS(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, 0);
			GAMEPLAY::CLEAR_AREA_OF_PROJECTILES(MyCoord.x, MyCoord.y, MyCoord.z, 1000000, 0);
		}

		if (VehicleFreezeProtectionDelay < GAMEPLAY::GET_GAME_TIMER())
		{
			if (VEHATTACH_P || CLEARVEH_ALL)
			{
				const int numElements = 10;
				const int arrSize = numElements + 1;  //Start at index 2, and the odd elements are padding
				uint32_t vehs[arrSize];
				vehs[0] = numElements;
				int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);
				for (int i = 0; i < count; ++i)
				{
					int offsettedID = i + 1;
					if (ENTITY::DOES_ENTITY_EXIST(vehs[offsettedID]) && VEHATTACH_P)
					{
						if (ENTITY::IS_ENTITY_ATTACHED(vehs[offsettedID]))
						{
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
							if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehs[offsettedID]))
							{
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehs[offsettedID], 0, 1);
								ENTITY::DELETE_ENTITY(&vehs[offsettedID]);
								addMessageShow("アタッチされた車両を削除しました。");
							}
						}
					}

					if (CLEARVEH_ALL)
					{
						if (ENTITY::DOES_ENTITY_EXIST(vehs[offsettedID]))
						{
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]);
							if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehs[offsettedID]))
							{
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehs[offsettedID], 0, 1);
								ENTITY::DELETE_ENTITY(&vehs[offsettedID]);
							}
						}
					}
				}

			}
			VehicleFreezeProtectionDelay = GAMEPLAY::GET_GAME_TIMER() + 500;
		}

		if (Low_Tecture)
		{
			if (!Low_TextureWater)
				GRAPHICS::SET_TIMECYCLE_MODIFIER(Low_Texture_Strin9[Low_TextureVar]);
		}

		if (PEDATTACH_P)
		{
			if (NETWORK::NETWORK_IS_IN_SESSION())
			{
				Ped Closest;
				Vector3 MyCoord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				if (PED::GET_CLOSEST_PED(MyCoord.x, MyCoord.y, MyCoord.z, 5, true, true, &Closest, false, true, -1))
				{
					if (ENTITY::IS_ENTITY_ATTACHED(Closest))
					{
						if (!PED::IS_PED_A_PLAYER(Closest))
						{
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Closest);
							ENTITY::DETACH_ENTITY(Closest, 1, 1);
							PED::DELETE_PED(&Closest);
							ENTITY::DELETE_ENTITY(&Closest);
						}
					}
				}
			}
		}

		if (SCRIPT_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(0x12CBD94) != 0x7C0802A6)
					PS3::WriteUInt32(0x12CBD94, 0x7C0802A6);
				if (PS3::ReadUInt32(0x12D1D88) != 0x7C0802A6)
					PS3::WriteUInt32(0x12D1D88, 0x7C0802A6);
				if (PS3::ReadUInt32(0x172D78C) != 0x40820068)
					PS3::WriteUInt32(0x172D78C, 0x40820068);
				if (PS3::ReadUInt32(0x1358F9C) != 0x38600001)
					PS3::WriteUInt32(0x1358F9C, 0x38600001);
				if (PS3::ReadUInt32(0x1358F08) != 0x907E0004)
					PS3::WriteUInt32(0x1358F08, 0x907E0004);
			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER())
				{
					if (PS3::ReadUInt32(0x12CBD94) != 0x4E800020)
						PS3::WriteUInt32(0x12CBD94, 0x4E800020);

					if (PS3::ReadUInt32(0x12D1D88) != 0x4E800020)
						PS3::WriteUInt32(0x12D1D88, 0x4E800020);

					if (PS3::ReadUInt32(0x172D78C) != 0x41820094)
						PS3::WriteUInt32(0x172D78C, 0x41820094);

					if (PS3::ReadUInt32(0x1358F9C) != 0x60000000)
						PS3::WriteUInt32(0x1358F9C, 0x60000000);

					if (PS3::ReadUInt32(0x1358F08) != 0x60000000)
						PS3::WriteUInt32(0x1358F08, 0x60000000);
				}
			}
		}

		if (STATUS_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(NETWORK_INCREMENT_STAT_EVENT) != 0x7C0802A6)
					PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, 0x7C0802A6);
			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER())
				{
					if (PS3::ReadUInt32(NETWORK_INCREMENT_STAT_EVENT) != 0x4E800020)
						PS3::WriteUInt32(NETWORK_INCREMENT_STAT_EVENT, 0x4E800020);
				}
			}
		}

		if (WEATHER_P)
		{
			if (!isOnline() || !NETWORK::NETWORK_IS_IN_SESSION())
			{
				if (PS3::ReadUInt32(GAME_WEATHER_EVENT) != 0x7C0802A6)
					PS3::WriteUInt32(GAME_WEATHER_EVENT, 0x7C0802A6);

				if (PS3::ReadUInt32(GAME_CLOCK_EVENT) != 0x7C0802A6)
					PS3::WriteUInt32(GAME_CLOCK_EVENT, 0x7C0802A6);
			}
			else
			{
				if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER() && !isPlayerPlayingNProgress())
				{
					if (PS3::ReadUInt32(GAME_WEATHER_EVENT) != 0x4E800020)
						PS3::WriteUInt32(GAME_WEATHER_EVENT, 0x4E800020);

					if (PS3::ReadUInt32(GAME_CLOCK_EVENT) != 0x4E800020)
						PS3::WriteUInt32(GAME_CLOCK_EVENT, 0x4E800020);
				}
			}
		}

		if (MapDelete_)
		{
			//ss1_lod_01_02_08_09_10_11
			//ss1_lod_slod3

			//dt1_10_build1_lod
			//dt1_lod_slod3
			//ch1_lod_slod3b
			GRAPHICS::_0xA706E84D();
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_lod_slod3"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ch1_lod_slod3b"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("prop_Ld_ferris_wheel"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_11_dt1_tower"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_05_build1_h"));//dt1_05_slod //dt1_05_build2_h
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_05_slod"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_11_flats"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_11_Flats_LOD"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_lod_slod3"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ap1_lod_slod4"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("SS1_02_SLOD1"));//4203348961 ch2_lod2_slod2a
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(4203348961);
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ch2_lod2_slod2a")); 
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_lod_03_04_05_11")); //dt1_lod_slod3
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_lod_slod3"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_05_build2_h"));//dt1_03_build2top

			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_12_build6"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_12_build1"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_12_build2"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_12_build3"));
			INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("hei_dt1_20_build2"));
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_03_build2top")); // hei_dt1_02_w01
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("hei_dt1_02_w01")); //dt1_10_build1_lod
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_10_build1_lod"));
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_lod_slod3"));
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("ss1_lod_01_02_08_09_10_11"));
			//INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("dt1_10_build1_lod"));
			GRAPHICS::_0x0DCC0B8B();
		}

		if (AutoClearArea)
		{
			if (ProtectionTimer < GAMEPLAY::GET_GAME_TIMER())
			{
				if (fps < 20)
				{
					if (PS3::ReadUInt32(0x13AE688) != 0x4E800020)
					{
						PS3::WriteUInt32(0x13AE688, 0x4E800020);
					}

					Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
					GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 100000000, true, 0, 0, 0);
					GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
					GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
					GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 100000000, 0, 0, 0, 0, 0);
					GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 100000000, 0);
					KEIRYOU_P_SUBTIMER = GAMEPLAY::GET_GAME_TIMER() + 2000;
				}
			}
			else
			{
				if (PS3::ReadUInt32(0x13AE688) != 0x7C0802A6)
				{
					PS3::WriteUInt32(0x13AE688, 0x7C0802A6);
				}
			}
		}
	}

	if (OBJECT_P)
	{
		*(int*)(0x1C6B918) = *(int*)((int)&give_control_events);
		*(int*)(0x1C6B918 + 0x04) = *(int*)((int)&give_control_events + 0x4);
	}
	//1C5C608
	if (DETECTION_P)
	{
		//PS3::WriteUInt32(0x1C4FAF0, 0xA199C0);
		//request_control_events
		//*(int*)(0x1C6B8E0) = *(int*)((int)&request_control_events);
		//*(int*)(0x1C6B8E0 + 0x04) = *(int*)((int)&request_control_events + 0x04);
		//*(int*)(0x1C4FAF0) = *(int*)((int)&HOST_SCRIPT_FUNC); //0xA199C0
		//4BFFE3F1
		branch_link(*(int*)((int)&returnKicked), 0x139B61C);
		branch_link(*(int*)((int)&sub_173226C_S), 0x12D2160);

		*(int*)(0x1C6BA78) = *(int*)((int)&_GAME_CLOCK_EVENT);
		*(int*)((0x1C6BA78 + 0x4)) = *(int*)((int)&_GAME_CLOCK_EVENT + 0x4);

		*(int*)(0x1C6C0A8) = *(int*)((int)&_NETWORK_CLEAR_PED_TASKS_EVENT);
		*(int*)((0x1C6C0A8 + 0x4)) = *(int*)((int)&_NETWORK_CLEAR_PED_TASKS_EVENT + 0x4);

		*(int*)(0x1C6BD80) = *(int*)((int)&scriptEventDetour);
		*(int*)((0x1C6BD80 + 0x4)) = *(int*)((int)&scriptEventDetour + 0x4);

		*(int*)(0x1C6BAA8) = *(int*)((int)&WeatherEventProtection);
		*(int*)((0x1C6BAA8 + 0x4)) = *(int*)((int)&WeatherEventProtection + 0x4);

		*(int*)(0x1C6BF80) = *(int*)((int)&AnimproProtection);
		*(int*)((0x1C6BF80 + 0x4)) = *(int*)((int)&AnimproProtection + 0x4);

		//*(int*)(0x1C6C5F8) = *(int*)((int)&Givepickuprewardprotection);
		//*(int*)((0x1C6C5F8 + 0x4)) = *(int*)((int)&Givepickuprewardprotection + 0x4);

		*(int*)(0x1C6C530) = *(int*)((int)&NETWORKINCREMENTSTATEVENT);
		*(int*)((0x1C6C530 + 0x4)) = *(int*)((int)&NETWORKINCREMENTSTATEVENT + 0x4);

		*(int*)(0x1C707E0) = *(int*)((int)&_NETWORK_ENTITIES_EVENT);
		*(int*)((0x1C707E0 + 0x4)) = *(int*)((int)&_NETWORK_ENTITIES_EVENT + 0x4);
	}

#pragma endregion
	
#pragma region FunMenu
	if (doAnimation)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		STREAMING::REQUEST_ANIM_DICT(doAnimation_Animdict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(doAnimation_Animdict))
		{
			AI::TASK_PLAY_ANIM(pPlayer, doAnimation_Animdict, doAnimation_AnimID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			doAnimation = false;
		}
	}

	if (breathfire)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("ent_liquid_cont");
		GRAPHICS::_0x9C720B61("ent_liquid_cont");
		if (GAMEPLAY::GET_GAME_TIMER() > FireTimer)
		{
			if (isPress(Button_X))
			{
				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("ent_sht_flame", PLAYER::PLAYER_PED_ID(), FIRE_BREATH.x, FIRE_BREATH.y, FIRE_BREATH.z, 132.1525, 103.4502, 79.8993, SKEL_Head, 1, 0, 0, 0);
				FireTimer = GAMEPLAY::GET_GAME_TIMER() + 2000;
			}
		}
	}

	if (MinecraftMode)
	{
		timeoutMinecraft--;
		if (timeoutMinecraft < 0) {
			timeoutMinecraft = -1;
			if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID())) {
				//ButtonDisable(Button_R2);

				Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				int bone = PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 0x796E);
				Vector3 handcoords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), bone, 0, 0, 0);
				Vector3 c = CAM2::_GET_COORDS_INFRONT(distanceMinecraft);
				float cx = tmp.x + c.x;
				float cy = tmp.y + c.y;
				float cz = tmp.z + c.z;
				//int Type = -1;
				bool hit = true;

				float coeff = (1.0f / 1.5f);
				float x = _round(/*hitCoords.x*/cx*coeff) / coeff;
				float y = _round(/*hitCoords.y*/cy*coeff) / coeff;
				float z = _round(/*hitCoords.z*/cz*coeff) / coeff;
				GRAPHICS::DRAW_LINE(handcoords.x, handcoords.y, handcoords.z, x, y, z/*hitCoords.x,hitCoords.y,hitCoords.z*/, 255, 0, 0, 255);
				//GRAPHICS::DRAW_LINE(x,y,z,x,y,z+0.1f,0,0,255,255);
				//GRAPHICS::DRAW_LINE(x,y,z,x,y+0.1f,z,0,255,0,255);
				//GRAPHICS::DRAW_LINE(x,y,z,x+0.1f,y,z,255,255,255,255);
				Vector3 c1 = { x + 0.75f, y + 0.75f, z + 0.1f }; Vector3 c11 = { x + 0.75f, y + 0.75f, z - 1.5f + 0.1f };
				Vector3 c2 = { x + 0.75f, y - 0.75f, z + 0.1f }; Vector3 c22 = { x + 0.75f, y - 0.75f, z - 1.5f + 0.1f };
				Vector3 c3 = { x - 0.75f, y - 0.75f, z + 0.1f }; Vector3 c33 = { x - 0.75f, y - 0.75f, z - 1.5f + 0.1f };
				Vector3 c4 = { x - 0.75f, y + 0.75f, z + 0.1f }; Vector3 c44 = { x - 0.75f, y + 0.75f, z - 1.5f + 0.1f };
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

				if (isPressed(Button_R1) == true) {
					M_Coord.x = x;
					M_Coord.y = y;
					M_Coord.z = z;
					M_Rot.x = 0;
					M_Rot.y = 180;
					M_Rot.z = 0;

					M_Hash = GAMEPLAY::GET_HASH_KEY("prop_mb_sandblock_01");
					MinecraftMode_Spawn = true;
					timeoutMinecraft = 100;
				}
				ButtonDisable(Button_R1);
			}
		}

		if (MinecraftMode_Spawn)
		{
			if (STREAMING::IS_MODEL_IN_CDIMAGE(M_Hash))
			{
				if (!STREAMING::HAS_MODEL_LOADED(M_Hash))
					REQUEST_MODEL(M_Hash);
				else
				{
					if (!ENTITY::DOES_ENTITY_EXIST(M_Spawned))
						M_Spawned = OBJECT::CREATE_OBJECT(M_Hash, M_Coord.x, M_Coord.y, M_Coord.z, true, true, true);
					else
					{
						//NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(M_Spawned);
						ENTITY::SET_ENTITY_COLLISION(M_Spawned, true, 1);

						ENTITY::SET_ENTITY_ROTATION(M_Spawned, M_Rot.x, M_Rot.y, M_Rot.z, 2, 1);
						ENTITY::FREEZE_ENTITY_POSITION(M_Spawned, true);
						ENTITY::SET_ENTITY_COORDS(M_Spawned, M_Coord.x, M_Coord.y, M_Coord.z, 0, 0, 0, 1);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(M_Hash);
						//ENTITY::SET_ENTITY_COORDS(M_Spawned, M_Coord.x, M_Coord.y, M_Coord.z, 0, 0, 0, 1);

						M_Spawned = 0;
						MinecraftMode_Spawn = false;
					}
				}
			}
			else
			{
				addMessageShow("モデルの読み込みに失敗しました。");
			}
		}
	}

	if (ParachuteMod)
	{
		//ButtonDisable(Button_L3);
		//ButtonDisable(Dpad_Up);
		//ButtonDisable(Dpad_Down);

		int JIBUN = PLAYER::PLAYER_PED_ID();

		strcpy(ParachuteText, "Speed : ");
		strcat(ParachuteText, FtoS(ParachuteSpeed, 100));
		drawText(ParachuteText, 1, 0.3, 0.150, 0.4, 0.4, 255, 255, 0, 255, true, false);

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L3))
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(JIBUN, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"), 1, true);
			Freeze(JIBUN);
			ApplyForce(JIBUN, newVector3(0, 0, 50), newVector3(0, 0, 0));
			AI::TASK_PARACHUTE(JIBUN, true);
			PED::_0xA819680B(JIBUN); //FORCE_PED_TO_OPEN_PARACHUTE
		}

		if (PED::GET_PED_PARACHUTE_STATE(PLAYER::PLAYER_PED_ID()) == 2)
		{
			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
			{
				AI::SET_PARACHUTE_TASK_THRUST(JIBUN, 2.5f);
			}
			else
			{
				AI::SET_PARACHUTE_TASK_THRUST(JIBUN, ParachuteSpeed);
			}
		}

		if (isPressed(Dpad_Up))
		{
			if (ParachuteSpeed > 10.0f)
			{
				ParachuteSpeed = 10.0f;
			}
			else
			{
				ParachuteSpeed += 0.5f;
			}
		}

		if (isPressed(Dpad_Down))
		{
			if (ParachuteSpeed < 0.0f)
			{
				ParachuteSpeed = 0.0f;
			}
			else
			{
				ParachuteSpeed -= 0.5f;
			}
		}
	}

	if (DragonFireCameraResetToggle > 0)
		DragonFireCameraResetToggle--;
	else if (DragonFireCameraResetToggle == 0)
	{
		CAM::RENDER_SCRIPT_CAMS1(0, 0, 3000, 1, 0);
		DragonFireCameraResetToggle = -1;
	}

	/*if (Psychokinetic_v2)
	{
		if (isPress(Button_R1))
		{
			ButtonDisable(Button_R1);

			char *dict1 = "move_m@generic";
			char *anim1 = "sprint";
			int player_ped = PLAYER::PLAYER_PED_ID();
			int Analog_LEFT_X = Analog(188);
			int Analog_LEFT_Y = Analog(189);
			float Rotation_Z = ENTITY::GET_ENTITY_HEADING(player_ped);

			Analog_LEFT_X -= 127;

			if (Analog_LEFT_X != 0)
				Rotation_Z -= 0.02 * SYSTEM::TO_FLOAT(Analog_LEFT_X);

			char aaa__[100];
			snprintf___(aaa__, 100, "Input : %i[%i]\nRotation : %f[%f]", Analog_LEFT_X, Analog_LEFT_X + 127, Rotation_Z, 0.02 * SYSTEM::TO_FLOAT(Analog_LEFT_X));
			drawText(aaa__, 0, 0.5, 0.5, 0.4, 0.4, 255, 255, 255, 255, true);

			if ((!PED::IS_PED_FALLING(player_ped)) && (!PED::IS_PED_SWIMMING_UNDER_WATER(player_ped)) && (!ENTITY::IS_ENTITY_PLAYING_ANIM(player_ped, dict1, anim1, 3)))
			{
				AI::TASK_PLAY_ANIM(player_ped, dict1, anim1, 8.0, -8.0, -1, 9, 0, 0, 0, 0);
			}

			ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), 0, 0, Rotation_Z, true, true);
		}
	}*/
	
#pragma endregion

#pragma region Recovery
	if (FullHack)
	{
		if (_FullHack_time == -1)
		{
			//PS3::Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 0xEB, 0x01);
			//PS3::Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 0xEC, 0x02);
			//PS3::Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 0xED, 0x03);
			//STAT_SET_INT("PROPERTY_HOUSE", 0x01, 1);
			//STAT_SET_INT("MULTI_PROPERTY_1", 0x02, 1);
			//STAT_SET_INT("MULTI_PROPERTY_2", 0x03, 1);

			#pragma region 所持品・アンロック・ステータス
		/*ステータス*/
			STAT_SET_INT("SCRIPT_INCREASE_STAM", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_STRN", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_SHO", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_STL", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_FLY", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_DRIV", 100, 1);
			STAT_SET_INT("SCRIPT_INCREASE_LUNG", 100, 1);

			/*足早*/
			STAT_SET_INT("CHAR_FM_ABILITY_1_UNLCK", 600, -1);
			STAT_SET_INT("CHAR_FM_ABILITY_2_UNLCK", 600, -1);
			STAT_SET_INT("CHAR_FM_ABILITY_3_UNLCK", 600, -1);

			/*無限ローリング*/
			STAT_SET_INT("SHOOTING_ABILITY", 15000, -1);

			/*アーマー*/
			STAT_SET_INT("MP_CHAR_ARMOUR_1_COUNT", INT_MAX, 1);
			STAT_SET_INT("MP_CHAR_ARMOUR_2_COUNT", INT_MAX, 1);
			STAT_SET_INT("MP_CHAR_ARMOUR_3_COUNT", INT_MAX, 1);
			STAT_SET_INT("MP_CHAR_ARMOUR_4_COUNT", INT_MAX, 1);
			STAT_SET_INT("MP_CHAR_ARMOUR_5_COUNT", INT_MAX, 1);

			/*スナック*/
			STAT_SET_INT("NO_BOUGHT_YUM_SNACKS", INT_MAX, 1);
			STAT_SET_INT("NO_BOUGHT_HEALTH_SNACKS", INT_MAX, 1);
			STAT_SET_INT("NO_BOUGHT_EPIC_SNACKS", INT_MAX, 1);
			STAT_SET_INT("MP0_NUMBER_OF_ORANGE_BOUGHT", INT_MAX, 1);
			STAT_SET_INT("MP0_CIGARETTES_BOUGHT", INT_MAX, 1);

			/*花火*/
			STAT_SET_INT("FIREWORK_TYPE_1_WHITE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_1_RED", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_1_BLUE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_2_WHITE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_2_RED", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_2_BLUE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_3_WHITE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_3_RED", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_3_BLUE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_4_WHITE", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_4_RED", INT_MAX, 1);
			STAT_SET_INT("FIREWORK_TYPE_4_BLUE", INT_MAX, 1);

			/*タバコ*/
			STAT_SET_INT("CIGARETTES_BOUGHT", INT_MAX, 1);

			/*LSC*/
			STAT_SET_INT("RACES_WON", 50, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_1_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_2_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_3_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_4_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_5_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_6_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_CARMOD_7_UNLCK", -1, 1);
			STAT_SET_INT("AWD_FMRALLYWONDRIVE", 1, 1);
			STAT_SET_INT("AWD_FMRALLYWONNAV", 1, 1);
			STAT_SET_INT("AWD_FMWINSEARACE", 1, 1);
			STAT_SET_INT("AWD_FMWINAIRRACE", 1, 1);
			STAT_SET_INT("NUMBER_TURBO_STARTS_IN_RACE", 50, 1);
			STAT_SET_INT("USJS_COMPLETED", 50, 1);
			STAT_SET_INT("AWD_FM_RACES_FASTEST_LAP", 50, 1);
			STAT_SET_INT("NUMBER_SLIPSTREAMS_IN_RACE", 100, 1);
			STAT_SET_INT("AWD_WIN_CAPTURES", 50, 1);                // Chrome Rims - Sport
			STAT_SET_INT("AWD_DROPOFF_CAP_PACKAGES", 100, 1);       // Chrome Rims - Lowrider
			STAT_SET_INT("AWD_KILL_CARRIER_CAPTURE", 100, 1);       // Chrome Rims - Offroad
			STAT_SET_INT("AWD_FINISH_HEISTS", 50, 1);               // Chrome Rims - High End
			STAT_SET_INT("AWD_FINISH_HEIST_SETUP_JOB", 50, 1);      // Chrome Rims - Tuner
			STAT_SET_INT("AWD_NIGHTVISION_KILLS", 100, 1);          // Chrome Rims - Bike
			STAT_SET_INT("AWD_WIN_LAST_TEAM_STANDINGS", 50, 1);     // Chrome Rims - SUV
			STAT_SET_INT("AWD_ONLY_PLAYER_ALIVE_LTS", 50, 1);       // Chrome Rims - Muscle

			/*Tatoo*/
			char *array3[] = { "AWD_FM_DM_WINS", "AWD_FM_TDM_MVP", "AWD_FM_DM_TOTALKILLS", "AWD_FMATTGANGHQ", "AWD_FMBBETWIN", "AWD_FMWINEVERYGAMEMODE", "AWD_FMRACEWORLDRECHOLDER", "AWD_FMFULLYMODDEDCAR", "AWD_FMMOSTKILLSSURVIVE", "AWD_FMKILL3ANDWINGTARACE", "AWD_FMKILLBOUNTY", "AWD_FMREVENGEKILLSDM", "AWD_FMKILLSTREAKSDM", "AWD_HOLD_UP_SHOPS", "AWD_LAPDANCES", "AWD_SECURITY_CARS_ROBBED", "AWD_RACES_WON", "AWD_CAR_BOMBS_ENEMY_KILLS", "PLAYER_HEADSHOTS", "DB_PLAYER_KILLS" };
			int array2[] = { 50, 50, 500, 5, 50000, 1, 1, 1, 1, 1, 25, 50, 10, 20, 25, 25, 50, 25, 500, 1000 };
			for (int j = 0; j < 20; j++)
			{
				STAT_SET_INT(array3[j], array2[j], 1);
			}

			/*Award*/
			char *array4[] = { "AWD_100_KILLS_PISTOL", "AWD_100_KILLS_SNIPER", "AWD_50_KILLS_GRENADES", "AWD_100_KILLS_SHOTGUN", "AWD_100_KILLS_SMG", "AWD_50_KILLS_ROCKETLAUNCH", "AWD_25_KILLS_STICKYBOMBS", "AWD_20_KILLS_MELEE", "AWD_100_HEADSHOTS", "AWD_50_VEHICLES_BLOWNUP", "AWD_VEHICLES_JACKEDR", "AWD_ENEMYDRIVEBYKILLS", "AWD_COPS_KILLED", "AWD_FM_DM_TOTALKILLS" };
			char *array5[] = { "AWD_LAPDANCES", "AWD_CARS_EXPORTED", "AWD_SECURITY_CARS_ROBBED", "AWD_5STAR_WANTED_AVOIDANCE", "AWD_VEHICLE_JUMP_OVER_40M", "AWD_RACES_WON", "AWD_CARS_EXPORTED", "AWD_NO_ARMWRESTLING_WINS", "AWD_WIN_AT_DARTS", "AWD_CAR_BOMBS_ENEMY_KILLS", "AWD_KILLS_ASSAULT_RIFLE", "AWD_KILLS_MACHINEGUN", "AWD_CARS_EXPORTED", "AWD_NO_HAIRCUTS", "AWD_PARACHUTE_JUMPS_50M", "AWD_PARACHUTE_JUMPS_20M", "AWD_FM_GOLF_BIRDIES", "AWD_FM_GOLF_WON", "AWD_FM_SHOOTRANG_TG_WON", "AWD_FM_SHOOTRANG_RT_WON", "AWD_FM_SHOOTRANG_CT_WON", "AWD_FM_TENNIS_WON", "AWD_FM_TENNIS_ACE", "AWD_FM_GTA_RACES_WON", "AWD_FM_RACES_FASTEST_LAP", "AWD_FM_RACE_LAST_FIRST", "AWD_FM_DM_WINS", "AWD_FM_TDM_WINS", "AWD_FM_TDM_MVP", "AWD_FM_DM_3KILLSAMEGUY", "AWD_FM_DM_STOLENKILL", "AWD_FMBASEJMP", "AWD_FMHORDWAVESSURVIVE", "AWD_FMCRATEDROPS", "AWD_FMRALLYWONDRIVE", "AWD_FMRALLYWONNAV", "AWD_FMWINRACETOPOINTS", "AWD_FMKILLBOUNTY", "AWD_FMOVERALLKILLS", "AWD_FMWINSEARACE", "AWD_FMREVENGEKILLSDM", "AWD_FMSHOOTDOWNCOPHELI", "AWD_FMMOSTFLIPSINONEVEHICLE", "AWD_FMMOSTSPINSINONEVEHICLE" };
			char *array6[] = { "AWD_FM6DARTCHKOUT", "AWD_FMWINEVERYGAMEMODE", "AWD_FMPICKUPDLCCRATE1ST", "AWD_FMWINALLRACEMODES", "AWD_FMRACEWORLDRECHOLDER", "AWD_FM50DIFITEMSCLOTHES", "AWD_FMFULLYMODDEDCAR", "AWD_FMWINCUSTOMRACE", "AWD_FM50DIFFERENTDM", "AWD_FM50DIFFERENTRACES", "AWD_FMMOSTKILLSGANGHIDE", "AWD_FMMOSTKILLSSURVIVE", "AWD_FMKILLCHEATER", "AWD_FMKILL3ANDWINGTARACE", "AWD_FMTATTOOALLBODYPARTS", "AWD_FMKILLSTREAKSDM", "AWD_FMFURTHESTWHEELIE", "AWD_DRIVE_ALL_COP_CARS", "AWD_FM_GOLF_HOLE_IN_1", "AWD_FM_SHOOTRANG_GRAN_WON", "AWD_FM_TENNIS_5_SET_WINS", "AWD_FM_TENNIS_STASETWIN", "AWD_BUY_EVERY_GUN", "AWD_FMATTGANGHQ" };
			char *array7[] = { "AWD_HOLD_UP_SHOPS", "AWD_FM_DM_KILLSTREAK", "AWD_FMBBETWIN" };
			int array8[] = { 500, 50, 1 };
			int array9[] = { 20, 100, 500000 };
			for (int j = 0; j < 14; j++)
			{
				STAT_SET_INT(array4[j], array8[0], 1);
			}

			for (int j = 0; j < 43; j++)
			{
				STAT_SET_INT(array5[j], array8[1], 1);
			}

			for (int j = 0; j < 23; j++)
			{
				STAT_SET_INT(array6[j], array8[2], 1);
			}

			for (int j = 0; j < 3; j++)
			{
				STAT_SET_INT(array7[j], array9[j], 1);
			}

			/*Parachute*/
			char *array14[] = { "CHAR_KIT_1_FM_UNLCK", "CHAR_KIT_2_FM_UNLCK", "CHAR_KIT_3_FM_UNLCK", "CHAR_KIT_4_FM_UNLCK", "CHAR_KIT_5_FM_UNLCK", "CHAR_KIT_6_FM_UNLCK", "CHAR_KIT_7_FM_UNLCK", "CHAR_KIT_8_FM_UNLCK", "CHAR_KIT_9_FM_UNLCK", "CHAR_KIT_10_FM_UNLCK", "CHAR_KIT_11_FM_UNLCK", "CHAR_KIT_12_FM_UNLCK", "CHAR_KIT_FM_PURCHASE", "CHAR_KIT_FM_PURCHASE2", "CHAR_KIT_FM_PURCHASE3", "CHAR_KIT_FM_PURCHASE4", "CHAR_KIT_FM_PURCHASE5", "CHAR_KIT_FM_PURCHASE6", "CHAR_KIT_FM_PURCHASE7", "CHAR_KIT_FM_PURCHASE8", "CHAR_KIT_FM_PURCHASE9", "CHAR_KIT_FM_PURCHASE10", "CHAR_KIT_FM_PURCHASE11", "CHAR_KIT_FM_PURCHASE12" };
			for (int i = 0; i < 24; i++)
			{
				STAT_SET_INT(array14[i], -1, 1);
			}

			/*銀行強盗 アイテム*/
			STAT_SET_INT("CHAR_FM_VEHICLE_1_UNLCK", -1, 1);
			STAT_SET_INT("CHAR_FM_VEHICLE_2_UNLCK", -1, 1);

			/*5％値引き*/
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("PLAYER_MUTED"), 0, 1);
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
			STAT_SET_INT("CHEAT_BITSET", 0, 1);
			STAT_SET_INT("BAD_SPORT_BITSET", 0, 1);
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

			/*報告削除*/
			char *array10[] = { "REPORT_STRENGTH", "COMMEND_STRENGTH", "FRIENDLY", "HELPFUL", "GRIEFING", "VC_ANNOYINGME", "VC_HATE", "OFFENSIVE_LANGUAGE", "OFFENSIVE_TAGPLATE", "OFFENSIVE_UGC", "BAD_CREW_NAME", "BAD_CREW_MOTTO", "BAD_CREW_STATUS", "BAD_CREW_EMBLEM", "GAME_EXPLOITS", "EXPLOITS", "ISPUNISHED" };
			int array11[] = { 0, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 17; i++)
			{
				char UNKO[50];
				strcpy(UNKO, "MPPLY_");
				strcat(UNKO, array10[i]);
				STAT_SET_INT(UNKO, array11[i], 1);
			}

			/*武器のカラー*/
			char *Array[] = {
				"ADMIN_WEAPON_GV_BS_1",
				"ADMIN_WEAPON_GV_BS_2",
				"ADMIN_WEAPON_GV_BS_3",
				"BOTTLE_IN_POSSESSION",
				"CHAR_FM_WEAP_UNLOCKED",
				"CHAR_FM_WEAP_UNLOCKED2",
				"CHAR_WEAP_FM_PURCHASE",
				"CHAR_WEAP_FM_PURCHASE2",
				"CHAR_FM_WEAP_ADDON_1_UNLCK",
				"CHAR_FM_WEAP_ADDON_2_UNLCK",
				"CHAR_FM_WEAP_ADDON_3_UNLCK",
				"CHAR_FM_WEAP_ADDON_4_UNLCK",
				"CHAR_FM_WEAP_ADDON_5_UNLCK",
				"WEAP_FM_ADDON_PURCH",
				"WEAP_FM_ADDON_PURCH2",
				"WEAP_FM_ADDON_PURCH3",
				"WEAP_FM_ADDON_PURCH4",
				"WEAP_FM_ADDON_PURCH5"
			};
			for (int i = 0; i < 18; i++)
			{
				STAT_SET_INT(Array[i], -1, 1);
			}
#pragma endregion
			//for (int i = 0; i < 10; i++)
			//{
			//	_0x3DB120_func(100000000000, 1);
			//}
		}
		uint GarageOffset = PS3::ReadUInt32(0x1E70390);

		if (_FullHack_time == -1)
		{
			for (int i = 0; i < 36; i++)
			{
				GarageEditor::Set_Chrome(GarageOffset, i);
				GarageEditor::Set_PatriotSmoke(GarageOffset, i);
				int r = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(150, 255);
				int g = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(150, 255);
				int b = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(150, 255);
				GarageEditor::Set_Color(GarageOffset, i, r, g, b);
				//GarageEditor::All_Delete(GarageOffset, i);
				GarageEditor::Set_Car(GarageOffset, i, 0);

			}

			_FullHack_time = 30;
		}
		else if (_FullHack_time > 0)
		{
			_FullHack_time--;
		}
		else if (_FullHack_time == 0)
		{
			for (int i = 0; i < 36; i++)
			{

				GarageEditor::Set_Car(GarageOffset, i, GAMEPLAY::GET_HASH_KEY(GarageEditor::GarageCars[i]));

				//GarageEditor::Set_PatriotSmoke(GarageOffset, i);
			}
			//PS3::WriteUInt32(GarageOffset + GarageEditor::Car_Hash + (0 * GarageEditor::All_Size), GAMEPLAY::GET_HASH_KEY("sovereign"));
			//Set_Chrome(GarageOffset, 0);
			//STAT_SET_INT("CASH_GIFT_NEW", INT_MAX, 1);
			STAT_SET_INT("SET_RP_GIFT_ADMIN", Ranks[120 - 1], 1);
			STAT_SET_INT("CHAR_SET_RP_GIFT_ADMIN", Ranks[120 - 1], 1);
			STAT_SET_INT("MPPLY_IS_HIGH_EARNER", 0, 0);
			//STAT_SET_INT("CASH_GIFT_RECEIVED", 1, 0);
			addMessageShow("[フルハック]Step.1 ガレージへ入る");
			addMessageShow("[フルハック]Step.2 ガレージ奥の青い円で全ての車をシャッフルする");
			addMessageShow("[フルハック]Step.3 Step.2を3つのガレージで行う");
			addMessageShow("[フルハック]Step.4 セッションを変更する(ランクが変更される)");
			addMessageShow("[フルハック]Step.5 オフラインへ行く (完了)");
			MsgTimer = GAMEPLAY::GET_GAME_TIMER() + 8000;
			FullHack = false;
		}

	}

	if (_1000KLoop && (_1000KLoop_time == 0))
	{
		NETWORKCASH::NETWORK_EARN_FROM_ROCKSTAR(10000000);
		_1000KLoop_time = 2;
	}
	else if (_1000KLoop_time > 0)
	{
		_1000KLoop_time--;
	}
#pragma endregion

#pragma region Misc
	if (DeleteParachute)
	{
		WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"));
	}

	if (View_FPS)
	{

		snprintf(bufFPS, 50, "%s%i ~w~FPS", fps >= 17 ? "~g~" : "~r~", fps);
		if (!msgindexflag)
		{
			
			drawText(bufFPS, 0, /*X*/Draw_Fps_X, /*Y*/msgYcoord + 0.18f, 0.35f, 0.35f, 255, 255, 255, 255, false, false);
		}
		else
		{
			drawText(bufFPS, 0, /*X*/Draw_Fps_X, /*Y*/msgYcoord - 0.12, 0.35f, 0.35f, 255, 255, 255, 255, false, false);
		}
	}

	if (View_Session)
	{
		if (cstrcmp(PLAYER::GET_PLAYER_NAME(NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0)), "**Invalid**"))
			HostN = "~r~シングルプレイヤー";
		else
			HostN = PLAYER::GET_PLAYER_NAME(NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0));

		char *HostN2 = PS3::ReadString_1(0x400236B8);
		if (GAMEPLAY::IS_STRING_NULL_OR_EMPTY(HostN2))
			HostN2 = "~r~シングルプレイヤー";
		int nums = 16 - NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
		snprintf(SessionHST, 100, "セッションホスト : ~r~%s", HostN2);
		snprintf(SessionBuf, 100, "スクリプトホスト : ~r~%s", HostN);
		sprintf(SessionNum, "セッションの空き : ~r~%d", nums);

		if (!msgindexflag)
		{
			drawText(SessionHST, 0, msgXcoord, msgYcoord + 0.21f, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
			drawText(SessionBuf, 0, msgXcoord, msgYcoord + 0.24f, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
			drawText(SessionNum, 0, msgXcoord, msgYcoord + 0.27f, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
		}
		else
		{
			drawText(SessionHST, 0, msgXcoord, msgYcoord - 0.090f, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
			drawText(SessionBuf, 0, msgXcoord, msgYcoord - 0.060, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
			drawText(SessionNum, 0, msgXcoord, msgYcoord - 0.030f, 0.35, 0.35, 255, 255, 255, 255, false, false, true);
		}
	}

	if (CServer)
	{
		if (GAMEPLAY::GET_GAME_TIMER() > CServerTimer)
		{
			PS3::WriteUInt32(0x12F2E38, R_NOP);
			CServer = false;
		}
	}

	if (vctalkertimer2 < GAMEPLAY::GET_GAME_TIMER())
	{
		if (VCTalker)
		{
			drawText("VCリスト:", 0, VCTalkerX, 0.000, 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, false, true, false);
			memset(TLK, 0, sizeof(TLK));
			char* Talker;
			for (int i = 0; i < 16; i++)
			{

				if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i))
				{
					vctalkerindex++;
					Talker = PLAYER::GET_PLAYER_NAME(i);
					if (NETWORK::NETWORK_IS_PLAYER_TALKING(i))
					{
						snprintf(TLK, 100, "~b~会話中: ~g~%s", Talker);
					}
					else
					{
						snprintf(TLK, 100, "~r~装着中: ~g~%s", Talker);
					}
					drawText(TLK, 0, VCTalkerX, 0.000 + (vctalkerindex * 0.033), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, false, true, false);

				}
			}
		}

		if (HackerView)
		{
			if (vctalkerindex == 0)
				vctalkerindex = 3;
			drawText("チーターリスト", 0, VCTalkerX, 0.000 + ((vctalkerindex + 2) * 0.033), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, false, true, false);
			for (int i = 0; i < 16; i++)
			{
				if (MenuDetected[i])
				{
					drawText(PLAYER::GET_PLAYER_NAME(i), 0, VCTalkerX, 0.000 + ((vctalkerindex + 3) * 0.033), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, false, true, false);
					vctalkerindex++;
				}
			}
		}
		vctalkertimer2 = GAMEPLAY::GET_GAME_TIMER() + 15;
	}
	vctalkerindex = 0;

	if (LightningLoop)
	{
		if (LightningLoop_Timer == 0)
		{
			GAMEPLAY::_0xDF38165E();
			LightningLoop_Timer = 30;
		}
		else if (LightningLoop_Timer > 0)
		{
			LightningLoop_Timer--;
		}

	}

	if (TimeStopper)
	{
		GAMEPLAY::SET_OVERRIDE_WEATHER("CLEAR");
		GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
	}
#pragma endregion

#pragma region MenuFunc
	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardActive = false;
			switch (keyboardAction)
			{
			case STRING_TO_INT:
				*keyboardIntVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				break;
			case CUSTOM_MESSAGE:
				MessageSend(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				addMessageShow("送信しました！");
				break;
			case CUSTOM_OBJECT:

				Create_Map_string = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				Create_Hash = GAMEPLAY::GET_HASH_KEY(Create_Map_string);
				Create_Map = true;
				addMessageShow("スポーンを開始します");
				break;
			case CUSTOM_NUMBERPLATE:
				int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				if (veh != 0)
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3);
					addMessageShow("変更しました！");
				}
				else
				{	
					addMessageShow("乗車してから実行してください。");
				}
				break;
			case CUSTOM_NAME:
				do_NameChange(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				addMessageShow("変更完了!セッションを移動してください！");
				break;
			case STRING_TO_FLOAT:
				*keybordFloatVar = SYSTEM::TO_FLOAT(StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()));
				break;
			case SEND_CHAT_:
				char buffer[300];
				char buffer_2[300];
				char *buf2 = "";
				int Handle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER2(PLAYER::PLAYER_ID(), &Handle[0], 13);
				memcpy((void*)0x1005FC00, NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]), 30);
				memcpy((void*)0x10056430, GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT(), 100);
				//sprintf(buffer_2, "%s : %s", (char*)0x10056430/*メッセージ*/, (char*)0x1005FC00/*名前*/);	
				sprintf(buffer, "Redirect_REDX.php?CMD=SEND_CHAT&VAR=%s%s&VAR2=%s", (_AdminFlag ? "~b~" : ""), (char*)0x10056430/*メッセージ*/, (char*)0x1005FC00/*名前*/);
				memcpy((void*)0x1005CCD0, buffer, 300);
				sendFlag = true;
				_chat_send = true;
				break;
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
#pragma endregion
	
}

#pragma region Player_List
int GET_PLAYER_STATUS(int player, int stat)
{
	return PS3::Read_Global(1581767 + (player * 306) + stat);
}

bool God_Mode_Check(int player)
{
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player))) {
		if (PS3::ReadInt16(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB4) != 0x3000 && //Godmode
			PS3::ReadByte(GetEntityAddress(PLAYER::GET_PLAYER_PED(player)) + 0xB7) != 0x00 && //Invisible
			!NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player) &&
			!PLAYER::IS_PLAYER_DEAD(player) &&
			!ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(player) &&
			(GET_PLAYER_STATUS(player, 238) == 0) &&
			!ENTITY::IS_ENTITY_IN_WATER(PLAYER::GET_PLAYER_PED(player)))
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
			{
				return true;
			}
		}
	}
}

char *REAL_NAME_RETURN(int index)
{
	int Handle[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER_1(index, &Handle[0], 13);
	return NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
}

char *ReturnMenuID1(int index)
{
	if (PLAYER::IS_PLAYER_PLAYING(index) && NETWORK::NETWORK_IS_PLAYER_CONNECTED(index))
	{
		if (PS3::Read_Global(1581767 + (index * 306) + 205) == 987)
			return "~w~[~p~Phantom ~r~A~w~]";
		else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 986)
			return "~w~[~p~Phantom~w~]";
		else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 914)
			return "~w~[~g~ZEDD~w~]";
		else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 911)
			return "~w~[~g~ZEDD ~r~A~w~]";
		else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 888)
			return "~w~[~y~PLS ~r~A~w~]";
		else if (PS3::Read_Global(1581767 + (index * 306) + 205) == 889)
			return "~w~[~g~PLS~w~]";
		else if (ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::GET_PLAYER_PED(index)) == 4095)
			return "~w~[~r~Paradise~w~]";
		else if (PLAYER::GET_PLAYER_MAX_ARMOUR(index > 100))
			return "~w~[~y~MOD~w~]";
		else if (MenuDetected[index])
			return "~w~[~y~MOD~w~]";
	}
	else
		return "";

	return "";
}

bool IS_THIS_PLAYER_FRIEND(char *name)
{
	if (NETWORK::NETWORK_IS_FRIEND_ONLINE(name))
	{
		return true;
	}
}

bool IS_THIS_PLAYER_NAME_FAKE(int index)
{
	if (!GAMEPLAY::ARE_STRINGS_EQUAL(REAL_NAME_RETURN(index), PLAYER::GET_PLAYER_NAME(index)))
		return true;
}

bool IS_PLAYER_SCRIPT_HOST(int index)
{
	int HostNumber = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
	if (HostNumber == index)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(index))
		{
			return true;
		}
	}
}

bool IS_PLAYER_SESSION_HOST(int index)
{
	if (GAMEPLAY::IS_STRING_NULL_OR_EMPTY(PS3::ReadString_1(0x400236B8)))
	{
		if (GAMEPLAY::ARE_STRINGS_EQUAL(PLAYER::GET_PLAYER_NAME(index), PS3::ReadString_1(0x400236B8)))
		{
			return true;
		}
	}
}
#pragma endregion

#pragma region Memory Bypass
void BypassAddress()
{
	//PS3::WriteUInt32(0x11355C8, 0x2C05022B);
	//PS3::WriteUInt32(0x11B26D8, 0x2C04022B);
	//PS3::WriteUInt32(0x179F70, 0x60000000); //Animal Freeze
	PS3::WriteUInt32(0x3F8B10, 0x60000000);
	PS3::WriteUInt32(0x10508BC, 0x60000000);
	PS3::WriteUInt32(0x408B14, 0x60000000);
	PS3::WriteUInt32(0x10508A0, 0x60000000);
	PS3::WriteUInt32(0xEB92E0, 0x60000000);
	PS3::WriteUInt32(0x4A71C0, 0x60000000);
	//PS3::WriteUInt32(0x3F8B10, 0x60000000); //Object Bypass
	//PS3::WriteUInt32(0x3D3E48, 0x60000000);
	//PS3::WriteUInt32(0x3DD3B0, 0x60000000);
	//PS3::WriteUInt32(0x3DD3C0, 0x60000000);
	//PS3::WriteUInt32(0x3F8B24, 0x60000000);
	//PS3::WriteUInt32(0x404AB4, 0x60000000);
	//PS3::WriteUInt32(0x44E144, 0x60000000);
	//PS3::WriteUInt32(0x3D3EB4, 0x60000000);
	PS3::WriteUInt32(0xAE57B0, 0x60000000);
	//PS3::WriteUInt32(0x4B537C, 0x60000000);
	PS3::WriteUInt32(0x13061B4, 0x60000000);
	//PS3::WriteUInt32(NETWORK_CRC_HASH_CHECK_EVENT, 0x4E800020);
	PS3::WriteUInt32(PICKUP_DESTROYED_EVENT, 0x4E800020);
	PS3::WriteUInt32(UPDATE_PLAYER_SCARS_EVENT, 0x4E800020);
	//PS3::WriteUInt32(NETWORK_CHECK_EXE_SIZE_EVENT, 0x4E800020);
	//PS3::WriteUInt32(NETWORK_CHECK_CODE_CRCS_EVENT, 0x4E800020);
	PS3::WriteUInt32(REPORT_CASH_SPAWN_EVENT, 0x4E800020);
}
#pragma endregion

#pragma region メニューの構成部分 (メソッド)
void SkipLoading()
{
	if (DLC2::_0x517B601B())
	{
		SCRIPT::SHUTDOWN_LOADING_SCREEN();
		SCRIPT::SET_NO_LOADING_SCREEN(1);
	}
}
void drawNotification(char*msg, int timer = 2000)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(timer, 1);
}

void drawMessage(char* msg = "", char *iconGroup = "CHAR_SOCIAL_CLUB", char* iconGroup2 = "CHAR_SOCIAL_CLUB", char *NAME = "Re:Hyper Dx", char* subject = "")
{
	UI::_0x574EE85C("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_SET_NOTIFICATION_MESSAGE(iconGroup, iconGroup2, true, 4, NAME, subject);
	UI::_DRAW_NOTIFICATION(false, true);
}

int getOption()
{
	if (optionPress)
		return currentOption;
	else return 0;
}

void resetVars()
{
	if (instructions)
	{
		rightpressing = false;
		leftpressing = false;
		instructionsSetupThisFrame = false;
		fastInstruction = false;
		squareInstruction = false;
		lrInstruction = false;
		udInstruction = false;
		optionPress = false;
		rightPress = false;
		leftPress = false;
		fastRightPress = false;
		fastLeftPress = false;
		squarePress = false;
		if (submenu == Closed)
		{
			GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&gGlareHandle);
			//GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&gAlienHandle);
		}
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
/*
CELL_EMAIL_BOD  =   "Enter your Eyefind message"
CELL_EMAIL_BODE =   "Message too long. Try again"
CELL_EMAIL_BODF =   "Forbidden message. Try again"
CELL_EMAIL_SOD  =   "Enter your Eyefind subject"
CELL_EMAIL_SODE =   "Subject too long. Try again"
CELL_EMAIL_SODF =   "Forbidden text. Try again"
CELL_EMASH_BOD  =   "Enter your Eyefind message"
CELL_EMASH_BODE =   "Message too long. Try again"
CELL_EMASH_BODF =   "Forbidden message. Try again"
CELL_EMASH_SOD  =   "Enter your Eyefind subject"
CELL_EMASH_SODE =   "Subject too long. Try again"
CELL_EMASH_SODF =   "Forbidden Text. Try again"
FMMC_KEY_TIP10  =   "Enter Synopsis"
FMMC_KEY_TIP12  =   "Enter Custom Team Name"
FMMC_KEY_TIP12F =   "Forbidden Text. Try again"
FMMC_KEY_TIP12N =   "Custom Team Name"
FMMC_KEY_TIP8   =   "Enter Message"
FMMC_KEY_TIP8F  =   "Forbidden Text. Try again"
FMMC_KEY_TIP8FS =   "Invalid Message. Try again"
FMMC_KEY_TIP8S  =   "Enter Message"
FMMC_KEY_TIP9   =   "Enter Outfit Name"
FMMC_KEY_TIP9F  =   "Invalid Outfit Name. Try again"
FMMC_KEY_TIP9N  =   "Outfit Name"
PM_NAME_CHALL   =   "Enter Challenge Name"
*/
void startKeyboard(int action, char *defaultText, int maxLength, int language = 1)
{
	/*
	american = 0
french = 1
german = 2
italian =3
spanish = 4
portuguese = 5
polish = 6
russian = 7
korean = 8
chinese = 9
japanese = 10
mexican = 11
chinese_simplified = 12
	*/
	//UNK::_GET_CURRENT_LANGUAGE_ID
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(language, "PM_NAME_CHALL", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}

void playSound(char* sound, char *soundgroup = "HUD_FRONTEND_DEFAULT_SOUNDSET")
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound, soundgroup);
}
int Button1 = Dpad_Right;
int Button2 = Button_X;
void monitorButtons()
{
	SetupTimer(20);
	
	if (submenu == Closed)
	{
		if (IsTimerReady())
		{
			if (isPress(Dpad_Right) && isPress(Button_X))
			{
				submenu = Main_Menu;
				submenuLevel = 0;
				currentOption = 1;
				playSound("YES");
				//drawMessage("\nVersion 1.0");
			}
			ResetTimer();
		}
	}
	else {
		ButtonDisable(Button_B);
		if (IsTimerReady())
		{
			if (isPressed(Button_B))
			{
				if (submenu == Main_Menu)
				{
					submenu = Closed;
				}
				else
				{
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				playSound("Back");
			}
			else if (isPressed(Button_A))
			{
				optionPress = true;
				playSound("SELECT");
			}
			else if (isPressed(Dpad_Up))
			{
				currentOption = currentOption - 1;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (isPressed(Dpad_Down))
			{
				currentOption = currentOption + 1;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				playSound("NAV_UP_DOWN");

			}
			else if (isPress(Dpad_Up))
			{
				if (GAMEPLAY::GET_GAME_TIMER() > DdownTimerCount)
				{
					hasBeenUsed = true;
					controlJustPressedTimeout++;
					if (controlJustPressedTimeout > 3)
					{
						currentOption = currentOption - 1;
						if (currentOption < 1)
						{
							currentOption = optionCount;
						}
						playSound("NAV_UP_DOWN");
						DdownTimerCount = GAMEPLAY::GET_GAME_TIMER() + ScrollTimer;
					}
				}
			}
			else if (isPress(Dpad_Down))
			{
				if (GAMEPLAY::GET_GAME_TIMER() > DdownTimerCount)
				{
					hasBeenUsed = true;
					controlJustPressedTimeout++;
					if (controlJustPressedTimeout > 3)
					{
						currentOption = currentOption + 1;
						if (currentOption > optionCount)
						{
							currentOption = 1;
						}
						playSound("NAV_UP_DOWN");
						DdownTimerCount = GAMEPLAY::GET_GAME_TIMER() + ScrollTimer;
					}
				}
			}
			else if (isPressed(Dpad_Right))
			{
				rightPress = true;
			}
			else if (isPressed(Dpad_Left))
			{
				leftPress = true;
			}
			else if (isPress(Dpad_Right))
			{
				fastRightPress = true;
			}
			else if (isPress(Dpad_Left))
			{
				fastLeftPress = true;
			}
			else if (rightPress || (isPress(Dpad_Right) && isPress(Button_L1)))
			{
				rightpressing = true;
			}
			else if (leftPress || (isPress(Dpad_Left)) && isPress(Button_L1))
			{
				leftpressing = true;
			}
			else if (isPressed(Button_X))
			{
				squarePress = true;
			}
			ResetTimer();
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

#pragma region All Entity

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
	Vector3 handleCoords = ENTITY::GET_ENTITY_COORDS(ent, 1);
	UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &ScreenX, &ScreenY);
	snprintf(text, 200, "%X", ENTITY::GET_ENTITY_MODEL(ent));
	drawText(text, 0, ScreenX, ScreenY, 0.4f, 0.4f, 255, 0, 0, 255, true, false);
}


int linesAddressPool[3] = { 255, 255, 255 };

#pragma endregion

#pragma region ファイル読み込み
/*void loadStringsFile(const char* strings)
{
	int fd, ret, LineNumber; uint64_t unk; char ReadBuffer[35000], line[35000];
	ret = cellFsOpen(strings, 0, &fd, NULL, 0);
	if (!ret) {
		cellFsRead(fd, ReadBuffer, 35000, &unk);
		cellFsClose(fd);
		for (int i = 0; i < 35000; i++) {
			if (ReadBuffer[i] == NULL) break;
			if (ReadBuffer[i] != '\n') {
				strcpy
			}
		}
		delete[] ReadBuffer;
		delete[] line;
	}
}*/

#pragma endregion

#pragma region テキスト変更
void SetLabelText(char* a_cLabelName, char* a_cTextToWrite) {
	PS3::WriteString2(GetLabelTextByGXT(a_cLabelName), a_cTextToWrite);
}

void SetOthersLabelText(char* a_cLabelName, char* a_cTextToWrite) {
	char* checkLen = (char*)(GetLabelTextByGXT(a_cLabelName));
	int lenOriginal = std::strlen(checkLen);
	printf("[DEBUG] length of %s label is %i\n", a_cLabelName, lenOriginal);
	int lenOfText = std::strlen(a_cTextToWrite);
	if (lenOfText > (lenOriginal + 0x1)) {
		printf("[ERROR] the length of text to write is too big!\n");
	}
	else {
		PS3::WriteString2(GetLabelTextByGXT(a_cLabelName), a_cTextToWrite);
	}
}
#pragma endregion

#pragma region Misc
char *raderjapanese[] = { "黒","赤","黄色","水色","青","ピンク","白", "透明", "真っ黒", "普通" };
char radercolor1[] = { 0x40, 0x14, 0x16, 0x19, 0x17, 0x18, 0x01, 0xFC, 0xF5, 0x80 };
int RaderIndex;
char bytesForResetWater[0x5994];
void DeleteWaterChecker()
{
	if (!checkeWater)
	{
		for (unsigned int i = 0; i < 0x5994; i++)
			bytesForResetWater[i] = *(char*)(*(unsigned int*)0x21C8C48 + i);
		checkeWater = true;
	}
}

void LoadIPL(bool toggle)
{
	if (toggle)
	{
		STREAMING::REQUEST_IPL("airfield");
		STREAMING::REQUEST_IPL("AP1_04_TriAf01");
		STREAMING::REQUEST_IPL("bh1_16_refurb");
		STREAMING::REQUEST_IPL("BH1_47_JoshHse_Burnt");
		STREAMING::REMOVE_IPL("BH1_47_JoshHse_UnBurnt");

		STREAMING::REQUEST_IPL("bnkheist_apt_dest");
		STREAMING::REMOVE_IPL("bnkheist_apt_norm");
		STREAMING::REQUEST_IPL("burgershot_yoga");
		STREAMING::REQUEST_IPL("burnt_switch_off");
		STREAMING::REQUEST_IPL("cargoship");

		STREAMING::REMOVE_IPL("canyonriver01");//train
		STREAMING::REMOVE_IPL("railing_start");
		STREAMING::REQUEST_IPL("canyonriver01_traincrash");
		STREAMING::REQUEST_IPL("railing_end");

		STREAMING::REQUEST_IPL("chemgrill_grp1");
		STREAMING::REQUEST_IPL("CH1_07_TriAf03");
		STREAMING::REQUEST_IPL("CH3_RD2_BishopsChickenGraffiti");

		//STREAMING::REQUEST_IPL("");
		STREAMING::REQUEST_IPL("chop_props");
		STREAMING::REQUEST_IPL("chophillskennel");
		STREAMING::REQUEST_IPL("CJ_IOABoat");
		STREAMING::REQUEST_IPL("coronertrash");
		STREAMING::REQUEST_IPL("Coroner_Int_on");
		STREAMING::REMOVE_IPL("Coroner_Int_off");
		STREAMING::REQUEST_IPL("crashed_cargoplane");
		STREAMING::REQUEST_IPL("CS1_02_cf_offmission");
		STREAMING::REQUEST_IPL("CS1_02_cf_onmission1");
		STREAMING::REQUEST_IPL("CS1_02_cf_onmission2");
		STREAMING::REQUEST_IPL("CS1_02_cf_onmission3");
		STREAMING::REQUEST_IPL("CS1_02_cf_onmission4 ");

		STREAMING::REQUEST_IPL("CS2_06_TriAf02");
		STREAMING::REQUEST_IPL("CS3_05_water_grp1");
		STREAMING::REQUEST_IPL("CS3_05_water_grp2 ");
		STREAMING::REQUEST_IPL("cs3_07_mpgates ");
		STREAMING::REQUEST_IPL("CS4_08_TriAf02");
		STREAMING::REQUEST_IPL("CS4_04_TriAf03");
		STREAMING::REQUEST_IPL("CS5_04_MazeBillboardGraffiti");
		STREAMING::REQUEST_IPL("cs5_4_trains");
		STREAMING::REQUEST_IPL("CS5_Roads_RonOilGraffiti");

		STREAMING::REQUEST_IPL("des_farmhouse");
		STREAMING::REQUEST_IPL("des_farmhs_endimap");
		STREAMING::REQUEST_IPL("des_farmhs_end_occl");

		STREAMING::REMOVE_IPL("des_farmhs_startimap");
		STREAMING::REMOVE_IPL("des_farmhs_start_occl");

		STREAMING::REQUEST_IPL("DES_ProTree_start");
		STREAMING::REQUEST_IPL("DES_ProTree_start_lod");

		STREAMING::REQUEST_IPL("DES_Smash2_startimap ");
		STREAMING::REQUEST_IPL("DES_StiltHouse_imapstart");
		STREAMING::REMOVE_IPL("DES_Smash2_endimap ");
		STREAMING::REMOVE_IPL("DES_StiltHouse_imapend");
		STREAMING::REMOVE_IPL("des_stilthouse_rebuild ");

		STREAMING::REQUEST_IPL("DT1_05_HC_REQ");
		STREAMING::REMOVE_IPL("DT1_05_HC_REMOVE");
		STREAMING::REQUEST_IPL("DT1_05_REQUEST");
		STREAMING::REQUEST_IPL("DT1_05_rubble");
		STREAMING::REMOVE_IPL("DT1_17_NewBill");
		STREAMING::REQUEST_IPL("DT1_17_OldBill");
		STREAMING::REQUEST_IPL("DT1_21_prop_lift_on");
		STREAMING::REQUEST_IPL("fakeint");

		STREAMING::REMOVE_IPL("farm");
		STREAMING::REQUEST_IPL("farm_burnt");
		STREAMING::REQUEST_IPL("farm_burnt_props ");

		STREAMING::REQUEST_IPL("farmint_cap");
		STREAMING::REQUEST_IPL("farmint");
		STREAMING::REQUEST_IPL("farm_props");

		STREAMING::REQUEST_IPL("FBI_colPLUG");
		STREAMING::REQUEST_IPL("FIBlobby");
		STREAMING::REMOVE_IPL("FIBlobbyfake");
		STREAMING::REMOVE_IPL("FBI_repair");
		STREAMING::REQUEST_IPL("ferris_finale_Anim");
		STREAMING::REQUEST_IPL("FruitBB");
		STREAMING::REQUEST_IPL("gasparticle_grp2");
		STREAMING::REQUEST_IPL("gasstation_ipl_group1");
		STREAMING::REQUEST_IPL("gasstation_ipl_group2");

		STREAMING::REQUEST_IPL("hei_carrier");
		STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
		STREAMING::REQUEST_IPL("hei_Carrier_int1");
		STREAMING::REQUEST_IPL("hei_Carrier_int2");
		STREAMING::REQUEST_IPL("hei_Carrier_int3");
		STREAMING::REQUEST_IPL("hei_Carrier_int4");
		STREAMING::REQUEST_IPL("hei_Carrier_int5");
		STREAMING::REQUEST_IPL("hei_Carrier_int6");
		STREAMING::REQUEST_IPL("hei_carrier_LODLights");

		STREAMING::REQUEST_IPL("hei_yacht_heist");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");

		STREAMING::REMOVE_IPL("id2_14_during_door");
		STREAMING::REMOVE_IPL("id2_14_during1");
		STREAMING::REMOVE_IPL("id2_14_during2");
		STREAMING::REQUEST_IPL("id2_14_on_fire");
		STREAMING::REMOVE_IPL("id2_14_post_no_int");
		STREAMING::REMOVE_IPL("id2_14_pre_no_int");

		STREAMING::REQUEST_IPL("ID2_21_G_Night");
		STREAMING::REQUEST_IPL("Jetsteal_ipl_grp1");
		STREAMING::REQUEST_IPL("Jetsteal_ipl_grp2");
		STREAMING::REQUEST_IPL("jetstealtunnel");
		STREAMING::REQUEST_IPL("jewel2fake");
		STREAMING::REQUEST_IPL("Jewel_Gasmasks");
		STREAMING::REQUEST_IPL("layer_sextoys_a");
		STREAMING::REQUEST_IPL("layer_torture");
		STREAMING::REQUEST_IPL("ld_rail_02_track");

		STREAMING::REQUEST_IPL("MG-Flight School 5");
		STREAMING::REQUEST_IPL("Michael_premier");
		STREAMING::REQUEST_IPL("occl_meth_grp1");
		STREAMING::REQUEST_IPL("Plane_crash_trench");
		STREAMING::REQUEST_IPL("post_hiest_unload");

		STREAMING::REQUEST_IPL("prologue01"); //North Yankton
		STREAMING::REQUEST_IPL("prologue01c");
		STREAMING::REQUEST_IPL("prologue01d");
		STREAMING::REQUEST_IPL("prologue01e");
		STREAMING::REQUEST_IPL("prologue01f");
		STREAMING::REQUEST_IPL("prologue01g");
		STREAMING::REQUEST_IPL("prologue01h");
		STREAMING::REQUEST_IPL("prologue01i");
		STREAMING::REQUEST_IPL("prologue01j");
		STREAMING::REQUEST_IPL("prologue01k");
		STREAMING::REQUEST_IPL("prologue01z");
		STREAMING::REQUEST_IPL("prologue02");
		STREAMING::REQUEST_IPL("prologue03");
		STREAMING::REQUEST_IPL("prologue03b");
		STREAMING::REQUEST_IPL("prologue03_grv_fun");
		STREAMING::REQUEST_IPL("prologue04");
		STREAMING::REQUEST_IPL("prologue04b");
		STREAMING::REQUEST_IPL("prologue05");
		STREAMING::REQUEST_IPL("prologue05b");
		STREAMING::REQUEST_IPL("prologue06");
		STREAMING::REQUEST_IPL("prologue06b");
		STREAMING::REQUEST_IPL("prologue06_int");
		STREAMING::REQUEST_IPL("prologuerd");
		STREAMING::REQUEST_IPL("prologuerdb");
		STREAMING::REQUEST_IPL("prologue_DistantLights");
		STREAMING::REQUEST_IPL("prologue_LODLights");
		STREAMING::REQUEST_IPL("prologue_m2_door");
		STREAMING::REQUEST_IPL("facelobby");

		STREAMING::REQUEST_IPL("prop_cheetah_covered");
		STREAMING::REQUEST_IPL("prop_entityXF_covered");
		STREAMING::REQUEST_IPL("prop_jb700_covered");
		STREAMING::REQUEST_IPL("prop_ztype_covered");

		STREAMING::REMOVE_IPL("RC12B_Default");
		STREAMING::REQUEST_IPL("RC12B_Destroyed");
		STREAMING::REMOVE_IPL("RC12B_Fixed");
		STREAMING::REMOVE_IPL("RC12B_HospitalInterior");

		//STREAMING::REQUEST_IPL("REMOVE_ALL_STATES");
		STREAMING::REQUEST_IPL("refit_unload");
		STREAMING::REMOVE_IPL("SC1_01_NewBill");
		STREAMING::REQUEST_IPL("SC1_01_OldBill");
		STREAMING::REQUEST_IPL("SC1_30_Keep_Closed");

		STREAMING::REQUEST_IPL("ship_occ_grp1");
		STREAMING::REQUEST_IPL("ship_occ_grp2");
		STREAMING::REQUEST_IPL("shr_int");
		STREAMING::REQUEST_IPL("smboat");
		STREAMING::REQUEST_IPL("SM_15_BldGRAF1");
		STREAMING::REQUEST_IPL("sunkcargoship");
		STREAMING::REQUEST_IPL("tankerexp_grp0");
		STREAMING::REQUEST_IPL("tankerexp_grp1");
		STREAMING::REQUEST_IPL("tankerexp_grp2");
		STREAMING::REQUEST_IPL("tankerexp_grp3");
		STREAMING::REQUEST_IPL("TrevorsMP");
		STREAMING::REQUEST_IPL("TrevorsTrailer");
		STREAMING::REQUEST_IPL("TrevorsTrailerTidy");
		STREAMING::REQUEST_IPL("TrevorsTrailerTrash");
		STREAMING::REQUEST_IPL("triathlon2_VBprops");

		STREAMING::REQUEST_IPL("TRV1_Trail_Finish");
		STREAMING::REMOVE_IPL("TRV1_Trail_end");
		STREAMING::REMOVE_IPL("TRV1_Trail_start");

		STREAMING::REQUEST_IPL("UFO");
		STREAMING::REQUEST_IPL("V_35_Fireman");
		STREAMING::REQUEST_IPL("VB_08_TriAf01");

		STREAMING::REQUEST_IPL("v_carshowroom");
		STREAMING::REQUEST_IPL("shutter_open");
		STREAMING::REMOVE_IPL("shutter_closed");
		STREAMING::REQUEST_IPL("shr_int");
		STREAMING::REQUEST_IPL("csr_inMission");
		STREAMING::REQUEST_IPL("fakeint");

		STREAMING::REQUEST_IPL("V_Michael_Garage");
		STREAMING::REQUEST_IPL("V_Michael_FameShame");
		STREAMING::REQUEST_IPL("V_Michael_JewelHeist");
		STREAMING::REQUEST_IPL("V_Michael_plane_ticket");
		STREAMING::REQUEST_IPL("V_Michael_Scuba");
		STREAMING::REQUEST_IPL("v_tunnel_hole");
		STREAMING::REQUEST_IPL("v_tunnel_hole_swap");
		STREAMING::REQUEST_IPL("yogagame");
		STREAMING::REQUEST_IPL("FINBANK");
		STREAMING::REQUEST_IPL("DT1_03_Shutter");
		STREAMING::REQUEST_IPL("DT1_03_Gr_Closed");
		STREAMING::REQUEST_IPL("DES_tankercrash");

		addMessageShow("~g~IPLをロードしました。");

	}
	else
	{
		STREAMING::REMOVE_IPL("airfield");
		STREAMING::REMOVE_IPL("AP1_04_TriAf01");
		STREAMING::REMOVE_IPL("bh1_16_refurb");
		STREAMING::REMOVE_IPL("BH1_47_JoshHse_Burnt");
		STREAMING::REQUEST_IPL("BH1_47_JoshHse_UnBurnt");
		STREAMING::REMOVE_IPL("bnkheist_apt_dest");
		STREAMING::REQUEST_IPL("bnkheist_apt_norm");
		STREAMING::REMOVE_IPL("burgershot_yoga");
		STREAMING::REMOVE_IPL("burnt_switch_off");
		STREAMING::REMOVE_IPL("cargoship");
		STREAMING::REQUEST_IPL("canyonriver01");//train
		STREAMING::REQUEST_IPL("railing_start");
		STREAMING::REMOVE_IPL("canyonriver01_traincrash");
		STREAMING::REMOVE_IPL("railing_end");
		STREAMING::REMOVE_IPL("chemgrill_grp1");
		STREAMING::REMOVE_IPL("CH1_07_TriAf03");
		STREAMING::REMOVE_IPL("CH3_RD2_BishopsChickenGraffiti");
		//STREAMING::REMOVE_IPL("");
		STREAMING::REMOVE_IPL("chop_props");
		STREAMING::REMOVE_IPL("chophillskennel");
		STREAMING::REQUEST_IPL("Coroner_Int_off");
		STREAMING::REMOVE_IPL("Coroner_Int_on");
		STREAMING::REMOVE_IPL("coronertrash");
		STREAMING::REMOVE_IPL("crashed_cargoplane");
		STREAMING::REMOVE_IPL("CS1_02_cf_offmission");
		STREAMING::REMOVE_IPL("CS1_02_cf_onmission1");
		STREAMING::REMOVE_IPL("CS1_02_cf_onmission2");
		STREAMING::REMOVE_IPL("CS1_02_cf_onmission3");
		STREAMING::REMOVE_IPL("CS1_02_cf_onmission4");
		STREAMING::REMOVE_IPL("CJ_IOABoat");
		STREAMING::REMOVE_IPL("CS2_06_TriAf02");
		STREAMING::REMOVE_IPL("CS3_05_water_grp1");
		STREAMING::REMOVE_IPL("CS3_05_water_grp2");
		STREAMING::REMOVE_IPL("cs3_07_mpgates");
		STREAMING::REMOVE_IPL("CS4_08_TriAf02");
		STREAMING::REMOVE_IPL("CS4_04_TriAf03");
		STREAMING::REMOVE_IPL("CS5_04_MazeBillboardGraffiti");
		STREAMING::REMOVE_IPL("cs5_4_trains");
		STREAMING::REMOVE_IPL("CS5_Roads_RonOilGraffiti");
		STREAMING::REMOVE_IPL("des_farmhouse");
		STREAMING::REQUEST_IPL("des_farmhs_startimap");
		STREAMING::REQUEST_IPL("des_farmhs_startimap");
		STREAMING::REMOVE_IPL("des_farmhs_endimap");
		STREAMING::REMOVE_IPL("des_farmhs_end_occl");
		STREAMING::REMOVE_IPL("DES_Smash2_startimap ");
		STREAMING::REMOVE_IPL("DES_StiltHouse_imapstart");
		STREAMING::REQUEST_IPL("DES_Smash2_endimap ");
		STREAMING::REQUEST_IPL("DES_StiltHouse_imapend");
		STREAMING::REQUEST_IPL("des_stilthouse_rebuild ");
		STREAMING::REMOVE_IPL("DT1_05_HC_REQ");
		STREAMING::REQUEST_IPL("DT1_05_HC_REMOVE");
		STREAMING::REMOVE_IPL("DT1_05_REQUEST");
		STREAMING::REMOVE_IPL("DT1_05_rubble");
		STREAMING::REQUEST_IPL("DT1_17_NewBill");
		STREAMING::REMOVE_IPL("DT1_17_OldBill");
		STREAMING::REMOVE_IPL("DT1_21_prop_lift_on");
		STREAMING::REMOVE_IPL("fakeint");
		STREAMING::REQUEST_IPL("farm");
		STREAMING::REMOVE_IPL("farm_burnt");
		STREAMING::REMOVE_IPL("farm_burnt_props ");
		STREAMING::REMOVE_IPL("farmint_cap");
		STREAMING::REMOVE_IPL("farmint");
		STREAMING::REMOVE_IPL("farm_props");
		STREAMING::REMOVE_IPL("FBI_colPLUG");
		STREAMING::REMOVE_IPL("FIBlobby");
		STREAMING::REQUEST_IPL("FIBlobbyfake");
		STREAMING::REQUEST_IPL("FBI_repair");
		STREAMING::REMOVE_IPL("ferris_finale_Anim");
		STREAMING::REMOVE_IPL("FruitBB");
		STREAMING::REMOVE_IPL("gasparticle_grp2");
		STREAMING::REMOVE_IPL("gasstation_ipl_group1");
		STREAMING::REMOVE_IPL("gasstation_ipl_group2");
		STREAMING::REMOVE_IPL("hei_carrier");
		STREAMING::REMOVE_IPL("hei_carrier_DistantLights");
		STREAMING::REMOVE_IPL("hei_Carrier_int1");
		STREAMING::REMOVE_IPL("hei_Carrier_int2");
		STREAMING::REMOVE_IPL("hei_Carrier_int3");
		STREAMING::REMOVE_IPL("hei_Carrier_int4");
		STREAMING::REMOVE_IPL("hei_Carrier_int5");
		STREAMING::REMOVE_IPL("hei_Carrier_int6");
		STREAMING::REMOVE_IPL("hei_carrier_LODLights");
		STREAMING::REMOVE_IPL("hei_yacht_heist");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bar");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bridge");
		STREAMING::REMOVE_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REMOVE_IPL("hei_yacht_heist_enginrm");
		STREAMING::REMOVE_IPL("hei_yacht_heist_LODLights");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Lounge");
		STREAMING::REQUEST_IPL("id2_14_during_door");
		STREAMING::REQUEST_IPL("id2_14_during1");
		STREAMING::REQUEST_IPL("id2_14_during2");
		STREAMING::REMOVE_IPL("id2_14_on_fire");
		STREAMING::REQUEST_IPL("id2_14_post_no_int");
		STREAMING::REQUEST_IPL("id2_14_pre_no_int");
		STREAMING::REMOVE_IPL("ID2_21_G_Night");
		STREAMING::REMOVE_IPL("Jetsteal_ipl_grp1");
		STREAMING::REMOVE_IPL("Jetsteal_ipl_grp2");
		STREAMING::REMOVE_IPL("jetstealtunnel");
		STREAMING::REMOVE_IPL("jewel2fake");
		STREAMING::REMOVE_IPL("Jewel_Gasmasks");
		STREAMING::REMOVE_IPL("layer_sextoys_a");
		STREAMING::REMOVE_IPL("layer_torture");
		STREAMING::REMOVE_IPL("ld_rail_02_track");
		STREAMING::REMOVE_IPL("MG-Flight School 5");
		STREAMING::REMOVE_IPL("Michael_premier");
		STREAMING::REMOVE_IPL("occl_meth_grp1");
		STREAMING::REMOVE_IPL("Plane_crash_trench");
		STREAMING::REMOVE_IPL("post_hiest_unload");
		STREAMING::REMOVE_IPL("prologue01"); //North Yankton
		STREAMING::REMOVE_IPL("prologue01c");
		STREAMING::REMOVE_IPL("prologue01d");
		STREAMING::REMOVE_IPL("prologue01e");
		STREAMING::REMOVE_IPL("prologue01f");
		STREAMING::REMOVE_IPL("prologue01g");
		STREAMING::REMOVE_IPL("prologue01h");
		STREAMING::REMOVE_IPL("prologue01i");
		STREAMING::REMOVE_IPL("prologue01j");
		STREAMING::REMOVE_IPL("prologue01k");
		STREAMING::REMOVE_IPL("prologue01z");
		STREAMING::REMOVE_IPL("prologue02");
		STREAMING::REMOVE_IPL("prologue03");
		STREAMING::REMOVE_IPL("prologue03b");
		STREAMING::REMOVE_IPL("prologue03_grv_fun");
		STREAMING::REMOVE_IPL("prologue04");
		STREAMING::REMOVE_IPL("prologue04b");
		STREAMING::REMOVE_IPL("prologue05");
		STREAMING::REMOVE_IPL("prologue05b");
		STREAMING::REMOVE_IPL("prologue06");
		STREAMING::REMOVE_IPL("prologue06b");
		STREAMING::REMOVE_IPL("prologue06_int");
		STREAMING::REMOVE_IPL("prologuerd");
		STREAMING::REMOVE_IPL("prologuerdb");
		STREAMING::REMOVE_IPL("prologue_DistantLights");
		STREAMING::REMOVE_IPL("prologue_LODLights");
		STREAMING::REMOVE_IPL("prologue_m2_door");
		STREAMING::REMOVE_IPL("facelobby");
		STREAMING::REQUEST_IPL("RC12B_Default");
		STREAMING::REMOVE_IPL("RC12B_Destroyed");
		STREAMING::REMOVE_IPL("RC12B_Fixed");
		STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
		STREAMING::REMOVE_IPL("refit_unload");
		STREAMING::REQUEST_IPL("SC1_01_NewBill");
		STREAMING::REMOVE_IPL("SC1_01_OldBill");
		STREAMING::REMOVE_IPL("SC1_30_Keep_Closed");
		STREAMING::REMOVE_IPL("ship_occ_grp1");
		STREAMING::REMOVE_IPL("ship_occ_grp2");
		STREAMING::REMOVE_IPL("shr_int");
		STREAMING::REMOVE_IPL("smboat");
		STREAMING::REMOVE_IPL("SM_15_BldGRAF1");
		STREAMING::REMOVE_IPL("sunkcargoship");
		STREAMING::REMOVE_IPL("tankerexp_grp0");
		STREAMING::REMOVE_IPL("tankerexp_grp1");
		STREAMING::REMOVE_IPL("tankerexp_grp2");
		STREAMING::REMOVE_IPL("tankerexp_grp3");
		STREAMING::REMOVE_IPL("TrevorsMP");
		STREAMING::REMOVE_IPL("TrevorsTrailer");
		STREAMING::REMOVE_IPL("TrevorsTrailerTidy");
		STREAMING::REMOVE_IPL("TrevorsTrailerTrash");
		STREAMING::REMOVE_IPL("triathlon2_VBprops");
		STREAMING::REMOVE_IPL("TRV1_Trail_Finish");
		STREAMING::REMOVE_IPL("TRV1_Trail_end");
		STREAMING::REQUEST_IPL("TRV1_Trail_start");
		STREAMING::REMOVE_IPL("v_carshowroom");
		STREAMING::REMOVE_IPL("shutter_open");
		STREAMING::REQUEST_IPL("shutter_closed");
		STREAMING::REMOVE_IPL("shr_int");
		STREAMING::REMOVE_IPL("csr_inMission");
		STREAMING::REMOVE_IPL("fakeint");
		STREAMING::REMOVE_IPL("V_Michael_Garage");
		STREAMING::REMOVE_IPL("V_Michael_FameShame");
		STREAMING::REMOVE_IPL("V_Michael_JewelHeist");
		STREAMING::REMOVE_IPL("V_Michael_plane_ticket");
		STREAMING::REMOVE_IPL("V_Michael_Scuba");
		STREAMING::REMOVE_IPL("v_tunnel_hole");
		STREAMING::REMOVE_IPL("v_tunnel_hole_swap");
		STREAMING::REMOVE_IPL("yogagame");
		STREAMING::REMOVE_IPL("FINBANK");
		STREAMING::REMOVE_IPL("DT1_03_Shutter");
		STREAMING::REMOVE_IPL("DT1_03_Gr_Closed");
		STREAMING::REMOVE_IPL("DES_tankercrash");
		addMessageShow("~r~IPLを破棄しました。");
	}
}
#pragma endregion

#pragma region ini file
void GetSettings()
{
	int fd;
	uint64_t unk;

	char ReadBuffer[1024] = { 0 };
	char ReadBuffer2[1024] = { 0 };
	char* locationToWrite = "/dev_hdd0/tmp/Re_HyperDx/ProtectionSettings.ini";
	if (cellFsOpen(locationToWrite, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
		return;
	cellFsRead(fd, ReadBuffer, 5000, &unk);
	cellFsClose(fd);

	strcpy(ReadBuffer2, ReadBuffer);
	bool str = strstr(ReadBuffer2, "1");
	
	if (str)
		printf("すぺくたーうんこ");
	/*int LineNumber = 0;
	char line[5000];
	for (int i = 0; i < 5000; i++)
	{
		if (ReadBuffer[i] == NULL)
			break;

		if (ReadBuffer[i] == '\n')
		{
			LineNumber++;
			switch (LineNumber)
			{
			case 1:
				SelectColour.R = _atoi(line);
				break;
			case 2:
				SelectColour.G = _atoi(line);
				break;
			case 3:
				SelectColour.B = _atoi(line);
				break;
			case 4:
				Menu_X = _atoi(line);
				break;
			case 5:
				if (CompareStrings(line, "0"))
					ChangeOptionChecked("Settings", "Clear Reports On Open", false);
				break;
			case 6:
				if (CompareStrings(line, "1"))
					ChangeOptionChecked("Settings", "Draw Line To Selected Player", true);
				break;
			case 7:
				if (CompareStrings(line, "1"))
					ChangeOptionChecked("Settings", "Clone Protection", true);
				break;
			case 8:
				if (CompareStrings(line, "1"))
					ChangeOptionChecked("Settings", "Prop Attach Protection", true);
				break;
			case 9:
				if (CompareStrings(line, "1"))
					ChangeOptionChecked("Settings", "Vehicle Attach Protection", true);
				break;
			case 10:
				if (CompareStrings(line, "1"))
				{
					ChangeOptionChecked("Settings", "PSN Name Spoofer", true);
					PSNSpoof = true;
				}
				break;
			}

			memset(line, 0, 5000);
		}
		else
			sprintf(line, "%s%c", line, ReadBuffer[i]);
	}

	if (SelectColour.R == 123 && SelectColour.G == 255 && SelectColour.B == 0)
		ChangeOptionRadioChecked("Settings", "Green");
	else if (SelectColour.R == 159 && SelectColour.G == 19 && SelectColour.B == 214)
		ChangeOptionRadioChecked("Settings", "Purple");
	else if (SelectColour.R == 19 && SelectColour.G == 123 && SelectColour.B == 214)
		ChangeOptionRadioChecked("Settings", "Blue");
	else if (SelectColour.R == 214 && SelectColour.G == 19 && SelectColour.B == 100)
		ChangeOptionRadioChecked("Settings", "Pink");
	else if (SelectColour.R == 214 && SelectColour.G == 19 && SelectColour.B == 19)
		ChangeOptionRadioChecked("Settings", "Red");
	else if (SelectColour.R == 214 && SelectColour.G == 117 && SelectColour.B == 19)
		ChangeOptionRadioChecked("Settings", "Orange");
	else if (SelectColour.R == 228 && SelectColour.G == 250 && SelectColour.B == 32)
		ChangeOptionRadioChecked("Settings", "Yellow");
	else
		ChangeOptionRadioChecked("Settings", "Custom RGB");*/
}
#pragma endregion

#pragma region 文字列読み込み
bool isNullorEmpty(char *string)
{
	int _length = strlen(string);
	bool _bool = false;
	for (int i = 0; i < _length; i++)
	{
		if (string[i] == '\0' || string[i] == NULL)
			return true;
		else
			return false;
	}
}

char *TestString[1000];
void Load_String()
{
	char* locationToRead = "/dev_hdd0/tmp/Re_HyperDx/StringTest.txt";
	int Add = 0x102F0100;
	uint64_t pos;
	int fd;
	uint64_t unk;


	int size = fileSize(locationToRead);
	char ReadBuffer[size];
	if (cellFsOpen(locationToRead, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
		return;
	else
		printf("Loaded String.txt\n");

	if (size != -1)
		printf("Loaded Size : %ibyte\n", size);
	else
		printf("Size Load Error\n");

	cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
	CellFsErrno Error = cellFsRead(fd, ReadBuffer, size, &unk);

	if (Error == CELL_FS_SUCCEEDED)
		printf("Readed String.txt\n");
	else
		printf("Read Error String.txt\n");

	cellFsClose(fd);
	
	printf(ReadBuffer);
	printf("\n");


	//char *compress;
	//compress = strstr(ReadBuffer, NULL);

	int LineNumber;
	char LoadedLine[400];
	strcpy(LoadedLine, "");
	char ReadBufferConverter[1];
	int index;

	bool through;

	while(true)
	{
		if (ReadBuffer[index] == '^' || index == size)
		{
			//if (isNullorEmpty(LoadedLine))
			//{
				break;
			//}
			//else
			//{
			//	PS3::WriteString(0x10054300, LoadedLine);
			//	TestString[LineNumber] = PS3::ReadString_1(0x10054300);
			//	printf("%s\n", LoadedLine);
			//	printf("%i\n", LineNumber);
			//	//LineNumber++;
			//	PS3::WriteByte(0x10054320, '\0');
			//	strcpy(LoadedLine, "");
			//	break;
			//}
		}

		if (ReadBuffer[index] == '/' && ReadBuffer[index + 1] == '/')
		{
			index + 1;
			through = true;
		}

		switch (ReadBuffer[index])
		{
		/*case '/': break;*/

		case '\n':
			if (!through)
			{
				PS3::WriteString(0x10054300, LoadedLine);
				TestString[LineNumber] = PS3::ReadString_1(0x10054300);
				printf("%s\n", LoadedLine);
				printf("%i\n", LineNumber);
				LineNumber++;
				PS3::WriteByte(0x10054320, '\0');
				strcpy(LoadedLine, "");
			}
			break;

		default:
			if (!through)
			{
				PS3::WriteByte(0x10054320, ReadBuffer[index]);
				//snprintf(ReadBufferConverter, 1, "%c", ReadBuffer[index]);
				strcat(LoadedLine, PS3::ReadString_1(0x10054320));
				PS3::WriteByte(0x10054320, '\0');
			}
			break;
		}

		if (ReadBuffer[index] == '\n')
			through = false;

		index++;
	}
	printf(TestString[LineNumber]);
	printf("\n");
}
#pragma endregion

#pragma region 自動機能
char *test;

namespace AutoOn {
	void do_BoolTrue(char *string)
	{
		bool _bool = (strstr(string, "= true") || (strstr(string, "= TRUE")));

		if (strstr(string, "GodMode")) { GodMode = _bool;  }
		if (strstr(string, "Detection")) { DETECTION_P = _bool;  }
		if (strstr(string, "NoWanted")) { Nocops = _bool;  }
		if (strstr(string, "ForceScriptHost")) { _GetHost = _bool; }
		if (strstr(string, "SuperRun")) { SuperRun = _bool; }
		if (strstr(string, "SuperJump")) { SuperJump = _bool;/* PS3::WriteString2(0x1033F5F0, "スーパージャンプ"); test = PS3::ReadString_1(0x1033F5F0); PS3::WriteByte(0x1033F5F0, '\0');*/ }
		if (strstr(string, "PlayerInformation")) { _PlayerUI = _bool; }
		if (strstr(string, "NameESP")) { NAME_ESP = _bool; }
		if (strstr(string, "HDDTelePo")) { isHDD = _bool; }
		if (strstr(string, "DontViewOpenMenu")) { DontViewOpenMenu = _bool; }
		if (strstr(string, "View_FPS")) { View_FPS = _bool; }
		if (strstr(string, "View_Session")) { View_Session = _bool; }
		if (strstr(string, "VCTalker")) { VCTalker = _bool; }
		if (strstr(string, "HackerView")) { HackerView = _bool; }
		if (strstr(string, "DeleteParachute")) { DeleteParachute = _bool; }
		if (strstr(string, "InfAmmo0")) 
		{ 
			sleep(10000);
			InfAmmo0 = _bool;
			//if (_bool)
				//UnlimitedAmmo(_bool);
		}
		if (strstr(string, "InfAmmo1")) { InfAmmo1 = _bool;  }
		if (strstr(string, "MaxUpgrades")) { MaxUpgrades = _bool; }
		if (strstr(string, "TeleAutomIncar")) { TeleAutomIncar = _bool; };

	}	
	char *locationToRead = "/dev_hdd0/tmp/Auto_Setting.txt";

	//char* locationToRead = "/dev_hdd0/tmp/Re_HyperDx/Auto_Setting.ini";
	//char *TestString[30];

	void Load_String()
	{	
		uint64_t pos;
		int fd;
		uint64_t unk;

		int size = fileSize(locationToRead);
		char ReadBuffer[size];
		if (cellFsOpen(locationToRead, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;

		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		if (cellFsRead(fd, ReadBuffer, size, &unk) != CELL_FS_SUCCEEDED)
			return;

		//printf(ReadBuffer);

		cellFsClose(fd);

		int LineNumber;
		char LoadedLine[100];
		char buf[100];
		strcpy(LoadedLine, "");
		//int index;

		bool through;

		for (int i = 0; i < size; i++)
		{
			if (ReadBuffer[i] == '^' || i == size)
			{
				break;
			}

			if (ReadBuffer[i] == '/' && ReadBuffer[i + 1] == '/')
			{
				i += 1;
				through = true;
			}
			char *TestString = "";
			switch (ReadBuffer[i])
			{

			case '\n':
				if (!through)
				{
					strcpy(buf, LoadedLine);
					TestString = buf;
					//PS3::WriteString(0x10054300, LoadedLine);
					//TestString = PS3::ReadString_1(0x10054300);
					do_BoolTrue(TestString);
			//		printf("%s\n", LoadedLine);
			//		printf("%i\n", LineNumber);
					//LineNumber++;
					PS3::WriteByte(0x10054320, '\0');
					strcpy(LoadedLine, "");
					//TestString = "";
				}
				break;

			default:
				if (!through)
				{
					PS3::WriteByte(0x10054320, ReadBuffer[i]);
					//snprintf(ReadBufferConverter, 1, "%c", ReadBuffer[index]);
					strcat(LoadedLine, PS3::ReadString_1(0x10054320));
					PS3::WriteByte(0x10054320, '\0');
				}
				break;
			}

			if (ReadBuffer[i] == '\n')
				through = false;

			//index++;
		}
	}
}

int DownloadFile_Ini(char* ip = "", char *location = "", char* fileName = "", char* dir = "") {
	struct sockaddr_in sockaddr;
	struct hostent *host;
	unsigned int temp;
	int fd2;
	
	//if (cellFsOpendir(dir, &fd2) != CELL_OK)
	//	cellFsMkdir(dir, CELL_FS_S_IFDIR);
	int fd4;
	CellFsErrno error = cellFsOpen(fileName, CELL_FS_O_RDONLY, &fd4, NULL, 0);
	cellFsClose(fd4);
	//cellFsClose(fd2);
	sleep(100);
	int fd3 = -1;
	//cellFsOpen(fileName, CELL_FS_O_CREAT, &fd, NULL, 0);

	
	//printf("\n\nTest\n\n");
	if (error != CELL_OK)
	{
		char RequestBuf[300];
		CellFsErrno check_status = cellFsOpen(fileName, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_APPEND, &fd3, NULL, 0);
		if (check_status != CELL_OK) {
			//printf("\n\n[DownloadFile] failed with cellFsOpen() 0x%x\nFile : %s\n\n", fd3, fileName);
			return -1;
		}
		else
		{
			//printf("\n\n[DownloadFile] Created 0x%x\n\n\n", fd3);
		}
		bool connected = false;
		int sock;
		int offset = 0;
		int total = 0;
		if ((unsigned int)-1 != (temp = inet_addr(ip))) {
			sockaddr.sin_family = AF_INET;
			sockaddr.sin_addr.s_addr = temp;
			//printf("\n\n[DownloadFile] Host : [TEMP]0x%x\n\n\n", temp);

		}
		else {
			if (NULL == (host = gethostbyname(ip))) {
				return 0;
			}
			//printf("\n\n[DownloadFile] Host : [HOST]0x%x\n\n\n", *((unsigned long*)host->h_addr));
			sockaddr.sin_family = host->h_addrtype;
			memcpy(&sockaddr.sin_addr, host->h_addr, host->h_length);
		}
		//host = gethostbyname(ip);

		//printf("\n\n[DownloadFile] Host : 0x%x\n\n\n", *((unsigned long*)host->h_addr));

		char responseBuffer[0x83];
		sockaddr.sin_port = htons(80); //Choose any port you want (needs to be opened on your server)
									   //sockaddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
		sock = socket(sockaddr.sin_family, SOCK_STREAM, 0);
		if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
			//printf("\n\n[DownloadFile] failed connecting with socket\n\n\n");
			return -1;
		}
		else
		{
			//printf("\n\n[DownloadFile] Connected with socket\n\n\n");
		}

		strcpy(RequestBuf, "GET /");// GET /line/
		strcat(RequestBuf, location);
		//strcat(RequestBuf, GET_);
		strcat(RequestBuf, " HTTP/1.0\r\nHOST: ");

		strcat(RequestBuf, ip);
		//strcat(RequestBuf, "/");
		//strcat(RequestBuf, location);
		strcat(RequestBuf, "\r\n\r\n");
		send(sock, RequestBuf, strlen(RequestBuf), 0);
		//printf("\n\n[DownloadFile]\n %s, 0x%X\n\n", RequestBuf, strlen(RequestBuf));

		char output[100];
		int r, size = 300; //size needs to be hardcoded OR you need to request the filesize from the socket server beforehand

		int lastPercent = 0;
		int progress = 0;
		int delta;
		//Dialog::ShowText("設定ファイルをダウンロード中");
		//Dialog::SetProgressText("");
		//cellMsgDialogOpen2(
		//	CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE | CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE,
		//	"アプデ完了 _ 2",
		//	NULL,
		//	NULL,
		//	NULL
		//);
		while ((r = recv(sock, responseBuffer, sizeof(responseBuffer), 0)) > 0) {
			//printf(responseBuffer);
			total += r;
			delta = total * 100 / size - progress;
			progress += delta;
			//cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, delta);
			//if (offset == 0)
			//{
			//cellFsWrite(fd, responseBuffer, r, NULL);
			//char* z = remove_headers(responseBuffer);
			//cellFsWrite(fd, z, strlen(z), NULL);
			//}
			//else
			if (offset != 0)
				cellFsWrite(fd3, responseBuffer, r, NULL);
			offset++;
		}

		//cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, 100 - progress);
		socketclose(sock);
		cellFsClose(fd3);
		//cellMsgDialogClose(0);

		if (total == 0) {
			//printf("[DownloadFile] No data was received\n");
			return -1;
		}

		//printf("[DownloadFile] Done reading %d bytes\n", total);
		return 0;
	}
}

#pragma endregion

#pragma region HeadLight
void WriteFloatLight(int index, float input)
{
	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
	for (int i = 0; i < 0x5D; i++)
	{
		PS3::WriteFloat(HeadlightAddress + (i * 0x180) + index, input);
	}
}

void WriteByteLight(int index, char input)
{
	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
	for (int i = 0; i < 0x5D; i++)
	{
		PS3::WriteByte(HeadlightAddress + (i * 0x180) + index, input);
	}
}

int light_Index;
int lightCorona_Index;

RGBA HeadLight;
int Corona_intensity[10];
int Corona_intensity_far[10];

int intensity[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int Corona_size[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int Corona_size_far[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int intensity_far[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int numCoronas[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
int falloffMax[] = { 3, 3,3,3,3,3,3,3,3,3 };
int falloffExponent[] = { 8,8,8,8,8,8,8,8,8,8 };
int innerConeAngle[] = { 30,30,30,30, 30,30, 30,30, 30,30 };
int outerConeAngle[] = { 80,80,80,80 ,80,80 ,80,80 ,80,80 };
int Indexed = 1;
int Corona_RedColor[10];
int Corona_GreenColor[10];
int Corona_BlueColor[10];
int RedColor[] = { 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
int GreenColor[10];
int BlueColor[10];
int zBias[10];
int _xRotation[10];
int _yRotation[10];
int _zRotation[10];
int headlightindex;
int headcoronaindex;
Light_ headlight;
LightCorona_ headlight_c;
LightEditor_s Editor;

void LightEditorReady(int lightInd, int coronaInd, bool is_su = false, char*name = "")
{
	Editor.is_sub = is_su;
	Editor.lightIndex = lightInd;
	Editor.coronaIndex = coronaInd;
	Editor.name = name;
	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);

	Editor.lightvalue = *(Light_*)(HeadlightAddress + (0 * 0x180) + Editor.lightIndex);
	Editor.coronavalue = *(LightCorona_*)(HeadlightAddress + (0 * 0x180) + Editor.coronaIndex);

	changeSubmenu(LightEditor_head);
}
//
//void HeadLightReady()
//{
//	Editor.is_sub = false;
//	Editor.lightIndex = 0xEC;
//	Editor.coronaIndex = 0x108;
//	Editor.name = "ヘッドライト";
//	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
//	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
//
//	Editor.lightvalue = *(Light_*)(HeadlightAddress + (0 * 0x180) + Editor.lightIndex);
//	Editor.coronavalue = *(LightCorona_*)(HeadlightAddress + (0 * 0x180) + Editor.coronaIndex);
//
//	changeSubmenu(LightEditor_head);
//}
//
//void TailReady()
//{
//	Editor.is_sub = false;
//	Editor.lightIndex = 0x78;
//	Editor.coronaIndex = 0x94;
//	Editor.name = "テールランプ";
//	int HeadlightIndex = PS3::ReadInt32(0x1CE4E38);
//	int HeadlightAddress = PS3::ReadInt32(HeadlightIndex + 0x1C);
//
//	Editor.lightvalue = *(Light_*)(HeadlightAddress + (0 * 0x180) + Editor.lightIndex);
//	Editor.coronavalue = *(LightCorona_*)(HeadlightAddress + (0 * 0x180) + Editor.coronaIndex);
//
//	changeSubmenu(LightEditor_head);
//}

void TailMiddleReady()
{
}

int LSCIndex;
void ReadyLSCMenu(int index)
{
	LSCIndex = index;
	changeSubmenu(VehicleMenu_Custom_Test_Custom);
}
#pragma endregion

