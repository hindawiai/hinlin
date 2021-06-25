<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/oom.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <skas.h>

व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

अटल व्योम समाप्त_off_processes(व्योम)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक pid;

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process(p) अणु
		काष्ठा task_काष्ठा *t;

		t = find_lock_task_mm(p);
		अगर (!t)
			जारी;
		pid = t->mm->context.id.u.pid;
		task_unlock(t);
		os_समाप्त_ptraced_process(pid, 1);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

व्योम uml_cleanup(व्योम)
अणु
	kदो_स्मृति_ok = 0;
	करो_uml_निकासcalls();
	समाप्त_off_processes();
पूर्ण

व्योम machine_restart(अक्षर * __unused)
अणु
	uml_cleanup();
	reboot_skas();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	uml_cleanup();
	halt_skas();
पूर्ण

व्योम machine_halt(व्योम)
अणु
	machine_घातer_off();
पूर्ण
