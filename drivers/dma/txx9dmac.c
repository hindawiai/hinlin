<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the TXx9 SoC DMA Controller
 *
 * Copyright (C) 2009 Atsushi Nemoto
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>

#समावेश "dmaengine.h"
#समावेश "txx9dmac.h"

अटल काष्ठा txx9dmac_chan *to_txx9dmac_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा txx9dmac_chan, chan);
पूर्ण

अटल काष्ठा txx9dmac_cregs __iomem *__dma_regs(स्थिर काष्ठा txx9dmac_chan *dc)
अणु
	वापस dc->ch_regs;
पूर्ण

अटल काष्ठा txx9dmac_cregs32 __iomem *__dma_regs32(
	स्थिर काष्ठा txx9dmac_chan *dc)
अणु
	वापस dc->ch_regs;
पूर्ण

#घोषणा channel64_पढ़ोq(dc, name) \
	__raw_पढ़ोq(&(__dma_regs(dc)->name))
#घोषणा channel64_ग_लिखोq(dc, name, val) \
	__raw_ग_लिखोq((val), &(__dma_regs(dc)->name))
#घोषणा channel64_पढ़ोl(dc, name) \
	__raw_पढ़ोl(&(__dma_regs(dc)->name))
#घोषणा channel64_ग_लिखोl(dc, name, val) \
	__raw_ग_लिखोl((val), &(__dma_regs(dc)->name))

#घोषणा channel32_पढ़ोl(dc, name) \
	__raw_पढ़ोl(&(__dma_regs32(dc)->name))
#घोषणा channel32_ग_लिखोl(dc, name, val) \
	__raw_ग_लिखोl((val), &(__dma_regs32(dc)->name))

#घोषणा channel_पढ़ोq(dc, name) channel64_पढ़ोq(dc, name)
#घोषणा channel_ग_लिखोq(dc, name, val) channel64_ग_लिखोq(dc, name, val)
#घोषणा channel_पढ़ोl(dc, name) \
	(is_dmac64(dc) ? \
	 channel64_पढ़ोl(dc, name) : channel32_पढ़ोl(dc, name))
#घोषणा channel_ग_लिखोl(dc, name, val) \
	(is_dmac64(dc) ? \
	 channel64_ग_लिखोl(dc, name, val) : channel32_ग_लिखोl(dc, name, val))

अटल dma_addr_t channel64_पढ़ो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc)
अणु
	अगर (माप(__dma_regs(dc)->CHAR) == माप(u64))
		वापस channel64_पढ़ोq(dc, CHAR);
	अन्यथा
		वापस channel64_पढ़ोl(dc, CHAR);
पूर्ण

अटल व्योम channel64_ग_लिखो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc, dma_addr_t val)
अणु
	अगर (माप(__dma_regs(dc)->CHAR) == माप(u64))
		channel64_ग_लिखोq(dc, CHAR, val);
	अन्यथा
		channel64_ग_लिखोl(dc, CHAR, val);
पूर्ण

अटल व्योम channel64_clear_CHAR(स्थिर काष्ठा txx9dmac_chan *dc)
अणु
#अगर defined(CONFIG_32BIT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
	channel64_ग_लिखोl(dc, CHAR, 0);
	channel64_ग_लिखोl(dc, __pad_CHAR, 0);
#अन्यथा
	channel64_ग_लिखोq(dc, CHAR, 0);
#पूर्ण_अगर
पूर्ण

अटल dma_addr_t channel_पढ़ो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc)
अणु
	अगर (is_dmac64(dc))
		वापस channel64_पढ़ो_CHAR(dc);
	अन्यथा
		वापस channel32_पढ़ोl(dc, CHAR);
पूर्ण

अटल व्योम channel_ग_लिखो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc, dma_addr_t val)
अणु
	अगर (is_dmac64(dc))
		channel64_ग_लिखो_CHAR(dc, val);
	अन्यथा
		channel32_ग_लिखोl(dc, CHAR, val);
पूर्ण

अटल काष्ठा txx9dmac_regs __iomem *__txx9dmac_regs(
	स्थिर काष्ठा txx9dmac_dev *ddev)
अणु
	वापस ddev->regs;
पूर्ण

अटल काष्ठा txx9dmac_regs32 __iomem *__txx9dmac_regs32(
	स्थिर काष्ठा txx9dmac_dev *ddev)
अणु
	वापस ddev->regs;
पूर्ण

#घोषणा dma64_पढ़ोl(ddev, name) \
	__raw_पढ़ोl(&(__txx9dmac_regs(ddev)->name))
#घोषणा dma64_ग_लिखोl(ddev, name, val) \
	__raw_ग_लिखोl((val), &(__txx9dmac_regs(ddev)->name))

#घोषणा dma32_पढ़ोl(ddev, name) \
	__raw_पढ़ोl(&(__txx9dmac_regs32(ddev)->name))
#घोषणा dma32_ग_लिखोl(ddev, name, val) \
	__raw_ग_लिखोl((val), &(__txx9dmac_regs32(ddev)->name))

#घोषणा dma_पढ़ोl(ddev, name) \
	(__is_dmac64(ddev) ? \
	dma64_पढ़ोl(ddev, name) : dma32_पढ़ोl(ddev, name))
#घोषणा dma_ग_लिखोl(ddev, name, val) \
	(__is_dmac64(ddev) ? \
	dma64_ग_लिखोl(ddev, name, val) : dma32_ग_लिखोl(ddev, name, val))

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण
अटल काष्ठा device *chan2parent(काष्ठा dma_chan *chan)
अणु
	वापस chan->dev->device.parent;
पूर्ण

अटल काष्ठा txx9dmac_desc *
txd_to_txx9dmac_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा txx9dmac_desc, txd);
पूर्ण

अटल dma_addr_t desc_पढ़ो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc,
				 स्थिर काष्ठा txx9dmac_desc *desc)
अणु
	वापस is_dmac64(dc) ? desc->hwdesc.CHAR : desc->hwdesc32.CHAR;
पूर्ण

अटल व्योम desc_ग_लिखो_CHAR(स्थिर काष्ठा txx9dmac_chan *dc,
			    काष्ठा txx9dmac_desc *desc, dma_addr_t val)
अणु
	अगर (is_dmac64(dc))
		desc->hwdesc.CHAR = val;
	अन्यथा
		desc->hwdesc32.CHAR = val;
