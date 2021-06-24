<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPARC_SYSCALL_H
#घोषणा __ASM_SPARC_SYSCALL_H

#समावेश <uapi/linux/audit.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/thपढ़ो_info.h>

/*
 * The syscall table always contains 32 bit poपूर्णांकers since we know that the
 * address of the function to be called is (way) below 4GB.  So the "int"
 * type here is what we want [need] क्रम both 32 bit and 64 bit प्रणालीs.
 */
बाह्य स्थिर अचिन्हित पूर्णांक sys_call_table[];

/* The प्रणाली call number is given by the user in %g1 */
अटल अंतरभूत दीर्घ syscall_get_nr(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	पूर्णांक syscall_p = pt_regs_is_syscall(regs);

	वापस (syscall_p ? regs->u_regs[UREG_G1] : -1L);
पूर्ण

अटल अंतरभूत व्योम syscall_rollback(काष्ठा task_काष्ठा *task,
				    काष्ठा pt_regs *regs)
अणु
	/* XXX This needs some thought.  On Sparc we करोn't
	 * XXX save away the original %o0 value somewhere.
	 * XXX Instead we hold it in रेजिस्टर %l5 at the top
	 * XXX level trap frame and pass this करोwn to the संकेत
	 * XXX dispatch code which is the only place that value
	 * XXX ever was needed.
	 */
पूर्ण

#अगर_घोषित CONFIG_SPARC32
अटल अंतरभूत bool syscall_has_error(काष्ठा pt_regs *regs)
अणु
	वापस (regs->psr & PSR_C) ? true : false;
पूर्ण
अटल अंतरभूत व्योम syscall_set_error(काष्ठा pt_regs *regs)
अणु
	regs->psr |= PSR_C;
पूर्ण
अटल अंतरभूत व्योम syscall_clear_error(काष्ठा pt_regs *regs)
अणु
	regs->psr &= ~PSR_C;
पूर्ण
#अन्यथा
अटल अंतरभूत bool syscall_has_error(काष्ठा pt_regs *regs)
अणु
	वापस (regs->tstate & (TSTATE_XCARRY | TSTATE_ICARRY)) ? true : false;
पूर्ण
अटल अंतरभूत व्योम syscall_set_error(काष्ठा pt_regs *regs)
अणु
	regs->tstate |= (TSTATE_XCARRY | TSTATE_ICARRY);
पूर्ण
अटल अंतरभूत व्योम syscall_clear_error(काष्ठा pt_regs *regs)
अणु
	regs->tstate &= ~(TSTATE_XCARRY | TSTATE_ICARRY);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत दीर्घ syscall_get_error(काष्ठा task_काष्ठा *task,
				     काष्ठा pt_regs *regs)
अणु
	दीर्घ val = regs->u_regs[UREG_I0];

	वापस (syscall_has_error(regs) ? -val : 0);
पूर्ण

अटल अंतरभूत दीर्घ syscall_get_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs)
अणु
	दीर्घ val = regs->u_regs[UREG_I0];

	वापस val;
पूर्ण

अटल अंतरभूत व्योम syscall_set_वापस_value(काष्ठा task_काष्ठा *task,
					    काष्ठा pt_regs *regs,
					    पूर्णांक error, दीर्घ val)
अणु
	अगर (error) अणु
		syscall_set_error(regs);
		regs->u_regs[UREG_I0] = -error;
	पूर्ण अन्यथा अणु
		syscall_clear_error(regs);
		regs->u_regs[UREG_I0] = val;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_get_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ *args)
अणु
	पूर्णांक zero_extend = 0;
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक n = 6;

#अगर_घोषित CONFIG_SPARC64
	अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		zero_extend = 1;
#पूर्ण_अगर

	क्रम (j = 0; j < n; j++) अणु
		अचिन्हित दीर्घ val = regs->u_regs[UREG_I0 + j];

		अगर (zero_extend)
			args[j] = (u32) val;
		अन्यथा
			args[j] = val;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम syscall_set_arguments(काष्ठा task_काष्ठा *task,
					 काष्ठा pt_regs *regs,
					 स्थिर अचिन्हित दीर्घ *args)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		regs->u_regs[UREG_I0 + i] = args[i];
पूर्ण

अटल अंतरभूत पूर्णांक syscall_get_arch(काष्ठा task_काष्ठा *task)
अणु
#अगर defined(CONFIG_SPARC64) && defined(CONFIG_COMPAT)
	वापस test_tsk_thपढ़ो_flag(task, TIF_32BIT)
		? AUDIT_ARCH_SPARC : AUDIT_ARCH_SPARC64;
#या_अगर defined(CONFIG_SPARC64)
	वापस AUDIT_ARCH_SPARC64;
#अन्यथा
	वापस AUDIT_ARCH_SPARC;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_SPARC_SYSCALL_H */
