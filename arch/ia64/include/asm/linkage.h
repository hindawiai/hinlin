<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा यंत्रlinkage CPP_ASMLINKAGE __attribute__((syscall_linkage))

#अन्यथा

#समावेश <यंत्र/यंत्रmacro.h>

#पूर्ण_अगर

#घोषणा cond_syscall(x) यंत्र(".weak\t" #x "#\n" #x "#\t=\tsys_ni_syscall#")
#घोषणा SYSCALL_ALIAS(alias, name)					\
	यंत्र ( #alias "# = " #name "#\n\t.globl " #alias "#")

#पूर्ण_अगर
