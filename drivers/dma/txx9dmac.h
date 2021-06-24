<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the TXx9 SoC DMA Controller
 *
 * Copyright (C) 2009 Atsushi Nemoto
 */
#अगर_अघोषित TXX9DMAC_H
#घोषणा TXX9DMAC_H

#समावेश <linux/dmaengine.h>
#समावेश <यंत्र/txx9/dmac.h>

/*
 * Design Notes:
 *
 * This DMAC have four channels and one FIFO buffer.  Each channel can
 * be configured क्रम memory-memory or device-memory transfer, but only
 * one channel can करो alignment-मुक्त memory-memory transfer at a समय
 * जबतक the channel should occupy the FIFO buffer क्रम effective
 * transfers.
 *
 * Instead of dynamically assign the FIFO buffer to channels, I chose
 * make one dedicated channel क्रम memory-memory transfer.  The
 * dedicated channel is खुला.  Other channels are निजी and used
 * क्रम slave transfer.  Some devices in the SoC are wired to certain
 * DMA channel.
 */

#अगर_घोषित CONFIG_MACH_TX49XX
अटल अंतरभूत bool txx9_dma_have_SMPCHN(व्योम)
अणु
	वापस true;
पूर्ण
#घोषणा TXX9_DMA_USE_SIMPLE_CHAIN
#अन्यथा
अटल अंतरभूत bool txx9_dma_have_SMPCHN(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN
#अगर_घोषित CONFIG_MACH_TX49XX
#घोषणा CCR_LE	TXX9_DMA_CCR_LE
#घोषणा MCR_LE	0
#अन्यथा
#घोषणा CCR_LE	0
#घोषणा MCR_LE	TXX9_DMA_MCR_LE
#पूर्ण_अगर
#अन्यथा
#घोषणा CCR_LE	0
#घोषणा MCR_LE	0
#पूर्ण_अगर

/*
 * Redefine this macro to handle dअगरferences between 32- and 64-bit
 * addressing, big vs. little endian, etc.
 */
#अगर_घोषित __BIG_ENDIAN
#घोषणा TXX9_DMA_REG32(name)		u32 __pad_##name; u32 name
#अन्यथा
#घोषणा TXX9_DMA_REG32(name)		u32 name; u32 __pad_##name
#पूर्ण_अगर

/* Hardware रेजिस्टर definitions. */
काष्ठा txx9dmac_cregs अणु
#अगर defined(CONFIG_32BIT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
	TXX9_DMA_REG32(CHAR);	/* Chain Address Register */
#अन्यथा
	u64 CHAR;		/* Chain Address Register */
#पूर्ण_अगर
	u64 SAR;		/* Source Address Register */
	u64 DAR;		/* Destination Address Register */
	TXX9_DMA_REG32(CNTR);	/* Count Register */
	TXX9_DMA_REG32(SAIR);	/* Source Address Increment Register */
	TXX9_DMA_REG32(DAIR);	/* Destination Address Increment Register */
	TXX9_DMA_REG32(CCR);	/* Channel Control Register */
	TXX9_DMA_REG32(CSR);	/* Channel Status Register */
पूर्ण;
काष्ठा txx9dmac_cregs32 अणु
	u32 CHAR;
	u32 SAR;
	u32 DAR;
	u32 CNTR;
	u32 SAIR;
	u32 DAIR;
	u32 CCR;
	u32 CSR;
पूर्ण;

काष्ठा txx9dmac_regs अणु
	/* per-channel रेजिस्टरs */
	काष्ठा txx9dmac_cregs	CHAN[TXX9_DMA_MAX_NR_CHANNELS];
	u64	__pad[9];
	u64	MFDR;		/* Memory Fill Data Register */
	TXX9_DMA_REG32(MCR);	/* Master Control Register */
पूर्ण;
काष्ठा txx9dmac_regs32 अणु
	काष्ठा txx9dmac_cregs32	CHAN[TXX9_DMA_MAX_NR_CHANNELS];
	u32	__pad[9];
	u32	MFDR;
	u32	MCR;
पूर्ण;

/* bits क्रम MCR */
#घोषणा TXX9_DMA_MCR_EIS(ch)	(0x10000000<<(ch))
#घोषणा TXX9_DMA_MCR_DIS(ch)	(0x01000000<<(ch))
#घोषणा TXX9_DMA_MCR_RSFIF	0x00000080
#घोषणा TXX9_DMA_MCR_FIFUM(ch)	(0x00000008<<(ch))
#घोषणा TXX9_DMA_MCR_LE		0x00000004
#घोषणा TXX9_DMA_MCR_RPRT	0x00000002
#घोषणा TXX9_DMA_MCR_MSTEN	0x00000001

/* bits क्रम CCRn */
#घोषणा TXX9_DMA_CCR_IMMCHN	0x20000000
#घोषणा TXX9_DMA_CCR_USEXFSZ	0x10000000
#घोषणा TXX9_DMA_CCR_LE		0x08000000
#घोषणा TXX9_DMA_CCR_DBINH	0x04000000
#घोषणा TXX9_DMA_CCR_SBINH	0x02000000
#घोषणा TXX9_DMA_CCR_CHRST	0x01000000
#घोषणा TXX9_DMA_CCR_RVBYTE	0x00800000
#घोषणा TXX9_DMA_CCR_ACKPOL	0x00400000
#घोषणा TXX9_DMA_CCR_REQPL	0x00200000
#घोषणा TXX9_DMA_CCR_EGREQ	0x00100000
#घोषणा TXX9_DMA_CCR_CHDN	0x00080000
#घोषणा TXX9_DMA_CCR_DNCTL	0x00060000
#घोषणा TXX9_DMA_CCR_EXTRQ	0x00010000
#घोषणा TXX9_DMA_CCR_INTRQD	0x0000e000
#घोषणा TXX9_DMA_CCR_INTENE	0x00001000
#घोषणा TXX9_DMA_CCR_INTENC	0x00000800
#घोषणा TXX9_DMA_CCR_INTENT	0x00000400
#घोषणा TXX9_DMA_CCR_CHNEN	0x00000200
#घोषणा TXX9_DMA_CCR_XFACT	0x00000100
#घोषणा TXX9_DMA_CCR_SMPCHN	0x00000020
#घोषणा TXX9_DMA_CCR_XFSZ(order)	(((order) << 2) & 0x0000001c)
#घोषणा TXX9_DMA_CCR_XFSZ_1	TXX9_DMA_CCR_XFSZ(0)
#घोषणा TXX9_DMA_CCR_XFSZ_2	TXX9_DMA_CCR_XFSZ(1)
#घोषणा TXX9_DMA_CCR_XFSZ_4	TXX9_DMA_CCR_XFSZ(2)
#घोषणा TXX9_DMA_CCR_XFSZ_8	TXX9_DMA_CCR_XFSZ(3)
#घोषणा TXX9_DMA_CCR_XFSZ_X4	TXX9_DMA_CCR_XFSZ(4)
#घोषणा TXX9_DMA_CCR_XFSZ_X8	TXX9_DMA_CCR_XFSZ(5)
#घोषणा TXX9_DMA_CCR_XFSZ_X16	TXX9_DMA_CCR_XFSZ(6)
#घोषणा TXX9_DMA_CCR_XFSZ_X32	TXX9_DMA_CCR_XFSZ(7)
#घोषणा TXX9_DMA_CCR_MEMIO	0x00000002
#घोषणा TXX9_DMA_CCR_SNGAD	0x00000001

/* bits क्रम CSRn */
#घोषणा TXX9_DMA_CSR_CHNEN	0x00000400
#घोषणा TXX9_DMA_CSR_STLXFER	0x00000200
#घोषणा TXX9_DMA_CSR_XFACT	0x00000100
#घोषणा TXX9_DMA_CSR_ABCHC	0x00000080
#घोषणा TXX9_DMA_CSR_NCHNC	0x00000040
#घोषणा TXX9_DMA_CSR_NTRNFC	0x00000020
#घोषणा TXX9_DMA_CSR_EXTDN	0x00000010
#घोषणा TXX9_DMA_CSR_CFERR	0x00000008
#घोषणा TXX9_DMA_CSR_CHERR	0x00000004
#घोषणा TXX9_DMA_CSR_DESERR	0x00000002
#घोषणा TXX9_DMA_CSR_SORERR	0x00000001

काष्ठा txx9dmac_chan अणु
	काष्ठा dma_chan		chan;
	काष्ठा dma_device	dma;
	काष्ठा txx9dmac_dev	*ddev;
	व्योम __iomem		*ch_regs;
	काष्ठा tasklet_काष्ठा	tasklet;
	पूर्णांक			irq;
	u32			ccr;

	spinlock_t		lock;

	/* these other elements are all रक्षित by lock */
	काष्ठा list_head	active_list;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_list;

	अचिन्हित पूर्णांक		descs_allocated;
पूर्ण;

काष्ठा txx9dmac_dev अणु
	व्योम __iomem		*regs;
	काष्ठा tasklet_काष्ठा	tasklet;
	पूर्णांक			irq;
	काष्ठा txx9dmac_chan	*chan[TXX9_DMA_MAX_NR_CHANNELS];
	bool			have_64bit_regs;
	अचिन्हित पूर्णांक		descsize;
पूर्ण;

अटल अंतरभूत bool __is_dmac64(स्थिर काष्ठा txx9dmac_dev *ddev)
अणु
	वापस ddev->have_64bit_regs;
पूर्ण

अटल अंतरभूत bool is_dmac64(स्थिर काष्ठा txx9dmac_chan *dc)
अणु
	वापस __is_dmac64(dc->ddev);
पूर्ण

#अगर_घोषित TXX9_DMA_USE_SIMPLE_CHAIN
/* Hardware descriptor definition. (क्रम simple-chain) */
काष्ठा txx9dmac_hwdesc अणु
#अगर defined(CONFIG_32BIT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
	TXX9_DMA_REG32(CHAR);
#अन्यथा
	u64 CHAR;
#पूर्ण_अगर
	u64 SAR;
	u64 DAR;
	TXX9_DMA_REG32(CNTR);
पूर्ण;
काष्ठा txx9dmac_hwdesc32 अणु
	u32 CHAR;
	u32 SAR;
	u32 DAR;
	u32 CNTR;
पूर्ण;
#अन्यथा
#घोषणा txx9dmac_hwdesc txx9dmac_cregs
#घोषणा txx9dmac_hwdesc32 txx9dmac_cregs32
#पूर्ण_अगर

काष्ठा txx9dmac_desc अणु
	/* FIRST values the hardware uses */
	जोड़ अणु
		काष्ठा txx9dmac_hwdesc hwdesc;
		काष्ठा txx9dmac_hwdesc32 hwdesc32;
	पूर्ण;

	/* THEN values क्रम driver housekeeping */
	काष्ठा list_head		desc_node ____cacheline_aligned;
	काष्ठा list_head		tx_list;
	काष्ठा dma_async_tx_descriptor	txd;
	माप_प्रकार				len;
पूर्ण;

#अगर_घोषित TXX9_DMA_USE_SIMPLE_CHAIN

अटल अंतरभूत bool txx9dmac_chan_INTENT(काष्ठा txx9dmac_chan *dc)
अणु
	वापस (dc->ccr & TXX9_DMA_CCR_INTENT) != 0;
पूर्ण

अटल अंतरभूत व्योम txx9dmac_chan_set_INTENT(काष्ठा txx9dmac_chan *dc)
अणु
	dc->ccr |= TXX9_DMA_CCR_INTENT;
पूर्ण

अटल अंतरभूत व्योम txx9dmac_desc_set_INTENT(काष्ठा txx9dmac_dev *ddev,
					    काष्ठा txx9dmac_desc *desc)
अणु
पूर्ण

अटल अंतरभूत व्योम txx9dmac_chan_set_SMPCHN(काष्ठा txx9dmac_chan *dc)
अणु
	dc->ccr |= TXX9_DMA_CCR_SMPCHN;
पूर्ण

अटल अंतरभूत व्योम txx9dmac_desc_set_nosimple(काष्ठा txx9dmac_dev *ddev,
					      काष्ठा txx9dmac_desc *desc,
					      u32 sair, u32 dair, u32 ccr)
अणु
पूर्ण

#अन्यथा /* TXX9_DMA_USE_SIMPLE_CHAIN */

अटल अंतरभूत bool txx9dmac_chan_INTENT(काष्ठा txx9dmac_chan *dc)
अणु
	वापस true;
पूर्ण

अटल व्योम txx9dmac_chan_set_INTENT(काष्ठा txx9dmac_chan *dc)
अणु
पूर्ण

अटल अंतरभूत व्योम txx9dmac_desc_set_INTENT(काष्ठा txx9dmac_dev *ddev,
					    काष्ठा txx9dmac_desc *desc)
अणु
	अगर (__is_dmac64(ddev))
		desc->hwdesc.CCR |= TXX9_DMA_CCR_INTENT;
	अन्यथा
		desc->hwdesc32.CCR |= TXX9_DMA_CCR_INTENT;
पूर्ण

अटल अंतरभूत व्योम txx9dmac_chan_set_SMPCHN(काष्ठा txx9dmac_chan *dc)
अणु
पूर्ण

अटल अंतरभूत व्योम txx9dmac_desc_set_nosimple(काष्ठा txx9dmac_dev *ddev,
					      काष्ठा txx9dmac_desc *desc,
					      u32 sai, u32 dai, u32 ccr)
अणु
	अगर (__is_dmac64(ddev)) अणु
		desc->hwdesc.SAIR = sai;
		desc->hwdesc.DAIR = dai;
		desc->hwdesc.CCR = ccr;
	पूर्ण अन्यथा अणु
		desc->hwdesc32.SAIR = sai;
		desc->hwdesc32.DAIR = dai;
		desc->hwdesc32.CCR = ccr;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* TXX9_DMA_USE_SIMPLE_CHAIN */

#पूर्ण_अगर /* TXX9DMAC_H */
