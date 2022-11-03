import chisel3._
import chisel3.util._

class CPUTop extends Module {
  val io = IO(new Bundle {
    val done = Output(Bool())
    val run = Input(Bool())
    // This signals are used by the tester for loading and dumping the memory content, do not touch
    val testerDataMemEnable = Input(Bool())
    val testerDataMemAddress = Input(UInt(16.W))
    val testerDataMemDataRead = Output(UInt(32.W))
    val testerDataMemWriteEnable = Input(Bool())
    val testerDataMemDataWrite = Input(UInt(32.W))
    // This signals are used by the tester for loading and dumping the memory content, do not touch
    val testerProgMemEnable = Input(Bool())
    val testerProgMemAddress = Input(UInt(16.W))
    val testerProgMemDataRead = Output(UInt(32.W))
    val testerProgMemWriteEnable = Input(Bool())
    val testerProgMemDataWrite = Input(UInt(32.W))
  })

  // Creating components
  val programCounter = Module(new ProgramCounter())
  val dataMemory = Module(new DataMemory())
  val programMemory = Module(new ProgramMemory())
  val registerFile = Module(new RegisterFile())
  val controlUnit = Module(new ControlUnit())
  val alu = Module(new ALU())

  // Connecting the modules
  // done
  io.done := controlUnit.io.done

  // ControlUnit
  controlUnit.io.opcode := programMemory.io.instructionRead(31, 24)

  // ProgramCounter
  programCounter.io.run := io.run
  programCounter.io.stop := controlUnit.io.done
  programCounter.io.jump := alu.io.cmpResult
  programCounter.io.programCounterJump := programMemory.io.instructionRead(15, 0)

  // ProgramMemory
  programMemory.io.address := programCounter.io.programCounter

  // RegisterFile
  registerFile.io.writeEnable := controlUnit.io.regWrite
  registerFile.io.aSel := programMemory.io.instructionRead(23, 20)
  registerFile.io.bSel := programMemory.io.instructionRead(19, 16)
  when (controlUnit.io.immediateWriteSel) {
    registerFile.io.writeSel := programMemory.io.instructionRead(19, 16)
  } .otherwise {
    registerFile.io.writeSel := programMemory.io.instructionRead(15, 12)
  }
  when (controlUnit.io.immediateRegWrite) {
    registerFile.io.writeData := programMemory.io.instructionRead(15, 0)
  } .elsewhen (controlUnit.io.memRegWrite) {
    registerFile.io.writeData := dataMemory.io.dataRead
  } .otherwise {
    registerFile.io.writeData := alu.io.result
  }

  // ALU
  alu.io.op1 := registerFile.io.a
  when (controlUnit.io.immediateOp) {
    alu.io.op2 := programMemory.io.instructionRead(15, 0)
  } .otherwise {
    alu.io.op2 := registerFile.io.b
  }
  alu.io.sel := controlUnit.io.aluSel

  // DataMemory
  dataMemory.io.writeEnable := controlUnit.io.dataWrite
  when (controlUnit.io.immediateAddr) {
    dataMemory.io.address := programMemory.io.instructionRead(15, 0)
  } .otherwise {
    dataMemory.io.address := registerFile.io.a(15,0)
  }
  dataMemory.io.dataWrite := registerFile.io.b



  // This signals are used by the tester for loading the program to the program memory, do not touch
  programMemory.io.testerAddress := io.testerProgMemAddress
  io.testerProgMemDataRead := programMemory.io.testerDataRead
  programMemory.io.testerDataWrite := io.testerProgMemDataWrite
  programMemory.io.testerEnable := io.testerProgMemEnable
  programMemory.io.testerWriteEnable := io.testerProgMemWriteEnable
  // This signals are used by the tester for loading and dumping the data memory content, do not touch
  dataMemory.io.testerAddress := io.testerDataMemAddress
  io.testerDataMemDataRead := dataMemory.io.testerDataRead
  dataMemory.io.testerDataWrite := io.testerDataMemDataWrite
  dataMemory.io.testerEnable := io.testerDataMemEnable
  dataMemory.io.testerWriteEnable := io.testerDataMemWriteEnable

}