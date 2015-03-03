# Fix scaling. Try to get readable numbers

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" # Note that we divide by $2!

set yrange [0:]
set logscale x

#be careful with relative standard deviations!

plot \
"data/result.dat" using 2:(1000 * $4/$2) with linespoints, \
"data/result.dat" using 2:(1000 * $8/$2) with linespoints
