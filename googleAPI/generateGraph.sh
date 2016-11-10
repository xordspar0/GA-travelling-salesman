#!/bin/sh

APIKEY=$(cat APIKEY)

oldIFS=$IFS
cities=($(cat cities.txt | sed 's/ /%20/g'))

echo "" > graph.txt
for i in $(seq 0 3)
do
	origin=${cities[$i]}
	for j in $(seq $(($i + 1)) 49)
	do
		destination=${cities[$j]}
		miles=$(curl -s "https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&origins=${origin}&destinations=${destination}&key=${APIKEY}" | grep -Eo '"[0-9,]+ mi"' | grep -Eo '[0-9,]+' | sed 's/,//g')
		echo $i $j $miles >> graph.txt
	done
done

