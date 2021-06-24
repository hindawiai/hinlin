<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh3/mmu_context.h
 *
 * Copyright (C) 1999 Niibe Yutaka
 */
#अगर_अघोषित __ASM_CPU_SH3_MMU_CONTEXT_H
#घोषणा __ASM_CPU_SH3_MMU_CONTEXT_H

#घोषणा MMU_PTEH	0xFFFFFFF0	/* Page table entry रेजिस्टर HIGH */
#घोषणा MMU_PTEL	0xFFFFFFF4	/* Page table entry रेजिस्टर LOW */
#घोषणा MMU_TTB		0xFFFFFFF8	/* Translation table base रेजिस्टर */
#घोषणा MMU_TEA		0xFFFFFFFC	/* TLB Exception Address */

#घोषणा MMUCR		0xFFFFFFE0	/* MMU Control Register */
#घोषणा MMUCR_TI	(1 << 2)	/* TLB flush bit */

#घोषणा MMU_TLB_ADDRESS_ARRAY	0xF2000000
#घोषणा MMU_PAGE_ASSOC_BIT	0x80

#घोषणा MMU_NTLB_ENTRIES	128	/* क्रम 7708 */
#घोषणा MMU_NTLB_WAYS		4
#घोषणा MMU_CONTROL_INIT	0x007	/* SV=0, TF=1, IX=1, AT=1 */

#घोषणा TRA	0xffffffd0
#घोषणा EXPEVT	0xffffffd4

#अगर defined(CONFIG_CPU_SUBTYPE_SH7705) || \
    defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7712) || \
    defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)
#घोषणा INTEVT	0xa4000000	/* INTEVTE2(0xa4000000) */
#अन्यथा
#घोषणा INTEVT	0xffffffd8
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CPU_SH3_MMU_CONTEXT_H */

