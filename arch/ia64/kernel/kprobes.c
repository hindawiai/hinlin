<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes (KProbes)
 *  arch/ia64/kernel/kprobes.c
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 * Copyright (C) Intel Corporation, 2005
 *
 * 2005-Apr     Rusty Lynch <rusty.lynch@पूर्णांकel.com> and Anil S Keshavamurthy
 *              <anil.s.keshavamurthy@पूर्णांकel.com> adapted from i386
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/preempt.h>
#समावेश <linux/extable.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/exception.h>

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[] = अणुअणुशून्य, शून्यपूर्णपूर्ण;

क्रमागत inकाष्ठाion_type अणुA, I, M, F, B, L, X, uपूर्ण;
अटल क्रमागत inकाष्ठाion_type bundle_encoding[32][3] = अणु
  अणु M, I, I पूर्ण,				/* 00 */
  अणु M, I, I पूर्ण,				/* 01 */
  अणु M, I, I पूर्ण,				/* 02 */
  अणु M, I, I पूर्ण,				/* 03 */
  अणु M, L, X पूर्ण,				/* 04 */
  अणु M, L, X पूर्ण,				/* 05 */
  अणु u, u, u पूर्ण,  			/* 06 */
  अणु u, u, u पूर्ण,  			/* 07 */
  अणु M, M, I पूर्ण,				/* 08 */
  अणु M, M, I पूर्ण,				/* 09 */
  अणु M, M, I पूर्ण,				/* 0A */
  अणु M, M, I पूर्ण,				/* 0B */
  अणु M, F, I पूर्ण,				/* 0C */
  अणु M, F, I पूर्ण,				/* 0D */
  अणु M, M, F पूर्ण,				/* 0E */
  अणु M, M, F पूर्ण,				/* 0F */
  अणु M, I, B पूर्ण,				/* 10 */
  अणु M, I, B पूर्ण,				/* 11 */
  अणु M, B, B पूर्ण,				/* 12 */
  अणु M, B, B पूर्ण,				/* 13 */
  अणु u, u, u पूर्ण,  			/* 14 */
  अणु u, u, u पूर्ण,  			/* 15 */
  अणु B, B, B पूर्ण,				/* 16 */
  अणु B, B, B पूर्ण,				/* 17 */
  अणु M, M, B पूर्ण,				/* 18 */
  अणु M, M, B पूर्ण,				/* 19 */
  अणु u, u, u पूर्ण,  			/* 1A */
  अणु u, u, u पूर्ण,  			/* 1B */
  अणु M, F, B पूर्ण,				/* 1C */
  अणु M, F, B पूर्ण,				/* 1D */
  अणु u, u, u पूर्ण,  			/* 1E */
  अणु u, u, u पूर्ण,  			/* 1F */
पूर्ण;

/* Insert a दीर्घ branch code */
अटल व्योम __kprobes set_brl_inst(व्योम *from, व्योम *to)
अणु
	s64 rel = ((s64) to - (s64) from) >> 4;
	bundle_t *brl;
	brl = (bundle_t *) ((u64) from & ~0xf);
	brl->quad0.ढाँचा = 0x05;	/* [MLX](stop) */
	brl->quad0.slot0 = NOP_M_INST;	/* nop.m 0x0 */
	brl->quad0.slot1_p0 = ((rel >> 20) & 0x7fffffffff) << 2;
	brl->quad1.slot1_p1 = (((rel >> 20) & 0x7fffffffff) << 2) >> (64 - 46);
	/* brl.cond.sptk.many.clr rel<<4 (qp=0) */
	brl->quad1.slot2 = BRL_INST(rel >> 59, rel & 0xfffff);
पूर्ण

/*
 * In this function we check to see अगर the inकाष्ठाion
 * is IP relative inकाष्ठाion and update the kprobe
 * inst flag accordingly
 */
अटल व्योम __kprobes update_kprobe_inst_flag(uपूर्णांक ढाँचा, uपूर्णांक  slot,
					      uपूर्णांक major_opcode,
					      अचिन्हित दीर्घ kprobe_inst,
					      काष्ठा kprobe *p)
