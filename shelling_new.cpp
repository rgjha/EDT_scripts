// March 21, 2018
// Written in desperation to speed things up.
// Speed of at least ~ 100x from old 2015 code.
// Shells for 16k lattice in less than a second.

// Equivalent to what driver + update + test did.

#include <iostream>
#include <fstream>
#include <random>
#include <vector> 
#include <algorithm> // For sort ()
#include <map>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <cstdio>
#include <list>
#include <set>
#include <limits>


# define VOL 8000    // Define N4inf volume here. Can pass as argument eventually.
# define ORIGIN_SOURCES 5

int data[VOL][6] ;
int BALL[VOL] = {0};
int Seed, TOP;
int head_node;
int total_count, partial_count;


using namespace std ;

vector<int> row ;
vector<int> ROW ;
vector<int> makeVector(int);
vector<int> vect;
vector<int> vectmp;
vector<int> vec_maxima;


  


// --------------------------------------------
void loadfile(){
ifstream input("config_new.dat");
// Configuration File //
// Just has N4 inf enteries.

for (int i = 0; i < VOL ; i++){
    for (int j = 0 ; j < 6 ; j++){
    input >> data[i][j];
    }
}
}
// --------------------------------------------



// --------------------------------------------
vector<int> makeVector(int aNumber){
vector<int> aVector;
row.clear();

for (int j = 0 ; j < 6 ; j++){
row.push_back (int(data[aNumber][j]));
}
    
sort(row.begin(), row.end());   // Could use "set" as well.
row.erase( unique( row.begin(), row.end() ), row.end() );
return row;
}


// --------------------------------------------

void update_begin() {
// First update is special
Seed = head_node;
vectmp = makeVector(Seed);
}

// --------------------------------------------




// --------------------------------------------

void update() {
    
ofstream myfile;
myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
    
for (std::vector<int>::iterator it = vectmp.begin()+1 ; it != vectmp.end(); ++it){
                
    if (BALL[*it] != 1) {
    myfile << *it << " "  ;
    vect.push_back (*it);
    }
                
    else {
    continue;
    }
                
    BALL[*it] = 1;
    
}

myfile << endl ;
int a = vect.size();
int b = vectmp.size();

if (b > TOP){
TOP = b ;
vec_maxima = vectmp; // Keep the peak here
}

partial_count = b ;
        
for (int i=0 ; i < a; i++){
vectmp = makeVector(vect[i]);
vect.insert(vect.end(), vectmp.begin(), vectmp.end());
}
    
vectmp.clear(); 
vectmp = vect;
vect.clear();

}

// --------------------------------------------


// --------------------------------------------
// If the file 'origin' exists, we will do usual stuff
// otherwise we need to select a dummy origin for selecting 5
int main ( int argc, char* argv[] ) {
 
    loadfile();
    FILE* fp = fopen("Origin.dat", "r");
    ofstream myfile;
    ofstream myfile2;
    myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
    
    if (fp) {
    
    fclose(fp);

    ofstream myfile;
    head_node = atoi(argv[0])  ;
    BALL[head_node] = 1;
    myfile << head_node << endl ;
    update_begin();
    
    while (total_count < VOL ){
        total_count = std::count(&BALL[0], &BALL[VOL], 1);
        update();
    }
    
    }
    

    else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, VOL);
        int head_node = data[dis(gen)][0];
        cout << "Random seed is --> " << head_node << endl ;
        
        BALL[head_node] = 1;
        myfile << head_node << endl ;
        
        
        update_begin();
        
        while (total_count < VOL ){
        total_count = std::count(&BALL[0], &BALL[VOL], 1);
        update();
        }
        
        // Pick five (origins) random 4-simplices from vec_maxima.
        
        myfile2.open ("Origin.dat", ios::out | ios::app | ios::binary);
        for (int i = 0 ; i < ORIGIN_SOURCES ; i++){
        int RandIndex = rand() % TOP;
        int D = vec_maxima[RandIndex];
        myfile2 << D << endl;
        }
        myfile2.close();

    }
    
myfile.close();
return 0 ;
}
