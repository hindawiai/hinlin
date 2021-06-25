<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पंचांग.h>
#समावेश "book3s.h"
#समावेश <यंत्र/यंत्र-prototypes.h>

#घोषणा OP_19_XOP_RFID		18
#घोषणा OP_19_XOP_RFI		50

#घोषणा OP_31_XOP_MFMSR		83
#घोषणा OP_31_XOP_MTMSR		146
#घोषणा OP_31_XOP_MTMSRD	178
#घोषणा OP_31_XOP_MTSR		210
#घोषणा OP_31_XOP_MTSRIN	242
#घोषणा OP_31_XOP_TLBIEL	274
/* Opcode is officially reserved, reuse it as sc 1 when sc 1 करोesn't trap */
#घोषणा OP_31_XOP_FAKE_SC1	308
#घोषणा OP_31_XOP_SLBMTE	402
#घोषणा OP_31_XOP_SLBIE		434
#घोषणा OP_31_XOP_SLBIA		498
#घोषणा OP_31_XOP_MFSR		595
#घोषणा OP_31_XOP_MFSRIN	659
#घोषणा OP_31_XOP_DCBA		758
#घोषणा OP_31_XOP_SLBMFEV	851
#घोषणा OP_31_XOP_EIOIO		854
#घोषणा OP_31_XOP_SLBMFEE	915
#घोषणा OP_31_XOP_SLBFEE	979

#घोषणा OP_31_XOP_TBEGIN	654
#घोषणा OP_31_XOP_TABORT	910

#घोषणा OP_31_XOP_TRECLAIM	942
#घोषणा OP_31_XOP_TRCHKPT	1006

/* DCBZ is actually 1014, but we patch it to 1010 so we get a trap */
#घोषणा OP_31_XOP_DCBZ		1010

#घोषणा OP_LFS			48
#घोषणा OP_LFD			50
#घोषणा OP_STFS			52
#घोषणा OP_STFD			54

#घोषणा SPRN_GQR0		912
#घोषणा SPRN_GQR1		913
#घोषणा SPRN_GQR2		914
#घोषणा SPRN_GQR3		915
#घोषणा SPRN_GQR4		916
#घोषणा SPRN_GQR5		917
#घोषणा SPRN_GQR6		918
#घोषणा SPRN_GQR7		919

क्रमागत priv_level अणु
	PRIV_PROBLEM = 0,
	PRIV_SUPER = 1,
	PRIV_HYPER = 2,
पूर्ण;

अटल bool spr_allowed(काष्ठा kvm_vcpu *vcpu, क्रमागत priv_level level)
अणु
	/* PAPR VMs only access supervisor SPRs */
	अगर (vcpu->arch.papr_enabled && (level > PRIV_SUPER))
		वापस false;

	/* Limit user space to its own small SPR set */
	अगर ((kvmppc_get_msr(vcpu) & MSR_PR) && level > PRIV_PROBLEM)
		वापस false;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल अंतरभूत व्योम kvmppc_copyto_vcpu_पंचांग(काष्ठा kvm_vcpu *vcpu)
अणु
	स_नकल(&vcpu->arch.gpr_पंचांग[0], &vcpu->arch.regs.gpr[0],
			माप(vcpu->arch.gpr_पंचांग));
	स_नकल(&vcpu->arch.fp_पंचांग, &vcpu->arch.fp,
			माप(काष्ठा thपढ़ो_fp_state));
	स_नकल(&vcpu->arch.vr_पंचांग, &vcpu->arch.vr,
			माप(काष्ठा thपढ़ो_vr_state));
	vcpu->arch.ppr_पंचांग = vcpu->arch.ppr;
	vcpu->arch.dscr_पंचांग = vcpu->arch.dscr;
	vcpu->arch.amr_पंचांग = vcpu->arch.amr;
	vcpu->arch.ctr_पंचांग = vcpu->arch.regs.ctr;
	vcpu->arch.tar_पंचांग = vcpu->arch.tar;
	vcpu->arch.lr_पंचांग = vcpu->arch.regs.link;
	vcpu->arch.cr_पंचांग = vcpu->arch.regs.ccr;
	vcpu->arch.xer_पंचांग = vcpu->arch.regs.xer;
	vcpu->arch.vrsave_पंचांग = vcpu->arch.vrsave;
पूर्ण

अटल अंतरभूत व्योम kvmppc_copyfrom_vcpu_पंचांग(काष्ठा kvm_vcpu *vcpu)
अणु
	स_नकल(&vcpu->arch.regs.gpr[0], &vcpu->arch.gpr_पंचांग[0],
			माप(vcpu->arch.regs.gpr));
	स_नकल(&vcpu->arch.fp, &vcpu->arch.fp_पंचांग,
			माप(काष्ठा thपढ़ो_fp_state));
	स_नकल(&vcpu->arch.vr, &vcpu->arch.vr_पंचांग,
			माप(काष्ठा thपढ़ो_vr_state));
	vcpu->arch.ppr = vcpu->arch.ppr_पंचांग;
	vcpu->arch.dscr = vcpu->arch.dscr_पंचांग;
	vcpu->arch.amr = vcpu->arch.amr_पंचांग;
	vcpu->arch.regs.ctr = vcpu->arch.ctr_पंचांग;
	vcpu->arch.tar = vcpu->arch.tar_पंचांग;
	vcpu->arch.regs.link = vcpu->arch.lr_पंचांग;
	vcpu->arch.regs.ccr = vcpu->arch.cr_पंचांग;
	vcpu->arch.regs.xer = vcpu->arch.xer_पंचांग;
	vcpu->arch.vrsave = vcpu->arch.vrsave_पंचांग;
