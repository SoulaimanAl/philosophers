#!/bin/bash

msg="how to use\n./philo_caclulator   philo_count   time_to_eat   time_to_sleep\nResult: mini_time_to_die\n./philo_caclulator 10 200 200\n410"
a=$1
b=$2
c=$3
if [ -z "$a" ]
then
	echo -e "$msg"
exit
fi

if [ -z "$b" ]
then
	echo -e "$msg"
exit
fi

if [ -z "$c" ]
then
	echo -e "$msg"
exit
fi

if [[ $((a % 2)) == 0 ]]
then
	if [[ $(( (b * 2) + 10 )) -gt $((b + c + 10 )) ]]
	then
		echo -e "Should not die: $(( (b * 2) + 10 ))\nShould die: $(( (b * 2) - 1 ))" 
	else 
		echo -e "Should not die: $(( b + c + 10 ))\nShould die: $(( b + c - 1 ))";
	fi
else
	if [[ $(( (b * 3) + 10 )) > $(( b + c + 10 )) ]]
	then
		echo -e "Should not die: $(( (b * 3) + 10 )) => $((b * 4))\nShould die: $(( (b * 3) - 1 ))"
	else 
		echo -e "Should not die: $(( b + c + 10 )) => $(( b * 2 + c ))\nShould die: $(( b + c - 1 ))"
	fi
fi

#ph1 0-200 200-300  300  ->310 410
#ph2 200-400