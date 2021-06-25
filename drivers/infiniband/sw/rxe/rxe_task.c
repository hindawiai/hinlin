<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hardirq.h>

#समावेश "rxe_task.h"

पूर्णांक __rxe_करो_task(काष्ठा rxe_task *task)

अणु
	पूर्णांक ret;

	जबतक ((ret = task->func(task->arg)) == 0)
		;

	task->ret = ret;

	वापस ret;
पूर्ण

/*
 * this locking is due to a potential race where
 * a second caller finds the task alपढ़ोy running
 * but looks just after the last call to func
 */
व्योम rxe_करो_task(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक cont;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा rxe_task *task = from_tasklet(task, t, tasklet);

	spin_lock_irqsave(&task->state_lock, flags);
	चयन (task->state) अणु
	हाल TASK_STATE_START:
		task->state = TASK_STATE_BUSY;
		spin_unlock_irqrestore(&task->state_lock, flags);
		अवरोध;

	हाल TASK_STATE_BUSY:
		task->state = TASK_STATE_ARMED;
		fallthrough;
	हाल TASK_STATE_ARMED:
		spin_unlock_irqrestore(&task->state_lock, flags);
		वापस;

	शेष:
		spin_unlock_irqrestore(&task->state_lock, flags);
		pr_warn("%s failed with bad state %d\n", __func__, task->state);
		वापस;
	पूर्ण

	करो अणु
		cont = 0;
		ret = task->func(task->arg);

		spin_lock_irqsave(&task->state_lock, flags);
		चयन (task->state) अणु
		हाल TASK_STATE_BUSY:
			अगर (ret)
				task->state = TASK_STATE_START;
			अन्यथा
				cont = 1;
			अवरोध;

		/* soneone tried to run the task since the last समय we called
		 * func, so we will call one more समय regardless of the
		 * वापस value
		 */
		हाल TASK_STATE_ARMED:
			task->state = TASK_STATE_BUSY;
			cont = 1;
			अवरोध;

		शेष:
			pr_warn("%s failed with bad state %d\n", __func__,
				task->state);
		पूर्ण
		spin_unlock_irqrestore(&task->state_lock, flags);
	पूर्ण जबतक (cont);

	task->ret = ret;
पूर्ण

पूर्णांक rxe_init_task(व्योम *obj, काष्ठा rxe_task *task,
		  व्योम *arg, पूर्णांक (*func)(व्योम *), अक्षर *name)
अणु
	task->obj	= obj;
	task->arg	= arg;
	task->func	= func;
	snम_लिखो(task->name, माप(task->name), "%s", name);
	task->destroyed	= false;

	tasklet_setup(&task->tasklet, rxe_करो_task);

	task->state = TASK_STATE_START;
	spin_lock_init(&task->state_lock);

	वापस 0;
पूर्ण

व्योम rxe_cleanup_task(काष्ठा rxe_task *task)
अणु
	अचिन्हित दीर्घ flags;
	bool idle;

	/*
	 * Mark the task, then रुको क्रम it to finish. It might be
	 * running in a non-tasklet (direct call) context.
	 */
	task->destroyed = true;

	करो अणु
		spin_lock_irqsave(&task->state_lock, flags);
		idle = (task->state == TASK_STATE_START);
		spin_unlock_irqrestore(&task->state_lock, flags);
	पूर्ण जबतक (!idle);

	tasklet_समाप्त(&task->tasklet);
पूर्ण

व्योम rxe_run_task(काष्ठा rxe_task *task, पूर्णांक sched)
अणु
	अगर (task->destroyed)
		वापस;

	अगर (sched)
		tasklet_schedule(&task->tasklet);
	अन्यथा
		rxe_करो_task(&task->tasklet);
पूर्ण

व्योम rxe_disable_task(काष्ठा rxe_task *task)
अणु
	tasklet_disable(&task->tasklet);
पूर्ण

व्योम rxe_enable_task(काष्ठा rxe_task *task)
अणु
	tasklet_enable(&task->tasklet);
पूर्ण
