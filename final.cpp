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

int a, Count, Cu_Count;
double av, av_g;

using namespace std;

int main(int argc, char *argv[]){
    
int VOL = atoi(argv[3]);
double data[VOL];

ofstream myfile ;
ofstream myfile4;
ofstream myfile5;
    
ifstream input(argv[1]);  // Configuration Relabelling File //
    
for (int i = 0; i < VOL; i++){
input >> data[i];                                // Read Data at once from Configuration file //
}
    
ofstream myfile1;
ifstream input1(argv[2]);                  // Minimum spanning tree input file //
    
while(!input1.eof()){
            
av = 0 ;
av_g = 0; 
Count = 0;
string line;
std::getline(input1, line);
            
istringstream fin(line);
while( fin >> a){
    
Count = Count + 1;
ofstream myfile ;
ifstream input(argv[1]);  // This is solution_vector file //
    
av_g += data[a] ;
}
    
if ( Count > 1 && av_g !=0){
// Eliminate the earlier inclusion of the origin itself by setting Count > 1 //
   
myfile4.open ("prop_data.dat", ios::out | ios::app | ios::binary);
myfile4 << av_g << " " << Count  << endl ;  // G(r)
myfile4.close();

Cu_Count += Count ; }
}
    
myfile1.close();
myfile.close();

return 0;
}
