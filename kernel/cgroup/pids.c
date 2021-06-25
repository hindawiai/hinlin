<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Process number limiting controller क्रम cgroups.
 *
 * Used to allow a cgroup hierarchy to stop any new processes from विभाजन()ing
 * after a certain limit is reached.
 *
 * Since it is trivial to hit the task limit without hitting any kmemcg limits
 * in place, PIDs are a fundamental resource. As such, PID exhaustion must be
 * preventable in the scope of a cgroup hierarchy by allowing resource limiting
 * of the number of tasks in a cgroup.
 *
 * In order to use the `pids` controller, set the maximum number of tasks in
 * pids.max (this is not available in the root cgroup क्रम obvious reasons). The
 * number of processes currently in the cgroup is given by pids.current.
 * Organisational operations are not blocked by cgroup policies, so it is
 * possible to have pids.current > pids.max. However, it is not possible to
 * violate a cgroup policy through विभाजन(). विभाजन() will वापस -EAGAIN अगर विभाजनing
 * would cause a cgroup policy to be violated.
 *
 * To set a cgroup to have no limit, set pids.max to "max". This is the शेष
 * क्रम all new cgroups (N.B. that PID limits are hierarchical, so the most
 * stringent limit in the hierarchy is followed).
 *
 * pids.current tracks all child cgroup hierarchies, so parent/pids.current is
 * a superset of parent/child/pids.current.
 *
 * Copyright (C) 2015 Aleksa Sarai <cyphar@cyphar.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task.h>

#घोषणा PIDS_MAX (PID_MAX_LIMIT + 1ULL)
#घोषणा PIDS_MAX_STR "max"

काष्ठा pids_cgroup अणु
	काष्ठा cgroup_subsys_state	css;

	/*
	 * Use 64-bit types so that we can safely represent "max" as
	 * %PIDS_MAX = (%PID_MAX_LIMIT + 1).
	 */
	atomic64_t			counter;
	atomic64_t			limit;

	/* Handle क्रम "pids.events" */
	काष्ठा cgroup_file		events_file;

	/* Number of बार विभाजन failed because limit was hit. */
	atomic64_t			events_limit;
पूर्ण;

अटल काष्ठा pids_cgroup *css_pids(काष्ठा cgroup_subsys_state *css)
अणु
	वापस container_of(css, काष्ठा pids_cgroup, css);
पूर्ण

अटल काष्ठा pids_cgroup *parent_pids(काष्ठा pids_cgroup *pids)
अणु
	वापस css_pids(pids->css.parent);
पूर्ण

अटल काष्ठा cgroup_subsys_state *
pids_css_alloc(काष्ठा cgroup_subsys_state *parent)
अणु
	काष्ठा pids_cgroup *pids;

	pids = kzalloc(माप(काष्ठा pids_cgroup), GFP_KERNEL);
	अगर (!pids)
		वापस ERR_PTR(-ENOMEM);

	atomic64_set(&pids->counter, 0);
	atomic64_set(&pids->limit, PIDS_MAX);
	atomic64_set(&pids->events_limit, 0);
	वापस &pids->css;
पूर्ण

अटल व्योम pids_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css_pids(css));
पूर्ण

/**
 * pids_cancel - unअक्षरge the local pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to cancel
 *
 * This function will WARN अगर the pid count goes under 0, because such a हाल is
 * a bug in the pids controller proper.
 */
अटल व्योम pids_cancel(काष्ठा pids_cgroup *pids, पूर्णांक num)
अणु
	/*
	 * A negative count (or overflow क्रम that matter) is invalid,
	 * and indicates a bug in the `pids` controller proper.
	 */
	WARN_ON_ONCE(atomic64_add_negative(-num, &pids->counter));
पूर्ण

/**
 * pids_unअक्षरge - hierarchically unअक्षरge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to unअक्षरge
 */
अटल व्योम pids_unअक्षरge(काष्ठा pids_cgroup *pids, पूर्णांक num)
अणु
	काष्ठा pids_cgroup *p;

	क्रम (p = pids; parent_pids(p); p = parent_pids(p))
		pids_cancel(p, num);
पूर्ण

/**
 * pids_अक्षरge - hierarchically अक्षरge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to अक्षरge
 *
 * This function करोes *not* follow the pid limit set. It cannot fail and the new
 * pid count may exceed the limit. This is only used क्रम reverting failed
 * attaches, where there is no other way out than violating the limit.
 */
अटल व्योम pids_अक्षरge(काष्ठा pids_cgroup *pids, पूर्णांक num)
अणु
	काष्ठा pids_cgroup *p;

	क्रम (p = pids; parent_pids(p); p = parent_pids(p))
		atomic64_add(num, &p->counter);
पूर्ण

/**
 * pids_try_अक्षरge - hierarchically try to अक्षरge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to अक्षरge
 *
 * This function follows the set limit. It will fail अगर the अक्षरge would cause
 * the new value to exceed the hierarchical limit. Returns 0 अगर the अक्षरge
 * succeeded, otherwise -EAGAIN.
 */
अटल पूर्णांक pids_try_अक्षरge(काष्ठा pids_cgroup *pids, पूर्णांक num)
अणु
	काष्ठा pids_cgroup *p, *q;

	क्रम (p = pids; parent_pids(p); p = parent_pids(p)) अणु
		पूर्णांक64_t new = atomic64_add_वापस(num, &p->counter);
		पूर्णांक64_t limit = atomic64_पढ़ो(&p->limit);

		/*
		 * Since new is capped to the maximum number of pid_t, अगर
		 * p->limit is %PIDS_MAX then we know that this test will never
		 * fail.
		 */
		अगर (new > limit)
			जाओ revert;
	पूर्ण

	वापस 0;

