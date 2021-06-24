<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Cirrus Logic EP93xx DMA Controller
 *
 * Copyright (C) 2011 Mika Westerberg
 *
 * DMA M2P implementation is based on the original
 * arch/arm/mach-ep93xx/dma-m2p.c which has following copyrights:
 *
 *   Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 *   Copyright (C) 2006 Applied Data Systems
 *   Copyright (C) 2009 Ryan Mallon <rmallon@gmail.com>
 *
 * This driver is based on dw_dmac and amba-pl08x drivers.
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>

#समावेश "dmaengine.h"

/* M2P रेजिस्टरs */
#घोषणा M2P_CONTROL			0x0000
#घोषणा M2P_CONTROL_STALLINT		BIT(0)
#घोषणा M2P_CONTROL_NFBINT		BIT(1)
#घोषणा M2P_CONTROL_CH_ERROR_INT	BIT(3)
#घोषणा M2P_CONTROL_ENABLE		BIT(4)
#घोषणा M2P_CONTROL_ICE			BIT(6)

#घोषणा M2P_INTERRUPT			0x0004
#घोषणा M2P_INTERRUPT_STALL		BIT(0)
#घोषणा M2P_INTERRUPT_NFB		BIT(1)
#घोषणा M2P_INTERRUPT_ERROR		BIT(3)

#घोषणा M2P_PPALLOC			0x0008
#घोषणा M2P_STATUS			0x000c

#घोषणा M2P_MAXCNT0			0x0020
#घोषणा M2P_BASE0			0x0024
#घोषणा M2P_MAXCNT1			0x0030
#घोषणा M2P_BASE1			0x0034

#घोषणा M2P_STATE_IDLE			0
#घोषणा M2P_STATE_STALL			1
#घोषणा M2P_STATE_ON			2
#घोषणा M2P_STATE_NEXT			3

/* M2M रेजिस्टरs */
#घोषणा M2M_CONTROL			0x0000
#घोषणा M2M_CONTROL_DONEINT		BIT(2)
#घोषणा M2M_CONTROL_ENABLE		BIT(3)
#घोषणा M2M_CONTROL_START		BIT(4)
#घोषणा M2M_CONTROL_DAH			BIT(11)
#घोषणा M2M_CONTROL_SAH			BIT(12)
#घोषणा M2M_CONTROL_PW_SHIFT		9
#घोषणा M2M_CONTROL_PW_8		(0 << M2M_CONTROL_PW_SHIFT)
#घोषणा M2M_CONTROL_PW_16		(1 << M2M_CONTROL_PW_SHIFT)
#घोषणा M2M_CONTROL_PW_32		(2 << M2M_CONTROL_PW_SHIFT)
#घोषणा M2M_CONTROL_PW_MASK		(3 << M2M_CONTROL_PW_SHIFT)
#घोषणा M2M_CONTROL_TM_SHIFT		13
#घोषणा M2M_CONTROL_TM_TX		(1 << M2M_CONTROL_TM_SHIFT)
#घोषणा M2M_CONTROL_TM_RX		(2 << M2M_CONTROL_TM_SHIFT)
#घोषणा M2M_CONTROL_NFBINT		BIT(21)
#घोषणा M2M_CONTROL_RSS_SHIFT		22
#घोषणा M2M_CONTROL_RSS_SSPRX		(1 << M2M_CONTROL_RSS_SHIFT)
#घोषणा M2M_CONTROL_RSS_SSPTX		(2 << M2M_CONTROL_RSS_SHIFT)
#घोषणा M2M_CONTROL_RSS_IDE		(3 << M2M_CONTROL_RSS_SHIFT)
#घोषणा M2M_CONTROL_NO_HDSK		BIT(24)
#घोषणा M2M_CONTROL_PWSC_SHIFT		25

#घोषणा M2M_INTERRUPT			0x0004
#घोषणा M2M_INTERRUPT_MASK		6

#घोषणा M2M_STATUS			0x000c
#घोषणा M2M_STATUS_CTL_SHIFT		1
#घोषणा M2M_STATUS_CTL_IDLE		(0 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_CTL_STALL		(1 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_CTL_MEMRD		(2 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_CTL_MEMWR		(3 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_CTL_BWCWAIT		(4 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_CTL_MASK		(7 << M2M_STATUS_CTL_SHIFT)
#घोषणा M2M_STATUS_BUF_SHIFT		4
#घोषणा M2M_STATUS_BUF_NO		(0 << M2M_STATUS_BUF_SHIFT)
#घोषणा M2M_STATUS_BUF_ON		(1 << M2M_STATUS_BUF_SHIFT)
#घोषणा M2M_STATUS_BUF_NEXT		(2 << M2M_STATUS_BUF_SHIFT)
#घोषणा M2M_STATUS_BUF_MASK		(3 << M2M_STATUS_BUF_SHIFT)
#घोषणा M2M_STATUS_DONE			BIT(6)

#घोषणा M2M_BCR0			0x0010
#घोषणा M2M_BCR1			0x0014
#घोषणा M2M_SAR_BASE0			0x0018
#घोषणा M2M_SAR_BASE1			0x001c
#घोषणा M2M_DAR_BASE0			0x002c
#घोषणा M2M_DAR_BASE1			0x0030

#घोषणा DMA_MAX_CHAN_BYTES		0xffff
#घोषणा DMA_MAX_CHAN_DESCRIPTORS	32

काष्ठा ep93xx_dma_engine;
अटल पूर्णांक ep93xx_dma_slave_config_ग_लिखो(काष्ठा dma_chan *chan,
					 क्रमागत dma_transfer_direction dir,
					 काष्ठा dma_slave_config *config);

/**
 * काष्ठा ep93xx_dma_desc - EP93xx specअगरic transaction descriptor
 * @src_addr: source address of the transaction
 * @dst_addr: destination address of the transaction
 * @size: size of the transaction (in bytes)
 * @complete: this descriptor is completed
 * @txd: dmaengine API descriptor
 * @tx_list: list of linked descriptors
 * @node: link used क्रम putting this पूर्णांकo a channel queue
 */
काष्ठा ep93xx_dma_desc अणु
	u32				src_addr;
	u32				dst_addr;
	माप_प्रकार				size;
	bool				complete;
	काष्ठा dma_async_tx_descriptor	txd;
	काष्ठा list_head		tx_list;
	काष्ठा list_head		node;
पूर्ण;

