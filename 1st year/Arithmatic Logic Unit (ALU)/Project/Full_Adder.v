module full_adder (a,b,c,sum,carry);
	input a,b,c;
	wire s1,c1;
	output sum, carry;
	half_adder h1 (a,b,s1,c1);
	half_adder h2 (s1,c,sum,c2);
	assign carry = c1 | c2;
endmodule
