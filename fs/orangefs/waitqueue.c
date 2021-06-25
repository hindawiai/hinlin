<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 * (C) 2011 Omnibond Systems
 *
 * Changes by Acxiom Corporation to implement generic service_operation()
 * function, Copyright Acxiom Corporation, 2005.
 *
 * See COPYING in top-level directory.
 */

/*
 *  In-kernel रुकोqueue operations.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"

अटल पूर्णांक रुको_क्रम_matching_करोwncall(काष्ठा orangefs_kernel_op_s *op,
		दीर्घ समयout,
		पूर्णांक flags)
			__acquires(op->lock);
अटल व्योम orangefs_clean_up_पूर्णांकerrupted_operation(काष्ठा orangefs_kernel_op_s *op)
	__releases(op->lock);

/*
 * What we करो in this function is to walk the list of operations that are
 * present in the request queue and mark them as purged.
 * NOTE: This is called from the device बंद after client-core has
 * guaranteed that no new operations could appear on the list since the
 * client-core is anyway going to निकास.
 */
व्योम purge_रुकोing_ops(व्योम)
अणु
	काष्ठा orangefs_kernel_op_s *op, *पंचांगp;

	spin_lock(&orangefs_request_list_lock);
	list_क्रम_each_entry_safe(op, पंचांगp, &orangefs_request_list, list) अणु
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "pvfs2-client-core: purging op tag %llu %s\n",
			     llu(op->tag),
			     get_opname_string(op));
		set_op_state_purged(op);
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "%s: op:%s: op_state:%d: process:%s:\n",
			     __func__,
			     get_opname_string(op),
			     op->op_state,
			     current->comm);
	पूर्ण
	spin_unlock(&orangefs_request_list_lock);
पूर्ण

/*
 * submits a ORANGEFS operation and रुकोs क्रम it to complete
 *
 * Note op->करोwncall.status will contain the status of the operation (in
 * त्रुटि_सं क्रमmat), whether provided by pvfs2-client or a result of failure to
 * service the operation.  If the caller wishes to distinguish, then
 * op->state can be checked to see अगर it was serviced or not.
 *
 * Returns contents of op->करोwncall.status क्रम convenience
 */
पूर्णांक service_operation(काष्ठा orangefs_kernel_op_s *op,
		      स्थिर अक्षर *op_name,
		      पूर्णांक flags)
अणु
	दीर्घ समयout = MAX_SCHEDULE_TIMEOUT;
	पूर्णांक ret = 0;

	DEFINE_WAIT(रुको_entry);

	op->upcall.tgid = current->tgid;
	op->upcall.pid = current->pid;

