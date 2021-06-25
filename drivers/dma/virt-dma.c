<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Virtual DMA channel support क्रम DMAengine
 *
 * Copyright (C) 2012 Russell King
 */
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश "virt-dma.h"

अटल काष्ठा virt_dma_desc *to_virt_desc(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा virt_dma_desc, tx);
पूर्ण

dma_cookie_t vchan_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(tx->chan);
	काष्ठा virt_dma_desc *vd = to_virt_desc(tx);
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&vc->lock, flags);
	cookie = dma_cookie_assign(tx);

	list_move_tail(&vd->node, &vc->desc_submitted);
	spin_unlock_irqrestore(&vc->lock, flags);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: submitted\n",
		vc, vd, cookie);

	वापस cookie;
पूर्ण
EXPORT_SYMBOL_GPL(vchan_tx_submit);

/**
 * vchan_tx_desc_मुक्त - मुक्त a reusable descriptor
 * @tx: the transfer
 *
 * This function मुक्तs a previously allocated reusable descriptor. The only
 * other way is to clear the DMA_CTRL_REUSE flag and submit one last समय the
 * transfer.
 *
 * Returns 0 upon success
 */
पूर्णांक vchan_tx_desc_मुक्त(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(tx->chan);
	काष्ठा virt_dma_desc *vd = to_virt_desc(tx);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->lock, flags);
	list_del(&vd->node);
	spin_unlock_irqrestore(&vc->lock, flags);

	dev_dbg(vc->chan.device->dev, "vchan %p: txd %p[%x]: freeing\n",
		vc, vd, vd->tx.cookie);
	vc->desc_मुक्त(vd);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vchan_tx_desc_मुक्त);

काष्ठा virt_dma_desc *vchan_find_desc(काष्ठा virt_dma_chan *vc,
	dma_cookie_t cookie)
अणु
	काष्ठा virt_dma_desc *vd;

	list_क्रम_each_entry(vd, &vc->desc_issued, node)
		अगर (vd->tx.cookie == cookie)
			वापस vd;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(vchan_find_desc);

/*
 * This tasklet handles the completion of a DMA descriptor by
 * calling its callback and मुक्तing it.
 */
अटल व्योम vchan_complete(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा virt_dma_chan *vc = from_tasklet(vc, t, task);
	काष्ठा virt_dma_desc *vd, *_vd;
	काष्ठा dmaengine_desc_callback cb;
	LIST_HEAD(head);

	spin_lock_irq(&vc->lock);
	list_splice_tail_init(&vc->desc_completed, &head);
	vd = vc->cyclic;
	अगर (vd) अणु
		vc->cyclic = शून्य;
		dmaengine_desc_get_callback(&vd->tx, &cb);
	पूर्ण अन्यथा अणु
		स_रखो(&cb, 0, माप(cb));
	पूर्ण
	spin_unlock_irq(&vc->lock);

	dmaengine_desc_callback_invoke(&cb, &vd->tx_result);

	list_क्रम_each_entry_safe(vd, _vd, &head, node) अणु
		dmaengine_desc_get_callback(&vd->tx, &cb);

		list_del(&vd->node);
		dmaengine_desc_callback_invoke(&cb, &vd->tx_result);
		vchan_vdesc_fini(vd);
	पूर्ण
पूर्ण

व्योम vchan_dma_desc_मुक्त_list(काष्ठा virt_dma_chan *vc, काष्ठा list_head *head)
अणु
	काष्ठा virt_dma_desc *vd, *_vd;

	list_क्रम_each_entry_safe(vd, _vd, head, node) अणु
		list_del(&vd->node);
		vchan_vdesc_fini(vd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vchan_dma_desc_मुक्त_list);

व्योम vchan_init(काष्ठा virt_dma_chan *vc, काष्ठा dma_device *dmadev)
अणु
	dma_cookie_init(&vc->chan);

	spin_lock_init(&vc->lock);
	INIT_LIST_HEAD(&vc->desc_allocated);
	INIT_LIST_HEAD(&vc->desc_submitted);
	INIT_LIST_HEAD(&vc->desc_issued);
	INIT_LIST_HEAD(&vc->desc_completed);
	INIT_LIST_HEAD(&vc->desc_terminated);

	tasklet_setup(&vc->task, vchan_complete);

	vc->chan.device = dmadev;
	list_add_tail(&vc->chan.device_node, &dmadev->channels);
पूर्ण
EXPORT_SYMBOL_GPL(vchan_init);

MODULE_AUTHOR("Russell King");
MODULE_LICENSE("GPL");
