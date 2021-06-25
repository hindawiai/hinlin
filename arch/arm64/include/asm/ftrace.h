<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/ftrace.h
 *
 * Copyright (C) 2013 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */
#अगर_अघोषित __ASM_FTRACE_H
#घोषणा __ASM_FTRACE_H

#समावेश <यंत्र/insn.h>

#घोषणा HAVE_FUNCTION_GRAPH_FP_TEST

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#अन्यथा
#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)_mcount)
#पूर्ण_अगर

/* The BL at the callsite's adjusted rec->ip */
#घोषणा MCOUNT_INSN_SIZE	AARCH64_INSN_SIZE

#घोषणा FTRACE_PLT_IDX		0
#घोषणा FTRACE_REGS_PLT_IDX	1
#घोषणा NR_FTRACE_PLTS		2

/*
 * Currently, gcc tends to save the link रेजिस्टर after the local variables
 * on the stack. This causes the max stack tracer to report the function
 * frame sizes क्रम the wrong functions. By defining
 * ARCH_FTRACE_SHIFT_STACK_TRACER, it will tell the stack tracer to expect
 * to find the वापस address on the stack after the local variables have
 * been set up.
 *
 * Note, this may change in the future, and we will need to deal with that
 * अगर it were to happen.
 */
#घोषणा ARCH_FTRACE_SHIFT_STACK_TRACER 1

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/compat.h>

बाह्य व्योम _mcount(अचिन्हित दीर्घ);
बाह्य व्योम *वापस_address(अचिन्हित पूर्णांक);

काष्ठा dyn_arch_ftrace अणु
	/* No extra data needed क्रम arm64 */
पूर्ण;

बाह्य अचिन्हित दीर्घ ftrace_graph_call;

बाह्य व्योम वापस_to_handler(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	/*
	 * Adjust addr to poपूर्णांक at the BL in the callsite.
	 * See ftrace_init_nop() क्रम the callsite sequence.
	 */
	अगर (IS_ENABLED(CONFIG_DYNAMIC_FTRACE_WITH_REGS))
		वापस addr + AARCH64_INSN_SIZE;
	/*
	 * addr is the address of the mcount call inकाष्ठाion.
	 * recordmcount करोes the necessary offset calculation.
	 */
	वापस addr;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
काष्ठा dyn_ftrace;
पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec);
#घोषणा ftrace_init_nop ftrace_init_nop
#पूर्ण_अगर

#घोषणा ftrace_वापस_address(n) वापस_address(n)

/*
 * Because AArch32 mode करोes not share the same syscall table with AArch64,
 * tracing compat syscalls may result in reporting bogus syscalls or even
 * hang-up, so just करो not trace them.
 * See kernel/trace/trace_syscalls.c
 *
 * x86 code says:
 * If the user really wants these, then they should use the
 * raw syscall tracepoपूर्णांकs with filtering.
 */
#घोषणा ARCH_TRACE_IGNORE_COMPAT_SYSCALLS
अटल अंतरभूत bool arch_trace_is_compat_syscall(काष्ठा pt_regs *regs)
अणु
	वापस is_compat_task();
पूर्ण

#घोषणा ARCH_HAS_SYSCALL_MATCH_SYM_NAME

अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym,
					       स्थिर अक्षर *name)
अणु
	/*
	 * Since all syscall functions have __arm64_ prefix, we must skip it.
	 * However, as we described above, we decided to ignore compat
	 * syscalls, so we करोn't care about __arm64_compat_ prefix here.
	 */
	वापस !म_भेद(sym + 8, name);
पूर्ण
#पूर्ण_अगर /* अगरndef __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_FTRACE_H */
