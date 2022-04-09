#! /bin/bash

if [ $# -ne 2 ]
then
    echo "ERROR: Script requires two arguments!"
    echo ""
    echo "Command format: ./lab.sh inputFileName outputFileName"
    echo ""
    echo ">> Input file shoudl be a CSV file (.csv)"
    echo ">> Output file shoudl be a Text file (.txt)"
    exit 1
fi

if ! [ -f "$1" ]
then
    echo "Error: Valid input file not found!"
    exit 1
fi

>$2

#--------------------------------------------------------------
echo "--------------------------------------------------------" >>$2
echo "List of all colleges" >> $2
echo "Column names : Name, PredominantDegree, HighestDegree, Region, Geography, AdmissionRate, AverageCost, Expenditure." >>$2
echo "--------------------------------------------------------" >>$2

awk -F"," 'NR>1 {print $1,$2,$3,$5,$6,$7,$10,$11}' $1 >> $2

#---------------------------------------------------------------
echo "" >> $2
echo "--------------------------------------------------------" >>$2
echo "Name of colleges with highest degree Bachelor's" >> $2
echo "--------------------------------------------------------" >>$2

awk -F"," '$3=="Bachelor\x27s" {print $1}' $1 >> $2
#----------------------------------------------------------------
echo "" >> $2
echo "--------------------------------------------------------" >>$2
echo "Average of AdmissionRate with respect to Geography" >> $2
echo "--------------------------------------------------------" >>$2
echo "" >> $2
echo "Geography: AverageAdmissionRate" >> $2
awk -F"," '$6=="Mid-size City" {count++;sum+=$7} END{printf "Mid-size City: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Small City" {count++;sum+=$7} END{printf "Small City: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Remote Rural" {count++;sum+=$7} END{printf "Remote Rural: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Fringe Rural" {count++;sum+=$7} END{printf "Fringe Rural: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Large Suburb" {count++;sum+=$7} END{printf "Large Suburb: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Distant Town" {count++;sum+=$7} END{printf "Distant Town: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Large City" {count++;sum+=$7} END{printf "Large City: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Remote Town" {count++;sum+=$7} END{printf "Remote Town: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Distant Rural" {count++;sum+=$7} END{printf "Distant Rural: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Small Suburb" {count++;sum+=$7} END{printf "Small Suburb: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Mid-size Suburb" {count++;sum+=$7} END{printf "Mid-size Suburb: %.4f\n", sum/count}' $1 >> $2
awk -F"," '$6=="Fringe Town" {count++;sum+=$7} END{printf "Fringe Town: %.4f\n", sum/count}' $1 >> $2

#----------------------------------------------------------------
echo "" >> $2
echo "--------------------------------------------------------" >>$2
echo "List of top 5 colleges with highest MedianEarning" >> $2
echo "--------------------------------------------------------" >>$2

sort -t , -k 16 -r -n input.csv > sample.csv
awk -F"," 'NR<=5 {print $1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16}' sample.csv >> $2
rm sample.csv