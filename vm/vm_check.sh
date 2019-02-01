#!/bin/sh

OWN_DIR=.
ORIG_DIR=source
NAME=corewar
COR_DIR=source/binary
OUR_RES=
ORIG_RES=
OWN_RET=
OK='\033[092m[ OK ]\033[0m'
KO='\033[091m[ KO ]\033[0m'
COUNTER=0

get_error()
{
	if (( $1 == $((128 + 6)) )); then
		echo "\033[091m[ ABRT ]\033[0m"
	elif (( $1 == $((128 + 10)) )); then
		echo "\033[091m[ BUS ]\033[0m"
	elif (( $1 == $((128 + 11)) )); then
		echo "\033[091m[ SEGV ]\033[0m"
	elif (( $1 == $((128 + 4)) )); then
		echo "\033[091m[ ILL ]\033[0m"
	elif (( $1 == $((128 + 8)) )); then
		echo "\033[091m[ FPE ]\033[0m"
	elif (( $1 == $((128 + 13)) )); then
		echo "\033[091m[ PIPE ]\033[0m"
	elif (( $1 == -1)); then
		echo $KO
	elif (( $1 == 0)); then
		echo $OK
	fi
}

for pl_1 in $(find $COR_DIR -name '*.cor'); do
	for pl_2 in $(find $COR_DIR -name '*.cor'); do
		for pl_3 in $(find $COR_DIR -name '*.cor'); do
			echo "\033[093m" $pl_1 '\t\t' $pl_2 '\t\t' $pl_3 "\033[0m"
			OUR_RES=$( $OWN_DIR/$NAME $pl_1 $pl_2 $pl_3)
			OWN_RET=$?
			if [ $OWN_RET != 0 ]; then
				get_error OWN_RET
				COUNTER=$((COUNTER+1))
				echo "\033[091m$OWN_DIR/$NAME $pl_1 $pl_2 $pl_3\033[0m"
			else
				OUR_RES=$(grep "has won" <<< "$OUR_RES" | awk -F\" '{print $2}')
				ORIG_RES=$($ORIG_DIR/$NAME $pl_1 $pl_2 $pl_3 | grep "has won" | awk -F\" '{print $2}')
				if [ "$OUR_RES" != "$ORIG_RES" ]; then
					echo "\033[091mFAIL\033[0m"
					COUNTER=$((COUNTER+1))
					echo "\033[091m$OWN_DIR/$NAME $pl_1 $pl_2 $pl_3\033[0m"
				fi
			fi
		done
	done
done

if [ $COUNTER == 0 ]; then
	echo "\033[092mAll rigth!\033[0m"
fi
