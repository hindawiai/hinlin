<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Bit definitions क्रम the MCF54xx ACR and CACR रेजिस्टरs.
 */

#अगर_अघोषित	m54xxacr_h
#घोषणा m54xxacr_h

/*
 *	Define the Cache रेजिस्टर flags.
 */
#घोषणा CACR_DEC	0x80000000	/* Enable data cache */
#घोषणा CACR_DWP	0x40000000	/* Data ग_लिखो protection */
#घोषणा CACR_DESB	0x20000000	/* Enable data store buffer */
#घोषणा CACR_DDPI	0x10000000	/* Disable invalidation by CPUSHL */
#घोषणा CACR_DHCLK	0x08000000	/* Half data cache lock mode */
#घोषणा CACR_DDCM_WT	0x00000000	/* Write through cache*/
#घोषणा CACR_DDCM_CP	0x02000000	/* Copyback cache */
#घोषणा CACR_DDCM_P	0x04000000	/* No cache, precise */
#घोषणा CACR_DDCM_IMP	0x06000000	/* No cache, imprecise */
#घोषणा CACR_DCINVA	0x01000000	/* Invalidate data cache */
#घोषणा CACR_BEC	0x00080000	/* Enable branch cache */
#घोषणा CACR_BCINVA	0x00040000	/* Invalidate branch cache */
#घोषणा CACR_IEC	0x00008000	/* Enable inकाष्ठाion cache */
#घोषणा CACR_DNFB	0x00002000	/* Inhibited fill buffer */
#घोषणा CACR_IDPI	0x00001000	/* Disable CPUSHL */
#घोषणा CACR_IHLCK	0x00000800	/* Inकाष्ठाion cache half lock */
#घोषणा CACR_IDCM	0x00000400	/* Inकाष्ठाion cache inhibit */
#घोषणा CACR_ICINVA	0x00000100	/* Invalidate instr cache */
#घोषणा CACR_EUSP	0x00000020	/* Enable separate user a7 */

#घोषणा ACR_BASE_POS	24		/* Address Base */
#घोषणा ACR_MASK_POS	16		/* Address Mask */
#घोषणा ACR_ENABLE	0x00008000	/* Enable address */
#घोषणा ACR_USER	0x00000000	/* User mode access only */
#घोषणा ACR_SUPER	0x00002000	/* Supervisor mode only */
#घोषणा ACR_ANY		0x00004000	/* Match any access mode */
#घोषणा ACR_CM_WT	0x00000000	/* Write through mode */
#घोषणा ACR_CM_CP	0x00000020	/* Copyback mode */
#घोषणा ACR_CM_OFF_PRE	0x00000040	/* No cache, precise */
#घोषणा ACR_CM_OFF_IMP	0x00000060	/* No cache, imprecise */
#घोषणा ACR_CM		0x00000060	/* Cache mode mask */
#घोषणा ACR_SP		0x00000008	/* Supervisor protect */
#घोषणा ACR_WPROTECT	0x00000004	/* Write protect */

#घोषणा ACR_BA(x)	((x) & 0xff000000)
#घोषणा ACR_ADMSK(x)	((((x) - 1) & 0xff000000) >> 8)

#अगर defined(CONFIG_M5407)

#घोषणा ICACHE_SIZE 0x4000	/* inकाष्ठाion - 16k */
#घोषणा DCACHE_SIZE 0x2000	/* data - 8k */

#या_अगर defined(CONFIG_M54xx)

#घोषणा ICACHE_SIZE 0x8000	/* inकाष्ठाion - 32k */
#घोषणा DCACHE_SIZE 0x8000	/* data - 32k */

#या_अगर defined(CONFIG_M5441x)

#घोषणा ICACHE_SIZE 0x2000	/* inकाष्ठाion - 8k */
#घोषणा DCACHE_SIZE 0x2000	/* data - 8k */
#पूर्ण_अगर

#घोषणा CACHE_LINE_SIZE 0x0010	/* 16 bytes */
#घोषणा CACHE_WAYS 4		/* 4 ways */

