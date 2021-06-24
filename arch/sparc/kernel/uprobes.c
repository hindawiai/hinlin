<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * User-space Probes (UProbes) क्रम sparc
 *
 * Copyright (C) 2013 Oracle Inc.
 *
 * Authors:
 *	Jose E. Marchesi <jose.marchesi@oracle.com>
 *	Eric Saपूर्णांक Etienne <eric.saपूर्णांक.etienne@oracle.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/uprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h> /* For काष्ठा task_काष्ठा */
#समावेश <linux/kdebug.h>

#समावेश <यंत्र/cacheflush.h>

/* Compute the address of the अवरोधpoपूर्णांक inकाष्ठाion and वापस it.
 *
 * Note that uprobe_get_swbp_addr is defined as a weak symbol in
 * kernel/events/uprobe.c.
 */
अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अटल व्योम copy_to_page(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
			 स्थिर व्योम *src, पूर्णांक len)
अणु
	व्योम *kaddr = kmap_atomic(page);

	स_नकल(kaddr + (vaddr & ~PAGE_MASK), src, len);
	kunmap_atomic(kaddr);
पूर्ण

/* Fill in the xol area with the probed inकाष्ठाion followed by the
 * single-step trap.  Some fixups in the copied inकाष्ठाion are
 * perक्रमmed at this poपूर्णांक.
 *
 * Note that uprobe_xol_copy is defined as a weak symbol in
 * kernel/events/uprobe.c.
 */
व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
			   व्योम *src, अचिन्हित दीर्घ len)
अणु
	स्थिर u32 stp_insn = UPROBE_STP_INSN;
	u32 insn = *(u32 *) src;

	/* Branches annulling their delay slot must be fixed to not करो
	 * so.  Clearing the annul bit on these inकाष्ठाions we can be
	 * sure the single-step अवरोधpoपूर्णांक in the XOL slot will be
	 * executed.
	 */

	u32 op = (insn >> 30) & 0x3;
	u32 op2 = (insn >> 22) & 0x7;

	अगर (op == 0 &&
	    (op2 == 1 || op2 == 2 || op2 == 3 || op2 == 5 || op2 == 6) &&
	    (insn & ANNUL_BIT) == ANNUL_BIT)
		insn &= ~ANNUL_BIT;

	copy_to_page(page, vaddr, &insn, len);
	copy_to_page(page, vaddr+len, &stp_insn, 4);
पूर्ण


/* Inकाष्ठाion analysis/validity.
 *
 * This function वापसs 0 on success or a -ve number on error.
 */
पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe,
			     काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	/* Any unsupported inकाष्ठाion?  Then वापस -EINVAL  */
	वापस 0;
पूर्ण

/* If INSN is a relative control transfer inकाष्ठाion, वापस the
 * corrected branch destination value.
 *
 * Note that regs->tpc and regs->tnpc still hold the values of the
 * program counters at the समय of the single-step trap due to the
 * execution of the UPROBE_STP_INSN at utask->xol_vaddr + 4.
 *
 */
अटल अचिन्हित दीर्घ relbranch_fixup(u32 insn, काष्ठा uprobe_task *utask,
				     काष्ठा pt_regs *regs)
अणु
	/* Branch not taken, no mods necessary.  */
	अगर (regs->tnpc == regs->tpc + 0x4UL)
		वापस utask->autask.saved_tnpc + 0x4UL;

	/* The three हालs are call, branch w/prediction,
	 * and traditional branch.
	 */
	अगर ((insn & 0xc0000000) == 0x40000000 ||
	    (insn & 0xc1c00000) == 0x00400000 ||
	    (insn & 0xc1c00000) == 0x00800000) अणु
		अचिन्हित दीर्घ real_pc = (अचिन्हित दीर्घ) utask->vaddr;
		अचिन्हित दीर्घ ixol_addr = utask->xol_vaddr;

		/* The inकाष्ठाion did all the work क्रम us
		 * alपढ़ोy, just apply the offset to the correct
		 * inकाष्ठाion location.
		 */
		वापस (real_pc + (regs->tnpc - ixol_addr));
	पूर्ण

	/* It is jmpl or some other असलolute PC modअगरication inकाष्ठाion,
	 * leave NPC as-is.
	 */
	वापस regs->tnpc;
पूर्ण

/* If INSN is an inकाष्ठाion which ग_लिखोs its PC location
 * पूर्णांकo a destination रेजिस्टर, fix that up.
 */
अटल पूर्णांक retpc_fixup(काष्ठा pt_regs *regs, u32 insn,
		       अचिन्हित दीर्घ real_pc)
