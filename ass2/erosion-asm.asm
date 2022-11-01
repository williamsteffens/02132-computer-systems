    ASS R0, 0;                       // Assign constans to registers
    ASS R9, 19; 
    ASS R10, 20;   
    ASS R15, 255;

    ASS R1, 0;                       // Outer for-loop, set x (R1) to 0
@XLOOP_START
    JGT @XLOOP_END, R1, R9;             // Condition for outer for-loop

    ASS R2, 0;                       // Inner for-loop, set y to 0
@YLOOP_START
    JGT @YLOOP_END, R1, R9;             // Condition for outer for-loop

// Processing border pixel
    JEQ @IF_XEQ0, R1, R0;               // if (x == 0) 
    JMP @END_XEQ0;
@IF_XEQ0
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0

        JMP @YLOOP_continue                 // continue
@END_XEQ0

    JEQ @IF_YEQ0, R2, R0;                   // if (y == 0) 
    JMP @END_YEQ0;  
@IF_YEQ0
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0

        JMP @YLOOP_continue                 // continue
@END_YEQ0
           
    JEQ @IF_XEQ19, R1, R9;              // if (x == 19) 
    JMP @END_XEQ19;
@IF_XEQ19
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0

        JMP @YLOOP_continue                 // continue
@END_XEQ19

    JEQ @IF_YEQ19, R2, R9;              // if (y == 19) 
    JMP @END_YEQ19;
@IF_YEQ19
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0

        JMP @YLOOP_continue                 // continue
@END_YEQ19

// Processing inner pixel
    // if (in_image(x,y) == 0)
    MULT R3, R2, R10;                       // y * 20                           
    ADD R3, R1, R3;                         // x + y * 20
    LOAD R3, R3;                            // R3 = mem(R3)
    JEQ @IF_IN_BLACK, R3, R0;               // mem(32) == 0
    JMP @ELSE_IN_BLACK;
@IF_IN_BLACK
// Black pixel
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
    JMP @END_IN_BLACK
@ELSE_IN_BLACK
// White pixel, checking neighboring pixels
    // if (in_image(x - 1, y) == 0 or in_image(x + 1, y) == 0 or in_image(x, y - 1) == 0 or in_image(x, y + 1) == 0)
    // in_image(x - 1, y) == 0
    MULT R3, R2, R10;                      // R3 = y * 20
    SUBI R4, R1, 1;                        // R4 = x - 1
    ADD R3, R4, R3;                        // R3 = (x - 1) + y * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ @IF_IN_WHITE, R3, R0;              // mem(R3) == 0

    // in_image(x + 1, y) == 0
    MULT R3, R2, R10;                      // R3 = y * 20
    ADDI R4, R1, 1;                        // R4 = x + 1
    ADD R3, R4, R3;                        // R3 = (x + 1) + y * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ @IF_IN_WHITE, R3, R0;              // mem(R3) == 0

    // in_image(x, y - 1) == 0
    SUBI R4, R2, 1;                        // R4 = y - 1
    MULT R3, R4, R10;                      // R3 = (y - 1) * 20
    ADD R3, R1, R3;                        // R3 = x + (y - 1) * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ @IF_IN_WHITE, R3, R0;              // mem(R3) == 0

    // in_image(x, y + 1) == 0
    ADDI R4, R2, 1;                        // R4 = y + 1
    MULT R3, R4, R10;                      // R3 = (y + 1) * 20
    ADD R3, R1, R3;                        // R3 = x + (y + 1) * 20
    LOAD R3, R3;                           // R3 = mem(R3)
    JEQ @IF_IN_WHITE, R3, R0;              // mem(R3) == 0

    JMP @ELSE_IN_WHITE;
@IF_IN_WHITE
// Erode
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R0;                         // mem(out_image(x,y)) = 0
    JMP @END_IN_WHITE
@ELSE_IN_WHITE
// Do not erode
        MULT R3, R2, R10;                   // out_image(x,y) = 0// y * 20 
        ADD R3, R1, R3;                     // x + y * 20
        ADDI R3, 400;                       // x + y * 20 + 400
        STD R3, R15;                         // mem(out_image(x,y)) = 0
@END_IN_WHITE

@END_IN_BLACK

@YLOOP_continue
    INC R2;                             // ++y
    JMP @YLOOP_STAT;                  // Loop back
@YLOOP_END
                      
    INC R1;                             // ++x 
    JMP @XLOOP_STAT;                  // Loop back
@XLOOP_END

    END;