declare -a arr
declare -a ind
declare -a rows
declare -a cols
if [[ $# -gt 0 ]]
then
	time=$1
else
	time=0.01
fi
i=0
row=0
col=0
while IFS= read -r -N 1 CHAR; do
    if [[ "$CHAR" != $'\n' && "$CHAR" != ' ' ]]
	then
    	arr+=($(echo "$CHAR"))
    	ind+=($i)
    	i=$(($i+1))
    	rows+=($row)
    	cols+=($col)
    	fi
   if [[ "$CHAR" = $'\n' ]]
	then
	row=$(($row+1))
	col=0
	else
	col=$(($col+1))
	fi
done
ind=( $(shuf -e "${ind[@]}") )
tput clear
for j in "${ind[@]}"; do
	tput cup ${rows[$j]} ${cols[$j]}
	echo ${arr[$j]}
	sleep "$time"
done
tput cup $row 0
