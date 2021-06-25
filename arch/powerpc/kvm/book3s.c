<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009. SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *    Alexander Graf <agraf@suse.de>
 *    Kevin Wolf <mail@kevin-wolf.de>
 *
 * Description:
 * This file is derived from arch/घातerpc/kvm/44x.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xive.h>

#समावेश "book3s.h"
#समावेश "trace.h"

/* #घोषणा EXIT_DEBUG */

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("exits", sum_निकासs),
	VCPU_STAT("mmio", mmio_निकासs),
	VCPU_STAT("sig", संकेत_निकासs),
	VCPU_STAT("sysc", syscall_निकासs),
	VCPU_STAT("inst_emu", emulated_inst_निकासs),
	VCPU_STAT("dec", dec_निकासs),
	VCPU_STAT("ext_intr", ext_पूर्णांकr_निकासs),
	VCPU_STAT("queue_intr", queue_पूर्णांकr),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	VCPU_STAT("halt_wait_ns", halt_रुको_ns),
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_successful_wait", halt_successful_रुको),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("pf_storage", pf_storage),
	VCPU_STAT("sp_storage", sp_storage),
	VCPU_STAT("pf_instruc", pf_instruc),
	VCPU_STAT("sp_instruc", sp_instruc),
	VCPU_STAT("ld", ld),
	VCPU_STAT("ld_slow", ld_slow),
	VCPU_STAT("st", st),
	VCPU_STAT("st_slow", st_slow),
	VCPU_STAT("pthru_all", pthru_all),
	VCPU_STAT("pthru_host", pthru_host),
	VCPU_STAT("pthru_bad_aff", pthru_bad_aff),
	VM_STAT("largepages_2M", num_2M_pages, .mode = 0444),
	VM_STAT("largepages_1G", num_1G_pages, .mode = 0444),
	अणु शून्य पूर्ण
पूर्ण;

अटल अंतरभूत व्योम kvmppc_update_पूर्णांक_pending(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित दीर्घ pending_now, अचिन्हित दीर्घ old_pending)
अणु
	अगर (is_kvmppc_hv_enabled(vcpu->kvm))
		वापस;
	अगर (pending_now)
		kvmppc_set_पूर्णांक_pending(vcpu, 1);
	अन्यथा अगर (old_pending)
		kvmppc_set_पूर्णांक_pending(vcpu, 0);
पूर्ण

अटल अंतरभूत bool kvmppc_critical_section(काष्ठा kvm_vcpu *vcpu)
अणु
	uदीर्घ crit_raw;
	uदीर्घ crit_r1;
	bool crit;

	अगर (is_kvmppc_hv_enabled(vcpu->kvm))
		वापस false;

	crit_raw = kvmppc_get_critical(vcpu);
	crit_r1 = kvmppc_get_gpr(vcpu, 1);

	/* Truncate crit indicators in 32 bit mode */
	अगर (!(kvmppc_get_msr(vcpu) & MSR_SF)) अणु
		crit_raw &= 0xffffffff;
		crit_r1 &= 0xffffffff;
	पूर्ण

	/* Critical section when crit == r1 */
	crit = (crit_raw == crit_r1);
	/* ... and we're in supervisor mode */
	crit = crit && !(kvmppc_get_msr(vcpu) & MSR_PR);

	वापस crit;
पूर्ण

व्योम kvmppc_inject_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 flags)
अणु
	vcpu->kvm->arch.kvm_ops->inject_पूर्णांकerrupt(vcpu, vec, flags);
पूर्ण

अटल पूर्णांक kvmppc_book3s_vec2irqprio(अचिन्हित पूर्णांक vec)
अणु
	अचिन्हित पूर्णांक prio;

	चयन (vec) अणु
	हाल 0x100: prio = BOOK3S_IRQPRIO_SYSTEM_RESET;		अवरोध;
	हाल 0x200: prio = BOOK3S_IRQPRIO_MACHINE_CHECK;	अवरोध;
	हाल 0x300: prio = BOOK3S_IRQPRIO_DATA_STORAGE;		अवरोध;
	हाल 0x380: prio = BOOK3S_IRQPRIO_DATA_SEGMENT;		अवरोध;
	हाल 0x400: prio = BOOK3S_IRQPRIO_INST_STORAGE;		अवरोध;
	हाल 0x480: prio = BOOK3S_IRQPRIO_INST_SEGMENT;		अवरोध;
	हाल 0x500: prio = BOOK3S_IRQPRIO_EXTERNAL;		अवरोध;
	हाल 0x600: prio = BOOK3S_IRQPRIO_ALIGNMENT;		अवरोध;
	हाल 0x700: prio = BOOK3S_IRQPRIO_PROGRAM;		अवरोध;
	हाल 0x800: prio = BOOK3S_IRQPRIO_FP_UNAVAIL;		अवरोध;
	हाल 0x900: prio = BOOK3S_IRQPRIO_DECREMENTER;		अवरोध;
	हाल 0xc00: prio = BOOK3S_IRQPRIO_SYSCALL;		अवरोध;
	हाल 0xd00: prio = BOOK3S_IRQPRIO_DEBUG;		अवरोध;
	हाल 0xf20: prio = BOOK3S_IRQPRIO_ALTIVEC;		अवरोध;
	हाल 0xf40: prio = BOOK3S_IRQPRIO_VSX;			अवरोध;
	हाल 0xf60: prio = BOOK3S_IRQPRIO_FAC_UNAVAIL;		अवरोध;
	शेष:    prio = BOOK3S_IRQPRIO_MAX;			अवरोध;
	पूर्ण

	वापस prio;
