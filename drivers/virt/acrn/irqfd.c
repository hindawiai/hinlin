<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN HSM irqfd: use eventfd objects to inject भव पूर्णांकerrupts
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Shuo Liu <shuo.a.liu@पूर्णांकel.com>
 *	Yakui Zhao <yakui.zhao@पूर्णांकel.com>
 */

#समावेश <linux/eventfd.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>

#समावेश "acrn_drv.h"

अटल LIST_HEAD(acrn_irqfd_clients);
अटल DEFINE_MUTEX(acrn_irqfds_mutex);

/**
 * काष्ठा hsm_irqfd - Properties of HSM irqfd
 * @vm:		Associated VM poपूर्णांकer
 * @रुको:	Entry of रुको-queue
 * @shutकरोwn:	Async shutकरोwn work
 * @eventfd:	Associated eventfd
 * @list:	Entry within &acrn_vm.irqfds of irqfds of a VM
 * @pt:		Structure क्रम select/poll on the associated eventfd
 * @msi:	MSI data
 */
काष्ठा hsm_irqfd अणु
	काष्ठा acrn_vm		*vm;
	रुको_queue_entry_t	रुको;
	काष्ठा work_काष्ठा	shutकरोwn;
	काष्ठा eventfd_ctx	*eventfd;
	काष्ठा list_head	list;
	poll_table		pt;
	काष्ठा acrn_msi_entry	msi;
पूर्ण;

अटल व्योम acrn_irqfd_inject(काष्ठा hsm_irqfd *irqfd)
अणु
	काष्ठा acrn_vm *vm = irqfd->vm;

	acrn_msi_inject(vm, irqfd->msi.msi_addr,
			irqfd->msi.msi_data);
पूर्ण

अटल व्योम hsm_irqfd_shutकरोwn(काष्ठा hsm_irqfd *irqfd)
अणु
	u64 cnt;

	lockdep_निश्चित_held(&irqfd->vm->irqfds_lock);

	/* हटाओ from रुको queue */
	list_del_init(&irqfd->list);
	eventfd_ctx_हटाओ_रुको_queue(irqfd->eventfd, &irqfd->रुको, &cnt);
	eventfd_ctx_put(irqfd->eventfd);
	kमुक्त(irqfd);
पूर्ण

अटल व्योम hsm_irqfd_shutकरोwn_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hsm_irqfd *irqfd;
	काष्ठा acrn_vm *vm;

	irqfd = container_of(work, काष्ठा hsm_irqfd, shutकरोwn);
	vm = irqfd->vm;
	mutex_lock(&vm->irqfds_lock);
	अगर (!list_empty(&irqfd->list))
		hsm_irqfd_shutकरोwn(irqfd);
	mutex_unlock(&vm->irqfds_lock);
पूर्ण

/* Called with wqh->lock held and पूर्णांकerrupts disabled */
अटल पूर्णांक hsm_irqfd_wakeup(रुको_queue_entry_t *रुको, अचिन्हित पूर्णांक mode,
			    पूर्णांक sync, व्योम *key)
अणु
	अचिन्हित दीर्घ poll_bits = (अचिन्हित दीर्घ)key;
	काष्ठा hsm_irqfd *irqfd;
	काष्ठा acrn_vm *vm;

	irqfd = container_of(रुको, काष्ठा hsm_irqfd, रुको);
	vm = irqfd->vm;
	अगर (poll_bits & POLLIN)
		/* An event has been संकेतed, inject an पूर्णांकerrupt */
		acrn_irqfd_inject(irqfd);

	अगर (poll_bits & POLLHUP)
		/* Do shutकरोwn work in thपढ़ो to hold wqh->lock */
		queue_work(vm->irqfd_wq, &irqfd->shutकरोwn);

	वापस 0;
पूर्ण

अटल व्योम hsm_irqfd_poll_func(काष्ठा file *file, रुको_queue_head_t *wqh,
				poll_table *pt)
अणु
	काष्ठा hsm_irqfd *irqfd;

	irqfd = container_of(pt, काष्ठा hsm_irqfd, pt);
	add_रुको_queue(wqh, &irqfd->रुको);
पूर्ण

/*
 * Assign an eventfd to a VM and create a HSM irqfd associated with the
 * eventfd. The properties of the HSM irqfd are built from a &काष्ठा
 * acrn_irqfd.
 */