पूर्ण

अटल व्योम kvmppc_emulate_treclaim(काष्ठा kvm_vcpu *vcpu, पूर्णांक ra_val)
अणु
	अचिन्हित दीर्घ guest_msr = kvmppc_get_msr(vcpu);
	पूर्णांक fc_val = ra_val ? ra_val : 1;
	uपूर्णांक64_t texasr;

	/* CR0 = 0 | MSR[TS] | 0 */
	vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & ~(CR0_MASK << CR0_SHIFT)) |
		(((guest_msr & MSR_TS_MASK) >> (MSR_TS_S_LG - 1))
		 << CR0_SHIFT);

	preempt_disable();
	पंचांग_enable();
	texasr = mfspr(SPRN_TEXASR);
	kvmppc_save_पंचांग_pr(vcpu);
	kvmppc_copyfrom_vcpu_पंचांग(vcpu);

	/* failure recording depends on Failure Summary bit */
	अगर (!(texasr & TEXASR_FS)) अणु
		texasr &= ~TEXASR_FC;
		texasr |= ((u64)fc_val << TEXASR_FC_LG) | TEXASR_FS;

		texasr &= ~(TEXASR_PR | TEXASR_HV);
		अगर (kvmppc_get_msr(vcpu) & MSR_PR)
			texasr |= TEXASR_PR;

		अगर (kvmppc_get_msr(vcpu) & MSR_HV)
			texasr |= TEXASR_HV;

		vcpu->arch.texasr = texasr;
		vcpu->arch.tfiar = kvmppc_get_pc(vcpu);
		mtspr(SPRN_TEXASR, texasr);
		mtspr(SPRN_TFIAR, vcpu->arch.tfiar);
	पूर्ण
	पंचांग_disable();
	/*
	 * treclaim need quit to non-transactional state.
	 */
	guest_msr &= ~(MSR_TS_MASK);
	kvmppc_set_msr(vcpu, guest_msr);
	preempt_enable();

	अगर (vcpu->arch.shaकरोw_fscr & FSCR_TAR)
		mtspr(SPRN_TAR, vcpu->arch.tar);
पूर्ण

अटल व्योम kvmppc_emulate_trchkpt(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ guest_msr = kvmppc_get_msr(vcpu);

	preempt_disable();
	/*
	 * need flush FP/VEC/VSX to vcpu save area beक्रमe
	 * copy.
	 */
	kvmppc_giveup_ext(vcpu, MSR_VSX);
	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);
	kvmppc_copyto_vcpu_पंचांग(vcpu);
	kvmppc_save_पंचांग_sprs(vcpu);

	/*
	 * as a result of trecheckpoपूर्णांक. set TS to suspended.
	 */
	guest_msr &= ~(MSR_TS_MASK);
	guest_msr |= MSR_TS_S;
	kvmppc_set_msr(vcpu, guest_msr);
	kvmppc_restore_पंचांग_pr(vcpu);
	preempt_enable();
पूर्ण

/* emulate tपात. at guest privilege state */
व्योम kvmppc_emulate_tपात(काष्ठा kvm_vcpu *vcpu, पूर्णांक ra_val)
अणु
	/* currently we only emulate tपात. but no emulation of other
	 * tपात variants since there is no kernel usage of them at
	 * present.
	 */
	अचिन्हित दीर्घ guest_msr = kvmppc_get_msr(vcpu);
	uपूर्णांक64_t org_texasr;

	preempt_disable();
	पंचांग_enable();
	org_texasr = mfspr(SPRN_TEXASR);
	पंचांग_पात(ra_val);

	/* CR0 = 0 | MSR[TS] | 0 */
	vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & ~(CR0_MASK << CR0_SHIFT)) |
		(((guest_msr & MSR_TS_MASK) >> (MSR_TS_S_LG - 1))
		 << CR0_SHIFT);

	vcpu->arch.texasr = mfspr(SPRN_TEXASR);
	/* failure recording depends on Failure Summary bit,
	 * and tपात will be treated as nops in non-transactional
	 * state.
	 */
	अगर (!(org_texasr & TEXASR_FS) &&
			MSR_TM_ACTIVE(guest_msr)) अणु
		vcpu->arch.texasr &= ~(TEXASR_PR | TEXASR_HV);
		अगर (guest_msr & MSR_PR)
			vcpu->arch.texasr |= TEXASR_PR;

		अगर (guest_msr & MSR_HV)
			vcpu->arch.texasr |= TEXASR_HV;

		vcpu->arch.tfiar = kvmppc_get_pc(vcpu);
	पूर्ण
	पंचांग_disable();
	preempt_enable();