पूर्ण

व्योम kvmppc_book3s_dequeue_irqprio(काष्ठा kvm_vcpu *vcpu,
					  अचिन्हित पूर्णांक vec)
अणु
	अचिन्हित दीर्घ old_pending = vcpu->arch.pending_exceptions;

	clear_bit(kvmppc_book3s_vec2irqprio(vec),
		  &vcpu->arch.pending_exceptions);

	kvmppc_update_पूर्णांक_pending(vcpu, vcpu->arch.pending_exceptions,
				  old_pending);
पूर्ण

व्योम kvmppc_book3s_queue_irqprio(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vec)
अणु
	vcpu->stat.queue_पूर्णांकr++;

	set_bit(kvmppc_book3s_vec2irqprio(vec),
		&vcpu->arch.pending_exceptions);
#अगर_घोषित EXIT_DEBUG
	prपूर्णांकk(KERN_INFO "Queueing interrupt %x\n", vec);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_book3s_queue_irqprio);

व्योम kvmppc_core_queue_machine_check(काष्ठा kvm_vcpu *vcpu, uदीर्घ flags)
अणु
	/* might as well deliver this straight away */
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_MACHINE_CHECK, flags);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_queue_machine_check);

व्योम kvmppc_core_queue_program(काष्ठा kvm_vcpu *vcpu, uदीर्घ flags)
अणु
	/* might as well deliver this straight away */
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_PROGRAM, flags);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_queue_program);

व्योम kvmppc_core_queue_fpunavail(काष्ठा kvm_vcpu *vcpu)
अणु
	/* might as well deliver this straight away */
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL, 0);
पूर्ण

व्योम kvmppc_core_queue_vec_unavail(काष्ठा kvm_vcpu *vcpu)
अणु
	/* might as well deliver this straight away */
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_ALTIVEC, 0);
पूर्ण

व्योम kvmppc_core_queue_vsx_unavail(काष्ठा kvm_vcpu *vcpu)
अणु
	/* might as well deliver this straight away */
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_VSX, 0);
पूर्ण

व्योम kvmppc_core_queue_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_DECREMENTER);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_queue_dec);

पूर्णांक kvmppc_core_pending_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस test_bit(BOOK3S_IRQPRIO_DECREMENTER, &vcpu->arch.pending_exceptions);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_pending_dec);

व्योम kvmppc_core_dequeue_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_book3s_dequeue_irqprio(vcpu, BOOK3S_INTERRUPT_DECREMENTER);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_dequeue_dec);

व्योम kvmppc_core_queue_बाह्यal(काष्ठा kvm_vcpu *vcpu,
                                काष्ठा kvm_पूर्णांकerrupt *irq)
अणु
	/*
	 * This हाल (KVM_INTERRUPT_SET) should never actually arise क्रम
	 * a pseries guest (because pseries guests expect their पूर्णांकerrupt
	 * controllers to जारी निश्चितing an बाह्यal पूर्णांकerrupt request
	 * until it is acknowledged at the पूर्णांकerrupt controller), but is
	 * included to aव्योम ABI अवरोधage and potentially क्रम other
	 * sorts of guest.
	 *
	 * There is a subtlety here: HV KVM करोes not test the
	 * बाह्यal_oneshot flag in the code that synthesizes
	 * बाह्यal पूर्णांकerrupts क्रम the guest just beक्रमe entering
	 * the guest.  That is OK even अगर userspace did करो a
	 * KVM_INTERRUPT_SET on a pseries guest vcpu, because the
	 * caller (kvm_vcpu_ioctl_पूर्णांकerrupt) करोes a kvm_vcpu_kick()
	 * which ends up करोing a smp_send_reschedule(), which will
	 * pull the guest all the way out to the host, meaning that
	 * we will call kvmppc_core_prepare_to_enter() beक्रमe entering
	 * the guest again, and that will handle the बाह्यal_oneshot
	 * flag correctly.
	 */
	अगर (irq->irq == KVM_INTERRUPT_SET)
		vcpu->arch.बाह्यal_oneshot = 1;

	kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_EXTERNAL);
