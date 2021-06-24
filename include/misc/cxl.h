<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015 IBM Corp.
 */

#अगर_अघोषित _MISC_CXL_H
#घोषणा _MISC_CXL_H

#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <uapi/misc/cxl.h>

/*
 * This करोcuments the in kernel API क्रम driver to use CXL. It allows kernel
 * drivers to bind to AFUs using an AFU configuration record exposed as a PCI
 * configuration record.
 *
 * This API enables control over AFU and contexts which can't be part of the
 * generic PCI API. This API is agnostic to the actual AFU.
 */

/* Get the AFU associated with a pci_dev */
काष्ठा cxl_afu *cxl_pci_to_afu(काष्ठा pci_dev *dev);

/* Get the AFU conf record number associated with a pci_dev */
अचिन्हित पूर्णांक cxl_pci_to_cfg_record(काष्ठा pci_dev *dev);


/*
 * Context lअगरeसमय overview:
 *
 * An AFU context may be inited and then started and stoppped multiple बार
 * beक्रमe it's released. ie.
 *    - cxl_dev_context_init()
 *      - cxl_start_context()
 *      - cxl_stop_context()
 *      - cxl_start_context()
 *      - cxl_stop_context()
 *     ...repeat...
 *    - cxl_release_context()
 * Once released, a context can't be started again.
 *
 * One context is inited by the cxl driver क्रम every pci_dev. This is to be
 * used as a शेष kernel context. cxl_get_context() will get this
 * context. This context will be released by PCI hot unplug, so करोesn't need to
 * be released explicitly by drivers.
 *
 * Additional kernel contexts may be inited using cxl_dev_context_init().
 * These must be released using cxl_context_detach().
 *
 * Once a context has been inited, IRQs may be configured. Firstly these IRQs
 * must be allocated (cxl_allocate_afu_irqs()), then inभागidually mapped to
 * specअगरic handlers (cxl_map_afu_irq()).
 *
 * These IRQs can be unmapped (cxl_unmap_afu_irq()) and finally released
 * (cxl_मुक्त_afu_irqs()).
 *
 * The AFU can be reset (cxl_afu_reset()). This will cause the PSL/AFU
 * hardware to lose track of all contexts. It's upto the caller of
 * cxl_afu_reset() to restart these contexts.
 */

/*
 * On pci_enabled_device(), the cxl driver will init a single cxl context क्रम
 * use by the driver. It करोesn't start this context (as that will likely
 * generate DMA traffic क्रम most AFUs).
 *
 * This माला_लो the शेष context associated with this pci_dev.  This context
 * करोesn't need to be released as this will be करोne by the PCI subप्रणाली on hot
 * unplug.
 */
काष्ठा cxl_context *cxl_get_context(काष्ठा pci_dev *dev);
/*
 * Allocate and initalise a context associated with a AFU PCI device. This
 * करोesn't start the context in the AFU.
 */
काष्ठा cxl_context *cxl_dev_context_init(काष्ठा pci_dev *dev);
/*
 * Release and मुक्त a context. Context should be stopped beक्रमe calling.
 */
पूर्णांक cxl_release_context(काष्ठा cxl_context *ctx);

/*
 * Set and get निजी data associated with a context. Allows drivers to have a
 * back poपूर्णांकer to some useful काष्ठाure.
 */
पूर्णांक cxl_set_priv(काष्ठा cxl_context *ctx, व्योम *priv);
व्योम *cxl_get_priv(काष्ठा cxl_context *ctx);

/*
 * Allocate AFU पूर्णांकerrupts क्रम this context. num=0 will allocate the शेष
 * क्रम this AFU as given in the AFU descriptor. This number करोesn't include the
 * पूर्णांकerrupt 0 (CAIA defines AFU IRQ 0 क्रम page faults). Each पूर्णांकerrupt to be
 * used must map a handler with cxl_map_afu_irq.
 */
पूर्णांक cxl_allocate_afu_irqs(काष्ठा cxl_context *cxl, पूर्णांक num);
/* Free allocated पूर्णांकerrupts */
व्योम cxl_मुक्त_afu_irqs(काष्ठा cxl_context *cxl);

/*
 * Map a handler क्रम an AFU पूर्णांकerrupt associated with a particular context. AFU
 * IRQS numbers start from 1 (CAIA defines AFU IRQ 0 क्रम page faults). cookie
 * is निजी data is that will be provided to the पूर्णांकerrupt handler.
 */
पूर्णांक cxl_map_afu_irq(काष्ठा cxl_context *cxl, पूर्णांक num,
		    irq_handler_t handler, व्योम *cookie, अक्षर *name);
/* unmap mapped IRQ handlers */
व्योम cxl_unmap_afu_irq(काष्ठा cxl_context *cxl, पूर्णांक num, व्योम *cookie);

/*
 * Start work on the AFU. This starts an cxl context and associates it with a
 * task. task == शून्य will make it a kernel context.
 */
पूर्णांक cxl_start_context(काष्ठा cxl_context *ctx, u64 wed,
		      काष्ठा task_काष्ठा *task);
/*
 * Stop a context and हटाओ it from the PSL
 */
पूर्णांक cxl_stop_context(काष्ठा cxl_context *ctx);

/* Reset the AFU */
पूर्णांक cxl_afu_reset(काष्ठा cxl_context *ctx);

/*
 * Set a context as a master context.
 * This sets the शेष problem space area mapped as the full space, rather
 * than just the per context area (क्रम slaves).
 */
व्योम cxl_set_master(काष्ठा cxl_context *ctx);

/*
 * Map and unmap the AFU Problem Space area. The amount and location mapped
 * depends on अगर this context is a master or slave.
 */
व्योम __iomem *cxl_psa_map(काष्ठा cxl_context *ctx);
व्योम cxl_psa_unmap(व्योम __iomem *addr);

