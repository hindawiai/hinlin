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
 * Tests we can setup an EBB on our child. The child expects this and enables
 * EBBs, which are then delivered to the child, even though the event is
 * created by the parent.
 */

अटल पूर्णांक victim_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe)
अणु
	FAIL_IF(रुको_क्रम_parent(पढ़ो_pipe));

	/* Setup our EBB handler, beक्रमe the EBB event is created */
	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();

	FAIL_IF(notअगरy_parent(ग_लिखो_pipe));

	जबतक (ebb_state.stats.ebb_count < 20) अणु
		FAIL_IF(core_busy_loop());
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	वापस 0;
पूर्ण

/* Tests we can setup an EBB on our child - अगर it's expecting it */
पूर्णांक ebb_on_willing_child(व्योम)
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

	/* Signal the child to setup its EBB handler */
	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	/* Child is running now */

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो_with_pid(&event, pid));
	FAIL_IF(ebb_event_enable(&event));

	/* Child show now take EBBs and then निकास */
	FAIL_IF(रुको_क्रम_child(pid));

	event_बंद(&event);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(ebb_on_willing_child, "ebb_on_willing_child");
पूर्ण
