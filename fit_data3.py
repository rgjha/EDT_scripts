#!/usr/bin/python

# This code fits the data to the function defined below #
# October 8, 2016 #
# =============================================================
import os
import sys
import numpy as np
from scipy.optimize import curve_fit
from scipy.stats import chi2


fname = sys.argv[1]
print "*******************************"

x, y, err = np.loadtxt(fname, unpack=True) # Read the data in #
n = len(x) # No. of data points #

# Initial values of parameters #
p0 = [1.00, 0.5, -0.025]

f = lambda x, a, b, c : (a* (x**c) * np.exp(b*x))
print "Fit form : A* x^C * np.exp(B*x) "


# Read about lambda notation here : http://www.secnetix.de/olli/Python/lambda_functions.hawk #

p, covm = curve_fit(f, x, y, p0, err) # Do the fit
a, b, c = p

chisq = sum(((f(x, a, b, c) - y)/err)**2) # Compute chi-squared
ndf = n -len(p) # no. of degrees of freedom
print "NDF is " , ndf
Q = 1. - chi2.cdf(chisq, ndf) # Quality of fit parameter : Q , More the better ! #
chisq = chisq / ndf # Compute chi-squared per DOF

aerr, berr, cerr = np.sqrt(np.diag(covm)/chisq) # Set the error bars

# ======================================
# Print the results #

print "-----"
print fname
print "A = %2.2f +/- %2.2f with %7.4f percent error " % (a, aerr, (aerr/a)*100)
print "B = %2.2f  +/-   %2.2f with %7.4f percent error " % (b, berr, (berr/b)*100)
print "C = %2.2f  +/-   %2.2f with %7.4f percent error " % (c, cerr, (cerr/c)*100)
print "chi squared / NDF = %2.3lf" % chisq
print "CL = %2.2f" % Q 

# Chi-square calculator : https://www.fourmilab.ch/rpkp/experiments/analysis/chiCalc.html # 

