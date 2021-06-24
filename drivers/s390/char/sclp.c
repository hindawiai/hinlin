<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * core function to access sclp पूर्णांकerface
 *
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/reboot.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/irq.h>

#समावेश "sclp.h"

#घोषणा SCLP_HEADER		"sclp: "

/* Lock to protect पूर्णांकernal data consistency. */
अटल DEFINE_SPINLOCK(sclp_lock);

/* Mask of events that we can send to the sclp पूर्णांकerface. */
अटल sccb_mask_t sclp_receive_mask;

/* Mask of events that we can receive from the sclp पूर्णांकerface. */
अटल sccb_mask_t sclp_send_mask;

/* List of रेजिस्टरed event listeners and senders. */
अटल LIST_HEAD(sclp_reg_list);

/* List of queued requests. */
अटल LIST_HEAD(sclp_req_queue);

/* Data क्रम पढ़ो and and init requests. */
अटल काष्ठा sclp_req sclp_पढ़ो_req;
अटल काष्ठा sclp_req sclp_init_req;
अटल व्योम *sclp_पढ़ो_sccb;
अटल काष्ठा init_sccb *sclp_init_sccb;

/* Suspend request */
अटल DECLARE_COMPLETION(sclp_request_queue_flushed);

/* Number of console pages to allocate, used by sclp_con.c and sclp_vt220.c */
पूर्णांक sclp_console_pages = SCLP_CONSOLE_PAGES;
/* Flag to indicate अगर buffer pages are dropped on buffer full condition */
पूर्णांक sclp_console_drop = 1;
/* Number of बार the console dropped buffer pages */
अचिन्हित दीर्घ sclp_console_full;

अटल व्योम sclp_suspend_req_cb(काष्ठा sclp_req *req, व्योम *data)
अणु
	complete(&sclp_request_queue_flushed);
पूर्ण

अटल पूर्णांक __init sclp_setup_console_pages(अक्षर *str)
अणु
	पूर्णांक pages, rc;

	rc = kstrtoपूर्णांक(str, 0, &pages);
	अगर (!rc && pages >= SCLP_CONSOLE_PAGES)
		sclp_console_pages = pages;
	वापस 1;
पूर्ण

__setup("sclp_con_pages=", sclp_setup_console_pages);

अटल पूर्णांक __init sclp_setup_console_drop(अक्षर *str)
अणु
	पूर्णांक drop, rc;

	rc = kstrtoपूर्णांक(str, 0, &drop);
	अगर (!rc)
		sclp_console_drop = drop;
	वापस 1;
पूर्ण

__setup("sclp_con_drop=", sclp_setup_console_drop);

अटल काष्ठा sclp_req sclp_suspend_req;

/* Timer क्रम request retries. */
अटल काष्ठा समयr_list sclp_request_समयr;

/* Timer क्रम queued requests. */
अटल काष्ठा समयr_list sclp_queue_समयr;

/* Internal state: is a request active at the sclp? */
अटल अस्थिर क्रमागत sclp_running_state_t अणु
	sclp_running_state_idle,
	sclp_running_state_running,
	sclp_running_state_reset_pending
पूर्ण sclp_running_state = sclp_running_state_idle;

/* Internal state: is a पढ़ो request pending? */
अटल अस्थिर क्रमागत sclp_पढ़ोing_state_t अणु
	sclp_पढ़ोing_state_idle,
	sclp_पढ़ोing_state_पढ़ोing
पूर्ण sclp_पढ़ोing_state = sclp_पढ़ोing_state_idle;

/* Internal state: is the driver currently serving requests? */
अटल अस्थिर क्रमागत sclp_activation_state_t अणु
	sclp_activation_state_active,
	sclp_activation_state_deactivating,
	sclp_activation_state_inactive,
	sclp_activation_state_activating
पूर्ण sclp_activation_state = sclp_activation_state_active;

/* Internal state: is an init mask request pending? */
अटल अस्थिर क्रमागत sclp_mask_state_t अणु
	sclp_mask_state_idle,
	sclp_mask_state_initializing
पूर्ण sclp_mask_state = sclp_mask_state_idle;

/* Internal state: is the driver suspended? */
अटल क्रमागत sclp_suspend_state_t अणु
	sclp_suspend_state_running,
	sclp_suspend_state_suspended,
पूर्ण sclp_suspend_state = sclp_suspend_state_running;

/* Maximum retry counts */
#घोषणा SCLP_INIT_RETRY		3
#घोषणा SCLP_MASK_RETRY		3

/* Timeout पूर्णांकervals in seconds.*/
#घोषणा SCLP_BUSY_INTERVAL	10
#घोषणा SCLP_RETRY_INTERVAL	30

अटल व्योम sclp_request_समयout(bool क्रमce_restart);
अटल व्योम sclp_process_queue(व्योम);
अटल व्योम __sclp_make_पढ़ो_req(व्योम);
अटल पूर्णांक sclp_init_mask(पूर्णांक calculate);
अटल पूर्णांक sclp_init(व्योम);

अटल व्योम
__sclp_queue_पढ़ो_req(व्योम)
अणु
	अगर (sclp_पढ़ोing_state == sclp_पढ़ोing_state_idle) अणु
		sclp_पढ़ोing_state = sclp_पढ़ोing_state_पढ़ोing;
		__sclp_make_पढ़ो_req();
		/* Add request to head of queue */
		list_add(&sclp_पढ़ो_req.list, &sclp_req_queue);
	पूर्ण
पूर्ण

