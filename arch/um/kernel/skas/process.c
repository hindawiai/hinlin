<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/task.h>

#समावेश <as-layout.h>
#समावेश <kern.h>
#समावेश <os.h>
#समावेश <skas.h>

बाह्य व्योम start_kernel(व्योम);

अटल पूर्णांक __init start_kernel_proc(व्योम *unused)
अणु
	पूर्णांक pid;

	block_संकेतs_trace();
	pid = os_getpid();

	cpu_tasks[0].pid = pid;
	cpu_tasks[0].task = current;

	start_kernel();
	वापस 0;
पूर्ण

बाह्य पूर्णांक userspace_pid[];

बाह्य अक्षर cpu0_irqstack[];

पूर्णांक __init start_uml(व्योम)
अणु
	stack_protections((अचिन्हित दीर्घ) &cpu0_irqstack);
	set_sigstack(cpu0_irqstack, THREAD_SIZE);

	init_new_thपढ़ो_संकेतs();

	init_task.thपढ़ो.request.u.thपढ़ो.proc = start_kernel_proc;
	init_task.thपढ़ो.request.u.thपढ़ो.arg = शून्य;
	वापस start_idle_thपढ़ो(task_stack_page(&init_task),
				 &init_task.thपढ़ो.चयन_buf);
पूर्ण

अचिन्हित दीर्घ current_stub_stack(व्योम)
अणु
	अगर (current->mm == शून्य)
		वापस 0;

	वापस current->mm->context.id.stack;
पूर्ण
