<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_book3s_64.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/ppc-opcode.h>

अटल व्योम emulate_tx_failure(काष्ठा kvm_vcpu *vcpu, u64 failure_cause)
अणु
	u64 texasr, tfiar;
	u64 msr = vcpu->arch.shregs.msr;

	tfiar = vcpu->arch.regs.nip & ~0x3ull;
	texasr = (failure_cause << 56) | TEXASR_ABORT | TEXASR_FS | TEXASR_EXACT;
	अगर (MSR_TM_SUSPENDED(vcpu->arch.shregs.msr))
		texasr |= TEXASR_SUSP;
	अगर (msr & MSR_PR) अणु
		texasr |= TEXASR_PR;
		tfiar |= 1;
	पूर्ण
	vcpu->arch.tfiar = tfiar;
	/* Preserve ROT and TL fields of existing TEXASR */
	vcpu->arch.texasr = (vcpu->arch.texasr & 0x3ffffff) | texasr;
पूर्ण

/*
 * This माला_लो called on a softpatch पूर्णांकerrupt on POWER9 DD2.2 processors.
 * We expect to find a TM-related inकाष्ठाion to be emulated.  The
 * inकाष्ठाion image is in vcpu->arch.emul_inst.  If the guest was in
 * TM suspended or transactional state, the checkpoपूर्णांकed state has been
 * reclaimed and is in the vcpu काष्ठा.  The CPU is in भव mode in
 * host context.
 */
