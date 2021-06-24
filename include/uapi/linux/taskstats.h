<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 WITH Linux-syscall-note */
/* taskstats.h - exporting per-task statistics
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2006
 *           (C) Balbir Singh,   IBM Corp. 2006
 *           (C) Jay Lan,        SGI, 2006
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#अगर_अघोषित _LINUX_TASKSTATS_H
#घोषणा _LINUX_TASKSTATS_H

#समावेश <linux/types.h>

/* Format क्रम per-task data वापसed to userland when
 *	- a task निकासs
 *	- listener requests stats क्रम a task
 *
 * The काष्ठा is versioned. Newer versions should only add fields to
 * the bottom of the काष्ठा to मुख्यtain backward compatibility.
 *
 *
 * To add new fields
 *	a) bump up TASKSTATS_VERSION
 *	b) add comment indicating new version number at end of काष्ठा
 *	c) add new fields after version comment; मुख्यtain 64-bit alignment
 */


#घोषणा TASKSTATS_VERSION	10
#घोषणा TS_COMM_LEN		32	/* should be >= TASK_COMM_LEN
					 * in linux/sched.h */

काष्ठा taskstats अणु

	/* The version number of this काष्ठा. This field is always set to
	 * TAKSTATS_VERSION, which is defined in <linux/taskstats.h>.
	 * Each समय the काष्ठा is changed, the value should be incremented.
	 */
	__u16	version;
	__u32	ac_निकासcode;		/* Exit status */

	/* The accounting flags of a task as defined in <linux/acct.h>
	 * Defined values are AFORK, ASU, ACOMPAT, ACORE, and AXSIG.
	 */
	__u8	ac_flag;		/* Record flags */
	__u8	ac_nice;		/* task_nice */

	/* Delay accounting fields start
	 *
	 * All values, until comment "Delay accounting fields end" are
	 * available only अगर delay accounting is enabled, even though the last
	 * few fields are not delays
	 *
	 * xxx_count is the number of delay values recorded
	 * xxx_delay_total is the corresponding cumulative delay in nanoseconds
	 *
	 * xxx_delay_total wraps around to zero on overflow
	 * xxx_count incremented regardless of overflow
	 */

	/* Delay रुकोing क्रम cpu, जबतक runnable
	 * count, delay_total NOT updated atomically
	 */
	__u64	cpu_count __attribute__((aligned(8)));
	__u64	cpu_delay_total;

	/* Following four fields atomically updated using task->delays->lock */

	/* Delay रुकोing क्रम synchronous block I/O to complete
	 * करोes not account क्रम delays in I/O submission
	 */
	__u64	blkio_count;
	__u64	blkio_delay_total;

	/* Delay रुकोing क्रम page fault I/O (swap in only) */
	__u64	swapin_count;
	__u64	swapin_delay_total;

	/* cpu "wall-clock" running समय
	 * On some architectures, value will adjust क्रम cpu समय stolen
	 * from the kernel in involuntary रुकोs due to भवization.
	 * Value is cumulative, in nanoseconds, without a corresponding count
	 * and wraps around to zero silently on overflow
	 */
	__u64	cpu_run_real_total;

	/* cpu "virtual" running समय
	 * Uses समय पूर्णांकervals seen by the kernel i.e. no adjusपंचांगent
	 * क्रम kernel's involuntary रुकोs due to भवization.
	 * Value is cumulative, in nanoseconds, without a corresponding count
	 * and wraps around to zero silently on overflow
	 */
	__u64	cpu_run_भव_total;
	/* Delay accounting fields end */
	/* version 1 ends here */

	/* Basic Accounting Fields start */
	अक्षर	ac_comm[TS_COMM_LEN];	/* Command name */
	__u8	ac_sched __attribute__((aligned(8)));
					/* Scheduling discipline */
	__u8	ac_pad[3];
	__u32	ac_uid __attribute__((aligned(8)));
					/* User ID */
	__u32	ac_gid;			/* Group ID */
	__u32	ac_pid;			/* Process ID */
	__u32	ac_ppid;		/* Parent process ID */
	/* __u32 range means बार from 1970 to 2106 */
	__u32	ac_bसमय;		/* Begin समय [sec since 1970] */
	__u64	ac_eसमय __attribute__((aligned(8)));
					/* Elapsed समय [usec] */
	__u64	ac_uसमय;		/* User CPU समय [usec] */
	__u64	ac_sसमय;		/* SYstem CPU समय [usec] */
	__u64	ac_minflt;		/* Minor Page Fault Count */
	__u64	ac_majflt;		/* Major Page Fault Count */
	/* Basic Accounting Fields end */

	/* Extended accounting fields start */
	/* Accumulated RSS usage in duration of a task, in MBytes-usecs.
	 * The current rss usage is added to this counter every समय
	 * a tick is अक्षरged to a task's प्रणाली समय. So, at the end we
	 * will have memory usage multiplied by प्रणाली समय. Thus an
	 * average usage per प्रणाली समय unit can be calculated.
	 */
	__u64	coremem;		/* accumulated RSS usage in MB-usec */
	/* Accumulated भव memory usage in duration of a task.
	 * Same as acct_rss_mem1 above except that we keep track of VM usage.
	 */
	__u64	virपंचांगem;		/* accumulated VM  usage in MB-usec */

	/* High watermark of RSS and भव memory usage in duration of
	 * a task, in KBytes.
	 */
	__u64	hiwater_rss;		/* High-watermark of RSS usage, in KB */
	__u64	hiwater_vm;		/* High-water VM usage, in KB */

	/* The following four fields are I/O statistics of a task. */
	__u64	पढ़ो_अक्षर;		/* bytes पढ़ो */
	__u64	ग_लिखो_अक्षर;		/* bytes written */
	__u64	पढ़ो_syscalls;		/* पढ़ो syscalls */
	__u64	ग_लिखो_syscalls;		/* ग_लिखो syscalls */
	/* Extended accounting fields end */