/* Set up request retry समयr. Called जबतक sclp_lock is locked. */
अटल अंतरभूत व्योम
__sclp_set_request_समयr(अचिन्हित दीर्घ समय, व्योम (*cb)(काष्ठा समयr_list *))
अणु
	del_समयr(&sclp_request_समयr);
	sclp_request_समयr.function = cb;
	sclp_request_समयr.expires = jअगरfies + समय;
	add_समयr(&sclp_request_समयr);
पूर्ण

अटल व्योम sclp_request_समयout_restart(काष्ठा समयr_list *unused)
अणु
	sclp_request_समयout(true);
पूर्ण

अटल व्योम sclp_request_समयout_normal(काष्ठा समयr_list *unused)
अणु
	sclp_request_समयout(false);
पूर्ण

/* Request समयout handler. Restart the request queue. If क्रमce_restart,
 * क्रमce restart of running request. */
अटल व्योम sclp_request_समयout(bool क्रमce_restart)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_lock, flags);
	अगर (क्रमce_restart) अणु
		अगर (sclp_running_state == sclp_running_state_running) अणु
			/* Break running state and queue NOP पढ़ो event request
			 * to get a defined पूर्णांकerface state. */
			__sclp_queue_पढ़ो_req();
			sclp_running_state = sclp_running_state_idle;
		पूर्ण
	पूर्ण अन्यथा अणु
		__sclp_set_request_समयr(SCLP_BUSY_INTERVAL * HZ,
					 sclp_request_समयout_normal);
	पूर्ण
	spin_unlock_irqrestore(&sclp_lock, flags);
	sclp_process_queue();
पूर्ण

/*
 * Returns the expire value in jअगरfies of the next pending request समयout,
 * अगर any. Needs to be called with sclp_lock.
 */
अटल अचिन्हित दीर्घ __sclp_req_queue_find_next_समयout(व्योम)
अणु
	अचिन्हित दीर्घ expires_next = 0;
	काष्ठा sclp_req *req;

	list_क्रम_each_entry(req, &sclp_req_queue, list) अणु
		अगर (!req->queue_expires)
			जारी;
		अगर (!expires_next ||
		   (समय_beक्रमe(req->queue_expires, expires_next)))
				expires_next = req->queue_expires;
	पूर्ण
	वापस expires_next;
पूर्ण

/*
 * Returns expired request, अगर any, and हटाओs it from the list.
 */
अटल काष्ठा sclp_req *__sclp_req_queue_हटाओ_expired_req(व्योम)
अणु
	अचिन्हित दीर्घ flags, now;
	काष्ठा sclp_req *req;

	spin_lock_irqsave(&sclp_lock, flags);
	now = jअगरfies;
	/* Don't need list_क्रम_each_safe because we अवरोध out after list_del */
	list_क्रम_each_entry(req, &sclp_req_queue, list) अणु
		अगर (!req->queue_expires)
			जारी;
		अगर (समय_beक्रमe_eq(req->queue_expires, now)) अणु
			अगर (req->status == SCLP_REQ_QUEUED) अणु
				req->status = SCLP_REQ_QUEUED_TIMEOUT;
				list_del(&req->list);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	req = शून्य;
out:
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस req;
पूर्ण

/*
 * Timeout handler क्रम queued requests. Removes request from list and
 * invokes callback. This समयr can be set per request in situations where
 * रुकोing too दीर्घ would be harmful to the प्रणाली, e.g. during SE reboot.
 */
अटल व्योम sclp_req_queue_समयout(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags, expires_next;
	काष्ठा sclp_req *req;

	करो अणु
		req = __sclp_req_queue_हटाओ_expired_req();
		अगर (req && req->callback)
			req->callback(req, req->callback_data);
	पूर्ण जबतक (req);

	spin_lock_irqsave(&sclp_lock, flags);
	expires_next = __sclp_req_queue_find_next_समयout();
	अगर (expires_next)
		mod_समयr(&sclp_queue_समयr, expires_next);
	spin_unlock_irqrestore(&sclp_lock, flags);
पूर्ण

/* Try to start a request. Return zero अगर the request was successfully
 * started or अगर it will be started at a later समय. Return non-zero otherwise.
 * Called जबतक sclp_lock is locked. */
अटल पूर्णांक
__sclp_start_request(काष्ठा sclp_req *req)
अणु
	पूर्णांक rc;

	अगर (sclp_running_state != sclp_running_state_idle)
		वापस 0;
	del_समयr(&sclp_request_समयr);
	rc = sclp_service_call(req->command, req->sccb);
	req->start_count++;

	अगर (rc == 0) अणु
		/* Successfully started request */
		req->status = SCLP_REQ_RUNNING;
		sclp_running_state = sclp_running_state_running;
		__sclp_set_request_समयr(SCLP_RETRY_INTERVAL * HZ,
					 sclp_request_समयout_restart);
		वापस 0;
	पूर्ण अन्यथा अगर (rc == -EBUSY) अणु
		/* Try again later */
		__sclp_set_request_समयr(SCLP_BUSY_INTERVAL * HZ,
					 sclp_request_समयout_normal);
		वापस 0;
	पूर्ण
	/* Request failed */
	req->status = SCLP_REQ_FAILED;
	वापस rc;
पूर्ण

/* Try to start queued requests. */
अटल व्योम
sclp_process_queue(व्योम)
अणु
	काष्ठा sclp_req *req;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_lock, flags);
	अगर (sclp_running_state != sclp_running_state_idle) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस;
	पूर्ण
	del_समयr(&sclp_request_समयr);
	जबतक (!list_empty(&sclp_req_queue)) अणु
		req = list_entry(sclp_req_queue.next, काष्ठा sclp_req, list);
		अगर (!req->sccb)
			जाओ करो_post;
		rc = __sclp_start_request(req);
		अगर (rc == 0)
			अवरोध;
		/* Request failed */
		अगर (req->start_count > 1) अणु
			/* Cannot पात alपढ़ोy submitted request - could still
			 * be active at the SCLP */
			__sclp_set_request_समयr(SCLP_BUSY_INTERVAL * HZ,
						 sclp_request_समयout_normal);
			अवरोध;
		पूर्ण
