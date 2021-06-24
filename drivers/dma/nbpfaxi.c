<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013-2014 Renesas Electronics Europe Ltd.
 * Author: Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/dma/nbpfaxi.h>

#समावेश "dmaengine.h"

#घोषणा NBPF_REG_CHAN_OFFSET	0
#घोषणा NBPF_REG_CHAN_SIZE	0x40

/* Channel Current Transaction Byte रेजिस्टर */
#घोषणा NBPF_CHAN_CUR_TR_BYTE	0x20

/* Channel Status रेजिस्टर */
#घोषणा NBPF_CHAN_STAT	0x24
#घोषणा NBPF_CHAN_STAT_EN	1
#घोषणा NBPF_CHAN_STAT_TACT	4
#घोषणा NBPF_CHAN_STAT_ERR	0x10
#घोषणा NBPF_CHAN_STAT_END	0x20
#घोषणा NBPF_CHAN_STAT_TC	0x40
#घोषणा NBPF_CHAN_STAT_DER	0x400

/* Channel Control रेजिस्टर */
#घोषणा NBPF_CHAN_CTRL	0x28
#घोषणा NBPF_CHAN_CTRL_SETEN	1
#घोषणा NBPF_CHAN_CTRL_CLREN	2
#घोषणा NBPF_CHAN_CTRL_STG	4
#घोषणा NBPF_CHAN_CTRL_SWRST	8
#घोषणा NBPF_CHAN_CTRL_CLRRQ	0x10
#घोषणा NBPF_CHAN_CTRL_CLREND	0x20
#घोषणा NBPF_CHAN_CTRL_CLRTC	0x40
#घोषणा NBPF_CHAN_CTRL_SETSUS	0x100
#घोषणा NBPF_CHAN_CTRL_CLRSUS	0x200

/* Channel Configuration रेजिस्टर */
#घोषणा NBPF_CHAN_CFG	0x2c
#घोषणा NBPF_CHAN_CFG_SEL	7		/* terminal SELect: 0..7 */
#घोषणा NBPF_CHAN_CFG_REQD	8		/* REQuest Direction: DMAREQ is 0: input, 1: output */
#घोषणा NBPF_CHAN_CFG_LOEN	0x10		/* LOw ENable: low DMA request line is: 0: inactive, 1: active */
#घोषणा NBPF_CHAN_CFG_HIEN	0x20		/* HIgh ENable: high DMA request line is: 0: inactive, 1: active */
#घोषणा NBPF_CHAN_CFG_LVL	0x40		/* LeVeL: DMA request line is sensed as 0: edge, 1: level */
#घोषणा NBPF_CHAN_CFG_AM	0x700		/* ACK Mode: 0: Pulse mode, 1: Level mode, b'1x: Bus Cycle */
#घोषणा NBPF_CHAN_CFG_SDS	0xf000		/* Source Data Size: 0: 8 bits,... , 7: 1024 bits */
#घोषणा NBPF_CHAN_CFG_DDS	0xf0000		/* Destination Data Size: as above */
#घोषणा NBPF_CHAN_CFG_SAD	0x100000	/* Source ADdress counting: 0: increment, 1: fixed */
#घोषणा NBPF_CHAN_CFG_DAD	0x200000	/* Destination ADdress counting: 0: increment, 1: fixed */
#घोषणा NBPF_CHAN_CFG_TM	0x400000	/* Transfer Mode: 0: single, 1: block TM */
#घोषणा NBPF_CHAN_CFG_DEM	0x1000000	/* DMAEND पूर्णांकerrupt Mask */
#घोषणा NBPF_CHAN_CFG_TCM	0x2000000	/* DMATCO पूर्णांकerrupt Mask */
#घोषणा NBPF_CHAN_CFG_SBE	0x8000000	/* Sweep Buffer Enable */
#घोषणा NBPF_CHAN_CFG_RSEL	0x10000000	/* RM: Register Set sELect */
#घोषणा NBPF_CHAN_CFG_RSW	0x20000000	/* RM: Register Select sWitch */
#घोषणा NBPF_CHAN_CFG_REN	0x40000000	/* RM: Register Set Enable */
#घोषणा NBPF_CHAN_CFG_DMS	0x80000000	/* 0: रेजिस्टर mode (RM), 1: link mode (LM) */

#घोषणा NBPF_CHAN_NXLA	0x38
#घोषणा NBPF_CHAN_CRLA	0x3c

/* Link Header field */
#घोषणा NBPF_HEADER_LV	1
#घोषणा NBPF_HEADER_LE	2
#घोषणा NBPF_HEADER_WBD	4
#घोषणा NBPF_HEADER_DIM	8

#घोषणा NBPF_CTRL	0x300
#घोषणा NBPF_CTRL_PR	1		/* 0: fixed priority, 1: round robin */
#घोषणा NBPF_CTRL_LVINT	2		/* DMAEND and DMAERR संकेतling: 0: pulse, 1: level */

#घोषणा NBPF_DSTAT_ER	0x314
#घोषणा NBPF_DSTAT_END	0x318

#घोषणा NBPF_DMA_BUSWIDTHS \
	(BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED) | \
	 BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
	 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))

काष्ठा nbpf_config अणु
	पूर्णांक num_channels;
	पूर्णांक buffer_size;
पूर्ण;

/*
 * We've got 3 types of objects, used to describe DMA transfers:
 * 1. high-level descriptor, containing a काष्ठा dma_async_tx_descriptor object
 *	in it, used to communicate with the user
 * 2. hardware DMA link descriptors, that we pass to DMAC क्रम DMA transfer
 *	queuing, these must be DMAable, using either the streaming DMA API or
 *	allocated from coherent memory - one per SG segment
 * 3. one per SG segment descriptors, used to manage HW link descriptors from
 *	(2). They करो not have to be DMAable. They can either be (a) allocated
 *	together with link descriptors as mixed (DMA / CPU) objects, or (b)
 *	separately. Even अगर allocated separately it would be best to link them
 *	to link descriptors once during channel resource allocation and always
 *	use them as a single object.
 * Thereक्रमe क्रम both हालs (a) and (b) at run-समय objects (2) and (3) shall be
 * treated as a single SG segment descriptor.
 */

काष्ठा nbpf_link_reg अणु
	u32	header;
	u32	src_addr;
	u32	dst_addr;
	u32	transaction_size;
	u32	config;
	u32	पूर्णांकerval;
	u32	extension;
	u32	next;
पूर्ण __packed;

काष्ठा nbpf_device;
काष्ठा nbpf_channel;
काष्ठा nbpf_desc;

काष्ठा nbpf_link_desc अणु
	काष्ठा nbpf_link_reg *hwdesc;
	dma_addr_t hwdesc_dma_addr;
	काष्ठा nbpf_desc *desc;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा nbpf_desc - DMA transfer descriptor
 * @async_tx:	dmaengine object
 * @user_रुको:	रुकोing क्रम a user ack
 * @length:	total transfer length
 * @chan:	associated DMAC channel
 * @sg:		list of hardware descriptors, represented by काष्ठा nbpf_link_desc
 * @node:	member in channel descriptor lists
 */
