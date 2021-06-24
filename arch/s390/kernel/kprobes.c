<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright IBM Corp. 2002, 2006
 *
 * s390 port, used ppc64 as ढाँचा. Mike Grundy <grundym@us.ibm.com>
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/preempt.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/extable.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/dis.h>
#समावेश "entry.h"

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe);
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[] = अणु पूर्ण;

DEFINE_INSN_CACHE_OPS(s390_insn);

अटल पूर्णांक insn_page_in_use;

व्योम *alloc_insn_page(व्योम)
अणु
	व्योम *page;

	page = module_alloc(PAGE_SIZE);
	अगर (!page)
		वापस शून्य;
	__set_memory((अचिन्हित दीर्घ) page, 1, SET_MEMORY_RO | SET_MEMORY_X);
	वापस page;
पूर्ण

व्योम मुक्त_insn_page(व्योम *page)
अणु
	module_memमुक्त(page);
पूर्ण

अटल व्योम *alloc_s390_insn_page(व्योम)
अणु
	अगर (xchg(&insn_page_in_use, 1) == 1)
		वापस शून्य;
	वापस &kprobes_insn_page;
पूर्ण

अटल व्योम मुक्त_s390_insn_page(व्योम *page)
अणु
	xchg(&insn_page_in_use, 0);
पूर्ण

काष्ठा kprobe_insn_cache kprobe_s390_insn_slots = अणु
	.mutex = __MUTEX_INITIALIZER(kprobe_s390_insn_slots.mutex),
	.alloc = alloc_s390_insn_page,
	.मुक्त = मुक्त_s390_insn_page,
	.pages = LIST_HEAD_INIT(kprobe_s390_insn_slots.pages),
	.insn_size = MAX_INSN_SIZE,
पूर्ण;

अटल व्योम copy_inकाष्ठाion(काष्ठा kprobe *p)
अणु
	kprobe_opcode_t insn[MAX_INSN_SIZE];
	s64 disp, new_disp;
	u64 addr, new_addr;
	अचिन्हित पूर्णांक len;

	len = insn_length(*p->addr >> 8);
	स_नकल(&insn, p->addr, len);
	p->opcode = insn[0];
	अगर (probe_is_insn_relative_दीर्घ(&insn[0])) अणु
		/*
		 * For pc-relative inकाष्ठाions in RIL-b or RIL-c क्रमmat patch
		 * the RI2 displacement field. We have alपढ़ोy made sure that
		 * the insn slot क्रम the patched inकाष्ठाion is within the same
		 * 2GB area as the original inकाष्ठाion (either kernel image or
		 * module area). Thereक्रमe the new displacement will always fit.
		 */
		disp = *(s32 *)&insn[1];
		addr = (u64)(अचिन्हित दीर्घ)p->addr;
		new_addr = (u64)(अचिन्हित दीर्घ)p->ainsn.insn;
		new_disp = ((addr + (disp * 2)) - new_addr) / 2;
		*(s32 *)&insn[1] = new_disp;
	पूर्ण
	s390_kernel_ग_लिखो(p->ainsn.insn, &insn, len);
पूर्ण
NOKPROBE_SYMBOL(copy_inकाष्ठाion);

अटल अंतरभूत पूर्णांक is_kernel_addr(व्योम *addr)
अणु
	वापस addr < (व्योम *)_end;
पूर्ण

अटल पूर्णांक s390_get_insn_slot(काष्ठा kprobe *p)
अणु
	/*
	 * Get an insn slot that is within the same 2GB area like the original
	 * inकाष्ठाion. That way inकाष्ठाions with a 32bit चिन्हित displacement
	 * field can be patched and executed within the insn slot.
	 */
	p->ainsn.insn = शून्य;
	अगर (is_kernel_addr(p->addr))
		p->ainsn.insn = get_s390_insn_slot();
	अन्यथा अगर (is_module_addr(p->addr))
		p->ainsn.insn = get_insn_slot();
	वापस p->ainsn.insn ? 0 : -ENOMEM;
पूर्ण
NOKPROBE_SYMBOL(s390_get_insn_slot);

अटल व्योम s390_मुक्त_insn_slot(काष्ठा kprobe *p)
अणु
	अगर (!p->ainsn.insn)
		वापस;
	अगर (is_kernel_addr(p->addr))
		मुक्त_s390_insn_slot(p->ainsn.insn, 0);
	अन्यथा
		मुक्त_insn_slot(p->ainsn.insn, 0);
	p->ainsn.insn = शून्य;
