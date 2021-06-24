<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Access to user प्रणाली call parameters and results
 *
 *  Copyright IBM Corp. 2008
 *  Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#अगर_अघोषित _ASM_SYSCALL_H
#घोषणा _ASM_SYSCALL_H	1

#समावेश <uapi/linux/audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>

बाह्य स्थिर sys_call_ptr_t sys_call_table[];
बाह्य स्थिर sys_call_ptr_t sys_call_table_emu[];

अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस test_pt_regs_flag(regs, PIF_SYSCALL) ?
		(regs->पूर्णांक_code & 0xffff) : -1;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	regs->gprs[2] = regs->orig_gpr2;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->gprs[2];
#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_31BIT)) अणु
		/*
		 * Sign-extend the value so (पूर्णांक)-EFOO becomes (दीर्घ)-EFOO
		 * and will match correctly in comparisons.
		 */
		error = (दीर्घ)(पूर्णांक)error;
	पूर्ण
#पूर्ण_अगर
	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->gprs[2];
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	set_pt_regs_flag(regs, PIF_SYSCALL_RET_SET);
	regs->gprs[2] = error ? error : val;
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ mask = -1UL;
	अचिन्हित पूर्णांक n = 6;

#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_31BIT))
		mask = 0xffffffff;
#पूर्ण_अगर
	जबतक (n-- > 0)
		अगर (n > 0)
			args[n] = regs->gprs[2 + n] & mask;

	args[0] = regs->orig_gpr2 & mask;
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	अचिन्हित पूर्णांक n = 6;

	जबतक (n-- > 0)
		अगर (n > 0)
			regs->gprs[2 + n] = args[n];
	regs->orig_gpr2 = args[0];
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_31BIT))
		वापस AUDIT_ARCH_S390;
#पूर्ण_अगर
	वापस AUDIT_ARCH_S390X;
पूर्ण

अटल अंतरभूत bool arch_syscall_is_vdso_sigवापस(काष्ठा pt_regs *regs)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर	/* _ASM_SYSCALL_H */
