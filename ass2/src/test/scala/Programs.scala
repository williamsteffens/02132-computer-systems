import chisel3._
import chisel3.util._
import chisel3.iotesters
import chisel3.iotesters.PeekPokeTester
import java.util

object Programs{
  val program1 = Array(
    "b01010000000000010000000000000001".U(32.W), // ASS R1 1;
    "b01010000000000100000000000000001".U(32.W), // ASS R2 1;
    "b00000000000100010010000000000000".U(32.W), // ADD R2 R1 R1;
    "b11111111111111111111111111111111".U(32.W), // END;
  )

  val program2 = Array(
    "h03202000".U(32.W),      // 0 INC R2;
    "h8F000003".U(32.W),      // 1 JMP 3;
    "h03202000".U(32.W),      // 2 INC R2;
    "h03202000".U(32.W),      // 3 INC R2;
    "hFFFFFFFF".U(32.W),      // 4 END;
  )

  val programErosion = Array(
    // Assign vals to Regs
      "h50000000".U(32.W),    // 0    ASS R0, 0;
      "h50090013".U(32.W),    // 1    ASS R9, 19;
      "h500A0014".U(32.W),    // 2    ASS R10, 20;
      "h500F00FF".U(32.W),    // 3    ASS R15, 255;
    // For loop starts
      "h50010000".U(32.W),    // 4    ASS R1, x (0);
      "h8C190050".U(32.W),    // 5    JGT 80, R1 (x), R9 (19);
      "h50020000".U(32.W),    // 6    ASS R2, y (0);
      "h8C29004E".U(32.W),    // 7    JGT 78, R2 (y), R9 (19);
    // if (x == 0)
      "h8910000A".U(32.W),    // 8    JEQ 10, R1 (x), R0 (0);
      "h8F00000F".U(32.W),    // 9    JMP 15;
      "h022A3000".U(32.W),    // 10   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 11   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 12   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 13   STD R3, R0;
      "h8F00004C".U(32.W),    // 14   JMP 76;
    // if (y == 0)
      "h89200011".U(32.W),    // 15   JEQ 17, R2 (y), R0 (0);
      "h8F000016".U(32.W),    // 16   JMP 22;
      "h022A3000".U(32.W),    // 17   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 18   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 19   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 20   STD R3, R0;
      "h8F00004C".U(32.W),    // 21   JMP 76;
    // if (x == 19)
      "h89190018".U(32.W),    // 22   JEQ 24, R1, R9;
      "h8F00001D".U(32.W),    // 23   JMP 29;
      "h022A3000".U(32.W),    // 24   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 25   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 26   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 27   STD R3, R0;
      "h8F00004C".U(32.W),    // 28   JMP 76;
    // if (y == 19)
      "h8929001F".U(32.W),    // 29   JEQ 31, R1, R9;
      "h8F000024".U(32.W),    // 30   JMP 36;
      "h022A3000".U(32.W),    // 31   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 32   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 33   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 34   STD R3, R0;
      "h8F00004C".U(32.W),    // 35   JMP 76;
    // if (in_image(x,y) == 0)
      "h022A3000".U(32.W),    // 36   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 37   ADD R3, R1, R3;
      "h10303000".U(32.W),    // 38   LOAD R3, R3;
      "h89300029".U(32.W),    // 39   JEQ 41, R3, R0;
      "h8F00002E".U(32.W),    // 40   JMP 46;
    // Black pixel
      "h022A3000".U(32.W),    // 41   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 42   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 43   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 44   STD R3, R0;
      "h8F00004C".U(32.W),    // 45   JMP 76;
    // White pixel
    // if (in_image(x - 1, y) == 0 or ...
      "h022A3000".U(32.W),    // 46   MULT R3, R2, R10;
      "h41140001".U(32.W),    // 47   SUBI R4, R1, 1;
      "h00433000".U(32.W),    // 48   ADD R3, R4, R3;
      "h10303000".U(32.W),    // 49   LOAD R3, R3;
      "h89300043".U(32.W),    // 50   JEQ 67, R3, R0;
    // ... in_image(x + 1, y) == 0 or ...
      "h022A3000".U(32.W),    // 51   MULT R3, R2, R10;
      "h40140001".U(32.W),    // 52   ADDI R4, R1, 1;
      "h00433000".U(32.W),    // 53   ADD R3, R4, R3;
      "h10303000".U(32.W),    // 54   LOAD R3, R3;
      "h89300043".U(32.W),    // 55   JEQ 67, R3, R0;
    // ... in_image(x, y - 1) == 0 or ...
      "h41240001".U(32.W),    // 56   SUBI R4, R2, 1;
      "h024A3000".U(32.W),    // 57   MULT R3, R4, R10;
      "h00133000".U(32.W),    // 58   ADD R3, R1, R3;
      "h10303000".U(32.W),    // 59   LOAD R3, R3;
      "h89300043".U(32.W),    // 60   JEQ 67, R3, R0;
    // ... in_image(x, y + 1) == 0)
      "h40240001".U(32.W),    // 61   ADDI R4, R1, 1;
      "h024A3000".U(32.W),    // 62   MULT R3, R4, R10;
      "h00133000".U(32.W),    // 63   ADD R3, R1, R3;
      "h10303000".U(32.W),    // 64   LOAD R3, R3;
      "h89300043".U(32.W),    // 65   JEQ 67, R3, R0;
      "h8F000048".U(32.W),    // 66   JMP 72;
    // Erode
      "h022A3000".U(32.W),    // 67   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 68   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 69   ADDI R3, R3, 400;
      "h20300000".U(32.W),    // 70   STD R3, R0;
      "h8F00004C".U(32.W),    // 71   JMP 76;
    // Do not erode
      "h022A3000".U(32.W),    // 72   MULT R3, R2, R10;
      "h00133000".U(32.W),    // 73   ADD R3, R1, R3;
      "h40330190".U(32.W),    // 74   ADDI R3, R3, 400;
      "h203F0000".U(32.W),    // 75   STD R3, R15;
    // For loop ends
      "h03202000".U(32.W),    // 76   INC R2;
      "h8F000007".U(32.W),    // 77   JMP 7;
      "h03101000".U(32.W),    // 78   INC R1;
      "h8F000005".U(32.W),    // 79   JMP 5;
      "hFFFFFFFF".U(32.W),    // 80   END;
  )
}