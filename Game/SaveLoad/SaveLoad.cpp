#include "stdafx.h"
#include "SaveLoad.h"

SaveLoad::SaveLoad()
{
	Load();
}

void SaveLoad::Load()
{
	FILE* file;
	if (fopen_s(&file, "save.sid", "rb") == NULL)
		return;
	int r = 0,c = 0;
	for (int i = 0; i < 30; i++)
	{
		int rank = 0;
		fread(&rank, 1, 1, file);
		int sco = 0;
		fread(&sco, sizeof(sco), 1, file);
		switch (r)
		{
		case 0:
			B.push_back(sco);
			break;
		case 1:
			I.push_back(sco);
			break;
		case 2:
			A.push_back(sco);
			break;
		}
		if (c == 9)
		{
			c = 0;
			r++;
		}
		else
			c++;
	}
}

void SaveLoad::Save()
{
	FILE* file;
	if (fopen_s(&file, "save.sid", "wb") == NULL)
		return;
	int r = 0, c = 0;
	for (int i = 0; i < 30; i++)
	{
		fwrite(&c, 1, 1, file);
		int sco = 0;
		switch (r)
		{
		case 0:
			sco = B[c];
			break;
		case 1:
			sco = I[c];
			break;
		case 2:
			sco = A[c];
			break;
		}
		int rank = 0;
		fwrite(&sco, sizeof(sco), 1, file);
		
		if (c == 9)
		{
			c = 0;
			r++;
		}
		else
			c++;
	}
}
