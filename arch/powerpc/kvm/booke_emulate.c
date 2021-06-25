<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2008
 * Copyright 2011 Freescale Semiconductor, Inc.
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/disassemble.h>

#समावेश "booke.h"

#घोषणा OP_19_XOP_RFI     50
#घोषणा OP_19_XOP_RFCI    51
#घोषणा OP_19_XOP_RFDI    39

#घोषणा OP_31_XOP_MFMSR   83
#घोषणा OP_31_XOP_WRTEE   131
#घोषणा OP_31_XOP_MTMSR   146
#घोषणा OP_31_XOP_WRTEEI  163

अटल व्योम kvmppc_emul_rfi(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.regs.nip = vcpu->arch.shared->srr0;
	kvmppc_set_msr(vcpu, vcpu->arch.shared->srr1);
पूर्ण

अटल व्योम kvmppc_emul_rfdi(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.regs.nip = vcpu->arch.dsrr0;
	kvmppc_set_msr(vcpu, vcpu->arch.dsrr1);
पूर्ण

अटल व्योम kvmppc_emul_rfci(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.regs.nip = vcpu->arch.csrr0;
	kvmppc_set_msr(vcpu, vcpu->arch.csrr1);
पूर्ण

पूर्णांक kvmppc_booke_emulate_op(काष्ठा kvm_vcpu *vcpu,
                            अचिन्हित पूर्णांक inst, पूर्णांक *advance)
अणु
	पूर्णांक emulated = EMULATE_DONE;
	पूर्णांक rs = get_rs(inst);
	पूर्णांक rt = get_rt(inst);

	चयन (get_op(inst)) अणु
	हाल 19:
		चयन (get_xop(inst)) अणु
		हाल OP_19_XOP_RFI:
			kvmppc_emul_rfi(vcpu);
			kvmppc_set_निकास_type(vcpu, EMULATED_RFI_EXITS);
			*advance = 0;
			अवरोध;

		हाल OP_19_XOP_RFCI:
			kvmppc_emul_rfci(vcpu);
			kvmppc_set_निकास_type(vcpu, EMULATED_RFCI_EXITS);
			*advance = 0;
			अवरोध;

		हाल OP_19_XOP_RFDI:
			kvmppc_emul_rfdi(vcpu);
			kvmppc_set_निकास_type(vcpu, EMULATED_RFDI_EXITS);
			*advance = 0;
			अवरोध;

		शेष:
			emulated = EMULATE_FAIL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 31:
		चयन (get_xop(inst)) अणु

		हाल OP_31_XOP_MFMSR:
			kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->msr);
			kvmppc_set_निकास_type(vcpu, EMULATED_MFMSR_EXITS);
			अवरोध;

		हाल OP_31_XOP_MTMSR:
			kvmppc_set_निकास_type(vcpu, EMULATED_MTMSR_EXITS);
			kvmppc_set_msr(vcpu, kvmppc_get_gpr(vcpu, rs));
			अवरोध;

		हाल OP_31_XOP_WRTEE:
			vcpu->arch.shared->msr = (vcpu->arch.shared->msr & ~MSR_EE)
					| (kvmppc_get_gpr(vcpu, rs) & MSR_EE);
			kvmppc_set_निकास_type(vcpu, EMULATED_WRTEE_EXITS);
			अवरोध;

		हाल OP_31_XOP_WRTEEI:
			vcpu->arch.shared->msr = (vcpu->arch.shared->msr & ~MSR_EE)
							 | (inst & MSR_EE);
			kvmppc_set_निकास_type(vcpu, EMULATED_WRTEE_EXITS);
			अवरोध;

		शेष:
			emulated = EMULATE_FAIL;
		पूर्ण

		अवरोध;

	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	वापस emulated;
पूर्ण

/*
 * NOTE: some of these रेजिस्टरs are not emulated on BOOKE_HV (GS-mode).
 * Their backing store is in real रेजिस्टरs, and these functions
 * will वापस the wrong result अगर called क्रम them in another context
 * (such as debugging).
 */
पूर्णांक kvmppc_booke_emulate_mtspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ spr_val)
अणु
	पूर्णांक emulated = EMULATE_DONE;
	bool debug_inst = false;

	चयन (sprn) अणु
	हाल SPRN_DEAR:
		vcpu->arch.shared->dar = spr_val;
		अवरोध;
	हाल SPRN_ESR:
		vcpu->arch.shared->esr = spr_val;
		अवरोध;
	हाल SPRN_CSRR0:
		vcpu->arch.csrr0 = spr_val;
		अवरोध;
	हाल SPRN_CSRR1:
		vcpu->arch.csrr1 = spr_val;
		अवरोध;
	हाल SPRN_DSRR0:
		vcpu->arch.dsrr0 = spr_val;
		अवरोध;
	हाल SPRN_DSRR1:
		vcpu->arch.dsrr1 = spr_val;
		अवरोध;
	हाल SPRN_IAC1:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.iac1 = spr_val;
		अवरोध;
	हाल SPRN_IAC2:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.iac2 = spr_val;
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल SPRN_IAC3:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.iac3 = spr_val;
		अवरोध;
	हाल SPRN_IAC4:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.iac4 = spr_val;
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_DAC1:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.dac1 = spr_val;
		अवरोध;
	हाल SPRN_DAC2:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.dac2 = spr_val;
		अवरोध;
	हाल SPRN_DBCR0:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		spr_val &= (DBCR0_IDM | DBCR0_IC | DBCR0_BT | DBCR0_TIE |
			DBCR0_IAC1 | DBCR0_IAC2 | DBCR0_IAC3 | DBCR0_IAC4  |
			DBCR0_DAC1R | DBCR0_DAC1W | DBCR0_DAC2R | DBCR0_DAC2W);

		vcpu->arch.dbg_reg.dbcr0 = spr_val;
		अवरोध;
	हाल SPRN_DBCR1:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.dbcr1 = spr_val;
		अवरोध;
	हाल SPRN_DBCR2:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		debug_inst = true;
		vcpu->arch.dbg_reg.dbcr2 = spr_val;
		अवरोध;
	हाल SPRN_DBSR:
		/*
		 * If userspace is debugging guest then guest
		 * can not access debug रेजिस्टरs.
		 */
		अगर (vcpu->guest_debug)
			अवरोध;

		vcpu->arch.dbsr &= ~spr_val;
		अगर (!(vcpu->arch.dbsr & ~DBSR_IDE))
			kvmppc_core_dequeue_debug(vcpu);
		अवरोध;
	हाल SPRN_TSR:
		kvmppc_clr_tsr_bits(vcpu, spr_val);
		अवरोध;
	हाल SPRN_TCR:
		/*
		 * WRC is a 2-bit field that is supposed to preserve its
		 * value once written to non-zero.
		 */
		अगर (vcpu->arch.tcr & TCR_WRC_MASK) अणु
			spr_val &= ~TCR_WRC_MASK;
			spr_val |= vcpu->arch.tcr & TCR_WRC_MASK;
		पूर्ण
		kvmppc_set_tcr(vcpu, spr_val);
		अवरोध;

	हाल SPRN_DECAR:
		vcpu->arch.decar = spr_val;
		अवरोध;
	/*
	 * Note: SPRG4-7 are user-पढ़ोable.
	 * These values are loaded पूर्णांकo the real SPRGs when resuming the
	 * guest (PR-mode only).
	 */
	हाल SPRN_SPRG4:
		kvmppc_set_sprg4(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG5:
		kvmppc_set_sprg5(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG6:
		kvmppc_set_sprg6(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG7:
		kvmppc_set_sprg7(vcpu, spr_val);
		अवरोध;

	हाल SPRN_IVPR:
		vcpu->arch.ivpr = spr_val;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
		mtspr(SPRN_GIVPR, spr_val);
#पूर्ण_अगर
		अवरोध;
	हाल SPRN_IVOR0:
		vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR1:
		vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK] = spr_val;
		अवरोध;
	हाल SPRN_IVOR2:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE] = spr_val;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
		mtspr(SPRN_GIVOR2, spr_val);
#पूर्ण_अगर
		अवरोध;
	हाल SPRN_IVOR3:
		vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE] = spr_val;
		अवरोध;
	हाल SPRN_IVOR4:
		vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR5:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT] = spr_val;
		अवरोध;
	हाल SPRN_IVOR6:
		vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM] = spr_val;
		अवरोध;
	हाल SPRN_IVOR7:
		vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR8:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL] = spr_val;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
		mtspr(SPRN_GIVOR8, spr_val);
