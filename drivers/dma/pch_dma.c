<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Topclअगरf PCH DMA controller driver
 * Copyright (c) 2010 Intel Corporation
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pch_dma.h>

#समावेश "dmaengine.h"

#घोषणा DRV_NAME "pch-dma"

#घोषणा DMA_CTL0_DISABLE		0x0
#घोषणा DMA_CTL0_SG			0x1
#घोषणा DMA_CTL0_ONESHOT		0x2
#घोषणा DMA_CTL0_MODE_MASK_BITS		0x3
#घोषणा DMA_CTL0_सूची_SHIFT_BITS		2
#घोषणा DMA_CTL0_BITS_PER_CH		4

#घोषणा DMA_CTL2_START_SHIFT_BITS	8
#घोषणा DMA_CTL2_IRQ_ENABLE_MASK	((1UL << DMA_CTL2_START_SHIFT_BITS) - 1)

#घोषणा DMA_STATUS_IDLE			0x0
#घोषणा DMA_STATUS_DESC_READ		0x1
#घोषणा DMA_STATUS_WAIT			0x2
#घोषणा DMA_STATUS_ACCESS		0x3
#घोषणा DMA_STATUS_BITS_PER_CH		2
#घोषणा DMA_STATUS_MASK_BITS		0x3
#घोषणा DMA_STATUS_SHIFT_BITS		16
#घोषणा DMA_STATUS_IRQ(x)		(0x1 << (x))
#घोषणा DMA_STATUS0_ERR(x)		(0x1 << ((x) + 8))
#घोषणा DMA_STATUS2_ERR(x)		(0x1 << (x))

#घोषणा DMA_DESC_WIDTH_SHIFT_BITS	12
#घोषणा DMA_DESC_WIDTH_1_BYTE		(0x3 << DMA_DESC_WIDTH_SHIFT_BITS)
#घोषणा DMA_DESC_WIDTH_2_BYTES		(0x2 << DMA_DESC_WIDTH_SHIFT_BITS)
#घोषणा DMA_DESC_WIDTH_4_BYTES		(0x0 << DMA_DESC_WIDTH_SHIFT_BITS)
#घोषणा DMA_DESC_MAX_COUNT_1_BYTE	0x3FF
#घोषणा DMA_DESC_MAX_COUNT_2_BYTES	0x3FF
#घोषणा DMA_DESC_MAX_COUNT_4_BYTES	0x7FF
#घोषणा DMA_DESC_END_WITHOUT_IRQ	0x0
#घोषणा DMA_DESC_END_WITH_IRQ		0x1
#घोषणा DMA_DESC_FOLLOW_WITHOUT_IRQ	0x2
#घोषणा DMA_DESC_FOLLOW_WITH_IRQ	0x3

#घोषणा MAX_CHAN_NR			12

#घोषणा DMA_MASK_CTL0_MODE	0x33333333
#घोषणा DMA_MASK_CTL2_MODE	0x00003333

अटल अचिन्हित पूर्णांक init_nr_desc_per_channel = 64;
module_param(init_nr_desc_per_channel, uपूर्णांक, 0644);
MODULE_PARM_DESC(init_nr_desc_per_channel,
		 "initial descriptors per channel (default: 64)");

काष्ठा pch_dma_desc_regs अणु
	u32	dev_addr;
	u32	mem_addr;
	u32	size;
	u32	next;
पूर्ण;

काष्ठा pch_dma_regs अणु
	u32	dma_ctl0;
	u32	dma_ctl1;
	u32	dma_ctl2;
	u32	dma_ctl3;
	u32	dma_sts0;
	u32	dma_sts1;
	u32	dma_sts2;
	u32	reserved3;
	काष्ठा pch_dma_desc_regs desc[MAX_CHAN_NR];
पूर्ण;

काष्ठा pch_dma_desc अणु
	काष्ठा pch_dma_desc_regs regs;
	काष्ठा dma_async_tx_descriptor txd;
	काष्ठा list_head	desc_node;
	काष्ठा list_head	tx_list;
पूर्ण;

काष्ठा pch_dma_chan अणु
	काष्ठा dma_chan		chan;
	व्योम __iomem *membase;
	क्रमागत dma_transfer_direction dir;
	काष्ठा tasklet_काष्ठा	tasklet;
	अचिन्हित दीर्घ		err_status;

	spinlock_t		lock;

	काष्ठा list_head	active_list;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_list;
	अचिन्हित पूर्णांक		descs_allocated;
पूर्ण;

#घोषणा PDC_DEV_ADDR	0x00
#घोषणा PDC_MEM_ADDR	0x04
#घोषणा PDC_SIZE	0x08
#घोषणा PDC_NEXT	0x0C

