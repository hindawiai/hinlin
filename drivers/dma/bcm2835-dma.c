<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * BCM2835 DMA engine support
 *
 * Author:      Florian Meier <florian.meier@koalo.de>
 *              Copyright 2013
 *
 * Based on
 *	OMAP DMAengine support by Russell King
 *
 *	BCM2708 DMA Driver
 *	Copyright (C) 2010 Broadcom
 *
 *	Raspberry Pi PCM I2S ALSA Driver
 *	Copyright (c) by Phil Poole 2013
 *
 *	MARVELL MMP Peripheral DMA Driver
 *	Copyright 2012 Marvell International Ltd.
 */
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>

#समावेश "virt-dma.h"

#घोषणा BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED 14
#घोषणा BCM2835_DMA_CHAN_NAME_SIZE 8

/**
 * काष्ठा bcm2835_dmadev - BCM2835 DMA controller
 * @ddev: DMA device
 * @base: base address of रेजिस्टर map
 * @zero_page: bus address of zero page (to detect transactions copying from
 *	zero page and aव्योम accessing memory अगर so)
 */
काष्ठा bcm2835_dmadev अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *base;
	dma_addr_t zero_page;
पूर्ण;

काष्ठा bcm2835_dma_cb अणु
	uपूर्णांक32_t info;
	uपूर्णांक32_t src;
	uपूर्णांक32_t dst;
	uपूर्णांक32_t length;
	uपूर्णांक32_t stride;
	uपूर्णांक32_t next;
	uपूर्णांक32_t pad[2];
पूर्ण;

काष्ठा bcm2835_cb_entry अणु
	काष्ठा bcm2835_dma_cb *cb;
	dma_addr_t paddr;
पूर्ण;

काष्ठा bcm2835_chan अणु
	काष्ठा virt_dma_chan vc;

	काष्ठा dma_slave_config	cfg;
	अचिन्हित पूर्णांक dreq;

	पूर्णांक ch;
	काष्ठा bcm2835_desc *desc;
	काष्ठा dma_pool *cb_pool;

	व्योम __iomem *chan_base;
	पूर्णांक irq_number;
	अचिन्हित पूर्णांक irq_flags;

	bool is_lite_channel;
पूर्ण;

काष्ठा bcm2835_desc अणु
	काष्ठा bcm2835_chan *c;
	काष्ठा virt_dma_desc vd;
	क्रमागत dma_transfer_direction dir;

	अचिन्हित पूर्णांक frames;
	माप_प्रकार size;

	bool cyclic;

	काष्ठा bcm2835_cb_entry cb_list[];
पूर्ण;

#घोषणा BCM2835_DMA_CS		0x00
#घोषणा BCM2835_DMA_ADDR	0x04
#घोषणा BCM2835_DMA_TI		0x08
#घोषणा BCM2835_DMA_SOURCE_AD	0x0c
#घोषणा BCM2835_DMA_DEST_AD	0x10
#घोषणा BCM2835_DMA_LEN		0x14
#घोषणा BCM2835_DMA_STRIDE	0x18
#घोषणा BCM2835_DMA_NEXTCB	0x1c
#घोषणा BCM2835_DMA_DEBUG	0x20

/* DMA CS Control and Status bits */
#घोषणा BCM2835_DMA_ACTIVE	BIT(0)  /* activate the DMA */
#घोषणा BCM2835_DMA_END		BIT(1)  /* current CB has ended */
#घोषणा BCM2835_DMA_INT		BIT(2)  /* पूर्णांकerrupt status */
#घोषणा BCM2835_DMA_DREQ	BIT(3)  /* DREQ state */
#घोषणा BCM2835_DMA_ISPAUSED	BIT(4)  /* Pause requested or not active */
#घोषणा BCM2835_DMA_ISHELD	BIT(5)  /* Is held by DREQ flow control */
#घोषणा BCM2835_DMA_WAITING_FOR_WRITES BIT(6) /* रुकोing क्रम last
					       * AXI-ग_लिखो to ack
					       */
#घोषणा BCM2835_DMA_ERR		BIT(8)
#घोषणा BCM2835_DMA_PRIORITY(x) ((x & 15) << 16) /* AXI priority */
#घोषणा BCM2835_DMA_PANIC_PRIORITY(x) ((x & 15) << 20) /* panic priority */
/* current value of TI.BCM2835_DMA_WAIT_RESP */
#घोषणा BCM2835_DMA_WAIT_FOR_WRITES BIT(28)
#घोषणा BCM2835_DMA_DIS_DEBUG	BIT(29) /* disable debug छोड़ो संकेत */
#घोषणा BCM2835_DMA_ABORT	BIT(30) /* Stop current CB, go to next, WO */
#घोषणा BCM2835_DMA_RESET	BIT(31) /* WO, self clearing */

