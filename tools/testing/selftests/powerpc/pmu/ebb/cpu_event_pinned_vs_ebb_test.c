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
 * Tests a pinned cpu event vs an EBB - in that order. The pinned cpu event
 * should reमुख्य and the EBB event should fail to enable.
 */

अटल पूर्णांक setup_cpu_event(काष्ठा event *event, पूर्णांक cpu)
अणु
	event_init_named(event, 0x400FA, "PM_RUN_INST_CMPL");

	event->attr.pinned = 1;

	event->attr.exclude_kernel = 1;
	event->attr.exclude_hv = 1;
	event->attr.exclude_idle = 1;

	SKIP_IF(require_paranoia_below(1));
	FAIL_IF(event_खोलो_with_cpu(event, cpu));
	FAIL_IF(event_enable(event));

	वापस 0;
पूर्ण

पूर्णांक cpu_event_pinned_vs_ebb(व्योम)
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

	/* We setup the cpu event first */
	rc = setup_cpu_event(&event, cpu);
	अगर (rc) अणु
		समाप्त_child_and_रुको(pid);
		वापस rc;
	पूर्ण

	/* Signal the child to install its EBB event and रुको */
	अगर (sync_with_child(पढ़ो_pipe, ग_लिखो_pipe))
		/* If it fails, रुको क्रम it to निकास */
		जाओ रुको;

	/* Signal the child to run */
	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

रुको:
	/* We expect it to fail to पढ़ो the event */
	FAIL_IF(रुको_क्रम_child(pid) != 2);

	FAIL_IF(event_disable(&event));
	FAIL_IF(event_पढ़ो(&event));

	event_report(&event);

	/* The cpu event should have run */
	FAIL_IF(event.result.value == 0);
	FAIL_IF(event.result.enabled != event.result.running);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(cpu_event_pinned_vs_ebb, "cpu_event_pinned_vs_ebb");
पूर्ण
