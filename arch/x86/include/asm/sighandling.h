<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SIGHANDLING_H
#घोषणा _ASM_X86_SIGHANDLING_H

#समावेश <linux/compiler.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/संकेत.स>

#समावेश <यंत्र/processor-flags.h>

#घोषणा FIX_EFLAGS	(X86_EFLAGS_AC | X86_EFLAGS_OF | \
			 X86_EFLAGS_DF | X86_EFLAGS_TF | X86_EFLAGS_SF | \
			 X86_EFLAGS_ZF | X86_EFLAGS_AF | X86_EFLAGS_PF | \
			 X86_EFLAGS_CF | X86_EFLAGS_RF)

व्योम संकेत_fault(काष्ठा pt_regs *regs, व्योम __user *frame, अक्षर *where);

#पूर्ण_अगर /* _ASM_X86_SIGHANDLING_H */