पूर्ण

व्योम kvmppc_core_dequeue_बाह्यal(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_book3s_dequeue_irqprio(vcpu, BOOK3S_INTERRUPT_EXTERNAL);
पूर्ण

व्योम kvmppc_core_queue_data_storage(काष्ठा kvm_vcpu *vcpu, uदीर्घ dar,
				    uदीर्घ flags)
अणु
	kvmppc_set_dar(vcpu, dar);
	kvmppc_set_dsisr(vcpu, flags);
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_DATA_STORAGE, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_queue_data_storage);

व्योम kvmppc_core_queue_inst_storage(काष्ठा kvm_vcpu *vcpu, uदीर्घ flags)
अणु
	kvmppc_inject_पूर्णांकerrupt(vcpu, BOOK3S_INTERRUPT_INST_STORAGE, flags);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_queue_inst_storage);

अटल पूर्णांक kvmppc_book3s_irqprio_deliver(काष्ठा kvm_vcpu *vcpu,
					 अचिन्हित पूर्णांक priority)
अणु
	पूर्णांक deliver = 1;
	पूर्णांक vec = 0;
	bool crit = kvmppc_critical_section(vcpu);

	चयन (priority) अणु
	हाल BOOK3S_IRQPRIO_DECREMENTER:
		deliver = (kvmppc_get_msr(vcpu) & MSR_EE) && !crit;
		vec = BOOK3S_INTERRUPT_DECREMENTER;
		अवरोध;
	हाल BOOK3S_IRQPRIO_EXTERNAL:
		deliver = (kvmppc_get_msr(vcpu) & MSR_EE) && !crit;
		vec = BOOK3S_INTERRUPT_EXTERNAL;
		अवरोध;
	हाल BOOK3S_IRQPRIO_SYSTEM_RESET:
		vec = BOOK3S_INTERRUPT_SYSTEM_RESET;
		अवरोध;
	हाल BOOK3S_IRQPRIO_MACHINE_CHECK:
		vec = BOOK3S_INTERRUPT_MACHINE_CHECK;
		अवरोध;
	हाल BOOK3S_IRQPRIO_DATA_STORAGE:
		vec = BOOK3S_INTERRUPT_DATA_STORAGE;
		अवरोध;
	हाल BOOK3S_IRQPRIO_INST_STORAGE:
		vec = BOOK3S_INTERRUPT_INST_STORAGE;
		अवरोध;
	हाल BOOK3S_IRQPRIO_DATA_SEGMENT:
		vec = BOOK3S_INTERRUPT_DATA_SEGMENT;
		अवरोध;
	हाल BOOK3S_IRQPRIO_INST_SEGMENT:
		vec = BOOK3S_INTERRUPT_INST_SEGMENT;
		अवरोध;
	हाल BOOK3S_IRQPRIO_ALIGNMENT:
		vec = BOOK3S_INTERRUPT_ALIGNMENT;
		अवरोध;
	हाल BOOK3S_IRQPRIO_PROGRAM:
		vec = BOOK3S_INTERRUPT_PROGRAM;
		अवरोध;
	हाल BOOK3S_IRQPRIO_VSX:
		vec = BOOK3S_INTERRUPT_VSX;
		अवरोध;
	हाल BOOK3S_IRQPRIO_ALTIVEC:
		vec = BOOK3S_INTERRUPT_ALTIVEC;
		अवरोध;
	हाल BOOK3S_IRQPRIO_FP_UNAVAIL:
		vec = BOOK3S_INTERRUPT_FP_UNAVAIL;
		अवरोध;
	हाल BOOK3S_IRQPRIO_SYSCALL:
		vec = BOOK3S_INTERRUPT_SYSCALL;
		अवरोध;
	हाल BOOK3S_IRQPRIO_DEBUG:
		vec = BOOK3S_INTERRUPT_TRACE;
		अवरोध;
	हाल BOOK3S_IRQPRIO_PERFORMANCE_MONITOR:
		vec = BOOK3S_INTERRUPT_PERFMON;
		अवरोध;
	हाल BOOK3S_IRQPRIO_FAC_UNAVAIL:
		vec = BOOK3S_INTERRUPT_FAC_UNAVAIL;
		अवरोध;
	शेष:
		deliver = 0;
		prपूर्णांकk(KERN_ERR "KVM: Unknown interrupt: 0x%x\n", priority);
		अवरोध;
	पूर्ण

#अगर 0
	prपूर्णांकk(KERN_INFO "Deliver interrupt 0x%x? %x\n", vec, deliver);
#पूर्ण_अगर

	अगर (deliver)
		kvmppc_inject_पूर्णांकerrupt(vcpu, vec, 0);

	वापस deliver;
पूर्ण

