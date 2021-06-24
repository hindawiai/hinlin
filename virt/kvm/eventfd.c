<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kvm eventfd support - use eventfd objects to संकेत various KVM events
 *
 * Copyright 2009 Novell.  All Rights Reserved.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Author:
 *	Gregory Haskins <ghaskins@novell.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_irqfd.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/file.h>
#समावेश <linux/list.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/irqbypass.h>
#समावेश <trace/events/kvm.h>

#समावेश <kvm/iodev.h>

#अगर_घोषित CONFIG_HAVE_KVM_IRQFD

अटल काष्ठा workqueue_काष्ठा *irqfd_cleanup_wq;

bool __attribute__((weak))
kvm_arch_irqfd_allowed(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	वापस true;
पूर्ण

अटल व्योम
irqfd_inject(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(work, काष्ठा kvm_kernel_irqfd, inject);
	काष्ठा kvm *kvm = irqfd->kvm;

	अगर (!irqfd->resampler) अणु
		kvm_set_irq(kvm, KVM_USERSPACE_IRQ_SOURCE_ID, irqfd->gsi, 1,
				false);
		kvm_set_irq(kvm, KVM_USERSPACE_IRQ_SOURCE_ID, irqfd->gsi, 0,
				false);
	पूर्ण अन्यथा
		kvm_set_irq(kvm, KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID,
			    irqfd->gsi, 1, false);
पूर्ण

/*
 * Since resampler irqfds share an IRQ source ID, we de-निश्चित once
 * then notअगरy all of the resampler irqfds using this GSI.  We can't
 * करो multiple de-निश्चितs or we risk racing with incoming re-निश्चितs.
 */
अटल व्योम
irqfd_resampler_ack(काष्ठा kvm_irq_ack_notअगरier *kian)
अणु
	काष्ठा kvm_kernel_irqfd_resampler *resampler;
	काष्ठा kvm *kvm;
	काष्ठा kvm_kernel_irqfd *irqfd;
	पूर्णांक idx;

	resampler = container_of(kian,
			काष्ठा kvm_kernel_irqfd_resampler, notअगरier);
	kvm = resampler->kvm;

	kvm_set_irq(kvm, KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID,
		    resampler->notअगरier.gsi, 0, false);

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);

	list_क्रम_each_entry_rcu(irqfd, &resampler->list, resampler_link)
		eventfd_संकेत(irqfd->resamplefd, 1);

	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
पूर्ण

अटल व्योम
irqfd_resampler_shutकरोwn(काष्ठा kvm_kernel_irqfd *irqfd)
अणु
	काष्ठा kvm_kernel_irqfd_resampler *resampler = irqfd->resampler;
	काष्ठा kvm *kvm = resampler->kvm;

	mutex_lock(&kvm->irqfds.resampler_lock);

	list_del_rcu(&irqfd->resampler_link);
	synchronize_srcu(&kvm->irq_srcu);

	अगर (list_empty(&resampler->list)) अणु
		list_del(&resampler->link);
		kvm_unरेजिस्टर_irq_ack_notअगरier(kvm, &resampler->notअगरier);
		kvm_set_irq(kvm, KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID,
			    resampler->notअगरier.gsi, 0, false);
		kमुक्त(resampler);
	पूर्ण

	mutex_unlock(&kvm->irqfds.resampler_lock);
पूर्ण

/*
 * Race-मुक्त decouple logic (ordering is critical)
 */
अटल व्योम
irqfd_shutकरोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(work, काष्ठा kvm_kernel_irqfd, shutकरोwn);
	काष्ठा kvm *kvm = irqfd->kvm;
	u64 cnt;

	/* Make sure irqfd has been initialized in assign path. */
	synchronize_srcu(&kvm->irq_srcu);

	/*
	 * Synchronize with the रुको-queue and unhook ourselves to prevent
	 * further events.
	 */
	eventfd_ctx_हटाओ_रुको_queue(irqfd->eventfd, &irqfd->रुको, &cnt);

	/*
	 * We know no new events will be scheduled at this poपूर्णांक, so block
	 * until all previously outstanding events have completed
	 */
	flush_work(&irqfd->inject);

	अगर (irqfd->resampler) अणु
		irqfd_resampler_shutकरोwn(irqfd);
		eventfd_ctx_put(irqfd->resamplefd);
	पूर्ण

	/*
	 * It is now safe to release the object's resources
	 */
#अगर_घोषित CONFIG_HAVE_KVM_IRQ_BYPASS
	irq_bypass_unरेजिस्टर_consumer(&irqfd->consumer);
#पूर्ण_अगर
	eventfd_ctx_put(irqfd->eventfd);
	kमुक्त(irqfd);
पूर्ण


/* assumes kvm->irqfds.lock is held */
अटल bool
irqfd_is_active(काष्ठा kvm_kernel_irqfd *irqfd)
अणु
	वापस list_empty(&irqfd->list) ? false : true;
पूर्ण

/*
 * Mark the irqfd as inactive and schedule it क्रम removal
 *
 * assumes kvm->irqfds.lock is held
 */
अटल व्योम
irqfd_deactivate(काष्ठा kvm_kernel_irqfd *irqfd)
अणु
	BUG_ON(!irqfd_is_active(irqfd));

	list_del_init(&irqfd->list);

	queue_work(irqfd_cleanup_wq, &irqfd->shutकरोwn);
पूर्ण

पूर्णांक __attribute__((weak)) kvm_arch_set_irq_inatomic(
				काष्ठा kvm_kernel_irq_routing_entry *irq,
				काष्ठा kvm *kvm, पूर्णांक irq_source_id,
				पूर्णांक level,
				bool line_status)
अणु
	वापस -EWOULDBLOCK;
पूर्ण

/*
 * Called with wqh->lock held and पूर्णांकerrupts disabled
 */
अटल पूर्णांक
irqfd_wakeup(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(रुको, काष्ठा kvm_kernel_irqfd, रुको);
	__poll_t flags = key_to_poll(key);
	काष्ठा kvm_kernel_irq_routing_entry irq;
	काष्ठा kvm *kvm = irqfd->kvm;
	अचिन्हित seq;
	पूर्णांक idx;
	पूर्णांक ret = 0;

	अगर (flags & EPOLLIN) अणु
		u64 cnt;
		eventfd_ctx_करो_पढ़ो(irqfd->eventfd, &cnt);

		idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
		करो अणु
			seq = पढ़ो_seqcount_begin(&irqfd->irq_entry_sc);
			irq = irqfd->irq_entry;
		पूर्ण जबतक (पढ़ो_seqcount_retry(&irqfd->irq_entry_sc, seq));
		/* An event has been संकेतed, inject an पूर्णांकerrupt */
		अगर (kvm_arch_set_irq_inatomic(&irq, kvm,
					      KVM_USERSPACE_IRQ_SOURCE_ID, 1,
					      false) == -EWOULDBLOCK)
			schedule_work(&irqfd->inject);
		srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
		ret = 1;
	पूर्ण

	अगर (flags & EPOLLHUP) अणु
		/* The eventfd is closing, detach from KVM */
		अचिन्हित दीर्घ अगरlags;

		spin_lock_irqsave(&kvm->irqfds.lock, अगरlags);

		/*
		 * We must check अगर someone deactivated the irqfd beक्रमe
		 * we could acquire the irqfds.lock since the item is
		 * deactivated from the KVM side beक्रमe it is unhooked from
		 * the रुको-queue.  If it is alपढ़ोy deactivated, we can
		 * simply वापस knowing the other side will cleanup क्रम us.
		 * We cannot race against the irqfd going away since the
		 * other side is required to acquire wqh->lock, which we hold
		 */
		अगर (irqfd_is_active(irqfd))
			irqfd_deactivate(irqfd);

		spin_unlock_irqrestore(&kvm->irqfds.lock, अगरlags);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
irqfd_ptable_queue_proc(काष्ठा file *file, रुको_queue_head_t *wqh,
			poll_table *pt)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(pt, काष्ठा kvm_kernel_irqfd, pt);
	add_रुको_queue_priority(wqh, &irqfd->रुको);
पूर्ण

/* Must be called under irqfds.lock */
अटल व्योम irqfd_update(काष्ठा kvm *kvm, काष्ठा kvm_kernel_irqfd *irqfd)
अणु
	काष्ठा kvm_kernel_irq_routing_entry *e;
	काष्ठा kvm_kernel_irq_routing_entry entries[KVM_NR_IRQCHIPS];
	पूर्णांक n_entries;

	n_entries = kvm_irq_map_gsi(kvm, entries, irqfd->gsi);

	ग_लिखो_seqcount_begin(&irqfd->irq_entry_sc);

	e = entries;
	अगर (n_entries == 1)
		irqfd->irq_entry = *e;
	अन्यथा
		irqfd->irq_entry.type = 0;

	ग_लिखो_seqcount_end(&irqfd->irq_entry_sc);
पूर्ण

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_BYPASS
व्योम __attribute__((weak)) kvm_arch_irq_bypass_stop(
				काष्ठा irq_bypass_consumer *cons)
अणु
पूर्ण

व्योम __attribute__((weak)) kvm_arch_irq_bypass_start(
				काष्ठा irq_bypass_consumer *cons)
अणु
पूर्ण

पूर्णांक  __attribute__((weak)) kvm_arch_update_irqfd_routing(
				काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
				uपूर्णांक32_t guest_irq, bool set)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
kvm_irqfd_assign(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd, *पंचांगp;
	काष्ठा fd f;
	काष्ठा eventfd_ctx *eventfd = शून्य, *resamplefd = शून्य;
	पूर्णांक ret;
	__poll_t events;
	पूर्णांक idx;

	अगर (!kvm_arch_पूर्णांकc_initialized(kvm))
		वापस -EAGAIN;

	अगर (!kvm_arch_irqfd_allowed(kvm, args))
		वापस -EINVAL;

	irqfd = kzalloc(माप(*irqfd), GFP_KERNEL_ACCOUNT);
	अगर (!irqfd)
		वापस -ENOMEM;

	irqfd->kvm = kvm;
	irqfd->gsi = args->gsi;
	INIT_LIST_HEAD(&irqfd->list);
	INIT_WORK(&irqfd->inject, irqfd_inject);
	INIT_WORK(&irqfd->shutकरोwn, irqfd_shutकरोwn);
	seqcount_spinlock_init(&irqfd->irq_entry_sc, &kvm->irqfds.lock);

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

	अगर (args->flags & KVM_IRQFD_FLAG_RESAMPLE) अणु
		काष्ठा kvm_kernel_irqfd_resampler *resampler;

		resamplefd = eventfd_ctx_fdget(args->resamplefd);
		अगर (IS_ERR(resamplefd)) अणु
			ret = PTR_ERR(resamplefd);
			जाओ fail;
		पूर्ण

		irqfd->resamplefd = resamplefd;
		INIT_LIST_HEAD(&irqfd->resampler_link);

		mutex_lock(&kvm->irqfds.resampler_lock);

		list_क्रम_each_entry(resampler,
				    &kvm->irqfds.resampler_list, link) अणु
			अगर (resampler->notअगरier.gsi == irqfd->gsi) अणु
				irqfd->resampler = resampler;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!irqfd->resampler) अणु
			resampler = kzalloc(माप(*resampler),
					    GFP_KERNEL_ACCOUNT);
			अगर (!resampler) अणु
				ret = -ENOMEM;
				mutex_unlock(&kvm->irqfds.resampler_lock);
				जाओ fail;
			पूर्ण

			resampler->kvm = kvm;
			INIT_LIST_HEAD(&resampler->list);
			resampler->notअगरier.gsi = irqfd->gsi;
			resampler->notअगरier.irq_acked = irqfd_resampler_ack;
			INIT_LIST_HEAD(&resampler->link);

			list_add(&resampler->link, &kvm->irqfds.resampler_list);
			kvm_रेजिस्टर_irq_ack_notअगरier(kvm,
						      &resampler->notअगरier);
			irqfd->resampler = resampler;
		पूर्ण

		list_add_rcu(&irqfd->resampler_link, &irqfd->resampler->list);
		synchronize_srcu(&kvm->irq_srcu);

		mutex_unlock(&kvm->irqfds.resampler_lock);
	पूर्ण

	/*
	 * Install our own custom wake-up handling so we are notअगरied via
	 * a callback whenever someone संकेतs the underlying eventfd
	 */
	init_रुकोqueue_func_entry(&irqfd->रुको, irqfd_wakeup);
	init_poll_funcptr(&irqfd->pt, irqfd_ptable_queue_proc);

	spin_lock_irq(&kvm->irqfds.lock);

	ret = 0;
	list_क्रम_each_entry(पंचांगp, &kvm->irqfds.items, list) अणु
		अगर (irqfd->eventfd != पंचांगp->eventfd)
			जारी;
		/* This fd is used क्रम another irq alपढ़ोy. */
		ret = -EBUSY;
		spin_unlock_irq(&kvm->irqfds.lock);
		जाओ fail;
	पूर्ण

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	irqfd_update(kvm, irqfd);

	list_add_tail(&irqfd->list, &kvm->irqfds.items);

	spin_unlock_irq(&kvm->irqfds.lock);

	/*
	 * Check अगर there was an event alपढ़ोy pending on the eventfd
	 * beक्रमe we रेजिस्टरed, and trigger it as अगर we didn't miss it.
	 */
	events = vfs_poll(f.file, &irqfd->pt);

	अगर (events & EPOLLIN)
		schedule_work(&irqfd->inject);

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_BYPASS
	अगर (kvm_arch_has_irq_bypass()) अणु
		irqfd->consumer.token = (व्योम *)irqfd->eventfd;
		irqfd->consumer.add_producer = kvm_arch_irq_bypass_add_producer;
		irqfd->consumer.del_producer = kvm_arch_irq_bypass_del_producer;
		irqfd->consumer.stop = kvm_arch_irq_bypass_stop;
		irqfd->consumer.start = kvm_arch_irq_bypass_start;
		ret = irq_bypass_रेजिस्टर_consumer(&irqfd->consumer);
		अगर (ret)
			pr_info("irq bypass consumer (token %p) registration fails: %d\n",
				irqfd->consumer.token, ret);
	पूर्ण
#पूर्ण_अगर

	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);

	/*
	 * करो not drop the file until the irqfd is fully initialized, otherwise
	 * we might race against the EPOLLHUP
	 */
	fdput(f);
	वापस 0;

fail:
	अगर (irqfd->resampler)
		irqfd_resampler_shutकरोwn(irqfd);

	अगर (resamplefd && !IS_ERR(resamplefd))
		eventfd_ctx_put(resamplefd);

	अगर (eventfd && !IS_ERR(eventfd))
		eventfd_ctx_put(eventfd);

	fdput(f);

out:
	kमुक्त(irqfd);
	वापस ret;
पूर्ण

bool kvm_irq_has_notअगरier(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin)
अणु
	काष्ठा kvm_irq_ack_notअगरier *kian;
	पूर्णांक gsi, idx;

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	gsi = kvm_irq_map_chip_pin(kvm, irqchip, pin);
	अगर (gsi != -1)
		hlist_क्रम_each_entry_rcu(kian, &kvm->irq_ack_notअगरier_list,
					 link)
			अगर (kian->gsi == gsi) अणु
				srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
				वापस true;
			पूर्ण

	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_irq_has_notअगरier);

