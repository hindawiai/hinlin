<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header file क्रम the Aपंचांगel AHB DMA Controller driver
 *
 * Copyright (C) 2008 Aपंचांगel Corporation
 */
#अगर_अघोषित AT_HDMAC_REGS_H
#घोषणा	AT_HDMAC_REGS_H

#घोषणा	AT_DMA_MAX_NR_CHANNELS	8


#घोषणा	AT_DMA_GCFG	0x00	/* Global Configuration Register */
#घोषणा		AT_DMA_IF_BIGEND(i)	(0x1 << (i))	/* AHB-Lite Interface i in Big-endian mode */
#घोषणा		AT_DMA_ARB_CFG	(0x1 << 4)	/* Arbiter mode. */
#घोषणा			AT_DMA_ARB_CFG_FIXED		(0x0 << 4)
#घोषणा			AT_DMA_ARB_CFG_ROUND_ROBIN	(0x1 << 4)

#घोषणा	AT_DMA_EN	0x04	/* Controller Enable Register */
#घोषणा		AT_DMA_ENABLE	(0x1 << 0)

#घोषणा	AT_DMA_SREQ	0x08	/* Software Single Request Register */
#घोषणा		AT_DMA_SSREQ(x)	(0x1 << ((x) << 1))		/* Request a source single transfer on channel x */
#घोषणा		AT_DMA_DSREQ(x)	(0x1 << (1 + ((x) << 1)))	/* Request a destination single transfer on channel x */

#घोषणा	AT_DMA_CREQ	0x0C	/* Software Chunk Transfer Request Register */
#घोषणा		AT_DMA_SCREQ(x)	(0x1 << ((x) << 1))		/* Request a source chunk transfer on channel x */
#घोषणा		AT_DMA_DCREQ(x)	(0x1 << (1 + ((x) << 1)))	/* Request a destination chunk transfer on channel x */

#घोषणा	AT_DMA_LAST	0x10	/* Software Last Transfer Flag Register */
#घोषणा		AT_DMA_SLAST(x)	(0x1 << ((x) << 1))		/* This src rq is last tx of buffer on channel x */
#घोषणा		AT_DMA_DLAST(x)	(0x1 << (1 + ((x) << 1)))	/* This dst rq is last tx of buffer on channel x */

#घोषणा	AT_DMA_SYNC	0x14	/* Request Synchronization Register */
#घोषणा		AT_DMA_SYR(h)	(0x1 << (h))			/* Synchronize handshake line h */

/* Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt रेजिस्टरs */
#घोषणा	AT_DMA_EBCIER	0x18	/* Enable रेजिस्टर */
#घोषणा	AT_DMA_EBCIDR	0x1C	/* Disable रेजिस्टर */
#घोषणा	AT_DMA_EBCIMR	0x20	/* Mask Register */
#घोषणा	AT_DMA_EBCISR	0x24	/* Status Register */
#घोषणा		AT_DMA_CBTC_OFFSET	8
#घोषणा		AT_DMA_ERR_OFFSET	16
#घोषणा		AT_DMA_BTC(x)	(0x1 << (x))
#घोषणा		AT_DMA_CBTC(x)	(0x1 << (AT_DMA_CBTC_OFFSET + (x)))
#घोषणा		AT_DMA_ERR(x)	(0x1 << (AT_DMA_ERR_OFFSET + (x)))

#घोषणा	AT_DMA_CHER	0x28	/* Channel Handler Enable Register */
#घोषणा		AT_DMA_ENA(x)	(0x1 << (x))
#घोषणा		AT_DMA_SUSP(x)	(0x1 << ( 8 + (x)))
#घोषणा		AT_DMA_KEEP(x)	(0x1 << (24 + (x)))

#घोषणा	AT_DMA_CHDR	0x2C	/* Channel Handler Disable Register */
#घोषणा		AT_DMA_DIS(x)	(0x1 << (x))
#घोषणा		AT_DMA_RES(x)	(0x1 << ( 8 + (x)))

#घोषणा	AT_DMA_CHSR	0x30	/* Channel Handler Status Register */
#घोषणा		AT_DMA_EMPT(x)	(0x1 << (16 + (x)))
#घोषणा		AT_DMA_STAL(x)	(0x1 << (24 + (x)))


#घोषणा	AT_DMA_CH_REGS_BASE	0x3C	/* Channel रेजिस्टरs base address */
#घोषणा	ch_regs(x)	(AT_DMA_CH_REGS_BASE + (x) * 0x28) /* Channel x base addr */

