
`ifndef bytearbiter
`define bytearbiter

`include "arbiterslice.v"



  module bytearbiter(
    input clk,
    input [7:0] IN,
    output reg OUT
  );


    wire [1:0] s0_wire;
    reg [3:0] s0_clk;
    
    assign s0_clk[0] = clk;
    assign s0_clk[1] = clk;
    assign s0_clk[2] = clk;
    assign s0_clk[3] = clk;
    
    
    
    arbiterslice s0(.clk(clk),.IN(s0_clk),.IN_SELECT(IN[0]),.OUT_SELECT(s0_wire));

    wire [1:0] s1_wire;
    arbiterslice s1(.clk(clk),.IN(s0_wire),.IN_SELECT(IN[1]),.OUT_SELECT(s1_wire));
    
    wire [1:0] s2_wire;
    arbiterslice s2(.clk(clk),.IN(s1_wire),.IN_SELECT(IN[2]),.OUT_SELECT(s2_wire));
    
    wire [1:0] s3_wire;
    arbiterslice s3(.clk(clk),.IN(s2_wire),.IN_SELECT(IN[3]),.OUT_SELECT(s3_wire));
    
    wire [1:0] s4_wire;
    arbiterslice s4(.clk(clk),.IN(s3_wire),.IN_SELECT(IN[4]),.OUT_SELECT(s4_wire));
    
    wire [1:0] s5_wire;
    arbiterslice s5(.clk(clk),.IN(s4_wire),.IN_SELECT(IN[5]),.OUT_SELECT(s5_wire));
    
    wire [1:0] s6_wire;
    arbiterslice s6(.clk(clk),.IN(s5_wire),.IN_SELECT(IN[6]),.OUT_SELECT(s6_wire));
    
    wire [1:0] s7_wire;
    arbiterslice s7(.clk(clk),.IN(s6_wire),.IN_SELECT(IN[7]),.OUT_SELECT(s7_wire));
    
    dlatch dl( .clk(clk),.D(s7_wire),.Q(OUT));
    

    
  endmodule

`endif