काष्ठा nbpf_desc अणु
	काष्ठा dma_async_tx_descriptor async_tx;
	bool user_रुको;
	माप_प्रकार length;
	काष्ठा nbpf_channel *chan;
	काष्ठा list_head sg;
	काष्ठा list_head node;
पूर्ण;

/* Take a wild guess: allocate 4 segments per descriptor */
#घोषणा NBPF_SEGMENTS_PER_DESC 4
#घोषणा NBPF_DESCS_PER_PAGE ((PAGE_SIZE - माप(काष्ठा list_head)) /	\
	(माप(काष्ठा nbpf_desc) +					\
	 NBPF_SEGMENTS_PER_DESC *					\
	 (माप(काष्ठा nbpf_link_desc) + माप(काष्ठा nbpf_link_reg))))
#घोषणा NBPF_SEGMENTS_PER_PAGE (NBPF_SEGMENTS_PER_DESC * NBPF_DESCS_PER_PAGE)

काष्ठा nbpf_desc_page अणु
	काष्ठा list_head node;
	काष्ठा nbpf_desc desc[NBPF_DESCS_PER_PAGE];
	काष्ठा nbpf_link_desc ldesc[NBPF_SEGMENTS_PER_PAGE];
	काष्ठा nbpf_link_reg hwdesc[NBPF_SEGMENTS_PER_PAGE];
पूर्ण;

/**
 * काष्ठा nbpf_channel - one DMAC channel
 * @dma_chan:	standard dmaengine channel object
 * @tasklet:	channel specअगरic tasklet used क्रम callbacks
 * @base:	रेजिस्टर address base
 * @nbpf:	DMAC
 * @name:	IRQ name
 * @irq:	IRQ number
 * @slave_src_addr:	source address क्रम slave DMA
 * @slave_src_width:	source slave data size in bytes
 * @slave_src_burst:	maximum source slave burst size in bytes
 * @slave_dst_addr:	destination address क्रम slave DMA
 * @slave_dst_width:	destination slave data size in bytes
 * @slave_dst_burst:	maximum destination slave burst size in bytes
 * @terminal:	DMA terminal, asचिन्हित to this channel
 * @dmarq_cfg:	DMA request line configuration - high / low, edge / level क्रम NBPF_CHAN_CFG
 * @flags:	configuration flags from DT
 * @lock:	protect descriptor lists
 * @मुक्त_links:	list of मुक्त link descriptors
 * @मुक्त:	list of मुक्त descriptors
 * @queued:	list of queued descriptors
 * @active:	list of descriptors, scheduled क्रम processing
 * @करोne:	list of completed descriptors, रुकोing post-processing
 * @desc_page:	list of additionally allocated descriptor pages - अगर any
 * @running:	linked descriptor of running transaction
 * @छोड़ोd:	are translations on this channel छोड़ोd?
 */
काष्ठा nbpf_channel अणु
	काष्ठा dma_chan dma_chan;
	काष्ठा tasklet_काष्ठा tasklet;
	व्योम __iomem *base;
	काष्ठा nbpf_device *nbpf;
	अक्षर name[16];
	पूर्णांक irq;
	dma_addr_t slave_src_addr;
	माप_प्रकार slave_src_width;
	माप_प्रकार slave_src_burst;
	dma_addr_t slave_dst_addr;
	माप_प्रकार slave_dst_width;
	माप_प्रकार slave_dst_burst;
	अचिन्हित पूर्णांक terminal;
	u32 dmarq_cfg;
	अचिन्हित दीर्घ flags;
	spinlock_t lock;
	काष्ठा list_head मुक्त_links;
	काष्ठा list_head मुक्त;
	काष्ठा list_head queued;
	काष्ठा list_head active;
	काष्ठा list_head करोne;
	काष्ठा list_head desc_page;
	काष्ठा nbpf_desc *running;
	bool छोड़ोd;
पूर्ण;

काष्ठा nbpf_device अणु
	काष्ठा dma_device dma_dev;
	व्योम __iomem *base;
	u32 max_burst_mem_पढ़ो;
	u32 max_burst_mem_ग_लिखो;
	काष्ठा clk *clk;
	स्थिर काष्ठा nbpf_config *config;
	अचिन्हित पूर्णांक eirq;
	काष्ठा nbpf_channel chan[];
पूर्ण;

क्रमागत nbpf_model अणु
	NBPF1B4,
	NBPF1B8,
	NBPF1B16,
	NBPF4B4,
	NBPF4B8,
	NBPF4B16,
	NBPF8B4,
	NBPF8B8,
	NBPF8B16,
पूर्ण;

अटल काष्ठा nbpf_config nbpf_cfg[] = अणु
	[NBPF1B4] = अणु
		.num_channels = 1,
		.buffer_size = 4,
	पूर्ण,
	[NBPF1B8] = अणु
		.num_channels = 1,
		.buffer_size = 8,
	पूर्ण,
	[NBPF1B16] = अणु
		.num_channels = 1,
		.buffer_size = 16,
	पूर्ण,
	[NBPF4B4] = अणु
		.num_channels = 4,
		.buffer_size = 4,
	पूर्ण,
	[NBPF4B8] = अणु
		.num_channels = 4,
		.buffer_size = 8,
	पूर्ण,
	[NBPF4B16] = अणु
		.num_channels = 4,
		.buffer_size = 16,
	पूर्ण,
	[NBPF8B4] = अणु
		.num_channels = 8,
		.buffer_size = 4,
	पूर्ण,
	[NBPF8B8] = अणु
		.num_channels = 8,
		.buffer_size = 8,
	पूर्ण,
	[NBPF8B16] = अणु
		.num_channels = 8,
		.buffer_size = 16,
	पूर्ण,
पूर्ण;

#घोषणा nbpf_to_chan(d) container_of(d, काष्ठा nbpf_channel, dma_chan)

/*
 * dmaengine drivers seem to have a lot in common and instead of sharing more
 * code, they reimplement those common algorithms independently. In this driver
 * we try to separate the hardware-specअगरic part from the (largely) generic
 * part. This improves code पढ़ोability and makes it possible in the future to
 * reuse the generic code in क्रमm of a helper library. That generic code should
 * be suitable क्रम various DMA controllers, using transfer descriptors in RAM
 * and pushing one SG list at a समय to the DMA controller.
 */

/*		Hardware-specअगरic part		*/

अटल अंतरभूत u32 nbpf_chan_पढ़ो(काष्ठा nbpf_channel *chan,
				 अचिन्हित पूर्णांक offset)
अणु
	u32 data = ioपढ़ो32(chan->base + offset);
	dev_dbg(chan->dma_chan.device->dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, chan->base, offset, data);
	वापस data;
पूर्ण

अटल अंतरभूत व्योम nbpf_chan_ग_लिखो(काष्ठा nbpf_channel *chan,
				   अचिन्हित पूर्णांक offset, u32 data)
अणु
	ioग_लिखो32(data, chan->base + offset);
	dev_dbg(chan->dma_chan.device->dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, chan->base, offset, data);