/**
 * काष्ठा ep93xx_dma_chan - an EP93xx DMA M2P/M2M channel
 * @chan: dmaengine API channel
 * @edma: poपूर्णांकer to to the engine device
 * @regs: memory mapped रेजिस्टरs
 * @irq: पूर्णांकerrupt number of the channel
 * @clk: घड़ी used by this channel
 * @tasklet: channel specअगरic tasklet used क्रम callbacks
 * @lock: lock protecting the fields following
 * @flags: flags क्रम the channel
 * @buffer: which buffer to use next (0/1)
 * @active: flattened chain of descriptors currently being processed
 * @queue: pending descriptors which are handled next
 * @मुक्त_list: list of मुक्त descriptors which can be used
 * @runसमय_addr: physical address currently used as dest/src (M2M only). This
 *                is set via .device_config beक्रमe slave operation is
 *                prepared
 * @runसमय_ctrl: M2M runसमय values क्रम the control रेजिस्टर.
 * @slave_config: slave configuration
 *
 * As EP93xx DMA controller करोesn't support real chained DMA descriptors we
 * will have slightly dअगरferent scheme here: @active poपूर्णांकs to a head of
 * flattened DMA descriptor chain.
 *
 * @queue holds pending transactions. These are linked through the first
 * descriptor in the chain. When a descriptor is moved to the @active queue,
 * the first and chained descriptors are flattened पूर्णांकo a single list.
 *
 * @chan.निजी holds poपूर्णांकer to &काष्ठा ep93xx_dma_data which contains
 * necessary channel configuration inक्रमmation. For स_नकल channels this must
 * be %शून्य.
 */
काष्ठा ep93xx_dma_chan अणु
	काष्ठा dma_chan			chan;
	स्थिर काष्ठा ep93xx_dma_engine	*edma;
	व्योम __iomem			*regs;
	पूर्णांक				irq;
	काष्ठा clk			*clk;
	काष्ठा tasklet_काष्ठा		tasklet;
	/* protects the fields following */
	spinlock_t			lock;
	अचिन्हित दीर्घ			flags;
/* Channel is configured क्रम cyclic transfers */
#घोषणा EP93XX_DMA_IS_CYCLIC		0

	पूर्णांक				buffer;
	काष्ठा list_head		active;
	काष्ठा list_head		queue;
	काष्ठा list_head		मुक्त_list;
	u32				runसमय_addr;
	u32				runसमय_ctrl;
	काष्ठा dma_slave_config		slave_config;
पूर्ण;

/**
 * काष्ठा ep93xx_dma_engine - the EP93xx DMA engine instance
 * @dma_dev: holds the dmaengine device
 * @m2m: is this an M2M or M2P device
 * @hw_setup: method which sets the channel up क्रम operation
 * @hw_synchronize: synchronizes DMA channel termination to current context
 * @hw_shutकरोwn: shuts the channel करोwn and flushes whatever is left
 * @hw_submit: pushes active descriptor(s) to the hardware
 * @hw_पूर्णांकerrupt: handle the पूर्णांकerrupt
 * @num_channels: number of channels क्रम this instance
 * @channels: array of channels
 *
 * There is one instance of this काष्ठा क्रम the M2P channels and one क्रम the
 * M2M channels. hw_xxx() methods are used to perक्रमm operations which are
 * dअगरferent on M2M and M2P channels. These methods are called with channel
 * lock held and पूर्णांकerrupts disabled so they cannot sleep.
 */
काष्ठा ep93xx_dma_engine अणु
	काष्ठा dma_device	dma_dev;
	bool			m2m;
	पूर्णांक			(*hw_setup)(काष्ठा ep93xx_dma_chan *);
	व्योम			(*hw_synchronize)(काष्ठा ep93xx_dma_chan *);
	व्योम			(*hw_shutकरोwn)(काष्ठा ep93xx_dma_chan *);
	व्योम			(*hw_submit)(काष्ठा ep93xx_dma_chan *);
	पूर्णांक			(*hw_पूर्णांकerrupt)(काष्ठा ep93xx_dma_chan *);
#घोषणा INTERRUPT_UNKNOWN	0
#घोषणा INTERRUPT_DONE		1
#घोषणा INTERRUPT_NEXT_BUFFER	2

	माप_प्रकार			num_channels;
	काष्ठा ep93xx_dma_chan	channels[];
पूर्ण;

अटल अंतरभूत काष्ठा device *chan2dev(काष्ठा ep93xx_dma_chan *edmac)
अणु
	वापस &edmac->chan.dev->device;
पूर्ण

अटल काष्ठा ep93xx_dma_chan *to_ep93xx_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा ep93xx_dma_chan, chan);
पूर्ण

/**
 * ep93xx_dma_set_active - set new active descriptor chain
 * @edmac: channel
 * @desc: head of the new active descriptor chain
 *
 * Sets @desc to be the head of the new active descriptor chain. This is the
 * chain which is processed next. The active list must be empty beक्रमe calling
 * this function.
 *
 * Called with @edmac->lock held and पूर्णांकerrupts disabled.
 */
अटल व्योम ep93xx_dma_set_active(काष्ठा ep93xx_dma_chan *edmac,
				  काष्ठा ep93xx_dma_desc *desc)
अणु
	BUG_ON(!list_empty(&edmac->active));

	list_add_tail(&desc->node, &edmac->active);

	/* Flatten the @desc->tx_list chain पूर्णांकo @edmac->active list */
	जबतक (!list_empty(&desc->tx_list)) अणु
		काष्ठा ep93xx_dma_desc *d = list_first_entry(&desc->tx_list,
			काष्ठा ep93xx_dma_desc, node);

		/*
		 * We copy the callback parameters from the first descriptor
		 * to all the chained descriptors. This way we can call the
		 * callback without having to find out the first descriptor in
		 * the chain. Useful क्रम cyclic transfers.
		 */
		d->txd.callback = desc->txd.callback;
		d->txd.callback_param = desc->txd.callback_param;

		list_move_tail(&d->node, &edmac->active);
	पूर्ण
पूर्ण

/* Called with @edmac->lock held and पूर्णांकerrupts disabled */
अटल काष्ठा ep93xx_dma_desc *
ep93xx_dma_get_active(काष्ठा ep93xx_dma_chan *edmac)
अणु
	वापस list_first_entry_or_null(&edmac->active,
					काष्ठा ep93xx_dma_desc, node);
पूर्ण

/**
 * ep93xx_dma_advance_active - advances to the next active descriptor
 * @edmac: channel
 *
 * Function advances active descriptor to the next in the @edmac->active and
 * वापसs %true अगर we still have descriptors in the chain to process.
 * Otherwise वापसs %false.
 *
 * When the channel is in cyclic mode always वापसs %true.
 *
 * Called with @edmac->lock held and पूर्णांकerrupts disabled.
 */
