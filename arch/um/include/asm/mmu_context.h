<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_MMU_CONTEXT_H
#घोषणा __UM_MMU_CONTEXT_H

#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmap_lock.h>

#समावेश <यंत्र/mm_hooks.h>
#समावेश <यंत्र/mmu.h>

बाह्य व्योम क्रमce_flush_all(व्योम);

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *old, काष्ठा mm_काष्ठा *new)
अणु
	/*
	 * This is called by fs/exec.c and sys_unshare()
	 * when the new ->mm is used क्रम the first समय.
	 */
	__चयन_mm(&new->context.id);
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next, 
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित cpu = smp_processor_id();

	अगर(prev != next)अणु
		cpumask_clear_cpu(cpu, mm_cpumask(prev));
		cpumask_set_cpu(cpu, mm_cpumask(next));
		अगर(next != &init_mm)
			__चयन_mm(&next->context.id);
	पूर्ण
पूर्ण

#घोषणा init_new_context init_new_context
बाह्य पूर्णांक init_new_context(काष्ठा task_काष्ठा *task, काष्ठा mm_काष्ठा *mm);

#घोषणा destroy_context destroy_context
बाह्य व्योम destroy_context(काष्ठा mm_काष्ठा *mm);

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
