<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * timb_dma.c timberdale FPGA DMA driver
 * Copyright (c) 2010 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA DMA engine
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/timb_dma.h>

#समावेश "dmaengine.h"

#घोषणा DRIVER_NAME "timb-dma"

/* Global DMA रेजिस्टरs */
#घोषणा TIMBDMA_ACR		0x34
#घोषणा TIMBDMA_32BIT_ADDR	0x01

#घोषणा TIMBDMA_ISR		0x080000
#घोषणा TIMBDMA_IPR		0x080004
#घोषणा TIMBDMA_IER		0x080008

/* Channel specअगरic रेजिस्टरs */
/* RX instances base addresses are 0x00, 0x40, 0x80 ...
 * TX instances base addresses are 0x18, 0x58, 0x98 ...
 */
#घोषणा TIMBDMA_INSTANCE_OFFSET		0x40
#घोषणा TIMBDMA_INSTANCE_TX_OFFSET	0x18

/* RX रेजिस्टरs, relative the instance base */
#घोषणा TIMBDMA_OFFS_RX_DHAR	0x00
#घोषणा TIMBDMA_OFFS_RX_DLAR	0x04
#घोषणा TIMBDMA_OFFS_RX_LR	0x0C
#घोषणा TIMBDMA_OFFS_RX_BLR	0x10
#घोषणा TIMBDMA_OFFS_RX_ER	0x14
#घोषणा TIMBDMA_RX_EN		0x01
/* bytes per Row, video specअगरic रेजिस्टर
 * which is placed after the TX रेजिस्टरs...
 */
#घोषणा TIMBDMA_OFFS_RX_BPRR	0x30

/* TX रेजिस्टरs, relative the instance base */
#घोषणा TIMBDMA_OFFS_TX_DHAR	0x00
#घोषणा TIMBDMA_OFFS_TX_DLAR	0x04
#घोषणा TIMBDMA_OFFS_TX_BLR	0x0C
#घोषणा TIMBDMA_OFFS_TX_LR	0x14


#घोषणा TIMB_DMA_DESC_SIZE	8

काष्ठा timb_dma_desc अणु
	काष्ठा list_head		desc_node;
	काष्ठा dma_async_tx_descriptor	txd;
	u8				*desc_list;
	अचिन्हित पूर्णांक			desc_list_len;
	bool				पूर्णांकerrupt;
पूर्ण;

काष्ठा timb_dma_chan अणु
	काष्ठा dma_chan		chan;
	व्योम __iomem		*membase;
	spinlock_t		lock; /* Used to protect data काष्ठाures,
					especially the lists and descriptors,
					from races between the tasklet and calls
					from above */
	bool			ongoing;
	काष्ठा list_head	active_list;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_list;
	अचिन्हित पूर्णांक		bytes_per_line;
	क्रमागत dma_transfer_direction	direction;
	अचिन्हित पूर्णांक		descs; /* Descriptors to allocate */
	अचिन्हित पूर्णांक		desc_elems; /* number of elems per descriptor */
पूर्ण;

काष्ठा timb_dma अणु
	काष्ठा dma_device	dma;
	व्योम __iomem		*membase;
	काष्ठा tasklet_काष्ठा	tasklet;
	काष्ठा timb_dma_chan	channels[];
पूर्ण;

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण
अटल काष्ठा device *chan2dmadev(काष्ठा dma_chan *chan)
अणु
	वापस chan2dev(chan)->parent->parent;
पूर्ण

अटल काष्ठा timb_dma *tdchantotd(काष्ठा timb_dma_chan *td_chan)
अणु
	पूर्णांक id = td_chan->chan.chan_id;
	वापस (काष्ठा timb_dma *)((u8 *)td_chan -
		id * माप(काष्ठा timb_dma_chan) - माप(काष्ठा timb_dma));
पूर्ण