अटल bool ep93xx_dma_advance_active(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_desc *desc;

	list_rotate_left(&edmac->active);

	अगर (test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags))
		वापस true;

	desc = ep93xx_dma_get_active(edmac);
	अगर (!desc)
		वापस false;

	/*
	 * If txd.cookie is set it means that we are back in the first
	 * descriptor in the chain and hence करोne with it.
	 */
	वापस !desc->txd.cookie;
पूर्ण

/*
 * M2P DMA implementation
 */

अटल व्योम m2p_set_control(काष्ठा ep93xx_dma_chan *edmac, u32 control)
अणु
	ग_लिखोl(control, edmac->regs + M2P_CONTROL);
	/*
	 * EP93xx User's Guide states that we must perक्रमm a dummy पढ़ो after
	 * ग_लिखो to the control रेजिस्टर.
	 */
	पढ़ोl(edmac->regs + M2P_CONTROL);
पूर्ण

अटल पूर्णांक m2p_hw_setup(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_data *data = edmac->chan.निजी;
	u32 control;

	ग_लिखोl(data->port & 0xf, edmac->regs + M2P_PPALLOC);

	control = M2P_CONTROL_CH_ERROR_INT | M2P_CONTROL_ICE
		| M2P_CONTROL_ENABLE;
	m2p_set_control(edmac, control);

	edmac->buffer = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 m2p_channel_state(काष्ठा ep93xx_dma_chan *edmac)
अणु
	वापस (पढ़ोl(edmac->regs + M2P_STATUS) >> 4) & 0x3;
पूर्ण

अटल व्योम m2p_hw_synchronize(काष्ठा ep93xx_dma_chan *edmac)
अणु
	अचिन्हित दीर्घ flags;
	u32 control;

	spin_lock_irqsave(&edmac->lock, flags);
	control = पढ़ोl(edmac->regs + M2P_CONTROL);
	control &= ~(M2P_CONTROL_STALLINT | M2P_CONTROL_NFBINT);
	m2p_set_control(edmac, control);
	spin_unlock_irqrestore(&edmac->lock, flags);

	जबतक (m2p_channel_state(edmac) >= M2P_STATE_ON)
		schedule();
पूर्ण

अटल व्योम m2p_hw_shutकरोwn(काष्ठा ep93xx_dma_chan *edmac)
अणु
	m2p_set_control(edmac, 0);

	जबतक (m2p_channel_state(edmac) != M2P_STATE_IDLE)
		dev_warn(chan2dev(edmac), "M2P: Not yet IDLE\n");
पूर्ण

अटल व्योम m2p_fill_desc(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_desc *desc;
	u32 bus_addr;

	desc = ep93xx_dma_get_active(edmac);
	अगर (!desc) अणु
		dev_warn(chan2dev(edmac), "M2P: empty descriptor list\n");
		वापस;
	पूर्ण

	अगर (ep93xx_dma_chan_direction(&edmac->chan) == DMA_MEM_TO_DEV)
		bus_addr = desc->src_addr;
	अन्यथा
		bus_addr = desc->dst_addr;

	अगर (edmac->buffer == 0) अणु
		ग_लिखोl(desc->size, edmac->regs + M2P_MAXCNT0);
		ग_लिखोl(bus_addr, edmac->regs + M2P_BASE0);
	पूर्ण अन्यथा अणु
		ग_लिखोl(desc->size, edmac->regs + M2P_MAXCNT1);
		ग_लिखोl(bus_addr, edmac->regs + M2P_BASE1);
	पूर्ण

	edmac->buffer ^= 1;
पूर्ण

अटल व्योम m2p_hw_submit(काष्ठा ep93xx_dma_chan *edmac)
अणु
	u32 control = पढ़ोl(edmac->regs + M2P_CONTROL);

	m2p_fill_desc(edmac);
	control |= M2P_CONTROL_STALLINT;

	अगर (ep93xx_dma_advance_active(edmac)) अणु
		m2p_fill_desc(edmac);
		control |= M2P_CONTROL_NFBINT;
	पूर्ण

	m2p_set_control(edmac, control);
पूर्ण

अटल पूर्णांक m2p_hw_पूर्णांकerrupt(काष्ठा ep93xx_dma_chan *edmac)
अणु
	u32 irq_status = पढ़ोl(edmac->regs + M2P_INTERRUPT);
	u32 control;

	अगर (irq_status & M2P_INTERRUPT_ERROR) अणु
		काष्ठा ep93xx_dma_desc *desc = ep93xx_dma_get_active(edmac);

		/* Clear the error पूर्णांकerrupt */
		ग_लिखोl(1, edmac->regs + M2P_INTERRUPT);

		/*
		 * It seems that there is no easy way of reporting errors back
		 * to client so we just report the error here and जारी as
		 * usual.
		 *
		 * Revisit this when there is a mechanism to report back the
		 * errors.
		 */
		dev_err(chan2dev(edmac),
			"DMA transfer failed! Details:\n"
			"\tcookie	: %d\n"
			"\tsrc_addr	: 0x%08x\n"
			"\tdst_addr	: 0x%08x\n"
			"\tsize		: %zu\n",
			desc->txd.cookie, desc->src_addr, desc->dst_addr,
			desc->size);
	पूर्ण

	/*
	 * Even latest E2 silicon revision someबार निश्चित STALL पूर्णांकerrupt
	 * instead of NFB. Thereक्रमe we treat them equally, basing on the
	 * amount of data we still have to transfer.
	 */
	अगर (!(irq_status & (M2P_INTERRUPT_STALL | M2P_INTERRUPT_NFB)))
		वापस INTERRUPT_UNKNOWN;

	अगर (ep93xx_dma_advance_active(edmac)) अणु
		m2p_fill_desc(edmac);
		वापस INTERRUPT_NEXT_BUFFER;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	control = पढ़ोl(edmac->regs + M2P_CONTROL);
	control &= ~(M2P_CONTROL_STALLINT | M2P_CONTROL_NFBINT);
	m2p_set_control(edmac, control);

	वापस INTERRUPT_DONE;
पूर्ण

/*
 * M2M DMA implementation
 */

अटल पूर्णांक m2m_hw_setup(काष्ठा ep93xx_dma_chan *edmac)
अणु
	स्थिर काष्ठा ep93xx_dma_data *data = edmac->chan.निजी;
	u32 control = 0;

	अगर (!data) अणु
		/* This is स_नकल channel, nothing to configure */
		ग_लिखोl(control, edmac->regs + M2M_CONTROL);
		वापस 0;
	पूर्ण

	चयन (data->port) अणु
	हाल EP93XX_DMA_SSP:
		/*
		 * This was found via experimenting - anything less than 5
		 * causes the channel to perक्रमm only a partial transfer which
		 * leads to problems since we करोn't get DONE पूर्णांकerrupt then.
		 */
		control = (5 << M2M_CONTROL_PWSC_SHIFT);
		control |= M2M_CONTROL_NO_HDSK;

		अगर (data->direction == DMA_MEM_TO_DEV) अणु
			control |= M2M_CONTROL_DAH;
			control |= M2M_CONTROL_TM_TX;
			control |= M2M_CONTROL_RSS_SSPTX;
		पूर्ण अन्यथा अणु
			control |= M2M_CONTROL_SAH;
			control |= M2M_CONTROL_TM_RX;
			control |= M2M_CONTROL_RSS_SSPRX;
		पूर्ण
		अवरोध;

	हाल EP93XX_DMA_IDE:
		/*
		 * This IDE part is totally untested. Values below are taken
		 * from the EP93xx Users's Guide and might not be correct.
		 */
		अगर (data->direction == DMA_MEM_TO_DEV) अणु
			/* Worst हाल from the UG */
			control = (3 << M2M_CONTROL_PWSC_SHIFT);
			control |= M2M_CONTROL_DAH;
			control |= M2M_CONTROL_TM_TX;
		पूर्ण अन्यथा अणु
			control = (2 << M2M_CONTROL_PWSC_SHIFT);
			control |= M2M_CONTROL_SAH;
			control |= M2M_CONTROL_TM_RX;
		पूर्ण

		control |= M2M_CONTROL_NO_HDSK;
		control |= M2M_CONTROL_RSS_IDE;
		control |= M2M_CONTROL_PW_16;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(control, edmac->regs + M2M_CONTROL);
	वापस 0;
पूर्ण

अटल व्योम m2m_hw_shutकरोwn(काष्ठा ep93xx_dma_chan *edmac)
अणु
	/* Just disable the channel */
	ग_लिखोl(0, edmac->regs + M2M_CONTROL);
पूर्ण

अटल व्योम m2m_fill_desc(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_desc *desc;

	desc = ep93xx_dma_get_active(edmac);
	अगर (!desc) अणु
		dev_warn(chan2dev(edmac), "M2M: empty descriptor list\n");
		वापस;
	पूर्ण

	अगर (edmac->buffer == 0) अणु
		ग_लिखोl(desc->src_addr, edmac->regs + M2M_SAR_BASE0);
		ग_लिखोl(desc->dst_addr, edmac->regs + M2M_DAR_BASE0);
		ग_लिखोl(desc->size, edmac->regs + M2M_BCR0);
	पूर्ण अन्यथा अणु
		ग_लिखोl(desc->src_addr, edmac->regs + M2M_SAR_BASE1);
		ग_लिखोl(desc->dst_addr, edmac->regs + M2M_DAR_BASE1);
		ग_लिखोl(desc->size, edmac->regs + M2M_BCR1);
	पूर्ण

	edmac->buffer ^= 1;
पूर्ण

अटल व्योम m2m_hw_submit(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_data *data = edmac->chan.निजी;
	u32 control = पढ़ोl(edmac->regs + M2M_CONTROL);

	/*
	 * Since we allow clients to configure PW (peripheral width) we always
	 * clear PW bits here and then set them according what is given in
	 * the runसमय configuration.
	 */
	control &= ~M2M_CONTROL_PW_MASK;
	control |= edmac->runसमय_ctrl;

	m2m_fill_desc(edmac);
	control |= M2M_CONTROL_DONEINT;

	अगर (ep93xx_dma_advance_active(edmac)) अणु
		m2m_fill_desc(edmac);
		control |= M2M_CONTROL_NFBINT;
	पूर्ण

	/*
	 * Now we can finally enable the channel. For M2M channel this must be
	 * करोne _after_ the BCRx रेजिस्टरs are programmed.
	 */
	control |= M2M_CONTROL_ENABLE;
	ग_लिखोl(control, edmac->regs + M2M_CONTROL);

	अगर (!data) अणु
		/*
		 * For स_नकल channels the software trigger must be निश्चितed
		 * in order to start the स_नकल operation.
		 */
		control |= M2M_CONTROL_START;
		ग_लिखोl(control, edmac->regs + M2M_CONTROL);
	पूर्ण
पूर्ण

/*
 * According to EP93xx User's Guide, we should receive DONE पूर्णांकerrupt when all
 * M2M DMA controller transactions complete normally. This is not always the
 * हाल - someबार EP93xx M2M DMA निश्चितs DONE पूर्णांकerrupt when the DMA channel
 * is still running (channel Buffer FSM in DMA_BUF_ON state, and channel
 * Control FSM in DMA_MEM_RD state, observed at least in IDE-DMA operation).
 * In effect, disabling the channel when only DONE bit is set could stop
 * currently running DMA transfer. To aव्योम this, we use Buffer FSM and
 * Control FSM to check current state of DMA channel.
 */
अटल पूर्णांक m2m_hw_पूर्णांकerrupt(काष्ठा ep93xx_dma_chan *edmac)
अणु
	u32 status = पढ़ोl(edmac->regs + M2M_STATUS);
	u32 ctl_fsm = status & M2M_STATUS_CTL_MASK;
	u32 buf_fsm = status & M2M_STATUS_BUF_MASK;
	bool करोne = status & M2M_STATUS_DONE;
	bool last_करोne;
	u32 control;
	काष्ठा ep93xx_dma_desc *desc;

	/* Accept only DONE and NFB पूर्णांकerrupts */
	अगर (!(पढ़ोl(edmac->regs + M2M_INTERRUPT) & M2M_INTERRUPT_MASK))
		वापस INTERRUPT_UNKNOWN;

	अगर (करोne) अणु
		/* Clear the DONE bit */
		ग_लिखोl(0, edmac->regs + M2M_INTERRUPT);
	पूर्ण

	/*
	 * Check whether we are करोne with descriptors or not. This, together
	 * with DMA channel state, determines action to take in पूर्णांकerrupt.
	 */
	desc = ep93xx_dma_get_active(edmac);
	last_करोne = !desc || desc->txd.cookie;

	/*
	 * Use M2M DMA Buffer FSM and Control FSM to check current state of
	 * DMA channel. Using DONE and NFB bits from channel status रेजिस्टर
	 * or bits from channel पूर्णांकerrupt रेजिस्टर is not reliable.
	 */
	अगर (!last_करोne &&
	    (buf_fsm == M2M_STATUS_BUF_NO ||
	     buf_fsm == M2M_STATUS_BUF_ON)) अणु
		/*
		 * Two buffers are पढ़ोy क्रम update when Buffer FSM is in
		 * DMA_NO_BUF state. Only one buffer can be prepared without
		 * disabling the channel or polling the DONE bit.
		 * To simplअगरy things, always prepare only one buffer.
		 */
		अगर (ep93xx_dma_advance_active(edmac)) अणु
			m2m_fill_desc(edmac);
			अगर (करोne && !edmac->chan.निजी) अणु
				/* Software trigger क्रम स_नकल channel */
				control = पढ़ोl(edmac->regs + M2M_CONTROL);
				control |= M2M_CONTROL_START;
				ग_लिखोl(control, edmac->regs + M2M_CONTROL);
			पूर्ण
			वापस INTERRUPT_NEXT_BUFFER;
		पूर्ण अन्यथा अणु
			last_करोne = true;
		पूर्ण
	पूर्ण

	/*
	 * Disable the channel only when Buffer FSM is in DMA_NO_BUF state
	 * and Control FSM is in DMA_STALL state.
	 */
	अगर (last_करोne &&
	    buf_fsm == M2M_STATUS_BUF_NO &&
	    ctl_fsm == M2M_STATUS_CTL_STALL) अणु
		/* Disable पूर्णांकerrupts and the channel */
		control = पढ़ोl(edmac->regs + M2M_CONTROL);
		control &= ~(M2M_CONTROL_DONEINT | M2M_CONTROL_NFBINT
			    | M2M_CONTROL_ENABLE);
		ग_लिखोl(control, edmac->regs + M2M_CONTROL);
		वापस INTERRUPT_DONE;
	पूर्ण

	/*
	 * Nothing to करो this समय.
	 */
	वापस INTERRUPT_NEXT_BUFFER;
पूर्ण

/*
 * DMA engine API implementation
 */

अटल काष्ठा ep93xx_dma_desc *
ep93xx_dma_desc_get(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_desc *desc, *_desc;
	काष्ठा ep93xx_dma_desc *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edmac->lock, flags);
	list_क्रम_each_entry_safe(desc, _desc, &edmac->मुक्त_list, node) अणु
		अगर (async_tx_test_ack(&desc->txd)) अणु
			list_del_init(&desc->node);

			/* Re-initialize the descriptor */
			desc->src_addr = 0;
			desc->dst_addr = 0;
			desc->size = 0;
			desc->complete = false;
			desc->txd.cookie = 0;
			desc->txd.callback = शून्य;
			desc->txd.callback_param = शून्य;

			ret = desc;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&edmac->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम ep93xx_dma_desc_put(काष्ठा ep93xx_dma_chan *edmac,
				काष्ठा ep93xx_dma_desc *desc)
अणु
	अगर (desc) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&edmac->lock, flags);
		list_splice_init(&desc->tx_list, &edmac->मुक्त_list);
		list_add(&desc->node, &edmac->मुक्त_list);
		spin_unlock_irqrestore(&edmac->lock, flags);
	पूर्ण
पूर्ण

/**
 * ep93xx_dma_advance_work - start processing the next pending transaction
 * @edmac: channel
 *
 * If we have pending transactions queued and we are currently idling, this
 * function takes the next queued transaction from the @edmac->queue and
 * pushes it to the hardware क्रम execution.
 */
अटल व्योम ep93xx_dma_advance_work(काष्ठा ep93xx_dma_chan *edmac)
अणु
	काष्ठा ep93xx_dma_desc *new;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edmac->lock, flags);
	अगर (!list_empty(&edmac->active) || list_empty(&edmac->queue)) अणु
		spin_unlock_irqrestore(&edmac->lock, flags);
		वापस;
	पूर्ण

	/* Take the next descriptor from the pending queue */
	new = list_first_entry(&edmac->queue, काष्ठा ep93xx_dma_desc, node);
	list_del_init(&new->node);

	ep93xx_dma_set_active(edmac, new);

	/* Push it to the hardware */
	edmac->edma->hw_submit(edmac);
	spin_unlock_irqrestore(&edmac->lock, flags);
पूर्ण

अटल व्योम ep93xx_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ep93xx_dma_chan *edmac = from_tasklet(edmac, t, tasklet);
	काष्ठा ep93xx_dma_desc *desc, *d;
	काष्ठा dmaengine_desc_callback cb;
	LIST_HEAD(list);

	स_रखो(&cb, 0, माप(cb));
	spin_lock_irq(&edmac->lock);
	/*
	 * If dma_terminate_all() was called beक्रमe we get to run, the active
	 * list has become empty. If that happens we aren't supposed to करो
	 * anything more than call ep93xx_dma_advance_work().
	 */
	desc = ep93xx_dma_get_active(edmac);
	अगर (desc) अणु
		अगर (desc->complete) अणु
			/* mark descriptor complete क्रम non cyclic हाल only */
			अगर (!test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags))
				dma_cookie_complete(&desc->txd);
			list_splice_init(&edmac->active, &list);
		पूर्ण
		dmaengine_desc_get_callback(&desc->txd, &cb);
	पूर्ण
	spin_unlock_irq(&edmac->lock);

	/* Pick up the next descriptor from the queue */
	ep93xx_dma_advance_work(edmac);

	/* Now we can release all the chained descriptors */
	list_क्रम_each_entry_safe(desc, d, &list, node) अणु
		dma_descriptor_unmap(&desc->txd);
		ep93xx_dma_desc_put(edmac, desc);
	पूर्ण

	dmaengine_desc_callback_invoke(&cb, शून्य);
पूर्ण

अटल irqवापस_t ep93xx_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ep93xx_dma_chan *edmac = dev_id;
	काष्ठा ep93xx_dma_desc *desc;
	irqवापस_t ret = IRQ_HANDLED;

	spin_lock(&edmac->lock);

	desc = ep93xx_dma_get_active(edmac);
	अगर (!desc) अणु
		dev_warn(chan2dev(edmac),
			 "got interrupt while active list is empty\n");
		spin_unlock(&edmac->lock);
		वापस IRQ_NONE;
	पूर्ण

	चयन (edmac->edma->hw_पूर्णांकerrupt(edmac)) अणु
	हाल INTERRUPT_DONE:
		desc->complete = true;
		tasklet_schedule(&edmac->tasklet);
		अवरोध;

	हाल INTERRUPT_NEXT_BUFFER:
		अगर (test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags))
			tasklet_schedule(&edmac->tasklet);
		अवरोध;

	शेष:
		dev_warn(chan2dev(edmac), "unknown interrupt!\n");
		ret = IRQ_NONE;
		अवरोध;
	पूर्ण

	spin_unlock(&edmac->lock);
	वापस ret;
