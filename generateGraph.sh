#!/bin/sh

APIKEY=$(cat APIKEY)
curl "https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&origins=Washington,DC&destinations=New+York+City,NY&key=${APIKEY}"

