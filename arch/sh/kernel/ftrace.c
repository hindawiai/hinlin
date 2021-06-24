<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Matt Fleming <matt@console-pimps.org>
 * Copyright (C) 2008 Paul Mundt <lethal@linux-sh.org>
 *
 * Code क्रम replacing ftrace calls with jumps.
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 *
 * Thanks goes to Ingo Molnar, क्रम suggesting the idea.
 * Mathieu Desnoyers, क्रम suggesting postponing the modअगरications.
 * Arjan van de Ven, क्रम keeping me straight, and explaining to me
 * the dangers of modअगरying code on the run.
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/unistd.h>
#समावेश <trace/syscall.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल अचिन्हित अक्षर ftrace_replaced_code[MCOUNT_INSN_SIZE];

अटल अचिन्हित अक्षर ftrace_nop[4];
/*
 * If we're trying to nop out a call to a function, we instead
 * place a call to the address after the memory table.
 *
 * 8c011060 <a>:
 * 8c011060:       02 d1           mov.l   8c01106c <a+0xc>,r1
 * 8c011062:       22 4f           sts.l   pr,@-r15
 * 8c011064:       02 c7           mova    8c011070 <a+0x10>,r0
 * 8c011066:       2b 41           jmp     @r1
 * 8c011068:       2a 40           lds     r0,pr
 * 8c01106a:       09 00           nop
 * 8c01106c:       68 24           .word 0x2468     <--- ip
 * 8c01106e:       1d 8c           .word 0x8c1d
 * 8c011070:       26 4f           lds.l   @r15+,pr <--- ip + MCOUNT_INSN_SIZE
 *
 * We ग_लिखो 0x8c011070 to 0x8c01106c so that on entry to a() we branch
 * past the _mcount call and जारी executing code like normal.
 */
अटल अचिन्हित अक्षर *ftrace_nop_replace(अचिन्हित दीर्घ ip)
अणु
	__raw_ग_लिखोl(ip + MCOUNT_INSN_SIZE, ftrace_nop);
	वापस ftrace_nop;
पूर्ण

अटल अचिन्हित अक्षर *ftrace_call_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	/* Place the address in the memory table. */
	__raw_ग_लिखोl(addr, ftrace_replaced_code);

	/*
	 * No locking needed, this must be called via kstop_machine
	 * which in essence is like running on a uniprocessor machine.
	 */
	वापस ftrace_replaced_code;
पूर्ण

/*
 * Modअगरying code must take extra care. On an SMP machine, अगर
 * the code being modअगरied is also being executed on another CPU
 * that CPU will have undefined results and possibly take a GPF.
 * We use kstop_machine to stop other CPUS from executing code.
 * But this करोes not stop NMIs from happening. We still need
 * to protect against that. We separate out the modअगरication of
 * the code to take care of this.
 *
 * Two buffers are added: An IP buffer and a "code" buffer.
 *
 * 1) Put the inकाष्ठाion poपूर्णांकer पूर्णांकo the IP buffer
 *    and the new code पूर्णांकo the "code" buffer.
 * 2) Wait क्रम any running NMIs to finish and set a flag that says
 *    we are modअगरying code, it is करोne in an atomic operation.
 * 3) Write the code
 * 4) clear the flag.
 * 5) Wait क्रम any running NMIs to finish.
 *
 * If an NMI is executed, the first thing it करोes is to call
 * "ftrace_nmi_enter". This will check अगर the flag is set to ग_लिखो
 * and अगर it is, it will ग_लिखो what is in the IP and "code" buffers.
 *
 * The trick is, it करोes not matter अगर everyone is writing the same
 * content to the code location. Also, अगर a CPU is executing code
 * it is OK to ग_लिखो to that code location अगर the contents being written
 * are the same as what exists.
 */
#घोषणा MOD_CODE_WRITE_FLAG (1 << 31)	/* set when NMI should करो the ग_लिखो */
अटल atomic_t nmi_running = ATOMIC_INIT(0);
अटल पूर्णांक mod_code_status;		/* holds वापस value of text ग_लिखो */
अटल व्योम *mod_code_ip;		/* holds the IP to ग_लिखो to */
अटल व्योम *mod_code_newcode;		/* holds the text to ग_लिखो to the IP */

