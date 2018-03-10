'''This code calculates the jackknife error
   First check/edit : September 12, 2015
   Checked further October 27, 2015 
   '''

import sys
import itertools 
from math import *
data = []; data_tot = 0. ; Data = [] ; data_jack = []

if len( sys.argv ) > 2:
    filename = sys.argv[1]
    therm_cut = int(sys.argv[2])
    binsize = sys.argv[3]
if len( sys.argv ) <= 2:
    print "NEED 3 ARGUMENTS : FILE THERM-CUT BLOCKSIZE "
    print "Run this as : python knife.py FILE THERM-CUT BLOCKSIZE"
    sys.exit()

file = open(filename, "r")
for line in itertools.islice(file, therm_cut, None):
    
# ThermCut will be ignored while reading line(s) 
    line = line.split()
    data_i = float(line[0])
    data.append(data_i)
    data_tot += data_i
    n = len(data)  # Data count


blocksize = int(binsize)

n_b = n / blocksize
B = 0.

for k in range(n_b):
    for w in range((k*blocksize)+1,(k*blocksize)+blocksize+1):
        B += data[w-1]
    Data.insert(k,B)
    B = 0

''' Do the jackknife estimates '''

for i in xrange(n_b-1):
    data_jack.append((data_tot - Data[i]) / (n - blocksize))
    data_av = data_tot / n   # Do the overall averages
    data_av = data_av
    data_jack_av = 0.; data_jack_err = 0.
for i in xrange(n_b-1):
    dR = data_jack[i]
    data_jack_av += dR
    data_jack_err += dR**2

data_jack_av /= n_b-1
data_jack_err /= n_b-1

data_jack_err = sqrt((n_b - 2) * abs(data_jack_err - data_jack_av**2))
print " %8.7f "  " %6.7f"   " %6.2f" % (data_jack_av, data_jack_err, n_b)
