<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Freescale SEC (talitos) device रेजिस्टर and descriptor header defines
 *
 * Copyright (c) 2006-2011 Freescale Semiconductor, Inc.
 */

#घोषणा TALITOS_TIMEOUT 100000
#घोषणा TALITOS1_MAX_DATA_LEN 32768
#घोषणा TALITOS2_MAX_DATA_LEN 65535

#घोषणा DESC_TYPE(desc_hdr) ((be32_to_cpu(desc_hdr) >> 3) & 0x1f)
#घोषणा PRIMARY_EU(desc_hdr) ((be32_to_cpu(desc_hdr) >> 28) & 0xf)
#घोषणा SECONDARY_EU(desc_hdr) ((be32_to_cpu(desc_hdr) >> 16) & 0xf)

/* descriptor poपूर्णांकer entry */
काष्ठा talitos_ptr अणु
	जोड़ अणु
		काष्ठा अणु		/* SEC2 क्रमmat */
			__be16 len;     /* length */
			u8 j_extent;    /* jump to sg link table and/or extent*/
			u8 eptr;        /* extended address */
		पूर्ण;
		काष्ठा अणु			/* SEC1 क्रमmat */
			__be16 res;
			__be16 len1;	/* length */
		पूर्ण;
	पूर्ण;
	__be32 ptr;     /* address */
पूर्ण;

/* descriptor */
काष्ठा talitos_desc अणु
	__be32 hdr;                     /* header high bits */
	जोड़ अणु
		__be32 hdr_lo;		/* header low bits */
		__be32 hdr1;		/* header क्रम SEC1 */
	पूर्ण;
	काष्ठा talitos_ptr ptr[7];      /* ptr/len pair array */
	__be32 next_desc;		/* next descriptor (SEC1) */
पूर्ण;

#घोषणा TALITOS_DESC_SIZE	(माप(काष्ठा talitos_desc) - माप(__be32))

/*
 * talitos_edesc - s/w-extended descriptor
 * @src_nents: number of segments in input scatterlist
 * @dst_nents: number of segments in output scatterlist
 * @iv_dma: dma address of iv क्रम checking continuity and link table
 * @dma_len: length of dma mapped link_tbl space
 * @dma_link_tbl: bus physical address of link_tbl/buf
 * @desc: h/w descriptor
 * @link_tbl: input and output h/w link tables (अगर अणुsrc,dstपूर्ण_nents > 1) (SEC2)
 * @buf: input and output buffeur (अगर अणुsrc,dstपूर्ण_nents > 1) (SEC1)
 *
 * अगर decrypting (with authcheck), or either one of src_nents or dst_nents
 * is greater than 1, an पूर्णांकegrity check value is concatenated to the end
 * of link_tbl data
 */
काष्ठा talitos_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	dma_addr_t iv_dma;
	पूर्णांक dma_len;
	dma_addr_t dma_link_tbl;
	काष्ठा talitos_desc desc;
	जोड़ अणु
		काष्ठा talitos_ptr link_tbl[0];
		u8 buf[0];
	पूर्ण;
पूर्ण;

/**
 * talitos_request - descriptor submission request
 * @desc: descriptor poपूर्णांकer (kernel भव)
 * @dma_desc: descriptor's physical bus address
 * @callback: whom to call when descriptor processing is करोne
 * @context: caller context (optional)
 */
काष्ठा talitos_request अणु
	काष्ठा talitos_desc *desc;
	dma_addr_t dma_desc;
	व्योम (*callback) (काष्ठा device *dev, काष्ठा talitos_desc *desc,
			  व्योम *context, पूर्णांक error);
	व्योम *context;
पूर्ण;

/* per-channel fअगरo management */
काष्ठा talitos_channel अणु
	व्योम __iomem *reg;

	/* request fअगरo */
	काष्ठा talitos_request *fअगरo;

	/* number of requests pending in channel h/w fअगरo */
	atomic_t submit_count ____cacheline_aligned;

	/* request submission (head) lock */
	spinlock_t head_lock ____cacheline_aligned;
	/* index to next मुक्त descriptor request */
	पूर्णांक head;

	/* request release (tail) lock */
	spinlock_t tail_lock ____cacheline_aligned;
	/* index to next in-progress/करोne descriptor request */
	पूर्णांक tail;