/* Transfer inक्रमmation bits - also bcm2835_cb.info field */
#घोषणा BCM2835_DMA_INT_EN	BIT(0)
#घोषणा BCM2835_DMA_TDMODE	BIT(1) /* 2D-Mode */
#घोषणा BCM2835_DMA_WAIT_RESP	BIT(3) /* रुको क्रम AXI-ग_लिखो to be acked */
#घोषणा BCM2835_DMA_D_INC	BIT(4)
#घोषणा BCM2835_DMA_D_WIDTH	BIT(5) /* 128bit ग_लिखोs अगर set */
#घोषणा BCM2835_DMA_D_DREQ	BIT(6) /* enable DREQ क्रम destination */
#घोषणा BCM2835_DMA_D_IGNORE	BIT(7) /* ignore destination ग_लिखोs */
#घोषणा BCM2835_DMA_S_INC	BIT(8)
#घोषणा BCM2835_DMA_S_WIDTH	BIT(9) /* 128bit ग_लिखोs अगर set */
#घोषणा BCM2835_DMA_S_DREQ	BIT(10) /* enable SREQ क्रम source */
#घोषणा BCM2835_DMA_S_IGNORE	BIT(11) /* ignore source पढ़ोs - पढ़ो 0 */
#घोषणा BCM2835_DMA_BURST_LENGTH(x) ((x & 15) << 12)
#घोषणा BCM2835_DMA_PER_MAP(x)	((x & 31) << 16) /* REQ source */
#घोषणा BCM2835_DMA_WAIT(x)	((x & 31) << 21) /* add DMA-रुको cycles */
#घोषणा BCM2835_DMA_NO_WIDE_BURSTS BIT(26) /* no 2 beat ग_लिखो bursts */

/* debug रेजिस्टर bits */
#घोषणा BCM2835_DMA_DEBUG_LAST_NOT_SET_ERR	BIT(0)
#घोषणा BCM2835_DMA_DEBUG_FIFO_ERR		BIT(1)
#घोषणा BCM2835_DMA_DEBUG_READ_ERR		BIT(2)
#घोषणा BCM2835_DMA_DEBUG_OUTSTANDING_WRITES_SHIFT 4
#घोषणा BCM2835_DMA_DEBUG_OUTSTANDING_WRITES_BITS 4
#घोषणा BCM2835_DMA_DEBUG_ID_SHIFT		16
#घोषणा BCM2835_DMA_DEBUG_ID_BITS		9
#घोषणा BCM2835_DMA_DEBUG_STATE_SHIFT		16
#घोषणा BCM2835_DMA_DEBUG_STATE_BITS		9
#घोषणा BCM2835_DMA_DEBUG_VERSION_SHIFT		25
#घोषणा BCM2835_DMA_DEBUG_VERSION_BITS		3
#घोषणा BCM2835_DMA_DEBUG_LITE			BIT(28)

/* shared रेजिस्टरs क्रम all dma channels */
#घोषणा BCM2835_DMA_INT_STATUS         0xfe0
#घोषणा BCM2835_DMA_ENABLE             0xff0

#घोषणा BCM2835_DMA_DATA_TYPE_S8	1
#घोषणा BCM2835_DMA_DATA_TYPE_S16	2
#घोषणा BCM2835_DMA_DATA_TYPE_S32	4
#घोषणा BCM2835_DMA_DATA_TYPE_S128	16

/* Valid only क्रम channels 0 - 14, 15 has its own base address */
#घोषणा BCM2835_DMA_CHAN(n)	((n) << 8) /* Base address */
#घोषणा BCM2835_DMA_CHANIO(base, n) ((base) + BCM2835_DMA_CHAN(n))

/* the max dma length क्रम dअगरferent channels */
#घोषणा MAX_DMA_LEN SZ_1G
#घोषणा MAX_LITE_DMA_LEN (SZ_64K - 4)

अटल अंतरभूत माप_प्रकार bcm2835_dma_max_frame_length(काष्ठा bcm2835_chan *c)
अणु
	/* lite and normal channels have dअगरferent max frame length */
	वापस c->is_lite_channel ? MAX_LITE_DMA_LEN : MAX_DMA_LEN;
पूर्ण

/* how many frames of max_len size करो we need to transfer len bytes */
अटल अंतरभूत माप_प्रकार bcm2835_dma_frames_क्रम_length(माप_प्रकार len,
						   माप_प्रकार max_len)
अणु
	वापस DIV_ROUND_UP(len, max_len);
