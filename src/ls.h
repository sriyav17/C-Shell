#ifndef LS_H
#define LS_H

#include "headers.h"
#include "global.h"

int compare(const void* a, const void* b);
void perms(struct stat filestat);
int find_flags_and_dir(int* lflag, int* aflag, int* num_of_dir, char tempdir[][maxsize]);
void ls();

#endif
