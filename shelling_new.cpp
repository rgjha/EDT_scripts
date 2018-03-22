// March 21, 2018
// Written in desperation to speed things up.
// Speed of at least ~ 100x from old 2015 code.
// Shells for 16k lattice in less than a second.

#include <iostream>
#include <fstream>
#include<vector> 
#include<algorithm>   // For sort ()
#include <map>
# define VOL 15880    // Define N4inf volume here. Can pass as argument eventually.

std::vector<int> row ;
std::vector<int> ROW ;
std::vector<int> makeVector(int);

int data[VOL][6] ;
int BALL[VOL] = {0};
int Seed;
int head_node = 100;
int total_count; 

std::vector<int> vect;
std::vector<int> vectmp;


using namespace std ;  

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
std::vector<int> makeVector(int aNumber){
std::vector<int> aVector;
row.clear();
  for (int j = 0 ; j < 6 ; j++){
    row.push_back (int(data[aNumber][j]));
  }
    
  sort(row.begin(), row.end());
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
    
for (std::vector<int>::iterator it = vectmp.begin()+1 ; it != vectmp.end(); ++it)
{
                
if (BALL[*it] != 1) {
std::cout << *it << " "  ;
vect.push_back (*it);
}
                
else {
continue;
}
                
BALL[*it] = 1;

}
std::cout << '\n';

int a = vect.size();
    
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
int main () {

BALL[head_node] = 1;
std::cout << head_node << endl  ;

    
loadfile();
update_begin();
    
while (total_count < VOL ){

total_count = std::count(&BALL[0], &BALL[VOL], 1);
update();
}

return 0 ;
}
