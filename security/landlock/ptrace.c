<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Ptrace hooks
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2019-2020 ANSSI
 */

#समावेश <यंत्र/current.h>
#समावेश <linux/cred.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>

#समावेश "common.h"
#समावेश "cred.h"
#समावेश "ptrace.h"
#समावेश "ruleset.h"
#समावेश "setup.h"

/**
 * करोमुख्य_scope_le - Checks करोमुख्य ordering क्रम scoped ptrace
 *
 * @parent: Parent करोमुख्य.
 * @child: Potential child of @parent.
 *
 * Checks अगर the @parent करोमुख्य is less or equal to (i.e. an ancestor, which
 * means a subset of) the @child करोमुख्य.
 */
अटल bool करोमुख्य_scope_le(स्थिर काष्ठा landlock_ruleset *स्थिर parent,
		स्थिर काष्ठा landlock_ruleset *स्थिर child)
अणु
	स्थिर काष्ठा landlock_hierarchy *walker;

	अगर (!parent)
		वापस true;
	अगर (!child)
		वापस false;
	क्रम (walker = child->hierarchy; walker; walker = walker->parent) अणु
		अगर (walker == parent->hierarchy)
			/* @parent is in the scoped hierarchy of @child. */
			वापस true;
	पूर्ण
	/* There is no relationship between @parent and @child. */
	वापस false;
पूर्ण

अटल bool task_is_scoped(स्थिर काष्ठा task_काष्ठा *स्थिर parent,
		स्थिर काष्ठा task_काष्ठा *स्थिर child)
अणु
	bool is_scoped;
	स्थिर काष्ठा landlock_ruleset *करोm_parent, *करोm_child;

	rcu_पढ़ो_lock();
	करोm_parent = landlock_get_task_करोमुख्य(parent);
	करोm_child = landlock_get_task_करोमुख्य(child);
	is_scoped = करोमुख्य_scope_le(करोm_parent, करोm_child);
	rcu_पढ़ो_unlock();
	वापस is_scoped;
पूर्ण

अटल पूर्णांक task_ptrace(स्थिर काष्ठा task_काष्ठा *स्थिर parent,
		स्थिर काष्ठा task_काष्ठा *स्थिर child)
अणु
	/* Quick वापस क्रम non-landlocked tasks. */
	अगर (!landlocked(parent))
		वापस 0;
	अगर (task_is_scoped(parent, child))
		वापस 0;
	वापस -EPERM;
पूर्ण

/**
 * hook_ptrace_access_check - Determines whether the current process may access
 *			      another
 *
 * @child: Process to be accessed.
 * @mode: Mode of attachment.
 *
 * If the current task has Landlock rules, then the child must have at least
 * the same rules.  Else denied.
 *
 * Determines whether a process may access another, वापसing 0 अगर permission
 * granted, -त्रुटि_सं अगर denied.
 */
अटल पूर्णांक hook_ptrace_access_check(काष्ठा task_काष्ठा *स्थिर child,
		स्थिर अचिन्हित पूर्णांक mode)
अणु
	वापस task_ptrace(current, child);
पूर्ण

/**
 * hook_ptrace_traceme - Determines whether another process may trace the
 *			 current one
 *
 * @parent: Task proposed to be the tracer.
 *
 * If the parent has Landlock rules, then the current task must have the same
 * or more rules.  Else denied.
 *
 * Determines whether the nominated task is permitted to trace the current
 * process, वापसing 0 अगर permission is granted, -त्रुटि_सं अगर denied.
 */
अटल पूर्णांक hook_ptrace_traceme(काष्ठा task_काष्ठा *स्थिर parent)
अणु
	वापस task_ptrace(parent, current);
पूर्ण

अटल काष्ठा security_hook_list landlock_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(ptrace_access_check, hook_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, hook_ptrace_traceme),
पूर्ण;

__init व्योम landlock_add_ptrace_hooks(व्योम)
अणु
	security_add_hooks(landlock_hooks, ARRAY_SIZE(landlock_hooks),
			LANDLOCK_NAME);
पूर्ण
