<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/probes/kprobes.c
 *
 * Kprobes support क्रम ARM64
 *
 * Copyright (C) 2013 Linaro Limited.
 * Author: Sandeepa Prabhu <sandeepa.prabhu@linaro.org>
 */
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/extable.h>
#समावेश <linux/slab.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/insn.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>

#समावेश "decode-insn.h"

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

अटल व्योम __kprobes
post_kprobe_handler(काष्ठा kprobe *, काष्ठा kprobe_ctlblk *, काष्ठा pt_regs *);

अटल व्योम __kprobes arch_prepare_ss_slot(काष्ठा kprobe *p)
अणु
	kprobe_opcode_t *addr = p->ainsn.api.insn;
	व्योम *addrs[] = अणुaddr, addr + 1पूर्ण;
	u32 insns[] = अणुp->opcode, BRK64_OPCODE_KPROBES_SSपूर्ण;

	/* prepare insn slot */
	aarch64_insn_patch_text(addrs, insns, 2);

	flush_icache_range((uपूर्णांकptr_t)addr, (uपूर्णांकptr_t)(addr + MAX_INSN_SIZE));

	/*
	 * Needs restoring of वापस address after stepping xol.
	 */
	p->ainsn.api.restore = (अचिन्हित दीर्घ) p->addr +
	  माप(kprobe_opcode_t);
पूर्ण

अटल व्योम __kprobes arch_prepare_simulate(काष्ठा kprobe *p)
अणु
	/* This inकाष्ठाions is not executed xol. No need to adjust the PC */
	p->ainsn.api.restore = 0;
पूर्ण

अटल व्योम __kprobes arch_simulate_insn(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (p->ainsn.api.handler)
		p->ainsn.api.handler((u32)p->opcode, (दीर्घ)p->addr, regs);

	/* single step simulated, now go क्रम post processing */
	post_kprobe_handler(p, kcb, regs);
पूर्ण

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ probe_addr = (अचिन्हित दीर्घ)p->addr;

	अगर (probe_addr & 0x3)
		वापस -EINVAL;

	/* copy inकाष्ठाion */
	p->opcode = le32_to_cpu(*p->addr);

	अगर (search_exception_tables(probe_addr))
		वापस -EINVAL;

	/* decode inकाष्ठाion */
	चयन (arm_kprobe_decode_insn(p->addr, &p->ainsn)) अणु
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

व्योम *alloc_insn_page(व्योम)
अणु
	वापस __vदो_स्मृति_node_range(PAGE_SIZE, 1, VMALLOC_START, VMALLOC_END,
			GFP_KERNEL, PAGE_KERNEL_ROX, VM_FLUSH_RESET_PERMS,
			NUMA_NO_NODE, __builtin_वापस_address(0));
पूर्ण

/* arm kprobe: install अवरोधpoपूर्णांक in text */
व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	व्योम *addr = p->addr;
	u32 insn = BRK64_OPCODE_KPROBES;

	aarch64_insn_patch_text(&addr, &insn, 1);
पूर्ण

/* disarm kprobe: हटाओ अवरोधpoपूर्णांक from text */
व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	व्योम *addr = p->addr;

	aarch64_insn_patch_text(&addr, &p->opcode, 1);
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.api.insn) अणु
		मुक्त_insn_slot(p->ainsn.api.insn, 0);
		p->ainsn.api.insn = शून्य;
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

/*
 * Mask all of DAIF जबतक executing the inकाष्ठाion out-of-line, to keep things
 * simple and aव्योम nesting exceptions. Interrupts करो have to be disabled since
 * the kprobe state is per-CPU and करोesn't get migrated.
 */
अटल व्योम __kprobes kprobes_save_local_irqflag(काष्ठा kprobe_ctlblk *kcb,
						काष्ठा pt_regs *regs)
अणु
	kcb->saved_irqflag = regs->pstate & DAIF_MASK;
	regs->pstate |= DAIF_MASK;
पूर्ण

अटल व्योम __kprobes kprobes_restore_local_irqflag(काष्ठा kprobe_ctlblk *kcb,
						काष्ठा pt_regs *regs)
अणु
	regs->pstate &= ~DAIF_MASK;
	regs->pstate |= kcb->saved_irqflag;