पूर्ण;

काष्ठा talitos_निजी अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *ofdev;
	व्योम __iomem *reg;
	व्योम __iomem *reg_deu;
	व्योम __iomem *reg_aesu;
	व्योम __iomem *reg_mdeu;
	व्योम __iomem *reg_afeu;
	व्योम __iomem *reg_rngu;
	व्योम __iomem *reg_pkeu;
	व्योम __iomem *reg_keu;
	व्योम __iomem *reg_crcu;
	पूर्णांक irq[2];

	/* SEC global रेजिस्टरs lock  */
	spinlock_t reg_lock ____cacheline_aligned;

	/* SEC version geometry (from device tree node) */
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक chfअगरo_len;
	अचिन्हित पूर्णांक exec_units;
	अचिन्हित पूर्णांक desc_types;

	/* SEC Compatibility info */
	अचिन्हित दीर्घ features;

	/*
	 * length of the request fअगरo
	 * fअगरo_len is chfअगरo_len rounded up to next घातer of 2
	 * so we can use bitwise ops to wrap
	 */
	अचिन्हित पूर्णांक fअगरo_len;

	काष्ठा talitos_channel *chan;

	/* next channel to be asचिन्हित next incoming descriptor */
	atomic_t last_chan ____cacheline_aligned;

	/* request callback tasklet */
	काष्ठा tasklet_काष्ठा करोne_task[2];

	/* list of रेजिस्टरed algorithms */
	काष्ठा list_head alg_list;

	/* hwrng device */
	काष्ठा hwrng rng;
	bool rng_रेजिस्टरed;
पूर्ण;

/* .features flag */
#घोषणा TALITOS_FTR_SRC_LINK_TBL_LEN_INCLUDES_EXTENT 0x00000001
#घोषणा TALITOS_FTR_HW_AUTH_CHECK 0x00000002
#घोषणा TALITOS_FTR_SHA224_HWINIT 0x00000004
#घोषणा TALITOS_FTR_HMAC_OK 0x00000008
#घोषणा TALITOS_FTR_SEC1 0x00000010

/*
 * If both CONFIG_CRYPTO_DEV_TALITOS1 and CONFIG_CRYPTO_DEV_TALITOS2 are
 * defined, we check the features which are set according to the device tree.
 * Otherwise, we answer true or false directly
 */
अटल अंतरभूत bool has_ftr_sec1(काष्ठा talitos_निजी *priv)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS1) &&
	    IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS2))
		वापस priv->features & TALITOS_FTR_SEC1;

	वापस IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS1);
पूर्ण

/*
 * TALITOS_xxx_LO addresses poपूर्णांक to the low data bits (32-63) of the रेजिस्टर
 */

#घोषणा ISR1_FORMAT(x)			(((x) << 28) | ((x) << 16))
#घोषणा ISR2_FORMAT(x)			(((x) << 4) | (x))

