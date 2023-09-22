#include "WeatherPriorityCalculator.h"
#include "dictionary.h"
#include "load_dictionary.h"
#include "Weather_pattern_selector.h"
#include "Weather_pattern_definer.h"
#include <locale.h>
#include <math.h>
#define MAX_FILE_SIZE 10000
#define MAX_STRING_SIZE 1000
#include <string.h>

void reverse(char * s)
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
void itoaa(int n, char * s)
{
	int i, sign;

	if ((sign = n) < 0)  
		n = -n;          
	i = 0;
	do {       
		s[i++] = n % 10 + '0';   
	} while ((n /= 10) > 0);     
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
char* GetCharasteristic(WeatherData * wd, char * str) {
	char * buf = (char*)malloc(sizeof(char)*256);
	
	for (int u = 0; u < 256; u++)
		buf[u] = 0;
	if (!strcmp(str, "perc.")) {
		 itoaa(wd->precipitation_amount,buf);
		 return buf;
	}
	if (!strcmp(str, "pressure")) {
		itoaa(wd->pressure, buf);
		return buf;
	}
	if (!strcmp(str, "min_night")) {
		itoaa(wd->night_temp.min, buf);
		return buf;
	}
	if (!strcmp(str, "max_night")) {
		itoaa(wd->night_temp.max, buf);
		return buf;
	}
	if (!strcmp(str, "min_day")) {
		itoaa(wd->day_temp.min, buf);
		return buf;
	}
	if (!strcmp(str, "max_day")) {
		itoaa(wd->day_temp.max, buf);
		return buf;
	}
	if (!strcmp(str, "min_perc.")) {
		itoaa(wd->perceived_temp.min, buf);
		return buf;
	}
	if (!strcmp(str, "max_perc.")) {
		itoaa(wd->perceived_temp.max, buf);
		return buf;
	}
	if (!strcmp(str, "speed")) {
		itoaa(wd->wind_data.max_speed, buf);
		return buf;
	}
	if (!strcmp(str, "max_gusts")) {
		itoaa(wd->wind_data.max_gusts, buf);
		return buf;
	}
}

char* ParseResult(char str[], WeatherData data) {
	char result[MAX_FILE_SIZE+1] = {0};
	int op = 0, sop = 0;

	char * curTag = malloc (sizeof(char)*30);
	for (int y = 0; y < 30; y++)
		curTag[y] = 0;
	char curTag2[30] = {0};
	for (int u = 0; u < MAX_FILE_SIZE; u++) {
		if (str[u] == '>') {
			op = 0;

			strcat(result, getWord(curTag));
			for (int y = 0; y < 30; y++) {
				curTag[y] = 0;
			}
		}
		else if (str[u] == '/') {
			sop = abs(sop-1);
			if (!sop) {
				char* cringe = GetCharasteristic(&data, curTag2);
				strcat(result, cringe);
				for (int y = 0; y < 30; y++) {
					curTag2[y] = 0;
				}
				free(cringe);
			}
		}
		else
		if (op) {
			char da[] = { str[u],0 };
			strcat(curTag, da);
		}
		else if (sop) {
			char da[] = { str[u],0 };
			strcat(curTag2, da);
		}else
		if (str[u] == '<')
			op = 1;
		else {
			char d[] = { str[u], '\0' };
			strcat(result, d);
		}
	}
	return result;
	free(curTag);
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	FILE* file = fopen("input.txt", "r");
	printf("Добро пожаловать в знаменитый центр предсказаний погоды. Вы можете любую опцию из ниже предложенных:\n");
	int p = 0;
	loadDictionary("dictionary.txt");
	while (1) {
		fseek(file, 0, SEEK_SET);
		printf("Опции:\n0. Ввести дату\n1. Закончить исполнение программы\n");
		int option = 0;
		scanf("%d", &option);
		if (option == 0) {
			WeatherData wdata;
			Date date = { 0,0,0 };
			printf("Введите дату в формате дд.мм.гггг:\n");
			scanf("%d.%d.%d", &date.day, &date.month, &date.year);
			printf("Отлично. Ожидайте, deus mechanicus уже работает над вашим запросом\n\n");
			Get_WeatherData(&wdata, file, date);
			WeatherPriority * priority = CalculatePriotity(&wdata);
			WeatherPriorityData priorityData = FormPriortyData(&wdata, priority);
			Selector(priority, &priorityData);
			Definition(&priorityData, p);
			p = 1;
			FILE* fSpace = fopen("Space_text.txt", "r");
			char result [MAX_FILE_SIZE];
			for (int u = 0; u < MAX_FILE_SIZE; u++)
			{
				result[u] = 0;
			}
			char* str = malloc(sizeof(char) * MAX_STRING_SIZE);
			int strNum = 0;
			while (fgets(str, MAX_STRING_SIZE, fSpace)) {
				strcat(result, str);
				strNum++;
			}
			free(str);
			char* jeez = ParseResult(result, wdata);
			FILE* filee = fopen("output.txt", "wb");
			fprintf(filee,"%s",jeez);
			fclose(fSpace);
			fclose(filee);
			printf("Уже готово. Результаты можно найти в файле output.txt\n");
		}
		else if (option == 1) {
			return 0;
		}
		else {
			printf("Я не понимаю такую команду\n");
		}
	}
}