<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CGROUP_H
#घोषणा _LINUX_CGROUP_H
/*
 *  cgroup पूर्णांकerface
 *
 *  Copyright (C) 2003 BULL SA
 *  Copyright (C) 2004-2006 Silicon Graphics, Inc.
 *
 */

#समावेश <linux/sched.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/rculist.h>
#समावेश <linux/cgroupstats.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/types.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/refcount.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <linux/cgroup-defs.h>

काष्ठा kernel_clone_args;

#अगर_घोषित CONFIG_CGROUPS

/*
 * All weight knobs on the शेष hierarchy should use the following min,
 * शेष and max values.  The शेष value is the logarithmic center of
 * MIN and MAX and allows 100x to be expressed in both directions.
 */
#घोषणा CGROUP_WEIGHT_MIN		1
#घोषणा CGROUP_WEIGHT_DFL		100
#घोषणा CGROUP_WEIGHT_MAX		10000

/* walk only thपढ़ोgroup leaders */
#घोषणा CSS_TASK_ITER_PROCS		(1U << 0)
/* walk all thपढ़ोed css_sets in the करोमुख्य */
#घोषणा CSS_TASK_ITER_THREADED		(1U << 1)

/* पूर्णांकernal flags */
#घोषणा CSS_TASK_ITER_SKIPPED		(1U << 16)

/* a css_task_iter should be treated as an opaque object */
काष्ठा css_task_iter अणु
	काष्ठा cgroup_subsys		*ss;
	अचिन्हित पूर्णांक			flags;

	काष्ठा list_head		*cset_pos;
	काष्ठा list_head		*cset_head;

	काष्ठा list_head		*tcset_pos;
	काष्ठा list_head		*tcset_head;

	काष्ठा list_head		*task_pos;

	काष्ठा list_head		*cur_tasks_head;
	काष्ठा css_set			*cur_cset;
	काष्ठा css_set			*cur_dcset;
	काष्ठा task_काष्ठा		*cur_task;
	काष्ठा list_head		iters_node;	/* css_set->task_iters */
पूर्ण;

बाह्य काष्ठा cgroup_root cgrp_dfl_root;
बाह्य काष्ठा css_set init_css_set;

#घोषणा SUBSYS(_x) बाह्य काष्ठा cgroup_subsys _x ## _cgrp_subsys;
#समावेश <linux/cgroup_subsys.h>
#अघोषित SUBSYS

#घोषणा SUBSYS(_x)								\
	बाह्य काष्ठा अटल_key_true _x ## _cgrp_subsys_enabled_key;		\
	बाह्य काष्ठा अटल_key_true _x ## _cgrp_subsys_on_dfl_key;
#समावेश <linux/cgroup_subsys.h>
#अघोषित SUBSYS

/**
 * cgroup_subsys_enabled - fast test on whether a subsys is enabled
 * @ss: subप्रणाली in question
 */
