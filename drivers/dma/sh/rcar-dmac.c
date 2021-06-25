<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car Gen2/Gen3 DMA Controller Driver
 *
 * Copyright (C) 2014-2019 Renesas Electronics Inc.
 *
 * Author: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../dmaengine.h"

/*
 * काष्ठा rcar_dmac_xfer_chunk - Descriptor क्रम a hardware transfer
 * @node: entry in the parent's chunks list
 * @src_addr: device source address
 * @dst_addr: device destination address
 * @size: transfer size in bytes
 */
काष्ठा rcar_dmac_xfer_chunk अणु
	काष्ठा list_head node;

	dma_addr_t src_addr;
	dma_addr_t dst_addr;
	u32 size;
पूर्ण;

/*
 * काष्ठा rcar_dmac_hw_desc - Hardware descriptor क्रम a transfer chunk
 * @sar: value of the SAR रेजिस्टर (source address)
 * @dar: value of the DAR रेजिस्टर (destination address)
 * @tcr: value of the TCR रेजिस्टर (transfer count)
 */
काष्ठा rcar_dmac_hw_desc अणु
	u32 sar;
	u32 dar;
	u32 tcr;
	u32 reserved;
पूर्ण __attribute__((__packed__));

/*
 * काष्ठा rcar_dmac_desc - R-Car Gen2 DMA Transfer Descriptor
 * @async_tx: base DMA asynchronous transaction descriptor
 * @direction: direction of the DMA transfer
 * @xfer_shअगरt: log2 of the transfer size
 * @chcr: value of the channel configuration रेजिस्टर क्रम this transfer
 * @node: entry in the channel's descriptors lists
 * @chunks: list of transfer chunks क्रम this transfer
 * @running: the transfer chunk being currently processed
 * @nchunks: number of transfer chunks क्रम this transfer
 * @hwdescs.use: whether the transfer descriptor uses hardware descriptors
 * @hwdescs.mem: hardware descriptors memory क्रम the transfer
 * @hwdescs.dma: device address of the hardware descriptors memory
 * @hwdescs.size: size of the hardware descriptors in bytes
 * @size: transfer size in bytes
 * @cyclic: when set indicates that the DMA transfer is cyclic
 */
काष्ठा rcar_dmac_desc अणु
	काष्ठा dma_async_tx_descriptor async_tx;
	क्रमागत dma_transfer_direction direction;
	अचिन्हित पूर्णांक xfer_shअगरt;
	u32 chcr;

	काष्ठा list_head node;
	काष्ठा list_head chunks;
	काष्ठा rcar_dmac_xfer_chunk *running;
	अचिन्हित पूर्णांक nchunks;

	काष्ठा अणु
		bool use;
		काष्ठा rcar_dmac_hw_desc *mem;
		dma_addr_t dma;
		माप_प्रकार size;
	पूर्ण hwdescs;

	अचिन्हित पूर्णांक size;
	bool cyclic;
पूर्ण;

#घोषणा to_rcar_dmac_desc(d)	container_of(d, काष्ठा rcar_dmac_desc, async_tx)

/*
 * काष्ठा rcar_dmac_desc_page - One page worth of descriptors
 * @node: entry in the channel's pages list
 * @descs: array of DMA descriptors
 * @chunks: array of transfer chunk descriptors
 */
काष्ठा rcar_dmac_desc_page अणु
	काष्ठा list_head node;

	जोड़ अणु
		काष्ठा rcar_dmac_desc descs[0];
		काष्ठा rcar_dmac_xfer_chunk chunks[0];
	पूर्ण;
पूर्ण;

#घोषणा RCAR_DMAC_DESCS_PER_PAGE					\
	((PAGE_SIZE - दुरत्व(काष्ठा rcar_dmac_desc_page, descs)) /	\
	माप(काष्ठा rcar_dmac_desc))
#घोषणा RCAR_DMAC_XFER_CHUNKS_PER_PAGE					\
	((PAGE_SIZE - दुरत्व(काष्ठा rcar_dmac_desc_page, chunks)) /	\
	माप(काष्ठा rcar_dmac_xfer_chunk))

/*
 * काष्ठा rcar_dmac_chan_slave - Slave configuration
 * @slave_addr: slave memory address
 * @xfer_size: size (in bytes) of hardware transfers
 */
काष्ठा rcar_dmac_chan_slave अणु
	phys_addr_t slave_addr;
	अचिन्हित पूर्णांक xfer_size;
पूर्ण;

/*
 * काष्ठा rcar_dmac_chan_map - Map of slave device phys to dma address
 * @addr: slave dma address
 * @dir: direction of mapping
 * @slave: slave configuration that is mapped
 */
काष्ठा rcar_dmac_chan_map अणु
	dma_addr_t addr;
	क्रमागत dma_data_direction dir;
	काष्ठा rcar_dmac_chan_slave slave;
पूर्ण;

/*
 * काष्ठा rcar_dmac_chan - R-Car Gen2 DMA Controller Channel
 * @chan: base DMA channel object
 * @iomem: channel I/O memory base
 * @index: index of this channel in the controller
 * @irq: channel IRQ
 * @src: slave memory address and size on the source side
 * @dst: slave memory address and size on the destination side
 * @mid_rid: hardware MID/RID क्रम the DMA client using this channel
 * @lock: protects the channel CHCR रेजिस्टर and the desc members
 * @desc.मुक्त: list of मुक्त descriptors
 * @desc.pending: list of pending descriptors (submitted with tx_submit)
 * @desc.active: list of active descriptors (activated with issue_pending)
 * @desc.करोne: list of completed descriptors
 * @desc.रुको: list of descriptors रुकोing क्रम an ack
 * @desc.running: the descriptor being processed (a member of the active list)
 * @desc.chunks_मुक्त: list of मुक्त transfer chunk descriptors
 * @desc.pages: list of pages used by allocated descriptors
 */
काष्ठा rcar_dmac_chan अणु
	काष्ठा dma_chan chan;
	व्योम __iomem *iomem;
	अचिन्हित पूर्णांक index;
	पूर्णांक irq;

	काष्ठा rcar_dmac_chan_slave src;
	काष्ठा rcar_dmac_chan_slave dst;
	काष्ठा rcar_dmac_chan_map map;
	पूर्णांक mid_rid;

	spinlock_t lock;

	काष्ठा अणु
		काष्ठा list_head मुक्त;
		काष्ठा list_head pending;
		काष्ठा list_head active;
		काष्ठा list_head करोne;
		काष्ठा list_head रुको;
		काष्ठा rcar_dmac_desc *running;

		काष्ठा list_head chunks_मुक्त;

		काष्ठा list_head pages;
	पूर्ण desc;
पूर्ण;

#घोषणा to_rcar_dmac_chan(c)	container_of(c, काष्ठा rcar_dmac_chan, chan)

/*
 * काष्ठा rcar_dmac - R-Car Gen2 DMA Controller
 * @engine: base DMA engine object
 * @dev: the hardware device
 * @dmac_base: remapped base रेजिस्टर block
 * @chan_base: remapped channel रेजिस्टर block (optional)
 * @n_channels: number of available channels
 * @channels: array of DMAC channels
 * @channels_mask: bitfield of which DMA channels are managed by this driver
 * @modules: biपंचांगask of client modules in use
 */
काष्ठा rcar_dmac अणु
	काष्ठा dma_device engine;
	काष्ठा device *dev;
	व्योम __iomem *dmac_base;
	व्योम __iomem *chan_base;

	अचिन्हित पूर्णांक n_channels;
	काष्ठा rcar_dmac_chan *channels;
	u32 channels_mask;

	DECLARE_BITMAP(modules, 256);
पूर्ण;

#घोषणा to_rcar_dmac(d)		container_of(d, काष्ठा rcar_dmac, engine)

#घोषणा क्रम_each_rcar_dmac_chan(i, dmac, chan)						\
	क्रम (i = 0, chan = &(dmac)->channels[0]; i < (dmac)->n_channels; i++, chan++)	\
		अगर (!((dmac)->channels_mask & BIT(i))) जारी; अन्यथा

/*
 * काष्ठा rcar_dmac_of_data - This driver's OF data
 * @chan_offset_base: DMAC channels base offset
 * @chan_offset_stride: DMAC channels offset stride
 */
काष्ठा rcar_dmac_of_data अणु
	u32 chan_offset_base;
	u32 chan_offset_stride;
पूर्ण;

/* -----------------------------------------------------------------------------
 * Registers
 */

#घोषणा RCAR_DMAISTA			0x0020
#घोषणा RCAR_DMASEC			0x0030
#घोषणा RCAR_DMAOR			0x0060
#घोषणा RCAR_DMAOR_PRI_FIXED		(0 << 8)
#घोषणा RCAR_DMAOR_PRI_ROUND_ROBIN	(3 << 8)
#घोषणा RCAR_DMAOR_AE			(1 << 2)
#घोषणा RCAR_DMAOR_DME			(1 << 0)
#घोषणा RCAR_DMACHCLR			0x0080	/* Not on R-Car V3U */
#घोषणा RCAR_DMADPSEC			0x00a0

