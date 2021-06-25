<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * User-space Probes (UProbes) क्रम घातerpc
 *
 * Copyright IBM Corporation, 2007-2012
 *
 * Adapted from the x86 port by Ananth N Mavinakayanahalli <ananth@in.ibm.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>

#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/inst.h>

#घोषणा UPROBE_TRAP_NR	अच_पूर्णांक_उच्च

/**
 * is_trap_insn - check अगर the inकाष्ठाion is a trap variant
 * @insn: inकाष्ठाion to be checked.
 * Returns true अगर @insn is a trap variant.
 */
bool is_trap_insn(uprobe_opcode_t *insn)
अणु
	वापस (is_trap(*insn));
पूर्ण

/**
 * arch_uprobe_analyze_insn
 * @mm: the probed address space.
 * @arch_uprobe: the probepoपूर्णांक inक्रमmation.
 * @addr: vaddr to probe.
 * Return 0 on success or a -ve number on error.
 */
पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe,
		काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अगर (addr & 0x03)
		वापस -EINVAL;

	अगर (cpu_has_feature(CPU_FTR_ARCH_31) &&
	    ppc_inst_prefixed(auprobe->insn) &&
	    (addr & 0x3f) == 60) अणु
		pr_info_ratelimited("Cannot register a uprobe on 64 byte unaligned prefixed instruction\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * arch_uprobe_pre_xol - prepare to execute out of line.
 * @auprobe: the probepoपूर्णांक inक्रमmation.
 * @regs: reflects the saved user state of current task.
 */
पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा arch_uprobe_task *autask = &current->utask->autask;

	autask->saved_trap_nr = current->thपढ़ो.trap_nr;
	current->thपढ़ो.trap_nr = UPROBE_TRAP_NR;
	regs->nip = current->utask->xol_vaddr;

	user_enable_single_step(current);
	वापस 0;
पूर्ण

/**
 * uprobe_get_swbp_addr - compute address of swbp given post-swbp regs
 * @regs: Reflects the saved state of the task after it has hit a अवरोधpoपूर्णांक
 * inकाष्ठाion.
 * Return the address of the अवरोधpoपूर्णांक inकाष्ठाion.
 */
अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

/*
 * If xol insn itself traps and generates a संकेत (संक_अवैध/संक_अंश/etc),
 * then detect the हाल where a singlestepped inकाष्ठाion jumps back to its
 * own address. It is assumed that anything like करो_page_fault/करो_trap/etc
 * sets thपढ़ो.trap_nr != अच_पूर्णांक_उच्च.
 *
 * arch_uprobe_pre_xol/arch_uprobe_post_xol save/restore thपढ़ो.trap_nr,
 * arch_uprobe_xol_was_trapped() simply checks that ->trap_nr is not equal to
 * UPROBE_TRAP_NR == अच_पूर्णांक_उच्च set by arch_uprobe_pre_xol().
 */
bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->thपढ़ो.trap_nr != UPROBE_TRAP_NR)
		वापस true;

	वापस false;
पूर्ण

/*
 * Called after single-stepping. To aव्योम the SMP problems that can
 * occur when we temporarily put back the original opcode to
 * single-step, we single-stepped a copy of the inकाष्ठाion.
 *
 * This function prepares to resume execution after the single-step.
 */
पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON_ONCE(current->thपढ़ो.trap_nr != UPROBE_TRAP_NR);

	current->thपढ़ो.trap_nr = utask->autask.saved_trap_nr;

	/*
	 * On घातerpc, except क्रम loads and stores, most inकाष्ठाions
	 * including ones that alter code flow (branches, calls, वापसs)
	 * are emulated in the kernel. We get here only अगर the emulation
	 * support करोesn't exist and have to fix-up the next inकाष्ठाion
	 * to be executed.
	 */
	regs->nip = (अचिन्हित दीर्घ)ppc_inst_next((व्योम *)utask->vaddr, &auprobe->insn);

	user_disable_single_step(current);
	वापस 0;
पूर्ण

/* callback routine क्रम handling exceptions. */
पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;
	काष्ठा pt_regs *regs = args->regs;

	/* regs == शून्य is a kernel bug */
	अगर (WARN_ON(!regs))
		वापस NOTIFY_DONE;

	/* We are only पूर्णांकerested in userspace traps */
	अगर (!user_mode(regs))
		वापस NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_BPT:
		अगर (uprobe_pre_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
		अवरोध;
	हाल DIE_SSTEP:
		अगर (uprobe_post_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/*
 * This function माला_लो called when XOL inकाष्ठाion either माला_लो trapped or
 * the thपढ़ो has a fatal संकेत, so reset the inकाष्ठाion poपूर्णांकer to its
 * probed address.
 */
व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	current->thपढ़ो.trap_nr = utask->autask.saved_trap_nr;
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr);

	user_disable_single_step(current);
पूर्ण

/*
 * See अगर the inकाष्ठाion can be emulated.
 * Returns true अगर inकाष्ठाion was emulated, false otherwise.
 */
bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	/*
	 * emulate_step() वापसs 1 अगर the insn was successfully emulated.
	 * For all other हालs, we need to single-step in hardware.
	 */
	ret = emulate_step(regs, ppc_inst_पढ़ो(&auprobe->insn));
	अगर (ret > 0)
		वापस true;

	वापस false;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_vaddr;

	orig_ret_vaddr = regs->link;

	/* Replace the वापस addr with trampoline addr */
	regs->link = trampoline_vaddr;

	वापस orig_ret_vaddr;
पूर्ण

bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
				काष्ठा pt_regs *regs)
अणु
	अगर (ctx == RP_CHECK_CHAIN_CALL)
		वापस regs->gpr[1] <= ret->stack;
	अन्यथा
		वापस regs->gpr[1] < ret->stack;
पूर्ण
