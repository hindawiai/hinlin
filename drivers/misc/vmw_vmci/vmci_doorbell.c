<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/completion.h>
#समावेश <linux/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "vmci_datagram.h"
#समावेश "vmci_doorbell.h"
#समावेश "vmci_resource.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_route.h"


#घोषणा VMCI_DOORBELL_INDEX_BITS	6
#घोषणा VMCI_DOORBELL_INDEX_TABLE_SIZE	(1 << VMCI_DOORBELL_INDEX_BITS)
#घोषणा VMCI_DOORBELL_HASH(_idx)	hash_32(_idx, VMCI_DOORBELL_INDEX_BITS)

/*
 * DoorbellEntry describes the a करोorbell notअगरication handle allocated by the
 * host.
 */
काष्ठा dbell_entry अणु
	काष्ठा vmci_resource resource;
	काष्ठा hlist_node node;
	काष्ठा work_काष्ठा work;
	vmci_callback notअगरy_cb;
	व्योम *client_data;
	u32 idx;
	u32 priv_flags;
	bool run_delayed;
	atomic_t active;	/* Only used by guest personality */
पूर्ण;

/* The VMCI index table keeps track of currently रेजिस्टरed करोorbells. */
काष्ठा dbell_index_table अणु
	spinlock_t lock;	/* Index table lock */
	काष्ठा hlist_head entries[VMCI_DOORBELL_INDEX_TABLE_SIZE];
पूर्ण;

अटल काष्ठा dbell_index_table vmci_करोorbell_it = अणु
	.lock = __SPIN_LOCK_UNLOCKED(vmci_करोorbell_it.lock),
पूर्ण;

/*
 * The max_notअगरy_idx is one larger than the currently known biपंचांगap index in
 * use, and is used to determine how much of the biपंचांगap needs to be scanned.
 */
अटल u32 max_notअगरy_idx;

/*
 * The notअगरy_idx_count is used क्रम determining whether there are मुक्त entries
 * within the biपंचांगap (अगर notअगरy_idx_count + 1 < max_notअगरy_idx).
 */
अटल u32 notअगरy_idx_count;

/*
 * The last_notअगरy_idx_reserved is used to track the last index handed out - in
 * the हाल where multiple handles share a notअगरication index, we hand out
 * indexes round robin based on last_notअगरy_idx_reserved.
 */
अटल u32 last_notअगरy_idx_reserved;

/* This is a one entry cache used to by the index allocation. */
अटल u32 last_notअगरy_idx_released = PAGE_SIZE;


/*
 * Utility function that retrieves the privilege flags associated
 * with a given करोorbell handle. For guest endpoपूर्णांकs, the
 * privileges are determined by the context ID, but क्रम host
 * endpoपूर्णांकs privileges are associated with the complete
 * handle. Hypervisor endpoपूर्णांकs are not yet supported.
 */
