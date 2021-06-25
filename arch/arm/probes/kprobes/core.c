<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/kprobes.c
 *
 * Kprobes on ARM
 *
 * Abhishek Sagar <sagar.abhishek@gmail.com>
 * Copyright (C) 2006, 2007 Motorola Inc.
 *
 * Nicolas Pitre <nico@marvell.com>
 * Copyright (C) 2007 Marvell Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/percpu.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/sections.h>

#समावेश "../decode-arm.h"
#समावेश "../decode-thumb.h"
#समावेश "core.h"

#घोषणा MIN_STACK_SIZE(addr) 				\
	min((अचिन्हित दीर्घ)MAX_STACK_SIZE,		\
	    (अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_START_SP - (addr))

#घोषणा flush_insns(addr, size)				\
	flush_icache_range((अचिन्हित दीर्घ)(addr),	\
			   (अचिन्हित दीर्घ)(addr) +	\
			   (size))

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);


पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	kprobe_opcode_t insn;
	kprobe_opcode_t पंचांगp_insn[MAX_INSN_SIZE];
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)p->addr;
	bool thumb;
	kprobe_decode_insn_t *decode_insn;
	स्थिर जोड़ decode_action *actions;
	पूर्णांक is;
	स्थिर काष्ठा decode_checker **checkers;

#अगर_घोषित CONFIG_THUMB2_KERNEL
	thumb = true;
	addr &= ~1; /* Bit 0 would normally be set to indicate Thumb code */
	insn = __mem_to_opcode_thumb16(((u16 *)addr)[0]);
	अगर (is_wide_inकाष्ठाion(insn)) अणु
		u16 inst2 = __mem_to_opcode_thumb16(((u16 *)addr)[1]);
		insn = __opcode_thumb32_compose(insn, inst2);
		decode_insn = thumb32_probes_decode_insn;
		actions = kprobes_t32_actions;
		checkers = kprobes_t32_checkers;
	पूर्ण अन्यथा अणु
		decode_insn = thumb16_probes_decode_insn;
		actions = kprobes_t16_actions;
		checkers = kprobes_t16_checkers;
	पूर्ण
#अन्यथा /* !CONFIG_THUMB2_KERNEL */
	thumb = false;
	अगर (addr & 0x3)
		वापस -EINVAL;
	insn = __mem_to_opcode_arm(*p->addr);
	decode_insn = arm_probes_decode_insn;
	actions = kprobes_arm_actions;
	checkers = kprobes_arm_checkers;
#पूर्ण_अगर

	p->opcode = insn;
	p->ainsn.insn = पंचांगp_insn;

	चयन ((*decode_insn)(insn, &p->ainsn, true, actions, checkers)) अणु
	हाल INSN_REJECTED:	/* not supported */
		वापस -EINVAL;

	हाल INSN_GOOD:		/* inकाष्ठाion uses slot */
		p->ainsn.insn = get_insn_slot();
		अगर (!p->ainsn.insn)
			वापस -ENOMEM;
		क्रम (is = 0; is < MAX_INSN_SIZE; ++is)
			p->ainsn.insn[is] = पंचांगp_insn[is];
		flush_insns(p->ainsn.insn,
				माप(p->ainsn.insn[0]) * MAX_INSN_SIZE);
		p->ainsn.insn_fn = (probes_insn_fn_t *)
					((uपूर्णांकptr_t)p->ainsn.insn | thumb);
		अवरोध;

	हाल INSN_GOOD_NO_SLOT:	/* inकाष्ठाion करोesn't need insn slot */
		p->ainsn.insn = शून्य;
		अवरोध;
	पूर्ण

	/*
	 * Never instrument insn like 'str r0, [sp, +/-r1]'. Also, insn likes
	 * 'str r0, [sp, #-68]' should also be prohibited.
	 * See __und_svc.
	 */
	अगर ((p->ainsn.stack_space < 0) ||
			(p->ainsn.stack_space > MAX_STACK_SIZE))
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित पूर्णांक brkp;
	व्योम *addr;

	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL)) अणु
		/* Remove any Thumb flag */
		addr = (व्योम *)((uपूर्णांकptr_t)p->addr & ~1);

		अगर (is_wide_inकाष्ठाion(p->opcode))
			brkp = KPROBE_THUMB32_BREAKPOINT_INSTRUCTION;
		अन्यथा
			brkp = KPROBE_THUMB16_BREAKPOINT_INSTRUCTION;
	पूर्ण अन्यथा अणु
		kprobe_opcode_t insn = p->opcode;

		addr = p->addr;
		brkp = KPROBE_ARM_BREAKPOINT_INSTRUCTION;

		अगर (insn >= 0xe0000000)
			brkp |= 0xe0000000;  /* Unconditional inकाष्ठाion */
		अन्यथा
			brkp |= insn & 0xf0000000;  /* Copy condition from insn */
	पूर्ण

	patch_text(addr, brkp);
पूर्ण

