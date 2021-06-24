<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA driver क्रम Xilinx ZynqMP DMA Engine
 *
 * Copyright (C) 2016 Xilinx, Inc. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma/xilinx_dma.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "../dmaengine.h"

/* Register Offsets */
#घोषणा ZYNQMP_DMA_ISR			0x100
#घोषणा ZYNQMP_DMA_IMR			0x104
#घोषणा ZYNQMP_DMA_IER			0x108
#घोषणा ZYNQMP_DMA_IDS			0x10C
#घोषणा ZYNQMP_DMA_CTRL0		0x110
#घोषणा ZYNQMP_DMA_CTRL1		0x114
#घोषणा ZYNQMP_DMA_DATA_ATTR		0x120
#घोषणा ZYNQMP_DMA_DSCR_ATTR		0x124
#घोषणा ZYNQMP_DMA_SRC_DSCR_WRD0	0x128
#घोषणा ZYNQMP_DMA_SRC_DSCR_WRD1	0x12C
#घोषणा ZYNQMP_DMA_SRC_DSCR_WRD2	0x130
#घोषणा ZYNQMP_DMA_SRC_DSCR_WRD3	0x134
#घोषणा ZYNQMP_DMA_DST_DSCR_WRD0	0x138
#घोषणा ZYNQMP_DMA_DST_DSCR_WRD1	0x13C
#घोषणा ZYNQMP_DMA_DST_DSCR_WRD2	0x140
#घोषणा ZYNQMP_DMA_DST_DSCR_WRD3	0x144
#घोषणा ZYNQMP_DMA_SRC_START_LSB	0x158
#घोषणा ZYNQMP_DMA_SRC_START_MSB	0x15C
#घोषणा ZYNQMP_DMA_DST_START_LSB	0x160
#घोषणा ZYNQMP_DMA_DST_START_MSB	0x164
#घोषणा ZYNQMP_DMA_TOTAL_BYTE		0x188
#घोषणा ZYNQMP_DMA_RATE_CTRL		0x18C
#घोषणा ZYNQMP_DMA_IRQ_SRC_ACCT		0x190
#घोषणा ZYNQMP_DMA_IRQ_DST_ACCT		0x194
#घोषणा ZYNQMP_DMA_CTRL2		0x200

/* Interrupt रेजिस्टरs bit field definitions */
#घोषणा ZYNQMP_DMA_DONE			BIT(10)
#घोषणा ZYNQMP_DMA_AXI_WR_DATA		BIT(9)
#घोषणा ZYNQMP_DMA_AXI_RD_DATA		BIT(8)
#घोषणा ZYNQMP_DMA_AXI_RD_DST_DSCR	BIT(7)
#घोषणा ZYNQMP_DMA_AXI_RD_SRC_DSCR	BIT(6)
#घोषणा ZYNQMP_DMA_IRQ_DST_ACCT_ERR	BIT(5)
#घोषणा ZYNQMP_DMA_IRQ_SRC_ACCT_ERR	BIT(4)
#घोषणा ZYNQMP_DMA_BYTE_CNT_OVRFL	BIT(3)
#घोषणा ZYNQMP_DMA_DST_DSCR_DONE	BIT(2)
#घोषणा ZYNQMP_DMA_INV_APB		BIT(0)

/* Control 0 रेजिस्टर bit field definitions */
#घोषणा ZYNQMP_DMA_OVR_FETCH		BIT(7)
#घोषणा ZYNQMP_DMA_POINT_TYPE_SG	BIT(6)
#घोषणा ZYNQMP_DMA_RATE_CTRL_EN		BIT(3)

/* Control 1 रेजिस्टर bit field definitions */
#घोषणा ZYNQMP_DMA_SRC_ISSUE		GENMASK(4, 0)

/* Data Attribute रेजिस्टर bit field definitions */
#घोषणा ZYNQMP_DMA_ARBURST		GENMASK(27, 26)
#घोषणा ZYNQMP_DMA_ARCACHE		GENMASK(25, 22)
#घोषणा ZYNQMP_DMA_ARCACHE_OFST		22
#घोषणा ZYNQMP_DMA_ARQOS		GENMASK(21, 18)
#घोषणा ZYNQMP_DMA_ARQOS_OFST		18
#घोषणा ZYNQMP_DMA_ARLEN		GENMASK(17, 14)
#घोषणा ZYNQMP_DMA_ARLEN_OFST		14
#घोषणा ZYNQMP_DMA_AWBURST		GENMASK(13, 12)
#घोषणा ZYNQMP_DMA_AWCACHE		GENMASK(11, 8)
#घोषणा ZYNQMP_DMA_AWCACHE_OFST		8
#घोषणा ZYNQMP_DMA_AWQOS		GENMASK(7, 4)
#घोषणा ZYNQMP_DMA_AWQOS_OFST		4
#घोषणा ZYNQMP_DMA_AWLEN		GENMASK(3, 0)
#घोषणा ZYNQMP_DMA_AWLEN_OFST		0

/* Descriptor Attribute रेजिस्टर bit field definitions */
#घोषणा ZYNQMP_DMA_AXCOHRNT		BIT(8)
#घोषणा ZYNQMP_DMA_AXCACHE		GENMASK(7, 4)
#घोषणा ZYNQMP_DMA_AXCACHE_OFST		4
#घोषणा ZYNQMP_DMA_AXQOS		GENMASK(3, 0)
#घोषणा ZYNQMP_DMA_AXQOS_OFST		0

/* Control रेजिस्टर 2 bit field definitions */
#घोषणा ZYNQMP_DMA_ENABLE		BIT(0)