#घोषणा ICACHE_SET_MASK	((ICACHE_SIZE / 64 - 1) << CACHE_WAYS)
#घोषणा DCACHE_SET_MASK	((DCACHE_SIZE / 64 - 1) << CACHE_WAYS)
#घोषणा ICACHE_MAX_ADDR	ICACHE_SET_MASK
#घोषणा DCACHE_MAX_ADDR	DCACHE_SET_MASK

/*
 *	Version 4 cores have a true harvard style separate inकाष्ठाion
 *	and data cache. Enable data and inकाष्ठाion caches, also enable ग_लिखो
 *	buffers and branch accelerator.
 */
/* attention : enabling CACR_DESB requires a "nop" to flush the store buffer */
/* use '+' instead of '|' for assembler's sake */

	/* Enable data cache */
	/* Enable data store buffer */
	/* outside ACRs : No cache, precise */
	/* Enable inकाष्ठाion+branch caches */
#अगर defined(CONFIG_M5407)
#घोषणा CACHE_MODE (CACR_DEC+CACR_DESB+CACR_DDCM_P+CACR_BEC+CACR_IEC)
#अन्यथा
#घोषणा CACHE_MODE (CACR_DEC+CACR_DESB+CACR_DDCM_P+CACR_BEC+CACR_IEC+CACR_EUSP)
#पूर्ण_अगर
#घोषणा CACHE_INIT (CACR_DCINVA+CACR_BCINVA+CACR_ICINVA)

#अगर defined(CONFIG_MMU)
/*
 *	If running with the MMU enabled then we need to map the पूर्णांकernal
 *	रेजिस्टर region as non-cacheable. And then we map all our RAM as
 *	cacheable and supervisor access only.
 */
#घोषणा ACR0_MODE	(ACR_BA(IOMEMBASE)+ACR_ADMSK(IOMEMSIZE)+ \
			 ACR_ENABLE+ACR_SUPER+ACR_CM_OFF_PRE+ACR_SP)
#अगर defined(CONFIG_CACHE_COPYBACK)
#घोषणा ACR1_MODE	(ACR_BA(CONFIG_RAMBASE)+ACR_ADMSK(CONFIG_RAMSIZE)+ \
			 ACR_ENABLE+ACR_SUPER+ACR_SP+ACR_CM_CP)
#अन्यथा
#घोषणा ACR1_MODE	(ACR_BA(CONFIG_RAMBASE)+ACR_ADMSK(CONFIG_RAMSIZE)+ \
			 ACR_ENABLE+ACR_SUPER+ACR_SP+ACR_CM_WT)
#पूर्ण_अगर
#घोषणा ACR2_MODE	0
#घोषणा ACR3_MODE	(ACR_BA(CONFIG_RAMBASE)+ACR_ADMSK(CONFIG_RAMSIZE)+ \
			 ACR_ENABLE+ACR_SUPER+ACR_SP)

#अन्यथा

/*
 *	For the non-MMU enabled हाल we map all of RAM as cacheable.
 */
#अगर defined(CONFIG_CACHE_COPYBACK)
#घोषणा DATA_CACHE_MODE (ACR_ENABLE+ACR_ANY+ACR_CM_CP)
#अन्यथा
#घोषणा DATA_CACHE_MODE (ACR_ENABLE+ACR_ANY+ACR_CM_WT)
#पूर्ण_अगर
#घोषणा INSN_CACHE_MODE (ACR_ENABLE+ACR_ANY)

#घोषणा CACHE_INVALIDATE  (CACHE_MODE+CACR_DCINVA+CACR_BCINVA+CACR_ICINVA)
#घोषणा CACHE_INVALIDATEI (CACHE_MODE+CACR_BCINVA+CACR_ICINVA)
#घोषणा CACHE_INVALIDATED (CACHE_MODE+CACR_DCINVA)
#घोषणा ACR0_MODE	(0x000f0000+DATA_CACHE_MODE)
#घोषणा ACR1_MODE	0
#घोषणा ACR2_MODE	(0x000f0000+INSN_CACHE_MODE)
#घोषणा ACR3_MODE	0

#अगर ((DATA_CACHE_MODE & ACR_CM) == ACR_CM_CP)
/* Copyback cache mode must push dirty cache lines first */
#घोषणा	CACHE_PUSH
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर	/* m54xxacr_h */
