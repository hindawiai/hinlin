<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/slab.h>

#समावेश "vmci_queue_pair.h"
#समावेश "vmci_datagram.h"
#समावेश "vmci_doorbell.h"
#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"

/* Use a wide upper bound क्रम the maximum contexts. */
#घोषणा VMCI_MAX_CONTEXTS 2000

/*
 * List of current VMCI contexts.  Contexts can be added by
 * vmci_ctx_create() and हटाओd via vmci_ctx_destroy().
 * These, aदीर्घ with context lookup, are रक्षित by the
 * list काष्ठाure's lock.
 */
अटल काष्ठा अणु
	काष्ठा list_head head;
	spinlock_t lock; /* Spinlock क्रम context list operations */
पूर्ण ctx_list = अणु
	.head = LIST_HEAD_INIT(ctx_list.head),
	.lock = __SPIN_LOCK_UNLOCKED(ctx_list.lock),
पूर्ण;

/* Used by contexts that did not set up notअगरy flag poपूर्णांकers */
अटल bool ctx_dummy_notअगरy;

अटल व्योम ctx_संकेत_notअगरy(काष्ठा vmci_ctx *context)
अणु
	*context->notअगरy = true;
पूर्ण

अटल व्योम ctx_clear_notअगरy(काष्ठा vmci_ctx *context)
अणु
	*context->notअगरy = false;
पूर्ण

/*
 * If nothing requires the attention of the guest, clears both
 * notअगरy flag and call.
 */
अटल व्योम ctx_clear_notअगरy_call(काष्ठा vmci_ctx *context)
अणु
	अगर (context->pending_datagrams == 0 &&
	    vmci_handle_arr_get_size(context->pending_करोorbell_array) == 0)
		ctx_clear_notअगरy(context);
पूर्ण

/*
 * Sets the context's notअगरy flag अगरf datagrams are pending क्रम this
 * context.  Called from vmci_setup_notअगरy().
 */
व्योम vmci_ctx_check_संकेत_notअगरy(काष्ठा vmci_ctx *context)
अणु
	spin_lock(&context->lock);
	अगर (context->pending_datagrams)
		ctx_संकेत_notअगरy(context);
	spin_unlock(&context->lock);
पूर्ण

/*
 * Allocates and initializes a VMCI context.
 */
काष्ठा vmci_ctx *vmci_ctx_create(u32 cid, u32 priv_flags,
				 uपूर्णांकptr_t event_hnd,
				 पूर्णांक user_version,
				 स्थिर काष्ठा cred *cred)
अणु
	काष्ठा vmci_ctx *context;
	पूर्णांक error;

	अगर (cid == VMCI_INVALID_ID) अणु
		pr_devel("Invalid context ID for VMCI context\n");
		error = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS) अणु
		pr_devel("Invalid flag (flags=0x%x) for VMCI context\n",
			 priv_flags);
		error = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (user_version == 0) अणु
		pr_devel("Invalid suer_version %d\n", user_version);
		error = -EINVAL;
		जाओ err_out;
	पूर्ण

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context) अणु
		pr_warn("Failed to allocate memory for VMCI context\n");
		error = -EINVAL;
		जाओ err_out;
	पूर्ण

	kref_init(&context->kref);
	spin_lock_init(&context->lock);
	INIT_LIST_HEAD(&context->list_item);
	INIT_LIST_HEAD(&context->datagram_queue);
	INIT_LIST_HEAD(&context->notअगरier_list);

	/* Initialize host-specअगरic VMCI context. */
	init_रुकोqueue_head(&context->host_context.रुको_queue);

	context->queue_pair_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_QP_COUNT);
	अगर (!context->queue_pair_array) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_ctx;
	पूर्ण

	context->करोorbell_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_DOORBELL_COUNT);
	अगर (!context->करोorbell_array) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_qp_array;
	पूर्ण

	context->pending_करोorbell_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_DOORBELL_COUNT);
	अगर (!context->pending_करोorbell_array) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_db_array;
	पूर्ण

	context->user_version = user_version;

	context->priv_flags = priv_flags;

	अगर (cred)
		context->cred = get_cred(cred);

	context->notअगरy = &ctx_dummy_notअगरy;
	context->notअगरy_page = शून्य;

	/*
	 * If we collide with an existing context we generate a new
	 * and use it instead. The VMX will determine अगर regeneration
	 * is okay. Since there isn't 4B - 16 VMs running on a given
	 * host, the below loop will terminate.
	 */
	spin_lock(&ctx_list.lock);

	जबतक (vmci_ctx_exists(cid)) अणु
		/* We reserve the lowest 16 ids क्रम fixed contexts. */
		cid = max(cid, VMCI_RESERVED_CID_LIMIT - 1) + 1;
		अगर (cid == VMCI_INVALID_ID)
			cid = VMCI_RESERVED_CID_LIMIT;
	पूर्ण
	context->cid = cid;

	list_add_tail_rcu(&context->list_item, &ctx_list.head);
	spin_unlock(&ctx_list.lock);

	वापस context;

 err_मुक्त_db_array:
	vmci_handle_arr_destroy(context->करोorbell_array);
 err_मुक्त_qp_array:
	vmci_handle_arr_destroy(context->queue_pair_array);
 err_मुक्त_ctx:
	kमुक्त(context);
 err_out:
	वापस ERR_PTR(error);
