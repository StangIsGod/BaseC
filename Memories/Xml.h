namespace XmlLoader {

	void StringDelete(char *s1, char *s2)
	{
		char *p = s1;
		p = strstr(s1, s2);
		if (p != NULL) {
			strcpy(p, p + strlen(s2));
			StringDelete(p + 1, s2);
		}
	}

	
	//Hash ReadObjectFile[100]; 
	bool LoadObjectFileBOOL;
	int ReadObjectFileCount, ReadObjectFileCountName;
	void ReadXMLObject(char* path)
	{
		char line[500];
		int fd; uint64_t unk; 
		int file_size = fileSize(path); 
		ReadObjectFileCount = 0, ReadObjectFileCountName = 0;
		char* PoolMemory = (char*)0x10020000;
		
		if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
			return;
		else
			cellFsRead(fd, (char*)0x10020000, file_size, &unk);
		cellFsClose(fd);

		for (int i = 0; i < file_size; i++)
		{
			if (PoolMemory[i] == 0x00)
				break;

			if (PoolMemory[i] == '\r' && PoolMemory[i + 1] == '\n')
			{
				if (strstr(line, "<name>"))
				{
					printf(line);
					StringDelete(line, "<name>");
					PS3::WriteString(0x10070000 + (0x50 * ReadObjectFileCountName), line);
					ReadObjectFileCountName++;
					
				}
				if (strstr(line, "<object>"))
				{
					printf(line);
					StringDelete(line, "<object>");
					PS3::WriteString(0x10060000 + (0x50 * ReadObjectFileCount), line);
					//PS3::WriteUInt32(0x10060000, GAMEPLAY::GET_HASH_KEY(line));
					//ReadObjectFile[ReadObjectFileCount] = GAMEPLAY::GET_HASH_KEY(line);
					ReadObjectFileCount++;
				}
				memset(line, 0, 500);
			}
			else
			{
				PS3::WriteByte(0x10065300, PoolMemory[i]);
				strcat(line, PS3::ReadString_1(0x10065300));
				PS3::WriteByte(0x10065300, '\0');
			}
		}
	}
}