/*
 * This function determines अगर an irqprio should be cleared once issued.
 */
अटल bool clear_irqprio(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority)
अणु
	चयन (priority) अणु
		हाल BOOK3S_IRQPRIO_DECREMENTER:
			/* DEC पूर्णांकerrupts get cleared by mtdec */
			वापस false;
		हाल BOOK3S_IRQPRIO_EXTERNAL:
			/*
			 * External पूर्णांकerrupts get cleared by userspace
			 * except when set by the KVM_INTERRUPT ioctl with
			 * KVM_INTERRUPT_SET (not KVM_INTERRUPT_SET_LEVEL).
			 */
			अगर (vcpu->arch.बाह्यal_oneshot) अणु
				vcpu->arch.बाह्यal_oneshot = 0;
				वापस true;
			पूर्ण
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक kvmppc_core_prepare_to_enter(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ *pending = &vcpu->arch.pending_exceptions;
	अचिन्हित दीर्घ old_pending = vcpu->arch.pending_exceptions;
	अचिन्हित पूर्णांक priority;

#अगर_घोषित EXIT_DEBUG
	अगर (vcpu->arch.pending_exceptions)
		prपूर्णांकk(KERN_EMERG "KVM: Check pending: %lx\n", vcpu->arch.pending_exceptions);
#पूर्ण_अगर
	priority = __ffs(*pending);
	जबतक (priority < BOOK3S_IRQPRIO_MAX) अणु
		अगर (kvmppc_book3s_irqprio_deliver(vcpu, priority) &&
		    clear_irqprio(vcpu, priority)) अणु
			clear_bit(priority, &vcpu->arch.pending_exceptions);
			अवरोध;
		पूर्ण

		priority = find_next_bit(pending,
					 BITS_PER_BYTE * माप(*pending),
					 priority + 1);
	पूर्ण

	/* Tell the guest about our पूर्णांकerrupt status */
	kvmppc_update_पूर्णांक_pending(vcpu, *pending, old_pending);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_core_prepare_to_enter);

kvm_pfn_t kvmppc_gpa_to_pfn(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, bool writing,
			bool *writable)
अणु
	uदीर्घ mp_pa = vcpu->arch.magic_page_pa & KVM_PAM;
	gfn_t gfn = gpa >> PAGE_SHIFT;

	अगर (!(kvmppc_get_msr(vcpu) & MSR_SF))
		mp_pa = (uपूर्णांक32_t)mp_pa;

	/* Magic page override */
	gpa &= ~0xFFFULL;
	अगर (unlikely(mp_pa) && unlikely((gpa & KVM_PAM) == mp_pa)) अणु
		uदीर्घ shared_page = ((uदीर्घ)vcpu->arch.shared) & PAGE_MASK;
		kvm_pfn_t pfn;

		pfn = (kvm_pfn_t)virt_to_phys((व्योम*)shared_page) >> PAGE_SHIFT;
		get_page(pfn_to_page(pfn));
		अगर (writable)
			*writable = true;
		वापस pfn;
	पूर्ण

	वापस gfn_to_pfn_prot(vcpu->kvm, gfn, writing, writable);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_gpa_to_pfn);

पूर्णांक kvmppc_xlate(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr, क्रमागत xlate_instdata xlid,
		 क्रमागत xlate_पढ़ोग_लिखो xlrw, काष्ठा kvmppc_pte *pte)
अणु
	bool data = (xlid == XLATE_DATA);
	bool isग_लिखो = (xlrw == XLATE_WRITE);
	पूर्णांक relocated = (kvmppc_get_msr(vcpu) & (data ? MSR_DR : MSR_IR));
	पूर्णांक r;

	अगर (relocated) अणु
		r = vcpu->arch.mmu.xlate(vcpu, eaddr, pte, data, isग_लिखो);
	पूर्ण अन्यथा अणु
		pte->eaddr = eaddr;
		pte->raddr = eaddr & KVM_PAM;
		pte->vpage = VSID_REAL | eaddr >> 12;
		pte->may_पढ़ो = true;
		pte->may_ग_लिखो = true;
		pte->may_execute = true;
		r = 0;

		अगर ((kvmppc_get_msr(vcpu) & (MSR_IR | MSR_DR)) == MSR_DR &&
		    !data) अणु
			अगर ((vcpu->arch.hflags & BOOK3S_HFLAG_SPLIT_HACK) &&
			    ((eaddr & SPLIT_HACK_MASK) == SPLIT_HACK_OFFS))
			pte->raddr &= ~SPLIT_HACK_MASK;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_load_last_inst(काष्ठा kvm_vcpu *vcpu,
		क्रमागत inकाष्ठाion_fetch_type type, u32 *inst)
