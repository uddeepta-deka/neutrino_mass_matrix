set terminal postscript solid color enhanced 22
set output 't12.eps'
set xlabel 'angle in radians'
set ylabel 'freq'
set border 3
set style fill solid 1.0 noborder
bin_width= 0.001;
bin_number(x) = floor(x/bin_width)
rounded(x) = bin_width*(bin_number(x)+0.5)
plot 't12.txt' using (rounded($1)):(1.0) smooth frequency with boxes title '{/Symbol q}_{12}' 

set output 't13.eps'
set xlabel 'angle in radians'
set ylabel 'freq'
set border 3
set style fill solid 1.0 noborder
bin_width= 0.001;
bin_number(x) = floor(x/bin_width)
rounded(x) = bin_width*(bin_number(x)+0.5)
plot 't13.txt' using (rounded($1)):(1.0) smooth frequency with boxes title '{/Symbol q}_{13}' 

set output 't23.eps'
set xlabel 'angle in radians'
set ylabel 'freq'
set border 3
set style fill solid 1.0 noborder
bin_width= 0.001;
bin_number(x) = floor(x/bin_width)
rounded(x) = bin_width*(bin_number(x)+0.5)
plot 't23.txt' using (rounded($1)):(1.0) smooth frequency with boxes title '{/Symbol q}_{23}' 
set terminal x11