पूर्ण

/*
 * Destroy VMCI context.
 */
व्योम vmci_ctx_destroy(काष्ठा vmci_ctx *context)
अणु
	spin_lock(&ctx_list.lock);
	list_del_rcu(&context->list_item);
	spin_unlock(&ctx_list.lock);
	synchronize_rcu();

	vmci_ctx_put(context);
पूर्ण

/*
 * Fire notअगरication क्रम all contexts पूर्णांकerested in given cid.
 */
अटल पूर्णांक ctx_fire_notअगरication(u32 context_id, u32 priv_flags)
अणु
	u32 i, array_size;
	काष्ठा vmci_ctx *sub_ctx;
	काष्ठा vmci_handle_arr *subscriber_array;
	काष्ठा vmci_handle context_handle =
		vmci_make_handle(context_id, VMCI_EVENT_HANDLER);

	/*
	 * We create an array to hold the subscribers we find when
	 * scanning through all contexts.
	 */
	subscriber_array = vmci_handle_arr_create(0, VMCI_MAX_CONTEXTS);
	अगर (subscriber_array == शून्य)
		वापस VMCI_ERROR_NO_MEM;

	/*
	 * Scan all contexts to find who is पूर्णांकerested in being
	 * notअगरied about given contextID.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sub_ctx, &ctx_list.head, list_item) अणु
		काष्ठा vmci_handle_list *node;

		/*
		 * We only deliver notअगरications of the removal of
		 * contexts, अगर the two contexts are allowed to
		 * पूर्णांकeract.
		 */
		अगर (vmci_deny_पूर्णांकeraction(priv_flags, sub_ctx->priv_flags))
			जारी;

		list_क्रम_each_entry_rcu(node, &sub_ctx->notअगरier_list, node) अणु
			अगर (!vmci_handle_is_equal(node->handle, context_handle))
				जारी;

			vmci_handle_arr_append_entry(&subscriber_array,
					vmci_make_handle(sub_ctx->cid,
							 VMCI_EVENT_HANDLER));
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Fire event to all subscribers. */
	array_size = vmci_handle_arr_get_size(subscriber_array);
	क्रम (i = 0; i < array_size; i++) अणु
		पूर्णांक result;
		काष्ठा vmci_event_ctx ev;

		ev.msg.hdr.dst = vmci_handle_arr_get_entry(subscriber_array, i);
		ev.msg.hdr.src = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
						  VMCI_CONTEXT_RESOURCE_ID);
		ev.msg.hdr.payload_size = माप(ev) - माप(ev.msg.hdr);
		ev.msg.event_data.event = VMCI_EVENT_CTX_REMOVED;
		ev.payload.context_id = context_id;

		result = vmci_datagram_dispatch(VMCI_HYPERVISOR_CONTEXT_ID,
						&ev.msg.hdr, false);
		अगर (result < VMCI_SUCCESS) अणु
			pr_devel("Failed to enqueue event datagram (type=%d) for context (ID=0x%x)\n",
				 ev.msg.event_data.event,
				 ev.msg.hdr.dst.context);
			/* We जारी to enqueue on next subscriber. */
		पूर्ण
	पूर्ण
	vmci_handle_arr_destroy(subscriber_array);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Returns the current number of pending datagrams. The call may
 * also serve as a synchronization poपूर्णांक क्रम the datagram queue,
 * as no enqueue operations can occur concurrently.
 */
पूर्णांक vmci_ctx_pending_datagrams(u32 cid, u32 *pending)
अणु
	काष्ठा vmci_ctx *context;

	context = vmci_ctx_get(cid);
	अगर (context == शून्य)
		वापस VMCI_ERROR_INVALID_ARGS;

	spin_lock(&context->lock);
	अगर (pending)
		*pending = context->pending_datagrams;
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Queues a VMCI datagram क्रम the appropriate target VM context.
 */
