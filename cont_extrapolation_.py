#!/usr/bin/python3
# This code fits the data to the function defined below #
# =============================================================
import os
import sys
import numpy as np
import math
from scipy.optimize import curve_fit
from scipy.stats import chi2

fname = sys.argv[1]

x, y, err = np.loadtxt(fname, unpack=True) # Read the data in #
n = len(x) # No. of data points #

# Initial values of parameters #
p0 = [1.0, 0.01]

f = lambda x, a, b : (a/(x*x)) + b 

# Read about lambda notation here : http://www.secnetix.de/olli/Python/lambda_functions.hawk #
p, covm = curve_fit(f, x, y, p0, err) # Do the fit
a, b = p

chisq = sum(((f(x, a, b) - y)/err)**2) # Compute chi-squared
ndf = n -len(p) # no. of degrees of freedom
print("NDF is " , ndf)
Q = 1. - chi2.cdf(chisq, ndf) # Quality of fit parameter : Q , More the better ! #
chisq = chisq / ndf # Compute chi-squared per DOF

covm = covm/chisq  # !
aerr, berr = np.sqrt(np.diag(covm)) # Set the error bars

# ======================================
# Print the results # 
# p[0] = a ; p[1] = b 
print("-----")
print("a = %10.8f +/- %7.8f with %7.4f percent error " % (a, aerr, (aerr/a)*100))
print("b = %10.7f  %7.7f with %7.4f percent error " % (b, berr, (berr/b)*100))
print("chi squared / NDF = %7.4lf" % chisq)
print("CL = %2.2f" % Q)   # Checked that it 1 - pvalue (gnuplot) ; 1 - P
print("fit(x) = %.4g * x + %.4g" % (p[0], p[1]))
print("err(x) = sqrt(%.4g - %.4g * x + %.4g * x**2)" % (covm[1][1], -1.0 * (covm[1][0]+ covm[0][1]), covm[0][0]))
# Chi-square calculator : https://www.fourmilab.ch/rpkp/experiments/analysis/chiCalc.html # 