अणु
	uदीर्घ pc = kvmppc_get_pc(vcpu);
	पूर्णांक r;

	अगर (type == INST_SC)
		pc -= 4;

	r = kvmppc_ld(vcpu, &pc, माप(u32), inst, false);
	अगर (r == EMULATE_DONE)
		वापस r;
	अन्यथा
		वापस EMULATE_AGAIN;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_load_last_inst);

पूर्णांक kvmppc_subarch_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण

व्योम kvmppc_subarch_vcpu_uninit(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret;

	vcpu_load(vcpu);
	ret = vcpu->kvm->arch.kvm_ops->get_sregs(vcpu, sregs);
	vcpu_put(vcpu);

	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret;

	vcpu_load(vcpu);
	ret = vcpu->kvm->arch.kvm_ops->set_sregs(vcpu, sregs);
	vcpu_put(vcpu);

	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	regs->pc = kvmppc_get_pc(vcpu);
	regs->cr = kvmppc_get_cr(vcpu);
	regs->ctr = kvmppc_get_ctr(vcpu);
	regs->lr = kvmppc_get_lr(vcpu);
	regs->xer = kvmppc_get_xer(vcpu);
	regs->msr = kvmppc_get_msr(vcpu);
	regs->srr0 = kvmppc_get_srr0(vcpu);
	regs->srr1 = kvmppc_get_srr1(vcpu);
	regs->pid = vcpu->arch.pid;
	regs->sprg0 = kvmppc_get_sprg0(vcpu);
	regs->sprg1 = kvmppc_get_sprg1(vcpu);
	regs->sprg2 = kvmppc_get_sprg2(vcpu);
	regs->sprg3 = kvmppc_get_sprg3(vcpu);
	regs->sprg4 = kvmppc_get_sprg4(vcpu);
	regs->sprg5 = kvmppc_get_sprg5(vcpu);
	regs->sprg6 = kvmppc_get_sprg6(vcpu);
	regs->sprg7 = kvmppc_get_sprg7(vcpu);

	क्रम (i = 0; i < ARRAY_SIZE(regs->gpr); i++)
		regs->gpr[i] = kvmppc_get_gpr(vcpu, i);

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	kvmppc_set_pc(vcpu, regs->pc);
	kvmppc_set_cr(vcpu, regs->cr);
	kvmppc_set_ctr(vcpu, regs->ctr);
	kvmppc_set_lr(vcpu, regs->lr);
	kvmppc_set_xer(vcpu, regs->xer);
	kvmppc_set_msr(vcpu, regs->msr);
	kvmppc_set_srr0(vcpu, regs->srr0);
	kvmppc_set_srr1(vcpu, regs->srr1);
	kvmppc_set_sprg0(vcpu, regs->sprg0);
	kvmppc_set_sprg1(vcpu, regs->sprg1);
	kvmppc_set_sprg2(vcpu, regs->sprg2);
	kvmppc_set_sprg3(vcpu, regs->sprg3);
	kvmppc_set_sprg4(vcpu, regs->sprg4);
	kvmppc_set_sprg5(vcpu, regs->sprg5);
	kvmppc_set_sprg6(vcpu, regs->sprg6);
	kvmppc_set_sprg7(vcpu, regs->sprg7);

	क्रम (i = 0; i < ARRAY_SIZE(regs->gpr); i++)
		kvmppc_set_gpr(vcpu, i, regs->gpr[i]);

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक kvmppc_get_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id,
			जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;

	r = vcpu->kvm->arch.kvm_ops->get_one_reg(vcpu, id, val);
	अगर (r == -EINVAL) अणु
		r = 0;
		चयन (id) अणु
		हाल KVM_REG_PPC_DAR:
			*val = get_reg_val(id, kvmppc_get_dar(vcpu));
			अवरोध;
		हाल KVM_REG_PPC_DSISR:
			*val = get_reg_val(id, kvmppc_get_dsisr(vcpu));
			अवरोध;
		हाल KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = id - KVM_REG_PPC_FPR0;
			*val = get_reg_val(id, VCPU_FPR(vcpu, i));
			अवरोध;
		हाल KVM_REG_PPC_FPSCR:
			*val = get_reg_val(id, vcpu->arch.fp.fpscr);
			अवरोध;
#अगर_घोषित CONFIG_VSX
		हाल KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31:
			अगर (cpu_has_feature(CPU_FTR_VSX)) अणु
				i = id - KVM_REG_PPC_VSR0;
				val->vsxval[0] = vcpu->arch.fp.fpr[i][0];
				val->vsxval[1] = vcpu->arch.fp.fpr[i][1];
			पूर्ण अन्यथा अणु
				r = -ENXIO;
			पूर्ण
			अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */
		हाल KVM_REG_PPC_DEBUG_INST:
			*val = get_reg_val(id, INS_TW);
			अवरोध;
#अगर_घोषित CONFIG_KVM_XICS
		हाल KVM_REG_PPC_ICP_STATE:
			अगर (!vcpu->arch.icp && !vcpu->arch.xive_vcpu) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			अगर (xics_on_xive())
				*val = get_reg_val(id, kvmppc_xive_get_icp(vcpu));
			अन्यथा
				*val = get_reg_val(id, kvmppc_xics_get_icp(vcpu));
			अवरोध;
#पूर्ण_अगर /* CONFIG_KVM_XICS */
#अगर_घोषित CONFIG_KVM_XIVE
		हाल KVM_REG_PPC_VP_STATE:
			अगर (!vcpu->arch.xive_vcpu) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			अगर (xive_enabled())
				r = kvmppc_xive_native_get_vp(vcpu, val);
			अन्यथा
				r = -ENXIO;
			अवरोध;
#पूर्ण_अगर /* CONFIG_KVM_XIVE */
		हाल KVM_REG_PPC_FSCR:
			*val = get_reg_val(id, vcpu->arch.fscr);
			अवरोध;
		हाल KVM_REG_PPC_TAR:
			*val = get_reg_val(id, vcpu->arch.tar);
			अवरोध;
		हाल KVM_REG_PPC_EBBHR:
			*val = get_reg_val(id, vcpu->arch.ebbhr);
			अवरोध;
		हाल KVM_REG_PPC_EBBRR:
			*val = get_reg_val(id, vcpu->arch.ebbrr);
			अवरोध;
		हाल KVM_REG_PPC_BESCR:
			*val = get_reg_val(id, vcpu->arch.bescr);
			अवरोध;
		हाल KVM_REG_PPC_IC:
			*val = get_reg_val(id, vcpu->arch.ic);
			अवरोध;
		शेष:
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_set_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id,
			जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;

	r = vcpu->kvm->arch.kvm_ops->set_one_reg(vcpu, id, val);
	अगर (r == -EINVAL) अणु
		r = 0;
		चयन (id) अणु
		हाल KVM_REG_PPC_DAR:
			kvmppc_set_dar(vcpu, set_reg_val(id, *val));
			अवरोध;
		हाल KVM_REG_PPC_DSISR:
			kvmppc_set_dsisr(vcpu, set_reg_val(id, *val));
			अवरोध;
		हाल KVM_REG_PPC_FPR0 ... KVM_REG_PPC_FPR31:
			i = id - KVM_REG_PPC_FPR0;
			VCPU_FPR(vcpu, i) = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_FPSCR:
			vcpu->arch.fp.fpscr = set_reg_val(id, *val);
			अवरोध;
#अगर_घोषित CONFIG_VSX
		हाल KVM_REG_PPC_VSR0 ... KVM_REG_PPC_VSR31:
			अगर (cpu_has_feature(CPU_FTR_VSX)) अणु
				i = id - KVM_REG_PPC_VSR0;
				vcpu->arch.fp.fpr[i][0] = val->vsxval[0];
				vcpu->arch.fp.fpr[i][1] = val->vsxval[1];
			पूर्ण अन्यथा अणु
				r = -ENXIO;
			पूर्ण
			अवरोध;
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_KVM_XICS
		हाल KVM_REG_PPC_ICP_STATE:
			अगर (!vcpu->arch.icp && !vcpu->arch.xive_vcpu) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			अगर (xics_on_xive())
				r = kvmppc_xive_set_icp(vcpu, set_reg_val(id, *val));
			अन्यथा
				r = kvmppc_xics_set_icp(vcpu, set_reg_val(id, *val));
			अवरोध;
#पूर्ण_अगर /* CONFIG_KVM_XICS */
#अगर_घोषित CONFIG_KVM_XIVE
		हाल KVM_REG_PPC_VP_STATE:
			अगर (!vcpu->arch.xive_vcpu) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			अगर (xive_enabled())
				r = kvmppc_xive_native_set_vp(vcpu, val);
			अन्यथा
				r = -ENXIO;
			अवरोध;
#पूर्ण_अगर /* CONFIG_KVM_XIVE */
		हाल KVM_REG_PPC_FSCR:
			vcpu->arch.fscr = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_TAR:
			vcpu->arch.tar = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_EBBHR:
			vcpu->arch.ebbhr = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_EBBRR:
			vcpu->arch.ebbrr = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_BESCR:
			vcpu->arch.bescr = set_reg_val(id, *val);
			अवरोध;
		हाल KVM_REG_PPC_IC:
			vcpu->arch.ic = set_reg_val(id, *val);
			अवरोध;
		शेष:
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

व्योम kvmppc_core_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_load(vcpu, cpu);
पूर्ण

व्योम kvmppc_core_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_put(vcpu);
पूर्ण

व्योम kvmppc_set_msr(काष्ठा kvm_vcpu *vcpu, u64 msr)
अणु
	vcpu->kvm->arch.kvm_ops->set_msr(vcpu, msr);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_set_msr);

