<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh3/cache.h
 *
 * Copyright (C) 1999 Niibe Yutaka
 */
#अगर_अघोषित __ASM_CPU_SH3_CACHE_H
#घोषणा __ASM_CPU_SH3_CACHE_H

#घोषणा L1_CACHE_SHIFT	4

#घोषणा SH_CACHE_VALID		1
#घोषणा SH_CACHE_UPDATED	2
#घोषणा SH_CACHE_COMBINED	4
#घोषणा SH_CACHE_ASSOC		8

#घोषणा SH_CCR		0xffffffec	/* Address of Cache Control Register */

#घोषणा CCR_CACHE_CE	0x01	/* Cache Enable */
#घोषणा CCR_CACHE_WT	0x02	/* Write-Through (क्रम P0,U0,P3) (अन्यथा ग_लिखोback) */
#घोषणा CCR_CACHE_CB	0x04	/* Write-Back (क्रम P1) (अन्यथा ग_लिखोthrough) */
#घोषणा CCR_CACHE_CF	0x08	/* Cache Flush */
#घोषणा CCR_CACHE_ORA	0x20	/* RAM mode */

#घोषणा CACHE_OC_ADDRESS_ARRAY	0xf0000000
#घोषणा CACHE_PHYSADDR_MASK	0x1ffffc00

#घोषणा CCR_CACHE_ENABLE	CCR_CACHE_CE
#घोषणा CCR_CACHE_INVALIDATE	CCR_CACHE_CF

#अगर defined(CONFIG_CPU_SUBTYPE_SH7705) || \
    defined(CONFIG_CPU_SUBTYPE_SH7710) || \
    defined(CONFIG_CPU_SUBTYPE_SH7720) || \
    defined(CONFIG_CPU_SUBTYPE_SH7721)
#घोषणा CCR3_REG	0xa40000b4
#घोषणा CCR_CACHE_16KB  0x00010000
#घोषणा CCR_CACHE_32KB	0x00020000
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CPU_SH3_CACHE_H */