/* Hardware रेजिस्टर offset क्रम each channel */
#घोषणा	ATC_SADDR_OFFSET	0x00	/* Source Address Register */
#घोषणा	ATC_DADDR_OFFSET	0x04	/* Destination Address Register */
#घोषणा	ATC_DSCR_OFFSET		0x08	/* Descriptor Address Register */
#घोषणा	ATC_CTRLA_OFFSET	0x0C	/* Control A Register */
#घोषणा	ATC_CTRLB_OFFSET	0x10	/* Control B Register */
#घोषणा	ATC_CFG_OFFSET		0x14	/* Configuration Register */
#घोषणा	ATC_SPIP_OFFSET		0x18	/* Src PIP Configuration Register */
#घोषणा	ATC_DPIP_OFFSET		0x1C	/* Dst PIP Configuration Register */


/* Bitfield definitions */

/* Bitfields in DSCR */
#घोषणा	ATC_DSCR_IF(i)		(0x3 & (i))	/* Dsc feched via AHB-Lite Interface i */

/* Bitfields in CTRLA */
#घोषणा	ATC_BTSIZE_MAX		0xFFFFUL	/* Maximum Buffer Transfer Size */
#घोषणा	ATC_BTSIZE(x)		(ATC_BTSIZE_MAX & (x)) /* Buffer Transfer Size */
#घोषणा	ATC_SCSIZE_MASK		(0x7 << 16)	/* Source Chunk Transfer Size */
#घोषणा		ATC_SCSIZE(x)		(ATC_SCSIZE_MASK & ((x) << 16))
#घोषणा		ATC_SCSIZE_1		(0x0 << 16)
#घोषणा		ATC_SCSIZE_4		(0x1 << 16)
#घोषणा		ATC_SCSIZE_8		(0x2 << 16)
#घोषणा		ATC_SCSIZE_16		(0x3 << 16)
#घोषणा		ATC_SCSIZE_32		(0x4 << 16)
#घोषणा		ATC_SCSIZE_64		(0x5 << 16)
#घोषणा		ATC_SCSIZE_128		(0x6 << 16)
#घोषणा		ATC_SCSIZE_256		(0x7 << 16)
#घोषणा	ATC_DCSIZE_MASK		(0x7 << 20)	/* Destination Chunk Transfer Size */
#घोषणा		ATC_DCSIZE(x)		(ATC_DCSIZE_MASK & ((x) << 20))
#घोषणा		ATC_DCSIZE_1		(0x0 << 20)
#घोषणा		ATC_DCSIZE_4		(0x1 << 20)
#घोषणा		ATC_DCSIZE_8		(0x2 << 20)
#घोषणा		ATC_DCSIZE_16		(0x3 << 20)
#घोषणा		ATC_DCSIZE_32		(0x4 << 20)
#घोषणा		ATC_DCSIZE_64		(0x5 << 20)
#घोषणा		ATC_DCSIZE_128		(0x6 << 20)
#घोषणा		ATC_DCSIZE_256		(0x7 << 20)
#घोषणा	ATC_SRC_WIDTH_MASK	(0x3 << 24)	/* Source Single Transfer Size */
#घोषणा		ATC_SRC_WIDTH(x)	((x) << 24)
#घोषणा		ATC_SRC_WIDTH_BYTE	(0x0 << 24)
#घोषणा		ATC_SRC_WIDTH_HALFWORD	(0x1 << 24)
#घोषणा		ATC_SRC_WIDTH_WORD	(0x2 << 24)
#घोषणा		ATC_REG_TO_SRC_WIDTH(r)	(((r) >> 24) & 0x3)
#घोषणा	ATC_DST_WIDTH_MASK	(0x3 << 28)	/* Destination Single Transfer Size */
#घोषणा		ATC_DST_WIDTH(x)	((x) << 28)
#घोषणा		ATC_DST_WIDTH_BYTE	(0x0 << 28)
#घोषणा		ATC_DST_WIDTH_HALFWORD	(0x1 << 28)
#घोषणा		ATC_DST_WIDTH_WORD	(0x2 << 28)
#घोषणा	ATC_DONE		(0x1 << 31)	/* Tx Done (only written back in descriptor) */

