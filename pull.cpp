/* This deals with MST file and relabels it properly based on SliceRead stuff */

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

int a;
using namespace std;

int main(int argc, char *argv[]){
int VOL = atoi(argv[3]);
int data[VOL*2]; 

ifstream input(argv[1]); // Configuration Relabelling File //
    
for (int i = 0; i < VOL*2; i++){
input >> data[i]; // Read Data at once from Configuration file //
}
   
ifstream input1(argv[2]); // Minimum spanning tree input file //
        

while(!input1.eof()){
            
string line;
std::getline(input1, line);
istringstream fin(line);
ofstream myfile2;
    
while( fin >> a){

ofstream myfile ;
ifstream input(argv[1]); // Configuration File //
                  
for (int i = 0; i < VOL*2; i++){
                                   
if ( i%2 == 0 && a == data[i]){
                       
ofstream myfile2;
myfile2.open ("MST_new.dat", ios::out | ios::app | ios::binary);
myfile2 << data[i+1] << " " ;
myfile2.close();
                                              
}
}
                
}
    
myfile2.open ("MST_new.dat", ios::out | ios::app | ios::binary);
    
myfile2 << endl ;
myfile2.close();
            
}

return 0;
}