पूर्ण

/**
 * ep93xx_dma_tx_submit - set the prepared descriptor(s) to be executed
 * @tx: descriptor to be executed
 *
 * Function will execute given descriptor on the hardware or अगर the hardware
 * is busy, queue the descriptor to be executed later on. Returns cookie which
 * can be used to poll the status of the descriptor.
 */
अटल dma_cookie_t ep93xx_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(tx->chan);
	काष्ठा ep93xx_dma_desc *desc;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edmac->lock, flags);
	cookie = dma_cookie_assign(tx);

	desc = container_of(tx, काष्ठा ep93xx_dma_desc, txd);

	/*
	 * If nothing is currently prosessed, we push this descriptor
	 * directly to the hardware. Otherwise we put the descriptor
	 * to the pending queue.
	 */
	अगर (list_empty(&edmac->active)) अणु
		ep93xx_dma_set_active(edmac, desc);
		edmac->edma->hw_submit(edmac);
	पूर्ण अन्यथा अणु
		list_add_tail(&desc->node, &edmac->queue);
	पूर्ण

	spin_unlock_irqrestore(&edmac->lock, flags);
	वापस cookie;
पूर्ण

/**
 * ep93xx_dma_alloc_chan_resources - allocate resources क्रम the channel
 * @chan: channel to allocate resources
 *
 * Function allocates necessary resources क्रम the given DMA channel and
 * वापसs number of allocated descriptors क्रम the channel. Negative त्रुटि_सं
 * is वापसed in हाल of failure.
 */
