<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TASK_WORK_H
#घोषणा _LINUX_TASK_WORK_H

#समावेश <linux/list.h>
#समावेश <linux/sched.h>

प्रकार व्योम (*task_work_func_t)(काष्ठा callback_head *);

अटल अंतरभूत व्योम
init_task_work(काष्ठा callback_head *twork, task_work_func_t func)
अणु
	twork->func = func;
पूर्ण

क्रमागत task_work_notअगरy_mode अणु
	TWA_NONE,
	TWA_RESUME,
	TWA_SIGNAL,
पूर्ण;

पूर्णांक task_work_add(काष्ठा task_काष्ठा *task, काष्ठा callback_head *twork,
			क्रमागत task_work_notअगरy_mode mode);

काष्ठा callback_head *task_work_cancel_match(काष्ठा task_काष्ठा *task,
	bool (*match)(काष्ठा callback_head *, व्योम *data), व्योम *data);
काष्ठा callback_head *task_work_cancel(काष्ठा task_काष्ठा *, task_work_func_t);
व्योम task_work_run(व्योम);

अटल अंतरभूत व्योम निकास_task_work(काष्ठा task_काष्ठा *task)
अणु
	task_work_run();
पूर्ण

#पूर्ण_अगर	/* _LINUX_TASK_WORK_H */