/* Buffer Descriptor definitions */
#घोषणा ZYNQMP_DMA_DESC_CTRL_STOP	0x10
#घोषणा ZYNQMP_DMA_DESC_CTRL_COMP_INT	0x4
#घोषणा ZYNQMP_DMA_DESC_CTRL_SIZE_256	0x2
#घोषणा ZYNQMP_DMA_DESC_CTRL_COHRNT	0x1

/* Interrupt Mask specअगरic definitions */
#घोषणा ZYNQMP_DMA_INT_ERR	(ZYNQMP_DMA_AXI_RD_DATA | \
				ZYNQMP_DMA_AXI_WR_DATA | \
				ZYNQMP_DMA_AXI_RD_DST_DSCR | \
				ZYNQMP_DMA_AXI_RD_SRC_DSCR | \
				ZYNQMP_DMA_INV_APB)
#घोषणा ZYNQMP_DMA_INT_OVRFL	(ZYNQMP_DMA_BYTE_CNT_OVRFL | \
				ZYNQMP_DMA_IRQ_SRC_ACCT_ERR | \
				ZYNQMP_DMA_IRQ_DST_ACCT_ERR)
#घोषणा ZYNQMP_DMA_INT_DONE	(ZYNQMP_DMA_DONE | ZYNQMP_DMA_DST_DSCR_DONE)
#घोषणा ZYNQMP_DMA_INT_EN_DEFAULT_MASK	(ZYNQMP_DMA_INT_DONE | \
					ZYNQMP_DMA_INT_ERR | \
					ZYNQMP_DMA_INT_OVRFL | \
					ZYNQMP_DMA_DST_DSCR_DONE)

/* Max number of descriptors per channel */
#घोषणा ZYNQMP_DMA_NUM_DESCS	32

/* Max transfer size per descriptor */
#घोषणा ZYNQMP_DMA_MAX_TRANS_LEN	0x40000000

/* Max burst lengths */
#घोषणा ZYNQMP_DMA_MAX_DST_BURST_LEN    32768U
#घोषणा ZYNQMP_DMA_MAX_SRC_BURST_LEN    32768U

/* Reset values क्रम data attributes */
#घोषणा ZYNQMP_DMA_AXCACHE_VAL		0xF

#घोषणा ZYNQMP_DMA_SRC_ISSUE_RST_VAL	0x1F

#घोषणा ZYNQMP_DMA_IDS_DEFAULT_MASK	0xFFF

/* Bus width in bits */
#घोषणा ZYNQMP_DMA_BUS_WIDTH_64		64
#घोषणा ZYNQMP_DMA_BUS_WIDTH_128	128

#घोषणा ZDMA_PM_TIMEOUT			100

#घोषणा ZYNQMP_DMA_DESC_SIZE(chan)	(chan->desc_size)

#घोषणा to_chan(chan)		container_of(chan, काष्ठा zynqmp_dma_chan, \
					     common)
#घोषणा tx_to_desc(tx)		container_of(tx, काष्ठा zynqmp_dma_desc_sw, \
					     async_tx)

/**
 * काष्ठा zynqmp_dma_desc_ll - Hw linked list descriptor
 * @addr: Buffer address
 * @size: Size of the buffer
 * @ctrl: Control word
 * @nxtdscraddr: Next descriptor base address
 * @rsvd: Reserved field and क्रम Hw पूर्णांकernal use.
 */
काष्ठा zynqmp_dma_desc_ll अणु
	u64 addr;
	u32 size;
	u32 ctrl;
	u64 nxtdscraddr;
	u64 rsvd;
पूर्ण;

/**
 * काष्ठा zynqmp_dma_desc_sw - Per Transaction काष्ठाure
 * @src: Source address क्रम simple mode dma
 * @dst: Destination address क्रम simple mode dma
 * @len: Transfer length क्रम simple mode dma
 * @node: Node in the channel descriptor list
 * @tx_list: List head क्रम the current transfer
 * @async_tx: Async transaction descriptor
 * @src_v: Virtual address of the src descriptor
 * @src_p: Physical address of the src descriptor
 * @dst_v: Virtual address of the dst descriptor
 * @dst_p: Physical address of the dst descriptor
 */
काष्ठा zynqmp_dma_desc_sw अणु
	u64 src;
	u64 dst;
	u32 len;
	काष्ठा list_head node;
	काष्ठा list_head tx_list;
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा zynqmp_dma_desc_ll *src_v;
	dma_addr_t src_p;
	काष्ठा zynqmp_dma_desc_ll *dst_v;
	dma_addr_t dst_p;
पूर्ण;

/**
 * काष्ठा zynqmp_dma_chan - Driver specअगरic DMA channel काष्ठाure
 * @zdev: Driver specअगरic device काष्ठाure
 * @regs: Control रेजिस्टरs offset
 * @lock: Descriptor operation lock
 * @pending_list: Descriptors रुकोing
 * @मुक्त_list: Descriptors मुक्त
 * @active_list: Descriptors active
 * @sw_desc_pool: SW descriptor pool
 * @करोne_list: Complete descriptors
 * @common: DMA common channel
 * @desc_pool_v: Statically allocated descriptor base
 * @desc_pool_p: Physical allocated descriptor base
 * @desc_मुक्त_cnt: Descriptor available count
 * @dev: The dma device
 * @irq: Channel IRQ
 * @is_dmacoherent: Tells whether dma operations are coherent or not
 * @tasklet: Cleanup work after irq
 * @idle : Channel status;
 * @desc_size: Size of the low level descriptor
 * @err: Channel has errors
 * @bus_width: Bus width
 * @src_burst_len: Source burst length
 * @dst_burst_len: Dest burst length
 */
