#Program to check output of rankfinding sols by correlating to quicksort
#Script will have to be changed to at first line of code to correspond to prob to be checked!
./rank_find_v3 < rankip1 > rankip1out
read -a ArrOut1Det < rankip1out
head -2 rankip1 > rankip1qs
./QuickSort < rankip1qs > rankip1sorted
read -a ArrOut1QS < rankip1sorted
tail -1 rankip1 > ranktobefound
read -a Ranks < ranktobefound
elems=$(head -1 rankip1)
for i in $(seq 0 $elems)
do
	if [ ${ArrOut1QS[$elems-${Ranks[$i]}]} -eq ${ArrOut1Det[$i]} ]
	then 
		#echo ${ArrOut1QS[$elems-${Ranks[$i]}]} 
		echo "correct"
	else
		echo "incorrect"
		echo ${ArrOut1QS[$elems-${Ranks[$i]}]} 
                echo ${ArrOut1Det[$i]}
	fi
done
