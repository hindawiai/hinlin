<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <test_progs.h>
#समावेश <sys/syscall.h>
#समावेश "linked_maps.skel.h"

व्योम test_linked_maps(व्योम)
अणु
	पूर्णांक err;
	काष्ठा linked_maps *skel;

	skel = linked_maps__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	err = linked_maps__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ cleanup;

	/* trigger */
	syscall(SYS_getpgid);

	ASSERT_EQ(skel->bss->output_first1, 2000, "output_first1");
	ASSERT_EQ(skel->bss->output_second1, 2, "output_second1");
	ASSERT_EQ(skel->bss->output_weak1, 2, "output_weak1");

cleanup:
	linked_maps__destroy(skel);
पूर्ण
