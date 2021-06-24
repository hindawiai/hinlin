<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Setup and helper functions to access QDIO.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/lockdep.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_qdio.h"

अटल bool enable_multibuffer = true;
module_param_named(datarouter, enable_multibuffer, bool, 0400);
MODULE_PARM_DESC(datarouter, "Enable hardware data router support (default on)");

#घोषणा ZFCP_QDIO_REQUEST_RESCAN_MSECS	(MSEC_PER_SEC * 10)
#घोषणा ZFCP_QDIO_REQUEST_SCAN_MSECS	MSEC_PER_SEC

अटल व्योम zfcp_qdio_handler_error(काष्ठा zfcp_qdio *qdio, अक्षर *dbftag,
				    अचिन्हित पूर्णांक qdio_err)
अणु
	काष्ठा zfcp_adapter *adapter = qdio->adapter;

	dev_warn(&adapter->ccw_device->dev, "A QDIO problem occurred\n");

	अगर (qdio_err & QDIO_ERROR_SLSB_STATE) अणु
		zfcp_qdio_siosl(adapter);
		zfcp_erp_adapter_shutकरोwn(adapter, 0, dbftag);
		वापस;
	पूर्ण
	zfcp_erp_adapter_reखोलो(adapter,
				ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
				ZFCP_STATUS_COMMON_ERP_FAILED, dbftag);
पूर्ण

अटल व्योम zfcp_qdio_zero_sbals(काष्ठा qdio_buffer *sbal[], पूर्णांक first, पूर्णांक cnt)
अणु
	पूर्णांक i, sbal_idx;

	क्रम (i = first; i < first + cnt; i++) अणु
		sbal_idx = i % QDIO_MAX_BUFFERS_PER_Q;
		स_रखो(sbal[sbal_idx], 0, माप(काष्ठा qdio_buffer));
	पूर्ण
पूर्ण

/* this needs to be called prior to updating the queue fill level */
अटल अंतरभूत व्योम zfcp_qdio_account(काष्ठा zfcp_qdio *qdio)
अणु
	अचिन्हित दीर्घ दीर्घ now, span;
	पूर्णांक used;

	now = get_tod_घड़ी_monotonic();
	span = (now - qdio->req_q_समय) >> 12;
	used = QDIO_MAX_BUFFERS_PER_Q - atomic_पढ़ो(&qdio->req_q_मुक्त);
	qdio->req_q_util += used * span;
	qdio->req_q_समय = now;
पूर्ण

अटल व्योम zfcp_qdio_पूर्णांक_req(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक qdio_err,
			      पूर्णांक queue_no, पूर्णांक idx, पूर्णांक count,
			      अचिन्हित दीर्घ parm)
अणु
	काष्ठा zfcp_qdio *qdio = (काष्ठा zfcp_qdio *) parm;

	अगर (unlikely(qdio_err)) अणु
		zfcp_qdio_handler_error(qdio, "qdireq1", qdio_err);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम zfcp_qdio_request_tasklet(काष्ठा tasklet_काष्ठा *tasklet)
अणु
	काष्ठा zfcp_qdio *qdio = from_tasklet(qdio, tasklet, request_tasklet);
	काष्ठा ccw_device *cdev = qdio->adapter->ccw_device;
	अचिन्हित पूर्णांक start, error;
	पूर्णांक completed;

	completed = qdio_inspect_queue(cdev, 0, false, &start, &error);
	अगर (completed > 0) अणु
		अगर (error) अणु
			zfcp_qdio_handler_error(qdio, "qdreqt1", error);
		पूर्ण अन्यथा अणु
			/* cleanup all SBALs being program-owned now */
			zfcp_qdio_zero_sbals(qdio->req_q, start, completed);

			spin_lock_irq(&qdio->stat_lock);
			zfcp_qdio_account(qdio);
			spin_unlock_irq(&qdio->stat_lock);
			atomic_add(completed, &qdio->req_q_मुक्त);
			wake_up(&qdio->req_q_wq);
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&qdio->req_q_मुक्त) < QDIO_MAX_BUFFERS_PER_Q)
		समयr_reduce(&qdio->request_समयr,
			     jअगरfies + msecs_to_jअगरfies(ZFCP_QDIO_REQUEST_RESCAN_MSECS));