#घोषणा RCAR_DMASAR			0x0000
#घोषणा RCAR_DMADAR			0x0004
#घोषणा RCAR_DMATCR			0x0008
#घोषणा RCAR_DMATCR_MASK		0x00ffffff
#घोषणा RCAR_DMATSR			0x0028
#घोषणा RCAR_DMACHCR			0x000c
#घोषणा RCAR_DMACHCR_CAE		(1 << 31)
#घोषणा RCAR_DMACHCR_CAIE		(1 << 30)
#घोषणा RCAR_DMACHCR_DPM_DISABLED	(0 << 28)
#घोषणा RCAR_DMACHCR_DPM_ENABLED	(1 << 28)
#घोषणा RCAR_DMACHCR_DPM_REPEAT		(2 << 28)
#घोषणा RCAR_DMACHCR_DPM_INFINITE	(3 << 28)
#घोषणा RCAR_DMACHCR_RPT_SAR		(1 << 27)
#घोषणा RCAR_DMACHCR_RPT_DAR		(1 << 26)
#घोषणा RCAR_DMACHCR_RPT_TCR		(1 << 25)
#घोषणा RCAR_DMACHCR_DPB		(1 << 22)
#घोषणा RCAR_DMACHCR_DSE		(1 << 19)
#घोषणा RCAR_DMACHCR_DSIE		(1 << 18)
#घोषणा RCAR_DMACHCR_TS_1B		((0 << 20) | (0 << 3))
#घोषणा RCAR_DMACHCR_TS_2B		((0 << 20) | (1 << 3))
#घोषणा RCAR_DMACHCR_TS_4B		((0 << 20) | (2 << 3))
#घोषणा RCAR_DMACHCR_TS_16B		((0 << 20) | (3 << 3))
#घोषणा RCAR_DMACHCR_TS_32B		((1 << 20) | (0 << 3))
#घोषणा RCAR_DMACHCR_TS_64B		((1 << 20) | (1 << 3))
#घोषणा RCAR_DMACHCR_TS_8B		((1 << 20) | (3 << 3))
#घोषणा RCAR_DMACHCR_DM_FIXED		(0 << 14)
#घोषणा RCAR_DMACHCR_DM_INC		(1 << 14)
#घोषणा RCAR_DMACHCR_DM_DEC		(2 << 14)
#घोषणा RCAR_DMACHCR_SM_FIXED		(0 << 12)
#घोषणा RCAR_DMACHCR_SM_INC		(1 << 12)
#घोषणा RCAR_DMACHCR_SM_DEC		(2 << 12)
#घोषणा RCAR_DMACHCR_RS_AUTO		(4 << 8)
#घोषणा RCAR_DMACHCR_RS_DMARS		(8 << 8)
#घोषणा RCAR_DMACHCR_IE			(1 << 2)
#घोषणा RCAR_DMACHCR_TE			(1 << 1)
#घोषणा RCAR_DMACHCR_DE			(1 << 0)
#घोषणा RCAR_DMATCRB			0x0018
#घोषणा RCAR_DMATSRB			0x0038
#घोषणा RCAR_DMACHCRB			0x001c
#घोषणा RCAR_DMACHCRB_DCNT(n)		((n) << 24)
#घोषणा RCAR_DMACHCRB_DPTR_MASK		(0xff << 16)
#घोषणा RCAR_DMACHCRB_DPTR_SHIFT	16
#घोषणा RCAR_DMACHCRB_DRST		(1 << 15)
#घोषणा RCAR_DMACHCRB_DTS		(1 << 8)
#घोषणा RCAR_DMACHCRB_SLM_NORMAL	(0 << 4)
#घोषणा RCAR_DMACHCRB_SLM_CLK(n)	((8 | (n)) << 4)
#घोषणा RCAR_DMACHCRB_PRI(n)		((n) << 0)
#घोषणा RCAR_DMARS			0x0040
#घोषणा RCAR_DMABUFCR			0x0048
#घोषणा RCAR_DMABUFCR_MBU(n)		((n) << 16)
#घोषणा RCAR_DMABUFCR_ULB(n)		((n) << 0)
#घोषणा RCAR_DMADPBASE			0x0050
#घोषणा RCAR_DMADPBASE_MASK		0xfffffff0
#घोषणा RCAR_DMADPBASE_SEL		(1 << 0)
#घोषणा RCAR_DMADPCR			0x0054
#घोषणा RCAR_DMADPCR_DIPT(n)		((n) << 24)
#घोषणा RCAR_DMAFIXSAR			0x0010
#घोषणा RCAR_DMAFIXDAR			0x0014
#घोषणा RCAR_DMAFIXDPBASE		0x0060

/* For R-Car V3U */
#घोषणा RCAR_V3U_DMACHCLR		0x0100

/* Hardcode the MEMCPY transfer size to 4 bytes. */
#घोषणा RCAR_DMAC_MEMCPY_XFER_SIZE	4

/* -----------------------------------------------------------------------------
 * Device access
 */

अटल व्योम rcar_dmac_ग_लिखो(काष्ठा rcar_dmac *dmac, u32 reg, u32 data)
अणु
	अगर (reg == RCAR_DMAOR)
		ग_लिखोw(data, dmac->dmac_base + reg);
	अन्यथा
		ग_लिखोl(data, dmac->dmac_base + reg);
पूर्ण

अटल u32 rcar_dmac_पढ़ो(काष्ठा rcar_dmac *dmac, u32 reg)
अणु
	अगर (reg == RCAR_DMAOR)
		वापस पढ़ोw(dmac->dmac_base + reg);
	अन्यथा
		वापस पढ़ोl(dmac->dmac_base + reg);
पूर्ण

अटल u32 rcar_dmac_chan_पढ़ो(काष्ठा rcar_dmac_chan *chan, u32 reg)
अणु
	अगर (reg == RCAR_DMARS)
		वापस पढ़ोw(chan->iomem + reg);
	अन्यथा
		वापस पढ़ोl(chan->iomem + reg);
पूर्ण

अटल व्योम rcar_dmac_chan_ग_लिखो(काष्ठा rcar_dmac_chan *chan, u32 reg, u32 data)
अणु
	अगर (reg == RCAR_DMARS)
		ग_लिखोw(data, chan->iomem + reg);
	अन्यथा
		ग_लिखोl(data, chan->iomem + reg);
पूर्ण

अटल व्योम rcar_dmac_chan_clear(काष्ठा rcar_dmac *dmac,
				 काष्ठा rcar_dmac_chan *chan)
अणु
	अगर (dmac->chan_base)
		rcar_dmac_chan_ग_लिखो(chan, RCAR_V3U_DMACHCLR, 1);
	अन्यथा
		rcar_dmac_ग_लिखो(dmac, RCAR_DMACHCLR, BIT(chan->index));
पूर्ण

अटल व्योम rcar_dmac_chan_clear_all(काष्ठा rcar_dmac *dmac)
अणु
	काष्ठा rcar_dmac_chan *chan;
	अचिन्हित पूर्णांक i;

	अगर (dmac->chan_base) अणु
		क्रम_each_rcar_dmac_chan(i, dmac, chan)
			rcar_dmac_chan_ग_लिखो(chan, RCAR_V3U_DMACHCLR, 1);
	पूर्ण अन्यथा अणु
		rcar_dmac_ग_लिखो(dmac, RCAR_DMACHCLR, dmac->channels_mask);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization and configuration
 */

अटल bool rcar_dmac_chan_is_busy(काष्ठा rcar_dmac_chan *chan)
अणु
	u32 chcr = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCR);

	वापस !!(chcr & (RCAR_DMACHCR_DE | RCAR_DMACHCR_TE));
पूर्ण

अटल व्योम rcar_dmac_chan_start_xfer(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc = chan->desc.running;
	u32 chcr = desc->chcr;

	WARN_ON_ONCE(rcar_dmac_chan_is_busy(chan));

	अगर (chan->mid_rid >= 0)
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMARS, chan->mid_rid);

	अगर (desc->hwdescs.use) अणु
		काष्ठा rcar_dmac_xfer_chunk *chunk =
			list_first_entry(&desc->chunks,
					 काष्ठा rcar_dmac_xfer_chunk, node);

		dev_dbg(chan->chan.device->dev,
			"chan%u: queue desc %p: %u@%pad\n",
			chan->index, desc, desc->nchunks, &desc->hwdescs.dma);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMAFIXSAR,
				     chunk->src_addr >> 32);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMAFIXDAR,
				     chunk->dst_addr >> 32);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMAFIXDPBASE,
				     desc->hwdescs.dma >> 32);