#घोषणा cgroup_subsys_enabled(ss)						\
	अटल_branch_likely(&ss ## _enabled_key)

/**
 * cgroup_subsys_on_dfl - fast test on whether a subsys is on शेष hierarchy
 * @ss: subप्रणाली in question
 */
#घोषणा cgroup_subsys_on_dfl(ss)						\
	अटल_branch_likely(&ss ## _on_dfl_key)

bool css_has_online_children(काष्ठा cgroup_subsys_state *css);
काष्ठा cgroup_subsys_state *css_from_id(पूर्णांक id, काष्ठा cgroup_subsys *ss);
काष्ठा cgroup_subsys_state *cgroup_e_css(काष्ठा cgroup *cgroup,
					 काष्ठा cgroup_subsys *ss);
काष्ठा cgroup_subsys_state *cgroup_get_e_css(काष्ठा cgroup *cgroup,
					     काष्ठा cgroup_subsys *ss);
काष्ठा cgroup_subsys_state *css_tryget_online_from_dir(काष्ठा dentry *dentry,
						       काष्ठा cgroup_subsys *ss);

काष्ठा cgroup *cgroup_get_from_path(स्थिर अक्षर *path);
काष्ठा cgroup *cgroup_get_from_fd(पूर्णांक fd);

पूर्णांक cgroup_attach_task_all(काष्ठा task_काष्ठा *from, काष्ठा task_काष्ठा *);
पूर्णांक cgroup_transfer_tasks(काष्ठा cgroup *to, काष्ठा cgroup *from);

पूर्णांक cgroup_add_dfl_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts);
पूर्णांक cgroup_add_legacy_cftypes(काष्ठा cgroup_subsys *ss, काष्ठा cftype *cfts);
पूर्णांक cgroup_rm_cftypes(काष्ठा cftype *cfts);
व्योम cgroup_file_notअगरy(काष्ठा cgroup_file *cfile);

पूर्णांक task_cgroup_path(काष्ठा task_काष्ठा *task, अक्षर *buf, माप_प्रकार buflen);
पूर्णांक cgroupstats_build(काष्ठा cgroupstats *stats, काष्ठा dentry *dentry);
पूर्णांक proc_cgroup_show(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
		     काष्ठा pid *pid, काष्ठा task_काष्ठा *tsk);

व्योम cgroup_विभाजन(काष्ठा task_काष्ठा *p);
बाह्य पूर्णांक cgroup_can_विभाजन(काष्ठा task_काष्ठा *p,
			   काष्ठा kernel_clone_args *kargs);
बाह्य व्योम cgroup_cancel_विभाजन(काष्ठा task_काष्ठा *p,
			       काष्ठा kernel_clone_args *kargs);
बाह्य व्योम cgroup_post_विभाजन(काष्ठा task_काष्ठा *p,
			     काष्ठा kernel_clone_args *kargs);
व्योम cgroup_निकास(काष्ठा task_काष्ठा *p);
व्योम cgroup_release(काष्ठा task_काष्ठा *p);
व्योम cgroup_मुक्त(काष्ठा task_काष्ठा *p);

पूर्णांक cgroup_init_early(व्योम);
पूर्णांक cgroup_init(व्योम);

पूर्णांक cgroup_parse_भग्न(स्थिर अक्षर *input, अचिन्हित dec_shअगरt, s64 *v);

/*
 * Iteration helpers and macros.
 */

काष्ठा cgroup_subsys_state *css_next_child(काष्ठा cgroup_subsys_state *pos,
					   काष्ठा cgroup_subsys_state *parent);
काष्ठा cgroup_subsys_state *css_next_descendant_pre(काष्ठा cgroup_subsys_state *pos,
						    काष्ठा cgroup_subsys_state *css);
काष्ठा cgroup_subsys_state *css_righपंचांगost_descendant(काष्ठा cgroup_subsys_state *pos);
काष्ठा cgroup_subsys_state *css_next_descendant_post(काष्ठा cgroup_subsys_state *pos,
						     काष्ठा cgroup_subsys_state *css);

काष्ठा task_काष्ठा *cgroup_taskset_first(काष्ठा cgroup_taskset *tset,
					 काष्ठा cgroup_subsys_state **dst_cssp);
काष्ठा task_काष्ठा *cgroup_taskset_next(काष्ठा cgroup_taskset *tset,
					काष्ठा cgroup_subsys_state **dst_cssp);

व्योम css_task_iter_start(काष्ठा cgroup_subsys_state *css, अचिन्हित पूर्णांक flags,
			 काष्ठा css_task_iter *it);
काष्ठा task_काष्ठा *css_task_iter_next(काष्ठा css_task_iter *it);
व्योम css_task_iter_end(काष्ठा css_task_iter *it);

/**
 * css_क्रम_each_child - iterate through children of a css
 * @pos: the css * to use as the loop cursor
 * @parent: css whose children to walk
 *
 * Walk @parent's children.  Must be called under rcu_पढ़ो_lock().
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 *
 * It is allowed to temporarily drop RCU पढ़ो lock during iteration.  The
 * caller is responsible क्रम ensuring that @pos reमुख्यs accessible until
 * the start of the next iteration by, क्रम example, bumping the css refcnt.
 */
#घोषणा css_क्रम_each_child(pos, parent)					\
	क्रम ((pos) = css_next_child(शून्य, (parent)); (pos);		\
	     (pos) = css_next_child((pos), (parent)))

/**
 * css_क्रम_each_descendant_pre - pre-order walk of a css's descendants
 * @pos: the css * to use as the loop cursor
 * @root: css whose descendants to walk
 *
 * Walk @root's descendants.  @root is included in the iteration and the
 * first node to be visited.  Must be called under rcu_पढ़ो_lock().
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 *
 * For example, the following guarantees that a descendant can't escape
 * state updates of its ancestors.
 *
 * my_online(@css)
 * अणु
 *	Lock @css's parent and @css;
 *	Inherit state from the parent;
 *	Unlock both.
 * पूर्ण
 *
 * my_update_state(@css)
 * अणु
 *	css_क्रम_each_descendant_pre(@pos, @css) अणु
 *		Lock @pos;
 *		अगर (@pos == @css)
 *			Update @css's state;
 *		अन्यथा
 *			Verअगरy @pos is alive and inherit state from its parent;
 *		Unlock @pos;
 *	पूर्ण
 * पूर्ण
 *
 * As दीर्घ as the inheriting step, including checking the parent state, is
 * enबंदd inside @pos locking, द्विगुन-locking the parent isn't necessary
 * जबतक inheriting.  The state update to the parent is guaranteed to be
 * visible by walking order and, as दीर्घ as inheriting operations to the
 * same @pos are atomic to each other, multiple updates racing each other
 * still result in the correct state.  It's guaranateed that at least one
 * inheritance happens क्रम any css after the latest update to its parent.
 *
 * If checking parent's state requires locking the parent, each inheriting
 * iteration should lock and unlock both @pos->parent and @pos.
 *
 * Alternatively, a subप्रणाली may choose to use a single global lock to
 * synchronize ->css_online() and ->css_offline() against tree-walking
 * operations.
 *
 * It is allowed to temporarily drop RCU पढ़ो lock during iteration.  The
 * caller is responsible क्रम ensuring that @pos reमुख्यs accessible until
 * the start of the next iteration by, क्रम example, bumping the css refcnt.
 */
#घोषणा css_क्रम_each_descendant_pre(pos, css)				\
	क्रम ((pos) = css_next_descendant_pre(शून्य, (css)); (pos);	\
	     (pos) = css_next_descendant_pre((pos), (css)))

/**
 * css_क्रम_each_descendant_post - post-order walk of a css's descendants
 * @pos: the css * to use as the loop cursor
 * @css: css whose descendants to walk
 *
 * Similar to css_क्रम_each_descendant_pre() but perक्रमms post-order
 * traversal instead.  @root is included in the iteration and the last
 * node to be visited.
 *
 * If a subप्रणाली synchronizes ->css_online() and the start of iteration, a
 * css which finished ->css_online() is guaranteed to be visible in the
 * future iterations and will stay visible until the last reference is put.
 * A css which hasn't finished ->css_online() or alपढ़ोy finished
 * ->css_offline() may show up during traversal.  It's each subsystem's
 * responsibility to synchronize against on/offlining.
 *
 * Note that the walk visibility guarantee example described in pre-order
 * walk करोesn't apply the same to post-order walks.
 */
#घोषणा css_क्रम_each_descendant_post(pos, css)				\
	क्रम ((pos) = css_next_descendant_post(शून्य, (css)); (pos);	\
	     (pos) = css_next_descendant_post((pos), (css)))

/**
 * cgroup_taskset_क्रम_each - iterate cgroup_taskset
 * @task: the loop cursor
 * @dst_css: the destination css
 * @tset: taskset to iterate
 *
 * @tset may contain multiple tasks and they may beदीर्घ to multiple
 * processes.
 *
 * On the v2 hierarchy, there may be tasks from multiple processes and they
 * may not share the source or destination csses.
 *
 * On traditional hierarchies, when there are multiple tasks in @tset, अगर a
 * task of a process is in @tset, all tasks of the process are in @tset.
 * Also, all are guaranteed to share the same source and destination csses.
 *
 * Iteration is not in any specअगरic order.
 */
#घोषणा cgroup_taskset_क्रम_each(task, dst_css, tset)			\
	क्रम ((task) = cgroup_taskset_first((tset), &(dst_css));		\
	     (task);							\
	     (task) = cgroup_taskset_next((tset), &(dst_css)))

/**
 * cgroup_taskset_क्रम_each_leader - iterate group leaders in a cgroup_taskset
 * @leader: the loop cursor
 * @dst_css: the destination css
 * @tset: taskset to iterate
 *
 * Iterate thपढ़ोgroup leaders of @tset.  For single-task migrations, @tset
 * may not contain any.
 */
#घोषणा cgroup_taskset_क्रम_each_leader(leader, dst_css, tset)		\
	क्रम ((leader) = cgroup_taskset_first((tset), &(dst_css));	\
	     (leader);							\
	     (leader) = cgroup_taskset_next((tset), &(dst_css)))	\
		अगर ((leader) != (leader)->group_leader)			\
			;						\
		अन्यथा

/*
 * Inline functions.
 */

अटल अंतरभूत u64 cgroup_id(स्थिर काष्ठा cgroup *cgrp)
अणु
	वापस cgrp->kn->id;
पूर्ण

/**
 * css_get - obtain a reference on the specअगरied css
 * @css: target css
 *
 * The caller must alपढ़ोy have a reference.
 */
अटल अंतरभूत व्योम css_get(काष्ठा cgroup_subsys_state *css)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		percpu_ref_get(&css->refcnt);
पूर्ण

/**
 * css_get_many - obtain references on the specअगरied css
 * @css: target css
 * @n: number of references to get
 *
 * The caller must alपढ़ोy have a reference.
 */
अटल अंतरभूत व्योम css_get_many(काष्ठा cgroup_subsys_state *css, अचिन्हित पूर्णांक n)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		percpu_ref_get_many(&css->refcnt, n);
पूर्ण

/**
 * css_tryget - try to obtain a reference on the specअगरied css
 * @css: target css
 *
 * Obtain a reference on @css unless it alपढ़ोy has reached zero and is
 * being released.  This function करोesn't care whether @css is on or
 * offline.  The caller naturally needs to ensure that @css is accessible
 * but करोesn't have to be holding a reference on it - IOW, RCU रक्षित
 * access is good enough क्रम this function.  Returns %true अगर a reference
 * count was successfully obtained; %false otherwise.
 */
अटल अंतरभूत bool css_tryget(काष्ठा cgroup_subsys_state *css)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		वापस percpu_ref_tryget(&css->refcnt);
	वापस true;
पूर्ण

/**
 * css_tryget_online - try to obtain a reference on the specअगरied css अगर online
 * @css: target css
 *
 * Obtain a reference on @css अगर it's online.  The caller naturally needs
 * to ensure that @css is accessible but करोesn't have to be holding a
 * reference on it - IOW, RCU रक्षित access is good enough क्रम this
 * function.  Returns %true अगर a reference count was successfully obtained;
 * %false otherwise.
 */
अटल अंतरभूत bool css_tryget_online(काष्ठा cgroup_subsys_state *css)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		वापस percpu_ref_tryget_live(&css->refcnt);
	वापस true;
पूर्ण

/**
 * css_is_dying - test whether the specअगरied css is dying
 * @css: target css
 *
 * Test whether @css is in the process of offlining or alपढ़ोy offline.  In
 * most हालs, ->css_online() and ->css_offline() callbacks should be
 * enough; however, the actual offline operations are RCU delayed and this
 * test वापसs %true also when @css is scheduled to be offlined.
 *
 * This is useful, क्रम example, when the use हाल requires synchronous
 * behavior with respect to cgroup removal.  cgroup removal schedules css
 * offlining but the css can seem alive जबतक the operation is being
 * delayed.  If the delay affects user visible semantics, this test can be
 * used to resolve the situation.
 */
अटल अंतरभूत bool css_is_dying(काष्ठा cgroup_subsys_state *css)
अणु
	वापस !(css->flags & CSS_NO_REF) && percpu_ref_is_dying(&css->refcnt);
पूर्ण

/**
 * css_put - put a css reference
 * @css: target css
 *
 * Put a reference obtained via css_get() and css_tryget_online().
 */
अटल अंतरभूत व्योम css_put(काष्ठा cgroup_subsys_state *css)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		percpu_ref_put(&css->refcnt);
पूर्ण

/**
 * css_put_many - put css references
 * @css: target css
 * @n: number of references to put
 *
 * Put references obtained via css_get() and css_tryget_online().
 */
अटल अंतरभूत व्योम css_put_many(काष्ठा cgroup_subsys_state *css, अचिन्हित पूर्णांक n)
अणु
	अगर (!(css->flags & CSS_NO_REF))
		percpu_ref_put_many(&css->refcnt, n);
पूर्ण

अटल अंतरभूत व्योम cgroup_get(काष्ठा cgroup *cgrp)
अणु
	css_get(&cgrp->self);
पूर्ण

अटल अंतरभूत bool cgroup_tryget(काष्ठा cgroup *cgrp)
अणु
	वापस css_tryget(&cgrp->self);
पूर्ण

अटल अंतरभूत व्योम cgroup_put(काष्ठा cgroup *cgrp)
अणु
	css_put(&cgrp->self);
पूर्ण

/**
 * task_css_set_check - obtain a task's css_set with extra access conditions
 * @task: the task to obtain css_set क्रम
 * @__c: extra condition expression to be passed to rcu_dereference_check()
 *
 * A task's css_set is RCU रक्षित, initialized and निकासed जबतक holding
 * task_lock(), and can only be modअगरied जबतक holding both cgroup_mutex
 * and task_lock() जबतक the task is alive.  This macro verअगरies that the
 * caller is inside proper critical section and वापसs @task's css_set.
 *
 * The caller can also specअगरy additional allowed conditions via @__c, such
 * as locks used during the cgroup_subsys::attach() methods.
 */
#अगर_घोषित CONFIG_PROVE_RCU
बाह्य काष्ठा mutex cgroup_mutex;
बाह्य spinlock_t css_set_lock;
#घोषणा task_css_set_check(task, __c)					\
	rcu_dereference_check((task)->cgroups,				\
		lockdep_is_held(&cgroup_mutex) ||			\
		lockdep_is_held(&css_set_lock) ||			\
		((task)->flags & PF_EXITING) || (__c))
#अन्यथा
#घोषणा task_css_set_check(task, __c)					\
	rcu_dereference((task)->cgroups)
#पूर्ण_अगर

/**
 * task_css_check - obtain css क्रम (task, subsys) w/ extra access conds
 * @task: the target task
 * @subsys_id: the target subप्रणाली ID
 * @__c: extra condition expression to be passed to rcu_dereference_check()
 *
 * Return the cgroup_subsys_state क्रम the (@task, @subsys_id) pair.  The
 * synchronization rules are the same as task_css_set_check().
 */
#घोषणा task_css_check(task, subsys_id, __c)				\
	task_css_set_check((task), (__c))->subsys[(subsys_id)]

/**
 * task_css_set - obtain a task's css_set
 * @task: the task to obtain css_set क्रम
 *
 * See task_css_set_check().
 */
अटल अंतरभूत काष्ठा css_set *task_css_set(काष्ठा task_काष्ठा *task)
अणु
	वापस task_css_set_check(task, false);
पूर्ण

/**
 * task_css - obtain css क्रम (task, subsys)
 * @task: the target task
 * @subsys_id: the target subप्रणाली ID
 *
 * See task_css_check().
 */
अटल अंतरभूत काष्ठा cgroup_subsys_state *task_css(काष्ठा task_काष्ठा *task,
						   पूर्णांक subsys_id)
अणु
	वापस task_css_check(task, subsys_id, false);
पूर्ण

/**
 * task_get_css - find and get the css क्रम (task, subsys)
 * @task: the target task
 * @subsys_id: the target subप्रणाली ID
 *
 * Find the css क्रम the (@task, @subsys_id) combination, increment a
 * reference on and वापस it.  This function is guaranteed to वापस a
 * valid css.  The वापसed css may alपढ़ोy have been offlined.
 */
अटल अंतरभूत काष्ठा cgroup_subsys_state *
task_get_css(काष्ठा task_काष्ठा *task, पूर्णांक subsys_id)
अणु
	काष्ठा cgroup_subsys_state *css;

	rcu_पढ़ो_lock();
	जबतक (true) अणु
		css = task_css(task, subsys_id);
		/*
		 * Can't use css_tryget_online() here.  A task which has
		 * PF_EXITING set may stay associated with an offline css.
		 * If such task calls this function, css_tryget_online()
		 * will keep failing.
		 */
		अगर (likely(css_tryget(css)))
			अवरोध;
		cpu_relax();
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस css;
पूर्ण

/**
 * task_css_is_root - test whether a task beदीर्घs to the root css
 * @task: the target task
 * @subsys_id: the target subप्रणाली ID
 *
 * Test whether @task beदीर्घs to the root css on the specअगरied subप्रणाली.
 * May be invoked in any context.
 */
अटल अंतरभूत bool task_css_is_root(काष्ठा task_काष्ठा *task, पूर्णांक subsys_id)
अणु
	वापस task_css_check(task, subsys_id, true) ==
		init_css_set.subsys[subsys_id];
पूर्ण

अटल अंतरभूत काष्ठा cgroup *task_cgroup(काष्ठा task_काष्ठा *task,
					 पूर्णांक subsys_id)
अणु
	वापस task_css(task, subsys_id)->cgroup;
पूर्ण

अटल अंतरभूत काष्ठा cgroup *task_dfl_cgroup(काष्ठा task_काष्ठा *task)
अणु
	वापस task_css_set(task)->dfl_cgrp;
पूर्ण

अटल अंतरभूत काष्ठा cgroup *cgroup_parent(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup_subsys_state *parent_css = cgrp->self.parent;

	अगर (parent_css)
		वापस container_of(parent_css, काष्ठा cgroup, self);
	वापस शून्य;
पूर्ण

/**
 * cgroup_is_descendant - test ancestry
 * @cgrp: the cgroup to be tested
 * @ancestor: possible ancestor of @cgrp
 *
 * Test whether @cgrp is a descendant of @ancestor.  It also वापसs %true
 * अगर @cgrp == @ancestor.  This function is safe to call as दीर्घ as @cgrp
 * and @ancestor are accessible.
 */
अटल अंतरभूत bool cgroup_is_descendant(काष्ठा cgroup *cgrp,
					काष्ठा cgroup *ancestor)
अणु
	अगर (cgrp->root != ancestor->root || cgrp->level < ancestor->level)
		वापस false;
	वापस cgrp->ancestor_ids[ancestor->level] == cgroup_id(ancestor);
पूर्ण

/**
 * cgroup_ancestor - find ancestor of cgroup
 * @cgrp: cgroup to find ancestor of
 * @ancestor_level: level of ancestor to find starting from root
 *
 * Find ancestor of cgroup at specअगरied level starting from root अगर it exists
 * and वापस poपूर्णांकer to it. Return शून्य अगर @cgrp करोesn't have ancestor at
 * @ancestor_level.
 *
 * This function is safe to call as दीर्घ as @cgrp is accessible.
 */
अटल अंतरभूत काष्ठा cgroup *cgroup_ancestor(काष्ठा cgroup *cgrp,
					     पूर्णांक ancestor_level)
अणु
	अगर (cgrp->level < ancestor_level)
		वापस शून्य;
	जबतक (cgrp && cgrp->level > ancestor_level)
		cgrp = cgroup_parent(cgrp);
	वापस cgrp;
पूर्ण

/**
 * task_under_cgroup_hierarchy - test task's membership of cgroup ancestry
 * @task: the task to be tested
 * @ancestor: possible ancestor of @task's cgroup
 *
 * Tests whether @task's शेष cgroup hierarchy is a descendant of @ancestor.
 * It follows all the same rules as cgroup_is_descendant, and only applies
 * to the शेष hierarchy.
 */
अटल अंतरभूत bool task_under_cgroup_hierarchy(काष्ठा task_काष्ठा *task,
					       काष्ठा cgroup *ancestor)
अणु
	काष्ठा css_set *cset = task_css_set(task);

	वापस cgroup_is_descendant(cset->dfl_cgrp, ancestor);
पूर्ण

/* no synchronization, the result can only be used as a hपूर्णांक */
अटल अंतरभूत bool cgroup_is_populated(काष्ठा cgroup *cgrp)
अणु
	वापस cgrp->nr_populated_csets + cgrp->nr_populated_करोमुख्य_children +
		cgrp->nr_populated_thपढ़ोed_children;
पूर्ण

/* वापसs ino associated with a cgroup */
अटल अंतरभूत ino_t cgroup_ino(काष्ठा cgroup *cgrp)
अणु
	वापस kernfs_ino(cgrp->kn);
पूर्ण

/* cft/css accessors क्रम cftype->ग_लिखो() operation */
अटल अंतरभूत काष्ठा cftype *of_cft(काष्ठा kernfs_खोलो_file *of)
अणु
	वापस of->kn->priv;
पूर्ण

काष्ठा cgroup_subsys_state *of_css(काष्ठा kernfs_खोलो_file *of);

/* cft/css accessors क्रम cftype->seq_*() operations */
अटल अंतरभूत काष्ठा cftype *seq_cft(काष्ठा seq_file *seq)
अणु
	वापस of_cft(seq->निजी);
पूर्ण

अटल अंतरभूत काष्ठा cgroup_subsys_state *seq_css(काष्ठा seq_file *seq)
अणु
	वापस of_css(seq->निजी);
पूर्ण

/*
 * Name / path handling functions.  All are thin wrappers around the kernfs
 * counterparts and can be called under any context.
 */

अटल अंतरभूत पूर्णांक cgroup_name(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen)
अणु
	वापस kernfs_name(cgrp->kn, buf, buflen);
पूर्ण

अटल अंतरभूत पूर्णांक cgroup_path(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen)
अणु
	वापस kernfs_path(cgrp->kn, buf, buflen);
पूर्ण

अटल अंतरभूत व्योम pr_cont_cgroup_name(काष्ठा cgroup *cgrp)
अणु
	pr_cont_kernfs_name(cgrp->kn);
पूर्ण

अटल अंतरभूत व्योम pr_cont_cgroup_path(काष्ठा cgroup *cgrp)
अणु
	pr_cont_kernfs_path(cgrp->kn);
पूर्ण

अटल अंतरभूत काष्ठा psi_group *cgroup_psi(काष्ठा cgroup *cgrp)
अणु
	वापस &cgrp->psi;
पूर्ण

अटल अंतरभूत व्योम cgroup_init_kthपढ़ोd(व्योम)
अणु
	/*
	 * kthपढ़ोd is inherited by all kthपढ़ोs, keep it in the root so
	 * that the new kthपढ़ोs are guaranteed to stay in the root until
	 * initialization is finished.
	 */
	current->no_cgroup_migration = 1;
पूर्ण

अटल अंतरभूत व्योम cgroup_kthपढ़ो_पढ़ोy(व्योम)
अणु
	/*
	 * This kthपढ़ो finished initialization.  The creator should have
	 * set PF_NO_SETAFFINITY अगर this kthपढ़ो should stay in the root.
	 */
	current->no_cgroup_migration = 0;
पूर्ण

व्योम cgroup_path_from_kernfs_id(u64 id, अक्षर *buf, माप_प्रकार buflen);
#अन्यथा /* !CONFIG_CGROUPS */

काष्ठा cgroup_subsys_state;
काष्ठा cgroup;

अटल अंतरभूत u64 cgroup_id(स्थिर काष्ठा cgroup *cgrp) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम css_get(काष्ठा cgroup_subsys_state *css) अणुपूर्ण
अटल अंतरभूत व्योम css_put(काष्ठा cgroup_subsys_state *css) अणुपूर्ण
अटल अंतरभूत पूर्णांक cgroup_attach_task_all(काष्ठा task_काष्ठा *from,
					 काष्ठा task_काष्ठा *t) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cgroupstats_build(काष्ठा cgroupstats *stats,
				    काष्ठा dentry *dentry) अणु वापस -EINVAL; पूर्ण

अटल अंतरभूत व्योम cgroup_विभाजन(काष्ठा task_काष्ठा *p) अणुपूर्ण
अटल अंतरभूत पूर्णांक cgroup_can_विभाजन(काष्ठा task_काष्ठा *p,
				  काष्ठा kernel_clone_args *kargs) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cgroup_cancel_विभाजन(काष्ठा task_काष्ठा *p,
				      काष्ठा kernel_clone_args *kargs) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_post_विभाजन(काष्ठा task_काष्ठा *p,
				    काष्ठा kernel_clone_args *kargs) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_निकास(काष्ठा task_काष्ठा *p) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_release(काष्ठा task_काष्ठा *p) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_मुक्त(काष्ठा task_काष्ठा *p) अणुपूर्ण

अटल अंतरभूत पूर्णांक cgroup_init_early(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cgroup_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cgroup_init_kthपढ़ोd(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_kthपढ़ो_पढ़ोy(व्योम) अणुपूर्ण

अटल अंतरभूत काष्ठा cgroup *cgroup_parent(काष्ठा cgroup *cgrp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा psi_group *cgroup_psi(काष्ठा cgroup *cgrp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool task_under_cgroup_hierarchy(काष्ठा task_काष्ठा *task,
					       काष्ठा cgroup *ancestor)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम cgroup_path_from_kernfs_id(u64 id, अक्षर *buf, माप_प्रकार buflen)
अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_CGROUPS */

#अगर_घोषित CONFIG_CGROUPS
/*
 * cgroup scalable recursive statistics.
 */
व्योम cgroup_rstat_updated(काष्ठा cgroup *cgrp, पूर्णांक cpu);
व्योम cgroup_rstat_flush(काष्ठा cgroup *cgrp);
व्योम cgroup_rstat_flush_irqsafe(काष्ठा cgroup *cgrp);
व्योम cgroup_rstat_flush_hold(काष्ठा cgroup *cgrp);
व्योम cgroup_rstat_flush_release(व्योम);

/*
 * Basic resource stats.
 */
#अगर_घोषित CONFIG_CGROUP_CPUACCT
व्योम cpuacct_अक्षरge(काष्ठा task_काष्ठा *tsk, u64 cpuसमय);
व्योम cpuacct_account_field(काष्ठा task_काष्ठा *tsk, पूर्णांक index, u64 val);
#अन्यथा
अटल अंतरभूत व्योम cpuacct_अक्षरge(काष्ठा task_काष्ठा *tsk, u64 cpuसमय) अणुपूर्ण
अटल अंतरभूत व्योम cpuacct_account_field(काष्ठा task_काष्ठा *tsk, पूर्णांक index,
					 u64 val) अणुपूर्ण
#पूर्ण_अगर

व्योम __cgroup_account_cpuसमय(काष्ठा cgroup *cgrp, u64 delta_exec);
व्योम __cgroup_account_cpuसमय_field(काष्ठा cgroup *cgrp,
				    क्रमागत cpu_usage_stat index, u64 delta_exec);

अटल अंतरभूत व्योम cgroup_account_cpuसमय(काष्ठा task_काष्ठा *task,
					  u64 delta_exec)
अणु
	काष्ठा cgroup *cgrp;

	cpuacct_अक्षरge(task, delta_exec);

	rcu_पढ़ो_lock();
	cgrp = task_dfl_cgroup(task);
	अगर (cgroup_parent(cgrp))
		__cgroup_account_cpuसमय(cgrp, delta_exec);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम cgroup_account_cpuसमय_field(काष्ठा task_काष्ठा *task,
						क्रमागत cpu_usage_stat index,
						u64 delta_exec)
अणु
	काष्ठा cgroup *cgrp;

	cpuacct_account_field(task, index, delta_exec);

	rcu_पढ़ो_lock();
	cgrp = task_dfl_cgroup(task);
	अगर (cgroup_parent(cgrp))
		__cgroup_account_cpuसमय_field(cgrp, index, delta_exec);
	rcu_पढ़ो_unlock();
पूर्ण

#अन्यथा	/* CONFIG_CGROUPS */

अटल अंतरभूत व्योम cgroup_account_cpuसमय(काष्ठा task_काष्ठा *task,
					  u64 delta_exec) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_account_cpuसमय_field(काष्ठा task_काष्ठा *task,
						क्रमागत cpu_usage_stat index,
						u64 delta_exec) अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUPS */

/*
 * sock->sk_cgrp_data handling.  For more info, see sock_cgroup_data
 * definition in cgroup-defs.h.
 */
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA

#अगर defined(CONFIG_CGROUP_NET_PRIO) || defined(CONFIG_CGROUP_NET_CLASSID)
बाह्य spinlock_t cgroup_sk_update_lock;
#पूर्ण_अगर

व्योम cgroup_sk_alloc_disable(व्योम);
व्योम cgroup_sk_alloc(काष्ठा sock_cgroup_data *skcd);
व्योम cgroup_sk_clone(काष्ठा sock_cgroup_data *skcd);
व्योम cgroup_sk_मुक्त(काष्ठा sock_cgroup_data *skcd);

अटल अंतरभूत काष्ठा cgroup *sock_cgroup_ptr(काष्ठा sock_cgroup_data *skcd)
अणु
#अगर defined(CONFIG_CGROUP_NET_PRIO) || defined(CONFIG_CGROUP_NET_CLASSID)
	अचिन्हित दीर्घ v;

	/*
	 * @skcd->val is 64bit but the following is safe on 32bit too as we
	 * just need the lower uदीर्घ to be written and पढ़ो atomically.
	 */
	v = READ_ONCE(skcd->val);

	अगर (v & 3)
		वापस &cgrp_dfl_root.cgrp;

	वापस (काष्ठा cgroup *)(अचिन्हित दीर्घ)v ?: &cgrp_dfl_root.cgrp;
#अन्यथा
	वापस (काष्ठा cgroup *)(अचिन्हित दीर्घ)skcd->val;
#पूर्ण_अगर
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_DATA */

अटल अंतरभूत व्योम cgroup_sk_alloc(काष्ठा sock_cgroup_data *skcd) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_sk_clone(काष्ठा sock_cgroup_data *skcd) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_sk_मुक्त(काष्ठा sock_cgroup_data *skcd) अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_DATA */

काष्ठा cgroup_namespace अणु
	काष्ठा ns_common	ns;
	काष्ठा user_namespace	*user_ns;
	काष्ठा ucounts		*ucounts;
	काष्ठा css_set          *root_cset;
पूर्ण;

बाह्य काष्ठा cgroup_namespace init_cgroup_ns;

#अगर_घोषित CONFIG_CGROUPS

व्योम मुक्त_cgroup_ns(काष्ठा cgroup_namespace *ns);

काष्ठा cgroup_namespace *copy_cgroup_ns(अचिन्हित दीर्घ flags,
					काष्ठा user_namespace *user_ns,
					काष्ठा cgroup_namespace *old_ns);

पूर्णांक cgroup_path_ns(काष्ठा cgroup *cgrp, अक्षर *buf, माप_प्रकार buflen,
		   काष्ठा cgroup_namespace *ns);

#अन्यथा /* !CONFIG_CGROUPS */

अटल अंतरभूत व्योम मुक्त_cgroup_ns(काष्ठा cgroup_namespace *ns) अणु पूर्ण
अटल अंतरभूत काष्ठा cgroup_namespace *
copy_cgroup_ns(अचिन्हित दीर्घ flags, काष्ठा user_namespace *user_ns,
	       काष्ठा cgroup_namespace *old_ns)
अणु
	वापस old_ns;
पूर्ण

#पूर्ण_अगर /* !CONFIG_CGROUPS */

अटल अंतरभूत व्योम get_cgroup_ns(काष्ठा cgroup_namespace *ns)
अणु
	अगर (ns)
		refcount_inc(&ns->ns.count);
पूर्ण

अटल अंतरभूत व्योम put_cgroup_ns(काष्ठा cgroup_namespace *ns)
अणु
	अगर (ns && refcount_dec_and_test(&ns->ns.count))
		मुक्त_cgroup_ns(ns);
पूर्ण

#अगर_घोषित CONFIG_CGROUPS

व्योम cgroup_enter_frozen(व्योम);
व्योम cgroup_leave_frozen(bool always_leave);
व्योम cgroup_update_frozen(काष्ठा cgroup *cgrp);
व्योम cgroup_मुक्तze(काष्ठा cgroup *cgrp, bool मुक्तze);
व्योम cgroup_मुक्तzer_migrate_task(काष्ठा task_काष्ठा *task, काष्ठा cgroup *src,
				 काष्ठा cgroup *dst);

अटल अंतरभूत bool cgroup_task_मुक्तze(काष्ठा task_काष्ठा *task)
अणु
	bool ret;

	अगर (task->flags & PF_KTHREAD)
		वापस false;

	rcu_पढ़ो_lock();
	ret = test_bit(CGRP_FREEZE, &task_dfl_cgroup(task)->flags);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल अंतरभूत bool cgroup_task_frozen(काष्ठा task_काष्ठा *task)
अणु
	वापस task->frozen;
पूर्ण

#अन्यथा /* !CONFIG_CGROUPS */

अटल अंतरभूत व्योम cgroup_enter_frozen(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cgroup_leave_frozen(bool always_leave) अणु पूर्ण
अटल अंतरभूत bool cgroup_task_मुक्तze(काष्ठा task_काष्ठा *task)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool cgroup_task_frozen(काष्ठा task_काष्ठा *task)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* !CONFIG_CGROUPS */

#अगर_घोषित CONFIG_CGROUP_BPF
अटल अंतरभूत व्योम cgroup_bpf_get(काष्ठा cgroup *cgrp)
अणु
	percpu_ref_get(&cgrp->bpf.refcnt);
पूर्ण

अटल अंतरभूत व्योम cgroup_bpf_put(काष्ठा cgroup *cgrp)
अणु
	percpu_ref_put(&cgrp->bpf.refcnt);
पूर्ण

#अन्यथा /* CONFIG_CGROUP_BPF */

अटल अंतरभूत व्योम cgroup_bpf_get(काष्ठा cgroup *cgrp) अणुपूर्ण
अटल अंतरभूत व्योम cgroup_bpf_put(काष्ठा cgroup *cgrp) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CGROUP_BPF */

#पूर्ण_अगर /* _LINUX_CGROUP_H */
