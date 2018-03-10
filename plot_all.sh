# Plot all files in the directory on a single plot.

gnuplot -p << eof
set term wxt size 1200,900 title 'plots'
set terminal postscript eps enhanced color solid font "Helvetica,14"

set output 'plot.eps'
set xlabel 'distance'
set xrange [0:20]
set yrange [0:8]
set nokey
plot for [ file in "$@" ] file w linespoints
eof
