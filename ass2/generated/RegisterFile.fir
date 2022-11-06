;buildInfoPackage: chisel3, version: 3.3.2, scalaVersion: 2.12.11, sbtVersion: 1.3.10
circuit RegisterFile : 
  module RegisterFile : 
    input clock : Clock
    input reset : UInt<1>
    output io : {flip aSel : UInt<4>, flip bSel : UInt<4>, flip writeData : UInt<32>, flip writeSel : UInt<4>, flip writeEnable : UInt<1>, a : UInt<32>, b : UInt<32>}
    
    io.a <= UInt<1>("h00") @[RegisterFile.scala 16:8]
    io.b <= UInt<1>("h00") @[RegisterFile.scala 17:8]
    wire _T : UInt<32>[16] @[RegisterFile.scala 20:45]
    _T[0] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[1] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[2] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[3] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[4] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[5] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[6] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[7] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[8] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[9] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[10] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[11] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[12] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[13] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[14] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    _T[15] <= UInt<32>("h00") @[RegisterFile.scala 20:45]
    reg registers : UInt<32>[16], clock with : (reset => (reset, _T)) @[RegisterFile.scala 20:37]
    when io.writeEnable : @[RegisterFile.scala 23:25]
      registers[io.writeSel] <= io.writeData @[RegisterFile.scala 24:28]
      skip @[RegisterFile.scala 23:25]
    io.a <= registers[io.aSel] @[RegisterFile.scala 28:8]
    io.b <= registers[io.bSel] @[RegisterFile.scala 29:8]
    
