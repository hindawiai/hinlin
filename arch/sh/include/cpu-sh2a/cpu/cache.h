<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh2a/cache.h
 *
 * Copyright (C) 2004 Paul Mundt
 */
#अगर_अघोषित __ASM_CPU_SH2A_CACHE_H
#घोषणा __ASM_CPU_SH2A_CACHE_H

#घोषणा L1_CACHE_SHIFT	4

#घोषणा SH_CACHE_VALID		1
#घोषणा SH_CACHE_UPDATED	2
#घोषणा SH_CACHE_COMBINED	4
#घोषणा SH_CACHE_ASSOC		8

#घोषणा SH_CCR		0xfffc1000 /* CCR1 */
#घोषणा SH_CCR2		0xfffc1004

/*
 * Most of the SH-2A CCR1 definitions resemble the SH-4 ones. All others not
 * listed here are reserved.
 */
#घोषणा CCR_CACHE_CB	0x0000	/* Hack */
#घोषणा CCR_CACHE_OCE	0x0001
#घोषणा CCR_CACHE_WT	0x0002
#घोषणा CCR_CACHE_OCI	0x0008	/* OCF */
#घोषणा CCR_CACHE_ICE	0x0100
#घोषणा CCR_CACHE_ICI	0x0800	/* ICF */

#घोषणा CACHE_IC_ADDRESS_ARRAY	0xf0000000
#घोषणा CACHE_OC_ADDRESS_ARRAY	0xf0800000

#घोषणा CCR_CACHE_ENABLE	(CCR_CACHE_OCE | CCR_CACHE_ICE)
#घोषणा CCR_CACHE_INVALIDATE	(CCR_CACHE_OCI | CCR_CACHE_ICI)
#घोषणा CCR_ICACHE_INVALIDATE	CCR_CACHE_ICI
#घोषणा CCR_OCACHE_INVALIDATE	CCR_CACHE_OCI
#घोषणा CACHE_PHYSADDR_MASK	0x1ffffc00

#पूर्ण_अगर /* __ASM_CPU_SH2A_CACHE_H */
