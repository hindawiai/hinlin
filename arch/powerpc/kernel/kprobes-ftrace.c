<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Dynamic Ftrace based Kprobes Optimization
 *
 * Copyright (C) Hitachi Ltd., 2012
 * Copyright 2016 Naveen N. Rao <naveen.n.rao@linux.vnet.ibm.com>
 *		  IBM Corporation
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/preempt.h>
#समावेश <linux/ftrace.h>

/* Ftrace callback handler क्रम kprobes */
व्योम kprobe_ftrace_handler(अचिन्हित दीर्घ nip, अचिन्हित दीर्घ parent_nip,
			   काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा kprobe *p;
	काष्ठा kprobe_ctlblk *kcb;
	काष्ठा pt_regs *regs;
	पूर्णांक bit;

	bit = ftrace_test_recursion_trylock(nip, parent_nip);
	अगर (bit < 0)
		वापस;

	regs = ftrace_get_regs(fregs);
	preempt_disable_notrace();
	p = get_kprobe((kprobe_opcode_t *)nip);
	अगर (unlikely(!p) || kprobe_disabled(p))
		जाओ out;

	kcb = get_kprobe_ctlblk();
	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(p);
	पूर्ण अन्यथा अणु
		/*
		 * On घातerpc, NIP is *beक्रमe* this inकाष्ठाion क्रम the
		 * pre handler
		 */
		regs->nip -= MCOUNT_INSN_SIZE;

		__this_cpu_ग_लिखो(current_kprobe, p);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
			/*
			 * Emulate singlestep (and also recover regs->nip)
			 * as अगर there is a nop
			 */
			regs->nip += MCOUNT_INSN_SIZE;
			अगर (unlikely(p->post_handler)) अणु
				kcb->kprobe_status = KPROBE_HIT_SSDONE;
				p->post_handler(p, regs, 0);
			पूर्ण
		पूर्ण
		/*
		 * If pre_handler वापसs !0, it changes regs->nip. We have to
		 * skip emulating post_handler.
		 */
		__this_cpu_ग_लिखो(current_kprobe, शून्य);
	पूर्ण
out:
	preempt_enable_notrace();
	ftrace_test_recursion_unlock(bit);
पूर्ण
NOKPROBE_SYMBOL(kprobe_ftrace_handler);

पूर्णांक arch_prepare_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	p->ainsn.insn = शून्य;
	p->ainsn.boostable = -1;
	वापस 0;
पूर्ण
