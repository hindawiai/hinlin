<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/nospec.h>
#समावेश "cc_driver.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_request_mgr.h"
#समावेश "cc_pm.h"

#घोषणा CC_MAX_POLL_ITER	10
/* The highest descriptor count in used */
#घोषणा CC_MAX_DESC_SEQ_LEN	23

काष्ठा cc_req_mgr_handle अणु
	/* Request manager resources */
	अचिन्हित पूर्णांक hw_queue_size; /* HW capability */
	अचिन्हित पूर्णांक min_मुक्त_hw_slots;
	अचिन्हित पूर्णांक max_used_sw_slots;
	काष्ठा cc_crypto_req req_queue[MAX_REQUEST_QUEUE_SIZE];
	u32 req_queue_head;
	u32 req_queue_tail;
	u32 axi_completed;
	u32 q_मुक्त_slots;
	/* This lock protects access to HW रेजिस्टर
	 * that must be single request at a समय
	 */
	spinlock_t hw_lock;
	काष्ठा cc_hw_desc compl_desc;
	u8 *dummy_comp_buff;
	dma_addr_t dummy_comp_buff_dma;

	/* backlog queue */
	काष्ठा list_head backlog;
	अचिन्हित पूर्णांक bl_len;
	spinlock_t bl_lock; /* protect backlog queue */

#अगर_घोषित COMP_IN_WQ
	काष्ठा workqueue_काष्ठा *workq;
	काष्ठा delayed_work compwork;
#अन्यथा
	काष्ठा tasklet_काष्ठा comptask;
#पूर्ण_अगर
पूर्ण;

काष्ठा cc_bl_item अणु
	काष्ठा cc_crypto_req creq;
	काष्ठा cc_hw_desc desc[CC_MAX_DESC_SEQ_LEN];
	अचिन्हित पूर्णांक len;
	काष्ठा list_head list;
	bool notअगर;
पूर्ण;

अटल स्थिर u32 cc_cpp_पूर्णांक_masks[CC_CPP_NUM_ALGS][CC_CPP_NUM_SLOTS] = अणु
	अणु BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_0_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_1_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_2_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_3_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_4_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_5_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_6_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_AES_7_INT_BIT_SHIFT) पूर्ण,
	अणु BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_0_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_1_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_2_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_3_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_4_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_5_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_6_INT_BIT_SHIFT),
	  BIT(CC_HOST_IRR_REE_OP_ABORTED_SM_7_INT_BIT_SHIFT) पूर्ण
पूर्ण;

अटल व्योम comp_handler(अचिन्हित दीर्घ devarg);
#अगर_घोषित COMP_IN_WQ
अटल व्योम comp_work_handler(काष्ठा work_काष्ठा *work);
#पूर्ण_अगर

अटल अंतरभूत u32 cc_cpp_पूर्णांक_mask(क्रमागत cc_cpp_alg alg, पूर्णांक slot)
अणु
	alg = array_index_nospec(alg, CC_CPP_NUM_ALGS);
	slot = array_index_nospec(slot, CC_CPP_NUM_SLOTS);

	वापस cc_cpp_पूर्णांक_masks[alg][slot];
पूर्ण

