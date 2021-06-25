<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009. SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *    Alexander Graf <agraf@suse.de>
 *    Kevin Wolf <mail@kevin-wolf.de>
 *    Paul Mackerras <paulus@samba.org>
 *
 * Description:
 * Functions relating to running KVM on Book 3S processors where
 * we करोn't have access to hypervisor mode, and we run the guest
 * in problem state (user mode).
 *
 * This file is derived from arch/घातerpc/kvm/44x.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/पंचांग.h>

#समावेश "book3s.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_pr.h"

/* #घोषणा EXIT_DEBUG */
/* #घोषणा DEBUG_EXT */

अटल पूर्णांक kvmppc_handle_ext(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक निकास_nr,
			     uदीर्घ msr);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल पूर्णांक kvmppc_handle_fac(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac);
#पूर्ण_अगर

/* Some compatibility defines */
#अगर_घोषित CONFIG_PPC_BOOK3S_32
#घोषणा MSR_USER32 MSR_USER
#घोषणा MSR_USER64 MSR_USER
#घोषणा HW_PAGE_SIZE PAGE_SIZE
#घोषणा HPTE_R_M   _PAGE_COHERENT
#पूर्ण_अगर

अटल bool kvmppc_is_split_real(काष्ठा kvm_vcpu *vcpu)
अणु
	uदीर्घ msr = kvmppc_get_msr(vcpu);
	वापस (msr & (MSR_IR|MSR_DR)) == MSR_DR;
पूर्ण

अटल व्योम kvmppc_fixup_split_real(काष्ठा kvm_vcpu *vcpu)
अणु
	uदीर्घ msr = kvmppc_get_msr(vcpu);
	uदीर्घ pc = kvmppc_get_pc(vcpu);

	/* We are in DR only split real mode */
	अगर ((msr & (MSR_IR|MSR_DR)) != MSR_DR)
		वापस;

	/* We have not fixed up the guest alपढ़ोy */
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_SPLIT_HACK)
		वापस;

	/* The code is in fixupable address space */
	अगर (pc & SPLIT_HACK_MASK)
		वापस;

	vcpu->arch.hflags |= BOOK3S_HFLAG_SPLIT_HACK;
	kvmppc_set_pc(vcpu, pc | SPLIT_HACK_OFFS);
पूर्ण

अटल व्योम kvmppc_unfixup_split_real(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_SPLIT_HACK) अणु
		uदीर्घ pc = kvmppc_get_pc(vcpu);
		uदीर्घ lr = kvmppc_get_lr(vcpu);
		अगर ((pc & SPLIT_HACK_MASK) == SPLIT_HACK_OFFS)
			kvmppc_set_pc(vcpu, pc & ~SPLIT_HACK_MASK);
		अगर ((lr & SPLIT_HACK_MASK) == SPLIT_HACK_OFFS)
			kvmppc_set_lr(vcpu, lr & ~SPLIT_HACK_MASK);
		vcpu->arch.hflags &= ~BOOK3S_HFLAG_SPLIT_HACK;
	पूर्ण
पूर्ण

अटल व्योम kvmppc_inject_पूर्णांकerrupt_pr(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags)
अणु
	अचिन्हित दीर्घ msr, pc, new_msr, new_pc;

	kvmppc_unfixup_split_real(vcpu);

	msr = kvmppc_get_msr(vcpu);
	pc = kvmppc_get_pc(vcpu);
	new_msr = vcpu->arch.पूर्णांकr_msr;
	new_pc = to_book3s(vcpu)->hior + vec;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* If transactional, change to suspend mode on IRQ delivery */
	अगर (MSR_TM_TRANSACTIONAL(msr))
		new_msr |= MSR_TS_S;
	अन्यथा
		new_msr |= msr & MSR_TS_MASK;
#पूर्ण_अगर

	kvmppc_set_srr0(vcpu, pc);
	kvmppc_set_srr1(vcpu, (msr & SRR1_MSR_BITS) | srr1_flags);
	kvmppc_set_pc(vcpu, new_pc);
	kvmppc_set_msr(vcpu, new_msr);
पूर्ण

अटल व्योम kvmppc_core_vcpu_load_pr(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	स_नकल(svcpu->slb, to_book3s(vcpu)->slb_shaकरोw, माप(svcpu->slb));
	svcpu->slb_max = to_book3s(vcpu)->slb_shaकरोw_max;
	svcpu->in_use = 0;
	svcpu_put(svcpu);
#पूर्ण_अगर

	/* Disable AIL अगर supported */
	अगर (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) & ~LPCR_AIL);

	vcpu->cpu = smp_processor_id();
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	current->thपढ़ो.kvm_shaकरोw_vcpu = vcpu->arch.shaकरोw_vcpu;
#पूर्ण_अगर

	अगर (kvmppc_is_split_real(vcpu))
		kvmppc_fixup_split_real(vcpu);

	kvmppc_restore_पंचांग_pr(vcpu);
पूर्ण

अटल व्योम kvmppc_core_vcpu_put_pr(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	अगर (svcpu->in_use) अणु
		kvmppc_copy_from_svcpu(vcpu);
	पूर्ण
	स_नकल(to_book3s(vcpu)->slb_shaकरोw, svcpu->slb, माप(svcpu->slb));
	to_book3s(vcpu)->slb_shaकरोw_max = svcpu->slb_max;
	svcpu_put(svcpu);
#पूर्ण_अगर

	अगर (kvmppc_is_split_real(vcpu))
		kvmppc_unfixup_split_real(vcpu);

	kvmppc_giveup_ext(vcpu, MSR_FP | MSR_VEC | MSR_VSX);
	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);
	kvmppc_save_पंचांग_pr(vcpu);

	/* Enable AIL अगर supported */
	अगर (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) | LPCR_AIL_3);

	vcpu->cpu = -1;
पूर्ण

/* Copy data needed by real-mode code from vcpu to shaकरोw vcpu */
व्योम kvmppc_copy_to_svcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);

	svcpu->gpr[0] = vcpu->arch.regs.gpr[0];
	svcpu->gpr[1] = vcpu->arch.regs.gpr[1];
	svcpu->gpr[2] = vcpu->arch.regs.gpr[2];
	svcpu->gpr[3] = vcpu->arch.regs.gpr[3];
	svcpu->gpr[4] = vcpu->arch.regs.gpr[4];
	svcpu->gpr[5] = vcpu->arch.regs.gpr[5];
	svcpu->gpr[6] = vcpu->arch.regs.gpr[6];
	svcpu->gpr[7] = vcpu->arch.regs.gpr[7];
	svcpu->gpr[8] = vcpu->arch.regs.gpr[8];
	svcpu->gpr[9] = vcpu->arch.regs.gpr[9];
	svcpu->gpr[10] = vcpu->arch.regs.gpr[10];
	svcpu->gpr[11] = vcpu->arch.regs.gpr[11];
	svcpu->gpr[12] = vcpu->arch.regs.gpr[12];
	svcpu->gpr[13] = vcpu->arch.regs.gpr[13];
	svcpu->cr  = vcpu->arch.regs.ccr;
	svcpu->xer = vcpu->arch.regs.xer;
	svcpu->ctr = vcpu->arch.regs.ctr;
	svcpu->lr  = vcpu->arch.regs.link;
	svcpu->pc  = vcpu->arch.regs.nip;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	svcpu->shaकरोw_fscr = vcpu->arch.shaकरोw_fscr;
#पूर्ण_अगर
	/*
	 * Now also save the current समय base value. We use this
	 * to find the guest purr and spurr value.
	 */
	vcpu->arch.entry_tb = get_tb();
	vcpu->arch.entry_vtb = get_vtb();
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		vcpu->arch.entry_ic = mfspr(SPRN_IC);
	svcpu->in_use = true;

	svcpu_put(svcpu);
पूर्ण

अटल व्योम kvmppc_recalc_shaकरोw_msr(काष्ठा kvm_vcpu *vcpu)
अणु
	uदीर्घ guest_msr = kvmppc_get_msr(vcpu);
	uदीर्घ smsr = guest_msr;

	/* Guest MSR values */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	smsr &= MSR_FE0 | MSR_FE1 | MSR_SF | MSR_SE | MSR_BE | MSR_LE |
		MSR_TM | MSR_TS_MASK;
#अन्यथा
	smsr &= MSR_FE0 | MSR_FE1 | MSR_SF | MSR_SE | MSR_BE | MSR_LE;
#पूर्ण_अगर
	/* Process MSR values */
	smsr |= MSR_ME | MSR_RI | MSR_IR | MSR_DR | MSR_PR | MSR_EE;
	/* External providers the guest reserved */
	smsr |= (guest_msr & vcpu->arch.guest_owned_ext);
	/* 64-bit Process MSR values */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	smsr |= MSR_HV;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	/*
	 * in guest privileged state, we want to fail all TM transactions.
	 * So disable MSR TM bit so that all tbegin. will be able to be
	 * trapped पूर्णांकo host.
	 */
	अगर (!(guest_msr & MSR_PR))
		smsr &= ~MSR_TM;
#पूर्ण_अगर
	vcpu->arch.shaकरोw_msr = smsr;
पूर्ण