पूर्ण

#घोषणा TXX9_DMA_MAX_COUNT	0x04000000

#घोषणा TXX9_DMA_INITIAL_DESC_COUNT	64

अटल काष्ठा txx9dmac_desc *txx9dmac_first_active(काष्ठा txx9dmac_chan *dc)
अणु
	वापस list_entry(dc->active_list.next,
			  काष्ठा txx9dmac_desc, desc_node);
पूर्ण

अटल काष्ठा txx9dmac_desc *txx9dmac_last_active(काष्ठा txx9dmac_chan *dc)
अणु
	वापस list_entry(dc->active_list.prev,
			  काष्ठा txx9dmac_desc, desc_node);
पूर्ण

अटल काष्ठा txx9dmac_desc *txx9dmac_first_queued(काष्ठा txx9dmac_chan *dc)
अणु
	वापस list_entry(dc->queue.next, काष्ठा txx9dmac_desc, desc_node);
पूर्ण

अटल काष्ठा txx9dmac_desc *txx9dmac_last_child(काष्ठा txx9dmac_desc *desc)
अणु
	अगर (!list_empty(&desc->tx_list))
		desc = list_entry(desc->tx_list.prev, typeof(*desc), desc_node);
	वापस desc;
पूर्ण

अटल dma_cookie_t txx9dmac_tx_submit(काष्ठा dma_async_tx_descriptor *tx);

अटल काष्ठा txx9dmac_desc *txx9dmac_desc_alloc(काष्ठा txx9dmac_chan *dc,
						 gfp_t flags)
अणु
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *desc;

	desc = kzalloc(माप(*desc), flags);
	अगर (!desc)
		वापस शून्य;
	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->txd, &dc->chan);
	desc->txd.tx_submit = txx9dmac_tx_submit;
	/* txd.flags will be overwritten in prep funcs */
	desc->txd.flags = DMA_CTRL_ACK;
	desc->txd.phys = dma_map_single(chan2parent(&dc->chan), &desc->hwdesc,
					ddev->descsize, DMA_TO_DEVICE);
	वापस desc;
पूर्ण

अटल काष्ठा txx9dmac_desc *txx9dmac_desc_get(काष्ठा txx9dmac_chan *dc)
अणु
	काष्ठा txx9dmac_desc *desc, *_desc;
	काष्ठा txx9dmac_desc *ret = शून्य;
	अचिन्हित पूर्णांक i = 0;

	spin_lock_bh(&dc->lock);
	list_क्रम_each_entry_safe(desc, _desc, &dc->मुक्त_list, desc_node) अणु
		अगर (async_tx_test_ack(&desc->txd)) अणु
			list_del(&desc->desc_node);
			ret = desc;
			अवरोध;
		पूर्ण
		dev_dbg(chan2dev(&dc->chan), "desc %p not ACKed\n", desc);
		i++;
	पूर्ण
	spin_unlock_bh(&dc->lock);

	dev_vdbg(chan2dev(&dc->chan), "scanned %u descriptors on freelist\n",
		 i);
	अगर (!ret) अणु
		ret = txx9dmac_desc_alloc(dc, GFP_ATOMIC);
		अगर (ret) अणु
			spin_lock_bh(&dc->lock);
			dc->descs_allocated++;
			spin_unlock_bh(&dc->lock);
		पूर्ण अन्यथा
			dev_err(chan2dev(&dc->chan),
				"not enough descriptors available\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम txx9dmac_sync_desc_क्रम_cpu(काष्ठा txx9dmac_chan *dc,
				       काष्ठा txx9dmac_desc *desc)
अणु
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *child;

	list_क्रम_each_entry(child, &desc->tx_list, desc_node)
		dma_sync_single_क्रम_cpu(chan2parent(&dc->chan),
				child->txd.phys, ddev->descsize,
				DMA_TO_DEVICE);
	dma_sync_single_क्रम_cpu(chan2parent(&dc->chan),
			desc->txd.phys, ddev->descsize,
			DMA_TO_DEVICE);
पूर्ण

/*
 * Move a descriptor, including any children, to the मुक्त list.
 * `desc' must not be on any lists.
 */
अटल व्योम txx9dmac_desc_put(काष्ठा txx9dmac_chan *dc,
			      काष्ठा txx9dmac_desc *desc)
अणु
	अगर (desc) अणु
		काष्ठा txx9dmac_desc *child;

		txx9dmac_sync_desc_क्रम_cpu(dc, desc);

		spin_lock_bh(&dc->lock);
		list_क्रम_each_entry(child, &desc->tx_list, desc_node)
			dev_vdbg(chan2dev(&dc->chan),
				 "moving child desc %p to freelist\n",
				 child);
		list_splice_init(&desc->tx_list, &dc->मुक्त_list);
		dev_vdbg(chan2dev(&dc->chan), "moving desc %p to freelist\n",
			 desc);
		list_add(&desc->desc_node, &dc->मुक्त_list);
		spin_unlock_bh(&dc->lock);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम txx9dmac_dump_regs(काष्ठा txx9dmac_chan *dc)
अणु
	अगर (is_dmac64(dc))
		dev_err(chan2dev(&dc->chan),
			"  CHAR: %#llx SAR: %#llx DAR: %#llx CNTR: %#x"
			" SAIR: %#x DAIR: %#x CCR: %#x CSR: %#x\n",
			(u64)channel64_पढ़ो_CHAR(dc),
			channel64_पढ़ोq(dc, SAR),
			channel64_पढ़ोq(dc, DAR),
			channel64_पढ़ोl(dc, CNTR),
			channel64_पढ़ोl(dc, SAIR),
			channel64_पढ़ोl(dc, DAIR),
			channel64_पढ़ोl(dc, CCR),
			channel64_पढ़ोl(dc, CSR));
	अन्यथा
		dev_err(chan2dev(&dc->chan),
			"  CHAR: %#x SAR: %#x DAR: %#x CNTR: %#x"
			" SAIR: %#x DAIR: %#x CCR: %#x CSR: %#x\n",
			channel32_पढ़ोl(dc, CHAR),
			channel32_पढ़ोl(dc, SAR),
			channel32_पढ़ोl(dc, DAR),
			channel32_पढ़ोl(dc, CNTR),
			channel32_पढ़ोl(dc, SAIR),
			channel32_पढ़ोl(dc, DAIR),
			channel32_पढ़ोl(dc, CCR),
			channel32_पढ़ोl(dc, CSR));
