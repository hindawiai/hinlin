<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MICROBLAZE_FTRACE
#घोषणा _ASM_MICROBLAZE_FTRACE

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)(_mcount))
#घोषणा MCOUNT_INSN_SIZE	8 /* माप mcount call */

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम _mcount(व्योम);
बाह्य व्योम ftrace_call_graph(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/* relocation of mcount call site is the same as the address */
अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */
#पूर्ण_अगर /* _ASM_MICROBLAZE_FTRACE */
