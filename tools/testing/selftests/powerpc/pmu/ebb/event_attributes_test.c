<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


/*
 * Test various attributes of the EBB event are enक्रमced.
 */
पूर्णांक event_attributes(व्योम)
अणु
	काष्ठा event event, leader;

	SKIP_IF(!ebb_is_supported());

	event_init(&event, 0x1001e);
	event_leader_ebb_init(&event);
	/* Expected to succeed */
	FAIL_IF(event_खोलो(&event));
	event_बंद(&event);


	event_init(&event, 0x001e); /* CYCLES - no PMC specअगरied */
	event_leader_ebb_init(&event);
	/* Expected to fail, no PMC specअगरied */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&event, 0x2001e);
	event_leader_ebb_init(&event);
	event.attr.exclusive = 0;
	/* Expected to fail, not exclusive */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&event, 0x3001e);
	event_leader_ebb_init(&event);
	event.attr.freq = 1;
	/* Expected to fail, sets freq */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&event, 0x4001e);
	event_leader_ebb_init(&event);
	event.attr.sample_period = 1;
	/* Expected to fail, sets sample_period */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&event, 0x1001e);
	event_leader_ebb_init(&event);
	event.attr.enable_on_exec = 1;
	/* Expected to fail, sets enable_on_exec */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&event, 0x1001e);
	event_leader_ebb_init(&event);
	event.attr.inherit = 1;
	/* Expected to fail, sets inherit */
	FAIL_IF(event_खोलो(&event) == 0);


	event_init(&leader, 0x1001e);
	event_leader_ebb_init(&leader);
	FAIL_IF(event_खोलो(&leader));

	event_init(&event, 0x20002);
	event_ebb_init(&event);

	/* Expected to succeed */
	FAIL_IF(event_खोलो_with_group(&event, leader.fd));
	event_बंद(&leader);
	event_बंद(&event);


	event_init(&leader, 0x1001e);
	event_leader_ebb_init(&leader);
	FAIL_IF(event_खोलो(&leader));

	event_init(&event, 0x20002);

	/* Expected to fail, event करोesn't request EBB, leader करोes */
	FAIL_IF(event_खोलो_with_group(&event, leader.fd) == 0);
	event_बंद(&leader);


	event_init(&leader, 0x1001e);
	event_leader_ebb_init(&leader);
	/* Clear the EBB flag */
	leader.attr.config &= ~(1ull << 63);

	FAIL_IF(event_खोलो(&leader));

	event_init(&event, 0x20002);
	event_ebb_init(&event);

	/* Expected to fail, leader करोesn't request EBB */
	FAIL_IF(event_खोलो_with_group(&event, leader.fd) == 0);
	event_बंद(&leader);


	event_init(&leader, 0x1001e);
	event_leader_ebb_init(&leader);
	leader.attr.exclusive = 0;
	/* Expected to fail, leader isn't exclusive */
	FAIL_IF(event_खोलो(&leader) == 0);


	event_init(&leader, 0x1001e);
	event_leader_ebb_init(&leader);
	leader.attr.pinned = 0;
	/* Expected to fail, leader isn't pinned */
	FAIL_IF(event_खोलो(&leader) == 0);

	event_init(&event, 0x1001e);
	event_leader_ebb_init(&event);
	/* Expected to fail, not a task event */
	SKIP_IF(require_paranoia_below(1));
	FAIL_IF(event_खोलो_with_cpu(&event, 0) == 0);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(event_attributes, "event_attributes");
पूर्ण