पूर्ण
NOKPROBE_SYMBOL(s390_मुक्त_insn_slot);

पूर्णांक arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अगर ((अचिन्हित दीर्घ) p->addr & 0x01)
		वापस -EINVAL;
	/* Make sure the probe isn't going on a dअगरficult inकाष्ठाion */
	अगर (probe_is_prohibited_opcode(p->addr))
		वापस -EINVAL;
	अगर (s390_get_insn_slot(p))
		वापस -ENOMEM;
	copy_inकाष्ठाion(p);
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(arch_prepare_kprobe);

काष्ठा swap_insn_args अणु
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक arm_kprobe : 1;
पूर्ण;

अटल पूर्णांक swap_inकाष्ठाion(व्योम *data)
अणु
	काष्ठा swap_insn_args *args = data;
	काष्ठा kprobe *p = args->p;
	u16 opc;

	opc = args->arm_kprobe ? BREAKPOINT_INSTRUCTION : p->opcode;
	s390_kernel_ग_लिखो(p->addr, &opc, माप(opc));
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(swap_inकाष्ठाion);

व्योम arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा swap_insn_args args = अणु.p = p, .arm_kprobe = 1पूर्ण;

	stop_machine_cpuslocked(swap_inकाष्ठाion, &args, शून्य);
पूर्ण
NOKPROBE_SYMBOL(arch_arm_kprobe);

व्योम arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा swap_insn_args args = अणु.p = p, .arm_kprobe = 0पूर्ण;

	stop_machine_cpuslocked(swap_inकाष्ठाion, &args, शून्य);
पूर्ण
NOKPROBE_SYMBOL(arch_disarm_kprobe);

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	s390_मुक्त_insn_slot(p);
पूर्ण
NOKPROBE_SYMBOL(arch_हटाओ_kprobe);

अटल व्योम enable_singlestep(काष्ठा kprobe_ctlblk *kcb,
			      काष्ठा pt_regs *regs,
			      अचिन्हित दीर्घ ip)
अणु
	काष्ठा per_regs per_kprobe;

	/* Set up the PER control रेजिस्टरs %cr9-%cr11 */
	per_kprobe.control = PER_EVENT_IFETCH;
	per_kprobe.start = ip;
	per_kprobe.end = ip;

	/* Save control regs and psw mask */
	__ctl_store(kcb->kprobe_saved_ctl, 9, 11);
	kcb->kprobe_saved_imask = regs->psw.mask &
		(PSW_MASK_PER | PSW_MASK_IO | PSW_MASK_EXT);

	/* Set PER control regs, turns on single step क्रम the given address */
	__ctl_load(per_kprobe, 9, 11);
	regs->psw.mask |= PSW_MASK_PER;
	regs->psw.mask &= ~(PSW_MASK_IO | PSW_MASK_EXT);
	regs->psw.addr = ip;
पूर्ण
NOKPROBE_SYMBOL(enable_singlestep);

अटल व्योम disable_singlestep(काष्ठा kprobe_ctlblk *kcb,
			       काष्ठा pt_regs *regs,
			       अचिन्हित दीर्घ ip)
अणु
	/* Restore control regs and psw mask, set new psw address */
	__ctl_load(kcb->kprobe_saved_ctl, 9, 11);
	regs->psw.mask &= ~PSW_MASK_PER;
	regs->psw.mask |= kcb->kprobe_saved_imask;
	regs->psw.addr = ip;
पूर्ण
NOKPROBE_SYMBOL(disable_singlestep);

/*
 * Activate a kprobe by storing its poपूर्णांकer to current_kprobe. The
 * previous kprobe is stored in kcb->prev_kprobe. A stack of up to
 * two kprobes can be active, see KPROBE_REENTER.
 */
अटल व्योम push_kprobe(काष्ठा kprobe_ctlblk *kcb, काष्ठा kprobe *p)
अणु
	kcb->prev_kprobe.kp = __this_cpu_पढ़ो(current_kprobe);
	kcb->prev_kprobe.status = kcb->kprobe_status;
	__this_cpu_ग_लिखो(current_kprobe, p);
पूर्ण
NOKPROBE_SYMBOL(push_kprobe);

/*
 * Deactivate a kprobe by backing up to the previous state. If the
 * current state is KPROBE_REENTER prev_kprobe.kp will be non-शून्य,
 * क्रम any other state prev_kprobe.kp will be शून्य.
 */
