    ASS R0, 0;                       // Assign constans to registers
    ASS R9, 19; 
    ASS R10, 20;   
    ASS R15, 255;
    ASS R1, 0;                       // Outer for-loop, set x (R1) to 0
    JGT 81, R1, R9;             // Condition for outer for-loop
    ASS R2, 0;                       // Inner for-loop, set y to 0
    JGT 78, R1, R9;             // Condition for outer for-loop
    JEQ 11, R1, R0;               // Processing border pixel// if (x == 0) 
    JMP 16;
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
        JMP 77;                 // continue
    JEQ 18, R2, R0;                   // if (y == 0) 
    JMP 23;  
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
        JMP 77;                 // continue
    JEQ 25, R1, R9;              // if (x == 19) 
    JMP 30;
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
        JMP 77;                 // continue
    JEQ 32, R2, R9;              // if (y == 19) 
    JMP 37;
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
        JMP 77;                 // continue
    MULT R3, R2, R10;                       // Processing inner pixel // if (in_image(x,y) == 0) // y * 20                           
    ADD R3, R1, R3;                         // x + y * 20
    LOAD R3, R3;                            // R3 = mem(R3)
    JEQ 42, R3, R0;               // mem(32) == 0
    JMP 47;
        MULT R3, R2, R10;                   // Black pixel // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
    JMP 77;
    MULT R3, R2, R10;                      // White pixel, checking neighboring pixels // if (in_image(x - 1, y) == 0 or in_image(x + 1, y) == 0 or in_image(x, y - 1) == 0 or in_image(x, y + 1) == 0) // in_image(x - 1, y) == 0// R3 = y * 20
    SUBI R4, R1, 1;                        // R4 = x - 1
    ADD R3, R4, R3;                        // R3 = (x - 1) + y * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ 68, R3, R0;              // mem(R3) == 0
    MULT R3, R2, R10;                      // in_image(x + 1, y) == 0// R3 = y * 20
    ADDI R4, R1, 1;                        // R4 = x + 1
    ADD R3, R4, R3;                        // R3 = (x + 1) + y * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ 68, R3, R0;              // mem(R3) == 0 // in_image(x, y - 1) == 0
    SUBI R4, R2, 1;                        // R4 = y - 1
    MULT R3, R4, R10;                      // R3 = (y - 1) * 20
    ADD R3, R1, R3;                        // R3 = x + (y - 1) * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ 68, R3, R0;              // mem(R3) == 0 // in_image(x, y + 1) == 0
    ADDI R4, R2, 1;                        // R4 = y + 1
    MULT R3, R4, R10;                      // R3 = (y + 1) * 20
    ADD R3, R1, R3;                        // R3 = x + (y + 1) * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ 68, R3, R0;              // mem(R3) == 0
    JMP 73;
        MULT R3, R2, R10;                   // Erode // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
    JMP 77;
        MULT R3, R2, R10;                   // Do not erode // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, R3, 400;                       // x + y * 20 + 400
        STD R3, R15;                         // mem(out_image(x,y)) = 0
    INC R2;                             // ++y
    JMP 8;                  // Loop back
    INC R1;                             // ++x 
    JMP 6;                  // Loop back
    END;