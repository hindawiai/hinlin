<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/dmaengine.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "../dmaengine.h"
#समावेश "registers.h"
#समावेश "idxd.h"

अटल अंतरभूत काष्ठा idxd_wq *to_idxd_wq(काष्ठा dma_chan *c)
अणु
	काष्ठा idxd_dma_chan *idxd_chan;

	idxd_chan = container_of(c, काष्ठा idxd_dma_chan, chan);
	वापस idxd_chan->wq;
पूर्ण

व्योम idxd_dma_complete_txd(काष्ठा idxd_desc *desc,
			   क्रमागत idxd_complete_type comp_type)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dmaengine_result res;
	पूर्णांक complete = 1;

	अगर (desc->completion->status == DSA_COMP_SUCCESS)
		res.result = DMA_TRANS_NOERROR;
	अन्यथा अगर (desc->completion->status)
		res.result = DMA_TRANS_WRITE_FAILED;
	अन्यथा अगर (comp_type == IDXD_COMPLETE_ABORT)
		res.result = DMA_TRANS_ABORTED;
	अन्यथा
		complete = 0;

	tx = &desc->txd;
	अगर (complete && tx->cookie) अणु
		dma_cookie_complete(tx);
		dma_descriptor_unmap(tx);
		dmaengine_desc_get_callback_invoke(tx, &res);
		tx->callback = शून्य;
		tx->callback_result = शून्य;
	पूर्ण
पूर्ण

अटल व्योम op_flag_setup(अचिन्हित दीर्घ flags, u32 *desc_flags)
अणु
	*desc_flags = IDXD_OP_FLAG_CRAV | IDXD_OP_FLAG_RCR;
	अगर (flags & DMA_PREP_INTERRUPT)
		*desc_flags |= IDXD_OP_FLAG_RCI;
पूर्ण

अटल अंतरभूत व्योम set_completion_address(काष्ठा idxd_desc *desc,
					  u64 *compl_addr)
अणु
		*compl_addr = desc->compl_dma;
पूर्ण

अटल अंतरभूत व्योम idxd_prep_desc_common(काष्ठा idxd_wq *wq,
					 काष्ठा dsa_hw_desc *hw, अक्षर opcode,
					 u64 addr_f1, u64 addr_f2, u64 len,
					 u64 compl, u32 flags)
अणु
	hw->flags = flags;
	hw->opcode = opcode;
	hw->src_addr = addr_f1;
	hw->dst_addr = addr_f2;
	hw->xfer_size = len;
	hw->priv = !!(wq->type == IDXD_WQT_KERNEL);
	hw->completion_addr = compl;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