/* Copy data touched by real-mode code from shaकरोw vcpu back to vcpu */
व्योम kvmppc_copy_from_svcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	uदीर्घ old_msr;
#पूर्ण_अगर

	/*
	 * Maybe we were alपढ़ोy preempted and synced the svcpu from
	 * our preempt notअगरiers. Don't bother touching this svcpu then.
	 */
	अगर (!svcpu->in_use)
		जाओ out;

	vcpu->arch.regs.gpr[0] = svcpu->gpr[0];
	vcpu->arch.regs.gpr[1] = svcpu->gpr[1];
	vcpu->arch.regs.gpr[2] = svcpu->gpr[2];
	vcpu->arch.regs.gpr[3] = svcpu->gpr[3];
	vcpu->arch.regs.gpr[4] = svcpu->gpr[4];
	vcpu->arch.regs.gpr[5] = svcpu->gpr[5];
	vcpu->arch.regs.gpr[6] = svcpu->gpr[6];
	vcpu->arch.regs.gpr[7] = svcpu->gpr[7];
	vcpu->arch.regs.gpr[8] = svcpu->gpr[8];
	vcpu->arch.regs.gpr[9] = svcpu->gpr[9];
	vcpu->arch.regs.gpr[10] = svcpu->gpr[10];
	vcpu->arch.regs.gpr[11] = svcpu->gpr[11];
	vcpu->arch.regs.gpr[12] = svcpu->gpr[12];
	vcpu->arch.regs.gpr[13] = svcpu->gpr[13];
	vcpu->arch.regs.ccr  = svcpu->cr;
	vcpu->arch.regs.xer = svcpu->xer;
	vcpu->arch.regs.ctr = svcpu->ctr;
	vcpu->arch.regs.link  = svcpu->lr;
	vcpu->arch.regs.nip  = svcpu->pc;
	vcpu->arch.shaकरोw_srr1 = svcpu->shaकरोw_srr1;
	vcpu->arch.fault_dar   = svcpu->fault_dar;
	vcpu->arch.fault_dsisr = svcpu->fault_dsisr;
	vcpu->arch.last_inst   = svcpu->last_inst;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	vcpu->arch.shaकरोw_fscr = svcpu->shaकरोw_fscr;
#पूर्ण_अगर
	/*
	 * Update purr and spurr using समय base on निकास.
	 */
	vcpu->arch.purr += get_tb() - vcpu->arch.entry_tb;
	vcpu->arch.spurr += get_tb() - vcpu->arch.entry_tb;
	to_book3s(vcpu)->vtb += get_vtb() - vcpu->arch.entry_vtb;
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		vcpu->arch.ic += mfspr(SPRN_IC) - vcpu->arch.entry_ic;

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	/*
	 * Unlike other MSR bits, MSR[TS]bits can be changed at guest without
	 * notअगरying host:
	 *  modअगरied by unprivileged inकाष्ठाions like "tbegin"/"tend"/
	 * "tresume"/"tsuspend" in PR KVM guest.
	 *
	 * It is necessary to sync here to calculate a correct shaकरोw_msr.
	 *
	 * privileged guest's tbegin will be failed at present. So we
	 * only take care of problem state guest.
	 */
	old_msr = kvmppc_get_msr(vcpu);
	अगर (unlikely((old_msr & MSR_PR) &&
		(vcpu->arch.shaकरोw_srr1 & (MSR_TS_MASK)) !=
				(old_msr & (MSR_TS_MASK)))) अणु
		old_msr &= ~(MSR_TS_MASK);
		old_msr |= (vcpu->arch.shaकरोw_srr1 & (MSR_TS_MASK));
		kvmppc_set_msr_fast(vcpu, old_msr);
		kvmppc_recalc_shaकरोw_msr(vcpu);
	पूर्ण
#पूर्ण_अगर

	svcpu->in_use = false;

out:
	svcpu_put(svcpu);
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
व्योम kvmppc_save_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu)
अणु
	पंचांग_enable();
	vcpu->arch.tfhar = mfspr(SPRN_TFHAR);
	vcpu->arch.texasr = mfspr(SPRN_TEXASR);
	vcpu->arch.tfiar = mfspr(SPRN_TFIAR);
	पंचांग_disable();
पूर्ण

व्योम kvmppc_restore_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu)
अणु
	पंचांग_enable();
	mtspr(SPRN_TFHAR, vcpu->arch.tfhar);
	mtspr(SPRN_TEXASR, vcpu->arch.texasr);
	mtspr(SPRN_TFIAR, vcpu->arch.tfiar);
	पंचांग_disable();
पूर्ण

/* loadup math bits which is enabled at kvmppc_get_msr() but not enabled at
 * hardware.
 */
अटल व्योम kvmppc_handle_lost_math_exts(काष्ठा kvm_vcpu *vcpu)
अणु
	uदीर्घ निकास_nr;
	uदीर्घ ext_dअगरf = (kvmppc_get_msr(vcpu) & ~vcpu->arch.guest_owned_ext) &
		(MSR_FP | MSR_VEC | MSR_VSX);

	अगर (!ext_dअगरf)
		वापस;

	अगर (ext_dअगरf == MSR_FP)
		निकास_nr = BOOK3S_INTERRUPT_FP_UNAVAIL;
	अन्यथा अगर (ext_dअगरf == MSR_VEC)
		निकास_nr = BOOK3S_INTERRUPT_ALTIVEC;
	अन्यथा
		निकास_nr = BOOK3S_INTERRUPT_VSX;

	kvmppc_handle_ext(vcpu, निकास_nr, ext_dअगरf);
पूर्ण

व्योम kvmppc_save_पंचांग_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(MSR_TM_ACTIVE(kvmppc_get_msr(vcpu)))) अणु
		kvmppc_save_पंचांग_sprs(vcpu);
		वापस;
	पूर्ण

	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);
	kvmppc_giveup_ext(vcpu, MSR_VSX);

	preempt_disable();
	_kvmppc_save_पंचांग_pr(vcpu, mfmsr());
	preempt_enable();
पूर्ण

व्योम kvmppc_restore_पंचांग_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!MSR_TM_ACTIVE(kvmppc_get_msr(vcpu))) अणु
		kvmppc_restore_पंचांग_sprs(vcpu);
		अगर (kvmppc_get_msr(vcpu) & MSR_TM) अणु
			kvmppc_handle_lost_math_exts(vcpu);
			अगर (vcpu->arch.fscr & FSCR_TAR)
				kvmppc_handle_fac(vcpu, FSCR_TAR_LG);
		पूर्ण
		वापस;
	पूर्ण

	preempt_disable();
	_kvmppc_restore_पंचांग_pr(vcpu, kvmppc_get_msr(vcpu));
	preempt_enable();

	अगर (kvmppc_get_msr(vcpu) & MSR_TM) अणु
		kvmppc_handle_lost_math_exts(vcpu);
		अगर (vcpu->arch.fscr & FSCR_TAR)
			kvmppc_handle_fac(vcpu, FSCR_TAR_LG);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvmppc_core_check_requests_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = 1; /* Indicate we want to get back पूर्णांकo the guest */

	/* We misuse TLB_FLUSH to indicate that we want to clear
	   all shaकरोw cache entries */
	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu))
		kvmppc_mmu_pte_flush(vcpu, 0, 0);

	वापस r;
पूर्ण

/************* MMU Notअगरiers *************/
अटल bool करो_kvm_unmap_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	दीर्घ i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvmppc_mmu_pte_pflush(vcpu, range->start << PAGE_SHIFT,
				      range->end << PAGE_SHIFT);

	वापस false;
पूर्ण

अटल bool kvm_unmap_gfn_range_pr(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस करो_kvm_unmap_gfn(kvm, range);
पूर्ण

अटल bool kvm_age_gfn_pr(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* XXX could be more clever ;) */
	वापस false;
पूर्ण

अटल bool kvm_test_age_gfn_pr(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* XXX could be more clever ;) */
	वापस false;
पूर्ण

अटल bool kvm_set_spte_gfn_pr(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* The page will get remapped properly on its next fault */
	वापस करो_kvm_unmap_gfn(kvm, range);
पूर्ण

/*****************************************/

अटल व्योम kvmppc_set_msr_pr(काष्ठा kvm_vcpu *vcpu, u64 msr)
अणु
	uदीर्घ old_msr;

	/* For PAPR guest, make sure MSR reflects guest mode */
	अगर (vcpu->arch.papr_enabled)
		msr = (msr & ~MSR_HV) | MSR_ME;

#अगर_घोषित EXIT_DEBUG
	prपूर्णांकk(KERN_INFO "KVM: Set MSR to 0x%llx\n", msr);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	/* We should never target guest MSR to TS=10 && PR=0,
	 * since we always fail transaction क्रम guest privilege
	 * state.
	 */
	अगर (!(msr & MSR_PR) && MSR_TM_TRANSACTIONAL(msr))
		kvmppc_emulate_tपात(vcpu,
			TM_CAUSE_KVM_FAC_UNAV | TM_CAUSE_PERSISTENT);
#पूर्ण_अगर

	old_msr = kvmppc_get_msr(vcpu);
	msr &= to_book3s(vcpu)->msr_mask;
	kvmppc_set_msr_fast(vcpu, msr);
	kvmppc_recalc_shaकरोw_msr(vcpu);

	अगर (msr & MSR_POW) अणु
		अगर (!vcpu->arch.pending_exceptions) अणु
			kvm_vcpu_block(vcpu);
			kvm_clear_request(KVM_REQ_UNHALT, vcpu);
			vcpu->स्थिति.सalt_wakeup++;

			/* Unset POW bit after we woke up */
			msr &= ~MSR_POW;
			kvmppc_set_msr_fast(vcpu, msr);
		पूर्ण
	पूर्ण

	अगर (kvmppc_is_split_real(vcpu))
		kvmppc_fixup_split_real(vcpu);
	अन्यथा
		kvmppc_unfixup_split_real(vcpu);

	अगर ((kvmppc_get_msr(vcpu) & (MSR_PR|MSR_IR|MSR_DR)) !=
		   (old_msr & (MSR_PR|MSR_IR|MSR_DR))) अणु
		kvmppc_mmu_flush_segments(vcpu);
		kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));

		/* Preload magic page segment when in kernel mode */
		अगर (!(msr & MSR_PR) && vcpu->arch.magic_page_pa) अणु
			काष्ठा kvm_vcpu_arch *a = &vcpu->arch;

			अगर (msr & MSR_DR)
				kvmppc_mmu_map_segment(vcpu, a->magic_page_ea);
			अन्यथा
				kvmppc_mmu_map_segment(vcpu, a->magic_page_pa);
		पूर्ण
	पूर्ण

	/*
	 * When चयनing from 32 to 64-bit, we may have a stale 32-bit
	 * magic page around, we need to flush it. Typically 32-bit magic
	 * page will be instantiated when calling पूर्णांकo RTAS. Note: We
	 * assume that such transition only happens जबतक in kernel mode,
	 * ie, we never transition from user 32-bit to kernel 64-bit with
	 * a 32-bit magic page around.
	 */
	अगर (vcpu->arch.magic_page_pa &&
	    !(old_msr & MSR_PR) && !(old_msr & MSR_SF) && (msr & MSR_SF)) अणु
		/* going from RTAS to normal kernel code */
		kvmppc_mmu_pte_flush(vcpu, (uपूर्णांक32_t)vcpu->arch.magic_page_pa,
				     ~0xFFFUL);
	पूर्ण

	/* Preload FPU अगर it's enabled */
	अगर (kvmppc_get_msr(vcpu) & MSR_FP)
		kvmppc_handle_ext(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL, MSR_FP);

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	अगर (kvmppc_get_msr(vcpu) & MSR_TM)
		kvmppc_handle_lost_math_exts(vcpu);
