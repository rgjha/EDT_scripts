#!/bin/bash
# Last edit : March 12, 2018 #

set -e 
date1=`date`
echo "RUNNING STARTED"

if [[ $# -ne 2 ]] ; then
echo 'Provide arguments : "ORIGINS" "TAG" '
echo 'TAG will be something like l4000k2450_h60 (without trailing underscore) !'
echo 'Must be run from the /Tree directory'
exit 0
fi


if [ -e "./list" ]; then
echo "File exists1" > /dev/null 2>&1
else 
echo "List of configs to run not found, bye-bye !!"
exit 1
fi

if [ -e "../sum_next.cpp" ]; then
echo "File exists1" > /dev/null 2>&1
else
exit 1
fi

while read size; do
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++"


tag=$2_${size}

# ========================================================================
# Now specify how many origins to take for every configuration (usually 5)
first=1
last=$1
# ========================================================================

scp ./Configs/$tag ./ 

for((origins="$first";origins<="$last";origins+=1))

do
echo Config/Origin = $size/$origins

if [ "$origins" == "$first" ] ; then
sed -n '/N4inf/,/N34/p' $tag > ab_${size}.dat  # Cuts between N4 inf and N34 #
N4inf=$(grep "N4inf:" ab_${size}.dat | awk '{print $2}')
# Reads the value of N4inf using grep and awk #
echo N4inf=$N4inf
sed '$d' ab_${size}.dat > tmp.dat
sed '1d' tmp.dat > config.dat
rm ab_*.dat
sed -e "s/VOL 8000/VOL $N4inf/g"  utilities.h > utilities1.h
rm utilities.h
mv utilities1.h utilities.h
g++ -std=c++0x driver.cpp update.cpp test.cpp -o dr.exe
./dr.exe 2000 # This is dummy now
rm dr.exe
rm MST.dat
awk 'NR==1, NR==1' Origin.dat > Origin_1.dat
awk 'NR==2, NR==2' Origin.dat > Origin_2.dat
awk 'NR==3, NR==3' Origin.dat > Origin_3.dat
awk 'NR==4, NR==4' Origin.dat > Origin_4.dat
awk 'NR==5, NR==5' Origin.dat > Origin_5.dat
fi

mv Origin_${origins}.dat  Origin.dat
value=$(<Origin.dat)
echo The redefined origin is =$value

g++ -std=c++0x driver.cpp update.cpp test.cpp -o dr1.exe
./dr1.exe $value  # Now, this value is not dummy but lines of Origin.dat
rm dr1.exe
rm Origin.dat

if [ "$origins" == "$last" ] ; then
sed -e "s/VOL $N4inf/VOL 8000/g"  utilities.h > utilities1.h
rm utilities.h
mv utilities1.h utilities.h
fi

mv MST.dat MST_${size}.dat
cp MST_${size}.dat ../MST.dat
cp config.dat ../config.dat
cp tmp.dat ../tmp.dat

cd ..   # Tree --> one down 
mv config.dat config_${size}_${origins}.dat

if [ "$origins" == "$first" ] ; then
    g++ -std=c++0x sliceread.cpp -o sr.exe
    ./sr.exe config_${size}_${origins}.dat $N4inf 
    rm sr.exe
    cp slice_read.dat slice_read_${size}_${origins}.dat
fi 

cp slice_read.dat slice_read_${size}_${origins}.dat

Actual=$(grep -w -m 1 "$value" slice_read_${size}_${origins}.dat | awk '{print $2}')
echo "$Actual" > Actual.dat

g++ -std=c++0x pull.cpp -o pull.exe
./pull.exe slice_read_${size}_${origins}.dat  MST.dat $N4inf 
rm pull.exe

cp MST_new.dat MST_new_${size}_${origins}.dat

g++ -std=c++0x smear.cpp -o smear.exe
./smear.exe MST_new_${size}_${origins}.dat
rm smear.exe

mv delta_sources delta_sources_${size}_${origins}
cp ./Tree/$tag ./

for((mass=5;mass<=80;mass*=2))
do
mass1=$(echo "scale=4; $mass/80"|bc -l)

./up_${mass}.x ${size} $tag  delta_sources_${size}_${origins}> s.dat 2>&1
sed '$d' s.dat > s1.dat    # Remove last line
sed '$d' s1.dat > s2.dat   
sed '1d' s2.dat > solution_vector.dat # Remove 1st line 
rm s.dat
rm s1.dat
rm s2.dat
mv solution_vector.dat solution8K_${size}_${origins}_${mass}
# If this loop is going for the first time, delete these files # 
if [ "$mass" == 5 ] ; then
rm Actual.dat
rm MST.dat
rm MST_new.dat
fi 

g++ -std=c++0x final.cpp -o final.exe
./final.exe solution8K_${size}_${origins}_${mass} MST_new_${size}_${origins}.dat $N4inf 
rm final.exe

mv prop_data.dat prop_${size}_${origins}.dat

if [ ! -d "./Data/${mass}" ]; then
  echo "Directory $mass not found, bye-bye !!" 
  exit 1 
fi
mv prop_${size}_${origins}.dat ./Data/${mass}

# ================================================
# Create a diretory in Data for different masses
# m = 0.03125, 0.0625, 0.125, 0.25, 0.50
# Their order is weird, due to addition later on
# m = .03125 --> 80
# m = .0625  --> 5
# m = .125  --> 10
# m = .25  --> 20
# m = .5  --> 40
# ================================================
done

if [ "$origins" == "$last" ] ; then
sh ./erase.sh    #Erase all files of completed config run #
fi

cd Tree
done 
done <list         # List contains all the config for which we run

date=`date`
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
echo "RUNNING started : $date1 and finished : $date" 
