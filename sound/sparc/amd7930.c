<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम AMD7930 sound chips found on Sparcs.
 * Copyright (C) 2002, 2008 David S. Miller <davem@davemloft.net>
 *
 * Based entirely upon drivers/sbus/audio/amd7930.c which is:
 * Copyright (C) 1996,1997 Thomas K. Dyas (tdyas@eden.rutgers.edu)
 *
 * --- Notes from Thomas's original driver ---
 * This is the lowlevel driver क्रम the AMD7930 audio chip found on all
 * sun4c machines and some sun4m machines.
 *
 * The amd7930 is actually an ISDN chip which has a very simple
 * पूर्णांकegrated audio encoder/decoder. When Sun decided on what chip to
 * use क्रम audio, they had the brilliant idea of using the amd7930 and
 * only connecting the audio encoder/decoder pins.
 *
 * Thanks to the AMD engineer who was able to get us the AMD79C30
 * databook which has all the programming inक्रमmation and gain tables.
 *
 * Advanced Micro Devices' Am79C30A is an ISDN/audio chip used in the
 * SparcStation 1+.  The chip provides microphone and speaker पूर्णांकerfaces
 * which provide mono-channel audio at 8K samples per second via either
 * 8-bit A-law or 8-bit mu-law encoding.  Also, the chip features an
 * ISDN BRI Line Interface Unit (LIU), I.430 S/T physical पूर्णांकerface,
 * which perक्रमms basic D channel LAPD processing and provides raw
 * B channel data.  The digital audio channel, the two ISDN B channels,
 * and two 64 Kbps channels to the microprocessor are all पूर्णांकerconnected
 * via a multiplexer.
 * --- End of notes from Thoamas's original driver ---
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Sun AMD7930 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Sun AMD7930 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Sun AMD7930 soundcard.");
MODULE_AUTHOR("Thomas K. Dyas and David S. Miller");
MODULE_DESCRIPTION("Sun AMD7930");
MODULE_LICENSE("GPL");

/* Device रेजिस्टर layout.  */

/* Register पूर्णांकerface presented to the CPU by the amd7930. */
#घोषणा AMD7930_CR	0x00UL		/* Command Register (W) */
#घोषणा AMD7930_IR	AMD7930_CR	/* Interrupt Register (R) */
#घोषणा AMD7930_DR	0x01UL		/* Data Register (R/W) */
#घोषणा AMD7930_DSR1	0x02UL		/* D-channel Status Register 1 (R) */
#घोषणा AMD7930_DER	0x03UL		/* D-channel Error Register (R) */
#घोषणा AMD7930_DCTB	0x04UL		/* D-channel Transmit Buffer (W) */
#घोषणा AMD7930_DCRB	AMD7930_DCTB	/* D-channel Receive Buffer (R) */
#घोषणा AMD7930_BBTB	0x05UL		/* Bb-channel Transmit Buffer (W) */
#घोषणा AMD7930_BBRB	AMD7930_BBTB	/* Bb-channel Receive Buffer (R) */
#घोषणा AMD7930_BCTB	0x06UL		/* Bc-channel Transmit Buffer (W) */
#घोषणा AMD7930_BCRB	AMD7930_BCTB	/* Bc-channel Receive Buffer (R) */
#घोषणा AMD7930_DSR2	0x07UL		/* D-channel Status Register 2 (R) */

/* Indirect रेजिस्टरs in the Main Audio Processor. */
काष्ठा amd7930_map अणु
	__u16	x[8];
	__u16	r[8];
	__u16	gx;
	__u16	gr;
	__u16	ger;
	__u16	stgr;
	__u16	ftgr;
	__u16	atgr;
	__u8	mmr1;
	__u8	mmr2;
पूर्ण;

/* After an amd7930 पूर्णांकerrupt, पढ़ोing the Interrupt Register (ir)
 * clears the पूर्णांकerrupt and वापसs a biपंचांगask indicating which
 * पूर्णांकerrupt source(s) require service.
 */

#घोषणा AMR_IR_DTTHRSH			0x01 /* D-channel xmit threshold */
#घोषणा AMR_IR_DRTHRSH			0x02 /* D-channel recv threshold */
#घोषणा AMR_IR_DSRI			0x04 /* D-channel packet status */
#घोषणा AMR_IR_DERI			0x08 /* D-channel error */
#घोषणा AMR_IR_BBUF			0x10 /* B-channel data xfer */
#घोषणा AMR_IR_LSRI			0x20 /* LIU status */
#घोषणा AMR_IR_DSR2I			0x40 /* D-channel buffer status */
#घोषणा AMR_IR_MLTFRMI			0x80 /* multअगरrame or PP */

/* The amd7930 has "indirect registers" which are accessed by writing
 * the रेजिस्टर number पूर्णांकo the Command Register and then पढ़ोing or
 * writing values from the Data Register as appropriate. We define the
 * AMR_* macros to be the indirect रेजिस्टर numbers and AM_* macros to
 * be bits in whatever रेजिस्टर is referred to.
 */

/* Initialization */
#घोषणा	AMR_INIT			0x21
#घोषणा		AM_INIT_ACTIVE			0x01
#घोषणा		AM_INIT_DATAONLY		0x02
#घोषणा		AM_INIT_POWERDOWN		0x03
#घोषणा		AM_INIT_DISABLE_INTS		0x04
#घोषणा AMR_INIT2			0x20
#घोषणा		AM_INIT2_ENABLE_POWERDOWN	0x20
#घोषणा		AM_INIT2_ENABLE_MULTIFRAME	0x10

