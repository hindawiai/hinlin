<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kdebug.h>
#समावेश <linux/types.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/uprobes.h>

#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/ptrace.h>

#समावेश "probes-common.h"

अटल अंतरभूत पूर्णांक insn_has_delay_slot(स्थिर जोड़ mips_inकाष्ठाion insn)
अणु
	वापस __insn_has_delay_slot(insn);
पूर्ण

/**
 * arch_uprobe_analyze_insn - inकाष्ठाion analysis including validity and fixups.
 * @mm: the probed address space.
 * @arch_uprobe: the probepoपूर्णांक inक्रमmation.
 * @addr: भव address at which to install the probepoपूर्णांक
 * Return 0 on success or a -ve number on error.
 */
पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *aup,
	काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	जोड़ mips_inकाष्ठाion inst;

	/*
	 * For the समय being this also blocks attempts to use uprobes with
	 * MIPS16 and microMIPS.
	 */
	अगर (addr & 0x03)
		वापस -EINVAL;

	inst.word = aup->insn[0];

	अगर (__insn_is_compact_branch(inst)) अणु
		pr_notice("Uprobes for compact branches are not supported\n");
		वापस -EINVAL;
	पूर्ण

	aup->ixol[0] = aup->insn[insn_has_delay_slot(inst)];
	aup->ixol[1] = UPROBE_BRK_UPROBE_XOL;		/* NOP  */

	वापस 0;
पूर्ण

/**
 * is_trap_insn - check अगर the inकाष्ठाion is a trap variant
 * @insn: inकाष्ठाion to be checked.
 * Returns true अगर @insn is a trap variant.
 *
 * This definition overrides the weak definition in kernel/events/uprobes.c.
 * and is needed क्रम the हाल where an architecture has multiple trap
 * inकाष्ठाions (like PowerPC or MIPS).  We treat BREAK just like the more
 * modern conditional trap inकाष्ठाions.
 */
bool is_trap_insn(uprobe_opcode_t *insn)
अणु
	जोड़ mips_inकाष्ठाion inst;

	inst.word = *insn;

	चयन (inst.i_क्रमmat.opcode) अणु
	हाल spec_op:
		चयन (inst.r_क्रमmat.func) अणु
		हाल अवरोध_op:
		हाल teq_op:
		हाल tge_op:
		हाल tgeu_op:
		हाल tlt_op:
		हाल tltu_op:
		हाल tne_op:
			वापस 1;
		पूर्ण
		अवरोध;

	हाल bcond_op:	/* Yes, really ...  */
		चयन (inst.u_क्रमmat.rt) अणु
		हाल teqi_op:
		हाल tgei_op:
		हाल tgeiu_op:
		हाल tlti_op:
		हाल tltiu_op:
		हाल tnei_op:
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा UPROBE_TRAP_NR	अच_दीर्घ_उच्च

/*
 * arch_uprobe_pre_xol - prepare to execute out of line.
 * @auprobe: the probepoपूर्णांक inक्रमmation.
 * @regs: reflects the saved user state of current task.
 */
पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	/*
	 * Now find the EPC where to resume after the अवरोधpoपूर्णांक has been
	 * dealt with.  This may require emulation of a branch.
	 */
	aup->resume_epc = regs->cp0_epc + 4;
	अगर (insn_has_delay_slot((जोड़ mips_inकाष्ठाion) aup->insn[0])) अणु
		__compute_वापस_epc_क्रम_insn(regs,
			(जोड़ mips_inकाष्ठाion) aup->insn[0]);
		aup->resume_epc = regs->cp0_epc;
	पूर्ण
	utask->autask.saved_trap_nr = current->thपढ़ो.trap_nr;
	current->thपढ़ो.trap_nr = UPROBE_TRAP_NR;
	regs->cp0_epc = current->utask->xol_vaddr;

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	current->thपढ़ो.trap_nr = utask->autask.saved_trap_nr;
	regs->cp0_epc = aup->resume_epc;

	वापस 0;
पूर्ण

/*
 * If xol insn itself traps and generates a संकेत(Say,
 * संक_अवैध/संक_अंश/etc), then detect the हाल where a singlestepped
 * inकाष्ठाion jumps back to its own address. It is assumed that anything
 * like करो_page_fault/करो_trap/etc sets thपढ़ो.trap_nr != -1.
 *
 * arch_uprobe_pre_xol/arch_uprobe_post_xol save/restore thपढ़ो.trap_nr,
 * arch_uprobe_xol_was_trapped() simply checks that ->trap_nr is not equal to
 * UPROBE_TRAP_NR == -1 set by arch_uprobe_pre_xol().
 */
bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.trap_nr != UPROBE_TRAP_NR)
		वापस true;

	वापस false;
पूर्ण

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
	हाल DIE_UPROBE:
		अगर (uprobe_pre_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
		अवरोध;
	हाल DIE_UPROBE_XOL:
		अगर (uprobe_post_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function माला_लो called when XOL inकाष्ठाion either माला_लो trapped or
 * the thपढ़ो has a fatal संकेत. Reset the inकाष्ठाion poपूर्णांकer to its
 * probed address क्रम the potential restart or क्रम post mortem analysis.
 */
व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *aup,
	काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr);
पूर्ण

अचिन्हित दीर्घ arch_uretprobe_hijack_वापस_addr(
	अचिन्हित दीर्घ trampoline_vaddr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ra;

	ra = regs->regs[31];

	/* Replace the वापस address with the trampoline address */
	regs->regs[31] = trampoline_vaddr;

	वापस ra;
पूर्ण

/**
 * set_swbp - store अवरोधpoपूर्णांक at a given address.
 * @auprobe: arch specअगरic probepoपूर्णांक inक्रमmation.
 * @mm: the probed process address space.
 * @vaddr: the भव address to insert the opcode.
 *
 * For mm @mm, store the अवरोधpoपूर्णांक inकाष्ठाion at @vaddr.
 * Return 0 (success) or a negative त्रुटि_सं.
 *
 * This version overrides the weak version in kernel/events/uprobes.c.
 * It is required to handle MIPS16 and microMIPS.
 */
पूर्णांक __weak set_swbp(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ vaddr)
अणु
	वापस uprobe_ग_लिखो_opcode(auprobe, mm, vaddr, UPROBE_SWBP_INSN);
पूर्ण

व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
				  व्योम *src, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ kaddr, kstart;

	/* Initialize the slot */
	kaddr = (अचिन्हित दीर्घ)kmap_atomic(page);
	kstart = kaddr + (vaddr & ~PAGE_MASK);
	स_नकल((व्योम *)kstart, src, len);
	flush_icache_range(kstart, kstart + len);
	kunmap_atomic((व्योम *)kaddr);
पूर्ण

/**
 * uprobe_get_swbp_addr - compute address of swbp given post-swbp regs
 * @regs: Reflects the saved state of the task after it has hit a अवरोधpoपूर्णांक
 * inकाष्ठाion.
 * Return the address of the अवरोधpoपूर्णांक inकाष्ठाion.
 *
 * This overrides the weak version in kernel/events/uprobes.c.
 */
अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

/*
 * See अगर the inकाष्ठाion can be emulated.
 * Returns true अगर inकाष्ठाion was emulated, false otherwise.
 *
 * For now we always emulate so this function just वापसs 0.
 */
bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
