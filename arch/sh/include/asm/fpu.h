<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FPU_H
#घोषणा __ASM_SH_FPU_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_SH_FPU
अटल अंतरभूत व्योम release_fpu(काष्ठा pt_regs *regs)
अणु
	regs->sr |= SR_FD;
पूर्ण

अटल अंतरभूत व्योम grab_fpu(काष्ठा pt_regs *regs)
अणु
	regs->sr &= ~SR_FD;
पूर्ण

बाह्य व्योम save_fpu(काष्ठा task_काष्ठा *__tsk);
बाह्य व्योम restore_fpu(काष्ठा task_काष्ठा *__tsk);
बाह्य व्योम fpu_state_restore(काष्ठा pt_regs *regs);
बाह्य व्योम __fpu_state_restore(व्योम);
#अन्यथा
#घोषणा save_fpu(tsk)			करो अणु पूर्ण जबतक (0)
#घोषणा restore_fpu(tsk)		करो अणु पूर्ण जबतक (0)
#घोषणा release_fpu(regs)		करो अणु पूर्ण जबतक (0)
#घोषणा grab_fpu(regs)			करो अणु पूर्ण जबतक (0)
#घोषणा fpu_state_restore(regs)		करो अणु पूर्ण जबतक (0)
#घोषणा __fpu_state_restore(regs)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा user_regset;

बाह्य पूर्णांक करो_fpu_inst(अचिन्हित लघु, काष्ठा pt_regs *);
बाह्य पूर्णांक init_fpu(काष्ठा task_काष्ठा *);

अटल अंतरभूत व्योम __unlazy_fpu(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs)
अणु
	अगर (task_thपढ़ो_info(tsk)->status & TS_USEDFPU) अणु
		task_thपढ़ो_info(tsk)->status &= ~TS_USEDFPU;
		save_fpu(tsk);
		release_fpu(regs);
	पूर्ण अन्यथा
		tsk->thपढ़ो.fpu_counter = 0;
पूर्ण

अटल अंतरभूत व्योम unlazy_fpu(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs)
अणु
	preempt_disable();
	__unlazy_fpu(tsk, regs);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम clear_fpu(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs)
अणु
	preempt_disable();
	अगर (task_thपढ़ो_info(tsk)->status & TS_USEDFPU) अणु
		task_thपढ़ो_info(tsk)->status &= ~TS_USEDFPU;
		release_fpu(regs);
	पूर्ण
	preempt_enable();
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_SH_FPU_H */
