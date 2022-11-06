module RegisterFile(
  input         clock,
  input         reset,
  input  [3:0]  io_aSel,
  input  [3:0]  io_bSel,
  input  [31:0] io_writeData,
  input  [3:0]  io_writeSel,
  input         io_writeEnable,
  output [31:0] io_a,
  output [31:0] io_b
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
  reg [31:0] _RAND_2;
  reg [31:0] _RAND_3;
  reg [31:0] _RAND_4;
  reg [31:0] _RAND_5;
  reg [31:0] _RAND_6;
  reg [31:0] _RAND_7;
  reg [31:0] _RAND_8;
  reg [31:0] _RAND_9;
  reg [31:0] _RAND_10;
  reg [31:0] _RAND_11;
  reg [31:0] _RAND_12;
  reg [31:0] _RAND_13;
  reg [31:0] _RAND_14;
  reg [31:0] _RAND_15;
`endif // RANDOMIZE_REG_INIT
  reg [31:0] registers_0; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_1; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_2; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_3; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_4; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_5; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_6; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_7; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_8; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_9; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_10; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_11; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_12; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_13; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_14; // @[RegisterFile.scala 20:37]
  reg [31:0] registers_15; // @[RegisterFile.scala 20:37]
  wire [31:0] _GEN_33 = 4'h1 == io_aSel ? registers_1 : registers_0; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_34 = 4'h2 == io_aSel ? registers_2 : _GEN_33; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_35 = 4'h3 == io_aSel ? registers_3 : _GEN_34; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_36 = 4'h4 == io_aSel ? registers_4 : _GEN_35; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_37 = 4'h5 == io_aSel ? registers_5 : _GEN_36; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_38 = 4'h6 == io_aSel ? registers_6 : _GEN_37; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_39 = 4'h7 == io_aSel ? registers_7 : _GEN_38; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_40 = 4'h8 == io_aSel ? registers_8 : _GEN_39; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_41 = 4'h9 == io_aSel ? registers_9 : _GEN_40; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_42 = 4'ha == io_aSel ? registers_10 : _GEN_41; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_43 = 4'hb == io_aSel ? registers_11 : _GEN_42; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_44 = 4'hc == io_aSel ? registers_12 : _GEN_43; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_45 = 4'hd == io_aSel ? registers_13 : _GEN_44; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_46 = 4'he == io_aSel ? registers_14 : _GEN_45; // @[RegisterFile.scala 28:8]
  wire [31:0] _GEN_49 = 4'h1 == io_bSel ? registers_1 : registers_0; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_50 = 4'h2 == io_bSel ? registers_2 : _GEN_49; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_51 = 4'h3 == io_bSel ? registers_3 : _GEN_50; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_52 = 4'h4 == io_bSel ? registers_4 : _GEN_51; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_53 = 4'h5 == io_bSel ? registers_5 : _GEN_52; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_54 = 4'h6 == io_bSel ? registers_6 : _GEN_53; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_55 = 4'h7 == io_bSel ? registers_7 : _GEN_54; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_56 = 4'h8 == io_bSel ? registers_8 : _GEN_55; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_57 = 4'h9 == io_bSel ? registers_9 : _GEN_56; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_58 = 4'ha == io_bSel ? registers_10 : _GEN_57; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_59 = 4'hb == io_bSel ? registers_11 : _GEN_58; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_60 = 4'hc == io_bSel ? registers_12 : _GEN_59; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_61 = 4'hd == io_bSel ? registers_13 : _GEN_60; // @[RegisterFile.scala 29:8]
  wire [31:0] _GEN_62 = 4'he == io_bSel ? registers_14 : _GEN_61; // @[RegisterFile.scala 29:8]
  assign io_a = 4'hf == io_aSel ? registers_15 : _GEN_46; // @[RegisterFile.scala 16:8 RegisterFile.scala 28:8]
  assign io_b = 4'hf == io_bSel ? registers_15 : _GEN_62; // @[RegisterFile.scala 17:8 RegisterFile.scala 29:8]
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  registers_0 = _RAND_0[31:0];
  _RAND_1 = {1{`RANDOM}};
  registers_1 = _RAND_1[31:0];
  _RAND_2 = {1{`RANDOM}};
  registers_2 = _RAND_2[31:0];
  _RAND_3 = {1{`RANDOM}};
  registers_3 = _RAND_3[31:0];
  _RAND_4 = {1{`RANDOM}};
  registers_4 = _RAND_4[31:0];
  _RAND_5 = {1{`RANDOM}};
  registers_5 = _RAND_5[31:0];
  _RAND_6 = {1{`RANDOM}};
  registers_6 = _RAND_6[31:0];
  _RAND_7 = {1{`RANDOM}};
  registers_7 = _RAND_7[31:0];
  _RAND_8 = {1{`RANDOM}};
  registers_8 = _RAND_8[31:0];
  _RAND_9 = {1{`RANDOM}};
  registers_9 = _RAND_9[31:0];
  _RAND_10 = {1{`RANDOM}};
  registers_10 = _RAND_10[31:0];
  _RAND_11 = {1{`RANDOM}};
  registers_11 = _RAND_11[31:0];
  _RAND_12 = {1{`RANDOM}};
  registers_12 = _RAND_12[31:0];
  _RAND_13 = {1{`RANDOM}};
  registers_13 = _RAND_13[31:0];
  _RAND_14 = {1{`RANDOM}};
  registers_14 = _RAND_14[31:0];
  _RAND_15 = {1{`RANDOM}};
  registers_15 = _RAND_15[31:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
  always @(posedge clock) begin
    if (reset) begin
      registers_0 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h0 == io_writeSel) begin
        registers_0 <= io_writeData;
      end
    end
    if (reset) begin
      registers_1 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h1 == io_writeSel) begin
        registers_1 <= io_writeData;
      end
    end
    if (reset) begin
      registers_2 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h2 == io_writeSel) begin
        registers_2 <= io_writeData;
      end
    end
    if (reset) begin
      registers_3 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h3 == io_writeSel) begin
        registers_3 <= io_writeData;
      end
    end
    if (reset) begin
      registers_4 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h4 == io_writeSel) begin
        registers_4 <= io_writeData;
      end
    end
    if (reset) begin
      registers_5 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h5 == io_writeSel) begin
        registers_5 <= io_writeData;
      end
    end
    if (reset) begin
      registers_6 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h6 == io_writeSel) begin
        registers_6 <= io_writeData;
      end
    end
    if (reset) begin
      registers_7 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h7 == io_writeSel) begin
        registers_7 <= io_writeData;
      end
    end
    if (reset) begin
      registers_8 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h8 == io_writeSel) begin
        registers_8 <= io_writeData;
      end
    end
    if (reset) begin
      registers_9 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'h9 == io_writeSel) begin
        registers_9 <= io_writeData;
      end
    end
    if (reset) begin
      registers_10 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'ha == io_writeSel) begin
        registers_10 <= io_writeData;
      end
    end
    if (reset) begin
      registers_11 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'hb == io_writeSel) begin
        registers_11 <= io_writeData;
      end
    end
    if (reset) begin
      registers_12 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'hc == io_writeSel) begin
        registers_12 <= io_writeData;
      end
    end
    if (reset) begin
      registers_13 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'hd == io_writeSel) begin
        registers_13 <= io_writeData;
      end
    end
    if (reset) begin
      registers_14 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'he == io_writeSel) begin
        registers_14 <= io_writeData;
      end
    end
    if (reset) begin
      registers_15 <= 32'h0;
    end else if (io_writeEnable) begin
      if (4'hf == io_writeSel) begin
        registers_15 <= io_writeData;
      end
    end
  end
endmodule
