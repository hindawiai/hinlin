<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * This module enables machines with Intel VT-x extensions to run भव
 * machines without emulation or binary translation.
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Avi Kivity   <avi@qumranet.com>
 *   Yaniv Kamay  <yaniv@qumranet.com>
 */

#समावेश <kvm/iodev.h>

#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/percpu.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/reboot.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/file.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/profile.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mman.h>
#समावेश <linux/swap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/compat.h>
#समावेश <linux/srcu.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/पन.स>
#समावेश <linux/lockdep.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ioctl.h>
#समावेश <linux/uaccess.h>

#समावेश "coalesced_mmio.h"
#समावेश "async_pf.h"
#समावेश "mmu_lock.h"
#समावेश "vfio.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/kvm.h>

#समावेश <linux/kvm_dirty_ring.h>

/* Worst हाल buffer size needed क्रम holding an पूर्णांकeger. */
#घोषणा ITOA_MAX_LEN 12

MODULE_AUTHOR("Qumranet");
MODULE_LICENSE("GPL");

/* Architectures should define their poll value according to the halt latency */
अचिन्हित पूर्णांक halt_poll_ns = KVM_HALT_POLL_NS_DEFAULT;
module_param(halt_poll_ns, uपूर्णांक, 0644);
EXPORT_SYMBOL_GPL(halt_poll_ns);

/* Default द्विगुनs per-vcpu halt_poll_ns. */
अचिन्हित पूर्णांक halt_poll_ns_grow = 2;
module_param(halt_poll_ns_grow, uपूर्णांक, 0644);
EXPORT_SYMBOL_GPL(halt_poll_ns_grow);

/* The start value to grow halt_poll_ns from */
अचिन्हित पूर्णांक halt_poll_ns_grow_start = 10000; /* 10us */
module_param(halt_poll_ns_grow_start, uपूर्णांक, 0644);
EXPORT_SYMBOL_GPL(halt_poll_ns_grow_start);

/* Default resets per-vcpu halt_poll_ns . */
अचिन्हित पूर्णांक halt_poll_ns_shrink;
module_param(halt_poll_ns_shrink, uपूर्णांक, 0644);
EXPORT_SYMBOL_GPL(halt_poll_ns_shrink);

/*
 * Ordering of locks:
 *
 *	kvm->lock --> kvm->slots_lock --> kvm->irq_lock
 */

DEFINE_MUTEX(kvm_lock);
अटल DEFINE_RAW_SPINLOCK(kvm_count_lock);
LIST_HEAD(vm_list);

अटल cpumask_var_t cpus_hardware_enabled;
अटल पूर्णांक kvm_usage_count;
अटल atomic_t hardware_enable_failed;

अटल काष्ठा kmem_cache *kvm_vcpu_cache;

अटल __पढ़ो_mostly काष्ठा preempt_ops kvm_preempt_ops;
अटल DEFINE_PER_CPU(काष्ठा kvm_vcpu *, kvm_running_vcpu);

काष्ठा dentry *kvm_debugfs_dir;
EXPORT_SYMBOL_GPL(kvm_debugfs_dir);

अटल पूर्णांक kvm_debugfs_num_entries;
अटल स्थिर काष्ठा file_operations stat_fops_per_vm;

अटल दीर्घ kvm_vcpu_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ioctl,
			   अचिन्हित दीर्घ arg);
#अगर_घोषित CONFIG_KVM_COMPAT
अटल दीर्घ kvm_vcpu_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ioctl,
				  अचिन्हित दीर्घ arg);
#घोषणा KVM_COMPAT(c)	.compat_ioctl	= (c)
#अन्यथा
/*
 * For architectures that करोn't implement a compat infraकाष्ठाure,
 * aकरोpt a द्विगुन line of defense:
 * - Prevent a compat task from खोलोing /dev/kvm
 * - If the खोलो has been करोne by a 64bit task, and the KVM fd
 *   passed to a compat task, let the ioctls fail.
 */
अटल दीर्घ kvm_no_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ioctl,
				अचिन्हित दीर्घ arg) अणु वापस -EINVAL; पूर्ण

अटल पूर्णांक kvm_no_compat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस is_compat_task() ? -ENODEV : 0;
पूर्ण
#घोषणा KVM_COMPAT(c)	.compat_ioctl	= kvm_no_compat_ioctl,	\
			.खोलो		= kvm_no_compat_खोलो
#पूर्ण_अगर
अटल पूर्णांक hardware_enable_all(व्योम);
अटल व्योम hardware_disable_all(व्योम);

अटल व्योम kvm_io_bus_destroy(काष्ठा kvm_io_bus *bus);

__visible bool kvm_rebooting;
EXPORT_SYMBOL_GPL(kvm_rebooting);

#घोषणा KVM_EVENT_CREATE_VM 0
#घोषणा KVM_EVENT_DESTROY_VM 1
अटल व्योम kvm_uevent_notअगरy_change(अचिन्हित पूर्णांक type, काष्ठा kvm *kvm);
अटल अचिन्हित दीर्घ दीर्घ kvm_createvm_count;
अटल अचिन्हित दीर्घ दीर्घ kvm_active_vms;

__weak व्योम kvm_arch_mmu_notअगरier_invalidate_range(काष्ठा kvm *kvm,
						   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

bool kvm_is_zone_device_pfn(kvm_pfn_t pfn)
अणु
	/*
	 * The metadata used by is_zone_device_page() to determine whether or
	 * not a page is ZONE_DEVICE is guaranteed to be valid अगर and only अगर
	 * the device has been pinned, e.g. by get_user_pages().  WARN अगर the
	 * page_count() is zero to help detect bad usage of this helper.
	 */
	अगर (!pfn_valid(pfn) || WARN_ON_ONCE(!page_count(pfn_to_page(pfn))))
		वापस false;

	वापस is_zone_device_page(pfn_to_page(pfn));
पूर्ण

bool kvm_is_reserved_pfn(kvm_pfn_t pfn)
अणु
	/*
	 * ZONE_DEVICE pages currently set PG_reserved, but from a refcounting
	 * perspective they are "normal" pages, albeit with slightly dअगरferent
	 * usage rules.
	 */
	अगर (pfn_valid(pfn))
		वापस PageReserved(pfn_to_page(pfn)) &&
		       !is_zero_pfn(pfn) &&
		       !kvm_is_zone_device_pfn(pfn);

	वापस true;
पूर्ण

bool kvm_is_transparent_hugepage(kvm_pfn_t pfn)
अणु
	काष्ठा page *page = pfn_to_page(pfn);

	अगर (!PageTransCompoundMap(page))
		वापस false;

	वापस is_transparent_hugepage(compound_head(page));
पूर्ण

/*
 * Switches to specअगरied vcpu, until a matching vcpu_put()
 */
व्योम vcpu_load(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cpu = get_cpu();

	__this_cpu_ग_लिखो(kvm_running_vcpu, vcpu);
	preempt_notअगरier_रेजिस्टर(&vcpu->preempt_notअगरier);
	kvm_arch_vcpu_load(vcpu, cpu);
	put_cpu();
पूर्ण
EXPORT_SYMBOL_GPL(vcpu_load);

व्योम vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	kvm_arch_vcpu_put(vcpu);
	preempt_notअगरier_unरेजिस्टर(&vcpu->preempt_notअगरier);
	__this_cpu_ग_लिखो(kvm_running_vcpu, शून्य);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(vcpu_put);

/* TODO: merge with kvm_arch_vcpu_should_kick */
अटल bool kvm_request_needs_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित req)
अणु
	पूर्णांक mode = kvm_vcpu_निकासing_guest_mode(vcpu);

	/*
	 * We need to रुको क्रम the VCPU to reenable पूर्णांकerrupts and get out of
	 * READING_SHADOW_PAGE_TABLES mode.
	 */
	अगर (req & KVM_REQUEST_WAIT)
		वापस mode != OUTSIDE_GUEST_MODE;

	/*
	 * Need to kick a running VCPU, but otherwise there is nothing to करो.
	 */
	वापस mode == IN_GUEST_MODE;
पूर्ण

अटल व्योम ack_flush(व्योम *_completed)
अणु
पूर्ण

अटल अंतरभूत bool kvm_kick_many_cpus(स्थिर काष्ठा cpumask *cpus, bool रुको)
अणु
	अगर (unlikely(!cpus))
		cpus = cpu_online_mask;

	अगर (cpumask_empty(cpus))
		वापस false;

	smp_call_function_many(cpus, ack_flush, शून्य, रुको);
	वापस true;
पूर्ण

bool kvm_make_vcpus_request_mask(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req,
				 काष्ठा kvm_vcpu *except,
				 अचिन्हित दीर्घ *vcpu_biपंचांगap, cpumask_var_t पंचांगp)
अणु
	पूर्णांक i, cpu, me;
	काष्ठा kvm_vcpu *vcpu;
	bool called;

	me = get_cpu();

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर ((vcpu_biपंचांगap && !test_bit(i, vcpu_biपंचांगap)) ||
		    vcpu == except)
			जारी;

		kvm_make_request(req, vcpu);
		cpu = vcpu->cpu;

		अगर (!(req & KVM_REQUEST_NO_WAKEUP) && kvm_vcpu_wake_up(vcpu))
			जारी;

		अगर (पंचांगp != शून्य && cpu != -1 && cpu != me &&
		    kvm_request_needs_ipi(vcpu, req))
			__cpumask_set_cpu(cpu, पंचांगp);
	पूर्ण

	called = kvm_kick_many_cpus(पंचांगp, !!(req & KVM_REQUEST_WAIT));
	put_cpu();

	वापस called;
पूर्ण

bool kvm_make_all_cpus_request_except(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req,
				      काष्ठा kvm_vcpu *except)
अणु
	cpumask_var_t cpus;
	bool called;

	zalloc_cpumask_var(&cpus, GFP_ATOMIC);

	called = kvm_make_vcpus_request_mask(kvm, req, except, शून्य, cpus);

	मुक्त_cpumask_var(cpus);
	वापस called;
पूर्ण

bool kvm_make_all_cpus_request(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req)
अणु
	वापस kvm_make_all_cpus_request_except(kvm, req, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_make_all_cpus_request);

#अगर_अघोषित CONFIG_HAVE_KVM_ARCH_TLB_FLUSH_ALL
व्योम kvm_flush_remote_tlbs(काष्ठा kvm *kvm)
अणु
	/*
	 * Read tlbs_dirty beक्रमe setting KVM_REQ_TLB_FLUSH in
	 * kvm_make_all_cpus_request.
	 */
	दीर्घ dirty_count = smp_load_acquire(&kvm->tlbs_dirty);

	/*
	 * We want to publish modअगरications to the page tables beक्रमe पढ़ोing
	 * mode. Pairs with a memory barrier in arch-specअगरic code.
	 * - x86: smp_mb__after_srcu_पढ़ो_unlock in vcpu_enter_guest
	 * and smp_mb in walk_shaकरोw_page_lockless_begin/end.
	 * - घातerpc: smp_mb in kvmppc_prepare_to_enter.
	 *
	 * There is alपढ़ोy an smp_mb__after_atomic() beक्रमe
	 * kvm_make_all_cpus_request() पढ़ोs vcpu->mode. We reuse that
	 * barrier here.
	 */
	अगर (!kvm_arch_flush_remote_tlb(kvm)
	    || kvm_make_all_cpus_request(kvm, KVM_REQ_TLB_FLUSH))
		++kvm->stat.remote_tlb_flush;
	cmpxchg(&kvm->tlbs_dirty, dirty_count, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_flush_remote_tlbs);
#पूर्ण_अगर

व्योम kvm_reload_remote_mmus(काष्ठा kvm *kvm)
अणु
	kvm_make_all_cpus_request(kvm, KVM_REQ_MMU_RELOAD);
पूर्ण

#अगर_घोषित KVM_ARCH_NR_OBJS_PER_MEMORY_CACHE
अटल अंतरभूत व्योम *mmu_memory_cache_alloc_obj(काष्ठा kvm_mmu_memory_cache *mc,
					       gfp_t gfp_flags)
अणु
	gfp_flags |= mc->gfp_zero;

	अगर (mc->kmem_cache)
		वापस kmem_cache_alloc(mc->kmem_cache, gfp_flags);
	अन्यथा
		वापस (व्योम *)__get_मुक्त_page(gfp_flags);
पूर्ण

पूर्णांक kvm_mmu_topup_memory_cache(काष्ठा kvm_mmu_memory_cache *mc, पूर्णांक min)
अणु
	व्योम *obj;

	अगर (mc->nobjs >= min)
		वापस 0;
	जबतक (mc->nobjs < ARRAY_SIZE(mc->objects)) अणु
		obj = mmu_memory_cache_alloc_obj(mc, GFP_KERNEL_ACCOUNT);
		अगर (!obj)
			वापस mc->nobjs >= min ? 0 : -ENOMEM;
		mc->objects[mc->nobjs++] = obj;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक kvm_mmu_memory_cache_nr_मुक्त_objects(काष्ठा kvm_mmu_memory_cache *mc)
अणु
	वापस mc->nobjs;
पूर्ण

व्योम kvm_mmu_मुक्त_memory_cache(काष्ठा kvm_mmu_memory_cache *mc)
अणु
	जबतक (mc->nobjs) अणु
		अगर (mc->kmem_cache)
			kmem_cache_मुक्त(mc->kmem_cache, mc->objects[--mc->nobjs]);
		अन्यथा
			मुक्त_page((अचिन्हित दीर्घ)mc->objects[--mc->nobjs]);
	पूर्ण
पूर्ण

व्योम *kvm_mmu_memory_cache_alloc(काष्ठा kvm_mmu_memory_cache *mc)
अणु
	व्योम *p;

	अगर (WARN_ON(!mc->nobjs))
		p = mmu_memory_cache_alloc_obj(mc, GFP_ATOMIC | __GFP_ACCOUNT);
	अन्यथा
		p = mc->objects[--mc->nobjs];
	BUG_ON(!p);
	वापस p;
पूर्ण
#पूर्ण_अगर

अटल व्योम kvm_vcpu_init(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm *kvm, अचिन्हित id)
अणु
	mutex_init(&vcpu->mutex);
	vcpu->cpu = -1;
	vcpu->kvm = kvm;
	vcpu->vcpu_id = id;
	vcpu->pid = शून्य;
	rcuरुको_init(&vcpu->रुको);
	kvm_async_pf_vcpu_init(vcpu);

	vcpu->pre_pcpu = -1;
	INIT_LIST_HEAD(&vcpu->blocked_vcpu_list);

	kvm_vcpu_set_in_spin_loop(vcpu, false);
	kvm_vcpu_set_dy_eligible(vcpu, false);
	vcpu->preempted = false;
	vcpu->पढ़ोy = false;
	preempt_notअगरier_init(&vcpu->preempt_notअगरier, &kvm_preempt_ops);
पूर्ण

व्योम kvm_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_dirty_ring_मुक्त(&vcpu->dirty_ring);
	kvm_arch_vcpu_destroy(vcpu);

	/*
	 * No need क्रम rcu_पढ़ो_lock as VCPU_RUN is the only place that changes
	 * the vcpu->pid poपूर्णांकer, and at deकाष्ठाion समय all file descriptors
	 * are alपढ़ोy gone.
	 */
	put_pid(rcu_dereference_रक्षित(vcpu->pid, 1));

	मुक्त_page((अचिन्हित दीर्घ)vcpu->run);
	kmem_cache_मुक्त(kvm_vcpu_cache, vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_destroy);

#अगर defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
अटल अंतरभूत काष्ठा kvm *mmu_notअगरier_to_kvm(काष्ठा mmu_notअगरier *mn)
अणु
	वापस container_of(mn, काष्ठा kvm, mmu_notअगरier);
पूर्ण

अटल व्योम kvm_mmu_notअगरier_invalidate_range(काष्ठा mmu_notअगरier *mn,
					      काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	kvm_arch_mmu_notअगरier_invalidate_range(kvm, start, end);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
पूर्ण

प्रकार bool (*hva_handler_t)(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);

प्रकार व्योम (*on_lock_fn_t)(काष्ठा kvm *kvm, अचिन्हित दीर्घ start,
			     अचिन्हित दीर्घ end);

काष्ठा kvm_hva_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	pte_t pte;
	hva_handler_t handler;
	on_lock_fn_t on_lock;
	bool flush_on_ret;
	bool may_block;
पूर्ण;

/*
 * Use a dedicated stub instead of शून्य to indicate that there is no callback
 * function/handler.  The compiler technically can't guarantee that a real
 * function will have a non-zero address, and so it will generate code to
 * check क्रम !शून्य, whereas comparing against a stub will be elided at compile
 * समय (unless the compiler is getting दीर्घ in the tooth, e.g. gcc 4.9).
 */
अटल व्योम kvm_null_fn(व्योम)
अणु

पूर्ण
#घोषणा IS_KVM_शून्य_FN(fn) ((fn) == (व्योम *)kvm_null_fn)

अटल __always_अंतरभूत पूर्णांक __kvm_handle_hva_range(काष्ठा kvm *kvm,
						  स्थिर काष्ठा kvm_hva_range *range)
अणु
	bool ret = false, locked = false;
	काष्ठा kvm_gfn_range gfn_range;
	काष्ठा kvm_memory_slot *slot;
	काष्ठा kvm_memslots *slots;
	पूर्णांक i, idx;

	/* A null handler is allowed अगर and only अगर on_lock() is provided. */
	अगर (WARN_ON_ONCE(IS_KVM_शून्य_FN(range->on_lock) &&
			 IS_KVM_शून्य_FN(range->handler)))
		वापस 0;

	idx = srcu_पढ़ो_lock(&kvm->srcu);

	/* The on_lock() path करोes not yet support lock elision. */
	अगर (!IS_KVM_शून्य_FN(range->on_lock)) अणु
		locked = true;
		KVM_MMU_LOCK(kvm);

		range->on_lock(kvm, range->start, range->end);

		अगर (IS_KVM_शून्य_FN(range->handler))
			जाओ out_unlock;
	पूर्ण

	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) अणु
		slots = __kvm_memslots(kvm, i);
		kvm_क्रम_each_memslot(slot, slots) अणु
			अचिन्हित दीर्घ hबहु_शुरू, hबहु_पूर्ण;

			hबहु_शुरू = max(range->start, slot->userspace_addr);
			hबहु_पूर्ण = min(range->end, slot->userspace_addr +
						  (slot->npages << PAGE_SHIFT));
			अगर (hबहु_शुरू >= hबहु_पूर्ण)
				जारी;

			/*
			 * To optimize क्रम the likely हाल where the address
			 * range is covered by zero or one memslots, करोn't
			 * bother making these conditional (to aव्योम ग_लिखोs on
			 * the second or later invocation of the handler).
			 */
			gfn_range.pte = range->pte;
			gfn_range.may_block = range->may_block;

			/*
			 * अणुgfn(page) | page पूर्णांकersects with [hबहु_शुरू, hबहु_पूर्ण)पूर्ण =
			 * अणुgfn_start, gfn_start+1, ..., gfn_end-1पूर्ण.
			 */
			gfn_range.start = hva_to_gfn_memslot(hबहु_शुरू, slot);
			gfn_range.end = hva_to_gfn_memslot(hबहु_पूर्ण + PAGE_SIZE - 1, slot);
			gfn_range.slot = slot;

			अगर (!locked) अणु
				locked = true;
				KVM_MMU_LOCK(kvm);
			पूर्ण
			ret |= range->handler(kvm, &gfn_range);
		पूर्ण
	पूर्ण

	अगर (range->flush_on_ret && (ret || kvm->tlbs_dirty))
		kvm_flush_remote_tlbs(kvm);

out_unlock:
	अगर (locked)
		KVM_MMU_UNLOCK(kvm);

	srcu_पढ़ो_unlock(&kvm->srcu, idx);

	/* The notअगरiers are averse to booleans. :-( */
	वापस (पूर्णांक)ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक kvm_handle_hva_range(काष्ठा mmu_notअगरier *mn,
						अचिन्हित दीर्घ start,
						अचिन्हित दीर्घ end,
						pte_t pte,
						hva_handler_t handler)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	स्थिर काष्ठा kvm_hva_range range = अणु
		.start		= start,
		.end		= end,
		.pte		= pte,
		.handler	= handler,
		.on_lock	= (व्योम *)kvm_null_fn,
		.flush_on_ret	= true,
		.may_block	= false,
	पूर्ण;

	वापस __kvm_handle_hva_range(kvm, &range);
पूर्ण

अटल __always_अंतरभूत पूर्णांक kvm_handle_hva_range_no_flush(काष्ठा mmu_notअगरier *mn,
							 अचिन्हित दीर्घ start,
							 अचिन्हित दीर्घ end,
							 hva_handler_t handler)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	स्थिर काष्ठा kvm_hva_range range = अणु
		.start		= start,
		.end		= end,
		.pte		= __pte(0),
		.handler	= handler,
		.on_lock	= (व्योम *)kvm_null_fn,
		.flush_on_ret	= false,
		.may_block	= false,
	पूर्ण;

	वापस __kvm_handle_hva_range(kvm, &range);
पूर्ण
अटल व्योम kvm_mmu_notअगरier_change_pte(काष्ठा mmu_notअगरier *mn,
					काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ address,
					pte_t pte)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);

	trace_kvm_set_spte_hva(address);

	/*
	 * .change_pte() must be surrounded by .invalidate_range_अणुstart,endपूर्ण(),
	 * and so always runs with an elevated notअगरier count.  This obviates
	 * the need to bump the sequence count.
	 */
	WARN_ON_ONCE(!kvm->mmu_notअगरier_count);

	kvm_handle_hva_range(mn, address, address + 1, pte, kvm_set_spte_gfn);
पूर्ण

