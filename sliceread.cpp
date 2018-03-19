#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <string>
#include <sstream>

using namespace std ;
int main(int argc, char *argv[])
{

int VOL = atoi(argv[2]);
int data[VOL]; 
ifstream input(argv[1]);  // Configuration File //
string line;
int count = 0; 
int start = 0  ; 

ofstream myfile;
myfile.open ("slice_read.dat", ios::out | ios::app | ios::binary);

while(getline(input, line)) {     // Read one line
istringstream iss(line); // Access line as a stream
iss >> data[count] ; // No need to read further
    
if (data[0] == 0){   // If it starts at 0  
myfile << data[count] << " " << (start) << endl ;
count += 1  ; 
start += 1  ; }

else if (data[0] !=0){ // If it does not start at 0 
myfile << data[count] << " " << (start)+data[0] << endl ;
count += 1  ; 
start += 1  ;
}

else{
continue;
}
}
    
return 0;
}
