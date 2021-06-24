<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SSH request transport layer.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <linux/completion.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/serial_hub.h>
#समावेश <linux/surface_aggregator/controller.h>

#समावेश "ssh_packet_layer.h"
#समावेश "ssh_request_layer.h"

#समावेश "trace.h"

/*
 * SSH_RTL_REQUEST_TIMEOUT - Request समयout.
 *
 * Timeout as kसमय_प्रकार delta क्रम request responses. If we have not received a
 * response in this समय-frame after finishing the underlying packet
 * transmission, the request will be completed with %-ETIMEDOUT as status
 * code.
 */
#घोषणा SSH_RTL_REQUEST_TIMEOUT			ms_to_kसमय(3000)

/*
 * SSH_RTL_REQUEST_TIMEOUT_RESOLUTION - Request समयout granularity.
 *
 * Time-resolution क्रम समयouts. Should be larger than one jअगरfy to aव्योम
 * direct re-scheduling of reaper work_काष्ठा.
 */
#घोषणा SSH_RTL_REQUEST_TIMEOUT_RESOLUTION	ms_to_kसमय(max(2000 / HZ, 50))

/*
 * SSH_RTL_MAX_PENDING - Maximum number of pending requests.
 *
 * Maximum number of requests concurrently रुकोing to be completed (i.e.
 * रुकोing क्रम the corresponding packet transmission to finish अगर they करोn't
 * have a response or रुकोing क्रम a response अगर they have one).
 */
#घोषणा SSH_RTL_MAX_PENDING		3

/*
 * SSH_RTL_TX_BATCH - Maximum number of requests processed per work execution.
 * Used to prevent livelocking of the workqueue. Value chosen via educated
 * guess, may be adjusted.
 */
#घोषणा SSH_RTL_TX_BATCH		10

#अगर_घोषित CONFIG_SURFACE_AGGREGATOR_ERROR_INJECTION

/**
 * ssh_rtl_should_drop_response() - Error injection hook to drop request
 * responses.
 *
 * Useful to cause request transmission समयouts in the driver by dropping the
 * response to a request.
 */
अटल noअंतरभूत bool ssh_rtl_should_drop_response(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_rtl_should_drop_response, TRUE);

#अन्यथा

