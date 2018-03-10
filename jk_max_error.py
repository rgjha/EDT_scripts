'''This code calculates the jackknife error
   by going through all possible blocksize i.e
   1 through (length of data) and prints the average
   and error corresponding to bin size where the error
   is maximized. Use with caution '''

import sys
from math import *
data = []; data_tot = 0. ; Data = [] ; data_jack = [] ; Error_Max = []
filename = sys.argv[1]

if len( sys.argv ) > 0:
    filename = sys.argv[1]
if len( sys.argv ) <= 0:
    print "NEED 1 ARGUMENT : FILE "
    print "Run this as : python knife.py FILENAME"
    sys.exit()

file = open(filename, "r")
for line in file:
    line = line.split()
    data_i = float(line[0])
    data.append(data_i)
    data_tot += data_i
n = len(data)

print "Data Size ", n
flag = 0 
data_jack_err_old = 0.
current_max_error = 0.

for i in range(1, n, 1):
    blocksize = i 
    n_b = n / blocksize
    print " SIZE", blocksize
    B = 0.

    for k in range(n_b):
        for w in range((k*blocksize)+1,(k*blocksize)+blocksize+1):
            B += data[w-1]
    
        Data.insert(k,B)
        B = 0.

    for i in xrange(n_b):
        data_jack.append((data_tot - Data[i]) / (n - blocksize))
        data_av = data_tot / n      # Do the overall averages
        data_jack_av = 0.; data_jack_err = 0.
    for i in xrange(n_b):
        dR = data_jack[i]
        data_jack_av += dR
        data_jack_err += dR**2

    data_jack_av /= n_b
    data_jack_err /= n_b

    data_jack_err = sqrt((n_b - 1) * abs(data_jack_err - data_jack_av**2))

    if data_jack_err > current_max_error and flag >0 :
        Error_Max.insert(0,data_jack_err)
        current_max_error = max(Error_Max)
        AVG = data_jack_av
        ERROR = data_jack_err
        BS = blocksize

    
    data_jack_err_old = data_jack_err
    data_jack_err = 0.0
    data_jack_av = 0.0
    flag = flag + 1
    B = 0.
    Data = [] ; data_jack = []

print "  %8.4f "  "  %6.4f "  "  %8.4f " % (AVG, ERROR, BS)


