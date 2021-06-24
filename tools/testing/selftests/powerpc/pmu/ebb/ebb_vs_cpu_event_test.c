<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "ebb.h"


/*
 * Tests an EBB vs a cpu event - in that order. The EBB should क्रमce the cpu
 * event off the PMU.
 */

अटल पूर्णांक setup_cpu_event(काष्ठा event *event, पूर्णांक cpu)
अणु
	event_init_named(event, 0x400FA, "PM_RUN_INST_CMPL");

	event->attr.exclude_kernel = 1;
	event->attr.exclude_hv = 1;
	event->attr.exclude_idle = 1;

	SKIP_IF(require_paranoia_below(1));
	FAIL_IF(event_खोलो_with_cpu(event, cpu));
	FAIL_IF(event_enable(event));

	वापस 0;
पूर्ण

पूर्णांक ebb_vs_cpu_event(व्योम)
अणु
	जोड़ pipe पढ़ो_pipe, ग_लिखो_pipe;
	काष्ठा event event;
	पूर्णांक cpu, rc;
	pid_t pid;

	SKIP_IF(!ebb_is_supported());

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);
	FAIL_IF(bind_to_cpu(cpu));

	FAIL_IF(pipe(पढ़ो_pipe.fds) == -1);
	FAIL_IF(pipe(ग_लिखो_pipe.fds) == -1);

	pid = विभाजन();
	अगर (pid == 0) अणु
		/* NB order of pipes looks reversed */
		निकास(ebb_child(ग_लिखो_pipe, पढ़ो_pipe));
	पूर्ण

	/* Signal the child to install its EBB event and रुको */
	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	/* Now try to install our CPU event */
	rc = setup_cpu_event(&event, cpu);
	अगर (rc) अणु
		समाप्त_child_and_रुको(pid);
		वापस rc;
	पूर्ण

	/* Signal the child to run */
	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	/* .. and रुको क्रम it to complete */
	FAIL_IF(रुको_क्रम_child(pid));
	FAIL_IF(event_disable(&event));
	FAIL_IF(event_पढ़ो(&event));

	event_report(&event);

	/* The cpu event may have run, but we करोn't expect 100% */
	FAIL_IF(event.result.enabled >= event.result.running);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(ebb_vs_cpu_event, "ebb_vs_cpu_event");
पूर्ण