अणु
	अचिन्हित दीर्घ *slot = शून्य;
	पूर्णांक rc = 0;

	/* Simplest हाल is 'call', which always uses %o7 */
	अगर ((insn & 0xc0000000) == 0x40000000)
		slot = &regs->u_regs[UREG_I7];

	/* 'jmpl' encodes the रेजिस्टर inside of the opcode */
	अगर ((insn & 0xc1f80000) == 0x81c00000) अणु
		अचिन्हित दीर्घ rd = ((insn >> 25) & 0x1f);

		अगर (rd <= 15) अणु
			slot = &regs->u_regs[rd];
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ fp = regs->u_regs[UREG_FP];
			/* Hard हाल, it goes onto the stack. */
			flushw_all();

			rd -= 16;
			अगर (test_thपढ़ो_64bit_stack(fp)) अणु
				अचिन्हित दीर्घ __user *uslot =
			(अचिन्हित दीर्घ __user *) (fp + STACK_BIAS) + rd;
				rc = __put_user(real_pc, uslot);
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक __user *uslot = (अचिन्हित पूर्णांक
						__user *) fp + rd;
				rc = __put_user((u32) real_pc, uslot);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (slot != शून्य)
		*slot = real_pc;
	वापस rc;
पूर्ण

/* Single-stepping can be aव्योमed क्रम certain inकाष्ठाions: NOPs and
 * inकाष्ठाions that can be emulated.  This function determines
 * whether the inकाष्ठाion where the uprobe is installed falls in one
 * of these हालs and emulates it.
 *
 * This function वापसs true अगर the single-stepping can be skipped,
 * false otherwise.
 */
bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	/* We currently only emulate NOP inकाष्ठाions.
	 */

	अगर (auprobe->ixol == (1 << 24)) अणु
		regs->tnpc += 4;
		regs->tpc += 4;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Prepare to execute out of line.  At this poपूर्णांक
 * current->utask->xol_vaddr poपूर्णांकs to an allocated XOL slot properly
 * initialized with the original inकाष्ठाion and the single-stepping
 * trap inकाष्ठाion.
 *
 * This function वापसs 0 on success, any other number on error.
 */
पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;
	काष्ठा arch_uprobe_task *autask = &current->utask->autask;

	/* Save the current program counters so they can be restored
	 * later.
	 */
	autask->saved_tpc = regs->tpc;
	autask->saved_tnpc = regs->tnpc;

	/* Adjust PC and NPC so the first inकाष्ठाion in the XOL slot
	 * will be executed by the user task.
	 */
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->xol_vaddr);

	वापस 0;
पूर्ण

/* Prepare to resume execution after the single-step.  Called after
 * single-stepping. To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.
 *
 * This function वापसs 0 on success, any other number on error.
 */
पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;
	काष्ठा arch_uprobe_task *autask = &utask->autask;
	u32 insn = auprobe->ixol;
	पूर्णांक rc = 0;

	अगर (utask->state == UTASK_SSTEP_ACK) अणु
		regs->tnpc = relbranch_fixup(insn, utask, regs);
		regs->tpc = autask->saved_tnpc;
		rc =  retpc_fixup(regs, insn, (अचिन्हित दीर्घ) utask->vaddr);
	पूर्ण अन्यथा अणु
		regs->tnpc = utask->vaddr+4;
		regs->tpc = autask->saved_tnpc+4;
	पूर्ण
	वापस rc;
पूर्ण

/* Handler क्रम uprobe traps.  This is called from the traps table and
 * triggers the proper die notअगरication.
 */
यंत्रlinkage व्योम uprobe_trap(काष्ठा pt_regs *regs,
			    अचिन्हित दीर्घ trap_level)
अणु
	BUG_ON(trap_level != 0x173 && trap_level != 0x174);

	/* We are only पूर्णांकerested in user-mode code.  Uprobe traps
	 * shall not be present in kernel code.
	 */
	अगर (!user_mode(regs)) अणु
		local_irq_enable();
		bad_trap(regs, trap_level);
		वापस;
	पूर्ण

	/* trap_level == 0x173 --> ta 0x73
	 * trap_level == 0x174 --> ta 0x74
	 */
	अगर (notअगरy_die((trap_level == 0x173) ? DIE_BPT : DIE_SSTEP,
				(trap_level == 0x173) ? "bpt" : "sstep",
				regs, 0, trap_level, SIGTRAP) != NOTIFY_STOP)
		bad_trap(regs, trap_level);
पूर्ण

/* Callback routine क्रम handling die notअगरications.
*/
पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	पूर्णांक ret = NOTIFY_DONE;
	काष्ठा die_args *args = (काष्ठा die_args *)data;

	/* We are only पूर्णांकerested in userspace traps */
	अगर (args->regs && !user_mode(args->regs))
		वापस NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_BPT:
		अगर (uprobe_pre_sstep_notअगरier(args->regs))
			ret = NOTIFY_STOP;
		अवरोध;

	हाल DIE_SSTEP:
		अगर (uprobe_post_sstep_notअगरier(args->regs))
			ret = NOTIFY_STOP;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* This function माला_लो called when a XOL inकाष्ठाion either माला_लो
 * trapped or the thपढ़ो has a fatal संकेत, so reset the inकाष्ठाion
 * poपूर्णांकer to its probed address.
 */
व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr);
पूर्ण

/* If xol insn itself traps and generates a संकेत(Say,
 * संक_अवैध/संक_अंश/etc), then detect the हाल where a singlestepped
 * inकाष्ठाion jumps back to its own address.
 */
bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	वापस false;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr,
				  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_vaddr = regs->u_regs[UREG_I7];

	regs->u_regs[UREG_I7] = trampoline_vaddr-8;

	वापस orig_ret_vaddr + 8;
पूर्ण
