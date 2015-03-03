# Add error bars

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" # Note that we divide by $2!

set yrange [0:]
set logscale x


plot \
"data/result_20.dat" using 2:(1000 * $4/$2):(1000 * $6/$2) with errorlines, \
"data/result_20.dat" using 2:(1000 * $8/$2):(1000 * $8/$2) with errorlines