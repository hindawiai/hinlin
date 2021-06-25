<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_MMU_CONTEXT_H
#घोषणा __SPARC_MMU_CONTEXT_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र-generic/mm_hooks.h>

/* Initialize a new mmu context.  This is invoked when a new
 * address space instance (unique or shared) is instantiated.
 */
#घोषणा init_new_context init_new_context
पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm);

/* Destroy a dead context.  This occurs when mmput drops the
 * mm_users count to zero, the mmaps have been released, and
 * all the page tables have been flushed.  Our job is to destroy
 * any reमुख्यing processor-specअगरic state.
 */
#घोषणा destroy_context destroy_context
व्योम destroy_context(काष्ठा mm_काष्ठा *mm);

/* Switch the current MM context. */
व्योम चयन_mm(काष्ठा mm_काष्ठा *old_mm, काष्ठा mm_काष्ठा *mm,
	       काष्ठा task_काष्ठा *tsk);

/* Activate a new MM instance क्रम the current task. */
#घोषणा activate_mm(active_mm, mm) चयन_mm((active_mm), (mm), शून्य)

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__SPARC_MMU_CONTEXT_H) */