पूर्णांक vmci_ctx_enqueue_datagram(u32 cid, काष्ठा vmci_datagram *dg)
अणु
	काष्ठा vmci_datagram_queue_entry *dq_entry;
	काष्ठा vmci_ctx *context;
	काष्ठा vmci_handle dg_src;
	माप_प्रकार vmci_dg_size;

	vmci_dg_size = VMCI_DG_SIZE(dg);
	अगर (vmci_dg_size > VMCI_MAX_DG_SIZE) अणु
		pr_devel("Datagram too large (bytes=%zu)\n", vmci_dg_size);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	/* Get the target VM's VMCI context. */
	context = vmci_ctx_get(cid);
	अगर (!context) अणु
		pr_devel("Invalid context (ID=0x%x)\n", cid);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	/* Allocate guest call entry and add it to the target VM's queue. */
	dq_entry = kदो_स्मृति(माप(*dq_entry), GFP_KERNEL);
	अगर (dq_entry == शून्य) अणु
		pr_warn("Failed to allocate memory for datagram\n");
		vmci_ctx_put(context);
		वापस VMCI_ERROR_NO_MEM;
	पूर्ण
	dq_entry->dg = dg;
	dq_entry->dg_size = vmci_dg_size;
	dg_src = dg->src;
	INIT_LIST_HEAD(&dq_entry->list_item);

	spin_lock(&context->lock);

	/*
	 * We put a higher limit on datagrams from the hypervisor.  If
	 * the pending datagram is not from hypervisor, then we check
	 * अगर enqueueing it would exceed the
	 * VMCI_MAX_DATAGRAM_QUEUE_SIZE limit on the destination.  If
	 * the pending datagram is from hypervisor, we allow it to be
	 * queued at the destination side provided we करोn't reach the
	 * VMCI_MAX_DATAGRAM_AND_EVENT_QUEUE_SIZE limit.
	 */
	अगर (context->datagram_queue_size + vmci_dg_size >=
	    VMCI_MAX_DATAGRAM_QUEUE_SIZE &&
	    (!vmci_handle_is_equal(dg_src,
				vmci_make_handle
				(VMCI_HYPERVISOR_CONTEXT_ID,
				 VMCI_CONTEXT_RESOURCE_ID)) ||
	     context->datagram_queue_size + vmci_dg_size >=
	     VMCI_MAX_DATAGRAM_AND_EVENT_QUEUE_SIZE)) अणु
		spin_unlock(&context->lock);
		vmci_ctx_put(context);
		kमुक्त(dq_entry);
		pr_devel("Context (ID=0x%x) receive queue is full\n", cid);
		वापस VMCI_ERROR_NO_RESOURCES;
	पूर्ण

	list_add(&dq_entry->list_item, &context->datagram_queue);
	context->pending_datagrams++;
	context->datagram_queue_size += vmci_dg_size;
	ctx_संकेत_notअगरy(context);
	wake_up(&context->host_context.रुको_queue);
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	वापस vmci_dg_size;
पूर्ण

/*
 * Verअगरies whether a context with the specअगरied context ID exists.
 * FIXME: utility is dubious as no decisions can be reliably made
 * using this data as context can appear and disappear at any समय.
 */
bool vmci_ctx_exists(u32 cid)
अणु
	काष्ठा vmci_ctx *context;
	bool exists = false;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(context, &ctx_list.head, list_item) अणु
		अगर (context->cid == cid) अणु
			exists = true;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस exists;
पूर्ण

/*
 * Retrieves VMCI context corresponding to the given cid.
 */
काष्ठा vmci_ctx *vmci_ctx_get(u32 cid)
अणु
	काष्ठा vmci_ctx *c, *context = शून्य;

	अगर (cid == VMCI_INVALID_ID)
		वापस शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(c, &ctx_list.head, list_item) अणु
		अगर (c->cid == cid) अणु
			/*
			 * The context owner drops its own reference to the
			 * context only after removing it from the list and
			 * रुकोing क्रम RCU grace period to expire. This
			 * means that we are not about to increase the
			 * reference count of something that is in the
			 * process of being destroyed.
			 */
			context = c;
			kref_get(&context->kref);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस context;
पूर्ण

/*
 * Deallocates all parts of a context data काष्ठाure. This
 * function करोesn't lock the context, because it assumes that
 * the caller was holding the last reference to context.
 */
अटल व्योम ctx_मुक्त_ctx(काष्ठा kref *kref)
अणु
	काष्ठा vmci_ctx *context = container_of(kref, काष्ठा vmci_ctx, kref);
	काष्ठा vmci_datagram_queue_entry *dq_entry, *dq_entry_पंचांगp;
	काष्ठा vmci_handle temp_handle;
	काष्ठा vmci_handle_list *notअगरier, *पंचांगp;

	/*
	 * Fire event to all contexts पूर्णांकerested in knowing this
	 * context is dying.
	 */
	ctx_fire_notअगरication(context->cid, context->priv_flags);

	/*
	 * Cleanup all queue pair resources attached to context.  If
	 * the VM dies without cleaning up, this code will make sure
	 * that no resources are leaked.
	 */
	temp_handle = vmci_handle_arr_get_entry(context->queue_pair_array, 0);
	जबतक (!vmci_handle_is_equal(temp_handle, VMCI_INVALID_HANDLE)) अणु
		अगर (vmci_qp_broker_detach(temp_handle,
					  context) < VMCI_SUCCESS) अणु
			/*
			 * When vmci_qp_broker_detach() succeeds it
			 * हटाओs the handle from the array.  If
			 * detach fails, we must हटाओ the handle
			 * ourselves.
			 */
			vmci_handle_arr_हटाओ_entry(context->queue_pair_array,
						     temp_handle);
		पूर्ण
		temp_handle =
		    vmci_handle_arr_get_entry(context->queue_pair_array, 0);
	पूर्ण

	/*
	 * It is fine to destroy this without locking the callQueue, as
	 * this is the only thपढ़ो having a reference to the context.
	 */
	list_क्रम_each_entry_safe(dq_entry, dq_entry_पंचांगp,
				 &context->datagram_queue, list_item) अणु
		WARN_ON(dq_entry->dg_size != VMCI_DG_SIZE(dq_entry->dg));
		list_del(&dq_entry->list_item);
		kमुक्त(dq_entry->dg);
		kमुक्त(dq_entry);
	पूर्ण

	list_क्रम_each_entry_safe(notअगरier, पंचांगp,
				 &context->notअगरier_list, node) अणु
		list_del(&notअगरier->node);
		kमुक्त(notअगरier);
	पूर्ण

	vmci_handle_arr_destroy(context->queue_pair_array);
	vmci_handle_arr_destroy(context->करोorbell_array);
	vmci_handle_arr_destroy(context->pending_करोorbell_array);
	vmci_ctx_unset_notअगरy(context);
	अगर (context->cred)
		put_cred(context->cred);
	kमुक्त(context);
