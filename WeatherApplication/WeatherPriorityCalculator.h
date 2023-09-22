#ifndef WeatherPriorityCalculatorHeaderDefined _
#define WeatherPriorityCalculatorHeaderDefined _
#include "WeatherPriority.h"
#include "Weather_data.h"
const struct Bounds {
	float Lbound;
	float Rbound;
};

const struct Bounds PrepBounds = { -1,1 };
const struct Bounds TempBounds = { -18,20 };
const struct Bounds WindBounds = { 0, 10.8f };
const struct Bounds PressureBounds = { 740, 750 };
WeatherPriority* CalculatePriotity(WeatherData* data) {
	WeatherPriority* resultVector = malloc(sizeof(WeatherPriority)*5);
	for (int i = 0; i < 5; i++)
		resultVector[i] = None;
	if (data->precipitation_amount > PrepBounds.Rbound) {
		resultVector[0] = _Precipitation;
	}
	if (data->day_temp.min < TempBounds.Lbound || data->day_temp.max > TempBounds.Rbound) {
		resultVector[1] = _Temperature;
	}
	else if (data->night_temp.min < TempBounds.Lbound || data->night_temp.max > TempBounds.Rbound) {
		resultVector[1] = _Temperature;
	}
	else if (data->perceived_temp.min < TempBounds.Lbound || data->perceived_temp.max > TempBounds.Rbound) {
		resultVector[1] = _Temperature;
	}
	if (data->pressure > PressureBounds.Rbound || data->pressure < PressureBounds.Lbound) {
		resultVector[2] = _Pressure;
	}
	if (data->wind_data.max_speed > WindBounds.Rbound) {
		resultVector[3] = _Wind;
	}
	for (int i = 0; i < max_events; i++) {
		if (data->event[i][0] != 0) {
			resultVector[4] = _Event;
		}
	}

	return resultVector;
}

WeatherPriorityData FormPriortyData(WeatherData* data, WeatherPriority* priority) {
	WeatherPriorityData result = { 0,0,0,0,0, {data->date.day, data->date.month, data->date.year} };
	char precipitation[precipitation_quan][string_len] = { "дождь\0", "снег\0", "град\0", "ливень\0", "снегопад\0" };
	for (int i = 0; i < sizeof(*priority); i++) {
		if (priority[i] == _Precipitation) {
			if (strcmp(data->precipitation, precipitation[0]))
				result.prepValue = RAIN;
			if (strcmp(data->precipitation, precipitation[1]))
				result.prepValue = SNOW;
			if (strcmp(data->precipitation, precipitation[2]))
				result.prepValue = HAIL;
			if (strcmp(data->precipitation, precipitation[3]))
				result.prepValue = RAINSTORM;
			if (strcmp(data->precipitation, precipitation[4]))
				result.prepValue = SNOWSTORM;
		}
		if (priority[i] == _Temperature) {
			if (data->day_temp.min < TempBounds.Lbound) {
				result.tempValue = LOW_TEMPERATURE;
			}
			else {
				result.tempValue = HIGH_TEMPERATURE;
			}
		}
		if (priority[i] == _Pressure) {
			if (data->pressure > PressureBounds.Rbound) {
				result.presValue = HIGH_PRESSURE;
			}
			else {
				result.presValue = LOW_PRESSURE;
			}
		}
		if (priority[i] == _Wind) {
			for (int u = 0; u < sizeof(data->wind_data.directions); u++) {
				result.windValue = u;
			}
		}
		if (priority[i] == _Event) {
			result.events = data->event;
		}
	}


	return result;
}

#endif