/* global रेजिस्टर offset addresses */
#घोषणा TALITOS_MCR			0x1030  /* master control रेजिस्टर */
#घोषणा   TALITOS_MCR_RCA0		(1 << 15) /* remap channel 0 */
#घोषणा   TALITOS_MCR_RCA1		(1 << 14) /* remap channel 1 */
#घोषणा   TALITOS_MCR_RCA2		(1 << 13) /* remap channel 2 */
#घोषणा   TALITOS_MCR_RCA3		(1 << 12) /* remap channel 3 */
#घोषणा   TALITOS1_MCR_SWR		0x1000000     /* s/w reset */
#घोषणा   TALITOS2_MCR_SWR		0x1     /* s/w reset */
#घोषणा TALITOS_MCR_LO			0x1034
#घोषणा TALITOS_IMR			0x1008  /* पूर्णांकerrupt mask रेजिस्टर */
/* enable channel IRQs */
#घोषणा   TALITOS1_IMR_INIT		ISR1_FORMAT(0xf)
#घोषणा   TALITOS1_IMR_DONE		ISR1_FORMAT(0x5) /* करोne IRQs */
/* enable channel IRQs */
#घोषणा   TALITOS2_IMR_INIT		(ISR2_FORMAT(0xf) | 0x10000)
#घोषणा   TALITOS2_IMR_DONE		ISR1_FORMAT(0x5) /* करोne IRQs */
#घोषणा TALITOS_IMR_LO			0x100C
#घोषणा   TALITOS1_IMR_LO_INIT		0x2000000 /* allow RNGU error IRQs */
#घोषणा   TALITOS2_IMR_LO_INIT		0x20000 /* allow RNGU error IRQs */
#घोषणा TALITOS_ISR			0x1010  /* पूर्णांकerrupt status रेजिस्टर */
#घोषणा   TALITOS1_ISR_4CHERR		ISR1_FORMAT(0xa) /* 4 ch errors mask */
#घोषणा   TALITOS1_ISR_4CHDONE		ISR1_FORMAT(0x5) /* 4 ch करोne mask */
#घोषणा   TALITOS1_ISR_CH_0_ERR		(2 << 28) /* ch 0 errors mask */
#घोषणा   TALITOS1_ISR_CH_0_DONE	(1 << 28) /* ch 0 करोne mask */
#घोषणा   TALITOS1_ISR_TEA_ERR		0x00000040
#घोषणा   TALITOS2_ISR_4CHERR		ISR2_FORMAT(0xa) /* 4 ch errors mask */
#घोषणा   TALITOS2_ISR_4CHDONE		ISR2_FORMAT(0x5) /* 4 ch करोne mask */
#घोषणा   TALITOS2_ISR_CH_0_ERR		2 /* ch 0 errors mask */
#घोषणा   TALITOS2_ISR_CH_0_DONE	1 /* ch 0 करोne mask */
#घोषणा   TALITOS2_ISR_CH_0_2_ERR	ISR2_FORMAT(0x2) /* ch 0, 2 err mask */
#घोषणा   TALITOS2_ISR_CH_0_2_DONE	ISR2_FORMAT(0x1) /* ch 0, 2 करोne mask */
#घोषणा   TALITOS2_ISR_CH_1_3_ERR	ISR2_FORMAT(0x8) /* ch 1, 3 err mask */
#घोषणा   TALITOS2_ISR_CH_1_3_DONE	ISR2_FORMAT(0x4) /* ch 1, 3 करोne mask */
#घोषणा TALITOS_ISR_LO			0x1014
#घोषणा TALITOS_ICR			0x1018  /* पूर्णांकerrupt clear रेजिस्टर */
#घोषणा TALITOS_ICR_LO			0x101C

/* channel रेजिस्टर address stride */
#घोषणा TALITOS_CH_BASE_OFFSET		0x1000	/* शेष channel map base */
#घोषणा TALITOS1_CH_STRIDE		0x1000
#घोषणा TALITOS2_CH_STRIDE		0x100

/* channel configuration रेजिस्टर  */
#घोषणा TALITOS_CCCR			0x8
#घोषणा   TALITOS2_CCCR_CONT		0x2    /* channel जारी on SEC2 */
#घोषणा   TALITOS2_CCCR_RESET		0x1    /* channel reset on SEC2 */
#घोषणा TALITOS_CCCR_LO			0xc
#घोषणा   TALITOS_CCCR_LO_IWSE		0x80   /* chan. ICCR ग_लिखोback enab. */
#घोषणा   TALITOS_CCCR_LO_EAE		0x20   /* extended address enable */
#घोषणा   TALITOS_CCCR_LO_CDWE		0x10   /* chan. करोne ग_लिखोback enab. */
#घोषणा   TALITOS_CCCR_LO_NE		0x8    /* fetch next descriptor enab. */
#घोषणा   TALITOS_CCCR_LO_NT		0x4    /* notअगरication type */
#घोषणा   TALITOS_CCCR_LO_CDIE		0x2    /* channel करोne IRQ enable */
#घोषणा   TALITOS1_CCCR_LO_RESET	0x1    /* channel reset on SEC1 */

