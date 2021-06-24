<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * KVM paravirt_ops implementation
 *
 * Copyright (C) 2007, Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 * Copyright IBM Corporation, 2007
 *   Authors: Anthony Liguori <aliguori@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) "kvm-guest: " fmt

#समावेश <linux/context_tracking.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/hash.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sरुको.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cpuidle_haltpoll.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/svm.h>

DEFINE_STATIC_KEY_FALSE(kvm_async_pf_enabled);

अटल पूर्णांक kvmapf = 1;

अटल पूर्णांक __init parse_no_kvmapf(अक्षर *arg)
अणु
        kvmapf = 0;
        वापस 0;
पूर्ण

early_param("no-kvmapf", parse_no_kvmapf);

अटल पूर्णांक steal_acc = 1;
अटल पूर्णांक __init parse_no_stealacc(अक्षर *arg)
अणु
        steal_acc = 0;
        वापस 0;
पूर्ण

early_param("no-steal-acc", parse_no_stealacc);

अटल DEFINE_PER_CPU_DECRYPTED(काष्ठा kvm_vcpu_pv_apf_data, apf_reason) __aligned(64);
DEFINE_PER_CPU_DECRYPTED(काष्ठा kvm_steal_समय, steal_समय) __aligned(64) __visible;
अटल पूर्णांक has_steal_घड़ी = 0;

/*
 * No need क्रम any "IO delay" on KVM
 */
अटल व्योम kvm_io_delay(व्योम)
अणु
पूर्ण

#घोषणा KVM_TASK_SLEEP_HASHBITS 8
#घोषणा KVM_TASK_SLEEP_HASHSIZE (1<<KVM_TASK_SLEEP_HASHBITS)

काष्ठा kvm_task_sleep_node अणु
	काष्ठा hlist_node link;
	काष्ठा sरुको_queue_head wq;
	u32 token;
	पूर्णांक cpu;
पूर्ण;

अटल काष्ठा kvm_task_sleep_head अणु
	raw_spinlock_t lock;
	काष्ठा hlist_head list;
पूर्ण async_pf_sleepers[KVM_TASK_SLEEP_HASHSIZE];

अटल काष्ठा kvm_task_sleep_node *_find_apf_task(काष्ठा kvm_task_sleep_head *b,
						  u32 token)
अणु
	काष्ठा hlist_node *p;

	hlist_क्रम_each(p, &b->list) अणु
		काष्ठा kvm_task_sleep_node *n =
			hlist_entry(p, typeof(*n), link);
		अगर (n->token == token)
			वापस n;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool kvm_async_pf_queue_task(u32 token, काष्ठा kvm_task_sleep_node *n)
अणु
	u32 key = hash_32(token, KVM_TASK_SLEEP_HASHBITS);
	काष्ठा kvm_task_sleep_head *b = &async_pf_sleepers[key];
	काष्ठा kvm_task_sleep_node *e;

	raw_spin_lock(&b->lock);
	e = _find_apf_task(b, token);
	अगर (e) अणु
		/* dummy entry exist -> wake up was delivered ahead of PF */
		hlist_del(&e->link);
		raw_spin_unlock(&b->lock);
		kमुक्त(e);
		वापस false;
	पूर्ण

	n->token = token;
	n->cpu = smp_processor_id();
	init_sरुको_queue_head(&n->wq);
	hlist_add_head(&n->link, &b->list);
	raw_spin_unlock(&b->lock);
	वापस true;
पूर्ण

/*
 * kvm_async_pf_task_रुको_schedule - Wait क्रम pagefault to be handled
 * @token:	Token to identअगरy the sleep node entry
 *
 * Invoked from the async pagefault handling code or from the VM निकास page
 * fault handler. In both हालs RCU is watching.
 */
व्योम kvm_async_pf_task_रुको_schedule(u32 token)
अणु
	काष्ठा kvm_task_sleep_node n;
	DECLARE_SWAITQUEUE(रुको);

	lockdep_निश्चित_irqs_disabled();

	अगर (!kvm_async_pf_queue_task(token, &n))
		वापस;

	क्रम (;;) अणु
		prepare_to_sरुको_exclusive(&n.wq, &रुको, TASK_UNINTERRUPTIBLE);
		अगर (hlist_unhashed(&n.link))
			अवरोध;

		local_irq_enable();
		schedule();
		local_irq_disable();
	पूर्ण
	finish_sरुको(&n.wq, &रुको);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_async_pf_task_रुको_schedule);