पूर्णांक kvmppc_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->kvm->arch.kvm_ops->vcpu_run(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
                                  काष्ठा kvm_translation *tr)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg)
अणु
	vcpu_load(vcpu);
	vcpu->guest_debug = dbg->control;
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

व्योम kvmppc_decrementer_func(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_core_queue_dec(vcpu);
	kvm_vcpu_kick(vcpu);
पूर्ण

पूर्णांक kvmppc_core_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->kvm->arch.kvm_ops->vcpu_create(vcpu);
पूर्ण

व्योम kvmppc_core_vcpu_मुक्त(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_मुक्त(vcpu);
पूर्ण

पूर्णांक kvmppc_core_check_requests(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->kvm->arch.kvm_ops->check_requests(vcpu);
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु

पूर्ण

पूर्णांक kvm_vm_ioctl_get_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log)
अणु
	वापस kvm->arch.kvm_ops->get_dirty_log(kvm, log);
पूर्ण

व्योम kvmppc_core_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	kvm->arch.kvm_ops->मुक्त_memslot(slot);
पूर्ण

व्योम kvmppc_core_flush_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु
	kvm->arch.kvm_ops->flush_memslot(kvm, memslot);
पूर्ण

पूर्णांक kvmppc_core_prepare_memory_region(काष्ठा kvm *kvm,
				काष्ठा kvm_memory_slot *memslot,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				क्रमागत kvm_mr_change change)
अणु
	वापस kvm->arch.kvm_ops->prepare_memory_region(kvm, memslot, mem,
							change);
पूर्ण

व्योम kvmppc_core_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				स्थिर काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
	kvm->arch.kvm_ops->commit_memory_region(kvm, mem, old, new, change);
पूर्ण

bool kvm_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm->arch.kvm_ops->unmap_gfn_range(kvm, range);
पूर्ण

bool kvm_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm->arch.kvm_ops->age_gfn(kvm, range);
पूर्ण

bool kvm_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm->arch.kvm_ops->test_age_gfn(kvm, range);
पूर्ण

bool kvm_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm->arch.kvm_ops->set_spte_gfn(kvm, range);
पूर्ण

पूर्णांक kvmppc_core_init_vm(काष्ठा kvm *kvm)
अणु

#अगर_घोषित CONFIG_PPC64
	INIT_LIST_HEAD_RCU(&kvm->arch.spapr_tce_tables);
	INIT_LIST_HEAD(&kvm->arch.rtas_tokens);
	mutex_init(&kvm->arch.rtas_token_lock);
#पूर्ण_अगर

	वापस kvm->arch.kvm_ops->init_vm(kvm);
पूर्ण

व्योम kvmppc_core_destroy_vm(काष्ठा kvm *kvm)
अणु
	kvm->arch.kvm_ops->destroy_vm(kvm);

#अगर_घोषित CONFIG_PPC64
	kvmppc_rtas_tokens_मुक्त(kvm);
	WARN_ON(!list_empty(&kvm->arch.spapr_tce_tables));
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_XICS
	/*
	 * Free the XIVE and XICS devices which are not directly मुक्तd by the
	 * device 'release' method
	 */
	kमुक्त(kvm->arch.xive_devices.native);
	kvm->arch.xive_devices.native = शून्य;
	kमुक्त(kvm->arch.xive_devices.xics_on_xive);
	kvm->arch.xive_devices.xics_on_xive = शून्य;
	kमुक्त(kvm->arch.xics_device);
	kvm->arch.xics_device = शून्य;
#पूर्ण_अगर /* CONFIG_KVM_XICS */
पूर्ण

पूर्णांक kvmppc_h_logical_ci_load(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ size = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ addr = kvmppc_get_gpr(vcpu, 5);
	u64 buf;
	पूर्णांक srcu_idx;
	पूर्णांक ret;

	अगर (!is_घातer_of_2(size) || (size > माप(buf)))
		वापस H_TOO_HARD;

	srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	ret = kvm_io_bus_पढ़ो(vcpu, KVM_MMIO_BUS, addr, size, &buf);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
	अगर (ret != 0)
		वापस H_TOO_HARD;

	चयन (size) अणु
	हाल 1:
		kvmppc_set_gpr(vcpu, 4, *(u8 *)&buf);
		अवरोध;

	हाल 2:
		kvmppc_set_gpr(vcpu, 4, be16_to_cpu(*(__be16 *)&buf));
		अवरोध;

	हाल 4:
		kvmppc_set_gpr(vcpu, 4, be32_to_cpu(*(__be32 *)&buf));
		अवरोध;

	हाल 8:
		kvmppc_set_gpr(vcpu, 4, be64_to_cpu(*(__be64 *)&buf));
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_logical_ci_load);

पूर्णांक kvmppc_h_logical_ci_store(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ size = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ addr = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ val = kvmppc_get_gpr(vcpu, 6);
	u64 buf;
	पूर्णांक srcu_idx;
	पूर्णांक ret;

	चयन (size) अणु
	हाल 1:
		*(u8 *)&buf = val;
		अवरोध;

	हाल 2:
		*(__be16 *)&buf = cpu_to_be16(val);
		अवरोध;

	हाल 4:
		*(__be32 *)&buf = cpu_to_be32(val);
		अवरोध;

	हाल 8:
		*(__be64 *)&buf = cpu_to_be64(val);
		अवरोध;

	शेष:
		वापस H_TOO_HARD;
	पूर्ण

	srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	ret = kvm_io_bus_ग_लिखो(vcpu, KVM_MMIO_BUS, addr, size, &buf);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, srcu_idx);
	अगर (ret != 0)
		वापस H_TOO_HARD;

	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_logical_ci_store);

पूर्णांक kvmppc_core_check_processor_compat(व्योम)
अणु
	/*
	 * We always वापस 0 क्रम book3s. We check
	 * क्रम compatibility जबतक loading the HV
	 * or PR module
	 */
	वापस 0;
पूर्ण

पूर्णांक kvmppc_book3s_hcall_implemented(काष्ठा kvm *kvm, अचिन्हित दीर्घ hcall)
अणु
	वापस kvm->arch.kvm_ops->hcall_implemented(hcall);
पूर्ण

#अगर_घोषित CONFIG_KVM_XICS
पूर्णांक kvm_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq, पूर्णांक level,
		bool line_status)
