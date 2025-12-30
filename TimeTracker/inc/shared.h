#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


#define APPEND "a+"
#define READ "r"

#define FILENAME "TimeTracker.txt"

#define DELIMITER "|"

#define ENTRY_SIZE 150
#define TIME_SIZES 20

void getTimeVariables(int*, int*, int*, int*, int*, struct tm*);
int openFile(FILE**, const char*, const char*);
void printErrno(void);