#घोषणा channel_पढ़ोl(pdc, name) \
	पढ़ोl((pdc)->membase + PDC_##name)
#घोषणा channel_ग_लिखोl(pdc, name, val) \
	ग_लिखोl((val), (pdc)->membase + PDC_##name)

काष्ठा pch_dma अणु
	काष्ठा dma_device	dma;
	व्योम __iomem *membase;
	काष्ठा dma_pool		*pool;
	काष्ठा pch_dma_regs	regs;
	काष्ठा pch_dma_desc_regs ch_regs[MAX_CHAN_NR];
	काष्ठा pch_dma_chan	channels[MAX_CHAN_NR];
पूर्ण;

#घोषणा PCH_DMA_CTL0	0x00
#घोषणा PCH_DMA_CTL1	0x04
#घोषणा PCH_DMA_CTL2	0x08
#घोषणा PCH_DMA_CTL3	0x0C
#घोषणा PCH_DMA_STS0	0x10
#घोषणा PCH_DMA_STS1	0x14
#घोषणा PCH_DMA_STS2	0x18

#घोषणा dma_पढ़ोl(pd, name) \
	पढ़ोl((pd)->membase + PCH_DMA_##name)
#घोषणा dma_ग_लिखोl(pd, name, val) \
	ग_लिखोl((val), (pd)->membase + PCH_DMA_##name)

अटल अंतरभूत
काष्ठा pch_dma_desc *to_pd_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा pch_dma_desc, txd);
पूर्ण

अटल अंतरभूत काष्ठा pch_dma_chan *to_pd_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा pch_dma_chan, chan);
पूर्ण

अटल अंतरभूत काष्ठा pch_dma *to_pd(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा pch_dma, dma);
पूर्ण

अटल अंतरभूत काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा device *chan2parent(काष्ठा dma_chan *chan)
अणु
	वापस chan->dev->device.parent;
पूर्ण

अटल अंतरभूत
काष्ठा pch_dma_desc *pdc_first_active(काष्ठा pch_dma_chan *pd_chan)
अणु
	वापस list_first_entry(&pd_chan->active_list,
				काष्ठा pch_dma_desc, desc_node);
पूर्ण

अटल अंतरभूत
काष्ठा pch_dma_desc *pdc_first_queued(काष्ठा pch_dma_chan *pd_chan)
अणु
	वापस list_first_entry(&pd_chan->queue,
				काष्ठा pch_dma_desc, desc_node);
पूर्ण

अटल व्योम pdc_enable_irq(काष्ठा dma_chan *chan, पूर्णांक enable)
अणु
	काष्ठा pch_dma *pd = to_pd(chan->device);
	u32 val;
	पूर्णांक pos;

	अगर (chan->chan_id < 8)
		pos = chan->chan_id;
	अन्यथा
		pos = chan->chan_id + 8;

	val = dma_पढ़ोl(pd, CTL2);

	अगर (enable)
		val |= 0x1 << pos;
	अन्यथा
		val &= ~(0x1 << pos);

	dma_ग_लिखोl(pd, CTL2, val);

	dev_dbg(chan2dev(chan), "pdc_enable_irq: chan %d -> %x\n",
		chan->chan_id, val);
पूर्ण

अटल व्योम pdc_set_dir(काष्ठा dma_chan *chan)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);
	काष्ठा pch_dma *pd = to_pd(chan->device);
	u32 val;
	u32 mask_mode;
	u32 mask_ctl;

	अगर (chan->chan_id < 8) अणु
		val = dma_पढ़ोl(pd, CTL0);

		mask_mode = DMA_CTL0_MODE_MASK_BITS <<
					(DMA_CTL0_BITS_PER_CH * chan->chan_id);
		mask_ctl = DMA_MASK_CTL0_MODE & ~(DMA_CTL0_MODE_MASK_BITS <<
				       (DMA_CTL0_BITS_PER_CH * chan->chan_id));
		val &= mask_mode;
		अगर (pd_chan->dir == DMA_MEM_TO_DEV)
			val |= 0x1 << (DMA_CTL0_BITS_PER_CH * chan->chan_id +
				       DMA_CTL0_सूची_SHIFT_BITS);
		अन्यथा
			val &= ~(0x1 << (DMA_CTL0_BITS_PER_CH * chan->chan_id +
					 DMA_CTL0_सूची_SHIFT_BITS));

		val |= mask_ctl;
		dma_ग_लिखोl(pd, CTL0, val);
	पूर्ण अन्यथा अणु
		पूर्णांक ch = chan->chan_id - 8; /* ch8-->0 ch9-->1 ... ch11->3 */
		val = dma_पढ़ोl(pd, CTL3);

		mask_mode = DMA_CTL0_MODE_MASK_BITS <<
						(DMA_CTL0_BITS_PER_CH * ch);
		mask_ctl = DMA_MASK_CTL2_MODE & ~(DMA_CTL0_MODE_MASK_BITS <<
						 (DMA_CTL0_BITS_PER_CH * ch));
		val &= mask_mode;
		अगर (pd_chan->dir == DMA_MEM_TO_DEV)
			val |= 0x1 << (DMA_CTL0_BITS_PER_CH * ch +
				       DMA_CTL0_सूची_SHIFT_BITS);
		अन्यथा
			val &= ~(0x1 << (DMA_CTL0_BITS_PER_CH * ch +
					 DMA_CTL0_सूची_SHIFT_BITS));
		val |= mask_ctl;
		dma_ग_लिखोl(pd, CTL3, val);
	पूर्ण

	dev_dbg(chan2dev(chan), "pdc_set_dir: chan %d -> %x\n",
		chan->chan_id, val);
पूर्ण

अटल व्योम pdc_set_mode(काष्ठा dma_chan *chan, u32 mode)
अणु
	काष्ठा pch_dma *pd = to_pd(chan->device);
	u32 val;
	u32 mask_ctl;
	u32 mask_dir;

	अगर (chan->chan_id < 8) अणु
		mask_ctl = DMA_MASK_CTL0_MODE & ~(DMA_CTL0_MODE_MASK_BITS <<
			   (DMA_CTL0_BITS_PER_CH * chan->chan_id));
		mask_dir = 1 << (DMA_CTL0_BITS_PER_CH * chan->chan_id +\
				 DMA_CTL0_सूची_SHIFT_BITS);
		val = dma_पढ़ोl(pd, CTL0);
		val &= mask_dir;
		val |= mode << (DMA_CTL0_BITS_PER_CH * chan->chan_id);
		val |= mask_ctl;
		dma_ग_लिखोl(pd, CTL0, val);
	पूर्ण अन्यथा अणु
		पूर्णांक ch = chan->chan_id - 8; /* ch8-->0 ch9-->1 ... ch11->3 */
		mask_ctl = DMA_MASK_CTL2_MODE & ~(DMA_CTL0_MODE_MASK_BITS <<
						 (DMA_CTL0_BITS_PER_CH * ch));
		mask_dir = 1 << (DMA_CTL0_BITS_PER_CH * ch +\
				 DMA_CTL0_सूची_SHIFT_BITS);
		val = dma_पढ़ोl(pd, CTL3);
		val &= mask_dir;
		val |= mode << (DMA_CTL0_BITS_PER_CH * ch);
		val |= mask_ctl;
		dma_ग_लिखोl(pd, CTL3, val);
	पूर्ण

	dev_dbg(chan2dev(chan), "pdc_set_mode: chan %d -> %x\n",
		chan->chan_id, val);
पूर्ण

अटल u32 pdc_get_status0(काष्ठा pch_dma_chan *pd_chan)
अणु
	काष्ठा pch_dma *pd = to_pd(pd_chan->chan.device);
	u32 val;

	val = dma_पढ़ोl(pd, STS0);
	वापस DMA_STATUS_MASK_BITS & (val >> (DMA_STATUS_SHIFT_BITS +
			DMA_STATUS_BITS_PER_CH * pd_chan->chan.chan_id));
पूर्ण

अटल u32 pdc_get_status2(काष्ठा pch_dma_chan *pd_chan)
अणु
	काष्ठा pch_dma *pd = to_pd(pd_chan->chan.device);
	u32 val;

	val = dma_पढ़ोl(pd, STS2);
	वापस DMA_STATUS_MASK_BITS & (val >> (DMA_STATUS_SHIFT_BITS +
			DMA_STATUS_BITS_PER_CH * (pd_chan->chan.chan_id - 8)));
पूर्ण

अटल bool pdc_is_idle(काष्ठा pch_dma_chan *pd_chan)
अणु
	u32 sts;

	अगर (pd_chan->chan.chan_id < 8)
		sts = pdc_get_status0(pd_chan);
	अन्यथा
		sts = pdc_get_status2(pd_chan);


	अगर (sts == DMA_STATUS_IDLE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम pdc_करोstart(काष्ठा pch_dma_chan *pd_chan, काष्ठा pch_dma_desc* desc)
अणु
	अगर (!pdc_is_idle(pd_chan)) अणु
		dev_err(chan2dev(&pd_chan->chan),
			"BUG: Attempt to start non-idle channel\n");
		वापस;
	पूर्ण

	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> dev_addr: %x\n",
		pd_chan->chan.chan_id, desc->regs.dev_addr);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> mem_addr: %x\n",
		pd_chan->chan.chan_id, desc->regs.mem_addr);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> size: %x\n",
		pd_chan->chan.chan_id, desc->regs.size);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> next: %x\n",
		pd_chan->chan.chan_id, desc->regs.next);

	अगर (list_empty(&desc->tx_list)) अणु
		channel_ग_लिखोl(pd_chan, DEV_ADDR, desc->regs.dev_addr);
		channel_ग_लिखोl(pd_chan, MEM_ADDR, desc->regs.mem_addr);
		channel_ग_लिखोl(pd_chan, SIZE, desc->regs.size);
		channel_ग_लिखोl(pd_chan, NEXT, desc->regs.next);
		pdc_set_mode(&pd_chan->chan, DMA_CTL0_ONESHOT);
	पूर्ण अन्यथा अणु
		channel_ग_लिखोl(pd_chan, NEXT, desc->txd.phys);
		pdc_set_mode(&pd_chan->chan, DMA_CTL0_SG);
	पूर्ण