अणु
	अगर (xics_on_xive())
		वापस kvmppc_xive_set_irq(kvm, irq_source_id, irq, level,
					   line_status);
	अन्यथा
		वापस kvmppc_xics_set_irq(kvm, irq_source_id, irq, level,
					   line_status);
पूर्ण

पूर्णांक kvm_arch_set_irq_inatomic(काष्ठा kvm_kernel_irq_routing_entry *irq_entry,
			      काष्ठा kvm *kvm, पूर्णांक irq_source_id,
			      पूर्णांक level, bool line_status)
अणु
	वापस kvm_set_irq(kvm, irq_source_id, irq_entry->gsi,
			   level, line_status);
पूर्ण
अटल पूर्णांक kvmppc_book3s_set_irq(काष्ठा kvm_kernel_irq_routing_entry *e,
				 काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
				 bool line_status)
अणु
	वापस kvm_set_irq(kvm, irq_source_id, e->gsi, level, line_status);
पूर्ण

पूर्णांक kvm_irq_map_gsi(काष्ठा kvm *kvm,
		    काष्ठा kvm_kernel_irq_routing_entry *entries, पूर्णांक gsi)
अणु
	entries->gsi = gsi;
	entries->type = KVM_IRQ_ROUTING_IRQCHIP;
	entries->set = kvmppc_book3s_set_irq;
	entries->irqchip.irqchip = 0;
	entries->irqchip.pin = gsi;
	वापस 1;
