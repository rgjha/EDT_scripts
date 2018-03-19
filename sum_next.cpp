/* This code reads the scalar-propagator file and then averages 
on the basis of geodesic distance from the smeared sources. It does
so until the nth (here, 4th) located smeared source. 
Nov 19, 2015 */ 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <string>

# define NUM 100      // r_max --> 100 
double data[NUM*2]; 
using namespace std;

int main(int argc, char *argv[])
{
ofstream myfile ;
ifstream input(argv[1]);  // Run as g++ -o exec sum_next.cpp, .exec FILENAME //
    
for (int i = 1; i <= (NUM*2); i++){
input >> data[i];              // Read Data at once from Configuration file //
}
    
for (int i = 1 ; i <= NUM*2 ; i++){
ofstream myfile;
        
if (i > 5 && i%2 != 0){  // Start at 5th becase that's one hop away from smeared source // 
myfile.open ("new.dat", ios::out | ios::app | ios::binary); 
if (data[i+1] != 0)
{
myfile << ((data[i]/data[i+1])) << endl ; 
}
 
else {
}
             
}
}
    
myfile.close();
return 0;
}
