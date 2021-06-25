<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ross.h: Ross module specअगरic definitions and defines.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_ROSS_H
#घोषणा _SPARC_ROSS_H

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/page.h>

/* Ross made Hypersparcs have a %psr 'impl' field of '0001'.  The 'vers'
 * field has '1111'.
 */

/* The MMU control रेजिस्टर fields on the HyperSparc.
 *
 * -----------------------------------------------------------------
 * |implvers| RSV |CWR|SE|WBE| MID |BM| C|CS|MR|CM|RSV|CE|RSV|NF|ME|
 * -----------------------------------------------------------------
 *  31    24 23-22 21  20  19 18-15 14 13 12 11 10  9   8 7-2  1  0
 *
 * Phew, lots of fields there ;-)
 *
 * CWR: Cache Wrapping Enabled, अगर one cache wrapping is on.
 * SE: Snoop Enable, turns on bus snooping क्रम cache activity अगर one.
 * WBE: Write Buffer Enable, one turns it on.
 * MID: The ModuleID of the chip क्रम MBus transactions.
 * BM: Boot-Mode. One indicates the MMU is in boot mode.
 * C: Indicates whether accesses are cachable जबतक the MMU is
 *    disabled.
 * CS: Cache Size -- 0 = 128k, 1 = 256k
 * MR: Memory Reflection, one indicates that the memory bus connected
 *     to the MBus supports memory reflection.
 * CM: Cache Mode -- 0 = ग_लिखो-through, 1 = copy-back
 * CE: Cache Enable -- 0 = no caching, 1 = cache is on
 * NF: No Fault -- 0 = faults trap the CPU from supervisor mode
 *                 1 = faults from supervisor mode करो not generate traps
 * ME: MMU Enable -- 0 = MMU is off, 1 = MMU is on
 */

#घोषणा HYPERSPARC_CWENABLE   0x00200000
#घोषणा HYPERSPARC_SBENABLE   0x00100000
#घोषणा HYPERSPARC_WBENABLE   0x00080000
#घोषणा HYPERSPARC_MIDMASK    0x00078000
#घोषणा HYPERSPARC_BMODE      0x00004000
#घोषणा HYPERSPARC_ACENABLE   0x00002000
#घोषणा HYPERSPARC_CSIZE      0x00001000
#घोषणा HYPERSPARC_MRFLCT     0x00000800
#घोषणा HYPERSPARC_CMODE      0x00000400
#घोषणा HYPERSPARC_CENABLE    0x00000100
#घोषणा HYPERSPARC_NFAULT     0x00000002
#घोषणा HYPERSPARC_MENABLE    0x00000001


/* The ICCR inकाष्ठाion cache रेजिस्टर on the HyperSparc.
 *
 * -----------------------------------------------
 * |                                 | FTD | ICE |
 * -----------------------------------------------
 *  31                                  1     0
 *
 * This रेजिस्टर is accessed using the V8 'wrasr' and 'rdasr'
 * opcodes, since not all assemblers understand them and those
 * that करो use dअगरferent semantics I will just hard code the
 * inकाष्ठाion with a '.word' statement.
 *
 * FTD:  If set to one flush inकाष्ठाions executed during an
 *       inकाष्ठाion cache hit occurs, the corresponding line
 *       क्रम said cache-hit is invalidated.  If FTD is zero,
 *       an unimplemented 'flush' trap will occur when any
 *       flush is executed by the processor.
 *
 * ICE:  If set to one, the inकाष्ठाion cache is enabled.  If
 *       zero, the cache will not be used क्रम inकाष्ठाion fetches.
 *
 * All other bits are पढ़ो as zeros, and ग_लिखोs to them have no
 * effect.
 *
 * Wheee, not many assemblers understand the %iccr रेजिस्टर nor
 * the generic asr r/w inकाष्ठाions.
 *
 *  1000 0011 0100 0111 1100 0000 0000 0000   ! rd %iccr, %g1
 *
 * 0x  8    3    4    7    c    0    0    0   ! 0x8347c000
 *
 *  1011 1111 1000 0000 0110 0000 0000 0000   ! wr %g1, 0x0, %iccr
 *
 * 0x  b    f    8    0    6    0    0    0   ! 0xbf806000
 *
 */

#घोषणा HYPERSPARC_ICCR_FTD     0x00000002
#घोषणा HYPERSPARC_ICCR_ICE     0x00000001

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत अचिन्हित पूर्णांक get_ross_icr(व्योम)
अणु
	अचिन्हित पूर्णांक icreg;

	__यंत्र__ __अस्थिर__(".word 0x8347c000\n\t" /* rd %iccr, %g1 */
			     "mov %%g1, %0\n\t"
			     : "=r" (icreg)
			     : /* no inमाला_दो */
			     : "g1", "memory");

	वापस icreg;
पूर्ण

अटल अंतरभूत व्योम put_ross_icr(अचिन्हित पूर्णांक icreg)
अणु
	__यंत्र__ __अस्थिर__("or %%g0, %0, %%g1\n\t"
			     ".word 0xbf806000\n\t" /* wr %g1, 0x0, %iccr */
			     "nop\n\t"
			     "nop\n\t"
			     "nop\n\t"
			     : /* no outमाला_दो */
			     : "r" (icreg)
			     : "g1", "memory");

	वापस;
पूर्ण

/* HyperSparc specअगरic cache flushing. */

/* This is क्रम the on-chip inकाष्ठाion cache. */
अटल अंतरभूत व्योम hyper_flush_whole_icache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_FLUSH_IWHOLE)
			     : "memory");
	वापस;
पूर्ण

बाह्य पूर्णांक vac_cache_size;
बाह्य पूर्णांक vac_line_size;

अटल अंतरभूत व्योम hyper_clear_all_tags(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम(addr = 0; addr < vac_cache_size; addr += vac_line_size)
		__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
				     : /* no outमाला_दो */
				     : "r" (addr), "i" (ASI_M_DATAC_TAG)
				     : "memory");
पूर्ण

अटल अंतरभूत व्योम hyper_flush_unconditional_combined(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = 0; addr < vac_cache_size; addr += vac_line_size)
		__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
				     : /* no outमाला_दो */
				     : "r" (addr), "i" (ASI_M_FLUSH_CTX)
				     : "memory");
पूर्ण

अटल अंतरभूत व्योम hyper_flush_cache_user(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = 0; addr < vac_cache_size; addr += vac_line_size)
		__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
				     : /* no outमाला_दो */
				     : "r" (addr), "i" (ASI_M_FLUSH_USER)
				     : "memory");
पूर्ण

अटल अंतरभूत व्योम hyper_flush_cache_page(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ end;

	page &= PAGE_MASK;
	end = page + PAGE_SIZE;
	जबतक (page < end) अणु
		__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
				     : /* no outमाला_दो */
				     : "r" (page), "i" (ASI_M_FLUSH_PAGE)
				     : "memory");
		page += vac_line_size;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(_SPARC_ROSS_H) */
