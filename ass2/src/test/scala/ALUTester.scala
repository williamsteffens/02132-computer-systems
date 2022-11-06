import chisel3.iotesters
import chisel3.iotesters.PeekPokeTester

class ALUTester(dut: ALU) extends PeekPokeTester(dut) {

  // Add operation, 2 + 2 = 4
  poke(dut.io.sel, 0)
  poke(dut.io.op1, 2)
  poke(dut.io.op2, 2)
  expect(dut.io.result, 4)
  step(5)

  // Subtract operation, 6-3 = 3
  poke(dut.io.sel, 1)
  poke(dut.io.op1, 6)
  poke(dut.io.op2, 3)
  expect(dut.io.result, 3)
  step(5)

  // Multiplication operation, 3*3=6
  poke(dut.io.sel, 2)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 3)
  expect(dut.io.result, 9)
  step(5)

  // Increment operation, 4+1=5
  poke(dut.io.sel, 3)
  poke(dut.io.op1, 4)
  poke(dut.io.op2, 10)
  expect(dut.io.result, 5)
  step(5)

  // Decrement operation, 3-1=2
  poke(dut.io.sel, 4)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 10)
  expect(dut.io.result, 2)
  step(5)

  // Bitwise NOT operation, !0 = 4294967295L
  poke(dut.io.sel, 5)
  poke(dut.io.op1, 0)
  poke(dut.io.op2, 22)
  expect(dut.io.result, 4294967295L)
  step(5)

  // Bitwise AND operation, 9 & 14 = 8
  poke(dut.io.sel, 6)
  poke(dut.io.op1, 9)
  poke(dut.io.op2, 14)
  expect(dut.io.result, 8)
  step(5)

  // Bitwise OR operation, 9 | 14 = 15
  poke(dut.io.sel, 7)
  poke(dut.io.op1, 9)
  poke(dut.io.op2, 14)
  expect(dut.io.result, 15)
  step(5)

  // Bitwise XOR operation, 9 ^ 14 = 7
  poke(dut.io.sel, 8)
  poke(dut.io.op1, 9)
  poke(dut.io.op2, 14)
  expect(dut.io.result, 7)
  step(5)

  // Equality operation, 4 == 4 = true
  poke(dut.io.sel, 9)
  poke(dut.io.op1, 4)
  poke(dut.io.op2, 4)
  expect(dut.io.cmpResult, true)
  step(5)

  // Equality operation, 4 == 5 = false
  poke(dut.io.sel, 9)
  poke(dut.io.op1, 4)
  poke(dut.io.op2, 5)
  expect(dut.io.cmpResult, false)
  step(5)

  // Inequality operation, 6=/=1 = true
  poke(dut.io.sel, 10)
  poke(dut.io.op1, 6)
  poke(dut.io.op2, 1)
  expect(dut.io.cmpResult, true)
  step(5)

  // Inequality operation, 6=/=6 = false
  poke(dut.io.sel, 10)
  poke(dut.io.op1, 6)
  poke(dut.io.op2, 6)
  expect(dut.io.cmpResult, false)
  step(5)

  // Greater than operation, 8>7 = true
  poke(dut.io.sel, 11)
  poke(dut.io.op1, 8)
  poke(dut.io.op2, 7)
  expect(dut.io.cmpResult, true)
  step(5)

  // Greater than operation, 8>8 = false
  poke(dut.io.sel, 11)
  poke(dut.io.op1, 8)
  poke(dut.io.op2, 8)
  expect(dut.io.cmpResult, false)
  step(5)

  // Greater than or equal operation, 7>=7 = true
  poke(dut.io.sel, 12)
  poke(dut.io.op1, 7)
  poke(dut.io.op2, 7)
  expect(dut.io.cmpResult, true)
  step(5)

  // Greater than or equal operation, 7>=8 = false
  poke(dut.io.sel, 12)
  poke(dut.io.op1, 7)
  poke(dut.io.op2, 8)
  expect(dut.io.cmpResult, false)
  step(5)

  // Less than operation, 3<4 = true
  poke(dut.io.sel, 13)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 4)
  expect(dut.io.cmpResult, true)
  step(5)

  // Less than operation, 3<2 = false
  poke(dut.io.sel, 13)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 4)
  expect(dut.io.cmpResult, true)
  step(5)

  // Less than or equal operation, 3<=3 = true
  poke(dut.io.sel, 14)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 3)
  expect(dut.io.cmpResult, true)
  step(5)

  // Less than or equal operation, 3<=1 = true
  poke(dut.io.sel, 14)
  poke(dut.io.op1, 3)
  poke(dut.io.op2, 1)
  expect(dut.io.cmpResult, false)
  step(5)

  // unconditional jump
  poke(dut.io.sel, 15)
  poke(dut.io.op1, 234)
  poke(dut.io.op2, 22)
  expect(dut.io.cmpResult, true)
  step(5)

}

object ALUTester {
  def main(args: Array[String]): Unit = {
    println("Testing ALU")
    iotesters.Driver.execute(
      Array("--generate-vcd-output", "on",
        "--target-dir", "generated",
        "--top-name", "ALU"),
      () => new ALU()) {
      c => new ALUTester(c)
    }
  }
}
