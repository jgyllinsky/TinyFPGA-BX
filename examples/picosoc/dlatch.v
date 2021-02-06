
`ifndef dlatch
`define dlatch



module dlatch(
    input clk,
    input D,
    output reg Q
  );

   always @(posedge clk)
     Q <= D;
      
      
endmodule
`endif