#पूर्ण_अगर
पूर्ण

अटल व्योम kvmppc_set_pvr_pr(काष्ठा kvm_vcpu *vcpu, u32 pvr)
अणु
	u32 host_pvr;

	vcpu->arch.hflags &= ~BOOK3S_HFLAG_SLB;
	vcpu->arch.pvr = pvr;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर ((pvr >= 0x330000) && (pvr < 0x70330000)) अणु
		kvmppc_mmu_book3s_64_init(vcpu);
		अगर (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0xfff00000;
		to_book3s(vcpu)->msr_mask = 0xffffffffffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_64;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		kvmppc_mmu_book3s_32_init(vcpu);
		अगर (!to_book3s(vcpu)->hior_explicit)
			to_book3s(vcpu)->hior = 0;
		to_book3s(vcpu)->msr_mask = 0xffffffffULL;
		vcpu->arch.cpu_type = KVM_CPU_3S_32;
	पूर्ण

	kvmppc_sanity_check(vcpu);

	/* If we are in hypervisor level on 970, we can tell the CPU to
	 * treat DCBZ as 32 bytes store */
	vcpu->arch.hflags &= ~BOOK3S_HFLAG_DCBZ32;
	अगर (vcpu->arch.mmu.is_dcbz32(vcpu) && (mfmsr() & MSR_HV) &&
	    !म_भेद(cur_cpu_spec->platक्रमm, "ppc970"))
		vcpu->arch.hflags |= BOOK3S_HFLAG_DCBZ32;

	/* Cell perक्रमms badly अगर MSR_FEx are set. So let's hope nobody
	   really needs them in a VM on Cell and क्रमce disable them. */
	अगर (!म_भेद(cur_cpu_spec->platक्रमm, "ppc-cell-be"))
		to_book3s(vcpu)->msr_mask &= ~(MSR_FE0 | MSR_FE1);

	/*
	 * If they're asking क्रम POWER6 or later, set the flag
	 * indicating that we can करो multiple large page sizes
	 * and 1TB segments.
	 * Also set the flag that indicates that tlbie has the large
	 * page bit in the RB opeअक्रम instead of the inकाष्ठाion.
	 */
	चयन (PVR_VER(pvr)) अणु
	हाल PVR_POWER6:
	हाल PVR_POWER7:
	हाल PVR_POWER7p:
	हाल PVR_POWER8:
	हाल PVR_POWER8E:
	हाल PVR_POWER8NVL:
	हाल PVR_POWER9:
		vcpu->arch.hflags |= BOOK3S_HFLAG_MULTI_PGSIZE |
			BOOK3S_HFLAG_NEW_TLBIE;
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_32
	/* 32 bit Book3S always has 32 byte dcbz */
	vcpu->arch.hflags |= BOOK3S_HFLAG_DCBZ32;
#पूर्ण_अगर

	/* On some CPUs we can execute paired single operations natively */
	यंत्र ( "mfpvr %0" : "=r"(host_pvr));
	चयन (host_pvr) अणु
	हाल 0x00080200:	/* lonestar 2.0 */
	हाल 0x00088202:	/* lonestar 2.2 */
	हाल 0x70000100:	/* gekko 1.0 */
	हाल 0x00080100:	/* gekko 2.0 */
	हाल 0x00083203:	/* gekko 2.3a */
	हाल 0x00083213:	/* gekko 2.3b */
	हाल 0x00083204:	/* gekko 2.4 */
	हाल 0x00083214:	/* gekko 2.4e (8SE) - retail HW2 */
	हाल 0x00087200:	/* broadway */
		vcpu->arch.hflags |= BOOK3S_HFLAG_NATIVE_PS;
		/* Enable HID2.PSE - in हाल we need it later */
		mtspr(SPRN_HID2_GEKKO, mfspr(SPRN_HID2_GEKKO) | (1 << 29));
	पूर्ण
पूर्ण

/* Book3s_32 CPUs always have 32 bytes cache line size, which Linux assumes. To
 * make Book3s_32 Linux work on Book3s_64, we have to make sure we trap dcbz to
 * emulate 32 bytes dcbz length.
 *
 * The Book3s_64 inventors also realized this हाल and implemented a special bit
 * in the HID5 रेजिस्टर, which is a hypervisor ressource. Thus we can't use it.
 *
 * My approach here is to patch the dcbz inकाष्ठाion on executing pages.
 */
अटल व्योम kvmppc_patch_dcbz(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *pte)
अणु
	काष्ठा page *hpage;
	u64 hpage_offset;
	u32 *page;
	पूर्णांक i;

	hpage = gfn_to_page(vcpu->kvm, pte->raddr >> PAGE_SHIFT);
	अगर (is_error_page(hpage))
		वापस;

	hpage_offset = pte->raddr & ~PAGE_MASK;
	hpage_offset &= ~0xFFFULL;
	hpage_offset /= 4;

	get_page(hpage);
	page = kmap_atomic(hpage);

	/* patch dcbz पूर्णांकo reserved inकाष्ठाion, so we trap */
	क्रम (i=hpage_offset; i < hpage_offset + (HW_PAGE_SIZE / 4); i++)
		अगर ((be32_to_cpu(page[i]) & 0xff0007ff) == INS_DCBZ)
			page[i] &= cpu_to_be32(0xfffffff7);

	kunmap_atomic(page);
	put_page(hpage);
पूर्ण

अटल bool kvmppc_visible_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	uदीर्घ mp_pa = vcpu->arch.magic_page_pa;

	अगर (!(kvmppc_get_msr(vcpu) & MSR_SF))
		mp_pa = (uपूर्णांक32_t)mp_pa;

	gpa &= ~0xFFFULL;
	अगर (unlikely(mp_pa) && unlikely((mp_pa & KVM_PAM) == (gpa & KVM_PAM))) अणु
		वापस true;
	पूर्ण

	वापस kvm_is_visible_gfn(vcpu->kvm, gpa >> PAGE_SHIFT);
पूर्ण

अटल पूर्णांक kvmppc_handle_pagefault(काष्ठा kvm_vcpu *vcpu,
			    uदीर्घ eaddr, पूर्णांक vec)
अणु
	bool data = (vec == BOOK3S_INTERRUPT_DATA_STORAGE);
	bool isग_लिखो = false;
	पूर्णांक r = RESUME_GUEST;
	पूर्णांक relocated;
	पूर्णांक page_found = 0;
	काष्ठा kvmppc_pte pte = अणु 0 पूर्ण;
	bool dr = (kvmppc_get_msr(vcpu) & MSR_DR) ? true : false;
	bool ir = (kvmppc_get_msr(vcpu) & MSR_IR) ? true : false;
	u64 vsid;

	relocated = data ? dr : ir;
	अगर (data && (vcpu->arch.fault_dsisr & DSISR_ISSTORE))
		isग_लिखो = true;

	/* Resolve real address अगर translation turned on */
	अगर (relocated) अणु
		page_found = vcpu->arch.mmu.xlate(vcpu, eaddr, &pte, data, isग_लिखो);
	पूर्ण अन्यथा अणु
		pte.may_execute = true;
		pte.may_पढ़ो = true;
		pte.may_ग_लिखो = true;
		pte.raddr = eaddr & KVM_PAM;
		pte.eaddr = eaddr;
		pte.vpage = eaddr >> 12;
		pte.page_size = MMU_PAGE_64K;
		pte.wimg = HPTE_R_M;
	पूर्ण

	चयन (kvmppc_get_msr(vcpu) & (MSR_DR|MSR_IR)) अणु
	हाल 0:
		pte.vpage |= ((u64)VSID_REAL << (SID_SHIFT - 12));
		अवरोध;
	हाल MSR_DR:
		अगर (!data &&
		    (vcpu->arch.hflags & BOOK3S_HFLAG_SPLIT_HACK) &&
		    ((pte.raddr & SPLIT_HACK_MASK) == SPLIT_HACK_OFFS))
			pte.raddr &= ~SPLIT_HACK_MASK;
		fallthrough;
	हाल MSR_IR:
		vcpu->arch.mmu.esid_to_vsid(vcpu, eaddr >> SID_SHIFT, &vsid);

		अगर ((kvmppc_get_msr(vcpu) & (MSR_DR|MSR_IR)) == MSR_DR)
			pte.vpage |= ((u64)VSID_REAL_DR << (SID_SHIFT - 12));
		अन्यथा
			pte.vpage |= ((u64)VSID_REAL_IR << (SID_SHIFT - 12));
		pte.vpage |= vsid;

		अगर (vsid == -1)
			page_found = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (vcpu->arch.mmu.is_dcbz32(vcpu) &&
	   (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32))) अणु
		/*
		 * If we करो the dcbz hack, we have to NX on every execution,
		 * so we can patch the executing code. This renders our guest
		 * NX-less.
		 */
		pte.may_execute = !data;
	पूर्ण

	अगर (page_found == -ENOENT || page_found == -EPERM) अणु
		/* Page not found in guest PTE entries, or protection fault */
		u64 flags;

		अगर (page_found == -EPERM)
			flags = DSISR_PROTFAULT;
		अन्यथा
			flags = DSISR_NOHPTE;
		अगर (data) अणु
			flags |= vcpu->arch.fault_dsisr & DSISR_ISSTORE;
			kvmppc_core_queue_data_storage(vcpu, eaddr, flags);
		पूर्ण अन्यथा अणु
			kvmppc_core_queue_inst_storage(vcpu, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (page_found == -EINVAL) अणु
		/* Page not found in guest SLB */
		kvmppc_set_dar(vcpu, kvmppc_get_fault_dar(vcpu));
		kvmppc_book3s_queue_irqprio(vcpu, vec + 0x80);
	पूर्ण अन्यथा अगर (kvmppc_visible_gpa(vcpu, pte.raddr)) अणु
		अगर (data && !(vcpu->arch.fault_dsisr & DSISR_NOHPTE)) अणु
			/*
			 * There is alपढ़ोy a host HPTE there, presumably
			 * a पढ़ो-only one क्रम a page the guest thinks
			 * is writable, so get rid of it first.
			 */
			kvmppc_mmu_unmap_page(vcpu, &pte);
		पूर्ण
		/* The guest's PTE is not mapped yet. Map on the host */
		अगर (kvmppc_mmu_map_page(vcpu, &pte, isग_लिखो) == -EIO) अणु
			/* Exit KVM अगर mapping failed */
			vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			वापस RESUME_HOST;
		पूर्ण
		अगर (data)
			vcpu->stat.sp_storage++;
		अन्यथा अगर (vcpu->arch.mmu.is_dcbz32(vcpu) &&
			 (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32)))
			kvmppc_patch_dcbz(vcpu, &pte);
	पूर्ण अन्यथा अणु
		/* MMIO */
		vcpu->stat.mmio_निकासs++;
		vcpu->arch.paddr_accessed = pte.raddr;
		vcpu->arch.vaddr_accessed = pte.eaddr;
		r = kvmppc_emulate_mmio(vcpu);
		अगर ( r == RESUME_HOST_NV )
			r = RESUME_HOST;
	पूर्ण

	वापस r;
