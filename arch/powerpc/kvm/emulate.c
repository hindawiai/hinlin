<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2007
 * Copyright 2011 Freescale Semiconductor, Inc.
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm_host.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश "timing.h"
#समावेश "trace.h"

व्योम kvmppc_emulate_dec(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ dec_nsec;
	अचिन्हित दीर्घ दीर्घ dec_समय;

	pr_debug("mtDEC: %lx\n", vcpu->arch.dec);
	hrसमयr_try_to_cancel(&vcpu->arch.dec_समयr);

#अगर_घोषित CONFIG_PPC_BOOK3S
	/* mtdec lowers the पूर्णांकerrupt line when positive. */
	kvmppc_core_dequeue_dec(vcpu);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOKE
	/* On BOOKE, DEC = 0 is as good as decrementer not enabled */
	अगर (vcpu->arch.dec == 0)
		वापस;
#पूर्ण_अगर

	/*
	 * The decrementer ticks at the same rate as the समयbase, so
	 * that's how we convert the guest DEC value to the number of
	 * host ticks.
	 */

	dec_समय = vcpu->arch.dec;
	/*
	 * Guest समयbase ticks at the same frequency as host समयbase.
	 * So use the host समयbase calculations क्रम decrementer emulation.
	 */
	dec_समय = tb_to_ns(dec_समय);
	dec_nsec = करो_भाग(dec_समय, NSEC_PER_SEC);
	hrसमयr_start(&vcpu->arch.dec_समयr,
		kसमय_set(dec_समय, dec_nsec), HRTIMER_MODE_REL);
	vcpu->arch.dec_jअगरfies = get_tb();
पूर्ण

u32 kvmppc_get_dec(काष्ठा kvm_vcpu *vcpu, u64 tb)
अणु
	u64 jd = tb - vcpu->arch.dec_jअगरfies;

#अगर_घोषित CONFIG_BOOKE
	अगर (vcpu->arch.dec < jd)
		वापस 0;
#पूर्ण_अगर

	वापस vcpu->arch.dec - jd;
पूर्ण

अटल पूर्णांक kvmppc_emulate_mtspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, पूर्णांक rs)
अणु
	क्रमागत emulation_result emulated = EMULATE_DONE;
	uदीर्घ spr_val = kvmppc_get_gpr(vcpu, rs);

	चयन (sprn) अणु
	हाल SPRN_SRR0:
		kvmppc_set_srr0(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SRR1:
		kvmppc_set_srr1(vcpu, spr_val);
		अवरोध;

	/* XXX We need to context-चयन the समयbase क्रम
	 * watchकरोg and FIT. */
	हाल SPRN_TBWL: अवरोध;
	हाल SPRN_TBWU: अवरोध;

	हाल SPRN_DEC:
		vcpu->arch.dec = (u32) spr_val;
		kvmppc_emulate_dec(vcpu);
		अवरोध;

	हाल SPRN_SPRG0:
		kvmppc_set_sprg0(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG1:
		kvmppc_set_sprg1(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG2:
		kvmppc_set_sprg2(vcpu, spr_val);
		अवरोध;
	हाल SPRN_SPRG3:
		kvmppc_set_sprg3(vcpu, spr_val);
		अवरोध;

	/* PIR can legally be written, but we ignore it */
	हाल SPRN_PIR: अवरोध;

	शेष:
		emulated = vcpu->kvm->arch.kvm_ops->emulate_mtspr(vcpu, sprn,
								  spr_val);
		अगर (emulated == EMULATE_FAIL)
			prपूर्णांकk(KERN_INFO "mtspr: unknown spr "
				"0x%x\n", sprn);
		अवरोध;
	पूर्ण

	kvmppc_set_निकास_type(vcpu, EMULATED_MTSPR_EXITS);

	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_mfspr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, पूर्णांक rt)
अणु
	क्रमागत emulation_result emulated = EMULATE_DONE;
	uदीर्घ spr_val = 0;

	चयन (sprn) अणु
	हाल SPRN_SRR0:
		spr_val = kvmppc_get_srr0(vcpu);
		अवरोध;
	हाल SPRN_SRR1:
		spr_val = kvmppc_get_srr1(vcpu);
		अवरोध;
	हाल SPRN_PVR:
		spr_val = vcpu->arch.pvr;
		अवरोध;
	हाल SPRN_PIR:
		spr_val = vcpu->vcpu_id;
		अवरोध;

	/* Note: mftb and TBRL/TBWL are user-accessible, so
	 * the guest can always access the real TB anyways.
	 * In fact, we probably will never see these traps. */
	हाल SPRN_TBWL:
		spr_val = get_tb() >> 32;
		अवरोध;
	हाल SPRN_TBWU:
		spr_val = get_tb();
		अवरोध;

	हाल SPRN_SPRG0:
		spr_val = kvmppc_get_sprg0(vcpu);
		अवरोध;
	हाल SPRN_SPRG1:
		spr_val = kvmppc_get_sprg1(vcpu);
		अवरोध;
	हाल SPRN_SPRG2:
		spr_val = kvmppc_get_sprg2(vcpu);
		अवरोध;
	हाल SPRN_SPRG3:
		spr_val = kvmppc_get_sprg3(vcpu);
		अवरोध;
	/* Note: SPRG4-7 are user-पढ़ोable, so we करोn't get
	 * a trap. */

	हाल SPRN_DEC:
		spr_val = kvmppc_get_dec(vcpu, get_tb());
		अवरोध;
	शेष:
		emulated = vcpu->kvm->arch.kvm_ops->emulate_mfspr(vcpu, sprn,
								  &spr_val);
		अगर (unlikely(emulated == EMULATE_FAIL)) अणु
			prपूर्णांकk(KERN_INFO "mfspr: unknown spr "
				"0x%x\n", sprn);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (emulated == EMULATE_DONE)
		kvmppc_set_gpr(vcpu, rt, spr_val);
	kvmppc_set_निकास_type(vcpu, EMULATED_MFSPR_EXITS);

	वापस emulated;
पूर्ण

/* XXX Should probably स्वतः-generate inकाष्ठाion decoding क्रम a particular core
 * from opcode tables in the future. */
पूर्णांक kvmppc_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 inst;
	पूर्णांक rs, rt, sprn;
	क्रमागत emulation_result emulated;
	पूर्णांक advance = 1;

	/* this शेष type might be overwritten by subcategories */
	kvmppc_set_निकास_type(vcpu, EMULATED_INST_EXITS);

	emulated = kvmppc_get_last_inst(vcpu, INST_GENERIC, &inst);
	अगर (emulated != EMULATE_DONE)
		वापस emulated;

	pr_debug("Emulating opcode %d / %d\n", get_op(inst), get_xop(inst));

	rs = get_rs(inst);
	rt = get_rt(inst);
	sprn = get_sprn(inst);

	चयन (get_op(inst)) अणु
	हाल OP_TRAP:
#अगर_घोषित CONFIG_PPC_BOOK3S
	हाल OP_TRAP_64:
		kvmppc_core_queue_program(vcpu, SRR1_PROGTRAP);
#अन्यथा
		kvmppc_core_queue_program(vcpu,
					  vcpu->arch.shared->esr | ESR_PTR);
#पूर्ण_अगर
		advance = 0;
		अवरोध;

	हाल 31:
		चयन (get_xop(inst)) अणु

		हाल OP_31_XOP_TRAP:
#अगर_घोषित CONFIG_64BIT
		हाल OP_31_XOP_TRAP_64:
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S
			kvmppc_core_queue_program(vcpu, SRR1_PROGTRAP);
#अन्यथा
			kvmppc_core_queue_program(vcpu,
					vcpu->arch.shared->esr | ESR_PTR);
#पूर्ण_अगर
			advance = 0;
			अवरोध;

		हाल OP_31_XOP_MFSPR:
			emulated = kvmppc_emulate_mfspr(vcpu, sprn, rt);
			अगर (emulated == EMULATE_AGAIN) अणु
				emulated = EMULATE_DONE;
				advance = 0;
			पूर्ण
			अवरोध;

		हाल OP_31_XOP_MTSPR:
			emulated = kvmppc_emulate_mtspr(vcpu, sprn, rs);
			अगर (emulated == EMULATE_AGAIN) अणु
				emulated = EMULATE_DONE;
				advance = 0;
			पूर्ण
			अवरोध;

		हाल OP_31_XOP_TLBSYNC:
			अवरोध;

		शेष:
			/* Attempt core-specअगरic emulation below. */
			emulated = EMULATE_FAIL;
		पूर्ण
		अवरोध;

	हाल 0:
		/*
		 * Inकाष्ठाion with primary opcode 0. Based on PowerISA
		 * these are illegal inकाष्ठाions.
		 */
		अगर (inst == KVMPPC_INST_SW_BREAKPOINT) अणु
			vcpu->run->निकास_reason = KVM_EXIT_DEBUG;
			vcpu->run->debug.arch.status = 0;
			vcpu->run->debug.arch.address = kvmppc_get_pc(vcpu);
			emulated = EMULATE_EXIT_USER;
			advance = 0;
		पूर्ण अन्यथा
			emulated = EMULATE_FAIL;

		अवरोध;

	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	अगर (emulated == EMULATE_FAIL) अणु
		emulated = vcpu->kvm->arch.kvm_ops->emulate_op(vcpu, inst,
							       &advance);
		अगर (emulated == EMULATE_AGAIN) अणु
			advance = 0;
		पूर्ण अन्यथा अगर (emulated == EMULATE_FAIL) अणु
			advance = 0;
			prपूर्णांकk(KERN_ERR "Couldn't emulate instruction 0x%08x "
			       "(op %d xop %d)\n", inst, get_op(inst), get_xop(inst));
		पूर्ण
	पूर्ण

	trace_kvm_ppc_instr(inst, kvmppc_get_pc(vcpu), emulated);

	/* Advance past emulated inकाष्ठाion. */
	अगर (advance)
		kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);

	वापस emulated;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_emulate_inकाष्ठाion);
