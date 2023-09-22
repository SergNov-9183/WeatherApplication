#ifndef Weather_data_H
#define Weather_data_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define string_len 256
#define text_len 2560
#define max_events 30
#define events_quan 4
#define precipitation_quan 5

typedef enum { N, NE, E, SE, S, SW, W, NW } CardinalDir;

typedef struct {
	unsigned day;
	unsigned month;
	unsigned year;
} Date;

typedef struct {
	short min;
	short max;
} Temperature;

typedef struct {
	unsigned short min_speed;
	unsigned short max_speed;

	unsigned short directions[NW + 1];

	unsigned short min_gusts;
	unsigned short max_gusts;
} Wind;

typedef struct {
	Date date;
	Temperature day_temp;
	Temperature night_temp;
	Temperature perceived_temp;
	char precipitation[string_len];
	unsigned short precipitation_amount;
	Wind wind_data;
	unsigned short pressure;
	char event[max_events][string_len];
} WeatherData;

void DashSkip(char str[], unsigned short* i) {
	while (str[*i] == ' ' || str[*i] == '\t')
		++(*i);
	return;
}

void WeatherToZero(WeatherData* weather_data) {
	const char zeroStr[string_len] = { 0 };
	const unsigned short zeroDir[NW + 1] = { 0 };

	weather_data->date.day = 0;
	weather_data->date.month = 0;
	weather_data->date.year = 0;

	weather_data->day_temp.min = 0;
	weather_data->day_temp.max = 0;

	weather_data->night_temp.min = 0;
	weather_data->night_temp.max = 0;

	weather_data->perceived_temp.min = 0;
	weather_data->perceived_temp.max = 0;

	memcpy(weather_data->precipitation, zeroStr, sizeof(char) * string_len);
	weather_data->precipitation_amount = 0;

	weather_data->wind_data.min_speed = 0;
	weather_data->wind_data.max_speed = 0;
	memcpy(weather_data->wind_data.directions, zeroDir, sizeof(CardinalDir) * (NW + 1));
	weather_data->wind_data.min_gusts = 0;
	weather_data->wind_data.max_gusts = 0;

	weather_data->pressure = 0;

	for (int i = 0; i < max_events; ++i)
		memcpy(weather_data->event[i], zeroStr, sizeof(char) * string_len);

	return;
}

void GetDate(Date* date, char str[], unsigned str_num, unsigned short* i) {
	date->day = 0;
	date->month = 0;
	date->year = 0;
	for (; str[*i] != '.'; ++(*i)) {
		if (str[*i] < '0' || str[*i] > '9') {
			if (str_num)
				fprintf(stderr, "Incorrect date input format\nLine - %u", str_num);
			else
				fprintf(stderr, "The specified date is not in the correct format (day.month.year)");
			exit(1);
		}
		date->day = date->day * 10 + str[*i] - '0';
	}
	++(*i);
	for (; str[*i] != '.'; ++(*i)) {
		if (str[*i] < '0' && str[*i] > '9') {
			if (str_num)
				fprintf(stderr, "Incorrect date input format\nLine - %u", str_num);
			else
				fprintf(stderr, "The specified date is not in the correct format (day.month.year)");
			exit(1);
		}
		date->month = date->month * 10 + str[*i] - '0';
	}
	++(*i);
	if (str[*i] < '0' || str[*i]>'9') {
		if (str_num)
			fprintf(stderr, "Incorrect date input format\nLine - %u", str_num);
		else
			fprintf(stderr, "The specified date is not in the correct format (day.month.year)");
		exit(1);
	}
	for (; str[*i] != ' ' && str[*i] != 0 && str[*i] != '\t'; ++(*i)) {
		if (str[*i] < '0' && str[*i] > '9') {
			if (str_num)
				fprintf(stderr, "Incorrect date input format\nLine - %u", str_num);
			else
				fprintf(stderr, "The specified date is not in the correct format (day.month.year)");
			exit(1);
		}
		date->year = date->year * 10 + str[*i] - '0';
	}
	return;
}

