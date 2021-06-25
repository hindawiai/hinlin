<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <misc/cxl.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmu_context.h>

#समावेश "cxl.h"

/*
 * Since we want to track memory mappings to be able to क्रमce-unmap
 * when the AFU is no दीर्घer reachable, we need an inode. For devices
 * खोलोed through the cxl user API, this is not a problem, but a
 * userland process can also get a cxl fd through the cxl_get_fd()
 * API, which is used by the cxlflash driver.
 *
 * Thereक्रमe we implement our own simple pseuकरो-fileप्रणाली and inode
 * allocator. We करोn't use the anonymous inode, as we need the
 * meta-data associated with it (address_space) and it is shared by
 * other drivers/processes, so it could lead to cxl unmapping VMAs
 * from अक्रमom processes.
 */

#घोषणा CXL_PSEUDO_FS_MAGIC	0x1697697f

अटल पूर्णांक cxl_fs_cnt;
अटल काष्ठा vfsmount *cxl_vfs_mount;

अटल पूर्णांक cxl_fs_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, CXL_PSEUDO_FS_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type cxl_fs_type = अणु
	.name		= "cxl",
	.owner		= THIS_MODULE,
	.init_fs_context = cxl_fs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;


व्योम cxl_release_mapping(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->kernelapi && ctx->mapping)
		simple_release_fs(&cxl_vfs_mount, &cxl_fs_cnt);
पूर्ण

अटल काष्ठा file *cxl_getfile(स्थिर अक्षर *name,
				स्थिर काष्ठा file_operations *fops,
				व्योम *priv, पूर्णांक flags)
अणु
	काष्ठा file *file;
	काष्ठा inode *inode;
	पूर्णांक rc;

	/* strongly inspired by anon_inode_getfile() */

	अगर (fops->owner && !try_module_get(fops->owner))
		वापस ERR_PTR(-ENOENT);

	rc = simple_pin_fs(&cxl_fs_type, &cxl_vfs_mount, &cxl_fs_cnt);
	अगर (rc < 0) अणु
		pr_err("Cannot mount cxl pseudo filesystem: %d\n", rc);
		file = ERR_PTR(rc);
		जाओ err_module;
	पूर्ण

	inode = alloc_anon_inode(cxl_vfs_mount->mnt_sb);
	अगर (IS_ERR(inode)) अणु
		file = ERR_CAST(inode);
		जाओ err_fs;
	पूर्ण

	file = alloc_file_pseuकरो(inode, cxl_vfs_mount, name,
				 flags & (O_ACCMODE | O_NONBLOCK), fops);
	अगर (IS_ERR(file))
		जाओ err_inode;

	file->निजी_data = priv;

	वापस file;

err_inode:
	iput(inode);
err_fs:
	simple_release_fs(&cxl_vfs_mount, &cxl_fs_cnt);
err_module:
	module_put(fops->owner);
	वापस file;
पूर्ण

काष्ठा cxl_context *cxl_dev_context_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा cxl_afu *afu;
	काष्ठा cxl_context  *ctx;
	पूर्णांक rc;

	afu = cxl_pci_to_afu(dev);
	अगर (IS_ERR(afu))
		वापस ERR_CAST(afu);

	ctx = cxl_context_alloc();
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->kernelapi = true;

	/* Make it a slave context.  We can promote it later? */
	rc = cxl_context_init(ctx, afu, false);
	अगर (rc)
		जाओ err_ctx;

	वापस ctx;

err_ctx:
	kमुक्त(ctx);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_dev_context_init);

काष्ठा cxl_context *cxl_get_context(काष्ठा pci_dev *dev)
अणु
	वापस dev->dev.archdata.cxl_ctx;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_get_context);

पूर्णांक cxl_release_context(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->status >= STARTED)
		वापस -EBUSY;

	cxl_context_मुक्त(ctx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_release_context);

अटल irq_hw_number_t cxl_find_afu_irq(काष्ठा cxl_context *ctx, पूर्णांक num)
अणु
	__u16 range;
	पूर्णांक r;

	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		range = ctx->irqs.range[r];
		अगर (num < range) अणु
			वापस ctx->irqs.offset[r] + num;
		पूर्ण
		num -= range;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक cxl_set_priv(काष्ठा cxl_context *ctx, व्योम *priv)
अणु
	अगर (!ctx)
		वापस -EINVAL;

	ctx->priv = priv;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_set_priv);

व्योम *cxl_get_priv(काष्ठा cxl_context *ctx)
अणु
	अगर (!ctx)
		वापस ERR_PTR(-EINVAL);

	वापस ctx->priv;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_get_priv);