पूर्ण

अटल अंतरभूत काष्ठा bcm2835_dmadev *to_bcm2835_dma_dev(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा bcm2835_dmadev, ddev);
पूर्ण

अटल अंतरभूत काष्ठा bcm2835_chan *to_bcm2835_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा bcm2835_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा bcm2835_desc *to_bcm2835_dma_desc(
		काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा bcm2835_desc, vd.tx);
पूर्ण

अटल व्योम bcm2835_dma_मुक्त_cb_chain(काष्ठा bcm2835_desc *desc)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < desc->frames; i++)
		dma_pool_मुक्त(desc->c->cb_pool, desc->cb_list[i].cb,
			      desc->cb_list[i].paddr);

	kमुक्त(desc);
पूर्ण

अटल व्योम bcm2835_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	bcm2835_dma_मुक्त_cb_chain(
		container_of(vd, काष्ठा bcm2835_desc, vd));
पूर्ण

अटल व्योम bcm2835_dma_create_cb_set_length(
	काष्ठा bcm2835_chan *chan,
	काष्ठा bcm2835_dma_cb *control_block,
	माप_प्रकार len,
	माप_प्रकार period_len,
	माप_प्रकार *total_len,
	u32 finalextrainfo)
अणु
	माप_प्रकार max_len = bcm2835_dma_max_frame_length(chan);

	/* set the length taking lite-channel limitations पूर्णांकo account */
	control_block->length = min_t(u32, len, max_len);

	/* finished अगर we have no period_length */
	अगर (!period_len)
		वापस;

	/*
	 * period_len means: that we need to generate
	 * transfers that are terminating at every
	 * multiple of period_len - this is typically
	 * used to set the पूर्णांकerrupt flag in info
	 * which is required during cyclic transfers
	 */

	/* have we filled in period_length yet? */
	अगर (*total_len + control_block->length < period_len) अणु
		/* update number of bytes in this period so far */
		*total_len += control_block->length;
		वापस;
	पूर्ण

	/* calculate the length that reमुख्यs to reach period_length */
	control_block->length = period_len - *total_len;

	/* reset total_length क्रम next period */
	*total_len = 0;

	/* add extrainfo bits in info */
	control_block->info |= finalextrainfo;
पूर्ण

अटल अंतरभूत माप_प्रकार bcm2835_dma_count_frames_क्रम_sg(
	काष्ठा bcm2835_chan *c,
	काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len)
अणु
	माप_प्रकार frames = 0;
	काष्ठा scatterlist *sgent;
	अचिन्हित पूर्णांक i;
	माप_प्रकार plength = bcm2835_dma_max_frame_length(c);

	क्रम_each_sg(sgl, sgent, sg_len, i)
		frames += bcm2835_dma_frames_क्रम_length(
			sg_dma_len(sgent), plength);

	वापस frames;
पूर्ण

/**
 * bcm2835_dma_create_cb_chain - create a control block and fills data in
 *
 * @chan:           the @dma_chan क्रम which we run this
 * @direction:      the direction in which we transfer
 * @cyclic:         it is a cyclic transfer
 * @info:           the शेष info bits to apply per controlblock
 * @frames:         number of controlblocks to allocate
 * @src:            the src address to assign (अगर the S_INC bit is set
 *                  in @info, then it माला_लो incremented)
 * @dst:            the dst address to assign (अगर the D_INC bit is set
 *                  in @info, then it माला_लो incremented)
 * @buf_len:        the full buffer length (may also be 0)
 * @period_len:     the period length when to apply @finalextrainfo
 *                  in addition to the last transfer
 *                  this will also अवरोध some control-blocks early
 * @finalextrainfo: additional bits in last controlblock
 *                  (or when period_len is reached in हाल of cyclic)
 * @gfp:            the GFP flag to use क्रम allocation
 */
