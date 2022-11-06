import chisel3.iotesters
import chisel3.iotesters.PeekPokeTester

class RegisterFileTester(dut: RegisterFile) extends PeekPokeTester(dut) {

  // writeEnable low -> no write
  poke(dut.io.writeEnable, false)
  for (i <- 0 to 15) {
    poke(dut.io.writeSel,i)
    poke(dut.io.writeData, 22 + i)
    step(1)
    poke(dut.io.aSel,i)
    expect(dut.io.a,0)
    poke(dut.io.bSel,i)
    expect(dut.io.b,0)
    step(1)
  }
  step(5)

  // writeEnable high -> write
  poke(dut.io.writeEnable, true)
  for (i <- 0 to 15) {
    poke(dut.io.writeSel,i)
    poke(dut.io.writeData, 22 + i)
    step(1)
    poke(dut.io.aSel,i)
    expect(dut.io.a,22 + i)
    poke(dut.io.bSel,i)
    expect(dut.io.b,22 + i)
    step(1)
  }
  step(5)

}

object RegisterFileTester {
  def main(args: Array[String]): Unit = {
    println("Testing RegisterFile")
    iotesters.Driver.execute(
      Array("--generate-vcd-output", "on",
        "--target-dir", "generated",
        "--top-name", "RegisterFile"),
      () => new RegisterFile()) {
      c => new RegisterFileTester(c)
    }
  }
}
