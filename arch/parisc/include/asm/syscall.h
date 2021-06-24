<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* syscall.h */

#अगर_अघोषित _ASM_PARISC_SYSCALL_H_
#घोषणा _ASM_PARISC_SYSCALL_H_

#समावेश <uapi/linux/audit.h>
#समावेश <linux/compat.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा NR_syscalls (__NR_Linux_syscalls)

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *tsk,
				  काष्ठा pt_regs *regs)
अणु
	वापस regs->gr[20];
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *tsk,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	args[5] = regs->gr[21];
	args[4] = regs->gr[22];
	args[3] = regs->gr[23];
	args[2] = regs->gr[24];
	args[1] = regs->gr[25];
	args[0] = regs->gr[26];
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->gr[28];
	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
						काष्ठा pt_regs *regs)
अणु
	वापस regs->gr[28];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->gr[28] = error ? error : val;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* करो nothing */
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक arch = AUDIT_ARCH_PARISC;
#अगर_घोषित CONFIG_64BIT
	अगर (!__is_compat_task(task))
		arch = AUDIT_ARCH_PARISC64;
#पूर्ण_अगर
	वापस arch;
पूर्ण
#पूर्ण_अगर /*_ASM_PARISC_SYSCALL_H_*/