अटल काष्ठा bcm2835_desc *bcm2835_dma_create_cb_chain(
	काष्ठा dma_chan *chan, क्रमागत dma_transfer_direction direction,
	bool cyclic, u32 info, u32 finalextrainfo, माप_प्रकार frames,
	dma_addr_t src, dma_addr_t dst, माप_प्रकार buf_len,
	माप_प्रकार period_len, gfp_t gfp)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	माप_प्रकार len = buf_len, total_len;
	माप_प्रकार frame;
	काष्ठा bcm2835_desc *d;
	काष्ठा bcm2835_cb_entry *cb_entry;
	काष्ठा bcm2835_dma_cb *control_block;

	अगर (!frames)
		वापस शून्य;

	/* allocate and setup the descriptor. */
	d = kzalloc(काष्ठा_size(d, cb_list, frames), gfp);
	अगर (!d)
		वापस शून्य;

	d->c = c;
	d->dir = direction;
	d->cyclic = cyclic;

	/*
	 * Iterate over all frames, create a control block
	 * क्रम each frame and link them together.
	 */
	क्रम (frame = 0, total_len = 0; frame < frames; d->frames++, frame++) अणु
		cb_entry = &d->cb_list[frame];
		cb_entry->cb = dma_pool_alloc(c->cb_pool, gfp,
					      &cb_entry->paddr);
		अगर (!cb_entry->cb)
			जाओ error_cb;

		/* fill in the control block */
		control_block = cb_entry->cb;
		control_block->info = info;
		control_block->src = src;
		control_block->dst = dst;
		control_block->stride = 0;
		control_block->next = 0;
		/* set up length in control_block अगर requested */
		अगर (buf_len) अणु
			/* calculate length honoring period_length */
			bcm2835_dma_create_cb_set_length(
				c, control_block,
				len, period_len, &total_len,
				cyclic ? finalextrainfo : 0);

			/* calculate new reमुख्यing length */
			len -= control_block->length;
		पूर्ण

		/* link this the last controlblock */
		अगर (frame)
			d->cb_list[frame - 1].cb->next = cb_entry->paddr;

		/* update src and dst and length */
		अगर (src && (info & BCM2835_DMA_S_INC))
			src += control_block->length;
		अगर (dst && (info & BCM2835_DMA_D_INC))
			dst += control_block->length;

		/* Length of total transfer */
		d->size += control_block->length;
	पूर्ण

	/* the last frame requires extra flags */
	d->cb_list[d->frames - 1].cb->info |= finalextrainfo;

	/* detect a size missmatch */
	अगर (buf_len && (d->size != buf_len))
		जाओ error_cb;

	वापस d;
error_cb:
	bcm2835_dma_मुक्त_cb_chain(d);

	वापस शून्य;
पूर्ण

अटल व्योम bcm2835_dma_fill_cb_chain_with_sg(
	काष्ठा dma_chan *chan,
	क्रमागत dma_transfer_direction direction,
	काष्ठा bcm2835_cb_entry *cb,
	काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	माप_प्रकार len, max_len;
	अचिन्हित पूर्णांक i;
	dma_addr_t addr;
	काष्ठा scatterlist *sgent;

	max_len = bcm2835_dma_max_frame_length(c);
	क्रम_each_sg(sgl, sgent, sg_len, i) अणु
		क्रम (addr = sg_dma_address(sgent), len = sg_dma_len(sgent);
		     len > 0;
		     addr += cb->cb->length, len -= cb->cb->length, cb++) अणु
			अगर (direction == DMA_DEV_TO_MEM)
				cb->cb->dst = addr;
			अन्यथा
				cb->cb->src = addr;
			cb->cb->length = min(len, max_len);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bcm2835_dma_पात(काष्ठा bcm2835_chan *c)
अणु
	व्योम __iomem *chan_base = c->chan_base;
	दीर्घ पूर्णांक समयout = 10000;

	/*
	 * A zero control block address means the channel is idle.
	 * (The ACTIVE flag in the CS रेजिस्टर is not a reliable indicator.)
	 */
	अगर (!पढ़ोl(chan_base + BCM2835_DMA_ADDR))
		वापस;

	/* Write 0 to the active bit - Pause the DMA */
	ग_लिखोl(0, chan_base + BCM2835_DMA_CS);

	/* Wait क्रम any current AXI transfer to complete */
	जबतक ((पढ़ोl(chan_base + BCM2835_DMA_CS) &
		BCM2835_DMA_WAITING_FOR_WRITES) && --समयout)
		cpu_relax();

	/* Peripheral might be stuck and fail to संकेत AXI ग_लिखो responses */
	अगर (!समयout)
		dev_err(c->vc.chan.device->dev,
			"failed to complete outstanding writes\n");

	ग_लिखोl(BCM2835_DMA_RESET, chan_base + BCM2835_DMA_CS);
पूर्ण

अटल व्योम bcm2835_dma_start_desc(काष्ठा bcm2835_chan *c)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&c->vc);
	काष्ठा bcm2835_desc *d;

	अगर (!vd) अणु
		c->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vd->node);

	c->desc = d = to_bcm2835_dma_desc(&vd->tx);

	ग_लिखोl(d->cb_list[0].paddr, c->chan_base + BCM2835_DMA_ADDR);
	ग_लिखोl(BCM2835_DMA_ACTIVE, c->chan_base + BCM2835_DMA_CS);
पूर्ण

