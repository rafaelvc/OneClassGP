#!/bin/bash

pop=500
gen=100 

re=`echo "s/\(ec.term.maxgen\">\)[0-9]*/\1${gen}/g"`
sed -i $re mymaxfct.conf

re=`echo "s/\(ec.pop.size\">\)[0-9]*/\1${pop}/g"`
sed -i $re mymaxfct.conf

for run in 1 2 3 4 5 6 7 8 9 10
do	
	mkdir -p results.$run/
	#folds
	for i in 1 2 3 4 5
	do
		re=`echo "s/^\(.*f.open.*\)[0-9].*$/\1${i}\");/g"`
		sed -i $re SymbRegMain.cpp
		sed -i $re SymbRegEvalOp.cpp
		make
		./symbreg -OBec.conf.file=mymaxfct.conf
		mv beagle.obm.gz results.$run/beagle_${i}.obm.gz
		mv beagle.log results.$run/beagle_${i}.log
		mv result_fold.txt results.$run/result_fold_${i}.txt
	done

done