पूर्ण

अटल व्योम pdc_chain_complete(काष्ठा pch_dma_chan *pd_chan,
			       काष्ठा pch_dma_desc *desc)
अणु
	काष्ठा dma_async_tx_descriptor *txd = &desc->txd;
	काष्ठा dmaengine_desc_callback cb;

	dmaengine_desc_get_callback(txd, &cb);
	list_splice_init(&desc->tx_list, &pd_chan->मुक्त_list);
	list_move(&desc->desc_node, &pd_chan->मुक्त_list);

	dmaengine_desc_callback_invoke(&cb, शून्य);
पूर्ण

अटल व्योम pdc_complete_all(काष्ठा pch_dma_chan *pd_chan)
अणु
	काष्ठा pch_dma_desc *desc, *_d;
	LIST_HEAD(list);

	BUG_ON(!pdc_is_idle(pd_chan));

	अगर (!list_empty(&pd_chan->queue))
		pdc_करोstart(pd_chan, pdc_first_queued(pd_chan));

	list_splice_init(&pd_chan->active_list, &list);
	list_splice_init(&pd_chan->queue, &pd_chan->active_list);

	list_क्रम_each_entry_safe(desc, _d, &list, desc_node)
		pdc_chain_complete(pd_chan, desc);
पूर्ण