काष्ठा zynqmp_dma_chan अणु
	काष्ठा zynqmp_dma_device *zdev;
	व्योम __iomem *regs;
	spinlock_t lock;
	काष्ठा list_head pending_list;
	काष्ठा list_head मुक्त_list;
	काष्ठा list_head active_list;
	काष्ठा zynqmp_dma_desc_sw *sw_desc_pool;
	काष्ठा list_head करोne_list;
	काष्ठा dma_chan common;
	व्योम *desc_pool_v;
	dma_addr_t desc_pool_p;
	u32 desc_मुक्त_cnt;
	काष्ठा device *dev;
	पूर्णांक irq;
	bool is_dmacoherent;
	काष्ठा tasklet_काष्ठा tasklet;
	bool idle;
	u32 desc_size;
	bool err;
	u32 bus_width;
	u32 src_burst_len;
	u32 dst_burst_len;
पूर्ण;

/**
 * काष्ठा zynqmp_dma_device - DMA device काष्ठाure
 * @dev: Device Structure
 * @common: DMA device काष्ठाure
 * @chan: Driver specअगरic DMA channel
 * @clk_मुख्य: Poपूर्णांकer to मुख्य घड़ी
 * @clk_apb: Poपूर्णांकer to apb घड़ी
 */
काष्ठा zynqmp_dma_device अणु
	काष्ठा device *dev;
	काष्ठा dma_device common;
	काष्ठा zynqmp_dma_chan *chan;
	काष्ठा clk *clk_मुख्य;
	काष्ठा clk *clk_apb;
पूर्ण;

अटल अंतरभूत व्योम zynqmp_dma_ग_लिखोq(काष्ठा zynqmp_dma_chan *chan, u32 reg,
				     u64 value)
अणु
	lo_hi_ग_लिखोq(value, chan->regs + reg);
पूर्ण

/**
 * zynqmp_dma_update_desc_to_ctrlr - Updates descriptor to the controller
 * @chan: ZynqMP DMA DMA channel poपूर्णांकer
 * @desc: Transaction descriptor poपूर्णांकer
 */
अटल व्योम zynqmp_dma_update_desc_to_ctrlr(काष्ठा zynqmp_dma_chan *chan,
				      काष्ठा zynqmp_dma_desc_sw *desc)
अणु
	dma_addr_t addr;

	addr = desc->src_p;
	zynqmp_dma_ग_लिखोq(chan, ZYNQMP_DMA_SRC_START_LSB, addr);
	addr = desc->dst_p;
	zynqmp_dma_ग_लिखोq(chan, ZYNQMP_DMA_DST_START_LSB, addr);
पूर्ण

/**
 * zynqmp_dma_desc_config_eod - Mark the descriptor as end descriptor
 * @chan: ZynqMP DMA channel poपूर्णांकer
 * @desc: Hw descriptor poपूर्णांकer
 */
अटल व्योम zynqmp_dma_desc_config_eod(काष्ठा zynqmp_dma_chan *chan,
				       व्योम *desc)
अणु
	काष्ठा zynqmp_dma_desc_ll *hw = (काष्ठा zynqmp_dma_desc_ll *)desc;

	hw->ctrl |= ZYNQMP_DMA_DESC_CTRL_STOP;
	hw++;
	hw->ctrl |= ZYNQMP_DMA_DESC_CTRL_COMP_INT | ZYNQMP_DMA_DESC_CTRL_STOP;
पूर्ण

/**
 * zynqmp_dma_config_sg_ll_desc - Configure the linked list descriptor
 * @chan: ZynqMP DMA channel poपूर्णांकer
 * @sdesc: Hw descriptor poपूर्णांकer
 * @src: Source buffer address
 * @dst: Destination buffer address
 * @len: Transfer length
 * @prev: Previous hw descriptor poपूर्णांकer
 */
अटल व्योम zynqmp_dma_config_sg_ll_desc(काष्ठा zynqmp_dma_chan *chan,
				   काष्ठा zynqmp_dma_desc_ll *sdesc,
				   dma_addr_t src, dma_addr_t dst, माप_प्रकार len,
				   काष्ठा zynqmp_dma_desc_ll *prev)
अणु
	काष्ठा zynqmp_dma_desc_ll *ddesc = sdesc + 1;

	sdesc->size = ddesc->size = len;
	sdesc->addr = src;
	ddesc->addr = dst;

	sdesc->ctrl = ddesc->ctrl = ZYNQMP_DMA_DESC_CTRL_SIZE_256;
	अगर (chan->is_dmacoherent) अणु
		sdesc->ctrl |= ZYNQMP_DMA_DESC_CTRL_COHRNT;
		ddesc->ctrl |= ZYNQMP_DMA_DESC_CTRL_COHRNT;
	पूर्ण

	अगर (prev) अणु
		dma_addr_t addr = chan->desc_pool_p +
			    ((uपूर्णांकptr_t)sdesc - (uपूर्णांकptr_t)chan->desc_pool_v);
		ddesc = prev + 1;
		prev->nxtdscraddr = addr;
		ddesc->nxtdscraddr = addr + ZYNQMP_DMA_DESC_SIZE(chan);
	पूर्ण
पूर्ण

/**
 * zynqmp_dma_init - Initialize the channel
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_init(काष्ठा zynqmp_dma_chan *chan)
अणु
	u32 val;

	ग_लिखोl(ZYNQMP_DMA_IDS_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IDS);
	val = पढ़ोl(chan->regs + ZYNQMP_DMA_ISR);
	ग_लिखोl(val, chan->regs + ZYNQMP_DMA_ISR);

	अगर (chan->is_dmacoherent) अणु
		val = ZYNQMP_DMA_AXCOHRNT;
		val = (val & ~ZYNQMP_DMA_AXCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_AXCACHE_OFST);
		ग_लिखोl(val, chan->regs + ZYNQMP_DMA_DSCR_ATTR);
	पूर्ण

	val = पढ़ोl(chan->regs + ZYNQMP_DMA_DATA_ATTR);
	अगर (chan->is_dmacoherent) अणु
		val = (val & ~ZYNQMP_DMA_ARCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_ARCACHE_OFST);
		val = (val & ~ZYNQMP_DMA_AWCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_AWCACHE_OFST);
	पूर्ण
	ग_लिखोl(val, chan->regs + ZYNQMP_DMA_DATA_ATTR);

	/* Clearing the पूर्णांकerrupt account rgisters */
	val = पढ़ोl(chan->regs + ZYNQMP_DMA_IRQ_SRC_ACCT);
	val = पढ़ोl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);

	chan->idle = true;
