<शैली गुरु>
//SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cgroup.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "cgroup-internal.h"

#समावेश <trace/events/cgroup.h>

/*
 * Propagate the cgroup frozen state upwards by the cgroup tree.
 */
अटल व्योम cgroup_propagate_frozen(काष्ठा cgroup *cgrp, bool frozen)
अणु
	पूर्णांक desc = 1;

	/*
	 * If the new state is frozen, some मुक्तzing ancestor cgroups may change
	 * their state too, depending on अगर all their descendants are frozen.
	 *
	 * Otherwise, all ancestor cgroups are क्रमced पूर्णांकo the non-frozen state.
	 */
	जबतक ((cgrp = cgroup_parent(cgrp))) अणु
		अगर (frozen) अणु
			cgrp->मुक्तzer.nr_frozen_descendants += desc;
			अगर (!test_bit(CGRP_FROZEN, &cgrp->flags) &&
			    test_bit(CGRP_FREEZE, &cgrp->flags) &&
			    cgrp->मुक्तzer.nr_frozen_descendants ==
			    cgrp->nr_descendants) अणु
				set_bit(CGRP_FROZEN, &cgrp->flags);
				cgroup_file_notअगरy(&cgrp->events_file);
				TRACE_CGROUP_PATH(notअगरy_frozen, cgrp, 1);
				desc++;
			पूर्ण
		पूर्ण अन्यथा अणु
			cgrp->मुक्तzer.nr_frozen_descendants -= desc;
			अगर (test_bit(CGRP_FROZEN, &cgrp->flags)) अणु
				clear_bit(CGRP_FROZEN, &cgrp->flags);
				cgroup_file_notअगरy(&cgrp->events_file);
				TRACE_CGROUP_PATH(notअगरy_frozen, cgrp, 0);
				desc++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Revisit the cgroup frozen state.
 * Checks अगर the cgroup is really frozen and perक्रमm all state transitions.
 */
व्योम cgroup_update_frozen(काष्ठा cgroup *cgrp)
अणु
	bool frozen;

	lockdep_निश्चित_held(&css_set_lock);

	/*
	 * If the cgroup has to be frozen (CGRP_FREEZE bit set),
	 * and all tasks are frozen and/or stopped, let's consider
	 * the cgroup frozen. Otherwise it's not frozen.
	 */
	frozen = test_bit(CGRP_FREEZE, &cgrp->flags) &&
		cgrp->मुक्तzer.nr_frozen_tasks == __cgroup_task_count(cgrp);

	अगर (frozen) अणु
		/* Alपढ़ोy there? */
		अगर (test_bit(CGRP_FROZEN, &cgrp->flags))
			वापस;

		set_bit(CGRP_FROZEN, &cgrp->flags);
	पूर्ण अन्यथा अणु
		/* Alपढ़ोy there? */
		अगर (!test_bit(CGRP_FROZEN, &cgrp->flags))
			वापस;

		clear_bit(CGRP_FROZEN, &cgrp->flags);
	पूर्ण
	cgroup_file_notअगरy(&cgrp->events_file);
	TRACE_CGROUP_PATH(notअगरy_frozen, cgrp, frozen);

	/* Update the state of ancestor cgroups. */
	cgroup_propagate_frozen(cgrp, frozen);
पूर्ण

/*
 * Increment cgroup's nr_frozen_tasks.
 */
अटल व्योम cgroup_inc_frozen_cnt(काष्ठा cgroup *cgrp)
अणु
	cgrp->मुक्तzer.nr_frozen_tasks++;
पूर्ण

/*
 * Decrement cgroup's nr_frozen_tasks.
 */
अटल व्योम cgroup_dec_frozen_cnt(काष्ठा cgroup *cgrp)
अणु
	cgrp->मुक्तzer.nr_frozen_tasks--;
	WARN_ON_ONCE(cgrp->मुक्तzer.nr_frozen_tasks < 0);
पूर्ण

/*
 * Enter frozen/stopped state, अगर not yet there. Update cgroup's counters,
 * and revisit the state of the cgroup, अगर necessary.
 */
