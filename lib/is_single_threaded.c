<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Function to determine अगर a thपढ़ो group is single thपढ़ोed or not
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 * - Derived from security/selinux/hooks.c
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/mm.h>

/*
 * Returns true अगर the task करोes not share ->mm with another thपढ़ो/process.
 */
bool current_is_single_thपढ़ोed(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा mm_काष्ठा *mm = task->mm;
	काष्ठा task_काष्ठा *p, *t;
	bool ret;

	अगर (atomic_पढ़ो(&task->संकेत->live) != 1)
		वापस false;

	अगर (atomic_पढ़ो(&mm->mm_users) == 1)
		वापस true;

	ret = false;
	rcu_पढ़ो_lock();
	क्रम_each_process(p) अणु
		अगर (unlikely(p->flags & PF_KTHREAD))
			जारी;
		अगर (unlikely(p == task->group_leader))
			जारी;

		क्रम_each_thपढ़ो(p, t) अणु
			अगर (unlikely(t->mm == mm))
				जाओ found;
			अगर (likely(t->mm))
				अवरोध;
			/*
			 * t->mm == शून्य. Make sure next_thपढ़ो/next_task
			 * will see other CLONE_VM tasks which might be
			 * विभाजनed beक्रमe निकासing.
			 */
			smp_rmb();
		पूर्ण
	पूर्ण
	ret = true;
found:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