/* CCPSR: channel poपूर्णांकer status रेजिस्टर */
#घोषणा TALITOS_CCPSR			0x10
#घोषणा TALITOS_CCPSR_LO		0x14
#घोषणा   TALITOS_CCPSR_LO_DOF		0x8000 /* द्विगुन FF ग_लिखो oflow error */
#घोषणा   TALITOS_CCPSR_LO_SOF		0x4000 /* single FF ग_लिखो oflow error */
#घोषणा   TALITOS_CCPSR_LO_MDTE		0x2000 /* master data transfer error */
#घोषणा   TALITOS_CCPSR_LO_SGDLZ	0x1000 /* s/g data len zero error */
#घोषणा   TALITOS_CCPSR_LO_FPZ		0x0800 /* fetch ptr zero error */
#घोषणा   TALITOS_CCPSR_LO_IDH		0x0400 /* illegal desc hdr error */
#घोषणा   TALITOS_CCPSR_LO_IEU		0x0200 /* invalid EU error */
#घोषणा   TALITOS_CCPSR_LO_EU		0x0100 /* EU error detected */
#घोषणा   TALITOS_CCPSR_LO_GB		0x0080 /* gather boundary error */
#घोषणा   TALITOS_CCPSR_LO_GRL		0x0040 /* gather वापस/length error */
#घोषणा   TALITOS_CCPSR_LO_SB		0x0020 /* scatter boundary error */
#घोषणा   TALITOS_CCPSR_LO_SRL		0x0010 /* scatter वापस/length error */

/* channel fetch fअगरo रेजिस्टर */
#घोषणा TALITOS_FF			0x48
#घोषणा TALITOS_FF_LO			0x4c

/* current descriptor poपूर्णांकer रेजिस्टर */
#घोषणा TALITOS_CDPR			0x40
#घोषणा TALITOS_CDPR_LO			0x44

/* descriptor buffer रेजिस्टर */
#घोषणा TALITOS_DESCBUF			0x80
#घोषणा TALITOS_DESCBUF_LO		0x84

/* gather link table */
#घोषणा TALITOS_GATHER			0xc0
#घोषणा TALITOS_GATHER_LO		0xc4

/* scatter link table */
#घोषणा TALITOS_SCATTER			0xe0
#घोषणा TALITOS_SCATTER_LO		0xe4

/* execution unit रेजिस्टरs base */
#घोषणा TALITOS2_DEU			0x2000
#घोषणा TALITOS2_AESU			0x4000
#घोषणा TALITOS2_MDEU			0x6000
#घोषणा TALITOS2_AFEU			0x8000
#घोषणा TALITOS2_RNGU			0xa000
#घोषणा TALITOS2_PKEU			0xc000
#घोषणा TALITOS2_KEU			0xe000
#घोषणा TALITOS2_CRCU			0xf000

#घोषणा TALITOS12_AESU			0x4000
#घोषणा TALITOS12_DEU			0x5000
#घोषणा TALITOS12_MDEU			0x6000

#घोषणा TALITOS10_AFEU			0x8000
#घोषणा TALITOS10_DEU			0xa000
#घोषणा TALITOS10_MDEU			0xc000
#घोषणा TALITOS10_RNGU			0xe000
#घोषणा TALITOS10_PKEU			0x10000
#घोषणा TALITOS10_AESU			0x12000

/* execution unit पूर्णांकerrupt status रेजिस्टरs */
#घोषणा TALITOS_EUDSR			0x10	/* data size */
#घोषणा TALITOS_EUDSR_LO		0x14
#घोषणा TALITOS_EURCR			0x18 /* reset control*/
#घोषणा TALITOS_EURCR_LO		0x1c
#घोषणा TALITOS_EUSR			0x28 /* rng status */
#घोषणा TALITOS_EUSR_LO			0x2c
#घोषणा TALITOS_EUISR			0x30
#घोषणा TALITOS_EUISR_LO		0x34
#घोषणा TALITOS_EUICR			0x38 /* पूर्णांक. control */
#घोषणा TALITOS_EUICR_LO		0x3c
#घोषणा TALITOS_EU_FIFO			0x800 /* output FIFO */
#घोषणा TALITOS_EU_FIFO_LO		0x804 /* output FIFO */
/* DES unit */
#घोषणा   TALITOS1_DEUICR_KPE		0x00200000 /* Key Parity Error */
/* message digest unit */
#घोषणा   TALITOS_MDEUICR_LO_ICE	0x4000 /* पूर्णांकegrity check IRQ enable */
/* अक्रमom number unit */
#घोषणा   TALITOS_RNGUSR_LO_RD		0x1	/* reset करोne */
#घोषणा   TALITOS_RNGUSR_LO_OFL		0xff0000/* output FIFO length */
#घोषणा   TALITOS_RNGURCR_LO_SR		0x1	/* software reset */