अटल व्योम pdc_handle_error(काष्ठा pch_dma_chan *pd_chan)
अणु
	काष्ठा pch_dma_desc *bad_desc;

	bad_desc = pdc_first_active(pd_chan);
	list_del(&bad_desc->desc_node);

	list_splice_init(&pd_chan->queue, pd_chan->active_list.prev);

	अगर (!list_empty(&pd_chan->active_list))
		pdc_करोstart(pd_chan, pdc_first_active(pd_chan));

	dev_crit(chan2dev(&pd_chan->chan), "Bad descriptor submitted\n");
	dev_crit(chan2dev(&pd_chan->chan), "descriptor cookie: %d\n",
		 bad_desc->txd.cookie);

	pdc_chain_complete(pd_chan, bad_desc);
पूर्ण

अटल व्योम pdc_advance_work(काष्ठा pch_dma_chan *pd_chan)
अणु
	अगर (list_empty(&pd_chan->active_list) ||
		list_is_singular(&pd_chan->active_list)) अणु
		pdc_complete_all(pd_chan);
	पूर्ण अन्यथा अणु
		pdc_chain_complete(pd_chan, pdc_first_active(pd_chan));
		pdc_करोstart(pd_chan, pdc_first_active(pd_chan));
	पूर्ण
पूर्ण

अटल dma_cookie_t pd_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा pch_dma_desc *desc = to_pd_desc(txd);
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(txd->chan);

	spin_lock(&pd_chan->lock);

	अगर (list_empty(&pd_chan->active_list)) अणु
		list_add_tail(&desc->desc_node, &pd_chan->active_list);
		pdc_करोstart(pd_chan, desc);
	पूर्ण अन्यथा अणु
		list_add_tail(&desc->desc_node, &pd_chan->queue);
	पूर्ण

	spin_unlock(&pd_chan->lock);
	वापस 0;
पूर्ण

अटल काष्ठा pch_dma_desc *pdc_alloc_desc(काष्ठा dma_chan *chan, gfp_t flags)
अणु
	काष्ठा pch_dma_desc *desc = शून्य;
	काष्ठा pch_dma *pd = to_pd(chan->device);
	dma_addr_t addr;

	desc = dma_pool_zalloc(pd->pool, flags, &addr);
	अगर (desc) अणु
		INIT_LIST_HEAD(&desc->tx_list);
		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.tx_submit = pd_tx_submit;
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.phys = addr;
	पूर्ण

	वापस desc;
पूर्ण

