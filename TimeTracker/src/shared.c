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
	*hour = (timeStruct->tm_hour) + 1;
	*minute = (timeStruct->tm_min) + 1;
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
		printErrno();
		perror("Error opening file: ");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/// <summary>
/// prints the int value of errno with a trailing space
/// </summary>
/// <param name=""></param>
void printErrno(void)
{
	printf("%d ", errno);
}