पूर्ण

अटल व्योम txx9dmac_reset_chan(काष्ठा txx9dmac_chan *dc)
अणु
	channel_ग_लिखोl(dc, CCR, TXX9_DMA_CCR_CHRST);
	अगर (is_dmac64(dc)) अणु
		channel64_clear_CHAR(dc);
		channel_ग_लिखोq(dc, SAR, 0);
		channel_ग_लिखोq(dc, DAR, 0);
	पूर्ण अन्यथा अणु
		channel_ग_लिखोl(dc, CHAR, 0);
		channel_ग_लिखोl(dc, SAR, 0);
		channel_ग_लिखोl(dc, DAR, 0);
	पूर्ण
	channel_ग_लिखोl(dc, CNTR, 0);
	channel_ग_लिखोl(dc, SAIR, 0);
	channel_ग_लिखोl(dc, DAIR, 0);
	channel_ग_लिखोl(dc, CCR, 0);
पूर्ण

/* Called with dc->lock held and bh disabled */
अटल व्योम txx9dmac_करोstart(काष्ठा txx9dmac_chan *dc,
			     काष्ठा txx9dmac_desc *first)
अणु
	काष्ठा txx9dmac_slave *ds = dc->chan.निजी;
	u32 sai, dai;

	dev_vdbg(chan2dev(&dc->chan), "dostart %u %p\n",
		 first->txd.cookie, first);
	/* ASSERT:  channel is idle */
	अगर (channel_पढ़ोl(dc, CSR) & TXX9_DMA_CSR_XFACT) अणु
		dev_err(chan2dev(&dc->chan),
			"BUG: Attempted to start non-idle channel\n");
		txx9dmac_dump_regs(dc);
		/* The tasklet will hopefully advance the queue... */
		वापस;
	पूर्ण

	अगर (is_dmac64(dc)) अणु
		channel64_ग_लिखोl(dc, CNTR, 0);
		channel64_ग_लिखोl(dc, CSR, 0xffffffff);
		अगर (ds) अणु
			अगर (ds->tx_reg) अणु
				sai = ds->reg_width;
				dai = 0;
			पूर्ण अन्यथा अणु
				sai = 0;
				dai = ds->reg_width;
			पूर्ण
		पूर्ण अन्यथा अणु
			sai = 8;
			dai = 8;
		पूर्ण
		channel64_ग_लिखोl(dc, SAIR, sai);
		channel64_ग_लिखोl(dc, DAIR, dai);
		/* All 64-bit DMAC supports SMPCHN */
		channel64_ग_लिखोl(dc, CCR, dc->ccr);
		/* Writing a non zero value to CHAR will निश्चित XFACT */
		channel64_ग_लिखो_CHAR(dc, first->txd.phys);
	पूर्ण अन्यथा अणु
		channel32_ग_लिखोl(dc, CNTR, 0);
		channel32_ग_लिखोl(dc, CSR, 0xffffffff);
		अगर (ds) अणु
			अगर (ds->tx_reg) अणु
				sai = ds->reg_width;
				dai = 0;
			पूर्ण अन्यथा अणु
				sai = 0;
				dai = ds->reg_width;
			पूर्ण
		पूर्ण अन्यथा अणु
			sai = 4;
			dai = 4;
		पूर्ण
		channel32_ग_लिखोl(dc, SAIR, sai);
		channel32_ग_लिखोl(dc, DAIR, dai);
		अगर (txx9_dma_have_SMPCHN()) अणु
			channel32_ग_लिखोl(dc, CCR, dc->ccr);
			/* Writing a non zero value to CHAR will निश्चित XFACT */
			channel32_ग_लिखोl(dc, CHAR, first->txd.phys);
		पूर्ण अन्यथा अणु
			channel32_ग_लिखोl(dc, CHAR, first->txd.phys);
			channel32_ग_लिखोl(dc, CCR, dc->ccr);
		पूर्ण
	पूर्ण
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम
txx9dmac_descriptor_complete(काष्ठा txx9dmac_chan *dc,
			     काष्ठा txx9dmac_desc *desc)
अणु
	काष्ठा dmaengine_desc_callback cb;
	काष्ठा dma_async_tx_descriptor *txd = &desc->txd;

	dev_vdbg(chan2dev(&dc->chan), "descriptor %u %p complete\n",
		 txd->cookie, desc);

	dma_cookie_complete(txd);
	dmaengine_desc_get_callback(txd, &cb);

	txx9dmac_sync_desc_क्रम_cpu(dc, desc);
	list_splice_init(&desc->tx_list, &dc->मुक्त_list);
	list_move(&desc->desc_node, &dc->मुक्त_list);

	dma_descriptor_unmap(txd);
	/*
	 * The API requires that no submissions are करोne from a
	 * callback, so we करोn't need to drop the lock here
	 */
	dmaengine_desc_callback_invoke(&cb, शून्य);
	dma_run_dependencies(txd);
पूर्ण

अटल व्योम txx9dmac_dequeue(काष्ठा txx9dmac_chan *dc, काष्ठा list_head *list)
अणु
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *desc;
	काष्ठा txx9dmac_desc *prev = शून्य;

	BUG_ON(!list_empty(list));
	करो अणु
		desc = txx9dmac_first_queued(dc);
		अगर (prev) अणु
			desc_ग_लिखो_CHAR(dc, prev, desc->txd.phys);
			dma_sync_single_क्रम_device(chan2parent(&dc->chan),
				prev->txd.phys, ddev->descsize,
				DMA_TO_DEVICE);
		पूर्ण
		prev = txx9dmac_last_child(desc);
		list_move_tail(&desc->desc_node, list);
		/* Make chain-completion पूर्णांकerrupt happen */
		अगर ((desc->txd.flags & DMA_PREP_INTERRUPT) &&
		    !txx9dmac_chan_INTENT(dc))
			अवरोध;
	पूर्ण जबतक (!list_empty(&dc->queue));
पूर्ण