पूर्ण

/*
 * Drops reference to VMCI context. If this is the last reference to
 * the context it will be deallocated. A context is created with
 * a reference count of one, and on destroy, it is हटाओd from
 * the context list beक्रमe its reference count is decremented. Thus,
 * अगर we reach zero, we are sure that nobody अन्यथा are about to increment
 * it (they need the entry in the context list क्रम that), and so there
 * is no need क्रम locking.
 */
व्योम vmci_ctx_put(काष्ठा vmci_ctx *context)
अणु
	kref_put(&context->kref, ctx_मुक्त_ctx);
पूर्ण

/*
 * Dequeues the next datagram and वापसs it to caller.
 * The caller passes in a poपूर्णांकer to the max size datagram
 * it can handle and the datagram is only unqueued अगर the
 * size is less than max_size. If larger max_size is set to
 * the size of the datagram to give the caller a chance to
 * set up a larger buffer क्रम the guestcall.
 */
पूर्णांक vmci_ctx_dequeue_datagram(काष्ठा vmci_ctx *context,
			      माप_प्रकार *max_size,
			      काष्ठा vmci_datagram **dg)
अणु
	काष्ठा vmci_datagram_queue_entry *dq_entry;
	काष्ठा list_head *list_item;
	पूर्णांक rv;

	/* Dequeue the next datagram entry. */
	spin_lock(&context->lock);
	अगर (context->pending_datagrams == 0) अणु
		ctx_clear_notअगरy_call(context);
		spin_unlock(&context->lock);
		pr_devel("No datagrams pending\n");
		वापस VMCI_ERROR_NO_MORE_DATAGRAMS;
	पूर्ण

	list_item = context->datagram_queue.next;

	dq_entry =
	    list_entry(list_item, काष्ठा vmci_datagram_queue_entry, list_item);

	/* Check size of caller's buffer. */
	अगर (*max_size < dq_entry->dg_size) अणु
		*max_size = dq_entry->dg_size;
		spin_unlock(&context->lock);
		pr_devel("Caller's buffer should be at least (size=%u bytes)\n",
			 (u32) *max_size);
		वापस VMCI_ERROR_NO_MEM;
	पूर्ण

	list_del(list_item);
	context->pending_datagrams--;
	context->datagram_queue_size -= dq_entry->dg_size;
	अगर (context->pending_datagrams == 0) अणु
		ctx_clear_notअगरy_call(context);
		rv = VMCI_SUCCESS;
	पूर्ण अन्यथा अणु
		/*
		 * Return the size of the next datagram.
		 */
		काष्ठा vmci_datagram_queue_entry *next_entry;

		list_item = context->datagram_queue.next;
		next_entry =
		    list_entry(list_item, काष्ठा vmci_datagram_queue_entry,
			       list_item);

		/*
		 * The following माप_प्रकार -> पूर्णांक truncation is fine as
		 * the maximum size of a (routable) datagram is 68KB.
		 */
		rv = (पूर्णांक)next_entry->dg_size;
	पूर्ण
	spin_unlock(&context->lock);

	/* Caller must मुक्त datagram. */
	*dg = dq_entry->dg;
	dq_entry->dg = शून्य;
	kमुक्त(dq_entry);

	वापस rv;
पूर्ण

/*
 * Reverts actions set up by vmci_setup_notअगरy().  Unmaps and unlocks the
 * page mapped/locked by vmci_setup_notअगरy().
 */
व्योम vmci_ctx_unset_notअगरy(काष्ठा vmci_ctx *context)
अणु
	काष्ठा page *notअगरy_page;

	spin_lock(&context->lock);

	notअगरy_page = context->notअगरy_page;
	context->notअगरy = &ctx_dummy_notअगरy;
	context->notअगरy_page = शून्य;

	spin_unlock(&context->lock);

	अगर (notअगरy_page) अणु
		kunmap(notअगरy_page);
		put_page(notअगरy_page);
	पूर्ण
पूर्ण

/*
 * Add remote_cid to list of contexts current contexts wants
 * notअगरications from/about.
 */
