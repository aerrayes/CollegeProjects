module mux ( S , w , f)
input [2:0] S ;
input [7:0] w ;
output f;
assign F = ( S[2] & S[1] & S[0] & w[7]) |
( S[2] & S[1] & ~S[0] & w[6]) |
( S[2] & ~S[1] & S[0] & w[5]) |
( S[2] & ~S[1] & ~S[0] & w[4]) |
( ~S[2] & S[1] & S[0] & w[3]) |
( ~S[2] & S[1] & ~S[0] & w[2]) |
( ~S[2] & ~S[1] & S[0] & w[1]) |
( ~S[2] & ~S[1] & ~S[0] & w[0]) ;
endmodule