पूर्ण

अटल अंतरभूत u32 nbpf_पढ़ो(काष्ठा nbpf_device *nbpf,
			    अचिन्हित पूर्णांक offset)
अणु
	u32 data = ioपढ़ो32(nbpf->base + offset);
	dev_dbg(nbpf->dma_dev.dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, nbpf->base, offset, data);
	वापस data;
पूर्ण

अटल अंतरभूत व्योम nbpf_ग_लिखो(काष्ठा nbpf_device *nbpf,
			      अचिन्हित पूर्णांक offset, u32 data)
अणु
	ioग_लिखो32(data, nbpf->base + offset);
	dev_dbg(nbpf->dma_dev.dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, nbpf->base, offset, data);
पूर्ण

अटल व्योम nbpf_chan_halt(काष्ठा nbpf_channel *chan)
अणु
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_CLREN);
पूर्ण

अटल bool nbpf_status_get(काष्ठा nbpf_channel *chan)
अणु
	u32 status = nbpf_पढ़ो(chan->nbpf, NBPF_DSTAT_END);

	वापस status & BIT(chan - chan->nbpf->chan);
पूर्ण

अटल व्योम nbpf_status_ack(काष्ठा nbpf_channel *chan)
अणु
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_CLREND);
पूर्ण

अटल u32 nbpf_error_get(काष्ठा nbpf_device *nbpf)
अणु
	वापस nbpf_पढ़ो(nbpf, NBPF_DSTAT_ER);
पूर्ण

अटल काष्ठा nbpf_channel *nbpf_error_get_channel(काष्ठा nbpf_device *nbpf, u32 error)
अणु
	वापस nbpf->chan + __ffs(error);
पूर्ण

अटल व्योम nbpf_error_clear(काष्ठा nbpf_channel *chan)
अणु
	u32 status;
	पूर्णांक i;

	/* Stop the channel, make sure DMA has been पातed */
	nbpf_chan_halt(chan);

	क्रम (i = 1000; i; i--) अणु
		status = nbpf_chan_पढ़ो(chan, NBPF_CHAN_STAT);
		अगर (!(status & NBPF_CHAN_STAT_TACT))
			अवरोध;
		cpu_relax();
	पूर्ण

	अगर (!i)
		dev_err(chan->dma_chan.device->dev,
			"%s(): abort timeout, channel status 0x%x\n", __func__, status);

	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_SWRST);
पूर्ण

अटल पूर्णांक nbpf_start(काष्ठा nbpf_desc *desc)
अणु
	काष्ठा nbpf_channel *chan = desc->chan;
	काष्ठा nbpf_link_desc *ldesc = list_first_entry(&desc->sg, काष्ठा nbpf_link_desc, node);

	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_NXLA, (u32)ldesc->hwdesc_dma_addr);
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_SETEN | NBPF_CHAN_CTRL_CLRSUS);
	chan->छोड़ोd = false;

	/* Software trigger MEMCPY - only MEMCPY uses the block mode */
	अगर (ldesc->hwdesc->config & NBPF_CHAN_CFG_TM)
		nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_STG);

	dev_dbg(chan->nbpf->dma_dev.dev, "%s(): next 0x%x, cur 0x%x\n", __func__,
		nbpf_chan_पढ़ो(chan, NBPF_CHAN_NXLA), nbpf_chan_पढ़ो(chan, NBPF_CHAN_CRLA));

	वापस 0;
पूर्ण

अटल व्योम nbpf_chan_prepare(काष्ठा nbpf_channel *chan)
अणु
	chan->dmarq_cfg = (chan->flags & NBPF_SLAVE_RQ_HIGH ? NBPF_CHAN_CFG_HIEN : 0) |
		(chan->flags & NBPF_SLAVE_RQ_LOW ? NBPF_CHAN_CFG_LOEN : 0) |
		(chan->flags & NBPF_SLAVE_RQ_LEVEL ?
		 NBPF_CHAN_CFG_LVL | (NBPF_CHAN_CFG_AM & 0x200) : 0) |
		chan->terminal;
पूर्ण

अटल व्योम nbpf_chan_prepare_शेष(काष्ठा nbpf_channel *chan)
अणु
	/* Don't output DMAACK */
	chan->dmarq_cfg = NBPF_CHAN_CFG_AM & 0x400;
	chan->terminal = 0;
	chan->flags = 0;
पूर्ण

अटल व्योम nbpf_chan_configure(काष्ठा nbpf_channel *chan)
अणु
	/*
	 * We assume, that only the link mode and DMA request line configuration
	 * have to be set in the configuration रेजिस्टर manually. Dynamic
	 * per-transfer configuration will be loaded from transfer descriptors.
	 */
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CFG, NBPF_CHAN_CFG_DMS | chan->dmarq_cfg);
पूर्ण

अटल u32 nbpf_xfer_ds(काष्ठा nbpf_device *nbpf, माप_प्रकार size,
			क्रमागत dma_transfer_direction direction)
अणु
	पूर्णांक max_burst = nbpf->config->buffer_size * 8;

	अगर (nbpf->max_burst_mem_पढ़ो || nbpf->max_burst_mem_ग_लिखो) अणु
		चयन (direction) अणु
		हाल DMA_MEM_TO_MEM:
			max_burst = min_not_zero(nbpf->max_burst_mem_पढ़ो,
						 nbpf->max_burst_mem_ग_लिखो);
			अवरोध;
		हाल DMA_MEM_TO_DEV:
			अगर (nbpf->max_burst_mem_पढ़ो)
				max_burst = nbpf->max_burst_mem_पढ़ो;
			अवरोध;
		हाल DMA_DEV_TO_MEM:
			अगर (nbpf->max_burst_mem_ग_लिखो)
				max_burst = nbpf->max_burst_mem_ग_लिखो;
			अवरोध;
		हाल DMA_DEV_TO_DEV:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Maximum supported bursts depend on the buffer size */
	वापस min_t(पूर्णांक, __ffs(size), ilog2(max_burst));
पूर्ण

अटल माप_प्रकार nbpf_xfer_size(काष्ठा nbpf_device *nbpf,
			     क्रमागत dma_slave_buswidth width, u32 burst)
अणु
	माप_प्रकार size;

	अगर (!burst)
		burst = 1;

	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		size = 8 * burst;
		अवरोध;

	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		size = 4 * burst;
		अवरोध;

	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		size = 2 * burst;
		अवरोध;

	शेष:
		pr_warn("%s(): invalid bus width %u\n", __func__, width);
		fallthrough;
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		size = burst;
	पूर्ण

	वापस nbpf_xfer_ds(nbpf, size, DMA_TRANS_NONE);
पूर्ण

/*
 * We need a way to recognise slaves, whose data is sent "raw" over the bus,
 * i.e. it isn't known in advance how many bytes will be received. Thereक्रमe
 * the slave driver has to provide a "large enough" buffer and either पढ़ो the
 * buffer, when it is full, or detect, that some data has arrived, then रुको क्रम
 * a समयout, अगर no more data arrives - receive what's alपढ़ोy there. We want to
 * handle such slaves in a special way to allow an optimised mode क्रम other
 * users, क्रम whom the amount of data is known in advance. So far there's no way
 * to recognise such slaves. We use a data-width check to distinguish between
 * the SD host and the PL011 UART.
 */