retry_servicing:
	op->करोwncall.status = 0;
	gossip_debug(GOSSIP_WAIT_DEBUG,
		     "%s: %s op:%p: process:%s: pid:%d:\n",
		     __func__,
		     op_name,
		     op,
		     current->comm,
		     current->pid);

	/*
	 * If ORANGEFS_OP_NO_MUTEX was set in flags, we need to aव्योम
	 * acquiring the request_mutex because we're servicing a
	 * high priority remount operation and the request_mutex is
	 * alपढ़ोy taken.
	 */
	अगर (!(flags & ORANGEFS_OP_NO_MUTEX)) अणु
		अगर (flags & ORANGEFS_OP_INTERRUPTIBLE)
			ret = mutex_lock_पूर्णांकerruptible(&orangefs_request_mutex);
		अन्यथा
			ret = mutex_lock_समाप्तable(&orangefs_request_mutex);
		/*
		 * check to see अगर we were पूर्णांकerrupted जबतक रुकोing क्रम
		 * mutex
		 */
		अगर (ret < 0) अणु
			op->करोwncall.status = ret;
			gossip_debug(GOSSIP_WAIT_DEBUG,
				     "%s: service_operation interrupted.\n",
				     __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* queue up the operation */
	spin_lock(&orangefs_request_list_lock);
	spin_lock(&op->lock);
	set_op_state_रुकोing(op);
	gossip_debug(GOSSIP_DEV_DEBUG,
		     "%s: op:%s: op_state:%d: process:%s:\n",
		     __func__,
		     get_opname_string(op),
		     op->op_state,
		     current->comm);
	/* add high priority remount op to the front of the line. */
	अगर (flags & ORANGEFS_OP_PRIORITY)
		list_add(&op->list, &orangefs_request_list);
	अन्यथा
		list_add_tail(&op->list, &orangefs_request_list);
	spin_unlock(&op->lock);
	wake_up_पूर्णांकerruptible(&orangefs_request_list_रुकोq);
	अगर (!__is_daemon_in_service()) अणु
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "%s:client core is NOT in service.\n",
			     __func__);
		/*
		 * Don't रुको क्रम the userspace component to वापस अगर
		 * the fileप्रणाली is being umounted anyway.
		 */
		अगर (op->upcall.type == ORANGEFS_VFS_OP_FS_UMOUNT)
			समयout = 0;
		अन्यथा
			समयout = op_समयout_secs * HZ;
	पूर्ण
	spin_unlock(&orangefs_request_list_lock);

	अगर (!(flags & ORANGEFS_OP_NO_MUTEX))
		mutex_unlock(&orangefs_request_mutex);

	ret = रुको_क्रम_matching_करोwncall(op, समयout, flags);
	gossip_debug(GOSSIP_WAIT_DEBUG,
		     "%s: wait_for_matching_downcall returned %d for %p\n",
		     __func__,
		     ret,
		     op);

	/* got matching करोwncall; make sure status is in त्रुटि_सं क्रमmat */
	अगर (!ret) अणु
		spin_unlock(&op->lock);
		op->करोwncall.status =
		    orangefs_normalize_to_त्रुटि_सं(op->करोwncall.status);
		ret = op->करोwncall.status;
		जाओ out;
	पूर्ण

	/* failed to get matching करोwncall */
	अगर (ret == -ETIMEDOUT) अणु
		gossip_err("%s: %s -- wait timed out; aborting attempt.\n",
			   __func__,
			   op_name);
	पूर्ण

	/*
	 * हटाओ a रुकोing op from the request list or
	 * हटाओ an in-progress op from the in-progress list.
	 */
	orangefs_clean_up_पूर्णांकerrupted_operation(op);

	op->करोwncall.status = ret;
	/* retry अगर operation has not been serviced and अगर requested */
	अगर (ret == -EAGAIN) अणु
		op->attempts++;
		समयout = op_समयout_secs * HZ;
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "orangefs: tag %llu (%s)"
			     " -- operation to be retried (%d attempt)\n",
			     llu(op->tag),
			     op_name,
			     op->attempts);

		/*
		 * io ops (ops that use the shared memory buffer) have
		 * to be वापसed to their caller क्रम a retry. Other ops
		 * can just be recycled here.
		 */
		अगर (!op->uses_shared_memory)
			जाओ retry_servicing;
	पूर्ण

out:
	gossip_debug(GOSSIP_WAIT_DEBUG,
		     "%s: %s returning: %d for %p.\n",
		     __func__,
		     op_name,
		     ret,
		     op);
	वापस ret;
पूर्ण

/* This can get called on an I/O op अगर it had a bad service_operation. */
bool orangefs_cancel_op_in_progress(काष्ठा orangefs_kernel_op_s *op)
अणु
	u64 tag = op->tag;
	अगर (!op_state_in_progress(op))
		वापस false;

	op->slot_to_मुक्त = op->upcall.req.io.buf_index;
	स_रखो(&op->upcall, 0, माप(op->upcall));
	स_रखो(&op->करोwncall, 0, माप(op->करोwncall));
	op->upcall.type = ORANGEFS_VFS_OP_CANCEL;
	op->upcall.req.cancel.op_tag = tag;
	op->करोwncall.type = ORANGEFS_VFS_OP_INVALID;
	op->करोwncall.status = -1;
	orangefs_new_tag(op);

	spin_lock(&orangefs_request_list_lock);
	/* orangefs_request_list_lock is enough of a barrier here */
	अगर (!__is_daemon_in_service()) अणु
		spin_unlock(&orangefs_request_list_lock);
		वापस false;
	पूर्ण
	spin_lock(&op->lock);
	set_op_state_रुकोing(op);
	gossip_debug(GOSSIP_DEV_DEBUG,
		     "%s: op:%s: op_state:%d: process:%s:\n",
		     __func__,
		     get_opname_string(op),
		     op->op_state,
		     current->comm);
	list_add(&op->list, &orangefs_request_list);
	spin_unlock(&op->lock);
	spin_unlock(&orangefs_request_list_lock);

	gossip_debug(GOSSIP_WAIT_DEBUG,
		     "Attempting ORANGEFS operation cancellation of tag %llu\n",
		     llu(tag));
	वापस true;
पूर्ण

/*
 * Change an op to the "given up" state and हटाओ it from its list.
 */
अटल व्योम
	orangefs_clean_up_पूर्णांकerrupted_operation(काष्ठा orangefs_kernel_op_s *op)
		__releases(op->lock)
