#include "Weather_pattern_definer.h"
#include "Weather_pattern_selector.h"


unsigned short FindIndexThroughWord(char Pat[WHOLE_PAT][PAT_LEN], const char Code[], unsigned short start)
{
	unsigned short index = start;
	while ((strcmp(Pat[index], Code)) != 0)
		index++;

	return index;
}

unsigned short FindIndexThroughSymbol(char Pat[WHOLE_PAT][PAT_LEN], const char Code, unsigned short start)
{
	unsigned short index = start;
	while (Pat[index][0] != Code)
		index++;

	return index;
}


void Pat2Text(char Pat[][PAT_LEN], const char Operation[], const char Phenomenon[], const char Character[], FILE* fText)
{
	unsigned short start, finish, index = 0;
	start = FindIndexThroughWord(Pat, Operation, 0) + 1;
	if (strlen(Phenomenon))
	{
		start = FindIndexThroughWord(Pat, Phenomenon, start) + 1; if (strlen(Character))
		{
			start = FindIndexThroughWord(Pat, Character, start) + 1;
			finish = (unsigned short)fmin(FindIndexThroughSymbol(Pat, '/', start) - 1, FindIndexThroughSymbol(Pat, '\n', start) - 1);
			index = (rand() % (finish - start + 1)) + start;
			Pat[index][strlen(Pat[index]) - 1] = ' ';
			fprintf(fText, "%s", Pat[index]);
		}
		else
		{
			finish = (unsigned short)fmin(FindIndexThroughSymbol(Pat, '_', start) - 1, FindIndexThroughSymbol(Pat, '\n', start) - 1);
			index = (rand() % (finish - start + 1)) + start;
			Pat[index][strlen(Pat[index]) - 1] = ' ';
			fprintf(fText, "%s", Pat[index]);
		}
	}
	else
	{
		finish = FindIndexThroughSymbol(Pat, '\n', start) - 1;
		index = (rand() % (finish - start + 1)) + start;
		Pat[index][strlen(Pat[index]) - 1] = ' ';
		fprintf(fText, "%s", Pat[index]);
	}

	return;
}


void Selector(WeatherPriority* WPriority, WeatherPriorityData* WPdata)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	unsigned short index = 0, start = 0, finish = 0;
	FILE* fPat = fopen("Patterns.txt", "rt");
	FILE* fText = fopen("Assistive_output.txt", "wt");
	char Pat[WHOLE_PAT][PAT_LEN] = { 0 };
	srand(_getpid());
	while (!feof(fPat))
		fgets(Pat[index++], PAT_LEN, fPat);

	fprintf(fText, "%s", "<Greetings>! ");

	Pat2Text(Pat, "#Announcement\n", "", "", fText);
	fprintf(fText, "\n");

	index = 0;

	fprintf(fText, "%u ", WPdata->date.day);

	switch (WPdata->date.month)
	{
	case(1):	fprintf(fText, "ÿíâàðÿ ");
		break;
	case(2):	fprintf(fText, "ôåâðàëÿ ");
		break;
	case(3):	fprintf(fText, "ìàðòà ");
		break;
	case(4):	fprintf(fText, "àïðåëÿ ");
		break;
	case(5):	fprintf(fText, "ìàÿ ");
		break;
	case(6):	fprintf(fText, "èþíÿ ");
		break;
	case(7):	fprintf(fText, "èþëÿ ");
		break;
	case(8):	fprintf(fText, "àâãóñòà ");
		break;
	case(9):	fprintf(fText, "ñåíòÿáðÿ ");
		break;
	case(10):	fprintf(fText, "îêòÿáðÿ ");
		break;
	case(11):	fprintf(fText, "íîÿáðÿ ");
		break;
	case(12):	fprintf(fText, "äåêàáðÿ ");
		break;
	}

	fprintf(fText, "%u ã:\n", WPdata->date.year);

	if (WPriority[1] == _Temperature)
	{
		switch (WPdata->tempValue)
		{
		case (HIGH_TEMPERATURE):
			Pat2Text(Pat, "#Special_decription\n", "_Temperature\n", "/Too_hot\n", fText);
			break;
		case (LOW_TEMPERATURE):
			Pat2Text(Pat, "#Special_decription\n", "_Temperature\n", "/Too_cold\n", fText);
			break;
		}
		Pat2Text(Pat, "#Standard_description\n", "_Temperature\n", "", fText);
	}

	if (WPriority[0] == _Precipitation)
		switch (WPdata->prepValue)
		{
		case (SNOWSTORM):
		case (RAINSTORM):
			Pat2Text(Pat, "#Special_decription\n", "_Precipitation\n", "/Heavy\n", fText);

			break;
		case (HAIL):
			Pat2Text(Pat, "#Special_decription\n", "_Precipitation\n", "/Grad\n", fText);
			break;
		}

	if (WPriority[2] == _Pressure)
		Pat2Text(Pat, "#Special_decription\n", "_Pressure\n", "", fText);

	if (WPriority[3] == _Wind)
	{
		Pat2Text(Pat, "#Special_decription\n", "_Wind\n", "", fText);
		Pat2Text(Pat, "#Standard_description\n", "_Wind\n", "/General_OK\n", fText);
		Pat2Text(Pat, "#Standard_description\n", "_Wind\n", "/General_Direction\n", fText);
	}

	if (WPriority[4] == _Event)
		Pat2Text(Pat, "#Special_decription\n", "_Event\n", "", fText);

	fclose(fPat);
	fclose(fText);

	return;
}

