/*#ifndef MainDefined _
#define MainDefined _
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Weather_pattern_selector.h"
#include "Weather_pattern_definer.h"

int main()
{
	WeatherPriorityData WPdata;
	WeatherPriority WPriority[5] = { _Precipitation, _Temperature, _Pressure, _Wind, _Event };
	WPdata.events = malloc(sizeof(char*) * 12);
	for (unsigned i = 0; i < sizeof(WPdata.events); ++i)
		WPdata.events[i] = malloc(sizeof(char) * 256);
	for (unsigned i = 0; i < sizeof(WPdata.events); ++i)
		strcpy(WPdata.events[i], "");
	WPdata.prepValue = SNOWSTORM;
	WPdata.tempValue = HIGH_TEMPERATURE;
	WPdata.presValue = LOW_PRESSURE;
	WPdata.windValue = _NE;
	WPdata.date.day = 23;
	WPdata.date.month = 9;
	WPdata.date.year = 2010;
	strcpy(WPdata.events[0], "гроза\0");
	strcpy(WPdata.events[1], "штормовой ветер\0");
	strcpy(WPdata.events[2], "праздник\0");
	Selector(WPriority, &WPdata);
	Definition(&WPdata);
	return 0;
}
#endif*/