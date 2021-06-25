<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu, <yu.liu@मुक्तscale.com>
 *
 * Description:
 * This file is derived from arch/घातerpc/kvm/44x_emulate.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/reg_booke.h>

#समावेश "booke.h"
#समावेश "e500.h"

#घोषणा XOP_DCBTLS  166
#घोषणा XOP_MSGSND  206
#घोषणा XOP_MSGCLR  238
#घोषणा XOP_MFTMR   366
#घोषणा XOP_TLBIVAX 786
#घोषणा XOP_TLBSX   914
#घोषणा XOP_TLBRE   946
#घोषणा XOP_TLBWE   978
#घोषणा XOP_TLBILX  18
#घोषणा XOP_EHPRIV  270

#अगर_घोषित CONFIG_KVM_E500MC
अटल पूर्णांक dbell2prio(uदीर्घ param)
अणु
	पूर्णांक msg = param & PPC_DBELL_TYPE_MASK;
	पूर्णांक prio = -1;

	चयन (msg) अणु
	हाल PPC_DBELL_TYPE(PPC_DBELL):
		prio = BOOKE_IRQPRIO_DBELL;
		अवरोध;
	हाल PPC_DBELL_TYPE(PPC_DBELL_CRIT):
		prio = BOOKE_IRQPRIO_DBELL_CRIT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस prio;
पूर्ण

अटल पूर्णांक kvmppc_e500_emul_msgclr(काष्ठा kvm_vcpu *vcpu, पूर्णांक rb)
अणु
	uदीर्घ param = vcpu->arch.regs.gpr[rb];
	पूर्णांक prio = dbell2prio(param);

	अगर (prio < 0)
		वापस EMULATE_FAIL;

	clear_bit(prio, &vcpu->arch.pending_exceptions);
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_e500_emul_msgsnd(काष्ठा kvm_vcpu *vcpu, पूर्णांक rb)
अणु
	uदीर्घ param = vcpu->arch.regs.gpr[rb];
	पूर्णांक prio = dbell2prio(rb);
	पूर्णांक pir = param & PPC_DBELL_PIR_MASK;
	पूर्णांक i;
	काष्ठा kvm_vcpu *cvcpu;

	अगर (prio < 0)
		वापस EMULATE_FAIL;

	kvm_क्रम_each_vcpu(i, cvcpu, vcpu->kvm) अणु
		पूर्णांक cpir = cvcpu->arch.shared->pir;
		अगर ((param & PPC_DBELL_MSG_BRDCAST) || (cpir == pir)) अणु
			set_bit(prio, &cvcpu->arch.pending_exceptions);
			kvm_vcpu_kick(cvcpu);
		पूर्ण
	पूर्ण

	वापस EMULATE_DONE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvmppc_e500_emul_ehpriv(काष्ठा kvm_vcpu *vcpu,
				   अचिन्हित पूर्णांक inst, पूर्णांक *advance)
