<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPUPOWER_CPUIDLE_H__
#घोषणा __CPUPOWER_CPUIDLE_H__

पूर्णांक cpuidle_is_state_disabled(अचिन्हित पूर्णांक cpu,
				       अचिन्हित पूर्णांक idlestate);
पूर्णांक cpuidle_state_disable(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक idlestate,
				   अचिन्हित पूर्णांक disable);
अचिन्हित दीर्घ cpuidle_state_latency(अचिन्हित पूर्णांक cpu,
						अचिन्हित पूर्णांक idlestate);
अचिन्हित दीर्घ cpuidle_state_usage(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक idlestate);
अचिन्हित दीर्घ दीर्घ cpuidle_state_समय(अचिन्हित पूर्णांक cpu,
						अचिन्हित पूर्णांक idlestate);
अक्षर *cpuidle_state_name(अचिन्हित पूर्णांक cpu,
				अचिन्हित पूर्णांक idlestate);
अक्षर *cpuidle_state_desc(अचिन्हित पूर्णांक cpu,
				अचिन्हित पूर्णांक idlestate);
अचिन्हित पूर्णांक cpuidle_state_count(अचिन्हित पूर्णांक cpu);

अक्षर *cpuidle_get_governor(व्योम);
अक्षर *cpuidle_get_driver(व्योम);

#पूर्ण_अगर /* __CPUPOWER_HELPERS_SYSFS_H__ */
