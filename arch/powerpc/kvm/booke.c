<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2007
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 *          Christian Ehrhardt <ehrhardt@linux.vnet.ibm.com>
 *          Scott Wood <scottwood@मुक्तscale.com>
 *          Varun Sethi <varun.sethi@मुक्तscale.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>

#समावेश <यंत्र/cputable.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/समय.स>

#समावेश "timing.h"
#समावेश "booke.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_booke.h"

अचिन्हित दीर्घ kvmppc_booke_handlers;

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("mmio", mmio_निकासs),
	VCPU_STAT("sig", संकेत_निकासs),
	VCPU_STAT("itlb_r", itlb_real_miss_निकासs),
	VCPU_STAT("itlb_v", itlb_virt_miss_निकासs),
	VCPU_STAT("dtlb_r", dtlb_real_miss_निकासs),
	VCPU_STAT("dtlb_v", dtlb_virt_miss_निकासs),
	VCPU_STAT("sysc", syscall_निकासs),
	VCPU_STAT("isi", isi_निकासs),
	VCPU_STAT("dsi", dsi_निकासs),
	VCPU_STAT("inst_emu", emulated_inst_निकासs),
	VCPU_STAT("dec", dec_निकासs),
	VCPU_STAT("ext_intr", ext_पूर्णांकr_निकासs),
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("doorbell", dbell_निकासs),
	VCPU_STAT("guest doorbell", gdbell_निकासs),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	VM_STAT("remote_tlb_flush", remote_tlb_flush),
	अणु शून्य पूर्ण
पूर्ण;

/* TODO: use vcpu_म_लिखो() */
व्योम kvmppc_dump_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	prपूर्णांकk("pc:   %08lx msr:  %08llx\n", vcpu->arch.regs.nip,
			vcpu->arch.shared->msr);
	prपूर्णांकk("lr:   %08lx ctr:  %08lx\n", vcpu->arch.regs.link,
			vcpu->arch.regs.ctr);
	prपूर्णांकk("srr0: %08llx srr1: %08llx\n", vcpu->arch.shared->srr0,
					    vcpu->arch.shared->srr1);

	prपूर्णांकk("exceptions: %08lx\n", vcpu->arch.pending_exceptions);

	क्रम (i = 0; i < 32; i += 4) अणु
		prपूर्णांकk("gpr%02d: %08lx %08lx %08lx %08lx\n", i,
		       kvmppc_get_gpr(vcpu, i),
		       kvmppc_get_gpr(vcpu, i+1),
		       kvmppc_get_gpr(vcpu, i+2),
		       kvmppc_get_gpr(vcpu, i+3));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SPE
व्योम kvmppc_vcpu_disable_spe(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	enable_kernel_spe();
	kvmppc_save_guest_spe(vcpu);
	disable_kernel_spe();
	vcpu->arch.shaकरोw_msr &= ~MSR_SPE;
	preempt_enable();
पूर्ण

अटल व्योम kvmppc_vcpu_enable_spe(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	enable_kernel_spe();
	kvmppc_load_guest_spe(vcpu);
	disable_kernel_spe();
	vcpu->arch.shaकरोw_msr |= MSR_SPE;
	preempt_enable();
पूर्ण

अटल व्योम kvmppc_vcpu_sync_spe(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.shared->msr & MSR_SPE) अणु
		अगर (!(vcpu->arch.shaकरोw_msr & MSR_SPE))
			kvmppc_vcpu_enable_spe(vcpu);
	पूर्ण अन्यथा अगर (vcpu->arch.shaकरोw_msr & MSR_SPE) अणु
		kvmppc_vcpu_disable_spe(vcpu);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम kvmppc_vcpu_sync_spe(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Load up guest vcpu FP state अगर it's needed.
 * It also set the MSR_FP in thपढ़ो so that host know
 * we're holding FPU, and then host can help to save
 * guest vcpu FP state अगर other thपढ़ोs require to use FPU.
 * This simulates an FP unavailable fault.
 *
 * It requires to be called with preemption disabled.
 */
अटल अंतरभूत व्योम kvmppc_load_guest_fp(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_PPC_FPU
	अगर (!(current->thपढ़ो.regs->msr & MSR_FP)) अणु
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		current->thपढ़ो.fp_save_area = &vcpu->arch.fp;
		current->thपढ़ो.regs->msr |= MSR_FP;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Save guest vcpu FP state पूर्णांकo thपढ़ो.
 * It requires to be called with preemption disabled.
 */
अटल अंतरभूत व्योम kvmppc_save_guest_fp(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_PPC_FPU
	अगर (current->thपढ़ो.regs->msr & MSR_FP)
		giveup_fpu(current);
	current->thपढ़ो.fp_save_area = शून्य;
#पूर्ण_अगर
पूर्ण

अटल व्योम kvmppc_vcpu_sync_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर defined(CONFIG_PPC_FPU) && !defined(CONFIG_KVM_BOOKE_HV)
	/* We always treat the FP bit as enabled from the host
	   perspective, so only need to adjust the shaकरोw MSR */
	vcpu->arch.shaकरोw_msr &= ~MSR_FP;
	vcpu->arch.shaकरोw_msr |= vcpu->arch.shared->msr & MSR_FP;
#पूर्ण_अगर
पूर्ण

/*
 * Simulate AltiVec unavailable fault to load guest state
 * from thपढ़ो to AltiVec unit.
 * It requires to be called with preemption disabled.
 */
अटल अंतरभूत व्योम kvmppc_load_guest_altivec(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
		अगर (!(current->thपढ़ो.regs->msr & MSR_VEC)) अणु
			enable_kernel_altivec();
			load_vr_state(&vcpu->arch.vr);
			disable_kernel_altivec();
			current->thपढ़ो.vr_save_area = &vcpu->arch.vr;
			current->thपढ़ो.regs->msr |= MSR_VEC;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Save guest vcpu AltiVec state पूर्णांकo thपढ़ो.
 * It requires to be called with preemption disabled.
 */
अटल अंतरभूत व्योम kvmppc_save_guest_altivec(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
		अगर (current->thपढ़ो.regs->msr & MSR_VEC)
			giveup_altivec(current);
		current->thपढ़ो.vr_save_area = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम kvmppc_vcpu_sync_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Synchronize guest's desire to get debug पूर्णांकerrupts पूर्णांकo shaकरोw MSR */
#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	vcpu->arch.shaकरोw_msr &= ~MSR_DE;
	vcpu->arch.shaकरोw_msr |= vcpu->arch.shared->msr & MSR_DE;
#पूर्ण_अगर

	/* Force enable debug पूर्णांकerrupts when user space wants to debug */
	अगर (vcpu->guest_debug) अणु
#अगर_घोषित CONFIG_KVM_BOOKE_HV
		/*
		 * Since there is no shaकरोw MSR, sync MSR_DE पूर्णांकo the guest
		 * visible MSR.
		 */
		vcpu->arch.shared->msr |= MSR_DE;
#अन्यथा
		vcpu->arch.shaकरोw_msr |= MSR_DE;
		vcpu->arch.shared->msr &= ~MSR_DE;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Helper function क्रम "full" MSR ग_लिखोs.  No need to call this अगर only
 * EE/CE/ME/DE/RI are changing.
 */
व्योम kvmppc_set_msr(काष्ठा kvm_vcpu *vcpu, u32 new_msr)
अणु
	u32 old_msr = vcpu->arch.shared->msr;

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	new_msr |= MSR_GS;
#पूर्ण_अगर

	vcpu->arch.shared->msr = new_msr;

	kvmppc_mmu_msr_notअगरy(vcpu, old_msr);
	kvmppc_vcpu_sync_spe(vcpu);
	kvmppc_vcpu_sync_fpu(vcpu);
	kvmppc_vcpu_sync_debug(vcpu);
पूर्ण

अटल व्योम kvmppc_booke_queue_irqprio(काष्ठा kvm_vcpu *vcpu,
                                       अचिन्हित पूर्णांक priority)
अणु
	trace_kvm_booke_queue_irqprio(vcpu, priority);
	set_bit(priority, &vcpu->arch.pending_exceptions);
पूर्ण

व्योम kvmppc_core_queue_dtlb_miss(काष्ठा kvm_vcpu *vcpu,
				 uदीर्घ dear_flags, uदीर्घ esr_flags)
अणु
	vcpu->arch.queued_dear = dear_flags;
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_DTLB_MISS);
पूर्ण

व्योम kvmppc_core_queue_data_storage(काष्ठा kvm_vcpu *vcpu,
				    uदीर्घ dear_flags, uदीर्घ esr_flags)
अणु
	vcpu->arch.queued_dear = dear_flags;
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_DATA_STORAGE);
पूर्ण

व्योम kvmppc_core_queue_itlb_miss(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ITLB_MISS);
पूर्ण

व्योम kvmppc_core_queue_inst_storage(काष्ठा kvm_vcpu *vcpu, uदीर्घ esr_flags)
अणु
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_INST_STORAGE);
पूर्ण

अटल व्योम kvmppc_core_queue_alignment(काष्ठा kvm_vcpu *vcpu, uदीर्घ dear_flags,
					uदीर्घ esr_flags)
अणु
	vcpu->arch.queued_dear = dear_flags;
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ALIGNMENT);
पूर्ण

व्योम kvmppc_core_queue_program(काष्ठा kvm_vcpu *vcpu, uदीर्घ esr_flags)
अणु
	vcpu->arch.queued_esr = esr_flags;
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_PROGRAM);
पूर्ण

व्योम kvmppc_core_queue_fpunavail(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_FP_UNAVAIL);
पूर्ण

#अगर_घोषित CONFIG_ALTIVEC
व्योम kvmppc_core_queue_vec_unavail(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ALTIVEC_UNAVAIL);
पूर्ण
#पूर्ण_अगर

व्योम kvmppc_core_queue_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_DECREMENTER);
पूर्ण

पूर्णांक kvmppc_core_pending_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस test_bit(BOOKE_IRQPRIO_DECREMENTER, &vcpu->arch.pending_exceptions);
पूर्ण

व्योम kvmppc_core_dequeue_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	clear_bit(BOOKE_IRQPRIO_DECREMENTER, &vcpu->arch.pending_exceptions);
पूर्ण

व्योम kvmppc_core_queue_बाह्यal(काष्ठा kvm_vcpu *vcpu,
                                काष्ठा kvm_पूर्णांकerrupt *irq)
अणु
	अचिन्हित पूर्णांक prio = BOOKE_IRQPRIO_EXTERNAL;

	अगर (irq->irq == KVM_INTERRUPT_SET_LEVEL)
		prio = BOOKE_IRQPRIO_EXTERNAL_LEVEL;

	kvmppc_booke_queue_irqprio(vcpu, prio);
पूर्ण

व्योम kvmppc_core_dequeue_बाह्यal(काष्ठा kvm_vcpu *vcpu)
अणु
	clear_bit(BOOKE_IRQPRIO_EXTERNAL, &vcpu->arch.pending_exceptions);
	clear_bit(BOOKE_IRQPRIO_EXTERNAL_LEVEL, &vcpu->arch.pending_exceptions);
पूर्ण

अटल व्योम kvmppc_core_queue_watchकरोg(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_WATCHDOG);
पूर्ण

अटल व्योम kvmppc_core_dequeue_watchकरोg(काष्ठा kvm_vcpu *vcpu)
अणु
	clear_bit(BOOKE_IRQPRIO_WATCHDOG, &vcpu->arch.pending_exceptions);
पूर्ण

व्योम kvmppc_core_queue_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_DEBUG);
पूर्ण