पूर्ण

/**
 * zynqmp_dma_tx_submit - Submit DMA transaction
 * @tx: Async transaction descriptor poपूर्णांकer
 *
 * Return: cookie value
 */
अटल dma_cookie_t zynqmp_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(tx->chan);
	काष्ठा zynqmp_dma_desc_sw *desc, *new;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ irqflags;

	new = tx_to_desc(tx);
	spin_lock_irqsave(&chan->lock, irqflags);
	cookie = dma_cookie_assign(tx);

	अगर (!list_empty(&chan->pending_list)) अणु
		desc = list_last_entry(&chan->pending_list,
				     काष्ठा zynqmp_dma_desc_sw, node);
		अगर (!list_empty(&desc->tx_list))
			desc = list_last_entry(&desc->tx_list,
					       काष्ठा zynqmp_dma_desc_sw, node);
		desc->src_v->nxtdscraddr = new->src_p;
		desc->src_v->ctrl &= ~ZYNQMP_DMA_DESC_CTRL_STOP;
		desc->dst_v->nxtdscraddr = new->dst_p;
		desc->dst_v->ctrl &= ~ZYNQMP_DMA_DESC_CTRL_STOP;
	पूर्ण

	list_add_tail(&new->node, &chan->pending_list);
	spin_unlock_irqrestore(&chan->lock, irqflags);

	वापस cookie;
पूर्ण

/**
 * zynqmp_dma_get_descriptor - Get the sw descriptor from the pool
 * @chan: ZynqMP DMA channel poपूर्णांकer
 *
 * Return: The sw descriptor
 */
अटल काष्ठा zynqmp_dma_desc_sw *
zynqmp_dma_get_descriptor(काष्ठा zynqmp_dma_chan *chan)
अणु
	काष्ठा zynqmp_dma_desc_sw *desc;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);
	desc = list_first_entry(&chan->मुक्त_list,
				काष्ठा zynqmp_dma_desc_sw, node);
	list_del(&desc->node);
	spin_unlock_irqrestore(&chan->lock, irqflags);

	INIT_LIST_HEAD(&desc->tx_list);
	/* Clear the src and dst descriptor memory */
	स_रखो((व्योम *)desc->src_v, 0, ZYNQMP_DMA_DESC_SIZE(chan));
	स_रखो((व्योम *)desc->dst_v, 0, ZYNQMP_DMA_DESC_SIZE(chan));

	वापस desc;
पूर्ण

/**
 * zynqmp_dma_मुक्त_descriptor - Issue pending transactions
 * @chan: ZynqMP DMA channel poपूर्णांकer
 * @sdesc: Transaction descriptor poपूर्णांकer
 */
अटल व्योम zynqmp_dma_मुक्त_descriptor(काष्ठा zynqmp_dma_chan *chan,
				 काष्ठा zynqmp_dma_desc_sw *sdesc)
अणु
	काष्ठा zynqmp_dma_desc_sw *child, *next;

	chan->desc_मुक्त_cnt++;
	list_del(&sdesc->node);
	list_add_tail(&sdesc->node, &chan->मुक्त_list);
	list_क्रम_each_entry_safe(child, next, &sdesc->tx_list, node) अणु
		chan->desc_मुक्त_cnt++;
		list_move_tail(&child->node, &chan->मुक्त_list);
	पूर्ण
पूर्ण

/**
 * zynqmp_dma_मुक्त_desc_list - Free descriptors list
 * @chan: ZynqMP DMA channel poपूर्णांकer
 * @list: List to parse and delete the descriptor
 */
अटल व्योम zynqmp_dma_मुक्त_desc_list(काष्ठा zynqmp_dma_chan *chan,
				      काष्ठा list_head *list)
अणु
	काष्ठा zynqmp_dma_desc_sw *desc, *next;

	list_क्रम_each_entry_safe(desc, next, list, node)
		zynqmp_dma_मुक्त_descriptor(chan, desc);
पूर्ण

/**
 * zynqmp_dma_alloc_chan_resources - Allocate channel resources
 * @dchan: DMA channel
 *
 * Return: Number of descriptors on success and failure value on error
 */