अणु
	p->ainsn.inst_flag = 0;
	p->ainsn.target_br_reg = 0;
	p->ainsn.slot = slot;

	/* Check क्रम Break inकाष्ठाion
	 * Bits 37:40 Major opcode to be zero
	 * Bits 27:32 X6 to be zero
	 * Bits 32:35 X3 to be zero
	 */
	अगर ((!major_opcode) && (!((kprobe_inst >> 27) & 0x1FF)) ) अणु
		/* is a अवरोध inकाष्ठाion */
	 	p->ainsn.inst_flag |= INST_FLAG_BREAK_INST;
		वापस;
	पूर्ण

	अगर (bundle_encoding[ढाँचा][slot] == B) अणु
		चयन (major_opcode) अणु
		  हाल INसूचीECT_CALL_OPCODE:
	 		p->ainsn.inst_flag |= INST_FLAG_FIX_BRANCH_REG;
			p->ainsn.target_br_reg = ((kprobe_inst >> 6) & 0x7);
			अवरोध;
		  हाल IP_RELATIVE_PREDICT_OPCODE:
		  हाल IP_RELATIVE_BRANCH_OPCODE:
			p->ainsn.inst_flag |= INST_FLAG_FIX_RELATIVE_IP_ADDR;
			अवरोध;
		  हाल IP_RELATIVE_CALL_OPCODE:
			p->ainsn.inst_flag |= INST_FLAG_FIX_RELATIVE_IP_ADDR;
			p->ainsn.inst_flag |= INST_FLAG_FIX_BRANCH_REG;
			p->ainsn.target_br_reg = ((kprobe_inst >> 6) & 0x7);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (bundle_encoding[ढाँचा][slot] == X) अणु
		चयन (major_opcode) अणु
		  हाल LONG_CALL_OPCODE:
			p->ainsn.inst_flag |= INST_FLAG_FIX_BRANCH_REG;
			p->ainsn.target_br_reg = ((kprobe_inst >> 6) & 0x7);
		  अवरोध;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

/*
 * In this function we check to see अगर the inकाष्ठाion
 * (qp) cmpx.crel.ctype p1,p2=r2,r3
 * on which we are inserting kprobe is cmp inकाष्ठाion
 * with ctype as unc.
 */
अटल uपूर्णांक __kprobes is_cmp_ctype_unc_inst(uपूर्णांक ढाँचा, uपूर्णांक slot,
					    uपूर्णांक major_opcode,
					    अचिन्हित दीर्घ kprobe_inst)
अणु
	cmp_inst_t cmp_inst;
	uपूर्णांक ctype_unc = 0;

	अगर (!((bundle_encoding[ढाँचा][slot] == I) ||
		(bundle_encoding[ढाँचा][slot] == M)))
		जाओ out;

	अगर (!((major_opcode == 0xC) || (major_opcode == 0xD) ||
		(major_opcode == 0xE)))
		जाओ out;

	cmp_inst.l = kprobe_inst;
	अगर ((cmp_inst.f.x2 == 0) || (cmp_inst.f.x2 == 1)) अणु
		/* Integer compare - Register Register (A6 type)*/
		अगर ((cmp_inst.f.tb == 0) && (cmp_inst.f.ta == 0)
				&&(cmp_inst.f.c == 1))
			ctype_unc = 1;
	पूर्ण अन्यथा अगर ((cmp_inst.f.x2 == 2)||(cmp_inst.f.x2 == 3)) अणु
		/* Integer compare - Immediate Register (A8 type)*/
		अगर ((cmp_inst.f.ta == 0) &&(cmp_inst.f.c == 1))
			ctype_unc = 1;
	पूर्ण
out:
	वापस ctype_unc;
पूर्ण

/*
 * In this function we check to see अगर the inकाष्ठाion
 * on which we are inserting kprobe is supported.
 * Returns qp value अगर supported
 * Returns -EINVAL अगर unsupported
 */
अटल पूर्णांक __kprobes unsupported_inst(uपूर्णांक ढाँचा, uपूर्णांक  slot,
				      uपूर्णांक major_opcode,
				      अचिन्हित दीर्घ kprobe_inst,
				      अचिन्हित दीर्घ addr)
