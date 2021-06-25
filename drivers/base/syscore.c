<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  syscore.c - Execution of प्रणाली core operations.
 *
 *  Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */

#समावेश <linux/syscore_ops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/suspend.h>
#समावेश <trace/events/घातer.h>

अटल LIST_HEAD(syscore_ops_list);
अटल DEFINE_MUTEX(syscore_ops_lock);

/**
 * रेजिस्टर_syscore_ops - Register a set of प्रणाली core operations.
 * @ops: System core operations to रेजिस्टर.
 */
व्योम रेजिस्टर_syscore_ops(काष्ठा syscore_ops *ops)
अणु
	mutex_lock(&syscore_ops_lock);
	list_add_tail(&ops->node, &syscore_ops_list);
	mutex_unlock(&syscore_ops_lock);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_syscore_ops);

/**
 * unरेजिस्टर_syscore_ops - Unरेजिस्टर a set of प्रणाली core operations.
 * @ops: System core operations to unरेजिस्टर.
 */
व्योम unरेजिस्टर_syscore_ops(काष्ठा syscore_ops *ops)
अणु
	mutex_lock(&syscore_ops_lock);
	list_del(&ops->node);
	mutex_unlock(&syscore_ops_lock);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_syscore_ops);

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * syscore_suspend - Execute all the रेजिस्टरed प्रणाली core suspend callbacks.
 *
 * This function is executed with one CPU on-line and disabled पूर्णांकerrupts.
 */
पूर्णांक syscore_suspend(व्योम)
अणु
	काष्ठा syscore_ops *ops;
	पूर्णांक ret = 0;

	trace_suspend_resume(TPS("syscore_suspend"), 0, true);
	pm_pr_dbg("Checking wakeup interrupts\n");

	/* Return error code अगर there are any wakeup पूर्णांकerrupts pending. */
	अगर (pm_wakeup_pending())
		वापस -EBUSY;

	WARN_ONCE(!irqs_disabled(),
		"Interrupts enabled before system core suspend.\n");

	list_क्रम_each_entry_reverse(ops, &syscore_ops_list, node)
		अगर (ops->suspend) अणु
			pm_pr_dbg("Calling %pS\n", ops->suspend);
			ret = ops->suspend();
			अगर (ret)
				जाओ err_out;
			WARN_ONCE(!irqs_disabled(),
				"Interrupts enabled after %pS\n", ops->suspend);
		पूर्ण

	trace_suspend_resume(TPS("syscore_suspend"), 0, false);
	वापस 0;

 err_out:
	pr_err("PM: System core suspend callback %pS failed.\n", ops->suspend);

	list_क्रम_each_entry_जारी(ops, &syscore_ops_list, node)
		अगर (ops->resume)
			ops->resume();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(syscore_suspend);

/**
 * syscore_resume - Execute all the रेजिस्टरed प्रणाली core resume callbacks.
 *
 * This function is executed with one CPU on-line and disabled पूर्णांकerrupts.
 */
व्योम syscore_resume(व्योम)
अणु
	काष्ठा syscore_ops *ops;

	trace_suspend_resume(TPS("syscore_resume"), 0, true);
	WARN_ONCE(!irqs_disabled(),
		"Interrupts enabled before system core resume.\n");

	list_क्रम_each_entry(ops, &syscore_ops_list, node)
		अगर (ops->resume) अणु
			pm_pr_dbg("Calling %pS\n", ops->resume);
			ops->resume();
			WARN_ONCE(!irqs_disabled(),
				"Interrupts enabled after %pS\n", ops->resume);
		पूर्ण
	trace_suspend_resume(TPS("syscore_resume"), 0, false);
पूर्ण
EXPORT_SYMBOL_GPL(syscore_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/**
 * syscore_shutकरोwn - Execute all the रेजिस्टरed प्रणाली core shutकरोwn callbacks.
 */
व्योम syscore_shutकरोwn(व्योम)
अणु
	काष्ठा syscore_ops *ops;

	mutex_lock(&syscore_ops_lock);

	list_क्रम_each_entry_reverse(ops, &syscore_ops_list, node)
		अगर (ops->shutकरोwn) अणु
			अगर (initcall_debug)
				pr_info("PM: Calling %pS\n", ops->shutकरोwn);
			ops->shutकरोwn();
		पूर्ण

	mutex_unlock(&syscore_ops_lock);
पूर्ण