पूर्णांक cxl_allocate_afu_irqs(काष्ठा cxl_context *ctx, पूर्णांक num)
अणु
	पूर्णांक res;
	irq_hw_number_t hwirq;

	अगर (num == 0)
		num = ctx->afu->pp_irqs;
	res = afu_allocate_irqs(ctx, num);
	अगर (res)
		वापस res;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE)) अणु
		/* In a guest, the PSL पूर्णांकerrupt is not multiplexed. It was
		 * allocated above, and we need to set its handler
		 */
		hwirq = cxl_find_afu_irq(ctx, 0);
		अगर (hwirq)
			cxl_map_irq(ctx->afu->adapter, hwirq, cxl_ops->psl_पूर्णांकerrupt, ctx, "psl");
	पूर्ण

	अगर (ctx->status == STARTED) अणु
		अगर (cxl_ops->update_ivtes)
			cxl_ops->update_ivtes(ctx);
		अन्यथा WARN(1, "BUG: cxl_allocate_afu_irqs must be called prior to starting the context on this platform\n");
	पूर्ण

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_allocate_afu_irqs);

व्योम cxl_मुक्त_afu_irqs(काष्ठा cxl_context *ctx)
अणु
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक virq;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE)) अणु
		hwirq = cxl_find_afu_irq(ctx, 0);
		अगर (hwirq) अणु
			virq = irq_find_mapping(शून्य, hwirq);
			अगर (virq)
				cxl_unmap_irq(virq, ctx);
		पूर्ण
	पूर्ण
	afu_irq_name_मुक्त(ctx);
	cxl_ops->release_irq_ranges(&ctx->irqs, ctx->afu->adapter);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_मुक्त_afu_irqs);

पूर्णांक cxl_map_afu_irq(काष्ठा cxl_context *ctx, पूर्णांक num,
		    irq_handler_t handler, व्योम *cookie, अक्षर *name)
अणु
	irq_hw_number_t hwirq;

	/*
	 * Find पूर्णांकerrupt we are to रेजिस्टर.
	 */
	hwirq = cxl_find_afu_irq(ctx, num);
	अगर (!hwirq)
		वापस -ENOENT;

	वापस cxl_map_irq(ctx->afu->adapter, hwirq, handler, cookie, name);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_map_afu_irq);

व्योम cxl_unmap_afu_irq(काष्ठा cxl_context *ctx, पूर्णांक num, व्योम *cookie)
अणु
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक virq;

	hwirq = cxl_find_afu_irq(ctx, num);
	अगर (!hwirq)
		वापस;

	virq = irq_find_mapping(शून्य, hwirq);
	अगर (virq)
		cxl_unmap_irq(virq, cookie);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_unmap_afu_irq);

/*
 * Start a context
 * Code here similar to afu_ioctl_start_work().
 */
पूर्णांक cxl_start_context(काष्ठा cxl_context *ctx, u64 wed,
		      काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक rc = 0;
	bool kernel = true;

	pr_devel("%s: pe: %i\n", __func__, ctx->pe);

	mutex_lock(&ctx->status_mutex);
	अगर (ctx->status == STARTED)
		जाओ out; /* alपढ़ोy started */

	/*
	 * Increment the mapped context count क्रम adapter. This also checks
	 * अगर adapter_context_lock is taken.
	 */
	rc = cxl_adapter_context_get(ctx->afu->adapter);
	अगर (rc)
		जाओ out;

	अगर (task) अणु
		ctx->pid = get_task_pid(task, PIDTYPE_PID);
		kernel = false;

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
	पूर्ण

	/*
	 * Increment driver use count. Enables global TLBIs क्रम hash
	 * and callbacks to handle the segment table
	 */
	cxl_ctx_get();

	/* See the comment in afu_ioctl_start_work() */
	smp_mb();

	अगर ((rc = cxl_ops->attach_process(ctx, kernel, wed, 0))) अणु
		put_pid(ctx->pid);
		ctx->pid = शून्य;
		cxl_adapter_context_put(ctx->afu->adapter);
		cxl_ctx_put();
		अगर (task) अणु
			cxl_context_mm_count_put(ctx);
			अगर (ctx->mm)
				mm_context_हटाओ_copro(ctx->mm);
		पूर्ण
		जाओ out;
	पूर्ण

	ctx->status = STARTED;
out:
	mutex_unlock(&ctx->status_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_start_context);

पूर्णांक cxl_process_element(काष्ठा cxl_context *ctx)
अणु
	वापस ctx->बाह्यal_pe;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_process_element);

/* Stop a context.  Returns 0 on success, otherwise -Errno */
पूर्णांक cxl_stop_context(काष्ठा cxl_context *ctx)
अणु
	वापस __detach_context(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_stop_context);

व्योम cxl_set_master(काष्ठा cxl_context *ctx)
अणु
	ctx->master = true;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_set_master);

/* wrappers around afu_* file ops which are EXPORTED */
पूर्णांक cxl_fd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस afu_खोलो(inode, file);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_खोलो);
पूर्णांक cxl_fd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस afu_release(inode, file);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_release);
दीर्घ cxl_fd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस afu_ioctl(file, cmd, arg);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_ioctl);
पूर्णांक cxl_fd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm)
अणु
	वापस afu_mmap(file, vm);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_mmap);
__poll_t cxl_fd_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll)
अणु
	वापस afu_poll(file, poll);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_poll);
sमाप_प्रकार cxl_fd_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *off)
अणु
	वापस afu_पढ़ो(file, buf, count, off);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fd_पढ़ो);

