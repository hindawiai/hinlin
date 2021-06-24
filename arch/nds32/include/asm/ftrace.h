<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_NDS32_FTRACE_H
#घोषणा __ASM_NDS32_FTRACE_H

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा HAVE_FUNCTION_GRAPH_FP_TEST

#घोषणा MCOUNT_ADDR ((अचिन्हित दीर्घ)(_mcount))
/* mcount call is composed of three inकाष्ठाions:
 * sethi + ori + jral
 */
#घोषणा MCOUNT_INSN_SIZE 12

बाह्य व्योम _mcount(अचिन्हित दीर्घ parent_ip);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

#घोषणा FTRACE_ADDR ((अचिन्हित दीर्घ)_ftrace_caller)

#अगर_घोषित __NDS32_EL__
#घोषणा INSN_NOP		0x09000040
#घोषणा INSN_SIZE(insn)		(((insn & 0x00000080) == 0) ? 4 : 2)
#घोषणा IS_SETHI(insn)		((insn & 0x000000fe) == 0x00000046)
#घोषणा ENDIAN_CONVERT(insn)	be32_to_cpu(insn)
#अन्यथा /* __NDS32_EB__ */
#घोषणा INSN_NOP		0x40000009
#घोषणा INSN_SIZE(insn)		(((insn & 0x80000000) == 0) ? 4 : 2)
#घोषणा IS_SETHI(insn)		((insn & 0xfe000000) == 0x46000000)
#घोषणा ENDIAN_CONVERT(insn)	(insn)
#पूर्ण_अगर

बाह्य व्योम _ftrace_caller(अचिन्हित दीर्घ parent_ip);
अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण
काष्ठा dyn_arch_ftrace अणु
पूर्ण;

#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#पूर्ण_अगर /* __ASM_NDS32_FTRACE_H */