पूर्णांक vmci_dbell_get_priv_flags(काष्ठा vmci_handle handle, u32 *priv_flags)
अणु
	अगर (priv_flags == शून्य || handle.context == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (handle.context == VMCI_HOST_CONTEXT_ID) अणु
		काष्ठा dbell_entry *entry;
		काष्ठा vmci_resource *resource;

		resource = vmci_resource_by_handle(handle,
						   VMCI_RESOURCE_TYPE_DOORBELL);
		अगर (!resource)
			वापस VMCI_ERROR_NOT_FOUND;

		entry = container_of(resource, काष्ठा dbell_entry, resource);
		*priv_flags = entry->priv_flags;
		vmci_resource_put(resource);
	पूर्ण अन्यथा अगर (handle.context == VMCI_HYPERVISOR_CONTEXT_ID) अणु
		/*
		 * Hypervisor endpoपूर्णांकs क्रम notअगरications are not
		 * supported (yet).
		 */
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण अन्यथा अणु
		*priv_flags = vmci_context_get_priv_flags(handle.context);
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Find करोorbell entry by biपंचांगap index.
 */
अटल काष्ठा dbell_entry *dbell_index_table_find(u32 idx)
अणु
	u32 bucket = VMCI_DOORBELL_HASH(idx);
	काष्ठा dbell_entry *dbell;

	hlist_क्रम_each_entry(dbell, &vmci_करोorbell_it.entries[bucket],
			     node) अणु
		अगर (idx == dbell->idx)
			वापस dbell;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Add the given entry to the index table.  This willi take a reference to the
 * entry's resource so that the entry is not deleted beक्रमe it is हटाओd from
 * the * table.
 */
अटल व्योम dbell_index_table_add(काष्ठा dbell_entry *entry)
अणु
	u32 bucket;
	u32 new_notअगरy_idx;

	vmci_resource_get(&entry->resource);

	spin_lock_bh(&vmci_करोorbell_it.lock);

	/*
	 * Below we try to allocate an index in the notअगरication
	 * biपंचांगap with "not too much" sharing between resources. If we
	 * use less that the full biपंचांगap, we either add to the end अगर
	 * there are no unused flags within the currently used area,
	 * or we search क्रम unused ones. If we use the full biपंचांगap, we
	 * allocate the index round robin.
	 */
	अगर (max_notअगरy_idx < PAGE_SIZE || notअगरy_idx_count < PAGE_SIZE) अणु
		अगर (last_notअगरy_idx_released < max_notअगरy_idx &&
		    !dbell_index_table_find(last_notअगरy_idx_released)) अणु
			new_notअगरy_idx = last_notअगरy_idx_released;
			last_notअगरy_idx_released = PAGE_SIZE;
		पूर्ण अन्यथा अणु
			bool reused = false;
			new_notअगरy_idx = last_notअगरy_idx_reserved;
			अगर (notअगरy_idx_count + 1 < max_notअगरy_idx) अणु
				करो अणु
					अगर (!dbell_index_table_find
					    (new_notअगरy_idx)) अणु
						reused = true;
						अवरोध;
					पूर्ण
					new_notअगरy_idx = (new_notअगरy_idx + 1) %
					    max_notअगरy_idx;
				पूर्ण जबतक (new_notअगरy_idx !=
					 last_notअगरy_idx_released);
			पूर्ण
			अगर (!reused) अणु
				new_notअगरy_idx = max_notअगरy_idx;
				max_notअगरy_idx++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		new_notअगरy_idx = (last_notअगरy_idx_reserved + 1) % PAGE_SIZE;
	पूर्ण

	last_notअगरy_idx_reserved = new_notअगरy_idx;
	notअगरy_idx_count++;

	entry->idx = new_notअगरy_idx;
	bucket = VMCI_DOORBELL_HASH(entry->idx);
	hlist_add_head(&entry->node, &vmci_करोorbell_it.entries[bucket]);

	spin_unlock_bh(&vmci_करोorbell_it.lock);
पूर्ण

/*
 * Remove the given entry from the index table.  This will release() the
 * entry's resource.
 */
अटल व्योम dbell_index_table_हटाओ(काष्ठा dbell_entry *entry)
अणु
	spin_lock_bh(&vmci_करोorbell_it.lock);

	hlist_del_init(&entry->node);

	notअगरy_idx_count--;
	अगर (entry->idx == max_notअगरy_idx - 1) अणु
		/*
		 * If we delete an entry with the maximum known
		 * notअगरication index, we take the opportunity to
		 * prune the current max. As there might be other
		 * unused indices immediately below, we lower the
		 * maximum until we hit an index in use.
		 */
		जबतक (max_notअगरy_idx > 0 &&
		       !dbell_index_table_find(max_notअगरy_idx - 1))
			max_notअगरy_idx--;
	पूर्ण

	last_notअगरy_idx_released = entry->idx;

	spin_unlock_bh(&vmci_करोorbell_it.lock);

	vmci_resource_put(&entry->resource);
पूर्ण

/*
 * Creates a link between the given करोorbell handle and the given
 * index in the biपंचांगap in the device backend. A notअगरication state
 * is created in hypervisor.
 */
अटल पूर्णांक dbell_link(काष्ठा vmci_handle handle, u32 notअगरy_idx)
अणु
	काष्ठा vmci_करोorbell_link_msg link_msg;

	link_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					    VMCI_DOORBELL_LINK);
	link_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	link_msg.hdr.payload_size = माप(link_msg) - VMCI_DG_HEADERSIZE;
	link_msg.handle = handle;
	link_msg.notअगरy_idx = notअगरy_idx;

	वापस vmci_send_datagram(&link_msg.hdr);
पूर्ण

/*
 * Unlinks the given करोorbell handle from an index in the biपंचांगap in
 * the device backend. The notअगरication state is destroyed in hypervisor.
 */
