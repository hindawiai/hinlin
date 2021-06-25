<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM hardware रेजिस्टर-level view
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 * Copyright 2018 NXP
 */

#अगर_अघोषित REGS_H
#घोषणा REGS_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-hi-lo.h>

/*
 * Architecture-specअगरic रेजिस्टर access methods
 *
 * CAAM's bus-addressable रेजिस्टरs are 64 bits पूर्णांकernally.
 * They have been wired to be safely accessible on 32-bit
 * architectures, however. Registers were organized such
 * that (a) they can be contained in 32 bits, (b) अगर not, then they
 * can be treated as two 32-bit entities, or finally (c) अगर they
 * must be treated as a single 64-bit value, then this can safely
 * be करोne with two 32-bit cycles.
 *
 * For 32-bit operations on 64-bit values, CAAM follows the same
 * 64-bit रेजिस्टर access conventions as it's predecessors, in that
 * ग_लिखोs are "triggered" by a ग_लिखो to the रेजिस्टर at the numerically
 * higher address, thus, a full 64-bit ग_लिखो cycle requires a ग_लिखो
 * to the lower address, followed by a ग_लिखो to the higher address,
 * which will latch/execute the ग_लिखो cycle.
 *
 * For example, let's assume a SW reset of CAAM through the master
 * configuration रेजिस्टर.
 * - SWRST is in bit 31 of MCFG.
 * - MCFG begins at base+0x0000.
 * - Bits 63-32 are a 32-bit word at base+0x0000 (numerically-lower)
 * - Bits 31-0 are a 32-bit word at base+0x0004 (numerically-higher)
 *
 * (and on Power, the convention is 0-31, 32-63, I know...)
 *
 * Assuming a 64-bit ग_लिखो to this MCFG to perक्रमm a software reset
 * would then require a ग_लिखो of 0 to base+0x0000, followed by a
 * ग_लिखो of 0x80000000 to base+0x0004, which would "execute" the
 * reset.
 *
 * Of course, since MCFG 63-32 is all zero, we could cheat and simply
 * ग_लिखो 0x8000000 to base+0x0004, and the reset would work fine.
 * However, since CAAM करोes contain some ग_लिखो-and-पढ़ो-पूर्णांकended
 * 64-bit रेजिस्टरs, this code defines 64-bit access methods क्रम
 * the sake of पूर्णांकernal consistency and simplicity, and so that a
 * clean transition to 64-bit is possible when it becomes necessary.
 *
 * There are limitations to this that the developer must recognize.
 * 32-bit architectures cannot enक्रमce an atomic-64 operation,
 * Thereक्रमe:
 *
 * - On ग_लिखोs, since the HW is assumed to latch the cycle on the
 *   ग_लिखो of the higher-numeric-address word, then ordered
 *   ग_लिखोs work OK.
 *
 * - For पढ़ोs, where a रेजिस्टर contains a relevant value of more
 *   that 32 bits, the hardware employs logic to latch the other
 *   "half" of the data until पढ़ो, ensuring an accurate value.
 *   This is of particular relevance when dealing with CAAM's
 *   perक्रमmance counters.
 *
 */

बाह्य bool caam_little_end;
बाह्य bool caam_imx;
बाह्य माप_प्रकार caam_ptr_sz;

#घोषणा caam_to_cpu(len)						\
अटल अंतरभूत u##len caam##len ## _to_cpu(u##len val)			\
अणु									\
	अगर (caam_little_end)						\
		वापस le##len ## _to_cpu((__क्रमce __le##len)val);	\
	अन्यथा								\
		वापस be##len ## _to_cpu((__क्रमce __be##len)val);	\
पूर्ण

#घोषणा cpu_to_caam(len)					\
अटल अंतरभूत u##len cpu_to_caam##len(u##len val)		\
अणु								\
	अगर (caam_little_end)					\
		वापस (__क्रमce u##len)cpu_to_le##len(val);	\
	अन्यथा							\
		वापस (__क्रमce u##len)cpu_to_be##len(val);	\
पूर्ण

caam_to_cpu(16)
caam_to_cpu(32)
caam_to_cpu(64)
cpu_to_caam(16)
cpu_to_caam(32)
cpu_to_caam(64)

अटल अंतरभूत व्योम wr_reg32(व्योम __iomem *reg, u32 data)
अणु
	अगर (caam_little_end)
		ioग_लिखो32(data, reg);
	अन्यथा
		ioग_लिखो32be(data, reg);
पूर्ण

अटल अंतरभूत u32 rd_reg32(व्योम __iomem *reg)
अणु
	अगर (caam_little_end)
		वापस ioपढ़ो32(reg);

	वापस ioपढ़ो32be(reg);
पूर्ण

अटल अंतरभूत व्योम clrsetbits_32(व्योम __iomem *reg, u32 clear, u32 set)
अणु
	अगर (caam_little_end)
		ioग_लिखो32((ioपढ़ो32(reg) & ~clear) | set, reg);
	अन्यथा
		ioग_लिखो32be((ioपढ़ो32be(reg) & ~clear) | set, reg);
पूर्ण

/*
 * The only users of these wr/rd_reg64 functions is the Job Ring (JR).
 * The DMA address रेजिस्टरs in the JR are handled dअगरferently depending on
 * platक्रमm:
 *
 * 1. All BE CAAM platक्रमms and i.MX platक्रमms (LE CAAM):
 *
 *    base + 0x0000 : most-signअगरicant 32 bits
 *    base + 0x0004 : least-signअगरicant 32 bits
 *
 * The 32-bit version of this core thereक्रमe has to ग_लिखो to base + 0x0004
 * to set the 32-bit wide DMA address.
 *
 * 2. All other LE CAAM platक्रमms (LS1021A etc.)
 *    base + 0x0000 : least-signअगरicant 32 bits
 *    base + 0x0004 : most-signअगरicant 32 bits
 */
अटल अंतरभूत व्योम wr_reg64(व्योम __iomem *reg, u64 data)
अणु
	अगर (caam_little_end) अणु
		अगर (caam_imx) अणु
			ioग_लिखो32(data >> 32, (u32 __iomem *)(reg));
			ioग_लिखो32(data, (u32 __iomem *)(reg) + 1);
		पूर्ण अन्यथा अणु
			ioग_लिखो64(data, reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		ioग_लिखो64be(data, reg);
	पूर्ण
पूर्ण

अटल अंतरभूत u64 rd_reg64(व्योम __iomem *reg)
अणु
	अगर (caam_little_end) अणु
		अगर (caam_imx) अणु
			u32 low, high;

			high = ioपढ़ो32(reg);
			low  = ioपढ़ो32(reg + माप(u32));

			वापस low + ((u64)high << 32);
		पूर्ण अन्यथा अणु
			वापस ioपढ़ो64(reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस ioपढ़ो64be(reg);
	पूर्ण
पूर्ण

अटल अंतरभूत u64 cpu_to_caam_dma64(dma_addr_t value)
अणु
	अगर (caam_imx) अणु
		u64 ret_val = (u64)cpu_to_caam32(lower_32_bits(value)) << 32;

		अगर (IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT))
			ret_val |= (u64)cpu_to_caam32(upper_32_bits(value));

		वापस ret_val;
	पूर्ण

	वापस cpu_to_caam64(value);
पूर्ण

अटल अंतरभूत u64 caam_dma64_to_cpu(u64 value)
अणु
	अगर (caam_imx)
		वापस (((u64)caam32_to_cpu(lower_32_bits(value)) << 32) |
			 (u64)caam32_to_cpu(upper_32_bits(value)));

	वापस caam64_to_cpu(value);
पूर्ण

अटल अंतरभूत u64 cpu_to_caam_dma(u64 value)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT) &&
	    caam_ptr_sz == माप(u64))
		वापस cpu_to_caam_dma64(value);
	अन्यथा
		वापस cpu_to_caam32(value);
पूर्ण

अटल अंतरभूत u64 caam_dma_to_cpu(u64 value)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT) &&
	    caam_ptr_sz == माप(u64))
		वापस caam_dma64_to_cpu(value);
	अन्यथा
		वापस caam32_to_cpu(value);