पूर्ण

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

		kprobes_save_local_irqflag(kcb, regs);
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
post_kprobe_handler(काष्ठा kprobe *cur, काष्ठा kprobe_ctlblk *kcb, काष्ठा pt_regs *regs)
अणु
	/* वापस addr restore अगर non-branching insn */
	अगर (cur->ainsn.api.restore != 0)
		inकाष्ठाion_poपूर्णांकer_set(regs, cur->ainsn.api.restore);

	/* restore back original saved kprobe variables and जारी */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		वापस;
	पूर्ण
	/* call post handler */
	kcb->kprobe_status = KPROBE_HIT_SSDONE;
	अगर (cur->post_handler)
		cur->post_handler(cur, regs, 0);

	reset_current_kprobe();
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
		 * kprobe and the ip poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		inकाष्ठाion_poपूर्णांकer_set(regs, (अचिन्हित दीर्घ) cur->addr);
		BUG_ON(!inकाष्ठाion_poपूर्णांकer(regs));

		अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
			restore_previous_kprobe(kcb);
		पूर्ण अन्यथा अणु
			kprobes_restore_local_irqflag(kcb, regs);
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
		 * user-specअगरied handler try to fix it first.
		 */
		अगर (cur->fault_handler && cur->fault_handler(cur, regs, fsr))
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

अटल व्योम __kprobes kprobe_handler(काष्ठा pt_regs *regs)
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
				वापस;
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
			 */
			अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
				setup_singlestep(p, regs, kcb, 0);
			पूर्ण अन्यथा
				reset_current_kprobe();
		पूर्ण
	पूर्ण
	/*
	 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
	 * after we hit it.  Another cpu has हटाओd
	 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
	 * at this address.  In either हाल, no further
	 * handling of this पूर्णांकerrupt is appropriate.
	 * Return back to original inकाष्ठाion, and जारी.
	 */
पूर्ण

अटल पूर्णांक __kprobes
kprobe_अवरोधpoपूर्णांक_ss_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	अचिन्हित दीर्घ addr = inकाष्ठाion_poपूर्णांकer(regs);
	काष्ठा kprobe *cur = kprobe_running();

	अगर (cur && (kcb->kprobe_status & (KPROBE_HIT_SS | KPROBE_REENTER)) &&
	    ((अचिन्हित दीर्घ)&cur->ainsn.api.insn[1] == addr)) अणु
		kprobes_restore_local_irqflag(kcb, regs);
		post_kprobe_handler(cur, kcb, regs);

		वापस DBG_HOOK_HANDLED;
	पूर्ण

	/* not ours, kprobes should ignore it */
	वापस DBG_HOOK_ERROR;
पूर्ण

अटल काष्ठा अवरोध_hook kprobes_अवरोध_ss_hook = अणु
	.imm = KPROBES_BRK_SS_IMM,
	.fn = kprobe_अवरोधpoपूर्णांक_ss_handler,
पूर्ण;

अटल पूर्णांक __kprobes
kprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	kprobe_handler(regs);
	वापस DBG_HOOK_HANDLED;
पूर्ण

अटल काष्ठा अवरोध_hook kprobes_अवरोध_hook = अणु
	.imm = KPROBES_BRK_IMM,
	.fn = kprobe_अवरोधpoपूर्णांक_handler,
पूर्ण;

/*
 * Provide a blacklist of symbols identअगरying ranges which cannot be kprobed.
 * This blacklist is exposed to userspace via debugfs (kprobes/blacklist).
 */
पूर्णांक __init arch_populate_kprobe_blacklist(व्योम)
अणु
	पूर्णांक ret;

	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__entry_text_start,
					(अचिन्हित दीर्घ)__entry_text_end);
	अगर (ret)
		वापस ret;
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__irqentry_text_start,
					(अचिन्हित दीर्घ)__irqentry_text_end);
	अगर (ret)
		वापस ret;
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__idmap_text_start,
					(अचिन्हित दीर्घ)__idmap_text_end);
	अगर (ret)
		वापस ret;
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__hyp_text_start,
					(अचिन्हित दीर्घ)__hyp_text_end);
	अगर (ret || is_kernel_in_hyp_mode())
		वापस ret;
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__hyp_idmap_text_start,
					(अचिन्हित दीर्घ)__hyp_idmap_text_end);
	वापस ret;
पूर्ण

व्योम __kprobes __used *trampoline_probe_handler(काष्ठा pt_regs *regs)
अणु
	वापस (व्योम *)kretprobe_trampoline_handler(regs, &kretprobe_trampoline,
					(व्योम *)kernel_stack_poपूर्णांकer(regs));
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->regs[30];
	ri->fp = (व्योम *)kernel_stack_poपूर्णांकer(regs);

	/* replace वापस addr (x30) with trampoline */
	regs->regs[30] = (दीर्घ)&kretprobe_trampoline;
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस 0;
पूर्ण

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	रेजिस्टर_kernel_अवरोध_hook(&kprobes_अवरोध_hook);
	रेजिस्टर_kernel_अवरोध_hook(&kprobes_अवरोध_ss_hook);

	वापस 0;
पूर्ण
