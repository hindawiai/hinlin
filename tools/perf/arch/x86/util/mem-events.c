<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/pmu.h"
#समावेश "map_symbol.h"
#समावेश "mem-events.h"

अटल अक्षर mem_loads_name[100];
अटल bool mem_loads_name__init;

#घोषणा MEM_LOADS_AUX		0x8203
#घोषणा MEM_LOADS_AUX_NAME	"{cpu/mem-loads-aux/,cpu/mem-loads,ldlat=%u/pp}:S"

bool is_mem_loads_aux_event(काष्ठा evsel *leader)
अणु
	अगर (!pmu_have_event("cpu", "mem-loads-aux"))
		वापस false;

	वापस leader->core.attr.config == MEM_LOADS_AUX;
पूर्ण

अक्षर *perf_mem_events__name(पूर्णांक i)
अणु
	काष्ठा perf_mem_event *e = perf_mem_events__ptr(i);

	अगर (!e)
		वापस शून्य;

	अगर (i == PERF_MEM_EVENTS__LOAD) अणु
		अगर (mem_loads_name__init)
			वापस mem_loads_name;

		mem_loads_name__init = true;

		अगर (pmu_have_event("cpu", "mem-loads-aux")) अणु
			scnम_लिखो(mem_loads_name, माप(mem_loads_name),
				  MEM_LOADS_AUX_NAME, perf_mem_events__loads_ldlat);
		पूर्ण अन्यथा अणु
			scnम_लिखो(mem_loads_name, माप(mem_loads_name),
				  e->name, perf_mem_events__loads_ldlat);
		पूर्ण
		वापस mem_loads_name;
	पूर्ण

	वापस (अक्षर *)e->name;
पूर्ण
