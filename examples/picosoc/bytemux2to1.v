`ifndef bytemux2to1
`define bytemux2to1

`include "mux2to1.v"



  module bytemux2to1(
    input clk,
    input [7:0] IN_0,
    input [7:0] IN_1,
    input IN_SELECT,
    output reg [7:0] OUT
  );


    always @(posedge clk)
      OUT <= IN_SELECT ? IN_1 : IN_0;


  endmodule


`endif