पूर्ण

/*
 * jr_outentry
 * Represents each entry in a JobR output ring
 */

अटल अंतरभूत व्योम jr_outentry_get(व्योम *outring, पूर्णांक hw_idx, dma_addr_t *desc,
				   u32 *jrstatus)
अणु

	अगर (caam_ptr_sz == माप(u32)) अणु
		काष्ठा अणु
			u32 desc;
			u32 jrstatus;
		पूर्ण __packed *outentry = outring;

		*desc = outentry[hw_idx].desc;
		*jrstatus = outentry[hw_idx].jrstatus;
	पूर्ण अन्यथा अणु
		काष्ठा अणु
			dma_addr_t desc;/* Poपूर्णांकer to completed descriptor */
			u32 jrstatus;	/* Status क्रम completed descriptor */
		पूर्ण __packed *outentry = outring;

		*desc = outentry[hw_idx].desc;
		*jrstatus = outentry[hw_idx].jrstatus;
	पूर्ण
पूर्ण

#घोषणा SIZखातापूर्ण_JR_OUTENTRY	(caam_ptr_sz + माप(u32))

अटल अंतरभूत dma_addr_t jr_outentry_desc(व्योम *outring, पूर्णांक hw_idx)
अणु
	dma_addr_t desc;
	u32 unused;

	jr_outentry_get(outring, hw_idx, &desc, &unused);

	वापस desc;
पूर्ण

अटल अंतरभूत u32 jr_outentry_jrstatus(व्योम *outring, पूर्णांक hw_idx)
अणु
	dma_addr_t unused;
	u32 jrstatus;

	jr_outentry_get(outring, hw_idx, &unused, &jrstatus);

	वापस jrstatus;
पूर्ण

अटल अंतरभूत व्योम jr_inpentry_set(व्योम *inpring, पूर्णांक hw_idx, dma_addr_t val)
अणु
	अगर (caam_ptr_sz == माप(u32)) अणु
		u32 *inpentry = inpring;

		inpentry[hw_idx] = val;
	पूर्ण अन्यथा अणु
		dma_addr_t *inpentry = inpring;

		inpentry[hw_idx] = val;
	पूर्ण
पूर्ण

#घोषणा SIZखातापूर्ण_JR_INPENTRY	caam_ptr_sz


/* Version रेजिस्टरs (Era 10+)	e80-eff */
काष्ठा version_regs अणु
	u32 crca;	/* CRCA_VERSION */
	u32 afha;	/* AFHA_VERSION */
	u32 kfha;	/* KFHA_VERSION */
	u32 pkha;	/* PKHA_VERSION */
	u32 aesa;	/* AESA_VERSION */
	u32 mdha;	/* MDHA_VERSION */
	u32 desa;	/* DESA_VERSION */
	u32 snw8a;	/* SNW8A_VERSION */
	u32 snw9a;	/* SNW9A_VERSION */
	u32 zuce;	/* ZUCE_VERSION */
	u32 zuca;	/* ZUCA_VERSION */
	u32 ccha;	/* CCHA_VERSION */
	u32 ptha;	/* PTHA_VERSION */
	u32 rng;	/* RNG_VERSION */
	u32 trng;	/* TRNG_VERSION */
	u32 aaha;	/* AAHA_VERSION */
	u32 rsvd[10];
	u32 sr;		/* SR_VERSION */
	u32 dma;	/* DMA_VERSION */
	u32 ai;		/* AI_VERSION */
	u32 qi;		/* QI_VERSION */
	u32 jr;		/* JR_VERSION */
	u32 deco;	/* DECO_VERSION */
पूर्ण;

/* Version रेजिस्टरs bitfields */

/* Number of CHAs instantiated */
#घोषणा CHA_VER_NUM_MASK	0xffull
/* CHA Miscellaneous Inक्रमmation */
#घोषणा CHA_VER_MISC_SHIFT	8
#घोषणा CHA_VER_MISC_MASK	(0xffull << CHA_VER_MISC_SHIFT)
/* CHA Revision Number */
#घोषणा CHA_VER_REV_SHIFT	16
#घोषणा CHA_VER_REV_MASK	(0xffull << CHA_VER_REV_SHIFT)
/* CHA Version ID */
#घोषणा CHA_VER_VID_SHIFT	24
#घोषणा CHA_VER_VID_MASK	(0xffull << CHA_VER_VID_SHIFT)

/* CHA Miscellaneous Inक्रमmation - AESA_MISC specअगरic */
#घोषणा CHA_VER_MISC_AES_GCM	BIT(1 + CHA_VER_MISC_SHIFT)

/*
 * caam_perfmon - Perक्रमmance Monitor/Secure Memory Status/
 *                CAAM Global Status/Component Version IDs
 *
 * Spans f00-fff wherever instantiated
 */

