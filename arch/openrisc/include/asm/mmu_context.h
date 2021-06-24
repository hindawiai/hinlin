<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_MMU_CONTEXT_H
#घोषणा __ASM_OPENRISC_MMU_CONTEXT_H

#समावेश <यंत्र-generic/mm_hooks.h>

#घोषणा init_new_context init_new_context
बाह्य पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm);
#घोषणा destroy_context destroy_context
बाह्य व्योम destroy_context(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
		      काष्ठा task_काष्ठा *tsk);

#घोषणा activate_mm(prev, next) चयन_mm((prev), (next), शून्य)

/* current active pgd - this is similar to other processors pgd
 * रेजिस्टरs like cr3 on the i386
 */

बाह्य अस्थिर pgd_t *current_pgd[]; /* defined in arch/खोलोrisc/mm/fault.c */

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
