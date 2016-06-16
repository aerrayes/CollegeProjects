module fourbittest(A,B,Cin,l,S,F,V,Cout);
input [3:0]A;
input [3:0]B;
input Cin,l;
input [2:0]S;
output [3:0]F;
output [1:0]V;
output Cout;
wire i;
twobittest two_one(A[1:0],B[1:0],Cin,l,S,F[1:0],V[0],i);
twobittest two_two(A[3:2],B[3:2],i,i,S,F[3:2],V[1],Cout);
endmodule
