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


	//open file
	FILE* file = NULL;
	if (openFile(&file, READ, FILENAME) == EXIT_FAILURE)
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
		int itemsRead = fread(&nextCharacter, 1, 1, file);
		//if its e, it needs to wait for an end time to be entered
		if (nextCharacter == STARTEND_DELIMITER || itemsRead != 1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, WARNING_TITLE, "File needs current entry to be finished\nin order to read entrys", NULL);
			errorOccured = true;
			goto cleanup;
		}
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, "File is Empty", NULL);
		errorOccured = true;
		goto cleanup;
	}
	//return to the start
	fseek(file, 0, SEEK_SET);
	
	char line[LINE_SIZE] = { 0 };
	int lineCount = 0;
	int totalTime = 0;
	do
	{
		lineCount++;
		//check that a line was imported
		if (fscanf(file, "%[^\n]\n", line) != 1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, strerror(errno), NULL);
			errorOccured = true;
			goto cleanup;
		}
		int startDay;
		int startMonth;
		int startYear;
		int startHour;
		int startMinute;
		int endDay;
		int endMonth;
		int endYear;
		int endHour;
		int endMinute;

		//parse the line
		int itemCount = sscanf(line, "Start |%d/%d/%d|%d:%d|~End |%d/%d/%d|%d:%d|\n", &startDay, &startMonth, &startYear, &startHour, &startMinute, &endDay, &endMonth, &endYear, &endHour, &endMinute);
		//check that all items were successfully parsed
		if (itemCount != 10)
		{
			//create a dynamic error message
			char errorMsg[ERROR_SIZE] = { 0 };
			snprintf(errorMsg, ERROR_SIZE - 1, "Could not parse all ten values from line %d", lineCount);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, errorMsg, NULL);
			errorOccured = true;
			goto cleanup;
		}
		totalTime += getTimeDelta(startDay, startMonth, startYear, startHour, startMinute, endDay, endMonth, endYear, endHour, endMinute);
	}while(!feof(file));

	//get the hour and minute totals
	int deltaHour = 0;
	int deltaMinute = 0;
	getMinutesAndHoursFromSeconds(totalTime, &deltaHour, &deltaMinute);

	//display the info
	char totalTimeMessage[MESSAGE_SIZE] = { 0 };
	snprintf(totalTimeMessage, MESSAGE_SIZE - 1, "Total Time(hh/mm):\n%d:%d\nNumber of Entrys: %d", deltaHour, deltaMinute, lineCount);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Time Tracked", totalTimeMessage, NULL);


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