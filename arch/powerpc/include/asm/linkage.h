<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_LINKAGE_H
#घोषणा _ASM_POWERPC_LINKAGE_H

#समावेश <यंत्र/types.h>

#अगर_घोषित PPC64_ELF_ABI_v1
#घोषणा cond_syscall(x) \
	यंत्र ("\t.weak " #x "\n\t.set " #x ", sys_ni_syscall\n"		\
	     "\t.weak ." #x "\n\t.set ." #x ", .sys_ni_syscall\n")
#घोषणा SYSCALL_ALIAS(alias, name)					\
	यंत्र ("\t.globl " #alias "\n\t.set " #alias ", " #name "\n"	\
	     "\t.globl ." #alias "\n\t.set ." #alias ", ." #name)
#पूर्ण_अगर

#पूर्ण_अगर	/* _ASM_POWERPC_LINKAGE_H */
