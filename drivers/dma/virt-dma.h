<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Virtual DMA channel support क्रम DMAengine
 *
 * Copyright (C) 2012 Russell King
 */
#अगर_अघोषित VIRT_DMA_H
#घोषणा VIRT_DMA_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "dmaengine.h"

काष्ठा virt_dma_desc अणु
	काष्ठा dma_async_tx_descriptor tx;
	काष्ठा dmaengine_result tx_result;
	/* रक्षित by vc.lock */
	काष्ठा list_head node;
पूर्ण;

काष्ठा virt_dma_chan अणु
	काष्ठा dma_chan	chan;
	काष्ठा tasklet_काष्ठा task;
	व्योम (*desc_मुक्त)(काष्ठा virt_dma_desc *);

	spinlock_t lock;

	/* रक्षित by vc.lock */
	काष्ठा list_head desc_allocated;
	काष्ठा list_head desc_submitted;
	काष्ठा list_head desc_issued;
	काष्ठा list_head desc_completed;
	काष्ठा list_head desc_terminated;

	काष्ठा virt_dma_desc *cyclic;
पूर्ण;

अटल अंतरभूत काष्ठा virt_dma_chan *to_virt_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा virt_dma_chan, chan);
पूर्ण

व्योम vchan_dma_desc_मुक्त_list(काष्ठा virt_dma_chan *vc, काष्ठा list_head *head);
व्योम vchan_init(काष्ठा virt_dma_chan *vc, काष्ठा dma_device *dmadev);
काष्ठा virt_dma_desc *vchan_find_desc(काष्ठा virt_dma_chan *, dma_cookie_t);
बाह्य dma_cookie_t vchan_tx_submit(काष्ठा dma_async_tx_descriptor *);
बाह्य पूर्णांक vchan_tx_desc_मुक्त(काष्ठा dma_async_tx_descriptor *);

/**
 * vchan_tx_prep - prepare a descriptor
 * @vc: भव channel allocating this descriptor
 * @vd: भव descriptor to prepare
 * @tx_flags: flags argument passed in to prepare function
 */
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *vchan_tx_prep(काष्ठा virt_dma_chan *vc,
	काष्ठा virt_dma_desc *vd, अचिन्हित दीर्घ tx_flags)
अणु
	अचिन्हित दीर्घ flags;

	dma_async_tx_descriptor_init(&vd->tx, &vc->chan);
	vd->tx.flags = tx_flags;
	vd->tx.tx_submit = vchan_tx_submit;
	vd->tx.desc_मुक्त = vchan_tx_desc_मुक्त;

	vd->tx_result.result = DMA_TRANS_NOERROR;
	vd->tx_result.residue = 0;

	spin_lock_irqsave(&vc->lock, flags);
	list_add_tail(&vd->node, &vc->desc_allocated);
	spin_unlock_irqrestore(&vc->lock, flags);

	वापस &vd->tx;
पूर्ण

/**
 * vchan_issue_pending - move submitted descriptors to issued list
 * @vc: भव channel to update
 *
 * vc.lock must be held by caller
 */
अटल अंतरभूत bool vchan_issue_pending(काष्ठा virt_dma_chan *vc)
अणु
	list_splice_tail_init(&vc->desc_submitted, &vc->desc_issued);
	वापस !list_empty(&vc->desc_issued);
पूर्ण

/**
 * vchan_cookie_complete - report completion of a descriptor
 * @vd: भव descriptor to update
 *
 * vc.lock must be held by caller
 */
अटल अंतरभूत व्योम vchan_cookie_complete(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(vd->tx.chan);
	dma_cookie_t cookie;

	cookie = vd->tx.cookie;
	dma_cookie_complete(&vd->tx);
	dev_vdbg(vc->chan.device->dev, "txd %p[%x]: marked complete\n",
		 vd, cookie);
	list_add_tail(&vd->node, &vc->desc_completed);

	tasklet_schedule(&vc->task);
पूर्ण

/**
 * vchan_vdesc_fini - Free or reuse a descriptor
 * @vd: भव descriptor to मुक्त/reuse
 */
अटल अंतरभूत व्योम vchan_vdesc_fini(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(vd->tx.chan);

	अगर (dmaengine_desc_test_reuse(&vd->tx)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&vc->lock, flags);
		list_add(&vd->node, &vc->desc_allocated);
		spin_unlock_irqrestore(&vc->lock, flags);
	पूर्ण अन्यथा अणु
		vc->desc_मुक्त(vd);
	पूर्ण
पूर्ण

/**
 * vchan_cyclic_callback - report the completion of a period
 * @vd: भव descriptor
 */
अटल अंतरभूत व्योम vchan_cyclic_callback(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(vd->tx.chan);

	vc->cyclic = vd;
	tasklet_schedule(&vc->task);
पूर्ण

/**
 * vchan_terminate_vdesc - Disable pending cyclic callback
 * @vd: भव descriptor to be terminated
 *
 * vc.lock must be held by caller
 */
अटल अंतरभूत व्योम vchan_terminate_vdesc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(vd->tx.chan);

	list_add_tail(&vd->node, &vc->desc_terminated);

	अगर (vc->cyclic == vd)
		vc->cyclic = शून्य;
पूर्ण

/**
 * vchan_next_desc - peek at the next descriptor to be processed
 * @vc: भव channel to obtain descriptor from
 *
 * vc.lock must be held by caller
 */
अटल अंतरभूत काष्ठा virt_dma_desc *vchan_next_desc(काष्ठा virt_dma_chan *vc)
अणु
	वापस list_first_entry_or_null(&vc->desc_issued,
					काष्ठा virt_dma_desc, node);
पूर्ण

/**
 * vchan_get_all_descriptors - obtain all submitted and issued descriptors
 * @vc: भव channel to get descriptors from
 * @head: list of descriptors found
 *
 * vc.lock must be held by caller
 *
 * Removes all submitted and issued descriptors from पूर्णांकernal lists, and
 * provides a list of all descriptors found
 */
अटल अंतरभूत व्योम vchan_get_all_descriptors(काष्ठा virt_dma_chan *vc,
	काष्ठा list_head *head)
अणु
	list_splice_tail_init(&vc->desc_allocated, head);
	list_splice_tail_init(&vc->desc_submitted, head);
	list_splice_tail_init(&vc->desc_issued, head);
	list_splice_tail_init(&vc->desc_completed, head);
	list_splice_tail_init(&vc->desc_terminated, head);
पूर्ण

अटल अंतरभूत व्योम vchan_मुक्त_chan_resources(काष्ठा virt_dma_chan *vc)
अणु
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);
	vchan_get_all_descriptors(vc, &head);
	list_क्रम_each_entry(vd, &head, node)
		dmaengine_desc_clear_reuse(&vd->tx);
	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);
पूर्ण

/**
 * vchan_synchronize() - synchronize callback execution to the current context
 * @vc: भव channel to synchronize
 *
 * Makes sure that all scheduled or active callbacks have finished running. For
 * proper operation the caller has to ensure that no new callbacks are scheduled
 * after the invocation of this function started.
 * Free up the terminated cyclic descriptor to prevent memory leakage.
 */
अटल अंतरभूत व्योम vchan_synchronize(काष्ठा virt_dma_chan *vc)
अणु
	LIST_HEAD(head);
	अचिन्हित दीर्घ flags;

	tasklet_समाप्त(&vc->task);

	spin_lock_irqsave(&vc->lock, flags);

	list_splice_tail_init(&vc->desc_terminated, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);
पूर्ण

#पूर्ण_अगर
