#!/usr/bin/python3
'''This code spits solution to the matrix equation :
[(-Box+m*m)]*[Solution] = Delta Source. It reads N4inf from
the original configuration file and then calculates the
neighbors of 4-simplex. If x=y, then it is (5.0 + m*m)
or else it is -1 or -2 or -3 or -4. Note that since we
deal with degenerate trinagulations, they can be up to 4
identical simplices. Needs tmp.dat as input file for
configuration (trimmed after bash) '''

''' Previous edits : October 2, 2015 '''
''' Last Edited : March 9, 2018 '''

import numpy as np
import pickle as pickle
import scipy as sp
import scipy.sparse
from numpy import ndarray
import os
import fileinput
import glob
import random
import time
import math
import collections
from scipy import sparse
from scipy.sparse import coo_matrix
from scipy import linalg
from numpy import matrix, rank
import scipy.sparse.linalg as spsl
import random

''' Define variables/constants '''

list = []
col = []
row = []
val = []
startTime = time.time()
m_square = 0.0625  # Bare mass squared in the Covariant Laplcacian #
count = 0


myfile = 'tmp.dat' # Configuration File #
count=0
search = 'N4inf:'
f2 = open(myfile, 'r')

with open(myfile) as myFile:
    for num, line in enumerate(myFile, 1):
        if search in line:
            lines = [_f for _f in (line.rstrip() for line in myFile) if _f]
            
            for line in lines:
                for j in range(0,6):
                    s  = line.split()
                    list.append(int(s[j]))    # Row business #
                    
                    if (j+1)% 6 == 0:         # When at the last choice for a particular row, write to files #
                        
                        col.append(int(s[j]))
                        list.pop(0)                         # Pull out the 0th element to start sorting #
                        
                        
                        counter=collections.Counter(list)   # Import collections at top of the code #
                        a, b = list(counter.keys()), list(counter.values())
                        a.insert(0,int(s[0]))               # Insert the pulled out element #
                        b[:] = [x*-1 for x in b]
                        b.insert(0, 5 + float(m_square)) # Insert Diagonal Values at 0th element # # Refer to the paper by Bakker and Smit #
                        
                        f4 = open("ROW.dat","a")
                        f4.write("%s\n" % s[0] * len(a)) # Forcing it to write the row number as many time required for COO format #
                        
                        
                        f5 = open("COLUMN.dat","a")
                        for i in range (0,len(a)):
                            f5.write("%s\n" % a[i])
                        
                        
                        f6 = open("VALUE.dat","a")
                        for i in range (0,len(b)):
                            f6.write("%s\n" % b[i])
                            del val[:] # Empty the lists defined so that we can move to next line, i.e next row #
                            del list[:]
        
            
            with open("ROW.dat") as f4:
                row = f4.readlines()
                row = [int(x.strip('\n')) for x in row]
            with open("COLUMN.dat") as f5:
                col = f5.readlines()
                col = [int(x.strip('\n')) for x in col]
    with open("VALUE.dat") as f6:
        val = f6.readlines()
        val = [float(x.strip('\n')) for x in val]
            
        A = coo_matrix((val, (row, col))).toarray()
        # COO i.e Coordinate format --> Dense Matrix #
            
        A1 = A[np.apply_along_axis(np.count_nonzero, 1, A) >= 2, :]
        # Deletes rows which have less than or equal to two non-zero elements #
            
        A2 = A1[:, np.apply_along_axis(np.count_nonzero, 0, A1) >= 2]
        # Deletes columns which have less than or equal to two non-zero elements #
            
        #print A.shape   # Prints dimension of matrix A #
        #print rank(A)   # Prints the rank of matrix A #
        #print A2.shape

        Q = A2.shape[0] # Number of rows in A2 #
        RR = coo_matrix(A2)
        
        MINV = linalg.inv(A2)
        DEL = np.zeros((Q,1))

        with open("delta_sources") as f8:
            content = f8.readlines()
 
            content = [ int(x) for x in content]
            # http://stackoverflow.com/questions/3371269/call-int-function-on-every-list-element-in-python #
            
            count = len(content)
            for i in range(0,count): 
                DEL[content[i]] = 1.00
            
            RG = np.count_nonzero(DEL)
            print(('No. of sources (1 for pint, > 1 for wall) == ', RG))
            RG1 = [i for i, e in enumerate(DEL) if e != 0]
            DATA = np.array(DEL)
            DEL_T = DEL.T
            X = MINV.dot(DEL)  # Remember that .dot is essential, normal matrix multiplication was troubling me here for sometime #
            #Y = np.linalg.solve(A2, DEL)     # X and Y are two different methods of calculating same thing #
            #Y = np.linalg.tensorsolve(A2,DEL)
            
            D = DEL.T
            X5 = D.dot(X)
            Y = np.arange(Q).reshape((Q,1))
            
            for l in range(Q):
                file = open("solution_vector.dat","a")  # Contains two-point function #
                file.write(str(X[l,0]))
                
                file.write("\n")
                file.close()

            runningTime = (time.time()-startTime)
            print("This Python code ran for about %f seconds" % runningTime)
