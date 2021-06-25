<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_THREADS_H
#घोषणा _LINUX_THREADS_H


/*
 * The शेष limit क्रम the nr of thपढ़ोs is now in
 * /proc/sys/kernel/thपढ़ोs-max.
 */

/*
 * Maximum supported processors.  Setting this smaller saves quite a
 * bit of memory.  Use nr_cpu_ids instead of this except क्रम अटल biपंचांगaps.
 */
#अगर_अघोषित CONFIG_NR_CPUS
/* FIXME: This should be fixed in the arch's Kconfig */
#घोषणा CONFIG_NR_CPUS	1
#पूर्ण_अगर

/* Places which use this should consider cpumask_var_t. */
#घोषणा NR_CPUS		CONFIG_NR_CPUS

#घोषणा MIN_THREADS_LEFT_FOR_ROOT 4

/*
 * This controls the शेष maximum pid allocated to a process
 */
#घोषणा PID_MAX_DEFAULT (CONFIG_BASE_SMALL ? 0x1000 : 0x8000)

/*
 * A maximum of 4 million PIDs should be enough क्रम a जबतक.
 * [NOTE: PID/TIDs are limited to 2^30 ~= 1 billion, see FUTEX_TID_MASK.]
 */
#घोषणा PID_MAX_LIMIT (CONFIG_BASE_SMALL ? PAGE_SIZE * 8 : \
	(माप(दीर्घ) > 4 ? 4 * 1024 * 1024 : PID_MAX_DEFAULT))

/*
 * Define a minimum number of pids per cpu.  Heuristically based
 * on original pid max of 32k क्रम 32 cpus.  Also, increase the
 * minimum settable value क्रम pid_max on the running प्रणाली based
 * on similar शेषs.  See kernel/pid.c:pidmap_init() क्रम details.
 */
#घोषणा PIDS_PER_CPU_DEFAULT	1024
#घोषणा PIDS_PER_CPU_MIN	8

#पूर्ण_अगर
