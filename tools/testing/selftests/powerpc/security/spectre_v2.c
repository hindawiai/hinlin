<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Copyright 2018-2019 IBM Corporation.
 */

#घोषणा __SANE_USERSPACE_TYPES__

#समावेश <sys/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <दो_स्मृति.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <sys/prctl.h>
#समावेश "utils.h"

#समावेश "../pmu/event.h"


बाह्य व्योम pattern_cache_loop(व्योम);
बाह्य व्योम indirect_branch_loop(व्योम);

अटल पूर्णांक करो_count_loop(काष्ठा event *events, bool is_p9, s64 *miss_percent)
अणु
	u64 pred, mpred;

	prctl(PR_TASK_PERF_EVENTS_ENABLE);

	अगर (is_p9)
		pattern_cache_loop();
	अन्यथा
		indirect_branch_loop();

	prctl(PR_TASK_PERF_EVENTS_DISABLE);

	event_पढ़ो(&events[0]);
	event_पढ़ो(&events[1]);

	// We could scale all the events by running/enabled but we're lazy
	// As दीर्घ as the PMU is uncontended they should all run
	FAIL_IF(events[0].result.running != events[0].result.enabled);
	FAIL_IF(events[1].result.running != events[1].result.enabled);

	pred =  events[0].result.value;
	mpred = events[1].result.value;

	अगर (is_p9) अणु
		event_पढ़ो(&events[2]);
		event_पढ़ो(&events[3]);
		FAIL_IF(events[2].result.running != events[2].result.enabled);
		FAIL_IF(events[3].result.running != events[3].result.enabled);

		pred  += events[2].result.value;
		mpred += events[3].result.value;
	पूर्ण

	*miss_percent = 100 * mpred / pred;

	वापस 0;
पूर्ण

अटल व्योम setup_event(काष्ठा event *e, u64 config, अक्षर *name)
अणु
	event_init_named(e, config, name);

	e->attr.disabled = 1;
	e->attr.exclude_kernel = 1;
	e->attr.exclude_hv = 1;
	e->attr.exclude_idle = 1;
पूर्ण

क्रमागत spectre_v2_state अणु
	VULNERABLE = 0,
	UNKNOWN = 1,		// Works with FAIL_IF()
	NOT_AFFECTED,
	BRANCH_SERIALISATION,
	COUNT_CACHE_DISABLED,
	COUNT_CACHE_FLUSH_SW,
	COUNT_CACHE_FLUSH_HW,
	BTB_FLUSH,
पूर्ण;

अटल क्रमागत spectre_v2_state get_sysfs_state(व्योम)
अणु
	क्रमागत spectre_v2_state state = UNKNOWN;
	अक्षर buf[256];
	पूर्णांक len;

	स_रखो(buf, 0, माप(buf));
	FAIL_IF(पढ़ो_sysfs_file("devices/system/cpu/vulnerabilities/spectre_v2", buf, माप(buf)));

	// Make sure it's शून्य terminated
	buf[माप(buf) - 1] = '\0';

	// Trim the trailing newline
	len = म_माप(buf);
	FAIL_IF(len < 1);
	buf[len - 1] = '\0';

	म_लिखो("sysfs reports: '%s'\n", buf);

	// Order matters
	अगर (म_माला(buf, "Vulnerable"))
		state = VULNERABLE;
	अन्यथा अगर (म_माला(buf, "Not affected"))
		state = NOT_AFFECTED;
	अन्यथा अगर (म_माला(buf, "Indirect branch serialisation (kernel only)"))
		state = BRANCH_SERIALISATION;
	अन्यथा अगर (म_माला(buf, "Indirect branch cache disabled"))
		state = COUNT_CACHE_DISABLED;
	अन्यथा अगर (म_माला(buf, "Software count cache flush (hardware accelerated)"))
		state = COUNT_CACHE_FLUSH_HW;
	अन्यथा अगर (म_माला(buf, "Software count cache flush"))
		state = COUNT_CACHE_FLUSH_SW;
	अन्यथा अगर (म_माला(buf, "Branch predictor state flush"))
		state = BTB_FLUSH;

	वापस state;
पूर्ण

