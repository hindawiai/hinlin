<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * turbosparc.h:  Defines specअगरic to the TurboSparc module.
 *            This is SRMMU stuff.
 *
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */
#अगर_अघोषित _SPARC_TURBOSPARC_H
#घोषणा _SPARC_TURBOSPARC_H

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/pgtsrmmu.h>

/* Bits in the SRMMU control रेजिस्टर क्रम TurboSparc modules.
 *
 * -------------------------------------------------------------------
 * |impl-vers| RSV| PMC |PE|PC| RSV |BM| RFR |IC|DC|PSO|RSV|ICS|NF|ME|
 * -------------------------------------------------------------------
 *  31    24 23-21 20-19 18 17 16-15 14 13-10  9  8  7  6-3   2  1  0
 *
 * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode
 *
 * This indicates whether the TurboSparc is in boot-mode or not.
 *
 * IC: Inकाष्ठाion Cache -- 0 = off, 1 = on
 * DC: Data Cache -- 0 = off, 1 = 0n
 *
 * These bits enable the on-cpu TurboSparc split I/D caches.
 *
 * ICS: ICache Snooping -- 0 = disable, 1 = enable snooping of icache
 * NF: No Fault -- 0 = faults generate traps, 1 = faults करोn't trap
 * ME: MMU enable -- 0 = mmu not translating, 1 = mmu translating
 *
 */

#घोषणा TURBOSPARC_MMUENABLE    0x00000001
#घोषणा TURBOSPARC_NOFAULT      0x00000002
#घोषणा TURBOSPARC_ICSNOOP	0x00000004
#घोषणा TURBOSPARC_PSO          0x00000080
#घोषणा TURBOSPARC_DCENABLE     0x00000100   /* Enable data cache */
#घोषणा TURBOSPARC_ICENABLE     0x00000200   /* Enable inकाष्ठाion cache */
#घोषणा TURBOSPARC_BMODE        0x00004000   
#घोषणा TURBOSPARC_PARITYODD	0x00020000   /* Parity odd, अगर enabled */
#घोषणा TURBOSPARC_PCENABLE	0x00040000   /* Enable parity checking */

/* Bits in the CPU configuration रेजिस्टर क्रम TurboSparc modules.
 *
 * -------------------------------------------------------
 * |IOClk|SNP|AXClk| RAH |  WS |  RSV  |SBC|WT|uS2|SE|SCC|
 * -------------------------------------------------------
 *    31   30 29-28 27-26 25-23   22-8  7-6  5  4   3 2-0
 *
 */

#घोषणा TURBOSPARC_SCENABLE 0x00000008	 /* Secondary cache enable */
#घोषणा TURBOSPARC_uS2	    0x00000010   /* Swअगरt compatibility mode */
#घोषणा TURBOSPARC_WTENABLE 0x00000020	 /* Write thru क्रम dcache */
#घोषणा TURBOSPARC_SNENABLE 0x40000000	 /* DVMA snoop enable */

#अगर_अघोषित __ASSEMBLY__

/* Bits [13:5] select one of 512 inकाष्ठाion cache tags */
अटल अंतरभूत व्योम turbosparc_inv_insn_tag(अचिन्हित दीर्घ addr)
अणु
        __यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_TXTC_TAG)
			     : "memory");
पूर्ण

/* Bits [13:5] select one of 512 data cache tags */
अटल अंतरभूत व्योम turbosparc_inv_data_tag(अचिन्हित दीर्घ addr)
अणु
        __यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_DATAC_TAG)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम turbosparc_flush_icache(व्योम)
अणु
	अचिन्हित दीर्घ addr;

        क्रम (addr = 0; addr < 0x4000; addr += 0x20)
                turbosparc_inv_insn_tag(addr);
पूर्ण

अटल अंतरभूत व्योम turbosparc_flush_dcache(व्योम)
अणु
	अचिन्हित दीर्घ addr;

        क्रम (addr = 0; addr < 0x4000; addr += 0x20)
                turbosparc_inv_data_tag(addr);
पूर्ण

अटल अंतरभूत व्योम turbosparc_idflash_clear(व्योम)
अणु
	अचिन्हित दीर्घ addr;

        क्रम (addr = 0; addr < 0x4000; addr += 0x20) अणु
                turbosparc_inv_insn_tag(addr);
                turbosparc_inv_data_tag(addr);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम turbosparc_set_ccreg(अचिन्हित दीर्घ regval)
अणु
	__यंत्र__ __अस्थिर__("sta %0, [%1] %2\n\t"
			     : /* no outमाला_दो */
			     : "r" (regval), "r" (0x600), "i" (ASI_M_MMUREGS)
			     : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ turbosparc_get_ccreg(व्योम)
अणु
	अचिन्हित दीर्घ regval;

	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     : "=r" (regval)
			     : "r" (0x600), "i" (ASI_M_MMUREGS));
	वापस regval;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC_TURBOSPARC_H) */
