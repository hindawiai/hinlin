<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2007 Tensilica Inc.
 * Copyright (C) 2018 Cadence Design Systems Inc.
 */

#अगर_अघोषित _ASM_SYSCALL_H
#घोषणा _ASM_SYSCALL_H

#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <uapi/linux/audit.h>

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_XTENSA;
पूर्ण

प्रकार व्योम (*syscall_t)(व्योम);
बाह्य syscall_t sys_call_table[];

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस regs->syscall;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* Do nothing. */
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	/* 0 अगर syscall succeeded, otherwise -Errorcode */
	वापस IS_ERR_VALUE(regs->areg[2]) ? regs->areg[2] : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->areg[2];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->areg[2] = (दीर्घ) error ? error : val;
पूर्ण

#घोषणा SYSCALL_MAX_ARGS 6
#घोषणा XTENSA_SYSCALL_ARGUMENT_REGS अणु6, 3, 4, 5, 8, 9पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	अटल स्थिर अचिन्हित पूर्णांक reg[] = XTENSA_SYSCALL_ARGUMENT_REGS;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 6; ++i)
		args[i] = regs->areg[reg[i]];
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	अटल स्थिर अचिन्हित पूर्णांक reg[] = XTENSA_SYSCALL_ARGUMENT_REGS;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 6; ++i)
		regs->areg[reg[i]] = args[i];
पूर्ण

यंत्रlinkage दीर्घ xtensa_rt_sigवापस(व्योम);
यंत्रlinkage दीर्घ xtensa_shmat(पूर्णांक, अक्षर __user *, पूर्णांक);
यंत्रlinkage दीर्घ xtensa_fadvise64_64(पूर्णांक, पूर्णांक,
				    अचिन्हित दीर्घ दीर्घ, अचिन्हित दीर्घ दीर्घ);

#पूर्ण_अगर
