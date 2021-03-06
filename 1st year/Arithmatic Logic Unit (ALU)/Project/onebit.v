module onebit(A,B,Cin,S,F,Cout);
	input A,B,Cin;
	input [2:0] S;
	output F;
	output Cout;
	wire [7:0] w;
	wire [3:0] z;
	half_adder inc1 (A,Cin,w[0],z[0]);
	//one_bit_tran_inc_A inc1 (A , Cin , w[0] , Cout [0]);
	//one_bit_addition add1 ( A , B , Cin , w[1] , Cout[1]);
	//one_bit_subtraction sub1 ( A, B , Cin , w[2] , Cout[2]);	
	Full_adder f1 (A,B,Cin,w[1],z[1]);
	Full_adder f2 (A,~B,Cin,w[2],z[2]);
	Decrement d1 (A,Cin,w[3],z[3]);
	assign w[4] = A & B;
	assign w[5] = A | B;
	assign w[6] = A ^ B;
	assign w[7] = ~A;
	
assign F = ( S[2] & S[1] & S[0] & w[7]) |
( S[2] & S[1] & ~S[0] & w[6]) |
( S[2] & ~S[1] & S[0] & w[5]) |
( S[2] & ~S[1] & ~S[0] & w[4]) |
( ~S[2] & S[1] & S[0] & w[3]) |
( ~S[2] & S[1] & ~S[0] & w[2]) |
( ~S[2] & ~S[1] & S[0] & w[1]) |
( ~S[2] & ~S[1] & ~S[0] & w[0]) ;

assign Cout = (S[1] & S[0] & z[3]) |
(S[1] & ~S[0] & z[2]) |
(~S[1] & S[0] & z[1]) |
(~S[1] & ~S[0] & z[0]) ;

endmodule
