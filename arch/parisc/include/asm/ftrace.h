<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_FTRACE_H
#घोषणा _ASM_PARISC_FTRACE_H

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम mcount(व्योम);

#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)mcount)
#घोषणा MCOUNT_INSN_SIZE	4
#घोषणा CC_USING_NOP_MCOUNT
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
बाह्य अचिन्हित दीर्घ sys_call_table[];

बाह्य अचिन्हित दीर्घ वापस_address(अचिन्हित पूर्णांक);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम ftrace_caller(व्योम);

काष्ठा dyn_arch_ftrace अणु
पूर्ण;

अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr);

#पूर्ण_अगर

#घोषणा ftrace_वापस_address(n) वापस_address(n)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_PARISC_FTRACE_H */
