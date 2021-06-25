<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_SYSCALL_H
#घोषणा _ASM_ARC_SYSCALL_H  1

#समावेश <uapi/linux/audit.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/ptrace.h>		/* in_syscall() */

अटल अंतरभूत दीर्घ
syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs) && in_syscall(regs))
		वापस regs->r8;
	अन्यथा
		वापस -1;
पूर्ण

अटल अंतरभूत व्योम
syscall_rollback(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	regs->r0 = regs->orig_r0;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_error(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	/* 0 अगर syscall succeeded, otherwise -Errorcode */
	वापस IS_ERR_VALUE(regs->r0) ? regs->r0 : 0;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->r0;
पूर्ण

अटल अंतरभूत व्योम
syscall_set_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			 पूर्णांक error, दीर्घ val)
अणु
	regs->r0 = (दीर्घ) error ?: val;
पूर्ण

/*
 * @i:      argument index [0,5]
 * @n:      number of arguments; n+i must be [1,6].
 */
अटल अंतरभूत व्योम
syscall_get_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ *inside_ptregs = &(regs->r0);
	अचिन्हित पूर्णांक n = 6;
	अचिन्हित पूर्णांक i = 0;

	जबतक (n--) अणु
		args[i++] = (*inside_ptregs);
		inside_ptregs--;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस IS_ENABLED(CONFIG_ISA_ARCOMPACT)
		? (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)
			? AUDIT_ARCH_ARCOMPACTBE : AUDIT_ARCH_ARCOMPACT)
		: (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)
			? AUDIT_ARCH_ARCV2BE : AUDIT_ARCH_ARCV2);
पूर्ण

#पूर्ण_अगर
