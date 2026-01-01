#pragma once
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#define SDL_MAIN_HANDLED
#include "SDL3/SDL.h"


#define APPEND "a+"
#define READ "r"

#define FILENAME "TimeTracker.txt"

#define DELIMITER '|'
#define STARTEND_DELIMITER '~'

#define ERROR_TITLE "Error"
#define WARNING_TITLE "Warning"

#define ENTRY_SIZE 150
#define TIME_SIZES 20
#define LINE_SIZE 50
#define ERROR_SIZE 100
#define MESSAGE_SIZE 100

void getTimeVariables(int*, int*, int*, int*, int*, struct tm*);
int openFile(FILE**, const char*, const char*);
void printErrnoNumber(void);
int getTimeDelta(int, int, int, int, int, int, int, int, int, int);
void getMinutesAndHoursFromSeconds(int, int*, int*);