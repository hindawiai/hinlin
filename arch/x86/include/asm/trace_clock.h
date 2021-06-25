<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TRACE_CLOCK_H
#घोषणा _ASM_X86_TRACE_CLOCK_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_X86_TSC

बाह्य u64 notrace trace_घड़ी_x86_tsc(व्योम);

# define ARCH_TRACE_CLOCKS \
	अणु trace_घड़ी_x86_tsc,	"x86-tsc",	.in_ns = 0 पूर्ण,

#अन्यथा /* !CONFIG_X86_TSC */

#घोषणा ARCH_TRACE_CLOCKS

#पूर्ण_अगर

#पूर्ण_अगर  /* _ASM_X86_TRACE_CLOCK_H */