पूर्णांक vmci_ctx_add_notअगरication(u32 context_id, u32 remote_cid)
अणु
	काष्ठा vmci_ctx *context;
	काष्ठा vmci_handle_list *notअगरier, *n;
	पूर्णांक result;
	bool exists = false;

	context = vmci_ctx_get(context_id);
	अगर (!context)
		वापस VMCI_ERROR_NOT_FOUND;

	अगर (VMCI_CONTEXT_IS_VM(context_id) && VMCI_CONTEXT_IS_VM(remote_cid)) अणु
		pr_devel("Context removed notifications for other VMs not supported (src=0x%x, remote=0x%x)\n",
			 context_id, remote_cid);
		result = VMCI_ERROR_DST_UNREACHABLE;
		जाओ out;
	पूर्ण

	अगर (context->priv_flags & VMCI_PRIVILEGE_FLAG_RESTRICTED) अणु
		result = VMCI_ERROR_NO_ACCESS;
		जाओ out;
	पूर्ण

	notअगरier = kदो_स्मृति(माप(काष्ठा vmci_handle_list), GFP_KERNEL);
	अगर (!notअगरier) अणु
		result = VMCI_ERROR_NO_MEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&notअगरier->node);
	notअगरier->handle = vmci_make_handle(remote_cid, VMCI_EVENT_HANDLER);

	spin_lock(&context->lock);

	अगर (context->n_notअगरiers < VMCI_MAX_CONTEXTS) अणु
		list_क्रम_each_entry(n, &context->notअगरier_list, node) अणु
			अगर (vmci_handle_is_equal(n->handle, notअगरier->handle)) अणु
				exists = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (exists) अणु
			kमुक्त(notअगरier);
			result = VMCI_ERROR_ALREADY_EXISTS;
		पूर्ण अन्यथा अणु
			list_add_tail_rcu(&notअगरier->node,
					  &context->notअगरier_list);
			context->n_notअगरiers++;
			result = VMCI_SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(notअगरier);
		result = VMCI_ERROR_NO_MEM;
	पूर्ण

	spin_unlock(&context->lock);

 out:
	vmci_ctx_put(context);
	वापस result;
पूर्ण

/*
 * Remove remote_cid from current context's list of contexts it is
 * पूर्णांकerested in getting notअगरications from/about.
 */
पूर्णांक vmci_ctx_हटाओ_notअगरication(u32 context_id, u32 remote_cid)
अणु
	काष्ठा vmci_ctx *context;
	काष्ठा vmci_handle_list *notअगरier, *पंचांगp;
	काष्ठा vmci_handle handle;
	bool found = false;

	context = vmci_ctx_get(context_id);
	अगर (!context)
		वापस VMCI_ERROR_NOT_FOUND;

	handle = vmci_make_handle(remote_cid, VMCI_EVENT_HANDLER);

	spin_lock(&context->lock);
	list_क्रम_each_entry_safe(notअगरier, पंचांगp,
				 &context->notअगरier_list, node) अणु
		अगर (vmci_handle_is_equal(notअगरier->handle, handle)) अणु
			list_del_rcu(&notअगरier->node);
			context->n_notअगरiers--;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&context->lock);

	अगर (found) अणु
		synchronize_rcu();
		kमुक्त(notअगरier);
	पूर्ण

	vmci_ctx_put(context);

	वापस found ? VMCI_SUCCESS : VMCI_ERROR_NOT_FOUND;
पूर्ण

अटल पूर्णांक vmci_ctx_get_chkpt_notअगरiers(काष्ठा vmci_ctx *context,
					u32 *buf_size, व्योम **pbuf)
अणु
	u32 *notअगरiers;
	माप_प्रकार data_size;
	काष्ठा vmci_handle_list *entry;
	पूर्णांक i = 0;

	अगर (context->n_notअगरiers == 0) अणु
		*buf_size = 0;
		*pbuf = शून्य;
		वापस VMCI_SUCCESS;
	पूर्ण

	data_size = context->n_notअगरiers * माप(*notअगरiers);
	अगर (*buf_size < data_size) अणु
		*buf_size = data_size;
		वापस VMCI_ERROR_MORE_DATA;
	पूर्ण

	notअगरiers = kदो_स्मृति(data_size, GFP_ATOMIC); /* FIXME: want GFP_KERNEL */
	अगर (!notअगरiers)
		वापस VMCI_ERROR_NO_MEM;

	list_क्रम_each_entry(entry, &context->notअगरier_list, node)
		notअगरiers[i++] = entry->handle.context;

	*buf_size = data_size;
	*pbuf = notअगरiers;
	वापस VMCI_SUCCESS;
पूर्ण

अटल पूर्णांक vmci_ctx_get_chkpt_करोorbells(काष्ठा vmci_ctx *context,
					u32 *buf_size, व्योम **pbuf)
अणु
	काष्ठा dbell_cpt_state *dbells;
	u32 i, n_करोorbells;

	n_करोorbells = vmci_handle_arr_get_size(context->करोorbell_array);
	अगर (n_करोorbells > 0) अणु
		माप_प्रकार data_size = n_करोorbells * माप(*dbells);
		अगर (*buf_size < data_size) अणु
			*buf_size = data_size;
			वापस VMCI_ERROR_MORE_DATA;
		पूर्ण

		dbells = kzalloc(data_size, GFP_ATOMIC);
		अगर (!dbells)
			वापस VMCI_ERROR_NO_MEM;

		क्रम (i = 0; i < n_करोorbells; i++)
			dbells[i].handle = vmci_handle_arr_get_entry(
						context->करोorbell_array, i);

		*buf_size = data_size;
		*pbuf = dbells;
	पूर्ण अन्यथा अणु
		*buf_size = 0;
		*pbuf = शून्य;
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Get current context's checkpoपूर्णांक state of given type.
 */
