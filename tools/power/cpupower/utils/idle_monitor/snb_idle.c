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

#घोषणा MSR_PKG_C2_RESIDENCY	0x60D
#घोषणा MSR_PKG_C7_RESIDENCY	0x3FA
#घोषणा MSR_CORE_C7_RESIDENCY	0x3FE

#घोषणा MSR_TSC	0x10

क्रमागत पूर्णांकel_snb_id अणु C7 = 0, PC2, PC7, SNB_CSTATE_COUNT, TSC = 0xFFFF पूर्ण;

अटल पूर्णांक snb_get_count_percent(अचिन्हित पूर्णांक self_id, द्विगुन *percent,
				 अचिन्हित पूर्णांक cpu);

अटल cstate_t snb_cstates[SNB_CSTATE_COUNT] = अणु
	अणु
		.name			= "C7",
		.desc			= N_("Processor Core C7"),
		.id			= C7,
		.range			= RANGE_CORE,
		.get_count_percent	= snb_get_count_percent,
	पूर्ण,
	अणु
		.name			= "PC2",
		.desc			= N_("Processor Package C2"),
		.id			= PC2,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= snb_get_count_percent,
	पूर्ण,
	अणु
		.name			= "PC7",
		.desc			= N_("Processor Package C7"),
		.id			= PC7,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= snb_get_count_percent,
	पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_start;
अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_end;
अटल अचिन्हित दीर्घ दीर्घ *previous_count[SNB_CSTATE_COUNT];
अटल अचिन्हित दीर्घ दीर्घ *current_count[SNB_CSTATE_COUNT];
/* valid flag क्रम all CPUs. If a MSR पढ़ो failed it will be zero */
अटल पूर्णांक *is_valid;

अटल पूर्णांक snb_get_count(क्रमागत पूर्णांकel_snb_id id, अचिन्हित दीर्घ दीर्घ *val,
			अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक msr;

	चयन (id) अणु
	हाल C7:
		msr = MSR_CORE_C7_RESIDENCY;
		अवरोध;
	हाल PC2:
		msr = MSR_PKG_C2_RESIDENCY;
		अवरोध;
	हाल PC7:
		msr = MSR_PKG_C7_RESIDENCY;
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

अटल पूर्णांक snb_get_count_percent(अचिन्हित पूर्णांक id, द्विगुन *percent,
				 अचिन्हित पूर्णांक cpu)
अणु
	*percent = 0.0;

	अगर (!is_valid[cpu])
		वापस -1;

	*percent = (100.0 *
		(current_count[id][cpu] - previous_count[id][cpu])) /
		(tsc_at_measure_end - tsc_at_measure_start);

	dprपूर्णांक("%s: previous: %llu - current: %llu - (%u)\n",
		snb_cstates[id].name, previous_count[id][cpu],
		current_count[id][cpu], cpu);

	dprपूर्णांक("%s: tsc_diff: %llu - count_diff: %llu - percent: %2.f (%u)\n",
	       snb_cstates[id].name,
	       (अचिन्हित दीर्घ दीर्घ) tsc_at_measure_end - tsc_at_measure_start,
	       current_count[id][cpu] - previous_count[id][cpu],
	       *percent, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक snb_start(व्योम)
अणु
	पूर्णांक num, cpu;
	अचिन्हित दीर्घ दीर्घ val;

	क्रम (num = 0; num < SNB_CSTATE_COUNT; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
			snb_get_count(num, &val, cpu);
			previous_count[num][cpu] = val;
		पूर्ण
	पूर्ण
	snb_get_count(TSC, &tsc_at_measure_start, base_cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक snb_stop(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	पूर्णांक num, cpu;

	snb_get_count(TSC, &tsc_at_measure_end, base_cpu);

	क्रम (num = 0; num < SNB_CSTATE_COUNT; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
			is_valid[cpu] = !snb_get_count(num, &val, cpu);
			current_count[num][cpu] = val;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा cpuidle_monitor पूर्णांकel_snb_monitor;

अटल काष्ठा cpuidle_monitor *snb_रेजिस्टर(व्योम)
अणु
	पूर्णांक num;

	अगर (cpuघातer_cpu_info.venकरोr != X86_VENDOR_INTEL
	    || cpuघातer_cpu_info.family != 6)
		वापस शून्य;

	चयन (cpuघातer_cpu_info.model) अणु
	हाल 0x2A: /* SNB */
	हाल 0x2D: /* SNB Xeon */
	हाल 0x3A: /* IVB */
	हाल 0x3E: /* IVB Xeon */
	हाल 0x3C: /* HSW */
	हाल 0x3F: /* HSW */
	हाल 0x45: /* HSW */
	हाल 0x46: /* HSW */
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	is_valid = सुस्मृति(cpu_count, माप(पूर्णांक));
	क्रम (num = 0; num < SNB_CSTATE_COUNT; num++) अणु
		previous_count[num] = सुस्मृति(cpu_count,
					माप(अचिन्हित दीर्घ दीर्घ));
		current_count[num]  = सुस्मृति(cpu_count,
					माप(अचिन्हित दीर्घ दीर्घ));
	पूर्ण
	पूर्णांकel_snb_monitor.name_len = म_माप(पूर्णांकel_snb_monitor.name);
	वापस &पूर्णांकel_snb_monitor;
पूर्ण

व्योम snb_unरेजिस्टर(व्योम)
अणु
	पूर्णांक num;
	मुक्त(is_valid);
	क्रम (num = 0; num < SNB_CSTATE_COUNT; num++) अणु
		मुक्त(previous_count[num]);
		मुक्त(current_count[num]);
	पूर्ण
पूर्ण

काष्ठा cpuidle_monitor पूर्णांकel_snb_monitor = अणु
	.name			= "SandyBridge",
	.hw_states		= snb_cstates,
	.hw_states_num		= SNB_CSTATE_COUNT,
	.start			= snb_start,
	.stop			= snb_stop,
	.करो_रेजिस्टर		= snb_रेजिस्टर,
	.unरेजिस्टर		= snb_unरेजिस्टर,
	.flags.needs_root	= 1,
	.overflow_s		= 922000000 /* 922337203 seconds TSC overflow
					       at 20GHz */
पूर्ण;
#पूर्ण_अगर /* defined(__i386__) || defined(__x86_64__) */
