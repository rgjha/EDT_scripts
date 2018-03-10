#ifndef UTILITIES_H
#define UTILITIES_H
 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <string>
#include <sstream>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>
#include <set>
#include <limits>


using namespace std;
# define VOL 8000
# define ORIGIN_SOURCES 5


extern int i, j, k, p, count_integer, timeslice, size ;
extern int a, b, C_total, A, B, C, D, E, F, G, H, ORIGIN;
extern int data[VOL][6];
extern int SeedArr[5];
extern double TOP;
extern vector<int> simplex ;
extern vector<int>::iterator it;
extern vector<double> maxima;


#endif
