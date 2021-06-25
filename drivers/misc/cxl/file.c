<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/poll.h>
#समावेश <linux/pid.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmu_context.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/copro.h>

#समावेश "cxl.h"
#समावेश "trace.h"

#घोषणा CXL_NUM_MINORS 256 /* Total to reserve */

#घोषणा CXL_AFU_MINOR_D(afu) (CXL_CARD_MINOR(afu->adapter) + 1 + (3 * afu->slice))
#घोषणा CXL_AFU_MINOR_M(afu) (CXL_AFU_MINOR_D(afu) + 1)
#घोषणा CXL_AFU_MINOR_S(afu) (CXL_AFU_MINOR_D(afu) + 2)
#घोषणा CXL_AFU_MKDEV_D(afu) MKDEV(MAJOR(cxl_dev), CXL_AFU_MINOR_D(afu))
#घोषणा CXL_AFU_MKDEV_M(afu) MKDEV(MAJOR(cxl_dev), CXL_AFU_MINOR_M(afu))
#घोषणा CXL_AFU_MKDEV_S(afu) MKDEV(MAJOR(cxl_dev), CXL_AFU_MINOR_S(afu))

#घोषणा CXL_DEVT_AFU(dev) ((MINOR(dev) % CXL_DEV_MINORS - 1) / 3)

#घोषणा CXL_DEVT_IS_CARD(dev) (MINOR(dev) % CXL_DEV_MINORS == 0)

अटल dev_t cxl_dev;

अटल काष्ठा class *cxl_class;

अटल पूर्णांक __afu_खोलो(काष्ठा inode *inode, काष्ठा file *file, bool master)
अणु
	काष्ठा cxl *adapter;
	काष्ठा cxl_afu *afu;
	काष्ठा cxl_context *ctx;
	पूर्णांक adapter_num = CXL_DEVT_ADAPTER(inode->i_rdev);
	पूर्णांक slice = CXL_DEVT_AFU(inode->i_rdev);
	पूर्णांक rc = -ENODEV;

	pr_devel("afu_open afu%i.%i\n", slice, adapter_num);

	अगर (!(adapter = get_cxl_adapter(adapter_num)))
		वापस -ENODEV;

	अगर (slice > adapter->slices)
		जाओ err_put_adapter;

	spin_lock(&adapter->afu_list_lock);
	अगर (!(afu = adapter->afu[slice])) अणु
		spin_unlock(&adapter->afu_list_lock);
		जाओ err_put_adapter;
	पूर्ण

	/*
	 * taking a ref to the afu so that it करोesn't go away
	 * क्रम rest of the function. This ref is released beक्रमe
	 * we वापस.
	 */
	cxl_afu_get(afu);
	spin_unlock(&adapter->afu_list_lock);

	अगर (!afu->current_mode)
		जाओ err_put_afu;

	अगर (!cxl_ops->link_ok(adapter, afu)) अणु
		rc = -EIO;
		जाओ err_put_afu;
	पूर्ण

	अगर (!(ctx = cxl_context_alloc())) अणु
		rc = -ENOMEM;
		जाओ err_put_afu;
	पूर्ण

	rc = cxl_context_init(ctx, afu, master);
	अगर (rc)
		जाओ err_put_afu;

	cxl_context_set_mapping(ctx, inode->i_mapping);

	pr_devel("afu_open pe: %i\n", ctx->pe);
	file->निजी_data = ctx;

	/* indicate success */
	rc = 0;

err_put_afu:
	/* release the ref taken earlier */
	cxl_afu_put(afu);
err_put_adapter:
	put_device(&adapter->dev);
	वापस rc;
पूर्ण

पूर्णांक afu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __afu_खोलो(inode, file, false);
पूर्ण

अटल पूर्णांक afu_master_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __afu_खोलो(inode, file, true);
पूर्ण