/* Bitfields in CTRLB */
#घोषणा	ATC_SIF(i)		(0x3 & (i))	/* Src tx करोne via AHB-Lite Interface i */
#घोषणा	ATC_DIF(i)		((0x3 & (i)) <<  4)	/* Dst tx करोne via AHB-Lite Interface i */
				  /* Specअगरy AHB पूर्णांकerfaces */
#घोषणा AT_DMA_MEM_IF		0 /* पूर्णांकerface 0 as memory पूर्णांकerface */
#घोषणा AT_DMA_PER_IF		1 /* पूर्णांकerface 1 as peripheral पूर्णांकerface */

#घोषणा	ATC_SRC_PIP		(0x1 <<  8)	/* Source Picture-in-Picture enabled */
#घोषणा	ATC_DST_PIP		(0x1 << 12)	/* Destination Picture-in-Picture enabled */
#घोषणा	ATC_SRC_DSCR_DIS	(0x1 << 16)	/* Src Descriptor fetch disable */
#घोषणा	ATC_DST_DSCR_DIS	(0x1 << 20)	/* Dst Descriptor fetch disable */
#घोषणा	ATC_FC_MASK		(0x7 << 21)	/* Choose Flow Controller */
#घोषणा		ATC_FC_MEM2MEM		(0x0 << 21)	/* Mem-to-Mem (DMA) */
#घोषणा		ATC_FC_MEM2PER		(0x1 << 21)	/* Mem-to-Periph (DMA) */
#घोषणा		ATC_FC_PER2MEM		(0x2 << 21)	/* Periph-to-Mem (DMA) */
#घोषणा		ATC_FC_PER2PER		(0x3 << 21)	/* Periph-to-Periph (DMA) */
#घोषणा		ATC_FC_PER2MEM_PER	(0x4 << 21)	/* Periph-to-Mem (Peripheral) */
#घोषणा		ATC_FC_MEM2PER_PER	(0x5 << 21)	/* Mem-to-Periph (Peripheral) */
#घोषणा		ATC_FC_PER2PER_SRCPER	(0x6 << 21)	/* Periph-to-Periph (Src Peripheral) */
#घोषणा		ATC_FC_PER2PER_DSTPER	(0x7 << 21)	/* Periph-to-Periph (Dst Peripheral) */
#घोषणा	ATC_SRC_ADDR_MODE_MASK	(0x3 << 24)
#घोषणा		ATC_SRC_ADDR_MODE_INCR	(0x0 << 24)	/* Incrementing Mode */
#घोषणा		ATC_SRC_ADDR_MODE_DECR	(0x1 << 24)	/* Decrementing Mode */
#घोषणा		ATC_SRC_ADDR_MODE_FIXED	(0x2 << 24)	/* Fixed Mode */
#घोषणा	ATC_DST_ADDR_MODE_MASK	(0x3 << 28)
#घोषणा		ATC_DST_ADDR_MODE_INCR	(0x0 << 28)	/* Incrementing Mode */
#घोषणा		ATC_DST_ADDR_MODE_DECR	(0x1 << 28)	/* Decrementing Mode */
#घोषणा		ATC_DST_ADDR_MODE_FIXED	(0x2 << 28)	/* Fixed Mode */
#घोषणा	ATC_IEN			(0x1 << 30)	/* BTC पूर्णांकerrupt enable (active low) */
#घोषणा	ATC_AUTO		(0x1 << 31)	/* Auto multiple buffer tx enable */

/* Bitfields in CFG */
#घोषणा ATC_PER_MSB(h)	((0x30U & (h)) >> 4)	/* Extract most signअगरicant bits of a handshaking identअगरier */

