<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_SYSCALL_H
#घोषणा __ASM_SYSCALL_H

#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <abi/regdef.h>
#समावेश <uapi/linux/audit.h>

बाह्य व्योम *sys_call_table[];

अटल अंतरभूत पूर्णांक
syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs_syscallid(regs);
पूर्ण

अटल अंतरभूत व्योम
syscall_set_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
	       पूर्णांक sysno)
अणु
	regs_syscallid(regs) = sysno;
पूर्ण

अटल अंतरभूत व्योम
syscall_rollback(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	regs->a0 = regs->orig_a0;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_error(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->a0;

	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ
syscall_get_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->a0;
पूर्ण

अटल अंतरभूत व्योम
syscall_set_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		पूर्णांक error, दीर्घ val)
अणु
	regs->a0 = (दीर्घ) error ?: val;
पूर्ण

अटल अंतरभूत व्योम
syscall_get_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ *args)
अणु
	args[0] = regs->orig_a0;
	args++;
	स_नकल(args, &regs->a1, 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम
syscall_set_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->orig_a0 = args[0];
	args++;
	स_नकल(&regs->a1, args, 5 * माप(regs->a1));
पूर्ण

अटल अंतरभूत पूर्णांक
syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_CSKY;
पूर्ण

#पूर्ण_अगर	/* __ASM_SYSCALL_H */
