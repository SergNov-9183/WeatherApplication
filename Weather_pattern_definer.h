#ifndef WEATHER_PATTERN_DEFINER_H
#define WEATHER_PATTERN_DEFINER_H
#define _CRT_SECURE_NO_WARNINGS
#define MES_LEN 2048
#define EX_LEN 128
#define ST_PUTPUT 2
#include <stdio.h>
#include <string.h>
#include "WeatherPriority.h"


void Copy2Str(char Source[MES_LEN], unsigned short start, unsigned short finish, char Dest[EX_LEN]);

void freeStr(char* Str);

void Definition(WeatherPriorityData* WPdata);

#endif //WEATHER_PATTERN_DEFINER_H