void GetTemperature(Temperature* temp, char str[], unsigned str_num, unsigned short* i) {
	DashSkip(str, i);
	unsigned short is_negative = 0;
	if (str[*i] == '-') {
		is_negative = 1;
		++(*i);
	}
	for (; str[*i] != '.' && !(str[*i] == ' ' || str[*i] == '\t'); ++(*i)) {
		if (str[*i] < '0' || str[*i] > '9') {
			fprintf(stderr, "Incorrect temperature input format\nLine - %u", str_num);
			exit(1);
		}
		temp->min = temp->min * 10 + str[*i] - '0';
	}
	if (is_negative)
		temp->min = -temp->min;
	is_negative = 0;
	if (str[*i] == ' ' && str[*i] == '\t')
		temp->max = temp->min;
	else {
		if (str[*i] != '.' || str[(*i) + 1] != '.') {
			fprintf(stderr, "Incorrect temperature input format\nLine - %u", str_num);
			exit(1);
		}
		(*i) += 2;
		if (str[*i] == '-') {
			is_negative = 1;
			++(*i);
		}
		for (; str[*i] != ' ' && str[*i] != '\t'; ++(*i)) {
			if (str[*i] < '0' || str[*i] > '9') {
				fprintf(stderr, "Incorrect temperature input format\nLine - %u", str_num);
				exit(1);
			}
			temp->max = temp->max * 10 + str[*i] - '0';
		}
		if (is_negative)
			temp->max = -temp->max;
	}
	return;
}

void GetPrecipitation(char dest[], char str[], unsigned str_num, unsigned short *i) {
	DashSkip(str, i);
	int j = 0;
	while (str[*i] != ' ' && str[*i] != '\t') {
		if ((str[*i] < -32 || str[*i] > -1)&&str[*i]!=-72) {
			fprintf(stderr, "Incorrect precipitation input format\nLine - %u", str_num);
			exit(1);
		}
		dest[j++] = str[(*i)++];
	}
	char no[4] = { 237, 229, 242, 0 };
	
	if (!strcmp(dest, no)) {
		dest[0] = 0;
		dest[1] = 0;
		dest[3] = 0;
	}
	else {
		char precipitation[precipitation_quan][string_len] = { "дождь\0", "снег\0", "град\0", "ливень\0", "снегопад\0" };
		unsigned short isPrecipitation = 0;
		for (int j = 0; j < precipitation_quan && !isPrecipitation; ++j) {
			if (!strcmp(precipitation[j], dest))
				isPrecipitation = 1;
		}
		if (!isPrecipitation) {
			setlocale(LC_ALL, "Russian");
			fprintf(stderr, "The program does not process such an precipitation: <%s>\nLine - %d", dest, str_num);
			exit(1);
		}
	}
	return;
}

void GetWindSpeed(unsigned short* min, unsigned short* max, char str[], unsigned str_num, unsigned short* i) {
	DashSkip(str, i);
	for (; str[*i] != '-' && !(str[*i] == ' ' || str[*i] == '\t'); ++(*i)) {
		if (str[*i] < '0' || str[*i] > '9') {
			fprintf(stderr, "Incorrect wind speed input format\nLine - %u", str_num);
			exit(1);
		}
		*min = (*min) * 10 + str[*i] - '0';
	}
	if (str[*i] == ' ' || str[*i] == '\t')
		*max = *min;
	else {
		if (str[*i] != '-') {
			fprintf(stderr, "Incorrect wind speed input format\nLine - %u", str_num);
			exit(1);
		}
		++(*i);
		for (; !(str[*i] == ' ' || str[*i] == '\t'); ++(*i)) {
			if (str[*i] < '0' || str[*i] > '9') {
				fprintf(stderr, "Incorrect wind speed input format\nLine - %u", str_num);
				exit(1);
			}
			*max = (*max) * 10 + str[*i] - '0';
		}
	}
	return;
}

void GetDir(unsigned short dir[], char str[], unsigned str_num, unsigned short* i) {
	char cur_dir[4] = { 0 };
	DashSkip(str, i);
	while (!(str[*i] == ' ' || str[*i] == '\t')) {
		int len = 0;
		while (str[*i] != ',' && !(str[*i] == ' ' || str[*i] == '\t'))
			cur_dir[len++] = str[(*i)++];
		if (len == 1) {
			switch (cur_dir[0])
			{
			case -47: // N
				dir[N] = 1;
				break;
			case -62: // E
				dir[E] = 1;
				break;
			case -34: // S
				dir[S] = 1;
				break;
			case -57: // W
				dir[W] = 1;
				break;
			default:
				fprintf(stderr, "Incorrect direction input format\nLine - %u", str_num);
				exit(1);
			}
		}
		else {
			const char ne[4] = {-47, '-', -62, 0};
			const char se[4] = {-34, '-', -62, 0};
			const char sw[4] = {-34, '-', -57, 0};
			const char nw[4] = {-47, '-', -57, 0};

			if (!strcmp(cur_dir, ne)) {
				dir[NE] = 1;
			}
			else if (!strcmp(cur_dir, se)) {
				dir[SE] = 1;
			}
			else if (!strcmp(cur_dir, sw)) {
				dir[SW] = 1;
			}
			else if (!strcmp(cur_dir, nw)) {
				dir[NW] = 1;
			}
			else {
				fprintf(stderr, "Incorrect direction input format\nLine - %u", str_num);
				exit(1);
			}
		}
		if (str[*i] == ',')
			(*i) += 2;
		len = 0;
	}
	return;
}

