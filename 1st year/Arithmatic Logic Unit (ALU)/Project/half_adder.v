module half_adder(a,b,sum,carry);
	input a,b;
	output sum, carry;
	assign sum = a^b; // sum bit
	assign carry = (a&b) ; //carry bit
endmodule