अटल अंतरभूत bool ssh_rtl_should_drop_response(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

अटल u16 ssh_request_get_rqid(काष्ठा ssh_request *rqst)
अणु
	वापस get_unaligned_le16(rqst->packet.data.ptr
				  + SSH_MSGOFFSET_COMMAND(rqid));
पूर्ण

अटल u32 ssh_request_get_rqid_safe(काष्ठा ssh_request *rqst)
अणु
	अगर (!rqst->packet.data.ptr)
		वापस U32_MAX;

	वापस ssh_request_get_rqid(rqst);
पूर्ण

अटल व्योम ssh_rtl_queue_हटाओ(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	spin_lock(&rtl->queue.lock);

	अगर (!test_and_clear_bit(SSH_REQUEST_SF_QUEUED_BIT, &rqst->state)) अणु
		spin_unlock(&rtl->queue.lock);
		वापस;
	पूर्ण

	list_del(&rqst->node);

	spin_unlock(&rtl->queue.lock);
	ssh_request_put(rqst);
पूर्ण

अटल bool ssh_rtl_queue_empty(काष्ठा ssh_rtl *rtl)
अणु
	bool empty;

	spin_lock(&rtl->queue.lock);
	empty = list_empty(&rtl->queue.head);
	spin_unlock(&rtl->queue.lock);

	वापस empty;
पूर्ण

अटल व्योम ssh_rtl_pending_हटाओ(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	spin_lock(&rtl->pending.lock);

	अगर (!test_and_clear_bit(SSH_REQUEST_SF_PENDING_BIT, &rqst->state)) अणु
		spin_unlock(&rtl->pending.lock);
		वापस;
	पूर्ण

	atomic_dec(&rtl->pending.count);
	list_del(&rqst->node);

	spin_unlock(&rtl->pending.lock);

	ssh_request_put(rqst);
पूर्ण

अटल पूर्णांक ssh_rtl_tx_pending_push(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	spin_lock(&rtl->pending.lock);

	अगर (test_bit(SSH_REQUEST_SF_LOCKED_BIT, &rqst->state)) अणु
		spin_unlock(&rtl->pending.lock);
		वापस -EINVAL;
	पूर्ण

	अगर (test_and_set_bit(SSH_REQUEST_SF_PENDING_BIT, &rqst->state)) अणु
		spin_unlock(&rtl->pending.lock);
		वापस -EALREADY;
	पूर्ण

	atomic_inc(&rtl->pending.count);
	list_add_tail(&ssh_request_get(rqst)->node, &rtl->pending.head);

	spin_unlock(&rtl->pending.lock);
	वापस 0;
पूर्ण

अटल व्योम ssh_rtl_complete_with_status(काष्ठा ssh_request *rqst, पूर्णांक status)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	trace_ssam_request_complete(rqst, status);

	/* rtl/ptl may not be set अगर we're canceling beक्रमe submitting. */
	rtl_dbg_cond(rtl, "rtl: completing request (rqid: %#06x, status: %d)\n",
		     ssh_request_get_rqid_safe(rqst), status);

	rqst->ops->complete(rqst, शून्य, शून्य, status);
पूर्ण

अटल व्योम ssh_rtl_complete_with_rsp(काष्ठा ssh_request *rqst,
				      स्थिर काष्ठा ssh_command *cmd,
				      स्थिर काष्ठा ssam_span *data)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	trace_ssam_request_complete(rqst, 0);

	rtl_dbg(rtl, "rtl: completing request with response (rqid: %#06x)\n",
		ssh_request_get_rqid(rqst));

	rqst->ops->complete(rqst, cmd, data, 0);
पूर्ण

अटल bool ssh_rtl_tx_can_process(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);

	अगर (test_bit(SSH_REQUEST_TY_FLUSH_BIT, &rqst->state))
		वापस !atomic_पढ़ो(&rtl->pending.count);

	वापस atomic_पढ़ो(&rtl->pending.count) < SSH_RTL_MAX_PENDING;
पूर्ण

अटल काष्ठा ssh_request *ssh_rtl_tx_next(काष्ठा ssh_rtl *rtl)
अणु
	काष्ठा ssh_request *rqst = ERR_PTR(-ENOENT);
	काष्ठा ssh_request *p, *n;

	spin_lock(&rtl->queue.lock);

	/* Find first non-locked request and हटाओ it. */
	list_क्रम_each_entry_safe(p, n, &rtl->queue.head, node) अणु
		अगर (unlikely(test_bit(SSH_REQUEST_SF_LOCKED_BIT, &p->state)))
			जारी;

		अगर (!ssh_rtl_tx_can_process(p)) अणु
			rqst = ERR_PTR(-EBUSY);
			अवरोध;
		पूर्ण

		/* Remove from queue and mark as transmitting. */
		set_bit(SSH_REQUEST_SF_TRANSMITTING_BIT, &p->state);
		/* Ensure state never माला_लो zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_REQUEST_SF_QUEUED_BIT, &p->state);

		list_del(&p->node);

		rqst = p;
		अवरोध;
	पूर्ण

	spin_unlock(&rtl->queue.lock);
	वापस rqst;
पूर्ण

अटल पूर्णांक ssh_rtl_tx_try_process_one(काष्ठा ssh_rtl *rtl)
अणु
	काष्ठा ssh_request *rqst;
	पूर्णांक status;

	/* Get and prepare next request क्रम transmit. */
	rqst = ssh_rtl_tx_next(rtl);
	अगर (IS_ERR(rqst))
		वापस PTR_ERR(rqst);

	/* Add it to/mark it as pending. */
	status = ssh_rtl_tx_pending_push(rqst);
	अगर (status) अणु
		ssh_request_put(rqst);
		वापस -EAGAIN;
	पूर्ण

	/* Submit packet. */
	status = ssh_ptl_submit(&rtl->ptl, &rqst->packet);
	अगर (status == -ESHUTDOWN) अणु
		/*
		 * Packet has been refused due to the packet layer shutting
		 * करोwn. Complete it here.
		 */
		set_bit(SSH_REQUEST_SF_LOCKED_BIT, &rqst->state);
		/*
		 * Note: A barrier is not required here, as there are only two
		 * references in the प्रणाली at this poपूर्णांक: The one that we have,
		 * and the other one that beदीर्घs to the pending set. Due to the
		 * request being marked as "transmitting", our process is the
		 * only one allowed to हटाओ the pending node and change the
		 * state. Normally, the task would fall to the packet callback,
		 * but as this is a path where submission failed, this callback
		 * will never be executed.
		 */

		ssh_rtl_pending_हटाओ(rqst);
		ssh_rtl_complete_with_status(rqst, -ESHUTDOWN);

		ssh_request_put(rqst);
		वापस -ESHUTDOWN;

	पूर्ण अन्यथा अगर (status) अणु
		/*
		 * If submitting the packet failed and the packet layer isn't
		 * shutting करोwn, the packet has either been submitted/queued
		 * beक्रमe (-EALREADY, which cannot happen as we have
		 * guaranteed that requests cannot be re-submitted), or the
		 * packet was marked as locked (-EINVAL). To mark the packet
		 * locked at this stage, the request, and thus the packets
		 * itself, had to have been canceled. Simply drop the
		 * reference. Cancellation itself will हटाओ it from the set
		 * of pending requests.
		 */

		WARN_ON(status != -EINVAL);

		ssh_request_put(rqst);
		वापस -EAGAIN;
	पूर्ण

	ssh_request_put(rqst);
	वापस 0;
पूर्ण

अटल bool ssh_rtl_tx_schedule(काष्ठा ssh_rtl *rtl)
अणु
	अगर (atomic_पढ़ो(&rtl->pending.count) >= SSH_RTL_MAX_PENDING)
		वापस false;

	अगर (ssh_rtl_queue_empty(rtl))
		वापस false;

	वापस schedule_work(&rtl->tx.work);
पूर्ण

अटल व्योम ssh_rtl_tx_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssh_rtl *rtl = to_ssh_rtl(work, tx.work);
	अचिन्हित पूर्णांक iterations = SSH_RTL_TX_BATCH;
	पूर्णांक status;

	/*
	 * Try to be nice and not block/live-lock the workqueue: Run a maximum
	 * of 10 tries, then re-submit अगर necessary. This should not be
	 * necessary क्रम normal execution, but guarantee it anyway.
	 */
	करो अणु
		status = ssh_rtl_tx_try_process_one(rtl);
		अगर (status == -ENOENT || status == -EBUSY)
			वापस;		/* No more requests to process. */

		अगर (status == -ESHUTDOWN) अणु
			/*
			 * Packet प्रणाली shutting करोwn. No new packets can be
			 * transmitted. Return silently, the party initiating
			 * the shutकरोwn should handle the rest.
			 */
			वापस;
		पूर्ण

		WARN_ON(status != 0 && status != -EAGAIN);
	पूर्ण जबतक (--iterations);

	/* Out of tries, reschedule. */
	ssh_rtl_tx_schedule(rtl);
पूर्ण

/**
 * ssh_rtl_submit() - Submit a request to the transport layer.
 * @rtl:  The request transport layer.
 * @rqst: The request to submit.
 *
 * Submits a request to the transport layer. A single request may not be
 * submitted multiple बार without reinitializing it.
 *
 * Return: Returns zero on success, %-EINVAL अगर the request type is invalid or
 * the request has been canceled prior to submission, %-EALREADY अगर the
 * request has alपढ़ोy been submitted, or %-ESHUTDOWN in हाल the request
 * transport layer has been shut करोwn.
 */
पूर्णांक ssh_rtl_submit(काष्ठा ssh_rtl *rtl, काष्ठा ssh_request *rqst)
अणु
	trace_ssam_request_submit(rqst);

	/*
	 * Ensure that requests expecting a response are sequenced. If this
	 * invariant ever changes, see the comment in ssh_rtl_complete() on what
	 * is required to be changed in the code.
	 */
	अगर (test_bit(SSH_REQUEST_TY_HAS_RESPONSE_BIT, &rqst->state))
		अगर (!test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &rqst->packet.state))
			वापस -EINVAL;

	spin_lock(&rtl->queue.lock);

	/*
	 * Try to set ptl and check अगर this request has alपढ़ोy been submitted.
	 *
	 * Must be inside lock as we might run पूर्णांकo a lost update problem
	 * otherwise: If this were outside of the lock, cancellation in
	 * ssh_rtl_cancel_nonpending() may run after we've set the ptl
	 * reference but beक्रमe we enter the lock. In that हाल, we'd detect
	 * that the request is being added to the queue and would try to हटाओ
	 * it from that, but removal might fail because it hasn't actually been
	 * added yet. By putting this cmpxchg in the critical section, we
	 * ensure that the queuing detection only triggers when we are alपढ़ोy
	 * in the critical section and the हटाओ process will रुको until the
	 * push operation has been completed (via lock) due to that. Only then,
	 * we can safely try to हटाओ it.
	 */
	अगर (cmpxchg(&rqst->packet.ptl, शून्य, &rtl->ptl)) अणु
		spin_unlock(&rtl->queue.lock);
		वापस -EALREADY;
	पूर्ण

	/*
	 * Ensure that we set ptl reference beक्रमe we जारी modअगरying state.
	 * This is required क्रम non-pending cancellation. This barrier is paired
	 * with the one in ssh_rtl_cancel_nonpending().
	 *
	 * By setting the ptl reference beक्रमe we test क्रम "locked", we can
	 * check अगर the "locked" test may have alपढ़ोy run. See comments in
	 * ssh_rtl_cancel_nonpending() क्रम more detail.
	 */
	smp_mb__after_atomic();

	अगर (test_bit(SSH_RTL_SF_SHUTDOWN_BIT, &rtl->state)) अणु
		spin_unlock(&rtl->queue.lock);
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (test_bit(SSH_REQUEST_SF_LOCKED_BIT, &rqst->state)) अणु
		spin_unlock(&rtl->queue.lock);
		वापस -EINVAL;
	पूर्ण

	set_bit(SSH_REQUEST_SF_QUEUED_BIT, &rqst->state);
	list_add_tail(&ssh_request_get(rqst)->node, &rtl->queue.head);

	spin_unlock(&rtl->queue.lock);

	ssh_rtl_tx_schedule(rtl);
	वापस 0;
पूर्ण

अटल व्योम ssh_rtl_समयout_reaper_mod(काष्ठा ssh_rtl *rtl, kसमय_प्रकार now,
				       kसमय_प्रकार expires)
अणु
	अचिन्हित दीर्घ delta = msecs_to_jअगरfies(kसमय_ms_delta(expires, now));
	kसमय_प्रकार aexp = kसमय_add(expires, SSH_RTL_REQUEST_TIMEOUT_RESOLUTION);

	spin_lock(&rtl->rtx_समयout.lock);

	/* Re-adjust / schedule reaper only अगर it is above resolution delta. */
	अगर (kसमय_beक्रमe(aexp, rtl->rtx_समयout.expires)) अणु
		rtl->rtx_समयout.expires = expires;
		mod_delayed_work(प्रणाली_wq, &rtl->rtx_समयout.reaper, delta);
	पूर्ण

	spin_unlock(&rtl->rtx_समयout.lock);
पूर्ण

अटल व्योम ssh_rtl_समयout_start(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);
	kसमय_प्रकार बारtamp = kसमय_get_coarse_bootसमय();
	kसमय_प्रकार समयout = rtl->rtx_समयout.समयout;

	अगर (test_bit(SSH_REQUEST_SF_LOCKED_BIT, &rqst->state))
		वापस;

	/*
	 * Note: The बारtamp माला_लो set only once. This happens on the packet
	 * callback. All other access to it is पढ़ो-only.
	 */
	WRITE_ONCE(rqst->बारtamp, बारtamp);
	/*
	 * Ensure बारtamp is set beक्रमe starting the reaper. Paired with
	 * implicit barrier following check on ssh_request_get_expiration() in
	 * ssh_rtl_समयout_reap.
	 */
	smp_mb__after_atomic();

	ssh_rtl_समयout_reaper_mod(rtl, बारtamp, बारtamp + समयout);
पूर्ण

अटल व्योम ssh_rtl_complete(काष्ठा ssh_rtl *rtl,
			     स्थिर काष्ठा ssh_command *command,
			     स्थिर काष्ठा ssam_span *command_data)
अणु
	काष्ठा ssh_request *r = शून्य;
	काष्ठा ssh_request *p, *n;
	u16 rqid = get_unaligned_le16(&command->rqid);

	trace_ssam_rx_response_received(command, command_data->len);

	/*
	 * Get request from pending based on request ID and mark it as response
	 * received and locked.
	 */
	spin_lock(&rtl->pending.lock);
	list_क्रम_each_entry_safe(p, n, &rtl->pending.head, node) अणु
		/* We generally expect requests to be processed in order. */
		अगर (unlikely(ssh_request_get_rqid(p) != rqid))
			जारी;

		/* Simulate response समयout. */
		अगर (ssh_rtl_should_drop_response()) अणु
			spin_unlock(&rtl->pending.lock);

			trace_ssam_ei_rx_drop_response(p);
			rtl_info(rtl, "request error injection: dropping response for request %p\n",
				 &p->packet);
			वापस;
		पूर्ण

		/*
		 * Mark as "response received" and "locked" as we're going to
		 * complete it.
		 */
		set_bit(SSH_REQUEST_SF_LOCKED_BIT, &p->state);
		set_bit(SSH_REQUEST_SF_RSPRCVD_BIT, &p->state);
		/* Ensure state never माला_लो zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_REQUEST_SF_PENDING_BIT, &p->state);

		atomic_dec(&rtl->pending.count);
		list_del(&p->node);

		r = p;
		अवरोध;
	पूर्ण
	spin_unlock(&rtl->pending.lock);

	अगर (!r) अणु
		rtl_warn(rtl, "rtl: dropping unexpected command message (rqid = %#06x)\n",
			 rqid);
		वापस;
	पूर्ण

	/* If the request hasn't been completed yet, we will करो this now. */
	अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state)) अणु
		ssh_request_put(r);
		ssh_rtl_tx_schedule(rtl);
		वापस;
	पूर्ण

	/*
	 * Make sure the request has been transmitted. In हाल of a sequenced
	 * request, we are guaranteed that the completion callback will run on
	 * the receiver thपढ़ो directly when the ACK क्रम the packet has been
	 * received. Similarly, this function is guaranteed to run on the
	 * receiver thपढ़ो. Thus we are guaranteed that अगर the packet has been
	 * successfully transmitted and received an ACK, the transmitted flag
	 * has been set and is visible here.
	 *
	 * We are currently not handling unsequenced packets here, as those
	 * should never expect a response as ensured in ssh_rtl_submit. If this
	 * ever changes, one would have to test क्रम
	 *
	 *	(r->state & (transmitting | transmitted))
	 *
	 * on unsequenced packets to determine अगर they could have been
	 * transmitted. There are no synchronization guarantees as in the
	 * sequenced हाल, since, in this हाल, the callback function will not
	 * run on the same thपढ़ो. Thus an exact determination is impossible.
	 */
	अगर (!test_bit(SSH_REQUEST_SF_TRANSMITTED_BIT, &r->state)) अणु
		rtl_err(rtl, "rtl: received response before ACK for request (rqid = %#06x)\n",
			rqid);

		/*
		 * NB: Timeout has alपढ़ोy been canceled, request alपढ़ोy been
		 * हटाओd from pending and marked as locked and completed. As
		 * we receive a "false" response, the packet might still be
		 * queued though.
		 */
		ssh_rtl_queue_हटाओ(r);

		ssh_rtl_complete_with_status(r, -EREMOTEIO);
		ssh_request_put(r);

		ssh_rtl_tx_schedule(rtl);
		वापस;
	पूर्ण

	/*
	 * NB: Timeout has alपढ़ोy been canceled, request alपढ़ोy been
	 * हटाओd from pending and marked as locked and completed. The request
	 * can also not be queued any more, as it has been marked as
	 * transmitting and later transmitted. Thus no need to हटाओ it from
	 * anywhere.
	 */

	ssh_rtl_complete_with_rsp(r, command, command_data);
	ssh_request_put(r);

	ssh_rtl_tx_schedule(rtl);
पूर्ण

अटल bool ssh_rtl_cancel_nonpending(काष्ठा ssh_request *r)
अणु
	काष्ठा ssh_rtl *rtl;
	अचिन्हित दीर्घ flags, fixed;
	bool हटाओ;

	/*
	 * Handle unsubmitted request: Try to mark the packet as locked,
	 * expecting the state to be zero (i.e. unsubmitted). Note that, अगर
	 * setting the state worked, we might still be adding the packet to the
	 * queue in a currently executing submit call. In that हाल, however,
	 * ptl reference must have been set previously, as locked is checked
	 * after setting ptl. Furthermore, when the ptl reference is set, the
	 * submission process is guaranteed to have entered the critical
	 * section. Thus only अगर we successfully locked this request and ptl is
	 * शून्य, we have successfully हटाओd the request, i.e. we are
	 * guaranteed that, due to the "locked" check in ssh_rtl_submit(), the
	 * packet will never be added. Otherwise, we need to try and grab it
	 * from the queue, where we are now guaranteed that the packet is or has
	 * been due to the critical section.
	 *
	 * Note that अगर the cmpxchg() fails, we are guaranteed that ptl has
	 * been set and is non-शून्य, as states can only be nonzero after this
	 * has been set. Also note that we need to fetch the अटल (type)
	 * flags to ensure that they करोn't cause the cmpxchg() to fail.
	 */
	fixed = READ_ONCE(r->state) & SSH_REQUEST_FLAGS_TY_MASK;
	flags = cmpxchg(&r->state, fixed, SSH_REQUEST_SF_LOCKED_BIT);

	/*
	 * Force correct ordering with regards to state and ptl reference access
	 * to safe-guard cancellation to concurrent submission against a
	 * lost-update problem. First try to exchange state, then also check
	 * ptl अगर that worked. This barrier is paired with the
	 * one in ssh_rtl_submit().
	 */
	smp_mb__after_atomic();

	अगर (flags == fixed && !READ_ONCE(r->packet.ptl)) अणु
		अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
			वापस true;

		ssh_rtl_complete_with_status(r, -ECANCELED);
		वापस true;
	पूर्ण

	rtl = ssh_request_rtl(r);
	spin_lock(&rtl->queue.lock);

	/*
	 * Note: 1) Requests cannot be re-submitted. 2) If a request is
	 * queued, it cannot be "transmitting"/"pending" yet. Thus, अगर we
	 * successfully हटाओ the request here, we have हटाओd all its
	 * occurrences in the प्रणाली.
	 */

	हटाओ = test_and_clear_bit(SSH_REQUEST_SF_QUEUED_BIT, &r->state);
	अगर (!हटाओ) अणु
		spin_unlock(&rtl->queue.lock);
		वापस false;
	पूर्ण

	set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state);
	list_del(&r->node);

	spin_unlock(&rtl->queue.lock);

	ssh_request_put(r);	/* Drop reference obtained from queue. */

	अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
		वापस true;

	ssh_rtl_complete_with_status(r, -ECANCELED);
	वापस true;
