<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* arch/sparc64/kernel/kprobes.c
 *
 * Copyright (C) 2004 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/extable.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/slab.h>
#समावेश <linux/context_tracking.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>

/* We करो not have hardware single-stepping on sparc64.
 * So we implement software single-stepping with अवरोधpoपूर्णांक
 * traps.  The top-level scheme is similar to that used
 * in the x86 kprobes implementation.
 *
 * In the kprobe->ainsn.insn[] array we store the original
 * inकाष्ठाion at index zero and a अवरोध inकाष्ठाion at
 * index one.
 *
 * When we hit a kprobe we:
 * - Run the pre-handler
 * - Remember "regs->tnpc" and पूर्णांकerrupt level stored in
 *   "regs->tstate" so we can restore them later
 * - Disable PIL पूर्णांकerrupts
 * - Set regs->tpc to poपूर्णांक to kprobe->ainsn.insn[0]
 * - Set regs->tnpc to poपूर्णांक to kprobe->ainsn.insn[1]
 * - Mark that we are actively in a kprobe
 *
 * At this poपूर्णांक we रुको क्रम the second अवरोधpoपूर्णांक at
 * kprobe->ainsn.insn[1] to hit.  When it करोes we:
 * - Run the post-handler
 * - Set regs->tpc to "remembered" regs->tnpc stored above,
 *   restore the PIL पूर्णांकerrupt level in "regs->tstate" as well
 * - Make any adjusपंचांगents necessary to regs->tnpc in order
 *   to handle relative branches correctly.  See below.
 * - Mark that we are no दीर्घer actively in a kprobe.
 */

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[] = अणुअणुशून्य, शून्यपूर्णपूर्ण;

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अगर ((अचिन्हित दीर्घ) p->addr & 0x3UL)
		वापस -EILSEQ;

	p->ainsn.insn[0] = *p->addr;
	flushi(&p->ainsn.insn[0]);

	p->ainsn.insn[1] = BREAKPOINT_INSTRUCTION_2;
	flushi(&p->ainsn.insn[1]);

	p->opcode = *p->addr;
	वापस 0;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = BREAKPOINT_INSTRUCTION;
	flushi(p->addr);
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = p->opcode;
	flushi(p->addr);
पूर्ण

अटल व्योम __kprobes save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
	kcb->prev_kprobe.orig_tnpc = kcb->kprobe_orig_tnpc;
	kcb->prev_kprobe.orig_tstate_pil = kcb->kprobe_orig_tstate_pil;
पूर्ण

अटल व्योम __kprobes restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
	kcb->kprobe_orig_tnpc = kcb->prev_kprobe.orig_tnpc;
	kcb->kprobe_orig_tstate_pil = kcb->prev_kprobe.orig_tstate_pil;
पूर्ण

अटल व्योम __kprobes set_current_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
				काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
	kcb->kprobe_orig_tnpc = regs->tnpc;
	kcb->kprobe_orig_tstate_pil = (regs->tstate & TSTATE_PIL);
पूर्ण

अटल व्योम __kprobes prepare_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			काष्ठा kprobe_ctlblk *kcb)
अणु
	regs->tstate |= TSTATE_PIL;

	/*single step अंतरभूत, अगर it a अवरोधpoपूर्णांक inकाष्ठाion*/
	अगर (p->opcode == BREAKPOINT_INSTRUCTION) अणु
		regs->tpc = (अचिन्हित दीर्घ) p->addr;
		regs->tnpc = kcb->kprobe_orig_tnpc;
	पूर्ण अन्यथा अणु
		regs->tpc = (अचिन्हित दीर्घ) &p->ainsn.insn[0];
		regs->tnpc = (अचिन्हित दीर्घ) &p->ainsn.insn[1];
	पूर्ण
पूर्ण

