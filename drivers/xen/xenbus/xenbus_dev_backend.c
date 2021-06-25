<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>

#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/xenbus_dev.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/events.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश "xenbus.h"

अटल पूर्णांक xenbus_backend_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस nonseekable_खोलो(inode, filp);
पूर्ण

अटल दीर्घ xenbus_alloc(करोmid_t करोmid)
अणु
	काष्ठा evtchn_alloc_unbound arg;
	पूर्णांक err = -EEXIST;

	xs_suspend();

	/* If xenstored_पढ़ोy is nonzero, that means we have alपढ़ोy talked to
	 * xenstore and set up watches. These watches will be restored by
	 * xs_resume, but that requires communication over the port established
	 * below that is not visible to anyone until the ioctl वापसs.
	 *
	 * This can be resolved by splitting the ioctl पूर्णांकo two parts
	 * (postponing the resume until xenstored is active) but this is
	 * unnecessarily complex क्रम the पूर्णांकended use where xenstored is only
	 * started once - so वापस -EEXIST अगर it's alपढ़ोy running.
	 */
	अगर (xenstored_पढ़ोy)
		जाओ out_err;

	gnttab_grant_क्रमeign_access_ref(GNTTAB_RESERVED_XENSTORE, करोmid,
			virt_to_gfn(xen_store_पूर्णांकerface), 0 /* writable */);

	arg.करोm = DOMID_SELF;
	arg.remote_करोm = करोmid;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound, &arg);
	अगर (err)
		जाओ out_err;

	अगर (xen_store_evtchn > 0)
		xb_deinit_comms();

	xen_store_evtchn = arg.port;

	xs_resume();

	वापस arg.port;

 out_err:
	xs_suspend_cancel();
	वापस err;
पूर्ण

अटल दीर्घ xenbus_backend_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ data)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल IOCTL_XENBUS_BACKEND_EVTCHN:
		अगर (xen_store_evtchn > 0)
			वापस xen_store_evtchn;
		वापस -ENODEV;
	हाल IOCTL_XENBUS_BACKEND_SETUP:
		वापस xenbus_alloc(data);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक xenbus_backend_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार size = vma->vm_end - vma->vm_start;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर ((size > PAGE_SIZE) || (vma->vm_pgoff != 0))
		वापस -EINVAL;

	अगर (remap_pfn_range(vma, vma->vm_start,
			    virt_to_pfn(xen_store_पूर्णांकerface),
			    size, vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations xenbus_backend_fops = अणु
	.खोलो = xenbus_backend_खोलो,
	.mmap = xenbus_backend_mmap,
	.unlocked_ioctl = xenbus_backend_ioctl,
पूर्ण;

अटल काष्ठा miscdevice xenbus_backend_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "xen/xenbus_backend",
	.fops = &xenbus_backend_fops,
पूर्ण;

अटल पूर्णांक __init xenbus_backend_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	err = misc_रेजिस्टर(&xenbus_backend_dev);
	अगर (err)
		pr_err("Could not register xenbus backend device\n");
	वापस err;
पूर्ण
device_initcall(xenbus_backend_init);
