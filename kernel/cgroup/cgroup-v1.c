<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "cgroup-internal.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/kmod.h>
#समावेश <linux/sort.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/cgroupstats.h>
#समावेश <linux/fs_parser.h>

#समावेश <trace/events/cgroup.h>

/*
 * pidlists linger the following amount beक्रमe being destroyed.  The goal
 * is aव्योमing frequent deकाष्ठाion in the middle of consecutive पढ़ो calls
 * Expiring in the middle is a perक्रमmance problem not a correctness one.
 * 1 sec should be enough.
 */
#घोषणा CGROUP_PIDLIST_DESTROY_DELAY	HZ

/* Controllers blocked by the commandline in v1 */
अटल u16 cgroup_no_v1_mask;

/* disable named v1 mounts */
अटल bool cgroup_no_v1_named;

/*
 * pidlist deकाष्ठाions need to be flushed on cgroup deकाष्ठाion.  Use a
 * separate workqueue as flush करोमुख्य.
 */
अटल काष्ठा workqueue_काष्ठा *cgroup_pidlist_destroy_wq;

/* protects cgroup_subsys->release_agent_path */
अटल DEFINE_SPINLOCK(release_agent_path_lock);

bool cgroup1_ssid_disabled(पूर्णांक ssid)
अणु
	वापस cgroup_no_v1_mask & (1 << ssid);
पूर्ण

/**
 * cgroup_attach_task_all - attach task 'tsk' to all cgroups of task 'from'
 * @from: attach to all cgroups of a given task
 * @tsk: the task to be attached
 */
पूर्णांक cgroup_attach_task_all(काष्ठा task_काष्ठा *from, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cgroup_root *root;
	पूर्णांक retval = 0;

	mutex_lock(&cgroup_mutex);
	percpu_करोwn_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
	क्रम_each_root(root) अणु
		काष्ठा cgroup *from_cgrp;

		अगर (root == &cgrp_dfl_root)
			जारी;

		spin_lock_irq(&css_set_lock);
		from_cgrp = task_cgroup_from_root(from, root);
		spin_unlock_irq(&css_set_lock);

		retval = cgroup_attach_task(from_cgrp, tsk, false);
		अगर (retval)
			अवरोध;
	पूर्ण
	percpu_up_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
	mutex_unlock(&cgroup_mutex);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(cgroup_attach_task_all);

/**
 * cgroup_trasnsfer_tasks - move tasks from one cgroup to another
 * @to: cgroup to which the tasks will be moved
 * @from: cgroup in which the tasks currently reside
 *
 * Locking rules between cgroup_post_विभाजन() and the migration path
 * guarantee that, अगर a task is विभाजनing जबतक being migrated, the new child
 * is guaranteed to be either visible in the source cgroup after the
 * parent's migration is complete or put पूर्णांकo the target cgroup.  No task
 * can slip out of migration through विभाजनing.
 */
पूर्णांक cgroup_transfer_tasks(काष्ठा cgroup *to, काष्ठा cgroup *from)
अणु
	DEFINE_CGROUP_MGCTX(mgctx);
	काष्ठा cgrp_cset_link *link;
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	अगर (cgroup_on_dfl(to))
		वापस -EINVAL;

	ret = cgroup_migrate_vet_dst(to);
	अगर (ret)
		वापस ret;

	mutex_lock(&cgroup_mutex);

	percpu_करोwn_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);

	/* all tasks in @from are being moved, all csets are source */
	spin_lock_irq(&css_set_lock);
	list_क्रम_each_entry(link, &from->cset_links, cset_link)
		cgroup_migrate_add_src(link->cset, to, &mgctx);
	spin_unlock_irq(&css_set_lock);

	ret = cgroup_migrate_prepare_dst(&mgctx);
	अगर (ret)
		जाओ out_err;

	/*
	 * Migrate tasks one-by-one until @from is empty.  This fails अगरf
	 * ->can_attach() fails.
	 */
	करो अणु
		css_task_iter_start(&from->self, 0, &it);

		करो अणु
			task = css_task_iter_next(&it);
		पूर्ण जबतक (task && (task->flags & PF_EXITING));

		अगर (task)
			get_task_काष्ठा(task);
		css_task_iter_end(&it);

		अगर (task) अणु
			ret = cgroup_migrate(task, false, &mgctx);
			अगर (!ret)
				TRACE_CGROUP_PATH(transfer_tasks, to, task, false);
			put_task_काष्ठा(task);
		पूर्ण
	पूर्ण जबतक (task && !ret);
out_err:
	cgroup_migrate_finish(&mgctx);
	percpu_up_ग_लिखो(&cgroup_thपढ़ोgroup_rwsem);
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

/*
 * Stuff क्रम पढ़ोing the 'tasks'/'procs' files.
 *
 * Reading this file can वापस large amounts of data अगर a cgroup has
 * *lots* of attached tasks. So it may need several calls to पढ़ो(),
 * but we cannot guarantee that the inक्रमmation we produce is correct
 * unless we produce it entirely atomically.
 *
 */

/* which pidlist file are we talking about? */
क्रमागत cgroup_filetype अणु
	CGROUP_खाता_PROCS,
	CGROUP_खाता_TASKS,
पूर्ण;

/*
 * A pidlist is a list of pids that भवly represents the contents of one
 * of the cgroup files ("procs" or "tasks"). We keep a list of such pidlists,
 * a pair (one each क्रम procs, tasks) क्रम each pid namespace that's relevant
 * to the cgroup.
 */