अटल पूर्णांक __kprobes kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	व्योम *addr = (व्योम *) regs->tpc;
	पूर्णांक ret = 0;
	काष्ठा kprobe_ctlblk *kcb;

	/*
	 * We करोn't want to be preempted क्रम the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	अगर (kprobe_running()) अणु
		p = get_kprobe(addr);
		अगर (p) अणु
			अगर (kcb->kprobe_status == KPROBE_HIT_SS) अणु
				regs->tstate = ((regs->tstate & ~TSTATE_PIL) |
					kcb->kprobe_orig_tstate_pil);
				जाओ no_kprobe;
			पूर्ण
			/* We have reentered the kprobe_handler(), since
			 * another probe was hit जबतक within the handler.
			 * We here save the original kprobes variables and
			 * just single step on the inकाष्ठाion of the new probe
			 * without calling any user handlers.
			 */
			save_previous_kprobe(kcb);
			set_current_kprobe(p, regs, kcb);
			kprobes_inc_nmissed_count(p);
			kcb->kprobe_status = KPROBE_REENTER;
			prepare_singlestep(p, regs, kcb);
			वापस 1;
		पूर्ण अन्यथा अगर (*(u32 *)addr != BREAKPOINT_INSTRUCTION) अणु
			/* The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd by
			 * another cpu right after we hit, no further
			 * handling of this पूर्णांकerrupt is appropriate
			 */
			ret = 1;
		पूर्ण
		जाओ no_kprobe;
	पूर्ण

	p = get_kprobe(addr);
	अगर (!p) अणु
		अगर (*(u32 *)addr != BREAKPOINT_INSTRUCTION) अणु
			/*
			 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
			 * after we hit it.  Another cpu has हटाओd
			 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
			 * at this address.  In either हाल, no further
			 * handling of this पूर्णांकerrupt is appropriate.
			 */
			ret = 1;
		पूर्ण
		/* Not one of ours: let kernel handle it */
		जाओ no_kprobe;
	पूर्ण

	set_current_kprobe(p, regs, kcb);
	kcb->kprobe_status = KPROBE_HIT_ACTIVE;
	अगर (p->pre_handler && p->pre_handler(p, regs)) अणु
		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण

	prepare_singlestep(p, regs, kcb);
	kcb->kprobe_status = KPROBE_HIT_SS;
	वापस 1;

no_kprobe:
	preempt_enable_no_resched();
	वापस ret;
पूर्ण

/* If INSN is a relative control transfer inकाष्ठाion,
 * वापस the corrected branch destination value.
 *
 * regs->tpc and regs->tnpc still hold the values of the
 * program counters at the समय of trap due to the execution
 * of the BREAKPOINT_INSTRUCTION_2 at p->ainsn.insn[1]
 * 
 */