अटल पूर्णांक nbpf_prep_one(काष्ठा nbpf_link_desc *ldesc,
			 क्रमागत dma_transfer_direction direction,
			 dma_addr_t src, dma_addr_t dst, माप_प्रकार size, bool last)
अणु
	काष्ठा nbpf_link_reg *hwdesc = ldesc->hwdesc;
	काष्ठा nbpf_desc *desc = ldesc->desc;
	काष्ठा nbpf_channel *chan = desc->chan;
	काष्ठा device *dev = chan->dma_chan.device->dev;
	माप_प्रकार mem_xfer, slave_xfer;
	bool can_burst;

	hwdesc->header = NBPF_HEADER_WBD | NBPF_HEADER_LV |
		(last ? NBPF_HEADER_LE : 0);

	hwdesc->src_addr = src;
	hwdesc->dst_addr = dst;
	hwdesc->transaction_size = size;

	/*
	 * set config: SAD, DAD, DDS, SDS, etc.
	 * Note on transfer sizes: the DMAC can perक्रमm unaligned DMA transfers,
	 * but it is important to have transaction size a multiple of both
	 * receiver and transmitter transfer sizes. It is also possible to use
	 * dअगरferent RAM and device transfer sizes, and it करोes work well with
	 * some devices, e.g. with V08R07S01E SD host controllers, which can use
	 * 128 byte transfers. But this करोesn't work with other devices,
	 * especially when the transaction size is unknown. This is the हाल,
	 * e.g. with serial drivers like amba-pl011.c. For reception it sets up
	 * the transaction size of 4K and अगर fewer bytes are received, it
	 * छोड़ोs DMA and पढ़ोs out data received via DMA as well as those left
	 * in the Rx FIFO. For this to work with the RAM side using burst
	 * transfers we enable the SBE bit and terminate the transfer in our
	 * .device_छोड़ो handler.
	 */
	mem_xfer = nbpf_xfer_ds(chan->nbpf, size, direction);

	चयन (direction) अणु
	हाल DMA_DEV_TO_MEM:
		can_burst = chan->slave_src_width >= 3;
		slave_xfer = min(mem_xfer, can_burst ?
				 chan->slave_src_burst : chan->slave_src_width);
		/*
		 * Is the slave narrower than 64 bits, i.e. isn't using the full
		 * bus width and cannot use bursts?
		 */
		अगर (mem_xfer > chan->slave_src_burst && !can_burst)
			mem_xfer = chan->slave_src_burst;
		/* Device-to-RAM DMA is unreliable without REQD set */
		hwdesc->config = NBPF_CHAN_CFG_SAD | (NBPF_CHAN_CFG_DDS & (mem_xfer << 16)) |
			(NBPF_CHAN_CFG_SDS & (slave_xfer << 12)) | NBPF_CHAN_CFG_REQD |
			NBPF_CHAN_CFG_SBE;
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		slave_xfer = min(mem_xfer, chan->slave_dst_width >= 3 ?
				 chan->slave_dst_burst : chan->slave_dst_width);
		hwdesc->config = NBPF_CHAN_CFG_DAD | (NBPF_CHAN_CFG_SDS & (mem_xfer << 12)) |
			(NBPF_CHAN_CFG_DDS & (slave_xfer << 16)) | NBPF_CHAN_CFG_REQD;
		अवरोध;

	हाल DMA_MEM_TO_MEM:
		hwdesc->config = NBPF_CHAN_CFG_TCM | NBPF_CHAN_CFG_TM |
			(NBPF_CHAN_CFG_SDS & (mem_xfer << 12)) |
			(NBPF_CHAN_CFG_DDS & (mem_xfer << 16));
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	hwdesc->config |= chan->dmarq_cfg | (last ? 0 : NBPF_CHAN_CFG_DEM) |
		NBPF_CHAN_CFG_DMS;

	dev_dbg(dev, "%s(): desc @ %pad: hdr 0x%x, cfg 0x%x, %zu @ %pad -> %pad\n",
		__func__, &ldesc->hwdesc_dma_addr, hwdesc->header,
		hwdesc->config, size, &src, &dst);

	dma_sync_single_क्रम_device(dev, ldesc->hwdesc_dma_addr, माप(*hwdesc),
				   DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल माप_प्रकार nbpf_bytes_left(काष्ठा nbpf_channel *chan)
अणु
	वापस nbpf_chan_पढ़ो(chan, NBPF_CHAN_CUR_TR_BYTE);
पूर्ण

अटल व्योम nbpf_configure(काष्ठा nbpf_device *nbpf)
अणु
	nbpf_ग_लिखो(nbpf, NBPF_CTRL, NBPF_CTRL_LVINT);
पूर्ण

/*		Generic part			*/

/* DMA ENGINE functions */
अटल व्योम nbpf_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	अचिन्हित दीर्घ flags;

	dev_dbg(dchan->device->dev, "Entry %s()\n", __func__);

	spin_lock_irqsave(&chan->lock, flags);
	अगर (list_empty(&chan->queued))
		जाओ unlock;

	list_splice_tail_init(&chan->queued, &chan->active);

	अगर (!chan->running) अणु
		काष्ठा nbpf_desc *desc = list_first_entry(&chan->active,
						काष्ठा nbpf_desc, node);
		अगर (!nbpf_start(desc))
			chan->running = desc;
	पूर्ण

unlock:
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल क्रमागत dma_status nbpf_tx_status(काष्ठा dma_chan *dchan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	क्रमागत dma_status status = dma_cookie_status(dchan, cookie, state);

	अगर (state) अणु
		dma_cookie_t running;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&chan->lock, flags);
		running = chan->running ? chan->running->async_tx.cookie : -EINVAL;

		अगर (cookie == running) अणु
			state->residue = nbpf_bytes_left(chan);
			dev_dbg(dchan->device->dev, "%s(): residue %u\n", __func__,
				state->residue);
		पूर्ण अन्यथा अगर (status == DMA_IN_PROGRESS) अणु
			काष्ठा nbpf_desc *desc;
			bool found = false;

			list_क्रम_each_entry(desc, &chan->active, node)
				अगर (desc->async_tx.cookie == cookie) अणु
					found = true;
					अवरोध;
				पूर्ण

			अगर (!found)
				list_क्रम_each_entry(desc, &chan->queued, node)
					अगर (desc->async_tx.cookie == cookie) अणु
						found = true;
						अवरोध;

					पूर्ण

			state->residue = found ? desc->length : 0;
		पूर्ण

		spin_unlock_irqrestore(&chan->lock, flags);
	पूर्ण

	अगर (chan->छोड़ोd)
		status = DMA_PAUSED;

	वापस status;
पूर्ण

अटल dma_cookie_t nbpf_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा nbpf_desc *desc = container_of(tx, काष्ठा nbpf_desc, async_tx);
	काष्ठा nbpf_channel *chan = desc->chan;
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&chan->lock, flags);
	cookie = dma_cookie_assign(tx);
	list_add_tail(&desc->node, &chan->queued);
	spin_unlock_irqrestore(&chan->lock, flags);

	dev_dbg(chan->dma_chan.device->dev, "Entry %s(%d)\n", __func__, cookie);

	वापस cookie;