/* Must be called with the spinlock held */
अटल व्योम __td_enable_chan_irq(काष्ठा timb_dma_chan *td_chan)
अणु
	पूर्णांक id = td_chan->chan.chan_id;
	काष्ठा timb_dma *td = tdchantotd(td_chan);
	u32 ier;

	/* enable पूर्णांकerrupt क्रम this channel */
	ier = ioपढ़ो32(td->membase + TIMBDMA_IER);
	ier |= 1 << id;
	dev_dbg(chan2dev(&td_chan->chan), "Enabling irq: %d, IER: 0x%x\n", id,
		ier);
	ioग_लिखो32(ier, td->membase + TIMBDMA_IER);
पूर्ण

/* Should be called with the spinlock held */
अटल bool __td_dma_करोne_ack(काष्ठा timb_dma_chan *td_chan)
अणु
	पूर्णांक id = td_chan->chan.chan_id;
	काष्ठा timb_dma *td = (काष्ठा timb_dma *)((u8 *)td_chan -
		id * माप(काष्ठा timb_dma_chan) - माप(काष्ठा timb_dma));
	u32 isr;
	bool करोne = false;

	dev_dbg(chan2dev(&td_chan->chan), "Checking irq: %d, td: %p\n", id, td);

	isr = ioपढ़ो32(td->membase + TIMBDMA_ISR) & (1 << id);
	अगर (isr) अणु
		ioग_लिखो32(isr, td->membase + TIMBDMA_ISR);
		करोne = true;
	पूर्ण

	वापस करोne;
पूर्ण

अटल पूर्णांक td_fill_desc(काष्ठा timb_dma_chan *td_chan, u8 *dma_desc,
	काष्ठा scatterlist *sg, bool last)
अणु
	अगर (sg_dma_len(sg) > अच_लघु_उच्च) अणु
		dev_err(chan2dev(&td_chan->chan), "Too big sg element\n");
		वापस -EINVAL;
	पूर्ण

	/* length must be word aligned */
	अगर (sg_dma_len(sg) % माप(u32)) अणु
		dev_err(chan2dev(&td_chan->chan), "Incorrect length: %d\n",
			sg_dma_len(sg));
		वापस -EINVAL;
	पूर्ण

	dev_dbg(chan2dev(&td_chan->chan), "desc: %p, addr: 0x%llx\n",
		dma_desc, (अचिन्हित दीर्घ दीर्घ)sg_dma_address(sg));

	dma_desc[7] = (sg_dma_address(sg) >> 24) & 0xff;
	dma_desc[6] = (sg_dma_address(sg) >> 16) & 0xff;
	dma_desc[5] = (sg_dma_address(sg) >> 8) & 0xff;
	dma_desc[4] = (sg_dma_address(sg) >> 0) & 0xff;

	dma_desc[3] = (sg_dma_len(sg) >> 8) & 0xff;
	dma_desc[2] = (sg_dma_len(sg) >> 0) & 0xff;

	dma_desc[1] = 0x00;
	dma_desc[0] = 0x21 | (last ? 0x02 : 0); /* tran, valid */

	वापस 0;
पूर्ण

/* Must be called with the spinlock held */
अटल व्योम __td_start_dma(काष्ठा timb_dma_chan *td_chan)
अणु
	काष्ठा timb_dma_desc *td_desc;

	अगर (td_chan->ongoing) अणु
		dev_err(chan2dev(&td_chan->chan),
			"Transfer already ongoing\n");
		वापस;
	पूर्ण

	td_desc = list_entry(td_chan->active_list.next, काष्ठा timb_dma_desc,
		desc_node);

	dev_dbg(chan2dev(&td_chan->chan),
		"td_chan: %p, chan: %d, membase: %p\n",
		td_chan, td_chan->chan.chan_id, td_chan->membase);

	अगर (td_chan->direction == DMA_DEV_TO_MEM) अणु

		/* descriptor address */
		ioग_लिखो32(0, td_chan->membase + TIMBDMA_OFFS_RX_DHAR);
		ioग_लिखो32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_RX_DLAR);
		/* Bytes per line */
		ioग_लिखो32(td_chan->bytes_per_line, td_chan->membase +
			TIMBDMA_OFFS_RX_BPRR);
		/* enable RX */
		ioग_लिखो32(TIMBDMA_RX_EN, td_chan->membase + TIMBDMA_OFFS_RX_ER);
	पूर्ण अन्यथा अणु
		/* address high */
		ioग_लिखो32(0, td_chan->membase + TIMBDMA_OFFS_TX_DHAR);
		ioग_लिखो32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_TX_DLAR);
	पूर्ण

	td_chan->ongoing = true;

	अगर (td_desc->पूर्णांकerrupt)
		__td_enable_chan_irq(td_chan);
