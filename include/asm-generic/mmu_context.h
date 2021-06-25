<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_MMU_CONTEXT_H
#घोषणा __ASM_GENERIC_MMU_CONTEXT_H

/*
 * Generic hooks to implement no-op functionality.
 */

काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;

/*
 * enter_lazy_tlb - Called when "tsk" is about to enter lazy TLB mode.
 *
 * @mm:  the currently active mm context which is becoming lazy
 * @tsk: task which is entering lazy tlb
 *
 * tsk->mm will be शून्य
 */
#अगर_अघोषित enter_lazy_tlb
अटल अंतरभूत व्योम enter_lazy_tlb(काष्ठा mm_काष्ठा *mm,
			काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * init_new_context - Initialize context of a new mm_काष्ठा.
 * @tsk: task काष्ठा क्रम the mm
 * @mm:  the new mm काष्ठा
 * @वापस: 0 on success, -त्रुटि_सं on failure
 */
#अगर_अघोषित init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
			काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * destroy_context - Unकरो init_new_context when the mm is going away
 * @mm: old mm काष्ठा
 */
#अगर_अघोषित destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * activate_mm - called after exec चयनes the current task to a new mm, to चयन to it
 * @prev_mm: previous mm of this task
 * @next_mm: new mm
 */
#अगर_अघोषित activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev_mm,
			       काष्ठा mm_काष्ठा *next_mm)
अणु
	चयन_mm(prev_mm, next_mm, current);
पूर्ण
#पूर्ण_अगर

/**
 * dectivate_mm - called when an mm is released after निकास or exec चयनes away from it
 * @tsk: the task
 * @mm:  the old mm
 */
#अगर_अघोषित deactivate_mm
अटल अंतरभूत व्योम deactivate_mm(काष्ठा task_काष्ठा *tsk,
			काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_MMU_CONTEXT_H */
