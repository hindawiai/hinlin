<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Kernel Probes (KProbes)
 *  arch/mips/kernel/kprobes.c
 *
 *  Copyright 2006 Sony Corp.
 *  Copyright 2010 Cavium Networks
 *
 *  Some portions copied from the घातerpc version.
 *
 *   Copyright (C) IBM Corporation, 2002, 2004
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/preempt.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/अवरोध.h>

#समावेश "probes-common.h"

अटल स्थिर जोड़ mips_inकाष्ठाion अवरोधpoपूर्णांक_insn = अणु
	.b_क्रमmat = अणु
		.opcode = spec_op,
		.code = BRK_KPROBE_BP,
		.func = अवरोध_op
	पूर्ण
पूर्ण;

अटल स्थिर जोड़ mips_inकाष्ठाion अवरोधpoपूर्णांक2_insn = अणु
	.b_क्रमmat = अणु
		.opcode = spec_op,
		.code = BRK_KPROBE_SSTEPBP,
		.func = अवरोध_op
	पूर्ण
पूर्ण;

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe);
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

अटल पूर्णांक __kprobes insn_has_delayslot(जोड़ mips_inकाष्ठाion insn)
अणु
	वापस __insn_has_delay_slot(insn);
पूर्ण

/*
 * insn_has_ll_or_sc function checks whether inकाष्ठाion is ll or sc
 * one; putting अवरोधpoपूर्णांक on top of atomic ll/sc pair is bad idea;
 * so we need to prevent it and refuse kprobes insertion क्रम such
 * inकाष्ठाions; cannot करो much about अवरोधpoपूर्णांक in the middle of
 * ll/sc pair; it is upto user to aव्योम those places
 */
अटल पूर्णांक __kprobes insn_has_ll_or_sc(जोड़ mips_inकाष्ठाion insn)
अणु
	पूर्णांक ret = 0;

	चयन (insn.i_क्रमmat.opcode) अणु
	हाल ll_op:
	हाल lld_op:
	हाल sc_op:
	हाल scd_op:
		ret = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	जोड़ mips_inकाष्ठाion insn;
	जोड़ mips_inकाष्ठाion prev_insn;
	पूर्णांक ret = 0;

	insn = p->addr[0];

	अगर (insn_has_ll_or_sc(insn)) अणु
		pr_notice("Kprobes for ll and sc instructions are not"
			  "supported\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_from_kernel_nofault(&prev_insn, p->addr - 1,
			माप(mips_inकाष्ठाion)) == 0 &&
	    insn_has_delayslot(prev_insn)) अणु
		pr_notice("Kprobes for branch delayslot are not supported\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (__insn_is_compact_branch(insn)) अणु
		pr_notice("Kprobes for compact branches are not supported\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* insn: must be on special executable page on mips. */
	p->ainsn.insn = get_insn_slot();
	अगर (!p->ainsn.insn) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * In the kprobe->ainsn.insn[] array we store the original
	 * inकाष्ठाion at index zero and a अवरोध trap inकाष्ठाion at
	 * index one.
	 *
	 * On MIPS arch अगर the inकाष्ठाion at probed address is a
	 * branch inकाष्ठाion, we need to execute the inकाष्ठाion at
	 * Branch Delayslot (BD) at the समय of probe hit. As MIPS also
	 * करोesn't have single stepping support, the BD inकाष्ठाion can
	 * not be executed in-line and it would be executed on SSOL slot
	 * using a normal अवरोधpoपूर्णांक inकाष्ठाion in the next slot.
	 * So, पढ़ो the inकाष्ठाion and save it क्रम later execution.
	 */
	अगर (insn_has_delayslot(insn))
		स_नकल(&p->ainsn.insn[0], p->addr + 1, माप(kprobe_opcode_t));
	अन्यथा
		स_नकल(&p->ainsn.insn[0], p->addr, माप(kprobe_opcode_t));

	p->ainsn.insn[1] = अवरोधpoपूर्णांक2_insn;
	p->opcode = *p->addr;

out:
	वापस ret;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = अवरोधpoपूर्णांक_insn;
	flush_insn_slot(p);
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = p->opcode;
	flush_insn_slot(p);
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.insn) अणु
		मुक्त_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = शून्य;
	पूर्ण
पूर्ण

अटल व्योम save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
	kcb->prev_kprobe.old_SR = kcb->kprobe_old_SR;
	kcb->prev_kprobe.saved_SR = kcb->kprobe_saved_SR;
	kcb->prev_kprobe.saved_epc = kcb->kprobe_saved_epc;
पूर्ण

अटल व्योम restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
	kcb->kprobe_old_SR = kcb->prev_kprobe.old_SR;
	kcb->kprobe_saved_SR = kcb->prev_kprobe.saved_SR;
	kcb->kprobe_saved_epc = kcb->prev_kprobe.saved_epc;
पूर्ण

अटल व्योम set_current_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			       काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
	kcb->kprobe_saved_SR = kcb->kprobe_old_SR = (regs->cp0_status & ST0_IE);
	kcb->kprobe_saved_epc = regs->cp0_epc;
पूर्ण

/**
 * evaluate_branch_instrucion -
 *
 * Evaluate the branch inकाष्ठाion at probed address during probe hit. The
 * result of evaluation would be the updated epc. The insturction in delayslot
 * would actually be single stepped using a normal अवरोधpoपूर्णांक) on SSOL slot.
 *
 * The result is also saved in the kprobe control block क्रम later use,
 * in हाल we need to execute the delayslot inकाष्ठाion. The latter will be
 * false क्रम NOP inकाष्ठाion in dealyslot and the branch-likely inकाष्ठाions
 * when the branch is taken. And क्रम those हालs we set a flag as
 * SKIP_DELAYSLOT in the kprobe control block
 */
अटल पूर्णांक evaluate_branch_inकाष्ठाion(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
					काष्ठा kprobe_ctlblk *kcb)
अणु
	जोड़ mips_inकाष्ठाion insn = p->opcode;
	दीर्घ epc;
	पूर्णांक ret = 0;

	epc = regs->cp0_epc;
	अगर (epc & 3)
		जाओ unaligned;

	अगर (p->ainsn.insn->word == 0)
		kcb->flags |= SKIP_DELAYSLOT;
	अन्यथा
		kcb->flags &= ~SKIP_DELAYSLOT;

	ret = __compute_वापस_epc_क्रम_insn(regs, insn);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == BRANCH_LIKELY_TAKEN)
		kcb->flags |= SKIP_DELAYSLOT;

	kcb->target_epc = regs->cp0_epc;

	वापस 0;

