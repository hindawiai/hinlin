<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/eventfd.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/misc/ocxl.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "ocxl_internal.h"


#घोषणा OCXL_NUM_MINORS 256 /* Total to reserve */

अटल dev_t ocxl_dev;
अटल काष्ठा class *ocxl_class;
अटल DEFINE_MUTEX(minors_idr_lock);
अटल काष्ठा idr minors_idr;

अटल काष्ठा ocxl_file_info *find_and_get_file_info(dev_t devno)
अणु
	काष्ठा ocxl_file_info *info;

	mutex_lock(&minors_idr_lock);
	info = idr_find(&minors_idr, MINOR(devno));
	अगर (info)
		get_device(&info->dev);
	mutex_unlock(&minors_idr_lock);
	वापस info;
पूर्ण

अटल पूर्णांक allocate_minor(काष्ठा ocxl_file_info *info)
अणु
	पूर्णांक minor;

	mutex_lock(&minors_idr_lock);
	minor = idr_alloc(&minors_idr, info, 0, OCXL_NUM_MINORS, GFP_KERNEL);
	mutex_unlock(&minors_idr_lock);
	वापस minor;
पूर्ण

अटल व्योम मुक्त_minor(काष्ठा ocxl_file_info *info)
अणु
	mutex_lock(&minors_idr_lock);
	idr_हटाओ(&minors_idr, MINOR(info->dev.devt));
	mutex_unlock(&minors_idr_lock);
पूर्ण

अटल पूर्णांक afu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocxl_file_info *info;
	काष्ठा ocxl_context *ctx;
	पूर्णांक rc;

	pr_debug("%s for device %x\n", __func__, inode->i_rdev);

	info = find_and_get_file_info(inode->i_rdev);
	अगर (!info)
		वापस -ENODEV;

	rc = ocxl_context_alloc(&ctx, info->afu, inode->i_mapping);
	अगर (rc) अणु
		put_device(&info->dev);
		वापस rc;
	पूर्ण
	put_device(&info->dev);
	file->निजी_data = ctx;
	वापस 0;
पूर्ण

अटल दीर्घ afu_ioctl_attach(काष्ठा ocxl_context *ctx,
			काष्ठा ocxl_ioctl_attach __user *uarg)
अणु
	काष्ठा ocxl_ioctl_attach arg;
	u64 amr = 0;
	पूर्णांक rc;

	pr_debug("%s for context %d\n", __func__, ctx->pasid);

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	/* Make sure reserved fields are not set क्रम क्रमward compatibility */
	अगर (arg.reserved1 || arg.reserved2 || arg.reserved3)
		वापस -EINVAL;

	amr = arg.amr & mfspr(SPRN_UAMOR);
	rc = ocxl_context_attach(ctx, amr, current->mm);
	वापस rc;
पूर्ण

अटल दीर्घ afu_ioctl_get_metadata(काष्ठा ocxl_context *ctx,
		काष्ठा ocxl_ioctl_metadata __user *uarg)