#पूर्ण_अगर
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMADPBASE,
				     (desc->hwdescs.dma & 0xfffffff0) |
				     RCAR_DMADPBASE_SEL);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMACHCRB,
				     RCAR_DMACHCRB_DCNT(desc->nchunks - 1) |
				     RCAR_DMACHCRB_DRST);

		/*
		 * Errata: When descriptor memory is accessed through an IOMMU
		 * the DMADAR रेजिस्टर isn't initialized स्वतःmatically from the
		 * first descriptor at beginning of transfer by the DMAC like it
		 * should. Initialize it manually with the destination address
		 * of the first chunk.
		 */
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMADAR,
				     chunk->dst_addr & 0xffffffff);

		/*
		 * Program the descriptor stage पूर्णांकerrupt to occur after the end
		 * of the first stage.
		 */
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMADPCR, RCAR_DMADPCR_DIPT(1));

		chcr |= RCAR_DMACHCR_RPT_SAR | RCAR_DMACHCR_RPT_DAR
		     |  RCAR_DMACHCR_RPT_TCR | RCAR_DMACHCR_DPB;

		/*
		 * If the descriptor isn't cyclic enable normal descriptor mode
		 * and the transfer completion पूर्णांकerrupt.
		 */
		अगर (!desc->cyclic)
			chcr |= RCAR_DMACHCR_DPM_ENABLED | RCAR_DMACHCR_IE;
		/*
		 * If the descriptor is cyclic and has a callback enable the
		 * descriptor stage पूर्णांकerrupt in infinite repeat mode.
		 */
		अन्यथा अगर (desc->async_tx.callback)
			chcr |= RCAR_DMACHCR_DPM_INFINITE | RCAR_DMACHCR_DSIE;
		/*
		 * Otherwise just select infinite repeat mode without any
		 * पूर्णांकerrupt.
		 */
		अन्यथा
			chcr |= RCAR_DMACHCR_DPM_INFINITE;
	पूर्ण अन्यथा अणु
		काष्ठा rcar_dmac_xfer_chunk *chunk = desc->running;

		dev_dbg(chan->chan.device->dev,
			"chan%u: queue chunk %p: %u@%pad -> %pad\n",
			chan->index, chunk, chunk->size, &chunk->src_addr,
			&chunk->dst_addr);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMAFIXSAR,
				     chunk->src_addr >> 32);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMAFIXDAR,
				     chunk->dst_addr >> 32);
#पूर्ण_अगर
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMASAR,
				     chunk->src_addr & 0xffffffff);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMADAR,
				     chunk->dst_addr & 0xffffffff);
		rcar_dmac_chan_ग_लिखो(chan, RCAR_DMATCR,
				     chunk->size >> desc->xfer_shअगरt);

		chcr |= RCAR_DMACHCR_DPM_DISABLED | RCAR_DMACHCR_IE;
	पूर्ण

	rcar_dmac_chan_ग_लिखो(chan, RCAR_DMACHCR,
			     chcr | RCAR_DMACHCR_DE | RCAR_DMACHCR_CAIE);
पूर्ण

अटल पूर्णांक rcar_dmac_init(काष्ठा rcar_dmac *dmac)
अणु
	u16 dmaor;

	/* Clear all channels and enable the DMAC globally. */
	rcar_dmac_chan_clear_all(dmac);
	rcar_dmac_ग_लिखो(dmac, RCAR_DMAOR,
			RCAR_DMAOR_PRI_FIXED | RCAR_DMAOR_DME);

	dmaor = rcar_dmac_पढ़ो(dmac, RCAR_DMAOR);
	अगर ((dmaor & (RCAR_DMAOR_AE | RCAR_DMAOR_DME)) != RCAR_DMAOR_DME) अणु
		dev_warn(dmac->dev, "DMAOR initialization failed.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptors submission
 */

अटल dma_cookie_t rcar_dmac_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा rcar_dmac_chan *chan = to_rcar_dmac_chan(tx->chan);
	काष्ठा rcar_dmac_desc *desc = to_rcar_dmac_desc(tx);
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&chan->lock, flags);

	cookie = dma_cookie_assign(tx);

	dev_dbg(chan->chan.device->dev, "chan%u: submit #%d@%p\n",
		chan->index, tx->cookie, desc);

	list_add_tail(&desc->node, &chan->desc.pending);
	desc->running = list_first_entry(&desc->chunks,
					 काष्ठा rcar_dmac_xfer_chunk, node);

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस cookie;
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptors allocation and मुक्त
 */

/*
 * rcar_dmac_desc_alloc - Allocate a page worth of DMA descriptors
 * @chan: the DMA channel
 * @gfp: allocation flags
 */
अटल पूर्णांक rcar_dmac_desc_alloc(काष्ठा rcar_dmac_chan *chan, gfp_t gfp)
अणु
	काष्ठा rcar_dmac_desc_page *page;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);
	अचिन्हित पूर्णांक i;

	page = (व्योम *)get_zeroed_page(gfp);
	अगर (!page)
		वापस -ENOMEM;

	क्रम (i = 0; i < RCAR_DMAC_DESCS_PER_PAGE; ++i) अणु
		काष्ठा rcar_dmac_desc *desc = &page->descs[i];

		dma_async_tx_descriptor_init(&desc->async_tx, &chan->chan);
		desc->async_tx.tx_submit = rcar_dmac_tx_submit;
		INIT_LIST_HEAD(&desc->chunks);

		list_add_tail(&desc->node, &list);
	पूर्ण

	spin_lock_irqsave(&chan->lock, flags);
	list_splice_tail(&list, &chan->desc.मुक्त);
	list_add_tail(&page->node, &chan->desc.pages);
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

/*
 * rcar_dmac_desc_put - Release a DMA transfer descriptor
 * @chan: the DMA channel
 * @desc: the descriptor
 *
 * Put the descriptor and its transfer chunk descriptors back in the channel's
 * मुक्त descriptors lists. The descriptor's chunks list will be reinitialized to
 * an empty list as a result.
 *
 * The descriptor must have been हटाओd from the channel's lists beक्रमe calling
 * this function.
 */