अटल व्योम pop_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
पूर्ण
NOKPROBE_SYMBOL(pop_kprobe);

व्योम arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *) regs->gprs[14];
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->gprs[14] = (अचिन्हित दीर्घ) &kretprobe_trampoline;
पूर्ण
NOKPROBE_SYMBOL(arch_prepare_kretprobe);

अटल व्योम kprobe_reenter_check(काष्ठा kprobe_ctlblk *kcb, काष्ठा kprobe *p)
अणु
	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SSDONE:
	हाल KPROBE_HIT_ACTIVE:
		kprobes_inc_nmissed_count(p);
		अवरोध;
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
	शेष:
		/*
		 * A kprobe on the code path to single step an inकाष्ठाion
		 * is a BUG. The code path resides in the .kprobes.text
		 * section and is executed with पूर्णांकerrupts disabled.
		 */
		pr_err("Invalid kprobe detected.\n");
		dump_kprobe(p);
		BUG();
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(kprobe_reenter_check);

अटल पूर्णांक kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb;
	काष्ठा kprobe *p;

	/*
	 * We want to disable preemption क्रम the entire duration of kprobe
	 * processing. That includes the calls to the pre/post handlers
	 * and single stepping the kprobe inकाष्ठाion.
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();
	p = get_kprobe((व्योम *)(regs->psw.addr - 2));

	अगर (p) अणु
		अगर (kprobe_running()) अणु
			/*
			 * We have hit a kprobe जबतक another is still
			 * active. This can happen in the pre and post
			 * handler. Single step the inकाष्ठाion of the
			 * new probe but करो not call any handler function
			 * of this secondary kprobe.
			 * push_kprobe and pop_kprobe saves and restores
			 * the currently active kprobe.
			 */
			kprobe_reenter_check(kcb, p);
			push_kprobe(kcb, p);
			kcb->kprobe_status = KPROBE_REENTER;
		पूर्ण अन्यथा अणु
			/*
			 * If we have no pre-handler or it वापसed 0, we
			 * जारी with single stepping. If we have a
			 * pre-handler and it वापसed non-zero, it prepped
			 * क्रम changing execution path, so get out करोing
			 * nothing more here.
			 */
			push_kprobe(kcb, p);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;
			अगर (p->pre_handler && p->pre_handler(p, regs)) अणु
				pop_kprobe(kcb);
				preempt_enable_no_resched();
				वापस 1;
			पूर्ण
			kcb->kprobe_status = KPROBE_HIT_SS;
		पूर्ण
		enable_singlestep(kcb, regs, (अचिन्हित दीर्घ) p->ainsn.insn);
		वापस 1;
	पूर्ण /* अन्यथा:
	   * No kprobe at this address and no active kprobe. The trap has
	   * not been caused by a kprobe अवरोधpoपूर्णांक. The race of अवरोधpoपूर्णांक
	   * vs. kprobe हटाओ करोes not exist because on s390 as we use
	   * stop_machine to arm/disarm the अवरोधpoपूर्णांकs.
	   */
	preempt_enable_no_resched();
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(kprobe_handler);

/*
 * Function वापस probe trampoline:
 *	- init_kprobes() establishes a probepoपूर्णांक here
 *	- When the probed function वापसs, this probe
 *		causes the handlers to fire
 */
अटल व्योम __used kretprobe_trampoline_holder(व्योम)
अणु
	यंत्र अस्थिर(".global kretprobe_trampoline\n"
		     "kretprobe_trampoline: bcr 0,0\n");
पूर्ण

/*
 * Called when the probe at kretprobe trampoline is hit
 */
अटल पूर्णांक trampoline_probe_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	regs->psw.addr = __kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);
	/*
	 * By वापसing a non-zero value, we are telling
	 * kprobe_handler() that we करोn't want the post_handler
	 * to run (and have re-enabled preemption)
	 */
	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(trampoline_probe_handler);

/*
 * Called after single-stepping.  p->addr is the address of the
 * inकाष्ठाion whose first byte has been replaced by the "breakpoint"
 * inकाष्ठाion.  To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.  The address of this
 * copy is p->ainsn.insn.
 */