अटल पूर्णांक ep93xx_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_data *data = chan->निजी;
	स्थिर अक्षर *name = dma_chan_name(chan);
	पूर्णांक ret, i;

	/* Sanity check the channel parameters */
	अगर (!edmac->edma->m2m) अणु
		अगर (!data)
			वापस -EINVAL;
		अगर (data->port < EP93XX_DMA_I2S1 ||
		    data->port > EP93XX_DMA_IRDA)
			वापस -EINVAL;
		अगर (data->direction != ep93xx_dma_chan_direction(chan))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (data) अणु
			चयन (data->port) अणु
			हाल EP93XX_DMA_SSP:
			हाल EP93XX_DMA_IDE:
				अगर (!is_slave_direction(data->direction))
					वापस -EINVAL;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (data && data->name)
		name = data->name;

	ret = clk_enable(edmac->clk);
	अगर (ret)
		वापस ret;

	ret = request_irq(edmac->irq, ep93xx_dma_पूर्णांकerrupt, 0, name, edmac);
	अगर (ret)
		जाओ fail_clk_disable;

	spin_lock_irq(&edmac->lock);
	dma_cookie_init(&edmac->chan);
	ret = edmac->edma->hw_setup(edmac);
	spin_unlock_irq(&edmac->lock);

	अगर (ret)
		जाओ fail_मुक्त_irq;

	क्रम (i = 0; i < DMA_MAX_CHAN_DESCRIPTORS; i++) अणु
		काष्ठा ep93xx_dma_desc *desc;

		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc) अणु
			dev_warn(chan2dev(edmac), "not enough descriptors\n");
			अवरोध;
		पूर्ण

		INIT_LIST_HEAD(&desc->tx_list);

		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.tx_submit = ep93xx_dma_tx_submit;

		ep93xx_dma_desc_put(edmac, desc);
	पूर्ण

	वापस i;