व्योम cc_req_mgr_fini(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_req_mgr_handle *req_mgr_h = drvdata->request_mgr_handle;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	अगर (!req_mgr_h)
		वापस; /* Not allocated */

	अगर (req_mgr_h->dummy_comp_buff_dma) अणु
		dma_मुक्त_coherent(dev, माप(u32), req_mgr_h->dummy_comp_buff,
				  req_mgr_h->dummy_comp_buff_dma);
	पूर्ण

	dev_dbg(dev, "max_used_hw_slots=%d\n", (req_mgr_h->hw_queue_size -
						req_mgr_h->min_मुक्त_hw_slots));
	dev_dbg(dev, "max_used_sw_slots=%d\n", req_mgr_h->max_used_sw_slots);

#अगर_घोषित COMP_IN_WQ
	flush_workqueue(req_mgr_h->workq);
	destroy_workqueue(req_mgr_h->workq);
#अन्यथा
	/* Kill tasklet */
	tasklet_समाप्त(&req_mgr_h->comptask);
#पूर्ण_अगर
	kमुक्त_sensitive(req_mgr_h);
	drvdata->request_mgr_handle = शून्य;
पूर्ण

पूर्णांक cc_req_mgr_init(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_req_mgr_handle *req_mgr_h;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	पूर्णांक rc = 0;

	req_mgr_h = kzalloc(माप(*req_mgr_h), GFP_KERNEL);
	अगर (!req_mgr_h) अणु
		rc = -ENOMEM;
		जाओ req_mgr_init_err;
	पूर्ण

	drvdata->request_mgr_handle = req_mgr_h;

	spin_lock_init(&req_mgr_h->hw_lock);
	spin_lock_init(&req_mgr_h->bl_lock);
	INIT_LIST_HEAD(&req_mgr_h->backlog);

#अगर_घोषित COMP_IN_WQ
	dev_dbg(dev, "Initializing completion workqueue\n");
	req_mgr_h->workq = create_singlethपढ़ो_workqueue("ccree");
	अगर (!req_mgr_h->workq) अणु
		dev_err(dev, "Failed creating work queue\n");
		rc = -ENOMEM;
		जाओ req_mgr_init_err;
	पूर्ण
	INIT_DELAYED_WORK(&req_mgr_h->compwork, comp_work_handler);
#अन्यथा
	dev_dbg(dev, "Initializing completion tasklet\n");
	tasklet_init(&req_mgr_h->comptask, comp_handler,
		     (अचिन्हित दीर्घ)drvdata);
#पूर्ण_अगर
	req_mgr_h->hw_queue_size = cc_ioपढ़ो(drvdata,
					     CC_REG(DSCRPTR_QUEUE_SRAM_SIZE));
	dev_dbg(dev, "hw_queue_size=0x%08X\n", req_mgr_h->hw_queue_size);
	अगर (req_mgr_h->hw_queue_size < MIN_HW_QUEUE_SIZE) अणु
		dev_err(dev, "Invalid HW queue size = %u (Min. required is %u)\n",
			req_mgr_h->hw_queue_size, MIN_HW_QUEUE_SIZE);
		rc = -ENOMEM;
		जाओ req_mgr_init_err;
	पूर्ण
	req_mgr_h->min_मुक्त_hw_slots = req_mgr_h->hw_queue_size;
	req_mgr_h->max_used_sw_slots = 0;

	/* Allocate DMA word क्रम "dummy" completion descriptor use */
	req_mgr_h->dummy_comp_buff =
		dma_alloc_coherent(dev, माप(u32),
				   &req_mgr_h->dummy_comp_buff_dma,
				   GFP_KERNEL);
	अगर (!req_mgr_h->dummy_comp_buff) अणु
		dev_err(dev, "Not enough memory to allocate DMA (%zu) dropped buffer\n",
			माप(u32));
		rc = -ENOMEM;
		जाओ req_mgr_init_err;
	पूर्ण

	/* Init. "dummy" completion descriptor */
	hw_desc_init(&req_mgr_h->compl_desc);
	set_din_स्थिर(&req_mgr_h->compl_desc, 0, माप(u32));
	set_करोut_dlli(&req_mgr_h->compl_desc, req_mgr_h->dummy_comp_buff_dma,
		      माप(u32), NS_BIT, 1);
	set_flow_mode(&req_mgr_h->compl_desc, BYPASS);
	set_queue_last_ind(drvdata, &req_mgr_h->compl_desc);

	वापस 0;

req_mgr_init_err:
	cc_req_mgr_fini(drvdata);
	वापस rc;
पूर्ण

अटल व्योम enqueue_seq(काष्ठा cc_drvdata *drvdata, काष्ठा cc_hw_desc seq[],
			अचिन्हित पूर्णांक seq_len)
अणु
	पूर्णांक i, w;
	व्योम __iomem *reg = drvdata->cc_base + CC_REG(DSCRPTR_QUEUE_WORD0);
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	/*
	 * We करो indeed ग_लिखो all 6 command words to the same
	 * रेजिस्टर. The HW supports this.
	 */

	क्रम (i = 0; i < seq_len; i++) अणु
		क्रम (w = 0; w <= 5; w++)
			ग_लिखोl_relaxed(seq[i].word[w], reg);

		अगर (cc_dump_desc)
			dev_dbg(dev, "desc[%02d]: 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
				i, seq[i].word[0], seq[i].word[1],
				seq[i].word[2], seq[i].word[3],
				seq[i].word[4], seq[i].word[5]);
	पूर्ण
पूर्ण

/**
 * request_mgr_complete() - Completion will take place अगर and only अगर user
 * requested completion by cc_send_sync_request().
 *
 * @dev: Device poपूर्णांकer
 * @dx_compl_h: The completion event to संकेत
 * @dummy: unused error code
 */
अटल व्योम request_mgr_complete(काष्ठा device *dev, व्योम *dx_compl_h,
				 पूर्णांक dummy)
अणु
	काष्ठा completion *this_compl = dx_compl_h;

	complete(this_compl);
पूर्ण

अटल पूर्णांक cc_queues_status(काष्ठा cc_drvdata *drvdata,
			    काष्ठा cc_req_mgr_handle *req_mgr_h,
			    अचिन्हित पूर्णांक total_seq_len)
अणु
	अचिन्हित दीर्घ poll_queue;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	/* SW queue is checked only once as it will not
	 * be changed during the poll because the spinlock_bh
	 * is held by the thपढ़ो
	 */
	अगर (((req_mgr_h->req_queue_head + 1) & (MAX_REQUEST_QUEUE_SIZE - 1)) ==
	    req_mgr_h->req_queue_tail) अणु
		dev_err(dev, "SW FIFO is full. req_queue_head=%d sw_fifo_len=%d\n",
			req_mgr_h->req_queue_head, MAX_REQUEST_QUEUE_SIZE);
		वापस -ENOSPC;
	पूर्ण

	अगर (req_mgr_h->q_मुक्त_slots >= total_seq_len)
		वापस 0;

	/* Wait क्रम space in HW queue. Poll स्थिरant num of iterations. */
	क्रम (poll_queue = 0; poll_queue < CC_MAX_POLL_ITER ; poll_queue++) अणु
		req_mgr_h->q_मुक्त_slots =
			cc_ioपढ़ो(drvdata, CC_REG(DSCRPTR_QUEUE_CONTENT));
		अगर (req_mgr_h->q_मुक्त_slots < req_mgr_h->min_मुक्त_hw_slots)
			req_mgr_h->min_मुक्त_hw_slots = req_mgr_h->q_मुक्त_slots;

		अगर (req_mgr_h->q_मुक्त_slots >= total_seq_len) अणु
			/* If there is enough place वापस */
			वापस 0;
		पूर्ण

		dev_dbg(dev, "HW FIFO is full. q_free_slots=%d total_seq_len=%d\n",
			req_mgr_h->q_मुक्त_slots, total_seq_len);
	पूर्ण
	/* No room in the HW queue try again later */
	dev_dbg(dev, "HW FIFO full, timeout. req_queue_head=%d sw_fifo_len=%d q_free_slots=%d total_seq_len=%d\n",
		req_mgr_h->req_queue_head, MAX_REQUEST_QUEUE_SIZE,
		req_mgr_h->q_मुक्त_slots, total_seq_len);
	वापस -ENOSPC;
पूर्ण

/**
 * cc_करो_send_request() - Enqueue caller request to crypto hardware.
 * Need to be called with HW lock held and PM running
 *
 * @drvdata: Associated device driver context
 * @cc_req: The request to enqueue
 * @desc: The crypto sequence
 * @len: The crypto sequence length
 * @add_comp: If "true": add an artअगरicial करोut DMA to mark completion
 *
 */
अटल व्योम cc_करो_send_request(काष्ठा cc_drvdata *drvdata,
			       काष्ठा cc_crypto_req *cc_req,
			       काष्ठा cc_hw_desc *desc, अचिन्हित पूर्णांक len,
			       bool add_comp)
अणु
	काष्ठा cc_req_mgr_handle *req_mgr_h = drvdata->request_mgr_handle;
	अचिन्हित पूर्णांक used_sw_slots;
	अचिन्हित पूर्णांक total_seq_len = len; /*initial sequence length*/
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	used_sw_slots = ((req_mgr_h->req_queue_head -
			  req_mgr_h->req_queue_tail) &
			 (MAX_REQUEST_QUEUE_SIZE - 1));
	अगर (used_sw_slots > req_mgr_h->max_used_sw_slots)
		req_mgr_h->max_used_sw_slots = used_sw_slots;

	/* Enqueue request - must be locked with HW lock*/
	req_mgr_h->req_queue[req_mgr_h->req_queue_head] = *cc_req;
	req_mgr_h->req_queue_head = (req_mgr_h->req_queue_head + 1) &
				    (MAX_REQUEST_QUEUE_SIZE - 1);

	dev_dbg(dev, "Enqueue request head=%u\n", req_mgr_h->req_queue_head);

	/*
	 * We are about to push command to the HW via the command रेजिस्टरs
	 * that may reference host memory. We need to issue a memory barrier
	 * to make sure there are no outstanding memory ग_लिखोs
	 */
	wmb();

	/* STAT_PHASE_4: Push sequence */

	enqueue_seq(drvdata, desc, len);

	अगर (add_comp) अणु
		enqueue_seq(drvdata, &req_mgr_h->compl_desc, 1);
		total_seq_len++;
	पूर्ण

	अगर (req_mgr_h->q_मुक्त_slots < total_seq_len) अणु
		/* This situation should never occur. Maybe indicating problem
		 * with resuming घातer. Set the मुक्त slot count to 0 and hope
		 * क्रम the best.
		 */
		dev_err(dev, "HW free slot count mismatch.");
		req_mgr_h->q_मुक्त_slots = 0;
	पूर्ण अन्यथा अणु
		/* Update the मुक्त slots in HW queue */
		req_mgr_h->q_मुक्त_slots -= total_seq_len;
	पूर्ण
पूर्ण

अटल व्योम cc_enqueue_backlog(काष्ठा cc_drvdata *drvdata,
			       काष्ठा cc_bl_item *bli)
अणु
	काष्ठा cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	spin_lock_bh(&mgr->bl_lock);
	list_add_tail(&bli->list, &mgr->backlog);
	++mgr->bl_len;
	dev_dbg(dev, "+++bl len: %d\n", mgr->bl_len);
	spin_unlock_bh(&mgr->bl_lock);
	tasklet_schedule(&mgr->comptask);
पूर्ण

अटल व्योम cc_proc_backlog(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;
	काष्ठा cc_bl_item *bli;
	काष्ठा cc_crypto_req *creq;
	व्योम *req;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	पूर्णांक rc;

	spin_lock(&mgr->bl_lock);

	जबतक (mgr->bl_len) अणु
		bli = list_first_entry(&mgr->backlog, काष्ठा cc_bl_item, list);
		dev_dbg(dev, "---bl len: %d\n", mgr->bl_len);

		spin_unlock(&mgr->bl_lock);


		creq = &bli->creq;
		req = creq->user_arg;

		/*
		 * Notअगरy the request we're moving out of the backlog
		 * but only अगर we haven't करोne so alपढ़ोy.
		 */
		अगर (!bli->notअगर) अणु
			creq->user_cb(dev, req, -EINPROGRESS);
			bli->notअगर = true;
		पूर्ण

		spin_lock(&mgr->hw_lock);

		rc = cc_queues_status(drvdata, mgr, bli->len);
		अगर (rc) अणु
			/*
			 * There is still no room in the FIFO क्रम
			 * this request. Bail out. We'll वापस here
			 * on the next completion irq.
			 */
			spin_unlock(&mgr->hw_lock);
			वापस;
		पूर्ण

		cc_करो_send_request(drvdata, &bli->creq, bli->desc, bli->len,
				   false);
		spin_unlock(&mgr->hw_lock);

		/* Remove ourselves from the backlog list */
		spin_lock(&mgr->bl_lock);
		list_del(&bli->list);
		--mgr->bl_len;
		kमुक्त(bli);
	पूर्ण

	spin_unlock(&mgr->bl_lock);
पूर्ण

पूर्णांक cc_send_request(काष्ठा cc_drvdata *drvdata, काष्ठा cc_crypto_req *cc_req,
		    काष्ठा cc_hw_desc *desc, अचिन्हित पूर्णांक len,
		    काष्ठा crypto_async_request *req)
अणु
	पूर्णांक rc;
	काष्ठा cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	bool backlog_ok = req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG;
	gfp_t flags = cc_gfp_flags(req);
	काष्ठा cc_bl_item *bli;

	rc = cc_pm_get(dev);
	अगर (rc) अणु
		dev_err(dev, "cc_pm_get returned %x\n", rc);
		वापस rc;
	पूर्ण

	spin_lock_bh(&mgr->hw_lock);
	rc = cc_queues_status(drvdata, mgr, len);

#अगर_घोषित CC_DEBUG_FORCE_BACKLOG
	अगर (backlog_ok)
		rc = -ENOSPC;
#पूर्ण_अगर /* CC_DEBUG_FORCE_BACKLOG */

	अगर (rc == -ENOSPC && backlog_ok) अणु
		spin_unlock_bh(&mgr->hw_lock);

		bli = kदो_स्मृति(माप(*bli), flags);
		अगर (!bli) अणु
			cc_pm_put_suspend(dev);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(&bli->creq, cc_req, माप(*cc_req));
		स_नकल(&bli->desc, desc, len * माप(*desc));
		bli->len = len;
		bli->notअगर = false;
		cc_enqueue_backlog(drvdata, bli);
		वापस -EBUSY;
	पूर्ण

	अगर (!rc) अणु
		cc_करो_send_request(drvdata, cc_req, desc, len, false);
		rc = -EINPROGRESS;
	पूर्ण

	spin_unlock_bh(&mgr->hw_lock);
	वापस rc;
पूर्ण

पूर्णांक cc_send_sync_request(काष्ठा cc_drvdata *drvdata,
			 काष्ठा cc_crypto_req *cc_req, काष्ठा cc_hw_desc *desc,
			 अचिन्हित पूर्णांक len)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;

	init_completion(&cc_req->seq_compl);
	cc_req->user_cb = request_mgr_complete;
	cc_req->user_arg = &cc_req->seq_compl;

	rc = cc_pm_get(dev);
	अगर (rc) अणु
		dev_err(dev, "cc_pm_get returned %x\n", rc);
		वापस rc;
	पूर्ण

	जबतक (true) अणु
		spin_lock_bh(&mgr->hw_lock);
		rc = cc_queues_status(drvdata, mgr, len + 1);

		अगर (!rc)
			अवरोध;

		spin_unlock_bh(&mgr->hw_lock);
		रुको_क्रम_completion_पूर्णांकerruptible(&drvdata->hw_queue_avail);
		reinit_completion(&drvdata->hw_queue_avail);
	पूर्ण

	cc_करो_send_request(drvdata, cc_req, desc, len, true);
	spin_unlock_bh(&mgr->hw_lock);
	रुको_क्रम_completion(&cc_req->seq_compl);
	वापस 0;
पूर्ण

/**
 * send_request_init() - Enqueue caller request to crypto hardware during init
 * process.
 * Assume this function is not called in the middle of a flow,
 * since we set QUEUE_LAST_IND flag in the last descriptor.
 *
 * @drvdata: Associated device driver context
 * @desc: The crypto sequence
 * @len: The crypto sequence length
 *
 * Return:
 * Returns "0" upon success
 */
पूर्णांक send_request_init(काष्ठा cc_drvdata *drvdata, काष्ठा cc_hw_desc *desc,
		      अचिन्हित पूर्णांक len)
अणु
	काष्ठा cc_req_mgr_handle *req_mgr_h = drvdata->request_mgr_handle;
	अचिन्हित पूर्णांक total_seq_len = len; /*initial sequence length*/
	पूर्णांक rc = 0;

	/* Wait क्रम space in HW and SW FIFO. Poll क्रम as much as FIFO_TIMEOUT.
	 */
	rc = cc_queues_status(drvdata, req_mgr_h, total_seq_len);
	अगर (rc)
		वापस rc;

	set_queue_last_ind(drvdata, &desc[(len - 1)]);

	/*
	 * We are about to push command to the HW via the command रेजिस्टरs
	 * that may reference host memory. We need to issue a memory barrier
	 * to make sure there are no outstanding memory ग_लिखोs
	 */
	wmb();
	enqueue_seq(drvdata, desc, len);

	/* Update the मुक्त slots in HW queue */
	req_mgr_h->q_मुक्त_slots =
		cc_ioपढ़ो(drvdata, CC_REG(DSCRPTR_QUEUE_CONTENT));

	वापस 0;
पूर्ण

व्योम complete_request(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;

	complete(&drvdata->hw_queue_avail);
#अगर_घोषित COMP_IN_WQ
	queue_delayed_work(request_mgr_handle->workq,
			   &request_mgr_handle->compwork, 0);
#अन्यथा
	tasklet_schedule(&request_mgr_handle->comptask);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित COMP_IN_WQ
अटल व्योम comp_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cc_drvdata *drvdata =
		container_of(work, काष्ठा cc_drvdata, compwork.work);

	comp_handler((अचिन्हित दीर्घ)drvdata);
पूर्ण
#पूर्ण_अगर

अटल व्योम proc_completions(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_crypto_req *cc_req;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;
	अचिन्हित पूर्णांक *tail = &request_mgr_handle->req_queue_tail;
	अचिन्हित पूर्णांक *head = &request_mgr_handle->req_queue_head;
	पूर्णांक rc;
	u32 mask;

	जबतक (request_mgr_handle->axi_completed) अणु
		request_mgr_handle->axi_completed--;

		/* Dequeue request */
		अगर (*head == *tail) अणु
			/* We are supposed to handle a completion but our
			 * queue is empty. This is not normal. Return and
			 * hope क्रम the best.
			 */
			dev_err(dev, "Request queue is empty head == tail %u\n",
				*head);
			अवरोध;
		पूर्ण

		cc_req = &request_mgr_handle->req_queue[*tail];

		अगर (cc_req->cpp.is_cpp) अणु

			dev_dbg(dev, "CPP request completion slot: %d alg:%d\n",
				cc_req->cpp.slot, cc_req->cpp.alg);
			mask = cc_cpp_पूर्णांक_mask(cc_req->cpp.alg,
					       cc_req->cpp.slot);
			rc = (drvdata->irq & mask ? -EPERM : 0);
			dev_dbg(dev, "Got mask: %x irq: %x rc: %d\n", mask,
				drvdata->irq, rc);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "None CPP request completion\n");
			rc = 0;
		पूर्ण

		अगर (cc_req->user_cb)
			cc_req->user_cb(dev, cc_req->user_arg, rc);
		*tail = (*tail + 1) & (MAX_REQUEST_QUEUE_SIZE - 1);
		dev_dbg(dev, "Dequeue request tail=%u\n", *tail);
		dev_dbg(dev, "Request completed. axi_completed=%d\n",
			request_mgr_handle->axi_completed);
		cc_pm_put_suspend(dev);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 cc_axi_comp_count(काष्ठा cc_drvdata *drvdata)
अणु
	वापस FIELD_GET(AXIM_MON_COMP_VALUE,
			 cc_ioपढ़ो(drvdata, drvdata->axim_mon_offset));
पूर्ण

/* Deferred service handler, run as पूर्णांकerrupt-fired tasklet */
अटल व्योम comp_handler(अचिन्हित दीर्घ devarg)
अणु
	काष्ठा cc_drvdata *drvdata = (काष्ठा cc_drvdata *)devarg;
	काष्ठा cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u32 irq;

	dev_dbg(dev, "Completion handler called!\n");
	irq = (drvdata->irq & drvdata->comp_mask);

	/* To aव्योम the पूर्णांकerrupt from firing as we unmask it,
	 * we clear it now
	 */
	cc_ioग_लिखो(drvdata, CC_REG(HOST_ICR), irq);

	/* Aव्योम race with above clear: Test completion counter once more */

	request_mgr_handle->axi_completed += cc_axi_comp_count(drvdata);

	dev_dbg(dev, "AXI completion after updated: %d\n",
		request_mgr_handle->axi_completed);

	जबतक (request_mgr_handle->axi_completed) अणु
		करो अणु
			drvdata->irq |= cc_ioपढ़ो(drvdata, CC_REG(HOST_IRR));
			irq = (drvdata->irq & drvdata->comp_mask);
			proc_completions(drvdata);

			/* At this poपूर्णांक (after proc_completions()),
			 * request_mgr_handle->axi_completed is 0.
			 */
			request_mgr_handle->axi_completed +=
						cc_axi_comp_count(drvdata);
		पूर्ण जबतक (request_mgr_handle->axi_completed > 0);

		cc_ioग_लिखो(drvdata, CC_REG(HOST_ICR), irq);

		request_mgr_handle->axi_completed += cc_axi_comp_count(drvdata);
	पूर्ण

	/* after verअगरying that there is nothing to करो,
	 * unmask AXI completion पूर्णांकerrupt
	 */
	cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR),
		   cc_ioपढ़ो(drvdata, CC_REG(HOST_IMR)) & ~drvdata->comp_mask);

	cc_proc_backlog(drvdata);
	dev_dbg(dev, "Comp. handler done.\n");
पूर्ण
