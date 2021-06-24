<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* swअगरt.h: Specअगरic definitions क्रम the _broken_ Swअगरt SRMMU
 *          MMU module.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_SWIFT_H
#घोषणा _SPARC_SWIFT_H

/* Swअगरt is so brain damaged, here is the mmu control रेजिस्टर. */
#घोषणा SWIFT_ST       0x00800000   /* SW tablewalk enable */
#घोषणा SWIFT_WP       0x00400000   /* Watchpoपूर्णांक enable   */

/* Branch folding (buggy, disable on production प्रणालीs!)  */
#घोषणा SWIFT_BF       0x00200000
#घोषणा SWIFT_PMC      0x00180000   /* Page mode control   */
#घोषणा SWIFT_PE       0x00040000   /* Parity enable       */
#घोषणा SWIFT_PC       0x00020000   /* Parity control      */
#घोषणा SWIFT_AP       0x00010000   /* Graphics page mode control (TCX/SX) */
#घोषणा SWIFT_AC       0x00008000   /* Alternate Cacheability (see viking.h) */
#घोषणा SWIFT_BM       0x00004000   /* Boot mode */
#घोषणा SWIFT_RC       0x00003c00   /* DRAM refresh control */
#घोषणा SWIFT_IE       0x00000200   /* Inकाष्ठाion cache enable */
#घोषणा SWIFT_DE       0x00000100   /* Data cache enable */
#घोषणा SWIFT_SA       0x00000080   /* Store Allocate */
#घोषणा SWIFT_NF       0x00000002   /* No fault mode */
#घोषणा SWIFT_EN       0x00000001   /* MMU enable */

/* Bits [13:5] select one of 512 inकाष्ठाion cache tags */
अटल अंतरभूत व्योम swअगरt_inv_insn_tag(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_TXTC_TAG)
			     : "memory");
पूर्ण

/* Bits [12:4] select one of 512 data cache tags */
अटल अंतरभूत व्योम swअगरt_inv_data_tag(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_DATAC_TAG)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम swअगरt_flush_dcache(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = 0; addr < 0x2000; addr += 0x10)
		swअगरt_inv_data_tag(addr);
पूर्ण

अटल अंतरभूत व्योम swअगरt_flush_icache(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = 0; addr < 0x4000; addr += 0x20)
		swअगरt_inv_insn_tag(addr);
पूर्ण

अटल अंतरभूत व्योम swअगरt_idflash_clear(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = 0; addr < 0x2000; addr += 0x10) अणु
		swअगरt_inv_insn_tag(addr<<1);
		swअगरt_inv_data_tag(addr);
	पूर्ण
पूर्ण

/* Swअगरt is so broken, it isn't even safe to use the following. */
अटल अंतरभूत व्योम swअगरt_flush_page(अचिन्हित दीर्घ page)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (page), "i" (ASI_M_FLUSH_PAGE)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम swअगरt_flush_segment(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_FLUSH_SEG)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम swअगरt_flush_region(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t"
			     : /* no outमाला_दो */
			     : "r" (addr), "i" (ASI_M_FLUSH_REGION)
			     : "memory");
पूर्ण

अटल अंतरभूत व्योम swअगरt_flush_context(व्योम)
अणु
	__यंत्र__ __अस्थिर__("sta %%g0, [%%g0] %0\n\t"
			     : /* no outमाला_दो */
			     : "i" (ASI_M_FLUSH_CTX)
			     : "memory");
पूर्ण

#पूर्ण_अगर /* !(_SPARC_SWIFT_H) */
