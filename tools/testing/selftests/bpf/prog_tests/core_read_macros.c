<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>

काष्ठा callback_head अणु
	काष्ठा callback_head *next;
	व्योम (*func)(काष्ठा callback_head *head);
पूर्ण;

/* ___shuffled flavor is just an illusion क्रम BPF code, it करोesn't really
 * exist and user-space needs to provide data in the memory layout that
 * matches callback_head. We just defined ___shuffled flavor to make it easier
 * to work with the skeleton
 */
काष्ठा callback_head___shuffled अणु
	काष्ठा callback_head___shuffled *next;
	व्योम (*func)(काष्ठा callback_head *head);
पूर्ण;

#समावेश "test_core_read_macros.skel.h"

व्योम test_core_पढ़ो_macros(व्योम)
अणु
	पूर्णांक duration = 0, err;
	काष्ठा test_core_पढ़ो_macros* skel;
	काष्ठा test_core_पढ़ो_macros__bss *bss;
	काष्ठा callback_head u_probe_in;
	काष्ठा callback_head___shuffled u_core_in;

	skel = test_core_पढ़ो_macros__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;
	bss = skel->bss;
	bss->my_pid = getpid();

	/* next poपूर्णांकers have to be set from the kernel side */
	bss->k_probe_in.func = (व्योम *)(दीर्घ)0x1234;
	bss->k_core_in.func = (व्योम *)(दीर्घ)0xabcd;

	u_probe_in.next = &u_probe_in;
	u_probe_in.func = (व्योम *)(दीर्घ)0x5678;
	bss->u_probe_in = &u_probe_in;

	u_core_in.next = &u_core_in;
	u_core_in.func = (व्योम *)(दीर्घ)0xdbca;
	bss->u_core_in = &u_core_in;

	err = test_core_पढ़ो_macros__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	usleep(1);

	ASSERT_EQ(bss->k_probe_out, 0x1234, "k_probe_out");
	ASSERT_EQ(bss->k_core_out, 0xabcd, "k_core_out");

	ASSERT_EQ(bss->u_probe_out, 0x5678, "u_probe_out");
	ASSERT_EQ(bss->u_core_out, 0xdbca, "u_core_out");

cleanup:
	test_core_पढ़ो_macros__destroy(skel);
पूर्ण
