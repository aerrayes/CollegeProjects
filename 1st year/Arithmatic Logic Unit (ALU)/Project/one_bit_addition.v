module one_bit_addition (A,B,Cin,F,Cout);
input A,B,Cin;
output F,Cout;
full_adder x (A,B,Cin,F,Cout);
endmodule 
