<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Access to user प्रणाली call parameters and results
 *
 * Copyright (C) 2008 Intel Corp.  Shaohua Li <shaohua.li@पूर्णांकel.com>
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 */

#अगर_अघोषित _ASM_SYSCALL_H
#घोषणा _ASM_SYSCALL_H	1

#समावेश <uapi/linux/audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	अगर ((दीर्घ)regs->cr_अगरs < 0) /* Not a syscall */
		वापस -1;

	वापस regs->r15;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* करो nothing */
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	वापस regs->r10 == -1 ? -regs->r8:0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->r8;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (error) अणु
		/* error < 0, but ia64 uses > 0 वापस value */
		regs->r8 = -error;
		regs->r10 = -1;
	पूर्ण अन्यथा अणु
		regs->r8 = val;
		regs->r10 = 0;
	पूर्ण
पूर्ण

बाह्य व्योम ia64_syscall_get_set_arguments(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, अचिन्हित दीर्घ *args, पूर्णांक rw);
अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	ia64_syscall_get_set_arguments(task, regs, args, 0);
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	ia64_syscall_get_set_arguments(task, regs, args, 1);
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_IA64;
पूर्ण
#पूर्ण_अगर	/* _ASM_SYSCALL_H */