अटल व्योम apf_task_wake_one(काष्ठा kvm_task_sleep_node *n)
अणु
	hlist_del_init(&n->link);
	अगर (swq_has_sleeper(&n->wq))
		swake_up_one(&n->wq);
पूर्ण

अटल व्योम apf_task_wake_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVM_TASK_SLEEP_HASHSIZE; i++) अणु
		काष्ठा kvm_task_sleep_head *b = &async_pf_sleepers[i];
		काष्ठा kvm_task_sleep_node *n;
		काष्ठा hlist_node *p, *next;

		raw_spin_lock(&b->lock);
		hlist_क्रम_each_safe(p, next, &b->list) अणु
			n = hlist_entry(p, typeof(*n), link);
			अगर (n->cpu == smp_processor_id())
				apf_task_wake_one(n);
		पूर्ण
		raw_spin_unlock(&b->lock);
	पूर्ण
पूर्ण

व्योम kvm_async_pf_task_wake(u32 token)
अणु
	u32 key = hash_32(token, KVM_TASK_SLEEP_HASHBITS);
	काष्ठा kvm_task_sleep_head *b = &async_pf_sleepers[key];
	काष्ठा kvm_task_sleep_node *n;

	अगर (token == ~0) अणु
		apf_task_wake_all();
		वापस;
	पूर्ण

again:
	raw_spin_lock(&b->lock);
	n = _find_apf_task(b, token);
	अगर (!n) अणु
		/*
		 * async PF was not yet handled.
		 * Add dummy entry क्रम the token.
		 */
		n = kzalloc(माप(*n), GFP_ATOMIC);
		अगर (!n) अणु
			/*
			 * Allocation failed! Busy रुको जबतक other cpu
			 * handles async PF.
			 */
			raw_spin_unlock(&b->lock);
			cpu_relax();
			जाओ again;
		पूर्ण
		n->token = token;
		n->cpu = smp_processor_id();
		init_sरुको_queue_head(&n->wq);
		hlist_add_head(&n->link, &b->list);
	पूर्ण अन्यथा अणु
		apf_task_wake_one(n);
	पूर्ण
	raw_spin_unlock(&b->lock);
	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_async_pf_task_wake);

noinstr u32 kvm_पढ़ो_and_reset_apf_flags(व्योम)
अणु
	u32 flags = 0;

	अगर (__this_cpu_पढ़ो(apf_reason.enabled)) अणु
		flags = __this_cpu_पढ़ो(apf_reason.flags);
		__this_cpu_ग_लिखो(apf_reason.flags, 0);
	पूर्ण

	वापस flags;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_and_reset_apf_flags);

noinstr bool __kvm_handle_async_pf(काष्ठा pt_regs *regs, u32 token)
अणु
	u32 flags = kvm_पढ़ो_and_reset_apf_flags();
	irqentry_state_t state;

	अगर (!flags)
		वापस false;

	state = irqentry_enter(regs);
	instrumentation_begin();

	/*
	 * If the host managed to inject an async #PF पूर्णांकo an पूर्णांकerrupt
	 * disabled region, then die hard as this is not going to end well
	 * and the host side is seriously broken.
	 */
	अगर (unlikely(!(regs->flags & X86_EFLAGS_IF)))
		panic("Host injected async #PF in interrupt disabled region\n");

	अगर (flags & KVM_PV_REASON_PAGE_NOT_PRESENT) अणु
		अगर (unlikely(!(user_mode(regs))))
			panic("Host injected async #PF in kernel mode\n");
		/* Page is swapped out by the host. */
		kvm_async_pf_task_रुको_schedule(token);
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Unexpected async PF flags: %x\n", flags);
	पूर्ण

	instrumentation_end();
	irqentry_निकास(regs, state);
	वापस true;
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_kvm_asyncpf_पूर्णांकerrupt)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	u32 token;

	ack_APIC_irq();

	inc_irq_stat(irq_hv_callback_count);

	अगर (__this_cpu_पढ़ो(apf_reason.enabled)) अणु
		token = __this_cpu_पढ़ो(apf_reason.token);
		kvm_async_pf_task_wake(token);
		__this_cpu_ग_लिखो(apf_reason.token, 0);
		wrmsrl(MSR_KVM_ASYNC_PF_ACK, 1);
	पूर्ण

	set_irq_regs(old_regs);
पूर्ण

अटल व्योम __init paravirt_ops_setup(व्योम)
अणु
	pv_info.name = "KVM";

	अगर (kvm_para_has_feature(KVM_FEATURE_NOP_IO_DELAY))
		pv_ops.cpu.io_delay = kvm_io_delay;