व्योम kvm_notअगरy_acked_gsi(काष्ठा kvm *kvm, पूर्णांक gsi)
अणु
	काष्ठा kvm_irq_ack_notअगरier *kian;

	hlist_क्रम_each_entry_rcu(kian, &kvm->irq_ack_notअगरier_list,
				 link)
		अगर (kian->gsi == gsi)
			kian->irq_acked(kian);
पूर्ण

व्योम kvm_notअगरy_acked_irq(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin)
अणु
	पूर्णांक gsi, idx;

	trace_kvm_ack_irq(irqchip, pin);

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	gsi = kvm_irq_map_chip_pin(kvm, irqchip, pin);
	अगर (gsi != -1)
		kvm_notअगरy_acked_gsi(kvm, gsi);
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
पूर्ण

व्योम kvm_रेजिस्टर_irq_ack_notअगरier(काष्ठा kvm *kvm,
				   काष्ठा kvm_irq_ack_notअगरier *kian)
अणु
	mutex_lock(&kvm->irq_lock);
	hlist_add_head_rcu(&kian->link, &kvm->irq_ack_notअगरier_list);
	mutex_unlock(&kvm->irq_lock);
	kvm_arch_post_irq_ack_notअगरier_list_update(kvm);
पूर्ण

व्योम kvm_unरेजिस्टर_irq_ack_notअगरier(काष्ठा kvm *kvm,
				    काष्ठा kvm_irq_ack_notअगरier *kian)
