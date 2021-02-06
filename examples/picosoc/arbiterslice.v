`ifndef arbiterslice
`define arbiterslice

`include "mux2to1.v"



  module arbiterslice(
    input clk,
    input [3:0] IN,
    
    
    input IN_SELECT,
    output reg [1:0] OUT_SELECT
  );

    mux2to1 mux0(.clk(clk), .IN_0(IN[0]), .IN_1(IN[1]),.IN_SELECT(IN_SELECT), .OUT(OUT_SELECT[0]));  
    mux2to1 mux1(.clk(clk), .IN_0(IN[2]), .IN_1(IN[3]),.IN_SELECT(IN_SELECT), .OUT(OUT_SELECT[1]));  

   
   // always @(posedge clk)
     // OUT <= IN_SELECT ? IN_1 : IN_0;
      
      
  endmodule


`endif