#घोषणा	ATC_SRC_PER(h)		(0xFU & (h))	/* Channel src rq associated with periph handshaking अगरc h */
#घोषणा	ATC_DST_PER(h)		((0xFU & (h)) <<  4)	/* Channel dst rq associated with periph handshaking अगरc h */
#घोषणा	ATC_SRC_REP		(0x1 <<  8)	/* Source Replay Mod */
#घोषणा	ATC_SRC_H2SEL		(0x1 <<  9)	/* Source Handshaking Mod */
#घोषणा		ATC_SRC_H2SEL_SW	(0x0 <<  9)
#घोषणा		ATC_SRC_H2SEL_HW	(0x1 <<  9)
#घोषणा	ATC_SRC_PER_MSB(h)	(ATC_PER_MSB(h) << 10)	/* Channel src rq (most signअगरicant bits) */
#घोषणा	ATC_DST_REP		(0x1 << 12)	/* Destination Replay Mod */
#घोषणा	ATC_DST_H2SEL		(0x1 << 13)	/* Destination Handshaking Mod */
#घोषणा		ATC_DST_H2SEL_SW	(0x0 << 13)
#घोषणा		ATC_DST_H2SEL_HW	(0x1 << 13)
#घोषणा	ATC_DST_PER_MSB(h)	(ATC_PER_MSB(h) << 14)	/* Channel dst rq (most signअगरicant bits) */
#घोषणा	ATC_SOD			(0x1 << 16)	/* Stop On Done */
#घोषणा	ATC_LOCK_IF		(0x1 << 20)	/* Interface Lock */
#घोषणा	ATC_LOCK_B		(0x1 << 21)	/* AHB Bus Lock */
#घोषणा	ATC_LOCK_IF_L		(0x1 << 22)	/* Master Interface Arbiter Lock */
#घोषणा		ATC_LOCK_IF_L_CHUNK	(0x0 << 22)
#घोषणा		ATC_LOCK_IF_L_BUFFER	(0x1 << 22)
#घोषणा	ATC_AHB_PROT_MASK	(0x7 << 24)	/* AHB Protection */
#घोषणा	ATC_FIFOCFG_MASK	(0x3 << 28)	/* FIFO Request Configuration */
#घोषणा		ATC_FIFOCFG_LARGESTBURST	(0x0 << 28)
#घोषणा		ATC_FIFOCFG_HALFFIFO		(0x1 << 28)
#घोषणा		ATC_FIFOCFG_ENOUGHSPACE		(0x2 << 28)

/* Bitfields in SPIP */
#घोषणा	ATC_SPIP_HOLE(x)	(0xFFFFU & (x))
#घोषणा	ATC_SPIP_BOUNDARY(x)	((0x3FF & (x)) << 16)

/* Bitfields in DPIP */
#घोषणा	ATC_DPIP_HOLE(x)	(0xFFFFU & (x))
#घोषणा	ATC_DPIP_BOUNDARY(x)	((0x3FF & (x)) << 16)


/*--  descriptors  -----------------------------------------------------*/

/* LLI == Linked List Item; aka DMA buffer descriptor */
काष्ठा at_lli अणु
	/* values that are not changed by hardware */
	dma_addr_t	saddr;
	dma_addr_t	daddr;
	/* value that may get written back: */
	u32		ctrla;
	/* more values that are not changed by hardware */
	u32		ctrlb;
	dma_addr_t	dscr;	/* chain to next lli */
पूर्ण;

/**
 * काष्ठा at_desc - software descriptor
 * @at_lli: hardware lli काष्ठाure
 * @txd: support क्रम the async_tx api
 * @desc_node: node on the channed descriptors list
 * @len: descriptor byte count
 * @total_len: total transaction byte count
 */
काष्ठा at_desc अणु
	/* FIRST values the hardware uses */
	काष्ठा at_lli			lli;

	/* THEN values क्रम driver housekeeping */
	काष्ठा list_head		tx_list;
	काष्ठा dma_async_tx_descriptor	txd;
	काष्ठा list_head		desc_node;
	माप_प्रकार				len;
	माप_प्रकार				total_len;

	/* Interleaved data */
	माप_प्रकार				boundary;
	माप_प्रकार				dst_hole;
	माप_प्रकार				src_hole;

	/* Memset temporary buffer */
	bool				स_रखो_buffer;
	dma_addr_t			स_रखो_paddr;
	पूर्णांक				*स_रखो_vaddr;
पूर्ण;

अटल अंतरभूत काष्ठा at_desc *
txd_to_at_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा at_desc, txd);
पूर्ण


/*--  Channels  --------------------------------------------------------*/

/**
 * atc_status - inक्रमmation bits stored in channel status flag
 *
 * Manipulated with atomic operations.
 */
क्रमागत atc_status अणु
	ATC_IS_ERROR = 0,
	ATC_IS_PAUSED = 1,
	ATC_IS_CYCLIC = 24,
पूर्ण;