#घोषणा TASKSTATS_HAS_IO_ACCOUNTING
	/* Per-task storage I/O accounting starts */
	__u64	पढ़ो_bytes;		/* bytes of पढ़ो I/O */
	__u64	ग_लिखो_bytes;		/* bytes of ग_लिखो I/O */
	__u64	cancelled_ग_लिखो_bytes;	/* bytes of cancelled ग_लिखो I/O */

	__u64  nvcsw;			/* voluntary_ctxt_चयनes */
	__u64  nivcsw;			/* nonvoluntary_ctxt_चयनes */

	/* समय accounting क्रम SMT machines */
	__u64	ac_uबारcaled;		/* uसमय scaled on frequency etc */
	__u64	ac_sबारcaled;		/* sसमय scaled on frequency etc */
	__u64	cpu_scaled_run_real_total; /* scaled cpu_run_real_total */

	/* Delay रुकोing क्रम memory reclaim */
	__u64	मुक्तpages_count;
	__u64	मुक्तpages_delay_total;

	/* Delay रुकोing क्रम thrashing page */
	__u64	thrashing_count;
	__u64	thrashing_delay_total;

	/* v10: 64-bit bसमय to aव्योम overflow */
	__u64	ac_bसमय64;		/* 64-bit begin समय */
पूर्ण;


/*
 * Commands sent from userspace
 * Not versioned. New commands should only be inserted at the क्रमागत's end
 * prior to __TASKSTATS_CMD_MAX
 */

क्रमागत अणु
	TASKSTATS_CMD_UNSPEC = 0,	/* Reserved */
	TASKSTATS_CMD_GET,		/* user->kernel request/get-response */
	TASKSTATS_CMD_NEW,		/* kernel->user event */
	__TASKSTATS_CMD_MAX,
पूर्ण;

#घोषणा TASKSTATS_CMD_MAX (__TASKSTATS_CMD_MAX - 1)

क्रमागत अणु
	TASKSTATS_TYPE_UNSPEC = 0,	/* Reserved */
	TASKSTATS_TYPE_PID,		/* Process id */
	TASKSTATS_TYPE_TGID,		/* Thपढ़ो group id */
	TASKSTATS_TYPE_STATS,		/* taskstats काष्ठाure */
	TASKSTATS_TYPE_AGGR_PID,	/* contains pid + stats */
	TASKSTATS_TYPE_AGGR_TGID,	/* contains tgid + stats */
	TASKSTATS_TYPE_शून्य,		/* contains nothing */
	__TASKSTATS_TYPE_MAX,
पूर्ण;

#घोषणा TASKSTATS_TYPE_MAX (__TASKSTATS_TYPE_MAX - 1)

क्रमागत अणु
	TASKSTATS_CMD_ATTR_UNSPEC = 0,
	TASKSTATS_CMD_ATTR_PID,
	TASKSTATS_CMD_ATTR_TGID,
	TASKSTATS_CMD_ATTR_REGISTER_CPUMASK,
	TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK,
	__TASKSTATS_CMD_ATTR_MAX,
पूर्ण;

#घोषणा TASKSTATS_CMD_ATTR_MAX (__TASKSTATS_CMD_ATTR_MAX - 1)

/* NETLINK_GENERIC related info */

#घोषणा TASKSTATS_GENL_NAME	"TASKSTATS"
#घोषणा TASKSTATS_GENL_VERSION	0x1

#पूर्ण_अगर /* _LINUX_TASKSTATS_H */