अटल व्योम txx9dmac_complete_all(काष्ठा txx9dmac_chan *dc)
अणु
	काष्ठा txx9dmac_desc *desc, *_desc;
	LIST_HEAD(list);

	/*
	 * Submit queued descriptors ASAP, i.e. beक्रमe we go through
	 * the completed ones.
	 */
	list_splice_init(&dc->active_list, &list);
	अगर (!list_empty(&dc->queue)) अणु
		txx9dmac_dequeue(dc, &dc->active_list);
		txx9dmac_करोstart(dc, txx9dmac_first_active(dc));
	पूर्ण

	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		txx9dmac_descriptor_complete(dc, desc);
पूर्ण

अटल व्योम txx9dmac_dump_desc(काष्ठा txx9dmac_chan *dc,
			       काष्ठा txx9dmac_hwdesc *desc)
अणु
	अगर (is_dmac64(dc)) अणु
#अगर_घोषित TXX9_DMA_USE_SIMPLE_CHAIN
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#llx s%#llx d%#llx c%#x\n",
			 (u64)desc->CHAR, desc->SAR, desc->DAR, desc->CNTR);
#अन्यथा
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#llx s%#llx d%#llx c%#x"
			 " si%#x di%#x cc%#x cs%#x\n",
			 (u64)desc->CHAR, desc->SAR, desc->DAR, desc->CNTR,
			 desc->SAIR, desc->DAIR, desc->CCR, desc->CSR);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		काष्ठा txx9dmac_hwdesc32 *d = (काष्ठा txx9dmac_hwdesc32 *)desc;
#अगर_घोषित TXX9_DMA_USE_SIMPLE_CHAIN
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#x s%#x d%#x c%#x\n",
			 d->CHAR, d->SAR, d->DAR, d->CNTR);
#अन्यथा
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#x s%#x d%#x c%#x"
			 " si%#x di%#x cc%#x cs%#x\n",
			 d->CHAR, d->SAR, d->DAR, d->CNTR,
			 d->SAIR, d->DAIR, d->CCR, d->CSR);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम txx9dmac_handle_error(काष्ठा txx9dmac_chan *dc, u32 csr)
अणु
	काष्ठा txx9dmac_desc *bad_desc;
	काष्ठा txx9dmac_desc *child;
	u32 errors;

	/*
	 * The descriptor currently at the head of the active list is
	 * borked. Since we करोn't have any way to report errors, we'll
	 * just have to scream loudly and try to carry on.
	 */
	dev_crit(chan2dev(&dc->chan), "Abnormal Chain Completion\n");
	txx9dmac_dump_regs(dc);

	bad_desc = txx9dmac_first_active(dc);
	list_del_init(&bad_desc->desc_node);

	/* Clear all error flags and try to restart the controller */
	errors = csr & (TXX9_DMA_CSR_ABCHC |
			TXX9_DMA_CSR_CFERR | TXX9_DMA_CSR_CHERR |
			TXX9_DMA_CSR_DESERR | TXX9_DMA_CSR_SORERR);
	channel_ग_लिखोl(dc, CSR, errors);

	अगर (list_empty(&dc->active_list) && !list_empty(&dc->queue))
		txx9dmac_dequeue(dc, &dc->active_list);
	अगर (!list_empty(&dc->active_list))
		txx9dmac_करोstart(dc, txx9dmac_first_active(dc));

	dev_crit(chan2dev(&dc->chan),
		 "Bad descriptor submitted for DMA! (cookie: %d)\n",
		 bad_desc->txd.cookie);
	txx9dmac_dump_desc(dc, &bad_desc->hwdesc);
	list_क्रम_each_entry(child, &bad_desc->tx_list, desc_node)
		txx9dmac_dump_desc(dc, &child->hwdesc);
	/* Pretend the descriptor completed successfully */
	txx9dmac_descriptor_complete(dc, bad_desc);
पूर्ण

अटल व्योम txx9dmac_scan_descriptors(काष्ठा txx9dmac_chan *dc)
अणु
	dma_addr_t chain;
	काष्ठा txx9dmac_desc *desc, *_desc;
	काष्ठा txx9dmac_desc *child;
	u32 csr;

	अगर (is_dmac64(dc)) अणु
		chain = channel64_पढ़ो_CHAR(dc);
		csr = channel64_पढ़ोl(dc, CSR);
		channel64_ग_लिखोl(dc, CSR, csr);
	पूर्ण अन्यथा अणु
		chain = channel32_पढ़ोl(dc, CHAR);
		csr = channel32_पढ़ोl(dc, CSR);
		channel32_ग_लिखोl(dc, CSR, csr);
	पूर्ण
	/* For dynamic chain, we should look at XFACT instead of NCHNC */
	अगर (!(csr & (TXX9_DMA_CSR_XFACT | TXX9_DMA_CSR_ABCHC))) अणु
		/* Everything we've submitted is करोne */
		txx9dmac_complete_all(dc);
		वापस;
	पूर्ण
	अगर (!(csr & TXX9_DMA_CSR_CHNEN))
		chain = 0;	/* last descriptor of this chain */

	dev_vdbg(chan2dev(&dc->chan), "scan_descriptors: char=%#llx\n",
		 (u64)chain);

	list_क्रम_each_entry_safe(desc, _desc, &dc->active_list, desc_node) अणु
		अगर (desc_पढ़ो_CHAR(dc, desc) == chain) अणु
			/* This one is currently in progress */
			अगर (csr & TXX9_DMA_CSR_ABCHC)
				जाओ scan_करोne;
			वापस;
		पूर्ण

		list_क्रम_each_entry(child, &desc->tx_list, desc_node)
			अगर (desc_पढ़ो_CHAR(dc, child) == chain) अणु
				/* Currently in progress */
				अगर (csr & TXX9_DMA_CSR_ABCHC)
					जाओ scan_करोne;
				वापस;
			पूर्ण

		/*
		 * No descriptors so far seem to be in progress, i.e.
		 * this one must be करोne.
		 */
		txx9dmac_descriptor_complete(dc, desc);
	पूर्ण
scan_करोne:
	अगर (csr & TXX9_DMA_CSR_ABCHC) अणु
		txx9dmac_handle_error(dc, csr);
		वापस;
	पूर्ण

	dev_err(chan2dev(&dc->chan),
		"BUG: All descriptors done, but channel not idle!\n");

	/* Try to जारी after resetting the channel... */
	txx9dmac_reset_chan(dc);

	अगर (!list_empty(&dc->queue)) अणु
		txx9dmac_dequeue(dc, &dc->active_list);
		txx9dmac_करोstart(dc, txx9dmac_first_active(dc));
	पूर्ण
