#ifndef WEATHER_PATTERN_SELECTOR_H _
#define WEATHER_PATTERN_SELECTOR_H _
#define _CRT_SECURE_NO_WARNINGS
#define WHOLE_PAT 128
#define PAT_LEN 512
#define NUM_PAT 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#include "WeatherPriority.h"
#include <windows.h>


int FindIndexThroughWord(char Pat[WHOLE_PAT][PAT_LEN], const char Code[], unsigned short start);

int FindIndexThroughSymbol(char Pat[WHOLE_PAT][PAT_LEN], const char Code, unsigned short start);

void Pat2Text(char Pat[][PAT_LEN], const char Operation[], const char Phenomenon[], const char Character[], FILE* fText);

void Selector(WeatherPriority* WPriority, WeatherPriorityData* WPdata);

#endif //WEATHER_PATTERN_SELECTOR_H
