`ifndef mux2to1
`define mux2to1

  module mux2to1(
    input clk,
    input IN_0,
    input IN_1,
    input IN_SELECT,
    output reg OUT
  );
    


    always @(posedge clk)
      OUT <= IN_SELECT ? IN_1 : IN_0;


  endmodule

`endif