/*
 * The actual disarming is करोne here on each CPU and synchronized using
 * stop_machine. This synchronization is necessary on SMP to aव्योम removing
 * a probe between the moment the 'Undefined Instruction' exception is उठाओd
 * and the moment the exception handler पढ़ोs the faulting inकाष्ठाion from
 * memory. It is also needed to atomically set the two half-words of a 32-bit
 * Thumb अवरोधpoपूर्णांक.
 */
काष्ठा patch अणु
	व्योम *addr;
	अचिन्हित पूर्णांक insn;
पूर्ण;

अटल पूर्णांक __kprobes_हटाओ_अवरोधpoपूर्णांक(व्योम *data)
अणु
	काष्ठा patch *p = data;
	__patch_text(p->addr, p->insn);
	वापस 0;
पूर्ण

व्योम __kprobes kprobes_हटाओ_अवरोधpoपूर्णांक(व्योम *addr, अचिन्हित पूर्णांक insn)
अणु
	काष्ठा patch p = अणु
		.addr = addr,
		.insn = insn,
	पूर्ण;
	stop_machine_cpuslocked(__kprobes_हटाओ_अवरोधpoपूर्णांक, &p,
				cpu_online_mask);
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	kprobes_हटाओ_अवरोधpoपूर्णांक((व्योम *)((uपूर्णांकptr_t)p->addr & ~1),
			p->opcode);
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.insn) अणु
		मुक्त_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __kprobes save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
पूर्ण

अटल व्योम __kprobes restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
पूर्ण

अटल व्योम __kprobes set_current_kprobe(काष्ठा kprobe *p)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
पूर्ण

अटल व्योम __kprobes
singlestep_skip(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	regs->ARM_cpsr = it_advance(regs->ARM_cpsr);
	अगर (is_wide_inकाष्ठाion(p->opcode))
		regs->ARM_pc += 4;
	अन्यथा
		regs->ARM_pc += 2;
#अन्यथा
	regs->ARM_pc += 4;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __kprobes
singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs, काष्ठा kprobe_ctlblk *kcb)
अणु
	p->ainsn.insn_singlestep(p->opcode, &p->ainsn, regs);
पूर्ण

/*
 * Called with IRQs disabled. IRQs must reमुख्य disabled from that poपूर्णांक
 * all the way until processing this kprobe is complete.  The current
 * kprobes implementation cannot process more than one nested level of
 * kprobe, and that level is reserved क्रम user kprobe handlers, so we can't
 * risk encountering a new kprobe in an पूर्णांकerrupt handler.
 */
व्योम __kprobes kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p, *cur;
	काष्ठा kprobe_ctlblk *kcb;

	kcb = get_kprobe_ctlblk();
	cur = kprobe_running();

#अगर_घोषित CONFIG_THUMB2_KERNEL
	/*
	 * First look क्रम a probe which was रेजिस्टरed using an address with
	 * bit 0 set, this is the usual situation क्रम poपूर्णांकers to Thumb code.
	 * If not found, fallback to looking क्रम one with bit 0 clear.
	 */
	p = get_kprobe((kprobe_opcode_t *)(regs->ARM_pc | 1));
	अगर (!p)
		p = get_kprobe((kprobe_opcode_t *)regs->ARM_pc);

#अन्यथा /* ! CONFIG_THUMB2_KERNEL */
	p = get_kprobe((kprobe_opcode_t *)regs->ARM_pc);
#पूर्ण_अगर

	अगर (p) अणु
		अगर (!p->ainsn.insn_check_cc(regs->ARM_cpsr)) अणु
			/*
			 * Probe hit but conditional execution check failed,
			 * so just skip the inकाष्ठाion and जारी as अगर
			 * nothing had happened.
			 * In this हाल, we can skip recursing check too.
			 */
			singlestep_skip(p, regs);
		पूर्ण अन्यथा अगर (cur) अणु
			/* Kprobe is pending, so we're recursing. */
			चयन (kcb->kprobe_status) अणु
			हाल KPROBE_HIT_ACTIVE:
			हाल KPROBE_HIT_SSDONE:
			हाल KPROBE_HIT_SS:
				/* A pre- or post-handler probe got us here. */
				kprobes_inc_nmissed_count(p);
				save_previous_kprobe(kcb);
				set_current_kprobe(p);
				kcb->kprobe_status = KPROBE_REENTER;
				singlestep(p, regs, kcb);
				restore_previous_kprobe(kcb);
				अवरोध;
			हाल KPROBE_REENTER:
				/* A nested probe was hit in FIQ, it is a BUG */
				pr_warn("Unrecoverable kprobe detected.\n");
				dump_kprobe(p);
				fallthrough;
			शेष:
				/* impossible हालs */
				BUG();
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Probe hit and conditional execution check ok. */
			set_current_kprobe(p);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;

			/*
			 * If we have no pre-handler or it वापसed 0, we
			 * जारी with normal processing. If we have a
			 * pre-handler and it वापसed non-zero, it will
			 * modअगरy the execution path and no need to single
			 * stepping. Let's just reset current kprobe and निकास.
			 */
			अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
				kcb->kprobe_status = KPROBE_HIT_SS;
				singlestep(p, regs, kcb);
				अगर (p->post_handler) अणु
					kcb->kprobe_status = KPROBE_HIT_SSDONE;
					p->post_handler(p, regs, 0);
				पूर्ण
			पूर्ण
			reset_current_kprobe();
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The probe was हटाओd and a race is in progress.
		 * There is nothing we can करो about it.  Let's restart
		 * the inकाष्ठाion.  By the समय we can restart, the
		 * real inकाष्ठाion will be there.
		 */
	पूर्ण
