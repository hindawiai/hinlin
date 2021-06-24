<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_PRIO_H
#घोषणा _LINUX_SCHED_PRIO_H

#घोषणा MAX_NICE	19
#घोषणा MIN_NICE	-20
#घोषणा NICE_WIDTH	(MAX_NICE - MIN_NICE + 1)

/*
 * Priority of a process goes from 0..MAX_PRIO-1, valid RT
 * priority is 0..MAX_RT_PRIO-1, and SCHED_NORMAL/SCHED_BATCH
 * tasks are in the range MAX_RT_PRIO..MAX_PRIO-1. Priority
 * values are inverted: lower p->prio value means higher priority.
 */

#घोषणा MAX_RT_PRIO		100

#घोषणा MAX_PRIO		(MAX_RT_PRIO + NICE_WIDTH)
#घोषणा DEFAULT_PRIO		(MAX_RT_PRIO + NICE_WIDTH / 2)

/*
 * Convert user-nice values [ -20 ... 0 ... 19 ]
 * to अटल priority [ MAX_RT_PRIO..MAX_PRIO-1 ],
 * and back.
 */
#घोषणा NICE_TO_PRIO(nice)	((nice) + DEFAULT_PRIO)
#घोषणा PRIO_TO_NICE(prio)	((prio) - DEFAULT_PRIO)

/*
 * Convert nice value [19,-20] to rlimit style value [1,40].
 */
अटल अंतरभूत दीर्घ nice_to_rlimit(दीर्घ nice)
अणु
	वापस (MAX_NICE - nice + 1);
पूर्ण

/*
 * Convert rlimit style value [1,40] to nice value [-20, 19].
 */
अटल अंतरभूत दीर्घ rlimit_to_nice(दीर्घ prio)
अणु
	वापस (MAX_NICE - prio + 1);
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_PRIO_H */
