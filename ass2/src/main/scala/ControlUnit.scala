import chisel3._
import chisel3.util._

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val opcode = Input(UInt(2.W))
    val regWrite = Output(Bool())
    val dataWrite = Output(Bool())
    val aluSel = Output(UInt(4.W))
    val memRegWrite = Output(Bool())
    val immediateOp = Output(Bool())
    val immediateAddr = Output(Bool())
    val immediateRegWrite = Output(Bool())
    val writeSelI = Output(Bool())
    val stop = Output(Bool())
  })

    // Default values
    io.regWrite := false.B
    io.dataWrite := false.B
    io.memRegWrite := false.B
    io.immediateOp := false.B
    io.immediateAddr := false.B
    io.immediateRegWrite := false.B
    io.stop := false.B
    io.aluSel := 0.U

    // Types
    switch (io.opcode(31,30)) {
      // R-type
      is ("b00".U) {
        // Operation
        switch (io.opcode(29,28)) {
          is ("b00".U) {
            // Arithmetic
            io.aluSel := io.opcode(27,24)
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
        io.writeSelI := true.B
        // Operation
        switch (io.opcode(29,28)) {
          is ("b00".U) {
            // Arithmetic immediate
            io.aluSel := io.opcode(27,24)
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
        io.aluSel := io.opcode(26,29)
      }

      // END
      is ("b11".U) {
        io.stop := true.B
      }
    }

}