पूर्ण

अटल व्योम txx9dmac_chan_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक irq;
	u32 csr;
	काष्ठा txx9dmac_chan *dc;

	dc = from_tasklet(dc, t, tasklet);
	csr = channel_पढ़ोl(dc, CSR);
	dev_vdbg(chan2dev(&dc->chan), "tasklet: status=%x\n", csr);

	spin_lock(&dc->lock);
	अगर (csr & (TXX9_DMA_CSR_ABCHC | TXX9_DMA_CSR_NCHNC |
		   TXX9_DMA_CSR_NTRNFC))
		txx9dmac_scan_descriptors(dc);
	spin_unlock(&dc->lock);
	irq = dc->irq;

	enable_irq(irq);
पूर्ण

अटल irqवापस_t txx9dmac_chan_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा txx9dmac_chan *dc = dev_id;

	dev_vdbg(chan2dev(&dc->chan), "interrupt: status=%#x\n",
			channel_पढ़ोl(dc, CSR));

	tasklet_schedule(&dc->tasklet);
	/*
	 * Just disable the पूर्णांकerrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	disable_irq_nosync(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम txx9dmac_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक irq;
	u32 csr;
	काष्ठा txx9dmac_chan *dc;

	काष्ठा txx9dmac_dev *ddev = from_tasklet(ddev, t, tasklet);
	u32 mcr;
	पूर्णांक i;

	mcr = dma_पढ़ोl(ddev, MCR);
	dev_vdbg(ddev->chan[0]->dma.dev, "tasklet: mcr=%x\n", mcr);
	क्रम (i = 0; i < TXX9_DMA_MAX_NR_CHANNELS; i++) अणु
		अगर ((mcr >> (24 + i)) & 0x11) अणु
			dc = ddev->chan[i];
			csr = channel_पढ़ोl(dc, CSR);
			dev_vdbg(chan2dev(&dc->chan), "tasklet: status=%x\n",
				 csr);
			spin_lock(&dc->lock);
			अगर (csr & (TXX9_DMA_CSR_ABCHC | TXX9_DMA_CSR_NCHNC |
				   TXX9_DMA_CSR_NTRNFC))
				txx9dmac_scan_descriptors(dc);
			spin_unlock(&dc->lock);
		पूर्ण
	पूर्ण
	irq = ddev->irq;

	enable_irq(irq);
पूर्ण

अटल irqवापस_t txx9dmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा txx9dmac_dev *ddev = dev_id;

	dev_vdbg(ddev->chan[0]->dma.dev, "interrupt: status=%#x\n",
			dma_पढ़ोl(ddev, MCR));

	tasklet_schedule(&ddev->tasklet);
	/*
	 * Just disable the पूर्णांकerrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	disable_irq_nosync(irq);

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

अटल dma_cookie_t txx9dmac_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा txx9dmac_desc *desc = txd_to_txx9dmac_desc(tx);
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(tx->chan);
	dma_cookie_t cookie;

	spin_lock_bh(&dc->lock);
	cookie = dma_cookie_assign(tx);

	dev_vdbg(chan2dev(tx->chan), "tx_submit: queued %u %p\n",
		 desc->txd.cookie, desc);

	list_add_tail(&desc->desc_node, &dc->queue);
	spin_unlock_bh(&dc->lock);

	वापस cookie;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
txx9dmac_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *desc;
	काष्ठा txx9dmac_desc *first;
	काष्ठा txx9dmac_desc *prev;
	माप_प्रकार xfer_count;
	माप_प्रकार offset;

	dev_vdbg(chan2dev(chan), "prep_dma_memcpy d%#llx s%#llx l%#zx f%#lx\n",
		 (u64)dest, (u64)src, len, flags);

	अगर (unlikely(!len)) अणु
		dev_dbg(chan2dev(chan), "prep_dma_memcpy: length is zero!\n");
		वापस शून्य;
	पूर्ण

	prev = first = शून्य;

	क्रम (offset = 0; offset < len; offset += xfer_count) अणु
		xfer_count = min_t(माप_प्रकार, len - offset, TXX9_DMA_MAX_COUNT);
		/*
		 * Workaround क्रम ERT-TX49H2-033, ERT-TX49H3-020,
		 * ERT-TX49H4-016 (slightly conservative)
		 */
		अगर (__is_dmac64(ddev)) अणु
			अगर (xfer_count > 0x100 &&
			    (xfer_count & 0xff) >= 0xfa &&
			    (xfer_count & 0xff) <= 0xff)
				xfer_count -= 0x20;
		पूर्ण अन्यथा अणु
			अगर (xfer_count > 0x80 &&
			    (xfer_count & 0x7f) >= 0x7e &&
			    (xfer_count & 0x7f) <= 0x7f)
				xfer_count -= 0x20;
		पूर्ण

		desc = txx9dmac_desc_get(dc);
		अगर (!desc) अणु
			txx9dmac_desc_put(dc, first);
			वापस शून्य;
		पूर्ण

		अगर (__is_dmac64(ddev)) अणु
			desc->hwdesc.SAR = src + offset;
			desc->hwdesc.DAR = dest + offset;
			desc->hwdesc.CNTR = xfer_count;
			txx9dmac_desc_set_nosimple(ddev, desc, 8, 8,
					dc->ccr | TXX9_DMA_CCR_XFACT);
		पूर्ण अन्यथा अणु
			desc->hwdesc32.SAR = src + offset;
			desc->hwdesc32.DAR = dest + offset;
			desc->hwdesc32.CNTR = xfer_count;
			txx9dmac_desc_set_nosimple(ddev, desc, 4, 4,
					dc->ccr | TXX9_DMA_CCR_XFACT);
		पूर्ण

		/*
		 * The descriptors on tx_list are not reachable from
		 * the dc->queue list or dc->active_list after a
		 * submit.  If we put all descriptors on active_list,
		 * calling of callback on the completion will be more
		 * complex.
		 */
		अगर (!first) अणु
			first = desc;
		पूर्ण अन्यथा अणु
			desc_ग_लिखो_CHAR(dc, prev, desc->txd.phys);
			dma_sync_single_क्रम_device(chan2parent(&dc->chan),
					prev->txd.phys, ddev->descsize,
					DMA_TO_DEVICE);
			list_add_tail(&desc->desc_node, &first->tx_list);
		पूर्ण
		prev = desc;
	पूर्ण

	/* Trigger पूर्णांकerrupt after last block */
	अगर (flags & DMA_PREP_INTERRUPT)
		txx9dmac_desc_set_INTENT(ddev, prev);

	desc_ग_लिखो_CHAR(dc, prev, 0);
	dma_sync_single_क्रम_device(chan2parent(&dc->chan),
			prev->txd.phys, ddev->descsize,
			DMA_TO_DEVICE);

	first->txd.flags = flags;
	first->len = len;

	वापस &first->txd;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