अटल पूर्णांक zynqmp_dma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(dchan);
	काष्ठा zynqmp_dma_desc_sw *desc;
	पूर्णांक i, ret;

	ret = pm_runसमय_resume_and_get(chan->dev);
	अगर (ret < 0)
		वापस ret;

	chan->sw_desc_pool = kसुस्मृति(ZYNQMP_DMA_NUM_DESCS, माप(*desc),
				     GFP_KERNEL);
	अगर (!chan->sw_desc_pool)
		वापस -ENOMEM;

	chan->idle = true;
	chan->desc_मुक्त_cnt = ZYNQMP_DMA_NUM_DESCS;

	INIT_LIST_HEAD(&chan->मुक्त_list);

	क्रम (i = 0; i < ZYNQMP_DMA_NUM_DESCS; i++) अणु
		desc = chan->sw_desc_pool + i;
		dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
		desc->async_tx.tx_submit = zynqmp_dma_tx_submit;
		list_add_tail(&desc->node, &chan->मुक्त_list);
	पूर्ण

	chan->desc_pool_v = dma_alloc_coherent(chan->dev,
					       (2 * chan->desc_size * ZYNQMP_DMA_NUM_DESCS),
					       &chan->desc_pool_p, GFP_KERNEL);
	अगर (!chan->desc_pool_v)
		वापस -ENOMEM;

	क्रम (i = 0; i < ZYNQMP_DMA_NUM_DESCS; i++) अणु
		desc = chan->sw_desc_pool + i;
		desc->src_v = (काष्ठा zynqmp_dma_desc_ll *) (chan->desc_pool_v +
					(i * ZYNQMP_DMA_DESC_SIZE(chan) * 2));
		desc->dst_v = (काष्ठा zynqmp_dma_desc_ll *) (desc->src_v + 1);
		desc->src_p = chan->desc_pool_p +
				(i * ZYNQMP_DMA_DESC_SIZE(chan) * 2);
		desc->dst_p = desc->src_p + ZYNQMP_DMA_DESC_SIZE(chan);
	पूर्ण

	वापस ZYNQMP_DMA_NUM_DESCS;
पूर्ण

/**
 * zynqmp_dma_start - Start DMA channel
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_start(काष्ठा zynqmp_dma_chan *chan)
अणु
	ग_लिखोl(ZYNQMP_DMA_INT_EN_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IER);
	ग_लिखोl(0, chan->regs + ZYNQMP_DMA_TOTAL_BYTE);
	chan->idle = false;
	ग_लिखोl(ZYNQMP_DMA_ENABLE, chan->regs + ZYNQMP_DMA_CTRL2);
पूर्ण

/**
 * zynqmp_dma_handle_ovfl_पूर्णांक - Process the overflow पूर्णांकerrupt
 * @chan: ZynqMP DMA channel poपूर्णांकer
 * @status: Interrupt status value
 */
अटल व्योम zynqmp_dma_handle_ovfl_पूर्णांक(काष्ठा zynqmp_dma_chan *chan, u32 status)
अणु
	अगर (status & ZYNQMP_DMA_BYTE_CNT_OVRFL)
		ग_लिखोl(0, chan->regs + ZYNQMP_DMA_TOTAL_BYTE);
	अगर (status & ZYNQMP_DMA_IRQ_DST_ACCT_ERR)
		पढ़ोl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);
	अगर (status & ZYNQMP_DMA_IRQ_SRC_ACCT_ERR)
		पढ़ोl(chan->regs + ZYNQMP_DMA_IRQ_SRC_ACCT);
पूर्ण

अटल व्योम zynqmp_dma_config(काष्ठा zynqmp_dma_chan *chan)
अणु
	u32 val, burst_val;

	val = पढ़ोl(chan->regs + ZYNQMP_DMA_CTRL0);
	val |= ZYNQMP_DMA_POINT_TYPE_SG;
	ग_लिखोl(val, chan->regs + ZYNQMP_DMA_CTRL0);

	val = पढ़ोl(chan->regs + ZYNQMP_DMA_DATA_ATTR);
	burst_val = __ilog2_u32(chan->src_burst_len);
	val = (val & ~ZYNQMP_DMA_ARLEN) |
		((burst_val << ZYNQMP_DMA_ARLEN_OFST) & ZYNQMP_DMA_ARLEN);
	burst_val = __ilog2_u32(chan->dst_burst_len);
	val = (val & ~ZYNQMP_DMA_AWLEN) |
		((burst_val << ZYNQMP_DMA_AWLEN_OFST) & ZYNQMP_DMA_AWLEN);
	ग_लिखोl(val, chan->regs + ZYNQMP_DMA_DATA_ATTR);
पूर्ण

/**
 * zynqmp_dma_device_config - Zynqmp dma device configuration
 * @dchan: DMA channel
 * @config: DMA device config
 *
 * Return: 0 always
 */
अटल पूर्णांक zynqmp_dma_device_config(काष्ठा dma_chan *dchan,
				    काष्ठा dma_slave_config *config)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(dchan);

	chan->src_burst_len = clamp(config->src_maxburst, 1U,
		ZYNQMP_DMA_MAX_SRC_BURST_LEN);
	chan->dst_burst_len = clamp(config->dst_maxburst, 1U,
		ZYNQMP_DMA_MAX_DST_BURST_LEN);

	वापस 0;
पूर्ण

/**
 * zynqmp_dma_start_transfer - Initiate the new transfer
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_start_transfer(काष्ठा zynqmp_dma_chan *chan)
अणु
	काष्ठा zynqmp_dma_desc_sw *desc;

	अगर (!chan->idle)
		वापस;

	zynqmp_dma_config(chan);

	desc = list_first_entry_or_null(&chan->pending_list,
					काष्ठा zynqmp_dma_desc_sw, node);
	अगर (!desc)
		वापस;

	list_splice_tail_init(&chan->pending_list, &chan->active_list);
	zynqmp_dma_update_desc_to_ctrlr(chan, desc);
	zynqmp_dma_start(chan);
पूर्ण


/**
 * zynqmp_dma_chan_desc_cleanup - Cleanup the completed descriptors
 * @chan: ZynqMP DMA channel
 */
अटल व्योम zynqmp_dma_chan_desc_cleanup(काष्ठा zynqmp_dma_chan *chan)
अणु
	काष्ठा zynqmp_dma_desc_sw *desc, *next;

	list_क्रम_each_entry_safe(desc, next, &chan->करोne_list, node) अणु
		dma_async_tx_callback callback;
		व्योम *callback_param;

		callback = desc->async_tx.callback;
		callback_param = desc->async_tx.callback_param;
		अगर (callback) अणु
			spin_unlock(&chan->lock);
			callback(callback_param);
			spin_lock(&chan->lock);
		पूर्ण

		/* Run any dependencies, then मुक्त the descriptor */
		zynqmp_dma_मुक्त_descriptor(chan, desc);
	पूर्ण
