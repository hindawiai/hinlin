<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/ioprio.c
 *
 * Copyright (C) 2004 Jens Axboe <axboe@kernel.dk>
 *
 * Helper functions क्रम setting/querying io priorities of processes. The
 * प्रणाली calls बंदly mimmick getpriority/setpriority, see the man page क्रम
 * those. The prio argument is a composite of prio class and prio data, where
 * the data argument has meaning within that class. The standard scheduling
 * classes have 8 distinct prio levels, with 0 being the highest prio and 7
 * being the lowest.
 *
 * IOW, setting BE scheduling class with prio 2 is करोne ala:
 *
 * अचिन्हित पूर्णांक prio = (IOPRIO_CLASS_BE << IOPRIO_CLASS_SHIFT) | 2;
 *
 * ioprio_set(PRIO_PROCESS, pid, prio);
 *
 * See also Documentation/block/ioprio.rst
 *
 */
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/cred.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/security.h>
#समावेश <linux/pid_namespace.h>

पूर्णांक set_task_ioprio(काष्ठा task_काष्ठा *task, पूर्णांक ioprio)
अणु
	पूर्णांक err;
	काष्ठा io_context *ioc;
	स्थिर काष्ठा cred *cred = current_cred(), *tcred;

	rcu_पढ़ो_lock();
	tcred = __task_cred(task);
	अगर (!uid_eq(tcred->uid, cred->euid) &&
	    !uid_eq(tcred->uid, cred->uid) && !capable(CAP_SYS_NICE)) अणु
		rcu_पढ़ो_unlock();
		वापस -EPERM;
	पूर्ण
	rcu_पढ़ो_unlock();

	err = security_task_setioprio(task, ioprio);
	अगर (err)
		वापस err;

	ioc = get_task_io_context(task, GFP_ATOMIC, NUMA_NO_NODE);
	अगर (ioc) अणु
		ioc->ioprio = ioprio;
		put_io_context(ioc);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(set_task_ioprio);

पूर्णांक ioprio_check_cap(पूर्णांक ioprio)
अणु
	पूर्णांक class = IOPRIO_PRIO_CLASS(ioprio);
	पूर्णांक data = IOPRIO_PRIO_DATA(ioprio);

	चयन (class) अणु
		हाल IOPRIO_CLASS_RT:
			अगर (!capable(CAP_SYS_NICE) && !capable(CAP_SYS_ADMIN))
				वापस -EPERM;
			fallthrough;
			/* rt has prio field too */
		हाल IOPRIO_CLASS_BE:
			अगर (data >= IOPRIO_BE_NR || data < 0)
				वापस -EINVAL;

			अवरोध;
		हाल IOPRIO_CLASS_IDLE:
			अवरोध;
		हाल IOPRIO_CLASS_NONE:
			अगर (data)
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

SYSCALL_DEFINE3(ioprio_set, पूर्णांक, which, पूर्णांक, who, पूर्णांक, ioprio)
अणु
	काष्ठा task_काष्ठा *p, *g;
	काष्ठा user_काष्ठा *user;
	काष्ठा pid *pgrp;
	kuid_t uid;
	पूर्णांक ret;

	ret = ioprio_check_cap(ioprio);
	अगर (ret)
		वापस ret;

	ret = -ESRCH;
	rcu_पढ़ो_lock();
	चयन (which) अणु
		हाल IOPRIO_WHO_PROCESS:
			अगर (!who)
				p = current;
			अन्यथा
				p = find_task_by_vpid(who);
			अगर (p)
				ret = set_task_ioprio(p, ioprio);
			अवरोध;
		हाल IOPRIO_WHO_PGRP:
			अगर (!who)
				pgrp = task_pgrp(current);
			अन्यथा
				pgrp = find_vpid(who);

			पढ़ो_lock(&tasklist_lock);
			करो_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p) अणु
				ret = set_task_ioprio(p, ioprio);
				अगर (ret) अणु
					पढ़ो_unlock(&tasklist_lock);
					जाओ out;
				पूर्ण
			पूर्ण जबतक_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p);
			पढ़ो_unlock(&tasklist_lock);

			अवरोध;
		हाल IOPRIO_WHO_USER:
			uid = make_kuid(current_user_ns(), who);
			अगर (!uid_valid(uid))
				अवरोध;
			अगर (!who)
				user = current_user();
			अन्यथा
				user = find_user(uid);

			अगर (!user)
				अवरोध;

			क्रम_each_process_thपढ़ो(g, p) अणु
				अगर (!uid_eq(task_uid(p), uid) ||
				    !task_pid_vnr(p))
					जारी;
				ret = set_task_ioprio(p, ioprio);
				अगर (ret)
					जाओ मुक्त_uid;
			पूर्ण
मुक्त_uid:
			अगर (who)
				मुक्त_uid(user);
			अवरोध;
		शेष:
			ret = -EINVAL;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक get_task_ioprio(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक ret;

	ret = security_task_getioprio(p);
	अगर (ret)
		जाओ out;
	ret = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, IOPRIO_NORM);
	task_lock(p);
	अगर (p->io_context)
		ret = p->io_context->ioprio;
	task_unlock(p);
out:
	वापस ret;
पूर्ण

पूर्णांक ioprio_best(अचिन्हित लघु aprio, अचिन्हित लघु bprio)
अणु
	अगर (!ioprio_valid(aprio))
		aprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);
	अगर (!ioprio_valid(bprio))
		bprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);

	वापस min(aprio, bprio);
पूर्ण

SYSCALL_DEFINE2(ioprio_get, पूर्णांक, which, पूर्णांक, who)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा user_काष्ठा *user;
	काष्ठा pid *pgrp;
	kuid_t uid;
	पूर्णांक ret = -ESRCH;
	पूर्णांक पंचांगpio;

	rcu_पढ़ो_lock();
	चयन (which) अणु
		हाल IOPRIO_WHO_PROCESS:
			अगर (!who)
				p = current;
			अन्यथा
				p = find_task_by_vpid(who);
			अगर (p)
				ret = get_task_ioprio(p);
			अवरोध;
		हाल IOPRIO_WHO_PGRP:
			अगर (!who)
				pgrp = task_pgrp(current);
			अन्यथा
				pgrp = find_vpid(who);
			करो_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p) अणु
				पंचांगpio = get_task_ioprio(p);
				अगर (पंचांगpio < 0)
					जारी;
				अगर (ret == -ESRCH)
					ret = पंचांगpio;
				अन्यथा
					ret = ioprio_best(ret, पंचांगpio);
			पूर्ण जबतक_each_pid_thपढ़ो(pgrp, PIDTYPE_PGID, p);
			अवरोध;
		हाल IOPRIO_WHO_USER:
			uid = make_kuid(current_user_ns(), who);
			अगर (!who)
				user = current_user();
			अन्यथा
				user = find_user(uid);

			अगर (!user)
				अवरोध;

			क्रम_each_process_thपढ़ो(g, p) अणु
				अगर (!uid_eq(task_uid(p), user->uid) ||
				    !task_pid_vnr(p))
					जारी;
				पंचांगpio = get_task_ioprio(p);
				अगर (पंचांगpio < 0)
					जारी;
				अगर (ret == -ESRCH)
					ret = पंचांगpio;
				अन्यथा
					ret = ioprio_best(ret, पंचांगpio);
			पूर्ण

			अगर (who)
				मुक्त_uid(user);
			अवरोध;
		शेष:
			ret = -EINVAL;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
