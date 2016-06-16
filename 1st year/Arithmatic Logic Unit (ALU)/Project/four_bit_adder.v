module four_bit_adder (a,b,cin,z,carry);
	input [3:0] a ;
	input [3:0] b ;
	input cin;
	output [3:0] z ;
	output carry ;
	wire [3:0] w;
	full_adder f1 (a[0],b[0],cin,z[0],w[0]);
	full_adder f2 (a[1],b[1],w[0],z[1],w[1]);
	full_adder f3 (a[2],b[2],w[1],z[2],w[2]);
	full_adder f4 (a[3],b[3],w[2],z[3],w[3]);
	assign carry = w[3];
endmodule
