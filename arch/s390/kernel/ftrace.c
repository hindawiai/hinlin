<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dynamic function tracer architecture backend.
 *
 * Copyright IBM Corp. 2009,2014
 *
 *   Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>,
 *		Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/kprobes.h>
#समावेश <trace/syscall.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/set_memory.h>
#समावेश "entry.h"

/*
 * To generate function prologue either gcc's hotpatch feature (since gcc 4.8)
 * or a combination of -pg -mrecord-mcount -mnop-mcount -mfentry flags
 * (since gcc 9 / clang 10) is used.
 * In both हालs the original and also the disabled function prologue contains
 * only a single six byte inकाष्ठाion and looks like this:
 * >	brcl	0,0			# offset 0
 * To enable ftrace the code माला_लो patched like above and afterwards looks
 * like this:
 * >	brasl	%r0,ftrace_caller	# offset 0
 *
 * The inकाष्ठाion will be patched by ftrace_make_call / ftrace_make_nop.
 * The ftrace function माला_लो called with a non-standard C function call ABI
 * where r0 contains the वापस address. It is also expected that the called
 * function only clobbers r0 and r1, but restores r2-r15.
 * For module code we can't directly jump to ftrace caller, but need a
 * trampoline (ftrace_plt), which clobbers also r1.
 */

अचिन्हित दीर्घ ftrace_plt;

पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
		       अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_insn orig, new, old;

	अगर (copy_from_kernel_nofault(&old, (व्योम *) rec->ip, माप(old)))
		वापस -EFAULT;
	/* Replace ftrace call with a nop. */
	ftrace_generate_call_insn(&orig, rec->ip);
	ftrace_generate_nop_insn(&new);

	/* Verअगरy that the to be replaced code matches what we expect. */
	अगर (स_भेद(&orig, &old, माप(old)))
		वापस -EINVAL;
	s390_kernel_ग_लिखो((व्योम *) rec->ip, &new, माप(new));
	वापस 0;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_insn orig, new, old;

	अगर (copy_from_kernel_nofault(&old, (व्योम *) rec->ip, माप(old)))
		वापस -EFAULT;
	/* Replace nop with an ftrace call. */
	ftrace_generate_nop_insn(&orig);
	ftrace_generate_call_insn(&new, rec->ip);

	/* Verअगरy that the to be replaced code matches what we expect. */
	अगर (स_भेद(&orig, &old, माप(old)))
		वापस -EINVAL;
	s390_kernel_ग_लिखो((व्योम *) rec->ip, &new, माप(new));
	वापस 0;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	वापस 0;
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MODULES

अटल पूर्णांक __init ftrace_plt_init(व्योम)
अणु
	अचिन्हित पूर्णांक *ip;

	ftrace_plt = (अचिन्हित दीर्घ) module_alloc(PAGE_SIZE);
	अगर (!ftrace_plt)
		panic("cannot allocate ftrace plt\n");
	ip = (अचिन्हित पूर्णांक *) ftrace_plt;
	ip[0] = 0x0d10e310; /* basr 1,0; lg 1,10(1); br 1 */
	ip[1] = 0x100a0004;
	ip[2] = 0x07f10000;
	ip[3] = FTRACE_ADDR >> 32;
	ip[4] = FTRACE_ADDR & 0xffffffff;
	set_memory_ro(ftrace_plt, 1);
	वापस 0;
पूर्ण
device_initcall(ftrace_plt_init);

#पूर्ण_अगर /* CONFIG_MODULES */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/*
 * Hook the वापस address and push it in the stack of वापस addresses
 * in current thपढ़ो info.
 */
अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ ra, अचिन्हित दीर्घ sp,
				    अचिन्हित दीर्घ ip)
अणु
	अगर (unlikely(ftrace_graph_is_dead()))
		जाओ out;
	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		जाओ out;
	ip -= MCOUNT_INSN_SIZE;
	अगर (!function_graph_enter(ra, ip, 0, (व्योम *) sp))
		ra = (अचिन्हित दीर्घ) वापस_to_handler;
out:
	वापस ra;
पूर्ण
NOKPROBE_SYMBOL(prepare_ftrace_वापस);

/*
 * Patch the kernel code at ftrace_graph_caller location. The inकाष्ठाion
 * there is branch relative on condition. To enable the ftrace graph code
 * block, we simply patch the mask field of the inकाष्ठाion to zero and
 * turn the inकाष्ठाion पूर्णांकo a nop.
 * To disable the ftrace graph code the mask field will be patched to
 * all ones, which turns the inकाष्ठाion पूर्णांकo an unconditional branch.
 */
पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	u8 op = 0x04; /* set mask field to zero */

	s390_kernel_ग_लिखो(__va(ftrace_graph_caller)+1, &op, माप(op));
	वापस 0;
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	u8 op = 0xf4; /* set mask field to all ones */

	s390_kernel_ग_लिखो(__va(ftrace_graph_caller)+1, &op, माप(op));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

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

	inकाष्ठाion_poपूर्णांकer_set(regs, ip);

	अगर (!p->pre_handler || !p->pre_handler(p, regs)) अणु

		inकाष्ठाion_poपूर्णांकer_set(regs, ip + MCOUNT_INSN_SIZE);

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
