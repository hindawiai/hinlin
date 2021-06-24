<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश <test_progs.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/btf.h>
#समावेश "test_ksyms_module.skel.h"

अटल पूर्णांक duration;

व्योम test_ksyms_module(व्योम)
अणु
	काष्ठा test_ksyms_module* skel;
	पूर्णांक err;

	skel = test_ksyms_module__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	err = test_ksyms_module__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	usleep(1);

	ASSERT_EQ(skel->bss->triggered, true, "triggered");
	ASSERT_EQ(skel->bss->out_mod_ksym_global, 123, "global_ksym_val");

cleanup:
	test_ksyms_module__destroy(skel);
पूर्ण