unaligned:
	pr_notice("%s: unaligned epc - sending SIGBUS.\n", current->comm);
	क्रमce_sig(SIGBUS);
	वापस -EFAULT;

पूर्ण

अटल व्योम prepare_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
						काष्ठा kprobe_ctlblk *kcb)
अणु
	पूर्णांक ret = 0;

	regs->cp0_status &= ~ST0_IE;

	/* single step अंतरभूत अगर the inकाष्ठाion is a अवरोध */
	अगर (p->opcode.word == अवरोधpoपूर्णांक_insn.word ||
	    p->opcode.word == अवरोधpoपूर्णांक2_insn.word)
		regs->cp0_epc = (अचिन्हित दीर्घ)p->addr;
	अन्यथा अगर (insn_has_delayslot(p->opcode)) अणु
		ret = evaluate_branch_inकाष्ठाion(p, regs, kcb);
		अगर (ret < 0) अणु
			pr_notice("Kprobes: Error in evaluating branch\n");
			वापस;
		पूर्ण
	पूर्ण
	regs->cp0_epc = (अचिन्हित दीर्घ)&p->ainsn.insn[0];
पूर्ण

/*
 * Called after single-stepping.  p->addr is the address of the
 * inकाष्ठाion whose first byte has been replaced by the "break 0"
 * inकाष्ठाion.	 To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.  The address of this
 * copy is p->ainsn.insn.
 *
 * This function prepares to वापस from the post-single-step
 * अवरोधpoपूर्णांक trap. In हाल of branch inकाष्ठाions, the target
 * epc to be restored.
 */
अटल व्योम __kprobes resume_execution(काष्ठा kprobe *p,
				       काष्ठा pt_regs *regs,
				       काष्ठा kprobe_ctlblk *kcb)
अणु
	अगर (insn_has_delayslot(p->opcode))
		regs->cp0_epc = kcb->target_epc;
	अन्यथा अणु
		अचिन्हित दीर्घ orig_epc = kcb->kprobe_saved_epc;
		regs->cp0_epc = orig_epc + 4;
	पूर्ण
पूर्ण

