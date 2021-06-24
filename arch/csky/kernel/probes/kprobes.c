<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kprobes.h>
#समावेश <linux/extable.h>
#समावेश <linux/slab.h>
#समावेश <linux/stop_machine.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "decode-insn.h"

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

अटल व्योम __kprobes
post_kprobe_handler(काष्ठा kprobe_ctlblk *, काष्ठा pt_regs *);

काष्ठा csky_insn_patch अणु
	kprobe_opcode_t	*addr;
	u32		opcode;
	atomic_t	cpu_count;
पूर्ण;

अटल पूर्णांक __kprobes patch_text_cb(व्योम *priv)
अणु
	काष्ठा csky_insn_patch *param = priv;
	अचिन्हित पूर्णांक addr = (अचिन्हित पूर्णांक)param->addr;

	अगर (atomic_inc_वापस(&param->cpu_count) == 1) अणु
		*(u16 *) addr = cpu_to_le16(param->opcode);
		dcache_wb_range(addr, addr + 2);
		atomic_inc(&param->cpu_count);
	पूर्ण अन्यथा अणु
		जबतक (atomic_पढ़ो(&param->cpu_count) <= num_online_cpus())
			cpu_relax();
	पूर्ण

	icache_inv_range(addr, addr + 2);

	वापस 0;
पूर्ण

अटल पूर्णांक __kprobes patch_text(kprobe_opcode_t *addr, u32 opcode)
अणु
	काष्ठा csky_insn_patch param = अणु addr, opcode, ATOMIC_INIT(0) पूर्ण;

	वापस stop_machine_cpuslocked(patch_text_cb, &param, cpu_online_mask);
पूर्ण

