#include "shared.h"


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
	if (openFile(&file, APPEND, FILENAME) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}



	//check if last character is e to know if program should abort

	//check if file is empty
	fseek(file, 0, SEEK_END);
	if (ftell(file) != 0)
	{
		//if not, go the the second last position
		fseek(file, -1, SEEK_END);
		char nextCharacter[TIME_SIZES];
		//read the last character
		fread(nextCharacter, 1, 1, file);
		//if its e, it needs to wait for an end time to be entered
		if (*nextCharacter == 'e')
		{
			fprintf(file, "e");
			printf("File needs entry end\n");
			return(EXIT_FAILURE);
		}
		else
		{
			fprintf(file, nextCharacter);
		}
	}

	//return to the end to append
	fseek(file, 0, SEEK_END);

	//create strings
	char date[TIME_SIZES] = { 0 };
	sprintf(date, "%d/%d/%d", day, month, year);
	char timeVar[TIME_SIZES] = { 0 };
	sprintf(timeVar, "%d:%d", hour, minute);
	char entry[ENTRY_SIZE] = { 0 };
	//add e to the end to indicate that an end entry must be submitted
	sprintf(entry, "Date %s%s%s Start %s%s%se", DELIMITER, date, DELIMITER, DELIMITER, timeVar, DELIMITER);

	//write to file
	fprintf(file, "%s", entry);
	printf(entry);

	//close file
	if (fclose(file) == EOF)
	{
		printErrno();
		perror("Error closing file: ");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



