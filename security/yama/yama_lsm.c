<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Yama Linux Security Module
 *
 * Author: Kees Cook <keescook@chromium.org>
 *
 * Copyright (C) 2010 Canonical, Ltd.
 * Copyright (C) 2011 The Chromium OS Authors.
 */

#समावेश <linux/lsm_hooks.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/prctl.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/task_work.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>

#घोषणा YAMA_SCOPE_DISABLED	0
#घोषणा YAMA_SCOPE_RELATIONAL	1
#घोषणा YAMA_SCOPE_CAPABILITY	2
#घोषणा YAMA_SCOPE_NO_ATTACH	3

अटल पूर्णांक ptrace_scope = YAMA_SCOPE_RELATIONAL;

/* describe a ptrace relationship क्रम potential exception */
काष्ठा ptrace_relation अणु
	काष्ठा task_काष्ठा *tracer;
	काष्ठा task_काष्ठा *tracee;
	bool invalid;
	काष्ठा list_head node;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल LIST_HEAD(ptracer_relations);
अटल DEFINE_SPINLOCK(ptracer_relations_lock);

अटल व्योम yama_relation_cleanup(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(yama_relation_work, yama_relation_cleanup);

काष्ठा access_report_info अणु
	काष्ठा callback_head work;
	स्थिर अक्षर *access;
	काष्ठा task_काष्ठा *target;
	काष्ठा task_काष्ठा *agent;
पूर्ण;

अटल व्योम __report_access(काष्ठा callback_head *work)
अणु
	काष्ठा access_report_info *info =
		container_of(work, काष्ठा access_report_info, work);
	अक्षर *target_cmd, *agent_cmd;

	target_cmd = kstrdup_quotable_cmdline(info->target, GFP_KERNEL);
	agent_cmd = kstrdup_quotable_cmdline(info->agent, GFP_KERNEL);

	pr_notice_ratelimited(
		"ptrace %s of \"%s\"[%d] was attempted by \"%s\"[%d]\n",
		info->access, target_cmd, info->target->pid, agent_cmd,
		info->agent->pid);

	kमुक्त(agent_cmd);
	kमुक्त(target_cmd);

	put_task_काष्ठा(info->agent);
	put_task_काष्ठा(info->target);
	kमुक्त(info);
पूर्ण

/* defers execution because cmdline access can sleep */
अटल व्योम report_access(स्थिर अक्षर *access, काष्ठा task_काष्ठा *target,
				काष्ठा task_काष्ठा *agent)
अणु
	काष्ठा access_report_info *info;
	अक्षर agent_comm[माप(agent->comm)];

	निश्चित_spin_locked(&target->alloc_lock); /* क्रम target->comm */

	अगर (current->flags & PF_KTHREAD) अणु
		/* I करोn't think kthपढ़ोs call task_work_run() beक्रमe निकासing.
		 * Imagine angry ranting about procfs here.
		 */
		pr_notice_ratelimited(
		    "ptrace %s of \"%s\"[%d] was attempted by \"%s\"[%d]\n",
		    access, target->comm, target->pid,
		    get_task_comm(agent_comm, agent), agent->pid);
		वापस;
	पूर्ण

	info = kदो_स्मृति(माप(*info), GFP_ATOMIC);
	अगर (!info)
		वापस;
	init_task_work(&info->work, __report_access);
	get_task_काष्ठा(target);
	get_task_काष्ठा(agent);
	info->access = access;
	info->target = target;
	info->agent = agent;
	अगर (task_work_add(current, &info->work, TWA_RESUME) == 0)
		वापस; /* success */

	WARN(1, "report_access called from exiting task");
	put_task_काष्ठा(target);
	put_task_काष्ठा(agent);
	kमुक्त(info);
पूर्ण

/**
 * yama_relation_cleanup - हटाओ invalid entries from the relation list
 *
 */
अटल व्योम yama_relation_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ptrace_relation *relation;

	spin_lock(&ptracer_relations_lock);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(relation, &ptracer_relations, node) अणु
		अगर (relation->invalid) अणु
			list_del_rcu(&relation->node);
			kमुक्त_rcu(relation, rcu);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock(&ptracer_relations_lock);
पूर्ण

/**
 * yama_ptracer_add - add/replace an exception क्रम this tracer/tracee pair
 * @tracer: the task_काष्ठा of the process करोing the ptrace
 * @tracee: the task_काष्ठा of the process to be ptraced
 *
 * Each tracee can have, at most, one tracer रेजिस्टरed. Each समय this
 * is called, the prior रेजिस्टरed tracer will be replaced क्रम the tracee.
 *
 * Returns 0 अगर relationship was added, -ve on error.
 */
अटल पूर्णांक yama_ptracer_add(काष्ठा task_काष्ठा *tracer,
			    काष्ठा task_काष्ठा *tracee)
अणु
	काष्ठा ptrace_relation *relation, *added;

	added = kदो_स्मृति(माप(*added), GFP_KERNEL);
	अगर (!added)
		वापस -ENOMEM;

	added->tracee = tracee;
	added->tracer = tracer;
	added->invalid = false;

	spin_lock(&ptracer_relations_lock);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(relation, &ptracer_relations, node) अणु
		अगर (relation->invalid)
			जारी;
		अगर (relation->tracee == tracee) अणु
			list_replace_rcu(&relation->node, &added->node);
			kमुक्त_rcu(relation, rcu);
			जाओ out;
		पूर्ण
	पूर्ण

	list_add_rcu(&added->node, &ptracer_relations);

out:
	rcu_पढ़ो_unlock();
	spin_unlock(&ptracer_relations_lock);
	वापस 0;
पूर्ण

/**
 * yama_ptracer_del - हटाओ exceptions related to the given tasks
 * @tracer: हटाओ any relation where tracer task matches
 * @tracee: हटाओ any relation where tracee task matches
 */
अटल व्योम yama_ptracer_del(काष्ठा task_काष्ठा *tracer,
			     काष्ठा task_काष्ठा *tracee)
अणु
	काष्ठा ptrace_relation *relation;
	bool marked = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(relation, &ptracer_relations, node) अणु
		अगर (relation->invalid)
			जारी;
		अगर (relation->tracee == tracee ||
		    (tracer && relation->tracer == tracer)) अणु
			relation->invalid = true;
			marked = true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (marked)
		schedule_work(&yama_relation_work);
पूर्ण

/**
 * yama_task_मुक्त - check क्रम task_pid to हटाओ from exception list
 * @task: task being हटाओd
 */
अटल व्योम yama_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	yama_ptracer_del(task, task);
पूर्ण

/**
 * yama_task_prctl - check क्रम Yama-specअगरic prctl operations
 * @option: operation
 * @arg2: argument
 * @arg3: argument
 * @arg4: argument
 * @arg5: argument
 *
 * Return 0 on success, -ve on error.  -ENOSYS is वापसed when Yama
 * करोes not handle the given option.
 */
अटल पूर्णांक yama_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			   अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	पूर्णांक rc = -ENOSYS;
	काष्ठा task_काष्ठा *myself = current;

	चयन (option) अणु
	हाल PR_SET_PTRACER:
		/* Since a thपढ़ो can call prctl(), find the group leader
		 * beक्रमe calling _add() or _del() on it, since we want
		 * process-level granularity of control. The tracer group
		 * leader checking is handled later when walking the ancestry
		 * at the समय of PTRACE_ATTACH check.
		 */
		rcu_पढ़ो_lock();
		अगर (!thपढ़ो_group_leader(myself))
			myself = rcu_dereference(myself->group_leader);
		get_task_काष्ठा(myself);
		rcu_पढ़ो_unlock();

		अगर (arg2 == 0) अणु
			yama_ptracer_del(शून्य, myself);
			rc = 0;
		पूर्ण अन्यथा अगर (arg2 == PR_SET_PTRACER_ANY || (पूर्णांक)arg2 == -1) अणु
			rc = yama_ptracer_add(शून्य, myself);
		पूर्ण अन्यथा अणु
			काष्ठा task_काष्ठा *tracer;

			tracer = find_get_task_by_vpid(arg2);
			अगर (!tracer) अणु
				rc = -EINVAL;
			पूर्ण अन्यथा अणु
				rc = yama_ptracer_add(tracer, myself);
				put_task_काष्ठा(tracer);
			पूर्ण
		पूर्ण

		put_task_काष्ठा(myself);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * task_is_descendant - walk up a process family tree looking क्रम a match
 * @parent: the process to compare against जबतक walking up from child
 * @child: the process to start from जबतक looking upwards क्रम parent
 *
 * Returns 1 अगर child is a descendant of parent, 0 अगर not.
 */
अटल पूर्णांक task_is_descendant(काष्ठा task_काष्ठा *parent,
			      काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक rc = 0;
	काष्ठा task_काष्ठा *walker = child;

	अगर (!parent || !child)
		वापस 0;

	rcu_पढ़ो_lock();
	अगर (!thपढ़ो_group_leader(parent))
		parent = rcu_dereference(parent->group_leader);
	जबतक (walker->pid > 0) अणु
		अगर (!thपढ़ो_group_leader(walker))
			walker = rcu_dereference(walker->group_leader);
		अगर (walker == parent) अणु
			rc = 1;
			अवरोध;
		पूर्ण
		walker = rcu_dereference(walker->real_parent);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/**
 * ptracer_exception_found - tracer रेजिस्टरed as exception क्रम this tracee
 * @tracer: the task_काष्ठा of the process attempting ptrace
 * @tracee: the task_काष्ठा of the process to be ptraced
 *
 * Returns 1 अगर tracer has a ptracer exception ancestor क्रम tracee.
 */
अटल पूर्णांक ptracer_exception_found(काष्ठा task_काष्ठा *tracer,
				   काष्ठा task_काष्ठा *tracee)
अणु
	पूर्णांक rc = 0;
	काष्ठा ptrace_relation *relation;
	काष्ठा task_काष्ठा *parent = शून्य;
	bool found = false;

	rcu_पढ़ो_lock();

	/*
	 * If there's alपढ़ोy an active tracing relationship, then make an
	 * exception क्रम the sake of other accesses, like process_vm_rw().
	 */
	parent = ptrace_parent(tracee);
	अगर (parent != शून्य && same_thपढ़ो_group(parent, tracer)) अणु
		rc = 1;
		जाओ unlock;
	पूर्ण

	/* Look क्रम a PR_SET_PTRACER relationship. */
	अगर (!thपढ़ो_group_leader(tracee))
		tracee = rcu_dereference(tracee->group_leader);
	list_क्रम_each_entry_rcu(relation, &ptracer_relations, node) अणु
		अगर (relation->invalid)
			जारी;
		अगर (relation->tracee == tracee) अणु
			parent = relation->tracer;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found && (parent == शून्य || task_is_descendant(parent, tracer)))
		rc = 1;

unlock:
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/**
 * yama_ptrace_access_check - validate PTRACE_ATTACH calls
 * @child: task that current task is attempting to ptrace
 * @mode: ptrace attach mode
 *
 * Returns 0 अगर following the ptrace is allowed, -ve on error.
 */
अटल पूर्णांक yama_ptrace_access_check(काष्ठा task_काष्ठा *child,
				    अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक rc = 0;

	/* require ptrace target be a child of ptracer on attach */
	अगर (mode & PTRACE_MODE_ATTACH) अणु
		चयन (ptrace_scope) अणु
		हाल YAMA_SCOPE_DISABLED:
			/* No additional restrictions. */
			अवरोध;
		हाल YAMA_SCOPE_RELATIONAL:
			rcu_पढ़ो_lock();
			अगर (!pid_alive(child))
				rc = -EPERM;
			अगर (!rc && !task_is_descendant(current, child) &&
			    !ptracer_exception_found(current, child) &&
			    !ns_capable(__task_cred(child)->user_ns, CAP_SYS_PTRACE))
				rc = -EPERM;
			rcu_पढ़ो_unlock();
			अवरोध;
		हाल YAMA_SCOPE_CAPABILITY:
			rcu_पढ़ो_lock();
			अगर (!ns_capable(__task_cred(child)->user_ns, CAP_SYS_PTRACE))
				rc = -EPERM;
			rcu_पढ़ो_unlock();
			अवरोध;
		हाल YAMA_SCOPE_NO_ATTACH:
		शेष:
			rc = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc && (mode & PTRACE_MODE_NOAUDIT) == 0)
		report_access("attach", child, current);

	वापस rc;
पूर्ण

/**
 * yama_ptrace_traceme - validate PTRACE_TRACEME calls
 * @parent: task that will become the ptracer of the current task
 *
 * Returns 0 अगर following the ptrace is allowed, -ve on error.
 */
अटल पूर्णांक yama_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	पूर्णांक rc = 0;

	/* Only disallow PTRACE_TRACEME on more aggressive settings. */
	चयन (ptrace_scope) अणु
	हाल YAMA_SCOPE_CAPABILITY:
		अगर (!has_ns_capability(parent, current_user_ns(), CAP_SYS_PTRACE))
			rc = -EPERM;
		अवरोध;
	हाल YAMA_SCOPE_NO_ATTACH:
		rc = -EPERM;
		अवरोध;
	पूर्ण

	अगर (rc) अणु
		task_lock(current);
		report_access("traceme", current, parent);
		task_unlock(current);
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा security_hook_list yama_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(ptrace_access_check, yama_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, yama_ptrace_traceme),
	LSM_HOOK_INIT(task_prctl, yama_task_prctl),
	LSM_HOOK_INIT(task_मुक्त, yama_task_मुक्त),
पूर्ण;

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक yama_करोपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table table_copy;

	अगर (ग_लिखो && !capable(CAP_SYS_PTRACE))
		वापस -EPERM;

	/* Lock the max value अगर it ever माला_लो set. */
	table_copy = *table;
	अगर (*(पूर्णांक *)table_copy.data == *(पूर्णांक *)table_copy.extra2)
		table_copy.extra1 = table_copy.extra2;

	वापस proc_करोपूर्णांकvec_minmax(&table_copy, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक max_scope = YAMA_SCOPE_NO_ATTACH;

अटल काष्ठा ctl_path yama_sysctl_path[] = अणु
	अणु .procname = "kernel", पूर्ण,
	अणु .procname = "yama", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table yama_sysctl_table[] = अणु
	अणु
		.procname       = "ptrace_scope",
		.data           = &ptrace_scope,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = yama_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = &max_scope,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल व्योम __init yama_init_sysctl(व्योम)
अणु
	अगर (!रेजिस्टर_sysctl_paths(yama_sysctl_path, yama_sysctl_table))
		panic("Yama: sysctl registration failed.\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम yama_init_sysctl(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल पूर्णांक __init yama_init(व्योम)
अणु
	pr_info("Yama: becoming mindful.\n");
	security_add_hooks(yama_hooks, ARRAY_SIZE(yama_hooks), "yama");
	yama_init_sysctl();
	वापस 0;
पूर्ण

DEFINE_LSM(yama) = अणु
	.name = "yama",
	.init = yama_init,
पूर्ण;
