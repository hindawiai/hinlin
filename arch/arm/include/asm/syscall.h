<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Access to user प्रणाली call parameters and results
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 */

#अगर_अघोषित _ASM_ARM_SYSCALL_H
#घोषणा _ASM_ARM_SYSCALL_H

#समावेश <uapi/linux/audit.h> /* क्रम AUDIT_ARCH_* */
#समावेश <linux/elf.h> /* क्रम ELF_EM */
#समावेश <linux/err.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/unistd.h>

#घोषणा NR_syscalls (__NR_syscalls)

बाह्य स्थिर अचिन्हित दीर्घ sys_call_table[];

अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task,
				 काष्ठा pt_regs *regs)
अणु
	वापस task_thपढ़ो_info(task)->syscall;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	regs->ARM_r0 = regs->ARM_ORIG_r0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->ARM_r0;
	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->ARM_r0;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->ARM_r0 = (दीर्घ) error ? error : val;
पूर्ण

#घोषणा SYSCALL_MAX_ARGS 7

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	args[0] = regs->ARM_ORIG_r0;
	args++;

	स_नकल(args, &regs->ARM_r0 + 1, 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->ARM_ORIG_r0 = args[0];
	args++;

	स_नकल(&regs->ARM_r0 + 1, args, 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	/* ARM tasks करोn't change audit architectures on the fly. */
	वापस AUDIT_ARCH_ARM;
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_SYSCALL_H */
