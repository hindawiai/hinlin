<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_FTRACE_H
#घोषणा _ASM_IA64_FTRACE_H

#अगर_घोषित CONFIG_FUNCTION_TRACER
#घोषणा MCOUNT_INSN_SIZE        32 /* माप mcount call */

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम _mcount(अचिन्हित दीर्घ pfs, अचिन्हित दीर्घ r1, अचिन्हित दीर्घ b0, अचिन्हित दीर्घ r0);
#घोषणा mcount _mcount

/* In IA64, MCOUNT_ADDR is set in link समय, so it's not a स्थिरant at compile समय */
#घोषणा MCOUNT_ADDR (((काष्ठा fnptr *)mcount)->ip)
#घोषणा FTRACE_ADDR (((काष्ठा fnptr *)ftrace_caller)->ip)

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	/* second bundle, insn 2 */
	वापस addr - 0x12;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#पूर्ण_अगर /* _ASM_IA64_FTRACE_H */
