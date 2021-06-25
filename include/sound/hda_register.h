<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HD-audio controller (Azalia) रेजिस्टरs and helpers
 *
 * For traditional reasons, we still use azx_ prefix here
 */

#अगर_अघोषित __SOUND_HDA_REGISTER_H
#घोषणा __SOUND_HDA_REGISTER_H

#समावेश <linux/पन.स>
#समावेश <sound/hdaudपन.स>

#घोषणा AZX_REG_GCAP			0x00
#घोषणा   AZX_GCAP_64OK		(1 << 0)   /* 64bit address support */
#घोषणा   AZX_GCAP_NSDO		(3 << 1)   /* # of serial data out संकेतs */
#घोषणा   AZX_GCAP_BSS		(31 << 3)  /* # of bidirectional streams */
#घोषणा   AZX_GCAP_ISS		(15 << 8)  /* # of input streams */
#घोषणा   AZX_GCAP_OSS		(15 << 12) /* # of output streams */
#घोषणा AZX_REG_VMIN			0x02
#घोषणा AZX_REG_VMAJ			0x03
#घोषणा AZX_REG_OUTPAY			0x04
#घोषणा AZX_REG_INPAY			0x06
#घोषणा AZX_REG_GCTL			0x08
#घोषणा   AZX_GCTL_RESET	(1 << 0)   /* controller reset */
#घोषणा   AZX_GCTL_FCNTRL	(1 << 1)   /* flush control */
#घोषणा   AZX_GCTL_UNSOL	(1 << 8)   /* accept unsol. response enable */
#घोषणा AZX_REG_WAKEEN			0x0c
#घोषणा AZX_REG_STATESTS		0x0e
#घोषणा AZX_REG_GSTS			0x10
#घोषणा   AZX_GSTS_FSTS		(1 << 1)   /* flush status */
#घोषणा AZX_REG_GCAP2			0x12
#घोषणा AZX_REG_LLCH			0x14
#घोषणा AZX_REG_OUTSTRMPAY		0x18
#घोषणा AZX_REG_INSTRMPAY		0x1A
#घोषणा AZX_REG_INTCTL			0x20
#घोषणा AZX_REG_INTSTS			0x24
#घोषणा AZX_REG_WALLCLK			0x30	/* 24Mhz source */
#घोषणा AZX_REG_OLD_SSYNC		0x34	/* SSYNC क्रम old ICH */
#घोषणा AZX_REG_SSYNC			0x38
#घोषणा AZX_REG_CORBLBASE		0x40
#घोषणा AZX_REG_CORBUBASE		0x44
#घोषणा AZX_REG_CORBWP			0x48
#घोषणा AZX_REG_CORBRP			0x4a
#घोषणा   AZX_CORBRP_RST	(1 << 15)  /* पढ़ो poपूर्णांकer reset */
#घोषणा AZX_REG_CORBCTL			0x4c
#घोषणा   AZX_CORBCTL_RUN	(1 << 1)   /* enable DMA */
#घोषणा   AZX_CORBCTL_CMEIE	(1 << 0)   /* enable memory error irq */
#घोषणा AZX_REG_CORBSTS			0x4d
#घोषणा   AZX_CORBSTS_CMEI	(1 << 0)   /* memory error indication */
#घोषणा AZX_REG_CORBSIZE		0x4e

#घोषणा AZX_REG_RIRBLBASE		0x50
#घोषणा AZX_REG_RIRBUBASE		0x54
#घोषणा AZX_REG_RIRBWP			0x58
#घोषणा   AZX_RIRBWP_RST	(1 << 15)  /* ग_लिखो poपूर्णांकer reset */
#घोषणा AZX_REG_RINTCNT			0x5a
#घोषणा AZX_REG_RIRBCTL			0x5c
#घोषणा   AZX_RBCTL_IRQ_EN	(1 << 0)   /* enable IRQ */
#घोषणा   AZX_RBCTL_DMA_EN	(1 << 1)   /* enable DMA */
#घोषणा   AZX_RBCTL_OVERRUN_EN	(1 << 2)   /* enable overrun irq */
#घोषणा AZX_REG_RIRBSTS			0x5d
#घोषणा   AZX_RBSTS_IRQ		(1 << 0)   /* response irq */
#घोषणा   AZX_RBSTS_OVERRUN	(1 << 2)   /* overrun irq */
#घोषणा AZX_REG_RIRBSIZE		0x5e

