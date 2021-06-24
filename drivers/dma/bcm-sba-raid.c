<शैली गुरु>
/*
 * Copyright (C) 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * Broadcom SBA RAID Driver
 *
 * The Broadcom stream buffer accelerator (SBA) provides offloading
 * capabilities क्रम RAID operations. The SBA offload engine is accessible
 * via Broadcom SoC specअगरic ring manager. Two or more offload engines
 * can share same Broadcom SoC specअगरic ring manager due to this Broadcom
 * SoC specअगरic ring manager driver is implemented as a mailbox controller
 * driver and offload engine drivers are implemented as mallbox clients.
 *
 * Typically, Broadcom SoC specअगरic ring manager will implement larger
 * number of hardware rings over one or more SBA hardware devices. By
 * design, the पूर्णांकernal buffer size of SBA hardware device is limited
 * but all offload operations supported by SBA can be broken करोwn पूर्णांकo
 * multiple small size requests and executed parallely on multiple SBA
 * hardware devices क्रम achieving high through-put.
 *
 * The Broadcom SBA RAID driver करोes not require any रेजिस्टर programming
 * except submitting request to SBA hardware device via mailbox channels.
 * This driver implements a DMA device with one DMA channel using a single
 * mailbox channel provided by Broadcom SoC specअगरic ring manager driver.
 * For having more SBA DMA channels, we can create more SBA device nodes
 * in Broadcom SoC specअगरic DTS based on number of hardware rings supported
 * by Broadcom SoC ring manager.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/list.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mailbox/brcm-message.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/raid/pq.h>

#समावेश "dmaengine.h"

/* ====== Driver macros and defines ===== */

#घोषणा SBA_TYPE_SHIFT					48
#घोषणा SBA_TYPE_MASK					GENMASK(1, 0)
#घोषणा SBA_TYPE_A					0x0
#घोषणा SBA_TYPE_B					0x2
#घोषणा SBA_TYPE_C					0x3
#घोषणा SBA_USER_DEF_SHIFT				32
#घोषणा SBA_USER_DEF_MASK				GENMASK(15, 0)
#घोषणा SBA_R_MDATA_SHIFT				24
#घोषणा SBA_R_MDATA_MASK				GENMASK(7, 0)
#घोषणा SBA_C_MDATA_MS_SHIFT				18
#घोषणा SBA_C_MDATA_MS_MASK				GENMASK(1, 0)
#घोषणा SBA_INT_SHIFT					17
#घोषणा SBA_INT_MASK					BIT(0)
#घोषणा SBA_RESP_SHIFT					16
#घोषणा SBA_RESP_MASK					BIT(0)
#घोषणा SBA_C_MDATA_SHIFT				8
#घोषणा SBA_C_MDATA_MASK				GENMASK(7, 0)
#घोषणा SBA_C_MDATA_BNUMx_SHIFT(__bnum)			(2 * (__bnum))
#घोषणा SBA_C_MDATA_BNUMx_MASK				GENMASK(1, 0)
#घोषणा SBA_C_MDATA_DNUM_SHIFT				5
#घोषणा SBA_C_MDATA_DNUM_MASK				GENMASK(4, 0)
#घोषणा SBA_C_MDATA_LS(__v)				((__v) & 0xff)
#घोषणा SBA_C_MDATA_MS(__v)				(((__v) >> 8) & 0x3)
#घोषणा SBA_CMD_SHIFT					0
#घोषणा SBA_CMD_MASK					GENMASK(3, 0)
#घोषणा SBA_CMD_ZERO_BUFFER				0x4
#घोषणा SBA_CMD_ZERO_ALL_BUFFERS			0x8
#घोषणा SBA_CMD_LOAD_BUFFER				0x9
#घोषणा SBA_CMD_XOR					0xa
#घोषणा SBA_CMD_GALOIS_XOR				0xb
#घोषणा SBA_CMD_WRITE_BUFFER				0xc
#घोषणा SBA_CMD_GALOIS					0xe

#घोषणा SBA_MAX_REQ_PER_MBOX_CHANNEL			8192
#घोषणा SBA_MAX_MSG_SEND_PER_MBOX_CHANNEL		8

/* Driver helper macros */
#घोषणा to_sba_request(tx)		\
	container_of(tx, काष्ठा sba_request, tx)
#घोषणा to_sba_device(dchan)		\
	container_of(dchan, काष्ठा sba_device, dma_chan)

/* ===== Driver data काष्ठाures ===== */

क्रमागत sba_request_flags अणु
	SBA_REQUEST_STATE_FREE		= 0x001,
	SBA_REQUEST_STATE_ALLOCED	= 0x002,
	SBA_REQUEST_STATE_PENDING	= 0x004,
	SBA_REQUEST_STATE_ACTIVE	= 0x008,
	SBA_REQUEST_STATE_ABORTED	= 0x010,
	SBA_REQUEST_STATE_MASK		= 0x0ff,
	SBA_REQUEST_FENCE		= 0x100,
पूर्ण;

काष्ठा sba_request अणु
	/* Global state */
	काष्ठा list_head node;
	काष्ठा sba_device *sba;
	u32 flags;
	/* Chained requests management */
	काष्ठा sba_request *first;
	काष्ठा list_head next;
	atomic_t next_pending_count;
	/* BRCM message data */
	काष्ठा brcm_message msg;
	काष्ठा dma_async_tx_descriptor tx;
	/* SBA commands */
	काष्ठा brcm_sba_command cmds[];
पूर्ण;

क्रमागत sba_version अणु
	SBA_VER_1 = 0,
	SBA_VER_2
पूर्ण;

काष्ठा sba_device अणु
	/* Underlying device */
	काष्ठा device *dev;
	/* DT configuration parameters */
	क्रमागत sba_version ver;
	/* Derived configuration parameters */
	u32 max_req;
	u32 hw_buf_size;
	u32 hw_resp_size;
	u32 max_pq_coefs;
	u32 max_pq_srcs;
	u32 max_cmd_per_req;
	u32 max_xor_srcs;
	u32 max_resp_pool_size;
	u32 max_cmds_pool_size;
	/* Maibox client and Mailbox channels */
	काष्ठा mbox_client client;
	काष्ठा mbox_chan *mchan;
	काष्ठा device *mbox_dev;
	/* DMA device and DMA channel */
	काष्ठा dma_device dma_dev;
	काष्ठा dma_chan dma_chan;
	/* DMA channel resources */
	व्योम *resp_base;
	dma_addr_t resp_dma_base;
	व्योम *cmds_base;
	dma_addr_t cmds_dma_base;
	spinlock_t reqs_lock;
	bool reqs_fence;
	काष्ठा list_head reqs_alloc_list;
	काष्ठा list_head reqs_pending_list;
	काष्ठा list_head reqs_active_list;
	काष्ठा list_head reqs_पातed_list;
	काष्ठा list_head reqs_मुक्त_list;
	/* DebugFS directory entries */
	काष्ठा dentry *root;
