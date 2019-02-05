#~/bin/bash
echo "VALIDATION BEGIN"

for file in $(ls *.min)
do
	echo $file
	cat $file | ~cs520/minic typecheck
done
