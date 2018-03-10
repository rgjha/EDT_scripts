#include "utilities.h"

using namespace std; 

void update(){
    
for (int z = 0 ; z < size  ; z++){
    int* arr = simplex.data();

    for(i = 0 ; i < VOL ; i++){
        if(arr[z] == data[i][0]){
            
            for (j = 1 ; j < 6; j++){
            it = find (simplex.begin(), simplex.end(), int(data[i][j]));
                
                if (it != simplex.end()){
                continue;
                }
            
                else{
                simplex.push_back  (int(data[i][j]));
                }
            }
        }

        else{
        continue ;
        }
    }
}

ofstream myfile;
ofstream myfile3;
myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
    
for(vector<int>::const_iterator i = (simplex.begin()+B); i < simplex.end(); i++){
myfile << *i << ' ' ;    
count_integer += 1 ;
}

A = simplex.size() - A;
size = simplex.size();
//cout << " Count : " << simplex.size()  << endl ;
myfile << endl ; 
myfile.close();
B += A ;
return;
}
