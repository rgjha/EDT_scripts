/* This part prepares the wall source for
 matrix inversion */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <cstdio>

using namespace std;
int a ; 
int nol = 0;

int main(int argc, char *argv[]){

ofstream myfile ;
ifstream input(argv[1]);
myfile.open ("delta_sources", ios::out | ios::app | ios::binary); 
       
string line;
for (int i = 1 ; i < 4 ; i++){

// Set i < 2 for point source, i < 4 means
// that we smear until 3rd hop (wall source)
    
std::getline(input, line);
istringstream fin(line);

while( fin >> a ){
myfile << a << endl ;
nol++; 
}
}
myfile << a << endl ; 

// Add this last simplex again because of the error in the executable 
// where it runs from 0 to count-1 rather than count !!!
// Checked with Judah's output --> March 10 2018

cout << "Number of simplices in the wall source is :  " << nol << endl ;

myfile.close();

return 0;
}
