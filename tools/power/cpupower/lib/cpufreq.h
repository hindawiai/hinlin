<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  cpufreq.h - definitions क्रम libcpufreq
 *
 *  Copyright (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 */

#अगर_अघोषित __CPUPOWER_CPUFREQ_H__
#घोषणा __CPUPOWER_CPUFREQ_H__

काष्ठा cpufreq_policy अणु
	अचिन्हित दीर्घ min;
	अचिन्हित दीर्घ max;
	अक्षर *governor;
पूर्ण;

काष्ठा cpufreq_available_governors अणु
	अक्षर *governor;
	काष्ठा cpufreq_available_governors *next;
	काष्ठा cpufreq_available_governors *first;
पूर्ण;

काष्ठा cpufreq_available_frequencies अणु
	अचिन्हित दीर्घ frequency;
	काष्ठा cpufreq_available_frequencies *next;
	काष्ठा cpufreq_available_frequencies *first;
पूर्ण;


काष्ठा cpufreq_affected_cpus अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा cpufreq_affected_cpus *next;
	काष्ठा cpufreq_affected_cpus *first;
पूर्ण;

काष्ठा cpufreq_stats अणु
	अचिन्हित दीर्घ frequency;
	अचिन्हित दीर्घ दीर्घ समय_in_state;
	काष्ठा cpufreq_stats *next;
	काष्ठा cpufreq_stats *first;
पूर्ण;



#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

/* determine current CPU frequency
 * - _kernel variant means kernel's opinion of CPU frequency
 * - _hardware variant means actual hardware CPU frequency,
 *    which is only available to root.
 *
 * वापसs 0 on failure, अन्यथा frequency in kHz.
 */

अचिन्हित दीर्घ cpufreq_get_freq_kernel(अचिन्हित पूर्णांक cpu);

अचिन्हित दीर्घ cpufreq_get_freq_hardware(अचिन्हित पूर्णांक cpu);

#घोषणा cpufreq_get(cpu) cpufreq_get_freq_kernel(cpu);


/* determine CPU transition latency
 *
 * वापसs 0 on failure, अन्यथा transition latency in 10^(-9) s = nanoseconds
 */
अचिन्हित दीर्घ cpufreq_get_transition_latency(अचिन्हित पूर्णांक cpu);


/* determine hardware CPU frequency limits
 *
 * These may be limited further by thermal, energy or other
 * considerations by cpufreq policy notअगरiers in the kernel.
 */

पूर्णांक cpufreq_get_hardware_limits(अचिन्हित पूर्णांक cpu,
				अचिन्हित दीर्घ *min,
				अचिन्हित दीर्घ *max);


/* determine CPUfreq driver used
 *
 * Remember to call cpufreq_put_driver when no दीर्घer needed
 * to aव्योम memory leakage, please.
 */

अक्षर *cpufreq_get_driver(अचिन्हित पूर्णांक cpu);

व्योम cpufreq_put_driver(अक्षर *ptr);


/* determine CPUfreq policy currently used
 *
 * Remember to call cpufreq_put_policy when no दीर्घer needed
 * to aव्योम memory leakage, please.
 */


काष्ठा cpufreq_policy *cpufreq_get_policy(अचिन्हित पूर्णांक cpu);

व्योम cpufreq_put_policy(काष्ठा cpufreq_policy *policy);


/* determine CPUfreq governors currently available
 *
 * may be modअगरied by modprobe'ing or rmmod'ing other governors. Please
 * मुक्त allocated memory by calling cpufreq_put_available_governors
 * after use.
 */


काष्ठा cpufreq_available_governors
*cpufreq_get_available_governors(अचिन्हित पूर्णांक cpu);

व्योम cpufreq_put_available_governors(
	काष्ठा cpufreq_available_governors *first);


/* determine CPU frequency states available
 *
 * Only present on _some_ ->target() cpufreq drivers. For inक्रमmation purposes
 * only. Please मुक्त allocated memory by calling
 * cpufreq_put_frequencies after use.
 */

काष्ठा cpufreq_available_frequencies
*cpufreq_get_available_frequencies(अचिन्हित पूर्णांक cpu);

व्योम cpufreq_put_available_frequencies(
		काष्ठा cpufreq_available_frequencies *first);

काष्ठा cpufreq_available_frequencies
*cpufreq_get_boost_frequencies(अचिन्हित पूर्णांक cpu);

व्योम cpufreq_put_boost_frequencies(
		काष्ठा cpufreq_available_frequencies *first);


/* determine affected CPUs
 *
 * Remember to call cpufreq_put_affected_cpus when no दीर्घer needed
 * to aव्योम memory leakage, please.
 */

काष्ठा cpufreq_affected_cpus *cpufreq_get_affected_cpus(अचिन्हित
							पूर्णांक cpu);

व्योम cpufreq_put_affected_cpus(काष्ठा cpufreq_affected_cpus *first);


/* determine related CPUs
 *
 * Remember to call cpufreq_put_related_cpus when no दीर्घer needed
 * to aव्योम memory leakage, please.
 */

काष्ठा cpufreq_affected_cpus *cpufreq_get_related_cpus(अचिन्हित
							पूर्णांक cpu);

व्योम cpufreq_put_related_cpus(काष्ठा cpufreq_affected_cpus *first);


/* determine stats क्रम cpufreq subप्रणाली
 *
 * This is not available in all kernel versions or configurations.
 */

काष्ठा cpufreq_stats *cpufreq_get_stats(अचिन्हित पूर्णांक cpu,
					अचिन्हित दीर्घ दीर्घ *total_समय);

व्योम cpufreq_put_stats(काष्ठा cpufreq_stats *stats);

अचिन्हित दीर्घ cpufreq_get_transitions(अचिन्हित पूर्णांक cpu);


/* set new cpufreq policy
 *
 * Tries to set the passed policy as new policy as बंद as possible,
 * but results may dअगरfer depending e.g. on governors being available.
 */

पूर्णांक cpufreq_set_policy(अचिन्हित पूर्णांक cpu, काष्ठा cpufreq_policy *policy);


/* modअगरy a policy by only changing min/max freq or governor
 *
 * Does not check whether result is what was पूर्णांकended.
 */

पूर्णांक cpufreq_modअगरy_policy_min(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ min_freq);
पूर्णांक cpufreq_modअगरy_policy_max(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ max_freq);
पूर्णांक cpufreq_modअगरy_policy_governor(अचिन्हित पूर्णांक cpu, अक्षर *governor);


/* set a specअगरic frequency
 *
 * Does only work अगर userspace governor can be used and no बाह्यal
 * पूर्णांकerference (other calls to this function or to set/modअगरy_policy)
 * occurs. Also करोes not work on ->range() cpufreq drivers.
 */

पूर्णांक cpufreq_set_frequency(अचिन्हित पूर्णांक cpu,
				अचिन्हित दीर्घ target_frequency);

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _CPUFREQ_H */
