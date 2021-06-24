<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * viking.h:  Defines specअगरic to the GNU/Viking MBUS module.
 *            This is SRMMU stuff.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_VIKING_H
#घोषणा _SPARC_VIKING_H

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/mxcc.h>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/pgtsrmmu.h>

/* Bits in the SRMMU control रेजिस्टर क्रम GNU/Viking modules.
 *
 * -----------------------------------------------------------
 * |impl-vers| RSV |TC|AC|SP|BM|PC|MBM|SB|IC|DC|PSO|RSV|NF|ME|
 * -----------------------------------------------------------
 *  31     24 23-17 16 15 14 13 12 11  10  9  8  7  6-2  1  0
 *
 * TC: Tablewalk Cacheable -- 0 = Twalks are not cacheable in E-cache
 *                            1 = Twalks are cacheable in E-cache
 *
 * GNU/Viking will only cache tablewalks in the E-cache (mxcc) अगर present
 * and never caches them पूर्णांकernally (or so states the करोcs).  Thereक्रमe
 * क्रम machines lacking an E-cache (ie. in MBUS mode) this bit must
 * reमुख्य cleared.
 *
 * AC: Alternate Cacheable -- 0 = Passthru physical accesses not cacheable
 *                            1 = Passthru physical accesses cacheable
 *
 * This indicates whether accesses are cacheable when no cachable bit
 * is present in the pte when the processor is in boot-mode or the
 * access करोes not need pte's for translation (ie. pass-thru ASI's).
 * "Cachable" is only referring to E-cache (अगर present) and not the
 * on chip split I/D caches of the GNU/Viking.
 *
 * SP: SnooP Enable -- 0 = bus snooping off, 1 = bus snooping on
 *
 * This enables snooping on the GNU/Viking bus.  This must be on
 * क्रम the hardware cache consistency mechanisms of the GNU/Viking
 * to work at all.  On non-mxcc GNU/Viking modules the split I/D
 * caches will snoop regardless of whether they are enabled, this
 * takes care of the हाल where the I or D or both caches are turned
 * off yet still contain valid data.  Note also that this bit करोes
 * not affect GNU/Viking store-buffer snoops, those happen अगर the
 * store-buffer is enabled no matter what.
 *
 * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode
 *
 * This indicates whether the GNU/Viking is in boot-mode or not,
 * अगर it is then all inकाष्ठाion fetch physical addresses are
 * computed as 0xff0000000 + low 28 bits of requested address.
 * GNU/Viking boot-mode करोes not affect data accesses.  Also,
 * in boot mode inकाष्ठाion accesses bypass the split on chip I/D
 * caches, they may be cached by the GNU/MXCC अगर present and enabled.
 *
 * MBM: MBus Mode -- 0 = not in MBus mode, 1 = in MBus mode
 *
 * This indicated the GNU/Viking configuration present.  If in
 * MBUS mode, the GNU/Viking lacks a GNU/MXCC E-cache.  If it is
 * not then the GNU/Viking is on a module VBUS connected directly
 * to a GNU/MXCC cache controller.  The GNU/MXCC can be thus connected
 * to either an GNU/MBUS (sun4m) or the packet-चयनed GNU/XBus (sun4d).
 *
 * SB: StoreBuffer enable -- 0 = store buffer off, 1 = store buffer on
 *
 * The GNU/Viking store buffer allows the chip to जारी execution
 * after a store even अगर the data cannot be placed in one of the
 * caches during that cycle.  If disabled, all stores operations
 * occur synchronously.
 *
 * IC: Inकाष्ठाion Cache -- 0 = off, 1 = on
 * DC: Data Cache -- 0 = off, 1 = 0n
 *
 * These bits enable the on-cpu GNU/Viking split I/D caches.  Note,
 * as mentioned above, these caches will snoop the bus in GNU/MBUS
 * configurations even when disabled to aव्योम data corruption.
 *
 * NF: No Fault -- 0 = faults generate traps, 1 = faults करोn't trap
 * ME: MMU enable -- 0 = mmu not translating, 1 = mmu translating
 *
 */

#घोषणा VIKING_MMUENABLE    0x00000001
#घोषणा VIKING_NOFAULT      0x00000002
#घोषणा VIKING_PSO          0x00000080
#घोषणा VIKING_DCENABLE     0x00000100   /* Enable data cache */
#घोषणा VIKING_ICENABLE     0x00000200   /* Enable inकाष्ठाion cache */
#घोषणा VIKING_SBENABLE     0x00000400   /* Enable store buffer */
#घोषणा VIKING_MMODE        0x00000800   /* MBUS mode */
#घोषणा VIKING_PCENABLE     0x00001000   /* Enable parity checking */
#घोषणा VIKING_BMODE        0x00002000   
#घोषणा VIKING_SPENABLE     0x00004000   /* Enable bus cache snooping */
#घोषणा VIKING_ACENABLE     0x00008000   /* Enable alternate caching */
#घोषणा VIKING_TCENABLE     0x00010000   /* Enable table-walks to be cached */
#घोषणा VIKING_DPENABLE     0x00040000   /* Enable the data prefetcher */

