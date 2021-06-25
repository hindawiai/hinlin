<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>

#समावेश "vmci_handle_array.h"
#समावेश "vmci_queue_pair.h"
#समावेश "vmci_datagram.h"
#समावेश "vmci_doorbell.h"
#समावेश "vmci_resource.h"
#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"

#घोषणा VMCI_UTIL_NUM_RESOURCES 1

क्रमागत अणु
	VMCI_NOTIFY_RESOURCE_QUEUE_PAIR = 0,
	VMCI_NOTIFY_RESOURCE_DOOR_BELL = 1,
पूर्ण;

क्रमागत अणु
	VMCI_NOTIFY_RESOURCE_ACTION_NOTIFY = 0,
	VMCI_NOTIFY_RESOURCE_ACTION_CREATE = 1,
	VMCI_NOTIFY_RESOURCE_ACTION_DESTROY = 2,
पूर्ण;

/*
 * VMCI driver initialization. This block can also be used to
 * pass initial group membership etc.
 */
काष्ठा vmci_init_blk अणु
	u32 cid;
	u32 flags;
पूर्ण;

/* VMCIqueue_pairAllocInfo_VMToVM */
काष्ठा vmci_qp_alloc_info_vmvm अणु
	काष्ठा vmci_handle handle;
	u32 peer;
	u32 flags;
	u64 produce_size;
	u64 consume_size;
	u64 produce_page_file;	  /* User VA. */
	u64 consume_page_file;	  /* User VA. */
	u64 produce_page_file_size;  /* Size of the file name array. */
	u64 consume_page_file_size;  /* Size of the file name array. */
	s32 result;
	u32 _pad;
पूर्ण;

/* VMCISetNotअगरyInfo: Used to pass notअगरy flag's address to the host driver. */
काष्ठा vmci_set_notअगरy_info अणु
	u64 notअगरy_uva;
	s32 result;
	u32 _pad;
पूर्ण;

/*
 * Per-instance host state
 */
काष्ठा vmci_host_dev अणु
	काष्ठा vmci_ctx *context;
	पूर्णांक user_version;
	क्रमागत vmci_obj_type ct_type;
	काष्ठा mutex lock;  /* Mutex lock क्रम vmci context access */
पूर्ण;

अटल काष्ठा vmci_ctx *host_context;
अटल bool vmci_host_device_initialized;
अटल atomic_t vmci_host_active_users = ATOMIC_INIT(0);

/*
 * Determines whether the VMCI host personality is
 * available. Since the core functionality of the host driver is
 * always present, all guests could possibly use the host
 * personality. However, to minimize the deviation from the
 * pre-unअगरied driver state of affairs, we only consider the host
 * device active अगर there is no active guest device or अगर there
 * are VMX'en with active VMCI contexts using the host device.
 */
bool vmci_host_code_active(व्योम)
अणु
	वापस vmci_host_device_initialized &&
	    (!vmci_guest_code_active() ||
	     atomic_पढ़ो(&vmci_host_active_users) > 0);
पूर्ण

पूर्णांक vmci_host_users(व्योम)
अणु
	वापस atomic_पढ़ो(&vmci_host_active_users);
पूर्ण

/*
 * Called on खोलो of /dev/vmci.
 */
अटल पूर्णांक vmci_host_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा vmci_host_dev *vmci_host_dev;

	vmci_host_dev = kzalloc(माप(काष्ठा vmci_host_dev), GFP_KERNEL);
	अगर (vmci_host_dev == शून्य)
		वापस -ENOMEM;

	vmci_host_dev->ct_type = VMCIOBJ_NOT_SET;
	mutex_init(&vmci_host_dev->lock);
	filp->निजी_data = vmci_host_dev;

	वापस 0;
पूर्ण

/*
 * Called on बंद of /dev/vmci, most often when the process
 * निकासs.
 */
अटल पूर्णांक vmci_host_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा vmci_host_dev *vmci_host_dev = filp->निजी_data;

	अगर (vmci_host_dev->ct_type == VMCIOBJ_CONTEXT) अणु
		vmci_ctx_destroy(vmci_host_dev->context);
		vmci_host_dev->context = शून्य;

		/*
		 * The number of active contexts is used to track whether any
		 * VMX'en are using the host personality. It is incremented when
		 * a context is created through the IOCTL_VMCI_INIT_CONTEXT
		 * ioctl.
		 */
		atomic_dec(&vmci_host_active_users);
	पूर्ण
	vmci_host_dev->ct_type = VMCIOBJ_NOT_SET;

	kमुक्त(vmci_host_dev);
	filp->निजी_data = शून्य;
	वापस 0;