#घोषणा AZX_REG_IC			0x60
#घोषणा AZX_REG_IR			0x64
#घोषणा AZX_REG_IRS			0x68
#घोषणा   AZX_IRS_VALID		(1<<1)
#घोषणा   AZX_IRS_BUSY		(1<<0)

#घोषणा AZX_REG_DPLBASE			0x70
#घोषणा AZX_REG_DPUBASE			0x74
#घोषणा   AZX_DPLBASE_ENABLE	0x1	/* Enable position buffer */

/* SD offset: SDI0=0x80, SDI1=0xa0, ... SDO3=0x160 */
क्रमागत अणु SDI0, SDI1, SDI2, SDI3, SDO0, SDO1, SDO2, SDO3 पूर्ण;

/* stream रेजिस्टर offsets from stream base */
#घोषणा AZX_REG_SD_CTL			0x00
#घोषणा AZX_REG_SD_CTL_3B		0x02 /* 3rd byte of SD_CTL रेजिस्टर */
#घोषणा AZX_REG_SD_STS			0x03
#घोषणा AZX_REG_SD_LPIB			0x04
#घोषणा AZX_REG_SD_CBL			0x08
#घोषणा AZX_REG_SD_LVI			0x0c
#घोषणा AZX_REG_SD_FIFOW		0x0e
#घोषणा AZX_REG_SD_FIFOSIZE		0x10
#घोषणा AZX_REG_SD_FORMAT		0x12
#घोषणा AZX_REG_SD_FIFOL		0x14
#घोषणा AZX_REG_SD_BDLPL		0x18
#घोषणा AZX_REG_SD_BDLPU		0x1c

/* GTS रेजिस्टरs */
#घोषणा AZX_REG_LLCH			0x14

#घोषणा AZX_REG_GTS_BASE		0x520

#घोषणा AZX_REG_GTSCC	(AZX_REG_GTS_BASE + 0x00)
#घोषणा AZX_REG_WALFCC	(AZX_REG_GTS_BASE + 0x04)
#घोषणा AZX_REG_TSCCL	(AZX_REG_GTS_BASE + 0x08)
#घोषणा AZX_REG_TSCCU	(AZX_REG_GTS_BASE + 0x0C)
#घोषणा AZX_REG_LLPFOC	(AZX_REG_GTS_BASE + 0x14)
#घोषणा AZX_REG_LLPCL	(AZX_REG_GTS_BASE + 0x18)
#घोषणा AZX_REG_LLPCU	(AZX_REG_GTS_BASE + 0x1C)

/* Haswell/Broadwell display HD-A controller Extended Mode रेजिस्टरs */
#घोषणा AZX_REG_HSW_EM4			0x100c
#घोषणा AZX_REG_HSW_EM5			0x1010