करो_post:
		/* Post-processing क्रम पातed request */
		list_del(&req->list);
		अगर (req->callback) अणु
			spin_unlock_irqrestore(&sclp_lock, flags);
			req->callback(req, req->callback_data);
			spin_lock_irqsave(&sclp_lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sclp_lock, flags);
पूर्ण

अटल पूर्णांक __sclp_can_add_request(काष्ठा sclp_req *req)
अणु
	अगर (req == &sclp_suspend_req || req == &sclp_init_req)
		वापस 1;
	अगर (sclp_suspend_state != sclp_suspend_state_running)
		वापस 0;
	अगर (sclp_init_state != sclp_init_state_initialized)
		वापस 0;
	अगर (sclp_activation_state != sclp_activation_state_active)
		वापस 0;
	वापस 1;
पूर्ण

/* Queue a new request. Return zero on success, non-zero otherwise. */
पूर्णांक
sclp_add_request(काष्ठा sclp_req *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_lock, flags);
	अगर (!__sclp_can_add_request(req)) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EIO;
	पूर्ण
	req->status = SCLP_REQ_QUEUED;
	req->start_count = 0;
	list_add_tail(&req->list, &sclp_req_queue);
	rc = 0;
	अगर (req->queue_समयout) अणु
		req->queue_expires = jअगरfies + req->queue_समयout * HZ;
		अगर (!समयr_pending(&sclp_queue_समयr) ||
		    समय_after(sclp_queue_समयr.expires, req->queue_expires))
			mod_समयr(&sclp_queue_समयr, req->queue_expires);
	पूर्ण अन्यथा
		req->queue_expires = 0;
	/* Start अगर request is first in list */
	अगर (sclp_running_state == sclp_running_state_idle &&
	    req->list.prev == &sclp_req_queue) अणु
		अगर (!req->sccb) अणु
			list_del(&req->list);
			rc = -ENODATA;
			जाओ out;
		पूर्ण
		rc = __sclp_start_request(req);
		अगर (rc)
			list_del(&req->list);
	पूर्ण
out:
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

EXPORT_SYMBOL(sclp_add_request);

/* Dispatch events found in request buffer to रेजिस्टरed listeners. Return 0
 * अगर all events were dispatched, non-zero otherwise. */
अटल पूर्णांक
sclp_dispatch_evbufs(काष्ठा sccb_header *sccb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा evbuf_header *evbuf;
	काष्ठा list_head *l;
	काष्ठा sclp_रेजिस्टर *reg;
	पूर्णांक offset;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_lock, flags);
	rc = 0;
	क्रम (offset = माप(काष्ठा sccb_header); offset < sccb->length;
	     offset += evbuf->length) अणु
		evbuf = (काष्ठा evbuf_header *) ((addr_t) sccb + offset);
		/* Check क्रम malक्रमmed hardware response */
		अगर (evbuf->length == 0)
			अवरोध;
		/* Search क्रम event handler */
		reg = शून्य;
		list_क्रम_each(l, &sclp_reg_list) अणु
			reg = list_entry(l, काष्ठा sclp_रेजिस्टर, list);
			अगर (reg->receive_mask & SCLP_EVTYP_MASK(evbuf->type))
				अवरोध;
			अन्यथा
				reg = शून्य;
		पूर्ण
		अगर (reg && reg->receiver_fn) अणु
			spin_unlock_irqrestore(&sclp_lock, flags);
			reg->receiver_fn(evbuf);
			spin_lock_irqsave(&sclp_lock, flags);
		पूर्ण अन्यथा अगर (reg == शून्य)
			rc = -EOPNOTSUPP;
	पूर्ण
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