idxd_dma_submit_स_नकल(काष्ठा dma_chan *c, dma_addr_t dma_dest,
		       dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा idxd_wq *wq = to_idxd_wq(c);
	u32 desc_flags;
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा idxd_desc *desc;

	अगर (wq->state != IDXD_WQ_ENABLED)
		वापस शून्य;

	अगर (len > idxd->max_xfer_bytes)
		वापस शून्य;

	op_flag_setup(flags, &desc_flags);
	desc = idxd_alloc_desc(wq, IDXD_OP_BLOCK);
	अगर (IS_ERR(desc))
		वापस शून्य;

	idxd_prep_desc_common(wq, desc->hw, DSA_OPCODE_MEMMOVE,
			      dma_src, dma_dest, len, desc->compl_dma,
			      desc_flags);

	desc->txd.flags = flags;

	वापस &desc->txd;
पूर्ण

अटल पूर्णांक idxd_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idxd_wq *wq = to_idxd_wq(chan);
	काष्ठा device *dev = &wq->idxd->pdev->dev;

	idxd_wq_get(wq);
	dev_dbg(dev, "%s: client_count: %d\n", __func__,
		idxd_wq_refcount(wq));
	वापस 0;
पूर्ण

अटल व्योम idxd_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idxd_wq *wq = to_idxd_wq(chan);
	काष्ठा device *dev = &wq->idxd->pdev->dev;

	idxd_wq_put(wq);
	dev_dbg(dev, "%s: client_count: %d\n", __func__,
		idxd_wq_refcount(wq));
पूर्ण

अटल क्रमागत dma_status idxd_dma_tx_status(काष्ठा dma_chan *dma_chan,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *txstate)
अणु
	वापस DMA_OUT_OF_ORDER;
पूर्ण

/*
 * issue_pending() करोes not need to करो anything since tx_submit() करोes the job
 * alपढ़ोy.
 */
अटल व्योम idxd_dma_issue_pending(काष्ठा dma_chan *dma_chan)
अणु
पूर्ण

अटल dma_cookie_t idxd_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_chan *c = tx->chan;
	काष्ठा idxd_wq *wq = to_idxd_wq(c);
	dma_cookie_t cookie;
	पूर्णांक rc;
	काष्ठा idxd_desc *desc = container_of(tx, काष्ठा idxd_desc, txd);

	cookie = dma_cookie_assign(tx);

	rc = idxd_submit_desc(wq, desc);
	अगर (rc < 0) अणु
		idxd_मुक्त_desc(wq, desc);
		वापस rc;
	पूर्ण

	वापस cookie;
पूर्ण

अटल व्योम idxd_dma_release(काष्ठा dma_device *device)
अणु
	काष्ठा idxd_dma_dev *idxd_dma = container_of(device, काष्ठा idxd_dma_dev, dma);

	kमुक्त(idxd_dma);
पूर्ण

पूर्णांक idxd_रेजिस्टर_dma_device(काष्ठा idxd_device *idxd)
अणु
	काष्ठा idxd_dma_dev *idxd_dma;
	काष्ठा dma_device *dma;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc;

	idxd_dma = kzalloc_node(माप(*idxd_dma), GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd_dma)
		वापस -ENOMEM;

	dma = &idxd_dma->dma;
	INIT_LIST_HEAD(&dma->channels);
	dma->dev = dev;

	dma_cap_set(DMA_PRIVATE, dma->cap_mask);
	dma_cap_set(DMA_COMPLETION_NO_ORDER, dma->cap_mask);
	dma->device_release = idxd_dma_release;

	अगर (idxd->hw.opcap.bits[0] & IDXD_OPCAP_MEMMOVE) अणु
		dma_cap_set(DMA_MEMCPY, dma->cap_mask);
		dma->device_prep_dma_स_नकल = idxd_dma_submit_स_नकल;
	पूर्ण

	dma->device_tx_status = idxd_dma_tx_status;
	dma->device_issue_pending = idxd_dma_issue_pending;
	dma->device_alloc_chan_resources = idxd_dma_alloc_chan_resources;
	dma->device_मुक्त_chan_resources = idxd_dma_मुक्त_chan_resources;

	rc = dma_async_device_रेजिस्टर(dma);
	अगर (rc < 0) अणु
		kमुक्त(idxd_dma);
		वापस rc;
	पूर्ण

	idxd_dma->idxd = idxd;
	/*
	 * This poपूर्णांकer is रक्षित by the refs taken by the dma_chan. It will reमुख्य valid
	 * as दीर्घ as there are outstanding channels.
	 */
	idxd->idxd_dma = idxd_dma;
	वापस 0;
पूर्ण

व्योम idxd_unरेजिस्टर_dma_device(काष्ठा idxd_device *idxd)
अणु
	dma_async_device_unरेजिस्टर(&idxd->idxd_dma->dma);
पूर्ण

पूर्णांक idxd_रेजिस्टर_dma_channel(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा dma_device *dma = &idxd->idxd_dma->dma;
	काष्ठा device *dev = &idxd->pdev->dev;
	काष्ठा idxd_dma_chan *idxd_chan;
	काष्ठा dma_chan *chan;
	पूर्णांक rc, i;

	idxd_chan = kzalloc_node(माप(*idxd_chan), GFP_KERNEL, dev_to_node(dev));
	अगर (!idxd_chan)
		वापस -ENOMEM;

	chan = &idxd_chan->chan;
	chan->device = dma;
	list_add_tail(&chan->device_node, &dma->channels);

	क्रम (i = 0; i < wq->num_descs; i++) अणु
		काष्ठा idxd_desc *desc = wq->descs[i];

		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.tx_submit = idxd_dma_tx_submit;
	पूर्ण

	rc = dma_async_device_channel_रेजिस्टर(dma, chan);
	अगर (rc < 0) अणु
		kमुक्त(idxd_chan);
		वापस rc;
	पूर्ण

	wq->idxd_chan = idxd_chan;
	idxd_chan->wq = wq;
	get_device(&wq->conf_dev);

	वापस 0;
पूर्ण

व्योम idxd_unरेजिस्टर_dma_channel(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_dma_chan *idxd_chan = wq->idxd_chan;
	काष्ठा dma_chan *chan = &idxd_chan->chan;
	काष्ठा idxd_dma_dev *idxd_dma = wq->idxd->idxd_dma;

	dma_async_device_channel_unरेजिस्टर(&idxd_dma->dma, chan);
	list_del(&chan->device_node);
	kमुक्त(wq->idxd_chan);
	wq->idxd_chan = शून्य;
	put_device(&wq->conf_dev);
पूर्ण
