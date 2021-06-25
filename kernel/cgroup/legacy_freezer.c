<शैली गुरु>
/*
 * cgroup_मुक्तzer.c -  control group मुक्तzer subप्रणाली
 *
 * Copyright IBM Corporation, 2007
 *
 * Author : Cedric Le Goater <clg@fr.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>

/*
 * A cgroup is मुक्तzing अगर any FREEZING flags are set.  FREEZING_SELF is
 * set अगर "FROZEN" is written to मुक्तzer.state cgroupfs file, and cleared
 * क्रम "THAWED".  FREEZING_PARENT is set अगर the parent मुक्तzer is FREEZING
 * क्रम whatever reason.  IOW, a cgroup has FREEZING_PARENT set अगर one of
 * its ancestors has FREEZING_SELF set.
 */
क्रमागत मुक्तzer_state_flags अणु
	CGROUP_FREEZER_ONLINE	= (1 << 0), /* मुक्तzer is fully online */
	CGROUP_FREEZING_SELF	= (1 << 1), /* this मुक्तzer is मुक्तzing */
	CGROUP_FREEZING_PARENT	= (1 << 2), /* the parent मुक्तzer is मुक्तzing */
	CGROUP_FROZEN		= (1 << 3), /* this and its descendants frozen */

	/* mask क्रम all FREEZING flags */
	CGROUP_FREEZING		= CGROUP_FREEZING_SELF | CGROUP_FREEZING_PARENT,
पूर्ण;

काष्ठा मुक्तzer अणु
	काष्ठा cgroup_subsys_state	css;
	अचिन्हित पूर्णांक			state;
पूर्ण;

अटल DEFINE_MUTEX(मुक्तzer_mutex);

अटल अंतरभूत काष्ठा मुक्तzer *css_मुक्तzer(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा मुक्तzer, css) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा मुक्तzer *task_मुक्तzer(काष्ठा task_काष्ठा *task)
अणु
	वापस css_मुक्तzer(task_css(task, मुक्तzer_cgrp_id));
पूर्ण

अटल काष्ठा मुक्तzer *parent_मुक्तzer(काष्ठा मुक्तzer *मुक्तzer)
अणु
	वापस css_मुक्तzer(मुक्तzer->css.parent);
पूर्ण

bool cgroup_मुक्तzing(काष्ठा task_काष्ठा *task)
अणु
	bool ret;

	rcu_पढ़ो_lock();
	ret = task_मुक्तzer(task)->state & CGROUP_FREEZING;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *मुक्तzer_state_strs(अचिन्हित पूर्णांक state)
अणु
	अगर (state & CGROUP_FROZEN)
		वापस "FROZEN";
	अगर (state & CGROUP_FREEZING)
		वापस "FREEZING";
	वापस "THAWED";
पूर्ण;

अटल काष्ठा cgroup_subsys_state *
मुक्तzer_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा मुक्तzer *मुक्तzer;

	मुक्तzer = kzalloc(माप(काष्ठा मुक्तzer), GFP_KERNEL);
	अगर (!मुक्तzer)
		वापस ERR_PTR(-ENOMEM);

	वापस &मुक्तzer->css;
पूर्ण

/**
 * मुक्तzer_css_online - commit creation of a मुक्तzer css
 * @css: css being created
 *
 * We're committing to creation of @css.  Mark it online and inherit
 * parent's freezing state while holding both parent's and our
 * मुक्तzer->lock.
 */
अटल पूर्णांक मुक्तzer_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(css);
	काष्ठा मुक्तzer *parent = parent_मुक्तzer(मुक्तzer);

	mutex_lock(&मुक्तzer_mutex);

	मुक्तzer->state |= CGROUP_FREEZER_ONLINE;

	अगर (parent && (parent->state & CGROUP_FREEZING)) अणु
		मुक्तzer->state |= CGROUP_FREEZING_PARENT | CGROUP_FROZEN;
		atomic_inc(&प्रणाली_मुक्तzing_cnt);
	पूर्ण

	mutex_unlock(&मुक्तzer_mutex);
	वापस 0;
पूर्ण

/**
 * मुक्तzer_css_offline - initiate deकाष्ठाion of a मुक्तzer css
 * @css: css being destroyed
 *
 * @css is going away.  Mark it dead and decrement प्रणाली_मुक्तzing_count अगर
 * it was holding one.
 */