अटल अचिन्हित दीर्घ __kprobes relbranch_fixup(u32 insn, काष्ठा kprobe *p,
					       काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ real_pc = (अचिन्हित दीर्घ) p->addr;

	/* Branch not taken, no mods necessary.  */
	अगर (regs->tnpc == regs->tpc + 0x4UL)
		वापस real_pc + 0x8UL;

	/* The three हालs are call, branch w/prediction,
	 * and traditional branch.
	 */
	अगर ((insn & 0xc0000000) == 0x40000000 ||
	    (insn & 0xc1c00000) == 0x00400000 ||
	    (insn & 0xc1c00000) == 0x00800000) अणु
		अचिन्हित दीर्घ ainsn_addr;

		ainsn_addr = (अचिन्हित दीर्घ) &p->ainsn.insn[0];

		/* The inकाष्ठाion did all the work क्रम us
		 * alपढ़ोy, just apply the offset to the correct
		 * inकाष्ठाion location.
		 */
		वापस (real_pc + (regs->tnpc - ainsn_addr));
	पूर्ण

	/* It is jmpl or some other असलolute PC modअगरication inकाष्ठाion,
	 * leave NPC as-is.
	 */
	वापस regs->tnpc;
पूर्ण

/* If INSN is an inकाष्ठाion which ग_लिखोs it's PC location
 * पूर्णांकo a destination रेजिस्टर, fix that up.
 */
अटल व्योम __kprobes retpc_fixup(काष्ठा pt_regs *regs, u32 insn,
				  अचिन्हित दीर्घ real_pc)
अणु
	अचिन्हित दीर्घ *slot = शून्य;

	/* Simplest हाल is 'call', which always uses %o7 */
	अगर ((insn & 0xc0000000) == 0x40000000) अणु
		slot = &regs->u_regs[UREG_I7];
	पूर्ण

	/* 'jmpl' encodes the रेजिस्टर inside of the opcode */
	अगर ((insn & 0xc1f80000) == 0x81c00000) अणु
		अचिन्हित दीर्घ rd = ((insn >> 25) & 0x1f);

		अगर (rd <= 15) अणु
			slot = &regs->u_regs[rd];
		पूर्ण अन्यथा अणु
			/* Hard हाल, it goes onto the stack. */
			flushw_all();

			rd -= 16;
			slot = (अचिन्हित दीर्घ *)
				(regs->u_regs[UREG_FP] + STACK_BIAS);
			slot += rd;
		पूर्ण
	पूर्ण
	अगर (slot != शून्य)
		*slot = real_pc;
पूर्ण

/*
 * Called after single-stepping.  p->addr is the address of the
 * inकाष्ठाion which has been replaced by the अवरोधpoपूर्णांक
 * inकाष्ठाion.  To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.  The address of this
 * copy is &p->ainsn.insn[0].
 *
 * This function prepares to वापस from the post-single-step
 * अवरोधpoपूर्णांक trap.
 */
अटल व्योम __kprobes resume_execution(काष्ठा kprobe *p,
		काष्ठा pt_regs *regs, काष्ठा kprobe_ctlblk *kcb)
अणु
	u32 insn = p->ainsn.insn[0];

	regs->tnpc = relbranch_fixup(insn, p, regs);

	/* This assignment must occur after relbranch_fixup() */
	regs->tpc = kcb->kprobe_orig_tnpc;

	retpc_fixup(regs, insn, (अचिन्हित दीर्घ) p->addr);

	regs->tstate = ((regs->tstate & ~TSTATE_PIL) |
			kcb->kprobe_orig_tstate_pil);
पूर्ण

अटल पूर्णांक __kprobes post_kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (!cur)
		वापस 0;

	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	resume_execution(cur, regs, kcb);

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
	स्थिर काष्ठा exception_table_entry *entry;

	चयन(kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the tpc poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->tpc = (अचिन्हित दीर्घ)cur->addr;
		regs->tnpc = kcb->kprobe_orig_tnpc;
		regs->tstate = ((regs->tstate & ~TSTATE_PIL) |
				kcb->kprobe_orig_tstate_pil);
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

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस 1;
		पूर्ण

		/*
		 * fixup_exception() could not handle it,
		 * Let करो_page_fault() fix it.
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wrapper routine to क्रम handling exceptions.
 */
पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *)data;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (args->regs && user_mode(args->regs))
		वापस ret;

	चयन (val) अणु
	हाल DIE_DEBUG:
		अगर (kprobe_handler(args->regs))
			ret = NOTIFY_STOP;
		अवरोध;
	हाल DIE_DEBUG_2:
		अगर (post_kprobe_handler(args->regs))
			ret = NOTIFY_STOP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

यंत्रlinkage व्योम __kprobes kprobe_trap(अचिन्हित दीर्घ trap_level,
				      काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	BUG_ON(trap_level != 0x170 && trap_level != 0x171);

	अगर (user_mode(regs)) अणु
		local_irq_enable();
		bad_trap(regs, trap_level);
		जाओ out;
	पूर्ण

	/* trap_level == 0x170 --> ta 0x70
	 * trap_level == 0x171 --> ta 0x71
	 */
	अगर (notअगरy_die((trap_level == 0x170) ? DIE_DEBUG : DIE_DEBUG_2,
		       (trap_level == 0x170) ? "debug" : "debug_2",
		       regs, 0, trap_level, SIGTRAP) != NOTIFY_STOP)
		bad_trap(regs, trap_level);
out:
	exception_निकास(prev_state);
पूर्ण

/* The value stored in the वापस address रेजिस्टर is actually 2
 * inकाष्ठाions beक्रमe where the callee will वापस to.
 * Sequences usually look something like this
 *
 *		call	some_function	<--- वापस रेजिस्टर poपूर्णांकs here
 *		 nop			<--- call delay slot
 *		whatever		<--- where callee वापसs to
 *
 * To keep trampoline_probe_handler logic simpler, we normalize the
 * value kept in ri->ret_addr so we करोn't need to keep adjusting it
 * back and क्रमth.
 */
व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)(regs->u_regs[UREG_RETPC] + 8);
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->u_regs[UREG_RETPC] =
		((अचिन्हित दीर्घ)kretprobe_trampoline) - 8;
पूर्ण

/*
 * Called when the probe at kretprobe trampoline is hit
 */
अटल पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p,
					      काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_address = 0;

	orig_ret_address = __kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);
	regs->tpc = orig_ret_address;
	regs->tnpc = orig_ret_address + 4;

	/*
	 * By वापसing a non-zero value, we are telling
	 * kprobe_handler() that we करोn't want the post_handler
	 * to run (and have re-enabled preemption)
	 */
	वापस 1;
पूर्ण

अटल व्योम __used kretprobe_trampoline_holder(व्योम)
अणु
	यंत्र अस्थिर(".global kretprobe_trampoline\n"
		     "kretprobe_trampoline:\n"
		     "\tnop\n"
		     "\tnop\n");
पूर्ण
अटल काष्ठा kprobe trampoline_p = अणु
	.addr = (kprobe_opcode_t *) &kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->addr == (kprobe_opcode_t *)&kretprobe_trampoline)
		वापस 1;

	वापस 0;
पूर्ण
