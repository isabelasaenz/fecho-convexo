set terminal gif animate delay 15
set output 'utils/animacao1000.gif'
set xrange [0:12000]
set yrange [0:12000]

stats 'output.dat' nooutput
do for [i=1:int(STATS_records)] {
   plot 'output.dat' using 1:2 every 1::0::i with linespoints
}
