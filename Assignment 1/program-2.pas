PROGRAM arrayReaderAndMerger (input, output);
CONST
    SPACE = 0; { used to deal with number separating space. }
    MAX_ARR_SIZE = 20; { maximum size that the integer arrays can have. }

TYPE
    numbers = PACKED ARRAY of integer;

VAR
    first_array: numbers; { array used to store the first line of integers. }
    second_array: numbers; { array used to store the second line of integers. }
    merged_array: numbers; { array used to store the merged integers. }
    first_array_size: integer;
    second_array_size: integer;


{*************READ ARRAY*************}
{*Parameter: array of integers, by reference*}
{*Output: number of integers populated in the array*}
FUNCTION read_array (VAR arr: numbers): integer;
    VAR
        num: integer; { temporary variable to store a read value. }
        counter: integer = 0; { used to keep track of the number of integers stored in an array. }
    
    BEGIN
        REPEAT { keep reading until eoln or until MAX_ARR_SIZE numbers have been read. }
            read(num);
            IF (num <> SPACE) THEN { use the read value if it's not a space. }
            BEGIN
                arr[counter] := num;
                counter := counter + 1;
            END;
        UNTIL (counter > MAX_ARR_SIZE) OR eoln;
        read_array := counter;
    END;



{*************PRINT ARRAY*************} 
{*Parameters: array of integers, by reference and size of the array, by value*}
PROCEDURE print_array (VAR arr: numbers; counter: integer);
    VAR
        i: integer = 0;
    BEGIN
        FOR i := 0 TO (counter - 1) DO write(arr[i], ' ');
        writeln; { insert an eoln. }
    END;



{*************MERGE ARRAYS*************}
{*Parameters: three arrays of integers, by reference and the sizes of the two arrays to be merged, by value*}
{*Output: the third array is populated with the sorted, merged values of the first two arrays*}
PROCEDURE merge_arrays (VAR first_array, second_array, merged_array: numbers; first_array_size, second_array_size: integer);
    VAR
        i, j, k: integer;
    BEGIN
        i := 0;
        j := 0;
        k := 0;
        WHILE (i < first_array_size) AND (j < second_array_size) DO
        BEGIN
            IF first_array[i] < second_array[j] THEN
            BEGIN
                merged_array[k] := first_array[i];
                k := k + 1;
                i := i + 1;
            END
            ELSE
            BEGIN
                merged_array[k] := second_array[j];
                k := k + 1;
                j := j + 1;                
            END;
        END;
        
        WHILE i < first_array_size DO
        BEGIN
            merged_array[k] := first_array[i];
            k := k + 1;
            i := i + 1;
        END;
        
        WHILE j < second_array_size DO
        BEGIN
            merged_array[k] := second_array[j];
            k := k + 1;
            j := j + 1;
        END;
    END;



{*************MAIN PROGRAM*************}   
BEGIN {program}
    setlength(first_array, MAX_ARR_SIZE);
    setlength(second_array, MAX_ARR_SIZE);
    setlength(merged_array, 2*MAX_ARR_SIZE);

    { read the arrays. }
    first_array_size := read_array(first_array);
    second_array_size := read_array(second_array);

    { print the arrays. }    
    print_array(first_array, first_array_size);
    print_array(second_array, second_array_size);

    { merge the arrays. }    
    merge_arrays(first_array, second_array, merged_array, first_array_size, second_array_size);

    { print the merged array. }
    print_array(merged_array, first_array_size + second_array_size);

END. {program}