/* Line Interface Unit */
#घोषणा	AMR_LIU_LSR			0xA1
#घोषणा		AM_LIU_LSR_STATE		0x07
#घोषणा		AM_LIU_LSR_F3			0x08
#घोषणा		AM_LIU_LSR_F7			0x10
#घोषणा		AM_LIU_LSR_F8			0x20
#घोषणा		AM_LIU_LSR_HSW			0x40
#घोषणा		AM_LIU_LSR_HSW_CHG		0x80
#घोषणा	AMR_LIU_LPR			0xA2
#घोषणा	AMR_LIU_LMR1			0xA3
#घोषणा		AM_LIU_LMR1_B1_ENABL		0x01
#घोषणा		AM_LIU_LMR1_B2_ENABL		0x02
#घोषणा		AM_LIU_LMR1_F_DISABL		0x04
#घोषणा		AM_LIU_LMR1_FA_DISABL		0x08
#घोषणा		AM_LIU_LMR1_REQ_ACTIV		0x10
#घोषणा		AM_LIU_LMR1_F8_F3		0x20
#घोषणा		AM_LIU_LMR1_LIU_ENABL		0x40
#घोषणा	AMR_LIU_LMR2			0xA4
#घोषणा		AM_LIU_LMR2_DECHO		0x01
#घोषणा		AM_LIU_LMR2_DLOOP		0x02
#घोषणा		AM_LIU_LMR2_DBACKOFF		0x04
#घोषणा		AM_LIU_LMR2_EN_F3_INT		0x08
#घोषणा		AM_LIU_LMR2_EN_F8_INT		0x10
#घोषणा		AM_LIU_LMR2_EN_HSW_INT		0x20
#घोषणा		AM_LIU_LMR2_EN_F7_INT		0x40
#घोषणा	AMR_LIU_2_4			0xA5
#घोषणा	AMR_LIU_MF			0xA6
#घोषणा	AMR_LIU_MFSB			0xA7
#घोषणा	AMR_LIU_MFQB			0xA8

/* Multiplexor */
#घोषणा	AMR_MUX_MCR1			0x41
#घोषणा	AMR_MUX_MCR2			0x42
#घोषणा	AMR_MUX_MCR3			0x43
#घोषणा		AM_MUX_CHANNEL_B1		0x01
#घोषणा		AM_MUX_CHANNEL_B2		0x02
#घोषणा		AM_MUX_CHANNEL_Ba		0x03
#घोषणा		AM_MUX_CHANNEL_Bb		0x04
#घोषणा		AM_MUX_CHANNEL_Bc		0x05
#घोषणा		AM_MUX_CHANNEL_Bd		0x06
#घोषणा		AM_MUX_CHANNEL_Be		0x07
#घोषणा		AM_MUX_CHANNEL_Bf		0x08
#घोषणा	AMR_MUX_MCR4			0x44
#घोषणा		AM_MUX_MCR4_ENABLE_INTS		0x08
#घोषणा		AM_MUX_MCR4_REVERSE_Bb		0x10
#घोषणा		AM_MUX_MCR4_REVERSE_Bc		0x20
#घोषणा	AMR_MUX_1_4			0x45

/* Main Audio Processor */
#घोषणा	AMR_MAP_X			0x61
#घोषणा	AMR_MAP_R			0x62
#घोषणा	AMR_MAP_GX			0x63
#घोषणा	AMR_MAP_GR			0x64
#घोषणा	AMR_MAP_GER			0x65
#घोषणा	AMR_MAP_STGR			0x66
#घोषणा	AMR_MAP_FTGR_1_2		0x67
#घोषणा	AMR_MAP_ATGR_1_2		0x68
#घोषणा	AMR_MAP_MMR1			0x69
#घोषणा		AM_MAP_MMR1_ALAW		0x01
#घोषणा		AM_MAP_MMR1_GX			0x02
#घोषणा		AM_MAP_MMR1_GR			0x04
#घोषणा		AM_MAP_MMR1_GER			0x08
#घोषणा		AM_MAP_MMR1_X			0x10
#घोषणा		AM_MAP_MMR1_R			0x20
#घोषणा		AM_MAP_MMR1_STG			0x40
#घोषणा		AM_MAP_MMR1_LOOPBACK		0x80
#घोषणा	AMR_MAP_MMR2			0x6A
#घोषणा		AM_MAP_MMR2_AINB		0x01
#घोषणा		AM_MAP_MMR2_LS			0x02
#घोषणा		AM_MAP_MMR2_ENABLE_DTMF		0x04
#घोषणा		AM_MAP_MMR2_ENABLE_TONEGEN	0x08
#घोषणा		AM_MAP_MMR2_ENABLE_TONERING	0x10
#घोषणा		AM_MAP_MMR2_DISABLE_HIGHPASS	0x20
#घोषणा		AM_MAP_MMR2_DISABLE_AUTOZERO	0x40
#घोषणा	AMR_MAP_1_10			0x6B
#घोषणा	AMR_MAP_MMR3			0x6C
#घोषणा	AMR_MAP_STRA			0x6D
#घोषणा	AMR_MAP_STRF			0x6E
#घोषणा	AMR_MAP_PEAKX			0x70
#घोषणा	AMR_MAP_PEAKR			0x71
#घोषणा	AMR_MAP_15_16			0x72