पूर्ण

/*
 * This is used to wake up the VMX when a VMCI call arrives, or
 * to wake up select() or poll() at the next घड़ी tick.
 */
अटल __poll_t vmci_host_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा vmci_host_dev *vmci_host_dev = filp->निजी_data;
	काष्ठा vmci_ctx *context = vmci_host_dev->context;
	__poll_t mask = 0;

	अगर (vmci_host_dev->ct_type == VMCIOBJ_CONTEXT) अणु
		/* Check क्रम VMCI calls to this VM context. */
		अगर (रुको)
			poll_रुको(filp, &context->host_context.रुको_queue,
				  रुको);

		spin_lock(&context->lock);
		अगर (context->pending_datagrams > 0 ||
		    vmci_handle_arr_get_size(
				context->pending_करोorbell_array) > 0) अणु
			mask = EPOLLIN;
		पूर्ण
		spin_unlock(&context->lock);
	पूर्ण
	वापस mask;
पूर्ण

/*
 * Copies the handles of a handle array पूर्णांकo a user buffer, and
 * वापसs the new length in userBufferSize. If the copy to the
 * user buffer fails, the functions still वापसs VMCI_SUCCESS,
 * but retval != 0.
 */
अटल पूर्णांक drv_cp_harray_to_user(व्योम __user *user_buf_uva,
				 u64 *user_buf_size,
				 काष्ठा vmci_handle_arr *handle_array,
				 पूर्णांक *retval)
अणु
	u32 array_size = 0;
	काष्ठा vmci_handle *handles;

	अगर (handle_array)
		array_size = vmci_handle_arr_get_size(handle_array);

	अगर (array_size * माप(*handles) > *user_buf_size)
		वापस VMCI_ERROR_MORE_DATA;

	*user_buf_size = array_size * माप(*handles);
	अगर (*user_buf_size)
		*retval = copy_to_user(user_buf_uva,
				       vmci_handle_arr_get_handles
				       (handle_array), *user_buf_size);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Sets up a given context क्रम notअगरy to work. Maps the notअगरy
 * boolean in user VA पूर्णांकo kernel space.
 */
अटल पूर्णांक vmci_host_setup_notअगरy(काष्ठा vmci_ctx *context,
				  अचिन्हित दीर्घ uva)
अणु
	पूर्णांक retval;

	अगर (context->notअगरy_page) अणु
		pr_devel("%s: Notify mechanism is already set up\n", __func__);
		वापस VMCI_ERROR_DUPLICATE_ENTRY;
	पूर्ण

	/*
	 * We are using 'bool' internally, but let's make sure we explicit
	 * about the size.
	 */
	BUILD_BUG_ON(माप(bool) != माप(u8));

	/*
	 * Lock physical page backing a given user VA.
	 */
	retval = get_user_pages_fast(uva, 1, FOLL_WRITE, &context->notअगरy_page);
	अगर (retval != 1) अणु
		context->notअगरy_page = शून्य;
		वापस VMCI_ERROR_GENERIC;
	पूर्ण

	/*
	 * Map the locked page and set up notअगरy poपूर्णांकer.
	 */
	context->notअगरy = kmap(context->notअगरy_page) + (uva & (PAGE_SIZE - 1));
	vmci_ctx_check_संकेत_notअगरy(context);

	वापस VMCI_SUCCESS;
पूर्ण

अटल पूर्णांक vmci_host_get_version(काष्ठा vmci_host_dev *vmci_host_dev,
				 अचिन्हित पूर्णांक cmd, व्योम __user *uptr)
अणु
	अगर (cmd == IOCTL_VMCI_VERSION2) अणु
		पूर्णांक __user *vptr = uptr;
		अगर (get_user(vmci_host_dev->user_version, vptr))
			वापस -EFAULT;
	पूर्ण

	/*
	 * The basic logic here is:
	 *
	 * If the user sends in a version of 0 tell it our version.
	 * If the user didn't send in a version, tell it our version.
	 * If the user sent in an old version, tell it -its- version.
	 * If the user sent in an newer version, tell it our version.
	 *
	 * The rationale behind telling the caller its version is that
	 * Workstation 6.5 required that VMX and VMCI kernel module were
	 * version sync'd.  All new VMX users will be programmed to
	 * handle the VMCI kernel module version.
	 */

	अगर (vmci_host_dev->user_version > 0 &&
	    vmci_host_dev->user_version < VMCI_VERSION_HOSTQP) अणु
		वापस vmci_host_dev->user_version;
	पूर्ण

	वापस VMCI_VERSION;
