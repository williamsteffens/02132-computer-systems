import chisel3._
import chisel3.util._

class Accelerator extends Module {
  val io = IO(new Bundle {
    val start       = Input(Bool())
    val done        = Output(Bool())

    val address     = Output(UInt (16.W))
    val dataRead    = Input(UInt (32.W))
    val writeEnable = Output(Bool ())
    val dataWrite   = Output(UInt (32.W))

  })

  //State enum and register
  val idle :: readCenterPixel :: readRightPixel :: readDownPixel :: readLeftPixel :: writePixel :: done :: Nil = Enum(7)
  val stateReg: UInt = RegInit(idle)

  // Variable Registers
  val xReg: UInt         = RegInit(0.U(5.W))
  val yReg: UInt         = RegInit(0.U(5.W))
  val addressReg: UInt   = RegInit(0.U(16.W))
  val erodeReg: Bool     = RegInit(false.B)
  val erodeNextReg: Bool = RegInit(false.B)

  // Border logic
  val borderPixel: Bool = WireDefault(false.B)
  borderPixel := xReg === 0.U | xReg === 19.U | yReg === 0.U | yReg === 19.U

  // Registers for saving the last row of pixels to reduce redundant memory reads
  val lastRowRegisters: Vec[Bool] = RegInit(VecInit(Seq.fill(20)(false.B)))

  // Default values
  io.done        := false.B
  io.writeEnable := false.B
  io.address     := 0.U(16.W)
  io.dataWrite   := erodeReg

  // FSMD switch
  switch (stateReg) {
    is (idle) {
      when (io.start) {
        stateReg := readCenterPixel
        addressReg := 0.U(16.W)
      }
    }

    is (readCenterPixel) {
      io.address := addressReg

      // Update lastRowRegisters
      when (io.dataRead === 0.U) {
        lastRowRegisters(xReg) := true.B
      } .otherwise {
        lastRowRegisters(xReg) := false.B
      }

      when (borderPixel | io.dataRead === 0.U | lastRowRegisters(xReg)) {
        erodeReg := true.B
        stateReg := writePixel
      } .otherwise {
        stateReg := readRightPixel
      }
    }

    is (readRightPixel) {
      io.address := addressReg + 1.U

      when (io.dataRead === 0.U) {
        erodeNextReg := true.B
        erodeReg := true.B
        stateReg := writePixel
      } .otherwise {
        stateReg := readDownPixel
      }
    }

    is (readDownPixel) {
      io.address := addressReg + 20.U

      when (io.dataRead === 0.U) {
        erodeReg := true.B
        stateReg := writePixel
      } .otherwise {
        stateReg := readLeftPixel
      }
    }

    is (readLeftPixel) {
      io.address := addressReg - 1.U
      when (io.dataRead === 0.U) {
        erodeReg := true.B
      } .otherwise {
        erodeReg := false.B
      }
      stateReg := writePixel
    }

    is (writePixel) {
      io.writeEnable := true.B
      io.address := addressReg + 400.U(16.W)
      addressReg := addressReg + 1.U(16.W)

      // Update x and y registers
      when (xReg < 19.U) {
        xReg := xReg + 1.U
      } .otherwise {
        xReg := 0.U
        yReg := yReg + 1.U
      }

      // Write out-pixel
      when (erodeReg) {
        io.dataWrite := 0.U(32.W)
      } .otherwise {
        io.dataWrite := 255.U(32.W)
      }

      when (addressReg === 399.U(16.W)) {
        stateReg := done
      } .elsewhen (erodeNextReg) {
        erodeReg := true.B
        erodeNextReg := false.B
        stateReg := writePixel
      } .otherwise {
        stateReg := readCenterPixel
      }
    }

    is (done) {
      io.done := true.B
    }
  }

}
