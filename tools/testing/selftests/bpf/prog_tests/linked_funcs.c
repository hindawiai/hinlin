<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <test_progs.h>
#समावेश <sys/syscall.h>
#समावेश "linked_funcs.skel.h"

व्योम test_linked_funcs(व्योम)
अणु
	पूर्णांक err;
	काष्ठा linked_funcs *skel;

	skel = linked_funcs__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	skel->rodata->my_tid = syscall(SYS_gettid);
	skel->bss->syscall_id = SYS_getpgid;

	err = linked_funcs__load(skel);
	अगर (!ASSERT_OK(err, "skel_load"))
		जाओ cleanup;

	err = linked_funcs__attach(skel);
	अगर (!ASSERT_OK(err, "skel_attach"))
		जाओ cleanup;

	/* trigger */
	syscall(SYS_getpgid);

	ASSERT_EQ(skel->bss->output_val1, 2000 + 2000, "output_val1");
	ASSERT_EQ(skel->bss->output_ctx1, SYS_getpgid, "output_ctx1");
	ASSERT_EQ(skel->bss->output_weak1, 42, "output_weak1");

	ASSERT_EQ(skel->bss->output_val2, 2 * 1000 + 2 * (2 * 1000), "output_val2");
	ASSERT_EQ(skel->bss->output_ctx2, SYS_getpgid, "output_ctx2");
	/* output_weak2 should never be updated */
	ASSERT_EQ(skel->bss->output_weak2, 0, "output_weak2");

cleanup:
	linked_funcs__destroy(skel);
पूर्ण
