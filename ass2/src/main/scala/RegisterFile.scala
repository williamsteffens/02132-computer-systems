import chisel3._
import chisel3.util._

class RegisterFile extends Module {
  val io = IO(new Bundle {
    val aSel = Input(UInt(4.W))
    val bSel = Input(UInt(4.W))
    val writeData = Input(UInt(32.W))
    val writeSel = Input(UInt(4.W))
    val writeEnable = Input(Bool())
    val a = Output(UInt(32.W))
    val b = Output(UInt(32.W))
  })

  // Default values
  io.a := 0.U
  io.b := 0.U

  // Define registers as a vec with init to 0
  val registers: Vec[UInt] = RegInit(VecInit(Seq.fill(16)(0.U(32.W))))

  // Set register inputs
  when (io.writeEnable) {
    registers(io.writeSel) := io.writeData
  }

  // Set register outputs
  io.a := registers(io.aSel)
  io.b := registers(io.bSel)

}