अटल पूर्णांक dbell_unlink(काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_करोorbell_unlink_msg unlink_msg;

	unlink_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_DOORBELL_UNLINK);
	unlink_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	unlink_msg.hdr.payload_size = माप(unlink_msg) - VMCI_DG_HEADERSIZE;
	unlink_msg.handle = handle;

	वापस vmci_send_datagram(&unlink_msg.hdr);
पूर्ण

/*
 * Notअगरy another guest or the host.  We send a datagram करोwn to the
 * host via the hypervisor with the notअगरication info.
 */
अटल पूर्णांक dbell_notअगरy_as_guest(काष्ठा vmci_handle handle, u32 priv_flags)
अणु
	काष्ठा vmci_करोorbell_notअगरy_msg notअगरy_msg;

	notअगरy_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_DOORBELL_NOTIFY);
	notअगरy_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	notअगरy_msg.hdr.payload_size = माप(notअगरy_msg) - VMCI_DG_HEADERSIZE;
	notअगरy_msg.handle = handle;

	वापस vmci_send_datagram(&notअगरy_msg.hdr);
पूर्ण

/*
 * Calls the specअगरied callback in a delayed context.
 */
अटल व्योम dbell_delayed_dispatch(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dbell_entry *entry = container_of(work,
						 काष्ठा dbell_entry, work);

	entry->notअगरy_cb(entry->client_data);
	vmci_resource_put(&entry->resource);
पूर्ण

/*
 * Dispatches a करोorbell notअगरication to the host context.
 */
पूर्णांक vmci_dbell_host_context_notअगरy(u32 src_cid, काष्ठा vmci_handle handle)
अणु
	काष्ठा dbell_entry *entry;
	काष्ठा vmci_resource *resource;

	अगर (vmci_handle_is_invalid(handle)) अणु
		pr_devel("Notifying an invalid doorbell (handle=0x%x:0x%x)\n",
			 handle.context, handle.resource);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	resource = vmci_resource_by_handle(handle,
					   VMCI_RESOURCE_TYPE_DOORBELL);
	अगर (!resource) अणु
		pr_devel("Notifying an unknown doorbell (handle=0x%x:0x%x)\n",
			 handle.context, handle.resource);
		वापस VMCI_ERROR_NOT_FOUND;
	पूर्ण

	entry = container_of(resource, काष्ठा dbell_entry, resource);
	अगर (entry->run_delayed) अणु
		अगर (!schedule_work(&entry->work))
			vmci_resource_put(resource);
	पूर्ण अन्यथा अणु
		entry->notअगरy_cb(entry->client_data);
		vmci_resource_put(resource);
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Register the notअगरication biपंचांगap with the host.
 */
bool vmci_dbell_रेजिस्टर_notअगरication_biपंचांगap(u64 biपंचांगap_ppn)
अणु
	पूर्णांक result;
	काष्ठा vmci_notअगरy_bm_set_msg biपंचांगap_set_msg = अणु पूर्ण;

	biपंचांगap_set_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
						  VMCI_SET_NOTIFY_BITMAP);
	biपंचांगap_set_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	biपंचांगap_set_msg.hdr.payload_size = माप(biपंचांगap_set_msg) -
	    VMCI_DG_HEADERSIZE;
	अगर (vmci_use_ppn64())
		biपंचांगap_set_msg.biपंचांगap_ppn64 = biपंचांगap_ppn;
	अन्यथा
		biपंचांगap_set_msg.biपंचांगap_ppn32 = (u32) biपंचांगap_ppn;

	result = vmci_send_datagram(&biपंचांगap_set_msg.hdr);
	अगर (result != VMCI_SUCCESS) अणु
		pr_devel("Failed to register (PPN=%llu) as notification bitmap (error=%d)\n",
			 biपंचांगap_ppn, result);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Executes or schedules the handlers क्रम a given notअगरy index.
 */
अटल व्योम dbell_fire_entries(u32 notअगरy_idx)
अणु
	u32 bucket = VMCI_DOORBELL_HASH(notअगरy_idx);
	काष्ठा dbell_entry *dbell;

	spin_lock_bh(&vmci_करोorbell_it.lock);

	hlist_क्रम_each_entry(dbell, &vmci_करोorbell_it.entries[bucket], node) अणु
		अगर (dbell->idx == notअगरy_idx &&
		    atomic_पढ़ो(&dbell->active) == 1) अणु
			अगर (dbell->run_delayed) अणु
				vmci_resource_get(&dbell->resource);
				अगर (!schedule_work(&dbell->work))
					vmci_resource_put(&dbell->resource);
			पूर्ण अन्यथा अणु
				dbell->notअगरy_cb(dbell->client_data);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&vmci_करोorbell_it.lock);
