for h in explicit_enum gradient_descent taboo simulated_annealing;
do
    for n in swap sweep;
    do
	rm results/$h.$n.result -f
	for i in 4 5 10 15 17 20 ;#21 22 23 24 25 30 50 100 500 1000;
	do
	    echo $h $n $i
	    timeout 3m ./partition $h $n graphs/$i.txt | sed -r 's#^(.+)$#'$i' \1#g'  >> results/$h.$n.result
	    echo plot \'results/$h.$n.result\' >> results.plot
	done
    done
done
