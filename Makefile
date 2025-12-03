all: day_1

clean:
	rm -rf ./out

day_1: days/day_1.c
	mkdir -p ./out
	gcc -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g days/day_1.c -o out/day_1
	./out/day_1 in/day_1.txt

day_2: days/day_2.c
	mkdir -p ./out
	gcc -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g days/day_2.c -o out/day_2
	./out/day_2 in/day_2.txt

