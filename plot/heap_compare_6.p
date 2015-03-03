# Label your axes!

set xlabel "Number of elements (logscale)"
set ylabel "Microseconds per push operation" # Note that we divide by $2!

set yrange [0:]
set logscale x

plot \
"data/result.dat" using 2:($4/$2) with linespoints, \
"data/result.dat" using 2:($8/$2) with linespoints
