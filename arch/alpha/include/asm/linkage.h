<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#घोषणा cond_syscall(x)  यंत्र(".weak\t" #x "\n" #x " = sys_ni_syscall")
#घोषणा SYSCALL_ALIAS(alias, name)					\
	यंत्र ( #alias " = " #name "\n\t.globl " #alias)

#पूर्ण_अगर