पूर्ण

अटल पूर्णांक nbpf_desc_page_alloc(काष्ठा nbpf_channel *chan)
अणु
	काष्ठा dma_chan *dchan = &chan->dma_chan;
	काष्ठा nbpf_desc_page *dpage = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	काष्ठा nbpf_link_desc *ldesc;
	काष्ठा nbpf_link_reg *hwdesc;
	काष्ठा nbpf_desc *desc;
	LIST_HEAD(head);
	LIST_HEAD(lhead);
	पूर्णांक i;
	काष्ठा device *dev = dchan->device->dev;

	अगर (!dpage)
		वापस -ENOMEM;

	dev_dbg(dev, "%s(): alloc %lu descriptors, %lu segments, total alloc %zu\n",
		__func__, NBPF_DESCS_PER_PAGE, NBPF_SEGMENTS_PER_PAGE, माप(*dpage));

	क्रम (i = 0, ldesc = dpage->ldesc, hwdesc = dpage->hwdesc;
	     i < ARRAY_SIZE(dpage->ldesc);
	     i++, ldesc++, hwdesc++) अणु
		ldesc->hwdesc = hwdesc;
		list_add_tail(&ldesc->node, &lhead);
		ldesc->hwdesc_dma_addr = dma_map_single(dchan->device->dev,
					hwdesc, माप(*hwdesc), DMA_TO_DEVICE);

		dev_dbg(dev, "%s(): mapped 0x%p to %pad\n", __func__,
			hwdesc, &ldesc->hwdesc_dma_addr);
	पूर्ण

	क्रम (i = 0, desc = dpage->desc;
	     i < ARRAY_SIZE(dpage->desc);
	     i++, desc++) अणु
		dma_async_tx_descriptor_init(&desc->async_tx, dchan);
		desc->async_tx.tx_submit = nbpf_tx_submit;
		desc->chan = chan;
		INIT_LIST_HEAD(&desc->sg);
		list_add_tail(&desc->node, &head);
	पूर्ण

	/*
	 * This function cannot be called from पूर्णांकerrupt context, so, no need to
	 * save flags
	 */
	spin_lock_irq(&chan->lock);
	list_splice_tail(&lhead, &chan->मुक्त_links);
	list_splice_tail(&head, &chan->मुक्त);
	list_add(&dpage->node, &chan->desc_page);
	spin_unlock_irq(&chan->lock);

	वापस ARRAY_SIZE(dpage->desc);
पूर्ण

अटल व्योम nbpf_desc_put(काष्ठा nbpf_desc *desc)
अणु
	काष्ठा nbpf_channel *chan = desc->chan;
	काष्ठा nbpf_link_desc *ldesc, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	list_क्रम_each_entry_safe(ldesc, पंचांगp, &desc->sg, node)
		list_move(&ldesc->node, &chan->मुक्त_links);

	list_add(&desc->node, &chan->मुक्त);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल व्योम nbpf_scan_acked(काष्ठा nbpf_channel *chan)
अणु
	काष्ठा nbpf_desc *desc, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->lock, flags);
	list_क्रम_each_entry_safe(desc, पंचांगp, &chan->करोne, node)
		अगर (async_tx_test_ack(&desc->async_tx) && desc->user_रुको) अणु
			list_move(&desc->node, &head);
			desc->user_रुको = false;
		पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);

	list_क्रम_each_entry_safe(desc, पंचांगp, &head, node) अणु
		list_del(&desc->node);
		nbpf_desc_put(desc);
	पूर्ण
पूर्ण

/*
 * We have to allocate descriptors with the channel lock dropped. This means,
 * beक्रमe we re-acquire the lock buffers can be taken alपढ़ोy, so we have to
 * re-check after re-acquiring the lock and possibly retry, अगर buffers are gone
 * again.
 */
अटल काष्ठा nbpf_desc *nbpf_desc_get(काष्ठा nbpf_channel *chan, माप_प्रकार len)
अणु
	काष्ठा nbpf_desc *desc = शून्य;
	काष्ठा nbpf_link_desc *ldesc, *prev = शून्य;

	nbpf_scan_acked(chan);

	spin_lock_irq(&chan->lock);

	करो अणु
		पूर्णांक i = 0, ret;

		अगर (list_empty(&chan->मुक्त)) अणु
			/* No more मुक्त descriptors */
			spin_unlock_irq(&chan->lock);
			ret = nbpf_desc_page_alloc(chan);
			अगर (ret < 0)
				वापस शून्य;
			spin_lock_irq(&chan->lock);
			जारी;
		पूर्ण
		desc = list_first_entry(&chan->मुक्त, काष्ठा nbpf_desc, node);
		list_del(&desc->node);

		करो अणु
			अगर (list_empty(&chan->मुक्त_links)) अणु
				/* No more मुक्त link descriptors */
				spin_unlock_irq(&chan->lock);
				ret = nbpf_desc_page_alloc(chan);
				अगर (ret < 0) अणु
					nbpf_desc_put(desc);
					वापस शून्य;
				पूर्ण
				spin_lock_irq(&chan->lock);
				जारी;
			पूर्ण

			ldesc = list_first_entry(&chan->मुक्त_links,
						 काष्ठा nbpf_link_desc, node);
			ldesc->desc = desc;
			अगर (prev)
				prev->hwdesc->next = (u32)ldesc->hwdesc_dma_addr;

			prev = ldesc;
			list_move_tail(&ldesc->node, &desc->sg);

			i++;
		पूर्ण जबतक (i < len);
	पूर्ण जबतक (!desc);

	prev->hwdesc->next = 0;

	spin_unlock_irq(&chan->lock);

	वापस desc;
पूर्ण

अटल व्योम nbpf_chan_idle(काष्ठा nbpf_channel *chan)
अणु
	काष्ठा nbpf_desc *desc, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->lock, flags);

	list_splice_init(&chan->करोne, &head);
	list_splice_init(&chan->active, &head);
	list_splice_init(&chan->queued, &head);

	chan->running = शून्य;

	spin_unlock_irqrestore(&chan->lock, flags);

	list_क्रम_each_entry_safe(desc, पंचांगp, &head, node) अणु
		dev_dbg(chan->nbpf->dma_dev.dev, "%s(): force-free desc %p cookie %d\n",
			__func__, desc, desc->async_tx.cookie);
		list_del(&desc->node);
		nbpf_desc_put(desc);
	पूर्ण
पूर्ण

अटल पूर्णांक nbpf_छोड़ो(काष्ठा dma_chan *dchan)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entry %s\n", __func__);

	chan->छोड़ोd = true;
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_SETSUS);
	/* See comment in nbpf_prep_one() */
	nbpf_chan_ग_लिखो(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_CLREN);

	वापस 0;
