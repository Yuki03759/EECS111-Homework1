#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>


#include "p1_threads.h"

void read_file(std::string filename);
void write_file(std::string filename);
void get_statistics(std::string class_name[], int num_processes, int num_threads);


#endif