अटल व्योम kvm_inc_notअगरier_count(काष्ठा kvm *kvm, अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end)
अणु
	/*
	 * The count increase must become visible at unlock समय as no
	 * spte can be established without taking the mmu_lock and
	 * count is also पढ़ो inside the mmu_lock critical section.
	 */
	kvm->mmu_notअगरier_count++;
	अगर (likely(kvm->mmu_notअगरier_count == 1)) अणु
		kvm->mmu_notअगरier_range_start = start;
		kvm->mmu_notअगरier_range_end = end;
	पूर्ण अन्यथा अणु
		/*
		 * Fully tracking multiple concurrent ranges has dimishing
		 * वापसs. Keep things simple and just find the minimal range
		 * which includes the current and new ranges. As there won't be
		 * enough inक्रमmation to subtract a range after its invalidate
		 * completes, any ranges invalidated concurrently will
		 * accumulate and persist until all outstanding invalidates
		 * complete.
		 */
		kvm->mmu_notअगरier_range_start =
			min(kvm->mmu_notअगरier_range_start, start);
		kvm->mmu_notअगरier_range_end =
			max(kvm->mmu_notअगरier_range_end, end);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_mmu_notअगरier_invalidate_range_start(काष्ठा mmu_notअगरier *mn,
					स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	स्थिर काष्ठा kvm_hva_range hva_range = अणु
		.start		= range->start,
		.end		= range->end,
		.pte		= __pte(0),
		.handler	= kvm_unmap_gfn_range,
		.on_lock	= kvm_inc_notअगरier_count,
		.flush_on_ret	= true,
		.may_block	= mmu_notअगरier_range_blockable(range),
	पूर्ण;

	trace_kvm_unmap_hva_range(range->start, range->end);

	__kvm_handle_hva_range(kvm, &hva_range);

	वापस 0;
पूर्ण

अटल व्योम kvm_dec_notअगरier_count(काष्ठा kvm *kvm, अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end)
अणु
	/*
	 * This sequence increase will notअगरy the kvm page fault that
	 * the page that is going to be mapped in the spte could have
	 * been मुक्तd.
	 */
	kvm->mmu_notअगरier_seq++;
	smp_wmb();
	/*
	 * The above sequence increase must be visible beक्रमe the
	 * below count decrease, which is ensured by the smp_wmb above
	 * in conjunction with the smp_rmb in mmu_notअगरier_retry().
	 */
	kvm->mmu_notअगरier_count--;
पूर्ण

अटल व्योम kvm_mmu_notअगरier_invalidate_range_end(काष्ठा mmu_notअगरier *mn,
					स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	स्थिर काष्ठा kvm_hva_range hva_range = अणु
		.start		= range->start,
		.end		= range->end,
		.pte		= __pte(0),
		.handler	= (व्योम *)kvm_null_fn,
		.on_lock	= kvm_dec_notअगरier_count,
		.flush_on_ret	= false,
		.may_block	= mmu_notअगरier_range_blockable(range),
	पूर्ण;

	__kvm_handle_hva_range(kvm, &hva_range);

	BUG_ON(kvm->mmu_notअगरier_count < 0);
पूर्ण

अटल पूर्णांक kvm_mmu_notअगरier_clear_flush_young(काष्ठा mmu_notअगरier *mn,
					      काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ start,
					      अचिन्हित दीर्घ end)
अणु
	trace_kvm_age_hva(start, end);

	वापस kvm_handle_hva_range(mn, start, end, __pte(0), kvm_age_gfn);
पूर्ण

अटल पूर्णांक kvm_mmu_notअगरier_clear_young(काष्ठा mmu_notअगरier *mn,
					काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ end)
अणु
	trace_kvm_age_hva(start, end);

	/*
	 * Even though we करो not flush TLB, this will still adversely
	 * affect perक्रमmance on pre-Haswell Intel EPT, where there is
	 * no EPT Access Bit to clear so that we have to tear करोwn EPT
	 * tables instead. If we find this unacceptable, we can always
	 * add a parameter to kvm_age_hva so that it effectively करोesn't
	 * करो anything on clear_young.
	 *
	 * Also note that currently we never issue secondary TLB flushes
	 * from clear_young, leaving this job up to the regular प्रणाली
	 * cadence. If we find this inaccurate, we might come up with a
	 * more sophisticated heuristic later.
	 */
	वापस kvm_handle_hva_range_no_flush(mn, start, end, kvm_age_gfn);
पूर्ण

अटल पूर्णांक kvm_mmu_notअगरier_test_young(काष्ठा mmu_notअगरier *mn,
				       काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ address)
अणु
	trace_kvm_test_age_hva(address);

	वापस kvm_handle_hva_range_no_flush(mn, address, address + 1,
					     kvm_test_age_gfn);
पूर्ण

अटल व्योम kvm_mmu_notअगरier_release(काष्ठा mmu_notअगरier *mn,
				     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kvm *kvm = mmu_notअगरier_to_kvm(mn);
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	kvm_arch_flush_shaकरोw_all(kvm);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops kvm_mmu_notअगरier_ops = अणु
	.invalidate_range	= kvm_mmu_notअगरier_invalidate_range,
	.invalidate_range_start	= kvm_mmu_notअगरier_invalidate_range_start,
	.invalidate_range_end	= kvm_mmu_notअगरier_invalidate_range_end,
	.clear_flush_young	= kvm_mmu_notअगरier_clear_flush_young,
	.clear_young		= kvm_mmu_notअगरier_clear_young,
	.test_young		= kvm_mmu_notअगरier_test_young,
	.change_pte		= kvm_mmu_notअगरier_change_pte,
	.release		= kvm_mmu_notअगरier_release,
पूर्ण;

अटल पूर्णांक kvm_init_mmu_notअगरier(काष्ठा kvm *kvm)
अणु
	kvm->mmu_notअगरier.ops = &kvm_mmu_notअगरier_ops;
	वापस mmu_notअगरier_रेजिस्टर(&kvm->mmu_notअगरier, current->mm);
पूर्ण

#अन्यथा  /* !(CONFIG_MMU_NOTIFIER && KVM_ARCH_WANT_MMU_NOTIFIER) */

अटल पूर्णांक kvm_init_mmu_notअगरier(काष्ठा kvm *kvm)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU_NOTIFIER && KVM_ARCH_WANT_MMU_NOTIFIER */

अटल काष्ठा kvm_memslots *kvm_alloc_memslots(व्योम)
अणु
	पूर्णांक i;
	काष्ठा kvm_memslots *slots;

	slots = kvzalloc(माप(काष्ठा kvm_memslots), GFP_KERNEL_ACCOUNT);
	अगर (!slots)
		वापस शून्य;

	क्रम (i = 0; i < KVM_MEM_SLOTS_NUM; i++)
		slots->id_to_index[i] = -1;

	वापस slots;
पूर्ण

अटल व्योम kvm_destroy_dirty_biपंचांगap(काष्ठा kvm_memory_slot *memslot)
अणु
	अगर (!memslot->dirty_biपंचांगap)
		वापस;

	kvमुक्त(memslot->dirty_biपंचांगap);
	memslot->dirty_biपंचांगap = शून्य;
पूर्ण

अटल व्योम kvm_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	kvm_destroy_dirty_biपंचांगap(slot);

	kvm_arch_मुक्त_memslot(kvm, slot);

	slot->flags = 0;
	slot->npages = 0;
पूर्ण

अटल व्योम kvm_मुक्त_memslots(काष्ठा kvm *kvm, काष्ठा kvm_memslots *slots)
अणु
	काष्ठा kvm_memory_slot *memslot;

	अगर (!slots)
		वापस;

	kvm_क्रम_each_memslot(memslot, slots)
		kvm_मुक्त_memslot(kvm, memslot);

	kvमुक्त(slots);
पूर्ण

अटल व्योम kvm_destroy_vm_debugfs(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;

	अगर (!kvm->debugfs_dentry)
		वापस;

	debugfs_हटाओ_recursive(kvm->debugfs_dentry);

	अगर (kvm->debugfs_stat_data) अणु
		क्रम (i = 0; i < kvm_debugfs_num_entries; i++)
			kमुक्त(kvm->debugfs_stat_data[i]);
		kमुक्त(kvm->debugfs_stat_data);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_create_vm_debugfs(काष्ठा kvm *kvm, पूर्णांक fd)
अणु
	अक्षर dir_name[ITOA_MAX_LEN * 2];
	काष्ठा kvm_stat_data *stat_data;
	काष्ठा kvm_stats_debugfs_item *p;

	अगर (!debugfs_initialized())
		वापस 0;

	snम_लिखो(dir_name, माप(dir_name), "%d-%d", task_pid_nr(current), fd);
	kvm->debugfs_dentry = debugfs_create_dir(dir_name, kvm_debugfs_dir);

	kvm->debugfs_stat_data = kसुस्मृति(kvm_debugfs_num_entries,
					 माप(*kvm->debugfs_stat_data),
					 GFP_KERNEL_ACCOUNT);
	अगर (!kvm->debugfs_stat_data)
		वापस -ENOMEM;

	क्रम (p = debugfs_entries; p->name; p++) अणु
		stat_data = kzalloc(माप(*stat_data), GFP_KERNEL_ACCOUNT);
		अगर (!stat_data)
			वापस -ENOMEM;

		stat_data->kvm = kvm;
		stat_data->dbgfs_item = p;
		kvm->debugfs_stat_data[p - debugfs_entries] = stat_data;
		debugfs_create_file(p->name, KVM_DBGFS_GET_MODE(p),
				    kvm->debugfs_dentry, stat_data,
				    &stat_fops_per_vm);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Called after the VM is otherwise initialized, but just beक्रमe adding it to
 * the vm_list.
 */
पूर्णांक __weak kvm_arch_post_init_vm(काष्ठा kvm *kvm)
अणु
	वापस 0;
पूर्ण

/*
 * Called just after removing the VM from the vm_list, but beक्रमe करोing any
 * other deकाष्ठाion.
 */
व्योम __weak kvm_arch_pre_destroy_vm(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल काष्ठा kvm *kvm_create_vm(अचिन्हित दीर्घ type)
अणु
	काष्ठा kvm *kvm = kvm_arch_alloc_vm();
	पूर्णांक r = -ENOMEM;
	पूर्णांक i;

	अगर (!kvm)
		वापस ERR_PTR(-ENOMEM);

	KVM_MMU_LOCK_INIT(kvm);
	mmgrab(current->mm);
	kvm->mm = current->mm;
	kvm_eventfd_init(kvm);
	mutex_init(&kvm->lock);
	mutex_init(&kvm->irq_lock);
	mutex_init(&kvm->slots_lock);
	INIT_LIST_HEAD(&kvm->devices);

	BUILD_BUG_ON(KVM_MEM_SLOTS_NUM > लघु_उच्च);

	अगर (init_srcu_काष्ठा(&kvm->srcu))
		जाओ out_err_no_srcu;
	अगर (init_srcu_काष्ठा(&kvm->irq_srcu))
		जाओ out_err_no_irq_srcu;

	refcount_set(&kvm->users_count, 1);
	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) अणु
		काष्ठा kvm_memslots *slots = kvm_alloc_memslots();

		अगर (!slots)
			जाओ out_err_no_arch_destroy_vm;
		/* Generations must be dअगरferent क्रम each address space. */
		slots->generation = i;
		rcu_assign_poपूर्णांकer(kvm->memslots[i], slots);
	पूर्ण

	क्रम (i = 0; i < KVM_NR_BUSES; i++) अणु
		rcu_assign_poपूर्णांकer(kvm->buses[i],
			kzalloc(माप(काष्ठा kvm_io_bus), GFP_KERNEL_ACCOUNT));
		अगर (!kvm->buses[i])
			जाओ out_err_no_arch_destroy_vm;
	पूर्ण

	kvm->max_halt_poll_ns = halt_poll_ns;

	r = kvm_arch_init_vm(kvm, type);
	अगर (r)
		जाओ out_err_no_arch_destroy_vm;

	r = hardware_enable_all();
	अगर (r)
		जाओ out_err_no_disable;

#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
	INIT_HLIST_HEAD(&kvm->irq_ack_notअगरier_list);
#पूर्ण_अगर

	r = kvm_init_mmu_notअगरier(kvm);
	अगर (r)
		जाओ out_err_no_mmu_notअगरier;

	r = kvm_arch_post_init_vm(kvm);
	अगर (r)
		जाओ out_err;

	mutex_lock(&kvm_lock);
	list_add(&kvm->vm_list, &vm_list);
	mutex_unlock(&kvm_lock);

	preempt_notअगरier_inc();

	वापस kvm;

out_err:
#अगर defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	अगर (kvm->mmu_notअगरier.ops)
		mmu_notअगरier_unरेजिस्टर(&kvm->mmu_notअगरier, current->mm);
#पूर्ण_अगर
out_err_no_mmu_notअगरier:
	hardware_disable_all();
out_err_no_disable:
	kvm_arch_destroy_vm(kvm);
out_err_no_arch_destroy_vm:
	WARN_ON_ONCE(!refcount_dec_and_test(&kvm->users_count));
	क्रम (i = 0; i < KVM_NR_BUSES; i++)
		kमुक्त(kvm_get_bus(kvm, i));
	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++)
		kvm_मुक्त_memslots(kvm, __kvm_memslots(kvm, i));
	cleanup_srcu_काष्ठा(&kvm->irq_srcu);
out_err_no_irq_srcu:
	cleanup_srcu_काष्ठा(&kvm->srcu);
out_err_no_srcu:
	kvm_arch_मुक्त_vm(kvm);
	mmdrop(current->mm);
	वापस ERR_PTR(r);
पूर्ण

अटल व्योम kvm_destroy_devices(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_device *dev, *पंचांगp;

	/*
	 * We करो not need to take the kvm->lock here, because nobody अन्यथा
	 * has a reference to the काष्ठा kvm at this poपूर्णांक and thereक्रमe
	 * cannot access the devices list anyhow.
	 */
	list_क्रम_each_entry_safe(dev, पंचांगp, &kvm->devices, vm_node) अणु
		list_del(&dev->vm_node);
		dev->ops->destroy(dev);
	पूर्ण
पूर्ण

अटल व्योम kvm_destroy_vm(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा mm_काष्ठा *mm = kvm->mm;

	kvm_uevent_notअगरy_change(KVM_EVENT_DESTROY_VM, kvm);
	kvm_destroy_vm_debugfs(kvm);
	kvm_arch_sync_events(kvm);
	mutex_lock(&kvm_lock);
	list_del(&kvm->vm_list);
	mutex_unlock(&kvm_lock);
	kvm_arch_pre_destroy_vm(kvm);

	kvm_मुक्त_irq_routing(kvm);
	क्रम (i = 0; i < KVM_NR_BUSES; i++) अणु
		काष्ठा kvm_io_bus *bus = kvm_get_bus(kvm, i);

		अगर (bus)
			kvm_io_bus_destroy(bus);
		kvm->buses[i] = शून्य;
	पूर्ण
	kvm_coalesced_mmio_मुक्त(kvm);
#अगर defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	mmu_notअगरier_unरेजिस्टर(&kvm->mmu_notअगरier, kvm->mm);
#अन्यथा
	kvm_arch_flush_shaकरोw_all(kvm);
#पूर्ण_अगर
	kvm_arch_destroy_vm(kvm);
	kvm_destroy_devices(kvm);
	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++)
		kvm_मुक्त_memslots(kvm, __kvm_memslots(kvm, i));
	cleanup_srcu_काष्ठा(&kvm->irq_srcu);
	cleanup_srcu_काष्ठा(&kvm->srcu);
	kvm_arch_मुक्त_vm(kvm);
	preempt_notअगरier_dec();
	hardware_disable_all();
	mmdrop(mm);
पूर्ण

व्योम kvm_get_kvm(काष्ठा kvm *kvm)
अणु
	refcount_inc(&kvm->users_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_kvm);

व्योम kvm_put_kvm(काष्ठा kvm *kvm)
अणु
	अगर (refcount_dec_and_test(&kvm->users_count))
		kvm_destroy_vm(kvm);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_put_kvm);

/*
 * Used to put a reference that was taken on behalf of an object associated
 * with a user-visible file descriptor, e.g. a vcpu or device, अगर installation
 * of the new file descriptor fails and the reference cannot be transferred to
 * its final owner.  In such हालs, the caller is still actively using @kvm and
 * will fail miserably अगर the refcount unexpectedly hits zero.
 */
व्योम kvm_put_kvm_no_destroy(काष्ठा kvm *kvm)
अणु
	WARN_ON(refcount_dec_and_test(&kvm->users_count));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_put_kvm_no_destroy);

अटल पूर्णांक kvm_vm_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;

	kvm_irqfd_release(kvm);

	kvm_put_kvm(kvm);
	वापस 0;
पूर्ण

/*
 * Allocation size is twice as large as the actual dirty biपंचांगap size.
 * See kvm_vm_ioctl_get_dirty_log() why this is needed.
 */
अटल पूर्णांक kvm_alloc_dirty_biपंचांगap(काष्ठा kvm_memory_slot *memslot)
अणु
	अचिन्हित दीर्घ dirty_bytes = 2 * kvm_dirty_biपंचांगap_bytes(memslot);

	memslot->dirty_biपंचांगap = kvzalloc(dirty_bytes, GFP_KERNEL_ACCOUNT);
	अगर (!memslot->dirty_biपंचांगap)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * Delete a memslot by decrementing the number of used slots and shअगरting all
 * other entries in the array क्रमward one spot.
 */
अटल अंतरभूत व्योम kvm_memslot_delete(काष्ठा kvm_memslots *slots,
				      काष्ठा kvm_memory_slot *memslot)
अणु
	काष्ठा kvm_memory_slot *mslots = slots->memslots;
	पूर्णांक i;

	अगर (WARN_ON(slots->id_to_index[memslot->id] == -1))
		वापस;

	slots->used_slots--;

	अगर (atomic_पढ़ो(&slots->lru_slot) >= slots->used_slots)
		atomic_set(&slots->lru_slot, 0);

	क्रम (i = slots->id_to_index[memslot->id]; i < slots->used_slots; i++) अणु
		mslots[i] = mslots[i + 1];
		slots->id_to_index[mslots[i].id] = i;
	पूर्ण
	mslots[i] = *memslot;
	slots->id_to_index[memslot->id] = -1;
पूर्ण

/*
 * "Insert" a new memslot by incrementing the number of used slots.  Returns
 * the new slot's initial index पूर्णांकo the memslots array.
 */
अटल अंतरभूत पूर्णांक kvm_memslot_insert_back(काष्ठा kvm_memslots *slots)
अणु
	वापस slots->used_slots++;
पूर्ण

/*
 * Move a changed memslot backwards in the array by shअगरting existing slots
 * with a higher GFN toward the front of the array.  Note, the changed memslot
 * itself is not preserved in the array, i.e. not swapped at this समय, only
 * its new index पूर्णांकo the array is tracked.  Returns the changed memslot's
 * current index पूर्णांकo the memslots array.
 */
अटल अंतरभूत पूर्णांक kvm_memslot_move_backward(काष्ठा kvm_memslots *slots,
					    काष्ठा kvm_memory_slot *memslot)
अणु
	काष्ठा kvm_memory_slot *mslots = slots->memslots;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(slots->id_to_index[memslot->id] == -1) ||
	    WARN_ON_ONCE(!slots->used_slots))
		वापस -1;

	/*
	 * Move the target memslot backward in the array by shअगरting existing
	 * memslots with a higher GFN (than the target memslot) towards the
	 * front of the array.
	 */
	क्रम (i = slots->id_to_index[memslot->id]; i < slots->used_slots - 1; i++) अणु
		अगर (memslot->base_gfn > mslots[i + 1].base_gfn)
			अवरोध;

		WARN_ON_ONCE(memslot->base_gfn == mslots[i + 1].base_gfn);

		/* Shअगरt the next memslot क्रमward one and update its index. */
		mslots[i] = mslots[i + 1];
		slots->id_to_index[mslots[i].id] = i;
	पूर्ण
	वापस i;
पूर्ण

/*
 * Move a changed memslot क्रमwards in the array by shअगरting existing slots with
 * a lower GFN toward the back of the array.  Note, the changed memslot itself
 * is not preserved in the array, i.e. not swapped at this समय, only its new
 * index पूर्णांकo the array is tracked.  Returns the changed memslot's final index
 * पूर्णांकo the memslots array.
 */
अटल अंतरभूत पूर्णांक kvm_memslot_move_क्रमward(काष्ठा kvm_memslots *slots,
					   काष्ठा kvm_memory_slot *memslot,
					   पूर्णांक start)
अणु
	काष्ठा kvm_memory_slot *mslots = slots->memslots;
	पूर्णांक i;

	क्रम (i = start; i > 0; i--) अणु
		अगर (memslot->base_gfn < mslots[i - 1].base_gfn)
			अवरोध;

		WARN_ON_ONCE(memslot->base_gfn == mslots[i - 1].base_gfn);

		/* Shअगरt the next memslot back one and update its index. */
		mslots[i] = mslots[i - 1];
		slots->id_to_index[mslots[i].id] = i;
	पूर्ण
	वापस i;
पूर्ण

/*
 * Re-sort memslots based on their GFN to account क्रम an added, deleted, or
 * moved memslot.  Sorting memslots by GFN allows using a binary search during
 * memslot lookup.
 *
 * IMPORTANT: Slots are sorted from highest GFN to lowest GFN!  I.e. the entry
 * at memslots[0] has the highest GFN.
 *
 * The sorting algorithm takes advantage of having initially sorted memslots
 * and knowing the position of the changed memslot.  Sorting is also optimized
 * by not swapping the updated memslot and instead only shअगरting other memslots
 * and tracking the new index क्रम the update memslot.  Only once its final
 * index is known is the updated memslot copied पूर्णांकo its position in the array.
 *
 *  - When deleting a memslot, the deleted memslot simply needs to be moved to
 *    the end of the array.
 *
 *  - When creating a memslot, the algorithm "inserts" the new memslot at the
 *    end of the array and then it क्रमward to its correct location.
 *
 *  - When moving a memslot, the algorithm first moves the updated memslot
 *    backward to handle the scenario where the memslot's GFN was changed to a
 *    lower value.  update_memslots() then falls through and runs the same flow
 *    as creating a memslot to move the memslot क्रमward to handle the scenario
 *    where its GFN was changed to a higher value.
 *
 * Note, slots are sorted from highest->lowest instead of lowest->highest क्रम
 * historical reasons.  Originally, invalid memslots where denoted by having
 * GFN=0, thus sorting from highest->lowest naturally sorted invalid memslots
 * to the end of the array.  The current algorithm uses dedicated logic to
 * delete a memslot and thus करोes not rely on invalid memslots having GFN=0.
 *
 * The other historical motiviation क्रम highest->lowest was to improve the
 * perक्रमmance of memslot lookup.  KVM originally used a linear search starting
 * at memslots[0].  On x86, the largest memslot usually has one of the highest,
 * अगर not *the* highest, GFN, as the bulk of the guest's RAM is located in a
 * single memslot above the 4gb boundary.  As the largest memslot is also the
 * most likely to be referenced, sorting it to the front of the array was
 * advantageous.  The current binary search starts from the middle of the array
 * and uses an LRU poपूर्णांकer to improve perक्रमmance क्रम all memslots and GFNs.
 */
अटल व्योम update_memslots(काष्ठा kvm_memslots *slots,
			    काष्ठा kvm_memory_slot *memslot,
			    क्रमागत kvm_mr_change change)
अणु
	पूर्णांक i;

	अगर (change == KVM_MR_DELETE) अणु
		kvm_memslot_delete(slots, memslot);
	पूर्ण अन्यथा अणु
		अगर (change == KVM_MR_CREATE)
			i = kvm_memslot_insert_back(slots);
		अन्यथा
			i = kvm_memslot_move_backward(slots, memslot);
		i = kvm_memslot_move_क्रमward(slots, memslot, i);

		/*
		 * Copy the memslot to its new position in memslots and update
		 * its index accordingly.
		 */
		slots->memslots[i] = *memslot;
		slots->id_to_index[memslot->id] = i;
	पूर्ण
पूर्ण

अटल पूर्णांक check_memory_region_flags(स्थिर काष्ठा kvm_userspace_memory_region *mem)
अणु
	u32 valid_flags = KVM_MEM_LOG_सूचीTY_PAGES;

#अगर_घोषित __KVM_HAVE_READONLY_MEM
	valid_flags |= KVM_MEM_READONLY;
#पूर्ण_अगर

	अगर (mem->flags & ~valid_flags)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा kvm_memslots *install_new_memslots(काष्ठा kvm *kvm,
		पूर्णांक as_id, काष्ठा kvm_memslots *slots)
अणु
	काष्ठा kvm_memslots *old_memslots = __kvm_memslots(kvm, as_id);
	u64 gen = old_memslots->generation;

	WARN_ON(gen & KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS);
	slots->generation = gen | KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS;

	rcu_assign_poपूर्णांकer(kvm->memslots[as_id], slots);
	synchronize_srcu_expedited(&kvm->srcu);

	/*
	 * Increment the new memslot generation a second समय, dropping the
	 * update in-progress flag and incrementing the generation based on
	 * the number of address spaces.  This provides a unique and easily
	 * identअगरiable generation number जबतक the memslots are in flux.
	 */
	gen = slots->generation & ~KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS;

	/*
	 * Generations must be unique even across address spaces.  We करो not need
	 * a global counter क्रम that, instead the generation space is evenly split
	 * across address spaces.  For example, with two address spaces, address
	 * space 0 will use generations 0, 2, 4, ... जबतक address space 1 will
	 * use generations 1, 3, 5, ...
	 */
	gen += KVM_ADDRESS_SPACE_NUM;

	kvm_arch_memslots_updated(kvm, gen);

	slots->generation = gen;

	वापस old_memslots;
पूर्ण

/*
 * Note, at a minimum, the current number of used slots must be allocated, even
 * when deleting a memslot, as we need a complete duplicate of the memslots क्रम
 * use when invalidating a memslot prior to deleting/moving the memslot.
 */
अटल काष्ठा kvm_memslots *kvm_dup_memslots(काष्ठा kvm_memslots *old,
					     क्रमागत kvm_mr_change change)
अणु
	काष्ठा kvm_memslots *slots;
	माप_प्रकार old_size, new_size;

	old_size = माप(काष्ठा kvm_memslots) +
		   (माप(काष्ठा kvm_memory_slot) * old->used_slots);

	अगर (change == KVM_MR_CREATE)
		new_size = old_size + माप(काष्ठा kvm_memory_slot);
	अन्यथा
		new_size = old_size;

	slots = kvzalloc(new_size, GFP_KERNEL_ACCOUNT);
	अगर (likely(slots))
		स_नकल(slots, old, old_size);

	वापस slots;
पूर्ण

अटल पूर्णांक kvm_set_memslot(काष्ठा kvm *kvm,
			   स्थिर काष्ठा kvm_userspace_memory_region *mem,
			   काष्ठा kvm_memory_slot *old,
			   काष्ठा kvm_memory_slot *new, पूर्णांक as_id,
			   क्रमागत kvm_mr_change change)
अणु
	काष्ठा kvm_memory_slot *slot;
	काष्ठा kvm_memslots *slots;
	पूर्णांक r;

	slots = kvm_dup_memslots(__kvm_memslots(kvm, as_id), change);
	अगर (!slots)
		वापस -ENOMEM;

	अगर (change == KVM_MR_DELETE || change == KVM_MR_MOVE) अणु
		/*
		 * Note, the INVALID flag needs to be in the appropriate entry
		 * in the freshly allocated memslots, not in @old or @new.
		 */
		slot = id_to_memslot(slots, old->id);
		slot->flags |= KVM_MEMSLOT_INVALID;

		/*
		 * We can re-use the old memslots, the only dअगरference from the
		 * newly installed memslots is the invalid flag, which will get
		 * dropped by update_memslots anyway.  We'll also revert to the
		 * old memslots अगर preparing the new memory region fails.
		 */
		slots = install_new_memslots(kvm, as_id, slots);

		/* From this poपूर्णांक no new shaकरोw pages poपूर्णांकing to a deleted,
		 * or moved, memslot will be created.
		 *
		 * validation of sp->gfn happens in:
		 *	- gfn_to_hva (kvm_पढ़ो_guest, gfn_to_pfn)
		 *	- kvm_is_visible_gfn (mmu_check_root)
		 */
		kvm_arch_flush_shaकरोw_memslot(kvm, slot);
	पूर्ण

	r = kvm_arch_prepare_memory_region(kvm, new, mem, change);
	अगर (r)
		जाओ out_slots;

	update_memslots(slots, new, change);
	slots = install_new_memslots(kvm, as_id, slots);

	kvm_arch_commit_memory_region(kvm, mem, old, new, change);

	kvमुक्त(slots);
	वापस 0;

out_slots:
	अगर (change == KVM_MR_DELETE || change == KVM_MR_MOVE)
		slots = install_new_memslots(kvm, as_id, slots);
	kvमुक्त(slots);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_delete_memslot(काष्ठा kvm *kvm,
			      स्थिर काष्ठा kvm_userspace_memory_region *mem,
			      काष्ठा kvm_memory_slot *old, पूर्णांक as_id)
अणु
	काष्ठा kvm_memory_slot new;
	पूर्णांक r;

	अगर (!old->npages)
		वापस -EINVAL;

	स_रखो(&new, 0, माप(new));
	new.id = old->id;
	/*
	 * This is only क्रम debugging purpose; it should never be referenced
	 * क्रम a हटाओd memslot.
	 */
	new.as_id = as_id;

	r = kvm_set_memslot(kvm, mem, old, &new, as_id, KVM_MR_DELETE);
	अगर (r)
		वापस r;

	kvm_मुक्त_memslot(kvm, old);
	वापस 0;
पूर्ण

/*
 * Allocate some memory and give it an address in the guest physical address
 * space.
 *
 * Discontiguous memory is allowed, mostly क्रम framebuffers.
 *
 * Must be called holding kvm->slots_lock क्रम ग_लिखो.
 */
पूर्णांक __kvm_set_memory_region(काष्ठा kvm *kvm,
			    स्थिर काष्ठा kvm_userspace_memory_region *mem)
अणु
	काष्ठा kvm_memory_slot old, new;
	काष्ठा kvm_memory_slot *पंचांगp;
	क्रमागत kvm_mr_change change;
	पूर्णांक as_id, id;
	पूर्णांक r;

	r = check_memory_region_flags(mem);
	अगर (r)
		वापस r;

	as_id = mem->slot >> 16;
	id = (u16)mem->slot;

	/* General sanity checks */
	अगर (mem->memory_size & (PAGE_SIZE - 1))
		वापस -EINVAL;
	अगर (mem->guest_phys_addr & (PAGE_SIZE - 1))
		वापस -EINVAL;
	/* We can पढ़ो the guest memory with __xxx_user() later on. */
	अगर ((mem->userspace_addr & (PAGE_SIZE - 1)) ||
	    (mem->userspace_addr != untagged_addr(mem->userspace_addr)) ||
	     !access_ok((व्योम __user *)(अचिन्हित दीर्घ)mem->userspace_addr,
			mem->memory_size))
		वापस -EINVAL;
	अगर (as_id >= KVM_ADDRESS_SPACE_NUM || id >= KVM_MEM_SLOTS_NUM)
		वापस -EINVAL;
	अगर (mem->guest_phys_addr + mem->memory_size < mem->guest_phys_addr)
		वापस -EINVAL;

	/*
	 * Make a full copy of the old memslot, the poपूर्णांकer will become stale
	 * when the memslots are re-sorted by update_memslots(), and the old
	 * memslot needs to be referenced after calling update_memslots(), e.g.
	 * to मुक्त its resources and क्रम arch specअगरic behavior.
	 */
	पंचांगp = id_to_memslot(__kvm_memslots(kvm, as_id), id);
	अगर (पंचांगp) अणु
		old = *पंचांगp;
		पंचांगp = शून्य;
	पूर्ण अन्यथा अणु
		स_रखो(&old, 0, माप(old));
		old.id = id;
	पूर्ण

	अगर (!mem->memory_size)
		वापस kvm_delete_memslot(kvm, mem, &old, as_id);

	new.as_id = as_id;
	new.id = id;
	new.base_gfn = mem->guest_phys_addr >> PAGE_SHIFT;
	new.npages = mem->memory_size >> PAGE_SHIFT;
	new.flags = mem->flags;
	new.userspace_addr = mem->userspace_addr;

	अगर (new.npages > KVM_MEM_MAX_NR_PAGES)
		वापस -EINVAL;

	अगर (!old.npages) अणु
		change = KVM_MR_CREATE;
		new.dirty_biपंचांगap = शून्य;
		स_रखो(&new.arch, 0, माप(new.arch));
	पूर्ण अन्यथा अणु /* Modअगरy an existing slot. */
		अगर ((new.userspace_addr != old.userspace_addr) ||
		    (new.npages != old.npages) ||
		    ((new.flags ^ old.flags) & KVM_MEM_READONLY))
			वापस -EINVAL;

		अगर (new.base_gfn != old.base_gfn)
			change = KVM_MR_MOVE;
		अन्यथा अगर (new.flags != old.flags)
			change = KVM_MR_FLAGS_ONLY;
		अन्यथा /* Nothing to change. */
			वापस 0;

		/* Copy dirty_biपंचांगap and arch from the current memslot. */
		new.dirty_biपंचांगap = old.dirty_biपंचांगap;
		स_नकल(&new.arch, &old.arch, माप(new.arch));
	पूर्ण

	अगर ((change == KVM_MR_CREATE) || (change == KVM_MR_MOVE)) अणु
		/* Check क्रम overlaps */
		kvm_क्रम_each_memslot(पंचांगp, __kvm_memslots(kvm, as_id)) अणु
			अगर (पंचांगp->id == id)
				जारी;
			अगर (!((new.base_gfn + new.npages <= पंचांगp->base_gfn) ||
			      (new.base_gfn >= पंचांगp->base_gfn + पंचांगp->npages)))
				वापस -EEXIST;
		पूर्ण
	पूर्ण

	/* Allocate/मुक्त page dirty biपंचांगap as needed */
	अगर (!(new.flags & KVM_MEM_LOG_सूचीTY_PAGES))
		new.dirty_biपंचांगap = शून्य;
	अन्यथा अगर (!new.dirty_biपंचांगap && !kvm->dirty_ring_size) अणु
		r = kvm_alloc_dirty_biपंचांगap(&new);
		अगर (r)
			वापस r;

		अगर (kvm_dirty_log_manual_protect_and_init_set(kvm))
			biपंचांगap_set(new.dirty_biपंचांगap, 0, new.npages);
	पूर्ण

	r = kvm_set_memslot(kvm, mem, &old, &new, as_id, change);
	अगर (r)
		जाओ out_biपंचांगap;

	अगर (old.dirty_biपंचांगap && !new.dirty_biपंचांगap)
		kvm_destroy_dirty_biपंचांगap(&old);
	वापस 0;

out_biपंचांगap:
	अगर (new.dirty_biपंचांगap && !old.dirty_biपंचांगap)
		kvm_destroy_dirty_biपंचांगap(&new);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(__kvm_set_memory_region);

पूर्णांक kvm_set_memory_region(काष्ठा kvm *kvm,
			  स्थिर काष्ठा kvm_userspace_memory_region *mem)
अणु
	पूर्णांक r;

	mutex_lock(&kvm->slots_lock);
	r = __kvm_set_memory_region(kvm, mem);
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_memory_region);