अटल काष्ठा pch_dma_desc *pdc_desc_get(काष्ठा pch_dma_chan *pd_chan)
अणु
	काष्ठा pch_dma_desc *desc, *_d;
	काष्ठा pch_dma_desc *ret = शून्य;
	पूर्णांक i = 0;

	spin_lock(&pd_chan->lock);
	list_क्रम_each_entry_safe(desc, _d, &pd_chan->मुक्त_list, desc_node) अणु
		i++;
		अगर (async_tx_test_ack(&desc->txd)) अणु
			list_del(&desc->desc_node);
			ret = desc;
			अवरोध;
		पूर्ण
		dev_dbg(chan2dev(&pd_chan->chan), "desc %p not ACKed\n", desc);
	पूर्ण
	spin_unlock(&pd_chan->lock);
	dev_dbg(chan2dev(&pd_chan->chan), "scanned %d descriptors\n", i);

	अगर (!ret) अणु
		ret = pdc_alloc_desc(&pd_chan->chan, GFP_ATOMIC);
		अगर (ret) अणु
			spin_lock(&pd_chan->lock);
			pd_chan->descs_allocated++;
			spin_unlock(&pd_chan->lock);
		पूर्ण अन्यथा अणु
			dev_err(chan2dev(&pd_chan->chan),
				"failed to alloc desc\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pdc_desc_put(काष्ठा pch_dma_chan *pd_chan,
			 काष्ठा pch_dma_desc *desc)
अणु
	अगर (desc) अणु
		spin_lock(&pd_chan->lock);
		list_splice_init(&desc->tx_list, &pd_chan->मुक्त_list);
		list_add(&desc->desc_node, &pd_chan->मुक्त_list);
		spin_unlock(&pd_chan->lock);
	पूर्ण
पूर्ण

अटल पूर्णांक pd_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);
	काष्ठा pch_dma_desc *desc;
	LIST_HEAD(पंचांगp_list);
	पूर्णांक i;

	अगर (!pdc_is_idle(pd_chan)) अणु
		dev_dbg(chan2dev(chan), "DMA channel not idle ?\n");
		वापस -EIO;
	पूर्ण

	अगर (!list_empty(&pd_chan->मुक्त_list))
		वापस pd_chan->descs_allocated;

	क्रम (i = 0; i < init_nr_desc_per_channel; i++) अणु
		desc = pdc_alloc_desc(chan, GFP_KERNEL);

		अगर (!desc) अणु
			dev_warn(chan2dev(chan),
				"Only allocated %d initial descriptors\n", i);
			अवरोध;
		पूर्ण

		list_add_tail(&desc->desc_node, &पंचांगp_list);
	पूर्ण

	spin_lock_irq(&pd_chan->lock);
	list_splice(&पंचांगp_list, &pd_chan->मुक्त_list);
	pd_chan->descs_allocated = i;
	dma_cookie_init(chan);
	spin_unlock_irq(&pd_chan->lock);

	pdc_enable_irq(chan, 1);

	वापस pd_chan->descs_allocated;
पूर्ण

अटल व्योम pd_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);
	काष्ठा pch_dma *pd = to_pd(chan->device);
	काष्ठा pch_dma_desc *desc, *_d;
	LIST_HEAD(पंचांगp_list);

	BUG_ON(!pdc_is_idle(pd_chan));
	BUG_ON(!list_empty(&pd_chan->active_list));
	BUG_ON(!list_empty(&pd_chan->queue));

	spin_lock_irq(&pd_chan->lock);
	list_splice_init(&pd_chan->मुक्त_list, &पंचांगp_list);
	pd_chan->descs_allocated = 0;
	spin_unlock_irq(&pd_chan->lock);

	list_क्रम_each_entry_safe(desc, _d, &पंचांगp_list, desc_node)
		dma_pool_मुक्त(pd->pool, desc, desc->txd.phys);

	pdc_enable_irq(chan, 0);
पूर्ण

