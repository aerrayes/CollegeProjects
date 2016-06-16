module one_bit_subtraction(A,B,Cin,F,Cout);
input A,B,Cin;
output F,Cout;
full_adder y(A,~B,Cin,F,Cout);
endmodule

