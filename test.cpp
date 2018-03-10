#include "utilities.h"

using namespace std;

void test(){

ofstream myfile ;

simplex.assign(0,0);
maxima.assign(0,0) ;
string line;

ifstream input1("MST.dat");

while(!input1.eof()){

C = 0 ;
std::getline(input1, line);
istringstream fin(line);


while( fin >> a){
C += 1;
}

maxima.push_back(C); }

int TOP ;
TOP = *max_element(maxima.begin(), maxima.end());
cout << "Max is :: " << TOP << endl ;

input1.clear();
input1.seekg(0, ios::beg); // Move buffer to start // 

while(!input1.eof()){

std::getline(input1, line);
C = 0;
istringstream fin2(line);

while( fin2 >> b){
C+= 1 ;
C_total +=1;
simplex.push_back(b);
}

myfile.open ("Origin.dat", ios::out | ios::app | ios::binary);

if(C == TOP){
random_device seed ;
mt19937 engine(seed( )) ;
cout << "NUMBER OF ORIGINS IS : " << ORIGIN_SOURCES << endl ; 
for (i = 0 ; i < ORIGIN_SOURCES ; i++){
uniform_int_distribution<int> choose(0 , TOP) ;
D = simplex[(C_total - TOP) + choose( engine )];
if (D==0){
D = simplex[(C_total - TOP) + choose( engine )];
myfile << D << endl ;
cout << "Random 4-simplex picked : " << D << endl ;}
else{
cout << "Random 4-simplex picked : " << D << endl ;
myfile << D << endl ;}}
}
    
myfile.close();

}
return;
}