अटल व्योम __kprobes arch_prepare_ss_slot(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ offset = is_insn32(p->opcode) ? 4 : 2;

	p->ainsn.api.restore = (अचिन्हित दीर्घ)p->addr + offset;

	patch_text(p->ainsn.api.insn, p->opcode);
पूर्ण

अटल व्योम __kprobes arch_prepare_simulate(काष्ठा kprobe *p)
अणु
	p->ainsn.api.restore = 0;
पूर्ण

अटल व्योम __kprobes arch_simulate_insn(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (p->ainsn.api.handler)
		p->ainsn.api.handler((u32)p->opcode, (दीर्घ)p->addr, regs);

	post_kprobe_handler(kcb, regs);
पूर्ण

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ probe_addr = (अचिन्हित दीर्घ)p->addr;

	अगर (probe_addr & 0x1) अणु
		pr_warn("Address not aligned.\n");
		वापस -EINVAL;
	पूर्ण

	/* copy inकाष्ठाion */
	p->opcode = le32_to_cpu(*p->addr);

	/* decode inकाष्ठाion */
	चयन (csky_probe_decode_insn(p->addr, &p->ainsn.api)) अणु
	हाल INSN_REJECTED:	/* insn not supported */
		वापस -EINVAL;

	हाल INSN_GOOD_NO_SLOT:	/* insn need simulation */
		p->ainsn.api.insn = शून्य;
		अवरोध;

	हाल INSN_GOOD:	/* inकाष्ठाion uses slot */
		p->ainsn.api.insn = get_insn_slot();
		अगर (!p->ainsn.api.insn)
			वापस -ENOMEM;
		अवरोध;
	पूर्ण

	/* prepare the inकाष्ठाion */
	अगर (p->ainsn.api.insn)
		arch_prepare_ss_slot(p);
	अन्यथा
		arch_prepare_simulate(p);

	वापस 0;
पूर्ण

/* install अवरोधpoपूर्णांक in text */
व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	patch_text(p->addr, USR_BKPT);
पूर्ण

/* हटाओ अवरोधpoपूर्णांक from text */
व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	patch_text(p->addr, p->opcode);
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
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

/*
 * Interrupts need to be disabled beक्रमe single-step mode is set, and not
 * reenabled until after single-step mode ends.
 * Without disabling पूर्णांकerrupt on local CPU, there is a chance of
 * पूर्णांकerrupt occurrence in the period of exception वापस and  start of
 * out-of-line single-step, that result in wrongly single stepping
 * पूर्णांकo the पूर्णांकerrupt handler.
 */
अटल व्योम __kprobes kprobes_save_local_irqflag(काष्ठा kprobe_ctlblk *kcb,
						काष्ठा pt_regs *regs)
अणु
	kcb->saved_sr = regs->sr;
	regs->sr &= ~BIT(6);
पूर्ण

अटल व्योम __kprobes kprobes_restore_local_irqflag(काष्ठा kprobe_ctlblk *kcb,
						काष्ठा pt_regs *regs)
अणु
	regs->sr = kcb->saved_sr;
पूर्ण

अटल व्योम __kprobes
set_ss_context(काष्ठा kprobe_ctlblk *kcb, अचिन्हित दीर्घ addr, काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ offset = is_insn32(p->opcode) ? 4 : 2;

	kcb->ss_ctx.ss_pending = true;
	kcb->ss_ctx.match_addr = addr + offset;
पूर्ण

अटल व्योम __kprobes clear_ss_context(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->ss_ctx.ss_pending = false;
	kcb->ss_ctx.match_addr = 0;
पूर्ण

#घोषणा TRACE_MODE_SI		BIT(14)
#घोषणा TRACE_MODE_MASK		~(0x3 << 14)
#घोषणा TRACE_MODE_RUN		0

अटल व्योम __kprobes setup_singlestep(काष्ठा kprobe *p,
				       काष्ठा pt_regs *regs,
				       काष्ठा kprobe_ctlblk *kcb, पूर्णांक reenter)
अणु
	अचिन्हित दीर्घ slot;

	अगर (reenter) अणु
		save_previous_kprobe(kcb);
		set_current_kprobe(p);
		kcb->kprobe_status = KPROBE_REENTER;
	पूर्ण अन्यथा अणु
		kcb->kprobe_status = KPROBE_HIT_SS;
	पूर्ण

	अगर (p->ainsn.api.insn) अणु
		/* prepare क्रम single stepping */
		slot = (अचिन्हित दीर्घ)p->ainsn.api.insn;

		set_ss_context(kcb, slot, p);	/* mark pending ss */

		/* IRQs and single stepping करो not mix well. */
		kprobes_save_local_irqflag(kcb, regs);
		regs->sr = (regs->sr & TRACE_MODE_MASK) | TRACE_MODE_SI;
		inकाष्ठाion_poपूर्णांकer_set(regs, slot);
	पूर्ण अन्यथा अणु
		/* insn simulation */
		arch_simulate_insn(p, regs);
	पूर्ण
पूर्ण

अटल पूर्णांक __kprobes reenter_kprobe(काष्ठा kprobe *p,
				    काष्ठा pt_regs *regs,
				    काष्ठा kprobe_ctlblk *kcb)
अणु
	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SSDONE:
	हाल KPROBE_HIT_ACTIVE:
		kprobes_inc_nmissed_count(p);
		setup_singlestep(p, regs, kcb, 1);
		अवरोध;
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		pr_warn("Unrecoverable kprobe detected.\n");
		dump_kprobe(p);
		BUG();
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम __kprobes
post_kprobe_handler(काष्ठा kprobe_ctlblk *kcb, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *cur = kprobe_running();

	अगर (!cur)
		वापस;

	/* वापस addr restore अगर non-branching insn */
	अगर (cur->ainsn.api.restore != 0)
		regs->pc = cur->ainsn.api.restore;

	/* restore back original saved kprobe variables and जारी */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		वापस;
	पूर्ण

	/* call post handler */
	kcb->kprobe_status = KPROBE_HIT_SSDONE;
	अगर (cur->post_handler)	अणु
		/* post_handler can hit अवरोधpoपूर्णांक and single step
		 * again, so we enable D-flag क्रम recursive exception.
		 */
		cur->post_handler(cur, regs, 0);
	पूर्ण

	reset_current_kprobe();
पूर्ण

पूर्णांक __kprobes kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the ip poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->pc = (अचिन्हित दीर्घ) cur->addr;
		अगर (!inकाष्ठाion_poपूर्णांकer(regs))
			BUG();

		अगर (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		अन्यथा
			reset_current_kprobe();

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
		अगर (fixup_exception(regs))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __kprobes
kprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p, *cur_kprobe;
	काष्ठा kprobe_ctlblk *kcb;
	अचिन्हित दीर्घ addr = inकाष्ठाion_poपूर्णांकer(regs);

	kcb = get_kprobe_ctlblk();
	cur_kprobe = kprobe_running();

	p = get_kprobe((kprobe_opcode_t *) addr);

	अगर (p) अणु
		अगर (cur_kprobe) अणु
			अगर (reenter_kprobe(p, regs, kcb))
				वापस 1;
		पूर्ण अन्यथा अणु
			/* Probe hit */
			set_current_kprobe(p);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;

			/*
			 * If we have no pre-handler or it वापसed 0, we
			 * जारी with normal processing.  If we have a
			 * pre-handler and it वापसed non-zero, it will
			 * modअगरy the execution path and no need to single
			 * stepping. Let's just reset current kprobe and निकास.
			 *
			 * pre_handler can hit a अवरोधpoपूर्णांक and can step thru
			 * beक्रमe वापस.
			 */
			अगर (!p->pre_handler || !p->pre_handler(p, regs))
				setup_singlestep(p, regs, kcb, 0);
			अन्यथा
				reset_current_kprobe();
		पूर्ण
		वापस 1;
	पूर्ण

	/*
	 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
	 * after we hit it.  Another cpu has हटाओd
	 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
	 * at this address.  In either हाल, no further
	 * handling of this पूर्णांकerrupt is appropriate.
	 * Return back to original inकाष्ठाion, and जारी.
	 */
	वापस 0;
पूर्ण

पूर्णांक __kprobes
kprobe_single_step_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर ((kcb->ss_ctx.ss_pending)
	    && (kcb->ss_ctx.match_addr == inकाष्ठाion_poपूर्णांकer(regs))) अणु
		clear_ss_context(kcb);	/* clear pending ss */

		kprobes_restore_local_irqflag(kcb, regs);
		regs->sr = (regs->sr & TRACE_MODE_MASK) | TRACE_MODE_RUN;

		post_kprobe_handler(kcb, regs);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Provide a blacklist of symbols identअगरying ranges which cannot be kprobed.
 * This blacklist is exposed to userspace via debugfs (kprobes/blacklist).
 */
पूर्णांक __init arch_populate_kprobe_blacklist(व्योम)
अणु
	पूर्णांक ret;

	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__irqentry_text_start,
					(अचिन्हित दीर्घ)__irqentry_text_end);
	वापस ret;
पूर्ण

व्योम __kprobes __used *trampoline_probe_handler(काष्ठा pt_regs *regs)
अणु
	वापस (व्योम *)kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->lr;
	ri->fp = शून्य;
	regs->lr = (अचिन्हित दीर्घ) &kretprobe_trampoline;
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस 0;
पूर्ण

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस 0;
पूर्ण