पूर्ण

#घोषणा vmci_ioctl_err(fmt, ...)	\
	pr_devel("%s: " fmt, ioctl_name, ##__VA_ARGS__)

अटल पूर्णांक vmci_host_करो_init_context(काष्ठा vmci_host_dev *vmci_host_dev,
				     स्थिर अक्षर *ioctl_name,
				     व्योम __user *uptr)
अणु
	काष्ठा vmci_init_blk init_block;
	स्थिर काष्ठा cred *cred;
	पूर्णांक retval;

	अगर (copy_from_user(&init_block, uptr, माप(init_block))) अणु
		vmci_ioctl_err("error reading init block\n");
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&vmci_host_dev->lock);

	अगर (vmci_host_dev->ct_type != VMCIOBJ_NOT_SET) अणु
		vmci_ioctl_err("received VMCI init on initialized handle\n");
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (init_block.flags & ~VMCI_PRIVILEGE_FLAG_RESTRICTED) अणु
		vmci_ioctl_err("unsupported VMCI restriction flag\n");
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	cred = get_current_cred();
	vmci_host_dev->context = vmci_ctx_create(init_block.cid,
						 init_block.flags, 0,
						 vmci_host_dev->user_version,
						 cred);
	put_cred(cred);
	अगर (IS_ERR(vmci_host_dev->context)) अणु
		retval = PTR_ERR(vmci_host_dev->context);
		vmci_ioctl_err("error initializing context\n");
		जाओ out;
	पूर्ण

	/*
	 * Copy cid to userlevel, we करो this to allow the VMX
	 * to enक्रमce its policy on cid generation.
	 */
	init_block.cid = vmci_ctx_get_id(vmci_host_dev->context);
	अगर (copy_to_user(uptr, &init_block, माप(init_block))) अणु
		vmci_ctx_destroy(vmci_host_dev->context);
		vmci_host_dev->context = शून्य;
		vmci_ioctl_err("error writing init block\n");
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	vmci_host_dev->ct_type = VMCIOBJ_CONTEXT;
	atomic_inc(&vmci_host_active_users);

	vmci_call_vsock_callback(true);

	retval = 0;

out:
	mutex_unlock(&vmci_host_dev->lock);
	वापस retval;
पूर्ण

अटल पूर्णांक vmci_host_करो_send_datagram(काष्ठा vmci_host_dev *vmci_host_dev,
				      स्थिर अक्षर *ioctl_name,
				      व्योम __user *uptr)
