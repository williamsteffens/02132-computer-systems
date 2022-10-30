;buildInfoPackage: chisel3, version: 3.3.2, scalaVersion: 2.12.11, sbtVersion: 1.3.10
circuit ProgramCounter : 
  module ProgramCounter : 
    input clock : Clock
    input reset : UInt<1>
    output io : {flip stop : UInt<1>, flip jump : UInt<1>, flip run : UInt<1>, flip programCounterJump : UInt<16>, programCounter : UInt<16>}
    
    reg PCReg : UInt<16>, clock with : (reset => (reset, UInt<16>("h00"))) @[ProgramCounter.scala 14:28]
    wire runStopLogic : UInt<1>
    runStopLogic <= UInt<1>("h00")
    node _T = not(io.run) @[ProgramCounter.scala 17:29]
    node _T_1 = or(io.stop, _T) @[ProgramCounter.scala 17:27]
    runStopLogic <= _T_1 @[ProgramCounter.scala 17:16]
    when runStopLogic : @[ProgramCounter.scala 20:23]
      PCReg <= PCReg @[ProgramCounter.scala 21:11]
      skip @[ProgramCounter.scala 20:23]
    else : @[ProgramCounter.scala 22:25]
      when io.jump : @[ProgramCounter.scala 22:25]
        PCReg <= io.programCounterJump @[ProgramCounter.scala 23:11]
        skip @[ProgramCounter.scala 22:25]
      else : @[ProgramCounter.scala 24:16]
        node _T_2 = add(PCReg, UInt<1>("h01")) @[ProgramCounter.scala 25:20]
        node _T_3 = tail(_T_2, 1) @[ProgramCounter.scala 25:20]
        PCReg <= _T_3 @[ProgramCounter.scala 25:11]
        skip @[ProgramCounter.scala 24:16]
    io.programCounter <= PCReg @[ProgramCounter.scala 29:21]
    