/* Number of DECOs */
#घोषणा CHA_NUM_MS_DECONUM_SHIFT	24
#घोषणा CHA_NUM_MS_DECONUM_MASK	(0xfull << CHA_NUM_MS_DECONUM_SHIFT)

/*
 * CHA version IDs / instantiation bitfields (< Era 10)
 * Defined क्रम use with the cha_id fields in perfmon, but the same shअगरt/mask
 * selectors can be used to pull out the number of instantiated blocks within
 * cha_num fields in perfmon because the locations are the same.
 */
#घोषणा CHA_ID_LS_AES_SHIFT	0
#घोषणा CHA_ID_LS_AES_MASK	(0xfull << CHA_ID_LS_AES_SHIFT)

#घोषणा CHA_ID_LS_DES_SHIFT	4
#घोषणा CHA_ID_LS_DES_MASK	(0xfull << CHA_ID_LS_DES_SHIFT)

#घोषणा CHA_ID_LS_ARC4_SHIFT	8
#घोषणा CHA_ID_LS_ARC4_MASK	(0xfull << CHA_ID_LS_ARC4_SHIFT)

#घोषणा CHA_ID_LS_MD_SHIFT	12
#घोषणा CHA_ID_LS_MD_MASK	(0xfull << CHA_ID_LS_MD_SHIFT)

#घोषणा CHA_ID_LS_RNG_SHIFT	16
#घोषणा CHA_ID_LS_RNG_MASK	(0xfull << CHA_ID_LS_RNG_SHIFT)

#घोषणा CHA_ID_LS_SNW8_SHIFT	20
#घोषणा CHA_ID_LS_SNW8_MASK	(0xfull << CHA_ID_LS_SNW8_SHIFT)

#घोषणा CHA_ID_LS_KAS_SHIFT	24
#घोषणा CHA_ID_LS_KAS_MASK	(0xfull << CHA_ID_LS_KAS_SHIFT)

#घोषणा CHA_ID_LS_PK_SHIFT	28
#घोषणा CHA_ID_LS_PK_MASK	(0xfull << CHA_ID_LS_PK_SHIFT)

#घोषणा CHA_ID_MS_CRC_SHIFT	0
#घोषणा CHA_ID_MS_CRC_MASK	(0xfull << CHA_ID_MS_CRC_SHIFT)

#घोषणा CHA_ID_MS_SNW9_SHIFT	4
#घोषणा CHA_ID_MS_SNW9_MASK	(0xfull << CHA_ID_MS_SNW9_SHIFT)

#घोषणा CHA_ID_MS_DECO_SHIFT	24
#घोषणा CHA_ID_MS_DECO_MASK	(0xfull << CHA_ID_MS_DECO_SHIFT)

#घोषणा CHA_ID_MS_JR_SHIFT	28
#घोषणा CHA_ID_MS_JR_MASK	(0xfull << CHA_ID_MS_JR_SHIFT)

/* Specअगरic CHA version IDs */
#घोषणा CHA_VER_VID_AES_LP	0x3ull
#घोषणा CHA_VER_VID_AES_HP	0x4ull
#घोषणा CHA_VER_VID_MD_LP256	0x0ull
#घोषणा CHA_VER_VID_MD_LP512	0x1ull
#घोषणा CHA_VER_VID_MD_HP	0x2ull

काष्ठा sec_vid अणु
	u16 ip_id;
	u8 maj_rev;
	u8 min_rev;
पूर्ण;

काष्ठा caam_perfmon अणु
	/* Perक्रमmance Monitor Registers			f00-f9f */
	u64 req_dequeued;	/* PC_REQ_DEQ - Dequeued Requests	     */
	u64 ob_enc_req;	/* PC_OB_ENC_REQ - Outbound Encrypt Requests */
	u64 ib_dec_req;	/* PC_IB_DEC_REQ - Inbound Decrypt Requests  */
	u64 ob_enc_bytes;	/* PC_OB_ENCRYPT - Outbound Bytes Encrypted  */
	u64 ob_prot_bytes;	/* PC_OB_PROTECT - Outbound Bytes Protected  */
	u64 ib_dec_bytes;	/* PC_IB_DECRYPT - Inbound Bytes Decrypted   */
	u64 ib_valid_bytes;	/* PC_IB_VALIDATED Inbound Bytes Validated   */
	u64 rsvd[13];

	/* CAAM Hardware Instantiation Parameters		fa0-fbf */
	u32 cha_rev_ms;		/* CRNR - CHA Rev No. Most signअगरicant half*/
	u32 cha_rev_ls;		/* CRNR - CHA Rev No. Least signअगरicant half*/
#घोषणा CTPR_MS_QI_SHIFT	25
#घोषणा CTPR_MS_QI_MASK		(0x1ull << CTPR_MS_QI_SHIFT)
#घोषणा CTPR_MS_PS		BIT(17)
#घोषणा CTPR_MS_DPAA2		BIT(13)
#घोषणा CTPR_MS_VIRT_EN_INCL	0x00000001
#घोषणा CTPR_MS_VIRT_EN_POR	0x00000002
#घोषणा CTPR_MS_PG_SZ_MASK	0x10
#घोषणा CTPR_MS_PG_SZ_SHIFT	4
	u32 comp_parms_ms;	/* CTPR - Compile Parameters Register	*/
	u32 comp_parms_ls;	/* CTPR - Compile Parameters Register	*/
	u64 rsvd1[2];

	/* CAAM Global Status					fc0-fdf */
	u64 faultaddr;	/* FAR  - Fault Address		*/
	u32 faultliodn;	/* FALR - Fault Address LIODN	*/
	u32 faultdetail;	/* FADR - Fault Addr Detail	*/
	u32 rsvd2;
#घोषणा CSTA_PLEND		BIT(10)
#घोषणा CSTA_ALT_PLEND		BIT(18)
	u32 status;		/* CSTA - CAAM Status */
	u64 rsvd3;

	/* Component Instantiation Parameters			fe0-fff */
	u32 rtic_id;		/* RVID - RTIC Version ID	*/
#घोषणा CCBVID_ERA_MASK		0xff000000
#घोषणा CCBVID_ERA_SHIFT	24
	u32 ccb_id;		/* CCBVID - CCB Version ID	*/
	u32 cha_id_ms;		/* CHAVID - CHA Version ID Most Signअगरicant*/
	u32 cha_id_ls;		/* CHAVID - CHA Version ID Least Signअगरicant*/
	u32 cha_num_ms;		/* CHANUM - CHA Number Most Signअगरicant	*/
	u32 cha_num_ls;		/* CHANUM - CHA Number Least Signअगरicant*/