काष्ठा cgroup_pidlist अणु
	/*
	 * used to find which pidlist is wanted. करोesn't change as दीर्घ as
	 * this particular list stays in the list.
	*/
	काष्ठा अणु क्रमागत cgroup_filetype type; काष्ठा pid_namespace *ns; पूर्ण key;
	/* array of xids */
	pid_t *list;
	/* how many elements the above list has */
	पूर्णांक length;
	/* each of these stored in a list by its cgroup */
	काष्ठा list_head links;
	/* poपूर्णांकer to the cgroup we beदीर्घ to, क्रम list removal purposes */
	काष्ठा cgroup *owner;
	/* क्रम delayed deकाष्ठाion */
	काष्ठा delayed_work destroy_dwork;
पूर्ण;

/*
 * Used to destroy all pidlists lingering रुकोing क्रम destroy समयr.  None
 * should be left afterwards.
 */
व्योम cgroup1_pidlist_destroy_all(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup_pidlist *l, *पंचांगp_l;

	mutex_lock(&cgrp->pidlist_mutex);
	list_क्रम_each_entry_safe(l, पंचांगp_l, &cgrp->pidlists, links)
		mod_delayed_work(cgroup_pidlist_destroy_wq, &l->destroy_dwork, 0);
	mutex_unlock(&cgrp->pidlist_mutex);

	flush_workqueue(cgroup_pidlist_destroy_wq);
	BUG_ON(!list_empty(&cgrp->pidlists));
पूर्ण

अटल व्योम cgroup_pidlist_destroy_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा cgroup_pidlist *l = container_of(dwork, काष्ठा cgroup_pidlist,
						destroy_dwork);
	काष्ठा cgroup_pidlist *toमुक्त = शून्य;

	mutex_lock(&l->owner->pidlist_mutex);

	/*
	 * Destroy अगरf we didn't get queued again.  The state won't change
	 * as destroy_dwork can only be queued जबतक locked.
	 */
	अगर (!delayed_work_pending(dwork)) अणु
		list_del(&l->links);
		kvमुक्त(l->list);
		put_pid_ns(l->key.ns);
		toमुक्त = l;
	पूर्ण

	mutex_unlock(&l->owner->pidlist_mutex);
	kमुक्त(toमुक्त);
पूर्ण

/*
 * pidlist_uniq - given a kदो_स्मृति()ed list, strip out all duplicate entries
 * Returns the number of unique elements.
 */
अटल पूर्णांक pidlist_uniq(pid_t *list, पूर्णांक length)
अणु
	पूर्णांक src, dest = 1;

	/*
	 * we presume the 0th element is unique, so i starts at 1. trivial
	 * edge हालs first; no work needs to be करोne क्रम either
	 */
	अगर (length == 0 || length == 1)
		वापस length;
	/* src and dest walk करोwn the list; dest counts unique elements */
	क्रम (src = 1; src < length; src++) अणु
		/* find next unique element */
		जबतक (list[src] == list[src-1]) अणु
			src++;
			अगर (src == length)
				जाओ after;
		पूर्ण
		/* dest always poपूर्णांकs to where the next unique element goes */
		list[dest] = list[src];
		dest++;
	पूर्ण
after:
	वापस dest;
पूर्ण

/*
 * The two pid files - task and cgroup.procs - guaranteed that the result
 * is sorted, which क्रमced this whole pidlist fiasco.  As pid order is
 * dअगरferent per namespace, each namespace needs dअगरferently sorted list,
 * making it impossible to use, क्रम example, single rbtree of member tasks
 * sorted by task poपूर्णांकer.  As pidlists can be fairly large, allocating one
 * per खोलो file is dangerous, so cgroup had to implement shared pool of
 * pidlists keyed by cgroup and namespace.
 */
अटल पूर्णांक cmppid(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(pid_t *)a - *(pid_t *)b;
पूर्ण

अटल काष्ठा cgroup_pidlist *cgroup_pidlist_find(काष्ठा cgroup *cgrp,
						  क्रमागत cgroup_filetype type)
अणु
	काष्ठा cgroup_pidlist *l;
	/* करोn't need task_nsproxy() if we're looking at ourself */
	काष्ठा pid_namespace *ns = task_active_pid_ns(current);

	lockdep_निश्चित_held(&cgrp->pidlist_mutex);

	list_क्रम_each_entry(l, &cgrp->pidlists, links)
		अगर (l->key.type == type && l->key.ns == ns)
			वापस l;
	वापस शून्य;
पूर्ण

/*
 * find the appropriate pidlist क्रम our purpose (given procs vs tasks)
 * वापसs with the lock on that pidlist alपढ़ोy held, and takes care
 * of the use count, or वापसs शून्य with no locks held अगर we're out of
 * memory.
 */
अटल काष्ठा cgroup_pidlist *cgroup_pidlist_find_create(काष्ठा cgroup *cgrp,
						क्रमागत cgroup_filetype type)
अणु
	काष्ठा cgroup_pidlist *l;

	lockdep_निश्चित_held(&cgrp->pidlist_mutex);

	l = cgroup_pidlist_find(cgrp, type);
	अगर (l)
		वापस l;

	/* entry not found; create a new one */
	l = kzalloc(माप(काष्ठा cgroup_pidlist), GFP_KERNEL);
	अगर (!l)
		वापस l;

	INIT_DELAYED_WORK(&l->destroy_dwork, cgroup_pidlist_destroy_work_fn);
	l->key.type = type;
	/* करोn't need task_nsproxy() if we're looking at ourself */
	l->key.ns = get_pid_ns(task_active_pid_ns(current));
	l->owner = cgrp;
	list_add(&l->links, &cgrp->pidlists);
	वापस l;
पूर्ण

/*
 * Load a cgroup's pidarray with either procs' tgids or tasks' pids
 */
अटल पूर्णांक pidlist_array_load(काष्ठा cgroup *cgrp, क्रमागत cgroup_filetype type,
			      काष्ठा cgroup_pidlist **lp)
अणु
	pid_t *array;
	पूर्णांक length;
	पूर्णांक pid, n = 0; /* used क्रम populating the array */
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा cgroup_pidlist *l;

	lockdep_निश्चित_held(&cgrp->pidlist_mutex);

	/*
	 * If cgroup माला_लो more users after we पढ़ो count, we won't have
	 * enough space - tough.  This race is indistinguishable to the
	 * caller from the हाल that the additional cgroup users didn't
	 * show up until someसमय later on.
	 */
	length = cgroup_task_count(cgrp);
	array = kvदो_स्मृति_array(length, माप(pid_t), GFP_KERNEL);
	अगर (!array)
		वापस -ENOMEM;
	/* now, populate the array */
	css_task_iter_start(&cgrp->self, 0, &it);
	जबतक ((tsk = css_task_iter_next(&it))) अणु
		अगर (unlikely(n == length))
			अवरोध;
		/* get tgid or pid क्रम procs or tasks file respectively */
		अगर (type == CGROUP_खाता_PROCS)
			pid = task_tgid_vnr(tsk);
		अन्यथा
			pid = task_pid_vnr(tsk);
		अगर (pid > 0) /* make sure to only use valid results */
			array[n++] = pid;
	पूर्ण
	css_task_iter_end(&it);
	length = n;
	/* now sort & (अगर procs) strip out duplicates */
	sort(array, length, माप(pid_t), cmppid, शून्य);
	अगर (type == CGROUP_खाता_PROCS)
		length = pidlist_uniq(array, length);

	l = cgroup_pidlist_find_create(cgrp, type);
	अगर (!l) अणु
		kvमुक्त(array);
		वापस -ENOMEM;
	पूर्ण

	/* store array, मुक्तing old अगर necessary */
	kvमुक्त(l->list);
	l->list = array;
	l->length = length;
	*lp = l;
	वापस 0;
पूर्ण

/*
 * seq_file methods क्रम the tasks/procs files. The seq_file position is the
 * next pid to display; the seq_file iterator is a poपूर्णांकer to the pid
 * in the cgroup->l->list array.
 */

अटल व्योम *cgroup_pidlist_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	/*
	 * Initially we receive a position value that corresponds to
	 * one more than the last pid shown (or 0 on the first call or
	 * after a seek to the start). Use a binary-search to find the
	 * next pid to display, अगर any
	 */
	काष्ठा kernfs_खोलो_file *of = s->निजी;
	काष्ठा cgroup *cgrp = seq_css(s)->cgroup;
	काष्ठा cgroup_pidlist *l;
	क्रमागत cgroup_filetype type = seq_cft(s)->निजी;
	पूर्णांक index = 0, pid = *pos;
	पूर्णांक *iter, ret;

	mutex_lock(&cgrp->pidlist_mutex);

	/*
	 * !शून्य @of->priv indicates that this isn't the first start()
	 * after खोलो.  If the matching pidlist is around, we can use that.
	 * Look क्रम it.  Note that @of->priv can't be used directly.  It
	 * could alपढ़ोy have been destroyed.
	 */
	अगर (of->priv)
		of->priv = cgroup_pidlist_find(cgrp, type);

	/*
	 * Either this is the first start() after खोलो or the matching
	 * pidlist has been destroyed inbetween.  Create a new one.
	 */
	अगर (!of->priv) अणु
		ret = pidlist_array_load(cgrp, type,
					 (काष्ठा cgroup_pidlist **)&of->priv);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण
	l = of->priv;

	अगर (pid) अणु
		पूर्णांक end = l->length;

		जबतक (index < end) अणु
			पूर्णांक mid = (index + end) / 2;
			अगर (l->list[mid] == pid) अणु
				index = mid;
				अवरोध;
			पूर्ण अन्यथा अगर (l->list[mid] <= pid)
				index = mid + 1;
			अन्यथा
				end = mid;
		पूर्ण
	पूर्ण
	/* If we're off the end of the array, we're करोne */
	अगर (index >= l->length)
		वापस शून्य;
	/* Update the असलtract position to be the actual pid that we found */
	iter = l->list + index;
	*pos = *iter;
	वापस iter;
पूर्ण

अटल व्योम cgroup_pidlist_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = s->निजी;
	काष्ठा cgroup_pidlist *l = of->priv;

	अगर (l)
		mod_delayed_work(cgroup_pidlist_destroy_wq, &l->destroy_dwork,
				 CGROUP_PIDLIST_DESTROY_DELAY);
	mutex_unlock(&seq_css(s)->cgroup->pidlist_mutex);
पूर्ण

अटल व्योम *cgroup_pidlist_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा kernfs_खोलो_file *of = s->निजी;
	काष्ठा cgroup_pidlist *l = of->priv;
	pid_t *p = v;
	pid_t *end = l->list + l->length;
	/*
	 * Advance to the next pid in the array. If this goes off the
	 * end, we're करोne
	 */
	p++;
	अगर (p >= end) अणु
		(*pos)++;
		वापस शून्य;
	पूर्ण अन्यथा अणु
		*pos = *p;
		वापस p;
	पूर्ण
पूर्ण

अटल पूर्णांक cgroup_pidlist_show(काष्ठा seq_file *s, व्योम *v)
अणु
	seq_म_लिखो(s, "%d\n", *(पूर्णांक *)v);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार __cgroup1_procs_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				     अक्षर *buf, माप_प्रकार nbytes, loff_t off,
				     bool thपढ़ोgroup)
अणु
	काष्ठा cgroup *cgrp;
	काष्ठा task_काष्ठा *task;
	स्थिर काष्ठा cred *cred, *tcred;
	sमाप_प्रकार ret;
	bool locked;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENODEV;

	task = cgroup_procs_ग_लिखो_start(buf, thपढ़ोgroup, &locked);
	ret = PTR_ERR_OR_ZERO(task);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * Even अगर we're attaching all tasks in the thपढ़ो group, we only
	 * need to check permissions on one of them.
	 */
	cred = current_cred();
	tcred = get_task_cred(task);
	अगर (!uid_eq(cred->euid, GLOBAL_ROOT_UID) &&
	    !uid_eq(cred->euid, tcred->uid) &&
	    !uid_eq(cred->euid, tcred->suid))
		ret = -EACCES;
	put_cred(tcred);
	अगर (ret)
		जाओ out_finish;

	ret = cgroup_attach_task(cgrp, task, thपढ़ोgroup);

out_finish:
	cgroup_procs_ग_लिखो_finish(task, locked);
out_unlock:
	cgroup_kn_unlock(of->kn);

	वापस ret ?: nbytes;
पूर्ण

अटल sमाप_प्रकार cgroup1_procs_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस __cgroup1_procs_ग_लिखो(of, buf, nbytes, off, true);
पूर्ण

अटल sमाप_प्रकार cgroup1_tasks_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस __cgroup1_procs_ग_लिखो(of, buf, nbytes, off, false);
पूर्ण

अटल sमाप_प्रकार cgroup_release_agent_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
					  अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cgroup *cgrp;

	BUILD_BUG_ON(माप(cgrp->root->release_agent_path) < PATH_MAX);

	cgrp = cgroup_kn_lock_live(of->kn, false);
	अगर (!cgrp)
		वापस -ENODEV;
	spin_lock(&release_agent_path_lock);
	strlcpy(cgrp->root->release_agent_path, म_मालाip(buf),
		माप(cgrp->root->release_agent_path));
	spin_unlock(&release_agent_path_lock);
	cgroup_kn_unlock(of->kn);
	वापस nbytes;
पूर्ण

अटल पूर्णांक cgroup_release_agent_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;

	spin_lock(&release_agent_path_lock);
	seq_माला_दो(seq, cgrp->root->release_agent_path);
	spin_unlock(&release_agent_path_lock);
	seq_अ_दो(seq, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_sane_behavior_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_माला_दो(seq, "0\n");
	वापस 0;
पूर्ण

अटल u64 cgroup_पढ़ो_notअगरy_on_release(काष्ठा cgroup_subsys_state *css,
					 काष्ठा cftype *cft)
अणु
	वापस notअगरy_on_release(css->cgroup);
पूर्ण

अटल पूर्णांक cgroup_ग_लिखो_notअगरy_on_release(काष्ठा cgroup_subsys_state *css,
					  काष्ठा cftype *cft, u64 val)
अणु
	अगर (val)
		set_bit(CGRP_NOTIFY_ON_RELEASE, &css->cgroup->flags);
	अन्यथा
		clear_bit(CGRP_NOTIFY_ON_RELEASE, &css->cgroup->flags);
	वापस 0;
पूर्ण

अटल u64 cgroup_clone_children_पढ़ो(काष्ठा cgroup_subsys_state *css,
				      काष्ठा cftype *cft)
अणु
	वापस test_bit(CGRP_CPUSET_CLONE_CHILDREN, &css->cgroup->flags);
पूर्ण

अटल पूर्णांक cgroup_clone_children_ग_लिखो(काष्ठा cgroup_subsys_state *css,
				       काष्ठा cftype *cft, u64 val)
अणु
	अगर (val)
		set_bit(CGRP_CPUSET_CLONE_CHILDREN, &css->cgroup->flags);
	अन्यथा
		clear_bit(CGRP_CPUSET_CLONE_CHILDREN, &css->cgroup->flags);
	वापस 0;
पूर्ण

/* cgroup core पूर्णांकerface files क्रम the legacy hierarchies */
काष्ठा cftype cgroup1_base_files[] = अणु
	अणु
		.name = "cgroup.procs",
		.seq_start = cgroup_pidlist_start,
		.seq_next = cgroup_pidlist_next,
		.seq_stop = cgroup_pidlist_stop,
		.seq_show = cgroup_pidlist_show,
		.निजी = CGROUP_खाता_PROCS,
		.ग_लिखो = cgroup1_procs_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.clone_children",
		.पढ़ो_u64 = cgroup_clone_children_पढ़ो,
		.ग_लिखो_u64 = cgroup_clone_children_ग_लिखो,
	पूर्ण,
	अणु
		.name = "cgroup.sane_behavior",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = cgroup_sane_behavior_show,
	पूर्ण,
	अणु
		.name = "tasks",
		.seq_start = cgroup_pidlist_start,
		.seq_next = cgroup_pidlist_next,
		.seq_stop = cgroup_pidlist_stop,
		.seq_show = cgroup_pidlist_show,
		.निजी = CGROUP_खाता_TASKS,
		.ग_लिखो = cgroup1_tasks_ग_लिखो,
	पूर्ण,
	अणु
		.name = "notify_on_release",
		.पढ़ो_u64 = cgroup_पढ़ो_notअगरy_on_release,
		.ग_लिखो_u64 = cgroup_ग_लिखो_notअगरy_on_release,
	पूर्ण,
	अणु
		.name = "release_agent",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = cgroup_release_agent_show,
		.ग_लिखो = cgroup_release_agent_ग_लिखो,
		.max_ग_लिखो_len = PATH_MAX - 1,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

/* Display inक्रमmation about each subप्रणाली and each hierarchy */
पूर्णांक proc_cgroupstats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i;

	seq_माला_दो(m, "#subsys_name\thierarchy\tnum_cgroups\tenabled\n");
	/*
	 * ideally we करोn't want subप्रणालीs moving around जबतक we करो this.
	 * cgroup_mutex is also necessary to guarantee an atomic snapshot of
	 * subsys/hierarchy state.
	 */
	mutex_lock(&cgroup_mutex);

	क्रम_each_subsys(ss, i)
		seq_म_लिखो(m, "%s\t%d\t%d\t%d\n",
			   ss->legacy_name, ss->root->hierarchy_id,
			   atomic_पढ़ो(&ss->root->nr_cgrps),
			   cgroup_ssid_enabled(i));

	mutex_unlock(&cgroup_mutex);
	वापस 0;
पूर्ण

/**
 * cgroupstats_build - build and fill cgroupstats
 * @stats: cgroupstats to fill inक्रमmation पूर्णांकo
 * @dentry: A dentry entry beदीर्घing to the cgroup क्रम which stats have
 * been requested.
 *
 * Build and fill cgroupstats so that taskstats can export it to user
 * space.
 */
पूर्णांक cgroupstats_build(काष्ठा cgroupstats *stats, काष्ठा dentry *dentry)
अणु
	काष्ठा kernfs_node *kn = kernfs_node_from_dentry(dentry);
	काष्ठा cgroup *cgrp;
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *tsk;

	/* it should be kernfs_node beदीर्घing to cgroupfs and is a directory */
	अगर (dentry->d_sb->s_type != &cgroup_fs_type || !kn ||
	    kernfs_type(kn) != KERNFS_सूची)
		वापस -EINVAL;

	mutex_lock(&cgroup_mutex);

	/*
	 * We aren't being called from kernfs and there's no guarantee on
	 * @kn->priv's validity.  For this and css_tryget_online_from_dir(),
	 * @kn->priv is RCU safe.  Let's करो the RCU dancing.
	 */
	rcu_पढ़ो_lock();
	cgrp = rcu_dereference(*(व्योम __rcu __क्रमce **)&kn->priv);
	अगर (!cgrp || cgroup_is_dead(cgrp)) अणु
		rcu_पढ़ो_unlock();
		mutex_unlock(&cgroup_mutex);
		वापस -ENOENT;
	पूर्ण
	rcu_पढ़ो_unlock();

	css_task_iter_start(&cgrp->self, 0, &it);
	जबतक ((tsk = css_task_iter_next(&it))) अणु
		चयन (tsk->state) अणु
		हाल TASK_RUNNING:
			stats->nr_running++;
			अवरोध;
		हाल TASK_INTERRUPTIBLE:
			stats->nr_sleeping++;
			अवरोध;
		हाल TASK_UNINTERRUPTIBLE:
			stats->nr_unपूर्णांकerruptible++;
			अवरोध;
		हाल TASK_STOPPED:
			stats->nr_stopped++;
			अवरोध;
		शेष:
			अगर (tsk->in_ioरुको)
				stats->nr_io_रुको++;
			अवरोध;
		पूर्ण
	पूर्ण
	css_task_iter_end(&it);

	mutex_unlock(&cgroup_mutex);
	वापस 0;
पूर्ण

व्योम cgroup1_check_क्रम_release(काष्ठा cgroup *cgrp)
अणु
	अगर (notअगरy_on_release(cgrp) && !cgroup_is_populated(cgrp) &&
	    !css_has_online_children(&cgrp->self) && !cgroup_is_dead(cgrp))
		schedule_work(&cgrp->release_agent_work);
पूर्ण

/*
 * Notअगरy userspace when a cgroup is released, by running the
 * configured release agent with the name of the cgroup (path
 * relative to the root of cgroup file प्रणाली) as the argument.
 *
 * Most likely, this user command will try to सूची_हटाओ this cgroup.
 *
 * This races with the possibility that some other task will be
 * attached to this cgroup beक्रमe it is हटाओd, or that some other
 * user task will 'mkdir' a child cgroup of this cgroup.  That's ok.
 * The presumed 'rmdir' will fail quietly अगर this cgroup is no दीर्घer
 * unused, and this cgroup will be reprieved from its death sentence,
 * to जारी to serve a useful existence.  Next समय it's released,
 * we will get notअगरied again, अगर it still has 'notify_on_release' set.
 *
 * The final arg to call_usermodehelper() is UMH_WAIT_EXEC, which
 * means only रुको until the task is successfully execve()'d.  The
 * separate release agent task is विभाजनed by call_usermodehelper(),
 * then control in this thपढ़ो वापसs here, without रुकोing क्रम the
 * release agent task.  We करोn't bother to रुको because the caller of
 * this routine has no use क्रम the निकास status of the release agent
 * task, so no sense holding our caller up क्रम that.
 */
व्योम cgroup1_release_agent(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgroup *cgrp =
		container_of(work, काष्ठा cgroup, release_agent_work);
	अक्षर *pathbuf, *agentbuf;
	अक्षर *argv[3], *envp[3];
	पूर्णांक ret;

	/* snoop agent path and निकास early अगर empty */
	अगर (!cgrp->root->release_agent_path[0])
		वापस;

	/* prepare argument buffers */
	pathbuf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	agentbuf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!pathbuf || !agentbuf)
		जाओ out_मुक्त;

	spin_lock(&release_agent_path_lock);
	strlcpy(agentbuf, cgrp->root->release_agent_path, PATH_MAX);
	spin_unlock(&release_agent_path_lock);
	अगर (!agentbuf[0])
		जाओ out_मुक्त;

	ret = cgroup_path_ns(cgrp, pathbuf, PATH_MAX, &init_cgroup_ns);
	अगर (ret < 0 || ret >= PATH_MAX)
		जाओ out_मुक्त;

	argv[0] = agentbuf;
	argv[1] = pathbuf;
	argv[2] = शून्य;

	/* minimal command environment */
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[2] = शून्य;

	call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
out_मुक्त:
	kमुक्त(agentbuf);
	kमुक्त(pathbuf);
पूर्ण

/*
 * cgroup_नाम - Only allow simple नाम of directories in place.
 */
अटल पूर्णांक cgroup1_नाम(काष्ठा kernfs_node *kn, काष्ठा kernfs_node *new_parent,
			  स्थिर अक्षर *new_name_str)
अणु
	काष्ठा cgroup *cgrp = kn->priv;
	पूर्णांक ret;

	/* करो not accept '\n' to prevent making /proc/<pid>/cgroup unparsable */
	अगर (म_अक्षर(new_name_str, '\n'))
		वापस -EINVAL;

	अगर (kernfs_type(kn) != KERNFS_सूची)
		वापस -ENOTसूची;
	अगर (kn->parent != new_parent)
		वापस -EIO;

	/*
	 * We're gonna grab cgroup_mutex which nests outside kernfs
	 * active_ref.  kernfs_नाम() करोesn't require active_ref
	 * protection.  Break them beक्रमe grabbing cgroup_mutex.
	 */
	kernfs_अवरोध_active_protection(new_parent);
	kernfs_अवरोध_active_protection(kn);

	mutex_lock(&cgroup_mutex);

	ret = kernfs_नाम(kn, new_parent, new_name_str);
	अगर (!ret)
		TRACE_CGROUP_PATH(नाम, cgrp);

	mutex_unlock(&cgroup_mutex);

	kernfs_unअवरोध_active_protection(kn);
	kernfs_unअवरोध_active_protection(new_parent);
	वापस ret;
पूर्ण

अटल पूर्णांक cgroup1_show_options(काष्ठा seq_file *seq, काष्ठा kernfs_root *kf_root)
अणु
	काष्ठा cgroup_root *root = cgroup_root_from_kf(kf_root);
	काष्ठा cgroup_subsys *ss;
	पूर्णांक ssid;

	क्रम_each_subsys(ss, ssid)
		अगर (root->subsys_mask & (1 << ssid))
			seq_show_option(seq, ss->legacy_name, शून्य);
	अगर (root->flags & CGRP_ROOT_NOPREFIX)
		seq_माला_दो(seq, ",noprefix");
	अगर (root->flags & CGRP_ROOT_XATTR)
		seq_माला_दो(seq, ",xattr");
	अगर (root->flags & CGRP_ROOT_CPUSET_V2_MODE)
		seq_माला_दो(seq, ",cpuset_v2_mode");

	spin_lock(&release_agent_path_lock);
	अगर (म_माप(root->release_agent_path))
		seq_show_option(seq, "release_agent",
				root->release_agent_path);
	spin_unlock(&release_agent_path_lock);

	अगर (test_bit(CGRP_CPUSET_CLONE_CHILDREN, &root->cgrp.flags))
		seq_माला_दो(seq, ",clone_children");
	अगर (म_माप(root->name))
		seq_show_option(seq, "name", root->name);
	वापस 0;
पूर्ण

क्रमागत cgroup1_param अणु
	Opt_all,
	Opt_clone_children,
	Opt_cpuset_v2_mode,
	Opt_name,
	Opt_none,
	Opt_noprefix,
	Opt_release_agent,
	Opt_xattr,
पूर्ण;

स्थिर काष्ठा fs_parameter_spec cgroup1_fs_parameters[] = अणु
	fsparam_flag  ("all",		Opt_all),
	fsparam_flag  ("clone_children", Opt_clone_children),
	fsparam_flag  ("cpuset_v2_mode", Opt_cpuset_v2_mode),
	fsparam_string("name",		Opt_name),
	fsparam_flag  ("none",		Opt_none),
	fsparam_flag  ("noprefix",	Opt_noprefix),
	fsparam_string("release_agent",	Opt_release_agent),
	fsparam_flag  ("xattr",		Opt_xattr),
	अणुपूर्ण
पूर्ण;

पूर्णांक cgroup1_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	काष्ठा cgroup_subsys *ss;
	काष्ठा fs_parse_result result;
	पूर्णांक opt, i;

	opt = fs_parse(fc, cgroup1_fs_parameters, param, &result);
	अगर (opt == -ENOPARAM) अणु
		अगर (म_भेद(param->key, "source") == 0) अणु
			अगर (fc->source)
				वापस invalf(fc, "Multiple sources not supported");
			fc->source = param->string;
			param->string = शून्य;
			वापस 0;
		पूर्ण
		क्रम_each_subsys(ss, i) अणु
			अगर (म_भेद(param->key, ss->legacy_name))
				जारी;
			अगर (!cgroup_ssid_enabled(i) || cgroup1_ssid_disabled(i))
				वापस invalfc(fc, "Disabled controller '%s'",
					       param->key);
			ctx->subsys_mask |= (1 << i);
			वापस 0;
		पूर्ण
		वापस invalfc(fc, "Unknown subsys name '%s'", param->key);
	पूर्ण
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_none:
		/* Explicitly have no subप्रणालीs */
		ctx->none = true;
		अवरोध;
	हाल Opt_all:
		ctx->all_ss = true;
		अवरोध;
	हाल Opt_noprefix:
		ctx->flags |= CGRP_ROOT_NOPREFIX;
		अवरोध;
	हाल Opt_clone_children:
		ctx->cpuset_clone_children = true;
		अवरोध;
	हाल Opt_cpuset_v2_mode:
		ctx->flags |= CGRP_ROOT_CPUSET_V2_MODE;
		अवरोध;
	हाल Opt_xattr:
		ctx->flags |= CGRP_ROOT_XATTR;
		अवरोध;
	हाल Opt_release_agent:
		/* Specअगरying two release agents is क्रमbidden */
		अगर (ctx->release_agent)
			वापस invalfc(fc, "release_agent respecified");
		ctx->release_agent = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_name:
		/* blocked by boot param? */
		अगर (cgroup_no_v1_named)
			वापस -ENOENT;
		/* Can't specअगरy an empty name */
		अगर (!param->size)
			वापस invalfc(fc, "Empty name");
		अगर (param->size > MAX_CGROUP_ROOT_NAMELEN - 1)
			वापस invalfc(fc, "Name too long");
		/* Must match [\w.-]+ */
		क्रम (i = 0; i < param->size; i++) अणु
			अक्षर c = param->string[i];
			अगर (है_अक्षर_अंक(c))
				जारी;
			अगर ((c == '.') || (c == '-') || (c == '_'))
				जारी;
			वापस invalfc(fc, "Invalid name");
		पूर्ण
		/* Specअगरying two names is क्रमbidden */
		अगर (ctx->name)
			वापस invalfc(fc, "name respecified");
		ctx->name = param->string;
		param->string = शून्य;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_cgroupfs_options(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	u16 mask = U16_MAX;
	u16 enabled = 0;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i;

#अगर_घोषित CONFIG_CPUSETS
	mask = ~((u16)1 << cpuset_cgrp_id);
#पूर्ण_अगर
	क्रम_each_subsys(ss, i)
		अगर (cgroup_ssid_enabled(i) && !cgroup1_ssid_disabled(i))
			enabled |= 1 << i;

	ctx->subsys_mask &= enabled;

	/*
	 * In असलence of 'none', 'name=' and subप्रणाली name options,
	 * let's default to 'all'.
	 */
	अगर (!ctx->subsys_mask && !ctx->none && !ctx->name)
		ctx->all_ss = true;

	अगर (ctx->all_ss) अणु
		/* Mutually exclusive option 'all' + subप्रणाली name */
		अगर (ctx->subsys_mask)
			वापस invalfc(fc, "subsys name conflicts with all");
		/* 'all' => select all the subप्रणालीs */
		ctx->subsys_mask = enabled;
	पूर्ण

	/*
	 * We either have to specअगरy by name or by subप्रणालीs. (So all
	 * empty hierarchies must have a name).
	 */
	अगर (!ctx->subsys_mask && !ctx->name)
		वापस invalfc(fc, "Need name or subsystem set");

	/*
	 * Option noprefix was पूर्णांकroduced just क्रम backward compatibility
	 * with the old cpuset, so we allow noprefix only अगर mounting just
	 * the cpuset subप्रणाली.
	 */
	अगर ((ctx->flags & CGRP_ROOT_NOPREFIX) && (ctx->subsys_mask & mask))
		वापस invalfc(fc, "noprefix used incorrectly");

	/* Can't specअगरy "none" and some subप्रणालीs */
	अगर (ctx->subsys_mask && ctx->none)
		वापस invalfc(fc, "none used incorrectly");

	वापस 0;
पूर्ण

पूर्णांक cgroup1_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	काष्ठा kernfs_root *kf_root = kernfs_root_from_sb(fc->root->d_sb);
	काष्ठा cgroup_root *root = cgroup_root_from_kf(kf_root);
	पूर्णांक ret = 0;
	u16 added_mask, हटाओd_mask;

	cgroup_lock_and_drain_offline(&cgrp_dfl_root.cgrp);

	/* See what subप्रणालीs are wanted */
	ret = check_cgroupfs_options(fc);
	अगर (ret)
		जाओ out_unlock;

	अगर (ctx->subsys_mask != root->subsys_mask || ctx->release_agent)
		pr_warn("option changes via remount are deprecated (pid=%d comm=%s)\n",
			task_tgid_nr(current), current->comm);

	added_mask = ctx->subsys_mask & ~root->subsys_mask;
	हटाओd_mask = root->subsys_mask & ~ctx->subsys_mask;

	/* Don't allow flags or name to change at remount */
	अगर ((ctx->flags ^ root->flags) ||
	    (ctx->name && म_भेद(ctx->name, root->name))) अणु
		errorfc(fc, "option or name mismatch, new: 0x%x \"%s\", old: 0x%x \"%s\"",
		       ctx->flags, ctx->name ?: "", root->flags, root->name);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* remounting is not allowed क्रम populated hierarchies */
	अगर (!list_empty(&root->cgrp.self.children)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ret = rebind_subप्रणालीs(root, added_mask);
	अगर (ret)
		जाओ out_unlock;

	WARN_ON(rebind_subप्रणालीs(&cgrp_dfl_root, हटाओd_mask));

	अगर (ctx->release_agent) अणु
		spin_lock(&release_agent_path_lock);
		म_नकल(root->release_agent_path, ctx->release_agent);
		spin_unlock(&release_agent_path_lock);
	पूर्ण

	trace_cgroup_remount(root);

 out_unlock:
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

काष्ठा kernfs_syscall_ops cgroup1_kf_syscall_ops = अणु
	.नाम			= cgroup1_नाम,
	.show_options		= cgroup1_show_options,
	.सूची_गढ़ो			= cgroup_सूची_गढ़ो,
	.सूची_हटाओ			= cgroup_सूची_हटाओ,
	.show_path		= cgroup_show_path,
पूर्ण;

/*
 * The guts of cgroup1 mount - find or create cgroup_root to use.
 * Called with cgroup_mutex held; वापसs 0 on success, -E... on
 * error and positive - in हाल when the candidate is busy dying.
 * On success it stashes a reference to cgroup_root पूर्णांकo given
 * cgroup_fs_context; that reference is *NOT* counting towards the
 * cgroup_root refcount.
 */
अटल पूर्णांक cgroup1_root_to_use(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	काष्ठा cgroup_root *root;
	काष्ठा cgroup_subsys *ss;
	पूर्णांक i, ret;

	/* First find the desired set of subप्रणालीs */
	ret = check_cgroupfs_options(fc);
	अगर (ret)
		वापस ret;

	/*
	 * Deकाष्ठाion of cgroup root is asynchronous, so subप्रणालीs may
	 * still be dying after the previous unmount.  Let's drain the
	 * dying subप्रणालीs.  We just need to ensure that the ones
	 * unmounted previously finish dying and करोn't care about new ones
	 * starting.  Testing ref liveliness is good enough.
	 */
	क्रम_each_subsys(ss, i) अणु
		अगर (!(ctx->subsys_mask & (1 << i)) ||
		    ss->root == &cgrp_dfl_root)
			जारी;

		अगर (!percpu_ref_tryget_live(&ss->root->cgrp.self.refcnt))
			वापस 1;	/* restart */
		cgroup_put(&ss->root->cgrp);
	पूर्ण

	क्रम_each_root(root) अणु
		bool name_match = false;

		अगर (root == &cgrp_dfl_root)
			जारी;

		/*
		 * If we asked क्रम a name then it must match.  Also, अगर
		 * name matches but sybsys_mask करोesn't, we should fail.
		 * Remember whether name matched.
		 */
		अगर (ctx->name) अणु
			अगर (म_भेद(ctx->name, root->name))
				जारी;
			name_match = true;
		पूर्ण

		/*
		 * If we asked क्रम subप्रणालीs (or explicitly क्रम no
		 * subप्रणालीs) then they must match.
		 */
		अगर ((ctx->subsys_mask || ctx->none) &&
		    (ctx->subsys_mask != root->subsys_mask)) अणु
			अगर (!name_match)
				जारी;
			वापस -EBUSY;
		पूर्ण

		अगर (root->flags ^ ctx->flags)
			pr_warn("new mount options do not match the existing superblock, will be ignored\n");

		ctx->root = root;
		वापस 0;
	पूर्ण

	/*
	 * No such thing, create a new one.  name= matching without subsys
	 * specअगरication is allowed क्रम alपढ़ोy existing hierarchies but we
	 * can't create new one without subsys specअगरication.
	 */
	अगर (!ctx->subsys_mask && !ctx->none)
		वापस invalfc(fc, "No subsys list or none specified");

	/* Hierarchies may only be created in the initial cgroup namespace. */
	अगर (ctx->ns != &init_cgroup_ns)
		वापस -EPERM;

	root = kzalloc(माप(*root), GFP_KERNEL);
	अगर (!root)
		वापस -ENOMEM;

	ctx->root = root;
	init_cgroup_root(ctx);

	ret = cgroup_setup_root(root, ctx->subsys_mask);
	अगर (ret)
		cgroup_मुक्त_root(root);
	वापस ret;
पूर्ण

पूर्णांक cgroup1_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा cgroup_fs_context *ctx = cgroup_fc2context(fc);
	पूर्णांक ret;

	/* Check अगर the caller has permission to mount. */
	अगर (!ns_capable(ctx->ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	cgroup_lock_and_drain_offline(&cgrp_dfl_root.cgrp);

	ret = cgroup1_root_to_use(fc);
	अगर (!ret && !percpu_ref_tryget_live(&ctx->root->cgrp.self.refcnt))
		ret = 1;	/* restart */

	mutex_unlock(&cgroup_mutex);

	अगर (!ret)
		ret = cgroup_करो_get_tree(fc);

	अगर (!ret && percpu_ref_is_dying(&ctx->root->cgrp.self.refcnt)) अणु
		काष्ठा super_block *sb = fc->root->d_sb;
		dput(fc->root);
		deactivate_locked_super(sb);
		ret = 1;
	पूर्ण

	अगर (unlikely(ret > 0)) अणु
		msleep(10);
		वापस restart_syscall();
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __init cgroup1_wq_init(व्योम)
अणु
	/*
	 * Used to destroy pidlists and separate to serve as flush करोमुख्य.
	 * Cap @max_active to 1 too.
	 */
	cgroup_pidlist_destroy_wq = alloc_workqueue("cgroup_pidlist_destroy",
						    0, 1);
	BUG_ON(!cgroup_pidlist_destroy_wq);
	वापस 0;
पूर्ण
core_initcall(cgroup1_wq_init);

अटल पूर्णांक __init cgroup_no_v1(अक्षर *str)
अणु
	काष्ठा cgroup_subsys *ss;
	अक्षर *token;
	पूर्णांक i;

	जबतक ((token = strsep(&str, ",")) != शून्य) अणु
		अगर (!*token)
			जारी;

		अगर (!म_भेद(token, "all")) अणु
			cgroup_no_v1_mask = U16_MAX;
			जारी;
		पूर्ण

		अगर (!म_भेद(token, "named")) अणु
			cgroup_no_v1_named = true;
			जारी;
		पूर्ण

		क्रम_each_subsys(ss, i) अणु
			अगर (म_भेद(token, ss->name) &&
			    म_भेद(token, ss->legacy_name))
				जारी;

			cgroup_no_v1_mask |= 1 << i;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
__setup("cgroup_no_v1=", cgroup_no_v1);
