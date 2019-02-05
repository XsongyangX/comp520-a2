#~/bin/bash
echo "VALIDATION BEGIN"

for file in $(ls *.min)
do
	cat $file | ~cs520/minic typecheck
done
