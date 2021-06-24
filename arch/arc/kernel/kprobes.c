<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/types.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/disयंत्र.h>

#घोषणा MIN_STACK_SIZE(addr)	min((अचिन्हित दीर्घ)MAX_STACK_SIZE, \
		(अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_SIZE - (addr))

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	/* Attempt to probe at unaligned address */
	अगर ((अचिन्हित दीर्घ)p->addr & 0x01)
		वापस -EINVAL;

	/* Address should not be in exception handling code */

	p->ainsn.is_लघु = is_लघु_instr((अचिन्हित दीर्घ)p->addr);
	p->opcode = *p->addr;

	वापस 0;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = UNIMP_S_INSTRUCTION;

	flush_icache_range((अचिन्हित दीर्घ)p->addr,
			   (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t));
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = p->opcode;

	flush_icache_range((अचिन्हित दीर्घ)p->addr,
			   (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t));
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	arch_disarm_kprobe(p);

	/* Can we हटाओ the kprobe in the middle of kprobe handling? */
	अगर (p->ainsn.t1_addr) अणु
		*(p->ainsn.t1_addr) = p->ainsn.t1_opcode;

		flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t1_addr,
				   (अचिन्हित दीर्घ)p->ainsn.t1_addr +
				   माप(kprobe_opcode_t));

		p->ainsn.t1_addr = शून्य;
	पूर्ण

	अगर (p->ainsn.t2_addr) अणु
		*(p->ainsn.t2_addr) = p->ainsn.t2_opcode;

		flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t2_addr,
				   (अचिन्हित दीर्घ)p->ainsn.t2_addr +
				   माप(kprobe_opcode_t));

		p->ainsn.t2_addr = शून्य;
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

अटल अंतरभूत व्योम __kprobes set_current_kprobe(काष्ठा kprobe *p)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
पूर्ण

अटल व्योम __kprobes resume_execution(काष्ठा kprobe *p, अचिन्हित दीर्घ addr,
				       काष्ठा pt_regs *regs)
अणु
	/* Remove the trap inकाष्ठाions inserted क्रम single step and
	 * restore the original inकाष्ठाions
	 */
	अगर (p->ainsn.t1_addr) अणु
		*(p->ainsn.t1_addr) = p->ainsn.t1_opcode;

		flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t1_addr,
				   (अचिन्हित दीर्घ)p->ainsn.t1_addr +
				   माप(kprobe_opcode_t));

		p->ainsn.t1_addr = शून्य;
	पूर्ण

	अगर (p->ainsn.t2_addr) अणु
		*(p->ainsn.t2_addr) = p->ainsn.t2_opcode;

		flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t2_addr,
				   (अचिन्हित दीर्घ)p->ainsn.t2_addr +
				   माप(kprobe_opcode_t));

		p->ainsn.t2_addr = शून्य;
	पूर्ण

	वापस;
पूर्ण

अटल व्योम __kprobes setup_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ next_pc;
	अचिन्हित दीर्घ tgt_अगर_br = 0;
	पूर्णांक is_branch;
	अचिन्हित दीर्घ bta;

	/* Copy the opcode back to the kprobe location and execute the
	 * inकाष्ठाion. Because of this we will not be able to get पूर्णांकo the
	 * same kprobe until this kprobe is करोne
	 */
	*(p->addr) = p->opcode;

	flush_icache_range((अचिन्हित दीर्घ)p->addr,
			   (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t));

	/* Now we insert the trap at the next location after this inकाष्ठाion to
	 * single step. If it is a branch we insert the trap at possible branch
	 * tarमाला_लो
	 */

	bta = regs->bta;

	अगर (regs->status32 & 0x40) अणु
		/* We are in a delay slot with the branch taken */

		next_pc = bta & ~0x01;

		अगर (!p->ainsn.is_लघु) अणु
			अगर (bta & 0x01)
				regs->blink += 2;
			अन्यथा अणु
				/* Branch not taken */
				next_pc += 2;

				/* next pc is taken from bta after executing the
				 * delay slot inकाष्ठाion
				 */
				regs->bta += 2;
			पूर्ण
		पूर्ण

		is_branch = 0;
	पूर्ण अन्यथा
		is_branch =
		    disयंत्र_next_pc((अचिन्हित दीर्घ)p->addr, regs,
			(काष्ठा callee_regs *) current->thपढ़ो.callee_reg,
			&next_pc, &tgt_अगर_br);

	p->ainsn.t1_addr = (kprobe_opcode_t *) next_pc;
	p->ainsn.t1_opcode = *(p->ainsn.t1_addr);
	*(p->ainsn.t1_addr) = TRAP_S_2_INSTRUCTION;

	flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t1_addr,
			   (अचिन्हित दीर्घ)p->ainsn.t1_addr +
			   माप(kprobe_opcode_t));

	अगर (is_branch) अणु
		p->ainsn.t2_addr = (kprobe_opcode_t *) tgt_अगर_br;
		p->ainsn.t2_opcode = *(p->ainsn.t2_addr);
		*(p->ainsn.t2_addr) = TRAP_S_2_INSTRUCTION;

		flush_icache_range((अचिन्हित दीर्घ)p->ainsn.t2_addr,
				   (अचिन्हित दीर्घ)p->ainsn.t2_addr +
				   माप(kprobe_opcode_t));
	पूर्ण