अणु
	काष्ठा ocxl_ioctl_metadata arg;

	स_रखो(&arg, 0, माप(arg));

	arg.version = 0;

	arg.afu_version_major = ctx->afu->config.version_major;
	arg.afu_version_minor = ctx->afu->config.version_minor;
	arg.pasid = ctx->pasid;
	arg.pp_mmio_size = ctx->afu->config.pp_mmio_stride;
	arg.global_mmio_size = ctx->afu->config.global_mmio_size;

	अगर (copy_to_user(uarg, &arg, माप(arg)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल दीर्घ afu_ioctl_enable_p9_रुको(काष्ठा ocxl_context *ctx,
		काष्ठा ocxl_ioctl_p9_रुको __user *uarg)
अणु
	काष्ठा ocxl_ioctl_p9_रुको arg;

	स_रखो(&arg, 0, माप(arg));

	अगर (cpu_has_feature(CPU_FTR_P9_TIDR)) अणु
		क्रमागत ocxl_context_status status;

		// Locks both status & tidr
		mutex_lock(&ctx->status_mutex);
		अगर (!ctx->tidr) अणु
			अगर (set_thपढ़ो_tidr(current)) अणु
				mutex_unlock(&ctx->status_mutex);
				वापस -ENOENT;
			पूर्ण

			ctx->tidr = current->thपढ़ो.tidr;
		पूर्ण

		status = ctx->status;
		mutex_unlock(&ctx->status_mutex);

		अगर (status == ATTACHED) अणु
			पूर्णांक rc = ocxl_link_update_pe(ctx->afu->fn->link,
				ctx->pasid, ctx->tidr);

			अगर (rc)
				वापस rc;
		पूर्ण

		arg.thपढ़ो_id = ctx->tidr;
	पूर्ण अन्यथा
		वापस -ENOENT;

	अगर (copy_to_user(uarg, &arg, माप(arg)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर


अटल दीर्घ afu_ioctl_get_features(काष्ठा ocxl_context *ctx,
		काष्ठा ocxl_ioctl_features __user *uarg)
अणु
	काष्ठा ocxl_ioctl_features arg;

	स_रखो(&arg, 0, माप(arg));

#अगर_घोषित CONFIG_PPC64
	अगर (cpu_has_feature(CPU_FTR_P9_TIDR))
		arg.flags[0] |= OCXL_IOCTL_FEATURES_FLAGS0_P9_WAIT;
#पूर्ण_अगर

	अगर (copy_to_user(uarg, &arg, माप(arg)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#घोषणा CMD_STR(x) (x == OCXL_IOCTL_ATTACH ? "ATTACH" :			\
			x == OCXL_IOCTL_IRQ_ALLOC ? "IRQ_ALLOC" :	\
			x == OCXL_IOCTL_IRQ_FREE ? "IRQ_FREE" :		\
			x == OCXL_IOCTL_IRQ_SET_FD ? "IRQ_SET_FD" :	\
			x == OCXL_IOCTL_GET_METADATA ? "GET_METADATA" :	\
			x == OCXL_IOCTL_ENABLE_P9_WAIT ? "ENABLE_P9_WAIT" :	\
			x == OCXL_IOCTL_GET_FEATURES ? "GET_FEATURES" :	\
			"UNKNOWN")

अटल irqवापस_t irq_handler(व्योम *निजी)
अणु
	काष्ठा eventfd_ctx *ev_ctx = निजी;

	eventfd_संकेत(ev_ctx, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम irq_मुक्त(व्योम *निजी)
अणु
	काष्ठा eventfd_ctx *ev_ctx = निजी;

	eventfd_ctx_put(ev_ctx);
पूर्ण

अटल दीर्घ afu_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ args)
अणु
	काष्ठा ocxl_context *ctx = file->निजी_data;
	काष्ठा ocxl_ioctl_irq_fd irq_fd;
	काष्ठा eventfd_ctx *ev_ctx;
	पूर्णांक irq_id;
	u64 irq_offset;
	दीर्घ rc;
	bool बंदd;

	pr_debug("%s for context %d, command %s\n", __func__, ctx->pasid,
		CMD_STR(cmd));

	mutex_lock(&ctx->status_mutex);
	बंदd = (ctx->status == CLOSED);
	mutex_unlock(&ctx->status_mutex);

	अगर (बंदd)
		वापस -EIO;

	चयन (cmd) अणु
	हाल OCXL_IOCTL_ATTACH:
		rc = afu_ioctl_attach(ctx,
				(काष्ठा ocxl_ioctl_attach __user *) args);
		अवरोध;

	हाल OCXL_IOCTL_IRQ_ALLOC:
		rc = ocxl_afu_irq_alloc(ctx, &irq_id);
		अगर (!rc) अणु
			irq_offset = ocxl_irq_id_to_offset(ctx, irq_id);
			rc = copy_to_user((u64 __user *) args, &irq_offset,
					माप(irq_offset));
			अगर (rc) अणु
				ocxl_afu_irq_मुक्त(ctx, irq_id);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल OCXL_IOCTL_IRQ_FREE:
		rc = copy_from_user(&irq_offset, (u64 __user *) args,
				माप(irq_offset));
		अगर (rc)
			वापस -EFAULT;
		irq_id = ocxl_irq_offset_to_id(ctx, irq_offset);
		rc = ocxl_afu_irq_मुक्त(ctx, irq_id);
		अवरोध;

	हाल OCXL_IOCTL_IRQ_SET_FD:
		rc = copy_from_user(&irq_fd, (u64 __user *) args,
				माप(irq_fd));
		अगर (rc)
			वापस -EFAULT;
		अगर (irq_fd.reserved)
			वापस -EINVAL;
		irq_id = ocxl_irq_offset_to_id(ctx, irq_fd.irq_offset);
		ev_ctx = eventfd_ctx_fdget(irq_fd.eventfd);
		अगर (IS_ERR(ev_ctx))
			वापस PTR_ERR(ev_ctx);
		rc = ocxl_irq_set_handler(ctx, irq_id, irq_handler, irq_मुक्त, ev_ctx);
		अवरोध;

	हाल OCXL_IOCTL_GET_METADATA:
		rc = afu_ioctl_get_metadata(ctx,
				(काष्ठा ocxl_ioctl_metadata __user *) args);
		अवरोध;

#अगर_घोषित CONFIG_PPC64
	हाल OCXL_IOCTL_ENABLE_P9_WAIT:
		rc = afu_ioctl_enable_p9_रुको(ctx,
				(काष्ठा ocxl_ioctl_p9_रुको __user *) args);
		अवरोध;
#पूर्ण_अगर

	हाल OCXL_IOCTL_GET_FEATURES:
		rc = afu_ioctl_get_features(ctx,
				(काष्ठा ocxl_ioctl_features __user *) args);
		अवरोध;

	शेष:
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

अटल दीर्घ afu_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ args)
अणु
	वापस afu_ioctl(file, cmd, args);
पूर्ण

अटल पूर्णांक afu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ocxl_context *ctx = file->निजी_data;

	pr_debug("%s for context %d\n", __func__, ctx->pasid);
	वापस ocxl_context_mmap(ctx, vma);
पूर्ण

अटल bool has_xsl_error(काष्ठा ocxl_context *ctx)
अणु
	bool ret;

	mutex_lock(&ctx->xsl_error_lock);
	ret = !!ctx->xsl_error.addr;
	mutex_unlock(&ctx->xsl_error_lock);

	वापस ret;
पूर्ण

/*
 * Are there any events pending on the AFU
 * ctx: The AFU context
 * Returns: true अगर there are events pending
 */
अटल bool afu_events_pending(काष्ठा ocxl_context *ctx)
अणु
	अगर (has_xsl_error(ctx))
		वापस true;
	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक afu_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा ocxl_context *ctx = file->निजी_data;
	अचिन्हित पूर्णांक mask = 0;
	bool बंदd;

	pr_debug("%s for context %d\n", __func__, ctx->pasid);

	poll_रुको(file, &ctx->events_wq, रुको);

	mutex_lock(&ctx->status_mutex);
	बंदd = (ctx->status == CLOSED);
	mutex_unlock(&ctx->status_mutex);

	अगर (afu_events_pending(ctx))
		mask = EPOLLIN | EPOLLRDNORM;
	अन्यथा अगर (बंदd)
		mask = EPOLLERR;

	वापस mask;
पूर्ण

/*
 * Populate the supplied buffer with a single XSL error
 * ctx:	The AFU context to report the error from
 * header: the event header to populate
 * buf: The buffer to ग_लिखो the body पूर्णांकo (should be at least
 *      AFU_EVENT_BODY_XSL_ERROR_SIZE)
 * Return: the amount of buffer that was populated
 */
अटल sमाप_प्रकार append_xsl_error(काष्ठा ocxl_context *ctx,
				काष्ठा ocxl_kernel_event_header *header,
				अक्षर __user *buf)
अणु
	काष्ठा ocxl_kernel_event_xsl_fault_error body;

	स_रखो(&body, 0, माप(body));

	mutex_lock(&ctx->xsl_error_lock);
	अगर (!ctx->xsl_error.addr) अणु
		mutex_unlock(&ctx->xsl_error_lock);
		वापस 0;
	पूर्ण

	body.addr = ctx->xsl_error.addr;
	body.dsisr = ctx->xsl_error.dsisr;
	body.count = ctx->xsl_error.count;

	ctx->xsl_error.addr = 0;
	ctx->xsl_error.dsisr = 0;
	ctx->xsl_error.count = 0;

	mutex_unlock(&ctx->xsl_error_lock);

	header->type = OCXL_AFU_EVENT_XSL_FAULT_ERROR;

	अगर (copy_to_user(buf, &body, माप(body)))
		वापस -EFAULT;

	वापस माप(body);
पूर्ण

#घोषणा AFU_EVENT_BODY_MAX_SIZE माप(काष्ठा ocxl_kernel_event_xsl_fault_error)

/*
 * Reports events on the AFU
 * Format:
 *	Header (काष्ठा ocxl_kernel_event_header)
 *	Body (काष्ठा ocxl_kernel_event_*)
 *	Header...
 */
अटल sमाप_प्रकार afu_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *off)
अणु
	काष्ठा ocxl_context *ctx = file->निजी_data;
	काष्ठा ocxl_kernel_event_header header;
	sमाप_प्रकार rc;
	sमाप_प्रकार used = 0;
	DEFINE_WAIT(event_रुको);

	स_रखो(&header, 0, माप(header));

	/* Require offset to be 0 */
	अगर (*off != 0)
		वापस -EINVAL;

	अगर (count < (माप(काष्ठा ocxl_kernel_event_header) +
			AFU_EVENT_BODY_MAX_SIZE))
		वापस -EINVAL;

	क्रम (;;) अणु
		prepare_to_रुको(&ctx->events_wq, &event_रुको,
				TASK_INTERRUPTIBLE);

		अगर (afu_events_pending(ctx))
			अवरोध;

		अगर (ctx->status == CLOSED)
			अवरोध;

		अगर (file->f_flags & O_NONBLOCK) अणु
			finish_रुको(&ctx->events_wq, &event_रुको);
			वापस -EAGAIN;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			finish_रुको(&ctx->events_wq, &event_रुको);
			वापस -ERESTARTSYS;
		पूर्ण

		schedule();
	पूर्ण

	finish_रुको(&ctx->events_wq, &event_रुको);

	अगर (has_xsl_error(ctx)) अणु
		used = append_xsl_error(ctx, &header, buf + माप(header));
		अगर (used < 0)
			वापस used;
	पूर्ण

	अगर (!afu_events_pending(ctx))
		header.flags |= OCXL_KERNEL_EVENT_FLAG_LAST;

	अगर (copy_to_user(buf, &header, माप(header)))
		वापस -EFAULT;

	used += माप(header);

	rc = used;
	वापस rc;
पूर्ण

अटल पूर्णांक afu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocxl_context *ctx = file->निजी_data;
	पूर्णांक rc;

	pr_debug("%s for device %x\n", __func__, inode->i_rdev);
	rc = ocxl_context_detach(ctx);
	mutex_lock(&ctx->mapping_lock);
	ctx->mapping = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	wake_up_all(&ctx->events_wq);
	अगर (rc != -EBUSY)
		ocxl_context_मुक्त(ctx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ocxl_afu_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = afu_खोलो,
	.unlocked_ioctl = afu_ioctl,
	.compat_ioctl   = afu_compat_ioctl,
	.mmap           = afu_mmap,
	.poll           = afu_poll,
	.पढ़ो           = afu_पढ़ो,
	.release        = afu_release,
पूर्ण;

// Free the info काष्ठा
अटल व्योम info_release(काष्ठा device *dev)
अणु
	काष्ठा ocxl_file_info *info = container_of(dev, काष्ठा ocxl_file_info, dev);

	ocxl_afu_put(info->afu);
	kमुक्त(info);
पूर्ण

अटल पूर्णांक ocxl_file_make_visible(काष्ठा ocxl_file_info *info)
अणु
	पूर्णांक rc;

	cdev_init(&info->cdev, &ocxl_afu_fops);
	rc = cdev_add(&info->cdev, info->dev.devt, 1);
	अगर (rc) अणु
		dev_err(&info->dev, "Unable to add afu char device: %d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ocxl_file_make_invisible(काष्ठा ocxl_file_info *info)
अणु
	cdev_del(&info->cdev);
पूर्ण

पूर्णांक ocxl_file_रेजिस्टर_afu(काष्ठा ocxl_afu *afu)
अणु
	पूर्णांक minor;
	पूर्णांक rc;
	काष्ठा ocxl_file_info *info;
	काष्ठा ocxl_fn *fn = afu->fn;
	काष्ठा pci_dev *pci_dev = to_pci_dev(fn->dev.parent);

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य)
		वापस -ENOMEM;

	minor = allocate_minor(info);
	अगर (minor < 0) अणु
		kमुक्त(info);
		वापस minor;
	पूर्ण

	info->dev.parent = &fn->dev;
	info->dev.devt = MKDEV(MAJOR(ocxl_dev), minor);
	info->dev.class = ocxl_class;
	info->dev.release = info_release;

	info->afu = afu;
	ocxl_afu_get(afu);

	rc = dev_set_name(&info->dev, "%s.%s.%hhu",
		afu->config.name, dev_name(&pci_dev->dev), afu->config.idx);
	अगर (rc)
		जाओ err_put;

	rc = device_रेजिस्टर(&info->dev);
	अगर (rc)
		जाओ err_put;

	rc = ocxl_sysfs_रेजिस्टर_afu(info);
	अगर (rc)
		जाओ err_unरेजिस्टर;

	rc = ocxl_file_make_visible(info);
	अगर (rc)
		जाओ err_unरेजिस्टर;

	ocxl_afu_set_निजी(afu, info);

	वापस 0;

err_unरेजिस्टर:
	ocxl_sysfs_unरेजिस्टर_afu(info); // safe to call even अगर रेजिस्टर failed
	device_unरेजिस्टर(&info->dev);
err_put:
	ocxl_afu_put(afu);
	मुक्त_minor(info);
	kमुक्त(info);
	वापस rc;
पूर्ण

व्योम ocxl_file_unरेजिस्टर_afu(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_file_info *info = ocxl_afu_get_निजी(afu);

	अगर (!info)
		वापस;

	ocxl_file_make_invisible(info);
	ocxl_sysfs_unरेजिस्टर_afu(info);
	मुक्त_minor(info);
	device_unरेजिस्टर(&info->dev);
पूर्ण

अटल अक्षर *ocxl_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "ocxl/%s", dev_name(dev));
पूर्ण

पूर्णांक ocxl_file_init(व्योम)
अणु
	पूर्णांक rc;

	idr_init(&minors_idr);

	rc = alloc_chrdev_region(&ocxl_dev, 0, OCXL_NUM_MINORS, "ocxl");
	अगर (rc) अणु
		pr_err("Unable to allocate ocxl major number: %d\n", rc);
		वापस rc;
	पूर्ण

	ocxl_class = class_create(THIS_MODULE, "ocxl");
	अगर (IS_ERR(ocxl_class)) अणु
		pr_err("Unable to create ocxl class\n");
		unरेजिस्टर_chrdev_region(ocxl_dev, OCXL_NUM_MINORS);
		वापस PTR_ERR(ocxl_class);
	पूर्ण

	ocxl_class->devnode = ocxl_devnode;
	वापस 0;
पूर्ण

व्योम ocxl_file_निकास(व्योम)
अणु
	class_destroy(ocxl_class);
	unरेजिस्टर_chrdev_region(ocxl_dev, OCXL_NUM_MINORS);
	idr_destroy(&minors_idr);
पूर्ण