पूर्ण

अटल व्योम __td_finish(काष्ठा timb_dma_chan *td_chan)
अणु
	काष्ठा dmaengine_desc_callback	cb;
	काष्ठा dma_async_tx_descriptor	*txd;
	काष्ठा timb_dma_desc		*td_desc;

	/* can happen अगर the descriptor is canceled */
	अगर (list_empty(&td_chan->active_list))
		वापस;

	td_desc = list_entry(td_chan->active_list.next, काष्ठा timb_dma_desc,
		desc_node);
	txd = &td_desc->txd;

	dev_dbg(chan2dev(&td_chan->chan), "descriptor %u complete\n",
		txd->cookie);

	/* make sure to stop the transfer */
	अगर (td_chan->direction == DMA_DEV_TO_MEM)
		ioग_लिखो32(0, td_chan->membase + TIMBDMA_OFFS_RX_ER);
/* Currently no support क्रम stopping DMA transfers
	अन्यथा
		ioग_लिखो32(0, td_chan->membase + TIMBDMA_OFFS_TX_DLAR);
*/
	dma_cookie_complete(txd);
	td_chan->ongoing = false;

	dmaengine_desc_get_callback(txd, &cb);

	list_move(&td_desc->desc_node, &td_chan->मुक्त_list);

	dma_descriptor_unmap(txd);
	/*
	 * The API requires that no submissions are करोne from a
	 * callback, so we करोn't need to drop the lock here
	 */
	dmaengine_desc_callback_invoke(&cb, शून्य);
पूर्ण

अटल u32 __td_ier_mask(काष्ठा timb_dma *td)
अणु
	पूर्णांक i;
	u32 ret = 0;

	क्रम (i = 0; i < td->dma.chancnt; i++) अणु
		काष्ठा timb_dma_chan *td_chan = td->channels + i;
		अगर (td_chan->ongoing) अणु
			काष्ठा timb_dma_desc *td_desc =
				list_entry(td_chan->active_list.next,
				काष्ठा timb_dma_desc, desc_node);
			अगर (td_desc->पूर्णांकerrupt)
				ret |= 1 << i;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __td_start_next(काष्ठा timb_dma_chan *td_chan)
अणु
	काष्ठा timb_dma_desc *td_desc;

	BUG_ON(list_empty(&td_chan->queue));
	BUG_ON(td_chan->ongoing);

	td_desc = list_entry(td_chan->queue.next, काष्ठा timb_dma_desc,
		desc_node);

	dev_dbg(chan2dev(&td_chan->chan), "%s: started %u\n",
		__func__, td_desc->txd.cookie);

	list_move(&td_desc->desc_node, &td_chan->active_list);
	__td_start_dma(td_chan);
पूर्ण

