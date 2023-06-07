#ifndef DIS_H
#define DIS_H

#include "headers.h"
#include "global.h"

int find_arguments(int* dflag, int* fflag, int* num_of_dir, char directory[], char filename[]);
int search(char temp[], char path[], int* dflag, int* fflag, int check, char filename[]);
void discover();

#endif