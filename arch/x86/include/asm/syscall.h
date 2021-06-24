<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Access to user प्रणाली call parameters and results
 *
 * Copyright (C) 2008-2009 Red Hat, Inc.  All rights reserved.
 *
 * See यंत्र-generic/syscall.h क्रम descriptions of what we must करो here.
 */

#अगर_अघोषित _ASM_X86_SYSCALL_H
#घोषणा _ASM_X86_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/thपढ़ो_info.h>	/* क्रम TS_COMPAT */
#समावेश <यंत्र/unistd.h>

प्रकार दीर्घ (*sys_call_ptr_t)(स्थिर काष्ठा pt_regs *);
बाह्य स्थिर sys_call_ptr_t sys_call_table[];

#अगर defined(CONFIG_X86_32)
#घोषणा ia32_sys_call_table sys_call_table
#पूर्ण_अगर

#अगर defined(CONFIG_IA32_EMULATION)
बाह्य स्थिर sys_call_ptr_t ia32_sys_call_table[];
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_X32_ABI
बाह्य स्थिर sys_call_ptr_t x32_sys_call_table[];
#पूर्ण_अगर

/*
 * Only the low 32 bits of orig_ax are meaningful, so we वापस पूर्णांक.
 * This importantly ignores the high bits on 64-bit, so comparisons
 * sign-extend the low 32 bits.
 */
अटल अंतरभूत पूर्णांक syscall_get_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस regs->orig_ax;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	regs->ax = regs->orig_ax;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ error = regs->ax;
#अगर_घोषित CONFIG_IA32_EMULATION
	/*
	 * TS_COMPAT is set क्रम 32-bit syscall entries and then
	 * reमुख्यs set until we वापस to user mode.
	 */
	अगर (task->thपढ़ो_info.status & (TS_COMPAT|TS_I386_REGS_POKED))
		/*
		 * Sign-extend the value so (पूर्णांक)-EFOO becomes (दीर्घ)-EFOO
		 * and will match correctly in comparisons.
		 */
		error = (दीर्घ) (पूर्णांक) error;
#पूर्ण_अगर
	वापस IS_ERR_VALUE(error) ? error : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->ax;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	regs->ax = (दीर्घ) error ?: val;
पूर्ण

#अगर_घोषित CONFIG_X86_32

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	स_नकल(args, &regs->bx, 6 * माप(args[0]));
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित पूर्णांक i, अचिन्हित पूर्णांक n,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	BUG_ON(i + n > 6);
	स_नकल(&regs->bx + i, args, n * माप(args[0]));
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_I386;
पूर्ण

#अन्यथा	 /* CONFIG_X86_64 */

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
# अगरdef CONFIG_IA32_EMULATION
	अगर (task->thपढ़ो_info.status & TS_COMPAT) अणु
		*args++ = regs->bx;
		*args++ = regs->cx;
		*args++ = regs->dx;
		*args++ = regs->si;
		*args++ = regs->di;
		*args   = regs->bp;
	पूर्ण अन्यथा
# endअगर
	अणु
		*args++ = regs->di;
		*args++ = regs->si;
		*args++ = regs->dx;
		*args++ = regs->r10;
		*args++ = regs->r8;
		*args   = regs->r9;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
# अगरdef CONFIG_IA32_EMULATION
	अगर (task->thपढ़ो_info.status & TS_COMPAT) अणु
		regs->bx = *args++;
		regs->cx = *args++;
		regs->dx = *args++;
		regs->si = *args++;
		regs->di = *args++;
		regs->bp = *args;
	पूर्ण अन्यथा
# endअगर
	अणु
		regs->di = *args++;
		regs->si = *args++;
		regs->dx = *args++;
		regs->r10 = *args++;
		regs->r8 = *args++;
		regs->r9 = *args;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	/* x32 tasks should be considered AUDIT_ARCH_X86_64. */
	वापस (IS_ENABLED(CONFIG_IA32_EMULATION) &&
		task->thपढ़ो_info.status & TS_COMPAT)
		? AUDIT_ARCH_I386 : AUDIT_ARCH_X86_64;
पूर्ण

व्योम करो_syscall_64(अचिन्हित दीर्घ nr, काष्ठा pt_regs *regs);
व्योम करो_पूर्णांक80_syscall_32(काष्ठा pt_regs *regs);
दीर्घ करो_fast_syscall_32(काष्ठा pt_regs *regs);

#पूर्ण_अगर	/* CONFIG_X86_32 */

#पूर्ण_अगर	/* _ASM_X86_SYSCALL_H */
