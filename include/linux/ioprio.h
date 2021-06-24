<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित IOPRIO_H
#घोषणा IOPRIO_H

#समावेश <linux/sched.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/iocontext.h>

/*
 * Gives us 8 prio classes with 13-bits of data क्रम each class
 */
#घोषणा IOPRIO_CLASS_SHIFT	(13)
#घोषणा IOPRIO_PRIO_MASK	((1UL << IOPRIO_CLASS_SHIFT) - 1)

#घोषणा IOPRIO_PRIO_CLASS(mask)	((mask) >> IOPRIO_CLASS_SHIFT)
#घोषणा IOPRIO_PRIO_DATA(mask)	((mask) & IOPRIO_PRIO_MASK)
#घोषणा IOPRIO_PRIO_VALUE(class, data)	(((class) << IOPRIO_CLASS_SHIFT) | data)

#घोषणा ioprio_valid(mask)	(IOPRIO_PRIO_CLASS((mask)) != IOPRIO_CLASS_NONE)

/*
 * These are the io priority groups as implemented by CFQ. RT is the realसमय
 * class, it always माला_लो premium service. BE is the best-efक्रमt scheduling
 * class, the शेष क्रम any process. IDLE is the idle scheduling class, it
 * is only served when no one अन्यथा is using the disk.
 */
क्रमागत अणु
	IOPRIO_CLASS_NONE,
	IOPRIO_CLASS_RT,
	IOPRIO_CLASS_BE,
	IOPRIO_CLASS_IDLE,
पूर्ण;

/*
 * 8 best efक्रमt priority levels are supported
 */
#घोषणा IOPRIO_BE_NR	(8)

क्रमागत अणु
	IOPRIO_WHO_PROCESS = 1,
	IOPRIO_WHO_PGRP,
	IOPRIO_WHO_USER,
पूर्ण;

/*
 * Fallback BE priority
 */
#घोषणा IOPRIO_NORM	(4)

/*
 * अगर process has set io priority explicitly, use that. अगर not, convert
 * the cpu scheduler nice value to an io priority
 */
अटल अंतरभूत पूर्णांक task_nice_ioprio(काष्ठा task_काष्ठा *task)
अणु
	वापस (task_nice(task) + 20) / 5;
पूर्ण

/*
 * This is क्रम the हाल where the task hasn't asked क्रम a specअगरic IO class.
 * Check क्रम idle and rt task process, and वापस appropriate IO class.
 */
अटल अंतरभूत पूर्णांक task_nice_ioclass(काष्ठा task_काष्ठा *task)
अणु
	अगर (task->policy == SCHED_IDLE)
		वापस IOPRIO_CLASS_IDLE;
	अन्यथा अगर (task_is_realसमय(task))
		वापस IOPRIO_CLASS_RT;
	अन्यथा
		वापस IOPRIO_CLASS_BE;
पूर्ण

/*
 * If the calling process has set an I/O priority, use that. Otherwise, वापस
 * the शेष I/O priority.
 */
अटल अंतरभूत पूर्णांक get_current_ioprio(व्योम)
अणु
	काष्ठा io_context *ioc = current->io_context;

	अगर (ioc)
		वापस ioc->ioprio;
	वापस IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, 0);
पूर्ण

/*
 * For inheritance, वापस the highest of the two given priorities
 */
बाह्य पूर्णांक ioprio_best(अचिन्हित लघु aprio, अचिन्हित लघु bprio);

बाह्य पूर्णांक set_task_ioprio(काष्ठा task_काष्ठा *task, पूर्णांक ioprio);

#अगर_घोषित CONFIG_BLOCK
बाह्य पूर्णांक ioprio_check_cap(पूर्णांक ioprio);
#अन्यथा
अटल अंतरभूत पूर्णांक ioprio_check_cap(पूर्णांक ioprio)
अणु
	वापस -ENOTBLK;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

#पूर्ण_अगर