अटल dma_cookie_t td_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा timb_dma_desc *td_desc = container_of(txd, काष्ठा timb_dma_desc,
		txd);
	काष्ठा timb_dma_chan *td_chan = container_of(txd->chan,
		काष्ठा timb_dma_chan, chan);
	dma_cookie_t cookie;

	spin_lock_bh(&td_chan->lock);
	cookie = dma_cookie_assign(txd);

	अगर (list_empty(&td_chan->active_list)) अणु
		dev_dbg(chan2dev(txd->chan), "%s: started %u\n", __func__,
			txd->cookie);
		list_add_tail(&td_desc->desc_node, &td_chan->active_list);
		__td_start_dma(td_chan);
	पूर्ण अन्यथा अणु
		dev_dbg(chan2dev(txd->chan), "tx_submit: queued %u\n",
			txd->cookie);

		list_add_tail(&td_desc->desc_node, &td_chan->queue);
	पूर्ण

	spin_unlock_bh(&td_chan->lock);

	वापस cookie;
पूर्ण

अटल काष्ठा timb_dma_desc *td_alloc_init_desc(काष्ठा timb_dma_chan *td_chan)
अणु
	काष्ठा dma_chan *chan = &td_chan->chan;
	काष्ठा timb_dma_desc *td_desc;
	पूर्णांक err;

	td_desc = kzalloc(माप(काष्ठा timb_dma_desc), GFP_KERNEL);
	अगर (!td_desc)
		जाओ out;

	td_desc->desc_list_len = td_chan->desc_elems * TIMB_DMA_DESC_SIZE;

	td_desc->desc_list = kzalloc(td_desc->desc_list_len, GFP_KERNEL);
	अगर (!td_desc->desc_list)
		जाओ err;

	dma_async_tx_descriptor_init(&td_desc->txd, chan);
	td_desc->txd.tx_submit = td_tx_submit;
	td_desc->txd.flags = DMA_CTRL_ACK;

	td_desc->txd.phys = dma_map_single(chan2dmadev(chan),
		td_desc->desc_list, td_desc->desc_list_len, DMA_TO_DEVICE);

	err = dma_mapping_error(chan2dmadev(chan), td_desc->txd.phys);
	अगर (err) अणु
		dev_err(chan2dev(chan), "DMA mapping error: %d\n", err);
		जाओ err;
	पूर्ण

	वापस td_desc;
err:
	kमुक्त(td_desc->desc_list);
	kमुक्त(td_desc);
out:
	वापस शून्य;

पूर्ण

अटल व्योम td_मुक्त_desc(काष्ठा timb_dma_desc *td_desc)
अणु
	dev_dbg(chan2dev(td_desc->txd.chan), "Freeing desc: %p\n", td_desc);
	dma_unmap_single(chan2dmadev(td_desc->txd.chan), td_desc->txd.phys,
		td_desc->desc_list_len, DMA_TO_DEVICE);

	kमुक्त(td_desc->desc_list);
	kमुक्त(td_desc);
पूर्ण

अटल व्योम td_desc_put(काष्ठा timb_dma_chan *td_chan,
	काष्ठा timb_dma_desc *td_desc)
अणु
	dev_dbg(chan2dev(&td_chan->chan), "Putting desc: %p\n", td_desc);

	spin_lock_bh(&td_chan->lock);
	list_add(&td_desc->desc_node, &td_chan->मुक्त_list);
	spin_unlock_bh(&td_chan->lock);
पूर्ण

