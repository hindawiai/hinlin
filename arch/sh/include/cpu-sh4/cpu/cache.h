<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh4/cache.h
 *
 * Copyright (C) 1999 Niibe Yutaka
 */
#अगर_अघोषित __ASM_CPU_SH4_CACHE_H
#घोषणा __ASM_CPU_SH4_CACHE_H

#घोषणा L1_CACHE_SHIFT	5

#घोषणा SH_CACHE_VALID		1
#घोषणा SH_CACHE_UPDATED	2
#घोषणा SH_CACHE_COMBINED	4
#घोषणा SH_CACHE_ASSOC		8

#घोषणा SH_CCR		0xff00001c	/* Address of Cache Control Register */
#घोषणा CCR_CACHE_OCE	0x0001	/* Opeअक्रम Cache Enable */
#घोषणा CCR_CACHE_WT	0x0002	/* Write-Through (क्रम P0,U0,P3) (अन्यथा ग_लिखोback)*/
#घोषणा CCR_CACHE_CB	0x0004	/* Copy-Back (क्रम P1) (अन्यथा ग_लिखोthrough) */
#घोषणा CCR_CACHE_OCI	0x0008	/* OC Invalidate */
#घोषणा CCR_CACHE_ORA	0x0020	/* OC RAM Mode */
#घोषणा CCR_CACHE_OIX	0x0080	/* OC Index Enable */
#घोषणा CCR_CACHE_ICE	0x0100	/* Inकाष्ठाion Cache Enable */
#घोषणा CCR_CACHE_ICI	0x0800	/* IC Invalidate */
#घोषणा CCR_CACHE_IIX	0x8000	/* IC Index Enable */
#अगर_अघोषित CONFIG_CPU_SH4A
#घोषणा CCR_CACHE_EMODE	0x80000000	/* EMODE Enable */
#पूर्ण_अगर

/* Default CCR setup: 8k+16k-byte cache,P1-wb,enable */
#घोषणा CCR_CACHE_ENABLE	(CCR_CACHE_OCE|CCR_CACHE_ICE)
#घोषणा CCR_CACHE_INVALIDATE	(CCR_CACHE_OCI|CCR_CACHE_ICI)

#घोषणा CACHE_IC_ADDRESS_ARRAY	0xf0000000
#घोषणा CACHE_OC_ADDRESS_ARRAY	0xf4000000

#घोषणा RAMCR			0xFF000074

#पूर्ण_अगर /* __ASM_CPU_SH4_CACHE_H */

