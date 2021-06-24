<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश "api/fs/fs.h"
#समावेश "util/pmu.h"
#समावेश "util/topdown.h"

/*
 * Check whether we can use a group क्रम top करोwn.
 * Without a group may get bad results due to multiplexing.
 */
bool arch_topकरोwn_check_group(bool *warn)
अणु
	पूर्णांक n;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/nmi_watchdog", &n) < 0)
		वापस false;
	अगर (n > 0) अणु
		*warn = true;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम arch_topकरोwn_group_warn(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि,
		"nmi_watchdog enabled with topdown. May give wrong results.\n"
		"Disable with echo 0 > /proc/sys/kernel/nmi_watchdog\n");
पूर्ण

#घोषणा TOPDOWN_SLOTS		0x0400

अटल bool is_topकरोwn_slots_event(काष्ठा evsel *counter)
अणु
	अगर (!counter->pmu_name)
		वापस false;

	अगर (म_भेद(counter->pmu_name, "cpu"))
		वापस false;

	अगर (counter->core.attr.config == TOPDOWN_SLOTS)
		वापस true;

	वापस false;
पूर्ण

/*
 * Check whether a topकरोwn group supports sample-पढ़ो.
 *
 * Only Topकरोwn metic supports sample-पढ़ो. The slots
 * event must be the leader of the topकरोwn group.
 */

bool arch_topकरोwn_sample_पढ़ो(काष्ठा evsel *leader)
अणु
	अगर (!pmu_have_event("cpu", "slots"))
		वापस false;

	अगर (is_topकरोwn_slots_event(leader))
		वापस true;

	वापस false;
पूर्ण
