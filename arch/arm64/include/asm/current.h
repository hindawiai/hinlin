<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CURRENT_H
#घोषणा __ASM_CURRENT_H

#समावेश <linux/compiler.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

/*
 * We करोn't use पढ़ो_sysreg() as we want the compiler to cache the value where
 * possible.
 */
अटल __always_अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	अचिन्हित दीर्घ sp_el0;

	यंत्र ("mrs %0, sp_el0" : "=r" (sp_el0));

	वापस (काष्ठा task_काष्ठा *)sp_el0;
पूर्ण

#घोषणा current get_current()

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_CURRENT_H */