अटल काष्ठा timb_dma_desc *td_desc_get(काष्ठा timb_dma_chan *td_chan)
अणु
	काष्ठा timb_dma_desc *td_desc, *_td_desc;
	काष्ठा timb_dma_desc *ret = शून्य;

	spin_lock_bh(&td_chan->lock);
	list_क्रम_each_entry_safe(td_desc, _td_desc, &td_chan->मुक्त_list,
		desc_node) अणु
		अगर (async_tx_test_ack(&td_desc->txd)) अणु
			list_del(&td_desc->desc_node);
			ret = td_desc;
			अवरोध;
		पूर्ण
		dev_dbg(chan2dev(&td_chan->chan), "desc %p not ACKed\n",
			td_desc);
	पूर्ण
	spin_unlock_bh(&td_chan->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक td_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा timb_dma_chan *td_chan =
		container_of(chan, काष्ठा timb_dma_chan, chan);
	पूर्णांक i;

	dev_dbg(chan2dev(chan), "%s: entry\n", __func__);

	BUG_ON(!list_empty(&td_chan->मुक्त_list));
	क्रम (i = 0; i < td_chan->descs; i++) अणु
		काष्ठा timb_dma_desc *td_desc = td_alloc_init_desc(td_chan);
		अगर (!td_desc) अणु
			अगर (i)
				अवरोध;
			अन्यथा अणु
				dev_err(chan2dev(chan),
					"Couldn't allocate any descriptors\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		td_desc_put(td_chan, td_desc);
	पूर्ण

	spin_lock_bh(&td_chan->lock);
	dma_cookie_init(chan);
	spin_unlock_bh(&td_chan->lock);

	वापस 0;
पूर्ण

अटल व्योम td_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा timb_dma_chan *td_chan =
		container_of(chan, काष्ठा timb_dma_chan, chan);
	काष्ठा timb_dma_desc *td_desc, *_td_desc;
	LIST_HEAD(list);

	dev_dbg(chan2dev(chan), "%s: Entry\n", __func__);

	/* check that all descriptors are मुक्त */
	BUG_ON(!list_empty(&td_chan->active_list));
	BUG_ON(!list_empty(&td_chan->queue));

	spin_lock_bh(&td_chan->lock);
	list_splice_init(&td_chan->मुक्त_list, &list);
	spin_unlock_bh(&td_chan->lock);

	list_क्रम_each_entry_safe(td_desc, _td_desc, &list, desc_node) अणु
		dev_dbg(chan2dev(chan), "%s: Freeing desc: %p\n", __func__,
			td_desc);
		td_मुक्त_desc(td_desc);
	पूर्ण
पूर्ण

अटल क्रमागत dma_status td_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
				    काष्ठा dma_tx_state *txstate)
अणु
	क्रमागत dma_status ret;

	dev_dbg(chan2dev(chan), "%s: Entry\n", __func__);

	ret = dma_cookie_status(chan, cookie, txstate);

	dev_dbg(chan2dev(chan), "%s: exit, ret: %d\n", 	__func__, ret);

	वापस ret;
पूर्ण

अटल व्योम td_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा timb_dma_chan *td_chan =
		container_of(chan, काष्ठा timb_dma_chan, chan);

	dev_dbg(chan2dev(chan), "%s: Entry\n", __func__);
	spin_lock_bh(&td_chan->lock);

	अगर (!list_empty(&td_chan->active_list))
		/* transfer ongoing */
		अगर (__td_dma_करोne_ack(td_chan))
			__td_finish(td_chan);

	अगर (list_empty(&td_chan->active_list) && !list_empty(&td_chan->queue))
		__td_start_next(td_chan);

	spin_unlock_bh(&td_chan->lock);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *td_prep_slave_sg(काष्ठा dma_chan *chan,
	काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags,
	व्योम *context)
अणु
	काष्ठा timb_dma_chan *td_chan =
		container_of(chan, काष्ठा timb_dma_chan, chan);
	काष्ठा timb_dma_desc *td_desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक desc_usage = 0;

	अगर (!sgl || !sg_len) अणु
		dev_err(chan2dev(chan), "%s: No SG list\n", __func__);
		वापस शून्य;
	पूर्ण

	/* even channels are क्रम RX, odd क्रम TX */
	अगर (td_chan->direction != direction) अणु
		dev_err(chan2dev(chan),
			"Requesting channel in wrong direction\n");
		वापस शून्य;
	पूर्ण

	td_desc = td_desc_get(td_chan);
	अगर (!td_desc) अणु
		dev_err(chan2dev(chan), "Not enough descriptors available\n");
		वापस शून्य;
	पूर्ण

	td_desc->पूर्णांकerrupt = (flags & DMA_PREP_INTERRUPT) != 0;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		पूर्णांक err;
		अगर (desc_usage > td_desc->desc_list_len) अणु
			dev_err(chan2dev(chan), "No descriptor space\n");
			वापस शून्य;
		पूर्ण

		err = td_fill_desc(td_chan, td_desc->desc_list + desc_usage, sg,
			i == (sg_len - 1));
		अगर (err) अणु
			dev_err(chan2dev(chan), "Failed to update desc: %d\n",
				err);
			td_desc_put(td_chan, td_desc);
			वापस शून्य;
		पूर्ण
		desc_usage += TIMB_DMA_DESC_SIZE;
	पूर्ण

	dma_sync_single_क्रम_device(chan2dmadev(chan), td_desc->txd.phys,
		td_desc->desc_list_len, DMA_TO_DEVICE);

	वापस &td_desc->txd;
पूर्ण

अटल पूर्णांक td_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा timb_dma_chan *td_chan =
		container_of(chan, काष्ठा timb_dma_chan, chan);
	काष्ठा timb_dma_desc *td_desc, *_td_desc;

	dev_dbg(chan2dev(chan), "%s: Entry\n", __func__);

	/* first the easy part, put the queue पूर्णांकo the मुक्त list */
	spin_lock_bh(&td_chan->lock);
	list_क्रम_each_entry_safe(td_desc, _td_desc, &td_chan->queue,
		desc_node)
		list_move(&td_desc->desc_node, &td_chan->मुक्त_list);

	/* now tear करोwn the running */
	__td_finish(td_chan);
	spin_unlock_bh(&td_chan->lock);

	वापस 0;
पूर्ण

अटल व्योम td_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा timb_dma *td = from_tasklet(td, t, tasklet);
	u32 isr;
	u32 ipr;
	u32 ier;
	पूर्णांक i;

	isr = ioपढ़ो32(td->membase + TIMBDMA_ISR);
	ipr = isr & __td_ier_mask(td);

	/* ack the पूर्णांकerrupts */
	ioग_लिखो32(ipr, td->membase + TIMBDMA_ISR);

	क्रम (i = 0; i < td->dma.chancnt; i++)
		अगर (ipr & (1 << i)) अणु
			काष्ठा timb_dma_chan *td_chan = td->channels + i;
			spin_lock(&td_chan->lock);
			__td_finish(td_chan);
			अगर (!list_empty(&td_chan->queue))
				__td_start_next(td_chan);
			spin_unlock(&td_chan->lock);
		पूर्ण

	ier = __td_ier_mask(td);
	ioग_लिखो32(ier, td->membase + TIMBDMA_IER);
पूर्ण


अटल irqवापस_t td_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा timb_dma *td = devid;
	u32 ipr = ioपढ़ो32(td->membase + TIMBDMA_IPR);

	अगर (ipr) अणु
		/* disable पूर्णांकerrupts, will be re-enabled in tasklet */
		ioग_लिखो32(0, td->membase + TIMBDMA_IER);

		tasklet_schedule(&td->tasklet);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण


अटल पूर्णांक td_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा timb_dma_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा timb_dma *td;
	काष्ठा resource *iomem;
	पूर्णांक irq;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (!request_mem_region(iomem->start, resource_size(iomem),
		DRIVER_NAME))
		वापस -EBUSY;

	td  = kzalloc(काष्ठा_size(td, channels, pdata->nr_channels),
		      GFP_KERNEL);
	अगर (!td) अणु
		err = -ENOMEM;
		जाओ err_release_region;
	पूर्ण

	dev_dbg(&pdev->dev, "Allocated TD: %p\n", td);

	td->membase = ioremap(iomem->start, resource_size(iomem));
	अगर (!td->membase) अणु
		dev_err(&pdev->dev, "Failed to remap I/O memory\n");
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	/* 32bit addressing */
	ioग_लिखो32(TIMBDMA_32BIT_ADDR, td->membase + TIMBDMA_ACR);

	/* disable and clear any पूर्णांकerrupts */
	ioग_लिखो32(0x0, td->membase + TIMBDMA_IER);
	ioग_लिखो32(0xFFFFFFFF, td->membase + TIMBDMA_ISR);

	tasklet_setup(&td->tasklet, td_tasklet);

	err = request_irq(irq, td_irq, IRQF_SHARED, DRIVER_NAME, td);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		जाओ err_tasklet_समाप्त;
	पूर्ण

	td->dma.device_alloc_chan_resources	= td_alloc_chan_resources;
	td->dma.device_मुक्त_chan_resources	= td_मुक्त_chan_resources;
	td->dma.device_tx_status		= td_tx_status;
	td->dma.device_issue_pending		= td_issue_pending;

	dma_cap_set(DMA_SLAVE, td->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, td->dma.cap_mask);
	td->dma.device_prep_slave_sg = td_prep_slave_sg;
	td->dma.device_terminate_all = td_terminate_all;

	td->dma.dev = &pdev->dev;

	INIT_LIST_HEAD(&td->dma.channels);

	क्रम (i = 0; i < pdata->nr_channels; i++) अणु
		काष्ठा timb_dma_chan *td_chan = &td->channels[i];
		काष्ठा timb_dma_platक्रमm_data_channel *pchan =
			pdata->channels + i;

		/* even channels are RX, odd are TX */
		अगर ((i % 2) == pchan->rx) अणु
			dev_err(&pdev->dev, "Wrong channel configuration\n");
			err = -EINVAL;
			जाओ err_मुक्त_irq;
		पूर्ण

		td_chan->chan.device = &td->dma;
		dma_cookie_init(&td_chan->chan);
		spin_lock_init(&td_chan->lock);
		INIT_LIST_HEAD(&td_chan->active_list);
		INIT_LIST_HEAD(&td_chan->queue);
		INIT_LIST_HEAD(&td_chan->मुक्त_list);

		td_chan->descs = pchan->descriptors;
		td_chan->desc_elems = pchan->descriptor_elements;
		td_chan->bytes_per_line = pchan->bytes_per_line;
		td_chan->direction = pchan->rx ? DMA_DEV_TO_MEM :
			DMA_MEM_TO_DEV;

		td_chan->membase = td->membase +
			(i / 2) * TIMBDMA_INSTANCE_OFFSET +
			(pchan->rx ? 0 : TIMBDMA_INSTANCE_TX_OFFSET);

		dev_dbg(&pdev->dev, "Chan: %d, membase: %p\n",
			i, td_chan->membase);

		list_add_tail(&td_chan->chan.device_node, &td->dma.channels);
	पूर्ण

	err = dma_async_device_रेजिस्टर(&td->dma);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register async device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, td);

	dev_dbg(&pdev->dev, "Probe result: %d\n", err);
	वापस err;

err_मुक्त_irq:
	मुक्त_irq(irq, td);
err_tasklet_समाप्त:
	tasklet_समाप्त(&td->tasklet);
	iounmap(td->membase);
err_मुक्त_mem:
	kमुक्त(td);
err_release_region:
	release_mem_region(iomem->start, resource_size(iomem));

	वापस err;

पूर्ण

अटल पूर्णांक td_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा timb_dma *td = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	dma_async_device_unरेजिस्टर(&td->dma);
	मुक्त_irq(irq, td);
	tasklet_समाप्त(&td->tasklet);
	iounmap(td->membase);
	kमुक्त(td);
	release_mem_region(iomem->start, resource_size(iomem));

	dev_dbg(&pdev->dev, "Removed...\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver td_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe	= td_probe,
	.हटाओ	= td_हटाओ,
पूर्ण;

module_platक्रमm_driver(td_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Timberdale DMA controller driver");
MODULE_AUTHOR("Pelagicore AB <info@pelagicore.com>");
MODULE_ALIAS("platform:"DRIVER_NAME);