व्योम kvmppc_core_dequeue_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	clear_bit(BOOKE_IRQPRIO_DEBUG, &vcpu->arch.pending_exceptions);
पूर्ण

अटल व्योम set_guest_srr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ srr0, u32 srr1)
अणु
	kvmppc_set_srr0(vcpu, srr0);
	kvmppc_set_srr1(vcpu, srr1);
पूर्ण

अटल व्योम set_guest_csrr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ srr0, u32 srr1)
अणु
	vcpu->arch.csrr0 = srr0;
	vcpu->arch.csrr1 = srr1;
पूर्ण

अटल व्योम set_guest_dsrr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ srr0, u32 srr1)
अणु
	अगर (cpu_has_feature(CPU_FTR_DEBUG_LVL_EXC)) अणु
		vcpu->arch.dsrr0 = srr0;
		vcpu->arch.dsrr1 = srr1;
	पूर्ण अन्यथा अणु
		set_guest_csrr(vcpu, srr0, srr1);
	पूर्ण
पूर्ण

अटल व्योम set_guest_mcsrr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ srr0, u32 srr1)
अणु
	vcpu->arch.mcsrr0 = srr0;
	vcpu->arch.mcsrr1 = srr1;
पूर्ण

/* Deliver the पूर्णांकerrupt of the corresponding priority, अगर possible. */
अटल पूर्णांक kvmppc_booke_irqprio_deliver(काष्ठा kvm_vcpu *vcpu,
                                        अचिन्हित पूर्णांक priority)
अणु
	पूर्णांक allowed = 0;
	uदीर्घ msr_mask = 0;
	bool update_esr = false, update_dear = false, update_epr = false;
	uदीर्घ crit_raw = vcpu->arch.shared->critical;
	uदीर्घ crit_r1 = kvmppc_get_gpr(vcpu, 1);
	bool crit;
	bool keep_irq = false;
	क्रमागत पूर्णांक_class पूर्णांक_class;
	uदीर्घ new_msr = vcpu->arch.shared->msr;

	/* Truncate crit indicators in 32 bit mode */
	अगर (!(vcpu->arch.shared->msr & MSR_SF)) अणु
		crit_raw &= 0xffffffff;
		crit_r1 &= 0xffffffff;
	पूर्ण

	/* Critical section when crit == r1 */
	crit = (crit_raw == crit_r1);
	/* ... and we're in supervisor mode */
	crit = crit && !(vcpu->arch.shared->msr & MSR_PR);

	अगर (priority == BOOKE_IRQPRIO_EXTERNAL_LEVEL) अणु
		priority = BOOKE_IRQPRIO_EXTERNAL;
		keep_irq = true;
	पूर्ण

	अगर ((priority == BOOKE_IRQPRIO_EXTERNAL) && vcpu->arch.epr_flags)
		update_epr = true;

	चयन (priority) अणु
	हाल BOOKE_IRQPRIO_DTLB_MISS:
	हाल BOOKE_IRQPRIO_DATA_STORAGE:
	हाल BOOKE_IRQPRIO_ALIGNMENT:
		update_dear = true;
		fallthrough;
	हाल BOOKE_IRQPRIO_INST_STORAGE:
	हाल BOOKE_IRQPRIO_PROGRAM:
		update_esr = true;
		fallthrough;
	हाल BOOKE_IRQPRIO_ITLB_MISS:
	हाल BOOKE_IRQPRIO_SYSCALL:
	हाल BOOKE_IRQPRIO_FP_UNAVAIL:
#अगर_घोषित CONFIG_SPE_POSSIBLE
	हाल BOOKE_IRQPRIO_SPE_UNAVAIL:
	हाल BOOKE_IRQPRIO_SPE_FP_DATA:
	हाल BOOKE_IRQPRIO_SPE_FP_ROUND:
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल BOOKE_IRQPRIO_ALTIVEC_UNAVAIL:
	हाल BOOKE_IRQPRIO_ALTIVEC_ASSIST:
#पूर्ण_अगर
	हाल BOOKE_IRQPRIO_AP_UNAVAIL:
		allowed = 1;
		msr_mask = MSR_CE | MSR_ME | MSR_DE;
		पूर्णांक_class = INT_CLASS_NONCRIT;
		अवरोध;
	हाल BOOKE_IRQPRIO_WATCHDOG:
	हाल BOOKE_IRQPRIO_CRITICAL:
	हाल BOOKE_IRQPRIO_DBELL_CRIT:
		allowed = vcpu->arch.shared->msr & MSR_CE;
		allowed = allowed && !crit;
		msr_mask = MSR_ME;
		पूर्णांक_class = INT_CLASS_CRIT;
		अवरोध;
	हाल BOOKE_IRQPRIO_MACHINE_CHECK:
		allowed = vcpu->arch.shared->msr & MSR_ME;
		allowed = allowed && !crit;
		पूर्णांक_class = INT_CLASS_MC;
		अवरोध;
	हाल BOOKE_IRQPRIO_DECREMENTER:
	हाल BOOKE_IRQPRIO_FIT:
		keep_irq = true;
		fallthrough;
	हाल BOOKE_IRQPRIO_EXTERNAL:
	हाल BOOKE_IRQPRIO_DBELL:
		allowed = vcpu->arch.shared->msr & MSR_EE;
		allowed = allowed && !crit;
		msr_mask = MSR_CE | MSR_ME | MSR_DE;
		पूर्णांक_class = INT_CLASS_NONCRIT;
		अवरोध;
	हाल BOOKE_IRQPRIO_DEBUG:
		allowed = vcpu->arch.shared->msr & MSR_DE;
		allowed = allowed && !crit;
		msr_mask = MSR_ME;
		अगर (cpu_has_feature(CPU_FTR_DEBUG_LVL_EXC))
			पूर्णांक_class = INT_CLASS_DBG;
		अन्यथा
			पूर्णांक_class = INT_CLASS_CRIT;

		अवरोध;
	पूर्ण

	अगर (allowed) अणु
		चयन (पूर्णांक_class) अणु
		हाल INT_CLASS_NONCRIT:
			set_guest_srr(vcpu, vcpu->arch.regs.nip,
				      vcpu->arch.shared->msr);
			अवरोध;
		हाल INT_CLASS_CRIT:
			set_guest_csrr(vcpu, vcpu->arch.regs.nip,
				       vcpu->arch.shared->msr);
			अवरोध;
		हाल INT_CLASS_DBG:
			set_guest_dsrr(vcpu, vcpu->arch.regs.nip,
				       vcpu->arch.shared->msr);
			अवरोध;
		हाल INT_CLASS_MC:
			set_guest_mcsrr(vcpu, vcpu->arch.regs.nip,
					vcpu->arch.shared->msr);
			अवरोध;
		पूर्ण

		vcpu->arch.regs.nip = vcpu->arch.ivpr |
					vcpu->arch.ivor[priority];
		अगर (update_esr)
			kvmppc_set_esr(vcpu, vcpu->arch.queued_esr);
		अगर (update_dear)
			kvmppc_set_dar(vcpu, vcpu->arch.queued_dear);
		अगर (update_epr) अणु
			अगर (vcpu->arch.epr_flags & KVMPPC_EPR_USER)
				kvm_make_request(KVM_REQ_EPR_EXIT, vcpu);
			अन्यथा अगर (vcpu->arch.epr_flags & KVMPPC_EPR_KERNEL) अणु
				BUG_ON(vcpu->arch.irq_type != KVMPPC_IRQ_MPIC);
				kvmppc_mpic_set_epr(vcpu);
			पूर्ण
		पूर्ण

		new_msr &= msr_mask;
#अगर defined(CONFIG_64BIT)
		अगर (vcpu->arch.epcr & SPRN_EPCR_ICM)
			new_msr |= MSR_CM;