पूर्ण

/**
 * zynqmp_dma_complete_descriptor - Mark the active descriptor as complete
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_complete_descriptor(काष्ठा zynqmp_dma_chan *chan)
अणु
	काष्ठा zynqmp_dma_desc_sw *desc;

	desc = list_first_entry_or_null(&chan->active_list,
					काष्ठा zynqmp_dma_desc_sw, node);
	अगर (!desc)
		वापस;
	list_del(&desc->node);
	dma_cookie_complete(&desc->async_tx);
	list_add_tail(&desc->node, &chan->करोne_list);
पूर्ण

/**
 * zynqmp_dma_issue_pending - Issue pending transactions
 * @dchan: DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(dchan);
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);
	zynqmp_dma_start_transfer(chan);
	spin_unlock_irqrestore(&chan->lock, irqflags);
पूर्ण

/**
 * zynqmp_dma_मुक्त_descriptors - Free channel descriptors
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_मुक्त_descriptors(काष्ठा zynqmp_dma_chan *chan)
अणु
	zynqmp_dma_मुक्त_desc_list(chan, &chan->active_list);
	zynqmp_dma_मुक्त_desc_list(chan, &chan->pending_list);
	zynqmp_dma_मुक्त_desc_list(chan, &chan->करोne_list);
पूर्ण

/**
 * zynqmp_dma_मुक्त_chan_resources - Free channel resources
 * @dchan: DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(dchan);
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);
	zynqmp_dma_मुक्त_descriptors(chan);
	spin_unlock_irqrestore(&chan->lock, irqflags);
	dma_मुक्त_coherent(chan->dev,
		(2 * ZYNQMP_DMA_DESC_SIZE(chan) * ZYNQMP_DMA_NUM_DESCS),
		chan->desc_pool_v, chan->desc_pool_p);
	kमुक्त(chan->sw_desc_pool);
	pm_runसमय_mark_last_busy(chan->dev);
	pm_runसमय_put_स्वतःsuspend(chan->dev);
पूर्ण

/**
 * zynqmp_dma_reset - Reset the channel
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_reset(काष्ठा zynqmp_dma_chan *chan)
अणु
	ग_लिखोl(ZYNQMP_DMA_IDS_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IDS);

	zynqmp_dma_complete_descriptor(chan);
	zynqmp_dma_chan_desc_cleanup(chan);
	zynqmp_dma_मुक्त_descriptors(chan);
	zynqmp_dma_init(chan);
पूर्ण

/**
 * zynqmp_dma_irq_handler - ZynqMP DMA Interrupt handler
 * @irq: IRQ number
 * @data: Poपूर्णांकer to the ZynqMP DMA channel काष्ठाure
 *
 * Return: IRQ_HANDLED/IRQ_NONE
 */
अटल irqवापस_t zynqmp_dma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा zynqmp_dma_chan *chan = (काष्ठा zynqmp_dma_chan *)data;
	u32 isr, imr, status;
	irqवापस_t ret = IRQ_NONE;

	isr = पढ़ोl(chan->regs + ZYNQMP_DMA_ISR);
	imr = पढ़ोl(chan->regs + ZYNQMP_DMA_IMR);
	status = isr & ~imr;

	ग_लिखोl(isr, chan->regs + ZYNQMP_DMA_ISR);
	अगर (status & ZYNQMP_DMA_INT_DONE) अणु
		tasklet_schedule(&chan->tasklet);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status & ZYNQMP_DMA_DONE)
		chan->idle = true;

	अगर (status & ZYNQMP_DMA_INT_ERR) अणु
		chan->err = true;
		tasklet_schedule(&chan->tasklet);
		dev_err(chan->dev, "Channel %p has errors\n", chan);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status & ZYNQMP_DMA_INT_OVRFL) अणु
		zynqmp_dma_handle_ovfl_पूर्णांक(chan, status);
		dev_dbg(chan->dev, "Channel %p overflow interrupt\n", chan);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * zynqmp_dma_करो_tasklet - Schedule completion tasklet
 * @t: Poपूर्णांकer to the ZynqMP DMA channel काष्ठाure
 */
अटल व्योम zynqmp_dma_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा zynqmp_dma_chan *chan = from_tasklet(chan, t, tasklet);
	u32 count;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);

	अगर (chan->err) अणु
		zynqmp_dma_reset(chan);
		chan->err = false;
		जाओ unlock;
	पूर्ण

	count = पढ़ोl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);

	जबतक (count) अणु
		zynqmp_dma_complete_descriptor(chan);
		zynqmp_dma_chan_desc_cleanup(chan);
		count--;
	पूर्ण

	अगर (chan->idle)
		zynqmp_dma_start_transfer(chan);

unlock:
	spin_unlock_irqrestore(&chan->lock, irqflags);
पूर्ण

/**
 * zynqmp_dma_device_terminate_all - Aborts all transfers on a channel
 * @dchan: DMA channel poपूर्णांकer
 *
 * Return: Always '0'
 */
अटल पूर्णांक zynqmp_dma_device_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा zynqmp_dma_chan *chan = to_chan(dchan);
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);
	ग_लिखोl(ZYNQMP_DMA_IDS_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IDS);
	zynqmp_dma_मुक्त_descriptors(chan);
	spin_unlock_irqrestore(&chan->lock, irqflags);

	वापस 0;
पूर्ण

