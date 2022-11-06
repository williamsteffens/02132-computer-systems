module ControlUnit(
  input        clock,
  input        reset,
  input  [7:0] io_opcode,
  output       io_regWrite,
  output       io_dataWrite,
  output [3:0] io_aluSel,
  output       io_memRegWrite,
  output       io_immediateOp,
  output       io_immediateAddr,
  output       io_immediateRegWrite,
  output       io_immediateWriteSel,
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
  assign io_immediateWriteSel = _T_1 ? 1'h0 : _T_8; // @[ControlUnit.scala 26:24 ControlUnit.scala 57:28]
  assign io_done = _T_1 ? 1'h0 : _GEN_34; // @[ControlUnit.scala 27:11 ControlUnit.scala 92:15]
endmodule
