<शैली गुरु>
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 1996, 1997, 1998, 1999 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 *
 * based on MIPS यंत्र/mmu_context.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_MMU_CONTEXT_H
#घोषणा _ASM_NIOS2_MMU_CONTEXT_H

#समावेश <linux/mm_types.h>

#समावेश <यंत्र-generic/mm_hooks.h>

बाह्य व्योम mmu_context_init(व्योम);
बाह्य अचिन्हित दीर्घ get_pid_from_context(mm_context_t *ctx);

/*
 * For the fast tlb miss handlers, we keep a poपूर्णांकer to the current pgd.
 * processor.
 */
बाह्य pgd_t *pgd_current;

/*
 * Initialize the context related info क्रम a new mm_काष्ठा instance.
 *
 * Set all new contexts to 0, that way the generation will never match
 * the currently running generation when this context is चयनed in.
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
					काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = 0;
	वापस 0;
पूर्ण

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
		काष्ठा task_काष्ठा *tsk);

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
#घोषणा activate_mm activate_mm
व्योम activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next);

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* _ASM_NIOS2_MMU_CONTEXT_H */
