/* ************************************************************************** */

#include "hardware.h"   // Defines hardware IO
#include <stdlib.h>

int main(void)
{
    Hardware_Setup();   // Initialize switches, buttons and LEDs
    ANSELBCLR = 0b0000111000000000;  // ANSB9, ANSB10, ANSB11 = 0

    __asm__ __volatile__(
        // PORT A - ALL LEDs
        // PORT F - ALL SWITCHES SW0-SW7
        // PORT D - RGB LEDs
        // PORT C - PMODA pins

        // Configure PORTC as OUTPUT
        "la   $s0, TRISC                   \n\t"
        "li   $t0, 0b0000000000000000      \n\t"
        "sw   $t0, 0($s0)                  \n\t"
    );

    while (1)
    {
        __asm__ __volatile__(
            // ===== delay count (use same value for each step) =====
            "lui  $t0, 0x0000               \n\t"
            "ori  $t0, $t0, 0x028F          \n\t"

            "lui  $t4, 0x0000               \n\t"
            "ori  $t4, $t4, 0x028F          \n\t"

            // LATC address (same as your template)
            "la   $s1, LATC                 \n\t"


            // ========= Step 1: 1000 =========
            // RC4..RC1 = 1000  -> LATC[4:1] = 1 000 -> 0x0010
            "li   $t3, 0x0010               \n\t"
            "sw   $t3, 0($s1)               \n\t"

            "Loop_1:                        \n\t"
            "addi $t0, $t0, -1              \n\t"
            "bne  $t0, $zero, Loop_1        \n\t"
            "nop                            \n\t"


            // ========= Step 2: 0100 =========
            // RC4..RC1 = 0100 -> LATC[4:1] = 0 100 -> 0x0008
            "li   $t3, 0x0008               \n\t"
            "sw   $t3, 0($s1)               \n\t"

            "Loop_2:                        \n\t"
            "addi $t4, $t4, -1              \n\t"
            "bne  $t4, $zero, Loop_2        \n\t"
            "nop                            \n\t"


            // reload delays (same style, minimal change)
            "lui  $t0, 0x0000               \n\t"
            "ori  $t0, $t0, 0x028F          \n\t"
            "lui  $t4, 0x0000               \n\t"
            "ori  $t4, $t4, 0x028F          \n\t"


            // ========= Step 3: 0010 =========
            // RC4..RC1 = 0010 -> LATC[4:1] = 0 010 -> 0x0004
            "li   $t3, 0x0004               \n\t"
            "sw   $t3, 0($s1)               \n\t"

            "Loop_3:                        \n\t"
            "addi $t0, $t0, -1              \n\t"
            "bne  $t0, $zero, Loop_3        \n\t"
            "nop                            \n\t"


            // ========= Step 4: 0001 =========
            // RC4..RC1 = 0001 -> LATC[4:1] = 0 001 -> 0x0002
            "li   $t3, 0x0002               \n\t"
            "sw   $t3, 0($s1)               \n\t"

            "Loop_4:                        \n\t"
            "addi $t4, $t4, -1              \n\t"
            "bne  $t4, $zero, Loop_4        \n\t"
            "nop                            \n\t"
        );
    }

    return (EXIT_FAILURE);   // Should never reach this statement
}
