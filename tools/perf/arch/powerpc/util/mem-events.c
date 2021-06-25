<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "map_symbol.h"
#समावेश "mem-events.h"

/* PowerPC करोes not support 'ldlat' parameter. */
अक्षर *perf_mem_events__name(पूर्णांक i)
अणु
	अगर (i == PERF_MEM_EVENTS__LOAD)
		वापस (अक्षर *) "cpu/mem-loads/";

	वापस (अक्षर *) "cpu/mem-stores/";
पूर्ण
