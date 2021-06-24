<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>

#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_route.h"

/*
 * Make a routing decision क्रम the given source and destination handles.
 * This will try to determine the route using the handles and the available
 * devices.  Will set the source context अगर it is invalid.
 */
पूर्णांक vmci_route(काष्ठा vmci_handle *src,
	       स्थिर काष्ठा vmci_handle *dst,
	       bool from_guest,
	       क्रमागत vmci_route *route)
अणु
	bool has_host_device = vmci_host_code_active();
	bool has_guest_device = vmci_guest_code_active();

	*route = VMCI_ROUTE_NONE;

	/*
	 * "from_guest" is only ever set to true by
	 * IOCTL_VMCI_DATAGRAM_SEND (or by the vmkernel equivalent),
	 * which comes from the VMX, so we know it is coming from a
	 * guest.
	 *
	 * To aव्योम inconsistencies, test these once.  We will test
	 * them again when we करो the actual send to ensure that we करो
	 * not touch a non-existent device.
	 */

	/* Must have a valid destination context. */
	अगर (VMCI_INVALID_ID == dst->context)
		वापस VMCI_ERROR_INVALID_ARGS;

	/* Anywhere to hypervisor. */
	अगर (VMCI_HYPERVISOR_CONTEXT_ID == dst->context) अणु

		/*
		 * If this message alपढ़ोy came from a guest then we
		 * cannot send it to the hypervisor.  It must come
		 * from a local client.
		 */
		अगर (from_guest)
			वापस VMCI_ERROR_DST_UNREACHABLE;

		/*
		 * We must be acting as a guest in order to send to
		 * the hypervisor.
		 */
		अगर (!has_guest_device)
			वापस VMCI_ERROR_DEVICE_NOT_FOUND;

		/* And we cannot send अगर the source is the host context. */
		अगर (VMCI_HOST_CONTEXT_ID == src->context)
			वापस VMCI_ERROR_INVALID_ARGS;

		/*
		 * If the client passed the ANON source handle then
		 * respect it (both context and resource are invalid).
		 * However, अगर they passed only an invalid context,
		 * then they probably mean ANY, in which हाल we
		 * should set the real context here beक्रमe passing it
		 * करोwn.
		 */
		अगर (VMCI_INVALID_ID == src->context &&
		    VMCI_INVALID_ID != src->resource)
			src->context = vmci_get_context_id();

		/* Send from local client करोwn to the hypervisor. */
		*route = VMCI_ROUTE_AS_GUEST;
		वापस VMCI_SUCCESS;
	पूर्ण

	/* Anywhere to local client on host. */
	अगर (VMCI_HOST_CONTEXT_ID == dst->context) अणु
		/*
		 * If it is not from a guest but we are acting as a
		 * guest, then we need to send it करोwn to the host.
		 * Note that अगर we are also acting as a host then this
		 * will prevent us from sending from local client to
		 * local client, but we accept that restriction as a
		 * way to हटाओ any ambiguity from the host context.
		 */
		अगर (src->context == VMCI_HYPERVISOR_CONTEXT_ID) अणु
			/*
			 * If the hypervisor is the source, this is
			 * host local communication. The hypervisor
			 * may send vmci event datagrams to the host
			 * itself, but it will never send datagrams to
			 * an "outer host" through the guest device.
			 */

			अगर (has_host_device) अणु
				*route = VMCI_ROUTE_AS_HOST;
				वापस VMCI_SUCCESS;
			पूर्ण अन्यथा अणु
				वापस VMCI_ERROR_DEVICE_NOT_FOUND;
			पूर्ण
		पूर्ण

		अगर (!from_guest && has_guest_device) अणु
			/* If no source context then use the current. */
			अगर (VMCI_INVALID_ID == src->context)
				src->context = vmci_get_context_id();

			/* Send it from local client करोwn to the host. */
			*route = VMCI_ROUTE_AS_GUEST;
			वापस VMCI_SUCCESS;
		पूर्ण

		/*
		 * Otherwise we alपढ़ोy received it from a guest and
		 * it is destined क्रम a local client on this host, or
		 * it is from another local client on this host.  We
		 * must be acting as a host to service it.
		 */
		अगर (!has_host_device)
			वापस VMCI_ERROR_DEVICE_NOT_FOUND;

		अगर (VMCI_INVALID_ID == src->context) अणु
			/*
			 * If it came from a guest then it must have a
			 * valid context.  Otherwise we can use the
			 * host context.
			 */
			अगर (from_guest)
				वापस VMCI_ERROR_INVALID_ARGS;

			src->context = VMCI_HOST_CONTEXT_ID;
		पूर्ण

		/* Route to local client. */
		*route = VMCI_ROUTE_AS_HOST;
		वापस VMCI_SUCCESS;
	पूर्ण

	/*
	 * If we are acting as a host then this might be destined क्रम
	 * a guest.
	 */
	अगर (has_host_device) अणु
		/* It will have a context अगर it is meant क्रम a guest. */
		अगर (vmci_ctx_exists(dst->context)) अणु
			अगर (VMCI_INVALID_ID == src->context) अणु
				/*
				 * If it came from a guest then it
				 * must have a valid context.
				 * Otherwise we can use the host
				 * context.
				 */

				अगर (from_guest)
					वापस VMCI_ERROR_INVALID_ARGS;

				src->context = VMCI_HOST_CONTEXT_ID;
			पूर्ण अन्यथा अगर (VMCI_CONTEXT_IS_VM(src->context) &&
				   src->context != dst->context) अणु
				/*
				 * VM to VM communication is not
				 * allowed. Since we catch all
				 * communication destined क्रम the host
				 * above, this must be destined क्रम a
				 * VM since there is a valid context.
				 */

				वापस VMCI_ERROR_DST_UNREACHABLE;
			पूर्ण

			/* Pass it up to the guest. */
			*route = VMCI_ROUTE_AS_HOST;
			वापस VMCI_SUCCESS;
		पूर्ण अन्यथा अगर (!has_guest_device) अणु
			/*
			 * The host is attempting to reach a CID
			 * without an active context, and we can't
			 * send it करोwn, since we have no guest
			 * device.
			 */

			वापस VMCI_ERROR_DST_UNREACHABLE;
		पूर्ण
	पूर्ण

	/*
	 * We must be a guest trying to send to another guest, which means
	 * we need to send it करोwn to the host. We करो not filter out VM to
	 * VM communication here, since we want to be able to use the guest
	 * driver on older versions that करो support VM to VM communication.
	 */
	अगर (!has_guest_device) अणु
		/*
		 * Ending up here means we have neither guest nor host
		 * device.
		 */
		वापस VMCI_ERROR_DEVICE_NOT_FOUND;
	पूर्ण

	/* If no source context then use the current context. */
	अगर (VMCI_INVALID_ID == src->context)
		src->context = vmci_get_context_id();

	/*
	 * Send it from local client करोwn to the host, which will
	 * route it to the other guest क्रम us.
	 */
	*route = VMCI_ROUTE_AS_GUEST;
	वापस VMCI_SUCCESS;
पूर्ण