/* Data Link Controller */
#घोषणा	AMR_DLC_FRAR_1_2_3		0x81
#घोषणा	AMR_DLC_SRAR_1_2_3		0x82
#घोषणा	AMR_DLC_TAR			0x83
#घोषणा	AMR_DLC_DRLR			0x84
#घोषणा	AMR_DLC_DTCR			0x85
#घोषणा	AMR_DLC_DMR1			0x86
#घोषणा		AMR_DLC_DMR1_DTTHRSH_INT	0x01
#घोषणा		AMR_DLC_DMR1_DRTHRSH_INT	0x02
#घोषणा		AMR_DLC_DMR1_TAR_ENABL		0x04
#घोषणा		AMR_DLC_DMR1_EORP_INT		0x08
#घोषणा		AMR_DLC_DMR1_EN_ADDR1		0x10
#घोषणा		AMR_DLC_DMR1_EN_ADDR2		0x20
#घोषणा		AMR_DLC_DMR1_EN_ADDR3		0x40
#घोषणा		AMR_DLC_DMR1_EN_ADDR4		0x80
#घोषणा		AMR_DLC_DMR1_EN_ADDRS		0xf0
#घोषणा	AMR_DLC_DMR2			0x87
#घोषणा		AMR_DLC_DMR2_RABRT_INT		0x01
#घोषणा		AMR_DLC_DMR2_RESID_INT		0x02
#घोषणा		AMR_DLC_DMR2_COLL_INT		0x04
#घोषणा		AMR_DLC_DMR2_FCS_INT		0x08
#घोषणा		AMR_DLC_DMR2_OVFL_INT		0x10
#घोषणा		AMR_DLC_DMR2_UNFL_INT		0x20
#घोषणा		AMR_DLC_DMR2_OVRN_INT		0x40
#घोषणा		AMR_DLC_DMR2_UNRN_INT		0x80
#घोषणा	AMR_DLC_1_7			0x88
#घोषणा	AMR_DLC_DRCR			0x89
#घोषणा	AMR_DLC_RNGR1			0x8A
#घोषणा	AMR_DLC_RNGR2			0x8B
#घोषणा	AMR_DLC_FRAR4			0x8C
#घोषणा	AMR_DLC_SRAR4			0x8D
#घोषणा	AMR_DLC_DMR3			0x8E
#घोषणा		AMR_DLC_DMR3_VA_INT		0x01
#घोषणा		AMR_DLC_DMR3_EOTP_INT		0x02
#घोषणा		AMR_DLC_DMR3_LBRP_INT		0x04
#घोषणा		AMR_DLC_DMR3_RBA_INT		0x08
#घोषणा		AMR_DLC_DMR3_LBT_INT		0x10
#घोषणा		AMR_DLC_DMR3_TBE_INT		0x20
#घोषणा		AMR_DLC_DMR3_RPLOST_INT		0x40
#घोषणा		AMR_DLC_DMR3_KEEP_FCS		0x80
#घोषणा	AMR_DLC_DMR4			0x8F
#घोषणा		AMR_DLC_DMR4_RCV_1		0x00
#घोषणा		AMR_DLC_DMR4_RCV_2		0x01
#घोषणा		AMR_DLC_DMR4_RCV_4		0x02
#घोषणा		AMR_DLC_DMR4_RCV_8		0x03
#घोषणा		AMR_DLC_DMR4_RCV_16		0x01
#घोषणा		AMR_DLC_DMR4_RCV_24		0x02
#घोषणा		AMR_DLC_DMR4_RCV_30		0x03
#घोषणा		AMR_DLC_DMR4_XMT_1		0x00
#घोषणा		AMR_DLC_DMR4_XMT_2		0x04
#घोषणा		AMR_DLC_DMR4_XMT_4		0x08
#घोषणा		AMR_DLC_DMR4_XMT_8		0x0c
#घोषणा		AMR_DLC_DMR4_XMT_10		0x08
#घोषणा		AMR_DLC_DMR4_XMT_14		0x0c
#घोषणा		AMR_DLC_DMR4_IDLE_MARK		0x00
#घोषणा		AMR_DLC_DMR4_IDLE_FLAG		0x10
#घोषणा		AMR_DLC_DMR4_ADDR_BOTH		0x00
#घोषणा		AMR_DLC_DMR4_ADDR_1ST		0x20
#घोषणा		AMR_DLC_DMR4_ADDR_2ND		0xa0
#घोषणा		AMR_DLC_DMR4_CR_ENABLE		0x40
#घोषणा	AMR_DLC_12_15			0x90
#घोषणा	AMR_DLC_ASR			0x91
#घोषणा	AMR_DLC_EFCR			0x92
#घोषणा		AMR_DLC_EFCR_EXTEND_FIFO	0x01
#घोषणा		AMR_DLC_EFCR_SEC_PKT_INT	0x02

#घोषणा AMR_DSR1_VADDR			0x01
#घोषणा AMR_DSR1_EORP			0x02
#घोषणा AMR_DSR1_PKT_IP			0x04
#घोषणा AMR_DSR1_DECHO_ON		0x08
#घोषणा AMR_DSR1_DLOOP_ON		0x10
#घोषणा AMR_DSR1_DBACK_OFF		0x20
#घोषणा AMR_DSR1_EOTP			0x40
#घोषणा AMR_DSR1_CXMT_ABRT		0x80