अटल पूर्णांक kvm_vm_ioctl_set_memory_region(काष्ठा kvm *kvm,
					  काष्ठा kvm_userspace_memory_region *mem)
अणु
	अगर ((u16)mem->slot >= KVM_USER_MEM_SLOTS)
		वापस -EINVAL;

	वापस kvm_set_memory_region(kvm, mem);
पूर्ण

#अगर_अघोषित CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT
/**
 * kvm_get_dirty_log - get a snapshot of dirty pages
 * @kvm:	poपूर्णांकer to kvm instance
 * @log:	slot id and address to which we copy the log
 * @is_dirty:	set to '1' अगर any dirty pages were found
 * @memslot:	set to the associated memslot, always valid on success
 */
पूर्णांक kvm_get_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log,
		      पूर्णांक *is_dirty, काष्ठा kvm_memory_slot **memslot)
अणु
	काष्ठा kvm_memslots *slots;
	पूर्णांक i, as_id, id;
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ any = 0;

	/* Dirty ring tracking is exclusive to dirty log tracking */
	अगर (kvm->dirty_ring_size)
		वापस -ENXIO;

	*memslot = शून्य;
	*is_dirty = 0;

	as_id = log->slot >> 16;
	id = (u16)log->slot;
	अगर (as_id >= KVM_ADDRESS_SPACE_NUM || id >= KVM_USER_MEM_SLOTS)
		वापस -EINVAL;

	slots = __kvm_memslots(kvm, as_id);
	*memslot = id_to_memslot(slots, id);
	अगर (!(*memslot) || !(*memslot)->dirty_biपंचांगap)
		वापस -ENOENT;

	kvm_arch_sync_dirty_log(kvm, *memslot);

	n = kvm_dirty_biपंचांगap_bytes(*memslot);

	क्रम (i = 0; !any && i < n/माप(दीर्घ); ++i)
		any = (*memslot)->dirty_biपंचांगap[i];

	अगर (copy_to_user(log->dirty_biपंचांगap, (*memslot)->dirty_biपंचांगap, n))
		वापस -EFAULT;

	अगर (any)
		*is_dirty = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_dirty_log);

#अन्यथा /* CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT */
/**
 * kvm_get_dirty_log_protect - get a snapshot of dirty pages
 *	and reenable dirty page tracking क्रम the corresponding pages.
 * @kvm:	poपूर्णांकer to kvm instance
 * @log:	slot id and address to which we copy the log
 *
 * We need to keep it in mind that VCPU thपढ़ोs can ग_लिखो to the biपंचांगap
 * concurrently. So, to aव्योम losing track of dirty pages we keep the
 * following order:
 *
 *    1. Take a snapshot of the bit and clear it अगर needed.
 *    2. Write protect the corresponding page.
 *    3. Copy the snapshot to the userspace.
 *    4. Upon वापस caller flushes TLB's अगर needed.
 *
 * Between 2 and 4, the guest may ग_लिखो to the page using the reमुख्यing TLB
 * entry.  This is not a problem because the page is reported dirty using
 * the snapshot taken beक्रमe and step 4 ensures that ग_लिखोs करोne after
 * निकासing to userspace will be logged क्रम the next call.
 *
 */
अटल पूर्णांक kvm_get_dirty_log_protect(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक i, as_id, id;
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ *dirty_biपंचांगap;
	अचिन्हित दीर्घ *dirty_biपंचांगap_buffer;
	bool flush;

	/* Dirty ring tracking is exclusive to dirty log tracking */
	अगर (kvm->dirty_ring_size)
		वापस -ENXIO;

	as_id = log->slot >> 16;
	id = (u16)log->slot;
	अगर (as_id >= KVM_ADDRESS_SPACE_NUM || id >= KVM_USER_MEM_SLOTS)
		वापस -EINVAL;

	slots = __kvm_memslots(kvm, as_id);
	memslot = id_to_memslot(slots, id);
	अगर (!memslot || !memslot->dirty_biपंचांगap)
		वापस -ENOENT;

	dirty_biपंचांगap = memslot->dirty_biपंचांगap;

	kvm_arch_sync_dirty_log(kvm, memslot);

	n = kvm_dirty_biपंचांगap_bytes(memslot);
	flush = false;
	अगर (kvm->manual_dirty_log_protect) अणु
		/*
		 * Unlike kvm_get_dirty_log, we always वापस false in *flush,
		 * because no flush is needed until KVM_CLEAR_सूचीTY_LOG.  There
		 * is some code duplication between this function and
		 * kvm_get_dirty_log, but hopefully all architecture
		 * transition to kvm_get_dirty_log_protect and kvm_get_dirty_log
		 * can be eliminated.
		 */
		dirty_biपंचांगap_buffer = dirty_biपंचांगap;
	पूर्ण अन्यथा अणु
		dirty_biपंचांगap_buffer = kvm_second_dirty_biपंचांगap(memslot);
		स_रखो(dirty_biपंचांगap_buffer, 0, n);

		KVM_MMU_LOCK(kvm);
		क्रम (i = 0; i < n / माप(दीर्घ); i++) अणु
			अचिन्हित दीर्घ mask;
			gfn_t offset;

			अगर (!dirty_biपंचांगap[i])
				जारी;

			flush = true;
			mask = xchg(&dirty_biपंचांगap[i], 0);
			dirty_biपंचांगap_buffer[i] = mask;

			offset = i * BITS_PER_LONG;
			kvm_arch_mmu_enable_log_dirty_pt_masked(kvm, memslot,
								offset, mask);
		पूर्ण
		KVM_MMU_UNLOCK(kvm);
	पूर्ण

	अगर (flush)
		kvm_arch_flush_remote_tlbs_memslot(kvm, memslot);

	अगर (copy_to_user(log->dirty_biपंचांगap, dirty_biपंचांगap_buffer, n))
		वापस -EFAULT;
	वापस 0;
पूर्ण


/**
 * kvm_vm_ioctl_get_dirty_log - get and clear the log of dirty pages in a slot
 * @kvm: kvm instance
 * @log: slot id and address to which we copy the log
 *
 * Steps 1-4 below provide general overview of dirty page logging. See
 * kvm_get_dirty_log_protect() function description क्रम additional details.
 *
 * We call kvm_get_dirty_log_protect() to handle steps 1-3, upon वापस we
 * always flush the TLB (step 4) even अगर previous step failed  and the dirty
 * biपंचांगap may be corrupt. Regardless of previous outcome the KVM logging API
 * करोes not preclude user space subsequent dirty log पढ़ो. Flushing TLB ensures
 * ग_लिखोs will be marked dirty क्रम next log पढ़ो.
 *
 *   1. Take a snapshot of the bit and clear it अगर needed.
 *   2. Write protect the corresponding page.
 *   3. Copy the snapshot to the userspace.
 *   4. Flush TLB's अगर needed.
 */
अटल पूर्णांक kvm_vm_ioctl_get_dirty_log(काष्ठा kvm *kvm,
				      काष्ठा kvm_dirty_log *log)
अणु
	पूर्णांक r;

	mutex_lock(&kvm->slots_lock);

	r = kvm_get_dirty_log_protect(kvm, log);

	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

/**
 * kvm_clear_dirty_log_protect - clear dirty bits in the biपंचांगap
 *	and reenable dirty page tracking क्रम the corresponding pages.
 * @kvm:	poपूर्णांकer to kvm instance
 * @log:	slot id and address from which to fetch the biपंचांगap of dirty pages
 */
अटल पूर्णांक kvm_clear_dirty_log_protect(काष्ठा kvm *kvm,
				       काष्ठा kvm_clear_dirty_log *log)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक as_id, id;
	gfn_t offset;
	अचिन्हित दीर्घ i, n;
	अचिन्हित दीर्घ *dirty_biपंचांगap;
	अचिन्हित दीर्घ *dirty_biपंचांगap_buffer;
	bool flush;

	/* Dirty ring tracking is exclusive to dirty log tracking */
	अगर (kvm->dirty_ring_size)
		वापस -ENXIO;

	as_id = log->slot >> 16;
	id = (u16)log->slot;
	अगर (as_id >= KVM_ADDRESS_SPACE_NUM || id >= KVM_USER_MEM_SLOTS)
		वापस -EINVAL;

	अगर (log->first_page & 63)
		वापस -EINVAL;

	slots = __kvm_memslots(kvm, as_id);
	memslot = id_to_memslot(slots, id);
	अगर (!memslot || !memslot->dirty_biपंचांगap)
		वापस -ENOENT;

	dirty_biपंचांगap = memslot->dirty_biपंचांगap;

	n = ALIGN(log->num_pages, BITS_PER_LONG) / 8;

	अगर (log->first_page > memslot->npages ||
	    log->num_pages > memslot->npages - log->first_page ||
	    (log->num_pages < memslot->npages - log->first_page && (log->num_pages & 63)))
	    वापस -EINVAL;

	kvm_arch_sync_dirty_log(kvm, memslot);

	flush = false;
	dirty_biपंचांगap_buffer = kvm_second_dirty_biपंचांगap(memslot);
	अगर (copy_from_user(dirty_biपंचांगap_buffer, log->dirty_biपंचांगap, n))
		वापस -EFAULT;

	KVM_MMU_LOCK(kvm);
	क्रम (offset = log->first_page, i = offset / BITS_PER_LONG,
		 n = DIV_ROUND_UP(log->num_pages, BITS_PER_LONG); n--;
	     i++, offset += BITS_PER_LONG) अणु
		अचिन्हित दीर्घ mask = *dirty_biपंचांगap_buffer++;
		atomic_दीर्घ_t *p = (atomic_दीर्घ_t *) &dirty_biपंचांगap[i];
		अगर (!mask)
			जारी;

		mask &= atomic_दीर्घ_fetch_andnot(mask, p);

		/*
		 * mask contains the bits that really have been cleared.  This
		 * never includes any bits beyond the length of the memslot (अगर
		 * the length is not aligned to 64 pages), thereक्रमe it is not
		 * a problem अगर userspace sets them in log->dirty_biपंचांगap.
		*/
		अगर (mask) अणु
			flush = true;
			kvm_arch_mmu_enable_log_dirty_pt_masked(kvm, memslot,
								offset, mask);
		पूर्ण
	पूर्ण
	KVM_MMU_UNLOCK(kvm);

	अगर (flush)
		kvm_arch_flush_remote_tlbs_memslot(kvm, memslot);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_clear_dirty_log(काष्ठा kvm *kvm,
					काष्ठा kvm_clear_dirty_log *log)
अणु
	पूर्णांक r;

	mutex_lock(&kvm->slots_lock);

	r = kvm_clear_dirty_log_protect(kvm, log);

	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT */

काष्ठा kvm_memory_slot *gfn_to_memslot(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	वापस __gfn_to_memslot(kvm_memslots(kvm), gfn);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_memslot);

काष्ठा kvm_memory_slot *kvm_vcpu_gfn_to_memslot(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	वापस __gfn_to_memslot(kvm_vcpu_memslots(vcpu), gfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_memslot);

bool kvm_is_visible_gfn(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	काष्ठा kvm_memory_slot *memslot = gfn_to_memslot(kvm, gfn);

	वापस kvm_is_visible_memslot(memslot);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_is_visible_gfn);

bool kvm_vcpu_is_visible_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	काष्ठा kvm_memory_slot *memslot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);

	वापस kvm_is_visible_memslot(memslot);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_is_visible_gfn);