#घोषणा SECVID_MS_IPID_MASK	0xffff0000
#घोषणा SECVID_MS_IPID_SHIFT	16
#घोषणा SECVID_MS_MAJ_REV_MASK	0x0000ff00
#घोषणा SECVID_MS_MAJ_REV_SHIFT	8
	u32 caam_id_ms;		/* CAAMVID - CAAM Version ID MS	*/
	u32 caam_id_ls;		/* CAAMVID - CAAM Version ID LS	*/
पूर्ण;

/* LIODN programming क्रम DMA configuration */
#घोषणा MSTRID_LOCK_LIODN	0x80000000
#घोषणा MSTRID_LOCK_MAKETRUSTED	0x00010000	/* only क्रम JR masterid */

#घोषणा MSTRID_LIODN_MASK	0x0fff
काष्ठा masterid अणु
	u32 liodn_ms;	/* lock and make-trusted control bits */
	u32 liodn_ls;	/* LIODN क्रम non-sequence and seq access */
पूर्ण;

/* Partition ID क्रम DMA configuration */
काष्ठा partid अणु
	u32 rsvd1;
	u32 pidr;	/* partition ID, DECO */
पूर्ण;

/* RNGB test mode (replicated twice in some configurations) */
/* Padded out to 0x100 */
काष्ठा rngtst अणु
	u32 mode;		/* RTSTMODEx - Test mode */
	u32 rsvd1[3];
	u32 reset;		/* RTSTRESETx - Test reset control */
	u32 rsvd2[3];
	u32 status;		/* RTSTSSTATUSx - Test status */
	u32 rsvd3;
	u32 errstat;		/* RTSTERRSTATx - Test error status */
	u32 rsvd4;
	u32 errctl;		/* RTSTERRCTLx - Test error control */
	u32 rsvd5;
	u32 entropy;		/* RTSTENTROPYx - Test entropy */
	u32 rsvd6[15];
	u32 verअगरctl;	/* RTSTVERIFCTLx - Test verअगरication control */
	u32 rsvd7;
	u32 verअगरstat;	/* RTSTVERIFSTATx - Test verअगरication status */
	u32 rsvd8;
	u32 verअगरdata;	/* RTSTVERIFDx - Test verअगरication data */
	u32 rsvd9;
	u32 xkey;		/* RTSTXKEYx - Test XKEY */
	u32 rsvd10;
	u32 oscctctl;	/* RTSTOSCCTCTLx - Test osc. counter control */
	u32 rsvd11;
	u32 oscct;		/* RTSTOSCCTx - Test oscillator counter */
	u32 rsvd12;
	u32 oscctstat;	/* RTSTODCCTSTATx - Test osc counter status */
	u32 rsvd13[2];
	u32 ofअगरo[4];	/* RTSTOFIFOx - Test output FIFO */
	u32 rsvd14[15];
पूर्ण;

/* RNG4 TRNG test रेजिस्टरs */
काष्ठा rng4tst अणु
#घोषणा RTMCTL_ACC  BIT(5)  /* TRNG access mode */
#घोषणा RTMCTL_PRGM BIT(16) /* 1 -> program mode, 0 -> run mode */
#घोषणा RTMCTL_SAMP_MODE_VON_NEUMANN_ES_SC	0 /* use von Neumann data in
						     both entropy shअगरter and
						     statistical checker */
#घोषणा RTMCTL_SAMP_MODE_RAW_ES_SC		1 /* use raw data in both
						     entropy shअगरter and
						     statistical checker */
#घोषणा RTMCTL_SAMP_MODE_VON_NEUMANN_ES_RAW_SC	2 /* use von Neumann data in
						     entropy shअगरter, raw data
						     in statistical checker */
#घोषणा RTMCTL_SAMP_MODE_INVALID		3 /* invalid combination */
	u32 rपंचांगctl;		/* misc. control रेजिस्टर */
	u32 rtscmisc;		/* statistical check misc. रेजिस्टर */
	u32 rtpkrrng;		/* poker range रेजिस्टर */
	जोड़ अणु
		u32 rtpkrmax;	/* PRGM=1: poker max. limit रेजिस्टर */
		u32 rtpkrsq;	/* PRGM=0: poker square calc. result रेजिस्टर */
	पूर्ण;
#घोषणा RTSDCTL_ENT_DLY_SHIFT 16
#घोषणा RTSDCTL_ENT_DLY_MASK (0xffff << RTSDCTL_ENT_DLY_SHIFT)
#घोषणा RTSDCTL_ENT_DLY_MIN 3200
#घोषणा RTSDCTL_ENT_DLY_MAX 12800
	u32 rtsdctl;		/* seed control रेजिस्टर */
	जोड़ अणु
		u32 rtsblim;	/* PRGM=1: sparse bit limit रेजिस्टर */
		u32 rttotsam;	/* PRGM=0: total samples रेजिस्टर */
	पूर्ण;
	u32 rtfrqmin;		/* frequency count min. limit रेजिस्टर */
#घोषणा RTFRQMAX_DISABLE	(1 << 20)
	जोड़ अणु
		u32 rtfrqmax;	/* PRGM=1: freq. count max. limit रेजिस्टर */
		u32 rtfrqcnt;	/* PRGM=0: freq. count रेजिस्टर */
	पूर्ण;
	u32 rsvd1[40];
#घोषणा RDSTA_SKVT 0x80000000
#घोषणा RDSTA_SKVN 0x40000000
#घोषणा RDSTA_PR0 BIT(4)
#घोषणा RDSTA_PR1 BIT(5)
#घोषणा RDSTA_IF0 0x00000001
#घोषणा RDSTA_IF1 0x00000002
#घोषणा RDSTA_MASK (RDSTA_PR1 | RDSTA_PR0 | RDSTA_IF1 | RDSTA_IF0)
	u32 rdsta;
	u32 rsvd2[15];
पूर्ण;

/*
 * caam_ctrl - basic core configuration
 * starts base + 0x0000 padded out to 0x1000
 */

#घोषणा KEK_KEY_SIZE		8
#घोषणा TKEK_KEY_SIZE		8
#घोषणा TDSK_KEY_SIZE		8

#घोषणा DECO_RESET	1	/* Use with DECO reset/availability regs */
#घोषणा DECO_RESET_0	(DECO_RESET << 0)
#घोषणा DECO_RESET_1	(DECO_RESET << 1)
#घोषणा DECO_RESET_2	(DECO_RESET << 2)
#घोषणा DECO_RESET_3	(DECO_RESET << 3)
#घोषणा DECO_RESET_4	(DECO_RESET << 4)