अटल व्योम clear_mod_flag(व्योम)
अणु
	पूर्णांक old = atomic_पढ़ो(&nmi_running);

	क्रम (;;) अणु
		पूर्णांक new = old & ~MOD_CODE_WRITE_FLAG;

		अगर (old == new)
			अवरोध;

		old = atomic_cmpxchg(&nmi_running, old, new);
	पूर्ण
पूर्ण

अटल व्योम ftrace_mod_code(व्योम)
अणु
	/*
	 * Yes, more than one CPU process can be writing to mod_code_status.
	 *    (and the code itself)
	 * But अगर one were to fail, then they all should, and अगर one were
	 * to succeed, then they all should.
	 */
	mod_code_status = copy_to_kernel_nofault(mod_code_ip, mod_code_newcode,
					     MCOUNT_INSN_SIZE);

	/* अगर we fail, then समाप्त any new ग_लिखोrs */
	अगर (mod_code_status)
		clear_mod_flag();
पूर्ण

व्योम arch_ftrace_nmi_enter(व्योम)
अणु
	अगर (atomic_inc_वापस(&nmi_running) & MOD_CODE_WRITE_FLAG) अणु
		smp_rmb();
		ftrace_mod_code();
	पूर्ण
	/* Must have previous changes seen beक्रमe executions */
	smp_mb();
पूर्ण

व्योम arch_ftrace_nmi_निकास(व्योम)
अणु
	/* Finish all executions beक्रमe clearing nmi_running */
	smp_mb();
	atomic_dec(&nmi_running);
पूर्ण

अटल व्योम रुको_क्रम_nmi_and_set_mod_flag(व्योम)
अणु
	अगर (!atomic_cmpxchg(&nmi_running, 0, MOD_CODE_WRITE_FLAG))
		वापस;

	करो अणु
		cpu_relax();
	पूर्ण जबतक (atomic_cmpxchg(&nmi_running, 0, MOD_CODE_WRITE_FLAG));
पूर्ण

अटल व्योम रुको_क्रम_nmi(व्योम)
अणु
	अगर (!atomic_पढ़ो(&nmi_running))
		वापस;

	करो अणु
		cpu_relax();
	पूर्ण जबतक (atomic_पढ़ो(&nmi_running));
पूर्ण

अटल पूर्णांक
करो_ftrace_mod_code(अचिन्हित दीर्घ ip, व्योम *new_code)
अणु
	mod_code_ip = (व्योम *)ip;
	mod_code_newcode = new_code;

	/* The buffers need to be visible beक्रमe we let NMIs ग_लिखो them */
	smp_mb();

	रुको_क्रम_nmi_and_set_mod_flag();

	/* Make sure all running NMIs have finished beक्रमe we ग_लिखो the code */
	smp_mb();

	ftrace_mod_code();

	/* Make sure the ग_लिखो happens beक्रमe clearing the bit */
	smp_mb();

	clear_mod_flag();
	रुको_क्रम_nmi();

	वापस mod_code_status;
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ ip, अचिन्हित अक्षर *old_code,
		       अचिन्हित अक्षर *new_code)
अणु
	अचिन्हित अक्षर replaced[MCOUNT_INSN_SIZE];

	/*
	 * Note:
	 * We are paranoid about modअगरying text, as अगर a bug was to happen, it
	 * could cause us to पढ़ो or ग_लिखो to someplace that could cause harm.
	 * Carefully पढ़ो and modअगरy the code with probe_kernel_*(), and make
	 * sure what we पढ़ो is what we expected it to be beक्रमe modअगरying it.
	 */

	/* पढ़ो the text we want to modअगरy */
	अगर (copy_from_kernel_nofault(replaced, (व्योम *)ip, MCOUNT_INSN_SIZE))
		वापस -EFAULT;

	/* Make sure it is what we expect it to be */
	अगर (स_भेद(replaced, old_code, MCOUNT_INSN_SIZE) != 0)
		वापस -EINVAL;

	/* replace the text with the new text */
	अगर (करो_ftrace_mod_code(ip, new_code))
		वापस -EPERM;

	flush_icache_range(ip, ip + MCOUNT_INSN_SIZE);

	वापस 0;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call) + MCOUNT_INSN_OFFSET;
	अचिन्हित अक्षर old[MCOUNT_INSN_SIZE], *new;

	स_नकल(old, (अचिन्हित अक्षर *)ip, MCOUNT_INSN_SIZE);
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func);

	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
		    काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *new, *old;
	अचिन्हित दीर्घ ip = rec->ip;

	old = ftrace_call_replace(ip, addr);
	new = ftrace_nop_replace(ip);

	वापस ftrace_modअगरy_code(rec->ip, old, new);
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *new, *old;
	अचिन्हित दीर्घ ip = rec->ip;

	old = ftrace_nop_replace(ip);
	new = ftrace_call_replace(ip, addr);

	वापस ftrace_modअगरy_code(rec->ip, old, new);
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम ftrace_graph_call(व्योम);