पूर्ण

/* Give up बाह्यal provider (FPU, Altivec, VSX) */
व्योम kvmppc_giveup_ext(काष्ठा kvm_vcpu *vcpu, uदीर्घ msr)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;

	/*
	 * VSX inकाष्ठाions can access FP and vector रेजिस्टरs, so अगर
	 * we are giving up VSX, make sure we give up FP and VMX as well.
	 */
	अगर (msr & MSR_VSX)
		msr |= MSR_FP | MSR_VEC;

	msr &= vcpu->arch.guest_owned_ext;
	अगर (!msr)
		वापस;

#अगर_घोषित DEBUG_EXT
	prपूर्णांकk(KERN_INFO "Giving up ext 0x%lx\n", msr);
#पूर्ण_अगर

	अगर (msr & MSR_FP) अणु
		/*
		 * Note that on CPUs with VSX, giveup_fpu stores
		 * both the traditional FP रेजिस्टरs and the added VSX
		 * रेजिस्टरs पूर्णांकo thपढ़ो.fp_state.fpr[].
		 */
		अगर (t->regs->msr & MSR_FP)
			giveup_fpu(current);
		t->fp_save_area = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_ALTIVEC
	अगर (msr & MSR_VEC) अणु
		अगर (current->thपढ़ो.regs->msr & MSR_VEC)
			giveup_altivec(current);
		t->vr_save_area = शून्य;
	पूर्ण
#पूर्ण_अगर

	vcpu->arch.guest_owned_ext &= ~(msr | MSR_VSX);
	kvmppc_recalc_shaकरोw_msr(vcpu);
पूर्ण

/* Give up facility (TAR / EBB / DSCR) */
व्योम kvmppc_giveup_fac(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (!(vcpu->arch.shaकरोw_fscr & (1ULL << fac))) अणु
		/* Facility not available to the guest, ignore giveup request*/
		वापस;
	पूर्ण

	चयन (fac) अणु
	हाल FSCR_TAR_LG:
		vcpu->arch.tar = mfspr(SPRN_TAR);
		mtspr(SPRN_TAR, current->thपढ़ो.tar);
		vcpu->arch.shaकरोw_fscr &= ~FSCR_TAR;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Handle बाह्यal providers (FPU, Altivec, VSX) */
अटल पूर्णांक kvmppc_handle_ext(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक निकास_nr,
			     uदीर्घ msr)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;

	/* When we have paired singles, we emulate in software */
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE)
		वापस RESUME_GUEST;

	अगर (!(kvmppc_get_msr(vcpu) & msr)) अणु
		kvmppc_book3s_queue_irqprio(vcpu, निकास_nr);
		वापस RESUME_GUEST;
	पूर्ण

	अगर (msr == MSR_VSX) अणु
		/* No VSX?  Give an illegal inकाष्ठाion पूर्णांकerrupt */
#अगर_घोषित CONFIG_VSX
		अगर (!cpu_has_feature(CPU_FTR_VSX))
#पूर्ण_अगर
		अणु
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण

		/*
		 * We have to load up all the FP and VMX रेजिस्टरs beक्रमe
		 * we can let the guest use VSX inकाष्ठाions.
		 */
		msr = MSR_FP | MSR_VEC | MSR_VSX;
	पूर्ण

	/* See अगर we alपढ़ोy own all the ext(s) needed */
	msr &= ~vcpu->arch.guest_owned_ext;
	अगर (!msr)
		वापस RESUME_GUEST;

#अगर_घोषित DEBUG_EXT
	prपूर्णांकk(KERN_INFO "Loading up ext 0x%lx\n", msr);
#पूर्ण_अगर

	अगर (msr & MSR_FP) अणु
		preempt_disable();
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		t->fp_save_area = &vcpu->arch.fp;
		preempt_enable();
	पूर्ण

	अगर (msr & MSR_VEC) अणु
#अगर_घोषित CONFIG_ALTIVEC
		preempt_disable();
		enable_kernel_altivec();
		load_vr_state(&vcpu->arch.vr);
		disable_kernel_altivec();
		t->vr_save_area = &vcpu->arch.vr;
		preempt_enable();
#पूर्ण_अगर
	पूर्ण

	t->regs->msr |= msr;
	vcpu->arch.guest_owned_ext |= msr;
	kvmppc_recalc_shaकरोw_msr(vcpu);

	वापस RESUME_GUEST;
पूर्ण

/*
 * Kernel code using FP or VMX could have flushed guest state to
 * the thपढ़ो_काष्ठा; अगर so, get it back now.
 */
अटल व्योम kvmppc_handle_lost_ext(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ lost_ext;

	lost_ext = vcpu->arch.guest_owned_ext & ~current->thपढ़ो.regs->msr;
	अगर (!lost_ext)
		वापस;

	अगर (lost_ext & MSR_FP) अणु
		preempt_disable();
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		preempt_enable();
	पूर्ण
#अगर_घोषित CONFIG_ALTIVEC
	अगर (lost_ext & MSR_VEC) अणु
		preempt_disable();
		enable_kernel_altivec();
		load_vr_state(&vcpu->arch.vr);
		disable_kernel_altivec();
		preempt_enable();
	पूर्ण
#पूर्ण_अगर
	current->thपढ़ो.regs->msr |= lost_ext;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64

व्योम kvmppc_trigger_fac_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac)
अणु
	/* Inject the Interrupt Cause field and trigger a guest पूर्णांकerrupt */
	vcpu->arch.fscr &= ~(0xffULL << 56);
	vcpu->arch.fscr |= (fac << 56);
	kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_FAC_UNAVAIL);
पूर्ण

अटल व्योम kvmppc_emulate_fac(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac)
अणु
	क्रमागत emulation_result er = EMULATE_FAIL;

	अगर (!(kvmppc_get_msr(vcpu) & MSR_PR))
		er = kvmppc_emulate_inकाष्ठाion(vcpu);

	अगर ((er != EMULATE_DONE) && (er != EMULATE_AGAIN)) अणु
		/* Couldn't emulate, trigger पूर्णांकerrupt in guest */
		kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, fac);
	पूर्ण
पूर्ण