काष्ठा caam_ctrl अणु
	/* Basic Configuration Section				000-01f */
	/* Read/Writable					        */
	u32 rsvd1;
	u32 mcr;		/* MCFG      Master Config Register  */
	u32 rsvd2;
	u32 scfgr;		/* SCFGR, Security Config Register */

	/* Bus Access Configuration Section			010-11f */
	/* Read/Writable                                                */
	काष्ठा masterid jr_mid[4];	/* JRxLIODNR - JobR LIODN setup */
	u32 rsvd3[11];
	u32 jrstart;			/* JRSTART - Job Ring Start Register */
	काष्ठा masterid rtic_mid[4];	/* RTICxLIODNR - RTIC LIODN setup */
	u32 rsvd4[5];
	u32 deco_rsr;			/* DECORSR - Deco Request Source */
	u32 rsvd11;
	u32 deco_rq;			/* DECORR - DECO Request */
	काष्ठा partid deco_mid[5];	/* DECOxLIODNR - 1 per DECO */
	u32 rsvd5[22];

	/* DECO Availability/Reset Section			120-3ff */
	u32 deco_avail;		/* DAR - DECO availability */
	u32 deco_reset;		/* DRR - DECO reset */
	u32 rsvd6[182];

	/* Key Encryption/Decryption Configuration              400-5ff */
	/* Read/Writable only जबतक in Non-secure mode                  */
	u32 kek[KEK_KEY_SIZE];	/* JDKEKR - Key Encryption Key */
	u32 tkek[TKEK_KEY_SIZE];	/* TDKEKR - Trusted Desc KEK */
	u32 tdsk[TDSK_KEY_SIZE];	/* TDSKR - Trusted Desc Signing Key */
	u32 rsvd7[32];
	u64 sknonce;			/* SKNR - Secure Key Nonce */
	u32 rsvd8[70];

	/* RNG Test/Verअगरication/Debug Access                   600-7ff */
	/* (Useful in Test/Debug modes only...)                         */
	जोड़ अणु
		काष्ठा rngtst rtst[2];
		काष्ठा rng4tst r4tst[2];
	पूर्ण;

	u32 rsvd9[416];

	/* Version रेजिस्टरs - पूर्णांकroduced with era 10		e80-eff */
	काष्ठा version_regs vreg;
	/* Perक्रमmance Monitor                                  f00-fff */
	काष्ठा caam_perfmon perfmon;
पूर्ण;

/*
 * Controller master config रेजिस्टर defs
 */
#घोषणा MCFGR_SWRESET		0x80000000 /* software reset */
#घोषणा MCFGR_WDENABLE		0x40000000 /* DECO watchकरोg enable */
#घोषणा MCFGR_WDFAIL		0x20000000 /* DECO watchकरोg क्रमce-fail */
#घोषणा MCFGR_DMA_RESET		0x10000000
#घोषणा MCFGR_LONG_PTR		0x00010000 /* Use >32-bit desc addressing */
#घोषणा SCFGR_RDBENABLE		0x00000400
#घोषणा SCFGR_VIRT_EN		0x00008000
#घोषणा DECORR_RQD0ENABLE	0x00000001 /* Enable DECO0 क्रम direct access */
#घोषणा DECORSR_JR0		0x00000001 /* JR to supply TZ, SDID, ICID */
#घोषणा DECORSR_VALID		0x80000000
#घोषणा DECORR_DEN0		0x00010000 /* DECO0 available क्रम access*/

/* AXI पढ़ो cache control */
#घोषणा MCFGR_ARCACHE_SHIFT	12
#घोषणा MCFGR_ARCACHE_MASK	(0xf << MCFGR_ARCACHE_SHIFT)
#घोषणा MCFGR_ARCACHE_BUFF	(0x1 << MCFGR_ARCACHE_SHIFT)
#घोषणा MCFGR_ARCACHE_CACH	(0x2 << MCFGR_ARCACHE_SHIFT)
#घोषणा MCFGR_ARCACHE_RALL	(0x4 << MCFGR_ARCACHE_SHIFT)

/* AXI ग_लिखो cache control */
#घोषणा MCFGR_AWCACHE_SHIFT	8
#घोषणा MCFGR_AWCACHE_MASK	(0xf << MCFGR_AWCACHE_SHIFT)
#घोषणा MCFGR_AWCACHE_BUFF	(0x1 << MCFGR_AWCACHE_SHIFT)
#घोषणा MCFGR_AWCACHE_CACH	(0x2 << MCFGR_AWCACHE_SHIFT)
#घोषणा MCFGR_AWCACHE_WALL	(0x8 << MCFGR_AWCACHE_SHIFT)

/* AXI pipeline depth */
#घोषणा MCFGR_AXIPIPE_SHIFT	4
#घोषणा MCFGR_AXIPIPE_MASK	(0xf << MCFGR_AXIPIPE_SHIFT)

#घोषणा MCFGR_AXIPRI		0x00000008 /* Assert AXI priority sideband */
#घोषणा MCFGR_LARGE_BURST	0x00000004 /* 128/256-byte burst size */
#घोषणा MCFGR_BURST_64		0x00000001 /* 64-byte burst size */

/* JRSTART रेजिस्टर offsets */
#घोषणा JRSTART_JR0_START       0x00000001 /* Start Job ring 0 */
#घोषणा JRSTART_JR1_START       0x00000002 /* Start Job ring 1 */
#घोषणा JRSTART_JR2_START       0x00000004 /* Start Job ring 2 */
#घोषणा JRSTART_JR3_START       0x00000008 /* Start Job ring 3 */

/*
 * caam_job_ring - direct job ring setup
 * 1-4 possible per instantiation, base + 1000/2000/3000/4000
 * Padded out to 0x1000
 */
