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
#include <vector>
#include <assert.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <math.h>

#include "p1_threads.h"


using namespace std;

class Node {
    public:
        string studentID;
        double grade;
        
    bool operator < (const Node& node)
    {
        return grade < node.grade ;
    }
};

struct runner_struct {
    int start;
    int end;
    int num_threads;
    int size;
    string filename;
};

vector<Node> merge(struct runner_struct s);
vector<Node> threadSort(vector<Node> array, int num_threads, string filename);
void copy_vector(std::vector<Node> array, std::vector<Node> array2);
void getResult(vector<Node> arr, int arrSize);
void print_vector(vector<Node> arr);
vector<Node> read_file(std::string filename);
void write_file(vector<Node> arr, string filename);
void get_statistics(std::string class_name[], int num_processes, int num_threads);

#endif