पूर्ण;

/* ====== Command helper routines ===== */

अटल अंतरभूत u64 __pure sba_cmd_enc(u64 cmd, u32 val, u32 shअगरt, u32 mask)
अणु
	cmd &= ~((u64)mask << shअगरt);
	cmd |= ((u64)(val & mask) << shअगरt);
	वापस cmd;
पूर्ण

अटल अंतरभूत u32 __pure sba_cmd_load_c_mdata(u32 b0)
अणु
	वापस b0 & SBA_C_MDATA_BNUMx_MASK;
पूर्ण

अटल अंतरभूत u32 __pure sba_cmd_ग_लिखो_c_mdata(u32 b0)
अणु
	वापस b0 & SBA_C_MDATA_BNUMx_MASK;
पूर्ण

अटल अंतरभूत u32 __pure sba_cmd_xor_c_mdata(u32 b1, u32 b0)
अणु
	वापस (b0 & SBA_C_MDATA_BNUMx_MASK) |
	       ((b1 & SBA_C_MDATA_BNUMx_MASK) << SBA_C_MDATA_BNUMx_SHIFT(1));
पूर्ण

अटल अंतरभूत u32 __pure sba_cmd_pq_c_mdata(u32 d, u32 b1, u32 b0)
अणु
	वापस (b0 & SBA_C_MDATA_BNUMx_MASK) |
	       ((b1 & SBA_C_MDATA_BNUMx_MASK) << SBA_C_MDATA_BNUMx_SHIFT(1)) |
	       ((d & SBA_C_MDATA_DNUM_MASK) << SBA_C_MDATA_DNUM_SHIFT);
पूर्ण

/* ====== General helper routines ===== */

अटल काष्ठा sba_request *sba_alloc_request(काष्ठा sba_device *sba)
अणु
	bool found = false;
	अचिन्हित दीर्घ flags;
	काष्ठा sba_request *req = शून्य;

	spin_lock_irqsave(&sba->reqs_lock, flags);
	list_क्रम_each_entry(req, &sba->reqs_मुक्त_list, node) अणु
		अगर (async_tx_test_ack(&req->tx)) अणु
			list_move_tail(&req->node, &sba->reqs_alloc_list);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sba->reqs_lock, flags);

	अगर (!found) अणु
		/*
		 * We have no more मुक्त requests so, we peek
		 * mailbox channels hoping few active requests
		 * would have completed which will create more
		 * room क्रम new requests.
		 */
		mbox_client_peek_data(sba->mchan);
		वापस शून्य;
	पूर्ण

	req->flags = SBA_REQUEST_STATE_ALLOCED;
	req->first = req;
	INIT_LIST_HEAD(&req->next);
	atomic_set(&req->next_pending_count, 1);

	dma_async_tx_descriptor_init(&req->tx, &sba->dma_chan);
	async_tx_ack(&req->tx);

	वापस req;
पूर्ण

/* Note: Must be called with sba->reqs_lock held */
अटल व्योम _sba_pending_request(काष्ठा sba_device *sba,
				 काष्ठा sba_request *req)
अणु
	lockdep_निश्चित_held(&sba->reqs_lock);
	req->flags &= ~SBA_REQUEST_STATE_MASK;
	req->flags |= SBA_REQUEST_STATE_PENDING;
	list_move_tail(&req->node, &sba->reqs_pending_list);
	अगर (list_empty(&sba->reqs_active_list))
		sba->reqs_fence = false;
पूर्ण

/* Note: Must be called with sba->reqs_lock held */
अटल bool _sba_active_request(काष्ठा sba_device *sba,
				काष्ठा sba_request *req)
अणु
	lockdep_निश्चित_held(&sba->reqs_lock);
	अगर (list_empty(&sba->reqs_active_list))
		sba->reqs_fence = false;
	अगर (sba->reqs_fence)
		वापस false;
	req->flags &= ~SBA_REQUEST_STATE_MASK;
	req->flags |= SBA_REQUEST_STATE_ACTIVE;
	list_move_tail(&req->node, &sba->reqs_active_list);
	अगर (req->flags & SBA_REQUEST_FENCE)
		sba->reqs_fence = true;
	वापस true;
पूर्ण

/* Note: Must be called with sba->reqs_lock held */
अटल व्योम _sba_पात_request(काष्ठा sba_device *sba,
			       काष्ठा sba_request *req)
अणु
	lockdep_निश्चित_held(&sba->reqs_lock);
	req->flags &= ~SBA_REQUEST_STATE_MASK;
	req->flags |= SBA_REQUEST_STATE_ABORTED;
	list_move_tail(&req->node, &sba->reqs_पातed_list);
	अगर (list_empty(&sba->reqs_active_list))
		sba->reqs_fence = false;
पूर्ण

/* Note: Must be called with sba->reqs_lock held */
अटल व्योम _sba_मुक्त_request(काष्ठा sba_device *sba,
			      काष्ठा sba_request *req)
अणु
	lockdep_निश्चित_held(&sba->reqs_lock);
	req->flags &= ~SBA_REQUEST_STATE_MASK;
	req->flags |= SBA_REQUEST_STATE_FREE;
	list_move_tail(&req->node, &sba->reqs_मुक्त_list);
	अगर (list_empty(&sba->reqs_active_list))
		sba->reqs_fence = false;
पूर्ण

अटल व्योम sba_मुक्त_chained_requests(काष्ठा sba_request *req)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_request *nreq;
	काष्ठा sba_device *sba = req->sba;

	spin_lock_irqsave(&sba->reqs_lock, flags);

	_sba_मुक्त_request(sba, req);
	list_क्रम_each_entry(nreq, &req->next, next)
		_sba_मुक्त_request(sba, nreq);

	spin_unlock_irqrestore(&sba->reqs_lock, flags);
पूर्ण

अटल व्योम sba_chain_request(काष्ठा sba_request *first,
			      काष्ठा sba_request *req)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_device *sba = req->sba;

	spin_lock_irqsave(&sba->reqs_lock, flags);

	list_add_tail(&req->next, &first->next);
	req->first = first;
	atomic_inc(&first->next_pending_count);

	spin_unlock_irqrestore(&sba->reqs_lock, flags);
पूर्ण

