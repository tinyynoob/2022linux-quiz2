
RNG: RNG.cpp
	g++ -o $@ $^

3: 3.c
	clang-format -i 3.c
	gcc -o $@ $^


4: 4.c
	clang-format -i 4.c
	gcc -o $@ $^

run4:
	sudo taskset -c 0 ./4 8 > 4_time.csv
	gnuplot 4_time.gp
	mv 4_time.png 4_time_8.png

	sudo taskset -c 0 ./4 24 > 4_time.csv
	gnuplot 4_time.gp
	mv 4_time.png 4_time_24.png

	sudo taskset -c 0 ./4 40 > 4_time.csv
	gnuplot 4_time.gp
	mv 4_time.png 4_time_40.png

	sudo taskset -c 0 ./4 56 > 4_time.csv
	gnuplot 4_time.gp
	mv 4_time.png 4_time_56.png

	rm 4_time.csv

clean:
	-rm -r 3 4 RNG gcd_time.csv