पूर्ण

अटल bool ssh_rtl_cancel_pending(काष्ठा ssh_request *r)
अणु
	/* If the packet is alपढ़ोy locked, it's going to be हटाओd लघुly. */
	अगर (test_and_set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state))
		वापस true;

	/*
	 * Now that we have locked the packet, we have guaranteed that it can't
	 * be added to the प्रणाली any more. If ptl is शून्य, the locked
	 * check in ssh_rtl_submit() has not been run and any submission,
	 * currently in progress or called later, won't add the packet. Thus we
	 * can directly complete it.
	 *
	 * The implicit memory barrier of test_and_set_bit() should be enough
	 * to ensure that the correct order (first lock, then check ptl) is
	 * ensured. This is paired with the barrier in ssh_rtl_submit().
	 */
	अगर (!READ_ONCE(r->packet.ptl)) अणु
		अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
			वापस true;

		ssh_rtl_complete_with_status(r, -ECANCELED);
		वापस true;
	पूर्ण

	/*
	 * Try to cancel the packet. If the packet has not been completed yet,
	 * this will subsequently (and synchronously) call the completion
	 * callback of the packet, which will complete the request.
	 */
	ssh_ptl_cancel(&r->packet);

	/*
	 * If the packet has been completed with success, i.e. has not been
	 * canceled by the above call, the request may not have been completed
	 * yet (may be रुकोing क्रम a response). Check अगर we need to करो this
	 * here.
	 */
	अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
		वापस true;

	ssh_rtl_queue_हटाओ(r);
	ssh_rtl_pending_हटाओ(r);
	ssh_rtl_complete_with_status(r, -ECANCELED);

	वापस true;