पूर्ण

पूर्णांक kvm_irq_map_chip_pin(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin)
अणु
	वापस pin;
पूर्ण

#पूर्ण_अगर /* CONFIG_KVM_XICS */

अटल पूर्णांक kvmppc_book3s_init(व्योम)
अणु
	पूर्णांक r;

	r = kvm_init(शून्य, माप(काष्ठा kvm_vcpu), 0, THIS_MODULE);
	अगर (r)
		वापस r;
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	r = kvmppc_book3s_init_pr();
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_XICS
#अगर_घोषित CONFIG_KVM_XIVE
	अगर (xics_on_xive()) अणु
		kvmppc_xive_init_module();
		kvm_रेजिस्टर_device_ops(&kvm_xive_ops, KVM_DEV_TYPE_XICS);
		अगर (kvmppc_xive_native_supported()) अणु
			kvmppc_xive_native_init_module();
			kvm_रेजिस्टर_device_ops(&kvm_xive_native_ops,
						KVM_DEV_TYPE_XIVE);
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
		kvm_रेजिस्टर_device_ops(&kvm_xics_ops, KVM_DEV_TYPE_XICS);
#पूर्ण_अगर
	वापस r;
पूर्ण

अटल व्योम kvmppc_book3s_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_KVM_XICS
	अगर (xics_on_xive()) अणु
		kvmppc_xive_निकास_module();
		kvmppc_xive_native_निकास_module();
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	kvmppc_book3s_निकास_pr();
#पूर्ण_अगर
	kvm_निकास();
पूर्ण

module_init(kvmppc_book3s_init);
module_निकास(kvmppc_book3s_निकास);

/* On 32bit this is our one and only kernel module */
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
#पूर्ण_अगर
