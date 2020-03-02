#!/bin/bash
TEST_NUMBER=$((`ls test/input -l | wc -l`-1))
DESCRIPTIONS=test/descriptions/desc_
OUTS=test/output/out_
INS=test/input/in_
DATAS=test/data/data_

# Print description to all tests.
if [ -f "$DESCRIPTIONS"main.txt ]; then
    echo -e "\033[1;35m"
    cat "$DESCRIPTIONS"main.txt
    echo -e "\033[0;29m"
fi

for i in $(seq 1 $TEST_NUMBER)
do
    SUFFIX=$i
    if [[ $i -lt 10 ]]; then
        SUFFIX=0$i
    fi 

    # Print description for the test, if it exists.
    if [ -f "$DESCRIPTIONS""$SUFFIX".txt ]; then
        echo -e "\033[1;35m"
        cat "$DESCRIPTIONS""$SUFFIX".txt
        echo -e "\033[0;29m"
    fi

    # Print input and data.
    if [ -f "$INS""$SUFFIX".txt ]; then
        echo
        echo -e "\033[1;33mInput:"
        cat "$INS""$SUFFIX".txt
    fi

    if [ -f "$DATAS""$SUFFIX".txt ]; then
        echo
        echo "Data:"
        cat "$DATAS""$SUFFIX".txt 
        echo -e "\033[0;29m"
    fi

    ./app.exe "$DATAS""$SUFFIX".txt autotest <"$INS""$SUFFIX".txt >test/out.txt
    
    echo -e "\033[1;36mYour answer:"
    cat test/out.txt

    if [ -f "$OUTS""$SUFFIX".txt ]; then
        echo -e "\033[1;32mRight answer:"
        echo
        cat "$OUTS""$SUFFIX".txt
        echo -e "\033[0;29m"
    fi
    
done

rm test/out.txt