अटल व्योम rcar_dmac_desc_put(काष्ठा rcar_dmac_chan *chan,
			       काष्ठा rcar_dmac_desc *desc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	list_splice_tail_init(&desc->chunks, &chan->desc.chunks_मुक्त);
	list_add(&desc->node, &chan->desc.मुक्त);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल व्योम rcar_dmac_desc_recycle_acked(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	/*
	 * We have to temporarily move all descriptors from the रुको list to a
	 * local list as iterating over the रुको list, even with
	 * list_क्रम_each_entry_safe, isn't safe अगर we release the channel lock
	 * around the rcar_dmac_desc_put() call.
	 */
	spin_lock_irqsave(&chan->lock, flags);
	list_splice_init(&chan->desc.रुको, &list);
	spin_unlock_irqrestore(&chan->lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &list, node) अणु
		अगर (async_tx_test_ack(&desc->async_tx)) अणु
			list_del(&desc->node);
			rcar_dmac_desc_put(chan, desc);
		पूर्ण
	पूर्ण

	अगर (list_empty(&list))
		वापस;

	/* Put the reमुख्यing descriptors back in the रुको list. */
	spin_lock_irqsave(&chan->lock, flags);
	list_splice(&list, &chan->desc.रुको);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/*
 * rcar_dmac_desc_get - Allocate a descriptor क्रम a DMA transfer
 * @chan: the DMA channel
 *
 * Locking: This function must be called in a non-atomic context.
 *
 * Return: A poपूर्णांकer to the allocated descriptor or शून्य अगर no descriptor can
 * be allocated.
 */
अटल काष्ठा rcar_dmac_desc *rcar_dmac_desc_get(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Recycle acked descriptors beक्रमe attempting allocation. */
	rcar_dmac_desc_recycle_acked(chan);

	spin_lock_irqsave(&chan->lock, flags);

	जबतक (list_empty(&chan->desc.मुक्त)) अणु
		/*
		 * No मुक्त descriptors, allocate a page worth of them and try
		 * again, as someone अन्यथा could race us to get the newly
		 * allocated descriptors. If the allocation fails वापस an
		 * error.
		 */
		spin_unlock_irqrestore(&chan->lock, flags);
		ret = rcar_dmac_desc_alloc(chan, GFP_NOWAIT);
		अगर (ret < 0)
			वापस शून्य;
		spin_lock_irqsave(&chan->lock, flags);
	पूर्ण

	desc = list_first_entry(&chan->desc.मुक्त, काष्ठा rcar_dmac_desc, node);
	list_del(&desc->node);

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस desc;
पूर्ण

/*
 * rcar_dmac_xfer_chunk_alloc - Allocate a page worth of transfer chunks
 * @chan: the DMA channel
 * @gfp: allocation flags
 */
अटल पूर्णांक rcar_dmac_xfer_chunk_alloc(काष्ठा rcar_dmac_chan *chan, gfp_t gfp)
अणु
	काष्ठा rcar_dmac_desc_page *page;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);
	अचिन्हित पूर्णांक i;

	page = (व्योम *)get_zeroed_page(gfp);
	अगर (!page)
		वापस -ENOMEM;

	क्रम (i = 0; i < RCAR_DMAC_XFER_CHUNKS_PER_PAGE; ++i) अणु
		काष्ठा rcar_dmac_xfer_chunk *chunk = &page->chunks[i];

		list_add_tail(&chunk->node, &list);
	पूर्ण

	spin_lock_irqsave(&chan->lock, flags);
	list_splice_tail(&list, &chan->desc.chunks_मुक्त);
	list_add_tail(&page->node, &chan->desc.pages);
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

/*
 * rcar_dmac_xfer_chunk_get - Allocate a transfer chunk क्रम a DMA transfer
 * @chan: the DMA channel
 *
 * Locking: This function must be called in a non-atomic context.
 *
 * Return: A poपूर्णांकer to the allocated transfer chunk descriptor or शून्य अगर no
 * descriptor can be allocated.
 */
अटल काष्ठा rcar_dmac_xfer_chunk *
rcar_dmac_xfer_chunk_get(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_xfer_chunk *chunk;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&chan->lock, flags);

	जबतक (list_empty(&chan->desc.chunks_मुक्त)) अणु
		/*
		 * No मुक्त descriptors, allocate a page worth of them and try
		 * again, as someone अन्यथा could race us to get the newly
		 * allocated descriptors. If the allocation fails वापस an
		 * error.
		 */
		spin_unlock_irqrestore(&chan->lock, flags);
		ret = rcar_dmac_xfer_chunk_alloc(chan, GFP_NOWAIT);
		अगर (ret < 0)
			वापस शून्य;
		spin_lock_irqsave(&chan->lock, flags);
	पूर्ण

	chunk = list_first_entry(&chan->desc.chunks_मुक्त,
				 काष्ठा rcar_dmac_xfer_chunk, node);
	list_del(&chunk->node);

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस chunk;
पूर्ण

अटल व्योम rcar_dmac_पुनः_स्मृति_hwdesc(काष्ठा rcar_dmac_chan *chan,
				     काष्ठा rcar_dmac_desc *desc, माप_प्रकार size)
अणु
	/*
	 * dma_alloc_coherent() allocates memory in page size increments. To
	 * aव्योम पुनः_स्मृतिating the hardware descriptors when the allocated size
	 * wouldn't change align the requested size to a multiple of the page
	 * size.
	 */
	size = PAGE_ALIGN(size);

	अगर (desc->hwdescs.size == size)
		वापस;

	अगर (desc->hwdescs.mem) अणु
		dma_मुक्त_coherent(chan->chan.device->dev, desc->hwdescs.size,
				  desc->hwdescs.mem, desc->hwdescs.dma);
		desc->hwdescs.mem = शून्य;
		desc->hwdescs.size = 0;
	पूर्ण

	अगर (!size)
		वापस;

	desc->hwdescs.mem = dma_alloc_coherent(chan->chan.device->dev, size,
					       &desc->hwdescs.dma, GFP_NOWAIT);
	अगर (!desc->hwdescs.mem)
		वापस;

	desc->hwdescs.size = size;
पूर्ण

अटल पूर्णांक rcar_dmac_fill_hwdesc(काष्ठा rcar_dmac_chan *chan,
				 काष्ठा rcar_dmac_desc *desc)
अणु
	काष्ठा rcar_dmac_xfer_chunk *chunk;
	काष्ठा rcar_dmac_hw_desc *hwdesc;

	rcar_dmac_पुनः_स्मृति_hwdesc(chan, desc, desc->nchunks * माप(*hwdesc));

	hwdesc = desc->hwdescs.mem;
	अगर (!hwdesc)
		वापस -ENOMEM;

	list_क्रम_each_entry(chunk, &desc->chunks, node) अणु
		hwdesc->sar = chunk->src_addr;
		hwdesc->dar = chunk->dst_addr;
		hwdesc->tcr = chunk->size >> desc->xfer_shअगरt;
		hwdesc++;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Stop and reset
 */
अटल व्योम rcar_dmac_chcr_de_barrier(काष्ठा rcar_dmac_chan *chan)
अणु
	u32 chcr;
	अचिन्हित पूर्णांक i;

	/*
	 * Ensure that the setting of the DE bit is actually 0 after
	 * clearing it.
	 */
	क्रम (i = 0; i < 1024; i++) अणु
		chcr = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCR);
		अगर (!(chcr & RCAR_DMACHCR_DE))
			वापस;
		udelay(1);
	पूर्ण

	dev_err(chan->chan.device->dev, "CHCR DE check error\n");
पूर्ण

अटल व्योम rcar_dmac_clear_chcr_de(काष्ठा rcar_dmac_chan *chan)
अणु
	u32 chcr = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCR);

	/* set DE=0 and flush reमुख्यing data */
	rcar_dmac_chan_ग_लिखो(chan, RCAR_DMACHCR, (chcr & ~RCAR_DMACHCR_DE));

	/* make sure all reमुख्यing data was flushed */
	rcar_dmac_chcr_de_barrier(chan);
पूर्ण

अटल व्योम rcar_dmac_chan_halt(काष्ठा rcar_dmac_chan *chan)
अणु
	u32 chcr = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCR);

	chcr &= ~(RCAR_DMACHCR_DSE | RCAR_DMACHCR_DSIE | RCAR_DMACHCR_IE |
		  RCAR_DMACHCR_TE | RCAR_DMACHCR_DE |
		  RCAR_DMACHCR_CAE | RCAR_DMACHCR_CAIE);
	rcar_dmac_chan_ग_लिखो(chan, RCAR_DMACHCR, chcr);
	rcar_dmac_chcr_de_barrier(chan);
पूर्ण

