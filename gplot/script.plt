# set some parameters and fit functions
set terminal png size 2000,1500
set grid
set border 3
#set log scale where appropriate nad plot each data file in a corresponding
#png file
#plot "data/dataH4_err.png"
set output "data/ueb6_1_1.png"
plot "data/ueb6_1_1.dat" using 1:2 with lines linewidth 7,\
     "data/ueb6_1_1.dat" using 1:3 with lines linewidth 4
set output "data/ueb6_1_1err.png"
set logscale y
plot "data/ueb6_1_1.dat" using 1:4 with lines linewidth 3
unset logscale y
set output "data/ueb6_2_1.png"
plot "data/ueb6_2_1.dat" using 1:2 with lines linewidth 7,\
     "data/ueb6_2_1.dat" using 1:3 with lines linewidth 4
set output "data/ueb6_2_1err.png"
plot "data/ueb6_2_2.dat" using 1:2 with lines linewidth 3