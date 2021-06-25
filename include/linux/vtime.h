<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KERNEL_VTIME_H
#घोषणा _LINUX_KERNEL_VTIME_H

#समावेश <linux/context_tracking_state.h>
#समावेश <linux/sched.h>

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
#समावेश <यंत्र/vसमय.स>
#पूर्ण_अगर

/*
 * Common vसमय APIs
 */
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING
बाह्य व्योम vसमय_account_kernel(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_account_idle(काष्ठा task_काष्ठा *tsk);
#पूर्ण_अगर /* !CONFIG_VIRT_CPU_ACCOUNTING */

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
बाह्य व्योम arch_vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_user_enter(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_user_निकास(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_guest_enter(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_guest_निकास(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_init_idle(काष्ठा task_काष्ठा *tsk, पूर्णांक cpu);
#अन्यथा /* !CONFIG_VIRT_CPU_ACCOUNTING_GEN  */
अटल अंतरभूत व्योम vसमय_user_enter(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_user_निकास(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_guest_enter(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_guest_निकास(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_init_idle(काष्ठा task_काष्ठा *tsk, पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
बाह्य व्योम vसमय_account_irq(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक offset);
बाह्य व्योम vसमय_account_softirq(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_account_hardirq(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम vसमय_flush(काष्ठा task_काष्ठा *tsk);
#अन्यथा /* !CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */
अटल अंतरभूत व्योम vसमय_account_irq(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक offset) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_account_softirq(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_account_hardirq(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम vसमय_flush(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर

/*
 * vसमय_accounting_enabled_this_cpu() definitions/declarations
 */
#अगर defined(CONFIG_VIRT_CPU_ACCOUNTING_NATIVE)

अटल अंतरभूत bool vसमय_accounting_enabled_this_cpu(व्योम) अणु वापस true; पूर्ण
बाह्य व्योम vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev);

अटल __always_अंतरभूत व्योम vसमय_account_guest_enter(व्योम)
अणु
	vसमय_account_kernel(current);
	current->flags |= PF_VCPU;
पूर्ण

अटल __always_अंतरभूत व्योम vसमय_account_guest_निकास(व्योम)
अणु
	vसमय_account_kernel(current);
	current->flags &= ~PF_VCPU;
पूर्ण

#या_अगर defined(CONFIG_VIRT_CPU_ACCOUNTING_GEN)

/*
 * Checks अगर vसमय is enabled on some CPU. Cpuसमय पढ़ोers want to be careful
 * in that हाल and compute the tickless cpuसमय.
 * For now vसमय state is tied to context tracking. We might want to decouple
 * those later अगर necessary.
 */
अटल अंतरभूत bool vसमय_accounting_enabled(व्योम)
अणु
	वापस context_tracking_enabled();
पूर्ण

अटल अंतरभूत bool vसमय_accounting_enabled_cpu(पूर्णांक cpu)
अणु
	वापस context_tracking_enabled_cpu(cpu);
पूर्ण

अटल अंतरभूत bool vसमय_accounting_enabled_this_cpu(व्योम)
अणु
	वापस context_tracking_enabled_this_cpu();
पूर्ण

बाह्य व्योम vसमय_प्रकारask_चयन_generic(काष्ठा task_काष्ठा *prev);

अटल अंतरभूत व्योम vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev)
अणु
	अगर (vसमय_accounting_enabled_this_cpu())
		vसमय_प्रकारask_चयन_generic(prev);
पूर्ण

अटल __always_अंतरभूत व्योम vसमय_account_guest_enter(व्योम)
अणु
	अगर (vसमय_accounting_enabled_this_cpu())
		vसमय_guest_enter(current);
	अन्यथा
		current->flags |= PF_VCPU;
पूर्ण

अटल __always_अंतरभूत व्योम vसमय_account_guest_निकास(व्योम)
अणु
	अगर (vसमय_accounting_enabled_this_cpu())
		vसमय_guest_निकास(current);
	अन्यथा
		current->flags &= ~PF_VCPU;
पूर्ण

#अन्यथा /* !CONFIG_VIRT_CPU_ACCOUNTING */

अटल अंतरभूत bool vसमय_accounting_enabled_this_cpu(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev) अणु पूर्ण

अटल __always_अंतरभूत व्योम vसमय_account_guest_enter(व्योम)
अणु
	current->flags |= PF_VCPU;
पूर्ण

अटल __always_अंतरभूत व्योम vसमय_account_guest_निकास(व्योम)
अणु
	current->flags &= ~PF_VCPU;
पूर्ण

#पूर्ण_अगर


#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
बाह्य व्योम irqसमय_account_irq(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक offset);
#अन्यथा
अटल अंतरभूत व्योम irqसमय_account_irq(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक offset) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम account_softirq_enter(काष्ठा task_काष्ठा *tsk)
अणु
	vसमय_account_irq(tsk, SOFTIRQ_OFFSET);
	irqसमय_account_irq(tsk, SOFTIRQ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम account_softirq_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	vसमय_account_softirq(tsk);
	irqसमय_account_irq(tsk, 0);
पूर्ण

अटल अंतरभूत व्योम account_hardirq_enter(काष्ठा task_काष्ठा *tsk)
अणु
	vसमय_account_irq(tsk, HARसूचीQ_OFFSET);
	irqसमय_account_irq(tsk, HARसूचीQ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम account_hardirq_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	vसमय_account_hardirq(tsk);
	irqसमय_account_irq(tsk, 0);
पूर्ण

#पूर्ण_अगर /* _LINUX_KERNEL_VTIME_H */
