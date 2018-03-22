#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "sparse.h"
#include "cholmod.h"

using namespace std;
void matrix_sqr(ValArray<double> &M, ValArray<double> &Msqr, int N4ct);
void conj_grad(ValArray<double> &M, ValArray<double> &phi, ValArray<double> &Mp, int N4ct, double minRes, int maxIt);

int main(int argc, char *argv[])
{

  int N4max(8000);      // Set double of the N4 volume
  int nConfig(1);
  int initConfig; 
  initConfig = atoi(argv[1]);

  double m(0.125);
  double Ng(1);
  int count(0); 


  long dum=-2;

  string bufferTemp2, bufferTemp3, bufferTemp4, bufferTemp5;

  for(int n(initConfig); n<nConfig+initConfig; n++)
    {
      ostringstream config_num;

      config_num << initConfig;

      bufferTemp3 = argv[2];
      bufferTemp4 = argv[3]; 
      infile input2(bufferTemp3);
      infile input6(bufferTemp5); 

      ValArray<int> SliceRead(N4max);
      ValArray<int> InvSliceRead(N4max);

      ValArray<int> N4inf(5*N4max);

      int N4ct(0);

      input2.find("N4inf:");
      input2 >> N4ct;

      for(int i(0); i<N4ct; i++)
	{
	  input2 >> SliceRead[i];
	  InvSliceRead[SliceRead[i]]=i;

	  for(int j(0); j<5; j++)
	    {input2 >> N4inf[5*SliceRead[i]+j];}

	}
      ValArray<double> val(6*N4ct);
      ValArray<int> row_ind(6*N4ct);
      ValArray<int> col_ptr(6*N4ct);

      int s(0);
      int s2(1);
      for(int i(0); i<N4ct; i++)
	{
	  ValArray<int> stor(5);
	  int s3(0);
	  for(int k(0); k<5; k++)
	    {
	      if(InvSliceRead[N4inf[5*SliceRead[i]+k]]<i)
		{
		  stor[s3]=InvSliceRead[N4inf[5*SliceRead[i]+k]];
		  s3++;
		}
	    }


	  for(int k(0); k<s3; k++)
	    {
	      for(int l(0); l<s3-1; l++)
		{
		  if(stor[l]>stor[l+1])
		    {
		      int temp = stor[l+1];
		      stor[l+1] = stor[l];
		      stor[l] = temp;
		    }
		}
	    }


	  if(s3>0)
	    {
	      val[s] += -1;
	      row_ind[s] = stor[0];
	      for(int k(1); k<s3; k++)
		{
		  if(stor[k]==stor[k-1])
		    {
		      val[s] += -1;
		    }
		  else
		    {
		      s++;
		      val[s] += -1;
		      row_ind[s] = stor[k];
		    }
		}
	      s++;
	    }

	  val[s] = 5.0+m*m;
	  row_ind[s] = i;
	  s++;
	  col_ptr[s2] = s;
	  s2++;

	}

      //  Initialize

      ValArray<double>::set_default_size(N4ct);
      ValArray<ValArray<double> >  phi(Ng);
      ValArray<ValArray<double> >  R(Ng);
      ValArray<ValArray<double> >  Minvphi(Ng);


      ValArray<double> valR(6*N4ct);
      ValArray<int> rowR_ind(6*N4ct);
      ValArray<int> colR_ptr(6*N4ct);


      double *v;
      int *ri, *cp;

      double *vR;
      int *riR, *cpR;
      
     infile input4(bufferTemp4);
     int data[400];
     // Assume that 400 would be maximum simplexes smeared ever for 4K i.e ~ 10% !
     string line;
     while (getline(input4, line)){
     input4 >> data[count];
     count = count+1;}
     cout << "Number of simplices actually smeared is " << count << endl ;
     
     // NOTE : March 2018 differences were here !! 
     for (int i(0) ; i < count-1 ; i++){ 
     phi[0][data[i]] = 1 ; 
     }

     int sR(0);
      for(int j(0); j<Ng; j++)
	{
	  for(int i(0); i<N4ct; i++)
	    {
	      if(phi[j][i]!=0)
		{
		  valR[sR]=phi[j][i];
	          rowR_ind[sR]=i;
		  sR++;
		}
	    }
	}

      colR_ptr[1]=sR;
     // CHLMOD STARTS HERE //

      cholmod_sparse *A;         // A is laplacian //
      cholmod_factor *L;
      cholmod_sparse *B;
      cholmod_dense *Y1;
      cholmod_sparse *Y; 
      cholmod_common Common, *cm;
      cm = &Common;

      cholmod_start (cm);
      cm->supernodal=0;

      A = cholmod_allocate_sparse(N4ct, N4ct, s, 1, 1, 1, 1, cm);

      cp = (int *) A->p;
      ri = (int *) A->i;
      v = (double*) A->x;     // This is ROW< COL< VAL //
      for(int i(0); i<N4ct+1; i++)
	{cp[i] = col_ptr[i];}
      for(int i(0); i<s; i++)
	{
	  ri[i] = row_ind[i];
	  v[i] = val[i];
	}       

// B = cholmod_allocate_sparse(N4ct, 1, count, 1, 1, 0, 1, cm); // Any !=square matrix will have this zero hidden, stype : 0 //
 

      B = cholmod_allocate_sparse(N4ct, 1, sR, 1, 1, 0, 1, cm);

      cpR = (int *) B->p;
      riR = (int *) B->i;
      vR = (double*) B->x;

      for(int i(0); i<2; i++)
	{cpR[i] = colR_ptr[i];}
      for(int i(0); i<sR; i++)
	{
	  riR[i] = rowR_ind[i];
	  vR[i] = valR[i];
	}

      L=cholmod_analyze(A, cm);

      cholmod_factorize(A, L, cm);
      Y=cholmod_spsolve(0, L, B, cm);        // First entry is - s type ! //
      Y1 = cholmod_sparse_to_dense(Y,cm);
      double *xfinal;
      int *cpfinal;

      

      xfinal = (double *) L->x;
      cpfinal = (int *) L->p;

      double determ(0);

      for(int i(0); i<N4ct; i++)
	{
	  determ += log(xfinal[cpfinal[i]]);
      // Calculate log(det) of Box operator
	}

      double *yfinal;

      yfinal = (double *) Y->x;
      double ans(0);

      for(int i(0); i<N4ct; i++)
	{Minvphi[0][i]=yfinal[i];}

      for(int i(0); i<N4ct; i++)
	{ans+=phi[0][i]*Minvphi[0][i];}

        for(int i(0); i<N4ct; i++)
        {cout <<  setprecision(10) << Minvphi[0][i] << endl ;}

      cholmod_free_factor(&L, cm);

      cholmod_free_sparse(&A, cm);

      cholmod_free_sparse(&B, cm);

      cholmod_free_sparse(&Y, cm);

      cholmod_free_dense(&Y1, cm) ; 

      cout << "logarithm of the Det is" << determ << endl;

      cholmod_finish (cm);

     cout << ans << endl; 
   }
return (0);
}


