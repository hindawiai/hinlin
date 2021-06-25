<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश <समय.स>
#समावेश "test_vmlinux.skel.h"

#घोषणा MY_TV_NSEC 1337

अटल व्योम nsleep()
अणु
	काष्ठा बारpec ts = अणु .tv_nsec = MY_TV_NSEC पूर्ण;

	(व्योम)syscall(__NR_nanosleep, &ts, शून्य);
पूर्ण

व्योम test_vmlinux(व्योम)
अणु
	पूर्णांक duration = 0, err;
	काष्ठा test_vmlinux* skel;
	काष्ठा test_vmlinux__bss *bss;

	skel = test_vmlinux__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;
	bss = skel->bss;

	err = test_vmlinux__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger everything */
	nsleep();

	CHECK(!bss->tp_called, "tp", "not called\n");
	CHECK(!bss->raw_tp_called, "raw_tp", "not called\n");
	CHECK(!bss->tp_btf_called, "tp_btf", "not called\n");
	CHECK(!bss->kprobe_called, "kprobe", "not called\n");
	CHECK(!bss->fentry_called, "fentry", "not called\n");

cleanup:
	test_vmlinux__destroy(skel);
पूर्ण
