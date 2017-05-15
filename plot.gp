set autoscale
set key autotitle columnhead
set xtics rotate
set terminal qt persist enhanced
set format y '%.0f'
set format x '%.0f'
set title TITLE
plot for [i=0:MAX] 'plot_cpu'.CPU_ID.'_'.i.'.txt' with steps lw 4