#पूर्ण_अगर
		kvmppc_set_msr(vcpu, new_msr);

		अगर (!keep_irq)
			clear_bit(priority, &vcpu->arch.pending_exceptions);
	पूर्ण

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	/*
	 * If an पूर्णांकerrupt is pending but masked, उठाओ a guest करोorbell
	 * so that we are notअगरied when the guest enables the relevant
	 * MSR bit.
	 */
	अगर (vcpu->arch.pending_exceptions & BOOKE_IRQMASK_EE)
		kvmppc_set_pending_पूर्णांकerrupt(vcpu, INT_CLASS_NONCRIT);
	अगर (vcpu->arch.pending_exceptions & BOOKE_IRQMASK_CE)
		kvmppc_set_pending_पूर्णांकerrupt(vcpu, INT_CLASS_CRIT);
	अगर (vcpu->arch.pending_exceptions & BOOKE_IRQPRIO_MACHINE_CHECK)
		kvmppc_set_pending_पूर्णांकerrupt(vcpu, INT_CLASS_MC);
#पूर्ण_अगर

	वापस allowed;
पूर्ण

/*
 * Return the number of jअगरfies until the next समयout.  If the समयout is
 * दीर्घer than the NEXT_TIMER_MAX_DELTA, then वापस NEXT_TIMER_MAX_DELTA
 * because the larger value can अवरोध the समयr APIs.
 */
