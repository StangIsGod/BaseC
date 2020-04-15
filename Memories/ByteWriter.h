bool PSNspoof;
bool PSNspoof1 = true;
bool PSNspoof12;
bool KickDetectedFreeze = true;
char HIKAKU[] ="AMAKAKE";
char HIKAKU2[] = "ANMS";
char HIKAKU3[] = "amakake";
char HIKAKU4[] = "JOKER";
char HIKAKU5[] = "joker";
char HIKAKU6[] = "anms";

namespace PS3
{
	unsigned int PlayerNameActual = 0x0200255C;
	void Write(int fd, char* Text, uint64_t unk)
	{
		cellFsWrite(fd, (const void*)Text, strlen(Text), &unk);
	}
	int fd;
	uint64_t unk;
	void WriteFile(char* dummy, char* URL)
	{
		//LicenseText = "Demo";
		char* LicenseText = dummy;
		char* LicenseFile = URL;

		//It has to be in some description of a folder (it can't be on the root of HDD0)
		if (cellFsOpen(LicenseFile, CELL_FS_O_CREAT | CELL_FS_O_WRONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;

		cellFsWrite(fd, (const void*)LicenseText, strlen(LicenseText), &unk);
		cellFsClose(fd);
	}

	const char* ReadTextFileLis(const char* Path)
	{
		char str[200], w[100], r[100], buf[200];
		int fd, dir;
		CellFsErrno Errno; CellFsErrno OG;
		uint64_t sw, pos, sr, rd;
		Errno = cellFsOpen(Path, CELL_FS_O_RDONLY, &fd, NULL, 0);
		if (Errno == 0)
		{
			Errno = cellFsRead(fd, str, sizeof(str), &sw);
			OG = Errno;
			Errno = cellFsClose(fd);
			if (OG == 0)
				return str;
			return "";
		}
		return "";
	}

	int SetGlobal(unsigned int globalId, int value, int wouldRead)
	{
		static unsigned int** arr = (unsigned int**)0x1E70370;
		switch (wouldRead)
		{
		case 0: arr[(globalId >> 18) & 0x3F][globalId & 0x3FFFF] = value;  break; //write
		case 1: return arr[(globalId >> 18) & 0x3F][globalId & 0x3FFFF];  break; //read
		}
	}
	
	void SetTunable(int index, int value)
	{
		int address = (*(int*)0x1E70374) + 4; //address‚ª1E70374‚É‚©‚í‚é
		{
			if (address != 0) //address‚ª0‚Å•Ô‚³‚ê‚È‚¢‚Æ‚«Ÿ‚Ì®‚ÉÀs
			{
				int temp = address; //‚±‚±‚Å‚àaddress‚ğtemp‚É‚©‚¦‚é
				temp += (index * 4); // temp(!E70374) + (index x 4)
				*(int*)temp = value; //ŒvZŒ‹‰Ê‚Ìaddress‚Ì‚Æ‚±‚ë‚Évalue‚ğ‘‚«‚Ş
			}
		}
	}

	int* ReadInt(int address, int length)
	{
		int intArray[100];
		for (int i = 0; i < length; i++)
		{
			intArray[i] = *(int*)(address + (i * 0x04));
		}
		return intArray;
	}

	uint64_t ReadUInt64(int address)
	{
		return *(uint64_t*)address;
	}

	int ReadInt16(int address)
	{
		return *(short*)address;
	}

	void WriteInt(int address, int* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(int*)(address + (i * 0x04)) = input[i];
		}
	}

	void WriteFloat(int address, float input)
	{
		*(float*)(address) = input;
	}

	float ReadFloat(int address)
	{
		return *(float*)address;
	}

	void WriteBytes(int address = 0, char* input = "", int length = 0, bool Sleep = false)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
			if (Sleep)
			{
				sleep(100);
			}
		}
	}

	void WriteBytes2(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}
	char byteArray3[144];
	char* ReadBytes3(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray3[i] = *(char*)(address + (i));
		}
		return byteArray3;
	}
	void WriteByte(int address = 0, char input = NULL)
	{
		*(char*)(address) = input;
	}
	char byteArray[100];

	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}

	char ReadByte(int address)
	{
		char Byte;
		Byte = *(char*)(address);
		return Byte;
	}


	int Read_Global(int a_uiGlobalID) 
	{
		int BBB2, CCC2, Ptr;
		Ptr = *(int*)((0x1E70374 - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
		if (Ptr != 0)
		{
			//PRINT(ItoS(Ptr), 2000);
			BBB2 = Ptr + ((a_uiGlobalID % 0x40000) * 4);
			CCC2 = *(int*)BBB2;

			return CCC2;
		}
		return 0;
	}

	//2399048 + 2415 + 232

	void NotifyDown(char*msg, int timer = 2000)
	{
		UI::_0xF42C43C7("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_0x38F82261(timer, 1);
	}


	int Read_Global_Printf(int a_uiGlobalID)
	{
		int BBB2, CCC2, Ptr;
		Ptr = *(int*)((0x1E70374 - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
		if (Ptr != 0)
		{
			//PRINT(ItoS(Ptr), 2000);
			BBB2 = Ptr + ((a_uiGlobalID % 0x40000) * 4);
			NotifyDown(ItoS(BBB2,true),5000);
		}
	}


	
	

	bool Write_Global(int a_uiGlobalID, int a_uiValue)
	{
		int Ptr = *(int*)((0x1E70374 - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
		if (Ptr != 0)
		{
			*(int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4)) = a_uiValue;
			return true;
		}
		return false;
	}

	void WriteString(int address, char* string)
	{
		int strlength = std::strlen(string);
		for (int i = 0; i < strlength; i++)
		{
			WriteByte(address + i, string[i]);
		}
		WriteByte(address + strlength, '\0');
	}
	char *Read_Global_Char(int a_uiGlobalID)
	{
		int Ptr = *(int*)((0x1E70370)+(((a_uiGlobalID / 0x40000) & 0x3F) * 4));
		if (Ptr != 0)
			return ReadBytes((Ptr + ((a_uiGlobalID % 0x40000) * 4)), 0x10);
		return 0;
	}
	void WriteString2(int address, char* string)
	{
		int FreeMem = 0x1D00000;
		int strlength = std::strlen(string);
		char* strpointer = *(char**)FreeMem = string;
		char* StrBytes = PS3::ReadBytes(*(int*)FreeMem, strlength);
		PS3::WriteBytes(address, StrBytes, strlength);
		*((char*)address + strlength) = '\0';
	}
	char* ReadString_1(int Address)
	{
		return (char*)Address;
	}
	char* ReadString(int address)
	{
		char returnRead[100];
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}
	
	const char *ReadString1(int address)
	{
		char returnR[100];
		char returnRead[100];
		memset(&returnRead[0], 0, sizeof(returnR));
		int strlength = 100;
		const char *StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnR;
	}

	void WriteInt32(int Address, int Input)
	{
		*(int*)Address = Input;
	}

	int ReadInt32(int Address)
	{
		return *(int*)Address;
	}

	void WriteUInt32(int Address, unsigned int Input)
	{
		*(unsigned int*)Address = Input;
	}

	unsigned int ReadUInt32(int Address)
	{
		return *(unsigned int*)Address;
	}

	float* ReadFloats(int address, int length)
	{
		float floatArray[100];
		for (int i = 0; i < length; i++)
		{
			floatArray[i] = *(float*)(address + (i * 0x04));
		}
		return floatArray;
	}

}
//13C0CE8
bool CompareMemory(const uint8_t* pData, const uint8_t* bMask, const char* sMask)
{
	for (; *sMask; ++sMask, ++pData, ++bMask)
		if (*sMask == 'x' && *pData != *bMask)
			return false;

	return *sMask == NULL;
}
typedef unsigned char* PBYTE;
bool Match(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dwAddress = 0x20000000, DWORD dwLen = 0xFFFF, BYTE *bMask = 0, char * szMask = "xx")
{
	for (DWORD i = 0; i < dwLen; i += 4)
		if (Match((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

void ProtectionPatch(int Address, bool toggle)
{
	PS3::WriteInt32(Address, toggle ? 0x4E800020 : 0x7C0802A6);
}
