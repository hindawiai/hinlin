<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Code क्रम tracing calls in Linux kernel.
 * Copyright (C) 2009-2016 Helge Deller <deller@gmx.de>
 *
 * based on code क्रम x86 which is:
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 *
 * future possible enhancements:
 *	- add CONFIG_STACK_TRACER
 */

#समावेश <linux/init.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/assembly.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/patch.h>

#घोषणा __hot __section(".text.hot")

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info.
 */
अटल व्योम __hot prepare_ftrace_वापस(अचिन्हित दीर्घ *parent,
					अचिन्हित दीर्घ self_addr)
अणु
	अचिन्हित दीर्घ old;
	बाह्य पूर्णांक parisc_वापस_to_handler;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	old = *parent;

	अगर (!function_graph_enter(old, self_addr, 0, शून्य))
		/* activate parisc_वापस_to_handler() as वापस poपूर्णांक */
		*parent = (अचिन्हित दीर्घ) &parisc_वापस_to_handler;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

व्योम notrace __hot ftrace_function_trampoline(अचिन्हित दीर्घ parent,
				अचिन्हित दीर्घ self_addr,
				अचिन्हित दीर्घ org_sp_gr3,
				काष्ठा ftrace_regs *fregs)
अणु
#अगर_अघोषित CONFIG_DYNAMIC_FTRACE
	बाह्य ftrace_func_t ftrace_trace_function;
#पूर्ण_अगर
	बाह्य काष्ठा ftrace_ops *function_trace_op;

	अगर (function_trace_op->flags & FTRACE_OPS_FL_ENABLED &&
	    ftrace_trace_function != ftrace_stub)
		ftrace_trace_function(self_addr, parent,
				function_trace_op, fregs);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (dereference_function_descriptor(ftrace_graph_वापस) !=
	    dereference_function_descriptor(ftrace_stub) ||
	    ftrace_graph_entry != ftrace_graph_entry_stub) अणु
		अचिन्हित दीर्घ *parent_rp;

		/* calculate poपूर्णांकer to %rp in stack */
		parent_rp = (अचिन्हित दीर्घ *) (org_sp_gr3 - RP_OFFSET);
		/* sanity check: parent_rp should hold parent */
		अगर (*parent_rp != parent)
			वापस;

		prepare_ftrace_वापस(parent_rp, self_addr);
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	वापस 0;
पूर्ण

पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
			अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण

अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr+(FTRACE_PATCHABLE_FUNCTION_SIZE-1)*4;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	u32 insn[FTRACE_PATCHABLE_FUNCTION_SIZE];
	u32 *tramp;
	पूर्णांक size, ret, i;
	व्योम *ip;

#अगर_घोषित CONFIG_64BIT
	अचिन्हित दीर्घ addr2 =
		(अचिन्हित दीर्घ)dereference_function_descriptor((व्योम *)addr);

	u32 ftrace_trampoline[] = अणु
		0x73c10208, /* std,ma r1,100(sp) */
		0x0c2110c1, /* ldd -10(r1),r1 */
		0xe820d002, /* bve,n (r1) */
		addr2 >> 32,
		addr2 & 0xffffffff,
		0xe83f1fd7, /* b,l,n .-14,r1 */
	पूर्ण;

	u32 ftrace_trampoline_unaligned[] = अणु
		addr2 >> 32,
		addr2 & 0xffffffff,
		0x37de0200, /* lकरो 100(sp),sp */
		0x73c13e01, /* std r1,-100(sp) */
		0x34213ff9, /* lकरो -4(r1),r1 */
		0x50213fc1, /* ldd -20(r1),r1 */
		0xe820d002, /* bve,n (r1) */
		0xe83f1fcf, /* b,l,n .-20,r1 */
	पूर्ण;

	BUILD_BUG_ON(ARRAY_SIZE(ftrace_trampoline_unaligned) >
				FTRACE_PATCHABLE_FUNCTION_SIZE);
#अन्यथा
	u32 ftrace_trampoline[] = अणु
		(u32)addr,
		0x6fc10080, /* stw,ma r1,40(sp) */
		0x48213fd1, /* ldw -18(r1),r1 */
		0xe820c002, /* bv,n r0(r1) */
		0xe83f1fdf, /* b,l,n .-c,r1 */
	पूर्ण;
#पूर्ण_अगर

	BUILD_BUG_ON(ARRAY_SIZE(ftrace_trampoline) >
				FTRACE_PATCHABLE_FUNCTION_SIZE);

	size = माप(ftrace_trampoline);
	tramp = ftrace_trampoline;

#अगर_घोषित CONFIG_64BIT
	अगर (rec->ip & 0x4) अणु
		size = माप(ftrace_trampoline_unaligned);
		tramp = ftrace_trampoline_unaligned;
	पूर्ण
#पूर्ण_अगर

	ip = (व्योम *)(rec->ip + 4 - size);

	ret = copy_from_kernel_nofault(insn, ip, size);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < size / 4; i++) अणु
		अगर (insn[i] != INSN_NOP)
			वापस -EINVAL;
	पूर्ण

	__patch_text_multiple(ip, tramp, size);
	वापस 0;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	u32 insn[FTRACE_PATCHABLE_FUNCTION_SIZE];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(insn); i++)
		insn[i] = INSN_NOP;

	__patch_text((व्योम *)rec->ip, INSN_NOP);
	__patch_text_multiple((व्योम *)rec->ip + 4 - माप(insn),
			      insn, माप(insn)-4);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
व्योम kprobe_ftrace_handler(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			   काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा kprobe_ctlblk *kcb;
	काष्ठा pt_regs *regs;
	काष्ठा kprobe *p;
	पूर्णांक bit;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	regs = ftrace_get_regs(fregs);
	preempt_disable_notrace();
	p = get_kprobe((kprobe_opcode_t *)ip);
	अगर (unlikely(!p) || kprobe_disabled(p))
		जाओ out;

	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(p);
		जाओ out;
	पूर्ण

	__this_cpu_ग_लिखो(current_kprobe, p);

	kcb = get_kprobe_ctlblk();
	kcb->kprobe_status = KPROBE_HIT_ACTIVE;

	regs->iaoq[0] = ip;
	regs->iaoq[1] = ip + 4;

	अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु
		regs->iaoq[0] = ip + 4;
		regs->iaoq[1] = ip + 8;

		अगर (unlikely(p->post_handler)) अणु
			kcb->kprobe_status = KPROBE_HIT_SSDONE;
			p->post_handler(p, regs, 0);
		पूर्ण
	पूर्ण
	__this_cpu_ग_लिखो(current_kprobe, शून्य);
out:
	preempt_enable_notrace();
	ftrace_test_recursion_unlock(bit);
पूर्ण
NOKPROBE_SYMBOL(kprobe_ftrace_handler);

पूर्णांक arch_prepare_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	p->ainsn.insn = शून्य;
	वापस 0;
पूर्ण
#पूर्ण_अगर
