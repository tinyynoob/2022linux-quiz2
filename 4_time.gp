reset                                                                           
set xlabel 'number of cases'
set ylabel 'total time (ns)'
set title 'perfomance comparison'
set term png enhanced font 'Times_New_Roman, 10'
set output '4_time.png'
set xtic 10000
set xtics rotate by 45 right
set datafile separator ","
set key left

plot \
"4_time.csv" using 1:2 with linespoints linewidth 1 title "naive", \
"4_time.csv" using 1:3 with linespoints linewidth 1 title "improved" 