txx9dmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_slave *ds = chan->निजी;
	काष्ठा txx9dmac_desc *prev;
	काष्ठा txx9dmac_desc *first;
	अचिन्हित पूर्णांक i;
	काष्ठा scatterlist *sg;

	dev_vdbg(chan2dev(chan), "prep_dma_slave\n");

	BUG_ON(!ds || !ds->reg_width);
	अगर (ds->tx_reg)
		BUG_ON(direction != DMA_MEM_TO_DEV);
	अन्यथा
		BUG_ON(direction != DMA_DEV_TO_MEM);
	अगर (unlikely(!sg_len))
		वापस शून्य;

	prev = first = शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		काष्ठा txx9dmac_desc *desc;
		dma_addr_t mem;
		u32 sai, dai;

		desc = txx9dmac_desc_get(dc);
		अगर (!desc) अणु
			txx9dmac_desc_put(dc, first);
			वापस शून्य;
		पूर्ण

		mem = sg_dma_address(sg);

		अगर (__is_dmac64(ddev)) अणु
			अगर (direction == DMA_MEM_TO_DEV) अणु
				desc->hwdesc.SAR = mem;
				desc->hwdesc.DAR = ds->tx_reg;
			पूर्ण अन्यथा अणु
				desc->hwdesc.SAR = ds->rx_reg;
				desc->hwdesc.DAR = mem;
			पूर्ण
			desc->hwdesc.CNTR = sg_dma_len(sg);
		पूर्ण अन्यथा अणु
			अगर (direction == DMA_MEM_TO_DEV) अणु
				desc->hwdesc32.SAR = mem;
				desc->hwdesc32.DAR = ds->tx_reg;
			पूर्ण अन्यथा अणु
				desc->hwdesc32.SAR = ds->rx_reg;
				desc->hwdesc32.DAR = mem;
			पूर्ण
			desc->hwdesc32.CNTR = sg_dma_len(sg);
		पूर्ण
		अगर (direction == DMA_MEM_TO_DEV) अणु
			sai = ds->reg_width;
			dai = 0;
		पूर्ण अन्यथा अणु
			sai = 0;
			dai = ds->reg_width;
		पूर्ण
		txx9dmac_desc_set_nosimple(ddev, desc, sai, dai,
					dc->ccr | TXX9_DMA_CCR_XFACT);

		अगर (!first) अणु
			first = desc;
		पूर्ण अन्यथा अणु
			desc_ग_लिखो_CHAR(dc, prev, desc->txd.phys);
			dma_sync_single_क्रम_device(chan2parent(&dc->chan),
					prev->txd.phys,
					ddev->descsize,
					DMA_TO_DEVICE);
			list_add_tail(&desc->desc_node, &first->tx_list);
		पूर्ण
		prev = desc;
	पूर्ण

	/* Trigger पूर्णांकerrupt after last block */
	अगर (flags & DMA_PREP_INTERRUPT)
		txx9dmac_desc_set_INTENT(ddev, prev);

	desc_ग_लिखो_CHAR(dc, prev, 0);
	dma_sync_single_क्रम_device(chan2parent(&dc->chan),
			prev->txd.phys, ddev->descsize,
			DMA_TO_DEVICE);

	first->txd.flags = flags;
	first->len = 0;

	वापस &first->txd;
पूर्ण

अटल पूर्णांक txx9dmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	काष्ठा txx9dmac_desc *desc, *_desc;
	LIST_HEAD(list);

	dev_vdbg(chan2dev(chan), "terminate_all\n");
	spin_lock_bh(&dc->lock);

	txx9dmac_reset_chan(dc);

	/* active_list entries will end up beक्रमe queued entries */
	list_splice_init(&dc->queue, &list);
	list_splice_init(&dc->active_list, &list);

	spin_unlock_bh(&dc->lock);

	/* Flush all pending and queued descriptors */
	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		txx9dmac_descriptor_complete(dc, desc);

	वापस 0;
पूर्ण

अटल क्रमागत dma_status
txx9dmac_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
		   काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस DMA_COMPLETE;

	spin_lock_bh(&dc->lock);
	txx9dmac_scan_descriptors(dc);
	spin_unlock_bh(&dc->lock);

	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल व्योम txx9dmac_chain_dynamic(काष्ठा txx9dmac_chan *dc,
				   काष्ठा txx9dmac_desc *prev)
अणु
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *desc;
	LIST_HEAD(list);

	prev = txx9dmac_last_child(prev);
	txx9dmac_dequeue(dc, &list);
	desc = list_entry(list.next, काष्ठा txx9dmac_desc, desc_node);
	desc_ग_लिखो_CHAR(dc, prev, desc->txd.phys);
	dma_sync_single_क्रम_device(chan2parent(&dc->chan),
				   prev->txd.phys, ddev->descsize,
				   DMA_TO_DEVICE);
	अगर (!(channel_पढ़ोl(dc, CSR) & TXX9_DMA_CSR_CHNEN) &&
	    channel_पढ़ो_CHAR(dc) == prev->txd.phys)
		/* Restart chain DMA */
		channel_ग_लिखो_CHAR(dc, desc->txd.phys);
	list_splice_tail(&list, &dc->active_list);
पूर्ण

अटल व्योम txx9dmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);

	spin_lock_bh(&dc->lock);

	अगर (!list_empty(&dc->active_list))
		txx9dmac_scan_descriptors(dc);
	अगर (!list_empty(&dc->queue)) अणु
		अगर (list_empty(&dc->active_list)) अणु
			txx9dmac_dequeue(dc, &dc->active_list);
			txx9dmac_करोstart(dc, txx9dmac_first_active(dc));
		पूर्ण अन्यथा अगर (txx9_dma_have_SMPCHN()) अणु
			काष्ठा txx9dmac_desc *prev = txx9dmac_last_active(dc);

			अगर (!(prev->txd.flags & DMA_PREP_INTERRUPT) ||
			    txx9dmac_chan_INTENT(dc))
				txx9dmac_chain_dynamic(dc, prev);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&dc->lock);