#अगर_घोषित CONFIG_X86_IO_APIC
	no_समयr_check = 1;
#पूर्ण_अगर
पूर्ण

अटल व्योम kvm_रेजिस्टर_steal_समय(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा kvm_steal_समय *st = &per_cpu(steal_समय, cpu);

	अगर (!has_steal_घड़ी)
		वापस;

	wrmsrl(MSR_KVM_STEAL_TIME, (slow_virt_to_phys(st) | KVM_MSR_ENABLED));
	pr_info("stealtime: cpu %d, msr %llx\n", cpu,
		(अचिन्हित दीर्घ दीर्घ) slow_virt_to_phys(st));
पूर्ण

अटल DEFINE_PER_CPU_DECRYPTED(अचिन्हित दीर्घ, kvm_apic_eoi) = KVM_PV_EOI_DISABLED;

अटल notrace व्योम kvm_guest_apic_eoi_ग_लिखो(u32 reg, u32 val)
अणु
	/**
	 * This relies on __test_and_clear_bit to modअगरy the memory
	 * in a way that is atomic with respect to the local CPU.
	 * The hypervisor only accesses this memory from the local CPU so
	 * there's no need क्रम lock or memory barriers.
	 * An optimization barrier is implied in apic ग_लिखो.
	 */
	अगर (__test_and_clear_bit(KVM_PV_EOI_BIT, this_cpu_ptr(&kvm_apic_eoi)))
		वापस;
	apic->native_eoi_ग_लिखो(APIC_EOI, APIC_EOI_ACK);
पूर्ण

अटल व्योम kvm_guest_cpu_init(व्योम)
अणु
	अगर (kvm_para_has_feature(KVM_FEATURE_ASYNC_PF_INT) && kvmapf) अणु
		u64 pa = slow_virt_to_phys(this_cpu_ptr(&apf_reason));

		WARN_ON_ONCE(!अटल_branch_likely(&kvm_async_pf_enabled));

		pa = slow_virt_to_phys(this_cpu_ptr(&apf_reason));
		pa |= KVM_ASYNC_PF_ENABLED | KVM_ASYNC_PF_DELIVERY_AS_INT;

		अगर (kvm_para_has_feature(KVM_FEATURE_ASYNC_PF_VMEXIT))
			pa |= KVM_ASYNC_PF_DELIVERY_AS_PF_VMEXIT;

		wrmsrl(MSR_KVM_ASYNC_PF_INT, HYPERVISOR_CALLBACK_VECTOR);

		wrmsrl(MSR_KVM_ASYNC_PF_EN, pa);
		__this_cpu_ग_लिखो(apf_reason.enabled, 1);
		pr_info("setup async PF for cpu %d\n", smp_processor_id());
	पूर्ण

	अगर (kvm_para_has_feature(KVM_FEATURE_PV_EOI)) अणु
		अचिन्हित दीर्घ pa;

		/* Size alignment is implied but just to make it explicit. */
		BUILD_BUG_ON(__alignof__(kvm_apic_eoi) < 4);
		__this_cpu_ग_लिखो(kvm_apic_eoi, 0);
		pa = slow_virt_to_phys(this_cpu_ptr(&kvm_apic_eoi))
			| KVM_MSR_ENABLED;
		wrmsrl(MSR_KVM_PV_EOI_EN, pa);
	पूर्ण

	अगर (has_steal_घड़ी)
		kvm_रेजिस्टर_steal_समय();
पूर्ण

अटल व्योम kvm_pv_disable_apf(व्योम)
अणु
	अगर (!__this_cpu_पढ़ो(apf_reason.enabled))
		वापस;

	wrmsrl(MSR_KVM_ASYNC_PF_EN, 0);
	__this_cpu_ग_लिखो(apf_reason.enabled, 0);

	pr_info("disable async PF for cpu %d\n", smp_processor_id());
पूर्ण

अटल व्योम kvm_disable_steal_समय(व्योम)
अणु
	अगर (!has_steal_घड़ी)
		वापस;

	wrmsr(MSR_KVM_STEAL_TIME, 0, 0);
पूर्ण

अटल u64 kvm_steal_घड़ी(पूर्णांक cpu)
अणु
	u64 steal;
	काष्ठा kvm_steal_समय *src;
	पूर्णांक version;

	src = &per_cpu(steal_समय, cpu);
	करो अणु
		version = src->version;
		virt_rmb();
		steal = src->steal;
		virt_rmb();
	पूर्ण जबतक ((version & 1) || (version != src->version));

	वापस steal;
पूर्ण

अटल अंतरभूत व्योम __set_percpu_decrypted(व्योम *ptr, अचिन्हित दीर्घ size)
अणु
	early_set_memory_decrypted((अचिन्हित दीर्घ) ptr, size);
पूर्ण

/*
 * Iterate through all possible CPUs and map the memory region poपूर्णांकed
 * by apf_reason, steal_समय and kvm_apic_eoi as decrypted at once.
 *
 * Note: we iterate through all possible CPUs to ensure that CPUs
 * hotplugged will have their per-cpu variable alपढ़ोy mapped as
 * decrypted.
 */
अटल व्योम __init sev_map_percpu_data(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!sev_active())
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		__set_percpu_decrypted(&per_cpu(apf_reason, cpu), माप(apf_reason));
		__set_percpu_decrypted(&per_cpu(steal_समय, cpu), माप(steal_समय));
		__set_percpu_decrypted(&per_cpu(kvm_apic_eoi, cpu), माप(kvm_apic_eoi));
	पूर्ण
पूर्ण

अटल व्योम kvm_guest_cpu_offline(bool shutकरोwn)
अणु
	kvm_disable_steal_समय();
	अगर (kvm_para_has_feature(KVM_FEATURE_PV_EOI))
		wrmsrl(MSR_KVM_PV_EOI_EN, 0);
	kvm_pv_disable_apf();
	अगर (!shutकरोwn)
		apf_task_wake_all();
	kvmघड़ी_disable();
पूर्ण

अटल पूर्णांक kvm_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	kvm_guest_cpu_init();
	local_irq_restore(flags);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल DEFINE_PER_CPU(cpumask_var_t, __pv_cpu_mask);

अटल bool pv_tlb_flush_supported(व्योम)
अणु
	वापस (kvm_para_has_feature(KVM_FEATURE_PV_TLB_FLUSH) &&
		!kvm_para_has_hपूर्णांक(KVM_HINTS_REALTIME) &&
		kvm_para_has_feature(KVM_FEATURE_STEAL_TIME));
पूर्ण

अटल bool pv_ipi_supported(व्योम)
अणु
	वापस kvm_para_has_feature(KVM_FEATURE_PV_SEND_IPI);
पूर्ण

अटल bool pv_sched_yield_supported(व्योम)
अणु
	वापस (kvm_para_has_feature(KVM_FEATURE_PV_SCHED_YIELD) &&
		!kvm_para_has_hपूर्णांक(KVM_HINTS_REALTIME) &&
	    kvm_para_has_feature(KVM_FEATURE_STEAL_TIME));
पूर्ण

#घोषणा KVM_IPI_CLUSTER_SIZE	(2 * BITS_PER_LONG)

अटल व्योम __send_ipi_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu, apic_id, icr;
	पूर्णांक min = 0, max = 0;
#अगर_घोषित CONFIG_X86_64
	__uपूर्णांक128_t ipi_biपंचांगap = 0;
#अन्यथा
	u64 ipi_biपंचांगap = 0;
#पूर्ण_अगर
	दीर्घ ret;

	अगर (cpumask_empty(mask))
		वापस;

	local_irq_save(flags);

	चयन (vector) अणु
	शेष:
		icr = APIC_DM_FIXED | vector;
		अवरोध;
	हाल NMI_VECTOR:
		icr = APIC_DM_NMI;
		अवरोध;
	पूर्ण

	क्रम_each_cpu(cpu, mask) अणु
		apic_id = per_cpu(x86_cpu_to_apicid, cpu);
		अगर (!ipi_biपंचांगap) अणु
			min = max = apic_id;
		पूर्ण अन्यथा अगर (apic_id < min && max - apic_id < KVM_IPI_CLUSTER_SIZE) अणु
			ipi_biपंचांगap <<= min - apic_id;
			min = apic_id;
		पूर्ण अन्यथा अगर (apic_id < min + KVM_IPI_CLUSTER_SIZE) अणु
			max = apic_id < max ? max : apic_id;
		पूर्ण अन्यथा अणु
			ret = kvm_hypercall4(KVM_HC_SEND_IPI, (अचिन्हित दीर्घ)ipi_biपंचांगap,
				(अचिन्हित दीर्घ)(ipi_biपंचांगap >> BITS_PER_LONG), min, icr);
			WARN_ONCE(ret < 0, "kvm-guest: failed to send PV IPI: %ld",
				  ret);
			min = max = apic_id;
			ipi_biपंचांगap = 0;
		पूर्ण
		__set_bit(apic_id - min, (अचिन्हित दीर्घ *)&ipi_biपंचांगap);
	पूर्ण

	अगर (ipi_biपंचांगap) अणु
		ret = kvm_hypercall4(KVM_HC_SEND_IPI, (अचिन्हित दीर्घ)ipi_biपंचांगap,
			(अचिन्हित दीर्घ)(ipi_biपंचांगap >> BITS_PER_LONG), min, icr);
		WARN_ONCE(ret < 0, "kvm-guest: failed to send PV IPI: %ld",
			  ret);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम kvm_send_ipi_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	__send_ipi_mask(mask, vector);
पूर्ण

अटल व्योम kvm_send_ipi_mask_allbutself(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	काष्ठा cpumask *new_mask = this_cpu_cpumask_var_ptr(__pv_cpu_mask);
	स्थिर काष्ठा cpumask *local_mask;

	cpumask_copy(new_mask, mask);
	cpumask_clear_cpu(this_cpu, new_mask);
	local_mask = new_mask;
	__send_ipi_mask(local_mask, vector);
पूर्ण

/*
 * Set the IPI entry poपूर्णांकs
 */
अटल व्योम kvm_setup_pv_ipi(व्योम)
अणु
	apic->send_IPI_mask = kvm_send_ipi_mask;
	apic->send_IPI_mask_allbutself = kvm_send_ipi_mask_allbutself;
	pr_info("setup PV IPIs\n");
पूर्ण

अटल व्योम kvm_smp_send_call_func_ipi(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	native_send_call_func_ipi(mask);

	/* Make sure other vCPUs get a chance to run अगर they need to. */
	क्रम_each_cpu(cpu, mask) अणु
		अगर (vcpu_is_preempted(cpu)) अणु
			kvm_hypercall1(KVM_HC_SCHED_YIELD, per_cpu(x86_cpu_to_apicid, cpu));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kvm_flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
			स्थिर काष्ठा flush_tlb_info *info)
अणु
	u8 state;
	पूर्णांक cpu;
	काष्ठा kvm_steal_समय *src;
	काष्ठा cpumask *flushmask = this_cpu_cpumask_var_ptr(__pv_cpu_mask);

	cpumask_copy(flushmask, cpumask);
	/*
	 * We have to call flush only on online vCPUs. And
	 * queue flush_on_enter क्रम pre-empted vCPUs
	 */
	क्रम_each_cpu(cpu, flushmask) अणु
		/*
		 * The local vCPU is never preempted, so we करो not explicitly
		 * skip check क्रम local vCPU - it will never be cleared from
		 * flushmask.
		 */
		src = &per_cpu(steal_समय, cpu);
		state = READ_ONCE(src->preempted);
		अगर ((state & KVM_VCPU_PREEMPTED)) अणु
			अगर (try_cmpxchg(&src->preempted, &state,
					state | KVM_VCPU_FLUSH_TLB))
				__cpumask_clear_cpu(cpu, flushmask);
		पूर्ण
	पूर्ण

	native_flush_tlb_multi(flushmask, info);
पूर्ण

अटल __init पूर्णांक kvm_alloc_cpumask(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!kvm_para_available() || nopv)
		वापस 0;

	अगर (pv_tlb_flush_supported() || pv_ipi_supported())
		क्रम_each_possible_cpu(cpu) अणु
			zalloc_cpumask_var_node(per_cpu_ptr(&__pv_cpu_mask, cpu),
				GFP_KERNEL, cpu_to_node(cpu));
		पूर्ण

	वापस 0;
पूर्ण
arch_initcall(kvm_alloc_cpumask);

अटल व्योम __init kvm_smp_prepare_boot_cpu(व्योम)
अणु
	/*
	 * Map the per-cpu variables as decrypted beक्रमe kvm_guest_cpu_init()
	 * shares the guest physical address with the hypervisor.
	 */
	sev_map_percpu_data();

	kvm_guest_cpu_init();
	native_smp_prepare_boot_cpu();
	kvm_spinlock_init();
पूर्ण

अटल पूर्णांक kvm_cpu_करोwn_prepare(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	kvm_guest_cpu_offline(false);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक kvm_suspend(व्योम)
अणु
	kvm_guest_cpu_offline(false);

	वापस 0;
पूर्ण

अटल व्योम kvm_resume(व्योम)
अणु
	kvm_cpu_online(raw_smp_processor_id());
पूर्ण

अटल काष्ठा syscore_ops kvm_syscore_ops = अणु
	.suspend	= kvm_suspend,
	.resume		= kvm_resume,
पूर्ण;

अटल व्योम kvm_pv_guest_cpu_reboot(व्योम *unused)
अणु
	kvm_guest_cpu_offline(true);
पूर्ण

अटल पूर्णांक kvm_pv_reboot_notअगरy(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_RESTART)
		on_each_cpu(kvm_pv_guest_cpu_reboot, शून्य, 1);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block kvm_pv_reboot_nb = अणु
	.notअगरier_call = kvm_pv_reboot_notअगरy,
पूर्ण;

/*
 * After a PV feature is रेजिस्टरed, the host will keep writing to the
 * रेजिस्टरed memory location. If the guest happens to shutकरोwn, this memory
 * won't be valid. In हालs like kexec, in which you install a new kernel, this
 * means a अक्रमom memory location will be kept being written.
 */
#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम kvm_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	kvm_guest_cpu_offline(true);
	native_machine_crash_shutकरोwn(regs);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init kvm_guest_init(व्योम)
अणु
	पूर्णांक i;

	paravirt_ops_setup();
	रेजिस्टर_reboot_notअगरier(&kvm_pv_reboot_nb);
	क्रम (i = 0; i < KVM_TASK_SLEEP_HASHSIZE; i++)
		raw_spin_lock_init(&async_pf_sleepers[i].lock);

	अगर (kvm_para_has_feature(KVM_FEATURE_STEAL_TIME)) अणु
		has_steal_घड़ी = 1;
		अटल_call_update(pv_steal_घड़ी, kvm_steal_घड़ी);
	पूर्ण

	अगर (kvm_para_has_feature(KVM_FEATURE_PV_EOI))
		apic_set_eoi_ग_लिखो(kvm_guest_apic_eoi_ग_लिखो);

	अगर (kvm_para_has_feature(KVM_FEATURE_ASYNC_PF_INT) && kvmapf) अणु
		अटल_branch_enable(&kvm_async_pf_enabled);
		alloc_पूर्णांकr_gate(HYPERVISOR_CALLBACK_VECTOR, यंत्र_sysvec_kvm_asyncpf_पूर्णांकerrupt);
	पूर्ण

#अगर_घोषित CONFIG_SMP
	अगर (pv_tlb_flush_supported()) अणु
		pv_ops.mmu.flush_tlb_multi = kvm_flush_tlb_multi;
		pv_ops.mmu.tlb_हटाओ_table = tlb_हटाओ_table;
		pr_info("KVM setup pv remote TLB flush\n");
	पूर्ण

	smp_ops.smp_prepare_boot_cpu = kvm_smp_prepare_boot_cpu;
	अगर (pv_sched_yield_supported()) अणु
		smp_ops.send_call_func_ipi = kvm_smp_send_call_func_ipi;
		pr_info("setup PV sched yield\n");
	पूर्ण
	अगर (cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "x86/kvm:online",
				      kvm_cpu_online, kvm_cpu_करोwn_prepare) < 0)
		pr_err("failed to install cpu hotplug callbacks\n");
#अन्यथा
	sev_map_percpu_data();
	kvm_guest_cpu_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_CORE
	machine_ops.crash_shutकरोwn = kvm_crash_shutकरोwn;
#पूर्ण_अगर

	रेजिस्टर_syscore_ops(&kvm_syscore_ops);

	/*
	 * Hard lockup detection is enabled by शेष. Disable it, as guests
	 * can get false positives too easily, क्रम example अगर the host is
	 * overcommitted.
	 */
	hardlockup_detector_disable();
पूर्ण

अटल noअंतरभूत uपूर्णांक32_t __kvm_cpuid_base(व्योम)
अणु
	अगर (boot_cpu_data.cpuid_level < 0)
		वापस 0;	/* So we करोn't blow up on old processors */

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस hypervisor_cpuid_base("KVMKVMKVM\0\0\0", 0);

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t kvm_cpuid_base(व्योम)
अणु
	अटल पूर्णांक kvm_cpuid_base = -1;

	अगर (kvm_cpuid_base == -1)
		kvm_cpuid_base = __kvm_cpuid_base();

	वापस kvm_cpuid_base;
पूर्ण

bool kvm_para_available(व्योम)
अणु
	वापस kvm_cpuid_base() != 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_para_available);

अचिन्हित पूर्णांक kvm_arch_para_features(व्योम)
अणु
	वापस cpuid_eax(kvm_cpuid_base() | KVM_CPUID_FEATURES);
पूर्ण

अचिन्हित पूर्णांक kvm_arch_para_hपूर्णांकs(व्योम)
अणु
	वापस cpuid_edx(kvm_cpuid_base() | KVM_CPUID_FEATURES);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_para_hपूर्णांकs);