अटल क्रमागत dma_status pd_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
				    काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल व्योम pd_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);

	अगर (pdc_is_idle(pd_chan)) अणु
		spin_lock(&pd_chan->lock);
		pdc_advance_work(pd_chan);
		spin_unlock(&pd_chan->lock);
	पूर्ण
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *pd_prep_slave_sg(काष्ठा dma_chan *chan,
			काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
			क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags,
			व्योम *context)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);
	काष्ठा pch_dma_slave *pd_slave = chan->निजी;
	काष्ठा pch_dma_desc *first = शून्य;
	काष्ठा pch_dma_desc *prev = शून्य;
	काष्ठा pch_dma_desc *desc = शून्य;
	काष्ठा scatterlist *sg;
	dma_addr_t reg;
	पूर्णांक i;

	अगर (unlikely(!sg_len)) अणु
		dev_info(chan2dev(chan), "prep_slave_sg: length is zero!\n");
		वापस शून्य;
	पूर्ण

	अगर (direction == DMA_DEV_TO_MEM)
		reg = pd_slave->rx_reg;
	अन्यथा अगर (direction == DMA_MEM_TO_DEV)
		reg = pd_slave->tx_reg;
	अन्यथा
		वापस शून्य;

	pd_chan->dir = direction;
	pdc_set_dir(chan);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		desc = pdc_desc_get(pd_chan);

		अगर (!desc)
			जाओ err_desc_get;

		desc->regs.dev_addr = reg;
		desc->regs.mem_addr = sg_dma_address(sg);
		desc->regs.size = sg_dma_len(sg);
		desc->regs.next = DMA_DESC_FOLLOW_WITHOUT_IRQ;

		चयन (pd_slave->width) अणु
		हाल PCH_DMA_WIDTH_1_BYTE:
			अगर (desc->regs.size > DMA_DESC_MAX_COUNT_1_BYTE)
				जाओ err_desc_get;
			desc->regs.size |= DMA_DESC_WIDTH_1_BYTE;
			अवरोध;
		हाल PCH_DMA_WIDTH_2_BYTES:
			अगर (desc->regs.size > DMA_DESC_MAX_COUNT_2_BYTES)
				जाओ err_desc_get;
			desc->regs.size |= DMA_DESC_WIDTH_2_BYTES;
			अवरोध;
		हाल PCH_DMA_WIDTH_4_BYTES:
			अगर (desc->regs.size > DMA_DESC_MAX_COUNT_4_BYTES)
				जाओ err_desc_get;
			desc->regs.size |= DMA_DESC_WIDTH_4_BYTES;
			अवरोध;
		शेष:
			जाओ err_desc_get;
		पूर्ण

		अगर (!first) अणु
			first = desc;
		पूर्ण अन्यथा अणु
			prev->regs.next |= desc->txd.phys;
			list_add_tail(&desc->desc_node, &first->tx_list);
		पूर्ण

		prev = desc;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT)
		desc->regs.next = DMA_DESC_END_WITH_IRQ;
	अन्यथा
		desc->regs.next = DMA_DESC_END_WITHOUT_IRQ;

	first->txd.cookie = -EBUSY;
	desc->txd.flags = flags;

	वापस &first->txd;

err_desc_get:
	dev_err(chan2dev(chan), "failed to get desc or wrong parameters\n");
	pdc_desc_put(pd_chan, first);
	वापस शून्य;
पूर्ण

अटल पूर्णांक pd_device_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा pch_dma_chan *pd_chan = to_pd_chan(chan);
	काष्ठा pch_dma_desc *desc, *_d;
	LIST_HEAD(list);

	spin_lock_irq(&pd_chan->lock);

	pdc_set_mode(&pd_chan->chan, DMA_CTL0_DISABLE);

	list_splice_init(&pd_chan->active_list, &list);
	list_splice_init(&pd_chan->queue, &list);

	list_क्रम_each_entry_safe(desc, _d, &list, desc_node)
		pdc_chain_complete(pd_chan, desc);

	spin_unlock_irq(&pd_chan->lock);

	वापस 0;
पूर्ण

अटल व्योम pdc_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा pch_dma_chan *pd_chan = from_tasklet(pd_chan, t, tasklet);
	अचिन्हित दीर्घ flags;

	अगर (!pdc_is_idle(pd_chan)) अणु
		dev_err(chan2dev(&pd_chan->chan),
			"BUG: handle non-idle channel in tasklet\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&pd_chan->lock, flags);
	अगर (test_and_clear_bit(0, &pd_chan->err_status))
		pdc_handle_error(pd_chan);
	अन्यथा
		pdc_advance_work(pd_chan);
	spin_unlock_irqrestore(&pd_chan->lock, flags);
पूर्ण

अटल irqवापस_t pd_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा pch_dma *pd = (काष्ठा pch_dma *)devid;
	काष्ठा pch_dma_chan *pd_chan;
	u32 sts0;
	u32 sts2;
	पूर्णांक i;
	पूर्णांक ret0 = IRQ_NONE;
	पूर्णांक ret2 = IRQ_NONE;

	sts0 = dma_पढ़ोl(pd, STS0);
	sts2 = dma_पढ़ोl(pd, STS2);

	dev_dbg(pd->dma.dev, "pd_irq sts0: %x\n", sts0);

	क्रम (i = 0; i < pd->dma.chancnt; i++) अणु
		pd_chan = &pd->channels[i];

		अगर (i < 8) अणु
			अगर (sts0 & DMA_STATUS_IRQ(i)) अणु
				अगर (sts0 & DMA_STATUS0_ERR(i))
					set_bit(0, &pd_chan->err_status);

				tasklet_schedule(&pd_chan->tasklet);
				ret0 = IRQ_HANDLED;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sts2 & DMA_STATUS_IRQ(i - 8)) अणु
				अगर (sts2 & DMA_STATUS2_ERR(i))
					set_bit(0, &pd_chan->err_status);

				tasklet_schedule(&pd_chan->tasklet);
				ret2 = IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	/* clear पूर्णांकerrupt bits in status रेजिस्टर */
	अगर (ret0)
		dma_ग_लिखोl(pd, STS0, sts0);
	अगर (ret2)
		dma_ग_लिखोl(pd, STS2, sts2);

	वापस ret0 | ret2;