अणु
	पूर्णांक qp;

	qp = kprobe_inst & 0x3f;
	अगर (is_cmp_ctype_unc_inst(ढाँचा, slot, major_opcode, kprobe_inst)) अणु
		अगर (slot == 1 && qp)  अणु
			prपूर्णांकk(KERN_WARNING "Kprobes on cmp unc "
					"instruction on slot 1 at <0x%lx> "
					"is not supported\n", addr);
			वापस -EINVAL;

		पूर्ण
		qp = 0;
	पूर्ण
	अन्यथा अगर (bundle_encoding[ढाँचा][slot] == I) अणु
		अगर (major_opcode == 0) अणु
			/*
			 * Check क्रम Integer speculation inकाष्ठाion
			 * - Bit 33-35 to be equal to 0x1
			 */
			अगर (((kprobe_inst >> 33) & 0x7) == 1) अणु
				prपूर्णांकk(KERN_WARNING
					"Kprobes on speculation inst at <0x%lx> not supported\n",
						addr);
				वापस -EINVAL;
			पूर्ण
			/*
			 * IP relative mov inकाष्ठाion
			 *  - Bit 27-35 to be equal to 0x30
			 */
			अगर (((kprobe_inst >> 27) & 0x1FF) == 0x30) अणु
				prपूर्णांकk(KERN_WARNING
					"Kprobes on \"mov r1=ip\" at <0x%lx> not supported\n",
						addr);
				वापस -EINVAL;

			पूर्ण
		पूर्ण
		अन्यथा अगर ((major_opcode == 5) &&	!(kprobe_inst & (0xFUl << 33)) &&
				(kprobe_inst & (0x1UL << 12))) अणु
			/* test bit inकाष्ठाions, tbit,tnat,tf
			 * bit 33-36 to be equal to 0
			 * bit 12 to be equal to 1
			 */
			अगर (slot == 1 && qp) अणु
				prपूर्णांकk(KERN_WARNING "Kprobes on test bit "
						"instruction on slot at <0x%lx> "
						"is not supported\n", addr);
				वापस -EINVAL;
			पूर्ण
			qp = 0;
		पूर्ण
	पूर्ण
	अन्यथा अगर (bundle_encoding[ढाँचा][slot] == B) अणु
		अगर (major_opcode == 7) अणु
			/* IP-Relative Predict major code is 7 */
			prपूर्णांकk(KERN_WARNING "Kprobes on IP-Relative"
					"Predict is not supported\n");
			वापस -EINVAL;
		पूर्ण
		अन्यथा अगर (major_opcode == 2) अणु
			/* Indirect Predict, major code is 2
			 * bit 27-32 to be equal to 10 or 11
			 */
			पूर्णांक x6=(kprobe_inst >> 27) & 0x3F;
			अगर ((x6 == 0x10) || (x6 == 0x11)) अणु
				prपूर्णांकk(KERN_WARNING "Kprobes on "
					"Indirect Predict is not supported\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	/* kernel करोes not use भग्न inकाष्ठाion, here क्रम safety kprobe
	 * will judge whether it is fcmp/flass/भग्न approximation inकाष्ठाion
	 */
	अन्यथा अगर (unlikely(bundle_encoding[ढाँचा][slot] == F)) अणु
		अगर ((major_opcode == 4 || major_opcode == 5) &&
				(kprobe_inst  & (0x1 << 12))) अणु
			/* fcmp/fclass unc inकाष्ठाion */
			अगर (slot == 1 && qp) अणु
				prपूर्णांकk(KERN_WARNING "Kprobes on fcmp/fclass "
					"instruction on slot at <0x%lx> "
					"is not supported\n", addr);
				वापस -EINVAL;

			पूर्ण
			qp = 0;
		पूर्ण
		अगर ((major_opcode == 0 || major_opcode == 1) &&
			(kprobe_inst & (0x1UL << 33))) अणु
			/* भग्न Approximation inकाष्ठाion */
			अगर (slot == 1 && qp) अणु
				prपूर्णांकk(KERN_WARNING "Kprobes on float Approx "
					"instr at <0x%lx> is not supported\n",
						addr);
				वापस -EINVAL;
			पूर्ण
			qp = 0;
		पूर्ण
	पूर्ण
	वापस qp;
पूर्ण

/*
 * In this function we override the bundle with
 * the अवरोध inकाष्ठाion at the given slot.
 */
अटल व्योम __kprobes prepare_अवरोध_inst(uपूर्णांक ढाँचा, uपूर्णांक  slot,
					 uपूर्णांक major_opcode,
					 अचिन्हित दीर्घ kprobe_inst,
					 काष्ठा kprobe *p,
					 पूर्णांक qp)
अणु
	अचिन्हित दीर्घ अवरोध_inst = BREAK_INST;
	bundle_t *bundle = &p->opcode.bundle;

	/*
	 * Copy the original kprobe_inst qualअगरying predicate(qp)
	 * to the अवरोध inकाष्ठाion
	 */
	अवरोध_inst |= qp;

	चयन (slot) अणु
	  हाल 0:
		bundle->quad0.slot0 = अवरोध_inst;
		अवरोध;
	  हाल 1:
		bundle->quad0.slot1_p0 = अवरोध_inst;
		bundle->quad1.slot1_p1 = अवरोध_inst >> (64-46);
		अवरोध;
	  हाल 2:
		bundle->quad1.slot2 = अवरोध_inst;
		अवरोध;
	पूर्ण

	/*
	 * Update the inकाष्ठाion flag, so that we can
	 * emulate the inकाष्ठाion properly after we
	 * single step on original inकाष्ठाion
	 */
	update_kprobe_inst_flag(ढाँचा, slot, major_opcode, kprobe_inst, p);
पूर्ण

अटल व्योम __kprobes get_kprobe_inst(bundle_t *bundle, uपूर्णांक slot,
	       	अचिन्हित दीर्घ *kprobe_inst, uपूर्णांक *major_opcode)
अणु
	अचिन्हित दीर्घ kprobe_inst_p0, kprobe_inst_p1;
	अचिन्हित पूर्णांक ढाँचा;

	ढाँचा = bundle->quad0.ढाँचा;

	चयन (slot) अणु
	  हाल 0:
		*major_opcode = (bundle->quad0.slot0 >> SLOT0_OPCODE_SHIFT);
		*kprobe_inst = bundle->quad0.slot0;
		  अवरोध;
	  हाल 1:
		*major_opcode = (bundle->quad1.slot1_p1 >> SLOT1_p1_OPCODE_SHIFT);
		kprobe_inst_p0 = bundle->quad0.slot1_p0;
		kprobe_inst_p1 = bundle->quad1.slot1_p1;
		*kprobe_inst = kprobe_inst_p0 | (kprobe_inst_p1 << (64-46));
		अवरोध;
	  हाल 2:
		*major_opcode = (bundle->quad1.slot2 >> SLOT2_OPCODE_SHIFT);
		*kprobe_inst = bundle->quad1.slot2;
		अवरोध;
	पूर्ण
पूर्ण

/* Returns non-zero अगर the addr is in the Interrupt Vector Table */
अटल पूर्णांक __kprobes in_ivt_functions(अचिन्हित दीर्घ addr)
अणु
	वापस (addr >= (अचिन्हित दीर्घ)__start_ivt_text
		&& addr < (अचिन्हित दीर्घ)__end_ivt_text);
पूर्ण

अटल पूर्णांक __kprobes valid_kprobe_addr(पूर्णांक ढाँचा, पूर्णांक slot,
				       अचिन्हित दीर्घ addr)
अणु
	अगर ((slot > 2) || ((bundle_encoding[ढाँचा][1] == L) && slot > 1)) अणु
		prपूर्णांकk(KERN_WARNING "Attempting to insert unaligned kprobe "
				"at 0x%lx\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (in_ivt_functions(addr)) अणु
		prपूर्णांकk(KERN_WARNING "Kprobes can't be inserted inside "
				"IVT functions at 0x%lx\n", addr);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __kprobes save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	अचिन्हित पूर्णांक i;
	i = atomic_add_वापस(1, &kcb->prev_kprobe_index);
	kcb->prev_kprobe[i-1].kp = kprobe_running();
	kcb->prev_kprobe[i-1].status = kcb->kprobe_status;
पूर्ण

अटल व्योम __kprobes restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	अचिन्हित पूर्णांक i;
	i = atomic_पढ़ो(&kcb->prev_kprobe_index);
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe[i-1].kp);
	kcb->kprobe_status = kcb->prev_kprobe[i-1].status;
	atomic_sub(1, &kcb->prev_kprobe_index);
पूर्ण

अटल व्योम __kprobes set_current_kprobe(काष्ठा kprobe *p,
			काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
पूर्ण

अटल व्योम kretprobe_trampoline(व्योम)
अणु
पूर्ण

पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	regs->cr_iip = __kretprobe_trampoline_handler(regs, kretprobe_trampoline, शून्य);
	/*
	 * By वापसing a non-zero value, we are telling
	 * kprobe_handler() that we करोn't want the post_handler
	 * to run (and have re-enabled preemption)
	 */
	वापस 1;
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->b0;
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->b0 = ((काष्ठा fnptr *)kretprobe_trampoline)->ip;
पूर्ण

/* Check the inकाष्ठाion in the slot is अवरोध */
अटल पूर्णांक __kprobes __is_ia64_अवरोध_inst(bundle_t *bundle, uपूर्णांक slot)
अणु
	अचिन्हित पूर्णांक major_opcode;
	अचिन्हित पूर्णांक ढाँचा = bundle->quad0.ढाँचा;
	अचिन्हित दीर्घ kprobe_inst;

	/* Move to slot 2, अगर bundle is MLX type and kprobe slot is 1 */
	अगर (slot == 1 && bundle_encoding[ढाँचा][1] == L)
		slot++;

	/* Get Kprobe probe inकाष्ठाion at given slot*/
	get_kprobe_inst(bundle, slot, &kprobe_inst, &major_opcode);

	/* For अवरोध inकाष्ठाion,
	 * Bits 37:40 Major opcode to be zero
	 * Bits 27:32 X6 to be zero
	 * Bits 32:35 X3 to be zero
	 */
	अगर (major_opcode || ((kprobe_inst >> 27) & 0x1FF)) अणु
		/* Not a अवरोध inकाष्ठाion */
		वापस 0;
	पूर्ण

	/* Is a अवरोध inकाष्ठाion */
	वापस 1;
पूर्ण

/*
 * In this function, we check whether the target bundle modअगरies IP or
 * it triggers an exception. If so, it cannot be boostable.
 */
अटल पूर्णांक __kprobes can_boost(bundle_t *bundle, uपूर्णांक slot,
			       अचिन्हित दीर्घ bundle_addr)
अणु
	अचिन्हित पूर्णांक ढाँचा = bundle->quad0.ढाँचा;

	करो अणु
		अगर (search_exception_tables(bundle_addr + slot) ||
		    __is_ia64_अवरोध_inst(bundle, slot))
			वापस 0;	/* exception may occur in this bundle*/
	पूर्ण जबतक ((++slot) < 3);
	ढाँचा &= 0x1e;
	अगर (ढाँचा >= 0x10 /* including B unit */ ||
	    ढाँचा == 0x04 /* including X unit */ ||
	    ढाँचा == 0x06) /* undefined */
		वापस 0;

	वापस 1;
पूर्ण

/* Prepare दीर्घ jump bundle and disables other boosters अगर need */
अटल व्योम __kprobes prepare_booster(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)p->addr & ~0xFULL;
	अचिन्हित पूर्णांक slot = (अचिन्हित दीर्घ)p->addr & 0xf;
	काष्ठा kprobe *other_kp;

	अगर (can_boost(&p->ainsn.insn[0].bundle, slot, addr)) अणु
		set_brl_inst(&p->ainsn.insn[1].bundle, (bundle_t *)addr + 1);
		p->ainsn.inst_flag |= INST_FLAG_BOOSTABLE;
	पूर्ण

	/* disables boosters in previous slots */
	क्रम (; addr < (अचिन्हित दीर्घ)p->addr; addr++) अणु
		other_kp = get_kprobe((व्योम *)addr);
		अगर (other_kp)
			other_kp->ainsn.inst_flag &= ~INST_FLAG_BOOSTABLE;
	पूर्ण
पूर्ण

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) p->addr;
	अचिन्हित दीर्घ *kprobe_addr = (अचिन्हित दीर्घ *)(addr & ~0xFULL);
	अचिन्हित दीर्घ kprobe_inst=0;
	अचिन्हित पूर्णांक slot = addr & 0xf, ढाँचा, major_opcode = 0;
	bundle_t *bundle;
	पूर्णांक qp;

	bundle = &((kprobe_opcode_t *)kprobe_addr)->bundle;
	ढाँचा = bundle->quad0.ढाँचा;

	अगर(valid_kprobe_addr(ढाँचा, slot, addr))
		वापस -EINVAL;

	/* Move to slot 2, अगर bundle is MLX type and kprobe slot is 1 */
	अगर (slot == 1 && bundle_encoding[ढाँचा][1] == L)
		slot++;

	/* Get kprobe_inst and major_opcode from the bundle */
	get_kprobe_inst(bundle, slot, &kprobe_inst, &major_opcode);

	qp = unsupported_inst(ढाँचा, slot, major_opcode, kprobe_inst, addr);
	अगर (qp < 0)
		वापस -EINVAL;

	p->ainsn.insn = get_insn_slot();
	अगर (!p->ainsn.insn)
		वापस -ENOMEM;
	स_नकल(&p->opcode, kprobe_addr, माप(kprobe_opcode_t));
	स_नकल(p->ainsn.insn, kprobe_addr, माप(kprobe_opcode_t));

	prepare_अवरोध_inst(ढाँचा, slot, major_opcode, kprobe_inst, p, qp);

	prepare_booster(p);

	वापस 0;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ arm_addr;
	bundle_t *src, *dest;

	arm_addr = ((अचिन्हित दीर्घ)p->addr) & ~0xFUL;
	dest = &((kprobe_opcode_t *)arm_addr)->bundle;
	src = &p->opcode.bundle;

	flush_icache_range((अचिन्हित दीर्घ)p->ainsn.insn,
			   (अचिन्हित दीर्घ)p->ainsn.insn +
			   माप(kprobe_opcode_t) * MAX_INSN_SIZE);

	चयन (p->ainsn.slot) अणु
		हाल 0:
			dest->quad0.slot0 = src->quad0.slot0;
			अवरोध;
		हाल 1:
			dest->quad1.slot1_p1 = src->quad1.slot1_p1;
			अवरोध;
		हाल 2:
			dest->quad1.slot2 = src->quad1.slot2;
			अवरोध;
	पूर्ण
	flush_icache_range(arm_addr, arm_addr + माप(kprobe_opcode_t));
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ arm_addr;
	bundle_t *src, *dest;

	arm_addr = ((अचिन्हित दीर्घ)p->addr) & ~0xFUL;
	dest = &((kprobe_opcode_t *)arm_addr)->bundle;
	/* p->ainsn.insn contains the original unaltered kprobe_opcode_t */
	src = &p->ainsn.insn->bundle;
	चयन (p->ainsn.slot) अणु
		हाल 0:
			dest->quad0.slot0 = src->quad0.slot0;
			अवरोध;
		हाल 1:
			dest->quad1.slot1_p1 = src->quad1.slot1_p1;
			अवरोध;
		हाल 2:
			dest->quad1.slot2 = src->quad1.slot2;
			अवरोध;
	पूर्ण
	flush_icache_range(arm_addr, arm_addr + माप(kprobe_opcode_t));
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.insn) अणु
		मुक्त_insn_slot(p->ainsn.insn,
			       p->ainsn.inst_flag & INST_FLAG_BOOSTABLE);
		p->ainsn.insn = शून्य;
	पूर्ण
