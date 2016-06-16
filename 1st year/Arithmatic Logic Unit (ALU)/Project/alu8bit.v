module ALU8bit (A,B, Cin, Sel, F, C, Z, S, V);
	input [7:0] A;
	input [7:0] B;
	input Cin;
	input [2:0] Sel;
	output [7:0] F;
	output C,Z,S,V;
	wire w;
	wire [3:0] x;
	fourbittest four_one (A[3:0],B[3:0],Cin,0,Sel,F[3:0],x[1:0],w);
	fourbittest four_two (A[7:4],B[7:4],w,w,Sel,F[7:4],x[3:2],C);
	assign V = x[3];
	assign Z= ~(F[0]|F[1]|F[2]|F[3]|F[4]|F[5]|F[6]|F[7]);
	assign S= F[7];
endmodule