पूर्ण

अटल व्योम zfcp_qdio_request_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा zfcp_qdio *qdio = from_समयr(qdio, समयr, request_समयr);

	tasklet_schedule(&qdio->request_tasklet);
पूर्ण

अटल व्योम zfcp_qdio_पूर्णांक_resp(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक qdio_err,
			       पूर्णांक queue_no, पूर्णांक idx, पूर्णांक count,
			       अचिन्हित दीर्घ parm)
अणु
	काष्ठा zfcp_qdio *qdio = (काष्ठा zfcp_qdio *) parm;
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	पूर्णांक sbal_no, sbal_idx;

	अगर (unlikely(qdio_err)) अणु
		अगर (zfcp_adapter_multi_buffer_active(adapter)) अणु
			व्योम *pl[ZFCP_QDIO_MAX_SBALS_PER_REQ + 1];
			काष्ठा qdio_buffer_element *sbale;
			u64 req_id;
			u8 scount;

			स_रखो(pl, 0,
			       ZFCP_QDIO_MAX_SBALS_PER_REQ * माप(व्योम *));
			sbale = qdio->res_q[idx]->element;
			req_id = sbale->addr;
			scount = min(sbale->scount + 1,
				     ZFCP_QDIO_MAX_SBALS_PER_REQ + 1);
				     /* incl. संकेतing SBAL */

			क्रम (sbal_no = 0; sbal_no < scount; sbal_no++) अणु
				sbal_idx = (idx + sbal_no) %
					QDIO_MAX_BUFFERS_PER_Q;
				pl[sbal_no] = qdio->res_q[sbal_idx];
			पूर्ण
			zfcp_dbf_hba_def_err(adapter, req_id, scount, pl);
		पूर्ण
		zfcp_qdio_handler_error(qdio, "qdires1", qdio_err);
		वापस;
	पूर्ण

	/*
	 * go through all SBALs from input queue currently
	 * वापसed by QDIO layer
	 */
	क्रम (sbal_no = 0; sbal_no < count; sbal_no++) अणु
		sbal_idx = (idx + sbal_no) % QDIO_MAX_BUFFERS_PER_Q;
		/* go through all SBALEs of SBAL */
		zfcp_fsf_reqid_check(qdio, sbal_idx);
	पूर्ण

	/*
	 * put SBALs back to response queue
	 */
	अगर (करो_QDIO(cdev, QDIO_FLAG_SYNC_INPUT, 0, idx, count, शून्य))
		zfcp_erp_adapter_reखोलो(qdio->adapter, 0, "qdires2");
पूर्ण

अटल व्योम zfcp_qdio_irq_tasklet(काष्ठा tasklet_काष्ठा *tasklet)
अणु
	काष्ठा zfcp_qdio *qdio = from_tasklet(qdio, tasklet, irq_tasklet);
	काष्ठा ccw_device *cdev = qdio->adapter->ccw_device;
	अचिन्हित पूर्णांक start, error;
	पूर्णांक completed;

	अगर (atomic_पढ़ो(&qdio->req_q_मुक्त) < QDIO_MAX_BUFFERS_PER_Q)
		tasklet_schedule(&qdio->request_tasklet);

	/* Check the Response Queue: */
	completed = qdio_inspect_queue(cdev, 0, true, &start, &error);
	अगर (completed < 0)
		वापस;
	अगर (completed > 0)
		zfcp_qdio_पूर्णांक_resp(cdev, error, 0, start, completed,
				   (अचिन्हित दीर्घ) qdio);

	अगर (qdio_start_irq(cdev))
		/* More work pending: */
		tasklet_schedule(&qdio->irq_tasklet);
पूर्ण

अटल व्योम zfcp_qdio_poll(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ data)
अणु
	काष्ठा zfcp_qdio *qdio = (काष्ठा zfcp_qdio *) data;

	tasklet_schedule(&qdio->irq_tasklet);
पूर्ण