पूर्ण
/*
 * We are resuming execution after a single step fault, so the pt_regs
 * काष्ठाure reflects the रेजिस्टर state after we executed the inकाष्ठाion
 * located in the kprobe (p->ainsn.insn->bundle).  We still need to adjust
 * the ip to poपूर्णांक back to the original stack address. To set the IP address
 * to original stack address, handle the हाल where we need to fixup the
 * relative IP address and/or fixup branch रेजिस्टर.
 */
अटल व्योम __kprobes resume_execution(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ bundle_addr = (अचिन्हित दीर्घ) (&p->ainsn.insn->bundle);
	अचिन्हित दीर्घ resume_addr = (अचिन्हित दीर्घ)p->addr & ~0xFULL;
	अचिन्हित दीर्घ ढाँचा;
	पूर्णांक slot = ((अचिन्हित दीर्घ)p->addr & 0xf);

	ढाँचा = p->ainsn.insn->bundle.quad0.ढाँचा;

	अगर (slot == 1 && bundle_encoding[ढाँचा][1] == L)
		slot = 2;

	अगर (p->ainsn.inst_flag & ~INST_FLAG_BOOSTABLE) अणु

		अगर (p->ainsn.inst_flag & INST_FLAG_FIX_RELATIVE_IP_ADDR) अणु
			/* Fix relative IP address */
			regs->cr_iip = (regs->cr_iip - bundle_addr) +
					resume_addr;
		पूर्ण

		अगर (p->ainsn.inst_flag & INST_FLAG_FIX_BRANCH_REG) अणु
		/*
		 * Fix target branch रेजिस्टर, software convention is
		 * to use either b0 or b6 or b7, so just checking
		 * only those रेजिस्टरs
		 */
			चयन (p->ainsn.target_br_reg) अणु
			हाल 0:
				अगर ((regs->b0 == bundle_addr) ||
					(regs->b0 == bundle_addr + 0x10)) अणु
					regs->b0 = (regs->b0 - bundle_addr) +
						resume_addr;
				पूर्ण
				अवरोध;
			हाल 6:
				अगर ((regs->b6 == bundle_addr) ||
					(regs->b6 == bundle_addr + 0x10)) अणु
					regs->b6 = (regs->b6 - bundle_addr) +
						resume_addr;
				पूर्ण
				अवरोध;
			हाल 7:
				अगर ((regs->b7 == bundle_addr) ||
					(regs->b7 == bundle_addr + 0x10)) अणु
					regs->b7 = (regs->b7 - bundle_addr) +
						resume_addr;
				पूर्ण
				अवरोध;
			पूर्ण /* end चयन */
		पूर्ण
		जाओ turn_ss_off;
	पूर्ण

	अगर (slot == 2) अणु
		अगर (regs->cr_iip == bundle_addr + 0x10) अणु
			regs->cr_iip = resume_addr + 0x10;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (regs->cr_iip == bundle_addr) अणु
			regs->cr_iip = resume_addr;
		पूर्ण
	पूर्ण

turn_ss_off:
	/* Turn off Single Step bit */
	ia64_psr(regs)->ss = 0;
पूर्ण

अटल व्योम __kprobes prepare_ss(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ bundle_addr = (अचिन्हित दीर्घ) &p->ainsn.insn->bundle;
	अचिन्हित दीर्घ slot = (अचिन्हित दीर्घ)p->addr & 0xf;

	/* single step अंतरभूत अगर अवरोध inकाष्ठाion */
	अगर (p->ainsn.inst_flag == INST_FLAG_BREAK_INST)
		regs->cr_iip = (अचिन्हित दीर्घ)p->addr & ~0xFULL;
	अन्यथा
		regs->cr_iip = bundle_addr & ~0xFULL;

	अगर (slot > 2)
		slot = 0;

	ia64_psr(regs)->ri = slot;

	/* turn on single stepping */
	ia64_psr(regs)->ss = 1;
पूर्ण

अटल पूर्णांक __kprobes is_ia64_अवरोध_inst(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक slot = ia64_psr(regs)->ri;
	अचिन्हित दीर्घ *kprobe_addr = (अचिन्हित दीर्घ *)regs->cr_iip;
	bundle_t bundle;

	स_नकल(&bundle, kprobe_addr, माप(bundle_t));

	वापस __is_ia64_अवरोध_inst(&bundle, slot);
पूर्ण

अटल पूर्णांक __kprobes pre_kprobes_handler(काष्ठा die_args *args)
अणु
	काष्ठा kprobe *p;
	पूर्णांक ret = 0;
	काष्ठा pt_regs *regs = args->regs;
	kprobe_opcode_t *addr = (kprobe_opcode_t *)inकाष्ठाion_poपूर्णांकer(regs);
	काष्ठा kprobe_ctlblk *kcb;

	/*
	 * We करोn't want to be preempted क्रम the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	/* Handle recursion हालs */
	अगर (kprobe_running()) अणु
		p = get_kprobe(addr);
		अगर (p) अणु
			अगर ((kcb->kprobe_status == KPROBE_HIT_SS) &&
	 		     (p->ainsn.inst_flag == INST_FLAG_BREAK_INST)) अणु
				ia64_psr(regs)->ss = 0;
				जाओ no_kprobe;
			पूर्ण
			/* We have reentered the pre_kprobe_handler(), since
			 * another probe was hit जबतक within the handler.
			 * We here save the original kprobes variables and
			 * just single step on the inकाष्ठाion of the new probe
			 * without calling any user handlers.
			 */
			save_previous_kprobe(kcb);
			set_current_kprobe(p, kcb);
			kprobes_inc_nmissed_count(p);
			prepare_ss(p, regs);
			kcb->kprobe_status = KPROBE_REENTER;
			वापस 1;
		पूर्ण अन्यथा अगर (!is_ia64_अवरोध_inst(regs)) अणु
			/* The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd by
			 * another cpu right after we hit, no further
			 * handling of this पूर्णांकerrupt is appropriate
			 */
			ret = 1;
			जाओ no_kprobe;
		पूर्ण अन्यथा अणु
			/* Not our अवरोध */
			जाओ no_kprobe;
		पूर्ण
	पूर्ण

	p = get_kprobe(addr);
	अगर (!p) अणु
		अगर (!is_ia64_अवरोध_inst(regs)) अणु
			/*
			 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
			 * after we hit it.  Another cpu has हटाओd
			 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
			 * at this address.  In either हाल, no further
			 * handling of this पूर्णांकerrupt is appropriate.
			 */
			ret = 1;

		पूर्ण

		/* Not one of our अवरोध, let kernel handle it */
		जाओ no_kprobe;
	पूर्ण

	set_current_kprobe(p, kcb);
	kcb->kprobe_status = KPROBE_HIT_ACTIVE;

	अगर (p->pre_handler && p->pre_handler(p, regs)) अणु
		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण

#अगर !defined(CONFIG_PREEMPTION)
	अगर (p->ainsn.inst_flag == INST_FLAG_BOOSTABLE && !p->post_handler) अणु
		/* Boost up -- we can execute copied inकाष्ठाions directly */
		ia64_psr(regs)->ri = p->ainsn.slot;
		regs->cr_iip = (अचिन्हित दीर्घ)&p->ainsn.insn->bundle & ~0xFULL;
		/* turn single stepping off */
		ia64_psr(regs)->ss = 0;

		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	prepare_ss(p, regs);
	kcb->kprobe_status = KPROBE_HIT_SS;
	वापस 1;

no_kprobe:
	preempt_enable_no_resched();
	वापस ret;
पूर्ण

अटल पूर्णांक __kprobes post_kprobes_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (!cur)
		वापस 0;

	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	resume_execution(cur, regs);

	/*Restore back the original saved kprobes variables and जारी. */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		जाओ out;
	पूर्ण
	reset_current_kprobe();

out:
	preempt_enable_no_resched();
	वापस 1;
पूर्ण

पूर्णांक __kprobes kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();


	चयन(kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the inकाष्ठाion poपूर्णांकer poपूर्णांकs back to
		 * the probe address and allow the page fault handler
		 * to जारी as a normal page fault.
		 */
		regs->cr_iip = ((अचिन्हित दीर्घ)cur->addr) & ~0xFULL;
		ia64_psr(regs)->ri = ((अचिन्हित दीर्घ)cur->addr) & 0xf;
		अगर (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		अन्यथा
			reset_current_kprobe();
		preempt_enable_no_resched();
		अवरोध;
	हाल KPROBE_HIT_ACTIVE:
	हाल KPROBE_HIT_SSDONE:
		/*
		 * We increment the nmissed count क्रम accounting,
		 * we can also use npre/npostfault count क्रम accounting
		 * these specअगरic fault हालs.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because inकाष्ठाions in the pre/post
		 * handler caused the page_fault, this could happen
		 * अगर handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specअगरied handler try to fix it first.
		 */
		अगर (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
			वापस 1;
		/*
		 * In हाल the user-specअगरied fault handler वापसed
		 * zero, try to fix up.
		 */
		अगर (ia64_करोne_with_exception(regs))
			वापस 1;

		/*
		 * Let ia64_करो_page_fault() fix it.
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *)data;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (args->regs && user_mode(args->regs))
		वापस ret;

	चयन(val) अणु
	हाल DIE_BREAK:
		/* err is अवरोध number from ia64_bad_अवरोध() */
		अगर ((args->err >> 12) == (__IA64_BREAK_KPROBE >> 12)
			|| args->err == 0)
			अगर (pre_kprobes_handler(args))
				ret = NOTIFY_STOP;
		अवरोध;
	हाल DIE_FAULT:
		/* err is vector number from ia64_fault() */
		अगर (args->err == 36)
			अगर (post_kprobes_handler(args->regs))
				ret = NOTIFY_STOP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अचिन्हित दीर्घ arch_deref_entry_poपूर्णांक(व्योम *entry)
अणु
	वापस ((काष्ठा fnptr *)entry)->ip;
पूर्ण

अटल काष्ठा kprobe trampoline_p = अणु
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	trampoline_p.addr =
		(kprobe_opcode_t *)((काष्ठा fnptr *)kretprobe_trampoline)->ip;
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->addr ==
		(kprobe_opcode_t *)((काष्ठा fnptr *)kretprobe_trampoline)->ip)
		वापस 1;

	वापस 0;
पूर्ण