अटल irqवापस_t bcm2835_dma_callback(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bcm2835_chan *c = data;
	काष्ठा bcm2835_desc *d;
	अचिन्हित दीर्घ flags;

	/* check the shared पूर्णांकerrupt */
	अगर (c->irq_flags & IRQF_SHARED) अणु
		/* check अगर the पूर्णांकerrupt is enabled */
		flags = पढ़ोl(c->chan_base + BCM2835_DMA_CS);
		/* अगर not set then we are not the reason क्रम the irq */
		अगर (!(flags & BCM2835_DMA_INT))
			वापस IRQ_NONE;
	पूर्ण

	spin_lock_irqsave(&c->vc.lock, flags);

	/*
	 * Clear the INT flag to receive further पूर्णांकerrupts. Keep the channel
	 * active in हाल the descriptor is cyclic or in हाल the client has
	 * alपढ़ोy terminated the descriptor and issued a new one. (May happen
	 * अगर this IRQ handler is thपढ़ोed.) If the channel is finished, it
	 * will reमुख्य idle despite the ACTIVE flag being set.
	 */
	ग_लिखोl(BCM2835_DMA_INT | BCM2835_DMA_ACTIVE,
	       c->chan_base + BCM2835_DMA_CS);

	d = c->desc;

	अगर (d) अणु
		अगर (d->cyclic) अणु
			/* call the cyclic callback */
			vchan_cyclic_callback(&d->vd);
		पूर्ण अन्यथा अगर (!पढ़ोl(c->chan_base + BCM2835_DMA_ADDR)) अणु
			vchan_cookie_complete(&c->desc->vd);
			bcm2835_dma_start_desc(c);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm2835_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	काष्ठा device *dev = c->vc.chan.device->dev;

	dev_dbg(dev, "Allocating DMA channel %d\n", c->ch);

	/*
	 * Control blocks are 256 bit in length and must start at a 256 bit
	 * (32 byte) aligned address (BCM2835 ARM Peripherals, sec. 4.2.1.1).
	 */
	c->cb_pool = dma_pool_create(dev_name(dev), dev,
				     माप(काष्ठा bcm2835_dma_cb), 32, 0);
	अगर (!c->cb_pool) अणु
		dev_err(dev, "unable to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस request_irq(c->irq_number, bcm2835_dma_callback,
			   c->irq_flags, "DMA IRQ", c);
पूर्ण

अटल व्योम bcm2835_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	vchan_मुक्त_chan_resources(&c->vc);
	मुक्त_irq(c->irq_number, c);
	dma_pool_destroy(c->cb_pool);

	dev_dbg(c->vc.chan.device->dev, "Freeing DMA channel %u\n", c->ch);
पूर्ण

अटल माप_प्रकार bcm2835_dma_desc_size(काष्ठा bcm2835_desc *d)
अणु
	वापस d->size;
पूर्ण

अटल माप_प्रकार bcm2835_dma_desc_size_pos(काष्ठा bcm2835_desc *d, dma_addr_t addr)
अणु
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;

	क्रम (size = i = 0; i < d->frames; i++) अणु
		काष्ठा bcm2835_dma_cb *control_block = d->cb_list[i].cb;
		माप_प्रकार this_size = control_block->length;
		dma_addr_t dma;

		अगर (d->dir == DMA_DEV_TO_MEM)
			dma = control_block->dst;
		अन्यथा
			dma = control_block->src;

		अगर (size)
			size += this_size;
		अन्यथा अगर (addr >= dma && addr < dma + this_size)
			size += dma + this_size - addr;
	पूर्ण

	वापस size;
पूर्ण

अटल क्रमागत dma_status bcm2835_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&c->vc.lock, flags);
	vd = vchan_find_desc(&c->vc, cookie);
	अगर (vd) अणु
		txstate->residue =
			bcm2835_dma_desc_size(to_bcm2835_dma_desc(&vd->tx));
	पूर्ण अन्यथा अगर (c->desc && c->desc->vd.tx.cookie == cookie) अणु
		काष्ठा bcm2835_desc *d = c->desc;
		dma_addr_t pos;

		अगर (d->dir == DMA_MEM_TO_DEV)
			pos = पढ़ोl(c->chan_base + BCM2835_DMA_SOURCE_AD);
		अन्यथा अगर (d->dir == DMA_DEV_TO_MEM)
			pos = पढ़ोl(c->chan_base + BCM2835_DMA_DEST_AD);
		अन्यथा
			pos = 0;

		txstate->residue = bcm2835_dma_desc_size_pos(d, pos);
	पूर्ण अन्यथा अणु
		txstate->residue = 0;
	पूर्ण

	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम bcm2835_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (vchan_issue_pending(&c->vc) && !c->desc)
		bcm2835_dma_start_desc(c);

	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *bcm2835_dma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	काष्ठा bcm2835_desc *d;
	u32 info = BCM2835_DMA_D_INC | BCM2835_DMA_S_INC;
	u32 extra = BCM2835_DMA_INT_EN | BCM2835_DMA_WAIT_RESP;
	माप_प्रकार max_len = bcm2835_dma_max_frame_length(c);
	माप_प्रकार frames;

	/* अगर src, dst or len is not given वापस with an error */
	अगर (!src || !dst || !len)
		वापस शून्य;

	/* calculate number of frames */
	frames = bcm2835_dma_frames_क्रम_length(len, max_len);

	/* allocate the CB chain - this also fills in the poपूर्णांकers */
	d = bcm2835_dma_create_cb_chain(chan, DMA_MEM_TO_MEM, false,
					info, extra, frames,
					src, dst, len, 0, GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	वापस vchan_tx_prep(&c->vc, &d->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *bcm2835_dma_prep_slave_sg(
	काष्ठा dma_chan *chan,
	काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	काष्ठा bcm2835_desc *d;
	dma_addr_t src = 0, dst = 0;
	u32 info = BCM2835_DMA_WAIT_RESP;
	u32 extra = BCM2835_DMA_INT_EN;
	माप_प्रकार frames;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(chan->device->dev,
			"%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (c->dreq != 0)
		info |= BCM2835_DMA_PER_MAP(c->dreq);

	अगर (direction == DMA_DEV_TO_MEM) अणु
		अगर (c->cfg.src_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES)
			वापस शून्य;
		src = c->cfg.src_addr;
		info |= BCM2835_DMA_S_DREQ | BCM2835_DMA_D_INC;
	पूर्ण अन्यथा अणु
		अगर (c->cfg.dst_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES)
			वापस शून्य;
		dst = c->cfg.dst_addr;
		info |= BCM2835_DMA_D_DREQ | BCM2835_DMA_S_INC;
	पूर्ण

	/* count frames in sg list */
	frames = bcm2835_dma_count_frames_क्रम_sg(c, sgl, sg_len);

	/* allocate the CB chain */
	d = bcm2835_dma_create_cb_chain(chan, direction, false,
					info, extra,
					frames, src, dst, 0, 0,
					GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	/* fill in frames with scatterlist poपूर्णांकers */
	bcm2835_dma_fill_cb_chain_with_sg(chan, direction, d->cb_list,
					  sgl, sg_len);

	वापस vchan_tx_prep(&c->vc, &d->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *bcm2835_dma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा bcm2835_dmadev *od = to_bcm2835_dma_dev(chan->device);
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	काष्ठा bcm2835_desc *d;
	dma_addr_t src, dst;
	u32 info = BCM2835_DMA_WAIT_RESP;
	u32 extra = 0;
	माप_प्रकार max_len = bcm2835_dma_max_frame_length(c);
	माप_प्रकार frames;

	/* Grab configuration */
	अगर (!is_slave_direction(direction)) अणु
		dev_err(chan->device->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!buf_len) अणु
		dev_err(chan->device->dev,
			"%s: bad buffer length (= 0)\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT)
		extra |= BCM2835_DMA_INT_EN;
	अन्यथा
		period_len = buf_len;

	/*
	 * warn अगर buf_len is not a multiple of period_len - this may leed
	 * to unexpected latencies क्रम पूर्णांकerrupts and thus audiable clicks
	 */
	अगर (buf_len % period_len)
		dev_warn_once(chan->device->dev,
			      "%s: buffer_length (%zd) is not a multiple of period_len (%zd)\n",
			      __func__, buf_len, period_len);

	/* Setup DREQ channel */
	अगर (c->dreq != 0)
		info |= BCM2835_DMA_PER_MAP(c->dreq);

	अगर (direction == DMA_DEV_TO_MEM) अणु
		अगर (c->cfg.src_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES)
			वापस शून्य;
		src = c->cfg.src_addr;
		dst = buf_addr;
		info |= BCM2835_DMA_S_DREQ | BCM2835_DMA_D_INC;
	पूर्ण अन्यथा अणु
		अगर (c->cfg.dst_addr_width != DMA_SLAVE_BUSWIDTH_4_BYTES)
			वापस शून्य;
		dst = c->cfg.dst_addr;
		src = buf_addr;
		info |= BCM2835_DMA_D_DREQ | BCM2835_DMA_S_INC;

		/* non-lite channels can ग_लिखो zeroes w/o accessing memory */
		अगर (buf_addr == od->zero_page && !c->is_lite_channel)
			info |= BCM2835_DMA_S_IGNORE;
	पूर्ण

	/* calculate number of frames */
	frames = /* number of periods */
		 DIV_ROUND_UP(buf_len, period_len) *
		 /* number of frames per period */
		 bcm2835_dma_frames_क्रम_length(period_len, max_len);

	/*
	 * allocate the CB chain
	 * note that we need to use GFP_NOWAIT, as the ALSA i2s dmaengine
	 * implementation calls prep_dma_cyclic with पूर्णांकerrupts disabled.
	 */
	d = bcm2835_dma_create_cb_chain(chan, direction, true,
					info, extra,
					frames, src, dst, buf_len,
					period_len, GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	/* wrap around पूर्णांकo a loop */
	d->cb_list[d->frames - 1].cb->next = d->cb_list[0].paddr;

	वापस vchan_tx_prep(&c->vc, &d->vd, flags);
पूर्ण

अटल पूर्णांक bcm2835_dma_slave_config(काष्ठा dma_chan *chan,
				    काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	c->cfg = *cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/* stop DMA activity */
	अगर (c->desc) अणु
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = शून्य;
		bcm2835_dma_पात(c);
	पूर्ण

	vchan_get_all_descriptors(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&c->vc, &head);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	vchan_synchronize(&c->vc);
पूर्ण

अटल पूर्णांक bcm2835_dma_chan_init(काष्ठा bcm2835_dmadev *d, पूर्णांक chan_id,
				 पूर्णांक irq, अचिन्हित पूर्णांक irq_flags)
अणु
	काष्ठा bcm2835_chan *c;

	c = devm_kzalloc(d->ddev.dev, माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;

	c->vc.desc_मुक्त = bcm2835_dma_desc_मुक्त;
	vchan_init(&c->vc, &d->ddev);

	c->chan_base = BCM2835_DMA_CHANIO(d->base, chan_id);
	c->ch = chan_id;
	c->irq_number = irq;
	c->irq_flags = irq_flags;

	/* check in DEBUG रेजिस्टर अगर this is a LITE channel */
	अगर (पढ़ोl(c->chan_base + BCM2835_DMA_DEBUG) &
		BCM2835_DMA_DEBUG_LITE)
		c->is_lite_channel = true;

	वापस 0;
पूर्ण

अटल व्योम bcm2835_dma_मुक्त(काष्ठा bcm2835_dmadev *od)
अणु
	काष्ठा bcm2835_chan *c, *next;

	list_क्रम_each_entry_safe(c, next, &od->ddev.channels,
				 vc.chan.device_node) अणु
		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
	पूर्ण

	dma_unmap_page_attrs(od->ddev.dev, od->zero_page, PAGE_SIZE,
			     DMA_TO_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_dma_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-dma", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_dma_of_match);

अटल काष्ठा dma_chan *bcm2835_dma_xlate(काष्ठा of_phandle_args *spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा bcm2835_dmadev *d = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;

	chan = dma_get_any_slave_channel(&d->ddev);
	अगर (!chan)
		वापस शून्य;

	/* Set DREQ from param */
	to_bcm2835_dma_chan(chan)->dreq = spec->args[0];

	वापस chan;
पूर्ण

अटल पूर्णांक bcm2835_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_dmadev *od;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक rc;
	पूर्णांक i, j;
	पूर्णांक irq[BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED + 1];
	पूर्णांक irq_flags;
	uपूर्णांक32_t chans_available;
	अक्षर chan_name[BCM2835_DMA_CHAN_NAME_SIZE];

	अगर (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(&pdev->dev, "Unable to set DMA mask\n");
		वापस rc;
	पूर्ण

	od = devm_kzalloc(&pdev->dev, माप(*od), GFP_KERNEL);
	अगर (!od)
		वापस -ENOMEM;

	dma_set_max_seg_size(&pdev->dev, 0x3FFFFFFF);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	od->base = base;

	dma_cap_set(DMA_SLAVE, od->ddev.cap_mask);
	dma_cap_set(DMA_PRIVATE, od->ddev.cap_mask);
	dma_cap_set(DMA_CYCLIC, od->ddev.cap_mask);
	dma_cap_set(DMA_MEMCPY, od->ddev.cap_mask);
	od->ddev.device_alloc_chan_resources = bcm2835_dma_alloc_chan_resources;
	od->ddev.device_मुक्त_chan_resources = bcm2835_dma_मुक्त_chan_resources;
	od->ddev.device_tx_status = bcm2835_dma_tx_status;
	od->ddev.device_issue_pending = bcm2835_dma_issue_pending;
	od->ddev.device_prep_dma_cyclic = bcm2835_dma_prep_dma_cyclic;
	od->ddev.device_prep_slave_sg = bcm2835_dma_prep_slave_sg;
	od->ddev.device_prep_dma_स_नकल = bcm2835_dma_prep_dma_स_नकल;
	od->ddev.device_config = bcm2835_dma_slave_config;
	od->ddev.device_terminate_all = bcm2835_dma_terminate_all;
	od->ddev.device_synchronize = bcm2835_dma_synchronize;
	od->ddev.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	od->ddev.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	od->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
			      BIT(DMA_MEM_TO_MEM);
	od->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	od->ddev.descriptor_reuse = true;
	od->ddev.dev = &pdev->dev;
	INIT_LIST_HEAD(&od->ddev.channels);

	platक्रमm_set_drvdata(pdev, od);

	od->zero_page = dma_map_page_attrs(od->ddev.dev, ZERO_PAGE(0), 0,
					   PAGE_SIZE, DMA_TO_DEVICE,
					   DMA_ATTR_SKIP_CPU_SYNC);
	अगर (dma_mapping_error(od->ddev.dev, od->zero_page)) अणु
		dev_err(&pdev->dev, "Failed to map zero page\n");
		वापस -ENOMEM;
	पूर्ण

	/* Request DMA channel mask from device tree */
	अगर (of_property_पढ़ो_u32(pdev->dev.of_node,
			"brcm,dma-channel-mask",
			&chans_available)) अणु
		dev_err(&pdev->dev, "Failed to get channel mask\n");
		rc = -EINVAL;
		जाओ err_no_dma;
	पूर्ण

	/* get irqs क्रम each channel that we support */
	क्रम (i = 0; i <= BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED; i++) अणु
		/* skip masked out channels */
		अगर (!(chans_available & (1 << i))) अणु
			irq[i] = -1;
			जारी;
		पूर्ण

		/* get the named irq */
		snम_लिखो(chan_name, माप(chan_name), "dma%i", i);
		irq[i] = platक्रमm_get_irq_byname(pdev, chan_name);
		अगर (irq[i] >= 0)
			जारी;

		/* legacy device tree हाल handling */
		dev_warn_once(&pdev->dev,
			      "missing interrupt-names property in device tree - legacy interpretation is used\n");
		/*
		 * in हाल of channel >= 11
		 * use the 11th पूर्णांकerrupt and that is shared
		 */
		irq[i] = platक्रमm_get_irq(pdev, i < 11 ? i : 11);
	पूर्ण

	/* get irqs क्रम each channel */
	क्रम (i = 0; i <= BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED; i++) अणु
		/* skip channels without irq */
		अगर (irq[i] < 0)
			जारी;

		/* check अगर there are other channels that also use this irq */
		irq_flags = 0;
		क्रम (j = 0; j <= BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED; j++)
			अगर ((i != j) && (irq[j] == irq[i])) अणु
				irq_flags = IRQF_SHARED;
				अवरोध;
			पूर्ण

		/* initialize the channel */
		rc = bcm2835_dma_chan_init(od, i, irq[i], irq_flags);
		अगर (rc)
			जाओ err_no_dma;
	पूर्ण

	dev_dbg(&pdev->dev, "Initialized %i DMA channels\n", i);

	/* Device-tree DMA controller registration */
	rc = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
			bcm2835_dma_xlate, od);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed to register DMA controller\n");
		जाओ err_no_dma;
	पूर्ण

	rc = dma_async_device_रेजिस्टर(&od->ddev);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"Failed to register slave DMA engine device: %d\n", rc);
		जाओ err_no_dma;
	पूर्ण

	dev_dbg(&pdev->dev, "Load BCM2835 DMA engine driver\n");

	वापस 0;

err_no_dma:
	bcm2835_dma_मुक्त(od);
	वापस rc;
पूर्ण

अटल पूर्णांक bcm2835_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_dmadev *od = platक्रमm_get_drvdata(pdev);

	dma_async_device_unरेजिस्टर(&od->ddev);
	bcm2835_dma_मुक्त(od);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_dma_driver = अणु
	.probe	= bcm2835_dma_probe,
	.हटाओ	= bcm2835_dma_हटाओ,
	.driver = अणु
		.name = "bcm2835-dma",
		.of_match_table = of_match_ptr(bcm2835_dma_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm2835_dma_driver);

MODULE_ALIAS("platform:bcm2835-dma");
MODULE_DESCRIPTION("BCM2835 DMA engine driver");
MODULE_AUTHOR("Florian Meier <florian.meier@koalo.de>");
MODULE_LICENSE("GPL");