व्योम cgroup_enter_frozen(व्योम)
अणु
	काष्ठा cgroup *cgrp;

	अगर (current->frozen)
		वापस;

	spin_lock_irq(&css_set_lock);
	current->frozen = true;
	cgrp = task_dfl_cgroup(current);
	cgroup_inc_frozen_cnt(cgrp);
	cgroup_update_frozen(cgrp);
	spin_unlock_irq(&css_set_lock);
पूर्ण

/*
 * Conditionally leave frozen/stopped state. Update cgroup's counters,
 * and revisit the state of the cgroup, अगर necessary.
 *
 * If always_leave is not set, and the cgroup is मुक्तzing,
 * we're racing with the cgroup freezing. In this case, we don't
 * drop the frozen counter to aव्योम a transient चयन to
 * the unfrozen state.
 */
व्योम cgroup_leave_frozen(bool always_leave)
अणु
	काष्ठा cgroup *cgrp;

	spin_lock_irq(&css_set_lock);
	cgrp = task_dfl_cgroup(current);
	अगर (always_leave || !test_bit(CGRP_FREEZE, &cgrp->flags)) अणु
		cgroup_dec_frozen_cnt(cgrp);
		cgroup_update_frozen(cgrp);
		WARN_ON_ONCE(!current->frozen);
		current->frozen = false;
	पूर्ण अन्यथा अगर (!(current->jobctl & JOBCTL_TRAP_FREEZE)) अणु
		spin_lock(&current->sighand->siglock);
		current->jobctl |= JOBCTL_TRAP_FREEZE;
		set_thपढ़ो_flag(TIF_SIGPENDING);
		spin_unlock(&current->sighand->siglock);
	पूर्ण
	spin_unlock_irq(&css_set_lock);
पूर्ण

/*
 * Freeze or unमुक्तze the task by setting or clearing the JOBCTL_TRAP_FREEZE
 * jobctl bit.
 */
अटल व्योम cgroup_मुक्तze_task(काष्ठा task_काष्ठा *task, bool मुक्तze)
अणु
	अचिन्हित दीर्घ flags;

	/* If the task is about to die, करोn't bother with मुक्तzing it. */
	अगर (!lock_task_sighand(task, &flags))
		वापस;

	अगर (मुक्तze) अणु
		task->jobctl |= JOBCTL_TRAP_FREEZE;
		संकेत_wake_up(task, false);
	पूर्ण अन्यथा अणु
		task->jobctl &= ~JOBCTL_TRAP_FREEZE;
		wake_up_process(task);
	पूर्ण

	unlock_task_sighand(task, &flags);
पूर्ण

/*
 * Freeze or unमुक्तze all tasks in the given cgroup.
 */
अटल व्योम cgroup_करो_मुक्तze(काष्ठा cgroup *cgrp, bool मुक्तze)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	lockdep_निश्चित_held(&cgroup_mutex);

	spin_lock_irq(&css_set_lock);
	अगर (मुक्तze)
		set_bit(CGRP_FREEZE, &cgrp->flags);
	अन्यथा
		clear_bit(CGRP_FREEZE, &cgrp->flags);
	spin_unlock_irq(&css_set_lock);

	अगर (मुक्तze)
		TRACE_CGROUP_PATH(मुक्तze, cgrp);
	अन्यथा
		TRACE_CGROUP_PATH(unमुक्तze, cgrp);

	css_task_iter_start(&cgrp->self, 0, &it);
	जबतक ((task = css_task_iter_next(&it))) अणु
		/*
		 * Ignore kernel thपढ़ोs here. Freezing cgroups containing
		 * kthपढ़ोs isn't supported.
		 */
		अगर (task->flags & PF_KTHREAD)
			जारी;
		cgroup_मुक्तze_task(task, मुक्तze);
	पूर्ण
	css_task_iter_end(&it);

	/*
	 * Cgroup state should be revisited here to cover empty leaf cgroups
	 * and cgroups which descendants are alपढ़ोy in the desired state.
	 */
	spin_lock_irq(&css_set_lock);
	अगर (cgrp->nr_descendants == cgrp->मुक्तzer.nr_frozen_descendants)
		cgroup_update_frozen(cgrp);
	spin_unlock_irq(&css_set_lock);
