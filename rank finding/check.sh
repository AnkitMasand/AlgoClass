./randrank < rankip3 > rankip3out
read -a ArrOut3Det < rankip3out
head -2 rankip3 > rankip3qs
./quicksort1 < rankip3qs > rankip3sorted
read -a ArrOut3QS < rankip3sorted
tail -1 rankip3 > ranktobefound
read -a Ranks < ranktobefound
elems=$(head -1 rankip3)
for i in $(seq 0 $elems)
do
	if [ ${ArrOut3QS[$elems-${Ranks[$i]}]} -eq ${ArrOut3Det[$i]} ]
	then 
		#echo ${ArrOut3QS[$elems-${Ranks[$i]}]} 
		echo "correct"
	else
		echo "incorrect"
		echo ${ArrOut3QS[$elems-${Ranks[$i]}]} 
                echo ${ArrOut3Det[$i]}
	fi
done
