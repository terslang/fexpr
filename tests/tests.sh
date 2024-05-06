# path to fexpr binary. Just use "fexpr" if installed to path
fexpr="../build/fexpr"

# Test cases for expr compatibility tests
expr_compat_cases=("1 + 1" "0 - 1" "3 + 5" "255 - 255")

echo "---------- Start Testing ----------"

echo "Starting expr compatibility tests"
for input in "${expr_compat_cases[@]}"
do
    expr_result=$(expr $input)
    fexpr_result=$($fexpr $input)

    if [[ $expr_result != $fexpr_result ]]
    then
        echo "Compatibility test failed for '$input'. expr result is '$expr_result' and fexpr result is '$fexpr_result'"
        exit 1
    fi
    
    printf "."
done

printf "\nTesting Done!\n"