/* Enable facilities (TAR, EBB, DSCR) क्रम the guest */
अटल पूर्णांक kvmppc_handle_fac(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac)
अणु
	bool guest_fac_enabled;
	BUG_ON(!cpu_has_feature(CPU_FTR_ARCH_207S));

	/*
	 * Not every facility is enabled by FSCR bits, check whether the
	 * guest has this facility enabled at all.
	 */
	चयन (fac) अणु
	हाल FSCR_TAR_LG:
	हाल FSCR_EBB_LG:
		guest_fac_enabled = (vcpu->arch.fscr & (1ULL << fac));
		अवरोध;
	हाल FSCR_TM_LG:
		guest_fac_enabled = kvmppc_get_msr(vcpu) & MSR_TM;
		अवरोध;
	शेष:
		guest_fac_enabled = false;
		अवरोध;
	पूर्ण

	अगर (!guest_fac_enabled) अणु
		/* Facility not enabled by the guest */
		kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, fac);
		वापस RESUME_GUEST;
	पूर्ण

	चयन (fac) अणु
	हाल FSCR_TAR_LG:
		/* TAR चयनing isn't lazy in Linux yet */
		current->thपढ़ो.tar = mfspr(SPRN_TAR);
		mtspr(SPRN_TAR, vcpu->arch.tar);
		vcpu->arch.shaकरोw_fscr |= FSCR_TAR;
		अवरोध;
	शेष:
		kvmppc_emulate_fac(vcpu, fac);
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	/* Since we disabled MSR_TM at privilege state, the mfspr inकाष्ठाion
	 * क्रम TM spr can trigger TM fac unavailable. In this हाल, the
	 * emulation is handled by kvmppc_emulate_fac(), which invokes
	 * kvmppc_emulate_mfspr() finally. But note the mfspr can include
	 * RT क्रम NV रेजिस्टरs. So it need to restore those NV reg to reflect
	 * the update.
	 */
	अगर ((fac == FSCR_TM_LG) && !(kvmppc_get_msr(vcpu) & MSR_PR))
		वापस RESUME_GUEST_NV;
#पूर्ण_अगर

	वापस RESUME_GUEST;
पूर्ण

व्योम kvmppc_set_fscr(काष्ठा kvm_vcpu *vcpu, u64 fscr)
अणु
	अगर ((vcpu->arch.fscr & FSCR_TAR) && !(fscr & FSCR_TAR)) अणु
		/* TAR got dropped, drop it in shaकरोw too */
		kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);
	पूर्ण अन्यथा अगर (!(vcpu->arch.fscr & FSCR_TAR) && (fscr & FSCR_TAR)) अणु
		vcpu->arch.fscr = fscr;
		kvmppc_handle_fac(vcpu, FSCR_TAR_LG);
		वापस;
	पूर्ण

	vcpu->arch.fscr = fscr;
पूर्ण
#पूर्ण_अगर

अटल व्योम kvmppc_setup_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) अणु
		u64 msr = kvmppc_get_msr(vcpu);

		kvmppc_set_msr(vcpu, msr | MSR_SE);
	पूर्ण
पूर्ण

अटल व्योम kvmppc_clear_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) अणु
		u64 msr = kvmppc_get_msr(vcpu);

		kvmppc_set_msr(vcpu, msr & ~MSR_SE);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_निकास_pr_progपूर्णांक(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक निकास_nr)
अणु
	क्रमागत emulation_result er;
	uदीर्घ flags;
	u32 last_inst;
	पूर्णांक emul, r;

	/*
	 * shaकरोw_srr1 only contains valid flags अगर we came here via a program
	 * exception. The other exceptions (emulation assist, FP unavailable,
	 * etc.) करो not provide flags in SRR1, so use an illegal-inकाष्ठाion
	 * exception when injecting a program पूर्णांकerrupt पूर्णांकo the guest.
	 */
	अगर (निकास_nr == BOOK3S_INTERRUPT_PROGRAM)
		flags = vcpu->arch.shaकरोw_srr1 & 0x1f0000ull;
	अन्यथा
		flags = SRR1_PROGILL;

	emul = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);
	अगर (emul != EMULATE_DONE)
		वापस RESUME_GUEST;

	अगर (kvmppc_get_msr(vcpu) & MSR_PR) अणु
#अगर_घोषित EXIT_DEBUG
		pr_info("Userspace triggered 0x700 exception at\n 0x%lx (0x%x)\n",
			kvmppc_get_pc(vcpu), last_inst);
#पूर्ण_अगर
		अगर ((last_inst & 0xff0007ff) != (INS_DCBZ & 0xfffffff7)) अणु
			kvmppc_core_queue_program(vcpu, flags);
			वापस RESUME_GUEST;
		पूर्ण
	पूर्ण

	vcpu->stat.emulated_inst_निकासs++;
	er = kvmppc_emulate_inकाष्ठाion(vcpu);
	चयन (er) अणु
	हाल EMULATE_DONE:
		r = RESUME_GUEST_NV;
		अवरोध;
	हाल EMULATE_AGAIN:
		r = RESUME_GUEST;
		अवरोध;
	हाल EMULATE_FAIL:
		pr_crit("%s: emulation at %lx failed (%08x)\n",
			__func__, kvmppc_get_pc(vcpu), last_inst);
		kvmppc_core_queue_program(vcpu, flags);
		r = RESUME_GUEST;
		अवरोध;
	हाल EMULATE_DO_MMIO:
		vcpu->run->निकास_reason = KVM_EXIT_MMIO;
		r = RESUME_HOST_NV;
		अवरोध;
	हाल EMULATE_EXIT_USER:
		r = RESUME_HOST_NV;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_handle_निकास_pr(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक निकास_nr)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r = RESUME_HOST;
	पूर्णांक s;

	vcpu->stat.sum_निकासs++;

	run->निकास_reason = KVM_EXIT_UNKNOWN;
	run->पढ़ोy_क्रम_पूर्णांकerrupt_injection = 1;

	/* We get here with MSR.EE=1 */

	trace_kvm_निकास(निकास_nr, vcpu);
	guest_निकास();

	चयन (निकास_nr) अणु
	हाल BOOK3S_INTERRUPT_INST_STORAGE:
	अणु
		uदीर्घ shaकरोw_srr1 = vcpu->arch.shaकरोw_srr1;
		vcpu->stat.pf_instruc++;

		अगर (kvmppc_is_split_real(vcpu))
			kvmppc_fixup_split_real(vcpu);

#अगर_घोषित CONFIG_PPC_BOOK3S_32
		/* We set segments as unused segments when invalidating them. So
		 * treat the respective fault as segment fault. */
		अणु
			काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu;
			u32 sr;

			svcpu = svcpu_get(vcpu);
			sr = svcpu->sr[kvmppc_get_pc(vcpu) >> SID_SHIFT];
			svcpu_put(svcpu);
			अगर (sr == SR_INVALID) अणु
				kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));
				r = RESUME_GUEST;
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		/* only care about PTEG not found errors, but leave NX alone */
		अगर (shaकरोw_srr1 & 0x40000000) अणु
			पूर्णांक idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
			r = kvmppc_handle_pagefault(vcpu, kvmppc_get_pc(vcpu), निकास_nr);
			srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
			vcpu->stat.sp_instruc++;
		पूर्ण अन्यथा अगर (vcpu->arch.mmu.is_dcbz32(vcpu) &&
			  (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32))) अणु
			/*
			 * XXX If we करो the dcbz hack we use the NX bit to flush&patch the page,
			 *     so we can't use the NX bit inside the guest. Let's cross our fingers,
			 *     that no guest that needs the dcbz hack करोes NX.
			 */
			kvmppc_mmu_pte_flush(vcpu, kvmppc_get_pc(vcpu), ~0xFFFUL);
			r = RESUME_GUEST;
		पूर्ण अन्यथा अणु
			kvmppc_core_queue_inst_storage(vcpu,
						shaकरोw_srr1 & 0x58000000);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_DATA_STORAGE:
	अणु
		uदीर्घ dar = kvmppc_get_fault_dar(vcpu);
		u32 fault_dsisr = vcpu->arch.fault_dsisr;
		vcpu->stat.pf_storage++;

