<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>

#समावेश "vmci_datagram.h"
#समावेश "vmci_resource.h"
#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"
#समावेश "vmci_route.h"

/*
 * काष्ठा datagram_entry describes the datagram entity. It is used क्रम datagram
 * entities created only on the host.
 */
काष्ठा datagram_entry अणु
	काष्ठा vmci_resource resource;
	u32 flags;
	bool run_delayed;
	vmci_datagram_recv_cb recv_cb;
	व्योम *client_data;
	u32 priv_flags;
पूर्ण;

काष्ठा delayed_datagram_info अणु
	काष्ठा datagram_entry *entry;
	काष्ठा work_काष्ठा work;
	bool in_dg_host_queue;
	/* msg and msg_payload must be together. */
	काष्ठा vmci_datagram msg;
	u8 msg_payload[];
पूर्ण;

/* Number of in-flight host->host datagrams */
अटल atomic_t delayed_dg_host_queue_size = ATOMIC_INIT(0);

/*
 * Create a datagram entry given a handle poपूर्णांकer.
 */
अटल पूर्णांक dg_create_handle(u32 resource_id,
			    u32 flags,
			    u32 priv_flags,
			    vmci_datagram_recv_cb recv_cb,
			    व्योम *client_data, काष्ठा vmci_handle *out_handle)
अणु
	पूर्णांक result;
	u32 context_id;
	काष्ठा vmci_handle handle;
	काष्ठा datagram_entry *entry;

	अगर ((flags & VMCI_FLAG_WELLKNOWN_DG_HND) != 0)
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर ((flags & VMCI_FLAG_ANYCID_DG_HND) != 0) अणु
		context_id = VMCI_INVALID_ID;
	पूर्ण अन्यथा अणु
		context_id = vmci_get_context_id();
		अगर (context_id == VMCI_INVALID_ID)
			वापस VMCI_ERROR_NO_RESOURCES;
	पूर्ण

	handle = vmci_make_handle(context_id, resource_id);

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		pr_warn("Failed allocating memory for datagram entry\n");
		वापस VMCI_ERROR_NO_MEM;
	पूर्ण

	entry->run_delayed = (flags & VMCI_FLAG_DG_DELAYED_CB) ? true : false;
	entry->flags = flags;
	entry->recv_cb = recv_cb;
	entry->client_data = client_data;
	entry->priv_flags = priv_flags;

	/* Make datagram resource live. */
	result = vmci_resource_add(&entry->resource,
				   VMCI_RESOURCE_TYPE_DATAGRAM,
				   handle);
	अगर (result != VMCI_SUCCESS) अणु
		pr_warn("Failed to add new resource (handle=0x%x:0x%x), error: %d\n",
			handle.context, handle.resource, result);
		kमुक्त(entry);
		वापस result;
	पूर्ण

	*out_handle = vmci_resource_handle(&entry->resource);
	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Internal utility function with the same purpose as
 * vmci_datagram_get_priv_flags that also takes a context_id.
 */
अटल पूर्णांक vmci_datagram_get_priv_flags(u32 context_id,
					काष्ठा vmci_handle handle,
					u32 *priv_flags)