पूर्ण

अटल पूर्णांक __kprobes kprobe_trap_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	kprobe_handler(regs);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

पूर्णांक __kprobes kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक fsr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the PC to poपूर्णांक back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->ARM_pc = (दीर्घ)cur->addr;
		अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
			restore_previous_kprobe(kcb);
		पूर्ण अन्यथा अणु
			reset_current_kprobe();
		पूर्ण
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
		 * user-specअगरied handler try to fix it.
		 */
		अगर (cur->fault_handler && cur->fault_handler(cur, regs, fsr))
			वापस 1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	/*
	 * notअगरy_die() is currently never called on ARM,
	 * so this callback is currently empty.
	 */
	वापस NOTIFY_DONE;
पूर्ण

/*
 * When a retprobed function वापसs, trampoline_handler() is called,
 * calling the kretprobe's handler. We स्थिरruct a काष्ठा pt_regs to
 * give a view of रेजिस्टरs r0-r11 to the user वापस-handler.  This is
 * not a complete pt_regs काष्ठाure, but that should be plenty sufficient
 * क्रम kretprobe handlers which should normally be पूर्णांकerested in r0 only
 * anyway.
 */
व्योम __naked __kprobes kretprobe_trampoline(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"stmdb	sp!, {r0 - r11}		\n\t"
		"mov	r0, sp			\n\t"
		"bl	trampoline_handler	\n\t"
		"mov	lr, r0			\n\t"
		"ldmia	sp!, {r0 - r11}		\n\t"
#अगर_घोषित CONFIG_THUMB2_KERNEL
		"bx	lr			\n\t"
#अन्यथा
		"mov	pc, lr			\n\t"
#पूर्ण_अगर
		: : : "memory");
पूर्ण

/* Called from kretprobe_trampoline */
अटल __used __kprobes व्योम *trampoline_handler(काष्ठा pt_regs *regs)
अणु
	वापस (व्योम *)kretprobe_trampoline_handler(regs, &kretprobe_trampoline,
						    (व्योम *)regs->ARM_fp);
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->ARM_lr;
	ri->fp = (व्योम *)regs->ARM_fp;

	/* Replace the वापस addr with trampoline addr. */
	regs->ARM_lr = (अचिन्हित दीर्घ)&kretprobe_trampoline;
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_THUMB2_KERNEL

अटल काष्ठा undef_hook kprobes_thumb16_अवरोध_hook = अणु
	.instr_mask	= 0xffff,
	.instr_val	= KPROBE_THUMB16_BREAKPOINT_INSTRUCTION,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= kprobe_trap_handler,
पूर्ण;

अटल काष्ठा undef_hook kprobes_thumb32_अवरोध_hook = अणु
	.instr_mask	= 0xffffffff,
	.instr_val	= KPROBE_THUMB32_BREAKPOINT_INSTRUCTION,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= kprobe_trap_handler,
पूर्ण;

#अन्यथा  /* !CONFIG_THUMB2_KERNEL */

अटल काष्ठा undef_hook kprobes_arm_अवरोध_hook = अणु
	.instr_mask	= 0x0fffffff,
	.instr_val	= KPROBE_ARM_BREAKPOINT_INSTRUCTION,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= kprobe_trap_handler,
पूर्ण;

#पूर्ण_अगर /* !CONFIG_THUMB2_KERNEL */

पूर्णांक __init arch_init_kprobes()
अणु
	arm_probes_decode_init();
#अगर_घोषित CONFIG_THUMB2_KERNEL
	रेजिस्टर_undef_hook(&kprobes_thumb16_अवरोध_hook);
	रेजिस्टर_undef_hook(&kprobes_thumb32_अवरोध_hook);
#अन्यथा
	रेजिस्टर_undef_hook(&kprobes_arm_अवरोध_hook);
#पूर्ण_अगर
	वापस 0;
पूर्ण

bool arch_within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	व्योम *a = (व्योम *)addr;

	वापस __in_irqentry_text(addr) ||
	       in_entry_text(addr) ||
	       in_idmap_text(addr) ||
	       memory_contains(__kprobes_text_start, __kprobes_text_end, a, 1);
पूर्ण
