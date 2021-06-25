<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes Jump Optimization (Optprobes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 * Copyright (C) Hitachi Ltd., 2012
 * Copyright (C) Huawei Inc., 2014
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/cacheflush.h>
/* क्रम arm_gen_branch */
#समावेश <यंत्र/insn.h>
/* क्रम patch_text */
#समावेश <यंत्र/patch.h>

#समावेश "core.h"

/*
 * See रेजिस्टर_usage_flags. If the probed inकाष्ठाion करोesn't use PC,
 * we can copy it पूर्णांकo ढाँचा and have it executed directly without
 * simulation or emulation.
 */
#घोषणा ARM_REG_PC	15
#घोषणा can_kprobe_direct_exec(m)	(!test_bit(ARM_REG_PC, &(m)))

/*
 * NOTE: the first sub and add inकाष्ठाion will be modअगरied according
 * to the stack cost of the inकाष्ठाion.
 */
यंत्र (
			".global optprobe_template_entry\n"
			"optprobe_template_entry:\n"
			".global optprobe_template_sub_sp\n"
			"optprobe_template_sub_sp:"
			"	sub	sp, sp, #0xff\n"
			"	stmia	sp, {r0 - r14} \n"
			".global optprobe_template_add_sp\n"
			"optprobe_template_add_sp:"
			"	add	r3, sp, #0xff\n"
			"	str	r3, [sp, #52]\n"
			"	mrs	r4, cpsr\n"
			"	str	r4, [sp, #64]\n"
			"	mov	r1, sp\n"
			"	ldr	r0, 1f\n"
			"	ldr	r2, 2f\n"
			/*
			 * AEABI requires an 8-bytes alignment stack. If
			 * SP % 8 != 0 (SP % 4 == 0 should be ensured),
			 * alloc more bytes here.
			 */
			"	and	r4, sp, #4\n"
			"	sub	sp, sp, r4\n"
#अगर __LINUX_ARM_ARCH__ >= 5
			"	blx	r2\n"
#अन्यथा
			"	mov     lr, pc\n"
			"	mov	pc, r2\n"
#पूर्ण_अगर
			"	add	sp, sp, r4\n"
			"	ldr	r1, [sp, #64]\n"
			"	tst	r1, #"__stringअगरy(PSR_T_BIT)"\n"
			"	ldrne	r2, [sp, #60]\n"
			"	orrne	r2, #1\n"
			"	strne	r2, [sp, #60] @ set bit0 of PC for thumb\n"
			"	msr	cpsr_cxsf, r1\n"
			".global optprobe_template_restore_begin\n"
			"optprobe_template_restore_begin:\n"
			"	ldmia	sp, {r0 - r15}\n"
			".global optprobe_template_restore_orig_insn\n"
			"optprobe_template_restore_orig_insn:\n"
			"	nop\n"
			".global optprobe_template_restore_end\n"
			"optprobe_template_restore_end:\n"
			"	nop\n"
			".global optprobe_template_val\n"
			"optprobe_template_val:\n"
			"1:	.long 0\n"
			".global optprobe_template_call\n"
			"optprobe_template_call:\n"
			"2:	.long 0\n"
			".global optprobe_template_end\n"
			"optprobe_template_end:\n");

#घोषणा TMPL_VAL_IDX \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_val - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_CALL_IDX \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_call - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_END_IDX \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_end - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_ADD_SP \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_add_sp - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_SUB_SP \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_sub_sp - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_RESTORE_BEGIN \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_restore_begin - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_RESTORE_ORIGN_INSN \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_restore_orig_insn - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)
#घोषणा TMPL_RESTORE_END \
	((अचिन्हित दीर्घ *)optprobe_ढाँचा_restore_end - (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry)

/*
 * ARM can always optimize an inकाष्ठाion when using ARM ISA, except
 * inकाष्ठाions like 'str r0, [sp, r1]' which store to stack and unable
 * to determine stack space consumption अटलally.
 */
पूर्णांक arch_prepared_optinsn(काष्ठा arch_optimized_insn *optinsn)
अणु
	वापस optinsn->insn != शून्य;
पूर्ण

/*
 * In ARM ISA, kprobe opt always replace one inकाष्ठाion (4 bytes
 * aligned and 4 bytes दीर्घ). It is impossible to encounter another
 * kprobe in the address range. So always वापस 0.
 */
पूर्णांक arch_check_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	वापस 0;
पूर्ण

/* Caller must ensure addr & 3 == 0 */
अटल पूर्णांक can_optimize(काष्ठा kprobe *kp)
अणु
	अगर (kp->ainsn.stack_space < 0)
		वापस 0;
	/*
	 * 255 is the biggest imm can be used in 'sub r0, r0, #<imm>'.
	 * Number larger than 255 needs special encoding.
	 */
	अगर (kp->ainsn.stack_space > 255 - माप(काष्ठा pt_regs))
		वापस 0;
	वापस 1;
पूर्ण

/* Free optimized inकाष्ठाion slot */
अटल व्योम
__arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op, पूर्णांक dirty)
अणु
	अगर (op->optinsn.insn) अणु
		मुक्त_optinsn_slot(op->optinsn.insn, dirty);
		op->optinsn.insn = शून्य;
	पूर्ण
पूर्ण

बाह्य व्योम kprobe_handler(काष्ठा pt_regs *regs);

अटल व्योम
optimized_callback(काष्ठा optimized_kprobe *op, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kprobe *p = &op->kp;
	काष्ठा kprobe_ctlblk *kcb;

	/* Save skipped रेजिस्टरs */
	regs->ARM_pc = (अचिन्हित दीर्घ)op->kp.addr;
	regs->ARM_ORIG_r0 = ~0UL;

	local_irq_save(flags);
	kcb = get_kprobe_ctlblk();

	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(&op->kp);
	पूर्ण अन्यथा अणु
		__this_cpu_ग_लिखो(current_kprobe, &op->kp);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_ग_लिखो(current_kprobe, शून्य);
	पूर्ण

	/*
	 * We singlestep the replaced inकाष्ठाion only when it can't be
	 * executed directly during restore.
	 */
	अगर (!p->ainsn.kprobe_direct_exec)
		op->kp.ainsn.insn_singlestep(p->opcode, &p->ainsn, regs);

	local_irq_restore(flags);
पूर्ण
NOKPROBE_SYMBOL(optimized_callback)

पूर्णांक arch_prepare_optimized_kprobe(काष्ठा optimized_kprobe *op, काष्ठा kprobe *orig)
अणु
	kprobe_opcode_t *code;
	अचिन्हित दीर्घ rel_chk;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ stack_protect = माप(काष्ठा pt_regs);

	अगर (!can_optimize(orig))
		वापस -EILSEQ;

	code = get_optinsn_slot();
	अगर (!code)
		वापस -ENOMEM;

	/*
	 * Verअगरy अगर the address gap is in 32MiB range, because this uses
	 * a relative jump.
	 *
	 * kprobe opt use a 'b' inकाष्ठाion to branch to optinsn.insn.
	 * According to ARM manual, branch inकाष्ठाion is:
	 *
	 *   31  28 27           24 23             0
	 *  +------+---+---+---+---+----------------+
	 *  | cond | 1 | 0 | 1 | 0 |      imm24     |
	 *  +------+---+---+---+---+----------------+
	 *
	 * imm24 is a चिन्हित 24 bits पूर्णांकeger. The real branch offset is computed
	 * by: imm32 = SignExtend(imm24:'00', 32);
	 *
	 * So the maximum क्रमward branch should be:
	 *   (0x007fffff << 2) = 0x01fffffc =  0x1fffffc
	 * The maximum backword branch should be:
	 *   (0xff800000 << 2) = 0xfe000000 = -0x2000000
	 *
	 * We can simply check (rel & 0xfe000003):
	 *  अगर rel is positive, (rel & 0xfe000000) shoule be 0
	 *  अगर rel is negitive, (rel & 0xfe000000) should be 0xfe000000
	 *  the last '3' is used क्रम alignment checking.
	 */
	rel_chk = (अचिन्हित दीर्घ)((दीर्घ)code -
			(दीर्घ)orig->addr + 8) & 0xfe000003;

	अगर ((rel_chk != 0) && (rel_chk != 0xfe000000)) अणु
		/*
		 * Dअगरferent from x86, we मुक्त code buf directly instead of
		 * calling __arch_हटाओ_optimized_kprobe() because
		 * we have not fill any field in op.
		 */
		मुक्त_optinsn_slot(code, 0);
		वापस -दुस्फल;
	पूर्ण

	/* Copy arch-dep-instance from ढाँचा. */
	स_नकल(code, (अचिन्हित दीर्घ *)optprobe_ढाँचा_entry,
			TMPL_END_IDX * माप(kprobe_opcode_t));

	/* Adjust buffer according to inकाष्ठाion. */
	BUG_ON(orig->ainsn.stack_space < 0);

	stack_protect += orig->ainsn.stack_space;

	/* Should have been filtered by can_optimize(). */
	BUG_ON(stack_protect > 255);

	/* Create a 'sub sp, sp, #<stack_protect>' */
	code[TMPL_SUB_SP] = __opcode_to_mem_arm(0xe24dd000 | stack_protect);
	/* Create a 'add r3, sp, #<stack_protect>' */
	code[TMPL_ADD_SP] = __opcode_to_mem_arm(0xe28d3000 | stack_protect);

	/* Set probe inक्रमmation */
	val = (अचिन्हित दीर्घ)op;
	code[TMPL_VAL_IDX] = val;

	/* Set probe function call */
	val = (अचिन्हित दीर्घ)optimized_callback;
	code[TMPL_CALL_IDX] = val;

	/* If possible, copy insn and have it executed during restore */
	orig->ainsn.kprobe_direct_exec = false;
	अगर (can_kprobe_direct_exec(orig->ainsn.रेजिस्टर_usage_flags)) अणु
		kprobe_opcode_t final_branch = arm_gen_branch(
				(अचिन्हित दीर्घ)(&code[TMPL_RESTORE_END]),
				(अचिन्हित दीर्घ)(op->kp.addr) + 4);
		अगर (final_branch != 0) अणु
			/*
			 * Replace original 'ldmia sp, {r0 - r15}' with
			 * 'ldmia {r0 - r14}', restore all रेजिस्टरs except pc.
			 */
			code[TMPL_RESTORE_BEGIN] = __opcode_to_mem_arm(0xe89d7fff);

			/* The original probed inकाष्ठाion */
			code[TMPL_RESTORE_ORIGN_INSN] = __opcode_to_mem_arm(orig->opcode);

			/* Jump back to next inकाष्ठाion */
			code[TMPL_RESTORE_END] = __opcode_to_mem_arm(final_branch);
			orig->ainsn.kprobe_direct_exec = true;
		पूर्ण
	पूर्ण

	flush_icache_range((अचिन्हित दीर्घ)code,
			   (अचिन्हित दीर्घ)(&code[TMPL_END_IDX]));

	/* Set op->optinsn.insn means prepared. */
	op->optinsn.insn = code;
	वापस 0;
पूर्ण

व्योम __kprobes arch_optimize_kprobes(काष्ठा list_head *oplist)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		अचिन्हित दीर्घ insn;
		WARN_ON(kprobe_disabled(&op->kp));

		/*
		 * Backup inकाष्ठाions which will be replaced
		 * by jump address
		 */
		स_नकल(op->optinsn.copied_insn, op->kp.addr,
				RELATIVEJUMP_SIZE);

		insn = arm_gen_branch((अचिन्हित दीर्घ)op->kp.addr,
				(अचिन्हित दीर्घ)op->optinsn.insn);
		BUG_ON(insn == 0);

		/*
		 * Make it a conditional branch अगर replaced insn
		 * is consitional
		 */
		insn = (__mem_to_opcode_arm(
			  op->optinsn.copied_insn[0]) & 0xf0000000) |
			(insn & 0x0fffffff);

		/*
		 * Similar to __arch_disarm_kprobe, operations which
		 * removing अवरोधpoपूर्णांकs must be wrapped by stop_machine
		 * to aव्योम racing.
		 */
		kprobes_हटाओ_अवरोधpoपूर्णांक(op->kp.addr, insn);

		list_del_init(&op->list);
	पूर्ण
पूर्ण

व्योम arch_unoptimize_kprobe(काष्ठा optimized_kprobe *op)
अणु
	arch_arm_kprobe(&op->kp);
पूर्ण

/*
 * Recover original inकाष्ठाions and अवरोधpoपूर्णांकs from relative jumps.
 * Caller must call with locking kprobe_mutex.
 */
व्योम arch_unoptimize_kprobes(काष्ठा list_head *oplist,
			    काष्ठा list_head *करोne_list)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		arch_unoptimize_kprobe(op);
		list_move(&op->list, करोne_list);
	पूर्ण
पूर्ण

पूर्णांक arch_within_optimized_kprobe(काष्ठा optimized_kprobe *op,
				अचिन्हित दीर्घ addr)
अणु
	वापस ((अचिन्हित दीर्घ)op->kp.addr <= addr &&
		(अचिन्हित दीर्घ)op->kp.addr + RELATIVEJUMP_SIZE > addr);
पूर्ण

व्योम arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	__arch_हटाओ_optimized_kprobe(op, 1);
पूर्ण
