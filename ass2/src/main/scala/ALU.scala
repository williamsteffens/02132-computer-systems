import chisel3._
import chisel3.util._

class ALU extends Module {
  val io = IO(new Bundle {
    val op1 = Input(UInt(32.W))
    val op2 = Input(UInt(32.W))
    val sel = Input(UInt(4.W))
    val result = Output(UInt(32.W))
    val cmpResult = Output(Bool())
  })

  // Default values
  io.result := 0.U
  io.cmpResult := false.B

  switch (io.sel) {
    // Arithmetic and Logic
    is (0.U) { io.result := io.op1 + io.op2 }        // ADD
    is (1.U) { io.result := io.op1 - io.op2 }        // SUB
    is (2.U) { io.result := io.op1 * io.op2 }        // MULT
    is (3.U) { io.result := io.op1 + 1.U }           // INC
    is (4.U) { io.result := io.op1 - 1.U}            // DEC
    is (5.U) { io.result := ~io.op1 }                // Bitwise NOT
    is (6.U) { io.result := io.op1 & io.op2 }        // Bitwise AND
    is (7.U) { io.result := io.op1 | io.op2 }        // Bitwise OR
    is (8.U) { io.result := io.op1 ^ io.op2 }        // Bitwise XOR

    // Comparison
    is (9.U) { io.cmpResult := io.op1 === io.op2 }   // JEQ
    is (10.U) { io.cmpResult := io.op1 =/= io.op2 }  // JNEQ
    is (11.U) { io.cmpResult := io.op1 > io.op2 }    // JGT
    is (12.U) { io.cmpResult := io.op1 >= io.op2 }   // JGE
    is (13.U) { io.cmpResult := io.op1 < io.op2 }    // JLT
    is (14.U) { io.cmpResult := io.op1 <= io.op2 }   // JLE
    is (15.U) { io.cmpResult := true.B }             // JMP
  }

}