काष्ठा caam_job_ring अणु
	/* Input ring */
	u64 inpring_base;	/* IRBAx -  Input desc ring baseaddr */
	u32 rsvd1;
	u32 inpring_size;	/* IRSx - Input ring size */
	u32 rsvd2;
	u32 inpring_avail;	/* IRSAx - Input ring room reमुख्यing */
	u32 rsvd3;
	u32 inpring_jobadd;	/* IRJAx - Input ring jobs added */

	/* Output Ring */
	u64 outring_base;	/* ORBAx - Output status ring base addr */
	u32 rsvd4;
	u32 outring_size;	/* ORSx - Output ring size */
	u32 rsvd5;
	u32 outring_rmvd;	/* ORJRx - Output ring jobs हटाओd */
	u32 rsvd6;
	u32 outring_used;	/* ORSFx - Output ring slots full */

	/* Status/Configuration */
	u32 rsvd7;
	u32 jroutstatus;	/* JRSTAx - JobR output status */
	u32 rsvd8;
	u32 jrपूर्णांकstatus;	/* JRINTx - JobR पूर्णांकerrupt status */
	u32 rconfig_hi;	/* JRxCFG - Ring configuration */
	u32 rconfig_lo;

	/* Indices. CAAM मुख्यtains as "heads" of each queue */
	u32 rsvd9;
	u32 inp_rdidx;	/* IRRIx - Input ring पढ़ो index */
	u32 rsvd10;
	u32 out_wtidx;	/* ORWIx - Output ring ग_लिखो index */

	/* Command/control */
	u32 rsvd11;
	u32 jrcommand;	/* JRCRx - JobR command */

	u32 rsvd12[900];

	/* Version रेजिस्टरs - पूर्णांकroduced with era 10           e80-eff */
	काष्ठा version_regs vreg;
	/* Perक्रमmance Monitor                                  f00-fff */
	काष्ठा caam_perfmon perfmon;
पूर्ण;

#घोषणा JR_RINGSIZE_MASK	0x03ff
/*
 * jrstatus - Job Ring Output Status
 * All values in lo word
 * Also note, same values written out as status through QI
 * in the command/status field of a frame descriptor
 */
#घोषणा JRSTA_SSRC_SHIFT            28
#घोषणा JRSTA_SSRC_MASK             0xf0000000

#घोषणा JRSTA_SSRC_NONE             0x00000000
#घोषणा JRSTA_SSRC_CCB_ERROR        0x20000000
#घोषणा JRSTA_SSRC_JUMP_HALT_USER   0x30000000
#घोषणा JRSTA_SSRC_DECO             0x40000000
#घोषणा JRSTA_SSRC_QI               0x50000000
#घोषणा JRSTA_SSRC_JRERROR          0x60000000
#घोषणा JRSTA_SSRC_JUMP_HALT_CC     0x70000000

#घोषणा JRSTA_DECOERR_JUMP          0x08000000
#घोषणा JRSTA_DECOERR_INDEX_SHIFT   8
#घोषणा JRSTA_DECOERR_INDEX_MASK    0xff00
#घोषणा JRSTA_DECOERR_ERROR_MASK    0x00ff

#घोषणा JRSTA_DECOERR_NONE          0x00
#घोषणा JRSTA_DECOERR_LINKLEN       0x01
#घोषणा JRSTA_DECOERR_LINKPTR       0x02
#घोषणा JRSTA_DECOERR_JRCTRL        0x03
#घोषणा JRSTA_DECOERR_DESCCMD       0x04
#घोषणा JRSTA_DECOERR_ORDER         0x05
#घोषणा JRSTA_DECOERR_KEYCMD        0x06
#घोषणा JRSTA_DECOERR_LOADCMD       0x07
#घोषणा JRSTA_DECOERR_STORECMD      0x08
#घोषणा JRSTA_DECOERR_OPCMD         0x09
#घोषणा JRSTA_DECOERR_FIFOLDCMD     0x0a
#घोषणा JRSTA_DECOERR_FIFOSTCMD     0x0b
#घोषणा JRSTA_DECOERR_MOVECMD       0x0c
#घोषणा JRSTA_DECOERR_JUMPCMD       0x0d
#घोषणा JRSTA_DECOERR_MATHCMD       0x0e
#घोषणा JRSTA_DECOERR_SHASHCMD      0x0f
#घोषणा JRSTA_DECOERR_SEQCMD        0x10
#घोषणा JRSTA_DECOERR_DECOINTERNAL  0x11
#घोषणा JRSTA_DECOERR_SHDESCHDR     0x12
#घोषणा JRSTA_DECOERR_HDRLEN        0x13
#घोषणा JRSTA_DECOERR_BURSTER       0x14
#घोषणा JRSTA_DECOERR_DESCSIGNATURE 0x15
#घोषणा JRSTA_DECOERR_DMA           0x16
#घोषणा JRSTA_DECOERR_BURSTFIFO     0x17
#घोषणा JRSTA_DECOERR_JRRESET       0x1a
#घोषणा JRSTA_DECOERR_JOBFAIL       0x1b
#घोषणा JRSTA_DECOERR_DNRERR        0x80
#घोषणा JRSTA_DECOERR_UNDEFPCL      0x81
#घोषणा JRSTA_DECOERR_PDBERR        0x82
#घोषणा JRSTA_DECOERR_ANRPLY_LATE   0x83
#घोषणा JRSTA_DECOERR_ANRPLY_REPLAY 0x84
#घोषणा JRSTA_DECOERR_SEQOVF        0x85
#घोषणा JRSTA_DECOERR_INVSIGN       0x86
#घोषणा JRSTA_DECOERR_DSASIGN       0x87

#घोषणा JRSTA_QIERR_ERROR_MASK      0x00ff

#घोषणा JRSTA_CCBERR_JUMP           0x08000000
#घोषणा JRSTA_CCBERR_INDEX_MASK     0xff00
#घोषणा JRSTA_CCBERR_INDEX_SHIFT    8
#घोषणा JRSTA_CCBERR_CHAID_MASK     0x00f0
#घोषणा JRSTA_CCBERR_CHAID_SHIFT    4
#घोषणा JRSTA_CCBERR_ERRID_MASK     0x000f

#घोषणा JRSTA_CCBERR_CHAID_AES      (0x01 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_DES      (0x02 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_ARC4     (0x03 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_MD       (0x04 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_RNG      (0x05 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_SNOW     (0x06 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_KASUMI   (0x07 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_PK       (0x08 << JRSTA_CCBERR_CHAID_SHIFT)
#घोषणा JRSTA_CCBERR_CHAID_CRC      (0x09 << JRSTA_CCBERR_CHAID_SHIFT)