अटल पूर्णांक __kprobes kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	पूर्णांक ret = 0;
	kprobe_opcode_t *addr;
	काष्ठा kprobe_ctlblk *kcb;

	addr = (kprobe_opcode_t *) regs->cp0_epc;

	/*
	 * We करोn't want to be preempted क्रम the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	/* Check we're not actually recursing */
	अगर (kprobe_running()) अणु
		p = get_kprobe(addr);
		अगर (p) अणु
			अगर (kcb->kprobe_status == KPROBE_HIT_SS &&
			    p->ainsn.insn->word == अवरोधpoपूर्णांक_insn.word) अणु
				regs->cp0_status &= ~ST0_IE;
				regs->cp0_status |= kcb->kprobe_saved_SR;
				जाओ no_kprobe;
			पूर्ण
			/*
			 * We have reentered the kprobe_handler(), since
			 * another probe was hit जबतक within the handler.
			 * We here save the original kprobes variables and
			 * just single step on the inकाष्ठाion of the new probe
			 * without calling any user handlers.
			 */
			save_previous_kprobe(kcb);
			set_current_kprobe(p, regs, kcb);
			kprobes_inc_nmissed_count(p);
			prepare_singlestep(p, regs, kcb);
			kcb->kprobe_status = KPROBE_REENTER;
			अगर (kcb->flags & SKIP_DELAYSLOT) अणु
				resume_execution(p, regs, kcb);
				restore_previous_kprobe(kcb);
				preempt_enable_no_resched();
			पूर्ण
			वापस 1;
		पूर्ण अन्यथा अगर (addr->word != अवरोधpoपूर्णांक_insn.word) अणु
			/*
			 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd by
			 * another cpu right after we hit, no further
			 * handling of this पूर्णांकerrupt is appropriate
			 */
			ret = 1;
		पूर्ण
		जाओ no_kprobe;
	पूर्ण

	p = get_kprobe(addr);
	अगर (!p) अणु
		अगर (addr->word != अवरोधpoपूर्णांक_insn.word) अणु
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
		/* handler has alपढ़ोy set things up, so skip ss setup */
		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण

	prepare_singlestep(p, regs, kcb);
	अगर (kcb->flags & SKIP_DELAYSLOT) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		अगर (p->post_handler)
			p->post_handler(p, regs, 0);
		resume_execution(p, regs, kcb);
		preempt_enable_no_resched();
	पूर्ण अन्यथा
		kcb->kprobe_status = KPROBE_HIT_SS;

	वापस 1;

no_kprobe:
	preempt_enable_no_resched();
	वापस ret;

पूर्ण

अटल अंतरभूत पूर्णांक post_kprobe_handler(काष्ठा pt_regs *regs)
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

	regs->cp0_status |= kcb->kprobe_saved_SR;

	/* Restore back the original saved kprobes variables and जारी. */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		जाओ out;
	पूर्ण
	reset_current_kprobe();
out:
	preempt_enable_no_resched();

	वापस 1;
पूर्ण

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
		वापस 1;

	अगर (kcb->kprobe_status & KPROBE_HIT_SS) अणु
		resume_execution(cur, regs, kcb);
		regs->cp0_status |= kcb->kprobe_old_SR;

		reset_current_kprobe();
		preempt_enable_no_resched();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Wrapper routine क्रम handling exceptions.
 */
पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु

	काष्ठा die_args *args = (काष्ठा die_args *)data;
	पूर्णांक ret = NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_BREAK:
		अगर (kprobe_handler(args->regs))
			ret = NOTIFY_STOP;
		अवरोध;
	हाल DIE_SSTEPBP:
		अगर (post_kprobe_handler(args->regs))
			ret = NOTIFY_STOP;
		अवरोध;

	हाल DIE_PAGE_FAULT:
		/* kprobe_running() needs smp_processor_id() */
		preempt_disable();

		अगर (kprobe_running()
		    && kprobe_fault_handler(args->regs, args->trapnr))
			ret = NOTIFY_STOP;
		preempt_enable();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Function वापस probe trampoline:
 *	- init_kprobes() establishes a probepoपूर्णांक here
 *	- When the probed function वापसs, this probe causes the
 *	  handlers to fire
 */
अटल व्योम __used kretprobe_trampoline_holder(व्योम)
अणु
	यंत्र अस्थिर(
		".set push\n\t"
		/* Keep the assembler from reordering and placing JR here. */
		".set noreorder\n\t"
		"nop\n\t"
		".global kretprobe_trampoline\n"
		"kretprobe_trampoline:\n\t"
		"nop\n\t"
		".set pop"
		: : : "memory");
पूर्ण

व्योम kretprobe_trampoline(व्योम);

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *) regs->regs[31];
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->regs[31] = (अचिन्हित दीर्घ)kretprobe_trampoline;
पूर्ण

/*
 * Called when the probe at kretprobe trampoline is hit
 */
अटल पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p,
						काष्ठा pt_regs *regs)
अणु
	inकाष्ठाion_poपूर्णांकer(regs) = __kretprobe_trampoline_handler(regs,
						kretprobe_trampoline, शून्य);
	/*
	 * By वापसing a non-zero value, we are telling
	 * kprobe_handler() that we करोn't want the post_handler
	 * to run (and have re-enabled preemption)
	 */
	वापस 1;
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->addr == (kprobe_opcode_t *)kretprobe_trampoline)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा kprobe trampoline_p = अणु
	.addr = (kprobe_opcode_t *)kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण
