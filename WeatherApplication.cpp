#include "WeatherPriorityCalculator.h"
#include "dictionary.h"
#include "Weather_pattern_selector.h"
#include "Weather_pattern_definer.h"
#define MAX_FILE_SIZE 10000
#define MAX_STRING_SIZE 1000

void printResult(char * str) {
	char result[MAX_FILE_SIZE] = {0};
	int op = 0;
	char curTag[256] = {0};
	for (int u = 0; u < sizeof(*str); u++) {
		if (str[u] == '>') {
			op = 0;
			strcat(result, getWord(curTag));
			for (int y = 0; y < 256; y++) {
				curTag[y] = 0;
			}
		}else
		if (op) {
			strcat(curTag, str[u]);
		}else
		if (str[u] == '<')
			op = 1;
		else {
			strcat(result, str[u]);
		}
	}
	printf("%s\n", result);
}

int main() {

	FILE* file = fopen("input.txt", "r");
	printf("Добро пожаловать в знаменитый центр предсказаний погоды. Вы можете любую опцию из ниже предложенных:\n");
	while (1) {
		printf("Options:\n0. Enter date\n 1. Exit\n");
		int option = 0;
		scanf("%d", &option);
		if (option == 0) {
			WeatherData wdata;
			Date date = { 0,0,0 };
			printf("Введите год:\n");
			scanf("%d", &date.year);
			printf("Введите месяц:\n");
			scanf("%d", &date.month);
			printf("Введите день:\n");
			scanf("%d", &date.day);
			printf("Отлично. Ожидайте, Омниссия уже работает над вашим запросом\n\n");
			Get_WeatherData(&wdata, file, date);
			WeatherPriority *priority = CalculatePriotity(&wdata);
			WeatherPriorityData priorityData = FormPriortyData(&wdata, priority);
			Selector(priority, &priorityData);
			Definition(&priorityData);
			FILE* fSpace = fopen("Space_text.txt", "r");
			char* result = malloc(sizeof(char) * MAX_FILE_SIZE);
			for (int u = 0; u < MAX_FILE_SIZE; u++)
			{
				result[u] = 0;
			}
			char* str = malloc(sizeof(char) * MAX_STRING_SIZE);
			int strNum = 0;
			while (fgets(str, MAX_STRING_SIZE, file)) {
				strcat(result, str);
				strNum++;
			}

			printResult(result);
		}
		else if (option == 1) {
			printf("As you wish, see you again next time!\n");
			return 0;
		}
		else {
			printf("I can't believe you did it. Now \n");
		}
	}
}