अटल अचिन्हित दीर्घ watchकरोg_next_समयout(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 tb, wdt_tb, wdt_ticks = 0;
	u64 nr_jअगरfies = 0;
	u32 period = TCR_GET_WP(vcpu->arch.tcr);

	wdt_tb = 1ULL << (63 - period);
	tb = get_tb();
	/*
	 * The watchकरोg समयout will hapeen when TB bit corresponding
	 * to watchकरोg will toggle from 0 to 1.
	 */
	अगर (tb & wdt_tb)
		wdt_ticks = wdt_tb;

	wdt_ticks += wdt_tb - (tb & (wdt_tb - 1));

	/* Convert समयbase ticks to jअगरfies */
	nr_jअगरfies = wdt_ticks;

	अगर (करो_भाग(nr_jअगरfies, tb_ticks_per_jअगरfy))
		nr_jअगरfies++;

	वापस min_t(अचिन्हित दीर्घ दीर्घ, nr_jअगरfies, NEXT_TIMER_MAX_DELTA);
पूर्ण

अटल व्योम arm_next_watchकरोg(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ nr_jअगरfies;
	अचिन्हित दीर्घ flags;

	/*
	 * If TSR_ENW and TSR_WIS are not set then no need to निकास to
	 * userspace, so clear the KVM_REQ_WATCHDOG request.
	 */
	अगर ((vcpu->arch.tsr & (TSR_ENW | TSR_WIS)) != (TSR_ENW | TSR_WIS))
		kvm_clear_request(KVM_REQ_WATCHDOG, vcpu);

	spin_lock_irqsave(&vcpu->arch.wdt_lock, flags);
	nr_jअगरfies = watchकरोg_next_समयout(vcpu);
	/*
	 * If the number of jअगरfies of watchकरोg समयr >= NEXT_TIMER_MAX_DELTA
	 * then करो not run the watchकरोg समयr as this can अवरोध समयr APIs.
	 */
	अगर (nr_jअगरfies < NEXT_TIMER_MAX_DELTA)
		mod_समयr(&vcpu->arch.wdt_समयr, jअगरfies + nr_jअगरfies);
	अन्यथा
		del_समयr(&vcpu->arch.wdt_समयr);
	spin_unlock_irqrestore(&vcpu->arch.wdt_lock, flags);
पूर्ण

व्योम kvmppc_watchकरोg_func(काष्ठा समयr_list *t)
अणु
	काष्ठा kvm_vcpu *vcpu = from_समयr(vcpu, t, arch.wdt_समयr);
	u32 tsr, new_tsr;
	पूर्णांक final;

	करो अणु
		new_tsr = tsr = vcpu->arch.tsr;
		final = 0;

		/* Time out event */
		अगर (tsr & TSR_ENW) अणु
			अगर (tsr & TSR_WIS)
				final = 1;
			अन्यथा
				new_tsr = tsr | TSR_WIS;
		पूर्ण अन्यथा अणु
			new_tsr = tsr | TSR_ENW;
		पूर्ण
	पूर्ण जबतक (cmpxchg(&vcpu->arch.tsr, tsr, new_tsr) != tsr);

	अगर (new_tsr & TSR_WIS) अणु
		smp_wmb();
		kvm_make_request(KVM_REQ_PENDING_TIMER, vcpu);
		kvm_vcpu_kick(vcpu);
	पूर्ण

	/*
	 * If this is final watchकरोg expiry and some action is required
	 * then निकास to userspace.
	 */
	अगर (final && (vcpu->arch.tcr & TCR_WRC_MASK) &&
	    vcpu->arch.watchकरोg_enabled) अणु
		smp_wmb();
		kvm_make_request(KVM_REQ_WATCHDOG, vcpu);
		kvm_vcpu_kick(vcpu);
	पूर्ण

	/*
	 * Stop running the watchकरोg समयr after final expiration to
	 * prevent the host from being flooded with समयrs अगर the
	 * guest sets a लघु period.
	 * Timers will resume when TSR/TCR is updated next समय.
	 */
	अगर (!final)
		arm_next_watchकरोg(vcpu);
पूर्ण

अटल व्योम update_समयr_पूर्णांकs(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर ((vcpu->arch.tcr & TCR_DIE) && (vcpu->arch.tsr & TSR_DIS))
		kvmppc_core_queue_dec(vcpu);
	अन्यथा
		kvmppc_core_dequeue_dec(vcpu);

	अगर ((vcpu->arch.tcr & TCR_WIE) && (vcpu->arch.tsr & TSR_WIS))
		kvmppc_core_queue_watchकरोg(vcpu);
	अन्यथा
		kvmppc_core_dequeue_watchकरोg(vcpu);
पूर्ण

अटल व्योम kvmppc_core_check_exceptions(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ *pending = &vcpu->arch.pending_exceptions;
	अचिन्हित पूर्णांक priority;

	priority = __ffs(*pending);
	जबतक (priority < BOOKE_IRQPRIO_MAX) अणु
		अगर (kvmppc_booke_irqprio_deliver(vcpu, priority))
			अवरोध;

		priority = find_next_bit(pending,
		                         BITS_PER_BYTE * माप(*pending),
		                         priority + 1);
	पूर्ण

	/* Tell the guest about our पूर्णांकerrupt status */
	vcpu->arch.shared->पूर्णांक_pending = !!*pending;
पूर्ण

/* Check pending exceptions and deliver one, अगर possible. */
पूर्णांक kvmppc_core_prepare_to_enter(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = 0;
	WARN_ON_ONCE(!irqs_disabled());

	kvmppc_core_check_exceptions(vcpu);

	अगर (kvm_request_pending(vcpu)) अणु
		/* Exception delivery उठाओd request; start over */
		वापस 1;
	पूर्ण

	अगर (vcpu->arch.shared->msr & MSR_WE) अणु
		local_irq_enable();
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		hard_irq_disable();

		kvmppc_set_निकास_type(vcpu, EMULATED_MTMSRWE_EXITS);
		r = 1;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_core_check_requests(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = 1; /* Indicate we want to get back पूर्णांकo the guest */

	अगर (kvm_check_request(KVM_REQ_PENDING_TIMER, vcpu))
		update_समयr_पूर्णांकs(vcpu);
#अगर defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu))
		kvmppc_core_flush_tlb(vcpu);
#पूर्ण_अगर

	अगर (kvm_check_request(KVM_REQ_WATCHDOG, vcpu)) अणु
		vcpu->run->निकास_reason = KVM_EXIT_WATCHDOG;
		r = 0;
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_EPR_EXIT, vcpu)) अणु
		vcpu->run->epr.epr = 0;
		vcpu->arch.epr_needed = true;
		vcpu->run->निकास_reason = KVM_EXIT_EPR;
		r = 0;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret, s;
	काष्ठा debug_reg debug;

	अगर (!vcpu->arch.sane) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		वापस -EINVAL;
	पूर्ण

	s = kvmppc_prepare_to_enter(vcpu);
	अगर (s <= 0) अणु
		ret = s;
		जाओ out;
	पूर्ण
	/* पूर्णांकerrupts now hard-disabled */

#अगर_घोषित CONFIG_PPC_FPU
	/* Save userspace FPU state in stack */
	enable_kernel_fp();

	/*
	 * Since we can't trap on MSR_FP in GS-mode, we consider the guest
	 * as always using the FPU.
	 */
	kvmppc_load_guest_fp(vcpu);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ALTIVEC
	/* Save userspace AltiVec state in stack */
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		enable_kernel_altivec();
	/*
	 * Since we can't trap on MSR_VEC in GS-mode, we consider the guest
	 * as always using the AltiVec.
	 */
	kvmppc_load_guest_altivec(vcpu);
#पूर्ण_अगर

	/* Switch to guest debug context */
	debug = vcpu->arch.dbg_reg;
	चयन_booke_debug_regs(&debug);
	debug = current->thपढ़ो.debug;
	current->thपढ़ो.debug = vcpu->arch.dbg_reg;

	vcpu->arch.pgdir = vcpu->kvm->mm->pgd;
	kvmppc_fix_ee_beक्रमe_entry();

	ret = __kvmppc_vcpu_run(vcpu);

	/* No need क्रम guest_निकास. It's करोne in handle_निकास.
	   We also get here with पूर्णांकerrupts enabled. */

	/* Switch back to user space debug context */
	चयन_booke_debug_regs(&debug);
	current->thपढ़ो.debug = debug;

#अगर_घोषित CONFIG_PPC_FPU
	kvmppc_save_guest_fp(vcpu);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ALTIVEC
	kvmppc_save_guest_altivec(vcpu);
#पूर्ण_अगर

out:
	vcpu->mode = OUTSIDE_GUEST_MODE;
	वापस ret;
पूर्ण

अटल पूर्णांक emulation_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er;

	er = kvmppc_emulate_inकाष्ठाion(vcpu);
	चयन (er) अणु
	हाल EMULATE_DONE:
		/* करोn't overग_लिखो subtypes, just account kvm_stats */
		kvmppc_account_निकास_stat(vcpu, EMULATED_INST_EXITS);
		/* Future optimization: only reload non-अस्थिरs अगर
		 * they were actually modअगरied by emulation. */
		वापस RESUME_GUEST_NV;

	हाल EMULATE_AGAIN:
		वापस RESUME_GUEST;

	हाल EMULATE_FAIL:
		prपूर्णांकk(KERN_CRIT "%s: emulation at %lx failed (%08x)\n",
		       __func__, vcpu->arch.regs.nip, vcpu->arch.last_inst);
		/* For debugging, encode the failing inकाष्ठाion and
		 * report it to userspace. */
		vcpu->run->hw.hardware_निकास_reason = ~0ULL << 32;
		vcpu->run->hw.hardware_निकास_reason |= vcpu->arch.last_inst;
		kvmppc_core_queue_program(vcpu, ESR_PIL);
		वापस RESUME_HOST;

	हाल EMULATE_EXIT_USER:
		वापस RESUME_HOST;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_handle_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	काष्ठा debug_reg *dbg_reg = &(vcpu->arch.dbg_reg);
	u32 dbsr = vcpu->arch.dbsr;

	अगर (vcpu->guest_debug == 0) अणु
		/*
		 * Debug resources beदीर्घ to Guest.
		 * Imprecise debug event is not injected
		 */
		अगर (dbsr & DBSR_IDE) अणु
			dbsr &= ~DBSR_IDE;
			अगर (!dbsr)
				वापस RESUME_GUEST;
		पूर्ण

		अगर (dbsr && (vcpu->arch.shared->msr & MSR_DE) &&
			    (vcpu->arch.dbg_reg.dbcr0 & DBCR0_IDM))
			kvmppc_core_queue_debug(vcpu);

		/* Inject a program पूर्णांकerrupt अगर trap debug is not allowed */
		अगर ((dbsr & DBSR_TIE) && !(vcpu->arch.shared->msr & MSR_DE))
			kvmppc_core_queue_program(vcpu, ESR_PTR);

		वापस RESUME_GUEST;
	पूर्ण

	/*
	 * Debug resource owned by userspace.
	 * Clear guest dbsr (vcpu->arch.dbsr)
	 */
	vcpu->arch.dbsr = 0;
	run->debug.arch.status = 0;
	run->debug.arch.address = vcpu->arch.regs.nip;

	अगर (dbsr & (DBSR_IAC1 | DBSR_IAC2 | DBSR_IAC3 | DBSR_IAC4)) अणु
		run->debug.arch.status |= KVMPPC_DEBUG_BREAKPOINT;
	पूर्ण अन्यथा अणु
		अगर (dbsr & (DBSR_DAC1W | DBSR_DAC2W))
			run->debug.arch.status |= KVMPPC_DEBUG_WATCH_WRITE;
		अन्यथा अगर (dbsr & (DBSR_DAC1R | DBSR_DAC2R))
			run->debug.arch.status |= KVMPPC_DEBUG_WATCH_READ;
		अगर (dbsr & (DBSR_DAC1R | DBSR_DAC1W))
			run->debug.arch.address = dbg_reg->dac1;
		अन्यथा अगर (dbsr & (DBSR_DAC2R | DBSR_DAC2W))
			run->debug.arch.address = dbg_reg->dac2;
	पूर्ण

	वापस RESUME_HOST;
पूर्ण

अटल व्योम kvmppc_fill_pt_regs(काष्ठा pt_regs *regs)
अणु
	uदीर्घ r1, ip, msr, lr;

	यंत्र("mr %0, 1" : "=r"(r1));
	यंत्र("mflr %0" : "=r"(lr));
	यंत्र("mfmsr %0" : "=r"(msr));
	यंत्र("bl 1f; 1: mflr %0" : "=r"(ip));

	स_रखो(regs, 0, माप(*regs));
	regs->gpr[1] = r1;
	regs->nip = ip;
	regs->msr = msr;
	regs->link = lr;
पूर्ण

/*
 * For पूर्णांकerrupts needed to be handled by host पूर्णांकerrupt handlers,
 * corresponding host handler are called from here in similar way
 * (but not exact) as they are called from low level handler
 * (such as from arch/घातerpc/kernel/head_fsl_booke.S).
 */
अटल व्योम kvmppc_restart_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
				     अचिन्हित पूर्णांक निकास_nr)
अणु
	काष्ठा pt_regs regs;

	चयन (निकास_nr) अणु
	हाल BOOKE_INTERRUPT_EXTERNAL:
		kvmppc_fill_pt_regs(&regs);
		करो_IRQ(&regs);
		अवरोध;
	हाल BOOKE_INTERRUPT_DECREMENTER:
		kvmppc_fill_pt_regs(&regs);
		समयr_पूर्णांकerrupt(&regs);
		अवरोध;
#अगर defined(CONFIG_PPC_DOORBELL)
	हाल BOOKE_INTERRUPT_DOORBELL:
		kvmppc_fill_pt_regs(&regs);
		करोorbell_exception(&regs);
		अवरोध;
#पूर्ण_अगर
	हाल BOOKE_INTERRUPT_MACHINE_CHECK:
		/* FIXME */
		अवरोध;
	हाल BOOKE_INTERRUPT_PERFORMANCE_MONITOR:
		kvmppc_fill_pt_regs(&regs);
		perक्रमmance_monitor_exception(&regs);
		अवरोध;
	हाल BOOKE_INTERRUPT_WATCHDOG:
		kvmppc_fill_pt_regs(&regs);
#अगर_घोषित CONFIG_BOOKE_WDT
		WatchकरोgException(&regs);
#अन्यथा
		unknown_exception(&regs);
#पूर्ण_अगर
		अवरोध;
	हाल BOOKE_INTERRUPT_CRITICAL:
		kvmppc_fill_pt_regs(&regs);
		unknown_exception(&regs);
		अवरोध;
	हाल BOOKE_INTERRUPT_DEBUG:
		/* Save DBSR beक्रमe preemption is enabled */
		vcpu->arch.dbsr = mfspr(SPRN_DBSR);
		kvmppc_clear_dbsr();
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_resume_inst_load(काष्ठा kvm_vcpu *vcpu,
				  क्रमागत emulation_result emulated, u32 last_inst)
अणु
	चयन (emulated) अणु
	हाल EMULATE_AGAIN:
		वापस RESUME_GUEST;

	हाल EMULATE_FAIL:
		pr_debug("%s: load instruction from guest address %lx failed\n",
		       __func__, vcpu->arch.regs.nip);
		/* For debugging, encode the failing inकाष्ठाion and
		 * report it to userspace. */
		vcpu->run->hw.hardware_निकास_reason = ~0ULL << 32;
		vcpu->run->hw.hardware_निकास_reason |= last_inst;
		kvmppc_core_queue_program(vcpu, ESR_PIL);
		वापस RESUME_HOST;

	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * kvmppc_handle_निकास
 *
 * Return value is in the क्रमm (errcode<<2 | RESUME_FLAG_HOST | RESUME_FLAG_NV)
 */
पूर्णांक kvmppc_handle_निकास(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक निकास_nr)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r = RESUME_HOST;
	पूर्णांक s;
	पूर्णांक idx;
	u32 last_inst = KVM_INST_FETCH_FAILED;
	क्रमागत emulation_result emulated = EMULATE_DONE;

	/* update beक्रमe a new last_निकास_type is rewritten */
	kvmppc_update_timing_stats(vcpu);

	/* restart पूर्णांकerrupts अगर they were meant क्रम the host */
	kvmppc_restart_पूर्णांकerrupt(vcpu, निकास_nr);

	/*
	 * get last inकाष्ठाion beक्रमe being preempted
	 * TODO: क्रम e6500 check also BOOKE_INTERRUPT_LRAT_ERROR & ESR_DATA
	 */
	चयन (निकास_nr) अणु
	हाल BOOKE_INTERRUPT_DATA_STORAGE:
	हाल BOOKE_INTERRUPT_DTLB_MISS:
	हाल BOOKE_INTERRUPT_HV_PRIV:
		emulated = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);
		अवरोध;
	हाल BOOKE_INTERRUPT_PROGRAM:
		/* SW अवरोधpoपूर्णांकs arrive as illegal inकाष्ठाions on HV */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			emulated = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	trace_kvm_निकास(निकास_nr, vcpu);
	guest_निकास_irqoff();

	local_irq_enable();

	run->निकास_reason = KVM_EXIT_UNKNOWN;
	run->पढ़ोy_क्रम_पूर्णांकerrupt_injection = 1;

	अगर (emulated != EMULATE_DONE) अणु
		r = kvmppc_resume_inst_load(vcpu, emulated, last_inst);
		जाओ out;
	पूर्ण

	चयन (निकास_nr) अणु
	हाल BOOKE_INTERRUPT_MACHINE_CHECK:
		prपूर्णांकk("MACHINE CHECK: %lx\n", mfspr(SPRN_MCSR));
		kvmppc_dump_vcpu(vcpu);
		/* For debugging, send invalid निकास reason to user space */
		run->hw.hardware_निकास_reason = ~1ULL << 32;
		run->hw.hardware_निकास_reason |= mfspr(SPRN_MCSR);
		r = RESUME_HOST;
		अवरोध;

	हाल BOOKE_INTERRUPT_EXTERNAL:
		kvmppc_account_निकास(vcpu, EXT_INTR_EXITS);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_DECREMENTER:
		kvmppc_account_निकास(vcpu, DEC_EXITS);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_WATCHDOG:
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_DOORBELL:
		kvmppc_account_निकास(vcpu, DBELL_EXITS);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_GUEST_DBELL_CRIT:
		kvmppc_account_निकास(vcpu, GDBELL_EXITS);

		/*
		 * We are here because there is a pending guest पूर्णांकerrupt
		 * which could not be delivered as MSR_CE or MSR_ME was not
		 * set.  Once we अवरोध from here we will retry delivery.
		 */
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_GUEST_DBELL:
		kvmppc_account_निकास(vcpu, GDBELL_EXITS);

		/*
		 * We are here because there is a pending guest पूर्णांकerrupt
		 * which could not be delivered as MSR_EE was not set.  Once
		 * we अवरोध from here we will retry delivery.
		 */
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_PERFORMANCE_MONITOR:
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_HV_PRIV:
		r = emulation_निकास(vcpu);
		अवरोध;

	हाल BOOKE_INTERRUPT_PROGRAM:
		अगर ((vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP) &&
			(last_inst == KVMPPC_INST_SW_BREAKPOINT)) अणु
			/*
			 * We are here because of an SW अवरोधpoपूर्णांक instr,
			 * so lets वापस to host to handle.
			 */
			r = kvmppc_handle_debug(vcpu);
			run->निकास_reason = KVM_EXIT_DEBUG;
			kvmppc_account_निकास(vcpu, DEBUG_EXITS);
			अवरोध;
		पूर्ण

		अगर (vcpu->arch.shared->msr & (MSR_PR | MSR_GS)) अणु
			/*
			 * Program traps generated by user-level software must
			 * be handled by the guest kernel.
			 *
			 * In GS mode, hypervisor privileged inकाष्ठाions trap
			 * on BOOKE_INTERRUPT_HV_PRIV, not here, so these are
			 * actual program पूर्णांकerrupts, handled by the guest.
			 */
			kvmppc_core_queue_program(vcpu, vcpu->arch.fault_esr);
			r = RESUME_GUEST;
			kvmppc_account_निकास(vcpu, USR_PR_INST);
			अवरोध;
		पूर्ण

		r = emulation_निकास(vcpu);
		अवरोध;

	हाल BOOKE_INTERRUPT_FP_UNAVAIL:
		kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_FP_UNAVAIL);
		kvmppc_account_निकास(vcpu, FP_UNAVAIL);
		r = RESUME_GUEST;
		अवरोध;

#अगर_घोषित CONFIG_SPE
	हाल BOOKE_INTERRUPT_SPE_UNAVAIL: अणु
		अगर (vcpu->arch.shared->msr & MSR_SPE)
			kvmppc_vcpu_enable_spe(vcpu);
		अन्यथा
			kvmppc_booke_queue_irqprio(vcpu,
						   BOOKE_IRQPRIO_SPE_UNAVAIL);
		r = RESUME_GUEST;
		अवरोध;
	पूर्ण

	हाल BOOKE_INTERRUPT_SPE_FP_DATA:
		kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_SPE_FP_DATA);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_SPE_FP_ROUND:
		kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_SPE_FP_ROUND);
		r = RESUME_GUEST;
		अवरोध;
