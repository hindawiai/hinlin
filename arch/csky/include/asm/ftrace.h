<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_FTRACE_H
#घोषणा __ASM_CSKY_FTRACE_H

#घोषणा MCOUNT_INSN_SIZE	14

#घोषणा HAVE_FUNCTION_GRAPH_FP_TEST

#घोषणा HAVE_FUNCTION_GRAPH_RET_ADDR_PTR

#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1

#घोषणा MCOUNT_ADDR	((अचिन्हित दीर्घ)_mcount)

#अगर_अघोषित __ASSEMBLY__

बाह्य व्योम _mcount(अचिन्हित दीर्घ);

बाह्य व्योम ftrace_graph_call(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;
#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_CSKY_FTRACE_H */
