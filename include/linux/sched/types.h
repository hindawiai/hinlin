<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_TYPES_H
#घोषणा _LINUX_SCHED_TYPES_H

#समावेश <linux/types.h>

/**
 * काष्ठा task_cpuसमय - collected CPU समय counts
 * @sसमय:		समय spent in kernel mode, in nanoseconds
 * @uसमय:		समय spent in user mode, in nanoseconds
 * @sum_exec_runसमय:	total समय spent on the CPU, in nanoseconds
 *
 * This काष्ठाure groups together three kinds of CPU समय that are tracked क्रम
 * thपढ़ोs and thपढ़ो groups.  Most things considering CPU समय want to group
 * these counts together and treat all three of them in parallel.
 */
काष्ठा task_cpuसमय अणु
	u64				sसमय;
	u64				uसमय;
	अचिन्हित दीर्घ दीर्घ		sum_exec_runसमय;
पूर्ण;

#पूर्ण_अगर