पूर्णांक afu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cxl_context *ctx = file->निजी_data;

	pr_devel("%s: closing cxl file descriptor. pe: %i\n",
		 __func__, ctx->pe);
	cxl_context_detach(ctx);


	/*
	 * Delete the context's mapping pointer, unless it's created by the
	 * kernel API, in which हाल leave it so it can be मुक्तd by reclaim_ctx()
	 */
	अगर (!ctx->kernelapi) अणु
		mutex_lock(&ctx->mapping_lock);
		ctx->mapping = शून्य;
		mutex_unlock(&ctx->mapping_lock);
	पूर्ण

	/*
	 * At this this poपूर्णांक all bottom halfs have finished and we should be
	 * getting no more IRQs from the hardware क्रम this context.  Once it's
	 * हटाओd from the IDR (and RCU synchronised) it's safe to मुक्त the
	 * sstp and context.
	 */
	cxl_context_मुक्त(ctx);

	वापस 0;
पूर्ण

अटल दीर्घ afu_ioctl_start_work(काष्ठा cxl_context *ctx,
				 काष्ठा cxl_ioctl_start_work __user *uwork)
अणु
	काष्ठा cxl_ioctl_start_work work;
	u64 amr = 0;
	पूर्णांक rc;

	pr_devel("%s: pe: %i\n", __func__, ctx->pe);

	/* Do this outside the status_mutex to aव्योम a circular dependency with
	 * the locking in cxl_mmap_fault() */
	अगर (copy_from_user(&work, uwork, माप(work)))
		वापस -EFAULT;

	mutex_lock(&ctx->status_mutex);
	अगर (ctx->status != OPENED) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * अगर any of the reserved fields are set or any of the unused
	 * flags are set it's invalid
	 */
	अगर (work.reserved1 || work.reserved2 || work.reserved3 ||
	    work.reserved4 || work.reserved5 ||
	    (work.flags & ~CXL_START_WORK_ALL)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!(work.flags & CXL_START_WORK_NUM_IRQS))
		work.num_पूर्णांकerrupts = ctx->afu->pp_irqs;
	अन्यथा अगर ((work.num_पूर्णांकerrupts < ctx->afu->pp_irqs) ||
		 (work.num_पूर्णांकerrupts > ctx->afu->irqs_max)) अणु
		rc =  -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((rc = afu_रेजिस्टर_irqs(ctx, work.num_पूर्णांकerrupts)))
		जाओ out;

	अगर (work.flags & CXL_START_WORK_AMR)
		amr = work.amr & mfspr(SPRN_UAMOR);

	अगर (work.flags & CXL_START_WORK_TID)
		ctx->assign_tidr = true;

	ctx->mmio_err_ff = !!(work.flags & CXL_START_WORK_ERR_FF);

	/*
	 * Increment the mapped context count क्रम adapter. This also checks
	 * अगर adapter_context_lock is taken.
	 */
	rc = cxl_adapter_context_get(ctx->afu->adapter);
	अगर (rc) अणु
		afu_release_irqs(ctx, ctx);
		जाओ out;
	पूर्ण

	/*
	 * We grab the PID here and not in the file खोलो to allow क्रम the हाल
	 * where a process (master, some daemon, etc) has खोलोed the अक्षरdev on
	 * behalf of another process, so the AFU's mm माला_लो bound to the process
	 * that perक्रमms this ioctl and not the process that खोलोed the file.
	 * Also we grab the PID of the group leader so that अगर the task that
	 * has perक्रमmed the attach operation निकासs the mm context of the
	 * process is still accessible.
	 */
	ctx->pid = get_task_pid(current, PIDTYPE_PID);

	/* acquire a reference to the task's mm */
	ctx->mm = get_task_mm(current);

	/* ensure this mm_काष्ठा can't be मुक्तd */
	cxl_context_mm_count_get(ctx);

	अगर (ctx->mm) अणु
		/* decrement the use count from above */
		mmput(ctx->mm);
		/* make TLBIs क्रम this context global */
		mm_context_add_copro(ctx->mm);
	पूर्ण

	/*
	 * Increment driver use count. Enables global TLBIs क्रम hash
	 * and callbacks to handle the segment table
	 */
	cxl_ctx_get();

	/*
	 * A barrier is needed to make sure all TLBIs are global
	 * beक्रमe we attach and the context starts being used by the
	 * adapter.
	 *
	 * Needed after mm_context_add_copro() क्रम radix and
	 * cxl_ctx_get() क्रम hash/p8.
	 *
	 * The barrier should really be mb(), since it involves a
	 * device. However, it's only useful when we have local
	 * vs. global TLBIs, i.e SMP=y. So keep smp_mb().
	 */
	smp_mb();

	trace_cxl_attach(ctx, work.work_element_descriptor, work.num_पूर्णांकerrupts, amr);

	अगर ((rc = cxl_ops->attach_process(ctx, false, work.work_element_descriptor,
							amr))) अणु
		afu_release_irqs(ctx, ctx);
		cxl_adapter_context_put(ctx->afu->adapter);
		put_pid(ctx->pid);
		ctx->pid = शून्य;
		cxl_ctx_put();
		cxl_context_mm_count_put(ctx);
		अगर (ctx->mm)
			mm_context_हटाओ_copro(ctx->mm);
		जाओ out;
	पूर्ण

	rc = 0;
	अगर (work.flags & CXL_START_WORK_TID) अणु
		work.tid = ctx->tidr;
		अगर (copy_to_user(uwork, &work, माप(work)))
			rc = -EFAULT;
	पूर्ण

	ctx->status = STARTED;

