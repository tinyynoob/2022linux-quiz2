
RNG: RNG.cpp
	g++ -o $@ $^

3: 3.c
	clang-format -i 3.c
	gcc -o $@ $^

clean:
	rm -r 3 RNG