पूर्ण

पूर्णांक __kprobes arc_kprobe_handler(अचिन्हित दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	काष्ठा kprobe_ctlblk *kcb;

	preempt_disable();

	kcb = get_kprobe_ctlblk();
	p = get_kprobe((अचिन्हित दीर्घ *)addr);

	अगर (p) अणु
		/*
		 * We have reentered the kprobe_handler, since another kprobe
		 * was hit जबतक within the handler, we save the original
		 * kprobes and single step on the inकाष्ठाion of the new probe
		 * without calling any user handlers to aव्योम recursive
		 * kprobes.
		 */
		अगर (kprobe_running()) अणु
			save_previous_kprobe(kcb);
			set_current_kprobe(p);
			kprobes_inc_nmissed_count(p);
			setup_singlestep(p, regs);
			kcb->kprobe_status = KPROBE_REENTER;
			वापस 1;
		पूर्ण

		set_current_kprobe(p);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;

		/* If we have no pre-handler or it वापसed 0, we जारी with
		 * normal processing. If we have a pre-handler and it वापसed
		 * non-zero - which means user handler setup रेजिस्टरs to निकास
		 * to another inकाष्ठाion, we must skip the single stepping.
		 */
		अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
			setup_singlestep(p, regs);
			kcb->kprobe_status = KPROBE_HIT_SS;
		पूर्ण अन्यथा अणु
			reset_current_kprobe();
			preempt_enable_no_resched();
		पूर्ण

		वापस 1;
	पूर्ण

	/* no_kprobe: */
	preempt_enable_no_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक __kprobes arc_post_kprobe_handler(अचिन्हित दीर्घ addr,
					 काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (!cur)
		वापस 0;

	resume_execution(cur, addr, regs);

	/* Rearm the kprobe */
	arch_arm_kprobe(cur);

	/*
	 * When we वापस from trap inकाष्ठाion we go to the next inकाष्ठाion
	 * We restored the actual inकाष्ठाion in resume_exectuiont and we to
	 * वापस to the same address and execute it
	 */
	regs->ret = addr;

	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		जाओ out;
	पूर्ण

	reset_current_kprobe();

out:
	preempt_enable_no_resched();
	वापस 1;
पूर्ण

/*
 * Fault can be क्रम the inकाष्ठाion being single stepped or क्रम the
 * pre/post handlers in the module.
 * This is applicable क्रम applications like user probes, where we have the
 * probe in user space and the handlers in the kernel
 */

पूर्णांक __kprobes kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single stepped
		 * caused the fault. We reset the current kprobe and allow the
		 * exception handler as अगर it is regular exception. In our
		 * हाल it करोesn't matter because the प्रणाली will be halted
		 */
		resume_execution(cur, (अचिन्हित दीर्घ)cur->addr, regs);

		अगर (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		अन्यथा
			reset_current_kprobe();

		preempt_enable_no_resched();
		अवरोध;

	हाल KPROBE_HIT_ACTIVE:
	हाल KPROBE_HIT_SSDONE:
		/*
		 * We are here because the inकाष्ठाions in the pre/post handler
		 * caused the fault.
		 */

		/* We increment the nmissed count क्रम accounting,
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
		 * In हाल the user-specअगरied fault handler वापसed zero,
		 * try to fix up.
		 */
		अगर (fixup_exception(regs))
			वापस 1;

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

पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;
	अचिन्हित दीर्घ addr = args->err;
	पूर्णांक ret = NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_IERR:
		अगर (arc_kprobe_handler(addr, args->regs))
			वापस NOTIFY_STOP;
		अवरोध;

	हाल DIE_TRAP:
		अगर (arc_post_kprobe_handler(addr, args->regs))
			वापस NOTIFY_STOP;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __used kretprobe_trampoline_holder(व्योम)
अणु
	__यंत्र__ __अस्थिर__(".global kretprobe_trampoline\n"
			     "kretprobe_trampoline:\n" "nop\n");
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु

	ri->ret_addr = (kprobe_opcode_t *) regs->blink;
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->blink = (अचिन्हित दीर्घ)&kretprobe_trampoline;
पूर्ण

अटल पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p,
					      काष्ठा pt_regs *regs)
अणु
	regs->ret = __kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);

	/* By वापसing a non zero value, we are telling the kprobe handler
	 * that we करोn't want the post_handler to run
	 */
	वापस 1;
पूर्ण

अटल काष्ठा kprobe trampoline_p = अणु
	.addr = (kprobe_opcode_t *) &kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	/* Registering the trampoline code क्रम the kret probe */
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->addr == (kprobe_opcode_t *) &kretprobe_trampoline)
		वापस 1;

	वापस 0;
पूर्ण

व्योम trap_is_kprobe(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs)
अणु
	notअगरy_die(DIE_TRAP, "kprobe_trap", regs, address, 0, SIGTRAP);
पूर्ण
