<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*****************************************************************************/

/*
 *      devio.c  --  User space communication with USB devices.
 *
 *      Copyright (C) 1999-2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  This file implements the usbfs/x/y files, where
 *  x is the bus number and y the device number.
 *
 *  It allows user space programs/"drivers" to communicate directly
 *  with USB devices without पूर्णांकervening kernel driver.
 *
 *  Revision history
 *    22.12.1999   0.1   Initial release (split from proc_usb.c)
 *    04.01.2000   0.2   Turned पूर्णांकo its own fileप्रणाली
 *    30.09.2005   0.3   Fix user-triggerable oops in async URB delivery
 *    			 (CAN-2005-3055)
 */

/*****************************************************************************/

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/poll.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>
#समावेश <linux/usbdevice_fs.h>
#समावेश <linux/usb/hcd.h>	/* क्रम usbcore पूर्णांकernals */
#समावेश <linux/cdev.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/security.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/moduleparam.h>

#समावेश "usb.h"

#अगर_घोषित CONFIG_PM
#घोषणा MAYBE_CAP_SUSPEND	USBDEVFS_CAP_SUSPEND
#अन्यथा
#घोषणा MAYBE_CAP_SUSPEND	0
#पूर्ण_अगर

#घोषणा USB_MAXBUS			64
#घोषणा USB_DEVICE_MAX			(USB_MAXBUS * 128)
#घोषणा USB_SG_SIZE			16384 /* split-size क्रम large txs */

/* Mutual exclusion क्रम ps->list in resume vs. release and हटाओ */
अटल DEFINE_MUTEX(usbfs_mutex);

काष्ठा usb_dev_state अणु
	काष्ठा list_head list;      /* state list */
	काष्ठा usb_device *dev;
	काष्ठा file *file;
	spinlock_t lock;            /* protects the async urb lists */
	काष्ठा list_head async_pending;
	काष्ठा list_head async_completed;
	काष्ठा list_head memory_list;
	रुको_queue_head_t रुको;     /* wake up अगर a request completed */
	रुको_queue_head_t रुको_क्रम_resume;   /* wake up upon runसमय resume */
	अचिन्हित पूर्णांक discsignr;
	काष्ठा pid *disc_pid;
	स्थिर काष्ठा cred *cred;
	sigval_t disccontext;
	अचिन्हित दीर्घ अगरclaimed;
	u32 disabled_bulk_eps;
	अचिन्हित दीर्घ पूर्णांकerface_allowed_mask;
	पूर्णांक not_yet_resumed;
	bool suspend_allowed;
	bool privileges_dropped;
पूर्ण;

काष्ठा usb_memory अणु
	काष्ठा list_head memlist;
	पूर्णांक vma_use_count;
	पूर्णांक urb_use_count;
	u32 size;
	व्योम *mem;
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ vm_start;
	काष्ठा usb_dev_state *ps;
पूर्ण;

काष्ठा async अणु
	काष्ठा list_head asynclist;
	काष्ठा usb_dev_state *ps;
	काष्ठा pid *pid;
	स्थिर काष्ठा cred *cred;
	अचिन्हित पूर्णांक signr;
	अचिन्हित पूर्णांक अगरnum;
	व्योम __user *userbuffer;
	व्योम __user *userurb;
	sigval_t userurb_sigval;
	काष्ठा urb *urb;
	काष्ठा usb_memory *usbm;
	अचिन्हित पूर्णांक mem_usage;
	पूर्णांक status;
	u8 bulk_addr;
	u8 bulk_status;
पूर्ण;

अटल bool usbfs_snoop;
module_param(usbfs_snoop, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(usbfs_snoop, "true to log all usbfs traffic");

अटल अचिन्हित usbfs_snoop_max = 65536;
module_param(usbfs_snoop_max, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(usbfs_snoop_max,
		"maximum number of bytes to print while snooping");

#घोषणा snoop(dev, क्रमmat, arg...)				\
	करो अणु							\
		अगर (usbfs_snoop)				\
			dev_info(dev, क्रमmat, ## arg);		\
	पूर्ण जबतक (0)

क्रमागत snoop_when अणु
	SUBMIT, COMPLETE
पूर्ण;

#घोषणा USB_DEVICE_DEV		MKDEV(USB_DEVICE_MAJOR, 0)

/* Limit on the total amount of memory we can allocate क्रम transfers */
अटल u32 usbfs_memory_mb = 16;
module_param(usbfs_memory_mb, uपूर्णांक, 0644);
MODULE_PARM_DESC(usbfs_memory_mb,
		"maximum MB allowed for usbfs buffers (0 = no limit)");

/* Hard limit, necessary to aव्योम arithmetic overflow */
#घोषणा USBFS_XFER_MAX         (अच_पूर्णांक_उच्च / 2 - 1000000)

अटल atomic64_t usbfs_memory_usage;	/* Total memory currently allocated */

/* Check whether it's okay to allocate more memory क्रम a transfer */
अटल पूर्णांक usbfs_increase_memory_usage(u64 amount)
अणु
	u64 lim;

	lim = READ_ONCE(usbfs_memory_mb);
	lim <<= 20;

	atomic64_add(amount, &usbfs_memory_usage);

	अगर (lim > 0 && atomic64_पढ़ो(&usbfs_memory_usage) > lim) अणु
		atomic64_sub(amount, &usbfs_memory_usage);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Memory क्रम a transfer is being deallocated */
अटल व्योम usbfs_decrease_memory_usage(u64 amount)
अणु
	atomic64_sub(amount, &usbfs_memory_usage);
पूर्ण

अटल पूर्णांक connected(काष्ठा usb_dev_state *ps)
अणु
	वापस (!list_empty(&ps->list) &&
			ps->dev->state != USB_STATE_NOTATTACHED);
पूर्ण

अटल व्योम dec_usb_memory_use_count(काष्ठा usb_memory *usbm, पूर्णांक *count)
अणु
	काष्ठा usb_dev_state *ps = usbm->ps;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->lock, flags);
	--*count;
	अगर (usbm->urb_use_count == 0 && usbm->vma_use_count == 0) अणु
		list_del(&usbm->memlist);
		spin_unlock_irqrestore(&ps->lock, flags);

		usb_मुक्त_coherent(ps->dev, usbm->size, usbm->mem,
				usbm->dma_handle);
		usbfs_decrease_memory_usage(
			usbm->size + माप(काष्ठा usb_memory));
		kमुक्त(usbm);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ps->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम usbdev_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा usb_memory *usbm = vma->vm_निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usbm->ps->lock, flags);
	++usbm->vma_use_count;
	spin_unlock_irqrestore(&usbm->ps->lock, flags);
पूर्ण

अटल व्योम usbdev_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा usb_memory *usbm = vma->vm_निजी_data;

	dec_usb_memory_use_count(usbm, &usbm->vma_use_count);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा usbdev_vm_ops = अणु
	.खोलो = usbdev_vm_खोलो,
	.बंद = usbdev_vm_बंद
पूर्ण;

अटल पूर्णांक usbdev_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा usb_memory *usbm = शून्य;
	काष्ठा usb_dev_state *ps = file->निजी_data;
	काष्ठा usb_hcd *hcd = bus_to_hcd(ps->dev->bus);
	माप_प्रकार size = vma->vm_end - vma->vm_start;
	व्योम *mem;
	अचिन्हित दीर्घ flags;
	dma_addr_t dma_handle;
	पूर्णांक ret;

	ret = usbfs_increase_memory_usage(size + माप(काष्ठा usb_memory));
	अगर (ret)
		जाओ error;

	usbm = kzalloc(माप(काष्ठा usb_memory), GFP_KERNEL);
	अगर (!usbm) अणु
		ret = -ENOMEM;
		जाओ error_decrease_mem;
	पूर्ण

	mem = usb_alloc_coherent(ps->dev, size, GFP_USER | __GFP_NOWARN,
			&dma_handle);
	अगर (!mem) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_usbm;
	पूर्ण

	स_रखो(mem, 0, size);

	usbm->mem = mem;
	usbm->dma_handle = dma_handle;
	usbm->size = size;
	usbm->ps = ps;
	usbm->vm_start = vma->vm_start;
	usbm->vma_use_count = 1;
	INIT_LIST_HEAD(&usbm->memlist);

	अगर (hcd->localmem_pool || !hcd_uses_dma(hcd)) अणु
		अगर (remap_pfn_range(vma, vma->vm_start,
				    virt_to_phys(usbm->mem) >> PAGE_SHIFT,
				    size, vma->vm_page_prot) < 0) अणु
			dec_usb_memory_use_count(usbm, &usbm->vma_use_count);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dma_mmap_coherent(hcd->self.sysdev, vma, mem, dma_handle,
				      size)) अणु
			dec_usb_memory_use_count(usbm, &usbm->vma_use_count);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	vma->vm_flags |= VM_IO;
	vma->vm_flags |= (VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &usbdev_vm_ops;
	vma->vm_निजी_data = usbm;

	spin_lock_irqsave(&ps->lock, flags);
	list_add_tail(&usbm->memlist, &ps->memory_list);
	spin_unlock_irqrestore(&ps->lock, flags);

	वापस 0;

error_मुक्त_usbm:
	kमुक्त(usbm);
error_decrease_mem:
	usbfs_decrease_memory_usage(size + माप(काष्ठा usb_memory));
error:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार usbdev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes,
			   loff_t *ppos)
अणु
	काष्ठा usb_dev_state *ps = file->निजी_data;
	काष्ठा usb_device *dev = ps->dev;
	sमाप_प्रकार ret = 0;
	अचिन्हित len;
	loff_t pos;
	पूर्णांक i;

	pos = *ppos;
	usb_lock_device(dev);
	अगर (!connected(ps)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण अन्यथा अगर (pos < 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (pos < माप(काष्ठा usb_device_descriptor)) अणु
		/* 18 bytes - fits on the stack */
		काष्ठा usb_device_descriptor temp_desc;

		स_नकल(&temp_desc, &dev->descriptor, माप(dev->descriptor));
		le16_to_cpus(&temp_desc.bcdUSB);
		le16_to_cpus(&temp_desc.idVenकरोr);
		le16_to_cpus(&temp_desc.idProduct);
		le16_to_cpus(&temp_desc.bcdDevice);

		len = माप(काष्ठा usb_device_descriptor) - pos;
		अगर (len > nbytes)
			len = nbytes;
		अगर (copy_to_user(buf, ((अक्षर *)&temp_desc) + pos, len)) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		*ppos += len;
		buf += len;
		nbytes -= len;
		ret += len;
	पूर्ण

	pos = माप(काष्ठा usb_device_descriptor);
	क्रम (i = 0; nbytes && i < dev->descriptor.bNumConfigurations; i++) अणु
		काष्ठा usb_config_descriptor *config =
			(काष्ठा usb_config_descriptor *)dev->rawdescriptors[i];
		अचिन्हित पूर्णांक length = le16_to_cpu(config->wTotalLength);

		अगर (*ppos < pos + length) अणु

			/* The descriptor may claim to be दीर्घer than it
			 * really is.  Here is the actual allocated length. */
			अचिन्हित alloclen =
				le16_to_cpu(dev->config[i].desc.wTotalLength);

			len = length - (*ppos - pos);
			अगर (len > nbytes)
				len = nbytes;

			/* Simply करोn't ग_लिखो (skip over) unallocated parts */
			अगर (alloclen > (*ppos - pos)) अणु
				alloclen -= (*ppos - pos);
				अगर (copy_to_user(buf,
				    dev->rawdescriptors[i] + (*ppos - pos),
				    min(len, alloclen))) अणु
					ret = -EFAULT;
					जाओ err;
				पूर्ण
			पूर्ण

			*ppos += len;
			buf += len;
			nbytes -= len;
			ret += len;
		पूर्ण

		pos += length;
	पूर्ण

err:
	usb_unlock_device(dev);
	वापस ret;
पूर्ण

/*
 * async list handling
 */

अटल काष्ठा async *alloc_async(अचिन्हित पूर्णांक numisoframes)
अणु
	काष्ठा async *as;

	as = kzalloc(माप(काष्ठा async), GFP_KERNEL);
	अगर (!as)
		वापस शून्य;
	as->urb = usb_alloc_urb(numisoframes, GFP_KERNEL);
	अगर (!as->urb) अणु
		kमुक्त(as);
		वापस शून्य;
	पूर्ण
	वापस as;
पूर्ण

अटल व्योम मुक्त_async(काष्ठा async *as)
अणु
	पूर्णांक i;

	put_pid(as->pid);
	अगर (as->cred)
		put_cred(as->cred);
	क्रम (i = 0; i < as->urb->num_sgs; i++) अणु
		अगर (sg_page(&as->urb->sg[i]))
			kमुक्त(sg_virt(&as->urb->sg[i]));
	पूर्ण

	kमुक्त(as->urb->sg);
	अगर (as->usbm == शून्य)
		kमुक्त(as->urb->transfer_buffer);
	अन्यथा
		dec_usb_memory_use_count(as->usbm, &as->usbm->urb_use_count);

	kमुक्त(as->urb->setup_packet);
	usb_मुक्त_urb(as->urb);
	usbfs_decrease_memory_usage(as->mem_usage);
	kमुक्त(as);
पूर्ण

अटल व्योम async_newpending(काष्ठा async *as)
अणु
	काष्ठा usb_dev_state *ps = as->ps;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->lock, flags);
	list_add_tail(&as->asynclist, &ps->async_pending);
	spin_unlock_irqrestore(&ps->lock, flags);
पूर्ण

अटल व्योम async_हटाओpending(काष्ठा async *as)
अणु
	काष्ठा usb_dev_state *ps = as->ps;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->lock, flags);
	list_del_init(&as->asynclist);
	spin_unlock_irqrestore(&ps->lock, flags);