/* Skylake/Broxton venकरोr-specअगरic रेजिस्टरs */
#घोषणा AZX_REG_VS_EM1			0x1000
#घोषणा AZX_REG_VS_INRC			0x1004
#घोषणा AZX_REG_VS_OUTRC		0x1008
#घोषणा AZX_REG_VS_FIFOTRK		0x100C
#घोषणा AZX_REG_VS_FIFOTRK2		0x1010
#घोषणा AZX_REG_VS_EM2			0x1030
#घोषणा AZX_REG_VS_EM3L			0x1038
#घोषणा AZX_REG_VS_EM3U			0x103C
#घोषणा AZX_REG_VS_EM4L			0x1040
#घोषणा AZX_REG_VS_EM4U			0x1044
#घोषणा AZX_REG_VS_LTRP			0x1048
#घोषणा AZX_REG_VS_D0I3C		0x104A
#घोषणा AZX_REG_VS_PCE			0x104B
#घोषणा AZX_REG_VS_L2MAGC		0x1050
#घोषणा AZX_REG_VS_L2LAHPT		0x1054
#घोषणा AZX_REG_VS_SDXDPIB_XBASE	0x1084
#घोषणा AZX_REG_VS_SDXDPIB_XINTERVAL	0x20
#घोषणा AZX_REG_VS_SDXEFIFOS_XBASE	0x1094
#घोषणा AZX_REG_VS_SDXEFIFOS_XINTERVAL	0x20

/* PCI space */
#घोषणा AZX_PCIREG_TCSEL		0x44

/*
 * other स्थिरants
 */

/* max number of fragments - we may use more अगर allocating more pages क्रम BDL */
#घोषणा BDL_SIZE		4096
#घोषणा AZX_MAX_BDL_ENTRIES	(BDL_SIZE / 16)
#घोषणा AZX_MAX_FRAG		32
/*
 * max buffer size - artअगरicial 4MB limit per stream to aव्योम big allocations
 * In theory it can be really big, but as it is per stream on प्रणालीs with many streams memory could
 * be quickly saturated अगर userspace requests maximum buffer size क्रम each of them.
 */
#घोषणा AZX_MAX_BUF_SIZE	(4*1024*1024)

/* RIRB पूर्णांक mask: overrun[2], response[0] */
#घोषणा RIRB_INT_RESPONSE	0x01
#घोषणा RIRB_INT_OVERRUN	0x04
#घोषणा RIRB_INT_MASK		0x05

/* STATESTS पूर्णांक mask: S3,SD2,SD1,SD0 */
#घोषणा STATESTS_INT_MASK	((1 << HDA_MAX_CODECS) - 1)

/* SD_CTL bits */
#घोषणा SD_CTL_STREAM_RESET	0x01	/* stream reset bit */
#घोषणा SD_CTL_DMA_START	0x02	/* stream DMA start bit */
#घोषणा SD_CTL_STRIPE		(3 << 16)	/* stripe control */
#घोषणा SD_CTL_TRAFFIC_PRIO	(1 << 18)	/* traffic priority */
#घोषणा SD_CTL_सूची		(1 << 19)	/* bi-directional stream */
#घोषणा SD_CTL_STREAM_TAG_MASK	(0xf << 20)
#घोषणा SD_CTL_STREAM_TAG_SHIFT	20

/* SD_CTL and SD_STS */
#घोषणा SD_INT_DESC_ERR		0x10	/* descriptor error पूर्णांकerrupt */
#घोषणा SD_INT_FIFO_ERR		0x08	/* FIFO error पूर्णांकerrupt */
#घोषणा SD_INT_COMPLETE		0x04	/* completion पूर्णांकerrupt */
#घोषणा SD_INT_MASK		(SD_INT_DESC_ERR|SD_INT_FIFO_ERR|\
				 SD_INT_COMPLETE)
#घोषणा SD_CTL_STRIPE_MASK	0x3	/* stripe control mask */

/* SD_STS */
#घोषणा SD_STS_FIFO_READY	0x20	/* FIFO पढ़ोy */

/* INTCTL and INTSTS */
#घोषणा AZX_INT_ALL_STREAM	0xff	   /* all stream पूर्णांकerrupts */
#घोषणा AZX_INT_CTRL_EN	0x40000000 /* controller पूर्णांकerrupt enable bit */
#घोषणा AZX_INT_GLOBAL_EN	0x80000000 /* global पूर्णांकerrupt enable bit */