#घोषणा AMR_DSR2_LBRP			0x01
#घोषणा AMR_DSR2_RBA			0x02
#घोषणा AMR_DSR2_RPLOST			0x04
#घोषणा AMR_DSR2_LAST_BYTE		0x08
#घोषणा AMR_DSR2_TBE			0x10
#घोषणा AMR_DSR2_MARK_IDLE		0x20
#घोषणा AMR_DSR2_FLAG_IDLE		0x40
#घोषणा AMR_DSR2_SECOND_PKT		0x80

#घोषणा AMR_DER_RABRT			0x01
#घोषणा AMR_DER_RFRAME			0x02
#घोषणा AMR_DER_COLLISION		0x04
#घोषणा AMR_DER_FCS			0x08
#घोषणा AMR_DER_OVFL			0x10
#घोषणा AMR_DER_UNFL			0x20
#घोषणा AMR_DER_OVRN			0x40
#घोषणा AMR_DER_UNRN			0x80

/* Peripheral Port */
#घोषणा	AMR_PP_PPCR1			0xC0
#घोषणा	AMR_PP_PPSR			0xC1
#घोषणा	AMR_PP_PPIER			0xC2
#घोषणा	AMR_PP_MTDR			0xC3
#घोषणा	AMR_PP_MRDR			0xC3
#घोषणा	AMR_PP_CITDR0			0xC4
#घोषणा	AMR_PP_CIRDR0			0xC4
#घोषणा	AMR_PP_CITDR1			0xC5
#घोषणा	AMR_PP_CIRDR1			0xC5
#घोषणा	AMR_PP_PPCR2			0xC8
#घोषणा	AMR_PP_PPCR3			0xC9

काष्ठा snd_amd7930 अणु
	spinlock_t		lock;
	व्योम __iomem		*regs;
	u32			flags;
#घोषणा AMD7930_FLAG_PLAYBACK	0x00000001
#घोषणा AMD7930_FLAG_CAPTURE	0x00000002

	काष्ठा amd7930_map	map;

	काष्ठा snd_card		*card;
	काष्ठा snd_pcm		*pcm;
	काष्ठा snd_pcm_substream	*playback_substream;
	काष्ठा snd_pcm_substream	*capture_substream;

	/* Playback/Capture buffer state. */
	अचिन्हित अक्षर		*p_orig, *p_cur;
	पूर्णांक			p_left;
	अचिन्हित अक्षर		*c_orig, *c_cur;
	पूर्णांक			c_left;

	पूर्णांक			rgain;
	पूर्णांक			pgain;
	पूर्णांक			mgain;

	काष्ठा platक्रमm_device	*op;
	अचिन्हित पूर्णांक		irq;
	काष्ठा snd_amd7930	*next;
पूर्ण;

अटल काष्ठा snd_amd7930 *amd7930_list;