अटल व्योम sba_cleanup_nonpending_requests(काष्ठा sba_device *sba)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_request *req, *req1;

	spin_lock_irqsave(&sba->reqs_lock, flags);

	/* Freeup all alloced request */
	list_क्रम_each_entry_safe(req, req1, &sba->reqs_alloc_list, node)
		_sba_मुक्त_request(sba, req);

	/* Set all active requests as पातed */
	list_क्रम_each_entry_safe(req, req1, &sba->reqs_active_list, node)
		_sba_पात_request(sba, req);

	/*
	 * Note: We expect that पातed request will be eventually
	 * मुक्तd by sba_receive_message()
	 */

	spin_unlock_irqrestore(&sba->reqs_lock, flags);
पूर्ण

अटल व्योम sba_cleanup_pending_requests(काष्ठा sba_device *sba)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_request *req, *req1;

	spin_lock_irqsave(&sba->reqs_lock, flags);

	/* Freeup all pending request */
	list_क्रम_each_entry_safe(req, req1, &sba->reqs_pending_list, node)
		_sba_मुक्त_request(sba, req);

	spin_unlock_irqrestore(&sba->reqs_lock, flags);
पूर्ण

अटल पूर्णांक sba_send_mbox_request(काष्ठा sba_device *sba,
				 काष्ठा sba_request *req)
अणु
	पूर्णांक ret = 0;

	/* Send message क्रम the request */
	req->msg.error = 0;
	ret = mbox_send_message(sba->mchan, &req->msg);
	अगर (ret < 0) अणु
		dev_err(sba->dev, "send message failed with error %d", ret);
		वापस ret;
	पूर्ण

	/* Check error वापसed by mailbox controller */
	ret = req->msg.error;
	अगर (ret < 0) अणु
		dev_err(sba->dev, "message error %d", ret);
	पूर्ण

	/* Signal txकरोne क्रम mailbox channel */
	mbox_client_txकरोne(sba->mchan, ret);

	वापस ret;
पूर्ण

/* Note: Must be called with sba->reqs_lock held */
अटल व्योम _sba_process_pending_requests(काष्ठा sba_device *sba)
अणु
	पूर्णांक ret;
	u32 count;
	काष्ठा sba_request *req;

	/* Process few pending requests */
	count = SBA_MAX_MSG_SEND_PER_MBOX_CHANNEL;
	जबतक (!list_empty(&sba->reqs_pending_list) && count) अणु
		/* Get the first pending request */
		req = list_first_entry(&sba->reqs_pending_list,
				       काष्ठा sba_request, node);

		/* Try to make request active */
		अगर (!_sba_active_request(sba, req))
			अवरोध;

		/* Send request to mailbox channel */
		ret = sba_send_mbox_request(sba, req);
		अगर (ret < 0) अणु
			_sba_pending_request(sba, req);
			अवरोध;
		पूर्ण

		count--;
	पूर्ण
पूर्ण