अटल काष्ठा qdio_buffer_element *
zfcp_qdio_sbal_chain(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	काष्ठा qdio_buffer_element *sbale;

	/* set last entry flag in current SBALE of current SBAL */
	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->eflags |= SBAL_EFLAGS_LAST_ENTRY;

	/* करोn't exceed last allowed SBAL */
	अगर (q_req->sbal_last == q_req->sbal_limit)
		वापस शून्य;

	/* set chaining flag in first SBALE of current SBAL */
	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->sflags |= SBAL_SFLAGS0_MORE_SBALS;

	/* calculate index of next SBAL */
	q_req->sbal_last++;
	q_req->sbal_last %= QDIO_MAX_BUFFERS_PER_Q;

	/* keep this requests number of SBALs up-to-date */
	q_req->sbal_number++;
	BUG_ON(q_req->sbal_number > ZFCP_QDIO_MAX_SBALS_PER_REQ);

	/* start at first SBALE of new SBAL */
	q_req->sbale_curr = 0;

	/* set storage-block type क्रम new SBAL */
	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->sflags |= q_req->sbtype;

	वापस sbale;
पूर्ण

अटल काष्ठा qdio_buffer_element *
zfcp_qdio_sbale_next(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	अगर (q_req->sbale_curr == qdio->max_sbale_per_sbal - 1)
		वापस zfcp_qdio_sbal_chain(qdio, q_req);
	q_req->sbale_curr++;
	वापस zfcp_qdio_sbale_curr(qdio, q_req);
पूर्ण

/**
 * zfcp_qdio_sbals_from_sg - fill SBALs from scatter-gather list
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_qdio_req
 * @sg: scatter-gather list
 * Returns: zero or -EINVAL on error
 */
पूर्णांक zfcp_qdio_sbals_from_sg(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req,
			    काष्ठा scatterlist *sg)
अणु
	काष्ठा qdio_buffer_element *sbale;

	/* set storage-block type क्रम this request */
	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->sflags |= q_req->sbtype;

	क्रम (; sg; sg = sg_next(sg)) अणु
		sbale = zfcp_qdio_sbale_next(qdio, q_req);
		अगर (!sbale) अणु
			atomic_inc(&qdio->req_q_full);
			zfcp_qdio_zero_sbals(qdio->req_q, q_req->sbal_first,
					     q_req->sbal_number);
			वापस -EINVAL;
		पूर्ण
		sbale->addr = sg_phys(sg);
		sbale->length = sg->length;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zfcp_qdio_sbal_check(काष्ठा zfcp_qdio *qdio)
अणु
	अगर (atomic_पढ़ो(&qdio->req_q_मुक्त) ||
	    !(atomic_पढ़ो(&qdio->adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * zfcp_qdio_sbal_get - get मुक्त sbal in request queue, रुको अगर necessary
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 *
 * The req_q_lock must be held by the caller of this function, and
 * this function may only be called from process context; it will
 * sleep when रुकोing क्रम a मुक्त sbal.
 *
 * Returns: 0 on success, -EIO अगर there is no मुक्त sbal after रुकोing.
 */
पूर्णांक zfcp_qdio_sbal_get(काष्ठा zfcp_qdio *qdio)
अणु
	दीर्घ ret;

	ret = रुको_event_पूर्णांकerruptible_lock_irq_समयout(qdio->req_q_wq,
		       zfcp_qdio_sbal_check(qdio), qdio->req_q_lock, 5 * HZ);

	अगर (!(atomic_पढ़ो(&qdio->adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		वापस -EIO;

	अगर (ret > 0)
		वापस 0;

	अगर (!ret) अणु
		atomic_inc(&qdio->req_q_full);
		/* assume hanging outbound queue, try queue recovery */
		zfcp_erp_adapter_reखोलो(qdio->adapter, 0, "qdsbg_1");
	पूर्ण

	वापस -EIO;
पूर्ण

/**
 * zfcp_qdio_send - send req to QDIO
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_qdio_req
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_qdio_send(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	पूर्णांक retval;
	u8 sbal_number = q_req->sbal_number;

	/*
	 * This should actually be a spin_lock_bh(stat_lock), to protect against
	 * Request Queue completion processing in tasklet context.
	 * But we can't करो so (and are safe), as we always get called with IRQs
	 * disabled by spin_lock_irq[save](req_q_lock).
	 */
	lockdep_निश्चित_irqs_disabled();
	spin_lock(&qdio->stat_lock);
	zfcp_qdio_account(qdio);
	spin_unlock(&qdio->stat_lock);

	atomic_sub(sbal_number, &qdio->req_q_मुक्त);

	retval = करो_QDIO(qdio->adapter->ccw_device, QDIO_FLAG_SYNC_OUTPUT, 0,
			 q_req->sbal_first, sbal_number, शून्य);

	अगर (unlikely(retval)) अणु
		/* Failed to submit the IO, roll back our modअगरications. */
		atomic_add(sbal_number, &qdio->req_q_मुक्त);
		zfcp_qdio_zero_sbals(qdio->req_q, q_req->sbal_first,
				     sbal_number);
		वापस retval;
	पूर्ण

	अगर (atomic_पढ़ो(&qdio->req_q_मुक्त) <= 2 * ZFCP_QDIO_MAX_SBALS_PER_REQ)
		tasklet_schedule(&qdio->request_tasklet);
	अन्यथा
		समयr_reduce(&qdio->request_समयr,
			     jअगरfies + msecs_to_jअगरfies(ZFCP_QDIO_REQUEST_SCAN_MSECS));

	/* account क्रम transferred buffers */
	qdio->req_q_idx += sbal_number;
	qdio->req_q_idx %= QDIO_MAX_BUFFERS_PER_Q;

	वापस 0;
पूर्ण

/**
 * zfcp_qdio_allocate - allocate queue memory and initialize QDIO data
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * Returns: -ENOMEM on memory allocation error or वापस value from
 *          qdio_allocate
 */
अटल पूर्णांक zfcp_qdio_allocate(काष्ठा zfcp_qdio *qdio)
अणु
	पूर्णांक ret;

	ret = qdio_alloc_buffers(qdio->req_q, QDIO_MAX_BUFFERS_PER_Q);
	अगर (ret)
		वापस -ENOMEM;

	ret = qdio_alloc_buffers(qdio->res_q, QDIO_MAX_BUFFERS_PER_Q);
	अगर (ret)
		जाओ मुक्त_req_q;

	init_रुकोqueue_head(&qdio->req_q_wq);

	ret = qdio_allocate(qdio->adapter->ccw_device, 1, 1);
	अगर (ret)
		जाओ मुक्त_res_q;

	वापस 0;

मुक्त_res_q:
	qdio_मुक्त_buffers(qdio->res_q, QDIO_MAX_BUFFERS_PER_Q);
मुक्त_req_q:
	qdio_मुक्त_buffers(qdio->req_q, QDIO_MAX_BUFFERS_PER_Q);
	वापस ret;
पूर्ण

/**
 * zfcp_बंद_qdio - बंद qdio queues क्रम an adapter
 * @qdio: poपूर्णांकer to काष्ठाure zfcp_qdio
 */
व्योम zfcp_qdio_बंद(काष्ठा zfcp_qdio *qdio)
अणु
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	पूर्णांक idx, count;

	अगर (!(atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		वापस;

	/* clear QDIOUP flag, thus करो_QDIO is not called during qdio_shutकरोwn */
	spin_lock_irq(&qdio->req_q_lock);
	atomic_andnot(ZFCP_STATUS_ADAPTER_QDIOUP, &adapter->status);
	spin_unlock_irq(&qdio->req_q_lock);

	wake_up(&qdio->req_q_wq);

	tasklet_disable(&qdio->irq_tasklet);
	tasklet_disable(&qdio->request_tasklet);
	del_समयr_sync(&qdio->request_समयr);
	qdio_stop_irq(adapter->ccw_device);
	qdio_shutकरोwn(adapter->ccw_device, QDIO_FLAG_CLEANUP_USING_CLEAR);

	/* cleanup used outbound sbals */
	count = atomic_पढ़ो(&qdio->req_q_मुक्त);
	अगर (count < QDIO_MAX_BUFFERS_PER_Q) अणु
		idx = (qdio->req_q_idx + count) % QDIO_MAX_BUFFERS_PER_Q;
		count = QDIO_MAX_BUFFERS_PER_Q - count;
		zfcp_qdio_zero_sbals(qdio->req_q, idx, count);
	पूर्ण
	qdio->req_q_idx = 0;
	atomic_set(&qdio->req_q_मुक्त, 0);
पूर्ण

व्योम zfcp_qdio_shost_update(काष्ठा zfcp_adapter *स्थिर adapter,
			    स्थिर काष्ठा zfcp_qdio *स्थिर qdio)
अणु
	काष्ठा Scsi_Host *स्थिर shost = adapter->scsi_host;

	अगर (shost == शून्य)
		वापस;

	shost->sg_tablesize = qdio->max_sbale_per_req;
	shost->max_sectors = qdio->max_sbale_per_req * 8;
पूर्ण

/**
 * zfcp_qdio_खोलो - prepare and initialize response queue
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * Returns: 0 on success, otherwise -EIO
 */
पूर्णांक zfcp_qdio_खोलो(काष्ठा zfcp_qdio *qdio)
अणु
	काष्ठा qdio_buffer **input_sbals[1] = अणुqdio->res_qपूर्ण;
	काष्ठा qdio_buffer **output_sbals[1] = अणुqdio->req_qपूर्ण;
	काष्ठा qdio_buffer_element *sbale;
	काष्ठा qdio_initialize init_data = अणु0पूर्ण;
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	काष्ठा ccw_device *cdev = adapter->ccw_device;
	काष्ठा qdio_ssqd_desc ssqd;
	पूर्णांक cc;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP)
		वापस -EIO;

	atomic_andnot(ZFCP_STATUS_ADAPTER_SIOSL_ISSUED,
			  &qdio->adapter->status);

	init_data.q_क्रमmat = QDIO_ZFCP_QFMT;
	init_data.qib_rflags = QIB_RFLAGS_ENABLE_DATA_DIV;
	अगर (enable_multibuffer)
		init_data.qdr_ac |= QDR_AC_MULTI_BUFFER_ENABLE;
	init_data.no_input_qs = 1;
	init_data.no_output_qs = 1;
	init_data.input_handler = zfcp_qdio_पूर्णांक_resp;
	init_data.output_handler = zfcp_qdio_पूर्णांक_req;
	init_data.irq_poll = zfcp_qdio_poll;
	init_data.पूर्णांक_parm = (अचिन्हित दीर्घ) qdio;
	init_data.input_sbal_addr_array = input_sbals;
	init_data.output_sbal_addr_array = output_sbals;

	अगर (qdio_establish(cdev, &init_data))
		जाओ failed_establish;

	अगर (qdio_get_ssqd_desc(cdev, &ssqd))
		जाओ failed_qdio;

	अगर (ssqd.qdioac2 & CHSC_AC2_DATA_DIV_ENABLED)
		atomic_or(ZFCP_STATUS_ADAPTER_DATA_DIV_ENABLED,
				&qdio->adapter->status);

	अगर (ssqd.qdioac2 & CHSC_AC2_MULTI_BUFFER_ENABLED) अणु
		atomic_or(ZFCP_STATUS_ADAPTER_MB_ACT, &adapter->status);
		qdio->max_sbale_per_sbal = QDIO_MAX_ELEMENTS_PER_BUFFER;
	पूर्ण अन्यथा अणु
		atomic_andnot(ZFCP_STATUS_ADAPTER_MB_ACT, &adapter->status);
		qdio->max_sbale_per_sbal = QDIO_MAX_ELEMENTS_PER_BUFFER - 1;
	पूर्ण

	qdio->max_sbale_per_req =
		ZFCP_QDIO_MAX_SBALS_PER_REQ * qdio->max_sbale_per_sbal
		- 2;
	अगर (qdio_activate(cdev))
		जाओ failed_qdio;

	क्रम (cc = 0; cc < QDIO_MAX_BUFFERS_PER_Q; cc++) अणु
		sbale = &(qdio->res_q[cc]->element[0]);
		sbale->length = 0;
		sbale->eflags = SBAL_EFLAGS_LAST_ENTRY;
		sbale->sflags = 0;
		sbale->addr = 0;
	पूर्ण

	अगर (करो_QDIO(cdev, QDIO_FLAG_SYNC_INPUT, 0, 0, QDIO_MAX_BUFFERS_PER_Q,
		    शून्य))
		जाओ failed_qdio;

	/* set index of first available SBALS / number of available SBALS */
	qdio->req_q_idx = 0;
	atomic_set(&qdio->req_q_मुक्त, QDIO_MAX_BUFFERS_PER_Q);
	atomic_or(ZFCP_STATUS_ADAPTER_QDIOUP, &qdio->adapter->status);

	/* Enable processing क्रम Request Queue completions: */
	tasklet_enable(&qdio->request_tasklet);
	/* Enable processing क्रम QDIO पूर्णांकerrupts: */
	tasklet_enable(&qdio->irq_tasklet);
	/* This results in a qdio_start_irq(): */
	tasklet_schedule(&qdio->irq_tasklet);

	zfcp_qdio_shost_update(adapter, qdio);

	वापस 0;

failed_qdio:
	qdio_shutकरोwn(cdev, QDIO_FLAG_CLEANUP_USING_CLEAR);
failed_establish:
	dev_err(&cdev->dev,
		"Setting up the QDIO connection to the FCP adapter failed\n");
	वापस -EIO;
पूर्ण

व्योम zfcp_qdio_destroy(काष्ठा zfcp_qdio *qdio)
अणु
	अगर (!qdio)
		वापस;

	tasklet_समाप्त(&qdio->irq_tasklet);
	tasklet_समाप्त(&qdio->request_tasklet);

	अगर (qdio->adapter->ccw_device)
		qdio_मुक्त(qdio->adapter->ccw_device);

	qdio_मुक्त_buffers(qdio->req_q, QDIO_MAX_BUFFERS_PER_Q);
	qdio_मुक्त_buffers(qdio->res_q, QDIO_MAX_BUFFERS_PER_Q);
	kमुक्त(qdio);
पूर्ण

पूर्णांक zfcp_qdio_setup(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_qdio *qdio;

	qdio = kzalloc(माप(काष्ठा zfcp_qdio), GFP_KERNEL);
	अगर (!qdio)
		वापस -ENOMEM;

	qdio->adapter = adapter;

	अगर (zfcp_qdio_allocate(qdio)) अणु
		kमुक्त(qdio);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&qdio->req_q_lock);
	spin_lock_init(&qdio->stat_lock);
	समयr_setup(&qdio->request_समयr, zfcp_qdio_request_समयr, 0);
	tasklet_setup(&qdio->irq_tasklet, zfcp_qdio_irq_tasklet);
	tasklet_setup(&qdio->request_tasklet, zfcp_qdio_request_tasklet);
	tasklet_disable(&qdio->irq_tasklet);
	tasklet_disable(&qdio->request_tasklet);

	adapter->qdio = qdio;
	वापस 0;
पूर्ण

/**
 * zfcp_qdio_siosl - Trigger logging in FCP channel
 * @adapter: The zfcp_adapter where to trigger logging
 *
 * Call the cio siosl function to trigger hardware logging.  This
 * wrapper function sets a flag to ensure hardware logging is only
 * triggered once beक्रमe going through qdio shutकरोwn.
 *
 * The triggers are always run from qdio tasklet context, so no
 * additional synchronization is necessary.
 */
व्योम zfcp_qdio_siosl(काष्ठा zfcp_adapter *adapter)
अणु
	पूर्णांक rc;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_SIOSL_ISSUED)
		वापस;

	rc = ccw_device_siosl(adapter->ccw_device);
	अगर (!rc)
		atomic_or(ZFCP_STATUS_ADAPTER_SIOSL_ISSUED,
				&adapter->status);
पूर्ण