अटल व्योम resume_execution(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	अचिन्हित दीर्घ ip = regs->psw.addr;
	पूर्णांक fixup = probe_get_fixup_type(p->ainsn.insn);

	अगर (fixup & FIXUP_PSW_NORMAL)
		ip += (अचिन्हित दीर्घ) p->addr - (अचिन्हित दीर्घ) p->ainsn.insn;

	अगर (fixup & FIXUP_BRANCH_NOT_TAKEN) अणु
		पूर्णांक ilen = insn_length(p->ainsn.insn[0] >> 8);
		अगर (ip - (अचिन्हित दीर्घ) p->ainsn.insn == ilen)
			ip = (अचिन्हित दीर्घ) p->addr + ilen;
	पूर्ण

	अगर (fixup & FIXUP_RETURN_REGISTER) अणु
		पूर्णांक reg = (p->ainsn.insn[0] & 0xf0) >> 4;
		regs->gprs[reg] += (अचिन्हित दीर्घ) p->addr -
				   (अचिन्हित दीर्घ) p->ainsn.insn;
	पूर्ण

	disable_singlestep(kcb, regs, ip);
पूर्ण
NOKPROBE_SYMBOL(resume_execution);

अटल पूर्णांक post_kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	काष्ठा kprobe *p = kprobe_running();

	अगर (!p)
		वापस 0;

	अगर (kcb->kprobe_status != KPROBE_REENTER && p->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		p->post_handler(p, regs, 0);
	पूर्ण

	resume_execution(p, regs);
	pop_kprobe(kcb);
	preempt_enable_no_resched();

	/*
	 * अगर somebody अन्यथा is singlestepping across a probe poपूर्णांक, psw mask
	 * will have PER set, in which हाल, जारी the reमुख्यing processing
	 * of करो_single_step, as अगर this is not a probe hit.
	 */
	अगर (regs->psw.mask & PSW_MASK_PER)
		वापस 0;

	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(post_kprobe_handler);

अटल पूर्णांक kprobe_trap_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	काष्ठा kprobe *p = kprobe_running();
	स्थिर काष्ठा exception_table_entry *entry;

	चयन(kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the nip poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		disable_singlestep(kcb, regs, (अचिन्हित दीर्घ) p->addr);
		pop_kprobe(kcb);
		preempt_enable_no_resched();
		अवरोध;
	हाल KPROBE_HIT_ACTIVE:
	हाल KPROBE_HIT_SSDONE:
		/*
		 * We increment the nmissed count क्रम accounting,
		 * we can also use npre/npostfault count क्रम accounting
		 * these specअगरic fault हालs.
		 */
		kprobes_inc_nmissed_count(p);

		/*
		 * We come here because inकाष्ठाions in the pre/post
		 * handler caused the page_fault, this could happen
		 * अगर handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specअगरied handler try to fix it first.
		 */
		अगर (p->fault_handler && p->fault_handler(p, regs, trapnr))
			वापस 1;

		/*
		 * In हाल the user-specअगरied fault handler वापसed
		 * zero, try to fix up.
		 */
		entry = s390_search_extables(regs->psw.addr);
		अगर (entry && ex_handle(entry, regs))
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
NOKPROBE_SYMBOL(kprobe_trap_handler);

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	पूर्णांक ret;

	अगर (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_disable();
	ret = kprobe_trap_handler(regs, trapnr);
	अगर (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_restore(regs->psw.mask & ~PSW_MASK_PER);
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(kprobe_fault_handler);

/*
 * Wrapper routine to क्रम handling exceptions.
 */
पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *) data;
	काष्ठा pt_regs *regs = args->regs;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_disable();

	चयन (val) अणु
	हाल DIE_BPT:
		अगर (kprobe_handler(regs))
			ret = NOTIFY_STOP;
		अवरोध;
	हाल DIE_SSTEP:
		अगर (post_kprobe_handler(regs))
			ret = NOTIFY_STOP;
		अवरोध;
	हाल DIE_TRAP:
		अगर (!preemptible() && kprobe_running() &&
		    kprobe_trap_handler(regs, args->trapnr))
			ret = NOTIFY_STOP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_restore(regs->psw.mask & ~PSW_MASK_PER);

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(kprobe_exceptions_notअगरy);

अटल काष्ठा kprobe trampoline = अणु
	.addr = (kprobe_opcode_t *) &kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस रेजिस्टर_kprobe(&trampoline);
पूर्ण

पूर्णांक arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस p->addr == (kprobe_opcode_t *) &kretprobe_trampoline;
पूर्ण
NOKPROBE_SYMBOL(arch_trampoline_kprobe);