void StrToWeather(char str[], unsigned str_num, WeatherData* weather_data) {
	WeatherToZero(weather_data);
	
	unsigned short i = 0;

	GetDate(&(weather_data->date), str, str_num, &i);

	GetTemperature(&(weather_data->night_temp), str, str_num, &i);
	GetTemperature(&(weather_data->day_temp), str, str_num, &i);
	GetTemperature(&(weather_data->perceived_temp), str, str_num, &i);

	GetPrecipitation(weather_data->precipitation, str, str_num, &i);
	if (weather_data->precipitation[0]) {
		DashSkip(str, &i);
		while (str[i] >= '0' && str[i] <= '9')
			weather_data->precipitation_amount = weather_data->precipitation_amount * 10 + str[i++] - '0';
		if (weather_data->precipitation_amount == 0 || (str[i] != ' ' && str[i] != '\t')) {
			fprintf(stderr, "Incorrect precipitation amount input format\nLine - %u", str_num);
			exit(1);
		}
	}

	GetWindSpeed(&(weather_data->wind_data.min_speed), &(weather_data->wind_data.max_speed), str, str_num, &i);
	GetDir(weather_data->wind_data.directions, str, str_num, &i);
	GetWindSpeed(&(weather_data->wind_data.min_gusts), &(weather_data->wind_data.max_gusts), str, str_num, &i);

	DashSkip(str, &i);
	for (; str[i] != ' ' && str[i] != '\t'; ++i) {
		if (str[i] < '0' || str[i] > '9') {
			fprintf(stderr, "Incorrect pressure input format\nLine - %u", str_num);
			exit(1);
		}
		weather_data->pressure = weather_data->pressure * 10 + str[i] - '0';
	}

	DashSkip(str, &i);
	int k = 0;
	
	while (str[i] != '\n') {
		int j = 0;
		while (str[i] != ' ' && str[i] != '\n' && str[i]!=',') {
				if ((str[i] < -32 || str[i] > -1) && str[i] != -72) {
					fprintf(stderr, "Incorrect precipitation input format\nLine - %u", str_num);
					exit(1);
				}
				weather_data->event[k][j] = str[i];
			++i;
			++j;
		}
		if (str[i] == ',')
			++i;
		++k;
		DashSkip(str, &i);
	}
	k = 0;
	char events[events_quan][string_len] = { "торнадо\0", "гроза\0", "туман\0", "гололедица\0" };
	while (weather_data->event[k][0]) {
		unsigned short isEvent = 0;
		for (int i = 0; i < events_quan && !isEvent; ++i) {
			if (!strcmp(events[i], weather_data->event[k]))
				isEvent = 1;
		}
		if (!isEvent) {
			setlocale(LC_ALL, "Russian");
			fprintf(stderr, "The program does not process such an event: <%s>\nLine - %u", weather_data->event[k], str_num);
			exit(1);
		}
		++k;
	}

	return;
}

void Get_WeatherData(WeatherData* weather_data, FILE* f, Date date) {
	char str[text_len] = { 0 };
	Date cur_date = { 0, 0, 0 };
	unsigned str_num = 2;
	fgets(str, text_len, f);

	unsigned short is_this_date = 0;
	while (!is_this_date && fgets(str, text_len, f)) {
		unsigned short i = 0;

		GetDate(&cur_date, str, str_num, &i);

		is_this_date = (cur_date.day == date.day &&
						cur_date.month == date.month &&
						cur_date.year == date.year);
		++str_num;
	}

	if (!is_this_date) {
		fprintf(stderr, "Mistake. There is no such date in the file");
		exit(1);
	}

	--str_num;
	StrToWeather(str, str_num, weather_data);
	return;
}

unsigned short EventsQuan(WeatherData* weather_data) {
	unsigned short int i = 0;
	while (weather_data->event[i++][0]);
	--i;
	return i;
}
#endif