पूर्णांक vmci_ctx_get_chkpt_state(u32 context_id,
			     u32 cpt_type,
			     u32 *buf_size,
			     व्योम **pbuf)
अणु
	काष्ठा vmci_ctx *context;
	पूर्णांक result;

	context = vmci_ctx_get(context_id);
	अगर (!context)
		वापस VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);

	चयन (cpt_type) अणु
	हाल VMCI_NOTIFICATION_CPT_STATE:
		result = vmci_ctx_get_chkpt_notअगरiers(context, buf_size, pbuf);
		अवरोध;

	हाल VMCI_WELLKNOWN_CPT_STATE:
		/*
		 * For compatibility with VMX'en with VM to VM communication, we
		 * always वापस zero wellknown handles.
		 */

		*buf_size = 0;
		*pbuf = शून्य;
		result = VMCI_SUCCESS;
		अवरोध;

	हाल VMCI_DOORBELL_CPT_STATE:
		result = vmci_ctx_get_chkpt_करोorbells(context, buf_size, pbuf);
		अवरोध;

	शेष:
		pr_devel("Invalid cpt state (type=%d)\n", cpt_type);
		result = VMCI_ERROR_INVALID_ARGS;
		अवरोध;
	पूर्ण

	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	वापस result;
पूर्ण

/*
 * Set current context's checkpoपूर्णांक state of given type.
 */
पूर्णांक vmci_ctx_set_chkpt_state(u32 context_id,
			     u32 cpt_type,
			     u32 buf_size,
			     व्योम *cpt_buf)
अणु
	u32 i;
	u32 current_id;
	पूर्णांक result = VMCI_SUCCESS;
	u32 num_ids = buf_size / माप(u32);

	अगर (cpt_type == VMCI_WELLKNOWN_CPT_STATE && num_ids > 0) अणु
		/*
		 * We would end up here अगर VMX with VM to VM communication
		 * attempts to restore a checkpoपूर्णांक with wellknown handles.
		 */
		pr_warn("Attempt to restore checkpoint with obsolete wellknown handles\n");
		वापस VMCI_ERROR_OBSOLETE;
	पूर्ण

	अगर (cpt_type != VMCI_NOTIFICATION_CPT_STATE) अणु
		pr_devel("Invalid cpt state (type=%d)\n", cpt_type);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	क्रम (i = 0; i < num_ids && result == VMCI_SUCCESS; i++) अणु
		current_id = ((u32 *)cpt_buf)[i];
		result = vmci_ctx_add_notअगरication(context_id, current_id);
		अगर (result != VMCI_SUCCESS)
			अवरोध;
	पूर्ण
	अगर (result != VMCI_SUCCESS)
		pr_devel("Failed to set cpt state (type=%d) (error=%d)\n",
			 cpt_type, result);

	वापस result;
पूर्ण

/*
 * Retrieves the specअगरied context's pending notअगरications in the
 * क्रमm of a handle array. The handle arrays वापसed are the
 * actual data - not a copy and should not be modअगरied by the
 * caller. They must be released using
 * vmci_ctx_rcv_notअगरications_release.
 */
पूर्णांक vmci_ctx_rcv_notअगरications_get(u32 context_id,
				   काष्ठा vmci_handle_arr **db_handle_array,
				   काष्ठा vmci_handle_arr **qp_handle_array)
अणु
	काष्ठा vmci_ctx *context;
	पूर्णांक result = VMCI_SUCCESS;

	context = vmci_ctx_get(context_id);
	अगर (context == शून्य)
		वापस VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);

	*db_handle_array = context->pending_करोorbell_array;
	context->pending_करोorbell_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_DOORBELL_COUNT);
	अगर (!context->pending_करोorbell_array) अणु
		context->pending_करोorbell_array = *db_handle_array;
		*db_handle_array = शून्य;
		result = VMCI_ERROR_NO_MEM;
	पूर्ण
	*qp_handle_array = शून्य;

	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	वापस result;
पूर्ण

/*
 * Releases handle arrays with pending notअगरications previously
 * retrieved using vmci_ctx_rcv_notअगरications_get. If the
 * notअगरications were not successfully handed over to the guest,
 * success must be false.
 */
व्योम vmci_ctx_rcv_notअगरications_release(u32 context_id,
					काष्ठा vmci_handle_arr *db_handle_array,
					काष्ठा vmci_handle_arr *qp_handle_array,
					bool success)