अटल व्योम rcar_dmac_chan_reinit(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(descs);

	spin_lock_irqsave(&chan->lock, flags);

	/* Move all non-मुक्त descriptors to the local lists. */
	list_splice_init(&chan->desc.pending, &descs);
	list_splice_init(&chan->desc.active, &descs);
	list_splice_init(&chan->desc.करोne, &descs);
	list_splice_init(&chan->desc.रुको, &descs);

	chan->desc.running = शून्य;

	spin_unlock_irqrestore(&chan->lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &descs, node) अणु
		list_del(&desc->node);
		rcar_dmac_desc_put(chan, desc);
	पूर्ण
पूर्ण

अटल व्योम rcar_dmac_stop_all_chan(काष्ठा rcar_dmac *dmac)
अणु
	काष्ठा rcar_dmac_chan *chan;
	अचिन्हित पूर्णांक i;

	/* Stop all channels. */
	क्रम_each_rcar_dmac_chan(i, dmac, chan) अणु
		/* Stop and reinitialize the channel. */
		spin_lock_irq(&chan->lock);
		rcar_dmac_chan_halt(chan);
		spin_unlock_irq(&chan->lock);
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_dmac_chan_छोड़ो(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	spin_lock_irqsave(&rchan->lock, flags);
	rcar_dmac_clear_chcr_de(rchan);
	spin_unlock_irqrestore(&rchan->lock, flags);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptors preparation
 */

अटल व्योम rcar_dmac_chan_configure_desc(काष्ठा rcar_dmac_chan *chan,
					  काष्ठा rcar_dmac_desc *desc)
अणु
	अटल स्थिर u32 chcr_ts[] = अणु
		RCAR_DMACHCR_TS_1B, RCAR_DMACHCR_TS_2B,
		RCAR_DMACHCR_TS_4B, RCAR_DMACHCR_TS_8B,
		RCAR_DMACHCR_TS_16B, RCAR_DMACHCR_TS_32B,
		RCAR_DMACHCR_TS_64B,
	पूर्ण;

	अचिन्हित पूर्णांक xfer_size;
	u32 chcr;

	चयन (desc->direction) अणु
	हाल DMA_DEV_TO_MEM:
		chcr = RCAR_DMACHCR_DM_INC | RCAR_DMACHCR_SM_FIXED
		     | RCAR_DMACHCR_RS_DMARS;
		xfer_size = chan->src.xfer_size;
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		chcr = RCAR_DMACHCR_DM_FIXED | RCAR_DMACHCR_SM_INC
		     | RCAR_DMACHCR_RS_DMARS;
		xfer_size = chan->dst.xfer_size;
		अवरोध;

	हाल DMA_MEM_TO_MEM:
	शेष:
		chcr = RCAR_DMACHCR_DM_INC | RCAR_DMACHCR_SM_INC
		     | RCAR_DMACHCR_RS_AUTO;
		xfer_size = RCAR_DMAC_MEMCPY_XFER_SIZE;
		अवरोध;
	पूर्ण

	desc->xfer_shअगरt = ilog2(xfer_size);
	desc->chcr = chcr | chcr_ts[desc->xfer_shअगरt];
पूर्ण

/*
 * rcar_dmac_chan_prep_sg - prepare transfer descriptors from an SG list
 *
 * Common routine क्रम खुला (MEMCPY) and slave DMA. The MEMCPY हाल is also
 * converted to scatter-gather to guarantee consistent locking and a correct
 * list manipulation. For slave DMA direction carries the usual meaning, and,
 * logically, the SG list is RAM and the addr variable contains slave address,
 * e.g., the FIFO I/O रेजिस्टर. For MEMCPY direction equals DMA_MEM_TO_MEM
 * and the SG list contains only one element and poपूर्णांकs at the source buffer.
 */
अटल काष्ठा dma_async_tx_descriptor *
rcar_dmac_chan_prep_sg(काष्ठा rcar_dmac_chan *chan, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sg_len, dma_addr_t dev_addr,
		       क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ dma_flags,
		       bool cyclic)
अणु
	काष्ठा rcar_dmac_xfer_chunk *chunk;
	काष्ठा rcar_dmac_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक nchunks = 0;
	अचिन्हित पूर्णांक max_chunk_size;
	अचिन्हित पूर्णांक full_size = 0;
	bool cross_boundary = false;
	अचिन्हित पूर्णांक i;
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	u32 high_dev_addr;
	u32 high_mem_addr;
#पूर्ण_अगर

	desc = rcar_dmac_desc_get(chan);
	अगर (!desc)
		वापस शून्य;

	desc->async_tx.flags = dma_flags;
	desc->async_tx.cookie = -EBUSY;

	desc->cyclic = cyclic;
	desc->direction = dir;

	rcar_dmac_chan_configure_desc(chan, desc);

	max_chunk_size = RCAR_DMATCR_MASK << desc->xfer_shअगरt;

	/*
	 * Allocate and fill the transfer chunk descriptors. We own the only
	 * reference to the DMA descriptor, there's no need क्रम locking.
	 */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma_addr_t mem_addr = sg_dma_address(sg);
		अचिन्हित पूर्णांक len = sg_dma_len(sg);

		full_size += len;

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		अगर (i == 0) अणु
			high_dev_addr = dev_addr >> 32;
			high_mem_addr = mem_addr >> 32;
		पूर्ण

		अगर ((dev_addr >> 32 != high_dev_addr) ||
		    (mem_addr >> 32 != high_mem_addr))
			cross_boundary = true;
#पूर्ण_अगर
		जबतक (len) अणु
			अचिन्हित पूर्णांक size = min(len, max_chunk_size);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
			/*
			 * Prevent inभागidual transfers from crossing 4GB
			 * boundaries.
			 */
			अगर (dev_addr >> 32 != (dev_addr + size - 1) >> 32) अणु
				size = ALIGN(dev_addr, 1ULL << 32) - dev_addr;
				cross_boundary = true;
			पूर्ण
			अगर (mem_addr >> 32 != (mem_addr + size - 1) >> 32) अणु
				size = ALIGN(mem_addr, 1ULL << 32) - mem_addr;
				cross_boundary = true;
			पूर्ण
#पूर्ण_अगर

			chunk = rcar_dmac_xfer_chunk_get(chan);
			अगर (!chunk) अणु
				rcar_dmac_desc_put(chan, desc);
				वापस शून्य;
			पूर्ण

			अगर (dir == DMA_DEV_TO_MEM) अणु
				chunk->src_addr = dev_addr;
				chunk->dst_addr = mem_addr;
			पूर्ण अन्यथा अणु
				chunk->src_addr = mem_addr;
				chunk->dst_addr = dev_addr;
			पूर्ण

			chunk->size = size;

			dev_dbg(chan->chan.device->dev,
				"chan%u: chunk %p/%p sgl %u@%p, %u/%u %pad -> %pad\n",
				chan->index, chunk, desc, i, sg, size, len,
				&chunk->src_addr, &chunk->dst_addr);

			mem_addr += size;
			अगर (dir == DMA_MEM_TO_MEM)
				dev_addr += size;

			len -= size;

			list_add_tail(&chunk->node, &desc->chunks);
			nchunks++;
		पूर्ण
	पूर्ण

	desc->nchunks = nchunks;
	desc->size = full_size;

	/*
	 * Use hardware descriptor lists अगर possible when more than one chunk
	 * needs to be transferred (otherwise they करोn't make much sense).
	 *
	 * Source/Destination address should be located in same 4GiB region
	 * in the 40bit address space when it uses Hardware descriptor,
	 * and cross_boundary is checking it.
	 */
	desc->hwdescs.use = !cross_boundary && nchunks > 1;
	अगर (desc->hwdescs.use) अणु
		अगर (rcar_dmac_fill_hwdesc(chan, desc) < 0)
			desc->hwdescs.use = false;
	पूर्ण

	वापस &desc->async_tx;
पूर्ण

/* -----------------------------------------------------------------------------
 * DMA engine operations
 */

अटल पूर्णांक rcar_dmac_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	पूर्णांक ret;

	INIT_LIST_HEAD(&rchan->desc.chunks_मुक्त);
	INIT_LIST_HEAD(&rchan->desc.pages);

	/* Pपुनः_स्मृतिate descriptors. */
	ret = rcar_dmac_xfer_chunk_alloc(rchan, GFP_KERNEL);
	अगर (ret < 0)
		वापस -ENOMEM;

	ret = rcar_dmac_desc_alloc(rchan, GFP_KERNEL);
	अगर (ret < 0)
		वापस -ENOMEM;

	वापस pm_runसमय_get_sync(chan->device->dev);
पूर्ण

अटल व्योम rcar_dmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	काष्ठा rcar_dmac *dmac = to_rcar_dmac(chan->device);
	काष्ठा rcar_dmac_chan_map *map = &rchan->map;
	काष्ठा rcar_dmac_desc_page *page, *_page;
	काष्ठा rcar_dmac_desc *desc;
	LIST_HEAD(list);

	/* Protect against ISR */
	spin_lock_irq(&rchan->lock);
	rcar_dmac_chan_halt(rchan);
	spin_unlock_irq(&rchan->lock);

	/*
	 * Now no new पूर्णांकerrupts will occur, but one might alपढ़ोy be
	 * running. Wait क्रम it to finish beक्रमe मुक्तing resources.
	 */
	synchronize_irq(rchan->irq);

	अगर (rchan->mid_rid >= 0) अणु
		/* The caller is holding dma_list_mutex */
		clear_bit(rchan->mid_rid, dmac->modules);
		rchan->mid_rid = -EINVAL;
	पूर्ण

	list_splice_init(&rchan->desc.मुक्त, &list);
	list_splice_init(&rchan->desc.pending, &list);
	list_splice_init(&rchan->desc.active, &list);
	list_splice_init(&rchan->desc.करोne, &list);
	list_splice_init(&rchan->desc.रुको, &list);

	rchan->desc.running = शून्य;

	list_क्रम_each_entry(desc, &list, node)
		rcar_dmac_पुनः_स्मृति_hwdesc(rchan, desc, 0);

	list_क्रम_each_entry_safe(page, _page, &rchan->desc.pages, node) अणु
		list_del(&page->node);
		मुक्त_page((अचिन्हित दीर्घ)page);
	पूर्ण

	/* Remove slave mapping अगर present. */
	अगर (map->slave.xfer_size) अणु
		dma_unmap_resource(chan->device->dev, map->addr,
				   map->slave.xfer_size, map->dir, 0);
		map->slave.xfer_size = 0;
	पूर्ण

	pm_runसमय_put(chan->device->dev);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
rcar_dmac_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dma_dest,
			  dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	काष्ठा scatterlist sgl;

	अगर (!len)
		वापस शून्य;

	sg_init_table(&sgl, 1);
	sg_set_page(&sgl, pfn_to_page(PFN_DOWN(dma_src)), len,
		    offset_in_page(dma_src));
	sg_dma_address(&sgl) = dma_src;
	sg_dma_len(&sgl) = len;

	वापस rcar_dmac_chan_prep_sg(rchan, &sgl, 1, dma_dest,
				      DMA_MEM_TO_MEM, flags, false);
पूर्ण

अटल पूर्णांक rcar_dmac_map_slave_addr(काष्ठा dma_chan *chan,
				    क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	काष्ठा rcar_dmac_chan_map *map = &rchan->map;
	phys_addr_t dev_addr;
	माप_प्रकार dev_size;
	क्रमागत dma_data_direction dev_dir;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_addr = rchan->src.slave_addr;
		dev_size = rchan->src.xfer_size;
		dev_dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		dev_addr = rchan->dst.slave_addr;
		dev_size = rchan->dst.xfer_size;
		dev_dir = DMA_FROM_DEVICE;
	पूर्ण

	/* Reuse current map अगर possible. */
	अगर (dev_addr == map->slave.slave_addr &&
	    dev_size == map->slave.xfer_size &&
	    dev_dir == map->dir)
		वापस 0;

	/* Remove old mapping अगर present. */
	अगर (map->slave.xfer_size)
		dma_unmap_resource(chan->device->dev, map->addr,
				   map->slave.xfer_size, map->dir, 0);
	map->slave.xfer_size = 0;

	/* Create new slave address map. */
	map->addr = dma_map_resource(chan->device->dev, dev_addr, dev_size,
				     dev_dir, 0);

	अगर (dma_mapping_error(chan->device->dev, map->addr)) अणु
		dev_err(chan->device->dev,
			"chan%u: failed to map %zx@%pap", rchan->index,
			dev_size, &dev_addr);
		वापस -EIO;
	पूर्ण

	dev_dbg(chan->device->dev, "chan%u: map %zx@%pap to %pad dir: %s\n",
		rchan->index, dev_size, &dev_addr, &map->addr,
		dev_dir == DMA_TO_DEVICE ? "DMA_TO_DEVICE" : "DMA_FROM_DEVICE");

	map->slave.slave_addr = dev_addr;
	map->slave.xfer_size = dev_size;
	map->dir = dev_dir;

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
rcar_dmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
			अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	/* Someone calling slave DMA on a generic channel? */
	अगर (rchan->mid_rid < 0 || !sg_len || !sg_dma_len(sgl)) अणु
		dev_warn(chan->device->dev,
			 "%s: bad parameter: len=%d, id=%d\n",
			 __func__, sg_len, rchan->mid_rid);
		वापस शून्य;
	पूर्ण

	अगर (rcar_dmac_map_slave_addr(chan, dir))
		वापस शून्य;

	वापस rcar_dmac_chan_prep_sg(rchan, sgl, sg_len, rchan->map.addr,
				      dir, flags, false);
पूर्ण

#घोषणा RCAR_DMAC_MAX_SG_LEN	32

अटल काष्ठा dma_async_tx_descriptor *
rcar_dmac_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf_addr,
			  माप_प्रकार buf_len, माप_प्रकार period_len,
			  क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक sg_len;
	अचिन्हित पूर्णांक i;

	/* Someone calling slave DMA on a generic channel? */
	अगर (rchan->mid_rid < 0 || buf_len < period_len) अणु
		dev_warn(chan->device->dev,
			"%s: bad parameter: buf_len=%zu, period_len=%zu, id=%d\n",
			__func__, buf_len, period_len, rchan->mid_rid);
		वापस शून्य;
	पूर्ण

	अगर (rcar_dmac_map_slave_addr(chan, dir))
		वापस शून्य;

	sg_len = buf_len / period_len;
	अगर (sg_len > RCAR_DMAC_MAX_SG_LEN) अणु
		dev_err(chan->device->dev,
			"chan%u: sg length %d exceeds limit %d",
			rchan->index, sg_len, RCAR_DMAC_MAX_SG_LEN);
		वापस शून्य;
	पूर्ण

	/*
	 * Allocate the sg list dynamically as it would consume too much stack
	 * space.
	 */
	sgl = kदो_स्मृति_array(sg_len, माप(*sgl), GFP_NOWAIT);
	अगर (!sgl)
		वापस शून्य;

	sg_init_table(sgl, sg_len);

	क्रम (i = 0; i < sg_len; ++i) अणु
		dma_addr_t src = buf_addr + (period_len * i);

		sg_set_page(&sgl[i], pfn_to_page(PFN_DOWN(src)), period_len,
			    offset_in_page(src));
		sg_dma_address(&sgl[i]) = src;
		sg_dma_len(&sgl[i]) = period_len;
	पूर्ण

	desc = rcar_dmac_chan_prep_sg(rchan, sgl, sg_len, rchan->map.addr,
				      dir, flags, true);

	kमुक्त(sgl);
	वापस desc;
पूर्ण

अटल पूर्णांक rcar_dmac_device_config(काष्ठा dma_chan *chan,
				   काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	/*
	 * We could lock this, but you shouldn't be configuring the
	 * channel, जबतक using it...
	 */
	rchan->src.slave_addr = cfg->src_addr;
	rchan->dst.slave_addr = cfg->dst_addr;
	rchan->src.xfer_size = cfg->src_addr_width;
	rchan->dst.xfer_size = cfg->dst_addr_width;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_dmac_chan_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rchan->lock, flags);
	rcar_dmac_chan_halt(rchan);
	spin_unlock_irqrestore(&rchan->lock, flags);

	/*
	 * FIXME: No new पूर्णांकerrupt can occur now, but the IRQ thपढ़ो might still
	 * be running.
	 */

	rcar_dmac_chan_reinit(rchan);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rcar_dmac_chan_get_residue(काष्ठा rcar_dmac_chan *chan,
					       dma_cookie_t cookie)
अणु
	काष्ठा rcar_dmac_desc *desc = chan->desc.running;
	काष्ठा rcar_dmac_xfer_chunk *running = शून्य;
	काष्ठा rcar_dmac_xfer_chunk *chunk;
	क्रमागत dma_status status;
	अचिन्हित पूर्णांक residue = 0;
	अचिन्हित पूर्णांक dptr = 0;
	अचिन्हित पूर्णांक chcrb;
	अचिन्हित पूर्णांक tcrb;
	अचिन्हित पूर्णांक i;

	अगर (!desc)
		वापस 0;

	/*
	 * If the cookie corresponds to a descriptor that has been completed
	 * there is no residue. The same check has alपढ़ोy been perक्रमmed by the
	 * caller but without holding the channel lock, so the descriptor could
	 * now be complete.
	 */
	status = dma_cookie_status(&chan->chan, cookie, शून्य);
	अगर (status == DMA_COMPLETE)
		वापस 0;

	/*
	 * If the cookie करोesn't correspond to the currently running transfer
	 * then the descriptor hasn't been processed yet, and the residue is
	 * equal to the full descriptor size.
	 * Also, a client driver is possible to call this function beक्रमe
	 * rcar_dmac_isr_channel_thपढ़ो() runs. In this हाल, the "desc.running"
	 * will be the next descriptor, and the करोne list will appear. So, अगर
	 * the argument cookie matches the करोne list's cookie, we can assume
	 * the residue is zero.
	 */
	अगर (cookie != desc->async_tx.cookie) अणु
		list_क्रम_each_entry(desc, &chan->desc.करोne, node) अणु
			अगर (cookie == desc->async_tx.cookie)
				वापस 0;
		पूर्ण
		list_क्रम_each_entry(desc, &chan->desc.pending, node) अणु
			अगर (cookie == desc->async_tx.cookie)
				वापस desc->size;
		पूर्ण
		list_क्रम_each_entry(desc, &chan->desc.active, node) अणु
			अगर (cookie == desc->async_tx.cookie)
				वापस desc->size;
		पूर्ण

		/*
		 * No descriptor found क्रम the cookie, there's thus no residue.
		 * This shouldn't happen अगर the calling driver passes a correct
		 * cookie value.
		 */
		WARN(1, "No descriptor for cookie!");
		वापस 0;
	पूर्ण

	/*
	 * We need to पढ़ो two रेजिस्टरs.
	 * Make sure the control रेजिस्टर करोes not skip to next chunk
	 * जबतक पढ़ोing the counter.
	 * Trying it 3 बार should be enough: Initial पढ़ो, retry, retry
	 * क्रम the paranoid.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		chcrb = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCRB) &
					    RCAR_DMACHCRB_DPTR_MASK;
		tcrb = rcar_dmac_chan_पढ़ो(chan, RCAR_DMATCRB);
		/* Still the same? */
		अगर (chcrb == (rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCRB) &
			      RCAR_DMACHCRB_DPTR_MASK))
			अवरोध;
	पूर्ण
	WARN_ONCE(i >= 3, "residue might be not continuous!");

	/*
	 * In descriptor mode the descriptor running poपूर्णांकer is not मुख्यtained
	 * by the पूर्णांकerrupt handler, find the running descriptor from the
	 * descriptor poपूर्णांकer field in the CHCRB रेजिस्टर. In non-descriptor
	 * mode just use the running descriptor poपूर्णांकer.
	 */
	अगर (desc->hwdescs.use) अणु
		dptr = chcrb >> RCAR_DMACHCRB_DPTR_SHIFT;
		अगर (dptr == 0)
			dptr = desc->nchunks;
		dptr--;
		WARN_ON(dptr >= desc->nchunks);
	पूर्ण अन्यथा अणु
		running = desc->running;
	पूर्ण

	/* Compute the size of all chunks still to be transferred. */
	list_क्रम_each_entry_reverse(chunk, &desc->chunks, node) अणु
		अगर (chunk == running || ++dptr == desc->nchunks)
			अवरोध;

		residue += chunk->size;
	पूर्ण

	/* Add the residue क्रम the current chunk. */
	residue += tcrb << desc->xfer_shअगरt;

	वापस residue;
पूर्ण

अटल क्रमागत dma_status rcar_dmac_tx_status(काष्ठा dma_chan *chan,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक residue;
	bool cyclic;

	status = dma_cookie_status(chan, cookie, txstate);
	अगर (status == DMA_COMPLETE || !txstate)
		वापस status;

	spin_lock_irqsave(&rchan->lock, flags);
	residue = rcar_dmac_chan_get_residue(rchan, cookie);
	cyclic = rchan->desc.running ? rchan->desc.running->cyclic : false;
	spin_unlock_irqrestore(&rchan->lock, flags);

	/* अगर there's no residue, the cookie is complete */
	अगर (!residue && !cyclic)
		वापस DMA_COMPLETE;

	dma_set_residue(txstate, residue);

	वापस status;
पूर्ण

अटल व्योम rcar_dmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rchan->lock, flags);

	अगर (list_empty(&rchan->desc.pending))
		जाओ करोne;

	/* Append the pending list to the active list. */
	list_splice_tail_init(&rchan->desc.pending, &rchan->desc.active);

	/*
	 * If no transfer is running pick the first descriptor from the active
	 * list and start the transfer.
	 */
	अगर (!rchan->desc.running) अणु
		काष्ठा rcar_dmac_desc *desc;

		desc = list_first_entry(&rchan->desc.active,
					काष्ठा rcar_dmac_desc, node);
		rchan->desc.running = desc;

		rcar_dmac_chan_start_xfer(rchan);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&rchan->lock, flags);
पूर्ण

अटल व्योम rcar_dmac_device_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	synchronize_irq(rchan->irq);
पूर्ण

/* -----------------------------------------------------------------------------
 * IRQ handling
 */

अटल irqवापस_t rcar_dmac_isr_desc_stage_end(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc = chan->desc.running;
	अचिन्हित पूर्णांक stage;

	अगर (WARN_ON(!desc || !desc->cyclic)) अणु
		/*
		 * This should never happen, there should always be a running
		 * cyclic descriptor when a descriptor stage end पूर्णांकerrupt is
		 * triggered. Warn and वापस.
		 */
		वापस IRQ_NONE;
	पूर्ण

	/* Program the पूर्णांकerrupt poपूर्णांकer to the next stage. */
	stage = (rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCRB) &
		 RCAR_DMACHCRB_DPTR_MASK) >> RCAR_DMACHCRB_DPTR_SHIFT;
	rcar_dmac_chan_ग_लिखो(chan, RCAR_DMADPCR, RCAR_DMADPCR_DIPT(stage));

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t rcar_dmac_isr_transfer_end(काष्ठा rcar_dmac_chan *chan)
अणु
	काष्ठा rcar_dmac_desc *desc = chan->desc.running;
	irqवापस_t ret = IRQ_WAKE_THREAD;

	अगर (WARN_ON_ONCE(!desc)) अणु
		/*
		 * This should never happen, there should always be a running
		 * descriptor when a transfer end पूर्णांकerrupt is triggered. Warn
		 * and वापस.
		 */
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * The transfer end पूर्णांकerrupt isn't generated क्रम each chunk when using
	 * descriptor mode. Only update the running chunk poपूर्णांकer in
	 * non-descriptor mode.
	 */
	अगर (!desc->hwdescs.use) अणु
		/*
		 * If we haven't completed the last transfer chunk simply move
		 * to the next one. Only wake the IRQ thपढ़ो अगर the transfer is
		 * cyclic.
		 */
		अगर (!list_is_last(&desc->running->node, &desc->chunks)) अणु
			desc->running = list_next_entry(desc->running, node);
			अगर (!desc->cyclic)
				ret = IRQ_HANDLED;
			जाओ करोne;
		पूर्ण

		/*
		 * We've completed the last transfer chunk. If the transfer is
		 * cyclic, move back to the first one.
		 */
		अगर (desc->cyclic) अणु
			desc->running =
				list_first_entry(&desc->chunks,
						 काष्ठा rcar_dmac_xfer_chunk,
						 node);
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* The descriptor is complete, move it to the करोne list. */
	list_move_tail(&desc->node, &chan->desc.करोne);

	/* Queue the next descriptor, अगर any. */
	अगर (!list_empty(&chan->desc.active))
		chan->desc.running = list_first_entry(&chan->desc.active,
						      काष्ठा rcar_dmac_desc,
						      node);
	अन्यथा
		chan->desc.running = शून्य;

करोne:
	अगर (chan->desc.running)
		rcar_dmac_chan_start_xfer(chan);

	वापस ret;
पूर्ण

अटल irqवापस_t rcar_dmac_isr_channel(पूर्णांक irq, व्योम *dev)
अणु
	u32 mask = RCAR_DMACHCR_DSE | RCAR_DMACHCR_TE;
	काष्ठा rcar_dmac_chan *chan = dev;
	irqवापस_t ret = IRQ_NONE;
	bool reinit = false;
	u32 chcr;

	spin_lock(&chan->lock);

	chcr = rcar_dmac_chan_पढ़ो(chan, RCAR_DMACHCR);
	अगर (chcr & RCAR_DMACHCR_CAE) अणु
		काष्ठा rcar_dmac *dmac = to_rcar_dmac(chan->chan.device);

		/*
		 * We करोn't need to call rcar_dmac_chan_halt()
		 * because channel is alपढ़ोy stopped in error हाल.
		 * We need to clear रेजिस्टर and check DE bit as recovery.
		 */
		rcar_dmac_chan_clear(dmac, chan);
		rcar_dmac_chcr_de_barrier(chan);
		reinit = true;
		जाओ spin_lock_end;
	पूर्ण

	अगर (chcr & RCAR_DMACHCR_TE)
		mask |= RCAR_DMACHCR_DE;
	rcar_dmac_chan_ग_लिखो(chan, RCAR_DMACHCR, chcr & ~mask);
	अगर (mask & RCAR_DMACHCR_DE)
		rcar_dmac_chcr_de_barrier(chan);

	अगर (chcr & RCAR_DMACHCR_DSE)
		ret |= rcar_dmac_isr_desc_stage_end(chan);

	अगर (chcr & RCAR_DMACHCR_TE)
		ret |= rcar_dmac_isr_transfer_end(chan);

spin_lock_end:
	spin_unlock(&chan->lock);

	अगर (reinit) अणु
		dev_err(chan->chan.device->dev, "Channel Address Error\n");

		rcar_dmac_chan_reinit(chan);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t rcar_dmac_isr_channel_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा rcar_dmac_chan *chan = dev;
	काष्ठा rcar_dmac_desc *desc;
	काष्ठा dmaengine_desc_callback cb;

	spin_lock_irq(&chan->lock);

	/* For cyclic transfers notअगरy the user after every chunk. */
	अगर (chan->desc.running && chan->desc.running->cyclic) अणु
		desc = chan->desc.running;
		dmaengine_desc_get_callback(&desc->async_tx, &cb);

		अगर (dmaengine_desc_callback_valid(&cb)) अणु
			spin_unlock_irq(&chan->lock);
			dmaengine_desc_callback_invoke(&cb, शून्य);
			spin_lock_irq(&chan->lock);
		पूर्ण
	पूर्ण

	/*
	 * Call the callback function क्रम all descriptors on the करोne list and
	 * move them to the ack रुको list.
	 */
	जबतक (!list_empty(&chan->desc.करोne)) अणु
		desc = list_first_entry(&chan->desc.करोne, काष्ठा rcar_dmac_desc,
					node);
		dma_cookie_complete(&desc->async_tx);
		list_del(&desc->node);

		dmaengine_desc_get_callback(&desc->async_tx, &cb);
		अगर (dmaengine_desc_callback_valid(&cb)) अणु
			spin_unlock_irq(&chan->lock);
			/*
			 * We own the only reference to this descriptor, we can
			 * safely dereference it without holding the channel
			 * lock.
			 */
			dmaengine_desc_callback_invoke(&cb, शून्य);
			spin_lock_irq(&chan->lock);
		पूर्ण

		list_add_tail(&desc->node, &chan->desc.रुको);
	पूर्ण

	spin_unlock_irq(&chan->lock);

	/* Recycle all acked descriptors. */
	rcar_dmac_desc_recycle_acked(chan);

	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * OF xlate and channel filter
 */

अटल bool rcar_dmac_chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	काष्ठा rcar_dmac *dmac = to_rcar_dmac(chan->device);
	काष्ठा of_phandle_args *dma_spec = arg;

	/*
	 * FIXME: Using a filter on OF platक्रमms is a nonsense. The OF xlate
	 * function knows from which device it wants to allocate a channel from,
	 * and would be perfectly capable of selecting the channel it wants.
	 * Forcing it to call dma_request_channel() and iterate through all
	 * channels from all controllers is just poपूर्णांकless.
	 */
	अगर (chan->device->device_config != rcar_dmac_device_config)
		वापस false;

	वापस !test_and_set_bit(dma_spec->args[0], dmac->modules);
पूर्ण

अटल काष्ठा dma_chan *rcar_dmac_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा rcar_dmac_chan *rchan;
	काष्ठा dma_chan *chan;
	dma_cap_mask_t mask;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	/* Only slave DMA channels can be allocated via DT */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	chan = __dma_request_channel(&mask, rcar_dmac_chan_filter, dma_spec,
				     ofdma->of_node);
	अगर (!chan)
		वापस शून्य;

	rchan = to_rcar_dmac_chan(chan);
	rchan->mid_rid = dma_spec->args[0];

	वापस chan;
पूर्ण

/* -----------------------------------------------------------------------------
 * Power management
 */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rcar_dmac_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rcar_dmac_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_dmac *dmac = dev_get_drvdata(dev);

	वापस rcar_dmac_init(dmac);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rcar_dmac_pm = अणु
	/*
	 * TODO क्रम प्रणाली sleep/resume:
	 *   - Wait क्रम the current transfer to complete and stop the device,
	 *   - Resume transfers, अगर any.
	 */
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(rcar_dmac_runसमय_suspend, rcar_dmac_runसमय_resume,
			   शून्य)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe and हटाओ
 */

अटल पूर्णांक rcar_dmac_chan_probe(काष्ठा rcar_dmac *dmac,
				काष्ठा rcar_dmac_chan *rchan)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dmac->dev);
	काष्ठा dma_chan *chan = &rchan->chan;
	अक्षर pdev_irqname[5];
	अक्षर *irqname;
	पूर्णांक ret;

	rchan->mid_rid = -EINVAL;

	spin_lock_init(&rchan->lock);

	INIT_LIST_HEAD(&rchan->desc.मुक्त);
	INIT_LIST_HEAD(&rchan->desc.pending);
	INIT_LIST_HEAD(&rchan->desc.active);
	INIT_LIST_HEAD(&rchan->desc.करोne);
	INIT_LIST_HEAD(&rchan->desc.रुको);

	/* Request the channel पूर्णांकerrupt. */
	प्र_लिखो(pdev_irqname, "ch%u", rchan->index);
	rchan->irq = platक्रमm_get_irq_byname(pdev, pdev_irqname);
	अगर (rchan->irq < 0)
		वापस -ENODEV;

	irqname = devm_kaप्र_लिखो(dmac->dev, GFP_KERNEL, "%s:%u",
				 dev_name(dmac->dev), rchan->index);
	अगर (!irqname)
		वापस -ENOMEM;

	/*
	 * Initialize the DMA engine channel and add it to the DMA engine
	 * channels list.
	 */
	chan->device = &dmac->engine;
	dma_cookie_init(chan);

	list_add_tail(&chan->device_node, &dmac->engine.channels);

	ret = devm_request_thपढ़ोed_irq(dmac->dev, rchan->irq,
					rcar_dmac_isr_channel,
					rcar_dmac_isr_channel_thपढ़ो, 0,
					irqname, rchan);
	अगर (ret) अणु
		dev_err(dmac->dev, "failed to request IRQ %u (%d)\n",
			rchan->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RCAR_DMAC_MAX_CHANNELS	32

अटल पूर्णांक rcar_dmac_parse_of(काष्ठा device *dev, काष्ठा rcar_dmac *dmac)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "dma-channels", &dmac->n_channels);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to read dma-channels property\n");
		वापस ret;
	पूर्ण

	/* The hardware and driver करोn't support more than 32 bits in CHCLR */
	अगर (dmac->n_channels <= 0 ||
	    dmac->n_channels >= RCAR_DMAC_MAX_CHANNELS) अणु
		dev_err(dev, "invalid number of channels %u\n",
			dmac->n_channels);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the driver is unable to पढ़ो dma-channel-mask property,
	 * the driver assumes that it can use all channels.
	 */
	dmac->channels_mask = GENMASK(dmac->n_channels - 1, 0);
	of_property_पढ़ो_u32(np, "dma-channel-mask", &dmac->channels_mask);

	/* If the property has out-of-channel mask, this driver clears it */
	dmac->channels_mask &= GENMASK(dmac->n_channels - 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर क्रमागत dma_slave_buswidth widths = DMA_SLAVE_BUSWIDTH_1_BYTE |
		DMA_SLAVE_BUSWIDTH_2_BYTES | DMA_SLAVE_BUSWIDTH_4_BYTES |
		DMA_SLAVE_BUSWIDTH_8_BYTES | DMA_SLAVE_BUSWIDTH_16_BYTES |
		DMA_SLAVE_BUSWIDTH_32_BYTES | DMA_SLAVE_BUSWIDTH_64_BYTES;
	स्थिर काष्ठा rcar_dmac_of_data *data;
	काष्ठा rcar_dmac_chan *chan;
	काष्ठा dma_device *engine;
	व्योम __iomem *chan_base;
	काष्ठा rcar_dmac *dmac;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -EINVAL;

	dmac = devm_kzalloc(&pdev->dev, माप(*dmac), GFP_KERNEL);
	अगर (!dmac)
		वापस -ENOMEM;

	dmac->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dmac);
	dma_set_max_seg_size(dmac->dev, RCAR_DMATCR_MASK);
	dma_set_mask_and_coherent(dmac->dev, DMA_BIT_MASK(40));

	ret = rcar_dmac_parse_of(&pdev->dev, dmac);
	अगर (ret < 0)
		वापस ret;

	/*
	 * A still unconfirmed hardware bug prevents the IPMMU microTLB 0 to be
	 * flushed correctly, resulting in memory corruption. DMAC 0 channel 0
	 * is connected to microTLB 0 on currently supported platक्रमms, so we
	 * can't use it with the IPMMU. As the IOMMU API operates at the device
	 * level we can't disable it selectively, so ignore channel 0 क्रम now अगर
	 * the device is part of an IOMMU group.
	 */
	अगर (device_iommu_mapped(&pdev->dev))
		dmac->channels_mask &= ~BIT(0);

	dmac->channels = devm_kसुस्मृति(&pdev->dev, dmac->n_channels,
				      माप(*dmac->channels), GFP_KERNEL);
	अगर (!dmac->channels)
		वापस -ENOMEM;

	/* Request resources. */
	dmac->dmac_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dmac->dmac_base))
		वापस PTR_ERR(dmac->dmac_base);

	अगर (!data->chan_offset_base) अणु
		dmac->chan_base = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(dmac->chan_base))
			वापस PTR_ERR(dmac->chan_base);

		chan_base = dmac->chan_base;
	पूर्ण अन्यथा अणु
		chan_base = dmac->dmac_base + data->chan_offset_base;
	पूर्ण

	क्रम_each_rcar_dmac_chan(i, dmac, chan) अणु
		chan->index = i;
		chan->iomem = chan_base + i * data->chan_offset_stride;
	पूर्ण

	/* Enable runसमय PM and initialize the device. */
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "runtime PM get sync failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = rcar_dmac_init(dmac);
	pm_runसमय_put(&pdev->dev);

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to reset device\n");
		जाओ error;
	पूर्ण

	/* Initialize engine */
	engine = &dmac->engine;

	dma_cap_set(DMA_MEMCPY, engine->cap_mask);
	dma_cap_set(DMA_SLAVE, engine->cap_mask);

	engine->dev		= &pdev->dev;
	engine->copy_align	= ilog2(RCAR_DMAC_MEMCPY_XFER_SIZE);

	engine->src_addr_widths	= widths;
	engine->dst_addr_widths	= widths;
	engine->directions	= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	engine->device_alloc_chan_resources	= rcar_dmac_alloc_chan_resources;
	engine->device_मुक्त_chan_resources	= rcar_dmac_मुक्त_chan_resources;
	engine->device_prep_dma_स_नकल		= rcar_dmac_prep_dma_स_नकल;
	engine->device_prep_slave_sg		= rcar_dmac_prep_slave_sg;
	engine->device_prep_dma_cyclic		= rcar_dmac_prep_dma_cyclic;
	engine->device_config			= rcar_dmac_device_config;
	engine->device_छोड़ो			= rcar_dmac_chan_छोड़ो;
	engine->device_terminate_all		= rcar_dmac_chan_terminate_all;
	engine->device_tx_status		= rcar_dmac_tx_status;
	engine->device_issue_pending		= rcar_dmac_issue_pending;
	engine->device_synchronize		= rcar_dmac_device_synchronize;

	INIT_LIST_HEAD(&engine->channels);

	क्रम_each_rcar_dmac_chan(i, dmac, chan) अणु
		ret = rcar_dmac_chan_probe(dmac, chan);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* Register the DMAC as a DMA provider क्रम DT. */
	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, rcar_dmac_of_xlate,
					 शून्य);
	अगर (ret < 0)
		जाओ error;

	/*
	 * Register the DMA engine device.
	 *
	 * Default transfer size of 32 bytes requires 32-byte alignment.
	 */
	ret = dma_async_device_रेजिस्टर(engine);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	of_dma_controller_मुक्त(pdev->dev.of_node);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rcar_dmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_dmac *dmac = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&dmac->engine);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम rcar_dmac_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_dmac *dmac = platक्रमm_get_drvdata(pdev);

	rcar_dmac_stop_all_chan(dmac);
पूर्ण

अटल स्थिर काष्ठा rcar_dmac_of_data rcar_dmac_data = अणु
	.chan_offset_base	= 0x8000,
	.chan_offset_stride	= 0x80,
पूर्ण;

अटल स्थिर काष्ठा rcar_dmac_of_data rcar_v3u_dmac_data = अणु
	.chan_offset_base	= 0x0,
	.chan_offset_stride	= 0x1000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_dmac_of_ids[] = अणु
	अणु
		.compatible = "renesas,rcar-dmac",
		.data = &rcar_dmac_data,
	पूर्ण, अणु
		.compatible = "renesas,dmac-r8a779a0",
		.data = &rcar_v3u_dmac_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_dmac_of_ids);

अटल काष्ठा platक्रमm_driver rcar_dmac_driver = अणु
	.driver		= अणु
		.pm	= &rcar_dmac_pm,
		.name	= "rcar-dmac",
		.of_match_table = rcar_dmac_of_ids,
	पूर्ण,
	.probe		= rcar_dmac_probe,
	.हटाओ		= rcar_dmac_हटाओ,
	.shutकरोwn	= rcar_dmac_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(rcar_dmac_driver);

MODULE_DESCRIPTION("R-Car Gen2 DMA Controller Driver");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL v2");