अटल व्योम मुक्तzer_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(css);

	mutex_lock(&मुक्तzer_mutex);

	अगर (मुक्तzer->state & CGROUP_FREEZING)
		atomic_dec(&प्रणाली_मुक्तzing_cnt);

	मुक्तzer->state = 0;

	mutex_unlock(&मुक्तzer_mutex);
पूर्ण

अटल व्योम मुक्तzer_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	kमुक्त(css_मुक्तzer(css));
पूर्ण

/*
 * Tasks can be migrated पूर्णांकo a dअगरferent मुक्तzer anyसमय regardless of its
 * current state.  मुक्तzer_attach() is responsible क्रम making new tasks
 * conक्रमm to the current state.
 *
 * Freezer state changes and task migration are synchronized via
 * @मुक्तzer->lock.  मुक्तzer_attach() makes the new tasks conक्रमm to the
 * current state and all following state changes can see the new tasks.
 */
अटल व्योम मुक्तzer_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *new_css;

	mutex_lock(&मुक्तzer_mutex);

	/*
	 * Make the new tasks conक्रमm to the current state of @new_css.
	 * For simplicity, when migrating any task to a FROZEN cgroup, we
	 * revert it to FREEZING and let update_अगर_frozen() determine the
	 * correct state later.
	 *
	 * Tasks in @tset are on @new_css but may not conक्रमm to its
	 * current state beक्रमe executing the following - !frozen tasks may
	 * be visible in a FROZEN cgroup and frozen tasks in a THAWED one.
	 */
	cgroup_taskset_क्रम_each(task, new_css, tset) अणु
		काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(new_css);

		अगर (!(मुक्तzer->state & CGROUP_FREEZING)) अणु
			__thaw_task(task);
		पूर्ण अन्यथा अणु
			मुक्तze_task(task);
			/* clear FROZEN and propagate upwards */
			जबतक (मुक्तzer && (मुक्तzer->state & CGROUP_FROZEN)) अणु
				मुक्तzer->state &= ~CGROUP_FROZEN;
				मुक्तzer = parent_मुक्तzer(मुक्तzer);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&मुक्तzer_mutex);
पूर्ण

/**
 * मुक्तzer_विभाजन - cgroup post विभाजन callback
 * @task: a task which has just been विभाजनed
 *
 * @task has just been created and should conक्रमm to the current state of
 * the cgroup_मुक्तzer it beदीर्घs to.  This function may race against
 * मुक्तzer_attach().  Losing to मुक्तzer_attach() means that we करोn't have
 * to करो anything as मुक्तzer_attach() will put @task पूर्णांकo the appropriate
 * state.
 */