पूर्ण

अटल पूर्णांक nbpf_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entry %s\n", __func__);
	dev_dbg(dchan->device->dev, "Terminating\n");

	nbpf_chan_halt(chan);
	nbpf_chan_idle(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक nbpf_config(काष्ठा dma_chan *dchan,
		       काष्ठा dma_slave_config *config)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entry %s\n", __func__);

	/*
	 * We could check config->slave_id to match chan->terminal here,
	 * but with DT they would be coming from the same source, so
	 * such a check would be superflous
	 */

	chan->slave_dst_addr = config->dst_addr;
	chan->slave_dst_width = nbpf_xfer_size(chan->nbpf,
					       config->dst_addr_width, 1);
	chan->slave_dst_burst = nbpf_xfer_size(chan->nbpf,
					       config->dst_addr_width,
					       config->dst_maxburst);
	chan->slave_src_addr = config->src_addr;
	chan->slave_src_width = nbpf_xfer_size(chan->nbpf,
					       config->src_addr_width, 1);
	chan->slave_src_burst = nbpf_xfer_size(chan->nbpf,
					       config->src_addr_width,
					       config->src_maxburst);

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *nbpf_prep_sg(काष्ठा nbpf_channel *chan,
		काष्ठा scatterlist *src_sg, काष्ठा scatterlist *dst_sg,
		माप_प्रकार len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा nbpf_link_desc *ldesc;
	काष्ठा scatterlist *mem_sg;
	काष्ठा nbpf_desc *desc;
	bool inc_src, inc_dst;
	माप_प्रकार data_len = 0;
	पूर्णांक i = 0;

	चयन (direction) अणु
	हाल DMA_DEV_TO_MEM:
		mem_sg = dst_sg;
		inc_src = false;
		inc_dst = true;
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		mem_sg = src_sg;
		inc_src = true;
		inc_dst = false;
		अवरोध;

	शेष:
	हाल DMA_MEM_TO_MEM:
		mem_sg = src_sg;
		inc_src = true;
		inc_dst = true;
	पूर्ण

	desc = nbpf_desc_get(chan, len);
	अगर (!desc)
		वापस शून्य;

	desc->async_tx.flags = flags;
	desc->async_tx.cookie = -EBUSY;
	desc->user_रुको = false;

	/*
	 * This is a निजी descriptor list, and we own the descriptor. No need
	 * to lock.
	 */
	list_क्रम_each_entry(ldesc, &desc->sg, node) अणु
		पूर्णांक ret = nbpf_prep_one(ldesc, direction,
					sg_dma_address(src_sg),
					sg_dma_address(dst_sg),
					sg_dma_len(mem_sg),
					i == len - 1);
		अगर (ret < 0) अणु
			nbpf_desc_put(desc);
			वापस शून्य;
		पूर्ण
		data_len += sg_dma_len(mem_sg);
		अगर (inc_src)
			src_sg = sg_next(src_sg);
		अगर (inc_dst)
			dst_sg = sg_next(dst_sg);
		mem_sg = direction == DMA_DEV_TO_MEM ? dst_sg : src_sg;
		i++;
	पूर्ण

	desc->length = data_len;

	/* The user has to वापस the descriptor to us ASAP via .tx_submit() */
	वापस &desc->async_tx;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *nbpf_prep_स_नकल(
	काष्ठा dma_chan *dchan, dma_addr_t dst, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	काष्ठा scatterlist dst_sg;
	काष्ठा scatterlist src_sg;

	sg_init_table(&dst_sg, 1);
	sg_init_table(&src_sg, 1);

	sg_dma_address(&dst_sg) = dst;
	sg_dma_address(&src_sg) = src;

	sg_dma_len(&dst_sg) = len;
	sg_dma_len(&src_sg) = len;

	dev_dbg(dchan->device->dev, "%s(): %zu @ %pad -> %pad\n",
		__func__, len, &src, &dst);

	वापस nbpf_prep_sg(chan, &src_sg, &dst_sg, 1,
			    DMA_MEM_TO_MEM, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *nbpf_prep_slave_sg(
	काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	काष्ठा scatterlist slave_sg;

	dev_dbg(dchan->device->dev, "Entry %s()\n", __func__);

	sg_init_table(&slave_sg, 1);

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		sg_dma_address(&slave_sg) = chan->slave_dst_addr;
		वापस nbpf_prep_sg(chan, sgl, &slave_sg, sg_len,
				    direction, flags);

	हाल DMA_DEV_TO_MEM:
		sg_dma_address(&slave_sg) = chan->slave_src_addr;
		वापस nbpf_prep_sg(chan, &slave_sg, sgl, sg_len,
				    direction, flags);

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक nbpf_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	पूर्णांक ret;

	INIT_LIST_HEAD(&chan->मुक्त);
	INIT_LIST_HEAD(&chan->मुक्त_links);
	INIT_LIST_HEAD(&chan->queued);
	INIT_LIST_HEAD(&chan->active);
	INIT_LIST_HEAD(&chan->करोne);

	ret = nbpf_desc_page_alloc(chan);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dchan->device->dev, "Entry %s(): terminal %u\n", __func__,
		chan->terminal);

	nbpf_chan_configure(chan);

	वापस ret;
पूर्ण

अटल व्योम nbpf_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा nbpf_channel *chan = nbpf_to_chan(dchan);
	काष्ठा nbpf_desc_page *dpage, *पंचांगp;

	dev_dbg(dchan->device->dev, "Entry %s()\n", __func__);

	nbpf_chan_halt(chan);
	nbpf_chan_idle(chan);
	/* Clean up क्रम अगर a channel is re-used क्रम MEMCPY after slave DMA */
	nbpf_chan_prepare_शेष(chan);

	list_क्रम_each_entry_safe(dpage, पंचांगp, &chan->desc_page, node) अणु
		काष्ठा nbpf_link_desc *ldesc;
		पूर्णांक i;
		list_del(&dpage->node);
		क्रम (i = 0, ldesc = dpage->ldesc;
		     i < ARRAY_SIZE(dpage->ldesc);
		     i++, ldesc++)
			dma_unmap_single(dchan->device->dev, ldesc->hwdesc_dma_addr,
					 माप(*ldesc->hwdesc), DMA_TO_DEVICE);
		मुक्त_page((अचिन्हित दीर्घ)dpage);
	पूर्ण
पूर्ण

अटल काष्ठा dma_chan *nbpf_of_xlate(काष्ठा of_phandle_args *dma_spec,
				      काष्ठा of_dma *ofdma)
अणु
	काष्ठा nbpf_device *nbpf = ofdma->of_dma_data;
	काष्ठा dma_chan *dchan;
	काष्ठा nbpf_channel *chan;

	अगर (dma_spec->args_count != 2)
		वापस शून्य;

	dchan = dma_get_any_slave_channel(&nbpf->dma_dev);
	अगर (!dchan)
		वापस शून्य;

	dev_dbg(dchan->device->dev, "Entry %s(%pOFn)\n", __func__,
		dma_spec->np);

	chan = nbpf_to_chan(dchan);

	chan->terminal = dma_spec->args[0];
	chan->flags = dma_spec->args[1];

	nbpf_chan_prepare(chan);
	nbpf_chan_configure(chan);

	वापस dchan;
पूर्ण

अटल व्योम nbpf_chan_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा nbpf_channel *chan = from_tasklet(chan, t, tasklet);
	काष्ठा nbpf_desc *desc, *पंचांगp;
	काष्ठा dmaengine_desc_callback cb;

	जबतक (!list_empty(&chan->करोne)) अणु
		bool found = false, must_put, recycling = false;

		spin_lock_irq(&chan->lock);

		list_क्रम_each_entry_safe(desc, पंचांगp, &chan->करोne, node) अणु
			अगर (!desc->user_रुको) अणु
				/* Newly completed descriptor, have to process */
				found = true;
				अवरोध;
			पूर्ण अन्यथा अगर (async_tx_test_ack(&desc->async_tx)) अणु
				/*
				 * This descriptor was रुकोing क्रम a user ACK,
				 * it can be recycled now.
				 */
				list_del(&desc->node);
				spin_unlock_irq(&chan->lock);
				nbpf_desc_put(desc);
				recycling = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (recycling)
			जारी;

		अगर (!found) अणु
			/* This can happen अगर TERMINATE_ALL has been called */
			spin_unlock_irq(&chan->lock);
			अवरोध;
		पूर्ण

		dma_cookie_complete(&desc->async_tx);

		/*
		 * With released lock we cannot dereference desc, maybe it's
		 * still on the "done" list
		 */
		अगर (async_tx_test_ack(&desc->async_tx)) अणु
			list_del(&desc->node);
			must_put = true;
		पूर्ण अन्यथा अणु
			desc->user_रुको = true;
			must_put = false;
		पूर्ण

		dmaengine_desc_get_callback(&desc->async_tx, &cb);

		/* ack and callback completed descriptor */
		spin_unlock_irq(&chan->lock);

		dmaengine_desc_callback_invoke(&cb, शून्य);

		अगर (must_put)
			nbpf_desc_put(desc);
	पूर्ण
पूर्ण

अटल irqवापस_t nbpf_chan_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा nbpf_channel *chan = dev;
	bool करोne = nbpf_status_get(chan);
	काष्ठा nbpf_desc *desc;
	irqवापस_t ret;
	bool bh = false;

	अगर (!करोne)
		वापस IRQ_NONE;

	nbpf_status_ack(chan);

	dev_dbg(&chan->dma_chan.dev->device, "%s()\n", __func__);

	spin_lock(&chan->lock);
	desc = chan->running;
	अगर (WARN_ON(!desc)) अणु
		ret = IRQ_NONE;
		जाओ unlock;
	पूर्ण अन्यथा अणु
		ret = IRQ_HANDLED;
		bh = true;
	पूर्ण

	list_move_tail(&desc->node, &chan->करोne);
	chan->running = शून्य;

	अगर (!list_empty(&chan->active)) अणु
		desc = list_first_entry(&chan->active,
					काष्ठा nbpf_desc, node);
		अगर (!nbpf_start(desc))
			chan->running = desc;
	पूर्ण

unlock:
	spin_unlock(&chan->lock);

	अगर (bh)
		tasklet_schedule(&chan->tasklet);

	वापस ret;
पूर्ण

अटल irqवापस_t nbpf_err_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा nbpf_device *nbpf = dev;
	u32 error = nbpf_error_get(nbpf);

	dev_warn(nbpf->dma_dev.dev, "DMA error IRQ %u\n", irq);

	अगर (!error)
		वापस IRQ_NONE;

	करो अणु
		काष्ठा nbpf_channel *chan = nbpf_error_get_channel(nbpf, error);
		/* On error: पात all queued transfers, no callback */
		nbpf_error_clear(chan);
		nbpf_chan_idle(chan);
		error = nbpf_error_get(nbpf);
	पूर्ण जबतक (error);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nbpf_chan_probe(काष्ठा nbpf_device *nbpf, पूर्णांक n)
अणु
	काष्ठा dma_device *dma_dev = &nbpf->dma_dev;
	काष्ठा nbpf_channel *chan = nbpf->chan + n;
	पूर्णांक ret;

	chan->nbpf = nbpf;
	chan->base = nbpf->base + NBPF_REG_CHAN_OFFSET + NBPF_REG_CHAN_SIZE * n;
	INIT_LIST_HEAD(&chan->desc_page);
	spin_lock_init(&chan->lock);
	chan->dma_chan.device = dma_dev;
	dma_cookie_init(&chan->dma_chan);
	nbpf_chan_prepare_शेष(chan);

	dev_dbg(dma_dev->dev, "%s(): channel %d: -> %p\n", __func__, n, chan->base);

	snम_लिखो(chan->name, माप(chan->name), "nbpf %d", n);

	tasklet_setup(&chan->tasklet, nbpf_chan_tasklet);
	ret = devm_request_irq(dma_dev->dev, chan->irq,
			nbpf_chan_irq, IRQF_SHARED,
			chan->name, chan);
	अगर (ret < 0)
		वापस ret;

	/* Add the channel to DMA device channel list */
	list_add_tail(&chan->dma_chan.device_node,
		      &dma_dev->channels);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nbpf_match[] = अणु
	अणु.compatible = "renesas,nbpfaxi64dmac1b4",	.data = &nbpf_cfg[NBPF1B4]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac1b8",	.data = &nbpf_cfg[NBPF1B8]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac1b16",	.data = &nbpf_cfg[NBPF1B16]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac4b4",	.data = &nbpf_cfg[NBPF4B4]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac4b8",	.data = &nbpf_cfg[NBPF4B8]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac4b16",	.data = &nbpf_cfg[NBPF4B16]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac8b4",	.data = &nbpf_cfg[NBPF8B4]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac8b8",	.data = &nbpf_cfg[NBPF8B8]पूर्ण,
	अणु.compatible = "renesas,nbpfaxi64dmac8b16",	.data = &nbpf_cfg[NBPF8B16]पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nbpf_match);

अटल पूर्णांक nbpf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा nbpf_device *nbpf;
	काष्ठा dma_device *dma_dev;
	काष्ठा resource *iomem, *irq_res;
	स्थिर काष्ठा nbpf_config *cfg;
	पूर्णांक num_channels;
	पूर्णांक ret, irq, eirq, i;
	पूर्णांक irqbuf[9] /* maximum 8 channels + error IRQ */;
	अचिन्हित पूर्णांक irqs = 0;

	BUILD_BUG_ON(माप(काष्ठा nbpf_desc_page) > PAGE_SIZE);

	/* DT only */
	अगर (!np)
		वापस -ENODEV;

	cfg = of_device_get_match_data(dev);
	num_channels = cfg->num_channels;

	nbpf = devm_kzalloc(dev, काष्ठा_size(nbpf, chan, num_channels),
			    GFP_KERNEL);
	अगर (!nbpf)
		वापस -ENOMEM;

	dma_dev = &nbpf->dma_dev;
	dma_dev->dev = dev;

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nbpf->base = devm_ioremap_resource(dev, iomem);
	अगर (IS_ERR(nbpf->base))
		वापस PTR_ERR(nbpf->base);

	nbpf->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(nbpf->clk))
		वापस PTR_ERR(nbpf->clk);

	of_property_पढ़ो_u32(np, "max-burst-mem-read",
			     &nbpf->max_burst_mem_पढ़ो);
	of_property_पढ़ो_u32(np, "max-burst-mem-write",
			     &nbpf->max_burst_mem_ग_लिखो);

	nbpf->config = cfg;

	क्रम (i = 0; irqs < ARRAY_SIZE(irqbuf); i++) अणु
		irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		अगर (!irq_res)
			अवरोध;

		क्रम (irq = irq_res->start; irq <= irq_res->end;
		     irq++, irqs++)
			irqbuf[irqs] = irq;
	पूर्ण

	/*
	 * 3 IRQ resource schemes are supported:
	 * 1. 1 shared IRQ क्रम error and all channels
	 * 2. 2 IRQs: one क्रम error and one shared क्रम all channels
	 * 3. 1 IRQ क्रम error and an own IRQ क्रम each channel
	 */
	अगर (irqs != 1 && irqs != 2 && irqs != num_channels + 1)
		वापस -ENXIO;

	अगर (irqs == 1) अणु
		eirq = irqbuf[0];

		क्रम (i = 0; i <= num_channels; i++)
			nbpf->chan[i].irq = irqbuf[0];
	पूर्ण अन्यथा अणु
		eirq = platक्रमm_get_irq_byname(pdev, "error");
		अगर (eirq < 0)
			वापस eirq;

		अगर (irqs == num_channels + 1) अणु
			काष्ठा nbpf_channel *chan;

			क्रम (i = 0, chan = nbpf->chan; i <= num_channels;
			     i++, chan++) अणु
				/* Skip the error IRQ */
				अगर (irqbuf[i] == eirq)
					i++;
				chan->irq = irqbuf[i];
			पूर्ण

			अगर (chan != nbpf->chan + num_channels)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* 2 IRQs and more than one channel */
			अगर (irqbuf[0] == eirq)
				irq = irqbuf[1];
			अन्यथा
				irq = irqbuf[0];

			क्रम (i = 0; i <= num_channels; i++)
				nbpf->chan[i].irq = irq;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(dev, eirq, nbpf_err_irq,
			       IRQF_SHARED, "dma error", nbpf);
	अगर (ret < 0)
		वापस ret;
	nbpf->eirq = eirq;

	INIT_LIST_HEAD(&dma_dev->channels);

	/* Create DMA Channel */
	क्रम (i = 0; i < num_channels; i++) अणु
		ret = nbpf_chan_probe(nbpf, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_PRIVATE, dma_dev->cap_mask);

	/* Common and MEMCPY operations */
	dma_dev->device_alloc_chan_resources
		= nbpf_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = nbpf_मुक्त_chan_resources;
	dma_dev->device_prep_dma_स_नकल = nbpf_prep_स_नकल;
	dma_dev->device_tx_status = nbpf_tx_status;
	dma_dev->device_issue_pending = nbpf_issue_pending;

	/*
	 * If we drop support क्रम unaligned MEMCPY buffer addresses and / or
	 * lengths by setting
	 * dma_dev->copy_align = 4;
	 * then we can set transfer length to 4 bytes in nbpf_prep_one() क्रम
	 * DMA_MEM_TO_MEM
	 */

	/* Compulsory क्रम DMA_SLAVE fields */
	dma_dev->device_prep_slave_sg = nbpf_prep_slave_sg;
	dma_dev->device_config = nbpf_config;
	dma_dev->device_छोड़ो = nbpf_छोड़ो;
	dma_dev->device_terminate_all = nbpf_terminate_all;

	dma_dev->src_addr_widths = NBPF_DMA_BUSWIDTHS;
	dma_dev->dst_addr_widths = NBPF_DMA_BUSWIDTHS;
	dma_dev->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	platक्रमm_set_drvdata(pdev, nbpf);

	ret = clk_prepare_enable(nbpf->clk);
	अगर (ret < 0)
		वापस ret;

	nbpf_configure(nbpf);

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret < 0)
		जाओ e_clk_off;

	ret = of_dma_controller_रेजिस्टर(np, nbpf_of_xlate, nbpf);
	अगर (ret < 0)
		जाओ e_dma_dev_unreg;

	वापस 0;

e_dma_dev_unreg:
	dma_async_device_unरेजिस्टर(dma_dev);
e_clk_off:
	clk_disable_unprepare(nbpf->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक nbpf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nbpf_device *nbpf = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	devm_मुक्त_irq(&pdev->dev, nbpf->eirq, nbpf);

	क्रम (i = 0; i < nbpf->config->num_channels; i++) अणु
		काष्ठा nbpf_channel *chan = nbpf->chan + i;

		devm_मुक्त_irq(&pdev->dev, chan->irq, chan);

		tasklet_समाप्त(&chan->tasklet);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&nbpf->dma_dev);
	clk_disable_unprepare(nbpf->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id nbpf_ids[] = अणु
	अणु"nbpfaxi64dmac1b4",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF1B4]पूर्ण,
	अणु"nbpfaxi64dmac1b8",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF1B8]पूर्ण,
	अणु"nbpfaxi64dmac1b16",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF1B16]पूर्ण,
	अणु"nbpfaxi64dmac4b4",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF4B4]पूर्ण,
	अणु"nbpfaxi64dmac4b8",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF4B8]पूर्ण,
	अणु"nbpfaxi64dmac4b16",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF4B16]पूर्ण,
	अणु"nbpfaxi64dmac8b4",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF8B4]पूर्ण,
	अणु"nbpfaxi64dmac8b8",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF8B8]पूर्ण,
	अणु"nbpfaxi64dmac8b16",	(kernel_uदीर्घ_t)&nbpf_cfg[NBPF8B16]पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, nbpf_ids);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nbpf_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा nbpf_device *nbpf = dev_get_drvdata(dev);
	clk_disable_unprepare(nbpf->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक nbpf_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा nbpf_device *nbpf = dev_get_drvdata(dev);
	वापस clk_prepare_enable(nbpf->clk);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops nbpf_pm_ops = अणु
	SET_RUNTIME_PM_OPS(nbpf_runसमय_suspend, nbpf_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver nbpf_driver = अणु
	.driver = अणु
		.name = "dma-nbpf",
		.of_match_table = nbpf_match,
		.pm = &nbpf_pm_ops,
	पूर्ण,
	.id_table = nbpf_ids,
	.probe = nbpf_probe,
	.हटाओ = nbpf_हटाओ,
पूर्ण;

module_platक्रमm_driver(nbpf_driver);

MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_DESCRIPTION("dmaengine driver for NBPFAXI64* DMACs");
MODULE_LICENSE("GPL v2");