#घोषणा TALITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256	0x28
#घोषणा TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512		0x48

/*
 * talitos descriptor header (hdr) bits
 */

/* written back when करोne */
#घोषणा DESC_HDR_DONE			cpu_to_be32(0xff000000)
#घोषणा DESC_HDR_LO_ICCR1_MASK		cpu_to_be32(0x00180000)
#घोषणा DESC_HDR_LO_ICCR1_PASS		cpu_to_be32(0x00080000)
#घोषणा DESC_HDR_LO_ICCR1_FAIL		cpu_to_be32(0x00100000)

/* primary execution unit select */
#घोषणा	DESC_HDR_SEL0_MASK		cpu_to_be32(0xf0000000)
#घोषणा	DESC_HDR_SEL0_AFEU		cpu_to_be32(0x10000000)
#घोषणा	DESC_HDR_SEL0_DEU		cpu_to_be32(0x20000000)
#घोषणा	DESC_HDR_SEL0_MDEUA		cpu_to_be32(0x30000000)
#घोषणा	DESC_HDR_SEL0_MDEUB		cpu_to_be32(0xb0000000)
#घोषणा	DESC_HDR_SEL0_RNG		cpu_to_be32(0x40000000)
#घोषणा	DESC_HDR_SEL0_PKEU		cpu_to_be32(0x50000000)
#घोषणा	DESC_HDR_SEL0_AESU		cpu_to_be32(0x60000000)
#घोषणा	DESC_HDR_SEL0_KEU		cpu_to_be32(0x70000000)
#घोषणा	DESC_HDR_SEL0_CRCU		cpu_to_be32(0x80000000)

/* primary execution unit mode (MODE0) and derivatives */
#घोषणा	DESC_HDR_MODE0_ENCRYPT		cpu_to_be32(0x00100000)
#घोषणा	DESC_HDR_MODE0_AESU_MASK	cpu_to_be32(0x00600000)
#घोषणा	DESC_HDR_MODE0_AESU_CBC		cpu_to_be32(0x00200000)
#घोषणा	DESC_HDR_MODE0_AESU_CTR		cpu_to_be32(0x00600000)
#घोषणा	DESC_HDR_MODE0_DEU_CBC		cpu_to_be32(0x00400000)
#घोषणा	DESC_HDR_MODE0_DEU_3DES		cpu_to_be32(0x00200000)
#घोषणा	DESC_HDR_MODE0_MDEU_CONT	cpu_to_be32(0x08000000)
#घोषणा	DESC_HDR_MODE0_MDEU_INIT	cpu_to_be32(0x01000000)
#घोषणा	DESC_HDR_MODE0_MDEU_HMAC	cpu_to_be32(0x00800000)
#घोषणा	DESC_HDR_MODE0_MDEU_PAD		cpu_to_be32(0x00400000)
#घोषणा	DESC_HDR_MODE0_MDEU_SHA224	cpu_to_be32(0x00300000)
#घोषणा	DESC_HDR_MODE0_MDEU_MD5		cpu_to_be32(0x00200000)
#घोषणा	DESC_HDR_MODE0_MDEU_SHA256	cpu_to_be32(0x00100000)
#घोषणा	DESC_HDR_MODE0_MDEU_SHA1	cpu_to_be32(0x00000000)
#घोषणा	DESC_HDR_MODE0_MDEUB_SHA384	cpu_to_be32(0x00000000)
#घोषणा	DESC_HDR_MODE0_MDEUB_SHA512	cpu_to_be32(0x00200000)
#घोषणा	DESC_HDR_MODE0_MDEU_MD5_HMAC	(DESC_HDR_MODE0_MDEU_MD5 | \
					 DESC_HDR_MODE0_MDEU_HMAC)
#घोषणा	DESC_HDR_MODE0_MDEU_SHA256_HMAC	(DESC_HDR_MODE0_MDEU_SHA256 | \
					 DESC_HDR_MODE0_MDEU_HMAC)