अणु
	अगर (context_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (context_id == VMCI_HOST_CONTEXT_ID) अणु
		काष्ठा datagram_entry *src_entry;
		काष्ठा vmci_resource *resource;

		resource = vmci_resource_by_handle(handle,
						   VMCI_RESOURCE_TYPE_DATAGRAM);
		अगर (!resource)
			वापस VMCI_ERROR_INVALID_ARGS;

		src_entry = container_of(resource, काष्ठा datagram_entry,
					 resource);
		*priv_flags = src_entry->priv_flags;
		vmci_resource_put(resource);
	पूर्ण अन्यथा अगर (context_id == VMCI_HYPERVISOR_CONTEXT_ID)
		*priv_flags = VMCI_MAX_PRIVILEGE_FLAGS;
	अन्यथा
		*priv_flags = vmci_context_get_priv_flags(context_id);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Calls the specअगरied callback in a delayed context.
 */
अटल व्योम dg_delayed_dispatch(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_datagram_info *dg_info =
			container_of(work, काष्ठा delayed_datagram_info, work);

	dg_info->entry->recv_cb(dg_info->entry->client_data, &dg_info->msg);

	vmci_resource_put(&dg_info->entry->resource);

	अगर (dg_info->in_dg_host_queue)
		atomic_dec(&delayed_dg_host_queue_size);

	kमुक्त(dg_info);
पूर्ण

/*
 * Dispatch datagram as a host, to the host, or other vm context. This
 * function cannot dispatch to hypervisor context handlers. This should
 * have been handled beक्रमe we get here by vmci_datagram_dispatch.
 * Returns number of bytes sent on success, error code otherwise.
 */
अटल पूर्णांक dg_dispatch_as_host(u32 context_id, काष्ठा vmci_datagram *dg)
अणु
	पूर्णांक retval;
	माप_प्रकार dg_size;
	u32 src_priv_flags;

	dg_size = VMCI_DG_SIZE(dg);

	/* Host cannot send to the hypervisor. */
	अगर (dg->dst.context == VMCI_HYPERVISOR_CONTEXT_ID)
		वापस VMCI_ERROR_DST_UNREACHABLE;

	/* Check that source handle matches sending context. */
	अगर (dg->src.context != context_id) अणु
		pr_devel("Sender context (ID=0x%x) is not owner of src datagram entry (handle=0x%x:0x%x)\n",
			 context_id, dg->src.context, dg->src.resource);
		वापस VMCI_ERROR_NO_ACCESS;
	पूर्ण

	/* Get hold of privileges of sending endpoपूर्णांक. */
	retval = vmci_datagram_get_priv_flags(context_id, dg->src,
					      &src_priv_flags);
	अगर (retval != VMCI_SUCCESS) अणु
		pr_warn("Couldn't get privileges (handle=0x%x:0x%x)\n",
			dg->src.context, dg->src.resource);
		वापस retval;
	पूर्ण

	/* Determine अगर we should route to host or guest destination. */
	अगर (dg->dst.context == VMCI_HOST_CONTEXT_ID) अणु
		/* Route to host datagram entry. */
		काष्ठा datagram_entry *dst_entry;
		काष्ठा vmci_resource *resource;

		अगर (dg->src.context == VMCI_HYPERVISOR_CONTEXT_ID &&
		    dg->dst.resource == VMCI_EVENT_HANDLER) अणु
			वापस vmci_event_dispatch(dg);
		पूर्ण

		resource = vmci_resource_by_handle(dg->dst,
						   VMCI_RESOURCE_TYPE_DATAGRAM);
		अगर (!resource) अणु
			pr_devel("Sending to invalid destination (handle=0x%x:0x%x)\n",
				 dg->dst.context, dg->dst.resource);
			वापस VMCI_ERROR_INVALID_RESOURCE;
		पूर्ण
		dst_entry = container_of(resource, काष्ठा datagram_entry,
					 resource);
		अगर (vmci_deny_पूर्णांकeraction(src_priv_flags,
					  dst_entry->priv_flags)) अणु
			vmci_resource_put(resource);
			वापस VMCI_ERROR_NO_ACCESS;
		पूर्ण

		/*
		 * If a VMCI datagram destined क्रम the host is also sent by the
		 * host, we always run it delayed. This ensures that no locks
		 * are held when the datagram callback runs.
		 */
		अगर (dst_entry->run_delayed ||
		    dg->src.context == VMCI_HOST_CONTEXT_ID) अणु
			काष्ठा delayed_datagram_info *dg_info;

			अगर (atomic_add_वापस(1, &delayed_dg_host_queue_size)
			    == VMCI_MAX_DELAYED_DG_HOST_QUEUE_SIZE) अणु
				atomic_dec(&delayed_dg_host_queue_size);
				vmci_resource_put(resource);
				वापस VMCI_ERROR_NO_MEM;
			पूर्ण

			dg_info = kदो_स्मृति(माप(*dg_info) +
				    (माप_प्रकार) dg->payload_size, GFP_ATOMIC);
			अगर (!dg_info) अणु
				atomic_dec(&delayed_dg_host_queue_size);
				vmci_resource_put(resource);
				वापस VMCI_ERROR_NO_MEM;
			पूर्ण

			dg_info->in_dg_host_queue = true;
			dg_info->entry = dst_entry;
			स_नकल(&dg_info->msg, dg, dg_size);

			INIT_WORK(&dg_info->work, dg_delayed_dispatch);
			schedule_work(&dg_info->work);
			retval = VMCI_SUCCESS;

		पूर्ण अन्यथा अणु
			retval = dst_entry->recv_cb(dst_entry->client_data, dg);
			vmci_resource_put(resource);
			अगर (retval < VMCI_SUCCESS)
				वापस retval;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Route to destination VM context. */
		काष्ठा vmci_datagram *new_dg;

		अगर (context_id != dg->dst.context) अणु
			अगर (vmci_deny_पूर्णांकeraction(src_priv_flags,
						  vmci_context_get_priv_flags
						  (dg->dst.context))) अणु
				वापस VMCI_ERROR_NO_ACCESS;
			पूर्ण अन्यथा अगर (VMCI_CONTEXT_IS_VM(context_id)) अणु
				/*
				 * If the sending context is a VM, it
				 * cannot reach another VM.
				 */

				pr_devel("Datagram communication between VMs not supported (src=0x%x, dst=0x%x)\n",
					 context_id, dg->dst.context);
				वापस VMCI_ERROR_DST_UNREACHABLE;
			पूर्ण
		पूर्ण

		/* We make a copy to enqueue. */
		new_dg = kmemdup(dg, dg_size, GFP_KERNEL);
		अगर (new_dg == शून्य)
			वापस VMCI_ERROR_NO_MEM;

		retval = vmci_ctx_enqueue_datagram(dg->dst.context, new_dg);
		अगर (retval < VMCI_SUCCESS) अणु
			kमुक्त(new_dg);
			वापस retval;
		पूर्ण
	पूर्ण

	/*
	 * We currently truncate the size to चिन्हित 32 bits. This करोesn't
	 * matter क्रम this handler as it only support 4Kb messages.
	 */
	वापस (पूर्णांक)dg_size;
पूर्ण

/*
 * Dispatch datagram as a guest, करोwn through the VMX and potentially to
 * the host.
 * Returns number of bytes sent on success, error code otherwise.
 */
अटल पूर्णांक dg_dispatch_as_guest(काष्ठा vmci_datagram *dg)
अणु
	पूर्णांक retval;
	काष्ठा vmci_resource *resource;

	resource = vmci_resource_by_handle(dg->src,
					   VMCI_RESOURCE_TYPE_DATAGRAM);
	अगर (!resource)
		वापस VMCI_ERROR_NO_HANDLE;

	retval = vmci_send_datagram(dg);
	vmci_resource_put(resource);
	वापस retval;
पूर्ण

/*
 * Dispatch datagram.  This will determine the routing क्रम the datagram
 * and dispatch it accordingly.
 * Returns number of bytes sent on success, error code otherwise.
 */
पूर्णांक vmci_datagram_dispatch(u32 context_id,
			   काष्ठा vmci_datagram *dg, bool from_guest)
अणु
	पूर्णांक retval;
	क्रमागत vmci_route route;

	BUILD_BUG_ON(माप(काष्ठा vmci_datagram) != 24);

	अगर (dg->payload_size > VMCI_MAX_DG_SIZE ||
	    VMCI_DG_SIZE(dg) > VMCI_MAX_DG_SIZE) अणु
		pr_devel("Payload (size=%llu bytes) too big to send\n",
			 (अचिन्हित दीर्घ दीर्घ)dg->payload_size);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	retval = vmci_route(&dg->src, &dg->dst, from_guest, &route);
	अगर (retval < VMCI_SUCCESS) अणु
		pr_devel("Failed to route datagram (src=0x%x, dst=0x%x, err=%d)\n",
			 dg->src.context, dg->dst.context, retval);
		वापस retval;
	पूर्ण

	अगर (VMCI_ROUTE_AS_HOST == route) अणु
		अगर (VMCI_INVALID_ID == context_id)
			context_id = VMCI_HOST_CONTEXT_ID;
		वापस dg_dispatch_as_host(context_id, dg);
	पूर्ण

	अगर (VMCI_ROUTE_AS_GUEST == route)
		वापस dg_dispatch_as_guest(dg);

	pr_warn("Unknown route (%d) for datagram\n", route);
	वापस VMCI_ERROR_DST_UNREACHABLE;
पूर्ण

/*
 * Invoke the handler क्रम the given datagram.  This is पूर्णांकended to be
 * called only when acting as a guest and receiving a datagram from the
 * भव device.
 */
पूर्णांक vmci_datagram_invoke_guest_handler(काष्ठा vmci_datagram *dg)
अणु
	काष्ठा vmci_resource *resource;
	काष्ठा datagram_entry *dst_entry;

	resource = vmci_resource_by_handle(dg->dst,
					   VMCI_RESOURCE_TYPE_DATAGRAM);
	अगर (!resource) अणु
		pr_devel("destination (handle=0x%x:0x%x) doesn't exist\n",
			 dg->dst.context, dg->dst.resource);
		वापस VMCI_ERROR_NO_HANDLE;
	पूर्ण

	dst_entry = container_of(resource, काष्ठा datagram_entry, resource);
	अगर (dst_entry->run_delayed) अणु
		काष्ठा delayed_datagram_info *dg_info;

		dg_info = kदो_स्मृति(माप(*dg_info) + (माप_प्रकार)dg->payload_size,
				  GFP_ATOMIC);
		अगर (!dg_info) अणु
			vmci_resource_put(resource);
			वापस VMCI_ERROR_NO_MEM;
		पूर्ण

		dg_info->in_dg_host_queue = false;
		dg_info->entry = dst_entry;
		स_नकल(&dg_info->msg, dg, VMCI_DG_SIZE(dg));

		INIT_WORK(&dg_info->work, dg_delayed_dispatch);
		schedule_work(&dg_info->work);
	पूर्ण अन्यथा अणु
		dst_entry->recv_cb(dst_entry->client_data, dg);
		vmci_resource_put(resource);
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * vmci_datagram_create_handle_priv() - Create host context datagram endpoपूर्णांक
 * @resource_id:        The resource ID.
 * @flags:      Datagram Flags.
 * @priv_flags: Privilege Flags.
 * @recv_cb:    Callback when receiving datagrams.
 * @client_data:        Poपूर्णांकer क्रम a datagram_entry काष्ठा
 * @out_handle: vmci_handle that is populated as a result of this function.
 *
 * Creates a host context datagram endpoपूर्णांक and वापसs a handle to it.
 */
पूर्णांक vmci_datagram_create_handle_priv(u32 resource_id,
				     u32 flags,
				     u32 priv_flags,
				     vmci_datagram_recv_cb recv_cb,
				     व्योम *client_data,
				     काष्ठा vmci_handle *out_handle)
अणु
	अगर (out_handle == शून्य)
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (recv_cb == शून्य) अणु
		pr_devel("Client callback needed when creating datagram\n");
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	अगर (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS)
		वापस VMCI_ERROR_INVALID_ARGS;

	वापस dg_create_handle(resource_id, flags, priv_flags, recv_cb,
				client_data, out_handle);
पूर्ण
EXPORT_SYMBOL_GPL(vmci_datagram_create_handle_priv);

/*
 * vmci_datagram_create_handle() - Create host context datagram endpoपूर्णांक
 * @resource_id:        Resource ID.
 * @flags:      Datagram Flags.
 * @recv_cb:    Callback when receiving datagrams.
 * @client_ata: Poपूर्णांकer क्रम a datagram_entry काष्ठा
 * @out_handle: vmci_handle that is populated as a result of this function.
 *
 * Creates a host context datagram endpoपूर्णांक and वापसs a handle to
 * it.  Same as vmci_datagram_create_handle_priv without the priviledge
 * flags argument.
 */
पूर्णांक vmci_datagram_create_handle(u32 resource_id,
				u32 flags,
				vmci_datagram_recv_cb recv_cb,
				व्योम *client_data,
				काष्ठा vmci_handle *out_handle)
अणु
	वापस vmci_datagram_create_handle_priv(
		resource_id, flags,
		VMCI_DEFAULT_PROC_PRIVILEGE_FLAGS,
		recv_cb, client_data,
		out_handle);
पूर्ण
EXPORT_SYMBOL_GPL(vmci_datagram_create_handle);

/*
 * vmci_datagram_destroy_handle() - Destroys datagram handle
 * @handle:     vmci_handle to be destroyed and reaped.
 *
 * Use this function to destroy any datagram handles created by
 * vmci_datagram_create_handleअणु,Privपूर्ण functions.
 */
पूर्णांक vmci_datagram_destroy_handle(काष्ठा vmci_handle handle)
अणु
	काष्ठा datagram_entry *entry;
	काष्ठा vmci_resource *resource;

	resource = vmci_resource_by_handle(handle, VMCI_RESOURCE_TYPE_DATAGRAM);
	अगर (!resource) अणु
		pr_devel("Failed to destroy datagram (handle=0x%x:0x%x)\n",
			 handle.context, handle.resource);
		वापस VMCI_ERROR_NOT_FOUND;
	पूर्ण

	entry = container_of(resource, काष्ठा datagram_entry, resource);

	vmci_resource_put(&entry->resource);
	vmci_resource_हटाओ(&entry->resource);
	kमुक्त(entry);

	वापस VMCI_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_datagram_destroy_handle);

/*
 * vmci_datagram_send() - Send a datagram
 * @msg:        The datagram to send.
 *
 * Sends the provided datagram on its merry way.
 */
पूर्णांक vmci_datagram_send(काष्ठा vmci_datagram *msg)
अणु
	अगर (msg == शून्य)
		वापस VMCI_ERROR_INVALID_ARGS;

	वापस vmci_datagram_dispatch(VMCI_INVALID_ID, msg, false);
पूर्ण
EXPORT_SYMBOL_GPL(vmci_datagram_send);
