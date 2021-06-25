<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक ret = 0;
	pthपढ़ो_attr_t thपढ़ो_attr;
	cpu_set_t cs;

	pthपढ़ो_attr_init(&thपढ़ो_attr);
	CPU_ZERO(&cs);

	ret = pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, माप(cs), &cs);

	वापस ret;
पूर्ण