/**
 * zynqmp_dma_prep_स_नकल - prepare descriptors क्रम स_नकल transaction
 * @dchan: DMA channel
 * @dma_dst: Destination buffer address
 * @dma_src: Source buffer address
 * @len: Transfer length
 * @flags: transfer ack flags
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *zynqmp_dma_prep_स_नकल(
				काष्ठा dma_chan *dchan, dma_addr_t dma_dst,
				dma_addr_t dma_src, माप_प्रकार len, uदीर्घ flags)
अणु
	काष्ठा zynqmp_dma_chan *chan;
	काष्ठा zynqmp_dma_desc_sw *new, *first = शून्य;
	व्योम *desc = शून्य, *prev = शून्य;
	माप_प्रकार copy;
	u32 desc_cnt;
	अचिन्हित दीर्घ irqflags;

	chan = to_chan(dchan);

	desc_cnt = DIV_ROUND_UP(len, ZYNQMP_DMA_MAX_TRANS_LEN);

	spin_lock_irqsave(&chan->lock, irqflags);
	अगर (desc_cnt > chan->desc_मुक्त_cnt) अणु
		spin_unlock_irqrestore(&chan->lock, irqflags);
		dev_dbg(chan->dev, "chan %p descs are not available\n", chan);
		वापस शून्य;
	पूर्ण
	chan->desc_मुक्त_cnt = chan->desc_मुक्त_cnt - desc_cnt;
	spin_unlock_irqrestore(&chan->lock, irqflags);

	करो अणु
		/* Allocate and populate the descriptor */
		new = zynqmp_dma_get_descriptor(chan);

		copy = min_t(माप_प्रकार, len, ZYNQMP_DMA_MAX_TRANS_LEN);
		desc = (काष्ठा zynqmp_dma_desc_ll *)new->src_v;
		zynqmp_dma_config_sg_ll_desc(chan, desc, dma_src,
					     dma_dst, copy, prev);
		prev = desc;
		len -= copy;
		dma_src += copy;
		dma_dst += copy;
		अगर (!first)
			first = new;
		अन्यथा
			list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	zynqmp_dma_desc_config_eod(chan, desc);
	async_tx_ack(&first->async_tx);
	first->async_tx.flags = flags;
	वापस &first->async_tx;
पूर्ण

/**
 * zynqmp_dma_chan_हटाओ - Channel हटाओ function
 * @chan: ZynqMP DMA channel poपूर्णांकer
 */
अटल व्योम zynqmp_dma_chan_हटाओ(काष्ठा zynqmp_dma_chan *chan)
अणु
	अगर (!chan)
		वापस;

	अगर (chan->irq)
		devm_मुक्त_irq(chan->zdev->dev, chan->irq, chan);
	tasklet_समाप्त(&chan->tasklet);
	list_del(&chan->common.device_node);
पूर्ण

/**
 * zynqmp_dma_chan_probe - Per Channel Probing
 * @zdev: Driver specअगरic device काष्ठाure
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक zynqmp_dma_chan_probe(काष्ठा zynqmp_dma_device *zdev,
			   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dma_chan *chan;
	काष्ठा resource *res;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक err;

	chan = devm_kzalloc(zdev->dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;
	chan->dev = zdev->dev;
	chan->zdev = zdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	chan->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(chan->regs))
		वापस PTR_ERR(chan->regs);

	chan->bus_width = ZYNQMP_DMA_BUS_WIDTH_64;
	chan->dst_burst_len = ZYNQMP_DMA_MAX_DST_BURST_LEN;
	chan->src_burst_len = ZYNQMP_DMA_MAX_SRC_BURST_LEN;
	err = of_property_पढ़ो_u32(node, "xlnx,bus-width", &chan->bus_width);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "missing xlnx,bus-width property\n");
		वापस err;
	पूर्ण

	अगर (chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_64 &&
	    chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_128) अणु
		dev_err(zdev->dev, "invalid bus-width value");
		वापस -EINVAL;
	पूर्ण

	chan->is_dmacoherent =  of_property_पढ़ो_bool(node, "dma-coherent");
	zdev->chan = chan;
	tasklet_setup(&chan->tasklet, zynqmp_dma_करो_tasklet);
	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->active_list);
	INIT_LIST_HEAD(&chan->pending_list);
	INIT_LIST_HEAD(&chan->करोne_list);
	INIT_LIST_HEAD(&chan->मुक्त_list);

	dma_cookie_init(&chan->common);
	chan->common.device = &zdev->common;
	list_add_tail(&chan->common.device_node, &zdev->common.channels);

	zynqmp_dma_init(chan);
	chan->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chan->irq < 0)
		वापस -ENXIO;
	err = devm_request_irq(&pdev->dev, chan->irq, zynqmp_dma_irq_handler, 0,
			       "zynqmp-dma", chan);
	अगर (err)
		वापस err;

	chan->desc_size = माप(काष्ठा zynqmp_dma_desc_ll);
	chan->idle = true;
	वापस 0;
पूर्ण

/**
 * of_zynqmp_dma_xlate - Translation function
 * @dma_spec: Poपूर्णांकer to DMA specअगरier as found in the device tree
 * @ofdma: Poपूर्णांकer to DMA controller data
 *
 * Return: DMA channel poपूर्णांकer on success and शून्य on error
 */
अटल काष्ठा dma_chan *of_zynqmp_dma_xlate(काष्ठा of_phandle_args *dma_spec,
					    काष्ठा of_dma *ofdma)
अणु
	काष्ठा zynqmp_dma_device *zdev = ofdma->of_dma_data;

	वापस dma_get_slave_channel(&zdev->chan->common);
पूर्ण