अचिन्हित दीर्घ kvm_host_page_size(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr, size;

	size = PAGE_SIZE;

	addr = kvm_vcpu_gfn_to_hva_prot(vcpu, gfn, शून्य);
	अगर (kvm_is_error_hva(addr))
		वापस PAGE_SIZE;

	mmap_पढ़ो_lock(current->mm);
	vma = find_vma(current->mm, addr);
	अगर (!vma)
		जाओ out;

	size = vma_kernel_pagesize(vma);

out:
	mmap_पढ़ो_unlock(current->mm);

	वापस size;
पूर्ण

अटल bool memslot_is_पढ़ोonly(काष्ठा kvm_memory_slot *slot)
अणु
	वापस slot->flags & KVM_MEM_READONLY;
पूर्ण

अटल अचिन्हित दीर्घ __gfn_to_hva_many(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				       gfn_t *nr_pages, bool ग_लिखो)
अणु
	अगर (!slot || slot->flags & KVM_MEMSLOT_INVALID)
		वापस KVM_HVA_ERR_BAD;

	अगर (memslot_is_पढ़ोonly(slot) && ग_लिखो)
		वापस KVM_HVA_ERR_RO_BAD;

	अगर (nr_pages)
		*nr_pages = slot->npages - (gfn - slot->base_gfn);

	वापस __gfn_to_hva_memslot(slot, gfn);
पूर्ण

अटल अचिन्हित दीर्घ gfn_to_hva_many(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				     gfn_t *nr_pages)
अणु
	वापस __gfn_to_hva_many(slot, gfn, nr_pages, true);
पूर्ण

अचिन्हित दीर्घ gfn_to_hva_memslot(काष्ठा kvm_memory_slot *slot,
					gfn_t gfn)
अणु
	वापस gfn_to_hva_many(slot, gfn, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_hva_memslot);

अचिन्हित दीर्घ gfn_to_hva(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	वापस gfn_to_hva_many(gfn_to_memslot(kvm, gfn), gfn, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_hva);

अचिन्हित दीर्घ kvm_vcpu_gfn_to_hva(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	वापस gfn_to_hva_many(kvm_vcpu_gfn_to_memslot(vcpu, gfn), gfn, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_hva);

/*
 * Return the hva of a @gfn and the R/W attribute अगर possible.
 *
 * @slot: the kvm_memory_slot which contains @gfn
 * @gfn: the gfn to be translated
 * @writable: used to वापस the पढ़ो/ग_लिखो attribute of the @slot अगर the hva
 * is valid and @writable is not शून्य
 */
अचिन्हित दीर्घ gfn_to_hva_memslot_prot(काष्ठा kvm_memory_slot *slot,
				      gfn_t gfn, bool *writable)
अणु
	अचिन्हित दीर्घ hva = __gfn_to_hva_many(slot, gfn, शून्य, false);

	अगर (!kvm_is_error_hva(hva) && writable)
		*writable = !memslot_is_पढ़ोonly(slot);

	वापस hva;
पूर्ण

अचिन्हित दीर्घ gfn_to_hva_prot(काष्ठा kvm *kvm, gfn_t gfn, bool *writable)
अणु
	काष्ठा kvm_memory_slot *slot = gfn_to_memslot(kvm, gfn);

	वापस gfn_to_hva_memslot_prot(slot, gfn, writable);
पूर्ण

अचिन्हित दीर्घ kvm_vcpu_gfn_to_hva_prot(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, bool *writable)
अणु
	काष्ठा kvm_memory_slot *slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);

	वापस gfn_to_hva_memslot_prot(slot, gfn, writable);
पूर्ण

अटल अंतरभूत पूर्णांक check_user_page_hwpoison(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक rc, flags = FOLL_HWPOISON | FOLL_WRITE;

	rc = get_user_pages(addr, 1, flags, शून्य, शून्य);
	वापस rc == -EHWPOISON;
पूर्ण

/*
 * The fast path to get the writable pfn which will be stored in @pfn,
 * true indicates success, otherwise false is वापसed.  It's also the
 * only part that runs अगर we can in atomic context.
 */
अटल bool hva_to_pfn_fast(अचिन्हित दीर्घ addr, bool ग_लिखो_fault,
			    bool *writable, kvm_pfn_t *pfn)
अणु
	काष्ठा page *page[1];

	/*
	 * Fast pin a writable pfn only अगर it is a ग_लिखो fault request
	 * or the caller allows to map a writable pfn क्रम a पढ़ो fault
	 * request.
	 */
	अगर (!(ग_लिखो_fault || writable))
		वापस false;

	अगर (get_user_page_fast_only(addr, FOLL_WRITE, page)) अणु
		*pfn = page_to_pfn(page[0]);

		अगर (writable)
			*writable = true;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * The slow path to get the pfn of the specअगरied host भव address,
 * 1 indicates success, -त्रुटि_सं is वापसed अगर error is detected.
 */
अटल पूर्णांक hva_to_pfn_slow(अचिन्हित दीर्घ addr, bool *async, bool ग_लिखो_fault,
			   bool *writable, kvm_pfn_t *pfn)
अणु
	अचिन्हित पूर्णांक flags = FOLL_HWPOISON;
	काष्ठा page *page;
	पूर्णांक npages = 0;

	might_sleep();

	अगर (writable)
		*writable = ग_लिखो_fault;

	अगर (ग_लिखो_fault)
		flags |= FOLL_WRITE;
	अगर (async)
		flags |= FOLL_NOWAIT;

	npages = get_user_pages_unlocked(addr, 1, &page, flags);
	अगर (npages != 1)
		वापस npages;

	/* map पढ़ो fault as writable अगर possible */
	अगर (unlikely(!ग_लिखो_fault) && writable) अणु
		काष्ठा page *wpage;

		अगर (get_user_page_fast_only(addr, FOLL_WRITE, &wpage)) अणु
			*writable = true;
			put_page(page);
			page = wpage;
		पूर्ण
	पूर्ण
	*pfn = page_to_pfn(page);
	वापस npages;
पूर्ण

अटल bool vma_is_valid(काष्ठा vm_area_काष्ठा *vma, bool ग_लिखो_fault)
अणु
	अगर (unlikely(!(vma->vm_flags & VM_READ)))
		वापस false;

	अगर (ग_लिखो_fault && (unlikely(!(vma->vm_flags & VM_WRITE))))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hva_to_pfn_remapped(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ addr, bool *async,
			       bool ग_लिखो_fault, bool *writable,
			       kvm_pfn_t *p_pfn)
अणु
	kvm_pfn_t pfn;
	pte_t *ptep;
	spinlock_t *ptl;
	पूर्णांक r;

	r = follow_pte(vma->vm_mm, addr, &ptep, &ptl);
	अगर (r) अणु
		/*
		 * get_user_pages fails क्रम VM_IO and VM_PFNMAP vmas and करोes
		 * not call the fault handler, so करो it here.
		 */
		bool unlocked = false;
		r = fixup_user_fault(current->mm, addr,
				     (ग_लिखो_fault ? FAULT_FLAG_WRITE : 0),
				     &unlocked);
		अगर (unlocked)
			वापस -EAGAIN;
		अगर (r)
			वापस r;

		r = follow_pte(vma->vm_mm, addr, &ptep, &ptl);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (ग_लिखो_fault && !pte_ग_लिखो(*ptep)) अणु
		pfn = KVM_PFN_ERR_RO_FAULT;
		जाओ out;
	पूर्ण

	अगर (writable)
		*writable = pte_ग_लिखो(*ptep);
	pfn = pte_pfn(*ptep);

	/*
	 * Get a reference here because callers of *hva_to_pfn* and
	 * *gfn_to_pfn* ultimately call kvm_release_pfn_clean on the
	 * वापसed pfn.  This is only needed अगर the VMA has VM_MIXEDMAP
	 * set, but the kvm_get_pfn/kvm_release_pfn_clean pair will
	 * simply करो nothing क्रम reserved pfns.
	 *
	 * Whoever called remap_pfn_range is also going to call e.g.
	 * unmap_mapping_range beक्रमe the underlying pages are मुक्तd,
	 * causing a call to our MMU notअगरier.
	 */ 
	kvm_get_pfn(pfn);

out:
	pte_unmap_unlock(ptep, ptl);
	*p_pfn = pfn;
	वापस 0;
पूर्ण

/*
 * Pin guest page in memory and वापस its pfn.
 * @addr: host भव address which maps memory to the guest
 * @atomic: whether this function can sleep
 * @async: whether this function need to रुको IO complete अगर the
 *         host page is not in the memory
 * @ग_लिखो_fault: whether we should get a writable host page
 * @writable: whether it allows to map a writable host page क्रम !@ग_लिखो_fault
 *
 * The function will map a writable host page क्रम these two हालs:
 * 1): @ग_लिखो_fault = true
 * 2): @ग_लिखो_fault = false && @writable, @writable will tell the caller
 *     whether the mapping is writable.
 */
अटल kvm_pfn_t hva_to_pfn(अचिन्हित दीर्घ addr, bool atomic, bool *async,
			bool ग_लिखो_fault, bool *writable)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	kvm_pfn_t pfn = 0;
	पूर्णांक npages, r;

	/* we can करो it either atomically or asynchronously, not both */
	BUG_ON(atomic && async);

	अगर (hva_to_pfn_fast(addr, ग_लिखो_fault, writable, &pfn))
		वापस pfn;

	अगर (atomic)
		वापस KVM_PFN_ERR_FAULT;

	npages = hva_to_pfn_slow(addr, async, ग_लिखो_fault, writable, &pfn);
	अगर (npages == 1)
		वापस pfn;

	mmap_पढ़ो_lock(current->mm);
	अगर (npages == -EHWPOISON ||
	      (!async && check_user_page_hwpoison(addr))) अणु
		pfn = KVM_PFN_ERR_HWPOISON;
		जाओ निकास;
	पूर्ण

retry:
	vma = find_vma_पूर्णांकersection(current->mm, addr, addr + 1);

	अगर (vma == शून्य)
		pfn = KVM_PFN_ERR_FAULT;
	अन्यथा अगर (vma->vm_flags & (VM_IO | VM_PFNMAP)) अणु
		r = hva_to_pfn_remapped(vma, addr, async, ग_लिखो_fault, writable, &pfn);
		अगर (r == -EAGAIN)
			जाओ retry;
		अगर (r < 0)
			pfn = KVM_PFN_ERR_FAULT;
	पूर्ण अन्यथा अणु
		अगर (async && vma_is_valid(vma, ग_लिखो_fault))
			*async = true;
		pfn = KVM_PFN_ERR_FAULT;
	पूर्ण
निकास:
	mmap_पढ़ो_unlock(current->mm);
	वापस pfn;
पूर्ण

kvm_pfn_t __gfn_to_pfn_memslot(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			       bool atomic, bool *async, bool ग_लिखो_fault,
			       bool *writable, hva_t *hva)
अणु
	अचिन्हित दीर्घ addr = __gfn_to_hva_many(slot, gfn, शून्य, ग_लिखो_fault);

	अगर (hva)
		*hva = addr;

	अगर (addr == KVM_HVA_ERR_RO_BAD) अणु
		अगर (writable)
			*writable = false;
		वापस KVM_PFN_ERR_RO_FAULT;
	पूर्ण

	अगर (kvm_is_error_hva(addr)) अणु
		अगर (writable)
			*writable = false;
		वापस KVM_PFN_NOSLOT;
	पूर्ण

	/* Do not map writable pfn in the पढ़ोonly memslot. */
	अगर (writable && memslot_is_पढ़ोonly(slot)) अणु
		*writable = false;
		writable = शून्य;
	पूर्ण

	वापस hva_to_pfn(addr, atomic, async, ग_लिखो_fault,
			  writable);
पूर्ण
EXPORT_SYMBOL_GPL(__gfn_to_pfn_memslot);

kvm_pfn_t gfn_to_pfn_prot(काष्ठा kvm *kvm, gfn_t gfn, bool ग_लिखो_fault,
		      bool *writable)
अणु
	वापस __gfn_to_pfn_memslot(gfn_to_memslot(kvm, gfn), gfn, false, शून्य,
				    ग_लिखो_fault, writable, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_pfn_prot);

kvm_pfn_t gfn_to_pfn_memslot(काष्ठा kvm_memory_slot *slot, gfn_t gfn)
अणु
	वापस __gfn_to_pfn_memslot(slot, gfn, false, शून्य, true, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_pfn_memslot);

kvm_pfn_t gfn_to_pfn_memslot_atomic(काष्ठा kvm_memory_slot *slot, gfn_t gfn)
अणु
	वापस __gfn_to_pfn_memslot(slot, gfn, true, शून्य, true, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_pfn_memslot_atomic);

kvm_pfn_t kvm_vcpu_gfn_to_pfn_atomic(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	वापस gfn_to_pfn_memslot_atomic(kvm_vcpu_gfn_to_memslot(vcpu, gfn), gfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_pfn_atomic);

kvm_pfn_t gfn_to_pfn(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	वापस gfn_to_pfn_memslot(gfn_to_memslot(kvm, gfn), gfn);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_pfn);

kvm_pfn_t kvm_vcpu_gfn_to_pfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	वापस gfn_to_pfn_memslot(kvm_vcpu_gfn_to_memslot(vcpu, gfn), gfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_pfn);

पूर्णांक gfn_to_page_many_atomic(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			    काष्ठा page **pages, पूर्णांक nr_pages)
अणु
	अचिन्हित दीर्घ addr;
	gfn_t entry = 0;

	addr = gfn_to_hva_many(slot, gfn, &entry);
	अगर (kvm_is_error_hva(addr))
		वापस -1;

	अगर (entry < nr_pages)
		वापस 0;

	वापस get_user_pages_fast_only(addr, nr_pages, FOLL_WRITE, pages);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_page_many_atomic);

अटल काष्ठा page *kvm_pfn_to_page(kvm_pfn_t pfn)
अणु
	अगर (is_error_noslot_pfn(pfn))
		वापस KVM_ERR_PTR_BAD_PAGE;

	अगर (kvm_is_reserved_pfn(pfn)) अणु
		WARN_ON(1);
		वापस KVM_ERR_PTR_BAD_PAGE;
	पूर्ण

	वापस pfn_to_page(pfn);
पूर्ण

काष्ठा page *gfn_to_page(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	kvm_pfn_t pfn;

	pfn = gfn_to_pfn(kvm, gfn);

	वापस kvm_pfn_to_page(pfn);
पूर्ण
EXPORT_SYMBOL_GPL(gfn_to_page);

व्योम kvm_release_pfn(kvm_pfn_t pfn, bool dirty, काष्ठा gfn_to_pfn_cache *cache)
अणु
	अगर (pfn == 0)
		वापस;

	अगर (cache)
		cache->pfn = cache->gfn = 0;

	अगर (dirty)
		kvm_release_pfn_dirty(pfn);
	अन्यथा
		kvm_release_pfn_clean(pfn);
पूर्ण

अटल व्योम kvm_cache_gfn_to_pfn(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				 काष्ठा gfn_to_pfn_cache *cache, u64 gen)
अणु
	kvm_release_pfn(cache->pfn, cache->dirty, cache);

	cache->pfn = gfn_to_pfn_memslot(slot, gfn);
	cache->gfn = gfn;
	cache->dirty = false;
	cache->generation = gen;
पूर्ण

अटल पूर्णांक __kvm_map_gfn(काष्ठा kvm_memslots *slots, gfn_t gfn,
			 काष्ठा kvm_host_map *map,
			 काष्ठा gfn_to_pfn_cache *cache,
			 bool atomic)
अणु
	kvm_pfn_t pfn;
	व्योम *hva = शून्य;
	काष्ठा page *page = KVM_UNMAPPED_PAGE;
	काष्ठा kvm_memory_slot *slot = __gfn_to_memslot(slots, gfn);
	u64 gen = slots->generation;

	अगर (!map)
		वापस -EINVAL;

	अगर (cache) अणु
		अगर (!cache->pfn || cache->gfn != gfn ||
			cache->generation != gen) अणु
			अगर (atomic)
				वापस -EAGAIN;
			kvm_cache_gfn_to_pfn(slot, gfn, cache, gen);
		पूर्ण
		pfn = cache->pfn;
	पूर्ण अन्यथा अणु
		अगर (atomic)
			वापस -EAGAIN;
		pfn = gfn_to_pfn_memslot(slot, gfn);
	पूर्ण
	अगर (is_error_noslot_pfn(pfn))
		वापस -EINVAL;

	अगर (pfn_valid(pfn)) अणु
		page = pfn_to_page(pfn);
		अगर (atomic)
			hva = kmap_atomic(page);
		अन्यथा
			hva = kmap(page);
#अगर_घोषित CONFIG_HAS_IOMEM
	पूर्ण अन्यथा अगर (!atomic) अणु
		hva = memremap(pfn_to_hpa(pfn), PAGE_SIZE, MEMREMAP_WB);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	अगर (!hva)
		वापस -EFAULT;

	map->page = page;
	map->hva = hva;
	map->pfn = pfn;
	map->gfn = gfn;

	वापस 0;
पूर्ण

पूर्णांक kvm_map_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, काष्ठा kvm_host_map *map,
		काष्ठा gfn_to_pfn_cache *cache, bool atomic)
अणु
	वापस __kvm_map_gfn(kvm_memslots(vcpu->kvm), gfn, map,
			cache, atomic);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_map_gfn);

पूर्णांक kvm_vcpu_map(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, काष्ठा kvm_host_map *map)
अणु
	वापस __kvm_map_gfn(kvm_vcpu_memslots(vcpu), gfn, map,
		शून्य, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_map);

अटल व्योम __kvm_unmap_gfn(काष्ठा kvm *kvm,
			काष्ठा kvm_memory_slot *memslot,
			काष्ठा kvm_host_map *map,
			काष्ठा gfn_to_pfn_cache *cache,
			bool dirty, bool atomic)
अणु
	अगर (!map)
		वापस;

	अगर (!map->hva)
		वापस;

	अगर (map->page != KVM_UNMAPPED_PAGE) अणु
		अगर (atomic)
			kunmap_atomic(map->hva);
		अन्यथा
			kunmap(map->page);
	पूर्ण
#अगर_घोषित CONFIG_HAS_IOMEM
	अन्यथा अगर (!atomic)
		memunmap(map->hva);
	अन्यथा
		WARN_ONCE(1, "Unexpected unmapping in atomic context");
#पूर्ण_अगर

	अगर (dirty)
		mark_page_dirty_in_slot(kvm, memslot, map->gfn);

	अगर (cache)
		cache->dirty |= dirty;
	अन्यथा
		kvm_release_pfn(map->pfn, dirty, शून्य);

	map->hva = शून्य;
	map->page = शून्य;
पूर्ण

पूर्णांक kvm_unmap_gfn(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_host_map *map, 
		  काष्ठा gfn_to_pfn_cache *cache, bool dirty, bool atomic)
अणु
	__kvm_unmap_gfn(vcpu->kvm, gfn_to_memslot(vcpu->kvm, map->gfn), map,
			cache, dirty, atomic);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_unmap_gfn);

व्योम kvm_vcpu_unmap(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_host_map *map, bool dirty)
अणु
	__kvm_unmap_gfn(vcpu->kvm, kvm_vcpu_gfn_to_memslot(vcpu, map->gfn),
			map, शून्य, dirty, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_unmap);

काष्ठा page *kvm_vcpu_gfn_to_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	kvm_pfn_t pfn;

	pfn = kvm_vcpu_gfn_to_pfn(vcpu, gfn);

	वापस kvm_pfn_to_page(pfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_gfn_to_page);

व्योम kvm_release_page_clean(काष्ठा page *page)
अणु
	WARN_ON(is_error_page(page));

	kvm_release_pfn_clean(page_to_pfn(page));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_release_page_clean);

व्योम kvm_release_pfn_clean(kvm_pfn_t pfn)
अणु
	अगर (!is_error_noslot_pfn(pfn) && !kvm_is_reserved_pfn(pfn))
		put_page(pfn_to_page(pfn));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_release_pfn_clean);

व्योम kvm_release_page_dirty(काष्ठा page *page)
अणु
	WARN_ON(is_error_page(page));

	kvm_release_pfn_dirty(page_to_pfn(page));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_release_page_dirty);

व्योम kvm_release_pfn_dirty(kvm_pfn_t pfn)
अणु
	kvm_set_pfn_dirty(pfn);
	kvm_release_pfn_clean(pfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_release_pfn_dirty);

व्योम kvm_set_pfn_dirty(kvm_pfn_t pfn)
अणु
	अगर (!kvm_is_reserved_pfn(pfn) && !kvm_is_zone_device_pfn(pfn))
		SetPageDirty(pfn_to_page(pfn));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_pfn_dirty);

व्योम kvm_set_pfn_accessed(kvm_pfn_t pfn)
अणु
	अगर (!kvm_is_reserved_pfn(pfn) && !kvm_is_zone_device_pfn(pfn))
		mark_page_accessed(pfn_to_page(pfn));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_pfn_accessed);

व्योम kvm_get_pfn(kvm_pfn_t pfn)
अणु
	अगर (!kvm_is_reserved_pfn(pfn))
		get_page(pfn_to_page(pfn));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_pfn);

अटल पूर्णांक next_segment(अचिन्हित दीर्घ len, पूर्णांक offset)
अणु
	अगर (len > PAGE_SIZE - offset)
		वापस PAGE_SIZE - offset;
	अन्यथा
		वापस len;
पूर्ण

अटल पूर्णांक __kvm_पढ़ो_guest_page(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				 व्योम *data, पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ addr;

	addr = gfn_to_hva_memslot_prot(slot, gfn, शून्य);
	अगर (kvm_is_error_hva(addr))
		वापस -EFAULT;
	r = __copy_from_user(data, (व्योम __user *)addr + offset, len);
	अगर (r)
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक kvm_पढ़ो_guest_page(काष्ठा kvm *kvm, gfn_t gfn, व्योम *data, पूर्णांक offset,
			पूर्णांक len)
अणु
	काष्ठा kvm_memory_slot *slot = gfn_to_memslot(kvm, gfn);

	वापस __kvm_पढ़ो_guest_page(slot, gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest_page);

पूर्णांक kvm_vcpu_पढ़ो_guest_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, व्योम *data,
			     पूर्णांक offset, पूर्णांक len)
अणु
	काष्ठा kvm_memory_slot *slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);

	वापस __kvm_पढ़ो_guest_page(slot, gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_पढ़ो_guest_page);

