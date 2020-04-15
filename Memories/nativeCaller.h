#pragma once

struct OPD_s {
	uint32_t sub;
	uint32_t toc;
};

struct NativeArg_s {
	void* pRet;
	int Count;
	void* pArg;
	template <typename T>
	T GetArg(int index)
	{
		return ((T*)this->pArg)[index];
	}
	template <typename T>
	void SetRet(T ret)
	{
		*(T*)this->pRet = ret;
	}
};
struct NativeTable_s {
	NativeTable_s* pNextTable;
	OPD_s* pNatives[7];
	int NativeCount;
	uint32_t Hashes[7];
}**NativeTable;

void HookNative(OPD_s* Native, void(*func)(NativeArg_s*))
{
	Native->sub = ((OPD_s*)func)->sub;
}

NativeTable_s** GetNativeTable(void)
{
	uint32_t tableAddress = 0;
	uint32_t byteArray[2] = { 0x3C6072BD, 0x3C8001C2 };
	uint32_t byteArray2[2] = { 0x3FC0, 0x33DE };
	for (uint32_t address = 0x380000; address < 0x480000; address += 4) {
		//find storing native address
		if (*(uint32_t*)address == byteArray[0]) {
			if (*(uint32_t*)(address + 4) == byteArray[1]) {
				//find bl
				for (; !(*(uint32_t*)address >= 0x48000000 && *(uint32_t*)address < 0x4C000000); address += 4);
				//get bl destination
				if (*(uint32_t*)address < 0x4A000000) address = address + (*(uint32_t*)address - 0x48000001);
				else address = address - (0x4C000001 - *(uint32_t*)address);
				//find lis r30
				for (; *(uint16_t*)address != byteArray2[0]; address += 4);
				tableAddress += *(uint16_t*)(address + 2) << 16;
				//find addic r30, r30
				for (; *(uint16_t*)address != byteArray2[1]; address += 4);
				tableAddress += *(uint16_t*)(address + 2);
				if (*(uint16_t*)(address + 2) >= 0x8000) tableAddress -= 0x10000;
				return (NativeTable_s**)tableAddress;
			}
		}
	}
	return NULL;
}

uint32_t Bls[16];
uint32_t* GetBls(OPD_s* func)
{
	int blsCount = 0;
	uint32_t address, addrCurr;
	for (address = func->sub;;address+=4) {
		addrCurr = *(uint32_t*)address;
		if (addrCurr >= 0x48000000 && addrCurr < 0x4C000000) {
			if ((addrCurr & 0xFF) % 4 == 0) {
				return Bls;
			}

			if (addrCurr < 0x4A000000)
				Bls[blsCount++] = address + (addrCurr - 0x48000001);
			else Bls[blsCount++] = address - (0x4C000001 - addrCurr);
		}
	}
}