अटल पूर्णांक ftrace_mod(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ old_addr,
		      अचिन्हित दीर्घ new_addr)
अणु
	अचिन्हित अक्षर code[MCOUNT_INSN_SIZE];

	अगर (copy_from_kernel_nofault(code, (व्योम *)ip, MCOUNT_INSN_SIZE))
		वापस -EFAULT;

	अगर (old_addr != __raw_पढ़ोl((अचिन्हित दीर्घ *)code))
		वापस -EINVAL;

	__raw_ग_लिखोl(new_addr, ip);
	वापस 0;
पूर्ण

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip, old_addr, new_addr;

	ip = (अचिन्हित दीर्घ)(&ftrace_graph_call) + GRAPH_INSN_OFFSET;
	old_addr = (अचिन्हित दीर्घ)(&skip_trace);
	new_addr = (अचिन्हित दीर्घ)(&ftrace_graph_caller);

	वापस ftrace_mod(ip, old_addr, new_addr);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip, old_addr, new_addr;

	ip = (अचिन्हित दीर्घ)(&ftrace_graph_call) + GRAPH_INSN_OFFSET;
	old_addr = (अचिन्हित दीर्घ)(&ftrace_graph_caller);
	new_addr = (अचिन्हित दीर्घ)(&skip_trace);

	वापस ftrace_mod(ip, old_addr, new_addr);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in the current thपढ़ो info.
 *
 * This is the मुख्य routine क्रम the function graph tracer. The function
 * graph tracer essentially works like this:
 *
 * parent is the stack address containing self_addr's वापस address.
 * We pull the real वापस address out of parent and store it in
 * current's ret_stack. Then, we replace the वापस address on the stack
 * with the address of वापस_to_handler. self_addr is the function that
 * called mcount.
 *
 * When self_addr वापसs, it will jump to वापस_to_handler which calls
 * ftrace_वापस_to_handler. ftrace_वापस_to_handler will pull the real
 * वापस address off of current's ret_stack and jump to it.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr)
अणु
	अचिन्हित दीर्घ old;
	पूर्णांक faulted;
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * Protect against fault, even अगर it shouldn't
	 * happen. This tool is too much पूर्णांकrusive to
	 * ignore such a protection.
	 */
	__यंत्र__ __अस्थिर__(
		"1:						\n\t"
		"mov.l		@%2, %0				\n\t"
		"2:						\n\t"
		"mov.l		%3, @%2				\n\t"
		"mov		#0, %1				\n\t"
		"3:						\n\t"
		".section .fixup, \"ax\"			\n\t"
		"4:						\n\t"
		"mov.l		5f, %0				\n\t"
		"jmp		@%0				\n\t"
		" mov		#1, %1				\n\t"
		".balign 4					\n\t"
		"5:	.long 3b				\n\t"
		".previous					\n\t"
		".section __ex_table,\"a\"			\n\t"
		".long 1b, 4b					\n\t"
		".long 2b, 4b					\n\t"
		".previous					\n\t"
		: "=&r" (old), "=r" (faulted)
		: "r" (parent), "r" (वापस_hooker)
	);

	अगर (unlikely(faulted)) अणु
		ftrace_graph_stop();
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (function_graph_enter(old, self_addr, 0, शून्य))
		__raw_ग_लिखोl(old, parent);
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