अणु
	पूर्णांक emulated = EMULATE_DONE;

	चयन (get_oc(inst)) अणु
	हाल EHPRIV_OC_DEBUG:
		vcpu->run->निकास_reason = KVM_EXIT_DEBUG;
		vcpu->run->debug.arch.address = vcpu->arch.regs.nip;
		vcpu->run->debug.arch.status = 0;
		kvmppc_account_निकास(vcpu, DEBUG_EXITS);
		emulated = EMULATE_EXIT_USER;
		*advance = 0;
		अवरोध;
	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण
	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_e500_emul_dcbtls(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	/* Always fail to lock the cache */
	vcpu_e500->l1csr0 |= L1CSR0_CUL;
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_e500_emul_mfपंचांगr(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक inst,
				  पूर्णांक rt)
अणु
	/* Expose one thपढ़ो per vcpu */
	अगर (get_पंचांगrn(inst) == TMRN_TMCFG0) अणु
		kvmppc_set_gpr(vcpu, rt,
			       1 | (1 << TMRN_TMCFG0_NATHRD_SHIFT));
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_FAIL;
पूर्ण

पूर्णांक kvmppc_core_emulate_op_e500(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित पूर्णांक inst, पूर्णांक *advance)
अणु
	पूर्णांक emulated = EMULATE_DONE;
	पूर्णांक ra = get_ra(inst);
	पूर्णांक rb = get_rb(inst);
	पूर्णांक rt = get_rt(inst);
	gva_t ea;

	चयन (get_op(inst)) अणु
	हाल 31:
		चयन (get_xop(inst)) अणु

		हाल XOP_DCBTLS:
			emulated = kvmppc_e500_emul_dcbtls(vcpu);
			अवरोध;

#अगर_घोषित CONFIG_KVM_E500MC
		हाल XOP_MSGSND:
			emulated = kvmppc_e500_emul_msgsnd(vcpu, rb);
			अवरोध;

		हाल XOP_MSGCLR:
			emulated = kvmppc_e500_emul_msgclr(vcpu, rb);
			अवरोध;
#पूर्ण_अगर

		हाल XOP_TLBRE:
			emulated = kvmppc_e500_emul_tlbre(vcpu);
			अवरोध;

		हाल XOP_TLBWE:
			emulated = kvmppc_e500_emul_tlbwe(vcpu);
			अवरोध;

		हाल XOP_TLBSX:
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbsx(vcpu, ea);
			अवरोध;

		हाल XOP_TLBILX: अणु
			पूर्णांक type = rt & 0x3;
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbilx(vcpu, type, ea);
			अवरोध;
		पूर्ण

		हाल XOP_TLBIVAX:
			ea = kvmppc_get_ea_indexed(vcpu, ra, rb);
			emulated = kvmppc_e500_emul_tlbivax(vcpu, ea);
			अवरोध;

		हाल XOP_MFTMR:
			emulated = kvmppc_e500_emul_mfपंचांगr(vcpu, inst, rt);
			अवरोध;

		हाल XOP_EHPRIV:
			emulated = kvmppc_e500_emul_ehpriv(vcpu, inst, advance);
			अवरोध;

		शेष:
			emulated = EMULATE_FAIL;
		पूर्ण

		अवरोध;

	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	अगर (emulated == EMULATE_FAIL)
		emulated = kvmppc_booke_emulate_op(vcpu, inst, advance);

	वापस emulated;
पूर्ण

पूर्णांक kvmppc_core_emulate_mtspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ spr_val)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक emulated = EMULATE_DONE;

	चयन (sprn) अणु
#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	हाल SPRN_PID:
		kvmppc_set_pid(vcpu, spr_val);
		अवरोध;
	हाल SPRN_PID1:
		अगर (spr_val != 0)
			वापस EMULATE_FAIL;
		vcpu_e500->pid[1] = spr_val;
		अवरोध;
	हाल SPRN_PID2:
		अगर (spr_val != 0)
			वापस EMULATE_FAIL;
		vcpu_e500->pid[2] = spr_val;
		अवरोध;
	हाल SPRN_MAS0:
		vcpu->arch.shared->mas0 = spr_val;
		अवरोध;
	हाल SPRN_MAS1:
		vcpu->arch.shared->mas1 = spr_val;
		अवरोध;
	हाल SPRN_MAS2:
		vcpu->arch.shared->mas2 = spr_val;
		अवरोध;
	हाल SPRN_MAS3:
		vcpu->arch.shared->mas7_3 &= ~(u64)0xffffffff;
		vcpu->arch.shared->mas7_3 |= spr_val;
		अवरोध;
	हाल SPRN_MAS4:
		vcpu->arch.shared->mas4 = spr_val;
		अवरोध;
	हाल SPRN_MAS6:
		vcpu->arch.shared->mas6 = spr_val;
		अवरोध;
	हाल SPRN_MAS7:
		vcpu->arch.shared->mas7_3 &= (u64)0xffffffff;
		vcpu->arch.shared->mas7_3 |= (u64)spr_val << 32;
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_L1CSR0:
		vcpu_e500->l1csr0 = spr_val;
		vcpu_e500->l1csr0 &= ~(L1CSR0_DCFI | L1CSR0_CLFC);
		अवरोध;
	हाल SPRN_L1CSR1:
		vcpu_e500->l1csr1 = spr_val;
		vcpu_e500->l1csr1 &= ~(L1CSR1_ICFI | L1CSR1_ICLFR);
		अवरोध;
	हाल SPRN_HID0:
		vcpu_e500->hid0 = spr_val;
		अवरोध;
	हाल SPRN_HID1:
		vcpu_e500->hid1 = spr_val;
		अवरोध;

	हाल SPRN_MMUCSR0:
		emulated = kvmppc_e500_emul_mt_mmucsr0(vcpu_e500,
				spr_val);
		अवरोध;

	हाल SPRN_PWRMGTCR0:
		/*
		 * Guest relies on host घातer management configurations
		 * Treat the request as a general store
		 */
		vcpu->arch.pwrmgtcr0 = spr_val;
		अवरोध;

	हाल SPRN_BUCSR:
		/*
		 * If we are here, it means that we have alपढ़ोy flushed the
		 * branch predictor, so just वापस to guest.
		 */
		अवरोध;

	/* extra exceptions */
