<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh2/cache.h
 *
 * Copyright (C) 2003 Paul Mundt
 */
#अगर_अघोषित __ASM_CPU_SH2_CACHE_H
#घोषणा __ASM_CPU_SH2_CACHE_H

#घोषणा L1_CACHE_SHIFT	4

#घोषणा SH_CACHE_VALID		1
#घोषणा SH_CACHE_UPDATED	2
#घोषणा SH_CACHE_COMBINED	4
#घोषणा SH_CACHE_ASSOC		8

#अगर defined(CONFIG_CPU_SUBTYPE_SH7619)
#घोषणा SH_CCR		0xffffffec

#घोषणा CCR_CACHE_CE	0x01	/* Cache enable */
#घोषणा CCR_CACHE_WT	0x02    /* CCR[bit1=1,bit2=1] */
				/* 0x00000000-0x7fffffff: Write-through  */
				/* 0x80000000-0x9fffffff: Write-back     */
                                /* 0xc0000000-0xdfffffff: Write-through  */
#घोषणा CCR_CACHE_CB	0x04    /* CCR[bit1=0,bit2=0] */
				/* 0x00000000-0x7fffffff: Write-back     */
				/* 0x80000000-0x9fffffff: Write-through  */
                                /* 0xc0000000-0xdfffffff: Write-back     */
#घोषणा CCR_CACHE_CF	0x08	/* Cache invalidate */

#घोषणा CACHE_OC_ADDRESS_ARRAY	0xf0000000
#घोषणा CACHE_OC_DATA_ARRAY	0xf1000000

#घोषणा CCR_CACHE_ENABLE	CCR_CACHE_CE
#घोषणा CCR_CACHE_INVALIDATE	CCR_CACHE_CF
#घोषणा CACHE_PHYSADDR_MASK	0x1ffffc00

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CPU_SH2_CACHE_H */
