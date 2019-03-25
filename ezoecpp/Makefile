gcc_options = -std=c++17 -Wall --pedantic-error

main.out : main.cpp all.h all.h.gch
	g++-8 $(gcc_options) -include all.h $< -o $@

all.h.gch : all.h
	g++-8 $(gcc_options) -x c++-header -o $@ all.h

run : main.out
	./main.out

clean :
	rm -f ./main.out
	rm -f ./all.h.gch

.PHONY : run clean