अटल व्योम sba_process_received_request(काष्ठा sba_device *sba,
					 काष्ठा sba_request *req)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा sba_request *nreq, *first = req->first;

	/* Process only after all chained requests are received */
	अगर (!atomic_dec_वापस(&first->next_pending_count)) अणु
		tx = &first->tx;

		WARN_ON(tx->cookie < 0);
		अगर (tx->cookie > 0) अणु
			spin_lock_irqsave(&sba->reqs_lock, flags);
			dma_cookie_complete(tx);
			spin_unlock_irqrestore(&sba->reqs_lock, flags);
			dmaengine_desc_get_callback_invoke(tx, शून्य);
			dma_descriptor_unmap(tx);
			tx->callback = शून्य;
			tx->callback_result = शून्य;
		पूर्ण

		dma_run_dependencies(tx);

		spin_lock_irqsave(&sba->reqs_lock, flags);

		/* Free all requests chained to first request */
		list_क्रम_each_entry(nreq, &first->next, next)
			_sba_मुक्त_request(sba, nreq);
		INIT_LIST_HEAD(&first->next);

		/* Free the first request */
		_sba_मुक्त_request(sba, first);

		/* Process pending requests */
		_sba_process_pending_requests(sba);

		spin_unlock_irqrestore(&sba->reqs_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम sba_ग_लिखो_stats_in_seqfile(काष्ठा sba_device *sba,
				       काष्ठा seq_file *file)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_request *req;
	u32 मुक्त_count = 0, alloced_count = 0;
	u32 pending_count = 0, active_count = 0, पातed_count = 0;

	spin_lock_irqsave(&sba->reqs_lock, flags);

	list_क्रम_each_entry(req, &sba->reqs_मुक्त_list, node)
		अगर (async_tx_test_ack(&req->tx))
			मुक्त_count++;

	list_क्रम_each_entry(req, &sba->reqs_alloc_list, node)
		alloced_count++;

	list_क्रम_each_entry(req, &sba->reqs_pending_list, node)
		pending_count++;

	list_क्रम_each_entry(req, &sba->reqs_active_list, node)
		active_count++;

	list_क्रम_each_entry(req, &sba->reqs_पातed_list, node)
		पातed_count++;

	spin_unlock_irqrestore(&sba->reqs_lock, flags);

	seq_म_लिखो(file, "maximum requests   = %d\n", sba->max_req);
	seq_म_लिखो(file, "free requests      = %d\n", मुक्त_count);
	seq_म_लिखो(file, "alloced requests   = %d\n", alloced_count);
	seq_म_लिखो(file, "pending requests   = %d\n", pending_count);
	seq_म_लिखो(file, "active requests    = %d\n", active_count);
	seq_म_लिखो(file, "aborted requests   = %d\n", पातed_count);
पूर्ण

/* ====== DMAENGINE callbacks ===== */

अटल व्योम sba_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	/*
	 * Channel resources are pre-alloced so we just मुक्त-up
	 * whatever we can so that we can re-use pre-alloced
	 * channel resources next समय.
	 */
	sba_cleanup_nonpending_requests(to_sba_device(dchan));
पूर्ण

अटल पूर्णांक sba_device_terminate_all(काष्ठा dma_chan *dchan)
अणु
	/* Cleanup all pending requests */
	sba_cleanup_pending_requests(to_sba_device(dchan));

	वापस 0;
पूर्ण

अटल व्योम sba_issue_pending(काष्ठा dma_chan *dchan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sba_device *sba = to_sba_device(dchan);

	/* Process pending requests */
	spin_lock_irqsave(&sba->reqs_lock, flags);
	_sba_process_pending_requests(sba);
	spin_unlock_irqrestore(&sba->reqs_lock, flags);
पूर्ण

अटल dma_cookie_t sba_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;
	काष्ठा sba_device *sba;
	काष्ठा sba_request *req, *nreq;

	अगर (unlikely(!tx))
		वापस -EINVAL;

	sba = to_sba_device(tx->chan);
	req = to_sba_request(tx);

	/* Assign cookie and mark all chained requests pending */
	spin_lock_irqsave(&sba->reqs_lock, flags);
	cookie = dma_cookie_assign(tx);
	_sba_pending_request(sba, req);
	list_क्रम_each_entry(nreq, &req->next, next)
		_sba_pending_request(sba, nreq);
	spin_unlock_irqrestore(&sba->reqs_lock, flags);

	वापस cookie;
पूर्ण

अटल क्रमागत dma_status sba_tx_status(काष्ठा dma_chan *dchan,
				     dma_cookie_t cookie,
				     काष्ठा dma_tx_state *txstate)
अणु
	क्रमागत dma_status ret;
	काष्ठा sba_device *sba = to_sba_device(dchan);

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	mbox_client_peek_data(sba->mchan);

	वापस dma_cookie_status(dchan, cookie, txstate);
पूर्ण

अटल व्योम sba_fillup_पूर्णांकerrupt_msg(काष्ठा sba_request *req,
				     काष्ठा brcm_sba_command *cmds,
				     काष्ठा brcm_message *msg)
अणु
	u64 cmd;
	u32 c_mdata;
	dma_addr_t resp_dma = req->tx.phys;
	काष्ठा brcm_sba_command *cmdsp = cmds;

	/* Type-B command to load dummy data पूर्णांकo buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, req->sba->hw_resp_size,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	c_mdata = sba_cmd_load_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
	cmdsp->data = resp_dma;
	cmdsp->data_len = req->sba->hw_resp_size;
	cmdsp++;

	/* Type-A command to ग_लिखो buf0 to dummy location */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, req->sba->hw_resp_size,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_RESP_SHIFT, SBA_RESP_MASK);
	c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	अगर (req->sba->hw_resp_size) अणु
		cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
		cmdsp->resp = resp_dma;
		cmdsp->resp_len = req->sba->hw_resp_size;
	पूर्ण
	cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = resp_dma;
	cmdsp->data_len = req->sba->hw_resp_size;
	cmdsp++;

	/* Fillup brcm_message */
	msg->type = BRCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = req;
	msg->error = 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sba_prep_dma_पूर्णांकerrupt(काष्ठा dma_chan *dchan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sba_request *req = शून्य;
	काष्ठा sba_device *sba = to_sba_device(dchan);

	/* Alloc new request */
	req = sba_alloc_request(sba);
	अगर (!req)
		वापस शून्य;

	/*
	 * Force fence so that no requests are submitted
	 * until DMA callback क्रम this request is invoked.
	 */
	req->flags |= SBA_REQUEST_FENCE;

	/* Fillup request message */
	sba_fillup_पूर्णांकerrupt_msg(req, req->cmds, &req->msg);

	/* Init async_tx descriptor */
	req->tx.flags = flags;
	req->tx.cookie = -EBUSY;

	वापस &req->tx;
पूर्ण

अटल व्योम sba_fillup_स_नकल_msg(काष्ठा sba_request *req,
				  काष्ठा brcm_sba_command *cmds,
				  काष्ठा brcm_message *msg,
				  dma_addr_t msg_offset, माप_प्रकार msg_len,
				  dma_addr_t dst, dma_addr_t src)
अणु
	u64 cmd;
	u32 c_mdata;
	dma_addr_t resp_dma = req->tx.phys;
	काष्ठा brcm_sba_command *cmdsp = cmds;

	/* Type-B command to load data पूर्णांकo buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	c_mdata = sba_cmd_load_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
	cmdsp->data = src + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

	/* Type-A command to ग_लिखो buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_RESP_SHIFT, SBA_RESP_MASK);
	c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	अगर (req->sba->hw_resp_size) अणु
		cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
		cmdsp->resp = resp_dma;
		cmdsp->resp_len = req->sba->hw_resp_size;
	पूर्ण
	cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = dst + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

	/* Fillup brcm_message */
	msg->type = BRCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = req;
	msg->error = 0;
पूर्ण

अटल काष्ठा sba_request *
sba_prep_dma_स_नकल_req(काष्ठा sba_device *sba,
			dma_addr_t off, dma_addr_t dst, dma_addr_t src,
			माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sba_request *req = शून्य;

	/* Alloc new request */
	req = sba_alloc_request(sba);
	अगर (!req)
		वापस शून्य;
	अगर (flags & DMA_PREP_FENCE)
		req->flags |= SBA_REQUEST_FENCE;

	/* Fillup request message */
	sba_fillup_स_नकल_msg(req, req->cmds, &req->msg,
			      off, len, dst, src);

	/* Init async_tx descriptor */
	req->tx.flags = flags;
	req->tx.cookie = -EBUSY;

	वापस req;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sba_prep_dma_स_नकल(काष्ठा dma_chan *dchan, dma_addr_t dst, dma_addr_t src,
		    माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	माप_प्रकार req_len;
	dma_addr_t off = 0;
	काष्ठा sba_device *sba = to_sba_device(dchan);
	काष्ठा sba_request *first = शून्य, *req;

	/* Create chained requests where each request is upto hw_buf_size */
	जबतक (len) अणु
		req_len = (len < sba->hw_buf_size) ? len : sba->hw_buf_size;

		req = sba_prep_dma_स_नकल_req(sba, off, dst, src,
					      req_len, flags);
		अगर (!req) अणु
			अगर (first)
				sba_मुक्त_chained_requests(first);
			वापस शून्य;
		पूर्ण

		अगर (first)
			sba_chain_request(first, req);
		अन्यथा
			first = req;

		off += req_len;
		len -= req_len;
	पूर्ण

	वापस (first) ? &first->tx : शून्य;
पूर्ण

अटल व्योम sba_fillup_xor_msg(काष्ठा sba_request *req,
				काष्ठा brcm_sba_command *cmds,
				काष्ठा brcm_message *msg,
				dma_addr_t msg_offset, माप_प्रकार msg_len,
				dma_addr_t dst, dma_addr_t *src, u32 src_cnt)
अणु
	u64 cmd;
	u32 c_mdata;
	अचिन्हित पूर्णांक i;
	dma_addr_t resp_dma = req->tx.phys;
	काष्ठा brcm_sba_command *cmdsp = cmds;

	/* Type-B command to load data पूर्णांकo buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	c_mdata = sba_cmd_load_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
	cmdsp->data = src[0] + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

	/* Type-B commands to xor data with buf0 and put it back in buf0 */
	क्रम (i = 1; i < src_cnt; i++) अणु
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_xor_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOR,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = src[i] + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Type-A command to ग_लिखो buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_RESP_SHIFT, SBA_RESP_MASK);
	c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	अगर (req->sba->hw_resp_size) अणु
		cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
		cmdsp->resp = resp_dma;
		cmdsp->resp_len = req->sba->hw_resp_size;
	पूर्ण
	cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = dst + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

	/* Fillup brcm_message */
	msg->type = BRCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = req;
	msg->error = 0;
पूर्ण

अटल काष्ठा sba_request *
sba_prep_dma_xor_req(काष्ठा sba_device *sba,
		     dma_addr_t off, dma_addr_t dst, dma_addr_t *src,
		     u32 src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sba_request *req = शून्य;

	/* Alloc new request */
	req = sba_alloc_request(sba);
	अगर (!req)
		वापस शून्य;
	अगर (flags & DMA_PREP_FENCE)
		req->flags |= SBA_REQUEST_FENCE;

	/* Fillup request message */
	sba_fillup_xor_msg(req, req->cmds, &req->msg,
			   off, len, dst, src, src_cnt);

	/* Init async_tx descriptor */
	req->tx.flags = flags;
	req->tx.cookie = -EBUSY;

	वापस req;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sba_prep_dma_xor(काष्ठा dma_chan *dchan, dma_addr_t dst, dma_addr_t *src,
		 u32 src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	माप_प्रकार req_len;
	dma_addr_t off = 0;
	काष्ठा sba_device *sba = to_sba_device(dchan);
	काष्ठा sba_request *first = शून्य, *req;

	/* Sanity checks */
	अगर (unlikely(src_cnt > sba->max_xor_srcs))
		वापस शून्य;

	/* Create chained requests where each request is upto hw_buf_size */
	जबतक (len) अणु
		req_len = (len < sba->hw_buf_size) ? len : sba->hw_buf_size;

		req = sba_prep_dma_xor_req(sba, off, dst, src, src_cnt,
					   req_len, flags);
		अगर (!req) अणु
			अगर (first)
				sba_मुक्त_chained_requests(first);
			वापस शून्य;
		पूर्ण

		अगर (first)
			sba_chain_request(first, req);
		अन्यथा
			first = req;

		off += req_len;
		len -= req_len;
	पूर्ण

	वापस (first) ? &first->tx : शून्य;
पूर्ण

अटल व्योम sba_fillup_pq_msg(काष्ठा sba_request *req,
				bool pq_जारी,
				काष्ठा brcm_sba_command *cmds,
				काष्ठा brcm_message *msg,
				dma_addr_t msg_offset, माप_प्रकार msg_len,
				dma_addr_t *dst_p, dma_addr_t *dst_q,
				स्थिर u8 *scf, dma_addr_t *src, u32 src_cnt)
अणु
	u64 cmd;
	u32 c_mdata;
	अचिन्हित पूर्णांक i;
	dma_addr_t resp_dma = req->tx.phys;
	काष्ठा brcm_sba_command *cmdsp = cmds;

	अगर (pq_जारी) अणु
		/* Type-B command to load old P पूर्णांकo buf0 */
		अगर (dst_p) अणु
			cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				SBA_TYPE_SHIFT, SBA_TYPE_MASK);
			cmd = sba_cmd_enc(cmd, msg_len,
				SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
			c_mdata = sba_cmd_load_c_mdata(0);
			cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
			cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
				SBA_CMD_SHIFT, SBA_CMD_MASK);
			cmdsp->cmd = cmd;
			*cmdsp->cmd_dma = cpu_to_le64(cmd);
			cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
			cmdsp->data = *dst_p + msg_offset;
			cmdsp->data_len = msg_len;
			cmdsp++;
		पूर्ण

		/* Type-B command to load old Q पूर्णांकo buf1 */
		अगर (dst_q) अणु
			cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				SBA_TYPE_SHIFT, SBA_TYPE_MASK);
			cmd = sba_cmd_enc(cmd, msg_len,
				SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
			c_mdata = sba_cmd_load_c_mdata(1);
			cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
			cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
				SBA_CMD_SHIFT, SBA_CMD_MASK);
			cmdsp->cmd = cmd;
			*cmdsp->cmd_dma = cpu_to_le64(cmd);
			cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
			cmdsp->data = *dst_q + msg_offset;
			cmdsp->data_len = msg_len;
			cmdsp++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Type-A command to zero all buffers */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_ZERO_ALL_BUFFERS,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
		cmdsp++;
	पूर्ण

	/* Type-B commands क्रम generate P onto buf0 and Q onto buf1 */
	क्रम (i = 0; i < src_cnt; i++) अणु
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_pq_c_mdata(raid6_gflog[scf[i]], 1, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
				  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_GALOIS_XOR,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = src[i] + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Type-A command to ग_लिखो buf0 */
	अगर (dst_p) अणु
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		cmd = sba_cmd_enc(cmd, 0x1,
				  SBA_RESP_SHIFT, SBA_RESP_MASK);
		c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
		अगर (req->sba->hw_resp_size) अणु
			cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
			cmdsp->resp = resp_dma;
			cmdsp->resp_len = req->sba->hw_resp_size;
		पूर्ण
		cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
		cmdsp->data = *dst_p + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Type-A command to ग_लिखो buf1 */
	अगर (dst_q) अणु
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		cmd = sba_cmd_enc(cmd, 0x1,
				  SBA_RESP_SHIFT, SBA_RESP_MASK);
		c_mdata = sba_cmd_ग_लिखो_c_mdata(1);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
		अगर (req->sba->hw_resp_size) अणु
			cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
			cmdsp->resp = resp_dma;
			cmdsp->resp_len = req->sba->hw_resp_size;
		पूर्ण
		cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
		cmdsp->data = *dst_q + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Fillup brcm_message */
	msg->type = BRCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = req;
	msg->error = 0;
पूर्ण

अटल काष्ठा sba_request *
sba_prep_dma_pq_req(काष्ठा sba_device *sba, dma_addr_t off,
		    dma_addr_t *dst_p, dma_addr_t *dst_q, dma_addr_t *src,
		    u32 src_cnt, स्थिर u8 *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sba_request *req = शून्य;

	/* Alloc new request */
	req = sba_alloc_request(sba);
	अगर (!req)
		वापस शून्य;
	अगर (flags & DMA_PREP_FENCE)
		req->flags |= SBA_REQUEST_FENCE;

	/* Fillup request messages */
	sba_fillup_pq_msg(req, dmaf_जारी(flags),
			  req->cmds, &req->msg,
			  off, len, dst_p, dst_q, scf, src, src_cnt);

	/* Init async_tx descriptor */
	req->tx.flags = flags;
	req->tx.cookie = -EBUSY;

	वापस req;
पूर्ण

अटल व्योम sba_fillup_pq_single_msg(काष्ठा sba_request *req,
				bool pq_जारी,
				काष्ठा brcm_sba_command *cmds,
				काष्ठा brcm_message *msg,
				dma_addr_t msg_offset, माप_प्रकार msg_len,
				dma_addr_t *dst_p, dma_addr_t *dst_q,
				dma_addr_t src, u8 scf)
अणु
	u64 cmd;
	u32 c_mdata;
	u8 pos, dpos = raid6_gflog[scf];
	dma_addr_t resp_dma = req->tx.phys;
	काष्ठा brcm_sba_command *cmdsp = cmds;

	अगर (!dst_p)
		जाओ skip_p;

	अगर (pq_जारी) अणु
		/* Type-B command to load old P पूर्णांकo buf0 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_load_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = *dst_p + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;

		/*
		 * Type-B commands to xor data with buf0 and put it
		 * back in buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_xor_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOR,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = src + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण अन्यथा अणु
		/* Type-B command to load old P पूर्णांकo buf0 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_load_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_LOAD_BUFFER,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = src + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Type-A command to ग_लिखो buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_RESP_SHIFT, SBA_RESP_MASK);
	c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	अगर (req->sba->hw_resp_size) अणु
		cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
		cmdsp->resp = resp_dma;
		cmdsp->resp_len = req->sba->hw_resp_size;
	पूर्ण
	cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = *dst_p + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

skip_p:
	अगर (!dst_q)
		जाओ skip_q;

	/* Type-A command to zero all buffers */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_ZERO_ALL_BUFFERS,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	cmdsp++;

	अगर (dpos == 255)
		जाओ skip_q_computation;
	pos = (dpos < req->sba->max_pq_coefs) ?
		dpos : (req->sba->max_pq_coefs - 1);

	/*
	 * Type-B command to generate initial Q from data
	 * and store output पूर्णांकo buf0
	 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	c_mdata = sba_cmd_pq_c_mdata(pos, 0, 0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
			  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_GALOIS,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
	cmdsp->data = src + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

	dpos -= pos;

	/* Multiple Type-A command to generate final Q */
	जबतक (dpos) अणु
		pos = (dpos < req->sba->max_pq_coefs) ?
			dpos : (req->sba->max_pq_coefs - 1);

		/*
		 * Type-A command to generate Q with buf0 and
		 * buf1 store result in buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_pq_c_mdata(pos, 0, 1);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
				  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_GALOIS,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
		cmdsp++;

		dpos -= pos;
	पूर्ण

skip_q_computation:
	अगर (pq_जारी) अणु
		/*
		 * Type-B command to XOR previous output with
		 * buf0 and ग_लिखो it पूर्णांकo buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_len,
				  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
		c_mdata = sba_cmd_xor_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOR,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_le64(cmd);
		cmdsp->flags = BRCM_SBA_CMD_TYPE_B;
		cmdsp->data = *dst_q + msg_offset;
		cmdsp->data_len = msg_len;
		cmdsp++;
	पूर्ण

	/* Type-A command to ग_लिखो buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_len,
			  SBA_USER_DEF_SHIFT, SBA_USER_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_RESP_SHIFT, SBA_RESP_MASK);
	c_mdata = sba_cmd_ग_लिखो_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_LS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WRITE_BUFFER,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_le64(cmd);
	cmdsp->flags = BRCM_SBA_CMD_TYPE_A;
	अगर (req->sba->hw_resp_size) अणु
		cmdsp->flags |= BRCM_SBA_CMD_HAS_RESP;
		cmdsp->resp = resp_dma;
		cmdsp->resp_len = req->sba->hw_resp_size;
	पूर्ण
	cmdsp->flags |= BRCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = *dst_q + msg_offset;
	cmdsp->data_len = msg_len;
	cmdsp++;

skip_q:
	/* Fillup brcm_message */
	msg->type = BRCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = req;
	msg->error = 0;
पूर्ण

अटल काष्ठा sba_request *
sba_prep_dma_pq_single_req(काष्ठा sba_device *sba, dma_addr_t off,
			   dma_addr_t *dst_p, dma_addr_t *dst_q,
			   dma_addr_t src, u8 scf, माप_प्रकार len,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा sba_request *req = शून्य;

	/* Alloc new request */
	req = sba_alloc_request(sba);
	अगर (!req)
		वापस शून्य;
	अगर (flags & DMA_PREP_FENCE)
		req->flags |= SBA_REQUEST_FENCE;

	/* Fillup request messages */
	sba_fillup_pq_single_msg(req,  dmaf_जारी(flags),
				 req->cmds, &req->msg, off, len,
				 dst_p, dst_q, src, scf);

	/* Init async_tx descriptor */
	req->tx.flags = flags;
	req->tx.cookie = -EBUSY;

	वापस req;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sba_prep_dma_pq(काष्ठा dma_chan *dchan, dma_addr_t *dst, dma_addr_t *src,
		u32 src_cnt, स्थिर u8 *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	u32 i, dst_q_index;
	माप_प्रकार req_len;
	bool slow = false;
	dma_addr_t off = 0;
	dma_addr_t *dst_p = शून्य, *dst_q = शून्य;
	काष्ठा sba_device *sba = to_sba_device(dchan);
	काष्ठा sba_request *first = शून्य, *req;

	/* Sanity checks */
	अगर (unlikely(src_cnt > sba->max_pq_srcs))
		वापस शून्य;
	क्रम (i = 0; i < src_cnt; i++)
		अगर (sba->max_pq_coefs <= raid6_gflog[scf[i]])
			slow = true;

	/* Figure-out P and Q destination addresses */
	अगर (!(flags & DMA_PREP_PQ_DISABLE_P))
		dst_p = &dst[0];
	अगर (!(flags & DMA_PREP_PQ_DISABLE_Q))
		dst_q = &dst[1];

	/* Create chained requests where each request is upto hw_buf_size */
	जबतक (len) अणु
		req_len = (len < sba->hw_buf_size) ? len : sba->hw_buf_size;

		अगर (slow) अणु
			dst_q_index = src_cnt;

			अगर (dst_q) अणु
				क्रम (i = 0; i < src_cnt; i++) अणु
					अगर (*dst_q == src[i]) अणु
						dst_q_index = i;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (dst_q_index < src_cnt) अणु
				i = dst_q_index;
				req = sba_prep_dma_pq_single_req(sba,
					off, dst_p, dst_q, src[i], scf[i],
					req_len, flags | DMA_PREP_FENCE);
				अगर (!req)
					जाओ fail;

				अगर (first)
					sba_chain_request(first, req);
				अन्यथा
					first = req;

				flags |= DMA_PREP_CONTINUE;
			पूर्ण

			क्रम (i = 0; i < src_cnt; i++) अणु
				अगर (dst_q_index == i)
					जारी;

				req = sba_prep_dma_pq_single_req(sba,
					off, dst_p, dst_q, src[i], scf[i],
					req_len, flags | DMA_PREP_FENCE);
				अगर (!req)
					जाओ fail;

				अगर (first)
					sba_chain_request(first, req);
				अन्यथा
					first = req;

				flags |= DMA_PREP_CONTINUE;
			पूर्ण
		पूर्ण अन्यथा अणु
			req = sba_prep_dma_pq_req(sba, off,
						  dst_p, dst_q, src, src_cnt,
						  scf, req_len, flags);
			अगर (!req)
				जाओ fail;

			अगर (first)
				sba_chain_request(first, req);
			अन्यथा
				first = req;
		पूर्ण

		off += req_len;
		len -= req_len;
	पूर्ण

	वापस (first) ? &first->tx : शून्य;

fail:
	अगर (first)
		sba_मुक्त_chained_requests(first);
	वापस शून्य;
पूर्ण

/* ====== Mailbox callbacks ===== */

अटल व्योम sba_receive_message(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा brcm_message *m = msg;
	काष्ठा sba_request *req = m->ctx;
	काष्ठा sba_device *sba = req->sba;

	/* Error count अगर message has error */
	अगर (m->error < 0)
		dev_err(sba->dev, "%s got message with error %d",
			dma_chan_name(&sba->dma_chan), m->error);

	/* Process received request */
	sba_process_received_request(sba, req);
पूर्ण

/* ====== Debugfs callbacks ====== */

अटल पूर्णांक sba_debugfs_stats_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा sba_device *sba = dev_get_drvdata(file->निजी);

	/* Write stats in file */
	sba_ग_लिखो_stats_in_seqfile(sba, file);

	वापस 0;
पूर्ण

/* ====== Platक्रमm driver routines ===== */

अटल पूर्णांक sba_pपुनः_स्मृति_channel_resources(काष्ठा sba_device *sba)
अणु
	पूर्णांक i, j, ret = 0;
	काष्ठा sba_request *req = शून्य;

	sba->resp_base = dma_alloc_coherent(sba->mbox_dev,
					    sba->max_resp_pool_size,
					    &sba->resp_dma_base, GFP_KERNEL);
	अगर (!sba->resp_base)
		वापस -ENOMEM;

	sba->cmds_base = dma_alloc_coherent(sba->mbox_dev,
					    sba->max_cmds_pool_size,
					    &sba->cmds_dma_base, GFP_KERNEL);
	अगर (!sba->cmds_base) अणु
		ret = -ENOMEM;
		जाओ fail_मुक्त_resp_pool;
	पूर्ण

	spin_lock_init(&sba->reqs_lock);
	sba->reqs_fence = false;
	INIT_LIST_HEAD(&sba->reqs_alloc_list);
	INIT_LIST_HEAD(&sba->reqs_pending_list);
	INIT_LIST_HEAD(&sba->reqs_active_list);
	INIT_LIST_HEAD(&sba->reqs_पातed_list);
	INIT_LIST_HEAD(&sba->reqs_मुक्त_list);

	क्रम (i = 0; i < sba->max_req; i++) अणु
		req = devm_kzalloc(sba->dev,
				   काष्ठा_size(req, cmds, sba->max_cmd_per_req),
				   GFP_KERNEL);
		अगर (!req) अणु
			ret = -ENOMEM;
			जाओ fail_मुक्त_cmds_pool;
		पूर्ण
		INIT_LIST_HEAD(&req->node);
		req->sba = sba;
		req->flags = SBA_REQUEST_STATE_FREE;
		INIT_LIST_HEAD(&req->next);
		atomic_set(&req->next_pending_count, 0);
		क्रम (j = 0; j < sba->max_cmd_per_req; j++) अणु
			req->cmds[j].cmd = 0;
			req->cmds[j].cmd_dma = sba->cmds_base +
				(i * sba->max_cmd_per_req + j) * माप(u64);
			req->cmds[j].cmd_dma_addr = sba->cmds_dma_base +
				(i * sba->max_cmd_per_req + j) * माप(u64);
			req->cmds[j].flags = 0;
		पूर्ण
		स_रखो(&req->msg, 0, माप(req->msg));
		dma_async_tx_descriptor_init(&req->tx, &sba->dma_chan);
		async_tx_ack(&req->tx);
		req->tx.tx_submit = sba_tx_submit;
		req->tx.phys = sba->resp_dma_base + i * sba->hw_resp_size;
		list_add_tail(&req->node, &sba->reqs_मुक्त_list);
	पूर्ण

	वापस 0;

fail_मुक्त_cmds_pool:
	dma_मुक्त_coherent(sba->mbox_dev,
			  sba->max_cmds_pool_size,
			  sba->cmds_base, sba->cmds_dma_base);
fail_मुक्त_resp_pool:
	dma_मुक्त_coherent(sba->mbox_dev,
			  sba->max_resp_pool_size,
			  sba->resp_base, sba->resp_dma_base);
	वापस ret;
पूर्ण

अटल व्योम sba_मुक्तup_channel_resources(काष्ठा sba_device *sba)
अणु
	dmaengine_terminate_all(&sba->dma_chan);
	dma_मुक्त_coherent(sba->mbox_dev, sba->max_cmds_pool_size,
			  sba->cmds_base, sba->cmds_dma_base);
	dma_मुक्त_coherent(sba->mbox_dev, sba->max_resp_pool_size,
			  sba->resp_base, sba->resp_dma_base);
	sba->resp_base = शून्य;
	sba->resp_dma_base = 0;
पूर्ण

अटल पूर्णांक sba_async_रेजिस्टर(काष्ठा sba_device *sba)
अणु
	पूर्णांक ret;
	काष्ठा dma_device *dma_dev = &sba->dma_dev;

	/* Initialize DMA channel cookie */
	sba->dma_chan.device = dma_dev;
	dma_cookie_init(&sba->dma_chan);

	/* Initialize DMA device capability mask */
	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_INTERRUPT, dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	dma_cap_set(DMA_PQ, dma_dev->cap_mask);

	/*
	 * Set mailbox channel device as the base device of
	 * our dma_device because the actual memory accesses
	 * will be करोne by mailbox controller
	 */
	dma_dev->dev = sba->mbox_dev;

	/* Set base prep routines */
	dma_dev->device_मुक्त_chan_resources = sba_मुक्त_chan_resources;
	dma_dev->device_terminate_all = sba_device_terminate_all;
	dma_dev->device_issue_pending = sba_issue_pending;
	dma_dev->device_tx_status = sba_tx_status;

	/* Set पूर्णांकerrupt routine */
	अगर (dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask))
		dma_dev->device_prep_dma_पूर्णांकerrupt = sba_prep_dma_पूर्णांकerrupt;

	/* Set स_नकल routine */
	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask))
		dma_dev->device_prep_dma_स_नकल = sba_prep_dma_स_नकल;

	/* Set xor routine and capability */
	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		dma_dev->device_prep_dma_xor = sba_prep_dma_xor;
		dma_dev->max_xor = sba->max_xor_srcs;
	पूर्ण

	/* Set pq routine and capability */
	अगर (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) अणु
		dma_dev->device_prep_dma_pq = sba_prep_dma_pq;
		dma_set_maxpq(dma_dev, sba->max_pq_srcs, 0);
	पूर्ण

	/* Initialize DMA device channel list */
	INIT_LIST_HEAD(&dma_dev->channels);
	list_add_tail(&sba->dma_chan.device_node, &dma_dev->channels);

	/* Register with Linux async DMA framework*/
	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret) अणु
		dev_err(sba->dev, "async device register error %d", ret);
		वापस ret;
	पूर्ण

	dev_info(sba->dev, "%s capabilities: %s%s%s%s\n",
	dma_chan_name(&sba->dma_chan),
	dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask) ? "interrupt " : "",
	dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask) ? "memcpy " : "",
	dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "xor " : "",
	dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "pq " : "");

	वापस 0;
पूर्ण

अटल पूर्णांक sba_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा sba_device *sba;
	काष्ठा platक्रमm_device *mbox_pdev;
	काष्ठा of_phandle_args args;

	/* Allocate मुख्य SBA काष्ठा */
	sba = devm_kzalloc(&pdev->dev, माप(*sba), GFP_KERNEL);
	अगर (!sba)
		वापस -ENOMEM;

	sba->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, sba);

	/* Number of mailbox channels should be atleast 1 */
	ret = of_count_phandle_with_args(pdev->dev.of_node,
					 "mboxes", "#mbox-cells");
	अगर (ret <= 0)
		वापस -ENODEV;

	/* Determine SBA version from DT compatible string */
	अगर (of_device_is_compatible(sba->dev->of_node, "brcm,iproc-sba"))
		sba->ver = SBA_VER_1;
	अन्यथा अगर (of_device_is_compatible(sba->dev->of_node,
					 "brcm,iproc-sba-v2"))
		sba->ver = SBA_VER_2;
	अन्यथा
		वापस -ENODEV;

	/* Derived Configuration parameters */
	चयन (sba->ver) अणु
	हाल SBA_VER_1:
		sba->hw_buf_size = 4096;
		sba->hw_resp_size = 8;
		sba->max_pq_coefs = 6;
		sba->max_pq_srcs = 6;
		अवरोध;
	हाल SBA_VER_2:
		sba->hw_buf_size = 4096;
		sba->hw_resp_size = 8;
		sba->max_pq_coefs = 30;
		/*
		 * We can support max_pq_srcs == max_pq_coefs because
		 * we are limited by number of SBA commands that we can
		 * fit in one message क्रम underlying ring manager HW.
		 */
		sba->max_pq_srcs = 12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	sba->max_req = SBA_MAX_REQ_PER_MBOX_CHANNEL;
	sba->max_cmd_per_req = sba->max_pq_srcs + 3;
	sba->max_xor_srcs = sba->max_cmd_per_req - 1;
	sba->max_resp_pool_size = sba->max_req * sba->hw_resp_size;
	sba->max_cmds_pool_size = sba->max_req *
				  sba->max_cmd_per_req * माप(u64);

	/* Setup mailbox client */
	sba->client.dev			= &pdev->dev;
	sba->client.rx_callback		= sba_receive_message;
	sba->client.tx_block		= false;
	sba->client.knows_txकरोne	= true;
	sba->client.tx_tout		= 0;

	/* Request mailbox channel */
	sba->mchan = mbox_request_channel(&sba->client, 0);
	अगर (IS_ERR(sba->mchan)) अणु
		ret = PTR_ERR(sba->mchan);
		जाओ fail_मुक्त_mchan;
	पूर्ण

	/* Find-out underlying mailbox device */
	ret = of_parse_phandle_with_args(pdev->dev.of_node,
					 "mboxes", "#mbox-cells", 0, &args);
	अगर (ret)
		जाओ fail_मुक्त_mchan;
	mbox_pdev = of_find_device_by_node(args.np);
	of_node_put(args.np);
	अगर (!mbox_pdev) अणु
		ret = -ENODEV;
		जाओ fail_मुक्त_mchan;
	पूर्ण
	sba->mbox_dev = &mbox_pdev->dev;

	/* Pपुनः_स्मृति channel resource */
	ret = sba_pपुनः_स्मृति_channel_resources(sba);
	अगर (ret)
		जाओ fail_मुक्त_mchan;

	/* Check availability of debugfs */
	अगर (!debugfs_initialized())
		जाओ skip_debugfs;

	/* Create debugfs root entry */
	sba->root = debugfs_create_dir(dev_name(sba->dev), शून्य);

	/* Create debugfs stats entry */
	debugfs_create_devm_seqfile(sba->dev, "stats", sba->root,
				    sba_debugfs_stats_show);

skip_debugfs:

	/* Register DMA device with Linux async framework */
	ret = sba_async_रेजिस्टर(sba);
	अगर (ret)
		जाओ fail_मुक्त_resources;

	/* Prपूर्णांक device info */
	dev_info(sba->dev, "%s using SBAv%d mailbox channel from %s",
		 dma_chan_name(&sba->dma_chan), sba->ver+1,
		 dev_name(sba->mbox_dev));

	वापस 0;

fail_मुक्त_resources:
	debugfs_हटाओ_recursive(sba->root);
	sba_मुक्तup_channel_resources(sba);
fail_मुक्त_mchan:
	mbox_मुक्त_channel(sba->mchan);
	वापस ret;
पूर्ण

अटल पूर्णांक sba_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sba_device *sba = platक्रमm_get_drvdata(pdev);

	dma_async_device_unरेजिस्टर(&sba->dma_dev);

	debugfs_हटाओ_recursive(sba->root);

	sba_मुक्तup_channel_resources(sba);

	mbox_मुक्त_channel(sba->mchan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sba_of_match[] = अणु
	अणु .compatible = "brcm,iproc-sba", पूर्ण,
	अणु .compatible = "brcm,iproc-sba-v2", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sba_of_match);

अटल काष्ठा platक्रमm_driver sba_driver = अणु
	.probe = sba_probe,
	.हटाओ = sba_हटाओ,
	.driver = अणु
		.name = "bcm-sba-raid",
		.of_match_table = sba_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sba_driver);

MODULE_DESCRIPTION("Broadcom SBA RAID driver");
MODULE_AUTHOR("Anup Patel <anup.patel@broadcom.com>");
MODULE_LICENSE("GPL v2");