#घोषणा PATCH_FOPS(NAME) अगर (!fops->NAME) fops->NAME = afu_fops.NAME

/* Get a काष्ठा file and fd क्रम a context and attach the ops */
काष्ठा file *cxl_get_fd(काष्ठा cxl_context *ctx, काष्ठा file_operations *fops,
			पूर्णांक *fd)
अणु
	काष्ठा file *file;
	पूर्णांक rc, flags, fdपंचांगp;
	अक्षर *name = शून्य;

	/* only allow one per context */
	अगर (ctx->mapping)
		वापस ERR_PTR(-EEXIST);

	flags = O_RDWR | O_CLOEXEC;

	/* This code is similar to anon_inode_getfd() */
	rc = get_unused_fd_flags(flags);
	अगर (rc < 0)
		वापस ERR_PTR(rc);
	fdपंचांगp = rc;

	/*
	 * Patch the file ops.  Needs to be careful that this is rentrant safe.
	 */
	अगर (fops) अणु
		PATCH_FOPS(खोलो);
		PATCH_FOPS(poll);
		PATCH_FOPS(पढ़ो);
		PATCH_FOPS(release);
		PATCH_FOPS(unlocked_ioctl);
		PATCH_FOPS(compat_ioctl);
		PATCH_FOPS(mmap);
	पूर्ण अन्यथा /* use शेष ops */
		fops = (काष्ठा file_operations *)&afu_fops;

	name = kaप्र_लिखो(GFP_KERNEL, "cxl:%d", ctx->pe);
	file = cxl_getfile(name, fops, ctx, flags);
	kमुक्त(name);
	अगर (IS_ERR(file))
		जाओ err_fd;

	cxl_context_set_mapping(ctx, file->f_mapping);
	*fd = fdपंचांगp;
	वापस file;

err_fd:
	put_unused_fd(fdपंचांगp);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_get_fd);

काष्ठा cxl_context *cxl_fops_get_context(काष्ठा file *file)
अणु
	वापस file->निजी_data;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_fops_get_context);

व्योम cxl_set_driver_ops(काष्ठा cxl_context *ctx,
			काष्ठा cxl_afu_driver_ops *ops)
अणु
	WARN_ON(!ops->fetch_event || !ops->event_delivered);
	atomic_set(&ctx->afu_driver_events, 0);
	ctx->afu_driver_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_set_driver_ops);

व्योम cxl_context_events_pending(काष्ठा cxl_context *ctx,
				अचिन्हित पूर्णांक new_events)
अणु
	atomic_add(new_events, &ctx->afu_driver_events);
	wake_up_all(&ctx->wq);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_context_events_pending);

पूर्णांक cxl_start_work(काष्ठा cxl_context *ctx,
		   काष्ठा cxl_ioctl_start_work *work)
अणु
	पूर्णांक rc;

	/* code taken from afu_ioctl_start_work */
	अगर (!(work->flags & CXL_START_WORK_NUM_IRQS))
		work->num_पूर्णांकerrupts = ctx->afu->pp_irqs;
	अन्यथा अगर ((work->num_पूर्णांकerrupts < ctx->afu->pp_irqs) ||
		 (work->num_पूर्णांकerrupts > ctx->afu->irqs_max)) अणु
		वापस -EINVAL;
	पूर्ण

	rc = afu_रेजिस्टर_irqs(ctx, work->num_पूर्णांकerrupts);
	अगर (rc)
		वापस rc;

	rc = cxl_start_context(ctx, work->work_element_descriptor, current);
	अगर (rc < 0) अणु
		afu_release_irqs(ctx, ctx);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_start_work);

व्योम __iomem *cxl_psa_map(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->status != STARTED)
		वापस शून्य;

	pr_devel("%s: psn_phys%llx size:%llx\n",
		__func__, ctx->psn_phys, ctx->psn_size);
	वापस ioremap(ctx->psn_phys, ctx->psn_size);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_psa_map);

व्योम cxl_psa_unmap(व्योम __iomem *addr)
अणु
	iounmap(addr);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_psa_unmap);

पूर्णांक cxl_afu_reset(काष्ठा cxl_context *ctx)
अणु
	काष्ठा cxl_afu *afu = ctx->afu;
	पूर्णांक rc;

	rc = cxl_ops->afu_reset(afu);
	अगर (rc)
		वापस rc;

	वापस cxl_ops->afu_check_and_enable(afu);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_afu_reset);

व्योम cxl_perst_reloads_same_image(काष्ठा cxl_afu *afu,
				  bool perst_reloads_same_image)
अणु
	afu->adapter->perst_same_image = perst_reloads_same_image;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_perst_reloads_same_image);

sमाप_प्रकार cxl_पढ़ो_adapter_vpd(काष्ठा pci_dev *dev, व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = cxl_pci_to_afu(dev);
	अगर (IS_ERR(afu))
		वापस -ENODEV;

	वापस cxl_ops->पढ़ो_adapter_vpd(afu->adapter, buf, count);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_पढ़ो_adapter_vpd);
