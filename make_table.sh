#!/bin/bash

echo "Order is : Pt, Px, Plaq., ML, SB"
for d in 3d_Nc8_8nt8_rt* ; do
echo $d
temp=`awk 'TMP = "%.2f" {printf "%2.0f \n", $4}' $d/results/poly_mod_polar.dat`
echo -ne "${temp}"
temp=`awk 'TMP = "%.2f" {printf "%0.4f (%2.0f) \n", $1, $2*10000}' $d/results/poly_mod_polar.dat`
echo -ne "&  " "${temp}" "&  "
temp=`awk 'TMP = "%.2f" {printf "%0.4f (%2.0f) \n", $1, $2*10000}' $d/results/lines_mod_polar.dat`
echo -ne "${temp}" "&  "
temp=`awk 'TMP = "%.2f" {printf "%0.4f (%2.0f) \n", $1, $2*10000}' $d/results/plaq.dat`
echo -ne "${temp}" "&  "
temp=`awk 'TMP = "%.2f" {printf "%0.4f (%2.0f) \n", $1, $2*10000}' $d/results/poly_mod.dat`
echo -ne "${temp}" "&  "
temp=`awk 'TMP = "%.2f" {printf "%0.5f (%2.0f) \n", $1, $2*100000}' $d/results/SB.dat`
echo "${temp}" "&  "  "&  "   "&  "
done 