/* below are so far hardcoded - should पढ़ो रेजिस्टरs in future */
#घोषणा AZX_MAX_CORB_ENTRIES	256
#घोषणा AZX_MAX_RIRB_ENTRIES	256

/* Capability header  Structure */
#घोषणा AZX_REG_CAP_HDR			0x0
#घोषणा AZX_CAP_HDR_VER_OFF		28
#घोषणा AZX_CAP_HDR_VER_MASK		(0xF << AZX_CAP_HDR_VER_OFF)
#घोषणा AZX_CAP_HDR_ID_OFF		16
#घोषणा AZX_CAP_HDR_ID_MASK		(0xFFF << AZX_CAP_HDR_ID_OFF)
#घोषणा AZX_CAP_HDR_NXT_PTR_MASK	0xFFFF

/* रेजिस्टरs of Software Position Based FIFO Capability Structure */
#घोषणा AZX_SPB_CAP_ID			0x4
#घोषणा AZX_REG_SPB_BASE_ADDR		0x700
#घोषणा AZX_REG_SPB_SPBFCH		0x00
#घोषणा AZX_REG_SPB_SPBFCCTL		0x04
/* Base used to calculate the iterating रेजिस्टर offset */
#घोषणा AZX_SPB_BASE			0x08
/* Interval used to calculate the iterating रेजिस्टर offset */
#घोषणा AZX_SPB_INTERVAL		0x08
/* SPIB base */
#घोषणा AZX_SPB_SPIB			0x00
/* SPIB MAXFIFO base*/
#घोषणा AZX_SPB_MAXFIFO			0x04

/* रेजिस्टरs of Global Time Synchronization Capability Structure */
#घोषणा AZX_GTS_CAP_ID			0x1
#घोषणा AZX_REG_GTS_GTSCH		0x00
#घोषणा AZX_REG_GTS_GTSCD		0x04
#घोषणा AZX_REG_GTS_GTSCTLAC		0x0C
#घोषणा AZX_GTS_BASE			0x20
#घोषणा AZX_GTS_INTERVAL		0x20

/* रेजिस्टरs क्रम Processing Pipe Capability Structure */
#घोषणा AZX_PP_CAP_ID			0x3
#घोषणा AZX_REG_PP_PPCH			0x10
#घोषणा AZX_REG_PP_PPCTL		0x04
#घोषणा AZX_PPCTL_PIE			(1<<31)
#घोषणा AZX_PPCTL_GPROCEN		(1<<30)
/* _X_ = dma engine # and cannot * exceed 29 (per spec max 30 dma engines) */
#घोषणा AZX_PPCTL_PROCEN(_X_)		(1<<(_X_))

#घोषणा AZX_REG_PP_PPSTS		0x08

#घोषणा AZX_PPHC_BASE			0x10
#घोषणा AZX_PPHC_INTERVAL		0x10

#घोषणा AZX_REG_PPHCLLPL		0x0
#घोषणा AZX_REG_PPHCLLPU		0x4
#घोषणा AZX_REG_PPHCLDPL		0x8
#घोषणा AZX_REG_PPHCLDPU		0xC

#घोषणा AZX_PPLC_BASE			0x10
#घोषणा AZX_PPLC_MULTI			0x10
#घोषणा AZX_PPLC_INTERVAL		0x10

#घोषणा AZX_REG_PPLCCTL			0x0
#घोषणा AZX_PPLCCTL_STRM_BITS		4
#घोषणा AZX_PPLCCTL_STRM_SHIFT		20
#घोषणा AZX_REG_MASK(bit_num, offset) \
	(((1 << (bit_num)) - 1) << (offset))
#घोषणा AZX_PPLCCTL_STRM_MASK \
	AZX_REG_MASK(AZX_PPLCCTL_STRM_BITS, AZX_PPLCCTL_STRM_SHIFT)