पूर्ण

/*
 * Adjust the task state (मुक्तze or unमुक्तze) and revisit the state of
 * source and destination cgroups.
 */
व्योम cgroup_मुक्तzer_migrate_task(काष्ठा task_काष्ठा *task,
				 काष्ठा cgroup *src, काष्ठा cgroup *dst)
अणु
	lockdep_निश्चित_held(&css_set_lock);

	/*
	 * Kernel thपढ़ोs are not supposed to be frozen at all.
	 */
	अगर (task->flags & PF_KTHREAD)
		वापस;

	/*
	 * It's not necessary to करो changes अगर both of the src and dst cgroups
	 * are not मुक्तzing and task is not frozen.
	 */
	अगर (!test_bit(CGRP_FREEZE, &src->flags) &&
	    !test_bit(CGRP_FREEZE, &dst->flags) &&
	    !task->frozen)
		वापस;

	/*
	 * Adjust counters of मुक्तzing and frozen tasks.
	 * Note, that अगर the task is frozen, but the destination cgroup is not
	 * frozen, we bump both counters to keep them balanced.
	 */
	अगर (task->frozen) अणु
		cgroup_inc_frozen_cnt(dst);
		cgroup_dec_frozen_cnt(src);
	पूर्ण
	cgroup_update_frozen(dst);
	cgroup_update_frozen(src);

	/*
	 * Force the task to the desired state.
	 */
	cgroup_मुक्तze_task(task, test_bit(CGRP_FREEZE, &dst->flags));
पूर्ण

व्योम cgroup_मुक्तze(काष्ठा cgroup *cgrp, bool मुक्तze)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cgroup *dsct;
	bool applied = false;

	lockdep_निश्चित_held(&cgroup_mutex);

	/*
	 * Nothing changed? Just निकास.
	 */
	अगर (cgrp->मुक्तzer.मुक्तze == मुक्तze)
		वापस;

	cgrp->मुक्तzer.मुक्तze = मुक्तze;

	/*
	 * Propagate changes करोwnwards the cgroup tree.
	 */
	css_क्रम_each_descendant_pre(css, &cgrp->self) अणु
		dsct = css->cgroup;

		अगर (cgroup_is_dead(dsct))
			जारी;

		अगर (मुक्तze) अणु
			dsct->मुक्तzer.e_मुक्तze++;
			/*
			 * Alपढ़ोy frozen because of ancestor's settings?
			 */
			अगर (dsct->मुक्तzer.e_मुक्तze > 1)
				जारी;
		पूर्ण अन्यथा अणु
			dsct->मुक्तzer.e_मुक्तze--;
			/*
			 * Still frozen because of ancestor's settings?
			 */
			अगर (dsct->मुक्तzer.e_मुक्तze > 0)
				जारी;

			WARN_ON_ONCE(dsct->मुक्तzer.e_मुक्तze < 0);
		पूर्ण

		/*
		 * Do change actual state: मुक्तze or unमुक्तze.
		 */
		cgroup_करो_मुक्तze(dsct, मुक्तze);
		applied = true;
	पूर्ण

	/*
	 * Even अगर the actual state hasn't changed, let's notअगरy a user.
	 * The state can be enक्रमced by an ancestor cgroup: the cgroup
	 * can alपढ़ोy be in the desired state or it can be locked in the
	 * opposite state, so that the transition will never happen.
	 * In both हालs it's better to notअगरy a user, that there is
	 * nothing to रुको क्रम.
	 */
	अगर (!applied) अणु
		TRACE_CGROUP_PATH(notअगरy_frozen, cgrp,
				  test_bit(CGRP_FROZEN, &cgrp->flags));
		cgroup_file_notअगरy(&cgrp->events_file);
	पूर्ण
पूर्ण
