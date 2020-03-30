Program PresidentRecords (input, output);
    
    CONST
        SPACE_INT = 0; { integer value of blank space. }
        SPACE_CHAR = ' '; { integer value of blank space. }
        END_MARKER = -1; { marker at the end of the president records as well as the list of years. }
        MAX_RECORDS = 20; { maximum number of records the program reads from the input. }
        MAX_NAME_LENGTH = 12; { maximum length a name array can have. }
        DOT = '.';
    TYPE
        name_array = PACKED ARRAY [0..MAX_NAME_LENGTH-1] of char;
        president_record = RECORD
            start_year: integer;
            end_year: integer;
            first_name: name_array;
            middle_name: name_array;
            last_name: name_array;
            END;
    VAR
        president_array: array of president_record; { length set to MAX_RECORDS in main. }
        current: integer = 0; { keeps track of latest president record being read. }
        end_of_list: boolean = FALSE; { used to keep track of the end of the input list of president records. }


{*************READ START YEAR*************}
{ Parameters: index of the array for the latest president record whose start year needs to be read. }
{* Output: Returns true if the end of the list of president records is detected.
    Otherwise, returns false. *}
{* Post condition: start_year variable for current_index record in the array is initialized. *}
FUNCTION read_start_year (current_index: integer): BOOLEAN;
    VAR
        num: integer = 0;
    BEGIN
        REPEAT
            read(num);
            IF num = END_MARKER THEN
            BEGIN
                read_start_year := true;
                BREAK;
            END
            ELSE
            BEGIN
                IF num <> SPACE_INT THEN
                BEGIN
                    president_array[current_index].start_year := num;
                    read_start_year := false;
                END;
            END;
        UNTIL num <> SPACE_INT;
    END;

{*************READ END YEAR*************}
{ Parameters: index of the array for the latest president record whose end year needs to be read. }
{* Post condition: end_year variable for current_index record in the array is initialized. *}
PROCEDURE read_end_year (current_index: integer);
    VAR
        num: integer = 0;
    BEGIN
        REPEAT
            read(num);
            IF num <> SPACE_INT THEN
            BEGIN
                president_array[current_index].end_year := num;
            END;
        UNTIL num <> SPACE_INT;
    END;

{*************READ NAME*************}
{ * Parameters: arr: reference to the name array that needs to be populated.
    position: index from where the array needs to continue being populated.
    If called to read entire first/last name, position = 0;
    If called to read last name from the read_middle_and_last_name proc when a middle name does not exist, position = 2,
    because two chars have already been read. * }
{* Post condition: The name_array passed by reference is populated. *}
PROCEDURE read_name (VAR arr: name_array; position: integer);
    VAR
        ch: char = ' ';
        name_index: integer = 0;
    BEGIN
        name_index := position;
        REPEAT
            read(ch);
        UNTIL ch <> SPACE_CHAR;
        
        arr[name_index] := ch;
        name_index := name_index + 1;
        
        REPEAT
            read(ch);
            IF ch <> SPACE_CHAR THEN
            BEGIN
                arr[name_index] := ch;
                name_index := name_index + 1;
            END;
        UNTIL (ch = SPACE_CHAR) OR eoln;
    END;


{*************READ MIDDLE AND LAST NAME*************}
{ Parameters: index of the array for the latest president record whose middle name needs to be read. }
{ Checks if a middle name exists. If it does, then populates the middle name of the president_array[current_index]. }
{ If it does not, then it populates the first two chars of the president_array[current_index].last_name }
{ Post condition: Calls read_name function to finish reading the last name. }
PROCEDURE read_middle_and_last_name (current_index: integer);
    VAR
        i: integer = 0;
        ch: char = ' ';
        next_ch: char = ' ';
    BEGIN
        REPEAT
            read(ch);
        UNTIL ch <> SPACE_CHAR;
        
        read(next_ch);
        IF next_ch = DOT THEN
        BEGIN
            president_array[current_index].middle_name[i] := ch;
            i := i + 1;
            president_array[current_index].middle_name[i] := next_ch;
            i := i + 1;
            read(ch);
            WHILE (ch <> SPACE_CHAR) DO
            BEGIN
                president_array[current_index].middle_name[i] := ch;
                i := i + 1;
                read(ch);
            END;
            read_name (president_array[current_index].last_name, 0);
        END
        
        ELSE
        BEGIN
            president_array[current_index].last_name[i] := ch;
            i := i + 1;
            president_array[current_index].last_name[i] := next_ch;
            i := i + 1;
            read_name (president_array[current_index].last_name, 2);
        END;
    END;

{*************PRINT PRESIDENT RECORDS*************}
{ Parameters: Number of president records that are stored in the array. }
{* Post condition: The records are printed. *}
PROCEDURE print_president_records (number_of_presidents_recorded: integer);
    VAR
        i: integer = 0;
    BEGIN
        WHILE (i < number_of_presidents_recorded) DO
        BEGIN
            write(president_array[i].start_year:4, ' ');
            write(president_array[i].end_year:4, ' ');
            write(president_array[i].first_name, ' ');
            write(president_array[i].middle_name, ' ');
            writeln(president_array[i].last_name);
            i := i + 1;
        END;
    END;

{*************FIND PRESIDENTS*************}
{ Sub-procedure called by search_president_by_year proc. }
{ Parameters: Year for which the president needs to be found. }
{* Post condition: If any president(s) matching the year is found,
        then the first, middle and last names are printed at the output. *}
PROCEDURE find_presidents(number_of_presidents_recorded, year: integer);
    VAR
        i: integer = 0;
        president_found: Boolean = false;
    BEGIN
        WHILE (i < number_of_presidents_recorded) DO
        BEGIN
            IF ((year > president_array[i].start_year) AND (year < president_array[i].end_year)) OR (year = president_array[i].start_year) OR (year = president_array[i].end_year) THEN
            BEGIN
                president_found := true;
                write(year, ' ');
                write(president_array[i].first_name, ' ');
                write(president_array[i].middle_name, ' ');
                writeln(president_array[i].last_name);
            END;
            i := i + 1;
        END;
        IF president_found = false THEN
        BEGIN
            writeln(year, ' No President records found for this year.');
        END;
    END;

{*************SEARCH PRESIDENTS BY YEAR*************}
{ Parameters: Number of president records that are stored in the array. }
{* Post condition: If any presidents matching any of the years read from the input are found,
        then the first, middle and last names are printed at the output using the find_presidents proc. *}
PROCEDURE search_president_by_year(number_of_presidents_recorded: integer);
    VAR
        num: integer = 0;
    BEGIN
        REPEAT
            read(num);
            IF (num <> SPACE_INT) AND (num <> -1) THEN
            BEGIN
                find_presidents(number_of_presidents_recorded, num);
            END;
        UNTIL eof;
    END;

{*************MAIN PROGRAM*************}
BEGIN
    setlength(president_array, MAX_RECORDS);
    
    { read the president records. }
    WHILE current < MAX_RECORDS DO
    BEGIN
        { read the start year of the term. }
        end_of_list := read_start_year(current);
        IF end_of_list = TRUE THEN BREAK
        ELSE
        BEGIN
            { read the end year of the term. }
            read_end_year(current);
            { read the first name. }
            read_name(president_array[current].first_name, 0);
            { read the middle (if it exists) and last names. }
            read_middle_and_last_name(current);
            { increment the index for the array. }
            current := current + 1;
        END;
    END;
    {print the president records. }
    print_president_records(current);

    { search for and print presidents matching the list of years read from input. }
    search_president_by_year(current);
END.