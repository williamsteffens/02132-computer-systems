import chisel3._
import chisel3.util._

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val opcode = Input(UInt(8.W))
    val regWrite = Output(Bool())
    val dataWrite = Output(Bool())
    val aluSel = Output(UInt(4.W))
    val memRegWrite = Output(Bool())
    val immediateOp = Output(Bool())
    val immediateAddr = Output(Bool())
    val immediateRegWrite = Output(Bool())
    val immediateWriteSel = Output(Bool())
    val done = Output(Bool())
  })

  // Default values
  io.regWrite := false.B
  io.dataWrite := false.B
  io.aluSel := 0.U
  io.memRegWrite := false.B
  io.immediateOp := false.B
  io.immediateAddr := false.B
  io.immediateRegWrite := false.B
  io.immediateWriteSel := false.B
  io.done := false.B

  // Types
  switch (io.opcode(7, 6)) {
    // R-type
    is ("b00".U) {
      // Operation
      switch (io.opcode(5, 4)) {
        is ("b00".U) {
          // Arithmetic
          io.aluSel := io.opcode(3, 0)
          io.regWrite := true.B
        }
        is ("b01".U) {
          // Load
          io.regWrite := true.B
          io.memRegWrite := true.B
        }
        is ("b10".U) {
          // Store
          io.dataWrite := true.B
        }
        is ("b11".U) {
          // Empty slot
        }
      }
    }

    // I-type
    is ("b01".U) {
      io.immediateWriteSel := true.B
      // Operation
      switch (io.opcode(5, 4)) {
        is ("b00".U) {
          // Arithmetic immediate
          io.aluSel := io.opcode(3, 0)
          io.regWrite := true.B
          io.immediateOp := true.B
        }
        is ("b01".U) {
          // Assign
          io.regWrite := true.B
          io.immediateRegWrite := true.B
        }
        is ("b10".U) {
          // Load immediate
          io.immediateAddr := true.B
          io.regWrite := true.B
          io.memRegWrite := true.B
        }
        is ("b11".U) {
          // Store immediate
          io.immediateAddr := true.B
          io.dataWrite := true.B
        }
      }
    }

    // J-type
    is ("b10".U) {
      io.aluSel := io.opcode(3, 0)
    }

    // END
    is ("b11".U) {
      io.done := true.B
    }
  }

}