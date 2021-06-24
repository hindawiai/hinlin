<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2021 Sअगरive.
 */
#अगर_अघोषित ASM_ERRATA_LIST_H
#घोषणा ASM_ERRATA_LIST_H

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/venकरोrid_list.h>

#अगर_घोषित CONFIG_ERRATA_SIFIVE
#घोषणा	ERRATA_SIFIVE_CIP_453 0
#घोषणा	ERRATA_SIFIVE_CIP_1200 1
#घोषणा	ERRATA_SIFIVE_NUMBER 2
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

#घोषणा ALT_INSN_FAULT(x)						\
ALTERNATIVE(__stringअगरy(RISCV_PTR करो_trap_insn_fault),			\
	    __stringअगरy(RISCV_PTR sअगरive_cip_453_insn_fault_trp),	\
	    SIFIVE_VENDOR_ID, ERRATA_SIFIVE_CIP_453,			\
	    CONFIG_ERRATA_SIFIVE_CIP_453)

#घोषणा ALT_PAGE_FAULT(x)						\
ALTERNATIVE(__stringअगरy(RISCV_PTR करो_page_fault),			\
	    __stringअगरy(RISCV_PTR sअगरive_cip_453_page_fault_trp),	\
	    SIFIVE_VENDOR_ID, ERRATA_SIFIVE_CIP_453,			\
	    CONFIG_ERRATA_SIFIVE_CIP_453)
#अन्यथा /* !__ASSEMBLY__ */

#घोषणा ALT_FLUSH_TLB_PAGE(x)						\
यंत्र(ALTERNATIVE("sfence.vma %0", "sfence.vma", SIFIVE_VENDOR_ID,	\
		ERRATA_SIFIVE_CIP_1200, CONFIG_ERRATA_SIFIVE_CIP_1200)	\
		: : "r" (addr) : "memory")

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