#घोषणा AZX_PPLCCTL_RUN			(1<<1)
#घोषणा AZX_PPLCCTL_STRST		(1<<0)

#घोषणा AZX_REG_PPLCFMT			0x4
#घोषणा AZX_REG_PPLCLLPL		0x8
#घोषणा AZX_REG_PPLCLLPU		0xC

/* रेजिस्टरs क्रम Multiple Links Capability Structure */
#घोषणा AZX_ML_CAP_ID			0x2
#घोषणा AZX_REG_ML_MLCH			0x00
#घोषणा AZX_REG_ML_MLCD			0x04
#घोषणा AZX_ML_BASE			0x40
#घोषणा AZX_ML_INTERVAL			0x40

#घोषणा AZX_REG_ML_LCAP			0x00
#घोषणा AZX_REG_ML_LCTL			0x04
#घोषणा AZX_REG_ML_LOSIDV		0x08
#घोषणा AZX_REG_ML_LSDIID		0x0C
#घोषणा AZX_REG_ML_LPSOO		0x10
#घोषणा AZX_REG_ML_LPSIO		0x12
#घोषणा AZX_REG_ML_LWALFC		0x18
#घोषणा AZX_REG_ML_LOUTPAY		0x20
#घोषणा AZX_REG_ML_LINPAY		0x30

/* bit0 is reserved, with BIT(1) mapping to stream1 */
#घोषणा ML_LOSIDV_STREAM_MASK		0xFFFE

#घोषणा ML_LCTL_SCF_MASK			0xF
#घोषणा AZX_MLCTL_SPA				(0x1 << 16)
#घोषणा AZX_MLCTL_CPA				(0x1 << 23)
#घोषणा AZX_MLCTL_SPA_SHIFT			16
#घोषणा AZX_MLCTL_CPA_SHIFT			23

/* रेजिस्टरs क्रम DMA Resume Capability Structure */
#घोषणा AZX_DRSM_CAP_ID			0x5
#घोषणा AZX_REG_DRSM_CTL		0x4
/* Base used to calculate the iterating रेजिस्टर offset */
#घोषणा AZX_DRSM_BASE			0x08
/* Interval used to calculate the iterating रेजिस्टर offset */
#घोषणा AZX_DRSM_INTERVAL		0x08

/* Global समय synchronization रेजिस्टरs */
#घोषणा GTSCC_TSCCD_MASK		0x80000000
#घोषणा GTSCC_TSCCD_SHIFT		BIT(31)
#घोषणा GTSCC_TSCCI_MASK		0x20
#घोषणा GTSCC_CDMAS_DMA_सूची_SHIFT	4

#घोषणा WALFCC_CIF_MASK			0x1FF
#घोषणा WALFCC_FN_SHIFT			9
#घोषणा HDA_CLK_CYCLES_PER_FRAME	512

/*
 * An error occurs near frame "rollover". The घड़ीs in frame value indicates
 * whether this error may have occurred. Here we use the value of 10. Please
 * see the errata क्रम the right number [<10]
 */
#घोषणा HDA_MAX_CYCLE_VALUE		499
#घोषणा HDA_MAX_CYCLE_OFFSET		10
#घोषणा HDA_MAX_CYCLE_READ_RETRY	10

#घोषणा TSCCU_CCU_SHIFT			32
#घोषणा LLPC_CCU_SHIFT			32


/*
 * helpers to पढ़ो the stream position
 */
अटल अंतरभूत अचिन्हित पूर्णांक
snd_hdac_stream_get_pos_lpib(काष्ठा hdac_stream *stream)
अणु
	वापस snd_hdac_stream_पढ़ोl(stream, SD_LPIB);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
snd_hdac_stream_get_pos_posbuf(काष्ठा hdac_stream *stream)
अणु
	वापस le32_to_cpu(*stream->posbuf);
पूर्ण

#पूर्ण_अगर /* __SOUND_HDA_REGISTER_H */
