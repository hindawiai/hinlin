<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 * m52xxacr.h -- ColdFire version 2 core cache support
 *
 * (C) Copyright 2010, Greg Ungerer <gerg@snapgear.com>
 */

/****************************************************************************/
#अगर_अघोषित m52xxacr_h
#घोषणा m52xxacr_h
/****************************************************************************/

/*
 * All varients of the ColdFire using version 2 cores have a similar
 * cache setup. Although not असलolutely identical the cache रेजिस्टर
 * definitions are compatible क्रम all of them. Mostly they support a
 * configurable cache memory that can be inकाष्ठाion only, data only,
 * or split inकाष्ठाion and data. The exception is the very old version 2
 * core based parts, like the 5206(e), 5249 and 5272, which are inकाष्ठाion
 * cache only. Cache size varies from 2k up to 16k.
 */

/*
 * Define the Cache Control रेजिस्टर flags.
 */
#घोषणा CACR_CENB	0x80000000	/* Enable cache */
#घोषणा CACR_CDPI	0x10000000	/* Disable invalidation by CPUSHL */
#घोषणा CACR_CFRZ	0x08000000	/* Cache मुक्तze mode */
#घोषणा CACR_CINV	0x01000000	/* Invalidate cache */
#घोषणा CACR_DISI	0x00800000	/* Disable inकाष्ठाion cache */
#घोषणा CACR_DISD	0x00400000	/* Disable data cache */
#घोषणा CACR_INVI	0x00200000	/* Invalidate inकाष्ठाion cache */
#घोषणा CACR_INVD	0x00100000	/* Invalidate data cache */
#घोषणा CACR_CEIB	0x00000400	/* Non-cachable inकाष्ठाion burst */
#घोषणा CACR_DCM	0x00000200	/* Default cache mode */
#घोषणा CACR_DBWE	0x00000100	/* Buffered ग_लिखो enable */
#घोषणा CACR_DWP	0x00000020	/* Write protection */
#घोषणा CACR_EUSP	0x00000010	/* Enable separate user a7 */

/*
 * Define the Access Control रेजिस्टर flags.
 */
#घोषणा ACR_BASE_POS	24		/* Address Base (upper 8 bits) */
#घोषणा ACR_MASK_POS	16		/* Address Mask (next 8 bits) */
#घोषणा ACR_ENABLE	0x00008000	/* Enable this ACR */
#घोषणा ACR_USER	0x00000000	/* Allow only user accesses */
#घोषणा ACR_SUPER	0x00002000	/* Allow supervisor access only */
#घोषणा ACR_ANY		0x00004000	/* Allow any access type */
#घोषणा ACR_CENB	0x00000000	/* Caching of region enabled */
#घोषणा ACR_CDIS	0x00000040	/* Caching of region disabled */
#घोषणा ACR_BWE		0x00000020	/* Write buffer enabled */
#घोषणा ACR_WPROTECT	0x00000004	/* Write protect region */

/*
 * Set the cache controller settings we will use. On the cores that support
 * a split cache configuration we allow all the combinations at Kconfig
 * समय. For those cores that only have an inकाष्ठाion cache we just set
 * that as on.
 */
#अगर defined(CONFIG_CACHE_I)
#घोषणा CACHE_TYPE	(CACR_DISD + CACR_EUSP)
#घोषणा CACHE_INVTYPEI	0
#या_अगर defined(CONFIG_CACHE_D)
#घोषणा CACHE_TYPE	(CACR_DISI + CACR_EUSP)
#घोषणा CACHE_INVTYPED	0
#या_अगर defined(CONFIG_CACHE_BOTH)
#घोषणा CACHE_TYPE	CACR_EUSP
#घोषणा CACHE_INVTYPEI	CACR_INVI
#घोषणा CACHE_INVTYPED	CACR_INVD
#अन्यथा
/* This is the inकाष्ठाion cache only devices (no split cache, no eusp) */
#घोषणा CACHE_TYPE	0
#घोषणा CACHE_INVTYPEI	0
#पूर्ण_अगर

#घोषणा CACHE_INIT	(CACR_CINV + CACHE_TYPE)
#घोषणा CACHE_MODE	(CACR_CENB + CACHE_TYPE + CACR_DCM)

#घोषणा CACHE_INVALIDATE  (CACHE_MODE + CACR_CINV)
#अगर defined(CACHE_INVTYPEI)
#घोषणा CACHE_INVALIDATEI (CACHE_MODE + CACR_CINV + CACHE_INVTYPEI)
#पूर्ण_अगर
#अगर defined(CACHE_INVTYPED)
#घोषणा CACHE_INVALIDATED (CACHE_MODE + CACR_CINV + CACHE_INVTYPED)
#पूर्ण_अगर

#घोषणा ACR0_MODE	((CONFIG_RAMBASE & 0xff000000) + \
			 (0x000f0000) + \
			 (ACR_ENABLE + ACR_ANY + ACR_CENB + ACR_BWE))
#घोषणा ACR1_MODE	0

/****************************************************************************/
#पूर्ण_अगर  /* m52xxsim_h */