अणु
	काष्ठा vmci_datagram_snd_rcv_info send_info;
	काष्ठा vmci_datagram *dg = शून्य;
	u32 cid;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&send_info, uptr, माप(send_info)))
		वापस -EFAULT;

	अगर (send_info.len > VMCI_MAX_DG_SIZE) अणु
		vmci_ioctl_err("datagram is too big (size=%d)\n",
			       send_info.len);
		वापस -EINVAL;
	पूर्ण

	अगर (send_info.len < माप(*dg)) अणु
		vmci_ioctl_err("datagram is too small (size=%d)\n",
			       send_info.len);
		वापस -EINVAL;
	पूर्ण

	dg = memdup_user((व्योम __user *)(uपूर्णांकptr_t)send_info.addr,
			 send_info.len);
	अगर (IS_ERR(dg)) अणु
		vmci_ioctl_err(
			"cannot allocate memory to dispatch datagram\n");
		वापस PTR_ERR(dg);
	पूर्ण

	अगर (VMCI_DG_SIZE(dg) != send_info.len) अणु
		vmci_ioctl_err("datagram size mismatch\n");
		kमुक्त(dg);
		वापस -EINVAL;
	पूर्ण

	pr_devel("Datagram dst (handle=0x%x:0x%x) src (handle=0x%x:0x%x), payload (size=%llu bytes)\n",
		 dg->dst.context, dg->dst.resource,
		 dg->src.context, dg->src.resource,
		 (अचिन्हित दीर्घ दीर्घ)dg->payload_size);

	/* Get source context id. */
	cid = vmci_ctx_get_id(vmci_host_dev->context);
	send_info.result = vmci_datagram_dispatch(cid, dg, true);
	kमुक्त(dg);

	वापस copy_to_user(uptr, &send_info, माप(send_info)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_receive_datagram(काष्ठा vmci_host_dev *vmci_host_dev,
					 स्थिर अक्षर *ioctl_name,
					 व्योम __user *uptr)
अणु
	काष्ठा vmci_datagram_snd_rcv_info recv_info;
	काष्ठा vmci_datagram *dg = शून्य;
	पूर्णांक retval;
	माप_प्रकार size;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&recv_info, uptr, माप(recv_info)))
		वापस -EFAULT;

	size = recv_info.len;
	recv_info.result = vmci_ctx_dequeue_datagram(vmci_host_dev->context,
						     &size, &dg);

	अगर (recv_info.result >= VMCI_SUCCESS) अणु
		व्योम __user *ubuf = (व्योम __user *)(uपूर्णांकptr_t)recv_info.addr;
		retval = copy_to_user(ubuf, dg, VMCI_DG_SIZE(dg));
		kमुक्त(dg);
		अगर (retval != 0)
			वापस -EFAULT;
	पूर्ण

	वापस copy_to_user(uptr, &recv_info, माप(recv_info)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_alloc_queuepair(काष्ठा vmci_host_dev *vmci_host_dev,
					स्थिर अक्षर *ioctl_name,
					व्योम __user *uptr)
अणु
	काष्ठा vmci_handle handle;
	पूर्णांक vmci_status;
	पूर्णांक __user *retptr;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vmci_host_dev->user_version < VMCI_VERSION_NOVMVM) अणु
		काष्ठा vmci_qp_alloc_info_vmvm alloc_info;
		काष्ठा vmci_qp_alloc_info_vmvm __user *info = uptr;

		अगर (copy_from_user(&alloc_info, uptr, माप(alloc_info)))
			वापस -EFAULT;

		handle = alloc_info.handle;
		retptr = &info->result;

		vmci_status = vmci_qp_broker_alloc(alloc_info.handle,
						alloc_info.peer,
						alloc_info.flags,
						VMCI_NO_PRIVILEGE_FLAGS,
						alloc_info.produce_size,
						alloc_info.consume_size,
						शून्य,
						vmci_host_dev->context);

		अगर (vmci_status == VMCI_SUCCESS)
			vmci_status = VMCI_SUCCESS_QUEUEPAIR_CREATE;
	पूर्ण अन्यथा अणु
		काष्ठा vmci_qp_alloc_info alloc_info;
		काष्ठा vmci_qp_alloc_info __user *info = uptr;
		काष्ठा vmci_qp_page_store page_store;

		अगर (copy_from_user(&alloc_info, uptr, माप(alloc_info)))
			वापस -EFAULT;

		handle = alloc_info.handle;
		retptr = &info->result;

		page_store.pages = alloc_info.ppn_va;
		page_store.len = alloc_info.num_ppns;

		vmci_status = vmci_qp_broker_alloc(alloc_info.handle,
						alloc_info.peer,
						alloc_info.flags,
						VMCI_NO_PRIVILEGE_FLAGS,
						alloc_info.produce_size,
						alloc_info.consume_size,
						&page_store,
						vmci_host_dev->context);
	पूर्ण

	अगर (put_user(vmci_status, retptr)) अणु
		अगर (vmci_status >= VMCI_SUCCESS) अणु
			vmci_status = vmci_qp_broker_detach(handle,
							vmci_host_dev->context);
		पूर्ण
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_queuepair_setva(काष्ठा vmci_host_dev *vmci_host_dev,
					स्थिर अक्षर *ioctl_name,
					व्योम __user *uptr)