/* Read event data request callback. */
अटल व्योम
sclp_पढ़ो_cb(काष्ठा sclp_req *req, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sccb_header *sccb;

	sccb = (काष्ठा sccb_header *) req->sccb;
	अगर (req->status == SCLP_REQ_DONE && (sccb->response_code == 0x20 ||
	    sccb->response_code == 0x220))
		sclp_dispatch_evbufs(sccb);
	spin_lock_irqsave(&sclp_lock, flags);
	sclp_पढ़ोing_state = sclp_पढ़ोing_state_idle;
	spin_unlock_irqrestore(&sclp_lock, flags);
पूर्ण

/* Prepare पढ़ो event data request. Called जबतक sclp_lock is locked. */
अटल व्योम __sclp_make_पढ़ो_req(व्योम)
अणु
	काष्ठा sccb_header *sccb;

	sccb = (काष्ठा sccb_header *) sclp_पढ़ो_sccb;
	clear_page(sccb);
	स_रखो(&sclp_पढ़ो_req, 0, माप(काष्ठा sclp_req));
	sclp_पढ़ो_req.command = SCLP_CMDW_READ_EVENT_DATA;
	sclp_पढ़ो_req.status = SCLP_REQ_QUEUED;
	sclp_पढ़ो_req.start_count = 0;
	sclp_पढ़ो_req.callback = sclp_पढ़ो_cb;
	sclp_पढ़ो_req.sccb = sccb;
	sccb->length = PAGE_SIZE;
	sccb->function_code = 0;
	sccb->control_mask[2] = 0x80;
पूर्ण

/* Search request list क्रम request with matching sccb. Return request अगर found,
 * शून्य otherwise. Called जबतक sclp_lock is locked. */
अटल अंतरभूत काष्ठा sclp_req *
__sclp_find_req(u32 sccb)
अणु
	काष्ठा list_head *l;
	काष्ठा sclp_req *req;

	list_क्रम_each(l, &sclp_req_queue) अणु
		req = list_entry(l, काष्ठा sclp_req, list);
		अगर (sccb == (u32) (addr_t) req->sccb)
				वापस req;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Handler क्रम बाह्यal पूर्णांकerruption. Perक्रमm request post-processing.
 * Prepare पढ़ो event data request अगर necessary. Start processing of next
 * request on queue. */
अटल व्योम sclp_पूर्णांकerrupt_handler(काष्ठा ext_code ext_code,
				   अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	काष्ठा sclp_req *req;
	u32 finished_sccb;
	u32 evbuf_pending;

	inc_irq_stat(IRQEXT_SCP);
	spin_lock(&sclp_lock);
	finished_sccb = param32 & 0xfffffff8;
	evbuf_pending = param32 & 0x3;
	अगर (finished_sccb) अणु
		del_समयr(&sclp_request_समयr);
		sclp_running_state = sclp_running_state_reset_pending;
		req = __sclp_find_req(finished_sccb);
		अगर (req) अणु
			/* Request post-processing */
			list_del(&req->list);
			req->status = SCLP_REQ_DONE;
			अगर (req->callback) अणु
				spin_unlock(&sclp_lock);
				req->callback(req, req->callback_data);
				spin_lock(&sclp_lock);
			पूर्ण
		पूर्ण
		sclp_running_state = sclp_running_state_idle;
	पूर्ण
	अगर (evbuf_pending &&
	    sclp_activation_state == sclp_activation_state_active)
		__sclp_queue_पढ़ो_req();
	spin_unlock(&sclp_lock);
	sclp_process_queue();
पूर्ण

/* Convert पूर्णांकerval in jअगरfies to TOD ticks. */
अटल अंतरभूत u64
sclp_tod_from_jअगरfies(अचिन्हित दीर्घ jअगरfies)
अणु
	वापस (u64) (jअगरfies / HZ) << 32;
पूर्ण

/* Wait until a currently running request finished. Note: जबतक this function
 * is running, no समयrs are served on the calling CPU. */
व्योम
sclp_sync_रुको(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ old_tick;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ cr0, cr0_sync;
	u64 समयout;
	पूर्णांक irq_context;

	/* We'll be disabling समयr पूर्णांकerrupts, so we need a custom समयout
	 * mechanism */
	समयout = 0;
	अगर (समयr_pending(&sclp_request_समयr)) अणु
		/* Get समयout TOD value */
		समयout = get_tod_घड़ी_fast() +
			  sclp_tod_from_jअगरfies(sclp_request_समयr.expires -
						jअगरfies);
	पूर्ण
	local_irq_save(flags);
	/* Prevent bottom half from executing once we क्रमce पूर्णांकerrupts खोलो */
	irq_context = in_पूर्णांकerrupt();
	अगर (!irq_context)
		local_bh_disable();
	/* Enable service-संकेत पूर्णांकerruption, disable समयr पूर्णांकerrupts */
	old_tick = local_tick_disable();
	trace_hardirqs_on();
	__ctl_store(cr0, 0, 0);
	cr0_sync = cr0 & ~CR0_IRQ_SUBCLASS_MASK;
	cr0_sync |= 1UL << (63 - 54);
	__ctl_load(cr0_sync, 0, 0);
	__arch_local_irq_stosm(0x01);
	/* Loop until driver state indicates finished request */
	जबतक (sclp_running_state != sclp_running_state_idle) अणु
		/* Check क्रम expired request समयr */
		अगर (समयr_pending(&sclp_request_समयr) &&
		    get_tod_घड़ी_fast() > समयout &&
		    del_समयr(&sclp_request_समयr))
			sclp_request_समयr.function(&sclp_request_समयr);
		cpu_relax();
	पूर्ण
	local_irq_disable();
	__ctl_load(cr0, 0, 0);
	अगर (!irq_context)
		_local_bh_enable();
	local_tick_enable(old_tick);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(sclp_sync_रुको);

/* Dispatch changes in send and receive mask to रेजिस्टरed listeners. */
अटल व्योम
sclp_dispatch_state_change(व्योम)
अणु
	काष्ठा list_head *l;
	काष्ठा sclp_रेजिस्टर *reg;
	अचिन्हित दीर्घ flags;
	sccb_mask_t receive_mask;
	sccb_mask_t send_mask;

	करो अणु
		spin_lock_irqsave(&sclp_lock, flags);
		reg = शून्य;
		list_क्रम_each(l, &sclp_reg_list) अणु
			reg = list_entry(l, काष्ठा sclp_रेजिस्टर, list);
			receive_mask = reg->send_mask & sclp_receive_mask;
			send_mask = reg->receive_mask & sclp_send_mask;
			अगर (reg->sclp_receive_mask != receive_mask ||
			    reg->sclp_send_mask != send_mask) अणु
				reg->sclp_receive_mask = receive_mask;
				reg->sclp_send_mask = send_mask;
				अवरोध;
			पूर्ण अन्यथा
				reg = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&sclp_lock, flags);
		अगर (reg && reg->state_change_fn)
			reg->state_change_fn(reg);
	पूर्ण जबतक (reg);
पूर्ण

काष्ठा sclp_statechangebuf अणु
	काष्ठा evbuf_header	header;
	u8		validity_sclp_active_facility_mask : 1;
	u8		validity_sclp_receive_mask : 1;
	u8		validity_sclp_send_mask : 1;
	u8		validity_पढ़ो_data_function_mask : 1;
	u16		_zeros : 12;
	u16		mask_length;
	u64		sclp_active_facility_mask;
	u8		masks[2 * 1021 + 4];	/* variable length */
	/*
	 * u8		sclp_receive_mask[mask_length];
	 * u8		sclp_send_mask[mask_length];
	 * u32		पढ़ो_data_function_mask;
	 */
पूर्ण __attribute__((packed));


/* State change event callback. Inक्रमm listeners of changes. */
अटल व्योम
sclp_state_change_cb(काष्ठा evbuf_header *evbuf)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sclp_statechangebuf *scbuf;

	BUILD_BUG_ON(माप(काष्ठा sclp_statechangebuf) > PAGE_SIZE);

	scbuf = (काष्ठा sclp_statechangebuf *) evbuf;
	spin_lock_irqsave(&sclp_lock, flags);
	अगर (scbuf->validity_sclp_receive_mask)
		sclp_receive_mask = sccb_get_recv_mask(scbuf);
	अगर (scbuf->validity_sclp_send_mask)
		sclp_send_mask = sccb_get_send_mask(scbuf);
	spin_unlock_irqrestore(&sclp_lock, flags);
	अगर (scbuf->validity_sclp_active_facility_mask)
		sclp.facilities = scbuf->sclp_active_facility_mask;
	sclp_dispatch_state_change();
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_state_change_event = अणु
	.receive_mask = EVTYP_STATECHANGE_MASK,
	.receiver_fn = sclp_state_change_cb
पूर्ण;

/* Calculate receive and send mask of currently रेजिस्टरed listeners.
 * Called जबतक sclp_lock is locked. */
अटल अंतरभूत व्योम
__sclp_get_mask(sccb_mask_t *receive_mask, sccb_mask_t *send_mask)
अणु
	काष्ठा list_head *l;
	काष्ठा sclp_रेजिस्टर *t;

	*receive_mask = 0;
	*send_mask = 0;
	list_क्रम_each(l, &sclp_reg_list) अणु
		t = list_entry(l, काष्ठा sclp_रेजिस्टर, list);
		*receive_mask |= t->receive_mask;
		*send_mask |= t->send_mask;
	पूर्ण
पूर्ण

/* Register event listener. Return 0 on success, non-zero otherwise. */
पूर्णांक
sclp_रेजिस्टर(काष्ठा sclp_रेजिस्टर *reg)
अणु
	अचिन्हित दीर्घ flags;
	sccb_mask_t receive_mask;
	sccb_mask_t send_mask;
	पूर्णांक rc;

	rc = sclp_init();
	अगर (rc)
		वापस rc;
	spin_lock_irqsave(&sclp_lock, flags);
	/* Check event mask क्रम collisions */
	__sclp_get_mask(&receive_mask, &send_mask);
	अगर (reg->receive_mask & receive_mask || reg->send_mask & send_mask) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EBUSY;
	पूर्ण
	/* Trigger initial state change callback */
	reg->sclp_receive_mask = 0;
	reg->sclp_send_mask = 0;
	reg->pm_event_posted = 0;
	list_add(&reg->list, &sclp_reg_list);
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(1);
	अगर (rc) अणु
		spin_lock_irqsave(&sclp_lock, flags);
		list_del(&reg->list);
		spin_unlock_irqrestore(&sclp_lock, flags);
	पूर्ण
	वापस rc;
पूर्ण

EXPORT_SYMBOL(sclp_रेजिस्टर);

/* Unरेजिस्टर event listener. */
व्योम
sclp_unरेजिस्टर(काष्ठा sclp_रेजिस्टर *reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_lock, flags);
	list_del(&reg->list);
	spin_unlock_irqrestore(&sclp_lock, flags);
	sclp_init_mask(1);
पूर्ण

EXPORT_SYMBOL(sclp_unरेजिस्टर);

/* Remove event buffers which are marked processed. Return the number of
 * reमुख्यing event buffers. */
पूर्णांक
sclp_हटाओ_processed(काष्ठा sccb_header *sccb)
अणु
	काष्ठा evbuf_header *evbuf;
	पूर्णांक unprocessed;
	u16 reमुख्यing;

	evbuf = (काष्ठा evbuf_header *) (sccb + 1);
	unprocessed = 0;
	reमुख्यing = sccb->length - माप(काष्ठा sccb_header);
	जबतक (reमुख्यing > 0) अणु
		reमुख्यing -= evbuf->length;
		अगर (evbuf->flags & 0x80) अणु
			sccb->length -= evbuf->length;
			स_नकल(evbuf, (व्योम *) ((addr_t) evbuf + evbuf->length),
			       reमुख्यing);
		पूर्ण अन्यथा अणु
			unprocessed++;
			evbuf = (काष्ठा evbuf_header *)
					((addr_t) evbuf + evbuf->length);
		पूर्ण
	पूर्ण
	वापस unprocessed;
पूर्ण

EXPORT_SYMBOL(sclp_हटाओ_processed);

/* Prepare init mask request. Called जबतक sclp_lock is locked. */
अटल अंतरभूत व्योम
__sclp_make_init_req(sccb_mask_t receive_mask, sccb_mask_t send_mask)
अणु
	काष्ठा init_sccb *sccb = sclp_init_sccb;

	clear_page(sccb);
	स_रखो(&sclp_init_req, 0, माप(काष्ठा sclp_req));
	sclp_init_req.command = SCLP_CMDW_WRITE_EVENT_MASK;
	sclp_init_req.status = SCLP_REQ_FILLED;
	sclp_init_req.start_count = 0;
	sclp_init_req.callback = शून्य;
	sclp_init_req.callback_data = शून्य;
	sclp_init_req.sccb = sccb;
	sccb->header.length = माप(*sccb);
	अगर (sclp_mask_compat_mode)
		sccb->mask_length = SCLP_MASK_SIZE_COMPAT;
	अन्यथा
		sccb->mask_length = माप(sccb_mask_t);
	sccb_set_recv_mask(sccb, receive_mask);
	sccb_set_send_mask(sccb, send_mask);
	sccb_set_sclp_recv_mask(sccb, 0);
	sccb_set_sclp_send_mask(sccb, 0);
पूर्ण

/* Start init mask request. If calculate is non-zero, calculate the mask as
 * requested by रेजिस्टरed listeners. Use zero mask otherwise. Return 0 on
 * success, non-zero otherwise. */
अटल पूर्णांक
sclp_init_mask(पूर्णांक calculate)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा init_sccb *sccb = sclp_init_sccb;
	sccb_mask_t receive_mask;
	sccb_mask_t send_mask;
	पूर्णांक retry;
	पूर्णांक rc;
	अचिन्हित दीर्घ रुको;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Check अगर पूर्णांकerface is in appropriate state */
	अगर (sclp_mask_state != sclp_mask_state_idle) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EBUSY;
	पूर्ण
	अगर (sclp_activation_state == sclp_activation_state_inactive) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EINVAL;
	पूर्ण
	sclp_mask_state = sclp_mask_state_initializing;
	/* Determine mask */
	अगर (calculate)
		__sclp_get_mask(&receive_mask, &send_mask);
	अन्यथा अणु
		receive_mask = 0;
		send_mask = 0;
	पूर्ण
	rc = -EIO;
	क्रम (retry = 0; retry <= SCLP_MASK_RETRY; retry++) अणु
		/* Prepare request */
		__sclp_make_init_req(receive_mask, send_mask);
		spin_unlock_irqrestore(&sclp_lock, flags);
		अगर (sclp_add_request(&sclp_init_req)) अणु
			/* Try again later */
			रुको = jअगरfies + SCLP_BUSY_INTERVAL * HZ;
			जबतक (समय_beक्रमe(jअगरfies, रुको))
				sclp_sync_रुको();
			spin_lock_irqsave(&sclp_lock, flags);
			जारी;
		पूर्ण
		जबतक (sclp_init_req.status != SCLP_REQ_DONE &&
		       sclp_init_req.status != SCLP_REQ_FAILED)
			sclp_sync_रुको();
		spin_lock_irqsave(&sclp_lock, flags);
		अगर (sclp_init_req.status == SCLP_REQ_DONE &&
		    sccb->header.response_code == 0x20) अणु
			/* Successful request */
			अगर (calculate) अणु
				sclp_receive_mask = sccb_get_sclp_recv_mask(sccb);
				sclp_send_mask = sccb_get_sclp_send_mask(sccb);
			पूर्ण अन्यथा अणु
				sclp_receive_mask = 0;
				sclp_send_mask = 0;
			पूर्ण
			spin_unlock_irqrestore(&sclp_lock, flags);
			sclp_dispatch_state_change();
			spin_lock_irqsave(&sclp_lock, flags);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	sclp_mask_state = sclp_mask_state_idle;
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

/* Deactivate SCLP पूर्णांकerface. On success, new requests will be rejected,
 * events will no दीर्घer be dispatched. Return 0 on success, non-zero
 * otherwise. */
पूर्णांक
sclp_deactivate(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Deactivate can only be called when active */
	अगर (sclp_activation_state != sclp_activation_state_active) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EINVAL;
	पूर्ण
	sclp_activation_state = sclp_activation_state_deactivating;
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(0);
	spin_lock_irqsave(&sclp_lock, flags);
	अगर (rc == 0)
		sclp_activation_state = sclp_activation_state_inactive;
	अन्यथा
		sclp_activation_state = sclp_activation_state_active;
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

EXPORT_SYMBOL(sclp_deactivate);

/* Reactivate SCLP पूर्णांकerface after sclp_deactivate. On success, new
 * requests will be accepted, events will be dispatched again. Return 0 on
 * success, non-zero otherwise. */
पूर्णांक
sclp_reactivate(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Reactivate can only be called when inactive */
	अगर (sclp_activation_state != sclp_activation_state_inactive) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस -EINVAL;
	पूर्ण
	sclp_activation_state = sclp_activation_state_activating;
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(1);
	spin_lock_irqsave(&sclp_lock, flags);
	अगर (rc == 0)
		sclp_activation_state = sclp_activation_state_active;
	अन्यथा
		sclp_activation_state = sclp_activation_state_inactive;
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

EXPORT_SYMBOL(sclp_reactivate);

/* Handler क्रम बाह्यal पूर्णांकerruption used during initialization. Modअगरy
 * request state to करोne. */
अटल व्योम sclp_check_handler(काष्ठा ext_code ext_code,
			       अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	u32 finished_sccb;

	inc_irq_stat(IRQEXT_SCP);
	finished_sccb = param32 & 0xfffffff8;
	/* Is this the पूर्णांकerrupt we are रुकोing क्रम? */
	अगर (finished_sccb == 0)
		वापस;
	अगर (finished_sccb != (u32) (addr_t) sclp_init_sccb)
		panic("sclp: unsolicited interrupt for buffer at 0x%x\n",
		      finished_sccb);
	spin_lock(&sclp_lock);
	अगर (sclp_running_state == sclp_running_state_running) अणु
		sclp_init_req.status = SCLP_REQ_DONE;
		sclp_running_state = sclp_running_state_idle;
	पूर्ण
	spin_unlock(&sclp_lock);
पूर्ण

/* Initial init mask request समयd out. Modअगरy request state to failed. */
अटल व्योम
sclp_check_समयout(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_lock, flags);
	अगर (sclp_running_state == sclp_running_state_running) अणु
		sclp_init_req.status = SCLP_REQ_FAILED;
		sclp_running_state = sclp_running_state_idle;
	पूर्ण
	spin_unlock_irqrestore(&sclp_lock, flags);
पूर्ण

/* Perक्रमm a check of the SCLP पूर्णांकerface. Return zero अगर the पूर्णांकerface is
 * available and there are no pending requests from a previous instance.
 * Return non-zero otherwise. */
अटल पूर्णांक
sclp_check_पूर्णांकerface(व्योम)
अणु
	काष्ठा init_sccb *sccb;
	अचिन्हित दीर्घ flags;
	पूर्णांक retry;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Prepare init mask command */
	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_SERVICE_SIG, sclp_check_handler);
	अगर (rc) अणु
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस rc;
	पूर्ण
	क्रम (retry = 0; retry <= SCLP_INIT_RETRY; retry++) अणु
		__sclp_make_init_req(0, 0);
		sccb = (काष्ठा init_sccb *) sclp_init_req.sccb;
		rc = sclp_service_call(sclp_init_req.command, sccb);
		अगर (rc == -EIO)
			अवरोध;
		sclp_init_req.status = SCLP_REQ_RUNNING;
		sclp_running_state = sclp_running_state_running;
		__sclp_set_request_समयr(SCLP_RETRY_INTERVAL * HZ,
					 sclp_check_समयout);
		spin_unlock_irqrestore(&sclp_lock, flags);
		/* Enable service-संकेत पूर्णांकerruption - needs to happen
		 * with IRQs enabled. */
		irq_subclass_रेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
		/* Wait क्रम संकेत from पूर्णांकerrupt or समयout */
		sclp_sync_रुको();
		/* Disable service-संकेत पूर्णांकerruption - needs to happen
		 * with IRQs enabled. */
		irq_subclass_unरेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
		spin_lock_irqsave(&sclp_lock, flags);
		del_समयr(&sclp_request_समयr);
		rc = -EBUSY;
		अगर (sclp_init_req.status == SCLP_REQ_DONE) अणु
			अगर (sccb->header.response_code == 0x20) अणु
				rc = 0;
				अवरोध;
			पूर्ण अन्यथा अगर (sccb->header.response_code == 0x74f0) अणु
				अगर (!sclp_mask_compat_mode) अणु
					sclp_mask_compat_mode = true;
					retry = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_SERVICE_SIG, sclp_check_handler);
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

/* Reboot event handler. Reset send and receive mask to prevent pending SCLP
 * events from पूर्णांकerfering with rebooted प्रणाली. */
अटल पूर्णांक
sclp_reboot_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	sclp_deactivate();
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sclp_reboot_notअगरier = अणु
	.notअगरier_call = sclp_reboot_event
पूर्ण;

/*
 * Suspend/resume SCLP notअगरier implementation
 */

अटल व्योम sclp_pm_event(क्रमागत sclp_pm_event sclp_pm_event, पूर्णांक rollback)
अणु
	काष्ठा sclp_रेजिस्टर *reg;
	अचिन्हित दीर्घ flags;

	अगर (!rollback) अणु
		spin_lock_irqsave(&sclp_lock, flags);
		list_क्रम_each_entry(reg, &sclp_reg_list, list)
			reg->pm_event_posted = 0;
		spin_unlock_irqrestore(&sclp_lock, flags);
	पूर्ण
	करो अणु
		spin_lock_irqsave(&sclp_lock, flags);
		list_क्रम_each_entry(reg, &sclp_reg_list, list) अणु
			अगर (rollback && reg->pm_event_posted)
				जाओ found;
			अगर (!rollback && !reg->pm_event_posted)
				जाओ found;
		पूर्ण
		spin_unlock_irqrestore(&sclp_lock, flags);
		वापस;
found:
		spin_unlock_irqrestore(&sclp_lock, flags);
		अगर (reg->pm_event_fn)
			reg->pm_event_fn(reg, sclp_pm_event);
		reg->pm_event_posted = rollback ? 0 : 1;
	पूर्ण जबतक (1);
पूर्ण

/*
 * Susend/resume callbacks क्रम platक्रमm device
 */

अटल पूर्णांक sclp_मुक्तze(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	sclp_pm_event(SCLP_PM_EVENT_FREEZE, 0);

	spin_lock_irqsave(&sclp_lock, flags);
	sclp_suspend_state = sclp_suspend_state_suspended;
	spin_unlock_irqrestore(&sclp_lock, flags);

	/* Init supend data */
	स_रखो(&sclp_suspend_req, 0, माप(sclp_suspend_req));
	sclp_suspend_req.callback = sclp_suspend_req_cb;
	sclp_suspend_req.status = SCLP_REQ_FILLED;
	init_completion(&sclp_request_queue_flushed);

	rc = sclp_add_request(&sclp_suspend_req);
	अगर (rc == 0)
		रुको_क्रम_completion(&sclp_request_queue_flushed);
	अन्यथा अगर (rc != -ENODATA)
		जाओ fail_thaw;

	rc = sclp_deactivate();
	अगर (rc)
		जाओ fail_thaw;
	वापस 0;

fail_thaw:
	spin_lock_irqsave(&sclp_lock, flags);
	sclp_suspend_state = sclp_suspend_state_running;
	spin_unlock_irqrestore(&sclp_lock, flags);
	sclp_pm_event(SCLP_PM_EVENT_THAW, 1);
	वापस rc;
पूर्ण

अटल पूर्णांक sclp_unकरो_suspend(क्रमागत sclp_pm_event event)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = sclp_reactivate();
	अगर (rc)
		वापस rc;

	spin_lock_irqsave(&sclp_lock, flags);
	sclp_suspend_state = sclp_suspend_state_running;
	spin_unlock_irqrestore(&sclp_lock, flags);

	sclp_pm_event(event, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक sclp_thaw(काष्ठा device *dev)
अणु
	वापस sclp_unकरो_suspend(SCLP_PM_EVENT_THAW);
पूर्ण

अटल पूर्णांक sclp_restore(काष्ठा device *dev)
अणु
	वापस sclp_unकरो_suspend(SCLP_PM_EVENT_RESTORE);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sclp_pm_ops = अणु
	.मुक्तze		= sclp_मुक्तze,
	.thaw		= sclp_thaw,
	.restore	= sclp_restore,
पूर्ण;

अटल sमाप_प्रकार con_pages_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", sclp_console_pages);
पूर्ण

अटल DRIVER_ATTR_RO(con_pages);

अटल sमाप_प्रकार con_drop_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", sclp_console_drop);
पूर्ण

अटल DRIVER_ATTR_RO(con_drop);

अटल sमाप_प्रकार con_full_show(काष्ठा device_driver *dev, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", sclp_console_full);
पूर्ण

अटल DRIVER_ATTR_RO(con_full);

अटल काष्ठा attribute *sclp_drv_attrs[] = अणु
	&driver_attr_con_pages.attr,
	&driver_attr_con_drop.attr,
	&driver_attr_con_full.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group sclp_drv_attr_group = अणु
	.attrs = sclp_drv_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *sclp_drv_attr_groups[] = अणु
	&sclp_drv_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा platक्रमm_driver sclp_pdrv = अणु
	.driver = अणु
		.name	= "sclp",
		.pm	= &sclp_pm_ops,
		.groups = sclp_drv_attr_groups,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *sclp_pdev;

/* Initialize SCLP driver. Return zero अगर driver is operational, non-zero
 * otherwise. */
अटल पूर्णांक
sclp_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Check क्रम previous or running initialization */
	अगर (sclp_init_state != sclp_init_state_uninitialized)
		जाओ fail_unlock;
	sclp_init_state = sclp_init_state_initializing;
	sclp_पढ़ो_sccb = (व्योम *) __get_मुक्त_page(GFP_ATOMIC | GFP_DMA);
	sclp_init_sccb = (व्योम *) __get_मुक्त_page(GFP_ATOMIC | GFP_DMA);
	BUG_ON(!sclp_पढ़ो_sccb || !sclp_init_sccb);
	/* Set up variables */
	list_add(&sclp_state_change_event.list, &sclp_reg_list);
	समयr_setup(&sclp_request_समयr, शून्य, 0);
	समयr_setup(&sclp_queue_समयr, sclp_req_queue_समयout, 0);
	/* Check पूर्णांकerface */
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_check_पूर्णांकerface();
	spin_lock_irqsave(&sclp_lock, flags);
	अगर (rc)
		जाओ fail_init_state_uninitialized;
	/* Register reboot handler */
	rc = रेजिस्टर_reboot_notअगरier(&sclp_reboot_notअगरier);
	अगर (rc)
		जाओ fail_init_state_uninitialized;
	/* Register पूर्णांकerrupt handler */
	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_SERVICE_SIG, sclp_पूर्णांकerrupt_handler);
	अगर (rc)
		जाओ fail_unरेजिस्टर_reboot_notअगरier;
	sclp_init_state = sclp_init_state_initialized;
	spin_unlock_irqrestore(&sclp_lock, flags);
	/* Enable service-संकेत बाह्यal पूर्णांकerruption - needs to happen with
	 * IRQs enabled. */
	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	sclp_init_mask(1);
	वापस 0;

fail_unरेजिस्टर_reboot_notअगरier:
	unरेजिस्टर_reboot_notअगरier(&sclp_reboot_notअगरier);
fail_init_state_uninitialized:
	sclp_init_state = sclp_init_state_uninitialized;
	मुक्त_page((अचिन्हित दीर्घ) sclp_पढ़ो_sccb);
	मुक्त_page((अचिन्हित दीर्घ) sclp_init_sccb);
fail_unlock:
	spin_unlock_irqrestore(&sclp_lock, flags);
	वापस rc;
पूर्ण

/*
 * SCLP panic notअगरier: If we are suspended, we thaw SCLP in order to be able
 * to prपूर्णांक the panic message.
 */
अटल पूर्णांक sclp_panic_notअगरy(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ event, व्योम *data)
अणु
	अगर (sclp_suspend_state == sclp_suspend_state_suspended)
		sclp_unकरो_suspend(SCLP_PM_EVENT_THAW);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sclp_on_panic_nb = अणु
	.notअगरier_call = sclp_panic_notअगरy,
	.priority = SCLP_PANIC_PRIO,
पूर्ण;

अटल __init पूर्णांक sclp_initcall(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&sclp_pdrv);
	अगर (rc)
		वापस rc;

	sclp_pdev = platक्रमm_device_रेजिस्टर_simple("sclp", -1, शून्य, 0);
	rc = PTR_ERR_OR_ZERO(sclp_pdev);
	अगर (rc)
		जाओ fail_platक्रमm_driver_unरेजिस्टर;

	rc = atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					    &sclp_on_panic_nb);
	अगर (rc)
		जाओ fail_platक्रमm_device_unरेजिस्टर;

	वापस sclp_init();

fail_platक्रमm_device_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(sclp_pdev);
fail_platक्रमm_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&sclp_pdrv);
	वापस rc;
पूर्ण

arch_initcall(sclp_initcall);
