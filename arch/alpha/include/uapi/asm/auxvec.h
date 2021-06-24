<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_ALPHA_AUXVEC_H
#घोषणा __ASM_ALPHA_AUXVEC_H

/* Reserve these numbers क्रम any future use of a VDSO.  */
#अगर 0
#घोषणा AT_SYSINFO		32
#घोषणा AT_SYSINFO_EHDR		33
#पूर्ण_अगर

/* More complete cache descriptions than AT_[DIU]CACHEBSIZE.  If the
   value is -1, then the cache करोesn't exist.  Otherwise:

      bit 0-3:	  Cache set-associativity; 0 means fully associative.
      bit 4-7:	  Log2 of cacheline size.
      bit 8-31:	  Size of the entire cache >> 8.
      bit 32-63:  Reserved.
*/

#घोषणा AT_L1I_CACHESHAPE	34
#घोषणा AT_L1D_CACHESHAPE	35
#घोषणा AT_L2_CACHESHAPE	36
#घोषणा AT_L3_CACHESHAPE	37

#घोषणा AT_VECTOR_SIZE_ARCH 4 /* entries in ARCH_DLINFO */

#पूर्ण_अगर /* __ASM_ALPHA_AUXVEC_H */
