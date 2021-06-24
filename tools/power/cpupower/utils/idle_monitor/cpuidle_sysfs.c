<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <cpuidle.h>

#समावेश "helpers/helpers.h"
#समावेश "idle_monitor/cpupower-monitor.h"

#घोषणा CPUIDLE_STATES_MAX 10
अटल cstate_t cpuidle_cstates[CPUIDLE_STATES_MAX];
काष्ठा cpuidle_monitor cpuidle_sysfs_monitor;

अटल अचिन्हित दीर्घ दीर्घ **previous_count;
अटल अचिन्हित दीर्घ दीर्घ **current_count;
अटल काष्ठा बारpec start_समय;
अटल अचिन्हित दीर्घ दीर्घ समयdअगरf;

अटल पूर्णांक cpuidle_get_count_percent(अचिन्हित पूर्णांक id, द्विगुन *percent,
				     अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ statedअगरf = current_count[cpu][id]
		- previous_count[cpu][id];
	dprपूर्णांक("%s: - diff: %llu - percent: %f (%u)\n",
	       cpuidle_cstates[id].name, समयdअगरf, *percent, cpu);

	अगर (समयdअगरf == 0)
		*percent = 0.0;
	अन्यथा
		*percent = ((100.0 * statedअगरf) / समयdअगरf);

	dprपूर्णांक("%s: - timediff: %llu - statediff: %llu - percent: %f (%u)\n",
	       cpuidle_cstates[id].name, समयdअगरf, statedअगरf, *percent, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक cpuidle_start(व्योम)
अणु
	पूर्णांक cpu, state;
	घड़ी_समय_लो(CLOCK_REALTIME, &start_समय);
	क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
		क्रम (state = 0; state < cpuidle_sysfs_monitor.hw_states_num;
		     state++) अणु
			previous_count[cpu][state] =
				cpuidle_state_समय(cpu, state);
			dprपूर्णांक("CPU %d - State: %d - Val: %llu\n",
			       cpu, state, previous_count[cpu][state]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cpuidle_stop(व्योम)
अणु
	पूर्णांक cpu, state;
	काष्ठा बारpec end_समय;
	घड़ी_समय_लो(CLOCK_REALTIME, &end_समय);
	समयdअगरf = बारpec_dअगरf_us(start_समय, end_समय);

	क्रम (cpu = 0; cpu < cpu_count; cpu++) अणु
		क्रम (state = 0; state < cpuidle_sysfs_monitor.hw_states_num;
		     state++) अणु
			current_count[cpu][state] =
				cpuidle_state_समय(cpu, state);
			dprपूर्णांक("CPU %d - State: %d - Val: %llu\n",
			       cpu, state, previous_count[cpu][state]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम fix_up_पूर्णांकel_idle_driver_name(अक्षर *पंचांगp, पूर्णांक num)
अणु
	/* fix up cpuidle name क्रम पूर्णांकel idle driver */
	अगर (!म_भेदन(पंचांगp, "NHM-", 4)) अणु
		चयन (num) अणु
		हाल 1:
			म_नकल(पंचांगp, "C1");
			अवरोध;
		हाल 2:
			म_नकल(पंचांगp, "C3");
			अवरोध;
		हाल 3:
			म_नकल(पंचांगp, "C6");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(पंचांगp, "SNB-", 4)) अणु
		चयन (num) अणु
		हाल 1:
			म_नकल(पंचांगp, "C1");
			अवरोध;
		हाल 2:
			म_नकल(पंचांगp, "C3");
			अवरोध;
		हाल 3:
			म_नकल(पंचांगp, "C6");
			अवरोध;
		हाल 4:
			म_नकल(पंचांगp, "C7");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(पंचांगp, "ATM-", 4)) अणु
		चयन (num) अणु
		हाल 1:
			म_नकल(पंचांगp, "C1");
			अवरोध;
		हाल 2:
			म_नकल(पंचांगp, "C2");
			अवरोध;
		हाल 3:
			म_नकल(पंचांगp, "C4");
			अवरोध;
		हाल 4:
			म_नकल(पंचांगp, "C6");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित __घातerpc__
व्योम map_घातer_idle_state_name(अक्षर *पंचांगp)
अणु
	अगर (!म_भेदन(पंचांगp, "stop0_lite", CSTATE_NAME_LEN))
		म_नकल(पंचांगp, "stop0L");
	अन्यथा अगर (!म_भेदन(पंचांगp, "stop1_lite", CSTATE_NAME_LEN))
		म_नकल(पंचांगp, "stop1L");
	अन्यथा अगर (!म_भेदन(पंचांगp, "stop2_lite", CSTATE_NAME_LEN))
		म_नकल(पंचांगp, "stop2L");
पूर्ण
#अन्यथा
व्योम map_घातer_idle_state_name(अक्षर *पंचांगp) अणु पूर्ण
#पूर्ण_अगर

अटल काष्ठा cpuidle_monitor *cpuidle_रेजिस्टर(व्योम)
अणु
	पूर्णांक num;
	अक्षर *पंचांगp;
	पूर्णांक this_cpu;

	this_cpu = sched_अ_लोpu();

	/* Assume idle state count is the same क्रम all CPUs */
	cpuidle_sysfs_monitor.hw_states_num = cpuidle_state_count(this_cpu);

	अगर (cpuidle_sysfs_monitor.hw_states_num <= 0)
		वापस शून्य;

	क्रम (num = 0; num < cpuidle_sysfs_monitor.hw_states_num; num++) अणु
		पंचांगp = cpuidle_state_name(this_cpu, num);
		अगर (पंचांगp == शून्य)
			जारी;

		map_घातer_idle_state_name(पंचांगp);
		fix_up_पूर्णांकel_idle_driver_name(पंचांगp, num);
		म_नकलन(cpuidle_cstates[num].name, पंचांगp, CSTATE_NAME_LEN - 1);
		मुक्त(पंचांगp);

		पंचांगp = cpuidle_state_desc(this_cpu, num);
		अगर (पंचांगp == शून्य)
			जारी;
		म_नकलन(cpuidle_cstates[num].desc, पंचांगp,	CSTATE_DESC_LEN - 1);
		मुक्त(पंचांगp);

		cpuidle_cstates[num].range = RANGE_THREAD;
		cpuidle_cstates[num].id = num;
		cpuidle_cstates[num].get_count_percent =
			cpuidle_get_count_percent;
	पूर्ण

	/* Free this at program termination */
	previous_count = दो_स्मृति(माप(दीर्घ दीर्घ *) * cpu_count);
	current_count = दो_स्मृति(माप(दीर्घ दीर्घ *) * cpu_count);
	क्रम (num = 0; num < cpu_count; num++) अणु
		previous_count[num] = दो_स्मृति(माप(दीर्घ दीर्घ) *
					cpuidle_sysfs_monitor.hw_states_num);
		current_count[num] = दो_स्मृति(माप(दीर्घ दीर्घ) *
					cpuidle_sysfs_monitor.hw_states_num);
	पूर्ण

	cpuidle_sysfs_monitor.name_len = म_माप(cpuidle_sysfs_monitor.name);
	वापस &cpuidle_sysfs_monitor;
पूर्ण

व्योम cpuidle_unरेजिस्टर(व्योम)
अणु
	पूर्णांक num;

	क्रम (num = 0; num < cpu_count; num++) अणु
		मुक्त(previous_count[num]);
		मुक्त(current_count[num]);
	पूर्ण
	मुक्त(previous_count);
	मुक्त(current_count);
पूर्ण

काष्ठा cpuidle_monitor cpuidle_sysfs_monitor = अणु
	.name			= "Idle_Stats",
	.hw_states		= cpuidle_cstates,
	.start			= cpuidle_start,
	.stop			= cpuidle_stop,
	.करो_रेजिस्टर		= cpuidle_रेजिस्टर,
	.unरेजिस्टर		= cpuidle_unरेजिस्टर,
	.flags.needs_root	= 0,
	.overflow_s		= अच_पूर्णांक_उच्च,
पूर्ण;