out:
	mutex_unlock(&ctx->status_mutex);
	वापस rc;
पूर्ण

अटल दीर्घ afu_ioctl_process_element(काष्ठा cxl_context *ctx,
				      पूर्णांक __user *upe)
अणु
	pr_devel("%s: pe: %i\n", __func__, ctx->pe);

	अगर (copy_to_user(upe, &ctx->बाह्यal_pe, माप(__u32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ afu_ioctl_get_afu_id(काष्ठा cxl_context *ctx,
				 काष्ठा cxl_afu_id __user *upafuid)
अणु
	काष्ठा cxl_afu_id afuid = अणु 0 पूर्ण;

	afuid.card_id = ctx->afu->adapter->adapter_num;
	afuid.afu_offset = ctx->afu->slice;
	afuid.afu_mode = ctx->afu->current_mode;

	/* set the flag bit in हाल the afu is a slave */
	अगर (ctx->afu->current_mode == CXL_MODE_सूचीECTED && !ctx->master)
		afuid.flags |= CXL_AFUID_FLAG_SLAVE;

	अगर (copy_to_user(upafuid, &afuid, माप(afuid)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

दीर्घ afu_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cxl_context *ctx = file->निजी_data;

	अगर (ctx->status == CLOSED)
		वापस -EIO;

	अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		वापस -EIO;

	pr_devel("afu_ioctl\n");
	चयन (cmd) अणु
	हाल CXL_IOCTL_START_WORK:
		वापस afu_ioctl_start_work(ctx, (काष्ठा cxl_ioctl_start_work __user *)arg);
	हाल CXL_IOCTL_GET_PROCESS_ELEMENT:
		वापस afu_ioctl_process_element(ctx, (__u32 __user *)arg);
	हाल CXL_IOCTL_GET_AFU_ID:
		वापस afu_ioctl_get_afu_id(ctx, (काष्ठा cxl_afu_id __user *)
					    arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल दीर्घ afu_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	वापस afu_ioctl(file, cmd, arg);
पूर्ण

पूर्णांक afu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm)
अणु
	काष्ठा cxl_context *ctx = file->निजी_data;

	/* AFU must be started beक्रमe we can MMIO */
	अगर (ctx->status != STARTED)
		वापस -EIO;

	अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		वापस -EIO;

	वापस cxl_context_iomap(ctx, vm);
पूर्ण

अटल अंतरभूत bool ctx_event_pending(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->pending_irq || ctx->pending_fault || ctx->pending_afu_err)
		वापस true;

	अगर (ctx->afu_driver_ops && atomic_पढ़ो(&ctx->afu_driver_events))
		वापस true;

	वापस false;
पूर्ण

__poll_t afu_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा cxl_context *ctx = file->निजी_data;
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;


	poll_रुको(file, &ctx->wq, poll);

	pr_devel("afu_poll wait done pe: %i\n", ctx->pe);

	spin_lock_irqsave(&ctx->lock, flags);
	अगर (ctx_event_pending(ctx))
		mask |= EPOLLIN | EPOLLRDNORM;
	अन्यथा अगर (ctx->status == CLOSED)
		/* Only error on बंदd when there are no futher events pending
		 */
		mask |= EPOLLERR;
	spin_unlock_irqrestore(&ctx->lock, flags);

	pr_devel("afu_poll pe: %i returning %#x\n", ctx->pe, mask);

	वापस mask;
पूर्ण

अटल sमाप_प्रकार afu_driver_event_copy(काष्ठा cxl_context *ctx,
				     अक्षर __user *buf,
				     काष्ठा cxl_event *event,
				     काष्ठा cxl_event_afu_driver_reserved *pl)
अणु
	/* Check event */
	अगर (!pl) अणु
		ctx->afu_driver_ops->event_delivered(ctx, pl, -EINVAL);
		वापस -EFAULT;
	पूर्ण

	/* Check event size */
	event->header.size += pl->data_size;
	अगर (event->header.size > CXL_READ_MIN_SIZE) अणु
		ctx->afu_driver_ops->event_delivered(ctx, pl, -EINVAL);
		वापस -EFAULT;
	पूर्ण

	/* Copy event header */
	अगर (copy_to_user(buf, event, माप(काष्ठा cxl_event_header))) अणु
		ctx->afu_driver_ops->event_delivered(ctx, pl, -EFAULT);
		वापस -EFAULT;
	पूर्ण

	/* Copy event data */
	buf += माप(काष्ठा cxl_event_header);
	अगर (copy_to_user(buf, &pl->data, pl->data_size)) अणु
		ctx->afu_driver_ops->event_delivered(ctx, pl, -EFAULT);
		वापस -EFAULT;
	पूर्ण

	ctx->afu_driver_ops->event_delivered(ctx, pl, 0); /* Success */
	वापस event->header.size;
पूर्ण

sमाप_प्रकार afu_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *off)
अणु
	काष्ठा cxl_context *ctx = file->निजी_data;
	काष्ठा cxl_event_afu_driver_reserved *pl = शून्य;
	काष्ठा cxl_event event;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	DEFINE_WAIT(रुको);

	अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		वापस -EIO;

	अगर (count < CXL_READ_MIN_SIZE)
		वापस -EINVAL;

	spin_lock_irqsave(&ctx->lock, flags);

	क्रम (;;) अणु
		prepare_to_रुको(&ctx->wq, &रुको, TASK_INTERRUPTIBLE);
		अगर (ctx_event_pending(ctx) || (ctx->status == CLOSED))
			अवरोध;

		अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu)) अणु
			rc = -EIO;
			जाओ out;
		पूर्ण

		अगर (file->f_flags & O_NONBLOCK) अणु
			rc = -EAGAIN;
			जाओ out;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			rc = -ERESTARTSYS;
			जाओ out;
		पूर्ण

		spin_unlock_irqrestore(&ctx->lock, flags);
		pr_devel("afu_read going to sleep...\n");
		schedule();
		pr_devel("afu_read woken up\n");
		spin_lock_irqsave(&ctx->lock, flags);
	पूर्ण

	finish_रुको(&ctx->wq, &रुको);

	स_रखो(&event, 0, माप(event));
	event.header.process_element = ctx->pe;
	event.header.size = माप(काष्ठा cxl_event_header);
	अगर (ctx->afu_driver_ops && atomic_पढ़ो(&ctx->afu_driver_events)) अणु
		pr_devel("afu_read delivering AFU driver specific event\n");
		pl = ctx->afu_driver_ops->fetch_event(ctx);
		atomic_dec(&ctx->afu_driver_events);
		event.header.type = CXL_EVENT_AFU_DRIVER;
	पूर्ण अन्यथा अगर (ctx->pending_irq) अणु
		pr_devel("afu_read delivering AFU interrupt\n");
		event.header.size += माप(काष्ठा cxl_event_afu_पूर्णांकerrupt);
		event.header.type = CXL_EVENT_AFU_INTERRUPT;
		event.irq.irq = find_first_bit(ctx->irq_biपंचांगap, ctx->irq_count) + 1;
		clear_bit(event.irq.irq - 1, ctx->irq_biपंचांगap);
		अगर (biपंचांगap_empty(ctx->irq_biपंचांगap, ctx->irq_count))
			ctx->pending_irq = false;
	पूर्ण अन्यथा अगर (ctx->pending_fault) अणु
		pr_devel("afu_read delivering data storage fault\n");
		event.header.size += माप(काष्ठा cxl_event_data_storage);
		event.header.type = CXL_EVENT_DATA_STORAGE;
		event.fault.addr = ctx->fault_addr;
		event.fault.dsisr = ctx->fault_dsisr;
		ctx->pending_fault = false;
	पूर्ण अन्यथा अगर (ctx->pending_afu_err) अणु
		pr_devel("afu_read delivering afu error\n");
		event.header.size += माप(काष्ठा cxl_event_afu_error);
		event.header.type = CXL_EVENT_AFU_ERROR;
		event.afu_error.error = ctx->afu_err;
		ctx->pending_afu_err = false;
	पूर्ण अन्यथा अगर (ctx->status == CLOSED) अणु
		pr_devel("afu_read fatal error\n");
		spin_unlock_irqrestore(&ctx->lock, flags);
		वापस -EIO;
	पूर्ण अन्यथा
		WARN(1, "afu_read must be buggy\n");

	spin_unlock_irqrestore(&ctx->lock, flags);

	अगर (event.header.type == CXL_EVENT_AFU_DRIVER)
		वापस afu_driver_event_copy(ctx, buf, &event, pl);

	अगर (copy_to_user(buf, &event, event.header.size))
		वापस -EFAULT;
	वापस event.header.size;

out:
	finish_रुको(&ctx->wq, &रुको);
	spin_unlock_irqrestore(&ctx->lock, flags);
	वापस rc;
पूर्ण

/* 
 * Note: अगर this is updated, we need to update api.c to patch the new ones in
 * too
 */
स्थिर काष्ठा file_operations afu_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = afu_खोलो,
	.poll		= afu_poll,
	.पढ़ो		= afu_पढ़ो,
	.release        = afu_release,
	.unlocked_ioctl = afu_ioctl,
	.compat_ioctl   = afu_compat_ioctl,
	.mmap           = afu_mmap,
पूर्ण;

अटल स्थिर काष्ठा file_operations afu_master_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = afu_master_खोलो,
	.poll		= afu_poll,
	.पढ़ो		= afu_पढ़ो,
	.release        = afu_release,
	.unlocked_ioctl = afu_ioctl,
	.compat_ioctl   = afu_compat_ioctl,
	.mmap           = afu_mmap,
पूर्ण;


अटल अक्षर *cxl_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (cpu_has_feature(CPU_FTR_HVMODE) &&
	    CXL_DEVT_IS_CARD(dev->devt)) अणु
		/*
		 * These minor numbers will eventually be used to program the
		 * PSL and AFUs once we have dynamic reprogramming support
		 */
		वापस शून्य;
	पूर्ण
	वापस kaप्र_लिखो(GFP_KERNEL, "cxl/%s", dev_name(dev));
पूर्ण

बाह्य काष्ठा class *cxl_class;

अटल पूर्णांक cxl_add_अक्षरdev(काष्ठा cxl_afu *afu, dev_t devt, काष्ठा cdev *cdev,
			   काष्ठा device **अक्षरdev, अक्षर *postfix, अक्षर *desc,
			   स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा device *dev;
	पूर्णांक rc;

	cdev_init(cdev, fops);
	अगर ((rc = cdev_add(cdev, devt, 1))) अणु
		dev_err(&afu->dev, "Unable to add %s chardev: %i\n", desc, rc);
		वापस rc;
	पूर्ण

	dev = device_create(cxl_class, &afu->dev, devt, afu,
			"afu%i.%i%s", afu->adapter->adapter_num, afu->slice, postfix);
	अगर (IS_ERR(dev)) अणु
		dev_err(&afu->dev, "Unable to create %s chardev in sysfs: %i\n", desc, rc);
		rc = PTR_ERR(dev);
		जाओ err;
	पूर्ण

	*अक्षरdev = dev;

	वापस 0;
err:
	cdev_del(cdev);
	वापस rc;
पूर्ण

पूर्णांक cxl_अक्षरdev_d_afu_add(काष्ठा cxl_afu *afu)
अणु
	वापस cxl_add_अक्षरdev(afu, CXL_AFU_MKDEV_D(afu), &afu->afu_cdev_d,
			       &afu->अक्षरdev_d, "d", "dedicated",
			       &afu_master_fops); /* Uses master fops */
पूर्ण

पूर्णांक cxl_अक्षरdev_m_afu_add(काष्ठा cxl_afu *afu)
अणु
	वापस cxl_add_अक्षरdev(afu, CXL_AFU_MKDEV_M(afu), &afu->afu_cdev_m,
			       &afu->अक्षरdev_m, "m", "master",
			       &afu_master_fops);
पूर्ण

पूर्णांक cxl_अक्षरdev_s_afu_add(काष्ठा cxl_afu *afu)
अणु
	वापस cxl_add_अक्षरdev(afu, CXL_AFU_MKDEV_S(afu), &afu->afu_cdev_s,
			       &afu->अक्षरdev_s, "s", "shared",
			       &afu_fops);
पूर्ण

व्योम cxl_अक्षरdev_afu_हटाओ(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->अक्षरdev_d) अणु
		cdev_del(&afu->afu_cdev_d);
		device_unरेजिस्टर(afu->अक्षरdev_d);
		afu->अक्षरdev_d = शून्य;
	पूर्ण
	अगर (afu->अक्षरdev_m) अणु
		cdev_del(&afu->afu_cdev_m);
		device_unरेजिस्टर(afu->अक्षरdev_m);
		afu->अक्षरdev_m = शून्य;
	पूर्ण
	अगर (afu->अक्षरdev_s) अणु
		cdev_del(&afu->afu_cdev_s);
		device_unरेजिस्टर(afu->अक्षरdev_s);
		afu->अक्षरdev_s = शून्य;
	पूर्ण
पूर्ण

पूर्णांक cxl_रेजिस्टर_afu(काष्ठा cxl_afu *afu)
अणु
	afu->dev.class = cxl_class;

	वापस device_रेजिस्टर(&afu->dev);
पूर्ण

पूर्णांक cxl_रेजिस्टर_adapter(काष्ठा cxl *adapter)
अणु
	adapter->dev.class = cxl_class;

	/*
	 * Future: When we support dynamically reprogramming the PSL & AFU we
	 * will expose the पूर्णांकerface to करो that via a अक्षरdev:
	 * adapter->dev.devt = CXL_CARD_MKDEV(adapter);
	 */

	वापस device_रेजिस्टर(&adapter->dev);
पूर्ण

dev_t cxl_get_dev(व्योम)
अणु
	वापस cxl_dev;
पूर्ण

पूर्णांक __init cxl_file_init(व्योम)
अणु
	पूर्णांक rc;

	/*
	 * If these change we really need to update API.  Either change some
	 * flags or update API version number CXL_API_VERSION.
	 */
	BUILD_BUG_ON(CXL_API_VERSION != 3);
	BUILD_BUG_ON(माप(काष्ठा cxl_ioctl_start_work) != 64);
	BUILD_BUG_ON(माप(काष्ठा cxl_event_header) != 8);
	BUILD_BUG_ON(माप(काष्ठा cxl_event_afu_पूर्णांकerrupt) != 8);
	BUILD_BUG_ON(माप(काष्ठा cxl_event_data_storage) != 32);
	BUILD_BUG_ON(माप(काष्ठा cxl_event_afu_error) != 16);

	अगर ((rc = alloc_chrdev_region(&cxl_dev, 0, CXL_NUM_MINORS, "cxl"))) अणु
		pr_err("Unable to allocate CXL major number: %i\n", rc);
		वापस rc;
	पूर्ण

	pr_devel("CXL device allocated, MAJOR %i\n", MAJOR(cxl_dev));

	cxl_class = class_create(THIS_MODULE, "cxl");
	अगर (IS_ERR(cxl_class)) अणु
		pr_err("Unable to create CXL class\n");
		rc = PTR_ERR(cxl_class);
		जाओ err;
	पूर्ण
	cxl_class->devnode = cxl_devnode;

	वापस 0;

err:
	unरेजिस्टर_chrdev_region(cxl_dev, CXL_NUM_MINORS);
	वापस rc;
पूर्ण

व्योम cxl_file_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(cxl_dev, CXL_NUM_MINORS);
	class_destroy(cxl_class);
पूर्ण
