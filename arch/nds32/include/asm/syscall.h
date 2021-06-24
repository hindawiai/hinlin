<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2008-2009 Red Hat, Inc.  All rights reserved.
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASM_NDS32_SYSCALL_H
#घोषणा _ASM_NDS32_SYSCALL_H	1

#समावेश <uapi/linux/audit.h>
#समावेश <linux/err.h>
काष्ठा task_काष्ठा;
काष्ठा pt_regs;

/**
 * syscall_get_nr - find what प्रणाली call a task is executing
 * @task:	task of पूर्णांकerest, must be blocked
 * @regs:	task_pt_regs() of @task
 *
 * If @task is executing a प्रणाली call or is at प्रणाली call
 * tracing about to attempt one, वापसs the प्रणाली call number.
 * If @task is not executing a प्रणाली call, i.e. it's blocked
 * inside the kernel क्रम a fault or संकेत, वापसs -1.
 *
 * Note this वापसs पूर्णांक even on 64-bit machines.  Only 32 bits of
 * प्रणाली call number can be meaningful.  If the actual arch value
 * is 64 bits, this truncates to 32 bits so 0xffffffff means -1.
 *
 * It's only valid to call this when @task is known to be blocked.
 */
अटल अंतरभूत पूर्णांक
syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->syscallno;
पूर्ण

/**
 * syscall_rollback - roll back रेजिस्टरs after an पातed प्रणाली call
 * @task:	task of पूर्णांकerest, must be in प्रणाली call निकास tracing
 * @regs:	task_pt_regs() of @task
 *
 * It's only valid to call this when @task is stopped क्रम प्रणाली
 * call निकास tracing (due to TIF_SYSCALL_TRACE or TIF_SYSCALL_AUDIT),
 * after tracehook_report_syscall_entry() वापसed nonzero to prevent
 * the प्रणाली call from taking place.
 *
 * This rolls back the रेजिस्टर state in @regs so it's as अगर the
 * प्रणाली call inकाष्ठाion was a no-op.  The रेजिस्टरs containing
 * the प्रणाली call number and arguments are as they were beक्रमe the
 * प्रणाली call inकाष्ठाion.  This may not be the same as what the
 * रेजिस्टर state looked like at प्रणाली call entry tracing.
 */
अटल अंतरभूत व्योम
syscall_rollback(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	regs->uregs[0] = regs->orig_r0;
पूर्ण

/**
 * syscall_get_error - check result of traced प्रणाली call
 * @task:	task of पूर्णांकerest, must be blocked
 * @regs:	task_pt_regs() of @task
 *
 * Returns 0 अगर the प्रणाली call succeeded, or -ERRORCODE अगर it failed.
 *
 * It's only valid to call this when @task is stopped क्रम tracing on निकास
 * from a प्रणाली call, due to %TIF_SYSCALL_TRACE or %TIF_SYSCALL_AUDIT.
 */
अटल अंतरभूत दीर्घ
syscall_get_error(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->uregs[0];
	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

/**
 * syscall_get_वापस_value - get the वापस value of a traced प्रणाली call
 * @task:	task of पूर्णांकerest, must be blocked
 * @regs:	task_pt_regs() of @task
 *
 * Returns the वापस value of the successful प्रणाली call.
 * This value is meaningless अगर syscall_get_error() वापसed nonzero.
 *
 * It's only valid to call this when @task is stopped क्रम tracing on निकास
 * from a प्रणाली call, due to %TIF_SYSCALL_TRACE or %TIF_SYSCALL_AUDIT.
 */
अटल अंतरभूत दीर्घ
syscall_get_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->uregs[0];
पूर्ण

/**
 * syscall_set_वापस_value - change the वापस value of a traced प्रणाली call
 * @task:	task of पूर्णांकerest, must be blocked
 * @regs:	task_pt_regs() of @task
 * @error:	negative error code, or zero to indicate success
 * @val:	user वापस value अगर @error is zero
 *
 * This changes the results of the प्रणाली call that user mode will see.
 * If @error is zero, the user sees a successful प्रणाली call with a
 * वापस value of @val.  If @error is nonzero, it's a negated त्रुटि_सं
 * code; the user sees a failed प्रणाली call with this त्रुटि_सं code.
 *
 * It's only valid to call this when @task is stopped क्रम tracing on निकास
 * from a प्रणाली call, due to %TIF_SYSCALL_TRACE or %TIF_SYSCALL_AUDIT.
 */
अटल अंतरभूत व्योम
syscall_set_वापस_value(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			 पूर्णांक error, दीर्घ val)
अणु
	regs->uregs[0] = (दीर्घ)error ? error : val;
पूर्ण

/**
 * syscall_get_arguments - extract प्रणाली call parameter values
 * @task:	task of पूर्णांकerest, must be blocked
 * @regs:	task_pt_regs() of @task
 * @args:	array filled with argument values
 *
 * Fetches 6 arguments to the प्रणाली call (from 0 through 5). The first
 * argument is stored in @args[0], and so on.
 *
 * It's only valid to call this when @task is stopped क्रम tracing on
 * entry to a प्रणाली call, due to %TIF_SYSCALL_TRACE or %TIF_SYSCALL_AUDIT.
 */
#घोषणा SYSCALL_MAX_ARGS 6
अटल अंतरभूत व्योम
syscall_get_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ *args)
अणु
	args[0] = regs->orig_r0;
	args++;
	स_नकल(args, &regs->uregs[0] + 1, 5 * माप(args[0]));
पूर्ण

/**
 * syscall_set_arguments - change प्रणाली call parameter value
 * @task:	task of पूर्णांकerest, must be in प्रणाली call entry tracing
 * @regs:	task_pt_regs() of @task
 * @args:	array of argument values to store
 *
 * Changes 6 arguments to the प्रणाली call. The first argument माला_लो value
 * @args[0], and so on.
 *
 * It's only valid to call this when @task is stopped क्रम tracing on
 * entry to a प्रणाली call, due to %TIF_SYSCALL_TRACE or %TIF_SYSCALL_AUDIT.
 */
अटल अंतरभूत व्योम
syscall_set_arguments(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		      स्थिर अचिन्हित दीर्घ *args)
अणु
	regs->orig_r0 = args[0];
	args++;

	स_नकल(&regs->uregs[0] + 1, args, 5 * माप(args[0]));
पूर्ण

अटल अंतरभूत पूर्णांक
syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)
		? AUDIT_ARCH_NDS32BE : AUDIT_ARCH_NDS32;
पूर्ण

#पूर्ण_अगर /* _ASM_NDS32_SYSCALL_H */
