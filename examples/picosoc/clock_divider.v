
/*
A clock divider in Verilog, using the cascading
flip-flop method.
*/
`include "mux2to1.v"
`include "bytemux2to1.v"
`include "bytearbiter.v"
`include "arbiterslice.v"
`include "dlatch.v"


module clock_divider(
  input clk,
  input reset,
  output reg clk_div2,
  output reg clk_div4,
  output reg clk_div8,
  output reg clk_div16,
  output reg [7:0] OUT_8bits,
  output reg OUT_8bits0,
  output reg OUT_8bits1,
  output reg OUT_8bits2,
  output reg OUT_8bits3,
  output reg OUT_8bits4,
  output reg OUT_8bits5,
  output reg OUT_8bits6,
  output reg OUT_8bits7
  
);

  // simple ripple clock divider
  
  always @(posedge clk)
    clk_div2 <= ~clk_div2;

  always @(posedge clk_div2)
    clk_div4 <= ~clk_div4;

  always @(posedge clk_div4)
    clk_div8 <= ~clk_div8;

  always @(posedge clk_div8)
    clk_div16 <= ~clk_div16;

  always @(posedge clk)
  begin
    OUT_8bits <= 8'h5;
    //OUT_8bits0 <= OUT_8bits[0];
    OUT_8bits1 <= OUT_8bits[1];
    OUT_8bits2 <= OUT_8bits[2];
    OUT_8bits3 <= OUT_8bits[3];
    OUT_8bits4 <= OUT_8bits[4];
    OUT_8bits5 <= OUT_8bits[5];
    OUT_8bits6 <= OUT_8bits[6];
    OUT_8bits7 <= OUT_8bits[7];
  end
  
  
//  mux2to1 muxy(.clk(clk), .IN_A(clk_div4), .IN_B(clk_div8),.IN_SELECT(clk_div16), .OUT(OUT_8bits0));
  mux2to1 muxy(.clk(clk), .IN_0(0), .IN_1(1),.IN_SELECT(clk_div16), .OUT(OUT_8bits0));  
  
  
endmodule
