<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPARC_PERF_EVENT_H
#घोषणा __ASM_SPARC_PERF_EVENT_H

#अगर_घोषित CONFIG_PERF_EVENTS
#समावेश <यंत्र/ptrace.h>

#घोषणा perf_arch_fetch_caller_regs(regs, ip)		\
करो अणु							\
	अचिन्हित दीर्घ _pstate, _asi, _pil, _i7, _fp;	\
	__यंत्र__ __अस्थिर__("rdpr %%pstate, %0\n\t"	\
			     "rd %%asi, %1\n\t"		\
			     "rdpr %%pil, %2\n\t"	\
			     "mov %%i7, %3\n\t"		\
			     "mov %%i6, %4\n\t"		\
			     : "=r" (_pstate),		\
			       "=r" (_asi),		\
			       "=r" (_pil),		\
			       "=r" (_i7),		\
			       "=r" (_fp));		\
	(regs)->tstate = (_pstate << 8) |		\
		(_asi << 24) | (_pil << 20);		\
	(regs)->tpc = (ip);				\
	(regs)->tnpc = (regs)->tpc + 4;			\
	(regs)->u_regs[UREG_I6] = _fp;			\
	(regs)->u_regs[UREG_I7] = _i7;			\
पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