void matrix_sqr(ValArray<double> &M, ValArray<double> &Msqr, int N4ct)
{

  for(int i(0); i<N4ct; i++)
    {
      for(int j(0); j<N4ct; j++)
	{
	  for(int k(0); k<N4ct; k++)
	    {
	      Msqr[i*N4ct+j] += M[i*N4ct+k]*M[k*N4ct+j];
	    }
	}
    }

}


void conj_grad(ValArray<double> &M, ValArray<double> &phi, ValArray<double> &x, int N4ct, double minRes, int maxIt)
{

  ValArray<double> r(N4ct);
  ValArray<double> p(N4ct);
  ValArray<double> Mx(N4ct);
  double rsold(0);
  double rsnew(0);
  double alpha(0);


  for(int i(0); i<N4ct; i++)
    {
      for(int j(0); j<N4ct; j++)
	{
	  Mx[i]+=M[i*N4ct+j]*x[j];
	}
      r[i] = phi[i] - Mx[i];
      p[i] = r[i];
    }

  for(int i(0); i<N4ct; i++)
    { rsold += r[i]*r[i]; }

  for(int l(0); l<maxIt; l++)
    {
      ValArray<double> Mp(N4ct);

      for(int i(0); i<N4ct; i++)
	{
	  for(int j(0); j<N4ct; j++)
	    {
	      Mp[i]+=M[i*N4ct+j]*p[j];
	    }
	}

      double denom(0);

      for(int i(0); i<N4ct; i++)
	{
	  denom += p[i]*Mp[i];
	}

      alpha = rsold/(denom);

      for(int i(0); i<N4ct; i++)
	{
	  x[i] = x[i] + alpha*p[i];
	  r[i] = r[i] - alpha*Mp[i];
	}

      rsnew = 0;
      for(int i(0); i<N4ct; i++)
	{
	  rsnew += r[i]*r[i];
	}
      if(sqrt(rsnew)<minRes)
	{
	  return;
	}
      else
	{
	  for(int i(0); i<N4ct; i++)
	    { p[i] = r[i] + rsnew/rsold*p[i]; }
	  rsold = rsnew;
	}

    }

  cout << "CG did not converge in " << maxIt << " iterations" << endl;

  return;

}
