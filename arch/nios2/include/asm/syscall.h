<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright Altera Corporation (C) <2014>. All rights reserved
 */

#अगर_अघोषित __ASM_NIOS2_SYSCALL_H__
#घोषणा __ASM_NIOS2_SYSCALL_H__

#समावेश <uapi/linux/audit.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>

अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->r2;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				काष्ठा pt_regs *regs)
अणु
	regs->r2 = regs->orig_r2;
	regs->r7 = regs->orig_r7;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				काष्ठा pt_regs *regs)
अणु
	वापस regs->r7 ? regs->r2 : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs)
अणु
	वापस regs->r2;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, पूर्णांक error, दीर्घ val)
अणु
	अगर (error) अणु
		/* error < 0, but nios2 uses > 0 वापस value */
		regs->r2 = -error;
		regs->r7 = 1;
	पूर्ण अन्यथा अणु
		regs->r2 = val;
		regs->r7 = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, अचिन्हित दीर्घ *args)
अणु
	*args++ = regs->r4;
	*args++ = regs->r5;
	*args++ = regs->r6;
	*args++ = regs->r7;
	*args++ = regs->r8;
	*args   = regs->r9;
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->r4 = *args++;
	regs->r5 = *args++;
	regs->r6 = *args++;
	regs->r7 = *args++;
	regs->r8 = *args++;
	regs->r9 = *args;
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_NIOS2;
पूर्ण

#पूर्ण_अगर