अणु
	काष्ठा vmci_qp_set_va_info set_va_info;
	काष्ठा vmci_qp_set_va_info __user *info = uptr;
	s32 result;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vmci_host_dev->user_version < VMCI_VERSION_NOVMVM) अणु
		vmci_ioctl_err("is not allowed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&set_va_info, uptr, माप(set_va_info)))
		वापस -EFAULT;

	अगर (set_va_info.va) अणु
		/*
		 * VMX is passing करोwn a new VA क्रम the queue
		 * pair mapping.
		 */
		result = vmci_qp_broker_map(set_va_info.handle,
					    vmci_host_dev->context,
					    set_va_info.va);
	पूर्ण अन्यथा अणु
		/*
		 * The queue pair is about to be unmapped by
		 * the VMX.
		 */
		result = vmci_qp_broker_unmap(set_va_info.handle,
					 vmci_host_dev->context, 0);
	पूर्ण

	वापस put_user(result, &info->result) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_queuepair_setpf(काष्ठा vmci_host_dev *vmci_host_dev,
					स्थिर अक्षर *ioctl_name,
					व्योम __user *uptr)
अणु
	काष्ठा vmci_qp_page_file_info page_file_info;
	काष्ठा vmci_qp_page_file_info __user *info = uptr;
	s32 result;

	अगर (vmci_host_dev->user_version < VMCI_VERSION_HOSTQP ||
	    vmci_host_dev->user_version >= VMCI_VERSION_NOVMVM) अणु
		vmci_ioctl_err("not supported on this VMX (version=%d)\n",
			       vmci_host_dev->user_version);
		वापस -EINVAL;
	पूर्ण

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&page_file_info, uptr, माप(*info)))
		वापस -EFAULT;

	/*
	 * Communicate success pre-emptively to the caller.  Note that the
	 * basic premise is that it is incumbent upon the caller not to look at
	 * the info.result field until after the ioctl() वापसs.  And then,
	 * only अगर the ioctl() result indicates no error.  We send up the
	 * SUCCESS status beक्रमe calling SetPageStore() store because failing
	 * to copy up the result code means unwinding the SetPageStore().
	 *
	 * It turns out the logic to unwind a SetPageStore() खोलोs a can of
	 * worms.  For example, अगर a host had created the queue_pair and a
	 * guest attaches and SetPageStore() is successful but writing success
	 * fails, then ... the host has to be stopped from writing (anymore)
	 * data पूर्णांकo the queue_pair.  That means an additional test in the
	 * VMCI_Enqueue() code path.  Ugh.
	 */

	अगर (put_user(VMCI_SUCCESS, &info->result)) अणु
		/*
		 * In this हाल, we can't ग_लिखो a result field of the
		 * caller's info block.  So, we don't even try to
		 * SetPageStore().
		 */
		वापस -EFAULT;
	पूर्ण

	result = vmci_qp_broker_set_page_store(page_file_info.handle,
						page_file_info.produce_va,
						page_file_info.consume_va,
						vmci_host_dev->context);
	अगर (result < VMCI_SUCCESS) अणु
		अगर (put_user(result, &info->result)) अणु
			/*
			 * Note that in this हाल the SetPageStore()
			 * call failed but we were unable to
			 * communicate that to the caller (because the
			 * copy_to_user() call failed).  So, अगर we
			 * simply वापस an error (in this हाल
			 * -EFAULT) then the caller will know that the
			 *  SetPageStore failed even though we couldn't
			 *  put the result code in the result field and
			 *  indicate exactly why it failed.
			 *
			 * That says nothing about the issue where we
			 * were once able to ग_लिखो to the caller's info
			 * memory and now can't.  Something more
			 * serious is probably going on than the fact
			 * that SetPageStore() didn't work.
			 */
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_qp_detach(काष्ठा vmci_host_dev *vmci_host_dev,
				  स्थिर अक्षर *ioctl_name,
				  व्योम __user *uptr)
अणु
	काष्ठा vmci_qp_dtch_info detach_info;
	काष्ठा vmci_qp_dtch_info __user *info = uptr;
	s32 result;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&detach_info, uptr, माप(detach_info)))
		वापस -EFAULT;

	result = vmci_qp_broker_detach(detach_info.handle,
				       vmci_host_dev->context);
	अगर (result == VMCI_SUCCESS &&
	    vmci_host_dev->user_version < VMCI_VERSION_NOVMVM) अणु
		result = VMCI_SUCCESS_LAST_DETACH;
	पूर्ण

	वापस put_user(result, &info->result) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_ctx_add_notअगरy(काष्ठा vmci_host_dev *vmci_host_dev,
				       स्थिर अक्षर *ioctl_name,
				       व्योम __user *uptr)
अणु
	काष्ठा vmci_ctx_info ar_info;
	काष्ठा vmci_ctx_info __user *info = uptr;
	s32 result;
	u32 cid;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&ar_info, uptr, माप(ar_info)))
		वापस -EFAULT;

	cid = vmci_ctx_get_id(vmci_host_dev->context);
	result = vmci_ctx_add_notअगरication(cid, ar_info.remote_cid);

	वापस put_user(result, &info->result) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_ctx_हटाओ_notअगरy(काष्ठा vmci_host_dev *vmci_host_dev,
					  स्थिर अक्षर *ioctl_name,
					  व्योम __user *uptr)
