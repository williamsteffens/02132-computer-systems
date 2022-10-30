import chisel3._
import chisel3.util._

class ProgramCounter extends Module {
  val io = IO(new Bundle {
    val stop = Input(Bool())
    val jump = Input(Bool())
    val run = Input(Bool())
    val programCounterJump = Input(UInt(16.W))
    val programCounter = Output(UInt(16.W))
  })

  //Implement this module here (respect the provided interface, since it used by the tester)
  val PCReg: UInt = RegInit(0.U(16.W))

  val runStopLogic: Bool = WireDefault(false.B)
  runStopLogic := io.stop | ~io.run

  // Chain of mux
  when (runStopLogic) {
    PCReg := PCReg
  } .elsewhen (io.jump) {
    PCReg := io.programCounterJump
  } .otherwise {
    PCReg := PCReg + 1.U
  }

  // Output
  io.programCounter := PCReg

}