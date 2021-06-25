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
 * Tests a per-task event vs an EBB - in that order. The EBB should push the
 * per-task event off the PMU.
 */

अटल पूर्णांक setup_child_event(काष्ठा event *event, pid_t child_pid)
अणु
	event_init_named(event, 0x400FA, "PM_RUN_INST_CMPL");

	event->attr.exclude_kernel = 1;
	event->attr.exclude_hv = 1;
	event->attr.exclude_idle = 1;

	FAIL_IF(event_खोलो_with_pid(event, child_pid));
	FAIL_IF(event_enable(event));

	वापस 0;
पूर्ण

पूर्णांक task_event_vs_ebb(व्योम)
अणु
	जोड़ pipe पढ़ो_pipe, ग_लिखो_pipe;
	काष्ठा event event;
	pid_t pid;
	पूर्णांक rc;

	SKIP_IF(!ebb_is_supported());

	FAIL_IF(pipe(पढ़ो_pipe.fds) == -1);
	FAIL_IF(pipe(ग_लिखो_pipe.fds) == -1);

	pid = विभाजन();
	अगर (pid == 0) अणु
		/* NB order of pipes looks reversed */
		निकास(ebb_child(ग_लिखो_pipe, पढ़ो_pipe));
	पूर्ण

	/* We setup the task event first */
	rc = setup_child_event(&event, pid);
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
	/* The EBB event should push the task event off so the child should succeed */
	FAIL_IF(रुको_क्रम_child(pid));
	FAIL_IF(event_disable(&event));
	FAIL_IF(event_पढ़ो(&event));

	event_report(&event);

	/* The task event may have run, or not so we can't निश्चित anything about it */

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(task_event_vs_ebb, "task_event_vs_ebb");
पूर्ण
