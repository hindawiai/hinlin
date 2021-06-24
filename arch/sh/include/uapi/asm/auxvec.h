<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_AUXVEC_H
#घोषणा __ASM_SH_AUXVEC_H

/*
 * Architecture-neutral AT_ values in 0-17, leave some room
 * क्रम more of them.
 */

/*
 * This entry gives some inक्रमmation about the FPU initialization
 * perक्रमmed by the kernel.
 */
#घोषणा AT_FPUCW		18	/* Used FPU control word.  */

#अगर defined(CONFIG_VSYSCALL) || !defined(__KERNEL__)
/*
 * Only define this in the vsyscall हाल, the entry poपूर्णांक to
 * the vsyscall page माला_लो placed here. The kernel will attempt
 * to build a gate VMA we करोn't care about otherwise..
 */
#घोषणा AT_SYSINFO_EHDR		33
#पूर्ण_अगर

/*
 * More complete cache descriptions than AT_[DIU]CACHEBSIZE.  If the
 * value is -1, then the cache करोesn't exist.  Otherwise:
 *
 *    bit 0-3:	  Cache set-associativity; 0 means fully associative.
 *    bit 4-7:	  Log2 of cacheline size.
 *    bit 8-31:	  Size of the entire cache >> 8.
 */
#घोषणा AT_L1I_CACHESHAPE	34
#घोषणा AT_L1D_CACHESHAPE	35
#घोषणा AT_L2_CACHESHAPE	36

#घोषणा AT_VECTOR_SIZE_ARCH 5 /* entries in ARCH_DLINFO */

#पूर्ण_अगर /* __ASM_SH_AUXVEC_H */
