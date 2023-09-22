#ifndef WeatherPriorityDataDefined _
#define WeatherPriorityDataDefined _

typedef enum  { _Precipitation, _Temperature, _Wind, _Pressure, _Event, None } WeatherPriority;
typedef enum  {RAIN, SNOW, HAIL, RAINSTORM, SNOWSTORM} _PrecipitationValue;
typedef enum  {LOW_TEMPERATURE, HIGH_TEMPERATURE} _TemperatureValue;
typedef enum  {LOW_PRESSURE, HIGH_PRESSURE} _PressureValue;
typedef enum  { _N, _NE, _E, _SE, _S, _SW, _W, _NW } _WindValue;

typedef struct {
	unsigned day;
	unsigned month;
	unsigned year;
} _Date;

typedef struct {
	_PrecipitationValue prepValue;
	_TemperatureValue tempValue;
	_WindValue windValue;
	_PressureValue presValue;
	char** events;
	_Date date;
} WeatherPriorityData;
#endif 