<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_CPUFREQ_H
#घोषणा _LINUX_SCHED_CPUFREQ_H

#समावेश <linux/types.h>

/*
 * Interface between cpufreq drivers and the scheduler:
 */

#घोषणा SCHED_CPUFREQ_IOWAIT	(1U << 0)

#अगर_घोषित CONFIG_CPU_FREQ
काष्ठा cpufreq_policy;

काष्ठा update_util_data अणु
       व्योम (*func)(काष्ठा update_util_data *data, u64 समय, अचिन्हित पूर्णांक flags);
पूर्ण;

व्योम cpufreq_add_update_util_hook(पूर्णांक cpu, काष्ठा update_util_data *data,
                       व्योम (*func)(काष्ठा update_util_data *data, u64 समय,
				    अचिन्हित पूर्णांक flags));
व्योम cpufreq_हटाओ_update_util_hook(पूर्णांक cpu);
bool cpufreq_this_cpu_can_update(काष्ठा cpufreq_policy *policy);

अटल अंतरभूत अचिन्हित दीर्घ map_util_freq(अचिन्हित दीर्घ util,
					अचिन्हित दीर्घ freq, अचिन्हित दीर्घ cap)
अणु
	वापस (freq + (freq >> 2)) * util / cap;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ map_util_perf(अचिन्हित दीर्घ util)
अणु
	वापस util + (util >> 2);
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_FREQ */

#पूर्ण_अगर /* _LINUX_SCHED_CPUFREQ_H */