/*  Get the process element क्रम this context */
पूर्णांक cxl_process_element(काष्ठा cxl_context *ctx);

/*
 * These calls allow drivers to create their own file descriptors and make them
 * identical to the cxl file descriptor user API. An example use हाल:
 *
 * काष्ठा file_operations cxl_my_fops = अणुपूर्ण;
 * ......
 *	// Init the context
 *	ctx = cxl_dev_context_init(dev);
 *	अगर (IS_ERR(ctx))
 *		वापस PTR_ERR(ctx);
 *	// Create and attach a new file descriptor to my file ops
 *	file = cxl_get_fd(ctx, &cxl_my_fops, &fd);
 *	// Start context
 *	rc = cxl_start_work(ctx, &work.work);
 *	अगर (rc) अणु
 *		fput(file);
 *		put_unused_fd(fd);
 *		वापस -ENODEV;
 *	पूर्ण
 *	// No error paths after installing the fd
 *	fd_install(fd, file);
 *	वापस fd;
 *
 * This inits a context, and माला_लो a file descriptor and associates some file
 * ops to that file descriptor. If the file ops are blank, the cxl driver will
 * fill them in with the शेष ones that mimic the standard user API.  Once
 * completed, the file descriptor can be installed. Once the file descriptor is
 * installed, it's visible to the user so no errors must occur past this poपूर्णांक.
 *
 * If cxl_fd_release() file op call is installed, the context will be stopped
 * and released when the fd is released. Hence the driver won't need to manage
 * this itself.
 */

/*
 * Take a context and associate it with my file ops. Returns the associated
 * file and file descriptor. Any file ops which are blank are filled in by the
 * cxl driver with the शेष ops to mimic the standard API.
 */
काष्ठा file *cxl_get_fd(काष्ठा cxl_context *ctx, काष्ठा file_operations *fops,
			पूर्णांक *fd);
/* Get the context associated with this file */
काष्ठा cxl_context *cxl_fops_get_context(काष्ठा file *file);
/*
 * Start a context associated a काष्ठा cxl_ioctl_start_work used by the
 * standard cxl user API.
 */
पूर्णांक cxl_start_work(काष्ठा cxl_context *ctx,
		   काष्ठा cxl_ioctl_start_work *work);
/*
 * Export all the existing fops so drivers can use them
 */
पूर्णांक cxl_fd_खोलो(काष्ठा inode *inode, काष्ठा file *file);
पूर्णांक cxl_fd_release(काष्ठा inode *inode, काष्ठा file *file);
दीर्घ cxl_fd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक cxl_fd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm);
__poll_t cxl_fd_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll);
sमाप_प्रकार cxl_fd_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			   loff_t *off);

/*
 * For EEH, a driver may want to निश्चित a PERST will reload the same image
 * from flash पूर्णांकo the FPGA.
 *
 * This is a property of the entire adapter, not a single AFU, so drivers
 * should set this property with care!
 */
व्योम cxl_perst_reloads_same_image(काष्ठा cxl_afu *afu,
				  bool perst_reloads_same_image);

/*
 * Read the VPD क्रम the card where the AFU resides
 */
sमाप_प्रकार cxl_पढ़ो_adapter_vpd(काष्ठा pci_dev *dev, व्योम *buf, माप_प्रकार count);

/*
 * AFU driver ops allow an AFU driver to create their own events to pass to
 * userspace through the file descriptor as a simpler alternative to overriding
 * the पढ़ो() and poll() calls that works with the generic cxl events. These
 * events are given priority over the generic cxl events, so they will be
 * delivered first अगर multiple types of events are pending.
 *
 * The AFU driver must call cxl_context_events_pending() to notअगरy the cxl
 * driver that new events are पढ़ोy to be delivered क्रम a specअगरic context.
 * cxl_context_events_pending() will adjust the current count of AFU driver
 * events क्रम this context, and wake up anyone रुकोing on the context रुको
 * queue.
 *
 * The cxl driver will then call fetch_event() to get a काष्ठाure defining
 * the size and address of the driver specअगरic event data. The cxl driver
 * will build a cxl header with type and process_element fields filled in,
 * and header.size set to माप(काष्ठा cxl_event_header) + data_size.
 * The total size of the event is limited to CXL_READ_MIN_SIZE (4K).
 *
 * fetch_event() is called with a spin lock held, so it must not sleep.
 *
 * The cxl driver will then deliver the event to userspace, and finally
 * call event_delivered() to वापस the status of the operation, identअगरied
 * by cxl context and AFU driver event data poपूर्णांकers.
 *   0        Success
 *   -EFAULT  copy_to_user() has failed
 *   -EINVAL  Event data poपूर्णांकer is शून्य, or event size is greater than
 *            CXL_READ_MIN_SIZE.
 */
काष्ठा cxl_afu_driver_ops अणु
	काष्ठा cxl_event_afu_driver_reserved *(*fetch_event) (
						काष्ठा cxl_context *ctx);
	व्योम (*event_delivered) (काष्ठा cxl_context *ctx,
				 काष्ठा cxl_event_afu_driver_reserved *event,
				 पूर्णांक rc);
पूर्ण;

/*
 * Associate the above driver ops with a specअगरic context.
 * Reset the current count of AFU driver events.
 */
व्योम cxl_set_driver_ops(काष्ठा cxl_context *ctx,
			काष्ठा cxl_afu_driver_ops *ops);

/* Notअगरy cxl driver that new events are पढ़ोy to be delivered क्रम context */
व्योम cxl_context_events_pending(काष्ठा cxl_context *ctx,
				अचिन्हित पूर्णांक new_events);

#पूर्ण_अगर /* _MISC_CXL_H */
