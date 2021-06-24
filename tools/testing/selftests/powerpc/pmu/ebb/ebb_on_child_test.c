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
 * Tests we can setup an EBB on our child. Nothing पूर्णांकeresting happens, because
 * even though the event is enabled and running the child hasn't enabled the
 * actual delivery of the EBBs.
 */

अटल पूर्णांक victim_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe)
अणु
	पूर्णांक i;

	FAIL_IF(रुको_क्रम_parent(पढ़ो_pipe));
	FAIL_IF(notअगरy_parent(ग_लिखो_pipe));

	/* Parent creates EBB event */

	FAIL_IF(रुको_क्रम_parent(पढ़ो_pipe));
	FAIL_IF(notअगरy_parent(ग_लिखो_pipe));

	/* Check the EBB is enabled by writing PMC1 */
	ग_लिखो_pmc1();

	/* EBB event is enabled here */
	क्रम (i = 0; i < 1000000; i++) ;

	वापस 0;
पूर्ण

पूर्णांक ebb_on_child(व्योम)
अणु
	जोड़ pipe पढ़ो_pipe, ग_लिखो_pipe;
	काष्ठा event event;
	pid_t pid;

	SKIP_IF(!ebb_is_supported());

	FAIL_IF(pipe(पढ़ो_pipe.fds) == -1);
	FAIL_IF(pipe(ग_लिखो_pipe.fds) == -1);

	pid = विभाजन();
	अगर (pid == 0) अणु
		/* NB order of pipes looks reversed */
		निकास(victim_child(ग_लिखो_pipe, पढ़ो_pipe));
	पूर्ण

	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	/* Child is running now */

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो_with_pid(&event, pid));
	FAIL_IF(ebb_event_enable(&event));

	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	/* Child should just निकास happily */
	FAIL_IF(रुको_क्रम_child(pid));

	event_बंद(&event);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(ebb_on_child, "ebb_on_child");
पूर्ण
