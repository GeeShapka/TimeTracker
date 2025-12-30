#pragma once
#pragma warning( disable : 4996 )
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


#define APPEND "a"
#define READ "r"

#define FILENAME "TimeTracker.tt"

#define DELIMITER "|"

#define ENTRY_SIZE 150

void getTimeVariables(int*, int*, int*, int*, int*, struct tm*);
int openFile(FILE*, const char*, const char*);