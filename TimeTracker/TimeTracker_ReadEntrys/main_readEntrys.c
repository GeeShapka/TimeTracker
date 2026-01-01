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
	int deltaHour;
	int deltaMinute;
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