#घोषणा JRSTA_CCBERR_ERRID_NONE     0x00
#घोषणा JRSTA_CCBERR_ERRID_MODE     0x01
#घोषणा JRSTA_CCBERR_ERRID_DATASIZ  0x02
#घोषणा JRSTA_CCBERR_ERRID_KEYSIZ   0x03
#घोषणा JRSTA_CCBERR_ERRID_PKAMEMSZ 0x04
#घोषणा JRSTA_CCBERR_ERRID_PKBMEMSZ 0x05
#घोषणा JRSTA_CCBERR_ERRID_SEQUENCE 0x06
#घोषणा JRSTA_CCBERR_ERRID_PKDIVZRO 0x07
#घोषणा JRSTA_CCBERR_ERRID_PKMODEVN 0x08
#घोषणा JRSTA_CCBERR_ERRID_KEYPARIT 0x09
#घोषणा JRSTA_CCBERR_ERRID_ICVCHK   0x0a
#घोषणा JRSTA_CCBERR_ERRID_HARDWARE 0x0b
#घोषणा JRSTA_CCBERR_ERRID_CCMAAD   0x0c
#घोषणा JRSTA_CCBERR_ERRID_INVCHA   0x0f

#घोषणा JRINT_ERR_INDEX_MASK        0x3fff0000
#घोषणा JRINT_ERR_INDEX_SHIFT       16
#घोषणा JRINT_ERR_TYPE_MASK         0xf00
#घोषणा JRINT_ERR_TYPE_SHIFT        8
#घोषणा JRINT_ERR_HALT_MASK         0xc
#घोषणा JRINT_ERR_HALT_SHIFT        2
#घोषणा JRINT_ERR_HALT_INPROGRESS   0x4
#घोषणा JRINT_ERR_HALT_COMPLETE     0x8
#घोषणा JRINT_JR_ERROR              0x02
#घोषणा JRINT_JR_INT                0x01

#घोषणा JRINT_ERR_TYPE_WRITE        1
#घोषणा JRINT_ERR_TYPE_BAD_INPADDR  3
#घोषणा JRINT_ERR_TYPE_BAD_OUTADDR  4
#घोषणा JRINT_ERR_TYPE_INV_INPWRT   5
#घोषणा JRINT_ERR_TYPE_INV_OUTWRT   6
#घोषणा JRINT_ERR_TYPE_RESET        7
#घोषणा JRINT_ERR_TYPE_REMOVE_OFL   8
#घोषणा JRINT_ERR_TYPE_ADD_OFL      9

#घोषणा JRCFG_SOE		0x04
#घोषणा JRCFG_ICEN		0x02
#घोषणा JRCFG_IMSK		0x01
#घोषणा JRCFG_ICDCT_SHIFT	8
#घोषणा JRCFG_ICTT_SHIFT	16

#घोषणा JRCR_RESET                  0x01

/*
 * caam_assurance - Assurance Controller View
 * base + 0x6000 padded out to 0x1000
 */

काष्ठा rtic_element अणु
	u64 address;
	u32 rsvd;
	u32 length;
पूर्ण;

काष्ठा rtic_block अणु
	काष्ठा rtic_element element[2];
पूर्ण;

काष्ठा rtic_memhash अणु
	u32 memhash_be[32];
	u32 memhash_le[32];
पूर्ण;

काष्ठा caam_assurance अणु
    /* Status/Command/Watchकरोg */
	u32 rsvd1;
	u32 status;		/* RSTA - Status */
	u32 rsvd2;
	u32 cmd;		/* RCMD - Command */
	u32 rsvd3;
	u32 ctrl;		/* RCTL - Control */
	u32 rsvd4;
	u32 throttle;	/* RTHR - Throttle */
	u32 rsvd5[2];
	u64 watchकरोg;	/* RWDOG - Watchकरोg Timer */
	u32 rsvd6;
	u32 rend;		/* REND - Endian corrections */
	u32 rsvd7[50];

	/* Block access/configuration @ 100/110/120/130 */
	काष्ठा rtic_block memblk[4];	/* Memory Blocks A-D */
	u32 rsvd8[32];

	/* Block hashes @ 200/300/400/500 */
	काष्ठा rtic_memhash hash[4];	/* Block hash values A-D */
	u32 rsvd_3[640];
पूर्ण;

/*
 * caam_queue_अगर - QI configuration and control
 * starts base + 0x7000, padded out to 0x1000 दीर्घ
 */

काष्ठा caam_queue_अगर अणु
	u32 qi_control_hi;	/* QICTL  - QI Control */
	u32 qi_control_lo;
	u32 rsvd1;
	u32 qi_status;	/* QISTA  - QI Status */
	u32 qi_deq_cfg_hi;	/* QIDQC  - QI Dequeue Configuration */
	u32 qi_deq_cfg_lo;
	u32 qi_enq_cfg_hi;	/* QISEQC - QI Enqueue Command     */
	u32 qi_enq_cfg_lo;
	u32 rsvd2[1016];
पूर्ण;

/* QI control bits - low word */
#घोषणा QICTL_DQEN      0x01              /* Enable frame pop          */
#घोषणा QICTL_STOP      0x02              /* Stop dequeue/enqueue      */
#घोषणा QICTL_SOE       0x04              /* Stop on error             */

/* QI control bits - high word */
#घोषणा QICTL_MBSI	0x01
#घोषणा QICTL_MHWSI	0x02
#घोषणा QICTL_MWSI	0x04
#घोषणा QICTL_MDWSI	0x08
#घोषणा QICTL_CBSI	0x10		/* CtrlDataByteSwapInput     */
#घोषणा QICTL_CHWSI	0x20		/* CtrlDataHalfSwapInput     */
#घोषणा QICTL_CWSI	0x40		/* CtrlDataWordSwapInput     */
#घोषणा QICTL_CDWSI	0x80		/* CtrlDataDWordSwapInput    */
#घोषणा QICTL_MBSO	0x0100
#घोषणा QICTL_MHWSO	0x0200
#घोषणा QICTL_MWSO	0x0400
#घोषणा QICTL_MDWSO	0x0800
#घोषणा QICTL_CBSO	0x1000		/* CtrlDataByteSwapOutput    */
#घोषणा QICTL_CHWSO	0x2000		/* CtrlDataHalfSwapOutput    */
#घोषणा QICTL_CWSO	0x4000		/* CtrlDataWordSwapOutput    */
#घोषणा QICTL_CDWSO     0x8000		/* CtrlDataDWordSwapOutput   */
#घोषणा QICTL_DMBS	0x010000
#घोषणा QICTL_EPO	0x020000