पूर्ण

/**
 * ssh_rtl_cancel() - Cancel request.
 * @rqst:    The request to cancel.
 * @pending: Whether to also cancel pending requests.
 *
 * Cancels the given request. If @pending is %false, this will not cancel
 * pending requests, i.e. requests that have alपढ़ोy been submitted to the
 * packet layer but not been completed yet. If @pending is %true, this will
 * cancel the given request regardless of the state it is in.
 *
 * If the request has been canceled by calling this function, both completion
 * and release callbacks of the request will be executed in a reasonable
 * समय-frame. This may happen during execution of this function, however,
 * there is no guarantee क्रम this. For example, a request currently
 * transmitting will be canceled/completed only after transmission has
 * completed, and the respective callbacks will be executed on the transmitter
 * thपढ़ो, which may happen during, but also some समय after execution of the
 * cancel function.
 *
 * Return: Returns %true अगर the given request has been canceled or completed,
 * either by this function or prior to calling this function, %false
 * otherwise. If @pending is %true, this function will always वापस %true.
 */
bool ssh_rtl_cancel(काष्ठा ssh_request *rqst, bool pending)
अणु
	काष्ठा ssh_rtl *rtl;
	bool canceled;

	अगर (test_and_set_bit(SSH_REQUEST_SF_CANCELED_BIT, &rqst->state))
		वापस true;

	trace_ssam_request_cancel(rqst);

	अगर (pending)
		canceled = ssh_rtl_cancel_pending(rqst);
	अन्यथा
		canceled = ssh_rtl_cancel_nonpending(rqst);

	/* Note: rtl may be शून्य अगर request has not been submitted yet. */
	rtl = ssh_request_rtl(rqst);
	अगर (canceled && rtl)
		ssh_rtl_tx_schedule(rtl);

	वापस canceled;