#या_अगर defined(CONFIG_SPE_POSSIBLE)
	हाल BOOKE_INTERRUPT_SPE_UNAVAIL:
		/*
		 * Guest wants SPE, but host kernel करोesn't support it.  Send
		 * an "unimplemented operation" program check to the guest.
		 */
		kvmppc_core_queue_program(vcpu, ESR_PUO | ESR_SPV);
		r = RESUME_GUEST;
		अवरोध;

	/*
	 * These really should never happen without CONFIG_SPE,
	 * as we should never enable the real MSR[SPE] in the guest.
	 */
	हाल BOOKE_INTERRUPT_SPE_FP_DATA:
	हाल BOOKE_INTERRUPT_SPE_FP_ROUND:
		prपूर्णांकk(KERN_CRIT "%s: unexpected SPE interrupt %u at %08lx\n",
		       __func__, निकास_nr, vcpu->arch.regs.nip);
		run->hw.hardware_निकास_reason = निकास_nr;
		r = RESUME_HOST;
		अवरोध;
#पूर्ण_अगर /* CONFIG_SPE_POSSIBLE */

/*
 * On cores with Vector category, KVM is loaded only अगर CONFIG_ALTIVEC,
 * see kvmppc_core_check_processor_compat().
 */
#अगर_घोषित CONFIG_ALTIVEC
	हाल BOOKE_INTERRUPT_ALTIVEC_UNAVAIL:
		kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ALTIVEC_UNAVAIL);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_ALTIVEC_ASSIST:
		kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ALTIVEC_ASSIST);
		r = RESUME_GUEST;
		अवरोध;
#पूर्ण_अगर

	हाल BOOKE_INTERRUPT_DATA_STORAGE:
		kvmppc_core_queue_data_storage(vcpu, vcpu->arch.fault_dear,
		                               vcpu->arch.fault_esr);
		kvmppc_account_निकास(vcpu, DSI_EXITS);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_INST_STORAGE:
		kvmppc_core_queue_inst_storage(vcpu, vcpu->arch.fault_esr);
		kvmppc_account_निकास(vcpu, ISI_EXITS);
		r = RESUME_GUEST;
		अवरोध;

	हाल BOOKE_INTERRUPT_ALIGNMENT:
		kvmppc_core_queue_alignment(vcpu, vcpu->arch.fault_dear,
		                            vcpu->arch.fault_esr);
		r = RESUME_GUEST;
		अवरोध;

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	हाल BOOKE_INTERRUPT_HV_SYSCALL:
		अगर (!(vcpu->arch.shared->msr & MSR_PR)) अणु
			kvmppc_set_gpr(vcpu, 3, kvmppc_kvm_pv(vcpu));
		पूर्ण अन्यथा अणु
			/*
			 * hcall from guest userspace -- send privileged
			 * inकाष्ठाion program check.
			 */
			kvmppc_core_queue_program(vcpu, ESR_PPR);
		पूर्ण

		r = RESUME_GUEST;
		अवरोध;
#अन्यथा
	हाल BOOKE_INTERRUPT_SYSCALL:
		अगर (!(vcpu->arch.shared->msr & MSR_PR) &&
		    (((u32)kvmppc_get_gpr(vcpu, 0)) == KVM_SC_MAGIC_R0)) अणु
			/* KVM PV hypercalls */
			kvmppc_set_gpr(vcpu, 3, kvmppc_kvm_pv(vcpu));
			r = RESUME_GUEST;
		पूर्ण अन्यथा अणु
			/* Guest syscalls */
			kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_SYSCALL);
		पूर्ण
		kvmppc_account_निकास(vcpu, SYSCALL_EXITS);
		r = RESUME_GUEST;
		अवरोध;
#पूर्ण_अगर

	हाल BOOKE_INTERRUPT_DTLB_MISS: अणु
		अचिन्हित दीर्घ eaddr = vcpu->arch.fault_dear;
		पूर्णांक gtlb_index;
		gpa_t gpaddr;
		gfn_t gfn;

#अगर_घोषित CONFIG_KVM_E500V2
		अगर (!(vcpu->arch.shared->msr & MSR_PR) &&
		    (eaddr & PAGE_MASK) == vcpu->arch.magic_page_ea) अणु
			kvmppc_map_magic(vcpu);
			kvmppc_account_निकास(vcpu, DTLB_VIRT_MISS_EXITS);
			r = RESUME_GUEST;

			अवरोध;
		पूर्ण
#पूर्ण_अगर

		/* Check the guest TLB. */
		gtlb_index = kvmppc_mmu_dtlb_index(vcpu, eaddr);
		अगर (gtlb_index < 0) अणु
			/* The guest didn't have a mapping क्रम it. */
			kvmppc_core_queue_dtlb_miss(vcpu,
			                            vcpu->arch.fault_dear,
			                            vcpu->arch.fault_esr);
			kvmppc_mmu_dtlb_miss(vcpu);
			kvmppc_account_निकास(vcpu, DTLB_REAL_MISS_EXITS);
			r = RESUME_GUEST;
			अवरोध;
		पूर्ण

		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

		gpaddr = kvmppc_mmu_xlate(vcpu, gtlb_index, eaddr);
		gfn = gpaddr >> PAGE_SHIFT;

		अगर (kvm_is_visible_gfn(vcpu->kvm, gfn)) अणु
			/* The guest TLB had a mapping, but the shaकरोw TLB
			 * didn't, and it is RAM. This could be because:
			 * a) the entry is mapping the host kernel, or
			 * b) the guest used a large mapping which we're faking
			 * Either way, we need to satisfy the fault without
			 * invoking the guest. */
			kvmppc_mmu_map(vcpu, eaddr, gpaddr, gtlb_index);
			kvmppc_account_निकास(vcpu, DTLB_VIRT_MISS_EXITS);
			r = RESUME_GUEST;
		पूर्ण अन्यथा अणु
			/* Guest has mapped and accessed a page which is not
			 * actually RAM. */
			vcpu->arch.paddr_accessed = gpaddr;
			vcpu->arch.vaddr_accessed = eaddr;
			r = kvmppc_emulate_mmio(vcpu);
			kvmppc_account_निकास(vcpu, MMIO_EXITS);
		पूर्ण

		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण

	हाल BOOKE_INTERRUPT_ITLB_MISS: अणु
		अचिन्हित दीर्घ eaddr = vcpu->arch.regs.nip;
		gpa_t gpaddr;
		gfn_t gfn;
		पूर्णांक gtlb_index;

		r = RESUME_GUEST;

		/* Check the guest TLB. */
		gtlb_index = kvmppc_mmu_itlb_index(vcpu, eaddr);
		अगर (gtlb_index < 0) अणु
			/* The guest didn't have a mapping क्रम it. */
			kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_ITLB_MISS);
			kvmppc_mmu_itlb_miss(vcpu);
			kvmppc_account_निकास(vcpu, ITLB_REAL_MISS_EXITS);
			अवरोध;
		पूर्ण

		kvmppc_account_निकास(vcpu, ITLB_VIRT_MISS_EXITS);

		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

		gpaddr = kvmppc_mmu_xlate(vcpu, gtlb_index, eaddr);
		gfn = gpaddr >> PAGE_SHIFT;

		अगर (kvm_is_visible_gfn(vcpu->kvm, gfn)) अणु
			/* The guest TLB had a mapping, but the shaकरोw TLB
			 * didn't. This could be because:
			 * a) the entry is mapping the host kernel, or
			 * b) the guest used a large mapping which we're faking
			 * Either way, we need to satisfy the fault without
			 * invoking the guest. */
			kvmppc_mmu_map(vcpu, eaddr, gpaddr, gtlb_index);
		पूर्ण अन्यथा अणु
			/* Guest mapped and leaped at non-RAM! */
			kvmppc_booke_queue_irqprio(vcpu, BOOKE_IRQPRIO_MACHINE_CHECK);
		पूर्ण

		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण

	हाल BOOKE_INTERRUPT_DEBUG: अणु
		r = kvmppc_handle_debug(vcpu);
		अगर (r == RESUME_HOST)
			run->निकास_reason = KVM_EXIT_DEBUG;
		kvmppc_account_निकास(vcpu, DEBUG_EXITS);
		अवरोध;
	पूर्ण

	शेष:
		prपूर्णांकk(KERN_EMERG "exit_nr %d\n", निकास_nr);
		BUG();
	पूर्ण