/**
 * काष्ठा at_dma_chan - पूर्णांकernal representation of an Aपंचांगel HDMAC channel
 * @chan_common: common dmaengine channel object members
 * @device: parent device
 * @ch_regs: memory mapped रेजिस्टर base
 * @mask: channel index in a mask
 * @per_अगर: peripheral पूर्णांकerface
 * @mem_अगर: memory पूर्णांकerface
 * @status: transmit status inक्रमmation from irq/prep* functions
 *                to tasklet (use atomic operations)
 * @tasklet: bottom half to finish transaction work
 * @save_cfg: configuration रेजिस्टर that is saved on suspend/resume cycle
 * @save_dscr: क्रम cyclic operations, preserve next descriptor address in
 *             the cyclic list on suspend/resume cycle
 * @dma_sconfig: configuration क्रम slave transfers, passed via
 * .device_config
 * @lock: serializes enqueue/dequeue operations to descriptors lists
 * @active_list: list of descriptors dmaengine is being running on
 * @queue: list of descriptors पढ़ोy to be submitted to engine
 * @मुक्त_list: list of descriptors usable by the channel
 */
काष्ठा at_dma_chan अणु
	काष्ठा dma_chan		chan_common;
	काष्ठा at_dma		*device;
	व्योम __iomem		*ch_regs;
	u8			mask;
	u8			per_अगर;
	u8			mem_अगर;
	अचिन्हित दीर्घ		status;
	काष्ठा tasklet_काष्ठा	tasklet;
	u32			save_cfg;
	u32			save_dscr;
	काष्ठा dma_slave_config dma_sconfig;

	spinlock_t		lock;

	/* these other elements are all रक्षित by lock */
	काष्ठा list_head	active_list;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_list;
पूर्ण;