revert:
	क्रम (q = pids; q != p; q = parent_pids(q))
		pids_cancel(q, num);
	pids_cancel(p, num);

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक pids_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *dst_css;

	cgroup_taskset_क्रम_each(task, dst_css, tset) अणु
		काष्ठा pids_cgroup *pids = css_pids(dst_css);
		काष्ठा cgroup_subsys_state *old_css;
		काष्ठा pids_cgroup *old_pids;

		/*
		 * No need to pin @old_css between here and cancel_attach()
		 * because cgroup core protects it from being मुक्तd beक्रमe
		 * the migration completes or fails.
		 */
		old_css = task_css(task, pids_cgrp_id);
		old_pids = css_pids(old_css);

		pids_अक्षरge(pids, 1);
		pids_unअक्षरge(old_pids, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pids_cancel_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *dst_css;

	cgroup_taskset_क्रम_each(task, dst_css, tset) अणु
		काष्ठा pids_cgroup *pids = css_pids(dst_css);
		काष्ठा cgroup_subsys_state *old_css;
		काष्ठा pids_cgroup *old_pids;

		old_css = task_css(task, pids_cgrp_id);
		old_pids = css_pids(old_css);

		pids_अक्षरge(old_pids, 1);
		pids_unअक्षरge(pids, 1);
	पूर्ण
पूर्ण

/*
 * task_css_check(true) in pids_can_विभाजन() and pids_cancel_विभाजन() relies
 * on cgroup_thपढ़ोgroup_change_begin() held by the copy_process().
 */
अटल पूर्णांक pids_can_विभाजन(काष्ठा task_काष्ठा *task, काष्ठा css_set *cset)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा pids_cgroup *pids;
	पूर्णांक err;

	अगर (cset)
		css = cset->subsys[pids_cgrp_id];
	अन्यथा
		css = task_css_check(current, pids_cgrp_id, true);
	pids = css_pids(css);
	err = pids_try_अक्षरge(pids, 1);
	अगर (err) अणु
		/* Only log the first समय events_limit is incremented. */
		अगर (atomic64_inc_वापस(&pids->events_limit) == 1) अणु
			pr_info("cgroup: fork rejected by pids controller in ");
			pr_cont_cgroup_path(css->cgroup);
			pr_cont("\n");
		पूर्ण
		cgroup_file_notअगरy(&pids->events_file);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम pids_cancel_विभाजन(काष्ठा task_काष्ठा *task, काष्ठा css_set *cset)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा pids_cgroup *pids;

	अगर (cset)
		css = cset->subsys[pids_cgrp_id];
	अन्यथा
		css = task_css_check(current, pids_cgrp_id, true);
	pids = css_pids(css);
	pids_unअक्षरge(pids, 1);
पूर्ण

अटल व्योम pids_release(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pids_cgroup *pids = css_pids(task_css(task, pids_cgrp_id));

	pids_unअक्षरge(pids, 1);
पूर्ण

अटल sमाप_प्रकार pids_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
			      माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup_subsys_state *css = of_css(of);
	काष्ठा pids_cgroup *pids = css_pids(css);
	पूर्णांक64_t limit;
	पूर्णांक err;

	buf = म_मालाip(buf);
	अगर (!म_भेद(buf, PIDS_MAX_STR)) अणु
		limit = PIDS_MAX;
		जाओ set_limit;
	पूर्ण

	err = kम_से_दीर्घl(buf, 0, &limit);
	अगर (err)
		वापस err;

	अगर (limit < 0 || limit >= PIDS_MAX)
		वापस -EINVAL;

set_limit:
	/*
	 * Limit updates करोn't need to be mutex'd, since it isn't
	 * critical that any racing विभाजन()s follow the new limit.
	 */
	atomic64_set(&pids->limit, limit);
	वापस nbytes;
पूर्ण

अटल पूर्णांक pids_max_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा cgroup_subsys_state *css = seq_css(sf);
	काष्ठा pids_cgroup *pids = css_pids(css);
	पूर्णांक64_t limit = atomic64_पढ़ो(&pids->limit);

	अगर (limit >= PIDS_MAX)
		seq_म_लिखो(sf, "%s\n", PIDS_MAX_STR);
	अन्यथा
		seq_म_लिखो(sf, "%lld\n", limit);

	वापस 0;
पूर्ण

अटल s64 pids_current_पढ़ो(काष्ठा cgroup_subsys_state *css,
			     काष्ठा cftype *cft)
अणु
	काष्ठा pids_cgroup *pids = css_pids(css);

	वापस atomic64_पढ़ो(&pids->counter);
पूर्ण

अटल पूर्णांक pids_events_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा pids_cgroup *pids = css_pids(seq_css(sf));

	seq_म_लिखो(sf, "max %lld\n", (s64)atomic64_पढ़ो(&pids->events_limit));
	वापस 0;
पूर्ण

अटल काष्ठा cftype pids_files[] = अणु
	अणु
		.name = "max",
		.ग_लिखो = pids_max_ग_लिखो,
		.seq_show = pids_max_show,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु
		.name = "current",
		.पढ़ो_s64 = pids_current_पढ़ो,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु
		.name = "events",
		.seq_show = pids_events_show,
		.file_offset = दुरत्व(काष्ठा pids_cgroup, events_file),
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys pids_cgrp_subsys = अणु
	.css_alloc	= pids_css_alloc,
	.css_मुक्त	= pids_css_मुक्त,
	.can_attach 	= pids_can_attach,
	.cancel_attach 	= pids_cancel_attach,
	.can_विभाजन	= pids_can_विभाजन,
	.cancel_विभाजन	= pids_cancel_विभाजन,
	.release	= pids_release,
	.legacy_cftypes	= pids_files,
	.dfl_cftypes	= pids_files,
	.thपढ़ोed	= true,
पूर्ण;
