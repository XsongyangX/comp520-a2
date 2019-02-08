#!/bin/bash

# parse command line arguments
if [ $# -lt 1 ]
then
	echo "Missing arguments"
	echo "Usage: $0 <mode>"
	echo " + mode: destroy|keep"
	echo " + + destroy: deletes the pretty printer output"
	echo " + + keep: keeps the pretty printer output"
	exit 1
fi

# build a compiler if not already built
if [ -f ./src/minic ]; then
	echo "Compiler minic found"
else
	./build.sh
fi

# create a pretty output directory
if [ -d ./pretty ]; then
	echo "Pretty directory found"
else
	mkdir pretty
	echo "Create pretty directory"
fi
	
# create a subdirectory for each phase described in 'programs' directory
for sub in $(ls programs)
do
	if [[ -d ./pretty/$sub ]]
	then
		echo "subdirectory exists"
	else
		mkdir ./pretty/$sub
		echo "subdirectory created: $sub"
	fi
done

# create another directory for each subdirectory to hold the double pretty output
for sub in $(ls pretty)
do
	if [[ -d ./pretty/$sub/compare ]]
	then 
		echo "comparison directory exists"
	else
		mkdir ./pretty/$sub/compare
		echo "compare directory created in $sub"
	fi
done

echo "--"
echo "initial pretty print"
echo "--"

# call compiler to pretty print source programs
for sub in $(ls programs)
do
	for program in $(ls programs/$sub/valid/ | egrep '*.min')
	do
		cat $program | ./src/minic pretty > ./pretty/$sub/$program
	done
done

echo "--"
echo "secondary pretty print"
echo "--"

# call compiler to pretty print on the pretty output
for sub in $(ls pretty)
do
	for program in $(ls pretty/$sub/ | egrep '*.min')
	do
		cat $program | ./src/minic pretty > ./pretty/$sub/compare/$program
	done
done

echo "-----"
echo "python script"
echo "-----"

# call python script to compare
./prettyCompare.py $1