<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MICROBLAZE_SYSCALL_H
#घोषणा __ASM_MICROBLAZE_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>

/* The प्रणाली call number is given by the user in R12 */
अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	वापस regs->r12;
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* TODO.  */
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	वापस IS_ERR_VALUE(regs->r3) ? regs->r3 : 0;
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	वापस regs->r3;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (error)
		regs->r3 = -error;
	अन्यथा
		regs->r3 = val;
पूर्ण

अटल अंतरभूत microblaze_reg_t microblaze_get_syscall_arg(काष्ठा pt_regs *regs,
							  अचिन्हित पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 5: वापस regs->r10;
	हाल 4: वापस regs->r9;
	हाल 3: वापस regs->r8;
	हाल 2: वापस regs->r7;
	हाल 1: वापस regs->r6;
	हाल 0: वापस regs->r5;
	शेष:
		BUG();
	पूर्ण
	वापस ~0;
पूर्ण

अटल अंतरभूत व्योम microblaze_set_syscall_arg(काष्ठा pt_regs *regs,
					      अचिन्हित पूर्णांक n,
					      अचिन्हित दीर्घ val)
अणु
	चयन (n) अणु
	हाल 5:
		regs->r10 = val;
	हाल 4:
		regs->r9 = val;
	हाल 3:
		regs->r8 = val;
	हाल 2:
		regs->r7 = val;
	हाल 1:
		regs->r6 = val;
	हाल 0:
		regs->r5 = val;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक n = 6;

	जबतक (n--)
		*args++ = microblaze_get_syscall_arg(regs, i++);
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक n = 6;

	जबतक (n--)
		microblaze_set_syscall_arg(regs, i++, *args++);
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs);

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
	वापस AUDIT_ARCH_MICROBLAZE;
पूर्ण
#पूर्ण_अगर /* __ASM_MICROBLAZE_SYSCALL_H */
