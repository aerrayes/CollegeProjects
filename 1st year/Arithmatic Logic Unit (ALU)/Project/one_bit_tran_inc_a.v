module one_bit_tran_inc_A(A,Cin,F,Cout);
input A,Cin;
output F,Cout;
assign F=A^Cin;
assign Cout=A&Cin;
endmodule

