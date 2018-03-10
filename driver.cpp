/* The main shelling code (Minimum spanning tree [MST]) code
for EDT analysis. Need to pass the trimmed (after bash) configuration
file with an argument which is the seed. If the origins are unknown
i.e Origin.dat doesn't exist then the argument is replaced with a random 
number between 0 and N4inf 
*/ 

#include "utilities.h"
#include "update.h" 
#include "test.h" 

int i, j, k, p, count_integer, timeslice, size ;
int a, b, C_total, A, B, C, D, E, F, G, H, ORIGIN;
int data[VOL][6] ;
int SeedArr[5];
double TOP ;
vector<int> simplex ;
vector<int>::iterator it;
vector<double> maxima ;

using namespace std;

int main( int argc, char* argv[] ){
    
ofstream myfile ;
simplex.assign(0,0);         // Assign a Simplex //
ifstream input("config.dat");  // Configuration File //
maxima.assign(0,0) ;
    
    
for (i = 0; i < VOL; i++){
    for (j = 0 ; j < 6 ; j++){
    input >> data[i][j];    // Read Data at once from Configuration file //
    }
}
    
    
    FILE* fp = fopen("Origin.dat", "r");
    if (fp) {
        
        fclose(fp);
        cout << "We can proceed since the file EXISTS and we have five distinct origins, we will now shell !" << endl ;
        ofstream myfile;
        
        int Seed = atoi(argv[1])  ;
        cout << "New origin is : " << Seed << endl ;
                
                
        for ( i = 0 ; i < VOL ; i ++){
            
            if (data[i][0] == Seed){
                simplex.push_back(Seed);
                myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
                myfile << Seed << ' ' ; // Print the seed to start the shelling MST file //
                myfile << endl ;
                myfile.close();
                        
                for (j = 1 ; j<6 ; j++){
                    it = find (simplex.begin(), simplex.end(), int(data[i][j]));
                    
                    if (it != simplex.end()){
                    continue;
                    }
                    else{
                    simplex.push_back (int(data[i][j]));
                    }
                }
            }
                    
            
            else{
            continue; 
            }

        }
                 
        myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
        
        for(vector<int>::const_iterator i = simplex.begin()+1; i < simplex.end(); i++) {

        myfile << *i << ' ' ;
        }
                
        myfile << endl ;
        myfile.close();
                
                
        size = simplex.size();
        while (simplex.size() < VOL){
            A = simplex.size();
            B = A  ;
            update();
            timeslice++ ;     
        }
    }
                    
    
    else {

    cout << "We will have to do a dummy test now since Origin.dat does not exist ! " << endl ;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, VOL);
    int Seed = data[dis(gen)][0];
    cout << "Random seed is :: " << Seed << endl ;
            
    for ( i = 0 ; i < VOL ; i ++){
                
        if (data[i][0] == Seed){
        simplex.push_back(Seed);
        myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
                    
            for(vector<int>::const_iterator i = simplex.begin(); i < simplex.end(); i++){
            myfile << *i << ' ' ;   // Print the contents of Simplex //
            }
                    
            myfile << endl ;
            myfile.close();
                    
                    
            for (j = 1 ; j<6 ; j++){
            it = find (simplex.begin(), simplex.end(), int(data[i][j]));
                        
            if (it != simplex.end()){
                            
            continue;
                            
            }
                        
            else{
                            
            simplex.push_back (int(data[i][j]));
            }
            }
        }
                
        else
        {
        continue; 
        }
                            
    }
            
            
    myfile.open ("MST.dat", ios::out | ios::app | ios::binary);
            
            
    for(vector<int>::const_iterator i = simplex.begin()+1; i < simplex.end(); i++) {
    myfile << *i << ' ' ;
    }
            
    myfile << endl ;
    myfile.close();
            
            
    size = simplex.size();
    while (simplex.size() < VOL){
        A = simplex.size();
        B = A  ;
        update();
        timeslice++ ;
    }
            
    test();


    }

return 0;
} 
