<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"

अटल bool vmci_disable_host;
module_param_named(disable_host, vmci_disable_host, bool, 0);
MODULE_PARM_DESC(disable_host,
		 "Disable driver host personality (default=enabled)");

अटल bool vmci_disable_guest;
module_param_named(disable_guest, vmci_disable_guest, bool, 0);
MODULE_PARM_DESC(disable_guest,
		 "Disable driver guest personality (default=enabled)");

अटल bool vmci_guest_personality_initialized;
अटल bool vmci_host_personality_initialized;

अटल DEFINE_MUTEX(vmci_vsock_mutex); /* protects vmci_vsock_transport_cb */
अटल vmci_vsock_cb vmci_vsock_transport_cb;
अटल bool vmci_vsock_cb_host_called;

/*
 * vmci_get_context_id() - Gets the current context ID.
 *
 * Returns the current context ID.  Note that since this is accessed only
 * from code running in the host, this always वापसs the host context ID.
 */
u32 vmci_get_context_id(व्योम)
अणु
	अगर (vmci_guest_code_active())
		वापस vmci_get_vm_context_id();
	अन्यथा अगर (vmci_host_code_active())
		वापस VMCI_HOST_CONTEXT_ID;

	वापस VMCI_INVALID_ID;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_get_context_id);

/*
 * vmci_रेजिस्टर_vsock_callback() - Register the VSOCK vmci_transport callback.
 *
 * The callback will be called when the first host or guest becomes active,
 * or अगर they are alपढ़ोy active when this function is called.
 * To unरेजिस्टर the callback, call this function with शून्य parameter.
 *
 * Returns 0 on success. -EBUSY अगर a callback is alपढ़ोy रेजिस्टरed.
 */
पूर्णांक vmci_रेजिस्टर_vsock_callback(vmci_vsock_cb callback)
अणु
	पूर्णांक err = 0;

	mutex_lock(&vmci_vsock_mutex);

	अगर (vmci_vsock_transport_cb && callback) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	vmci_vsock_transport_cb = callback;

	अगर (!vmci_vsock_transport_cb) अणु
		vmci_vsock_cb_host_called = false;
		जाओ out;
	पूर्ण

	अगर (vmci_guest_code_active())
		vmci_vsock_transport_cb(false);

	अगर (vmci_host_users() > 0) अणु
		vmci_vsock_cb_host_called = true;
		vmci_vsock_transport_cb(true);
	पूर्ण

out:
	mutex_unlock(&vmci_vsock_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_रेजिस्टर_vsock_callback);

व्योम vmci_call_vsock_callback(bool is_host)
अणु
	mutex_lock(&vmci_vsock_mutex);

	अगर (!vmci_vsock_transport_cb)
		जाओ out;

	/* In the host, this function could be called multiple बार,
	 * but we want to रेजिस्टर it only once.
	 */
	अगर (is_host) अणु
		अगर (vmci_vsock_cb_host_called)
			जाओ out;

		vmci_vsock_cb_host_called = true;
	पूर्ण

	vmci_vsock_transport_cb(is_host);
out:
	mutex_unlock(&vmci_vsock_mutex);
पूर्ण

अटल पूर्णांक __init vmci_drv_init(व्योम)
अणु
	पूर्णांक vmci_err;
	पूर्णांक error;

	vmci_err = vmci_event_init();
	अगर (vmci_err < VMCI_SUCCESS) अणु
		pr_err("Failed to initialize VMCIEvent (result=%d)\n",
		       vmci_err);
		वापस -EINVAL;
	पूर्ण

	अगर (!vmci_disable_guest) अणु
		error = vmci_guest_init();
		अगर (error) अणु
			pr_warn("Failed to initialize guest personality (err=%d)\n",
				error);
		पूर्ण अन्यथा अणु
			vmci_guest_personality_initialized = true;
			pr_info("Guest personality initialized and is %s\n",
				vmci_guest_code_active() ?
				"active" : "inactive");
		पूर्ण
	पूर्ण

	अगर (!vmci_disable_host) अणु
		error = vmci_host_init();
		अगर (error) अणु
			pr_warn("Unable to initialize host personality (err=%d)\n",
				error);
		पूर्ण अन्यथा अणु
			vmci_host_personality_initialized = true;
			pr_info("Initialized host personality\n");
		पूर्ण
	पूर्ण

	अगर (!vmci_guest_personality_initialized &&
	    !vmci_host_personality_initialized) अणु
		vmci_event_निकास();
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
module_init(vmci_drv_init);

अटल व्योम __निकास vmci_drv_निकास(व्योम)
अणु
	अगर (vmci_guest_personality_initialized)
		vmci_guest_निकास();

	अगर (vmci_host_personality_initialized)
		vmci_host_निकास();

	vmci_event_निकास();
पूर्ण
module_निकास(vmci_drv_निकास);

MODULE_AUTHOR("VMware, Inc.");
MODULE_DESCRIPTION("VMware Virtual Machine Communication Interface.");
MODULE_VERSION("1.1.6.0-k");
MODULE_LICENSE("GPL v2");