अणु
	काष्ठा vmci_ctx_info ar_info;
	काष्ठा vmci_ctx_info __user *info = uptr;
	u32 cid;
	पूर्णांक result;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&ar_info, uptr, माप(ar_info)))
		वापस -EFAULT;

	cid = vmci_ctx_get_id(vmci_host_dev->context);
	result = vmci_ctx_हटाओ_notअगरication(cid,
					      ar_info.remote_cid);

	वापस put_user(result, &info->result) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_ctx_get_cpt_state(काष्ठा vmci_host_dev *vmci_host_dev,
					  स्थिर अक्षर *ioctl_name,
					  व्योम __user *uptr)
अणु
	काष्ठा vmci_ctx_chkpt_buf_info get_info;
	u32 cid;
	व्योम *cpt_buf;
	पूर्णांक retval;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&get_info, uptr, माप(get_info)))
		वापस -EFAULT;

	cid = vmci_ctx_get_id(vmci_host_dev->context);
	get_info.result = vmci_ctx_get_chkpt_state(cid, get_info.cpt_type,
						&get_info.buf_size, &cpt_buf);
	अगर (get_info.result == VMCI_SUCCESS && get_info.buf_size) अणु
		व्योम __user *ubuf = (व्योम __user *)(uपूर्णांकptr_t)get_info.cpt_buf;
		retval = copy_to_user(ubuf, cpt_buf, get_info.buf_size);
		kमुक्त(cpt_buf);

		अगर (retval)
			वापस -EFAULT;
	पूर्ण

	वापस copy_to_user(uptr, &get_info, माप(get_info)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_ctx_set_cpt_state(काष्ठा vmci_host_dev *vmci_host_dev,
					  स्थिर अक्षर *ioctl_name,
					  व्योम __user *uptr)
अणु
	काष्ठा vmci_ctx_chkpt_buf_info set_info;
	u32 cid;
	व्योम *cpt_buf;
	पूर्णांक retval;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&set_info, uptr, माप(set_info)))
		वापस -EFAULT;

	cpt_buf = memdup_user((व्योम __user *)(uपूर्णांकptr_t)set_info.cpt_buf,
				set_info.buf_size);
	अगर (IS_ERR(cpt_buf))
		वापस PTR_ERR(cpt_buf);

	cid = vmci_ctx_get_id(vmci_host_dev->context);
	set_info.result = vmci_ctx_set_chkpt_state(cid, set_info.cpt_type,
						   set_info.buf_size, cpt_buf);

	retval = copy_to_user(uptr, &set_info, माप(set_info)) ? -EFAULT : 0;

	kमुक्त(cpt_buf);
	वापस retval;
पूर्ण

अटल पूर्णांक vmci_host_करो_get_context_id(काष्ठा vmci_host_dev *vmci_host_dev,
				       स्थिर अक्षर *ioctl_name,
				       व्योम __user *uptr)
अणु
	u32 __user *u32ptr = uptr;

	वापस put_user(VMCI_HOST_CONTEXT_ID, u32ptr) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_set_notअगरy(काष्ठा vmci_host_dev *vmci_host_dev,
				   स्थिर अक्षर *ioctl_name,
				   व्योम __user *uptr)
अणु
	काष्ठा vmci_set_notअगरy_info notअगरy_info;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&notअगरy_info, uptr, माप(notअगरy_info)))
		वापस -EFAULT;

	अगर (notअगरy_info.notअगरy_uva) अणु
		notअगरy_info.result =
			vmci_host_setup_notअगरy(vmci_host_dev->context,
					       notअगरy_info.notअगरy_uva);
	पूर्ण अन्यथा अणु
		vmci_ctx_unset_notअगरy(vmci_host_dev->context);
		notअगरy_info.result = VMCI_SUCCESS;
	पूर्ण

	वापस copy_to_user(uptr, &notअगरy_info, माप(notअगरy_info)) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_notअगरy_resource(काष्ठा vmci_host_dev *vmci_host_dev,
					स्थिर अक्षर *ioctl_name,
					व्योम __user *uptr)
