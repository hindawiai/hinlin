<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Syscall support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_HEXAGON_SYSCALL_H
#घोषणा _ASM_HEXAGON_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>

प्रकार दीर्घ (*syscall_fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
	अचिन्हित दीर्घ, अचिन्हित दीर्घ,
	अचिन्हित दीर्घ, अचिन्हित दीर्घ);

#समावेश <यंत्र-generic/syscalls.h>

बाह्य व्योम *sys_call_table[];

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस regs->r06;
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	स_नकल(args, &(&regs->r00)[0], 6 * माप(args[0]));
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	वापस IS_ERR_VALUE(regs->r00) ? regs->r00 : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->r00;
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_HEXAGON;
पूर्ण

#पूर्ण_अगर
