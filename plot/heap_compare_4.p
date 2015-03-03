#change to relative metric

plot \
"data/result.dat" using 2:($4/$2) with linespoints, \
"data/result.dat" using 2:($8/$2) with linespoints
