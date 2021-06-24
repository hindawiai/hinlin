<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश <समय.स>
#समावेश "test_subprogs.skel.h"
#समावेश "test_subprogs_unused.skel.h"

अटल पूर्णांक duration;

व्योम test_subprogs(व्योम)
अणु
	काष्ठा test_subprogs *skel;
	काष्ठा test_subprogs_unused *skel2;
	पूर्णांक err;

	skel = test_subprogs__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	err = test_subprogs__attach(skel);
	अगर (CHECK(err, "skel_attach", "failed to attach skeleton: %d\n", err))
		जाओ cleanup;

	usleep(1);

	CHECK(skel->bss->res1 != 12, "res1", "got %d, exp %d\n", skel->bss->res1, 12);
	CHECK(skel->bss->res2 != 17, "res2", "got %d, exp %d\n", skel->bss->res2, 17);
	CHECK(skel->bss->res3 != 19, "res3", "got %d, exp %d\n", skel->bss->res3, 19);
	CHECK(skel->bss->res4 != 36, "res4", "got %d, exp %d\n", skel->bss->res4, 36);

	skel2 = test_subprogs_unused__खोलो_and_load();
	ASSERT_OK_PTR(skel2, "unused_progs_skel");
	test_subprogs_unused__destroy(skel2);

cleanup:
	test_subprogs__destroy(skel);
पूर्ण
