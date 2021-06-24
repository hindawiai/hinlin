<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kprobes.h>

/* Ftrace callback handler क्रम kprobes -- called under preepmt disabled */
व्योम kprobe_ftrace_handler(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			   काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा kprobe *p;
	काष्ठा pt_regs *regs;
	काष्ठा kprobe_ctlblk *kcb;
	पूर्णांक bit;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	preempt_disable_notrace();
	p = get_kprobe((kprobe_opcode_t *)ip);
	अगर (unlikely(!p) || kprobe_disabled(p))
		जाओ out;

	regs = ftrace_get_regs(fregs);
	kcb = get_kprobe_ctlblk();
	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(p);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ orig_ip = inकाष्ठाion_poपूर्णांकer(regs);

		inकाष्ठाion_poपूर्णांकer_set(regs, ip);

		__this_cpu_ग_लिखो(current_kprobe, p);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
			/*
			 * Emulate singlestep (and also recover regs->pc)
			 * as अगर there is a nop
			 */
			inकाष्ठाion_poपूर्णांकer_set(regs,
				(अचिन्हित दीर्घ)p->addr + MCOUNT_INSN_SIZE);
			अगर (unlikely(p->post_handler)) अणु
				kcb->kprobe_status = KPROBE_HIT_SSDONE;
				p->post_handler(p, regs, 0);
			पूर्ण
			inकाष्ठाion_poपूर्णांकer_set(regs, orig_ip);
		पूर्ण

		/*
		 * If pre_handler वापसs !0, it changes regs->pc. We have to
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
	p->ainsn.api.insn = शून्य;
	वापस 0;
पूर्ण
