program HelloWorld;
var
counter : integer =10;

begin
    repeat
        writeln('Hello World!');
        counter := counter -1;
    until counter = 0;
end.