अणु
	काष्ठा vmci_dbell_notअगरy_resource_info info;
	u32 cid;

	अगर (vmci_host_dev->user_version < VMCI_VERSION_NOTIFY) अणु
		vmci_ioctl_err("invalid for current VMX versions\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&info, uptr, माप(info)))
		वापस -EFAULT;

	cid = vmci_ctx_get_id(vmci_host_dev->context);

	चयन (info.action) अणु
	हाल VMCI_NOTIFY_RESOURCE_ACTION_NOTIFY:
		अगर (info.resource == VMCI_NOTIFY_RESOURCE_DOOR_BELL) अणु
			u32 flags = VMCI_NO_PRIVILEGE_FLAGS;
			info.result = vmci_ctx_notअगरy_dbell(cid, info.handle,
							    flags);
		पूर्ण अन्यथा अणु
			info.result = VMCI_ERROR_UNAVAILABLE;
		पूर्ण
		अवरोध;

	हाल VMCI_NOTIFY_RESOURCE_ACTION_CREATE:
		info.result = vmci_ctx_dbell_create(cid, info.handle);
		अवरोध;

	हाल VMCI_NOTIFY_RESOURCE_ACTION_DESTROY:
		info.result = vmci_ctx_dbell_destroy(cid, info.handle);
		अवरोध;

	शेष:
		vmci_ioctl_err("got unknown action (action=%d)\n",
			       info.action);
		info.result = VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	वापस copy_to_user(uptr, &info, माप(info)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक vmci_host_करो_recv_notअगरications(काष्ठा vmci_host_dev *vmci_host_dev,
					   स्थिर अक्षर *ioctl_name,
					   व्योम __user *uptr)
अणु
	काष्ठा vmci_ctx_notअगरy_recv_info info;
	काष्ठा vmci_handle_arr *db_handle_array;
	काष्ठा vmci_handle_arr *qp_handle_array;
	व्योम __user *ubuf;
	u32 cid;
	पूर्णांक retval = 0;

	अगर (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) अणु
		vmci_ioctl_err("only valid for contexts\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vmci_host_dev->user_version < VMCI_VERSION_NOTIFY) अणु
		vmci_ioctl_err("not supported for the current vmx version\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&info, uptr, माप(info)))
		वापस -EFAULT;

	अगर ((info.db_handle_buf_size && !info.db_handle_buf_uva) ||
	    (info.qp_handle_buf_size && !info.qp_handle_buf_uva)) अणु
		वापस -EINVAL;
	पूर्ण

	cid = vmci_ctx_get_id(vmci_host_dev->context);

	info.result = vmci_ctx_rcv_notअगरications_get(cid,
				&db_handle_array, &qp_handle_array);
	अगर (info.result != VMCI_SUCCESS)
		वापस copy_to_user(uptr, &info, माप(info)) ? -EFAULT : 0;

	ubuf = (व्योम __user *)(uपूर्णांकptr_t)info.db_handle_buf_uva;
	info.result = drv_cp_harray_to_user(ubuf, &info.db_handle_buf_size,
					    db_handle_array, &retval);
	अगर (info.result == VMCI_SUCCESS && !retval) अणु
		ubuf = (व्योम __user *)(uपूर्णांकptr_t)info.qp_handle_buf_uva;
		info.result = drv_cp_harray_to_user(ubuf,
						    &info.qp_handle_buf_size,
						    qp_handle_array, &retval);
	पूर्ण

	अगर (!retval && copy_to_user(uptr, &info, माप(info)))
		retval = -EFAULT;

	vmci_ctx_rcv_notअगरications_release(cid,
				db_handle_array, qp_handle_array,
				info.result == VMCI_SUCCESS && !retval);

	वापस retval;
पूर्ण

अटल दीर्घ vmci_host_unlocked_ioctl(काष्ठा file *filp,
				     अचिन्हित पूर्णांक iocmd, अचिन्हित दीर्घ ioarg)
अणु
#घोषणा VMCI_DO_IOCTL(ioctl_name, ioctl_fn) करो अणु			\
		अक्षर *name = "IOCTL_VMCI_" # ioctl_name;		\
		वापस vmci_host_करो_ ## ioctl_fn(			\
			vmci_host_dev, name, uptr);			\
	पूर्ण जबतक (0)

	काष्ठा vmci_host_dev *vmci_host_dev = filp->निजी_data;
	व्योम __user *uptr = (व्योम __user *)ioarg;

	चयन (iocmd) अणु
	हाल IOCTL_VMCI_INIT_CONTEXT:
		VMCI_DO_IOCTL(INIT_CONTEXT, init_context);
	हाल IOCTL_VMCI_DATAGRAM_SEND:
		VMCI_DO_IOCTL(DATAGRAM_SEND, send_datagram);
	हाल IOCTL_VMCI_DATAGRAM_RECEIVE:
		VMCI_DO_IOCTL(DATAGRAM_RECEIVE, receive_datagram);
	हाल IOCTL_VMCI_QUEUEPAIR_ALLOC:
		VMCI_DO_IOCTL(QUEUEPAIR_ALLOC, alloc_queuepair);
	हाल IOCTL_VMCI_QUEUEPAIR_SETVA:
		VMCI_DO_IOCTL(QUEUEPAIR_SETVA, queuepair_setva);
	हाल IOCTL_VMCI_QUEUEPAIR_SETPAGEखाता:
		VMCI_DO_IOCTL(QUEUEPAIR_SETPAGEखाता, queuepair_setpf);
	हाल IOCTL_VMCI_QUEUEPAIR_DETACH:
		VMCI_DO_IOCTL(QUEUEPAIR_DETACH, qp_detach);
	हाल IOCTL_VMCI_CTX_ADD_NOTIFICATION:
		VMCI_DO_IOCTL(CTX_ADD_NOTIFICATION, ctx_add_notअगरy);
	हाल IOCTL_VMCI_CTX_REMOVE_NOTIFICATION:
		VMCI_DO_IOCTL(CTX_REMOVE_NOTIFICATION, ctx_हटाओ_notअगरy);
	हाल IOCTL_VMCI_CTX_GET_CPT_STATE:
		VMCI_DO_IOCTL(CTX_GET_CPT_STATE, ctx_get_cpt_state);
	हाल IOCTL_VMCI_CTX_SET_CPT_STATE:
		VMCI_DO_IOCTL(CTX_SET_CPT_STATE, ctx_set_cpt_state);
	हाल IOCTL_VMCI_GET_CONTEXT_ID:
		VMCI_DO_IOCTL(GET_CONTEXT_ID, get_context_id);
	हाल IOCTL_VMCI_SET_NOTIFY:
		VMCI_DO_IOCTL(SET_NOTIFY, set_notअगरy);
	हाल IOCTL_VMCI_NOTIFY_RESOURCE:
		VMCI_DO_IOCTL(NOTIFY_RESOURCE, notअगरy_resource);
	हाल IOCTL_VMCI_NOTIFICATIONS_RECEIVE:
		VMCI_DO_IOCTL(NOTIFICATIONS_RECEIVE, recv_notअगरications);

	हाल IOCTL_VMCI_VERSION:
	हाल IOCTL_VMCI_VERSION2:
		वापस vmci_host_get_version(vmci_host_dev, iocmd, uptr);

	शेष:
		pr_devel("%s: Unknown ioctl (iocmd=%d)\n", __func__, iocmd);
		वापस -EINVAL;
	पूर्ण

#अघोषित VMCI_DO_IOCTL
पूर्ण

अटल स्थिर काष्ठा file_operations vmuser_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vmci_host_खोलो,
	.release	= vmci_host_बंद,
	.poll		= vmci_host_poll,
	.unlocked_ioctl	= vmci_host_unlocked_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice vmci_host_miscdev = अणु
	 .name = "vmci",
	 .minor = MISC_DYNAMIC_MINOR,
	 .fops = &vmuser_fops,
पूर्ण;

पूर्णांक __init vmci_host_init(व्योम)
अणु
	पूर्णांक error;

	host_context = vmci_ctx_create(VMCI_HOST_CONTEXT_ID,
					VMCI_DEFAULT_PROC_PRIVILEGE_FLAGS,
					-1, VMCI_VERSION, शून्य);
	अगर (IS_ERR(host_context)) अणु
		error = PTR_ERR(host_context);
		pr_warn("Failed to initialize VMCIContext (error%d)\n",
			error);
		वापस error;
	पूर्ण

	error = misc_रेजिस्टर(&vmci_host_miscdev);
	अगर (error) अणु
		pr_warn("Module registration error (name=%s, major=%d, minor=%d, err=%d)\n",
			vmci_host_miscdev.name,
			MISC_MAJOR, vmci_host_miscdev.minor,
			error);
		pr_warn("Unable to initialize host personality\n");
		vmci_ctx_destroy(host_context);
		वापस error;
	पूर्ण

	pr_info("VMCI host device registered (name=%s, major=%d, minor=%d)\n",
		vmci_host_miscdev.name, MISC_MAJOR, vmci_host_miscdev.minor);

	vmci_host_device_initialized = true;
	वापस 0;
पूर्ण

व्योम __निकास vmci_host_निकास(व्योम)
अणु
	vmci_host_device_initialized = false;

	misc_deरेजिस्टर(&vmci_host_miscdev);
	vmci_ctx_destroy(host_context);
	vmci_qp_broker_निकास();

	pr_debug("VMCI host driver module unloaded\n");
पूर्ण
