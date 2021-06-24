<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/parisc/kernel/kprobes.c
 *
 * PA-RISC kprobes implementation
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/patch.h>

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	अगर ((अचिन्हित दीर्घ)p->addr & 3UL)
		वापस -EINVAL;

	p->ainsn.insn = get_insn_slot();
	अगर (!p->ainsn.insn)
		वापस -ENOMEM;

	स_नकल(p->ainsn.insn, p->addr,
		MAX_INSN_SIZE * माप(kprobe_opcode_t));
	p->opcode = *p->addr;
	flush_insn_slot(p);
	वापस 0;
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (!p->ainsn.insn)
		वापस;

	मुक्त_insn_slot(p->ainsn.insn, 0);
	p->ainsn.insn = शून्य;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	patch_text(p->addr, PARISC_KPROBES_BREAK_INSN);
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	patch_text(p->addr, p->opcode);
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

अटल व्योम __kprobes setup_singlestep(काष्ठा kprobe *p,
		काष्ठा kprobe_ctlblk *kcb, काष्ठा pt_regs *regs)
अणु
	kcb->iaoq[0] = regs->iaoq[0];
	kcb->iaoq[1] = regs->iaoq[1];
	regs->iaoq[0] = (अचिन्हित दीर्घ)p->ainsn.insn;
	mtctl(0, 0);
	regs->gr[0] |= PSW_R;
पूर्ण

पूर्णांक __kprobes parisc_kprobe_अवरोध_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	काष्ठा kprobe_ctlblk *kcb;

	preempt_disable();

	kcb = get_kprobe_ctlblk();
	p = get_kprobe((अचिन्हित दीर्घ *)regs->iaoq[0]);

	अगर (!p) अणु
		preempt_enable_no_resched();
		वापस 0;
	पूर्ण

	अगर (kprobe_running()) अणु
		/*
		 * We have reentered the kprobe_handler, since another kprobe
		 * was hit जबतक within the handler, we save the original
		 * kprobes and single step on the inकाष्ठाion of the new probe
		 * without calling any user handlers to aव्योम recursive
		 * kprobes.
		 */
		save_previous_kprobe(kcb);
		set_current_kprobe(p);
		kprobes_inc_nmissed_count(p);
		setup_singlestep(p, kcb, regs);
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
		setup_singlestep(p, kcb, regs);
		kcb->kprobe_status = KPROBE_HIT_SS;
	पूर्ण अन्यथा अणु
		reset_current_kprobe();
		preempt_enable_no_resched();
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक __kprobes parisc_kprobe_ss_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	काष्ठा kprobe *p = kprobe_running();

	अगर (!p)
		वापस 0;

	अगर (regs->iaoq[0] != (अचिन्हित दीर्घ)p->ainsn.insn+4)
		वापस 0;

	/* restore back original saved kprobe variables and जारी */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		वापस 1;
	पूर्ण

	/* क्रम असलolute branch inकाष्ठाions we can copy iaoq_b. क्रम relative
	 * branch inकाष्ठाions we need to calculate the new address based on the
	 * dअगरference between iaoq_f and iaoq_b. We cannot use iaoq_b without
	 * modअगरicationt because it's based on our ainsn.insn address.
	 */

	अगर (p->post_handler)
		p->post_handler(p, regs, 0);

	चयन (regs->iir >> 26) अणु
	हाल 0x38: /* BE */
	हाल 0x39: /* BE,L */
	हाल 0x3a: /* BV */
	हाल 0x3b: /* BVE */
		/* क्रम असलolute branches, regs->iaoq[1] has alपढ़ोy the right
		 * address
		 */
		regs->iaoq[0] = kcb->iaoq[1];
		अवरोध;
	शेष:
		regs->iaoq[1] = kcb->iaoq[0];
		regs->iaoq[1] += (regs->iaoq[1] - regs->iaoq[0]) + 4;
		regs->iaoq[0] = kcb->iaoq[1];
		अवरोध;
	पूर्ण
	kcb->kprobe_status = KPROBE_HIT_SSDONE;
	reset_current_kprobe();
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम kretprobe_trampoline(व्योम)
अणु
	यंत्र अस्थिर("nop");
	यंत्र अस्थिर("nop");
पूर्ण

अटल पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p,
					      काष्ठा pt_regs *regs);

अटल काष्ठा kprobe trampoline_p = अणु
	.pre_handler = trampoline_probe_handler
पूर्ण;

अटल पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p,
					      काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_address;

	orig_ret_address = __kretprobe_trampoline_handler(regs, trampoline_p.addr, शून्य);
	inकाष्ठाion_poपूर्णांकer_set(regs, orig_ret_address);

	वापस 1;
पूर्ण

व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->gr[2];
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr. */
	regs->gr[2] = (अचिन्हित दीर्घ)trampoline_p.addr;
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस p->addr == trampoline_p.addr;
पूर्ण

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	trampoline_p.addr = (kprobe_opcode_t *)
		dereference_function_descriptor(kretprobe_trampoline);
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण
