module twobittest (A,B,Cin,l,S,F,V,Cout);
input [1:0] A;
input [1:0] B;
input Cin,l;
input [2:0] S;
output [1:0] F;
output Cout,V;
wire x;
onebittest one_one(A[0],B[0],Cin,l,S,F[0],x);
onebittest one_two (A[1],B[1],x,x,S,F[1],Cout);
assign V = x ^ Cout;
endmodule

