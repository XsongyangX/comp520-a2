#!/bin/bash

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
fi
	
# create a subdirectory for each phase described in 'programs' directory
for sub in $(ls programs)
do
	mkdir ./pretty/$sub
done

