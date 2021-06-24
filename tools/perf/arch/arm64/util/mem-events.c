<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "map_symbol.h"
#समावेश "mem-events.h"

#घोषणा E(t, n, s) अणु .tag = t, .name = n, .sysfs_name = s पूर्ण

अटल काष्ठा perf_mem_event perf_mem_events[PERF_MEM_EVENTS__MAX] = अणु
	E("spe-load",	"arm_spe_0/ts_enable=1,load_filter=1,store_filter=0,min_latency=%u/",	"arm_spe_0"),
	E("spe-store",	"arm_spe_0/ts_enable=1,load_filter=0,store_filter=1/",			"arm_spe_0"),
	E("spe-ldst",	"arm_spe_0/ts_enable=1,load_filter=1,store_filter=1,min_latency=%u/",	"arm_spe_0"),
पूर्ण;

अटल अक्षर mem_ev_name[100];

काष्ठा perf_mem_event *perf_mem_events__ptr(पूर्णांक i)
अणु
	अगर (i >= PERF_MEM_EVENTS__MAX)
		वापस शून्य;

	वापस &perf_mem_events[i];
पूर्ण

अक्षर *perf_mem_events__name(पूर्णांक i)
अणु
	काष्ठा perf_mem_event *e = perf_mem_events__ptr(i);

	अगर (i >= PERF_MEM_EVENTS__MAX)
		वापस शून्य;

	अगर (i == PERF_MEM_EVENTS__LOAD || i == PERF_MEM_EVENTS__LOAD_STORE)
		scnम_लिखो(mem_ev_name, माप(mem_ev_name),
			  e->name, perf_mem_events__loads_ldlat);
	अन्यथा /* PERF_MEM_EVENTS__STORE */
		scnम_लिखो(mem_ev_name, माप(mem_ev_name), e->name);

	वापस mem_ev_name;
पूर्ण