अणु
	काष्ठा vmci_ctx *context = vmci_ctx_get(context_id);

	spin_lock(&context->lock);
	अगर (!success) अणु
		काष्ठा vmci_handle handle;

		/*
		 * New notअगरications may have been added जबतक we were not
		 * holding the context lock, so we transfer any new pending
		 * करोorbell notअगरications to the old array, and reinstate the
		 * old array.
		 */

		handle = vmci_handle_arr_हटाओ_tail(
					context->pending_करोorbell_array);
		जबतक (!vmci_handle_is_invalid(handle)) अणु
			अगर (!vmci_handle_arr_has_entry(db_handle_array,
						       handle)) अणु
				vmci_handle_arr_append_entry(
						&db_handle_array, handle);
			पूर्ण
			handle = vmci_handle_arr_हटाओ_tail(
					context->pending_करोorbell_array);
		पूर्ण
		vmci_handle_arr_destroy(context->pending_करोorbell_array);
		context->pending_करोorbell_array = db_handle_array;
		db_handle_array = शून्य;
	पूर्ण अन्यथा अणु
		ctx_clear_notअगरy_call(context);
	पूर्ण
	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	अगर (db_handle_array)
		vmci_handle_arr_destroy(db_handle_array);

	अगर (qp_handle_array)
		vmci_handle_arr_destroy(qp_handle_array);
पूर्ण

/*
 * Registers that a new करोorbell handle has been allocated by the
 * context. Only करोorbell handles रेजिस्टरed can be notअगरied.
 */
