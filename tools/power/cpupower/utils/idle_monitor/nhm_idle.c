<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 *  Based on Len Brown's <lenb@kernel.org> turbostat tool.
 */

#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "helpers/helpers.h"
#समावेश "idle_monitor/cpupower-monitor.h"

#घोषणा MSR_PKG_C3_RESIDENCY	0x3F8
#घोषणा MSR_PKG_C6_RESIDENCY	0x3F9
#घोषणा MSR_CORE_C3_RESIDENCY	0x3FC
#घोषणा MSR_CORE_C6_RESIDENCY	0x3FD

#घोषणा MSR_TSC	0x10

#घोषणा NHM_CSTATE_COUNT 4

क्रमागत पूर्णांकel_nhm_id अणु C3 = 0, C6, PC3, PC6, TSC = 0xFFFF पूर्ण;

अटल पूर्णांक nhm_get_count_percent(अचिन्हित पूर्णांक self_id, द्विगुन *percent,
				 अचिन्हित पूर्णांक cpu);

अटल cstate_t nhm_cstates[NHM_CSTATE_COUNT] = अणु
	अणु
		.name			= "C3",
		.desc			= N_("Processor Core C3"),
		.id			= C3,
		.range			= RANGE_CORE,
		.get_count_percent	= nhm_get_count_percent,
	पूर्ण,
	अणु
		.name			= "C6",
		.desc			= N_("Processor Core C6"),
		.id			= C6,
		.range			= RANGE_CORE,
		.get_count_percent	= nhm_get_count_percent,
	पूर्ण,

	अणु
		.name			= "PC3",
		.desc			= N_("Processor Package C3"),
		.id			= PC3,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= nhm_get_count_percent,
	पूर्ण,
	अणु
		.name			= "PC6",
		.desc			= N_("Processor Package C6"),
		.id			= PC6,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= nhm_get_count_percent,
	पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_start;
अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_end;
अटल अचिन्हित दीर्घ दीर्घ *previous_count[NHM_CSTATE_COUNT];
अटल अचिन्हित दीर्घ दीर्घ *current_count[NHM_CSTATE_COUNT];
/* valid flag क्रम all CPUs. If a MSR पढ़ो failed it will be zero */
अटल पूर्णांक *is_valid;

अटल पूर्णांक nhm_get_count(क्रमागत पूर्णांकel_nhm_id id, अचिन्हित दीर्घ दीर्घ *val,
			अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक msr;

	चयन (id) अणु
	हाल C3:
		msr = MSR_CORE_C3_RESIDENCY;
		अवरोध;
	हाल C6:
		msr = MSR_CORE_C6_RESIDENCY;
		अवरोध;
	हाल PC3:
		msr = MSR_PKG_C3_RESIDENCY;
		अवरोध;
	हाल PC6:
		msr = MSR_PKG_C6_RESIDENCY;
		अवरोध;
	हाल TSC:
		msr = MSR_TSC;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	अगर (पढ़ो_msr(cpu, msr, val))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nhm_get_count_percent(अचिन्हित पूर्णांक id, द्विगुन *percent,
				 अचिन्हित पूर्णांक cpu)
अणु
	*percent = 0.0;

	अगर (!is_valid[cpu])
		वापस -1;

	*percent = (100.0 *
		(current_count[id][cpu] - previous_count[id][cpu])) /
		(tsc_at_measure_end - tsc_at_measure_start);

	dprपूर्णांक("%s: previous: %llu - current: %llu - (%u)\n",
		nhm_cstates[id].name, previous_count[id][cpu],
		current_count[id][cpu], cpu);

	dprपूर्णांक("%s: tsc_diff: %llu - count_diff: %llu - percent: %2.f (%u)\n",
	       nhm_cstates[id].name,
	       (अचिन्हित दीर्घ दीर्घ) tsc_at_measure_end - tsc_at_measure_start,
	       current_count[id][cpu] - previous_count[id][cpu],
	       *percent, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक nhm_start(व्योम)
अणु
	पूर्णांक num, cpu;
	अचिन्हित दीर्घ दीर्घ dbg, val;

	nhm_get_count(TSC, &tsc_at_measure_start, base_cpu);

	क्रम (num = 0; num < NHM_CSTATE_COUNT; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
			is_valid[cpu] = !nhm_get_count(num, &val, cpu);
			previous_count[num][cpu] = val;
		पूर्ण
	पूर्ण
	nhm_get_count(TSC, &dbg, base_cpu);
	dprपूर्णांक("TSC diff: %llu\n", dbg - tsc_at_measure_start);
	वापस 0;
पूर्ण

अटल पूर्णांक nhm_stop(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित दीर्घ दीर्घ dbg;
	पूर्णांक num, cpu;

	nhm_get_count(TSC, &tsc_at_measure_end, base_cpu);

	क्रम (num = 0; num < NHM_CSTATE_COUNT; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
			is_valid[cpu] = !nhm_get_count(num, &val, cpu);
			current_count[num][cpu] = val;
		पूर्ण
	पूर्ण
	nhm_get_count(TSC, &dbg, base_cpu);
	dprपूर्णांक("TSC diff: %llu\n", dbg - tsc_at_measure_end);

	वापस 0;
पूर्ण

काष्ठा cpuidle_monitor पूर्णांकel_nhm_monitor;

काष्ठा cpuidle_monitor *पूर्णांकel_nhm_रेजिस्टर(व्योम)
अणु
	पूर्णांक num;

	अगर (cpuघातer_cpu_info.venकरोr != X86_VENDOR_INTEL)
		वापस शून्य;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_INV_TSC))
		वापस शून्य;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_APERF))
		वापस शून्य;

	/* Free this at program termination */
	is_valid = सुस्मृति(cpu_count, माप(पूर्णांक));
	क्रम (num = 0; num < NHM_CSTATE_COUNT; num++) अणु
		previous_count[num] = सुस्मृति(cpu_count,
					माप(अचिन्हित दीर्घ दीर्घ));
		current_count[num]  = सुस्मृति(cpu_count,
					माप(अचिन्हित दीर्घ दीर्घ));
	पूर्ण

	पूर्णांकel_nhm_monitor.name_len = म_माप(पूर्णांकel_nhm_monitor.name);
	वापस &पूर्णांकel_nhm_monitor;
पूर्ण

व्योम पूर्णांकel_nhm_unरेजिस्टर(व्योम)
अणु
	पूर्णांक num;

	क्रम (num = 0; num < NHM_CSTATE_COUNT; num++) अणु
		मुक्त(previous_count[num]);
		मुक्त(current_count[num]);
	पूर्ण
	मुक्त(is_valid);
पूर्ण

काष्ठा cpuidle_monitor पूर्णांकel_nhm_monitor = अणु
	.name			= "Nehalem",
	.hw_states_num		= NHM_CSTATE_COUNT,
	.hw_states		= nhm_cstates,
	.start			= nhm_start,
	.stop			= nhm_stop,
	.करो_रेजिस्टर		= पूर्णांकel_nhm_रेजिस्टर,
	.unरेजिस्टर		= पूर्णांकel_nhm_unरेजिस्टर,
	.flags.needs_root	= 1,
	.overflow_s		= 922000000 /* 922337203 seconds TSC overflow
					       at 20GHz */
पूर्ण;
#पूर्ण_अगर