पूर्ण

#पूर्ण_अगर

पूर्णांक kvmppc_core_emulate_op_pr(काष्ठा kvm_vcpu *vcpu,
			      अचिन्हित पूर्णांक inst, पूर्णांक *advance)
अणु
	पूर्णांक emulated = EMULATE_DONE;
	पूर्णांक rt = get_rt(inst);
	पूर्णांक rs = get_rs(inst);
	पूर्णांक ra = get_ra(inst);
	पूर्णांक rb = get_rb(inst);
	u32 inst_sc = 0x44000002;

	चयन (get_op(inst)) अणु
	हाल 0:
		emulated = EMULATE_FAIL;
		अगर ((kvmppc_get_msr(vcpu) & MSR_LE) &&
		    (inst == swab32(inst_sc))) अणु
			/*
			 * This is the byte reversed syscall inकाष्ठाion of our
			 * hypercall handler. Early versions of LE Linux didn't
			 * swap the inकाष्ठाions correctly and ended up in
			 * illegal inकाष्ठाions.
			 * Just always fail hypercalls on these broken प्रणालीs.
			 */
			kvmppc_set_gpr(vcpu, 3, EV_UNIMPLEMENTED);
			kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
			emulated = EMULATE_DONE;
		पूर्ण
		अवरोध;
	हाल 19:
		चयन (get_xop(inst)) अणु
		हाल OP_19_XOP_RFID:
		हाल OP_19_XOP_RFI: अणु
			अचिन्हित दीर्घ srr1 = kvmppc_get_srr1(vcpu);
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
			अचिन्हित दीर्घ cur_msr = kvmppc_get_msr(vcpu);

			/*
			 * add rules to fit in ISA specअगरication regarding TM
			 * state transistion in TM disable/Suspended state,
			 * and target TM state is TM inactive(00) state. (the
			 * change should be suppressed).
			 */
			अगर (((cur_msr & MSR_TM) == 0) &&
				((srr1 & MSR_TM) == 0) &&
				MSR_TM_SUSPENDED(cur_msr) &&
				!MSR_TM_ACTIVE(srr1))
				srr1 |= MSR_TS_S;
