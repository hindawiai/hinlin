<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/rculist.h>
#समावेश <linux/completion.h>

#समावेश "vmci_resource.h"
#समावेश "vmci_driver.h"


#घोषणा VMCI_RESOURCE_HASH_BITS         7
#घोषणा VMCI_RESOURCE_HASH_BUCKETS      (1 << VMCI_RESOURCE_HASH_BITS)

काष्ठा vmci_hash_table अणु
	spinlock_t lock;
	काष्ठा hlist_head entries[VMCI_RESOURCE_HASH_BUCKETS];
पूर्ण;

अटल काष्ठा vmci_hash_table vmci_resource_table = अणु
	.lock = __SPIN_LOCK_UNLOCKED(vmci_resource_table.lock),
पूर्ण;

अटल अचिन्हित पूर्णांक vmci_resource_hash(काष्ठा vmci_handle handle)
अणु
	वापस hash_32(handle.resource, VMCI_RESOURCE_HASH_BITS);
पूर्ण

/*
 * Gets a resource (अगर one exists) matching given handle from the hash table.
 */
अटल काष्ठा vmci_resource *vmci_resource_lookup(काष्ठा vmci_handle handle,
						  क्रमागत vmci_resource_type type)
अणु
	काष्ठा vmci_resource *r, *resource = शून्य;
	अचिन्हित पूर्णांक idx = vmci_resource_hash(handle);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(r,
				 &vmci_resource_table.entries[idx], node) अणु
		u32 cid = r->handle.context;
		u32 rid = r->handle.resource;

		अगर (r->type == type &&
		    rid == handle.resource &&
		    (cid == handle.context || cid == VMCI_INVALID_ID ||
		     handle.context == VMCI_INVALID_ID)) अणु
			resource = r;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस resource;
पूर्ण

/*
 * Find an unused resource ID and वापस it. The first
 * VMCI_RESERVED_RESOURCE_ID_MAX are reserved so we start from
 * its value + 1.
 * Returns VMCI resource id on success, VMCI_INVALID_ID on failure.
 */
अटल u32 vmci_resource_find_id(u32 context_id,
				 क्रमागत vmci_resource_type resource_type)
अणु
	अटल u32 resource_id = VMCI_RESERVED_RESOURCE_ID_MAX + 1;
	u32 old_rid = resource_id;
	u32 current_rid;

	/*
	 * Generate a unique resource ID.  Keep on trying until we wrap around
	 * in the RID space.
	 */
	करो अणु
		काष्ठा vmci_handle handle;

		current_rid = resource_id;
		resource_id++;
		अगर (unlikely(resource_id == VMCI_INVALID_ID)) अणु
			/* Skip the reserved rids. */
			resource_id = VMCI_RESERVED_RESOURCE_ID_MAX + 1;
		पूर्ण

		handle = vmci_make_handle(context_id, current_rid);
		अगर (!vmci_resource_lookup(handle, resource_type))
			वापस current_rid;
	पूर्ण जबतक (resource_id != old_rid);

	वापस VMCI_INVALID_ID;
पूर्ण


पूर्णांक vmci_resource_add(काष्ठा vmci_resource *resource,
		      क्रमागत vmci_resource_type resource_type,
		      काष्ठा vmci_handle handle)

अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक result;

	spin_lock(&vmci_resource_table.lock);

	अगर (handle.resource == VMCI_INVALID_ID) अणु
		handle.resource = vmci_resource_find_id(handle.context,
			resource_type);
		अगर (handle.resource == VMCI_INVALID_ID) अणु
			result = VMCI_ERROR_NO_HANDLE;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (vmci_resource_lookup(handle, resource_type)) अणु
		result = VMCI_ERROR_ALREADY_EXISTS;
		जाओ out;
	पूर्ण

	resource->handle = handle;
	resource->type = resource_type;
	INIT_HLIST_NODE(&resource->node);
	kref_init(&resource->kref);
	init_completion(&resource->करोne);

	idx = vmci_resource_hash(resource->handle);
	hlist_add_head_rcu(&resource->node, &vmci_resource_table.entries[idx]);

	result = VMCI_SUCCESS;

out:
	spin_unlock(&vmci_resource_table.lock);
	वापस result;
पूर्ण

व्योम vmci_resource_हटाओ(काष्ठा vmci_resource *resource)
अणु
	काष्ठा vmci_handle handle = resource->handle;
	अचिन्हित पूर्णांक idx = vmci_resource_hash(handle);
	काष्ठा vmci_resource *r;

	/* Remove resource from hash table. */
	spin_lock(&vmci_resource_table.lock);

	hlist_क्रम_each_entry(r, &vmci_resource_table.entries[idx], node) अणु
		अगर (vmci_handle_is_equal(r->handle, resource->handle)) अणु
			hlist_del_init_rcu(&r->node);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&vmci_resource_table.lock);
	synchronize_rcu();

	vmci_resource_put(resource);
	रुको_क्रम_completion(&resource->करोne);
पूर्ण

काष्ठा vmci_resource *
vmci_resource_by_handle(काष्ठा vmci_handle resource_handle,
			क्रमागत vmci_resource_type resource_type)
अणु
	काष्ठा vmci_resource *r, *resource = शून्य;

	rcu_पढ़ो_lock();

	r = vmci_resource_lookup(resource_handle, resource_type);
	अगर (r &&
	    (resource_type == r->type ||
	     resource_type == VMCI_RESOURCE_TYPE_ANY)) अणु
		resource = vmci_resource_get(r);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस resource;
पूर्ण

/*
 * Get a reference to given resource.
 */
काष्ठा vmci_resource *vmci_resource_get(काष्ठा vmci_resource *resource)
अणु
	kref_get(&resource->kref);

	वापस resource;
पूर्ण

अटल व्योम vmci_release_resource(काष्ठा kref *kref)
अणु
	काष्ठा vmci_resource *resource =
		container_of(kref, काष्ठा vmci_resource, kref);

	/* Verअगरy the resource has been unlinked from hash table */
	WARN_ON(!hlist_unhashed(&resource->node));

	/* Signal that container of this resource can now be destroyed */
	complete(&resource->करोne);
पूर्ण

/*
 * Resource's release function will get called अगर last reference.
 * If it is the last reference, then we are sure that nobody अन्यथा
 * can increment the count again (it's gone from the resource hash
 * table), so there's no need क्रम locking here.
 */
पूर्णांक vmci_resource_put(काष्ठा vmci_resource *resource)
अणु
	/*
	 * We propagate the inक्रमmation back to caller in हाल it wants to know
	 * whether entry was मुक्तd.
	 */
	वापस kref_put(&resource->kref, vmci_release_resource) ?
		VMCI_SUCCESS_ENTRY_DEAD : VMCI_SUCCESS;
पूर्ण

काष्ठा vmci_handle vmci_resource_handle(काष्ठा vmci_resource *resource)
अणु
	वापस resource->handle;
पूर्ण