fail_मुक्त_irq:
	मुक्त_irq(edmac->irq, edmac);
fail_clk_disable:
	clk_disable(edmac->clk);

	वापस ret;
पूर्ण

/**
 * ep93xx_dma_मुक्त_chan_resources - release resources क्रम the channel
 * @chan: channel
 *
 * Function releases all the resources allocated क्रम the given channel.
 * The channel must be idle when this is called.
 */
अटल व्योम ep93xx_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_desc *desc, *d;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	BUG_ON(!list_empty(&edmac->active));
	BUG_ON(!list_empty(&edmac->queue));

	spin_lock_irqsave(&edmac->lock, flags);
	edmac->edma->hw_shutकरोwn(edmac);
	edmac->runसमय_addr = 0;
	edmac->runसमय_ctrl = 0;
	edmac->buffer = 0;
	list_splice_init(&edmac->मुक्त_list, &list);
	spin_unlock_irqrestore(&edmac->lock, flags);

	list_क्रम_each_entry_safe(desc, d, &list, node)
		kमुक्त(desc);

	clk_disable(edmac->clk);
	मुक्त_irq(edmac->irq, edmac);
पूर्ण

/**
 * ep93xx_dma_prep_dma_स_नकल - prepare a स_नकल DMA operation
 * @chan: channel
 * @dest: destination bus address
 * @src: source bus address
 * @len: size of the transaction
 * @flags: flags क्रम the descriptor
 *
 * Returns a valid DMA descriptor or %शून्य in हाल of failure.
 */
अटल काष्ठा dma_async_tx_descriptor *
ep93xx_dma_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest,
			   dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_desc *desc, *first;
	माप_प्रकार bytes, offset;

	first = शून्य;
	क्रम (offset = 0; offset < len; offset += bytes) अणु
		desc = ep93xx_dma_desc_get(edmac);
		अगर (!desc) अणु
			dev_warn(chan2dev(edmac), "couldn't get descriptor\n");
			जाओ fail;
		पूर्ण

		bytes = min_t(माप_प्रकार, len - offset, DMA_MAX_CHAN_BYTES);

		desc->src_addr = src + offset;
		desc->dst_addr = dest + offset;
		desc->size = bytes;

		अगर (!first)
			first = desc;
		अन्यथा
			list_add_tail(&desc->node, &first->tx_list);
	पूर्ण

	first->txd.cookie = -EBUSY;
	first->txd.flags = flags;

	वापस &first->txd;
fail:
	ep93xx_dma_desc_put(edmac, first);
	वापस शून्य;
पूर्ण

/**
 * ep93xx_dma_prep_slave_sg - prepare a slave DMA operation
 * @chan: channel
 * @sgl: list of buffers to transfer
 * @sg_len: number of entries in @sgl
 * @dir: direction of tha DMA transfer
 * @flags: flags क्रम the descriptor
 * @context: operation context (ignored)
 *
 * Returns a valid DMA descriptor or %शून्य in हाल of failure.
 */
