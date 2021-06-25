<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Access to user प्रणाली call parameters and results
 *
 * See यंत्र-generic/syscall.h क्रम function descriptions.
 *
 * Copyright (C) 2015 Mickaथ+l Salaथञn <mic@digikod.net>
 */

#अगर_अघोषित __UM_SYSCALL_GENERIC_H
#घोषणा __UM_SYSCALL_GENERIC_H

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <sysdep/ptrace.h>

अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु

	वापस PT_REGS_SYSCALL_NR(regs);
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* करो nothing */
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	स्थिर दीर्घ error = regs_वापस_value(regs);

	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs_वापस_value(regs);
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	PT_REGS_SET_SYSCALL_RETURN(regs, (दीर्घ) error ?: val);
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	स्थिर काष्ठा uml_pt_regs *r = &regs->regs;

	*args++ = UPT_SYSCALL_ARG1(r);
	*args++ = UPT_SYSCALL_ARG2(r);
	*args++ = UPT_SYSCALL_ARG3(r);
	*args++ = UPT_SYSCALL_ARG4(r);
	*args++ = UPT_SYSCALL_ARG5(r);
	*args   = UPT_SYSCALL_ARG6(r);
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	काष्ठा uml_pt_regs *r = &regs->regs;

	UPT_SYSCALL_ARG1(r) = *args++;
	UPT_SYSCALL_ARG2(r) = *args++;
	UPT_SYSCALL_ARG3(r) = *args++;
	UPT_SYSCALL_ARG4(r) = *args++;
	UPT_SYSCALL_ARG5(r) = *args++;
	UPT_SYSCALL_ARG6(r) = *args;
पूर्ण

/* See arch/x86/um/यंत्र/syscall.h क्रम syscall_get_arch() definition. */

#पूर्ण_अगर	/* __UM_SYSCALL_GENERIC_H */
