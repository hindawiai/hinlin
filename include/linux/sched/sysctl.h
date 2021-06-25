<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_SYSCTL_H
#घोषणा _LINUX_SCHED_SYSCTL_H

#समावेश <linux/types.h>

काष्ठा ctl_table;

#अगर_घोषित CONFIG_DETECT_HUNG_TASK

#अगर_घोषित CONFIG_SMP
बाह्य अचिन्हित पूर्णांक sysctl_hung_task_all_cpu_backtrace;
#अन्यथा
#घोषणा sysctl_hung_task_all_cpu_backtrace 0
#पूर्ण_अगर /* CONFIG_SMP */

बाह्य पूर्णांक	     sysctl_hung_task_check_count;
बाह्य अचिन्हित पूर्णांक  sysctl_hung_task_panic;
बाह्य अचिन्हित दीर्घ sysctl_hung_task_समयout_secs;
बाह्य अचिन्हित दीर्घ sysctl_hung_task_check_पूर्णांकerval_secs;
बाह्य पूर्णांक sysctl_hung_task_warnings;
पूर्णांक proc_करोhung_task_समयout_secs(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
#अन्यथा
/* Aव्योम need क्रम अगरdefs अन्यथाwhere in the code */
क्रमागत अणु sysctl_hung_task_समयout_secs = 0 पूर्ण;
#पूर्ण_अगर

बाह्य अचिन्हित पूर्णांक sysctl_sched_child_runs_first;

बाह्य अचिन्हित पूर्णांक sysctl_sched_latency;
बाह्य अचिन्हित पूर्णांक sysctl_sched_min_granularity;
बाह्य अचिन्हित पूर्णांक sysctl_sched_wakeup_granularity;

क्रमागत sched_tunable_scaling अणु
	SCHED_TUNABLESCALING_NONE,
	SCHED_TUNABLESCALING_LOG,
	SCHED_TUNABLESCALING_LINEAR,
	SCHED_TUNABLESCALING_END,
पूर्ण;
बाह्य अचिन्हित पूर्णांक sysctl_sched_tunable_scaling;

बाह्य अचिन्हित पूर्णांक sysctl_numa_balancing_scan_delay;
बाह्य अचिन्हित पूर्णांक sysctl_numa_balancing_scan_period_min;
बाह्य अचिन्हित पूर्णांक sysctl_numa_balancing_scan_period_max;
बाह्य अचिन्हित पूर्णांक sysctl_numa_balancing_scan_size;

#अगर_घोषित CONFIG_SCHED_DEBUG
बाह्य __पढ़ो_mostly अचिन्हित पूर्णांक sysctl_sched_migration_cost;
बाह्य __पढ़ो_mostly अचिन्हित पूर्णांक sysctl_sched_nr_migrate;

बाह्य पूर्णांक sysctl_resched_latency_warn_ms;
बाह्य पूर्णांक sysctl_resched_latency_warn_once;
#पूर्ण_अगर

/*
 *  control realसमय throttling:
 *
 *  /proc/sys/kernel/sched_rt_period_us
 *  /proc/sys/kernel/sched_rt_runसमय_us
 */
बाह्य अचिन्हित पूर्णांक sysctl_sched_rt_period;
बाह्य पूर्णांक sysctl_sched_rt_runसमय;

बाह्य अचिन्हित पूर्णांक sysctl_sched_dl_period_max;
बाह्य अचिन्हित पूर्णांक sysctl_sched_dl_period_min;

#अगर_घोषित CONFIG_UCLAMP_TASK
बाह्य अचिन्हित पूर्णांक sysctl_sched_uclamp_util_min;
बाह्य अचिन्हित पूर्णांक sysctl_sched_uclamp_util_max;
बाह्य अचिन्हित पूर्णांक sysctl_sched_uclamp_util_min_rt_शेष;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CFS_BANDWIDTH
बाह्य अचिन्हित पूर्णांक sysctl_sched_cfs_bandwidth_slice;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_AUTOGROUP
बाह्य अचिन्हित पूर्णांक sysctl_sched_स्वतःgroup_enabled;
#पूर्ण_अगर

बाह्य पूर्णांक sysctl_sched_rr_बारlice;
बाह्य पूर्णांक sched_rr_बारlice;

पूर्णांक sched_rr_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक sched_rt_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक sysctl_sched_uclamp_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक sysctl_numa_balancing(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक sysctl_schedstats(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
बाह्य अचिन्हित पूर्णांक sysctl_sched_energy_aware;
पूर्णांक sched_energy_aware_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_SYSCTL_H */
