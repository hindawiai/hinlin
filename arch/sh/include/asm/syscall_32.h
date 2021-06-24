<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SYSCALL_32_H
#घोषणा __ASM_SH_SYSCALL_32_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>

/* The प्रणाली call number is given by the user in R3 */
अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस (regs->tra >= 0) ? regs->regs[3] : -1L;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/*
	 * XXX: This needs some thought. On SH we करोn't
	 * save away the original r0 value anywhere.
	 */
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	वापस IS_ERR_VALUE(regs->regs[0]) ? regs->regs[0] : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[0];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->regs[0] = (दीर्घ) error ?: val;
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु

	/* Argument pattern is: R4, R5, R6, R7, R0, R1 */
	args[5] = regs->regs[1];
	args[4] = regs->regs[0];
	args[3] = regs->regs[7];
	args[2] = regs->regs[6];
	args[1] = regs->regs[5];
	args[0] = regs->regs[4];
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->regs[1] = args[5];
	regs->regs[0] = args[4];
	regs->regs[7] = args[3];
	regs->regs[6] = args[2];
	regs->regs[5] = args[1];
	regs->regs[4] = args[0];
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक arch = AUDIT_ARCH_SH;

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	arch |= __AUDIT_ARCH_LE;
#पूर्ण_अगर
	वापस arch;
पूर्ण
#पूर्ण_अगर /* __ASM_SH_SYSCALL_32_H */