पूर्ण

अटल काष्ठा async *async_अ_लोompleted(काष्ठा usb_dev_state *ps)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा async *as = शून्य;

	spin_lock_irqsave(&ps->lock, flags);
	अगर (!list_empty(&ps->async_completed)) अणु
		as = list_entry(ps->async_completed.next, काष्ठा async,
				asynclist);
		list_del_init(&as->asynclist);
	पूर्ण
	spin_unlock_irqrestore(&ps->lock, flags);
	वापस as;
पूर्ण

अटल काष्ठा async *async_getpending(काष्ठा usb_dev_state *ps,
					     व्योम __user *userurb)
अणु
	काष्ठा async *as;

	list_क्रम_each_entry(as, &ps->async_pending, asynclist)
		अगर (as->userurb == userurb) अणु
			list_del_init(&as->asynclist);
			वापस as;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम snoop_urb(काष्ठा usb_device *udev,
		व्योम __user *userurb, पूर्णांक pipe, अचिन्हित length,
		पूर्णांक समयout_or_status, क्रमागत snoop_when when,
		अचिन्हित अक्षर *data, अचिन्हित data_len)
अणु
	अटल स्थिर अक्षर *types[] = अणु"isoc", "int", "ctrl", "bulk"पूर्ण;
	अटल स्थिर अक्षर *dirs[] = अणु"out", "in"पूर्ण;
	पूर्णांक ep;
	स्थिर अक्षर *t, *d;

	अगर (!usbfs_snoop)
		वापस;

	ep = usb_pipeendpoपूर्णांक(pipe);
	t = types[usb_pipetype(pipe)];
	d = dirs[!!usb_pipein(pipe)];

	अगर (userurb) अणु		/* Async */
		अगर (when == SUBMIT)
			dev_info(&udev->dev, "userurb %px, ep%d %s-%s, "
					"length %u\n",
					userurb, ep, t, d, length);
		अन्यथा
			dev_info(&udev->dev, "userurb %px, ep%d %s-%s, "
					"actual_length %u status %d\n",
					userurb, ep, t, d, length,
					समयout_or_status);
	पूर्ण अन्यथा अणु
		अगर (when == SUBMIT)
			dev_info(&udev->dev, "ep%d %s-%s, length %u, "
					"timeout %d\n",
					ep, t, d, length, समयout_or_status);
		अन्यथा
			dev_info(&udev->dev, "ep%d %s-%s, actual_length %u, "
					"status %d\n",
					ep, t, d, length, समयout_or_status);
	पूर्ण

	data_len = min(data_len, usbfs_snoop_max);
	अगर (data && data_len > 0) अणु
		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE, 32, 1,
			data, data_len, 1);
	पूर्ण
पूर्ण

अटल व्योम snoop_urb_data(काष्ठा urb *urb, अचिन्हित len)
अणु
	पूर्णांक i, size;

	len = min(len, usbfs_snoop_max);
	अगर (!usbfs_snoop || len == 0)
		वापस;

	अगर (urb->num_sgs == 0) अणु
		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE, 32, 1,
			urb->transfer_buffer, len, 1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < urb->num_sgs && len; i++) अणु
		size = (len > USB_SG_SIZE) ? USB_SG_SIZE : len;
		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE, 32, 1,
			sg_virt(&urb->sg[i]), size, 1);
		len -= size;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_urb_data_to_user(u8 __user *userbuffer, काष्ठा urb *urb)
अणु
	अचिन्हित i, len, size;

	अगर (urb->number_of_packets > 0)		/* Isochronous */
		len = urb->transfer_buffer_length;
	अन्यथा					/* Non-Isoc */
		len = urb->actual_length;

	अगर (urb->num_sgs == 0) अणु
		अगर (copy_to_user(userbuffer, urb->transfer_buffer, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < urb->num_sgs && len; i++) अणु
		size = (len > USB_SG_SIZE) ? USB_SG_SIZE : len;
		अगर (copy_to_user(userbuffer, sg_virt(&urb->sg[i]), size))
			वापस -EFAULT;
		userbuffer += size;
		len -= size;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AS_CONTINUATION	1
#घोषणा AS_UNLINK	2

अटल व्योम cancel_bulk_urbs(काष्ठा usb_dev_state *ps, अचिन्हित bulk_addr)
__releases(ps->lock)
__acquires(ps->lock)
अणु
	काष्ठा urb *urb;
	काष्ठा async *as;

	/* Mark all the pending URBs that match bulk_addr, up to but not
	 * including the first one without AS_CONTINUATION.  If such an
	 * URB is encountered then a new transfer has alपढ़ोy started so
	 * the endpoपूर्णांक करोesn't need to be disabled; otherwise it करोes.
	 */
	list_क्रम_each_entry(as, &ps->async_pending, asynclist) अणु
		अगर (as->bulk_addr == bulk_addr) अणु
			अगर (as->bulk_status != AS_CONTINUATION)
				जाओ rescan;
			as->bulk_status = AS_UNLINK;
			as->bulk_addr = 0;
		पूर्ण
	पूर्ण
	ps->disabled_bulk_eps |= (1 << bulk_addr);

	/* Now carefully unlink all the marked pending URBs */
 rescan:
	list_क्रम_each_entry_reverse(as, &ps->async_pending, asynclist) अणु
		अगर (as->bulk_status == AS_UNLINK) अणु
			as->bulk_status = 0;		/* Only once */
			urb = as->urb;
			usb_get_urb(urb);
			spin_unlock(&ps->lock);		/* Allow completions */
			usb_unlink_urb(urb);
			usb_put_urb(urb);
			spin_lock(&ps->lock);
			जाओ rescan;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम async_completed(काष्ठा urb *urb)
अणु
	काष्ठा async *as = urb->context;
	काष्ठा usb_dev_state *ps = as->ps;
	काष्ठा pid *pid = शून्य;
	स्थिर काष्ठा cred *cred = शून्य;
	अचिन्हित दीर्घ flags;
	sigval_t addr;
	पूर्णांक signr, त्रुटि_सं;

	spin_lock_irqsave(&ps->lock, flags);
	list_move_tail(&as->asynclist, &ps->async_completed);
	as->status = urb->status;
	signr = as->signr;
	अगर (signr) अणु
		त्रुटि_सं = as->status;
		addr = as->userurb_sigval;
		pid = get_pid(as->pid);
		cred = get_cred(as->cred);
	पूर्ण
	snoop(&urb->dev->dev, "urb complete\n");
	snoop_urb(urb->dev, as->userurb, urb->pipe, urb->actual_length,
			as->status, COMPLETE, शून्य, 0);
	अगर (usb_urb_dir_in(urb))
		snoop_urb_data(urb, urb->actual_length);

	अगर (as->status < 0 && as->bulk_addr && as->status != -ECONNRESET &&
			as->status != -ENOENT)
		cancel_bulk_urbs(ps, as->bulk_addr);

	wake_up(&ps->रुको);
	spin_unlock_irqrestore(&ps->lock, flags);

	अगर (signr) अणु
		समाप्त_pid_usb_asyncio(signr, त्रुटि_सं, addr, pid, cred);
		put_pid(pid);
		put_cred(cred);
	पूर्ण
पूर्ण

अटल व्योम destroy_async(काष्ठा usb_dev_state *ps, काष्ठा list_head *list)
अणु
	काष्ठा urb *urb;
	काष्ठा async *as;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->lock, flags);
	जबतक (!list_empty(list)) अणु
		as = list_last_entry(list, काष्ठा async, asynclist);
		list_del_init(&as->asynclist);
		urb = as->urb;
		usb_get_urb(urb);

		/* drop the spinlock so the completion handler can run */
		spin_unlock_irqrestore(&ps->lock, flags);
		usb_समाप्त_urb(urb);
		usb_put_urb(urb);
		spin_lock_irqsave(&ps->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ps->lock, flags);
पूर्ण

अटल व्योम destroy_async_on_पूर्णांकerface(काष्ठा usb_dev_state *ps,
				       अचिन्हित पूर्णांक अगरnum)
अणु
	काष्ठा list_head *p, *q, hitlist;
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&hitlist);
	spin_lock_irqsave(&ps->lock, flags);
	list_क्रम_each_safe(p, q, &ps->async_pending)
		अगर (अगरnum == list_entry(p, काष्ठा async, asynclist)->अगरnum)
			list_move_tail(p, &hitlist);
	spin_unlock_irqrestore(&ps->lock, flags);
	destroy_async(ps, &hitlist);
पूर्ण

अटल व्योम destroy_all_async(काष्ठा usb_dev_state *ps)
अणु
	destroy_async(ps, &ps->async_pending);
पूर्ण

/*
 * पूर्णांकerface claims are made only at the request of user level code,
 * which can also release them (explicitly or by closing files).
 * they're also unकरोne when devices disconnect.
 */

अटल पूर्णांक driver_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम driver_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_dev_state *ps = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित पूर्णांक अगरnum = पूर्णांकf->altsetting->desc.bInterfaceNumber;

	अगर (!ps)
		वापस;

	/* NOTE:  this relies on usbcore having canceled and completed
	 * all pending I/O requests; 2.6 करोes that.
	 */

	अगर (likely(अगरnum < 8*माप(ps->अगरclaimed)))
		clear_bit(अगरnum, &ps->अगरclaimed);
	अन्यथा
		dev_warn(&पूर्णांकf->dev, "interface number %u out of range\n",
			 अगरnum);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	/* क्रमce async requests to complete */
	destroy_async_on_पूर्णांकerface(ps, अगरnum);
पूर्ण

/* We करोn't care about suspend/resume of claimed पूर्णांकerfaces */
अटल पूर्णांक driver_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक driver_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

/* The following routines apply to the entire device, not पूर्णांकerfaces */
व्योम usbfs_notअगरy_suspend(काष्ठा usb_device *udev)
अणु
	/* We करोn't need to handle this */
पूर्ण

