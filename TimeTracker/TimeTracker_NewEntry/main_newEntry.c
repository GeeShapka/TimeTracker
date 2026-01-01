#include "shared.h"


int main(void)
{
	bool errorOccured = false;
	bool sdlOpen = false;
	bool fileOpen = false;


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, SDL_GetError(), NULL);
		return EXIT_FAILURE;
	}
	sdlOpen = true;

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
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, strerror(errno), NULL);
		errorOccured = true;
		goto cleanup;
	}
	fileOpen = true;


	//check if last character is e to know if program should abort

	//check if file is empty
	fseek(file, 0, SEEK_END);
	if (ftell(file) != 0)
	{
		char nextCharacter = '\0';
		//if not empty, go the the second last position
		fseek(file, -1, SEEK_END);
		//read the last character
		fread(&nextCharacter, 1, 1, file);
		//if its e, it needs to wait for an end time to be entered
		if (nextCharacter == STARTEND_DELIMITER)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, WARNING_TITLE, "File needs current entry to be finished\nin order to create a new entry", NULL);
			errorOccured = true;
			goto cleanup;
		}
	}

	//return to the end to append
	fseek(file, 0, SEEK_END);

	//create strings
	char date[TIME_SIZES] = { 0 };
	snprintf(date, TIME_SIZES, "%d/%d/%d", day, month, year);
	char timeVar[TIME_SIZES] = { 0 };
	snprintf(timeVar, TIME_SIZES, "%d:%d", hour, minute);
	char entry[ENTRY_SIZE] = { 0 };
	//add seperate delimiter to the end to indicate that an end entry must be submitted
	snprintf(entry, ENTRY_SIZE, "Start %c%s%c%s%c%c", DELIMITER, date, DELIMITER, timeVar, DELIMITER, STARTEND_DELIMITER);

	//write to file
	fprintf(file, "%s", entry);

cleanup:
	//close file
	if (fileOpen == true)
	{
		if (fclose(file) == EOF)
		{
			//printErrnoNumber();
			//perror("Error closing file: ");
			//sdl might not be open, so check if it is
			if (sdlOpen)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, strerror(errno), NULL);
			}
			errorOccured = true;
		}
	}
	//close sdl
	if (sdlOpen)
	{
		SDL_Quit();
	}
	if (errorOccured)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

