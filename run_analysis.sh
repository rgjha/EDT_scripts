#!/bin/bash

set -e  # Exit immediately if any problem
# Before we take off, strip the configuration number from the Data directory and make a list #

if [ -e list.txt ]  # Delete list if it exists from previous run
then
rm list.txt
else
echo "list not found" > /dev/null 2>&1
fi

for file in ./M=0.5/Data/*_1.dat ; do
list=$(echo $file | awk -F '_' '{print $2}')
printf $(echo "$list") >> list.txt
printf "%s\n" >> list.txt
done

echo "List done"

while read size; do  # read the list of configs from list.txt and loop over it #

for d in M=*   # This has to be changed to M=*
do
cd $d

for((origins=1;origins<=5;origins+=1))
do
if [ -e sum_next.cpp ]
then
echo "File exists1" > /dev/null 2>&1
else
scp ../sum_next.cpp ./
fi
g++ -o abc sum_next.cpp                 # Involves average over simplices at distance 'r' respectively #
./abc ./Data/prop_${size}_${origins}.dat
rm abc
mv new.dat ${size}_new_${origins}.dat
done

# Now we build for specific configuration(s) #

pr -w 170 -m -t ${size}_new_*.dat > G1.dat      # Building G(r) by combining from different origins #

# Alternate : paste file1 file2 | column -s $'\t' -t

for((origins=1;origins<=5;origins+=1))
do
awk ' {print ($1*$1)} ' ${size}_new_${origins}.dat > New_${origins}.dat  # Square to obtain G^2 (r) #
done

pr -w 170 -m -t New_*.dat > G2.dat
# Combine different origins together in a file

# Now, Average over origins

awk '
{ T=0
for(N=1; N<=NF; N++) T+=$N;
T/=(NF)
print T }' G1.dat > G_r_${size}.dat

awk '
{ T=0
for(N=1; N<=NF; N++) T+=$N;
T/=(NF)
print T }' G2.dat > G2_r_${size}.dat


# Note : G(r)^{2} should be constructed after sum OVER CONFIGS #
# I am never explicitly calculating it, since I fit to G(r) only #

rm New_*.dat
rm ${size}*.dat
rm G1.dat G2.dat

if [ -d Gr ]
then
echo "Directory exists1" > /dev/null 2>&1
else
mkdir Gr
fi

if [ -d G2r ]
then
echo "Directory exists" > /dev/null 2>&1
else
mkdir G2r
fi

mv G_r_${size}.dat ./Gr
mv G2_r_${size}.dat ./G2r

cd ..

done
done <list.txt

for d in M=*    # Scans directory for different bare mass  # This has to be changed to M=*
do
cd $d

cd G2r
if [ -e strip_one.sh ]
then
echo "Directory exists1" > /dev/null 2>&1
else
scp ../../strip_one.sh ./
fi
sh strip_one.sh

if [ -e knife.py ]
then
echo "----" > /dev/null 2>&1
else
scp ../../knife.py ./
fi

flag=0
for((size=1;size<=17;size+=1)) ; do
python knife.py DF_${size}.txt >> mean.dat
MAX=$(< "DF_1.txt" wc -l)
A=$(< "DF_${size}.txt" wc -l)
if [ "$A" -lt "$MAX" ] && [ "$flag" -eq 0 ]
then
max="${size}"
max1=$((max - 1))
flag=1
echo "For some configs, tail vanishes from ${max} onwards, so max t-slice for G2r is "${max1}" "
else
echo "----" > /dev/null 2>&1
fi
done

head -"${max1}" mean.dat > mean1-${max1}.dat
tail -n+2 mean1-${max1}.dat > mean2-${max1}.dat
tail -n+3 mean1-${max1}.dat > mean3-${max1}.dat
tail -n+4 mean1-${max1}.dat > mean4-${max1}.dat



if [ -e 1-${max1}.py ]
then
echo "----" > /dev/null 2>&1
else
scp ../../LSQ_Codes/1-${max1}.py ./
fi
python 1-${max1}.py > Out1-${max1}_G2r
echo "Ran 1-${max1} LSQ fit now "

cd ..

cd Gr
if [ -e strip_one.sh ]
then
echo "Directory exists1" > /dev/null 2>&1
else
scp ../../strip_one.sh ./
fi
sh strip_one.sh

if [ -e knife.py ]
then
echo "----" > /dev/null 2>&1
else
scp ../../knife.py ./
fi

flag=0
for((size=1;size<=17;size+=1)) ; do
python knife.py DF_${size}.txt >> mean.dat
MAX=$(< "DF_1.txt" wc -l)
A=$(< "DF_${size}.txt" wc -l)
if [ "$A" -lt "$MAX" ] && [ "$flag" -eq 0 ]
then
max="${size}"
max1=$((max - 1))
flag=1
echo "For some configs, tail vanishes from ${max} onwards, so max t-slice for Gr is "${max1}" "
else
echo "----" > /dev/null 2>&1
fi
done

head -"${max1}" mean.dat > mean1-${max1}.dat
tail -n+2 mean1-${max1}.dat > mean2-${max1}.dat
tail -n+3 mean1-${max1}.dat > mean3-${max1}.dat
tail -n+4 mean1-${max1}.dat > mean4-${max1}.dat

if [ -e 1-${max1}.py ]
then
echo "----" > /dev/null 2>&1
else
scp ../../LSQ_Codes/1-${max1}.py ./
fi
python 1-${max1}.py > Out1-${max1}_Gr
echo "Ran 1-${max1} LSQ fit now "

cd ..
cd .. 

done