अटल पूर्णांक acrn_irqfd_assign(काष्ठा acrn_vm *vm, काष्ठा acrn_irqfd *args)
अणु
	काष्ठा eventfd_ctx *eventfd = शून्य;
	काष्ठा hsm_irqfd *irqfd, *पंचांगp;
	__poll_t events;
	काष्ठा fd f;
	पूर्णांक ret = 0;

	irqfd = kzalloc(माप(*irqfd), GFP_KERNEL);
	अगर (!irqfd)
		वापस -ENOMEM;

	irqfd->vm = vm;
	स_नकल(&irqfd->msi, &args->msi, माप(args->msi));
	INIT_LIST_HEAD(&irqfd->list);
	INIT_WORK(&irqfd->shutकरोwn, hsm_irqfd_shutकरोwn_work);

	f = fdget(args->fd);
	अगर (!f.file) अणु
		ret = -EBADF;
		जाओ out;
	पूर्ण

	eventfd = eventfd_ctx_fileget(f.file);
	अगर (IS_ERR(eventfd)) अणु
		ret = PTR_ERR(eventfd);
		जाओ fail;
	पूर्ण

	irqfd->eventfd = eventfd;

	/*
	 * Install custom wake-up handling to be notअगरied whenever underlying
	 * eventfd is संकेतed.
	 */
	init_रुकोqueue_func_entry(&irqfd->रुको, hsm_irqfd_wakeup);
	init_poll_funcptr(&irqfd->pt, hsm_irqfd_poll_func);

	mutex_lock(&vm->irqfds_lock);
	list_क्रम_each_entry(पंचांगp, &vm->irqfds, list) अणु
		अगर (irqfd->eventfd != पंचांगp->eventfd)
			जारी;
		ret = -EBUSY;
		mutex_unlock(&vm->irqfds_lock);
		जाओ fail;
	पूर्ण
	list_add_tail(&irqfd->list, &vm->irqfds);
	mutex_unlock(&vm->irqfds_lock);

	/* Check the pending event in this stage */
	events = vfs_poll(f.file, &irqfd->pt);

	अगर (events & EPOLLIN)
		acrn_irqfd_inject(irqfd);

	fdput(f);
	वापस 0;
fail:
	अगर (eventfd && !IS_ERR(eventfd))
		eventfd_ctx_put(eventfd);

	fdput(f);
out:
	kमुक्त(irqfd);
	वापस ret;
पूर्ण

अटल पूर्णांक acrn_irqfd_deassign(काष्ठा acrn_vm *vm,
			       काष्ठा acrn_irqfd *args)
अणु
	काष्ठा hsm_irqfd *irqfd, *पंचांगp;
	काष्ठा eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	mutex_lock(&vm->irqfds_lock);
	list_क्रम_each_entry_safe(irqfd, पंचांगp, &vm->irqfds, list) अणु
		अगर (irqfd->eventfd == eventfd) अणु
			hsm_irqfd_shutकरोwn(irqfd);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vm->irqfds_lock);
	eventfd_ctx_put(eventfd);

	वापस 0;
पूर्ण

पूर्णांक acrn_irqfd_config(काष्ठा acrn_vm *vm, काष्ठा acrn_irqfd *args)
अणु
	पूर्णांक ret;

	अगर (args->flags & ACRN_IRQFD_FLAG_DEASSIGN)
		ret = acrn_irqfd_deassign(vm, args);
	अन्यथा
		ret = acrn_irqfd_assign(vm, args);

	वापस ret;
पूर्ण

पूर्णांक acrn_irqfd_init(काष्ठा acrn_vm *vm)
अणु
	INIT_LIST_HEAD(&vm->irqfds);
	mutex_init(&vm->irqfds_lock);
	vm->irqfd_wq = alloc_workqueue("acrn_irqfd-%u", 0, 0, vm->vmid);
	अगर (!vm->irqfd_wq)
		वापस -ENOMEM;

	dev_dbg(acrn_dev.this_device, "VM %u irqfd init.\n", vm->vmid);
	वापस 0;
पूर्ण

व्योम acrn_irqfd_deinit(काष्ठा acrn_vm *vm)
अणु
	काष्ठा hsm_irqfd *irqfd, *next;

	dev_dbg(acrn_dev.this_device, "VM %u irqfd deinit.\n", vm->vmid);
	destroy_workqueue(vm->irqfd_wq);
	mutex_lock(&vm->irqfds_lock);
	list_क्रम_each_entry_safe(irqfd, next, &vm->irqfds, list)
		hsm_irqfd_shutकरोwn(irqfd);
	mutex_unlock(&vm->irqfds_lock);
पूर्ण