#घोषणा	channel_पढ़ोl(atchan, name) \
	__raw_पढ़ोl((atchan)->ch_regs + ATC_##name##_OFFSET)

#घोषणा	channel_ग_लिखोl(atchan, name, val) \
	__raw_ग_लिखोl((val), (atchan)->ch_regs + ATC_##name##_OFFSET)

अटल अंतरभूत काष्ठा at_dma_chan *to_at_dma_chan(काष्ठा dma_chan *dchan)
अणु
	वापस container_of(dchan, काष्ठा at_dma_chan, chan_common);
पूर्ण

/*
 * Fix sconfig's burst size according to at_hdmac. We need to convert them as:
 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3, 32 -> 4, 64 -> 5, 128 -> 6, 256 -> 7.
 *
 * This can be करोne by finding most signअगरicant bit set.
 */
अटल अंतरभूत व्योम convert_burst(u32 *maxburst)
अणु
	अगर (*maxburst > 1)
		*maxburst = fls(*maxburst) - 2;
	अन्यथा
		*maxburst = 0;
पूर्ण

/*
 * Fix sconfig's bus width according to at_hdmac.
 * 1 byte -> 0, 2 bytes -> 1, 4 bytes -> 2.
 */
अटल अंतरभूत u8 convert_buswidth(क्रमागत dma_slave_buswidth addr_width)
अणु
	चयन (addr_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		वापस 1;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		वापस 2;
	शेष:
		/* For 1 byte width or fallback */
		वापस 0;
	पूर्ण
पूर्ण

/*--  Controller  ------------------------------------------------------*/

/**
 * काष्ठा at_dma - पूर्णांकernal representation of an Aपंचांगel HDMA Controller
 * @chan_common: common dmaengine dma_device object members
 * @atdma_devtype: identअगरier of DMA controller compatibility
 * @ch_regs: memory mapped रेजिस्टर base
 * @clk: dma controller घड़ी
 * @save_imr: पूर्णांकerrupt mask रेजिस्टर that is saved on suspend/resume cycle
 * @all_chan_mask: all channels availlable in a mask
 * @dma_desc_pool: base of DMA descriptor region (DMA address)
 * @chan: channels table to store at_dma_chan काष्ठाures
 */
काष्ठा at_dma अणु
	काष्ठा dma_device	dma_common;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	u32			save_imr;

	u8			all_chan_mask;

	काष्ठा dma_pool		*dma_desc_pool;
	काष्ठा dma_pool		*स_रखो_pool;
	/* AT THE END channels table */
	काष्ठा at_dma_chan	chan[];
पूर्ण;

#घोषणा	dma_पढ़ोl(atdma, name) \
	__raw_पढ़ोl((atdma)->regs + AT_DMA_##name)
#घोषणा	dma_ग_लिखोl(atdma, name, val) \
	__raw_ग_लिखोl((val), (atdma)->regs + AT_DMA_##name)

अटल अंतरभूत काष्ठा at_dma *to_at_dma(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा at_dma, dma_common);
पूर्ण


/*--  Helper functions  ------------------------------------------------*/

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

#अगर defined(VERBOSE_DEBUG)
अटल व्योम vdbg_dump_regs(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_dma	*atdma = to_at_dma(atchan->chan_common.device);

	dev_err(chan2dev(&atchan->chan_common),
		"  channel %d : imr = 0x%x, chsr = 0x%x\n",
		atchan->chan_common.chan_id,
		dma_पढ़ोl(atdma, EBCIMR),
		dma_पढ़ोl(atdma, CHSR));

	dev_err(chan2dev(&atchan->chan_common),
		"  channel: s0x%x d0x%x ctrl0x%x:0x%x cfg0x%x l0x%x\n",
		channel_पढ़ोl(atchan, SADDR),
		channel_पढ़ोl(atchan, DADDR),
		channel_पढ़ोl(atchan, CTRLA),
		channel_पढ़ोl(atchan, CTRLB),
		channel_पढ़ोl(atchan, CFG),
		channel_पढ़ोl(atchan, DSCR));
पूर्ण
#अन्यथा
अटल व्योम vdbg_dump_regs(काष्ठा at_dma_chan *atchan) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम atc_dump_lli(काष्ठा at_dma_chan *atchan, काष्ठा at_lli *lli)
अणु
	dev_crit(chan2dev(&atchan->chan_common),
		 "desc: s%pad d%pad ctrl0x%x:0x%x l%pad\n",
		 &lli->saddr, &lli->daddr,
		 lli->ctrla, lli->ctrlb, &lli->dscr);
पूर्ण


अटल व्योम atc_setup_irq(काष्ठा at_dma *atdma, पूर्णांक chan_id, पूर्णांक on)
अणु
	u32 ebci;

	/* enable पूर्णांकerrupts on buffer transfer completion & error */
	ebci =    AT_DMA_BTC(chan_id)
		| AT_DMA_ERR(chan_id);
	अगर (on)
		dma_ग_लिखोl(atdma, EBCIER, ebci);
	अन्यथा
		dma_ग_लिखोl(atdma, EBCIDR, ebci);
पूर्ण

अटल व्योम atc_enable_chan_irq(काष्ठा at_dma *atdma, पूर्णांक chan_id)
अणु
	atc_setup_irq(atdma, chan_id, 1);
पूर्ण

अटल व्योम atc_disable_chan_irq(काष्ठा at_dma *atdma, पूर्णांक chan_id)
अणु
	atc_setup_irq(atdma, chan_id, 0);
पूर्ण


/**
 * atc_chan_is_enabled - test अगर given channel is enabled
 * @atchan: channel we want to test status
 */
अटल अंतरभूत पूर्णांक atc_chan_is_enabled(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_dma	*atdma = to_at_dma(atchan->chan_common.device);

	वापस !!(dma_पढ़ोl(atdma, CHSR) & atchan->mask);
पूर्ण

/**
 * atc_chan_is_छोड़ोd - test channel छोड़ो/resume status
 * @atchan: channel we want to test status
 */
अटल अंतरभूत पूर्णांक atc_chan_is_छोड़ोd(काष्ठा at_dma_chan *atchan)
अणु
	वापस test_bit(ATC_IS_PAUSED, &atchan->status);
पूर्ण

/**
 * atc_chan_is_cyclic - test अगर given channel has cyclic property set
 * @atchan: channel we want to test status
 */
अटल अंतरभूत पूर्णांक atc_chan_is_cyclic(काष्ठा at_dma_chan *atchan)
अणु
	वापस test_bit(ATC_IS_CYCLIC, &atchan->status);
पूर्ण

/**
 * set_desc_eol - set end-of-link to descriptor so it will end transfer
 * @desc: descriptor, signle or at the end of a chain, to end chain on
 */
अटल व्योम set_desc_eol(काष्ठा at_desc *desc)
अणु
	u32 ctrlb = desc->lli.ctrlb;

	ctrlb &= ~ATC_IEN;
	ctrlb |= ATC_SRC_DSCR_DIS | ATC_DST_DSCR_DIS;

	desc->lli.ctrlb = ctrlb;
	desc->lli.dscr = 0;
पूर्ण

#पूर्ण_अगर /* AT_HDMAC_REGS_H */
