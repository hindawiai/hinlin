<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARM64_ASM_SIGNAL_H
#घोषणा __ARM64_ASM_SIGNAL_H

#समावेश <यंत्र/memory.h>
#समावेश <uapi/यंत्र/संकेत.स>
#समावेश <uapi/यंत्र/siginfo.h>

अटल अंतरभूत व्योम __user *arch_untagged_si_addr(व्योम __user *addr,
						 अचिन्हित दीर्घ sig,
						 अचिन्हित दीर्घ si_code)
अणु
	/*
	 * For historical reasons, all bits of the fault address are exposed as
	 * address bits क्रम watchpoपूर्णांक exceptions. New architectures should
	 * handle the tag bits consistently.
	 */
	अगर (sig == SIGTRAP && si_code == TRAP_BRKPT)
		वापस addr;

	वापस untagged_addr(addr);
पूर्ण
#घोषणा arch_untagged_si_addr arch_untagged_si_addr

#पूर्ण_अगर