अटल व्योम मुक्तzer_विभाजन(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा मुक्तzer *मुक्तzer;

	/*
	 * The root cgroup is non-मुक्तzable, so we can skip locking the
	 * मुक्तzer.  This is safe regardless of race with task migration.
	 * If we didn't race or won, skipping is obviously the right thing
	 * to करो.  If we lost and root is the new cgroup, noop is still the
	 * right thing to करो.
	 */
	अगर (task_css_is_root(task, मुक्तzer_cgrp_id))
		वापस;

	mutex_lock(&मुक्तzer_mutex);
	rcu_पढ़ो_lock();

	मुक्तzer = task_मुक्तzer(task);
	अगर (मुक्तzer->state & CGROUP_FREEZING)
		मुक्तze_task(task);

	rcu_पढ़ो_unlock();
	mutex_unlock(&मुक्तzer_mutex);
पूर्ण

/**
 * update_अगर_frozen - update whether a cgroup finished मुक्तzing
 * @css: css of पूर्णांकerest
 *
 * Once FREEZING is initiated, transition to FROZEN is lazily updated by
 * calling this function.  If the current state is FREEZING but not FROZEN,
 * this function checks whether all tasks of this cgroup and the descendant
 * cgroups finished मुक्तzing and, अगर so, sets FROZEN.
 *
 * The caller is responsible क्रम grabbing RCU पढ़ो lock and calling
 * update_अगर_frozen() on all descendants prior to invoking this function.
 *
 * Task states and मुक्तzer state might disagree जबतक tasks are being
 * migrated पूर्णांकo or out of @css, so we can't verअगरy task states against
 * @मुक्तzer state here.  See मुक्तzer_attach() क्रम details.
 */
अटल व्योम update_अगर_frozen(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(css);
	काष्ठा cgroup_subsys_state *pos;
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	lockdep_निश्चित_held(&मुक्तzer_mutex);

	अगर (!(मुक्तzer->state & CGROUP_FREEZING) ||
	    (मुक्तzer->state & CGROUP_FROZEN))
		वापस;

	/* are all (live) children frozen? */
	rcu_पढ़ो_lock();
	css_क्रम_each_child(pos, css) अणु
		काष्ठा मुक्तzer *child = css_मुक्तzer(pos);

		अगर ((child->state & CGROUP_FREEZER_ONLINE) &&
		    !(child->state & CGROUP_FROZEN)) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* are all tasks frozen? */
	css_task_iter_start(css, 0, &it);

	जबतक ((task = css_task_iter_next(&it))) अणु
		अगर (मुक्तzing(task)) अणु
			/*
			 * मुक्तzer_should_skip() indicates that the task
			 * should be skipped when determining मुक्तzing
			 * completion.  Consider it frozen in addition to
			 * the usual frozen condition.
			 */
			अगर (!frozen(task) && !मुक्तzer_should_skip(task))
				जाओ out_iter_end;
		पूर्ण
	पूर्ण

	मुक्तzer->state |= CGROUP_FROZEN;
out_iter_end:
	css_task_iter_end(&it);
पूर्ण

अटल पूर्णांक मुक्तzer_पढ़ो(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा cgroup_subsys_state *css = seq_css(m), *pos;

	mutex_lock(&मुक्तzer_mutex);
	rcu_पढ़ो_lock();

	/* update states bottom-up */
	css_क्रम_each_descendant_post(pos, css) अणु
		अगर (!css_tryget_online(pos))
			जारी;
		rcu_पढ़ो_unlock();

		update_अगर_frozen(pos);

		rcu_पढ़ो_lock();
		css_put(pos);
	पूर्ण

	rcu_पढ़ो_unlock();
	mutex_unlock(&मुक्तzer_mutex);

	seq_माला_दो(m, मुक्तzer_state_strs(css_मुक्तzer(css)->state));
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम मुक्तze_cgroup(काष्ठा मुक्तzer *मुक्तzer)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	css_task_iter_start(&मुक्तzer->css, 0, &it);
	जबतक ((task = css_task_iter_next(&it)))
		मुक्तze_task(task);
	css_task_iter_end(&it);
पूर्ण

अटल व्योम unमुक्तze_cgroup(काष्ठा मुक्तzer *मुक्तzer)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	css_task_iter_start(&मुक्तzer->css, 0, &it);
	जबतक ((task = css_task_iter_next(&it)))
		__thaw_task(task);
	css_task_iter_end(&it);
पूर्ण

/**
 * मुक्तzer_apply_state - apply state change to a single cgroup_मुक्तzer
 * @मुक्तzer: मुक्तzer to apply state change to
 * @मुक्तze: whether to मुक्तze or unमुक्तze
 * @state: CGROUP_FREEZING_* flag to set or clear
 *
 * Set or clear @state on @cgroup according to @मुक्तze, and perक्रमm
 * मुक्तzing or thawing as necessary.
 */
अटल व्योम मुक्तzer_apply_state(काष्ठा मुक्तzer *मुक्तzer, bool मुक्तze,
				अचिन्हित पूर्णांक state)
अणु
	/* also synchronizes against task migration, see मुक्तzer_attach() */
	lockdep_निश्चित_held(&मुक्तzer_mutex);

	अगर (!(मुक्तzer->state & CGROUP_FREEZER_ONLINE))
		वापस;

	अगर (मुक्तze) अणु
		अगर (!(मुक्तzer->state & CGROUP_FREEZING))
			atomic_inc(&प्रणाली_मुक्तzing_cnt);
		मुक्तzer->state |= state;
		मुक्तze_cgroup(मुक्तzer);
	पूर्ण अन्यथा अणु
		bool was_मुक्तzing = मुक्तzer->state & CGROUP_FREEZING;

		मुक्तzer->state &= ~state;

		अगर (!(मुक्तzer->state & CGROUP_FREEZING)) अणु
			अगर (was_मुक्तzing)
				atomic_dec(&प्रणाली_मुक्तzing_cnt);
			मुक्तzer->state &= ~CGROUP_FROZEN;
			unमुक्तze_cgroup(मुक्तzer);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * मुक्तzer_change_state - change the मुक्तzing state of a cgroup_मुक्तzer
 * @मुक्तzer: मुक्तzer of पूर्णांकerest
 * @मुक्तze: whether to मुक्तze or thaw
 *
 * Freeze or thaw @मुक्तzer according to @मुक्तze.  The operations are
 * recursive - all descendants of @मुक्तzer will be affected.
 */
अटल व्योम मुक्तzer_change_state(काष्ठा मुक्तzer *मुक्तzer, bool मुक्तze)
अणु
	काष्ठा cgroup_subsys_state *pos;

	/*
	 * Update all its descendants in pre-order traversal.  Each
	 * descendant will try to inherit its parent's FREEZING state as
	 * CGROUP_FREEZING_PARENT.
	 */
	mutex_lock(&मुक्तzer_mutex);
	rcu_पढ़ो_lock();
	css_क्रम_each_descendant_pre(pos, &मुक्तzer->css) अणु
		काष्ठा मुक्तzer *pos_f = css_मुक्तzer(pos);
		काष्ठा मुक्तzer *parent = parent_मुक्तzer(pos_f);

		अगर (!css_tryget_online(pos))
			जारी;
		rcu_पढ़ो_unlock();

		अगर (pos_f == मुक्तzer)
			मुक्तzer_apply_state(pos_f, मुक्तze,
					    CGROUP_FREEZING_SELF);
		अन्यथा
			मुक्तzer_apply_state(pos_f,
					    parent->state & CGROUP_FREEZING,
					    CGROUP_FREEZING_PARENT);

		rcu_पढ़ो_lock();
		css_put(pos);
	पूर्ण
	rcu_पढ़ो_unlock();
	mutex_unlock(&मुक्तzer_mutex);
पूर्ण

अटल sमाप_प्रकार मुक्तzer_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
			     अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	bool मुक्तze;

	buf = म_मालाip(buf);

	अगर (म_भेद(buf, मुक्तzer_state_strs(0)) == 0)
		मुक्तze = false;
	अन्यथा अगर (म_भेद(buf, मुक्तzer_state_strs(CGROUP_FROZEN)) == 0)
		मुक्तze = true;
	अन्यथा
		वापस -EINVAL;

	मुक्तzer_change_state(css_मुक्तzer(of_css(of)), मुक्तze);
	वापस nbytes;
पूर्ण

अटल u64 मुक्तzer_self_मुक्तzing_पढ़ो(काष्ठा cgroup_subsys_state *css,
				      काष्ठा cftype *cft)
अणु
	काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(css);

	वापस (bool)(मुक्तzer->state & CGROUP_FREEZING_SELF);
पूर्ण

अटल u64 मुक्तzer_parent_मुक्तzing_पढ़ो(काष्ठा cgroup_subsys_state *css,
					काष्ठा cftype *cft)
अणु
	काष्ठा मुक्तzer *मुक्तzer = css_मुक्तzer(css);

	वापस (bool)(मुक्तzer->state & CGROUP_FREEZING_PARENT);
पूर्ण

अटल काष्ठा cftype files[] = अणु
	अणु
		.name = "state",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = मुक्तzer_पढ़ो,
		.ग_लिखो = मुक्तzer_ग_लिखो,
	पूर्ण,
	अणु
		.name = "self_freezing",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_u64 = मुक्तzer_self_मुक्तzing_पढ़ो,
	पूर्ण,
	अणु
		.name = "parent_freezing",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_u64 = मुक्तzer_parent_मुक्तzing_पढ़ो,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys मुक्तzer_cgrp_subsys = अणु
	.css_alloc	= मुक्तzer_css_alloc,
	.css_online	= मुक्तzer_css_online,
	.css_offline	= मुक्तzer_css_offline,
	.css_मुक्त	= मुक्तzer_css_मुक्त,
	.attach		= मुक्तzer_attach,
	.विभाजन		= मुक्तzer_विभाजन,
	.legacy_cftypes	= files,
पूर्ण;