/* QI status bits */
#घोषणा QISTA_PHRDERR   0x01              /* PreHeader Read Error      */
#घोषणा QISTA_CFRDERR   0x02              /* Compound Frame Read Error */
#घोषणा QISTA_OFWRERR   0x04              /* Output Frame Read Error   */
#घोषणा QISTA_BPDERR    0x08              /* Buffer Pool Depleted      */
#घोषणा QISTA_BTSERR    0x10              /* Buffer Undersize          */
#घोषणा QISTA_CFWRERR   0x20              /* Compound Frame Write Err  */
#घोषणा QISTA_STOPD     0x80000000        /* QI Stopped (see QICTL)    */

/* deco_sg_table - DECO view of scatter/gather table */
काष्ठा deco_sg_table अणु
	u64 addr;		/* Segment Address */
	u32 elen;		/* E, F bits + 30-bit length */
	u32 bpid_offset;	/* Buffer Pool ID + 16-bit length */
पूर्ण;

/*
 * caam_deco - descriptor controller - CHA cluster block
 *
 * Only accessible when direct DECO access is turned on
 * (करोne in DECORR, via MID programmed in DECOxMID
 *
 * 5 typical, base + 0x8000/9000/a000/b000
 * Padded out to 0x1000 दीर्घ
 */
काष्ठा caam_deco अणु
	u32 rsvd1;
	u32 cls1_mode;	/* CxC1MR -  Class 1 Mode */
	u32 rsvd2;
	u32 cls1_keysize;	/* CxC1KSR - Class 1 Key Size */
	u32 cls1_datasize_hi;	/* CxC1DSR - Class 1 Data Size */
	u32 cls1_datasize_lo;
	u32 rsvd3;
	u32 cls1_icvsize;	/* CxC1ICVSR - Class 1 ICV size */
	u32 rsvd4[5];
	u32 cha_ctrl;	/* CCTLR - CHA control */
	u32 rsvd5;
	u32 irq_crtl;	/* CxCIRQ - CCB पूर्णांकerrupt करोne/error/clear */
	u32 rsvd6;
	u32 clr_written;	/* CxCWR - Clear-Written */
	u32 ccb_status_hi;	/* CxCSTA - CCB Status/Error */
	u32 ccb_status_lo;
	u32 rsvd7[3];
	u32 aad_size;	/* CxAADSZR - Current AAD Size */
	u32 rsvd8;
	u32 cls1_iv_size;	/* CxC1IVSZR - Current Class 1 IV Size */
	u32 rsvd9[7];
	u32 pkha_a_size;	/* PKASZRx - Size of PKHA A */
	u32 rsvd10;
	u32 pkha_b_size;	/* PKBSZRx - Size of PKHA B */
	u32 rsvd11;
	u32 pkha_n_size;	/* PKNSZRx - Size of PKHA N */
	u32 rsvd12;
	u32 pkha_e_size;	/* PKESZRx - Size of PKHA E */
	u32 rsvd13[24];
	u32 cls1_ctx[16];	/* CxC1CTXR - Class 1 Context @100 */
	u32 rsvd14[48];
	u32 cls1_key[8];	/* CxC1KEYR - Class 1 Key @200 */
	u32 rsvd15[121];
	u32 cls2_mode;	/* CxC2MR - Class 2 Mode */
	u32 rsvd16;
	u32 cls2_keysize;	/* CxX2KSR - Class 2 Key Size */
	u32 cls2_datasize_hi;	/* CxC2DSR - Class 2 Data Size */
	u32 cls2_datasize_lo;
	u32 rsvd17;
	u32 cls2_icvsize;	/* CxC2ICVSZR - Class 2 ICV Size */
	u32 rsvd18[56];
	u32 cls2_ctx[18];	/* CxC2CTXR - Class 2 Context @500 */
	u32 rsvd19[46];
	u32 cls2_key[32];	/* CxC2KEYR - Class2 Key @600 */
	u32 rsvd20[84];
	u32 inp_infofअगरo_hi;	/* CxIFIFO - Input Info FIFO @7d0 */
	u32 inp_infofअगरo_lo;
	u32 rsvd21[2];
	u64 inp_datafअगरo;	/* CxDFIFO - Input Data FIFO */
	u32 rsvd22[2];
	u64 out_datafअगरo;	/* CxOFIFO - Output Data FIFO */
	u32 rsvd23[2];
	u32 jr_ctl_hi;	/* CxJRR - JobR Control Register      @800 */
	u32 jr_ctl_lo;
	u64 jr_descaddr;	/* CxDADR - JobR Descriptor Address */
#घोषणा DECO_OP_STATUS_HI_ERR_MASK 0xF00000FF
	u32 op_status_hi;	/* DxOPSTA - DECO Operation Status */
	u32 op_status_lo;
	u32 rsvd24[2];
	u32 liodn;		/* DxLSR - DECO LIODN Status - non-seq */
	u32 td_liodn;	/* DxLSR - DECO LIODN Status - trustdesc */
	u32 rsvd26[6];
	u64 math[4];		/* DxMTH - Math रेजिस्टर */
	u32 rsvd27[8];
	काष्ठा deco_sg_table gthr_tbl[4];	/* DxGTR - Gather Tables */
	u32 rsvd28[16];
	काष्ठा deco_sg_table sctr_tbl[4];	/* DxSTR - Scatter Tables */
	u32 rsvd29[48];
	u32 descbuf[64];	/* DxDESB - Descriptor buffer */
	u32 rscvd30[193];
#घोषणा DESC_DBG_DECO_STAT_VALID	0x80000000
#घोषणा DESC_DBG_DECO_STAT_MASK		0x00F00000
#घोषणा DESC_DBG_DECO_STAT_SHIFT	20
	u32 desc_dbg;		/* DxDDR - DECO Debug Register */
	u32 rsvd31[13];
#घोषणा DESC_DER_DECO_STAT_MASK		0x000F0000
#घोषणा DESC_DER_DECO_STAT_SHIFT	16
	u32 dbg_exec;		/* DxDER - DECO Debug Exec Register */
	u32 rsvd32[112];
पूर्ण;

#घोषणा DECO_STAT_HOST_ERR	0xD

#घोषणा DECO_JQCR_WHL		0x20000000
#घोषणा DECO_JQCR_FOUR		0x10000000

#घोषणा JR_BLOCK_NUMBER		1
#घोषणा ASSURE_BLOCK_NUMBER	6
#घोषणा QI_BLOCK_NUMBER		7
#घोषणा DECO_BLOCK_NUMBER	8
#घोषणा PG_SIZE_4K		0x1000
#घोषणा PG_SIZE_64K		0x10000
#पूर्ण_अगर /* REGS_H */
