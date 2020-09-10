program gcd(void);
var 
    x, y : integer;
function gcd(a, b : integer) : integer;
    begin
        if a mod b = 0 then
            gcd := b
        else
            gcd := gcd(b, a mod b)
    end;
begin
    x := 24;
    y := 36;
    writeln(gcd(x,y));
end.