/* ************************************************************************** */

#include "hardware.h"   // Defines hardware IO
#include <stdlib.h>

int main(void)
{
    Hardware_Setup();   // Initialize switches, buttons and LEDs
    ANSELBCLR = 0b0000111000000000;  // ANSB9, ANSB10, ANSB11 = 0

    __asm__ __volatile__(
        // PORT C - PMODA_1, PMODA_2  (RC2, RC1)
        // PORT G - PMODA_9, PMODA_8  (RG8, RG7)

        // Configure PORTC as OUTPUT
        "la   $s0, TRISC                   \n\t"
        "li   $t0, 0x0000                  \n\t"
        "sw   $t0, 0($s0)                  \n\t"

        // Configure PORTG as OUTPUT
        "la   $s0, TRISG                   \n\t"
        "li   $t0, 0x0000                  \n\t"
        "sw   $t0, 0($s0)                  \n\t"

        // Disable analog on RG7 & RG8
        "la   $s0, ANSELGCLR               \n\t"
        "li   $t0, 0x0180                  \n\t"   // bits 7 and 8
        "sw   $t0, 0($s0)                  \n\t"
    );

    while (1)
    {
        __asm__ __volatile__(
            // delay counts
            "lui  $t0, 0x0000               \n\t"
            "ori  $t0, $t0, 0x028F          \n\t"

            "lui  $t4, 0x0000               \n\t"
            "ori  $t4, $t4, 0x028F          \n\t"

            // latch addresses
            "la   $s1, LATC                 \n\t"
            "la   $s2, LATG                 \n\t"


            // RG7 PMODA_8
            "li   $t3, 0x0000               \n\t"
            "sw   $t3, 0($s1)               \n\t"   // LATC = 0
            "li   $t3, 0x0080               \n\t"
            "sw   $t3, 0($s2)               \n\t"   // LATG bit7

            "Loop_1:                        \n\t"
            "addi $t0, $t0, -1              \n\t"
            "bne  $t0, $zero, Loop_1        \n\t"
            "nop                            \n\t"


            // RG8 PMODA_9
            "li   $t3, 0x0000               \n\t"
            "sw   $t3, 0($s1)               \n\t"
            "li   $t3, 0x0100               \n\t"
            "sw   $t3, 0($s2)               \n\t"

            "Loop_2:                        \n\t"
            "addi $t4, $t4, -1              \n\t"
            "bne  $t4, $zero, Loop_2        \n\t"
            "nop                            \n\t"


            // reload delays
            "lui  $t0, 0x0000               \n\t"
            "ori  $t0, $t0, 0x028F          \n\t"
            "lui  $t4, 0x0000               \n\t"
            "ori  $t4, $t4, 0x028F          \n\t"


            // RC2 (PMODA_1)
            "li   $t3, 0x0000               \n\t"
            "sw   $t3, 0($s2)               \n\t"   // LATG = 0
            "li   $t3, 0x0004               \n\t"
            "sw   $t3, 0($s1)               \n\t"   // LATC bit2

            "Loop_3:                        \n\t"
            "addi $t0, $t0, -1              \n\t"
            "bne  $t0, $zero, Loop_3        \n\t"
            "nop                            \n\t"


            // RC1 (PMODA_2)
            "li   $t3, 0x0000               \n\t"
            "sw   $t3, 0($s2)               \n\t"
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
