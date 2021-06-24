<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Auto-group scheduling implementation:
 */
#समावेश <linux/nospec.h>
#समावेश "sched.h"

अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_sched_स्वतःgroup_enabled = 1;
अटल काष्ठा स्वतःgroup स्वतःgroup_शेष;
अटल atomic_t स्वतःgroup_seq_nr;

व्योम __init स्वतःgroup_init(काष्ठा task_काष्ठा *init_task)
अणु
	स्वतःgroup_शेष.tg = &root_task_group;
	kref_init(&स्वतःgroup_शेष.kref);
	init_rwsem(&स्वतःgroup_शेष.lock);
	init_task->संकेत->स्वतःgroup = &स्वतःgroup_शेष;
पूर्ण

व्योम स्वतःgroup_मुक्त(काष्ठा task_group *tg)
अणु
	kमुक्त(tg->स्वतःgroup);
पूर्ण

अटल अंतरभूत व्योम स्वतःgroup_destroy(काष्ठा kref *kref)
अणु
	काष्ठा स्वतःgroup *ag = container_of(kref, काष्ठा स्वतःgroup, kref);

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	/* We've redirected RT tasks to the root task group... */
	ag->tg->rt_se = शून्य;
	ag->tg->rt_rq = शून्य;
#पूर्ण_अगर
	sched_offline_group(ag->tg);
	sched_destroy_group(ag->tg);
पूर्ण

अटल अंतरभूत व्योम स्वतःgroup_kref_put(काष्ठा स्वतःgroup *ag)
अणु
	kref_put(&ag->kref, स्वतःgroup_destroy);
पूर्ण

अटल अंतरभूत काष्ठा स्वतःgroup *स्वतःgroup_kref_get(काष्ठा स्वतःgroup *ag)
अणु
	kref_get(&ag->kref);
	वापस ag;
पूर्ण