#अगर_घोषित CONFIG_SPE_POSSIBLE
	हाल SPRN_IVOR32:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR33:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA] = spr_val;
		अवरोध;
	हाल SPRN_IVOR34:
		vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND] = spr_val;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल SPRN_IVOR32:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_UNAVAIL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR33:
		vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_ASSIST] = spr_val;
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_IVOR35:
		vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR] = spr_val;
		अवरोध;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	हाल SPRN_IVOR36:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL] = spr_val;
		अवरोध;
	हाल SPRN_IVOR37:
		vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT] = spr_val;
		अवरोध;
#पूर्ण_अगर
	शेष:
		emulated = kvmppc_booke_emulate_mtspr(vcpu, sprn, spr_val);
	पूर्ण

	वापस emulated;
पूर्ण

पूर्णांक kvmppc_core_emulate_mfspr_e500(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ *spr_val)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक emulated = EMULATE_DONE;

	चयन (sprn) अणु
#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	हाल SPRN_PID:
		*spr_val = vcpu_e500->pid[0];
		अवरोध;
	हाल SPRN_PID1:
		*spr_val = vcpu_e500->pid[1];
		अवरोध;
	हाल SPRN_PID2:
		*spr_val = vcpu_e500->pid[2];
		अवरोध;
	हाल SPRN_MAS0:
		*spr_val = vcpu->arch.shared->mas0;
		अवरोध;
	हाल SPRN_MAS1:
		*spr_val = vcpu->arch.shared->mas1;
		अवरोध;
	हाल SPRN_MAS2:
		*spr_val = vcpu->arch.shared->mas2;
		अवरोध;
	हाल SPRN_MAS3:
		*spr_val = (u32)vcpu->arch.shared->mas7_3;
		अवरोध;
	हाल SPRN_MAS4:
		*spr_val = vcpu->arch.shared->mas4;
		अवरोध;
	हाल SPRN_MAS6:
		*spr_val = vcpu->arch.shared->mas6;
		अवरोध;
	हाल SPRN_MAS7:
		*spr_val = vcpu->arch.shared->mas7_3 >> 32;
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_DECAR:
		*spr_val = vcpu->arch.decar;
		अवरोध;
	हाल SPRN_TLB0CFG:
		*spr_val = vcpu->arch.tlbcfg[0];
		अवरोध;
	हाल SPRN_TLB1CFG:
		*spr_val = vcpu->arch.tlbcfg[1];
		अवरोध;
	हाल SPRN_TLB0PS:
		अगर (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			वापस EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[0];
		अवरोध;
	हाल SPRN_TLB1PS:
		अगर (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			वापस EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[1];
		अवरोध;
	हाल SPRN_L1CSR0:
		*spr_val = vcpu_e500->l1csr0;
		अवरोध;
	हाल SPRN_L1CSR1:
		*spr_val = vcpu_e500->l1csr1;
		अवरोध;
	हाल SPRN_HID0:
		*spr_val = vcpu_e500->hid0;
		अवरोध;
	हाल SPRN_HID1:
		*spr_val = vcpu_e500->hid1;
		अवरोध;
	हाल SPRN_SVR:
		*spr_val = vcpu_e500->svr;
		अवरोध;

	हाल SPRN_MMUCSR0:
		*spr_val = 0;
		अवरोध;

	हाल SPRN_MMUCFG:
		*spr_val = vcpu->arch.mmucfg;
		अवरोध;
	हाल SPRN_EPTCFG:
		अगर (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			वापस EMULATE_FAIL;
		/*
		 * Legacy Linux guests access EPTCFG रेजिस्टर even अगर the E.PT
		 * category is disabled in the VM. Give them a chance to live.
		 */
		*spr_val = vcpu->arch.eptcfg;
		अवरोध;

	हाल SPRN_PWRMGTCR0:
		*spr_val = vcpu->arch.pwrmgtcr0;
		अवरोध;

	/* extra exceptions */
#अगर_घोषित CONFIG_SPE_POSSIBLE
	हाल SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL];
		अवरोध;
	हाल SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA];
		अवरोध;
	हाल SPRN_IVOR34:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND];
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_UNAVAIL];
		अवरोध;
	हाल SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_ASSIST];
		अवरोध;
#पूर्ण_अगर
	हाल SPRN_IVOR35:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR];
		अवरोध;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	हाल SPRN_IVOR36:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL];
		अवरोध;
	हाल SPRN_IVOR37:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT];
		अवरोध;
#पूर्ण_अगर
	शेष:
		emulated = kvmppc_booke_emulate_mfspr(vcpu, sprn, spr_val);
	पूर्ण

	वापस emulated;
पूर्ण