अटल काष्ठा dma_async_tx_descriptor *
ep93xx_dma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			 अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
			 अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_desc *desc, *first;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (!edmac->edma->m2m && dir != ep93xx_dma_chan_direction(chan)) अणु
		dev_warn(chan2dev(edmac),
			 "channel was configured with different direction\n");
		वापस शून्य;
	पूर्ण

	अगर (test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags)) अणु
		dev_warn(chan2dev(edmac),
			 "channel is already used for cyclic transfers\n");
		वापस शून्य;
	पूर्ण

	ep93xx_dma_slave_config_ग_लिखो(chan, dir, &edmac->slave_config);

	first = शून्य;
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		माप_प्रकार len = sg_dma_len(sg);

		अगर (len > DMA_MAX_CHAN_BYTES) अणु
			dev_warn(chan2dev(edmac), "too big transfer size %zu\n",
				 len);
			जाओ fail;
		पूर्ण

		desc = ep93xx_dma_desc_get(edmac);
		अगर (!desc) अणु
			dev_warn(chan2dev(edmac), "couldn't get descriptor\n");
			जाओ fail;
		पूर्ण

		अगर (dir == DMA_MEM_TO_DEV) अणु
			desc->src_addr = sg_dma_address(sg);
			desc->dst_addr = edmac->runसमय_addr;
		पूर्ण अन्यथा अणु
			desc->src_addr = edmac->runसमय_addr;
			desc->dst_addr = sg_dma_address(sg);
		पूर्ण
		desc->size = len;

		अगर (!first)
			first = desc;
		अन्यथा
			list_add_tail(&desc->node, &first->tx_list);
	पूर्ण

	first->txd.cookie = -EBUSY;
	first->txd.flags = flags;

	वापस &first->txd;

fail:
	ep93xx_dma_desc_put(edmac, first);
	वापस शून्य;
पूर्ण

/**
 * ep93xx_dma_prep_dma_cyclic - prepare a cyclic DMA operation
 * @chan: channel
 * @dma_addr: DMA mapped address of the buffer
 * @buf_len: length of the buffer (in bytes)
 * @period_len: length of a single period
 * @dir: direction of the operation
 * @flags: tx descriptor status flags
 *
 * Prepares a descriptor क्रम cyclic DMA operation. This means that once the
 * descriptor is submitted, we will be submitting in a @period_len sized
 * buffers and calling callback once the period has been elapsed. Transfer
 * terminates only when client calls dmaengine_terminate_all() क्रम this
 * channel.
 *
 * Returns a valid DMA descriptor or %शून्य in हाल of failure.
 */
अटल काष्ठा dma_async_tx_descriptor *
ep93xx_dma_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t dma_addr,
			   माप_प्रकार buf_len, माप_प्रकार period_len,
			   क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_desc *desc, *first;
	माप_प्रकार offset = 0;

	अगर (!edmac->edma->m2m && dir != ep93xx_dma_chan_direction(chan)) अणु
		dev_warn(chan2dev(edmac),
			 "channel was configured with different direction\n");
		वापस शून्य;
	पूर्ण

	अगर (test_and_set_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags)) अणु
		dev_warn(chan2dev(edmac),
			 "channel is already used for cyclic transfers\n");
		वापस शून्य;
	पूर्ण

	अगर (period_len > DMA_MAX_CHAN_BYTES) अणु
		dev_warn(chan2dev(edmac), "too big period length %zu\n",
			 period_len);
		वापस शून्य;
	पूर्ण

	ep93xx_dma_slave_config_ग_लिखो(chan, dir, &edmac->slave_config);

	/* Split the buffer पूर्णांकo period size chunks */
	first = शून्य;
	क्रम (offset = 0; offset < buf_len; offset += period_len) अणु
		desc = ep93xx_dma_desc_get(edmac);
		अगर (!desc) अणु
			dev_warn(chan2dev(edmac), "couldn't get descriptor\n");
			जाओ fail;
		पूर्ण

		अगर (dir == DMA_MEM_TO_DEV) अणु
			desc->src_addr = dma_addr + offset;
			desc->dst_addr = edmac->runसमय_addr;
		पूर्ण अन्यथा अणु
			desc->src_addr = edmac->runसमय_addr;
			desc->dst_addr = dma_addr + offset;
		पूर्ण

		desc->size = period_len;

		अगर (!first)
			first = desc;
		अन्यथा
			list_add_tail(&desc->node, &first->tx_list);
	पूर्ण

	first->txd.cookie = -EBUSY;

	वापस &first->txd;

fail:
	ep93xx_dma_desc_put(edmac, first);
	वापस शून्य;
पूर्ण

/**
 * ep93xx_dma_synchronize - Synchronizes the termination of transfers to the
 * current context.
 * @chan: channel
 *
 * Synchronizes the DMA channel termination to the current context. When this
 * function वापसs it is guaranteed that all transfers क्रम previously issued
 * descriptors have stopped and and it is safe to मुक्त the memory associated
 * with them. Furthermore it is guaranteed that all complete callback functions
 * क्रम a previously submitted descriptor have finished running and it is safe to
 * मुक्त resources accessed from within the complete callbacks.
 */
अटल व्योम ep93xx_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);

	अगर (edmac->edma->hw_synchronize)
		edmac->edma->hw_synchronize(edmac);
पूर्ण

/**
 * ep93xx_dma_terminate_all - terminate all transactions
 * @chan: channel
 *
 * Stops all DMA transactions. All descriptors are put back to the
 * @edmac->मुक्त_list and callbacks are _not_ called.
 */
अटल पूर्णांक ep93xx_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	काष्ठा ep93xx_dma_desc *desc, *_d;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	spin_lock_irqsave(&edmac->lock, flags);
	/* First we disable and flush the DMA channel */
	edmac->edma->hw_shutकरोwn(edmac);
	clear_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags);
	list_splice_init(&edmac->active, &list);
	list_splice_init(&edmac->queue, &list);
	/*
	 * We then re-enable the channel. This way we can जारी submitting
	 * the descriptors by just calling ->hw_submit() again.
	 */
	edmac->edma->hw_setup(edmac);
	spin_unlock_irqrestore(&edmac->lock, flags);

	list_क्रम_each_entry_safe(desc, _d, &list, node)
		ep93xx_dma_desc_put(edmac, desc);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_dma_slave_config(काष्ठा dma_chan *chan,
				   काष्ठा dma_slave_config *config)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);

	स_नकल(&edmac->slave_config, config, माप(*config));

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_dma_slave_config_ग_लिखो(काष्ठा dma_chan *chan,
					 क्रमागत dma_transfer_direction dir,
					 काष्ठा dma_slave_config *config)