#घोषणा PM_BR_PRED_CCACHE	0x040a4	// P8 + P9
#घोषणा PM_BR_MPRED_CCACHE	0x040ac	// P8 + P9
#घोषणा PM_BR_PRED_PCACHE	0x048a0	// P9 only
#घोषणा PM_BR_MPRED_PCACHE	0x048b0	// P9 only

#घोषणा SPRN_PVR 287

पूर्णांक spectre_v2_test(व्योम)
अणु
	क्रमागत spectre_v2_state state;
	काष्ठा event events[4];
	s64 miss_percent;
	bool is_p9;

	// The PMU events we use only work on Power8 or later
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	state = get_sysfs_state();
	अगर (state == UNKNOWN) अणु
		म_लिखो("Error: couldn't determine spectre_v2 mitigation state?\n");
		वापस -1;
	पूर्ण

	स_रखो(events, 0, माप(events));

	setup_event(&events[0], PM_BR_PRED_CCACHE,  "PM_BR_PRED_CCACHE");
	setup_event(&events[1], PM_BR_MPRED_CCACHE, "PM_BR_MPRED_CCACHE");
	FAIL_IF(event_खोलो(&events[0]));
	FAIL_IF(event_खोलो_with_group(&events[1], events[0].fd) == -1);

	is_p9 = ((mfspr(SPRN_PVR) >>  16) & 0xFFFF) == 0x4e;

	अगर (is_p9) अणु
		// Count pattern cache too
		setup_event(&events[2], PM_BR_PRED_PCACHE,  "PM_BR_PRED_PCACHE");
		setup_event(&events[3], PM_BR_MPRED_PCACHE, "PM_BR_MPRED_PCACHE");

		FAIL_IF(event_खोलो_with_group(&events[2], events[0].fd) == -1);
		FAIL_IF(event_खोलो_with_group(&events[3], events[0].fd) == -1);
	पूर्ण

	FAIL_IF(करो_count_loop(events, is_p9, &miss_percent));

	event_report_justअगरied(&events[0], 18, 10);
	event_report_justअगरied(&events[1], 18, 10);
	event_बंद(&events[0]);
	event_बंद(&events[1]);

	अगर (is_p9) अणु
		event_report_justअगरied(&events[2], 18, 10);
		event_report_justअगरied(&events[3], 18, 10);
		event_बंद(&events[2]);
		event_बंद(&events[3]);
	पूर्ण

	म_लिखो("Miss percent %lld %%\n", miss_percent);

	चयन (state) अणु
	हाल VULNERABLE:
	हाल NOT_AFFECTED:
	हाल COUNT_CACHE_FLUSH_SW:
	हाल COUNT_CACHE_FLUSH_HW:
		// These should all not affect userspace branch prediction
		अगर (miss_percent > 15) अणु
			म_लिखो("Branch misses > 15%% unexpected in this configuration!\n");
			म_लिखो("Possible mis-match between reported & actual mitigation\n");
			/*
			 * Such a mismatch may be caused by a guest प्रणाली
			 * reporting as vulnerable when the host is mitigated.
			 * Return skip code to aव्योम detecting this as an error.
			 * We are not vulnerable and reporting otherwise, so
			 * missing such a mismatch is safe.
			 */
			अगर (state == VULNERABLE)
				वापस 4;

			वापस 1;
		पूर्ण
		अवरोध;
	हाल BRANCH_SERIALISATION:
		// This seems to affect userspace branch prediction a bit?
		अगर (miss_percent > 25) अणु
			म_लिखो("Branch misses > 25%% unexpected in this configuration!\n");
			म_लिखो("Possible mis-match between reported & actual mitigation\n");
			वापस 1;
		पूर्ण
		अवरोध;
	हाल COUNT_CACHE_DISABLED:
		अगर (miss_percent < 95) अणु
			म_लिखो("Branch misses < 20%% unexpected in this configuration!\n");
			म_लिखो("Possible mis-match between reported & actual mitigation\n");
			वापस 1;
		पूर्ण
		अवरोध;
	हाल UNKNOWN:
	हाल BTB_FLUSH:
		म_लिखो("Not sure!\n");
		वापस 1;
	पूर्ण

	म_लिखो("OK - Measured branch prediction rates match reported spectre v2 mitigation.\n");

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(spectre_v2_test, "spectre_v2");
पूर्ण
