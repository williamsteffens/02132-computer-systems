import chisel3.iotesters
import chisel3.iotesters.PeekPokeTester

class ControlUnitTester(dut: ControlUnit) extends PeekPokeTester(dut) {

  // R-type
  // ADD
  poke(dut.io.opcode, Integer.parseInt("00000000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // SUB
  poke(dut.io.opcode, Integer.parseInt("00000001",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 1)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // MULT
  poke(dut.io.opcode, Integer.parseInt("00000010",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 2)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // INC
  poke(dut.io.opcode, Integer.parseInt("00000011",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 3)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // DEC
  poke(dut.io.opcode, Integer.parseInt("00000100",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 4)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // NOT
  poke(dut.io.opcode, Integer.parseInt("00000101",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 5)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // AND
  poke(dut.io.opcode, Integer.parseInt("00000110",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 6)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // OR
  poke(dut.io.opcode, Integer.parseInt("00000111",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 7)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // XOR
  poke(dut.io.opcode, Integer.parseInt("00001000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 8)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // LOAD
  poke(dut.io.opcode, Integer.parseInt("00010000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, true)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // STD
  poke(dut.io.opcode, Integer.parseInt("00100000",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, true)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)



  // I-type
  // ADDI
  poke(dut.io.opcode, Integer.parseInt("01000000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, true)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, true)
  expect(dut.io.done, false)
  step(5)

  // SUBI
  poke(dut.io.opcode, Integer.parseInt("01000001",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 1)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, true)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, true)
  expect(dut.io.done, false)
  step(5)

  // ASS
  poke(dut.io.opcode, Integer.parseInt("01010000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, true)
  expect(dut.io.immediateWriteSel, true)
  expect(dut.io.done, false)
  step(5)

  // LOADI
  poke(dut.io.opcode, Integer.parseInt("01100000",2))
  expect(dut.io.regWrite, true)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, true)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, true)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, true)
  expect(dut.io.done, false)
  step(5)

  // STDI
  poke(dut.io.opcode, Integer.parseInt("01110000",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, true)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, true)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, true)
  expect(dut.io.done, false)
  step(5)



  // J-type
  // JMP
  poke(dut.io.opcode, Integer.parseInt("10001111",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 15)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JEQ
  poke(dut.io.opcode, Integer.parseInt("10001001",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 9)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JNEQ
  poke(dut.io.opcode, Integer.parseInt("10001010",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 10)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JGT
  poke(dut.io.opcode, Integer.parseInt("10001011",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 11)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JGE
  poke(dut.io.opcode, Integer.parseInt("10001100",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 12)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JLT
  poke(dut.io.opcode, Integer.parseInt("10001101",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 13)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)

  // JLE
  poke(dut.io.opcode, Integer.parseInt("10001110",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 14)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, false)
  step(5)



  // END-type
  // END
  poke(dut.io.opcode, Integer.parseInt("11000000",2))
  expect(dut.io.regWrite, false)
  expect(dut.io.dataWrite, false)
  expect(dut.io.aluSel, 0)
  expect(dut.io.memRegWrite, false)
  expect(dut.io.immediateOp, false)
  expect(dut.io.immediateAddr, false)
  expect(dut.io.immediateRegWrite, false)
  expect(dut.io.immediateWriteSel, false)
  expect(dut.io.done, true)

}

object ControlUnitTester {
  def main(args: Array[String]): Unit = {
    println("Testing ControlUnit")
    iotesters.Driver.execute(
      Array("--generate-vcd-output", "on",
        "--target-dir", "generated",
        "--top-name", "ControlUnit"),
      () => new ControlUnit()) {
      c => new ControlUnitTester(c)
    }
  }
}
