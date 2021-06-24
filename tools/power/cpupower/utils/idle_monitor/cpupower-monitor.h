<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 */

#अगर_अघोषित __CPUIDLE_INFO_HW__
#घोषणा __CPUIDLE_INFO_HW__

#समावेश <मानकतर्क.स>
#समावेश <समय.स>

#समावेश "idle_monitor/idle_monitors.h"

#घोषणा MONITORS_MAX 20
#घोषणा MONITOR_NAME_LEN 20

/* CSTATE_NAME_LEN is limited by header field width defined
 * in cpuघातer-monitor.c. Header field width is defined to be
 * sum of percent width and two spaces क्रम padding.
 */
#अगर_घोषित __घातerpc__
#घोषणा CSTATE_NAME_LEN 7
#अन्यथा
#घोषणा CSTATE_NAME_LEN 5
#पूर्ण_अगर
#घोषणा CSTATE_DESC_LEN 60

बाह्य पूर्णांक cpu_count;

/* Hard to define the right names ...: */
क्रमागत घातer_range_e अणु
	RANGE_THREAD,	/* Lowest in topology hierarcy, AMD: core, Intel: thपढ़ो
			   kernel sysfs: cpu */
	RANGE_CORE,	/* AMD: unit, Intel: core, kernel_sysfs: core_id */
	RANGE_PACKAGE,	/* Package, processor socket */
	RANGE_MACHINE,	/* Machine, platक्रमm wide */
	RANGE_MAX पूर्ण;

प्रकार काष्ठा cstate अणु
	पूर्णांक  id;
	क्रमागत घातer_range_e range;
	अक्षर name[CSTATE_NAME_LEN];
	अक्षर desc[CSTATE_DESC_LEN];

	/* either provide a percentage or a general count */
	पूर्णांक (*get_count_percent)(अचिन्हित पूर्णांक self_id, द्विगुन *percent,
				 अचिन्हित पूर्णांक cpu);
	पूर्णांक (*get_count)(अचिन्हित पूर्णांक self_id, अचिन्हित दीर्घ दीर्घ *count,
			 अचिन्हित पूर्णांक cpu);
पूर्ण cstate_t;

काष्ठा cpuidle_monitor अणु
	/* Name must not contain whitespaces */
	अक्षर name[MONITOR_NAME_LEN];
	पूर्णांक name_len;
	पूर्णांक hw_states_num;
	cstate_t *hw_states;
	पूर्णांक (*start) (व्योम);
	पूर्णांक (*stop) (व्योम);
	काष्ठा cpuidle_monitor* (*करो_रेजिस्टर) (व्योम);
	व्योम (*unरेजिस्टर)(व्योम);
	अचिन्हित पूर्णांक overflow_s;
	काष्ठा अणु
		अचिन्हित पूर्णांक needs_root:1;
		अचिन्हित पूर्णांक per_cpu_schedule:1;
	पूर्ण flags;
पूर्ण;

बाह्य दीर्घ दीर्घ बारpec_dअगरf_us(काष्ठा बारpec start, काष्ठा बारpec end);

#घोषणा prपूर्णांक_overflow_err(mes, ov)						\
अणु										\
	ख_लिखो(मानक_त्रुटि, gettext("Measure took %u seconds, but registers could "	\
				"overflow at %u seconds, results "		\
				"could be inaccurate\n"), mes, ov);		\
पूर्ण


/* Taken over from x86info project sources  -> वापस 0 on success */
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>
अटल अंतरभूत पूर्णांक bind_cpu(पूर्णांक cpu)
अणु
	cpu_set_t set;

	अगर (sched_getaffinity(getpid(), माप(set), &set) == 0) अणु
		CPU_ZERO(&set);
		CPU_SET(cpu, &set);
		वापस sched_setaffinity(getpid(), माप(set), &set);
	पूर्ण
	वापस 1;
पूर्ण

#पूर्ण_अगर /* __CPUIDLE_INFO_HW__ */
