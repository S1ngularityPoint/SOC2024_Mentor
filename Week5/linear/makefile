CC=g++

linear: main.cpp
	$(CC) main.cpp linear_sol.cpp ../matrix/matrix.cpp -o main -std=c++17 -DWITHOUT_NUMPY -I/usr/include/python2.7 -lpython2.7
	./main <linear_dataset.csv > out.txt
clean:
	rm main