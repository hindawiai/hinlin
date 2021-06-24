<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Copyright (C) 2009 DSLab, Lanzhou University, China
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#अगर_अघोषित _ASM_MIPS_FTRACE_H
#घोषणा _ASM_MIPS_FTRACE_H

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा MCOUNT_ADDR ((अचिन्हित दीर्घ)(_mcount))
#घोषणा MCOUNT_INSN_SIZE 4		/* माप mcount call */

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम _mcount(व्योम);
#घोषणा mcount _mcount

#घोषणा safe_load(load, src, dst, error)		\
करो अणु							\
	यंत्र अस्थिर (					\
		"1: " load " %[tmp_dst], 0(%[tmp_src])\n"	\
		"   li %[tmp_err], 0\n"			\
		"2: .insn\n"				\
							\
		".section .fixup, \"ax\"\n"		\
		"3: li %[tmp_err], 1\n"			\
		"   j 2b\n"				\
		".previous\n"				\
							\
		".section\t__ex_table,\"a\"\n\t"	\
		STR(PTR) "\t1b, 3b\n\t"			\
		".previous\n"				\
							\
		: [पंचांगp_dst] "=&r" (dst), [पंचांगp_err] "=r" (error)\
		: [पंचांगp_src] "r" (src)			\
		: "memory"				\
	);						\
पूर्ण जबतक (0)

#घोषणा safe_store(store, src, dst, error)	\
करो अणु						\
	यंत्र अस्थिर (				\
		"1: " store " %[tmp_src], 0(%[tmp_dst])\n"\
		"   li %[tmp_err], 0\n"		\
		"2: .insn\n"			\
						\
		".section .fixup, \"ax\"\n"	\
		"3: li %[tmp_err], 1\n"		\
		"   j 2b\n"			\
		".previous\n"			\
						\
		".section\t__ex_table,\"a\"\n\t"\
		STR(PTR) "\t1b, 3b\n\t"		\
		".previous\n"			\
						\
		: [पंचांगp_err] "=r" (error)	\
		: [पंचांगp_dst] "r" (dst), [पंचांगp_src] "r" (src)\
		: "memory"			\
	);					\
पूर्ण जबतक (0)

#घोषणा safe_load_code(dst, src, error) \
	safe_load(STR(lw), src, dst, error)
#घोषणा safe_store_code(src, dst, error) \
	safe_store(STR(sw), src, dst, error)

#घोषणा safe_load_stack(dst, src, error) \
	safe_load(STR(PTR_L), src, dst, error)

#घोषणा safe_store_stack(src, dst, error) \
	safe_store(STR(PTR_S), src, dst, error)


#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;

#पूर्ण_अगर /*  CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */
#पूर्ण_अगर /* _ASM_MIPS_FTRACE_H */
