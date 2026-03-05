/* ************************************************************************** */

#include "hardware.h"   // Defines hardware IO
#include <stdlib.h>

int main(void)
{
    Hardware_Setup();
    ANSELBCLR = 0b0000111000000000;

    __asm__ __volatile__(
        // Configure PORTG as OUTPUT (PMODA_4, PMODA_8 are on PORTG)
        "la   $s0, TRISG                   \n\t"
        "li   $t0, 0x0000                  \n\t"
        "sw   $t0, 0($s0)                  \n\t"
    );

    while (1)
    {
        __asm__ __volatile__(
            // ===== HIGH delay count =====
            "lui  $t0, 0x0000               \n\t"
            "ori  $t0, $t0, 0x028F          \n\t"

            // ===== LOW delay count =====
            "lui  $t4, 0x0000               \n\t"
            "ori  $t4, $t4, 0x028F          \n\t"

            // Output HIGH on PMODA_4 (RG6)  -> 0x0040
            "li   $t3, 0x0040               \n\t"
            "la   $s1, LATG                 \n\t"
            "sw   $t3, 0($s1)               \n\t"

            // HIGH interval
            "Loop_On:                       \n\t"
            "addi $t0, $t0, -1              \n\t"
            "bne  $t0, $zero, Loop_On       \n\t"
            "nop                            \n\t"

            // Output LOW
            "li   $t3, 0x0000               \n\t"
            "sw   $t3, 0($s1)               \n\t"

            // LOW interval
            "Loop_Off:                      \n\t"
            "addi $t4, $t4, -1              \n\t"
            "bne  $t4, $zero, Loop_Off      \n\t"
            "nop                            \n\t"
        );
    }

    return (EXIT_FAILURE);
}
