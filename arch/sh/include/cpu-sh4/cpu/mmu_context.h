<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh4/mmu_context.h
 *
 * Copyright (C) 1999 Niibe Yutaka
 */
#अगर_अघोषित __ASM_CPU_SH4_MMU_CONTEXT_H
#घोषणा __ASM_CPU_SH4_MMU_CONTEXT_H

#घोषणा MMU_PTEH	0xFF000000	/* Page table entry रेजिस्टर HIGH */
#घोषणा MMU_PTEL	0xFF000004	/* Page table entry रेजिस्टर LOW */
#घोषणा MMU_TTB		0xFF000008	/* Translation table base रेजिस्टर */
#घोषणा MMU_TEA		0xFF00000C	/* TLB Exception Address */
#घोषणा MMU_PTEA	0xFF000034	/* PTE assistance रेजिस्टर */
#घोषणा MMU_PTEAEX	0xFF00007C	/* PTE ASID extension रेजिस्टर */

#घोषणा MMUCR		0xFF000010	/* MMU Control Register */

#घोषणा MMU_TLB_ENTRY_SHIFT	8

#घोषणा MMU_ITLB_ADDRESS_ARRAY  0xF2000000
#घोषणा MMU_ITLB_ADDRESS_ARRAY2	0xF2800000
#घोषणा MMU_ITLB_DATA_ARRAY	0xF3000000
#घोषणा MMU_ITLB_DATA_ARRAY2	0xF3800000

#घोषणा MMU_UTLB_ADDRESS_ARRAY	0xF6000000
#घोषणा MMU_UTLB_ADDRESS_ARRAY2	0xF6800000
#घोषणा MMU_UTLB_DATA_ARRAY	0xF7000000
#घोषणा MMU_UTLB_DATA_ARRAY2	0xF7800000
#घोषणा MMU_PAGE_ASSOC_BIT	0x80

#अगर_घोषित CONFIG_MMU
#घोषणा MMUCR_AT		(1 << 0)
#अन्यथा
#घोषणा MMUCR_AT		(0)
#पूर्ण_अगर

#घोषणा MMUCR_TI		(1 << 2)

#घोषणा MMUCR_URB		0x00FC0000
#घोषणा MMUCR_URB_SHIFT		18
#घोषणा MMUCR_URB_NENTRIES	64
#घोषणा MMUCR_URC		0x0000FC00
#घोषणा MMUCR_URC_SHIFT		10

#अगर defined(CONFIG_32BIT) && defined(CONFIG_CPU_SUBTYPE_ST40)
#घोषणा MMUCR_SE		(1 << 4)
#अन्यथा
#घोषणा MMUCR_SE		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_HAS_PTEAEX
#घोषणा MMUCR_AEX		(1 << 6)
#अन्यथा
#घोषणा MMUCR_AEX		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_X2TLB
#घोषणा MMUCR_ME		(1 << 7)
#अन्यथा
#घोषणा MMUCR_ME		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_STORE_QUEUES
#घोषणा MMUCR_SQMD		(1 << 9)
#अन्यथा
#घोषणा MMUCR_SQMD		(0)
#पूर्ण_अगर

#घोषणा MMU_NTLB_ENTRIES	64
#घोषणा MMU_CONTROL_INIT	(MMUCR_AT | MMUCR_TI | MMUCR_SQMD | \
				 MMUCR_ME | MMUCR_SE | MMUCR_AEX)

#घोषणा TRA	0xff000020
#घोषणा EXPEVT	0xff000024
#घोषणा INTEVT	0xff000028

#पूर्ण_अगर /* __ASM_CPU_SH4_MMU_CONTEXT_H */

