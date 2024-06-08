CC=g++
CFLAGS=-Wall

all: R M Test

R: Coins.cpp
	$(CC) $(CFLAGS) Coins.cpp -o Coins_R
	./Coins_R 1

M: Coins.cpp
	$(CC) $(CFLAGS) Coins.cpp -o Coins_M
	./Coins_M 2

Joint: Coins.cpp
	$(CC) $(CFLAGS) Coins.cpp -o Coins
	./Coins 3 

Test: Coins.cpp
	$(CC) $(CFLAGS) Coins.cpp -o Coins
	i=1; \
	while [ $$i -le 8 ]; do \
		echo $$i; \
		timeout 5 ./Coins 3 < tests_coins/$$i.in; \
		i=$$((i + 1)); \
	done;

clean:
	rm Coins Coins_M Coins_R