अणु
	mutex_lock(&kvm->irq_lock);
	hlist_del_init_rcu(&kian->link);
	mutex_unlock(&kvm->irq_lock);
	synchronize_srcu(&kvm->irq_srcu);
	kvm_arch_post_irq_ack_notअगरier_list_update(kvm);
पूर्ण
#पूर्ण_अगर

व्योम
kvm_eventfd_init(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
	spin_lock_init(&kvm->irqfds.lock);
	INIT_LIST_HEAD(&kvm->irqfds.items);
	INIT_LIST_HEAD(&kvm->irqfds.resampler_list);
	mutex_init(&kvm->irqfds.resampler_lock);
#पूर्ण_अगर
	INIT_LIST_HEAD(&kvm->ioeventfds);
पूर्ण

#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
/*
 * shutकरोwn any irqfd's that match fd+gsi
 */
अटल पूर्णांक
kvm_irqfd_deassign(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd, *पंचांगp;
	काष्ठा eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	spin_lock_irq(&kvm->irqfds.lock);

	list_क्रम_each_entry_safe(irqfd, पंचांगp, &kvm->irqfds.items, list) अणु
		अगर (irqfd->eventfd == eventfd && irqfd->gsi == args->gsi) अणु
			/*
			 * This clearing of irq_entry.type is needed क्रम when
			 * another thपढ़ो calls kvm_irq_routing_update beक्रमe
			 * we flush workqueue below (we synchronize with
			 * kvm_irq_routing_update using irqfds.lock).
			 */
			ग_लिखो_seqcount_begin(&irqfd->irq_entry_sc);
			irqfd->irq_entry.type = 0;
			ग_लिखो_seqcount_end(&irqfd->irq_entry_sc);
			irqfd_deactivate(irqfd);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&kvm->irqfds.lock);
	eventfd_ctx_put(eventfd);

	/*
	 * Block until we know all outstanding shutकरोwn jobs have completed
	 * so that we guarantee there will not be any more पूर्णांकerrupts on this
	 * gsi once this deassign function वापसs.
	 */
	flush_workqueue(irqfd_cleanup_wq);

	वापस 0;
पूर्ण

पूर्णांक
kvm_irqfd(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	अगर (args->flags & ~(KVM_IRQFD_FLAG_DEASSIGN | KVM_IRQFD_FLAG_RESAMPLE))
		वापस -EINVAL;

	अगर (args->flags & KVM_IRQFD_FLAG_DEASSIGN)
		वापस kvm_irqfd_deassign(kvm, args);

	वापस kvm_irqfd_assign(kvm, args);
पूर्ण

/*
 * This function is called as the kvm VM fd is being released. Shutकरोwn all
 * irqfds that still reमुख्य खोलो
 */
व्योम
kvm_irqfd_release(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd, *पंचांगp;

	spin_lock_irq(&kvm->irqfds.lock);

	list_क्रम_each_entry_safe(irqfd, पंचांगp, &kvm->irqfds.items, list)
		irqfd_deactivate(irqfd);

	spin_unlock_irq(&kvm->irqfds.lock);

	/*
	 * Block until we know all outstanding shutकरोwn jobs have completed
	 * since we करो not take a kvm* reference.
	 */
	flush_workqueue(irqfd_cleanup_wq);

पूर्ण

/*
 * Take note of a change in irq routing.
 * Caller must invoke synchronize_srcu(&kvm->irq_srcu) afterwards.
 */
व्योम kvm_irq_routing_update(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd;

	spin_lock_irq(&kvm->irqfds.lock);

	list_क्रम_each_entry(irqfd, &kvm->irqfds.items, list) अणु
		irqfd_update(kvm, irqfd);

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_BYPASS
		अगर (irqfd->producer) अणु
			पूर्णांक ret = kvm_arch_update_irqfd_routing(
					irqfd->kvm, irqfd->producer->irq,
					irqfd->gsi, 1);
			WARN_ON(ret);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	spin_unlock_irq(&kvm->irqfds.lock);
पूर्ण

/*
 * create a host-wide workqueue क्रम issuing deferred shutकरोwn requests
 * aggregated from all vm* instances. We need our own isolated
 * queue to ease flushing work items when a VM निकासs.
 */
पूर्णांक kvm_irqfd_init(व्योम)
अणु
	irqfd_cleanup_wq = alloc_workqueue("kvm-irqfd-cleanup", 0, 0);
	अगर (!irqfd_cleanup_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम kvm_irqfd_निकास(व्योम)
अणु
	destroy_workqueue(irqfd_cleanup_wq);
पूर्ण
#पूर्ण_अगर

/*
 * --------------------------------------------------------------------
 * ioeventfd: translate a PIO/MMIO memory ग_लिखो to an eventfd संकेत.
 *
 * userspace can रेजिस्टर a PIO/MMIO address with an eventfd क्रम receiving
 * notअगरication when the memory has been touched.
 * --------------------------------------------------------------------
 */

काष्ठा _ioeventfd अणु
	काष्ठा list_head     list;
	u64                  addr;
	पूर्णांक                  length;
	काष्ठा eventfd_ctx  *eventfd;
	u64                  datamatch;
	काष्ठा kvm_io_device dev;
	u8                   bus_idx;
	bool                 wildcard;
पूर्ण;

अटल अंतरभूत काष्ठा _ioeventfd *
to_ioeventfd(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा _ioeventfd, dev);
पूर्ण

अटल व्योम
ioeventfd_release(काष्ठा _ioeventfd *p)
अणु
	eventfd_ctx_put(p->eventfd);
	list_del(&p->list);
	kमुक्त(p);
पूर्ण

अटल bool
ioeventfd_in_range(काष्ठा _ioeventfd *p, gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	u64 _val;

	अगर (addr != p->addr)
		/* address must be precise क्रम a hit */
		वापस false;

	अगर (!p->length)
		/* length = 0 means only look at the address, so always a hit */
		वापस true;

	अगर (len != p->length)
		/* address-range must be precise क्रम a hit */
		वापस false;

	अगर (p->wildcard)
		/* all अन्यथा equal, wildcard is always a hit */
		वापस true;

	/* otherwise, we have to actually compare the data */

	BUG_ON(!IS_ALIGNED((अचिन्हित दीर्घ)val, len));

	चयन (len) अणु
	हाल 1:
		_val = *(u8 *)val;
		अवरोध;
	हाल 2:
		_val = *(u16 *)val;
		अवरोध;
	हाल 4:
		_val = *(u32 *)val;
		अवरोध;
	हाल 8:
		_val = *(u64 *)val;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस _val == p->datamatch;
पूर्ण

/* MMIO/PIO ग_लिखोs trigger an event अगर the addr/val match */
अटल पूर्णांक
ioeventfd_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *this, gpa_t addr,
		पूर्णांक len, स्थिर व्योम *val)
अणु
	काष्ठा _ioeventfd *p = to_ioeventfd(this);

	अगर (!ioeventfd_in_range(p, addr, len, val))
		वापस -EOPNOTSUPP;

	eventfd_संकेत(p->eventfd, 1);
	वापस 0;
पूर्ण

/*
 * This function is called as KVM is completely shutting करोwn.  We करो not
 * need to worry about locking just nuke anything we have as quickly as possible
 */
अटल व्योम
ioeventfd_deकाष्ठाor(काष्ठा kvm_io_device *this)
अणु
	काष्ठा _ioeventfd *p = to_ioeventfd(this);

	ioeventfd_release(p);
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops ioeventfd_ops = अणु
	.ग_लिखो      = ioeventfd_ग_लिखो,
	.deकाष्ठाor = ioeventfd_deकाष्ठाor,
पूर्ण;

/* assumes kvm->slots_lock held */
अटल bool
ioeventfd_check_collision(काष्ठा kvm *kvm, काष्ठा _ioeventfd *p)
अणु
	काष्ठा _ioeventfd *_p;

	list_क्रम_each_entry(_p, &kvm->ioeventfds, list)
		अगर (_p->bus_idx == p->bus_idx &&
		    _p->addr == p->addr &&
		    (!_p->length || !p->length ||
		     (_p->length == p->length &&
		      (_p->wildcard || p->wildcard ||
		       _p->datamatch == p->datamatch))))
			वापस true;

	वापस false;
पूर्ण

अटल क्रमागत kvm_bus ioeventfd_bus_from_flags(__u32 flags)
अणु
	अगर (flags & KVM_IOEVENTFD_FLAG_PIO)
		वापस KVM_PIO_BUS;
	अगर (flags & KVM_IOEVENTFD_FLAG_VIRTIO_CCW_NOTIFY)
		वापस KVM_VIRTIO_CCW_NOTIFY_BUS;
	वापस KVM_MMIO_BUS;
पूर्ण

अटल पूर्णांक kvm_assign_ioeventfd_idx(काष्ठा kvm *kvm,
				क्रमागत kvm_bus bus_idx,
				काष्ठा kvm_ioeventfd *args)
अणु

	काष्ठा eventfd_ctx *eventfd;
	काष्ठा _ioeventfd *p;
	पूर्णांक ret;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	p = kzalloc(माप(*p), GFP_KERNEL_ACCOUNT);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	INIT_LIST_HEAD(&p->list);
	p->addr    = args->addr;
	p->bus_idx = bus_idx;
	p->length  = args->len;
	p->eventfd = eventfd;

	/* The datamatch feature is optional, otherwise this is a wildcard */
	अगर (args->flags & KVM_IOEVENTFD_FLAG_DATAMATCH)
		p->datamatch = args->datamatch;
	अन्यथा
		p->wildcard = true;

	mutex_lock(&kvm->slots_lock);

	/* Verअगरy that there isn't a match alपढ़ोy */
	अगर (ioeventfd_check_collision(kvm, p)) अणु
		ret = -EEXIST;
		जाओ unlock_fail;
	पूर्ण

	kvm_iodevice_init(&p->dev, &ioeventfd_ops);

	ret = kvm_io_bus_रेजिस्टर_dev(kvm, bus_idx, p->addr, p->length,
				      &p->dev);
	अगर (ret < 0)
		जाओ unlock_fail;

	kvm_get_bus(kvm, bus_idx)->ioeventfd_count++;
	list_add_tail(&p->list, &kvm->ioeventfds);

	mutex_unlock(&kvm->slots_lock);

	वापस 0;

unlock_fail:
	mutex_unlock(&kvm->slots_lock);

fail:
	kमुक्त(p);
	eventfd_ctx_put(eventfd);

	वापस ret;
पूर्ण

अटल पूर्णांक
kvm_deassign_ioeventfd_idx(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx,
			   काष्ठा kvm_ioeventfd *args)
अणु
	काष्ठा _ioeventfd        *p, *पंचांगp;
	काष्ठा eventfd_ctx       *eventfd;
	काष्ठा kvm_io_bus	 *bus;
	पूर्णांक                       ret = -ENOENT;
	bool                      wildcard;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	wildcard = !(args->flags & KVM_IOEVENTFD_FLAG_DATAMATCH);

	mutex_lock(&kvm->slots_lock);

	list_क्रम_each_entry_safe(p, पंचांगp, &kvm->ioeventfds, list) अणु

		अगर (p->bus_idx != bus_idx ||
		    p->eventfd != eventfd  ||
		    p->addr != args->addr  ||
		    p->length != args->len ||
		    p->wildcard != wildcard)
			जारी;

		अगर (!p->wildcard && p->datamatch != args->datamatch)
			जारी;

		kvm_io_bus_unरेजिस्टर_dev(kvm, bus_idx, &p->dev);
		bus = kvm_get_bus(kvm, bus_idx);
		अगर (bus)
			bus->ioeventfd_count--;
		ioeventfd_release(p);
		ret = 0;
		अवरोध;
	पूर्ण

	mutex_unlock(&kvm->slots_lock);

	eventfd_ctx_put(eventfd);

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_deassign_ioeventfd(काष्ठा kvm *kvm, काष्ठा kvm_ioeventfd *args)
अणु
	क्रमागत kvm_bus bus_idx = ioeventfd_bus_from_flags(args->flags);
	पूर्णांक ret = kvm_deassign_ioeventfd_idx(kvm, bus_idx, args);

	अगर (!args->len && bus_idx == KVM_MMIO_BUS)
		kvm_deassign_ioeventfd_idx(kvm, KVM_FAST_MMIO_BUS, args);

	वापस ret;
पूर्ण

अटल पूर्णांक
kvm_assign_ioeventfd(काष्ठा kvm *kvm, काष्ठा kvm_ioeventfd *args)
अणु
	क्रमागत kvm_bus              bus_idx;
	पूर्णांक ret;

	bus_idx = ioeventfd_bus_from_flags(args->flags);
	/* must be natural-word sized, or 0 to ignore length */
	चयन (args->len) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* check क्रम range overflow */
	अगर (args->addr + args->len < args->addr)
		वापस -EINVAL;

	/* check क्रम extra flags that we करोn't understand */
	अगर (args->flags & ~KVM_IOEVENTFD_VALID_FLAG_MASK)
		वापस -EINVAL;

	/* ioeventfd with no length can't be combined with DATAMATCH */
	अगर (!args->len && (args->flags & KVM_IOEVENTFD_FLAG_DATAMATCH))
		वापस -EINVAL;

	ret = kvm_assign_ioeventfd_idx(kvm, bus_idx, args);
	अगर (ret)
		जाओ fail;

	/* When length is ignored, MMIO is also put on a separate bus, क्रम
	 * faster lookups.
	 */
	अगर (!args->len && bus_idx == KVM_MMIO_BUS) अणु
		ret = kvm_assign_ioeventfd_idx(kvm, KVM_FAST_MMIO_BUS, args);
		अगर (ret < 0)
			जाओ fast_fail;
	पूर्ण

	वापस 0;

fast_fail:
	kvm_deassign_ioeventfd_idx(kvm, bus_idx, args);
fail:
	वापस ret;
पूर्ण

पूर्णांक
kvm_ioeventfd(काष्ठा kvm *kvm, काष्ठा kvm_ioeventfd *args)
अणु
	अगर (args->flags & KVM_IOEVENTFD_FLAG_DEASSIGN)
		वापस kvm_deassign_ioeventfd(kvm, args);

	वापस kvm_assign_ioeventfd(kvm, args);
पूर्ण
