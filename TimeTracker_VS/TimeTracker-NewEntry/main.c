#include "../Shared/shared.h"




int main(void)
{
	//get current time
	time_t currentTimeSeconds = time(NULL);
	struct tm* timeStruct = localtime(&currentTimeSeconds);

	int day;
	int month;
	int year;
	int hour;
	int minute;

	getTimeVariables(&day, &month, &year, &hour, &minute, timeStruct);

	//open file
	FILE* file = NULL;
	if (openFile(file, APPEND, FILENAME) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	//create string


	//write to file


	//close file
	errno = 0;
	fclose(file);
	if (errno != 0)
	{
		perror("Errno closing file:\n");
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}



