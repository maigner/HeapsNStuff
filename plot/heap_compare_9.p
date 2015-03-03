# Fix the Key
# Fix ranges

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" # Note that we divide by $2!

set yrange [0:40]
set logscale x

plot \
"data/result_20.dat" using 2:(1000 * $4/$2):(1000 * $6/$2):xticlabel(2) with errorlines title "My heap implementation", \
"data/result_20.dat" using 2:(1000 * $8/$2):(1000 * $8/$2):xticlabel(2) with errorlines title "STL heap"