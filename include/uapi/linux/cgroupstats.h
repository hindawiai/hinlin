<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 WITH Linux-syscall-note */
/* cgroupstats.h - exporting per-cgroup statistics
 *
 * Copyright IBM Corporation, 2007
 * Author Balbir Singh <balbir@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#अगर_अघोषित _LINUX_CGROUPSTATS_H
#घोषणा _LINUX_CGROUPSTATS_H

#समावेश <linux/types.h>
#समावेश <linux/taskstats.h>

/*
 * Data shared between user space and kernel space on a per cgroup
 * basis. This data is shared using taskstats.
 *
 * Most of these states are derived by looking at the task->state value
 * For the nr_io_रुको state, a flag in the delay accounting काष्ठाure
 * indicates that the task is रुकोing on IO
 *
 * Each member is aligned to a 8 byte boundary.
 */
काष्ठा cgroupstats अणु
	__u64	nr_sleeping;		/* Number of tasks sleeping */
	__u64	nr_running;		/* Number of tasks running */
	__u64	nr_stopped;		/* Number of tasks in stopped state */
	__u64	nr_unपूर्णांकerruptible;	/* Number of tasks in unपूर्णांकerruptible */
					/* state */
	__u64	nr_io_रुको;		/* Number of tasks रुकोing on IO */
पूर्ण;

/*
 * Commands sent from userspace
 * Not versioned. New commands should only be inserted at the क्रमागत's end
 * prior to __CGROUPSTATS_CMD_MAX
 */

क्रमागत अणु
	CGROUPSTATS_CMD_UNSPEC = __TASKSTATS_CMD_MAX,	/* Reserved */
	CGROUPSTATS_CMD_GET,		/* user->kernel request/get-response */
	CGROUPSTATS_CMD_NEW,		/* kernel->user event */
	__CGROUPSTATS_CMD_MAX,
पूर्ण;

#घोषणा CGROUPSTATS_CMD_MAX (__CGROUPSTATS_CMD_MAX - 1)

क्रमागत अणु
	CGROUPSTATS_TYPE_UNSPEC = 0,	/* Reserved */
	CGROUPSTATS_TYPE_CGROUP_STATS,	/* contains name + stats */
	__CGROUPSTATS_TYPE_MAX,
पूर्ण;

#घोषणा CGROUPSTATS_TYPE_MAX (__CGROUPSTATS_TYPE_MAX - 1)

क्रमागत अणु
	CGROUPSTATS_CMD_ATTR_UNSPEC = 0,
	CGROUPSTATS_CMD_ATTR_FD,
	__CGROUPSTATS_CMD_ATTR_MAX,
पूर्ण;

#घोषणा CGROUPSTATS_CMD_ATTR_MAX (__CGROUPSTATS_CMD_ATTR_MAX - 1)

#पूर्ण_अगर /* _LINUX_CGROUPSTATS_H */
