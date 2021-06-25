<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_book3s_64.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/ppc-opcode.h>

/*
 * This handles the हालs where the guest is in real suspend mode
 * and we want to get back to the guest without करोoming the transaction.
 * The caller has checked that the guest is in real-suspend mode
 * (MSR[TS] = S and the fake-suspend flag is not set).
 */
पूर्णांक kvmhv_p9_पंचांग_emulation_early(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 instr = vcpu->arch.emul_inst;
	u64 newmsr, msr, bescr;
	पूर्णांक rs;

	/*
	 * rfid, rfebb, and mपंचांगsrd encode bit 31 = 0 since it's a reserved bit
	 * in these inकाष्ठाions, so masking bit 31 out करोesn't change these
	 * inकाष्ठाions. For the tsr. inकाष्ठाion अगर bit 31 = 0 then it is per
	 * ISA an invalid क्रमm, however P9 UM, in section 4.6.10 Book II Invalid
	 * Forms, inक्रमms specअगरically that ignoring bit 31 is an acceptable way
	 * to handle TM-related invalid क्रमms that have bit 31 = 0. Moreover,
	 * क्रम emulation purposes both क्रमms (w/ and wo/ bit 31 set) can
	 * generate a softpatch पूर्णांकerrupt. Hence both क्रमms are handled below
	 * क्रम tsr. to make them behave the same way.
	 */
	चयन (instr & PO_XOP_OPCODE_MASK) अणु
	हाल PPC_INST_RFID:
		/* XXX करो we need to check क्रम PR=0 here? */
		newmsr = vcpu->arch.shregs.srr1;
		/* should only get here क्रम Sx -> T1 transition */
		अगर (!(MSR_TM_TRANSACTIONAL(newmsr) && (newmsr & MSR_TM)))
			वापस 0;
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = vcpu->arch.shregs.srr0;
		वापस 1;

	हाल PPC_INST_RFEBB:
		/* check क्रम PR=1 and arch 2.06 bit set in PCR */
		msr = vcpu->arch.shregs.msr;
		अगर ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206))
			वापस 0;
		/* check EBB facility is available */
		अगर (!(vcpu->arch.hfscr & HFSCR_EBB) ||
		    ((msr & MSR_PR) && !(mfspr(SPRN_FSCR) & FSCR_EBB)))
			वापस 0;
		bescr = mfspr(SPRN_BESCR);
		/* expect to see a S->T transition requested */
		अगर (((bescr >> 30) & 3) != 2)
			वापस 0;
		bescr &= ~BESCR_GE;
		अगर (instr & (1 << 11))
			bescr |= BESCR_GE;
		mtspr(SPRN_BESCR, bescr);
		msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		vcpu->arch.shregs.msr = msr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = mfspr(SPRN_EBBRR);
		वापस 1;

	हाल PPC_INST_MTMSRD:
		/* XXX करो we need to check क्रम PR=0 here? */
		rs = (instr >> 21) & 0x1f;
		newmsr = kvmppc_get_gpr(vcpu, rs);
		msr = vcpu->arch.shregs.msr;
		/* check this is a Sx -> T1 transition */
		अगर (!(MSR_TM_TRANSACTIONAL(newmsr) && (newmsr & MSR_TM)))
			वापस 0;
		/* mपंचांगsrd करोesn't change LE */
		newmsr = (newmsr & ~MSR_LE) | (msr & MSR_LE);
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		वापस 1;

	/* ignore bit 31, see comment above */
	हाल (PPC_INST_TSR & PO_XOP_OPCODE_MASK):
		/* we know the MSR has the TS field = S (0b01) here */
		msr = vcpu->arch.shregs.msr;
		/* check क्रम PR=1 and arch 2.06 bit set in PCR */
		अगर ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206))
			वापस 0;
		/* check क्रम TM disabled in the HFSCR or MSR */
		अगर (!(vcpu->arch.hfscr & HFSCR_TM) || !(msr & MSR_TM))
			वापस 0;
		/* L=1 => tresume => set TS to T (0b10) */
		अगर (instr & (1 << 21))
			vcpu->arch.shregs.msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		/* Set CR0 to 0b0010 */
		vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) |
			0x20000000;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This is called when we are वापसing to a guest in TM transactional
 * state.  We roll the guest state back to the checkpoपूर्णांकed state.
 */
व्योम kvmhv_emulate_पंचांग_rollback(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.shregs.msr &= ~MSR_TS_MASK;	/* go to N state */
	vcpu->arch.regs.nip = vcpu->arch.tfhar;
	copy_from_checkpoपूर्णांक(vcpu);
	vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) | 0xa0000000;
पूर्ण
