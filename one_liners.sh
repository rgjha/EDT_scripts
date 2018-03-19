#!/bin/bash

# Find file with some name 'abc'
find . -type f -name "abc*"

# Untar ABC.tar.gz
gunzip -c ABC.tar.gz | tar xopf -

# Line with no keyword
grep -w -v -e "done"  FILE

# Restrict decimal of 'awk' output
Some output | awk '{printf "%.2f %.2f\n", $1, $2}'

# Check internet speed etc. (also prints IP address)
curl -s  https://raw.githubusercontent.com/sivel/speedtest-cli/master/speedtest.py | python -

# Print 1 to something in bash
printf "%d\n" {1..109} >> MDTU

#Cut Line 10 to 100 from some file
sed -n -e '10,100p' input.txt > output.txt

# Merge many eps files into one pdf #
convert -density 600 *.eps -resize 100% new.pdf

# Sort file in ascending order
sort -n $file

# Cut first 50 lines of a file
tail -n +50  infile > outfile

# RMS of a file
awk '{ sum += $1*$1; n++ } END { if (n > 0) print sqrt(sum / n); }' FILE

# Average of a column in a file
awk '{ sum += $1; n++ } END { if (n > 0) print sum / n; }' FILE

# Maximum entry of a file
cat FILE | awk '{if ($1 > max) max=$1}END{print max}'

# Minimum entry
cat FILE  | awk 'BEGIN{min=512} {if ($1 < min) min=$1}END{print min}'

# If there is empty/blank lines in a file, it will remove them #
sed '/^\s*$/d' OLDFILE > NEWFILE

# Prints number of files with specific name in a given folder #
exts=( out.*); printf "There are ${#exts[@]} of them " extensions;

# Number of lines in a folder
find . -name '*.h' | xargs wc -l

# Merge files with one column each side by side #
pr -m -t OLDFILE1 OLDFILE2 > NEWFILE

# Alternative to pr -m -t above 
paste N* | column -s $'\t' -t

# Takes all the files with specific name in a folder and averages line by line #
awk '{a[FNR]+=$0;b[FNR]++;}END{for(i=1;i<=FNR;i++)print a[i]/b[i];}' FILES >> FILE

# Run on Condor without interruption #
nohup time bash ./script.sh > OUTFILE 2>&1

# Kill processes
lsof +D .
kill -9 PID#




