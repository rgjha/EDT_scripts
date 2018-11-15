// Code by Scott Bassler. Goes from combinatorial lattice to the 
// degenerate one. Not checked. 

#include "/home/sdbassle/edt/ChrisSpect/Lib3/Fit/JFit.h"
#include "/home/sdbassle/edt/ChrisSpect/Lib3/Templates/ValArray.h"
#include "/home/sdbassle/edt/ChrisSpect/Lib3/Utils/Io.h"
#include "/home/sdbassle/edt/ChrisSpect/Lib3/JackStuff/ran2.h"
#include "/home/sdbassle/edt/ChrisSpect/Lib3/JackStuff/Output_4DE.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "/home/sdbassle/edt/ChrisSpect/Lib3/JackStuff/EuclidComb2/moveEcomb2.h"
#include "/home/sdbassle/edt_bare/dyntri/4dstuff/Euclid/ChrisSpect/Lib3/Utils/Error.h"

using namespace std;

int main(int argc, char* argv[]) 

{ 
  string filedumb="dump"; 
  infile input(filedumb);

  int N4ct;
  int N0ct;
  double k4;
  int stack;
  int dumbint;
  double dumbdoub;

  input >> N4ct;     input >> N0ct;  input >> stack; 
  input >> dumbdoub; input >> k4; input >> dumbdoub;
 

  for(int i=3;i<stack+3;i++)    
    {
      input >> dumbint;
    }
    
    
    // N4 : Node of a simplex (5)
    // N4inf : Simplex neighbor of simplex (5)

  ValArray<int> N4(5*N4ct);
  ValArray<int> N4inf(5*N4ct);

  for(int i=0;i<N4ct;i++)
    {
      for(int j=0;j<5;j++)
	{
	  input >> dumbint;
	  N4[5*i+j]=dumbint;
	  input >> dumbint;
	  N4inf[5*i+j]=dumbint;
	}
    }

  int Dsub;
  bool news;
  int dumbN4;
  int dumbcheck;
  int Nct;

  // Making N1 and N14 //
    // N14 : Link of a simplex
    // N1 : Link

  int N1ct=0;
  ValArray<int> N1(10*N4ct);  
  ValArray<int> N14(10*N4ct);  
  Dsub=1;  
  
  Nct=0;
  for(int i=0;i<N4ct;i++)
    {
      dumbN4=0;
      for(int j=0;j<5;j++)
	{
	  for(int k=j+1;k<5;k++)
	    {
	      news=true;
	      //Nodes are N4[5*i+j] and N4[5*i+k]
	      for(int q=0;q<Nct;q++)
		{
		  dumbcheck=0;
		  for(int r=0;r<Dsub+1;r++)
		    {
		      if(N1[2*q+r]==N4[5*i+j] ||
			 N1[2*q+r]==N4[5*i+k])
			{
			  dumbcheck++;
			}
		    }
		  if(dumbcheck==Dsub+1)
		    {
		      news=false;
		      dumbint=q;
		      q=Nct;
		      }
		}
	      if(news)
		{
		  dumbint=Nct;
		  N1[2*Nct+0]=N4[5*i+j]; N1[2*Nct+1]=N4[5*i+k];
		  Nct++;
		}
	      N14[10*i+dumbN4]=dumbint;
	      dumbN4++;
	    }
	}
    }
  N1ct=Nct;

  // Making N2 and N24 //

  int N2ct=0;
  ValArray<int> N2(3*10*N4ct);   // Every triangle has three nodes
  ValArray<int> N24(10*N4ct);  
  Dsub=2;  
  
  Nct=0;
  for(int i=0;i<N4ct;i++)
    {
      dumbN4=0;
      for(int j=0;j<5;j++)
	{
	  for(int k=j+1;k<5;k++)
	    {
	      for(int l=k+1;l<5;l++)
		{
		  news=true;
		  //Nodes are N4[5*i+j] and N4[5*i+k]
		  for(int q=0;q<Nct;q++)
		    {
		      dumbcheck=0;
		      for(int r=0;r<Dsub+1;r++)
			{
			  if(N2[(Dsub+1)*q+r]==N4[5*i+j] ||
			     N2[(Dsub+1)*q+r]==N4[5*i+k] ||
			     N2[(Dsub+1)*q+r]==N4[5*i+l])
			    {
			      dumbcheck++;
			    }
			}
		      if(dumbcheck==Dsub+1)
			{
			  news=false;
			  dumbint=q;
			  q=Nct;
			}
		    }
		  if(news)
		    {
		      dumbint=Nct;
		      N2[(Dsub+1)*Nct+0]=N4[5*i+j]; 
		      N2[(Dsub+1)*Nct+1]=N4[5*i+k];
		      N2[(Dsub+1)*Nct+2]=N4[5*i+l];
		      Nct++;
		    }
		  N24[10*i+dumbN4]=dumbint;
		  dumbN4++;
		}
	    }
	}
    }
  N2ct=Nct;

  // Making N3 and N34 //
 
  int N3ct=0;
  ValArray<int> N3(4*5*N4ct);  
  ValArray<int> N34(10*N4ct);  
  Dsub=3;  
  
  Nct=0;
  for(int i=0;i<N4ct;i++)
    {
      dumbN4=0;
      for(int j=0;j<5;j++)
	{
	  for(int k=j+1;k<5;k++)
	    {
	      for(int l=k+1;l<5;l++)
		{
		  for(int m=l+1;m<5;m++)
		    {
		      news=true;
		      //Nodes are N4[5*i+j] and N4[5*i+k]
		      for(int q=0;q<Nct;q++)
			{
			  dumbcheck=0;
			  for(int r=0;r<Dsub+1;r++)
			    {
			      if(N3[(Dsub+1)*q+r]==N4[5*i+j] ||
				 N3[(Dsub+1)*q+r]==N4[5*i+k] ||
				 N3[(Dsub+1)*q+r]==N4[5*i+l] ||
				 N3[(Dsub+1)*q+r]==N4[5*i+m])
				{
				  dumbcheck++;
				}
			    }
			  if(dumbcheck==Dsub+1)
			    {
			      news=false;
			      dumbint=q;
			      q=Nct;
			    }
			}
		      if(news)
			{
			  dumbint=Nct;
			  N3[(Dsub+1)*Nct+0]=N4[5*i+j]; 
			  N3[(Dsub+1)*Nct+1]=N4[5*i+k];
			  N3[(Dsub+1)*Nct+2]=N4[5*i+l];
			  N3[(Dsub+1)*Nct+3]=N4[5*i+m];
			  Nct++;
			}
		      N34[5*i+dumbN4]=dumbint;
		      dumbN4++;
		    }
		}
	    }
	}
    }
  N3ct=Nct;

  // Making TriOrder //

  ValArray<int> TriOrder(N2ct);

  for(int i=0;i<N4ct;i++)
    {
      for(int j=0;j<10;j++)
	{
	  TriOrder[N24[10*i+j]]++;
	}
    }

  // Printing // 

  cout<<"k4: "<<k4<<endl;
  cout<<endl;

  cout<<"N0: " << N0ct <<endl;
  cout<<endl;

  cout<<"N4: "<<N4ct<<endl;
  for(int i=0;i<N4ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<5;j++)
	{
	  cout<<N4[5*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N4inf: "<<N4ct<<endl;
  for(int i=0;i<N4ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<5;j++)
	{
	  cout<<N4inf[5*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;


  cout<<"N34: "<<N4ct<<endl;
  for(int i=0;i<N4ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<5;j++)
	{
	  cout<<N34[5*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N24: "<<N4ct<<endl;
  for(int i=0;i<N4ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<10;j++)
	{
	  cout<<N24[10*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N14: "<<N4ct<<endl;
  for(int i=0;i<N4ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<10;j++)
	{
	  cout<<N14[10*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N3: "<<N3ct<<endl;
  for(int i=0;i<N3ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<4;j++)
	{
	  cout<<N3[4*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N2: "<<N2ct<<endl;
  for(int i=0;i<N2ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<3;j++)
	{
	  cout<<N2[3*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"N1: "<<N1ct<<endl;
  for(int i=0;i<N1ct;i++)
    {
      cout<<i<<"  ";
      for(int j=0;j<2;j++)
	{
	  cout<<N1[2*i+j]<<" ";
	}
      cout<<endl;
    }
  cout<<endl;

  cout<<"TriOrder: "<<N2ct<<endl;
  for(int i=0;i<N2ct;i++)
    {
      cout<<i<<"  "<<TriOrder[i]<<endl;
    }

return 0;
}
