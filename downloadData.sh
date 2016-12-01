#!/bin/bash

curl http://snap.stanford.edu/data/roadNet-TX.txt.gz | gunzip | tail -n +5 > net.txt