void Copy2Str(char Source[MES_LEN], unsigned short start, unsigned short finish, char Dest[EX_LEN])
{
	unsigned short i;
	for (i = start; i < finish; ++i)
	{
		Dest[i - start] = Source[i];
	}
	while (i - start < EX_LEN)
	{
		Dest[i - start] = '\0';
		++i;
	}

	return;
}

void freeStr(char* Str)
{
	for (int i = 0; i < strlen(Str); ++i)
		Str[i] = '\0';

	return;
}

void Definition(WeatherPriorityData* WPdata)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fText = fopen("Assistive_output.txt", "rt");
	char Message[MES_LEN] = { 0 };
	char RMessage[MES_LEN] = { 0 };
	char Ex[ST_PUTPUT][EX_LEN] = { 0 };
	char Example[EX_LEN] = { 0 };
	unsigned short index = 0;
	unsigned short shift = 0;
	for (unsigned short i = 0; i < 2; ++i)
		fgets(Ex[i], EX_LEN, fText);
	fgets(Message, MES_LEN, fText);
	fclose(fText);

	for (int index = 1; index < strlen(Message) - 1; ++index)
	{
		freeStr(RMessage);
		int start = index, finish = index + 1;
		if ((Message[index] >= 'A' && Message[index] <= 'Z' && Message[index - 1] == ' ' && Message[index + 1] >= 'A' && Message[index + 1] <= 'Z'))
		{
			while ((Message[finish] >= 'A' && Message[finish] <= 'Z' || Message[finish] == '_') && finish <= strlen(Message))
				finish++;
			Copy2Str(Message, start, finish, Example);
			if (!(strcmp(Example, "HEAVY_PRECIPITATION")))
			{
				switch (WPdata->prepValue)
				{
				case(RAINSTORM):
					strcpy(Example, "heavy_rain");
					break;
				case(SNOWSTORM):
					strcpy(Example, "heavy_snow");
					break;
				}

			}
			if (!(strcmp(Example, "SUBSTANCE")))
			{
				switch (WPdata->prepValue)
				{
				case(RAINSTORM):
				case(RAIN):
					strcpy(Example, "water");
					break;
				case(SNOWSTORM):
				case(SNOW):
					strcpy(Example, "snow");
					break;
				}
			}

			if (!(strcmp(Example, "PRESSURE_VALUE")))
			{
				switch (WPdata->presValue)
				{
				case(LOW_PRESSURE):
					strcpy(Example, "low");
					break;
				case(HIGH_PRESSURE):
					strcpy(Example, "high");
					break;
				}


			}
			if (!(strcmp(Example, "PRECIPITATION")))
			{
				switch (WPdata->prepValue)
				{
				case(RAIN):
					strcpy(Example, "rain");
					break;
				case(SNOW):
					strcpy(Example, "snow");
					break;
				}
			}

			if (!(strcmp(Example, "HEAPS")))
			{
				switch (WPdata->prepValue)
				{
				case(RAIN):
				case(RAINSTORM):
					strcpy(Example, "puddles");
					break;
				case(SNOW):
				case(SNOWSTORM):
					strcpy(Example, "snowdrifts");
					break;
				}
			}

			if (!(strcmp(Example, "DIRECTION")))
			{
				freeStr(Example);
				if (WPdata->windValue == _N)
					strcat(Example, "N");
				if (WPdata->windValue == _S)
					strcat(Example, "S");
				if (WPdata->windValue == _E)
					strcat(Example, "E");
				if (WPdata->windValue == _W)
					strcat(Example, "W");
				if (WPdata->windValue == _NW)
					strcat(Example, "NW");
				if (WPdata->windValue == _SW)
					strcat(Example, "SW");
				if (WPdata->windValue == _NE)
					strcat(Example, "NE");
				if (WPdata->windValue == _SE)
					strcat(Example, "SE");
			}

			if (!(strcmp(Example, "EVENT_VALUE")))
			{
				freeStr(Example);
				unsigned short pos = 0;
				for (pos; pos < sizeof(WPdata->events); ++pos)
				{
					if (strlen(WPdata->events[pos]))
					{
						strcat(Example, WPdata->events[pos]);
						if (strlen(WPdata->events[pos + 1]) && !strlen(WPdata->events[pos + 2]))
							strcat(Example, " è ");
						if (strlen(WPdata->events[pos + 1]) && strlen(WPdata->events[pos + 2]))
							strcat(Example, ", ");
					}
				}
			}

			for (int j = 0; j <= strlen(Message) - start; ++j)
				Message[j + start] = Message[finish + j];

			strncat(RMessage, Message, start);
			strcat(RMessage, Example);
			strcat(RMessage, Message + start);
			strcpy(Message, RMessage);
		}
	}

	FILE* fOutput = fopen("Space_text.txt", "wt");
	for (int i = 0; i < 2; ++i)
		fprintf(fOutput, "%s", Ex[i]);
	fprintf(fOutput, "%s", Message);

	fclose(fOutput);

	return;
}
