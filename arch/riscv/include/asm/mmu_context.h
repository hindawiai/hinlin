<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_MMU_CONTEXT_H
#घोषणा _ASM_RISCV_MMU_CONTEXT_H

#समावेश <linux/mm_types.h>
#समावेश <यंत्र-generic/mm_hooks.h>

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	काष्ठा task_काष्ठा *task);

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev,
			       काष्ठा mm_काष्ठा *next)
अणु
	चयन_mm(prev, next, शून्य);
पूर्ण

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
			काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_MMU
	atomic_दीर्घ_set(&mm->context.id, 0);
#पूर्ण_अगर
	वापस 0;
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* _ASM_RISCV_MMU_CONTEXT_H */