#घोषणा	DESC_HDR_MODE0_MDEU_SHA1_HMAC	(DESC_HDR_MODE0_MDEU_SHA1 | \
					 DESC_HDR_MODE0_MDEU_HMAC)

/* secondary execution unit select (SEL1) */
#घोषणा	DESC_HDR_SEL1_MASK		cpu_to_be32(0x000f0000)
#घोषणा	DESC_HDR_SEL1_MDEUA		cpu_to_be32(0x00030000)
#घोषणा	DESC_HDR_SEL1_MDEUB		cpu_to_be32(0x000b0000)
#घोषणा	DESC_HDR_SEL1_CRCU		cpu_to_be32(0x00080000)

/* secondary execution unit mode (MODE1) and derivatives */
#घोषणा	DESC_HDR_MODE1_MDEU_CICV	cpu_to_be32(0x00004000)
#घोषणा	DESC_HDR_MODE1_MDEU_INIT	cpu_to_be32(0x00001000)
#घोषणा	DESC_HDR_MODE1_MDEU_HMAC	cpu_to_be32(0x00000800)
#घोषणा	DESC_HDR_MODE1_MDEU_PAD		cpu_to_be32(0x00000400)
#घोषणा	DESC_HDR_MODE1_MDEU_SHA224	cpu_to_be32(0x00000300)
#घोषणा	DESC_HDR_MODE1_MDEU_MD5		cpu_to_be32(0x00000200)
#घोषणा	DESC_HDR_MODE1_MDEU_SHA256	cpu_to_be32(0x00000100)
#घोषणा	DESC_HDR_MODE1_MDEU_SHA1	cpu_to_be32(0x00000000)
#घोषणा	DESC_HDR_MODE1_MDEUB_SHA384	cpu_to_be32(0x00000000)
#घोषणा	DESC_HDR_MODE1_MDEUB_SHA512	cpu_to_be32(0x00000200)
#घोषणा	DESC_HDR_MODE1_MDEU_MD5_HMAC	(DESC_HDR_MODE1_MDEU_MD5 | \
					 DESC_HDR_MODE1_MDEU_HMAC)
#घोषणा	DESC_HDR_MODE1_MDEU_SHA256_HMAC	(DESC_HDR_MODE1_MDEU_SHA256 | \
					 DESC_HDR_MODE1_MDEU_HMAC)
#घोषणा	DESC_HDR_MODE1_MDEU_SHA1_HMAC	(DESC_HDR_MODE1_MDEU_SHA1 | \
					 DESC_HDR_MODE1_MDEU_HMAC)
#घोषणा DESC_HDR_MODE1_MDEU_SHA224_HMAC	(DESC_HDR_MODE1_MDEU_SHA224 | \
					 DESC_HDR_MODE1_MDEU_HMAC)
#घोषणा DESC_HDR_MODE1_MDEUB_SHA384_HMAC	(DESC_HDR_MODE1_MDEUB_SHA384 | \
						 DESC_HDR_MODE1_MDEU_HMAC)
#घोषणा DESC_HDR_MODE1_MDEUB_SHA512_HMAC	(DESC_HDR_MODE1_MDEUB_SHA512 | \
						 DESC_HDR_MODE1_MDEU_HMAC)

/* direction of overall data flow (सूची) */
#घोषणा	DESC_HDR_सूची_INBOUND		cpu_to_be32(0x00000002)

/* request करोne notअगरication (DN) */
#घोषणा	DESC_HDR_DONE_NOTIFY		cpu_to_be32(0x00000001)

/* descriptor types */
#घोषणा DESC_HDR_TYPE_AESU_CTR_NONSNOOP		cpu_to_be32(0 << 3)
#घोषणा DESC_HDR_TYPE_IPSEC_ESP			cpu_to_be32(1 << 3)
#घोषणा DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU	cpu_to_be32(2 << 3)
#घोषणा DESC_HDR_TYPE_HMAC_SNOOP_NO_AFEU	cpu_to_be32(4 << 3)

/* link table extent field bits */
#घोषणा DESC_PTR_LNKTBL_JUMP			0x80
#घोषणा DESC_PTR_LNKTBL_RET			0x02
#घोषणा DESC_PTR_LNKTBL_NEXT			0x01
