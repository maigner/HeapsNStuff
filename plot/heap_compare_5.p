# fixing range and scale

set yrange [0:]
set logscale x

plot \
"data/result.dat" using 2:($4/$2) with linespoints, \
"data/result.dat" using 2:($8/$2) with linespoints
