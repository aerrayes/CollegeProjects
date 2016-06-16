module fourbit(A,B,Cin,l,S,F,V,Cout);
input [3:0]A;
input [3:0]B;
input Cin,l;
input [2:0]S;
output [3:0]F;
output [1:0]V;
output Cout;
wire i;
twobit two_one([1:0]A,[1:0]B,Cin,l,S,[1:0]F,V[0],i);
twobit two_two([3:2]A,[3:2]B,i,i,S,[3:2]F,V[1],Cout);
endmodule
