<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_FTRACE_H
#घोषणा _ASM_X86_FTRACE_H

#अगर_घोषित CONFIG_FUNCTION_TRACER
#अगर_अघोषित CC_USING_FENTRY
# error Compiler करोes not support fentry?
#पूर्ण_अगर
# define MCOUNT_ADDR		((अचिन्हित दीर्घ)(__fentry__))
#घोषणा MCOUNT_INSN_SIZE	5 /* माप mcount call */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#पूर्ण_अगर

#घोषणा HAVE_FUNCTION_GRAPH_RET_ADDR_PTR

#अगर_अघोषित __ASSEMBLY__
बाह्य atomic_t modअगरying_ftrace_code;
बाह्य व्योम __fentry__(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	/*
	 * addr is the address of the mcount call inकाष्ठाion.
	 * recordmcount करोes the necessary offset calculation.
	 */
	वापस addr;
पूर्ण

/*
 * When a ftrace रेजिस्टरed caller is tracing a function that is
 * also set by a रेजिस्टर_ftrace_direct() call, it needs to be
 * dअगरferentiated in the ftrace_caller trampoline. To करो this, we
 * place the direct caller in the ORIG_AX part of pt_regs. This
 * tells the ftrace_caller that there's a direct caller.
 */
अटल अंतरभूत व्योम arch_ftrace_set_direct_caller(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	/* Emulate a call */
	regs->orig_ax = addr;
पूर्ण

#अगर_घोषित CONFIG_HAVE_DYNAMIC_FTRACE_WITH_ARGS
काष्ठा ftrace_regs अणु
	काष्ठा pt_regs		regs;
पूर्ण;

अटल __always_अंतरभूत काष्ठा pt_regs *
arch_ftrace_get_regs(काष्ठा ftrace_regs *fregs)
अणु
	/* Only when FL_SAVE_REGS is set, cs will be non zero */
	अगर (!fregs->regs.cs)
		वापस शून्य;
	वापस &fregs->regs;
पूर्ण

#घोषणा ftrace_inकाष्ठाion_poपूर्णांकer_set(fregs, _ip)	\
	करो अणु (fregs)->regs.ip = (_ip); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

काष्ठा dyn_arch_ftrace अणु
	/* No extra data needed क्रम x86 */
पूर्ण;

#घोषणा FTRACE_GRAPH_TRAMP_ADDR FTRACE_GRAPH_ADDR

#पूर्ण_अगर /*  CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */


#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_FUNCTION_TRACER) && defined(CONFIG_DYNAMIC_FTRACE)
बाह्य व्योम set_ftrace_ops_ro(व्योम);
#अन्यथा
अटल अंतरभूत व्योम set_ftrace_ops_ro(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा ARCH_HAS_SYSCALL_MATCH_SYM_NAME
अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym, स्थिर अक्षर *name)
अणु
	/*
	 * Compare the symbol name with the प्रणाली call name. Skip the
	 * "__x64_sys", "__ia32_sys", "__do_sys" or simple "sys" prefix.
	 */
	वापस !म_भेद(sym + 3, name + 3) ||
		(!म_भेदन(sym, "__x64_", 6) && !म_भेद(sym + 9, name + 3)) ||
		(!म_भेदन(sym, "__ia32_", 7) && !म_भेद(sym + 10, name + 3)) ||
		(!म_भेदन(sym, "__do_sys", 8) && !म_भेद(sym + 8, name + 3));
पूर्ण

#अगर_अघोषित COMPILE_OFFSETS

#अगर defined(CONFIG_FTRACE_SYSCALLS) && defined(CONFIG_IA32_EMULATION)
#समावेश <linux/compat.h>

/*
 * Because ia32 syscalls करो not map to x86_64 syscall numbers
 * this screws up the trace output when tracing a ia32 task.
 * Instead of reporting bogus syscalls, just करो not trace them.
 *
 * If the user really wants these, then they should use the
 * raw syscall tracepoपूर्णांकs with filtering.
 */
#घोषणा ARCH_TRACE_IGNORE_COMPAT_SYSCALLS 1
अटल अंतरभूत bool arch_trace_is_compat_syscall(काष्ठा pt_regs *regs)
अणु
	वापस in_32bit_syscall();
पूर्ण
#पूर्ण_अगर /* CONFIG_FTRACE_SYSCALLS && CONFIG_IA32_EMULATION */
#पूर्ण_अगर /* !COMPILE_OFFSETS */
#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_FTRACE_H */
