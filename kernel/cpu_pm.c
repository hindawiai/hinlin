<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@android.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscore_ops.h>

अटल ATOMIC_NOTIFIER_HEAD(cpu_pm_notअगरier_chain);

अटल पूर्णांक cpu_pm_notअगरy(क्रमागत cpu_pm_event event)
अणु
	पूर्णांक ret;

	/*
	 * atomic_notअगरier_call_chain has a RCU पढ़ो critical section, which
	 * could be disfunctional in cpu idle. Copy RCU_NONIDLE code to let
	 * RCU know this.
	 */
	rcu_irq_enter_irqson();
	ret = atomic_notअगरier_call_chain(&cpu_pm_notअगरier_chain, event, शून्य);
	rcu_irq_निकास_irqson();

	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक cpu_pm_notअगरy_robust(क्रमागत cpu_pm_event event_up, क्रमागत cpu_pm_event event_करोwn)
अणु
	पूर्णांक ret;

	rcu_irq_enter_irqson();
	ret = atomic_notअगरier_call_chain_robust(&cpu_pm_notअगरier_chain, event_up, event_करोwn, शून्य);
	rcu_irq_निकास_irqson();

	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण

/**
 * cpu_pm_रेजिस्टर_notअगरier - रेजिस्टर a driver with cpu_pm
 * @nb: notअगरier block to रेजिस्टर
 *
 * Add a driver to a list of drivers that are notअगरied about
 * CPU and CPU cluster low घातer entry and निकास.
 *
 * This function may sleep, and has the same वापस conditions as
 * raw_notअगरier_chain_रेजिस्टर.
 */
पूर्णांक cpu_pm_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&cpu_pm_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_pm_रेजिस्टर_notअगरier);

/**
 * cpu_pm_unरेजिस्टर_notअगरier - unरेजिस्टर a driver with cpu_pm
 * @nb: notअगरier block to be unरेजिस्टरed
 *
 * Remove a driver from the CPU PM notअगरier list.
 *
 * This function may sleep, and has the same वापस conditions as
 * raw_notअगरier_chain_unरेजिस्टर.
 */
पूर्णांक cpu_pm_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&cpu_pm_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_pm_unरेजिस्टर_notअगरier);

/**
 * cpu_pm_enter - CPU low घातer entry notअगरier
 *
 * Notअगरies listeners that a single CPU is entering a low घातer state that may
 * cause some blocks in the same घातer करोमुख्य as the cpu to reset.
 *
 * Must be called on the affected CPU with पूर्णांकerrupts disabled.  Platक्रमm is
 * responsible क्रम ensuring that cpu_pm_enter is not called twice on the same
 * CPU beक्रमe cpu_pm_निकास is called. Notअगरied drivers can include VFP
 * co-processor, पूर्णांकerrupt controller and its PM extensions, local CPU
 * समयrs context save/restore which shouldn't be पूर्णांकerrupted. Hence it
 * must be called with पूर्णांकerrupts disabled.
 *
 * Return conditions are same as __raw_notअगरier_call_chain.
 */
पूर्णांक cpu_pm_enter(व्योम)
अणु
	वापस cpu_pm_notअगरy_robust(CPU_PM_ENTER, CPU_PM_ENTER_FAILED);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_pm_enter);

/**
 * cpu_pm_निकास - CPU low घातer निकास notअगरier
 *
 * Notअगरies listeners that a single CPU is निकासing a low घातer state that may
 * have caused some blocks in the same घातer करोमुख्य as the cpu to reset.
 *
 * Notअगरied drivers can include VFP co-processor, पूर्णांकerrupt controller
 * and its PM extensions, local CPU समयrs context save/restore which
 * shouldn't be पूर्णांकerrupted. Hence it must be called with पूर्णांकerrupts disabled.
 *
 * Return conditions are same as __raw_notअगरier_call_chain.
 */
पूर्णांक cpu_pm_निकास(व्योम)
अणु
	वापस cpu_pm_notअगरy(CPU_PM_EXIT);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_pm_निकास);

/**
 * cpu_cluster_pm_enter - CPU cluster low घातer entry notअगरier
 *
 * Notअगरies listeners that all cpus in a घातer करोमुख्य are entering a low घातer
 * state that may cause some blocks in the same घातer करोमुख्य to reset.
 *
 * Must be called after cpu_pm_enter has been called on all cpus in the घातer
 * करोमुख्य, and beक्रमe cpu_pm_निकास has been called on any cpu in the घातer
 * करोमुख्य. Notअगरied drivers can include VFP co-processor, पूर्णांकerrupt controller
 * and its PM extensions, local CPU समयrs context save/restore which
 * shouldn't be पूर्णांकerrupted. Hence it must be called with पूर्णांकerrupts disabled.
 *
 * Must be called with पूर्णांकerrupts disabled.
 *
 * Return conditions are same as __raw_notअगरier_call_chain.
 */
पूर्णांक cpu_cluster_pm_enter(व्योम)
अणु
	वापस cpu_pm_notअगरy_robust(CPU_CLUSTER_PM_ENTER, CPU_CLUSTER_PM_ENTER_FAILED);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_cluster_pm_enter);

/**
 * cpu_cluster_pm_निकास - CPU cluster low घातer निकास notअगरier
 *
 * Notअगरies listeners that all cpus in a घातer करोमुख्य are निकासing क्रमm a
 * low घातer state that may have caused some blocks in the same घातer करोमुख्य
 * to reset.
 *
 * Must be called after cpu_cluster_pm_enter has been called क्रम the घातer
 * करोमुख्य, and beक्रमe cpu_pm_निकास has been called on any cpu in the घातer
 * करोमुख्य. Notअगरied drivers can include VFP co-processor, पूर्णांकerrupt controller
 * and its PM extensions, local CPU समयrs context save/restore which
 * shouldn't be पूर्णांकerrupted. Hence it must be called with पूर्णांकerrupts disabled.
 *
 * Return conditions are same as __raw_notअगरier_call_chain.
 */
पूर्णांक cpu_cluster_pm_निकास(व्योम)
अणु
	वापस cpu_pm_notअगरy(CPU_CLUSTER_PM_EXIT);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_cluster_pm_निकास);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cpu_pm_suspend(व्योम)
अणु
	पूर्णांक ret;

	ret = cpu_pm_enter();
	अगर (ret)
		वापस ret;

	ret = cpu_cluster_pm_enter();
	वापस ret;
पूर्ण

अटल व्योम cpu_pm_resume(व्योम)
अणु
	cpu_cluster_pm_निकास();
	cpu_pm_निकास();
पूर्ण

अटल काष्ठा syscore_ops cpu_pm_syscore_ops = अणु
	.suspend = cpu_pm_suspend,
	.resume = cpu_pm_resume,
पूर्ण;

अटल पूर्णांक cpu_pm_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&cpu_pm_syscore_ops);
	वापस 0;
पूर्ण
core_initcall(cpu_pm_init);
#पूर्ण_अगर