out:
	/*
	 * To aव्योम clobbering निकास_reason, only check क्रम संकेतs अगर we
	 * aren't alपढ़ोy निकासing to userspace क्रम some other reason.
	 */
	अगर (!(r & RESUME_HOST)) अणु
		s = kvmppc_prepare_to_enter(vcpu);
		अगर (s <= 0)
			r = (s << 2) | RESUME_HOST | (r & RESUME_FLAG_NV);
		अन्यथा अणु
			/* पूर्णांकerrupts now hard-disabled */
			kvmppc_fix_ee_beक्रमe_entry();
			kvmppc_load_guest_fp(vcpu);
			kvmppc_load_guest_altivec(vcpu);
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम kvmppc_set_tsr(काष्ठा kvm_vcpu *vcpu, u32 new_tsr)
अणु
	u32 old_tsr = vcpu->arch.tsr;

	vcpu->arch.tsr = new_tsr;

	अगर ((old_tsr ^ vcpu->arch.tsr) & (TSR_ENW | TSR_WIS))
		arm_next_watchकरोg(vcpu);

	update_समयr_पूर्णांकs(vcpu);
पूर्ण

पूर्णांक kvmppc_subarch_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	/* setup watchकरोg समयr once */
	spin_lock_init(&vcpu->arch.wdt_lock);
	समयr_setup(&vcpu->arch.wdt_समयr, kvmppc_watchकरोg_func, 0);

	/*
	 * Clear DBSR.MRR to aव्योम guest debug पूर्णांकerrupt as
	 * this is of host पूर्णांकerest
	 */
	mtspr(SPRN_DBSR, DBSR_MRR);
	वापस 0;
पूर्ण

व्योम kvmppc_subarch_vcpu_uninit(काष्ठा kvm_vcpu *vcpu)
अणु
	del_समयr_sync(&vcpu->arch.wdt_समयr);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	vcpu_load(vcpu);

	regs->pc = vcpu->arch.regs.nip;
	regs->cr = kvmppc_get_cr(vcpu);
	regs->ctr = vcpu->arch.regs.ctr;
	regs->lr = vcpu->arch.regs.link;
	regs->xer = kvmppc_get_xer(vcpu);
	regs->msr = vcpu->arch.shared->msr;
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

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	पूर्णांक i;

	vcpu_load(vcpu);

	vcpu->arch.regs.nip = regs->pc;
	kvmppc_set_cr(vcpu, regs->cr);
	vcpu->arch.regs.ctr = regs->ctr;
	vcpu->arch.regs.link = regs->lr;
	kvmppc_set_xer(vcpu, regs->xer);
	kvmppc_set_msr(vcpu, regs->msr);
	kvmppc_set_srr0(vcpu, regs->srr0);
	kvmppc_set_srr1(vcpu, regs->srr1);
	kvmppc_set_pid(vcpu, regs->pid);
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

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

अटल व्योम get_sregs_base(काष्ठा kvm_vcpu *vcpu,
                           काष्ठा kvm_sregs *sregs)
अणु
	u64 tb = get_tb();

	sregs->u.e.features |= KVM_SREGS_E_BASE;

	sregs->u.e.csrr0 = vcpu->arch.csrr0;
	sregs->u.e.csrr1 = vcpu->arch.csrr1;
	sregs->u.e.mcsr = vcpu->arch.mcsr;
	sregs->u.e.esr = kvmppc_get_esr(vcpu);
	sregs->u.e.dear = kvmppc_get_dar(vcpu);
	sregs->u.e.tsr = vcpu->arch.tsr;
	sregs->u.e.tcr = vcpu->arch.tcr;
	sregs->u.e.dec = kvmppc_get_dec(vcpu, tb);
	sregs->u.e.tb = tb;
	sregs->u.e.vrsave = vcpu->arch.vrsave;
पूर्ण

अटल पूर्णांक set_sregs_base(काष्ठा kvm_vcpu *vcpu,
                          काष्ठा kvm_sregs *sregs)
अणु
	अगर (!(sregs->u.e.features & KVM_SREGS_E_BASE))
		वापस 0;

	vcpu->arch.csrr0 = sregs->u.e.csrr0;
	vcpu->arch.csrr1 = sregs->u.e.csrr1;
	vcpu->arch.mcsr = sregs->u.e.mcsr;
	kvmppc_set_esr(vcpu, sregs->u.e.esr);
	kvmppc_set_dar(vcpu, sregs->u.e.dear);
	vcpu->arch.vrsave = sregs->u.e.vrsave;
	kvmppc_set_tcr(vcpu, sregs->u.e.tcr);

	अगर (sregs->u.e.update_special & KVM_SREGS_E_UPDATE_DEC) अणु
		vcpu->arch.dec = sregs->u.e.dec;
		kvmppc_emulate_dec(vcpu);
	पूर्ण

	अगर (sregs->u.e.update_special & KVM_SREGS_E_UPDATE_TSR)
		kvmppc_set_tsr(vcpu, sregs->u.e.tsr);

	वापस 0;
पूर्ण

अटल व्योम get_sregs_arch206(काष्ठा kvm_vcpu *vcpu,
                              काष्ठा kvm_sregs *sregs)
अणु
	sregs->u.e.features |= KVM_SREGS_E_ARCH206;

	sregs->u.e.pir = vcpu->vcpu_id;
	sregs->u.e.mcsrr0 = vcpu->arch.mcsrr0;
	sregs->u.e.mcsrr1 = vcpu->arch.mcsrr1;
	sregs->u.e.decar = vcpu->arch.decar;
	sregs->u.e.ivpr = vcpu->arch.ivpr;
पूर्ण

अटल पूर्णांक set_sregs_arch206(काष्ठा kvm_vcpu *vcpu,
                             काष्ठा kvm_sregs *sregs)
अणु
	अगर (!(sregs->u.e.features & KVM_SREGS_E_ARCH206))
		वापस 0;

	अगर (sregs->u.e.pir != vcpu->vcpu_id)
		वापस -EINVAL;

	vcpu->arch.mcsrr0 = sregs->u.e.mcsrr0;
	vcpu->arch.mcsrr1 = sregs->u.e.mcsrr1;
	vcpu->arch.decar = sregs->u.e.decar;
	vcpu->arch.ivpr = sregs->u.e.ivpr;

	वापस 0;
पूर्ण

पूर्णांक kvmppc_get_sregs_ivor(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	sregs->u.e.features |= KVM_SREGS_E_IVOR;

	sregs->u.e.ivor_low[0] = vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL];
	sregs->u.e.ivor_low[1] = vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK];
	sregs->u.e.ivor_low[2] = vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE];
	sregs->u.e.ivor_low[3] = vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE];
	sregs->u.e.ivor_low[4] = vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL];
	sregs->u.e.ivor_low[5] = vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT];
	sregs->u.e.ivor_low[6] = vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM];
	sregs->u.e.ivor_low[7] = vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL];
	sregs->u.e.ivor_low[8] = vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL];
	sregs->u.e.ivor_low[9] = vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL];
	sregs->u.e.ivor_low[10] = vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER];
	sregs->u.e.ivor_low[11] = vcpu->arch.ivor[BOOKE_IRQPRIO_FIT];
	sregs->u.e.ivor_low[12] = vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG];
	sregs->u.e.ivor_low[13] = vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS];
	sregs->u.e.ivor_low[14] = vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS];
	sregs->u.e.ivor_low[15] = vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG];
	वापस 0;
पूर्ण

पूर्णांक kvmppc_set_sregs_ivor(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	अगर (!(sregs->u.e.features & KVM_SREGS_E_IVOR))
		वापस 0;

	vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL] = sregs->u.e.ivor_low[0];
	vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK] = sregs->u.e.ivor_low[1];
	vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE] = sregs->u.e.ivor_low[2];
	vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE] = sregs->u.e.ivor_low[3];
	vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL] = sregs->u.e.ivor_low[4];
	vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT] = sregs->u.e.ivor_low[5];
	vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM] = sregs->u.e.ivor_low[6];
	vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL] = sregs->u.e.ivor_low[7];
	vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL] = sregs->u.e.ivor_low[8];
	vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL] = sregs->u.e.ivor_low[9];
	vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER] = sregs->u.e.ivor_low[10];
	vcpu->arch.ivor[BOOKE_IRQPRIO_FIT] = sregs->u.e.ivor_low[11];
	vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG] = sregs->u.e.ivor_low[12];
	vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS] = sregs->u.e.ivor_low[13];
	vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS] = sregs->u.e.ivor_low[14];
	vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG] = sregs->u.e.ivor_low[15];

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
                                  काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret;

	vcpu_load(vcpu);

	sregs->pvr = vcpu->arch.pvr;

	get_sregs_base(vcpu, sregs);
	get_sregs_arch206(vcpu, sregs);
	ret = vcpu->kvm->arch.kvm_ops->get_sregs(vcpu, sregs);

	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
                                  काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret = -EINVAL;

	vcpu_load(vcpu);
	अगर (vcpu->arch.pvr != sregs->pvr)
		जाओ out;

	ret = set_sregs_base(vcpu, sregs);
	अगर (ret < 0)
		जाओ out;

	ret = set_sregs_arch206(vcpu, sregs);
	अगर (ret < 0)
		जाओ out;

	ret = vcpu->kvm->arch.kvm_ops->set_sregs(vcpu, sregs);