पूर्णांक kvm_पढ़ो_guest(काष्ठा kvm *kvm, gpa_t gpa, व्योम *data, अचिन्हित दीर्घ len)
अणु
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक seg;
	पूर्णांक offset = offset_in_page(gpa);
	पूर्णांक ret;

	जबतक ((seg = next_segment(len, offset)) != 0) अणु
		ret = kvm_पढ़ो_guest_page(kvm, gfn, data, offset, seg);
		अगर (ret < 0)
			वापस ret;
		offset = 0;
		len -= seg;
		data += seg;
		++gfn;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest);

पूर्णांक kvm_vcpu_पढ़ो_guest(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, व्योम *data, अचिन्हित दीर्घ len)
अणु
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक seg;
	पूर्णांक offset = offset_in_page(gpa);
	पूर्णांक ret;

	जबतक ((seg = next_segment(len, offset)) != 0) अणु
		ret = kvm_vcpu_पढ़ो_guest_page(vcpu, gfn, data, offset, seg);
		अगर (ret < 0)
			वापस ret;
		offset = 0;
		len -= seg;
		data += seg;
		++gfn;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_पढ़ो_guest);

अटल पूर्णांक __kvm_पढ़ो_guest_atomic(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			           व्योम *data, पूर्णांक offset, अचिन्हित दीर्घ len)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ addr;

	addr = gfn_to_hva_memslot_prot(slot, gfn, शून्य);
	अगर (kvm_is_error_hva(addr))
		वापस -EFAULT;
	pagefault_disable();
	r = __copy_from_user_inatomic(data, (व्योम __user *)addr + offset, len);
	pagefault_enable();
	अगर (r)
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक kvm_vcpu_पढ़ो_guest_atomic(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			       व्योम *data, अचिन्हित दीर्घ len)
अणु
	gfn_t gfn = gpa >> PAGE_SHIFT;
	काष्ठा kvm_memory_slot *slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	पूर्णांक offset = offset_in_page(gpa);

	वापस __kvm_पढ़ो_guest_atomic(slot, gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_पढ़ो_guest_atomic);

अटल पूर्णांक __kvm_ग_लिखो_guest_page(काष्ठा kvm *kvm,
				  काष्ठा kvm_memory_slot *memslot, gfn_t gfn,
			          स्थिर व्योम *data, पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ addr;

	addr = gfn_to_hva_memslot(memslot, gfn);
	अगर (kvm_is_error_hva(addr))
		वापस -EFAULT;
	r = __copy_to_user((व्योम __user *)addr + offset, data, len);
	अगर (r)
		वापस -EFAULT;
	mark_page_dirty_in_slot(kvm, memslot, gfn);
	वापस 0;
पूर्ण

पूर्णांक kvm_ग_लिखो_guest_page(काष्ठा kvm *kvm, gfn_t gfn,
			 स्थिर व्योम *data, पूर्णांक offset, पूर्णांक len)
अणु
	काष्ठा kvm_memory_slot *slot = gfn_to_memslot(kvm, gfn);

	वापस __kvm_ग_लिखो_guest_page(kvm, slot, gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_ग_लिखो_guest_page);

पूर्णांक kvm_vcpu_ग_लिखो_guest_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			      स्थिर व्योम *data, पूर्णांक offset, पूर्णांक len)
अणु
	काष्ठा kvm_memory_slot *slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);

	वापस __kvm_ग_लिखो_guest_page(vcpu->kvm, slot, gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_ग_लिखो_guest_page);

पूर्णांक kvm_ग_लिखो_guest(काष्ठा kvm *kvm, gpa_t gpa, स्थिर व्योम *data,
		    अचिन्हित दीर्घ len)
अणु
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक seg;
	पूर्णांक offset = offset_in_page(gpa);
	पूर्णांक ret;

	जबतक ((seg = next_segment(len, offset)) != 0) अणु
		ret = kvm_ग_लिखो_guest_page(kvm, gfn, data, offset, seg);
		अगर (ret < 0)
			वापस ret;
		offset = 0;
		len -= seg;
		data += seg;
		++gfn;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_ग_लिखो_guest);

पूर्णांक kvm_vcpu_ग_लिखो_guest(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, स्थिर व्योम *data,
		         अचिन्हित दीर्घ len)
अणु
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक seg;
	पूर्णांक offset = offset_in_page(gpa);
	पूर्णांक ret;

	जबतक ((seg = next_segment(len, offset)) != 0) अणु
		ret = kvm_vcpu_ग_लिखो_guest_page(vcpu, gfn, data, offset, seg);
		अगर (ret < 0)
			वापस ret;
		offset = 0;
		len -= seg;
		data += seg;
		++gfn;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_ग_लिखो_guest);

अटल पूर्णांक __kvm_gfn_to_hva_cache_init(काष्ठा kvm_memslots *slots,
				       काष्ठा gfn_to_hva_cache *ghc,
				       gpa_t gpa, अचिन्हित दीर्घ len)
अणु
	पूर्णांक offset = offset_in_page(gpa);
	gfn_t start_gfn = gpa >> PAGE_SHIFT;
	gfn_t end_gfn = (gpa + len - 1) >> PAGE_SHIFT;
	gfn_t nr_pages_needed = end_gfn - start_gfn + 1;
	gfn_t nr_pages_avail;

	/* Update ghc->generation beक्रमe perक्रमming any error checks. */
	ghc->generation = slots->generation;

	अगर (start_gfn > end_gfn) अणु
		ghc->hva = KVM_HVA_ERR_BAD;
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the requested region crosses two memslots, we still
	 * verअगरy that the entire region is valid here.
	 */
	क्रम ( ; start_gfn <= end_gfn; start_gfn += nr_pages_avail) अणु
		ghc->memslot = __gfn_to_memslot(slots, start_gfn);
		ghc->hva = gfn_to_hva_many(ghc->memslot, start_gfn,
					   &nr_pages_avail);
		अगर (kvm_is_error_hva(ghc->hva))
			वापस -EFAULT;
	पूर्ण

	/* Use the slow path क्रम cross page पढ़ोs and ग_लिखोs. */
	अगर (nr_pages_needed == 1)
		ghc->hva += offset;
	अन्यथा
		ghc->memslot = शून्य;

	ghc->gpa = gpa;
	ghc->len = len;
	वापस 0;
पूर्ण

पूर्णांक kvm_gfn_to_hva_cache_init(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			      gpa_t gpa, अचिन्हित दीर्घ len)
अणु
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	वापस __kvm_gfn_to_hva_cache_init(slots, ghc, gpa, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_gfn_to_hva_cache_init);

पूर्णांक kvm_ग_लिखो_guest_offset_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
				  व्योम *data, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ len)
अणु
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	पूर्णांक r;
	gpa_t gpa = ghc->gpa + offset;

	BUG_ON(len + offset > ghc->len);

	अगर (slots->generation != ghc->generation) अणु
		अगर (__kvm_gfn_to_hva_cache_init(slots, ghc, ghc->gpa, ghc->len))
			वापस -EFAULT;
	पूर्ण

	अगर (kvm_is_error_hva(ghc->hva))
		वापस -EFAULT;

	अगर (unlikely(!ghc->memslot))
		वापस kvm_ग_लिखो_guest(kvm, gpa, data, len);

	r = __copy_to_user((व्योम __user *)ghc->hva + offset, data, len);
	अगर (r)
		वापस -EFAULT;
	mark_page_dirty_in_slot(kvm, ghc->memslot, gpa >> PAGE_SHIFT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_ग_लिखो_guest_offset_cached);

पूर्णांक kvm_ग_लिखो_guest_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			   व्योम *data, अचिन्हित दीर्घ len)
अणु
	वापस kvm_ग_लिखो_guest_offset_cached(kvm, ghc, data, 0, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_ग_लिखो_guest_cached);

पूर्णांक kvm_पढ़ो_guest_offset_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
				 व्योम *data, अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ len)
अणु
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	पूर्णांक r;
	gpa_t gpa = ghc->gpa + offset;

	BUG_ON(len + offset > ghc->len);

	अगर (slots->generation != ghc->generation) अणु
		अगर (__kvm_gfn_to_hva_cache_init(slots, ghc, ghc->gpa, ghc->len))
			वापस -EFAULT;
	पूर्ण

	अगर (kvm_is_error_hva(ghc->hva))
		वापस -EFAULT;

	अगर (unlikely(!ghc->memslot))
		वापस kvm_पढ़ो_guest(kvm, gpa, data, len);

	r = __copy_from_user(data, (व्योम __user *)ghc->hva + offset, len);
	अगर (r)
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest_offset_cached);

पूर्णांक kvm_पढ़ो_guest_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			  व्योम *data, अचिन्हित दीर्घ len)
अणु
	वापस kvm_पढ़ो_guest_offset_cached(kvm, ghc, data, 0, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest_cached);

पूर्णांक kvm_clear_guest(काष्ठा kvm *kvm, gpa_t gpa, अचिन्हित दीर्घ len)
अणु
	स्थिर व्योम *zero_page = (स्थिर व्योम *) __va(page_to_phys(ZERO_PAGE(0)));
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक seg;
	पूर्णांक offset = offset_in_page(gpa);
	पूर्णांक ret;

	जबतक ((seg = next_segment(len, offset)) != 0) अणु
		ret = kvm_ग_लिखो_guest_page(kvm, gfn, zero_page, offset, len);
		अगर (ret < 0)
			वापस ret;
		offset = 0;
		len -= seg;
		++gfn;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_clear_guest);

व्योम mark_page_dirty_in_slot(काष्ठा kvm *kvm,
			     काष्ठा kvm_memory_slot *memslot,
		 	     gfn_t gfn)
अणु
	अगर (memslot && kvm_slot_dirty_track_enabled(memslot)) अणु
		अचिन्हित दीर्घ rel_gfn = gfn - memslot->base_gfn;
		u32 slot = (memslot->as_id << 16) | memslot->id;

		अगर (kvm->dirty_ring_size)
			kvm_dirty_ring_push(kvm_dirty_ring_get(kvm),
					    slot, rel_gfn);
		अन्यथा
			set_bit_le(rel_gfn, memslot->dirty_biपंचांगap);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mark_page_dirty_in_slot);