पूर्ण

अटल व्योम __maybe_unused pch_dma_save_regs(काष्ठा pch_dma *pd)
अणु
	काष्ठा pch_dma_chan *pd_chan;
	काष्ठा dma_chan *chan, *_c;
	पूर्णांक i = 0;

	pd->regs.dma_ctl0 = dma_पढ़ोl(pd, CTL0);
	pd->regs.dma_ctl1 = dma_पढ़ोl(pd, CTL1);
	pd->regs.dma_ctl2 = dma_पढ़ोl(pd, CTL2);
	pd->regs.dma_ctl3 = dma_पढ़ोl(pd, CTL3);

	list_क्रम_each_entry_safe(chan, _c, &pd->dma.channels, device_node) अणु
		pd_chan = to_pd_chan(chan);

		pd->ch_regs[i].dev_addr = channel_पढ़ोl(pd_chan, DEV_ADDR);
		pd->ch_regs[i].mem_addr = channel_पढ़ोl(pd_chan, MEM_ADDR);
		pd->ch_regs[i].size = channel_पढ़ोl(pd_chan, SIZE);
		pd->ch_regs[i].next = channel_पढ़ोl(pd_chan, NEXT);

		i++;
	पूर्ण
पूर्ण

अटल व्योम __maybe_unused pch_dma_restore_regs(काष्ठा pch_dma *pd)
अणु
	काष्ठा pch_dma_chan *pd_chan;
	काष्ठा dma_chan *chan, *_c;
	पूर्णांक i = 0;

	dma_ग_लिखोl(pd, CTL0, pd->regs.dma_ctl0);
	dma_ग_लिखोl(pd, CTL1, pd->regs.dma_ctl1);
	dma_ग_लिखोl(pd, CTL2, pd->regs.dma_ctl2);
	dma_ग_लिखोl(pd, CTL3, pd->regs.dma_ctl3);

	list_क्रम_each_entry_safe(chan, _c, &pd->dma.channels, device_node) अणु
		pd_chan = to_pd_chan(chan);

		channel_ग_लिखोl(pd_chan, DEV_ADDR, pd->ch_regs[i].dev_addr);
		channel_ग_लिखोl(pd_chan, MEM_ADDR, pd->ch_regs[i].mem_addr);
		channel_ग_लिखोl(pd_chan, SIZE, pd->ch_regs[i].size);
		channel_ग_लिखोl(pd_chan, NEXT, pd->ch_regs[i].next);

		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused pch_dma_suspend(काष्ठा device *dev)
अणु
	काष्ठा pch_dma *pd = dev_get_drvdata(dev);

	अगर (pd)
		pch_dma_save_regs(pd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_dma_resume(काष्ठा device *dev)
अणु
	काष्ठा pch_dma *pd = dev_get_drvdata(dev);

	अगर (pd)
		pch_dma_restore_regs(pd);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_dma_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pch_dma *pd;
	काष्ठा pch_dma_regs *regs;
	अचिन्हित पूर्णांक nr_channels;
	पूर्णांक err;
	पूर्णांक i;

	nr_channels = id->driver_data;
	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, pd);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 1) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Cannot find proper base address\n");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources\n");
		जाओ err_disable_pdev;
	पूर्ण

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot set proper DMA config\n");
		जाओ err_मुक्त_res;
	पूर्ण

	regs = pd->membase = pci_iomap(pdev, 1, 0);
	अगर (!pd->membase) अणु
		dev_err(&pdev->dev, "Cannot map MMIO registers\n");
		err = -ENOMEM;
		जाओ err_मुक्त_res;
	पूर्ण

	pci_set_master(pdev);
	pd->dma.dev = &pdev->dev;

	err = request_irq(pdev->irq, pd_irq, IRQF_SHARED, DRV_NAME, pd);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		जाओ err_iounmap;
	पूर्ण

	pd->pool = dma_pool_create("pch_dma_desc_pool", &pdev->dev,
				   माप(काष्ठा pch_dma_desc), 4, 0);
	अगर (!pd->pool) अणु
		dev_err(&pdev->dev, "Failed to alloc DMA descriptors\n");
		err = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण


	INIT_LIST_HEAD(&pd->dma.channels);

	क्रम (i = 0; i < nr_channels; i++) अणु
		काष्ठा pch_dma_chan *pd_chan = &pd->channels[i];

		pd_chan->chan.device = &pd->dma;
		dma_cookie_init(&pd_chan->chan);

		pd_chan->membase = &regs->desc[i];

		spin_lock_init(&pd_chan->lock);

		INIT_LIST_HEAD(&pd_chan->active_list);
		INIT_LIST_HEAD(&pd_chan->queue);
		INIT_LIST_HEAD(&pd_chan->मुक्त_list);

		tasklet_setup(&pd_chan->tasklet, pdc_tasklet);
		list_add_tail(&pd_chan->chan.device_node, &pd->dma.channels);
	पूर्ण

	dma_cap_zero(pd->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, pd->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, pd->dma.cap_mask);

	pd->dma.device_alloc_chan_resources = pd_alloc_chan_resources;
	pd->dma.device_मुक्त_chan_resources = pd_मुक्त_chan_resources;
	pd->dma.device_tx_status = pd_tx_status;
	pd->dma.device_issue_pending = pd_issue_pending;
	pd->dma.device_prep_slave_sg = pd_prep_slave_sg;
	pd->dma.device_terminate_all = pd_device_terminate_all;

	err = dma_async_device_रेजिस्टर(&pd->dma);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register DMA device\n");
		जाओ err_मुक्त_pool;
	पूर्ण

	वापस 0;

