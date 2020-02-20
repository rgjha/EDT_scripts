#!/bin/bash

# Find file with some name 'abc'
find . -type f -name "abc*"

# Change comma separated by tab separated and add each to new line 
# Useful for Mathematica sometimes
cat test.txt | tr '[,]' '[\t]' | tr " " "\n"

# Merge line 'n' and 'n+1' together on one line 
awk 'NR%2{printf "%s ",$0;next;}1' FILENAME

# Check the magnetization for my tensor script 
awk 'NR%2{printf "%s ",$0;next;}1' input >> tmp1
awk '{print $1, ($9-$3)/($12-$6), 0.50*($12+$6),$4, $5}' tmp1

# Delete files below some size 2700 (usually in units of ls -lrt output)
find . -type f -size -2700c -exec rm '{}' \;

# Find files whose size is less than 100 bytes
find . -type f -size -100c

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

# Delete files whose name is mentioned in FILE
xargs rm < FILE

# Sort a file
sort FILE -o FILE

# Run through files named *.txt in ascending order
for d in `ls *.txt | sort -V`; do

# Split SB.csv comma separated to file
awk -F',' '{print $2}' SB.csv >> sb.txt

# Cut a file between two line numbers passed
sed -n "${args[0]},${args[1]} p" FINAL_4K_m0125 > 4K_0125

# Change all extensions in directory
for d in *.c ; do
filename="${d%.*}"
mv $filename.c $filename.cpp
done

# Change SSH key to not being asked to enter password each time
ssh-keygen
ssh-copy-id -i ~/.ssh/id_rsa.pub XXX@comet.sdsc.edu # Replace appropraitely
ssh XXX@comet.sdsc.edu # Check that all is fine

# Python 2 to 3
for d in *.py ; do
2to3 -w $d  >> /dev/null 2>&1
sed 's/python/python3/g' $d >> tmp
mv tmp $d
done








