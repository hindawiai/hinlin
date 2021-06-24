<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FTRACE_H
#घोषणा __ASM_SH_FTRACE_H

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा MCOUNT_INSN_SIZE	4 /* माप mcount call */
#घोषणा FTRACE_SYSCALL_MAX	NR_syscalls

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम mcount(व्योम);

#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)(mcount))

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#घोषणा CALL_ADDR		((दीर्घ)(ftrace_call))
#घोषणा STUB_ADDR		((दीर्घ)(ftrace_stub))
#घोषणा GRAPH_ADDR		((दीर्घ)(ftrace_graph_call))
#घोषणा CALLER_ADDR		((दीर्घ)(ftrace_caller))

#घोषणा MCOUNT_INSN_OFFSET	((STUB_ADDR - CALL_ADDR) - 4)
#घोषणा GRAPH_INSN_OFFSET	((CALLER_ADDR - GRAPH_ADDR) - 4)

काष्ठा dyn_arch_ftrace अणु
	/* No extra data needed on sh */
पूर्ण;

#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	/* 'addr' is the memory table address. */
	वापस addr;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#अगर_अघोषित __ASSEMBLY__

/* arch/sh/kernel/वापस_address.c */
बाह्य व्योम *वापस_address(अचिन्हित पूर्णांक);

#घोषणा ftrace_वापस_address(n) वापस_address(n)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_SH_FTRACE_H */
