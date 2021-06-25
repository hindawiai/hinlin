<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_TASK_STACK_H
#घोषणा _LINUX_SCHED_TASK_STACK_H

/*
 * task->stack (kernel stack) handling पूर्णांकerfaces:
 */

#समावेश <linux/sched.h>
#समावेश <linux/magic.h>

#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK

/*
 * When accessing the stack of a non-current task that might निकास, use
 * try_get_task_stack() instead.  task_stack_page will वापस a poपूर्णांकer
 * that could get मुक्तd out from under you.
 */
अटल अंतरभूत व्योम *task_stack_page(स्थिर काष्ठा task_काष्ठा *task)
अणु
	वापस task->stack;
पूर्ण

#घोषणा setup_thपढ़ो_stack(new,old)	करो अणु पूर्ण जबतक(0)

अटल अंतरभूत अचिन्हित दीर्घ *end_of_stack(स्थिर काष्ठा task_काष्ठा *task)
अणु
	वापस task->stack;
पूर्ण

#या_अगर !defined(__HAVE_THREAD_FUNCTIONS)

#घोषणा task_stack_page(task)	((व्योम *)(task)->stack)

अटल अंतरभूत व्योम setup_thपढ़ो_stack(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *org)
अणु
	*task_thपढ़ो_info(p) = *task_thपढ़ो_info(org);
	task_thपढ़ो_info(p)->task = p;
पूर्ण

/*
 * Return the address of the last usable दीर्घ on the stack.
 *
 * When the stack grows करोwn, this is just above the thपढ़ो
 * info काष्ठा. Going any lower will corrupt the thपढ़ोinfo.
 *
 * When the stack grows up, this is the highest address.
 * Beyond that position, we corrupt data on the next page.
 */
अटल अंतरभूत अचिन्हित दीर्घ *end_of_stack(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_STACK_GROWSUP
	वापस (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)task_thपढ़ो_info(p) + THREAD_SIZE) - 1;
#अन्यथा
	वापस (अचिन्हित दीर्घ *)(task_thपढ़ो_info(p) + 1);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
अटल अंतरभूत व्योम *try_get_task_stack(काष्ठा task_काष्ठा *tsk)
अणु
	वापस refcount_inc_not_zero(&tsk->stack_refcount) ?
		task_stack_page(tsk) : शून्य;
पूर्ण

बाह्य व्योम put_task_stack(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम *try_get_task_stack(काष्ठा task_काष्ठा *tsk)
अणु
	वापस task_stack_page(tsk);
पूर्ण

अटल अंतरभूत व्योम put_task_stack(काष्ठा task_काष्ठा *tsk) अणुपूर्ण
#पूर्ण_अगर

#घोषणा task_stack_end_corrupted(task) \
		(*(end_of_stack(task)) != STACK_END_MAGIC)

अटल अंतरभूत पूर्णांक object_is_on_stack(स्थिर व्योम *obj)
अणु
	व्योम *stack = task_stack_page(current);

	वापस (obj >= stack) && (obj < (stack + THREAD_SIZE));
पूर्ण

बाह्य व्योम thपढ़ो_stack_cache_init(व्योम);

#अगर_घोषित CONFIG_DEBUG_STACK_USAGE
अटल अंतरभूत अचिन्हित दीर्घ stack_not_used(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ *n = end_of_stack(p);

	करो अणु 	/* Skip over canary */
# अगरdef CONFIG_STACK_GROWSUP
		n--;
# अन्यथा
		n++;
# endअगर
	पूर्ण जबतक (!*n);

# अगरdef CONFIG_STACK_GROWSUP
	वापस (अचिन्हित दीर्घ)end_of_stack(p) - (अचिन्हित दीर्घ)n;
# अन्यथा
	वापस (अचिन्हित दीर्घ)n - (अचिन्हित दीर्घ)end_of_stack(p);
# endअगर
पूर्ण
#पूर्ण_अगर
बाह्य व्योम set_task_stack_end_magic(काष्ठा task_काष्ठा *tsk);

#अगर_अघोषित __HAVE_ARCH_KSTACK_END
अटल अंतरभूत पूर्णांक kstack_end(व्योम *addr)
अणु
	/* Reliable end of stack detection:
	 * Some APM bios versions misalign the stack
	 */
	वापस !(((अचिन्हित दीर्घ)addr+माप(व्योम*)-1) & (THREAD_SIZE-माप(व्योम*)));
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_TASK_STACK_H */