err_मुक्त_pool:
	dma_pool_destroy(pd->pool);
err_मुक्त_irq:
	मुक्त_irq(pdev->irq, pd);
err_iounmap:
	pci_iounmap(pdev, pd->membase);
err_मुक्त_res:
	pci_release_regions(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
err_मुक्त_mem:
	kमुक्त(pd);
	वापस err;
पूर्ण

अटल व्योम pch_dma_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dma *pd = pci_get_drvdata(pdev);
	काष्ठा pch_dma_chan *pd_chan;
	काष्ठा dma_chan *chan, *_c;

	अगर (pd) अणु
		dma_async_device_unरेजिस्टर(&pd->dma);

		मुक्त_irq(pdev->irq, pd);

		list_क्रम_each_entry_safe(chan, _c, &pd->dma.channels,
					 device_node) अणु
			pd_chan = to_pd_chan(chan);

			tasklet_समाप्त(&pd_chan->tasklet);
		पूर्ण

		dma_pool_destroy(pd->pool);
		pci_iounmap(pdev, pd->membase);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		kमुक्त(pd);
	पूर्ण
पूर्ण

/* PCI Device ID of DMA device */
#घोषणा PCI_DEVICE_ID_EG20T_PCH_DMA_8CH        0x8810
#घोषणा PCI_DEVICE_ID_EG20T_PCH_DMA_4CH        0x8815
#घोषणा PCI_DEVICE_ID_ML7213_DMA1_8CH	0x8026
#घोषणा PCI_DEVICE_ID_ML7213_DMA2_8CH	0x802B
#घोषणा PCI_DEVICE_ID_ML7213_DMA3_4CH	0x8034
#घोषणा PCI_DEVICE_ID_ML7213_DMA4_12CH	0x8032
#घोषणा PCI_DEVICE_ID_ML7223_DMA1_4CH	0x800B
#घोषणा PCI_DEVICE_ID_ML7223_DMA2_4CH	0x800E
#घोषणा PCI_DEVICE_ID_ML7223_DMA3_4CH	0x8017
#घोषणा PCI_DEVICE_ID_ML7223_DMA4_4CH	0x803B
#घोषणा PCI_DEVICE_ID_ML7831_DMA1_8CH	0x8810
#घोषणा PCI_DEVICE_ID_ML7831_DMA2_4CH	0x8815

अटल स्थिर काष्ठा pci_device_id pch_dma_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_EG20T_PCH_DMA_8CH), 8 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_EG20T_PCH_DMA_4CH), 4 पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_DMA1_8CH), 8पूर्ण, /* UART Video */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_DMA2_8CH), 8पूर्ण, /* PCMIF SPI */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_DMA3_4CH), 4पूर्ण, /* FPGA */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_DMA4_12CH), 12पूर्ण, /* I2S */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_DMA1_4CH), 4पूर्ण, /* UART */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_DMA2_4CH), 4पूर्ण, /* Video SPI */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_DMA3_4CH), 4पूर्ण, /* Security */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_DMA4_4CH), 4पूर्ण, /* FPGA */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7831_DMA1_8CH), 8पूर्ण, /* UART */
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7831_DMA2_4CH), 4पूर्ण, /* SPI */
	अणु 0, पूर्ण,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(pch_dma_pm_ops, pch_dma_suspend, pch_dma_resume);

अटल काष्ठा pci_driver pch_dma_driver = अणु
	.name		= DRV_NAME,
	.id_table	= pch_dma_id_table,
	.probe		= pch_dma_probe,
	.हटाओ		= pch_dma_हटाओ,
	.driver.pm	= &pch_dma_pm_ops,
पूर्ण;

module_pci_driver(pch_dma_driver);

MODULE_DESCRIPTION("Intel EG20T PCH / LAPIS Semicon ML7213/ML7223/ML7831 IOH "
		   "DMA controller driver");
MODULE_AUTHOR("Yong Wang <yong.y.wang@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, pch_dma_id_table);