व्योम usbfs_notअगरy_resume(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_dev_state *ps;

	/* Protect against simultaneous हटाओ or release */
	mutex_lock(&usbfs_mutex);
	list_क्रम_each_entry(ps, &udev->filelist, list) अणु
		WRITE_ONCE(ps->not_yet_resumed, 0);
		wake_up_all(&ps->रुको_क्रम_resume);
	पूर्ण
	mutex_unlock(&usbfs_mutex);
पूर्ण

काष्ठा usb_driver usbfs_driver = अणु
	.name =		"usbfs",
	.probe =	driver_probe,
	.disconnect =	driver_disconnect,
	.suspend =	driver_suspend,
	.resume =	driver_resume,
	.supports_स्वतःsuspend = 1,
पूर्ण;

अटल पूर्णांक claimपूर्णांकf(काष्ठा usb_dev_state *ps, अचिन्हित पूर्णांक अगरnum)
अणु
	काष्ठा usb_device *dev = ps->dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक err;

	अगर (अगरnum >= 8*माप(ps->अगरclaimed))
		वापस -EINVAL;
	/* alपढ़ोy claimed */
	अगर (test_bit(अगरnum, &ps->अगरclaimed))
		वापस 0;

	अगर (ps->privileges_dropped &&
			!test_bit(अगरnum, &ps->पूर्णांकerface_allowed_mask))
		वापस -EACCES;

	पूर्णांकf = usb_अगरnum_to_अगर(dev, अगरnum);
	अगर (!पूर्णांकf)
		err = -ENOENT;
	अन्यथा अणु
		अचिन्हित पूर्णांक old_suppress;

		/* suppress uevents जबतक claiming पूर्णांकerface */
		old_suppress = dev_get_uevent_suppress(&पूर्णांकf->dev);
		dev_set_uevent_suppress(&पूर्णांकf->dev, 1);
		err = usb_driver_claim_पूर्णांकerface(&usbfs_driver, पूर्णांकf, ps);
		dev_set_uevent_suppress(&पूर्णांकf->dev, old_suppress);
	पूर्ण
	अगर (err == 0)
		set_bit(अगरnum, &ps->अगरclaimed);
	वापस err;
पूर्ण

अटल पूर्णांक releaseपूर्णांकf(काष्ठा usb_dev_state *ps, अचिन्हित पूर्णांक अगरnum)
अणु
	काष्ठा usb_device *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक err;

	err = -EINVAL;
	अगर (अगरnum >= 8*माप(ps->अगरclaimed))
		वापस err;
	dev = ps->dev;
	पूर्णांकf = usb_अगरnum_to_अगर(dev, अगरnum);
	अगर (!पूर्णांकf)
		err = -ENOENT;
	अन्यथा अगर (test_and_clear_bit(अगरnum, &ps->अगरclaimed)) अणु
		अचिन्हित पूर्णांक old_suppress;

		/* suppress uevents जबतक releasing पूर्णांकerface */
		old_suppress = dev_get_uevent_suppress(&पूर्णांकf->dev);
		dev_set_uevent_suppress(&पूर्णांकf->dev, 1);
		usb_driver_release_पूर्णांकerface(&usbfs_driver, पूर्णांकf);
		dev_set_uevent_suppress(&पूर्णांकf->dev, old_suppress);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक checkपूर्णांकf(काष्ठा usb_dev_state *ps, अचिन्हित पूर्णांक अगरnum)
अणु
	अगर (ps->dev->state != USB_STATE_CONFIGURED)
		वापस -EHOSTUNREACH;
	अगर (अगरnum >= 8*माप(ps->अगरclaimed))
		वापस -EINVAL;
	अगर (test_bit(अगरnum, &ps->अगरclaimed))
		वापस 0;
	/* अगर not yet claimed, claim it क्रम the driver */
	dev_warn(&ps->dev->dev, "usbfs: process %d (%s) did not claim "
		 "interface %u before use\n", task_pid_nr(current),
		 current->comm, अगरnum);
	वापस claimपूर्णांकf(ps, अगरnum);
पूर्ण

अटल पूर्णांक findपूर्णांकfep(काष्ठा usb_device *dev, अचिन्हित पूर्णांक ep)
अणु
	अचिन्हित पूर्णांक i, j, e;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpt;

	अगर (ep & ~(USB_सूची_IN|0xf))
		वापस -EINVAL;
	अगर (!dev->actconfig)
		वापस -ESRCH;
	क्रम (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) अणु
		पूर्णांकf = dev->actconfig->पूर्णांकerface[i];
		क्रम (j = 0; j < पूर्णांकf->num_altsetting; j++) अणु
			alts = &पूर्णांकf->altsetting[j];
			क्रम (e = 0; e < alts->desc.bNumEndpoपूर्णांकs; e++) अणु
				endpt = &alts->endpoपूर्णांक[e].desc;
				अगर (endpt->bEndpoपूर्णांकAddress == ep)
					वापस alts->desc.bInterfaceNumber;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक check_ctrlrecip(काष्ठा usb_dev_state *ps, अचिन्हित पूर्णांक requesttype,
			   अचिन्हित पूर्णांक request, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक ret = 0;
	काष्ठा usb_host_पूर्णांकerface *alt_setting;

	अगर (ps->dev->state != USB_STATE_UNAUTHENTICATED
	 && ps->dev->state != USB_STATE_ADDRESS
	 && ps->dev->state != USB_STATE_CONFIGURED)
		वापस -EHOSTUNREACH;
	अगर (USB_TYPE_VENDOR == (USB_TYPE_MASK & requesttype))
		वापस 0;

	/*
	 * check क्रम the special corner हाल 'get_device_id' in the prपूर्णांकer
	 * class specअगरication, which we always want to allow as it is used
	 * to query things like ink level, etc.
	 */
	अगर (requesttype == 0xa1 && request == 0) अणु
		alt_setting = usb_find_alt_setting(ps->dev->actconfig,
						   index >> 8, index & 0xff);
		अगर (alt_setting
		 && alt_setting->desc.bInterfaceClass == USB_CLASS_PRINTER)
			वापस 0;
	पूर्ण

	index &= 0xff;
	चयन (requesttype & USB_RECIP_MASK) अणु
	हाल USB_RECIP_ENDPOINT:
		अगर ((index & ~USB_सूची_IN) == 0)
			वापस 0;
		ret = findपूर्णांकfep(ps->dev, index);
		अगर (ret < 0) अणु
			/*
			 * Some not fully compliant Win apps seem to get
			 * index wrong and have the endpoपूर्णांक number here
			 * rather than the endpoपूर्णांक address (with the
			 * correct direction). Win करोes let this through,
			 * so we'll not reject it here but leave it to
			 * the device to not अवरोध KVM. But we warn.
			 */
			ret = findपूर्णांकfep(ps->dev, index ^ 0x80);
			अगर (ret >= 0)
				dev_info(&ps->dev->dev,
					"%s: process %i (%s) requesting ep %02x but needs %02x\n",
					__func__, task_pid_nr(current),
					current->comm, index, index ^ 0x80);
		पूर्ण
		अगर (ret >= 0)
			ret = checkपूर्णांकf(ps, ret);
		अवरोध;

	हाल USB_RECIP_INTERFACE:
		ret = checkपूर्णांकf(ps, index);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा usb_host_endpoपूर्णांक *ep_to_host_endpoपूर्णांक(काष्ठा usb_device *dev,
						     अचिन्हित अक्षर ep)
अणु
	अगर (ep & USB_ENDPOINT_सूची_MASK)
		वापस dev->ep_in[ep & USB_ENDPOINT_NUMBER_MASK];
	अन्यथा
		वापस dev->ep_out[ep & USB_ENDPOINT_NUMBER_MASK];
पूर्ण

अटल पूर्णांक parse_usbdevfs_streams(काष्ठा usb_dev_state *ps,
				  काष्ठा usbdevfs_streams __user *streams,
				  अचिन्हित पूर्णांक *num_streams_ret,
				  अचिन्हित पूर्णांक *num_eps_ret,
				  काष्ठा usb_host_endpoपूर्णांक ***eps_ret,
				  काष्ठा usb_पूर्णांकerface **पूर्णांकf_ret)
अणु
	अचिन्हित पूर्णांक i, num_streams, num_eps;
	काष्ठा usb_host_endpoपूर्णांक **eps;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = शून्य;
	अचिन्हित अक्षर ep;
	पूर्णांक अगरnum, ret;

	अगर (get_user(num_streams, &streams->num_streams) ||
	    get_user(num_eps, &streams->num_eps))
		वापस -EFAULT;

	अगर (num_eps < 1 || num_eps > USB_MAXENDPOINTS)
		वापस -EINVAL;

	/* The XHCI controller allows max 2 ^ 16 streams */
	अगर (num_streams_ret && (num_streams < 2 || num_streams > 65536))
		वापस -EINVAL;

	eps = kदो_स्मृति_array(num_eps, माप(*eps), GFP_KERNEL);
	अगर (!eps)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_eps; i++) अणु
		अगर (get_user(ep, &streams->eps[i])) अणु
			ret = -EFAULT;
			जाओ error;
		पूर्ण
		eps[i] = ep_to_host_endpoपूर्णांक(ps->dev, ep);
		अगर (!eps[i]) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		/* usb_alloc/मुक्त_streams operate on an usb_पूर्णांकerface */
		अगरnum = findपूर्णांकfep(ps->dev, ep);
		अगर (अगरnum < 0) अणु
			ret = अगरnum;
			जाओ error;
		पूर्ण

		अगर (i == 0) अणु
			ret = checkपूर्णांकf(ps, अगरnum);
			अगर (ret < 0)
				जाओ error;
			पूर्णांकf = usb_अगरnum_to_अगर(ps->dev, अगरnum);
		पूर्ण अन्यथा अणु
			/* Verअगरy all eps beदीर्घ to the same पूर्णांकerface */
			अगर (अगरnum != पूर्णांकf->altsetting->desc.bInterfaceNumber) अणु
				ret = -EINVAL;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (num_streams_ret)
		*num_streams_ret = num_streams;
	*num_eps_ret = num_eps;
	*eps_ret = eps;
	*पूर्णांकf_ret = पूर्णांकf;

	वापस 0;

error:
	kमुक्त(eps);
	वापस ret;
पूर्ण

अटल काष्ठा usb_device *usbdev_lookup_by_devt(dev_t devt)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_devt(&usb_bus_type, devt);
	अगर (!dev)
		वापस शून्य;
	वापस to_usb_device(dev);
पूर्ण

/*
 * file operations
 */
अटल पूर्णांक usbdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_device *dev = शून्य;
	काष्ठा usb_dev_state *ps;
	पूर्णांक ret;

	ret = -ENOMEM;
	ps = kzalloc(माप(काष्ठा usb_dev_state), GFP_KERNEL);
	अगर (!ps)
		जाओ out_मुक्त_ps;

	ret = -ENODEV;

	/* usbdev device-node */
	अगर (imajor(inode) == USB_DEVICE_MAJOR)
		dev = usbdev_lookup_by_devt(inode->i_rdev);
	अगर (!dev)
		जाओ out_मुक्त_ps;

	usb_lock_device(dev);
	अगर (dev->state == USB_STATE_NOTATTACHED)
		जाओ out_unlock_device;

	ret = usb_स्वतःresume_device(dev);
	अगर (ret)
		जाओ out_unlock_device;

	ps->dev = dev;
	ps->file = file;
	ps->पूर्णांकerface_allowed_mask = 0xFFFFFFFF; /* 32 bits */
	spin_lock_init(&ps->lock);
	INIT_LIST_HEAD(&ps->list);
	INIT_LIST_HEAD(&ps->async_pending);
	INIT_LIST_HEAD(&ps->async_completed);
	INIT_LIST_HEAD(&ps->memory_list);
	init_रुकोqueue_head(&ps->रुको);
	init_रुकोqueue_head(&ps->रुको_क्रम_resume);
	ps->disc_pid = get_pid(task_pid(current));
	ps->cred = get_current_cred();
	smp_wmb();

	/* Can't race with resume; the device is alपढ़ोy active */
	list_add_tail(&ps->list, &dev->filelist);
	file->निजी_data = ps;
	usb_unlock_device(dev);
	snoop(&dev->dev, "opened by process %d: %s\n", task_pid_nr(current),
			current->comm);
	वापस ret;

 out_unlock_device:
	usb_unlock_device(dev);
	usb_put_dev(dev);
 out_मुक्त_ps:
	kमुक्त(ps);
	वापस ret;
पूर्ण

अटल पूर्णांक usbdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_dev_state *ps = file->निजी_data;
	काष्ठा usb_device *dev = ps->dev;
	अचिन्हित पूर्णांक अगरnum;
	काष्ठा async *as;

	usb_lock_device(dev);
	usb_hub_release_all_ports(dev, ps);

	/* Protect against simultaneous resume */
	mutex_lock(&usbfs_mutex);
	list_del_init(&ps->list);
	mutex_unlock(&usbfs_mutex);

	क्रम (अगरnum = 0; ps->अगरclaimed && अगरnum < 8*माप(ps->अगरclaimed);
			अगरnum++) अणु
		अगर (test_bit(अगरnum, &ps->अगरclaimed))
			releaseपूर्णांकf(ps, अगरnum);
	पूर्ण
	destroy_all_async(ps);
	अगर (!ps->suspend_allowed)
		usb_स्वतःsuspend_device(dev);
	usb_unlock_device(dev);
	usb_put_dev(dev);
	put_pid(ps->disc_pid);
	put_cred(ps->cred);

	as = async_अ_लोompleted(ps);
	जबतक (as) अणु
		मुक्त_async(as);
		as = async_अ_लोompleted(ps);
	पूर्ण

	kमुक्त(ps);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_proc_control(काष्ठा usb_dev_state *ps,
		काष्ठा usbdevfs_ctrltransfer *ctrl)
अणु
	काष्ठा usb_device *dev = ps->dev;
	अचिन्हित पूर्णांक पंचांगo;
	अचिन्हित अक्षर *tbuf;
	अचिन्हित wLength;
	पूर्णांक i, pipe, ret;

	ret = check_ctrlrecip(ps, ctrl->bRequestType, ctrl->bRequest,
			      ctrl->wIndex);
	अगर (ret)
		वापस ret;
	wLength = ctrl->wLength;	/* To suppress 64k PAGE_SIZE warning */
	अगर (wLength > PAGE_SIZE)
		वापस -EINVAL;
	ret = usbfs_increase_memory_usage(PAGE_SIZE + माप(काष्ठा urb) +
			माप(काष्ठा usb_ctrlrequest));
	अगर (ret)
		वापस ret;
	tbuf = (अचिन्हित अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!tbuf) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	पंचांगo = ctrl->समयout;
	snoop(&dev->dev, "control urb: bRequestType=%02x "
		"bRequest=%02x wValue=%04x "
		"wIndex=%04x wLength=%04x\n",
		ctrl->bRequestType, ctrl->bRequest, ctrl->wValue,
		ctrl->wIndex, ctrl->wLength);
	अगर (ctrl->bRequestType & 0x80) अणु
		pipe = usb_rcvctrlpipe(dev, 0);
		snoop_urb(dev, शून्य, pipe, ctrl->wLength, पंचांगo, SUBMIT, शून्य, 0);

		usb_unlock_device(dev);
		i = usb_control_msg(dev, pipe, ctrl->bRequest,
				    ctrl->bRequestType, ctrl->wValue, ctrl->wIndex,
				    tbuf, ctrl->wLength, पंचांगo);
		usb_lock_device(dev);
		snoop_urb(dev, शून्य, pipe, max(i, 0), min(i, 0), COMPLETE,
			  tbuf, max(i, 0));
		अगर ((i > 0) && ctrl->wLength) अणु
			अगर (copy_to_user(ctrl->data, tbuf, i)) अणु
				ret = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ctrl->wLength) अणु
			अगर (copy_from_user(tbuf, ctrl->data, ctrl->wLength)) अणु
				ret = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
		pipe = usb_sndctrlpipe(dev, 0);
		snoop_urb(dev, शून्य, pipe, ctrl->wLength, पंचांगo, SUBMIT,
			tbuf, ctrl->wLength);

		usb_unlock_device(dev);
		i = usb_control_msg(dev, usb_sndctrlpipe(dev, 0), ctrl->bRequest,
				    ctrl->bRequestType, ctrl->wValue, ctrl->wIndex,
				    tbuf, ctrl->wLength, पंचांगo);
		usb_lock_device(dev);
		snoop_urb(dev, शून्य, pipe, max(i, 0), min(i, 0), COMPLETE, शून्य, 0);
	पूर्ण
	अगर (i < 0 && i != -EPIPE) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "usbfs: USBDEVFS_CONTROL "
			   "failed cmd %s rqt %u rq %u len %u ret %d\n",
			   current->comm, ctrl->bRequestType, ctrl->bRequest,
			   ctrl->wLength, i);
	पूर्ण
	ret = i;
 करोne:
	मुक्त_page((अचिन्हित दीर्घ) tbuf);
	usbfs_decrease_memory_usage(PAGE_SIZE + माप(काष्ठा urb) +
			माप(काष्ठा usb_ctrlrequest));
	वापस ret;
