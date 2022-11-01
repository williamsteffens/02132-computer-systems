module ProgramCounter(
  input         clock,
  input         reset,
  input         io_stop,
  input         io_jump,
  input         io_run,
  input  [15:0] io_programCounterJump,
  output [15:0] io_programCounter
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_REG_INIT
  reg [15:0] PCReg; // @[ProgramCounter.scala 14:28]
  wire  _T = ~io_run; // @[ProgramCounter.scala 17:29]
  wire  runStopLogic = io_stop | _T; // @[ProgramCounter.scala 17:27]
  wire [15:0] _T_3 = PCReg + 16'h1; // @[ProgramCounter.scala 25:20]
  assign io_programCounter = PCReg; // @[ProgramCounter.scala 29:21]
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
  PCReg = _RAND_0[15:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
  always @(posedge clock) begin
    if (reset) begin
      PCReg <= 16'h0;
    end else if (!(runStopLogic)) begin
      if (io_jump) begin
        PCReg <= io_programCounterJump;
      end else begin
        PCReg <= _T_3;
      end
    end
  end
endmodule
module DataMemory(
  input         clock,
  input  [15:0] io_address,
  output [31:0] io_dataRead,
  input         io_writeEnable,
  input  [31:0] io_dataWrite,
  input         io_testerEnable,
  input  [15:0] io_testerAddress,
  output [31:0] io_testerDataRead,
  input         io_testerWriteEnable,
  input  [31:0] io_testerDataWrite
);
`ifdef RANDOMIZE_MEM_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_MEM_INIT
  reg [31:0] memory [0:65535]; // @[DataMemory.scala 18:20]
  wire [31:0] memory__T_data; // @[DataMemory.scala 18:20]
  wire [15:0] memory__T_addr; // @[DataMemory.scala 18:20]
  wire [31:0] memory__T_2_data; // @[DataMemory.scala 18:20]
  wire [15:0] memory__T_2_addr; // @[DataMemory.scala 18:20]
  wire [31:0] memory__T_1_data; // @[DataMemory.scala 18:20]
  wire [15:0] memory__T_1_addr; // @[DataMemory.scala 18:20]
  wire  memory__T_1_mask; // @[DataMemory.scala 18:20]
  wire  memory__T_1_en; // @[DataMemory.scala 18:20]
  wire [31:0] memory__T_3_data; // @[DataMemory.scala 18:20]
  wire [15:0] memory__T_3_addr; // @[DataMemory.scala 18:20]
  wire  memory__T_3_mask; // @[DataMemory.scala 18:20]
  wire  memory__T_3_en; // @[DataMemory.scala 18:20]
  wire [31:0] _GEN_5 = io_testerWriteEnable ? io_testerDataWrite : memory__T_data; // @[DataMemory.scala 24:32]
  wire [31:0] _GEN_11 = io_writeEnable ? io_dataWrite : memory__T_2_data; // @[DataMemory.scala 32:26]
  assign memory__T_addr = io_testerAddress;
  assign memory__T_data = memory[memory__T_addr]; // @[DataMemory.scala 18:20]
  assign memory__T_2_addr = io_address;
  assign memory__T_2_data = memory[memory__T_2_addr]; // @[DataMemory.scala 18:20]
  assign memory__T_1_data = io_testerDataWrite;
  assign memory__T_1_addr = io_testerAddress;
  assign memory__T_1_mask = 1'h1;
  assign memory__T_1_en = io_testerEnable & io_testerWriteEnable;
  assign memory__T_3_data = io_dataWrite;
  assign memory__T_3_addr = io_address;
  assign memory__T_3_mask = 1'h1;
  assign memory__T_3_en = io_testerEnable ? 1'h0 : io_writeEnable;
  assign io_dataRead = io_testerEnable ? 32'h0 : _GEN_11; // @[DataMemory.scala 23:17 DataMemory.scala 30:17 DataMemory.scala 34:19]
  assign io_testerDataRead = io_testerEnable ? _GEN_5 : 32'h0; // @[DataMemory.scala 22:23 DataMemory.scala 26:25 DataMemory.scala 31:23]
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
`ifdef RANDOMIZE_MEM_INIT
  _RAND_0 = {1{`RANDOM}};
  for (initvar = 0; initvar < 65536; initvar = initvar+1)
    memory[initvar] = _RAND_0[31:0];
`endif // RANDOMIZE_MEM_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
  always @(posedge clock) begin
    if(memory__T_1_en & memory__T_1_mask) begin
      memory[memory__T_1_addr] <= memory__T_1_data; // @[DataMemory.scala 18:20]
    end
    if(memory__T_3_en & memory__T_3_mask) begin
      memory[memory__T_3_addr] <= memory__T_3_data; // @[DataMemory.scala 18:20]
    end
  end
endmodule
module ProgramMemory(
  input         clock,
  input  [15:0] io_address,
  output [31:0] io_instructionRead,
  input         io_testerEnable,
  input  [15:0] io_testerAddress,
  output [31:0] io_testerDataRead,
  input         io_testerWriteEnable,
  input  [31:0] io_testerDataWrite
);
`ifdef RANDOMIZE_MEM_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_MEM_INIT
  reg [31:0] memory [0:65535]; // @[ProgramMemory.scala 16:20]
  wire [31:0] memory__T_data; // @[ProgramMemory.scala 16:20]
  wire [15:0] memory__T_addr; // @[ProgramMemory.scala 16:20]
  wire [31:0] memory__T_2_data; // @[ProgramMemory.scala 16:20]
  wire [15:0] memory__T_2_addr; // @[ProgramMemory.scala 16:20]
  wire [31:0] memory__T_1_data; // @[ProgramMemory.scala 16:20]
  wire [15:0] memory__T_1_addr; // @[ProgramMemory.scala 16:20]
  wire  memory__T_1_mask; // @[ProgramMemory.scala 16:20]
  wire  memory__T_1_en; // @[ProgramMemory.scala 16:20]
  wire [31:0] _GEN_5 = io_testerWriteEnable ? io_testerDataWrite : memory__T_data; // @[ProgramMemory.scala 22:32]
  assign memory__T_addr = io_testerAddress;
  assign memory__T_data = memory[memory__T_addr]; // @[ProgramMemory.scala 16:20]
  assign memory__T_2_addr = io_address;
  assign memory__T_2_data = memory[memory__T_2_addr]; // @[ProgramMemory.scala 16:20]
  assign memory__T_1_data = io_testerDataWrite;
  assign memory__T_1_addr = io_testerAddress;
  assign memory__T_1_mask = 1'h1;
  assign memory__T_1_en = io_testerEnable & io_testerWriteEnable;
  assign io_instructionRead = io_testerEnable ? 32'h0 : memory__T_2_data; // @[ProgramMemory.scala 21:24 ProgramMemory.scala 28:24]
  assign io_testerDataRead = io_testerEnable ? _GEN_5 : 32'h0; // @[ProgramMemory.scala 20:23 ProgramMemory.scala 24:25 ProgramMemory.scala 29:23]
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
`ifdef RANDOMIZE_MEM_INIT
  _RAND_0 = {1{`RANDOM}};
  for (initvar = 0; initvar < 65536; initvar = initvar+1)
    memory[initvar] = _RAND_0[31:0];
`endif // RANDOMIZE_MEM_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
  always @(posedge clock) begin
    if(memory__T_1_en & memory__T_1_mask) begin
      memory[memory__T_1_addr] <= memory__T_1_data; // @[ProgramMemory.scala 16:20]
    end
  end
endmodule
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
module ControlUnit(
  input  [7:0] io_opcode,
  output       io_regWrite,
  output       io_dataWrite,
  output [3:0] io_aluSel,
  output       io_memRegWrite,
  output       io_immediateOp,
  output       io_immediateAddr,
  output       io_immediateRegWrite,
  output       io_writeSelI,
  output       io_done
);
  wire  _T_1 = 2'h0 == io_opcode[7:6]; // @[Conditional.scala 37:30]
  wire  _T_3 = 2'h0 == io_opcode[5:4]; // @[Conditional.scala 37:30]
  wire  _T_5 = 2'h1 == io_opcode[5:4]; // @[Conditional.scala 37:30]
  wire  _T_6 = 2'h2 == io_opcode[5:4]; // @[Conditional.scala 37:30]
  wire  _T_7 = 2'h3 == io_opcode[5:4]; // @[Conditional.scala 37:30]
  wire  _GEN_2 = _T_5 ? 1'h0 : _T_6; // @[Conditional.scala 39:67]
  wire [3:0] _GEN_3 = _T_3 ? io_opcode[3:0] : 4'h0; // @[Conditional.scala 40:58]
  wire  _GEN_4 = _T_3 | _T_5; // @[Conditional.scala 40:58]
  wire  _GEN_5 = _T_3 ? 1'h0 : _T_5; // @[Conditional.scala 40:58]
  wire  _GEN_6 = _T_3 ? 1'h0 : _GEN_2; // @[Conditional.scala 40:58]
  wire  _T_8 = 2'h1 == io_opcode[7:6]; // @[Conditional.scala 37:30]
  wire  _GEN_8 = _T_6 | _T_7; // @[Conditional.scala 39:67]
  wire  _GEN_10 = _T_6 ? 1'h0 : _T_7; // @[Conditional.scala 39:67]
  wire  _GEN_11 = _T_5 | _T_6; // @[Conditional.scala 39:67]
  wire  _GEN_13 = _T_5 ? 1'h0 : _GEN_8; // @[Conditional.scala 39:67]
  wire  _GEN_15 = _T_5 ? 1'h0 : _GEN_10; // @[Conditional.scala 39:67]
  wire  _GEN_17 = _T_3 | _GEN_11; // @[Conditional.scala 40:58]
  wire  _GEN_20 = _T_3 ? 1'h0 : _GEN_13; // @[Conditional.scala 40:58]
  wire  _GEN_22 = _T_3 ? 1'h0 : _GEN_15; // @[Conditional.scala 40:58]
  wire  _T_15 = 2'h2 == io_opcode[7:6]; // @[Conditional.scala 37:30]
  wire  _T_17 = 2'h3 == io_opcode[7:6]; // @[Conditional.scala 37:30]
  wire [3:0] _GEN_24 = _T_15 ? io_opcode[3:0] : 4'h0; // @[Conditional.scala 39:67]
  wire  _GEN_25 = _T_15 ? 1'h0 : _T_17; // @[Conditional.scala 39:67]
  wire [3:0] _GEN_27 = _T_8 ? _GEN_3 : _GEN_24; // @[Conditional.scala 39:67]
  wire  _GEN_28 = _T_8 & _GEN_17; // @[Conditional.scala 39:67]
  wire  _GEN_29 = _T_8 & _T_3; // @[Conditional.scala 39:67]
  wire  _GEN_30 = _T_8 & _GEN_5; // @[Conditional.scala 39:67]
  wire  _GEN_31 = _T_8 & _GEN_20; // @[Conditional.scala 39:67]
  wire  _GEN_32 = _T_8 & _GEN_6; // @[Conditional.scala 39:67]
  wire  _GEN_33 = _T_8 & _GEN_22; // @[Conditional.scala 39:67]
  wire  _GEN_34 = _T_8 ? 1'h0 : _GEN_25; // @[Conditional.scala 39:67]
  assign io_regWrite = _T_1 ? _GEN_4 : _GEN_28; // @[ControlUnit.scala 19:15 ControlUnit.scala 38:23 ControlUnit.scala 42:23 ControlUnit.scala 63:23 ControlUnit.scala 68:23 ControlUnit.scala 74:23]
  assign io_dataWrite = _T_1 ? _GEN_6 : _GEN_33; // @[ControlUnit.scala 20:16 ControlUnit.scala 47:24 ControlUnit.scala 80:24]
  assign io_aluSel = _T_1 ? _GEN_3 : _GEN_27; // @[ControlUnit.scala 21:13 ControlUnit.scala 37:21 ControlUnit.scala 62:21 ControlUnit.scala 87:17]
  assign io_memRegWrite = _T_1 ? _GEN_5 : _GEN_32; // @[ControlUnit.scala 22:18 ControlUnit.scala 43:26 ControlUnit.scala 75:26]
  assign io_immediateOp = _T_1 ? 1'h0 : _GEN_29; // @[ControlUnit.scala 23:18 ControlUnit.scala 64:26]
  assign io_immediateAddr = _T_1 ? 1'h0 : _GEN_31; // @[ControlUnit.scala 24:20 ControlUnit.scala 73:28 ControlUnit.scala 79:28]
  assign io_immediateRegWrite = _T_1 ? 1'h0 : _GEN_30; // @[ControlUnit.scala 25:24 ControlUnit.scala 69:32]
  assign io_writeSelI = _T_1 ? 1'h0 : _T_8; // @[ControlUnit.scala 26:16 ControlUnit.scala 57:20]
  assign io_done = _T_1 ? 1'h0 : _GEN_34; // @[ControlUnit.scala 27:11 ControlUnit.scala 92:15]
endmodule
module ALU(
  input  [31:0] io_op1,
  input  [31:0] io_op2,
  input  [3:0]  io_sel,
  output [31:0] io_result,
  output        io_cmpResult
);
  wire  _T = 4'h0 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_2 = io_op1 + io_op2; // @[ALU.scala 19:36]
  wire  _T_3 = 4'h1 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_5 = io_op1 - io_op2; // @[ALU.scala 20:36]
  wire  _T_6 = 4'h2 == io_sel; // @[Conditional.scala 37:30]
  wire [63:0] _T_7 = io_op1 * io_op2; // @[ALU.scala 21:36]
  wire  _T_8 = 4'h3 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_10 = io_op1 + 32'h1; // @[ALU.scala 22:36]
  wire  _T_11 = 4'h4 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_13 = io_op1 - 32'h1; // @[ALU.scala 23:36]
  wire  _T_14 = 4'h5 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_15 = ~io_op1; // @[ALU.scala 24:29]
  wire  _T_16 = 4'h6 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_17 = io_op1 & io_op2; // @[ALU.scala 25:36]
  wire  _T_18 = 4'h7 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_19 = io_op1 | io_op2; // @[ALU.scala 26:36]
  wire  _T_20 = 4'h8 == io_sel; // @[Conditional.scala 37:30]
  wire [31:0] _T_21 = io_op1 ^ io_op2; // @[ALU.scala 27:36]
  wire  _T_22 = 4'h9 == io_sel; // @[Conditional.scala 37:30]
  wire  _T_23 = io_op1 == io_op2; // @[ALU.scala 30:39]
  wire  _T_24 = 4'ha == io_sel; // @[Conditional.scala 37:30]
  wire  _T_25 = io_op1 != io_op2; // @[ALU.scala 31:40]
  wire  _T_26 = 4'hb == io_sel; // @[Conditional.scala 37:30]
  wire  _T_27 = io_op1 > io_op2; // @[ALU.scala 32:40]
  wire  _T_28 = 4'hc == io_sel; // @[Conditional.scala 37:30]
  wire  _T_29 = io_op1 >= io_op2; // @[ALU.scala 33:40]
  wire  _T_30 = 4'hd == io_sel; // @[Conditional.scala 37:30]
  wire  _T_31 = io_op1 < io_op2; // @[ALU.scala 34:40]
  wire  _T_32 = 4'he == io_sel; // @[Conditional.scala 37:30]
  wire  _T_33 = io_op1 <= io_op2; // @[ALU.scala 35:40]
  wire  _T_34 = 4'hf == io_sel; // @[Conditional.scala 37:30]
  wire  _GEN_1 = _T_32 ? _T_33 : _T_34; // @[Conditional.scala 39:67]
  wire  _GEN_2 = _T_30 ? _T_31 : _GEN_1; // @[Conditional.scala 39:67]
  wire  _GEN_3 = _T_28 ? _T_29 : _GEN_2; // @[Conditional.scala 39:67]
  wire  _GEN_4 = _T_26 ? _T_27 : _GEN_3; // @[Conditional.scala 39:67]
  wire  _GEN_5 = _T_24 ? _T_25 : _GEN_4; // @[Conditional.scala 39:67]
  wire  _GEN_6 = _T_22 ? _T_23 : _GEN_5; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_7 = _T_20 ? _T_21 : 32'h0; // @[Conditional.scala 39:67]
  wire  _GEN_8 = _T_20 ? 1'h0 : _GEN_6; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_9 = _T_18 ? _T_19 : _GEN_7; // @[Conditional.scala 39:67]
  wire  _GEN_10 = _T_18 ? 1'h0 : _GEN_8; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_11 = _T_16 ? _T_17 : _GEN_9; // @[Conditional.scala 39:67]
  wire  _GEN_12 = _T_16 ? 1'h0 : _GEN_10; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_13 = _T_14 ? _T_15 : _GEN_11; // @[Conditional.scala 39:67]
  wire  _GEN_14 = _T_14 ? 1'h0 : _GEN_12; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_15 = _T_11 ? _T_13 : _GEN_13; // @[Conditional.scala 39:67]
  wire  _GEN_16 = _T_11 ? 1'h0 : _GEN_14; // @[Conditional.scala 39:67]
  wire [31:0] _GEN_17 = _T_8 ? _T_10 : _GEN_15; // @[Conditional.scala 39:67]
  wire  _GEN_18 = _T_8 ? 1'h0 : _GEN_16; // @[Conditional.scala 39:67]
  wire [63:0] _GEN_19 = _T_6 ? _T_7 : {{32'd0}, _GEN_17}; // @[Conditional.scala 39:67]
  wire  _GEN_20 = _T_6 ? 1'h0 : _GEN_18; // @[Conditional.scala 39:67]
  wire [63:0] _GEN_21 = _T_3 ? {{32'd0}, _T_5} : _GEN_19; // @[Conditional.scala 39:67]
  wire  _GEN_22 = _T_3 ? 1'h0 : _GEN_20; // @[Conditional.scala 39:67]
  wire [63:0] _GEN_23 = _T ? {{32'd0}, _T_2} : _GEN_21; // @[Conditional.scala 40:58]
  assign io_result = _GEN_23[31:0]; // @[ALU.scala 14:13 ALU.scala 19:26 ALU.scala 20:26 ALU.scala 21:26 ALU.scala 22:26 ALU.scala 23:26 ALU.scala 24:26 ALU.scala 25:26 ALU.scala 26:26 ALU.scala 27:26]
  assign io_cmpResult = _T ? 1'h0 : _GEN_22; // @[ALU.scala 15:16 ALU.scala 30:29 ALU.scala 31:30 ALU.scala 32:30 ALU.scala 33:30 ALU.scala 34:30 ALU.scala 35:30 ALU.scala 36:30]
endmodule
module CPUTop(
  input         clock,
  input         reset,
  output        io_done,
  input         io_run,
  input         io_testerDataMemEnable,
  input  [15:0] io_testerDataMemAddress,
  output [31:0] io_testerDataMemDataRead,
  input         io_testerDataMemWriteEnable,
  input  [31:0] io_testerDataMemDataWrite,
  input         io_testerProgMemEnable,
  input  [15:0] io_testerProgMemAddress,
  output [31:0] io_testerProgMemDataRead,
  input         io_testerProgMemWriteEnable,
  input  [31:0] io_testerProgMemDataWrite
);
  wire  programCounter_clock; // @[CPUTop.scala 23:30]
  wire  programCounter_reset; // @[CPUTop.scala 23:30]
  wire  programCounter_io_stop; // @[CPUTop.scala 23:30]
  wire  programCounter_io_jump; // @[CPUTop.scala 23:30]
  wire  programCounter_io_run; // @[CPUTop.scala 23:30]
  wire [15:0] programCounter_io_programCounterJump; // @[CPUTop.scala 23:30]
  wire [15:0] programCounter_io_programCounter; // @[CPUTop.scala 23:30]
  wire  dataMemory_clock; // @[CPUTop.scala 24:26]
  wire [15:0] dataMemory_io_address; // @[CPUTop.scala 24:26]
  wire [31:0] dataMemory_io_dataRead; // @[CPUTop.scala 24:26]
  wire  dataMemory_io_writeEnable; // @[CPUTop.scala 24:26]
  wire [31:0] dataMemory_io_dataWrite; // @[CPUTop.scala 24:26]
  wire  dataMemory_io_testerEnable; // @[CPUTop.scala 24:26]
  wire [15:0] dataMemory_io_testerAddress; // @[CPUTop.scala 24:26]
  wire [31:0] dataMemory_io_testerDataRead; // @[CPUTop.scala 24:26]
  wire  dataMemory_io_testerWriteEnable; // @[CPUTop.scala 24:26]
  wire [31:0] dataMemory_io_testerDataWrite; // @[CPUTop.scala 24:26]
  wire  programMemory_clock; // @[CPUTop.scala 25:29]
  wire [15:0] programMemory_io_address; // @[CPUTop.scala 25:29]
  wire [31:0] programMemory_io_instructionRead; // @[CPUTop.scala 25:29]
  wire  programMemory_io_testerEnable; // @[CPUTop.scala 25:29]
  wire [15:0] programMemory_io_testerAddress; // @[CPUTop.scala 25:29]
  wire [31:0] programMemory_io_testerDataRead; // @[CPUTop.scala 25:29]
  wire  programMemory_io_testerWriteEnable; // @[CPUTop.scala 25:29]
  wire [31:0] programMemory_io_testerDataWrite; // @[CPUTop.scala 25:29]
  wire  registerFile_clock; // @[CPUTop.scala 26:28]
  wire  registerFile_reset; // @[CPUTop.scala 26:28]
  wire [3:0] registerFile_io_aSel; // @[CPUTop.scala 26:28]
  wire [3:0] registerFile_io_bSel; // @[CPUTop.scala 26:28]
  wire [31:0] registerFile_io_writeData; // @[CPUTop.scala 26:28]
  wire [3:0] registerFile_io_writeSel; // @[CPUTop.scala 26:28]
  wire  registerFile_io_writeEnable; // @[CPUTop.scala 26:28]
  wire [31:0] registerFile_io_a; // @[CPUTop.scala 26:28]
  wire [31:0] registerFile_io_b; // @[CPUTop.scala 26:28]
  wire [7:0] controlUnit_io_opcode; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_regWrite; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_dataWrite; // @[CPUTop.scala 27:27]
  wire [3:0] controlUnit_io_aluSel; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_memRegWrite; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_immediateOp; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_immediateAddr; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_immediateRegWrite; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_writeSelI; // @[CPUTop.scala 27:27]
  wire  controlUnit_io_done; // @[CPUTop.scala 27:27]
  wire [31:0] alu_io_op1; // @[CPUTop.scala 28:19]
  wire [31:0] alu_io_op2; // @[CPUTop.scala 28:19]
  wire [3:0] alu_io_sel; // @[CPUTop.scala 28:19]
  wire [31:0] alu_io_result; // @[CPUTop.scala 28:19]
  wire  alu_io_cmpResult; // @[CPUTop.scala 28:19]
  wire [31:0] _GEN_1 = controlUnit_io_memRegWrite ? dataMemory_io_dataRead : alu_io_result; // @[CPUTop.scala 57:44]
  wire [31:0] _GEN_4 = controlUnit_io_immediateAddr ? {{16'd0}, programMemory_io_instructionRead[15:0]} : registerFile_io_a; // @[CPUTop.scala 75:39]
  ProgramCounter programCounter ( // @[CPUTop.scala 23:30]
    .clock(programCounter_clock),
    .reset(programCounter_reset),
    .io_stop(programCounter_io_stop),
    .io_jump(programCounter_io_jump),
    .io_run(programCounter_io_run),
    .io_programCounterJump(programCounter_io_programCounterJump),
    .io_programCounter(programCounter_io_programCounter)
  );
  DataMemory dataMemory ( // @[CPUTop.scala 24:26]
    .clock(dataMemory_clock),
    .io_address(dataMemory_io_address),
    .io_dataRead(dataMemory_io_dataRead),
    .io_writeEnable(dataMemory_io_writeEnable),
    .io_dataWrite(dataMemory_io_dataWrite),
    .io_testerEnable(dataMemory_io_testerEnable),
    .io_testerAddress(dataMemory_io_testerAddress),
    .io_testerDataRead(dataMemory_io_testerDataRead),
    .io_testerWriteEnable(dataMemory_io_testerWriteEnable),
    .io_testerDataWrite(dataMemory_io_testerDataWrite)
  );
  ProgramMemory programMemory ( // @[CPUTop.scala 25:29]
    .clock(programMemory_clock),
    .io_address(programMemory_io_address),
    .io_instructionRead(programMemory_io_instructionRead),
    .io_testerEnable(programMemory_io_testerEnable),
    .io_testerAddress(programMemory_io_testerAddress),
    .io_testerDataRead(programMemory_io_testerDataRead),
    .io_testerWriteEnable(programMemory_io_testerWriteEnable),
    .io_testerDataWrite(programMemory_io_testerDataWrite)
  );
  RegisterFile registerFile ( // @[CPUTop.scala 26:28]
    .clock(registerFile_clock),
    .reset(registerFile_reset),
    .io_aSel(registerFile_io_aSel),
    .io_bSel(registerFile_io_bSel),
    .io_writeData(registerFile_io_writeData),
    .io_writeSel(registerFile_io_writeSel),
    .io_writeEnable(registerFile_io_writeEnable),
    .io_a(registerFile_io_a),
    .io_b(registerFile_io_b)
  );
  ControlUnit controlUnit ( // @[CPUTop.scala 27:27]
    .io_opcode(controlUnit_io_opcode),
    .io_regWrite(controlUnit_io_regWrite),
    .io_dataWrite(controlUnit_io_dataWrite),
    .io_aluSel(controlUnit_io_aluSel),
    .io_memRegWrite(controlUnit_io_memRegWrite),
    .io_immediateOp(controlUnit_io_immediateOp),
    .io_immediateAddr(controlUnit_io_immediateAddr),
    .io_immediateRegWrite(controlUnit_io_immediateRegWrite),
    .io_writeSelI(controlUnit_io_writeSelI),
    .io_done(controlUnit_io_done)
  );
  ALU alu ( // @[CPUTop.scala 28:19]
    .io_op1(alu_io_op1),
    .io_op2(alu_io_op2),
    .io_sel(alu_io_sel),
    .io_result(alu_io_result),
    .io_cmpResult(alu_io_cmpResult)
  );
  assign io_done = controlUnit_io_done; // @[CPUTop.scala 32:11]
  assign io_testerDataMemDataRead = dataMemory_io_testerDataRead; // @[CPUTop.scala 91:28]
  assign io_testerProgMemDataRead = programMemory_io_testerDataRead; // @[CPUTop.scala 85:28]
  assign programCounter_clock = clock;
  assign programCounter_reset = reset;
  assign programCounter_io_stop = controlUnit_io_done; // @[CPUTop.scala 39:26]
  assign programCounter_io_jump = alu_io_cmpResult; // @[CPUTop.scala 40:26]
  assign programCounter_io_run = io_run; // @[CPUTop.scala 38:25]
  assign programCounter_io_programCounterJump = programMemory_io_instructionRead[15:0]; // @[CPUTop.scala 41:40]
  assign dataMemory_clock = clock;
  assign dataMemory_io_address = _GEN_4[15:0]; // @[CPUTop.scala 76:27 CPUTop.scala 78:27]
  assign dataMemory_io_writeEnable = controlUnit_io_dataWrite; // @[CPUTop.scala 73:29]
  assign dataMemory_io_dataWrite = registerFile_io_b; // @[CPUTop.scala 74:27]
  assign dataMemory_io_testerEnable = io_testerDataMemEnable; // @[CPUTop.scala 93:30]
  assign dataMemory_io_testerAddress = io_testerDataMemAddress; // @[CPUTop.scala 90:31]
  assign dataMemory_io_testerWriteEnable = io_testerDataMemWriteEnable; // @[CPUTop.scala 94:35]
  assign dataMemory_io_testerDataWrite = io_testerDataMemDataWrite; // @[CPUTop.scala 92:33]
  assign programMemory_clock = clock;
  assign programMemory_io_address = programCounter_io_programCounter; // @[CPUTop.scala 44:28]
  assign programMemory_io_testerEnable = io_testerProgMemEnable; // @[CPUTop.scala 87:33]
  assign programMemory_io_testerAddress = io_testerProgMemAddress; // @[CPUTop.scala 84:34]
  assign programMemory_io_testerWriteEnable = io_testerProgMemWriteEnable; // @[CPUTop.scala 88:38]
  assign programMemory_io_testerDataWrite = io_testerProgMemDataWrite; // @[CPUTop.scala 86:36]
  assign registerFile_clock = clock;
  assign registerFile_reset = reset;
  assign registerFile_io_aSel = programMemory_io_instructionRead[23:20]; // @[CPUTop.scala 48:24]
  assign registerFile_io_bSel = programMemory_io_instructionRead[19:16]; // @[CPUTop.scala 49:24]
  assign registerFile_io_writeData = controlUnit_io_immediateRegWrite ? {{16'd0}, programMemory_io_instructionRead[15:0]} : _GEN_1; // @[CPUTop.scala 56:31 CPUTop.scala 58:31 CPUTop.scala 60:31]
  assign registerFile_io_writeSel = controlUnit_io_writeSelI ? programMemory_io_instructionRead[19:16] : programMemory_io_instructionRead[15:12]; // @[CPUTop.scala 51:30 CPUTop.scala 53:30]
  assign registerFile_io_writeEnable = controlUnit_io_regWrite; // @[CPUTop.scala 47:31]
  assign controlUnit_io_opcode = programMemory_io_instructionRead[31:24]; // @[CPUTop.scala 35:25]
  assign alu_io_op1 = registerFile_io_a; // @[CPUTop.scala 64:14]
  assign alu_io_op2 = controlUnit_io_immediateOp ? {{16'd0}, programMemory_io_instructionRead[15:0]} : registerFile_io_b; // @[CPUTop.scala 66:16 CPUTop.scala 68:16]
  assign alu_io_sel = controlUnit_io_aluSel; // @[CPUTop.scala 70:14]
endmodule