#पूर्ण_अगर
		अवरोध;
	हाल SPRN_IVOR9:
		vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR10:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER] = spr_val;
		अवरोध;
	हाल SPRN_IVOR11:
		vcpu->arch.ivor[BOOKE_IRQPRIO_FIT] = spr_val;
		अवरोध;
	हाल SPRN_IVOR12:
		vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG] = spr_val;
		अवरोध;
	हाल SPRN_IVOR13:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS] = spr_val;
		अवरोध;
	हाल SPRN_IVOR14:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS] = spr_val;
		अवरोध;
	हाल SPRN_IVOR15:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG] = spr_val;
		अवरोध;
	हाल SPRN_MCSR:
		vcpu->arch.mcsr &= ~spr_val;
		अवरोध;
#अगर defined(CONFIG_64BIT)
	हाल SPRN_EPCR:
		kvmppc_set_epcr(vcpu, spr_val);
#अगर_घोषित CONFIG_KVM_BOOKE_HV
		mtspr(SPRN_EPCR, vcpu->arch.shaकरोw_epcr);
#पूर्ण_अगर
		अवरोध;
#पूर्ण_अगर
	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	अगर (debug_inst) अणु
		current->thपढ़ो.debug = vcpu->arch.dbg_reg;
		चयन_booke_debug_regs(&vcpu->arch.dbg_reg);
	पूर्ण
	वापस emulated;
