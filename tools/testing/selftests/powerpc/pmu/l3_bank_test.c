<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "event.h"
#समावेश "utils.h"

#घोषणा MALLOC_SIZE     (0x10000 * 10)  /* Ought to be enough .. */

/*
 * Tests that the L3 bank handling is correct. We fixed it in commit e9aaac1.
 */
अटल पूर्णांक l3_bank_test(व्योम)
अणु
	काष्ठा event event;
	अक्षर *p;
	पूर्णांक i;

	// The L3 bank logic is only used on Power8 or later
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	p = दो_स्मृति(MALLOC_SIZE);
	FAIL_IF(!p);

	event_init(&event, 0x84918F);

	FAIL_IF(event_खोलो(&event));

	क्रम (i = 0; i < MALLOC_SIZE; i += 0x10000)
		p[i] = i;

	event_पढ़ो(&event);
	event_report(&event);

	FAIL_IF(event.result.running == 0);
	FAIL_IF(event.result.enabled == 0);

	event_बंद(&event);
	मुक्त(p);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(l3_bank_test, "l3_bank_test");
पूर्ण