अटल uपूर्णांक32_t __init kvm_detect(व्योम)
अणु
	वापस kvm_cpuid_base();
पूर्ण

अटल व्योम __init kvm_apic_init(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (pv_ipi_supported())
		kvm_setup_pv_ipi();
#पूर्ण_अगर
पूर्ण

अटल bool __init kvm_msi_ext_dest_id(व्योम)
अणु
	वापस kvm_para_has_feature(KVM_FEATURE_MSI_EXT_DEST_ID);
पूर्ण

अटल व्योम __init kvm_init_platक्रमm(व्योम)
अणु
	kvmघड़ी_init();
	x86_platक्रमm.apic_post_init = kvm_apic_init;
पूर्ण

#अगर defined(CONFIG_AMD_MEM_ENCRYPT)
अटल व्योम kvm_sev_es_hcall_prepare(काष्ठा ghcb *ghcb, काष्ठा pt_regs *regs)
अणु
	/* RAX and CPL are alपढ़ोy in the GHCB */
	ghcb_set_rbx(ghcb, regs->bx);
	ghcb_set_rcx(ghcb, regs->cx);
	ghcb_set_rdx(ghcb, regs->dx);
	ghcb_set_rsi(ghcb, regs->si);
पूर्ण

अटल bool kvm_sev_es_hcall_finish(काष्ठा ghcb *ghcb, काष्ठा pt_regs *regs)
अणु
	/* No checking of the वापस state needed */
	वापस true;
पूर्ण
#पूर्ण_अगर

स्थिर __initस्थिर काष्ठा hypervisor_x86 x86_hyper_kvm = अणु
	.name				= "KVM",
	.detect				= kvm_detect,
	.type				= X86_HYPER_KVM,
	.init.guest_late_init		= kvm_guest_init,
	.init.x2apic_available		= kvm_para_available,
	.init.msi_ext_dest_id		= kvm_msi_ext_dest_id,
	.init.init_platक्रमm		= kvm_init_platक्रमm,
#अगर defined(CONFIG_AMD_MEM_ENCRYPT)
	.runसमय.sev_es_hcall_prepare	= kvm_sev_es_hcall_prepare,
	.runसमय.sev_es_hcall_finish	= kvm_sev_es_hcall_finish,
#पूर्ण_अगर
पूर्ण;

अटल __init पूर्णांक activate_jump_labels(व्योम)
अणु
	अगर (has_steal_घड़ी) अणु
		अटल_key_slow_inc(&paravirt_steal_enabled);
		अगर (steal_acc)
			अटल_key_slow_inc(&paravirt_steal_rq_enabled);
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(activate_jump_labels);

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS

/* Kick a cpu by its apicid. Used to wake up a halted vcpu */
अटल व्योम kvm_kick_cpu(पूर्णांक cpu)
अणु
	पूर्णांक apicid;
	अचिन्हित दीर्घ flags = 0;

	apicid = per_cpu(x86_cpu_to_apicid, cpu);
	kvm_hypercall2(KVM_HC_KICK_CPU, flags, apicid);
पूर्ण

#समावेश <यंत्र/qspinlock.h>

अटल व्योम kvm_रुको(u8 *ptr, u8 val)
अणु
	अगर (in_nmi())
		वापस;

	/*
	 * halt until it's our turn and kicked. Note that we करो safe halt
	 * क्रम irq enabled हाल to aव्योम hang when lock info is overwritten
	 * in irq spinlock slowpath and no spurious पूर्णांकerrupt occur to save us.
	 */
	अगर (irqs_disabled()) अणु
		अगर (READ_ONCE(*ptr) == val)
			halt();
	पूर्ण अन्यथा अणु
		local_irq_disable();

		अगर (READ_ONCE(*ptr) == val)
			safe_halt();

		local_irq_enable();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_32
__visible bool __kvm_vcpu_is_preempted(दीर्घ cpu)
अणु
	काष्ठा kvm_steal_समय *src = &per_cpu(steal_समय, cpu);

	वापस !!(src->preempted & KVM_VCPU_PREEMPTED);
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(__kvm_vcpu_is_preempted);

#अन्यथा

#समावेश <यंत्र/यंत्र-offsets.h>

बाह्य bool __raw_callee_save___kvm_vcpu_is_preempted(दीर्घ);

/*
 * Hand-optimize version क्रम x86-64 to aव्योम 8 64-bit रेजिस्टर saving and
 * restoring to/from the stack.
 */
यंत्र(
".pushsection .text;"
".global __raw_callee_save___kvm_vcpu_is_preempted;"
".type __raw_callee_save___kvm_vcpu_is_preempted, @function;"
"__raw_callee_save___kvm_vcpu_is_preempted:"
"movq	__per_cpu_offset(,%rdi,8), %rax;"
"cmpb	$0, " __stringअगरy(KVM_STEAL_TIME_preempted) "+steal_time(%rax);"
"setne	%al;"
"ret;"
".size __raw_callee_save___kvm_vcpu_is_preempted, .-__raw_callee_save___kvm_vcpu_is_preempted;"
".popsection");

#पूर्ण_अगर

/*
 * Setup pv_lock_ops to exploit KVM_FEATURE_PV_UNHALT अगर present.
 */
व्योम __init kvm_spinlock_init(व्योम)
अणु
	/*
	 * In हाल host करोesn't support KVM_FEATURE_PV_UNHALT there is still an
	 * advantage of keeping virt_spin_lock_key enabled: virt_spin_lock() is
	 * preferred over native qspinlock when vCPU is preempted.
	 */
	अगर (!kvm_para_has_feature(KVM_FEATURE_PV_UNHALT)) अणु
		pr_info("PV spinlocks disabled, no host support\n");
		वापस;
	पूर्ण

	/*
	 * Disable PV spinlocks and use native qspinlock when dedicated pCPUs
	 * are available.
	 */
	अगर (kvm_para_has_hपूर्णांक(KVM_HINTS_REALTIME)) अणु
		pr_info("PV spinlocks disabled with KVM_HINTS_REALTIME hints\n");
		जाओ out;
	पूर्ण

	अगर (num_possible_cpus() == 1) अणु
		pr_info("PV spinlocks disabled, single CPU\n");
		जाओ out;
	पूर्ण

	अगर (nopvspin) अणु
		pr_info("PV spinlocks disabled, forced by \"nopvspin\" parameter\n");
		जाओ out;
	पूर्ण

	pr_info("PV spinlocks enabled\n");

	__pv_init_lock_hash();
	pv_ops.lock.queued_spin_lock_slowpath = __pv_queued_spin_lock_slowpath;
	pv_ops.lock.queued_spin_unlock =
		PV_CALLEE_SAVE(__pv_queued_spin_unlock);
	pv_ops.lock.रुको = kvm_रुको;
	pv_ops.lock.kick = kvm_kick_cpu;

	अगर (kvm_para_has_feature(KVM_FEATURE_STEAL_TIME)) अणु
		pv_ops.lock.vcpu_is_preempted =
			PV_CALLEE_SAVE(__kvm_vcpu_is_preempted);
	पूर्ण
	/*
	 * When PV spinlock is enabled which is preferred over
	 * virt_spin_lock(), virt_spin_lock_key's value is meaningless.
	 * Just disable it anyway.
	 */
out:
	अटल_branch_disable(&virt_spin_lock_key);
पूर्ण

#पूर्ण_अगर	/* CONFIG_PARAVIRT_SPINLOCKS */

#अगर_घोषित CONFIG_ARCH_CPUIDLE_HALTPOLL

अटल व्योम kvm_disable_host_haltpoll(व्योम *i)
अणु
	wrmsrl(MSR_KVM_POLL_CONTROL, 0);
पूर्ण

अटल व्योम kvm_enable_host_haltpoll(व्योम *i)
अणु
	wrmsrl(MSR_KVM_POLL_CONTROL, 1);
पूर्ण

व्योम arch_haltpoll_enable(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL)) अणु
		pr_err_once("host does not support poll control\n");
		pr_err_once("host upgrade recommended\n");
		वापस;
	पूर्ण

	/* Enable guest halt poll disables host halt poll */
	smp_call_function_single(cpu, kvm_disable_host_haltpoll, शून्य, 1);
पूर्ण
EXPORT_SYMBOL_GPL(arch_haltpoll_enable);

व्योम arch_haltpoll_disable(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL))
		वापस;

	/* Disable guest halt poll enables host halt poll */
	smp_call_function_single(cpu, kvm_enable_host_haltpoll, शून्य, 1);
पूर्ण
EXPORT_SYMBOL_GPL(arch_haltpoll_disable);
#पूर्ण_अगर