out:
	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvmppc_get_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id,
			जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_IAC1:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac1);
		अवरोध;
	हाल KVM_REG_PPC_IAC2:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac2);
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल KVM_REG_PPC_IAC3:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac3);
		अवरोध;
	हाल KVM_REG_PPC_IAC4:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac4);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_PPC_DAC1:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.dac1);
		अवरोध;
	हाल KVM_REG_PPC_DAC2:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.dac2);
		अवरोध;
	हाल KVM_REG_PPC_EPR: अणु
		u32 epr = kvmppc_get_epr(vcpu);
		*val = get_reg_val(id, epr);
		अवरोध;
	पूर्ण
#अगर defined(CONFIG_64BIT)
	हाल KVM_REG_PPC_EPCR:
		*val = get_reg_val(id, vcpu->arch.epcr);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_PPC_TCR:
		*val = get_reg_val(id, vcpu->arch.tcr);
		अवरोध;
	हाल KVM_REG_PPC_TSR:
		*val = get_reg_val(id, vcpu->arch.tsr);
		अवरोध;
	हाल KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		अवरोध;
	हाल KVM_REG_PPC_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave);
		अवरोध;
	शेष:
		r = vcpu->kvm->arch.kvm_ops->get_one_reg(vcpu, id, val);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_set_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id,
			जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_IAC1:
		vcpu->arch.dbg_reg.iac1 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_IAC2:
		vcpu->arch.dbg_reg.iac2 = set_reg_val(id, *val);
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल KVM_REG_PPC_IAC3:
		vcpu->arch.dbg_reg.iac3 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_IAC4:
		vcpu->arch.dbg_reg.iac4 = set_reg_val(id, *val);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_REG_PPC_DAC1:
		vcpu->arch.dbg_reg.dac1 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_DAC2:
		vcpu->arch.dbg_reg.dac2 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_EPR: अणु
		u32 new_epr = set_reg_val(id, *val);
		kvmppc_set_epr(vcpu, new_epr);
		अवरोध;
	पूर्ण
#अगर defined(CONFIG_64BIT)
	हाल KVM_REG_PPC_EPCR: अणु
		u32 new_epcr = set_reg_val(id, *val);
		kvmppc_set_epcr(vcpu, new_epcr);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_REG_PPC_OR_TSR: अणु
		u32 tsr_bits = set_reg_val(id, *val);
		kvmppc_set_tsr_bits(vcpu, tsr_bits);
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_CLEAR_TSR: अणु
		u32 tsr_bits = set_reg_val(id, *val);
		kvmppc_clr_tsr_bits(vcpu, tsr_bits);
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TSR: अणु
		u32 tsr = set_reg_val(id, *val);
		kvmppc_set_tsr(vcpu, tsr);
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TCR: अणु
		u32 tcr = set_reg_val(id, *val);
		kvmppc_set_tcr(vcpu, tcr);
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_VRSAVE:
		vcpu->arch.vrsave = set_reg_val(id, *val);
		अवरोध;
	शेष:
		r = vcpu->kvm->arch.kvm_ops->set_one_reg(vcpu, id, val);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
                                  काष्ठा kvm_translation *tr)
अणु
	पूर्णांक r;

	vcpu_load(vcpu);
	r = kvmppc_core_vcpu_translate(vcpu, tr);
	vcpu_put(vcpu);
	वापस r;
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु

पूर्ण

पूर्णांक kvm_vm_ioctl_get_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

व्योम kvmppc_core_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
पूर्ण

पूर्णांक kvmppc_core_prepare_memory_region(काष्ठा kvm *kvm,
				      काष्ठा kvm_memory_slot *memslot,
				      स्थिर काष्ठा kvm_userspace_memory_region *mem,
				      क्रमागत kvm_mr_change change)
अणु
	वापस 0;
पूर्ण

व्योम kvmppc_core_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				स्थिर काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
पूर्ण

व्योम kvmppc_core_flush_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु
पूर्ण

व्योम kvmppc_set_epcr(काष्ठा kvm_vcpu *vcpu, u32 new_epcr)
अणु
#अगर defined(CONFIG_64BIT)
	vcpu->arch.epcr = new_epcr;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	vcpu->arch.shaकरोw_epcr &= ~SPRN_EPCR_GICM;
	अगर (vcpu->arch.epcr  & SPRN_EPCR_ICM)
		vcpu->arch.shaकरोw_epcr |= SPRN_EPCR_GICM;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

व्योम kvmppc_set_tcr(काष्ठा kvm_vcpu *vcpu, u32 new_tcr)
अणु
	vcpu->arch.tcr = new_tcr;
	arm_next_watchकरोg(vcpu);
	update_समयr_पूर्णांकs(vcpu);
पूर्ण

व्योम kvmppc_set_tsr_bits(काष्ठा kvm_vcpu *vcpu, u32 tsr_bits)
अणु
	set_bits(tsr_bits, &vcpu->arch.tsr);
	smp_wmb();
	kvm_make_request(KVM_REQ_PENDING_TIMER, vcpu);
	kvm_vcpu_kick(vcpu);
पूर्ण

व्योम kvmppc_clr_tsr_bits(काष्ठा kvm_vcpu *vcpu, u32 tsr_bits)
अणु
	clear_bits(tsr_bits, &vcpu->arch.tsr);

	/*
	 * We may have stopped the watchकरोg due to
	 * being stuck on final expiration.
	 */
	अगर (tsr_bits & (TSR_ENW | TSR_WIS))
		arm_next_watchकरोg(vcpu);

	update_समयr_पूर्णांकs(vcpu);
पूर्ण

व्योम kvmppc_decrementer_func(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.tcr & TCR_ARE) अणु
		vcpu->arch.dec = vcpu->arch.decar;
		kvmppc_emulate_dec(vcpu);
	पूर्ण

	kvmppc_set_tsr_bits(vcpu, TSR_DIS);
पूर्ण

अटल पूर्णांक kvmppc_booke_add_अवरोधpoपूर्णांक(काष्ठा debug_reg *dbg_reg,
				       uपूर्णांक64_t addr, पूर्णांक index)
अणु
	चयन (index) अणु
	हाल 0:
		dbg_reg->dbcr0 |= DBCR0_IAC1;
		dbg_reg->iac1 = addr;
		अवरोध;
	हाल 1:
		dbg_reg->dbcr0 |= DBCR0_IAC2;
		dbg_reg->iac2 = addr;
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल 2:
		dbg_reg->dbcr0 |= DBCR0_IAC3;
		dbg_reg->iac3 = addr;
		अवरोध;
	हाल 3:
		dbg_reg->dbcr0 |= DBCR0_IAC4;
		dbg_reg->iac4 = addr;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	dbg_reg->dbcr0 |= DBCR0_IDM;
	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_booke_add_watchpoपूर्णांक(काष्ठा debug_reg *dbg_reg, uपूर्णांक64_t addr,
				       पूर्णांक type, पूर्णांक index)
अणु
	चयन (index) अणु
	हाल 0:
		अगर (type & KVMPPC_DEBUG_WATCH_READ)
			dbg_reg->dbcr0 |= DBCR0_DAC1R;
		अगर (type & KVMPPC_DEBUG_WATCH_WRITE)
			dbg_reg->dbcr0 |= DBCR0_DAC1W;
		dbg_reg->dac1 = addr;
		अवरोध;
	हाल 1:
		अगर (type & KVMPPC_DEBUG_WATCH_READ)
			dbg_reg->dbcr0 |= DBCR0_DAC2R;
		अगर (type & KVMPPC_DEBUG_WATCH_WRITE)
			dbg_reg->dbcr0 |= DBCR0_DAC2W;
		dbg_reg->dac2 = addr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dbg_reg->dbcr0 |= DBCR0_IDM;
	वापस 0;
पूर्ण
व्योम kvm_guest_protect_msr(काष्ठा kvm_vcpu *vcpu, uदीर्घ prot_biपंचांगap, bool set)
अणु
	/* XXX: Add similar MSR protection क्रम BookE-PR */
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	BUG_ON(prot_biपंचांगap & ~(MSRP_UCLEP | MSRP_DEP | MSRP_PMMP));
	अगर (set) अणु
		अगर (prot_biपंचांगap & MSR_UCLE)
			vcpu->arch.shaकरोw_msrp |= MSRP_UCLEP;
		अगर (prot_biपंचांगap & MSR_DE)
			vcpu->arch.shaकरोw_msrp |= MSRP_DEP;
		अगर (prot_biपंचांगap & MSR_PMM)
			vcpu->arch.shaकरोw_msrp |= MSRP_PMMP;
	पूर्ण अन्यथा अणु
		अगर (prot_biपंचांगap & MSR_UCLE)
			vcpu->arch.shaकरोw_msrp &= ~MSRP_UCLEP;
		अगर (prot_biपंचांगap & MSR_DE)
			vcpu->arch.shaकरोw_msrp &= ~MSRP_DEP;
		अगर (prot_biपंचांगap & MSR_PMM)
			vcpu->arch.shaकरोw_msrp &= ~MSRP_PMMP;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक kvmppc_xlate(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr, क्रमागत xlate_instdata xlid,
		 क्रमागत xlate_पढ़ोग_लिखो xlrw, काष्ठा kvmppc_pte *pte)
