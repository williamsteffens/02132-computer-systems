// hand compilation of erosion step

for x from 0 to 19
--------------------------------------------
ASS R1, 0                   // Set x to zero in mem(ax)
STD ax, R1;
LOOP_outer;                 // Label
////////////////////////
// Inside of the loop //
////////////////////////
LI R2, ax;                  // Inc x by 1
LAD R3, R2;
ADDI R1, R3, 1;
SD R1, R2                   // Store x in mem(ax)
LI R2, 20;
JLT LOOP_outer, R1, R2;     // Jump to LOOP_outer if x less than 20



if (x == 0) {...}
--------------------------------------------
LI R1, ax;                  // Load x in R2
LD R2, R1;
LI R1, 0;
JEQ IF_equal, R2, R1; 
JMP IFNOT_equal             // Jump past if not equal
IF_equal;
///////////////////////////
// Inside of if-statment //
///////////////////////////
IFNOT_equal;



if (x == 0) {...} else {...} 
--------------------------------------------
LI R1, ax;                  // Load x in R2
LD R2, R1;
LI R1, 0;                   // Load 0 in R1
JEQ IF_equal, R2, R1;       // Cmp x to 0
JMP ELSE_equal
IF_equal;
///////////////////////////
// Inside of if-statment //
///////////////////////////
JMP IFELSE_end;
ELSE_equal;
/////////////////////////////
// Inside of else-statment //
/////////////////////////////
IFELSE_end;



continue
--------------------------------------------
JMP LOOP_continue            // Jump inc x by 1 (end of loop)



some_image(x,y) = 0 
using the x + 20 * y, we get the following:
--------------------------------------------
LI R1, ay                   // Load y in R2
LD R2, R1
LI R1, 20                   // Load 20 in R1
MULT R3, R1, R2             // Calc product of R1 and R2, and store in R3
LI R1, ax                   // Load x in R2
LD R2, R1
ADD R1, R2, R3              // Calc sum of R2 and R3, and store in R1



// terminates execution
END;