पूर्ण

पूर्णांक kvmppc_booke_emulate_mfspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ *spr_val)
अणु
	पूर्णांक emulated = EMULATE_DONE;

	चयन (sprn) अणु
	हाल SPRN_IVPR:
		*spr_val = vcpu->arch.ivpr;
		अवरोध;
	हाल SPRN_DEAR:
		*spr_val = vcpu->arch.shared->dar;
		अवरोध;
	हाल SPRN_ESR:
		*spr_val = vcpu->arch.shared->esr;
		अवरोध;
	हाल SPRN_EPR:
		*spr_val = vcpu->arch.epr;
		अवरोध;
	हाल SPRN_CSRR0:
		*spr_val = vcpu->arch.csrr0;
		अवरोध;
	हाल SPRN_CSRR1:
		*spr_val = vcpu->arch.csrr1;
		अवरोध;
	हाल SPRN_DSRR0:
		*spr_val = vcpu->arch.dsrr0;
		अवरोध;
	हाल SPRN_DSRR1:
		*spr_val = vcpu->arch.dsrr1;
		अवरोध;
	हाल SPRN_IAC1:
		*spr_val = vcpu->arch.dbg_reg.iac1;
		अवरोध;
	हाल SPRN_IAC2:
		*spr_val = vcpu->arch.dbg_reg.iac2;
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल SPRN_IAC3:
		*spr_val = vcpu->arch.dbg_reg.iac3;
		अवरोध;
	हाल SPRN_IAC4:
		*spr_val = vcpu->arch.dbg_reg.iac4;
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_DAC1:
		*spr_val = vcpu->arch.dbg_reg.dac1;
		अवरोध;
	हाल SPRN_DAC2:
		*spr_val = vcpu->arch.dbg_reg.dac2;
		अवरोध;
	हाल SPRN_DBCR0:
		*spr_val = vcpu->arch.dbg_reg.dbcr0;
		अगर (vcpu->guest_debug)
			*spr_val = *spr_val | DBCR0_EDM;
		अवरोध;
	हाल SPRN_DBCR1:
		*spr_val = vcpu->arch.dbg_reg.dbcr1;
		अवरोध;
	हाल SPRN_DBCR2:
		*spr_val = vcpu->arch.dbg_reg.dbcr2;
		अवरोध;
	हाल SPRN_DBSR:
		*spr_val = vcpu->arch.dbsr;
		अवरोध;
	हाल SPRN_TSR:
		*spr_val = vcpu->arch.tsr;
		अवरोध;
	हाल SPRN_TCR:
		*spr_val = vcpu->arch.tcr;
		अवरोध;

	हाल SPRN_IVOR0:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL];
		अवरोध;
	हाल SPRN_IVOR1:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK];
		अवरोध;
	हाल SPRN_IVOR2:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE];
		अवरोध;
	हाल SPRN_IVOR3:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE];
		अवरोध;
	हाल SPRN_IVOR4:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL];
		अवरोध;
	हाल SPRN_IVOR5:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT];
		अवरोध;
	हाल SPRN_IVOR6:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM];
		अवरोध;
	हाल SPRN_IVOR7:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL];
		अवरोध;
	हाल SPRN_IVOR8:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL];
		अवरोध;
	हाल SPRN_IVOR9:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL];
		अवरोध;
	हाल SPRN_IVOR10:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER];
		अवरोध;
	हाल SPRN_IVOR11:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_FIT];
		अवरोध;
	हाल SPRN_IVOR12:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG];
		अवरोध;
	हाल SPRN_IVOR13:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS];
		अवरोध;
	हाल SPRN_IVOR14:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS];
		अवरोध;
	हाल SPRN_IVOR15:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG];
		अवरोध;
	हाल SPRN_MCSR:
		*spr_val = vcpu->arch.mcsr;
		अवरोध;
#अगर defined(CONFIG_64BIT)
	हाल SPRN_EPCR:
		*spr_val = vcpu->arch.epcr;
		अवरोध;
#पूर्ण_अगर

	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	वापस emulated;
पूर्ण
