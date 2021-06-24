<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_JOBCTL_H
#घोषणा _LINUX_SCHED_JOBCTL_H

#समावेश <linux/types.h>

काष्ठा task_काष्ठा;

/*
 * task->jobctl flags
 */
#घोषणा JOBCTL_STOP_SIGMASK	0xffff	/* signr of the last group stop */

#घोषणा JOBCTL_STOP_DEQUEUED_BIT 16	/* stop संकेत dequeued */
#घोषणा JOBCTL_STOP_PENDING_BIT	17	/* task should stop क्रम group stop */
#घोषणा JOBCTL_STOP_CONSUME_BIT	18	/* consume group stop count */
#घोषणा JOBCTL_TRAP_STOP_BIT	19	/* trap क्रम STOP */
#घोषणा JOBCTL_TRAP_NOTIFY_BIT	20	/* trap क्रम NOTIFY */
#घोषणा JOBCTL_TRAPPING_BIT	21	/* चयनing to TRACED */
#घोषणा JOBCTL_LISTENING_BIT	22	/* ptracer is listening क्रम events */
#घोषणा JOBCTL_TRAP_FREEZE_BIT	23	/* trap क्रम cgroup मुक्तzer */

#घोषणा JOBCTL_STOP_DEQUEUED	(1UL << JOBCTL_STOP_DEQUEUED_BIT)
#घोषणा JOBCTL_STOP_PENDING	(1UL << JOBCTL_STOP_PENDING_BIT)
#घोषणा JOBCTL_STOP_CONSUME	(1UL << JOBCTL_STOP_CONSUME_BIT)
#घोषणा JOBCTL_TRAP_STOP	(1UL << JOBCTL_TRAP_STOP_BIT)
#घोषणा JOBCTL_TRAP_NOTIFY	(1UL << JOBCTL_TRAP_NOTIFY_BIT)
#घोषणा JOBCTL_TRAPPING		(1UL << JOBCTL_TRAPPING_BIT)
#घोषणा JOBCTL_LISTENING	(1UL << JOBCTL_LISTENING_BIT)
#घोषणा JOBCTL_TRAP_FREEZE	(1UL << JOBCTL_TRAP_FREEZE_BIT)

#घोषणा JOBCTL_TRAP_MASK	(JOBCTL_TRAP_STOP | JOBCTL_TRAP_NOTIFY)
#घोषणा JOBCTL_PENDING_MASK	(JOBCTL_STOP_PENDING | JOBCTL_TRAP_MASK)

बाह्य bool task_set_jobctl_pending(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ mask);
बाह्य व्योम task_clear_jobctl_trapping(काष्ठा task_काष्ठा *task);
बाह्य व्योम task_clear_jobctl_pending(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ mask);

#पूर्ण_अगर /* _LINUX_SCHED_JOBCTL_H */
