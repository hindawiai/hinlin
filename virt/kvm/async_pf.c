<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kvm asynchronous fault support
 *
 * Copyright 2010 Red Hat, Inc.
 *
 * Author:
 *      Gleb Natapov <gleb@redhat.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/sched/mm.h>

#समावेश "async_pf.h"
#समावेश <trace/events/kvm.h>

अटल काष्ठा kmem_cache *async_pf_cache;

पूर्णांक kvm_async_pf_init(व्योम)
अणु
	async_pf_cache = KMEM_CACHE(kvm_async_pf, 0);

	अगर (!async_pf_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम kvm_async_pf_deinit(व्योम)
अणु
	kmem_cache_destroy(async_pf_cache);
	async_pf_cache = शून्य;
पूर्ण

व्योम kvm_async_pf_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	INIT_LIST_HEAD(&vcpu->async_pf.करोne);
	INIT_LIST_HEAD(&vcpu->async_pf.queue);
	spin_lock_init(&vcpu->async_pf.lock);
पूर्ण

अटल व्योम async_pf_execute(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvm_async_pf *apf =
		container_of(work, काष्ठा kvm_async_pf, work);
	काष्ठा mm_काष्ठा *mm = apf->mm;
	काष्ठा kvm_vcpu *vcpu = apf->vcpu;
	अचिन्हित दीर्घ addr = apf->addr;
	gpa_t cr2_or_gpa = apf->cr2_or_gpa;
	पूर्णांक locked = 1;
	bool first;

	might_sleep();

	/*
	 * This work is run asynchronously to the task which owns
	 * mm and might be करोne in another context, so we must
	 * access remotely.
	 */
	mmap_पढ़ो_lock(mm);
	get_user_pages_remote(mm, addr, 1, FOLL_WRITE, शून्य, शून्य,
			&locked);
	अगर (locked)
		mmap_पढ़ो_unlock(mm);

	अगर (IS_ENABLED(CONFIG_KVM_ASYNC_PF_SYNC))
		kvm_arch_async_page_present(vcpu, apf);

	spin_lock(&vcpu->async_pf.lock);
	first = list_empty(&vcpu->async_pf.करोne);
	list_add_tail(&apf->link, &vcpu->async_pf.करोne);
	apf->vcpu = शून्य;
	spin_unlock(&vcpu->async_pf.lock);

	अगर (!IS_ENABLED(CONFIG_KVM_ASYNC_PF_SYNC) && first)
		kvm_arch_async_page_present_queued(vcpu);

	/*
	 * apf may be मुक्तd by kvm_check_async_pf_completion() after
	 * this poपूर्णांक
	 */

	trace_kvm_async_pf_completed(addr, cr2_or_gpa);

	rcuरुको_wake_up(&vcpu->रुको);

	mmput(mm);
	kvm_put_kvm(vcpu->kvm);
पूर्ण

व्योम kvm_clear_async_pf_completion_queue(काष्ठा kvm_vcpu *vcpu)
अणु
	spin_lock(&vcpu->async_pf.lock);

	/* cancel outstanding work queue item */
	जबतक (!list_empty(&vcpu->async_pf.queue)) अणु
		काष्ठा kvm_async_pf *work =
			list_first_entry(&vcpu->async_pf.queue,
					 typeof(*work), queue);
		list_del(&work->queue);

		/*
		 * We know it's present in vcpu->async_pf.करोne, करो
		 * nothing here.
		 */
		अगर (!work->vcpu)
			जारी;

		spin_unlock(&vcpu->async_pf.lock);
#अगर_घोषित CONFIG_KVM_ASYNC_PF_SYNC
		flush_work(&work->work);
#अन्यथा
		अगर (cancel_work_sync(&work->work)) अणु
			mmput(work->mm);
			kvm_put_kvm(vcpu->kvm); /* == work->vcpu->kvm */
			kmem_cache_मुक्त(async_pf_cache, work);
		पूर्ण
#पूर्ण_अगर
		spin_lock(&vcpu->async_pf.lock);
	पूर्ण

	जबतक (!list_empty(&vcpu->async_pf.करोne)) अणु
		काष्ठा kvm_async_pf *work =
			list_first_entry(&vcpu->async_pf.करोne,
					 typeof(*work), link);
		list_del(&work->link);
		kmem_cache_मुक्त(async_pf_cache, work);
	पूर्ण
	spin_unlock(&vcpu->async_pf.lock);

	vcpu->async_pf.queued = 0;
पूर्ण

व्योम kvm_check_async_pf_completion(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_async_pf *work;

	जबतक (!list_empty_careful(&vcpu->async_pf.करोne) &&
	      kvm_arch_can_dequeue_async_page_present(vcpu)) अणु
		spin_lock(&vcpu->async_pf.lock);
		work = list_first_entry(&vcpu->async_pf.करोne, typeof(*work),
					      link);
		list_del(&work->link);
		spin_unlock(&vcpu->async_pf.lock);

		kvm_arch_async_page_पढ़ोy(vcpu, work);
		अगर (!IS_ENABLED(CONFIG_KVM_ASYNC_PF_SYNC))
			kvm_arch_async_page_present(vcpu, work);

		list_del(&work->queue);
		vcpu->async_pf.queued--;
		kmem_cache_मुक्त(async_pf_cache, work);
	पूर्ण
पूर्ण

/*
 * Try to schedule a job to handle page fault asynchronously. Returns 'true' on
 * success, 'false' on failure (page fault has to be handled synchronously).
 */
bool kvm_setup_async_pf(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
			अचिन्हित दीर्घ hva, काष्ठा kvm_arch_async_pf *arch)
अणु
	काष्ठा kvm_async_pf *work;

	अगर (vcpu->async_pf.queued >= ASYNC_PF_PER_VCPU)
		वापस false;

	/* Arch specअगरic code should not करो async PF in this हाल */
	अगर (unlikely(kvm_is_error_hva(hva)))
		वापस false;

	/*
	 * करो alloc noरुको since अगर we are going to sleep anyway we
	 * may as well sleep faulting in page
	 */
	work = kmem_cache_zalloc(async_pf_cache, GFP_NOWAIT | __GFP_NOWARN);
	अगर (!work)
		वापस false;

	work->wakeup_all = false;
	work->vcpu = vcpu;
	work->cr2_or_gpa = cr2_or_gpa;
	work->addr = hva;
	work->arch = *arch;
	work->mm = current->mm;
	mmget(work->mm);
	kvm_get_kvm(work->vcpu->kvm);

	INIT_WORK(&work->work, async_pf_execute);

	list_add_tail(&work->queue, &vcpu->async_pf.queue);
	vcpu->async_pf.queued++;
	work->notpresent_injected = kvm_arch_async_page_not_present(vcpu, work);

	schedule_work(&work->work);

	वापस true;
पूर्ण

पूर्णांक kvm_async_pf_wakeup_all(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_async_pf *work;
	bool first;

	अगर (!list_empty_careful(&vcpu->async_pf.करोne))
		वापस 0;

	work = kmem_cache_zalloc(async_pf_cache, GFP_ATOMIC);
	अगर (!work)
		वापस -ENOMEM;

	work->wakeup_all = true;
	INIT_LIST_HEAD(&work->queue); /* क्रम list_del to work */

	spin_lock(&vcpu->async_pf.lock);
	first = list_empty(&vcpu->async_pf.करोne);
	list_add_tail(&work->link, &vcpu->async_pf.करोne);
	spin_unlock(&vcpu->async_pf.lock);

	अगर (!IS_ENABLED(CONFIG_KVM_ASYNC_PF_SYNC) && first)
		kvm_arch_async_page_present_queued(vcpu);

	vcpu->async_pf.queued++;
	वापस 0;
पूर्ण