अटल अंतरभूत काष्ठा स्वतःgroup *स्वतःgroup_task_get(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा स्वतःgroup *ag;
	अचिन्हित दीर्घ flags;

	अगर (!lock_task_sighand(p, &flags))
		वापस स्वतःgroup_kref_get(&स्वतःgroup_शेष);

	ag = स्वतःgroup_kref_get(p->संकेत->स्वतःgroup);
	unlock_task_sighand(p, &flags);

	वापस ag;
पूर्ण

अटल अंतरभूत काष्ठा स्वतःgroup *स्वतःgroup_create(व्योम)
अणु
	काष्ठा स्वतःgroup *ag = kzalloc(माप(*ag), GFP_KERNEL);
	काष्ठा task_group *tg;

	अगर (!ag)
		जाओ out_fail;

	tg = sched_create_group(&root_task_group);
	अगर (IS_ERR(tg))
		जाओ out_मुक्त;

	kref_init(&ag->kref);
	init_rwsem(&ag->lock);
	ag->id = atomic_inc_वापस(&स्वतःgroup_seq_nr);
	ag->tg = tg;
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	/*
	 * Autogroup RT tasks are redirected to the root task group
	 * so we करोn't have to move tasks around upon policy change,
	 * or flail around trying to allocate bandwidth on the fly.
	 * A bandwidth exception in __sched_setscheduler() allows
	 * the policy change to proceed.
	 */
	मुक्त_rt_sched_group(tg);
	tg->rt_se = root_task_group.rt_se;
	tg->rt_rq = root_task_group.rt_rq;
#पूर्ण_अगर
	tg->स्वतःgroup = ag;

	sched_online_group(tg, &root_task_group);
	वापस ag;

out_मुक्त:
	kमुक्त(ag);
out_fail:
	अगर (prपूर्णांकk_ratelimit()) अणु
		prपूर्णांकk(KERN_WARNING "autogroup_create: %s failure.\n",
			ag ? "sched_create_group()" : "kzalloc()");
	पूर्ण

	वापस स्वतःgroup_kref_get(&स्वतःgroup_शेष);
पूर्ण

bool task_wants_स्वतःgroup(काष्ठा task_काष्ठा *p, काष्ठा task_group *tg)
अणु
	अगर (tg != &root_task_group)
		वापस false;
	/*
	 * If we race with स्वतःgroup_move_group() the caller can use the old
	 * value of संकेत->स्वतःgroup but in this हाल sched_move_task() will
	 * be called again beक्रमe स्वतःgroup_kref_put().
	 *
	 * However, there is no way sched_स्वतःgroup_निकास_task() could tell us
	 * to aव्योम स्वतःgroup->tg, so we abuse PF_EXITING flag क्रम this हाल.
	 */
	अगर (p->flags & PF_EXITING)
		वापस false;

	वापस true;
पूर्ण

व्योम sched_स्वतःgroup_निकास_task(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * We are going to call निकास_notअगरy() and स्वतःgroup_move_group() can't
	 * see this thपढ़ो after that: we can no दीर्घer use संकेत->स्वतःgroup.
	 * See the PF_EXITING check in task_wants_स्वतःgroup().
	 */
	sched_move_task(p);
पूर्ण

अटल व्योम
स्वतःgroup_move_group(काष्ठा task_काष्ठा *p, काष्ठा स्वतःgroup *ag)
अणु
	काष्ठा स्वतःgroup *prev;
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ flags;

	BUG_ON(!lock_task_sighand(p, &flags));

	prev = p->संकेत->स्वतःgroup;
	अगर (prev == ag) अणु
		unlock_task_sighand(p, &flags);
		वापस;
	पूर्ण

	p->संकेत->स्वतःgroup = स्वतःgroup_kref_get(ag);
	/*
	 * We can't aव्योम sched_move_task() after we changed संकेत->स्वतःgroup,
	 * this process can alपढ़ोy run with task_group() == prev->tg or we can
	 * race with cgroup code which can पढ़ो स्वतःgroup = prev under rq->lock.
	 * In the latter हाल क्रम_each_thपढ़ो() can not miss a migrating thपढ़ो,
	 * cpu_cgroup_attach() must not be possible after cgroup_निकास() and it
	 * can't be हटाओd from thपढ़ो list, we hold ->siglock.
	 *
	 * If an निकासing thपढ़ो was alपढ़ोy हटाओd from thपढ़ो list we rely on
	 * sched_स्वतःgroup_निकास_task().
	 */
	क्रम_each_thपढ़ो(p, t)
		sched_move_task(t);

	unlock_task_sighand(p, &flags);
	स्वतःgroup_kref_put(prev);
पूर्ण

/* Allocates GFP_KERNEL, cannot be called under any spinlock: */
व्योम sched_स्वतःgroup_create_attach(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा स्वतःgroup *ag = स्वतःgroup_create();

	स्वतःgroup_move_group(p, ag);

	/* Drop extra reference added by स्वतःgroup_create(): */
	स्वतःgroup_kref_put(ag);
पूर्ण
EXPORT_SYMBOL(sched_स्वतःgroup_create_attach);

/* Cannot be called under siglock. Currently has no users: */
व्योम sched_स्वतःgroup_detach(काष्ठा task_काष्ठा *p)
अणु
	स्वतःgroup_move_group(p, &स्वतःgroup_शेष);
पूर्ण
EXPORT_SYMBOL(sched_स्वतःgroup_detach);

व्योम sched_स्वतःgroup_विभाजन(काष्ठा संकेत_काष्ठा *sig)
अणु
	sig->स्वतःgroup = स्वतःgroup_task_get(current);
पूर्ण

व्योम sched_स्वतःgroup_निकास(काष्ठा संकेत_काष्ठा *sig)
अणु
	स्वतःgroup_kref_put(sig->स्वतःgroup);
पूर्ण

अटल पूर्णांक __init setup_स्वतःgroup(अक्षर *str)
अणु
	sysctl_sched_स्वतःgroup_enabled = 0;

	वापस 1;
पूर्ण
__setup("noautogroup", setup_स्वतःgroup);

#अगर_घोषित CONFIG_PROC_FS

पूर्णांक proc_sched_स्वतःgroup_set_nice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	अटल अचिन्हित दीर्घ next = INITIAL_JIFFIES;
	काष्ठा स्वतःgroup *ag;
	अचिन्हित दीर्घ shares;
	पूर्णांक err, idx;

	अगर (nice < MIN_NICE || nice > MAX_NICE)
		वापस -EINVAL;

	err = security_task_setnice(current, nice);
	अगर (err)
		वापस err;

	अगर (nice < 0 && !can_nice(current, nice))
		वापस -EPERM;

	/* This is a heavy operation, taking global locks.. */
	अगर (!capable(CAP_SYS_ADMIN) && समय_beक्रमe(jअगरfies, next))
		वापस -EAGAIN;

	next = HZ / 10 + jअगरfies;
	ag = स्वतःgroup_task_get(p);

	idx = array_index_nospec(nice + 20, 40);
	shares = scale_load(sched_prio_to_weight[idx]);

	करोwn_ग_लिखो(&ag->lock);
	err = sched_group_set_shares(ag->tg, shares);
	अगर (!err)
		ag->nice = nice;
	up_ग_लिखो(&ag->lock);

	स्वतःgroup_kref_put(ag);

	वापस err;
पूर्ण

व्योम proc_sched_स्वतःgroup_show_task(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m)
अणु
	काष्ठा स्वतःgroup *ag = स्वतःgroup_task_get(p);

	अगर (!task_group_is_स्वतःgroup(ag->tg))
		जाओ out;

	करोwn_पढ़ो(&ag->lock);
	seq_म_लिखो(m, "/autogroup-%ld nice %d\n", ag->id, ag->nice);
	up_पढ़ो(&ag->lock);

out:
	स्वतःgroup_kref_put(ag);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

पूर्णांक स्वतःgroup_path(काष्ठा task_group *tg, अक्षर *buf, पूर्णांक buflen)
अणु
	अगर (!task_group_is_स्वतःgroup(tg))
		वापस 0;

	वापस snम_लिखो(buf, buflen, "%s-%ld", "/autogroup", tg->स्वतःgroup->id);
पूर्ण
