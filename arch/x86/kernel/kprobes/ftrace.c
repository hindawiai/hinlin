<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Dynamic Ftrace based Kprobes Optimization
 *
 * Copyright (C) Hitachi Ltd., 2012
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/preempt.h>
#समावेश <linux/ftrace.h>

#समावेश "common.h"

/* Ftrace callback handler क्रम kprobes -- called under preempt disabled */
व्योम kprobe_ftrace_handler(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			   काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);
	काष्ठा kprobe *p;
	काष्ठा kprobe_ctlblk *kcb;
	पूर्णांक bit;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	preempt_disable_notrace();
	p = get_kprobe((kprobe_opcode_t *)ip);
	अगर (unlikely(!p) || kprobe_disabled(p))
		जाओ out;

	kcb = get_kprobe_ctlblk();
	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(p);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ orig_ip = regs->ip;
		/* Kprobe handler expects regs->ip = ip + 1 as अवरोधpoपूर्णांक hit */
		regs->ip = ip + माप(kprobe_opcode_t);

		__this_cpu_ग_लिखो(current_kprobe, p);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
			/*
			 * Emulate singlestep (and also recover regs->ip)
			 * as अगर there is a 5byte nop
			 */
			regs->ip = (अचिन्हित दीर्घ)p->addr + MCOUNT_INSN_SIZE;
			अगर (unlikely(p->post_handler)) अणु
				kcb->kprobe_status = KPROBE_HIT_SSDONE;
				p->post_handler(p, regs, 0);
			पूर्ण
			regs->ip = orig_ip;
		पूर्ण
		/*
		 * If pre_handler वापसs !0, it changes regs->ip. We have to
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
	p->ainsn.boostable = false;
	वापस 0;
पूर्ण
