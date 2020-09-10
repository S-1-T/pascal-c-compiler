program test(nothing);
var a:boolean;
b:integer;c:real;d:char;e :array[1..10] of integer;f :array[1..10] of integer;

begin
  a :=false;
  b :=3;
  d :='a';
  c :=1.1;
  b := 1+c;

  a := b;
  a := c;
  a := d;
  b := c;
  b := d;
  c := d;

  a :=e;
  e :=a;
  e :=f
end.
