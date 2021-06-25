<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <माला.स>
#समावेश "evlist.h"
#समावेश "env.h"
#समावेश "sample-raw.h"

/*
 * Check platक्रमm the perf data file was created on and perक्रमm platक्रमm
 * specअगरic पूर्णांकerpretation.
 */
व्योम evlist__init_trace_event_sample_raw(काष्ठा evlist *evlist)
अणु
	स्थिर अक्षर *arch_pf = perf_env__arch(evlist->env);

	अगर (arch_pf && !म_भेद("s390", arch_pf))
		evlist->trace_event_sample_raw = evlist__s390_sample_raw;
पूर्ण