/**
 * zynqmp_dma_suspend - Suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक __maybe_unused zynqmp_dma_suspend(काष्ठा device *dev)
अणु
	अगर (!device_may_wakeup(dev))
		वापस pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

/**
 * zynqmp_dma_resume - Resume from suspend
 * @dev:	Address of the device काष्ठाure
 *
 * Resume operation after suspend.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक __maybe_unused zynqmp_dma_resume(काष्ठा device *dev)
अणु
	अगर (!device_may_wakeup(dev))
		वापस pm_runसमय_क्रमce_resume(dev);

	वापस 0;
पूर्ण

/**
 * zynqmp_dma_runसमय_suspend - Runसमय suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 * Return: 0 always
 */
अटल पूर्णांक __maybe_unused zynqmp_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_dma_device *zdev = dev_get_drvdata(dev);

	clk_disable_unprepare(zdev->clk_मुख्य);
	clk_disable_unprepare(zdev->clk_apb);

	वापस 0;
पूर्ण

/**
 * zynqmp_dma_runसमय_resume - Runसमय suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 * Return: 0 always
 */
अटल पूर्णांक __maybe_unused zynqmp_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_dma_device *zdev = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(zdev->clk_मुख्य);
	अगर (err) अणु
		dev_err(dev, "Unable to enable main clock.\n");
		वापस err;
	पूर्ण

	err = clk_prepare_enable(zdev->clk_apb);
	अगर (err) अणु
		dev_err(dev, "Unable to enable apb clock.\n");
		clk_disable_unprepare(zdev->clk_मुख्य);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops zynqmp_dma_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(zynqmp_dma_suspend, zynqmp_dma_resume)
	SET_RUNTIME_PM_OPS(zynqmp_dma_runसमय_suspend,
			   zynqmp_dma_runसमय_resume, शून्य)
पूर्ण;

/**
 * zynqmp_dma_probe - Driver probe function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक zynqmp_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dma_device *zdev;
	काष्ठा dma_device *p;
	पूर्णांक ret;

	zdev = devm_kzalloc(&pdev->dev, माप(*zdev), GFP_KERNEL);
	अगर (!zdev)
		वापस -ENOMEM;

	zdev->dev = &pdev->dev;
	INIT_LIST_HEAD(&zdev->common.channels);

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(44));
	dma_cap_set(DMA_MEMCPY, zdev->common.cap_mask);

	p = &zdev->common;
	p->device_prep_dma_स_नकल = zynqmp_dma_prep_स_नकल;
	p->device_terminate_all = zynqmp_dma_device_terminate_all;
	p->device_issue_pending = zynqmp_dma_issue_pending;
	p->device_alloc_chan_resources = zynqmp_dma_alloc_chan_resources;
	p->device_मुक्त_chan_resources = zynqmp_dma_मुक्त_chan_resources;
	p->device_tx_status = dma_cookie_status;
	p->device_config = zynqmp_dma_device_config;
	p->dev = &pdev->dev;

	zdev->clk_मुख्य = devm_clk_get(&pdev->dev, "clk_main");
	अगर (IS_ERR(zdev->clk_मुख्य)) अणु
		dev_err(&pdev->dev, "main clock not found.\n");
		वापस PTR_ERR(zdev->clk_मुख्य);
	पूर्ण

	zdev->clk_apb = devm_clk_get(&pdev->dev, "clk_apb");
	अगर (IS_ERR(zdev->clk_apb)) अणु
		dev_err(&pdev->dev, "apb clock not found.\n");
		वापस PTR_ERR(zdev->clk_apb);
	पूर्ण

	platक्रमm_set_drvdata(pdev, zdev);
	pm_runसमय_set_स्वतःsuspend_delay(zdev->dev, ZDMA_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(zdev->dev);
	pm_runसमय_enable(zdev->dev);
	pm_runसमय_get_sync(zdev->dev);
	अगर (!pm_runसमय_enabled(zdev->dev)) अणु
		ret = zynqmp_dma_runसमय_resume(zdev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = zynqmp_dma_chan_probe(zdev, pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Probing channel failed\n");
		जाओ err_disable_pm;
	पूर्ण

	p->dst_addr_widths = BIT(zdev->chan->bus_width / 8);
	p->src_addr_widths = BIT(zdev->chan->bus_width / 8);

	dma_async_device_रेजिस्टर(&zdev->common);

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_zynqmp_dma_xlate, zdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to register DMA to DT\n");
		dma_async_device_unरेजिस्टर(&zdev->common);
		जाओ मुक्त_chan_resources;
	पूर्ण

	pm_runसमय_mark_last_busy(zdev->dev);
	pm_runसमय_put_sync_स्वतःsuspend(zdev->dev);

	dev_info(&pdev->dev, "ZynqMP DMA driver Probe success\n");

	वापस 0;

मुक्त_chan_resources:
	zynqmp_dma_chan_हटाओ(zdev->chan);
err_disable_pm:
	अगर (!pm_runसमय_enabled(zdev->dev))
		zynqmp_dma_runसमय_suspend(zdev->dev);
	pm_runसमय_disable(zdev->dev);
	वापस ret;
पूर्ण

/**
 * zynqmp_dma_हटाओ - Driver हटाओ function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: Always '0'
 */
अटल पूर्णांक zynqmp_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dma_device *zdev = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&zdev->common);

	zynqmp_dma_chan_हटाओ(zdev->chan);
	pm_runसमय_disable(zdev->dev);
	अगर (!pm_runसमय_enabled(zdev->dev))
		zynqmp_dma_runसमय_suspend(zdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_dma_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-dma-1.0", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_dma_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_dma_driver = अणु
	.driver = अणु
		.name = "xilinx-zynqmp-dma",
		.of_match_table = zynqmp_dma_of_match,
		.pm = &zynqmp_dma_dev_pm_ops,
	पूर्ण,
	.probe = zynqmp_dma_probe,
	.हटाओ = zynqmp_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(zynqmp_dma_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx ZynqMP DMA driver");
