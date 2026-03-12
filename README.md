## Lab3 day 2:
1) for task 2 the problem we had was adding the masks from two ports and thgen writing it to only one latch.
2) what we have now is
   1) 1000 → RG8 / PMODA_9 → LATG = 0x0100 or bit 8 (0000 0001 0000 0000)
   2) 0100 → RC2 / PMODA_1 → LATC = 0x0004
   3) 0010 → RC1 / PMODA_2 → LATC = 0x0002
   4) 0001 → RG7 / PMODA_8 → LATG = 0x0080 
3) so now for the two phase we should storet 1001 , 1100 , 0110, 0011 which is:
  1) 1001 = RG8 + RG7 → LATG = 0x0180, LATC = 0x0000
  2) 1100 = RG8 + RC2 → LATG = 0x0100, LATC = 0x0004
  3) 0110 = RC2 + RC1 → LATG = 0x0000, LATC = 0x0006
  4) 0011 = RC1 + RG7 → LATG = 0x0080, LATC = 0x0002
4) and never ever comine Latch C bits with Latch G bits
