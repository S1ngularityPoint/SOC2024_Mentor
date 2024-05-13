echo $3
./input < $1 $2 $3 > input.txt 
./Naive < input.txt
./Parallel < input.txt