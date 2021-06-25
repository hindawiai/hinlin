<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CURRENT_H
#घोषणा _ASM_X86_CURRENT_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/percpu.h>

#अगर_अघोषित __ASSEMBLY__
काष्ठा task_काष्ठा;

DECLARE_PER_CPU(काष्ठा task_काष्ठा *, current_task);

अटल __always_अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	वापस this_cpu_पढ़ो_stable(current_task);
पूर्ण

#घोषणा current get_current()

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_CURRENT_H */