पूर्ण

अटल पूर्णांक proc_control(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_ctrltransfer ctrl;

	अगर (copy_from_user(&ctrl, arg, माप(ctrl)))
		वापस -EFAULT;
	वापस करो_proc_control(ps, &ctrl);
पूर्ण

अटल पूर्णांक करो_proc_bulk(काष्ठा usb_dev_state *ps,
		काष्ठा usbdevfs_bulktransfer *bulk)
अणु
	काष्ठा usb_device *dev = ps->dev;
	अचिन्हित पूर्णांक पंचांगo, len1, pipe;
	पूर्णांक len2;
	अचिन्हित अक्षर *tbuf;
	पूर्णांक i, ret;

	ret = findपूर्णांकfep(ps->dev, bulk->ep);
	अगर (ret < 0)
		वापस ret;
	ret = checkपूर्णांकf(ps, ret);
	अगर (ret)
		वापस ret;
	अगर (bulk->ep & USB_सूची_IN)
		pipe = usb_rcvbulkpipe(dev, bulk->ep & 0x7f);
	अन्यथा
		pipe = usb_sndbulkpipe(dev, bulk->ep & 0x7f);
	अगर (!usb_maxpacket(dev, pipe, !(bulk->ep & USB_सूची_IN)))
		वापस -EINVAL;
	len1 = bulk->len;
	अगर (len1 >= (पूर्णांक_उच्च - माप(काष्ठा urb)))
		वापस -EINVAL;
	ret = usbfs_increase_memory_usage(len1 + माप(काष्ठा urb));
	अगर (ret)
		वापस ret;

	/*
	 * len1 can be almost arbitrarily large.  Don't WARN if it's
	 * too big, just fail the request.
	 */
	tbuf = kदो_स्मृति(len1, GFP_KERNEL | __GFP_NOWARN);
	अगर (!tbuf) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	पंचांगo = bulk->समयout;
	अगर (bulk->ep & 0x80) अणु
		snoop_urb(dev, शून्य, pipe, len1, पंचांगo, SUBMIT, शून्य, 0);

		usb_unlock_device(dev);
		i = usb_bulk_msg(dev, pipe, tbuf, len1, &len2, पंचांगo);
		usb_lock_device(dev);
		snoop_urb(dev, शून्य, pipe, len2, i, COMPLETE, tbuf, len2);

		अगर (!i && len2) अणु
			अगर (copy_to_user(bulk->data, tbuf, len2)) अणु
				ret = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (len1) अणु
			अगर (copy_from_user(tbuf, bulk->data, len1)) अणु
				ret = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
		snoop_urb(dev, शून्य, pipe, len1, पंचांगo, SUBMIT, tbuf, len1);

		usb_unlock_device(dev);
		i = usb_bulk_msg(dev, pipe, tbuf, len1, &len2, पंचांगo);
		usb_lock_device(dev);
		snoop_urb(dev, शून्य, pipe, len2, i, COMPLETE, शून्य, 0);
	पूर्ण
	ret = (i < 0 ? i : len2);
 करोne:
	kमुक्त(tbuf);
	usbfs_decrease_memory_usage(len1 + माप(काष्ठा urb));
	वापस ret;
पूर्ण

अटल पूर्णांक proc_bulk(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_bulktransfer bulk;

	अगर (copy_from_user(&bulk, arg, माप(bulk)))
		वापस -EFAULT;
	वापस करो_proc_bulk(ps, &bulk);
पूर्ण

अटल व्योम check_reset_of_active_ep(काष्ठा usb_device *udev,
		अचिन्हित पूर्णांक epnum, अक्षर *ioctl_name)
अणु
	काष्ठा usb_host_endpoपूर्णांक **eps;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	eps = (epnum & USB_सूची_IN) ? udev->ep_in : udev->ep_out;
	ep = eps[epnum & 0x0f];
	अगर (ep && !list_empty(&ep->urb_list))
		dev_warn(&udev->dev, "Process %d (%s) called USBDEVFS_%s for active endpoint 0x%02x\n",
				task_pid_nr(current), current->comm,
				ioctl_name, epnum);
पूर्ण

अटल पूर्णांक proc_resetep(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित पूर्णांक ep;
	पूर्णांक ret;

	अगर (get_user(ep, (अचिन्हित पूर्णांक __user *)arg))
		वापस -EFAULT;
	ret = findपूर्णांकfep(ps->dev, ep);
	अगर (ret < 0)
		वापस ret;
	ret = checkपूर्णांकf(ps, ret);
	अगर (ret)
		वापस ret;
	check_reset_of_active_ep(ps->dev, ep, "RESETEP");
	usb_reset_endpoपूर्णांक(ps->dev, ep);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_clearhalt(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित पूर्णांक ep;
	पूर्णांक pipe;
	पूर्णांक ret;

	अगर (get_user(ep, (अचिन्हित पूर्णांक __user *)arg))
		वापस -EFAULT;
	ret = findपूर्णांकfep(ps->dev, ep);
	अगर (ret < 0)
		वापस ret;
	ret = checkपूर्णांकf(ps, ret);
	अगर (ret)
		वापस ret;
	check_reset_of_active_ep(ps->dev, ep, "CLEAR_HALT");
	अगर (ep & USB_सूची_IN)
		pipe = usb_rcvbulkpipe(ps->dev, ep & 0x7f);
	अन्यथा
		pipe = usb_sndbulkpipe(ps->dev, ep & 0x7f);

	वापस usb_clear_halt(ps->dev, pipe);
पूर्ण

अटल पूर्णांक proc_getdriver(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_getdriver gd;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक ret;

	अगर (copy_from_user(&gd, arg, माप(gd)))
		वापस -EFAULT;
	पूर्णांकf = usb_अगरnum_to_अगर(ps->dev, gd.पूर्णांकerface);
	अगर (!पूर्णांकf || !पूर्णांकf->dev.driver)
		ret = -ENODATA;
	अन्यथा अणु
		strlcpy(gd.driver, पूर्णांकf->dev.driver->name,
				माप(gd.driver));
		ret = (copy_to_user(arg, &gd, माप(gd)) ? -EFAULT : 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक proc_connectinfo(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_connectinfo ci;

	स_रखो(&ci, 0, माप(ci));
	ci.devnum = ps->dev->devnum;
	ci.slow = ps->dev->speed == USB_SPEED_LOW;

	अगर (copy_to_user(arg, &ci, माप(ci)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक proc_conninfo_ex(काष्ठा usb_dev_state *ps,
			    व्योम __user *arg, माप_प्रकार size)
अणु
	काष्ठा usbdevfs_conninfo_ex ci;
	काष्ठा usb_device *udev = ps->dev;

	अगर (size < माप(ci.size))
		वापस -EINVAL;

	स_रखो(&ci, 0, माप(ci));
	ci.size = माप(ci);
	ci.busnum = udev->bus->busnum;
	ci.devnum = udev->devnum;
	ci.speed = udev->speed;

	जबतक (udev && udev->portnum != 0) अणु
		अगर (++ci.num_ports <= ARRAY_SIZE(ci.ports))
			ci.ports[ARRAY_SIZE(ci.ports) - ci.num_ports] =
					udev->portnum;
		udev = udev->parent;
	पूर्ण

	अगर (ci.num_ports < ARRAY_SIZE(ci.ports))
		स_हटाओ(&ci.ports[0],
			&ci.ports[ARRAY_SIZE(ci.ports) - ci.num_ports],
			ci.num_ports);

	अगर (copy_to_user(arg, &ci, min(माप(ci), size)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक proc_resetdevice(काष्ठा usb_dev_state *ps)
अणु
	काष्ठा usb_host_config *actconfig = ps->dev->actconfig;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक i, number;

	/* Don't allow a device reset अगर the process has dropped the
	 * privilege to करो such things and any of the पूर्णांकerfaces are
	 * currently claimed.
	 */
	अगर (ps->privileges_dropped && actconfig) अणु
		क्रम (i = 0; i < actconfig->desc.bNumInterfaces; ++i) अणु
			पूर्णांकerface = actconfig->पूर्णांकerface[i];
			number = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
			अगर (usb_पूर्णांकerface_claimed(पूर्णांकerface) &&
					!test_bit(number, &ps->अगरclaimed)) अणु
				dev_warn(&ps->dev->dev,
					"usbfs: interface %d claimed by %s while '%s' resets device\n",
					number,	पूर्णांकerface->dev.driver->name, current->comm);
				वापस -EACCES;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस usb_reset_device(ps->dev);
पूर्ण

अटल पूर्णांक proc_setपूर्णांकf(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_setपूर्णांकerface setपूर्णांकf;
	पूर्णांक ret;

	अगर (copy_from_user(&setपूर्णांकf, arg, माप(setपूर्णांकf)))
		वापस -EFAULT;
	ret = checkपूर्णांकf(ps, setपूर्णांकf.पूर्णांकerface);
	अगर (ret)
		वापस ret;

	destroy_async_on_पूर्णांकerface(ps, setपूर्णांकf.पूर्णांकerface);

	वापस usb_set_पूर्णांकerface(ps->dev, setपूर्णांकf.पूर्णांकerface,
			setपूर्णांकf.altsetting);
पूर्ण

अटल पूर्णांक proc_setconfig(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	पूर्णांक u;
	पूर्णांक status = 0;
	काष्ठा usb_host_config *actconfig;

	अगर (get_user(u, (पूर्णांक __user *)arg))
		वापस -EFAULT;

	actconfig = ps->dev->actconfig;

	/* Don't touch the device अगर any पूर्णांकerfaces are claimed.
	 * It could पूर्णांकerfere with other drivers' operations, and अगर
	 * an पूर्णांकerface is claimed by usbfs it could easily deadlock.
	 */
	अगर (actconfig) अणु
		पूर्णांक i;

		क्रम (i = 0; i < actconfig->desc.bNumInterfaces; ++i) अणु
			अगर (usb_पूर्णांकerface_claimed(actconfig->पूर्णांकerface[i])) अणु
				dev_warn(&ps->dev->dev,
					"usbfs: interface %d claimed by %s "
					"while '%s' sets config #%d\n",
					actconfig->पूर्णांकerface[i]
						->cur_altsetting
						->desc.bInterfaceNumber,
					actconfig->पूर्णांकerface[i]
						->dev.driver->name,
					current->comm, u);
				status = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* SET_CONFIGURATION is often abused as a "cheap" driver reset,
	 * so aव्योम usb_set_configuration()'s kick to sysfs
	 */
	अगर (status == 0) अणु
		अगर (actconfig && actconfig->desc.bConfigurationValue == u)
			status = usb_reset_configuration(ps->dev);
		अन्यथा
			status = usb_set_configuration(ps->dev, u);
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा usb_memory *
find_memory_area(काष्ठा usb_dev_state *ps, स्थिर काष्ठा usbdevfs_urb *uurb)
अणु
	काष्ठा usb_memory *usbm = शून्य, *iter;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ uurb_start = (अचिन्हित दीर्घ)uurb->buffer;

	spin_lock_irqsave(&ps->lock, flags);
	list_क्रम_each_entry(iter, &ps->memory_list, memlist) अणु
		अगर (uurb_start >= iter->vm_start &&
				uurb_start < iter->vm_start + iter->size) अणु
			अगर (uurb->buffer_length > iter->vm_start + iter->size -
					uurb_start) अणु
				usbm = ERR_PTR(-EINVAL);
			पूर्ण अन्यथा अणु
				usbm = iter;
				usbm->urb_use_count++;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ps->lock, flags);
	वापस usbm;
पूर्ण

अटल पूर्णांक proc_करो_submiturb(काष्ठा usb_dev_state *ps, काष्ठा usbdevfs_urb *uurb,
			काष्ठा usbdevfs_iso_packet_desc __user *iso_frame_desc,
			व्योम __user *arg, sigval_t userurb_sigval)
अणु
	काष्ठा usbdevfs_iso_packet_desc *isopkt = शून्य;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा async *as = शून्य;
	काष्ठा usb_ctrlrequest *dr = शून्य;
	अचिन्हित पूर्णांक u, totlen, isofrmlen;
	पूर्णांक i, ret, num_sgs = 0, अगरnum = -1;
	पूर्णांक number_of_packets = 0;
	अचिन्हित पूर्णांक stream_id = 0;
	व्योम *buf;
	bool is_in;
	bool allow_लघु = false;
	bool allow_zero = false;
	अचिन्हित दीर्घ mask =	USBDEVFS_URB_SHORT_NOT_OK |
				USBDEVFS_URB_BULK_CONTINUATION |
				USBDEVFS_URB_NO_FSBR |
				USBDEVFS_URB_ZERO_PACKET |
				USBDEVFS_URB_NO_INTERRUPT;
	/* USBDEVFS_URB_ISO_ASAP is a special हाल */
	अगर (uurb->type == USBDEVFS_URB_TYPE_ISO)
		mask |= USBDEVFS_URB_ISO_ASAP;

	अगर (uurb->flags & ~mask)
			वापस -EINVAL;

	अगर ((अचिन्हित पूर्णांक)uurb->buffer_length >= USBFS_XFER_MAX)
		वापस -EINVAL;
	अगर (uurb->buffer_length > 0 && !uurb->buffer)
		वापस -EINVAL;
	अगर (!(uurb->type == USBDEVFS_URB_TYPE_CONTROL &&
	    (uurb->endpoपूर्णांक & ~USB_ENDPOINT_सूची_MASK) == 0)) अणु
		अगरnum = findपूर्णांकfep(ps->dev, uurb->endpoपूर्णांक);
		अगर (अगरnum < 0)
			वापस अगरnum;
		ret = checkपूर्णांकf(ps, अगरnum);
		अगर (ret)
			वापस ret;
	पूर्ण
	ep = ep_to_host_endpoपूर्णांक(ps->dev, uurb->endpoपूर्णांक);
	अगर (!ep)
		वापस -ENOENT;
	is_in = (uurb->endpoपूर्णांक & USB_ENDPOINT_सूची_MASK) != 0;

	u = 0;
	चयन (uurb->type) अणु
	हाल USBDEVFS_URB_TYPE_CONTROL:
		अगर (!usb_endpoपूर्णांक_xfer_control(&ep->desc))
			वापस -EINVAL;
		/* min 8 byte setup packet */
		अगर (uurb->buffer_length < 8)
			वापस -EINVAL;
		dr = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
		अगर (!dr)
			वापस -ENOMEM;
		अगर (copy_from_user(dr, uurb->buffer, 8)) अणु
			ret = -EFAULT;
			जाओ error;
		पूर्ण
		अगर (uurb->buffer_length < (le16_to_cpu(dr->wLength) + 8)) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		ret = check_ctrlrecip(ps, dr->bRequestType, dr->bRequest,
				      le16_to_cpu(dr->wIndex));
		अगर (ret)
			जाओ error;
		uurb->buffer_length = le16_to_cpu(dr->wLength);
		uurb->buffer += 8;
		अगर ((dr->bRequestType & USB_सूची_IN) && uurb->buffer_length) अणु
			is_in = true;
			uurb->endpoपूर्णांक |= USB_सूची_IN;
		पूर्ण अन्यथा अणु
			is_in = false;
			uurb->endpoपूर्णांक &= ~USB_सूची_IN;
		पूर्ण
		अगर (is_in)
			allow_लघु = true;
		snoop(&ps->dev->dev, "control urb: bRequestType=%02x "
			"bRequest=%02x wValue=%04x "
			"wIndex=%04x wLength=%04x\n",
			dr->bRequestType, dr->bRequest,
			__le16_to_cpu(dr->wValue),
			__le16_to_cpu(dr->wIndex),
			__le16_to_cpu(dr->wLength));
		u = माप(काष्ठा usb_ctrlrequest);
		अवरोध;

	हाल USBDEVFS_URB_TYPE_BULK:
		अगर (!is_in)
			allow_zero = true;
		अन्यथा
			allow_लघु = true;
		चयन (usb_endpoपूर्णांक_type(&ep->desc)) अणु
		हाल USB_ENDPOINT_XFER_CONTROL:
		हाल USB_ENDPOINT_XFER_ISOC:
			वापस -EINVAL;
		हाल USB_ENDPOINT_XFER_INT:
			/* allow single-shot पूर्णांकerrupt transfers */
			uurb->type = USBDEVFS_URB_TYPE_INTERRUPT;
			जाओ पूर्णांकerrupt_urb;
		पूर्ण
		num_sgs = DIV_ROUND_UP(uurb->buffer_length, USB_SG_SIZE);
		अगर (num_sgs == 1 || num_sgs > ps->dev->bus->sg_tablesize)
			num_sgs = 0;
		अगर (ep->streams)
			stream_id = uurb->stream_id;
		अवरोध;

	हाल USBDEVFS_URB_TYPE_INTERRUPT:
		अगर (!usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc))
			वापस -EINVAL;
 पूर्णांकerrupt_urb:
		अगर (!is_in)
			allow_zero = true;
		अन्यथा
			allow_लघु = true;
		अवरोध;

	हाल USBDEVFS_URB_TYPE_ISO:
		/* arbitrary limit */
		अगर (uurb->number_of_packets < 1 ||
		    uurb->number_of_packets > 128)
			वापस -EINVAL;
		अगर (!usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
			वापस -EINVAL;
		number_of_packets = uurb->number_of_packets;
		isofrmlen = माप(काष्ठा usbdevfs_iso_packet_desc) *
				   number_of_packets;
		isopkt = memdup_user(iso_frame_desc, isofrmlen);
		अगर (IS_ERR(isopkt)) अणु
			ret = PTR_ERR(isopkt);
			isopkt = शून्य;
			जाओ error;
		पूर्ण
		क्रम (totlen = u = 0; u < number_of_packets; u++) अणु
			/*
			 * arbitrary limit need क्रम USB 3.1 Gen2
			 * sizemax: 96 DPs at SSP, 96 * 1024 = 98304
			 */
			अगर (isopkt[u].length > 98304) अणु
				ret = -EINVAL;
				जाओ error;
			पूर्ण
			totlen += isopkt[u].length;
		पूर्ण
		u *= माप(काष्ठा usb_iso_packet_descriptor);
		uurb->buffer_length = totlen;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (uurb->buffer_length > 0 &&
			!access_ok(uurb->buffer, uurb->buffer_length)) अणु
		ret = -EFAULT;
		जाओ error;
	पूर्ण
	as = alloc_async(number_of_packets);
	अगर (!as) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	as->usbm = find_memory_area(ps, uurb);
	अगर (IS_ERR(as->usbm)) अणु
		ret = PTR_ERR(as->usbm);
		as->usbm = शून्य;
		जाओ error;
	पूर्ण

	/* करो not use SG buffers when memory mapped segments
	 * are in use
	 */
	अगर (as->usbm)
		num_sgs = 0;

	u += माप(काष्ठा async) + माप(काष्ठा urb) +
	     (as->usbm ? 0 : uurb->buffer_length) +
	     num_sgs * माप(काष्ठा scatterlist);
	ret = usbfs_increase_memory_usage(u);
	अगर (ret)
		जाओ error;
	as->mem_usage = u;

	अगर (num_sgs) अणु
		as->urb->sg = kदो_स्मृति_array(num_sgs,
					    माप(काष्ठा scatterlist),
					    GFP_KERNEL | __GFP_NOWARN);
		अगर (!as->urb->sg) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		as->urb->num_sgs = num_sgs;
		sg_init_table(as->urb->sg, as->urb->num_sgs);

		totlen = uurb->buffer_length;
		क्रम (i = 0; i < as->urb->num_sgs; i++) अणु
			u = (totlen > USB_SG_SIZE) ? USB_SG_SIZE : totlen;
			buf = kदो_स्मृति(u, GFP_KERNEL);
			अगर (!buf) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
			sg_set_buf(&as->urb->sg[i], buf, u);

			अगर (!is_in) अणु
				अगर (copy_from_user(buf, uurb->buffer, u)) अणु
					ret = -EFAULT;
					जाओ error;
				पूर्ण
				uurb->buffer += u;
			पूर्ण
			totlen -= u;
		पूर्ण
	पूर्ण अन्यथा अगर (uurb->buffer_length > 0) अणु
		अगर (as->usbm) अणु
			अचिन्हित दीर्घ uurb_start = (अचिन्हित दीर्घ)uurb->buffer;

			as->urb->transfer_buffer = as->usbm->mem +
					(uurb_start - as->usbm->vm_start);
		पूर्ण अन्यथा अणु
			as->urb->transfer_buffer = kदो_स्मृति(uurb->buffer_length,
					GFP_KERNEL | __GFP_NOWARN);
			अगर (!as->urb->transfer_buffer) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
			अगर (!is_in) अणु
				अगर (copy_from_user(as->urb->transfer_buffer,
						   uurb->buffer,
						   uurb->buffer_length)) अणु
					ret = -EFAULT;
					जाओ error;
				पूर्ण
			पूर्ण अन्यथा अगर (uurb->type == USBDEVFS_URB_TYPE_ISO) अणु
				/*
				 * Isochronous input data may end up being
				 * discontiguous अगर some of the packets are
				 * लघु. Clear the buffer so that the gaps
				 * करोn't leak kernel data to userspace.
				 */
				स_रखो(as->urb->transfer_buffer, 0,
						uurb->buffer_length);
			पूर्ण
		पूर्ण
	पूर्ण
	as->urb->dev = ps->dev;
	as->urb->pipe = (uurb->type << 30) |
			__create_pipe(ps->dev, uurb->endpoपूर्णांक & 0xf) |
			(uurb->endpoपूर्णांक & USB_सूची_IN);

	/* This tedious sequence is necessary because the URB_* flags
	 * are पूर्णांकernal to the kernel and subject to change, whereas
	 * the USBDEVFS_URB_* flags are a user API and must not be changed.
	 */
	u = (is_in ? URB_सूची_IN : URB_सूची_OUT);
	अगर (uurb->flags & USBDEVFS_URB_ISO_ASAP)
		u |= URB_ISO_ASAP;
	अगर (allow_लघु && uurb->flags & USBDEVFS_URB_SHORT_NOT_OK)
		u |= URB_SHORT_NOT_OK;
	अगर (allow_zero && uurb->flags & USBDEVFS_URB_ZERO_PACKET)
		u |= URB_ZERO_PACKET;
	अगर (uurb->flags & USBDEVFS_URB_NO_INTERRUPT)
		u |= URB_NO_INTERRUPT;
	as->urb->transfer_flags = u;

	अगर (!allow_लघु && uurb->flags & USBDEVFS_URB_SHORT_NOT_OK)
		dev_warn(&ps->dev->dev, "Requested nonsensical USBDEVFS_URB_SHORT_NOT_OK.\n");
	अगर (!allow_zero && uurb->flags & USBDEVFS_URB_ZERO_PACKET)
		dev_warn(&ps->dev->dev, "Requested nonsensical USBDEVFS_URB_ZERO_PACKET.\n");

	as->urb->transfer_buffer_length = uurb->buffer_length;
	as->urb->setup_packet = (अचिन्हित अक्षर *)dr;
	dr = शून्य;
	as->urb->start_frame = uurb->start_frame;
	as->urb->number_of_packets = number_of_packets;
	as->urb->stream_id = stream_id;

	अगर (ep->desc.bInterval) अणु
		अगर (uurb->type == USBDEVFS_URB_TYPE_ISO ||
				ps->dev->speed == USB_SPEED_HIGH ||
				ps->dev->speed >= USB_SPEED_SUPER)
			as->urb->पूर्णांकerval = 1 <<
					min(15, ep->desc.bInterval - 1);
		अन्यथा
			as->urb->पूर्णांकerval = ep->desc.bInterval;
	पूर्ण

	as->urb->context = as;
	as->urb->complete = async_completed;
	क्रम (totlen = u = 0; u < number_of_packets; u++) अणु
		as->urb->iso_frame_desc[u].offset = totlen;
		as->urb->iso_frame_desc[u].length = isopkt[u].length;
		totlen += isopkt[u].length;
	पूर्ण
	kमुक्त(isopkt);
	isopkt = शून्य;
	as->ps = ps;
	as->userurb = arg;
	as->userurb_sigval = userurb_sigval;
	अगर (as->usbm) अणु
		अचिन्हित दीर्घ uurb_start = (अचिन्हित दीर्घ)uurb->buffer;

		as->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		as->urb->transfer_dma = as->usbm->dma_handle +
				(uurb_start - as->usbm->vm_start);
	पूर्ण अन्यथा अगर (is_in && uurb->buffer_length > 0)
		as->userbuffer = uurb->buffer;
	as->signr = uurb->signr;
	as->अगरnum = अगरnum;
	as->pid = get_pid(task_pid(current));
	as->cred = get_current_cred();
	snoop_urb(ps->dev, as->userurb, as->urb->pipe,
			as->urb->transfer_buffer_length, 0, SUBMIT,
			शून्य, 0);
	अगर (!is_in)
		snoop_urb_data(as->urb, as->urb->transfer_buffer_length);

	async_newpending(as);

	अगर (usb_endpoपूर्णांक_xfer_bulk(&ep->desc)) अणु
		spin_lock_irq(&ps->lock);

		/* Not exactly the endpoपूर्णांक address; the direction bit is
		 * shअगरted to the 0x10 position so that the value will be
		 * between 0 and 31.
		 */
		as->bulk_addr = usb_endpoपूर्णांक_num(&ep->desc) |
			((ep->desc.bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK)
				>> 3);

		/* If this bulk URB is the start of a new transfer, re-enable
		 * the endpoपूर्णांक.  Otherwise mark it as a continuation URB.
		 */
		अगर (uurb->flags & USBDEVFS_URB_BULK_CONTINUATION)
			as->bulk_status = AS_CONTINUATION;
		अन्यथा
			ps->disabled_bulk_eps &= ~(1 << as->bulk_addr);

		/* Don't accept continuation URBs अगर the endpoपूर्णांक is
		 * disabled because of an earlier error.
		 */
		अगर (ps->disabled_bulk_eps & (1 << as->bulk_addr))
			ret = -EREMOTEIO;
		अन्यथा
			ret = usb_submit_urb(as->urb, GFP_ATOMIC);
		spin_unlock_irq(&ps->lock);
	पूर्ण अन्यथा अणु
		ret = usb_submit_urb(as->urb, GFP_KERNEL);
	पूर्ण

	अगर (ret) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &ps->dev->dev,
			   "usbfs: usb_submit_urb returned %d\n", ret);
		snoop_urb(ps->dev, as->userurb, as->urb->pipe,
				0, ret, COMPLETE, शून्य, 0);
		async_हटाओpending(as);
		जाओ error;
	पूर्ण
	वापस 0;

 error:
	kमुक्त(isopkt);
	kमुक्त(dr);
	अगर (as)
		मुक्त_async(as);
	वापस ret;
पूर्ण

अटल पूर्णांक proc_submiturb(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_urb uurb;
	sigval_t userurb_sigval;

	अगर (copy_from_user(&uurb, arg, माप(uurb)))
		वापस -EFAULT;

	स_रखो(&userurb_sigval, 0, माप(userurb_sigval));
	userurb_sigval.sival_ptr = arg;

	वापस proc_करो_submiturb(ps, &uurb,
			(((काष्ठा usbdevfs_urb __user *)arg)->iso_frame_desc),
			arg, userurb_sigval);
पूर्ण

अटल पूर्णांक proc_unlinkurb(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा urb *urb;
	काष्ठा async *as;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->lock, flags);
	as = async_getpending(ps, arg);
	अगर (!as) अणु
		spin_unlock_irqrestore(&ps->lock, flags);
		वापस -EINVAL;
	पूर्ण

	urb = as->urb;
	usb_get_urb(urb);
	spin_unlock_irqrestore(&ps->lock, flags);

	usb_समाप्त_urb(urb);
	usb_put_urb(urb);

	वापस 0;
पूर्ण

अटल व्योम compute_isochronous_actual_length(काष्ठा urb *urb)
अणु
	अचिन्हित पूर्णांक i;

	अगर (urb->number_of_packets > 0) अणु
		urb->actual_length = 0;
		क्रम (i = 0; i < urb->number_of_packets; i++)
			urb->actual_length +=
					urb->iso_frame_desc[i].actual_length;
	पूर्ण
पूर्ण

अटल पूर्णांक processcompl(काष्ठा async *as, व्योम __user * __user *arg)
अणु
	काष्ठा urb *urb = as->urb;
	काष्ठा usbdevfs_urb __user *userurb = as->userurb;
	व्योम __user *addr = as->userurb;
	अचिन्हित पूर्णांक i;

	compute_isochronous_actual_length(urb);
	अगर (as->userbuffer && urb->actual_length) अणु
		अगर (copy_urb_data_to_user(as->userbuffer, urb))
			जाओ err_out;
	पूर्ण
	अगर (put_user(as->status, &userurb->status))
		जाओ err_out;
	अगर (put_user(urb->actual_length, &userurb->actual_length))
		जाओ err_out;
	अगर (put_user(urb->error_count, &userurb->error_count))
		जाओ err_out;

	अगर (usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc)) अणु
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अगर (put_user(urb->iso_frame_desc[i].actual_length,
				     &userurb->iso_frame_desc[i].actual_length))
				जाओ err_out;
			अगर (put_user(urb->iso_frame_desc[i].status,
				     &userurb->iso_frame_desc[i].status))
				जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (put_user(addr, (व्योम __user * __user *)arg))
		वापस -EFAULT;
	वापस 0;

err_out:
	वापस -EFAULT;
पूर्ण

अटल काष्ठा async *reap_as(काष्ठा usb_dev_state *ps)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा async *as = शून्य;
	काष्ठा usb_device *dev = ps->dev;

	add_रुको_queue(&ps->रुको, &रुको);
	क्रम (;;) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		as = async_अ_लोompleted(ps);
		अगर (as || !connected(ps))
			अवरोध;
		अगर (संकेत_pending(current))
			अवरोध;
		usb_unlock_device(dev);
		schedule();
		usb_lock_device(dev);
	पूर्ण
	हटाओ_रुको_queue(&ps->रुको, &रुको);
	set_current_state(TASK_RUNNING);
	वापस as;
पूर्ण

अटल पूर्णांक proc_reapurb(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा async *as = reap_as(ps);

	अगर (as) अणु
		पूर्णांक retval;

		snoop(&ps->dev->dev, "reap %px\n", as->userurb);
		retval = processcompl(as, (व्योम __user * __user *)arg);
		मुक्त_async(as);
		वापस retval;
	पूर्ण
	अगर (संकेत_pending(current))
		वापस -EINTR;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक proc_reapurbnonblock(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	पूर्णांक retval;
	काष्ठा async *as;

	as = async_अ_लोompleted(ps);
	अगर (as) अणु
		snoop(&ps->dev->dev, "reap %px\n", as->userurb);
		retval = processcompl(as, (व्योम __user * __user *)arg);
		मुक्त_async(as);
	पूर्ण अन्यथा अणु
		retval = (connected(ps) ? -EAGAIN : -ENODEV);
	पूर्ण
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक proc_control_compat(काष्ठा usb_dev_state *ps,
				काष्ठा usbdevfs_ctrltransfer32 __user *p32)
अणु
	काष्ठा usbdevfs_ctrltransfer ctrl;
	u32 udata;

	अगर (copy_from_user(&ctrl, p32, माप(*p32) - माप(compat_caddr_t)) ||
	    get_user(udata, &p32->data))
		वापस -EFAULT;
	ctrl.data = compat_ptr(udata);
	वापस करो_proc_control(ps, &ctrl);
पूर्ण

अटल पूर्णांक proc_bulk_compat(काष्ठा usb_dev_state *ps,
			काष्ठा usbdevfs_bulktransfer32 __user *p32)
अणु
	काष्ठा usbdevfs_bulktransfer bulk;
	compat_caddr_t addr;

	अगर (get_user(bulk.ep, &p32->ep) ||
	    get_user(bulk.len, &p32->len) ||
	    get_user(bulk.समयout, &p32->समयout) ||
	    get_user(addr, &p32->data))
		वापस -EFAULT;
	bulk.data = compat_ptr(addr);
	वापस करो_proc_bulk(ps, &bulk);
पूर्ण

अटल पूर्णांक proc_disconnectसंकेत_compat(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_disconnectसंकेत32 ds;

	अगर (copy_from_user(&ds, arg, माप(ds)))
		वापस -EFAULT;
	ps->discsignr = ds.signr;
	ps->disccontext.sival_पूर्णांक = ds.context;
	वापस 0;
पूर्ण

अटल पूर्णांक get_urb32(काष्ठा usbdevfs_urb *kurb,
		     काष्ठा usbdevfs_urb32 __user *uurb)
अणु
	काष्ठा usbdevfs_urb32 urb32;
	अगर (copy_from_user(&urb32, uurb, माप(*uurb)))
		वापस -EFAULT;
	kurb->type = urb32.type;
	kurb->endpoपूर्णांक = urb32.endpoपूर्णांक;
	kurb->status = urb32.status;
	kurb->flags = urb32.flags;
	kurb->buffer = compat_ptr(urb32.buffer);
	kurb->buffer_length = urb32.buffer_length;
	kurb->actual_length = urb32.actual_length;
	kurb->start_frame = urb32.start_frame;
	kurb->number_of_packets = urb32.number_of_packets;
	kurb->error_count = urb32.error_count;
	kurb->signr = urb32.signr;
	kurb->usercontext = compat_ptr(urb32.usercontext);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_submiturb_compat(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_urb uurb;
	sigval_t userurb_sigval;

	अगर (get_urb32(&uurb, (काष्ठा usbdevfs_urb32 __user *)arg))
		वापस -EFAULT;

	स_रखो(&userurb_sigval, 0, माप(userurb_sigval));
	userurb_sigval.sival_पूर्णांक = ptr_to_compat(arg);

	वापस proc_करो_submiturb(ps, &uurb,
			((काष्ठा usbdevfs_urb32 __user *)arg)->iso_frame_desc,
			arg, userurb_sigval);
पूर्ण

अटल पूर्णांक processcompl_compat(काष्ठा async *as, व्योम __user * __user *arg)
अणु
	काष्ठा urb *urb = as->urb;
	काष्ठा usbdevfs_urb32 __user *userurb = as->userurb;
	व्योम __user *addr = as->userurb;
	अचिन्हित पूर्णांक i;

	compute_isochronous_actual_length(urb);
	अगर (as->userbuffer && urb->actual_length) अणु
		अगर (copy_urb_data_to_user(as->userbuffer, urb))
			वापस -EFAULT;
	पूर्ण
	अगर (put_user(as->status, &userurb->status))
		वापस -EFAULT;
	अगर (put_user(urb->actual_length, &userurb->actual_length))
		वापस -EFAULT;
	अगर (put_user(urb->error_count, &userurb->error_count))
		वापस -EFAULT;

	अगर (usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc)) अणु
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अगर (put_user(urb->iso_frame_desc[i].actual_length,
				     &userurb->iso_frame_desc[i].actual_length))
				वापस -EFAULT;
			अगर (put_user(urb->iso_frame_desc[i].status,
				     &userurb->iso_frame_desc[i].status))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (put_user(ptr_to_compat(addr), (u32 __user *)arg))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक proc_reapurb_compat(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा async *as = reap_as(ps);

	अगर (as) अणु
		पूर्णांक retval;

		snoop(&ps->dev->dev, "reap %px\n", as->userurb);
		retval = processcompl_compat(as, (व्योम __user * __user *)arg);
		मुक्त_async(as);
		वापस retval;
	पूर्ण
	अगर (संकेत_pending(current))
		वापस -EINTR;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक proc_reapurbnonblock_compat(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	पूर्णांक retval;
	काष्ठा async *as;

	as = async_अ_लोompleted(ps);
	अगर (as) अणु
		snoop(&ps->dev->dev, "reap %px\n", as->userurb);
		retval = processcompl_compat(as, (व्योम __user * __user *)arg);
		मुक्त_async(as);
	पूर्ण अन्यथा अणु
		retval = (connected(ps) ? -EAGAIN : -ENODEV);
	पूर्ण
	वापस retval;
पूर्ण


#पूर्ण_अगर

अटल पूर्णांक proc_disconnectसंकेत(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_disconnectसंकेत ds;

	अगर (copy_from_user(&ds, arg, माप(ds)))
		वापस -EFAULT;
	ps->discsignr = ds.signr;
	ps->disccontext.sival_ptr = ds.context;
	वापस 0;
पूर्ण

अटल पूर्णांक proc_claimपूर्णांकerface(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित पूर्णांक अगरnum;

	अगर (get_user(अगरnum, (अचिन्हित पूर्णांक __user *)arg))
		वापस -EFAULT;
	वापस claimपूर्णांकf(ps, अगरnum);
पूर्ण

अटल पूर्णांक proc_releaseपूर्णांकerface(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित पूर्णांक अगरnum;
	पूर्णांक ret;

	अगर (get_user(अगरnum, (अचिन्हित पूर्णांक __user *)arg))
		वापस -EFAULT;
	ret = releaseपूर्णांकf(ps, अगरnum);
	अगर (ret < 0)
		वापस ret;
	destroy_async_on_पूर्णांकerface(ps, अगरnum);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_ioctl(काष्ठा usb_dev_state *ps, काष्ठा usbdevfs_ioctl *ctl)
अणु
	पूर्णांक			size;
	व्योम			*buf = शून्य;
	पूर्णांक			retval = 0;
	काष्ठा usb_पूर्णांकerface    *पूर्णांकf = शून्य;
	काष्ठा usb_driver       *driver = शून्य;

	अगर (ps->privileges_dropped)
		वापस -EACCES;

	अगर (!connected(ps))
		वापस -ENODEV;

	/* alloc buffer */
	size = _IOC_SIZE(ctl->ioctl_code);
	अगर (size > 0) अणु
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
		अगर ((_IOC_सूची(ctl->ioctl_code) & _IOC_WRITE)) अणु
			अगर (copy_from_user(buf, ctl->data, size)) अणु
				kमुक्त(buf);
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_रखो(buf, 0, size);
		पूर्ण
	पूर्ण

	अगर (ps->dev->state != USB_STATE_CONFIGURED)
		retval = -EHOSTUNREACH;
	अन्यथा अगर (!(पूर्णांकf = usb_अगरnum_to_अगर(ps->dev, ctl->अगरno)))
		retval = -EINVAL;
	अन्यथा चयन (ctl->ioctl_code) अणु

	/* disconnect kernel driver from पूर्णांकerface */
	हाल USBDEVFS_DISCONNECT:
		अगर (पूर्णांकf->dev.driver) अणु
			driver = to_usb_driver(पूर्णांकf->dev.driver);
			dev_dbg(&पूर्णांकf->dev, "disconnect by usbfs\n");
			usb_driver_release_पूर्णांकerface(driver, पूर्णांकf);
		पूर्ण अन्यथा
			retval = -ENODATA;
		अवरोध;

	/* let kernel drivers try to (re)bind to the पूर्णांकerface */
	हाल USBDEVFS_CONNECT:
		अगर (!पूर्णांकf->dev.driver)
			retval = device_attach(&पूर्णांकf->dev);
		अन्यथा
			retval = -EBUSY;
		अवरोध;

	/* talk directly to the पूर्णांकerface's driver */
	शेष:
		अगर (पूर्णांकf->dev.driver)
			driver = to_usb_driver(पूर्णांकf->dev.driver);
		अगर (driver == शून्य || driver->unlocked_ioctl == शून्य) अणु
			retval = -ENOTTY;
		पूर्ण अन्यथा अणु
			retval = driver->unlocked_ioctl(पूर्णांकf, ctl->ioctl_code, buf);
			अगर (retval == -ENOIOCTLCMD)
				retval = -ENOTTY;
		पूर्ण
	पूर्ण

	/* cleanup and वापस */
	अगर (retval >= 0
			&& (_IOC_सूची(ctl->ioctl_code) & _IOC_READ) != 0
			&& size > 0
			&& copy_to_user(ctl->data, buf, size) != 0)
		retval = -EFAULT;

	kमुक्त(buf);
	वापस retval;
पूर्ण

अटल पूर्णांक proc_ioctl_शेष(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_ioctl	ctrl;

	अगर (copy_from_user(&ctrl, arg, माप(ctrl)))
		वापस -EFAULT;
	वापस proc_ioctl(ps, &ctrl);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक proc_ioctl_compat(काष्ठा usb_dev_state *ps, compat_uptr_t arg)
अणु
	काष्ठा usbdevfs_ioctl32 ioc32;
	काष्ठा usbdevfs_ioctl ctrl;

	अगर (copy_from_user(&ioc32, compat_ptr(arg), माप(ioc32)))
		वापस -EFAULT;
	ctrl.अगरno = ioc32.अगरno;
	ctrl.ioctl_code = ioc32.ioctl_code;
	ctrl.data = compat_ptr(ioc32.data);
	वापस proc_ioctl(ps, &ctrl);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक proc_claim_port(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित portnum;
	पूर्णांक rc;

	अगर (get_user(portnum, (अचिन्हित __user *) arg))
		वापस -EFAULT;
	rc = usb_hub_claim_port(ps->dev, portnum, ps);
	अगर (rc == 0)
		snoop(&ps->dev->dev, "port %d claimed by process %d: %s\n",
			portnum, task_pid_nr(current), current->comm);
	वापस rc;
पूर्ण

अटल पूर्णांक proc_release_port(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित portnum;

	अगर (get_user(portnum, (अचिन्हित __user *) arg))
		वापस -EFAULT;
	वापस usb_hub_release_port(ps->dev, portnum, ps);
पूर्ण

अटल पूर्णांक proc_get_capabilities(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	__u32 caps;

	caps = USBDEVFS_CAP_ZERO_PACKET | USBDEVFS_CAP_NO_PACKET_SIZE_LIM |
			USBDEVFS_CAP_REAP_AFTER_DISCONNECT | USBDEVFS_CAP_MMAP |
			USBDEVFS_CAP_DROP_PRIVILEGES |
			USBDEVFS_CAP_CONNINFO_EX | MAYBE_CAP_SUSPEND;
	अगर (!ps->dev->bus->no_stop_on_लघु)
		caps |= USBDEVFS_CAP_BULK_CONTINUATION;
	अगर (ps->dev->bus->sg_tablesize)
		caps |= USBDEVFS_CAP_BULK_SCATTER_GATHER;

	अगर (put_user(caps, (__u32 __user *)arg))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक proc_disconnect_claim(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	काष्ठा usbdevfs_disconnect_claim dc;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	अगर (copy_from_user(&dc, arg, माप(dc)))
		वापस -EFAULT;

	पूर्णांकf = usb_अगरnum_to_अगर(ps->dev, dc.पूर्णांकerface);
	अगर (!पूर्णांकf)
		वापस -EINVAL;

	अगर (पूर्णांकf->dev.driver) अणु
		काष्ठा usb_driver *driver = to_usb_driver(पूर्णांकf->dev.driver);

		अगर (ps->privileges_dropped)
			वापस -EACCES;

		अगर ((dc.flags & USBDEVFS_DISCONNECT_CLAIM_IF_DRIVER) &&
				म_भेदन(dc.driver, पूर्णांकf->dev.driver->name,
					माप(dc.driver)) != 0)
			वापस -EBUSY;

		अगर ((dc.flags & USBDEVFS_DISCONNECT_CLAIM_EXCEPT_DRIVER) &&
				म_भेदन(dc.driver, पूर्णांकf->dev.driver->name,
					माप(dc.driver)) == 0)
			वापस -EBUSY;

		dev_dbg(&पूर्णांकf->dev, "disconnect by usbfs\n");
		usb_driver_release_पूर्णांकerface(driver, पूर्णांकf);
	पूर्ण

	वापस claimपूर्णांकf(ps, dc.पूर्णांकerface);
पूर्ण

अटल पूर्णांक proc_alloc_streams(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित num_streams, num_eps;
	काष्ठा usb_host_endpoपूर्णांक **eps;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक r;

	r = parse_usbdevfs_streams(ps, arg, &num_streams, &num_eps,
				   &eps, &पूर्णांकf);
	अगर (r)
		वापस r;

	destroy_async_on_पूर्णांकerface(ps,
				   पूर्णांकf->altsetting[0].desc.bInterfaceNumber);

	r = usb_alloc_streams(पूर्णांकf, eps, num_eps, num_streams, GFP_KERNEL);
	kमुक्त(eps);
	वापस r;
पूर्ण

अटल पूर्णांक proc_मुक्त_streams(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	अचिन्हित num_eps;
	काष्ठा usb_host_endpoपूर्णांक **eps;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक r;

	r = parse_usbdevfs_streams(ps, arg, शून्य, &num_eps, &eps, &पूर्णांकf);
	अगर (r)
		वापस r;

	destroy_async_on_पूर्णांकerface(ps,
				   पूर्णांकf->altsetting[0].desc.bInterfaceNumber);

	r = usb_मुक्त_streams(पूर्णांकf, eps, num_eps, GFP_KERNEL);
	kमुक्त(eps);
	वापस r;
पूर्ण

अटल पूर्णांक proc_drop_privileges(काष्ठा usb_dev_state *ps, व्योम __user *arg)
अणु
	u32 data;

	अगर (copy_from_user(&data, arg, माप(data)))
		वापस -EFAULT;

	/* This is a one way operation. Once privileges are
	 * dropped, you cannot regain them. You may however reissue
	 * this ioctl to shrink the allowed पूर्णांकerfaces mask.
	 */
	ps->पूर्णांकerface_allowed_mask &= data;
	ps->privileges_dropped = true;

	वापस 0;
पूर्ण

अटल पूर्णांक proc_क्रमbid_suspend(काष्ठा usb_dev_state *ps)
अणु
	पूर्णांक ret = 0;

	अगर (ps->suspend_allowed) अणु
		ret = usb_स्वतःresume_device(ps->dev);
		अगर (ret == 0)
			ps->suspend_allowed = false;
		अन्यथा अगर (ret != -ENODEV)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक proc_allow_suspend(काष्ठा usb_dev_state *ps)
अणु
	अगर (!connected(ps))
		वापस -ENODEV;

	WRITE_ONCE(ps->not_yet_resumed, 1);
	अगर (!ps->suspend_allowed) अणु
		usb_स्वतःsuspend_device(ps->dev);
		ps->suspend_allowed = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक proc_रुको_क्रम_resume(काष्ठा usb_dev_state *ps)
अणु
	पूर्णांक ret;

	usb_unlock_device(ps->dev);
	ret = रुको_event_पूर्णांकerruptible(ps->रुको_क्रम_resume,
			READ_ONCE(ps->not_yet_resumed) == 0);
	usb_lock_device(ps->dev);

	अगर (ret != 0)
		वापस -EINTR;
	वापस proc_क्रमbid_suspend(ps);
पूर्ण

/*
 * NOTE:  All requests here that have पूर्णांकerface numbers as parameters
 * are assuming that somehow the configuration has been prevented from
 * changing.  But there's no mechanism to ensure that...
 */
अटल दीर्घ usbdev_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				व्योम __user *p)
अणु
	काष्ठा usb_dev_state *ps = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा usb_device *dev = ps->dev;
	पूर्णांक ret = -ENOTTY;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EPERM;

	usb_lock_device(dev);

	/* Reap operations are allowed even after disconnection */
	चयन (cmd) अणु
	हाल USBDEVFS_REAPURB:
		snoop(&dev->dev, "%s: REAPURB\n", __func__);
		ret = proc_reapurb(ps, p);
		जाओ करोne;

	हाल USBDEVFS_REAPURBNDELAY:
		snoop(&dev->dev, "%s: REAPURBNDELAY\n", __func__);
		ret = proc_reapurbnonblock(ps, p);
		जाओ करोne;

#अगर_घोषित CONFIG_COMPAT
	हाल USBDEVFS_REAPURB32:
		snoop(&dev->dev, "%s: REAPURB32\n", __func__);
		ret = proc_reapurb_compat(ps, p);
		जाओ करोne;

	हाल USBDEVFS_REAPURBNDELAY32:
		snoop(&dev->dev, "%s: REAPURBNDELAY32\n", __func__);
		ret = proc_reapurbnonblock_compat(ps, p);
		जाओ करोne;
#पूर्ण_अगर
	पूर्ण

	अगर (!connected(ps)) अणु
		usb_unlock_device(dev);
		वापस -ENODEV;
	पूर्ण

	चयन (cmd) अणु
	हाल USBDEVFS_CONTROL:
		snoop(&dev->dev, "%s: CONTROL\n", __func__);
		ret = proc_control(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_BULK:
		snoop(&dev->dev, "%s: BULK\n", __func__);
		ret = proc_bulk(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_RESETEP:
		snoop(&dev->dev, "%s: RESETEP\n", __func__);
		ret = proc_resetep(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_RESET:
		snoop(&dev->dev, "%s: RESET\n", __func__);
		ret = proc_resetdevice(ps);
		अवरोध;

	हाल USBDEVFS_CLEAR_HALT:
		snoop(&dev->dev, "%s: CLEAR_HALT\n", __func__);
		ret = proc_clearhalt(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_GETDRIVER:
		snoop(&dev->dev, "%s: GETDRIVER\n", __func__);
		ret = proc_getdriver(ps, p);
		अवरोध;

	हाल USBDEVFS_CONNECTINFO:
		snoop(&dev->dev, "%s: CONNECTINFO\n", __func__);
		ret = proc_connectinfo(ps, p);
		अवरोध;

	हाल USBDEVFS_SETINTERFACE:
		snoop(&dev->dev, "%s: SETINTERFACE\n", __func__);
		ret = proc_setपूर्णांकf(ps, p);
		अवरोध;

	हाल USBDEVFS_SETCONFIGURATION:
		snoop(&dev->dev, "%s: SETCONFIGURATION\n", __func__);
		ret = proc_setconfig(ps, p);
		अवरोध;

	हाल USBDEVFS_SUBMITURB:
		snoop(&dev->dev, "%s: SUBMITURB\n", __func__);
		ret = proc_submiturb(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

#अगर_घोषित CONFIG_COMPAT
	हाल USBDEVFS_CONTROL32:
		snoop(&dev->dev, "%s: CONTROL32\n", __func__);
		ret = proc_control_compat(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_BULK32:
		snoop(&dev->dev, "%s: BULK32\n", __func__);
		ret = proc_bulk_compat(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_DISCSIGNAL32:
		snoop(&dev->dev, "%s: DISCSIGNAL32\n", __func__);
		ret = proc_disconnectसंकेत_compat(ps, p);
		अवरोध;

	हाल USBDEVFS_SUBMITURB32:
		snoop(&dev->dev, "%s: SUBMITURB32\n", __func__);
		ret = proc_submiturb_compat(ps, p);
		अगर (ret >= 0)
			inode->i_mसमय = current_समय(inode);
		अवरोध;

	हाल USBDEVFS_IOCTL32:
		snoop(&dev->dev, "%s: IOCTL32\n", __func__);
		ret = proc_ioctl_compat(ps, ptr_to_compat(p));
		अवरोध;
#पूर्ण_अगर

	हाल USBDEVFS_DISCARDURB:
		snoop(&dev->dev, "%s: DISCARDURB %px\n", __func__, p);
		ret = proc_unlinkurb(ps, p);
		अवरोध;

	हाल USBDEVFS_DISCSIGNAL:
		snoop(&dev->dev, "%s: DISCSIGNAL\n", __func__);
		ret = proc_disconnectसंकेत(ps, p);
		अवरोध;

	हाल USBDEVFS_CLAIMINTERFACE:
		snoop(&dev->dev, "%s: CLAIMINTERFACE\n", __func__);
		ret = proc_claimपूर्णांकerface(ps, p);
		अवरोध;

	हाल USBDEVFS_RELEASEINTERFACE:
		snoop(&dev->dev, "%s: RELEASEINTERFACE\n", __func__);
		ret = proc_releaseपूर्णांकerface(ps, p);
		अवरोध;

	हाल USBDEVFS_IOCTL:
		snoop(&dev->dev, "%s: IOCTL\n", __func__);
		ret = proc_ioctl_शेष(ps, p);
		अवरोध;

	हाल USBDEVFS_CLAIM_PORT:
		snoop(&dev->dev, "%s: CLAIM_PORT\n", __func__);
		ret = proc_claim_port(ps, p);
		अवरोध;

	हाल USBDEVFS_RELEASE_PORT:
		snoop(&dev->dev, "%s: RELEASE_PORT\n", __func__);
		ret = proc_release_port(ps, p);
		अवरोध;
	हाल USBDEVFS_GET_CAPABILITIES:
		ret = proc_get_capabilities(ps, p);
		अवरोध;
	हाल USBDEVFS_DISCONNECT_CLAIM:
		ret = proc_disconnect_claim(ps, p);
		अवरोध;
	हाल USBDEVFS_ALLOC_STREAMS:
		ret = proc_alloc_streams(ps, p);
		अवरोध;
	हाल USBDEVFS_FREE_STREAMS:
		ret = proc_मुक्त_streams(ps, p);
		अवरोध;
	हाल USBDEVFS_DROP_PRIVILEGES:
		ret = proc_drop_privileges(ps, p);
		अवरोध;
	हाल USBDEVFS_GET_SPEED:
		ret = ps->dev->speed;
		अवरोध;
	हाल USBDEVFS_FORBID_SUSPEND:
		ret = proc_क्रमbid_suspend(ps);
		अवरोध;
	हाल USBDEVFS_ALLOW_SUSPEND:
		ret = proc_allow_suspend(ps);
		अवरोध;
	हाल USBDEVFS_WAIT_FOR_RESUME:
		ret = proc_रुको_क्रम_resume(ps);
		अवरोध;
	पूर्ण

	/* Handle variable-length commands */
	चयन (cmd & ~IOCSIZE_MASK) अणु
	हाल USBDEVFS_CONNINFO_EX(0):
		ret = proc_conninfo_ex(ps, p, _IOC_SIZE(cmd));
		अवरोध;
	पूर्ण

 करोne:
	usb_unlock_device(dev);
	अगर (ret >= 0)
		inode->i_aसमय = current_समय(inode);
	वापस ret;
पूर्ण

अटल दीर्घ usbdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	ret = usbdev_करो_ioctl(file, cmd, (व्योम __user *)arg);

	वापस ret;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t usbdev_poll(काष्ठा file *file,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा usb_dev_state *ps = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &ps->रुको, रुको);
	अगर (file->f_mode & FMODE_WRITE && !list_empty(&ps->async_completed))
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (!connected(ps))
		mask |= EPOLLHUP;
	अगर (list_empty(&ps->list))
		mask |= EPOLLERR;
	वापस mask;
पूर्ण

स्थिर काष्ठा file_operations usbdev_file_operations = अणु
	.owner =	  THIS_MODULE,
	.llseek =	  no_seek_end_llseek,
	.पढ़ो =		  usbdev_पढ़ो,
	.poll =		  usbdev_poll,
	.unlocked_ioctl = usbdev_ioctl,
	.compat_ioctl =   compat_ptr_ioctl,
	.mmap =           usbdev_mmap,
	.खोलो =		  usbdev_खोलो,
	.release =	  usbdev_release,
पूर्ण;

अटल व्योम usbdev_हटाओ(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_dev_state *ps;

	/* Protect against simultaneous resume */
	mutex_lock(&usbfs_mutex);
	जबतक (!list_empty(&udev->filelist)) अणु
		ps = list_entry(udev->filelist.next, काष्ठा usb_dev_state, list);
		destroy_all_async(ps);
		wake_up_all(&ps->रुको);
		WRITE_ONCE(ps->not_yet_resumed, 0);
		wake_up_all(&ps->रुको_क्रम_resume);
		list_del_init(&ps->list);
		अगर (ps->discsignr)
			समाप्त_pid_usb_asyncio(ps->discsignr, EPIPE, ps->disccontext,
					     ps->disc_pid, ps->cred);
	पूर्ण
	mutex_unlock(&usbfs_mutex);
पूर्ण

अटल पूर्णांक usbdev_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ action, व्योम *dev)
अणु
	चयन (action) अणु
	हाल USB_DEVICE_ADD:
		अवरोध;
	हाल USB_DEVICE_REMOVE:
		usbdev_हटाओ(dev);
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block usbdev_nb = अणु
	.notअगरier_call =	usbdev_notअगरy,
पूर्ण;

अटल काष्ठा cdev usb_device_cdev;

पूर्णांक __init usb_devio_init(व्योम)
अणु
	पूर्णांक retval;

	retval = रेजिस्टर_chrdev_region(USB_DEVICE_DEV, USB_DEVICE_MAX,
					"usb_device");
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "Unable to register minors for usb_device\n");
		जाओ out;
	पूर्ण
	cdev_init(&usb_device_cdev, &usbdev_file_operations);
	retval = cdev_add(&usb_device_cdev, USB_DEVICE_DEV, USB_DEVICE_MAX);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "Unable to get usb_device major %d\n",
		       USB_DEVICE_MAJOR);
		जाओ error_cdev;
	पूर्ण
	usb_रेजिस्टर_notअगरy(&usbdev_nb);
out:
	वापस retval;

error_cdev:
	unरेजिस्टर_chrdev_region(USB_DEVICE_DEV, USB_DEVICE_MAX);
	जाओ out;
पूर्ण

व्योम usb_devio_cleanup(व्योम)
अणु
	usb_unरेजिस्टर_notअगरy(&usbdev_nb);
	cdev_del(&usb_device_cdev);
	unरेजिस्टर_chrdev_region(USB_DEVICE_DEV, USB_DEVICE_MAX);
पूर्ण