/* Idle the AMD7930 chip.  The amd->lock is not held.  */
अटल __अंतरभूत__ व्योम amd7930_idle(काष्ठा snd_amd7930 *amd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&amd->lock, flags);
	sbus_ग_लिखोb(AMR_INIT, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(0, amd->regs + AMD7930_DR);
	spin_unlock_irqrestore(&amd->lock, flags);
पूर्ण

/* Enable chip पूर्णांकerrupts.  The amd->lock is not held.  */
अटल __अंतरभूत__ व्योम amd7930_enable_पूर्णांकs(काष्ठा snd_amd7930 *amd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&amd->lock, flags);
	sbus_ग_लिखोb(AMR_INIT, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(AM_INIT_ACTIVE, amd->regs + AMD7930_DR);
	spin_unlock_irqrestore(&amd->lock, flags);
पूर्ण

/* Disable chip पूर्णांकerrupts.  The amd->lock is not held.  */
अटल __अंतरभूत__ व्योम amd7930_disable_पूर्णांकs(काष्ठा snd_amd7930 *amd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&amd->lock, flags);
	sbus_ग_लिखोb(AMR_INIT, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(AM_INIT_ACTIVE | AM_INIT_DISABLE_INTS, amd->regs + AMD7930_DR);
	spin_unlock_irqrestore(&amd->lock, flags);
पूर्ण

/* Commit amd7930_map settings to the hardware.
 * The amd->lock is held and local पूर्णांकerrupts are disabled.
 */
अटल व्योम __amd7930_ग_लिखो_map(काष्ठा snd_amd7930 *amd)
अणु
	काष्ठा amd7930_map *map = &amd->map;

	sbus_ग_लिखोb(AMR_MAP_GX, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(((map->gx >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_ग_लिखोb(((map->gx >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_ग_लिखोb(AMR_MAP_GR, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(((map->gr >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_ग_लिखोb(((map->gr >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_ग_लिखोb(AMR_MAP_STGR, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(((map->stgr >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_ग_लिखोb(((map->stgr >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_ग_लिखोb(AMR_MAP_GER, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(((map->ger >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_ग_लिखोb(((map->ger >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_ग_लिखोb(AMR_MAP_MMR1, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(map->mmr1, amd->regs + AMD7930_DR);

	sbus_ग_लिखोb(AMR_MAP_MMR2, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(map->mmr2, amd->regs + AMD7930_DR);
पूर्ण

/* gx, gr & stg gains.  this table must contain 256 elements with
 * the 0th being "infinity" (the magic value 9008).  The reमुख्यing
 * elements match sun's gain curve (but with higher resolution):
 * -18 to 0dB in .16dB steps then 0 to 12dB in .08dB steps.
 */
अटल __स्थिर__ __u16 gx_coeff[256] = अणु
	0x9008, 0x8b7c, 0x8b51, 0x8b45, 0x8b42, 0x8b3b, 0x8b36, 0x8b33,
	0x8b32, 0x8b2a, 0x8b2b, 0x8b2c, 0x8b25, 0x8b23, 0x8b22, 0x8b22,
	0x9122, 0x8b1a, 0x8aa3, 0x8aa3, 0x8b1c, 0x8aa6, 0x912d, 0x912b,
	0x8aab, 0x8b12, 0x8aaa, 0x8ab2, 0x9132, 0x8ab4, 0x913c, 0x8abb,
	0x9142, 0x9144, 0x9151, 0x8ad5, 0x8aeb, 0x8a79, 0x8a5a, 0x8a4a,
	0x8b03, 0x91c2, 0x91bb, 0x8a3f, 0x8a33, 0x91b2, 0x9212, 0x9213,
	0x8a2c, 0x921d, 0x8a23, 0x921a, 0x9222, 0x9223, 0x922d, 0x9231,
	0x9234, 0x9242, 0x925b, 0x92dd, 0x92c1, 0x92b3, 0x92ab, 0x92a4,
	0x92a2, 0x932b, 0x9341, 0x93d3, 0x93b2, 0x93a2, 0x943c, 0x94b2,
	0x953a, 0x9653, 0x9782, 0x9e21, 0x9d23, 0x9cd2, 0x9c23, 0x9baa,
	0x9bde, 0x9b33, 0x9b22, 0x9b1d, 0x9ab2, 0xa142, 0xa1e5, 0x9a3b,
	0xa213, 0xa1a2, 0xa231, 0xa2eb, 0xa313, 0xa334, 0xa421, 0xa54b,
	0xada4, 0xac23, 0xab3b, 0xaaab, 0xaa5c, 0xb1a3, 0xb2ca, 0xb3bd,
	0xbe24, 0xbb2b, 0xba33, 0xc32b, 0xcb5a, 0xd2a2, 0xe31d, 0x0808,
	0x72ba, 0x62c2, 0x5c32, 0x52db, 0x513e, 0x4cce, 0x43b2, 0x4243,
	0x41b4, 0x3b12, 0x3bc3, 0x3df2, 0x34bd, 0x3334, 0x32c2, 0x3224,
	0x31aa, 0x2a7b, 0x2aaa, 0x2b23, 0x2bba, 0x2c42, 0x2e23, 0x25bb,
	0x242b, 0x240f, 0x231a, 0x22bb, 0x2241, 0x2223, 0x221f, 0x1a33,
	0x1a4a, 0x1acd, 0x2132, 0x1b1b, 0x1b2c, 0x1b62, 0x1c12, 0x1c32,
	0x1d1b, 0x1e71, 0x16b1, 0x1522, 0x1434, 0x1412, 0x1352, 0x1323,
	0x1315, 0x12bc, 0x127a, 0x1235, 0x1226, 0x11a2, 0x1216, 0x0a2a,
	0x11bc, 0x11d1, 0x1163, 0x0ac2, 0x0ab2, 0x0aab, 0x0b1b, 0x0b23,
	0x0b33, 0x0c0f, 0x0bb3, 0x0c1b, 0x0c3e, 0x0cb1, 0x0d4c, 0x0ec1,
	0x079a, 0x0614, 0x0521, 0x047c, 0x0422, 0x03b1, 0x03e3, 0x0333,
	0x0322, 0x031c, 0x02aa, 0x02ba, 0x02f2, 0x0242, 0x0232, 0x0227,
	0x0222, 0x021b, 0x01ad, 0x0212, 0x01b2, 0x01bb, 0x01cb, 0x01f6,
	0x0152, 0x013a, 0x0133, 0x0131, 0x012c, 0x0123, 0x0122, 0x00a2,
	0x011b, 0x011e, 0x0114, 0x00b1, 0x00aa, 0x00b3, 0x00bd, 0x00ba,
	0x00c5, 0x00d3, 0x00f3, 0x0062, 0x0051, 0x0042, 0x003b, 0x0033,
	0x0032, 0x002a, 0x002c, 0x0025, 0x0023, 0x0022, 0x001a, 0x0021,
	0x001b, 0x001b, 0x001d, 0x0015, 0x0013, 0x0013, 0x0012, 0x0012,
	0x000a, 0x000a, 0x0011, 0x0011, 0x000b, 0x000b, 0x000c, 0x000e,
पूर्ण;

अटल __स्थिर__ __u16 ger_coeff[] = अणु
	0x431f, /* 5. dB */
	0x331f, /* 5.5 dB */
	0x40dd, /* 6. dB */
	0x11dd, /* 6.5 dB */
	0x440f, /* 7. dB */
	0x411f, /* 7.5 dB */
	0x311f, /* 8. dB */
	0x5520, /* 8.5 dB */
	0x10dd, /* 9. dB */
	0x4211, /* 9.5 dB */
	0x410f, /* 10. dB */
	0x111f, /* 10.5 dB */
	0x600b, /* 11. dB */
	0x00dd, /* 11.5 dB */
	0x4210, /* 12. dB */
	0x110f, /* 13. dB */
	0x7200, /* 14. dB */
	0x2110, /* 15. dB */
	0x2200, /* 15.9 dB */
	0x000b, /* 16.9 dB */
	0x000f  /* 18. dB */
पूर्ण;

/* Update amd7930_map settings and program them पूर्णांकo the hardware.
 * The amd->lock is held and local पूर्णांकerrupts are disabled.
 */
अटल व्योम __amd7930_update_map(काष्ठा snd_amd7930 *amd)
अणु
	काष्ठा amd7930_map *map = &amd->map;
	पूर्णांक level;

	map->gx = gx_coeff[amd->rgain];
	map->stgr = gx_coeff[amd->mgain];
	level = (amd->pgain * (256 + ARRAY_SIZE(ger_coeff))) >> 8;
	अगर (level >= 256) अणु
		map->ger = ger_coeff[level - 256];
		map->gr = gx_coeff[255];
	पूर्ण अन्यथा अणु
		map->ger = ger_coeff[0];
		map->gr = gx_coeff[level];
	पूर्ण
	__amd7930_ग_लिखो_map(amd);
पूर्ण

अटल irqवापस_t snd_amd7930_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_amd7930 *amd = dev_id;
	अचिन्हित पूर्णांक elapsed;
	u8 ir;

	spin_lock(&amd->lock);

	elapsed = 0;

	ir = sbus_पढ़ोb(amd->regs + AMD7930_IR);
	अगर (ir & AMR_IR_BBUF) अणु
		u8 byte;

		अगर (amd->flags & AMD7930_FLAG_PLAYBACK) अणु
			अगर (amd->p_left > 0) अणु
				byte = *(amd->p_cur++);
				amd->p_left--;
				sbus_ग_लिखोb(byte, amd->regs + AMD7930_BBTB);
				अगर (amd->p_left == 0)
					elapsed |= AMD7930_FLAG_PLAYBACK;
			पूर्ण अन्यथा
				sbus_ग_लिखोb(0, amd->regs + AMD7930_BBTB);
		पूर्ण अन्यथा अगर (amd->flags & AMD7930_FLAG_CAPTURE) अणु
			byte = sbus_पढ़ोb(amd->regs + AMD7930_BBRB);
			अगर (amd->c_left > 0) अणु
				*(amd->c_cur++) = byte;
				amd->c_left--;
				अगर (amd->c_left == 0)
					elapsed |= AMD7930_FLAG_CAPTURE;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&amd->lock);

	अगर (elapsed & AMD7930_FLAG_PLAYBACK)
		snd_pcm_period_elapsed(amd->playback_substream);
	अन्यथा
		snd_pcm_period_elapsed(amd->capture_substream);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_amd7930_trigger(काष्ठा snd_amd7930 *amd, अचिन्हित पूर्णांक flag, पूर्णांक cmd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	spin_lock_irqsave(&amd->lock, flags);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		अगर (!(amd->flags & flag)) अणु
			amd->flags |= flag;

			/* Enable B channel पूर्णांकerrupts.  */
			sbus_ग_लिखोb(AMR_MUX_MCR4, amd->regs + AMD7930_CR);
			sbus_ग_लिखोb(AM_MUX_MCR4_ENABLE_INTS, amd->regs + AMD7930_DR);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		अगर (amd->flags & flag) अणु
			amd->flags &= ~flag;

			/* Disable B channel पूर्णांकerrupts.  */
			sbus_ग_लिखोb(AMR_MUX_MCR4, amd->regs + AMD7930_CR);
			sbus_ग_लिखोb(0, amd->regs + AMD7930_DR);
		पूर्ण
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&amd->lock, flags);

	वापस result;
पूर्ण

अटल पूर्णांक snd_amd7930_playback_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	वापस snd_amd7930_trigger(amd, AMD7930_FLAG_PLAYBACK, cmd);
पूर्ण

अटल पूर्णांक snd_amd7930_capture_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	वापस snd_amd7930_trigger(amd, AMD7930_FLAG_CAPTURE, cmd);
पूर्ण

अटल पूर्णांक snd_amd7930_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित दीर्घ flags;
	u8 new_mmr1;

	spin_lock_irqsave(&amd->lock, flags);

	amd->flags |= AMD7930_FLAG_PLAYBACK;

	/* Setup the pseuकरो-dma transfer poपूर्णांकers.  */
	amd->p_orig = amd->p_cur = runसमय->dma_area;
	amd->p_left = size;

	/* Put the chip पूर्णांकo the correct encoding क्रमmat.  */
	new_mmr1 = amd->map.mmr1;
	अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_A_LAW)
		new_mmr1 |= AM_MAP_MMR1_ALAW;
	अन्यथा
		new_mmr1 &= ~AM_MAP_MMR1_ALAW;
	अगर (new_mmr1 != amd->map.mmr1) अणु
		amd->map.mmr1 = new_mmr1;
		__amd7930_update_map(amd);
	पूर्ण

	spin_unlock_irqrestore(&amd->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित दीर्घ flags;
	u8 new_mmr1;

	spin_lock_irqsave(&amd->lock, flags);

	amd->flags |= AMD7930_FLAG_CAPTURE;

	/* Setup the pseuकरो-dma transfer poपूर्णांकers.  */
	amd->c_orig = amd->c_cur = runसमय->dma_area;
	amd->c_left = size;

	/* Put the chip पूर्णांकo the correct encoding क्रमmat.  */
	new_mmr1 = amd->map.mmr1;
	अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_A_LAW)
		new_mmr1 |= AM_MAP_MMR1_ALAW;
	अन्यथा
		new_mmr1 &= ~AM_MAP_MMR1_ALAW;
	अगर (new_mmr1 != amd->map.mmr1) अणु
		amd->map.mmr1 = new_mmr1;
		__amd7930_update_map(amd);
	पूर्ण

	spin_unlock_irqrestore(&amd->lock, flags);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_amd7930_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(amd->flags & AMD7930_FLAG_PLAYBACK))
		वापस 0;
	ptr = amd->p_cur - amd->p_orig;
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_amd7930_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(amd->flags & AMD7930_FLAG_CAPTURE))
		वापस 0;

	ptr = amd->c_cur - amd->c_orig;
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

/* Playback and capture have identical properties.  */
अटल स्थिर काष्ठा snd_pcm_hardware snd_amd7930_pcm_hw =
अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_MMAP_VALID |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_HALF_DUPLEX),
	.क्रमmats		= SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW,
	.rates			= SNDRV_PCM_RATE_8000,
	.rate_min		= 8000,
	.rate_max		= 8000,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= (64*1024),
	.period_bytes_min	= 1,
	.period_bytes_max	= (64*1024),
	.periods_min		= 1,
	.periods_max		= 1024,
पूर्ण;

अटल पूर्णांक snd_amd7930_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	amd->playback_substream = substream;
	runसमय->hw = snd_amd7930_pcm_hw;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	amd->capture_substream = substream;
	runसमय->hw = snd_amd7930_pcm_hw;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);

	amd->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_amd7930 *amd = snd_pcm_substream_chip(substream);

	amd->capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_amd7930_playback_ops = अणु
	.खोलो		=	snd_amd7930_playback_खोलो,
	.बंद		=	snd_amd7930_playback_बंद,
	.prepare	=	snd_amd7930_playback_prepare,
	.trigger	=	snd_amd7930_playback_trigger,
	.poपूर्णांकer	=	snd_amd7930_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_amd7930_capture_ops = अणु
	.खोलो		=	snd_amd7930_capture_खोलो,
	.बंद		=	snd_amd7930_capture_बंद,
	.prepare	=	snd_amd7930_capture_prepare,
	.trigger	=	snd_amd7930_capture_trigger,
	.poपूर्णांकer	=	snd_amd7930_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_amd7930_pcm(काष्ठा snd_amd7930 *amd)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(amd->card,
			       /* ID */             "sun_amd7930",
			       /* device */         0,
			       /* playback count */ 1,
			       /* capture count */  1, &pcm)) < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_amd7930_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_amd7930_capture_ops);

	pcm->निजी_data = amd;
	pcm->info_flags = 0;
	म_नकल(pcm->name, amd->card->लघुname);
	amd->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 64*1024, 64*1024);

	वापस 0;
पूर्ण

#घोषणा VOLUME_MONITOR	0
#घोषणा VOLUME_CAPTURE	1
#घोषणा VOLUME_PLAYBACK	2

अटल पूर्णांक snd_amd7930_info_volume(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_get_volume(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_amd7930 *amd = snd_kcontrol_chip(kctl);
	पूर्णांक type = kctl->निजी_value;
	पूर्णांक *swval;

	चयन (type) अणु
	हाल VOLUME_MONITOR:
		swval = &amd->mgain;
		अवरोध;
	हाल VOLUME_CAPTURE:
		swval = &amd->rgain;
		अवरोध;
	हाल VOLUME_PLAYBACK:
	शेष:
		swval = &amd->pgain;
		अवरोध;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = *swval;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_put_volume(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_amd7930 *amd = snd_kcontrol_chip(kctl);
	अचिन्हित दीर्घ flags;
	पूर्णांक type = kctl->निजी_value;
	पूर्णांक *swval, change;

	चयन (type) अणु
	हाल VOLUME_MONITOR:
		swval = &amd->mgain;
		अवरोध;
	हाल VOLUME_CAPTURE:
		swval = &amd->rgain;
		अवरोध;
	हाल VOLUME_PLAYBACK:
	शेष:
		swval = &amd->pgain;
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&amd->lock, flags);

	अगर (*swval != ucontrol->value.पूर्णांकeger.value[0]) अणु
		*swval = ucontrol->value.पूर्णांकeger.value[0] & 0xff;
		__amd7930_update_map(amd);
		change = 1;
	पूर्ण अन्यथा
		change = 0;

	spin_unlock_irqrestore(&amd->lock, flags);

	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new amd7930_controls[] = अणु
	अणु
		.अगरace		=	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name		=	"Monitor Volume",
		.index		=	0,
		.info		=	snd_amd7930_info_volume,
		.get		=	snd_amd7930_get_volume,
		.put		=	snd_amd7930_put_volume,
		.निजी_value	=	VOLUME_MONITOR,
	पूर्ण,
	अणु
		.अगरace		=	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name		=	"Capture Volume",
		.index		=	0,
		.info		=	snd_amd7930_info_volume,
		.get		=	snd_amd7930_get_volume,
		.put		=	snd_amd7930_put_volume,
		.निजी_value	=	VOLUME_CAPTURE,
	पूर्ण,
	अणु
		.अगरace		=	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name		=	"Playback Volume",
		.index		=	0,
		.info		=	snd_amd7930_info_volume,
		.get		=	snd_amd7930_get_volume,
		.put		=	snd_amd7930_put_volume,
		.निजी_value	=	VOLUME_PLAYBACK,
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_amd7930_mixer(काष्ठा snd_amd7930 *amd)
अणु
	काष्ठा snd_card *card;
	पूर्णांक idx, err;

	अगर (snd_BUG_ON(!amd || !amd->card))
		वापस -EINVAL;

	card = amd->card;
	म_नकल(card->mixername, card->लघुname);

	क्रम (idx = 0; idx < ARRAY_SIZE(amd7930_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card,
				       snd_ctl_new1(&amd7930_controls[idx], amd))) < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_मुक्त(काष्ठा snd_amd7930 *amd)
अणु
	काष्ठा platक्रमm_device *op = amd->op;

	amd7930_idle(amd);

	अगर (amd->irq)
		मुक्त_irq(amd->irq, amd);

	अगर (amd->regs)
		of_iounmap(&op->resource[0], amd->regs,
			   resource_size(&op->resource[0]));

	kमुक्त(amd);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_amd7930_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_amd7930 *amd = device->device_data;

	वापस snd_amd7930_मुक्त(amd);
पूर्ण

अटल स्थिर काष्ठा snd_device_ops snd_amd7930_dev_ops = अणु
	.dev_मुक्त	=	snd_amd7930_dev_मुक्त,
पूर्ण;

अटल पूर्णांक snd_amd7930_create(काष्ठा snd_card *card,
			      काष्ठा platक्रमm_device *op,
			      पूर्णांक irq, पूर्णांक dev,
			      काष्ठा snd_amd7930 **ramd)
अणु
	काष्ठा snd_amd7930 *amd;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	*ramd = शून्य;
	amd = kzalloc(माप(*amd), GFP_KERNEL);
	अगर (amd == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&amd->lock);
	amd->card = card;
	amd->op = op;

	amd->regs = of_ioremap(&op->resource[0], 0,
			       resource_size(&op->resource[0]), "amd7930");
	अगर (!amd->regs) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "amd7930-%d: Unable to map chip registers.\n", dev);
		kमुक्त(amd);
		वापस -EIO;
	पूर्ण

	amd7930_idle(amd);

	अगर (request_irq(irq, snd_amd7930_पूर्णांकerrupt,
			IRQF_SHARED, "amd7930", amd)) अणु
		snd_prपूर्णांकk(KERN_ERR "amd7930-%d: Unable to grab IRQ %d\n",
			   dev, irq);
		snd_amd7930_मुक्त(amd);
		वापस -EBUSY;
	पूर्ण
	amd->irq = irq;

	amd7930_enable_पूर्णांकs(amd);

	spin_lock_irqsave(&amd->lock, flags);

	amd->rgain = 128;
	amd->pgain = 200;
	amd->mgain = 0;

	स_रखो(&amd->map, 0, माप(amd->map));
	amd->map.mmr1 = (AM_MAP_MMR1_GX | AM_MAP_MMR1_GER |
			 AM_MAP_MMR1_GR | AM_MAP_MMR1_STG);
	amd->map.mmr2 = (AM_MAP_MMR2_LS | AM_MAP_MMR2_AINB);

	__amd7930_update_map(amd);

	/* Always MUX audio (Ba) to channel Bb. */
	sbus_ग_लिखोb(AMR_MUX_MCR1, amd->regs + AMD7930_CR);
	sbus_ग_लिखोb(AM_MUX_CHANNEL_Ba | (AM_MUX_CHANNEL_Bb << 4),
		    amd->regs + AMD7930_DR);

	spin_unlock_irqrestore(&amd->lock, flags);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
				  amd, &snd_amd7930_dev_ops)) < 0) अणु
		snd_amd7930_मुक्त(amd);
		वापस err;
	पूर्ण

	*ramd = amd;
	वापस 0;
पूर्ण

अटल पूर्णांक amd7930_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा resource *rp = &op->resource[0];
	अटल पूर्णांक dev_num;
	काष्ठा snd_card *card;
	काष्ठा snd_amd7930 *amd;
	पूर्णांक err, irq;

	irq = op->archdata.irqs[0];

	अगर (dev_num >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev_num]) अणु
		dev_num++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&op->dev, index[dev_num], id[dev_num],
			   THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "AMD7930");
	म_नकल(card->लघुname, "Sun AMD7930");
	प्र_लिखो(card->दीर्घname, "%s at 0x%02lx:0x%08Lx, irq %d",
		card->लघुname,
		rp->flags & 0xffL,
		(अचिन्हित दीर्घ दीर्घ)rp->start,
		irq);

	अगर ((err = snd_amd7930_create(card, op,
				      irq, dev_num, &amd)) < 0)
		जाओ out_err;

	अगर ((err = snd_amd7930_pcm(amd)) < 0)
		जाओ out_err;

	अगर ((err = snd_amd7930_mixer(amd)) < 0)
		जाओ out_err;

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ out_err;

	amd->next = amd7930_list;
	amd7930_list = amd;

	dev_num++;

	वापस 0;

out_err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id amd7930_match[] = अणु
	अणु
		.name = "audio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, amd7930_match);

अटल काष्ठा platक्रमm_driver amd7930_sbus_driver = अणु
	.driver = अणु
		.name = "audio",
		.of_match_table = amd7930_match,
	पूर्ण,
	.probe		= amd7930_sbus_probe,
पूर्ण;

अटल पूर्णांक __init amd7930_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&amd7930_sbus_driver);
पूर्ण

अटल व्योम __निकास amd7930_निकास(व्योम)
अणु
	काष्ठा snd_amd7930 *p = amd7930_list;

	जबतक (p != शून्य) अणु
		काष्ठा snd_amd7930 *next = p->next;

		snd_card_मुक्त(p->card);

		p = next;
	पूर्ण

	amd7930_list = शून्य;

	platक्रमm_driver_unरेजिस्टर(&amd7930_sbus_driver);
पूर्ण

module_init(amd7930_init);
module_निकास(amd7930_निकास);