पूर्ण

अटल पूर्णांक txx9dmac_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	काष्ठा txx9dmac_slave *ds = chan->निजी;
	काष्ठा txx9dmac_desc *desc;
	पूर्णांक i;

	dev_vdbg(chan2dev(chan), "alloc_chan_resources\n");

	/* ASSERT:  channel is idle */
	अगर (channel_पढ़ोl(dc, CSR) & TXX9_DMA_CSR_XFACT) अणु
		dev_dbg(chan2dev(chan), "DMA channel not idle?\n");
		वापस -EIO;
	पूर्ण

	dma_cookie_init(chan);

	dc->ccr = TXX9_DMA_CCR_IMMCHN | TXX9_DMA_CCR_INTENE | CCR_LE;
	txx9dmac_chan_set_SMPCHN(dc);
	अगर (!txx9_dma_have_SMPCHN() || (dc->ccr & TXX9_DMA_CCR_SMPCHN))
		dc->ccr |= TXX9_DMA_CCR_INTENC;
	अगर (chan->device->device_prep_dma_स_नकल) अणु
		अगर (ds)
			वापस -EINVAL;
		dc->ccr |= TXX9_DMA_CCR_XFSZ_X8;
	पूर्ण अन्यथा अणु
		अगर (!ds ||
		    (ds->tx_reg && ds->rx_reg) || (!ds->tx_reg && !ds->rx_reg))
			वापस -EINVAL;
		dc->ccr |= TXX9_DMA_CCR_EXTRQ |
			TXX9_DMA_CCR_XFSZ(__ffs(ds->reg_width));
		txx9dmac_chan_set_INTENT(dc);
	पूर्ण

	spin_lock_bh(&dc->lock);
	i = dc->descs_allocated;
	जबतक (dc->descs_allocated < TXX9_DMA_INITIAL_DESC_COUNT) अणु
		spin_unlock_bh(&dc->lock);

		desc = txx9dmac_desc_alloc(dc, GFP_KERNEL);
		अगर (!desc) अणु
			dev_info(chan2dev(chan),
				"only allocated %d descriptors\n", i);
			spin_lock_bh(&dc->lock);
			अवरोध;
		पूर्ण
		txx9dmac_desc_put(dc, desc);

		spin_lock_bh(&dc->lock);
		i = ++dc->descs_allocated;
	पूर्ण
	spin_unlock_bh(&dc->lock);

	dev_dbg(chan2dev(chan),
		"alloc_chan_resources allocated %d descriptors\n", i);

	वापस i;
पूर्ण

अटल व्योम txx9dmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	काष्ठा txx9dmac_dev *ddev = dc->ddev;
	काष्ठा txx9dmac_desc *desc, *_desc;
	LIST_HEAD(list);

	dev_dbg(chan2dev(chan), "free_chan_resources (descs allocated=%u)\n",
			dc->descs_allocated);

	/* ASSERT:  channel is idle */
	BUG_ON(!list_empty(&dc->active_list));
	BUG_ON(!list_empty(&dc->queue));
	BUG_ON(channel_पढ़ोl(dc, CSR) & TXX9_DMA_CSR_XFACT);

	spin_lock_bh(&dc->lock);
	list_splice_init(&dc->मुक्त_list, &list);
	dc->descs_allocated = 0;
	spin_unlock_bh(&dc->lock);

	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node) अणु
		dev_vdbg(chan2dev(chan), "  freeing descriptor %p\n", desc);
		dma_unmap_single(chan2parent(chan), desc->txd.phys,
				 ddev->descsize, DMA_TO_DEVICE);
		kमुक्त(desc);
	पूर्ण

	dev_vdbg(chan2dev(chan), "free_chan_resources done\n");
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम txx9dmac_off(काष्ठा txx9dmac_dev *ddev)
अणु
	dma_ग_लिखोl(ddev, MCR, 0);
पूर्ण

अटल पूर्णांक __init txx9dmac_chan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा txx9dmac_chan_platक्रमm_data *cpdata =
			dev_get_platdata(&pdev->dev);
	काष्ठा platक्रमm_device *dmac_dev = cpdata->dmac_dev;
	काष्ठा txx9dmac_platक्रमm_data *pdata = dev_get_platdata(&dmac_dev->dev);
	काष्ठा txx9dmac_chan *dc;
	पूर्णांक err;
	पूर्णांक ch = pdev->id % TXX9_DMA_MAX_NR_CHANNELS;
	पूर्णांक irq;

	dc = devm_kzalloc(&pdev->dev, माप(*dc), GFP_KERNEL);
	अगर (!dc)
		वापस -ENOMEM;

	dc->dma.dev = &pdev->dev;
	dc->dma.device_alloc_chan_resources = txx9dmac_alloc_chan_resources;
	dc->dma.device_मुक्त_chan_resources = txx9dmac_मुक्त_chan_resources;
	dc->dma.device_terminate_all = txx9dmac_terminate_all;
	dc->dma.device_tx_status = txx9dmac_tx_status;
	dc->dma.device_issue_pending = txx9dmac_issue_pending;
	अगर (pdata && pdata->स_नकल_chan == ch) अणु
		dc->dma.device_prep_dma_स_नकल = txx9dmac_prep_dma_स_नकल;
		dma_cap_set(DMA_MEMCPY, dc->dma.cap_mask);
	पूर्ण अन्यथा अणु
		dc->dma.device_prep_slave_sg = txx9dmac_prep_slave_sg;
		dma_cap_set(DMA_SLAVE, dc->dma.cap_mask);
		dma_cap_set(DMA_PRIVATE, dc->dma.cap_mask);
	पूर्ण

	INIT_LIST_HEAD(&dc->dma.channels);
	dc->ddev = platक्रमm_get_drvdata(dmac_dev);
	अगर (dc->ddev->irq < 0) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;
		tasklet_setup(&dc->tasklet, txx9dmac_chan_tasklet);
		dc->irq = irq;
		err = devm_request_irq(&pdev->dev, dc->irq,
			txx9dmac_chan_पूर्णांकerrupt, 0, dev_name(&pdev->dev), dc);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		dc->irq = -1;
	dc->ddev->chan[ch] = dc;
	dc->chan.device = &dc->dma;
	list_add_tail(&dc->chan.device_node, &dc->chan.device->channels);
	dma_cookie_init(&dc->chan);

	अगर (is_dmac64(dc))
		dc->ch_regs = &__txx9dmac_regs(dc->ddev)->CHAN[ch];
	अन्यथा
		dc->ch_regs = &__txx9dmac_regs32(dc->ddev)->CHAN[ch];
	spin_lock_init(&dc->lock);

	INIT_LIST_HEAD(&dc->active_list);
	INIT_LIST_HEAD(&dc->queue);
	INIT_LIST_HEAD(&dc->मुक्त_list);

	txx9dmac_reset_chan(dc);

	platक्रमm_set_drvdata(pdev, dc);

	err = dma_async_device_रेजिस्टर(&dc->dma);
	अगर (err)
		वापस err;
	dev_dbg(&pdev->dev, "TXx9 DMA Channel (dma%d%s%s)\n",
		dc->dma.dev_id,
		dma_has_cap(DMA_MEMCPY, dc->dma.cap_mask) ? " memcpy" : "",
		dma_has_cap(DMA_SLAVE, dc->dma.cap_mask) ? " slave" : "");

	वापस 0;
