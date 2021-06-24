<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPUPOWER_HELPERS_SYSFS_H__
#घोषणा __CPUPOWER_HELPERS_SYSFS_H__

#घोषणा PATH_TO_CPU "/sys/devices/system/cpu/"
#घोषणा MAX_LINE_LEN 255
#घोषणा SYSFS_PATH_MAX 255

बाह्य अचिन्हित पूर्णांक sysfs_पढ़ो_file(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen);

बाह्य अचिन्हित पूर्णांक sysfs_idlestate_file_exists(अचिन्हित पूर्णांक cpu,
						अचिन्हित पूर्णांक idlestate,
						स्थिर अक्षर *fname);

बाह्य पूर्णांक sysfs_is_cpu_online(अचिन्हित पूर्णांक cpu);

बाह्य पूर्णांक sysfs_is_idlestate_disabled(अचिन्हित पूर्णांक cpu,
				       अचिन्हित पूर्णांक idlestate);
बाह्य पूर्णांक sysfs_idlestate_disable(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक idlestate,
				   अचिन्हित पूर्णांक disable);
बाह्य अचिन्हित दीर्घ sysfs_get_idlestate_latency(अचिन्हित पूर्णांक cpu,
						अचिन्हित पूर्णांक idlestate);
बाह्य अचिन्हित दीर्घ sysfs_get_idlestate_usage(अचिन्हित पूर्णांक cpu,
					अचिन्हित पूर्णांक idlestate);
बाह्य अचिन्हित दीर्घ दीर्घ sysfs_get_idlestate_समय(अचिन्हित पूर्णांक cpu,
						अचिन्हित पूर्णांक idlestate);
बाह्य अक्षर *sysfs_get_idlestate_name(अचिन्हित पूर्णांक cpu,
				अचिन्हित पूर्णांक idlestate);
बाह्य अक्षर *sysfs_get_idlestate_desc(अचिन्हित पूर्णांक cpu,
				अचिन्हित पूर्णांक idlestate);
बाह्य अचिन्हित पूर्णांक sysfs_get_idlestate_count(अचिन्हित पूर्णांक cpu);

बाह्य अक्षर *sysfs_get_cpuidle_governor(व्योम);
बाह्य अक्षर *sysfs_get_cpuidle_driver(व्योम);

बाह्य पूर्णांक sysfs_get_sched(स्थिर अक्षर *smt_mc);
बाह्य पूर्णांक sysfs_set_sched(स्थिर अक्षर *smt_mc, पूर्णांक val);

#पूर्ण_अगर /* __CPUPOWER_HELPERS_SYSFS_H__ */
