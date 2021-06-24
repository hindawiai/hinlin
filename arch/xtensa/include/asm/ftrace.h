<शैली गुरु>
/*
 * arch/xtensa/include/यंत्र/ftrace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2013 Tensilica Inc.
 */
#अगर_अघोषित _XTENSA_FTRACE_H
#घोषणा _XTENSA_FTRACE_H

#समावेश <यंत्र/processor.h>

#अगर_अघोषित __ASSEMBLY__
#घोषणा ftrace_वापस_address0 (अणु अचिन्हित दीर्घ a0, a1; \
		__यंत्र__ __अस्थिर__ ( \
			"mov %0, a0\n" \
			"mov %1, a1\n" \
			: "=r"(a0), "=r"(a1)); \
		MAKE_PC_FROM_RA(a0, a1); पूर्ण)

#अगर_घोषित CONFIG_FRAME_POINTER
बाह्य अचिन्हित दीर्घ वापस_address(अचिन्हित level);
#घोषणा ftrace_वापस_address(n) वापस_address(n)
#पूर्ण_अगर
#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा MCOUNT_ADDR ((अचिन्हित दीर्घ)(_mcount))
#घोषणा MCOUNT_INSN_SIZE 3

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम _mcount(व्योम);
#घोषणा mcount _mcount
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#पूर्ण_अगर /* _XTENSA_FTRACE_H */