अणु
	काष्ठा ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	क्रमागत dma_slave_buswidth width;
	अचिन्हित दीर्घ flags;
	u32 addr, ctrl;

	अगर (!edmac->edma->m2m)
		वापस -EINVAL;

	चयन (dir) अणु
	हाल DMA_DEV_TO_MEM:
		width = config->src_addr_width;
		addr = config->src_addr;
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		width = config->dst_addr_width;
		addr = config->dst_addr;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		ctrl = 0;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		ctrl = M2M_CONTROL_PW_16;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		ctrl = M2M_CONTROL_PW_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&edmac->lock, flags);
	edmac->runसमय_addr = addr;
	edmac->runसमय_ctrl = ctrl;
	spin_unlock_irqrestore(&edmac->lock, flags);

	वापस 0;
पूर्ण

/**
 * ep93xx_dma_tx_status - check अगर a transaction is completed
 * @chan: channel
 * @cookie: transaction specअगरic cookie
 * @state: state of the transaction is stored here अगर given
 *
 * This function can be used to query state of a given transaction.
 */
अटल क्रमागत dma_status ep93xx_dma_tx_status(काष्ठा dma_chan *chan,
					    dma_cookie_t cookie,
					    काष्ठा dma_tx_state *state)
अणु
	वापस dma_cookie_status(chan, cookie, state);
पूर्ण

/**
 * ep93xx_dma_issue_pending - push pending transactions to the hardware
 * @chan: channel
 *
 * When this function is called, all pending transactions are pushed to the
 * hardware and executed.
 */
अटल व्योम ep93xx_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	ep93xx_dma_advance_work(to_ep93xx_dma_chan(chan));
पूर्ण

अटल पूर्णांक __init ep93xx_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_dma_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा ep93xx_dma_engine *edma;
	काष्ठा dma_device *dma_dev;
	माप_प्रकार edma_size;
	पूर्णांक ret, i;

	edma_size = pdata->num_channels * माप(काष्ठा ep93xx_dma_chan);
	edma = kzalloc(माप(*edma) + edma_size, GFP_KERNEL);
	अगर (!edma)
		वापस -ENOMEM;

	dma_dev = &edma->dma_dev;
	edma->m2m = platक्रमm_get_device_id(pdev)->driver_data;
	edma->num_channels = pdata->num_channels;

	INIT_LIST_HEAD(&dma_dev->channels);
	क्रम (i = 0; i < pdata->num_channels; i++) अणु
		स्थिर काष्ठा ep93xx_dma_chan_data *cdata = &pdata->channels[i];
		काष्ठा ep93xx_dma_chan *edmac = &edma->channels[i];

		edmac->chan.device = dma_dev;
		edmac->regs = cdata->base;
		edmac->irq = cdata->irq;
		edmac->edma = edma;

		edmac->clk = clk_get(शून्य, cdata->name);
		अगर (IS_ERR(edmac->clk)) अणु
			dev_warn(&pdev->dev, "failed to get clock for %s\n",
				 cdata->name);
			जारी;
		पूर्ण

		spin_lock_init(&edmac->lock);
		INIT_LIST_HEAD(&edmac->active);
		INIT_LIST_HEAD(&edmac->queue);
		INIT_LIST_HEAD(&edmac->मुक्त_list);
		tasklet_setup(&edmac->tasklet, ep93xx_dma_tasklet);

		list_add_tail(&edmac->chan.device_node,
			      &dma_dev->channels);
	पूर्ण

	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_CYCLIC, dma_dev->cap_mask);

	dma_dev->dev = &pdev->dev;
	dma_dev->device_alloc_chan_resources = ep93xx_dma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = ep93xx_dma_मुक्त_chan_resources;
	dma_dev->device_prep_slave_sg = ep93xx_dma_prep_slave_sg;
	dma_dev->device_prep_dma_cyclic = ep93xx_dma_prep_dma_cyclic;
	dma_dev->device_config = ep93xx_dma_slave_config;
	dma_dev->device_synchronize = ep93xx_dma_synchronize;
	dma_dev->device_terminate_all = ep93xx_dma_terminate_all;
	dma_dev->device_issue_pending = ep93xx_dma_issue_pending;
	dma_dev->device_tx_status = ep93xx_dma_tx_status;

	dma_set_max_seg_size(dma_dev->dev, DMA_MAX_CHAN_BYTES);

	अगर (edma->m2m) अणु
		dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
		dma_dev->device_prep_dma_स_नकल = ep93xx_dma_prep_dma_स_नकल;

		edma->hw_setup = m2m_hw_setup;
		edma->hw_shutकरोwn = m2m_hw_shutकरोwn;
		edma->hw_submit = m2m_hw_submit;
		edma->hw_पूर्णांकerrupt = m2m_hw_पूर्णांकerrupt;
	पूर्ण अन्यथा अणु
		dma_cap_set(DMA_PRIVATE, dma_dev->cap_mask);

		edma->hw_synchronize = m2p_hw_synchronize;
		edma->hw_setup = m2p_hw_setup;
		edma->hw_shutकरोwn = m2p_hw_shutकरोwn;
		edma->hw_submit = m2p_hw_submit;
		edma->hw_पूर्णांकerrupt = m2p_hw_पूर्णांकerrupt;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (unlikely(ret)) अणु
		क्रम (i = 0; i < edma->num_channels; i++) अणु
			काष्ठा ep93xx_dma_chan *edmac = &edma->channels[i];
			अगर (!IS_ERR_OR_शून्य(edmac->clk))
				clk_put(edmac->clk);
		पूर्ण
		kमुक्त(edma);
	पूर्ण अन्यथा अणु
		dev_info(dma_dev->dev, "EP93xx M2%s DMA ready\n",
			 edma->m2m ? "M" : "P");
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ep93xx_dma_driver_ids[] = अणु
	अणु "ep93xx-dma-m2p", 0 पूर्ण,
	अणु "ep93xx-dma-m2m", 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ep93xx_dma_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-dma",
	पूर्ण,
	.id_table	= ep93xx_dma_driver_ids,
पूर्ण;

अटल पूर्णांक __init ep93xx_dma_module_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&ep93xx_dma_driver, ep93xx_dma_probe);
पूर्ण
subsys_initcall(ep93xx_dma_module_init);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@iki.fi>");
MODULE_DESCRIPTION("EP93xx DMA driver");
MODULE_LICENSE("GPL");
