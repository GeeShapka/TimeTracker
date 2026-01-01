#include "shared.h"


/// <summary>
/// Gets variables out of the tm struct
/// </summary>
/// <param name="day"></param>
/// <param name="month"></param>
/// <param name="year"></param>
/// <param name="hour"></param>
/// <param name="minute"></param>
/// <param name="timeStruct"></param>
void getTimeVariables(int* day, int* month, int* year, int* hour, int* minute, struct tm* timeStruct)
{
	*day = timeStruct->tm_mday;
	*month = (timeStruct->tm_mon) + 1;
	*year = (timeStruct->tm_year) + 1900;
	*hour = (timeStruct->tm_hour);
	*minute = (timeStruct->tm_min);
	return;
}

/// <summary>
/// opens a file
/// </summary>
/// <param name="file"></param>
/// <param name="method"></param>
/// <param name="fileName"></param>
/// <returns>1 on falure, 0 on success</returns>
int openFile(FILE** file, const char* method, const char* fileName)
{
	*file = fopen(fileName, method);
	if (*file == NULL)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/// <summary>
/// prints the int value of errno with a trailing space
/// </summary>
/// <param name=""></param>
void printErrnoNumber(void)
{
	//printf("%d ", errno);
}

/// <summary>
/// gets and returns the difference between two dates in seconds
/// </summary>
/// <param name="sDay"></param>
/// <param name="sMonth"></param>
/// <param name="sYear"></param>
/// <param name="sHour"></param>
/// <param name="sMinute"></param>
/// <param name="eDay"></param>
/// <param name="eMonth"></param>
/// <param name="eYear"></param>
/// <param name="eHour"></param>
/// <param name="eMinute"></param>
/// <returns></returns>
int getTimeDelta(int sDay, int sMonth, int sYear, int sHour, int sMinute, int eDay, int eMonth, int eYear, int eHour, int eMinute)
{
	struct tm sTimeStruct;
	sTimeStruct.tm_mday = sDay;
	sTimeStruct.tm_mon = sMonth - 1;
	sTimeStruct.tm_year = sYear - 1900;
	sTimeStruct.tm_hour = sHour;
	sTimeStruct.tm_min = sMinute;

	struct tm eTimeStruct;
	eTimeStruct.tm_mday = eDay;
	eTimeStruct.tm_mon = eMonth - 1;
	eTimeStruct.tm_year = eYear - 1900;
	eTimeStruct.tm_hour = eHour;
	eTimeStruct.tm_min = eMinute;

	time_t sTime = mktime(&sTimeStruct);
	time_t eTime = mktime(&eTimeStruct);

	double deltaTime = difftime(eTime, sTime);
	return (int)deltaTime;
}

/// <summary>
/// takes a number of seconds and extracts the hours and minutes from it
/// </summary>
/// <param name="seconds"></param>
/// <param name="minutes">variable to hold minute value</param>
/// <param name="hours">variable to hold hour value</param>
void getMinutesAndHoursFromSeconds(int seconds, int* hours, int* minutes)
{
	*hours = seconds / 3600;
	*minutes = ((seconds % 3600) / 60);
}