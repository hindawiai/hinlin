<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_SWITCH_TO_H
#घोषणा _ASM_RISCV_SWITCH_TO_H

#समावेश <linux/sched/task_stack.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/csr.h>

#अगर_घोषित CONFIG_FPU
बाह्य व्योम __ख_स्थितिe_save(काष्ठा task_काष्ठा *save_to);
बाह्य व्योम __ख_स्थितिe_restore(काष्ठा task_काष्ठा *restore_from);

अटल अंतरभूत व्योम __ख_स्थितिe_clean(काष्ठा pt_regs *regs)
अणु
	regs->status = (regs->status & ~SR_FS) | SR_FS_CLEAN;
पूर्ण

अटल अंतरभूत व्योम ख_स्थितिe_off(काष्ठा task_काष्ठा *task,
			      काष्ठा pt_regs *regs)
अणु
	regs->status = (regs->status & ~SR_FS) | SR_FS_OFF;
पूर्ण

अटल अंतरभूत व्योम ख_स्थितिe_save(काष्ठा task_काष्ठा *task,
			       काष्ठा pt_regs *regs)
अणु
	अगर ((regs->status & SR_FS) == SR_FS_सूचीTY) अणु
		__ख_स्थितिe_save(task);
		__ख_स्थितिe_clean(regs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ख_स्थितिe_restore(काष्ठा task_काष्ठा *task,
				  काष्ठा pt_regs *regs)
अणु
	अगर ((regs->status & SR_FS) != SR_FS_OFF) अणु
		__ख_स्थितिe_restore(task);
		__ख_स्थितिe_clean(regs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __चयन_to_aux(काष्ठा task_काष्ठा *prev,
				   काष्ठा task_काष्ठा *next)
अणु
	काष्ठा pt_regs *regs;

	regs = task_pt_regs(prev);
	अगर (unlikely(regs->status & SR_SD))
		ख_स्थितिe_save(prev, regs);
	ख_स्थितिe_restore(next, task_pt_regs(next));
पूर्ण

बाह्य bool has_fpu;
#अन्यथा
#घोषणा has_fpu false
#घोषणा ख_स्थितिe_save(task, regs) करो अणु पूर्ण जबतक (0)
#घोषणा ख_स्थितिe_restore(task, regs) करो अणु पूर्ण जबतक (0)
#घोषणा __चयन_to_aux(__prev, __next) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *,
				       काष्ठा task_काष्ठा *);

#घोषणा चयन_to(prev, next, last)			\
करो अणु							\
	काष्ठा task_काष्ठा *__prev = (prev);		\
	काष्ठा task_काष्ठा *__next = (next);		\
	अगर (has_fpu)					\
		__चयन_to_aux(__prev, __next);	\
	((last) = __चयन_to(__prev, __next));		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_RISCV_SWITCH_TO_H */