/*
 * GNU/Viking Breakpoपूर्णांक Action Register fields.
 */
#घोषणा VIKING_ACTION_MIX   0x00001000   /* Enable multiple inकाष्ठाions */

/*
 * GNU/Viking Cache Tags.
 */
#घोषणा VIKING_PTAG_VALID   0x01000000   /* Cache block is valid */
#घोषणा VIKING_PTAG_सूचीTY   0x00010000   /* Block has been modअगरied */
#घोषणा VIKING_PTAG_SHARED  0x00000100   /* Shared with some other cache */

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम viking_flush_icache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_IC_FLCLEAR)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम viking_flush_dcache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_DC_FLCLEAR)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम viking_unlock_icache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (0x80000000), "i" (ASI_M_IC_FLCLEAR)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम viking_unlock_dcache(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (0x80000000), "i" (ASI_M_DC_FLCLEAR)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम viking_set_bpreg(अचिन्हित दीर्घ regval)
अणु
	__यंत्र__ __अस्थिर__("sta %0, [%%g0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (regval), "i" (ASI_M_ACTION)
			     : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ viking_get_bpreg(व्योम)
अणु
	अचिन्हित दीर्घ regval;

	__यंत्र__ __अस्थिर__("lda [%%g0] %1, %0\n\t"
			     : "=r" (regval)
			     : "i" (ASI_M_ACTION));
	वापस regval;
पूर्ण

अटल अंतरभूत व्योम viking_get_dcache_ptag(पूर्णांक set, पूर्णांक block,
					      अचिन्हित दीर्घ *data)
अणु
	अचिन्हित दीर्घ ptag = ((set & 0x7f) << 5) | ((block & 0x3) << 26) |
			     0x80000000;
	अचिन्हित दीर्घ info, page;

	__यंत्र__ __अस्थिर__ ("ldda [%2] %3, %%g2\n\t"
			      "or %%g0, %%g2, %0\n\t"
			      "or %%g0, %%g3, %1\n\t"
			      : "=r" (info), "=r" (page)
			      : "r" (ptag), "i" (ASI_M_DATAC_TAG)
			      : "g2", "g3");
	data[0] = info;
	data[1] = page;
पूर्ण

अटल अंतरभूत व्योम viking_mxcc_turn_off_parity(अचिन्हित दीर्घ *mregp,
						   अचिन्हित दीर्घ *mxcc_cregp)
अणु
	अचिन्हित दीर्घ mreg = *mregp;
	अचिन्हित दीर्घ mxcc_creg = *mxcc_cregp;

	mreg &= ~(VIKING_PCENABLE);
	mxcc_creg &= ~(MXCC_CTL_PARE);

	__यंत्र__ __अस्थिर__ ("set 1f, %%g2\n\t"
			      "andcc %%g2, 4, %%g0\n\t"
			      "bne 2f\n\t"
			      " nop\n"
			      "1:\n\t"
			      "sta %0, [%%g0] %3\n\t"
			      "sta %1, [%2] %4\n\t"
			      "b 1f\n\t"
			      " nop\n\t"
			      "nop\n"
			      "2:\n\t"
			      "sta %0, [%%g0] %3\n\t"
			      "sta %1, [%2] %4\n"
			      "1:\n\t"
			      : /* no output */
			      : "r" (mreg), "r" (mxcc_creg),
			        "r" (MXCC_CREG), "i" (ASI_M_MMUREGS),
			        "i" (ASI_M_MXCC)
			      : "g2", "memory", "cc");
	*mregp = mreg;
	*mxcc_cregp = mxcc_creg;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ viking_hwprobe(अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ val;

	vaddr &= PAGE_MASK;
	/* Probe all MMU entries. */
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     : "=r" (val)
			     : "r" (vaddr | 0x400), "i" (ASI_M_FLUSH_PROBE));
	अगर (!val)
		वापस 0;

	/* Probe region. */
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     : "=r" (val)
			     : "r" (vaddr | 0x200), "i" (ASI_M_FLUSH_PROBE));
	अगर ((val & SRMMU_ET_MASK) == SRMMU_ET_PTE) अणु
		vaddr &= ~PGसूची_MASK;
		vaddr >>= PAGE_SHIFT;
		वापस val | (vaddr << 8);
	पूर्ण

	/* Probe segment. */
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     : "=r" (val)
			     : "r" (vaddr | 0x100), "i" (ASI_M_FLUSH_PROBE));
	अगर ((val & SRMMU_ET_MASK) == SRMMU_ET_PTE) अणु
		vaddr &= ~PMD_MASK;
		vaddr >>= PAGE_SHIFT;
		वापस val | (vaddr << 8);
	पूर्ण

	/* Probe page. */
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     : "=r" (val)
			     : "r" (vaddr), "i" (ASI_M_FLUSH_PROBE));
	वापस val;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC_VIKING_H) */