पूर्ण

/*
 * Scans the notअगरication biपंचांगap, collects pending notअगरications,
 * resets the biपंचांगap and invokes appropriate callbacks.
 */
व्योम vmci_dbell_scan_notअगरication_entries(u8 *biपंचांगap)
अणु
	u32 idx;

	क्रम (idx = 0; idx < max_notअगरy_idx; idx++) अणु
		अगर (biपंचांगap[idx] & 0x1) अणु
			biपंचांगap[idx] &= ~1;
			dbell_fire_entries(idx);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * vmci_करोorbell_create() - Creates a करोorbell
 * @handle:     A handle used to track the resource.  Can be invalid.
 * @flags:      Flag that determines context of callback.
 * @priv_flags: Privileges flags.
 * @notअगरy_cb:  The callback to be ivoked when the करोorbell fires.
 * @client_data:        A parameter to be passed to the callback.
 *
 * Creates a करोorbell with the given callback. If the handle is
 * VMCI_INVALID_HANDLE, a मुक्त handle will be asचिन्हित, अगर
 * possible. The callback can be run immediately (potentially with
 * locks held - the शेष) or delayed (in a kernel thपढ़ो) by
 * specअगरying the flag VMCI_FLAG_DELAYED_CB. If delayed execution
 * is selected, a given callback may not be run अगर the kernel is
 * unable to allocate memory क्रम the delayed execution (highly
 * unlikely).
 */
पूर्णांक vmci_करोorbell_create(काष्ठा vmci_handle *handle,
			 u32 flags,
			 u32 priv_flags,
			 vmci_callback notअगरy_cb, व्योम *client_data)
अणु
	काष्ठा dbell_entry *entry;
	काष्ठा vmci_handle new_handle;
	पूर्णांक result;

	अगर (!handle || !notअगरy_cb || flags & ~VMCI_FLAG_DELAYED_CB ||
	    priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS)
		वापस VMCI_ERROR_INVALID_ARGS;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry == शून्य) अणु
		pr_warn("Failed allocating memory for datagram entry\n");
		वापस VMCI_ERROR_NO_MEM;
	पूर्ण

	अगर (vmci_handle_is_invalid(*handle)) अणु
		u32 context_id = vmci_get_context_id();

		अगर (context_id == VMCI_INVALID_ID) अणु
			pr_warn("Failed to get context ID\n");
			result = VMCI_ERROR_NO_RESOURCES;
			जाओ मुक्त_mem;
		पूर्ण

		/* Let resource code allocate a मुक्त ID क्रम us */
		new_handle = vmci_make_handle(context_id, VMCI_INVALID_ID);
	पूर्ण अन्यथा अणु
		bool valid_context = false;

		/*
		 * Validate the handle.  We must करो both of the checks below
		 * because we can be acting as both a host and a guest at the
		 * same समय. We always allow the host context ID, since the
		 * host functionality is in practice always there with the
		 * unअगरied driver.
		 */
		अगर (handle->context == VMCI_HOST_CONTEXT_ID ||
		    (vmci_guest_code_active() &&
		     vmci_get_context_id() == handle->context)) अणु
			valid_context = true;
		पूर्ण

		अगर (!valid_context || handle->resource == VMCI_INVALID_ID) अणु
			pr_devel("Invalid argument (handle=0x%x:0x%x)\n",
				 handle->context, handle->resource);
			result = VMCI_ERROR_INVALID_ARGS;
			जाओ मुक्त_mem;
		पूर्ण

		new_handle = *handle;
	पूर्ण

	entry->idx = 0;
	INIT_HLIST_NODE(&entry->node);
	entry->priv_flags = priv_flags;
	INIT_WORK(&entry->work, dbell_delayed_dispatch);
	entry->run_delayed = flags & VMCI_FLAG_DELAYED_CB;
	entry->notअगरy_cb = notअगरy_cb;
	entry->client_data = client_data;
	atomic_set(&entry->active, 0);

	result = vmci_resource_add(&entry->resource,
				   VMCI_RESOURCE_TYPE_DOORBELL,
				   new_handle);
	अगर (result != VMCI_SUCCESS) अणु
		pr_warn("Failed to add new resource (handle=0x%x:0x%x), error: %d\n",
			new_handle.context, new_handle.resource, result);
		जाओ मुक्त_mem;
	पूर्ण

	new_handle = vmci_resource_handle(&entry->resource);
	अगर (vmci_guest_code_active()) अणु
		dbell_index_table_add(entry);
		result = dbell_link(new_handle, entry->idx);
		अगर (VMCI_SUCCESS != result)
			जाओ destroy_resource;

		atomic_set(&entry->active, 1);
	पूर्ण

	*handle = new_handle;

	वापस result;

 destroy_resource:
	dbell_index_table_हटाओ(entry);
	vmci_resource_हटाओ(&entry->resource);
 मुक्त_mem:
	kमुक्त(entry);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_करोorbell_create);