पूर्णांक kvmhv_p9_पंचांग_emulation(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 instr = vcpu->arch.emul_inst;
	u64 msr = vcpu->arch.shregs.msr;
	u64 newmsr, bescr;
	पूर्णांक ra, rs;

	/*
	 * rfid, rfebb, and mपंचांगsrd encode bit 31 = 0 since it's a reserved bit
	 * in these inकाष्ठाions, so masking bit 31 out करोesn't change these
	 * inकाष्ठाions. For treclaim., tsr., and trechkpt. inकाष्ठाions अगर bit
	 * 31 = 0 then they are per ISA invalid क्रमms, however P9 UM, in section
	 * 4.6.10 Book II Invalid Forms, inक्रमms specअगरically that ignoring bit
	 * 31 is an acceptable way to handle these invalid क्रमms that have
	 * bit 31 = 0. Moreover, क्रम emulation purposes both क्रमms (w/ and wo/
	 * bit 31 set) can generate a softpatch पूर्णांकerrupt. Hence both क्रमms
	 * are handled below क्रम these inकाष्ठाions so they behave the same way.
	 */
	चयन (instr & PO_XOP_OPCODE_MASK) अणु
	हाल PPC_INST_RFID:
		/* XXX करो we need to check क्रम PR=0 here? */
		newmsr = vcpu->arch.shregs.srr1;
		/* should only get here क्रम Sx -> T1 transition */
		WARN_ON_ONCE(!(MSR_TM_SUSPENDED(msr) &&
			       MSR_TM_TRANSACTIONAL(newmsr) &&
			       (newmsr & MSR_TM)));
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = vcpu->arch.shregs.srr0;
		वापस RESUME_GUEST;

	हाल PPC_INST_RFEBB:
		अगर ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		/* check EBB facility is available */
		अगर (!(vcpu->arch.hfscr & HFSCR_EBB)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		अगर ((msr & MSR_PR) && !(vcpu->arch.fscr & FSCR_EBB)) अणु
			/* generate a facility unavailable पूर्णांकerrupt */
			vcpu->arch.fscr = (vcpu->arch.fscr & ~(0xffull << 56)) |
				((u64)FSCR_EBB_LG << 56);
			kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_FAC_UNAVAIL);
			वापस RESUME_GUEST;
		पूर्ण
		bescr = vcpu->arch.bescr;
		/* expect to see a S->T transition requested */
		WARN_ON_ONCE(!(MSR_TM_SUSPENDED(msr) &&
			       ((bescr >> 30) & 3) == 2));
		bescr &= ~BESCR_GE;
		अगर (instr & (1 << 11))
			bescr |= BESCR_GE;
		vcpu->arch.bescr = bescr;
		msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		vcpu->arch.shregs.msr = msr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = vcpu->arch.ebbrr;
		वापस RESUME_GUEST;

	हाल PPC_INST_MTMSRD:
		/* XXX करो we need to check क्रम PR=0 here? */
		rs = (instr >> 21) & 0x1f;
		newmsr = kvmppc_get_gpr(vcpu, rs);
		/* check this is a Sx -> T1 transition */
		WARN_ON_ONCE(!(MSR_TM_SUSPENDED(msr) &&
			       MSR_TM_TRANSACTIONAL(newmsr) &&
			       (newmsr & MSR_TM)));
		/* mपंचांगsrd करोesn't change LE */
		newmsr = (newmsr & ~MSR_LE) | (msr & MSR_LE);
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		वापस RESUME_GUEST;

	/* ignore bit 31, see comment above */
	हाल (PPC_INST_TSR & PO_XOP_OPCODE_MASK):
		/* check क्रम PR=1 and arch 2.06 bit set in PCR */
		अगर ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		/* check क्रम TM disabled in the HFSCR or MSR */
		अगर (!(vcpu->arch.hfscr & HFSCR_TM)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		अगर (!(msr & MSR_TM)) अणु
			/* generate a facility unavailable पूर्णांकerrupt */
			vcpu->arch.fscr = (vcpu->arch.fscr & ~(0xffull << 56)) |
				((u64)FSCR_TM_LG << 56);
			kvmppc_book3s_queue_irqprio(vcpu,
						BOOK3S_INTERRUPT_FAC_UNAVAIL);
			वापस RESUME_GUEST;
		पूर्ण
		/* Set CR0 to indicate previous transactional state */
		vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) |
			(((msr & MSR_TS_MASK) >> MSR_TS_S_LG) << 29);
		/* L=1 => tresume, L=0 => tsuspend */
		अगर (instr & (1 << 21)) अणु
			अगर (MSR_TM_SUSPENDED(msr))
				msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		पूर्ण अन्यथा अणु
			अगर (MSR_TM_TRANSACTIONAL(msr))
				msr = (msr & ~MSR_TS_MASK) | MSR_TS_S;
		पूर्ण
		vcpu->arch.shregs.msr = msr;
		वापस RESUME_GUEST;

	/* ignore bit 31, see comment above */
	हाल (PPC_INST_TRECLAIM & PO_XOP_OPCODE_MASK):
		/* check क्रम TM disabled in the HFSCR or MSR */
		अगर (!(vcpu->arch.hfscr & HFSCR_TM)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		अगर (!(msr & MSR_TM)) अणु
			/* generate a facility unavailable पूर्णांकerrupt */
			vcpu->arch.fscr = (vcpu->arch.fscr & ~(0xffull << 56)) |
				((u64)FSCR_TM_LG << 56);
			kvmppc_book3s_queue_irqprio(vcpu,
						BOOK3S_INTERRUPT_FAC_UNAVAIL);
			वापस RESUME_GUEST;
		पूर्ण
		/* If no transaction active, generate TM bad thing */
		अगर (!MSR_TM_ACTIVE(msr)) अणु
			kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
			वापस RESUME_GUEST;
		पूर्ण
		/* If failure was not previously recorded, recompute TEXASR */
		अगर (!(vcpu->arch.orig_texasr & TEXASR_FS)) अणु
			ra = (instr >> 16) & 0x1f;
			अगर (ra)
				ra = kvmppc_get_gpr(vcpu, ra) & 0xff;
			emulate_tx_failure(vcpu, ra);
		पूर्ण

		copy_from_checkpoपूर्णांक(vcpu);

		/* Set CR0 to indicate previous transactional state */
		vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) |
			(((msr & MSR_TS_MASK) >> MSR_TS_S_LG) << 29);
		vcpu->arch.shregs.msr &= ~MSR_TS_MASK;
		वापस RESUME_GUEST;

	/* ignore bit 31, see comment above */
	हाल (PPC_INST_TRECHKPT & PO_XOP_OPCODE_MASK):
		/* XXX करो we need to check क्रम PR=0 here? */
		/* check क्रम TM disabled in the HFSCR or MSR */
		अगर (!(vcpu->arch.hfscr & HFSCR_TM)) अणु
			/* generate an illegal inकाष्ठाion पूर्णांकerrupt */
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			वापस RESUME_GUEST;
		पूर्ण
		अगर (!(msr & MSR_TM)) अणु
			/* generate a facility unavailable पूर्णांकerrupt */
			vcpu->arch.fscr = (vcpu->arch.fscr & ~(0xffull << 56)) |
				((u64)FSCR_TM_LG << 56);
			kvmppc_book3s_queue_irqprio(vcpu,
						BOOK3S_INTERRUPT_FAC_UNAVAIL);
			वापस RESUME_GUEST;
		पूर्ण
		/* If transaction active or TEXASR[FS] = 0, bad thing */
		अगर (MSR_TM_ACTIVE(msr) || !(vcpu->arch.texasr & TEXASR_FS)) अणु
			kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
			वापस RESUME_GUEST;
		पूर्ण

		copy_to_checkpoपूर्णांक(vcpu);

		/* Set CR0 to indicate previous transactional state */
		vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) |
			(((msr & MSR_TS_MASK) >> MSR_TS_S_LG) << 29);
		vcpu->arch.shregs.msr = msr | MSR_TS_S;
		वापस RESUME_GUEST;
	पूर्ण

	/* What should we करो here? We didn't recognize the inकाष्ठाion */
	kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
	pr_warn_ratelimited("Unrecognized TM-related instruction %#x for emulation", instr);

	वापस RESUME_GUEST;
पूर्ण
