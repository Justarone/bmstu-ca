#!/bin/bash
TEST_NUMBER=$(ls -l | grep in | wc -l)
for i in $(seq 1 $TEST_NUMBER)
do
    SUFFIX=$i
    if [[ $i -lt 10 ]]; then
        SUFFIX=0$i
    fi 

    ../app.exe < in_$SUFFIX.txt > out.txt

    if [ $(diff out.txt out_$SUFFIX.txt >/dev/null) ]; then
        echo "Test ${i}: FAILED."
    else
        echo "Test ${i}: OK."
    fi
done