पूर्ण

अटल पूर्णांक txx9dmac_chan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा txx9dmac_chan *dc = platक्रमm_get_drvdata(pdev);


	dma_async_device_unरेजिस्टर(&dc->dma);
	अगर (dc->irq >= 0) अणु
		devm_मुक्त_irq(&pdev->dev, dc->irq, dc);
		tasklet_समाप्त(&dc->tasklet);
	पूर्ण
	dc->ddev->chan[pdev->id % TXX9_DMA_MAX_NR_CHANNELS] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक __init txx9dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा txx9dmac_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा resource *io;
	काष्ठा txx9dmac_dev *ddev;
	u32 mcr;
	पूर्णांक err;

	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!io)
		वापस -EINVAL;

	ddev = devm_kzalloc(&pdev->dev, माप(*ddev), GFP_KERNEL);
	अगर (!ddev)
		वापस -ENOMEM;

	अगर (!devm_request_mem_region(&pdev->dev, io->start, resource_size(io),
				     dev_name(&pdev->dev)))
		वापस -EBUSY;

	ddev->regs = devm_ioremap(&pdev->dev, io->start, resource_size(io));
	अगर (!ddev->regs)
		वापस -ENOMEM;
	ddev->have_64bit_regs = pdata->have_64bit_regs;
	अगर (__is_dmac64(ddev))
		ddev->descsize = माप(काष्ठा txx9dmac_hwdesc);
	अन्यथा
		ddev->descsize = माप(काष्ठा txx9dmac_hwdesc32);

	/* क्रमce dma off, just in हाल */
	txx9dmac_off(ddev);

	ddev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ddev->irq >= 0) अणु
		tasklet_setup(&ddev->tasklet, txx9dmac_tasklet);
		err = devm_request_irq(&pdev->dev, ddev->irq,
			txx9dmac_पूर्णांकerrupt, 0, dev_name(&pdev->dev), ddev);
		अगर (err)
			वापस err;
	पूर्ण

	mcr = TXX9_DMA_MCR_MSTEN | MCR_LE;
	अगर (pdata && pdata->स_नकल_chan >= 0)
		mcr |= TXX9_DMA_MCR_FIFUM(pdata->स_नकल_chan);
	dma_ग_लिखोl(ddev, MCR, mcr);

	platक्रमm_set_drvdata(pdev, ddev);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9dmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा txx9dmac_dev *ddev = platक्रमm_get_drvdata(pdev);

	txx9dmac_off(ddev);
	अगर (ddev->irq >= 0) अणु
		devm_मुक्त_irq(&pdev->dev, ddev->irq, ddev);
		tasklet_समाप्त(&ddev->tasklet);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम txx9dmac_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा txx9dmac_dev *ddev = platक्रमm_get_drvdata(pdev);

	txx9dmac_off(ddev);
पूर्ण

अटल पूर्णांक txx9dmac_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा txx9dmac_dev *ddev = dev_get_drvdata(dev);

	txx9dmac_off(ddev);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9dmac_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा txx9dmac_dev *ddev = dev_get_drvdata(dev);
	काष्ठा txx9dmac_platक्रमm_data *pdata = dev_get_platdata(dev);
	u32 mcr;

	mcr = TXX9_DMA_MCR_MSTEN | MCR_LE;
	अगर (pdata && pdata->स_नकल_chan >= 0)
		mcr |= TXX9_DMA_MCR_FIFUM(pdata->स_नकल_chan);
	dma_ग_लिखोl(ddev, MCR, mcr);
	वापस 0;

पूर्ण

अटल स्थिर काष्ठा dev_pm_ops txx9dmac_dev_pm_ops = अणु
	.suspend_noirq = txx9dmac_suspend_noirq,
	.resume_noirq = txx9dmac_resume_noirq,
पूर्ण;

अटल काष्ठा platक्रमm_driver txx9dmac_chan_driver = अणु
	.हटाओ		= txx9dmac_chan_हटाओ,
	.driver = अणु
		.name	= "txx9dmac-chan",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver txx9dmac_driver = अणु
	.हटाओ		= txx9dmac_हटाओ,
	.shutकरोwn	= txx9dmac_shutकरोwn,
	.driver = अणु
		.name	= "txx9dmac",
		.pm	= &txx9dmac_dev_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init txx9dmac_init(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_probe(&txx9dmac_driver, txx9dmac_probe);
	अगर (!rc) अणु
		rc = platक्रमm_driver_probe(&txx9dmac_chan_driver,
					   txx9dmac_chan_probe);
		अगर (rc)
			platक्रमm_driver_unरेजिस्टर(&txx9dmac_driver);
	पूर्ण
	वापस rc;
पूर्ण
module_init(txx9dmac_init);

अटल व्योम __निकास txx9dmac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&txx9dmac_chan_driver);
	platक्रमm_driver_unरेजिस्टर(&txx9dmac_driver);
पूर्ण
module_निकास(txx9dmac_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TXx9 DMA Controller driver");
MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_ALIAS("platform:txx9dmac");
MODULE_ALIAS("platform:txx9dmac-chan");