व्योम mark_page_dirty(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	काष्ठा kvm_memory_slot *memslot;

	memslot = gfn_to_memslot(kvm, gfn);
	mark_page_dirty_in_slot(kvm, memslot, gfn);
पूर्ण
EXPORT_SYMBOL_GPL(mark_page_dirty);

व्योम kvm_vcpu_mark_page_dirty(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	काष्ठा kvm_memory_slot *memslot;

	memslot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	mark_page_dirty_in_slot(vcpu->kvm, memslot, gfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_mark_page_dirty);

व्योम kvm_sigset_activate(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->sigset_active)
		वापस;

	/*
	 * This करोes a lockless modअगरication of ->real_blocked, which is fine
	 * because, only current can change ->real_blocked and all पढ़ोers of
	 * ->real_blocked करोn't care as दीर्घ ->real_blocked is always a subset
	 * of ->blocked.
	 */
	sigprocmask(SIG_SETMASK, &vcpu->sigset, &current->real_blocked);
पूर्ण

व्योम kvm_sigset_deactivate(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->sigset_active)
		वापस;

	sigprocmask(SIG_SETMASK, &current->real_blocked, शून्य);
	sigemptyset(&current->real_blocked);
पूर्ण

अटल व्योम grow_halt_poll_ns(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक old, val, grow, grow_start;

	old = val = vcpu->halt_poll_ns;
	grow_start = READ_ONCE(halt_poll_ns_grow_start);
	grow = READ_ONCE(halt_poll_ns_grow);
	अगर (!grow)
		जाओ out;

	val *= grow;
	अगर (val < grow_start)
		val = grow_start;

	अगर (val > vcpu->kvm->max_halt_poll_ns)
		val = vcpu->kvm->max_halt_poll_ns;

	vcpu->halt_poll_ns = val;
out:
	trace_kvm_halt_poll_ns_grow(vcpu->vcpu_id, val, old);
पूर्ण

अटल व्योम shrink_halt_poll_ns(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक old, val, shrink;

	old = val = vcpu->halt_poll_ns;
	shrink = READ_ONCE(halt_poll_ns_shrink);
	अगर (shrink == 0)
		val = 0;
	अन्यथा
		val /= shrink;

	vcpu->halt_poll_ns = val;
	trace_kvm_halt_poll_ns_shrink(vcpu->vcpu_id, val, old);
पूर्ण

अटल पूर्णांक kvm_vcpu_check_block(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret = -EINTR;
	पूर्णांक idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	अगर (kvm_arch_vcpu_runnable(vcpu)) अणु
		kvm_make_request(KVM_REQ_UNHALT, vcpu);
		जाओ out;
	पूर्ण
	अगर (kvm_cpu_has_pending_समयr(vcpu))
		जाओ out;
	अगर (संकेत_pending(current))
		जाओ out;
	अगर (kvm_check_request(KVM_REQ_UNBLOCK, vcpu))
		जाओ out;

	ret = 0;
out:
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
update_halt_poll_stats(काष्ठा kvm_vcpu *vcpu, u64 poll_ns, bool रुकोed)
अणु
	अगर (रुकोed)
		vcpu->स्थिति.सalt_poll_fail_ns += poll_ns;
	अन्यथा
		vcpu->स्थिति.सalt_poll_success_ns += poll_ns;
पूर्ण

/*
 * The vCPU has executed a HLT inकाष्ठाion with in-kernel mode enabled.
 */
व्योम kvm_vcpu_block(काष्ठा kvm_vcpu *vcpu)
अणु
	kसमय_प्रकार start, cur, poll_end;
	bool रुकोed = false;
	u64 block_ns;

	kvm_arch_vcpu_blocking(vcpu);

	start = cur = poll_end = kसमय_get();
	अगर (vcpu->halt_poll_ns && !kvm_arch_no_poll(vcpu)) अणु
		kसमय_प्रकार stop = kसमय_add_ns(kसमय_get(), vcpu->halt_poll_ns);

		++vcpu->स्थिति.सalt_attempted_poll;
		करो अणु
			/*
			 * This sets KVM_REQ_UNHALT अगर an पूर्णांकerrupt
			 * arrives.
			 */
			अगर (kvm_vcpu_check_block(vcpu) < 0) अणु
				++vcpu->स्थिति.सalt_successful_poll;
				अगर (!vcpu_valid_wakeup(vcpu))
					++vcpu->स्थिति.सalt_poll_invalid;
				जाओ out;
			पूर्ण
			poll_end = cur = kसमय_get();
		पूर्ण जबतक (kvm_vcpu_can_poll(cur, stop));
	पूर्ण

	prepare_to_rcuरुको(&vcpu->रुको);
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kvm_vcpu_check_block(vcpu) < 0)
			अवरोध;

		रुकोed = true;
		schedule();
	पूर्ण
	finish_rcuरुको(&vcpu->रुको);
	cur = kसमय_get();
out:
	kvm_arch_vcpu_unblocking(vcpu);
	block_ns = kसमय_प्रकारo_ns(cur) - kसमय_प्रकारo_ns(start);

	update_halt_poll_stats(
		vcpu, kसमय_प्रकारo_ns(kसमय_sub(poll_end, start)), रुकोed);

	अगर (!kvm_arch_no_poll(vcpu)) अणु
		अगर (!vcpu_valid_wakeup(vcpu)) अणु
			shrink_halt_poll_ns(vcpu);
		पूर्ण अन्यथा अगर (vcpu->kvm->max_halt_poll_ns) अणु
			अगर (block_ns <= vcpu->halt_poll_ns)
				;
			/* we had a दीर्घ block, shrink polling */
			अन्यथा अगर (vcpu->halt_poll_ns &&
					block_ns > vcpu->kvm->max_halt_poll_ns)
				shrink_halt_poll_ns(vcpu);
			/* we had a लघु halt and our poll समय is too small */
			अन्यथा अगर (vcpu->halt_poll_ns < vcpu->kvm->max_halt_poll_ns &&
					block_ns < vcpu->kvm->max_halt_poll_ns)
				grow_halt_poll_ns(vcpu);
		पूर्ण अन्यथा अणु
			vcpu->halt_poll_ns = 0;
		पूर्ण
	पूर्ण

	trace_kvm_vcpu_wakeup(block_ns, रुकोed, vcpu_valid_wakeup(vcpu));
	kvm_arch_vcpu_block_finish(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_block);

bool kvm_vcpu_wake_up(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा rcuरुको *रुकोp;

	रुकोp = kvm_arch_vcpu_get_रुको(vcpu);
	अगर (rcuरुको_wake_up(रुकोp)) अणु
		WRITE_ONCE(vcpu->पढ़ोy, true);
		++vcpu->स्थिति.सalt_wakeup;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_wake_up);

#अगर_अघोषित CONFIG_S390
/*
 * Kick a sleeping VCPU, or a guest VCPU in guest mode, पूर्णांकo host kernel mode.
 */
व्योम kvm_vcpu_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक me;
	पूर्णांक cpu = vcpu->cpu;

	अगर (kvm_vcpu_wake_up(vcpu))
		वापस;

	me = get_cpu();
	अगर (cpu != me && (अचिन्हित)cpu < nr_cpu_ids && cpu_online(cpu))
		अगर (kvm_arch_vcpu_should_kick(vcpu))
			smp_send_reschedule(cpu);
	put_cpu();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_kick);
#पूर्ण_अगर /* !CONFIG_S390 */

पूर्णांक kvm_vcpu_yield_to(काष्ठा kvm_vcpu *target)
अणु
	काष्ठा pid *pid;
	काष्ठा task_काष्ठा *task = शून्य;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	pid = rcu_dereference(target->pid);
	अगर (pid)
		task = get_pid_task(pid, PIDTYPE_PID);
	rcu_पढ़ो_unlock();
	अगर (!task)
		वापस ret;
	ret = yield_to(task, 1);
	put_task_काष्ठा(task);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_yield_to);

/*
 * Helper that checks whether a VCPU is eligible क्रम directed yield.
 * Most eligible candidate to yield is decided by following heuristics:
 *
 *  (a) VCPU which has not करोne pl-निकास or cpu relax पूर्णांकercepted recently
 *  (preempted lock holder), indicated by @in_spin_loop.
 *  Set at the beginning and cleared at the end of पूर्णांकerception/PLE handler.
 *
 *  (b) VCPU which has करोne pl-निकास/ cpu relax पूर्णांकercepted but did not get
 *  chance last समय (mostly it has become eligible now since we have probably
 *  yielded to lockholder in last iteration. This is करोne by toggling
 *  @dy_eligible each समय a VCPU checked क्रम eligibility.)
 *
 *  Yielding to a recently pl-निकासed/cpu relax पूर्णांकercepted VCPU beक्रमe yielding
 *  to preempted lock-holder could result in wrong VCPU selection and CPU
 *  burning. Giving priority क्रम a potential lock-holder increases lock
 *  progress.
 *
 *  Since algorithm is based on heuristics, accessing another VCPU data without
 *  locking करोes not harm. It may result in trying to yield to  same VCPU, fail
 *  and जारी with next VCPU and so on.
 */
अटल bool kvm_vcpu_eligible_क्रम_directed_yield(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT
	bool eligible;

	eligible = !vcpu->spin_loop.in_spin_loop ||
		    vcpu->spin_loop.dy_eligible;

	अगर (vcpu->spin_loop.in_spin_loop)
		kvm_vcpu_set_dy_eligible(vcpu, !vcpu->spin_loop.dy_eligible);

	वापस eligible;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

/*
 * Unlike kvm_arch_vcpu_runnable, this function is called outside
 * a vcpu_load/vcpu_put pair.  However, क्रम most architectures
 * kvm_arch_vcpu_runnable करोes not require vcpu_load.
 */
bool __weak kvm_arch_dy_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_arch_vcpu_runnable(vcpu);
पूर्ण

अटल bool vcpu_dy_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_arch_dy_runnable(vcpu))
		वापस true;

#अगर_घोषित CONFIG_KVM_ASYNC_PF
	अगर (!list_empty_careful(&vcpu->async_pf.करोne))
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

bool __weak kvm_arch_dy_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण

व्योम kvm_vcpu_on_spin(काष्ठा kvm_vcpu *me, bool yield_to_kernel_mode)
अणु
	काष्ठा kvm *kvm = me->kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक last_boosted_vcpu = me->kvm->last_boosted_vcpu;
	पूर्णांक yielded = 0;
	पूर्णांक try = 3;
	पूर्णांक pass;
	पूर्णांक i;

	kvm_vcpu_set_in_spin_loop(me, true);
	/*
	 * We boost the priority of a VCPU that is runnable but not
	 * currently running, because it got preempted by something
	 * अन्यथा and called schedule in __vcpu_run.  Hopefully that
	 * VCPU is holding the lock that we need and will release it.
	 * We approximate round-robin by starting at the last boosted VCPU.
	 */
	क्रम (pass = 0; pass < 2 && !yielded && try; pass++) अणु
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			अगर (!pass && i <= last_boosted_vcpu) अणु
				i = last_boosted_vcpu;
				जारी;
			पूर्ण अन्यथा अगर (pass && i > last_boosted_vcpu)
				अवरोध;
			अगर (!READ_ONCE(vcpu->पढ़ोy))
				जारी;
			अगर (vcpu == me)
				जारी;
			अगर (rcuरुको_active(&vcpu->रुको) &&
			    !vcpu_dy_runnable(vcpu))
				जारी;
			अगर (READ_ONCE(vcpu->preempted) && yield_to_kernel_mode &&
			    !kvm_arch_dy_has_pending_पूर्णांकerrupt(vcpu) &&
			    !kvm_arch_vcpu_in_kernel(vcpu))
				जारी;
			अगर (!kvm_vcpu_eligible_क्रम_directed_yield(vcpu))
				जारी;

			yielded = kvm_vcpu_yield_to(vcpu);
			अगर (yielded > 0) अणु
				kvm->last_boosted_vcpu = i;
				अवरोध;
			पूर्ण अन्यथा अगर (yielded < 0) अणु
				try--;
				अगर (!try)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	kvm_vcpu_set_in_spin_loop(me, false);

	/* Ensure vcpu is not eligible during next spinloop */
	kvm_vcpu_set_dy_eligible(me, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_on_spin);

अटल bool kvm_page_in_dirty_ring(काष्ठा kvm *kvm, अचिन्हित दीर्घ pgoff)
अणु
#अगर KVM_सूचीTY_LOG_PAGE_OFFSET > 0
	वापस (pgoff >= KVM_सूचीTY_LOG_PAGE_OFFSET) &&
	    (pgoff < KVM_सूचीTY_LOG_PAGE_OFFSET +
	     kvm->dirty_ring_size / PAGE_SIZE);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल vm_fault_t kvm_vcpu_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा kvm_vcpu *vcpu = vmf->vma->vm_file->निजी_data;
	काष्ठा page *page;

	अगर (vmf->pgoff == 0)
		page = virt_to_page(vcpu->run);
#अगर_घोषित CONFIG_X86
	अन्यथा अगर (vmf->pgoff == KVM_PIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->arch.pio_data);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_MMIO
	अन्यथा अगर (vmf->pgoff == KVM_COALESCED_MMIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->kvm->coalesced_mmio_ring);
#पूर्ण_अगर
	अन्यथा अगर (kvm_page_in_dirty_ring(vcpu->kvm, vmf->pgoff))
		page = kvm_dirty_ring_get_page(
		    &vcpu->dirty_ring,
		    vmf->pgoff - KVM_सूचीTY_LOG_PAGE_OFFSET);
	अन्यथा
		वापस kvm_arch_vcpu_fault(vcpu, vmf);
	get_page(page);
	vmf->page = page;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा kvm_vcpu_vm_ops = अणु
	.fault = kvm_vcpu_fault,
पूर्ण;

अटल पूर्णांक kvm_vcpu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kvm_vcpu *vcpu = file->निजी_data;
	अचिन्हित दीर्घ pages = (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;

	अगर ((kvm_page_in_dirty_ring(vcpu->kvm, vma->vm_pgoff) ||
	     kvm_page_in_dirty_ring(vcpu->kvm, vma->vm_pgoff + pages - 1)) &&
	    ((vma->vm_flags & VM_EXEC) || !(vma->vm_flags & VM_SHARED)))
		वापस -EINVAL;

	vma->vm_ops = &kvm_vcpu_vm_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;

	kvm_put_kvm(vcpu->kvm);
	वापस 0;
पूर्ण

अटल काष्ठा file_operations kvm_vcpu_fops = अणु
	.release        = kvm_vcpu_release,
	.unlocked_ioctl = kvm_vcpu_ioctl,
	.mmap           = kvm_vcpu_mmap,
	.llseek		= noop_llseek,
	KVM_COMPAT(kvm_vcpu_compat_ioctl),
पूर्ण;

/*
 * Allocates an inode क्रम the vcpu.
 */
अटल पूर्णांक create_vcpu_fd(काष्ठा kvm_vcpu *vcpu)
अणु
	अक्षर name[8 + 1 + ITOA_MAX_LEN + 1];

	snम_लिखो(name, माप(name), "kvm-vcpu:%d", vcpu->vcpu_id);
	वापस anon_inode_getfd(name, &kvm_vcpu_fops, vcpu, O_RDWR | O_CLOEXEC);
पूर्ण

अटल व्योम kvm_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित __KVM_HAVE_ARCH_VCPU_DEBUGFS
	काष्ठा dentry *debugfs_dentry;
	अक्षर dir_name[ITOA_MAX_LEN * 2];

	अगर (!debugfs_initialized())
		वापस;

	snम_लिखो(dir_name, माप(dir_name), "vcpu%d", vcpu->vcpu_id);
	debugfs_dentry = debugfs_create_dir(dir_name,
					    vcpu->kvm->debugfs_dentry);

	kvm_arch_create_vcpu_debugfs(vcpu, debugfs_dentry);
#पूर्ण_अगर
पूर्ण

/*
 * Creates some भव cpus.  Good luck creating more than one.
 */
अटल पूर्णांक kvm_vm_ioctl_create_vcpu(काष्ठा kvm *kvm, u32 id)
अणु
	पूर्णांक r;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा page *page;

	अगर (id >= KVM_MAX_VCPU_ID)
		वापस -EINVAL;

	mutex_lock(&kvm->lock);
	अगर (kvm->created_vcpus == KVM_MAX_VCPUS) अणु
		mutex_unlock(&kvm->lock);
		वापस -EINVAL;
	पूर्ण

	kvm->created_vcpus++;
	mutex_unlock(&kvm->lock);

	r = kvm_arch_vcpu_precreate(kvm, id);
	अगर (r)
		जाओ vcpu_decrement;

	vcpu = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL_ACCOUNT);
	अगर (!vcpu) अणु
		r = -ENOMEM;
		जाओ vcpu_decrement;
	पूर्ण

	BUILD_BUG_ON(माप(काष्ठा kvm_run) > PAGE_SIZE);
	page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!page) अणु
		r = -ENOMEM;
		जाओ vcpu_मुक्त;
	पूर्ण
	vcpu->run = page_address(page);

	kvm_vcpu_init(vcpu, kvm, id);

	r = kvm_arch_vcpu_create(vcpu);
	अगर (r)
		जाओ vcpu_मुक्त_run_page;

	अगर (kvm->dirty_ring_size) अणु
		r = kvm_dirty_ring_alloc(&vcpu->dirty_ring,
					 id, kvm->dirty_ring_size);
		अगर (r)
			जाओ arch_vcpu_destroy;
	पूर्ण

	mutex_lock(&kvm->lock);
	अगर (kvm_get_vcpu_by_id(kvm, id)) अणु
		r = -EEXIST;
		जाओ unlock_vcpu_destroy;
	पूर्ण

	vcpu->vcpu_idx = atomic_पढ़ो(&kvm->online_vcpus);
	BUG_ON(kvm->vcpus[vcpu->vcpu_idx]);

	/* Now it's all set up, let userspace reach it */
	kvm_get_kvm(kvm);
	r = create_vcpu_fd(vcpu);
	अगर (r < 0) अणु
		kvm_put_kvm_no_destroy(kvm);
		जाओ unlock_vcpu_destroy;
	पूर्ण

	kvm->vcpus[vcpu->vcpu_idx] = vcpu;

	/*
	 * Pairs with smp_rmb() in kvm_get_vcpu.  Write kvm->vcpus
	 * beक्रमe kvm->online_vcpu's incremented value.
	 */
	smp_wmb();
	atomic_inc(&kvm->online_vcpus);

	mutex_unlock(&kvm->lock);
	kvm_arch_vcpu_postcreate(vcpu);
	kvm_create_vcpu_debugfs(vcpu);
	वापस r;

unlock_vcpu_destroy:
	mutex_unlock(&kvm->lock);
	kvm_dirty_ring_मुक्त(&vcpu->dirty_ring);
arch_vcpu_destroy:
	kvm_arch_vcpu_destroy(vcpu);
vcpu_मुक्त_run_page:
	मुक्त_page((अचिन्हित दीर्घ)vcpu->run);
vcpu_मुक्त:
	kmem_cache_मुक्त(kvm_vcpu_cache, vcpu);
vcpu_decrement:
	mutex_lock(&kvm->lock);
	kvm->created_vcpus--;
	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_set_sigmask(काष्ठा kvm_vcpu *vcpu, sigset_t *sigset)
अणु
	अगर (sigset) अणु
		sigdअन्यथापंचांगask(sigset, sigmask(SIGKILL)|sigmask(SIGSTOP));
		vcpu->sigset_active = 1;
		vcpu->sigset = *sigset;
	पूर्ण अन्यथा
		vcpu->sigset_active = 0;
	वापस 0;
पूर्ण

अटल दीर्घ kvm_vcpu_ioctl(काष्ठा file *filp,
			   अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक r;
	काष्ठा kvm_fpu *fpu = शून्य;
	काष्ठा kvm_sregs *kvm_sregs = शून्य;

	अगर (vcpu->kvm->mm != current->mm)
		वापस -EIO;

	अगर (unlikely(_IOC_TYPE(ioctl) != KVMIO))
		वापस -EINVAL;

	/*
	 * Some architectures have vcpu ioctls that are asynchronous to vcpu
	 * execution; mutex_lock() would अवरोध them.
	 */
	r = kvm_arch_vcpu_async_ioctl(filp, ioctl, arg);
	अगर (r != -ENOIOCTLCMD)
		वापस r;

	अगर (mutex_lock_समाप्तable(&vcpu->mutex))
		वापस -EINTR;
	चयन (ioctl) अणु
	हाल KVM_RUN: अणु
		काष्ठा pid *oldpid;
		r = -EINVAL;
		अगर (arg)
			जाओ out;
		oldpid = rcu_access_poपूर्णांकer(vcpu->pid);
		अगर (unlikely(oldpid != task_pid(current))) अणु
			/* The thपढ़ो running this VCPU changed. */
			काष्ठा pid *newpid;

			r = kvm_arch_vcpu_run_pid_change(vcpu);
			अगर (r)
				अवरोध;

			newpid = get_task_pid(current, PIDTYPE_PID);
			rcu_assign_poपूर्णांकer(vcpu->pid, newpid);
			अगर (oldpid)
				synchronize_rcu();
			put_pid(oldpid);
		पूर्ण
		r = kvm_arch_vcpu_ioctl_run(vcpu);
		trace_kvm_userspace_निकास(vcpu->run->निकास_reason, r);
		अवरोध;
	पूर्ण
	हाल KVM_GET_REGS: अणु
		काष्ठा kvm_regs *kvm_regs;

		r = -ENOMEM;
		kvm_regs = kzalloc(माप(काष्ठा kvm_regs), GFP_KERNEL_ACCOUNT);
		अगर (!kvm_regs)
			जाओ out;
		r = kvm_arch_vcpu_ioctl_get_regs(vcpu, kvm_regs);
		अगर (r)
			जाओ out_मुक्त1;
		r = -EFAULT;
		अगर (copy_to_user(argp, kvm_regs, माप(काष्ठा kvm_regs)))
			जाओ out_मुक्त1;
		r = 0;
out_मुक्त1:
		kमुक्त(kvm_regs);
		अवरोध;
	पूर्ण
	हाल KVM_SET_REGS: अणु
		काष्ठा kvm_regs *kvm_regs;

		kvm_regs = memdup_user(argp, माप(*kvm_regs));
		अगर (IS_ERR(kvm_regs)) अणु
			r = PTR_ERR(kvm_regs);
			जाओ out;
		पूर्ण
		r = kvm_arch_vcpu_ioctl_set_regs(vcpu, kvm_regs);
		kमुक्त(kvm_regs);
		अवरोध;
	पूर्ण
	हाल KVM_GET_SREGS: अणु
		kvm_sregs = kzalloc(माप(काष्ठा kvm_sregs),
				    GFP_KERNEL_ACCOUNT);
		r = -ENOMEM;
		अगर (!kvm_sregs)
			जाओ out;
		r = kvm_arch_vcpu_ioctl_get_sregs(vcpu, kvm_sregs);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, kvm_sregs, माप(काष्ठा kvm_sregs)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_SREGS: अणु
		kvm_sregs = memdup_user(argp, माप(*kvm_sregs));
		अगर (IS_ERR(kvm_sregs)) अणु
			r = PTR_ERR(kvm_sregs);
			kvm_sregs = शून्य;
			जाओ out;
		पूर्ण
		r = kvm_arch_vcpu_ioctl_set_sregs(vcpu, kvm_sregs);
		अवरोध;
	पूर्ण
	हाल KVM_GET_MP_STATE: अणु
		काष्ठा kvm_mp_state mp_state;

		r = kvm_arch_vcpu_ioctl_get_mpstate(vcpu, &mp_state);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, &mp_state, माप(mp_state)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_MP_STATE: अणु
		काष्ठा kvm_mp_state mp_state;

		r = -EFAULT;
		अगर (copy_from_user(&mp_state, argp, माप(mp_state)))
			जाओ out;
		r = kvm_arch_vcpu_ioctl_set_mpstate(vcpu, &mp_state);
		अवरोध;
	पूर्ण
	हाल KVM_TRANSLATE: अणु
		काष्ठा kvm_translation tr;

		r = -EFAULT;
		अगर (copy_from_user(&tr, argp, माप(tr)))
			जाओ out;
		r = kvm_arch_vcpu_ioctl_translate(vcpu, &tr);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, &tr, माप(tr)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_GUEST_DEBUG: अणु
		काष्ठा kvm_guest_debug dbg;

		r = -EFAULT;
		अगर (copy_from_user(&dbg, argp, माप(dbg)))
			जाओ out;
		r = kvm_arch_vcpu_ioctl_set_guest_debug(vcpu, &dbg);
		अवरोध;
	पूर्ण
	हाल KVM_SET_SIGNAL_MASK: अणु
		काष्ठा kvm_संकेत_mask __user *sigmask_arg = argp;
		काष्ठा kvm_संकेत_mask kvm_sigmask;
		sigset_t sigset, *p;

		p = शून्य;
		अगर (argp) अणु
			r = -EFAULT;
			अगर (copy_from_user(&kvm_sigmask, argp,
					   माप(kvm_sigmask)))
				जाओ out;
			r = -EINVAL;
			अगर (kvm_sigmask.len != माप(sigset))
				जाओ out;
			r = -EFAULT;
			अगर (copy_from_user(&sigset, sigmask_arg->sigset,
					   माप(sigset)))
				जाओ out;
			p = &sigset;
		पूर्ण
		r = kvm_vcpu_ioctl_set_sigmask(vcpu, p);
		अवरोध;
	पूर्ण
	हाल KVM_GET_FPU: अणु
		fpu = kzalloc(माप(काष्ठा kvm_fpu), GFP_KERNEL_ACCOUNT);
		r = -ENOMEM;
		अगर (!fpu)
			जाओ out;
		r = kvm_arch_vcpu_ioctl_get_fpu(vcpu, fpu);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, fpu, माप(काष्ठा kvm_fpu)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_FPU: अणु
		fpu = memdup_user(argp, माप(*fpu));
		अगर (IS_ERR(fpu)) अणु
			r = PTR_ERR(fpu);
			fpu = शून्य;
			जाओ out;
		पूर्ण
		r = kvm_arch_vcpu_ioctl_set_fpu(vcpu, fpu);
		अवरोध;
	पूर्ण
	शेष:
		r = kvm_arch_vcpu_ioctl(filp, ioctl, arg);
	पूर्ण
out:
	mutex_unlock(&vcpu->mutex);
	kमुक्त(fpu);
	kमुक्त(kvm_sregs);
	वापस r;
पूर्ण

#अगर_घोषित CONFIG_KVM_COMPAT
अटल दीर्घ kvm_vcpu_compat_ioctl(काष्ठा file *filp,
				  अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक r;

	अगर (vcpu->kvm->mm != current->mm)
		वापस -EIO;

	चयन (ioctl) अणु
	हाल KVM_SET_SIGNAL_MASK: अणु
		काष्ठा kvm_संकेत_mask __user *sigmask_arg = argp;
		काष्ठा kvm_संकेत_mask kvm_sigmask;
		sigset_t sigset;

		अगर (argp) अणु
			r = -EFAULT;
			अगर (copy_from_user(&kvm_sigmask, argp,
					   माप(kvm_sigmask)))
				जाओ out;
			r = -EINVAL;
			अगर (kvm_sigmask.len != माप(compat_sigset_t))
				जाओ out;
			r = -EFAULT;
			अगर (get_compat_sigset(&sigset,
					      (compat_sigset_t __user *)sigmask_arg->sigset))
				जाओ out;
			r = kvm_vcpu_ioctl_set_sigmask(vcpu, &sigset);
		पूर्ण अन्यथा
			r = kvm_vcpu_ioctl_set_sigmask(vcpu, शून्य);
		अवरोध;
	पूर्ण
	शेष:
		r = kvm_vcpu_ioctl(filp, ioctl, arg);
	पूर्ण

out:
	वापस r;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvm_device_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kvm_device *dev = filp->निजी_data;

	अगर (dev->ops->mmap)
		वापस dev->ops->mmap(dev, vma);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक kvm_device_ioctl_attr(काष्ठा kvm_device *dev,
				 पूर्णांक (*accessor)(काष्ठा kvm_device *dev,
						 काष्ठा kvm_device_attr *attr),
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_device_attr attr;

	अगर (!accessor)
		वापस -EPERM;

	अगर (copy_from_user(&attr, (व्योम __user *)arg, माप(attr)))
		वापस -EFAULT;

	वापस accessor(dev, &attr);
पूर्ण

अटल दीर्घ kvm_device_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_device *dev = filp->निजी_data;

	अगर (dev->kvm->mm != current->mm)
		वापस -EIO;

	चयन (ioctl) अणु
	हाल KVM_SET_DEVICE_ATTR:
		वापस kvm_device_ioctl_attr(dev, dev->ops->set_attr, arg);
	हाल KVM_GET_DEVICE_ATTR:
		वापस kvm_device_ioctl_attr(dev, dev->ops->get_attr, arg);
	हाल KVM_HAS_DEVICE_ATTR:
		वापस kvm_device_ioctl_attr(dev, dev->ops->has_attr, arg);
	शेष:
		अगर (dev->ops->ioctl)
			वापस dev->ops->ioctl(dev, ioctl, arg);

		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_device_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kvm_device *dev = filp->निजी_data;
	काष्ठा kvm *kvm = dev->kvm;

	अगर (dev->ops->release) अणु
		mutex_lock(&kvm->lock);
		list_del(&dev->vm_node);
		dev->ops->release(dev);
		mutex_unlock(&kvm->lock);
	पूर्ण

	kvm_put_kvm(kvm);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations kvm_device_fops = अणु
	.unlocked_ioctl = kvm_device_ioctl,
	.release = kvm_device_release,
	KVM_COMPAT(kvm_device_ioctl),
	.mmap = kvm_device_mmap,
पूर्ण;

काष्ठा kvm_device *kvm_device_from_filp(काष्ठा file *filp)
अणु
	अगर (filp->f_op != &kvm_device_fops)
		वापस शून्य;

	वापस filp->निजी_data;
पूर्ण

अटल स्थिर काष्ठा kvm_device_ops *kvm_device_ops_table[KVM_DEV_TYPE_MAX] = अणु
#अगर_घोषित CONFIG_KVM_MPIC
	[KVM_DEV_TYPE_FSL_MPIC_20]	= &kvm_mpic_ops,
	[KVM_DEV_TYPE_FSL_MPIC_42]	= &kvm_mpic_ops,
#पूर्ण_अगर
पूर्ण;

पूर्णांक kvm_रेजिस्टर_device_ops(स्थिर काष्ठा kvm_device_ops *ops, u32 type)
अणु
	अगर (type >= ARRAY_SIZE(kvm_device_ops_table))
		वापस -ENOSPC;

	अगर (kvm_device_ops_table[type] != शून्य)
		वापस -EEXIST;

	kvm_device_ops_table[type] = ops;
	वापस 0;
पूर्ण

व्योम kvm_unरेजिस्टर_device_ops(u32 type)
अणु
	अगर (kvm_device_ops_table[type] != शून्य)
		kvm_device_ops_table[type] = शून्य;
पूर्ण

अटल पूर्णांक kvm_ioctl_create_device(काष्ठा kvm *kvm,
				   काष्ठा kvm_create_device *cd)
अणु
	स्थिर काष्ठा kvm_device_ops *ops = शून्य;
	काष्ठा kvm_device *dev;
	bool test = cd->flags & KVM_CREATE_DEVICE_TEST;
	पूर्णांक type;
	पूर्णांक ret;

	अगर (cd->type >= ARRAY_SIZE(kvm_device_ops_table))
		वापस -ENODEV;

	type = array_index_nospec(cd->type, ARRAY_SIZE(kvm_device_ops_table));
	ops = kvm_device_ops_table[type];
	अगर (ops == शून्य)
		वापस -ENODEV;

	अगर (test)
		वापस 0;

	dev = kzalloc(माप(*dev), GFP_KERNEL_ACCOUNT);
	अगर (!dev)
		वापस -ENOMEM;

	dev->ops = ops;
	dev->kvm = kvm;

	mutex_lock(&kvm->lock);
	ret = ops->create(dev, type);
	अगर (ret < 0) अणु
		mutex_unlock(&kvm->lock);
		kमुक्त(dev);
		वापस ret;
	पूर्ण
	list_add(&dev->vm_node, &kvm->devices);
	mutex_unlock(&kvm->lock);

	अगर (ops->init)
		ops->init(dev);

	kvm_get_kvm(kvm);
	ret = anon_inode_getfd(ops->name, &kvm_device_fops, dev, O_RDWR | O_CLOEXEC);
	अगर (ret < 0) अणु
		kvm_put_kvm_no_destroy(kvm);
		mutex_lock(&kvm->lock);
		list_del(&dev->vm_node);
		mutex_unlock(&kvm->lock);
		ops->destroy(dev);
		वापस ret;
	पूर्ण

	cd->fd = ret;
	वापस 0;
पूर्ण

अटल दीर्घ kvm_vm_ioctl_check_extension_generic(काष्ठा kvm *kvm, दीर्घ arg)
अणु
	चयन (arg) अणु
	हाल KVM_CAP_USER_MEMORY:
	हाल KVM_CAP_DESTROY_MEMORY_REGION_WORKS:
	हाल KVM_CAP_JOIN_MEMORY_REGIONS_WORKS:
	हाल KVM_CAP_INTERNAL_ERROR_DATA:
#अगर_घोषित CONFIG_HAVE_KVM_MSI
	हाल KVM_CAP_SIGNAL_MSI:
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
	हाल KVM_CAP_IRQFD:
	हाल KVM_CAP_IRQFD_RESAMPLE:
#पूर्ण_अगर
	हाल KVM_CAP_IOEVENTFD_ANY_LENGTH:
	हाल KVM_CAP_CHECK_EXTENSION_VM:
	हाल KVM_CAP_ENABLE_CAP_VM:
	हाल KVM_CAP_HALT_POLL:
		वापस 1;
#अगर_घोषित CONFIG_KVM_MMIO
	हाल KVM_CAP_COALESCED_MMIO:
		वापस KVM_COALESCED_MMIO_PAGE_OFFSET;
	हाल KVM_CAP_COALESCED_PIO:
		वापस 1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT
	हाल KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2:
		वापस KVM_सूचीTY_LOG_MANUAL_CAPS;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM_IRQ_ROUTING
	हाल KVM_CAP_IRQ_ROUTING:
		वापस KVM_MAX_IRQ_ROUTES;
#पूर्ण_अगर
#अगर KVM_ADDRESS_SPACE_NUM > 1
	हाल KVM_CAP_MULTI_ADDRESS_SPACE:
		वापस KVM_ADDRESS_SPACE_NUM;
#पूर्ण_अगर
	हाल KVM_CAP_NR_MEMSLOTS:
		वापस KVM_USER_MEM_SLOTS;
	हाल KVM_CAP_सूचीTY_LOG_RING:
#अगर KVM_सूचीTY_LOG_PAGE_OFFSET > 0
		वापस KVM_सूचीTY_RING_MAX_ENTRIES * माप(काष्ठा kvm_dirty_gfn);
#अन्यथा
		वापस 0;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
	वापस kvm_vm_ioctl_check_extension(kvm, arg);
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_enable_dirty_log_ring(काष्ठा kvm *kvm, u32 size)
अणु
	पूर्णांक r;

	अगर (!KVM_सूचीTY_LOG_PAGE_OFFSET)
		वापस -EINVAL;

	/* the size should be घातer of 2 */
	अगर (!size || (size & (size - 1)))
		वापस -EINVAL;

	/* Should be bigger to keep the reserved entries, or a page */
	अगर (size < kvm_dirty_ring_get_rsvd_entries() *
	    माप(काष्ठा kvm_dirty_gfn) || size < PAGE_SIZE)
		वापस -EINVAL;

	अगर (size > KVM_सूचीTY_RING_MAX_ENTRIES *
	    माप(काष्ठा kvm_dirty_gfn))
		वापस -E2BIG;

	/* We only allow it to set once */
	अगर (kvm->dirty_ring_size)
		वापस -EINVAL;

	mutex_lock(&kvm->lock);

	अगर (kvm->created_vcpus) अणु
		/* We करोn't allow to change this value after vcpu created */
		r = -EINVAL;
	पूर्ण अन्यथा अणु
		kvm->dirty_ring_size = size;
		r = 0;
	पूर्ण

	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_reset_dirty_pages(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक cleared = 0;

	अगर (!kvm->dirty_ring_size)
		वापस -EINVAL;

	mutex_lock(&kvm->slots_lock);

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		cleared += kvm_dirty_ring_reset(vcpu->kvm, &vcpu->dirty_ring);

	mutex_unlock(&kvm->slots_lock);

	अगर (cleared)
		kvm_flush_remote_tlbs(kvm);

	वापस cleared;
पूर्ण

पूर्णांक __attribute__((weak)) kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm,
						  काष्ठा kvm_enable_cap *cap)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_enable_cap_generic(काष्ठा kvm *kvm,
					   काष्ठा kvm_enable_cap *cap)
अणु
	चयन (cap->cap) अणु
#अगर_घोषित CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT
	हाल KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2: अणु
		u64 allowed_options = KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE;

		अगर (cap->args[0] & KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE)
			allowed_options = KVM_सूचीTY_LOG_MANUAL_CAPS;

		अगर (cap->flags || (cap->args[0] & ~allowed_options))
			वापस -EINVAL;
		kvm->manual_dirty_log_protect = cap->args[0];
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_CAP_HALT_POLL: अणु
		अगर (cap->flags || cap->args[0] != (अचिन्हित पूर्णांक)cap->args[0])
			वापस -EINVAL;

		kvm->max_halt_poll_ns = cap->args[0];
		वापस 0;
	पूर्ण
	हाल KVM_CAP_सूचीTY_LOG_RING:
		वापस kvm_vm_ioctl_enable_dirty_log_ring(kvm, cap->args[0]);
	शेष:
		वापस kvm_vm_ioctl_enable_cap(kvm, cap);
	पूर्ण
पूर्ण

अटल दीर्घ kvm_vm_ioctl(काष्ठा file *filp,
			   अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक r;

	अगर (kvm->mm != current->mm)
		वापस -EIO;
	चयन (ioctl) अणु
	हाल KVM_CREATE_VCPU:
		r = kvm_vm_ioctl_create_vcpu(kvm, arg);
		अवरोध;
	हाल KVM_ENABLE_CAP: अणु
		काष्ठा kvm_enable_cap cap;

		r = -EFAULT;
		अगर (copy_from_user(&cap, argp, माप(cap)))
			जाओ out;
		r = kvm_vm_ioctl_enable_cap_generic(kvm, &cap);
		अवरोध;
	पूर्ण
	हाल KVM_SET_USER_MEMORY_REGION: अणु
		काष्ठा kvm_userspace_memory_region kvm_userspace_mem;

		r = -EFAULT;
		अगर (copy_from_user(&kvm_userspace_mem, argp,
						माप(kvm_userspace_mem)))
			जाओ out;

		r = kvm_vm_ioctl_set_memory_region(kvm, &kvm_userspace_mem);
		अवरोध;
	पूर्ण
	हाल KVM_GET_सूचीTY_LOG: अणु
		काष्ठा kvm_dirty_log log;

		r = -EFAULT;
		अगर (copy_from_user(&log, argp, माप(log)))
			जाओ out;
		r = kvm_vm_ioctl_get_dirty_log(kvm, &log);
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT
	हाल KVM_CLEAR_सूचीTY_LOG: अणु
		काष्ठा kvm_clear_dirty_log log;

		r = -EFAULT;
		अगर (copy_from_user(&log, argp, माप(log)))
			जाओ out;
		r = kvm_vm_ioctl_clear_dirty_log(kvm, &log);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_MMIO
	हाल KVM_REGISTER_COALESCED_MMIO: अणु
		काष्ठा kvm_coalesced_mmio_zone zone;

		r = -EFAULT;
		अगर (copy_from_user(&zone, argp, माप(zone)))
			जाओ out;
		r = kvm_vm_ioctl_रेजिस्टर_coalesced_mmio(kvm, &zone);
		अवरोध;
	पूर्ण
	हाल KVM_UNREGISTER_COALESCED_MMIO: अणु
		काष्ठा kvm_coalesced_mmio_zone zone;

		r = -EFAULT;
		अगर (copy_from_user(&zone, argp, माप(zone)))
			जाओ out;
		r = kvm_vm_ioctl_unरेजिस्टर_coalesced_mmio(kvm, &zone);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_IRQFD: अणु
		काष्ठा kvm_irqfd data;

		r = -EFAULT;
		अगर (copy_from_user(&data, argp, माप(data)))
			जाओ out;
		r = kvm_irqfd(kvm, &data);
		अवरोध;
	पूर्ण
	हाल KVM_IOEVENTFD: अणु
		काष्ठा kvm_ioeventfd data;

		r = -EFAULT;
		अगर (copy_from_user(&data, argp, माप(data)))
			जाओ out;
		r = kvm_ioeventfd(kvm, &data);
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_HAVE_KVM_MSI
	हाल KVM_SIGNAL_MSI: अणु
		काष्ठा kvm_msi msi;

		r = -EFAULT;
		अगर (copy_from_user(&msi, argp, माप(msi)))
			जाओ out;
		r = kvm_send_userspace_msi(kvm, &msi);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित __KVM_HAVE_IRQ_LINE
	हाल KVM_IRQ_LINE_STATUS:
	हाल KVM_IRQ_LINE: अणु
		काष्ठा kvm_irq_level irq_event;

		r = -EFAULT;
		अगर (copy_from_user(&irq_event, argp, माप(irq_event)))
			जाओ out;

		r = kvm_vm_ioctl_irq_line(kvm, &irq_event,
					ioctl == KVM_IRQ_LINE_STATUS);
		अगर (r)
			जाओ out;

		r = -EFAULT;
		अगर (ioctl == KVM_IRQ_LINE_STATUS) अणु
			अगर (copy_to_user(argp, &irq_event, माप(irq_event)))
				जाओ out;
		पूर्ण

		r = 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM_IRQ_ROUTING
	हाल KVM_SET_GSI_ROUTING: अणु
		काष्ठा kvm_irq_routing routing;
		काष्ठा kvm_irq_routing __user *urouting;
		काष्ठा kvm_irq_routing_entry *entries = शून्य;

		r = -EFAULT;
		अगर (copy_from_user(&routing, argp, माप(routing)))
			जाओ out;
		r = -EINVAL;
		अगर (!kvm_arch_can_set_irq_routing(kvm))
			जाओ out;
		अगर (routing.nr > KVM_MAX_IRQ_ROUTES)
			जाओ out;
		अगर (routing.flags)
			जाओ out;
		अगर (routing.nr) अणु
			urouting = argp;
			entries = vmemdup_user(urouting->entries,
					       array_size(माप(*entries),
							  routing.nr));
			अगर (IS_ERR(entries)) अणु
				r = PTR_ERR(entries);
				जाओ out;
			पूर्ण
		पूर्ण
		r = kvm_set_irq_routing(kvm, entries, routing.nr,
					routing.flags);
		kvमुक्त(entries);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_IRQ_ROUTING */
	हाल KVM_CREATE_DEVICE: अणु
		काष्ठा kvm_create_device cd;

		r = -EFAULT;
		अगर (copy_from_user(&cd, argp, माप(cd)))
			जाओ out;

		r = kvm_ioctl_create_device(kvm, &cd);
		अगर (r)
			जाओ out;

		r = -EFAULT;
		अगर (copy_to_user(argp, &cd, माप(cd)))
			जाओ out;

		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_CHECK_EXTENSION:
		r = kvm_vm_ioctl_check_extension_generic(kvm, arg);
		अवरोध;
	हाल KVM_RESET_सूचीTY_RINGS:
		r = kvm_vm_ioctl_reset_dirty_pages(kvm);
		अवरोध;
	शेष:
		r = kvm_arch_vm_ioctl(filp, ioctl, arg);
	पूर्ण
out:
	वापस r;
पूर्ण

#अगर_घोषित CONFIG_KVM_COMPAT
काष्ठा compat_kvm_dirty_log अणु
	__u32 slot;
	__u32 padding1;
	जोड़ अणु
		compat_uptr_t dirty_biपंचांगap; /* one bit per page */
		__u64 padding2;
	पूर्ण;
पूर्ण;

अटल दीर्घ kvm_vm_compat_ioctl(काष्ठा file *filp,
			   अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;
	पूर्णांक r;

	अगर (kvm->mm != current->mm)
		वापस -EIO;
	चयन (ioctl) अणु
	हाल KVM_GET_सूचीTY_LOG: अणु
		काष्ठा compat_kvm_dirty_log compat_log;
		काष्ठा kvm_dirty_log log;

		अगर (copy_from_user(&compat_log, (व्योम __user *)arg,
				   माप(compat_log)))
			वापस -EFAULT;
		log.slot	 = compat_log.slot;
		log.padding1	 = compat_log.padding1;
		log.padding2	 = compat_log.padding2;
		log.dirty_biपंचांगap = compat_ptr(compat_log.dirty_biपंचांगap);

		r = kvm_vm_ioctl_get_dirty_log(kvm, &log);
		अवरोध;
	पूर्ण
	शेष:
		r = kvm_vm_ioctl(filp, ioctl, arg);
	पूर्ण
	वापस r;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा file_operations kvm_vm_fops = अणु
	.release        = kvm_vm_release,
	.unlocked_ioctl = kvm_vm_ioctl,
	.llseek		= noop_llseek,
	KVM_COMPAT(kvm_vm_compat_ioctl),
पूर्ण;

bool file_is_kvm(काष्ठा file *file)
अणु
	वापस file && file->f_op == &kvm_vm_fops;
पूर्ण
EXPORT_SYMBOL_GPL(file_is_kvm);

अटल पूर्णांक kvm_dev_ioctl_create_vm(अचिन्हित दीर्घ type)
अणु
	पूर्णांक r;
	काष्ठा kvm *kvm;
	काष्ठा file *file;

	kvm = kvm_create_vm(type);
	अगर (IS_ERR(kvm))
		वापस PTR_ERR(kvm);
#अगर_घोषित CONFIG_KVM_MMIO
	r = kvm_coalesced_mmio_init(kvm);
	अगर (r < 0)
		जाओ put_kvm;
#पूर्ण_अगर
	r = get_unused_fd_flags(O_CLOEXEC);
	अगर (r < 0)
		जाओ put_kvm;

	file = anon_inode_getfile("kvm-vm", &kvm_vm_fops, kvm, O_RDWR);
	अगर (IS_ERR(file)) अणु
		put_unused_fd(r);
		r = PTR_ERR(file);
		जाओ put_kvm;
	पूर्ण

	/*
	 * Don't call kvm_put_kvm anymore at this poपूर्णांक; file->f_op is
	 * alपढ़ोy set, with ->release() being kvm_vm_release().  In error
	 * हालs it will be called by the final fput(file) and will take
	 * care of करोing kvm_put_kvm(kvm).
	 */
	अगर (kvm_create_vm_debugfs(kvm, r) < 0) अणु
		put_unused_fd(r);
		fput(file);
		वापस -ENOMEM;
	पूर्ण
	kvm_uevent_notअगरy_change(KVM_EVENT_CREATE_VM, kvm);

	fd_install(r, file);
	वापस r;

put_kvm:
	kvm_put_kvm(kvm);
	वापस r;
पूर्ण

अटल दीर्घ kvm_dev_ioctl(काष्ठा file *filp,
			  अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	दीर्घ r = -EINVAL;

	चयन (ioctl) अणु
	हाल KVM_GET_API_VERSION:
		अगर (arg)
			जाओ out;
		r = KVM_API_VERSION;
		अवरोध;
	हाल KVM_CREATE_VM:
		r = kvm_dev_ioctl_create_vm(arg);
		अवरोध;
	हाल KVM_CHECK_EXTENSION:
		r = kvm_vm_ioctl_check_extension_generic(शून्य, arg);
		अवरोध;
	हाल KVM_GET_VCPU_MMAP_SIZE:
		अगर (arg)
			जाओ out;
		r = PAGE_SIZE;     /* काष्ठा kvm_run */
#अगर_घोषित CONFIG_X86
		r += PAGE_SIZE;    /* pio data page */
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_MMIO
		r += PAGE_SIZE;    /* coalesced mmio ring page */
#पूर्ण_अगर
		अवरोध;
	हाल KVM_TRACE_ENABLE:
	हाल KVM_TRACE_PAUSE:
	हाल KVM_TRACE_DISABLE:
		r = -EOPNOTSUPP;
		अवरोध;
	शेष:
		वापस kvm_arch_dev_ioctl(filp, ioctl, arg);
	पूर्ण
out:
	वापस r;
पूर्ण

अटल काष्ठा file_operations kvm_अक्षरdev_ops = अणु
	.unlocked_ioctl = kvm_dev_ioctl,
	.llseek		= noop_llseek,
	KVM_COMPAT(kvm_dev_ioctl),
पूर्ण;

अटल काष्ठा miscdevice kvm_dev = अणु
	KVM_MINOR,
	"kvm",
	&kvm_अक्षरdev_ops,
पूर्ण;

अटल व्योम hardware_enable_nolock(व्योम *junk)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	पूर्णांक r;

	अगर (cpumask_test_cpu(cpu, cpus_hardware_enabled))
		वापस;

	cpumask_set_cpu(cpu, cpus_hardware_enabled);

	r = kvm_arch_hardware_enable();

	अगर (r) अणु
		cpumask_clear_cpu(cpu, cpus_hardware_enabled);
		atomic_inc(&hardware_enable_failed);
		pr_info("kvm: enabling virtualization on CPU%d failed\n", cpu);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	raw_spin_lock(&kvm_count_lock);
	अगर (kvm_usage_count)
		hardware_enable_nolock(शून्य);
	raw_spin_unlock(&kvm_count_lock);
	वापस 0;
पूर्ण

अटल व्योम hardware_disable_nolock(व्योम *junk)
अणु
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (!cpumask_test_cpu(cpu, cpus_hardware_enabled))
		वापस;
	cpumask_clear_cpu(cpu, cpus_hardware_enabled);
	kvm_arch_hardware_disable();
पूर्ण

अटल पूर्णांक kvm_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	raw_spin_lock(&kvm_count_lock);
	अगर (kvm_usage_count)
		hardware_disable_nolock(शून्य);
	raw_spin_unlock(&kvm_count_lock);
	वापस 0;
पूर्ण

अटल व्योम hardware_disable_all_nolock(व्योम)
अणु
	BUG_ON(!kvm_usage_count);

	kvm_usage_count--;
	अगर (!kvm_usage_count)
		on_each_cpu(hardware_disable_nolock, शून्य, 1);
पूर्ण

अटल व्योम hardware_disable_all(व्योम)
अणु
	raw_spin_lock(&kvm_count_lock);
	hardware_disable_all_nolock();
	raw_spin_unlock(&kvm_count_lock);
पूर्ण

अटल पूर्णांक hardware_enable_all(व्योम)
अणु
	पूर्णांक r = 0;

	raw_spin_lock(&kvm_count_lock);

	kvm_usage_count++;
	अगर (kvm_usage_count == 1) अणु
		atomic_set(&hardware_enable_failed, 0);
		on_each_cpu(hardware_enable_nolock, शून्य, 1);

		अगर (atomic_पढ़ो(&hardware_enable_failed)) अणु
			hardware_disable_all_nolock();
			r = -EBUSY;
		पूर्ण
	पूर्ण

	raw_spin_unlock(&kvm_count_lock);

	वापस r;
पूर्ण

अटल पूर्णांक kvm_reboot(काष्ठा notअगरier_block *notअगरier, अचिन्हित दीर्घ val,
		      व्योम *v)
अणु
	/*
	 * Some (well, at least mine) BIOSes hang on reboot अगर
	 * in vmx root mode.
	 *
	 * And Intel TXT required VMX off क्रम all cpu when प्रणाली shutकरोwn.
	 */
	pr_info("kvm: exiting hardware virtualization\n");
	kvm_rebooting = true;
	on_each_cpu(hardware_disable_nolock, शून्य, 1);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block kvm_reboot_notअगरier = अणु
	.notअगरier_call = kvm_reboot,
	.priority = 0,
पूर्ण;

अटल व्योम kvm_io_bus_destroy(काष्ठा kvm_io_bus *bus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bus->dev_count; i++) अणु
		काष्ठा kvm_io_device *pos = bus->range[i].dev;

		kvm_iodevice_deकाष्ठाor(pos);
	पूर्ण
	kमुक्त(bus);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_io_bus_cmp(स्थिर काष्ठा kvm_io_range *r1,
				 स्थिर काष्ठा kvm_io_range *r2)
अणु
	gpa_t addr1 = r1->addr;
	gpa_t addr2 = r2->addr;

	अगर (addr1 < addr2)
		वापस -1;

	/* If r2->len == 0, match the exact address.  If r2->len != 0,
	 * accept any overlapping ग_लिखो.  Any order is acceptable क्रम
	 * overlapping ranges, because kvm_io_bus_get_first_dev ensures
	 * we process all of them.
	 */
	अगर (r2->len) अणु
		addr1 += r1->len;
		addr2 += r2->len;
	पूर्ण

	अगर (addr1 > addr2)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_io_bus_sort_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	वापस kvm_io_bus_cmp(p1, p2);
पूर्ण

अटल पूर्णांक kvm_io_bus_get_first_dev(काष्ठा kvm_io_bus *bus,
			     gpa_t addr, पूर्णांक len)
अणु
	काष्ठा kvm_io_range *range, key;
	पूर्णांक off;

	key = (काष्ठा kvm_io_range) अणु
		.addr = addr,
		.len = len,
	पूर्ण;

	range = द्वा_खोज(&key, bus->range, bus->dev_count,
			माप(काष्ठा kvm_io_range), kvm_io_bus_sort_cmp);
	अगर (range == शून्य)
		वापस -ENOENT;

	off = range - bus->range;

	जबतक (off > 0 && kvm_io_bus_cmp(&key, &bus->range[off-1]) == 0)
		off--;

	वापस off;
पूर्ण

अटल पूर्णांक __kvm_io_bus_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_bus *bus,
			      काष्ठा kvm_io_range *range, स्थिर व्योम *val)
अणु
	पूर्णांक idx;

	idx = kvm_io_bus_get_first_dev(bus, range->addr, range->len);
	अगर (idx < 0)
		वापस -EOPNOTSUPP;

	जबतक (idx < bus->dev_count &&
		kvm_io_bus_cmp(range, &bus->range[idx]) == 0) अणु
		अगर (!kvm_iodevice_ग_लिखो(vcpu, bus->range[idx].dev, range->addr,
					range->len, val))
			वापस idx;
		idx++;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

/* kvm_io_bus_ग_लिखो - called under kvm->slots_lock */
पूर्णांक kvm_io_bus_ग_लिखो(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx, gpa_t addr,
		     पूर्णांक len, स्थिर व्योम *val)
अणु
	काष्ठा kvm_io_bus *bus;
	काष्ठा kvm_io_range range;
	पूर्णांक r;

	range = (काष्ठा kvm_io_range) अणु
		.addr = addr,
		.len = len,
	पूर्ण;

	bus = srcu_dereference(vcpu->kvm->buses[bus_idx], &vcpu->kvm->srcu);
	अगर (!bus)
		वापस -ENOMEM;
	r = __kvm_io_bus_ग_लिखो(vcpu, bus, &range, val);
	वापस r < 0 ? r : 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_io_bus_ग_लिखो);

/* kvm_io_bus_ग_लिखो_cookie - called under kvm->slots_lock */
पूर्णांक kvm_io_bus_ग_लिखो_cookie(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx,
			    gpa_t addr, पूर्णांक len, स्थिर व्योम *val, दीर्घ cookie)
अणु
	काष्ठा kvm_io_bus *bus;
	काष्ठा kvm_io_range range;

	range = (काष्ठा kvm_io_range) अणु
		.addr = addr,
		.len = len,
	पूर्ण;

	bus = srcu_dereference(vcpu->kvm->buses[bus_idx], &vcpu->kvm->srcu);
	अगर (!bus)
		वापस -ENOMEM;

	/* First try the device referenced by cookie. */
	अगर ((cookie >= 0) && (cookie < bus->dev_count) &&
	    (kvm_io_bus_cmp(&range, &bus->range[cookie]) == 0))
		अगर (!kvm_iodevice_ग_लिखो(vcpu, bus->range[cookie].dev, addr, len,
					val))
			वापस cookie;

	/*
	 * cookie contained garbage; fall back to search and वापस the
	 * correct cookie value.
	 */
	वापस __kvm_io_bus_ग_लिखो(vcpu, bus, &range, val);
पूर्ण

अटल पूर्णांक __kvm_io_bus_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_bus *bus,
			     काष्ठा kvm_io_range *range, व्योम *val)
अणु
	पूर्णांक idx;

	idx = kvm_io_bus_get_first_dev(bus, range->addr, range->len);
	अगर (idx < 0)
		वापस -EOPNOTSUPP;

	जबतक (idx < bus->dev_count &&
		kvm_io_bus_cmp(range, &bus->range[idx]) == 0) अणु
		अगर (!kvm_iodevice_पढ़ो(vcpu, bus->range[idx].dev, range->addr,
				       range->len, val))
			वापस idx;
		idx++;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

/* kvm_io_bus_पढ़ो - called under kvm->slots_lock */
पूर्णांक kvm_io_bus_पढ़ो(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx, gpa_t addr,
		    पूर्णांक len, व्योम *val)
अणु
	काष्ठा kvm_io_bus *bus;
	काष्ठा kvm_io_range range;
	पूर्णांक r;

	range = (काष्ठा kvm_io_range) अणु
		.addr = addr,
		.len = len,
	पूर्ण;

	bus = srcu_dereference(vcpu->kvm->buses[bus_idx], &vcpu->kvm->srcu);
	अगर (!bus)
		वापस -ENOMEM;
	r = __kvm_io_bus_पढ़ो(vcpu, bus, &range, val);
	वापस r < 0 ? r : 0;
पूर्ण

/* Caller must hold slots_lock. */
पूर्णांक kvm_io_bus_रेजिस्टर_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx, gpa_t addr,
			    पूर्णांक len, काष्ठा kvm_io_device *dev)
अणु
	पूर्णांक i;
	काष्ठा kvm_io_bus *new_bus, *bus;
	काष्ठा kvm_io_range range;

	bus = kvm_get_bus(kvm, bus_idx);
	अगर (!bus)
		वापस -ENOMEM;

	/* exclude ioeventfd which is limited by maximum fd */
	अगर (bus->dev_count - bus->ioeventfd_count > NR_IOBUS_DEVS - 1)
		वापस -ENOSPC;

	new_bus = kदो_स्मृति(काष्ठा_size(bus, range, bus->dev_count + 1),
			  GFP_KERNEL_ACCOUNT);
	अगर (!new_bus)
		वापस -ENOMEM;

	range = (काष्ठा kvm_io_range) अणु
		.addr = addr,
		.len = len,
		.dev = dev,
	पूर्ण;

	क्रम (i = 0; i < bus->dev_count; i++)
		अगर (kvm_io_bus_cmp(&bus->range[i], &range) > 0)
			अवरोध;

	स_नकल(new_bus, bus, माप(*bus) + i * माप(काष्ठा kvm_io_range));
	new_bus->dev_count++;
	new_bus->range[i] = range;
	स_नकल(new_bus->range + i + 1, bus->range + i,
		(bus->dev_count - i) * माप(काष्ठा kvm_io_range));
	rcu_assign_poपूर्णांकer(kvm->buses[bus_idx], new_bus);
	synchronize_srcu_expedited(&kvm->srcu);
	kमुक्त(bus);

	वापस 0;
पूर्ण

पूर्णांक kvm_io_bus_unरेजिस्टर_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx,
			      काष्ठा kvm_io_device *dev)
अणु
	पूर्णांक i, j;
	काष्ठा kvm_io_bus *new_bus, *bus;

	lockdep_निश्चित_held(&kvm->slots_lock);

	bus = kvm_get_bus(kvm, bus_idx);
	अगर (!bus)
		वापस 0;

	क्रम (i = 0; i < bus->dev_count; i++) अणु
		अगर (bus->range[i].dev == dev) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == bus->dev_count)
		वापस 0;

	new_bus = kदो_स्मृति(काष्ठा_size(bus, range, bus->dev_count - 1),
			  GFP_KERNEL_ACCOUNT);
	अगर (new_bus) अणु
		स_नकल(new_bus, bus, काष्ठा_size(bus, range, i));
		new_bus->dev_count--;
		स_नकल(new_bus->range + i, bus->range + i + 1,
				flex_array_size(new_bus, range, new_bus->dev_count - i));
	पूर्ण

	rcu_assign_poपूर्णांकer(kvm->buses[bus_idx], new_bus);
	synchronize_srcu_expedited(&kvm->srcu);

	/* Destroy the old bus _after_ installing the (null) bus. */
	अगर (!new_bus) अणु
		pr_err("kvm: failed to shrink bus, removing it completely\n");
		क्रम (j = 0; j < bus->dev_count; j++) अणु
			अगर (j == i)
				जारी;
			kvm_iodevice_deकाष्ठाor(bus->range[j].dev);
		पूर्ण
	पूर्ण

	kमुक्त(bus);
	वापस new_bus ? 0 : -ENOMEM;
पूर्ण

काष्ठा kvm_io_device *kvm_io_bus_get_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx,
					 gpa_t addr)
