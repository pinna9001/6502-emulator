tests=(memory lda ldx ldy sta stx sty transfer stack decrement increment adc)

for test in "${tests[@]}"
do
    echo "Test: "$test
    make "run_"$test"_test"
    if [ $? -gt 0 ]
    then
        echo "Test failed"
        exit 1
    fi
done