<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO generic eventfd code क्रम IRQFD support.
 * Derived from drivers/vfio/pci/vfio_pci_पूर्णांकrs.c
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */

#समावेश <linux/vfपन.स>
#समावेश <linux/eventfd.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा DRIVER_VERSION  "0.1"
#घोषणा DRIVER_AUTHOR   "Alex Williamson <alex.williamson@redhat.com>"
#घोषणा DRIVER_DESC     "IRQFD support for VFIO bus drivers"

अटल काष्ठा workqueue_काष्ठा *vfio_irqfd_cleanup_wq;
अटल DEFINE_SPINLOCK(virqfd_lock);

अटल पूर्णांक __init vfio_virqfd_init(व्योम)
अणु
	vfio_irqfd_cleanup_wq =
		create_singlethपढ़ो_workqueue("vfio-irqfd-cleanup");
	अगर (!vfio_irqfd_cleanup_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __निकास vfio_virqfd_निकास(व्योम)
अणु
	destroy_workqueue(vfio_irqfd_cleanup_wq);
पूर्ण

अटल व्योम virqfd_deactivate(काष्ठा virqfd *virqfd)
अणु
	queue_work(vfio_irqfd_cleanup_wq, &virqfd->shutकरोwn);
पूर्ण

अटल पूर्णांक virqfd_wakeup(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा virqfd *virqfd = container_of(रुको, काष्ठा virqfd, रुको);
	__poll_t flags = key_to_poll(key);

	अगर (flags & EPOLLIN) अणु
		u64 cnt;
		eventfd_ctx_करो_पढ़ो(virqfd->eventfd, &cnt);

		/* An event has been संकेतed, call function */
		अगर ((!virqfd->handler ||
		     virqfd->handler(virqfd->opaque, virqfd->data)) &&
		    virqfd->thपढ़ो)
			schedule_work(&virqfd->inject);
	पूर्ण

	अगर (flags & EPOLLHUP) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&virqfd_lock, flags);

		/*
		 * The eventfd is closing, अगर the virqfd has not yet been
		 * queued क्रम release, as determined by testing whether the
		 * virqfd poपूर्णांकer to it is still valid, queue it now.  As
		 * with kvm irqfds, we know we won't race against the virqfd
		 * going away because we hold the lock to get here.
		 */
		अगर (*(virqfd->pvirqfd) == virqfd) अणु
			*(virqfd->pvirqfd) = शून्य;
			virqfd_deactivate(virqfd);
		पूर्ण

		spin_unlock_irqrestore(&virqfd_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virqfd_ptable_queue_proc(काष्ठा file *file,
				     रुको_queue_head_t *wqh, poll_table *pt)
अणु
	काष्ठा virqfd *virqfd = container_of(pt, काष्ठा virqfd, pt);
	add_रुको_queue(wqh, &virqfd->रुको);
पूर्ण

अटल व्योम virqfd_shutकरोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virqfd *virqfd = container_of(work, काष्ठा virqfd, shutकरोwn);
	u64 cnt;

	eventfd_ctx_हटाओ_रुको_queue(virqfd->eventfd, &virqfd->रुको, &cnt);
	flush_work(&virqfd->inject);
	eventfd_ctx_put(virqfd->eventfd);

	kमुक्त(virqfd);
पूर्ण

अटल व्योम virqfd_inject(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virqfd *virqfd = container_of(work, काष्ठा virqfd, inject);
	अगर (virqfd->thपढ़ो)
		virqfd->thपढ़ो(virqfd->opaque, virqfd->data);
पूर्ण

पूर्णांक vfio_virqfd_enable(व्योम *opaque,
		       पूर्णांक (*handler)(व्योम *, व्योम *),
		       व्योम (*thपढ़ो)(व्योम *, व्योम *),
		       व्योम *data, काष्ठा virqfd **pvirqfd, पूर्णांक fd)
अणु
	काष्ठा fd irqfd;
	काष्ठा eventfd_ctx *ctx;
	काष्ठा virqfd *virqfd;
	पूर्णांक ret = 0;
	__poll_t events;

	virqfd = kzalloc(माप(*virqfd), GFP_KERNEL);
	अगर (!virqfd)
		वापस -ENOMEM;

	virqfd->pvirqfd = pvirqfd;
	virqfd->opaque = opaque;
	virqfd->handler = handler;
	virqfd->thपढ़ो = thपढ़ो;
	virqfd->data = data;

	INIT_WORK(&virqfd->shutकरोwn, virqfd_shutकरोwn);
	INIT_WORK(&virqfd->inject, virqfd_inject);

	irqfd = fdget(fd);
	अगर (!irqfd.file) अणु
		ret = -EBADF;
		जाओ err_fd;
	पूर्ण

	ctx = eventfd_ctx_fileget(irqfd.file);
	अगर (IS_ERR(ctx)) अणु
		ret = PTR_ERR(ctx);
		जाओ err_ctx;
	पूर्ण

	virqfd->eventfd = ctx;

	/*
	 * virqfds can be released by closing the eventfd or directly
	 * through ioctl.  These are both करोne through a workqueue, so
	 * we update the poपूर्णांकer to the virqfd under lock to aव्योम
	 * pushing multiple jobs to release the same virqfd.
	 */
	spin_lock_irq(&virqfd_lock);

	अगर (*pvirqfd) अणु
		spin_unlock_irq(&virqfd_lock);
		ret = -EBUSY;
		जाओ err_busy;
	पूर्ण
	*pvirqfd = virqfd;

	spin_unlock_irq(&virqfd_lock);

	/*
	 * Install our own custom wake-up handling so we are notअगरied via
	 * a callback whenever someone संकेतs the underlying eventfd.
	 */
	init_रुकोqueue_func_entry(&virqfd->रुको, virqfd_wakeup);
	init_poll_funcptr(&virqfd->pt, virqfd_ptable_queue_proc);

	events = vfs_poll(irqfd.file, &virqfd->pt);

	/*
	 * Check अगर there was an event alपढ़ोy pending on the eventfd
	 * beक्रमe we रेजिस्टरed and trigger it as अगर we didn't miss it.
	 */
	अगर (events & EPOLLIN) अणु
		अगर ((!handler || handler(opaque, data)) && thपढ़ो)
			schedule_work(&virqfd->inject);
	पूर्ण

	/*
	 * Do not drop the file until the irqfd is fully initialized,
	 * otherwise we might race against the EPOLLHUP.
	 */
	fdput(irqfd);

	वापस 0;
err_busy:
	eventfd_ctx_put(ctx);
err_ctx:
	fdput(irqfd);
err_fd:
	kमुक्त(virqfd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_virqfd_enable);

व्योम vfio_virqfd_disable(काष्ठा virqfd **pvirqfd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&virqfd_lock, flags);

	अगर (*pvirqfd) अणु
		virqfd_deactivate(*pvirqfd);
		*pvirqfd = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&virqfd_lock, flags);

	/*
	 * Block until we know all outstanding shutकरोwn jobs have completed.
	 * Even अगर we करोn't queue the job, flush the wq to be sure it's
	 * been released.
	 */
	flush_workqueue(vfio_irqfd_cleanup_wq);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_virqfd_disable);

module_init(vfio_virqfd_init);
module_निकास(vfio_virqfd_निकास);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