अणु
	काष्ठा kvm_io_bus *bus;
	पूर्णांक dev_idx, srcu_idx;
	काष्ठा kvm_io_device *iodev = शून्य;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);

	bus = srcu_dereference(kvm->buses[bus_idx], &kvm->srcu);
	अगर (!bus)
		जाओ out_unlock;

	dev_idx = kvm_io_bus_get_first_dev(bus, addr, 1);
	अगर (dev_idx < 0)
		जाओ out_unlock;

	iodev = bus->range[dev_idx].dev;

out_unlock:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	वापस iodev;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_io_bus_get_dev);

अटल पूर्णांक kvm_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			   पूर्णांक (*get)(व्योम *, u64 *), पूर्णांक (*set)(व्योम *, u64),
			   स्थिर अक्षर *fmt)
अणु
	काष्ठा kvm_stat_data *stat_data = (काष्ठा kvm_stat_data *)
					  inode->i_निजी;

	/* The debugfs files are a reference to the kvm काष्ठा which
	 * is still valid when kvm_destroy_vm is called.
	 * To aव्योम the race between खोलो and the removal of the debugfs
	 * directory we test against the users count.
	 */
	अगर (!refcount_inc_not_zero(&stat_data->kvm->users_count))
		वापस -ENOENT;

	अगर (simple_attr_खोलो(inode, file, get,
		    KVM_DBGFS_GET_MODE(stat_data->dbgfs_item) & 0222
		    ? set : शून्य,
		    fmt)) अणु
		kvm_put_kvm(stat_data->kvm);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kvm_stat_data *stat_data = (काष्ठा kvm_stat_data *)
					  inode->i_निजी;

	simple_attr_release(inode, file);
	kvm_put_kvm(stat_data->kvm);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_get_stat_per_vm(काष्ठा kvm *kvm, माप_प्रकार offset, u64 *val)