अणु
	पूर्णांक gtlb_index;
	gpa_t gpaddr;

#अगर_घोषित CONFIG_KVM_E500V2
	अगर (!(vcpu->arch.shared->msr & MSR_PR) &&
	    (eaddr & PAGE_MASK) == vcpu->arch.magic_page_ea) अणु
		pte->eaddr = eaddr;
		pte->raddr = (vcpu->arch.magic_page_pa & PAGE_MASK) |
			     (eaddr & ~PAGE_MASK);
		pte->vpage = eaddr >> PAGE_SHIFT;
		pte->may_पढ़ो = true;
		pte->may_ग_लिखो = true;
		pte->may_execute = true;

		वापस 0;
	पूर्ण
#पूर्ण_अगर

	/* Check the guest TLB. */
	चयन (xlid) अणु
	हाल XLATE_INST:
		gtlb_index = kvmppc_mmu_itlb_index(vcpu, eaddr);
		अवरोध;
	हाल XLATE_DATA:
		gtlb_index = kvmppc_mmu_dtlb_index(vcpu, eaddr);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* Do we have a TLB entry at all? */
	अगर (gtlb_index < 0)
		वापस -ENOENT;

	gpaddr = kvmppc_mmu_xlate(vcpu, gtlb_index, eaddr);

	pte->eaddr = eaddr;
	pte->raddr = (gpaddr & PAGE_MASK) | (eaddr & ~PAGE_MASK);
	pte->vpage = eaddr >> PAGE_SHIFT;

	/* XXX पढ़ो permissions from the guest TLB */
	pte->may_पढ़ो = true;
	pte->may_ग_लिखो = true;
	pte->may_execute = true;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					 काष्ठा kvm_guest_debug *dbg)
अणु
	काष्ठा debug_reg *dbg_reg;
	पूर्णांक n, b = 0, w = 0;
	पूर्णांक ret = 0;

	vcpu_load(vcpu);

	अगर (!(dbg->control & KVM_GUESTDBG_ENABLE)) अणु
		vcpu->arch.dbg_reg.dbcr0 = 0;
		vcpu->guest_debug = 0;
		kvm_guest_protect_msr(vcpu, MSR_DE, false);
		जाओ out;
	पूर्ण

	kvm_guest_protect_msr(vcpu, MSR_DE, true);
	vcpu->guest_debug = dbg->control;
	vcpu->arch.dbg_reg.dbcr0 = 0;

	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		vcpu->arch.dbg_reg.dbcr0 |= DBCR0_IDM | DBCR0_IC;

	/* Code below handles only HW अवरोधpoपूर्णांकs */
	dbg_reg = &(vcpu->arch.dbg_reg);

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	/*
	 * On BookE-HV (e500mc) the guest is always executed with MSR.GS=1
	 * DBCR1 and DBCR2 are set to trigger debug events when MSR.PR is 0
	 */
	dbg_reg->dbcr1 = 0;
	dbg_reg->dbcr2 = 0;
#अन्यथा
	/*
	 * On BookE-PR (e500v2) the guest is always executed with MSR.PR=1
	 * We set DBCR1 and DBCR2 to only trigger debug events when MSR.PR
	 * is set.
	 */
	dbg_reg->dbcr1 = DBCR1_IAC1US | DBCR1_IAC2US | DBCR1_IAC3US |
			  DBCR1_IAC4US;
	dbg_reg->dbcr2 = DBCR2_DAC1US | DBCR2_DAC2US;
#पूर्ण_अगर

	अगर (!(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP))
		जाओ out;

	ret = -EINVAL;
	क्रम (n = 0; n < (KVMPPC_BOOKE_IAC_NUM + KVMPPC_BOOKE_DAC_NUM); n++) अणु
		uपूर्णांक64_t addr = dbg->arch.bp[n].addr;
		uपूर्णांक32_t type = dbg->arch.bp[n].type;

		अगर (type == KVMPPC_DEBUG_NONE)
			जारी;

		अगर (type & ~(KVMPPC_DEBUG_WATCH_READ |
			     KVMPPC_DEBUG_WATCH_WRITE |
			     KVMPPC_DEBUG_BREAKPOINT))
			जाओ out;

		अगर (type & KVMPPC_DEBUG_BREAKPOINT) अणु
			/* Setting H/W अवरोधpoपूर्णांक */
			अगर (kvmppc_booke_add_अवरोधpoपूर्णांक(dbg_reg, addr, b++))
				जाओ out;
		पूर्ण अन्यथा अणु
			/* Setting H/W watchpoपूर्णांक */
			अगर (kvmppc_booke_add_watchpoपूर्णांक(dbg_reg, addr,
							type, w++))
				जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	vcpu_put(vcpu);
	वापस ret;
पूर्ण

व्योम kvmppc_booke_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	vcpu->cpu = smp_processor_id();
	current->thपढ़ो.kvm_vcpu = vcpu;
पूर्ण

व्योम kvmppc_booke_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	current->thपढ़ो.kvm_vcpu = शून्य;
	vcpu->cpu = -1;

	/* Clear pending debug event in DBSR */
	kvmppc_clear_dbsr();
पूर्ण

पूर्णांक kvmppc_core_init_vm(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.kvm_ops->init_vm(kvm);
पूर्ण

पूर्णांक kvmppc_core_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	पूर्णांक r;

	r = vcpu->kvm->arch.kvm_ops->vcpu_create(vcpu);
	अगर (r)
		वापस r;

	/* Initial guest state: 16MB mapping 0 -> 0, PC = 0, MSR = 0, R1 = 16MB */
	vcpu->arch.regs.nip = 0;
	vcpu->arch.shared->pir = vcpu->vcpu_id;
	kvmppc_set_gpr(vcpu, 1, (16<<20) - 8); /* -8 क्रम the callee-save LR slot */
	kvmppc_set_msr(vcpu, 0);

#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	vcpu->arch.shaकरोw_msr = MSR_USER | MSR_IS | MSR_DS;
	vcpu->arch.shaकरोw_pid = 1;
	vcpu->arch.shared->msr = 0;
#पूर्ण_अगर

	/* Eye-catching numbers so we know अगर the guest takes an पूर्णांकerrupt
	 * beक्रमe it's programmed its own IVPR/IVORs. */
	vcpu->arch.ivpr = 0x55550000;
	क्रम (i = 0; i < BOOKE_IRQPRIO_MAX; i++)
		vcpu->arch.ivor[i] = 0x7700 | i * 4;

	kvmppc_init_timing_stats(vcpu);

	r = kvmppc_core_vcpu_setup(vcpu);
	अगर (r)
		vcpu->kvm->arch.kvm_ops->vcpu_मुक्त(vcpu);
	kvmppc_sanity_check(vcpu);
	वापस r;
पूर्ण

व्योम kvmppc_core_vcpu_मुक्त(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_मुक्त(vcpu);
पूर्ण

व्योम kvmppc_core_destroy_vm(काष्ठा kvm *kvm)
अणु
	kvm->arch.kvm_ops->destroy_vm(kvm);
पूर्ण

व्योम kvmppc_core_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_load(vcpu, cpu);
पूर्ण

व्योम kvmppc_core_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->kvm->arch.kvm_ops->vcpu_put(vcpu);
पूर्ण

पूर्णांक __init kvmppc_booke_init(व्योम)
अणु
#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	अचिन्हित दीर्घ ivor[16];
	अचिन्हित दीर्घ *handler = kvmppc_booke_handler_addr;
	अचिन्हित दीर्घ max_ivor = 0;
	अचिन्हित दीर्घ handler_len;
	पूर्णांक i;

	/* We install our own exception handlers by hijacking IVPR. IVPR must
	 * be 16-bit aligned, so we need a 64KB allocation. */
	kvmppc_booke_handlers = __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
	                                         VCPU_SIZE_ORDER);
	अगर (!kvmppc_booke_handlers)
		वापस -ENOMEM;

	/* XXX make sure our handlers are smaller than Linux's */

	/* Copy our पूर्णांकerrupt handlers to match host IVORs. That way we करोn't
	 * have to swap the IVORs on every guest/host transition. */
	ivor[0] = mfspr(SPRN_IVOR0);
	ivor[1] = mfspr(SPRN_IVOR1);
	ivor[2] = mfspr(SPRN_IVOR2);
	ivor[3] = mfspr(SPRN_IVOR3);
	ivor[4] = mfspr(SPRN_IVOR4);
	ivor[5] = mfspr(SPRN_IVOR5);
	ivor[6] = mfspr(SPRN_IVOR6);
	ivor[7] = mfspr(SPRN_IVOR7);
	ivor[8] = mfspr(SPRN_IVOR8);
	ivor[9] = mfspr(SPRN_IVOR9);
	ivor[10] = mfspr(SPRN_IVOR10);
	ivor[11] = mfspr(SPRN_IVOR11);
	ivor[12] = mfspr(SPRN_IVOR12);
	ivor[13] = mfspr(SPRN_IVOR13);
	ivor[14] = mfspr(SPRN_IVOR14);
	ivor[15] = mfspr(SPRN_IVOR15);

	क्रम (i = 0; i < 16; i++) अणु
		अगर (ivor[i] > max_ivor)
			max_ivor = i;

		handler_len = handler[i + 1] - handler[i];
		स_नकल((व्योम *)kvmppc_booke_handlers + ivor[i],
		       (व्योम *)handler[i], handler_len);
	पूर्ण

	handler_len = handler[max_ivor + 1] - handler[max_ivor];
	flush_icache_range(kvmppc_booke_handlers, kvmppc_booke_handlers +
			   ivor[max_ivor] + handler_len);
#पूर्ण_अगर /* !BOOKE_HV */
	वापस 0;
पूर्ण

व्योम __निकास kvmppc_booke_निकास(व्योम)
अणु
	मुक्त_pages(kvmppc_booke_handlers, VCPU_SIZE_ORDER);
	kvm_निकास();
पूर्ण
