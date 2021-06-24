<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश <sched.h>

#समावेश <cpufreq.h>
#समावेश <cpuघातer.h>

#समावेश "config.h"
#समावेश "system.h"

/**
 * वापसs समय since epoch in तगs
 *
 * @retval समय
 **/

दीर्घ दीर्घ पूर्णांक get_समय()
अणु
	काष्ठा समयval now;

	समय_लोofday(&now, शून्य);

	वापस (दीर्घ दीर्घ पूर्णांक)(now.tv_sec * 1000000LL + now.tv_usec);
पूर्ण

/**
 * sets the cpufreq governor
 *
 * @param governor cpufreq governor name
 * @param cpu cpu क्रम which the governor should be set
 *
 * @retval 0 on success
 * @retval -1 when failed
 **/

पूर्णांक set_cpufreq_governor(अक्षर *governor, अचिन्हित पूर्णांक cpu)
अणु

	dम_लिखो("set %s as cpufreq governor\n", governor);

	अगर (cpuघातer_is_cpu_online(cpu) != 1) अणु
		लिखो_त्रुटि("cpufreq_cpu_exists");
		ख_लिखो(मानक_त्रुटि, "error: cpu %u does not exist\n", cpu);
		वापस -1;
	पूर्ण

	अगर (cpufreq_modअगरy_policy_governor(cpu, governor) != 0) अणु
		लिखो_त्रुटि("cpufreq_modify_policy_governor");
		ख_लिखो(मानक_त्रुटि, "error: unable to set %s governor\n", governor);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sets cpu affinity क्रम the process
 *
 * @param cpu cpu# to which the affinity should be set
 *
 * @retval 0 on success
 * @retval -1 when setting the affinity failed
 **/

पूर्णांक set_cpu_affinity(अचिन्हित पूर्णांक cpu)
अणु
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	dम_लिखो("set affinity to cpu #%u\n", cpu);

	अगर (sched_setaffinity(getpid(), माप(cpu_set_t), &cpuset) < 0) अणु
		लिखो_त्रुटि("sched_setaffinity");
		ख_लिखो(मानक_त्रुटि, "warning: unable to set cpu affinity\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sets the process priority parameter
 *
 * @param priority priority value
 *
 * @retval 0 on success
 * @retval -1 when setting the priority failed
 **/

पूर्णांक set_process_priority(पूर्णांक priority)
अणु
	काष्ठा sched_param param;

	dम_लिखो("set scheduler priority to %i\n", priority);

	param.sched_priority = priority;

	अगर (sched_setscheduler(0, SCHEDULER, &param) < 0) अणु
		लिखो_त्रुटि("sched_setscheduler");
		ख_लिखो(मानक_त्रुटि, "warning: unable to set scheduler priority\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * notअगरies the user that the benchmark may run some समय
 *
 * @param config benchmark config values
 *
 **/

व्योम prepare_user(स्थिर काष्ठा config *config)
अणु
	अचिन्हित दीर्घ sleep_समय = 0;
	अचिन्हित दीर्घ load_समय = 0;
	अचिन्हित पूर्णांक round;

	क्रम (round = 0; round < config->rounds; round++) अणु
		sleep_समय +=  2 * config->cycles *
			(config->sleep + config->sleep_step * round);
		load_समय += 2 * config->cycles *
			(config->load + config->load_step * round) +
			(config->load + config->load_step * round * 4);
	पूर्ण

	अगर (config->verbose || config->output != मानक_निकास)
		म_लिखो("approx. test duration: %im\n",
		       (पूर्णांक)((sleep_समय + load_समय) / 60000000));
पूर्ण

/**
 * sets up the cpu affinity and scheduler priority
 *
 * @param config benchmark config values
 *
 **/

व्योम prepare_प्रणाली(स्थिर काष्ठा config *config)
अणु
	अगर (config->verbose)
		म_लिखो("set cpu affinity to cpu #%u\n", config->cpu);

	set_cpu_affinity(config->cpu);

	चयन (config->prio) अणु
	हाल SCHED_HIGH:
		अगर (config->verbose)
			म_लिखो("high priority condition requested\n");

		set_process_priority(PRIORITY_HIGH);
		अवरोध;
	हाल SCHED_LOW:
		अगर (config->verbose)
			म_लिखो("low priority condition requested\n");

		set_process_priority(PRIORITY_LOW);
		अवरोध;
	शेष:
		अगर (config->verbose)
			म_लिखो("default priority condition requested\n");

		set_process_priority(PRIORITY_DEFAULT);
	पूर्ण
पूर्ण

