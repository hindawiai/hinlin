<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STACKLEAK_H
#घोषणा _LINUX_STACKLEAK_H

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

/*
 * Check that the poison value poपूर्णांकs to the unused hole in the
 * भव memory map क्रम your platक्रमm.
 */
#घोषणा STACKLEAK_POISON -0xBEEF
#घोषणा STACKLEAK_SEARCH_DEPTH 128

#अगर_घोषित CONFIG_GCC_PLUGIN_STACKLEAK
#समावेश <यंत्र/stacktrace.h>

अटल अंतरभूत व्योम stackleak_task_init(काष्ठा task_काष्ठा *t)
अणु
	t->lowest_stack = (अचिन्हित दीर्घ)end_of_stack(t) + माप(अचिन्हित दीर्घ);
# अगरdef CONFIG_STACKLEAK_METRICS
	t->prev_lowest_stack = t->lowest_stack;
# endअगर
पूर्ण

#अगर_घोषित CONFIG_STACKLEAK_RUNTIME_DISABLE
पूर्णांक stack_erasing_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
#पूर्ण_अगर

#अन्यथा /* !CONFIG_GCC_PLUGIN_STACKLEAK */
अटल अंतरभूत व्योम stackleak_task_init(काष्ठा task_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