/*
 * vmci_करोorbell_destroy() - Destroy a करोorbell.
 * @handle:     The handle tracking the resource.
 *
 * Destroys a करोorbell previously created with vmcii_करोorbell_create. This
 * operation may block रुकोing क्रम a callback to finish.
 */
पूर्णांक vmci_करोorbell_destroy(काष्ठा vmci_handle handle)
अणु
	काष्ठा dbell_entry *entry;
	काष्ठा vmci_resource *resource;

	अगर (vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	resource = vmci_resource_by_handle(handle,
					   VMCI_RESOURCE_TYPE_DOORBELL);
	अगर (!resource) अणु
		pr_devel("Failed to destroy doorbell (handle=0x%x:0x%x)\n",
			 handle.context, handle.resource);
		वापस VMCI_ERROR_NOT_FOUND;
	पूर्ण

	entry = container_of(resource, काष्ठा dbell_entry, resource);

	अगर (!hlist_unhashed(&entry->node)) अणु
		पूर्णांक result;

		dbell_index_table_हटाओ(entry);

		result = dbell_unlink(handle);
		अगर (VMCI_SUCCESS != result) अणु

			/*
			 * The only reason this should fail would be
			 * an inconsistency between guest and
			 * hypervisor state, where the guest believes
			 * it has an active registration whereas the
			 * hypervisor करोesn't. One हाल where this may
			 * happen is अगर a करोorbell is unरेजिस्टरed
			 * following a hibernation at a समय where the
			 * करोorbell state hasn't been restored on the
			 * hypervisor side yet. Since the handle has
			 * now been हटाओd in the guest, we just
			 * prपूर्णांक a warning and वापस success.
			 */
			pr_devel("Unlink of doorbell (handle=0x%x:0x%x) unknown by hypervisor (error=%d)\n",
				 handle.context, handle.resource, result);
		पूर्ण
	पूर्ण

	/*
	 * Now हटाओ the resource from the table.  It might still be in use
	 * after this, in a callback or still on the delayed work queue.
	 */
	vmci_resource_put(&entry->resource);
	vmci_resource_हटाओ(&entry->resource);

	kमुक्त(entry);

	वापस VMCI_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_करोorbell_destroy);

/*
 * vmci_करोorbell_notअगरy() - Ring the करोorbell (and hide in the bushes).
 * @dst:        The handlle identअगरying the करोorbell resource
 * @priv_flags: Priviledge flags.
 *
 * Generates a notअगरication on the करोorbell identअगरied by the
 * handle. For host side generation of notअगरications, the caller
 * can specअगरy what the privilege of the calling side is.
 */
पूर्णांक vmci_करोorbell_notअगरy(काष्ठा vmci_handle dst, u32 priv_flags)
अणु
	पूर्णांक retval;
	क्रमागत vmci_route route;
	काष्ठा vmci_handle src;

	अगर (vmci_handle_is_invalid(dst) ||
	    (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS))
		वापस VMCI_ERROR_INVALID_ARGS;

	src = VMCI_INVALID_HANDLE;
	retval = vmci_route(&src, &dst, false, &route);
	अगर (retval < VMCI_SUCCESS)
		वापस retval;

	अगर (VMCI_ROUTE_AS_HOST == route)
		वापस vmci_ctx_notअगरy_dbell(VMCI_HOST_CONTEXT_ID,
					     dst, priv_flags);

	अगर (VMCI_ROUTE_AS_GUEST == route)
		वापस dbell_notअगरy_as_guest(dst, priv_flags);

	pr_warn("Unknown route (%d) for doorbell\n", route);
	वापस VMCI_ERROR_DST_UNREACHABLE;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_करोorbell_notअगरy);