पूर्ण

अटल व्योम ssh_rtl_packet_callback(काष्ठा ssh_packet *p, पूर्णांक status)
अणु
	काष्ठा ssh_request *r = to_ssh_request(p);

	अगर (unlikely(status)) अणु
		set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state);

		अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
			वापस;

		/*
		 * The packet may get canceled even though it has not been
		 * submitted yet. The request may still be queued. Check the
		 * queue and हटाओ it अगर necessary. As the समयout would have
		 * been started in this function on success, there's no need
		 * to cancel it here.
		 */
		ssh_rtl_queue_हटाओ(r);
		ssh_rtl_pending_हटाओ(r);
		ssh_rtl_complete_with_status(r, status);

		ssh_rtl_tx_schedule(ssh_request_rtl(r));
		वापस;
	पूर्ण

	/* Update state: Mark as transmitted and clear transmitting. */
	set_bit(SSH_REQUEST_SF_TRANSMITTED_BIT, &r->state);
	/* Ensure state never माला_लो zero. */
	smp_mb__beक्रमe_atomic();
	clear_bit(SSH_REQUEST_SF_TRANSMITTING_BIT, &r->state);

	/* If we expect a response, we just need to start the समयout. */
	अगर (test_bit(SSH_REQUEST_TY_HAS_RESPONSE_BIT, &r->state)) अणु
		/*
		 * Note: This is the only place where the बारtamp माला_लो set,
		 * all other access to it is पढ़ो-only.
		 */
		ssh_rtl_समयout_start(r);
		वापस;
	पूर्ण

	/*
	 * If we करोn't expect a response, lock, हटाओ, and complete the
	 * request. Note that, at this poपूर्णांक, the request is guaranteed to have
	 * left the queue and no समयout has been started. Thus we only need to
	 * हटाओ it from pending. If the request has alपढ़ोy been completed (it
	 * may have been canceled) वापस.
	 */

	set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state);
	अगर (test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
		वापस;

	ssh_rtl_pending_हटाओ(r);
	ssh_rtl_complete_with_status(r, 0);

	ssh_rtl_tx_schedule(ssh_request_rtl(r));
पूर्ण

अटल kसमय_प्रकार ssh_request_get_expiration(काष्ठा ssh_request *r, kसमय_प्रकार समयout)
अणु
	kसमय_प्रकार बारtamp = READ_ONCE(r->बारtamp);

	अगर (बारtamp != KTIME_MAX)
		वापस kसमय_add(बारtamp, समयout);
	अन्यथा
		वापस KTIME_MAX;
पूर्ण

अटल व्योम ssh_rtl_समयout_reap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssh_rtl *rtl = to_ssh_rtl(work, rtx_समयout.reaper.work);
	काष्ठा ssh_request *r, *n;
	LIST_HEAD(claimed);
	kसमय_प्रकार now = kसमय_get_coarse_bootसमय();
	kसमय_प्रकार समयout = rtl->rtx_समयout.समयout;
	kसमय_प्रकार next = KTIME_MAX;

	trace_ssam_rtl_समयout_reap(atomic_पढ़ो(&rtl->pending.count));

	/*
	 * Mark reaper as "not pending". This is करोne beक्रमe checking any
	 * requests to aव्योम lost-update type problems.
	 */
	spin_lock(&rtl->rtx_समयout.lock);
	rtl->rtx_समयout.expires = KTIME_MAX;
	spin_unlock(&rtl->rtx_समयout.lock);

	spin_lock(&rtl->pending.lock);
	list_क्रम_each_entry_safe(r, n, &rtl->pending.head, node) अणु
		kसमय_प्रकार expires = ssh_request_get_expiration(r, समयout);

		/*
		 * Check अगर the समयout hasn't expired yet. Find out next
		 * expiration date to be handled after this run.
		 */
		अगर (kसमय_after(expires, now)) अणु
			next = kसमय_beक्रमe(expires, next) ? expires : next;
			जारी;
		पूर्ण

		/* Aव्योम further transitions अगर locked. */
		अगर (test_and_set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state))
			जारी;

		/*
		 * We have now marked the packet as locked. Thus it cannot be
		 * added to the pending or queued lists again after we've
		 * हटाओd it here. We can thereक्रमe re-use the node of this
		 * packet temporarily.
		 */

		clear_bit(SSH_REQUEST_SF_PENDING_BIT, &r->state);

		atomic_dec(&rtl->pending.count);
		list_del(&r->node);

		list_add_tail(&r->node, &claimed);
	पूर्ण
	spin_unlock(&rtl->pending.lock);

	/* Cancel and complete the request. */
	list_क्रम_each_entry_safe(r, n, &claimed, node) अणु
		trace_ssam_request_समयout(r);

		/*
		 * At this poपूर्णांक we've हटाओd the packet from pending. This
		 * means that we've obtained the last (only) reference of the
		 * प्रणाली to it. Thus we can just complete it.
		 */
		अगर (!test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
			ssh_rtl_complete_with_status(r, -ETIMEDOUT);

		/*
		 * Drop the reference we've obtained by removing it from the
		 * pending set.
		 */
		list_del(&r->node);
		ssh_request_put(r);
	पूर्ण

	/* Ensure that the reaper करोesn't run again immediately. */
	next = max(next, kसमय_add(now, SSH_RTL_REQUEST_TIMEOUT_RESOLUTION));
	अगर (next != KTIME_MAX)
		ssh_rtl_समयout_reaper_mod(rtl, now, next);

	ssh_rtl_tx_schedule(rtl);
पूर्ण

अटल व्योम ssh_rtl_rx_event(काष्ठा ssh_rtl *rtl, स्थिर काष्ठा ssh_command *cmd,
			     स्थिर काष्ठा ssam_span *data)
अणु
	trace_ssam_rx_event_received(cmd, data->len);

	rtl_dbg(rtl, "rtl: handling event (rqid: %#06x)\n",
		get_unaligned_le16(&cmd->rqid));

	rtl->ops.handle_event(rtl, cmd, data);
पूर्ण

अटल व्योम ssh_rtl_rx_command(काष्ठा ssh_ptl *p, स्थिर काष्ठा ssam_span *data)
अणु
	काष्ठा ssh_rtl *rtl = to_ssh_rtl(p, ptl);
	काष्ठा device *dev = &p->serdev->dev;
	काष्ठा ssh_command *command;
	काष्ठा ssam_span command_data;

	अगर (sshp_parse_command(dev, data, &command, &command_data))
		वापस;

	अगर (ssh_rqid_is_event(get_unaligned_le16(&command->rqid)))
		ssh_rtl_rx_event(rtl, command, &command_data);
	अन्यथा
		ssh_rtl_complete(rtl, command, &command_data);
पूर्ण

अटल व्योम ssh_rtl_rx_data(काष्ठा ssh_ptl *p, स्थिर काष्ठा ssam_span *data)
अणु
	अगर (!data->len) अणु
		ptl_err(p, "rtl: rx: no data frame payload\n");
		वापस;
	पूर्ण

	चयन (data->ptr[0]) अणु
	हाल SSH_PLD_TYPE_CMD:
		ssh_rtl_rx_command(p, data);
		अवरोध;

	शेष:
		ptl_err(p, "rtl: rx: unknown frame payload type (type: %#04x)\n",
			data->ptr[0]);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ssh_rtl_packet_release(काष्ठा ssh_packet *p)
अणु
	काष्ठा ssh_request *rqst;

	rqst = to_ssh_request(p);
	rqst->ops->release(rqst);
पूर्ण

अटल स्थिर काष्ठा ssh_packet_ops ssh_rtl_packet_ops = अणु
	.complete = ssh_rtl_packet_callback,
	.release = ssh_rtl_packet_release,
पूर्ण;

/**
 * ssh_request_init() - Initialize SSH request.
 * @rqst:  The request to initialize.
 * @flags: Request flags, determining the type of the request.
 * @ops:   Request operations.
 *
 * Initializes the given SSH request and underlying packet. Sets the message
 * buffer poपूर्णांकer to %शून्य and the message buffer length to zero. This buffer
 * has to be set separately via ssh_request_set_data() beक्रमe submission and
 * must contain a valid SSH request message.
 *
 * Return: Returns zero on success or %-EINVAL अगर the given flags are invalid.
 */
पूर्णांक ssh_request_init(काष्ठा ssh_request *rqst, क्रमागत ssam_request_flags flags,
		     स्थिर काष्ठा ssh_request_ops *ops)
अणु
	अचिन्हित दीर्घ type = BIT(SSH_PACKET_TY_BLOCKING_BIT);

	/* Unsequenced requests cannot have a response. */
	अगर (flags & SSAM_REQUEST_UNSEQUENCED && flags & SSAM_REQUEST_HAS_RESPONSE)
		वापस -EINVAL;

	अगर (!(flags & SSAM_REQUEST_UNSEQUENCED))
		type |= BIT(SSH_PACKET_TY_SEQUENCED_BIT);

	ssh_packet_init(&rqst->packet, type, SSH_PACKET_PRIORITY(DATA, 0),
			&ssh_rtl_packet_ops);

	INIT_LIST_HEAD(&rqst->node);

	rqst->state = 0;
	अगर (flags & SSAM_REQUEST_HAS_RESPONSE)
		rqst->state |= BIT(SSH_REQUEST_TY_HAS_RESPONSE_BIT);

	rqst->बारtamp = KTIME_MAX;
	rqst->ops = ops;

	वापस 0;
पूर्ण

/**
 * ssh_rtl_init() - Initialize request transport layer.
 * @rtl:    The request transport layer to initialize.
 * @serdev: The underlying serial device, i.e. the lower-level transport.
 * @ops:    Request transport layer operations.
 *
 * Initializes the given request transport layer and associated packet
 * transport layer. Transmitter and receiver thपढ़ोs must be started
 * separately via ssh_rtl_start(), after the request-layer has been
 * initialized and the lower-level serial device layer has been set up.
 *
 * Return: Returns zero on success and a nonzero error code on failure.
 */
पूर्णांक ssh_rtl_init(काष्ठा ssh_rtl *rtl, काष्ठा serdev_device *serdev,
		 स्थिर काष्ठा ssh_rtl_ops *ops)
अणु
	काष्ठा ssh_ptl_ops ptl_ops;
	पूर्णांक status;

	ptl_ops.data_received = ssh_rtl_rx_data;

	status = ssh_ptl_init(&rtl->ptl, serdev, &ptl_ops);
	अगर (status)
		वापस status;

	spin_lock_init(&rtl->queue.lock);
	INIT_LIST_HEAD(&rtl->queue.head);

	spin_lock_init(&rtl->pending.lock);
	INIT_LIST_HEAD(&rtl->pending.head);
	atomic_set_release(&rtl->pending.count, 0);

	INIT_WORK(&rtl->tx.work, ssh_rtl_tx_work_fn);

	spin_lock_init(&rtl->rtx_समयout.lock);
	rtl->rtx_समयout.समयout = SSH_RTL_REQUEST_TIMEOUT;
	rtl->rtx_समयout.expires = KTIME_MAX;
	INIT_DELAYED_WORK(&rtl->rtx_समयout.reaper, ssh_rtl_समयout_reap);

	rtl->ops = *ops;

	वापस 0;
पूर्ण

/**
 * ssh_rtl_destroy() - Deinitialize request transport layer.
 * @rtl: The request transport layer to deinitialize.
 *
 * Deinitializes the given request transport layer and मुक्तs resources
 * associated with it. If receiver and/or transmitter thपढ़ोs have been
 * started, the layer must first be shut करोwn via ssh_rtl_shutकरोwn() beक्रमe
 * this function can be called.
 */
व्योम ssh_rtl_destroy(काष्ठा ssh_rtl *rtl)
अणु
	ssh_ptl_destroy(&rtl->ptl);
पूर्ण

/**
 * ssh_rtl_start() - Start request transmitter and receiver.
 * @rtl: The request transport layer.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssh_rtl_start(काष्ठा ssh_rtl *rtl)
अणु
	पूर्णांक status;

	status = ssh_ptl_tx_start(&rtl->ptl);
	अगर (status)
		वापस status;

	ssh_rtl_tx_schedule(rtl);

	status = ssh_ptl_rx_start(&rtl->ptl);
	अगर (status) अणु
		ssh_rtl_flush(rtl, msecs_to_jअगरfies(5000));
		ssh_ptl_tx_stop(&rtl->ptl);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ssh_flush_request अणु
	काष्ठा ssh_request base;
	काष्ठा completion completion;
	पूर्णांक status;
पूर्ण;

अटल व्योम ssh_rtl_flush_request_complete(काष्ठा ssh_request *r,
					   स्थिर काष्ठा ssh_command *cmd,
					   स्थिर काष्ठा ssam_span *data,
					   पूर्णांक status)
अणु
	काष्ठा ssh_flush_request *rqst;

	rqst = container_of(r, काष्ठा ssh_flush_request, base);
	rqst->status = status;
पूर्ण

अटल व्योम ssh_rtl_flush_request_release(काष्ठा ssh_request *r)
अणु
	काष्ठा ssh_flush_request *rqst;

	rqst = container_of(r, काष्ठा ssh_flush_request, base);
	complete_all(&rqst->completion);
पूर्ण

अटल स्थिर काष्ठा ssh_request_ops ssh_rtl_flush_request_ops = अणु
	.complete = ssh_rtl_flush_request_complete,
	.release = ssh_rtl_flush_request_release,
पूर्ण;

/**
 * ssh_rtl_flush() - Flush the request transport layer.
 * @rtl:     request transport layer
 * @समयout: समयout क्रम the flush operation in jअगरfies
 *
 * Queue a special flush request and रुको क्रम its completion. This request
 * will be completed after all other currently queued and pending requests
 * have been completed. Instead of a normal data packet, this request submits
 * a special flush packet, meaning that upon completion, also the underlying
 * packet transport layer has been flushed.
 *
 * Flushing the request layer guarantees that all previously submitted
 * requests have been fully completed beक्रमe this call वापसs. Additionally,
 * flushing blocks execution of all later submitted requests until the flush
 * has been completed.
 *
 * If the caller ensures that no new requests are submitted after a call to
 * this function, the request transport layer is guaranteed to have no
 * reमुख्यing requests when this call वापसs. The same guarantee करोes not hold
 * क्रम the packet layer, on which control packets may still be queued after
 * this call.
 *
 * Return: Returns zero on success, %-ETIMEDOUT अगर the flush समयd out and has
 * been canceled as a result of the समयout, or %-ESHUTDOWN अगर the packet
 * and/or request transport layer has been shut करोwn beक्रमe this call. May
 * also वापस %-EINTR अगर the underlying packet transmission has been
 * पूर्णांकerrupted.
 */
पूर्णांक ssh_rtl_flush(काष्ठा ssh_rtl *rtl, अचिन्हित दीर्घ समयout)
अणु
	स्थिर अचिन्हित पूर्णांक init_flags = SSAM_REQUEST_UNSEQUENCED;
	काष्ठा ssh_flush_request rqst;
	पूर्णांक status;

	ssh_request_init(&rqst.base, init_flags, &ssh_rtl_flush_request_ops);
	rqst.base.packet.state |= BIT(SSH_PACKET_TY_FLUSH_BIT);
	rqst.base.packet.priority = SSH_PACKET_PRIORITY(FLUSH, 0);
	rqst.base.state |= BIT(SSH_REQUEST_TY_FLUSH_BIT);

	init_completion(&rqst.completion);

	status = ssh_rtl_submit(rtl, &rqst.base);
	अगर (status)
		वापस status;

	ssh_request_put(&rqst.base);

	अगर (!रुको_क्रम_completion_समयout(&rqst.completion, समयout)) अणु
		ssh_rtl_cancel(&rqst.base, true);
		रुको_क्रम_completion(&rqst.completion);
	पूर्ण

	WARN_ON(rqst.status != 0 && rqst.status != -ECANCELED &&
		rqst.status != -ESHUTDOWN && rqst.status != -EINTR);

	वापस rqst.status == -ECANCELED ? -ETIMEDOUT : rqst.status;
पूर्ण

/**
 * ssh_rtl_shutकरोwn() - Shut करोwn request transport layer.
 * @rtl: The request transport layer.
 *
 * Shuts करोwn the request transport layer, removing and canceling all queued
 * and pending requests. Requests canceled by this operation will be completed
 * with %-ESHUTDOWN as status. Receiver and transmitter thपढ़ोs will be
 * stopped, the lower-level packet layer will be shutकरोwn.
 *
 * As a result of this function, the transport layer will be marked as shut
 * करोwn. Submission of requests after the transport layer has been shut करोwn
 * will fail with %-ESHUTDOWN.
 */
व्योम ssh_rtl_shutकरोwn(काष्ठा ssh_rtl *rtl)
अणु
	काष्ठा ssh_request *r, *n;
	LIST_HEAD(claimed);
	पूर्णांक pending;

	set_bit(SSH_RTL_SF_SHUTDOWN_BIT, &rtl->state);
	/*
	 * Ensure that the layer माला_लो marked as shut-करोwn beक्रमe actually
	 * stopping it. In combination with the check in ssh_rtl_submit(),
	 * this guarantees that no new requests can be added and all alपढ़ोy
	 * queued requests are properly canceled.
	 */
	smp_mb__after_atomic();

	/* Remove requests from queue. */
	spin_lock(&rtl->queue.lock);
	list_क्रम_each_entry_safe(r, n, &rtl->queue.head, node) अणु
		set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state);
		/* Ensure state never माला_लो zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_REQUEST_SF_QUEUED_BIT, &r->state);

		list_del(&r->node);
		list_add_tail(&r->node, &claimed);
	पूर्ण
	spin_unlock(&rtl->queue.lock);

	/*
	 * We have now guaranteed that the queue is empty and no more new
	 * requests can be submitted (i.e. it will stay empty). This means that
	 * calling ssh_rtl_tx_schedule() will not schedule tx.work any more. So
	 * we can simply call cancel_work_sync() on tx.work here and when that
	 * वापसs, we've locked it करोwn. This also means that after this call,
	 * we करोn't submit any more packets to the underlying packet layer, so
	 * we can also shut that करोwn.
	 */

	cancel_work_sync(&rtl->tx.work);
	ssh_ptl_shutकरोwn(&rtl->ptl);
	cancel_delayed_work_sync(&rtl->rtx_समयout.reaper);

	/*
	 * Shutting करोwn the packet layer should also have canceled all
	 * requests. Thus the pending set should be empty. Attempt to handle
	 * this gracefully anyways, even though this should be dead code.
	 */

	pending = atomic_पढ़ो(&rtl->pending.count);
	अगर (WARN_ON(pending)) अणु
		spin_lock(&rtl->pending.lock);
		list_क्रम_each_entry_safe(r, n, &rtl->pending.head, node) अणु
			set_bit(SSH_REQUEST_SF_LOCKED_BIT, &r->state);
			/* Ensure state never माला_लो zero. */
			smp_mb__beक्रमe_atomic();
			clear_bit(SSH_REQUEST_SF_PENDING_BIT, &r->state);

			list_del(&r->node);
			list_add_tail(&r->node, &claimed);
		पूर्ण
		spin_unlock(&rtl->pending.lock);
	पूर्ण

	/* Finally, cancel and complete the requests we claimed beक्रमe. */
	list_क्रम_each_entry_safe(r, n, &claimed, node) अणु
		/*
		 * We need test_and_set() because we still might compete with
		 * cancellation.
		 */
		अगर (!test_and_set_bit(SSH_REQUEST_SF_COMPLETED_BIT, &r->state))
			ssh_rtl_complete_with_status(r, -ESHUTDOWN);

		/*
		 * Drop the reference we've obtained by removing it from the
		 * lists.
		 */
		list_del(&r->node);
		ssh_request_put(r);
	पूर्ण
पूर्ण
