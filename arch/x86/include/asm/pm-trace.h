<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PM_TRACE_H
#घोषणा _ASM_X86_PM_TRACE_H

#समावेश <यंत्र/यंत्र.h>

#घोषणा TRACE_RESUME(user)					\
करो अणु								\
	अगर (pm_trace_enabled) अणु					\
		स्थिर व्योम *tracedata;				\
		यंत्र अस्थिर(_ASM_MOV " $1f,%0\n"		\
			     ".section .tracedata,\"a\"\n"	\
			     "1:\t.word %c1\n\t"		\
			     _ASM_PTR " %c2\n"			\
			     ".previous"			\
			     :"=r" (tracedata)			\
			     : "i" (__LINE__), "i" (__खाता__));	\
		generate_pm_trace(tracedata, user);		\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा TRACE_SUSPEND(user)	TRACE_RESUME(user)

#पूर्ण_अगर /* _ASM_X86_PM_TRACE_H */