#पूर्ण_अगर
			kvmppc_set_pc(vcpu, kvmppc_get_srr0(vcpu));
			kvmppc_set_msr(vcpu, srr1);
			*advance = 0;
			अवरोध;
		पूर्ण

		शेष:
			emulated = EMULATE_FAIL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 31:
		चयन (get_xop(inst)) अणु
		हाल OP_31_XOP_MFMSR:
			kvmppc_set_gpr(vcpu, rt, kvmppc_get_msr(vcpu));
			अवरोध;
		हाल OP_31_XOP_MTMSRD:
		अणु
			uदीर्घ rs_val = kvmppc_get_gpr(vcpu, rs);
			अगर (inst & 0x10000) अणु
				uदीर्घ new_msr = kvmppc_get_msr(vcpu);
				new_msr &= ~(MSR_RI | MSR_EE);
				new_msr |= rs_val & (MSR_RI | MSR_EE);
				kvmppc_set_msr_fast(vcpu, new_msr);
			पूर्ण अन्यथा
				kvmppc_set_msr(vcpu, rs_val);
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_MTMSR:
			kvmppc_set_msr(vcpu, kvmppc_get_gpr(vcpu, rs));
			अवरोध;
		हाल OP_31_XOP_MFSR:
		अणु
			पूर्णांक srnum;

			srnum = kvmppc_get_field(inst, 12 + 32, 15 + 32);
			अगर (vcpu->arch.mmu.mfsrin) अणु
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_MFSRIN:
		अणु
			पूर्णांक srnum;

			srnum = (kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf;
			अगर (vcpu->arch.mmu.mfsrin) अणु
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_MTSR:
			vcpu->arch.mmu.mtsrin(vcpu,
				(inst >> 16) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			अवरोध;
		हाल OP_31_XOP_MTSRIN:
			vcpu->arch.mmu.mtsrin(vcpu,
				(kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			अवरोध;
		हाल OP_31_XOP_TLBIE:
		हाल OP_31_XOP_TLBIEL:
		अणु
			bool large = (inst & 0x00200000) ? true : false;
			uदीर्घ addr = kvmppc_get_gpr(vcpu, rb);
			vcpu->arch.mmu.tlbie(vcpu, addr, large);
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_PPC_BOOK3S_64
		हाल OP_31_XOP_FAKE_SC1:
		अणु
			/* SC 1 papr hypercalls */
			uदीर्घ cmd = kvmppc_get_gpr(vcpu, 3);
			पूर्णांक i;

		        अगर ((kvmppc_get_msr(vcpu) & MSR_PR) ||
			    !vcpu->arch.papr_enabled) अणु
				emulated = EMULATE_FAIL;
				अवरोध;
			पूर्ण

			अगर (kvmppc_h_pr(vcpu, cmd) == EMULATE_DONE)
				अवरोध;

			vcpu->run->papr_hcall.nr = cmd;
			क्रम (i = 0; i < 9; ++i) अणु
				uदीर्घ gpr = kvmppc_get_gpr(vcpu, 4 + i);
				vcpu->run->papr_hcall.args[i] = gpr;
			पूर्ण

			vcpu->run->निकास_reason = KVM_EXIT_PAPR_HCALL;
			vcpu->arch.hcall_needed = 1;
			emulated = EMULATE_EXIT_USER;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		हाल OP_31_XOP_EIOIO:
			अवरोध;
		हाल OP_31_XOP_SLBMTE:
			अगर (!vcpu->arch.mmu.slbmte)
				वापस EMULATE_FAIL;

			vcpu->arch.mmu.slbmte(vcpu,
					kvmppc_get_gpr(vcpu, rs),
					kvmppc_get_gpr(vcpu, rb));
			अवरोध;
		हाल OP_31_XOP_SLBIE:
			अगर (!vcpu->arch.mmu.slbie)
				वापस EMULATE_FAIL;

			vcpu->arch.mmu.slbie(vcpu,
					kvmppc_get_gpr(vcpu, rb));
			अवरोध;
		हाल OP_31_XOP_SLBIA:
			अगर (!vcpu->arch.mmu.slbia)
				वापस EMULATE_FAIL;

			vcpu->arch.mmu.slbia(vcpu);
			अवरोध;
		हाल OP_31_XOP_SLBFEE:
			अगर (!(inst & 1) || !vcpu->arch.mmu.slbfee) अणु
				वापस EMULATE_FAIL;
			पूर्ण अन्यथा अणु
				uदीर्घ b, t;
				uदीर्घ cr = kvmppc_get_cr(vcpu) & ~CR0_MASK;

				b = kvmppc_get_gpr(vcpu, rb);
				अगर (!vcpu->arch.mmu.slbfee(vcpu, b, &t))
					cr |= 2 << CR0_SHIFT;
				kvmppc_set_gpr(vcpu, rt, t);
				/* copy XER[SO] bit to CR0[SO] */
				cr |= (vcpu->arch.regs.xer & 0x80000000) >>
					(31 - CR0_SHIFT);
				kvmppc_set_cr(vcpu, cr);
			पूर्ण
			अवरोध;
		हाल OP_31_XOP_SLBMFEE:
			अगर (!vcpu->arch.mmu.slbmfee) अणु
				emulated = EMULATE_FAIL;
			पूर्ण अन्यथा अणु
				uदीर्घ t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfee(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			पूर्ण
			अवरोध;
		हाल OP_31_XOP_SLBMFEV:
			अगर (!vcpu->arch.mmu.slbmfev) अणु
				emulated = EMULATE_FAIL;
			पूर्ण अन्यथा अणु
				uदीर्घ t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfev(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			पूर्ण
			अवरोध;
		हाल OP_31_XOP_DCBA:
			/* Gets treated as NOP */
			अवरोध;
		हाल OP_31_XOP_DCBZ:
		अणु
			uदीर्घ rb_val = kvmppc_get_gpr(vcpu, rb);
			uदीर्घ ra_val = 0;
			uदीर्घ addr, vaddr;
			u32 zeros[8] = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
			u32 dsisr;
			पूर्णांक r;

			अगर (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);

			addr = (ra_val + rb_val) & ~31ULL;
			अगर (!(kvmppc_get_msr(vcpu) & MSR_SF))
				addr &= 0xffffffff;
			vaddr = addr;

			r = kvmppc_st(vcpu, &addr, 32, zeros, true);
			अगर ((r == -ENOENT) || (r == -EPERM)) अणु
				*advance = 0;
				kvmppc_set_dar(vcpu, vaddr);
				vcpu->arch.fault_dar = vaddr;

				dsisr = DSISR_ISSTORE;
				अगर (r == -ENOENT)
					dsisr |= DSISR_NOHPTE;
				अन्यथा अगर (r == -EPERM)
					dsisr |= DSISR_PROTFAULT;

				kvmppc_set_dsisr(vcpu, dsisr);
				vcpu->arch.fault_dsisr = dsisr;

				kvmppc_book3s_queue_irqprio(vcpu,
					BOOK3S_INTERRUPT_DATA_STORAGE);
			पूर्ण

			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
		हाल OP_31_XOP_TBEGIN:
		अणु
			अगर (!cpu_has_feature(CPU_FTR_TM))
				अवरोध;

			अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
				kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			अगर (!(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
				preempt_disable();
				vcpu->arch.regs.ccr = (CR0_TBEGIN_FAILURE |
				  (vcpu->arch.regs.ccr & ~(CR0_MASK << CR0_SHIFT)));

				vcpu->arch.texasr = (TEXASR_FS | TEXASR_EXACT |
					(((u64)(TM_CAUSE_EMULATE | TM_CAUSE_PERSISTENT))
						 << TEXASR_FC_LG));

				अगर ((inst >> 21) & 0x1)
					vcpu->arch.texasr |= TEXASR_ROT;

				अगर (kvmppc_get_msr(vcpu) & MSR_HV)
					vcpu->arch.texasr |= TEXASR_HV;

				vcpu->arch.tfhar = kvmppc_get_pc(vcpu) + 4;
				vcpu->arch.tfiar = kvmppc_get_pc(vcpu);

				kvmppc_restore_पंचांग_sprs(vcpu);
				preempt_enable();
			पूर्ण अन्यथा
				emulated = EMULATE_FAIL;
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_TABORT:
		अणु
			uदीर्घ guest_msr = kvmppc_get_msr(vcpu);
			अचिन्हित दीर्घ ra_val = 0;

			अगर (!cpu_has_feature(CPU_FTR_TM))
				अवरोध;

			अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
				kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			/* only emulate क्रम privilege guest, since problem state
			 * guest can run with TM enabled and we करोn't expect to
			 * trap at here क्रम that हाल.
			 */
			WARN_ON(guest_msr & MSR_PR);

			अगर (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);

			kvmppc_emulate_tपात(vcpu, ra_val);
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_TRECLAIM:
		अणु
			uदीर्घ guest_msr = kvmppc_get_msr(vcpu);
			अचिन्हित दीर्घ ra_val = 0;

			अगर (!cpu_has_feature(CPU_FTR_TM))
				अवरोध;

			अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
				kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			/* generate पूर्णांकerrupts based on priorities */
			अगर (guest_msr & MSR_PR) अणु
				/* Privileged Inकाष्ठाion type Program Interrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			अगर (!MSR_TM_ACTIVE(guest_msr)) अणु
				/* TM bad thing पूर्णांकerrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			अगर (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);
			kvmppc_emulate_treclaim(vcpu, ra_val);
			अवरोध;
		पूर्ण
		हाल OP_31_XOP_TRCHKPT:
		अणु
			uदीर्घ guest_msr = kvmppc_get_msr(vcpu);
			अचिन्हित दीर्घ texasr;

			अगर (!cpu_has_feature(CPU_FTR_TM))
				अवरोध;

			अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
				kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			/* generate पूर्णांकerrupt based on priorities */
			अगर (guest_msr & MSR_PR) अणु
				/* Privileged Inकाष्ठाion type Program Intr */
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			पंचांग_enable();
			texasr = mfspr(SPRN_TEXASR);
			पंचांग_disable();

			अगर (MSR_TM_ACTIVE(guest_msr) ||
				!(texasr & (TEXASR_FS))) अणु
				/* TM bad thing पूर्णांकerrupt */
				kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
				emulated = EMULATE_AGAIN;
				अवरोध;
			पूर्ण

			kvmppc_emulate_trchkpt(vcpu);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		शेष:
			emulated = EMULATE_FAIL;
		पूर्ण
		अवरोध;
	शेष:
		emulated = EMULATE_FAIL;
	पूर्ण

	अगर (emulated == EMULATE_FAIL)
		emulated = kvmppc_emulate_paired_single(vcpu);

	वापस emulated;
पूर्ण

व्योम kvmppc_set_bat(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_bat *bat, bool upper,
                    u32 val)
अणु
	अगर (upper) अणु
		/* Upper BAT */
		u32 bl = (val >> 2) & 0x7ff;
		bat->bepi_mask = (~bl << 17);
		bat->bepi = val & 0xfffe0000;
		bat->vs = (val & 2) ? 1 : 0;
		bat->vp = (val & 1) ? 1 : 0;
		bat->raw = (bat->raw & 0xffffffff00000000ULL) | val;
	पूर्ण अन्यथा अणु
		/* Lower BAT */
		bat->brpn = val & 0xfffe0000;
		bat->wimg = (val >> 3) & 0xf;
		bat->pp = val & 3;
		bat->raw = (bat->raw & 0x00000000ffffffffULL) | ((u64)val << 32);
	पूर्ण
पूर्ण

अटल काष्ठा kvmppc_bat *kvmppc_find_bat(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	काष्ठा kvmppc_bat *bat;

	चयन (sprn) अणु
	हाल SPRN_IBAT0U ... SPRN_IBAT3L:
		bat = &vcpu_book3s->ibat[(sprn - SPRN_IBAT0U) / 2];
		अवरोध;
	हाल SPRN_IBAT4U ... SPRN_IBAT7L:
		bat = &vcpu_book3s->ibat[4 + ((sprn - SPRN_IBAT4U) / 2)];
		अवरोध;
	हाल SPRN_DBAT0U ... SPRN_DBAT3L:
		bat = &vcpu_book3s->dbat[(sprn - SPRN_DBAT0U) / 2];
		अवरोध;
	हाल SPRN_DBAT4U ... SPRN_DBAT7L:
		bat = &vcpu_book3s->dbat[4 + ((sprn - SPRN_DBAT4U) / 2)];
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस bat;
पूर्ण

पूर्णांक kvmppc_core_emulate_mtspr_pr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ spr_val)
अणु
	पूर्णांक emulated = EMULATE_DONE;

	चयन (sprn) अणु
	हाल SPRN_SDR1:
		अगर (!spr_allowed(vcpu, PRIV_HYPER))
			जाओ unprivileged;
		to_book3s(vcpu)->sdr1 = spr_val;
		अवरोध;
	हाल SPRN_DSISR:
		kvmppc_set_dsisr(vcpu, spr_val);
		अवरोध;
	हाल SPRN_DAR:
		kvmppc_set_dar(vcpu, spr_val);
		अवरोध;
	हाल SPRN_HIOR:
		to_book3s(vcpu)->hior = spr_val;
		अवरोध;
	हाल SPRN_IBAT0U ... SPRN_IBAT3L:
	हाल SPRN_IBAT4U ... SPRN_IBAT7L:
	हाल SPRN_DBAT0U ... SPRN_DBAT3L:
	हाल SPRN_DBAT4U ... SPRN_DBAT7L:
	अणु
		काष्ठा kvmppc_bat *bat = kvmppc_find_bat(vcpu, sprn);

		kvmppc_set_bat(vcpu, bat, !(sprn % 2), (u32)spr_val);
		/* BAT ग_लिखोs happen so rarely that we're ok to flush
		 * everything here */
		kvmppc_mmu_pte_flush(vcpu, 0, 0);
		kvmppc_mmu_flush_segments(vcpu);
		अवरोध;
	पूर्ण
	हाल SPRN_HID0:
		to_book3s(vcpu)->hid[0] = spr_val;
		अवरोध;
	हाल SPRN_HID1:
		to_book3s(vcpu)->hid[1] = spr_val;
		अवरोध;
	हाल SPRN_HID2:
		to_book3s(vcpu)->hid[2] = spr_val;
		अवरोध;
	हाल SPRN_HID2_GEKKO:
		to_book3s(vcpu)->hid[2] = spr_val;
		/* HID2.PSE controls paired single on gekko */
		चयन (vcpu->arch.pvr) अणु
		हाल 0x00080200:	/* lonestar 2.0 */
		हाल 0x00088202:	/* lonestar 2.2 */
		हाल 0x70000100:	/* gekko 1.0 */
		हाल 0x00080100:	/* gekko 2.0 */
		हाल 0x00083203:	/* gekko 2.3a */
		हाल 0x00083213:	/* gekko 2.3b */
		हाल 0x00083204:	/* gekko 2.4 */
		हाल 0x00083214:	/* gekko 2.4e (8SE) - retail HW2 */
		हाल 0x00087200:	/* broadway */
			अगर (vcpu->arch.hflags & BOOK3S_HFLAG_NATIVE_PS) अणु
				/* Native paired singles */
			पूर्ण अन्यथा अगर (spr_val & (1 << 29)) अणु /* HID2.PSE */
				vcpu->arch.hflags |= BOOK3S_HFLAG_PAIRED_SINGLE;
				kvmppc_giveup_ext(vcpu, MSR_FP);
			पूर्ण अन्यथा अणु
				vcpu->arch.hflags &= ~BOOK3S_HFLAG_PAIRED_SINGLE;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SPRN_HID4:
	हाल SPRN_HID4_GEKKO:
		to_book3s(vcpu)->hid[4] = spr_val;
		अवरोध;
	हाल SPRN_HID5:
		to_book3s(vcpu)->hid[5] = spr_val;
		/* guest HID5 set can change is_dcbz32 */
		अगर (vcpu->arch.mmu.is_dcbz32(vcpu) &&
		    (mfmsr() & MSR_HV))
			vcpu->arch.hflags |= BOOK3S_HFLAG_DCBZ32;
		अवरोध;
	हाल SPRN_GQR0:
	हाल SPRN_GQR1:
	हाल SPRN_GQR2:
	हाल SPRN_GQR3:
	हाल SPRN_GQR4:
	हाल SPRN_GQR5:
	हाल SPRN_GQR6:
	हाल SPRN_GQR7:
		to_book3s(vcpu)->gqr[sprn - SPRN_GQR0] = spr_val;
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल SPRN_FSCR:
		kvmppc_set_fscr(vcpu, spr_val);
		अवरोध;
	हाल SPRN_BESCR:
		vcpu->arch.bescr = spr_val;
		अवरोध;
	हाल SPRN_EBBHR:
		vcpu->arch.ebbhr = spr_val;
		अवरोध;
	हाल SPRN_EBBRR:
		vcpu->arch.ebbrr = spr_val;
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल SPRN_TFHAR:
	हाल SPRN_TEXASR:
	हाल SPRN_TFIAR:
		अगर (!cpu_has_feature(CPU_FTR_TM))
			अवरोध;

		अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
			kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
			emulated = EMULATE_AGAIN;
			अवरोध;
		पूर्ण

		अगर (MSR_TM_ACTIVE(kvmppc_get_msr(vcpu)) &&
			!((MSR_TM_SUSPENDED(kvmppc_get_msr(vcpu))) &&
					(sprn == SPRN_TFHAR))) अणु
			/* it is illegal to mtspr() TM regs in
			 * other than non-transactional state, with
			 * the exception of TFHAR in suspend state.
			 */
			kvmppc_core_queue_program(vcpu, SRR1_PROGTM);
			emulated = EMULATE_AGAIN;
			अवरोध;
		पूर्ण

		पंचांग_enable();
		अगर (sprn == SPRN_TFHAR)
			mtspr(SPRN_TFHAR, spr_val);
		अन्यथा अगर (sprn == SPRN_TEXASR)
			mtspr(SPRN_TEXASR, spr_val);
		अन्यथा
			mtspr(SPRN_TFIAR, spr_val);
		पंचांग_disable();

		अवरोध;
#पूर्ण_अगर
#पूर्ण_अगर
	हाल SPRN_ICTC:
	हाल SPRN_THRM1:
	हाल SPRN_THRM2:
	हाल SPRN_THRM3:
	हाल SPRN_CTRLF:
	हाल SPRN_CTRLT:
	हाल SPRN_L2CR:
	हाल SPRN_DSCR:
	हाल SPRN_MMCR0_GEKKO:
	हाल SPRN_MMCR1_GEKKO:
	हाल SPRN_PMC1_GEKKO:
	हाल SPRN_PMC2_GEKKO:
	हाल SPRN_PMC3_GEKKO:
	हाल SPRN_PMC4_GEKKO:
	हाल SPRN_WPAR_GEKKO:
	हाल SPRN_MSSSR0:
	हाल SPRN_DABR:
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल SPRN_MMCRS:
	हाल SPRN_MMCRA:
	हाल SPRN_MMCR0:
	हाल SPRN_MMCR1:
	हाल SPRN_MMCR2:
	हाल SPRN_UMMCR2:
	हाल SPRN_UAMOR:
	हाल SPRN_IAMR:
	हाल SPRN_AMR:
#पूर्ण_अगर
		अवरोध;
unprivileged:
	शेष:
		pr_info_ratelimited("KVM: invalid SPR write: %d\n", sprn);
		अगर (sprn & 0x10) अणु
			अगर (kvmppc_get_msr(vcpu) & MSR_PR) अणु
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((kvmppc_get_msr(vcpu) & MSR_PR) || sprn == 0) अणु
				kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
				emulated = EMULATE_AGAIN;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस emulated;
पूर्ण

पूर्णांक kvmppc_core_emulate_mfspr_pr(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ *spr_val)
अणु
	पूर्णांक emulated = EMULATE_DONE;

	चयन (sprn) अणु
	हाल SPRN_IBAT0U ... SPRN_IBAT3L:
	हाल SPRN_IBAT4U ... SPRN_IBAT7L:
	हाल SPRN_DBAT0U ... SPRN_DBAT3L:
	हाल SPRN_DBAT4U ... SPRN_DBAT7L:
	अणु
		काष्ठा kvmppc_bat *bat = kvmppc_find_bat(vcpu, sprn);

		अगर (sprn % 2)
			*spr_val = bat->raw >> 32;
		अन्यथा
			*spr_val = bat->raw;

		अवरोध;
	पूर्ण
	हाल SPRN_SDR1:
		अगर (!spr_allowed(vcpu, PRIV_HYPER))
			जाओ unprivileged;
		*spr_val = to_book3s(vcpu)->sdr1;
		अवरोध;
	हाल SPRN_DSISR:
		*spr_val = kvmppc_get_dsisr(vcpu);
		अवरोध;
	हाल SPRN_DAR:
		*spr_val = kvmppc_get_dar(vcpu);
		अवरोध;
	हाल SPRN_HIOR:
		*spr_val = to_book3s(vcpu)->hior;
		अवरोध;
	हाल SPRN_HID0:
		*spr_val = to_book3s(vcpu)->hid[0];
		अवरोध;
	हाल SPRN_HID1:
		*spr_val = to_book3s(vcpu)->hid[1];
		अवरोध;
	हाल SPRN_HID2:
	हाल SPRN_HID2_GEKKO:
		*spr_val = to_book3s(vcpu)->hid[2];
		अवरोध;
	हाल SPRN_HID4:
	हाल SPRN_HID4_GEKKO:
		*spr_val = to_book3s(vcpu)->hid[4];
		अवरोध;
	हाल SPRN_HID5:
		*spr_val = to_book3s(vcpu)->hid[5];
		अवरोध;
	हाल SPRN_CFAR:
	हाल SPRN_DSCR:
		*spr_val = 0;
		अवरोध;
	हाल SPRN_PURR:
		/*
		 * On निकास we would have updated purr
		 */
		*spr_val = vcpu->arch.purr;
		अवरोध;
	हाल SPRN_SPURR:
		/*
		 * On निकास we would have updated spurr
		 */
		*spr_val = vcpu->arch.spurr;
		अवरोध;
	हाल SPRN_VTB:
		*spr_val = to_book3s(vcpu)->vtb;
		अवरोध;
	हाल SPRN_IC:
		*spr_val = vcpu->arch.ic;
		अवरोध;
	हाल SPRN_GQR0:
	हाल SPRN_GQR1:
	हाल SPRN_GQR2:
	हाल SPRN_GQR3:
	हाल SPRN_GQR4:
	हाल SPRN_GQR5:
	हाल SPRN_GQR6:
	हाल SPRN_GQR7:
		*spr_val = to_book3s(vcpu)->gqr[sprn - SPRN_GQR0];
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल SPRN_FSCR:
		*spr_val = vcpu->arch.fscr;
		अवरोध;
	हाल SPRN_BESCR:
		*spr_val = vcpu->arch.bescr;
		अवरोध;
	हाल SPRN_EBBHR:
		*spr_val = vcpu->arch.ebbhr;
		अवरोध;
	हाल SPRN_EBBRR:
		*spr_val = vcpu->arch.ebbrr;
		अवरोध;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल SPRN_TFHAR:
	हाल SPRN_TEXASR:
	हाल SPRN_TFIAR:
		अगर (!cpu_has_feature(CPU_FTR_TM))
			अवरोध;

		अगर (!(kvmppc_get_msr(vcpu) & MSR_TM)) अणु
			kvmppc_trigger_fac_पूर्णांकerrupt(vcpu, FSCR_TM_LG);
			emulated = EMULATE_AGAIN;
			अवरोध;
		पूर्ण

		पंचांग_enable();
		अगर (sprn == SPRN_TFHAR)
			*spr_val = mfspr(SPRN_TFHAR);
		अन्यथा अगर (sprn == SPRN_TEXASR)
			*spr_val = mfspr(SPRN_TEXASR);
		अन्यथा अगर (sprn == SPRN_TFIAR)
			*spr_val = mfspr(SPRN_TFIAR);
		पंचांग_disable();
		अवरोध;
#पूर्ण_अगर
#पूर्ण_अगर
	हाल SPRN_THRM1:
	हाल SPRN_THRM2:
	हाल SPRN_THRM3:
	हाल SPRN_CTRLF:
	हाल SPRN_CTRLT:
	हाल SPRN_L2CR:
	हाल SPRN_MMCR0_GEKKO:
	हाल SPRN_MMCR1_GEKKO:
	हाल SPRN_PMC1_GEKKO:
	हाल SPRN_PMC2_GEKKO:
	हाल SPRN_PMC3_GEKKO:
	हाल SPRN_PMC4_GEKKO:
	हाल SPRN_WPAR_GEKKO:
	हाल SPRN_MSSSR0:
	हाल SPRN_DABR:
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल SPRN_MMCRS:
	हाल SPRN_MMCRA:
	हाल SPRN_MMCR0:
	हाल SPRN_MMCR1:
	हाल SPRN_MMCR2:
	हाल SPRN_UMMCR2:
	हाल SPRN_TIR:
	हाल SPRN_UAMOR:
	हाल SPRN_IAMR:
	हाल SPRN_AMR:
#पूर्ण_अगर
		*spr_val = 0;
		अवरोध;
	शेष:
unprivileged:
		pr_info_ratelimited("KVM: invalid SPR read: %d\n", sprn);
		अगर (sprn & 0x10) अणु
			अगर (kvmppc_get_msr(vcpu) & MSR_PR) अणु
				kvmppc_core_queue_program(vcpu, SRR1_PROGPRIV);
				emulated = EMULATE_AGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((kvmppc_get_msr(vcpu) & MSR_PR) || sprn == 0 ||
			    sprn == 4 || sprn == 5 || sprn == 6) अणु
				kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
				emulated = EMULATE_AGAIN;
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	वापस emulated;
पूर्ण

u32 kvmppc_alignment_dsisr(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक inst)
अणु
	वापस make_dsisr(inst);
पूर्ण

uदीर्घ kvmppc_alignment_dar(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक inst)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * Linux's fix_alignment() assumes that DAR is valid, so can we
	 */
	वापस vcpu->arch.fault_dar;
#अन्यथा
	uदीर्घ dar = 0;
	uदीर्घ ra = get_ra(inst);
	uदीर्घ rb = get_rb(inst);

	चयन (get_op(inst)) अणु
	हाल OP_LFS:
	हाल OP_LFD:
	हाल OP_STFD:
	हाल OP_STFS:
		अगर (ra)
			dar = kvmppc_get_gpr(vcpu, ra);
		dar += (s32)((s16)inst);
		अवरोध;
	हाल 31:
		अगर (ra)
			dar = kvmppc_get_gpr(vcpu, ra);
		dar += kvmppc_get_gpr(vcpu, rb);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "KVM: Unaligned instruction 0x%x\n", inst);
		अवरोध;
	पूर्ण

	वापस dar;
#पूर्ण_अगर
पूर्ण
