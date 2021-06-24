<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 * m53xxacr.h -- ColdFire version 3 core cache support
 *
 * (C) Copyright 2010, Greg Ungerer <gerg@snapgear.com>
 */

/****************************************************************************/
#अगर_अघोषित m53xxacr_h
#घोषणा m53xxacr_h
/****************************************************************************/

/*
 * All varients of the ColdFire using version 3 cores have a similar
 * cache setup. They have a unअगरied inकाष्ठाion and data cache, with
 * configurable ग_लिखो-through or copy-back operation.
 */

/*
 * Define the Cache Control रेजिस्टर flags.
 */
#घोषणा CACR_EC		0x80000000	/* Enable cache */
#घोषणा CACR_ESB	0x20000000	/* Enable store buffer */
#घोषणा CACR_DPI	0x10000000	/* Disable invalidation by CPUSHL */
#घोषणा CACR_HLCK	0x08000000	/* Half cache lock mode */
#घोषणा CACR_CINVA	0x01000000	/* Invalidate cache */
#घोषणा CACR_DNFB	0x00000400	/* Inhibited fill buffer */
#घोषणा CACR_DCM_WT	0x00000000	/* Cacheable ग_लिखो-through */
#घोषणा CACR_DCM_CB	0x00000100	/* Cacheable copy-back */
#घोषणा CACR_DCM_PRE	0x00000200	/* Cache inhibited, precise */
#घोषणा CACR_DCM_IMPRE	0x00000300	/* Cache inhibited, imprecise */
#घोषणा CACR_WPROTECT	0x00000020	/* Write protect*/
#घोषणा CACR_EUSP	0x00000010	/* Eanble separate user a7 */

/*
 * Define the Access Control रेजिस्टर flags.
 */
#घोषणा ACR_BASE_POS	24		/* Address Base (upper 8 bits) */
#घोषणा ACR_MASK_POS	16		/* Address Mask (next 8 bits) */
#घोषणा ACR_ENABLE	0x00008000	/* Enable this ACR */
#घोषणा ACR_USER	0x00000000	/* Allow only user accesses */
#घोषणा ACR_SUPER	0x00002000	/* Allow supervisor access only */
#घोषणा ACR_ANY		0x00004000	/* Allow any access type */
#घोषणा ACR_CM_WT	0x00000000	/* Cacheable, ग_लिखो-through */
#घोषणा ACR_CM_CB	0x00000020	/* Cacheable, copy-back */
#घोषणा ACR_CM_PRE	0x00000040	/* Cache inhibited, precise */
#घोषणा ACR_CM_IMPRE	0x00000060	/* Cache inhibited, imprecise */
#घोषणा ACR_WPROTECT	0x00000004	/* Write protect region */

/*
 * Define the cache type and arrangement (needed क्रम pushes).
 */
#अगर defined(CONFIG_M5307)
#घोषणा	CACHE_SIZE	0x2000		/* 8k of unअगरied cache */
#घोषणा	ICACHE_SIZE	CACHE_SIZE
#घोषणा	DCACHE_SIZE	CACHE_SIZE
#या_अगर defined(CONFIG_M53xx)
#घोषणा	CACHE_SIZE	0x4000		/* 16k of unअगरied cache */
#घोषणा	ICACHE_SIZE	CACHE_SIZE
#घोषणा	DCACHE_SIZE	CACHE_SIZE
#पूर्ण_अगर

#घोषणा	CACHE_LINE_SIZE	16		/* 16 byte line size */
#घोषणा	CACHE_WAYS	4		/* 4 ways - set associative */

/*
 * Set the cache controller settings we will use. This शेष in the
 * CACR is cache inhibited, we use the ACR रेजिस्टर to set cacheing
 * enabled on the regions we want (eg RAM).
 */
#अगर defined(CONFIG_CACHE_COPYBACK)
#घोषणा CACHE_TYPE	ACR_CM_CB
#घोषणा CACHE_PUSH
#अन्यथा
#घोषणा CACHE_TYPE	ACR_CM_WT
#पूर्ण_अगर

#अगर_घोषित CONFIG_COLDFIRE_SW_A7
#घोषणा CACHE_MODE	(CACR_EC + CACR_ESB + CACR_DCM_PRE)
#अन्यथा
#घोषणा CACHE_MODE	(CACR_EC + CACR_ESB + CACR_DCM_PRE + CACR_EUSP)
#पूर्ण_अगर

/*
 * Unअगरied cache means we will never need to flush क्रम coherency of
 * inकाष्ठाion fetch. We will need to flush to मुख्यtain memory/DMA
 * coherency though in all हालs. And क्रम copyback caches we will need
 * to push cached data as well.
 */
#घोषणा CACHE_INIT        (CACHE_MODE + CACR_CINVA - CACR_EC)
#घोषणा CACHE_INVALIDATE  (CACHE_MODE + CACR_CINVA)
#घोषणा CACHE_INVALIDATED (CACHE_MODE + CACR_CINVA)

#घोषणा ACR0_MODE	((CONFIG_RAMBASE & 0xff000000) + \
			 (0x000f0000) + \
			 (ACR_ENABLE + ACR_ANY + CACHE_TYPE))
#घोषणा ACR1_MODE	0

/****************************************************************************/
#पूर्ण_अगर  /* m53xxsim_h */