//joaat hash
uint32_t jenkins_one_at_a_time_hash(char* key) {
	size_t i = 0, length = strlen(key);
	uint32_t hash = 0;
	while (i != length) {
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}

OPD_s* GetNative(uint32_t Hash)
{
	int i = 0;
	NativeTable_s* Table = NULL;
	Table = NativeTable[Hash & 0xFF];
	while (Table->Hashes[i] != Hash)
	{
		i++;
		if (i == Table->NativeCount) {
			i = 0;
			Table = Table->pNextTable;
			if (Table == NULL)
				return NULL;
		}
	}
	return Table->pNatives[i];
}

void CallNative(OPD_s* Native, NativeArg_s* Arg)
{
	((void(*)(NativeArg_s*))Native)(Arg);
}

template <typename T>
T GetReturn(NativeArg_s* Arg)
{
	return *(T*)Arg->pRet;
}

void ResetArg(NativeArg_s* Arg, char* buffer)
{
	Arg->pRet = buffer;
	Arg->pArg = buffer;
	Arg->Count = 0;
}

template <typename T>
void PushArg(NativeArg_s* Arg, T param)
{
	((T*)Arg->pArg)[Arg->Count++] = param;
}

template <typename T>
T invoke(uint32_t Hash)
{
	NativeArg_s arg_s;
	char buffer[4];
	ResetArg(&arg_s, buffer);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1>
T invoke(uint32_t Hash, P1 p1)
{
	NativeArg_s arg_s;
	char buffer[4 * 1];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}

template <typename T, typename P1, typename P2>
T invoke(uint32_t Hash, P1 p1, P2 p2)
{
	NativeArg_s arg_s;
	char buffer[4 * 2];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2>
T invoke_a(uint32_t Hash, P1 p1, P2 p2)
{
	NativeArg_s arg_s;
	char buffer[4 * 2];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3)
{
	NativeArg_s arg_s;
	char buffer[4 * 3];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4)
{
	NativeArg_s arg_s;
	char buffer[4 * 4];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
	NativeArg_s arg_s;
	char buffer[4 * 5];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
	NativeArg_s arg_s;
	char buffer[4 * 6];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
{
	NativeArg_s arg_s;
	char buffer[4 * 7];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
{
	NativeArg_s arg_s;
	char buffer[4 * 8];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
{
	NativeArg_s arg_s;
	char buffer[4 * 9];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
{
	NativeArg_s arg_s;
	char buffer[4 * 10];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11)
{
	NativeArg_s arg_s;
	char buffer[4 * 11];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12)
{
	NativeArg_s arg_s;
	char buffer[4 * 12];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13)
{
	NativeArg_s arg_s;
	char buffer[4 * 13];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14)
{
	NativeArg_s arg_s;
	char buffer[4 * 14];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15)
{
	NativeArg_s arg_s;
	char buffer[4 * 15];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16)
{
	NativeArg_s arg_s;
	char buffer[4 * 16];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17)
{
	NativeArg_s arg_s;
	char buffer[4 * 17];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18)
{
	NativeArg_s arg_s;
	char buffer[4 * 18];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19)
{
	NativeArg_s arg_s;
	char buffer[4 * 19];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20)
{
	NativeArg_s arg_s;
	char buffer[4 * 20];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21)
{
	NativeArg_s arg_s;
	char buffer[4 * 21];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22)
{
	NativeArg_s arg_s;
	char buffer[4 * 22];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23)
{
	NativeArg_s arg_s;
	char buffer[4 * 23];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24)
{
	NativeArg_s arg_s;
	char buffer[4 * 24];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25)
{
	NativeArg_s arg_s;
	char buffer[4 * 25];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26)
{
	NativeArg_s arg_s;
	char buffer[4 * 26];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27)
{
	NativeArg_s arg_s;
	char buffer[4 * 27];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27, P28 p28)
{
	NativeArg_s arg_s;
	char buffer[4 * 28];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	PushArg(&arg_s, p28);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27, P28 p28, P29 p29)
{
	NativeArg_s arg_s;
	char buffer[4 * 29];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	PushArg(&arg_s, p28);
	PushArg(&arg_s, p29);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27, P28 p28, P29 p29, P30 p30)
{
	NativeArg_s arg_s;
	char buffer[4 * 30];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	PushArg(&arg_s, p28);
	PushArg(&arg_s, p29);
	PushArg(&arg_s, p30);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27, P28 p28, P29 p29, P30 p30, P31 p31)
{
	NativeArg_s arg_s;
	char buffer[4 * 31];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	PushArg(&arg_s, p28);
	PushArg(&arg_s, p29);
	PushArg(&arg_s, p30);
	PushArg(&arg_s, p31);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26, typename P27, typename P28, typename P29, typename P30, typename P31, typename P32>
T invoke(uint32_t Hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15, P16 p16, P17 p17, P18 p18, P19 p19, P20 p20, P21 p21, P22 p22, P23 p23, P24 p24, P25 p25, P26 p26, P27 p27, P28 p28, P29 p29, P30 p30, P31 p31, P32 p32)
{
	NativeArg_s arg_s;
	char buffer[4 * 32];
	ResetArg(&arg_s, buffer);
	PushArg(&arg_s, p1);
	PushArg(&arg_s, p2);
	PushArg(&arg_s, p3);
	PushArg(&arg_s, p4);
	PushArg(&arg_s, p5);
	PushArg(&arg_s, p6);
	PushArg(&arg_s, p7);
	PushArg(&arg_s, p8);
	PushArg(&arg_s, p9);
	PushArg(&arg_s, p10);
	PushArg(&arg_s, p11);
	PushArg(&arg_s, p12);
	PushArg(&arg_s, p13);
	PushArg(&arg_s, p14);
	PushArg(&arg_s, p15);
	PushArg(&arg_s, p16);
	PushArg(&arg_s, p17);
	PushArg(&arg_s, p18);
	PushArg(&arg_s, p19);
	PushArg(&arg_s, p20);
	PushArg(&arg_s, p21);
	PushArg(&arg_s, p22);
	PushArg(&arg_s, p23);
	PushArg(&arg_s, p24);
	PushArg(&arg_s, p25);
	PushArg(&arg_s, p26);
	PushArg(&arg_s, p27);
	PushArg(&arg_s, p28);
	PushArg(&arg_s, p29);
	PushArg(&arg_s, p30);
	PushArg(&arg_s, p31);
	PushArg(&arg_s, p32);
	CallNative(GetNative(Hash), &arg_s);
	return GetReturn<T>(&arg_s);
}