अणु
	*val = *(uदीर्घ *)((व्योम *)kvm + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_clear_stat_per_vm(काष्ठा kvm *kvm, माप_प्रकार offset)
अणु
	*(uदीर्घ *)((व्योम *)kvm + offset) = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_get_stat_per_vcpu(काष्ठा kvm *kvm, माप_प्रकार offset, u64 *val)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	*val = 0;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		*val += *(u64 *)((व्योम *)vcpu + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_clear_stat_per_vcpu(काष्ठा kvm *kvm, माप_प्रकार offset)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		*(u64 *)((व्योम *)vcpu + offset) = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_stat_data_get(व्योम *data, u64 *val)
अणु
	पूर्णांक r = -EFAULT;
	काष्ठा kvm_stat_data *stat_data = (काष्ठा kvm_stat_data *)data;

	चयन (stat_data->dbgfs_item->kind) अणु
	हाल KVM_STAT_VM:
		r = kvm_get_stat_per_vm(stat_data->kvm,
					stat_data->dbgfs_item->offset, val);
		अवरोध;
	हाल KVM_STAT_VCPU:
		r = kvm_get_stat_per_vcpu(stat_data->kvm,
					  stat_data->dbgfs_item->offset, val);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_stat_data_clear(व्योम *data, u64 val)
अणु
	पूर्णांक r = -EFAULT;
	काष्ठा kvm_stat_data *stat_data = (काष्ठा kvm_stat_data *)data;

	अगर (val)
		वापस -EINVAL;

	चयन (stat_data->dbgfs_item->kind) अणु
	हाल KVM_STAT_VM:
		r = kvm_clear_stat_per_vm(stat_data->kvm,
					  stat_data->dbgfs_item->offset);
		अवरोध;
	हाल KVM_STAT_VCPU:
		r = kvm_clear_stat_per_vcpu(stat_data->kvm,
					    stat_data->dbgfs_item->offset);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_stat_data_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	__simple_attr_check_क्रमmat("%llu\n", 0ull);
	वापस kvm_debugfs_खोलो(inode, file, kvm_stat_data_get,
				kvm_stat_data_clear, "%llu\n");
पूर्ण

अटल स्थिर काष्ठा file_operations stat_fops_per_vm = अणु
	.owner = THIS_MODULE,
	.खोलो = kvm_stat_data_खोलो,
	.release = kvm_debugfs_release,
	.पढ़ो = simple_attr_पढ़ो,
	.ग_लिखो = simple_attr_ग_लिखो,
	.llseek = no_llseek,
पूर्ण;

अटल पूर्णांक vm_stat_get(व्योम *_offset, u64 *val)
अणु
	अचिन्हित offset = (दीर्घ)_offset;
	काष्ठा kvm *kvm;
	u64 पंचांगp_val;

	*val = 0;
	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_get_stat_per_vm(kvm, offset, &पंचांगp_val);
		*val += पंचांगp_val;
	पूर्ण
	mutex_unlock(&kvm_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक vm_stat_clear(व्योम *_offset, u64 val)
अणु
	अचिन्हित offset = (दीर्घ)_offset;
	काष्ठा kvm *kvm;

	अगर (val)
		वापस -EINVAL;

	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_clear_stat_per_vm(kvm, offset);
	पूर्ण
	mutex_unlock(&kvm_lock);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vm_stat_fops, vm_stat_get, vm_stat_clear, "%llu\n");

अटल पूर्णांक vcpu_stat_get(व्योम *_offset, u64 *val)
अणु
	अचिन्हित offset = (दीर्घ)_offset;
	काष्ठा kvm *kvm;
	u64 पंचांगp_val;

	*val = 0;
	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_get_stat_per_vcpu(kvm, offset, &पंचांगp_val);
		*val += पंचांगp_val;
	पूर्ण
	mutex_unlock(&kvm_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक vcpu_stat_clear(व्योम *_offset, u64 val)
अणु
	अचिन्हित offset = (दीर्घ)_offset;
	काष्ठा kvm *kvm;

	अगर (val)
		वापस -EINVAL;

	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_clear_stat_per_vcpu(kvm, offset);
	पूर्ण
	mutex_unlock(&kvm_lock);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vcpu_stat_fops, vcpu_stat_get, vcpu_stat_clear,
			"%llu\n");

अटल स्थिर काष्ठा file_operations *stat_fops[] = अणु
	[KVM_STAT_VCPU] = &vcpu_stat_fops,
	[KVM_STAT_VM]   = &vm_stat_fops,
पूर्ण;

अटल व्योम kvm_uevent_notअगरy_change(अचिन्हित पूर्णांक type, काष्ठा kvm *kvm)
अणु
	काष्ठा kobj_uevent_env *env;
	अचिन्हित दीर्घ दीर्घ created, active;

	अगर (!kvm_dev.this_device || !kvm)
		वापस;

	mutex_lock(&kvm_lock);
	अगर (type == KVM_EVENT_CREATE_VM) अणु
		kvm_createvm_count++;
		kvm_active_vms++;
	पूर्ण अन्यथा अगर (type == KVM_EVENT_DESTROY_VM) अणु
		kvm_active_vms--;
	पूर्ण
	created = kvm_createvm_count;
	active = kvm_active_vms;
	mutex_unlock(&kvm_lock);

	env = kzalloc(माप(*env), GFP_KERNEL_ACCOUNT);
	अगर (!env)
		वापस;

	add_uevent_var(env, "CREATED=%llu", created);
	add_uevent_var(env, "COUNT=%llu", active);

	अगर (type == KVM_EVENT_CREATE_VM) अणु
		add_uevent_var(env, "EVENT=create");
		kvm->userspace_pid = task_pid_nr(current);
	पूर्ण अन्यथा अगर (type == KVM_EVENT_DESTROY_VM) अणु
		add_uevent_var(env, "EVENT=destroy");
	पूर्ण
	add_uevent_var(env, "PID=%d", kvm->userspace_pid);

	अगर (!IS_ERR_OR_शून्य(kvm->debugfs_dentry)) अणु
		अक्षर *पंचांगp, *p = kदो_स्मृति(PATH_MAX, GFP_KERNEL_ACCOUNT);

		अगर (p) अणु
			पंचांगp = dentry_path_raw(kvm->debugfs_dentry, p, PATH_MAX);
			अगर (!IS_ERR(पंचांगp))
				add_uevent_var(env, "STATS_PATH=%s", पंचांगp);
			kमुक्त(p);
		पूर्ण
	पूर्ण
	/* no need क्रम checks, since we are adding at most only 5 keys */
	env->envp[env->envp_idx++] = शून्य;
	kobject_uevent_env(&kvm_dev.this_device->kobj, KOBJ_CHANGE, env->envp);
	kमुक्त(env);
पूर्ण

अटल व्योम kvm_init_debug(व्योम)
अणु
	काष्ठा kvm_stats_debugfs_item *p;

	kvm_debugfs_dir = debugfs_create_dir("kvm", शून्य);

	kvm_debugfs_num_entries = 0;
	क्रम (p = debugfs_entries; p->name; ++p, kvm_debugfs_num_entries++) अणु
		debugfs_create_file(p->name, KVM_DBGFS_GET_MODE(p),
				    kvm_debugfs_dir, (व्योम *)(दीर्घ)p->offset,
				    stat_fops[p->kind]);
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_suspend(व्योम)
अणु
	अगर (kvm_usage_count)
		hardware_disable_nolock(शून्य);
	वापस 0;
पूर्ण

अटल व्योम kvm_resume(व्योम)
अणु
	अगर (kvm_usage_count) अणु
#अगर_घोषित CONFIG_LOCKDEP
		WARN_ON(lockdep_is_held(&kvm_count_lock));
#पूर्ण_अगर
		hardware_enable_nolock(शून्य);
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops kvm_syscore_ops = अणु
	.suspend = kvm_suspend,
	.resume = kvm_resume,
पूर्ण;

अटल अंतरभूत
काष्ठा kvm_vcpu *preempt_notअगरier_to_vcpu(काष्ठा preempt_notअगरier *pn)
अणु
	वापस container_of(pn, काष्ठा kvm_vcpu, preempt_notअगरier);
पूर्ण

अटल व्योम kvm_sched_in(काष्ठा preempt_notअगरier *pn, पूर्णांक cpu)
अणु
	काष्ठा kvm_vcpu *vcpu = preempt_notअगरier_to_vcpu(pn);

	WRITE_ONCE(vcpu->preempted, false);
	WRITE_ONCE(vcpu->पढ़ोy, false);

	__this_cpu_ग_लिखो(kvm_running_vcpu, vcpu);
	kvm_arch_sched_in(vcpu, cpu);
	kvm_arch_vcpu_load(vcpu, cpu);
पूर्ण

अटल व्योम kvm_sched_out(काष्ठा preempt_notअगरier *pn,
			  काष्ठा task_काष्ठा *next)
अणु
	काष्ठा kvm_vcpu *vcpu = preempt_notअगरier_to_vcpu(pn);

	अगर (current->state == TASK_RUNNING) अणु
		WRITE_ONCE(vcpu->preempted, true);
		WRITE_ONCE(vcpu->पढ़ोy, true);
	पूर्ण
	kvm_arch_vcpu_put(vcpu);
	__this_cpu_ग_लिखो(kvm_running_vcpu, शून्य);
पूर्ण

/**
 * kvm_get_running_vcpu - get the vcpu running on the current CPU.
 *
 * We can disable preemption locally around accessing the per-CPU variable,
 * and use the resolved vcpu poपूर्णांकer after enabling preemption again,
 * because even अगर the current thपढ़ो is migrated to another CPU, पढ़ोing
 * the per-CPU value later will give us the same value as we update the
 * per-CPU variable in the preempt notअगरier handlers.
 */
काष्ठा kvm_vcpu *kvm_get_running_vcpu(व्योम)
अणु
	काष्ठा kvm_vcpu *vcpu;

	preempt_disable();
	vcpu = __this_cpu_पढ़ो(kvm_running_vcpu);
	preempt_enable();

	वापस vcpu;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_running_vcpu);

/**
 * kvm_get_running_vcpus - get the per-CPU array of currently running vcpus.
 */
काष्ठा kvm_vcpu * __percpu *kvm_get_running_vcpus(व्योम)
अणु
        वापस &kvm_running_vcpu;
पूर्ण

काष्ठा kvm_cpu_compat_check अणु
	व्योम *opaque;
	पूर्णांक *ret;
पूर्ण;

अटल व्योम check_processor_compat(व्योम *data)
अणु
	काष्ठा kvm_cpu_compat_check *c = data;

	*c->ret = kvm_arch_check_processor_compat(c->opaque);
पूर्ण

पूर्णांक kvm_init(व्योम *opaque, अचिन्हित vcpu_size, अचिन्हित vcpu_align,
		  काष्ठा module *module)
अणु
	काष्ठा kvm_cpu_compat_check c;
	पूर्णांक r;
	पूर्णांक cpu;

	r = kvm_arch_init(opaque);
	अगर (r)
		जाओ out_fail;

	/*
	 * kvm_arch_init makes sure there's at most one caller
	 * क्रम architectures that support multiple implementations,
	 * like पूर्णांकel and amd on x86.
	 * kvm_arch_init must be called beक्रमe kvm_irqfd_init to aव्योम creating
	 * conflicts in हाल kvm is alपढ़ोy setup क्रम another implementation.
	 */
	r = kvm_irqfd_init();
	अगर (r)
		जाओ out_irqfd;

	अगर (!zalloc_cpumask_var(&cpus_hardware_enabled, GFP_KERNEL)) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_0;
	पूर्ण

	r = kvm_arch_hardware_setup(opaque);
	अगर (r < 0)
		जाओ out_मुक्त_1;

	c.ret = &r;
	c.opaque = opaque;
	क्रम_each_online_cpu(cpu) अणु
		smp_call_function_single(cpu, check_processor_compat, &c, 1);
		अगर (r < 0)
			जाओ out_मुक्त_2;
	पूर्ण

	r = cpuhp_setup_state_nocalls(CPUHP_AP_KVM_STARTING, "kvm/cpu:starting",
				      kvm_starting_cpu, kvm_dying_cpu);
	अगर (r)
		जाओ out_मुक्त_2;
	रेजिस्टर_reboot_notअगरier(&kvm_reboot_notअगरier);

	/* A kmem cache lets us meet the alignment requirements of fx_save. */
	अगर (!vcpu_align)
		vcpu_align = __alignof__(काष्ठा kvm_vcpu);
	kvm_vcpu_cache =
		kmem_cache_create_usercopy("kvm_vcpu", vcpu_size, vcpu_align,
					   SLAB_ACCOUNT,
					   दुरत्व(काष्ठा kvm_vcpu, arch),
					   माप_field(काष्ठा kvm_vcpu, arch),
					   शून्य);
	अगर (!kvm_vcpu_cache) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_3;
	पूर्ण

	r = kvm_async_pf_init();
	अगर (r)
		जाओ out_मुक्त;

	kvm_अक्षरdev_ops.owner = module;
	kvm_vm_fops.owner = module;
	kvm_vcpu_fops.owner = module;

	r = misc_रेजिस्टर(&kvm_dev);
	अगर (r) अणु
		pr_err("kvm: misc device register failed\n");
		जाओ out_unreg;
	पूर्ण

	रेजिस्टर_syscore_ops(&kvm_syscore_ops);

	kvm_preempt_ops.sched_in = kvm_sched_in;
	kvm_preempt_ops.sched_out = kvm_sched_out;

	kvm_init_debug();

	r = kvm_vfio_ops_init();
	WARN_ON(r);

	वापस 0;

out_unreg:
	kvm_async_pf_deinit();
out_मुक्त:
	kmem_cache_destroy(kvm_vcpu_cache);
out_मुक्त_3:
	unरेजिस्टर_reboot_notअगरier(&kvm_reboot_notअगरier);
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_KVM_STARTING);
out_मुक्त_2:
	kvm_arch_hardware_unsetup();
out_मुक्त_1:
	मुक्त_cpumask_var(cpus_hardware_enabled);
out_मुक्त_0:
	kvm_irqfd_निकास();
out_irqfd:
	kvm_arch_निकास();
out_fail:
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_init);

व्योम kvm_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(kvm_debugfs_dir);
	misc_deरेजिस्टर(&kvm_dev);
	kmem_cache_destroy(kvm_vcpu_cache);
	kvm_async_pf_deinit();
	unरेजिस्टर_syscore_ops(&kvm_syscore_ops);
	unरेजिस्टर_reboot_notअगरier(&kvm_reboot_notअगरier);
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_KVM_STARTING);
	on_each_cpu(hardware_disable_nolock, शून्य, 1);
	kvm_arch_hardware_unsetup();
	kvm_arch_निकास();
	kvm_irqfd_निकास();
	मुक्त_cpumask_var(cpus_hardware_enabled);
	kvm_vfio_ops_निकास();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_निकास);

काष्ठा kvm_vm_worker_thपढ़ो_context अणु
	काष्ठा kvm *kvm;
	काष्ठा task_काष्ठा *parent;
	काष्ठा completion init_करोne;
	kvm_vm_thपढ़ो_fn_t thपढ़ो_fn;
	uपूर्णांकptr_t data;
	पूर्णांक err;
पूर्ण;

अटल पूर्णांक kvm_vm_worker_thपढ़ो(व्योम *context)
अणु
	/*
	 * The init_context is allocated on the stack of the parent thपढ़ो, so
	 * we have to locally copy anything that is needed beyond initialization
	 */
	काष्ठा kvm_vm_worker_thपढ़ो_context *init_context = context;
	काष्ठा kvm *kvm = init_context->kvm;
	kvm_vm_thपढ़ो_fn_t thपढ़ो_fn = init_context->thपढ़ो_fn;
	uपूर्णांकptr_t data = init_context->data;
	पूर्णांक err;

	err = kthपढ़ो_park(current);
	/* kthपढ़ो_park(current) is never supposed to वापस an error */
	WARN_ON(err != 0);
	अगर (err)
		जाओ init_complete;

	err = cgroup_attach_task_all(init_context->parent, current);
	अगर (err) अणु
		kvm_err("%s: cgroup_attach_task_all failed with err %d\n",
			__func__, err);
		जाओ init_complete;
	पूर्ण

	set_user_nice(current, task_nice(init_context->parent));

init_complete:
	init_context->err = err;
	complete(&init_context->init_करोne);
	init_context = शून्य;

	अगर (err)
		वापस err;

	/* Wait to be woken up by the spawner beक्रमe proceeding. */
	kthपढ़ो_parkme();

	अगर (!kthपढ़ो_should_stop())
		err = thपढ़ो_fn(kvm, data);

	वापस err;
पूर्ण

पूर्णांक kvm_vm_create_worker_thपढ़ो(काष्ठा kvm *kvm, kvm_vm_thपढ़ो_fn_t thपढ़ो_fn,
				uपूर्णांकptr_t data, स्थिर अक्षर *name,
				काष्ठा task_काष्ठा **thपढ़ो_ptr)
अणु
	काष्ठा kvm_vm_worker_thपढ़ो_context init_context = अणुपूर्ण;
	काष्ठा task_काष्ठा *thपढ़ो;

	*thपढ़ो_ptr = शून्य;
	init_context.kvm = kvm;
	init_context.parent = current;
	init_context.thपढ़ो_fn = thपढ़ो_fn;
	init_context.data = data;
	init_completion(&init_context.init_करोne);

	thपढ़ो = kthपढ़ो_run(kvm_vm_worker_thपढ़ो, &init_context,
			     "%s-%d", name, task_pid_nr(current));
	अगर (IS_ERR(thपढ़ो))
		वापस PTR_ERR(thपढ़ो);

	/* kthपढ़ो_run is never supposed to वापस शून्य */
	WARN_ON(thपढ़ो == शून्य);

	रुको_क्रम_completion(&init_context.init_करोne);

	अगर (!init_context.err)
		*thपढ़ो_ptr = thपढ़ो;

	वापस init_context.err;
पूर्ण
