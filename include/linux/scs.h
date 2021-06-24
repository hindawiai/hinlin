<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shaकरोw Call Stack support.
 *
 * Copyright (C) 2019 Google LLC
 */

#अगर_अघोषित _LINUX_SCS_H
#घोषणा _LINUX_SCS_H

#समावेश <linux/gfp.h>
#समावेश <linux/poison.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>

#अगर_घोषित CONFIG_SHADOW_CALL_STACK

#घोषणा SCS_ORDER		0
#घोषणा SCS_SIZE		(PAGE_SIZE << SCS_ORDER)
#घोषणा GFP_SCS			(GFP_KERNEL | __GFP_ZERO)

/* An illegal poपूर्णांकer value to mark the end of the shaकरोw stack. */
#घोषणा SCS_END_MAGIC		(0x5f6UL + POISON_POINTER_DELTA)

#घोषणा task_scs(tsk)		(task_thपढ़ो_info(tsk)->scs_base)
#घोषणा task_scs_sp(tsk)	(task_thपढ़ो_info(tsk)->scs_sp)

व्योम *scs_alloc(पूर्णांक node);
व्योम scs_मुक्त(व्योम *s);
व्योम scs_init(व्योम);
पूर्णांक scs_prepare(काष्ठा task_काष्ठा *tsk, पूर्णांक node);
व्योम scs_release(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत व्योम scs_task_reset(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * Reset the shaकरोw stack to the base address in हाल the task
	 * is reused.
	 */
	task_scs_sp(tsk) = task_scs(tsk);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *__scs_magic(व्योम *s)
अणु
	वापस (अचिन्हित दीर्घ *)(s + SCS_SIZE) - 1;
पूर्ण

अटल अंतरभूत bool task_scs_end_corrupted(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ *magic = __scs_magic(task_scs(tsk));
	अचिन्हित दीर्घ sz = task_scs_sp(tsk) - task_scs(tsk);

	वापस sz >= SCS_SIZE - 1 || READ_ONCE_NOCHECK(*magic) != SCS_END_MAGIC;
पूर्ण

#अन्यथा /* CONFIG_SHADOW_CALL_STACK */

अटल अंतरभूत व्योम *scs_alloc(पूर्णांक node) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम scs_मुक्त(व्योम *s) अणुपूर्ण
अटल अंतरभूत व्योम scs_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम scs_task_reset(काष्ठा task_काष्ठा *tsk) अणुपूर्ण
अटल अंतरभूत पूर्णांक scs_prepare(काष्ठा task_काष्ठा *tsk, पूर्णांक node) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम scs_release(काष्ठा task_काष्ठा *tsk) अणुपूर्ण
अटल अंतरभूत bool task_scs_end_corrupted(काष्ठा task_काष्ठा *tsk) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_SHADOW_CALL_STACK */

#पूर्ण_अगर /* _LINUX_SCS_H */