अणु
	/*
	 * handle पूर्णांकerrupted हालs depending on what state we were in when
	 * the पूर्णांकerruption is detected.
	 *
	 * Called with op->lock held.
	 */

	/*
	 * List manipulation code अन्यथाwhere will ignore ops that
	 * have been given up upon.
	 */
	op->op_state |= OP_VFS_STATE_GIVEN_UP;

	अगर (list_empty(&op->list)) अणु
		/* caught copying to/from daemon */
		BUG_ON(op_state_serviced(op));
		spin_unlock(&op->lock);
		रुको_क्रम_completion(&op->रुकोq);
	पूर्ण अन्यथा अगर (op_state_रुकोing(op)) अणु
		/*
		 * upcall hasn't been पढ़ो; हटाओ op from upcall request
		 * list.
		 */
		spin_unlock(&op->lock);
		spin_lock(&orangefs_request_list_lock);
		list_del_init(&op->list);
		spin_unlock(&orangefs_request_list_lock);
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "Interrupted: Removed op %p from request_list\n",
			     op);
	पूर्ण अन्यथा अगर (op_state_in_progress(op)) अणु
		/* op must be हटाओd from the in progress htable */
		spin_unlock(&op->lock);
		spin_lock(&orangefs_htable_ops_in_progress_lock);
		list_del_init(&op->list);
		spin_unlock(&orangefs_htable_ops_in_progress_lock);
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "Interrupted: Removed op %p"
			     " from htable_ops_in_progress\n",
			     op);
	पूर्ण अन्यथा अणु
		spin_unlock(&op->lock);
		gossip_err("interrupted operation is in a weird state 0x%x\n",
			   op->op_state);
	पूर्ण
	reinit_completion(&op->रुकोq);
पूर्ण

/*
 * Sleeps on रुकोqueue रुकोing क्रम matching करोwncall.
 * If client-core finishes servicing, then we are good to go.
 * अन्यथा अगर client-core निकासs, we get woken up here, and retry with a समयout
 *
 * When this call वापसs to the caller, the specअगरied op will no
 * दीर्घer be in either the in_progress hash table or on the request list.
 *
 * Returns 0 on success and -त्रुटि_सं on failure
 * Errors are:
 * EAGAIN in हाल we want the caller to requeue and try again..
 * EINTR/EIO/ETIMEDOUT indicating we are करोne trying to service this
 * operation since client-core seems to be निकासing too often
 * or अगर we were पूर्णांकerrupted.
 *
 * Returns with op->lock taken.
 */
अटल पूर्णांक रुको_क्रम_matching_करोwncall(काष्ठा orangefs_kernel_op_s *op,
		दीर्घ समयout,
		पूर्णांक flags)
			__acquires(op->lock)
अणु
	दीर्घ n;
	पूर्णांक ग_लिखोback = flags & ORANGEFS_OP_WRITEBACK,
	    पूर्णांकerruptible = flags & ORANGEFS_OP_INTERRUPTIBLE;

	/*
	 * There's a "schedule_timeout" inside of these रुको
	 * primitives, during which the op is out of the hands of the
	 * user process that needs something करोne and is being
	 * manipulated by the client-core process.
	 */
	अगर (ग_लिखोback)
		n = रुको_क्रम_completion_io_समयout(&op->रुकोq, समयout);
	अन्यथा अगर (!ग_लिखोback && पूर्णांकerruptible)
		n = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&op->रुकोq,
								      समयout);
	अन्यथा /* !ग_लिखोback && !पूर्णांकerruptible but compiler complains */
		n = रुको_क्रम_completion_समाप्तable_समयout(&op->रुकोq, समयout);

	spin_lock(&op->lock);

	अगर (op_state_serviced(op))
		वापस 0;

	अगर (unlikely(n < 0)) अणु
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "%s: operation interrupted, tag %llu, %p\n",
			     __func__,
			     llu(op->tag),
			     op);
		वापस -EINTR;
	पूर्ण
	अगर (op_state_purged(op)) अणु
		gossip_debug(GOSSIP_WAIT_DEBUG,
			     "%s: operation purged, tag %llu, %p, %d\n",
			     __func__,
			     llu(op->tag),
			     op,
			     op->attempts);
		वापस (op->attempts < ORANGEFS_PURGE_RETRY_COUNT) ?
			 -EAGAIN :
			 -EIO;
	पूर्ण
	/* must have समयd out, then... */
	gossip_debug(GOSSIP_WAIT_DEBUG,
		     "%s: operation timed out, tag %llu, %p, %d)\n",
		     __func__,
		     llu(op->tag),
		     op,
		     op->attempts);
	वापस -ETIMEDOUT;
पूर्ण