#अगर_घोषित CONFIG_PPC_BOOK3S_32
		/* We set segments as unused segments when invalidating them. So
		 * treat the respective fault as segment fault. */
		अणु
			काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu;
			u32 sr;

			svcpu = svcpu_get(vcpu);
			sr = svcpu->sr[dar >> SID_SHIFT];
			svcpu_put(svcpu);
			अगर (sr == SR_INVALID) अणु
				kvmppc_mmu_map_segment(vcpu, dar);
				r = RESUME_GUEST;
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		/*
		 * We need to handle missing shaकरोw PTEs, and
		 * protection faults due to us mapping a page पढ़ो-only
		 * when the guest thinks it is writable.
		 */
		अगर (fault_dsisr & (DSISR_NOHPTE | DSISR_PROTFAULT)) अणु
			पूर्णांक idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
			r = kvmppc_handle_pagefault(vcpu, dar, निकास_nr);
			srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		पूर्ण अन्यथा अणु
			kvmppc_core_queue_data_storage(vcpu, dar, fault_dsisr);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_DATA_SEGMENT:
		अगर (kvmppc_mmu_map_segment(vcpu, kvmppc_get_fault_dar(vcpu)) < 0) अणु
			kvmppc_set_dar(vcpu, kvmppc_get_fault_dar(vcpu));
			kvmppc_book3s_queue_irqprio(vcpu,
				BOOK3S_INTERRUPT_DATA_SEGMENT);
		पूर्ण
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_INST_SEGMENT:
		अगर (kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu)) < 0) अणु
			kvmppc_book3s_queue_irqprio(vcpu,
				BOOK3S_INTERRUPT_INST_SEGMENT);
		पूर्ण
		r = RESUME_GUEST;
		अवरोध;
	/* We're good on these - the host merely wanted to get our attention */
	हाल BOOK3S_INTERRUPT_DECREMENTER:
	हाल BOOK3S_INTERRUPT_HV_DECREMENTER:
	हाल BOOK3S_INTERRUPT_DOORBELL:
	हाल BOOK3S_INTERRUPT_H_DOORBELL:
		vcpu->stat.dec_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_EXTERNAL:
	हाल BOOK3S_INTERRUPT_EXTERNAL_HV:
	हाल BOOK3S_INTERRUPT_H_VIRT:
		vcpu->stat.ext_पूर्णांकr_निकासs++;
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_HMI:
	हाल BOOK3S_INTERRUPT_PERFMON:
	हाल BOOK3S_INTERRUPT_SYSTEM_RESET:
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_PROGRAM:
	हाल BOOK3S_INTERRUPT_H_EMUL_ASSIST:
		r = kvmppc_निकास_pr_progपूर्णांक(vcpu, निकास_nr);
		अवरोध;
	हाल BOOK3S_INTERRUPT_SYSCALL:
	अणु
		u32 last_sc;
		पूर्णांक emul;

		/* Get last sc क्रम papr */
		अगर (vcpu->arch.papr_enabled) अणु
			/* The sc instuction poपूर्णांकs SRR0 to the next inst */
			emul = kvmppc_get_last_inst(vcpu, INST_SC, &last_sc);
			अगर (emul != EMULATE_DONE) अणु
				kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) - 4);
				r = RESUME_GUEST;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (vcpu->arch.papr_enabled &&
		    (last_sc == 0x44000022) &&
		    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
			/* SC 1 papr hypercalls */
			uदीर्घ cmd = kvmppc_get_gpr(vcpu, 3);
			पूर्णांक i;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
			अगर (kvmppc_h_pr(vcpu, cmd) == EMULATE_DONE) अणु
				r = RESUME_GUEST;
				अवरोध;
			पूर्ण
#पूर्ण_अगर

			run->papr_hcall.nr = cmd;
			क्रम (i = 0; i < 9; ++i) अणु
				uदीर्घ gpr = kvmppc_get_gpr(vcpu, 4 + i);
				run->papr_hcall.args[i] = gpr;
			पूर्ण
			run->निकास_reason = KVM_EXIT_PAPR_HCALL;
			vcpu->arch.hcall_needed = 1;
			r = RESUME_HOST;
		पूर्ण अन्यथा अगर (vcpu->arch.osi_enabled &&
		    (((u32)kvmppc_get_gpr(vcpu, 3)) == OSI_SC_MAGIC_R3) &&
		    (((u32)kvmppc_get_gpr(vcpu, 4)) == OSI_SC_MAGIC_R4)) अणु
			/* MOL hypercalls */
			u64 *gprs = run->osi.gprs;
			पूर्णांक i;

			run->निकास_reason = KVM_EXIT_OSI;
			क्रम (i = 0; i < 32; i++)
				gprs[i] = kvmppc_get_gpr(vcpu, i);
			vcpu->arch.osi_needed = 1;
			r = RESUME_HOST_NV;
		पूर्ण अन्यथा अगर (!(kvmppc_get_msr(vcpu) & MSR_PR) &&
		    (((u32)kvmppc_get_gpr(vcpu, 0)) == KVM_SC_MAGIC_R0)) अणु
			/* KVM PV hypercalls */
			kvmppc_set_gpr(vcpu, 3, kvmppc_kvm_pv(vcpu));
			r = RESUME_GUEST;
		पूर्ण अन्यथा अणु
			/* Guest syscalls */
			vcpu->stat.syscall_निकासs++;
			kvmppc_book3s_queue_irqprio(vcpu, निकास_nr);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_FP_UNAVAIL:
	हाल BOOK3S_INTERRUPT_ALTIVEC:
	हाल BOOK3S_INTERRUPT_VSX:
	अणु
		पूर्णांक ext_msr = 0;
		पूर्णांक emul;
		u32 last_inst;

		अगर (vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE) अणु
			/* Do paired single inकाष्ठाion emulation */
			emul = kvmppc_get_last_inst(vcpu, INST_GENERIC,
						    &last_inst);
			अगर (emul == EMULATE_DONE)
				r = kvmppc_निकास_pr_progपूर्णांक(vcpu, निकास_nr);
			अन्यथा
				r = RESUME_GUEST;

			अवरोध;
		पूर्ण

		/* Enable बाह्यal provider */
		चयन (निकास_nr) अणु
		हाल BOOK3S_INTERRUPT_FP_UNAVAIL:
			ext_msr = MSR_FP;
			अवरोध;

		हाल BOOK3S_INTERRUPT_ALTIVEC:
			ext_msr = MSR_VEC;
			अवरोध;

		हाल BOOK3S_INTERRUPT_VSX:
			ext_msr = MSR_VSX;
			अवरोध;
		पूर्ण

		r = kvmppc_handle_ext(vcpu, निकास_nr, ext_msr);
		अवरोध;
	पूर्ण
	हाल BOOK3S_INTERRUPT_ALIGNMENT:
	अणु
		u32 last_inst;
		पूर्णांक emul = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);

		अगर (emul == EMULATE_DONE) अणु
			u32 dsisr;
			u64 dar;

			dsisr = kvmppc_alignment_dsisr(vcpu, last_inst);
			dar = kvmppc_alignment_dar(vcpu, last_inst);

			kvmppc_set_dsisr(vcpu, dsisr);
			kvmppc_set_dar(vcpu, dar);

			kvmppc_book3s_queue_irqprio(vcpu, निकास_nr);
		पूर्ण
		r = RESUME_GUEST;
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल BOOK3S_INTERRUPT_FAC_UNAVAIL:
		r = kvmppc_handle_fac(vcpu, vcpu->arch.shaकरोw_fscr >> 56);
		अवरोध;
