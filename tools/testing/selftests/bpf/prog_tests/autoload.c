<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश <समय.स>
#समावेश "test_autoload.skel.h"

व्योम test_स्वतःload(व्योम)
अणु
	पूर्णांक duration = 0, err;
	काष्ठा test_स्वतःload* skel;

	skel = test_स्वतःload__खोलो_and_load();
	/* prog3 should be broken */
	अगर (CHECK(skel, "skel_open_and_load", "unexpected success\n"))
		जाओ cleanup;

	skel = test_स्वतःload__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		जाओ cleanup;

	/* करोn't load prog3 */
	bpf_program__set_स्वतःload(skel->progs.prog3, false);

	err = test_स्वतःload__load(skel);
	अगर (CHECK(err, "skel_load", "failed to load skeleton: %d\n", err))
		जाओ cleanup;

	err = test_स्वतःload__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	usleep(1);

	CHECK(!skel->bss->prog1_called, "prog1", "not called\n");
	CHECK(!skel->bss->prog2_called, "prog2", "not called\n");
	CHECK(skel->bss->prog3_called, "prog3", "called?!\n");

cleanup:
	test_स्वतःload__destroy(skel);
पूर्ण