पूर्णांक vmci_ctx_dbell_create(u32 context_id, काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_ctx *context;
	पूर्णांक result;

	अगर (context_id == VMCI_INVALID_ID || vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	context = vmci_ctx_get(context_id);
	अगर (context == शून्य)
		वापस VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);
	अगर (!vmci_handle_arr_has_entry(context->करोorbell_array, handle))
		result = vmci_handle_arr_append_entry(&context->करोorbell_array,
						      handle);
	अन्यथा
		result = VMCI_ERROR_DUPLICATE_ENTRY;

	spin_unlock(&context->lock);
	vmci_ctx_put(context);

	वापस result;
पूर्ण

/*
 * Unरेजिस्टरs a करोorbell handle that was previously रेजिस्टरed
 * with vmci_ctx_dbell_create.
 */
पूर्णांक vmci_ctx_dbell_destroy(u32 context_id, काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_ctx *context;
	काष्ठा vmci_handle हटाओd_handle;

	अगर (context_id == VMCI_INVALID_ID || vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	context = vmci_ctx_get(context_id);
	अगर (context == शून्य)
		वापस VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);
	हटाओd_handle =
	    vmci_handle_arr_हटाओ_entry(context->करोorbell_array, handle);
	vmci_handle_arr_हटाओ_entry(context->pending_करोorbell_array, handle);
	spin_unlock(&context->lock);

	vmci_ctx_put(context);

	वापस vmci_handle_is_invalid(हटाओd_handle) ?
	    VMCI_ERROR_NOT_FOUND : VMCI_SUCCESS;
पूर्ण

/*
 * Unरेजिस्टरs all करोorbell handles that were previously
 * रेजिस्टरed with vmci_ctx_dbell_create.
 */
पूर्णांक vmci_ctx_dbell_destroy_all(u32 context_id)
अणु
	काष्ठा vmci_ctx *context;
	काष्ठा vmci_handle handle;

	अगर (context_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	context = vmci_ctx_get(context_id);
	अगर (context == शून्य)
		वापस VMCI_ERROR_NOT_FOUND;

	spin_lock(&context->lock);
	करो अणु
		काष्ठा vmci_handle_arr *arr = context->करोorbell_array;
		handle = vmci_handle_arr_हटाओ_tail(arr);
	पूर्ण जबतक (!vmci_handle_is_invalid(handle));
	करो अणु
		काष्ठा vmci_handle_arr *arr = context->pending_करोorbell_array;
		handle = vmci_handle_arr_हटाओ_tail(arr);
	पूर्ण जबतक (!vmci_handle_is_invalid(handle));
	spin_unlock(&context->lock);

	vmci_ctx_put(context);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Registers a notअगरication of a करोorbell handle initiated by the
 * specअगरied source context. The notअगरication of करोorbells are
 * subject to the same isolation rules as datagram delivery. To
 * allow host side senders of notअगरications a finer granularity
 * of sender rights than those asचिन्हित to the sending context
 * itself, the host context is required to specअगरy a dअगरferent
 * set of privilege flags that will override the privileges of
 * the source context.
 */
पूर्णांक vmci_ctx_notअगरy_dbell(u32 src_cid,
			  काष्ठा vmci_handle handle,
			  u32 src_priv_flags)
अणु
	काष्ठा vmci_ctx *dst_context;
	पूर्णांक result;

	अगर (vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	/* Get the target VM's VMCI context. */
	dst_context = vmci_ctx_get(handle.context);
	अगर (!dst_context) अणु
		pr_devel("Invalid context (ID=0x%x)\n", handle.context);
		वापस VMCI_ERROR_NOT_FOUND;
	पूर्ण

	अगर (src_cid != handle.context) अणु
		u32 dst_priv_flags;

		अगर (VMCI_CONTEXT_IS_VM(src_cid) &&
		    VMCI_CONTEXT_IS_VM(handle.context)) अणु
			pr_devel("Doorbell notification from VM to VM not supported (src=0x%x, dst=0x%x)\n",
				 src_cid, handle.context);
			result = VMCI_ERROR_DST_UNREACHABLE;
			जाओ out;
		पूर्ण

		result = vmci_dbell_get_priv_flags(handle, &dst_priv_flags);
		अगर (result < VMCI_SUCCESS) अणु
			pr_warn("Failed to get privilege flags for destination (handle=0x%x:0x%x)\n",
				handle.context, handle.resource);
			जाओ out;
		पूर्ण

		अगर (src_cid != VMCI_HOST_CONTEXT_ID ||
		    src_priv_flags == VMCI_NO_PRIVILEGE_FLAGS) अणु
			src_priv_flags = vmci_context_get_priv_flags(src_cid);
		पूर्ण

		अगर (vmci_deny_पूर्णांकeraction(src_priv_flags, dst_priv_flags)) अणु
			result = VMCI_ERROR_NO_ACCESS;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (handle.context == VMCI_HOST_CONTEXT_ID) अणु
		result = vmci_dbell_host_context_notअगरy(src_cid, handle);
	पूर्ण अन्यथा अणु
		spin_lock(&dst_context->lock);

		अगर (!vmci_handle_arr_has_entry(dst_context->करोorbell_array,
					       handle)) अणु
			result = VMCI_ERROR_NOT_FOUND;
		पूर्ण अन्यथा अणु
			अगर (!vmci_handle_arr_has_entry(
					dst_context->pending_करोorbell_array,
					handle)) अणु
				result = vmci_handle_arr_append_entry(
					&dst_context->pending_करोorbell_array,
					handle);
				अगर (result == VMCI_SUCCESS) अणु
					ctx_संकेत_notअगरy(dst_context);
					wake_up(&dst_context->host_context.रुको_queue);
				पूर्ण
			पूर्ण अन्यथा अणु
				result = VMCI_SUCCESS;
			पूर्ण
		पूर्ण
		spin_unlock(&dst_context->lock);
	पूर्ण

 out:
	vmci_ctx_put(dst_context);

	वापस result;
पूर्ण

bool vmci_ctx_supports_host_qp(काष्ठा vmci_ctx *context)
अणु
	वापस context && context->user_version >= VMCI_VERSION_HOSTQP;
पूर्ण

/*
 * Registers that a new queue pair handle has been allocated by
 * the context.
 */
पूर्णांक vmci_ctx_qp_create(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle)
अणु
	पूर्णांक result;

	अगर (context == शून्य || vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (!vmci_handle_arr_has_entry(context->queue_pair_array, handle))
		result = vmci_handle_arr_append_entry(
			&context->queue_pair_array, handle);
	अन्यथा
		result = VMCI_ERROR_DUPLICATE_ENTRY;

	वापस result;
पूर्ण

/*
 * Unरेजिस्टरs a queue pair handle that was previously रेजिस्टरed
 * with vmci_ctx_qp_create.
 */
पूर्णांक vmci_ctx_qp_destroy(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_handle hndl;

	अगर (context == शून्य || vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	hndl = vmci_handle_arr_हटाओ_entry(context->queue_pair_array, handle);

	वापस vmci_handle_is_invalid(hndl) ?
		VMCI_ERROR_NOT_FOUND : VMCI_SUCCESS;
पूर्ण

/*
 * Determines whether a given queue pair handle is रेजिस्टरed
 * with the given context.
 */
bool vmci_ctx_qp_exists(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle)
अणु
	अगर (context == शून्य || vmci_handle_is_invalid(handle))
		वापस false;

	वापस vmci_handle_arr_has_entry(context->queue_pair_array, handle);
पूर्ण

/*
 * vmci_context_get_priv_flags() - Retrieve privilege flags.
 * @context_id: The context ID of the VMCI context.
 *
 * Retrieves privilege flags of the given VMCI context ID.
 */
u32 vmci_context_get_priv_flags(u32 context_id)
अणु
	अगर (vmci_host_code_active()) अणु
		u32 flags;
		काष्ठा vmci_ctx *context;

		context = vmci_ctx_get(context_id);
		अगर (!context)
			वापस VMCI_LEAST_PRIVILEGE_FLAGS;

		flags = context->priv_flags;
		vmci_ctx_put(context);
		वापस flags;
	पूर्ण
	वापस VMCI_NO_PRIVILEGE_FLAGS;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_context_get_priv_flags);

/*
 * vmci_is_context_owner() - Determimnes अगर user is the context owner
 * @context_id: The context ID of the VMCI context.
 * @uid:        The host user id (real kernel value).
 *
 * Determines whether a given UID is the owner of given VMCI context.
 */
bool vmci_is_context_owner(u32 context_id, kuid_t uid)
अणु
	bool is_owner = false;

	अगर (vmci_host_code_active()) अणु
		काष्ठा vmci_ctx *context = vmci_ctx_get(context_id);
		अगर (context) अणु
			अगर (context->cred)
				is_owner = uid_eq(context->cred->uid, uid);
			vmci_ctx_put(context);
		पूर्ण
	पूर्ण

	वापस is_owner;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_is_context_owner);