#पूर्ण_अगर
	हाल BOOK3S_INTERRUPT_MACHINE_CHECK:
		kvmppc_book3s_queue_irqprio(vcpu, निकास_nr);
		r = RESUME_GUEST;
		अवरोध;
	हाल BOOK3S_INTERRUPT_TRACE:
		अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) अणु
			run->निकास_reason = KVM_EXIT_DEBUG;
			r = RESUME_HOST;
		पूर्ण अन्यथा अणु
			kvmppc_book3s_queue_irqprio(vcpu, निकास_nr);
			r = RESUME_GUEST;
		पूर्ण
		अवरोध;
	शेष:
	अणु
		uदीर्घ shaकरोw_srr1 = vcpu->arch.shaकरोw_srr1;
		/* Ugh - bork here! What did we get? */
		prपूर्णांकk(KERN_EMERG "exit_nr=0x%x | pc=0x%lx | msr=0x%lx\n",
			निकास_nr, kvmppc_get_pc(vcpu), shaकरोw_srr1);
		r = RESUME_HOST;
		BUG();
		अवरोध;
	पूर्ण
	पूर्ण

	अगर (!(r & RESUME_HOST)) अणु
		/* To aव्योम clobbering निकास_reason, only check क्रम संकेतs अगर
		 * we aren't alपढ़ोy निकासing to userspace क्रम some other
		 * reason. */

		/*
		 * Interrupts could be समयrs क्रम the guest which we have to
		 * inject again, so let's postpone them until we're in the guest
		 * and अगर we really did समय things so badly, then we just निकास
		 * again due to a host बाह्यal पूर्णांकerrupt.
		 */
		s = kvmppc_prepare_to_enter(vcpu);
		अगर (s <= 0)
			r = s;
		अन्यथा अणु
			/* पूर्णांकerrupts now hard-disabled */
			kvmppc_fix_ee_beक्रमe_entry();
		पूर्ण

		kvmppc_handle_lost_ext(vcpu);
	पूर्ण

	trace_kvm_book3s_reenter(r, vcpu);

	वापस r;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_get_sregs_pr(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	पूर्णांक i;

	sregs->pvr = vcpu->arch.pvr;

	sregs->u.s.sdr1 = to_book3s(vcpu)->sdr1;
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_SLB) अणु
		क्रम (i = 0; i < 64; i++) अणु
			sregs->u.s.ppc64.slb[i].slbe = vcpu->arch.slb[i].orige | i;
			sregs->u.s.ppc64.slb[i].slbv = vcpu->arch.slb[i].origv;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 16; i++)
			sregs->u.s.ppc32.sr[i] = kvmppc_get_sr(vcpu, i);

		क्रम (i = 0; i < 8; i++) अणु
			sregs->u.s.ppc32.ibat[i] = vcpu3s->ibat[i].raw;
			sregs->u.s.ppc32.dbat[i] = vcpu3s->dbat[i].raw;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_set_sregs_pr(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	पूर्णांक i;

	kvmppc_set_pvr_pr(vcpu, sregs->pvr);

	vcpu3s->sdr1 = sregs->u.s.sdr1;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_SLB) अणु
		/* Flush all SLB entries */
		vcpu->arch.mmu.slbmte(vcpu, 0, 0);
		vcpu->arch.mmu.slbia(vcpu);

		क्रम (i = 0; i < 64; i++) अणु
			u64 rb = sregs->u.s.ppc64.slb[i].slbe;
			u64 rs = sregs->u.s.ppc64.slb[i].slbv;

			अगर (rb & SLB_ESID_V)
				vcpu->arch.mmu.slbmte(vcpu, rs, rb);
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		क्रम (i = 0; i < 16; i++) अणु
			vcpu->arch.mmu.mtsrin(vcpu, i, sregs->u.s.ppc32.sr[i]);
		पूर्ण
		क्रम (i = 0; i < 8; i++) अणु
			kvmppc_set_bat(vcpu, &(vcpu3s->ibat[i]), false,
				       (u32)sregs->u.s.ppc32.ibat[i]);
			kvmppc_set_bat(vcpu, &(vcpu3s->ibat[i]), true,
				       (u32)(sregs->u.s.ppc32.ibat[i] >> 32));
			kvmppc_set_bat(vcpu, &(vcpu3s->dbat[i]), false,
				       (u32)sregs->u.s.ppc32.dbat[i]);
			kvmppc_set_bat(vcpu, &(vcpu3s->dbat[i]), true,
				       (u32)(sregs->u.s.ppc32.dbat[i] >> 32));
		पूर्ण
	पूर्ण

	/* Flush the MMU after messing with the segments */
	kvmppc_mmu_pte_flush(vcpu, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_get_one_reg_pr(काष्ठा kvm_vcpu *vcpu, u64 id,
				 जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		अवरोध;
	हाल KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, to_book3s(vcpu)->hior);
		अवरोध;
	हाल KVM_REG_PPC_VTB:
		*val = get_reg_val(id, to_book3s(vcpu)->vtb);
		अवरोध;
	हाल KVM_REG_PPC_LPCR:
	हाल KVM_REG_PPC_LPCR_64:
		/*
		 * We are only पूर्णांकerested in the LPCR_ILE bit
		 */
		अगर (vcpu->arch.पूर्णांकr_msr & MSR_LE)
			*val = get_reg_val(id, LPCR_ILE);
		अन्यथा
			*val = get_reg_val(id, 0);
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल KVM_REG_PPC_TFHAR:
		*val = get_reg_val(id, vcpu->arch.tfhar);
		अवरोध;
	हाल KVM_REG_PPC_TFIAR:
		*val = get_reg_val(id, vcpu->arch.tfiar);
		अवरोध;
	हाल KVM_REG_PPC_TEXASR:
		*val = get_reg_val(id, vcpu->arch.texasr);
		अवरोध;
	हाल KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		*val = get_reg_val(id,
				vcpu->arch.gpr_पंचांग[id-KVM_REG_PPC_TM_GPR0]);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	अणु
		पूर्णांक i, j;

		i = id - KVM_REG_PPC_TM_VSR0;
		अगर (i < 32)
			क्रम (j = 0; j < TS_FPRWIDTH; j++)
				val->vsxval[j] = vcpu->arch.fp_पंचांग.fpr[i][j];
		अन्यथा अणु
			अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				val->vval = vcpu->arch.vr_पंचांग.vr[i-32];
			अन्यथा
				r = -ENXIO;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TM_CR:
		*val = get_reg_val(id, vcpu->arch.cr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_XER:
		*val = get_reg_val(id, vcpu->arch.xer_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_LR:
		*val = get_reg_val(id, vcpu->arch.lr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_CTR:
		*val = get_reg_val(id, vcpu->arch.ctr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_FPSCR:
		*val = get_reg_val(id, vcpu->arch.fp_पंचांग.fpscr);
		अवरोध;
	हाल KVM_REG_PPC_TM_AMR:
		*val = get_reg_val(id, vcpu->arch.amr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSCR:
		अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
			*val = get_reg_val(id, vcpu->arch.vr_पंचांग.vscr.u[3]);
		अन्यथा
			r = -ENXIO;
		अवरोध;
	हाल KVM_REG_PPC_TM_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr_पंचांग);
		अवरोध;
	हाल KVM_REG_PPC_TM_TAR:
		*val = get_reg_val(id, vcpu->arch.tar_पंचांग);
		अवरोध;
#पूर्ण_अगर
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम kvmppc_set_lpcr_pr(काष्ठा kvm_vcpu *vcpu, u64 new_lpcr)
अणु
	अगर (new_lpcr & LPCR_ILE)
		vcpu->arch.पूर्णांकr_msr |= MSR_LE;
	अन्यथा
		vcpu->arch.पूर्णांकr_msr &= ~MSR_LE;
पूर्ण

अटल पूर्णांक kvmppc_set_one_reg_pr(काष्ठा kvm_vcpu *vcpu, u64 id,
				 जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;

	चयन (id) अणु
	हाल KVM_REG_PPC_HIOR:
		to_book3s(vcpu)->hior = set_reg_val(id, *val);
		to_book3s(vcpu)->hior_explicit = true;
		अवरोध;
	हाल KVM_REG_PPC_VTB:
		to_book3s(vcpu)->vtb = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_LPCR:
	हाल KVM_REG_PPC_LPCR_64:
		kvmppc_set_lpcr_pr(vcpu, set_reg_val(id, *val));
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल KVM_REG_PPC_TFHAR:
		vcpu->arch.tfhar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TFIAR:
		vcpu->arch.tfiar = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TEXASR:
		vcpu->arch.texasr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		vcpu->arch.gpr_पंचांग[id - KVM_REG_PPC_TM_GPR0] =
			set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	अणु
		पूर्णांक i, j;

		i = id - KVM_REG_PPC_TM_VSR0;
		अगर (i < 32)
			क्रम (j = 0; j < TS_FPRWIDTH; j++)
				vcpu->arch.fp_पंचांग.fpr[i][j] = val->vsxval[j];
		अन्यथा
			अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
				vcpu->arch.vr_पंचांग.vr[i-32] = val->vval;
			अन्यथा
				r = -ENXIO;
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TM_CR:
		vcpu->arch.cr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_XER:
		vcpu->arch.xer_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_LR:
		vcpu->arch.lr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_CTR:
		vcpu->arch.ctr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_FPSCR:
		vcpu->arch.fp_पंचांग.fpscr = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_AMR:
		vcpu->arch.amr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_PPR:
		vcpu->arch.ppr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VRSAVE:
		vcpu->arch.vrsave_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_VSCR:
		अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
			vcpu->arch.vr.vscr.u[3] = set_reg_val(id, *val);
		अन्यथा
			r = -ENXIO;
		अवरोध;
	हाल KVM_REG_PPC_TM_DSCR:
		vcpu->arch.dscr_पंचांग = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_TM_TAR:
		vcpu->arch.tar_पंचांग = set_reg_val(id, *val);
		अवरोध;
#पूर्ण_अगर
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_core_vcpu_create_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s;
	अचिन्हित दीर्घ p;
	पूर्णांक err;

	err = -ENOMEM;

	vcpu_book3s = vzalloc(माप(काष्ठा kvmppc_vcpu_book3s));
	अगर (!vcpu_book3s)
		जाओ out;
	vcpu->arch.book3s = vcpu_book3s;

#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	vcpu->arch.shaकरोw_vcpu =
		kzalloc(माप(*vcpu->arch.shaकरोw_vcpu), GFP_KERNEL);
	अगर (!vcpu->arch.shaकरोw_vcpu)
		जाओ मुक्त_vcpu3s;
#पूर्ण_अगर

	p = __get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
	अगर (!p)
		जाओ मुक्त_shaकरोw_vcpu;
	vcpu->arch.shared = (व्योम *)p;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Always start the shared काष्ठा in native endian mode */
#अगर_घोषित __BIG_ENDIAN__
        vcpu->arch.shared_big_endian = true;
#अन्यथा
        vcpu->arch.shared_big_endian = false;
#पूर्ण_अगर

	/*
	 * Default to the same as the host अगर we're on sufficiently
	 * recent machine that we have 1TB segments;
	 * otherwise शेष to PPC970FX.
	 */
	vcpu->arch.pvr = 0x3C0301;
	अगर (mmu_has_feature(MMU_FTR_1T_SEGMENT))
		vcpu->arch.pvr = mfspr(SPRN_PVR);
	vcpu->arch.पूर्णांकr_msr = MSR_SF;
#अन्यथा
	/* शेष to book3s_32 (750) */
	vcpu->arch.pvr = 0x84202;
	vcpu->arch.पूर्णांकr_msr = 0;
#पूर्ण_अगर
	kvmppc_set_pvr_pr(vcpu, vcpu->arch.pvr);
	vcpu->arch.slb_nr = 64;

	vcpu->arch.shaकरोw_msr = MSR_USER64 & ~MSR_LE;

	err = kvmppc_mmu_init_pr(vcpu);
	अगर (err < 0)
		जाओ मुक्त_shared_page;

	वापस 0;

मुक्त_shared_page:
	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.shared);
मुक्त_shaकरोw_vcpu:
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	kमुक्त(vcpu->arch.shaकरोw_vcpu);
मुक्त_vcpu3s:
#पूर्ण_अगर
	vमुक्त(vcpu_book3s);
out:
	वापस err;
पूर्ण

अटल व्योम kvmppc_core_vcpu_मुक्त_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);

	kvmppc_mmu_destroy_pr(vcpu);
	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.shared & PAGE_MASK);
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	kमुक्त(vcpu->arch.shaकरोw_vcpu);
#पूर्ण_अगर
	vमुक्त(vcpu_book3s);
पूर्ण

अटल पूर्णांक kvmppc_vcpu_run_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	/* Check अगर we can run the vcpu at all */
	अगर (!vcpu->arch.sane) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	kvmppc_setup_debug(vcpu);

	/*
	 * Interrupts could be समयrs क्रम the guest which we have to inject
	 * again, so let's postpone them until we're in the guest and अगर we
	 * really did समय things so badly, then we just निकास again due to
	 * a host बाह्यal पूर्णांकerrupt.
	 */
	ret = kvmppc_prepare_to_enter(vcpu);
	अगर (ret <= 0)
		जाओ out;
	/* पूर्णांकerrupts now hard-disabled */

	/* Save FPU, Altivec and VSX state */
	giveup_all(current);

	/* Preload FPU अगर it's enabled */
	अगर (kvmppc_get_msr(vcpu) & MSR_FP)
		kvmppc_handle_ext(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL, MSR_FP);

	kvmppc_fix_ee_beक्रमe_entry();

	ret = __kvmppc_vcpu_run(vcpu);

	kvmppc_clear_debug(vcpu);

	/* No need क्रम guest_निकास. It's करोne in handle_निकास.
	   We also get here with पूर्णांकerrupts enabled. */

	/* Make sure we save the guest FPU/Altivec/VSX state */
	kvmppc_giveup_ext(vcpu, MSR_FP | MSR_VEC | MSR_VSX);

	/* Make sure we save the guest TAR/EBB/DSCR state */
	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);

out:
	vcpu->mode = OUTSIDE_GUEST_MODE;
	वापस ret;
पूर्ण

/*
 * Get (and clear) the dirty memory log क्रम a memory slot.
 */
अटल पूर्णांक kvm_vm_ioctl_get_dirty_log_pr(काष्ठा kvm *kvm,
					 काष्ठा kvm_dirty_log *log)
अणु
	काष्ठा kvm_memory_slot *memslot;
	काष्ठा kvm_vcpu *vcpu;
	uदीर्घ ga, ga_end;
	पूर्णांक is_dirty = 0;
	पूर्णांक r;
	अचिन्हित दीर्घ n;

	mutex_lock(&kvm->slots_lock);

	r = kvm_get_dirty_log(kvm, log, &is_dirty, &memslot);
	अगर (r)
		जाओ out;

	/* If nothing is dirty, करोn't bother messing with page tables. */
	अगर (is_dirty) अणु
		ga = memslot->base_gfn << PAGE_SHIFT;
		ga_end = ga + (memslot->npages << PAGE_SHIFT);

		kvm_क्रम_each_vcpu(n, vcpu, kvm)
			kvmppc_mmu_pte_pflush(vcpu, ga, ga_end);

		n = kvm_dirty_biपंचांगap_bytes(memslot);
		स_रखो(memslot->dirty_biपंचांगap, 0, n);
	पूर्ण

	r = 0;
out:
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

अटल व्योम kvmppc_core_flush_memslot_pr(काष्ठा kvm *kvm,
					 काष्ठा kvm_memory_slot *memslot)
अणु
	वापस;
पूर्ण

अटल पूर्णांक kvmppc_core_prepare_memory_region_pr(काष्ठा kvm *kvm,
					काष्ठा kvm_memory_slot *memslot,
					स्थिर काष्ठा kvm_userspace_memory_region *mem,
					क्रमागत kvm_mr_change change)
अणु
	वापस 0;
पूर्ण

अटल व्योम kvmppc_core_commit_memory_region_pr(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				स्थिर काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
	वापस;
पूर्ण

अटल व्योम kvmppc_core_मुक्त_memslot_pr(काष्ठा kvm_memory_slot *slot)
अणु
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक kvm_vm_ioctl_get_smmu_info_pr(काष्ठा kvm *kvm,
					 काष्ठा kvm_ppc_smmu_info *info)
अणु
	दीर्घ पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	info->flags = 0;

	/* SLB is always 64 entries */
	info->slb_size = 64;

	/* Standard 4k base page size segment */
	info->sps[0].page_shअगरt = 12;
	info->sps[0].slb_enc = 0;
	info->sps[0].enc[0].page_shअगरt = 12;
	info->sps[0].enc[0].pte_enc = 0;

	/*
	 * 64k large page size.
	 * We only want to put this in अगर the CPUs we're emulating
	 * support it, but unक्रमtunately we करोn't have a vcpu easily
	 * to hand here to test.  Just pick the first vcpu, and अगर
	 * that करोesn't exist yet, report the minimum capability,
	 * i.e., no 64k pages.
	 * 1T segment support goes aदीर्घ with 64k pages.
	 */
	i = 1;
	vcpu = kvm_get_vcpu(kvm, 0);
	अगर (vcpu && (vcpu->arch.hflags & BOOK3S_HFLAG_MULTI_PGSIZE)) अणु
		info->flags = KVM_PPC_1T_SEGMENTS;
		info->sps[i].page_shअगरt = 16;
		info->sps[i].slb_enc = SLB_VSID_L | SLB_VSID_LP_01;
		info->sps[i].enc[0].page_shअगरt = 16;
		info->sps[i].enc[0].pte_enc = 1;
		++i;
	पूर्ण

	/* Standard 16M large page size segment */
	info->sps[i].page_shअगरt = 24;
	info->sps[i].slb_enc = SLB_VSID_L;
	info->sps[i].enc[0].page_shअगरt = 24;
	info->sps[i].enc[0].pte_enc = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_configure_mmu_pr(काष्ठा kvm *kvm, काष्ठा kvm_ppc_mmuv3_cfg *cfg)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
		वापस -ENODEV;
	/* Require flags and process table base and size to all be zero. */
	अगर (cfg->flags || cfg->process_table)
		वापस -EINVAL;
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक kvm_vm_ioctl_get_smmu_info_pr(काष्ठा kvm *kvm,
					 काष्ठा kvm_ppc_smmu_info *info)
अणु
	/* We should not get called */
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

अटल अचिन्हित पूर्णांक kvm_global_user_count = 0;
अटल DEFINE_SPINLOCK(kvm_global_user_count_lock);

अटल पूर्णांक kvmppc_core_init_vm_pr(काष्ठा kvm *kvm)
अणु
	mutex_init(&kvm->arch.hpt_mutex);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Start out with the शेष set of hcalls enabled */
	kvmppc_pr_init_शेष_hcalls(kvm);
#पूर्ण_अगर

	अगर (firmware_has_feature(FW_FEATURE_SET_MODE)) अणु
		spin_lock(&kvm_global_user_count_lock);
		अगर (++kvm_global_user_count == 1)
			pseries_disable_reloc_on_exc();
		spin_unlock(&kvm_global_user_count_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kvmppc_core_destroy_vm_pr(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_PPC64
	WARN_ON(!list_empty(&kvm->arch.spapr_tce_tables));
#पूर्ण_अगर

	अगर (firmware_has_feature(FW_FEATURE_SET_MODE)) अणु
		spin_lock(&kvm_global_user_count_lock);
		BUG_ON(kvm_global_user_count == 0);
		अगर (--kvm_global_user_count == 0)
			pseries_enable_reloc_on_exc();
		spin_unlock(&kvm_global_user_count_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_core_check_processor_compat_pr(व्योम)
अणु
	/*
	 * PR KVM can work on POWER9 inside a guest partition
	 * running in HPT mode.  It can't work अगर we are using
	 * radix translation (because radix provides no way क्रम
	 * a process to have unique translations in quadrant 3).
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300) && radix_enabled())
		वापस -EIO;
	वापस 0;
पूर्ण

अटल दीर्घ kvm_arch_vm_ioctl_pr(काष्ठा file *filp,
				 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTTY;
पूर्ण

अटल काष्ठा kvmppc_ops kvm_ops_pr = अणु
	.get_sregs = kvm_arch_vcpu_ioctl_get_sregs_pr,
	.set_sregs = kvm_arch_vcpu_ioctl_set_sregs_pr,
	.get_one_reg = kvmppc_get_one_reg_pr,
	.set_one_reg = kvmppc_set_one_reg_pr,
	.vcpu_load   = kvmppc_core_vcpu_load_pr,
	.vcpu_put    = kvmppc_core_vcpu_put_pr,
	.inject_पूर्णांकerrupt = kvmppc_inject_पूर्णांकerrupt_pr,
	.set_msr     = kvmppc_set_msr_pr,
	.vcpu_run    = kvmppc_vcpu_run_pr,
	.vcpu_create = kvmppc_core_vcpu_create_pr,
	.vcpu_मुक्त   = kvmppc_core_vcpu_मुक्त_pr,
	.check_requests = kvmppc_core_check_requests_pr,
	.get_dirty_log = kvm_vm_ioctl_get_dirty_log_pr,
	.flush_memslot = kvmppc_core_flush_memslot_pr,
	.prepare_memory_region = kvmppc_core_prepare_memory_region_pr,
	.commit_memory_region = kvmppc_core_commit_memory_region_pr,
	.unmap_gfn_range = kvm_unmap_gfn_range_pr,
	.age_gfn  = kvm_age_gfn_pr,
	.test_age_gfn = kvm_test_age_gfn_pr,
	.set_spte_gfn = kvm_set_spte_gfn_pr,
	.मुक्त_memslot = kvmppc_core_मुक्त_memslot_pr,
	.init_vm = kvmppc_core_init_vm_pr,
	.destroy_vm = kvmppc_core_destroy_vm_pr,
	.get_smmu_info = kvm_vm_ioctl_get_smmu_info_pr,
	.emulate_op = kvmppc_core_emulate_op_pr,
	.emulate_mtspr = kvmppc_core_emulate_mtspr_pr,
	.emulate_mfspr = kvmppc_core_emulate_mfspr_pr,
	.fast_vcpu_kick = kvm_vcpu_kick,
	.arch_vm_ioctl  = kvm_arch_vm_ioctl_pr,
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	.hcall_implemented = kvmppc_hcall_impl_pr,
	.configure_mmu = kvm_configure_mmu_pr,
#पूर्ण_अगर
	.giveup_ext = kvmppc_giveup_ext,
पूर्ण;


पूर्णांक kvmppc_book3s_init_pr(व्योम)
अणु
	पूर्णांक r;

	r = kvmppc_core_check_processor_compat_pr();
	अगर (r < 0)
		वापस r;

	kvm_ops_pr.owner = THIS_MODULE;
	kvmppc_pr_ops = &kvm_ops_pr;

	r = kvmppc_mmu_hpte_sysinit();
	वापस r;
पूर्ण

व्योम kvmppc_book3s_निकास_pr(व्योम)
अणु
	kvmppc_pr_ops = शून्य;
	kvmppc_mmu_hpte_sysनिकास();
पूर्ण

/*
 * We only support separate modules क्रम book3s 64
 */
#अगर_घोषित CONFIG_PPC_BOOK3S_64

module_init(kvmppc_book3s_init_pr);
module_निकास(kvmppc_book3s_निकास_pr);

MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(KVM_MINOR);
MODULE_ALIAS("devname:kvm");
#पूर्ण_अगर
